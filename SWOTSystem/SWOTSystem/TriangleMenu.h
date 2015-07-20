#pragma once
#include "afxwin.h"

class CTriangleMenu :
	public CMenu
{
public:
	CTriangleMenu(void);
	~CTriangleMenu(void);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

};
