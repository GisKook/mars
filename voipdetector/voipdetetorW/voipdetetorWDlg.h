// voipdetetorWDlg.h : header file
//

#pragma once


// CvoipdetetorWDlg dialog
class CvoipdetetorWDlg : public CDialog
{
// Construction
public:
	CvoipdetetorWDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VOIPDETETORW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


private:
	CString m_strInterface;
private:
	CString CreateCaptureInterfaceDialog();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
