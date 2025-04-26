#include "cimgui_te.h"

int main(int argc, char** argv) {
    ImGuiTestEngine* engine = cImGuiTestEngine_CreateContext();
    cImGuiTestEngine_DestroyContext(engine);
    printf("Created and destroyed engine\n");

    ImGuiPerfTool* perf = ImGuiPerfTool_ImGuiPerfTool();
    ImGuiPerfTool_destroy(perf);
    printf("Created and destroyed perftool\n");

    return 0;
}
