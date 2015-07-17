// SWOTSystem.h : main header file for the SWOTSystem application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSWOTSystemApp:
// See SWOTSystem.cpp for the implementation of this class
//

class CSWOTSystemApp : public CWinApp
{
public:
	CSWOTSystemApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSWOTSystemApp theApp;