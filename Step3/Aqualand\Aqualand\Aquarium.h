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
#include <string>

#include "XmlNode.h"

using namespace xmlnode;

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

    void Save(const std::wstring& filename);

    void Load(const std::wstring& filename);

    void Clear();

    void Update(double elapsed);

    /// Get the width of the aquarium
    /// \returns Aquarium width
    int GetWidth() const { return mBackground->GetWidth(); }

    /// Get the height of the aquarium
    /// \returns Aquarium height
    int GetHeight() const { return mBackground->GetHeight(); }

private:
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<CItem> > mItems;

    /// To handle Item tags
    void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);
};

