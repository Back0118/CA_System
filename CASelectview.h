#pragma once


// CASelectview 视图

class CASelectview : public CTreeView
{
	DECLARE_DYNCREATE(CASelectview)

protected:
	CASelectview();           // 动态创建所使用的受保护的构造函数
	virtual ~CASelectview();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl* c_treeCtrl;//树控件
	CImageList c_imageList;//图标列表
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};


