/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInExe.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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

