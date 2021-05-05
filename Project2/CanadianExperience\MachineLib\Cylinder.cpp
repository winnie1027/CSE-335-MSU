/**
 * \file Cylinder.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Cylinder.h"

 /// to the tubing connector in rotations
const double ConnectorAngle = -0.17;

/// Distance from bottom center of the cylinder to the tubing connector
const double ConnectorDistance = 24.5;


CCylinder::CCylinder()
{
	mAirSink.SetComponent(this);
}

void CCylinder::Draw(Graphics* graphics, Point position)
{
	mMount.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
	auto rotation = mRam.GetRotation();
	if (rotation == 0.25)
	{
		// Drum ram
		mRam.DrawPolygon(graphics, position.X + mPosition.X + (mAirPressure * (mMaxExtent * mExtent)), position.Y + mPosition.Y);
	}
	else if (rotation == 0.5)
	{
		// Cymbal ram
		mRam.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y + (mAirPressure * (mMaxExtent * mExtent)));
	}
	else
	{
		// Chime rams
		mRam.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y - (mAirPressure * (mMaxExtent * mExtent)));
	}
	mCylinder.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
}

void CCylinder::SetPosition(int x, int y)
{
	mPosition.X = x;
	mPosition.Y = y;

	CComponent::SetPosition(x, y);
	double airX = x + cos(ConnectorAngle * M_PI * 2) * ConnectorDistance;
	double airY = y + sin(ConnectorAngle * M_PI * 2) * ConnectorDistance;

	mAirSink.SetEndpoint(Point(airX-15, airY+5));
}

void CCylinder::SetAirPressure(double pressure)
{
	mAirPressure = pressure;
	mMotionSource.SetAirPressure(pressure);
}

void CCylinder::SetMotionSink(std::shared_ptr<CInstrument> instrument)
{
	mInstrument = instrument;
	mMotionSource.SetAirSink(mInstrument->GetSink());
	mInstrument->GetSink()->SetMotionSource(&mMotionSource);
}