/**
 * \file ViewTimeline.h
 *
 * \author Winnie Yang
 *
 * View window for the animation timeline
 */

#pragma once

#include "PictureObserver.h"


class CMainFrame;

/** View window for the animation timeline */
class CViewTimeline : public CScrollView, public CPictureObserver
{
	DECLARE_DYNCREATE(CViewTimeline)

public:
	virtual void UpdateObserver() override;

    static const int Height = 90;      ///< Height to make this window

	/**
	* Set the mainFrame pointer
	* \param mainFrame Pointer to the CMainFrame window
	*/
	void SetMainFrame(CMainFrame* mainFrame) { mMainFrame = mainFrame; }

protected:
	CViewTimeline();           // protected constructor used by dynamic creation
	virtual ~CViewTimeline();


protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditSetkeyframe();
    afx_msg void OnEditDeletekeyframe();

private:
	/// The main frame window that uses this view
	CMainFrame* mMainFrame = nullptr;
};


