/**
 * \file Instrument.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Instrument.h"

using namespace std;

CInstrument::CInstrument() : mMotionSink(this)
{

}

void CInstrument::SetAudioChannel(shared_ptr<CWavChannel> channel)
{
}

void CInstrument::Draw(Graphics* graphics, Point position)
{
}

void CInstrument::SetAirPressure(double pressure)
{
}
