/**
 * \file AirSink.h
 *
 * \author Winnie Yang
 *
 * Air sink class. the end that receives air.
 */



#pragma once

#include "EndPoint.h"
#include "Component.h"


/**
 * Air sink class. the end that receives air.
 */
class CAirSink : public CEndPoint
{
public:

    /// Constructor
    CAirSink();

    /// Destructor
    virtual ~CAirSink() {}

    /// Copy constructor/disabled
    CAirSink(const CAirSink&) = delete;

    /// Assignment operator/disabled
    void operator=(const CAirSink&) = delete;

    /**
    * Air pressure setter
    * \param pressure Air pressure
    * 
    */
    void SetAirPressure(double pressure) { mComponent->SetAirPressure(pressure); }

    /**
    * Component setter
    * \param component Component
    */
    void SetComponent(CComponent* component) { mComponent = component; }

private:
    /// Component pointer
    CComponent* mComponent = nullptr;

};

