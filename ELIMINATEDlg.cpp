// ELIMINATEDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "ELIMINATEDlg.h"
#include"file.h"
#include"Global.h"
#include "RSASignerVerifier.h"
#include<string>


// ELIMINATEDlg

IMPLEMENT_DYNCREATE(ELIMINATEDlg, CFormView)

ELIMINATEDlg::ELIMINATEDlg()
	: CFormView(IDD_ELIMDlg)
	, Delete_name(_T(""))
{

}

ELIMINATEDlg::~ELIMINATEDlg()
{
}

void ELIMINATEDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DeleteEDIT1, Delete_name);
}

BEGIN_MESSAGE_MAP(ELIMINATEDlg, CFormView)
	ON_BN_CLICKED(IDOK, &ELIMINATEDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ELIMINATEDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ELIMINATEDlg 诊断

#ifdef _DEBUG
void ELIMINATEDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ELIMINATEDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ELIMINATEDlg 消息处理程序


void ELIMINATEDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	std::string name;
	name = CT2A(Delete_name.GetString());
	if (Delete_name.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else
	{
		bool res1 = F_ile::readFilename(name);
		if (res1)
		{
			std::string outputName;
			Global glo;
			F_ile::getNameFromFile(name, outputName);

			if (glo.userExists(outputName))
			{
				 glo.removeUser(outputName);
				 MessageBox(TEXT("删除成功"));
			}
		}
		else
		{
			MessageBox(TEXT("输入无效"));
		}

	}
	Delete_name.Empty();
	UpdateData(FALSE);

}


void ELIMINATEDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete_name.Empty();
	UpdateData(FALSE);
}
