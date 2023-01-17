#include "Timer.h"
#include <chrono>

static std::chrono::high_resolution_clock::time_point s_lastTime;
static bool s_initialized = false;

float Timer::deltaTime = 0.0f;

void Timer::CalcDeltaTime()
{
	if (!s_initialized)
	{
		s_lastTime = std::chrono::high_resolution_clock::now();
		s_initialized = true;
		deltaTime = 0.0f;
		return;
	}

	auto now = std::chrono::high_resolution_clock::now();
	auto delta = std::chrono::duration<double>(now - s_lastTime).count();
	s_lastTime = now;

	deltaTime = static_cast<float>(delta);
}