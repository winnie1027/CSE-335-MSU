/**
 * \file BashfulGreen.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "BashfulGreen.h"
#include "Aquarium.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring BashfulGreenImageName = L"images/bashful-green.png";
const wstring BashfulRedImageName = L"images/bashful-red.png";


/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CBashfulGreen::CBashfulGreen(CAquarium* aquarium) : CItem(aquarium)
{
    mFishImage = unique_ptr<Bitmap>(Bitmap::FromFile(BashfulGreenImageName.c_str()));
    mRedImage = unique_ptr<Bitmap>(Bitmap::FromFile(BashfulRedImageName.c_str()));

    // Constructs green bashful fish
    if (mFishImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += BashfulGreenImageName;
        AfxMessageBox(msg.c_str());
    }
    // Constructs red bashful fish
    else if (mRedImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += BashfulRedImageName;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Draw our fish
 * \param graphics The graphics context to draw on
 */
void CBashfulGreen::Draw(Gdiplus::Graphics* graphics)
{
    CAquarium* aquarium = GetAquarium();

    // Draws green bashful fish
    if (!aquarium->TooClose(this))
    {
        double wid = mFishImage->GetWidth();
        double hit = mFishImage->GetHeight();
        graphics->DrawImage(mFishImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mFishImage->GetWidth(), (float)mFishImage->GetHeight());
    }
    // Draws red bashful fish
    else
    {
        double wid = mRedImage->GetWidth();
        double hit = mRedImage->GetHeight();
        graphics->DrawImage(mRedImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mRedImage->GetWidth(), (float)mRedImage->GetHeight());
    }
}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CBashfulGreen::HitTest(int x, int y)
{
    double wid = mFishImage->GetWidth();
    double hit = mFishImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mFishImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mFishImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

