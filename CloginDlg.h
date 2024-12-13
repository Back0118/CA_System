#pragma once
#include "afxdialogex.h"


// CloginDlg 对话框

class CloginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CloginDlg)

public:
	CloginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CloginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
private:
	CString c_user;
	CString c_pwd;
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
};
