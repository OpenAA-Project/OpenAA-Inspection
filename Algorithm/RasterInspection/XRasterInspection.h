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
#include "XReferencePDF.h"

#define	RasterInspectionVersion	1

class	RasterInspectionItem;
class	RasterInspectionRegulation;
class	RasterInspectionInPage;
class	RasterInspectionBase;
class	RasterInspectionLibrary;

class	RasterInspectionItem;
class	RasterInspectionInPage;
class	MatchingResultList;
class	PalletizingBackItem;
class	RotatedMatchingPattern;

//==========================================================================================

class	RasterInspectionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ShowItems;
	bool	ShowResult;
	bool	ModeShowPDF;
	bool	ModeShowItemImage;

	RasterInspectionDrawAttr(LayersBase *Base):ServiceForLayers(Base){	ShowItems=true;	ShowResult=true;	}
	RasterInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	RasterInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	RasterInspectionDrawAttr	&operator=(RasterInspectionDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	RasterInspectionDrawAttr::RasterInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	ShowItems			=true;
	ShowResult			=true;
	ModeShowPDF			=false;
	ModeShowItemImage	=false;
}

inline	RasterInspectionDrawAttr	&RasterInspectionDrawAttr::operator=(RasterInspectionDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	ShowItems			=src.ShowItems;
	ShowResult			=src.ShowResult;
	ModeShowPDF			=src.ModeShowPDF;
	ModeShowItemImage	=src.ModeShowItemImage;
	return *this;
}

inline	bool	RasterInspectionDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	if(::Save(f,ShowItems)==false)
		return false;
	if(::Save(f,ShowResult)==false)
		return false;
	if(::Save(f,ModeShowPDF)==false)
		return false;
	if(::Save(f,ModeShowItemImage)==false)
		return false;
	return true;
}
inline	bool	RasterInspectionDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	if(::Load(f,ShowItems)==false)
		return false;
	if(::Load(f,ShowResult)==false)
		return false;
	if(::Load(f,ModeShowPDF)==false)
		return false;
	if(::Load(f,ModeShowItemImage)==false)
		return false;
	return true;
}

//========================================================================================
class	RasterInspectionThreshold : public AlgorithmThreshold
{
public:
	double	GenColorDistance;
	int		SearchAreaDot;
	double	SearchWaveDiv;
	double	WaveDistance;
	int		OKDot;

	RasterInspectionThreshold(RasterInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

};

class	RasterInspectionItem : public AlgorithmItemPITemplate<RasterInspectionInPage,RasterInspectionBase>
{
	AlignmentPacket2D		*AVector;
	int						ResultDx,ResultDy;
	FlexAreaColorImage		ColorArea;
	ImageBuffer				**TargetImageList;
	BYTE					**YIndex;
	BYTE					*TargetC;

	BYTE	**Map;
	BYTE	**DummyMap;
	int		MapXByte;
	int		MapYLen;
public:
	RasterInspectionItem(void);
	virtual	~RasterInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new RasterInspectionItem();	}
	void	SetAreaWithImage(FlexArea &area,ImageBufferListContainer &ImageContainer);

	const	RasterInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const RasterInspectionThreshold *)GetThresholdBaseReadable(base);	}
	RasterInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (RasterInspectionThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new RasterInspectionThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	//virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	
	void	CopyThreshold(RasterInspectionItem &src);
	void	CopyThresholdOnly(RasterInspectionItem &src);
    bool    Save(QIODevice *file)					override;
    bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:
	bool	CalcDistance	(const RasterInspectionThreshold *RThr,int MasterX,int MasterY,BYTE *TargetC);
	bool	CalcDistanceFix	(const RasterInspectionThreshold *RThr,int MasterX,int MasterY,BYTE *TargetC);
};

//========================================================================================
#pragma	pack(push,1)
struct ReferenceIndex
{
	int32	Index1;
	int32	Index2;
	int32	Index3;
};
#pragma	pack(pop)

class   RasterInspectionInPage : public AlgorithmInPagePITemplate<RasterInspectionItem,RasterInspectionBase>
{
public:
	ImageBufferListContainer	MasterByPDF;

	RasterInspectionInPage(AlgorithmBase *parent);
	~RasterInspectionInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)					override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)						override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	void	GenerateRasterInspection(RasterInspectionLibrary *LibDim[],int LibDimNumb);
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
private:
	bool	UseLibraryForMaskingInOtherPage(int LibID);
};

class	RasterInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int		OmitZoneDot;
	int		TransparentPDF;

	ReferencePDFContainer   RContainer;

	RasterInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new RasterInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("RasterInspection");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigRasterInspection.dat");		}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//==================================================================================

class	RasterInspectionThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	RasterInspectionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RasterInspectionThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	double	GenColorDistance;
	int		SearchAreaDot;
	double	SearchWaveDiv;
	double	WaveDistance;
	int		OKDot;

	RasterInspectionThresholdSend(void);

	void	ConstructList(RasterInspectionThresholdReq *reqPacket,RasterInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	RasterInspectionReqTryThreshold
{
public:
	RasterInspectionItem	Threshold;
	struct RasterInspectionReqTryThresholdStruct
	{
		int32	GlobalPage		;
		int		ItemID			;	
		double	GenColorDistance;
		int		SearchAreaDot	;
		double	SearchWaveDiv	;
		double	WaveDistance	;
		int		OKDot			;
	}Data;

	RasterInspectionReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	RasterInspectionSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;

	RasterInspectionSendTryThreshold(void);
	~RasterInspectionSendTryThreshold(void);

	void	ConstructList(RasterInspectionReqTryThreshold *reqPacket,RasterInspectionBase *Base);
	void	Calc(RasterInspectionItem *Target,RasterInspectionItem *Src,RasterInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	RasterInspectionHistogramListReqCommand		3
#define	RasterInspectionHistogramListSendCommand	4
#define	RasterInspectionReqThresholdReqCommand		5
#define	RasterInspectionReqThresholdSendCommand		6
#define	RasterInspectionReqTryThresholdCommand		7
#define	RasterInspectionSendTryThresholdCommand		8
#define	RasterInspectionReqChangeShiftCommand		9
#define	SetIndependentItemNameDataCommand_All		10
//==================================================================================
class	CmdGetRasterInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetRasterInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterInspectionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetRasterInspectionLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetRasterInspectionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterInspectionLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempRasterInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearRasterInspectionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertRasterInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateRasterInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRasterInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteRasterInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteRasterInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteRasterInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempRasterInspectionItemPacket : public GUIDirectMessage
{
public:
	RasterInspectionItem	*Point;
	CmdCreateTempRasterInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRasterInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromRasterInspectionItemPacket : public GUIDirectMessage
{
public:
	RasterInspectionItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromRasterInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromRasterInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRasterInspectionItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			LibID;

	CmdAddRasterInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRasterInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRasterInspectionItemPacketFromByteArray : public GUIDirectMessage
{
public:
	RasterInspectionItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadRasterInspectionItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRasterInspectionItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterInspectionResultInItem : public GUIDirectMessage
{
public:
	double	Radian;
	int		XoomSize;
	int		ResultIndex;
	CmdRasterInspectionResultInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterInspectionResultInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterAddReferencePDF : public GUIDirectMessage
{
public:
	ReferencePDF	RData;

	CmdRasterAddReferencePDF(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterAddReferencePDF(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterShowReferencePDF : public GUIDirectMessage
{
public:
	bool	Deletable;
	ReferencePDF	RData;

	CmdRasterShowReferencePDF(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterShowReferencePDF(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterShowReferencePDFList : public GUIDirectMessage
{
public:
	CmdRasterShowReferencePDFList(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterShowReferencePDFList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateRasterInspection : public GUIDirectMessage
{
public:
	IntList			LibList;

	CmdGenerateRasterInspection(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateRasterInspection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
