/**
 * \file Car.cpp
 *
 * \author 
 */


#include "pch.h"
#include "Car.h"

using namespace Gdiplus;
using namespace std;

/** Constructor
* \param game The game this car is
* \param imagePair The pair of images for this item
*/
CCar::CCar(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CVehicle(game, imagePair)
{
  mCarImageTwo = imagePair.second;
}

/**
* brief Load the attributes for a car node.
* \param node The Xml node we are loading the item from
*/
void CCar::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) 
{
	CVehicle::XmlLoad(node);
	/*if (mCarImageTwo->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += secondCarImage;
		AfxMessageBox(msg.c_str());
	}*/
}

/**
 *
 * Set car's second image.
 * \param filename
 */
void CCar::SetSecondImage(wstring& filename)
{
	mCarImageTwo = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
}

/**
 * Update our car
 * \param elapsed The amount of time when update is called
 */
void CCar::Update(double elapsed)
{
	UpdateTime(elapsed);
	if (mTimeTotal >= mSwapTime)
	{
		SwitchSwapBool();
		ResetTime();
	}
	CVehicle::Update(elapsed);
}

/**
 * Draw our car
 * \param graphics The graphics context to draw on
 */
void CCar::Draw(Gdiplus::Graphics* graphics)
{
	if (mSwapped)
	{
		double wid = mCarImageTwo->GetWidth();
		double hit = mCarImageTwo->GetHeight();

		double check = GetX();

		graphics->DrawImage(mCarImageTwo.get(),
			(float(GetX())),
			(float(GetY())),
			(float)mCarImageTwo->GetWidth(),
			(float)mCarImageTwo->GetHeight());
	}
	else
	{
		CItem::Draw(graphics);
	}
}


/**
 * Determine the distance from this item to some other item.
 * \param hero Hero in the game
 * \param heroNearRiver 
 * \param cheat True if the RoadCheat menu option has been selected, False otherwise
 * \return Distance in pixels
 */
void CCar::Distance(std::shared_ptr<CHero> hero, bool heroNearRiver, bool cheat) { 
	
  if (!heroNearRiver) 
  {
    bool check = CVehicle::CalculateDistance(hero, false);
    if (check) 
	{
      if (!cheat) 
	  {
        hero->SetHeroHit(true);
        hero->SetCarHitID(GetName());
      }
    }
  }
  
}