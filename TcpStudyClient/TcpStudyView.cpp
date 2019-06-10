
// TcpStudyView.cpp : CTcpStudyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TcpStudy.h"
#endif

#include "TcpStudyDoc.h"
#include "TcpStudyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpStudyView

IMPLEMENT_DYNCREATE(CTcpStudyView, CView)

BEGIN_MESSAGE_MAP(CTcpStudyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTcpStudyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTcpStudyView 构造/析构

CTcpStudyView::CTcpStudyView()
{
	// TODO: 在此处添加构造代码

}

CTcpStudyView::~CTcpStudyView()
{
}

BOOL CTcpStudyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTcpStudyView 绘制

void CTcpStudyView::OnDraw(CDC* /*pDC*/)
{
	CTcpStudyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTcpStudyView 打印


void CTcpStudyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTcpStudyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTcpStudyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTcpStudyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTcpStudyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTcpStudyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTcpStudyView 诊断

#ifdef _DEBUG
void CTcpStudyView::AssertValid() const
{
	CView::AssertValid();
}

void CTcpStudyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTcpStudyDoc* CTcpStudyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTcpStudyDoc)));
	return (CTcpStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CTcpStudyView 消息处理程序
