// 2dcolorView.h : interface of the CMy2dcolorView class
//


#pragma once


class CMy2dcolorView : public CView
{
protected: // create from serialization only
	CMy2dcolorView();
	DECLARE_DYNCREATE(CMy2dcolorView)

// Attributes
public:
	CMy2dcolorDoc* GetDocument() const;

// Operations
public:
private:
	void DrawRectBox(CDC *pDC, RECT rect);
	void DrawRect(CDC *pDC, RECT rect, COLORREF color);

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
	virtual ~CMy2dcolorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	RECT m_rectbox;
	RECT m_rectboxW;
	RECT m_rectcyan;
	RECT m_rectcyanW;
	
	RECT m_rectcyan1;
	RECT m_rectcyan2;
	RECT m_rectcyan3;

	RECT m_rectyellow;
	RECT m_rectMagenta;
	RECT m_rectGray;
	RECT m_rectGreen;
	RECT m_rectPurple;
	RECT m_rectPurpleW;
private:
	int m_action;
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in 2dcolorView.cpp
inline CMy2dcolorDoc* CMy2dcolorView::GetDocument() const
   { return reinterpret_cast<CMy2dcolorDoc*>(m_pDocument); }
#endif

