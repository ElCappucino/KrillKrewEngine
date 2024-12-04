#pragma once

#include <chrono>

class Timer {
private:
	static Timer* sIntance;
	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<float> deltaTime;
	float timerScale;

protected:
	Timer();

public:
	static Timer* Instance();
	void reset();
	float getDeltaTime();
	void setTimeScale(float T);
	float getTimeScale();
	void tick();
};