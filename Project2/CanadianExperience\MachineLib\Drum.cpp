/**
 * \file Drum.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Drum.h"

using namespace std;

CDrum::CDrum()
{
}

void CDrum::Draw(Graphics* graphics, Point position)
{
	mDrum.DrawPolygon(graphics, position.X + mPosition.X + 275, position.Y + mPosition.Y);
}

void CDrum::SetAirPressure(double pressure)
{
	mOldPressure = mPressure;
	mPressure = pressure;
	if (mOldPressure < 1 && mPressure== 1)
	{
		if (mChannel != nullptr)
		{
			mChannel->Play();
		}
	}
}
