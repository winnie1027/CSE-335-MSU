/**
 * \file DecorItem.cpp
 *
 * \author Caroline Gormely
 */

#include "pch.h"
#include "DecorItem.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The game this car decor item is in 
* \param imagePair the pair of images for this item
*/
CDecorItem::CDecorItem(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair)
{
  mDecorImage = imagePair.first;
} 

/**
* brief Load the attributes for a decor item node.
* \param node The Xml node we are loading the item from
*/
void CDecorItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
	mStartX = node->GetAttributeDoubleValue(L"x", 0);
    mStartY = node->GetAttributeDoubleValue(L"y", 0);
	mRepeatX = node->GetAttributeDoubleValue(L"repeat-x", 0);
	mRepeatY = node->GetAttributeDoubleValue(L"repeat-y", 0);
}


/**
 * Draws the decor images repeatedly.
 * \param graphics 
 */
void CDecorItem::Draw(Gdiplus::Graphics* graphics)
{
	//Get the original position (not in tile units)
	double startX = GetPosition().X() / GetTileWidth();
	double startY = GetPosition().Y() / GetTileWidth();

	//Keeps the decor item stationary
	if (startX ==  static_cast<double>(mRepeatX - 1) || startY == static_cast<double>(mRepeatY - 1)) 
	{
          startX = mStartX;
          startY = mStartY;
    }

	//Repeat drawing the tile to form a block of tiles
	for (double x = startX; x < startX + mRepeatX; x++)
	{
		for (double y = startY; y < startY + mRepeatY; y++)
		{  
            SetLocation(static_cast<double>(x * GetTileWidth()),
                        static_cast<double>(y * GetTileWidth()));
            CItem::Draw(graphics);
		}
	}

}

/**
* Destructor
*/
CDecorItem::~CDecorItem()
{
}
