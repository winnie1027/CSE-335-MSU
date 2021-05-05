/**
 * \file AnimChannelPoint.h
 *
 * \author Winnie Yang
 *
 * Animation channel for points.
 */



#pragma once

#include "AnimChannel.h"

using namespace std;

/**
 * Animation channel for points.
 */
class CAnimChannelPoint : public CAnimChannel
{
public:
    // Constructor
    CAnimChannelPoint();

    /** Copy constructor disabled */
    CAnimChannelPoint(const CAnimChannelPoint&) = delete;
    /** Assignment operator disabled */
    void operator=(const CAnimChannelPoint&) = delete;

    virtual ~CAnimChannelPoint();

    /** Point getter
    * \returns mPoint */
    Gdiplus::Point GetPoint() { return mPoint; }

    void SetKeyframe(Gdiplus::Point point);

    /** Class that represents a keyframe point */
    class KeyframePoint : public Keyframe
    {
    public:
        /** Constructor
        * \param channel The channel we are for
        * \param point The point for the keyframe */
        KeyframePoint(CAnimChannelPoint* channel, Gdiplus::Point point) :
            Keyframe(channel), mChannel(channel), mPoint(point) {}

        /** Default constructor disabled */
        KeyframePoint() = delete;
        /** Copy constructor disabled */
        KeyframePoint(const KeyframePoint&) = delete;
        /** Assignment operator disabled */
        void operator=(const KeyframePoint&) = delete;

        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        /** Use this keyframe as keyframe 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

        /** Use this keyframe as the point */
        virtual void UseOnly() override { mChannel->mPoint = mPoint; }

        /** Keyframe point getter
        * \returns mPoint */
        Gdiplus::Point GetPoint() { return mPoint; }

    private:
        /// Keyframe point
        Gdiplus::Point mPoint;

        /// The channel this keyframe is associated with
        CAnimChannelPoint* mChannel;
    };

protected:
    virtual void Tween(double t) override;

private:
    /// Point of channel
    Gdiplus::Point mPoint;  

    /// The first point keyframe
    KeyframePoint* mKeyframe1;

    /// The second point keyframe
    KeyframePoint* mKeyframe2;
};

