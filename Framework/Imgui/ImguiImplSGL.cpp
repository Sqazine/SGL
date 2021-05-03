#include <cstdint>
#include "ImguiImplSGL.h"

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>                       // intptr_t
#else
#include <stdint.h> // intptr_t
#endif

bool ImguiImplSGLInit()
{
    ImGuiIO &io = ImGui::GetIO();
    io.BackendRendererName = "imgui_impl_sgl";
    return true;
}
void ImguiImplSGLShutdown()
{
    ImguiImplSGLDestroyDeviceObjects();
}
void ImguiImplSGLNewFrame()
{
}
void ImguiImplSGLRenderDrawData(ImDrawData *draw_data)
{
}
bool ImguiImplSGLCreateFontsTexture()
{
}
void ImguiImplSGLDestroyFontsTexture()
{
}
bool ImguiImplSGLCreateDeviceObjects()
{
}
void ImguiImplSGLDestroyDeviceObjects()
{
}