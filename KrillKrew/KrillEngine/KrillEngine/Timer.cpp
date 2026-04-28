#include "Timer.h"

Timer* Timer::instance = nullptr;

Timer* Timer::Instance() {
	if (instance == nullptr) {
		instance = new Timer();
	}
	return instance;
}

Timer::Timer()
	: timerScale(1.0f), deltaTime(0.0f), frameCount(0), fps(0.0f), fpsUpdateInterval(1.0f), fpsElapsedTime(0.0f) {
	reset();
}

void Timer::reset() {
	startTime = std::chrono::high_resolution_clock::now();
	lastTime = startTime;
	deltaTime = std::chrono::duration<float>(0.0f);
	frameCount = 0;
	fps = 0.0f;
	fpsElapsedTime = 0.0f;
}

float Timer::getDeltaTime() const {
	return deltaTime.count();
}

void Timer::setTimeScale(float T) {
	timerScale = T;
}

float Timer::getTimeScale() const {
	return timerScale;
}

void Timer::tick() 
{
	auto now = std::chrono::high_resolution_clock::now();
	deltaTime = (now - lastTime) * timerScale;
	lastTime = now;

	// FPS tracking
	fpsElapsedTime += deltaTime.count();
	frameCount++;
	//KK_CORE_INFO("fpsElapsedTime: {0}", fpsElapsedTime);
	if (fpsElapsedTime >= fpsUpdateInterval) {
		fps = frameCount / fpsElapsedTime;
		
		frameCount = 0;
		fpsElapsedTime = 0.0f;
	}
	//KK_CORE_INFO("FPS: {0}", fps);
	
}

float Timer::getFps() const
{
	return fps;
}