
// TcpStudy.h : TcpStudy Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTcpStudyApp:
// �йش����ʵ�֣������ TcpStudy.cpp
//

class CTcpStudyApp : public CWinAppEx
{
public:
	CTcpStudyApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void On32771_sendRequest();
};

extern CTcpStudyApp theApp;
