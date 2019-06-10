
// TcpStudyServerView.cpp : CTcpStudyServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TcpStudyServer.h"
#endif

#include "TcpStudyServerDoc.h"
#include "TcpStudyServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpStudyServerView

IMPLEMENT_DYNCREATE(CTcpStudyServerView, CView)

BEGIN_MESSAGE_MAP(CTcpStudyServerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTcpStudyServerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTcpStudyServerView ����/����

CTcpStudyServerView::CTcpStudyServerView()
{
	// TODO: �ڴ˴���ӹ������

}

CTcpStudyServerView::~CTcpStudyServerView()
{
}

BOOL CTcpStudyServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTcpStudyServerView ����

void CTcpStudyServerView::OnDraw(CDC* /*pDC*/)
{
	CTcpStudyServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTcpStudyServerView ��ӡ


void CTcpStudyServerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTcpStudyServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTcpStudyServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTcpStudyServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CTcpStudyServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTcpStudyServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTcpStudyServerView ���

#ifdef _DEBUG
void CTcpStudyServerView::AssertValid() const
{
	CView::AssertValid();
}

void CTcpStudyServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTcpStudyServerDoc* CTcpStudyServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTcpStudyServerDoc)));
	return (CTcpStudyServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CTcpStudyServerView ��Ϣ�������
