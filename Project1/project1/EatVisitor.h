/**
 * \file EatVisitor.h
 *
 * \author Sirena Ly
 *
 * Defines the visitor to check if cargo has been eaten.
 */

#pragma once
#include "ItemVisitor.h"
#include "Game.h"
#include "Cargo.h"


/**
 * Defines Eaten Visitor class. Checks for loss condition.
 */
class CEatVisitor : public CItemVisitor 
{
 public:
  /** Gives information to visitor.
   * \param hero Hero that item is set to
   * \param game - game this is in
   */
  void SetInformation(shared_ptr<CHero> hero, CGame* game) 
  {
    mHero = hero;
    mGame = game;
  }

  ///  Checks if cargo item has been eaten
  void CheckIfEaten();

  ///  Checks if this level has been won
  void CheckWin();

  /// Visits cargo object
  /// \param cargo - cargo object
  virtual void CEatVisitor::VisitCargo(CCargo* cargo) override;

  /// Returns the eaten item
  /// \returns mEaten
  wstring GetEatenItem() { return mEaten; }

  /// Returns the item that did the eating
  /// \returns mAte
  wstring GetItemEater() { return mAte; }

 private:
  shared_ptr<CHero> mHero;  ///< Hero in game
  CGame* mGame; ///< Current game we are playing
  vector<CCargo*> mCargoItems;  ///< Temporary list to check all cargo items

  wstring mEaten; ///< Item eaten
  wstring mAte; ///< Item that ate
};
