/**
 * \file DeleteRocketVisitor.h
 *
 * \author Winnie Yang
 *
 * This visitor class deletes the rocket launch pad.
 */



#pragma once
#include "TileVisitor.h"
#include "TileRocketPad.h"
#include "Rocket.h"


class CDeleteRocketVisitor : public CTileVisitor
{
public:
	// Constructor
	CDeleteRocketVisitor::CDeleteRocketVisitor(CTileRocketPad *pad);

	// Rocket pad visitor
	virtual void VisitRocketPad(CTileRocketPad* pad) override;

private:
	// rocket pad
	CTileRocketPad* mRocketTile = nullptr;

	bool mRocket = false;
};

