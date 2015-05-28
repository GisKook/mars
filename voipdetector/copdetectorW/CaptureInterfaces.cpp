// CaptureInterfaces.cpp : 实现文件
//

#include "stdafx.h"
#include "copdetectorW.h"
#include "CaptureInterfaces.h"

#define STARTID 10000
#define GETID(x) STARTID+x

// CCaptureInterfaces 对话框

IMPLEMENT_DYNAMIC(CCaptureInterfaces, CDialog)

CCaptureInterfaces::CCaptureInterfaces(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureInterfaces::IDD, pParent),m_devindex(-1)
{

}

CCaptureInterfaces::~CCaptureInterfaces()
{
}

void CCaptureInterfaces::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CCaptureInterfaces::OnInitDialog()
{
	CDialog::OnInitDialog();
	int interfacecount = m_interfaces.size();
	int bottom = 80+20*interfacecount;
	int right = 500;
	this->SetWindowPos(NULL, -1,-1,500,bottom,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	CButton *btnok = (CButton*)this->GetDlgItem(IDOK);
	CRect crControl;
	btnok->GetWindowRect(crControl);
	btnok->MoveWindow(right - crControl.Width()*2 - 20, bottom - crControl.Height() - 30,crControl.Width(),crControl.Height());
	btnok->Invalidate();
	CButton *btncancle = (CButton*)this->GetDlgItem(IDCANCEL);
	btncancle->GetWindowRect(crControl);
	btncancle->MoveWindow(right - crControl.Width() - 10, bottom - crControl.Height() - 30,crControl.Width(),crControl.Height());
	btncancle->Invalidate();

	m_checks = new CButton[interfacecount];
	for(int i = 0; i < interfacecount; ++i){
		m_checks[i].Create(m_interfaces[i],WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
			CRect(10,10+20*i,500,30+i*20), this, GETID(i));
	}

	return TRUE;
}

void CCaptureInterfaces::AddInterface( std::string strinerface )
{ 
	m_interfaces.push_back(strinerface.c_str());
}
BEGIN_MESSAGE_MAP(CCaptureInterfaces, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED,10000,10010,&CCaptureInterfaces::OnBnsClicked)
	ON_BN_CLICKED(IDOK, &CCaptureInterfaces::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCaptureInterfaces::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCaptureInterfaces 消息处理程序

void CCaptureInterfaces::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
	int devcount = m_interfaces.size();
	int i;
	for(i = 0; i < devcount; ++i){
		if (m_checks[i].GetCheck())
		{
			break;
		}
	}
	if (i == devcount)
	{
		i = -1;
	}
	m_devindex = i;
}

void CCaptureInterfaces::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CCaptureInterfaces::OnBnsClicked( UINT nid)
{ 
	int index = nid - STARTID;
	if (m_checks[index].GetCheck())
	{
		m_checks[index].SetCheck(0);
	}else{
		m_checks[index].SetCheck(1);
	}
}
