#include "IntegrationShowConnectionStateResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowConnectionState\IntegrationShowConnectionState.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationShowConnectionState.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "WaitingConnectionForm.h"
#include <QMenu>
#include "IntegrationLoadMaster.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowConnectionState";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show connection state");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationShowConnectionState(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowConnectionState.png")));
}

//==================================================================================================================

ColorFrameWithClick::ColorFrameWithClick(int number ,QWidget * parent, Qt::WindowFlags f)
	:mtColorFrame(parent,f)
{
	Number=number;
	//grabMouse();
}

void	ColorFrameWithClick::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::RightButton){
		IntegrationShowConnectionState	*p=dynamic_cast<IntegrationShowConnectionState *>(parent());
		if(p!=NULL){
			QMenu	Menu(this);
			Menu.addAction ("Reboot program", this, SLOT(SlotReboot()));
			Menu.addAction ("Check"			, this, SLOT(SlotCheck()));
			Menu.addSeparator();
			Menu.addAction ("Reboot all"	, this, SLOT(SlotRebootAll()));

			QPoint	Q=mapToGlobal(QPoint(10,10));
			Menu.exec(Q);
		}
	}
}

void	ColorFrameWithClick::SlotReboot()
{
	IntegrationShowConnectionState	*p=dynamic_cast<IntegrationShowConnectionState *>(parent());
	if(p!=NULL){
		p->SlaveReboot(Number);
	}
}
void	ColorFrameWithClick::SlotCheck()
{
	IntegrationShowConnectionState	*p=dynamic_cast<IntegrationShowConnectionState *>(parent());
	if(p!=NULL){
		p->SlaveCheck(Number);
	}
}
void	ColorFrameWithClick::SlotRebootAll()
{
	IntegrationShowConnectionState	*p=dynamic_cast<IntegrationShowConnectionState *>(parent());
	if(p!=NULL){
		p->RebootAllSlaves();
	}
}


//============================================================================
IntegrationShowConnectionState::SlaveLine::SlaveLine(int n,IntegrationShowConnectionState *parent)
	:Label(parent),Frame(n,parent)
{
	State=false;
	Frame.setGeometry(0,n*24,24,24);
	Frame.SetColor(Qt::gray);
	Label.setGeometry(26,n*24,parent->width()-26,24);
}
void	IntegrationShowConnectionState::SlaveLine::SetState(bool ON)
{
	if(ON==true){
		State=true;
		Frame.SetColor(Qt::green);
	}
	else{
		State=false;
		Frame.SetColor(Qt::gray);
	}
}
void	IntegrationShowConnectionState::SlaveLine::Show(void)
{
	Frame.show();
	Label.show();
}
void	IntegrationShowConnectionState::SlaveLine::SetText(const QString &str)
{
	Label.setText(str);
}

IntegrationShowConnectionState::IntegrationShowConnectionState(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(250,250);
	WaitingConnection=NULL;
}

IntegrationShowConnectionState::~IntegrationShowConnectionState()
{
	if(WaitingConnection!=NULL){
		delete	WaitingConnection;
	}
	WaitingConnection=NULL;
}

void	IntegrationShowConnectionState::ReadyParam(void)
{
	if(GetEditMode()==false
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int i=0;i<N;i++){
			SlaveLine	*L=new SlaveLine(i,this);
			SlaveLines.AppendList(L);
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL){
				if(m->IsDependent()==false){
					L->SetText(m->GetMachineName());
				}
				else{
					L->SetText(m->GetMachineName()+QString(/**/"-1"));
				}
			}
			L->Show();
		}

		connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalSlaveConnected())		,this,SLOT(SlotSlaveConnected()));
		connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalSlaveDisconnected())	,this,SLOT(SlotSlaveDisconnected()));
	}

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"LoadMaster",/**/"");
	if(f!=NULL){
		CmdReqEnableLoadAtFirst	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
		if(RCmd.EnableLoadAtFirst==true){
			WaitingConnection=new WaitingConnectionForm(GetLayersBase(),this);
			WaitingConnection->show();
		}
	}
}

void	IntegrationShowConnectionState::TransmitDirectly(GUIDirectMessage *packet)
{
	IntegrationGetConnectionState	*IntegrationGetConnectionStateVar=dynamic_cast<IntegrationGetConnectionState *>(packet);
	if(IntegrationGetConnectionStateVar!=NULL){
		IntegrationGetConnectionStateVar->State.RemoveAll();
		IntegrationCommPack		*C=GetLayersBase()->GetIntegrationCommPointer();
		if(C!=NULL){
			int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			for(int i=0;i<N;i++){
				SlaveLine	*L=SlaveLines.GetItem(i);
				IntegrationCommPipe	*s=C->GetSocket(i);
				if(s==NULL || s->IsConnected()==false){
					IntegrationGetConnectionStateVar->State.Add(false);
				}
				else{
					IntegrationGetConnectionStateVar->State.Add(true);
				}
			}
		}
		return;
	}
}

void	IntegrationShowConnectionState::SlotSlaveConnected()
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		IntegrationCommPack		*C=GetLayersBase()->GetIntegrationCommPointer();
		if(C!=NULL){
			int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			for(int i=0;i<N;i++){
				SlaveLine	*L=SlaveLines.GetItem(i);
				IntegrationCommPipe	*s=C->GetSocket(i);
				if(s==NULL || s->IsConnected()==false){
					L->SetState(false);
				}
				else{
					L->SetState(true);
				}
			}
		}
	}
}

void	IntegrationShowConnectionState::SlotSlaveDisconnected()
{
	SlotSlaveConnected();
}

void	IntegrationShowConnectionState::SlaveReboot(int number)
{
}
void	IntegrationShowConnectionState::SlaveCheck(int number)
{
}
void	IntegrationShowConnectionState::RebootAllSlaves(void)
{
}


