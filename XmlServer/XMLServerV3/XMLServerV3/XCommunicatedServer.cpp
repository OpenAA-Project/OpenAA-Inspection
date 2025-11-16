#include "XCommunicatedServer.h"
#include "XErrorCode.h"
#include "XCommandServer.h"

CommunicatedServerLeaf::CommunicatedServerLeaf(int ID ,CommunicatedServerComm *parent)
	:FastCommLeaf(ID,parent)
{
}


static	bool	Connection=true;

CommunicatedServerComm::CommunicatedServerComm(XMLServerComm *parent)
	:FastComm(parent)
{
	Parent=parent;
	LastAccessTime=XDateTime::currentDateTime();

	if(!connect(this,SIGNAL(SignalExecuteWriteOut()),this,SLOT(SlotExecuteWriteOut()),Qt::QueuedConnection))
		Connection=false;
}

void	CommunicatedServerComm::SlotExecuteWriteOut()
{
	Parent->WriteOutAll();
}
	

void	CommunicatedServerComm::SendCommandWriteOut(void)
{
	int	sec=LastAccessTime.secsTo(XDateTime::currentDateTime());

	if(sec>30){
		LastAccessTime=XDateTime::currentDateTime();
		SendCommandWriteOutInner(Parent->CommunicatedServerIP0);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP1);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP2);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP3);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP4);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP5);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP6);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP7);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP8);
		SendCommandWriteOutInner(Parent->CommunicatedServerIP9);
	}
}

void	CommunicatedServerComm::SendCommandWriteOutInner(const QString &HostIP)
{
	if(HostIP.isEmpty()==false){
		CommunicatedServerLeaf	*c=new CommunicatedServerLeaf(0,this);
		c->Set(this ,HostIP,CommunicatedServerPort);
		if(c->StartConnect()==true){
			ErrorCodeList ErrorData;
			struct EntryPointBase::EntryPointPacketInfo	Info(CS_Command_WriteOut
															,0
															,0
															,0
															,/**/""
															,/**/"" 
															,/**/"");
			c->TxData(0,Info,NULL,0,ErrorData);
			c->deleteLater();
		}
	}
}

void	CommunicatedServerComm::SlotReceived(int ID,int Cmd)
{
	FastCommLeaf *FR=GetLeaf(ID);
	RecList	*R=FR->UnpackTopRxBuff();
	if(R!=NULL){
		const char	*EmitterRoot;
		char	EmitterRootBuff[100];
		const char	*EmitterName;
		char	EmitterNameBuff[100];
		const char	*CmdClass;
		char	CmdClassBuff[100];
		BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
		if(fp==NULL){
			delete	R;
			return;
		}

		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			fp	=R->GetError(fp,ErrorData);
		}
		
		EmitterRoot	=EmitterRootBuff;
		EmitterName	=EmitterNameBuff;
		CmdClass	=CmdClassBuff;
		//QBuffer buff;
		//R->GetPointer(fp ,buff);
		//buff.open(QIODevice::ReadOnly);

		if(Cmd==CS_Command_WriteOut){
			emit	SignalExecuteWriteOut();
		}
	}
}

