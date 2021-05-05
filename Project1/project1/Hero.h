/**
 * \file Hero.h
 *
 * \author Caroline Gormely
 *
 * Class for the hero in our game.
 */


#pragma once
#include "Item.h"


/**
 * Class for the hero in our game.
 */
class CHero : public CItem 
{
 public:

  CHero(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);

  /// Delete default constructor
  CHero() = delete;

  /// Delete copy constructor
  CHero(const CHero &) = delete;

  /// Moves hero to the left
  void MoveLeft() { SetLocation(GetPosition().X() - GetTileWidth(), GetPosition().Y()); }

  /// Moves hero to the right
  void MoveRight() { SetLocation(GetPosition().X() + GetTileWidth(), GetPosition().Y()); }

  /// Moves hero up
  void MoveUp() { SetLocation(GetPosition().X(), GetPosition().Y() - GetTileWidth()); }

  /// Moves hero down
  void MoveDown() { SetLocation(GetPosition().X(), GetPosition().Y() + GetTileWidth()); }

  /// Sets Hit member variable to true
  /// \param check - True if we checking for a hit, False otherwise 
  void SetHeroHit(bool check) { mHit = check;}

  /// Sets the mDrawn depending on if the hero has drown
  /// \param check
  void SetHeroDrown(bool check) { mDrown = check; }

  virtual void Draw(Gdiplus::Graphics* graphics) override;

  virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

  virtual void Update(double elapsed) override;

  /// Sets cargo item to hero
  /// \param cargo
  void SetCarriedItem(CCargo* cargo) { mCarriedItem = cargo; }

  /// Gets cargo item carried by hero
  /// \returns mCarriedItem
  CCargo* GetCarriedItem() { return mCarriedItem; }

  /** Accept a visitor
   * \param visitor The visitor we accept */
  virtual void Accept(CItemVisitor* visitor) override 
  {
    visitor->VisitHero(this);
  }

  /// Sets if lower
  /// \param set
  void SetIfLower(bool set) { mOnLower = set; }

  /// Gets if lower
  /// \returns mOnLower
  bool GetIfLower() { return mOnLower; }

  /// Sets item
  /// \param item
  void SetItem(std::shared_ptr<CItem> item) { mCargo = item; }
  
  /// Gets item
  /// \returns mCargo
  std::shared_ptr<CItem> GetItem() { return mCargo; }

  /// Returns hit status of hero
  /// \returns mHit
  bool GetHit() { return mHit; }

  /// Returns drowning status of hero
  /// \returns mDrown
  bool GetDrown() { return mDrown; }

  /// Sets hero to a boat
  /// \param boat
  void SetBoat(CBoat* boat) { mBoat = boat; }

  /// Gets boat hero is on
  /// \returns mBoat
  CBoat* GetBoat() { return mBoat; }

  /// Sets if hero is near river
  /// \param check
  void SetNearRiver(bool check) { mNearRiver = check; }

  /// Returns if hero is near river
  /// \returns mNearRiver
  bool GetNearRiver() { return mNearRiver; }

  /// Sets ID of the car that hit hero
  /// \param carID
  void SetCarHitID(std::wstring carID) { mHitCarID = carID;}

  /// Returns ID of car that hit hero
  /// \returns mHitCarID
  wstring GetCarHit() { return mHitCarID; }

  /// Sets mask image 
  /// \param image
  void SetMaskImage(std::shared_ptr<Gdiplus::Bitmap> image) 
  {
    mMaskImage = image;
  }

  /// Returns the mask image
  /// \returns mMaskImage
  std::shared_ptr<Gdiplus::Bitmap>* GetMaskImage() { return &mMaskImage; }

  /// Reset the items location
  virtual void Reset() override;


 private:
  /// Image of the hero when it has been hit
  std::shared_ptr<Gdiplus::Bitmap> mHitImage = nullptr;

  /// Image of the mask that goes in front of the hero when
  /// it falls into the water
  std::shared_ptr<Gdiplus::Bitmap> mMaskImage = nullptr;

  /// Pointer to the cargo that the hero is currently carrying
  CCargo* mCarriedItem = nullptr;

  /// Reposition carried item in front
  std::shared_ptr<CItem> mCargo = nullptr;

  /// Sets hero on boat
  CBoat* mBoat = nullptr;

  /// Gets name of car that hit hero
  wstring mHitCarID = L"";

  /// If hero is hit by a car
  bool mHit = false;

  /// If hero drowns
  bool mDrown = false;

  /// If hero is on a river
  bool mNearRiver = false;

  /// If hero is on lower part of game
  bool mOnLower = true;

  /// startingX
  double mStartX = 7.5;

  /// startingY
  double mStartY = 14;
};
