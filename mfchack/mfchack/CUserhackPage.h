﻿#pragma once


// CUserhackPage 对话框

class CUserhackPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CUserhackPage)

public:
	CUserhackPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserhackPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void CUserhackPage::OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButton1();
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
};
