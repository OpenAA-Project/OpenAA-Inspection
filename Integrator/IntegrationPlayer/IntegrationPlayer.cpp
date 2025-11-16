/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\IntegrationPlayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	ForApplication
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "ThreadSequence.h"
#include "XExecuteIntegrationPlayer.h"
#include "XDirectComm.h"
#include "XPieceArchitect.h"
#include "IntegrationPlayer.h"
#include "XIntegrationComm.h"
#include "XGUIInExe.h"

IntegrationPlayer::IntegrationPlayer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

IntegrationPlayer::~IntegrationPlayer()
{

}


GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event);


ThreadSequence		*EntryPointForGlobal::GetThreadSequence(void)	const
{
	return GetLayersBase()->GetSequenceInstance();
}

GUIInstancePack		*EntryPointForGlobal::GetGUIInstancePack(void)
{
	return(GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot());
}

bool	EntryPointForGlobal::SendData(int32 commID ,int globalPage
						,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						,QBuffer *f
						,ErrorCodeList &ErrorData)
{
	return GetLayersBase()->GetGuiInitializer()->TxData(globalPage ,IndoPacket ,commID ,f,ErrorData);
}

bool	EntryPointForGlobal::SendIntegrationData (int slaveNo
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f,ErrorCodeList &ErrorData)
{
	return GetLayersBase()->GetGuiInitializer()->TxIntegrationData(slaveNo ,IndoPacket ,f,ErrorData);
}


bool	EntryPointForGlobal::SendArray(int32 commID ,int globalPage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QByteArray *f
					,ErrorCodeList &ErrorData)
{
	return GetLayersBase()->GetGuiInitializer()->TxData(globalPage ,IndoPacket ,commID ,f,ErrorData);
}

bool	EntryPointForGlobal::SendDataDirectComm(int32 commID ,int globalPage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f
					,ErrorCodeList &ErrorData)
{
	return DirectCommBase->TxData(globalPage ,IndoPacket,commID ,f,ErrorData);
}

void	EntryPointForGlobal::ReadyReadDirectComm(void)
{
	if(DirectCommBase!=NULL){
		DirectCommBase->ReadyReadDirectComm();
	}
}

QTcpSocket	*EntryPointForGlobal::GetSocket(int ComNo)
{
	return GetLayersBase()->GetGuiInitializer()->GetSocket(ComNo);
}

QTcpSocket	*EntryPointForGlobal::GetIntegrationSocket(int slaveNo)
{
	return GetLayersBase()->GetGuiInitializer()->GetIntegrationSocket(slaveNo);
}

DirectComm			*EntryPointForGlobal::CreateDirectComm(QObject * parent)
{
	DirectCommBase=new DirectComm(GetLayersBase(),parent);
	return DirectCommBase;
}

bool	EntryPointForGlobal::InitialDirectCommInSlave(DirectComm *p,QObject * parent,SystemConnectionInfoContainer &Info)
{
	return p->InitialCreate(parent,Info);
}


void	EntryPointForGlobal::GUISetProperty(GUIFormBase *CurrentForm,GUIFormBase *PutTop)
{
}

void	EntryPointForGlobal::GUIRemoveItem(GUIFormBase *w)
{
	for(GUIItemInstance *c=GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Handle==w){
			GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot()->RemoveList(c);
			return;
		}
	}
}

PieceClass			*EntryPointForGlobal::SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)
{
	if(GetLayersBase()!=NULL && GetLayersBase()->GetPieceStock()){
		return GetLayersBase()->GetPieceStock()->SearchAndLoad(masterCode,ErrorMessageOfFalse);
	}
	return NULL;
}


GUIInitializer::GUIInitializer(LayersBase *base)
:ServiceForLayers(base)
{
	GuiDLLPack	=new GuiDLLItemContainer;
	CommRootNumb=0;
	for(int i=0;i<sizeof(CommRoot)/sizeof(CommRoot[0]);i++){
		CommRoot[i]=NULL;
	}
	GUIInstanceRoot.AppendList(new GUIInstancePack(GetLayersBase(),this));
	IntegrationComm=new GUIIntegrationCommPack(base);
}

GUIInitializer::~GUIInitializer(void)
{
	//Layers->ReleaseAll();
	GetLayersBase()->ReleaseLogger();
	Release();
	GUIInstanceRoot.RemoveAll();
	GetLayersBase()->ReleaseBeforeReleasingGUI();
	GuiDLLPack->Close();
	GetLayersBase()->ReleaseAll();
	GuiDLLPack->RemoveAll();

	delete	GuiDLLPack;
	GuiDLLPack=NULL;
	
	delete	IntegrationComm;
	IntegrationComm=NULL;
}