// SWOTSystemView.cpp : implementation of the CSWOTSystemView class
//

#include "stdafx.h"
#include "SWOTSystem.h"

#include "SWOTSystemDoc.h"
#include "SWOTSystemView.h"

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
#endif //_DEBUG


// CSWOTSystemView message handlers
