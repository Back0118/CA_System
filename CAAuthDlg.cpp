// CAAuthDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "CAAuthDlg.h"
#include<string>
#include"file.h"
#include"Global.h"
#include "RSASignerVerifier.h"
#pragma warning(disable:4996)
// CAAuthDlg

IMPLEMENT_DYNCREATE(CAAuthDlg, CFormView)

CAAuthDlg::CAAuthDlg()
	: CFormView(IDD_AUTH)
	, AUTH_name(_T(""))
	, AUTH_privatekey(_T(""))
{

}

CAAuthDlg::~CAAuthDlg()
{
}

void CAAuthDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AUTHEDIT1, AUTH_name);
	DDX_Text(pDX, IDC_AUEDIT2, AUTH_privatekey);
}

BEGIN_MESSAGE_MAP(CAAuthDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CAAuthDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAAuthDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAAuthDlg 诊断

#ifdef _DEBUG
void CAAuthDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAAuthDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAAuthDlg 消息处理程序


void CAAuthDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::string name, path;
	name = CT2A(AUTH_name.GetString());
	path = CT2A(AUTH_privatekey.GetString());
	if (AUTH_name.IsEmpty()|| AUTH_privatekey.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else
	{
		bool res1 = F_ile::readFilename(name);
		bool res2 = F_ile::readFilePubilcpath(path);
		if (!res2)
		{
			MessageBoxA(NULL, "The file is not a PEM file.", "Error", MB_OK | MB_ICONERROR);
		}
		else if (res1 && res2)
		{
			RSASignerVerifier signerVerifier;
			Global glo;
			std::string outputName,user_Hash;
			F_ile::getNameFromFile(name,outputName);
			if (glo.userExists(outputName))
			{
				user_Hash=glo.getSHA256Hash(outputName);
				RSA* privateKey = signerVerifier.LoadPrivateKey(path);
				if (!privateKey) {
					MessageBox(TEXT("私钥加载失败"));
					return ;  // 如果加载私钥失败，退出
				}
				else
				{
					std::vector<unsigned char> signature = signerVerifier.SignHashWithPrivateKey(privateKey, user_Hash);
					signerVerifier.SaveSignatureToFile("signature.sig", signature);
					glo.signature = signature;
					MessageBox(TEXT("签名成功"));
				}
				RSA_free(privateKey);
				
			}

		}
		AUTH_name.Empty();
		AUTH_privatekey.Empty();
		UpdateData(FALSE);

	}
}


void CAAuthDlg::OnBnClickedCancel()
{
	AUTH_name.Empty();
	AUTH_privatekey.Empty();
	UpdateData(FALSE);
}
