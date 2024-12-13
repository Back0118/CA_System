// CA_Displayview.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "CA_Displayview.h"


// CA_Displayview

IMPLEMENT_DYNCREATE(CA_Displayview, CFormView)

CA_Displayview::CA_Displayview()
	: CFormView(IDD_CA_Displayview)
{

}

CA_Displayview::~CA_Displayview()
{
}

void CA_Displayview::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CA_Displayview, CFormView)
END_MESSAGE_MAP()


// CA_Displayview 诊断

#ifdef _DEBUG
void CA_Displayview::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CA_Displayview::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CA_Displayview 消息处理程序
