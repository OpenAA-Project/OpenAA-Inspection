/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIEditor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define	ForApplication
#include "XGUI.h"
#include "XGUIInterfaceDLL.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XDirectComm.h"
#include "XPieceArchitect.h"

#if defined(ModeEditGUI)
#include "propertylist.h"
#include "itemlistwindow.h"
extern	ItemListWindow* MainItem;
extern	PropertyList * MainProperty; 
#endif

class	ThreadSequence;
class	ExecuteInspectBase;


ThreadSequence		*EntryPointForGlobal::GetThreadSequence(void)	const
{
	return NULL;
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
	return GetLayersBase()->GetGuiInitializer()->TxData(globalPage ,IndoPacket,commID ,f,ErrorData);
}
bool	EntryPointForGlobal::SendArray(int32 commID ,int globalPage
						   ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						   ,QByteArray *f
						   ,ErrorCodeList &ErrorData)
{
	return GetLayersBase()->GetGuiInitializer()->TxData(globalPage ,IndoPacket,commID ,f,ErrorData);
}
bool	EntryPointForGlobal::SendDataDirectComm(int32 commID ,int globalPage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f
					,ErrorCodeList &ErrorData)
{
	return true;
}

bool	EntryPointForGlobal::SendIntegrationData (int slaveNo
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f ,ErrorCodeList &ErrorData)
{
	return GetLayersBase()->GetGuiInitializer()->TxIntegrationData(slaveNo ,IndoPacket,f,ErrorData);
}


QTcpSocket	*EntryPointForGlobal::GetSocket(int ComNo)
{
	return GetLayersBase()->GetGuiInitializer()->GetSocket(ComNo);
}
QTcpSocket	*EntryPointForGlobal::GetIntegrationSocket(int slaveNo)
{
	return GetLayersBase()->GetGuiInitializer()->GetIntegrationSocket(slaveNo);
}

void	EntryPointForGlobal::ReadyReadDirectComm(void)
{
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
#if defined(ModeEditGUI)
	if(CurrentForm!=NULL){
		GUIItemInstance	*c=CurrentForm->GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot()->Search(CurrentForm);
		if(c!=NULL && MainProperty!=NULL){
			MainProperty->DLLInst=c;
			MainProperty->PutTop=PutTop;
			if(c->DLLAccess!=NULL){
				MainProperty->ShowList(c->DLLAccess->RootName,c->DLLAccess->Name);
			}
			else{
				MainProperty->ClearList();
			}
		}
	}
	else{
		if(MainProperty!=NULL){
			MainProperty->DLLInst=NULL;
		}
	}
#endif
}

void	EntryPointForGlobal::GUIRemoveItem(GUIFormBase *w)
{
	for(GUIItemInstance *c=w->GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Handle==w){
			w->GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot()->RemoveList(c);
			return;
		}
	}
}

PieceClass			*EntryPointForGlobal::SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)
{
	if(GetLayersBase()!=NULL && GetLayersBase()->GetPieceStock()){
		return GetLayersBase()->GetPieceStock()->SearchAndLoad(masterCode,ErrorMessageOfFalse);
	}
	ErrorMessageOfFalse="No PieceStock";
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
	IntegrationComm				=NULL;
}

GUIInitializer::~GUIInitializer(void)
{
	GetLayersBase()->ReleaseLogger();
	Release();
	GUIInstanceRoot.RemoveAll();
	GetLayersBase()->ReleaseBeforeReleasingGUI();
	GuiDLLPack->Close();
	GetLayersBase()->ReleaseAll();
	GuiDLLPack->RemoveAll();

	delete	GuiDLLPack;
	GuiDLLPack=NULL;
}