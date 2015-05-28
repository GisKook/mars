#pragma once
#include <string>
#include <vector>


// CCaptureInterfaces �Ի���

class CCaptureInterfaces : public CDialog
{
	DECLARE_DYNAMIC(CCaptureInterfaces)

public:
	CCaptureInterfaces(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCaptureInterfaces();
	virtual BOOL OnInitDialog();
public:
	void AddInterface(std::string strinerface);
	int GetDevIndex(){return m_devindex;};

private:
	std::vector<CString>m_interfaces;
	CButton * m_checks;
	int m_devindex;
// �Ի�������
	enum { IDD = IDD_COPDETECTORW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnsClicked(UINT);
};
