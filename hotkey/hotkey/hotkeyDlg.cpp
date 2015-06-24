// hotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hotkey.h"
#include "hotkeyDlg.h"
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+5001
#define ID_COPY WM_USER+5002
#define ID_PASTE WM_USER+5003
#define ID_CALC WM_USER+5004


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// ChotkeyDlg dialog




ChotkeyDlg::ChotkeyDlg(CWnd* pParent /*=NULL*/)
: CDialog(ChotkeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_YOUREARNINGS, m_yourearnings);
	DDX_Control(pDX, IDC_EDIT_BTC, m_billedtoclient);
	DDX_Control(pDX, IDC_EDIT_BIDSCOUNT, m_bidscount);
	DDX_Control(pDX, IDC_EDIT_YES, m_yourearnings2);
	DDX_Control(pDX, IDC_EDIT_HB, m_highbids);
	DDX_Control(pDX, IDC_EDIT_LB, m_lowbids);
	DDX_Control(pDX, IDC_EDIT_AVGBIDS, m_avgbids);
	DDX_Control(pDX, IDC_EDIT_TOAVG, m_theothers);
}

BEGIN_MESSAGE_MAP(ChotkeyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification, "hotkey", IDR_MENU_TRAYICON)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_COMMAND(ID_HOTKEY_EXIT, &ChotkeyDlg::OnHotkeyExit)
	ON_BN_CLICKED(IDOK, &ChotkeyDlg::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_HOTKEY()
	ON_EN_CHANGE(IDC_EDIT_HB, &ChotkeyDlg::OnEnChangeEditHb)
	ON_BN_CLICKED(IDC_BUTTON_BTC, &ChotkeyDlg::OnBnClickedButtonBtc)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &ChotkeyDlg::OnBnClickedButtonCalc)
END_MESSAGE_MAP()


// ChotkeyDlg message handlers

BOOL ChotkeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_hCheck = AfxGetApp()->LoadIcon(IDI_ICON_CHECK); 
	m_hUncheck = AfxGetApp()->LoadIcon(IDI_ICON_UNCHECK); 
	m_hDollor = AfxGetApp()->LoadIcon(IDI_ICON_DOLLOR);
	m_bcheck = false;
	//m_trayicon.Create(this, WM_ICON_NOTIFY, "Paste with line break",m_hUncheck,IDR_MENU_TRAYICON);
	m_trayicon.Create(this, WM_ICON_NOTIFY, "elance's calc",m_hDollor,IDR_MENU_TRAYICON);
//	if(!::RegisterHotKey(this->m_hWnd,ID_COPY,MOD_CONTROL | MOD_ALT,'C')){
//		MessageBox("ctrl+alt+C Register failed");
//	}
//	if(!::RegisterHotKey(this->m_hWnd,ID_PASTE,MOD_CONTROL | MOD_ALT,'V')){
//		MessageBox("ctrl+alt+V Register failed");
//	}
	if(!::RegisterHotKey(this->m_hWnd,ID_CALC,MOD_CONTROL | MOD_ALT,'X')){
		MessageBox("ctrl+alt+X Register failed");
		return FALSE;
	}
	m_bshow = false;
	
	//::RegisterHotKey(this->GetSafeHwnd(),ID_PASTE,MOD_CONTROL|MOD_ALT,'v');
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ChotkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ChotkeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ChotkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT ChotkeyDlg::OnTrayNotification( WPARAM wParam,LPARAM lParam )
{ 
	if(LOWORD(lParam) == WM_LBUTTONDOWN) 
	{
//		m_bcheck = !m_bcheck;
//		if(m_bcheck){
//			m_trayicon.SetIcon(m_hCheck); 
//			m_trayicon.SetTooltipText("Paste without line break");
//		}else{
//			m_trayicon.SetIcon(m_hUncheck);
//			m_trayicon.SetTooltipText("Paste with line break");
//		}
		this->ShowWindow(SW_NORMAL);
		m_bshow = true;

	}
	return m_trayicon.OnTrayNotification(wParam, lParam);
}

void ChotkeyDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_trayicon.ShowIcon();
	ShowWindow(SW_HIDE);
	return;
	//CDialog::OnClose();
}

void ChotkeyDlg::OnHotkeyExit()
{
	// TODO: 在此添加命令处理程序代码
//	UnregisterHotKey(this->m_hWnd, ID_COPY);
//	UnregisterHotKey(this->m_hWnd, ID_PASTE);
	UnregisterHotKey(this->m_hWnd, ID_CALC);
	OnOK();
}

void ChotkeyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

int ChotkeyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void ChotkeyDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnNcPaint()
//	static int i = 2;
//	if(i > 0)
//	{
//		i --;
//		ShowWindow(SW_HIDE);
//	}
//	else
		CDialog::OnNcPaint();
}


void ChotkeyDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId == ID_COPY && m_bcheck){
		keybd_event(VkKeyScan('C'),0xae, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
		keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release

		keybd_event(VK_CONTROL,0x9d,0 , 0); // Ctrl Press
		keybd_event(VkKeyScan('C'),0xae,0 , 0); // 'C' Press
		keybd_event(VkKeyScan('C'),0xae, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
	}else if(nHotKeyId == ID_PASTE && m_bcheck){
		keybd_event(VkKeyScan('V'),0xaf, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
		keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release
		CString text = GetClipboardText();
		if(!text.IsEmpty()){
			CString textwithoutlinebreak = ClearLinebreak(text);
			SetClipboardText(textwithoutlinebreak);
		}

		keybd_event(VK_CONTROL,0x9d,0 , 0); // Ctrl Press
		keybd_event(VkKeyScan('V'),0xaf,0 , 0); // 'C' Press
		keybd_event(VkKeyScan('V'),0xaf, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
	}else if (nHotKeyId == ID_CALC){
		if(!m_bshow){
			this->ShowWindow(SW_NORMAL);
			m_bshow = true;
		}else{
			this->ShowWindow(SW_HIDE);
			m_bshow = false;
		}
	}

	//CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

CString ChotkeyDlg::GetClipboardText()
{ 
	// Try opening the clipboard
	if (!OpenClipboard()){
		return "";
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == NULL){
		return "";
	}
	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>( GlobalLock(hData) );
	if (pszText == NULL){
		return "";
	}
	// Save text in a string class instance
	CString text( pszText );

	// Release the lock
	GlobalUnlock( hData );

	// Release the clipboard
	CloseClipboard();

	return text;
}

void ChotkeyDlg::SetClipboardText( CString text )
{
	if ( !OpenClipboard() )
	{
		AfxMessageBox( _T("Cannot open the Clipboard") );
		return;
	}
	// Remove the current Clipboard contents 
	if( !EmptyClipboard() )
	{
		AfxMessageBox( _T("Cannot empty the Clipboard") );
		return;
	}
	// Get the currently selected data
	int textlen = strlen(text.GetBuffer());
	char * temp = (char *)malloc(textlen+3);
	memcpy(temp, text.GetBuffer(), textlen);
	temp[textlen] = '\r';
	temp[textlen+1] = '\n';
	temp[textlen+2] = 0;
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, textlen+3);
	strcpy_s((char*)hGlob, textlen+3,temp); 
	free(temp);
	// For the appropriate data formats... 
	if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
	{
		CString msg;
		msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		AfxMessageBox( msg );
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}

CString ChotkeyDlg::ClearLinebreak( CString text ){
	CString strwithoutlinebreak;
	int textlen = text.GetLength();
	for (int i = 0; i < textlen; ++i){
		if (text[i] != '\r' && text[i] != '\n') {
			strwithoutlinebreak += text[i];
		}
	}
	return strwithoutlinebreak;
}

void ChotkeyDlg::OnEnChangeEditHb()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void ChotkeyDlg::OnBnClickedButtonBtc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strmyearnings,strbilledtoclient;
	m_yourearnings.GetWindowText(strmyearnings);
	m_billedtoclient.GetWindowText(strbilledtoclient);
	strmyearnings.Trim();
	strbilledtoclient.Trim();
	if(!strmyearnings.IsEmpty()){
		strbilledtoclient.Format("%0.2f", atof(strmyearnings.GetBuffer())/0.9125);
		m_billedtoclient.SetWindowText(strbilledtoclient);
	}else if(!strbilledtoclient.IsEmpty()){
		strmyearnings.Format("%0.2f", atof(strbilledtoclient) - atof(strbilledtoclient.GetBuffer())*0.0875);
		m_yourearnings.SetWindowText(strmyearnings);
	}
}

void ChotkeyDlg::OnBnClickedButtonCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strbidscount,stryourearnings,strhighbids,strlowbids,stravgbids,strresult;
	m_bidscount.GetWindowText(strbidscount);
	m_yourearnings2.GetWindowText(stryourearnings);
	m_highbids.GetWindowText(strhighbids);
	m_lowbids.GetWindowText(strlowbids);
	m_avgbids.GetWindowText(stravgbids);
	if(strbidscount.IsEmpty() || stryourearnings.IsEmpty() || strhighbids.IsEmpty() ||
		strlowbids.IsEmpty() || stravgbids.IsEmpty()){
			return;
	}
	int bidscoount = atoi(strbidscount);
	float yourearnings, higbids,lowbids,avgbids;
	yourearnings = atof(stryourearnings.GetBuffer());
	higbids = atof(strhighbids.GetBuffer());
	lowbids = atof(strlowbids.GetBuffer());
	avgbids = atof(stravgbids.GetBuffer());

	float total = avgbids * bidscoount;
	float avg ;
	if(abs(higbids - yourearnings/0.9125) < 1.0 ){
		avg = (total - higbids - lowbids )/(bidscoount-2);
	}else{
		avg = (total - higbids - lowbids - yourearnings/0.9125)/(bidscoount-3);
	}
	
	strresult.Format("%0.2f", avg);
	m_theothers.SetWindowText(strresult);
}
