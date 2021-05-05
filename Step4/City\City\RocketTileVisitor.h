/**
 * \file RocketTileVisitor.h
 *
 * \author Winnie Yang
 *
 * This class is a visitor that visits rocket tiles.
 */


#pragma once
#include "TileVisitor.h"
#include "TileRocketPad.h"


/**
 * Visits rocket tiles.
 */
class CRocketTileVisitor : public CTileVisitor
{
public:
	// Visit a rocket pad object
	virtual void VisitRocketPad(CTileRocketPad *pad);

	/// Getter for rocket pad
	/// 
	/// return mRocketPad
	CTileRocketPad* GetPadVisitor() { return mRocketPad; }

private:
	// Rocket pad
	CTileRocketPad* mRocketPad = nullptr;
};

