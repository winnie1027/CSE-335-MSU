/**
 * \file Aquarium.h
 *
 * \author Winnie Yang
 *
 * The aquarium where fish will be in and added to.
 */


#pragma once

#include <memory>
#include <vector>
#include "BashfulGreen.h"

class CItem;

/**
 * Represents an aquarium
 */
class CAquarium
{
public:
    CAquarium();

    void Add(std::shared_ptr<CItem> item);

    void Remove(std::shared_ptr<CItem> item);

    void OnDraw(Gdiplus::Graphics* graphics);

    std::shared_ptr<CItem> HitTest(int x, int y);

    // Detects when a fish gets too close to a Bashful fish
    bool TooClose(CItem* bashful);

private:
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<CItem> > mItems;
};

