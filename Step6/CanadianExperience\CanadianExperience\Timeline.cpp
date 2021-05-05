/**
 * \file Timeline.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Timeline.h"


 /**
  * Constructor
  */
CTimeline::CTimeline()
{
}



/**
 * Add channel to timeline
 * \param channel 
 */
void CTimeline::AddChannel(CAnimChannel* channel)
{
	mChannels.push_back(channel);
	channel->SetTimeline(this);
}


/**
 * Delete the current keyframe.
 */
void CTimeline::DeleteKeyframe()
{
    for (auto channel: mChannels)
    {
        channel->RemoveFrame();
    }
}

/** 
* Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
* 
*/
void CTimeline::SetCurrentTime(double currentTime)
{
    mCurrentTime = currentTime;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}