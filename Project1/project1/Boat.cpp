/**
 * \file Boat.cpp
 *
 * \author
 */


#include "pch.h"
#include "Boat.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The game this boat is 
* \param imagePair The pair of images for this item
*/
CBoat::CBoat(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CVehicle(game, imagePair)
{

}

/**
*  Load the attributes for a boat node.
* \param node The Xml node we are loading the item from
*/
void CBoat::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) 
{
  CVehicle::XmlLoad(node);
}

void CBoat::Distance(std::shared_ptr<CHero> hero, bool heroNearRiver, bool cheat) 
{
  if (heroNearRiver) 
  {
    bool check = CVehicle::CalculateDistance(hero, true);
    if (check && !hero->GetBoat()) 
    {
      if (!cheat) 
      {
        hero->SetBoat(this);
      }
    } 
    
  } else 
  {
    hero->SetBoat(nullptr);
  }
}






