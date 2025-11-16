#if	!defined(XIntegrationPacketComm_h)
#define	XIntegrationPacketComm_h

#include <QBitmap>
#include <QIODevice>
#include "XDateTime.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include "XUndo.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "XGUIDirectMessage.h"

//-------------------------------------------------------------------
//	Communication from integrationPC to Integration-SlavePC(MasterPC)
//-------------------------------------------------------------------


class	IntegrationCmdPacketBase : public NPList<IntegrationCmdPacketBase> 
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

private:
	bool	SentRealSocket;
	QString EmitterRoot;
	QString EmitterName;
	QString	ClassName;
	int32	SlaveNo;
	IntegrationCmdPacketBase	*SendBackPacket;
protected:
	IntegrationCmdPacketBase	*ReturnBackInReceive;
private:
	ErrorCodeList	ErrorData;

	bool	Received;
	bool	FromMaster;
public:

	IntegrationCmdPacketBase(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,const QString &className ,int SlaveNo);
	virtual	~IntegrationCmdPacketBase(void);

	virtual	bool	Load(QIODevice *f)=0;
	virtual	bool	Save(QIODevice *f)=0;
	virtual	QByteArray	*GetSaveArray(void)	{	return NULL;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

	bool	IsPossibleToSend(int32 slaveNo)	const;
	bool	Send(IntegrationCmdPacketBase *parent ,int32 slaveNo ,int32 cmd);
	bool	SendReqAck(IntegrationCmdPacketBase *parent ,int32 slaveNo ,int32 cmd);
	bool	Send(int32 slaveNo ,int32 cmd ,IntegrationCmdPacketBase &AckPacket ,int32 MaxWaitMiliSec=10000);
	bool	SendFromSlaveToMaster(int32 OwnSlaveNo ,int32 cmd);

	bool	IsReceived(void)	const	{	return(Received);	}
	void	ClearReceivedFlag(void)		{	Received=false;	}
	IntegrationCmdPacketBase	*GetSendBackPacket(void)	const	{	return SendBackPacket;	}
	int		GetSlaveNo(void)	const	{	return SlaveNo;	}
	QString GetEmitterRoot(void)	const	{	return EmitterRoot;	}
	QString GetEmitterName(void)	const	{	return EmitterName;	}
	IntegrationCmdPacketBase	*SetSlaveNo(int slaveno);
	bool	WaitForReadyRead(int slaveNo ,int milisec);

	void	SetError(int errorCode=0 ,const QString &errorMessage=/**/"" ,ErrorCodeList::CautionLevel level=ErrorCodeList::_None);
	void	SetError(ErrorCodeList &ErrorData);
	void	AddErrorDataToSystem(ErrorCodeList &ErrorData,int slaveNo);

	bool	GetReceived(void)		const	{	return Received;	}
	void	SetReceived(bool b)				{	Received=b;			}
	bool	GetFromMaster(void)		const	{	return FromMaster;	}
	void	SetFromMaster(bool b)			{	FromMaster=b;		}

	void	SendAck(int slaveNo);

protected:
	void	PopupPacketPriority(void);

};
#define	GetSendBackIntegrationRec(typeclass,base,emitterRoot,emitterName)	(typeclass *)((ReturnBackInReceive==NULL)?(ReturnBackInReceive=new typeclass(base,emitterRoot,emitterName)):ReturnBackInReceive)
#define	GetSendBackIntegration(typeclass,base,emitterRoot,emitterName,slaveNo)	(typeclass *)((GetSendBackPacket()==NULL)?(GetSendBackIntegrationRec(typeclass,base,emitterRoot,emitterName)):(GetSendBackPacket()->SetSlaveNo(slaveNo)))
#define	CloseSendBackIntegration(typedata)				if(GetSendBackPacket()==NULL && ReturnBackInReceive==NULL){	delete	typedata;	}


class	IntegrationAck: public IntegrationCmdPacketBase
{
public:
	IntegrationAck(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}	
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
private:

};
class	IntegrationCmdPacketBaseContainer : public NPListPack<IntegrationCmdPacketBase>
{
public:
	IntegrationCmdPacketBaseContainer(void){}

	IntegrationCmdPacketBaseContainer	&operator=(IntegrationCmdPacketBaseContainer *a);
};

bool	IntegrationMultiReq( IntegrationCmdPacketBaseContainer &RCmdContainer
							,IntegrationCmdPacketBaseContainer ACmdContainer
							,DWORD WaitingMilisec=2000
							,bool ShowProcessingPanel=true
							,const QString &TitleOnPanel="On communicating...");
bool	IntegrationMultiAck( IntegrationCmdPacketBaseContainer &RCmdContainer
							,DWORD WaitingMilisec=2000
							,bool ShowProcessingPanel=true
							,const QString &TitleOnPanel="On communicating...");

#endif