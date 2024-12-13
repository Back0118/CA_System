// EN_File.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "EN_File.h"
#include "MD5Calculator.h"
#include"SystemInfo.h"
#include"AESFileDncryptor.h"
// EN_File

IMPLEMENT_DYNCREATE(EN_File, CFormView)

EN_File::EN_File()
	: CFormView(IDD_ENDIALOG1)
	, EN_Path(_T(""))
{

}

EN_File::~EN_File()
{
}

void EN_File::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENEDIT2, EN_Path);
}

BEGIN_MESSAGE_MAP(EN_File, CFormView)
	ON_BN_CLICKED(IDENOK, &EN_File::OnBnClickedEnok)
END_MESSAGE_MAP()


// EN_File 诊断

#ifdef _DEBUG
void EN_File::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EN_File::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// EN_File 消息处理程序


void EN_File::OnBnClickedEnok()
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
	std::string outputFile = "decrypted_file.txt";
	UpdateData(TRUE);
	path = CT2A(EN_Path.GetString());
	if (EN_Path.IsEmpty())
	{
		MessageBox(TEXT("输入内容不可为空"));
		return;
	}
	else{

		std::string iv = "abcdefabcdefabcd";
		AESFileDecryptor decryptor(md5Hash.substr(0,16), iv);

		bool success = decryptor.decryptFile(path, "decrypted_file.txt", md5Hash);
		if (success) {
			MessageBox(TEXT("文件解密成功！"));
		}
		else {
			MessageBox(TEXT("文件解密失败！"));
		}

		return ;
	}

}
