/**
 * \file Item.cpp
 *
 * \author 
 */

#include <string>
#include <sstream>

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;


/** Constructor
* \param game The game this item is in
* \param imagePair the pair of images for this item
*/
CItem::CItem(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair)
{
    mGame = game;
    mItemImage = imagePair.first;
}

/**
* brief Load the attributes for a item node.
* \param node The Xml node we are loading the item from
*/
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // Setting the position of the item to the position in the XML tag
    mTagName = node->GetName();
    mName = node->GetAttributeValue(L"name", L"").c_str();
    mID = node->GetAttributeValue(L"id", L"");

    double pxlX = node->GetAttributeDoubleValue(L"x", 0) * mTile; 
    double pxlY = node->GetAttributeDoubleValue(L"y", 0) * mTile;
    mP.Set(pxlX, pxlY);
}

/**
*  Destructor
*/
CItem::~CItem()
{
}


/**
 * Draws non decor/background items - ( the boats, cars, cargo, hero)
 * @param graphics 
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    if (mItemImage)
    // Draws image as normal.
    {
        double wid = mItemImage->GetWidth();
        double hit = mItemImage->GetHeight();

        graphics->DrawImage(mItemImage.get(),
            (float(mP.X())),
            (float(mP.Y())),
            (float)mItemImage->GetWidth() + 2, //account for rounding error
            (float)mItemImage->GetHeight() + 2);
    }
}



