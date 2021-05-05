/**
 * \file CardReader.h
 *
 * \author Winnie Yang
 *
 * The card reader.
 */



#pragma once

#include "Component.h"
#include "AirSource.h"

#include <memory>

using namespace Gdiplus;



/**
 * The card reader.
 */
class CCardReader : public CComponent
{
public:
    /// Constructor
    CCardReader();

    /// Destructor
    virtual ~CCardReader() {}

    /// Copy constructor/disabled
    CCardReader(const CCardReader&) = delete;

    /// Assignment operator/disabled
    void operator=(const CCardReader&) = delete;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    * \param position Position of the graphics object
    */
    virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position) override;

    /**
    * Time setter
    * \param seconds Time in seconds
    */
    virtual void SetTime(double seconds) override;

    /**
     * Determine if a hole is punched in the card.
     * \param column Column on the card, from 0 (left of first column) to 80 (last column)
     * \param row Row on the card, -2 to 9.
     * \return True if hole is punched at column, row
    */
    bool IsPunched(int column, int row);

    /**
    * Set the image of card
    * \param filename Fime name of image
    */
    void SetCard(const std::wstring& filename) { mCard.SetImage(filename); }

    /**
    * Set the image of card reader back
    * \param filename Fime name of image
    */
    void SetReaderBack(const std::wstring& filename) { mCardReaderBack.SetImage(filename); }

    /**
    * Set the image of card reader front
    * \param filename Fime name of image
    */
    void SetReaderFront(const std::wstring& filename) { mCardReaderFront.SetImage(filename); }

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetPosition(int x, int y) override;

    /**
    * Roates the image
    * \param rotate Rotation degrees
    */
    void SetRotation(double rotate) { mCard.SetRotation(rotate); }

    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCard(int x, int y, int wid = 0, int hit = 0) { mCard.Rectangle(x, y, wid, hit); }

    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCardReaderBack(int x, int y, int wid = 0, int hit = 0) { mCardReaderBack.Rectangle(x, y, wid, hit); }


    /**
     * Create a rectangle
     * \param x Left side X
     * \param y Bottom left Y
     * \param wid Width of the rectangle. If not supplied, use an image width
     * \param hit Height of the rectangle. If not supplied, use an image height
     */
    void RectangleCardReaderFront(int x, int y, int wid = 0, int hit = 0) { mCardReaderFront.Rectangle(x, y, wid, hit); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetCardWidth() { return mCard.GetImageWidth(); }

    /**
     * Get the width of any set image for this polygon. This may not be
     * the width we actually draw, but is the size of the polygon itself.
     * \return Width in pixels
    */
    int GetCardReaderFrontWidth() { return mCardReaderFront.GetImageWidth(); }

    /**
    * Get the width of any set image for this polygon. This may not be
    * the width we actually draw, but is the size of the polygon itself.
    * \return Width in pixels
    */
    int GetCardReaderBackWidth() { return mCardReaderBack.GetImageWidth(); }

    /**
     * Get an air source.
     * \param source Source index 0-9
     * \return Pointer to CAirSource object.
    */
    std::shared_ptr<CAirSource> GetSource(int source) { return mSources[source]; }

private:
    
    /// Position of the card related object
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// Card object
    CPolygon mCard;

    /// The back part of card reader
    CPolygon mCardReaderBack;

    /// The front part of card reader
    CPolygon mCardReaderFront;

    /// Time in seconds
    double mTime;

    /// Vector of air sources
    std::vector<std::shared_ptr<CAirSource>> mSources;

    /// NJumber of air sources
    int mNumSources = 10;

    /// The initial column on the card
    int mColumn = 1;

    /// Beats per minute used for punching card
    int mBeatsPerMinute = 180;
};

