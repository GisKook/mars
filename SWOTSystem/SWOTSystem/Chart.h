#pragma once

class CChart
{
public:
	CChart(void);
	~CChart(void);
public:
	typedef struct{
		int count;
		COLORREF color[32];
		int height[32];
		CString str[32];
		void HistogramParam(){
			count = 0;
			memset(color, 0, sizeof(color));
			memset(height, 0, sizeof(height));
		}
	}HistogramParam;
	enum HitTestStatus{
		HTSNULL = 0,
		PROMOTION = 1,
		TITLEMID = 2,
	};
public: 
	void SetBoxRect(RECT rc){m_rectbox = rc;};
	void SetTitleRect(RECT rc);
	void SetTitle(CString title);
	void SetDC(CDC * dc){m_dc = dc;};
	void DrawBackground();
	void DrawHistogram(HistogramParam * p);
	int GetBoxHeight(){return m_rectbox.top - m_rectbox.bottom;};
	int Hittest(POINT pt);
private:

	void DrawTile(CString str);
	void DrawRect(CDC*, RECT &, COLORREF c);
	void DrawPolygon(CDC *, POINT *, int count, COLORREF c);

	void DrawArraw();
	void DrawBox();
	void DrawFont(CString str, RECT rc, int fontsize, CString fontname, COLORREF c, int fontstyle = FW_NORMAL);

	RECT GetHistoGram(int count, int height, int index);
public:
	CDC *m_dc;
	CString m_title;
	RECT m_rectbox;
	RECT m_recttitle;
	RECT m_recttitlemid;
	POINT m_leftarraw[3];
	POINT m_rightarraw[3];
};
