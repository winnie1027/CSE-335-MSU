/**
 * \file MachineTwoFactory.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "MachineTwoFactory.h"
#include "Machine.h"
#include "Component.h"
#include "Instrument.h"
#include "Shape.h"
#include "CardReader.h"
#include "Cylinder.h"
#include "Chime.h"
#include "Cymbal.h"
#include "Drum.h"
#include "Tubing.h"

using namespace Gdiplus;
using namespace std;

CMachineTwoFactory::CMachineTwoFactory()
{
}

CMachineTwoFactory::~CMachineTwoFactory()
{
}

shared_ptr<CMachineCustom> CMachineTwoFactory::Create()
{
    // Locations of stuff
    const int BaseWidth = 650;
    const int BaseHeight = 10;

    // All of the centers (X)
    const int FrameworkCenter = 25;
    const int CardReaderCenter = -250;
    const int CylinderCenter = 63;
    const int ChimesCenter = 47;
    const int CymbalAndDrumCenter = 275;
    const int ClampingPostCenter = -150;

    const int CylinderBottom = -95;
    const int ChimeTop = -335;
    const int CylinderAndChimesSpacing = 55;
    const int NumChimes = 5;

    // The card actual dimensions are 847 by 379 pixels,
    // a size choosen to make the column spacing exactly
    // 10 pixels. We draw it much smaller than that on the screen

    /// Width to draw the card on the screen in pixels
    const int CardWidth = 132;

    /// Height to draw the card on the screen in pixels
    const int CardLength = 297;

    /// Amount of offset the center of the card so it will
    /// appear at the right place relative to the card reader.
    const int CardOffsetX = 126;

    /// Y dimension of the offset
    const int CardOffsetY = 65;

    // These values are all for the underlying image. They
    // can be used for find the punches.

    /// Width of a card column in pixels
    const int CardColumnWidth = 10;

    /// Height of a card row in pixels
    const int CardRowHeight = 29;

    /// X offset for the first column (left side)
    const int CardColumn0X = 24;

    /// Y offset to the first row (0's)
    /// There are actually two rows above this that can be used
    const int CardRow0Y = 78;

    /// Width of a punched hole
    const int CardPunchWidth = 8;

    /// Height of a punched hole
    const int CardPunchHit = 20;

    /// Any average luminance below this level is considered a punched hole
    const double CardPunchLuminance = 0.1;

    //
    // These values are for the outputs of the card reader,
    // where the tubing attaches.
    //

    /// Y offset to the first card reader output in pixels
    const int OutputOffsetY = -92;

    /// X offset to the first card reader output in pixels
    const int OutputOffsetX = -35;

    /// X spacing for the outputs
    const double OutputSpacingX = 10.7;

    /// The chime hammer mount image
    const std::wstring ChimeMountImage = L"images/hammer-mount.png";

    /// The chime hammer image
    const std::wstring ChimeHammerImage = L"images/hammer.png";

    /// The chime itself
    const std::wstring ChimeImage = L"images/chime.png";

    /// Width to draw the actual chime
    const int ChimeWidth = 15;

    /// Offset of the Chime relative to the origin
    /// of this component X value
    const double ChimeOffsetX = -18.0;

    /// Offset of the Chime Y value
    const double ChimeOffsetY = 5.0;

    /// The location in the hammer image for the pivot point X
    const double HammerPivotX = 33;

    /// The location in the hammer image for the pivot point X
    const double HammerPivotY = 10;

    /// Amount to rotate hammer away from chime in unit rotations
    const double HammerRotation = 0.08;

    // The machine itself. The value passed to the 
    // constructor is the machine number.
    auto machine = make_shared<CMachineCustom>(2);

    // The base, just a flat to sit things on
    auto base = make_shared<CShape>();
    base->Rectangle(-BaseWidth / 2, BaseHeight, BaseWidth, BaseHeight);
    base->SetColor(Color::DarkGray);
    machine->AddComponent(base);

    //
    // The framework that holds the cylinders and chimes
    //
    auto framework = make_shared<CShape>();
    framework->SetImage(L"images/framework.png");
    framework->Rectangle(-framework->GetImageWidth() / 2, 0);
    framework->SetPosition(FrameworkCenter, 0);
    machine->AddComponent(framework);

    /// Image for the back of the card reader
    const std::wstring CardReaderBackImage = L"images/card-reader-back.png";

    /// Image for the front of the card reader
    const std::wstring CardReaderFrontImage = L"images/card-reader-front.png";

    //
    // The card reader and card
    //
    auto cardreader = make_shared<CCardReader>();
    cardreader->SetCard(L"images/suzanna.png");
    cardreader->SetReaderBack(CardReaderBackImage);
    cardreader->SetReaderFront(CardReaderFrontImage);
    cardreader->RectangleCard(CardOffsetX, CardOffsetY, CardLength, CardWidth);
    cardreader->RectangleCardReaderBack(-cardreader->GetCardReaderBackWidth() / 2, 0);
    cardreader->RectangleCardReaderFront(-cardreader->GetCardReaderFrontWidth() / 2, 0);
    cardreader->SetRotation(-0.25);
    cardreader->SetPosition(CardReaderCenter, 0);
    machine->AddComponent(cardreader);

    //
    // Cylinders and chimes
    //
    int ChimeLength[] = { 220, 170, 125, 100, 75 };
    wchar_t* sounds[] = { L"audio/chimeC3.wav",
        L"audio/chimeD3.wav",
        L"audio/chimeE3.wav",
        L"audio/chimeG3.wav",
        L"audio/chimeA3.wav" };

    // Vector to collect the cylinders so we can 
    // run tubing to them later.
    std::vector<std::shared_ptr<CCylinder>> cylinders;

    //
    // The cylinders and chimes
    //
    int cylinderX = -CylinderAndChimesSpacing * NumChimes / 2 + CylinderCenter;
    int chimeX = -CylinderAndChimesSpacing * NumChimes / 2 + ChimesCenter;
    for (int i = 0; i < NumChimes; i++) {

        //
        // The chimemount, chime, and hammer
        //
        auto chime = make_shared<CChime>();
        chime->SetMachineNumber(2);
        chime->SetMount(ChimeMountImage);
        chime->SetChime(ChimeImage);
        chime->SetHammer(ChimeHammerImage);
        chime->RectangleMount(-chime->GetMountWidth() / 2 + ChimeOffsetX, ChimeOffsetY);
        chime->RectangleChime(-chime->GetChimeWidth() / 2 + ChimeOffsetX, ChimeOffsetY, ChimeWidth, ChimeLength[i]);
        chime->RectangleHammer(-chime->GetHammerWidth() / 2 + ChimeOffsetX, ChimeOffsetY);
        chime->SetChimeRotation(-0.5);
        chime->SetHammerRotation(HammerRotation);
        chime->SetPosition(chimeX + 20, ChimeTop + 70);
        machine->AddComponent(chime);

        //
        // The cylinder base
        //
        auto cylinder = make_shared<CCylinder>();
        cylinder->SetMount(L"images/cylinder-base.png");
        cylinder->SetRam(L"images/cylinder-ram.png");
        cylinder->SetCylinder(L"images/cylinder.png");
        cylinder->RectangleMount(-cylinder->GetMountWidth() / 2 + ChimeOffsetX, ChimeOffsetY);
        cylinder->RectangleRam(-cylinder->GetRamWidth() / 2 + ChimeOffsetX, ChimeOffsetY);
        cylinder->RectangleCylinder(-cylinder->GetCylinderWidth() / 2 + ChimeOffsetX, ChimeOffsetY);
        cylinder->SetPosition(cylinderX + 15, CylinderBottom - 5);
        machine->AddComponent(cylinder);
        cylinders.push_back(cylinder);

        // Connect the motion
        cylinder->SetMotionSink(chime);

        // Add sound to the chime
        auto channel = machine->GetWavPlayer()->CreateChannel(sounds[i]);
        chime->SetAudioChannel(channel);

        // Move to the next x locations
        cylinderX += CylinderAndChimesSpacing;
        chimeX += CylinderAndChimesSpacing;
    }

    //
    // The cymbal
    //
    auto cymbal = make_shared<CCymbal>();
    cymbal->SetMachineNumber(2);
    cymbal->SetCymbal(L"images/cymbal.png");
    cymbal->SetStand(L"images/cymbal-stand.png");
    cymbal->RectangleCymbal(-cymbal->GetCymbalWidth() / 2, 0);
    cymbal->RectangleCymbalStand(-cymbal->GetStandWidth() / 2, 0);
    cymbal->SetPosition(CymbalAndDrumCenter, 0);
    machine->AddComponent(cymbal);

    auto channel = machine->GetWavPlayer()->CreateChannel(L"audio/cymbal.wav");
    cymbal->SetAudioChannel(channel);

    // Cantilever to hold the cylinder
    auto cant = make_shared<CShape>();
    cant->SetImage(L"images/cantilever.png");
    cant->Rectangle(0, 0);   // 0,0 is lower right corner
    cant->SetPosition(framework->GetImageWidth() / 2 - 46, -framework->GetImageHeight() + 3);
    machine->AddComponent(cant);

    auto cymbalCylinder = make_shared<CCylinder>();
    cymbalCylinder->SetCylinder(L"images/cylinder.png");
    cymbalCylinder->SetMount(L"images/cylinder-base.png");
    cymbalCylinder->SetRam(L"images/cylinder-ram.png");
    cymbalCylinder->RectangleMount(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    cymbalCylinder->RectangleRam(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    cymbalCylinder->RectangleCylinder(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    cymbalCylinder->SetPosition(cant->GetX() + 100, cant->GetY() - 2);
    cymbalCylinder->SetBaseRotation(0.5);
    cymbalCylinder->SetCylinderRotation(0.5);
    cymbalCylinder->SetRamRotation(0.5);
    cymbalCylinder->SetMaxExtent(0.55);
    machine->AddComponent(cymbalCylinder);

    cymbalCylinder->SetMotionSink(cymbal);

    //
    // The drum
    //
    auto drum = make_shared<CDrum>();
    drum->SetDrum(L"images/drum.png");
    drum->RectangleDrum(-drum->GetDrumWidth() / 2, 0);
    drum->SetPosition(CymbalAndDrumCenter, 0);
    machine->AddComponent(drum);

    channel = machine->GetWavPlayer()->CreateChannel(L"audio/kick.wav");
    drum->SetAudioChannel(channel);

    // Block to hold the cylinder
    auto block = make_shared<CShape>();
    block->SetImage(L"images/angle-block.png");
    block->Rectangle(-block->GetImageWidth(), 0);   // 0,0 is lower right corner
    block->SetPosition(91, 0);
    machine->AddComponent(block);

    auto drumCylinder = make_shared<CCylinder>();
    drumCylinder->SetCylinder(L"images/cylinder.png");
    drumCylinder->SetMount(L"images/cylinder-base.png");
    drumCylinder->SetRam(L"images/cylinder-ram.png");
    drumCylinder->RectangleMount(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    drumCylinder->RectangleRam(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    drumCylinder->RectangleCylinder(-cymbalCylinder->GetCylinderWidth() / 2, 0);
    drumCylinder->SetPosition(90, -30);
    drumCylinder->SetCylinderRotation(0.25);
    drumCylinder->SetBaseRotation(0.25);
    drumCylinder->SetRamRotation(0.25);
    machine->AddComponent(drumCylinder);

    drumCylinder->SetMotionSink(drum);

    //
    // Clamping post for the tubing
    //
    auto post = make_shared<CShape>();
    post->SetImage(L"images/clamping-post.png");
    post->Rectangle(-post->GetImageWidth() / 2, 0);
    post->SetPosition(ClampingPostCenter, 0);
    machine->AddComponent(post);


    //
    // We do the tubing last so it is on top
    // 
    for (int i = 0; i < 5; i++)
    {
        auto tubing = make_shared<CTubing>();
        cardreader->GetSource(i)->SetSpeed(50);
        cardreader->GetSource(i)->SetSink(tubing->GetSink());
        tubing->SetSource(cardreader->GetSource(i));
        tubing->GetSource()->SetSink(cylinders[4 - i]->GetSink());
        machine->AddComponent(tubing);

        tubing->AddClamp(ClampingPostCenter, -10 - 10 * i, 0.75, 50);

    }

    auto tubing = make_shared<CTubing>();
    cardreader->GetSource(9)->SetSink(tubing->GetSink());
    cardreader->GetSource(9)->SetSpeed(25);
    cardreader->GetSource(9)->SetSpeed(50);
    tubing->SetSource(cardreader->GetSource(9));
    tubing->GetSource()->SetSink(cymbalCylinder->GetSink());
    machine->AddComponent(tubing);

    tubing->AddClamp(-162, -90, 0.5, 50);
    tubing->AddClamp(-162, -360, 0.5, 100);

    tubing = make_shared<CTubing>();
    cardreader->GetSource(8)->SetSpeed(10);
    cardreader->GetSource(8)->SetSink(tubing->GetSink());
    tubing->SetSource(cardreader->GetSource(8));
    tubing->GetSource()->SetSink(drumCylinder->GetSink());
    machine->AddComponent(tubing);

    tubing->AddClamp(ClampingPostCenter, -10 - 10 * 5, 0.75, 50);

    // Clamping post clamps for the tubing
    auto clamps = make_shared<CShape>();
    clamps->SetImage(L"images/clamping-post-clamps.png");
    clamps->Rectangle(-clamps->GetImageWidth() / 2, 0);
    clamps->SetPosition(ClampingPostCenter, 0);
    machine->AddComponent(clamps);

    return machine;
}