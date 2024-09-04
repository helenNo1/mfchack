#pragma once


// CKernelhackPage 对话框

class CKernelhackPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CKernelhackPage)

public:
	CKernelhackPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CKernelhackPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_KERNEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
};
