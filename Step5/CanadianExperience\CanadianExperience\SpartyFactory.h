/**
 * \file SpartyFactory.h
 *
 * \author Winnie Yang
 *
 * Factory class that builds Sparty.
 */



#pragma once

#include "ActorFactory.h"
#include "Actor.h"

#include <memory>

using namespace std;

/**
 * Factory class that builds Sparty.
 */
class CSpartyFactory : public CActorFactory
{
public:
	/// Initial create function
	std::shared_ptr<CActor> Create();
};

