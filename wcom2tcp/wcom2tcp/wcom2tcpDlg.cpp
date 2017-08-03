// wcom2tcpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wcom2tcp.h"
#include "wcom2tcpDlg.h"
#include "conf.h"
#include "serial.h"
#include "socket.h"
#include "protocol_common.h"
#include "event_hub.h"
#include "protocol_tt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+5001

#define SERIAL_PREFIX "\\\\.\\"
#define HELP_FILE "./readme.txt"
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
extern struct conf g_conf;

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
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


    // Cwcom2tcpDlg 对话框




Cwcom2tcpDlg::Cwcom2tcpDlg(CWnd* pParent /*=NULL*/)
: CDialog(Cwcom2tcpDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TRANSMISSION);
}

void Cwcom2tcpDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cwcom2tcpDlg, CDialog)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification, "hotkey", IDR_MENU_TRAY)
    //}}AFX_MSG_MAP
ON_BN_CLICKED(ID_BUTTON_OPEN_SERIAL, &Cwcom2tcpDlg::OnBnClickedButtonOpenSerial)
ON_BN_CLICKED(ID_BUTTON_CONNECT, &Cwcom2tcpDlg::OnBnClickedButtonConnect)
ON_BN_CLICKED(IDOK, &Cwcom2tcpDlg::OnBnClickedOk)
ON_BN_CLICKED(ID_BUTTON_BREAK, &Cwcom2tcpDlg::OnBnClickedButtonBreak)
ON_BN_CLICKED(IDC_BUTTON_GEN_ID_AND_KEY3, &Cwcom2tcpDlg::OnBnClickedButtonGenIdAndKey3)
ON_STN_CLICKED(IDC_STATIC_TIPS, &Cwcom2tcpDlg::OnStnClickedStaticTips)
ON_COMMAND(ID_TRAYICON_QUIT, &Cwcom2tcpDlg::OnTrayiconQuit)
ON_BN_CLICKED(ID_BUTTON_HELP, &Cwcom2tcpDlg::OnBnClickedButtonHelp)
ON_BN_CLICKED(ID_BUTTON_COPY_KEY, &Cwcom2tcpDlg::OnBnClickedButtonCopyKey)
ON_BN_CLICKED(ID_BUTTON_QUERY, &Cwcom2tcpDlg::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


    // Cwcom2tcpDlg 消息处理程序

BOOL Cwcom2tcpDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    conf_load();
    Init();
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TRANSMISSION);
    m_trayicon.Create(this, WM_ICON_NOTIFY, "透传服务器",m_hIcon,IDR_MENU_TRAY);


    WSADATA wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);

    m_socket = NULL;
    m_serial = NULL;

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cwcom2tcpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cwcom2tcpDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cwcom2tcpDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void Cwcom2tcpDlg::OnBnClickedButtonGenIdAndKey()
{
    // TODO: Add your control notification handler code here
}

void Cwcom2tcpDlg::OnBnClickedButtonOpenSerial()
{
    // TODO: Add your control notification handler code here
    CString serial;
    CString serial_save;
    GetDlgItemText(IDC_COMBO_SERIAL, serial_save); 
    serial = SERIAL_PREFIX+serial_save;
    ComParams comParms;
    if (m_serial == NULL){
        m_serial = OpenC0C(serial.GetBuffer(), comParms);
        if (m_serial == INVALID_HANDLE_VALUE){
            SetDlgItemText(IDC_STATIC_TIPS, "打开串口失败");
        }else{
            SetDlgItemText(IDC_STATIC_TIPS, "打开串口成功"); 
        }
    }
    conf_update(SERIAL, serial_save.GetBuffer());
    serial_save.ReleaseBuffer();
    serial.ReleaseBuffer();
}

void Cwcom2tcpDlg::OnBnClickedButtonConnect()
{
	OnBnClickedButtonBreak();
	if (CheckInputBlank()){
		return;
	}
    // TODO: Add your control notification handler code here
    CString ip_addr, ip_port;
    GetDlgItemText(IDC_IP_ADDR,ip_addr);
    GetDlgItemText(IDC_IP_PORT, ip_port);
    if(m_socket == NULL){
        m_socket  = Connect(NULL, ip_addr.GetBuffer(), ip_port.GetBuffer());
        if (m_socket){ 
            SetDlgItemText(IDC_STATIC_TIPS, "连接服务器成功");
            conf_update(IP, ip_addr.GetBuffer());
            conf_update(PORT, ip_port.GetBuffer());
            if (0 == CheckRegister()){ 
                SetDlgItemText(IDC_STATIC_TIPS, "配对路由器成功");
                DWORD thread_id;
                HANDLE m_thread = CreateThread(NULL,
                    0, 
                    (LPTHREAD_START_ROUTINE)Cwcom2tcpDlg::DoRoute,
                    this,
                    0,
                    &thread_id);
            }else{ 
                SetDlgItemText(IDC_STATIC_TIPS, "配对路由器失败");
            }
        }
        ip_addr.ReleaseBuffer();
        ip_port.ReleaseBuffer();
    }
}

void Cwcom2tcpDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    m_trayicon.ShowIcon();
    ShowWindow(SW_HIDE);
    return;
}

void Cwcom2tcpDlg::OnBnClickedButtonBreak()
{
    // TODO: Add your control notification handler code here
    Disconnect(m_socket);
    m_socket = NULL;
    if (m_thread != 0) {
        WaitForSingleObject(m_thread, INFINITE);
        //	CloseHandle(m_thread);
    }
    SetDlgItemText(IDC_STATIC_TIPS, "断开服务器");

}

double GetRandomNumber(double start, double range){
   // srand(time(0));
 //   return double(rand()) / double(RAND_MAX) * range + start;
	return 100;
}

void Cwcom2tcpDlg::OnBnClickedButtonGenIdAndKey3()
{
    // TODO: Add your control notification handler code here
    //	CTime cur_time = CTime::GetCurrentTime();
    m_id = GetRandomNumber(10000000, 10000000);
    m_key = GetRandomNumber(10500000, 10000000);

    CString s_id;
    s_id.Format("%lld", m_id);
    CString s_key;
    s_key.Format("%d", m_key);

    SetDlgItemText(IDC_EDIT_CLIENTID, s_id);
    SetDlgItemText(IDC_EDIT_CLIENT_KEY2, s_key);
}

int Cwcom2tcpDlg::CheckRegister()
{
    CString str_id,str_key;
    GetDlgItemText(IDC_EDIT_CLIENTID, str_id);
    GetDlgItemText(IDC_EDIT_CLIENT_KEY2, str_key);

    struct protocol_register reg;
    memset(&reg, 0, sizeof(struct protocol_register));
    reg.id = _atoi64(str_id.GetBuffer());
    reg.key = atoi(str_key.GetBuffer());
    char protocol_reg[64] = {0};
    int len = encode_protocol_register((unsigned char*)protocol_reg, &reg); 
    int iResult = send(m_socket, protocol_reg, len, 0);
    if (iResult != SOCKET_ERROR) {
        unsigned char recvbuf[1024];
        int recvbuflen = 1024;
        iResult = 0;
        do{
            iResult += recv(m_socket, (char *)recvbuf, recvbuflen, 0);
            int nError=WSAGetLastError();
            if (nError==SOCKET_ERROR){
                wprintf(L"send failed with error: %d\n", WSAGetLastError());
            }
        }while(iResult < PROTOCOL_TT_FEEDBACK_LEN);

        return parse_tt_feedback((unsigned char *)recvbuf);
    } 

    wprintf(L"send failed with error: %d\n", WSAGetLastError());
    return 1;
}

void Cwcom2tcpDlg::DoRoute(void * p)
{
    Cwcom2tcpDlg * pp = (Cwcom2tcpDlg *)p;
    TTProtocol * proto = new TTProtocol(10, 10);
    proto->SetID(pp->m_id);
    pp->SetDlgItemText(IDC_STATIC_TIPS, "透传通道已建立，请启动PLC客户端");
    InOut(pp->m_serial, pp->m_socket, *proto, true);
}

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
std::vector<CString> QueryKey(HKEY hKey) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 

    BYTE achValueV[MAX_VALUE_NAME]; 
    DWORD cchValueV = MAX_VALUE_NAME; 
 
    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 
 
    // Enumerate the key values. 
    std::vector<CString> comms;

    if (cValues) 
    {
        printf( "\nNumber of values: %d\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            achValueV[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                achValueV,
                &cchValueV);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                comms.push_back(CString(achValueV));
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
            } 
        }
    }

    return comms;
}

void Cwcom2tcpDlg::Init()
{ 
    CComboBox * comboCom = (CComboBox*)GetDlgItem(IDC_COMBO_SERIAL);
    comboCom->SetWindowText(g_conf.serial);
    CIPAddressCtrl * ipcntrl = (CIPAddressCtrl *)GetDlgItem(IDC_IP_ADDR);
    ipcntrl->SetWindowText(g_conf.ip);
    CEdit * portcntrl =  (CEdit *)GetDlgItem(IDC_IP_PORT);
    portcntrl->SetWindowText(g_conf.port);

    HKEY hTestKey;
    if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
            TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
            0,
            KEY_READ,
            &hTestKey) == ERROR_SUCCESS
      ) {
        m_comms = QueryKey(hTestKey);
    }

    RegCloseKey(hTestKey);
	CComboBox * combo = (CComboBox*)GetDlgItem(IDC_COMBO_SERIAL);

	std::vector<CString>::iterator pos = m_comms.begin();
	for(;pos != m_comms.end(); pos++){
		combo->AddString(*pos); 
	}

	m_dlg_query = new CQueryDlg();
	m_dlg_query->Create(IDD_DIALOG_QUERY);
}

void Cwcom2tcpDlg::OnStnClickedStaticTips()
{
    // TODO: Add your control notification handler code here
}

LRESULT Cwcom2tcpDlg::OnTrayNotification( WPARAM wParam,LPARAM lParam )
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
    }
    return m_trayicon.OnTrayNotification(wParam, lParam);

}

void Cwcom2tcpDlg::OnClose()
{
    m_trayicon.ShowIcon();
    ShowWindow(SW_HIDE);
    return;
}

void Cwcom2tcpDlg::OnTrayiconQuit()
{
    // TODO: Add your command handler code here
    if(m_socket){
        Disconnect(m_socket);
    }
    if (m_serial) {
        CloseHandle(m_serial);
    }
    WSACleanup();
    OnOK();
}

void Cwcom2tcpDlg::OnCancel()
{ 
    m_trayicon.ShowIcon();
    ShowWindow(SW_HIDE);
    return;
}


void Cwcom2tcpDlg::OnBnClickedButtonHelp()
{
    // TODO: Add your control notification handler code here
    ShellExecute(NULL,"open","NOTEPAD.EXE",HELP_FILE,NULL,SW_SHOWNORMAL);
}

bool Cwcom2tcpDlg::SetClipboardText( CString text )
{
    if ( !OpenClipboard() )
    {
        SetDlgItemText(IDC_STATIC_TIPS, "复制失败");
        return false;
    }
    // Remove the current Clipboard contents 
    if( !EmptyClipboard() )
    {
        SetDlgItemText(IDC_STATIC_TIPS, "复制失败");
        return false;
    }
    // Get the currently selected data
    int textlen = strlen(text.GetBuffer());
    char * temp = (char *)malloc(textlen+3);
    memcpy(temp, text.GetBuffer(), textlen);
    temp[textlen] = 0;
    ///temp[textlen] = '\r';
    ///temp[textlen+1] = '\n';
    ///temp[textlen+2] = 0;
    HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, textlen+1);
    strcpy_s((char*)hGlob, textlen+1,temp); 
    free(temp);
    // For the appropriate data formats... 
    if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
    {
        CString msg;
        SetDlgItemText(IDC_STATIC_TIPS, "复制失败");
        CloseClipboard();
        GlobalFree(hGlob);
        return false;
    }
    CloseClipboard();

    return true;
}

void Cwcom2tcpDlg::OnBnClickedButtonCopyId()
{
    // TODO: Add your control notification handler code here
    CString clientid;
    GetDlgItemText(IDC_EDIT_CLIENTID, clientid);
    if(SetClipboardText(clientid)){
        SetDlgItemText(IDC_STATIC_TIPS, "已复制到剪切板");
    }else{
        SetDlgItemText(IDC_STATIC_TIPS, "复制失败");
    }

}

void Cwcom2tcpDlg::OnBnClickedButtonCopyKey()
{
    // TODO: Add your control notification handler code here
    CString clientkey;
    GetDlgItemText(IDC_EDIT_CLIENT_KEY2, clientkey);
    if(SetClipboardText(clientkey)){
        SetDlgItemText(IDC_STATIC_TIPS, "已复制到剪切板");
    }else{
        SetDlgItemText(IDC_STATIC_TIPS, "复制失败");
    }
}

bool Cwcom2tcpDlg::CheckInputBlank()
{ 
	CString strClientID;
	CString strClientKey;
	GetDlgItemText(IDC_EDIT_CLIENTID, strClientID);
	GetDlgItemText(IDC_EDIT_CLIENT_KEY2, strClientKey); 
	if(strClientID.IsEmpty()){
		SetDlgItemText(IDC_STATIC_TIPS, "请输入透传客户端ID");
		((CEdit *)(GetDlgItem(IDC_EDIT_CLIENTID)))->SetFocus();

		return true;
	}else if (strClientKey.IsEmpty()){
		SetDlgItemText(IDC_STATIC_TIPS, "请输入透传客户端Key");
		((CEdit*)(GetDlgItem(IDC_EDIT_CLIENT_KEY2)))->SetFocus();
		
		return true;
	}

	return false;
}

void Cwcom2tcpDlg::OnBnClickedButtonQuery()
{
	// TODO: Add your control notification handler code here
	this->m_dlg_query->ShowWindow(SW_NORMAL);
}
