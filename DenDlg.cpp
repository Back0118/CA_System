// DenDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "DenDlg.h"
#include"SystemInfo.h"
#include<string>
#include "MD5Calculator.h"
#include "AESFileEncryptor.h"

// DenDlg



IMPLEMENT_DYNCREATE(DenDlg, CFormView)

DenDlg::DenDlg()
	: CFormView(IDD_DenDlg)
	, FlieCr_Path(_T(""))
{

}

DenDlg::~DenDlg()
{
}

void DenDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, FlieCr_Path);
}

BEGIN_MESSAGE_MAP(DenDlg, CFormView)
	ON_BN_CLICKED(IDC_FLEPRBUTTON1, &DenDlg::OnBnClickedFleprbutton1)
END_MESSAGE_MAP()


// DenDlg 诊断

#ifdef _DEBUG
void DenDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DenDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DenDlg 消息处理程序


void DenDlg::OnBnClickedFleprbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SystemInfo sysInfo;
	MD5Calculator md5Calc;
	std::wstring resr = sysInfo.ShowInfo();;
	std::string res(resr.begin(), resr.end());
	MessageBox(resr.c_str());
	std::string md5Hash = md5Calc.computeMD5(res);
	std::wstring md5HashWStr = md5Calc.md5stringToWString(md5Hash);
	MessageBox(md5HashWStr.c_str());
	std::string path;
	std::string outputFile = "output.enc";
	UpdateData(TRUE);
	path=CT2A(FlieCr_Path.GetString());
	if (FlieCr_Path.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else
	{
		std::string iv = "abcdefabcdefabcd";
		AESFileEncryptor encryptor(md5Hash.substr(0,16), iv);
		if (encryptor.encryptFile(path, outputFile,md5Hash)) {
			MessageBox(TEXT("文件加密成功！"));
			FlieCr_Path.Empty();
			UpdateData(FALSE);
		}
		else {
			MessageBox(TEXT("文件加密失败！"));
			FlieCr_Path.Empty();
			UpdateData(FALSE);
		}

	}
}
