/**
 * \file Tubing.h
 *
 * \author Winnie Yang
 *
 * Tubing for instrument which connects sources to sinks.
 */



#pragma once

#include "Component.h"
#include "AirSource.h"
#include "AirSink.h"
#include "Clamp.h"
#include "AirSinkDestination.h"

#include <vector>


/**
 * Tubing for instrument which connects sources to sinks.
 */
class CTubing : public CComponent, public CAirSinkDestination
{
public:

    /// Constructor
    CTubing();

    /// Destructor
    virtual ~CTubing() {}

    /// Copy constructor/disabled
    CTubing(const CTubing&) = delete;

    /// Assignment operator/disabled
    void operator=(const CTubing&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
	virtual void Draw(Graphics* graphics, Point position) override;

    /**
    * Setter for air pressure.
    * \param pressure Air pressure
    */
    virtual void SetAirPressure(double pressure) override;

    /**
    * Gets the sink for components.
    * \return air sink
    */
    CAirSink* GetSink() { return &mAirSink; }

    /**
    * Sets the air source for tubing.
    * \param source Air source
    */
    void SetSource(std::shared_ptr<CAirSource> source) { mAirSource = source; }

    /**
    * Gets the air source for tubing.
    * \return Air source
    */
    std::shared_ptr<CAirSource> GetSource() { return mAirSource; }

    /**
    * Adds clamp for tubing.
    * \param x X
    * \param y Y
    * \param rotation Rotation
    * \param speed Speed
    */
    void AddClamp(int x, int y, double rotation, double speed);

private:

	/// Air pressure
	//double mAirPressure;

    /// Air source object
    std::shared_ptr<CAirSource> mAirSource;

    /// Air sink object
    CAirSink mAirSink;

    /// Vector of clamps
    std::vector<std::shared_ptr<CClamp>> mClamps;
};

