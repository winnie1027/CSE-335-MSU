/**
 * \file Chime.h
 *
 * \author Winnie Yang
 *
 * Chime instrument.
 */



#pragma once

#include "Instrument.h"



/**
 * Chime instrument.
 */
class CChime : public CInstrument
{
public:

    /// Constructor
    CChime();

    /// Destructor
    virtual ~CChime() {}

    /// Copy constructor/disabled
    CChime(const CChime&) = delete;

    /// Assignment operator/disabled
    void operator=(const CChime&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
    virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position) override;

    /**
    * Sets the audio for chime.
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
    * Chime image setter
    * \param filename Chime image
    */
    void SetChime(std::wstring filename) { mChime.SetImage(filename); }

    /**
    * Chime mount image setter
    * \param filename Mount image
    */
    void SetMount(std::wstring filename) { mMount.SetImage(filename); }

    /**
    * Chime hammer image setter
    * \param filename Hammer image
    */
    void SetHammer(std::wstring filename) { mHammer.SetImage(filename); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetChimeWidth() { return mChime.GetImageWidth(); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * @return Width in pixels
    */
    int GetMountWidth() { return mMount.GetImageWidth(); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetHammerWidth() { return mHammer.GetImageWidth(); }

    /**
     * Create a chime
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleChime(int x, int y, int wid = 0, int hit = 0) { mChime.Rectangle(x, y, wid, hit); }

    /**
     * Create a mount
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleMount(int x, int y, int wid = 0, int hit = 0) { mMount.Rectangle(x, y, wid, hit); }

    /**
     * Create a hammer
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleHammer(int x, int y, int wid = 0, int hit = 0) { mHammer.Rectangle(x, y, wid, hit); }

    /**
    * Rotates the hammer image
    * \param rotate Rotation degrees
    */
    void SetHammerRotation(double rotate) { mHammer.SetRotation(rotate); }

    /**
    * Roates the chime image
    * \param rotate Rotation degrees
    */
    void SetChimeRotation(double rotate) { mChime.SetRotation(rotate); }

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) override;

    /**
    * Setter for machine number.
    * \param machine Machine number specifically used for factory 2
    */
    void SetMachineNumber(int machine) { mMachineNumber = machine; }

private:

    /// Wav channel used for audio
    std::shared_ptr<CWavChannel> mChannel;

    /// Position of the chime
    Point mPosition = Point(0, 0);

    /// Chime polygon item
    CPolygon mChime;

    /// Chime mount polygon item
    CPolygon mMount;
    
    /// Chime hammer polygon item
    CPolygon mHammer;

    /// Current air pressure
    double mPressure = 0;

    /// Previous air pressure
    double mOldPressure = 0;

    /// Initial machine number
    int mMachineNumber = 1;
};

