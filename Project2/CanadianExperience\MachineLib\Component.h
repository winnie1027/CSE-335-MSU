/**
 * \file Component.h
 *
 * \author Winnie Yang
 *
 * Base class for all components of instrument.
 */



#pragma once

#include "Polygon.h"

#include <memory>



/**
 * Base class for all components of instrument.
 */
class CComponent
{
public:
    /// Constructor
    CComponent();

    /// Destructor
    virtual ~CComponent() {}

    /// Copy constructor/disabled
    CComponent(const CComponent&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position);

    /**
    * Setter for time in seconds
    * \param seconds Time in seconds
    */
	virtual void SetTime(double seconds);

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetPosition(int x, int y) { mPosition.X = x, mPosition.Y = y; }

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure);

    /**
    * Point getter for component
    * \return position
    */
    Gdiplus::Point GetPosition() { return mPosition; }

private:

	/// Position of the component
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

};

