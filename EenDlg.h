#pragma once



// EenDlg 窗体视图

class EenDlg : public CFormView
{
	DECLARE_DYNCREATE(EenDlg)

protected:
	EenDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~EenDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EenDlg };
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
	afx_msg void OnBnClickedEenok();
	afx_msg void OnBnClickedEencancel();
private:
	CString Ver_name;
	CString CA_pulickey;
};


