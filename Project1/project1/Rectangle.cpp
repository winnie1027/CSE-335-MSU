/**
 * \file Rectangle.cpp
 *
 * \author Caroline Gormely
 */



#include "pch.h"
#include "Rectangle.h"


/**
 * Constructor for rectangle object.
 * 
 * \param game 
 * \param imagePair 
 */
CRectangle::CRectangle(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair) {}


/**
 * Draw rectangles that indicate road lines.
 * \param graphics to draw with
 */
void CRectangle::Draw(Gdiplus::Graphics* graphics) 
{
  Pen pen(Color(mColor[0], mColor[1], mColor[2]), mHeight*GetTileWidth()); // get colors for rectangle
  int startX = static_cast<int>(GetPosition().X());
  int startY = static_cast<int>(GetPosition().Y());

  for (int j = 0; j < mRepeatY; ++j) 
  { // repeat
    int modifyX = startX;
    for (int i = 0; i < mRepeatX; ++i) 
    {
      graphics->DrawLine(&pen, modifyX, startY, modifyX + mWidth * GetTileWidth(), startY);
      modifyX += GetTileWidth();
    }
    startY += GetTileWidth();
  }
}



/**
 * Load from Xml child node.
 * \param node to read from
 */
void CRectangle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) 
{
  CItem::XmlLoad(node);
  double check = GetPosition().X();
  double check2 = GetPosition().Y();
  mHeight = node->GetAttributeDoubleValue(L"height", 0);
  mWidth = node->GetAttributeDoubleValue(L"width", 0);
  double check3 = mHeight;
  double check4 = mWidth;
  wstring wsColor = (node->GetAttributeValue(L"color", L"0,0,0"));
  std::string tempColor(wsColor.begin(), wsColor.end());

  // Creates the vector of doubles we pass into the Color( ) in Draw function
  string substr = "";
  for (char symbol : tempColor) 
  {
    if (symbol != ',') 
    {
      substr += symbol;
    }
    if (symbol == ',') 
    {
      mColor.push_back(stoi(substr));
      substr = "";
    }
  }
  mColor.push_back(stoi(substr));

  //double pxlX = node->GetAttributeDoubleValue(L"x", 0);  //* mWidth;
  //double pxlY = node->GetAttributeDoubleValue(L"y", 0);  //* mHeight;
  mRepeatX = node->GetAttributeIntValue(L"repeat-x", 1);
  mRepeatY = node->GetAttributeIntValue(L"repeat-y", 1);
  /*SetLocation(pxlX, pxlY);*/
}
