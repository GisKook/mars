// wcom2tcp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cwcom2tcpApp:
// �йش����ʵ�֣������ wcom2tcp.cpp
//

class Cwcom2tcpApp : public CWinApp
{
public:
	Cwcom2tcpApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hOneInstanceMutex;
};

extern Cwcom2tcpApp theApp;