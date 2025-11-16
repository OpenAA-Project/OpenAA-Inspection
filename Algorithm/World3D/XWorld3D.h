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
#include "XStepFile.h"

#define	World3DVersion	1

class	World3DItem;
class	World3DRegulation;
class	World3DInPage;
class	World3DBase;
class	World3DLibrary;

class	World3DItem;
class	World3DInPage;
class	MatchingResultList;
class	PalletizingBackItem;
class	RotatedMatchingPattern;

//==========================================================================================

class	World3DDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	World3DDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	World3DDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	World3DDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	World3DDrawAttr	&operator=(World3DDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	World3DDrawAttr::World3DDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	World3DDrawAttr	&World3DDrawAttr::operator=(World3DDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	World3DDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	World3DDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}

//========================================================================================
class	World3DThreshold : public AlgorithmThreshold
{
public:

	World3DThreshold(World3DItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	World3DItem : public AlgorithmItemPITemplate<World3DInPage,World3DBase>
{
public:
	StepFileStructure	StepData;
public:
	World3DItem(void);
	virtual	~World3DItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new World3DItem();	}
	virtual	bool		Save(QIODevice *f)					override;
	virtual	bool		Load(QIODevice *f,LayersBase *LBase)override;
	const	World3DThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const World3DThreshold *)GetThresholdBaseReadable(base);	}
	World3DThreshold			*GetThresholdW(LayersBase *base=NULL){	return (World3DThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new World3DThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	World3DItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(World3DItem &src);
	void	CopyThresholdOnly(World3DItem &src);
	void	CopyArea(World3DItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;


};

//========================================================================================

class   World3DInPage : public AlgorithmInPagePITemplate<World3DItem,World3DBase>
{
public:
	World3DInPage(AlgorithmBase *parent);
	~World3DInPage(void);

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

class	World3DBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	double	PickupLineVar;
	double	AffinParam[6];
	double	MinAvrage;		//Background;

	World3DBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new World3DInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("World3D");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigWorld3D.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	World3DHistogramListReqCommand		3
#define	World3DHistogramListSendCommand		4
#define	World3DReqThresholdReqCommand			5
#define	World3DReqThresholdSendCommand		6
#define	World3DReqTryThresholdCommand			7
#define	World3DSendTryThresholdCommand		8
#define	World3DReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All	10
//==================================================================================
class	CmdGetWorld3DLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetWorld3DLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetWorld3DLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetWorld3DLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetWorld3DLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetWorld3DLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempWorld3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearWorld3DLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertWorld3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateWorld3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadWorld3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteWorld3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteWorld3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteWorld3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempWorld3DItemPacket : public GUIDirectMessage
{
public:
	World3DItem	*Point;
	CmdCreateTempWorld3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempWorld3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromWorld3DItemPacket : public GUIDirectMessage
{
public:
	World3DItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromWorld3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromWorld3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddWorld3DItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			LibID;

	CmdAddWorld3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddWorld3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadWorld3DItemPacketFromByteArray : public GUIDirectMessage
{
public:
	World3DItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadWorld3DItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadWorld3DItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdWorld3DResultInItem : public GUIDirectMessage
{
public:
	double	Radian;
	int		XoomSize;
	int		ResultIndex;
	CmdWorld3DResultInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdWorld3DResultInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadStepFile : public GUIDirectMessage
{
public:
	QByteArray	FArray;

	CmdLoadStepFile(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadStepFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};