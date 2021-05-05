/**
 * \file Item.h
 *
 * \author
 *
 * Parents class for all items in the game.
 */



#pragma once

#include <memory>
#include <string>
#include <vector>
#include "XmlNode.h"
#include "Vector.h"
#include "ItemVisitor.h"

using namespace xmlnode;
using namespace std;
using namespace Gdiplus;

class CGame;

/**
 * Class for an item. Base class for cargo, hero, vehicle and decor items.
 */
class CItem
{


public:
	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	virtual ~CItem(); 


	/** Sets location of the item 
	  * \param x - x location 
	  * \param y - y location
	  */
	void SetLocation(double x, double y) 
	{
		mP.Set(x, y); 
	} 

	/** Sets mOriginalP of the item
	  * \param p - position Vector
	  */
	void SetStartingLocation(CVector p)
	{
		mOriginalP.Set(p.X(), p.Y());
	}

	/**  The ID of this item
	* \returns ID the id of this item */
	wstring GetId() { return mID; }

	
	/**  Height of the item's image
	* \returns height of the item's image */
	double GetHeight() { return mItemImage->GetHeight(); }
	
	/**  Width of the item's image
	* \returns width of the item's image */
    double GetWidth() { return mItemImage->GetWidth(); }

	/** Size of a tile
	  * \returns size of 1 tile 
	  */
	double GetTileWidth() { return mTile; }
	
	/**  The position of the item
	* \returns mP position of the item */
	CVector GetPosition() { return mP; }

	/**  The position of the item
	* \returns mP position of the item */
	CVector GetStartingPosition() { return mOriginalP; }

	/** Return the X position of the item
	* \returns mP.X */
	double GetX() { return mP.X(); }

	/** Return the Y position of the item
	* \returns mP.Y */
	double GetY() { return mP.Y(); }

	/// Get the game this item is in
	/// \returns Game pointer
	CGame* GetGame() { return mGame; }

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Handle updates for animation
    /// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}


	/// Adds elapsed to the total time
	/// \param time Time to add to the total game time
	/// \param restart bool to restart mGameTime
	void SetGameTime(double time, bool restart) 
	{ 
		if (!restart) 
		{
            mGameTime += time;
        } else 
		{
           mGameTime = 0;   
		}
	}

	/// The amount of time the game this item is in has been going for
	/// \returns mGameTime
	double GetGameTime() { return mGameTime; }

	/** Test this item to see if it has been clicked on
	 * \param x X location on the game to test
	 * \param y Y location on the game to test
	 * \return true if clicked on */
	virtual bool ClickTest(int x, int y) { return false; }

	/// Is item being carried
	/// \return false if item not being carried
	virtual bool Carry() { return false; }

	/// Returns the item's pixel format
	/// \returns pixel format of the item image
	Gdiplus::PixelFormat GetImagePixelFormat(){ return mItemImage->GetPixelFormat(); }

	/// Gets the item's pixel 
	/// \param testX location in x-axis
	/// \param testY location in y-axis
	/// \param color Color of pixel
	void GetImagePixel(int testX, int testY, Gdiplus::Color color){ mItemImage->GetPixel(testX, testY, &color); }

	/** Determine the distance from this item to some other item.
	 * \param hero Hero item we are testing
	 * \param heroNearRiver
	 * \param cheat - True if cheat mode has been selected, False otherwise
	 */
    virtual void Distance(std::shared_ptr<CHero> hero, bool heroNearRiver, bool cheat){};


	/** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) = 0;
		
	/// Get ID of the item 
	/// \returns mID
	wstring GetID() { return mID; }

	/// Get name of the item 
	/// \returns mTagName
	wstring GetTagName() { return mTagName; }

	/// Sets name of the item 
	/// \param x - the name
	void SetName(wstring x) {mName = x;}

	/// Get name of the item
	/// \returns mName
    wstring GetName() { return mName; }

	/// Reset function for items
	virtual void Reset() {}


private: 

	/// Game this item is in
	CGame* mGame;

	/// How long game this item is in has been going for
	double mGameTime = 0;

	/// Vector represenenting the item's position 
	CVector mP;

	/// Vector represenenting the item's start position 
	CVector mOriginalP;

	/// Image of the item
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;

	/// Name of the item (ex: Grain)
	wstring mName;

	/// First word to appear in the tag (cargo, decor)
	wstring mTagName;

	/// ID of the item
	wstring mID;

	/// Size of a tile
	double mTile = 64;

	


 protected:
    CItem(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);
	

};
