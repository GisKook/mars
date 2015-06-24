// hotkeyDlg.h : header file
//

#pragma once

#include "TrayIcon.h"
#include "afxwin.h"
// ChotkeyDlg dialog
class ChotkeyDlg : public CDialog
{
// Construction
public:
	ChotkeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HOTKEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CTrayIcon m_trayicon;
	bool m_bcheck;
	bool m_bshow;
	HICON m_hCheck;
	HICON m_hUncheck;
	HICON m_hDollor;
// Implementation
private:
	CString GetClipboardText();
	void SetClipboardText(CString text);
	CString ClearLinebreak(CString text);
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnHotkeyExit();
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnEnChangeEditHb();
	CEdit m_yourearnings;
	CEdit m_billedtoclient;
	CEdit m_bidscount;
	CEdit m_yourearnings2;
	CEdit m_highbids;
	CEdit m_lowbids;
	CEdit m_avgbids;
	CEdit m_theothers;
	afx_msg void OnBnClickedButtonBtc();
	afx_msg void OnBnClickedButtonCalc();
};
