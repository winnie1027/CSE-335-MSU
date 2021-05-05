/**
 * \file Cargo.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "Cargo.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/** Constructor
* \param game The game this cargo item is in
* \param imagePair The pair of images for this item
*/
CCargo::CCargo(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair)
{
   mCarriedImage = imagePair.second;
}


/**
 * Loads cargo from XML
 * \param node 
 */
void CCargo::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
    mStartX = GetPosition().X();
    mStartY *= GetTileWidth();
    SetLocation(GetPosition().X(), mStartY);
    SetStartingLocation(GetPosition());
    mEats = node->GetAttributeValue(L"eats", L"");
}



/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CCargo::ClickTest(int x, int y)
{
    double wid = GetWidth();
    double hit =GetHeight();
    

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetPosition().X();
    double testY = y - GetPosition().Y();
    
    
    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = GetImagePixelFormat(); 
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        GetImagePixel((int)testX, (int)testY, color);
        return color.GetAlpha() != 0;
    }
    else 
    {
        return true;
    }
    
    
}

/**
 * Draws the cargo item
 * @param graphics
 */
void CCargo::Draw(Gdiplus::Graphics* graphics)
{
    
    if (mCarried) 
    {

        if (mCarriedImage)
        {

            double wid = mCarriedImage->GetWidth();
            double hit = mCarriedImage->GetHeight();

           // double check = mP.X();
           graphics->DrawImage(mCarriedImage.get(),
                (float(CItem::GetPosition().X())),
                (float(CItem::GetPosition().Y())),
                (float)mCarriedImage->GetWidth(),
                (float)mCarriedImage->GetHeight());
        }
    }

    else 
    { 
        // everything gets drawn as normal besides the protector after 45 seconds have passed
        if (!(this->GetTagName() == L"protector" && this->GetGameTime() > 45 ))
        {
            CItem::Draw(graphics);
        }     
    }

}

/**
* Set cargo back to the location
*/
void CCargo::Reset()
{
    SetLocation(GetStartingPosition().X(), GetStartingPosition().Y());
    mCarried = false;
    this->SetGameTime(0, true);
}