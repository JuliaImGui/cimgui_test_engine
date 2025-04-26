# Makefile for *nix systems. Not tested on Windows.

TE_ROOT = ./imgui_test_engine/imgui_test_engine

SOURCES = $(TE_ROOT)/imgui_capture_tool.cpp $(TE_ROOT)/imgui_te_context.cpp $(TE_ROOT)/imgui_te_coroutine.cpp
SOURCES += $(TE_ROOT)/imgui_te_engine.cpp $(TE_ROOT)/imgui_te_exporters.cpp $(TE_ROOT)/imgui_te_perftool.cpp
SOURCES += $(TE_ROOT)/imgui_te_ui.cpp $(TE_ROOT)/imgui_te_utils.cpp
SOURCES += cimgui_te.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -std=c++14 -shared -fPIC -DIMGUI_TEST_ENGINE_ENABLE_COROUTINE_STDTHREAD_IMPL -DIMGUI_ENABLE_TEST_ENGINE
CXXFLAGS += -I$(TE_ROOT) -I./cimgui -I./cimgui/imgui
CXXFLAGS += -Wfatal-errors -Wall

cimgui_te.so: cimgui_te.cpp cimgui_te.h
	$(CXX) $(CXXFLAGS) $(SOURCES) -o cimgui_te.so

example: example.c cimgui_te.so
	make -C cimgui        # Make cimgui.so
	cp cimgui/cimgui.so . # Copy to the current directory for convenience
	$(CC) -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS -I./cimgui -L. -l:cimgui_te.so -l:cimgui.so example.c -o example

all: cimgui_te.so

clean:
	rm -f cimgui_te.so *.o example
