/**
 * \file BashfulGreen.h
 *
 * \author Winnie Yang
 *
 * Class that implements the Bashful-green fish.
 */


#pragma once

#include <memory>
#include <string>

#include "Item.h"


 /**
  * Implements the Bashful-green fish.
  */
class CBashfulGreen : public CItem
{
public:
    CBashfulGreen(CAquarium* aquarium);

    /// Default constructor (disabled)
    CBashfulGreen() = delete;

    /// Copy constructor (disabled)
    CBashfulGreen(const CBashfulGreen&) = delete;

    /// Hit test
    bool HitTest(int x, int y);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
    std::unique_ptr<Gdiplus::Bitmap> mRedImage;
};

