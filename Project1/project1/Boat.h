/**
 * \file Boat.h
 *
 * \author Caroline Gormely
 *
 * Class for a boat in the game. Hero must use one of these to get across the river.
 */

#pragma once

#include <memory>
#include "Vehicle.h"

/**
 * Class for a boat in the game. Derived from CVehicle.
 */
class CBoat : public CVehicle
{
public:
  CBoat(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);

  void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

   /// Default constructor (disabled)
    CBoat() = delete;

    /// Copy constructor (disabled)
    CBoat(const CBoat&) = delete;

    /**  Sets starting position of the boat
    * \param x x position
      \param y y position  */
    void SetLocation(double x, double y) { CItem::SetLocation(x, y); }

    /**  Sets speed of the boat
    * \param speed - the speed of the boat */
    void SetSpeed(double speed) { CVehicle::SetSpeed(speed); }

    /**  Sets width of the boat
    * \param width - the width of the boat */
    void SetWidth(double width) { mWidth = width; }

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override 
    {
      visitor->VisitBoat(this);
    }

    /** Distance function
    * \param hero The hero in the game
      \param heroNearRiver whether or not hero is near the water
      \param cheat True if the RiverCheat menu option has been selected, False otherwise */
    virtual void Distance(std::shared_ptr<CHero> hero,
                          bool heroNearRiver, bool cheat) override;



   

private:
    /// Width of the boat image
    double mWidth;

};

