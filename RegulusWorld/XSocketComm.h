#pragma once

#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include <QBuffer>

class RegulusWorld;

#pragma	pack(push,1)
struct	RWTxRxLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
	int32		ErrorCode;
	int32		IDForUndo;
	int16		EmitterNameLen;
	BYTE		ClassNameLen;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;
};

#pragma	pack(pop)

class	RWRecList : public NPList<RWRecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;
	int16		EmitterNameLen;
	int16		ClassNameLen;
	int32		IDForUndo;
	int32		ErrorCode;
	BYTE		ErrorLevel;
	BYTE		ErrorMessageLen;
	BYTE		ErrorTimeLen;

	RWRecList(int len);
	~RWRecList(void);


	BYTE	*GetClassNamePointer(char CmdEmitterNameBuff[] ,char CmdClassBuff[] ,int maxByte);
	BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};

class	RWTxList : public NPList<RWTxList>
{
public:
	int32	Len;
	BYTE	*Data;

	RWTxList(int len , BYTE *data);
	~RWTxList(void);
};

//================================================================

class	RWPacketBase : public NPList<RWPacketBase> 
{
	friend	class RegulusWorld;

	RegulusWorld	*Base;
public:
	enum		CautionLevel{
					 _None		=0		//No error
					,_Critical	=1		//stop system
					,_Important	=2		//die something for function, thread
					,_Alart		=3		//Never die , light level error
					,_Message	=4		//pure message
	};

private:
	bool	SentRealSocket;
	QString EmitterName;
	QString	ClassName;
	RWPacketBase	*SendBackPacket;

	ErrorCodeList	ErrorData;
	int32	IDForUndo;

	bool	Received;
	bool	FromMaster;
public:

	RWPacketBase(RegulusWorld *base,const QString &EmitterName ,const QString &className);
	virtual	~RWPacketBase(void);

	virtual	bool	Load(QIODevice *f)=0;
	virtual	bool	Save(QIODevice *f)=0;
	virtual	QByteArray	*GetSaveArray(void){	return NULL;	}

	virtual	void	Receive(int cmd ,const QString &EmitterName ,int ClientID)=0;	

	bool	Send(RWPacketBase *parent ,int32 cmd ,int OwnID=-1);
	bool	Send(int32 cmd ,RWPacketBase &AckPacket ,int OwnID=-1,int32 MaxWaitMiliSec=10000);
	//bool	SendFromSlaveToMaster(int32 cmd);

	bool	IsReceived(void)		const	{	return(Received);	}
	void	ClearReceivedFlag(void)			{	Received=false;		}
	RWPacketBase	*GetSendBackPacket(void)	const	{	return SendBackPacket;	}

	bool	WaitForReadyRead(int OwnID,int milisec);

	void	SetError(int errorCode=0 ,const QString &errorMessage=/**/"" ,ErrorCodeList::CautionLevel level=ErrorCodeList::_None);
	void	SetError(const ErrorCodeList &ErrorData);
	void	AddErrorDataToSystem(ErrorCodeList &ErrorData);

	bool	GetReceived(void)		const	{	return Received;	}
	void	SetReceived(bool b)				{	Received=b;			}
	bool	GetFromMaster(void)		const	{	return FromMaster;	}
	void	SetFromMaster(bool b)			{	FromMaster=b;		}

protected:
	void	PopupPacketPriority(void);
};

#define	GetRWSendBack(typeclass,base,emitterName)	(typeclass *)((GetSendBackPacket()==NULL)?new typeclass(base,emitterName) : GetSendBackPacket())
#define	CloseRWSendBack(typedata)				if(GetSendBackPacket()==NULL){	delete	typedata;	}
