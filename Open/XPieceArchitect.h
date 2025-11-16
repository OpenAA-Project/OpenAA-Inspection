/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPieceArchitect.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPIECEARCHITECT_H)
#define	XPIECEARCHITECT_H

#include "NList.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XEntryPoint.h"

class	GUIInitializer;
class	ExecuteInitialAfterEditInfo;

class	AlgorithmImageList : public NPList<AlgorithmImageList>
{
	QString	DLLRoot;
	QString	DLLName;
	QImage	*Image;
public:

	AlgorithmImageList(void){	Image=NULL;	}
	AlgorithmImageList(const AlgorithmImageList &src)
		:DLLRoot(src.DLLRoot),DLLName(src.DLLName)
		{	Image=new QImage(*src.Image);	}
	AlgorithmImageList(const QString &_DLLRoot
					,  const QString &_DLLName
					,QImage	*_Image)
					:DLLRoot(_DLLRoot),DLLName(_DLLName),Image(_Image){}


	const QString	&GetDLLRoot(void)	const	{	return DLLRoot;		}
	const QString	&GetDLLName(void)	const	{	return DLLName;		}

	QImage	*GetImage(void)		const	{	return Image;		}
	void	DeleteImage(void)			{	delete	Image;	Image=NULL;	}
	void	SetImage(QImage *img)		{	Image=img;	}
};

class	PieceClass : public NPList<PieceClass> , public EntryPointBase
{
	class	PCLayersBase : public LayersBase
	{
		LayersBase	*ParentBase;
	public:
		PCLayersBase(LayersBase *Parent);
		virtual	~PCLayersBase(void);

		bool	Set(LayersBase *Base,int masterCode,PieceClass *parent
						,QString &ErrorMessageOfFalse);
		bool	ReLoadMasterDataForPiece(LayersBase *Base,int masterCode,PieceClass *parent
											,QString &ErrorMessageOfFalse);
		virtual	bool	GetOnTerminating(void)	const	override;
	};
	PCLayersBase	*PieceLayersBase;
	double	ZoomRateOnImage;
	IntList LayerListOnImage;
	NPListPack<AlgorithmImageList>	ImageList;

public:
	PieceClass(void);
	PieceClass(const PieceClass &src);
	~PieceClass(void);

	PieceClass	&operator=(const PieceClass &src);
	bool	Initial(LayersBase *Base,int masterCode,QString &ErrorMessageOfFalse);
	int		GetMasterCode(void)	const	{	return (PieceLayersBase!=NULL)?PieceLayersBase->GetMasterCode():-1;	}

	virtual	LayersBase			*GetLayersBase(void)		const	override	{	return PieceLayersBase;		}
	virtual	ThreadSequence		*GetThreadSequence(void)	const	override;
	virtual	ExecuteInspectBase	*GetExecuteInspect(void)	const	override;
	virtual	DirectComm			*CreateDirectComm(QObject * parent)	override;
	virtual	bool				InitialDirectCommInSlave(DirectComm	*p,QObject * parent ,SystemConnectionInfoContainer &)	override;
	virtual	int					GetDirectCommIDFromGlobalPage(int globalPageTo)	override;
	virtual	void				SetLanguageCode(int LanguageCode)	override;	
	virtual	PieceClass			*SearchAndLoadPiece(int masterCode ,QString &ErrorMessageOfFalse)	override{	return NULL;	}
	bool	ReLoadMasterDataForPiece(LayersBase *Base,QString &ErrorMessageOfFalse);

	virtual	bool		SendData (int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f 
								,ErrorCodeList &)						override;
	virtual	bool		SendArray(int32 commID ,int privatePage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray *f 
								,ErrorCodeList &)						override;
	virtual	bool		SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f ,ErrorCodeList &ErrorData)	override;	
	virtual	bool		SendDataDirectComm(int32 commID ,int privatePage
										,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
										,QBuffer *f 
										,ErrorCodeList &ErrorData)		override;

	virtual	void		ReadyReadDirectComm(void)	override;

	virtual	QTcpSocket	*GetSocket(int ComNo)											override;
	virtual	QTcpSocket	*GetIntegrationSocket(int slaveNo)								override;

	virtual	void		WaitReadyReadAll(int milisec)									override;

	virtual	GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event)	override;
	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)			override;
	virtual	bool	GUIIsEditMode(void)						override;
	virtual	void	GUIRemoveItem(GUIFormBase *w)			override;
	virtual	GUIInstancePack		*GetGUIInstancePack(void)	override;

	AlgorithmItemRoot	*GetAlgorithmItem(const QString &DLLRoot,const QString &DLLName,int Layer ,int ItemID)	;
	bool	SetAlgorithmItemData(int Command ,const QString &DLLRoot,const QString &DLLName ,AlgorithmItemIndependentPack &IData)	;
	bool	SaveAlgorithmForMaster(const QString &DLLRoot,const QString &DLLName)	;

	QImage	*GetAlgorithmImage(int LocalPage
							,IntList &LayerList ,const QString &DLLRoot ,const QString &DLLName 
							,double ZoomRate ,const QColor &ncol ,int ntranparentLevel);
	ExeResult	ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo)	;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override{}
	virtual	void	LoopOnIdle(void)	override{}
};

class	PieceStocker : public NPListPack<PieceClass>,public ServiceForLayers
{
	QReadWriteLock	MutexLoader;
	QMutex			MutexPieceInitializer;
public:
	PieceStocker(LayersBase	*base):ServiceForLayers(base){}

	PieceClass	*SearchAndLoad(int masterCode,QString &ErrorMessageOfFalse);
	PieceClass	*SearchOnly(int masterCode);
	void	RemoveFromList(PieceClass *p);
	QImage	*GetAlgorithmImage(int LocalPage
								,int MasterCode ,IntList &LayerList 
								,const QString &DLLRoot ,const QString &DLLName 
								,double ZoomRate ,const QColor &ncol ,int ntranparentLevel
								,QString &ErrorMessageOfFalse);
	bool	ReLoadMasterDataForPiece(QString &ErrorMessageOfFalse);
	bool	ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo
									,QString &ErrorMessageOfFalse);
};

//=======================================================

class	GUICmdReqUpdateAlgorithmOnPiece : public GUICmdPacketBase
{
public:
	int32		PieceCode;
	QString		DLLRoot;
	QString		DLLName;
	AlgorithmItemIndependentPack		IData;
	int32		Command;

	GUICmdReqUpdateAlgorithmOnPiece(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckUpdateAlgorithmOnPiece : public GUICmdPacketBase
{
public:
	bool	Ret;
	GUICmdAckUpdateAlgorithmOnPiece(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
