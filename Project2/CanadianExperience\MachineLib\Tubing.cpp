/**
 * \file Tubing.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Tubing.h"

using namespace Gdiplus;

CTubing::CTubing()
{
	mAirSink.SetComponent(this);
}

void CTubing::Draw(Graphics* graphics, Point position)
{
	Pen brush(Color(255, 0, 0, 0), 2);

	int i = 0;
	int x = position.X + GetPosition().X;
	int y = position.Y + GetPosition().Y;

	auto point1X = mAirSource->GetEndpoint().X + x;
	auto point1Y = mAirSource->GetEndpoint().Y + y;

	auto point2X = point1X - sin(mAirSource->GetRotation() * M_PI * 2) * mAirSource->GetSpeed();
	auto point2Y = point1Y + cos(mAirSource->GetRotation() * M_PI * 2) * mAirSource->GetSpeed();

	auto point4X = mClamps[i]->GetEndpoint().X + x;
	auto point4Y = mClamps[i]->GetEndpoint().Y + y;

	auto point3X = point4X + sin(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();
	auto point3Y = point4Y - cos(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();

	Point p1 = Point(point1X, point1Y);
	Point p2 = Point(point2X, point2Y);
	Point p3 = Point(point3X, point3Y);
	Point p4 = Point(point4X, point4Y);

	graphics->DrawBezier(&brush, p1, p2, p3, p4);

	auto saveSM = graphics->GetSmoothingMode();
	graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

	// Code to draw the Bezier curve segment

	graphics->SetSmoothingMode(saveSM);

	for (i; i < mClamps.size() - 1; i++)
	{
		auto point1X = mClamps[i]->GetEndpoint().X + x;
		auto point1Y = mClamps[i]->GetEndpoint().Y + y;

		auto point2X = point1X - sin(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();
		auto point2Y = point1Y + cos(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();

		auto point4X = mClamps[i+1]->GetEndpoint().X + x;
		auto point4Y = mClamps[i+1]->GetEndpoint().Y + y;

		auto point3X = point4X + sin(mClamps[i+1]->GetRotation() * M_PI * 2) * mClamps[i+1]->GetSpeed();
		auto point3Y = point4Y - cos(mClamps[i+1]->GetRotation() * M_PI * 2) * mClamps[i+1]->GetSpeed();

		Point p1 = Point(point1X, point1Y);
		Point p2 = Point(point2X, point2Y);
		Point p3 = Point(point3X, point3Y);
		Point p4 = Point(point4X, point4Y);

		graphics->DrawBezier(&brush, p1, p2, p3, p4);

		auto saveSM = graphics->GetSmoothingMode();
		graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

		// Code to draw the Bezier curve segment

		graphics->SetSmoothingMode(saveSM);
	}

		point1X = mClamps[i]->GetEndpoint().X + x;
		point1Y = mClamps[i]->GetEndpoint().Y + y;

		point2X = point1X - sin(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();
		point2Y = point1Y + cos(mClamps[i]->GetRotation() * M_PI * 2) * mClamps[i]->GetSpeed();

		point4X = mAirSource->GetSink()->GetEndpoint().X + x;
		point4Y = mAirSource->GetSink()->GetEndpoint().Y + y;

		point3X = point4X + sin(mAirSource->GetSink()->GetRotation() * M_PI * 2) * mAirSource->GetSink()->GetSpeed();
		point3Y = point4Y - cos(mAirSource->GetSink()->GetRotation() * M_PI * 2) * mAirSource->GetSink()->GetSpeed();

		p1 = Point(point1X, point1Y);
		p2 = Point(point2X, point2Y);
		p3 = Point(point3X, point3Y);
		p4 = Point(point4X, point4Y);

		graphics->DrawBezier(&brush, p1, p2, p3, p4);

		saveSM = graphics->GetSmoothingMode();
		graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

		// Code to draw the Bezier curve segment

		graphics->SetSmoothingMode(saveSM);
}

void CTubing::SetAirPressure(double pressure)
{
	if (mAirSource != nullptr)
	{ 
		mAirSource->SetAirPressure(pressure); 
	}
}

void CTubing::AddClamp(int x, int y, double rotation, double speed)
{
	auto clamp = std::make_shared<CClamp>(x, y, rotation, speed);
	mClamps.push_back(clamp);
}
