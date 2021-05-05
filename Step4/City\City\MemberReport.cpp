#include "pch.h"
#include <sstream>
#include <iostream>
#include "MemberReport.h"
#include "Tile.h"

using namespace std;

/**
 * Constructor
 * @param tile File this report is for. 
*/
CMemberReport::CMemberReport(std::shared_ptr<CTile> tile) : mTile(tile)
{
}

/**
 * Generate the report line that is displayed.
 * @return String report line
*/
std::wstring CMemberReport::Report()
{
    wstringstream str;
    str << mTile->GetX() << L", " << mTile->GetY() << L": " << mReport;
    return str.str();
}