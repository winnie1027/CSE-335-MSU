/**
 * \file PolyDrawable.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "PolyDrawable.h"
#include <vector>


using namespace std;
using namespace Gdiplus;


 /**
  * Constructor
  * \param name The drawable name
  */
CPolyDrawable::CPolyDrawable(const std::wstring& name) : CDrawable(name)
{
}


/**
 * Destructor
 */
CPolyDrawable::~CPolyDrawable()
{
}



/**
 * Draws the polygon
 * \param graphics 
 */
void CPolyDrawable::Draw(Gdiplus::Graphics* graphics)
{
    SolidBrush brush(mColor);

    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}


/**
 * Hit test
 * \param pos 
 * \returns 
 */
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    GraphicsPath path;
    path.AddPolygon(&points[0], (int)points.size());
    return path.IsVisible(pos) ? true : false;
}


/**
 * Add a point to the polygon
 * \param point 
 */
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}