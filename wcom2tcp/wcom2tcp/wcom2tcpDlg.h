// wcom2tcpDlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include "TrayIcon.h"
#include "QueryDlg.h"
// Cwcom2tcpDlg �Ի���
class Cwcom2tcpDlg : public CDialog
{
// ����
public:
	Cwcom2tcpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WCOM2TCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGenIdAndKey();
	afx_msg void OnBnClickedButtonOpenSerial();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBreak();

public:
	SOCKET m_socket;
	HANDLE m_serial;
	CString m_tt_id;
	CString m_tt_key;
	unsigned long long m_id;
	unsigned int m_key;
private:
	int CheckRegister();
	static void DoRoute(void *);
	HANDLE m_thread;
private:
	bool CheckInputBlank();
private:
	void Init();
	bool SetClipboardText(CString text);
private:
	CTrayIcon m_trayicon;
	HICON m_icon;
    std::vector<CString> m_comms;
	CQueryDlg *m_dlg_query;

public:
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnBnClickedButtonGenIdAndKey3();
	afx_msg void OnStnClickedStaticTips();
	afx_msg void OnTrayiconQuit();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonCopyId();
	afx_msg void OnBnClickedButtonCopyKey();
	afx_msg void OnBnClickedButtonQuery();
};
