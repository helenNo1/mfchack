
// ctextdemoDlg.h: 头文件
//

#pragma once


// CctextdemoDlg 对话框
class CctextdemoDlg : public CDialogEx
{
	int m_nTextX;   // 水平滚动文本的起始点的x坐标   
	int m_nTextY;   // 垂直滚动文本的起始点的y坐标   
	CFont m_newFont;   // 新字体   
	CFont* m_pOldFont; // 选择新字体之前的字体  
// 构造
public:
	CctextdemoDlg(CWnd* pParent = nullptr);	// 标准构造函数
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTEXTDEMO_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
