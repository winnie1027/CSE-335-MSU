/**
* \file Item.h
*
* \author Winnie Yang
*
* Base class for any item in our aquarium.
*/

#pragma once

#include "XmlNode.h"

#include <memory>
#include <string>


class CAquarium;

/**
 * Base class for any item in our aquarium.
 */
class CItem
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    virtual ~CItem();

    /** The X location of the item
     * \returns X location in pixels */
    double GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    double GetY() const { return mY; }

    /// Set the item location
    /// \param x X location
    /// \param y Y location
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /// Draw this item
    /// \param graphics Graphics device to draw on
    void Draw(Gdiplus::Graphics* graphics);

    /// Saves fish to Xml
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Loads a fish from Xml
    /// \param node A node pointer to a fish
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    /** Test this item to see if it has been clicked on
    * \param x X location on the aquarium to test
    * \param y Y location on the aquarium to test
    * \return true if clicked on */
    bool HitTest(int x, int y);

    /// Get the aquarium this item is in
    /// \returns Aquarium pointer
    CAquarium* GetAquarium() { return mAquarium; }

    /// Set the mirror status
    /// \param m New mirror flag
    void SetMirror(bool m) { mMirror = m; }

    /// Gets fish image
    /// \returns pointer to image
    Gdiplus::Bitmap * GetImage() { return mItemImage.get(); }

protected:
    /// Loads filename
    /// \param filename Filename
    CItem(CAquarium* aquarium, const std::wstring& filename);

    /// The image of this fish
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

private:

    /// The aquarium this item is contained in
    CAquarium* mAquarium;

    // Item location in the aquarium
    double   mX = 0;     ///< X location for the center of the item
    double   mY = 0;     ///< Y location for the center of the item

    bool mMirror = false;   ///< True mirrors the item image
};
