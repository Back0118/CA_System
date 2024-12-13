#pragma once



// EN_File 窗体视图

class EN_File : public CFormView
{
	DECLARE_DYNCREATE(EN_File)

protected:
	EN_File();           // 动态创建所使用的受保护的构造函数
	virtual ~EN_File();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENDIALOG1 };
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
	CString EN_Path;
public:
	afx_msg void OnBnClickedEnok();
};


