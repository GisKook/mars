// 2dcolor.h : main header file for the 2dcolor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy2dcolorApp:
// See 2dcolor.cpp for the implementation of this class
//

class CMy2dcolorApp : public CWinApp
{
public:
	CMy2dcolorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2dcolorApp theApp;