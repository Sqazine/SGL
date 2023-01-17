#include "Window.h"
#include <unordered_map>
#include <windows.h>
Window::Window(const std::string &title, const SGL::Vector2u32 &extent)
{
	//初始化SDL
	SDL_Init(SDL_INIT_VIDEO);
	m_Handle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(extent.x), static_cast<int>(extent.y), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	m_SDLRenderer = SDL_CreateRenderer(m_Handle, -1, SDL_RENDERER_ACCELERATED);
	m_DefaultRenderTexture = SDL_CreateTexture(m_SDLRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, static_cast<int>(extent.x), static_cast<int>(extent.y));
}

Window::~Window()
{
	SDL_DestroyRenderer(m_SDLRenderer);
	SDL_Quit();
	SDL_DestroyWindow(m_Handle);
}

void Window::ResizeExtent(const SGL::Vector2u32 &extent)
{
}
SGL::Vector2u32 Window::GetExtent() const
{
	SGL::Vector2u32 extent;
	SDL_GetWindowSize(m_Handle, (int32_t *)&extent.x, (int32_t *)&extent.y);
	return extent;
}

std::string Window::GetTitle() const
{
	return SDL_GetWindowTitle(m_Handle);
}

void Window::SetTitle(const std::string &title)
{
	SDL_SetWindowTitle(m_Handle, title.c_str());
}

SDL_Window *Window::GetHandle() const
{
	return m_Handle;
}

void Window::SetBufferData(void *data)
{
	SDL_UpdateTexture(m_DefaultRenderTexture, nullptr, data, GetExtent().x * 4);
	SDL_RenderCopyEx(m_SDLRenderer, m_DefaultRenderTexture, nullptr, nullptr, 0.0f, nullptr, SDL_FLIP_VERTICAL);
	SDL_RenderPresent(m_SDLRenderer);
}