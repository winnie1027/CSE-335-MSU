/**
 * \file Car.h
 *
 * \author Caroline Gormely
 *
 * Class for a car in the game. 
 * If the hero collides with one of these, the player loses the level.
 */

#pragma once

#include <memory>
#include "Vehicle.h"

/**
 * Class for a car in the grame. Derived from CVehicle.
 */
class CCar : public CVehicle
{
 public:
	/// Constuctor
	CCar(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
	//virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

	/// Delete default constructor
	CCar() = delete;

	/// Delete copy constructor
	CCar(const CCar&) = delete;

	/**  Sets location of the car
	* \param x - x location of the car
		\param y - y location of the car */
	void SetLocation(double x, double y) { CItem::SetLocation(x, y); }

	/**  Sets speed of the car
	* \param speed The speed of the car */
	void SetSpeed(double speed) { CVehicle::SetSpeed(speed); }

	/**  Sets width of the car's image
	* \param width The width of the image */
	void SetWidth(double width) { mWidth = width; }

	/** Sets swap time of the car's image
	* \param seconds The swap time in seconds */
	void SetSwapTime(double seconds) { mSwapTime = seconds; }

	/// Updates the time for the animation of the car
	/// \param time - the time that has elapsed since last update
	void UpdateTime(double time) { mTimeTotal += time; }

	/// Rests the time for the car - used for animation
	void ResetTime() { mTimeTotal = 0; }

	void SetSecondImage(wstring& filename);

	/// Set the mirror status
	void SwitchSwapBool() { mSwapped = !mSwapped; }

	virtual void Update(double elapsed) override;

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	//virtual bool Distance(std::shared_ptr<CItem> other) override;

	/** Accept a visitor
        * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override 
	{
        visitor->VisitCar(this);
    }

	virtual void Distance(std::shared_ptr<CHero> hero, bool heroNearRiver, bool cheat) override;


private:
	/// 2nd image for the Car
	std::shared_ptr<Gdiplus::Bitmap> mCarImageTwo;

	/// boolean for swapping Car image
	bool mSwapped = false;

	/// width of the car 
	double mWidth;

	/// Swap time of the car
	double mSwapTime = 0.5;

	/// total time since last swap
	double mTimeTotal = 0;
};

