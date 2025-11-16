#if	!defined(XSERVERLAYERBASE_H)
#define	XSERVERLAYERBASE_H

#include "XDataInLayer.h"
#include "NList.h"
#include "XFlexArea.h"
#include <QByteArray>
#include "XEntryPoint.h"
class	ServerLayerBase;

class	ServerEntryPoint : public EntryPointBase
{
	ServerLayerBase	*Base;
public:
	ServerEntryPoint(ServerLayerBase *base):Base(base){}

	virtual	LayersBase			*GetLayersBase(void)		const	override;
	virtual	ThreadSequence		*GetThreadSequence(void)	const	override{	return NULL;	}
	virtual	ExecuteInspectBase	*GetExecuteInspect(void)	const	override{	return NULL;	}
	virtual	void				SetLanguageCode(int LanguageCode)	override{}
	virtual	PieceClass			*SearchAndLoadPiece(int masterCode,QString &ErrorMessageOfFalse)	override
										{	return NULL;	}

	virtual	bool		SendData (int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)						override{	return false;	}
	virtual	bool		SendDataDirectComm(int32 commID ,int privatePage
										,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
										,QBuffer *f ,ErrorCodeList &ErrorData)				override{	return false;	}
	virtual	bool		SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)						override{	return false;	}


	virtual	bool		SendArray(int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray *f,ErrorCodeList &ErrorData)					override{	return false;	}
								
	virtual	QTcpSocket	*GetSocket(int ComNo)											override{	return NULL;	}
	virtual	QTcpSocket	*GetIntegrationSocket(int slaveNo)								override{	return NULL;	}
	virtual	void	ReadyReadDirectComm(void)		override{}

	virtual	GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)	override{	return NULL;	}
	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)	override{}
	virtual	bool	GUIIsEditMode(void)											override{	return false;	}
	virtual	void	GUIRemoveItem(GUIFormBase *w)								override{}
	virtual	GUIInstancePack		*GetGUIInstancePack(void)						override{	return NULL;	}
	virtual	GUIFormBase	*ShowOtherGUI(GUIFormBase *ChainedParent
									,const QString &GUIFileName 
									,LayersBase *LayersBasePointer ,bool EditMode=false)	override{	return NULL;	}

	virtual	DirectComm			*CreateDirectComm(QObject * parent)				override{	return NULL;	}
	virtual	bool				InitialDirectCommInSlave(DirectComm	*p,QObject * parent ,SystemConnectionInfoContainer &)	override{	return false;	}

	virtual	int					GetDirectCommIDFromGlobalPage(int globalPageTo)	override{	return globalPageTo;	}
	virtual	void	WaitReadyReadAll(int milisec)			override{}

	virtual	void	LoopOnIdle(void)	override	{}

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override{}
};


class	ServerLayerBase : public LayersBase , public NPList<ServerLayerBase>
{
	Q_OBJECT
		
	LayersBase			*ParentLayerBase;
public:
	FlexArea	PointArea;
	int			SampleType;

	ServerLayerBase(LayersBase *ParentLayerBase ,EntryPointBase *PInspectionData);
	virtual	~ServerLayerBase(void);

	bool	InitialForServer(int XSize ,int YSize ,int Layer);
	bool	LoadItemParamData(int LibType , int LibID ,QByteArray &Array);
};

#endif
