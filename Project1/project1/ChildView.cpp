
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "ItemVisitor.h"
#include "CargoVisitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 50;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

// CChildView

/**
 * Constructor
 */
CChildView::CChildView()
{
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

/// \cond
/// This doxygen switch tells it to ignore this block of code
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_CHEAT_ROADCHEAT32778, &CChildView::OnCheatRoadCheat)
	ON_COMMAND(ID_CHEAT_RIVERCHEAT32779, &CChildView::OnCheatRiverCheat)
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_WM_ERASEBKGND()
        ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
        ON_UPDATE_COMMAND_UI(ID_CHEAT_ROADCHEAT32778,
                             &CChildView::OnUpdateCheatRoadcheat32778)
        ON_UPDATE_COMMAND_UI(ID_CHEAT_RIVERCHEAT32779,
                             &CChildView::OnUpdateCheatRivercheat32779)
        END_MESSAGE_MAP()
        /// \endcond



// CChildView message handlers

/**
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint() 
{

	CPaintDC paintDC(this);
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);
	CRect rect;
	GetClientRect(&rect);

	

	if (mFirstLoad) 
	{
          mFirstLoad = false;
          mGame = CGame();
          mGame.ChangeLevels(1);
    } 


	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;
	
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
    while (elapsed > MaxElapsed) 
	{
      mGame.Update(MaxElapsed);
      elapsed -= MaxElapsed;
	} 

	if (elapsed > 0) 
	{
      mGame.Update(elapsed);
    }

	//Performs hit test to see if car hit Hero
	/*mGame.HitTest();*/
	


}



/**
 * Called when user selects the Road Cheat menu option under Cheat
 */
void CChildView::OnCheatRoadCheat()
{
	// TODO: Add your command handler code here

	if (mGame.GetRoadCheat()) 
	{
        mGame.SetRoadCheat(false);
    } else 
	{
        mGame.SetRoadCheat(true);
    }

}

/**
 * Called when user selects the River Cheat menu option under Cheat
 */
void CChildView::OnCheatRiverCheat()
{
  if (mGame.GetRiverCheat()) 
  {
    mGame.SetRiverCheat(false);
  } else 
  {
    mGame.SetRiverCheat(true);
  }
}

/**
 * Called when user selects the Level 0 menu option under Levels
 */
void CChildView::OnLevelLevel0() 
{ 
	mGame.ChangeLevels(0); 
	mGame.ResetAttributes(true);
}

/**
 * Called when user selects the Level 1 menu option under Levels
 */
void CChildView::OnLevelLevel1() 
{
	mGame.ChangeLevels(1);
    mGame.ResetAttributes(true);
}

/**
 * Called when user selects the Level 2 menu option under Levels
 */
void CChildView::OnLevelLevel2() 
{ 
	mGame.ChangeLevels(2); 
	mGame.ResetAttributes(true);
}


/**
 * Called when user selects the Level 3 menu option under Levels
 */
void CChildView::OnLevelLevel3() 
{ 
	mGame.ChangeLevels(3); 
	mGame.ResetAttributes(true);
}


/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent) 
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}

/**
 * Handles key being pressed
 * \param nChar char being pressed
 * \param nRepCnt
 * \param nFlags
 */
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	mGame.OnKeyDown(nChar, nRepCnt, nFlags);

}

/**
 * Handles button being held down
 * \param nFlags char being pressed
 * \param point
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point); 
	mGame.OnButtonDown(nFlags, point);
}


/**
 * enable the checked option handler
 * \param pCmdUI user interface pointer
 */
void CChildView::OnUpdateCheatRoadcheat32778(CCmdUI* pCmdUI) 
{

  mGame.GetRoadCheat() ? pCmdUI->SetCheck(true) : pCmdUI->SetCheck(false);
}

/**
 * enable the checked option handler
 * \param pCmdUI user interface pointer
 */
void CChildView::OnUpdateCheatRivercheat32779(CCmdUI* pCmdUI) 
{
  mGame.GetRiverCheat() ? pCmdUI->SetCheck(true) : pCmdUI->SetCheck(false);

}
