/**
 * \file MachineDrawable.h
 *
 * \author Winnie Yang
 *
 * Draws machine in Canadian Experience
 */


#pragma once

#include "Drawable.h"
#include "Machine.h"
#include "Timeline.h"


/**
 *  Draws machine in Canadian Experience
 */
class CMachineDrawable : public CDrawable
{
public:
    /**
    * Constructor
    * \param name 
    */
    CMachineDrawable(const std::wstring& name);

    /** Default constructor disabled */
    CMachineDrawable() = delete;
    /** Copy constructor disabled */
    CMachineDrawable(const CMachineDrawable&) = delete;
    /** Assignment operator disabled */
    void operator=(const CMachineDrawable&) = delete;

    /**
    * Draws the machines
    * \Param graphics Graphics 
    */
    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /**
    * Gets the machine number.
    */
    int GetMachineNumber() { mMachine->GetMachineNumber(); }

    /**
    * Sets the machine number.
    * \param machine Machine number
    */
    void SetMachineNumber(int machine) { mMachine->SetMachineNumber(machine); }

    /**
    * Sets the timeline.
    * \param timeline Timeline
    */
    virtual void SetTimeline(CTimeline* timeline) override;

    /**
    * Turns on the machine.
    */
    void TurnOnMachine();

private:
    /// Machine
    std::shared_ptr<CMachine> mMachine;

    /// State frame
    int mStartFrame = 0;

    /// Timeline
    CTimeline* mTimeline = nullptr;
};

