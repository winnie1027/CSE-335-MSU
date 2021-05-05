/**
 * \file Aquarium.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "Aquarium.h"
#include "Item.h"
#include "FishBeta.h"
#include "BashfulGreen.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 */
CAquarium::CAquarium()
{
    mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/background1.png"));
    if (mBackground->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/background1.png");
    }
}

/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
 * Remove an item that's duplicated then move it to the end of the list
 * \param item Item gets removed except if it's in the end
 */
void CAquarium::Remove(std::shared_ptr<CItem> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }
}

/** Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics* graphics)
{
    graphics->DrawImage(mBackground.get(), 0, 0,
        mBackground->GetWidth(), mBackground->GetHeight());

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush green(Color(0, 64, 0));
    graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**Detects when a fish gets too close (200 pixels) to a Bashful fish.
 * 
 * \param bashful Pointer to bashful fish
 * \returns Boolean to be sent back to BashfulGreen for reconstruction
 */
bool CAquarium::TooClose(CItem* bashful)
{
    for (auto item : mItems)
    {
        if (item.get() != bashful)
        {
            // Distance in the X and Y directions
            double dx = item->GetX() - bashful->GetX();
            double dy = item->GetY() - bashful->GetY();

            // Calculates distance between fish and Bashful fish
            double distance = sqrt(dx * dx + dy * dy);

            if (distance <= 200)
            {
                return true;
            }
        }
    }
    return false;
}
