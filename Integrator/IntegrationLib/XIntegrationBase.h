#if	!defined(XIntegrationBase_h)
#define	XIntegrationBase_h

#include <QObject>
#include <QImage>
#include <QString>
#include <QByteArray>

#include "XTypeDef.h"
#include "NListComp.h"
#include "XYCross.h"
#include "XDateTime.h"
#include "XServiceForLayers.h"
#include "XParamIntegrationMaster.h"
#include "XMainSchemeMemory.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XResult.h"

class	IntegrationBase;
class	EachMaster;
class	IntegrationCommPack;
class	InspectionList;
class	NGPointInPage;
class	NGPointInAllPage;
class	NGPointInAllPhase;
class	NGPointPointerList;
class	SystemResultStocker;

class   NGPoint : public NPList<NGPoint>
{
  public:
#pragma	pack(push,1)
	short	Error;
	DWORD	PosResult;
    //int32	TargetX,TargetY;
	int32	MasterX,MasterY;
	int32	MX,MY;		//Shift by Alignment
	int32	HX,HY;		//Shift by itself
	union{
		int32	Cause[2];
		char	Message[8];
	};
	_ResultType	ResultType;
	union{
		
		double	DoubleCause;
	};
	int32	LibType;
	int32	LibID;
	int32	Index;
	int32	UniqueID;
	int8	ShadowLevel		;
	int8	ShadowNumber	;
	QByteArray	ExtraData;
	NGPointInPage	*PagePoint;
#pragma	pack(pop)

    NGPoint(NGPointInPage *p)			
		:MasterX(0) ,MasterY(0) ,LibType(-1),LibID(-1),Index(-1)
		,UniqueID(-1),ShadowLevel(0),ShadowNumber(0),PagePoint(p){}
    NGPoint(NGPointInPage *p,int _x,int _y)	
		:MasterX(_x),MasterY(_y),LibType(-1),LibID(-1),Index(-1)
		,UniqueID(-1),ShadowLevel(0),ShadowNumber(0),PagePoint(p){}
    NGPoint(const NGPoint &src);

	bool	IsOK(void)	const	{	return (Error==1)?true:false;	}
	bool	IsNG(void)	const	{	return (Error>1)?true:false;	}

    NGPoint   &operator=(NGPoint &src);
	void	GetTargetCenter(int &cx, int &cy)	{	cx=MasterX+MX+HX;	cy=MasterY+MY+HY;	}
	void	GetMasterCenter(int &cx, int &cy)	{	cx=MasterX;	cy=MasterY;	}

	int		GetCauseType(void)	{	return PosResult;	}
};


class   IntegNGImage : public NPList<IntegNGImage>
{
  #pragma	pack(push,1)
	BYTE		**SrcImage[3];
	int32		SrcImageXLen;
	int32		SrcImageYLen;
 
	uchar		*CompressedPtn	;
    int32		PtnByte			;
public:
	int8		ShadowLevel		;
	int8		ShadowNumber	;

	int8		GlobalPage;
	int32		Number;		//ＮＧファイル先頭を０とした通し番号
    int32		x1,y1,x2,y2;//検査画像上のページ内位置
  #pragma	pack(pop)
	QImage		Image;
public:

	IntegNGImage(int ShadowLevel,int ShadowNumber);
	~IntegNGImage(void);

	int		GetNumber(void)	const	{	return Number;				}
	QImage	&GetImage(void)	const	{	return (QImage	&)Image;	}
	void	GetCenter(int &cx ,int &cy)	const	{	cx=(x1+x2)/2;	cy=(y1+y2)/2;	}
	bool	Uncompress(void);
	bool	LoadJDT		(QIODevice *f);
	bool	LoadRawImage(QIODevice *f);
	void	EnumNGPoint(NGPointInPage *PageData ,NPListPack<NGPointPointerList> &NGList);
};

class   NGPointPointerList : public NPList<NGPointPointerList>
{
public:
	NGPoint	*NG;

	NGPointPointerList(NGPoint *p):NG(p){}
};

class	IntegBindedNGArea : public NPList<IntegBindedNGArea>
{
public:
	int	x1,y1,x2,y2;
	NGPointInPage	*Parent;
	NPListPack<NGPointPointerList>	NGPointerList;

	IntegBindedNGArea(NGPointInPage *parent):Parent(parent){}
	void	GetCenter(int &cx ,int &cy)	const	{	cx=(x1+x2)/2;	cy=(y1+y2)/2;	}
};


class   NGPointInPage : public NPList<NGPointInPage> ,public NPListPack<NGPoint>
{
	NGPointInAllPage	*Parent;
  public:
	int32	Page;
	bool	FlagSet;
	QString	ImageFileName;
	NPListPack<IntegNGImage>	NGImages;

    NGPointInPage(NGPointInAllPage *p)			:Parent(p)	{	Page=0;		FlagSet=false;	}
	NGPointInPage(NGPointInAllPage *p,int page)	:Parent(p)	{	Page=page;	FlagSet=false;	}
	NGPointInPage(NGPointInAllPage *p,NGPointInPage &src);

	int		GetNGCount(void)	const;
	NGPoint	*GetFirstNG(void)	const	{	return NPListPack<NGPoint>::GetFirst();		}

    NGPointInPage &operator=(NGPointInPage &src);
	NGPointInAllPage	*GetParent(void)	const	{	return Parent;	}
	int		GetPage(void)					const	{	return Page;	}
	int		GetPhase(void)	const;

	void	BindNGPoint(int XLen ,int YLen ,NPListPack<IntegBindedNGArea> &NGAreaPack);
	bool	UncompressImages(void);
	IntegNGImage	*FindImage(int number)	const;
	void	MakeMasterImage(QImage *Image, int cx, int cy ,double ZoomRate);
  private:

};

class   NGPointInAllPage : public NPList<NGPointInAllPage> ,public NPListPack<NGPointInPage>
{
	NGPointInAllPhase	*Parent;
  public:
	int		Phase;

	//NGPointInAllPage(NGPointInAllPhase *p)			:Parent(p)	{	Phase=0;		}
    NGPointInAllPage(NGPointInAllPhase *p,int phase):Parent(p)	{	Phase=phase;	}

    NGPointInAllPage &operator=(NGPointInAllPage &src);
	NGPointInAllPhase	*GetParent(void)		const	{	return Parent;	}
	NGPointInPage		*GetPageData(int page)	const	{	return NPListPack<NGPointInPage>::GetItem(page);	}
	int		GetPhase(void)						const	{	return Phase;	}

	bool	IsSetAllPages(void)	const;
	int		GetNGCount(void)	const;
};

class   NGPointInAllPhase : public NPListPack<NGPointInAllPage>
{
	InspectionList	*Parent;
  public:
    NGPointInAllPhase(InspectionList *p):Parent(p){}

    NGPointInAllPhase &operator=(NGPointInAllPhase &src);
	InspectionList	*GetParent(void)			const	{	return Parent;	}

	NGPointInAllPage	*GetPhaseData(int page)	const	{		return GetItem(page);	}

	bool	IsSetAllPhases(void)	const;
	int		GetNGCount(void)		const;
};

inline	int		NGPointInPage::GetPhase(void)	const	{	return (Parent!=NULL)?Parent->GetPhase():0;	}
//----------------------------------------------------------------

class	InspectionList : public NPList<InspectionList>
{
	EachMaster	*Master;
public:
	int	ID;
	QString	FileName;
	NGPointInAllPhase	NGPointAllPhases;
	XDateTime			InspectionTime;
	QByteArray			RemarkData;
	BYTE	Result;
	
	InspectionList(EachMaster *p):NGPointAllPhases(this)	{	Master=p;	ID=-1;	}
	EachMaster	*GetMaster(void)	const	{	return Master;		}
	int		GetNGCount(void)	const;
	QString	GetFileName(void)	const;

	NGPointInAllPage	*GetPhaseData(int page)	const	{	return NGPointAllPhases.GetItem(page);	}
};

class	InspectionListPointer : public NPList<InspectionListPointer>
{
public:
	InspectionList	*Pointer;

	InspectionListPointer(InspectionList *p):Pointer(p){}
};


class	LotList : public NPList<LotList>
{
public:
	QString	LotName;
	QString	LotID;
	QString	LotFileName;
	QString	Remark;
	int		GlobalID;
	qint64	LastSeekPoint;

	LotList(void)				{	GlobalID=-1;	LastSeekPoint=0;	}
	LotList(const LotList &src)	{	LotName=src.LotName;	LotID=src.LotID;	LotFileName=src.LotFileName;	GlobalID=src.GlobalID;	LastSeekPoint=0;	}

	LotList &operator=(const LotList &src);
};

class LotListContainer : public NPListPack<LotList>
{
public:
	LotListContainer(){}
	~LotListContainer(){}

	LotListContainer	&operator=(const LotListContainer &src);
	LotListContainer	&operator=(const NPListPack<LotList> &src);

	bool	MergeByFileName(LotList *a);
};


#pragma	pack(push,1)
struct	TotalResultStruct
{
	short	Error;		//1:OK	2-:NG
	int32	InspectionID;
	BYTE	Year;
	BYTE	Month;
	BYTE	Day;
	BYTE	Hour;
	BYTE	Minute;
	BYTE	Second;
	DWORD	Microsec;
	short	LoadedPageCount;
};
#pragma	pack(pop)
#define	MaxCountTotalResultDim	30*3600*24*5


class	InspectionListContainer : public QObject ,public NPListPack<InspectionList>
{
	Q_OBJECT

	EachMaster *Parent;
public:
	int							CountingPoint;
	struct	TotalResultStruct	*ResultDim;
	int							ResultCount;
	int							AllocatedResultCount;
	int32		TotalCount;
	int32		NGCount;

	InspectionListContainer(EachMaster *p);
	~InspectionListContainer(void);

	void	AppendList(InspectionList *n);
	void	SetResultPage(int Phase ,int GlobalPage,InspectionList *n);
	void	RemoveAll(void);

signals:
	void	SignalDoneLoadResult(InspectionList *n);
};

class AccessToPage
{
public:
	int32	GlobalPage;
	QString	IPAddress;
	int32	Port;

	AccessToPage(void){	GlobalPage=0;	Port=0;	}

	AccessToPage	&operator=(const AccessToPage &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	IntegrationSystemResult
{
public:
	QByteArray	Result;
};

class IntegrationSystemResultStocker
{
	IntegrationSystemResult	*Dim;
	int				DimCount;
	int				WPoint;
	int				RPoint;
	int				StockedCount;
	QMutex			AccessMutex;
public:
	IntegrationSystemResultStocker(int AllocCount=100);
	~IntegrationSystemResultStocker(void);

	bool	ReallocateDimCount(int AllocCount);

	void	PushResult(const QByteArray &data);
	IntegrationSystemResult	*PopResult(void);
};

class	EachMaster : public QObject ,public NPList<EachMaster>,public ServiceForLayers
{
	Q_OBJECT

	IntegrationBase	*Parent;
	InspectionList	*Ins;	//For load lot
private:
	IntegrationSlave		*Slave;
	QString	MachineName;
	int32	MasterCode;
	QString	MasterName;
	//int32	LayerNumb;
	int32	PageNumb;
	int32	PhaseNumb;
	int32	ThresholdLevelID;
	DataInPage::ConstructionData	*CData;	//	Index=phase*PageNumb+page
	int32	*LayerNumbDim;
	int32	CurrentPhase;
	NPListPack<LotList>	LotContainer;
	LotList	*CurrentLot;
	double	TransformUnitPerPixelX;
	double	TransformUnitPerPixelY;
	AccessToPage	*AccessToPageDim;

	InspectionListContainer		CurrentInspection;
	ImageBuffer	***MasterImage;
	ImageBuffer	***TargetImage;
	IntegrationSystemResultStocker		SystemResultContainer;

public:
	EachMaster(IntegrationBase *parent ,IntegrationSlave *slave);
	~EachMaster(void);

	ParamIntegrationMaster	*GetParamIntegrationMaster(void)	const;
	int		GetPhaseNumb(void)	const		;
	int		GetPageNumb(void)	const		;
	int		GetLayerNumb(int phase ,int page)	const;
	int		GetMaxLayerNumb(void)	const;
	int		GetDotPerLine(int phase ,int page)	const;
	int		GetMaxLines(int phase ,int page)	const;
	int		GetCurrentPhase(void)	const	{	return CurrentPhase;	}
	void	SetCurrentPhase(int phase)		{	CurrentPhase=phase;		}

	const	InspectionListContainer		&GetCurrentInspection(void)	const	{	return CurrentInspection;	}
	void	ResetCounterCurrentInspection(void)								{	CurrentInspection.NGCount	=0;
																				CurrentInspection.TotalCount=0;		}
	void	RemoveAllCurrentInspection(void)		{	CurrentInspection.RemoveAll();	}

	void	IncCountingPoint(void)		{	CurrentInspection.CountingPoint++;	}
	int		GetLotCount(void)	const	{	return LotContainer.GetCount();	}
	LotList	*GetLotFirst(void)			{	return LotContainer.GetFirst();	}
	void	ClearLotContainer(void)		{	LotContainer.RemoveAll();		}
	IntegrationSlave		*GetSlave(void)	const	{	return Slave;		}

	bool	IsDependent(void)	const;

	bool	ClearMaster(void);
	void	ClearImageBuff(void);
	bool	LoadMaster(int MasterCode);
	bool	LoadLotList(int MasterCode);

	bool	ClearCurrentLot(void);
	bool	LoadLot(LotList *Current);
	bool	AppendSelectLot(LotList *Current);

	int		GetIntegrationSlaveNo(void)	const;
	int		GetMachineCode(void)	const	{	return (Slave!=NULL)?Slave->MachineCode:-1;	}
	QString	GetMachineName(void)	const;
	void	SetMachineName(const QString &s)	{	MachineName=s;	}
	XYData	*GetOutlineOffset(int phase, int page)	const;
	void	ReleaseImageBuffer(void);
	void	AllocateImageBuffer(void);
	bool	ReallocXYPixels(int page,int NewDotPerLine ,int NewMaxLines);
	bool	MoveAll(bool Mastered,bool Targeted,int XDir,int YDir);
	bool	AddPhase(int _AddedPhaseCount);
	bool	RemovePhase(int PhaseCode);

	int32	GetMasterCode(void)		const	{	return MasterCode;	}
	void	SetMasterCode(int n)			{	MasterCode=n;		}
	QString	GetMasterName(void)		const	{	return MasterName;	}
	void	SetMasterName(const QString &s)	{	MasterName=s;		}

	bool	LoadTargetImage(InspectionList *p ,QString &RetImageFileName);
	bool	LoadMasterImage(ImageBuffer ***ImageNuff);
	QString	CreateMasterImageFileName(const QString &ImagePath,int Phase,int Page);
	bool	LoadMasterImageFile(int Phase, int Page ,const QString &ImageFileName ,ImageBuffer *BufferByLayer);
	bool	LoadMasterImageFile(int Phase, int Page ,QIODevice &ImageFile,ImageBuffer *BufferByLayer);
	bool	LoadOutlineOffsetForDatabase(void);

	void	PushResult(const QByteArray &s)	{	SystemResultContainer.PushResult(s);	}

	bool	LoadImage(QString FileName ,ImageBuffer ***Buff);
	bool	LoadNaming(QIODevice &File);
	bool	LoadOutputLibData(QIODevice &File);
	bool	GetXY(int &x1, int &y1 ,int &x2 ,int &y2)	const;
	ImageBuffer	*GetMasterImage(int phase ,int page ,int layer)	const;
	ImageBuffer	*GetTargetImage(int phase ,int page ,int layer)	const;
	bool	GetMasterImage(int phase ,int page ,ImagePointerContainer &ImageList)	const;
	bool	GetTargetImage(int phase ,int page ,ImagePointerContainer &ImageList)	const;

	void	DrawImage(QImage *Img,XYData &c
						,int phase ,int page
						,ImageBuffer *IBuff[]
						,double ZoomRate,int movx ,int movy
						,bool EnableToColorizeFor3Layers=true);

	bool	RequireMasterImage(bool MixMaster);
	bool	RequireMasterImageInPhase(int phase,bool MixMaster);
	bool	RequireSlaveInfo(void);
	bool	RequireAccessToPage(void);
	bool	ReqPhaseNames(QStringList &RetPhaseNames);
	bool	SetPhaseName(int Phase ,const QString PhaseName);

	LotList	*GetCurrentLot(void)	const	{	return CurrentLot;	}
	bool	SetCurrentLot(LotList *Lot);
	bool	AddCurrentLot(LotList *L);

	void	GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	int		GetGlobalPage(int globalX ,int globalY)		const;
	void	GetGlobalPage(int globalX ,int globalY,IntList &PageList)	const;
	void	GetGlobalPage(int globalX1 ,int globalY1 ,int globalX2 ,int globalY2 ,IntList &PageList)	const;
	int		GetLocalPageFromGlobal(int GlobalPage)	const;
	int		GetPageFromArea(FlexArea &Area,IntList &PageList)		const;
	int		GetPageFromVector(VectorLineBase *v,IntList &PageList)	const;
	int		GetLocalMatrixFromGlobal(int globalX ,int globalY ,int &localX ,int &localY)			const;
	void	GetGlobalMatrixFromLocal(int Page ,int localX ,int localY ,int &globalX ,int &globalY)	const;

	double	TransformPixelDistanceToUnit(double PixelX1,double PixelY1 ,double PixelX2,double PixelY2)	const;
	double	TransformUnitDistanceToPixel(double UnitX1 ,double UnitY1  ,double UnitX2 ,double UnitY2)	const;
	double	TransformPixelDistanceToUnit(double PixelXLen,double PixelYLen)	const;
	double	TransformUnitDistanceToPixel(double UnitXLen ,double UnitYLen)	const;

	double	TransformPixelToUnit(double pixel)			const;
	double	TransformUnitToPixel(double unit)			const;
	QString	TransformPixelToUnitStr(double pixel)		const;
	QString	GetUnitStr(void)							const;
	QString	GetUnitStr(double unit)						const;
	double	TransformPixelToUnitSquare(double pixel)	const;
	double	TransformUnitToPixelSquare(double unit)		const;
	QString	TransformPixelToUnitSquareStr(double pixel)	const;
	QString	GetUnitSquareStr(double unit)				const;
	AccessToPage	*GetAccessToPageDim(int page)		const	{	return &AccessToPageDim[page];	}

private:
	bool	LoadLotFile(LotList *Current ,QIODevice &File);

signals:
	void	SignalDoneLoadResult(InspectionList *n);
	
private slots:
	void	SlotDoneLoadResult(InspectionList *n);

};

class	IntegrationCommonData
{
public:
	double	CommonSizeX;
	double	CommonSizeY;
	double	CommonSizeZ;
	QString	RelationNumber;
	QString	RelationName;
	QString	RelationRemark;
	QByteArray	Something;
	double	AddedX;
	double	AddedY;
	double	AddedZ;

	IntegrationCommonData(void);
	IntegrationCommonData(const QByteArray &data);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	
	IntegrationCommonData	&operator=(IntegrationCommonData &src);
};

class	IntegrationBase : public QObject ,public ServiceForLayers
{
	Q_OBJECT

	ParamIntegrationMaster	*ParamIntegrationMasterData;
	//IntegrationCommPack		*CommIndex;
	IntegrationCommonData	CommonData;
	DWORD	LastActionTime;
	int32	ThresholdLevelID;
	bool	ReEntrant;
public:
	int		MasterRelationCode;
	volatile	bool	AvailableIntegrationResource;
	
	NPListPack<EachMaster>	MasterDatas;

	int		CurrentLotGlobalID;
	int32	TotalCount	;
	int32	NGCount		;

	IntegrationBase(LayersBase *base,ParamIntegrationMaster	*p);
	virtual	~IntegrationBase(void);

	bool	Initialize(void);
	//bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	AddPhase(int SlaveNo ,QStringList &AddedPhaseNameList);
	bool	RemovePhase(int SlaveNo ,int PhaseCode);
	bool	SetCurrentPhase(int SlaveNo ,int PhaseCode);

	void	ResetTotalResult(void);


	IntegrationCommonData	*GetCommonData(void)	const	{	return (IntegrationCommonData *)&CommonData;	}
	void	SetCommonData(IntegrationCommonData &src);

	bool	LoadRelationMaster(int RelationCode);
	bool	LoadLotData(void);

	QString	GetLibraryName(int LibType ,int LibID);
	bool	GetInformation(  QString &RetRelationNumber
							,QString &RetRelationName
							,QString &RetRemark
							,int &RetRelationType
							,QByteArray &CommonData
							,int32 &ThresholdLevelID);
	ParamIntegrationMaster	*GetParamIntegrationMaster(void)	const{	return ParamIntegrationMasterData;	}

	int		GetMasterRelationCode(void)	const	{	return	MasterRelationCode;		}
	void	SetMasterRelationCode(int d)		{	MasterRelationCode=d;			}
	bool	UpdateLastLoadedTimeMasterRelation(void);
	
	bool	SelectLot(int GlobalID);
	EachMaster	*GetMaster(int SlaveNo)	const	{	return MasterDatas[SlaveNo];	}
	EachMaster	*FindMaster(int MachineCode)	const;
	int		EnumMaster(int MachineCode ,EachMaster *Pointer[],int MaxCountOfBuffer)	const;
	int		EnumMaster(EachMaster *Pointer[],int MaxCountOfBuffer)	const;

	int		GetIntegrationSlaveNoFromMachineCode(int MachineCode)	const;
	int		GetIntegrationSlaveCount(void)		const	{	return (ParamIntegrationMasterData==NULL)?0:ParamIntegrationMasterData->GetIntegrationSlaveCount();	}

	//void	SetCommIndex(IntegrationCommPack *d)	{	CommIndex=d;		}
	//IntegrationCommPack		*GetCommIndex(void)		{	return CommIndex;	}
	bool	IsConnected(int SlaveNo)	const;
	bool	IsMastered(void)			const;
	void	SlaveConnected(void);
	void	SlaveDisconnected(void);
	bool	CheckOnProcessing(int SlaveNo);
	bool	WaitWhileProcessing(void);
	void	ExecuteInitialAfterEdit(int SlaveNo);
	bool	HasLocalCamera(void);

	void	BroadcastInspectionDone	(int SlaveNo,int64 InspectionID ,bool OK);
	void	BroadcastScanningDone	(int SlaveNo,int64 InspectionID);
	void	UpdateInspection(void);
	bool	NowOnUsing(void);
	QString	ReplaceImageFile(const QString &ImageFileName,int MachineID);

	bool	DeliverRebuildThresholdLevel(void);
	bool	DeliverThresholdLevel(int LevelID);
	bool	DeliverCopyThresholdLevel(int SourceLevelID ,int DestLevelID);
	bool	SetCurrentIntoThresholdLevel(int LevelID);
	int32	GetThresholdLevelID(void)	{	return ThresholdLevelID;	}

	bool	InitialForLocalHost(void);
	bool	IsLocal(int SlaveNo)	const;

	void	SetSystemResult(int phase,int page,const QByteArray &Result);
signals:
	void	SignalSlaveConnected();
	void	SignalAllSlaveConnected();
	void	SignalSlaveDisconnected();
	void	SignalInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	SignalScanningDone	(int SlaveNo,int64 InspectionID);
	void	SignalDoneLoadResult(InspectionList *n);
	void	SignalChangeThresholdLevel(int OldLevelID ,int NewLevelID);
private slots:
	void	SlotDoneLoadResult(InspectionList *n);
};


inline	ParamIntegrationMaster	*EachMaster::GetParamIntegrationMaster(void)	const{	return (Parent!=NULL)?Parent->GetParamIntegrationMaster():NULL;	}

//-------------Message packet---------------------

class	CmdClearMasterData : public SpecifiedBroadcaster
{
public:
	CmdClearMasterData(void){}
};
class	CmdLoadedMasterData : public SpecifiedBroadcaster
{
public:
	CmdLoadedMasterData(void){}
};
class	CmdUpdatedMasterImage : public SpecifiedBroadcaster
{
public:
	CmdUpdatedMasterImage(void){}
};
class	CmdChangeLotID : public SpecifiedBroadcaster
{
public:
	QString	LotID	;
	QString	LotName	;
	CmdChangeLotID(void){}
};
class	CmdChangeNewLotID : public SpecifiedBroadcaster
{
public:
	CmdChangeNewLotID(void){}
};
class	CmdSelectResult : public SpecifiedBroadcaster
{
public:
	int	ResultID;
	CmdSelectResult(void){}
};
class	CmdAppendResult : public SpecifiedBroadcaster
{
public:
	int	ResultID;
	int	SlaveNo;
	CmdAppendResult(void){}
};
class	CmdSelectNGLine : public SpecifiedBroadcaster
{
public:
	IntegNGImage	*NG;
	CmdSelectNGLine(void){}
};

class	CmdExecLoadLot : public GUIDirectMessage
{
public:
	CmdExecLoadLot(LayersBase *base):GUIDirectMessage(base){}
	CmdExecLoadLot(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadedImage : public SpecifiedBroadcaster
{
public:
	InspectionList	*Pointer;

	CmdLoadedImage(void)	{	Pointer=NULL;	}
};

class	CmdShowNGPoint : public SpecifiedBroadcaster
{
public:
	EachMaster		*Master;
	NGPoint			*NG;
	IntegNGImage	*NGImage;
	InspectionList	*Result;

	CmdShowNGPoint(void)	{	Master=NULL;	NG=NULL;	NGImage=NULL;	Result=NULL;	}
};
class	CmdClearCounter : public SpecifiedBroadcaster
{
public:
	CmdClearCounter(void){}
};
class	CmdReqNGPositionInPanel : public GUIDirectMessage
{
public:
	EachMaster		*Master;
	NGPoint			*NG;
	int				WorldX1,WorldY1,WorldX2,WorldY2;
	bool			Found;

	CmdReqNGPositionInPanel(LayersBase *base):GUIDirectMessage(base){	Master=NULL;	NG=NULL;	}
	CmdReqNGPositionInPanel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Master=NULL;	NG=NULL;}

};

class	CmdReqUpdateHistory : public SpecifiedBroadcaster
{
public:
	int	SlaveNo;
	CmdReqUpdateHistory(void){	SlaveNo=-1;	}
};
class	CmdReqUpdateResult : public SpecifiedBroadcaster
{
public:
	CmdReqUpdateResult(void){}
};

class	CmdReqUpdateCurrentInspection : public SpecifiedBroadcaster
{
public:
	int	SlaveNo;
	CmdReqUpdateCurrentInspection(void){	SlaveNo=-1;	}
};



#endif
