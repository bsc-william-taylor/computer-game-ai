
#include "Timer.h"

__int64 Timer::counterStart = 0;

double Timer::frequency = 0.0;

void Timer::start()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
    frequency = double(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;
}

double Timer::stop()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - counterStart) / frequency;
}