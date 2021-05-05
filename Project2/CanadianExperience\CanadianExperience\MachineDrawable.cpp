/**
 * \file MachineDrawable.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "MachineDrawable.h"
#include "MachineFactory.h"
#include "MachineDlg.h"

CMachineDrawable::CMachineDrawable(const std::wstring& name) : CDrawable(name)
{
	CMachineFactory factory;
	mMachine = factory.CreateMachine();
}

void CMachineDrawable::Draw(Gdiplus::Graphics* graphics)
{
	int frame = mTimeline->GetCurrentFrame();
    if (frame >= mStartFrame)
    {
        mMachine->SetMachineFrame(frame - mStartFrame);
    }
    else
    {
        mMachine->SetMachineFrame(0);
    }

    float scale = 0.5f;
    auto save = graphics->Save();
    graphics->TranslateTransform((float)mPlacedPosition.X,
        (float)mPlacedPosition.Y);
    graphics->ScaleTransform(scale, scale);
    mMachine->DrawMachine(graphics);
    graphics->Restore(save);
}

void CMachineDrawable::SetTimeline(CTimeline* timeline)
{
    CDrawable::SetTimeline(timeline);
    mTimeline = timeline;
}

void CMachineDrawable::TurnOnMachine()
{
    CMachineDlg dlg(mMachine);
    if (dlg.DoModal() == IDOK)
    {
        // A machine has been selected

    }
}
