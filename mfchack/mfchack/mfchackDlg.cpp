
// mfchackDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "mfchack.h"
#include "mfchackDlg.h"
#include "afxdialogex.h"
//#include "CAddSheet.h"


#define WM_EXIT_APP (WM_USER + 1)  // 定义自定义的退出消息

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfchackDlg 对话框



CmfchackDlg::CmfchackDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHACK_DIALOG, pParent), m_addSheet(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfchackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfchackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()  // 添加对 WM_CLOSE 消息的处理

END_MESSAGE_MAP()


void CmfchackDlg::checkRun() {
	typedef void(*DllCheckRun)();
	DllCheckRun dllCheckRun = NULL;

	HINSTANCE hDLL = LoadLibrary(L"dll_runsingle.dll");
	if (hDLL != NULL)
	{
		dllCheckRun = (DllCheckRun)GetProcAddress(hDLL, "checkRun");
		if (dllCheckRun != NULL)
		{
			MessageBox(_T("load checkRun success"), _T("ok window"), MB_OK);
			//HelloWorld();
		}
		else
		{
			MessageBox(_T("load checkRun fail"), _T("err window"), MB_OK);
			return;

		}
		dllCheckRun();
		FreeLibrary(hDLL);

	}
	else
	{
		MessageBox(_T("Could not load dll_keyinputlog.dll"), _T("err"), MB_OK);

	}
}

// CmfchackDlg 消息处理程序

BOOL CmfchackDlg::OnInitDialog()
{
	checkRun();
	
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 创建属性表对象   
	//CAddSheet sheet(_T(""));
	// 设置属性对话框为向导对话框   
	//sheet.SetWizardMode();
	// 打开模态向导对话框   
	//sheet.DoModal();


	// 初始化属性表
	m_addSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	m_addSheet.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	CRect rect;
	GetClientRect(&rect);
	m_addSheet.SetWindowPos(nullptr, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOACTIVATE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfchackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfchackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfchackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CmfchackDlg::OnClose()
{
	::MessageBox(NULL, L"oncancel func in", L"debug", MB_OK);
	// 发送自定义退出消息给 DLL
	HWND hwnd = ::FindWindow(_T("DummyWindowClass"), _T("Dummy Window"));
	if (hwnd)
	{
		::PostMessage(hwnd, WM_EXIT_APP, 0, 0);
	}

	CDialogEx::OnClose();
}

