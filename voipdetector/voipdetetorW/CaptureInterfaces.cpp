// CaptureInterfaces.cpp : implementation file
//

#include "stdafx.h"
#include "voipdetetorW.h"
#include "CaptureInterfaces.h"


// CCaptureInterfaces dialog

IMPLEMENT_DYNAMIC(CCaptureInterfaces, CDialog)

CCaptureInterfaces::CCaptureInterfaces(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureInterfaces::IDD, pParent),m_checks(NULL),m_static(NULL)
{

}

CCaptureInterfaces::~CCaptureInterfaces()
{
	delete []m_checks;
	delete []m_static;
	m_interfaces.clear();
}

void CCaptureInterfaces::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CCaptureInterfaces::AddInterface( CString strinerface )
{ 
	m_interfaces.push_back(strinerface);
}

INT_PTR CCaptureInterfaces::DoModal()
{
	int interfacecount = m_interfaces.size();

	//this->SetWindowPos(NULL, -1,-1,300,interfacecount * 50,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	this->SetWindowPos(NULL, -1,-1,300,500,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	//m_checks = new CCheckListBox[interfacecount];
	//m_static = new CStatic[interfacecount];
	//std::vector<CString>::iterator pos;
	//int i;
	//for(pos = m_interfaces.begin(),i = 0; pos != m_interfaces.end();++pos,++i){ 
	//	m_static[i].SetWindowText(*pos);

	//}
	return CDialog::DoModal();
}
BEGIN_MESSAGE_MAP(CCaptureInterfaces, CDialog)
END_MESSAGE_MAP()


// CCaptureInterfaces message handlers
