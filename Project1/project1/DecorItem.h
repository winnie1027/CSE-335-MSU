/**
 * \file DecorItem.h
 *
 * \author Caroline Gormely
 *
 * The class for a decor item in our game. 
 * This includes rivers, roads and sidewalks.
 */

#pragma once

#include <memory>

#include "Item.h"
#include "XMlNode.h"
#include "Game.h"

using namespace xmlnode;
using namespace std;


/**
 * Class for a decor item. Derived from CItem
 */
class CDecorItem : public CItem
{
public:
    CDecorItem(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);

    /// Default constructor (disabled)
    CDecorItem() = delete;

    /// Copy constructor (disabled)
    CDecorItem(const CDecorItem&) = delete;

    /// Destructor 
    ~CDecorItem();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    virtual void Draw(Gdiplus::Graphics* graphics) override;
 
    ///  Sets the number of times this item will repeat when drawn
    /// \param repeatX Number of times image is repeated in the x direction
    void SetRepeatX(int repeatX) { mRepeatX = repeatX; }

    ///  Sets the number of times this item will repeat when drawn
    /// \param repeatY Number of times image is repeated in the y direction
    void SetRepeatY(int repeatY) { mRepeatY = repeatY; }

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override 
    {
      visitor->VisitDecorItem(this);
    }


  

private:
    /// Starting x position
    double mStartX = 0;
    
    /// Starting y position
    double mStartY = 0;
    
    /// Number of times item image will repeat in the x direction
    double mRepeatX = 1;
    
    /// Number of times item image will repeat in the y direction
    double mRepeatY = 1;

    /// Image of the decor item
    std::shared_ptr<Gdiplus::Bitmap> mDecorImage;
};
