#pragma once

#include <windows.h>

class Timestamp
{
public:
    Timestamp()
    {
        QueryPerformanceFrequency(&_frequency);
        QueryPerformanceCounter(&_startCount);
    }
    ~Timestamp()
    {}

    void    update()
    {
        QueryPerformanceCounter(&_startCount);
    }
    /**
    *   获取当前秒
    */
    double getElapsedSecond()
    {
        return  getElapsedTimeInMicroSec() * 0.000001;
    }
    /**
    *   获取毫秒
    */
    double getElapsedTimeInMilliSec()
    {
        return this->getElapsedTimeInMicroSec() * 0.001;
    }
    /**
    *   获取微妙
    */
    double getElapsedTimeInMicroSec()
    {
        LARGE_INTEGER endCount;
        QueryPerformanceCounter(&endCount);

        double  startTimeInMicroSec =   _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
        double  endTimeInMicroSec   =   endCount.QuadPart * (1000000.0 / _frequency.QuadPart);

        return  endTimeInMicroSec - startTimeInMicroSec;
    }
protected:
    LARGE_INTEGER   _frequency;
    LARGE_INTEGER   _startCount;
};