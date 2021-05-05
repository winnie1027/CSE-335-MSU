/**
 * \file Instrument.h
 *
 * \author Winnie Yang
 *
 * Base class for all instruments.
 */



#pragma once

#include "Component.h"
#include "MotionSink.h"
#include "WavChannel.h"

using namespace Gdiplus;


/**
 * Base class for all instruments.
 */
class CInstrument : public CComponent
{
public:

    /// Constructor
    CInstrument();

    /// Destructor
    virtual ~CInstrument() {}

    /// Copy constructor/disabled
    CInstrument(const CInstrument&) = delete;

    /// Assignment operator/disabled
    void operator=(const CInstrument&) = delete;

    /**
    * Sets the audio for instrument.
    * \param channel Sound channel
    */
    virtual void SetAudioChannel(std::shared_ptr<CWavChannel> channel);

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
    virtual void Draw(Graphics* graphics, Point position) override;

    /**
    * Motion sink getter.
    * \return Motion sink
    */
    CMotionSink* GetSink() { return &mMotionSink; }

    /**
    * Sets air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure);

private:
	/// Motion sink object
	CMotionSink mMotionSink;
};

