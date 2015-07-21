// SWOTSystemView.cpp : implementation of the CSWOTSystemView class
//

#include "stdafx.h"
#include "SWOTSystem.h"

#include "SWOTSystemDoc.h"
#include "SWOTSystemView.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSWOTSystemView
const int CSWOTSystemView::m_logolen = 200;
IMPLEMENT_DYNCREATE(CSWOTSystemView, CView)

BEGIN_MESSAGE_MAP(CSWOTSystemView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDM_PROMOTION, &CSWOTSystemView::OnPromotion)
END_MESSAGE_MAP()

// CSWOTSystemView construction/destruction

CSWOTSystemView::CSWOTSystemView()
{
	// TODO: add construction code here

}

CSWOTSystemView::~CSWOTSystemView()
{
}

BOOL CSWOTSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSWOTSystemView drawing

void CSWOTSystemView::OnDraw(CDC* pdc)
{
	CSWOTSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawLogo(pdc);

	// TODO: add draw code for native data here
}


// CSWOTSystemView printing

BOOL CSWOTSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSWOTSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSWOTSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSWOTSystemView diagnostics

#ifdef _DEBUG
void CSWOTSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSWOTSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSWOTSystemDoc* CSWOTSystemView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSWOTSystemDoc)));
	return (CSWOTSystemDoc*)m_pDocument;
}

void CSWOTSystemView::OnInitialUpdate()
{ 
	int x = m_logolen;
	DWORD dwStyle = ( WS_VISIBLE | BS_FLAT | BS_LEFT | BS_OWNERDRAW ) & ~WS_BORDER & ~WS_DLGFRAME;
	m_mainbtn[0].Create("Promotion", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[0].SetCaption("Promotion");
	m_mainbtn[0].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[0].MoveButton(x,0,18);

	m_mainbtn[1].Create("Production", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[1].SetCaption("Production");
	m_mainbtn[1].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[1].MoveButton(x,0,18);

	m_mainbtn[2].Create("Administration", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[2].SetCaption("Administration");
	m_mainbtn[2].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[2].MoveButton(x,0,18);

	m_mainbtn[3].Create("Management", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[3].SetCaption("Management");
	m_mainbtn[3].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[3].MoveButton(x,0,18);

	m_mainbtn[4].Create("Finnacial", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[4].SetCaption("Finnacial");
	m_mainbtn[4].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[4].MoveButton(x,0,18);

	m_mainbtn[5].Create("Legal", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[5].SetCaption("Legal");
	m_mainbtn[5].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[5].MoveButton(x,0,18);
}

void CSWOTSystemView::DrawLogo( CDC *pdc )
{ 
	RECT rect, rectbelow, rectleft;
	GetClientRect(&rect);
	DrawRect(pdc,&rect,RGB(255,255,255));
	rectbelow = rect;
	rectbelow.top = m_mainbtn[0].GetHeight() - 1;
	rectbelow.bottom = m_mainbtn[0].GetHeight()*2;
	DrawRect(pdc,&rectbelow, RGB(125,125,125));
	rectleft = rect;
	rectleft.right = m_logolen - 30;
	DrawRect(pdc,&rectleft, RGB(125,125,125));

	int height = m_mainbtn[0].GetHeight();
	rect.bottom = height;
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(RGB(39,38,38)); 
	oldbrush = pdc->SelectObject(&brush);
	CPen pen, *oldpen;
	pen.CreatePen(PS_NULL, 0, RGB(39,38,38));
	oldpen = pdc->SelectObject(&pen);
	RECT logorect = rect;
	logorect.right = m_logolen - 30;
	pdc->Rectangle(&logorect);

	int oldmode = pdc->SetBkMode(TRANSPARENT);
	
	CFont font, *oldfont;
	font.CreateFont(19,
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		"Microsoft YaHei");
	oldfont = pdc->SelectObject(&font);
	
	COLORREF oldtxtcolor = pdc->SetTextColor(RGB(255,255,255));		// Set the color of the caption to be yellow
	pdc->DrawText("S W O T  P R O F I L E", &logorect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pdc->SelectObject(oldfont);
	font.DeleteObject(); 
	pdc->SelectObject(oldpen);
	pen.DeleteObject(); 
	pdc->SelectObject(oldbrush);
	brush.DeleteObject();
	pdc->SetBkMode(oldmode);
	pdc->SetTextColor(oldtxtcolor);
}

void CSWOTSystemView::DrawRect( CDC *pDC, RECT * rect, COLORREF c )
{
	CBrush backbrush, *oldbackbrush;
	backbrush.CreateSolidBrush(c);
	oldbackbrush = pDC->SelectObject(&backbrush);
	CPen pen,*oldpen;
	pen.CreatePen(PS_NULL,0, RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(rect);
	pDC->SelectObject(oldbackbrush);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	backbrush.DeleteObject();
}

#endif //_DEBUG


// CSWOTSystemView message handlers

void CSWOTSystemView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
}

void CSWOTSystemView::OnPromotion()
{
	MessageBox(__FUNCTION__);
	ResetMenu(0);
}

void CSWOTSystemView::OnProduction()
{
	MessageBox(__FUNCTION__);
	ResetMenu(1);

}

void CSWOTSystemView::OnAdministration()
{
	MessageBox(__FUNCTION__);
	ResetMenu(2);

}

void CSWOTSystemView::OnManagement()
{
	MessageBox(__FUNCTION__);
	ResetMenu(3);

}

void CSWOTSystemView::OnFinnacial()
{
	MessageBox(__FUNCTION__);
	ResetMenu(4);

}

void CSWOTSystemView::OnLegal()
{
	MessageBox(__FUNCTION__);
	ResetMenu(5);

}

void CSWOTSystemView::ResetMenu(int index)
{
	if(index < 0 || index > 5){
		return;
	}
	for(int i = 0; i < 6; ++i){ 
		if(i == index){
			continue;
		}else{
			if (m_mainbtn[index].GetStatus() != CButtonTriangle::Normal) {
				m_mainbtn[index].SetStatus(CButtonTriangle::Normal);
			}
		}
	} 
}
