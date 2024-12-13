// CASelectview.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "CASelectview.h"
#include"MainFrm.h"

// CASelectview

IMPLEMENT_DYNCREATE(CASelectview, CTreeView)

CASelectview::CASelectview()
{

}

CASelectview::~CASelectview()
{
}

BEGIN_MESSAGE_MAP(CASelectview, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CASelectview::OnTvnSelchanged)
END_MESSAGE_MAP()


// CASelectview 诊断

#ifdef _DEBUG
void CASelectview::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CASelectview::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CASelectview 消息处理程序


void CASelectview::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	//初始化，树视图
	// 获取控件
	c_treeCtrl = &GetTreeCtrl();
	//1、准备图片集合
	 HICON icon=AfxGetApp()->LoadIconW(IDB_BITMAP1);
	 c_imageList.Create(40, 40, ILC_COLOR32, 1, 1);
	 c_imageList.Add(icon);
	 c_treeCtrl->SetImageList(&c_imageList, TVSIL_NORMAL);
	//2、添加节点
	c_treeCtrl->InsertItem(TEXT("申请证书"), 0, 0, NULL);
	c_treeCtrl->InsertItem(TEXT("签名证书"), 0, 0, NULL);
	c_treeCtrl->InsertItem(TEXT("删除证书"), 0, 0, NULL);
	c_treeCtrl->InsertItem(TEXT("验证证书"), 0, 0, NULL);
	c_treeCtrl->InsertItem(TEXT("待开发"), 0, 0, NULL);
	c_treeCtrl->InsertItem(TEXT("待开发2"), 0, 0, NULL);
	// TODO: 在此添加专用代码和/或调用基类
}


void CASelectview::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	HTREEITEM item = c_treeCtrl->GetSelectedItem();
	CString str = c_treeCtrl->GetItemText(item);
	//MessageBox(str);
	if (str==TEXT("申请证书"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
		}
	else if (str == TEXT("签名证书"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (str == TEXT("删除证书"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (str == TEXT("验证证书"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else if (str == TEXT("待开发"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
	}
	else if (str == TEXT("待开发2"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_F, (WPARAM)NM_F, (LPARAM)0);
	}
}
