// QueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wcom2tcp.h"
#include "QueryDlg.h"
#include "conf.h"
#include <afxinet.h>


extern struct conf g_conf;
// CQueryDlg dialog
#define QUERY_ALL_ROUTER "/plc/query_all_routers"
#define QUERY_ALL_WIN "/plc/query_all_win_client"
#define QUERY_ROUTER "/plc/query_router"
#define QUERY_WIN "/plc/query_win_client"
#define QUERY_ID "id"

IMPLEMENT_DYNAMIC(CQueryDlg, CDialog)

CQueryDlg::CQueryDlg(CWnd* pParent /*=NULL*/)
: CDialog(CQueryDlg::IDD, pParent)
{

}

CQueryDlg::~CQueryDlg()
{
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQueryDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_ALL_WIN, &CQueryDlg::OnBnClickedButtonQueryAllWin)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_ALL_ROUTER, &CQueryDlg::OnBnClickedButtonQueryAllRouter)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_QUERY_ROUTER, &CQueryDlg::OnBnClickedButtonQueryRouter)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_WIN, &CQueryDlg::OnBnClickedButtonQueryWin)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CQueryDlg message handlers

void CQueryDlg::OnBnClickedButtonQueryAllWin()
{
	// TODO: Add your control notification handler code here
	this->SetDlgItemText(IDC_EDIT_QUERY_RESULT, this->send_request(QUERY_ALL_WIN, ""));
}

void CQueryDlg::OnBnClickedButtonQueryAllRouter()
{
	// TODO: Add your control notification handler code here
	this->SetDlgItemText(IDC_EDIT_QUERY_RESULT,this->send_request(QUERY_ALL_ROUTER, ""));
}

void CQueryDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	this->SetDlgItemText(IDC_EDIT_QUERY_ADDR, g_conf.query_ip);
	this->SetDlgItemText(IDC_EDIT_QUERY_PORT, g_conf.query_port);
}

CString CQueryDlg::send_request( CString uri, CString id )
{
	CString _url;
	if (id.IsEmpty()){ 
		_url = uri;
	}else{
		_url = uri+"?id="+id;
	}
	CString addr, port;
	int nPort;
	this->GetDlgItemText(IDC_EDIT_QUERY_ADDR, addr);
	this->GetDlgItemText(IDC_EDIT_QUERY_PORT, port); 
	nPort = ::atoi(port.GetBuffer());
	port.ReleaseBuffer();

	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	CHttpConnection* pConnection = session.GetHttpConnection(addr,(INTERNET_PORT)nPort);
	CHttpFile* pFile = pConnection->OpenRequest( CHttpConnection::HTTP_VERB_GET,_url);

	/*CString szHeaders = L"Accept: audio/x-aiff, audio/basic, audio/midi,\
	audio/mpeg, audio/wav, image/jpeg, image/gif, image/jpg, image/png,\
	image/mng, image/bmp, text/plain, text/html, text/htm\r\n";

	pFile->AddRequestHeaders(szHeaders);*/

	pFile->SendRequest();

	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	CString strResp = "";
	if(dwRet != HTTP_STATUS_OK)
	{
		CString errText;
	}
	else
	{
		record_conf();
		int len = pFile->GetLength();
		char buf[2000];
		int numread;
		CString filepath;

		while ((numread = pFile->Read(buf,sizeof(buf)-1)) > 0)
		{
			buf[numread] = '\0';
			strResp  += buf;
		}
	}

	session.Close();
	pFile->Close(); 
	delete pFile;

	return strResp;
}


void CQueryDlg::OnBnClickedButtonQueryRouter()
{
	// TODO: Add your control notification handler code here
	CString id;
	this->GetDlgItemText(IDC_EDIT_QUERY_ID, id);
	this->SetDlgItemText(IDC_EDIT_QUERY_RESULT,this->send_request(QUERY_ROUTER, id));
}

void CQueryDlg::OnBnClickedButtonQueryWin()
{
	// TODO: Add your control notification handler code here
	CString id;
	this->GetDlgItemText(IDC_EDIT_QUERY_ID, id);
	this->SetDlgItemText(IDC_EDIT_QUERY_RESULT,this->send_request(QUERY_WIN, id));
}

void CQueryDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CQueryDlg::record_conf()
{
	CString addr, port;
	this->GetDlgItemText(IDC_EDIT_QUERY_ADDR, addr);
	this->GetDlgItemText(IDC_EDIT_QUERY_PORT, port); 
	conf_update(QUERY_IP, addr.GetBuffer());
	conf_update(QUERY_PORT, port.GetBuffer());
	addr.ReleaseBuffer();
	port.ReleaseBuffer();
}
