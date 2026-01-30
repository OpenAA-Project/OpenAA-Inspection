/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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