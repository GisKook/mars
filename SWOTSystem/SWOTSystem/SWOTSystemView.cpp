// SWOTSystemView.cpp : implementation of the CSWOTSystemView class
//

#include "stdafx.h"
#include "SWOTSystem.h"

#include "SWOTSystemDoc.h"
#include "SWOTSystemView.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSWOTSystemView
const int CSWOTSystemView::m_logolen = 200;
const int CSWOTSystemView::m_logomenugap = 15;
const char * g_fontname = "Arial";
IMPLEMENT_DYNCREATE(CSWOTSystemView, CView)

BEGIN_MESSAGE_MAP(CSWOTSystemView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDM_PROMOTION, &CSWOTSystemView::OnPromotion)
	ON_BN_CLICKED(IDM_PRODUCTION, &CSWOTSystemView::OnProduction)
	ON_BN_CLICKED(IDM_ADMINISTRATION, &CSWOTSystemView::OnAdministration)
	ON_BN_CLICKED(IDM_MANAGEMENT, &CSWOTSystemView::OnManagement)
	ON_BN_CLICKED(IDM_FINNACIAL, &CSWOTSystemView::OnFinnacial)
	ON_BN_CLICKED(IDM_LEGAL, &CSWOTSystemView::OnLegal)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDMP_ADVERTISING, &CSWOTSystemView::OnPromotionAdvertising)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CSWOTSystemView construction/destruction

CSWOTSystemView::CSWOTSystemView():m_menustatus(255), m_scalex(0), m_scaley(0),m_topheight(0)
{
	// TODO: add construction code here
	m_hp = new CChart::HistogramParam;
	m_hp->count = 0; 
	m_hp->title = "";
	m_histroy.push_back(m_hp);
	m_hpindex = 1;
}

CSWOTSystemView::~CSWOTSystemView()
{
}

BOOL CSWOTSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSWOTSystemView drawing

void CSWOTSystemView::OnDraw(CDC* pdc)
{
	CSWOTSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawLogo(pdc);
	GetScale(pdc);
	SetRect();
	if(m_menustatus == Promotion){
		m_viemenu.SetDC(pdc);
		m_viemenu.Draw();
	}else{
		DrawLogo(pdc);
	}

	int mapmode = SetCoordinate(pdc);

	m_chart.SetDC(pdc);
	m_chart.DrawHistogram(m_hp);
	m_chart.DrawBackground(); 
	m_pie.SetDC(pdc);
	m_pie.Draw();

	pdc->SetMapMode(mapmode);
	// TODO: add draw code for native data here
}


// CSWOTSystemView printing

BOOL CSWOTSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSWOTSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSWOTSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSWOTSystemView diagnostics

#ifdef _DEBUG
void CSWOTSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSWOTSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSWOTSystemDoc* CSWOTSystemView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSWOTSystemDoc)));
	return (CSWOTSystemDoc*)m_pDocument;
}

void CSWOTSystemView::OnInitialUpdate()
{ 
	int x = m_logolen;
	int fontsize = 18;
	DWORD dwStyle = ( WS_VISIBLE | BS_FLAT | BS_LEFT | BS_OWNERDRAW ) & ~WS_BORDER & ~WS_DLGFRAME;
	m_mainbtn[0].Create("Promotion", dwStyle, CRect(0,0,0,0), this, IDM_PROMOTION, 0);
	m_mainbtn[0].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	m_mainbtn[0].MoveButton(x,0,fontsize);
	m_topheight = m_mainbtn[0].GetHeight()*2;
	x = m_mainbtn[0].MoveButton(x,m_topheight,fontsize);
	m_mainbtn[0].AddMenuItem(IDMP_PROMOTION, "1.   Promotion", 0);
	m_mainbtn[0].AddMenuItem(IDMP_PUBLICRELATIONS, "1.1 Public relations(PR)", 0);
	m_mainbtn[0].AddMenuItem(IDMP_RECEPTION, "1.2 Reception", 0);
	m_mainbtn[0].AddMenuItem(IDMP_CUSTOMERSERVICES, "1.3 Customer Services", 0);
	m_mainbtn[0].AddMenuItem(IDMP_SALES, "1.4 Sales", 0);
	m_mainbtn[0].AddMenuItem(IDMP_AFTERSALESSUPPORT, "1.5 After-sales Support", 0);
	m_mainbtn[0].AddMenuItem(IDMP_MARKETING , "1.6 Marketing", 0);
	m_mainbtn[0].AddMenuItem(IDMP_ADVERTISING, "1.7 Advertising", 0);
	m_mainbtn[0].AddMenuItem(IDMP_PROMOTION2, "1.8 Promotion", 0);

	m_mainbtn[1].Create("Production", dwStyle, CRect(0,0,0,0), this, IDM_PRODUCTION, 1);
	m_mainbtn[1].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[1].MoveButton(x,m_topheight,fontsize);

	m_mainbtn[2].Create("Administration", dwStyle, CRect(0,0,0,0), this, IDM_ADMINISTRATION, 2);
	m_mainbtn[2].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[2].MoveButton(x,m_topheight,fontsize);

	m_mainbtn[3].Create("Management", dwStyle, CRect(0,0,0,0), this, IDM_MANAGEMENT, 3);
	m_mainbtn[3].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[3].MoveButton(x,m_topheight,fontsize);

	m_mainbtn[4].Create("Finnacial", dwStyle, CRect(0,0,0,0), this, IDM_FINNACIAL, 4);
	m_mainbtn[4].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[4].MoveButton(x,m_topheight,fontsize);

	m_mainbtn[5].Create("Legal", dwStyle, CRect(0,0,0,0), this, IDM_LEGAL,5);
	m_mainbtn[5].ModifyStyleEx( 0, WS_EX_STATICEDGE, 0);
	x = m_mainbtn[5].MoveButton(x,m_topheight,fontsize);

}

void CSWOTSystemView::DrawLogo( CDC *pdc )
{ 
	RECT rect, rectbelow, rectleft,recttop;
	GetClientRect(&rect);
	DrawRect(pdc,&rect,RGB(255,255,255));
	rectbelow = rect;
	rectbelow.top = m_mainbtn[0].GetHeight() - 1 + m_topheight;
	rectbelow.bottom = m_mainbtn[0].GetHeight()*2+m_topheight;
	DrawRect(pdc,&rectbelow, RGB(125,125,125));
	recttop = rect;
	recttop.bottom = m_topheight;
	DrawRect(pdc,&recttop, RGB(211,211,211));
	rectleft = rect;
	rectleft.top = m_topheight;
	rectleft.right = m_logolen - m_logomenugap;
	DrawRect(pdc,&rectleft, RGB(125,125,125));

	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(RGB(39,38,38)); 
	oldbrush = pdc->SelectObject(&brush);
	CPen pen, *oldpen;
	pen.CreatePen(PS_NULL, 0, RGB(39,38,38));
	oldpen = pdc->SelectObject(&pen);
	RECT logorect = rect;
	logorect.top = m_topheight-1;
	logorect.right = m_logolen - m_logomenugap;
	logorect.bottom = logorect.top + m_mainbtn[0].GetHeight();
	pdc->Rectangle(&logorect);

	int oldmode = pdc->SetBkMode(TRANSPARENT);

	CFont font, *oldfont;
	font.CreateFont(m_mainbtn[0].GetHeight()*0.7,
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		g_fontname);
	oldfont = pdc->SelectObject(&font);

	COLORREF oldtxtcolor = pdc->SetTextColor(RGB(255,255,255));		// Set the color of the caption to be yellow
	pdc->DrawText("S W O T  P R O F I L E", &logorect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	CFont fonttop;
	fonttop.CreateFont(m_topheight/2,
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		g_fontname);
	pdc->SelectObject(&fonttop);
	pdc->SetTextColor(RGB(0,0,0));		// Set the color of the caption to be yellow
	recttop.left += 10;
	pdc->DrawText("SWOT System", &recttop, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	pdc->SelectObject(oldfont);
	font.DeleteObject(); 
	fonttop.DeleteObject();
	pdc->SelectObject(oldpen);
	pen.DeleteObject(); 
	pdc->SelectObject(oldbrush);
	brush.DeleteObject();
	pdc->SetBkMode(oldmode);
	pdc->SetTextColor(oldtxtcolor);
}

void CSWOTSystemView::DrawRect( CDC *pDC, RECT * rect, COLORREF c )
{
	CBrush backbrush, *oldbackbrush;
	backbrush.CreateSolidBrush(c);
	oldbackbrush = pDC->SelectObject(&backbrush);
	CPen pen,*oldpen;
	pen.CreatePen(PS_NULL,0, RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(rect);
	pDC->SelectObject(oldbackbrush);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	backbrush.DeleteObject();
}

#endif //_DEBUG


// CSWOTSystemView message handlers

void CSWOTSystemView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MSG message;
	int dbclktime = GetDoubleClickTime();
	DWORD st = GetTickCount();
	while(1)
	{
		if(::PeekMessage(&message, NULL, 0 ,0 , PM_REMOVE))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
			if(message.message == WM_LBUTTONDBLCLK)
				return;
		}
		DWORD et = GetTickCount();
		if(et - st > 200){
			break;
		}
		CView::OnLButtonDown(nFlags, point);
	}
	if( CChart::PROMOTION == m_chart.Hittest(ConvertPoint(point)) && m_menustatus == Promotion){ 
		m_hp = new CChart::HistogramParam;
		m_hp->count = 3;

		m_hp->height[0] = m_chart.GetBoxHeight()*10/16;
		m_hp->color[0] = RGB(247,229,213);
		m_hp->height[1] = m_chart.GetBoxHeight()*7/20;
		m_hp->color[1] = RGB(240,203,171);
		m_hp->height[2] = m_chart.GetBoxHeight()*16/20;
		m_hp->color[2] = RGB(233,178,130);
		m_hp->title = m_chart.m_title;

		m_histroy.push_back(m_hp);
		m_hpindex = m_histroy.size();
		InvalidateRectEx(m_chart.m_rectbox);
	}else if(CChart::TITLEMID == m_chart.Hittest(ConvertPoint(point)) && m_menustatus == Promotion){
		m_hp = new CChart::HistogramParam;
		m_hp->count = 1;
		m_hp->height[0] = m_chart.GetBoxHeight()/2;
		m_hp->color[0] = RGB(226,152,88);
		m_hp->title = m_chart.m_title;
		m_histroy.push_back(m_hp);
		m_hpindex  = m_histroy.size();

		InvalidateRectEx(m_chart.m_rectbox);
	}else if(CChart::LEFTARROW == m_chart.Hittest(ConvertPoint(point))){ 
		m_hpindex--;
		if(m_hpindex == m_histroy.size() - 1){
			m_hpindex --;
		}
		if(m_hpindex <= 0 ){
			m_hpindex = 0;
		}else if(m_hpindex >= m_histroy.size()){
			m_hpindex = m_histroy.size()-1;
		}
		CChart::HistogramParam *hp = m_histroy[m_hpindex];
		fprintf(stdout, "total %d leftarraw  :%d \n", m_histroy.size(), m_hpindex);
		if(hp != m_hp)
		{
			m_hp = hp;
			InvalidateRectEx(m_chart.m_rectbox);
			InvalidateRectEx(m_chart.m_recttitle);
		}
	}else if(CChart::RIGHTARROW == m_chart.Hittest(ConvertPoint(point))){ 
		m_hpindex++;
		if(m_hpindex <= 0 ){
			m_hpindex = 0;
		}else if(m_hpindex >= m_histroy.size()){
			m_hpindex = m_histroy.size() - 1;
		}
		
		fprintf(stdout, "total %d rightarraw :%d \n", m_histroy.size(), m_hpindex);
		CChart::HistogramParam *hp = m_histroy[m_hpindex];
		if(hp != m_hp)
		{
			m_hp = hp;
			InvalidateRectEx(m_chart.m_rectbox);
			InvalidateRectEx(m_chart.m_recttitle);
		}
	}else{
	}
	CView::OnLButtonDown(nFlags, point);
}

void CSWOTSystemView::OnPromotion()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(0);
	if(m_mainbtn[0].GetStatus() == CButtonTriangle::SelectText){
		m_viemenu.Clear();
		RECT rc;
		const int gap = 10;
		rc.left = gap;
		rc.right = rc.left + (m_logolen - m_logomenugap - gap * 2);
		rc.top = m_mainbtn[0].GetHeight()*2+m_topheight;
		rc.bottom = rc.top + m_mainbtn[0].GetMenuItemCount()*35;
		m_viemenu.SetRect(rc);

		m_chart.SetTitle("P R O M O T I O N");
		m_hp = new CChart::HistogramParam;
		m_hp->count = 1;
		m_hp->height[0] = m_chart.GetBoxHeight()/2;
		m_hp->color[0] = RGB(226,152,88);
		m_hp->title = m_chart.m_title;
		m_histroy.push_back(m_hp);
		m_hpindex = m_histroy.size();

		rc = m_chart.m_rectbox;
		rc.bottom = m_chart.m_recttitle.bottom;
		InvalidateRectEx(rc);
	}	

	SetMenu(0);
}

void CSWOTSystemView::OnProduction()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(1);
	SetMenu(1);
}

void CSWOTSystemView::OnAdministration()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(2);
}

void CSWOTSystemView::OnManagement()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(3);
}

void CSWOTSystemView::OnFinnacial()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(4);
}

void CSWOTSystemView::OnLegal()
{
	//MessageBox(__FUNCTION__);
	ResetMenu(5);
}

void CSWOTSystemView::ResetMenu(int index)
{
	if(index < 0 || index > 5){
		return;
	}
	for(int i = 0; i < 6; ++i){ 
		if(i == index){
			continue;
		}else{
			if (m_mainbtn[i].GetStatus() != CButtonTriangle::Normal) {
				m_mainbtn[i].SetStatus(CButtonTriangle::Normal);
			}
		}
	} 
}

int CSWOTSystemView::SetCoordinate(CDC *pdc)
{
	int mapmode = pdc->SetMapMode(MM_LOMETRIC); 
	RECT rc;
	this->GetClientRect(&rc); 
	pdc->SetViewportOrg(rc.left /*+ m_logolen - m_logomenugap*/, rc.bottom);

	return mapmode;
}

void CSWOTSystemView::SetMenu( int index )
{
	if(m_mainbtn[index].GetStatus() == CButtonTriangle::SelectText){
		int itemcount = m_mainbtn[index].GetMenuItemCount();
		for(int i = 0; i < itemcount; ++i){
			m_viemenu.AddMenuItem(m_mainbtn[index].GetMenuString(i));
		}

		m_menustatus = index;
	}else{
		m_menustatus = MENUNULL;
	}
	RECT rc;
	GetClientRect(&rc);
	rc.right = m_logolen; 
	InvalidateRect(&rc);
}

void CSWOTSystemView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if( CChart::PROMOTION == m_chart.Hittest(ConvertPoint(point)) && m_menustatus == Promotion){ 
		m_hp = new CChart::HistogramParam;
		m_hp->count = 8;

		m_hp->height[0] = m_chart.GetBoxHeight()*15/16;
		m_hp->color[0] = RGB(233,178,130);
		m_hp->str[0] = "1.1";
		m_hp->height[1] = m_chart.GetBoxHeight()*7/16;
		m_hp->color[1] = RGB(237,191,150);
		m_hp->str[1] = "1.2";
		m_hp->height[2] = m_chart.GetBoxHeight()*11/16;
		m_hp->color[2] = RGB(233,178,130);
		m_hp->str[2] = "1.3";
		m_hp->height[3] = m_chart.GetBoxHeight()*1/16;
		m_hp->color[3] = RGB(237,191,150);
		m_hp->str[3] = "1.4";
		m_hp->height[4] = m_chart.GetBoxHeight()*6/16;
		m_hp->color[4] = RGB(233,178,130);
		m_hp->str[4] = "1.5";
		m_hp->height[5] = m_chart.GetBoxHeight()*10/16;
		m_hp->color[5] = RGB(237,191,150);
		m_hp->str[5] = "1.6";
		m_hp->height[6] = m_chart.GetBoxHeight()*9/16;
		m_hp->color[6] = RGB(233,178,130);
		m_hp->str[6] = "1.7";
		m_hp->height[7] = m_chart.GetBoxHeight()*10/16;
		m_hp->color[7] = RGB(237,191,150);
		m_hp->str[7] = "1.8";

		m_hp->title = m_chart.m_title;

		m_histroy.push_back(m_hp);
		m_hpindex  = m_histroy.size();
		InvalidateRectEx(m_chart.m_rectbox);
	}else{
	}
	CView::OnLButtonDblClk(nFlags, point);
}

void CSWOTSystemView::GetScale( CDC *dc )
{
	// pixels count
	int pagecx=dc->GetDeviceCaps(HORZRES);
	int pagecy=dc->GetDeviceCaps(VERTRES);
	int pagesx=dc->GetDeviceCaps(HORZSIZE);
	int pagesy=dc->GetDeviceCaps(VERTSIZE);

	m_scalex = ((double)(pagesx * 10)) / (double)(pagecx);
	m_scaley = ((double)(pagesy * 10)) / (double)(pagecy);
	// dpi
	m_dpix = dc->GetDeviceCaps(LOGPIXELSX);
	m_dpiy = dc->GetDeviceCaps(LOGPIXELSY);
	GetClientRect(&m_clientrect);
}

POINT CSWOTSystemView::ConvertPoint( POINT pt )
{ 
	int height = m_clientrect.bottom - m_clientrect.top;
	int width = m_clientrect.right - m_clientrect.left;
	int x = pt.x;
	int y = height - pt.y;

	POINT result;
	result.x = x * m_scalex;
	result.y = y * m_scaley;

	return result;
}

void CSWOTSystemView::InvalidateRectEx( RECT &rect )
{
	RECT rc = rect;
	int height = (m_clientrect.bottom - m_clientrect.top)*m_scaley;
	int width = rect.right - rect.left;
	rc.left /= m_scalex;
	rc.right /= m_scalex;
	rc.top = (height - rc.top)/m_scaley;
	rc.bottom  = (height - rc.bottom)/m_scaley;
	this->InvalidateRect(&rc); 
}

void CSWOTSystemView::RestChart()
{
	m_chart.SetTitle("");
	m_hp = new CChart::HistogramParam;
	m_hp->count = 0;
	m_hp->title = m_chart.m_title;
	m_histroy.push_back(m_hp);
	m_hpindex = m_histroy.size();
}

void CSWOTSystemView::OnPromotionAdvertising()
{ 
	m_menustatus = Promotion;
	m_viemenu.Clear();
	
	m_viemenu.AddMenuItem("1.7   ADVERTISING");
	m_viemenu.AddMenuItem("1.7.1 Brief");
	m_viemenu.AddMenuItem("1.7.2 Research");
	m_viemenu.AddMenuItem("1.7.3 Creative");
	m_viemenu.AddMenuItem("1.7.4 Media production");
	m_viemenu.AddMenuItem("1.7.5 Media placement");

	RECT rc;
	const int gap = 10;
	rc.left = gap;
	rc.right = rc.left + (m_logolen - m_logomenugap - gap * 2);
	rc.top = m_mainbtn[0].GetHeight()*2+m_topheight;
	rc.bottom = rc.top + m_viemenu.GetItemCount()*35;
	m_viemenu.SetRect(rc);

	m_hp = new CChart::HistogramParam;
	m_hp->color[0] = RGB(226,152, 88);
	m_hp->count = 1;
	m_hp->height[0] = m_chart.GetBoxHeight()*7/10;
	m_hp->title = "1.7 A D V E R T I S I N G";
	m_chart.SetTitle("1.7 A D V E R T I S I N G");
	m_histroy.push_back(m_hp);
	m_hpindex = m_histroy.size();
	Invalidate();
	this->SetFocus();
}

void CSWOTSystemView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	//SetRect();
}

RECT CSWOTSystemView::ConvertRect( RECT & rect )
{
	RECT result;
	int height = m_clientrect.bottom - m_clientrect.top;
	int width = m_clientrect.right - m_clientrect.left; 
	result.left = rect.left * m_scalex;
	result.right = rect.right * m_scalex;
	result.top = (height - rect.top) * m_scaley;
	result.bottom = (height - rect.bottom) * m_scaley;

	return result;
}

void CSWOTSystemView::SetRect()
{
	if(m_scalex < 0.0001 && m_scalex > -0.0001 && m_scaley < 0.0001 && m_scaley > -0.0001){
		return ;
	}
	RECT rect;
	GetClientRect(&rect);
	RECT chart, charttitle, pie, rectview;

	rectview = rect;
	rectview.left = rect.left + m_logolen;
	rectview.top = rect.top + m_mainbtn[0].GetHeight()*2;

	chart = rectview;
	pie = rectview;

	int chartgap = 140;
	int topgap = 30, sidegap = 30, charttitleheight = 30;
	chart.left += sidegap;
	chart.top += topgap + m_topheight;
	chart.right = rectview.left + (rectview.right - rectview.left)/2-sidegap+chartgap;
	chart.bottom -= charttitleheight;

	pie.left = chart.right + 20;
	pie.top += topgap + m_topheight;
	pie.right -= sidegap;
	//pie.bottom -= charttitleheight;

	if(chart.right - chart.left > chart.bottom - chart.top){
		chart.right = chart.left + chart.bottom - chart.top;
	}else{
		chart.bottom = chart.top + chart.right - chart.left;
	}
	charttitle = chart;
	charttitle.top = chart.bottom;
	charttitle.bottom = charttitle.top + charttitleheight;


	rect = ConvertRect(pie);
	m_pie.SetRect(rect);
	rect = ConvertRect(chart);
	m_chart.SetBoxRect(rect);
	rect = ConvertRect(charttitle);
	m_chart.SetTitleRect(rect);
}
