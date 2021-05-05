/**
 * \file XMlLoader.cpp
 *
 * \author Caroline Gormely
 */

#include "pch.h"
#include "XmlLoader.h"
#include "Boat.h"
#include "Car.h"
#include "DecorItem.h"
#include "Rectangle.h"
#include "Cargo.h"
#include "Hero.h"
#include "Level.h"

#include <algorithm>

using namespace std;
using namespace xmlnode;
using namespace Gdiplus;


/**
* Constructor
* \param level - The level whose file is being loaded
* \param filename - The level's XML filename
* \param game - Game we are loading level into
*/
CXmlLoader::CXmlLoader(CLevel* level, wstring& filename, CGame* game)
{
    mLevel = level;
    mFilename = filename;
    mGame = game;
    mMapItemImages = game->GetImageMap();
}

/**
* Creates Item objects that represent rectangles
* \param node The XML node we are loading
*/
void CXmlLoader::XmlRectTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    shared_ptr<CItem> rect;
    std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(nullptr, nullptr);
    rect = make_shared<CRectangle>(mGame, imagePair);
    Add(rect);
    rect->XmlLoad(node);
}

/**
* Creates DecorItem objects
* \param node The XML node we are loading
*/
void CXmlLoader::XmlDecorTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    shared_ptr<CItem> decorItem;
    wstring id = node->GetAttributeValue(L"id", L"");
    std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = (*mMapItemImages)[id];
    decorItem = make_shared<CDecorItem>(mGame, imagePair);
    Add(decorItem);
    decorItem->XmlLoad(node);
}

/**
* Parses the background tag
* \param node The XML node we are loading
*/
void CXmlLoader::XmlBackgroundTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"decor")
        {
            XmlDecorTag(child);
        }
        else if (child->GetType() == NODE_ELEMENT && child->GetName() == L"rect")
        {
            XmlRectTag(child);
        }
    }
}

/**
* Creates Hero object from the hero tag
* \param node The XML node we are loading
*/
void CXmlLoader::XmlHeroTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    wstring filename = L"images/";
    shared_ptr<CHero> hero;
    wstring name = node->GetAttributeValue(L"name", L"");
    
    if (mMapItemImages->find(name) == mMapItemImages->end()) 
    {
      filename = filename + node->GetAttributeValue(L"image", L"");
      wstring hitHeroImage = node->GetAttributeValue(L"hit-image", L"");

      hitHeroImage = L"images/" + hitHeroImage;
      shared_ptr<Bitmap> image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
      shared_ptr<Bitmap> image2 = shared_ptr<Bitmap>(Bitmap::FromFile(hitHeroImage.c_str()));
      std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(image1, image2);

      (*mMapItemImages)[name] = imagePair;

      wstring maskHeroImage = L"images/" + node->GetAttributeValue(L"mask", L"");
      auto maskImage = shared_ptr<Bitmap>(Bitmap::FromFile(maskHeroImage.c_str()));

      (*mMapItemImages)[L"accessories"] = make_pair(maskImage, nullptr);

    }

    auto imagePair = (*mMapItemImages)[name];
    hero = make_shared<CHero>(mGame, imagePair);
    mLevel->SetHero(hero);


    Add(hero);
    hero->XmlLoad(node);
}

/**
* Creates Cargo objects from the cargo tags
* \param node The XML node we are loading
*/
void CXmlLoader::XmlCargoTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{ 
    wstring filename1 = L"images/";
    wstring filename2 = L"images/";
    shared_ptr<CItem> cargo;
    wstring name = node->GetAttributeValue(L"name", L"");
    if (mMapItemImages->find(name) == mMapItemImages->end()) 
    {
      filename1 = filename1 + node->GetAttributeValue(L"image", L"");
      filename2 = filename2 + node->GetAttributeValue(L"carried-image", L"");
      shared_ptr<Bitmap> image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename1.c_str()));
      shared_ptr<Bitmap> image2 = shared_ptr<Bitmap>(Bitmap::FromFile(filename2.c_str()));
      std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(image1, image2);
      (*mMapItemImages)[name] = imagePair;
    }

    auto imagePair = (*mMapItemImages)[name];
    cargo = make_shared<CCargo>(mGame, imagePair); 
    Add(cargo);
    cargo->XmlLoad(node);
}

/**
* Creates Car objects from the car tags that are children of the road tags
* \param node The XML node whose children (the cars) we are loading
*/
void CXmlLoader::XmlRoadTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double positionY = node->GetAttributeDoubleValue(L"y", 0);

    for (auto child : node->GetChildren())
    {
        double swapTime = 0.5; //< default
        wstring id = child->GetAttributeValue(L"id", L"");
        std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = (*mMapItemImages)[id];
        double positionX = child->GetAttributeDoubleValue(L"x", 0);
        wstring wsSwapTime = child->GetAttributeValue(L"swap-time", L"");
        if (wsSwapTime != L"")
            swapTime = std::stod(wsSwapTime);
        shared_ptr<CCar> car = make_shared<CCar>(mGame, imagePair);
        car->SetLocation(positionX * car->GetTileWidth(), positionY * car->GetTileWidth());
        car->SetStartingLocation(car->GetPosition());
        car->SetName(mIDNames[id]);
        wstring check = car->GetName();
        car->SetSwapTime(swapTime);
        car->XmlLoad(node);
        Add(car);
    }
}

/**
* Creates Boat objects from the boat tags that are children of the river tags
* \param node The XML node whose children (the boats) we are loading
*/
void CXmlLoader::XmlRiverTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    shared_ptr<CItem> boat;
    
    double positionY = node->GetAttributeDoubleValue(L"y", 0);
    mLevel->GetRiverPositions()->push_back(positionY * 64);

    for (auto child : node->GetChildren()) 
    {
      wstring id = child->GetAttributeValue(L"id", L"");
      std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = (*mMapItemImages)[id];
      boat = make_shared<CBoat>(mGame, imagePair);
      double positionX = child->GetAttributeDoubleValue(L"x", 0);
      boat->SetLocation(positionX * boat->GetTileWidth(), positionY * boat->GetTileWidth());
      boat->SetStartingLocation(boat->GetPosition());
      boat->SetName(id);
      boat->XmlLoad(node);
      Add(boat);
    }
}

/**
* Creates the maps with the id, image pairs obtained from the XML tags
* \param node The Xml node we are loading the id and image from
*/
void CXmlLoader::XmlTypesTag(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto childNode : node->GetChildren())
    {
        wstring name = childNode->GetName();
        wstring id = childNode->GetAttributeValue(L"id", L"");
        if (mMapItemImages->find(id) == mMapItemImages->end()) 
        {
          if (name == L"decor" || name == L"boat") 
          {
            wstring filename = L"images/" + childNode->GetAttributeValue(L"image", L"");
            auto image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
            auto image2 = nullptr;

            (*mMapItemImages)[id] = make_pair(image1, image2);
          } else if (name == L"car")
          {
            wstring filename1 = L"images/" + childNode->GetAttributeValue(L"image1", L"");
            wstring filename2 = L"images/" + childNode->GetAttributeValue(L"image2", L"");
            auto image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename1.c_str()));
            auto image2 = shared_ptr<Bitmap>(Bitmap::FromFile(filename2.c_str()));

            (*mMapItemImages)[id] = make_pair(image1, image2);

          }
        }

        wstring objectName = childNode->GetAttributeValue(L"name", L"");
        mIDNames[id] = objectName;

    }
}

/**
 * Load the file from XML
 * \param filename The file to load.
 * \return vector of items in the level that was loaded
 */
vector<shared_ptr<CItem>> CXmlLoader::Load(std::wstring& filename)
{
        // We surround with a try/catch to handle errors
        try
        {
            // Open the document to read
            shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

            // Once we know it is open, clear the existing data
            Clear();

            // Traverse the children of the root
            //
            for (auto node : root->GetChildren())
            {
                if (node->GetName() == L"types")
                {
                    XmlTypesTag(node);
                }
                else if (node->GetName() == L"background")
                {
                    XmlBackgroundTag(node);
                }

                else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"river")
                {
                    XmlRiverTag(node);
                }
                else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"road")
                {
                   XmlRoadTag(node);
                }
                else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"hero")
                {
                    XmlHeroTag(node);
                }
                else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"cargo")
                {
                    XmlCargoTag(node);
                }
                else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"protector")
                {
                    mLevel->SetProtectorStatus(true);
                    XmlCargoTag(node);
                }
            }
        }
        catch (CXmlNode::Exception ex)
        {
            AfxMessageBox(ex.Message().c_str());
        }
   return mItems;
}


/**
 * Clear the game data.
 *
 * Deletes all known items in the game.
 */
void CXmlLoader::Clear()
{
    mItems.clear();
}

/**
 * Add an item to the game
 * \param item New item to add
 */
void CXmlLoader::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

