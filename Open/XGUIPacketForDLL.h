/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XGUIPacketForDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XGUIPACKET_H)
#define	XGUIPACKET_H

#include <QBitmap>
#include <QIODevice>
#include "XDateTime.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include "XUndo.h"
#include "XServiceForLayers.h"
#include "XGUIDirectMessage.h"
#include <typeinfo>

class	EntryPointBase;
class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	GUICmdPacketBase;
class	IntegrationCmdPacketBase;

class	SpecifiedBroadcaster
{
public:
	SpecifiedBroadcaster(void){}
	virtual	~SpecifiedBroadcaster(void){}
};


//================================================================

#ifdef GUICmdPacketBase_LIB
# define GUICmdPacketBase_EXPORT Q_DECL_EXPORT
#else
# define GUICmdPacketBase_EXPORT Q_DECL_IMPORT
#endif

class	GUICmdPacketBase : public NPList<GUICmdPacketBase> 
							,public GUIDirectMessage ,public ServiceForLayers
{
	friend	class	LayersBase;
public:
	enum		CautionLevel{
					 _None		=0		//No error
					,_Critical	=1		//stop system
					,_Important	=2		//die something for function, thread
					,_Alart		=3		//Never die , light level error
					,_Message	=4		//pure message
	};

protected:
	bool	SentRealSocket;
	QString EmitterRoot;
	QString EmitterName;
	QString	ClassName;
	int32	GlobalPage;
	GUICmdPacketBase	*SendBackPacket;
	GUICmdPacketBase	*ReturnBackInReceive;

	ErrorCodeList	ErrorData;

	bool	Received;
	bool	FromMaster;
public:

	GUICmdPacketBase(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,const QString &className ,int globalPage);
	virtual	~GUICmdPacketBase(void);

	virtual	bool	Load(QIODevice *f)=0;
	virtual	bool	Save(QIODevice *f)=0;
	virtual	QByteArray	*GetSaveArray(void){	return NULL;	}

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)=0;	


	bool	IsPossibleToSend(int32 globalPage)	const;
	bool	Send(GUICmdPacketBase *parent ,int32 globalPage ,int32 cmd);
	bool	SendAllPages(GUICmdPacketBase *parent ,int32 cmd);
	bool	Send(int32 globalPage ,int32 cmd ,GUICmdPacketBase &AckPacket ,int32 MaxWaitMiliSec=10000);
	bool	SendOnly(int32 globalPage ,int32 cmd ,int32 MaxWaitMiliSec=10000);
	bool	SendFromSlaveToMaster(int32 globalPage ,int32 cmd);

	bool	IsReceived(void)		const	{	return(Received);	}
	void	ClearReceivedFlag(void)			{	Received=false;		}
	GUICmdPacketBase	*GetSendBackPacket(void)	const	{	return SendBackPacket;	}
	GUICmdPacketBase	*SetLocalPage(int localPage);
	int		GetGlobalPage(void)	const	{	return GlobalPage;	}
	void	SetGlobalPage(int gpage)	{	GlobalPage=gpage;	}
	bool	WaitForReadyRead(int GlobalPage ,int milisec);

	bool	SendAck(int LocalPage);
	void	SetError(int errorCode=0 ,const QString &errorMessage=/**/"" ,ErrorCodeList::CautionLevel level=ErrorCodeList::_None);
	void	SetError(const ErrorCodeList &ErrorData);
	void	AddErrorDataToSystem(ErrorCodeList &ErrorData,int globalPage);

	bool	GetReceived(void)		const	{	return Received;	}
	void	SetReceived(bool b)				{	Received=b;			}
	bool	GetFromMaster(void)		const	{	return FromMaster;	}
	void	SetFromMaster(bool b)			{	FromMaster=b;		}

protected:
	void	PopupPacketPriority(void);
	void	ActivePhaseList(IntList &PhaseList);
};

#define	GetSendBackRec(typeclass,base,emitterRoot,emitterName)	(typeclass *)((ReturnBackInReceive==NULL)?(ReturnBackInReceive=new typeclass(base,emitterRoot,emitterName)):ReturnBackInReceive)
#define	GetSendBack(typeclass,base,emitterRoot,emitterName,localPage)	(typeclass *)((GetSendBackPacket()==NULL)?GetSendBackRec(typeclass,base,emitterRoot,emitterName) : GetSendBackPacket())->SetLocalPage(localPage)
#define	CloseSendBack(typedata)				if(GetSendBackPacket()==NULL && ReturnBackInReceive==NULL){	delete	typedata;	}


class	GUICmdPacketBasePointerList : public NPList<GUICmdPacketBasePointerList>
{
	GUICmdPacketBase	*Base;
public:

	explicit	GUICmdPacketBasePointerList(GUICmdPacketBase *base){	Base=base;	}
	~GUICmdPacketBasePointerList(void)			{	delete	Base;	}

	GUICmdPacketBase	*GetBase(void)	const	{	return Base;	}
};

class	GUICmdPacketBasePointerListContainer : public NPListPack<GUICmdPacketBasePointerList>
{
public:
	GUICmdPacketBasePointerListContainer(void){}

	GUICmdPacketBasePointerListContainer	&operator=(GUICmdPacketBase *a){	AppendList(new GUICmdPacketBasePointerList(a));	return *this;	}
};

class	GUICmdPacketBaseContainer : public NPListPack<GUICmdPacketBase>
{
public:
	GUICmdPacketBaseContainer(void){}
};

bool	GUICmdMultiReq(  GUICmdPacketBaseContainer &RCmdContainer
						,GUICmdPacketBaseContainer &ACmdContainer
						,DWORD WaitingMilisec=2000
						,bool ShowProcessingPanel=true
						,const QString &TitleOnPanel="On communicating...");
bool	GUICmdMultiAck(GUICmdPacketBaseContainer &RCmdContainer
						,DWORD WaitingMilisec=2000
						,bool ShowProcessingPanel=true
						,const QString &TitleOnPanel="On communicating...");

//=================================================================================

class	IntegrationCmdPacketBasePointerList : public NPList<IntegrationCmdPacketBasePointerList>
{
	IntegrationCmdPacketBase	*Base;
public:

	explicit	IntegrationCmdPacketBasePointerList(IntegrationCmdPacketBase *base){	Base=base;	}
	~IntegrationCmdPacketBasePointerList(void);
	IntegrationCmdPacketBase	*GetBase(void)	{	return Base;	}
};

class	IntegrationCmdPacketBasePointerListContainer : public NPListPack<IntegrationCmdPacketBasePointerList>
{
public:
	IntegrationCmdPacketBasePointerListContainer(void){}

	IntegrationCmdPacketBasePointerListContainer	&operator=(IntegrationCmdPacketBase *a);
};

//=================================================================================

class	GUICmdPacketDim : public NPList<GUICmdPacketDim>
{
	friend class	LayersBase;
	GUICmdPacketBase *Sender;
	GUICmdPacketBase *Receiver;
	int GlobalPage;
	int Cmd;
public:
	GUICmdPacketDim(GUICmdPacketBase *sender ,GUICmdPacketBase *receiver, int globalPage,int cmd)
	{
		Sender		=sender;
		Receiver	=receiver;
		GlobalPage	=globalPage;
		Cmd			=cmd;
	}
	int	GetPage(void)			const	{	return GlobalPage;	}
	bool	IsReceived(void)	const	{	return Receiver->IsReceived();	}
};

#endif
