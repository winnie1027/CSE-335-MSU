/**
 * \file XMlLoader.h
 *
 * \author 
 *
 * 
 */

#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "XmlNode.h"
#include "Item.h"
#include "Level.h"

using namespace std;

class Level;
/**
 * Class that loads XML
 */
class CXmlLoader
{
public:
    /// Default constructor (disabled)
    CXmlLoader() = delete;

    /// Copy constructor (disabled)
    CXmlLoader(const CXmlLoader&) = delete;

   // CXmlLoader(CGame* game);

    CXmlLoader(CLevel* level, wstring& filename, CGame* game);

    std::vector<shared_ptr<CItem>> Load(std::wstring& filename);

    void Clear();

    void Add(std::shared_ptr<CItem> item);

    void XmlRoadTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlRiverTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlTypesTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlCargoTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlHeroTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlBackgroundTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlDecorTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    void XmlRectTag(const std::shared_ptr<xmlnode::CXmlNode>& node);

    
private:

    /// Game we are loading files for
    CGame* mGame;

    /// Level we are loading files for
    CLevel* mLevel;

    /// Filename of the XML document being loaded
    wstring mFilename = L"";

    /// Vector of items currently in the game 
    std::vector<shared_ptr<CItem>> mItems;

    /// Map with ID as key and loaded image pair as value
    std::map<wstring, std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>>>* mMapItemImages;

    /// Map ID with a name
    std::map<wstring, wstring> mIDNames;

};
