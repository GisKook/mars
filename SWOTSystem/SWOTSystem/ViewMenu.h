#pragma once
#include <vector>

class CViewMenu
{
public:
	CViewMenu(void);
	~CViewMenu(void);
public:
	void SetRect(RECT rc){m_rectmenu = rc;}
	void SetDC(CDC *dc){m_dc = dc;}
	void AddMenuItem(CString str);
	void Clear();
	void Draw();
	int GetItemCount(){return m_menuitem.size();}
private:
	void DrawRect(CDC*, RECT &, COLORREF c);
	RECT GetRect(RECT & rc, int count, int index);

	void DrawFont(CString str, RECT rc, int fontsize, CString fontname, COLORREF c, int fontstyle = FW_NORMAL);
private:
	CDC * m_dc;
	RECT m_rectmenu;
	std::vector<CString> m_menuitem;
};
