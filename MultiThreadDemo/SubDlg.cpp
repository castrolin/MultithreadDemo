// SubDlg.cpp : ��@��
//

#include "stdafx.h"
#include "MultiThreadDemo.h"
#include "MultiThreadDemoDlg.h"
#include "SubDlg.h"
#include "afxdialogex.h"

// CSubDlg ��ܤ��

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


// CSubDlg �T���B�z�`��


void CSubDlg::OnBnClickedButtonyes()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	button = TRUE;
	EndDialog(IDYES); // this will return IDCANCEL

}


void CSubDlg::OnBnClickedButtonno()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	button = FALSE;
	EndDialog(IDNO);
}


void CSubDlg::OnBnClickedButtoncancel()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	AfxMessageBox("Nothing");
	EndDialog(IDYES);
}
