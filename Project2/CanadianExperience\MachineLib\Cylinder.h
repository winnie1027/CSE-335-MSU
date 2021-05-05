/**
 * \file Cylinder.h
 *
 * \author Winnie Yang
 *
 * Cylinder on the instrument.
 */


#pragma once

#include "Component.h"
#include "AirSink.h"
#include "MotionSource.h"
#include "MotionSink.h"
#include "Instrument.h"
#include "Shape.h"
#include "AirSinkDestination.h"



/**
 * Cylinder on the instrument.
 */
class CCylinder : public CComponent, public CAirSinkDestination
{
public:

    /// Constructor
    CCylinder();

    /// Destructor
    virtual ~CCylinder() {}

    /// Copy constructor/disabled
    CCylinder(const CCylinder&) = delete;

    /// Assignment operator/disabled
    void operator=(const CCylinder&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
    virtual void Draw(Graphics* graphics, Point position) override;

    /**
    * Cylinder rotator setter
    * \param rotation Rotation
    */
    void SetCylinderRotation(double rotation) { mCylinder.SetRotation(rotation); }

    /**
    * Cylinder baserotator setter
    * \param rotation Rotation
    */
    void SetBaseRotation(double rotation) { mMount.SetRotation(rotation); }

    /**
    * Cylinder ram rotator setter
    * \param rotation Rotation
    */
    void SetRamRotation(double rotation) { mRam.SetRotation(rotation); }

    /**
    * Sets the max extension for rams
    * \param extent Max extent
    */
    void SetMaxExtent(double extent) { mMaxExtent = extent; }

    /**
    * Sets the mount image.
    * \param filename Mount image
    */
    void SetMount(std::wstring filename) { mMount.SetImage(filename); }

    /**
    * Sets the cylinder image.
    * \param filename Cylinder image
    */
    void SetCylinder(std::wstring filename) { mCylinder.SetImage(filename); }

    /**
    * Sets the ram image.
    * \param filename Ram image
    */
    void SetRam(std::wstring filename) { mRam.SetImage(filename); }

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    void SetPosition(int x, int y) override;

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetMountWidth() { return mMount.GetImageWidth(); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetCylinderWidth() { return mCylinder.GetImageWidth(); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetRamWidth() { return mRam.GetImageWidth(); }

    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleMount(int x, int y, int wid = 0, int hit = 0) { mMount.Rectangle(x, y, wid, hit); }

    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCylinder(int x, int y, int wid = 0, int hit = 0) { mCylinder.Rectangle(x, y, wid, hit); }

    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleRam(int x, int y, int wid = 0, int hit = 0) { mRam.Rectangle(x, y, wid, hit); }

    /**
    * Air sink getter
    * \return Air sink
    */
    CAirSink* GetSink() { return &mAirSink; }

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) override;

    /**
    * Motion sink setter
    * \param instrument The instrument this motion sink is
    */
    void SetMotionSink(std::shared_ptr<CInstrument> instrument);

private: 
    /// Position of cylinder
    Point mPosition = Point(0, 0);

	/// Cylinder mount polygon object
	CPolygon mMount;

    /// Cylinder polygon object
	CPolygon mCylinder;
    
    /// Cymbal Cylinder polygon object
    CPolygon mCymbalCylinder;

    /// Ram polygon object that extends from cylinders
    CPolygon mRam;

	/// Air pressure
	double mAirPressure = 0;

    // How far the cylinder ram can extent
    double mMaxExtent = 1;

    /// The furthest a ram can extend from a cylinder
    double mExtent = 44;

    /// Air sink object
    CAirSink mAirSink;

    /// Motion source
    CMotionSource mMotionSource;

    /// Motion sink component
    std::shared_ptr<CComponent> mMotionSink;

    /// Instrument 
    std::shared_ptr<CInstrument> mInstrument;
};

