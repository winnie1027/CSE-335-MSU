/**
 * \file MachineFactory.cpp
 *
 * \author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineFactory.h"
#include "Machine.h"
#include "MachineTemp.h"


using namespace std;


/**
 * Create a machine object
 * \returns Object of type CMachine
 */
std::shared_ptr<CMachine> CMachineFactory::CreateMachine()
{
    return make_shared<CMachineTemp>();
}

