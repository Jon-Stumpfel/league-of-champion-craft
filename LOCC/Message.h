#pragma once
#include "StdAfx.h"
#include "imessage.h"


class CMessage : public IMessage
{
public:
	CMessage(MSG_TYPE msgID) { m_nMessageID = msgID;}
	virtual ~CMessage(void) { }

	virtual MSGID GetMessageID(void) { return m_nMessageID; };
private:
	MSGID	m_nMessageID;
};

