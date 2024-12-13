// CAUTODlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "CAUTODlg.h"
#include"file.h"
#include <string>
#include "RsaKeyGenerator.h"
#pragma warning(disable:4996)
// CAUTODlg

IMPLEMENT_DYNCREATE(CAUTODlg, CFormView)

CAUTODlg::CAUTODlg()
	: CFormView(IDD_AUTOGRAPH)
	, User_information(_T(""))
	, Publickey_Path(_T(""))
	, CA_privatepath(_T(""))
{

}

CAUTODlg::~CAUTODlg()
{
}

void CAUTODlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AUTEDIT1, User_information);
	DDX_Text(pDX, IDC_AUTEDIT2, Publickey_Path);
	DDX_Text(pDX, IDC_AUTOEDIT1, CA_privatepath);
}

BEGIN_MESSAGE_MAP(CAUTODlg, CFormView)
	ON_BN_CLICKED(IDC_AUTOBUTTON1, &CAUTODlg::OnBnClickedAutobutton1)
	ON_BN_CLICKED(IDC_AUTOBUTTON2, &CAUTODlg::OnBnClickedAutobutton2)
END_MESSAGE_MAP()


// CAUTODlg 诊断

#ifdef _DEBUG
void CAUTODlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAUTODlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAUTODlg 消息处理程序


void CAUTODlg::OnBnClickedAutobutton1()
{ 
	UpdateData(TRUE);
	std::string name,path;
	name=CT2A(User_information.GetString());
	path = CT2A(Publickey_Path.GetString());
	if(User_information.IsEmpty()|| Publickey_Path.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else
	{
		bool res1=F_ile::readFilename(name);
		bool res2=F_ile::readFilePubilcpath(path);
		if (!res2)
		{
			MessageBoxA(NULL, "The file is not a PEM file.", "Error", MB_OK | MB_ICONERROR);
		}
		else if (res1 && res2)
		{
			if (F_ile::combineFilesToNewFile(name, path))
			{
				MessageBox(TEXT("已经保存在此运行程序的目录下,申请认证成功"));
				RsaKeyGenerator keyGen(2048, RSA_F4);
				if (!keyGen.generateKeys()) {
					MessageBox(TEXT("生成失败"));
					return;
				}
				if (!keyGen.writePublicKey("public-1.pem")) {
					MessageBoxA(NULL, "公钥写入文件失败!", "错误", MB_OK | MB_ICONERROR);
					return;
				}
				if (!keyGen.writePrivateKey("private-1.pem")) {
					MessageBoxA(NULL, "私钥写入文件失败!", "错误", MB_OK | MB_ICONERROR);
					return;
				}
				MessageBoxA(NULL, "RSA密钥对已成功生成并保存！", "成功", MB_OK | MB_ICONINFORMATION);
				std::string privateKeyPath = keyGen.getPrivateKeyFilePath();
				CA_privatepath = privateKeyPath.c_str();
				UpdateData(FALSE);
				User_information.Empty();
				Publickey_Path.Empty();
				UpdateData(FALSE);

			}
			
		}
	}

}


void CAUTODlg::OnBnClickedAutobutton2()
{
	// TODO: 在此添加控件通知处理程序代码
	User_information.Empty();
	Publickey_Path.Empty();
	CA_privatepath.Empty();
	UpdateData(FALSE);
}
