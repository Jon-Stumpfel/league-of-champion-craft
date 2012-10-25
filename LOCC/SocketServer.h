#pragma once

#define NET_CONNECT			0x02
#define NET_QUIT			0x03
#define NET_INPUT_UP		0x03
#define NET_INPUT_DOWN		0x04
#define NET_INPUT_LEFT		0x05
#define NET_INPUT_RIGHT		0x06
#define NET_INPUT_ACCEPT	0x07
#define NET_INPUT_CANCEL	0x08
#define NET_INPUT_START		0x09

#define NET_YOUAREONE	0x35
#define NET_YOUARETWO	0x36

#define NET_BEGINMAP1	0x37
#define NET_BEGINMAP2	0x38
#define NET_BEGINMAP3	0x39
#define NET_BEGINMAP4	0x40
#define NET_BEGINMAP5	0x41

#define NET_HELLOWORLD		0x79
class CSocketServer
{


	static CSocketServer* s_Instance;
public:
	static CSocketServer* GetInstance(void);
	static void DeleteInstance(void);

	void Initialize(void);
	void Shutdown(void);

	bool GetListenThreadShutdown(void) { return m_bShutdownListenThread;}
	bool GetWorkThreadShutdown(void) { return m_bShutdownWorkThread;}
	int GetNumConnections(void);


public:
	SOCKET sockets[3];
	sockaddr_in server;
	sockaddr client[2];
	bool m_bShutdownListenThread;
	bool m_bShutdownWorkThread;
	int m_nNumConnections;

	HANDLE listenThread;
	HANDLE workThread1;
	HANDLE workThread2;

	DWORD threadID;
	DWORD workThread1ID;
	DWORD workThread2ID;
private:
	CSocketServer(void);
	~CSocketServer(void);
	CSocketServer(const CSocketServer&);
	CSocketServer& operator=(const CSocketServer&);
};


class CSocketClient
{
public:
	static CSocketClient* GetInstance(void);
	static void DeleteInstance(void);

	bool Initialize(unsigned char byte1 = 127, unsigned char byte2 = 0, unsigned char byte3 = 0, unsigned char byte4 = 1);
	void Shutdown(void);

	void Send(unsigned int byteCode);
	SOCKET m_sClientSocket;
	sockaddr_in m_tClientAddr;

	int m_nNetworkPlayerID;

private:
	static CSocketClient* s_Instance;

	CSocketClient(void);
	~CSocketClient(void);
	CSocketClient(const CSocketClient&);
	CSocketClient& operator=(const CSocketClient&);


};