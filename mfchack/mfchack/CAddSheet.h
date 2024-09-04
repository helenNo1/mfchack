#pragma once
#include "CUserhackPage.h"
#include "CKernelhackPage.h"


// CAddSheet

class CAddSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAddSheet)
	CUserhackPage    m_userpage;
	CKernelhackPage     m_kernelpage;
	

public:
	CAddSheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CAddSheet();
	BOOL CAddSheet::OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};


