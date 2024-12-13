// DecrptionDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "DecrptionDlg.h"


// DecrptionDlg

IMPLEMENT_DYNCREATE(DecrptionDlg, CFormView)

DecrptionDlg::DecrptionDlg()
	: CFormView(IDD_CADecrption)
{

}

DecrptionDlg::~DecrptionDlg()
{
}

void DecrptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DecrptionDlg, CFormView)
END_MESSAGE_MAP()


// DecrptionDlg 诊断

#ifdef _DEBUG
void DecrptionDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DecrptionDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DecrptionDlg 消息处理程序
