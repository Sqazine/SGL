#include "Window.h"

Window::Window(const std::string title, uint32_t w, uint32_t h)
	:m_Width(w),m_Height(h),m_Title(title)
{
	m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

Window::~Window()
{
	SDL_DestroyWindow(m_Window);
}

uint32_t Window::GetWidth() const
{
	return m_Width;
}

uint32_t Window::GetHeight() const
{
	return m_Height;
}

const std::string& Window::GetTitle() const
{
	return m_Title;
}

void Window::SetTitle(const std::string& name)
{
	m_Title = name;
}

SDL_Window* Window::GetHandle() const
{
	return m_Window;
}
