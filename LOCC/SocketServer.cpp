#include "StdAfx.h"
#include "SocketServer.h"
#include "Game.h"
#include "MultiplayerState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#define WM_SOCKET WM_USER+1

CSocketServer* CSocketServer::s_Instance = nullptr;
CSocketClient* CSocketClient::s_Instance = nullptr;
CSocketServer::CSocketServer(void)
{
}


CSocketServer::~CSocketServer(void)
{
}
DWORD WINAPI workThreadWork1(LPVOID args);
DWORD WINAPI workThreadWork2(LPVOID args);
DWORD WINAPI listenThreadWork(LPVOID args)
{
	unsigned int nThreadRunCount = 0;
	while (!CSocketServer::GetInstance()->GetListenThreadShutdown())
	{
		int addr_size = sizeof(sockaddr);
		while (CSocketServer::GetInstance()->m_nNumConnections < 2)
		{
			OutputDebugString(L"Network: Beginning Accept\n");

			CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1] = accept
				(CSocketServer::GetInstance()->sockets[0], 
				&CSocketServer::GetInstance()->client[CSocketServer::GetInstance()->m_nNumConnections],
				&addr_size);
			sockaddr addrinfo;
			int namelen = sizeof(addrinfo);
			getpeername(CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1], &addrinfo, &namelen);
			OutputDebugString(L"Network: End Accept\n");

			if (CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1] == INVALID_SOCKET)
			{
				OutputDebugString(L"NetworkError: Unable to accept connection\n");
				WSACleanup();
				return 1;
			}
			else
			{
				OutputDebugString(L"Player connected\n");
				char buffer[500];
				sprintf_s(buffer, "%c%d", NET_CONNECT, CSocketServer::GetInstance()->m_nNumConnections+1);
				send(CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1], buffer, 2, 0);
				if (CSocketServer::GetInstance()->m_nNumConnections == 0)
				{
					char buffer[80];
					sprintf_s(buffer, "%c%d", NET_YOUAREONE, CSocketServer::GetInstance()->m_nNumConnections+1);
					send(CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1], buffer, 2, 0);
					CSocketServer::GetInstance()->workThread1 = CreateThread(NULL, 0, workThreadWork1, 0, 0, &CSocketServer::GetInstance()->workThread1ID);
				}
				else if (CSocketServer::GetInstance()->m_nNumConnections == 1)
				{
					char buffer[80];
					sprintf_s(buffer, "%c%d", NET_YOUARETWO, CSocketServer::GetInstance()->m_nNumConnections+1);
					send(CSocketServer::GetInstance()->sockets[CSocketServer::GetInstance()->m_nNumConnections+1], buffer, 2, 0);
					CSocketServer::GetInstance()->workThread2 = CreateThread(NULL, 0, workThreadWork2, 0, 0, &CSocketServer::GetInstance()->workThread2ID);
					CMultiplayerState::GetInstance()->PlayerConnected();
				}
				CSocketServer::GetInstance()->m_nNumConnections++;
				if (CSocketServer::GetInstance()->m_nNumConnections == 2)
				{
					OutputDebugString(L"Network: Max connections reached. Leaving Listen Thread...\n");
					return 1;
				}

			}
		}
	}
	std::wostringstream woss;
	woss << "Closing Thread: Final Count - " << nThreadRunCount << '\n';
	OutputDebugString((LPCWSTR)woss.str().c_str());
	return 1;
}

DWORD WINAPI workThreadWork1(LPVOID args)
{
	char buffer[80];
	while (!CSocketServer::GetInstance()->GetWorkThreadShutdown())
	{
		// process receives and send them to the other client
		int error = recv (CSocketServer::GetInstance()->sockets[1], buffer, 2, 0);
		if ((error == 0) || (error == INVALID_SOCKET))
		{
			CSocketServer::GetInstance()->Shutdown();
			CSocketClient::GetInstance()->Shutdown();
			return 10;
		}
		if ((buffer[0]==NET_HELLOWORLD))
		{
			OutputDebugString(L"Received Hello World from Player 1\n");
		}
		//if ((buffer[0]==NET_INPUT_UP))
		//{
		//	send(CSocketServer::GetInstance()->sockets[2], buffer, 2, 0);
		//	OutputDebugString(L"Server: Relaying NET_INPUT_UP to socket 2\n");
		//}

		send(CSocketServer::GetInstance()->sockets[2], buffer, 2, 0);

	}


	return 1;
}
DWORD WINAPI workThreadWork2(LPVOID args)
{
	char buffer[80];
	while (!CSocketServer::GetInstance()->GetWorkThreadShutdown())
	{
		// process receives and send them to the other client
		int error = recv (CSocketServer::GetInstance()->sockets[2], buffer, 2, 0);
		if ((error == 0) || (error == INVALID_SOCKET))
		{
			CSocketServer::GetInstance()->Shutdown();
			CSocketClient::GetInstance()->Shutdown();
			CStateStack::GetInstance()->Switch(CMainMenuState::GetInstance());
			return 10;
		}
		if ((buffer[0]==NET_HELLOWORLD))
		{
			OutputDebugString(L"Received Hello World from Player 2\n");
		}
		send(CSocketServer::GetInstance()->sockets[1], buffer, 2, 0);
		

	}


	return 1;
}
CSocketServer* CSocketServer::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CSocketServer();
	return s_Instance;
}
void CSocketServer::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}

void CSocketServer::Initialize(void)
{

	
	m_nNumConnections = 0;
	m_bShutdownListenThread = false;
	m_bShutdownWorkThread = false;
	WSADATA wsaData;

	int error = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (error != 0)
	{
		OutputDebugString(L"NetworkError: WSA Startup error\n");
		return;
	}

	if (wsaData.wVersion != 0x0202)
	{
		OutputDebugString(L"NetworkError: Wrong version of Winsock\n");
		return;
	}

	sockets[0] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.sin_family = AF_INET;
	server.sin_port = htons(44444);
	server.sin_addr.S_un.S_un_b.s_b1 = 127;
	server.sin_addr.S_un.S_un_b.s_b2 = 0;
	server.sin_addr.S_un.S_un_b.s_b3 = 0;
	server.sin_addr.S_un.S_un_b.s_b4 = 1;


	if (bind(sockets[0], (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
	{
		OutputDebugString(L"NetworkError: Unable to bind socket\n");
		WSACleanup();
		return;
	}

	if (listen(sockets[0], 15) == SOCKET_ERROR)
	{
		OutputDebugString(L"NetworkError: Unable to listen\n");
		WSACleanup();
		return;
	}

	OutputDebugString(L"Network: Listening for connections...\n");

	threadID = 0;
	listenThread = 0;

	int value = 10;
	listenThread = CreateThread(NULL, 0, listenThreadWork, &value, 0, &threadID);
	
}
void CSocketServer::Shutdown(void)
{
//	WaitForSingleObject(listenThread, 5000);
	m_bShutdownListenThread = true;
	m_bShutdownWorkThread = true;
	closesocket(sockets[0]);
	WSACleanup();
}





///////////////////////////////////////////
/// Socket client code
////////////////////////////////////////////

CSocketClient::CSocketClient(void)
{

}
CSocketClient::~CSocketClient(void)
{

}

CSocketClient* CSocketClient::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CSocketClient();
	return s_Instance;
}
void CSocketClient::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}


bool CSocketClient::Initialize(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4)
{
	WSADATA w;
	int error = WSAStartup(MAKEWORD(2,2), &w);
	if (error)
	{
		OutputDebugString(L"ClientError: Failure to startup WSA\n");
		return false;
	}

	if (w.wVersion != 0x0202)
	{
		OutputDebugString(L"ClientError: Wrong Winsock Version\n");
		return false;
	}

	m_sClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	WSAAsyncSelect(m_sClientSocket, CGame::GetInstance()->GetHWND(), WM_SOCKET, (FD_CLOSE | FD_CONNECT | FD_READ | FD_CONNECT));

	char a[16]="127.0.0.1";
	m_tClientAddr.sin_family = AF_INET;
	m_tClientAddr.sin_port = htons(44444);
	m_tClientAddr.sin_addr.S_un.S_un_b.s_b1 = byte1;
	m_tClientAddr.sin_addr.S_un.S_un_b.s_b2 = byte2;
	m_tClientAddr.sin_addr.S_un.S_un_b.s_b3 = byte3;
	m_tClientAddr.sin_addr.S_un.S_un_b.s_b4 = byte4;


	if (connect(m_sClientSocket, (LPSOCKADDR)&m_tClientAddr, sizeof(m_tClientAddr)) == SOCKET_ERROR)
	{

		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			OutputDebugString(L"ClientError: WSAEWOULDBLOCK, sleeping 750\n");
			Sleep(750);
			connect(m_sClientSocket, (LPSOCKADDR)&m_tClientAddr, sizeof(m_tClientAddr));
			return true;
		}
		std::wostringstream woss;
		woss << "ClientError: WSA Error: " << WSAGetLastError() << '\n';
		OutputDebugString((LPCWSTR)woss.str().c_str());
		return false;;
	}
	// if here, successfull connection


	return true;
}
void CSocketClient::Shutdown(void)
{
	closesocket(m_sClientSocket);
//	WSACleanup();
}

void CSocketClient::Send(unsigned int byteCode)
{
	char txtbuffer[80];
	sprintf_s(txtbuffer, "%c%d", NET_HELLOWORLD, 0);
	send(m_sClientSocket, txtbuffer, 2, 0);
	int x = 9;
}