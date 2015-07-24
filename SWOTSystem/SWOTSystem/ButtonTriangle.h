#pragma once
#include <vector>

// CButtonTriangle

class CButtonTriangle : public CButton
{
	DECLARE_DYNAMIC(CButtonTriangle)

public:
	CButtonTriangle();
	virtual ~CButtonTriangle();

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	enum ButtonStatus{ 
		Normal = 0,
		SelectText,
		SelectArrow,
		SelectArrowOff,
	} ;
private:
public:
	BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int inde);
public: 
	int MoveButton(int x, int y, int height);

private:
	CMenu m_menu;
	
public:
	void SetStatus(ButtonStatus status);
	int GetStatus(){return m_status;};
	int GetHeight(){return m_size.cy;};
	void DrawRect(CDC *pDC, RECT &rect, COLORREF c);
	BOOL AddMenuItem(UINT nMenuId, const CString strMenu, UINT nMenuFlags);
	CString GetMenuString(int index);
	int GetMenuItemCount();

private:
	CString m_strCaption;
	SIZE m_size;
	int m_fontsize;
	POINT m_triangle[3];
	int m_status;
	CWnd * m_parent;
	int m_index;
	std::vector<CString> m_menuitem;

	static const CString m_fontname;
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnNcPaint();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


