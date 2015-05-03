// colourchanging.h : main header file for the colourchanging application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CcolourchangingApp:
// See colourchanging.cpp for the implementation of this class
//

class CcolourchangingApp : public CWinApp
{
public:
	CcolourchangingApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CcolourchangingApp theApp;