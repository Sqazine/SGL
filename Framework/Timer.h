#pragma once
class Timer
{
public:
	~Timer() {}
	static float deltaTime;
	static void CalcDeltaTime();
private:
	Timer() {}
};

