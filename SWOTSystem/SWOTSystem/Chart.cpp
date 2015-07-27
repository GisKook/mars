#include "StdAfx.h"
#include "Chart.h"

CChart::CChart(void):m_dc(NULL)
{
}

CChart::~CChart(void)
{
}

void CChart::DrawBackground()
{ 
	if(m_rectbox.bottom == m_rectbox.top || m_rectbox.right == m_rectbox.left){
		return;
	}
	DrawBox();
	RECT rc = m_rectbox;
	int subboxheight = (m_rectbox.top-m_rectbox.bottom)/4;

	rc.bottom = m_rectbox.top - subboxheight;
	DrawFont("Strength", rc, subboxheight/3,"Microsoft YaHei", RGB(211,211,211), FW_BOLD);

	rc.top = rc.bottom;
	rc.bottom = rc.top - subboxheight;
	DrawFont("Opportunity", rc, subboxheight/3,"Microsoft YaHei", RGB(211,211,211), FW_BOLD);

	rc.top = rc.bottom;
	rc.bottom = rc.top - subboxheight;
	DrawFont("Weakness", rc, subboxheight/3,"Microsoft YaHei", RGB(211,211,211), FW_BOLD);
	
	rc.top = rc.bottom;
	rc.bottom = rc.top - subboxheight;
	DrawFont("Threat", rc, subboxheight/3,"Microsoft YaHei", RGB(211,211,211), FW_BOLD);

	rc = m_recttitle;
	rc.left -= 5;
	rc.right += 6;
	DrawRect(m_dc, rc, RGB(219,127,46));
	DrawArraw();
	DrawTile(m_title);
}

void CChart::DrawRect(CDC *pDC, RECT &rect, COLORREF c)
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

void CChart::DrawPolygon( CDC * pdc, POINT *pt, int count, COLORREF c ) {
	CBrush backbrush, *oldbackbrush;
	backbrush.CreateSolidBrush(c);
	oldbackbrush = pdc->SelectObject(&backbrush);
	pdc->Polygon(pt,count);
	pdc->SelectObject(oldbackbrush);
	backbrush.DeleteObject();
}

void CChart::DrawArraw()
{ 
	DrawPolygon(m_dc, m_leftarrow, 3, RGB(0,0,0));
	DrawPolygon(m_dc, m_rightarrow, 3, RGB(0,0,0));
}

void CChart::DrawBox()
{ 
	CDC * pDC = m_dc;
	RECT rect = m_rectbox;
	CPen pen,pen2;
	CPen * oldpen;
	RECT rectex;
	rectex.left = 0;
	rectex.top = 0;
	rectex.right = 2;
	rectex.bottom = 2;
	pDC->DPtoLP(&rectex);
	pen.CreatePen(PS_SOLID, rectex.right - rectex.left, RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	CPoint pts[5];
	pts[0].x = rect.left;
	pts[0].y = rect.bottom;
	pts[1].x = rect.right;
	pts[1].y = rect.bottom;
	pts[2].x = rect.right;
	pts[2].y = rect.top;
	pts[3].x = rect.left;
	pts[3].y = rect.top;
	pts[4].x = pts[0].x;
	pts[4].y = pts[0].y;

	pDC->Polyline(pts, 5);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();

	rectex.left = 0;
	rectex.right = 1;
	rectex.top = 1;
	rectex.bottom = 0;
	pDC->DPtoLP(&rectex);
	pen2.CreatePen(PS_SOLID, rectex.right-rectex.left, RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen2);

	pts[0].x = rect.left;
	pts[0].y = rect.bottom + (rect.top-rect.bottom)/4;
	pts[1].x = rect.right;
	pts[1].y = rect.bottom + (rect.top-rect.bottom)/4;
	pDC->MoveTo(pts[0]);
	pDC->LineTo(pts[1]);

	pts[0].x = rect.left;
	pts[0].y = rect.bottom + 2*(rect.top-rect.bottom)/4;
	pts[1].x = rect.right;
	pts[1].y = rect.bottom + 2*(rect.top-rect.bottom)/4;
	pDC->MoveTo(pts[0]);
	pDC->LineTo(pts[1]);

	pts[0].x = rect.left;
	pts[0].y = rect.bottom + 3*(rect.top-rect.bottom)/4;
	pts[1].x = rect.right;
	pts[1].y = rect.bottom + 3*(rect.top-rect.bottom)/4;
	pDC->MoveTo(pts[0]);
	pDC->LineTo(pts[1]);

	pDC->SelectObject(oldpen);
	pen2.DeleteObject();
}

void CChart::DrawFont( CString str, RECT rc, int fontsize, CString fontname, COLORREF c, int fontstyle) { 
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
	m_dc->DrawText(str,&rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	font.DeleteObject();
	m_dc->SelectObject(oldfont);
	m_dc->SetBkMode(bkmode);
}

void CChart::DrawTile( CString str )
{ 
	int fontsize = (m_recttitle.top - m_recttitle.bottom);
	DrawFont(str, m_recttitle, fontsize, "Microsoft YaHei", RGB(0,0,0), FW_BOLD);
}

void CChart::SetTitle( CString title )
{
	m_title = title;
}

void CChart::DrawHistogram( HistogramParam * p )
{ 
	if(m_rectbox.bottom == m_rectbox.top || m_rectbox.right == m_rectbox.left){
		return;
	}
	if(p == NULL){
		return ;
	}
	RECT rc;
	RECT rect;
	int fontsize;
	for (int i = 0; i < p->count; i++) {
		rc = GetHistoGram(p->count, p->height[i], i);
		DrawRect(m_dc, rc, p->color[i]);
		if(!p->str[i].IsEmpty()){
			rect = rc;
			rect.top = rect.bottom + (rect.right - rect.left)/2;
			fontsize = (rect.right - rect.left)/2;
			DrawFont(p->str[i], rect,fontsize,"Microsoft YaHei", RGB(0,0,0));
		}
	}
}

RECT CChart::GetHistoGram( int count, int height, int index) { 
	RECT result;
	int width = (m_rectbox.right - m_rectbox.left)/count;
	result.left = m_rectbox.left + index*width;
	result.right = result.left + width;
	result.bottom = m_rectbox.bottom;
	result.top = result.bottom + height;

	return result;
}

int CChart::Hittest( POINT p )
{
	CRgn leftarrow, rightarrow;
	leftarrow.CreatePolygonRgn(m_leftarrow, 3, ALTERNATE);
	rightarrow.CreatePolygonRgn(m_rightarrow, 3, ALTERNATE);
	RECT rect = m_rectbox; 
	rect.top = rect.bottom + (rect.top - rect.bottom)/2;
	if(p.x > rect.left && p.x < rect.right && p.y > rect.bottom && p.y < rect.top){
		return PROMOTION;
	}else if(p.x > m_recttitlemid.left && p.x < m_recttitlemid.right && p.y > m_recttitlemid.bottom && p.y < m_recttitlemid.top){
		return TITLEMID;
	}else if(leftarrow.PtInRegion(p)){
		return LEFTARROW;
	}else if(rightarrow.PtInRegion(p)){
		return RIGHTARROW;
	}

	return HTSNULL;
}

void CChart::SetTitleRect( RECT rc )
{
	m_recttitle = rc; 
	const int gap1 = 10;
	int arrawheight = (m_recttitle.top - m_recttitle.bottom)/2;
	m_leftarrow[0].x = m_recttitle.left + 5;
	m_leftarrow[0].y = m_recttitle.bottom + arrawheight;
	m_leftarrow[1].x = m_leftarrow[0].x + arrawheight;
	m_leftarrow[1].y = m_recttitle.top - gap1;
	m_leftarrow[2].x = m_leftarrow[0].x + arrawheight;
	m_leftarrow[2].y = m_recttitle.bottom + gap1;

	m_rightarrow[0].x = m_recttitle.right - 5;
	m_rightarrow[0].y = m_recttitle.bottom + arrawheight;
	m_rightarrow[1].x = m_rightarrow[0].x - arrawheight;
	m_rightarrow[1].y = m_recttitle.top - gap1;
	m_rightarrow[2].x = m_rightarrow[0].x - arrawheight;
	m_rightarrow[2].y = m_recttitle.bottom + gap1;

	m_recttitlemid = m_recttitle;
	m_recttitlemid.left = m_leftarrow[1].x;
	m_recttitlemid.right = m_rightarrow[1].x;
}
