#include "pch.h"
#include "Level.h"

#include "XMlNode.h"
#include "DecorItem.h"
#include "Cargo.h"
#include "Car.h"
#include "Boat.h"
#include "Hero.h"
#include "XMlLoader.h"

/// Level constructor
/// \param filename - name of the XML file for this level
/// \param game - game this level is in
///
CLevel::CLevel(CGame* game, wstring& filename)
{
    mFilename = filename;
    mGame = game;
}

/// Loads the level by calling CXmlLoader load function
void CLevel::Load() 
{ 
    CXmlLoader xLoader(this, mFilename, mGame);
    mLevelItems = xLoader.Load(mFilename);

}



