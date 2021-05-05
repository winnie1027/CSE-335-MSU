/**
 * \file FishDory.h
 *
 * \author Winnie Yang
 *
 * Class that implements Dory fish.
 */


#pragma once

#include "Item.h"
#include "Fish.h"

 /**
  * Implements Dory fish.
  */
class CFishDory : public CFish
{
public:
    CFishDory(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishDory() = delete;

    /// Copy constructor (disabled)
    CFishDory(const CFishDory&) = delete;

    /// Saves Xml of fish
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

private:
    /// Maximum speed in pixels in the X direction
    const double MaxSpeedX = 700;

    /// Maximum speed in pixels in the Y direction
    const double MaxSpeedY = 700;

    /// Minimum speed in pixels in the X direction
    const double MinSpeedX = 300;

    /// Minimum speed in pixels in the Y direction
    const double MinSpeedY = 300;
};

