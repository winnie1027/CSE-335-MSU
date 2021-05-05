/**
 * \file Magikarp.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include <string>
#include "Magikarp.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring MagikarpImageName = L"images/magikarp.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CMagikarp::CMagikarp(CAquarium* aquarium) : CFish(aquarium, MagikarpImageName)
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
CMagikarp::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"magi");
    return itemNode;
}

