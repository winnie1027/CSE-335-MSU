/**
 * \file DecorCastle.h
 *
 * \author Winnie Yang
 *
 * Class that implements the castle item.
 */


#pragma once

#include "Item.h"


/**
 * Represents a castle decor
 */
class CDecorCastle : public CItem
{
public:

    /// Constructor
    CDecorCastle(CAquarium* aquarium);

    /// Default constructor (disabled)
    CDecorCastle() = delete;

    /// Copy constructor (disabled)
    CDecorCastle(const CDecorCastle&) = delete;

    /// Saves Xml of castle
    /// \return None
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

