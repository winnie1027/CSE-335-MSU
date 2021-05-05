/**
 * \file Polygon.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include <cassert>
#include "Polygon.h"

using namespace Gdiplus;
using namespace std;

/// Degrees in a circle
const double Circle = 360;

/**
 * Constructor
 */
CPolygon::CPolygon()
{
    // Create an initial brush in black
    mBrush = make_shared<Gdiplus::SolidBrush>(Color::Black);
}

/**
 * Destructor
 */
CPolygon::~CPolygon()
{
}


/**
 * Add a point to the polygon
 * @param x  X value for point
 * @param y  Y value for point
*/
void CPolygon::AddPoint(int x, int y) 
{ 
    // Points can only be added before drawing. Once the polygon
    // is drawn one time, it can no longer be changed. If this 
    // assertion fails, you attempted to add points after
    // the polygon has drawn
    assert(!mHasDrawn);
    mPoints.push_back(Gdiplus::PointF((float)x, (float)y)); 
}


/**
 * Create a rectangle
 * \param x Lower-left side X
 * \param y  Lower-left side Y
 * \param wid Width of the rectangle. If not supplied, use an image width
 * \param hit Height of the rectangle. If not supplied, use an image height
 */
void CPolygon::Rectangle(int x, int y, int wid, int hit)
{
    if (wid == 0)
    {
        // If this assertion fails, you attempted to use the 
        // image width as the rectangle width before an image has
        // been set for the component
        assert(mTexture != nullptr);
        wid = GetImageWidth();
    }

    if (hit == 0)
    {
        // If this assertion fails, you attempted to use the 
        // image height as the rectangle height before an image has
        // been set for the component
        assert(mTexture != nullptr);
        hit = GetImageHeight();
    }

    AddPoint(x, y);
    AddPoint(x, y-hit);
    AddPoint(x+wid, y-hit);
    AddPoint(x+wid, y);
}

/**
 * Create a rectangle
 * \param x Lower-left side X
 * \param y  Lower-left side Y
 * \param wid Width of the rectangle. If not supplied, use an image width
 * \param hit Height of the rectangle. If not supplied, use an image height
 */
void CPolygon::Rectangle(double x, double y, double wid, double hit)
{
    Rectangle((int)(x + 0.5), (int)(y + 0.5), (int)(wid + 0.5), (int)(hit + 0.5));
}


/**
 * Create a centered square at location 0,0
 * \param size Width and height of the square
 */
void CPolygon::CenteredSquare(int size)
{
    Rectangle(-size / 2, size / 2, size, size);
}


/**
 * Set the color of the polygon. If we set a color, images are not used.
 * \param color A Gdiplus Color object.
 */
void CPolygon::SetColor(Gdiplus::Color color)
{
    mBrush = make_shared<Gdiplus::SolidBrush>(color);
    mTextureBrush = nullptr;
}

/**
 * Set an image we will use as a texture for the polygon
 * \param filename Image filename
 */
void CPolygon::SetImage(std::wstring filename)
{
    mTexture = shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mTexture->GetLastStatus() != Ok)
    {
        AfxMessageBox((wstring(L"Failed to open ") + filename).c_str());
    }
    mTextureBrush = make_shared<Gdiplus::TextureBrush>(mTexture.get());
    mTextureBrush->SetWrapMode(Gdiplus::WrapMode::WrapModeTileFlipXY);
    mBrush = mTextureBrush;
}


/**
 * Get the width of any set image for this polygon. This may not be
 * the width we actually draw, but is the size of the polygon itself.
 * @return Width in pixels
*/
int CPolygon::GetImageWidth()
{
    assert(mTexture != nullptr);
    return mTexture->GetWidth();
}


/**
 * Get the height of any set image for this polygon. This may not be
 * the height we actually draw, but is the size of the polygon itself.
 * @return Height in pixels
*/
int CPolygon::GetImageHeight()
{
    assert(mTexture != nullptr);
    return mTexture->GetHeight();
}


/**
 * Get the average luminance of a block of pixels in any supplied image.
 * @param x Top left X in pixels
 * @param y Top left Y in pixels
 * @param wid Width of the block to average
 * @param hit Height of the block to average
 * @return Luminance in the range 0-1, where 0 is black.
*/
double CPolygon::AverageLuminance(int x, int y, int wid, int hit)
{
    assert(mTexture != nullptr);

    double sum = 0;
    int cnt = 0;
    
    for (int i = x; i < x + wid; i++) 
    {
        if (i < 0 || i >= GetImageWidth()) 
        {
            continue;
        }

        for (int j = y; j < y + hit; j++)
        {
            if (j < 0 || j >= GetImageHeight())
            {
                continue;
            }

            Gdiplus::Color color;
            mTexture->GetPixel(i, j, &color);

            sum += (double)color.GetR() + (double)color.GetB() + (double)color.GetG();
            cnt += 3;
        }
    }

    if (cnt == 0)
    {
        return 0;
    }

    return (sum / cnt) / 255.0;
}


/**
 * Draw the polygon
 * \param graphics Gdiplus graphics object
 * \param x X location to draw in pixels
 * \param y Y location to draw in pixels
 */
void CPolygon::DrawPolygon(Gdiplus::Graphics *graphics, double x, double y)
{
    // If this assertion fails, you have not added any points to the polygon.
    // You must call functions such as AddPoint, Rectangle, CenteredSquare
    // to create something to draw. This assertion fails if you have not
    // done so.
    assert(!mPoints.empty());

    auto saveSM = graphics->GetSmoothingMode();
    graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)x, (REAL)y);
    graphics->RotateTransform((REAL)(mRotation * Circle));

    if (mTextureBrush != nullptr)
    {
        ConfigureTextureBrush();
    }

    graphics->FillPolygon(mBrush.get(), &mPoints[0], mPoints.size());

    graphics->Restore(save);

    graphics->SetSmoothingMode(saveSM);

    mHasDrawn = true;
}

/**
 * Configure a brush to use for the texture map. 
 *
 * We only do this if we are using a texture map. It makes the 
 * bounds of the texture map to the extents of the polygon.
 */
void CPolygon::ConfigureTextureBrush()
{
    //
    // Find minimum and maximum x and y values
    //
    PointF min = mPoints[0];
    PointF max = mPoints[0];
    for (PointF p : mPoints)
    {
        if (p.X < min.X)
        {
            min.X = p.X;
        }

        if (p.X > max.X)
        {
            max.X = p.X;
        }

        if (p.Y < min.Y)
        {
            min.Y = p.Y;
        }

        if (p.Y > max.Y)
        {
            max.Y = p.Y;
        }
    }

    mTextureBrush->ResetTransform();
    mTextureBrush->TranslateTransform(min.X, min.Y);
    mTextureBrush->ScaleTransform((max.X - min.X) / mTexture->GetWidth(),
        (max.Y - min.Y) / mTexture->GetHeight());
}