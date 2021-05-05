/**
 * \file SpartyFactory.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "SpartyFactory.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"


using namespace Gdiplus;


/** This is a concrete factory method that creates the Sparty actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CSpartyFactory::Create()
{
    shared_ptr<CActor> actor = make_shared<CActor>(L"Sparty");

    auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/sparty_torso.png");
    shirt->SetCenter(Point(55, 138));
    shirt->SetPosition(Point(0, -114));
    actor->SetRoot(shirt);

    auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/sparty_lleg.png");
    lleg->SetCenter(Point(11, 9));
    lleg->SetPosition(Point(27, 40));
    shirt->AddChild(lleg);

    auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/sparty_rleg.png");
    rleg->SetCenter(Point(39, 9));
    rleg->SetPosition(Point(-27, 40));
    shirt->AddChild(rleg);

    auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/sparty_lhead.png");
    headb->SetCenter(Point(44, 31));
    headb->SetPosition(Point(0, -130));
    shirt->AddChild(headb);

    auto headt = make_shared<CHeadTop>(L"Head Top", L"images/sparty_head.png");
    headt->SetCenter(Point(40, 145));
    headt->SetPosition(Point(0, -31));
    headb->AddChild(headt);

    auto larm = make_shared<CImageDrawable>(L"Left Arm", L"images/sparty_rarm.png");
    larm->SetCenter(Point(90, 0));
    larm->SetPosition(Point(-45, -120));
    shirt->AddChild(larm);

    auto rarm = make_shared<CImageDrawable>(L"Right Arm", L"images/sparty_larm.png");
    rarm->SetCenter(Point(0, 0));
    rarm->SetPosition(Point(55, -120));
    shirt->AddChild(rarm);

    auto flag = make_shared<CImageDrawable>(L"Flag", L"images/msu_flag.png");
    flag->SetCenter(Point(100, 150));
    flag->SetPosition(Point(-90, 100));
    larm->AddChild(flag);

    auto leye = make_shared<CImageDrawable>(L"Left eye", L"images/sparty_leye.png");
    leye->SetPosition(Point(-20, -50));
    headt->AddChild(leye);

    auto reye = make_shared<CImageDrawable>(L"Right eye", L"images/sparty_reye.png");
    reye->SetPosition(Point(12, -49));
    headt->AddChild(reye);

    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(shirt);
    actor->AddDrawable(flag);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);
    actor->AddDrawable(leye);
    actor->AddDrawable(reye);

    return actor;
}
