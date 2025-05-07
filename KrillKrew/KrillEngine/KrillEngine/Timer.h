#pragma once

#include <chrono>
#include "Log.h"

class Timer {
private:
	static Timer* instance;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point lastTime;
	std::chrono::duration<float> deltaTime;
	float timerScale;

	// fps count and cap
	int frameCount;
	float fps;
	float fpsUpdateInterval; // seconds
	float fpsElapsedTime;

protected:
	Timer();

public:
	static Timer* Instance();
	void reset();
	void tick();

	float getDeltaTime() const;
	void setTimeScale(float T);
	float getTimeScale() const;
	float getFps() const;

};