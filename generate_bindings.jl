import JSON3
using Clang
import Clang.LibClang as LibClang
import Clang_jll


# These types are implemented by cimgui
const existing_templates = Dict(
    "ImVector<ImGuiWindow *>" => "ImVector_ImGuiWindowPtr",
    "ImVector<char>" => "ImVector_char",
    "ImVector<const char *>" => "ImVector_const_charPtr"
)

# These we need to generate ourselves
const generated_templates = Dict(
    "ImVector<ImGuiTest *>" => "ImVector_ImGuiTest_Ptr",
    "ImVector<ImGuiTestInput>" => "ImVector_ImGuiTestInput",
    "ImVector<ImGuiTestRunTask>" => "ImVector_ImGuiTestRunTask",
    "ImVector<ImGuiTestInfoTask *>" => "ImVector_ImGuiTestInfoTask_Ptr",
    "ImVector<ImGuiTestItemInfo>" => "ImVector_ImGuiTestItemInfo",
    "ImVector<ImGuiTestLogLineInfo>" => "ImVector_ImGuiTestLogLineInfo",
    "ImVector<ImGuiPerfToolEntry>" => "ImVector_ImGuiPerfToolEntry",
    "ImVector<ImGuiPerfToolBatch>" => "ImVector_ImGuiPerfToolBatch",
    "ImVector<ImGuiCaptureWindowData>" => "ImVector_ImGuiCaptureWindowData",

    "ImVector<double>" => "ImVector_double",
    "ImVector<char *>" => "ImVector_charPtr",
    "ImVector<unsigned int>" => "ImVector_Uint",
    "ImVector<unsigned long long>" => "ImVector_Ulonglong",

    "ImMovingAverage<double>" => "ImMovingAverage_double",

    "ImPool<ImGuiTestItemInfo>" => "ImPool_ImGuiTestItemInfo"
)

# Dictionary of filename -> list of lines in the file
const header_files = Dict{String, Vector{String}}()

# Store the Clang translation unit in a global variable to ensure it doesn't get
# garbage collected.
tu::Union{Nothing, TranslationUnit} = nothing

# Represent information about a function argument
ArgInfo = @NamedTuple{name::String, type::String}

mutable struct CxxFunction
    stname::String
    ret::String
    retref::Bool
    argsT::Vector{ArgInfo}
    args::String
    defaults::Dict{String, String}
    isvararg::Bool
    constructor::Bool
    destructor::Bool
    funcname::String
    cimguiname::String
    ov_cimguiname::String
    location::String
    comment::Union{Nothing, String}

    body::String
end

signature(x::CxxFunction) = "$(x.ret) $(x.ov_cimguiname)$(x.args)"

function implementation(x::CxxFunction)
    """
    $(signature(x)) {
        $(x.body)
    }
    """
end

struct CxxStruct
    name::String
    location::String
    comment::Union{Nothing, String}
    fields::Vector{Dict}
    implementation::String
    methods::Vector{CxxFunction}
end

struct CxxEnum
    name::String
    location::String
    comment::Union{Nothing, String}
    constants::Vector{Dict}
    implementation::String
end

function is_fn_pointer(type)
    kind(type) == LibClang.CXType_Pointer && kind(Clang.getCanonicalType(Clang.getPointeeType(type))) == LibClang.CXType_FunctionProto
end

# Convert a C++ type to a C type. This will:
# - Convert references to pointers
# - Replace templated types with their C counterpart
function get_c_type(cursor)
    # If this is a function pointer, just return the spelling. This will
    # preserve the original spelling like 'ImFuncPtr(...)' etc.
    if is_fn_pointer(cursor)
        return false, spelling(cursor)
    end

    type = Clang.getCanonicalType(cursor)

    # Another quick check: if this is a *function* rather than a *function
    # pointer*, decay the type to a pointer. C++ does this automatically but in
    # C we have to be explicit. Needed for the
    # ImGuiCaptureContext(ImGuiScreenCaptureFunc) constructor.
    if kind(type) == LibClang.CXType_FunctionProto
        return false, "$(spelling(cursor))*"
    end

    is_ref = kind(type) == LibClang.CXType_LValueReference
    is_pointer = kind(type) == LibClang.CXType_Pointer || is_ref
    type = is_pointer ? Clang.getPointeeType(type) : type

    type_spelling = spelling(type)
    if !isnothing(match(r"\w+<.+>", type_spelling))
        if haskey(existing_templates, type_spelling)
            type_spelling = existing_templates[type_spelling]
        elseif haskey(generated_templates, type_spelling)
            type_spelling = generated_templates[type_spelling]
        else
            error("Unsupported template type: $(type_spelling)")
        end
    end

    if type_spelling == "__va_list_tag[1]"
        # Special case for ImGuiTestContext_LogExV
        type_spelling = "va_list"
    elseif type_spelling == "_IO_FILE"
        # Special case for ImGuiCaptureContext::_VideoEncoderPipe
        type_spelling = "FILE"
    end

    type_spelling = is_pointer ? "$(type_spelling)*" : type_spelling

    is_ref, type_spelling
end

# Generate a C type that's ABI compatible with a C++ templated type. Used for
# generating ImVector/ImPool specializations.
function generate_template(type_str, cursor)
    template_type, template_arg = match(r"(\w+)<(.+)>", type_str).captures

    type = filter(!Clang.is_forward_declaration, search(cursor, string(template_type))) |> only
    field_cursors = [c for c in children(type) if kind(c) == LibClang.CXCursor_FieldDecl]
    fields = String[]
    for x in field_cursors
        field_type = spelling(Clang.getCursorType(x))
        if field_type == "T *"
            # This is an ImVector
            field_type = "$(template_arg)*"
        elseif field_type == "ImVector<T>"
            # This is an ImPool
            field_type = "ImVector_$(template_arg)"
        elseif field_type == "ImVector<TYPE>"
            # This is ImMovingAverage::Samples
            field_type = "ImVector_$(template_arg)"
        elseif field_type == "TYPE"
            # This is ImMovingAverage::Accum
            field_type = template_arg
        end

        push!(fields, "$(field_type) $(spelling(x));")
    end

    struct_name = generated_templates[type_str]
    fields_str = join(fields, " ")

    return "typedef struct $struct_name { $fields_str } $struct_name"
end

# Find a comment on the same line as `line_no`
function find_sameline_comment(header, line_no)
    line = header_files[header][line_no]
    comment_idx = findfirst("//", line)

    if isnothing(comment_idx)
        nothing
    else
        line[first(comment_idx):end]
    end
end

# Find a comment or comment block above `line_no`
function find_above_comment(header, line_no)
    all_comments = String[]
    for i in 1:line_no - 1
        comment_match = match(r"\s*(//.+)", header_files[header][line_no - i])
        if !isnothing(comment_match)
            pushfirst!(all_comments, comment_match.captures[1])
        else
            break
        end
    end

    isempty(all_comments) ? nothing : join(all_comments, "\n")
end

# Create a CxxFunction from a function cursor
function wrap_function(cursor, parent_struct=nothing)
    is_method = !isnothing(parent_struct)
    is_constructor = kind(cursor) == LibClang.CXCursor_Constructor
    is_destructor = kind(cursor) == LibClang.CXCursor_Destructor
    struct_name = is_method ? spelling(parent_struct) : ""

    # Get the function type, name, and return type
    func_type = Clang.getCursorType(cursor)
    ret_type = (is_constructor || is_destructor) ? nothing : Clang.getCursorResultType(cursor)

    ret_is_void = if is_destructor
        true
    elseif is_constructor
        false
    else
        kind(ret_type) == LibClang.CXType_Void
    end
    ret_is_ref = (is_constructor || is_destructor) ? false : kind(ret_type) == LibClang.CXType_LValueReference

    ret_type_str = if is_constructor
        "$struct_name *"
    elseif is_destructor
        "void"
    elseif ret_is_ref
        t = Clang.getPointeeType(ret_type)
        "$(spelling(t)) *"
    else
        spelling(ret_type)
    end

    funcname = is_destructor ? "destroy" : spelling(cursor)
    cimguiname = if is_method
        "$(struct_name)_$(funcname)"
    else
        "c$(funcname)"
    end
    
    # Get the arguments and their types
    n_args = Clang.getNumArguments(cursor)
    argsT = ArgInfo[]
    if is_method && !is_constructor
        push!(argsT, (; name="self", type="$(struct_name)*"))
    end

    # Collect all the arguments to pass to the upstream C++ function,
    # dereferencing pointers as necessary if an argument is a reference.
    forwarded_args = []
    is_vararg = Clang.isVariadic(cursor)
    defaults = Dict{String, String}()
    for i in 0:n_args - 1
        arg = Clang.getArgument(cursor, i)
        arg_spelling = spelling(arg)
        arg_source = Clang.getSourceCode(arg)
        default_value_match = match(r".+=\s*(.+)\s*", arg_source)
        if !isnothing(default_value_match)
            defaults[arg_spelling] = default_value_match.captures[1]
        end

        is_ref, arg_type = get_c_type(LibClang.clang_getArgType(func_type, i))
        push!(argsT, (; name=arg_spelling, type=arg_type))
        push!(forwarded_args, (is_ref, arg_spelling))
    end
    if is_vararg
        push!(argsT, (; name="...", type=""))
        push!(forwarded_args, (false, "args"))
    end

    arg_names_str = join([is_ref ? "*$(x)" : x for (is_ref, x) in forwarded_args], ", ")
    inner_call = if is_constructor
        "IM_NEW($struct_name)($arg_names_str)"
    elseif is_destructor
        "IM_DELETE(self)"
    elseif is_method
        "self->$funcname($arg_names_str)"
    else
        "$funcname($arg_names_str)"
    end
    inner_call = ret_is_ref ? "&($inner_call)" : inner_call

    body = if is_vararg
        if ret_is_void
            """
            va_list args;
            va_start(args, $(forwarded_args[end - 1][2]));
            $(inner_call);
            va_end(args);
            """
        else            
            """
            va_list args;
            va_start(args, $(forwarded_args[end - 1][2]));
            $(ret_type_str) ret = $(inner_call);
            va_end(args);
            return ret;
            """
        end
    else
        ret_is_void ? "$(inner_call);" : "return $(inner_call);"
    end
    
    args = join(["$(x.type) $(x.name)" for x in argsT], ", ")
    args = "($args)"

    filename, line_no, _ = Clang.get_file_line_column(cursor)
    filename = basename(filename)
    comment = find_sameline_comment(filename, line_no)
    location = "$(filename[1:end-2]):$(line_no)"

    CxxFunction(struct_name, ret_type_str, ret_is_ref,
                argsT, args, defaults, is_vararg,
                is_constructor, is_destructor,
                funcname, cimguiname, cimguiname, location,
                comment,
                body)
end

# Create a CxxStruct for a struct cursor
function wrap_struct(cursor, blacklist)
    struct_name = spelling(cursor)
    field_cursors = [c for c in children(cursor) if kind(c) == LibClang.CXCursor_FieldDecl]

    fields = Dict[]            # Holds metadata for structs_and_enums.json
    fields_str_list = String[] # Holds each C-compatible field definition

    # Process all fields
    for c in field_cursors
        type = Clang.getCursorType(c)
        is_array = kind(type) == LibClang.CXType_ConstantArray

        is_ref, type_str = get_c_type(type)
        if is_ref
            error("Cannot wrap struct $(struct_name), it has a reference field which cannot be represented in C")
        end

        filename, line_no, _ = Clang.get_file_line_column(c)
        comment = find_sameline_comment(basename(filename), line_no)
        name = spelling(c)

        if is_array
            # Strip the size from the type and move it to the name
            size_str = type_str[findfirst(r"\[\d+\]", type_str)]
            type_str = chopsuffix(type_str, size_str)
            name = name * size_str
        end

        d = Dict{String, Any}("name" => name,
                              "type" => type_str)
        if is_array
            d["size"] = Clang.getNumElements(type)
        end
        if !isnothing(comment)
            d["comment"] = Dict("sameline" => comment)
        end

        push!(fields, d)

        str = if is_fn_pointer(type)
            # Function pointer fields can have slightly different syntax, so
            # just return the source code stripped of any default value.
            source = Clang.getSourceCode(c)
            contains(source, "=") ? match(r"(.*\w+)\s*=.+", source).captures[1] : source
        else
            "$(type_str) $(name)"
        end
        str = "    $(str);" * (isnothing(comment) ? "" : " $(comment)")
        push!(fields_str_list, str)
    end

    fields_str = join(fields_str_list, "\n")
    implementation = """
    struct $struct_name {
    $fields_str
    };
    """

    # Now that we've got all the fields, wrap the struct methods
    wrapped_methods = CxxFunction[]
    for c in children(cursor)
        if kind(c) in (LibClang.CXCursor_CXXMethod, LibClang.CXCursor_Constructor, LibClang.CXCursor_Destructor)
            func_name = spelling(c)
            blacklisted = any(!isnothing, [match(re, func_name) for re in blacklist])
            if !blacklisted
                push!(wrapped_methods, wrap_function(c, cursor))
            end
        end
    end

    filename, line_no, _ = Clang.get_file_line_column(cursor)
    filename = basename(filename)
    location = "$(filename[1:end - 2]):$(line_no)"
    comment = find_above_comment(filename, line_no)

    CxxStruct(struct_name, location, comment, fields, implementation, wrapped_methods)
end

# Create a CxxEnum for an enum cursor
function wrap_enum(cursor)
    # Collect metadata about each constant for structs_and_enums.json
    constants = Dict[]
    for c in children(cursor)
        name = spelling(c)
        calc_value = Clang.value(c)
        filename, line_no, _ = Clang.get_file_line_column(c)
        comment = find_sameline_comment(basename(filename), line_no)

        constant_source = Clang.getSourceCode(c)
        value_match = match(r"=\s*(.+)", constant_source)
        value = isnothing(value_match) ? "" : value_match.captures[1]

        d = Dict("name" => name, "value" => value, "calc_value" => calc_value)
        if !isnothing(comment)
            d["comment"] = comment
        end

        push!(constants, d)
    end

    filename, line_no, _ = Clang.get_file_line_column(cursor)
    filename = basename(filename)
    location = "$(filename[1:end - 2]):$(line_no)"

    comment = find_above_comment(filename, line_no)
    name = spelling(cursor)

    # The actual implementation of the enum is almost C-compatible, so we just
    # use the original source code (which has the advantage of automatically
    # preserving constant comments). The only thing to remove is any underlying
    # type, since that's only supported since C23.
    implementation = Clang.getSourceCode(cursor)
    implementation = replace(implementation, r" : .+" => "")

    if !endswith(name, "_")
        implementation = "typedef $(implementation) $(name)"
    end

    CxxEnum(name, location, comment, constants, implementation)
end

# For wrapping typedefs we always use the original source code
wrap_typedef(cursor) = Clang.getSourceCode(cursor)

# Convert a type into something that can go in a function name, e.g. 'ImGuiRef*'
# -> 'RefPtr'. Used for generating template specializations.
function simplify_type(t)
    suffix = replace(t, "ImGui" => "")
    suffix = replace(suffix, "unsigned" => "U")
    suffix = replace(suffix, r"(const )?char\s*\*" => "Str")
    suffix = replace(suffix, "*" => "Ptr")
    suffix = replace(suffix, " " => "")
end

# Update a single CxxFunction in `overloads` to use a de-overloaded name
function update_overload(t, arg_idx, overloads, last_suffix="")
    overload = filter(x -> get(x.argsT, arg_idx, (; type=false)).type == t, overloads) |> only
    suffix = simplify_type(t)
    overload.ov_cimguiname = "$(overload.cimguiname)_$(last_suffix)$(suffix)"
end

# Rename overloads of all the CxxFunction's in `functions` to avoid naming
# conflicts.
function deoverload!(functions)
    visited_functions = Set{String}()

    for f in functions
        # Keep track of which functions we've processed already
        if f.cimguiname in visited_functions
            continue
        end
        push!(visited_functions, f.cimguiname)

        # Check if there are any overloads at all
        overloads = filter(x -> x.cimguiname == f.cimguiname, functions)
        if length(overloads) == 1
            continue
        end

        # Find the maximum number of args of any overload
        max_args = maximum(x -> length(x.argsT), overloads)
        # Track how many overloads we've processed so we know when to exit
        visited_overloads = 0
        # The `last_suffix` is needed for cases like this:
        #   foo(int)      -> foo_int
        #   foo(int, int) -> foo_intint
        # In cases where an overload is at the end of its argument list, but
        # there are other overloads with more args, and all the args match
        # so far, we have to track the suffix of the `foo(int)` overload to
        # use in the next suffixes.
        last_suffix = ""

        # Iterate over all available argument indices
        for i in 1:max_args
            if visited_overloads == length(overloads)
                break
            end

            # Count how many times each type appears at arg index `i` for
            # all the overloads.
            type_counts = Dict{String, Int}()
            for overload in overloads
                if i <= length(overload.argsT)
                    t = overload.argsT[i].type
                    type_counts[t] = get!(type_counts, t, 0) + 1
                end
            end

            # Get all the types that only appear once and update their
            # overloads.
            single_types = [t for (t, c) in type_counts if c == 1]
            for t in single_types
                update_overload(t, i, overloads, last_suffix)
                visited_overloads += 1
            end

            # If we didn't find any overloads to update and we're at the end
            # of the argument list for one of the overloads, update it.
            if isempty(single_types) && visited_overloads < length(overloads)
                filtered_overloads = filter(x -> length(x.argsT) == i, overloads)
                if isempty(filtered_overloads)
                    continue
                end

                t = filtered_overloads[1].argsT[i].type
                last_suffix = simplify_type(t)
                update_overload(t, i, filtered_overloads)
                visited_overloads += 1
            end
        end
    end
end

function generate()
    imgui_root = joinpath(@__DIR__, "cimgui", "imgui")
    te_root = joinpath(@__DIR__, "imgui_test_engine", "imgui_test_engine")
    args = ["-x", "c++", "-I$(imgui_root)", "-I$(te_root)", "-DIMGUI_TEST_ENGINE_ENABLE_COROUTINE_STDTHREAD_IMPL"]

    # Find the system #include directories to avoid missing header warnings
    stderr_pipe = Pipe()
    run(pipeline(`$(Clang_jll.clang()) -v -c -x c++ /dev/null`; stderr=stderr_pipe))
    close(stderr_pipe.in)
    record = false
    for l in eachline(stderr_pipe)
        if startswith(l, "#include <...> search starts here")
            record = true
        elseif startswith(l, "End of search list")
            break
        elseif record
            push!(args, "-I$(strip(l))")
        end
    end

    headers = [
        "imgui_capture_tool.h",
        "imgui_te_context.h",
        "imgui_te_coroutine.h",
        "imgui_te_engine.h",
        "imgui_te_exporters.h",
        "imgui_te_internal.h",
        "imgui_te_perftool.h",
        "imgui_te_ui.h",
        "imgui_te_utils.h"
    ]
    wrapped_structs = CxxStruct[]
    wrapped_enums = CxxEnum[]
    wrapped_typedefs = String[]
    wrapped_functions = Dict{String, Vector{CxxFunction}}() # Dictionary of filename -> functions

    blacklist = [
        # Haven't figured out how to wrap these yet
        r"ImGuiTestEngineUtil_appendf_auto", r"operator=", r"operator\[\]",
        # ImGuiTestContext::ItemOpenFullPath() is declared, but not implementated for some reason
        r"ItemOpenFullPath"]
    global tu = Clang.parse_header(Index(), joinpath(@__DIR__, "all_includes.h"), args)
    root_cursor = Clang.getTranslationUnitCursor(tu)

    for header in headers
        wrapped_functions[header] = CxxFunction[]
        header_files[header] = readlines(joinpath(te_root, header))
    end

    push!(wrapped_typedefs, "typedef void Str; // Manual typedef to avoid having to wrap the Str class")

    # Generate template specializations from one of the headers. Go in reverse
    # sorted order so that ImPool specializations are at the end (they may need
    # a specialized ImVector).
    for t in generated_templates |> keys |> collect |> sort |> reverse
        push!(wrapped_typedefs, generate_template(t, root_cursor))
    end

    # Wrap all the symbols found in the headers
    for c in children(root_cursor)
        symbol_name = spelling(c)
        filename = basename(Clang.get_filename(c))
        blacklisted = any(!isnothing, [match(re, symbol_name) for re in blacklist])
        if blacklisted || !in(filename, headers)
            continue
        end

        k = kind(c)
        if k == LibClang.CXCursor_StructDecl && !Clang.is_forward_declaration(c)
            push!(wrapped_structs, wrap_struct(c, blacklist))
        elseif k == LibClang.CXCursor_EnumDecl && !Clang.is_forward_declaration(c)
            push!(wrapped_enums, wrap_enum(c))
        elseif k == LibClang.CXCursor_TypedefDecl
            push!(wrapped_typedefs, wrap_typedef(c))
        elseif k == LibClang.CXCursor_FunctionDecl
            push!(wrapped_functions[filename], wrap_function(c))
        end
    end

    # Resolve conflicts between overloads on structs and top-level functions
    deoverload!(vcat(values(wrapped_functions)...))
    for s in wrapped_structs
        deoverload!(s.methods)
    end
    
    out_header = "cimgui_te.h"
    out_source = "cimgui_te.cpp"

    # Write header file
    open(out_header; write=true) do f
        write(f, """
        #ifndef CIMGUI_TEST_ENGINE
        #define CIMGUI_TEST_ENGINE

        #include "cimgui.h"

        #if defined _WIN32 || defined __CYGWIN__
            #ifdef CIMGUI_NO_EXPORT
                #define API
            #else
                #define API __declspec(dllexport)
            #endif
        #else
            #ifdef __GNUC__
                #define API  __attribute__((__visibility__("default")))
            #else
                #define API
            #endif
        #endif

        #if defined __cplusplus
            #define EXTERN extern "C"
        #else
            #include <stdarg.h>
            #include <stdbool.h>
            #define EXTERN extern
        #endif

        #define CIMGUI_TE_API EXTERN API

        // Manually copied from imgui_te_engine.h
        #define ImFuncPtr(FUNC_TYPE) FUNC_TYPE*

        #ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS

        """)

        write(f, "// Forward declarations\n")
        for s in wrapped_structs
            write(f, "typedef struct $(s.name) $(s.name);\n")
        end
        write(f, "\n")

        write(f, "// Typedefs\n")
        for t in wrapped_typedefs
            write(f, t, ";\n")
        end
        write(f, "\n")

        for e in wrapped_enums
            if !isnothing(e.comment)
                write(f, e.comment, "\n")
            end
            write(f, e.implementation, ";\n\n")
        end

        for s in wrapped_structs
            if !isnothing(s.comment)
                write(f, s.comment, "\n")
            end
            write(f, s.implementation, "\n")
        end

        write(f, """
        #endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

        #ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS

        """)
        for (cxx_name, c_name) in generated_templates
            write(f, "typedef $(cxx_name) $(c_name);\n")
        end
        write(f, "\n#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS\n\n")

        for (header, funcs) in wrapped_functions
            if isempty(funcs)
                continue
            end

            write(f, "/** Header file: $(header) **/\n")
            for x in funcs
                if !isnothing(x.comment)
                    write(f, x.comment, "\n")
                end
                write(f, "CIMGUI_TE_API ", signature(x), ";\n")
            end
            write(f, "\n")
        end

        for s in wrapped_structs
            if isempty(s.methods)
                continue
            end

            write(f, "/* $(s.name) */\n")
            for m in s.methods
                if !isnothing(m.comment)
                    write(f, m.comment, "\n")
                end
                write(f, "CIMGUI_TE_API ", signature(m), ";\n")
            end
            write(f, "\n")
        end

        write(f, "#endif // CIMGUI_TEST_ENGINE")
    end

    # Write source file
    open(out_source; write=true) do f
        write(f, """
        #include "imgui_te_context.h"
        #include "imgui_te_engine.h"
        #include "imgui_te_coroutine.h"
        #include "imgui_te_internal.h"
        #include "imgui_te_perftool.h"
        #include "imgui_capture_tool.h"
        #include "imgui_te_exporters.h"
        #include "imgui_te_ui.h"
        #include "imgui_te_utils.h"

        #include "cimgui_te.h"

        """)

        for (header, funcs) in wrapped_functions
            if isempty(funcs)
                continue
            end

            write(f, "// $(header)\n")
            for x in funcs
                write(f, "CIMGUI_TE_API ", implementation(x), "\n")
            end
        end

        for s in wrapped_structs
            for m in s.methods
                write(f, "CIMGUI_TE_API ", implementation(m), "\n")
            end
        end
    end

    # Format source file
    clang_format = joinpath(Clang_jll.artifact_dir, "tools", "clang-format")
    style = "{BasedOnStyle: llvm, IndentWidth: 4, PointerAlignment: Left, ColumnLimit: 120, SortIncludes: false}"
    Clang_jll.clang() do _
        run(`$(clang_format) --style=$(style) -i $(out_source)`)
    end

    # Write definitions.json
    definitions = Dict()
    all_funcs = CxxFunction[]
    for funcs in values(wrapped_functions)
        append!(all_funcs, funcs)
    end
    for s in wrapped_structs
        append!(all_funcs, s.methods)
    end
    
    for x in all_funcs
        func_dict = Dict("stname" => x.stname,
                         "ret" => x.ret,
                         "retref" => x.retref,
                         "argsT" => x.argsT,
                         "args" => x.args,                                         
                         "defaults" => x.defaults,
                         "isvararg" => x.isvararg,
                         "funcname" => x.funcname,
                         "cimguiname" => x.cimguiname,
                         "ov_cimguiname" => x.ov_cimguiname,
                         "location" => x.location)
        if !isnothing(x.comment)
            func_dict["comment"] = x.comment
        end
        if x.constructor
            func_dict["constructor"] = true
        end
        if x.destructor
            func_dict["destructor"] = true
        end

        if !haskey(definitions, x.cimguiname)
            definitions[x.cimguiname] = [func_dict]
        else
            push!(definitions[x.cimguiname], func_dict)
        end
    end

    open("definitions.json"; write=true) do f
        JSON3.pretty(f, definitions)
    end

    # Write structs_and_enums.json
    structs_and_enums = Dict("enums" => Dict(),
                             "structs" => Dict(),
                             "locations" => Dict(),
                             "enum_comments" => Dict(),
                             "struct_comments" => Dict())
    for e in wrapped_enums
        structs_and_enums["enums"][e.name] = e.constants
        structs_and_enums["locations"][e.name] = e.location

        if !isnothing(e.comment)
            structs_and_enums["enum_comments"][e.name] = Dict("above" => e.comment)
        end
    end
    for s in wrapped_structs
        structs_and_enums["structs"][s.name] = s.fields
        structs_and_enums["locations"][s.name] = s.location

        if !isnothing(s.comment)
            structs_and_enums["struct_comments"][s.name] = Dict("above" => s.comment)
        end
    end

    open("structs_and_enums.json"; write=true) do f
        JSON3.pretty(f, structs_and_enums)
    end

    nothing
end

# Run automatically if the script is launched from the command-line
if !isempty(Base.PROGRAM_FILE)
    generate()
end
