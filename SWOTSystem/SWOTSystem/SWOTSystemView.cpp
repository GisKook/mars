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

IMPLEMENT_DYNCREATE(CSWOTSystemView, CView)

BEGIN_MESSAGE_MAP(CSWOTSystemView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
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

void CSWOTSystemView::OnDraw(CDC* /*pDC*/)
{
	CSWOTSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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
	int x = 0;
	DWORD dwStyle = ( WS_VISIBLE | BS_FLAT | BS_LEFT) & ~WS_BORDER & ~WS_DLGFRAME;
	m_mainbtn[0].Create("Promotion", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[0].SetCaption("Promotion");
	x = m_mainbtn[0].MoveButton(x,0,25);

	m_mainbtn[1].Create("Production", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[1].SetCaption("Production");
	x = m_mainbtn[1].MoveButton(x,0,25);

	m_mainbtn[2].Create("Administration", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[2].SetCaption("Administration");
	x = m_mainbtn[2].MoveButton(x,0,25);

	m_mainbtn[3].Create("Management", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[3].SetCaption("Management");
	x = m_mainbtn[3].MoveButton(x,0,25);

	m_mainbtn[4].Create("Finnacial", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[4].SetCaption("Finnacial");
	x = m_mainbtn[4].MoveButton(x,0,25);

	m_mainbtn[5].Create("Legal", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION);
	m_mainbtn[5].SetCaption("Legal");
	x = m_mainbtn[5].MoveButton(x,0,25);
}

#endif //_DEBUG


// CSWOTSystemView message handlers
