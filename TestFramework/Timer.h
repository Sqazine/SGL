#pragma once
#include <cstdint>
class Timer
{
public:
	~Timer() {}
	static float deltaTime;
	static void CalcDeltaTime();
private:
	Timer() {}
	static uint32_t currentTime;
};

