
// CA_SystemView.cpp: CCASystemView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CA_System.h"
#endif

#include "CA_SystemDoc.h"
#include "CA_SystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCASystemView

IMPLEMENT_DYNCREATE(CCASystemView, CView)

BEGIN_MESSAGE_MAP(CCASystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCASystemView 构造/析构

CCASystemView::CCASystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCASystemView::~CCASystemView()
{
}

BOOL CCASystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCASystemView 绘图

void CCASystemView::OnDraw(CDC* /*pDC*/)
{
	CCASystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCASystemView 打印

BOOL CCASystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCASystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCASystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCASystemView 诊断

#ifdef _DEBUG
void CCASystemView::AssertValid() const
{
	CView::AssertValid();
}

void CCASystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCASystemDoc* CCASystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCASystemDoc)));
	return (CCASystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CCASystemView 消息处理程序
