#include "pch.h"
#include <string>
#include "Rocket.h"
#include "TileRocketPad.h"

using namespace std;
using namespace Gdiplus;

const std::wstring RocketImage = L"images/rocket.png";

const float RocketOffsetX = -64;

const float RocketOffsetY = -105;

const double RocketBezierY = 200;

/// Default rocket speed in t values per second
const double RocketSpeed = 0.5;

/**
 * Constructor
 * @param city City this rocket is associated with. 
*/
CRocket::CRocket(CCity* city)
{
    mImage = unique_ptr<Bitmap>(Bitmap::FromFile(RocketImage.c_str()));
    if (mImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += RocketImage;
        AfxMessageBox(msg.c_str());
        return;
    }
}

/**
 * Set the rocket launching pad.
 * 
 * Whenever the launching pad is set, the rocket is reset
 * to a ready-to-launch condition on the pad.
 * @param pad New rocket launching pad
*/
void CRocket::SetLaunchingPad(CTileRocketPad* pad)
{
    mLandingPad = nullptr;
    mLaunchingPad = pad;
    mSpeed = 0;
    mT = 0;
}

/**
 * Set the rocket landing pad.
 * This initiates the rocket flight from launch pad to landing pad.
 * @param pad New rocket landing pad.
*/
void CRocket::SetLandingPad(CTileRocketPad* pad)
{
    mLandingPad = pad;
    mSpeed = RocketSpeed;
    mT = 0;
}

/**
 * Update the rocket in time. This allows the rocket to fly.
 * 
 * If the rocket is pointed to by both a launching and landing
 * pad, the update will only be done when called from the 
 * pad that is the lower on the screen (maximum Y value)
 * 
 * @param pad Pad this function is called from.
 * @param elapsed Elasped time in seconds.
*/
void CRocket::Update(CTileRocketPad* pad, double elapsed)
{
    if (!IsLowerOwner(pad))
    {
        return;
    }

    mT += elapsed * mSpeed;

    if (mT > 1)
    {
        mT = 1;
        mSpeed = 0;

        // We have landed
        if (mLandingPad != mLaunchingPad)
        {
            mLaunchingPad->RocketIsGone();
        }

        mLandingPad->RocketHasLanded();
    }

}

/**
 * Draw the rocket
 * 
 * If the rocket is pointed to by both a launching and landing
 * pad, the drawing will only be done when called from the 
 * pad that is the lower on the screen (maximum Y value)
 * 
 * @param pad The pad object that called the draw.
 * @param graphics Graphics context to draw the rocket on. 
*/
void CRocket::Draw(CTileRocketPad *pad, Gdiplus::Graphics* graphics)
{
    if (!IsLowerOwner(pad))
    {
        return;
    }

    if (mImage != nullptr)
    {
        auto position = ComputePosition();

        int wid = mImage->GetWidth();
        int hit = mImage->GetHeight();

        graphics->DrawImage(mImage.get(),
            position.X + RocketOffsetX, position.Y + RocketOffsetY,
            (float)wid, (float)hit);
    }
}

/**
 * Determine if this pad is the lower (int Y) of two pads owning
 * the rocket. If only owned by one, return true.
 * @param pad Pad to test
 * @return True if pad is the lower pad or rocket has only one owner.
*/
bool CRocket::IsLowerOwner(CTileRocketPad *pad)
{
    // Smart drawing and updating. We only draw 
    // or update when called by the lowest tile
    // when we are pointed to by more than one pad.
    if (mLaunchingPad != nullptr && mLandingPad != nullptr)
    {
        if (mLaunchingPad->GetY() > mLandingPad->GetY())
        {
            // Only draw if called by the launching pad
            if (pad != mLaunchingPad)
            {
                return false;
            }
        }
        else
        {
            // Only draw if called by the landing pad
            if (pad != mLandingPad)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * Is this rocket in flight right now?
 * @return true if rocket is inflight
*/
bool CRocket::InFlight()
{
    return mSpeed > 0;
}


/**
 * Compute a position for the rocket.
 * @return Position as a PointF object.
*/
Gdiplus::PointF CRocket::ComputePosition()
{
    if (mLaunchingPad != nullptr)
    {
        if (mLandingPad == nullptr)
        {
            // We have a launching pad, but no landing 
            // pad. Just return the launching pad location
            return PointF((float)mLaunchingPad->GetX(), (float)mLaunchingPad->GetY());
        }

        // We are in flight
        double x1 = mLaunchingPad->GetX();
        double y1 = mLaunchingPad->GetY();
        double x4 = mLandingPad->GetX();
        double y4 = mLandingPad->GetY();

        double x2 = x1;
        double y2 = y1 - RocketBezierY;
        double x3 = x4;
        double y3 = y4 - RocketBezierY;

        double t = mT;

        // Compute Bezier curve basis functions
        double b1 = (1 - t) * (1 - t) * (1 - t);
        double b2 = 3 * (1 - t) * (1 - t) * t;
        double b3 = 3 * (1 - t) * t * t;
        double b4 = t * t * t;

        return PointF(
            (float)(x1 * b1 + x2 * b2 + x3 * b3 + x4 * b4),
            (float)(y1 * b1 + y2 * b2 + y3 * b3 + y4 * b4)
        );

    }
    else
    {
        return PointF(0, 0);
    }
}
