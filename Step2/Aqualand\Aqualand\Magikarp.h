/**
 * \file Magikarp.h
 *
 * \author Winnie Yang
 *
 * Class that implements Magikarp fish.
 */


#pragma once

#include <memory>

#include "Item.h"


 /**
  * Implements Magikarp fish.
  */
class CMagikarp : public CItem
{
public:
    CMagikarp(CAquarium* aquarium);

    /// Default constructor (disabled)
    CMagikarp() = delete;

    /// Copy constructor (disabled)
    CMagikarp(const CMagikarp&) = delete;

    /// Hit test
    bool HitTest(int x, int y);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

