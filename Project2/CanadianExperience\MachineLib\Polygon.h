/**
 * \file Polygon.h
 *
 * \author Charles Owen
 *
 * Generic polygon class that is used to make shapes we
 * will use in our project.
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

/**
 * Generic polygon class that is used to make shapes we 
 * will use in our project.
 */
class CPolygon
{
public:
    CPolygon();
    virtual ~CPolygon();


    void AddPoint(int x, int y);

    /// Add a point to the polygon. Convenience version that accepts doubles.
    /// \param x X value for point
    /// \param y Y value for point
    void AddPoint(double x, double y) { AddPoint((int)x, (int)y); }

    void Rectangle(int x, int y, int wid=0, int hit=0);
    void Rectangle(double x, double y, double wid=0, double hit=0);
    void CenteredSquare(int size);

    void SetColor(Gdiplus::Color color);

    void SetImage(std::wstring filename);

    int GetImageWidth();

    int GetImageHeight();

    double AverageLuminance(int x, int y, int wid, int hit);

    void DrawPolygon(Gdiplus::Graphics* graphics, double x, double y);

    /// Set the rotation of the polygon
    /// \param rotation Rotation in turns, where 0-1 is one revolution.
    virtual void SetRotation(double rotation) { mRotation = rotation; }

    /// Get the rotation of the polygon
    /// \return rotation Rotation in turns, where 0-1 is one revolution.
    double GetRotation() { return mRotation; }

private:
    void ConfigureTextureBrush();

    /// The points that make up the polygon
    std::vector<Gdiplus::PointF> mPoints;

    /// A brush to draw the polygon with
    std::shared_ptr<Gdiplus::Brush> mBrush;

    /// If we are using a textured brush, this will be it
    std::shared_ptr<Gdiplus::TextureBrush> mTextureBrush;

    /// If we are using a texture image, this is it
    std::shared_ptr<Gdiplus::Bitmap> mTexture;

    /// Any amount to rotate the polygon in turns
    /// 0 to 1 is one complete rotation
    double mRotation = 0;

    /// Set to true once the polygon has been drawn one time
    bool mHasDrawn = false;
};

