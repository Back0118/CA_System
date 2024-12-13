#pragma once



// CA_Displayview 窗体视图

class CA_Displayview : public CFormView
{
	DECLARE_DYNCREATE(CA_Displayview)

protected:
	CA_Displayview();           // 动态创建所使用的受保护的构造函数
	virtual ~CA_Displayview();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CA_Displayview };
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
};


