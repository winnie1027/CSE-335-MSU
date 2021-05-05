/**
 * \file LaunchRocketVisitor.h
 *
 * \author Winnie Yang
 *
 * Visitor that launches the rocket.
 */


#pragma once
#include "TileVisitor.h"
#include "TileRocketPad.h"
#include "Rocket.h"


/**
 * Visitor class to visit rocket launch pad.
 */
class CLaunchRocketVisitor : public CTileVisitor
{
public:
	// Constructor
	CLaunchRocketVisitor::CLaunchRocketVisitor(std::shared_ptr<CTile> pad);

	// Rocket pad visitor
	virtual void VisitRocketPad(CTileRocketPad* tile) override;

	// Launches rocket
	void LaunchRocket();

private:
	// Launch
	CTileRocketPad* mLauncher = nullptr;

	// Land
	CTileRocketPad* mLanding = nullptr;

	// Rockey
	std::shared_ptr<CRocket> mRocket = nullptr;

	// Tile
	std::shared_ptr<CTile> mTile = nullptr;
};

