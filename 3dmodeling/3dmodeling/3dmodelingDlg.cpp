// 3dmodelingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3dmodeling.h"
#include "3dmodelingDlg.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMy3dmodelingDlg dialog




CMy3dmodelingDlg::CMy3dmodelingDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMy3dmodelingDlg::IDD, pParent),
m_bformat(false),
m_bytecount(0),
m_colors(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3dmodelingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_tips);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_outputfilepath);
}

BEGIN_MESSAGE_MAP(CMy3dmodelingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FORMAT, &CMy3dmodelingDlg::OnBnClickedButtonFormat)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CMy3dmodelingDlg::OnBnClickedButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_FILEPATH, &CMy3dmodelingDlg::OnBnClickedButtonFilepath)
END_MESSAGE_MAP()


// CMy3dmodelingDlg message handlers

const char* g_byteliterals[] = {"00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
                                "10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
                                "20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
                                "30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
                                "40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
                                "50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
                                "60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
                                "70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
                                "80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
                                "90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
                                "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
                                "B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
                                "C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
                                "D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
                                "E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
                                "F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF"};

BOOL CMy3dmodelingDlg::OnInitDialog()
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
	for (int i = 0; i <= 255; ++i)
	{
		m_str2byte[g_byteliterals[i]] = i;
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3dmodelingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy3dmodelingDlg::OnPaint()
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
HCURSOR CMy3dmodelingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy3dmodelingDlg::OnBnClickedButtonFormat()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strinput; 
	m_input.GetWindowText(strinput);
	int inputstatus = IsIllegal(strinput);
	switch(inputstatus){
		case INPUT_UNAVAILABLECHARACTER:
			m_bformat = false;
			m_tips.SetWindowText("There are illegal characters in your input.Please check it.");
			break;
		case INPUT_NOTMATCH:
			m_bformat = false;
			m_tips.SetWindowText("It is not complete inputs.Please check it.");
			break;
		case INPUT_OK:
			m_bformat = true;
			FormatRawColors(strinput);
			ShowFormatColors();
			FillBytes(m_strrawinput);
			m_tips.SetWindowText("");
			break;
		default:
			break;
	}
}

int CMy3dmodelingDlg::IsIllegal( CString strinput)
{
	int count = strinput.GetLength();
	int charactercount = 0;
	for(int i = 0; i < count; ++i){
		if ((strinput[i] <= '9'  && strinput[i] >= '0') ||
			(strinput[i] <='f' && strinput[i] >= 'a' ||
			(strinput[i] <='F' && strinput[i] >= 'A')))
		{ 
			charactercount++;
		}else{
			if(strinput[i] != ' ' && 
			   strinput[i] != '\t' &&
		       strinput[i] != '\r' &&
			   strinput[i] != '\n'){
			   return INPUT_UNAVAILABLECHARACTER;
			}
		}
	}

	if (charactercount % 2 == 1)
	{
		return INPUT_NOTMATCH;
	}

	return INPUT_OK;

}

int CMy3dmodelingDlg::FillBytes( CString strinput )
{
	// strinput need no space
	char hex[3];
	int count = strinput.GetLength();
	assert(count%2==0);
	int bytecount = count/2;
	if (m_bytecount < bytecount)
	{
		free(m_colors);
		m_colors = (unsigned char *)malloc(bytecount);
		m_bytecount = bytecount;
	}
	for (int i = 0,j = 0;  i < count; i+=2,j++)
	{ 
		hex[0] = strinput[i];
		hex[1] = strinput[i+1];
		hex[2] = 0; 
		m_colors[j] = m_str2byte[hex];
	}

	return 0;
}

void CMy3dmodelingDlg::ShowFormatColors()
{
	
	int charactercount = m_strrawinput.GetLength();
	CString strShowColors;
	for (int i = 0; i < charactercount/2; ++i)
	{
		strShowColors+=m_strrawinput[i];
		strShowColors+=m_strrawinput[i+1];
		strShowColors+=" ";
	}

	m_input.SetWindowText(strShowColors);
}

int CMy3dmodelingDlg::FormatRawColors( CString strinput )
{
	m_strrawinput.Empty();
	int count = strinput.GetLength();
	for(int i = 0; i < count; ++i){
		if(strinput[i] != ' ' && 
		   strinput[i] != '\n' && 
		   strinput[i] != '\r' && 
		   strinput[i] != '\t'){
			m_strrawinput += strinput[i];
		}
	}
	
	return 0;
}

void CMy3dmodelingDlg::OnBnClickedButtonGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_tips.SetWindowText("That is the key issue!!!");
}

void CMy3dmodelingDlg::OnBnClickedButtonFilepath()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilters[]= _T("OBJ Files (*.obj)|*obj|C4D Files (*.c4d)|*.c4d|All Files (*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T(""), _T("untitled.obj"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	fileDlg.GetOFN().lpstrTitle = "save 3d modeling file";
	if(fileDlg.DoModal() == IDOK)
	{
		CString strOutFileName = fileDlg.GetPathName();
		m_outputfilepath.SetWindowText(strOutFileName);
	}
}
