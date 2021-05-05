/**
 * \file MachineTwoFactory.h
 *
 * \author Winnie Yang
 *
 * The machine factory that creates machine two.
 */



#pragma once

#include <memory>

#include "MachineCustom.h"


/**
 * The machine factory that creates machine two.
 */
class CMachineTwoFactory
{
public:
	/// Constructor
	CMachineTwoFactory();

	/// Destructor
	virtual ~CMachineTwoFactory();

	/**
	* Create Machine #2
	* \return Working machine
	*/
	std::shared_ptr<CMachineCustom> Create();
};

