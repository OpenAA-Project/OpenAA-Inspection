/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDirectCommPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDIRECTCOMMPACKET_H)
#define	XDIRECTCOMMPACKET_H

#include <QtGui>
//#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XGUIDirectMessage.h"

class	SystemConnectionInfo : public NPList<SystemConnectionInfo>
{
	int32	ID;
	QString	IPAddress;
	int32	GlobalPage;
public:
	SystemConnectionInfo(void){	ID=0;	GlobalPage=-1;	}
	SystemConnectionInfo(int32 globalPage ,int32 id ,const QString &ipAddress);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	int32	GetID(void)					const{	return ID;	}
	const QString	&GetIPAddress(void)	const{	return IPAddress;	}
	int32	GetGlobalPage(void)			const{	return GlobalPage;	}
};

class	SystemConnectionInfoContainer : public NPListPack<SystemConnectionInfo>
{
public:
	int32		WaitingTimeToConnect;

	SystemConnectionInfoContainer(void){	WaitingTimeToConnect=5000;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	SystemConnectionInfo	*GetInfo(int ID)	const;

	SystemConnectionInfoContainer	&operator=(SystemConnectionInfoContainer &src);
};

//=================================================================

class	DirectCommPacketBase : public NPList<DirectCommPacketBase> ,public GUIDirectMessage,public ServiceForLayers
{
	friend	class	LayersBase;
protected:
	bool	SentRealSocket;
	bool	FromMaster;
	QString EmitterRoot;
	QString EmitterName;
	QString	ClassName;
	int32	GlobalPageFrom;
	DirectCommPacketBase	*SendBackPacket;
	DirectCommPacketBase	*ReturnBackInReceive;
	ErrorCodeList	ErrorData;

	bool	Received;
public:

	DirectCommPacketBase(LayersBase *base, int globalPageOwn 
						,const QString &EmitterRoot ,const QString &EmitterName ,const QString &className);
	virtual	~DirectCommPacketBase(void);

	virtual	bool	Load(QIODevice *f)=0;
	virtual	bool	Save(QIODevice *f)=0;
	virtual	QByteArray	*GetSaveArray(void){	return NULL;	}

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)=0;	

	bool	Send(DirectCommPacketBase *parent ,int32 globalPageTo ,int32 cmd);
	bool	Send(int32 globalPageTo ,int32 cmd ,DirectCommPacketBase &AckPacket ,int32 MaxWaitMiliSec=3000);

	bool	IsReceived(void)	const	{	return(Received);	}
	void	SetReceived(bool b)			{	Received=b;			}

	DirectCommPacketBase	*SetLocalPage(int localPage);

	void	ClearReceivedFlag(void){	Received=false;	}
	DirectCommPacketBase	*GetSendBackPacket(void)	const	{	return SendBackPacket;	}
	int		GetGlobalPageFrom(void)	const	{	return GlobalPageFrom;	}
	void	SetGlobalPageFrom(int gpage)	{	GlobalPageFrom=gpage;	}
	bool	WaitForReadyRead(int GlobalPage ,int milisec);

protected:
	void	PopupPacketPriority(void);
};
class	DirectCommReceiverList : public NPList<DirectCommReceiverList>
{
public:
	QString				EmitterRoot;
	QString				EmitterName;
	QString				ClassName;
	DirectCommPacketBase	*Point;

	DirectCommReceiverList(void)
		:Point(NULL){}
	DirectCommReceiverList(const QString &emitterRoot ,const QString &emitterName ,const QString &classname , DirectCommPacketBase *p)
		:EmitterRoot(emitterRoot),EmitterName(emitterName),ClassName(classname),Point(p){}
};

class	DirectCmdPacketBasePointerList : public NPList<DirectCmdPacketBasePointerList>
{
	DirectCommPacketBase	*Base;
public:

	explicit	DirectCmdPacketBasePointerList(DirectCommPacketBase *base){	Base=base;	}
	~DirectCmdPacketBasePointerList(void)			{	delete	Base;	}

	DirectCommPacketBase	*GetBase(void)	const	{	return Base;	}
};

class	DirectCmdPacketBaseContainer : public NPListPack<DirectCmdPacketBasePointerList>
{
public:
	DirectCmdPacketBaseContainer(void){}

	DirectCmdPacketBaseContainer	&operator=(DirectCommPacketBase *a){	AppendList(new DirectCmdPacketBasePointerList(a));	return *this;	}
};

//---------------------------------------------------------------------------------------------
class	SlaveCommForkStart : public DirectCommPacketBase
{
public:
	explicit	SlaveCommForkStart(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPageOwn=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;
};

class	SlaveCommJoin : public DirectCommPacketBase
{
public:
	explicit	SlaveCommJoin(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPageOwn=-1);

	virtual	bool	Load(QIODevice *f)	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	override;
};

#endif