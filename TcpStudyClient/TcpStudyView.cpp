
// TcpStudyView.cpp : CTcpStudyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTcpStudyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTcpStudyView ����/����

CTcpStudyView::CTcpStudyView()
{
	// TODO: �ڴ˴���ӹ������

}

CTcpStudyView::~CTcpStudyView()
{
}

BOOL CTcpStudyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTcpStudyView ����

void CTcpStudyView::OnDraw(CDC* /*pDC*/)
{
	CTcpStudyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTcpStudyView ��ӡ


void CTcpStudyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTcpStudyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTcpStudyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTcpStudyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CTcpStudyView ���

#ifdef _DEBUG
void CTcpStudyView::AssertValid() const
{
	CView::AssertValid();
}

void CTcpStudyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTcpStudyDoc* CTcpStudyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTcpStudyDoc)));
	return (CTcpStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CTcpStudyView ��Ϣ�������
