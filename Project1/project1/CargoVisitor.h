/**
 * \file CargoVisitor.h
 *
 * \author Sirena Ly
 *
 * Defines the visitor class that sets a cargo item to a Hero. 
 */

#pragma once
#include "ItemVisitor.h"
#include "Cargo.h"
#include "Game.h"


/**
 * Class for a cargo visitor.
 */
class CCargoVisitor : public CItemVisitor 
{
 public:
  /** Gives information to visitor.
   * \param hero Hero that item is set to
   \param game - game the cargo items being visited are in*/
  void SetInformation(shared_ptr<CHero> hero, CGame* game) 
  { 
	mHero = hero;
    mGame = game;
  }

  /// Gets the cargo item
    /// \returns item associated with the hero
  shared_ptr<CItem> RetrieveCargo() 
  { 
    if (mHero->GetItem()) 
    {
      return mHero->GetItem();
    }

    return nullptr;
  }

  /// Sets the cargo to the hero
  /// \param item 
  void SetCargo(std::shared_ptr<CItem> item) 
  { 
      mHero->SetItem(item);
  }

  /** Moves item along with the hero.
   * */
  void MoveCargoItem() 
  {
    if (mHero->GetCarriedItem()) 
    {
      mHero->GetCarriedItem()->SetLocation(mHero->GetPosition().X(),
                                           mHero->GetPosition().Y());
    }
  }

  virtual void CCargoVisitor::VisitCargo(CCargo* cargo) override;

 private:
  shared_ptr<CHero> mHero; ///< Hero in game
  shared_ptr<CItem> mItem; ///< Item hero carries
  CGame* mGame;  ///< Game
 
};
