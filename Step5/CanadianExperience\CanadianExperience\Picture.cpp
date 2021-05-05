/**
 * \file Picture.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "Picture.h"
#include "PictureObserver.h"

using namespace Gdiplus;


/**
 * Destructor
 */
CPicture::~CPicture()
{
}

/**
 * Add an observer to this picture.
 * \param observer The observer to add
 */
void CPicture::AddObserver(CPictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * \param observer The observer to remove
 */
void CPicture::RemoveObserver(CPictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void CPicture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/**
 * Add actor to this picture
 * \param actor New actor to add
 */
void CPicture::AddActor(std::shared_ptr<CActor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}


/**
 * Draw this picture on a device context
 * \param graphics The device context to draw on
 */
void CPicture::Draw(Gdiplus::Graphics* graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }
}
