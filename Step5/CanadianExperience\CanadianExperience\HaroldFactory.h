/**
 * \file HaroldFactory.h
 *
 * \author Winnie Yang
 *
 * Factory class that builds the Harold character 
 */


#pragma once

#include "ActorFactory.h"
#include "Actor.h"

#include <memory>

using namespace std;


/**
 * Factory class that builds the Harold character 
 */
class CHaroldFactory : public CActorFactory
{
public:
	/// Initial create function
	std::shared_ptr<CActor> Create();
};

