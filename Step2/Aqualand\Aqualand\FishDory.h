/**
 * \file FishDory.h
 *
 * \author Winnie Yang
 *
 * Class that implements Dory fish.
 */


#pragma once

#include <memory>

#include "Item.h"


 /**
  * Implements Dory fish.
  */
class CFishDory : public CItem
{
public:
    CFishDory(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishDory() = delete;

    /// Copy constructor (disabled)
    CFishDory(const CFishDory&) = delete;

    /// Hit test
    bool HitTest(int x, int y);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

