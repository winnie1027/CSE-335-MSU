/**
 * \file MachineTemp.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "MachineTemp.h"

CMachineTemp::CMachineTemp()
{
	SetMachineNumber(1);
}

void CMachineTemp::SetMachineNumber(int machine)
{
	if (machine == 1)
	{
		CMachineOneFactory factoryOne;
		mMachineCustom = factoryOne.Create();		
	}
	else if (machine == 2)
	{
		CMachineTwoFactory factoryTwo;
		mMachineCustom = factoryTwo.Create();
	}
}
