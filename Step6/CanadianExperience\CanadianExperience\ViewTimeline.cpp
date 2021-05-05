/**
 * \file ViewTimeline.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Timeline.h"
#include "MainFrm.h"
#include "Picture.h"
#include "AnimChannel.h"

#include <sstream>

using namespace std;
using namespace Gdiplus;

/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
    mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
    assert(mPointer->GetLastStatus() == Ok);
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
    UpdateWindow();
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
    // Get the timeline
    CTimeline* timeline = GetPicture()->GetTimeline();

    // Set the scroll system correctly
    CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
    SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    //// TODO: Drawing code goes here
    //Pen pen(Color(0, 128, 0), 1);
    //graphics.DrawRectangle(&pen, 10, 10, 200, 60);

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 16);

    //SolidBrush brush(Color(0, 0, 0));
    //graphics.DrawString(L"Timeline!",  // String to draw
    //    -1,         // String length, -1 means it figures it out 
    //    &font,      // The font to use
    //    PointF(15, 15),   // Where to draw
    //    &brush);    // The brush to draw the text with

    //CString time = CTime::GetCurrentTime().Format("%H:%M:%S");
    //graphics.DrawString(time,  // String to draw
    //    -1,         // String length, -1 means it figures it out 
    //    &font,      // The font to use
    //    PointF(15, 40),   // Where to draw
    //    &brush);    // The brush to draw the text with

    CRect rect;
    GetClientRect(&rect);
    int hit = rect.Height();
    int wid = rect.Width();

    Pen tickPen(Color::Black, 1);
    FontFamily fontA(L"Arial");
    Gdiplus::Font fontB(&fontA, 25, FontStyleBold);
    SolidBrush tickBrush(Color(0, 0, 0));

    int tickNum = 0;

    for (int i = 0; i <= timeline->GetNumFrames(); i++)
    {
        tickNum = i;
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;

        int X = BorderLeft + TickSpacing * i;
        int Y1 = BorderTop;
        
        // Convert the tick number to seconds in a string
        std::wstringstream str;
        str << tickNum / timeline->GetFrameRate();
        std::wstring wstr = str.str();

        RectF size;
        PointF origin(0.0f, 0.0f);
        graphics.MeasureString(wstr.c_str(), wstr.size(),
            &font, origin, &size);

        if (onSecond)
        {
            int Y2 = BorderTop + TickLong;
            graphics.DrawLine(&tickPen, X, Y1, X, Y2);

            StringFormat format;
            format.SetAlignment(StringAlignmentCenter);
            Gdiplus::Font fontSec(&fontA, 10);
            graphics.DrawString(wstr.c_str(), -1, &fontSec, PointF(X, Y2), &format, &tickBrush);
        }
        else
        {
            int Y2 = BorderTop + TickShort;
            graphics.DrawLine(&tickPen, X, Y1, X, Y2);
        }
    }
    graphics.DrawImage(mPointer.get(), 5 + timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing, BorderTop);
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
     auto picture = GetPicture();
     for (auto actor : *picture)
     {
         actor->SetKeyframe();
     }
 }


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     auto picture = GetPicture();
     auto timeline = picture->GetTimeline();
     auto currFrame = timeline->GetCurrentFrame();
     
     for (auto actor : *picture)
     {
         timeline->DeleteKeyframe();
     }
     picture->SetAnimationTime(timeline->GetCurrentFrame());
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
     ON_WM_LBUTTONDOWN()
     ON_WM_MOUSEMOVE()
 END_MESSAGE_MAP()


/** Handle a left button mouse press event
* \param nFlags flags associated with the mouse press
* \param point The location of the mouse press
*/
 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     int x = point.x;

     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();
     int pointerX = (int)(timeline->GetCurrentTime() *
         timeline->GetFrameRate() * TickSpacing + BorderLeft);

     mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
         x <= pointerX + (int)mPointer->GetWidth() / 2;

     __super::OnLButtonDown(nFlags, point);
 }


/**
 * Compute the time based on the current mouse X location.
 * \param nFlags Flags associated with the mouse press
 * \param point The location of the mouse press
 */
 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     double x = point.x;

     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();

     // Get the picture
     shared_ptr<CPicture> picture = GetPicture();

     double currentTime = (x -BorderLeft) / (timeline->GetFrameRate() * double(TickSpacing));

     if (nFlags & MK_LBUTTON)
     {
         if (currentTime > timeline->GetDuration())
         {
             currentTime = timeline->GetDuration();
         }
         else if (currentTime < 0)
         {
             currentTime = 0;
         }
         picture->SetAnimationTime(currentTime);
     }

     __super::OnMouseMove(nFlags, point);
 }
