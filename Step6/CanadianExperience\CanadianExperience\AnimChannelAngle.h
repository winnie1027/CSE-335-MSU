/**
 * \file AnimChannelAngle.h
 *
 * \author Winnie Yang
 *
 * Animation channel for angles.
 */




#pragma once

#include "AnimChannel.h"

class CDrawable;


/**
 * Animation channel for angles.
 */
class CAnimChannelAngle : public CAnimChannel
{
public :
    // Constructor
    CAnimChannelAngle();

    /** Copy constructor disabled */
    CAnimChannelAngle(const CAnimChannelAngle&) = delete;
    /** Assignment operator disabled */
    void operator=(const CAnimChannelAngle&) = delete;

    virtual ~CAnimChannelAngle();

    /** Angle getter
    * \returns mAngle */
    double GetAngle() { return mAngle; }

    void SetKeyframe(double angle);

    /** Class that represents a keyframe angle */
    class KeyframeAngle : public Keyframe
    {
    public:
        /** Constructor
        * \param channel The channel we are for
        * \param angle The angle for the keyframe */
        KeyframeAngle(CAnimChannelAngle* channel, double angle) :
            Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /** Default constructor disabled */
        KeyframeAngle() = delete;
        /** Copy constructor disabled */
        KeyframeAngle(const KeyframeAngle&) = delete;
        /** Assignment operator disabled */
        void operator=(const KeyframeAngle&) = delete;

        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        /** Use this keyframe as keyfraem 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

        /** Use this keyframe as the angle */
        virtual void UseOnly() override { mChannel->mAngle = mAngle; }

        /** Keyframe angle getter
        * \returns mAngle */
        double GetAngle() { return mAngle; }

    private:
        /// Angle
        double mAngle;

        /// The channel this keyframe is associated with
        CAnimChannelAngle* mChannel;
    };

protected:
    virtual void Tween(double t) override;

private:
    /// Angle of channel
    double mAngle = 0;

    /// The first angle keyframe
    KeyframeAngle* mKeyframe1;

    /// The second angle keyframe
    KeyframeAngle* mKeyframe2;
};

