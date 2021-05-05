/**
 * \file Drum.h
 *
 * \author Winnie Yang
 *
 * Drum instrument.
 */



#pragma once

#include "Instrument.h"


/**
 * Drum instrument.
 */
class CDrum : public CInstrument
{
public:

    /// Constructor
    CDrum();

    /// Destructor
    virtual ~CDrum() {}

    /// Copy constructor/disabled
    CDrum(const CDrum&) = delete;

    /// Assignment operator/disabled
    void operator=(const CDrum&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
	virtual void Draw(Graphics* graphics, Point position) override;

    /**
    * Sets the audio for cymbal.
    * \param channel Audio channel for chime
    */
    virtual void SetAudioChannel(std::shared_ptr<CWavChannel> channel) override { mChannel = channel; }

    /**
    * Sets the drum image.
    * \param filename Drum image
    */
    void SetDrum(std::wstring filename) { mDrum.SetImage(filename); }

    /**
     * Create a rectangle for drum
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleDrum(int x, int y, int wid = 0, int hit = 0) { mDrum.Rectangle(x, y, wid, hit); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetDrumWidth() { return mDrum.GetImageWidth(); }

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) override;

private:
    /// The point of drum
    Point mPosition = Point(0, 0);

    /// Channel used for audio
    std::shared_ptr<CWavChannel> mChannel;

	/// Polygon object for drum
	CPolygon mDrum;

    /// Current air pressure
    double mPressure = 0;

    /// Previous air pressure
    double mOldPressure = 0;
};

