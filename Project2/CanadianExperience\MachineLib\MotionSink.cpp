/**
 * \file MotionSink.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "MotionSink.h"
#include "MotionSource.h"
#include "Instrument.h"

CMotionSink::CMotionSink(CInstrument* instrument)
{
    mInstrument = instrument;
}

void CMotionSink::SetAirPressure(double pressure)
{
    if (mInstrument != nullptr)
    {
        mInstrument->SetAirPressure(pressure);
    }
}
