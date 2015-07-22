// ButtonTriangle.cpp : 实现文件
//

#include "stdafx.h"
#include "SWOTSystem.h"
#include "ButtonTriangle.h"
#include "SWOTSystemDoc.h"
#include "SWOTSystemView.h"


// CButtonTriangle
const CString CButtonTriangle::m_fontname = "Microsoft YaHei";
IMPLEMENT_DYNAMIC(CButtonTriangle, CButton)

CButtonTriangle::CButtonTriangle():m_status(CButtonTriangle::Normal)
{
	m_menu.CreatePopupMenu(); 
}

CButtonTriangle::~CButtonTriangle()
{
	m_menu.DestroyMenu();
}


BEGIN_MESSAGE_MAP(CButtonTriangle, CButton)
	ON_WM_DRAWITEM()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


int CButtonTriangle::MoveButton( int x, int y, int fontheight )
{ 
	m_fontsize = fontheight;
	CDC MemDC; //首先定义一个显示设备对象
	HDC hdc = ::GetDC(this->GetSafeHwnd());
	MemDC.Attach(hdc);
	CFont font;
	font.CreateFont(fontheight, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		m_fontname);
	MemDC.SelectObject(font);
	GetTextExtentPoint32(MemDC.GetSafeHdc(),m_strCaption,m_strCaption.GetLength(),&m_size);
	MemDC.Detach();
	m_size.cx += 45;
	m_size.cy += 6;

	m_triangle[0].x = m_size.cx - 20;
	m_triangle[0].y = m_size.cy/2-1;
	m_triangle[1].x = m_size.cx - 14;
	m_triangle[1].y = m_size.cy/2-1;
	m_triangle[2].x = m_size.cx - 17;
	m_triangle[2].y = m_size.cy/2 + 4;

	this->MoveWindow(x, y, m_size.cx, m_size.cy);

	return x + m_size.cx - 2;
}

void CButtonTriangle::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CButtonTriangle::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CButton::OnNcPaint()
	return;
	CDC* pDC = GetWindowDC();

	//work out the coordinates of the window rectangle,
	CRect rect;
	GetWindowRect( &rect);
	rect.OffsetRect( -rect.left, -rect.top);

	//Draw a single line around the outside
	CBrush brush( RGB( 212, 208, 200));
	pDC->FrameRect( &rect, &brush);
	ReleaseDC( pDC);
}

void CButtonTriangle::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	fprintf(stdout, " %s %s %d\n", m_strCaption,__FUNCTION__, m_status);
	// TODO:  添加您的代码以绘制指定项
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);		//Get device context object
	CRect rt;
	rt = lpDrawItemStruct->rcItem;		//Get button rect
	rt.left += 14;

	dc.SetBkMode(TRANSPARENT);
	CRect rect = lpDrawItemStruct->rcItem;
	rect.left -= 1;
	rect.right += 1;
	rect.top -= 1;
	rect.bottom += 1;
	DrawRect(&dc, rect, RGB(255,255,255));
	//dc.FillSolidRect(rt, RGB(0, 0, 255));		//Fill button with blue color
	UINT state = lpDrawItemStruct->itemState;	//Get state of the button
	CFont font, *oldfont;
	font.CreateFont(m_fontsize, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		m_fontname);
	oldfont = dc.SelectObject(&font);
	if(m_status == Normal){		
		dc.SetTextColor(RGB(0,0,0));		// Set the color of the caption to be yellow
		dc.DrawText(m_strCaption,rt,DT_LEFT|DT_VCENTER|DT_SINGLELINE);		// Draw out the caption				
	}else if(m_status == SelectArrow || m_status == SelectArrowOff){
		dc.SetTextColor(RGB(0,0,0));		// Set the color of the caption to be yellow
		CBrush backbrush, *oldbackbrush;
		backbrush.CreateSolidBrush(RGB(168,168,168));
		oldbackbrush = dc.SelectObject(&backbrush);
		CPen pen,*oldpen;
		pen.CreatePen(PS_NULL,0, RGB(0,0,0));
		oldpen = dc.SelectObject(&pen);
		dc.Rectangle(&lpDrawItemStruct->rcItem);
		dc.DrawText(m_strCaption,rt,DT_LEFT|DT_VCENTER|DT_SINGLELINE);		// Draw out the caption
		dc.SelectObject(oldbackbrush);
		dc.SelectObject(oldpen);
		pen.DeleteObject();
		backbrush.DeleteObject();
	}else{
		dc.SetTextColor(RGB(219,127,46));		// Set the color of the caption to be yellow
		dc.DrawText(m_strCaption,rt,DT_LEFT|DT_VCENTER|DT_SINGLELINE);		// Draw out the caption
	}


	CBrush newbrush;
	CBrush * oldbrush;
	newbrush.CreateSolidBrush(RGB(0,0,0));
	oldbrush = dc.SelectObject(&newbrush);
	dc.Polygon(m_triangle,3);
	font.DeleteObject();
	newbrush.DeleteObject();
	dc.SelectObject(oldbrush);
	dc.SelectObject(oldfont);
	dc.Detach(); 
}

void CButtonTriangle::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRgn rgn;
	POINT polygon[3];
	polygon[0].x = m_triangle[0].x - 12;
	polygon[0].y = m_triangle[0].y - 12;
	polygon[1].x = m_triangle[1].x + 12;
	polygon[1].y = m_triangle[1].y - 12;
	polygon[2].x = m_triangle[2].x;
	polygon[2].y = m_triangle[2].y + 12;
	rgn.CreatePolygonRgn(polygon, 3, ALTERNATE);
	bool in = rgn.PtInRegion(point);
	if(in && m_status != SelectArrow){
		m_status = SelectArrow;
		CRect rc;
		GetWindowRect(rc);

		int x = rc.left;
		int y = rc.bottom;
		Invalidate();
		((CSWOTSystemView*)m_parent)->ResetMenu(m_index);
		m_menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,x,y,m_parent);
	}else if(in  && m_status == SelectArrow){
		m_status = SelectArrowOff;
	}else if(m_status != SelectText){
		m_status = SelectText;
	}
	rgn.DeleteObject();
	
	Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}

void CButtonTriangle::SetStatus( ButtonStatus status )
{
	m_status = status;
	Invalidate();
}

void CButtonTriangle::DrawRect( CDC *pDC, RECT &rect, COLORREF c )
{
	CBrush backbrush, *oldbackbrush;
	backbrush.CreateSolidBrush(c);
	oldbackbrush = pDC->SelectObject(&backbrush);
	CPen pen,*oldpen;
	pen.CreatePen(PS_NULL,0, RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(&rect);
	pDC->SelectObject(oldbackbrush);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	backbrush.DeleteObject();
}

BOOL CButtonTriangle::Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int index )
{
	m_parent = pParentWnd;
	m_strCaption = lpszCaption;
	m_index = index;
	dwStyle |= BS_OWNERDRAW; // Enforce
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID );
}

BOOL CButtonTriangle::AddMenuItem( UINT nMenuId, const CString strMenu, UINT nMenuFlags )
{
	return m_menu.AppendMenu(nMenuFlags | MF_STRING, nMenuId, (LPCTSTR)strMenu); 
}
