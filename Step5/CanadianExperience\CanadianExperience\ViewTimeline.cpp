/**
 * \file ViewTimeline.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"

#include "MainFrm.h"

using namespace std;
using namespace Gdiplus;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{

}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}

/**
 * Force an update of this window when the picture changes.
 */
void CViewTimeline::UpdateObserver()
{
    Invalidate();
}


/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    // TODO: Drawing code goes here
    Pen pen(Color(0, 128, 0), 1);
    graphics.DrawRectangle(&pen, 10, 10, 200, 60);

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    SolidBrush brush(Color(0, 0, 0));
    graphics.DrawString(L"Timeline!",  // String to draw
        -1,         // String length, -1 means it figures it out 
        &font,      // The font to use
        PointF(15, 15),   // Where to draw
        &brush);    // The brush to draw the text with

    CString time = CTime::GetCurrentTime().Format("%H:%M:%S");
    graphics.DrawString(time,  // String to draw
        -1,         // String length, -1 means it figures it out 
        &font,      // The font to use
        PointF(15, 40),   // Where to draw
        &brush);    // The brush to draw the text with
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle the Edit>Set Keyframe menu option */
 void CViewTimeline::OnEditSetkeyframe()
 {
     // TODO: Add your command handler code here
 }


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     // TODO: Add your command handler code here
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
 END_MESSAGE_MAP()