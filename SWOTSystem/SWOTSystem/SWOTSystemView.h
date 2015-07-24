// SWOTSystemView.h : interface of the CSWOTSystemView class
//


#pragma once

#include "ButtonTriangle.h"
#include "Chart.h"
#include "Pie.h"
#include "ViewMenu.h"
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

private:
	int SetCoordinate(CDC *);
	void DrawRect(CDC *pdc, RECT * rect, COLORREF c);
	void DrawLogo(CDC *pdc);
private:
	const static int m_logolen;
	const static int m_logomenugap;
private:
	CChart m_chart;
	CPie m_pie;
	CViewMenu m_viemenu;
private:
	enum MenuStatus{
		Promotion = 0,
		MENUNULL = 255,
	};
	int m_menustatus;

protected:
private:
	CButtonTriangle m_mainbtn[6];

// Generated message map functions
public:
	void ResetMenu(int index);
	void SetMenu(int index);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPromotion();
	afx_msg void OnProduction();
	afx_msg void OnAdministration();
	afx_msg void OnManagement();
	afx_msg void OnFinnacial();
	afx_msg void OnLegal();
};

#ifndef _DEBUG  // debug version in SWOTSystemView.cpp
inline CSWOTSystemDoc* CSWOTSystemView::GetDocument() const
   { return reinterpret_cast<CSWOTSystemDoc*>(m_pDocument); }
#endif

