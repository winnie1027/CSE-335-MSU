/**
 * \file Magikarp.h
 *
 * \author Winnie Yang
 *
 * Class that implements Magikarp fish.
 */


#pragma once

#include "Item.h"
#include "Fish.h"

 /**
  * Implements Magikarp fish.
  */
class CMagikarp : public CFish
{
public:
    CMagikarp(CAquarium* aquarium);

    /// Default constructor (disabled)
    CMagikarp() = delete;

    /// Copy constructor (disabled)
    CMagikarp(const CMagikarp&) = delete;

    /// Saves Xml of fish
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

private:
    /// Maximum speed in pixels in the X direction
    const double MaxSpeedX = 300;

    /// Maximum speed in pixels in the Y direction
    const double MaxSpeedY = 300;

    /// Minimum speed in pixels in the X direction
    const double MinSpeedX = 50;

    /// Minimum speed in pixels in the Y direction
    const double MinSpeedY = 50;
};

