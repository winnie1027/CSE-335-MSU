/**
* \file TileGarden.h
*
* \author Charles B. Owen
*
*  Class that implements a Garden tile
*/

#pragma once

#include "Tile.h"


/**
*  A Garden tile
*/
class CTileGarden : public CTile
{
public:
    CTileGarden(CCity* city);

    ///  Default constructor (disabled)
    CTileGarden() = delete;

    ///  Copy constructor (disabled)
    CTileGarden(const CTileGarden&) = delete;

    ~CTileGarden();;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void Report(std::shared_ptr<CMemberReport> report) override;

    /// The supported pruning states
    enum class PruningStates { Pruned, Overgrown1, Overgrown2, Overgrown3, Overgrown4 };

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CTileVisitor* visitor) override { visitor->VisitGarden(this); }
};

