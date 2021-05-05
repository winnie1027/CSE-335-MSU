/**
 * \file Cymbal.h
 *
 * \author Winnie Yang
 *
 * Cymbal instrument.
 */



#pragma once

#include "Instrument.h"


/**
 * Cymbal instrument.
 */
class CCymbal : public CInstrument
{
public:

    /// Constructor
    CCymbal();

    /// Destructor
    virtual ~CCymbal() {}

    /// Copy constructor/disabled
    CCymbal(const CCymbal&) = delete;

    /// Assignment operator/disabled
    void operator=(const CCymbal&) = delete;

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
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    void SetPosition(int x, int y) override { mPosition.X = x, mPosition.Y = y; }

    /**
    * Sets the image for cymbal.
    * \param filename Cymbal image
    */
    void SetCymbal(std::wstring filename) { mCymbal.SetImage(filename); }

    /**
    * Sets the image for the cymbal stand.
    * \param filename filename Cymbal stand image
    */
    void SetStand(std::wstring filename) { mStand.SetImage(filename); }
    
    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetCymbalWidth() { return mCymbal.GetImageWidth(); }

    /**
    * Gets the cymbal stand's width.
    * \return Width of cymbal stand
    */
    int GetStandWidth() { return mStand.GetImageWidth(); }

    /**
     * Create a cymbal
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCymbal(int x, int y, int wid = 0, int hit = 0) { mCymbal.Rectangle(x, y, wid, hit); }

    /**
     * Create a cymbal stand.
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCymbalStand(int x, int y, int wid = 0, int hit = 0) { mStand.Rectangle(x, y, wid, hit); }

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) override;

    /**
    * Sets the machine number for the purpose of doing challenge tasks
    * \param machine Machine number
    */
    void SetMachineNumber(int machine) { mMachineNumber = machine; }

private:

    /// Position of the component
    Point mPosition = Point(0, 0);

    /// Channel for audio
    std::shared_ptr<CWavChannel> mChannel;

    /// Polygon object for the cymbal stand
    CPolygon mStand;

    /// Polygon object for the cymbal
    CPolygon mCymbal;

    /// Current air pressure
    double mPressure = 0;

    /// Previous air pressure
    double mOldPressure = 0;

    /// Machine number used for challenge tasks
    int mMachineNumber = 1;
};

