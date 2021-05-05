/**
 * \file CardReader.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "CardReader.h"

using namespace std;


// These values are all for the underlying image. They
// can be used for find the punches.

/// Width to draw the card on the screen in pixels
const int CardWidth = 132;

/// Height to draw the card on the screen in pixels
const int CardLength = 297;

/// Width of a card column in pixels
const int CardColumnWidth = 10;

/// Height of a card row in pixels
const int CardRowHeight = 29;

/// X offset for the first column (left side)
const int CardColumn0X = 24;

/// Y offset to the first row (0's)
/// There are actually two rows above this that can be used
const int CardRow0Y = 78;

/// Width of a punched hole
const int CardPunchWidth = 8;

/// Height of a punched hole
const int CardPunchHit = 20;

/// Any average luminance below this level is considered a punched hole
const double CardPunchLuminance = 0.1;

/// Y offset to the first card reader output in pixels
const int OutputOffsetY = -92;

/// X offset to the first card reader output in pixels
const int OutputOffsetX = -35;

/// X spacing for the outputs
const double OutputSpacingX = 10.7;

CCardReader::CCardReader()
{
    for (int i = 0; i < 10; i++)
    {
        auto source = make_shared<CAirSource>();
        mSources.push_back(source);
    }
}

void CCardReader::Draw(Graphics* graphics, Point position)
{
    auto cardMath = double(CardLength) / GetCardWidth();

    mCardReaderBack.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
    mCard.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y + (mColumn - 1) * cardMath * CardColumnWidth);
    mCardReaderFront.DrawPolygon(graphics, position.X + mPosition.X, position.Y + mPosition.Y);
}

void CCardReader::SetTime(double seconds)
{
    double beat = seconds * mBeatsPerMinute / 60.0;
    double remainder = fmod(beat, 1);
    mColumn = (int)beat;
    if (mColumn <= 80)
    {
        for (int row = 0; row < mNumSources; row++)
        {
            bool punched = IsPunched(mColumn, row);
            if (punched && remainder < 0.5)
            {
                mSources[row]->SetAirPressure(1);
            }
            else
            {
                mSources[row]->SetAirPressure(0);
            }
        }
    }
}


bool CCardReader::IsPunched(int column, int row)
{
    auto luminance = mCard.AverageLuminance(CardColumn0X + (column - 1) * CardColumnWidth,
        CardRow0Y + CardRowHeight * row, CardPunchWidth, CardPunchHit);
    return luminance < CardPunchLuminance;
}

void CCardReader::SetPosition(int x, int y)
{
    mPosition.X = x;
    mPosition.Y = y;

    CComponent::SetPosition(x, y);

    for (int row = 0; row < mNumSources; row++)
    {
        mSources[row]->SetEndpoint(Gdiplus::Point(
            (int)(x + OutputOffsetX + OutputSpacingX * row),
            y + OutputOffsetY
        ));
    }
}
