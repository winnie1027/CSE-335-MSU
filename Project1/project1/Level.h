/**
 * \file Level.h
 *
 * \author Caroline Gormely
 *
 * Class for the levels that make up the game.
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Item.h"


using namespace std;

/**
 * Class for the levels in the game
 */
class CLevel
{
private:
	/// Pointer to the game
	CGame* mGame;

	/// Vector of items currently in the game 
	std::vector<shared_ptr<CItem>> mLevelItems;
	
	/// Vector of river positions
	std::vector<double> mRiverPositions;

	/// Hero in this level
	shared_ptr<CHero> mHero = nullptr;

	/// filename for this level
	wstring mFilename;

	/// True if protector item is in this level
	bool mProtector;

public:
    CLevel(CGame* game, wstring& filename);

	/// Delete default constructor
	CLevel() = delete;

    void Load();

	/// Level filename
	/// \returns levels filename
	wstring& GetFilename() { return mFilename; }

	/// This level's items
	/// \returns the items in this level
	std::vector<shared_ptr<CItem>> GetItems() { return mLevelItems; }

	/// Set Hero
	/// \param hero 
	void SetHero(shared_ptr<CHero> hero) { mHero = hero; }

	/// Get Hero
	/// \returns mHero
    shared_ptr<CHero> GetHero() { return mHero; }

	/// Get river positions for this level
	/// \returns &mRiverPositions
	std::vector<double>* GetRiverPositions() { return &mRiverPositions; }

	/// Sets protector status of level to true
	/// \param protector boolean 
	void SetProtectorStatus(bool protector) { mProtector = true; }

	/// Returns protector status of level 
	/// \returns mProtector  
	bool GetProtectorStatus() { return mProtector; }


};

