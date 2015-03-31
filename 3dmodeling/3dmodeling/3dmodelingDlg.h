// 3dmodelingDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <map>
#include <string>


// CMy3dmodelingDlg dialog
class CMy3dmodelingDlg : public CDialog
{
// Construction
public:
	CMy3dmodelingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY3DMODELING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	enum{
		INPUT_OK,
		INPUT_UNAVAILABLECHARACTER,
		INPUT_NOTMATCH
	};

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFormat();
	CEdit m_input;
private:
	int IsIllegal(CString strinput);
	int FillBytes(CString strinput);
	void ShowFormatColors();
	int FormatRawColors(CString strinput);
private:
	bool m_bformat;
	unsigned char * m_colors;
	int m_bytecount;
	std::map<std::string, unsigned char>m_str2byte;
	
	CString m_strrawinput;
public:
	CStatic m_tips;
	afx_msg void OnBnClickedButtonGenerate();
	afx_msg void OnBnClickedButtonFilepath();
	CEdit m_outputfilepath;
};
