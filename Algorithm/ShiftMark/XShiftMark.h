#pragma once

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XYCross.h"
#include "XFlexAreaImage.h"
#include "XStandardCommand.h"

#define	ShiftMarkVersion	5


class   AlignmentInLayer;
class	XAlignmentArea;
class	ShiftMarkLibrary;
class	ShiftMarkBase;
class	ShiftMarkItem;
class	ShiftMarkInPage;
class	SetThresholdShiftMarkInfo;


class	ShiftMarkThreshold : public AlgorithmThreshold
{
public:
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//è¡é∏îªíËÇµÇ´Ç¢ílÅi0-100)
	bool	EnableMark;
	bool	ColorMatch;

	ShiftMarkThreshold(ShiftMarkItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const override;
	virtual	bool	Save(QIODevice *f)				 override;
    virtual	bool	Load(QIODevice *f)				 override;
	virtual	void	FromLibrary(AlgorithmLibrary *src) override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest) override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer) 	const	override;
};


class   ShiftMarkItem : public AlgorithmItemPITemplate<ShiftMarkInPage,ShiftMarkBase>
{
public:
	FlexAreaColorRotatedImageContainer	EdgeArea;
	FlexAreaColorRotatedImageContainer	MarkArea;
public:
	AlignmentPacket2D	*EdgeVector;
	AlignmentPacket2D	*MarkVector;
	double				MarkDistance;

	FlexArea	EdgePoint;
	FlexArea	MarkPoint;
	QColor		MarkColor;
	QColor		PaperColor;
	QColor		BackColor;

	int		ResultEMx;
	int		ResultEMy;
	int		ResultMMx;
	int		ResultMMy;
	double	ResultMPos;
	double	ResultMatchMark;
	double	ResultMarkAngle;	//Radian
public:

	ShiftMarkItem(void);
	virtual	~ShiftMarkItem(void);

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ShiftMarkItem();	}
	const	ShiftMarkThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ShiftMarkThreshold *)GetThresholdBaseReadable(base);	}
	ShiftMarkThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ShiftMarkThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override {	return new ShiftMarkThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	ShiftMarkItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(ShiftMarkItem &src);
	void	CopyThresholdOnly(ShiftMarkItem &src);
	void	CopyArea(ShiftMarkItem &src);
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	override{	return (GetVector()!=NULL)?GetVector()->GetXY(x1,y1,x2,y2):false;	}
	virtual	VectorLineBase	*CreateVectorBase(void)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	void	MoveForAlignment(void)	override;

	virtual	void	MoveTo(int dx ,int dy)	override;
	virtual	void	MasterImageHasChanged(void)	override;
	void	InitialEdgeMark(void);
private:
	bool	MatchMovePoint(bool UseAlignment,ImageBuffer *ImageList[]);
	QColor	GetMarkEdgePointColor(FlexArea &PointArea,ImagePointerContainer &ImageList
											,int dx,int dy ,double Vt);
	void	MoveCenterPosition(int mex,int mey,double eRotation,double mRotation
								,ImageBuffer *ImageList[]);
};


class   ShiftMarkInPage : public AlgorithmInPagePITemplate<ShiftMarkItem,ShiftMarkBase>
{
public:

	ShiftMarkInPage(AlgorithmBase *parent);
	~ShiftMarkInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new ShiftMarkItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	UndoSetIndependentShiftMarkItemNameDataCommand(QIODevice *f);
};

class	ShiftMarkBase	: public AlgorithmBase
{
public:
	QColor		ColorShiftMarkNormal		;
	QColor		ColorShiftMarkSelected	;
	QColor		ColorShiftMarkActive		;
	int			OmitZoneDot;
	int			MaxRotationDegree;
	int			DiffColorH;

	ShiftMarkBase(LayersBase *Base);
	~ShiftMarkBase(void);
	virtual	ShiftMarkInPage	*NewChild(AlgorithmBase *parent)		override	{	return(new ShiftMarkInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)	override{	return QString("ShiftMark");				}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigShiftMark.dat");	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	QString	GetNameByCurrentLanguage(void)	override;

};

//==================================================================================
#define	SetIndepenShiftMarkItemDataCommand_OnlyOne			1
#define	SetIndepenShiftMarkItemDataCommand_All				2
#define	ShiftMarkHistogramListReqCommand						3
#define	ShiftMarkHistogramListSendCommand					4
#define	ShiftMarkReqThresholdReqCommand						5
#define	ShiftMarkReqThresholdSendCommand						6
#define	ShiftMarkReqTryThresholdCommand						7
#define	ShiftMarkSendTryThresholdCommand						8
#define	ShiftMarkReqChangeShiftCommand						9
#define	SetIndepenShiftMarkItemNameDataCommand_All			10
//==================================================================================

class	ShiftMarkDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	int		ShowingItemID;

	ShiftMarkDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	ShiftMarkDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	ShiftMarkDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel);

	void	Initial(void);

	ShiftMarkDrawAttr	&operator=(ShiftMarkDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	ShiftMarkDrawAttr::ShiftMarkDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	ShiftMarkDrawAttr::ShiftMarkDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol,ntranparentLevel,scol,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
,ShowingItemID(-1)
{
}
inline	ShiftMarkDrawAttr	&ShiftMarkDrawAttr::operator=(ShiftMarkDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	ShowingItemID	=src.ShowingItemID;
	return *this;
}
inline	bool	ShiftMarkDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,ShowingItemID)==false)	return false;
	return true;
}
inline	bool	ShiftMarkDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,ShowingItemID)==false)	return false;
	return true;
}

class	ShiftMarkListForPacketPack;

class	MakeShiftMarkListPacket : public GUIDirectMessage
{
public:
	ShiftMarkListForPacketPack	*ListInfo;

	MakeShiftMarkListPacket(LayersBase *base):GUIDirectMessage(base){}
};
