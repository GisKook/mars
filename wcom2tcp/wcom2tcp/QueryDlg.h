#pragma once


// CQueryDlg dialog

class CQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CQueryDlg)

public:
	CQueryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryDlg();

private:
	CString send_request(CString uri, CString id);
	void record_conf();
// Dialog Data
	enum { IDD = IDD_DIALOG_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQueryAllWin();
	afx_msg void OnBnClickedButtonQueryAllRouter();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonQueryRouter();
	afx_msg void OnBnClickedButtonQueryWin();
	afx_msg void OnClose();
};
