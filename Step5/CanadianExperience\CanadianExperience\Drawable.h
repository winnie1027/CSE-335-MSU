/**
 * \file Drawable.h
 *
 * \author Winnie Yang
 *
 * 
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */


#pragma once


#include <memory>
#include <string>
#include <vector>


class CActor;


/**
 * Abstract base class for drawable elements of our picture
 */
class CDrawable
{
public:
    virtual ~CDrawable();

    /** Default constructor disabled */
    CDrawable() = delete;
    /** Copy constructor disabled */
    CDrawable(const CDrawable&) = delete;
    /** Assignment operator disabled */
    void operator=(const CDrawable&) = delete;

    /** Set the drawable actor */
    void SetActor(CActor* actor);

    /** To draw the drawable
    * \param graphics The graohics we'll be drawing */
    virtual void Draw(Gdiplus::Graphics* graphics) = 0;

    /** Place of drawable */
    void Place(Gdiplus::Point offset, double rotate);

    /** To add a child to drawable */
    void AddChild(std::shared_ptr<CDrawable> child);
    
    /** Hit test for drawable
    * \param pos Theposition of drawable 
    * \returns bool */
    virtual bool HitTest(Gdiplus::Point pos) = 0;

    /** Movability of drawable
    * \returns bool */
    virtual bool IsMovable() { return false; }

    /** To move the drawable */
    void Move(Gdiplus::Point delta);

    /** Set the drawable position
     * \param pos The new drawable position*/
    void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

    /** Get the drawable position
     * \returns The drawable position*/
    Gdiplus::Point GetPosition() const { return mPosition; }

    /** Set the rotation angle in radians
    * \param r The new rotation angle in radians*/
    void SetRotation(double r) { mRotation = r; }

    /** Get the rotation angle in radians
    * \returns The rotation angle in radians*/
    double GetRotation() const { return mRotation; }

    /** Get the drawable name
    * \returns The drawable name */
    std::wstring GetName() const { return mName; }

    /** Get the drawable parent
    * \returns The pointer to parent */
    CDrawable* GetParent() { return mParent; }

    /** To set parent to drawable
    * \param parent The parent of drawable */
    void SetParent(CDrawable* parent) { mParent = parent; }

protected:
    /// Drawable's name, constructor
    CDrawable(const std::wstring& name);

    /// Drawable's rotation point
    Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);

    /// The actual postion in the drawing
    Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);

    /// The actual rotation in the drawing
    double mPlacedR = 0;

private:
    /// The drawable name
    std::wstring mName;

    /// The position of this drawable relative to its parent
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    CActor* mActor = nullptr;

    /// Pointer to drawable itself
    CDrawable* mParent = nullptr;

    /// A collection of drawable's children
    std::vector<std::shared_ptr<CDrawable>> mChildren;
};
