#pragma once


// CAndroidDlg 对话框

class CAndroidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAndroidDlg)

public:
	CAndroidDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAndroidDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANDROID_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
