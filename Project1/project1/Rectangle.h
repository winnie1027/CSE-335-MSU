/**
 * \file Rectangle.h
 *
 * \author Sirena Ly
 *
 * Defines the rectangle objects in the game.
 */


#pragma once
#include "Item.h"
#include "Game.h"

/// Class for rectangle
class CRectangle : public CItem 
{
 public:
  /// Default Constructor
  CRectangle() = delete;

  /// Copy Constructor
  CRectangle(const CRectangle&) = delete;

  CRectangle(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair);
  void Draw(Gdiplus::Graphics* graphics);
  void CRectangle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

  /** Accept a visitor
   * \param visitor The visitor we accept */
  virtual void Accept(CItemVisitor* visitor) override 
  {
    visitor->VisitRectangle(this);
  }



 private:
  /// Number of times an item image will repeat in the x direction
  int mRepeatX = 1;

  /// Number of times an item image will repeat in the y direction
  int mRepeatY = 1;

  /// Vector of the 3 colors used for the pen (rectangles)
  vector<int> mColor;

  /// Width of the line drawn for the rectangles
  double mWidth = 0;

  /// Height of the line drawn for the rectangle
  double mHeight = 0;

};
