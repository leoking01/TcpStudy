
// TcpStudyServer.h : TcpStudyServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "ListeningSocket.h"       //  


// CTcpStudyServerApp:
// �йش����ʵ�֣������ TcpStudyServer.cpp
//

class CTcpStudyServerApp : public CWinAppEx
{
public:
	CTcpStudyServerApp();


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
	afx_msg void On32771_startServe();


	CListeningSocket* m_pSocket;
	BOOL statusOfSocketBeCreated ;
	afx_msg void On32772_closeServer();
	afx_msg void On32773_OnExit();
};

extern CTcpStudyServerApp theApp;
