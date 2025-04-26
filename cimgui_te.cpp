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

// imgui_te_internal.h
CIMGUI_TE_API ImGuiTestItemInfo* cImGuiTestEngine_FindItemInfo(ImGuiTestEngine* engine, unsigned int id,
                                                               const char* debug_id) {
    return ImGuiTestEngine_FindItemInfo(engine, id, debug_id);
}

CIMGUI_TE_API void cImGuiTestEngine_Yield(ImGuiTestEngine* engine) { ImGuiTestEngine_Yield(engine); }

CIMGUI_TE_API void cImGuiTestEngine_SetDeltaTime(ImGuiTestEngine* engine, float delta_time) {
    ImGuiTestEngine_SetDeltaTime(engine, delta_time);
}

CIMGUI_TE_API int cImGuiTestEngine_GetFrameCount(ImGuiTestEngine* engine) {
    return ImGuiTestEngine_GetFrameCount(engine);
}

CIMGUI_TE_API bool cImGuiTestEngine_PassFilter(ImGuiTest* test, const char* filter) {
    return ImGuiTestEngine_PassFilter(test, filter);
}

CIMGUI_TE_API void cImGuiTestEngine_RunTest(ImGuiTestEngine* engine, ImGuiTestContext* ctx, ImGuiTest* test,
                                            int run_flags) {
    ImGuiTestEngine_RunTest(engine, ctx, test, run_flags);
}

CIMGUI_TE_API void cImGuiTestEngine_BindImGuiContext(ImGuiTestEngine* engine, ImGuiContext* ui_ctx) {
    ImGuiTestEngine_BindImGuiContext(engine, ui_ctx);
}

CIMGUI_TE_API void cImGuiTestEngine_UnbindImGuiContext(ImGuiTestEngine* engine, ImGuiContext* ui_ctx) {
    ImGuiTestEngine_UnbindImGuiContext(engine, ui_ctx);
}

CIMGUI_TE_API void cImGuiTestEngine_RebootUiContext(ImGuiTestEngine* engine) {
    ImGuiTestEngine_RebootUiContext(engine);
}

CIMGUI_TE_API ImGuiPerfTool* cImGuiTestEngine_GetPerfTool(ImGuiTestEngine* engine) {
    return ImGuiTestEngine_GetPerfTool(engine);
}

CIMGUI_TE_API void cImGuiTestEngine_UpdateTestsSourceLines(ImGuiTestEngine* engine) {
    ImGuiTestEngine_UpdateTestsSourceLines(engine);
}

CIMGUI_TE_API bool cImGuiTestEngine_CaptureScreenshot(ImGuiTestEngine* engine, ImGuiCaptureArgs* args) {
    return ImGuiTestEngine_CaptureScreenshot(engine, args);
}

CIMGUI_TE_API bool cImGuiTestEngine_CaptureBeginVideo(ImGuiTestEngine* engine, ImGuiCaptureArgs* args) {
    return ImGuiTestEngine_CaptureBeginVideo(engine, args);
}

CIMGUI_TE_API bool cImGuiTestEngine_CaptureEndVideo(ImGuiTestEngine* engine, ImGuiCaptureArgs* args) {
    return ImGuiTestEngine_CaptureEndVideo(engine, args);
}

CIMGUI_TE_API const char* cImGuiTestEngine_GetStatusName(ImGuiTestStatus v) { return ImGuiTestEngine_GetStatusName(v); }

CIMGUI_TE_API const char* cImGuiTestEngine_GetRunSpeedName(ImGuiTestRunSpeed v) {
    return ImGuiTestEngine_GetRunSpeedName(v);
}

CIMGUI_TE_API const char* cImGuiTestEngine_GetVerboseLevelName(ImGuiTestVerboseLevel v) {
    return ImGuiTestEngine_GetVerboseLevelName(v);
}

// imgui_te_utils.h
CIMGUI_TE_API ImGuiID cImHashDecoratedPath(const char* str, const char* str_end, unsigned int seed) {
    return ImHashDecoratedPath(str, str_end, seed);
}

CIMGUI_TE_API const char* cImFindNextDecoratedPartInPath(const char* str, const char* str_end) {
    return ImFindNextDecoratedPartInPath(str, str_end);
}

CIMGUI_TE_API bool cImFileExist(const char* filename) { return ImFileExist(filename); }

CIMGUI_TE_API bool cImFileDelete(const char* filename) { return ImFileDelete(filename); }

CIMGUI_TE_API bool cImFileCreateDirectoryChain(const char* path, const char* path_end) {
    return ImFileCreateDirectoryChain(path, path_end);
}

CIMGUI_TE_API bool cImFileFindInParents(const char* sub_path, int max_parent_count, Str* output) {
    return ImFileFindInParents(sub_path, max_parent_count, output);
}

CIMGUI_TE_API bool cImFileLoadSourceBlurb(const char* filename, int line_no_start, int line_no_end,
                                          ImGuiTextBuffer* out_buf) {
    return ImFileLoadSourceBlurb(filename, line_no_start, line_no_end, out_buf);
}

CIMGUI_TE_API const char* cImPathFindFilename(const char* path, const char* path_end) {
    return ImPathFindFilename(path, path_end);
}

CIMGUI_TE_API const char* cImPathFindExtension(const char* path, const char* path_end) {
    return ImPathFindExtension(path, path_end);
}

CIMGUI_TE_API void cImPathFixSeparatorsForCurrentOS(char* buf) { ImPathFixSeparatorsForCurrentOS(buf); }

CIMGUI_TE_API void cImStrReplace(Str* s, const char* find, const char* repl) { ImStrReplace(s, find, repl); }

CIMGUI_TE_API const char* cImStrchrRangeWithEscaping(const char* str, const char* str_end, char find_c) {
    return ImStrchrRangeWithEscaping(str, str_end, find_c);
}

CIMGUI_TE_API void cImStrXmlEscape(Str* s) { ImStrXmlEscape(s); }

CIMGUI_TE_API int cImStrBase64Encode(const unsigned char* src, char* dst, int length) {
    return ImStrBase64Encode(src, dst, length);
}

CIMGUI_TE_API void cImParseExtractArgcArgvFromCommandLine(int* out_argc, const char*** out_argv, const char* cmd_line) {
    ImParseExtractArgcArgvFromCommandLine(out_argc, out_argv, cmd_line);
}

CIMGUI_TE_API bool cImParseFindIniSection(const char* ini_config, const char* header, ImVector_char* result) {
    return ImParseFindIniSection(ini_config, header, result);
}

CIMGUI_TE_API uint64_t cImTimeGetInMicroseconds() { return ImTimeGetInMicroseconds(); }

CIMGUI_TE_API void cImTimestampToISO8601(unsigned long timestamp, Str* out_date) {
    ImTimestampToISO8601(timestamp, out_date);
}

CIMGUI_TE_API void cImThreadSleepInMilliseconds(int ms) { ImThreadSleepInMilliseconds(ms); }

CIMGUI_TE_API void cImThreadSetCurrentThreadDescription(const char* description) {
    ImThreadSetCurrentThreadDescription(description);
}

CIMGUI_TE_API const ImBuildInfo* cImBuildGetCompilationInfo() { return ImBuildGetCompilationInfo(); }

CIMGUI_TE_API bool cImBuildFindGitBranchName(const char* git_repo_path, Str* branch_name) {
    return ImBuildFindGitBranchName(git_repo_path, branch_name);
}

CIMGUI_TE_API bool cImOsCreateProcess(const char* cmd_line) { return ImOsCreateProcess(cmd_line); }

CIMGUI_TE_API FILE* cImOsPOpen(const char* cmd_line, const char* mode) { return ImOsPOpen(cmd_line, mode); }

CIMGUI_TE_API void cImOsPClose(FILE* fp) { ImOsPClose(fp); }

CIMGUI_TE_API void cImOsOpenInShell(const char* path) { ImOsOpenInShell(path); }

CIMGUI_TE_API bool cImOsIsDebuggerPresent() { return ImOsIsDebuggerPresent(); }

CIMGUI_TE_API void cImOsOutputDebugString(const char* message) { ImOsOutputDebugString(message); }

CIMGUI_TE_API void cImOsConsoleSetTextColor(ImOsConsoleStream stream, ImOsConsoleTextColor color) {
    ImOsConsoleSetTextColor(stream, color);
}

CIMGUI_TE_API ImGuiID cTableGetHeaderID_Str(ImGuiTable* table, const char* column, int instance_no) {
    return TableGetHeaderID(table, column, instance_no);
}

CIMGUI_TE_API ImGuiID cTableGetHeaderID_int(ImGuiTable* table, int column_n, int instance_no) {
    return TableGetHeaderID(table, column_n, instance_no);
}

CIMGUI_TE_API void cTableDiscardInstanceAndSettings(unsigned int table_id) {
    TableDiscardInstanceAndSettings(table_id);
}

CIMGUI_TE_API void cDrawDataVerifyMatchingBufferCount(ImDrawData* draw_data) {
    DrawDataVerifyMatchingBufferCount(draw_data);
}

// imgui_te_exporters.h
CIMGUI_TE_API void cImGuiTestEngine_PrintResultSummary(ImGuiTestEngine* engine) {
    ImGuiTestEngine_PrintResultSummary(engine);
}

CIMGUI_TE_API void cImGuiTestEngine_Export(ImGuiTestEngine* engine) { ImGuiTestEngine_Export(engine); }

CIMGUI_TE_API void cImGuiTestEngine_ExportEx(ImGuiTestEngine* engine, ImGuiTestEngineExportFormat format,
                                             const char* filename) {
    ImGuiTestEngine_ExportEx(engine, format, filename);
}

// imgui_te_ui.h
CIMGUI_TE_API void cImGuiTestEngine_ShowTestEngineWindows(ImGuiTestEngine* engine, bool* p_open) {
    ImGuiTestEngine_ShowTestEngineWindows(engine, p_open);
}

CIMGUI_TE_API void cImGuiTestEngine_OpenSourceFile(ImGuiTestEngine* engine, const char* source_filename,
                                                   int source_line_no) {
    ImGuiTestEngine_OpenSourceFile(engine, source_filename, source_line_no);
}

// imgui_te_engine.h
CIMGUI_TE_API void cImGuiTestEngineHook_ItemAdd(ImGuiContext* ui_ctx, unsigned int id, const ImRect* bb,
                                                const ImGuiLastItemData* item_data) {
    ImGuiTestEngineHook_ItemAdd(ui_ctx, id, *bb, item_data);
}

CIMGUI_TE_API void cImGuiTestEngineHook_ItemInfo(ImGuiContext* ui_ctx, unsigned int id, const char* label, int flags) {
    ImGuiTestEngineHook_ItemInfo(ui_ctx, id, label, flags);
}

CIMGUI_TE_API void cImGuiTestEngineHook_Log(ImGuiContext* ui_ctx, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ImGuiTestEngineHook_Log(ui_ctx, fmt, args);
    va_end(args);
}

CIMGUI_TE_API const char* cImGuiTestEngine_FindItemDebugLabel(ImGuiContext* ui_ctx, unsigned int id) {
    return ImGuiTestEngine_FindItemDebugLabel(ui_ctx, id);
}

CIMGUI_TE_API bool cImGuiTestEngine_Check(const char* file, const char* func, int line, int flags, bool result,
                                          const char* expr) {
    return ImGuiTestEngine_Check(file, func, line, flags, result, expr);
}

CIMGUI_TE_API bool cImGuiTestEngine_CheckStrOp(const char* file, const char* func, int line, int flags, const char* op,
                                               const char* lhs_var, const char* lhs_value, const char* rhs_var,
                                               const char* rhs_value, bool* out_result) {
    return ImGuiTestEngine_CheckStrOp(file, func, line, flags, op, lhs_var, lhs_value, rhs_var, rhs_value, out_result);
}

CIMGUI_TE_API bool cImGuiTestEngine_Error(const char* file, const char* func, int line, int flags, const char* fmt,
                                          ...) {
    va_list args;
    va_start(args, fmt);
    bool ret = ImGuiTestEngine_Error(file, func, line, flags, fmt, args);
    va_end(args);
    return ret;
}

CIMGUI_TE_API void cImGuiTestEngine_AssertLog(const char* expr, const char* file, const char* function, int line) {
    ImGuiTestEngine_AssertLog(expr, file, function, line);
}

CIMGUI_TE_API ImGuiTextBuffer* cImGuiTestEngine_GetTempStringBuilder() {
    return ImGuiTestEngine_GetTempStringBuilder();
}

CIMGUI_TE_API ImGuiTestEngine* cImGuiTestEngine_CreateContext() { return ImGuiTestEngine_CreateContext(); }

CIMGUI_TE_API void cImGuiTestEngine_DestroyContext(ImGuiTestEngine* engine) { ImGuiTestEngine_DestroyContext(engine); }

CIMGUI_TE_API void cImGuiTestEngine_Start(ImGuiTestEngine* engine, ImGuiContext* ui_ctx) {
    ImGuiTestEngine_Start(engine, ui_ctx);
}

CIMGUI_TE_API void cImGuiTestEngine_Stop(ImGuiTestEngine* engine) { ImGuiTestEngine_Stop(engine); }

CIMGUI_TE_API void cImGuiTestEngine_PostSwap(ImGuiTestEngine* engine) { ImGuiTestEngine_PostSwap(engine); }

CIMGUI_TE_API ImGuiTestEngineIO* cImGuiTestEngine_GetIO(ImGuiTestEngine* engine) {
    return &(ImGuiTestEngine_GetIO(engine));
}

CIMGUI_TE_API ImGuiTest* cImGuiTestEngine_RegisterTest(ImGuiTestEngine* engine, const char* category, const char* name,
                                                       const char* src_file, int src_line) {
    return ImGuiTestEngine_RegisterTest(engine, category, name, src_file, src_line);
}

CIMGUI_TE_API void cImGuiTestEngine_UnregisterTest(ImGuiTestEngine* engine, ImGuiTest* test) {
    ImGuiTestEngine_UnregisterTest(engine, test);
}

CIMGUI_TE_API void cImGuiTestEngine_UnregisterAllTests(ImGuiTestEngine* engine) {
    ImGuiTestEngine_UnregisterAllTests(engine);
}

CIMGUI_TE_API void cImGuiTestEngine_QueueTest(ImGuiTestEngine* engine, ImGuiTest* test, int run_flags) {
    ImGuiTestEngine_QueueTest(engine, test, run_flags);
}

CIMGUI_TE_API void cImGuiTestEngine_QueueTests(ImGuiTestEngine* engine, ImGuiTestGroup group, const char* filter,
                                               int run_flags) {
    ImGuiTestEngine_QueueTests(engine, group, filter, run_flags);
}

CIMGUI_TE_API bool cImGuiTestEngine_TryAbortEngine(ImGuiTestEngine* engine) {
    return ImGuiTestEngine_TryAbortEngine(engine);
}

CIMGUI_TE_API void cImGuiTestEngine_AbortCurrentTest(ImGuiTestEngine* engine) {
    ImGuiTestEngine_AbortCurrentTest(engine);
}

CIMGUI_TE_API ImGuiTest* cImGuiTestEngine_FindTestByName(ImGuiTestEngine* engine, const char* category,
                                                         const char* name) {
    return ImGuiTestEngine_FindTestByName(engine, category, name);
}

CIMGUI_TE_API bool cImGuiTestEngine_IsTestQueueEmpty(ImGuiTestEngine* engine) {
    return ImGuiTestEngine_IsTestQueueEmpty(engine);
}

CIMGUI_TE_API bool cImGuiTestEngine_IsUsingSimulatedInputs(ImGuiTestEngine* engine) {
    return ImGuiTestEngine_IsUsingSimulatedInputs(engine);
}

CIMGUI_TE_API void cImGuiTestEngine_GetResult(ImGuiTestEngine* engine, int* count_tested, int* success_count) {
    ImGuiTestEngine_GetResult(engine, *count_tested, *success_count);
}

CIMGUI_TE_API void cImGuiTestEngine_GetTestList(ImGuiTestEngine* engine, ImVector_ImGuiTest_Ptr* out_tests) {
    ImGuiTestEngine_GetTestList(engine, out_tests);
}

CIMGUI_TE_API void cImGuiTestEngine_GetTestQueue(ImGuiTestEngine* engine, ImVector_ImGuiTestRunTask* out_tests) {
    ImGuiTestEngine_GetTestQueue(engine, out_tests);
}

CIMGUI_TE_API void cImGuiTestEngine_InstallDefaultCrashHandler() { ImGuiTestEngine_InstallDefaultCrashHandler(); }

CIMGUI_TE_API void cImGuiTestEngine_CrashHandler() { ImGuiTestEngine_CrashHandler(); }

// imgui_te_perftool.h
CIMGUI_TE_API void cImGuiTestEngine_PerfToolAppendToCSV(ImGuiPerfTool* perf_log, ImGuiPerfToolEntry* entry,
                                                        const char* filename) {
    ImGuiTestEngine_PerfToolAppendToCSV(perf_log, entry, filename);
}

// imgui_te_coroutine.h
CIMGUI_TE_API ImGuiTestCoroutineInterface* cCoroutine_ImplStdThread_GetInterface() {
    return Coroutine_ImplStdThread_GetInterface();
}

CIMGUI_TE_API ImGuiCaptureImageBuf* ImGuiCaptureImageBuf_ImGuiCaptureImageBuf() {
    return IM_NEW(ImGuiCaptureImageBuf)();
}

CIMGUI_TE_API void ImGuiCaptureImageBuf_destroy(ImGuiCaptureImageBuf* self) { IM_DELETE(self); }

CIMGUI_TE_API void ImGuiCaptureImageBuf_Clear(ImGuiCaptureImageBuf* self) { self->Clear(); }

CIMGUI_TE_API void ImGuiCaptureImageBuf_CreateEmpty(ImGuiCaptureImageBuf* self, int w, int h) {
    self->CreateEmpty(w, h);
}

CIMGUI_TE_API bool ImGuiCaptureImageBuf_SaveFile(ImGuiCaptureImageBuf* self, const char* filename) {
    return self->SaveFile(filename);
}

CIMGUI_TE_API void ImGuiCaptureImageBuf_RemoveAlpha(ImGuiCaptureImageBuf* self) { self->RemoveAlpha(); }

CIMGUI_TE_API ImGuiCaptureContext* ImGuiCaptureContext_ImGuiCaptureContext(ImGuiScreenCaptureFunc* capture_func) {
    return IM_NEW(ImGuiCaptureContext)(capture_func);
}

CIMGUI_TE_API void ImGuiCaptureContext_PreNewFrame(ImGuiCaptureContext* self) { self->PreNewFrame(); }

CIMGUI_TE_API void ImGuiCaptureContext_PreRender(ImGuiCaptureContext* self) { self->PreRender(); }

CIMGUI_TE_API void ImGuiCaptureContext_PostRender(ImGuiCaptureContext* self) { self->PostRender(); }

CIMGUI_TE_API ImGuiCaptureStatus ImGuiCaptureContext_CaptureUpdate(ImGuiCaptureContext* self, ImGuiCaptureArgs* args) {
    return self->CaptureUpdate(args);
}

CIMGUI_TE_API void ImGuiCaptureContext_RestoreBackedUpData(ImGuiCaptureContext* self) { self->RestoreBackedUpData(); }

CIMGUI_TE_API void ImGuiCaptureContext_ClearState(ImGuiCaptureContext* self) { self->ClearState(); }

CIMGUI_TE_API void ImGuiCaptureContext_BeginVideoCapture(ImGuiCaptureContext* self, ImGuiCaptureArgs* args) {
    self->BeginVideoCapture(args);
}

CIMGUI_TE_API void ImGuiCaptureContext_EndVideoCapture(ImGuiCaptureContext* self) { self->EndVideoCapture(); }

CIMGUI_TE_API bool ImGuiCaptureContext_IsCapturingVideo(ImGuiCaptureContext* self) { return self->IsCapturingVideo(); }

CIMGUI_TE_API bool ImGuiCaptureContext_IsCapturing(ImGuiCaptureContext* self) { return self->IsCapturing(); }

CIMGUI_TE_API ImGuiCaptureToolUI* ImGuiCaptureToolUI_ImGuiCaptureToolUI() { return IM_NEW(ImGuiCaptureToolUI)(); }

CIMGUI_TE_API void ImGuiCaptureToolUI_ShowCaptureToolWindow(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context,
                                                            bool* p_open) {
    self->ShowCaptureToolWindow(context, p_open);
}

CIMGUI_TE_API void ImGuiCaptureToolUI__CaptureWindowPicker(ImGuiCaptureToolUI* self, ImGuiCaptureArgs* args) {
    self->_CaptureWindowPicker(args);
}

CIMGUI_TE_API void ImGuiCaptureToolUI__CaptureWindowsSelector(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context,
                                                              ImGuiCaptureArgs* args) {
    self->_CaptureWindowsSelector(context, args);
}

CIMGUI_TE_API void ImGuiCaptureToolUI__SnapWindowsToGrid(ImGuiCaptureToolUI* self, float cell_size) {
    self->_SnapWindowsToGrid(cell_size);
}

CIMGUI_TE_API bool ImGuiCaptureToolUI__InitializeOutputFile(ImGuiCaptureToolUI* self) {
    return self->_InitializeOutputFile();
}

CIMGUI_TE_API bool ImGuiCaptureToolUI__ShowEncoderConfigFields(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context) {
    return self->_ShowEncoderConfigFields(context);
}

CIMGUI_TE_API ImGuiTestItemInfo* ImGuiTestItemInfo_ImGuiTestItemInfo() { return IM_NEW(ImGuiTestItemInfo)(); }

CIMGUI_TE_API void ImGuiTestItemList_Clear(ImGuiTestItemList* self) { self->Clear(); }

CIMGUI_TE_API void ImGuiTestItemList_Reserve(ImGuiTestItemList* self, int capacity) { self->Reserve(capacity); }

CIMGUI_TE_API int ImGuiTestItemList_GetSize(ImGuiTestItemList* self) { return self->GetSize(); }

CIMGUI_TE_API const ImGuiTestItemInfo* ImGuiTestItemList_GetByIndex(ImGuiTestItemList* self, int n) {
    return self->GetByIndex(n);
}

CIMGUI_TE_API const ImGuiTestItemInfo* ImGuiTestItemList_GetByID(ImGuiTestItemList* self, unsigned int id) {
    return self->GetByID(id);
}

CIMGUI_TE_API size_t ImGuiTestItemList_size(ImGuiTestItemList* self) { return self->size(); }

CIMGUI_TE_API const ImGuiTestItemInfo* ImGuiTestItemList_begin(ImGuiTestItemList* self) { return self->begin(); }

CIMGUI_TE_API const ImGuiTestItemInfo* ImGuiTestItemList_end(ImGuiTestItemList* self) { return self->end(); }

CIMGUI_TE_API ImGuiTestLog* ImGuiTestLog_ImGuiTestLog() { return IM_NEW(ImGuiTestLog)(); }

CIMGUI_TE_API bool ImGuiTestLog_IsEmpty(ImGuiTestLog* self) { return self->IsEmpty(); }

CIMGUI_TE_API void ImGuiTestLog_Clear(ImGuiTestLog* self) { self->Clear(); }

CIMGUI_TE_API int ImGuiTestLog_ExtractLinesForVerboseLevels(ImGuiTestLog* self, ImGuiTestVerboseLevel level_min,
                                                            ImGuiTestVerboseLevel level_max,
                                                            ImGuiTextBuffer* out_buffer) {
    return self->ExtractLinesForVerboseLevels(level_min, level_max, out_buffer);
}

CIMGUI_TE_API void ImGuiTestLog_UpdateLineOffsets(ImGuiTestLog* self, ImGuiTestEngineIO* engine_io,
                                                  ImGuiTestVerboseLevel level, const char* start) {
    self->UpdateLineOffsets(engine_io, level, start);
}

CIMGUI_TE_API ImGuiTest* ImGuiTest_ImGuiTest() { return IM_NEW(ImGuiTest)(); }

CIMGUI_TE_API void ImGuiTest_destroy(ImGuiTest* self) { IM_DELETE(self); }

CIMGUI_TE_API void ImGuiTest_SetOwnedName(ImGuiTest* self, const char* name) { self->SetOwnedName(name); }

CIMGUI_TE_API ImGuiTestRef* ImGuiTestRef_ImGuiTestRef() { return IM_NEW(ImGuiTestRef)(); }

CIMGUI_TE_API ImGuiTestRef* ImGuiTestRef_ImGuiTestRef_Uint(unsigned int id) { return IM_NEW(ImGuiTestRef)(id); }

CIMGUI_TE_API ImGuiTestRef* ImGuiTestRef_ImGuiTestRef_Str(const char* path) { return IM_NEW(ImGuiTestRef)(path); }

CIMGUI_TE_API bool ImGuiTestRef_IsEmpty(ImGuiTestRef* self) { return self->IsEmpty(); }

CIMGUI_TE_API const char* ImGuiTestRefDesc_c_str(ImGuiTestRefDesc* self) { return self->c_str(); }

CIMGUI_TE_API ImGuiTestRefDesc* ImGuiTestRefDesc_ImGuiTestRefDesc_constTestRefPtr(const ImGuiTestRef* ref) {
    return IM_NEW(ImGuiTestRefDesc)(*ref);
}

CIMGUI_TE_API ImGuiTestRefDesc*
ImGuiTestRefDesc_ImGuiTestRefDesc_constTestRefPtrconstTestItemInfoPtr(const ImGuiTestRef* ref,
                                                                      const ImGuiTestItemInfo* item) {
    return IM_NEW(ImGuiTestRefDesc)(*ref, *item);
}

CIMGUI_TE_API ImGuiTestActionFilter* ImGuiTestActionFilter_ImGuiTestActionFilter() {
    return IM_NEW(ImGuiTestActionFilter)();
}

CIMGUI_TE_API ImGuiTestGenericItemStatus* ImGuiTestGenericItemStatus_ImGuiTestGenericItemStatus() {
    return IM_NEW(ImGuiTestGenericItemStatus)();
}

CIMGUI_TE_API void ImGuiTestGenericItemStatus_Clear(ImGuiTestGenericItemStatus* self) { self->Clear(); }

CIMGUI_TE_API void ImGuiTestGenericItemStatus_QuerySet(ImGuiTestGenericItemStatus* self, bool ret_val) {
    self->QuerySet(ret_val);
}

CIMGUI_TE_API void ImGuiTestGenericItemStatus_QueryInc(ImGuiTestGenericItemStatus* self, bool ret_val) {
    self->QueryInc(ret_val);
}

CIMGUI_TE_API ImGuiTestGenericVars* ImGuiTestGenericVars_ImGuiTestGenericVars() {
    return IM_NEW(ImGuiTestGenericVars)();
}

CIMGUI_TE_API void ImGuiTestGenericVars_Clear(ImGuiTestGenericVars* self) { self->Clear(); }

CIMGUI_TE_API void ImGuiTestContext_Finish(ImGuiTestContext* self, ImGuiTestStatus status) { self->Finish(status); }

CIMGUI_TE_API ImGuiTestStatus ImGuiTestContext_RunChildTest(ImGuiTestContext* self, const char* test_name, int flags) {
    return self->RunChildTest(test_name, flags);
}

CIMGUI_TE_API bool ImGuiTestContext_IsError(ImGuiTestContext* self) { return self->IsError(); }

CIMGUI_TE_API bool ImGuiTestContext_IsWarmUpGuiFrame(ImGuiTestContext* self) { return self->IsWarmUpGuiFrame(); }

CIMGUI_TE_API bool ImGuiTestContext_IsFirstGuiFrame(ImGuiTestContext* self) { return self->IsFirstGuiFrame(); }

CIMGUI_TE_API bool ImGuiTestContext_IsFirstTestFrame(ImGuiTestContext* self) { return self->IsFirstTestFrame(); }

CIMGUI_TE_API bool ImGuiTestContext_IsGuiFuncOnly(ImGuiTestContext* self) { return self->IsGuiFuncOnly(); }

CIMGUI_TE_API bool ImGuiTestContext_SuspendTestFunc(ImGuiTestContext* self, const char* file, int line) {
    return self->SuspendTestFunc(file, line);
}

CIMGUI_TE_API void ImGuiTestContext_LogEx(ImGuiTestContext* self, ImGuiTestVerboseLevel level, int flags,
                                          const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->LogEx(level, flags, fmt, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_LogExV(ImGuiTestContext* self, ImGuiTestVerboseLevel level, int flags,
                                           const char* fmt, va_list args) {
    self->LogExV(level, flags, fmt, args);
}

CIMGUI_TE_API void ImGuiTestContext_LogToTTY(ImGuiTestContext* self, ImGuiTestVerboseLevel level, const char* message,
                                             const char* message_end) {
    self->LogToTTY(level, message, message_end);
}

CIMGUI_TE_API void ImGuiTestContext_LogToDebugger(ImGuiTestContext* self, ImGuiTestVerboseLevel level,
                                                  const char* message) {
    self->LogToDebugger(level, message);
}

CIMGUI_TE_API void ImGuiTestContext_LogDebug(ImGuiTestContext* self, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->LogDebug(fmt, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_LogInfo(ImGuiTestContext* self, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->LogInfo(fmt, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_LogWarning(ImGuiTestContext* self, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->LogWarning(fmt, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_LogError(ImGuiTestContext* self, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->LogError(fmt, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_LogBasicUiState(ImGuiTestContext* self) { self->LogBasicUiState(); }

CIMGUI_TE_API void ImGuiTestContext_LogItemList(ImGuiTestContext* self, ImGuiTestItemList* list) {
    self->LogItemList(list);
}

CIMGUI_TE_API void ImGuiTestContext_Yield(ImGuiTestContext* self, int count) { self->Yield(count); }

CIMGUI_TE_API void ImGuiTestContext_Sleep(ImGuiTestContext* self, float time_in_second) { self->Sleep(time_in_second); }

CIMGUI_TE_API void ImGuiTestContext_SleepShort(ImGuiTestContext* self) { self->SleepShort(); }

CIMGUI_TE_API void ImGuiTestContext_SleepStandard(ImGuiTestContext* self) { self->SleepStandard(); }

CIMGUI_TE_API void ImGuiTestContext_SleepNoSkip(ImGuiTestContext* self, float time_in_second,
                                                float framestep_in_second) {
    self->SleepNoSkip(time_in_second, framestep_in_second);
}

CIMGUI_TE_API void ImGuiTestContext_SetRef_TestRef(ImGuiTestContext* self, ImGuiTestRef ref) { self->SetRef(ref); }

CIMGUI_TE_API void ImGuiTestContext_SetRef_WindowPtr(ImGuiTestContext* self, ImGuiWindow* window) {
    self->SetRef(window);
}

CIMGUI_TE_API ImGuiTestRef ImGuiTestContext_GetRef(ImGuiTestContext* self) { return self->GetRef(); }

CIMGUI_TE_API ImGuiTestItemInfo ImGuiTestContext_WindowInfo(ImGuiTestContext* self, ImGuiTestRef window_ref,
                                                            int flags) {
    return self->WindowInfo(window_ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_WindowClose(ImGuiTestContext* self, ImGuiTestRef window_ref) {
    self->WindowClose(window_ref);
}

CIMGUI_TE_API void ImGuiTestContext_WindowCollapse(ImGuiTestContext* self, ImGuiTestRef window_ref, bool collapsed) {
    self->WindowCollapse(window_ref, collapsed);
}

CIMGUI_TE_API void ImGuiTestContext_WindowFocus(ImGuiTestContext* self, ImGuiTestRef window_ref, int flags) {
    self->WindowFocus(window_ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_WindowBringToFront(ImGuiTestContext* self, ImGuiTestRef window_ref, int flags) {
    self->WindowBringToFront(window_ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_WindowMove(ImGuiTestContext* self, ImGuiTestRef window_ref, ImVec2 pos,
                                               ImVec2 pivot, int flags) {
    self->WindowMove(window_ref, pos, pivot, flags);
}

CIMGUI_TE_API void ImGuiTestContext_WindowResize(ImGuiTestContext* self, ImGuiTestRef window_ref, ImVec2 sz) {
    self->WindowResize(window_ref, sz);
}

CIMGUI_TE_API bool ImGuiTestContext_WindowTeleportToMakePosVisible(ImGuiTestContext* self, ImGuiTestRef window_ref,
                                                                   ImVec2 pos_in_window) {
    return self->WindowTeleportToMakePosVisible(window_ref, pos_in_window);
}

CIMGUI_TE_API ImGuiWindow* ImGuiTestContext_GetWindowByRef(ImGuiTestContext* self, ImGuiTestRef window_ref) {
    return self->GetWindowByRef(window_ref);
}

CIMGUI_TE_API void ImGuiTestContext_PopupCloseOne(ImGuiTestContext* self) { self->PopupCloseOne(); }

CIMGUI_TE_API void ImGuiTestContext_PopupCloseAll(ImGuiTestContext* self) { self->PopupCloseAll(); }

CIMGUI_TE_API ImGuiID ImGuiTestContext_PopupGetWindowID(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->PopupGetWindowID(ref);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetID_TestRef(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->GetID(ref);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetID_TestRefTestRef(ImGuiTestContext* self, ImGuiTestRef ref,
                                                            ImGuiTestRef seed_ref) {
    return self->GetID(ref, seed_ref);
}

CIMGUI_TE_API ImVec2 ImGuiTestContext_GetPosOnVoid(ImGuiTestContext* self, ImGuiViewport* viewport) {
    return self->GetPosOnVoid(viewport);
}

CIMGUI_TE_API ImVec2 ImGuiTestContext_GetWindowTitlebarPoint(ImGuiTestContext* self, ImGuiTestRef window_ref) {
    return self->GetWindowTitlebarPoint(window_ref);
}

CIMGUI_TE_API ImVec2 ImGuiTestContext_GetMainMonitorWorkPos(ImGuiTestContext* self) {
    return self->GetMainMonitorWorkPos();
}

CIMGUI_TE_API ImVec2 ImGuiTestContext_GetMainMonitorWorkSize(ImGuiTestContext* self) {
    return self->GetMainMonitorWorkSize();
}

CIMGUI_TE_API void ImGuiTestContext_CaptureReset(ImGuiTestContext* self) { self->CaptureReset(); }

CIMGUI_TE_API void ImGuiTestContext_CaptureSetExtension(ImGuiTestContext* self, const char* ext) {
    self->CaptureSetExtension(ext);
}

CIMGUI_TE_API bool ImGuiTestContext_CaptureAddWindow(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->CaptureAddWindow(ref);
}

CIMGUI_TE_API void ImGuiTestContext_CaptureScreenshotWindow(ImGuiTestContext* self, ImGuiTestRef ref,
                                                            int capture_flags) {
    self->CaptureScreenshotWindow(ref, capture_flags);
}

CIMGUI_TE_API bool ImGuiTestContext_CaptureScreenshot(ImGuiTestContext* self, int capture_flags) {
    return self->CaptureScreenshot(capture_flags);
}

CIMGUI_TE_API bool ImGuiTestContext_CaptureBeginVideo(ImGuiTestContext* self) { return self->CaptureBeginVideo(); }

CIMGUI_TE_API bool ImGuiTestContext_CaptureEndVideo(ImGuiTestContext* self) { return self->CaptureEndVideo(); }

CIMGUI_TE_API void ImGuiTestContext_MouseMove(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->MouseMove(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_MouseMoveToPos(ImGuiTestContext* self, ImVec2 pos) { self->MouseMoveToPos(pos); }

CIMGUI_TE_API void ImGuiTestContext_MouseTeleportToPos(ImGuiTestContext* self, ImVec2 pos, int flags) {
    self->MouseTeleportToPos(pos, flags);
}

CIMGUI_TE_API void ImGuiTestContext_MouseClick(ImGuiTestContext* self, int button) { self->MouseClick(button); }

CIMGUI_TE_API void ImGuiTestContext_MouseClickMulti(ImGuiTestContext* self, int button, int count) {
    self->MouseClickMulti(button, count);
}

CIMGUI_TE_API void ImGuiTestContext_MouseDoubleClick(ImGuiTestContext* self, int button) {
    self->MouseDoubleClick(button);
}

CIMGUI_TE_API void ImGuiTestContext_MouseDown(ImGuiTestContext* self, int button) { self->MouseDown(button); }

CIMGUI_TE_API void ImGuiTestContext_MouseUp(ImGuiTestContext* self, int button) { self->MouseUp(button); }

CIMGUI_TE_API void ImGuiTestContext_MouseLiftDragThreshold(ImGuiTestContext* self, int button) {
    self->MouseLiftDragThreshold(button);
}

CIMGUI_TE_API void ImGuiTestContext_MouseDragWithDelta(ImGuiTestContext* self, ImVec2 delta, int button) {
    self->MouseDragWithDelta(delta, button);
}

CIMGUI_TE_API void ImGuiTestContext_MouseWheel(ImGuiTestContext* self, ImVec2 delta) { self->MouseWheel(delta); }

CIMGUI_TE_API void ImGuiTestContext_MouseWheelX(ImGuiTestContext* self, float dx) { self->MouseWheelX(dx); }

CIMGUI_TE_API void ImGuiTestContext_MouseWheelY(ImGuiTestContext* self, float dy) { self->MouseWheelY(dy); }

CIMGUI_TE_API void ImGuiTestContext_MouseMoveToVoid(ImGuiTestContext* self, ImGuiViewport* viewport) {
    self->MouseMoveToVoid(viewport);
}

CIMGUI_TE_API void ImGuiTestContext_MouseClickOnVoid(ImGuiTestContext* self, int button, ImGuiViewport* viewport) {
    self->MouseClickOnVoid(button, viewport);
}

CIMGUI_TE_API ImGuiWindow* ImGuiTestContext_FindHoveredWindowAtPos(ImGuiTestContext* self, const ImVec2* pos) {
    return self->FindHoveredWindowAtPos(*pos);
}

CIMGUI_TE_API bool ImGuiTestContext_FindExistingVoidPosOnViewport(ImGuiTestContext* self, ImGuiViewport* viewport,
                                                                  ImVec2* out) {
    return self->FindExistingVoidPosOnViewport(viewport, out);
}

CIMGUI_TE_API void ImGuiTestContext_MouseSetViewport(ImGuiTestContext* self, ImGuiWindow* window) {
    self->MouseSetViewport(window);
}

CIMGUI_TE_API void ImGuiTestContext_MouseSetViewportID(ImGuiTestContext* self, unsigned int viewport_id) {
    self->MouseSetViewportID(viewport_id);
}

CIMGUI_TE_API void ImGuiTestContext_KeyDown(ImGuiTestContext* self, int key_chord) { self->KeyDown(key_chord); }

CIMGUI_TE_API void ImGuiTestContext_KeyUp(ImGuiTestContext* self, int key_chord) { self->KeyUp(key_chord); }

CIMGUI_TE_API void ImGuiTestContext_KeyPress(ImGuiTestContext* self, int key_chord, int count) {
    self->KeyPress(key_chord, count);
}

CIMGUI_TE_API void ImGuiTestContext_KeyHold(ImGuiTestContext* self, int key_chord, float time) {
    self->KeyHold(key_chord, time);
}

CIMGUI_TE_API void ImGuiTestContext_KeySetEx(ImGuiTestContext* self, int key_chord, bool is_down, float time) {
    self->KeySetEx(key_chord, is_down, time);
}

CIMGUI_TE_API void ImGuiTestContext_KeyChars(ImGuiTestContext* self, const char* chars) { self->KeyChars(chars); }

CIMGUI_TE_API void ImGuiTestContext_KeyCharsAppend(ImGuiTestContext* self, const char* chars) {
    self->KeyCharsAppend(chars);
}

CIMGUI_TE_API void ImGuiTestContext_KeyCharsAppendEnter(ImGuiTestContext* self, const char* chars) {
    self->KeyCharsAppendEnter(chars);
}

CIMGUI_TE_API void ImGuiTestContext_KeyCharsReplace(ImGuiTestContext* self, const char* chars) {
    self->KeyCharsReplace(chars);
}

CIMGUI_TE_API void ImGuiTestContext_KeyCharsReplaceEnter(ImGuiTestContext* self, const char* chars) {
    self->KeyCharsReplaceEnter(chars);
}

CIMGUI_TE_API void ImGuiTestContext_SetInputMode(ImGuiTestContext* self, ImGuiInputSource input_mode) {
    self->SetInputMode(input_mode);
}

CIMGUI_TE_API void ImGuiTestContext_NavMoveTo(ImGuiTestContext* self, ImGuiTestRef ref) { self->NavMoveTo(ref); }

CIMGUI_TE_API void ImGuiTestContext_NavActivate(ImGuiTestContext* self) { self->NavActivate(); }

CIMGUI_TE_API void ImGuiTestContext_NavInput(ImGuiTestContext* self) { self->NavInput(); }

CIMGUI_TE_API void ImGuiTestContext_ScrollTo(ImGuiTestContext* self, ImGuiTestRef ref, ImGuiAxis axis, float scroll_v,
                                             int flags) {
    self->ScrollTo(ref, axis, scroll_v, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToX(ImGuiTestContext* self, ImGuiTestRef ref, float scroll_x) {
    self->ScrollToX(ref, scroll_x);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToY(ImGuiTestContext* self, ImGuiTestRef ref, float scroll_y) {
    self->ScrollToY(ref, scroll_y);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToTop(ImGuiTestContext* self, ImGuiTestRef ref) { self->ScrollToTop(ref); }

CIMGUI_TE_API void ImGuiTestContext_ScrollToBottom(ImGuiTestContext* self, ImGuiTestRef ref) {
    self->ScrollToBottom(ref);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToItem(ImGuiTestContext* self, ImGuiTestRef ref, ImGuiAxis axis, int flags) {
    self->ScrollToItem(ref, axis, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToItemX(ImGuiTestContext* self, ImGuiTestRef ref) {
    self->ScrollToItemX(ref);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToItemY(ImGuiTestContext* self, ImGuiTestRef ref) {
    self->ScrollToItemY(ref);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollToTabItem(ImGuiTestContext* self, ImGuiTabBar* tab_bar, unsigned int tab_id) {
    self->ScrollToTabItem(tab_bar, tab_id);
}

CIMGUI_TE_API bool ImGuiTestContext_ScrollErrorCheck(ImGuiTestContext* self, ImGuiAxis axis, float expected,
                                                     float actual, int* remaining_attempts) {
    return self->ScrollErrorCheck(axis, expected, actual, remaining_attempts);
}

CIMGUI_TE_API void ImGuiTestContext_ScrollVerifyScrollMax(ImGuiTestContext* self, ImGuiTestRef ref) {
    self->ScrollVerifyScrollMax(ref);
}

CIMGUI_TE_API ImGuiTestItemInfo ImGuiTestContext_ItemInfo(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    return self->ItemInfo(ref, flags);
}

CIMGUI_TE_API ImGuiTestItemInfo ImGuiTestContext_ItemInfoOpenFullPath(ImGuiTestContext* self, ImGuiTestRef ref,
                                                                      int flags) {
    return self->ItemInfoOpenFullPath(ref, flags);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_ItemInfoHandleWildcardSearch(ImGuiTestContext* self,
                                                                    const char* wildcard_prefix_start,
                                                                    const char* wildcard_prefix_end,
                                                                    const char* wildcard_suffix_start) {
    return self->ItemInfoHandleWildcardSearch(wildcard_prefix_start, wildcard_prefix_end, wildcard_suffix_start);
}

CIMGUI_TE_API ImGuiTestItemInfo ImGuiTestContext_ItemInfoNull(ImGuiTestContext* self) { return self->ItemInfoNull(); }

CIMGUI_TE_API void ImGuiTestContext_GatherItems(ImGuiTestContext* self, ImGuiTestItemList* out_list,
                                                ImGuiTestRef parent, int depth) {
    self->GatherItems(out_list, parent, depth);
}

CIMGUI_TE_API void ImGuiTestContext_ItemAction(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref,
                                               int flags, void* action_arg) {
    self->ItemAction(action, ref, flags, action_arg);
}

CIMGUI_TE_API void ImGuiTestContext_ItemClick(ImGuiTestContext* self, ImGuiTestRef ref, int button, int flags) {
    self->ItemClick(ref, button, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemDoubleClick(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemDoubleClick(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemCheck(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemCheck(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemUncheck(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemUncheck(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemOpen(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemOpen(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemClose(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemClose(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemInput(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemInput(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemNavActivate(ImGuiTestContext* self, ImGuiTestRef ref, int flags) {
    self->ItemNavActivate(ref, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemActionAll(ImGuiTestContext* self, ImGuiTestAction action,
                                                  ImGuiTestRef ref_parent, const ImGuiTestActionFilter* filter) {
    self->ItemActionAll(action, ref_parent, filter);
}

CIMGUI_TE_API void ImGuiTestContext_ItemOpenAll(ImGuiTestContext* self, ImGuiTestRef ref_parent, int depth,
                                                int passes) {
    self->ItemOpenAll(ref_parent, depth, passes);
}

CIMGUI_TE_API void ImGuiTestContext_ItemCloseAll(ImGuiTestContext* self, ImGuiTestRef ref_parent, int depth,
                                                 int passes) {
    self->ItemCloseAll(ref_parent, depth, passes);
}

CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_int(ImGuiTestContext* self, ImGuiTestRef ref, int v) {
    self->ItemInputValue(ref, v);
}

CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_float(ImGuiTestContext* self, ImGuiTestRef ref, float f) {
    self->ItemInputValue(ref, f);
}

CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_Str(ImGuiTestContext* self, ImGuiTestRef ref, const char* str) {
    self->ItemInputValue(ref, str);
}

CIMGUI_TE_API int ImGuiTestContext_ItemReadAsInt(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemReadAsInt(ref);
}

CIMGUI_TE_API float ImGuiTestContext_ItemReadAsFloat(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemReadAsFloat(ref);
}

CIMGUI_TE_API bool ImGuiTestContext_ItemReadAsScalar(ImGuiTestContext* self, ImGuiTestRef ref, int data_type,
                                                     void* out_data, int flags) {
    return self->ItemReadAsScalar(ref, data_type, out_data, flags);
}

CIMGUI_TE_API const char* ImGuiTestContext_ItemReadAsString_TestRef(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemReadAsString(ref);
}

CIMGUI_TE_API size_t ImGuiTestContext_ItemReadAsString_TestRefStr(ImGuiTestContext* self, ImGuiTestRef ref,
                                                                  char* out_buf, unsigned long out_buf_size) {
    return self->ItemReadAsString(ref, out_buf, out_buf_size);
}

CIMGUI_TE_API bool ImGuiTestContext_ItemExists(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemExists(ref);
}

CIMGUI_TE_API bool ImGuiTestContext_ItemIsChecked(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemIsChecked(ref);
}

CIMGUI_TE_API bool ImGuiTestContext_ItemIsOpened(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->ItemIsOpened(ref);
}

CIMGUI_TE_API void ImGuiTestContext_ItemVerifyCheckedIfAlive(ImGuiTestContext* self, ImGuiTestRef ref, bool checked) {
    self->ItemVerifyCheckedIfAlive(ref, checked);
}

CIMGUI_TE_API void ImGuiTestContext_ItemHold(ImGuiTestContext* self, ImGuiTestRef ref, float time) {
    self->ItemHold(ref, time);
}

CIMGUI_TE_API void ImGuiTestContext_ItemHoldForFrames(ImGuiTestContext* self, ImGuiTestRef ref, int frames) {
    self->ItemHoldForFrames(ref, frames);
}

CIMGUI_TE_API void ImGuiTestContext_ItemDragOverAndHold(ImGuiTestContext* self, ImGuiTestRef ref_src,
                                                        ImGuiTestRef ref_dst) {
    self->ItemDragOverAndHold(ref_src, ref_dst);
}

CIMGUI_TE_API void ImGuiTestContext_ItemDragAndDrop(ImGuiTestContext* self, ImGuiTestRef ref_src, ImGuiTestRef ref_dst,
                                                    int button) {
    self->ItemDragAndDrop(ref_src, ref_dst, button);
}

CIMGUI_TE_API void ImGuiTestContext_ItemDragWithDelta(ImGuiTestContext* self, ImGuiTestRef ref_src, ImVec2 pos_delta) {
    self->ItemDragWithDelta(ref_src, pos_delta);
}

CIMGUI_TE_API void ImGuiTestContext_TabClose(ImGuiTestContext* self, ImGuiTestRef ref) { self->TabClose(ref); }

CIMGUI_TE_API bool ImGuiTestContext_TabBarCompareOrder(ImGuiTestContext* self, ImGuiTabBar* tab_bar,
                                                       const char** tab_order) {
    return self->TabBarCompareOrder(tab_bar, tab_order);
}

CIMGUI_TE_API void ImGuiTestContext_MenuAction(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref) {
    self->MenuAction(action, ref);
}

CIMGUI_TE_API void ImGuiTestContext_MenuActionAll(ImGuiTestContext* self, ImGuiTestAction action,
                                                  ImGuiTestRef ref_parent) {
    self->MenuActionAll(action, ref_parent);
}

CIMGUI_TE_API void ImGuiTestContext_MenuClick(ImGuiTestContext* self, ImGuiTestRef ref) { self->MenuClick(ref); }

CIMGUI_TE_API void ImGuiTestContext_MenuCheck(ImGuiTestContext* self, ImGuiTestRef ref) { self->MenuCheck(ref); }

CIMGUI_TE_API void ImGuiTestContext_MenuUncheck(ImGuiTestContext* self, ImGuiTestRef ref) { self->MenuUncheck(ref); }

CIMGUI_TE_API void ImGuiTestContext_MenuCheckAll(ImGuiTestContext* self, ImGuiTestRef ref_parent) {
    self->MenuCheckAll(ref_parent);
}

CIMGUI_TE_API void ImGuiTestContext_MenuUncheckAll(ImGuiTestContext* self, ImGuiTestRef ref_parent) {
    self->MenuUncheckAll(ref_parent);
}

CIMGUI_TE_API void ImGuiTestContext_ComboClick(ImGuiTestContext* self, ImGuiTestRef ref) { self->ComboClick(ref); }

CIMGUI_TE_API void ImGuiTestContext_ComboClickAll(ImGuiTestContext* self, ImGuiTestRef ref) {
    self->ComboClickAll(ref);
}

CIMGUI_TE_API void ImGuiTestContext_TableOpenContextMenu(ImGuiTestContext* self, ImGuiTestRef ref, int column_n) {
    self->TableOpenContextMenu(ref, column_n);
}

CIMGUI_TE_API ImGuiSortDirection ImGuiTestContext_TableClickHeader(ImGuiTestContext* self, ImGuiTestRef ref,
                                                                   const char* label, int key_mods) {
    return self->TableClickHeader(ref, label, key_mods);
}

CIMGUI_TE_API void ImGuiTestContext_TableSetColumnEnabled(ImGuiTestContext* self, ImGuiTestRef ref, const char* label,
                                                          bool enabled) {
    self->TableSetColumnEnabled(ref, label, enabled);
}

CIMGUI_TE_API void ImGuiTestContext_TableResizeColumn(ImGuiTestContext* self, ImGuiTestRef ref, int column_n,
                                                      float width) {
    self->TableResizeColumn(ref, column_n, width);
}

CIMGUI_TE_API const ImGuiTableSortSpecs* ImGuiTestContext_TableGetSortSpecs(ImGuiTestContext* self, ImGuiTestRef ref) {
    return self->TableGetSortSpecs(ref);
}

CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowPos(ImGuiTestContext* self, ImGuiViewport* viewport,
                                                                  const ImVec2* pos) {
    self->ViewportPlatform_SetWindowPos(viewport, *pos);
}

CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowSize(ImGuiTestContext* self, ImGuiViewport* viewport,
                                                                   const ImVec2* size) {
    self->ViewportPlatform_SetWindowSize(viewport, *size);
}

CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowFocus(ImGuiTestContext* self, ImGuiViewport* viewport) {
    self->ViewportPlatform_SetWindowFocus(viewport);
}

CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_CloseWindow(ImGuiTestContext* self, ImGuiViewport* viewport) {
    self->ViewportPlatform_CloseWindow(viewport);
}

CIMGUI_TE_API void ImGuiTestContext_DockClear(ImGuiTestContext* self, const char* window_name, ...) {
    va_list args;
    va_start(args, window_name);
    self->DockClear(window_name, args);
    va_end(args);
}

CIMGUI_TE_API void ImGuiTestContext_DockInto(ImGuiTestContext* self, ImGuiTestRef src_id, ImGuiTestRef dst_id,
                                             ImGuiDir split_dir, bool is_outer_docking, int flags) {
    self->DockInto(src_id, dst_id, split_dir, is_outer_docking, flags);
}

CIMGUI_TE_API void ImGuiTestContext_UndockNode(ImGuiTestContext* self, unsigned int dock_id) {
    self->UndockNode(dock_id);
}

CIMGUI_TE_API void ImGuiTestContext_UndockWindow(ImGuiTestContext* self, const char* window_name) {
    self->UndockWindow(window_name);
}

CIMGUI_TE_API bool ImGuiTestContext_WindowIsUndockedOrStandalone(ImGuiTestContext* self, ImGuiWindow* window) {
    return self->WindowIsUndockedOrStandalone(window);
}

CIMGUI_TE_API bool ImGuiTestContext_DockIdIsUndockedOrStandalone(ImGuiTestContext* self, unsigned int dock_id) {
    return self->DockIdIsUndockedOrStandalone(dock_id);
}

CIMGUI_TE_API void ImGuiTestContext_DockNodeHideTabBar(ImGuiTestContext* self, ImGuiDockNode* node, bool hidden) {
    self->DockNodeHideTabBar(node, hidden);
}

CIMGUI_TE_API void ImGuiTestContext_PerfCalcRef(ImGuiTestContext* self) { self->PerfCalcRef(); }

CIMGUI_TE_API void ImGuiTestContext_PerfCapture(ImGuiTestContext* self, const char* category, const char* test_name,
                                                const char* csv_file) {
    self->PerfCapture(category, test_name, csv_file);
}

CIMGUI_TE_API bool ImGuiTestContext_ItemSelectAndReadValue_int(ImGuiTestContext* self, ImGuiTestRef ref, int data_type,
                                                               void* out_data, int flags) {
    return self->ItemSelectAndReadValue(ref, data_type, out_data, flags);
}

CIMGUI_TE_API void ImGuiTestContext_ItemSelectAndReadValue_intPtr(ImGuiTestContext* self, ImGuiTestRef ref,
                                                                  int* out_v) {
    self->ItemSelectAndReadValue(ref, out_v);
}

CIMGUI_TE_API void ImGuiTestContext_ItemSelectAndReadValue_floatPtr(ImGuiTestContext* self, ImGuiTestRef ref,
                                                                    float* out_v) {
    self->ItemSelectAndReadValue(ref, out_v);
}

CIMGUI_TE_API void ImGuiTestContext_YieldUntil(ImGuiTestContext* self, int frame_count) {
    self->YieldUntil(frame_count);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetIDByInt_int(ImGuiTestContext* self, int n) { return self->GetIDByInt(n); }

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetIDByInt_intTestRef(ImGuiTestContext* self, int n, ImGuiTestRef seed_ref) {
    return self->GetIDByInt(n, seed_ref);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetIDByPtr_voidPtr(ImGuiTestContext* self, void* p) {
    return self->GetIDByPtr(p);
}

CIMGUI_TE_API ImGuiID ImGuiTestContext_GetIDByPtr_voidPtrTestRef(ImGuiTestContext* self, void* p,
                                                                 ImGuiTestRef seed_ref) {
    return self->GetIDByPtr(p, seed_ref);
}

CIMGUI_TE_API void ImGuiTestContext__MakeAimingSpaceOverPos(ImGuiTestContext* self, ImGuiViewport* viewport,
                                                            ImGuiWindow* over_window, const ImVec2* over_pos) {
    self->_MakeAimingSpaceOverPos(viewport, over_window, *over_pos);
}

CIMGUI_TE_API void ImGuiTestContext__ForeignWindowsHideOverPos(ImGuiTestContext* self, const ImVec2* pos,
                                                               ImGuiWindow** ignore_list) {
    self->_ForeignWindowsHideOverPos(*pos, ignore_list);
}

CIMGUI_TE_API void ImGuiTestContext__ForeignWindowsUnhideAll(ImGuiTestContext* self) {
    self->_ForeignWindowsUnhideAll();
}

CIMGUI_TE_API ImGuiCsvParser* ImGuiCsvParser_ImGuiCsvParser(int columns) { return IM_NEW(ImGuiCsvParser)(columns); }

CIMGUI_TE_API void ImGuiCsvParser_destroy(ImGuiCsvParser* self) { IM_DELETE(self); }

CIMGUI_TE_API bool ImGuiCsvParser_Load(ImGuiCsvParser* self, const char* file_name) { return self->Load(file_name); }

CIMGUI_TE_API void ImGuiCsvParser_Clear(ImGuiCsvParser* self) { self->Clear(); }

CIMGUI_TE_API const char* ImGuiCsvParser_GetCell(ImGuiCsvParser* self, int row, int col) {
    return self->GetCell(row, col);
}

CIMGUI_TE_API void ImGuiTestGatherTask_Clear(ImGuiTestGatherTask* self) { self->Clear(); }

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForKeyChord(ImGuiTestInput* self, int key_chord, bool down) {
    return self->ForKeyChord(key_chord, down);
}

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForChar(ImGuiTestInput* self, unsigned short v) { return self->ForChar(v); }

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForViewportFocus(ImGuiTestInput* self, unsigned int viewport_id) {
    return self->ForViewportFocus(viewport_id);
}

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForViewportSetPos(ImGuiTestInput* self, unsigned int viewport_id,
                                                              const ImVec2* pos) {
    return self->ForViewportSetPos(viewport_id, *pos);
}

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForViewportSetSize(ImGuiTestInput* self, unsigned int viewport_id,
                                                               const ImVec2* size) {
    return self->ForViewportSetSize(viewport_id, *size);
}

CIMGUI_TE_API ImGuiTestInput ImGuiTestInput_ForViewportClose(ImGuiTestInput* self, unsigned int viewport_id) {
    return self->ForViewportClose(viewport_id);
}

CIMGUI_TE_API ImGuiTestEngine* ImGuiTestEngine_ImGuiTestEngine() { return IM_NEW(ImGuiTestEngine)(); }

CIMGUI_TE_API void ImGuiTestEngine_destroy(ImGuiTestEngine* self) { IM_DELETE(self); }

CIMGUI_TE_API ImGuiPerfToolEntry* ImGuiPerfToolEntry_ImGuiPerfToolEntry() { return IM_NEW(ImGuiPerfToolEntry)(); }

CIMGUI_TE_API ImGuiPerfToolEntry*
ImGuiPerfToolEntry_ImGuiPerfToolEntry_constPerfToolEntryPtr(const ImGuiPerfToolEntry* rhs) {
    return IM_NEW(ImGuiPerfToolEntry)(*rhs);
}

CIMGUI_TE_API void ImGuiPerfToolEntry_Set(ImGuiPerfToolEntry* self, const ImGuiPerfToolEntry* rhs) { self->Set(*rhs); }

CIMGUI_TE_API void ImGuiPerfToolBatch_destroy(ImGuiPerfToolBatch* self) { IM_DELETE(self); }

CIMGUI_TE_API ImGuiPerfTool* ImGuiPerfTool_ImGuiPerfTool() { return IM_NEW(ImGuiPerfTool)(); }

CIMGUI_TE_API void ImGuiPerfTool_destroy(ImGuiPerfTool* self) { IM_DELETE(self); }

CIMGUI_TE_API void ImGuiPerfTool_Clear(ImGuiPerfTool* self) { self->Clear(); }

CIMGUI_TE_API bool ImGuiPerfTool_LoadCSV(ImGuiPerfTool* self, const char* filename) { return self->LoadCSV(filename); }

CIMGUI_TE_API void ImGuiPerfTool_AddEntry(ImGuiPerfTool* self, ImGuiPerfToolEntry* entry) { self->AddEntry(entry); }

CIMGUI_TE_API void ImGuiPerfTool_ShowPerfToolWindow(ImGuiPerfTool* self, ImGuiTestEngine* engine, bool* p_open) {
    self->ShowPerfToolWindow(engine, p_open);
}

CIMGUI_TE_API void ImGuiPerfTool_ViewOnly_Str(ImGuiPerfTool* self, const char* perf_name) { self->ViewOnly(perf_name); }

CIMGUI_TE_API void ImGuiPerfTool_ViewOnly_StrPtr(ImGuiPerfTool* self, const char** perf_names) {
    self->ViewOnly(perf_names);
}

CIMGUI_TE_API ImGuiPerfToolEntry* ImGuiPerfTool_GetEntryByBatchIdx(ImGuiPerfTool* self, int idx,
                                                                   const char* perf_name) {
    return self->GetEntryByBatchIdx(idx, perf_name);
}

CIMGUI_TE_API bool ImGuiPerfTool_SaveHtmlReport(ImGuiPerfTool* self, const char* file_name, const char* image_file) {
    return self->SaveHtmlReport(file_name, image_file);
}

CIMGUI_TE_API bool ImGuiPerfTool_Empty(ImGuiPerfTool* self) { return self->Empty(); }

CIMGUI_TE_API void ImGuiPerfTool__Rebuild(ImGuiPerfTool* self) { self->_Rebuild(); }

CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleBuild_PerfToolBatchPtr(ImGuiPerfTool* self, ImGuiPerfToolBatch* batch) {
    return self->_IsVisibleBuild(batch);
}

CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleBuild_PerfToolEntryPtr(ImGuiPerfTool* self, ImGuiPerfToolEntry* batch) {
    return self->_IsVisibleBuild(batch);
}

CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleTest(ImGuiPerfTool* self, const char* test_name) {
    return self->_IsVisibleTest(test_name);
}

CIMGUI_TE_API void ImGuiPerfTool__CalculateLegendAlignment(ImGuiPerfTool* self) { self->_CalculateLegendAlignment(); }

CIMGUI_TE_API void ImGuiPerfTool__ShowEntriesPlot(ImGuiPerfTool* self) { self->_ShowEntriesPlot(); }

CIMGUI_TE_API void ImGuiPerfTool__ShowEntriesTable(ImGuiPerfTool* self) { self->_ShowEntriesTable(); }

CIMGUI_TE_API void ImGuiPerfTool__SetBaseline(ImGuiPerfTool* self, int batch_index) { self->_SetBaseline(batch_index); }

CIMGUI_TE_API void ImGuiPerfTool__AddSettingsHandler(ImGuiPerfTool* self) { self->_AddSettingsHandler(); }

CIMGUI_TE_API void ImGuiPerfTool__UnpackSortedKey(ImGuiPerfTool* self, unsigned long long key, int* batch_index,
                                                  int* entry_index, int* monotonic_index) {
    self->_UnpackSortedKey(key, batch_index, entry_index, monotonic_index);
}
