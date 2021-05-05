/**
 * \file MotionSink.h
 *
 * \author Winnie Yang
 *
 * Motion sink for the instrument.
 */



#pragma once

class CInstrument;

class CMotionSource;


/**
 * Motion sink for the instrument.
 */
class CMotionSink
{
public:

    /// Constructor
    CMotionSink(CInstrument* instrument);

    /// Destructor
    virtual ~CMotionSink() {}

    /// Copy constructor/disabled
    CMotionSink(const CMotionSink&) = delete;

    /// Assignment operator/disabled
    void operator=(const CMotionSink&) = delete;

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    void SetAirPressure(double pressure);

    /**
    * Sets the motion source for instrument.
    * \param source Motion source
    */
    void SetMotionSource(CMotionSource* source) { mSource = source; };

private:
    /// Motion source
    CMotionSource* mSource = nullptr;

    /// Instrument
    CInstrument* mInstrument = nullptr;
};

