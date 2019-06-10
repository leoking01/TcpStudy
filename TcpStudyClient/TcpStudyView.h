
// TcpStudyView.h : CTcpStudyView ��Ľӿ�
//

#pragma once


class CTcpStudyView : public CView
{
protected: // �������л�����
	CTcpStudyView();
	DECLARE_DYNCREATE(CTcpStudyView)

// ����
public:
	CTcpStudyDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTcpStudyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TcpStudyView.cpp �еĵ��԰汾
inline CTcpStudyDoc* CTcpStudyView::GetDocument() const
   { return reinterpret_cast<CTcpStudyDoc*>(m_pDocument); }
#endif

