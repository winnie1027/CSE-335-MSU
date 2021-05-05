/**
 * \file MachineDemoView.h
 *
 * \author Charles Owen
 *
 * A view window that displays a single machine object
 */

#pragma once

#include <memory>
#include <string>
#include "Machine.h"

/**
 * A view window that displays a single machine object
 */
class CMachineDemoView : public CWnd
{
	DECLARE_DYNAMIC(CMachineDemoView)

public:
	CMachineDemoView();
	virtual ~CMachineDemoView();

    void SetFrame(int frame);
    void SetMachineNumber(int machine);
    void SetScale(double scale);

    /**
     * Get the machine object
     * 
     * You are not allowed to do this in your adapter class!
     * \return CMachine object
     */
    std::shared_ptr<CMachine> GetMachine() { return mMachine; }

    /**
     * Set the save filename that will save the first image generated
     * @param filename Filename
    */
    void SetSaveFile(const std::wstring& filename) { mSaveFile = filename; }

    /**
     * Set a label to appear on the image
     * @param label Label string
    */
    void SetLabel(const std::wstring& label) { mLabel = label; }

    /**
     * If set true, the program will exit after drawing the first image
     * @param die True to exit after drawing first image
    */
    void SetDie(bool die) { mDie = die; }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
    double mScale = 1.0;                ///< Amount to scale the image

    int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
    void Draw(Gdiplus::Graphics* graphics);

    BOOL RegisterWindowClass();

    std::shared_ptr<CMachine> mMachine;       ///< Machine we are displaying

    std::wstring mSaveFile;             ///< Any file to save the image to
    std::wstring mLabel;                ///< The picture label
    bool mDie = false;                  ///< Die after save file option
};


