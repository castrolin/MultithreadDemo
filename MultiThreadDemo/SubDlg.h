#pragma once
#include "afxwin.h"


// CSubDlg ��ܤ��

class CSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlg)

public:
	CSubDlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CSubDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_Active };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

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
