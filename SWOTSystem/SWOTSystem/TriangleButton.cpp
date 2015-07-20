#include "StdAfx.h"
#include "TriangleButton.h"

CTriangleButton::CTriangleButton(void)
{
}

CTriangleButton::~CTriangleButton(void)
{
}

void CTriangleButton::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);		//Get device context object
	CRect rt;
	rt = lpDrawItemStruct->rcItem;		//Get button rect

	dc.FillSolidRect(rt, RGB(0, 0, 255));		//Fill button with blue color

	UINT state = lpDrawItemStruct->itemState;	//Get state of the button
	if ( (state & ODS_SELECTED) )		// If it is pressed
	{
		dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face
	}
	else
	{
		dc.DrawEdge(rt,EDGE_RAISED,BF_RECT);	// Draw a raised face
	}
	dc.SetTextColor(RGB(255,255,120));		// Set the color of the caption to be yellow
	CString strTemp;
	GetWindowText(strTemp);		// Get the caption which have been set
	dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE);		// Draw out the caption
	if ( (state & ODS_FOCUS ) )       // If the button is focused
	{
		// Draw a focus rect which indicates the user 
		// that the button is focused
		int iChange = 3;
		rt.top += iChange;
		rt.left += iChange;
		rt.right -= iChange;
		rt.bottom -= iChange;
		dc.DrawFocusRect(rt);
	}
	dc.Detach();
}

void CTriangleButton::SetCaption( CString strCaption )
{ 
	m_strCaption = strCaption;
}

int CTriangleButton::MoveButton( int x, int y, int cy )
{
	int btnlen = strlen(m_strCaption) * 8 + 12;
    this->MoveWindow(x,y,btnlen, cy);

	return x + btnlen;
}
