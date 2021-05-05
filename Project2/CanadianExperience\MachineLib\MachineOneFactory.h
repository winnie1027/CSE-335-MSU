/**
 * \file MachineOneFactory.h
 *
 * \author Winnie Yang
 *
 * The machine factory that creates machine one.
 */


#pragma once

#include <memory>

#include "MachineCustom.h"


/**
 * The machine factory that creates machine one.
 */
class CMachineOneFactory
{
public:
	/// Constructor
	CMachineOneFactory();

	/// Destructor
	virtual ~CMachineOneFactory();

	/**
	* Create Machine #1
	* \return Working machine
	*/
	std::shared_ptr<CMachineCustom> Create();

};

