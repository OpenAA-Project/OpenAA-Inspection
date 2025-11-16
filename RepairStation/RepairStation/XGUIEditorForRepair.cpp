/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XGUIEditorForRepair.cpp
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
#include "propertylist.h"
#include "XDataInLayerForRepair.h"
#include "XDataInExe.h"
#include "XDirectComm.h"
#include "XPieceArchitect.h"

class	ThreadSequence;
class	ExecuteInspectBase;

static	LayersBase	*Layers;
GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event);
static	NPListPack<ReceiverList>	RCmdBase;


extern	"C"{
	static	LayersBase	*DGetLayersBase(void);
	static	bool		DSendData(int32 cmd ,int32 commID ,int privatePage
						, const QString &EmitterRoot,const QString &EmitterName ,const QString &CmdClass 
						,QBuffer *f
						,int32 IDForUndo
						,ErrorCodeList &ErrorData);
	static	bool		DSendArray(int32 cmd ,int32 commID ,int globalPage
						, const QString &EmitterRoot,const QString &EmitterName ,const QString &CmdClass 
						,QByteArray *f
						,int32 IDForUndo
						,ErrorCodeList &ErrorData);
	static	QTcpSocket	*DGetSocket(int ComNo);
	static	void		DGUIRemoveItem(GUIFormBase *w);
	static	void		DGUISetProperty(GUIFormBase *CurrentForm,GUIFormBase *PutTop);
	static	DirectComm	*DCreateDirectComm(QObject * parent);
	static	PieceClass	*DSearchAndLoadPiece(int masterCode);
};


static	LayersBase	*DGetLayersBase(void)
{
	return(Layers);
}

static	ThreadSequence	*DGetThreadSequence(void)
{
	return EntryPointToFuncGlobal->GetLayersBase()->GetSequenceInstance();
}

static	GUIInstancePack	*DGetGUIInstancePack(void)
{
	return(GUIInitialData->GetGUIInstanceRoot());
}

static	bool	DSendData(int32 cmd ,int32 commID ,int globalPage
						, const QString &EmitterRoot,const QString &EmitterName ,const QString &CmdClass 
						,QBuffer *f
						,int32 IDForUndo
						,ErrorCodeList &ErrorData)
{
	return GUIInitialData->TxData(cmd ,globalPage ,EmitterRoot,EmitterName ,CmdClass ,commID ,f,IDForUndo,ErrorData);
}
static	bool	DSendArray(int32 cmd ,int32 commID ,int globalPage
						   , const QString &EmitterRoot,const QString &EmitterName ,const QString &CmdClass 
						   ,QByteArray *f
						   ,int32 IDForUndo
						   ,ErrorCodeList &ErrorData)
{
	return GUIInitialData->TxData(cmd ,globalPage ,EmitterRoot,EmitterName ,CmdClass ,commID ,f,IDForUndo,ErrorData);
}

static	QTcpSocket	*DGetSocket(int ComNo)
{
	return GUIInitialData->GetSocket(ComNo);
}

static	DirectComm	*DCreateDirectComm(QObject * parent,SystemConnectionInfoContainer &Info)
{
	DirectComm	*DirectCommBase=new DirectComm(DGetLayersBase(),parent,Info);
	DirectCommBase->InitialCreate(parent);
	return DirectCommBase;
}

static	void	DGUISetProperty(GUIFormBase *CurrentForm,GUIFormBase *PutTop)
{
	if(CurrentForm!=NULL){
		GUIItemInstance	*c=GUIInitialData->GetGUIInstanceRoot()->Search(CurrentForm);
		if(c!=NULL && MainProperty!=NULL){
			MainProperty->DLLInst=c;
			if(c->DLLAccess!=NULL)
				MainProperty->ShowList(c->DLLAccess->RootName,c->DLLAccess->Name);
		}
	}
	else{
		if(MainProperty!=NULL)
			MainProperty->DLLInst=NULL;
	}
}

static	void		DGUIRemoveItem(GUIFormBase *w)
{
	for(GUIItemInstance *c=GUIInitialData->GetGUIInstanceRoot()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Handle==w){
			GUIInitialData->GetGUIInstanceRoot()->RemoveList(c);
			return;
		}
	}
}

static	PieceClass	*DSearchAndLoadPiece(int masterCode)
{
	if(Layers!=NULL)
		return Layers->GetPieceStock()->SearchAndLoad(masterCode);
	return NULL;
}

GUIInitializer::GUIInitializer(LayersBase *base)
:ServiceForLayers(base)
{
	GuiDLLPack	=new GuiDLLItemContainer;
	for(int i=0;i<sizeof(CommRoot)/sizeof(CommRoot[0]);i++){
		CommRoot[i]=NULL;
	}
	GUIInstanceRoot.AppendList(new GUIInstancePack(GetLayersBase()));
	IntegrationComm				=NULL;
	IntegrationPageDirectlyComm	=NULL
	;
	EntryPointForGlobal	*e=dynamic_cast<EntryPointForGlobal *>(GetLayersBase()->GetEntryPoint());
	if(e!=NULL){
		e->DLL_GetLayersBase			=DGetLayersBase;
		e->DLL_SendData					=DSendData;
		e->DLL_SendArray				=DSendArray;
		e->DLL_GUISetProperty			=DGUISetProperty;
		e->DLL_GUIMouseLeftDownInEdit	=GUIMouseLeftDownInEdit;
		e->DLL_GUIRemoveItem			=DGUIRemoveItem;
		e->DLL_GetThreadSequence		=DGetThreadSequence;
		e->DLL_GetGUIInstancePack		=DGetGUIInstancePack;
		e->DLL_GetSocket				=DGetSocket;
		e->DLL_CreateDirectComm			=DCreateDirectComm;
		e->DLL_SearchAndLoadPiece		=DSearchAndLoadPiece;
	}
}

GUIInitializer::~GUIInitializer(void)
{
	Release();
	GUIInstanceRoot.RemoveAll();
	GetLayersBase()->ReleaseBeforeReleasingGUI();
	GuiDLLPack->Close();
	GetLayersBase()->ReleaseAll();
	GuiDLLPack->RemoveAll();

	delete	GuiDLLPack;
	GuiDLLPack=NULL;
}
