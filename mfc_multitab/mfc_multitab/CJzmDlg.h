#pragma once


// CJzmDlg 对话框

class CJzmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJzmDlg)

public:
	CJzmDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CJzmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JIZHUOMI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
