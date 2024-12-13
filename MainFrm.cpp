// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CA_System.h"
#include "MainFrm.h"
#include"CASelectview.h"
#include"CA_Displayview.h"
#include"CAUTODlg.h"
#include"CAAuthDlg.h"
#include"ELIMINATEDlg.h"
#include"DenDlg.h"
#include"EenDlg.h"
#include"EN_File.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(NM_A,OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	ON_MESSAGE(NM_F, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

void CMainFrame::SwitchView(CRuntimeClass* pNewViewClass)
{
	CCreateContext Context;
	Context.m_pNewViewClass = pNewViewClass;
	Context.m_pCurrentFrame = this;
	Context.m_pLastView = (CFormView*)c_spliter.GetPane(0, 1);
	c_spliter.DeleteView(0, 1);
	c_spliter.CreateView(0, 1, pNewViewClass, CSize(600, 500), &Context);

	CFormView* pNewView = (CFormView*)c_spliter.GetPane(0, 1);
	c_spliter.RecalcLayout();
	pNewView->OnInitialUpdate();
	c_spliter.SetActivePane(0, 1);
}


// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//设置图标，拿图标资源就行
//SetClassLong()
	//右侧标题
	SetTitle(TEXT("414Back开发"));
	//设置窗口大小
	MoveWindow(0, 0, 800, 500);
	//设置居中显示
	CenterWindow();
	return 0;
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	c_spliter.CreateStatic(this, 1, 2);
	c_spliter.CreateView(0, 0, RUNTIME_CLASS(CASelectview), CSize(200, 500), pContext);
	c_spliter.CreateView(0, 1, RUNTIME_CLASS(CA_Displayview), CSize(600, 500), pContext);
	//拆成1行两类
	return TRUE;
}


LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_A:
		SwitchView(RUNTIME_CLASS(CAUTODlg)); 
		break;
	case NM_B:
		SwitchView(RUNTIME_CLASS(CAAuthDlg));  
		break;
	case NM_C:
		SwitchView(RUNTIME_CLASS(ELIMINATEDlg));
		break;
	case NM_D:
		SwitchView(RUNTIME_CLASS(EenDlg));
		break;
	case NM_E:
		SwitchView(RUNTIME_CLASS(DenDlg));
	    break;
	case NM_F:
		SwitchView(RUNTIME_CLASS(EN_File));
		break;
	}
	
	return 0;
}
