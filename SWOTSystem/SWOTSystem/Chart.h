#pragma once

class CChart
{
public:
	CChart(void);
	~CChart(void);
public: 
	void SetBoxRect(RECT rc){m_rectbox = rc;};
	void SetTitleRect(RECT rc){m_recttitle = rc;};
	void SetTitle(CString title){m_title = title;};
	void SetDC(CDC * dc){m_dc = dc;};

	void DrawBackground();

private:
	CDC *m_dc;

	RECT m_rectbox;

	CString m_title;
	RECT m_recttitle;
};
