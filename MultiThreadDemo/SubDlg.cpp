// SubDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MultiThreadDemo.h"
#include "MultiThreadDemoDlg.h"
#include "SubDlg.h"
#include "afxdialogex.h"

// CSubDlg 對話方塊

IMPLEMENT_DYNAMIC(CSubDlg, CDialogEx)

CSubDlg::CSubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubDlg::IDD, pParent)
	, m_subdlgStatic(_T(""))
{

}

CSubDlg::~CSubDlg()
{
}

void CSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_yes, m_yes);
	DDX_Control(pDX, IDC_BUTTON_no, m_no);
	DDX_Control(pDX, IDC_BUTTON_cancel, m_cancel);
	DDX_Text(pDX, IDC_STATIC_subdlg, m_subdlgStatic);
}


BEGIN_MESSAGE_MAP(CSubDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_yes, &CSubDlg::OnBnClickedButtonyes)
	ON_BN_CLICKED(IDC_BUTTON_no, &CSubDlg::OnBnClickedButtonno)
	ON_BN_CLICKED(IDC_BUTTON_cancel, &CSubDlg::OnBnClickedButtoncancel)
END_MESSAGE_MAP()


// CSubDlg 訊息處理常式


void CSubDlg::OnBnClickedButtonyes()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	button = TRUE;
	EndDialog(IDYES); // this will return IDCANCEL

}


void CSubDlg::OnBnClickedButtonno()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	button = FALSE;
	EndDialog(IDNO);
}


void CSubDlg::OnBnClickedButtoncancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AfxMessageBox("Nothing");
	EndDialog(IDYES);
}
