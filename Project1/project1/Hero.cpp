/**
 * \file Hero.cpp
 *
 * \author Caroline Gormely
 */



#include "pch.h"
#include "Hero.h"
#include "Boat.h"
#include "Car.h"



using namespace Gdiplus;
using namespace std;

/** Constructor
* \param game The game this hero is
* \param imagePair The pair of images for this item
*/
CHero::CHero(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair)
{
  mHitImage = imagePair.second;
  mMaskImage = (*game->GetImageMap())[L"accessories"].first;
}

/**
* brief Load the attributes for a hero node.
* \param node The Xml node we are loading the item from
*/
void CHero::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) 
{
  CItem::XmlLoad(node);

  SetLocation(mStartX * GetTileWidth(), mStartY * GetTileWidth());
  SetStartingLocation(GetPosition());
}

/**
 * Updates the hero
 * \param elapsed The amount of time when update is called
 */
void CHero::Update(double elapsed) 
{
  if (GetBoat()) 
  {
    SetLocation(mBoat->GetPosition().X() + mBoat->GetWidth()/2 - GetWidth()/2,
                mBoat->GetPosition().Y());
    if (mCargo)
    {
      mCargo->SetLocation(this->GetPosition().X(), this->GetPosition().Y());
    }
  } 
  else 
  {
    SetLocation(GetPosition().X(), GetPosition().Y());
  }


}

/**
 * Draws the hero
 * \param graphics The graphics context to draw on
 */
void CHero::Draw(Gdiplus::Graphics* graphics)
{
    
    if (mHit) {

        if (mHitImage)
        {

            double wid = mHitImage->GetWidth();
            double hit = mHitImage->GetHeight();

            // double check = mP.X();

            graphics->DrawImage(mHitImage.get(),
                (float(CItem::GetPosition().X())),
                (float(CItem::GetPosition().Y())),
                (float)mHitImage->GetWidth(),
                (float)mHitImage->GetHeight());


        }
    }

    else if (mDrown) 
    {
      bool check = true;
        if (mMaskImage)
        {
            CItem::Draw(graphics);

            double wid = mMaskImage->GetWidth();
            double hit = mMaskImage->GetHeight();

            graphics->DrawImage(mMaskImage.get(),
                (float(CItem::GetPosition().X())),
                (float(CItem::GetPosition().Y())),
                (float)mMaskImage->GetWidth(),
                (float)mMaskImage->GetHeight());


        }
        
    }
    else 
    { 
        
      CItem::Draw(graphics);

    }

}

/**
* Set the hero back to the beginning
*/
void CHero::Reset()
{
    SetLocation(GetStartingPosition().X(), GetStartingPosition().Y());
    SetBoat(nullptr);
    mDrown = false;
    mHit = false;
    mCarriedItem = nullptr;
    mCargo = nullptr;
    mOnLower = true;
}