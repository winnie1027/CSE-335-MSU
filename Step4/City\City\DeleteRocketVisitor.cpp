/**
 * \file DeleteRocketVisitor.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "DeleteRocketVisitor.h"

CDeleteRocketVisitor::CDeleteRocketVisitor(CTileRocketPad *pad) : mRocketTile(pad) 
{
}

void CDeleteRocketVisitor::VisitRocketPad(CTileRocketPad *pad)
{
	if (pad == mRocketTile)
	{
		return;
	}
	if (mRocket)
	{
		pad->SetVisitor(nullptr);
	}
	else
	{
		pad->SetVisitor(mRocketTile->GetVisitor());
		pad->GetVisitor()->SetLaunchingPad(pad);
		mRocket = true;
	}
}

