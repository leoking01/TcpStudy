
// TcpStudy.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TcpStudy.h"
#include "MainFrm.h"

#include "TcpStudyDoc.h"
#include "TcpStudyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpStudyApp

BEGIN_MESSAGE_MAP(CTcpStudyApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CTcpStudyApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_32771, &CTcpStudyApp::On32771_sendRequest)
END_MESSAGE_MAP()


// CTcpStudyApp ����

CTcpStudyApp::CTcpStudyApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TcpStudy.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CTcpStudyApp ����

CTcpStudyApp theApp;


// CTcpStudyApp ��ʼ��

BOOL CTcpStudyApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTcpStudyDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CTcpStudyView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CTcpStudyApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CTcpStudyApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CTcpStudyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTcpStudyApp �Զ������/���淽��

void CTcpStudyApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CTcpStudyApp::LoadCustomState()
{
}

void CTcpStudyApp::SaveCustomState()
{
}

// CTcpStudyApp ��Ϣ�������

//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <winsock2.h>
//void ErrorHandling(char* message);
//
//int main__tcp_client(int argc, char* argv[])
//{
//	WSADATA wsaData;
//	SOCKET hSocket;
//	SOCKADDR_IN servAddr;
//
//	char message[30];
//	int strLen=0;
//	int idx=0, readLen=0;
//
//	if( 0 )
//	{
//		if(argc!=3)
//		{
//			printf("Usage : %s <IP> <port>\n", argv[0]);
//			exit(1);
//		}
//	}
//
//
//	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		ErrorHandling("WSAStartup() error!");  
//
//	hSocket=socket(PF_INET, SOCK_STREAM, 0);
//	if(hSocket==INVALID_SOCKET)
//		ErrorHandling("hSocket() error");
//
//	memset(&servAddr, 0, sizeof(servAddr));
//	servAddr.sin_family=AF_INET;
//
//	//127.0.0.1 9190 
//	//servAddr.sin_addr.s_addr=inet_addr(argv[1]);
//	//servAddr.sin_port=htons(atoi(argv[2]));
//
//	char car[200];
//	sprintf( car, "%d.%d.%d.%d",  127,0,0,1   );
//
//
//	servAddr.sin_addr.s_addr=inet_addr(car );
//	servAddr.sin_port=htons(  9190  );
//
//
//	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR)
//		ErrorHandling("connect() error!");
//
//	while(readLen=recv(hSocket, &message[idx++], 1, 0))
//	{
//		if(readLen==-1)
//			ErrorHandling("read() error!");
//
//		strLen+=readLen;
//	}
//
//	printf("Message from server: %s \n", message);  
//	printf("Function read call count: %d \n", strLen);
//
//	closesocket(hSocket);
//	WSACleanup();
//	AfxMessageBox( _T( "���ӳɹ������ͳɹ���"));
//
//	return 0;
//}
//
//void ErrorHandling(char* message)
//{
//	AfxMessageBox( _T( "������������ʧ�ܣ��˳�����"));
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}


//--------------------- 
//	���ߣ�52_���ȵľ� 
//	��Դ��CSDN 
//ԭ�ģ�https://blog.csdn.net/qq_40194498/article/details/80245607 
//��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�

int start_request( ) ;
void CTcpStudyApp::On32771_sendRequest()
{
	// TODO: �ڴ���������������
	//main__tcp_client( 0,   NULL );
	// TODO: �ڴ���������������
	AllocConsole();
	freopen  ( "conout$", "w",  stdout );
	int  res = start_request( ) ;

	FreeConsole();
}



// Client.cpp : Defines the entry point for the console application.
#include "winsock2.h"
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

//int main(int argc, char* argv[])
int start_request( )
{
	const int BUF_SIZE = 64;
	WSADATA			wsd;				//WSADATA����
	SOCKET			sClient;			//�ͻ����׽���
	SOCKADDR_IN		servAddr;			//��������ַ
	char			bufSend[BUF_SIZE];	//�������ݻ�����
	char			bufRecv[BUF_SIZE];  //�������ݻ�����
	int				retVal;				//����ֵ
	char*			closeSymbol = "0";//����ͨ�ŵı�־

	// ���÷���˵�ַ
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", (void*)&servAddr.sin_addr.S_un.S_addr);
	servAddr.sin_port = htons((short)4999);
	int	nServAddlen = sizeof(servAddr);

	// ��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}

	// ����������׽���
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sClient)
	{
		cout << "Socket failed !" << endl;
		WSACleanup();               //�ͷ��׽�����Դ
		return  -1;
	}
	else
	{
		cout << "Client Socket init !" << endl;
	}

	// �ͻ���socket���ӷ����
	retVal = connect(sClient, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		closesocket(sClient);	//�ر��׽���
		WSACleanup();			//�ͷ��׽�����Դ
		return -1;
	}
	else
	{
		cout << "Two Sockets are ready for communication !" << endl;
	}

	// ѭ���ȴ��������˷������� & �ӷ���˽�������
	while (true) {
		// ��ʼ��buf�ռ�
		ZeroMemory(bufSend, BUF_SIZE);

		// �����˷�������buf
		cout << "Data send to Server Socket: "<<endl;
		//cin >> bufSend;
		bufSend[0]= 'a';
		bufSend[1]= 'b';
		bufSend[2]= 'c';
		//std::endl>> bufSend;
		retVal = send(sClient, bufSend, strlen(bufSend), 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			closesocket(sClient);	//�رշ�����׽���
			WSACleanup();		    //�ͷ��׽�����Դ
			return -1;
		}
		// ���ͻ��˷��͵�������'0'�����ʾ�ͻ���������˴�TCPͨ��
		if (!strcmp(bufSend, closeSymbol))
		{
			cout << "Client Socket wants to finish this communication" << endl;
			break;
		}

		// �ӷ���˽�������bufRecv
		retVal = recv(sClient, bufRecv, BUF_SIZE, 0);
		bufRecv[retVal] = '\0';
		cout << "Data recv from Server Socket: " << bufRecv << endl;
		// ������˷��͵�������'0'�����ʾ�����������˴�TCPͨ��		
		if (!strcmp(bufRecv, closeSymbol))
			//if (bufRecv[0] == '0')
		{
			cout << "Server Socket wants to finish this communication" << endl;
			break;
		}

	}
	//�˳�
	closesocket(sClient);	//�رշ�����׽���
	WSACleanup();		
	//�ͷ��׽�����Դ
	Sleep(5000);
	return 0;
}