/**
 * \file AirSource.h
 *
 * \author Winnie Yang
 *
 * Air source where the air comes from.
 */



#pragma once

#include "EndPoint.h"
#include "AirSink.h"


/**
 * Air source where the air comes from.
 */
class CAirSource : public CEndPoint
{
public:

    /// Constructor
    CAirSource();

    /// Destructor
    virtual ~CAirSource() {}

    /// Copy constructor/disabled
    CAirSource(const CAirSource&) = delete;

    /// Assignment operator/disabled
    void operator=(const CAirSource&) = delete;

    /**
    * Air pressure setter
    * \param pressure Air pressure
    */
    void SetAirPressure(double pressure);

    /**
    * Airsink setter
    * \param airSink Air sink
    */
    void SetSink(CAirSink* airSink) { mAirSink = airSink; }

    /**
    * Air sink getter
    * \return mAirsink
    */
    CAirSink* GetSink() { return mAirSink; }

private:
    /// Air sink pointer
    CAirSink* mAirSink = nullptr;

};

