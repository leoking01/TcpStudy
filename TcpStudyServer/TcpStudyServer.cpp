
// TcpStudyServer.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_32771, &CTcpStudyServerApp::On32771_startServe)
	ON_COMMAND(ID_32772, &CTcpStudyServerApp::On32772_closeServer)
	ON_COMMAND(ID_32773, &CTcpStudyServerApp::On32773_OnExit)
END_MESSAGE_MAP()


// CTcpStudyServerApp 构造

CTcpStudyServerApp::CTcpStudyServerApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TcpStudyServer.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CTcpStudyServerApp 对象

CTcpStudyServerApp theApp;


// CTcpStudyServerApp 初始化

BOOL CTcpStudyServerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTcpStudyServerDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CTcpStudyServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}

int CTcpStudyServerApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CTcpStudyServerApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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

// 用于运行对话框的应用程序命令
void CTcpStudyServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTcpStudyServerApp 自定义加载/保存方法

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

// CTcpStudyServerApp 消息处理程序

/*
运行环境：VS2015

基于https://blog.csdn.net/orange_xxx/article/details/7276868做出了简单修改，可以完全实现双向的数据通信；

TCP通信流程

服务器端步骤：
	加载套接字库，创建套接字(WSAStartup()/socket())；
	绑定套接字到一个IP地址和一个端口上(bind())；
	将套接字设置为监听模式等待连接请求(listen())；
	请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字(accept())；
	用返回的套接字和客户端进行通信(send()/recv())；
	返回，等待另一连接请求；
	关闭套接字，关闭加载的套接字库(closesocket()/WSACleanup())。

客户端步骤：
	加载套接字库，创建套接字(WSAStartup()/socket())；
	向服务器发出连接请求(connect())；
	和服务器端进行通信(send()/recv())；
	关闭套接字，关闭加载的套接字库(closesocket()/WSACleanup())。
	--------------------- 
	作者：nandejxy 
	来源：CSDN 
原文：https://blog.csdn.net/nandejxy/article/details/82874606 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/


//int main_startServe(int argc, char* argv[]);
int start_server( ) ;
void CTcpStudyServerApp::On32771_startServe()
{
	// TODO: 在此添加命令处理程序代码
	if( 0 )
	{
		int portNum = 8000 ;
		m_pSocket = new CListeningSocket( this );
		statusOfSocketBeCreated =   m_pSocket->Create( portNum  ) ;

		if(  statusOfSocketBeCreated  )
		{
			if(  !m_pSocket->Listen( )  )
			{
				AfxMessageBox(_T("侦听失败!" ));
			}
			else
			{
				AfxMessageBox(_T("侦听成功!"));
			}
		}
		else
		{
			AfxMessageBox(_T("socket创建失败!" ));
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
//	AfxMessageBox(  _T("开启服务成功。") ) ;
//
//	return 0;
//}
//
//void ErrorHandling(char* message)
//{
//	AfxMessageBox(  _T("开启服务失败,发生错误。") ) ;
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}
////--------------------- 
////	作者：52_赫兹的鲸 
////	来源：CSDN 
////原文：https://blog.csdn.net/qq_40194498/article/details/80245607 
////版权声明：本文为博主原创文章，转载请附上博文链接！
//
//




void CTcpStudyServerApp::On32772_closeServer()
{
	// TODO: 在此添加命令处理程序代码
}


void CTcpStudyServerApp::On32773_OnExit()
{
	// TODO: 在此添加命令处理程序代码
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
	WSADATA			wsd;			    //WSADATA变量
	SOCKET			sServer;		    //服务器套接字
	SOCKET			sClient;		    //客户端套接字
	SOCKADDR_IN		servAddr;		    //服务器地址
	SOCKADDR_IN     clientAddr;         //客户端地址
	char			bufSend[BUF_SIZE];	//发送数据缓冲区
	char			bufRecv[BUF_SIZE];  //接收数据缓冲区
	int				retVal;			    //返回值
	char*			closeSymbol = "0";  //结束通信的标志

	// 服务端套接字地址 
	servAddr.sin_family = AF_INET;        //协议
	servAddr.sin_port = htons(4999);      //端口
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		  //INADDR_ANY
	inet_pton(AF_INET, "127.0.0.1", (void*)&servAddr.sin_addr.S_un.S_addr);

	// 初始化套接字动态库	
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed !" << endl;
		return 1;
	}

	// 创建服务端套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		cout << "socket failed!" << endl;
		WSACleanup();			 //释放套接字资源;
		return  -1;
	}
	else
	{
		cout << "Server Socket init!" << endl;
		cout << "Server Socket IP: 127.0.0.1" << endl;
		cout << "Server Socket Port: 4999" << endl;
	}

	// 套接字绑定IP和端口
	retVal = bind( sServer, (LPSOCKADDR)&servAddr, sizeof(SOCKADDR_IN)  );
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		closesocket(sServer);	//关闭服务端套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	else
	{
		cout << "Server Socket bind IP & Port !" << endl;
	}

	// 开始监听当前套接字端口是否有数据
	retVal = listen(sServer, 1);
	if (0 == retVal)
	{
		cout << "Server Socket is listening !" << endl;
	}
	else if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		closesocket(sServer);	//关闭服务端套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	else
	{
		cout << "One Client Socket is connecting !" << endl;

	}

	// 如果客户端发送请求，则接受客户端，开始从该客户端读取数据
	cout << "Server Socket is waiting accpetion !" << endl;
	int addrClientlen = sizeof(clientAddr);
	sClient = accept(sServer, (sockaddr FAR*)&clientAddr,  &addrClientlen);
	if (INVALID_SOCKET == sClient)
	{
		cout << "accept failed!" << endl;
		closesocket(sServer);	//关闭服务端套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	else
	{
		cout << "Two Sockets are ready for communication !" << endl;
	}

	// 循环等待accept的端口发送数据，从客户端接收数据 & 向客户端发送数据
	while (true) 
	{
		// 初始化缓冲空间
		ZeroMemory(bufRecv, BUF_SIZE);

		// 接收客户端发送的buf信息
		retVal = recv(sClient, bufRecv, BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{// 接收失败则关闭服务端客户端套接字
			cout << "recv failed!" << endl;
			closesocket(sServer);	//关闭服务端套接字
			WSACleanup();			//释放套接字资源;
			return -1;
		}

		// 确认客户端发送的信息
		bufRecv[retVal] = '\0';			// 接收的最后一位设为\0，避免烫烫的问题
		cout << "Data recv from Client Socket: " << bufRecv << endl;
		// 若客户端发送的数据是'0'，则表示客户端想结束此次TCP通信		
		if (!strcmp(bufRecv, closeSymbol))
		{
			cout << "Client Socket wants to finish this communication" << endl;
			break;
		}

		// 将sendBuf信息发送到客户端
		cout << "Data send to Client Socket: ";
		cin >> bufSend;
		send(sClient, bufSend, strlen(bufSend), 0);
		// 若服务端发送的数据是'0'，则表示服务端想结束此次TCP通信	
		if (!strcmp(bufSend, closeSymbol))
		{
			cout << "Server Socket wants to finish this communication" << endl;
			break;
		}
	}
	// 退出
	closesocket(sServer);	//关闭服务端套接字
	WSACleanup();			//释放套接字资源;
	Sleep(5000);
	return 0;
}