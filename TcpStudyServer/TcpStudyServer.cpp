
// TcpStudyServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TcpStudyServer.h"
#include "MainFrm.h"

#include "TcpStudyServerDoc.h"
#include "TcpStudyServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpStudyServerApp

BEGIN_MESSAGE_MAP(CTcpStudyServerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CTcpStudyServerApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_32771, &CTcpStudyServerApp::On32771_startServe)
	ON_COMMAND(ID_32772, &CTcpStudyServerApp::On32772_closeServer)
	ON_COMMAND(ID_32773, &CTcpStudyServerApp::On32773_OnExit)
END_MESSAGE_MAP()


// CTcpStudyServerApp ����

CTcpStudyServerApp::CTcpStudyServerApp()
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
	SetAppID(_T("TcpStudyServer.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CTcpStudyServerApp ����

CTcpStudyServerApp theApp;


// CTcpStudyServerApp ��ʼ��

BOOL CTcpStudyServerApp::InitInstance()
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
		RUNTIME_CLASS(CTcpStudyServerDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CTcpStudyServerView));
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

int CTcpStudyServerApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CTcpStudyServerApp ��Ϣ�������


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
void CTcpStudyServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTcpStudyServerApp �Զ������/���淽��

void CTcpStudyServerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CTcpStudyServerApp::LoadCustomState()
{
}

void CTcpStudyServerApp::SaveCustomState()
{
}

// CTcpStudyServerApp ��Ϣ�������

/*
���л�����VS2015

����https://blog.csdn.net/orange_xxx/article/details/7276868�����˼��޸ģ�������ȫʵ��˫�������ͨ�ţ�

TCPͨ������

�������˲��裺
	�����׽��ֿ⣬�����׽���(WSAStartup()/socket())��
	���׽��ֵ�һ��IP��ַ��һ���˿���(bind())��
	���׽�������Ϊ����ģʽ�ȴ���������(listen())��
	�������󣬽����������󣬷���һ���µĶ�Ӧ�ڴ˴����ӵ��׽���(accept())��
	�÷��ص��׽��ֺͿͻ��˽���ͨ��(send()/recv())��
	���أ��ȴ���һ��������
	�ر��׽��֣��رռ��ص��׽��ֿ�(closesocket()/WSACleanup())��

�ͻ��˲��裺
	�����׽��ֿ⣬�����׽���(WSAStartup()/socket())��
	�������������������(connect())��
	�ͷ������˽���ͨ��(send()/recv())��
	�ر��׽��֣��رռ��ص��׽��ֿ�(closesocket()/WSACleanup())��
	--------------------- 
	���ߣ�nandejxy 
	��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/nandejxy/article/details/82874606 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/


//int main_startServe(int argc, char* argv[]);
int start_server( ) ;
void CTcpStudyServerApp::On32771_startServe()
{
	// TODO: �ڴ���������������
	if( 0 )
	{
		int portNum = 8000 ;
		m_pSocket = new CListeningSocket( this );
		statusOfSocketBeCreated =   m_pSocket->Create( portNum  ) ;

		if(  statusOfSocketBeCreated  )
		{
			if(  !m_pSocket->Listen( )  )
			{
				AfxMessageBox(_T("����ʧ��!" ));
			}
			else
			{
				AfxMessageBox(_T("�����ɹ�!"));
			}
		}
		else
		{
			AfxMessageBox(_T("socket����ʧ��!" ));
		}
	}


	AllocConsole();
	freopen  ( "conout$", "w",  stdout );
	int res = start_server( ) ;
	FreeConsole();
}

//
//#include <stdio.h>
//#include <stdlib.h>
//#include <winsock2.h>
//
//void ErrorHandling(char* message);
//
//int main_startServe(int argc, char* argv[])
//{
//	WSADATA wsaData;
//	SOCKET hServSock, hClntSock;        
//	SOCKADDR_IN servAddr, clntAddr;     
//
//	int szClntAddr;
//	char message[]="Hello World!";
//
//	if( 0 )
//	{
//		if(argc!=2) 
//		{
//			printf("Usage : %s <port>\n", argv[0]);
//			exit(1);
//		}
//	}
//
//
//	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
//		ErrorHandling("WSAStartup() error!"); 
//
//	hServSock=socket(PF_INET, SOCK_STREAM, 0);
//	if(hServSock==INVALID_SOCKET)
//		ErrorHandling("socket() error");
//
//	memset(&servAddr, 0, sizeof(servAddr));
//	servAddr.sin_family=AF_INET;
//	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
//	if( 0 )
//		servAddr.sin_port=htons(atoi(argv[1]));
//
//	servAddr.sin_port=htons( 9190  );
//
//	if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
//		ErrorHandling("bind() error");  
//
//	if(listen(hServSock, 5)==SOCKET_ERROR)
//		ErrorHandling("listen() error");
//
//	szClntAddr=sizeof(clntAddr);        
//	hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr,&szClntAddr);
//	if(hClntSock==INVALID_SOCKET)
//		ErrorHandling("accept() error");  
//
//	send(hClntSock, message, sizeof(message), 0);
//	closesocket(hClntSock);
//	closesocket(hServSock);
//	WSACleanup();
//
//	AfxMessageBox(  _T("��������ɹ���") ) ;
//
//	return 0;
//}
//
//void ErrorHandling(char* message)
//{
//	AfxMessageBox(  _T("��������ʧ��,��������") ) ;
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}
////--------------------- 
////	���ߣ�52_���ȵľ� 
////	��Դ��CSDN 
////ԭ�ģ�https://blog.csdn.net/qq_40194498/article/details/80245607 
////��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
//
//




void CTcpStudyServerApp::On32772_closeServer()
{
	// TODO: �ڴ���������������
}


void CTcpStudyServerApp::On32773_OnExit()
{
	// TODO: �ڴ���������������
	exit( 0 );
}




#include "winsock2.h"
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
using namespace std;

//int main(int argc, char* argv[])
int start_server( )
{
	const   int   BUF_SIZE = 64;
	WSADATA			wsd;			    //WSADATA����
	SOCKET			sServer;		    //�������׽���
	SOCKET			sClient;		    //�ͻ����׽���
	SOCKADDR_IN		servAddr;		    //��������ַ
	SOCKADDR_IN     clientAddr;         //�ͻ��˵�ַ
	char			bufSend[BUF_SIZE];	//�������ݻ�����
	char			bufRecv[BUF_SIZE];  //�������ݻ�����
	int				retVal;			    //����ֵ
	char*			closeSymbol = "0";  //����ͨ�ŵı�־

	// ������׽��ֵ�ַ 
	servAddr.sin_family = AF_INET;        //Э��
	servAddr.sin_port = htons(4999);      //�˿�
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		  //INADDR_ANY
	inet_pton(AF_INET, "127.0.0.1", (void*)&servAddr.sin_addr.S_un.S_addr);

	// ��ʼ���׽��ֶ�̬��	
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed !" << endl;
		return 1;
	}

	// ����������׽���
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		cout << "socket failed!" << endl;
		WSACleanup();			 //�ͷ��׽�����Դ;
		return  -1;
	}
	else
	{
		cout << "Server Socket init!" << endl;
		cout << "Server Socket IP: 127.0.0.1" << endl;
		cout << "Server Socket Port: 4999" << endl;
	}

	// �׽��ְ�IP�Ͷ˿�
	retVal = bind( sServer, (LPSOCKADDR)&servAddr, sizeof(SOCKADDR_IN)  );
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		closesocket(sServer);	//�رշ�����׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}
	else
	{
		cout << "Server Socket bind IP & Port !" << endl;
	}

	// ��ʼ������ǰ�׽��ֶ˿��Ƿ�������
	retVal = listen(sServer, 1);
	if (0 == retVal)
	{
		cout << "Server Socket is listening !" << endl;
	}
	else if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		closesocket(sServer);	//�رշ�����׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}
	else
	{
		cout << "One Client Socket is connecting !" << endl;

	}

	// ����ͻ��˷�����������ܿͻ��ˣ���ʼ�Ӹÿͻ��˶�ȡ����
	cout << "Server Socket is waiting accpetion !" << endl;
	int addrClientlen = sizeof(clientAddr);
	sClient = accept(sServer, (sockaddr FAR*)&clientAddr,  &addrClientlen);
	if (INVALID_SOCKET == sClient)
	{
		cout << "accept failed!" << endl;
		closesocket(sServer);	//�رշ�����׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}
	else
	{
		cout << "Two Sockets are ready for communication !" << endl;
	}

	// ѭ���ȴ�accept�Ķ˿ڷ������ݣ��ӿͻ��˽������� & ��ͻ��˷�������
	while (true) 
	{
		// ��ʼ������ռ�
		ZeroMemory(bufRecv, BUF_SIZE);

		// ���տͻ��˷��͵�buf��Ϣ
		retVal = recv(sClient, bufRecv, BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{// ����ʧ����رշ���˿ͻ����׽���
			cout << "recv failed!" << endl;
			closesocket(sServer);	//�رշ�����׽���
			WSACleanup();			//�ͷ��׽�����Դ;
			return -1;
		}

		// ȷ�Ͽͻ��˷��͵���Ϣ
		bufRecv[retVal] = '\0';			// ���յ����һλ��Ϊ\0���������̵�����
		cout << "Data recv from Client Socket: " << bufRecv << endl;
		// ���ͻ��˷��͵�������'0'�����ʾ�ͻ���������˴�TCPͨ��		
		if (!strcmp(bufRecv, closeSymbol))
		{
			cout << "Client Socket wants to finish this communication" << endl;
			break;
		}

		// ��sendBuf��Ϣ���͵��ͻ���
		cout << "Data send to Client Socket: ";
		cin >> bufSend;
		send(sClient, bufSend, strlen(bufSend), 0);
		// ������˷��͵�������'0'�����ʾ�����������˴�TCPͨ��	
		if (!strcmp(bufSend, closeSymbol))
		{
			cout << "Server Socket wants to finish this communication" << endl;
			break;
		}
	}
	// �˳�
	closesocket(sServer);	//�رշ�����׽���
	WSACleanup();			//�ͷ��׽�����Դ;
	Sleep(5000);
	return 0;
}