/**
 * \file Picture.h
 *
 * \author Winnie Yang
 *
 * The picture we are drawing.
 * 
 */


#pragma once

#include "Actor.h"
#include "Timeline.h"

#include <vector>


class CPictureObserver;

/**
* The picture we are drawing.
*
* There will be one picture object that contains all of
* our actors, which then contains the drawables.
*/
class CPicture
{
public:
    CPicture() {}
    virtual ~CPicture();

    /// Copy Constructor (Disabled)
    CPicture(const CPicture&) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const CPicture&) = delete;

    /** The picture size
    * \returns Size */
    Gdiplus::Size GetSize() { return mSize; }

    /** The picture size
    * \param size The new picture size */
    void SetSize(Gdiplus::Size size) { mSize = size; }

    void AddObserver(CPictureObserver* observer);
    void RemoveObserver(CPictureObserver* observer);
    void UpdateObservers();
    void Draw(Gdiplus::Graphics* graphics);
    void SetAnimationTime(double time);
    void AddActor(std::shared_ptr<CActor> actor);
 
    /** Get a pointer to the Timeline object
    * \returns Pointer to the Timeline object
    */
    CTimeline* GetTimeline() { return &mTimeline; }

    /** Iterator that iterates over some collection */
    class ActorIter
    {
    public:
        /** Constructor
         * \param actor The collection we are iterating over 
         * \param pos The actor position */
        ActorIter(CPicture* actor, int pos) : mCollection(actor), mPos(pos) {}

        /** Test for end of the iterator
        * \param other
         * \returns True if we this position equals not equal to the other position */
        bool operator!=(const ActorIter& other) const
        {
            return mPos != other.mPos;
        }

        /** Get value at current position
         * \returns Value at mPos in the collection */
        std::shared_ptr<CActor> operator *() const { return mCollection->mActors[mPos]; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }


    private:
        CPicture* mCollection;   ///< Collection we are iterating over
        int mPos;       ///< Position in the collection
    };

    /** Iterator begins
    * \returns Beginning spot */
    ActorIter begin() { return ActorIter(this, 0); }
    /** Iterator ends
    * \returns End spot */
    ActorIter end() { return ActorIter(this, mActors.size()); }

private:
    /// The picture size
    Gdiplus::Size mSize = Gdiplus::Size(800, 600);

    /// The observers of this picture
    std::vector<CPictureObserver*> mObservers;

    /// Vector to store actors
    std::vector<std::shared_ptr<CActor> > mActors;

    /// The animation timeline
    CTimeline mTimeline;
};

