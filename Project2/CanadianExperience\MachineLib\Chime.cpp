/**
 * \file Chime.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Chime.h"

using namespace std;

/// The location in the hammer image for the pivot point X
const double HammerPivotX = 33;

/// The location in the hammer image for the pivot point X
const double HammerPivotY = 10;

/// Amount to rotate hammer away from chime in unit rotations
const double HammerRotation = 0.08;

CChime::CChime()
{

}

void CChime::Draw(Graphics* graphics, Point position)
{
	//int x = position.X + GetPosition().X;
	//int y = position.Y + GetPosition().Y;

	mMount.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
	if (mPressure == 0)
	{
		mHammer.SetRotation(HammerRotation);
		mHammer.DrawPolygon(graphics, position.X + mPosition.X - 5, position.Y + mPosition.Y + HammerPivotY);
		mChime.SetRotation(0.5);
		mChime.DrawPolygon(graphics, position.X + mPosition.X - 60, position.Y + mPosition.Y - 60);
	}
	else if (mPressure == 1)
	{
		mHammer.SetRotation(0);
		mHammer.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
		if (mMachineNumber == 2)
		{
			mChime.SetRotation(0.52);
			mChime.DrawPolygon(graphics, position.X + mPosition.X - 60, position.Y + mPosition.Y - 60);
		}
		else 
		{
			mChime.DrawPolygon(graphics, position.X + mPosition.X - 60, position.Y + mPosition.Y - 60);
		}
	}
}

void CChime::SetAirPressure(double pressure)
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