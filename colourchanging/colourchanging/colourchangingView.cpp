// colourchangingView.cpp : implementation of the CcolourchangingView class
//

#include "stdafx.h"
#include "colourchanging.h"

#include "colourchangingDoc.h"
#include "colourchangingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcolourchangingView

CDC * g_pDC = NULL;
IMPLEMENT_DYNCREATE(CcolourchangingView, CView)

BEGIN_MESSAGE_MAP(CcolourchangingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CcolourchangingView construction/destruction

CcolourchangingView::CcolourchangingView()
{
	// TODO: add construction code here
	m_nRect = 5;
	m_pRect = new RECT[5];
	m_pColors = new COLORREF[5];
	for(int i = 0; i < m_nRect; i++){
		m_pRect[i].left = i*100;
		m_pRect[i].top= 0;
		m_pRect[i].right = m_pRect[i].left + 100;
		m_pRect[i].bottom = 100;
	}
	for(int i = 0; i < m_nRect; i++){
		m_pColors[i] = RGB(i*50,i*50,i*50);
	}
}

CcolourchangingView::~CcolourchangingView()
{
}

BOOL CcolourchangingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CcolourchangingView drawing

void CcolourchangingView::OnDraw(CDC* pDC)
{
	CcolourchangingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	g_pDC = pDC;
	// TODO: add draw code for native data here
	for(int i = 0; i < m_nRect; ++i){
		drawrectange(m_pRect[i], m_pColors[i], pDC);
	}
	

	
	

}


// CcolourchangingView printing

BOOL CcolourchangingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CcolourchangingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CcolourchangingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CcolourchangingView diagnostics

#ifdef _DEBUG
void CcolourchangingView::AssertValid() const
{
	CView::AssertValid();
}

void CcolourchangingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcolourchangingDoc* CcolourchangingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcolourchangingDoc)));
	return (CcolourchangingDoc*)m_pDocument;
}

void CcolourchangingView::drawrectange( RECT rc, COLORREF color, CDC *pDC ) { 
	CBrush * pOldBrush = NULL;
	CBrush * pBrush = new CBrush();
	pBrush->CreateSolidBrush(color);
	pOldBrush = pDC->SelectObject(pBrush);
	pDC->Rectangle(&rc);
	pDC->SelectObject(pOldBrush);
	delete pBrush;
}

#endif //_DEBUG


// CcolourchangingView message handlers
COLORREF getrandomcolor(){
	BYTE red = ((double)rand()/255);
	BYTE green = ((double)rand()/255);
	BYTE blue = ((double)rand()/255);

	return RGB(red, green, blue);
}
void CcolourchangingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default 
	int index = getrectindex(point);
	if(index != -1){
		m_pColors[index] = getrandomcolor();
		
		::InvalidateRect(WindowFromDC(g_pDC->GetSafeHdc()), &m_pRect[index], true);
	}

	CView::OnLButtonUp(nFlags, point);
}

int CcolourchangingView::getrectindex( CPoint point ) { 
	for (int i = 0; i < m_nRect; ++i) {
		if(point.x>m_pRect[i].left && point.y>m_pRect[i].top 
			&& point.x < m_pRect[i].right && point.y < m_pRect[i].bottom){
				return i;
		}
	}

	return -1;
}
void CcolourchangingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int index = getrectindex(point);
	
	if(index != -1){ 
		int nRect = m_nRect;
		++nRect;
		RECT * pRECT;
		COLORREF * pCOLOR;
		pRECT = new RECT[nRect];
		
		memcpy(pRECT, m_pRect, sizeof(RECT)*index);
		pRECT[index].left = m_pRect[index].left;
		pRECT[index].right = pRECT[index].left + (m_pRect[index].right-m_pRect[index].left)/4;
		pRECT[index].top = m_pRect[index].top;
		pRECT[index].bottom= m_pRect[index].bottom;
		pRECT[index+1].left = pRECT[index].right;
		pRECT[index+1].top = m_pRect[index].top;
		pRECT[index+1].right = m_pRect[index].right;
		pRECT[index+1].bottom = m_pRect[index].bottom;
		memcpy(pRECT+index+2,&m_pRect[index+1], sizeof(RECT)*(nRect - index - 2));

		pCOLOR = new COLORREF[nRect]; 
		memcpy(pCOLOR, m_pColors, sizeof(COLORREF)*index);
		pCOLOR[index] = m_pColors[index];
		pCOLOR[index+1] = getrandomcolor();
		memcpy(pCOLOR+index +2, &m_pColors[index+1], sizeof(COLORREF)*(nRect - index - 2));
		delete[] m_pColors;
		delete[] m_pRect;
		m_pColors = pCOLOR;
		m_nRect = nRect;
		m_pRect = pRECT;

	}

	CView::OnLButtonDblClk(nFlags, point);
}
