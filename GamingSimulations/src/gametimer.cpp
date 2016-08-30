#include "gametimer.h"

//return current time. Time is counted from beginning of simulation
float GameTimer::currentTime()
{
    LARGE_INTEGER t = { 0 };
    QueryPerformanceCounter(&t);
    return (float) ((t.QuadPart - startTime.QuadPart) * 1000.0f / frequency.QuadPart);

}

LARGE_INTEGER GameTimer::getStartTime()
{
    return startTime;
}

bool GameTimer::init()
{
    if (!QueryPerformanceCounter(&startTime))
    {
        return false;
    }
    
    if (!QueryPerformanceFrequency(&frequency))
    {
        return false;
    }
    return true;
}

void GameTimer::update()
{
}

bool GameTimer::shutdown()
{
    return true;
}

