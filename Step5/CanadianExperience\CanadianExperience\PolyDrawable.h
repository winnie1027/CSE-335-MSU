/**
 * \file PolyDrawable.h
 *
 * \author Winnie Yang
 *
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 * 
 */


#pragma once

#include "Drawable.h"
#include <vector>


/**
 * A drawable based on polygon images.
 */
class CPolyDrawable : public CDrawable
{
public:
	virtual ~CPolyDrawable();

	CPolyDrawable(const std::wstring& name);

	/** Default constructor disabled */
	CPolyDrawable() = delete;
	/** Copy constructor disabled */
	CPolyDrawable(const CPolyDrawable&) = delete;
	/** Assignment operator disabled */
	void operator=(const CPolyDrawable&) = delete;

	/** Get the color
	 * \returns mColor*/
	Gdiplus::Color GetColor() const { return mColor; }

	/** Set the mColor
	* \param color The new color*/
	void SetColor(Gdiplus::Color color) { mColor = color; }

	/// Draw a polygon
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/// Hit test
	virtual bool HitTest(Gdiplus::Point pos) override;

	/// To add points to the polygon
	void AddPoint(Gdiplus::Point delta);

private:
	/// The polygon color
	Gdiplus::Color mColor = Gdiplus::Color::Black;

	/// The array of point objects
	std::vector<Gdiplus::Point> mPoints;
};

