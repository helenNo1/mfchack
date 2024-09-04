
// mfchackDlg.h: 头文件
//

#pragma once
#include "CAddSheet.h"

// CmfchackDlg 对话框
class CmfchackDlg : public CDialogEx
{
	CAddSheet m_addSheet; // 添加属性表成员变量
// 构造
public:
	CmfchackDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
	virtual void OnClose();      // 覆盖 OnOK 方法
	void checkRun();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHACK_DIALOG };
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
};
