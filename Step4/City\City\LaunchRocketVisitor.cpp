/**
 * \file LaunchRocketVisitor.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "LaunchRocketVisitor.h"


CLaunchRocketVisitor::CLaunchRocketVisitor(std::shared_ptr<CTile> pad) : mTile(pad)
{
}


/**
 * Visits rocket pad
 * \param pad Rocket pad
 */
void CLaunchRocketVisitor::VisitRocketPad(CTileRocketPad* pad)
{
	if (mTile.get() == pad)
	{
		mLanding = pad;
	}
	if (pad->GetVisitor() != nullptr)
	{
		mLauncher = pad;
		mRocket = pad->GetVisitor();
	}
}


/**
 * Rocket launcher
 */
void CLaunchRocketVisitor::LaunchRocket()
{
	if (mRocket == nullptr || mRocket->InFlight())
	{
		return;
	}
	if (mLanding == nullptr || mLauncher == nullptr)
	{
		return;
	}
	mRocket->SetLandingPad(mLanding);
	mLanding->SetVisitor(mRocket);
}