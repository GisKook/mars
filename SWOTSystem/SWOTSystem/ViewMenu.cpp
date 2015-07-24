#include "StdAfx.h"
#include "ViewMenu.h"
using namespace std;

CViewMenu::CViewMenu(void):m_dc(NULL)
{
}

CViewMenu::~CViewMenu(void)
{
}

void CViewMenu::AddMenuItem( CString str )
{
	m_menuitem.push_back(str); 
}

void CViewMenu::DrawRect( CDC* pDC, RECT &rect, COLORREF c )
{
	CBrush backbrush, *oldbackbrush;
	backbrush.CreateSolidBrush(c);
	oldbackbrush = pDC->SelectObject(&backbrush);
	CPen pen,*oldpen;
	pen.CreatePen(PS_NULL,0, c);
	oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(&rect);
	pDC->SelectObject(oldbackbrush);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	backbrush.DeleteObject();
}

void CViewMenu::Draw()
{
	DrawRect(m_dc,m_rectmenu, RGB(255,255,255));
	int itemcount = m_menuitem.size();
	RECT rc = m_rectmenu;
	rc.bottom = rc.top + (m_rectmenu.bottom - m_rectmenu.top)/itemcount;
	DrawRect(m_dc,rc, RGB(219,127,46));
	 
	rc = GetRect(m_rectmenu, itemcount, 0);
	rc.left += 10;
	DrawFont(m_menuitem[0], rc, rc.bottom - rc.top, "Microsoft YaHei", RGB(0,0,0), FW_BOLD);

	for(int i=1; i < itemcount; i++){
		rc = GetRect(m_rectmenu, itemcount, i);
		rc.left += 10;
		DrawFont(m_menuitem[i], rc, rc.bottom - rc.top, "Microsoft YaHei", RGB(0,0,0), FW_NORMAL);
	}
}

RECT CViewMenu::GetRect( RECT & rc, int count, int index )
{
	RECT result = rc;
	int height = (rc.bottom - rc.top)/count;
	result.top = rc.top +  height * index;
	result.bottom = result.top + height;

	return result;
}

void CViewMenu::DrawFont( CString str, RECT rc, int fontsize, CString fontname, COLORREF c, int fontstyle /*= FW_NORMAL*/ )
{
	int bkmode = m_dc->SetBkMode(TRANSPARENT);
	CFont font, *oldfont;
	font.CreateFont(fontsize, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		fontstyle, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		fontname);
	oldfont = m_dc->SelectObject(&font);
	m_dc->SetTextColor(c);
	m_dc->DrawText(str,&rc, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	font.DeleteObject();
	m_dc->SelectObject(oldfont);
	m_dc->SetBkMode(bkmode);
}

void CViewMenu::Clear()
{
	m_menuitem.clear();
}
