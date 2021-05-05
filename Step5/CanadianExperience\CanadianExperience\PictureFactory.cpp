/**
 * \file PictureFactory.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "SpartyFactory.h"


using namespace std;
using namespace Gdiplus;


 /** Factory method to create a new picture.
 * \returns The created picture
 */
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI =
        make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // Create and add Sparty
    CSpartyFactory factory1;
    auto sparty = factory1.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(400, 500));

    // This is where Sparty will spart out
    sparty->SetPosition(Point(800, 450));

    picture->AddActor(harold);
    picture->AddActor(sparty);

    return picture;
}