#pragma once
#include <imgui.h>      
IMGUI_IMPL_API bool     ImguiImplSGLInit();
IMGUI_IMPL_API void     ImguiImplSGLShutdown();
IMGUI_IMPL_API void     ImguiImplSGLNewFrame();
IMGUI_IMPL_API void     ImguiImplSGLRenderDrawData(ImDrawData* draw_data);
IMGUI_IMPL_API bool     ImguiImplSGLCreateFontsTexture();
IMGUI_IMPL_API void     ImguiImplSGLDestroyFontsTexture();
IMGUI_IMPL_API bool     ImguiImplSGLCreateDeviceObjects();
IMGUI_IMPL_API void     ImguiImplSGLDestroyDeviceObjects();