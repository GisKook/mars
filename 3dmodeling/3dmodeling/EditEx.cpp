// EditEx.cpp : 实现文件
//

#include "stdafx.h"
#include "3dmodeling.h"
#include "EditEx.h"


// CEditEx

IMPLEMENT_DYNAMIC(CEditEx, CEdit)

CEditEx::CEditEx()
{

}

CEditEx::~CEditEx()
{
}

BOOL CEditEx::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message == WM_KEYDOWN)
	{
		BOOL b = GetKeyState(VK_CONTROL) & 0x80;
		if(b && (pMsg->wParam=='a'||pMsg->wParam=='A'))
		{
			SetSel(0,-1);
			return TRUE;
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
BEGIN_MESSAGE_MAP(CEditEx, CEdit)
END_MESSAGE_MAP()



// CEditEx 消息处理程序


