/**
 * \file ChildView.cpp
 *
 * \author Winnie Yang
 */

#include "pch.h"
#include "framework.h"
#include "Aqualand.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishDory.h"
#include "Magikarp.h"
#include "BashfulGreen.h"
#include "DoubleBufferDC.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;


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


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_COMMAND(ID_ADDFISH_DORYFISH, &CChildView::OnAddfishDoryfish)
	ON_COMMAND(ID_ADDFISH_MAGIKARP, &CChildView::OnAddfishMagikarp)

	ON_COMMAND(ID_ADDFISH_BASHFULFISH, &CChildView::OnAddfishBashfulfish)
END_MESSAGE_MAP()



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
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

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
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting

	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);
}

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;


/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		// We have selected an item
		// Move it to the end of the list of items
		mAquarium.Add(mGrabbedItem);
		mAquarium.Remove(mGrabbedItem);
	}
}

/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
			// check collisions from collision
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
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
 * Add Fish/Beta menu option handler
 */
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}


/**
 * Add Fish/Dory menu option handler
 */
void CChildView::OnAddfishDoryfish()
{
	auto fish = make_shared<CFishDory>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}


/**
 * Add Magikarp menu option handler
 */
void CChildView::OnAddfishMagikarp()
{
	auto fish = make_shared<CMagikarp>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}


/**
 * Add Bashful-green fish menu option handler
 */
void CChildView::OnAddfishBashfulfish()
{
	auto fish = make_shared<CBashfulGreen>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}