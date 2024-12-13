// EenDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "EenDlg.h"
#include<string>
#include"file.h"
#include "RSASignerVerifier.h"
#include"Global.h"
#pragma warning(disable:4996)

// EenDlg

IMPLEMENT_DYNCREATE(EenDlg, CFormView)

EenDlg::EenDlg()
	: CFormView(IDD_EenDlg)
	, Ver_name(_T(""))
	, CA_pulickey(_T(""))
{

}

EenDlg::~EenDlg()
{
}

void EenDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VEREDIT1, Ver_name);
	DDX_Text(pDX, IDC_VEREDIT2, CA_pulickey);
}

BEGIN_MESSAGE_MAP(EenDlg, CFormView)
	ON_BN_CLICKED(IDEenOK, &EenDlg::OnBnClickedEenok)
	ON_BN_CLICKED(IDEenCANCEL, &EenDlg::OnBnClickedEencancel)
END_MESSAGE_MAP()


// EenDlg 诊断

#ifdef _DEBUG
void EenDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EenDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// EenDlg 消息处理程序


void EenDlg::OnBnClickedEenok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::string name, path;
	name = CT2A(Ver_name.GetString());
	path = CT2A(CA_pulickey.GetString());
	if (Ver_name.IsEmpty() || CA_pulickey.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else {
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
			std::string outputName, user_Hash;
			F_ile::getNameFromFile(name, outputName);
			if (glo.userExists(outputName))
			{
				user_Hash = glo.getSHA256Hash(outputName);
				RSA* pubilickey = signerVerifier.LoadPublicKey(path);
				if (!pubilickey) {
					MessageBox(TEXT("公钥加载失败"));
					return;  // 如果加载私钥失败，退出
				}
				else {
					bool res=signerVerifier.VerifySignatureWithPublicKey(pubilickey, user_Hash, glo.signature);
					if (res)
					{
						MessageBox(TEXT("验证成功"));
					}
					else {
						MessageBox(TEXT("验证失败"));
					}
				}
				RSA_free(pubilickey);
			}
			else {
				MessageBox(TEXT("用户不存在"));
			}
		}
		Ver_name.Empty();
		CA_pulickey.Empty();
		UpdateData(FALSE);

	}

}


void EenDlg::OnBnClickedEencancel()
{
	Ver_name.Empty();
	CA_pulickey.Empty();
	UpdateData(FALSE);

}
