/**
 * \file Clamp.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Clamp.h"


CClamp::CClamp(int x, int y, double rotation, double speed) : mPosition(x, y), mRotation(rotation), mSpeed(speed)
{
	SetEndpoint(Gdiplus::Point(x, y));
	SetRotation(rotation);
	SetSpeed(speed);
}
