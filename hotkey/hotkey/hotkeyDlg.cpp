// hotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hotkey.h"
#include "hotkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+5001
#define ID_COPY WM_USER+5002
#define ID_PASTE WM_USER+5003


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
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TRAY); 
	m_trayicon.Create(this, WM_ICON_NOTIFY, "HOTKEY",hIcon,IDR_MENU_TRAYICON);
	if(!::RegisterHotKey(this->m_hWnd,ID_COPY,MOD_CONTROL | MOD_ALT,'C')){
		MessageBox("ctrl+alt+C Register failed");
	}
	if(!::RegisterHotKey(this->m_hWnd,ID_PASTE,MOD_CONTROL | MOD_ALT,'V')){
		MessageBox("ctrl+alt+V Register failed");
	}
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
	///	if(LOWORD(lParam) == WM_LBUTTONDBLCLK) 
	///	{
	///		ShowWindow(SW_SHOW);
	///	}
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
	UnregisterHotKey(this->m_hWnd, ID_COPY);
	UnregisterHotKey(this->m_hWnd, ID_PASTE);
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
	static int i = 2;
	if(i > 0)
	{
		i --;
		ShowWindow(SW_HIDE);
	}
	else
		CDialog::OnNcPaint();
}


void ChotkeyDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId == ID_COPY){
		keybd_event(VkKeyScan('C'),0xae, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
		keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release

		keybd_event(VK_CONTROL,0x9d,0 , 0); // Ctrl Press
		keybd_event(VkKeyScan('C'),0xae,0 , 0); // 'C' Press
		keybd_event(VkKeyScan('C'),0xae, KEYEVENTF_KEYUP,0); // 'C' Release
		keybd_event(VK_CONTROL,0x9d,KEYEVENTF_KEYUP,0); // Ctrl Release
	}else if(nHotKeyId == ID_PASTE){
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
