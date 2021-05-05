/**
 * \file Rocket.h
 *
 * \author Charles B. Owen
 *
 * Class the implements a simple rocket.
 */

#pragma once

#include <memory>

class CCity;
class CTileRocketPad;

/**
 * Class the implements a simple rocket.
*/
class CRocket
{
public:
    CRocket(CCity* city);

    void SetLaunchingPad(CTileRocketPad* pad);
    void SetLandingPad(CTileRocketPad* pad);

    void Update(CTileRocketPad* pad, double elapsed);

    void Draw(CTileRocketPad* pad, Gdiplus::Graphics* graphics);

 
    bool InFlight();

private:
    Gdiplus::PointF ComputePosition();
    bool IsLowerOwner(CTileRocketPad* pad);

    /// The image of the rocket
    std::unique_ptr<Gdiplus::Bitmap> mImage;

    /// The launching pad for the rocket
    CTileRocketPad* mLaunchingPad = nullptr;

    /// The landing pad for the rocket
    CTileRocketPad* mLandingPad = nullptr;

    /// Current position of the rocket in flight
    /// as a T value from 0 to 1.
    double mT = 0;

    /// Speed of the rocket in t units per second
    double mSpeed = 0;
};

