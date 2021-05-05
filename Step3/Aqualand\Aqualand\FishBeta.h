/**
 * \file FishBeta.h
 *
 * \author Winnie Yang
 *
 * Class the implements a Beta fish
 */

#pragma once

#include "Item.h"
#include "Fish.h"

 /**
  * Implements a Beta fish
  */
class CFishBeta : public CFish
{
public:
    CFishBeta(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;

    /// Saves Xml of fish
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

private:
    /// Maximum speed in pixels in the X direction
    const double MaxSpeedX = 500;

    /// Maximum speed in pixels in the Y direction
    const double MaxSpeedY = 500;

    /// Minimum speed in pixels in the X direction
    const double MinSpeedX = 50;

    /// Minimum speed in pixels in the Y direction
    const double MinSpeedY = 50;
};
