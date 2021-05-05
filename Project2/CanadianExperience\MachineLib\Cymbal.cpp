/**
 * \file Cymbal.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Cymbal.h"

using namespace std;

CCymbal::CCymbal()
{
}

void CCymbal::Draw(Graphics* graphics, Point position)
{
	mStand.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
	if (mMachineNumber == 2 && mPressure == 1)
	{
		mCymbal.SetRotation(-0.03);
		mCymbal.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y - 170);
	}
	else 
	{
		mCymbal.SetRotation(0);
		mCymbal.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y - 170);
	}
}

void CCymbal::SetAirPressure(double pressure)
{
	mOldPressure = mPressure;
	mPressure = pressure;
	if (mOldPressure < 1 && mPressure == 1)
	{
		if (mChannel != nullptr)
		{
			mChannel->Play();
		}
	}
}