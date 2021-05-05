/**
 * \file TileRocketPad.cpp
 *
 * \author 
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "Tile.h"
#include "City.h"
#include "TileRocketPad.h"
#include "MemberReport.h"
#include "Rocket.h"
#include "RocketTileVisitor.h"
#include "DeleteRocketVisitor.h"


using namespace std;
using namespace Gdiplus;

/// The image to display for the rocket pad
const wstring RocketPadImage = L"pad.png";


/** Constructor
* \param city The city this is a member of
*/
CTileRocketPad::CTileRocketPad(CCity* city) : CTile(city)
{
    SetImage(RocketPadImage);
    CRocketTileVisitor rocketVisitor;
    city->Accept(&rocketVisitor);
    if (rocketVisitor.GetPadVisitor() == nullptr)
    {
        mRocketPad = make_shared<CRocket>(city);
        mRocketPad->SetLaunchingPad(this);
    }
}


/**  Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileRocketPad::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"rocketpad");

    return itemNode;
}


/**
 * Generate a report for this  tile.
 * @param report
*/
void CTileRocketPad::Report(std::shared_ptr<CMemberReport> report)
{
    wstringstream str;
    str << L"Rocket Pad";

    report->SetReport(str.str());
}

/**
 * Indicate that this object is about to be deleted by
 * begin dragged into the trash can. If the function
 * override returns false, the delete will not occur.
 * @return true if okay to delete.
*/
bool CTileRocketPad::PendingDelete()
{
    if (mRocketPad != nullptr)
    {
        CDeleteRocketVisitor rocket(this);
        GetCity()->Accept(&rocket);
    }
    return true;
}

/**
 * This function is called when the rocket has
 * landed on some other pad. It is no longer accessible to
 * this pad.
*/
void CTileRocketPad::RocketIsGone()
{
    if (mRocketPad != nullptr)
    {
        mRocketPad = nullptr;
    }
}

/**
 * This function is called when the rocket has landed on this
 * pad. This pad should now become the launching pad.
*/
void CTileRocketPad::RocketHasLanded()
{
    if (mRocketPad != nullptr)
    {
        mRocketPad.get()->SetLaunchingPad(this);
    }
}


/**
 * This function draws the rocket.
 * \param graphics 
 */
void CTileRocketPad::Draw(Gdiplus::Graphics* graphics)
{
    CTile::Draw(graphics);
    if (mRocketPad != nullptr)
    {
        mRocketPad->Draw(this, graphics);
    }
}


/**
 * This function updates the rocket pad.
 * \param elapsed
 */
void CTileRocketPad::Update(double elapsed)
{
    if (mRocketPad != nullptr)
    {
        mRocketPad->Update(this, elapsed);
    }
}