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

// Forward declarations
typedef struct ImGuiCaptureImageBuf ImGuiCaptureImageBuf;
typedef struct ImGuiCaptureArgs ImGuiCaptureArgs;
typedef struct ImGuiCaptureWindowData ImGuiCaptureWindowData;
typedef struct ImGuiCaptureContext ImGuiCaptureContext;
typedef struct ImGuiCaptureToolUI ImGuiCaptureToolUI;
typedef struct ImGuiTestEngineResultSummary ImGuiTestEngineResultSummary;
typedef struct ImGuiTestEngineIO ImGuiTestEngineIO;
typedef struct ImGuiTestItemInfo ImGuiTestItemInfo;
typedef struct ImGuiTestItemList ImGuiTestItemList;
typedef struct ImGuiTestLogLineInfo ImGuiTestLogLineInfo;
typedef struct ImGuiTestLog ImGuiTestLog;
typedef struct ImGuiTestOutput ImGuiTestOutput;
typedef struct ImGuiTest ImGuiTest;
typedef struct ImGuiTestRunTask ImGuiTestRunTask;
typedef struct ImGuiTestRef ImGuiTestRef;
typedef struct ImGuiTestRefDesc ImGuiTestRefDesc;
typedef struct ImGuiTestActionFilter ImGuiTestActionFilter;
typedef struct ImGuiTestGenericItemStatus ImGuiTestGenericItemStatus;
typedef struct ImGuiTestGenericVars ImGuiTestGenericVars;
typedef struct ImGuiTestContext ImGuiTestContext;
typedef struct ImGuiTestCoroutineInterface ImGuiTestCoroutineInterface;
typedef struct ImBuildInfo ImBuildInfo;
typedef struct ImGuiCsvParser ImGuiCsvParser;
typedef struct ImGuiTestInfoTask ImGuiTestInfoTask;
typedef struct ImGuiTestGatherTask ImGuiTestGatherTask;
typedef struct ImGuiTestFindByLabelTask ImGuiTestFindByLabelTask;
typedef struct ImGuiTestInput ImGuiTestInput;
typedef struct ImGuiTestInputs ImGuiTestInputs;
typedef struct ImGuiTestEngine ImGuiTestEngine;
typedef struct ImGuiPerfToolEntry ImGuiPerfToolEntry;
typedef struct ImGuiPerfToolBatch ImGuiPerfToolBatch;
typedef struct ImGuiPerfTool ImGuiPerfTool;

// Typedefs
typedef void Str; // Manual typedef to avoid having to wrap the Str class;
typedef struct ImVector_Ulonglong { int Size; int Capacity; unsigned long long* Data; } ImVector_Ulonglong;
typedef struct ImVector_Uint { int Size; int Capacity; unsigned int* Data; } ImVector_Uint;
typedef struct ImVector_double { int Size; int Capacity; double* Data; } ImVector_double;
typedef struct ImVector_charPtr { int Size; int Capacity; char ** Data; } ImVector_charPtr;
typedef struct ImVector_ImGuiTestRunTask { int Size; int Capacity; ImGuiTestRunTask* Data; } ImVector_ImGuiTestRunTask;
typedef struct ImVector_ImGuiTestLogLineInfo { int Size; int Capacity; ImGuiTestLogLineInfo* Data; } ImVector_ImGuiTestLogLineInfo;
typedef struct ImVector_ImGuiTestItemInfo { int Size; int Capacity; ImGuiTestItemInfo* Data; } ImVector_ImGuiTestItemInfo;
typedef struct ImVector_ImGuiTestInput { int Size; int Capacity; ImGuiTestInput* Data; } ImVector_ImGuiTestInput;
typedef struct ImVector_ImGuiTestInfoTask_Ptr { int Size; int Capacity; ImGuiTestInfoTask ** Data; } ImVector_ImGuiTestInfoTask_Ptr;
typedef struct ImVector_ImGuiTest_Ptr { int Size; int Capacity; ImGuiTest ** Data; } ImVector_ImGuiTest_Ptr;
typedef struct ImVector_ImGuiPerfToolEntry { int Size; int Capacity; ImGuiPerfToolEntry* Data; } ImVector_ImGuiPerfToolEntry;
typedef struct ImVector_ImGuiPerfToolBatch { int Size; int Capacity; ImGuiPerfToolBatch* Data; } ImVector_ImGuiPerfToolBatch;
typedef struct ImVector_ImGuiCaptureWindowData { int Size; int Capacity; ImGuiCaptureWindowData* Data; } ImVector_ImGuiCaptureWindowData;
typedef struct ImPool_ImGuiTestItemInfo { ImVector_ImGuiTestItemInfo Buf; ImGuiStorage Map; ImPoolIdx FreeIdx; ImPoolIdx AliveCount; } ImPool_ImGuiTestItemInfo;
typedef struct ImMovingAverage_double { ImVector_double Samples; double Accum; int Idx; int FillAmount; } ImMovingAverage_double;
typedef unsigned int ImGuiCaptureFlags;
typedef bool (ImGuiScreenCaptureFunc)(ImGuiID viewport_id, int x, int y, int w, int h, unsigned int* pixels, void* user_data);
typedef int ImGuiTestFlags;
typedef int ImGuiTestCheckFlags;
typedef int ImGuiTestLogFlags;
typedef int ImGuiTestRunFlags;
typedef void (ImGuiTestEngineSrcFileOpenFunc)(const char* filename, int line_no, void* user_data);
typedef void    (ImGuiTestGuiFunc)(ImGuiTestContext* ctx);
typedef void    (ImGuiTestTestFunc)(ImGuiTestContext* ctx);
typedef void    (ImGuiTestVarsConstructor)(void* buffer);
typedef void    (ImGuiTestVarsPostConstructor)(ImGuiTestContext* ctx, void* ptr, void* fn);
typedef void    (ImGuiTestVarsDestructor)(void* ptr);
typedef int ImGuiTestOpFlags;
typedef void* ImGuiTestCoroutineHandle;
typedef void (ImGuiTestCoroutineMainFunc)(void* data);

enum ImGuiCaptureFlags_
{
    ImGuiCaptureFlags_None                      = 0,
    ImGuiCaptureFlags_StitchAll                 = 1 << 0,   // Capture entire window scroll area (by scrolling and taking multiple screenshot). Only works for a single window.
    ImGuiCaptureFlags_IncludeOtherWindows       = 1 << 1,   // Disable hiding other windows (when CaptureAddWindow has been called by default other windows are hidden)
    ImGuiCaptureFlags_IncludePopups             = 1 << 2,   // Expand capture area to automatically include visible popups (Unused if ImGuiCaptureFlags_IncludeOtherWindows is set)
    ImGuiCaptureFlags_HideMouseCursor           = 1 << 3,   // Hide render software mouse cursor during capture.
    ImGuiCaptureFlags_Instant                   = 1 << 4,   // Perform capture on very same frame. Only works when capturing a rectangular region. Unsupported features: content stitching, window hiding, window relocation.
    ImGuiCaptureFlags_NoSave                    = 1 << 5    // Do not save output image.
};

typedef enum ImGuiCaptureStatus
{
    ImGuiCaptureStatus_InProgress,
    ImGuiCaptureStatus_Done,
    ImGuiCaptureStatus_Error
} ImGuiCaptureStatus;

// Stored in ImGuiTestContext: where we are currently running GuiFunc or TestFunc
typedef enum ImGuiTestActiveFunc
{
    ImGuiTestActiveFunc_None,
    ImGuiTestActiveFunc_GuiFunc,
    ImGuiTestActiveFunc_TestFunc
} ImGuiTestActiveFunc;

typedef enum ImGuiTestRunSpeed
{
    ImGuiTestRunSpeed_Fast          = 0,    // Run tests as fast as possible (teleport mouse, skip delays, etc.)
    ImGuiTestRunSpeed_Normal        = 1,    // Run tests at human watchable speed (for debugging)
    ImGuiTestRunSpeed_Cinematic     = 2,    // Run tests with pauses between actions (for e.g. tutorials)
    ImGuiTestRunSpeed_COUNT
} ImGuiTestRunSpeed;

typedef enum ImGuiTestVerboseLevel
{
    ImGuiTestVerboseLevel_Silent    = 0,    // -v0
    ImGuiTestVerboseLevel_Error     = 1,    // -v1
    ImGuiTestVerboseLevel_Warning   = 2,    // -v2
    ImGuiTestVerboseLevel_Info      = 3,    // -v3
    ImGuiTestVerboseLevel_Debug     = 4,    // -v4
    ImGuiTestVerboseLevel_Trace     = 5,
    ImGuiTestVerboseLevel_COUNT
} ImGuiTestVerboseLevel;

// Test status (stored in ImGuiTest)
typedef enum ImGuiTestStatus
{
    ImGuiTestStatus_Unknown     = 0,
    ImGuiTestStatus_Success     = 1,
    ImGuiTestStatus_Queued      = 2,
    ImGuiTestStatus_Running     = 3,
    ImGuiTestStatus_Error       = 4,
    ImGuiTestStatus_Suspended   = 5,
    ImGuiTestStatus_COUNT
} ImGuiTestStatus;

// Test group: this is mostly used to categorize tests in our testing UI. (Stored in ImGuiTest)
typedef enum ImGuiTestGroup
{
    ImGuiTestGroup_Unknown      = -1,
    ImGuiTestGroup_Tests        = 0,
    ImGuiTestGroup_Perfs        = 1,
    ImGuiTestGroup_COUNT
} ImGuiTestGroup;

// Flags (stored in ImGuiTest)
enum ImGuiTestFlags_
{
    ImGuiTestFlags_None                 = 0,
    ImGuiTestFlags_NoGuiWarmUp          = 1 << 0,   // Disable running the GUI func for 2 frames before starting test code. For tests which absolutely need to start before GuiFunc.
    ImGuiTestFlags_NoAutoFinish         = 1 << 1,   // By default, tests with no TestFunc (only a GuiFunc) will end after warmup. Setting this require test to call ctx->Finish().
    ImGuiTestFlags_NoRecoveryWarnings   = 1 << 2    // Error/recovery warnings (missing End/Pop calls etc.) will be displayed as normal debug entries, for tests which may rely on those.
    //ImGuiTestFlags_RequireViewports   = 1 << 10
};

// Flags for IM_CHECK* macros.
enum ImGuiTestCheckFlags_
{
    ImGuiTestCheckFlags_None            = 0,
    ImGuiTestCheckFlags_SilentSuccess   = 1 << 0
};

// Flags for ImGuiTestContext::Log* functions.
enum ImGuiTestLogFlags_
{
    ImGuiTestLogFlags_None              = 0,
    ImGuiTestLogFlags_NoHeader          = 1 << 0    // Do not display frame count and depth padding
};

enum ImGuiTestRunFlags_
{
    ImGuiTestRunFlags_None              = 0,
    ImGuiTestRunFlags_GuiFuncDisable    = 1 << 0,   // Used internally to temporarily disable the GUI func (at the end of a test, etc)
    ImGuiTestRunFlags_GuiFuncOnly       = 1 << 1,   // Set when user selects "Run GUI func"
    ImGuiTestRunFlags_NoSuccessMsg      = 1 << 2,
    ImGuiTestRunFlags_EnableRawInputs   = 1 << 3,   // Disable input submission to let test submission raw input event (in order to test e.g. IO queue)
    ImGuiTestRunFlags_RunFromGui        = 1 << 4,   // Test ran manually from GUI, will disable watchdog.
    ImGuiTestRunFlags_RunFromCommandLine= 1 << 5,   // Test queued from command-line.

    // Flags for ImGuiTestContext::RunChildTest()
    ImGuiTestRunFlags_NoError           = 1 << 10,
    ImGuiTestRunFlags_ShareVars         = 1 << 11,  // Share generic vars and custom vars between child and parent tests (custom vars need to be same type)
    ImGuiTestRunFlags_ShareTestContext  = 1 << 12,  // Share ImGuiTestContext instead of creating a new one (unsure what purpose this may be useful for yet)
    // TODO: Add GuiFunc options
};

// Named actions. Generally you will call the named helpers e.g. ItemClick(). This is used by shared/low-level functions such as ItemAction().
typedef enum ImGuiTestAction
{
    ImGuiTestAction_Unknown = 0,
    ImGuiTestAction_Hover,          // Move mouse
    ImGuiTestAction_Click,          // Move mouse and click
    ImGuiTestAction_DoubleClick,    // Move mouse and double-click
    ImGuiTestAction_Check,          // Check item if unchecked (Checkbox, MenuItem or any widget reporting ImGuiItemStatusFlags_Checkable)
    ImGuiTestAction_Uncheck,        // Uncheck item if checked
    ImGuiTestAction_Open,           // Open item if closed (TreeNode, BeginMenu or any widget reporting ImGuiItemStatusFlags_Openable)
    ImGuiTestAction_Close,          // Close item if opened
    ImGuiTestAction_Input,          // Start text inputing into a field (e.g. CTRL+Click on Drags/Slider, click on InputText etc.)
    ImGuiTestAction_NavActivate,    // Activate item with navigation
    ImGuiTestAction_COUNT
} ImGuiTestAction;

// Generic flags for many ImGuiTestContext functions
// Some flags are only supported by a handful of functions. Check function headers for list of supported flags.
enum ImGuiTestOpFlags_
{
    ImGuiTestOpFlags_None               = 0,
    ImGuiTestOpFlags_NoCheckHoveredId   = 1 << 1,   // Don't check for HoveredId after aiming for a widget. A few situations may want this: while e.g. dragging or another items prevents hovering, or for items that don't use ItemHoverable()
    ImGuiTestOpFlags_NoError            = 1 << 2,   // Don't abort/error e.g. if the item cannot be found or the operation doesn't succeed.
    ImGuiTestOpFlags_NoFocusWindow      = 1 << 3,   // Don't focus window when aiming at an item
    ImGuiTestOpFlags_NoAutoUncollapse   = 1 << 4,   // Disable automatically uncollapsing windows (useful when specifically testing Collapsing behaviors)
    ImGuiTestOpFlags_NoAutoOpenFullPath = 1 << 5,   // Disable automatically opening intermediaries (e.g. ItemClick("Hello/OK") will automatically first open "Hello" if "OK" isn't found. Only works if ref is a string path.
    ImGuiTestOpFlags_NoYield            = 1 << 6,   // Don't yield (only supported by a few functions), in case you need to manage rigorous per-frame timing.
    ImGuiTestOpFlags_IsSecondAttempt    = 1 << 7,   // Used by recursing functions to indicate a second attempt
    ImGuiTestOpFlags_MoveToEdgeL        = 1 << 8,   // Simple Dumb aiming helpers to test widget that care about clicking position. May need to replace will better functionalities.
    ImGuiTestOpFlags_MoveToEdgeR        = 1 << 9,
    ImGuiTestOpFlags_MoveToEdgeU        = 1 << 10,
    ImGuiTestOpFlags_MoveToEdgeD        = 1 << 11,
};

typedef enum ImOsConsoleStream
{
    ImOsConsoleStream_StandardOutput,
    ImOsConsoleStream_StandardError,
} ImOsConsoleStream;

typedef enum ImOsConsoleTextColor
{
    ImOsConsoleTextColor_Black,
    ImOsConsoleTextColor_White,
    ImOsConsoleTextColor_BrightWhite,
    ImOsConsoleTextColor_BrightRed,
    ImOsConsoleTextColor_BrightGreen,
    ImOsConsoleTextColor_BrightBlue,
    ImOsConsoleTextColor_BrightYellow,
} ImOsConsoleTextColor;

typedef enum ImGuiTestInputType
{
    ImGuiTestInputType_None,
    ImGuiTestInputType_Key,
    ImGuiTestInputType_Char,
    ImGuiTestInputType_ViewportFocus,
    ImGuiTestInputType_ViewportSetPos,
    ImGuiTestInputType_ViewportSetSize,
    ImGuiTestInputType_ViewportClose
} ImGuiTestInputType;

typedef enum ImGuiPerfToolDisplayType
{
    ImGuiPerfToolDisplayType_Simple,                            // Each run will be displayed individually.
    ImGuiPerfToolDisplayType_PerBranchColors,                   // Use one bar color per branch.
    ImGuiPerfToolDisplayType_CombineByBuildInfo,                // Entries with same build information will be averaged.
} ImGuiPerfToolDisplayType;

typedef enum ImGuiTestEngineExportFormat
{
    ImGuiTestEngineExportFormat_None = 0,
    ImGuiTestEngineExportFormat_JUnitXml,
} ImGuiTestEngineExportFormat;

// [Internal]
// Helper class for simple bitmap manipulation (not particularly efficient!)
struct ImGuiCaptureImageBuf {
    int Width;
    int Height;
    unsigned int* Data; // RGBA8
};

// Defines input and output arguments for capture process.
// When capturing from tests you can usually use the ImGuiTestContext::CaptureXXX() helpers functions.
struct ImGuiCaptureArgs {
    unsigned int InFlags; // Flags for customizing behavior of screenshot tool.
    ImVector_ImGuiWindowPtr InCaptureWindows; // Windows to capture. All other windows will be hidden. May be used with InCaptureRect to capture only some windows in specified rect.
    ImRect InCaptureRect; // Screen rect to capture. Does not include padding.
    float InPadding; // Extra padding at the edges of the screenshot. Ensure that there is available space around capture rect horizontally, also vertically if ImGuiCaptureFlags_StitchFullContents is not used.
    char InOutputFile[256]; // Output will be saved to a file if InOutputImageBuf is nullptr.
    ImGuiCaptureImageBuf* InOutputImageBuf; // _OR_ Output will be saved to image buffer if specified.
    int InRecordFPSTarget; // FPS target for recording videos.
    int InSizeAlign; // Resolution alignment (0 = auto, 1 = no alignment, >= 2 = align width/height to be multiple of given value)
    ImVec2 OutImageSize; // Produced image size.
};

struct ImGuiCaptureWindowData {
    ImGuiWindow* Window;
    ImRect BackupRect;
    ImVec2 PosDuringCapture;
};

// Implements functionality for capturing images
struct ImGuiCaptureContext {
    ImFuncPtr(ImGuiScreenCaptureFunc) ScreenCaptureFunc; // Graphics backend specific function that captures specified portion of framebuffer and writes RGBA data to `pixels` buffer.
    void* ScreenCaptureUserData; // Custom user pointer which is passed to ScreenCaptureFunc. (Optional)
    char* VideoCaptureEncoderPath; // Video encoder path (not owned, stored externally).
    int VideoCaptureEncoderPathSize; // Optional. Set in order to edit this parameter from UI.
    char* VideoCaptureEncoderParams; // Video encoder params (not owned, stored externally).
    int VideoCaptureEncoderParamsSize; // Optional. Set in order to edit this parameter from UI.
    char* GifCaptureEncoderParams; // Video encoder params for GIF output (not owned, stored externally).
    int GifCaptureEncoderParamsSize; // Optional. Set in order to edit this parameter from UI.
    ImRect _CaptureRect; // Viewport rect that is being captured.
    ImRect _CapturedWindowRect; // Top-left corner of region that covers all windows included in capture. This is not same as _CaptureRect.Min when capturing explicitly specified rect.
    int _ChunkNo; // Number of chunk that is being captured when capture spans multiple frames.
    int _FrameNo; // Frame number during capture process that spans multiple frames.
    ImVec2 _MouseRelativeToWindowPos; // Mouse cursor position relative to captured window (when _StitchAll is in use).
    ImGuiWindow* _HoveredWindow; // Window which was hovered at capture start.
    ImGuiCaptureImageBuf _CaptureBuf; // Output image buffer.
    const ImGuiCaptureArgs* _CaptureArgs; // Current capture args. Set only if capture is in progress.
    ImVector_ImGuiCaptureWindowData _WindowsData; // Backup windows that will have their rect modified and restored. args->InCaptureWindows can not be used because popups may get closed during capture and no longer appear in that list.
    bool _VideoRecording; // Flag indicating that video recording is in progress.
    double _VideoLastFrameTime; // Time when last video frame was recorded.
    FILE* _VideoEncoderPipe; // File writing to stdin of video encoder process.
    bool _BackupMouseDrawCursor; // Initial value of g.IO.MouseDrawCursor
    ImVec2 _BackupDisplayWindowPadding; // Backup padding. We set it to {0, 0} during capture.
    ImVec2 _BackupDisplaySafeAreaPadding; // Backup padding. We set it to {0, 0} during capture.
};

// Implements UI for capturing images
// (when using ImGuiTestEngine scripting API you may not need to use this at all)
struct ImGuiCaptureToolUI {
    float SnapGridSize; // Size of the grid cell for "snap to grid" functionality.
    char OutputLastFilename[256]; // File name of last captured file.
    char* VideoCaptureExtension; // Video file extension (e.g. ".gif" or ".mp4")
    int VideoCaptureExtensionSize; // Optional. Set in order to edit this parameter from UI.
    ImGuiCaptureArgs _CaptureArgs; // Capture args
    bool _StateIsPickingWindow;
    bool _StateIsCapturing;
    ImVector_Uint _SelectedWindows;
    char _OutputFileTemplate[256]; //
    int _FileCounter; // Counter which may be appended to file name when saving. By default, counting starts from 1. When done this field holds number of saved files.
};

struct ImGuiTestEngineResultSummary {
    int CountTested; // Number of tests executed
    int CountSuccess; // Number of tests succeeded
    int CountInQueue; // Number of tests remaining in queue (e.g. aborted, crashed)
};

struct ImGuiTestEngineIO {
    ImGuiTestCoroutineInterface* CoroutineFuncs; // (Required) Coroutine functions (see imgui_te_coroutines.h)
    ImFuncPtr(ImGuiTestEngineSrcFileOpenFunc)   SrcFileOpenFunc; // (Optional) To open source files from test engine UI (otherwise default to open file in shell)
    ImFuncPtr(ImGuiScreenCaptureFunc)           ScreenCaptureFunc; // (Optional) To capture graphics output (application _MUST_ call ImGuiTestEngine_PostSwap() function after swapping is framebuffer)
    void* SrcFileOpenUserData; // (Optional) User data for SrcFileOpenFunc
    void* ScreenCaptureUserData; // (Optional) User data for ScreenCaptureFunc
    bool ConfigSavedSettings; // Load/Save settings in main context .ini file.
    ImGuiTestRunSpeed ConfigRunSpeed; // Run tests in fast/normal/cinematic mode
    bool ConfigStopOnError; // Stop queued tests on test error
    bool ConfigBreakOnError; // Break debugger on test error by calling IM_DEBUG_BREAK()
    bool ConfigKeepGuiFunc; // Keep test GUI running at the end of the test
    ImGuiTestVerboseLevel ConfigVerboseLevel;
    ImGuiTestVerboseLevel ConfigVerboseLevelOnError;
    bool ConfigLogToTTY;
    bool ConfigLogToDebugger;
    bool ConfigRestoreFocusAfterTests; // Restore focus back after running tests
    bool ConfigCaptureEnabled; // Master enable flags for capturing and saving captures. Disable to avoid e.g. lengthy saving of large PNG files.
    bool ConfigCaptureOnError;
    bool ConfigNoThrottle; // Disable vsync for performance measurement or fast test running
    bool ConfigMouseDrawCursor; // Enable drawing of Dear ImGui software mouse cursor when running tests
    float ConfigFixedDeltaTime; // Use fixed delta time instead of calculating it from wall clock
    int PerfStressAmount; // Integer to scale the amount of items submitted in test
    char GitBranchName[64]; // e.g. fill in branch name (e.g. recorded in perf samples .csv)
    float MouseSpeed; // Mouse speed (pixel/second) when not running in fast mode
    float MouseWobble; // (0.0f..1.0f) How much wobble to apply to the mouse (pixels per pixel of move distance) when not running in fast mode
    float ScrollSpeed; // Scroll speed (pixel/second) when not running in fast mode
    float TypingSpeed; // Char input speed (characters/second) when not running in fast mode
    float ActionDelayShort; // Time between short actions
    float ActionDelayStandard; // Time between most actions
    char VideoCaptureEncoderPath[256]; // Video encoder executable path, e.g. "path/to/ffmpeg.exe".
    char VideoCaptureEncoderParams[256]; // Video encoder parameters for .MP4 captures, e.g. see IMGUI_CAPTURE_DEFAULT_VIDEO_PARAMS_FOR_FFMPEG
    char GifCaptureEncoderParams[512]; // Video encoder parameters for .GIF captures, e.g. see IMGUI_CAPTURE_DEFAULT_GIF_PARAMS_FOR_FFMPEG
    char VideoCaptureExtension[8]; // Video file extension (default, may be overridden by test).
    float ConfigWatchdogWarning; // Warn when a test exceed this time (in second)
    float ConfigWatchdogKillTest; // Attempt to stop running a test when exceeding this time (in second)
    float ConfigWatchdogKillApp; // Stop application when exceeding this time (in second)
    const char* ExportResultsFilename;
    ImGuiTestEngineExportFormat ExportResultsFormat;
    bool CheckDrawDataIntegrity; // Check ImDrawData integrity (buffer count, etc.). Currently cheap but may become a slow operation.
    bool IsRunningTests;
    bool IsRequestingMaxAppSpeed; // When running in fast mode: request app to skip vsync or even skip rendering if it wants
    bool IsCapturing; // Capture is in progress
};

// Information about a given item or window, result of an ItemInfo() or WindowInfo() query
struct ImGuiTestItemInfo {
    unsigned int ID; // Item ID
    char DebugLabel[32]; // Shortened/truncated label for debugging and convenience purpose
    ImGuiWindow* Window; // Item Window
    unsigned int NavLayer; // Nav layer of the item (ImGuiNavLayer)
    int Depth; // Depth from requested parent id. 0 == ID is immediate child of requested parent id.
    int TimestampMain; // Timestamp of main result (all fields)
    int TimestampStatus; // Timestamp of StatusFlags
    unsigned int ParentID; // Item Parent ID (value at top of the ID stack)
    ImRect RectFull; // Item Rectangle
    ImRect RectClipped; // Item Rectangle (clipped with window->ClipRect at time of item submission)
    int ItemFlags; // Item flags
    int StatusFlags; // Item Status flags (fully updated for some items only, compare TimestampStatus to FrameCount)
};

// Result of an GatherItems() query
struct ImGuiTestItemList {
    ImPool_ImGuiTestItemInfo Pool;
};

struct ImGuiTestLogLineInfo {
    ImGuiTestVerboseLevel Level;
    int LineOffset;
};

struct ImGuiTestLog {
    ImGuiTextBuffer Buffer;
    ImVector_ImGuiTestLogLineInfo LineInfo;
    int CountPerLevel[6];
};

// Storage for the output of a test run
struct ImGuiTestOutput {
    ImGuiTestStatus Status;
    ImGuiTestLog Log;
    unsigned long long StartTime;
    unsigned long long EndTime;
};

// Storage for one test
struct ImGuiTest {
    const char* Category; // Literal, not owned
    const char* Name; // Literal, generally not owned unless NameOwned=true
    ImGuiTestGroup Group; // Coarse groups: 'Tests' or 'Perf'
    bool NameOwned; //
    int ArgVariant; // User parameter. Generally we use it to run variations of a same test by sharing GuiFunc/TestFunc
    int Flags; // See ImGuiTestFlags_
    ImFuncPtr(ImGuiTestGuiFunc)     GuiFunc; // GUI function (optional if your test are running over an existing GUI application)
    ImFuncPtr(ImGuiTestTestFunc)    TestFunc; // Test function
    void* UserData; // General purpose user data (if assigning capturing lambdas on GuiFunc/TestFunc you may not need to use this)
    const char* SourceFile; // __FILE__
    int SourceLine; // __LINE__
    int SourceLineEnd; // end of line (when calculated by ImGuiTestEngine_StartCalcSourceLineEnds())
    ImGuiTestOutput Output;
    unsigned long VarsSize;
    ImGuiTestVarsConstructor*       VarsConstructor;
    ImGuiTestVarsPostConstructor*   VarsPostConstructor; // To override constructor default (in case the default are problematic on the first GuiFunc frame)
    void* VarsPostConstructorUserFn;
    ImGuiTestVarsDestructor*        VarsDestructor;
};

// Stored in test queue
struct ImGuiTestRunTask {
    ImGuiTest* Test;
    int RunFlags;
};

// Weak reference to an Item/Window given an hashed ID _or_ a string path ID.
// This is most often passed as argument to function and generally has a very short lifetime.
// Documentation: https://github.com/ocornut/imgui_test_engine/wiki/Named-References
// (SUGGESTION: add those constructors to "VA Step Filter" (Visual Assist) or a .natstepfilter file (Visual Studio) so they are skipped by F11 (StepInto)
struct ImGuiTestRef {
    unsigned int ID; // Pre-hashed ID
    const char* Path; // Relative or absolute path (string pointed to, not owned, as our lifetime is very short)
};

// Debug helper to output a string showing the Path, ID or Debug Label based on what is available (some items only have ID as we couldn't find/store a Path)
// (The size is arbitrary, this is only used for logging info the user/debugger)
struct ImGuiTestRefDesc {
    char Buf[80];
};

// Advanced filtering for ItemActionAll()
struct ImGuiTestActionFilter {
    int MaxDepth;
    int MaxPasses;
    const int* MaxItemCountPerDepth;
    int RequireAllStatusFlags;
    int RequireAnyStatusFlags;
};

// Helper struct to store various query-able state of an item.
// This facilitate interactions between GuiFunc and TestFunc, since those state are frequently used.
struct ImGuiTestGenericItemStatus {
    int RetValue; // return value
    int Hovered; // result of IsItemHovered()
    int Active; // result of IsItemActive()
    int Focused; // result of IsItemFocused()
    int Clicked; // result of IsItemClicked()
    int Visible; // result of IsItemVisible()
    int Edited; // result of IsItemEdited()
    int Activated; // result of IsItemActivated()
    int Deactivated; // result of IsItemDeactivated()
    int DeactivatedAfterEdit; // result of IsItemDeactivatedAfterEdit()
};

// Generic structure with various storage fields.
// This is useful for tests to quickly share data between GuiFunc and TestFunc without creating custom data structure.
// If those fields are not enough: using test->SetVarsDataType<>() + ctx->GetVars<>() it is possible to store custom data.
struct ImGuiTestGenericVars {
    int Step;
    int Count;
    unsigned int DockId;
    unsigned int OwnerId;
    ImVec2 WindowSize;
    int WindowFlags;
    int TableFlags;
    int PopupFlags;
    ImGuiTestGenericItemStatus Status;
    bool ShowWindow1;
    bool ShowWindow2;
    bool UseClipper;
    bool UseViewports;
    float Width;
    ImVec2 Pos;
    ImVec2 Pivot;
    ImVec2 ItemSize;
    ImVec4 Color1;
    ImVec4 Color2;
    int Int1;
    int Int2;
    int IntArray[10];
    float Float1;
    float Float2;
    float FloatArray[10];
    bool Bool1;
    bool Bool2;
    bool BoolArray[10];
    unsigned int Id;
    unsigned int IdArray[10];
    char Str1[256];
    char Str2[256];
};

struct ImGuiTestContext {
    ImGuiTestGenericVars GenericVars; // Generic variables holder for convenience.
    void* UserVars; // Access using ctx->GetVars<Type>(). Setup with test->SetVarsDataType<>().
    ImGuiContext* UiContext; // UI context
    ImGuiTestEngineIO* EngineIO; // Test Engine IO/settings
    ImGuiTest* Test; // Test currently running
    ImGuiTestOutput* TestOutput; // Test output (generally == &Test->Output)
    int OpFlags; // Flags affecting all operation (supported: ImGuiTestOpFlags_NoAutoUncollapse)
    int PerfStressAmount; // Convenience copy of engine->IO.PerfStressAmount
    int FrameCount; // Test frame count (restarts from zero every time)
    int FirstTestFrameCount; // First frame where TestFunc is running (after warm-up frame). This is generally -1 or 0 depending on whether we have warm up enabled
    bool FirstGuiFrame;
    bool HasDock; // #ifdef IMGUI_HAS_DOCK expressed in an easier to test value
    ImGuiCaptureArgs* CaptureArgs; // Capture settings used by ctx->Capture*() functions
    ImGuiTestEngine* Engine;
    ImGuiTestInputs* Inputs;
    int RunFlags;
    ImGuiTestActiveFunc ActiveFunc; // None/GuiFunc/TestFunc
    double RunningTime; // Amount of wall clock time the Test has been running. Used by safety watchdog.
    int ActionDepth; // Nested depth of ctx-> function calls (used to decorate log)
    int CaptureCounter; // Number of captures
    int ErrorCounter; // Number of errors (generally this maxxes at 1 as most functions will early out)
    bool Abort;
    double PerfRefDt;
    int PerfIterations; // Number of frames for PerfCapture() measurements
    char RefStr[256]; // Reference window/path over which all named references are based
    unsigned int RefID; // Reference ID over which all named references are based
    unsigned int RefWindowID; // ID of a window that contains RefID item
    ImGuiInputSource InputMode; // Prefer interacting with mouse/keyboard/gamepad
    ImVector_char TempString;
    ImVector_char Clipboard; // Private clipboard for the test instance
    ImVector_ImGuiWindowPtr ForeignWindowsToHide;
    ImGuiTestItemInfo DummyItemInfoNull; // Storage for ItemInfoNull()
    bool CachedLinesPrintedToTTY;
};

// Coroutine support interface
// Your app needs to return and implement this.
// You can '#define IMGUI_TEST_ENGINE_ENABLE_COROUTINE_STDTHREAD_IMPL 1' in your imconfig file to use a default implementation using std::thread
// Documentation: https://github.com/ocornut/imgui_test_engine/wiki/Setting-Up
struct ImGuiTestCoroutineInterface {
    ImGuiTestCoroutineHandle (*CreateFunc)(ImGuiTestCoroutineMainFunc* func, const char* name, void* data);
    void                     (*DestroyFunc)(ImGuiTestCoroutineHandle handle);
    bool                     (*RunFunc)(ImGuiTestCoroutineHandle handle);
    void                     (*YieldFunc)();
};

// All the pointers are expect to be literals/persistent
struct ImBuildInfo {
    const char* Type;
    const char* Cpu;
    const char* OS;
    const char* Compiler;
    char Date[32]; // "YYYY-MM-DD"
    const char* Time;
};

struct ImGuiCsvParser {
    int Columns; // Number of columns in CSV file.
    int Rows; // Number of rows in CSV file.
    char* _Data; // CSV file data.
    ImVector_charPtr _Index; // CSV table: _Index[row * _Columns + col].
};

// Query item position/window/state given ID.
struct ImGuiTestInfoTask {
    unsigned int ID;
    int FrameCount; // Timestamp of request
    char DebugName[64]; // Debug string representing the queried ID
    ImGuiTestItemInfo Result;
};

// Gather item list in given parent ID.
struct ImGuiTestGatherTask {
    unsigned int InParentID;
    int InMaxDepth;
    short InLayerMask;
    ImGuiTestItemList* OutList;
    ImGuiTestItemInfo* LastItemInfo;
};

// Find item ID given a label and a parent id
// Usually used by queries with wildcards such as ItemInfo("hello/**/foo/bar")
struct ImGuiTestFindByLabelTask {
    unsigned int InPrefixId; // A known base ID which appears BEFORE the wildcard ID (for "hello/**/foo/bar" it would be hash of "hello")
    int InSuffixDepth; // Number of labels in a path, after unknown base ID (for "hello/**/foo/bar" it would be 2)
    const char* InSuffix; // A label string which appears on ID stack after unknown base ID (for "hello/**/foo/bar" it would be "foo/bar")
    const char* InSuffixLastItem; // A last label string (for "hello/**/foo/bar" it would be "bar")
    unsigned int InSuffixLastItemHash;
    int InFilterItemStatusFlags; // Flags required for item to be returned
    unsigned int OutItemId; // Result item ID
};

// FIXME: May want to strip further now that core imgui is using its own input queue
struct ImGuiTestInput {
    ImGuiTestInputType Type;
    int KeyChord;
    unsigned short Char;
    bool Down;
    unsigned int ViewportId;
    ImVec2 ViewportPosSize;
};

struct ImGuiTestInputs {
    ImVec2 MousePosValue; // Own non-rounded copy of MousePos in order facilitate simulating mouse movement very slow speed and high-framerate
    ImVec2 MouseWheel;
    unsigned int MouseHoveredViewport;
    int MouseButtonsValue; // FIXME-TESTS: Use simulated_io.MouseDown[] ?
    ImVector_ImGuiTestInput Queue;
    bool HostEscDown;
    float HostEscDownDuration; // Maintain our own DownDuration for host/backend ESC key so we can abort.
};

// [Internal] Test Engine Context
struct ImGuiTestEngine {
    ImGuiTestEngineIO IO;
    ImGuiContext* UiContextTarget; // imgui context for testing
    ImGuiContext* UiContextActive; // imgui context for testing == UiContextTarget or nullptr
    bool Started;
    unsigned long long BatchStartTime;
    unsigned long long BatchEndTime;
    int FrameCount;
    float OverrideDeltaTime; // Inject custom delta time into imgui context to simulate clock passing faster than wall clock time.
    ImVector_ImGuiTest_Ptr TestsAll;
    ImVector_ImGuiTestRunTask TestsQueue;
    ImGuiTestContext* TestContext; // Running test context
    bool TestsSourceLinesDirty;
    ImVector_ImGuiTestInfoTask_Ptr InfoTasks;
    ImGuiTestGatherTask GatherTask;
    ImGuiTestFindByLabelTask FindByLabelTask;
    void* TestQueueCoroutine; // Coroutine to run the test queue
    bool TestQueueCoroutineShouldExit; // Flag to indicate that we are shutting down and the test queue coroutine should stop
    ImGuiTestInputs Inputs;
    bool Abort;
    ImGuiTest* UiSelectAndScrollToTest;
    ImGuiTest* UiSelectedTest;
    Str* UiFilterTests;
    Str* UiFilterPerfs;
    unsigned int UiFilterByStatusMask;
    bool UiMetricsOpen;
    bool UiDebugLogOpen;
    bool UiCaptureToolOpen;
    bool UiStackToolOpen;
    bool UiPerfToolOpen;
    float UiLogHeight;
    double PerfRefDeltaTime;
    ImMovingAverage_double PerfDeltaTime100;
    ImMovingAverage_double PerfDeltaTime500;
    ImGuiPerfTool* PerfTool;
    ImGuiCaptureToolUI CaptureTool; // Capture tool UI
    ImGuiCaptureContext CaptureContext; // Capture context used in tests
    ImGuiCaptureArgs* CaptureCurrentArgs;
    bool PostSwapCalled;
    bool ToolDebugRebootUiContext; // Completely shutdown and recreate the dear imgui context in place
    bool ToolSlowDown;
    int ToolSlowDownMs;
    ImGuiTestRunSpeed BackupConfigRunSpeed;
    bool BackupConfigNoThrottle;
};

// [Internal] Perf log entry. Changes to this struct should be reflected in ImGuiTestContext::PerfCapture() and ImGuiTestEngine_Start().
// This struct assumes strings stored here will be available until next ImGuiPerfTool::Clear() call. Fortunately we do not have to actively
// manage lifetime of these strings. New entries are created only in two cases:
// 1. ImGuiTestEngine_PerfToolAppendToCSV() call after perf test has run. This call receives ImGuiPerfToolEntry with const strings stored indefinitely by application.
// 2. As a consequence of ImGuiPerfTool::LoadCSV() call, we persist the ImGuiCSVParser instance, which keeps parsed CSV text, from which strings are referenced.
// As a result our solution also doesn't make many allocations.
struct ImGuiPerfToolEntry {
    unsigned long long Timestamp; // Title of a particular batch of perftool entries.
    const char* Category; // Name of category perf test is in.
    const char* TestName; // Name of perf test.
    double DtDeltaMs; // Result of perf test.
    double DtDeltaMsMin; // May be used by perftool.
    double DtDeltaMsMax; // May be used by perftool.
    int NumSamples; // Number aggregated samples.
    int PerfStressAmount; //
    const char* GitBranchName; // Build information.
    const char* BuildType; //
    const char* Cpu; //
    const char* OS; //
    const char* Compiler; //
    const char* Date; // Date of this entry or min date of combined entries.
    double VsBaseline; // Percent difference vs baseline.
    int LabelIndex; // Index of TestName in ImGuiPerfTool::_LabelsVisible.
};

// [Internal] Perf log batch.
struct ImGuiPerfToolBatch {
    unsigned long long BatchID; // Timestamp of the batch, or unique ID of the build in combined mode.
    int NumSamples; // A number of unique batches aggregated.
    int BranchIndex; // For per-branch color mapping.
    ImVector_ImGuiPerfToolEntry Entries; // Aggregated perf test entries. Order follows ImGuiPerfTool::_LabelsVisible order.
};

struct ImGuiPerfTool {
    ImVector_ImGuiPerfToolEntry _SrcData; // Raw entries from CSV file (with string pointer into CSV data).
    ImVector_const_charPtr _Labels;
    ImVector_const_charPtr _LabelsVisible; // ImPlot requires a pointer of all labels beforehand. Always contains a dummy "" entry at the end!
    ImVector_ImGuiPerfToolBatch _Batches;
    ImGuiStorage _LabelBarCounts; // Number bars each label will render.
    int _NumVisibleBuilds; // Cached number of visible builds.
    int _NumUniqueBuilds; // Cached number of unique builds.
    ImGuiPerfToolDisplayType _DisplayType;
    int _BaselineBatchIndex; // Index of baseline build.
    unsigned long long _BaselineTimestamp;
    unsigned long long _BaselineBuildId;
    char _Filter[128]; // Context menu filtering substring.
    char _FilterDateFrom[11];
    char _FilterDateTo[11];
    float _InfoTableHeight;
    int _AlignStress; // Alignment values for build info components, so they look aligned in the legend.
    int _AlignType;
    int _AlignOs;
    int _AlignCpu;
    int _AlignCompiler;
    int _AlignBranch;
    int _AlignSamples;
    bool _InfoTableSortDirty;
    ImVector_Ulonglong _InfoTableSort; // _InfoTableSort[_LabelsVisible.Size * _Batches.Size]. Contains sorted batch indices for each label.
    const ImGuiTableSortSpecs* _InfoTableSortSpecs; // Current table sort specs.
    ImGuiStorage _TempSet; // Used as a set
    int _TableHoveredTest; // Index within _VisibleLabelPointers array.
    int _TableHoveredBatch;
    int _PlotHoverTest;
    int _PlotHoverBatch;
    bool _PlotHoverTestLabel;
    bool _ReportGenerating;
    ImGuiStorage _Visibility;
    ImGuiCsvParser* _CsvParser; // We keep this around and point to its fields
};

#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS

typedef ImVector<ImGuiPerfToolEntry> ImVector_ImGuiPerfToolEntry;
typedef ImVector<unsigned int> ImVector_Uint;
typedef ImVector<ImGuiCaptureWindowData> ImVector_ImGuiCaptureWindowData;
typedef ImVector<ImGuiTestItemInfo> ImVector_ImGuiTestItemInfo;
typedef ImVector<unsigned long long> ImVector_Ulonglong;
typedef ImMovingAverage<double> ImMovingAverage_double;
typedef ImVector<ImGuiPerfToolBatch> ImVector_ImGuiPerfToolBatch;
typedef ImVector<ImGuiTestInfoTask *> ImVector_ImGuiTestInfoTask_Ptr;
typedef ImVector<char *> ImVector_charPtr;
typedef ImPool<ImGuiTestItemInfo> ImPool_ImGuiTestItemInfo;
typedef ImVector<ImGuiTestLogLineInfo> ImVector_ImGuiTestLogLineInfo;
typedef ImVector<double> ImVector_double;
typedef ImVector<ImGuiTest *> ImVector_ImGuiTest_Ptr;
typedef ImVector<ImGuiTestInput> ImVector_ImGuiTestInput;
typedef ImVector<ImGuiTestRunTask> ImVector_ImGuiTestRunTask;

#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

/** Header file: imgui_te_internal.h **/
CIMGUI_TE_API ImGuiTestItemInfo * cImGuiTestEngine_FindItemInfo(ImGuiTestEngine* engine, unsigned int id, const char* debug_id);
CIMGUI_TE_API void cImGuiTestEngine_Yield(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_SetDeltaTime(ImGuiTestEngine* engine, float delta_time);
CIMGUI_TE_API int cImGuiTestEngine_GetFrameCount(ImGuiTestEngine* engine);
CIMGUI_TE_API bool cImGuiTestEngine_PassFilter(ImGuiTest* test, const char* filter);
CIMGUI_TE_API void cImGuiTestEngine_RunTest(ImGuiTestEngine* engine, ImGuiTestContext* ctx, ImGuiTest* test, int run_flags);
CIMGUI_TE_API void cImGuiTestEngine_BindImGuiContext(ImGuiTestEngine* engine, ImGuiContext* ui_ctx);
CIMGUI_TE_API void cImGuiTestEngine_UnbindImGuiContext(ImGuiTestEngine* engine, ImGuiContext* ui_ctx);
CIMGUI_TE_API void cImGuiTestEngine_RebootUiContext(ImGuiTestEngine* engine);
CIMGUI_TE_API ImGuiPerfTool * cImGuiTestEngine_GetPerfTool(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_UpdateTestsSourceLines(ImGuiTestEngine* engine);
CIMGUI_TE_API bool cImGuiTestEngine_CaptureScreenshot(ImGuiTestEngine* engine, ImGuiCaptureArgs* args);
CIMGUI_TE_API bool cImGuiTestEngine_CaptureBeginVideo(ImGuiTestEngine* engine, ImGuiCaptureArgs* args);
CIMGUI_TE_API bool cImGuiTestEngine_CaptureEndVideo(ImGuiTestEngine* engine, ImGuiCaptureArgs* args);
CIMGUI_TE_API const char * cImGuiTestEngine_GetStatusName(ImGuiTestStatus v);
CIMGUI_TE_API const char * cImGuiTestEngine_GetRunSpeedName(ImGuiTestRunSpeed v);
CIMGUI_TE_API const char * cImGuiTestEngine_GetVerboseLevelName(ImGuiTestVerboseLevel v);

/** Header file: imgui_te_utils.h **/
CIMGUI_TE_API ImGuiID cImHashDecoratedPath(const char* str, const char* str_end, unsigned int seed);
CIMGUI_TE_API const char * cImFindNextDecoratedPartInPath(const char* str, const char* str_end);
CIMGUI_TE_API bool cImFileExist(const char* filename);
CIMGUI_TE_API bool cImFileDelete(const char* filename);
CIMGUI_TE_API bool cImFileCreateDirectoryChain(const char* path, const char* path_end);
CIMGUI_TE_API bool cImFileFindInParents(const char* sub_path, int max_parent_count, Str* output);
CIMGUI_TE_API bool cImFileLoadSourceBlurb(const char* filename, int line_no_start, int line_no_end, ImGuiTextBuffer* out_buf);
// Return value always between path and path_end
CIMGUI_TE_API const char * cImPathFindFilename(const char* path, const char* path_end);
// Return value always between path and path_end
CIMGUI_TE_API const char * cImPathFindExtension(const char* path, const char* path_end);
CIMGUI_TE_API void cImPathFixSeparatorsForCurrentOS(char* buf);
CIMGUI_TE_API void cImStrReplace(Str* s, const char* find, const char* repl);
CIMGUI_TE_API const char * cImStrchrRangeWithEscaping(const char* str, const char* str_end, char find_c);
CIMGUI_TE_API void cImStrXmlEscape(Str* s);
CIMGUI_TE_API int cImStrBase64Encode(const unsigned char* src, char* dst, int length);
CIMGUI_TE_API void cImParseExtractArgcArgvFromCommandLine(int* out_argc, const char *** out_argv, const char* cmd_line);
CIMGUI_TE_API bool cImParseFindIniSection(const char* ini_config, const char* header, ImVector_char* result);
CIMGUI_TE_API uint64_t cImTimeGetInMicroseconds();
CIMGUI_TE_API void cImTimestampToISO8601(unsigned long timestamp, Str* out_date);
CIMGUI_TE_API void cImThreadSleepInMilliseconds(int ms);
CIMGUI_TE_API void cImThreadSetCurrentThreadDescription(const char* description);
CIMGUI_TE_API const ImBuildInfo * cImBuildGetCompilationInfo();
CIMGUI_TE_API bool cImBuildFindGitBranchName(const char* git_repo_path, Str* branch_name);
CIMGUI_TE_API bool cImOsCreateProcess(const char* cmd_line);
CIMGUI_TE_API FILE * cImOsPOpen(const char* cmd_line, const char* mode);
CIMGUI_TE_API void cImOsPClose(FILE* fp);
CIMGUI_TE_API void cImOsOpenInShell(const char* path);
CIMGUI_TE_API bool cImOsIsDebuggerPresent();
CIMGUI_TE_API void cImOsOutputDebugString(const char* message);
CIMGUI_TE_API void cImOsConsoleSetTextColor(ImOsConsoleStream stream, ImOsConsoleTextColor color);
CIMGUI_TE_API ImGuiID cTableGetHeaderID_Str(ImGuiTable* table, const char* column, int instance_no);
CIMGUI_TE_API ImGuiID cTableGetHeaderID_int(ImGuiTable* table, int column_n, int instance_no);
CIMGUI_TE_API void cTableDiscardInstanceAndSettings(unsigned int table_id);
CIMGUI_TE_API void cDrawDataVerifyMatchingBufferCount(ImDrawData* draw_data);

/** Header file: imgui_te_exporters.h **/
CIMGUI_TE_API void cImGuiTestEngine_PrintResultSummary(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_Export(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_ExportEx(ImGuiTestEngine* engine, ImGuiTestEngineExportFormat format, const char* filename);

/** Header file: imgui_te_ui.h **/
CIMGUI_TE_API void cImGuiTestEngine_ShowTestEngineWindows(ImGuiTestEngine* engine, bool* p_open);
CIMGUI_TE_API void cImGuiTestEngine_OpenSourceFile(ImGuiTestEngine* engine, const char* source_filename, int source_line_no);

/** Header file: imgui_te_engine.h **/
CIMGUI_TE_API void cImGuiTestEngineHook_ItemAdd(ImGuiContext* ui_ctx, unsigned int id, const ImRect* bb, const ImGuiLastItemData* item_data);
CIMGUI_TE_API void cImGuiTestEngineHook_ItemInfo(ImGuiContext* ui_ctx, unsigned int id, const char* label, int flags);
CIMGUI_TE_API void cImGuiTestEngineHook_Log(ImGuiContext* ui_ctx, const char* fmt,  ...);
CIMGUI_TE_API const char * cImGuiTestEngine_FindItemDebugLabel(ImGuiContext* ui_ctx, unsigned int id);
CIMGUI_TE_API bool cImGuiTestEngine_Check(const char* file, const char* func, int line, int flags, bool result, const char* expr);
CIMGUI_TE_API bool cImGuiTestEngine_CheckStrOp(const char* file, const char* func, int line, int flags, const char* op, const char* lhs_var, const char* lhs_value, const char* rhs_var, const char* rhs_value, bool* out_result);
CIMGUI_TE_API bool cImGuiTestEngine_Error(const char* file, const char* func, int line, int flags, const char* fmt,  ...);
CIMGUI_TE_API void cImGuiTestEngine_AssertLog(const char* expr, const char* file, const char* function, int line);
CIMGUI_TE_API ImGuiTextBuffer * cImGuiTestEngine_GetTempStringBuilder();
// Create test engine
CIMGUI_TE_API ImGuiTestEngine * cImGuiTestEngine_CreateContext();
// Destroy test engine. Call after ImGui::DestroyContext() so test engine specific ini data gets saved.
CIMGUI_TE_API void cImGuiTestEngine_DestroyContext(ImGuiTestEngine* engine);
// Bind to a dear imgui context. Start coroutine.
CIMGUI_TE_API void cImGuiTestEngine_Start(ImGuiTestEngine* engine, ImGuiContext* ui_ctx);
// Stop coroutine and export if any. (Unbind will lazily happen on context shutdown)
CIMGUI_TE_API void cImGuiTestEngine_Stop(ImGuiTestEngine* engine);
// Call every frame after framebuffer swap, will process screen capture and call test_io.ScreenCaptureFunc()
CIMGUI_TE_API void cImGuiTestEngine_PostSwap(ImGuiTestEngine* engine);
CIMGUI_TE_API ImGuiTestEngineIO * cImGuiTestEngine_GetIO(ImGuiTestEngine* engine);
// Prefer calling IM_REGISTER_TEST()
CIMGUI_TE_API ImGuiTest * cImGuiTestEngine_RegisterTest(ImGuiTestEngine* engine, const char* category, const char* name, const char* src_file, int src_line);
CIMGUI_TE_API void cImGuiTestEngine_UnregisterTest(ImGuiTestEngine* engine, ImGuiTest* test);
CIMGUI_TE_API void cImGuiTestEngine_UnregisterAllTests(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_QueueTest(ImGuiTestEngine* engine, ImGuiTest* test, int run_flags);
CIMGUI_TE_API void cImGuiTestEngine_QueueTests(ImGuiTestEngine* engine, ImGuiTestGroup group, const char* filter, int run_flags);
CIMGUI_TE_API bool cImGuiTestEngine_TryAbortEngine(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_AbortCurrentTest(ImGuiTestEngine* engine);
CIMGUI_TE_API ImGuiTest * cImGuiTestEngine_FindTestByName(ImGuiTestEngine* engine, const char* category, const char* name);
CIMGUI_TE_API bool cImGuiTestEngine_IsTestQueueEmpty(ImGuiTestEngine* engine);
CIMGUI_TE_API bool cImGuiTestEngine_IsUsingSimulatedInputs(ImGuiTestEngine* engine);
CIMGUI_TE_API void cImGuiTestEngine_GetResultSummary(ImGuiTestEngine* engine, ImGuiTestEngineResultSummary* out_results);
CIMGUI_TE_API void cImGuiTestEngine_GetTestList(ImGuiTestEngine* engine, ImVector_ImGuiTest_Ptr* out_tests);
CIMGUI_TE_API void cImGuiTestEngine_GetTestQueue(ImGuiTestEngine* engine, ImVector_ImGuiTestRunTask* out_tests);
// Install default crash handler (if you don't have one)
CIMGUI_TE_API void cImGuiTestEngine_InstallDefaultCrashHandler();
// Default crash handler, should be called from a custom crash handler if such exists
CIMGUI_TE_API void cImGuiTestEngine_CrashHandler();

/** Header file: imgui_te_perftool.h **/
CIMGUI_TE_API void cImGuiTestEngine_PerfToolAppendToCSV(ImGuiPerfTool* perf_log, ImGuiPerfToolEntry* entry, const char* filename);

/* ImGuiCaptureImageBuf */
CIMGUI_TE_API ImGuiCaptureImageBuf * ImGuiCaptureImageBuf_ImGuiCaptureImageBuf();
CIMGUI_TE_API void ImGuiCaptureImageBuf_destroy(ImGuiCaptureImageBuf* self);
// Free allocated memory buffer if such exists.
CIMGUI_TE_API void ImGuiCaptureImageBuf_Clear(ImGuiCaptureImageBuf* self);
// Reallocate buffer for pixel data and zero it.
CIMGUI_TE_API void ImGuiCaptureImageBuf_CreateEmpty(ImGuiCaptureImageBuf* self, int w, int h);
// Save pixel data to specified image file.
CIMGUI_TE_API bool ImGuiCaptureImageBuf_SaveFile(ImGuiCaptureImageBuf* self, const char* filename);
// Clear alpha channel from all pixels.
CIMGUI_TE_API void ImGuiCaptureImageBuf_RemoveAlpha(ImGuiCaptureImageBuf* self);

/* ImGuiCaptureContext */
CIMGUI_TE_API ImGuiCaptureContext * ImGuiCaptureContext_ImGuiCaptureContext(ImGuiScreenCaptureFunc* capture_func);
CIMGUI_TE_API void ImGuiCaptureContext_PreNewFrame(ImGuiCaptureContext* self);
CIMGUI_TE_API void ImGuiCaptureContext_PreRender(ImGuiCaptureContext* self);
CIMGUI_TE_API void ImGuiCaptureContext_PostRender(ImGuiCaptureContext* self);
CIMGUI_TE_API ImGuiCaptureStatus ImGuiCaptureContext_CaptureUpdate(ImGuiCaptureContext* self, ImGuiCaptureArgs* args);
CIMGUI_TE_API void ImGuiCaptureContext_RestoreBackedUpData(ImGuiCaptureContext* self);
CIMGUI_TE_API void ImGuiCaptureContext_ClearState(ImGuiCaptureContext* self);
CIMGUI_TE_API void ImGuiCaptureContext_BeginVideoCapture(ImGuiCaptureContext* self, ImGuiCaptureArgs* args);
CIMGUI_TE_API void ImGuiCaptureContext_EndVideoCapture(ImGuiCaptureContext* self);
CIMGUI_TE_API bool ImGuiCaptureContext_IsCapturingVideo(ImGuiCaptureContext* self);
CIMGUI_TE_API bool ImGuiCaptureContext_IsCapturing(ImGuiCaptureContext* self);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiCaptureContext_destroy(ImGuiCaptureContext* self);

/* ImGuiCaptureToolUI */
CIMGUI_TE_API ImGuiCaptureToolUI * ImGuiCaptureToolUI_ImGuiCaptureToolUI();
// Render a capture tool window with various options and utilities.
CIMGUI_TE_API void ImGuiCaptureToolUI_ShowCaptureToolWindow(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context, bool* p_open);
// Render a window picker that captures picked window to file specified in file_name.
CIMGUI_TE_API void ImGuiCaptureToolUI__CaptureWindowPicker(ImGuiCaptureToolUI* self, ImGuiCaptureArgs* args);
// Render a selector for selecting multiple windows for capture.
CIMGUI_TE_API void ImGuiCaptureToolUI__CaptureWindowsSelector(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context, ImGuiCaptureArgs* args);
// Snap edges of all visible windows to a virtual grid.
CIMGUI_TE_API void ImGuiCaptureToolUI__SnapWindowsToGrid(ImGuiCaptureToolUI* self, float cell_size);
// Format output file template into capture args struct and ensure target directory exists.
CIMGUI_TE_API bool ImGuiCaptureToolUI__InitializeOutputFile(ImGuiCaptureToolUI* self);
CIMGUI_TE_API bool ImGuiCaptureToolUI__ShowEncoderConfigFields(ImGuiCaptureToolUI* self, ImGuiCaptureContext* context);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiCaptureToolUI_destroy(ImGuiCaptureToolUI* self);

/* ImGuiTestItemInfo */
CIMGUI_TE_API ImGuiTestItemInfo * ImGuiTestItemInfo_ImGuiTestItemInfo();
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestItemInfo_destroy(ImGuiTestItemInfo* self);

/* ImGuiTestItemList */
CIMGUI_TE_API void ImGuiTestItemList_Clear(ImGuiTestItemList* self);
CIMGUI_TE_API void ImGuiTestItemList_Reserve(ImGuiTestItemList* self, int capacity);
CIMGUI_TE_API int ImGuiTestItemList_GetSize(ImGuiTestItemList* self);
CIMGUI_TE_API const ImGuiTestItemInfo * ImGuiTestItemList_GetByIndex(ImGuiTestItemList* self, int n);
CIMGUI_TE_API const ImGuiTestItemInfo * ImGuiTestItemList_GetByID(ImGuiTestItemList* self, unsigned int id);
CIMGUI_TE_API size_t ImGuiTestItemList_size(ImGuiTestItemList* self);
CIMGUI_TE_API const ImGuiTestItemInfo * ImGuiTestItemList_begin(ImGuiTestItemList* self);
CIMGUI_TE_API const ImGuiTestItemInfo * ImGuiTestItemList_end(ImGuiTestItemList* self);

/* ImGuiTestLog */
CIMGUI_TE_API ImGuiTestLog * ImGuiTestLog_ImGuiTestLog();
CIMGUI_TE_API bool ImGuiTestLog_IsEmpty(ImGuiTestLog* self);
CIMGUI_TE_API void ImGuiTestLog_Clear(ImGuiTestLog* self);
CIMGUI_TE_API int ImGuiTestLog_ExtractLinesForVerboseLevels(ImGuiTestLog* self, ImGuiTestVerboseLevel level_min, ImGuiTestVerboseLevel level_max, ImGuiTextBuffer* out_buffer);
CIMGUI_TE_API void ImGuiTestLog_UpdateLineOffsets(ImGuiTestLog* self, ImGuiTestEngineIO* engine_io, ImGuiTestVerboseLevel level, const char* start);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestLog_destroy(ImGuiTestLog* self);

/* ImGuiTest */
CIMGUI_TE_API ImGuiTest * ImGuiTest_ImGuiTest();
CIMGUI_TE_API void ImGuiTest_destroy(ImGuiTest* self);
CIMGUI_TE_API void ImGuiTest_SetOwnedName(ImGuiTest* self, const char* name);

/* ImGuiTestRef */
CIMGUI_TE_API ImGuiTestRef * ImGuiTestRef_ImGuiTestRef();
CIMGUI_TE_API ImGuiTestRef * ImGuiTestRef_ImGuiTestRef_Uint(unsigned int id);
CIMGUI_TE_API ImGuiTestRef * ImGuiTestRef_ImGuiTestRef_Str(const char* path);
CIMGUI_TE_API bool ImGuiTestRef_IsEmpty(ImGuiTestRef* self);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestRef_destroy(ImGuiTestRef* self);

/* ImGuiTestRefDesc */
CIMGUI_TE_API const char * ImGuiTestRefDesc_c_str(ImGuiTestRefDesc* self);
CIMGUI_TE_API ImGuiTestRefDesc * ImGuiTestRefDesc_ImGuiTestRefDesc_constTestRefPtr(const ImGuiTestRef* ref);
CIMGUI_TE_API ImGuiTestRefDesc * ImGuiTestRefDesc_ImGuiTestRefDesc_constTestRefPtrconstTestItemInfoPtr(const ImGuiTestRef* ref, const ImGuiTestItemInfo* item);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestRefDesc_destroy(ImGuiTestRefDesc* self);

/* ImGuiTestActionFilter */
CIMGUI_TE_API ImGuiTestActionFilter * ImGuiTestActionFilter_ImGuiTestActionFilter();
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestActionFilter_destroy(ImGuiTestActionFilter* self);

/* ImGuiTestGenericItemStatus */
CIMGUI_TE_API ImGuiTestGenericItemStatus * ImGuiTestGenericItemStatus_ImGuiTestGenericItemStatus();
CIMGUI_TE_API void ImGuiTestGenericItemStatus_Clear(ImGuiTestGenericItemStatus* self);
CIMGUI_TE_API void ImGuiTestGenericItemStatus_QuerySet(ImGuiTestGenericItemStatus* self, bool ret_val);
CIMGUI_TE_API void ImGuiTestGenericItemStatus_QueryInc(ImGuiTestGenericItemStatus* self, bool ret_val);
CIMGUI_TE_API void ImGuiTestGenericItemStatus_Draw(ImGuiTestGenericItemStatus* self);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestGenericItemStatus_destroy(ImGuiTestGenericItemStatus* self);

/* ImGuiTestGenericVars */
CIMGUI_TE_API ImGuiTestGenericVars * ImGuiTestGenericVars_ImGuiTestGenericVars();
CIMGUI_TE_API void ImGuiTestGenericVars_Clear(ImGuiTestGenericVars* self);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiTestGenericVars_destroy(ImGuiTestGenericVars* self);

/* ImGuiTestContext */
// Set test status and stop running. Usually called when running test logic from GuiFunc() only.
CIMGUI_TE_API void ImGuiTestContext_Finish(ImGuiTestContext* self, ImGuiTestStatus status);
// [Experimental] Run another test from the current test.
CIMGUI_TE_API ImGuiTestStatus ImGuiTestContext_RunChildTest(ImGuiTestContext* self, const char* test_name, int flags);
CIMGUI_TE_API bool ImGuiTestContext_IsError(ImGuiTestContext* self);
// Unless test->Flags has ImGuiTestFlags_NoGuiWarmUp, we run GuiFunc() twice before running TestFunc(). Those frames are called "WarmUp" frames.
CIMGUI_TE_API bool ImGuiTestContext_IsWarmUpGuiFrame(ImGuiTestContext* self);
CIMGUI_TE_API bool ImGuiTestContext_IsFirstGuiFrame(ImGuiTestContext* self);
// First frame where TestFunc is running (after warm-up frame).
CIMGUI_TE_API bool ImGuiTestContext_IsFirstTestFrame(ImGuiTestContext* self);
CIMGUI_TE_API bool ImGuiTestContext_IsGuiFuncOnly(ImGuiTestContext* self);
// [DEBUG] Generally called via IM_SUSPEND_TESTFUNC
CIMGUI_TE_API bool ImGuiTestContext_SuspendTestFunc(ImGuiTestContext* self, const char* file, int line);
CIMGUI_TE_API void ImGuiTestContext_LogEx(ImGuiTestContext* self, ImGuiTestVerboseLevel level, int flags, const char* fmt,  ...);
CIMGUI_TE_API void ImGuiTestContext_LogExV(ImGuiTestContext* self, ImGuiTestVerboseLevel level, int flags, const char* fmt, va_list args);
CIMGUI_TE_API void ImGuiTestContext_LogToTTY(ImGuiTestContext* self, ImGuiTestVerboseLevel level, const char* message, const char* message_end);
CIMGUI_TE_API void ImGuiTestContext_LogToDebugger(ImGuiTestContext* self, ImGuiTestVerboseLevel level, const char* message);
// ImGuiTestVerboseLevel_Debug or ImGuiTestVerboseLevel_Trace depending on context depth
CIMGUI_TE_API void ImGuiTestContext_LogDebug(ImGuiTestContext* self, const char* fmt,  ...);
// ImGuiTestVerboseLevel_Info
CIMGUI_TE_API void ImGuiTestContext_LogInfo(ImGuiTestContext* self, const char* fmt,  ...);
// ImGuiTestVerboseLevel_Warning
CIMGUI_TE_API void ImGuiTestContext_LogWarning(ImGuiTestContext* self, const char* fmt,  ...);
// ImGuiTestVerboseLevel_Error
CIMGUI_TE_API void ImGuiTestContext_LogError(ImGuiTestContext* self, const char* fmt,  ...);
CIMGUI_TE_API void ImGuiTestContext_LogBasicUiState(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_LogItemList(ImGuiTestContext* self, ImGuiTestItemList* list);
CIMGUI_TE_API void ImGuiTestContext_Yield(ImGuiTestContext* self, int count);
// Sleep for a given simulation time, unless in Fast mode
CIMGUI_TE_API void ImGuiTestContext_Sleep(ImGuiTestContext* self, float time_in_second);
// Standard short delay of io.ActionDelayShort (~0.15f), unless in Fast mode.
CIMGUI_TE_API void ImGuiTestContext_SleepShort(ImGuiTestContext* self);
// Standard regular delay of io.ActionDelayStandard (~0.40f), unless in Fast mode.
CIMGUI_TE_API void ImGuiTestContext_SleepStandard(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_SleepNoSkip(ImGuiTestContext* self, float time_in_second, float framestep_in_second);
CIMGUI_TE_API void ImGuiTestContext_SetRef_TestRef(ImGuiTestContext* self, ImGuiTestRef ref);
// Shortcut to SetRef(window->Name) which works for ChildWindow (see code)
CIMGUI_TE_API void ImGuiTestContext_SetRef_WindowPtr(ImGuiTestContext* self, ImGuiWindow* window);
CIMGUI_TE_API void ImGuiTestContext_GetRef(ImGuiTestRef* pOut, ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_WindowInfo(ImGuiTestItemInfo* pOut, ImGuiTestContext* self, ImGuiTestRef window_ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_WindowClose(ImGuiTestContext* self, ImGuiTestRef window_ref);
CIMGUI_TE_API void ImGuiTestContext_WindowCollapse(ImGuiTestContext* self, ImGuiTestRef window_ref, bool collapsed);
CIMGUI_TE_API void ImGuiTestContext_WindowFocus(ImGuiTestContext* self, ImGuiTestRef window_ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_WindowBringToFront(ImGuiTestContext* self, ImGuiTestRef window_ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_WindowMove(ImGuiTestContext* self, ImGuiTestRef window_ref, ImVec2 pos, ImVec2 pivot, int flags);
CIMGUI_TE_API void ImGuiTestContext_WindowResize(ImGuiTestContext* self, ImGuiTestRef window_ref, ImVec2 sz);
CIMGUI_TE_API bool ImGuiTestContext_WindowTeleportToMakePosVisible(ImGuiTestContext* self, ImGuiTestRef window_ref, ImVec2 pos_in_window);
CIMGUI_TE_API ImGuiWindow * ImGuiTestContext_GetWindowByRef(ImGuiTestContext* self, ImGuiTestRef window_ref);
CIMGUI_TE_API void ImGuiTestContext_PopupCloseOne(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_PopupCloseAll(ImGuiTestContext* self);
CIMGUI_TE_API ImGuiID ImGuiTestContext_PopupGetWindowID(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API ImGuiID ImGuiTestContext_GetID_TestRef(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API ImGuiID ImGuiTestContext_GetID_TestRefTestRef(ImGuiTestContext* self, ImGuiTestRef ref, ImGuiTestRef seed_ref);
// Find a point that has no windows // FIXME: This needs error return and flag to enable/disable forcefully finding void.
CIMGUI_TE_API void ImGuiTestContext_GetPosOnVoid(ImVec2* pOut, ImGuiTestContext* self, ImGuiViewport* viewport);
// Return a clickable point on window title-bar (window tab for docked windows).
CIMGUI_TE_API void ImGuiTestContext_GetWindowTitlebarPoint(ImVec2* pOut, ImGuiTestContext* self, ImGuiTestRef window_ref);
// Work pos and size of main viewport when viewports are disabled, or work pos and size of monitor containing main viewport when viewports are enabled.
CIMGUI_TE_API void ImGuiTestContext_GetMainMonitorWorkPos(ImVec2* pOut, ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_GetMainMonitorWorkSize(ImVec2* pOut, ImGuiTestContext* self);
// Reset state (use when doing multiple captures)
CIMGUI_TE_API void ImGuiTestContext_CaptureReset(ImGuiTestContext* self);
// Set capture file format (otherwise for video this default to EngineIO->VideoCaptureExtension)
CIMGUI_TE_API void ImGuiTestContext_CaptureSetExtension(ImGuiTestContext* self, const char* ext);
// Add window to be captured (default to capture everything)
CIMGUI_TE_API bool ImGuiTestContext_CaptureAddWindow(ImGuiTestContext* self, ImGuiTestRef ref);
// Trigger a screen capture of a single window (== CaptureAddWindow() + CaptureScreenshot())
CIMGUI_TE_API void ImGuiTestContext_CaptureScreenshotWindow(ImGuiTestContext* self, ImGuiTestRef ref, int capture_flags);
// Trigger a screen capture
CIMGUI_TE_API bool ImGuiTestContext_CaptureScreenshot(ImGuiTestContext* self, int capture_flags);
// Start a video capture
CIMGUI_TE_API bool ImGuiTestContext_CaptureBeginVideo(ImGuiTestContext* self);
CIMGUI_TE_API bool ImGuiTestContext_CaptureEndVideo(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_MouseMove(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_MouseMoveToPos(ImGuiTestContext* self, ImVec2 pos);
CIMGUI_TE_API void ImGuiTestContext_MouseTeleportToPos(ImGuiTestContext* self, ImVec2 pos, int flags);
CIMGUI_TE_API void ImGuiTestContext_MouseClick(ImGuiTestContext* self, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseClickMulti(ImGuiTestContext* self, int button, int count);
CIMGUI_TE_API void ImGuiTestContext_MouseDoubleClick(ImGuiTestContext* self, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseDown(ImGuiTestContext* self, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseUp(ImGuiTestContext* self, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseLiftDragThreshold(ImGuiTestContext* self, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseDragWithDelta(ImGuiTestContext* self, ImVec2 delta, int button);
CIMGUI_TE_API void ImGuiTestContext_MouseWheel(ImGuiTestContext* self, ImVec2 delta);
CIMGUI_TE_API void ImGuiTestContext_MouseWheelX(ImGuiTestContext* self, float dx);
CIMGUI_TE_API void ImGuiTestContext_MouseWheelY(ImGuiTestContext* self, float dy);
CIMGUI_TE_API void ImGuiTestContext_MouseMoveToVoid(ImGuiTestContext* self, ImGuiViewport* viewport);
CIMGUI_TE_API void ImGuiTestContext_MouseClickOnVoid(ImGuiTestContext* self, int button, ImGuiViewport* viewport);
CIMGUI_TE_API ImGuiWindow * ImGuiTestContext_FindHoveredWindowAtPos(ImGuiTestContext* self, const ImVec2* pos);
CIMGUI_TE_API bool ImGuiTestContext_FindExistingVoidPosOnViewport(ImGuiTestContext* self, ImGuiViewport* viewport, ImVec2* out);
CIMGUI_TE_API void ImGuiTestContext_MouseSetViewport(ImGuiTestContext* self, ImGuiWindow* window);
CIMGUI_TE_API void ImGuiTestContext_MouseSetViewportID(ImGuiTestContext* self, unsigned int viewport_id);
CIMGUI_TE_API void ImGuiTestContext_KeyDown(ImGuiTestContext* self, int key_chord);
CIMGUI_TE_API void ImGuiTestContext_KeyUp(ImGuiTestContext* self, int key_chord);
CIMGUI_TE_API void ImGuiTestContext_KeyPress(ImGuiTestContext* self, int key_chord, int count);
CIMGUI_TE_API void ImGuiTestContext_KeyHold(ImGuiTestContext* self, int key_chord, float time);
CIMGUI_TE_API void ImGuiTestContext_KeySetEx(ImGuiTestContext* self, int key_chord, bool is_down, float time);
// Input characters
CIMGUI_TE_API void ImGuiTestContext_KeyChars(ImGuiTestContext* self, const char* chars);
// Input characters at end of field
CIMGUI_TE_API void ImGuiTestContext_KeyCharsAppend(ImGuiTestContext* self, const char* chars);
// Input characters at end of field, press Enter
CIMGUI_TE_API void ImGuiTestContext_KeyCharsAppendEnter(ImGuiTestContext* self, const char* chars);
// Delete existing field then input characters
CIMGUI_TE_API void ImGuiTestContext_KeyCharsReplace(ImGuiTestContext* self, const char* chars);
// Delete existing field then input characters, press Enter
CIMGUI_TE_API void ImGuiTestContext_KeyCharsReplaceEnter(ImGuiTestContext* self, const char* chars);
// Mouse or Keyboard or Gamepad. In Keyboard or Gamepad mode, actions such as ItemClick or ItemInput are using nav facilities instead of Mouse.
CIMGUI_TE_API void ImGuiTestContext_SetInputMode(ImGuiTestContext* self, ImGuiInputSource input_mode);
CIMGUI_TE_API void ImGuiTestContext_NavMoveTo(ImGuiTestContext* self, ImGuiTestRef ref);
// Activate current selected item: activate button, tweak sliders/drags. Equivalent of pressing Space on keyboard, ImGuiKey_GamepadFaceUp on a gamepad.
CIMGUI_TE_API void ImGuiTestContext_NavActivate(ImGuiTestContext* self);
// Input into select item: input sliders/drags. Equivalent of pressing Enter on keyboard, ImGuiKey_GamepadFaceDown on a gamepad.
CIMGUI_TE_API void ImGuiTestContext_NavInput(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_ScrollTo(ImGuiTestContext* self, ImGuiTestRef ref, ImGuiAxis axis, float scroll_v, int flags);
CIMGUI_TE_API void ImGuiTestContext_ScrollToX(ImGuiTestContext* self, ImGuiTestRef ref, float scroll_x);
CIMGUI_TE_API void ImGuiTestContext_ScrollToY(ImGuiTestContext* self, ImGuiTestRef ref, float scroll_y);
CIMGUI_TE_API void ImGuiTestContext_ScrollToTop(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ScrollToBottom(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ScrollToItem(ImGuiTestContext* self, ImGuiTestRef ref, ImGuiAxis axis, int flags);
CIMGUI_TE_API void ImGuiTestContext_ScrollToItemX(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ScrollToItemY(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ScrollToTabItem(ImGuiTestContext* self, ImGuiTabBar* tab_bar, unsigned int tab_id);
CIMGUI_TE_API bool ImGuiTestContext_ScrollErrorCheck(ImGuiTestContext* self, ImGuiAxis axis, float expected, float actual, int* remaining_attempts);
CIMGUI_TE_API void ImGuiTestContext_ScrollVerifyScrollMax(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ItemInfo(ImGuiTestItemInfo* pOut, ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemInfoOpenFullPath(ImGuiTestItemInfo* pOut, ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API ImGuiID ImGuiTestContext_ItemInfoHandleWildcardSearch(ImGuiTestContext* self, const char* wildcard_prefix_start, const char* wildcard_prefix_end, const char* wildcard_suffix_start);
CIMGUI_TE_API void ImGuiTestContext_ItemInfoNull(ImGuiTestItemInfo* pOut, ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_GatherItems(ImGuiTestContext* self, ImGuiTestItemList* out_list, ImGuiTestRef parent, int depth);
CIMGUI_TE_API void ImGuiTestContext_ItemAction(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref, int flags, void* action_arg);
CIMGUI_TE_API void ImGuiTestContext_ItemClick(ImGuiTestContext* self, ImGuiTestRef ref, int button, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemDoubleClick(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemCheck(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemUncheck(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemOpen(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemClose(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemInput(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemNavActivate(ImGuiTestContext* self, ImGuiTestRef ref, int flags);
CIMGUI_TE_API void ImGuiTestContext_ItemActionAll(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref_parent, const ImGuiTestActionFilter* filter);
CIMGUI_TE_API void ImGuiTestContext_ItemOpenAll(ImGuiTestContext* self, ImGuiTestRef ref_parent, int depth, int passes);
CIMGUI_TE_API void ImGuiTestContext_ItemCloseAll(ImGuiTestContext* self, ImGuiTestRef ref_parent, int depth, int passes);
CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_int(ImGuiTestContext* self, ImGuiTestRef ref, int v);
CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_float(ImGuiTestContext* self, ImGuiTestRef ref, float f);
CIMGUI_TE_API void ImGuiTestContext_ItemInputValue_Str(ImGuiTestContext* self, ImGuiTestRef ref, const char* str);
CIMGUI_TE_API int ImGuiTestContext_ItemReadAsInt(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API float ImGuiTestContext_ItemReadAsFloat(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API bool ImGuiTestContext_ItemReadAsScalar(ImGuiTestContext* self, ImGuiTestRef ref, int data_type, void* out_data, int flags);
CIMGUI_TE_API const char * ImGuiTestContext_ItemReadAsString_TestRef(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API size_t ImGuiTestContext_ItemReadAsString_TestRefStr(ImGuiTestContext* self, ImGuiTestRef ref, char* out_buf, unsigned long out_buf_size);
CIMGUI_TE_API bool ImGuiTestContext_ItemExists(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API bool ImGuiTestContext_ItemIsChecked(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API bool ImGuiTestContext_ItemIsOpened(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ItemVerifyCheckedIfAlive(ImGuiTestContext* self, ImGuiTestRef ref, bool checked);
CIMGUI_TE_API void ImGuiTestContext_ItemHold(ImGuiTestContext* self, ImGuiTestRef ref, float time);
CIMGUI_TE_API void ImGuiTestContext_ItemHoldForFrames(ImGuiTestContext* self, ImGuiTestRef ref, int frames);
CIMGUI_TE_API void ImGuiTestContext_ItemDragOverAndHold(ImGuiTestContext* self, ImGuiTestRef ref_src, ImGuiTestRef ref_dst);
CIMGUI_TE_API void ImGuiTestContext_ItemDragAndDrop(ImGuiTestContext* self, ImGuiTestRef ref_src, ImGuiTestRef ref_dst, int button);
CIMGUI_TE_API void ImGuiTestContext_ItemDragWithDelta(ImGuiTestContext* self, ImGuiTestRef ref_src, ImVec2 pos_delta);
CIMGUI_TE_API void ImGuiTestContext_TabClose(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API bool ImGuiTestContext_TabBarCompareOrder(ImGuiTestContext* self, ImGuiTabBar* tab_bar, const char ** tab_order);
CIMGUI_TE_API void ImGuiTestContext_MenuAction(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_MenuActionAll(ImGuiTestContext* self, ImGuiTestAction action, ImGuiTestRef ref_parent);
CIMGUI_TE_API void ImGuiTestContext_MenuClick(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_MenuCheck(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_MenuUncheck(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_MenuCheckAll(ImGuiTestContext* self, ImGuiTestRef ref_parent);
CIMGUI_TE_API void ImGuiTestContext_MenuUncheckAll(ImGuiTestContext* self, ImGuiTestRef ref_parent);
CIMGUI_TE_API void ImGuiTestContext_ComboClick(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ComboClickAll(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_TableOpenContextMenu(ImGuiTestContext* self, ImGuiTestRef ref, int column_n);
CIMGUI_TE_API ImGuiSortDirection ImGuiTestContext_TableClickHeader(ImGuiTestContext* self, ImGuiTestRef ref, const char* label, int key_mods);
CIMGUI_TE_API void ImGuiTestContext_TableSetColumnEnabled(ImGuiTestContext* self, ImGuiTestRef ref, const char* label, bool enabled);
CIMGUI_TE_API void ImGuiTestContext_TableResizeColumn(ImGuiTestContext* self, ImGuiTestRef ref, int column_n, float width);
CIMGUI_TE_API const ImGuiTableSortSpecs * ImGuiTestContext_TableGetSortSpecs(ImGuiTestContext* self, ImGuiTestRef ref);
CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowPos(ImGuiTestContext* self, ImGuiViewport* viewport, const ImVec2* pos);
CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowSize(ImGuiTestContext* self, ImGuiViewport* viewport, const ImVec2* size);
CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_SetWindowFocus(ImGuiTestContext* self, ImGuiViewport* viewport);
CIMGUI_TE_API void ImGuiTestContext_ViewportPlatform_CloseWindow(ImGuiTestContext* self, ImGuiViewport* viewport);
CIMGUI_TE_API void ImGuiTestContext_DockClear(ImGuiTestContext* self, const char* window_name,  ...);
CIMGUI_TE_API void ImGuiTestContext_DockInto(ImGuiTestContext* self, ImGuiTestRef src_id, ImGuiTestRef dst_id, ImGuiDir split_dir, bool is_outer_docking, int flags);
CIMGUI_TE_API void ImGuiTestContext_UndockNode(ImGuiTestContext* self, unsigned int dock_id);
CIMGUI_TE_API void ImGuiTestContext_UndockWindow(ImGuiTestContext* self, const char* window_name);
CIMGUI_TE_API bool ImGuiTestContext_WindowIsUndockedOrStandalone(ImGuiTestContext* self, ImGuiWindow* window);
CIMGUI_TE_API bool ImGuiTestContext_DockIdIsUndockedOrStandalone(ImGuiTestContext* self, unsigned int dock_id);
CIMGUI_TE_API void ImGuiTestContext_DockNodeHideTabBar(ImGuiTestContext* self, ImGuiDockNode* node, bool hidden);
CIMGUI_TE_API void ImGuiTestContext_PerfCalcRef(ImGuiTestContext* self);
CIMGUI_TE_API void ImGuiTestContext_PerfCapture(ImGuiTestContext* self, const char* category, const char* test_name, const char* csv_file);
// Move windows covering 'window' at pos.
CIMGUI_TE_API void ImGuiTestContext__MakeAimingSpaceOverPos(ImGuiTestContext* self, ImGuiViewport* viewport, ImGuiWindow* over_window, const ImVec2* over_pos);
// FIXME: Aim to remove this system...
CIMGUI_TE_API void ImGuiTestContext__ForeignWindowsHideOverPos(ImGuiTestContext* self, const ImVec2* pos, ImGuiWindow ** ignore_list);
// FIXME: Aim to remove this system...
CIMGUI_TE_API void ImGuiTestContext__ForeignWindowsUnhideAll(ImGuiTestContext* self);

/* ImGuiCsvParser */
CIMGUI_TE_API ImGuiCsvParser * ImGuiCsvParser_ImGuiCsvParser(int columns);
CIMGUI_TE_API void ImGuiCsvParser_destroy(ImGuiCsvParser* self);
// Open and parse a CSV file.
CIMGUI_TE_API bool ImGuiCsvParser_Load(ImGuiCsvParser* self, const char* file_name);
// Free allocated buffers.
CIMGUI_TE_API void ImGuiCsvParser_Clear(ImGuiCsvParser* self);
CIMGUI_TE_API const char * ImGuiCsvParser_GetCell(ImGuiCsvParser* self, int row, int col);

/* ImGuiTestGatherTask */
CIMGUI_TE_API void ImGuiTestGatherTask_Clear(ImGuiTestGatherTask* self);

/* ImGuiTestInput */
CIMGUI_TE_API void ImGuiTestInput_ForKeyChord(ImGuiTestInput* pOut, ImGuiTestInput* self, int key_chord, bool down);
CIMGUI_TE_API void ImGuiTestInput_ForChar(ImGuiTestInput* pOut, ImGuiTestInput* self, unsigned short v);
CIMGUI_TE_API void ImGuiTestInput_ForViewportFocus(ImGuiTestInput* pOut, ImGuiTestInput* self, unsigned int viewport_id);
CIMGUI_TE_API void ImGuiTestInput_ForViewportSetPos(ImGuiTestInput* pOut, ImGuiTestInput* self, unsigned int viewport_id, const ImVec2* pos);
CIMGUI_TE_API void ImGuiTestInput_ForViewportSetSize(ImGuiTestInput* pOut, ImGuiTestInput* self, unsigned int viewport_id, const ImVec2* size);
CIMGUI_TE_API void ImGuiTestInput_ForViewportClose(ImGuiTestInput* pOut, ImGuiTestInput* self, unsigned int viewport_id);

/* ImGuiTestEngine */
CIMGUI_TE_API ImGuiTestEngine * ImGuiTestEngine_ImGuiTestEngine();
CIMGUI_TE_API void ImGuiTestEngine_destroy(ImGuiTestEngine* self);

/* ImGuiPerfToolEntry */
CIMGUI_TE_API ImGuiPerfToolEntry * ImGuiPerfToolEntry_ImGuiPerfToolEntry();
CIMGUI_TE_API ImGuiPerfToolEntry * ImGuiPerfToolEntry_ImGuiPerfToolEntry_constPerfToolEntryPtr(const ImGuiPerfToolEntry* rhs);
CIMGUI_TE_API void ImGuiPerfToolEntry_Set(ImGuiPerfToolEntry* self, const ImGuiPerfToolEntry* rhs);
// Automatically generated destructor
CIMGUI_TE_API void ImGuiPerfToolEntry_destroy(ImGuiPerfToolEntry* self);

/* ImGuiPerfToolBatch */
// FIXME: Misleading: nothing to destruct in that struct?
CIMGUI_TE_API void ImGuiPerfToolBatch_destroy(ImGuiPerfToolBatch* self);

/* ImGuiPerfTool */
CIMGUI_TE_API ImGuiPerfTool * ImGuiPerfTool_ImGuiPerfTool();
CIMGUI_TE_API void ImGuiPerfTool_destroy(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool_Clear(ImGuiPerfTool* self);
CIMGUI_TE_API bool ImGuiPerfTool_LoadCSV(ImGuiPerfTool* self, const char* filename);
CIMGUI_TE_API void ImGuiPerfTool_AddEntry(ImGuiPerfTool* self, ImGuiPerfToolEntry* entry);
CIMGUI_TE_API void ImGuiPerfTool_ShowPerfToolWindow(ImGuiPerfTool* self, ImGuiTestEngine* engine, bool* p_open);
CIMGUI_TE_API void ImGuiPerfTool_ViewOnly_Str(ImGuiPerfTool* self, const char* perf_name);
CIMGUI_TE_API void ImGuiPerfTool_ViewOnly_StrPtr(ImGuiPerfTool* self, const char ** perf_names);
CIMGUI_TE_API ImGuiPerfToolEntry * ImGuiPerfTool_GetEntryByBatchIdx(ImGuiPerfTool* self, int idx, const char* perf_name);
CIMGUI_TE_API bool ImGuiPerfTool_SaveHtmlReport(ImGuiPerfTool* self, const char* file_name, const char* image_file);
CIMGUI_TE_API bool ImGuiPerfTool_Empty(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool__Rebuild(ImGuiPerfTool* self);
CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleBuild_PerfToolBatchPtr(ImGuiPerfTool* self, ImGuiPerfToolBatch* batch);
CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleBuild_PerfToolEntryPtr(ImGuiPerfTool* self, ImGuiPerfToolEntry* batch);
CIMGUI_TE_API bool ImGuiPerfTool__IsVisibleTest(ImGuiPerfTool* self, const char* test_name);
CIMGUI_TE_API void ImGuiPerfTool__CalculateLegendAlignment(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool__ShowEntriesPlot(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool__ShowEntriesTable(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool__SetBaseline(ImGuiPerfTool* self, int batch_index);
CIMGUI_TE_API void ImGuiPerfTool__AddSettingsHandler(ImGuiPerfTool* self);
CIMGUI_TE_API void ImGuiPerfTool__UnpackSortedKey(ImGuiPerfTool* self, unsigned long long key, int* batch_index, int* entry_index, int* monotonic_index);

#endif // CIMGUI_TEST_ENGINE