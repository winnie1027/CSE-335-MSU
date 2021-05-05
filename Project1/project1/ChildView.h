
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"

// CChildView window

/**
 * ChildView class
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCheatRoadCheat();
	afx_msg void OnCheatRiverCheat();
	afx_msg void OnLevelLevel0();
	afx_msg void OnLevelLevel1();
	afx_msg void OnLevelLevel2();
	afx_msg void OnLevelLevel3();
private:
	/// True until the first time we draw
	bool mFirstDraw = true;

	/// True if first time loading a level
	bool mFirstLoad = true;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates

	/// The game we are in
	CGame mGame;
public:
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	

afx_msg void OnUpdateCheatRoadcheat32778(CCmdUI* pCmdUI);
        afx_msg void OnUpdateCheatRivercheat32779(CCmdUI* pCmdUI);
};

