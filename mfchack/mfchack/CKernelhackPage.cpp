// CKernelhackPage.cpp: 实现文件
//

#include "pch.h"
#include "mfchack.h"
#include "CKernelhackPage.h"
#include "afxdialogex.h"


// CKernelhackPage 对话框

IMPLEMENT_DYNAMIC(CKernelhackPage, CMFCPropertyPage)

CKernelhackPage::CKernelhackPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_DIALOG_KERNEL)
{

}

CKernelhackPage::~CKernelhackPage()
{
}

void CKernelhackPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKernelhackPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CKernelhackPage 消息处理程序

