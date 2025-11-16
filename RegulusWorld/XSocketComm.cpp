#include "XSocketComm.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"
#include "XDateTime.h"
#include "XRegulusWorld.h"
#include "XRegulusWorldClient.h"
#include "XCriticalFunc.h"

RWRecList::RWRecList(int len)
{
	Len=len;
	if(Len!=0){
		Data=new BYTE[Len];
	}
	else{
		Data=NULL;
	}
	EmitterNameLen	=0;
	ClassNameLen	=0;
	ErrorCode		=0;
	ErrorLevel		=0;
	ErrorMessageLen	=0;
	ErrorTimeLen	=0;
}

RWRecList::~RWRecList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

BYTE	*RWRecList::GetClassNamePointer(char EmitterName[],char CmdClassBuff[] ,int maxByte)
{
	CmdClassBuff[maxByte-1]=0;
	EmitterName[maxByte-1]=0;
	if(Data==NULL)
		return NULL;
	BYTE	*p=Data;

	strncpy(EmitterName,(char *)p,maxByte-1);
	p+=EmitterNameLen+1;
	if(strlen(EmitterName)!=EmitterNameLen){
		return NULL;
	}
	strncpy(CmdClassBuff,(char *)p,maxByte-1);
	p+=ClassNameLen+1;
	if(strlen(CmdClassBuff)!=ClassNameLen){
		return NULL;
	}
	return(p);
}

BYTE	*RWRecList::GetPointer(BYTE *p ,int32 &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((int32 *)p);
	p+=sizeof(int32);
	return(p);
}
BYTE	*RWRecList::GetPointer(BYTE *p ,WORD &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((WORD *)p);
	p+=sizeof(WORD);
	return(p);
}
BYTE	*RWRecList::GetPointer(BYTE *p ,bool &ret)
{
	if(p==NULL){
		p=Data;
	}
	ret=*((bool *)p);
	p+=sizeof(bool);
	return(p);
}
BYTE	*RWRecList::GetPointer(BYTE *p ,BYTE *buff ,int buffByte)
{
	if(p==NULL){
		p=Data;
	}
	memcpy(buff,p,buffByte);
	p+=buffByte;
	return(p);
}

BYTE	*RWRecList::GetPointer(BYTE *p ,QBuffer &ret)
{
	if(p==NULL){
		p=Data;
	}
	int32	rsize=*((int32 *)p);
	p+=sizeof(int32);
	if(ret.isOpen()){
		ret.close();
	}
	ret.setData((const char *)p,rsize);
	return(p+rsize);
}

BYTE	*RWRecList::GetError(BYTE *fp,ErrorCodeList &ErrorData)
{
	char	CmdErrorMessage[1000];
	char	CmdErrorTime[1000];

	strncpy(CmdErrorMessage,(char *)fp,sizeof(CmdErrorMessage)-1);
	CmdErrorMessage[sizeof(CmdErrorMessage)-1]=0;
	fp+=ErrorMessageLen+1;
	if(strlen(CmdErrorMessage)!=ErrorMessageLen){
		return NULL;
	}

	strncpy(CmdErrorTime,(char *)fp,sizeof(CmdErrorTime)-1);
	CmdErrorTime[sizeof(CmdErrorTime)-1]=0;
	fp+=ErrorTimeLen+1;
	if(strlen(CmdErrorTime)!=ErrorTimeLen){
		return NULL;
	}
	ErrorData.SetError(ErrorCode
					,CmdErrorMessage
					,(ErrorCodeList::CautionLevel)ErrorLevel
					,XDateTime::fromString(QString(CmdErrorTime),"d/M/yy h:m:s.z"));
	return fp;
}

//==================================================================================

RWTxList::RWTxList(int len , BYTE *data)
{
	Len=len;
	Data=new BYTE[Len];
	memcpy(Data,data,Len);
}

RWTxList::~RWTxList(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
}

//==================================================================================

RWPacketBase::RWPacketBase(RegulusWorld *base,const QString &emitterName ,const QString &className)
	:Base(base)
{
	EmitterName =emitterName;
	SendBackPacket=NULL;
	ClearReceivedFlag();
	FromMaster=false;
	SentRealSocket=false;
	QString	C1=ClassName=className;
	QString	C2=C1.remove(/**/" __ptr64");
	ClassName=C2.remove(/**/" __ptr32");
	Base->AppendPacket(this ,emitterName ,ClassName);
}
RWPacketBase::~RWPacketBase(void)
{
	Base->RemovePacket(this);
}

void	RWPacketBase::PopupPacketPriority(void)
{
	Base->PopupPacketPriority(this);
}


void	RWPacketBase::SetError(int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	ErrorData.SetError(errorCode ,errorMessage ,level,XDateTime::currentDateTime());
}
void	RWPacketBase::SetError(const ErrorCodeList &_ErrorData)
{
	ErrorData=_ErrorData;
}

void	RWPacketBase::AddErrorDataToSystem(ErrorCodeList &_ErrorData)
{
	if(_ErrorData.GetLevel()!=ErrorCodeList::_None){
		ErrorData=_ErrorData;
		ErrorCodeList	*c=new ErrorCodeList();
		*c=ErrorData;
		Base->AddError(c);
	}
}

bool	RWPacketBase::Send(RWPacketBase *parent ,int32 cmd ,int OwnID)
{
	SentRealSocket=false;
	if(Base->GetServerMode()==true){
		AccessSocket	*sv=Base->GetServerSocket(OwnID);
		if(sv!=NULL){
			//Send Packet to Salve
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(Save(&F)==true){
				if(sv->TxData(cmd ,EmitterName,ClassName ,&F,IDForUndo,ErrorData)==false){
					return false;
				}
			}
			else{
				return false;
			}
			SentRealSocket=true;
		}
		else{
			return false;
		}
	}
	else{
		RWClientSocket	*Cli=Base->GetClientSocket(OwnID);
		if(Cli!=NULL){
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(Save(&F)==true){
				if(Cli->TxData(cmd ,EmitterName,ClassName ,&F,IDForUndo,ErrorData)==false){
					return false;
				}
			}
			else{
				return false;
			}
			SentRealSocket=true;
		}
		else{
			return false;
		}
	}

	return(true);
}


bool	RWPacketBase::WaitForReadyRead(int OwnID,int milisec)
{
	if(Base->GetServerMode()==true){
		AccessSocket	*sv=Base->GetServerSocket(OwnID);
		if(sv!=NULL){
			return sv->WaitForReadyRead(milisec);
		}
	}
	else{
		RWClientSocket	*Cli=Base->GetClientSocket(OwnID);
		if(Cli!=NULL){
			return Cli->WaitForReadyRead(milisec);
		}
	}

	return false;
}

bool	RWPacketBase::Send(int32 cmd ,RWPacketBase &AckPacket ,int OwnID,int32 MaxWaitMiliSec)
{
	AckPacket.PopupPacketPriority();
	PopupPacketPriority();
	AckPacket.ClearReceivedFlag();

	SendBackPacket=&AckPacket;
	FromMaster=false;
	if(Send(this ,cmd ,OwnID)==false){
		AckPacket.Received=false;
		return false;
	}
	if(SentRealSocket==false){
		QTimer	TM;
		TM.setSingleShot(true);
		TM.start(MaxWaitMiliSec);
		while(TM.isActive()==true){
			if(AckPacket.IsReceived()==true){
				return(true);
			}
			QThreadForWait::MSWait(20);
		}
	}
	else{
		DWORD	StartTime=GetComputerMiliSec();
		//for(;;){
		while(GetComputerMiliSec()-StartTime<MaxWaitMiliSec){
			AckPacket.WaitForReadyRead(OwnID,MaxWaitMiliSec/5);
			if(AckPacket.IsReceived()==true){
				return(true);
			}
		}
		return false;
	}
	return(false);
}


//=================================================================