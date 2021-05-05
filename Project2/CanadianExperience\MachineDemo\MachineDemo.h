/**
 * \file MachineDemo.h
 * Header file for the MachineDemo application class
 * \cond
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class CMachineDemoDlg;

/**
 * MachineDemo application class
 */
class CMachineDemoApp : public CWinApp
{
public:
	CMachineDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

private:
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

	void ProcessCommandLine(CMachineDemoDlg* dlg);

};

extern CMachineDemoApp theApp;

/** \endcond */