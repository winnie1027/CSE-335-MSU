/**
 * \file DecorCastle.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "DecorCastle.h"
#include "Aquarium.h"

/// Castle file name
const std::wstring CastleImageName = L"images/castle.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CDecorCastle::CDecorCastle(CAquarium* aquarium) : CItem(aquarium, CastleImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode>
CDecorCastle::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);
    itemNode->SetAttribute(L"type", L"castle");
    return itemNode;
}