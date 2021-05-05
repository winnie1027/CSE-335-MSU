/**
 * \file TileRocketPad.h
 *
 * \author 
 *
 * Class that implements a rocket pad.
 */

#pragma once

#include "Tile.h"
#include "Rocket.h"

class CRocket;

/**
 * Class that implements a rocket pad.
 * 
 * This is where rockets take off and land.
*/
class CTileRocketPad : public CTile
{
public:
    CTileRocketPad(CCity* city);

    ///  Default constructor (disabled)
    CTileRocketPad() = delete;

    ///  Copy constructor (disabled)
    CTileRocketPad(const CTileRocketPad&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void Report(std::shared_ptr<CMemberReport> report) override;

    virtual bool PendingDelete() override;

    void RocketIsGone();
    void RocketHasLanded();

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CTileVisitor* visitor) override { visitor->VisitRocketPad(this); }

    std::shared_ptr<CRocket> GetVisitor() { return mRocketPad; }

    // Visitor setter
    void SetVisitor(std::shared_ptr<CRocket> rocket) { mRocketPad = rocket; }

    virtual void Update(double elapsed) override;

private:
    std::shared_ptr<CRocket> mRocketPad;
};

