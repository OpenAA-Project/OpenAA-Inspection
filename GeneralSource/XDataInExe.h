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



#if	!defined(XDATAINEXE_H)
#define	XDATAINEXE_H

#include "XDataInLayer.h"
#include <QTcpSocket>
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

class	GUIInitializer;
class	DirectComm;

class	EntryPointForGlobal : public EntryPointBase
{
	ExecuteInspectBase	*ExecuteInspectBasePointer;
	DirectComm			*DirectCommBase;
public:
	EntryPointForGlobal(void);
	~EntryPointForGlobal(void);

	virtual	DirectComm			*CreateDirectComm(QObject * parent)		override;
	virtual	bool				InitialDirectCommInSlave(DirectComm	*p,QObject * parent,SystemConnectionInfoContainer &Info)	override;

	virtual	int					GetDirectCommIDFromGlobalPage(int globalPageTo)	override;

	virtual	ThreadSequence		*GetThreadSequence(void)	const	override;
	virtual	ExecuteInspectBase	*GetExecuteInspect(void)	const	override{	return ExecuteInspectBasePointer;	}

	virtual	void				SetExecuteInspect(ExecuteInspectBase *ExeIns)	override	{	ExecuteInspectBasePointer=ExeIns;	}


	virtual	void				WaitReadyReadAll(int milisec)		override;
	virtual	void				SetLanguageCode(int LanguageCode)	override;
	virtual	PieceClass			*SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)	override;
	virtual	GUIFormBase	*ShowOtherGUI(GUIFormBase *ChainedParent
									,const QString &GUIFileName 
									,LayersBase *LayersBasePointer ,bool EditMode=false)	override;

	virtual	bool		SendData (int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f
								,ErrorCodeList &ErrorData)	override;
	virtual	bool		SendDataDirectComm(int32 commID ,int privatePage
											,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
											,QBuffer *f 
											,ErrorCodeList &ErrorData)	override;
	virtual	bool		SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)	override;

	virtual	bool		SendArray(int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray *f
								,ErrorCodeList &ErrorData)	override;
	virtual	void	ReadyReadDirectComm(void)	override;

	virtual	QTcpSocket	*GetSocket(int ComNo)				override;
	virtual	QTcpSocket	*GetIntegrationSocket(int slaveNo)	override;

	virtual	GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)	override;
	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)				override;
	virtual	void	GUIRemoveItem(GUIFormBase *w)				override;
	virtual	GUIInstancePack		*GetGUIInstancePack(void)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override	{	if(GetExecuteInspect()!=NULL)	GetExecuteInspect()->SpecifiedDirectly(v);	}
	virtual	void	LoopOnIdle(void)	override;
};

inline	EntryPointForGlobal::EntryPointForGlobal(void)
{	
	ExecuteInspectBasePointer		=NULL;
	DirectCommBase					=NULL;
}

#endif
