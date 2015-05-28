// copdetectorWDlg.h : header file
//

#pragma once

#include "voippcap.h"
#include "TrayIcon.h"

// CcopdetectorWDlg dialog
class CcopdetectorWDlg : public CDialog
{
// Construction
public:
	CcopdetectorWDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COPDETECTORW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
private:
	CString CreateCaptureInterfaceDialog();
public:
	int m_index;
	struct voippcap * m_pcap;
	packet_handler m_packethandler;
private:
	CTrayIcon m_trayicon;
	HICON m_hIconPhone;
private:
	HANDLE m_hthread;
	static void capturenet(void *);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg void OnVoipdetectorExit();
};
