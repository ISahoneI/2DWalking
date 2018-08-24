#pragma once

#include <time.h>
#include <Windows.h>

class Timer
{
private:
	LARGE_INTEGER start;
	double frequence;
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
};