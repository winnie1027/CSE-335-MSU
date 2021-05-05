/**
 * \file Vehicle.h
 *
 * \author Caroline Gormely
 *
 * Class for a vehichle. The hero wants to either avoid or be associated 
 * with a vehicle depending on its type.
 */

#pragma once

#include "Item.h"
#include "Vector.h"
#include "Game.h"

/**
 * Class for a vehicle. Base class for CCar and CBoat.
 */
class CVehicle : public CItem 
{
public:

	/// Default constructor (disabled)
	CVehicle() = delete;

	/// Copy constructor (disabled)
	CVehicle(const CVehicle&) = delete;

	/**  Sets speed of the vehicle
	* \param speed - the speed of the vehicle */
	void SetSpeed(double speed) { mSpeed = speed; }

	/// Speed of the vehicle
	/// \return speed of the vehicle
	double GetSpeed() { return mSpeed; }

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void Update(double elapsed) override;

    bool CalculateDistance(std::shared_ptr<CHero> hero, bool ifBoat);

protected:
    /// Constructor
	CVehicle(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);
	
private:
	/// Speed of the vehicle
	double mSpeed = 0;

	/// Width that allows the vehicle to wrap around
	double mWidth = 0;

	/// Filename of the vehicle image
	wstring mFilename;
	
};

