/**
 * \file MachineTemp.h
 *
 * \author Winnie Yang
 *
 * Machine class derived from machine.
 */


#pragma once

#include "Machine.h"
#include "MachineCustom.h"
#include "MachineOneFactory.h"
#include "MachineTwoFactory.h"

using namespace Gdiplus;


/**
 * Machine class derived from machine.
 */
class CMachineTemp : public CMachine
{
public:
	/// Constructor
	CMachineTemp();

	/// Destructor
	virtual ~CMachineTemp() {}

	/// Copy constructor/disabled
	CMachineTemp(const CMachineTemp&) = delete;

	/// Assignment operator/disabled
	void operator=(const CMachineTemp&) = delete;

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetLocation(int x, int y) override { mMachineCustom->SetLocation(x, y); }

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    */
    virtual void DrawMachine(Gdiplus::Graphics* graphics) override { mMachineCustom->Draw(graphics); }

    /**
    * Set the current machine animation frame
    * \param frame Frame number
    */
    virtual void SetMachineFrame(int frame) override { mMachineCustom->SetMachineFrame(frame); }

    /**
    * Set the machine number
    * \param machine An integer number. Each number makes a different machine
    */
    virtual void SetMachineNumber(int machine) override;

    /**
     * Get the current machine number
     * \return Machine number integer
     */
    virtual int GetMachineNumber() override { return mMachineCustom->GetMachineNumber(); }

private:

    /// Position of the component
    Point mLocation = Point(0, 0);

    /// Shared pointer to machine custom
    std::shared_ptr<CMachineCustom> mMachineCustom = nullptr;
};

