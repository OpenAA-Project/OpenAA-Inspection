#if	!defined(XProjectedInspection_H)
#define	XProjectedInspection_H


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XStandardCommand.h"

#define	ProjectedInspectionVersion	4

class	ProjectedInspectionItem;
class	ProjectedInspectionInLayer;
class	ProjectedInspectionInPage;
class	ProjectedInspectionBase;


class	ProjectedInspectionItem;
class	ProjectedInspectionInPage;
class	ProjectedInspectionLibrary;


//==========================================================================================

class	ProjectedInspectionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;

	ProjectedInspectionDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	ProjectedInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol),ServiceForLayers(Base){}
	ProjectedInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
		,ServiceForLayers(Base)
	{	
		AreaColor			=ncol;	
		NegAreaColor		=acol;	
		NegAreaColorSelected=scol;	
		AreaColor			.setAlpha(ntranparentLevel);
		NegAreaColor		.setAlpha(atranparentLevel);
		NegAreaColorSelected.setAlpha(stranparentLevel);
	}

	ProjectedInspectionDrawAttr	&operator=(ProjectedInspectionDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	ProjectedInspectionDrawAttr	&ProjectedInspectionDrawAttr::operator=(ProjectedInspectionDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	ProjectedInspectionDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	ProjectedInspectionDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}
//========================================================================================
//========================================================================================
class	ProjectedInspectionThreshold : public AlgorithmThreshold
{
	friend	class	ProjectedInspectionItem ;

public:
	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;
	float	OKWidthDiffereceH;	//暗側　平均輝度値よりこの輝度以下に暗くなったらNG
	float	OKWidthDiffereceL;	//明側　平均輝度値よりこの輝度以上に明るくなったらNG
	bool	UseAbsolute;		//輝度値を絶対値を使うか？
	bool	CircleMode	;
	int32	EvenLength;			//平均値算出のバンド長さ
	double	PartialSwingAngle;	//振り角度(ラジアン）

	ProjectedInspectionThreshold(ProjectedInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer) 	const	override;
};


class	ProjectedInspectionItem : public AlgorithmItemPLITemplate<ProjectedInspectionInLayer,ProjectedInspectionInPage,ProjectedInspectionBase>
{
	friend	class	ProjectedInspectionThreshold;

	double	SCos,SSin;
	double	MasterCx,MasterCy;
	int		LMinD;
	int		LMaxD;
	double	MinD;
	double	MaxD;
public:
	AlignmentPacket2D	*AVector;

	double	*ProjectedData;
	double	*BlockVDim;
	int		AllocatedBlockVDimNumb;
	int		BlockNumb;
	int		*ProjectedDots;
	BYTE	*ProjectedResult;
	double	*ProjectedSize;
	double	*ProjectedThreH;
	double	*ProjectedThreL;
	int		ProjectedDataLen;

	ProjectedInspectionItem(void);
	~ProjectedInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ProjectedInspectionItem();	}
	void Release(void);

	const	ProjectedInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ProjectedInspectionThreshold *)GetThresholdBaseReadable(base);	}
	ProjectedInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ProjectedInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ProjectedInspectionThreshold(this);	}

	void	CopyThreshold(ProjectedInspectionItem &src);
	void	CopyThresholdOnly(ProjectedInspectionItem &src);

	virtual	int32		GetItemClassType(void)	override	{		return 0;		}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	ProjectedInspectionItem		&operator=(ProjectedInspectionItem &src);
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

private:
	double  GetLinePointFoot(double Cx,double Cy ,double px ,double py ,double &X ,double &Y);
	void	PjDrawLine(ResultInItemRoot &Res,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,int x1, int y1 ,int x2, int y2);
	void	NDrawLine (ResultInItemRoot &Res,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,double x1, double y1 ,double x2, double y2);

	void	ExecuteAverateTable(void);
	void	MakeThreshold(void);
	void	ExecuteJudgement(void);
};

class   ProjectedInspectionInLayer : public AlgorithmInLayerPLITemplate<ProjectedInspectionItem,ProjectedInspectionInPage,ProjectedInspectionBase>
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
public:
	ProjectedInspectionInLayer(AlgorithmInPageRoot *parent);
	~ProjectedInspectionInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	CreatePickupBmpBuff(void);
	void	PickupTest(ProjectedInspectionLibrary &LibData);
	void	GenerateBlocks(ProjectedInspectionLibrary *LibDim[],int LibDimNumb);

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

};

class   ProjectedInspectionInPage : public AlgorithmInPagePLITemplate<ProjectedInspectionItem,ProjectedInspectionInLayer,ProjectedInspectionBase>
{

public:
	ProjectedInspectionInPage(AlgorithmBase *parent);
	~ProjectedInspectionInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new ProjectedInspectionInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	PickupTest(IntList &LayerList ,ProjectedInspectionLibrary &LibData);
	void	GenerateBlocks(IntList &LayerList, ProjectedInspectionLibrary *LibDim[],int LibDimNumb);

private:

};

class	ProjectedInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorPickup;
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	int		OmitZoneDot;

	ProjectedInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)override{	return new ProjectedInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	QString	GetDataText(void)			override{	return QString("ProjectedInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigProjectedInspection.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)				override;
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==================================================================================
class	ProjectedInspectionHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ProjectedInspectionHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ProjectedInspectionHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	double	*ProjectedData;
	int		*ProjectedDots;
	int		ProjectedDataLen;

	ProjectedInspectionHistogramListSend(void);
	~ProjectedInspectionHistogramListSend(void);

	void	ConstructList(ProjectedInspectionHistogramListReq *reqPacket,ProjectedInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ProjectedInspectionThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ProjectedInspectionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ProjectedInspectionThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;
	int32	OKWidthDiffereceL;
	int32	OKWidthDiffereceH;
	bool	UseAbsolute;		//輝度値を絶対値を使うか？
	int32	EvenLength;			//平均値算出のバンド長さ
	double	PartialSwingAngle;

	ProjectedInspectionThresholdSend(void);

	void	ConstructList(ProjectedInspectionThresholdReq *reqPacket,ProjectedInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	ProjectedInspectionReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;	
	ProjectedInspectionItem	Threshold;

	ProjectedInspectionReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	ProjectedInspectionSendTryThreshold : public AddedDataClass
{
public:
	int		NGDots;
	int		Error;
	ResultInItemRoot	*Result;

	ProjectedInspectionSendTryThreshold(void);
	~ProjectedInspectionSendTryThreshold(void);

	void	ConstructList(ProjectedInspectionReqTryThreshold *reqPacket,ProjectedInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ProjectedInspectionChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ProjectedInspectionItemID;
	int32	Dx,Dy;

	ProjectedInspectionChangeShift(void){}

	void	Reflect(ProjectedInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	SetIndependentItemNameDataCommand_All	3
#define	ProjectedInspectionHistogramListReqCommand				3
#define	ProjectedInspectionHistogramListSendCommand				4
#define	ProjectedInspectionReqThresholdReqCommand				5
#define	ProjectedInspectionReqThresholdSendCommand				6
#define	ProjectedInspectionReqTryThresholdCommand				7
#define	ProjectedInspectionSendTryThresholdCommand				8
#define	ProjectedInspectionReqChangeShiftCommand				9

//===================================================================================
class	ProjectedInspectionInfoList : public  NPListSaveLoad<ProjectedInspectionInfoList>
{
public:
	int	GlobalPage;
	int	Layer;
	int	ItemID;
	int	LibID;
	int	x1,y1,x2,y2;

	ProjectedInspectionInfoList(void){}

	ProjectedInspectionInfoList	&operator=(ProjectedInspectionInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ProjectedInspectionInfoContainer : public NPListPackSaveLoad<ProjectedInspectionInfoList>
{
public:
	ProjectedInspectionInfoContainer(void){}
	virtual	ProjectedInspectionInfoList	*Create(void){	return new ProjectedInspectionInfoList();	}
};

inline	ProjectedInspectionInfoList	&ProjectedInspectionInfoList::operator=(ProjectedInspectionInfoList &src)
{
	GlobalPage	=src.GlobalPage;
	Layer		=src.Layer;
	ItemID		=src.ItemID;
	LibID		=src.LibID;
	x1			=src.x1;
	y1			=src.y1;
	x2			=src.x2;
	y2			=src.y2;
	return *this;
}

inline	bool	ProjectedInspectionInfoList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	return true;
}
inline	bool	ProjectedInspectionInfoList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	return true;
}

//===================================================================================
class	CmdGetProjectedInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetProjectedInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProjectedInspectionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetProjectedInspectionLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetProjectedInspectionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProjectedInspectionLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempProjectedInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearProjectedInspectionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertProjectedInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateProjectedInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadProjectedInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteProjectedInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteProjectedInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteProjectedInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestProjectedInspectionPacket : public GUIDirectMessage
{
public:
	//ProjectedInspectionLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestProjectedInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestProjectedInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateProjectedInspectionPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	IntList		LayerList;
	int			Page;
	CmdGenerateProjectedInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateProjectedInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempProjectedInspectionItemPacket : public GUIDirectMessage
{
public:
	ProjectedInspectionItem	*Point;
	CmdCreateTempProjectedInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempProjectedInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromProjectedInspectionItemPacket : public GUIDirectMessage
{
public:
	ProjectedInspectionItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromProjectedInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromProjectedInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteProjectedInspectionItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LibID;
	IntList		LayerList;
	CmdAddByteProjectedInspectionItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteProjectedInspectionItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadProjectedInspectionItemPacketFromByteArray : public GUIDirectMessage
{
public:
	ProjectedInspectionItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadProjectedInspectionItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadProjectedInspectionItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedProjectedInspectionFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedProjectedInspectionFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedProjectedInspectionFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestProjectedInspectionPacket: public GUIDirectMessage
{
public:
	CmdClearTestProjectedInspectionPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestProjectedInspectionPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdProjectedInspectionInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	ProjectedInspectionInfoContainer	*ProjectedInspectionInfos;
	CmdProjectedInspectionInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdProjectedInspectionInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetProjectedInspectionFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	ProjectedInspectionItem	*ProjectedInspectionInfoOnMouse;

	CmdGetProjectedInspectionFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProjectedInspectionFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateProjectedInspectionItem: public GUIDirectMessage
{
public:
	ProjectedInspectionItem	*ProjectedInspection;
	CmdCreateProjectedInspectionItem(LayersBase *base):GUIDirectMessage(base){	ProjectedInspection=NULL;	}
	CmdCreateProjectedInspectionItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ProjectedInspection=NULL;	}
};



#endif