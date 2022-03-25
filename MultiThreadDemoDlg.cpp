
// MultiThreadDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiThreadDemo.h"
#include "MultiThreadDemoDlg.h"
#include "SubDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GLOBAL variable due to access the variable in different program
TimerThread* timethread  = new TimerThread;
CommThread* commthread = new CommThread;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMultiThreadDemoDlg dialog




CMultiThreadDemoDlg::CMultiThreadDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiThreadDemoDlg::IDD, pParent)
	, m_displaystring(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiThreadDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_press, m_press);
	DDX_Control(pDX, IDC_STATIC_Timer, m_timer);
	DDX_Control(pDX, IDC_STATIC_Thread, m_thread);
	DDX_Control(pDX, IDC_BUTTON_pause, m_pause);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_add);
	DDX_Control(pDX, IDC_BUTTON_MINUS, m_minus);
	DDX_Control(pDX, IDC_BUTTON_ZERO, m_beZero);

	DDX_Text(pDX, IDC_EDIT_DISPLAY, m_displaystring);
}

BEGIN_MESSAGE_MAP(CMultiThreadDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_press, &CMultiThreadDemoDlg::OnBnClickedButtonpress)
	ON_BN_CLICKED(IDC_BUTTON_pause, &CMultiThreadDemoDlg::OnBnClickedButtonpause)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMultiThreadDemoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CMultiThreadDemoDlg::OnBnClickedButtonMinus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMultiThreadDemoDlg message handlers

BOOL CMultiThreadDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	commthread->addevent = CreateEvent(NULL,TRUE,FALSE,NULL);
	commthread->minusevent = CreateEvent(NULL,TRUE,FALSE,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultiThreadDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiThreadDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiThreadDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMultiThreadDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	strMain.Format("Running: %d", currValue);
	if(currValue <= maxValue)
	{
		if(currValue == maxValue)
		{
			currValue = 0;
		}
		else
		{
			currValue++;
		}
			
	}

	m_timer.SetWindowText(strMain);

	timethread -> strMain.Format("Running: %d", timethread -> currentValue);
	m_thread.SetWindowText(timethread ->strMain);
	CDialogEx::OnTimer(nIDEvent);
}


UINT TimerThread::MyThreadProc(LPVOID Param)
{	
	
	TimerThread *timethreada =    (TimerThread*)(Param);

	/* check the other event state and decide what to do */	
	if( WaitForSingleObject(timethread -> stopevent,10) == WAIT_OBJECT_0)	 
	{

		timethreada->currentValue = 0;

		while(timethreada -> currentValue <= timethreada -> maxValue +1 )
		{
			if(timethreada -> currentValue == timethreada -> maxValue +1 )
			{
				timethreada -> currentValue = 0;
			}

			Sleep(1050);
			timethreada -> currentValue++;
			if ( WaitForSingleObject(timethread -> stopevent,5) == WAIT_TIMEOUT )
			{
				TRACE("The No butoon still run \n");

				// Don't forget to the release the event when finished the events!
				// Release the source, if don't do this step, the "Deathlock" will be appeared after use the thread again.
				CloseHandle(timethread->stopevent);

				return TRUE;
			}
				
		}
	}
	
}

UINT CommThread::AddThreadProc(LPVOID Param)
{
	/* check the other event state and decide what to do */
	SetEvent(commthread->addevent);

	if(WaitForSingleObject(commthread -> minusevent, 0) != WAIT_OBJECT_0 || WaitForSingleObject(commthread -> minusevent, 0) == WAIT_OBJECT_0 )
	{
		TRACE("The MinusThread is finished \n");
		CMultiThreadDemoDlg* addthread =  (CMultiThreadDemoDlg*)(Param);
		addthread->GetDlgItem(IDC_EDIT_DISPLAY)-> GetWindowText(commthread->inputstring);
		commthread-> InputValue = atoi(commthread->inputstring); // string into int
		commthread-> InputValue ++;
		commthread->inputstring.Format("%d",commthread-> InputValue);
		addthread->GetDlgItem(IDC_EDIT_DISPLAY) -> SetWindowText(commthread->inputstring);
		return TRUE;
	}

	//while(WaitForSingleObject(commthread -> minusevent, 0) == WAIT_OBJECT_0)
	//{
	//	TRACE("The minus still running ?? \n");
	//	return TRUE;
	//}
	//ResetEvent(commthread -> addevent);
	
	
	
}

UINT CommThread:: MinusThreadProc(LPVOID Param)
{
	/* check the other event state and decide what to do */
	SetEvent(commthread-> minusevent);

	if(WaitForSingleObject(commthread -> addevent, 0) == WAIT_OBJECT_0 || WaitForSingleObject(commthread -> addevent, 0) != WAIT_OBJECT_0)
	{	
		TRACE("The AddThread is finished \n");
		CMultiThreadDemoDlg* minusthread =  (CMultiThreadDemoDlg*)(Param);
		minusthread->GetDlgItem(IDC_EDIT_DISPLAY)-> GetWindowText(commthread->inputstring);
		commthread-> InputValue = atoi(commthread->inputstring); // string into int
		commthread-> InputValue --;
		commthread->inputstring.Format("%d",commthread-> InputValue);
		minusthread->GetDlgItem(IDC_EDIT_DISPLAY) -> SetWindowText(commthread->inputstring);
		return TRUE;
	}

	//while( WaitForSingleObject(commthread -> addevent, 0) == WAIT_OBJECT_0)
	//{
	//	TRACE("The add still running ?? \n");
	//	return TRUE;
	//}

	//ResetEvent(commthread -> minusevent);
	

	

	
	
}


void CMultiThreadDemoDlg::OnBnClickedButtonpress()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//TimerThread* timethread  = new TimerThread;
	

	timethread -> currentValue = 0;
	timethread -> maxValue = 10;
	timethread -> currValue = 0 ;

	maxValue = 10; // CMultiThreadDemoDlg member variable
	currValue = 0; // CMultiThreadDemoDlg member variable

	CSubDlg* DLG = new CSubDlg;
	switch(DLG -> DoModal())
	{
	case IDYES:
		
		SetTimer(1234,1000,0); // for timer
		TRACE("YES press \n");
		//Begin the Thread and Setting
		timethread ->stopevent = CreateEvent(NULL,TRUE,TRUE,"stopevent");
		timethread -> ThreadEvent = AfxBeginThread(TimerThread::MyThreadProc,timethread);// for the specified thread
		
		break;

	case IDNO:

		TRACE("No press \n");
		KillTimer(1234);

		//Use the signaled state to control the program finished or not
		//This method have to accompany to the UNIT LPVOID ThreadFunctioin
		//Please draw the system diagram in order to memorize the concept
		//

		ResetEvent(timethread -> stopevent);
		timethread -> dw = WaitForSingleObject(timethread->ThreadEvent->m_hThread,10);

		if(timethread -> dw == WAIT_TIMEOUT)
		{
			TRACE("the wait for it die \n");
			//TerminateThread(timethread ->ThreadEvent -> m_hThread,0);
		}
	
		// the sub thread will be closed by this command but this is a dangerous function
		//TerminateThread(timethread ->ThreadEvent -> m_hThread,0);
		
		m_timer.SetWindowText("Timer Stopped");
		m_thread.SetWindowTextA("Thread Stopped");

		break;
	}

	delete 	 DLG;
}

void CMultiThreadDemoDlg::OnBnClickedButtonpause()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if(AfxMessageBox("Close Program",MB_YESNO) == IDYES)
	{
		TRACE("YES \n"); // Debug skill similar to assert
		AfxMessageBox("Will close the file");
		Sleep(10);
		EndDialog(IDD);	 // IDD is the main frame dialog
	}
	else
	{
		TRACE("NO \n");
		EndDialog(IDD);
	}
}




void CMultiThreadDemoDlg::OnBnClickedButtonAdd()
{
	
	
	//CWinThread* addbeginthread = AfxBeginThread(CommThread::AddThreadProc,this,THREAD_PRIORITY_NORMAL);

	if(WaitForSingleObject(commthread -> addevent,10) != WAIT_OBJECT_0)
	{
		TRACE("AddThread has not started \n");
		CWinThread* addbeginthread = AfxBeginThread(CommThread::AddThreadProc,this,THREAD_PRIORITY_NORMAL);
		addbeginthread ->ResumeThread();
		return;
	}
	else
	{
		TRACE("AddThread has already started once \n");
		CWinThread* addbeginthread = AfxBeginThread(CommThread::AddThreadProc,this,THREAD_PRIORITY_NORMAL);
		addbeginthread ->ResumeThread();
		return;
	}
		

	//addbeginthread ->ResumeThread();
	//CloseHandle(commthread->minusevent);

}


void CMultiThreadDemoDlg::OnBnClickedButtonMinus()
{
	if(WaitForSingleObject(commthread -> minusevent,10) == WAIT_OBJECT_0)
	{
		TRACE("AddThread has not been started \n");
		CWinThread* addbeginthread = AfxBeginThread(CommThread::MinusThreadProc,this,THREAD_PRIORITY_NORMAL);
		addbeginthread -> ResumeThread();
		return;
	}
	else
	{
		TRACE("Minus Thread has already started one time");
		CWinThread* addbeginthread = AfxBeginThread(CommThread::MinusThreadProc,this,THREAD_PRIORITY_NORMAL);
		addbeginthread -> ResumeThread();
		return;
	}
		


	
	
}


void CMultiThreadDemoDlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	// release the memory in oder to memory leak
	delete timethread;
	delete commthread;
	


	CDialogEx::OnClose();
}
