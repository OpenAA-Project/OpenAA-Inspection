#pragma once

#include "XTypeDef.h"
#include <QString>
#include <QBuffer>
#include <QTcpSocket>
#include <QMouseEvent>
#include <QString>

class	GUIFormBase;
class	ThreadSequence;
class	ExecuteInspectBase;
class	GUIInstancePack;
class	ErrorCodeList;
class	PieceClass;
class	DirectComm;
class	SpecifiedBroadcaster;
class	SystemConnectionInfoContainer;
class	LayersBase;

class	EntryPointBase
{
	LayersBase	*Base;
	bool		EditMode;
public:
	bool		NoCamDevice;

	struct EntryPointPacketInfo
	{
		int32	cmd;
		int32	ShadowLevel ;
		int32	ShadowNumber;
		int32	IDForUndo;
		const	QString &EmitterRoot;
		const	QString &EmitterName;
		const	QString &CmdClass;

		EntryPointPacketInfo(int32	_cmd
							,int32	_ShadowLevel
							,int32	_ShadowNumber
							,int32	_IDForUndo
							,const QString &_EmitterRoot
							,const QString &_EmitterName
							,const QString &_CmdClass)
			:cmd(_cmd)
			,ShadowLevel(_ShadowLevel),ShadowNumber(_ShadowNumber)
			,IDForUndo(_IDForUndo)
			,EmitterRoot(_EmitterRoot)
			,EmitterName(_EmitterName)
			,CmdClass(_CmdClass)
		{}
	};

	EntryPointBase(void);
	virtual	~EntryPointBase(void){}

	void	SetLayersBase(LayersBase *base)						{	Base=base;		}
	virtual	LayersBase			*GetLayersBase(void)	const	{	return Base;	}
	virtual	ThreadSequence		*GetThreadSequence(void)const	=0;
	virtual	ExecuteInspectBase	*GetExecuteInspect(void)const	=0;
	virtual	void				SetLanguageCode(int LanguageCode)	=0;
	virtual	PieceClass			*SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)	=0;

	virtual	void	SetExecuteInspect(ExecuteInspectBase *e)	{}


	virtual	bool		SendData (int32 commID,int privatePage
								,struct EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)	=0;
	virtual	bool		SendDataDirectComm(int32 commID,int privatePage
										,struct EntryPointPacketInfo &IndoPacket
										,QBuffer *f ,ErrorCodeList &ErrorData)	=0;
	virtual	bool		SendIntegrationData (int slaveNo
										,struct EntryPointPacketInfo &IndoPacket
										,QBuffer *f ,ErrorCodeList &ErrorData)	=0;
	
	virtual	bool		SendArray(int32 commID,int privatePage
								,struct EntryPointPacketInfo &IndoPacket
								,QByteArray *f,ErrorCodeList &ErrorData)	=0;


	virtual	QTcpSocket	*GetSocket(int ComNo)	=0;
	virtual	QTcpSocket	*GetIntegrationSocket(int slaveNo)	=0;
	virtual	void	ReadyReadDirectComm(void)	=0;

	virtual	GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)	=0;
	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)	=0;
	virtual	bool	GUIIsEditMode(void)		{	return EditMode;	}
	virtual	void	GUISetEditMode(bool b)	{	EditMode=b;	}
	virtual	void	GUIRemoveItem(GUIFormBase *w)								=0;
	virtual	GUIInstancePack		*GetGUIInstancePack(void)						=0;
	virtual	GUIFormBase	*ShowOtherGUI(GUIFormBase *ChainedParent
									,const QString &GUIFileName 
									,LayersBase *LayersBasePointer ,bool EditMode=false){	return NULL;	}

	virtual	DirectComm			*CreateDirectComm(QObject * parent)=0;
	virtual	bool				InitialDirectCommInSlave(DirectComm	*p,QObject * parent ,SystemConnectionInfoContainer &)=0;

	virtual	int					GetDirectCommIDFromGlobalPage(int globalPageTo)	=0;
	virtual	void	WaitReadyReadAll(int milisec)			=0;

	int	GetGlobalPageFromLocal(int localPage);
	bool	IsMasterPC(void);
	virtual	void	LoopOnIdle(void)	=0;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	=0;
};

EntryPointBase	*MakeEntryPointForGlobal(void);

//========================================================================================
