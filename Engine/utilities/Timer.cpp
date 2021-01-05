#include "Timer.h"
#include <SDL2/SDL.h>
uint32_t Timer::currentTime = 0;
float Timer::deltaTime = 0.0f;

void Timer::CalcDeltaTime()
{
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_CurrentTime + 16));
	deltaTime = (SDL_GetTicks() - currentTime) / 1000.0f;
	currentTime = SDL_GetTicks();
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
}
