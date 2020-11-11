#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
#include <string>
class Window
{
public:
	Window(const std::string title, uint32_t w, uint32_t h);
	~Window();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	const std::string& GetTitle() const;
	void SetTitle(const std::string& name);

	SDL_Window* GetHandle() const;
private:
	SDL_Window* m_Window;
	std::string m_Title;
	uint32_t m_Width, m_Height;
};

