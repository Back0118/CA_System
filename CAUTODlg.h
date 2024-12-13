#pragma once



// CAUTODlg 窗体视图

class CAUTODlg : public CFormView
{
	DECLARE_DYNCREATE(CAUTODlg)

protected:
	CAUTODlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAUTODlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOGRAPH };
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
	afx_msg void OnBnClickedAutobutton1();
	afx_msg void OnBnClickedAutobutton2();

private:
	CString User_information;
	CString Publickey_Path;
	CString CA_privatepath;
};


