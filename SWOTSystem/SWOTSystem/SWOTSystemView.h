// SWOTSystemView.h : interface of the CSWOTSystemView class
//


#pragma once

#include "ButtonTriangle.h"
#include "Chart.h"
#include "Pie.h"
#include "ViewMenu.h"
#include <vector>
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
	void InvalidateRectEx(RECT & rect);
	RECT ConvertRect(RECT & rect);
private:
	const static int m_logolen;
	const static int m_logomenugap;
private:
	CChart::HistogramParam *m_hp;
	int m_hpindex;
	std::vector<CChart::HistogramParam *>m_histroy;

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

private:
	void GetScale(CDC *pdc);
	int m_dpix;
	int m_dpiy;
	RECT m_clientrect;
	double m_scalex;
	double m_scaley;
	POINT ConvertPoint(POINT pt);

	void SetRect();

protected:
private:
	CButtonTriangle m_mainbtn[6];
private:
	int m_topheight;

// Generated message map functions
public:
	void ResetMenu(int index);
	void SetMenu(int index);
	void RestChart();
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
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPromotionAdvertising();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in SWOTSystemView.cpp
inline CSWOTSystemDoc* CSWOTSystemView::GetDocument() const
   { return reinterpret_cast<CSWOTSystemDoc*>(m_pDocument); }
#endif

