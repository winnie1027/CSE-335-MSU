/**
 * \file Vehicle.cpp
 *
 * \author
 */

#include "pch.h"
#include "Vehicle.h"
#include "Game.h"
#include <cmath>

using namespace Gdiplus;
using namespace std;

/// Constructor for a vehicle object
/// \param game Game this vehicle is in
/// \param imagePair - the pair of images for the vehicle 
CVehicle::CVehicle(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair)
{
}

/**
*  Load the attributes for a vehicle node.
* \param node The Xml node we are loading the item from
*/
void CVehicle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) 
{
  mSpeed = node->GetAttributeDoubleValue(L"speed", 0);
  mWidth = node->GetAttributeDoubleValue(L"width", 0);
}

/**
*  Update the vehicle item. Overrides CItem::Update()
* \param elapsed The time this update is called
*/
void CVehicle::Update(double elapsed) 
{
    int maxXSpot = 1024 + (mWidth - 16)/2 * GetTileWidth();
    int minXSpot = -((mWidth - 16)/2 * GetTileWidth());

    if (mSpeed > 0 && (GetPosition().X() >= maxXSpot))
    {
        SetLocation(minXSpot, GetPosition().Y());
    }
    else if (mSpeed < 0 && (GetPosition().X() <= minXSpot))
    {
        SetLocation(maxXSpot, GetPosition().Y());
    }
    else
    {
        SetLocation((GetPosition().X() + (mSpeed * elapsed) * GetTileWidth()), GetPosition().Y());
    }

    
}

/**
 * Determine the distance from this item to some other item.
 * \param hero Hero item we are testing
 * \param isBoat true if the item is a CBoat object
 * \returns boolean
 */
bool CVehicle::CalculateDistance(std::shared_ptr<CHero> hero, bool isBoat)
{
  double left = GetPosition().X(); // left side of boat
  double right = GetPosition().X() + GetWidth(); //right side of boat

  //get middle of boat; get left side by - half boat width, get right side by + half boat width, see if sparty's position falls within that position
  if (hero->GetPosition().Y() == GetPosition().Y()) 
  {
    
    if (isBoat) 
    { // If hero on boat, check if it is between the left and right bounds of boat
      if (hero->GetPosition().X() + hero->GetWidth() / 2 >= left &&
          hero->GetPosition().X() + hero->GetWidth() / 2 <= right) 
      {
        return true;
      }
    } else 
    {
      /// Calculate distance between hero and center of car (X direction
      /// only)
      if (mSpeed > 0) 
      { /// calculations for car going right
        return (abs(hero->GetPosition().X() - hero->GetWidth() / 2 -
                    GetPosition().X() - GetWidth() / 2) <= 50);
      } else 
      { /// calculations for car going left
        return (abs(hero->GetPosition().X() - hero->GetWidth() / 2 -
                    GetPosition().X() + GetWidth() / 2) <= 50);
      }
     
    }

  }

  // Return false if not in the same lane
  return false;
    
}

