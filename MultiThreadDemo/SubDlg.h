#pragma once
#include "afxwin.h"


// CSubDlg 對話方塊

class CSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlg)

public:
	CSubDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CSubDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_Active };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonyes();
	CButton m_yes;
	CString TestMsg;
	CButton m_no;
	BOOL button;
	afx_msg void OnBnClickedButtonno();
	CButton m_cancel;
	afx_msg void OnBnClickedButtoncancel();
	CString m_subdlgStatic;


};
