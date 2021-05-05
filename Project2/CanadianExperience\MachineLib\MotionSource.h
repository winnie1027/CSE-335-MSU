/**
 * \file MotionSource.h
 *
 * \author Winnie Yang
 *
 * The motion source for the instrument.
 */



#pragma once

class CMotionSink;


/**
 *  The motion source for the instrument.
 */
class CMotionSource
{
public:

    /// Constructor
    CMotionSource();

    /// Destructor
    virtual ~CMotionSource() {}

    /// Copy constructor/disabled
    CMotionSource(const CMotionSource&) = delete;

    /// Assignment operator/disabled
    void operator=(const CMotionSource&) = delete;
    
    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    void SetAirPressure(double pressure);

    /**
    * Sets the air sink for instrument.
    * \param sink Air sink
    */
    void SetAirSink(CMotionSink* sink) { mMotionSink = sink; }

private:

    /// Motion sink
    CMotionSink* mMotionSink = nullptr;

};

