#pragma once
#include <vector>


// CCaptureInterfaces dialog

class CCaptureInterfaces : public CDialog
{
	DECLARE_DYNAMIC(CCaptureInterfaces)

public:
	CCaptureInterfaces(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCaptureInterfaces();
	INT_PTR DoModal();

public:
	void AddInterface(CString strinerface);
// Dialog Data
	enum { IDD = IDD_DIALOG_CAPTUREINTERFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	std::vector<CString>m_interfaces;
	CCheckListBox * m_checks;
	CStatic * m_static;
};
