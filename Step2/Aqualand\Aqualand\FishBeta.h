/**
 * \file FishBeta.h
 *
 * \author Winnie Yang
 *
 * Class the implements a Beta fish
 */

#pragma once

#include <memory>

#include "Item.h"


 /**
  * Implements a Beta fish
  */
class CFishBeta : public CItem
{
public:
    CFishBeta(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;

    /// Hit test
    bool HitTest(int x, int y);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
