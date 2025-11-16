#include "IntegrationImageBankResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationImageBank\IntegrationImageBank.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationImageBank.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include <QIcon>
#include <QPixmap>
#include "XMacroFunction.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include "IntegrationImageBankForm.h"
#include "ImageBank.h"
#include "XLotInformation.h"
#include "ImageBank.h"
#include "StartProcessAgainButton.h"
#include "XCriticalFunc.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ImageBank";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to control ImageBank");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationSetStateImageBank		(Base,sRoot,sName);
	(*Base)	=new IntegrationSetImageBankClear		(Base,sRoot,sName);
	(*Base)	=new IntegrationReqListImageBankContainer(Base,sRoot,sName);
	(*Base)	=new IntegrationAckListImageBankContainer(Base,sRoot,sName);
	(*Base)	=new IntegrationReqImageBankSwitch		(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationImageBank(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationImageBank *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationImageBank *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationImageBank *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationImageBank *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"ListCount";
	Data[4].Pointer				 =&((IntegrationImageBank *)Instance)->ListCount;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"BootON";
	Data[5].Pointer				 =&((IntegrationImageBank *)Instance)->BootON;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"StoreOnlyOK";
	Data[6].Pointer				 =&((IntegrationImageBank *)Instance)->StoreOnlyOK;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"StoreOnlyNG";
	Data[7].Pointer				 =&((IntegrationImageBank *)Instance)->StoreOnlyNG;
	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationImageBank.png")));
}


//==================================================================================================
IntegrationImageBank::IntegrationImageBank(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationImageBankBtn");
	Button.move(0,0);
	Msg=/**/"Image bank";
	resize(80,25);

	ListCount	=10;
	Form		=NULL;
	BootON		=true;
	StoreOnlyOK	=true;
	StoreOnlyNG	=true;

	Button.setStyleSheet("QToolButton {"
						"	border-style: outset;"
						"	border-width: 1px;"
						"	border-radius: 25px;"
						"	border-color: gray;"
						"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						"}"
						"QToolButton:pressed { 	"
						"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationImageBank::~IntegrationImageBank()
{
	if(Form!=NULL){
		delete	Form;
		Form=NULL;
	}
}

void	IntegrationImageBank::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationImageBank::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationImageBank::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqImageBankGridList	*CmdReqImageBankGridListVar=dynamic_cast<CmdReqImageBankGridList *>(packet);
	if(CmdReqImageBankGridListVar!=NULL){
		CmdReqImageBankGridListVar->GridList.RemoveAll();
		UpdateList();
 		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int n=0;n<N;n++){
		    for(ListImageBank *s=BankDim[n].GetFirst();s!=NULL;s=s->GetNext()){
		        bool    Found=false;
		        for(ListImageBankPointerContainer *d=CmdReqImageBankGridListVar->GridList.GetFirst();d!=NULL;d=d->GetNext()){
		            ListImageBankPointer   *p=d->NPListPack<ListImageBankPointer>::GetFirst();
		            if(p!=NULL){
		                if(p->Pointer->InspectionID==s->InspectionID){
		                    d->AppendList(new ListImageBankPointer(s));
		                    Found=true;
		                    break;
		                }
		            }
		        }
		        if(Found==false){
		            ListImageBankPointerContainer   *dn=new ListImageBankPointerContainer();
		            s->SlaveID=n;
		            dn->AppendList(new ListImageBankPointer(s));
		            CmdReqImageBankGridListVar->GridList.AppendList(dn);
		        }
		    }
		}
		CmdReqImageBankGridListVar->GridList.Sort();
		return;
	}
	CmdSetStateImageBank	*CmdSetStateImageBankVar=dynamic_cast<CmdSetStateImageBank *>(packet);
	if(CmdSetStateImageBankVar!=NULL){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		    IntegrationSetStateImageBank	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		    RCmd.ONMode         =CmdSetStateImageBankVar->ONMode        ;
		    RCmd.StoreOnlyOK    =CmdSetStateImageBankVar->StoreOnlyOK   ;
		    RCmd.StoreOnlyNG    =CmdSetStateImageBankVar->StoreOnlyNG   ;
		    RCmd.ListCount      =CmdSetStateImageBankVar->ListCount     ;
		    RCmd.Send(NULL,SlaveNo,0);
		}
		return;
	}
	CmdReqListImageBankPointerContainer	*CmdReqListImageBankPointerContainerVar=dynamic_cast<CmdReqListImageBankPointerContainer *>(packet);
	if(CmdReqListImageBankPointerContainerVar!=NULL){
		IntList SlaveList;
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		    ListImageBankPointer *q;
		    for(q=CmdReqListImageBankPointerContainerVar->Pointer->NPListPack<ListImageBankPointer>::GetFirst();q!=NULL;q=q->GetNext()){
		        if(q->Pointer->SlaveID==SlaveNo){
		            break;
		        }
		    }
		    if(q!=NULL){
		        IntegrationReqImageBankSwitch	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		        RCmd.LoadedID=q->Pointer->LoadedID;
				RCmd.ExeRetry=CmdReqListImageBankPointerContainerVar->ExeRetry;
			    RCmd.Send(NULL,SlaveNo,0);
		    }
		}
		DWORD	t=::GetComputerMiliSec();
		while((::GetComputerMiliSec()-t)<GetParamGlobal()->MaxInspectMilisec){
			for(IntClass *v=SlaveList.GetFirst();v!=NULL;v=v->GetNext()){
				if(GetLayersBase()->HasReceivedIntegrationAck(v->GetValue())==true){
					SlaveList.RemoveList(v);
					break;
				}
			}
			if(SlaveList.GetCount()==0){
				break;
			}
		}
		BroadcastShowInPlayer();

		return;
	}
}

void	IntegrationImageBank::SlotClicked ()
{
	if(Form==NULL){
		Form=new IntegrationImageBankForm(GetLayersBase(),this);
	}
	Form->show();
	Form->ShowGrid();
}

void	IntegrationImageBank::UpdateList(void)
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int n=0;n<N;n++){
		 BankDim[n].RemoveAll();
		IntegrationReqListImageBankContainer	RCmd(GetLayersBase(),sRoot,sName,n);
        IntegrationAckListImageBankContainer	ACmd(GetLayersBase(),sRoot,sName,n);
		if(RCmd.Send(n,0,ACmd)==true){
            BankDim[n]=ACmd.Container;
			for(ListImageBank *a=BankDim[n].GetFirst();a!=NULL;a=a->GetNext()){
				a->SlaveID=n;
			}
		}
	}
}
void	IntegrationImageBank::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LVar!=NULL){
		UpdateList();
		return;
	}
}

//==================================================================================================

IntegrationSetStateImageBank::IntegrationSetStateImageBank(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetStateImageBank::Load(QIODevice *f)
{
	if(::Load(f,ONMode	)==false)
		return false;
	if(::Load(f,StoreOnlyOK	)==false)
		return false;
	if(::Load(f,StoreOnlyNG	)==false)
		return false;
	if(::Load(f,ListCount	)==false)
		return false;
	return true;
}
bool	IntegrationSetStateImageBank::Save(QIODevice *f)
{
	if(::Save(f,ONMode	)==false)
		return false;
	if(::Save(f,StoreOnlyOK	)==false)
		return false;
	if(::Save(f,StoreOnlyNG	)==false)
		return false;
	if(::Save(f,ListCount	)==false)
		return false;
	return true;
}

void	IntegrationSetStateImageBank::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ImageBank",/**/"");
	if(f!=NULL){
		CmdSetStateImageBank	RCmd(GetLayersBase());
		RCmd.ListCount	=ListCount;
		RCmd.StoreOnlyOK=StoreOnlyOK;
		RCmd.StoreOnlyNG=StoreOnlyNG;
		RCmd.ONMode		=ONMode;
		f->TransmitDirectly(&RCmd);
	}
}


IntegrationSetImageBankClear::IntegrationSetImageBankClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationSetImageBankClear::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ImageBank",/**/"");
	if(f!=NULL){
		CmdSetClearImageBank	RCmd(GetLayersBase());

		f->TransmitDirectly(&RCmd);
	}
}

//===================================================================================================

IntegrationReqListImageBankContainer::IntegrationReqListImageBankContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqListImageBankContainer::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckListImageBankContainer	*SendBack=GetSendBackIntegration(IntegrationAckListImageBankContainer,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	ImageBank	*f=(ImageBank *)GetLayersBase()->FindByName(/**/"Button",/**/"ImageBank",/**/"");
	if(f!=NULL){
		int	CurrentLotAutoCount=GetLayersBase()->GetLot(0)->GetLotAutoCount();
		for(ImageInInspection *s=f->Bank.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->InspectionID>=0 && s->LotAutoCount==CurrentLotAutoCount){
				ListImageBank	*L=new ListImageBank();
				L->Time			=s->Time;
				L->InspectionID	=s->InspectionID;
				L->LoadedID		=s->LoadedID	;
				L->ResultOK		=s->ResultOK;
				L->SlaveID		=0;
				L->ProcessMSec	=s->ProcessMSec;

				SendBack->Container.AppendList(L);
			}
		}
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckListImageBankContainer::IntegrationAckListImageBankContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckListImageBankContainer::Load(QIODevice *f)
{
	if(Container.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationAckListImageBankContainer::Save(QIODevice *f)
{
	if(Container.Save(f)==false)
		return false;
	return true;
}

//===================================================================================================

IntegrationReqImageBankSwitch::IntegrationReqImageBankSwitch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqImageBankSwitch::Load(QIODevice *f)
{
	if(::Load(f,LoadedID	)==false)
		return false;
	if(::Load(f,ExeRetry	)==false)
		return false;
	return true;
}
bool	IntegrationReqImageBankSwitch::Save(QIODevice *f)
{
	if(::Save(f,LoadedID	)==false)
		return false;
	if(::Save(f,ExeRetry	)==false)
		return false;
	return true;
}

void	IntegrationReqImageBankSwitch::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ImageBank",/**/"");
	if(f!=NULL){
		CmdSwitchImageBank	RCmd(GetLayersBase());
		RCmd.LoadedID	=LoadedID;
		f->TransmitDirectly(&RCmd);
	}
	if(ExeRetry==true){
		GUIFormBase	*f2=GetLayersBase()->FindByName(/**/"Action",/**/"StartProcessAgainButton",/**/"");
		if(f2!=NULL){
			CmdReqPush	RCmd(GetLayersBase());
			f2->TransmitDirectly(&RCmd);
		}
	}
	SendAck(slaveNo);
}

