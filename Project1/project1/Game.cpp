/**
 * \file Game.cpp
 *
 * \author 
 */

#include "pch.h"
#include "Game.h"
#include "XMlNode.h"
#include "DecorItem.h"
#include "Cargo.h"
#include "Car.h"
#include "Boat.h"
#include "Hero.h"
#include "XMlLoader.h"
#include "ItemVisitor.h"
#include "CargoVisitor.h"
#include "EatVisitor.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <chrono>
#include <future>


using namespace xmlnode;
using namespace Gdiplus;
using namespace std;
using namespace std::chrono_literals;

/**
 * Destructor
 */
CGame::~CGame()
{
}

/**
 * Game constructor
 */
CGame::CGame() 
{
  wstring filenameZero = L"levels/level0.xml";
  wstring filenameOne = L"levels/level1.xml";
  wstring filenameTwo = L"levels/level2.xml";
  wstring filenameThree = L"levels/level3.xml";
  CLevel LevelZero = CLevel(this, filenameZero);
  CLevel LevelOne = CLevel(this, filenameOne);
  CLevel LevelTwo = CLevel(this, filenameTwo);
  CLevel LevelThree = CLevel(this, filenameThree);
  mLevels = { LevelZero, LevelOne, LevelTwo, LevelThree }; 
  LoadFile();

}
    
/**
 * Loads the file for the current level the game is on
 */
void CGame::LoadFile() {
  for (auto i = mLevels.begin(); i != mLevels.end(); i++) 
  {
    (*i).Load();
  }
}


/**
 * Resetting attributes.
 * \param resetItems 
 */
void CGame::ResetAttributes(bool resetItems)
{
    //reset booleans
    mLevelWon = false;
    mLevelLost = false;
    mDisplayBegin = true;
    mHero->SetHeroHit(false);
    mHero->SetHeroDrown(false);
    //reset timer
    mTotalTime = 0;
    mStartingTime = 0;
    //reset cheats ?
    mRiverCheat = false;
    mRoadCheat = false;
    if (resetItems)
    {
        //reset item positions
        for (auto item : mItems) {
            item->Reset();
        }
    }
}


/**
 * Changes game level.
 * \param levelNum 
 */
void CGame::ChangeLevels(int levelNum) 
{
  mCargoNames.clear();
  mPos = levelNum;
  mItems = mLevels[levelNum].GetItems();
  mHero = mLevels[levelNum].GetHero();
  // don't need to reset items' positions 
  //    bc they are getting set for the first time
  for (auto& item : mItems) 
  {
    if (item->GetTagName() == L"cargo") 
    {
      mCargoNames.push_back(std::make_pair(item->GetTagName(), item->GetName()));
    }
    if (item->GetTagName() == L"protector") 
    {
      mCargoNames.push_back(std::make_pair(item->GetTagName(), item->GetName()));
    }
  }

  ResetAttributes(false);
}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);
    mGraphics = graphics;

    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    // From here on you are drawing virtual pixels
    for (auto& item : mItems)
    {
        item->Draw(graphics);
    }

    // Implement illusion for boats & car movement
    graphics->FillRectangle(&brush, Width-200, 0, 1000, Height);
    graphics->FillRectangle(&brush, -1000, 0, 1000, Height);

    // Print words on the side
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 30, FontStyleBold);

    // Prints Level 1
    SolidBrush green(Color(0, 200, 50));
    SolidBrush red(Color(200, 120, 150));
    wstring levelNumber = std::to_wstring(mPos);
    wstring toDraw = L"Level " + levelNumber;
    graphics->DrawString(toDraw.c_str(), -1, &font, PointF(1050, 70), &green);
    int yPos = 150;
    for (auto item : mCargoNames)
    {
        if (item.first != L"protector") 
        {
          graphics->DrawString(item.second.c_str(), -1, &font, PointF(1050, yPos),
                               &red);
        }
        yPos += 50;
        if (item.first == L"protector" && mTotalTime <= 45) 
        {
          graphics->DrawString(item.second.c_str(), -1, &font, PointF(1050, 300),
                               &red);
        }
      
    }
}

/**
 * If less than 2 seconds since game has started, display
 * that the level has begun. 
 */
void CGame::DisplayLevelString()
{
    if (mDisplayBegin)
    {
        FontFamily fontFamily1(L"Arial");
        Gdiplus::Font font1(&fontFamily1, 50, FontStyleBold);
        SolidBrush orange(Color::Orange);
        wstring levelNumber = std::to_wstring(mPos);
        wstring toDraw = L"Level " + levelNumber + L" Begins";
        mGraphics->DrawString(toDraw.c_str(), -1, &font1, PointF(260, 500), &orange);
    }
}

/**
 * Displays win message if user won the game
 */
void CGame::DisplayWinString()
{
    //don't need to set a limit on how long win message is displayed since
   //next level will be loaded right after

    FontFamily fontFamily1(L"Arial");
    Gdiplus::Font font1(&fontFamily1, 50, FontStyleBold);
    SolidBrush orange(Color::Orange);
    // if level is not 3, display level complete
    if (mPos != 3) 
    {
        wstring toDraw = L"Level Complete!";
        mGraphics->DrawString(toDraw.c_str(), -1, &font1, PointF(250, 480), &orange);
    }
    // display game complete for level 3 only
    else 
    {
        wstring toDraw = L"Game Complete!";
        mGraphics->DrawString(toDraw.c_str(), -1, &font1, PointF(250, 480), &orange);
    }
}

/**
 * Displays loss message if user lost
 */
void CGame::DisplayLossString()
{
    //don't need to set a limit on how long message is displayed since
    //level will be reset 2 seconds after

    FontFamily fontFamily1(L"Arial");
    Gdiplus::Font font1(&fontFamily1, 24, FontStyleBold);
    SolidBrush orange(Color::Orange);
    //display loss reason
    mGraphics->DrawString(mLossReason.c_str(), -1, &font1,
                          PointF(255, 507), &orange);
}

/// Sets protector cat status of game to true for 45 seconds.
    /// \param protector boolean 
void CGame::SetGameProtectorStatus(bool protector) 
{
    FontFamily fontFamily1(L"Arial");
    Gdiplus::Font font1(&fontFamily1, 20, FontStyleBold);
    Gdiplus::Font captionFont(&fontFamily1, 15, FontStyleBold);
    SolidBrush brush(Color::Lavender);
    SolidBrush black(Color::Black);
    int napTime = 45 - mTotalTime;
    wstring timeLeft = to_wstring(napTime);

    // in a level that has a protector item
    if (mLevels[mPos].GetProtectorStatus() == true) 
    {
      if (!mLevelLost) {
        if (mTotalTime > 0 && mTotalTime < 5) 
        {
          mGraphics->DrawString(L"Black cat prevents items from eating", -1,
                                &font1, PointF(260, 510), &brush);
          mGraphics->DrawString(L"each other for the first 45 seconds!", -1,
                                &font1, PointF(270, 540), &brush);
        }
        if (mTotalTime > 5 && mTotalTime < 10) {
          mGraphics->DrawString(L"I won't eat the fish, I'm vegan.", -1,
                                &captionFont, PointF(740, 900), &black);
        }
        if (mTotalTime > 5 && mTotalTime < 43) 
        {
          mGraphics->DrawString(L"My nap time is in ", -1, &captionFont,
                                PointF(805, 920), &black);
          mGraphics->DrawString(timeLeft.c_str(), -1, &captionFont,
                                PointF(825, 940), &black);
          mGraphics->DrawString(L" seconds :)", -1, &captionFont,
                                PointF(852, 940), &black);
        }
        if (mTotalTime <= 45) 
        {
          mProtector = true;
        }
        if (mTotalTime > 45 && mTotalTime < 50) 
        {
          mGraphics->DrawString(L"Cat guardian has gone home to nap!", -1,
                                &font1, PointF(270, 520), &brush);
        }
        if (mTotalTime > 45)  // cat no longer protects once 45 seconds have elapsed
        {
          mProtector = false;
        }
      }
        
    }
}

/**
 * Update items inside the game.
 * \param elapsed 
 */
void CGame::Update(double elapsed)
{
    mStartingTime += elapsed;

    if (mStartingTime >= 2)
        mDisplayBegin = false;

    if (!mDisplayBegin)
        mTotalTime += elapsed;
    DisplayLevelString();
    SetGameProtectorStatus(mLevels[mPos].GetProtectorStatus());


    if (mLevelLost)
    {
        
        if (!mLossTimeSet)
        {
            mLossTime = mTotalTime;
            mLossTimeSet = true;
        }
        // Display level loss reason for 2 seconds before reloading level
        if (mTotalTime - mLossTime < 3)
        {
            DisplayLossString();
        }
        // Reload level after 2 seconds
        else
        {
            Loss();
            mLossTimeSet = false;
        }
    }

    if (mLevelWon)
    {
        if (!mWinTimeSet)
        {
            mWinTime = mTotalTime;
            mWinTimeSet = true;
        }
        // Display level complete for 2 seconds before loading new level
        if (mTotalTime - mWinTime < 3)
        {
            DisplayWinString();
        }
        // Load new level after 2 seconds
        else
        {
          if (mPos < 3)
          {
            Win(mPos + 1);
          } else {
            ResetAttributes(true);
          }
          mWinTimeSet = false;
        }
    }

    for (auto& item : mItems)
    {
        item->Update(elapsed);
        item->SetGameTime(elapsed, false);
    }

    if (!mLevelLost) 
    {
      CheckHit();
    }


    // Timer object
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 24, FontStyleBold);
    SolidBrush white(Color(255, 255, 255));
    wstring minute = std::to_wstring(int(mTotalTime / 60));
    wstring second;
    wstring time;

    if (mDisplayBegin)
    {
        mGraphics->DrawString(L"Get Ready!", -1, &font, PointF(1100, 0), &white);
    }
    else if (mWinTimeSet || mLossTimeSet)
    {
        Gdiplus::Font font2(&fontFamily, 30, FontStyleBold);
        mGraphics->DrawString(L"Level Complete", -1, &font2, PointF(1125, 0), &white);
    }
    else 
    {
        if (int(mTotalTime) % 60 < 10)
        {
            second = L"0" + std::to_wstring(int(mTotalTime) % 60);
        }
        else
        {
            second = std::to_wstring(int(mTotalTime) % 60);
        }
        if (int(mTotalTime / 60) < 10)
        {
            time = L"0" + minute + L":" + second;
        }
        else
        {
            time = minute + L":" + second;
        }
        // Draws timer
        mGraphics->DrawString(time.c_str(), -1, &font, PointF(1125, 0), &white);
    }
}

/** Test an x,y click location to see if it clicked
* on some item in the game.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CGame::ClickTest(int x, int y)
{
    double newx = (x - mXOffset) / mScale;
    double newy = (y - mYOffset) / mScale;
   
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->ClickTest(newx, newy))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Places object of class CItem at the end of the vector.
 * 
 * \param item pointer to game object
 */
void CGame::RepositionItem(std::shared_ptr<CItem> item) 
{
  auto loc = find(begin(mItems), end(mItems), item);
  if (loc != end(mItems)) 
  {
    mItems.erase(loc);
  }
  mItems.push_back(item);
}


/** Accept a visitor for the collection
 * \param visitor The visitor for the collection
 */
void CGame::Accept(CItemVisitor *visitor) 
{
  for (auto item : mItems) 
  {
    item->Accept(visitor);
  }
}


/**
 * When mouse is clicked, check if it is cargo
 * and check if all the cargo has made it to winning
 * side.
 * \param nFlags flags from mouse click
 * \param point point clicked
 */
void CGame::OnButtonDown(UINT nFlags, CPoint point) 
{
  if (!mLossTimeSet && !mWinTimeSet && !mDisplayBegin) 
  {
    CCargoVisitor visitor;
    auto item = ClickTest(point.x, point.y);
    if (item != nullptr &&
        item->GetTagName() != L"protector")  // check if cargo is clicked
    {
      if (mHero->GetPosition().Y() >= mLowerY || mHero->GetPosition().Y() <= mHigherY) {
        visitor.SetInformation(mHero, this);  // set cargo to hero
        visitor.SetCargo(item);
        item->Accept(&visitor);
        RepositionItem(item);
      }
    }

    CEatVisitor eatCheck;
    eatCheck.SetInformation(mHero, this);
    Accept(&eatCheck);
    eatCheck.CheckWin();  // check if all 3 cargo items are there
  }

}


/**
 * If player wins the level.
 * \param nextLevel 
 */
void CGame::Win(int nextLevel)
{
   //Win function must be called in CGame::Update since we are drawing a string
    ChangeLevels(nextLevel);
}


/**
 * If player loses the level.
 */
void CGame::Loss()
{
    // Set everything back to their original spots without reloading level
    ResetAttributes(true);
}

/**
 * Check if cargo is eaten when sparty leaves sidewalk.
 */
void CGame::CheckCargo() 
{
  // Only check if the items have been eaten if there is no protector
  if (GetGameProtectorStatus() == false)
  {
      CEatVisitor eatCheck;
      eatCheck.SetInformation(mHero, this);
      Accept(&eatCheck);
      eatCheck.CheckIfEaten();
      // eatCheck.DeleteItems();

      if (mLevelLost) 
      {
        wstring eatenItem = eatCheck.GetEatenItem();
        wstring itemEater = eatCheck.GetItemEater();
        mLossReason = L"The " + itemEater + L" has eaten the " + eatenItem;
      }
  }
}

/**
 * Checks if hero is hit.
 */
void CGame::CheckHit() 
{
    mHero->SetNearRiver(false);

    for (auto it = mLevels[mPos].GetRiverPositions()->begin();
            it != mLevels[mPos].GetRiverPositions()->end(); it++) 
    {
        if ((*it) == mHero->GetPosition().Y()) 
        {
            mHero->SetNearRiver(true);
        }
    }

    if (!mHero->GetNearRiver()) 
    {
      mHero->SetBoat(nullptr);
    }

    for (auto item : mItems)
    {
      if (item != mHero) 
      {
        if (mHero->GetNearRiver()) 
        {
          item->Distance(mHero, true, mRiverCheat);
        } else {
          item->Distance(mHero, false, mRoadCheat);
        }
      }
    }

    if (!mHero->GetBoat() && mHero->GetNearRiver() && !mRiverCheat) 
    {
      mHero->SetHeroDrown(true);
      if (mHero->GetCarriedItem()) 
      {
        mHero->GetCarriedItem()->SetLocation(-64, 0);
      }
      mHero->SetCarriedItem(nullptr);
      mLevelLost = true;
      mLossReason = mHero->GetName() + L" has fallen into the river";
    }

    if (mHero->GetHit() && !mRoadCheat) 
    {
      mLevelLost = true;
      wstring carHit = mHero->GetCarHit();
      if (mHero->GetCarriedItem()) 
      {
        mHero->GetCarriedItem()->SetLocation(-64, 0);
      }
      mHero->SetCarriedItem(nullptr);
      mLossReason = mHero->GetName() + L" was hit by " + carHit;
    }

    if ((mHero->GetPosition().X() < 0 || mHero->GetPosition().X() > 1024) && mHero->GetNearRiver())
    {
      mLevelLost = true;
      mHero->SetBoat(nullptr);
      mHero->GetCarriedItem()->SetLocation(-64, 0);
      mHero->SetLocation(-64, 0);
      mLossReason = mHero->GetName() + L" has drifted out of bounds";
      
    }

}


/**
 * Moves hero using ESDF or up, down right, left keys.
 * \param nChar char to push
 * \param nRepCnt count
 * \param nFlags flag
 */
void CGame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (!mLossTimeSet && !mWinTimeSet && !mDisplayBegin)
    {
    if (!mHero->GetBoat()) 
    {
      // Left arrow and S key
      if (nChar == VK_LEFT || nChar == 0x53)
      {
        if (mHero->GetPosition().X() > 0) 
        {
          mHero->MoveLeft();
        }
      }
      // Right arrow and F key
      if (nChar == VK_RIGHT || nChar == 0x46) 
      {
        if (mHero->GetPosition().X() < (static_cast<double>(Width) - mHero->GetTileWidth() * 4)) 
        {
          mHero->MoveRight();
        }
      }
    }
        // Up arrow and E key
        if (nChar == VK_UP || nChar == 0x45)
        {
            if (mHero->GetPosition().Y() > mHero->GetTileWidth())
            {
                mHero->MoveUp();
            }
        }
        // Down arrow and D key
        if (nChar == VK_DOWN || nChar == 0x44)
        {
            if (mHero->GetPosition().Y() < mLowerY + mHero->GetTileWidth())
            {
                mHero->MoveDown();
            }
        }

        CCargoVisitor cargoVisitor;
        cargoVisitor.SetInformation(mHero, this);
        cargoVisitor.MoveCargoItem();

        CheckCargo();

        if (mHero->GetPosition().Y() < mLowerY)
        {
            bool check = false;
            mHero->SetIfLower(false);

        }
        else if (mHero->GetPosition().Y() > mHigherY)
        {
            mHero->SetIfLower(true);
        }

        RepositionItem(mHero);
        if (cargoVisitor.RetrieveCargo())
        {
            RepositionItem(mHero->GetItem());
        }

        mHero->SetBoat(nullptr);
    }
}



      