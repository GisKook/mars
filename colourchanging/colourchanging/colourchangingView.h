// colourchangingView.h : interface of the CcolourchangingView class
//


#pragma once


class CcolourchangingView : public CView
{
protected: // create from serialization only
	CcolourchangingView();
	DECLARE_DYNCREATE(CcolourchangingView)

// Attributes
public:
	CcolourchangingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CcolourchangingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void drawrectange(RECT rc, COLORREF color, CDC *pDC);
	int getrectindex(CPoint point);
private:
	int m_nRect; 
	RECT * m_pRect;
	COLORREF * m_pColors;
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in colourchangingView.cpp
inline CcolourchangingDoc* CcolourchangingView::GetDocument() const
   { return reinterpret_cast<CcolourchangingDoc*>(m_pDocument); }
#endif

