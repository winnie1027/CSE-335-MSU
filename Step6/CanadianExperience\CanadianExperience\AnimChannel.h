/**
 * \file AnimChannel.h
 *
 * \author Winnie Yang
 *
 * Base class for animation channels 
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels. 
 */



#pragma once

#include <string>
#include <memory>
#include <vector>

using namespace std;

class CTimeline;

/** Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels. */
class CAnimChannel
{
public:
    // Constructor
    CAnimChannel();

    /** Copy constructor disabled */
    CAnimChannel(const CAnimChannel&) = delete;
    /** Assignment operator disabled */
    void operator=(const CAnimChannel&) = delete;

    virtual ~CAnimChannel();
    
    /** Validity
    * \returns bool */
    bool IsValid();

    /** Frame setter
    * \param currFrame Current frame */
    void SetFrame(int currFrame);

    /** Name setter
    * \param name mName will be set to */
    void SetName(const std::wstring& name) { mName = name; }

    /** Name getter
    * \returns mName */
    std::wstring GetName() const { return mName; }

    /** Timeline getter
    * \returns mTimeline */
    CTimeline* GetTimeline() { return mTimeline; }

    /** Timeline setter
    * \param timeline */
    void SetTimeline(CTimeline* timeline) { mTimeline = timeline; }

    void RemoveFrame();

    /** Class that represents a keyframe */
    class Keyframe
    {
    public:
        virtual void UseAs1();
        virtual void UseAs2();
        virtual void UseOnly();

        /** Keyframe getter
        * \returns mFrame */
        int GetFrame() { return mFrame; }

        /** Keyframe setter
        * \param frame */
        void SetFrame(int frame) { mFrame = frame; }

    protected:
        /** Constructor
        * \param channel Channel we are associated with */
        Keyframe(CAnimChannel* channel) : mChannel(channel) {}
        /// Keyframe
        int mFrame;     

        /** Default constructor disabled */
        Keyframe() = delete;
        /** Copy constructor disabled */
        Keyframe(const Keyframe&) = delete;
        /** Assignment operator disabled */
        void operator=(const Keyframe&) = delete;

    private:
        /// The channel this keyframe is associated with
        CAnimChannel* mChannel;
    };

protected:
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    virtual void Tween(double t);

private:
    std::wstring mName;     ///< The channel name
    int mKeyframe1 = -1;    ///< The first keyframe
    int mKeyframe2 = -1;    ///< The second keyframe

    /// The timeline object
    CTimeline* mTimeline;

    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;
};

