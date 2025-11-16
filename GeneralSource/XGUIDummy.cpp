/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIDummy.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"


ThreadSequence		*EntryPointForGlobal::GetThreadSequence(void)	const
{
	return GetLayersBase()->GetSequenceInstance();
}

DirectComm			*EntryPointForGlobal::CreateDirectComm(QObject * parent)
{
	return NULL;
}
bool				EntryPointForGlobal::InitialDirectCommInSlave(DirectComm	*p,QObject * parent,SystemConnectionInfoContainer &Info)
{
	return true;
}


PieceClass			*EntryPointForGlobal::SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)
{
	return NULL;
}

bool		EntryPointForGlobal::SendData (int32 commID ,int privatePage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f
					,ErrorCodeList &ErrorData)
{
	return true;
}
bool		EntryPointForGlobal::SendDataDirectComm(int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f 
								,ErrorCodeList &ErrorData)
{
	return true;
}
bool		EntryPointForGlobal::SendIntegrationData (int slaveNo
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f ,ErrorCodeList &ErrorData)
{
	return true;
}

bool		EntryPointForGlobal::SendArray(int32 commID ,int privatePage
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QByteArray *f
					,ErrorCodeList &ErrorData)
{
	return true;
}
void	EntryPointForGlobal::ReadyReadDirectComm(void)
{
}

QTcpSocket	*EntryPointForGlobal::GetSocket(int ComNo)
{
	return NULL;
}
QTcpSocket	*EntryPointForGlobal::GetIntegrationSocket(int slaveNo)
{
	return NULL;
}

void	EntryPointForGlobal::GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)
{}
void	EntryPointForGlobal::GUIRemoveItem(GUIFormBase *w)
{
}
GUIInstancePack		*EntryPointForGlobal::GetGUIInstancePack(void)
{
	return(GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot());
}


void	GUIItemInstance::SlotRelease()
{
} 
void	GUIItemInstance::SlotMove()
{
}
void	GUIItemInstance::SlotResize()
{
}

GUIFormBase		*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)
{
	return NULL;
}

GUIInitializer::GUIInitializer(LayersBase *Base)
	:ServiceForLayers(Base),GuiDLLPack(NULL)
{
	CommRootNumb=0;
	for(int i=0;i<sizeof(CommRoot)/sizeof(CommRoot[0]);i++){
		CommRoot[i]=NULL;
	}
	IntegrationComm				=NULL;
}

GUIInitializer::~GUIInitializer(void)
{
	Release();
}