/**
 * \file AirSource.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "AirSource.h"

CAirSource::CAirSource()
{
}

void CAirSource::SetAirPressure(double pressure)
{
	if (mAirSink != nullptr)
	{
		mAirSink->SetAirPressure(pressure);
	}
}

