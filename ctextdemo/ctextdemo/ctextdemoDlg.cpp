
// ctextdemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ctextdemo.h"
#include "ctextdemoDlg.h"
#include "afxdialogex.h"

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


// CctextdemoDlg 对话框



CctextdemoDlg::CctextdemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTEXTDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nTextX = 260;
	m_nTextY = 10;
	m_pOldFont = NULL;
}

void CctextdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CctextdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CctextdemoDlg 消息处理程序

BOOL CctextdemoDlg::OnInitDialog()
{
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

	  // 创建一种新的字体（18点，隶书）   
	m_newFont.CreatePointFont(180, _T("隶书"));

	// 设置定时器，定时时间为200ms   
	SetTimer(1, 200, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CctextdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CctextdemoDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting   

		 // 设置m_newFont对象的字体为当前字体，并将之前的字体指针保存到m_pOldFont   
		m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
		// 设置   
		dc.SetBkMode(TRANSPARENT); //设置背景为透明！   
		// 设置文本颜色为红色   
		dc.SetTextColor(RGB(255, 0, 0));
		// 在指定位置输出文本   
		dc.TextOut(m_nTextX, 10, _T("欢迎来到鸡啄米！"));
		// 设置文本颜色为绿色   
		dc.SetTextColor(RGB(0, 255, 0));
		// 在指定位置输出文本   
		dc.TextOut(10, m_nTextY, _T("谢谢关注www.jizhuomi.com"));
		// 恢复以前的字体   
		dc.SelectObject(m_pOldFont);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CctextdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CctextdemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	// TODO: Add your message handler code here and/or call default   
	LOGFONT logFont;
	// 获取m_newFont字体的LOGFONT结构   
	m_newFont.GetLogFont(&logFont);

	// 将m_nTextX的值减5   
	m_nTextX -= 5;
	// 如果m_nTextX小于10，则文本“欢迎来到鸡啄米”回到起始位置   
	if (m_nTextX < 10)
		m_nTextX = 260;

	// 将m_nTextY的值加一个字符高度   
	m_nTextY += abs(logFont.lfHeight);
	// 如果m_nTextY大于260，则文本“谢谢关注www.jizhuomi.com”回到起始位置   
	if (m_nTextY > 260)
		m_nTextY = 10;

	// 使窗口客户区无效，之后就会重绘   
	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}
