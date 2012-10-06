#include "StdAfx.h"
#include "MessageSystem.h"
#include "IMessage.h"

CMessageSystem* CMessageSystem::s_Instance = nullptr;


CMessageSystem::CMessageSystem(void)
{
}


CMessageSystem::~CMessageSystem(void)
{
}

CMessageSystem* CMessageSystem::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CMessageSystem();

	return s_Instance;
}
void CMessageSystem::DeleteInstance(void)
	{
		if (s_Instance != nullptr)
		{
			s_Instance->ShutdownMessageSystem();
			delete s_Instance;
		}
		s_Instance = nullptr;
	}
void CMessageSystem::InitMessageSystem( MESSAGEPROC MsgProc )
{
	if ( MsgProc == nullptr )
		return;

	m_nMsgProc = MsgProc;
}

void CMessageSystem::SendMessage( IMessage* pMsg )
{
	if ( pMsg == nullptr )
		return;

	m_qMsgQueue.push( pMsg );
}

void CMessageSystem::ProcessMessages( void )
{
	if( m_nMsgProc == nullptr )
		return;

	while( m_qMsgQueue.empty() == false )
	{
		m_nMsgProc( m_qMsgQueue.front() );
		delete m_qMsgQueue.front();
		m_qMsgQueue.pop();
	}
}

void CMessageSystem::ClearMessages( void )
{
	while( m_qMsgQueue.empty() == false )
	{
		delete m_qMsgQueue.front();
		m_qMsgQueue.pop();
	}
}

void CMessageSystem::ShutdownMessageSystem( void )
{
	ClearMessages();
	m_nMsgProc = nullptr;
}