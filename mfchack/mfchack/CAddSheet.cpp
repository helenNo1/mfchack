// CAddSheet.cpp: 实现文件
//

#include "pch.h"
#include "mfchack.h"
#include "CAddSheet.h"


// CAddSheet

IMPLEMENT_DYNAMIC(CAddSheet, CPropertySheet)

CAddSheet::CAddSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	// 添加三个属性页到属性表   
	AddPage(&m_userpage);
	AddPage(&m_kernelpage);
	
}

CAddSheet::CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	// 添加三个属性页到属性表   
	AddPage(&m_userpage);
	AddPage(&m_kernelpage);
}

CAddSheet::~CAddSheet()
{
}


BEGIN_MESSAGE_MAP(CAddSheet, CPropertySheet)
END_MESSAGE_MAP()


// CAddSheet 消息处理程序
BOOL CAddSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// 隐藏“确定”、“取消”、“应用”和“帮助”按钮
	CWnd* pButton = GetDlgItem(IDOK);
	if (pButton)
	{
		pButton->ShowWindow(SW_HIDE);
	}
	pButton = GetDlgItem(IDCANCEL);
	if (pButton)
	{
		pButton->ShowWindow(SW_HIDE);
	}
	pButton = GetDlgItem(ID_APPLY_NOW);
	if (pButton)
	{
		pButton->ShowWindow(SW_HIDE);
	}
	pButton = GetDlgItem(IDHELP);
	if (pButton)
	{
		pButton->ShowWindow(SW_HIDE);
	}

	return bResult;
}


