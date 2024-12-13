// CloginDlg.cpp: 实现文件
//

#include "pch.h"
#include "CA_System.h"
#include "afxdialogex.h"
#include "CloginDlg.h"


// CloginDlg 对话框

IMPLEMENT_DYNAMIC(CloginDlg, CDialogEx)

CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGIN, pParent)
	, c_user(_T(""))
	, c_pwd(_T(""))
{

}

CloginDlg::~CloginDlg()
{
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, c_user);
	DDX_Text(pDX, IDC_EDIT2, c_pwd);
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CloginDlg::OnBnClickedButton3)

	ON_BN_CLICKED(IDC_BUTTON2, &CloginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CloginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CloginDlg 消息处理程序



void CloginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}



void CloginDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	if (c_user.IsEmpty() || c_pwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	//获取正确的值
	//CInfoFile file

	CString name, pwd;
	name = "123";
	pwd = "123";
	{
		if (name == c_user)
		{
			if (pwd == c_pwd)
			{
				//关闭当前对话框
				CDialog::OnCancel(); 
			}
			else
			{
				MessageBox(TEXT("密码有误"));
			}
		}
		else
		{
			MessageBox(TEXT("没有此用户"));
		}
	}

}


void CloginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

}


BOOL CloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//默认登录信息
	CString name,pwd;
	c_user = name;
	c_pwd = pwd;
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CloginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CloginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();

	//退出程序
	exit(0);
}
