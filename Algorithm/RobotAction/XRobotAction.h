#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"
#include "XYCross.h"
#include "XRobotControl.h"

#define	RobotActionVersion	1

class	RobotActionItem;
class	RobotActionInPage;
class	RobotActionBase;

//==========================================================================================

class	RobotActionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	RobotActionDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	RobotActionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	RobotActionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	RobotActionDrawAttr	&operator=(RobotActionDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	RobotActionDrawAttr::RobotActionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	RobotActionDrawAttr	&RobotActionDrawAttr::operator=(RobotActionDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	RobotActionDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	RobotActionDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}
//========================================================================================
class	RobotActionThreshold : public AlgorithmThreshold
{
public:

	RobotActionThreshold(RobotActionItem *parent);

	//virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)								override	{	return true;	}
    virtual	bool	Load(QIODevice *f)								override	{	return true;	}
	//virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	//virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	//
	//virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

};
class	RobotActionItem: public AlgorithmItemPITemplate<RobotActionInPage,RobotActionBase>
{
	
public:
	RobotActionItem(void){}

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new RobotActionItem();	}
	//virtual	bool		Save(QIODevice *f)					override;
	//virtual	bool		Load(QIODevice *f,LayersBase *LBase)override;
	const	RobotActionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const RobotActionThreshold *)GetThresholdBaseReadable(base);	}
	RobotActionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (RobotActionThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new RobotActionThreshold(this);	}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	//virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	//virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    //virtual	RobotActionItem &operator=(const AlgorithmItemRoot &src) override;

	//virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	//virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
	//virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	//virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	//virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

};


//========================================================================================

class	ActionMarkBase : public ServiceForLayers ,public NPList<ActionMarkBase>
{
protected:
	QPixmap	*IconP;
	QPixmap	*IconM;
	int32			LoadedVer;
	XYClass			MarkPoint;
	RobotActionBase	*ABase;
	bool			Selected	;
	bool			Active		;
public:
	ActionMarkBase(LayersBase *base,RobotActionBase *aBase);
	~ActionMarkBase(void);

	void	SetXY(int x ,int y);
	virtual	int32	GetClassID(void)		=0;
	virtual	QString	GetTypeName(void)		=0;
	virtual	QString	GetAlgoLibName(void)	=0;
	virtual	QString	GetParamStr(void)		=0;
	virtual	ActionMarkBase	*Clone(void)	=0;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	virtual	bool		Save(QIODevice *f)	;					
	virtual	bool		Load(QIODevice *f)	;

	void	CopyFrom(const ActionMarkBase &src);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}

	virtual	bool	ExecuteInitialAfterEdit	(void)	{	return true;	}
	virtual	bool	ExecuteProcessing		(void)	{	return true;	}
};

class ActionMarkContainer : public ServiceForLayers ,public NPListPack<ActionMarkBase> 
{
	RobotActionBase	*ABase;
public:
	ActionMarkContainer(LayersBase *base,RobotActionBase *aBase):ServiceForLayers(base),ABase(aBase){}

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	bool		Save(QIODevice *f)	;					
	bool		Load(QIODevice *f)	;
};


//----------------------------------------------------------------------------------------

class	ActionMarkMove: public ActionMarkBase
{
public:
	float	Speed;
public:
	ActionMarkMove(LayersBase *base,RobotActionBase *aBase);

	virtual	int32	GetClassID(void)		override		{	return 1;	}
	virtual	QString	GetTypeName(void)		override;
	virtual	QString	GetAlgoLibName(void)	override;
	virtual	QString	GetParamStr(void)		override;
	virtual	ActionMarkBase	*Clone(void)	override	{	return new ActionMarkMove(GetLayersBase(),ABase);	}
	virtual	bool		Save(QIODevice *f)	override;
	virtual	bool		Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

    ActionMarkMove &operator=(const ActionMarkMove &src);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ExecuteInitialAfterEdit	(void)	override;
	virtual	bool	ExecuteProcessing		(void)	override;

};
//========================================================================================
class RobotActionCaptureItem;

class	ActionMarkCapture : public ActionMarkBase
{
public:
	int32	AlgorithmType	;
	int32	AlgorithmPhase	;
	int32	AlgorithmPage	;
	int32	AlgorithmLayer	;
	int32	AlgorithmItemID	;	
	float	StopMilisec		;
public:
	ActionMarkCapture(LayersBase *base,RobotActionBase *aBase);

	virtual	int32	GetClassID(void)	override		{	return 2;	}
	virtual	QString	GetTypeName(void)	override;
	virtual	QString	GetAlgoLibName(void)	override;
	virtual	QString	GetParamStr(void)		override;
	virtual	ActionMarkBase	*Clone(void)	override	{	return new ActionMarkCapture(GetLayersBase(),ABase);	}
	virtual	bool		Save(QIODevice *f)	override;
	virtual	bool		Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

    ActionMarkCapture &operator=(const ActionMarkCapture &src);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ExecuteInitialAfterEdit	(void)	override;
	virtual	bool	ExecuteProcessing		(void)	override;

private:
	AlgorithmItemRoot	*GetOperationItem(void);

};

//========================================================================================

class   RobotActionInPage : public AlgorithmInPagePITemplate<RobotActionItem,RobotActionBase>
{
public:

	RobotActionInPage(AlgorithmBase *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

};

class	RobotActionBase : public QObject ,public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;

	QByteArray			RobotParamArray;
	RobotClassPack		RobotPack;
	ActionMarkContainer	RContainer;

	RobotActionBase(LayersBase *Base);

	virtual	void	InitialAfterParamLoaded(void)	override;

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new RobotActionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	bool	SaveUnique(QIODevice *f)	override;
	virtual	bool	LoadUnique(QIODevice *f)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("RobotAction");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigRobotAction.dat");		}

	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)	override;

};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	RobotActionHistogramListReqCommand		3
#define	RobotActionHistogramListSendCommand		4
#define	RobotActionReqThresholdReqCommand			5
#define	RobotActionReqThresholdSendCommand		6
#define	RobotActionReqTryThresholdCommand			7
#define	RobotActionSendTryThresholdCommand		8
#define	RobotActionReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All	10
//==================================================================================
class	CmdGetRobotActionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetRobotActionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRobotActionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetRobotActionLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetRobotActionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRobotActionLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempRobotActionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearRobotActionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertRobotActionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateRobotActionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRobotActionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteRobotActionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteRobotActionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteRobotActionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempRobotActionItemPacket : public GUIDirectMessage
{
public:
	RobotActionItem	*Point;
	CmdCreateTempRobotActionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRobotActionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromRobotActionItemPacket : public GUIDirectMessage
{
public:
	RobotActionItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromRobotActionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromRobotActionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRobotActionItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			LibID;

	CmdAddRobotActionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRobotActionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRobotActionItemPacketFromByteArray : public GUIDirectMessage
{
public:
	RobotActionItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadRobotActionItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRobotActionItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRobotActionResultInItem : public GUIDirectMessage
{
public:
	double	Radian;
	int		XoomSize;
	int		ResultIndex;
	CmdRobotActionResultInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionResultInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//-----------------------------------------------------------------------------------------------
class	CmdRobotActionAddMove: public GUIDirectMessage
{
public:
	int		UniversalDx,UniversalDy;
	float	Speed;

	CmdRobotActionAddMove(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionAddMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRobotActionModifyMove: public GUIDirectMessage
{
public:
	float	Speed;
	int		Number;

	CmdRobotActionModifyMove(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionModifyMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRobotActionAddCapture: public GUIDirectMessage
{
public:
	int		UniversalDx,UniversalDy;
	int32	AlgorithmType	;
	int32	AlgorithmPhase	;
	int32	AlgorithmPage	;
	int32	AlgorithmLayer	;
	int32	AlgorithmItemID	;	
    float	StopMilisec;

	CmdRobotActionAddCapture(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionAddCapture(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRobotActionModifyCapture: public GUIDirectMessage
{
public:
	int32	AlgorithmType	;
	int32	AlgorithmPhase	;
	int32	AlgorithmPage	;
	int32	AlgorithmLayer	;
	int32	AlgorithmItemID	;	
    float	StopMilisec;
	int		Number;

	CmdRobotActionModifyCapture(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionModifyCapture(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRobotActionClear: public GUIDirectMessage
{
public:

	CmdRobotActionClear(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionClear(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRobotTeachingMode: public GUIDirectMessage
{
public:
	bool	TeachingMode;

	CmdRobotTeachingMode(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotTeachingMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

