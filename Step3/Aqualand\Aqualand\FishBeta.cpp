/**
 * \file FishBeta.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include <string>
#include "FishBeta.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium* aquarium) : CFish(aquarium, FishBetaImageName)
{
    double betaSpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    double betaSpeedY = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);

    SetSpeed(betaSpeedX, betaSpeedY);
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"beta");
    return itemNode;
}
