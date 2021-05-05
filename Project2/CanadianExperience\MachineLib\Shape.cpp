/**
 * \file Shape.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
}

void CShape::Draw(Graphics* graphics, Point position)
{
    mPolygon.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
}

