/**
 * \file TimelineDlg.h
 *
 * \author Winnie Yang
 *
 * 
 */


#pragma once

class CTimeline;



/**
 * CTimelineDlg dialog
 */
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	/** standard constructor 
	* \param pParent */
	CTimelineDlg(CWnd* pParent = nullptr);   
	virtual ~CTimelineDlg();

	/// Setter for timeline
	void SetTimeline(CTimeline* timeline);

	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

protected:
	/** DDX/DDV support 
	* \param pDX */
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
private:
	/// Number of frames
	int mNumFrames;

	/// The timeline we are editing
	CTimeline* mTimeline = nullptr;

	/// Frame rate
	int mFrameRate;
};
