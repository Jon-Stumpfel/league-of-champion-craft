#pragma once

typedef int MSGID;
class IMessage
{
public:
	IMessage(void);
	virtual ~IMessage(void) = 0;

	virtual MSGID	GetMessageID( void )	= 0 {};

private:

	IMessage( const IMessage& );
	IMessage& operator= ( const IMessage& );
};