
// TcpStudy.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_32771, &CTcpStudyApp::On32771_sendRequest)
END_MESSAGE_MAP()


// CTcpStudyApp 构造

CTcpStudyApp::CTcpStudyApp()
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
	SetAppID(_T("TcpStudy.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CTcpStudyApp 对象

CTcpStudyApp theApp;


// CTcpStudyApp 初始化

BOOL CTcpStudyApp::InitInstance()
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
		RUNTIME_CLASS(CTcpStudyDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CTcpStudyView));
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

int CTcpStudyApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CTcpStudyApp 消息处理程序


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
void CTcpStudyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTcpStudyApp 自定义加载/保存方法

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

// CTcpStudyApp 消息处理程序

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
//	AfxMessageBox( _T( "连接成功，发送成功。"));
//
//	return 0;
//}
//
//void ErrorHandling(char* message)
//{
//	AfxMessageBox( _T( "发生错误，连接失败，退出程序。"));
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}


//--------------------- 
//	作者：52_赫兹的鲸 
//	来源：CSDN 
//原文：https://blog.csdn.net/qq_40194498/article/details/80245607 
//版权声明：本文为博主原创文章，转载请附上博文链接！

int start_request( ) ;
void CTcpStudyApp::On32771_sendRequest()
{
	// TODO: 在此添加命令处理程序代码
	//main__tcp_client( 0,   NULL );
	// TODO: 在此添加命令处理程序代码
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
	WSADATA			wsd;				//WSADATA变量
	SOCKET			sClient;			//客户端套接字
	SOCKADDR_IN		servAddr;			//服务器地址
	char			bufSend[BUF_SIZE];	//发送数据缓冲区
	char			bufRecv[BUF_SIZE];  //接收数据缓冲区
	int				retVal;				//返回值
	char*			closeSymbol = "0";//结束通信的标志

	// 设置服务端地址
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", (void*)&servAddr.sin_addr.S_un.S_addr);
	servAddr.sin_port = htons((short)4999);
	int	nServAddlen = sizeof(servAddr);

	// 初始化套接字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}

	// 创建服务端套接字
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sClient)
	{
		cout << "Socket failed !" << endl;
		WSACleanup();               //释放套接字资源
		return  -1;
	}
	else
	{
		cout << "Client Socket init !" << endl;
	}

	// 客户端socket连接服务端
	retVal = connect(sClient, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		closesocket(sClient);	//关闭套接字
		WSACleanup();			//释放套接字资源
		return -1;
	}
	else
	{
		cout << "Two Sockets are ready for communication !" << endl;
	}

	// 循环等待，向服务端发送数据 & 从服务端接收数据
	while (true) {
		// 初始化buf空间
		ZeroMemory(bufSend, BUF_SIZE);

		// 向服务端发送数据buf
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
			closesocket(sClient);	//关闭服务端套接字
			WSACleanup();		    //释放套接字资源
			return -1;
		}
		// 若客户端发送的数据是'0'，则表示客户端想结束此次TCP通信
		if (!strcmp(bufSend, closeSymbol))
		{
			cout << "Client Socket wants to finish this communication" << endl;
			break;
		}

		// 从服务端接收数据bufRecv
		retVal = recv(sClient, bufRecv, BUF_SIZE, 0);
		bufRecv[retVal] = '\0';
		cout << "Data recv from Server Socket: " << bufRecv << endl;
		// 若服务端发送的数据是'0'，则表示服务端想结束此次TCP通信		
		if (!strcmp(bufRecv, closeSymbol))
			//if (bufRecv[0] == '0')
		{
			cout << "Server Socket wants to finish this communication" << endl;
			break;
		}

	}
	//退出
	closesocket(sClient);	//关闭服务端套接字
	WSACleanup();		
	//释放套接字资源
	Sleep(5000);
	return 0;
}