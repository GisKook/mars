#include "StdAfx.h"
#include "Pie.h"
#include "math.h"

const double CPie::PI=3.14159265;
const double CPie::radio=3.14159265/180;
const int CPie::gap = 50;
CPie::CPie(void)
{
}

CPie::~CPie(void)
{
}

void CPie::DrawRect( CDC* pDC, RECT & rect, COLORREF c )
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

void CPie::DrawBackground()
{
	DrawRect(m_dc, m_rectbackground, RGB(222,222,222));
}

void CPie::DrawCircle()
{
	RECT rc = m_rectmaxcircle;
	int sidelengthgap = (rc.right - rc.left)/8;

	m_dc->SelectObject(GetStockObject(NULL_BRUSH));
	m_dc->Ellipse(&rc);

	for (int i = 0; i < 3; i++) {
		rc.left += sidelengthgap;
		rc.right -= sidelengthgap;
		rc.top -= sidelengthgap;
		rc.bottom += sidelengthgap;
		m_dc->Ellipse(&rc);
	}
}

void CPie::DrawLines()
{
	RECT rc = m_rectmaxcircle; 
	int sidelength = (m_rectmaxcircle.right - m_rectmaxcircle.left);
	int radius = sidelength / 2;
	POINT pt1, pt2;

	pt1.x = rc.left;
	pt1.y = rc.bottom + radius;
	pt2.x = rc.right;
	pt2.y = rc.bottom + radius;
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

	pt1.x = rc.left + radius;
	pt1.y = rc.top;
	pt2.x = rc.left + radius;
	pt2.y = rc.bottom;
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

	pt1.x = rc.left + (radius - radius*cos(radio*30));
	pt1.y = rc.top - (radius - radius*sin(radio*30));
	pt2.x = rc.right - (radius - radius*cos(radio*30));
	pt2.y = rc.bottom + (radius - radius*sin(radio*30));
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

	pt1.x = rc.left + (radius - radius*cos(radio*60));
	pt1.y = rc.top - (radius - radius*sin(radio*60));
	pt2.x = rc.right - (radius - radius*cos(radio*60));
	pt2.y = rc.bottom + (radius - radius*sin(radio*60));
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

	pt1.x = rc.left + (radius - radius*cos(radio*120));
	pt1.y = rc.top - (radius - radius*sin(radio*120));
	pt2.x = rc.right - (radius - radius*cos(radio*120));
	pt2.y = rc.bottom + (radius - radius*sin(radio*120));
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

	pt1.x = rc.left + (radius - radius*cos(radio*150));
	pt1.y = rc.top - (radius - radius*sin(radio*150));
	pt2.x = rc.right - (radius - radius*cos(radio*150));
	pt2.y = rc.bottom + (radius - radius*sin(radio*150));
	m_dc->MoveTo(pt1);
	m_dc->LineTo(pt2);

}

void CPie::DrawPie( CRect rect,int anglestart, int angleend, COLORREF c )
{
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(c);
	oldbrush = m_dc->SelectObject(&brush);

	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, c);
	oldpen = m_dc->SelectObject(&pen);

	int sidelength = rect.Width();
	int radius = sidelength/2;
	POINT pt1,pt2;
	pt1.x = rect.left + (radius - radius*cos(radio*anglestart));
	pt1.y = rect.top - (radius - radius*sin(radio*anglestart));
	pt2.x = rect.left + (radius - radius*cos(radio*angleend));
	pt2.y = rect.top - (radius - radius*sin(radio*angleend));
	m_dc->Pie(rect, pt1,pt2);

	m_dc->SelectObject(oldpen);
	pen.DeleteObject();
	m_dc->SelectObject(oldbrush);
	brush.DeleteObject();
}

void CPie::Draw()
{
	DrawBackground();
	RECT backcirclerect = m_rectmaxcircle;
	ZoomInRect(backcirclerect, m_ringwidth);
	DrawSolidCircle(backcirclerect,RGB(0,0,0));
	DrawSolidCircle(m_rectmaxcircle,RGB(255,255,255));
	DrawPieTitle("PROMOTION");
	RECT rc = m_rectmaxcircle;
	int sidelength = rc.right - rc.left;
	int radius = sidelength/2;
	
	ZoomOutRect(rc, radius*9/16);
	DrawPie(rc,30,0,RGB(127,0,255));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*3/8);
	DrawPie(rc,60,30,RGB(255,1,255));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*1/8);
	DrawPie(rc,90,60,RGB(255,0,127));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*1/2+2);
	DrawPie(rc,120,90,RGB(255,0,0));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*1/2-2);
	DrawPie(rc,150,120,RGB(255,127,0));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*1/3);
	DrawPie(rc,180,150,RGB(255,255,0));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*7/10);
	DrawPie(rc,210,180,RGB(127,255,0));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*5/16);
	DrawPie(rc,240,210,RGB(0,255,0));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*7/24);
	DrawPie(rc,270,240,RGB(0,255,127));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*1/8);
	DrawPie(rc,300,270,RGB(0,255,255));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*7/10);
	DrawPie(rc,330,300,RGB(0,127,255));

	rc = m_rectmaxcircle;
	ZoomOutRect(rc, radius*3/8);
	DrawPie(rc,360,330,RGB(0,0,255));

	
	DrawCircle();
	DrawLines();
	
}

void CPie::ZoomOutRect( RECT &rc, int x ) {
	rc.left += x;
	rc.right -= x;
	rc.top -= x;
	rc.bottom += x;
}

void CPie::SetRect( RECT rc )
{
	m_rectbackground = rc; 

	RECT rcmax = m_rectbackground;
	if (m_rectbackground.top - m_rectbackground.bottom > m_rectbackground.right - m_rectbackground.left) {
		rcmax.bottom = m_rectbackground.top - (m_rectbackground.right - m_rectbackground.left);
	}else{
		rcmax.right = m_rectbackground.left + (m_rectbackground.top - m_rectbackground.bottom);
	}

	rcmax.left += gap;
	rcmax.right -= gap;
	rcmax.top -= gap;
	rcmax.bottom += gap;

	m_rectmaxcircle = rcmax;
	m_ringwidth = (m_rectmaxcircle.right - m_rectmaxcircle.left)/20;
	ZoomOutRect(m_rectmaxcircle, m_ringwidth);

	
}

void CPie::DrawSolidCircle( RECT &rect, COLORREF c )
{
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(c);
	oldbrush = m_dc->SelectObject(&brush);
	
	m_dc->Ellipse(&rect);

	brush.DeleteObject();
	m_dc->SelectObject(oldbrush);
	
}

void CPie::ZoomInRect( RECT &rc, int x )
{
	rc.left -= x;
	rc.right += x;
	rc.top += x;
	rc.bottom -= x;
}

void CPie::DrawPieTitle( CString str )
{
	int charactercount = str.GetLength();
	int angle = 0;
	if(charactercount & 1){
		angle = 90 + (45 - charactercount/2*5);
	}else{
		angle = 90 + (45 - charactercount/2*5-2);
	}
	int incircleradius = (m_rectmaxcircle.right - m_rectmaxcircle.left)/2;
	int radius = incircleradius+m_ringwidth;
	int x,y;
	for(int i = 0; i < charactercount; ++i){
		x = m_rectmaxcircle.left + incircleradius + cos((180-angle)*radio)*radius;
		y = m_rectmaxcircle.top + m_ringwidth - (radius - sin(angle*radio)*radius);
		DrawChar(CString(str.GetAt(i)), m_ringwidth,"Microsoft YaHei", x,y,angle+270,RGB(255,255,255));
		angle+=5;
	}
}

void CPie::DrawChar( CString str, int fontsize, CString fontname,int x, int y, int angle, COLORREF c )
{
	CFont font , * oldfont;
	
	
	font.CreateFont(fontsize, // nHeight 
		0, // nWidth 
		angle*10, // nEscapement 
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
		fontname);
	oldfont = m_dc->SelectObject(&font);
	int bkmode = m_dc->SetBkMode(TRANSPARENT);
	m_dc->SetTextColor(c);
	m_dc->TextOut(x,y, str, str.GetLength());
	m_dc->SetBkMode(bkmode);
	
	m_dc->SelectObject(oldfont);
	font.DeleteObject();
}
