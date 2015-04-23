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
m_bytecapacity(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bytes.m_colors = NULL;
}

void CMy3dmodelingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_tips);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_outputfilepath);
	DDX_Control(pDX, IDC_EDIT_MNN, m_mnn);
	DDX_Control(pDX, IDC_EDIT_MD, m_md);
	DDX_Control(pDX, IDC_EDIT_MSA, m_msa);
	DDX_Control(pDX, IDC_EDIT_MAXA, m_maxa);
	DDX_Control(pDX, IDC_EDIT_MINA, m_mina);
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
	 HMODULE hModule = GetModuleHandle(NULL);
	char exefile[256] = {0};
	GetModuleFileName(hModule, exefile, 256);
	m_strexe = exefile;
	m_mnn.SetWindowText("100");
	m_md.SetWindowText("100");

	m_msa.SetWindowText("45");
	m_maxa.SetWindowText("120");
	m_mina.SetWindowText("10");

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
	if (m_bytecapacity < bytecount)
	{
		free(m_bytes.m_colors);
		m_bytes.m_colors = (unsigned char *)malloc(bytecount);
		m_bytecapacity = bytecount;
	}

	m_pointcount = bytecount/3;
	m_bytecount = m_pointcount* 3;

	for (int i = 0,j = 0;  i < m_bytecount; i+=2,j++)
	{ 
		hex[0] = strinput[i];
		hex[1] = strinput[i+1];
		if(hex[0] >= 'a' && hex[0] <='z'){
			hex[0] -= 'z' - 'Z';
		}
		if(hex[1] >= 'a' && hex[1] <='z'){
			hex[1] -= 'z' - 'Z';
		}
		hex[2] = 0; 
		m_bytes.m_colors[j] = m_str2byte[hex];
	}

	return 0;
}

void CMy3dmodelingDlg::ShowFormatColors()
{
	
	int charactercount = m_strrawinput.GetLength();
	CString strShowColors;
	for (int i = 0; i < charactercount; i+=2)
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
	//m_tips.SetWindowText("That is the key issue!!!");
	CString strfile;
	m_outputfilepath.GetWindowText(strfile);
	if (!strfile.IsEmpty()) {
		if(!m_bformat){
			OnBnClickedButtonFormat();
		}
		CString strmnn, strmd;
		m_mnn.GetWindowText(strmnn);
		m_md.GetWindowText(strmd);
		if(strmnn.IsEmpty()){
			strmnn = "100";
		}
		if(strmd.IsEmpty()){
			strmd = "100";
		}

		int count = strfile.ReverseFind('.');
		char opobjpath[256] = {0};
		memcpy(opobjpath, strfile.GetBuffer(), count);
		opobjpath[count] = '_'; opobjpath[count+1] = 'o'; opobjpath[count+2] = 'p'; opobjpath[count+3] = 's';
		opobjpath[count+4] = '.'; opobjpath[count+5] = 'o'; opobjpath[count+6] = 'b'; opobjpath[count+7] = 'j';
		WriteOBJFile(opobjpath);
		m_tips.SetWindowText("obj file (only points) generate successfully.");

		char pcdpath[256] = {0};
		memcpy(pcdpath, strfile.GetBuffer(), count);
		pcdpath[count] = '.'; pcdpath[count+1] = 'p'; pcdpath[count+2] = 'c'; pcdpath[count+3] = 'd';
		WritePCDFile(pcdpath);
		m_tips.SetWindowText("pcd file generate successfully.");

		CString strmsa, strmaxa, strmina;
		m_msa.GetWindowText(strmsa);
		m_maxa.GetWindowText(strmaxa);
		m_mina.GetWindowText(strmina);
		if(strmsa.IsEmpty()){strmsa = "45";};
		if(strmaxa.IsEmpty()){strmaxa = "120";};
		if(strmina.IsEmpty()){strmina = "10";}; 
		char vtkpath[256] = {0};
		memcpy(vtkpath, strfile.GetBuffer(), count);
		vtkpath[count] = '.'; vtkpath[count+1] = 'v'; vtkpath[count+2] = 't'; vtkpath[count+3] = 'k';
		char objpath[256] = {0};
		memcpy(objpath, strfile.GetBuffer(), count);
		objpath[count] = '.'; objpath[count+1] = 'o'; objpath[count+2] = 'b'; objpath[count+3] = 'j';
		char pcd2vtk[256] = {0};
		count = m_strexe.ReverseFind('\\');
		memcpy(pcd2vtk, m_strexe.GetBuffer(),count);
		CString pcd2vtkcmd = pcd2vtk+CString("\\pcd2vtk.exe ") + strmd + CString(" 50 ") + strmnn+" "+pcdpath + " " + vtkpath + " " + strmsa + " " + strmaxa + " " + strmina;
		system(pcd2vtkcmd.GetBuffer());
		m_tips.SetWindowText("vtk file generate successfully.");

		char vtk2obj[256] = {0};
		memcpy(vtk2obj, m_strexe.GetBuffer(),count);
		CString vtk2objcmd = vtk2obj+CString("\\vtk2obj.exe ")+CString(vtkpath)+CString(" ")+CString(objpath);
		system(vtk2objcmd);

		m_tips.SetWindowText("obj file generate successfully.");
		remove(pcdpath);
		remove(vtkpath);
		m_pointcount = 0;
		memset(m_bytes.m_colors, 0, m_bytecapacity);

		m_bformat = false;
	}
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

int CMy3dmodelingDlg::WritePCDFile( CString strfile )
{
	FILE * pcdfile = fopen(strfile.GetBuffer(), "w");
	char buffercomment[] = "# .PCD v.5 - Point Cloud Data file format\n";
	char buffercommentcopyright[] = "# generated by 3dmodeling software\n";
	char buffer[] = "VERSION .5\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n";
	fwrite(buffercomment, sizeof(char), sizeof(buffercomment)-1, pcdfile);
	fwrite(buffercommentcopyright, sizeof(char), sizeof(buffercommentcopyright)-1, pcdfile);
	fwrite(buffer, sizeof(char), sizeof(buffer)-1, pcdfile);
	char bufferwidth[64] = {0};
	sprintf(bufferwidth, "WIDTH %d\n", m_pointcount);
	fwrite(bufferwidth, sizeof(char), strlen(bufferwidth), pcdfile);
	char bufferheight[] = "HEIGHT 1\n";
	fwrite(bufferheight, sizeof(char), sizeof(bufferheight)-1, pcdfile);
	char bufferpointscount[64] = {0};
	sprintf(bufferpointscount, "POINTS %d\n", m_pointcount);
	fwrite(bufferpointscount, sizeof(char), strlen(bufferpointscount), pcdfile);
	char bufferdata[] = "DATA ascii\n";
	fwrite(bufferdata, sizeof(char), sizeof(bufferdata)-1, pcdfile);

	char bufferpoints[64];
	for(int i = 0; i < m_pointcount; ++i){ 
		memset(bufferpoints, 0, 64);
		sprintf(bufferpoints, "%d %d %d\n", m_bytes.m_colors[i], m_bytes.m_colors[i+1], m_bytes.m_colors[i+2]);
		fwrite(bufferpoints, sizeof(char), strlen(bufferpoints), pcdfile);
	}
	fflush(pcdfile);
	fclose(pcdfile);

	return 0;
}

int CMy3dmodelingDlg::WriteOBJFile( CString strfile )
{
	FILE * objfile = fopen(strfile.GetBuffer(), "w");
	char buffercomment[] = "####\n";
	fwrite(buffercomment, sizeof(char), sizeof(buffercomment)-1, objfile);
	char buffercommentcopyright[] = "# generated by 3dmodeling software\n";
	fwrite(buffercommentcopyright, sizeof(char), sizeof(buffercommentcopyright)-1, objfile);
	char bufferversion[] = "# OBJ dataFile simple version. File name: ";
	fwrite(bufferversion, sizeof(char), sizeof(bufferversion)-1, objfile);
	char filename[256] = {0};
	memcpy(filename, strfile.GetBuffer(), strfile.GetLength());
	filename[strfile.GetLength()] = '\n';
	fwrite(filename, sizeof(char), strfile.GetLength()+1, objfile);

	char buffervertices[64] = {0};
	sprintf(buffervertices, "# Vertices %d\n", m_pointcount);
	fwrite(buffervertices, sizeof(char), strlen(buffervertices), objfile);
	char bufferleft[] = "# Faces: 0\n#### \n# List of Vertices, with (x,y,z) coordinates, w is optional.\n";
	fwrite(bufferleft, sizeof(char), sizeof(bufferleft)-1, objfile);
	
	char bufferpoints[64];
	for(int i = 0; i < m_pointcount; ++i){ 
		memset(bufferpoints, 0, 64);
		sprintf(bufferpoints, "v %d %d %d\n", m_bytes.m_colors[i], m_bytes.m_colors[i+1], m_bytes.m_colors[i+2]);
		fwrite(bufferpoints, sizeof(char), strlen(bufferpoints), objfile);
	}
	fflush(objfile);
	fclose(objfile);
	

	return 0;
}
