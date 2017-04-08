
#pragma once

#include <Windows.h>

class Timer
{
    static __int64 counterStart;
    static double frequency;
public:
    static void start();
    static double stop();
};
