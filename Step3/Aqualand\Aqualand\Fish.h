/**
 * \file Fish.h
 *
 * \author Winnie Yang
 *
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */

#pragma once

#include "Item.h"
#include "Aquarium.h"



/**
 * Represents a fish of any kind
 */
class CFish : public CItem
{

public:
    /// Default constructor (disabled)
    CFish() = delete;

    /// Copy constructor (disabled)
    CFish(const CFish&) = delete;

    /// Gets speed in X direction
    /// \returns speed x
    double const GetSpeedX() { return mSpeedX; }

    /// Gets speed in Y direction
    /// \returns speed y
    double const GetSpeedY() { return mSpeedY; }

    /// Saves Xml of fish
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Loads Xml of fish
    /// \return None
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Updates fish info
    void Update(double elapsed);

    /// Set speed of fish
    /// \param x speed X
    /// \param y speed Y
    void SetSpeed(double x, double y) { mSpeedX = x; mSpeedY = y; }

protected:
    /// Constructor
    CFish(CAquarium* aquarium, const std::wstring& filename);

private:
    /// Fish speed in the X direction
    double mSpeedX;

    /// Fish speed in the Y direction
    double mSpeedY;
};

