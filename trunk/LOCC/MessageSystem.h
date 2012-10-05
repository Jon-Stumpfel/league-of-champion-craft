#pragma once

class IMessage;

typedef void (*MESSAGEPROC)(IMessage*);

class CMessageSystem
{

public:

	static CMessageSystem* GetInstance( void );

	int GetNumMessage( void ) const { return (int)m_qMsgQueue.size(); }

	void InitMessageSystem( MESSAGEPROC MsgProc );
	void SendMessage( IMessage* pMsg );
	void ProcessMessages( void );
	void ClearMessages( void );
	void ShutdownMessageSystem( void );

private:

	CMessageSystem(void);
	CMessageSystem( CMessageSystem& );
	CMessageSystem* operator=( CMessageSystem& );
	~CMessageSystem(void);

	static CMessageSystem* s_Instance;

	std::queue< IMessage* > m_qMsgQueue;
	MESSAGEPROC m_nMsgProc;

};

