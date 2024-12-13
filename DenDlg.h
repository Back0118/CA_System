#pragma once

#include<vector>

// DenDlg 窗体视图

class DenDlg : public CFormView
{
	DECLARE_DYNCREATE(DenDlg)

protected:
	DenDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~DenDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DenDlg };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDenok();
	afx_msg void OnBnClickedDencancel();
private:
	CString FlieCr_Path;
public:
	afx_msg void OnBnClickedFleprbutton1();
};


