#pragma once



// CAAuthDlg 窗体视图

class CAAuthDlg : public CFormView
{
	DECLARE_DYNCREATE(CAAuthDlg)

protected:
	CAAuthDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAAuthDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTH };
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
private:
	CString AUTH_name;
	CString AUTH_privatekey;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


