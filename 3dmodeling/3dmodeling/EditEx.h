#pragma once


// CEditEx

class CEditEx : public CEdit
{
	DECLARE_DYNAMIC(CEditEx)

public:
	CEditEx();
	virtual ~CEditEx();
public:
	BOOL CEditEx::PreTranslateMessage( MSG* pMsg );

protected:
	DECLARE_MESSAGE_MAP()
};


