#pragma once


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
	} ;
private:
public: 
	void SetCaption(CString strCaption);
	int MoveButton(int x, int y, int height);

public:
	void SetStatus(ButtonStatus status);
	int GetStatus(){return m_status;};
	int GetHeight(){return m_size.cy;};
	void DrawRect(CDC *pDC, RECT &rect, COLORREF c);

private:
	CString m_strCaption;
	SIZE m_size;
	int m_fontsize;
	POINT m_triangle[3];
	int m_status;

	static const CString m_fontname;
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnNcPaint();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


