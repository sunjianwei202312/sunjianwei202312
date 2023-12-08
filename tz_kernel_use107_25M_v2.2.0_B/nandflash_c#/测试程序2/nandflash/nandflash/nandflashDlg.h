// nandflashDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CnandflashDlg 对话框
class CnandflashDlg : public CDialog
{
// 构造
public:
	CnandflashDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NANDFLASH_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	static DWORD WINAPI G_ReadThread(LPVOID lpParameter);
	static DWORD WINAPI G_RemoveThread(LPVOID lpParameter);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnStnClickedStatic1();
	afx_msg void OnBnClickedstart();
	afx_msg void P_ReadPortThread();
	afx_msg void P_RemovePortThread();
	afx_msg void RemoveFunction();
	afx_msg void comparefile(char * str1,int jishu);
	//afx_msg TCHAR *CString2TCHAR(CString &str);
	CEdit m_control;
	CString m_value;
	CEdit m_size_control;
	CString m_size_value;
	CEdit m_num_control;
	CString m_num_value;
	afx_msg void OnBnClickedremove();
};
