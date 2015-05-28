#pragma once
#include <string>
#include <vector>


// CCaptureInterfaces 对话框

class CCaptureInterfaces : public CDialog
{
	DECLARE_DYNAMIC(CCaptureInterfaces)

public:
	CCaptureInterfaces(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCaptureInterfaces();
	virtual BOOL OnInitDialog();
public:
	void AddInterface(std::string strinerface);
	int GetDevIndex(){return m_devindex;};

private:
	std::vector<CString>m_interfaces;
	CButton * m_checks;
	int m_devindex;
// 对话框数据
	enum { IDD = IDD_COPDETECTORW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnsClicked(UINT);
};
