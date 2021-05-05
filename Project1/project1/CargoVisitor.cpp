/**
 * \file CargoVisitor.cpp
 *
 * \author Sirena Ly
 */



#include "pch.h"
#include "CargoVisitor.h"
#include "Cargo.h"


/**
 * Set the clicked cargo with the Hero.
 * 
 * \param cargo Cargo to be set with the Hero
 */
void CCargoVisitor::VisitCargo(CCargo* cargo) {
  if (!mHero->GetCarriedItem())  // if the Hero is not carrying an item, set the
                                 // clicked item
  {
    mHero->SetCarriedItem(cargo);
    
    if ((mHero->GetPosition().Y() >= mGame->GetHigherPlace() &&
         mHero->GetCarriedItem()->GetPosition().Y() >=
             mGame->GetHigherPlace()) ||
        (mHero->GetPosition().Y() <= mGame->GetLowerPlace() &&
         mHero->GetCarriedItem()->GetPosition().Y() <=
             mGame->GetLowerPlace()))  // if limits sparty to pick up only one
                                       // specific side
    {
          mHero->GetCarriedItem()->SetItemCarried(true);
          mHero->GetCarriedItem()->SetLocation(mHero->GetPosition().X(),
                                               mHero->GetPosition().Y());
    } 
    else 
    {
      mHero->SetCarriedItem(nullptr);
      SetCargo(nullptr);
    } 
  } 
  else 
  {
    if (mHero->GetCarriedItem() == cargo) // releases the cargo
    {
      if (mHero->GetPosition().Y() >= mGame->GetLowerPlace()) 
      {
        mHero->GetCarriedItem()->SetItemCarried(false);
        mHero->GetCarriedItem()->SetLocation(mHero->GetCarriedItem()->GetStartingX(), mGame->GetLowerPlace() + mHero->GetTileWidth());
        mHero->SetCarriedItem(nullptr);
      } 
      else if (mHero->GetPosition().Y() <= mGame->GetHigherPlace()) 
      {
        mHero->GetCarriedItem()->SetItemCarried(false);
        mHero->GetCarriedItem()->SetLocation(
        mHero->GetCarriedItem()->GetStartingX(), 0);
        mHero->SetCarriedItem(nullptr);
      }

      SetCargo(nullptr);

    } 
    else // swaps the cargo with a different cargo that was clicked
    {
       mHero->GetCarriedItem()->SetItemCarried(false);
      if (mHero->GetIfLower()) 
      {
        mHero->GetCarriedItem()->SetLocation(
            mHero->GetCarriedItem()->GetStartingX(),
            mGame->GetLowerPlace() + mHero->GetTileWidth());
      } 
      else 
      {
        mHero->GetCarriedItem()->SetLocation(
            mHero->GetCarriedItem()->GetStartingX(),
            0);
      }
       mHero->SetCarriedItem(cargo);
       mHero->GetCarriedItem()->SetItemCarried(true);
       mHero->GetCarriedItem()->SetLocation(mHero->GetPosition().X(),
                                           mHero->GetPosition().Y());

    }
  }


}
