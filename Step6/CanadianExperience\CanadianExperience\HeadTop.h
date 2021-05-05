/**
 * \file HeadTop.h
 *
 * \author Winnie Yang
 *
 * Finish drawing the head.
 */



#pragma once

#include "ImageDrawable.h"
#include "AnimChannelPoint.h"


/**
 * This class finishes drawing the head.
 */
class CHeadTop : public CImageDrawable
{
public:
	CHeadTop(const std::wstring& name, const std::wstring& filename);
	/** Transform a point from a location on the bitmap to
	*  a location on the screen.
	* \param  p Point to transform
	* \returns Transformed point
	*/
	Gdiplus::Point TransformPoint(Gdiplus::Point p);

	/// Draw a head
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/** If head is movable
	* \returns bool */
	virtual bool IsMovable() override { return true; }

	virtual void SetTimeline(CTimeline* timeline) override;
	
	virtual void SetKeyframe() override;

	virtual void GetKeyframe() override;

private:
	/// Name of body part
	std::wstring mName = CImageDrawable::GetName();

	/// Animate channel object
	CAnimChannelPoint mChannel;
};

