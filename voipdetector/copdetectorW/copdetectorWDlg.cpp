// copdetectorWDlg.cpp : implementation file
//

#include "stdafx.h"
#include "copdetectorW.h"
#include "copdetectorWDlg.h"
#include "CaptureInterfaces.h"
#include "sipprotocol.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+5001

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


// CcopdetectorWDlg dialog




CcopdetectorWDlg::CcopdetectorWDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcopdetectorWDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcopdetectorWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcopdetectorWDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification, "voip", IDR_MENU_TRAY)
	//}}AFX_MSG_MAP
	ON_WM_NCPAINT()
	ON_COMMAND(ID_VOIPDETECTOR_EXIT, &CcopdetectorWDlg::OnVoipdetectorExit)
END_MESSAGE_MAP()


// CcopdetectorWDlg message handlers

BOOL CcopdetectorWDlg::OnInitDialog()
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
	//TRAYICON
	m_hIconPhone = AfxGetApp()->LoadIcon(IDI_ICON_PHONE); 
	m_trayicon.Create(this, WM_ICON_NOTIFY, "voip detector",m_hIconPhone,IDR_MENU_TRAY);
	//TRAYICON
	m_pcap = voippcap_create();
	CString strdev = CreateCaptureInterfaceDialog();
	if (strdev.IsEmpty())
	{
		voippcap_destroy(m_pcap);
		MessageBox("Since the net is not selected.Program will exit.","Tips");
		exit(1);
	}
	CString notify;
	notify = "Listening on "+strdev;
	m_trayicon.SetTooltipText(notify);
	//::SendMessage(m_trayicon.GetNotificationWnd()->m_hWnd,WM_ICON_NOTIFY,,512);
	m_packethandler = sipprotocol_packet_handler;

	DWORD tid;
	m_hthread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)CcopdetectorWDlg::capturenet,this,0,&tid);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcopdetectorWDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcopdetectorWDlg::OnPaint()
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
HCURSOR CcopdetectorWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CcopdetectorWDlg::CreateCaptureInterfaceDialog()
{ 
	char errbuf[PCAP_ERRBUF_SIZE] = {0};
	std::vector<std::string> desc;
	std::vector<std::string> devs = voippcap_getalldevs(m_pcap,desc,errbuf);
	if(devs.size() == 1){
		return devs[0].c_str();
	}else if(devs.size() == 0){
		return "";
	}
	CCaptureInterfaces dlgCaptureInterfaces; 
	std::vector<std::string>::iterator it;
	int i = 0;
	for (it = devs.begin(); it != devs.end(); ++it) {
		dlgCaptureInterfaces.AddInterface(desc[i]);
		i++;
	}
	dlgCaptureInterfaces.DoModal();

	m_index = dlgCaptureInterfaces.GetDevIndex();
	if(m_index != -1){
		return devs[m_index].c_str();
	}

	return "";
}

LRESULT CcopdetectorWDlg::OnTrayNotification( WPARAM wParam,LPARAM lParam )
{
	if(LOWORD(lParam) == WM_LBUTTONDOWN) 
	{
	}
	return m_trayicon.OnTrayNotification(wParam, lParam);
}

void CcopdetectorWDlg::OnNcPaint()
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

void CcopdetectorWDlg::OnVoipdetectorExit()
{
	// TODO: 在此添加命令处理程序代码
	OnOK();
}

void CcopdetectorWDlg::capturenet( void * param)
{
	CcopdetectorWDlg *dlg = (CcopdetectorWDlg *)param;
	char errbuf[PCAP_ERRBUF_SIZE];
	voippcap_capture(dlg->m_pcap,dlg->m_index,dlg->m_packethandler,errbuf);
}
