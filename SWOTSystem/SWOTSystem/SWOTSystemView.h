// SWOTSystemView.h : interface of the CSWOTSystemView class
//


#pragma once

#include "TriangleButton.h"
class CSWOTSystemView : public CView
{
protected: // create from serialization only
	CSWOTSystemView();
	DECLARE_DYNCREATE(CSWOTSystemView)

// Attributes
public:
	CSWOTSystemDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // called first time after construct
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// Implementation
public:
	virtual ~CSWOTSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private:
	CTriangleButton m_mainbtn[6];

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SWOTSystemView.cpp
inline CSWOTSystemDoc* CSWOTSystemView::GetDocument() const
   { return reinterpret_cast<CSWOTSystemDoc*>(m_pDocument); }
#endif

