/**
 * \file EndPoint.h
 *
 * \author Winnie Yang
 *
 * The endpoint for tubing connection.
 */


#pragma once

using namespace Gdiplus;


/**
 * The endpoint for tubing connection.
 */
class CEndPoint
{
public:

    /// Constructor
    CEndPoint();

    /// Destructor
    virtual ~CEndPoint() {}

    /// Copy constructor/disabled
    CEndPoint(const CEndPoint&) = delete;

    /// Assignment operator/disabled
    void operator=(const CEndPoint&) = delete;

    /**
    * Sets the rotation for tubing.
    * \param rotation Rotation
    */
    void SetRotation(double rotation) { mAngle = rotation; }

    /**
    * Gets the rotation for tubing.
    * \return Angle of rotation
    */
    double GetRotation() { return mAngle; }

    /**
    * Setter for speed.
    * \param speed Speed
    */
    virtual void SetSpeed(double speed) { mSpeed = speed; }

    /**
    * Getter for speed.
    * \return speed
    */
    double GetSpeed() { return mSpeed; }

    /**
    * Sets the endpoint for tubing.
    * \param point Point of endpoint
    */
    void SetEndpoint(Point point) { mPosition = point; }

    /**
    * Getter for end point.
    * \return endpoint
    */
    Point GetEndpoint() { return mPosition; }

private:
	/// Rotation for tubing
	double mAngle = 0;

	/// Speed
	double mSpeed = 0;

	/// Point of endpoint
	Point mPosition = Point(0, 0);
};

