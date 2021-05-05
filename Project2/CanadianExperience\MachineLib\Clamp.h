/**
 * \file Clamp.h
 *
 * \author Winnie Yang
 *
 * Clamp used for tubing.
 */



#pragma once

#include "EndPoint.h"


/**
 * Clamp used for tubing.
 */
class CClamp : public CEndPoint
{
public:
    /// Constructor
    CClamp(int x, int y, double rotation, double speed);

    /// Destructor
    virtual ~CClamp() {}

    /// Copy constructor/disabled
    CClamp(const CClamp&) = delete;

    /// Assignment operator/disabled
    void operator=(const CClamp&) = delete;

private:

    /// Position of clamp
    Point mPosition = Point(0, 0);

    /// Rotation used for tubing
    double mRotation = 0;

    /// Speed used for tubing
    double mSpeed = 0;
};

