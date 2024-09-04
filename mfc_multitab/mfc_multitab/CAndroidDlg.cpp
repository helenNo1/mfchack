// CAndroidDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfc_multitab.h"
#include "CAndroidDlg.h"
#include "afxdialogex.h"


// CAndroidDlg 对话框

IMPLEMENT_DYNAMIC(CAndroidDlg, CDialogEx)

CAndroidDlg::CAndroidDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANDROID_DIALOG, pParent)
{

}

CAndroidDlg::~CAndroidDlg()
{
}

void CAndroidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAndroidDlg, CDialogEx)
END_MESSAGE_MAP()


// CAndroidDlg 消息处理程序
