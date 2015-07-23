#pragma once

class CPie
{
public:
	CPie(void);
	~CPie(void);
public:
	void SetDC(CDC *dc){m_dc = dc;};
	void SetRect(RECT rc);
	void DrawBackground();
	void DrawCircle();
	void DrawLines();
	void DrawPie(CRect rect, int anglestart, int angleend, COLORREF c);
	void DrawSolidCircle(RECT &rect, COLORREF c);

	void DrawChar(CString str, int fontsize, CString fontname, int x, int y, int angle, COLORREF c);
	void DrawPieTitle(CString str);

	void Draw();
	
private:
	void DrawRect(CDC*, RECT &, COLORREF c);
	void ZoomOutRect(RECT &rc, int x);
	void ZoomInRect(RECT &rc, int x);
private:
	RECT m_rectbackground;
	RECT m_rectmaxcircle;
	CDC * m_dc;
	int m_ringwidth;
private:
	static const double PI;
	static const double radio;
	static const int gap;
};
