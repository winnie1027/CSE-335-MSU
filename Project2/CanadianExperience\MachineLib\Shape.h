/**
 * \file Shape.h
 *
 * \author Winnie Yang
 *
 * Creates shaped components for instrument.
 */



#pragma once

#include "Component.h"
#include "WavChannel.h"
#include "MachineTemp.h"

#include <memory>

using namespace Gdiplus;


/**
 * Creates shaped components for instrument.
 */
class CShape : public CComponent
{
public:
    /// Constructor
    CShape();

    /// Destructor
    virtual ~CShape() {}

    /// Copy constructor/disabled
    CShape(const CShape&) = delete;

    /// Assignment operator/disabled
    void operator=(const CShape&) = delete;

	/**
	* Draw the machine at the currently specified location
	* \param graphics GDI+ Graphics object
	* \param position Position of the graphics object
	*/
    virtual void Draw(Graphics* graphics, Point position) override;

	/**
	 * Create a rectangle
	 * \param x Left side X
	 * \param y Bottom left Y
	 * \param wid Width of the rectangle. If not supplied, use an image width
	 * \param hit Height of the rectangle. If not supplied, use an image height
	 */
	void Rectangle(int x, int y, int wid = 0, int hit = 0) { mPolygon.Rectangle(x, y, wid, hit); }

	/**
	 * Set an image we will use as a texture for the polygon
	 * \param filename Image filename
	 */
	void SetImage(std::wstring filename) { mPolygon.SetImage(filename); }

	/**
	 * Get the width of any set image for this polygon. This may not be
	 * the width we actually draw, but is the size of the polygon itself.
	 * \return Width in pixels
	*/
	int GetImageWidth() { return mPolygon.GetImageWidth(); }
	
	/**
	 * Get the height of any set image for this polygon. This may not be
	 * the height we actually draw, but is the size of the polygon itself.
	 * \return Height in pixels
	*/
	int GetImageHeight() { return mPolygon.GetImageHeight(); }

	/** Set the color for the polygon
	* \param color New color to set */
	void SetColor(Gdiplus::Color color) { mPolygon.SetColor(color); }

	/**
	* Set the position for the root of the machine
	* \param x X location (pixels)
	* \param y Y location (pixels)
	*/
	void SetPosition(int x, int y) override { mPosition.X = x, mPosition.Y = y; }

	/**
	* Sets the audio for shape.
	* \param channel Audio channel
	*/
	void SetAudioChannel(std::shared_ptr<CWavChannel> channel) { mWavChannel = channel; }

	/**
	* Gets the X point of shape.
	* \return X
	*/
	double GetX() { return mPosition.X; }

	/**
	* Gets the Y point of shape.
	* \return Y
	*/
	double GetY() { return mPosition.Y; }

private:

	/// Position of the component
	Point mPosition = Point(0, 0);

    /// Polygon object
    CPolygon mPolygon;

	/// Audio channel
	std::shared_ptr<CWavChannel> mWavChannel;
};

