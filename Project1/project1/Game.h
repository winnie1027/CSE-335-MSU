/**
 * \file Game.h
 *
 * \author Caroline Gormely
 *
 * The game class. This loads the levels that are played and controls the game.
 */

#pragma once
#include "Item.h"
#include "ItemVisitor.h"
#include "Level.h"
#include "Hero.h"
#include <vector>
#include <map>

using namespace std;

class CXmlLoader;
class CLevel;


/**
 * Class for the game.
 */
class CGame
{

private: 
    /// Game area in virtual pixels
    const static int Width = 1224;

    /// Game area height in virtual pixels
    const static int Height = 1024;

    /// Scale depends on size of the screen 
    double mScale = 0;

    /// How much we offset drawing the image in the x direction
    double mXOffset = 0;

    /// How much we offset drawing the image in the y direction
    double mYOffset = 0;

    /// Vector of items currently in the game 
    std::vector<shared_ptr<CItem>> mItems;

    /// Pointer to the hero in the game
    shared_ptr<CHero> mHero;

    /// The different levels in the game
    std::vector<CLevel> mLevels;

    /// Cargo names
    std::vector<std::pair<std::wstring, std::wstring>> mCargoNames;

    /// True only once level has been won
    bool mLevelWon = false;

    /// True if one of the loss conditions has been met
    bool mLevelLost = false;

    /// Total time since level has begun
    double mTotalTime = 0;

    /// The time when  a level was won, used to figure out display time for level complete
    double mWinTime = 0;

    /// Checks if win time has been set
    bool mWinTimeSet = false;

    /// The time when  a level was won, used to figure out display time for level complete
    double mLossTime = 0;

    /// Time during the start of a level
    double mStartingTime = 0;

    /// Checks if win time has been set
    bool mLossTimeSet = false;

    /// Level number (which level are we playing)
    int mPos = 0;

    /// Graphics used to do the displaying
    Gdiplus::Graphics* mGraphics;

    /// Y lower bound
    double mLowerY = 896;

    /// Y upper bound
    double mHigherY = 64;

    /// True if river cheat selected
    bool mRiverCheat = false;

    /// True if road cheat selected
    bool mRoadCheat = false;

    /// True if protector item is in game
    bool mProtector = false;

    /// Map that contains loaded images per item; this ensures all images are loaded once
    std::map<wstring, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>>> mMapItemImages;

    /// True during first 2 seconds of game
    bool mDisplayBegin = true;

    /// Wstring of loss reason
    wstring mLossReason = L"";

public:
    /// Constructor
    CGame();

    /// Destructor 
    ~CGame();

    /// The levels in the game
    /// \returns vector of levels
    vector<CLevel> GetLevels() { return mLevels; }

    /// True if win, false otherwise
    /// \returns whether or not the level has been won
    bool WasLevelWon() { return mLevelWon; }

    /// Get the width of the aquarium
    /// \returns Aquarium width
    int GetWidth() const { return Width; }

    /// Get the height of the aquarium
    /// \returns Aquarium height
    int GetHeight() const { return Height; }

    void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

    void DisplayLevelString();

    void DisplayWinString();

    void DisplayLossString();

    void Update(double elapsed);

    void LoadFile();//std::wstring& filename);

    void ChangeLevels(int levelNum);

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    std::shared_ptr<CItem> ClickTest(int x, int y);

    /// OffsetX for the screen
    /// \returns mOffsetX
    double GetXOffset() { return mXOffset; }

    /// Determine if there is a car within distance of 50 pixels from mHero
    //void HitTest();

    void RepositionItem(std::shared_ptr<CItem> item);

    void Accept(CItemVisitor* visitor);

    /// Gets pointer to hero.
    /// \returns mHero.
    shared_ptr<CHero> GetHero() { return mHero; }

    void OnButtonDown(UINT nFlags, CPoint point);

    /// Checks the cargo 
    void CheckCargo();

    /// Checks if there has been a hit
    void CheckHit();

    /// Sets Loss if one of the loss conditions are met
    void SetLoss() { mLevelLost = true; }

    /// Sets wins if cargo is on winning side 
    void SetWin() { mLevelWon = true; }

    /// The river cheat
    /// \returns mRiverCheat - true if that option has been selected
    bool GetRiverCheat() { return mRiverCheat; }

    /// Sets the river cheat
    /// \param check - true if that option has been selected
    void SetRiverCheat(bool check) { mRiverCheat = check; }

    /// The road cheat
    /// \returns mRoadCheat - true if that option has been selected
    bool GetRoadCheat() { return mRoadCheat; }

    /// Sets the road cheat
    /// \param check - true if that option has been selected
    void SetRoadCheat(bool check) { mRoadCheat = check; }

    void SetGameProtectorStatus(bool protector);

    /// Gets protector status of game 
    /// \returns mProtector boolean 
    bool GetGameProtectorStatus() { return mProtector; }

    void Win(int nextLevel);

    /// Function to reset Game attributes and item positions
    void Loss();

    void ResetAttributes(bool resetItems);

    /// The image map for an item
    /// \returns &mMapItemImages
    std::map<wstring, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>>>*
    GetImageMap() {return &mMapItemImages;}

    /// Gets Y position of lower platform
    /// \returns mLowerY
    double GetLowerPlace() { return mLowerY; }

    /// Gets Y position of higher platform
    /// \returns mHigherY
    double GetHigherPlace() { return mHigherY; }

};  

