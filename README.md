# cimgui_test_engine
This repo contains a generator to create C bindings for the
[imgui_test_engine](https://github.com/ocornut/imgui_test_engine). It's very
much inspired by [cimgui](https://github.com/cimgui/cimgui) and is designed to
be used in combination with cimgui.

The output files in this repo were generated for **Dear ImGui 1.92.5**.

## Using the output files
Unlike ImGui the `imgui_test_engine` symbols are spread across multiple files, but
for the sake of simplicity these are all combined into single header and
source files:
- `cimgui_te.h`
- `cimgui_te.c`

Have a look at the `Makefile` to see how to compile it into a shared
library. There is also an `example.c` program that can be built with `make
example` to show how to compile a binary that uses the C API. As with cimgui,
define `CIMGUI_DEFINE_ENUMS_AND_STRUCTS` to enable the C API. The
`IMGUI_TEST_ENGINE_ENABLE_COROUTINE_STDTHREAD_IMPL` directive is copied over
from the upstream headers so you can use that to enable/disable the
`std::thread` coroutine implementation.

In addition, symbol metadata is saved in files that mirror their counterparts in
cimgui:
- [`definitions.json`](https://github.com/cimgui/cimgui?tab=readme-ov-file#definitions-description)
- [`structs_and_enums.json`](https://github.com/cimgui/cimgui?tab=readme-ov-file#structs_and_enums-description)

Some metadata may be missing. If you spot anything missing or different that's
causing problems, feel free to open an issue and we'll see if it can be
fixed. If you're generating bindings using these files make
sure that the symbols from `imgui_te_internal.h` are not exposed (or have
adequately intimidating docstrings).

## Using the generator
The generator is written from scratch in Julia. It uses
[libclang](https://clang.llvm.org/docs/LibClang.html) through
[Clang.jl](https://juliainterop.github.io/Clang.jl) to parse the C++ headers
into an AST, and then visits the nodes in the AST to generate C code for
them.

To run the generator:
1. Install Julia: https://julialang.org/install/
2. Instantiate the project to install all dependencies: `julia --project -e 'import Pkg; Pkg.instantiate()'`
3. Run the generator script: `julia --project generate_bindings.jl`

If you want to generate bindings for different versions just update the `cimgui`
and `imgui_test_engine` submodules first.
