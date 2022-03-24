
// MultiThreadDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <string>
#include <sstream>


// CMultiThreadDemoDlg dialog
class CMultiThreadDemoDlg : public CDialogEx
{
// Construction
public:
	CMultiThreadDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MULTITHREADDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	afx_msg void OnBnClickedButtonpress();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_timer;
	CStatic m_thread;
	CButton m_press;
	CButton m_pause;
	CFont m_font;
	afx_msg void OnBnClickedButtonpause();
	CButton m_add;
	CButton m_minus;
	CButton m_beZero;

	CString strMain;
	int currValue ;	//for timer
	int maxValue;
	afx_msg void OnBnClickedButtonAdd();
	CString m_displaystring;
	afx_msg void OnBnClickedButtonMinus();

	CWinThread* addbeginthread;

	afx_msg void OnClose();
};
class TimerThread
{
public:

	static UINT MyThreadProc(LPVOID Param);

	CString strMain;
	int currValue ;	//for timer
	int currentValue;	//for thread
	int maxValue;
	CWinThread* ThreadEvent;
	HANDLE stopevent;
	
	DWORD dw;
};
class CommThread
{
public:
	static UINT AddThreadProc(LPVOID Param);
	static UINT MinusThreadProc(LPVOID Param);
	int InputValue;
	CString	inputstring;
	HANDLE mainevent;
	HANDLE addevent;
	
};