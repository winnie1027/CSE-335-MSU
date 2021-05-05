/**
 * \file Item.cpp
 *
 * \author Winnie Yang
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"


 /** Constructor
 * \param aquarium The aquarium this item is a member of
 */
CItem::CItem(CAquarium* aquarium) : mAquarium(aquarium)
{
}


/**
 * Destructor
 */
CItem::~CItem()
{
}