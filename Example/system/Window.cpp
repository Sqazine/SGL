#include "Window.h"

Window::Window(const std::string& title, const SGLVector2u32 &extent)
{
	m_Handle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(extent.x), static_cast<int>(extent.y), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

Window::~Window()
{
	SDL_DestroyWindow(m_Handle);
}

void Window::ResizeExtent(const SGLVector2u32 &extent)
{
}
SGLVector2u32 Window::GetExtent() const
{
	SGLVector2u32 extent;
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
