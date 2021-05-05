/**
 * \file MotionSource.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "MotionSource.h"
#include "MotionSink.h"

CMotionSource::CMotionSource()
{
}

void CMotionSource::SetAirPressure(double pressure)
{
    if (mMotionSink != nullptr)
    {
        mMotionSink->SetAirPressure(pressure);
    }
}

