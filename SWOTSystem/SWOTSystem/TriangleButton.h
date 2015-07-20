#pragma once
#include "afxwin.h"

class CTriangleButton :
	public CButton
{
public:
	CTriangleButton(void);
	~CTriangleButton(void);

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	void SetCaption(CString strCaption);

	int MoveButton(int x, int y, int cy);

private:
	CString m_strCaption;
};
