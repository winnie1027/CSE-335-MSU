/**
 * \file RocketTileVisitor.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "RocketTileVisitor.h"


/**
 * Visitor that visits rocket pads.
 * \param rocketPad 
 */
void CRocketTileVisitor::VisitRocketPad(CTileRocketPad* rocketPad)
{
	if (rocketPad->GetVisitor() != nullptr)
	{
		if (mRocketPad == nullptr)
		{
			mRocketPad = rocketPad;
		}
	}
}