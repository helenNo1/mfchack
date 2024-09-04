
// mfc_multitabDlg.h: 头文件
//

#pragma once
#include "CJzmDlg.h"
#include "CAndroidDlg.h"

// CmfcmultitabDlg 对话框
class CmfcmultitabDlg : public CDialogEx
{
	CJzmDlg m_jzmDlg;
	CAndroidDlg m_androidDlg;
// 构造
public:
	CmfcmultitabDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MULTITAB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
