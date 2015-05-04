// 2dcolorView.cpp : implementation of the CMy2dcolorView class
//

#include "stdafx.h"
#include "2dcolor.h"

#include "2dcolorDoc.h"
#include "2dcolorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2dcolorView

CDC * g_pdc;
IMPLEMENT_DYNCREATE(CMy2dcolorView, CView)

BEGIN_MESSAGE_MAP(CMy2dcolorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMy2dcolorView construction/destruction

CMy2dcolorView::CMy2dcolorView()
{
	// TODO: add construction code here
	int offsetx = 100;
	int offsety = 100;
	m_rectbox.left = offsetx;
	m_rectbox.right = offsetx+1000;
	m_rectbox.top = offsety+1000;
	m_rectbox.bottom = offsety; 

	memcpy(&m_rectcyan, &m_rectbox, sizeof(RECT));
	m_rectcyan.top = 660+offsety;

	m_rectcyan1.left = offsetx;
	m_rectcyan1.right = offsetx + (m_rectbox.right-m_rectbox.left)/3;
	m_rectcyan1.top = offsety + 780;
	m_rectcyan1.bottom = offsety;

	m_rectcyan2.left = m_rectcyan1.right-1;
	m_rectcyan2.right = m_rectcyan2.left+ (m_rectbox.right - m_rectbox.left)/3;
	m_rectcyan2.top = offsety + 290;
	m_rectcyan2.bottom = offsety;

	m_rectcyan3.left = m_rectcyan2.right-2;
	m_rectcyan3.right = m_rectbox.right;
	m_rectcyan3.top = offsety + 430;
	m_rectcyan3.bottom = offsety;

	int temp = (m_rectbox.right - m_rectbox.left)/5;
	m_rectyellow.left = offsetx;
	m_rectyellow.right = m_rectyellow.left + temp;
	m_rectyellow.bottom = offsety;
	m_rectyellow.top = offsety+660;
	
	m_rectMagenta.left = m_rectyellow.right-2;
	m_rectMagenta.right = m_rectMagenta.left + temp;
	m_rectMagenta.bottom = offsety;
	m_rectMagenta.top = offsety+330;

	m_rectGray.left = m_rectMagenta.right -2;
	m_rectGray.right = m_rectGray.left + temp;
	m_rectGray.bottom = offsety;
	m_rectGray.top = offsety+250;

	m_rectGreen.left = m_rectGray.right - 2;
	m_rectGreen.right = m_rectGreen.left + temp;
	m_rectGreen.bottom = offsety;
	m_rectGreen.top = offsety+750;

	m_rectPurple.left = m_rectGreen.right - 2;
	m_rectPurple.right = m_rectbox.right;
	m_rectPurple.bottom = offsety;
	m_rectPurple.top = offsety + 500;
	
	m_action = 0;
}

CMy2dcolorView::~CMy2dcolorView()
{
}

BOOL CMy2dcolorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy2dcolorView drawing

void CMy2dcolorView::OnDraw(CDC* pDC)
{
	CMy2dcolorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	g_pdc = pDC;
	// TODO: add draw code for native data here
	int mapmode = pDC->SetMapMode(MM_LOMETRIC);
	//int mapmode = pDC->SetMapMode(MM_TEXT);
	RECT rect;
	::GetClientRect(pDC->GetWindow()->GetSafeHwnd(),&rect);

	memcpy(&m_rectboxW, &m_rectbox, sizeof(m_rectboxW));
	memcpy(&m_rectcyanW, &m_rectcyan, sizeof(m_rectcyanW));
	memcpy(&m_rectPurpleW, &m_rectPurple, sizeof(m_rectPurple));
	pDC->LPtoDP(&m_rectcyanW);
	pDC->LPtoDP(&m_rectboxW);
	pDC->LPtoDP(&m_rectPurpleW);
	m_rectboxW.top += rect.bottom;
	m_rectboxW.bottom += rect.bottom;
	m_rectcyanW.top += rect.bottom;
	m_rectcyanW.bottom += rect.bottom;
	m_rectPurpleW.top += rect.bottom;
	m_rectPurpleW.bottom += rect.bottom;
	pDC->SetViewportOrg(0, rect.bottom);
	switch(m_action){
		case 0:
			DrawRect(pDC, m_rectcyan, RGB(0,172,236));
			DrawRectBox(pDC,m_rectbox);
			break;
		case 1:
			DrawRect(pDC, m_rectcyan1, RGB(204,238,251));
			DrawRect(pDC, m_rectcyan2, RGB(178,230,249));
			DrawRect(pDC, m_rectcyan3, RGB(153,222,247));
			DrawRectBox(pDC,m_rectbox);
			break;
		case 2:
			DrawRect(pDC, m_rectyellow, RGB(255,248,148));
			DrawRect(pDC, m_rectMagenta, RGB(228,134,195));
			DrawRect(pDC, m_rectGray, RGB(168,168,168));
			DrawRect(pDC, m_rectGreen, RGB(139,191,79));
			DrawRect(pDC, m_rectPurple, RGB(116,115,177));
			DrawRectBox(pDC,m_rectbox);
			break;
		default:
			break;
	}
	pDC->SetMapMode(mapmode);
}


// CMy2dcolorView printing

BOOL CMy2dcolorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy2dcolorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy2dcolorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy2dcolorView diagnostics

#ifdef _DEBUG
void CMy2dcolorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2dcolorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2dcolorDoc* CMy2dcolorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2dcolorDoc)));
	return (CMy2dcolorDoc*)m_pDocument;
}

void CMy2dcolorView::DrawRectBox( CDC *pDC, RECT rect)
{
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
	CPoint * pts = new CPoint[5]; 
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
	
	rectex.left = 0;
	rectex.right = 1;
	rectex.top = 1;
	rectex.bottom = 0;
	pDC->DPtoLP(&rectex);
	pen2.CreatePen(PS_SOLID, rectex.right-rectex.left, RGB(0,0,0));
	pDC->SelectObject(&pen2);
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

	delete []pts;
	pDC->SelectObject(oldpen);
}

void CMy2dcolorView::DrawRect( CDC *pDC, RECT rect, COLORREF color )
{ 
	CPen pen;
	CPen * oldpen;
	pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	
	CBrush brush;
	CBrush *oldbrush;
	brush.CreateSolidBrush(color);
	oldbrush = pDC->SelectObject(&brush);
	pDC->Rectangle(&rect);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	
}


#endif //_DEBUG


// CMy2dcolorView message handlers

void CMy2dcolorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 
	if (point.x >= m_rectcyanW.left && point.x <= m_rectcyanW.right && point.y >= m_rectcyanW.top && point.y <= m_rectcyanW.bottom)
	{
		m_action = 1;
		printf("click\n");
		::InvalidateRect(this->GetSafeHwnd(), NULL, true);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMy2dcolorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_action == 0 && point.x >= m_rectcyanW.left && point.x <= m_rectcyanW.right && point.y >= m_rectcyanW.top && point.y <= m_rectcyanW.bottom)
	{
		m_action = 2;
		printf("dclick\n");
	}
	CView::OnLButtonDblClk(nFlags, point);
}

void CMy2dcolorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_action = 0;
	CView::OnLButtonUp(nFlags, point);
}
