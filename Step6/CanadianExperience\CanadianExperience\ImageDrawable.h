/**
 * \file ImageDrawable.h
 *
 * \author Winnie Yang
 *
 * This class draws an image.
 */



#pragma once

#include "Drawable.h"
#include <memory>


/**
 * This class draws an image.
 */
class CImageDrawable : public CDrawable
{
public:
	/// Constructor
	CImageDrawable(const std::wstring& name, const std::wstring& filename);

	/// Draw an image
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/// Hit test
	virtual bool HitTest(Gdiplus::Point pos) override;

	/** Set the image drawable center
	* \param pos The new image drawable center*/
	void SetCenter(Gdiplus::Point pos) { mCenter = pos; }

	/** Get the image drawable center
	 * \returns The image drawable center*/
	Gdiplus::Point GetCenter() const { return mCenter; }

protected:
	/// The image for this drawable
	std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
	/// Image drawable center
	Gdiplus::Point mCenter = Gdiplus::Point(0, 0);
};

