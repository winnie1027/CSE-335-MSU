/**
 * \file Cargo.h
 *
 * \author Caroline Gormely
 *
 * Class for a cargo item in the game.
 * These are the items the hero transports.
 */

#pragma once

#include "Item.h"
#include "Vector.h"
#include <string>


/**
 * Class for a cargo item in the game. Derived from CItem.
 */
class CCargo : public CItem
{
public:
	/// Constuctor
	CCargo(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);

	/// Delete default constructor
	CCargo() = delete;

	/// Delete copy constructor
	CCargo(const CCargo&) = delete;


	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;


	/**  Sets starting position of the boat
	* \param x x position
	  \param y y position  */
	void SetLocation(double x, double y) { CItem::SetLocation(x, y); };


	virtual bool ClickTest(int x, int y) override; 

	/// Updates mCarried to say whether cargo item is being carried or not
	/// \param check
	void SetItemCarried(bool check) { mCarried = check; }

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/** Accept a visitor
         * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override
	{
       visitor->VisitCargo(this);
    }

    /** Get initial X
     * \return starting X position */
	double GetStartingX() { return mStartX; }

	/// What this item eats
	/// \returns mEats
	wstring GetItemEats() { return mEats; }

	/// Reset item position
	virtual void Reset() override;

private: 	
	/// Image of the cargo item when it is being carried
	std::shared_ptr<Gdiplus::Bitmap> mCarriedImage;

	/// The cargo item this item will eat if left alone with it
	wstring mEats;

	/// True if carog tiem has been eaten by another cargo item
	bool mEaten = false;

	/// True if item is being carried
	bool mCarried = false;

	/// Starting X
	double mStartX = 0;
	
	/// Starting Y
	double mStartY = 15;
};

