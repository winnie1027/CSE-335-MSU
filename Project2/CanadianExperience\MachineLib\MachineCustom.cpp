/**
 * \file MachineCustom.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "MachineCustom.h"

using namespace std;

CMachineCustom::CMachineCustom(int machine) : mMachineNumber(machine)
{
}

void CMachineCustom::Draw(Graphics* graphics)
{
	for (auto component : mComponents)
	{
		component->Draw(graphics, mPosition);
	}
}

void CMachineCustom::SetMachineFrame(int frame)
{
	for (auto component : mComponents)
	{
		component->SetTime(frame/mFrameRate);
	}
}
