#include "Timer.h"

Timer* Timer::sIntance = nullptr;

Timer* Timer::Instance() {
	if (sIntance == nullptr) {
		sIntance = new Timer();
	}
	return sIntance;
}

Timer::Timer() {
	reset();
	timerScale = 1.0f;
	deltaTime = std::chrono::duration<float>(0.0f);
}

void Timer::reset() {
	startTime = std::chrono::system_clock::now();
}

float Timer::getDeltaTime() {
	return deltaTime.count();
}

void Timer::setTimeScale(float T) {
	timerScale = T;
}

float Timer::getTimeScale() {
	return timerScale;
}

void Timer::tick() {
	deltaTime = std::chrono::system_clock::now() - startTime;
}