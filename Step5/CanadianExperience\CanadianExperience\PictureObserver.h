/**
 * \file PictureObserver.h
 *
 * \author Winnie Yang
 *
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 * 
 */


#pragma once

#include <memory>

class CPicture;

/**
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class CPictureObserver
{
protected:
	// Constructor
	CPictureObserver() {}

	/// Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver&) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPictureObserver&) = delete;

public:
	// Virtual Destructor
	virtual ~CPictureObserver();

	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;

	/** Picture setter */
	void SetPicture(std::shared_ptr<CPicture> picture);

	/** Getter for picture
	* \returns mPicture */
	std::shared_ptr<CPicture> GetPicture() { return mPicture; }

	/// Used for testing
	bool mUpdated = false;

private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;

};

