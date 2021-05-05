/**
 * \file HeadTop.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "HeadTop.h"

#include <iostream>

using namespace Gdiplus;
using namespace std;


/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/** Constructor
 * \param name The drawable name
 * \param filename The filename for the image */
CHeadTop::CHeadTop(const std::wstring& name, const std::wstring& filename) : CImageDrawable(name, filename)
{
    mImage = std::unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}


 /** Transform a point from a location on the bitmap to
 *  a location on the screen.
 * \param  p Point to transform
 * \returns Transformed point
 */
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}


/**
 * Draws the head of the character.
 * \param graphics What's to be drawn
 */
void CHeadTop::Draw(Gdiplus::Graphics* graphics)
{
    CImageDrawable::Draw(graphics);

    // Harold
    Pen brow(Color::Black, 2);

    float wid1 = 15.0f;
    float hit1 = 20.0f;

    float wid = 15.0f;
    float hit = 20.0f;

    // Only draw eyes and eyebrows on Harold's head top
    if (mName == L"Harold Head Top")
    {
        Gdiplus::SolidBrush blackBrush(Color::Black);
        Point leftBrow = TransformPoint(Point(70, 80));
        auto state = graphics->Save();
        graphics->TranslateTransform(leftBrow.X, leftBrow.Y);
        graphics->RotateTransform((float)(-mPlacedR * RtoD));
        graphics->DrawLine(&brow, -wid1 / 2, -hit1 / 2, -wid1 / 2 + 20, -hit1 / 2 - 5);
        graphics->Restore(state);

        Point rightBrow = TransformPoint(Point(35, 75));
        state = graphics->Save();
        graphics->TranslateTransform(rightBrow.X, rightBrow.Y);
        graphics->RotateTransform((float)(-mPlacedR * RtoD));
        graphics->DrawLine(&brow, -wid1 / 2, -hit1 / 2, -wid1 / 2 + 20, -hit1 / 2 + 5);
        graphics->Restore(state);

        Point leftEye = TransformPoint(Point(38, 85));
        state = graphics->Save();
        graphics->TranslateTransform(leftEye.X, leftEye.Y);
        graphics->RotateTransform((float)(-mPlacedR * RtoD));
        graphics->FillEllipse(&blackBrush, -wid / 2, -hit / 2, wid, hit);
        graphics->Restore(state);

        state = graphics->Save();
        Point rightEye = TransformPoint(Point(70, 85));
        graphics->TranslateTransform(rightEye.X, rightEye.Y);
        graphics->RotateTransform((float)(-mPlacedR * RtoD));
        graphics->FillEllipse(&blackBrush, -wid / 2, -hit / 2, wid, hit);
        graphics->Restore(state);
    }
}