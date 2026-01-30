/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



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