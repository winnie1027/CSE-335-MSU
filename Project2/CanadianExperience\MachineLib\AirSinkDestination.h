/**
 * \file AirSinkDestination.h
 *
 * \author Winnie Yang
 *
 * Interface class.
 */



#pragma once


/**
 * Air destination, interface class.
 */
class CAirSinkDestination
{
public:
    /// Constructor
    CAirSinkDestination();

    /// Destructor
    virtual ~CAirSinkDestination() {}

    /// Copy constructor/disabled
    CAirSinkDestination(const CAirSinkDestination&) = delete;

    /// Assignment operator/disabled
    void operator=(const CAirSinkDestination&) = delete;

    /**
    * Airpressure setter
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) = 0;

private:

};

