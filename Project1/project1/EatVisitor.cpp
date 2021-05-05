#include "pch.h"
#include "EatVisitor.h"
#include <algorithm>


void CEatVisitor::VisitCargo(CCargo* cargo)
{ 
	if (mHero->GetCarriedItem() != cargo) {
        if (mHero->GetIfLower() && cargo->GetPosition().Y() >= mGame->GetLowerPlace()) 
        {
           mCargoItems.push_back(cargo);  // create temporary list of cargo items
           
        } else if (!mHero->GetIfLower() && cargo->GetPosition().Y() <= mGame->GetHigherPlace()) 
        {
           mCargoItems.push_back(cargo);
        }
    }

}


void CEatVisitor::CheckIfEaten() 
{ 
  double check = mCargoItems.size();
  for (auto it = mCargoItems.begin(); it != mCargoItems.end(); it++)
  {
    auto eats = (*it)->GetItemEats(); // get the item that the each cargo eats
    for (auto it2 = mCargoItems.begin(); it2 != mCargoItems.end(); it2++) 
	{
      auto itemID = (*it2)->GetId(); // check if eaten item is within the vector
      if (itemID == eats) 
      {
        if (mHero->GetPosition().Y() < mGame->GetLowerPlace() && mHero->GetPosition().Y() > mGame->GetHigherPlace()) 
        {
          bool check = true;
          mGame->SetLoss();
          mEaten = eats;
          mAte = (*it)->GetId();
        }
      }
    }
  
  }

}

void CEatVisitor::CheckWin() 
{
  double win = 3;
  bool check = false;
  if (mCargoItems.size() == win) 
  {
    for (auto it = mCargoItems.begin(); it != mCargoItems.end(); it++) 
    {
      if ((*it)->GetPosition().Y() <= mGame->GetHigherPlace()) 
      {
        check = true;
      } else 
      {
        check = false;
      }
      
    }
  }

  if (check) 
  {
    mGame->SetWin();
  }
}


