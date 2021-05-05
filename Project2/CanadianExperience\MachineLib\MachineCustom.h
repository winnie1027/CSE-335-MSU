/**
 * \file MachineCustom.h
 *
 * \author Winnie Yang
 *
 * Machine class that makes custom machines.
 */


#pragma once

#include "WavPlayer.h"
#include "Component.h"

#include <memory>
#include <vector>

using namespace Gdiplus;


/**
 *  Machine class that makes custom machines.
 */
class CMachineCustom
{
public:
    /// Constructor
    CMachineCustom(int machine);

    /// Destructor
    virtual ~CMachineCustom() {}

    /// Copy constructor/disabled
    CMachineCustom(const CMachineCustom&) = delete;

    /// Assignment operator/disabled
    void operator=(const CMachineCustom&) = delete;

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetLocation(int x, int y) { mPosition.X = x, mPosition.Y = y; }

    /**
    * Draw the machine
    * \param graphics GDI+ Graphics object
    */
    virtual void Draw(Gdiplus::Graphics* graphics);

    /**
    * Set the current machine animation frame
    * \param frame Frame number
    */
    virtual void SetMachineFrame(int frame);

    /**
     * Get the current machine number
     * \return Machine number integer
     */
    virtual int GetMachineNumber() { return mMachineNumber; }

    /**
    * Adds component to machine.
    * \param component Component
    */
    void AddComponent(std::shared_ptr<CComponent> component) { mComponents.push_back(component); }

    /**
    * Gets the audio player for machine/
    * \return Wavplayer
    */
    CWavPlayer* GetWavPlayer() { return &mWavPlayer; }

private:
    /// Frame rate
    double mFrameRate = 30;

    /// Machine number
    int mMachineNumber = 1;

    /// Position of the component
    Point mPosition = Point(0, 0);

    /// WavPlayer pointer
    CWavPlayer mWavPlayer;

    /// Component objects
    std::vector<std::shared_ptr<CComponent>> mComponents;
};

