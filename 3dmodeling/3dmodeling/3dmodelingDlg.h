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
public:
	struct RGB{
		unsigned char R;
		unsigned char G;
		unsigned char B;
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
	int WritePCDFile(CString strfile);
	int WriteOBJFile(CString strfile);
	int ShowRawPoints();
	
private:
	bool m_bformat;
	union{
		unsigned char * m_colors;
		struct RGB * m_rgb; 
	}m_bytes;
	
	int m_bytecapacity;
	int m_bytecount;
	int m_pointcount;
	std::map<std::string, unsigned char>m_str2byte;
	
	CString m_strrawinput;
private:
	CString m_strexe;
public:
	CStatic m_tips;
	afx_msg void OnBnClickedButtonGenerate();
	afx_msg void OnBnClickedButtonFilepath();
	CEdit m_outputfilepath;
	CEdit m_mnn;
	CEdit m_md;
	CEdit m_msa;
	CEdit m_maxa;
	CEdit m_mina;
	CEdit m_output;
};
