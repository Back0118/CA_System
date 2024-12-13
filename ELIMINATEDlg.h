#pragma once



// ELIMINATEDlg 窗体视图

class ELIMINATEDlg : public CFormView
{
	DECLARE_DYNCREATE(ELIMINATEDlg)

protected:
	ELIMINATEDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~ELIMINATEDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELIMDlg };
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
	CString Delete_name;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


