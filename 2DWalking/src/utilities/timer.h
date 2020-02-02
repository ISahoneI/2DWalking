#pragma once

#include <time.h>
#include <stdbool.h>
#include <Windows.h>

class Timer
{
private:
	LARGE_INTEGER start;
	double frequence;

	float currentTime = 0.0f;

	///FPS Limiter
	double fpsLimit = 1.0 / 250.0;
	unsigned int fps = 0;
	double lastFrameTime = 0.0;
	double lastUpdateTime = 0.0;
	double deltaTime = 0.0;
	double currentFrame = 0.0;

public:
	Timer()
	{
		LARGE_INTEGER frequence;
		QueryPerformanceFrequency(&frequence);
		this->frequence = 1.0 / frequence.QuadPart;
		QueryPerformanceCounter(&start);
	}

	void reset()
	{
		QueryPerformanceCounter(&start);
	}

	float elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - start.QuadPart;
		return (float)(cycles * this->frequence);
	}

	void initFrameIteration(double windowTime)
	{
		currentFrame = windowTime;
		deltaTime = currentFrame - lastFrameTime;
		lastUpdateTime = currentFrame;
	}

	boolean fpsPassed() {
		boolean res = (currentFrame - lastFrameTime) >= fpsLimit;
		if (res) {
			resetFrameTime();
			fps++;
		}
		return res;
	}

	boolean oneSecondPassed() {
		boolean res = (elapsed() - currentTime) > 1.0f;
		if (res) {
			currentTime++;
		}
		return res;
	}

	void resetFps() {
		fps = 0;
	}

	void resetFrameTime() {
		lastFrameTime = currentFrame;
	}

	void resetUpdateTime() {
		lastUpdateTime = currentFrame;
	}

	unsigned int getFps() {
		return fps;
	}

	double getDeltaTime() {
		return deltaTime;
	}

	void setFpsLimit(double fpsLimit) {
		this->fpsLimit = 1.0 / fpsLimit;
	}

};