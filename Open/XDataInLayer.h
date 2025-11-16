/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDataInLayer.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XDataInLayerH
#define XDataInLayerH
//---------------------------------------------------------------------------
#include "XTypeDef.h"
#include <QIODevice>
#include <QMouseEvent>
#include <QFileDialog>
//#include <QTextCodec>
#include <QMutex>
#include <QStringList>
#include "NList.h"
#include "XErrorCode.h"
#include "XFlexArea.h"
#include "XDateTime.h"
#include "XBoolList.h"
#include "XMainSchemeMemory.h"
#include "XParamGlobal.h"
#include "XGUIPacketForDLL.h"
#include "XLearningInPage.h"
#include "XUndo.h"
#include "XRegulation.h"
#include "XDirectCommPacket.h"
#include <typeinfo>
#include <QReadWriteLock>
#include "XAuthentication.h"
#include "XAlgorithmCommon.h"
#include "XShadowTree.h"
#include "XGUILanguage.h"
#include "XControlPoints.h"
#include "XServiceForLayers.h"
#include <memory>

class	QTcpSocket;
class	QTextCodec;

class	AlgorithmDLLContainer;
class	LayersBase;
class	PageDataInOnePhase;
class	MaskData;
class	AlgorithmBase;
class	AlignmentInLayerRoot;
class	AlgorithmInPageRoot;
class	AlgorithmInPageInOnePhase;
class	DataInPage;
class	EntryPointBase;
class	LogicDLLBaseClass;
class	ResultDLLBaseClass;
class	ResultInspection;
class	XUpdateDatabase;
class	ExcludedListPack;
class	ReceiverList;
class	GUIDirectMessage;
class	LogicDLL;
class	AlgorithmItemRoot;
class	AlgorithmLibraryContainer;
class	AlgorithmItemIndependentPack;
class	ClipboardList;
class	ThreadSequence;
class	MixTransferComm;
class	QSqlDatabase;
class	DatabaseLoader;
class	GUIFormBase;
class	PieceClass;
class	PieceStocker;
class	OnProcessingForm;
class	DirectComm;
class	LightClass;
class	LightAccessList;
class	LightClassPack;
class	ParamGUI;
class	FilterBankBase;
class	FileRegistry;
class	OutlineOffsetInBlob;
class	LogoStocker;
class	AnyDataContainer;
class	RootNameListContainer;
class	DirectCommReceiverList;
class	DirectCommPacketBase;
class	VectorLineBase;
class	GeneralStockerContainer;
class	ErrorCodeList;
class	CmdWritternResult;
class	LearningRegListContainer;
class	PasswordManager;
class	SystemConnectionInfoContainer;
class	SyncGUIPack;
class	FilterInstanceContainer;
class	StatusController;
class	LearningRegister;
class	AlignmentPacketBase;
class	GUIInitializer;
class	GUIInstancePack;
class	ShowLoadingDLLForm;
class	LotInformation;
class	LotBase;
class	AlgorithmBasePointerContainer;
class	ShareMasterDestination;
class	ShareMasterContainer;
class	QStringListListCSV;
class	SpecifiedBroadcaster;
class	PrinterClassPack;
class	ShrinkingPackContainer;
class	LensWindowForm;
class	DisplayImage;
class	ZoneWindowForEdit;
class	IntegrationBase;
class	IntegrationCmdPacketBase;
class	WidgetGeometry;
class	ResultAnalizerDLLContainer;
class	ResultAnalizerItemBaseContainer;
class	GUICmdPacketBasePointerListContainer;
class	DirectCmdPacketBaseContainer		;
class	IntegrationCmdPacketBasePointerListContainer	;
class	AuthenticationInside				;
class	SeqControl							;
struct	ReceivedResultCountsParam			;
class	WriteResultThread					;
class	LibTypeListContainer				;
class	ResultHistryContainer				;
class	ArrangementDLLBase					;
class	LogOutClass							;
class	ListOfQImageStocker					;
class	ParamDatabase						;
class	LanguagePackage						;
class	OperationLogger						;
class	RelationMasterList					;
class	ResultInspectionPointerStock		;
class	ConstMapBufferListContainer			;
class	FileThreadListContainer				;
class	LevelFolder							;
class	LevelFolderContainer				;
class	IntegrationCommPack					;
class	ComponentListContainer				;
class	ExecuteInitialAfterEditInfo			;
class	MultiLayerColor						;
class	LoadedInfoContainerInPhase			;
class	TransformBase						;
class	AlgorithmThreshold					;
class	AlgorithmItemIndex					;
class	LearningInDBThreshold				;
class	AlgorithmLibrary					;

//========================================================================================

#define	ResultCmdSaveSlaveCommand		1
#define	ResultCmdLotChangedSlaveCommand	2
#define	ReportErrorFromSlaveCommand		3
#define	ShowCriticalErrorCommand		4
#define	BroadcastShowInPlayerCommand	5

class	ClipboardAlgorithmItem : public NPList<ClipboardAlgorithmItem>
{
public:
	FlexArea		Area;
	VectorLineBase	*Vector;
	int32			ItemClassType;
	QByteArray		ItemData;
	int32			Page;
	int32			Layer;

	ClipboardAlgorithmItem(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Draw(int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col);
	ClipboardAlgorithmItem	&operator=(const ClipboardAlgorithmItem &src);
};

class	ClipboardAlgorithm : public NPList<ClipboardAlgorithm>
{
	XDateTime		CreatedTime;
public:
	LayersBase		*LBase;
	AlgorithmBase	*Base;
	NPListPack<ClipboardAlgorithmItem>	Items;
	QString			Remark;

	explicit	ClipboardAlgorithm(const XDateTime &_CreatedTime ,LayersBase *lbase)
								:CreatedTime(_CreatedTime),LBase(lbase){	Base=NULL;	}
	explicit	ClipboardAlgorithm(LayersBase *lbase){	LBase=lbase;	Base=NULL;	}

	bool	Save(int localPage,QIODevice *f);
	bool	Load(int localPage,QIODevice *f);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Draw(int localPage ,int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col);
	ClipboardAlgorithm	&operator=(ClipboardAlgorithm &src);
	void	CopyInPages(ClipboardAlgorithm &src ,IntList &LocalPages);
	XDateTime		&GetCreatedTime(void){	return CreatedTime;	}

	void	Absorb(ClipboardAlgorithm *From);
};

class	ClipboardList : public NPListPack<ClipboardAlgorithm>
{
public:
	ClipboardList(void){};
	~ClipboardList(void);

	void	AppendList(ClipboardAlgorithm *item ,bool EnableDup);
	ClipboardAlgorithm	*Find(XDateTime &CreatedTime);
};

class	PageAndLayerList : public NPList<PageAndLayerList>
{
public:
	int32	Page;
	int32	Layer;

	PageAndLayerList(void);
	PageAndLayerList	&operator=(PageAndLayerList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	PageAndLayerFlagList : public NPList<PageAndLayerFlagList>
{
public:
	int32	Page;
	int32	Layer;
	bool	Done;

	PageAndLayerFlagList(void);
	PageAndLayerFlagList(int page ,int layer);
	PageAndLayerFlagList	&operator=(PageAndLayerFlagList &src);
	PageAndLayerFlagList	&operator+=(PageAndLayerFlagList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PageAndLayerFlagListContainer : public NPListPack<PageAndLayerFlagList>
{
public:
	PageAndLayerFlagListContainer(void){}

	PageAndLayerFlagListContainer	&operator+=(PageAndLayerFlagListContainer &src);
};

class	ErrorInfoList : public NPList<ErrorInfoList>
{
public:
	int			Page;
	QStringList	Messages;
	bool		ReqReboot;

	ErrorInfoList(void){	Page=-1;	ReqReboot=false;	}
};

class	PasteListMatrix : public NPList<PasteListMatrix>
{
public:
	int32		GlobalPage;
	BoolList	Layers;
	int			XPos;
	int			YPos;

	PasteListMatrix(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	PasteListMatrix	&operator=(PasteListMatrix &src);
};

class	PasteListMatrixContainer : public NPListPack<PasteListMatrix>
{
public:
	PasteListMatrixContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Save(QStringListListCSV &csv);
	bool	Load(QStringListListCSV &csv);
	PasteListMatrixContainer	&operator=(PasteListMatrixContainer &src);
};

//========================================================================================
class	NGImageContainerInPage;

class	NGImageContainerInPagePointerList : public NPList<NGImageContainerInPagePointerList>
{
	NGImageContainerInPage *Point;
public:
	explicit	NGImageContainerInPagePointerList(NGImageContainerInPage *p);

	NGImageContainerInPagePointerList	&operator=(const NGImageContainerInPagePointerList &src);
	NGImageContainerInPage *GetPoint(void);
};



class	ThreadImageCompresserInPage : public QThread,public ServiceForLayers
{
	NPListPack<NGImageContainerInPagePointerList>	NGImageContainerInPageContainer;
	QMutex											Accessor;
	DataInPage		*ParentPage;
public:
	bool	CloseMode;
	ThreadImageCompresserInPage(LayersBase *base,DataInPage *p);
	~ThreadImageCompresserInPage(void);

	void	Set(NGImageContainerInPage *point);
	bool	IsDone(void);
	int		GetCountOfCompressing(void);
protected:
	void run();

};

//========================================================================================

class	SystemResult
{
public:
	int			MasterCode;
	int			LotAutoCount;
	DWORD		StoredTime;
	QByteArray	Result;
};

class SystemResultStocker : public ServiceForLayers
{
	SystemResult	*Dim;
	int				DimCount;
	int				WPoint;
	int				RPoint;
	int				StockedCount;
	QMutex			AccessMutex;
public:
	SystemResultStocker(LayersBase *base ,int AllocCount=100);
	~SystemResultStocker(void);

	void	ReallocateDimCount(int AllocCount);

	void	ClearSystemResult(void);
	void	PushResult(const QByteArray &data);
	SystemResult	*PopResult(void);
	SystemResult	*GetLastResult(void);
	int		GetStockedSystemResult(void);
};

//========================================================================================

struct	PropertyGeneralStocker
{
	bool			SynchronizeToSlave;		//Default:false
	bool			SaveInMasterData;		//Default:false

	PropertyGeneralStocker(void)	{	SynchronizeToSlave=false;	SaveInMasterData=false;	}
};

//========================================================================================

class	AlgorithmBasePointerList : public NPList<AlgorithmBasePointerList>
{
	AlgorithmBase	*Base;
public:
	explicit	AlgorithmBasePointerList(AlgorithmBase *base):Base(base){}

	AlgorithmBasePointerList	&operator=(const AlgorithmBasePointerList &src)
												{	Base=src.Base;	return *this;	}
	AlgorithmBase	*GetAlgorithmBase(void)		{	return Base;	}
};

class	AlgorithmBasePointerContainer : public NPListPack<AlgorithmBasePointerList>
{
public:
	AlgorithmBasePointerContainer(void){}
	void	Add(AlgorithmBase *a);
	void	Merge(AlgorithmBase *p);
	AlgorithmBase	*FindAlgorithmBase(int LibType);
};

class	BufferInfoList
{
public:
	QString		BufferName;
	int			OriginCode;	//-1:通常バッファ	0-:他で作成された

	BufferInfoList(void);
	BufferInfoList(const BufferInfoList &src);

	BufferInfoList &operator=(const BufferInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DataInLayer : public QObject ,public IdentifiedClass
{
	Q_OBJECT

	DataInPage			*ParentPage;
	ImageBuffer     	*TargetBuffDim[2];
	int					TargetWPoint;
	int					TargetRPoint;
	int					StoringTargetCounter;
	AnyDataContainer	*AnyData;
protected:
		//These are allocated in Slave or 1CPU
	bool			Exchanged;
	int32			AllocatedCountMasterBuff;
	int32			AllocatedCountBackGroundBuff;
	ImageBuffer     **MasterBuff;
	ImageBuffer		**BackGroundBuff;
	ImageBuffer     *TargetTRBuff;		//転置画像（Y-Y交換)
	ImageBuffer     *RawTargetBuff;		//After filtering, before PreAlignment
	ImageBuffer     *TempTargetBuff;
	//ImageBuffer		*ViewTargetBuff;
	ImageBuffer		*CamTargetBuff;		//Just after capturing by camera
	ImageBuffer		*BitBuff;
	ImageBuffer     *TrialTargetBuff;
public:
	int32				Layer;
	QMutex			AccessTarget;
	QMutex			AccessMaster;
	bool			EnableCapture;

	class	ConstructionData
	{
	public:
		int32				ResNumb;
		BYTE				*RBrightTable;
		BYTE				*GBrightTable;
		BYTE				*BBrightTable;
		bool				UseTable;

		explicit	ConstructionData(DataInLayer *parent);
		ConstructionData(const ConstructionData &src);
		~ConstructionData(void);

		ConstructionData	&operator=(const ConstructionData &src);
		bool    SaveBrightTable(QIODevice *f);
		bool    LoadBrightTable(QIODevice *f);

	};
	ConstructionData	CData;

	explicit	DataInLayer(DataInPage *parent);
	virtual	~DataInLayer(void);

	void	Initial(bool EnabledImageMemoryAllocation=true);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	void	ReallocMemoryMaster(void);
	void	ReallocMemoryTarget(void);
	void	ReallocMemoryBackGround(void);
	void	ReallocUseBufferToTarget(BYTE **Buff);
	bool	ReallocateMasterCount(int CountMaster);
	bool	ReallocateBackGroundCount(int CountMaster);

	void	AllocateTargetTRBuff(void);
	void	ReleaseTargetTRBuff(void);

	XYData	*GetOutlineOffset(void)						const;
	void	GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	AnyDataContainer	*GetAnyData(void)	const	{	return AnyData;	}
	void		SetEnableCapture(bool b=true);
	bool		GetEnableCapture(void)	const;

	DataInPage	*GetParent(void)		const	{	return ParentPage;	}
	LayersBase	*GetLayersBase(void)	const;
	ParamGlobal	*GetParamGlobal(void)	const;
	ParamComm	*GetParamComm(void)		const;
	int			GetLayer(void)			const;
	int			GetPage(void)			const;
	int			GetPhase(void)			const;

	bool    SaveAttr(QIODevice *f);
	bool    LoadAttr(QIODevice *f);
	bool    SaveBrightTable(QIODevice *f);
	bool    LoadBrightTable(QIODevice *f);
	bool    Save(QIODevice *f);
	bool    Load(QIODevice *f);
	bool	SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2);
	bool	LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2);
	virtual	void	CopyImage(int sourceImageType ,int destImageType);
	bool	CopyFrom(QImage &SrcImg ,bool ToMaster);

	int		GetCountAllMasterBuff(void)		const;
	int		GetCountOnlyMasterBuff(void)	const;
	int		GetCountDispatchMasterBuff(void)const;
	int		GetCountAllBackGroundBuff(void)		const;
	int		GetCountOnlyBackGroundBuff(void)	const;
	int		GetLayerNumb(void)			const;
	int		GetPageNumb(void)			const;
	int		GetPhaseNumb(void)			const;
	int		GetDotPerLine(void)			const;
	int		GetMaxLines(void)			const;

	void	StoringStartTargetBuff(void);
	void	StoringFinishTargetBuff(void);
	int		GetStoringTargetCounter(void)	const	{	return StoringTargetCounter;	}

	ImageBuffer	&GetMasterBuff(void)			const;
	ImageBuffer	&GetMasterBuff(int n)			const;
	ImageBuffer	&GetBackGroundBuff(void)		const;
	ImageBuffer	&GetBackGroundBuff(int n)		const;
	ImageBuffer	&GetTargetBuff(void)			const;
	ImageBuffer	&GetTargetTRBuff(void)			const;
	ImageBuffer	&GetRawTargetBuff(void)			const;
	ImageBuffer	&GetDelayedViewBuff(void)		const;
	ImageBuffer	&GetLastDelayedViewBuff(void)	const;
	ImageBuffer	&GetCamTargetBuff(void)			const;
	ImageBuffer	&GetBitBuff(void)				const;
	ImageBuffer	&GetTrialTargetBuff(void)		const;

	ImageBuffer	*GetMasterBuffPointer(void)			const;
	ImageBuffer	*GetMasterBuffPointer(int n)		const;
	ImageBuffer	*GetBackGroundBuffPointer(void)		const;
	ImageBuffer	*GetBackGroundBuffPointer(int n)	const;
	ImageBuffer	*GetTargetBuffPointer(void)			const;
	ImageBuffer	*GetTargetTRBuffPointer(void)		const;
	ImageBuffer	*GetRawTargetBuffPointer(void)		const;
	ImageBuffer	*GetDelayedViewBuffPointer(void)	const;
	ImageBuffer	*GetLastDelayedViewBuffPointer(void)const;
	ImageBuffer	*GetCamTargetBuffPointer(void)		const;
	ImageBuffer	*GetBitBuffPointer(void)			const;
	ImageBuffer	*GetTrialTargetBuffPointer(void)	const;

	ImageBuffer	*GetDispatchMasterBuffPointer(int n)			const;
	ImageBuffer	*FindDispatchMasterBuffPointer(int OriginCode)	const;

	void	SetToMasterBuff(ImageBuffer &Img);
	void	SetToMasterBuff(int n,ImageBuffer &Img);
	void	SetToBackGroundBuff(ImageBuffer &Img);
	void	SetToBackGroundBuff(int n,ImageBuffer &Img);
	void	SetToTargetBuff(ImageBuffer &Img);

	bool	IsMasterBuffEnabled(void)		const;
	bool	IsMasterBuffEnabled(int n)		const;
	bool	IsBackGroundBuffEnabled(void)	const;
	bool	IsBackGroundBuffEnabled(int n)	const;
	bool	IsTargetBuffEnabled(void)		const;
	bool	IsTargetTRBuffEnabled(void)		const;
	bool	IsRawTargetBuffEnabled(void)	const;
	bool	IsDelayedViewBuffEnabled(void)	const;
	bool	IsCamTargetBuffEnabled(void)	const;
	bool	IsBitBuffEnabled(void)			const;
	bool	IsTrialTargetBuffEnabled(void)	const;
	bool	HasDataInBitBuff(void);

	void	SwitchImageBuff(void)	{	Exchanged=!Exchanged;	}
	void	SwapImageOutOfBuffer(int ImageDataType);
	void	SwapImageInToBuffer(int ImageDataType);
	void	Mirror(bool XMode ,bool YMode);
	void	CreateAndCopyTempTargetBuff(void);
	void	ReleaseTempTargetBuff(void);
	void	CopyTempToTargetBuff(void);
	void	UndoPasteRect(QIODevice *f);
	void	UndoMoveImage(QIODevice *f);
	void	UndoRotateImage(QIODevice *f);
	void	UndoMirrorImage(QIODevice *f);

	bool	IsEdited(void)			const;
	bool	IsCalcDone(void)		const;
	void	SetEdited(bool edited);
	void	SetCalcDone(bool calcdone);
	void	CopyTargetImageToRaw(void);
	void	CopyTargetToTransposition(void);
	void	CopyTargetToCameraBuff(void);
	void	CopyBitBuffToTransposition(void);
	void	RestoreTargetImageFromRaw(void);
	void	CopyToDelayedView(void);
	void	CopyTargetToTrial(void);

	int		SetDispatchMaster(const QString &MasterBuffName, int OriginCode
							,ImageBuffer *s,int pos=-1);	//Return allocated position
	bool	RemoveDispatchMaster(int pos);

private:
	QString	GetFileNameToSwapBuffer(void);
signals:
	void	SignalChangedMasterImage(int LayerNo);
private slots:
	void	SlotChangedMasterImage();
};

class   DataInPage : public QObject,public LearningInPage,public IdentifiedClass
{
	Q_OBJECT

	friend	class   LayersBase;
	friend	class	PageDataInOnePhase;
protected:
	DataInLayer			**LayerData;
	int32				AllocatedLayerNumb;
	LayersBase			*Parent;
	PageDataInOnePhase	*ParentPhase;
	QReadWriteLock		MutexNGCounter;
	int					NGCounter;
	int					OKCounter;
	BYTE				**UncoveredMap;
	int					UncoveredXByte;
	int					UncoveredYLen;
	QMutex				CommTxLock;
	QMutex				CommRxLock;
	LoadedInfoContainerInPhase	*ResultLoaded;

	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;
	SystemResultStocker	SystemResultContainer;
	AnyDataContainer		*AnyData;
public:
	XYPointContainerWithName	ControlPointsForPages;	//Page間でコピーするときのAffin制御点
	XYPointContainerWithName	DymmyPointsForPages;	//Page間でコピーするときのAffin制御点
public:
	int32				Page;
//	SmallPartsPack		SmallParts;
	bool				IsWaitingReq;
	bool				EnableCapture;

	class	ConstructionData
	{
	public:
	    XYData              OutlineOffset;	//輪郭をあわせる時のオフセット
		int32				DotPerLine	;
		int32				MaxLines	;

		explicit	ConstructionData(DataInPage *Parent);
		ConstructionData(void);
		~ConstructionData(void);

		bool    Save(QIODevice *f);
		bool    Load(QIODevice *f);
		ConstructionData	&operator=(const ConstructionData &src){
			OutlineOffset=src.OutlineOffset;
			DotPerLine	=src.DotPerLine;
			MaxLines	=src.MaxLines;
			return *this;
		}
		int32	GetDotPerLine(void)	const	{	return DotPerLine	;	}
		int32	GetMaxLines(void)	const	{	return MaxLines	;		}
	};
	ConstructionData	CData;
private:
	ConstructionData	CDataBack;
	ThreadImageCompresserInPage	ThreadImageCompresser;
	XYRegPointContainer	XYRegulation;
public:
    explicit	DataInPage(int Page ,PageDataInOnePhase	*parentPhase);
    virtual	~DataInPage(void);

    void    Initial(bool EnabledImageMemoryAllocation=true);
    void    Release(void);

	void	SetCData(void);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newLayerNumb);
	bool	ReallocateMasterCount(int CountMaster);
	void	ReallocMemoryMaster(void);
	bool	ReallocateBackGroundCount(int CountMaster);
	void	ReallocMemoryBackGround(void);
	void	ReallocMemoryTarget(void);

	void	AllocateTargetTRBuff(void);
	void	ReleaseTargetTRBuff(void);

	DataInLayer	*GetLayerData(int layer)	const	{	return (0<=layer && layer<AllocatedLayerNumb)?LayerData[layer]:NULL;	}
	int			GetPage(void)				const	{	return(Page);	}
	int			GetPhaseCode(void)			const;
	PageDataInOnePhase	*GetParentPhase(void)	const;
	AnyDataContainer	*GetAnyData(void)	const	{	return AnyData;	}
	void		SetEnableCapture(bool b=true);
	bool		GetEnableCapture(void)	const;

	XYData	*GetOutlineOffset(void)		;
	XYData	*GetGlobalOutlineOffset(void)	const;
	void	SetGlobalOutlineOffset(int X ,int Y);
	XYData	*GetOutlineOffsetLoaded(void)	const	{	return (XYData	*)&CData.OutlineOffset;	}
	void	GetLocalMatrixFromGlobalInMaster(int globalX ,int globalY ,int &localX ,int &localY);
	void	GetGlobalMatrixFromLocalInMaster(int localX ,int localY ,int &globalX ,int &globalY);

	bool	HasRealTransform(int localX ,int localY)	const;
	virtual	void	Draw(QImage &img, int movx ,int movy ,double ZoomRate);

	LayersBase			*GetLayersBase(void)	const{	return Parent;		}
	ParamGlobal			*GetParamGlobal(void)	const;
	ParamComm			*GetParamComm(void)		const;
	int		GetCountAllMasterBuff(void)			const;
	int		GetCountOnlyMasterBuff(void)		const;
	int		GetCountDispatchMasterBuff(void)	const;
	int		GetCountAllBackGroundBuff(void)		const;
	int		GetCountOnlyBackGroundBuff(void)	const;
	int		GetLayerNumb(void)		const;
	int		GetPageNumb(void)		const;
	int		GetPhaseNumb(void)		const;
	int		GetDotPerLine(void)		const;
	int		GetMaxLines(void)		const;
	void	SetDotPerLine(int d);
	void	SetMaxLines(int d)	;
	void	ResetSize(void)		;

	void	LockTarget(void);
	void	UnlockTarget(void);
	void	LockMaster(void);
	void	UnlockMaster(void);

	void	GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)		const;
	bool	ClipAreaGlobal(FlexArea &LocalArea);
	bool	ClipAreaLocal(FlexArea &LocalArea);
	bool	ClipMoveAreaFromGlobal(FlexArea &GlobalArea);
	bool	IsInclude(int localX ,int localY)				const;
	bool	IsIncludeFromGlobal(int GlobalX ,int GlobalY);
	bool	IsOverlapped(FlexArea &globalArea)				const;
	bool	ClipMoveVectorFromGlobal(VectorLineBase *GlobalVector);
	bool	ClipVectorLocal(VectorLineBase *LocalVector);
	bool	IsOverlapped(VectorLineBase *Vector)			const;

	bool    SaveAttr(QIODevice *f);
	bool    LoadAttr(QIODevice *f);
	bool    SaveBrightTable(QIODevice *f);
	bool    LoadBrightTable(QIODevice *f);
	bool    Save(QIODevice *f);
	bool    Load(QIODevice *f);
	bool	SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2);
	bool	LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2);
	void	CopyImage(int sourceImageType ,int destImageType);

	bool    SaveControlPointsForPages(QIODevice *f);
	bool    LoadControlPointsForPages(QIODevice *f);
	virtual	const	XYPointContainerWithName	&GetControlPointsForPages(void);

	//Following is implimented in XMasterData.cpp
	bool	SQLSavePage(int32 masterCode, int32 machineID , QString &ErrorMsg ,const QString &ImagePath ,bool ForceSave);
	bool	SQLLoadPage(int32 masterCode, int32 machineID ,bool ModeLoadMasterImage ,QString &ErrorMsg ,LoadedInfoContainerInPhase &LInfo);
	bool	SQLUpdateAlgorithmOnly(AlgorithmInPageRoot *AlgoPage);
	bool	CopyFrom(QImage &SrcImg ,bool ToMaster);
	bool	CopyFrom(ImageBuffer *DestBuff[],QImage &SrcImg);
	bool	CopyTo(QImage &DstImg ,bool ToMaster);

	void	IncrementNGCounterWithMutex(int result);
	void	AddNGCounter(int NGCount);
	int		GetNGCounter(void);
	int		GetOKCounter(void);
	void	ClearNGCounterWithMutex(void);

	void	SwitchImageBuff(void);
	void	GetMasterImages		(ImagePointerContainer &Images)			const;
	void	GetMasterImages		(int n ,ImagePointerContainer &Images)	const;
	void	GetTargetImages		(ImagePointerContainer &Images)			const;
	void	GetTargetTRImages	(ImagePointerContainer &Images)			const;
	void	GetDelayedViewImages(ImagePointerContainer &Images)			const;
	void	GetLastDelayedViewImages(ImagePointerContainer &Images)		const;
	void	GetBitImages		(ImagePointerContainer &Images)			const;
	void	GetRawTargetImages	(ImagePointerContainer &Images)			const;
	void	GetCamTargetImages	(ImagePointerContainer &Images)			const;
	void	GetTrialTargetImages(ImagePointerContainer &Images)			const;

	int		GetMasterImages		(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetMasterImages		(int n,ImageBuffer *Images[],int MaxCountOfBuff)const;
	int		GetTargetImages		(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetTargetTRImages	(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetDelayedViewImages(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetLastDelayedViewImages(ImageBuffer *Images[],int MaxCountOfBuff)	const;
	int		GetBitImages		(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetRawTargetImages	(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetCamTargetImages	(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	int		GetTrialTargetImages(ImageBuffer *Images[],int MaxCountOfBuff)		const;
	void	CopyToDelayedView(void);

	bool	IsEdited(void)				const;
	bool	IsCalcDone(void)			const;
	void	SetEdited(bool edited);
	void	SetCalcDone(bool calcdone);
	void	CopyTargetImageToRaw(void);

	int		GetStoringTargetCounter(void)	const;

	void	SetCompressedContainer(NGImageContainerInPage *point);
	bool	IsDoneCompressed(void)		{	return ThreadImageCompresser.IsDone();	}
	int		GetCountOfCompressing(void);

	void	MakeUncoveredMap(void);
	const	BYTE	**GetUncoveredMap(int &XByte ,int &YLen);

	QString	CreateMasterImageFileName(int32 masterCode,int _MachineID,const QString &ImagePath
									,int ShadowLevel ,int ShadowNumber);
	QString	GetImageFile(int32 masterCode, int machineID);
	QString	CreateLogicFileName(int32 masterCode ,LogicDLL *abase,int _MachineID,const QString &ImagePath
								,int ShadowLevel ,int ShadowNumber);

	void	UndoCopyImageInPhases	(QIODevice *f);
	void	UndoPourImage			(QIODevice *f);
	void	UndoReplaceColorImage	(QIODevice *f);

	void	LockTxComm(void);
	void	UnlockTxComm(void);
	void	LockRxComm(void);
	void	UnlockRxComm(void);

	void	ClearSystemResult(void);
	void	ReallocateSystemResult(int AllocCount);
	void	PushSystemResult(const QByteArray &data);
	SystemResult	*PopSystemResult(void);
	SystemResult	*GetLastSystemResult(void);
	int		GetStockedSystemResult(void);

	void	DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
					,bool Mastered
					,const QColor &LColor
					,int OffsetX ,int OffsetY);

	void	SetResultLoaded(LoadedInfoContainerInPhase &res);
	LoadedInfoContainerInPhase	&GetResultLoaded(void)		;
	void	ClearResultLoaded(void)							;

	void	SwapImageOutOfBuffer(int ImageDataType);
	void	SwapImageInToBuffer(int ImageDataType);

	bool	AllocateDynamicMasking(void);
	BYTE	**GetDynamicMaskingMap(void)	const	{	return DynamicMaskMap;			}
	int		GetDynamicMaskMapXByte(void)	const	{	return DynamicMaskMapXByte;		}
	int		GetDynamicMaskMapYLen(void)		const	{	return DynamicMaskMapYLen;		}
	void	ClearDynamicMaskMap(void);

	XYRegPointContainer	&GetRegulation(void);
	void	SetRegulation(XYRegPointContainer &s);
	bool	HasRegulation(void);
	void	ClearRegulation(void);
	bool	TransformImageToReal(int imagex ,int imagey ,double &realX ,double &realY)	const	{	return XYRegulation.TransformImageToReal(imagex ,imagey ,realX ,realY);	}
	bool	TransformRealToImage(double realX ,double realY ,int &imagex ,int &imagey)	const	{	return XYRegulation.TransformRealToImage(realX ,realY ,imagex ,imagey);	}
	void	CopyTargetToTransposition(void);
	void	CopyTargetToCameraBuff(void);
	void	CopyBitBuffToTransposition(void);
	void	CopyTargetToTrial(void);

	void	GetMasterPixel(MultiLayerColor &R ,int X,int Y)	const;
	void	SetMasterPixel(MultiLayerColor &R ,int X,int Y);
	void	GetTargetPixel(MultiLayerColor &R ,int X,int Y)	const;
	void	SetTargetPixel(MultiLayerColor &R ,int X,int Y);

	int	SetDispatchMaster(const QString &MasterBuffName, int OriginCode
						,ImageBufferListContainer &s,int pos=-1);	//Return allocated position
	void	RemoveDispatchMaster(int pos);

	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything);

public:
	bool	LoadLogicFile(const QString &LogicFileName
						, AlgorithmBase	*base
						, AlgorithmInPageInOnePhase *pbase
						, AlgorithmInPageRoot *ap
						, int DataVersion);
	bool	SaveLogicFile(const QString &LogicFileName
						, AlgorithmBase	*base
						, AlgorithmInPageInOnePhase *pbase
						, AlgorithmInPageRoot *ap);
	QString	GetLogicFileName(int masterCode ,LogicDLL *p ,int machineID ,QString ImagePath);

public:
	bool	LoadMasterImageFile(const QString &ImageFileName);
	bool	SaveMasterImageFile(const QString &ImageFileName  ,bool ForceSave);

private:
	void    ReleaseInside(void);
	bool	LoadMasterImageFile(QIODevice &ImageFile);
	bool	SaveMasterImageFile(QIODevice &ImageFile ,bool ForceSave);

signals:
	void	SignalChangedMasterImage(int PageNo ,int LayerNo);
private slots:
	void	SlotChangedMasterImage(int LayerNo);
};

class	PageDataInOnePhase: public QObject,public IdentifiedClass
{
	Q_OBJECT

	friend	class   DataInPage;

	int						MasterCode;		//異なるマスターデータから構成されるときのコード
	DataInPage				**PageData;
	int32					AllocatedPageNumb;
	FilterInstanceContainer	**FilterContainer;
	int32					PhaseCode;
	LayersBase				*Parent;
	int32					FromSourcePhase;
	int32					LotAutoCount;
	AnyDataContainer		*AnyData;
public:
	PageDataInOnePhase(int phaseCode ,LayersBase *parent);
	virtual	~PageDataInOnePhase(void);

	void	InitialCreate(LayersBase *Base ,bool EnabledImageMemoryAllocation=true);
	void	Release(void);

	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	ReallocXYPixelsPage(int Page ,int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPageNumb);
	bool	ReallocateMasterCount(int CountMaster);
	bool	ReallocateBackGroundCount(int CountBackGround);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
	void	ResetSize(void);

	void	RemoveDispatchMaster(int pos);

	bool    SaveBrightTable(QIODevice *f);
	bool    LoadBrightTable(QIODevice *f);
	bool    SaveAttr(QIODevice *f);
	bool    LoadAttr(QIODevice *f);

	int		GetCountAllMasterBuff(void)		const;
	int		GetCountOnlyMasterBuff(void)	const;
	int		GetCountDispatchMasterBuff(void)const;
	int		GetCountAllBackGroundBuff(void)		const;
	int		GetCountOnlyBackGroundBuff(void)	const;
	int		GetPageNumb(void)	{	return AllocatedPageNumb;	}

	DataInPage *GetPageData(int page)		const	{	return (0<=page && page<AllocatedPageNumb)?PageData[page]:NULL;	}
	int32	GetAllocatedPageNumb(void)		const	{	return AllocatedPageNumb;		}
	void	SetAllocatedPageNumb(int32 Numb)		{	AllocatedPageNumb=Numb;			}
	LayersBase	*GetLayersBase(void)		const	{	return Parent;					}

	void		SetPhaseCode(int phasecode)			{	PhaseCode=phasecode;			}
	int			GetMasterCode(void)			const	{	return MasterCode;				}
	void		SetFromSourcePhase(int src)			{	FromSourcePhase=src;			}
	int			GetFromSourcePhase(void)	const	{	return FromSourcePhase;			}

	DataInPage **GetPageData(void)			const	{	return PageData;				}
	void	SetPageData(DataInPage **Data)			{	PageData=Data;					}
	void	SetPageData(int i,DataInPage *Data)		{	PageData[i]=Data;				}
	int		GetPhaseCode(void)				const	{	return PhaseCode;	}	

	DataInPage	*operator[](int page)		{	return (0<=page && page<AllocatedPageNumb)?PageData[page]:NULL;	}
	bool	IsValidData(void)		const	{	return (PageData==NULL)?false:true;		}

	bool	IsCalcDone(void)	const;
	bool	IsEdited(void)		const;
	void	SetEdited(bool edited);
	
	bool	LoadFilterContainer(QIODevice *f);
	bool	SaveFilterContainer(QIODevice *f);
	FilterInstanceContainer	*GetFilterContainer(int page){	return FilterContainer[page];	}

	bool    SaveControlPointsForPages(QIODevice *f);
	bool    LoadControlPointsForPages(QIODevice *f);
	void	CopyControlPointsForPages(int SourcePage ,int DestPage);
	const	XYPointContainerWithName	&GetControlPointsForPages(int page);

	bool	SavePhaseSource(QIODevice *f);
	bool	LoadPhaseSource(QIODevice *f);

	void	LockTarget(void);
	void	UnlockTarget(void);
	void	LockMaster(void);
	void	UnlockMaster(void);

	bool	ExecuteFilterBeforeScan(LayersBase *Base);
	ExeResult	ExecuteFilterExecuteInitialAfterEdit	(void);
	ExeResult	ExecuteFilterExecuteStartByInspection	(void);
	ExeResult	ExecuteFilterExecutePreAlignment		(void);
	ExeResult	ExecuteFilterExecuteAlignment			(void);
	ExeResult	ExecuteFilterExecutePreProcessing		(void);
	ExeResult	ExecuteFilterExecuteProcessing			(void);
	ExeResult	ExecuteFilterExecuteProcessingRevived	(void);
	ExeResult	ExecuteFilterExecutePostProcessing		(void);
	bool	ExecuteFilteringMaster(LayersBase *Base);
	bool	ExecuteFilteringTarget(LayersBase *Base);

	void	CopyImageMasterFrom(LayersBase *Base,PageDataInOnePhase *src);
	void	CopyImageTargetFrom(LayersBase *Base,PageDataInOnePhase *src);
	void	CopyPageData(int DstPage ,int SrcPage ,bool ModeCopyAllAlgorithm=true ,bool ModeCopyAllFilter=true);

	bool	GetMasterInfo(int32 &MachineID ,QString &MasterName ,QString &Remark);
	bool	GetLotInfo(QString &LotID ,QString &LotName,QString &Remark);

	void	SwapImageOutOfBuffer(int ImageDataType);
	void	SwapImageInToBuffer(int ImageDataType);

	int		GetCountOfCompressing(void);

	bool    SaveRegulation(QIODevice *f);
	bool    LoadRegulation(QIODevice *f);
	bool	HasRegulation(void);

	bool    SaveImages(QIODevice *f);
	bool    LoadImages(QIODevice *f);
	void	SwitchImageBuff(void);

	void	GetGlobalPage(int globalX1 ,int globalY1 ,int globalX2 ,int globalY2 ,IntList &PageList)	const;
	int		GetLocalPageFromArea(FlexArea &Area ,IntList &List)						const;
	int		GetLocalPageFromArea(DisplayImage *p ,FlexArea &Area ,IntList &List)	const;
	int		GetLocalPageFromVector(VectorLineBase *v,IntList &PageList)				const;
	int		GetLocalPageFromAreaFromDrawingTop(FlexArea &Area)						const;
	int		GetLocalPageFromAreaFromDrawingTop(int globalX ,int globalY)			const;
	int		GetLocalMatrixFromGlobal(int globalX ,int globalY ,int &localX ,int &localY)				const;
	void	GetGlobalMatrixFromLocal(int localPage ,int localX ,int localY ,int &globalX ,int &globalY)	const;
	bool	GetRealMatrixFromGlobal(int globalX ,int globalY ,double &realX ,double &realY)				const;
	bool	HasRealTransform(int globalX ,int globalY)								const;

	DataInPage *GetPageDataByPoint(int globalX ,int globalY)	const;
	QString		GetColorString(int gx ,int gy)	const;

	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	int		GetMaxLayerNumb(void)	const;
	int		GetDotPerLine(int page)		const;
	int		GetMaxLines(int page)		const;
	int		GetMaxDotPerLine(void)		const;
	int		GetMaxMaxLines(void)		const;

	void	CopyTargetToTransposition(void);
	void	CopyTargetToCameraBuff(void);

	AnyDataContainer	*GetAnyData(void)	const	{	return AnyData;	}

	void	ClearSystemResult(void);
signals:
	void	SignalChangedMasterImage(int phase,int Page ,int Layer);
private slots:
	void	SlotChangedMasterImage(int PageNo,int LayerNo);
};

class	DataInExecuter : public ServiceForLayers,public IdentifiedClass
{
	int32				ID;
	ResultInspection	*CurrentResultForCalc;
	bool				Calculating;
	int					InsideReEntrant;
	DWORD				StartInspectionTimeMilisec;
	bool				DonePutCurrentResult;
	ReceivedResultCountsParam	*ReceivedResultCounts;	//これはスレーブからの結果値であり、ResultInspectionとは一致しない場合がある
public:
	enum	ResultState
	{
		 _Result_None		=0
		,_Result_OK			=1
		,_Result_NG			=2
		,_Result_TimeOut	=3
		,_Result_MaxNG		=4
		,_Result_Other		=5
	}Result;
public:
	enum	ExecutingState
	{
		_None						=0
		,NowExecuteInitialAfterEdit	=1
		,NowExecuteStartByScanOnly	=2
		,NowExecuteStartByInspection=3
		,NowExecuteCaptured			=4
		,NowExecutePreAlignment		=5
		,NowExecuteAlignment		=6
		,NowExecutePreProcessing	=7
		,NowExecuteProcessing		=8
		,NowExecuteProcessingRevived=9
		,NowExecutePostProcessing	=10
		,NowExecutePreScanning		=11
		,NowExecuteScanning			=12
		,NowExecutePostScanning		=13

		,FinExecuteInitialAfterEdit	=1
		,FinExecuteStartByScanOnly	=2
		,FinExecuteStartByInspection=3
		,FinExecuteCaptured			=4
		,FinExecutePreAlignment		=5
		,FinExecuteAlignment		=6
		,FinExecutePreProcessing	=7
		,FinExecuteProcessing		=8
		,FinExecuteProcessingRevived=9
		,FinExecutePostProcessing	=10
		,FinExecutePreScanning		=11
		,FinExecuteScanning			=12
		,FinExecutePostScanning		=13

	};
private:
	ExecutingState	State;
	ExecutingState	PushedState;

public:
	DataInExecuter(int id ,LayersBase *Base);
	virtual	~DataInExecuter(void);

	void	Initial(void);
	void	SetCurrentResultForCalc(ResultInspection *L);
	void	SetStartTimeForInspect(XDateTime &d);
	ExecutingState	GetState(void)					const	{	return State;	}
	void	ForceState(ExecutingState state)				{	State=state;	}
	void	InitializeState(void);
	bool	GetDonePutCurrentResult(void)			const	{	return DonePutCurrentResult;	}
	ResultInspection	*GetResultInspection(void)	const	{	return CurrentResultForCalc;	}
	int32	GetID(void)								const	{	return ID;		}

	void	ExecuteInitialAfterEditLoop		(int ExeID);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteStartByScanOnly		(int ExeID);
	ExeResult	ExecuteStartByInspection	(int ExeID);
	ExeResult	ExecuteCaptured				(int ExeID,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment			(int ExeID);
	ExeResult	ExecuteAlignment			(int ExeID);
	ExeResult	ExecutePreProcessing		(int ExeID);
	ExeResult	ExecuteProcessing			(int ExeID);
	ExeResult	ExecuteProcessingRevived	(int ExeID);
	ExeResult	ExecutePostProcessing		(int ExeID);
	ExeResult	ExecutePreScanning			(int ExeID);
	ExeResult	ExecuteScanning				(int ExeID);
	ExeResult	ExecutePostScanning			(int ExeID);

	ExeResult	PretendFinishProcessing		(int ExeID);

	void	PushState(void);
	void	PopState(void);

	void	PutCurrentResult(void);
	void	PutForceCurrentResult(bool DependOnPhaseMode,bool DependOnPageMode);
	ReceivedResultCountsParam	*GetReceivedResultCounts(void);
	void	ClearReceivedResultCounts(void);
	void	SetResultReceivedFlag(int Page,int64 resultCounts=0 ,bool TimeOutBreak=false,bool MaxErrorBreak=false);
	bool	IsAllFinishedResultReceiving(void);
	bool	IsStrategicFinishedResultReceiving(void);
	void	SetReceivedResultCounts(ReceivedResultCountsParam *Param)	{	ReceivedResultCounts=Param;		}
	int32	GetCountOfFinishedResultReceiving(void);
	bool	IsStrategicFinishedResultReceiving(int strategicNumber);
	bool	IsResultOK(void);
	bool	IsResultTimeOut(void);
	bool	IsResultMaxError(void);
	QString	GetExecutingStateString(void);
	DWORD	GetStartInspectionTimeMilisec(void)	{	return StartInspectionTimeMilisec;	}

	void	CopyResultCountFrom(DataInExecuter &src);
	void	SetResult(ResultState r)		{	Result=r;		}
	ResultState	GetResult(void)		const	{	return Result;	}
private:
	LogicDLLBaseClass		*GetLogicDLLBase(void);
};

inline	ReceivedResultCountsParam	*DataInExecuter::GetReceivedResultCounts(void){	return ReceivedResultCounts;	}

class   LayersBase : public QObject 
					,public AuthenticationInComponent
					,public ShadowTree
					,public IdentifiedClass
{
	Q_OBJECT

	friend class   DataInLayer;
	friend class   DataInPage;
	friend class   GUIFormBase;

	const LayersBase	*Parent;
	QString TypeName;

	Qt::HANDLE				MainThread;
	PageDataInOnePhase		*PageData;
	//int32					AllocatedPageNumb;
	int32					AllocatedPhaseNumb;
	PageDataInOnePhase		**PageDataPhase;
	int32					CurrentPhase;
	int32					ShadowNumber;
	int32					CurrentShadowNumber;
	int32					ReturnCode	;
	bool					FastBoot	;
	bool					StartThreadWriteMode;
	int						NumThreads;

	NPListPack<CommErrorList>	CommErrorListContainer;
	QMutex						MutexCommErrorList;

	NPListPack<AlgorithmBasePointerList>	PreAlignmentBase;
	NPListPack<AlgorithmBasePointerList>	AlignmentBase;
	NPListPack<AlgorithmBasePointerList>	PreProcessingBase;
	NPListPack<AlgorithmBasePointerList>	ProcessingBase;
	NPListPack<AlgorithmBasePointerList>	PostProcessingBase;

	CmdWritternResult	*PacketWritternResult;

	DataInExecuter	**ExecuterDim;
	int				AllocExecuterDim;
	int				CurrentCalcPoint;
	int				CurrentDrawPoint;
	int				LastCurrentCalcPoint;
	bool			EnableFilter;
	bool			EnableProcess;

	XDateTime		StartInspectionTime;
	XDateTime		EndInspectionTime;

	ParamGlobal		*ParamGlobalData;
	ParamComm		*ParamCommData;
	ParamGUI		*ParamGUIData;

	BufferInfoList	*BufferInfoListDim;
	int				AllocatedBufferInfoCount;

	LevelFolder		*CurrentLevel;

	NPListPack<ReceiverList>				*RCmdBase;
	NPListPack<DirectCommReceiverList>		*RCmdDirectCommBase;
	GUICmdPacketBasePointerListContainer	GUICmdContainer;
	DirectCmdPacketBaseContainer			DirectCmdContainer;
	QMutex									GUICmdPacketMutex;
	bool									*SendingData;

	NPListPack<ReceiverList>			*RIntegrationCmdBase;
	IntegrationCmdPacketBasePointerListContainer	IntegrationCmdContainer;
	QMutex								CmdIntegrationPacketMutex;
	bool								*IntegrationSendingData;

	bool			*AckFlag;
	int32			AllocatedAckFlag;
	int				AckFilterID;

	bool			EnableLoopOnIdle;

	DataInPage::ConstructionData	*GlobalOffset;
	int								GlobalPageNumb;

	DWORD							MilisecExecuteFilter;
	QTime							StartTimeExecuteFilter;

	DataInPage						**DrawPageIndex;	//描画順序
	int64							_CurrentInspectID;
	int64							_LastInspectID;
	ResultInspectionPointerStock	*ResultInspectionPointerStocker;
	bool							ForceChangedInspectID;
	QApplication					*AppPointer;
	QByteArray						LightDataFromMasterData;	//照明がない場合のデータ保管場所
	LensWindowForm					*LensWindow;
	QReadWriteLock					ChangingDataStructure;		//Recursive mutex
	QMutex							MutexForLoadSave;
public:
	struct	HasChanged
	{
		bool	ChangedPreAlignment		:1;
		bool	ChangedAlignment		:1;	
		bool	ChangedPreProcessing	:1;	
		bool	ChangedProcessing		:1;	
		bool	ChangedProcessingRevived:1;	
		bool	ChangedPostProcessing	:1;	
		bool	ChangedNoProcessing		:1;
		bool	ChangedPieceProcessing	:1;
		bool	ChangedPreScanning		:1;
		bool	ChangedScanning			:1;
		bool	ChangedPostScanning		:1;
		bool	ChangedMatchAlignment	:1;	
		bool	ChangedManageResult		:1;
		bool	ChangedMasking			:1;
		bool	ChangedDynamicMasking	:1;	
	};
protected:
	struct	HasChanged	ChangedAlgo;

public:
	bool	ScanChangedInSlave(void);
	bool	IsChanged(int AlgorithmBit_Type);
	void	SetChangedStruct(const struct HasChanged &ChangedAlgoData)	{	ChangedAlgo=ChangedAlgoData;	}
	bool	UseDynamicMasking;

protected:
	int32	EventPriority;	//0:Normal(Strong)	1:Show DisplayImagePanel  2:-weaker
public:
	int		GetEventPriority(void)	{	return EventPriority;	}
	void	SetEventPriority(int n)	{	EventPriority=n;		}

protected:
	int32				MasterCode;
	QString				MasterName;
	QString				Remark;
	int32				MachineID;
	int32				MachineIDFromMaster;
	XDateTime			RegTime;
	int32				WorkerID;
	QString				WorkerName;
	int32				Version;
	int32				LoadedVersion;
	XDateTime			LastEditTime;
	int32				CategoryID;
	QSqlDatabase		*RootDBase;
	bool				OriginalRootDBase;
	int32				InspectionRemark;
	DWORD				StartInspectionTimeMilisec;
	DWORD				InspectionTimeMilisec;
	QString				CurrentPath;
	QString				UserPath;
	short				MasterType;		//0:MasterData 1:PieceData
	QImage				TopView;
	EntryPointBase		*EntryPoint;
	int					BootingLevel;	//Topでは０、部品のための子プロセスでは１、孫プロセスでは２～	NotSaved
	QString				GUIFileName;	//Not Saved
	int32				ErrorOccurs;
	bool				OnTerminating;
	bool				StopCommSender;
	QString				LocalLanguageSolutionFileName;
	int32				CurrentStrategicNumber;
	int32				CurrentStrategicNumberForSeq;
	int32				CurrentStrategicNumberForCalc;
	int32				CurrentStrategicNumberInExe;
	IntList				CurrentStrategicQueue;
	QMutex				MutexCurrentStrategic;
	int32				InsideReEntrant;
	int64				ResultWrittenID;
	bool				TmpHidingProcessingForm;
	bool				InsideLearningEditor;
	QString				SelectedImagePath;		//複数の画像パスから選択したパス
	int32				CurrentScanPhaseNumber;
	int32				CurrentLibFolderID;		//-1:Original root
	int32				ResultFromAlgorithm;	//NGのとき１
	volatile bool		OnChanging;
	volatile	int		ViewRefreshCounter;
	int32				ThresholdLevelParentID;	//0:Top root
	int32				ThresholdLevelID;
	bool				EditPasswordMode;
	bool				ReadyOK;
	bool				PossibleToUpdateDisplay;

private:
	bool							DefaultArrangeMode;
	bool							ShouldWriteResult;
	PageAndLayerFlagListContainer	CapturedPageLayerList;
	QMutex							MutexCapturedPageLayerList;
	QMutex							MutexDraw;
	QMutex							MutexWeakDraw;
	int64							InspectionNumber;
	int64							LatchedInspectionNumber;
	QString							InspectionString;
	bool							ModeInspectionPlayer;
	ZoneWindowForEdit				*ZoneWindow;
	GUIFormBase						*CurrentZoneWindowComponent;
	SystemResultStocker				SystemResultContainer;

protected:
	std::shared_ptr<DatabaseLoader>	DBLoader;
	AlgorithmDLLContainer			*AlgoDLLContPointer;
	LogicDLLBaseClass				*LogicDLLBase;
	ResultDLLBaseClass				*ResultDLLBase;
	WriteResultThread				*ResultThread;
	ClipboardList					ClipboardDatas;
	ThreadSequence					*SequenceInstance;
	LibTypeListContainer			*LibType;
	LibTypeListContainer			*InstalledLibType;
	MixTransferComm					*MTransfer;
	ResultHistryContainer			*ResultHistryData;
	PieceStocker					*PieceStock;
	ArrangementDLLBase				*ArrangementDLLStock;
	GUIFormBase						*MainWidget;
	LotBase							*LotInfo;
	OnProcessingForm				*OnProcessing;
	DirectComm						*DirectCommBase;
	LightClassPack					*LightBase;
	LogOutClass						*LogCreater;
	ParamDatabase					*LocalParamStocker;
	std::shared_ptr<FilterBankBase>	FilterBank;
	FileRegistry					*FRegistry;
	OutlineOffsetInBlob				*OutlineOffsetWriter;
	std::shared_ptr<LogoStocker>	LogoStockerInstance;
	AnyDataContainer				*AnyData;
	GeneralStockerContainer			*GeneralStockerData;
	QMutex							ErrorMutex;
	ErrorCodeListContainer			*ErrorContainer;
	LearningRegListContainer		*LearningRegData;
	std::shared_ptr<PasswordManager> PasswordHolder;
	std::shared_ptr<SyncGUIPack>	SyncGUIData;
	StatusController				*StatusControllerData;
	LearningRegister				*LearningRegisterData;
	GUIInitializer					*GuiInitializerData;
	GUIInstancePack					*GUIInstancePackData;
	ListOfQImageStocker				*ListOfQImageStockerData;
	UndoStocker						UndoDataStocker;
	UndoStocker						RedoDataStocker;
	ShowLoadingDLLForm				*InstShowLoadingDLLForm;
	LanguagePackage					*LanguagePackageData;
	GUILanguageContainer			GUILanguageContainerInst;
	ShareMasterContainer			*DataOfShareMasterContainer;
	PasteListMatrixContainer		*PasteListMatrixContainerBase;
	std::shared_ptr<OperationLogger>	OperationLoggerData;
	PrinterClassPack				*PrinterClassPackData;
	std::shared_ptr<ShrinkingPackContainer>	ShrinkingPackContainerInstance;
	IntegrationBase					*IntegrationBaseData;
	WidgetGeometry					*ResizeData;
	ResultAnalizerDLLContainer		*ResultAnalizerDLLPack;
	ResultAnalizerItemBaseContainer	*ResultAnalizerItemBasePack;
	std::shared_ptr<AuthenticationInside>	AuthenticationInst;
	ShadowTree						*ShadowTreeInst;
	FileThreadListContainer			*FileThreadListContainerInst;
	LevelFolderContainer			*LevelFolderContainerInst;

public:
    explicit	LayersBase(EntryPointBase *pEntryPoint ,bool StartThreadWriteMode=true);
	explicit	LayersBase(const QString &TypeName ,LayersBase *ParentLayer);
	explicit	LayersBase(const LayersBase *Parent,bool StartThreadWriteMode=true);
	explicit	LayersBase(const LayersBase *Parent,int shadownumber,bool StartThreadWriteMode=true);
    virtual	~LayersBase(void);

	const LayersBase	*GetParent(void)	const	{	return Parent;	}

	virtual	bool    Initial(QString &Msg,bool NoDatabase=false);
	virtual	bool	InitialDatabaseLoader(QString &Msg,bool NoDatabase=false);
	virtual	void	InitialCreatePages(bool EnabledImageMemoryAllocation=true);
    virtual	void    InitialAlgorithm(RootNameListContainer &List ,const QStringList &AlgorithmPath,bool LoadAll=false);
	virtual	void	InitializeToStart(void);
	virtual	void    InitialAfterParamLoaded(void);
	virtual	void    InitialAllocExecuterDim(void);
	virtual	void    InitialResult(bool ShowInWindow=true);
	virtual	void    InitialAlgorithmBlob(void);
	virtual	void    InitialAlgorithmLibrary(void);
	virtual	void    InitialFinalize(QWidget *mainform);
	virtual	void    InitialArrangementDLL(void);
	virtual	bool    InitialLight(bool OutputMode);
	virtual	bool    InitialFilterBank(void);
	virtual	bool    InitialResultAnalizer(void);
	virtual	bool    InitialPrinter(void);
	virtual	bool    InitialSyncGUI(void);
	virtual	void    InitialExecuter(void);
	void	SetUseDynamicMasking(bool b);

	int		GetNumThreads(void)	const	{	return NumThreads;	}

	void	StartReady(void)			{	ReadyOK=true;	}
	bool	IsReadyOK(void)		const	{	return ReadyOK;	}

	int		SetBufferInfo(const QString &BuffName ,int OriginCode ,int Pos=-1);
	BufferInfoList	*GetBufferInfo(int index);
	int		FindBufferInfo(int OriginCode);
	int		GetCountBufferInfo(void);
	void	ClearBufferInfo(void);
	void	RemoveBufferInfo(int OriginCode);
	int		ShowSelectMasterNoOriginCodeDialog(int OriginCode=-1);

	virtual	void    CopyAlgorithm	(const LayersBase *parent ,RootNameListContainer &List ,const char *AlgorithmPath,bool LoadAll=false);
	virtual	bool	CheckResultDLL(void);
	bool	CheckDependencyDLL(ComponentListContainer &NoComponentList);

	virtual	void    PrepareResult(void);
	virtual	void    CreateAlgorithmPointer(void);
	virtual	void    ReallocAlgorithm(void);
	virtual	void    MakeAlgorithmBlobList(ExcludedListPack &List);
	virtual	void    DeliverOutlineOffset(void);
	virtual	bool    OpenCommsForDirectComm(void);
	virtual	bool    DeliverAllCommsForDirectComm(int WaitingMiliSec);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	ReallocateMasterCount(int CountMaster);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
	bool	RemovePhase(int RemovedPhaseCode);	//can not remove phase0

	bool	TryLockRChangingDataStructure(void)	{	return ChangingDataStructure.tryLockForRead();	}
	void	LockWChangingDataStructure(void)	{	ChangingDataStructure.lockForWrite();	}
	void	LockRChangingDataStructure(void)	{	ChangingDataStructure.lockForRead();	}
	void	UnlockChangingDataStructure(void)	{	ChangingDataStructure.unlock();	}
	void	LockTarget(void);
	void	UnlockTarget(void);
	void	LockMaster(void);
	void	UnlockMaster(void);
	bool	IsPossibleToUpdateDisplay(void)	const	{	return PossibleToUpdateDisplay;	}
	void	SetPossibleToUpdateDisplay(bool b)		{	PossibleToUpdateDisplay=b;		}

    bool    OpenDatabase(XUpdateDatabase &dbase);
    bool    CloseDatabase(void);
	void	SetDatabase(QSqlDatabase *dbase);
	bool	IsValidDatabase(void);
    void    Release(void);
	void    ReleaseLogger(void);
	void    ReleaseBeforeReleasingGUI(void);
	void    ReleaseAll(void);

	bool	LoadShrinkingPackContainer(void);

	int		GetCurrentShadowNumber(void)	{	return CurrentShadowNumber;	}
	void	SetCurrentShadowNumber(int n)	{	CurrentShadowNumber=n;		}
	int		GetOwnShadowNumber(void)		{	return ShadowNumber;		}
	LayersBase	*GetShadowLayersBase(int n);

	void	SetMainForm(GUIFormBase *form);
	GUIFormBase *GetMainWidget(void);
	bool		SetLanguageCode(int LanguageCode ,bool AlgorithmMode=true,bool GUIMode=true ,bool GeneralStockerMode=true);
	bool		SetLanguageCode(bool AlgorithmMode=true,bool GUIMode=true ,bool GeneralStockerMode=true);
	static		const	char	*GetLanguageSolutionFileName(void);
	bool		LoadLanguageSolution(const QString &LNGFileName);
	bool		LoadGUILanguage(const QString &GLNFileName);
	bool		SaveGUILanguage(const QString &GLNFileName);
	bool		PickupGUILanguage(void);
	GUILanguageContainer &GetGUILanguageContainer(void)			{	return GUILanguageContainerInst; }
	LanguagePackage		&GetLanguagePackageData(void)			{	return *LanguagePackageData;	}
	LanguagePackage		*GetLanguagePackageDataPointer(void)	{	return LanguagePackageData;		}
	void		SetDefaultCodec(void);
	void		RestoreCodec(void);
	QApplication	*GetApplication(void)		{	return AppPointer;		}

	bool		IsValidData(void)			const;
	DataInPage *GetPageData(int page)		const				{	return (PageData==NULL)?NULL:PageData->GetPageData(page);	}
	DataInPage *GetPageDataByPoint(int globalX ,int globalY);
	PageDataInOnePhase	*GetPageDataPhase(int phase)	const	{	return (PageDataPhase!=NULL)?PageDataPhase[phase]:NULL;	}
	PageDataInOnePhase	*GetCurrentPageDataPhase(void)	const	{	return PageData;	}
	virtual	void	Draw(QImage &img, int movx ,int movy ,double ZoomRate);

	ParamGlobal	*GetParamGlobal(void)	const;
	ParamComm	*GetParamComm(void)		const;
	ParamGUI	*GetParamGUI(void)		const;
	bool		IsValid(int page ,int layer)	const;

	void	operator=(GUICmdPacketBase *s);
	void	operator=(DirectCommPacketBase *s);
	void	operator=(IntegrationCmdPacketBase *s);

	GUICmdPacketBasePointerListContainer			&GetGUICmdContainer						(void)	{	return	GUICmdContainer	;			}
	DirectCmdPacketBaseContainer					&GetDirectCmdContainer					(void)	{	return	DirectCmdContainer;			}
	IntegrationCmdPacketBasePointerListContainer	&GetIntegrationCmdContainer				(void)	{	return	IntegrationCmdContainer;	}
	void	RemovePacket(const QString &DLLRoot,const QString &&DLLName);

	bool		InitialParamFromDatabase(int masterCode);

	EntryPointBase	*GetEntryPoint(void)	const	{	return EntryPoint;	}

	int		GetCountAllMasterBuff(void)		const;
	int		GetCountOnlyMasterBuff(void)	const;
	int		GetCountDispatchMasterBuff(void)const;
	int		GetCountAllBackGroundBuff(void)		const;
	int		GetCountOnlyBackGroundBuff(void)	const;

	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	int		GetLayerNumb(int page)			const;
	int		GetMaxLayerNumb(void)		const;
	int		GetPageNumb(void)			const;
	int		GetPhaseNumb(void)			const;
	int		GetDotPerLine(int page)		const;
	int		GetMaxLines(int page)		const;
	int		GetMaxDotPerLine(void)		const;
	int		GetMaxMaxLines(void)		const;
	int		GetCurrentPhase(void)		const;
	int		SetCurrentPhase(int phase)	;
	void	ResetSize(void);

	GUIFormBase	*FindByName(const QString &FormRoot ,const QString &FormName ,const QString &InstName)	const;
	GUIFormBase	*FindByName(const QString &InstName)													const;
	int EnumGUIInst(const QString &FormRoot ,const QString &FormName ,GUIFormBase *Ret[] ,int MaxRet)	const;
	int EnumGUI(GUIFormBase *Ret[] ,int MaxRet)															const;
	void	SetAreaSizeInImagePanel(bool DrawWholeMode=false);
	bool	ChangeGUI(const QString &GUIFileData);

	LogicDLL		*GetAlgorithmDLL(const QString &_DLLRoot ,const QString &_DLLName)	const;
	AlgorithmBase	*GetAlgorithmBase(const QString &_DLLRoot ,const QString &_DLLName)	const;
	AlgorithmBase	*GetAlgorithmBase(int LibType)										const;
	void	GetAlgorithmByType(AlgorithmBasePointerContainer &Bases ,int AlgorithmType)	const;
	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const;

	bool			IsDatabaseOk(void)	const	{		return (RootDBase==NULL)?false:true;	}
	QSqlDatabase	&GetDatabase(void)	const	{		return *RootDBase;	}

	bool	DatabaseInitialLoad(const QString &PathAndFileName);
	bool	DatabaseRelease(void);
	void	DatabaseLock(void);
	void	DatabaseUnlock(void);

	void	LockForLoadSave(void);
	void	UnlockForLoadSave(void);

	ResultInspection	*GetCurrentResultForCalc(void)	const;
	ResultInspection	*GetNextResultForCalc(void)		const;
	ResultInspection	*GetCurrentResultForDraw(void)	const;
	ResultInspection	*GetBufferedResult(int64 inspectionID)	const;
	ResultInspection	*GetBufferedResultAbsolutely(int64 inspectionID)	const;
	ResultInspection	*GetBufferedOlderResult(int64 inspectionID, int GenerationLevel=0)	const;
	void	PushExecuterState(void);
	void	PopExecuterState(void);

	void	SetCurrentResultForCalcPointer(ResultInspection *res);
	void	SetCurrentResultForDrawPointer(ResultInspection *res);
	void	RewindCalcPoint(void);
	void	GetCalcPoint(int CPoints[])	const;
	void	SetCalcPoint(int CPoints[]);
	void	DecPoint(void);
	void	ClearAllReceivedResultCounts(void);

	DataInExecuter::ExecutingState	GetCurrentStateInexecuter(int index)	const;
	int		GetIndexInCurrentStateExecuter(DataInExecuter::ExecutingState state);
	bool	SetCurrentStateInExecuter(int index ,DataInExecuter::ExecutingState state);

	int64	GetCurrentInspectIDForDisplay(void)	const	{	return _LastInspectID;		}
	int64	GetCurrentInspectIDForExecute(void)	const	{	return _CurrentInspectID;	}
	void	ClearInspectID(void);
	void	IncrementInspectID(void);
	void	DecrementInspectID(void);
	void	SetCurrentInspectID(int64 id);
	void	SetForceChangedInspectID(void);
	void	ResetForceChangedInspectID(void)		{	ForceChangedInspectID=false;	}
	bool	GetForceChangedInspectID(void)	const	{	return ForceChangedInspectID;	}

	int32	GetCurrentScanPhaseNumber(void)	const;
	void	SetCurrentScanPhaseNumber(int n);
	void	TF_SetCurrentScanPhaseNumber(int n);
	void	IncreaseCurrentScanPhaseNumber(void);
	void	GetCurrentPhaseFromScanPhase(IntList &PhaseCodes)	const;
	void	GetPhaseFromScanPhase(int ScanPhaseNumber ,IntList &PhaseCodes)	const;
	void	GetScanPhaseFromPhase(int phase ,int &RetScanPhaseNumber)		const;
	void	MakeCapturedAllList(ListPhasePageLayerPack &CapturedList);

	ClipboardAlgorithm	*SearchClipboard(const XDateTime &id);
	int		GetSelectedItemCount(const QString &DLLRoot ,const QString &DLLName);

	int32			GetMasterCode(void)				const	{	return MasterCode;	}
	void			SetMasterCode(int32	code)				{	MasterCode=code;	}
	const QString	&GetMasterName(void)			const	{	return MasterName;	}
	void			SetMasterName(const QString &str)		{	MasterName=str;		}
	const QString	&GetRemark(void)				const	{	return Remark;		}
	void			SetRemark(const QString &str)			{	Remark=str;			}
	int32			GetMachineID(void)				const	{	return MachineID;	}
	void			SetMachineID(int32 id)					{	MachineID=id;		}
	int32			GetMachineIDFromMaster(void)	const	{	return MachineIDFromMaster;	}
	void			SetMachineIDFromMaster(int32 id)		{	MachineIDFromMaster=id;		}
	const XDateTime	&GetRegTime(void)				const	{	return RegTime;		}
	void			SetRegTime(const XDateTime &d)			{	RegTime=d;			}
	int32			GetWorkerID(void)				const	{	return WorkerID;	}
	void			SetWorkerID(int32 id)					{	WorkerID=id;		}
	const QString	&GetWorkerName(void)			const	{	return WorkerName;	}
	void			SetWorkerName(const QString &name)		{	WorkerName=name;	}
	int32			GetVersion(void)				const	{	return Version;		}
	void			SetVersion(int32 d)						{	Version=d;			}
	int32			GetLoadedVersion(void)			const	{	return LoadedVersion;	}
	void			SetLoadedVersion(int32 d)				{	LoadedVersion=d;		}
	const XDateTime	&GetLastEditTime(void)			const	{	return LastEditTime;	}
	void			SetLastEditTime(const XDateTime &d)		{	LastEditTime=d;			}
	int32			GetCategoryID(void)				const	{	return CategoryID;	}
	void			SetCategoryID(int32 d)					{	CategoryID=d;		}
	QSqlDatabase	*GetDataBase(void)				const	{	return RootDBase;	}
	int32			GetInspectionRemark(void)		const	{	return InspectionRemark;	}
	void			SetInspectionRemark(int32 d)			{	InspectionRemark=d;			}
	DWORD			GetStartInspectionTimeMilisec(void)	const	{	return StartInspectionTimeMilisec;	}
	void			SetStartInspectionTimeMilisec(DWORD	s);
	DWORD			GetInspectionTimeMilisec(void)		const	{	return InspectionTimeMilisec;		}
	void			SetInspectionTimeMilisec(DWORD s)			{	InspectionTimeMilisec=s;			}
	//const QString  &GetCurrentPath(void)				const	{	return CurrentPath;		}
	void			SetCurrentPath(const QString &currentPath)	{	CurrentPath=currentPath;	}
	void			SetUserPath(const QString &userPath)	{	UserPath=userPath;		}
	const QString	GetUserPath(void)				const;
	static	const QString	GetUserPath(const QString &UserPath);
	const QString	&GetSystemPath(void)			const	{	return CurrentPath;		}
	short			GetMasterType(void)			const		{	return MasterType;		}		//0:MasterData 1:PieceData
	void			SetMasterType(int mastertype)			{	MasterType=mastertype;	}		//0:MasterData 1:PieceData
	QImage			&GetTopView(void)						{	return TopView;			}
	int				GetBootingLevel(void)		const		{	return BootingLevel;	}	//Topでは０、部品のための子プロセスでは１、孫プロセスでは２～	NotSaved
	void			SetBootingLevel(int d)					{	BootingLevel=d;			}	//Topでは０、部品のための子プロセスでは１、孫プロセスでは２～	NotSaved
	const QString	&GetGUIFileName(void)		const		{	return GUIFileName;		}	//Not Saved
	void			SetGUIFileName(const QString &filename)	{	GUIFileName=filename;		}	//Not Saved
	int32			GetErrorOccurs(void)		const		{	return ErrorOccurs;		}
	void			SetErrorOccurs(int32 d)					{	ErrorOccurs=d;			}
	virtual	bool	GetOnTerminating(void)		const		{	return OnTerminating;	}
	virtual	void	SetOnTerminating(bool b)				{	OnTerminating=b;		}
	bool			GetStopCommSender(void)		const		{	return StopCommSender;	}
	int				GetLanguageCode(void);
	int64			GetResultWrittenID(void)	const		{	return ResultWrittenID;	}
	void			SetResultWrittenID(int64 id);
	int64			GetUnsavedMinimumID(void);
	int64			GetInspectionNumber(void)	const			{	return InspectionNumber;		}
	void			SetInspectionNumber(int64 d)				{	InspectionNumber=d;				}
	int64			GetLatchedInspectionNumber(void)	const	{	return LatchedInspectionNumber;	}
	void			SetLatchedInspectionNumber(int64 d)			{	LatchedInspectionNumber=d;		}
	QString			GetInspectionString(void)	const			{	return InspectionString;		}
	void			SetInspectionString(const QString &d)		{	InspectionString=d;				}
	bool			GetInsideLearningEditor(void)		const	{	return InsideLearningEditor;	}
	const QString	&GetSelectedImagePath(void)			const	{	return SelectedImagePath;		}
	void			SetSelectedImagePath(const QString &s)		{	SelectedImagePath=s;			}
	DWORD			GetMilisecExecuteFilter(void)		const	{	return MilisecExecuteFilter;	}
	void			ClearMilisecExecuteFilter(void)				{	MilisecExecuteFilter=0;			}
	const QString	&GetLocalLanguageSolutionFileName(void)const{	return LocalLanguageSolutionFileName;	}

	bool			LoadLevelFolderContainerFromDB(void);
	int32			GetThresholdLevelID(void);
	int32			GetThresholdLevelValue(int LevelID=-1);
	int32			GetThresholdLevelOrderInParent(int &CountInParent,int LevelID=-1,int LevelParentID=-1);
	int32			GetThresholdLevelOrderInParentOnly(int LevelID=-1,int LevelParentID=-1);
	int32			GetThresholdLevelIDFromOrder(int Order,int LevelParentID=-1);
	int32			GetThresholdParentLevelID(int LevelID=-1);
	QString			GetThresholdLevelName(int LevelID=-1);
	QString			GetThresholdParentLevelName(int LevelParentID=-1);
	void			SetThresholdLevel(int LevelParentID ,int LevelID);
	void			SetThresholdLevel(int LevelID);
	void			DeliverThresholdLevel(int LevelParentID ,int LevelID);
	void			DeliverThresholdLevel(void);
	void			DeliverRebuildThresholdLevel(void);
	int				EnumThresholdLevelIDInFolder(IntList &RetLevelIDs ,int LevelParentID=-1);
	void			CopyThresholdLevel(int SourceLevelID ,int DestLevelID);
	void			DeliverCopyThresholdLevel(int SourceLevelID ,int DestLevelID);
	int				SelectThresholdLevel(void);
	void			DeliverSetCurrentIntoThresholdLevel(int LevelID);
	void			SetCurrentIntoThresholdLevel(int LevelID);	//Write current threshold into ThresholdLevel

	int				GetCurrentCalcPoint(void)	const	{	return CurrentCalcPoint;	}
	void			SetCurrentCalcPoint(int n)			{	CurrentCalcPoint=n;			}
	int				GetCurrentDrawPoint(void)	const	{	return CurrentDrawPoint;	}
	int				GetLastCurrentCalcPoint(void)const	{	return LastCurrentCalcPoint;	}
	IntList			&GetCurrentStrategicQueue(void)	{	return CurrentStrategicQueue;	}

	bool			GetModeInspectionPlayer(void)const	{	return ModeInspectionPlayer;	}
	void			SetModeInspectionPlayer(bool b)		{	ModeInspectionPlayer=b;			}

	int				GetLibFolderID(void)		const	{	return CurrentLibFolderID;		}
	void			SetLibFolderID(int libFolderID ,int originalLibFolder ,bool TransferToSlave=true);	//originalLibFolder=-1: Only selection
	void			SetLibFolderID(int libFolderID)		{	CurrentLibFolderID=libFolderID;	}
	QString			GetLibFolderName(int libFolderID)		const;
	QString			GetLibTypeName(int LibType)				const;
	QString			GetLibraryName(int LibType ,int LibID)	const;

	void			SetEditPasswordMode(bool b)			{	EditPasswordMode=b;			}
	bool			GetEditPasswordMode(void)	const	{	return EditPasswordMode;	}

	std::shared_ptr<DatabaseLoader>	&GetDatabaseLoader(bool CheckDB=true)	const;
	AlgorithmDLLContainer	*GetAlgoDLLContPointer(void)	;
	AlgorithmDLLContainer	*GetAlgoDLLContPointer(void)	const;
	LogicDLLBaseClass		*GetLogicDLLBase(void)			const;
	ResultDLLBaseClass		*GetResultDLLBase(void)			const;
	WriteResultThread		*GetResultThread(void)			const;
	ClipboardList			*GetClipboardDatas(void)		const;
	ThreadSequence			*GetSequenceInstance(void)		const;
	SeqControl				*GetSeqControl(void)			const;
	void					SetSequenceInstance(ThreadSequence *seq);
	LibTypeListContainer	*GetLibType(void)				const;
	LibTypeListContainer	*GetInstalledLibType(void)		const;
	MixTransferComm			*GetMTransfer(void)				const;
	ResultHistryContainer	*GetResultHistryData(void)		const;
	PieceStocker			*GetPieceStock(void)			const;
	ArrangementDLLBase		*GetArrangementDLLStock(void)	const;
	OnProcessingForm		*GetOnProcessing(void)			const;
	DirectComm				*GetDirectCommBase(void)		const;
	void					SetDirectCommBase(DirectComm *s){	DirectCommBase=s;	}
	LightClassPack			*GetLightBase(void)				const;
	LotInformation			*GetLot(int n)					const;
	LotBase					*GetLotBase(void)				const;
	LogOutClass				*GetLogCreater(void)			const;
	ParamDatabase			*GetLocalParamStocker(void)		const;
	QTextCodec				*GetDefaultCodecCString(void)	const;
	QTextCodec				*GetDefaultCodecLocale(void)	const;
	QTextCodec				*GetDefaultCodecTr(void)		const;
	QTextCodec				*GetCurrentCodecCString(void)	const;
	QTextCodec				*GetCurrentCodecLocale(void)	const;
	QTextCodec				*GetCurrentCodecTr(void)		const;
	int						GetCodecPushedCount(void)		const;
	std::shared_ptr<FilterBankBase>		GetFilterBank(void)	const;
	FileRegistry			*GetFRegistry(void)				const;
	OutlineOffsetInBlob		*GetOutlineOffsetWriter(void)	const;
	std::shared_ptr<LogoStocker>	GetLogoStockerInstance(void)	const;
	AnyDataContainer		*GetAnyData(void)				const;
	GeneralStockerContainer	*GetGeneralStocker(void)		const;
	ErrorCodeListContainer	*GetErrorContainer(void)		const;
	LearningRegListContainer	*GetLearningRegData(void)	const;
	std::shared_ptr<PasswordManager>	GetPasswordHolder(void)		const;
	std::shared_ptr<SyncGUIPack>		GetSyncGUIData(void)		const;
	StatusController		*GetStatusController(void)		const;
	LearningRegister		*GetLearningRegister(void)		const;
	ListOfQImageStocker		*GetListOfQImageStocker(void)	const;
	ShareMasterDestination	*GetDataOfShareMaster(void)		const;
	ShareMasterContainer	*GetDataOfShareMasterContainer(void)	const;
	GUIInstancePack	*GetGUIInstancePack(void)		const	{	return GUIInstancePackData;		}
	void	SetGUIInstancePack(GUIInstancePack *v)			{	GUIInstancePackData=v;		}
	UndoStocker				&GetUndoStocker(void)			{	return UndoDataStocker;		}
	UndoStocker				&GetRedoStocker(void)			{	return RedoDataStocker;		}
	PasteListMatrixContainer	*GetPasteListMatrixContainerBase(void)				const	{	return PasteListMatrixContainerBase;	}
	std::shared_ptr<OperationLogger>		GetOperationLoggerData(void)			const	{	return OperationLoggerData;				}
	PrinterClassPack						*GetPrinterClassPackData(void)			const	{	return PrinterClassPackData;			}
	std::shared_ptr<ShrinkingPackContainer>	GetShrinkingPackContainer(void)			const	{	return ShrinkingPackContainerInstance;	}
	IntegrationBase							*GetIntegrationBasePointer(void)		const	{	return IntegrationBaseData;			}
	void									SetIntegrationBase(IntegrationBase *b)			{	IntegrationBaseData=b;				}
	WidgetGeometry							*GetResizeContainer(void)				const	{	return ResizeData;					}
	ResultAnalizerDLLContainer				*GetResultAnalizerDLLContainer(void)	const	{	return ResultAnalizerDLLPack;		}
	ResultAnalizerItemBaseContainer			*GetResultAnalizerItemBaseContainer(void)const	{	return ResultAnalizerItemBasePack;	}
	std::shared_ptr<AuthenticationInside>	GetAuthenticationInst(void)				const	{	return AuthenticationInst;			}
	FileThreadListContainer					*GetFileThreadListContainer(void)		const	{	return FileThreadListContainerInst;	}
	LevelFolderContainer					*GetLevelFolderContainer(void)			const	{	return LevelFolderContainerInst;	}
	NPListPack<CommErrorList>				&GetCommErrorListContainer(void)				{	return CommErrorListContainer;		}

	void	SetGUIInitializer(GUIInitializer *guiInitializerData);
	GUIInitializer	*GetGuiInitializer(void)	const	{	return GuiInitializerData;	}

	void			SetGlobalOffset(int	GlobalPageNumb ,DataInPage::ConstructionData *GlobalOffset);
	DataInPage::ConstructionData *GetGlobalOffset(int GlobalPage)	const;
	void			ChangeGlobalOffset(int _GlobalPage ,XYData &Dest);

	DataInExecuter	*GetExecuter(int id)				const	{	return ExecuterDim[id];	}
	DataInExecuter	*GetExecuter(const XDateTime &Key)	const;
	DataInExecuter	*GetExecuter(ResultInspection *Res)	const;

	void	BroadcastMachineID(void);
	bool	MachineIDExists(void);

	virtual	bool    SaveTargetImage(const QString &filename);
    virtual	bool    LoadTargetImage(const QString &filename);
    virtual	bool    SaveMasterImage(const QString &filename);
    virtual	bool    LoadMasterImage(const QString &filename);
    virtual	bool    LoadMasterImageInPage(const QString &filename ,int LPage);

	virtual	bool    SavePixWithAlgorithm(QIODevice *f);
	virtual	bool    LoadPixWithAlgorithm(QIODevice *f);
	virtual	bool    SaveResult(QIODevice *f);
	virtual	bool    LoadResult(QIODevice *f);

	virtual	bool	AddMasterFieldData		(const QString &FieldName, const QVariant &data);
	virtual	bool	AddMasterFieldData		(int MasterCode,const QString &FieldName, const QVariant &data);
	virtual	bool	AddRelationFieldData	(int RelationCode,const QString &FieldName, const QVariant &data);
	virtual	bool	LoadMasterFieldData		(const QString &FieldName, QVariant &data);
	virtual	bool	LoadMasterFieldData		(int MasterCode,const QString &FieldName, QVariant &data);
	virtual	bool	LoadRelationFieldData	(int RelationCode,const QString &FieldName, QVariant &data);
	bool	CheckInstalledAlgorithm(RootNameListContainer &FromGUI,RootNameListContainer &LackOfAlgorithm);

    virtual	bool    LoadBitmapToMaster(int page ,QIODevice *f);
    virtual	bool    SaveBitmapFromMaster(int page ,QIODevice *f);
    virtual	bool    LoadBitmapToTarget(int page ,QIODevice *f);
    virtual	bool    SaveBitmapFromTarget(int page ,QIODevice *f);
	virtual	bool	CopyImage(int sourceImageType ,int destImageType);

	virtual	bool	LoadPIX(QIODevice &RFile ,ImageBuffer ***Buff,int PageCount ,int LayerCount);
					//	*Buff[Layer][Page]
	virtual	bool	LoadPIXInfo(QIODevice &RFile
								,int32	&Ver
								,int32	&iDotPerLine
								,int32	&iMaxLines
								,int32	&iPageNumb
								,int32	&iLayerNumb
								,int32	&iYCountBase);

	bool    SaveBrightTable(QIODevice *f);
	bool    LoadBrightTable(QIODevice *f);
	virtual	bool    SaveAttrDefault(void);
	virtual	bool    LoadAttrDefault(void);
	virtual	bool    SaveAttr(QIODevice *f);
	virtual	bool    LoadAttr(QIODevice *f);
	virtual	bool    SaveImages(QIODevice *f);
	virtual	bool    LoadImages(QIODevice *f);
	virtual	bool    SaveAllAlgorithm(QIODevice *f);
	virtual	bool    LoadAllAlgorithm(QIODevice *f);
	virtual	bool    SaveHeader(QIODevice *f);
	virtual	bool    LoadHeader(QIODevice *f);

	virtual	bool    SaveRegulation(QIODevice *f);
	virtual	bool    LoadRegulation(QIODevice *f);
	virtual	bool    SaveRegulationDefault(void);
	virtual	bool    LoadRegulationDefault(void);
	virtual	bool	HasRegulation(void);

	QString	GetFilterDefFileName(void)	const;
	bool	LoadFilterDef(void);
	bool	SaveFilterDef(void);
	bool	LoadFilterDef(QIODevice *f);
	bool	SaveFilterDef(QIODevice *f);
	bool	ExecuteFilterBeforeScan(void);
	bool	ExecuteFilteringMaster(void);
	bool	ExecuteFilteringTarget(void);
	bool	IsEnableFilter(void)	const	{	return EnableFilter;	}
	void	SetEnableFilter(bool b)			{	EnableFilter=b;			}

	bool	IsEnableProcess(void)	const	{	return EnableProcess;	}
	void	SetEnableProcess(bool b)		{	EnableProcess=b;		}

	void	GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	int		GetGlobalPage(int globalX ,int globalY)		const;
	void	GetGlobalPage(int globalX ,int globalY,IntList &PageList)	const;
	void	GetGlobalPage(int globalX1 ,int globalY1 ,int globalX2 ,int globalY2 ,IntList &PageList)	const;
	int		GetLocalPageFromArea(FlexArea &Area,IntList &PageList)		const;
	int		GetLocalPageFromArea(DisplayImage *p,FlexArea &Area,IntList &PageList)	const;
	int		GetLocalPageFromAreaFromDrawingTop(FlexArea &Area)			const;
	int		GetLocalPageFromAreaFromDrawingTop(int globalX ,int globalY)const;
	int		GetLocalPageFromGlobal	(int globalPage)					const;
	int		GetGlobalPageFromLocal	(int localPage)						const;
	QString	GetColorString(int gx ,int gy)								const;
	int		GetGlobalPageNumb(void)			const	{	return GlobalPageNumb;	}
	XYData	*GetGlobalOutlineOffset(int globalpage)	const;
	int		GetLocalPageFromVector(VectorLineBase *v,IntList &PageList)	const;
	int		GetLocalMatrixFromGlobal(int globalX ,int globalY ,int &localX ,int &localY)	const;
	void	GetLocalMatrixFromGlobal(int GlobalPage,int globalX ,int globalY ,int &localX ,int &localY)	const;
	void	GetGlobalMatrixFromLocal(int localPage ,int localX ,int localY ,int &globalX ,int &globalY)	const;
	bool	GetRealMatrixFromGlobal(int globalX ,int globalY ,double &realX ,double &realY)	const;
	bool	HasRealTransform(int globalX ,int globalY)	const;

	bool	SQLGetMachineInfo(int MachineID 
							 ,QString &NetID
							 ,QString &Name
							 ,QString &Version
							 ,QString &Remark);
	//Following is implimented in XMasterData.cpp
	int		SQLCreateNewMasterRelation(  const QString &RelationNumber 
										,const QString &RelationName 
										,const QString &Remark 
										,int RelationType
										,int32 ThresholdLevelID);
	int		SQLSaveNewMasterData(const QString &_MasterName 
								,const QString &_Remark 
								,int32 _CategoryID
								,const QString &ImagePath
								,QString &ErrorMessageOfFalse);
	bool	SQLLoadMasterData(int masterCode,int _MachineID 
								,bool ModeLoadMasterImage
								,bool &CriticalErrorOccured
								,QString &ErrorMessageOfFalse);
	bool	SQLLoadMasterDataIn1Phase(int masterCode,int _MachineID 
								,int DestPhase
								,bool ModeLoadMasterImage
								,bool &CriticalErrorOccured
								,QString &ErrorMessageOfFalse);
	bool	SQLUpdateAlgorithmOnly(AlgorithmBase *Algo);
	bool	SQLUpdateMasterData(int _MachineID
								,const QString &ImagePath 
								,bool ForceSave 
								,QString &ErrorMessageOfFalse
								,bool UpdateGeneralSetting=true);
	bool	SQLSetRelationOnMasterData(int masterCode,int RelationCode ,int RelationID);
	int		SQLSearchMasterCode(int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount);
	void	SetAllModeLoadSaveInPlayer(bool b);
	int		SQLGetRelationCode(int masterCode);
	void	SQLSetWorker(int workerID);

	bool	LoadMasterImageInMasterData(int masterCode,int _MachineID  ,int LocalPage ,QString &ErrorMsg);
	bool	SaveMasterImageInMasterData(int masterCode,int _MachineID  ,int LocalPage ,bool ForceSave ,QString &ErrorMsg);
	bool	LoadAlgorithmDataInMasterData(int masterCode,int _MachineID
										  ,AlgorithmInPageRoot *APage
										  ,QString &ErrorMsg);
	bool	SaveAlgorithmDataInMasterData(int masterCode,int _MachineID
										  ,AlgorithmInPageRoot *APage
										  ,QString &ErrorMsg);

	bool	GetDulicatedData(int32 masterCode ,IntList &MachineList);
	bool	SaveOutlineOffsetForDatabase(void);
	bool	LoadOutlineOffsetForDatabase(void);
	bool	LoadGUIContent(const QString &GUIContentFileName);
	bool	SaveGUIContent(const QString &GUIContentFileName);
	bool	LoadGUIContent(QIODevice &GUIContentFile);
	bool	SaveGUIContent(QIODevice &GUIContentFile);

	virtual	bool		MakeExecuteInitialAfterEditInfo	(ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep=true);
	virtual	ExeResult	ExecuteStartByScanOnly	(bool ProgressStep=true);
	virtual	ExeResult	ExecuteStartByInspection(bool ProgressStep=true);
	virtual	ExeResult	ExecuteCaptured			(ListPhasePageLayerPack &CapturedList ,bool ProgressStep=true);
	virtual	ExeResult	ExecutePreAlignment		(bool ProgressStep=true);
	virtual	ExeResult	ExecuteAlignment		(bool ProgressStep=true);
	virtual	ExeResult	ExecutePreProcessing	(bool ProgressStep=true);
	virtual	ExeResult	ExecuteProcessing		(bool ProgressStep=true);
	virtual	ExeResult	ExecuteProcessingRevived(bool ProgressStep=true);
	virtual	ExeResult	ExecutePostProcessing	(bool ProgressStep=true);
	virtual	ExeResult	ExecutePreScanning		(bool ProgressStep=true);
	virtual	ExeResult	ExecuteScanning			(bool ProgressStep=true);
	virtual	ExeResult	ExecutePostScanning		(bool ProgressStep=true);

	virtual	ExeResult	PretendFinishProcessing	(bool ProgressStep=true);

	void	DeliverTransmitDirectly(GUIDirectMessage *packet);

	void	RefreshByMap(int phase ,int page ,ReflectionMode Mode,ConstMapBufferListContainer &Map);
	void	RefreshByMap(int phase ,int page ,int layer ,ReflectionMode Mode,ConstMapBufferListContainer &Map);

	bool	IsLocalCamera(void)		const;
	bool	PutCurrentResult(void);
	bool	PutForceResult(int InspectionID,bool DependOnPhaseMode,bool DependOnPageMode);
	void	SwitchImageBuff(void);
	bool	CheckSystemVersion(QStringList &Str);
	bool	GetShouldWriteResult(void)						{	return ShouldWriteResult;	}
	void	SetShouldWriteResult(bool _ShouldWriteResult)	{	ShouldWriteResult=_ShouldWriteResult;	}
	void	RemoveStockedResult(void);

	bool	CreatePartialData(int globalX1 ,int globalY1 ,int globalX2, int globalY2
							,QIODevice *createdGlobalParam ,QIODevice *createdPix);

	virtual	void	ExecuteCopy(const QString &AlgoRoot ,const QString &AlgoName ,int localPage 
								,const XDateTime &createdTime ,IntList &LayerList,bool EnableDup);

	void	CopyPageData(int DstPage ,int SrcPage	
						,bool ModeCopyAllAlgorithm ,bool ModeCopyAllFilter);

	void	SetStartInspectTime(const XDateTime &d);
	void	SetEndInspectionTime(const XDateTime &d);
	XDateTime	&GetStartInspectTime(void);
	XDateTime	&GetEndInspectionTime(void)	;
	void	CommandSaveResultToSlave(ResultInspection *Res);
	void	CommandOutputInLotChangedToSlave(void);
	void	MainFormCommand(int cmd);
	void	WroteCommon(const XDateTime &tm);
	void	WroteSlave(const XDateTime &tm);

	void	RemoveResultFromOldest(int n);

	void	CloseAll(int ReturnCode=0);
	void	CloseOne(int ReturnCode=0);
	void	SetReturnCode(int d)		{	ReturnCode=d;		}
	int32	GetReturnCode(void)	const	{	return ReturnCode;	}
	void	SetFastBoot(bool b)			{	FastBoot=b;			}
	bool	GetFastBoot(void)	const	{	return FastBoot;	}

	int		ProcessingReEntrant;
	void	ShowProcessingForm (const QString &Title ,bool CancelMode=false ,int MaxValue=-1);
	void	StepProcessing(int localpage ,const QString &message=/**/"");
	void	SetMaxProcessing(int maxValue);
	void	AddMaxProcessing(int localpage ,int maxValue);
	void	CloseProcessingForm(void);
	void	DelayedCloseProcessingForm(int sec);
	void	TmpHideProcessingForm(void);
	void	TmpRercoverProcessingForm(void);

	void	SendAckToMaster(int localpage,int FilterdID=-1);
	void	SendErrorAckToMaster(int localPage
								,int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level
								,int FilterdID=-1);
	void	SetAckFlag(int localPage ,int FilterdID=-1);
	void	ClearAllAckFlag(int FilterdID=-1);
	bool	IsAllAcknowledged(void);
	bool	WaitAllAcknowledged(int waitsecond,bool CallProcessEvent=false);

	DataInPage	*GetDrawturn(int TurnForPage)	const;
	void	SetTopInPage(DataInPage	*CurrentPage);

	void	AppendPacket(GUICmdPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className);
	bool	RemovePacket(GUICmdPacketBase *PSrc);
	void	PopupPacketPriority(GUICmdPacketBase *PSrc);
	GUICmdPacketBase *FindPacket(int globalPage ,const QString &ClassName);
	GUICmdPacketBase *FindPacket(int globalPage ,const QString &ClassName, QString &emitterRoot, QString &emitterName);

	bool	PacketSender(NPListPack<GUICmdPacketDim> &Dim ,int32 MaxWaitMiliSec=100000);
	bool	SendInfo(int globalPage);
	void    CheckSlave(NPListPack<ErrorInfoList> &ErrorPages);

	void	AppendDirectCommPacket(DirectCommPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className);
	bool	RemoveDirectCommPacket(DirectCommPacketBase *PSrc);
	void	PopupDirectCommPacketPriority(DirectCommPacketBase *PSrc);
	DirectCommPacketBase *FindDirectCommPacket(int globalPageFrom ,const QString &ClassName);
	DirectCommPacketBase *FindDirectCommPacket(int globalPageFrom ,const QString &ClassName, QString &emitterRoot, QString &emitterName);


	void	AppendIntegrationPacket(IntegrationCmdPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className);
	bool	RemoveIntegrationPacket(IntegrationCmdPacketBase *PSrc);
	void	PopupIntegrationPacketPriority(IntegrationCmdPacketBase *PSrc);
	IntegrationCmdPacketBase *FindIntegrationPacket(int slaveNo ,const QString &ClassName);
	IntegrationCmdPacketBase *FindIntegrationPacket(int slaveNo ,const QString &ClassName, QString &emitterRoot, QString &emitterName);
	void	AddIntegrationError(ErrorCodeList *e ,int slaveNo);
	bool	GetIntegrationSendingData(int slaveNo);
	void	SetIntegrationSendingData(int slaveNo ,bool d);
	bool	HasReceivedIntegrationAck(int slaveNo);

	IntegrationCommPack				*GetIntegrationCommPointer(void)			;

	void	WriteAllSettingFiles(void);
	void	ReadBaseSettingFiles	(bool Initialized=false,int BootSmall=-1);
	void	ReadOtherSettingFiles	(bool Initialized=false,int BootSmall=-1);
	void	ReadAllSettingFiles		(bool Initialized=false,int BootSmall=-1);
	void	ReadLogicSettingFiles(bool Initialized=false);
	void	SendSettingsToSlave(void);

	int		GetCurrentStrategicNumber(void);
	void	IncreaseCurrentStrategicNumber(void);
	void	SetCurrentStrategicNumber(int n);
	int		GetCurrentStrategicNumberForSeq(void);
	void	SetCurrentStrategicNumberForSeq(int n);
	int		GetCurrentStrategicNumberForCalc(void);
	void	SetCurrentStrategicNumberInExe(int d);
	int		GetCurrentStrategicNumberInExe(void)	{	return CurrentStrategicNumberInExe;	}
	void	PopCurrentStrategicNumberForCalc(void);
	void	ClearCurrentStrategicNumberForCalc(void);
	void	ForceStrategicNumber(int n);

	void	PushCapturedPageLayer(PageAndLayerFlagListContainer &CurrentCapturedPageLayerList);
	int		GetTopPageInCapturedPageLayer(void);
	int		GetTopPageInCapturedPageLayer(bool DoneFlag);
	int		GetTopLayerInCapturedPageLayer(void);
	void	ClearTopInCapturedPageLayer(void);
	bool	GetTopFlagInCaptured(void);

	bool	GetDefaultArrangeMode(void){	return DefaultArrangeMode;	}
	void	SetDefaultArrangeMode(bool d){	DefaultArrangeMode=d;	}

	void	ExecuteLogoInGUIForm(GUIFormBase *W ,const QString &dllroot ,const QString &dllname);
	void	ExecuteLogoInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname);

	void	MessageSocketError(IntList &ErrorPages);

	void	SetEntryPoint(EntryPointBase *Point)						{	EntryPoint=Point;				}
	int32	GetAllocatedPageNumb(void)									{	return (PageData!=NULL)?PageData->GetAllocatedPageNumb():0;	}
	void	SetAllocatedPageNumb(int32 Numb)							{	if(PageData!=NULL)	PageData->SetAllocatedPageNumb(Numb);	}
	DataInPage **GetPageData(void)										{	return (PageData!=NULL)?PageData->GetPageData():NULL;		}
	void	SetPageData(DataInPage **Data)								{	if(PageData!=NULL)	PageData->SetPageData(Data);			}
	void	SetPageData(int i,DataInPage *Data)							{	if(PageData!=NULL)	PageData->SetPageData(i,Data);			}
	void	SetPageData(PageDataInOnePhase *Data)						{	PageData=Data;					}
	int32	GetAllocatedPhaseNumb(void)									{	return AllocatedPhaseNumb;		}
	void	SetAllocatedPhaseNumb(int32 Numb)							{	AllocatedPhaseNumb=Numb;		}
	PageDataInOnePhase **GetPhaseData(void)								{	return PageDataPhase;			}
	void	SetPhaseData(PageDataInOnePhase **Data)						{	PageDataPhase=Data;				}
	void	SetPhaseData(int i,PageDataInOnePhase *Data)				{	PageDataPhase[i]=Data;			}
	DataInPage **GetDrawPageIndex(void)									{	return DrawPageIndex;			}
	void	SetDrawPageIndex(DataInPage **Index)						{	DrawPageIndex=Index;			}
	void	SetDrawPageIndex(int i,DataInPage *Index)					{	DrawPageIndex[i]=Index;			}

	bool	IsEdited(void);
	bool	IsCalcDone(void);
	void	SetEdited(bool edited);
	void	SetCalcDone(bool calcdone);
	void	ClearExecuterState(void);

	void	StandardManageResult(ResultInspection *Res);

	void	AddError(ErrorCodeList *e ,int localPage);
	int		GetErrorCount(void);
	void	ClearErrorCount(void);
	bool	GetError(int index ,ErrorCodeList &Ret);
	ErrorCodeList	*PopError(void);
	void	SendErrorToMaster(int errorCode=0 , const QString &errorMessage=/**/"" ,ErrorCodeList::CautionLevel level=ErrorCodeList::_None);

	void	BroadcastInspectionNumber(void);

	void	LockDraw(void)		{	MutexDraw.lock();			}
	bool	TryLockDraw(void)	{	return MutexDraw.tryLock();	}
	void	UnlockDraw(void)	{	MutexDraw.unlock();			}

	void	LockWeakDraw(void)		{	MutexWeakDraw.lock();			}
	bool	TryLockWeakDraw(void)	{	return MutexWeakDraw.tryLock();	}
	void	UnlockWeakDraw(void)	{	MutexWeakDraw.unlock();			}

	bool	IsDoneCompressed(void);
	int		GetCountOfCompressing(void);
	bool	NeedWaitingForCompress(void);

	void	SetStatusModes(GUIFormBase *f,const QStringList &modes);
	void	SetStatusModes(GUIFormBase *f,const QString &mode);

	bool	DeliverMakeUncoveredArea(void);
	void	GetAlignmentForProcessing(int page ,AlignmentPacketBase &Packet);
	void	ReloadAllAlgorithm(void);
	void	DeliverMoveForAlignment(void);

	void	DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
					,bool Mastered
					,const QColor &LColor
					,int OffsetX ,int OffsetY);
	void	SendToOtherPhaseMaster(void);
	void	SendToOtherPhaseTarget(void);
	
	int32	GetIDForUndo(void);
	void	AddUndo(UndoTopic *a);
	void	AddRedo(UndoTopic *a);
	bool	ExecuteUndoInMaster(void);
	bool	ExecuteRedoInMaster(void);

	void	TestLoadDLL(const QString &FileName);
	void	InformToLoadDLL(const QString &FileName);
	void	CloseInformed(void);

	bool	IsMainThread(void);
	void	CenterizeDialog(QWidget *w);
	void	LoopOnIdle(void);
	void	SetEnableLoopOnIdle(bool EnableFlag)	{	EnableLoopOnIdle=EnableFlag;	}
	bool	GetEnableLoopOnIdle(void)	const		{	return EnableLoopOnIdle;		}

	void	ClearHistgramData(void);
	bool	SaveHistgram(QIODevice *f);
	bool	LoadHistgram(QIODevice *f);

	void	SwapImageOutOfBuffer(int ImageDataType = ImageBufferMaster|ImageBufferTarget|ImageBufferRawTarget);
	void	SwapImageInToBuffer (int ImageDataType = ImageBufferMaster|ImageBufferTarget|ImageBufferRawTarget);

	bool	GetSendingData(int globalpage);
	void	SetSendingData(int globalpage ,bool d);
	void	SetCommErrorNoAck(int globalpage,const QString &ClassNameStr);
	void	SetCommErrorNoAck(int SlaveNo,int GlobalPage,const QString &ClassNameStr);
	void	LockMutexCommErrorList(void);
	void	UnlockMutexCommErrorList(void);

	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	ReallocXYPixelsPage(int Phase ,int Page ,int NewDotPerLine ,int NewMaxLines);
	bool	GetOnChanging(void)		{	return OnChanging;	}
	void	SetOnChanging(bool b)	{	OnChanging=b;	}

	QString	CreateGUIContentFileName(int32 masterCode,int _MachineID,const QString &ImagePath
									,int ShadowLevel=0, int ShadowNumber=0);
	void	InstallOperationLog(QObject *window);


	bool    ThinAreaN(BYTE **bmpdata
					,BYTE **bitoperation
					,int xbyte ,int YLenDot 
					,int Numb
					,FlexArea *ForceZone=NULL
					,bool EnableThread=true);
	bool    FatAreaN(BYTE **bmpdata
					,BYTE **bitoperation
					,int xbyte ,int YLenDot 
					,int Numb
					,FlexArea *ForceZone=NULL
					,bool EnableThread=true);
	bool    ThinArea1(BYTE **bmpdata
					,BYTE **bitoperation
					,int xbyte ,int YLenDot 
					,FlexArea *ForceZone=NULL
					,bool EnableThread=true);	//1画素収縮して切れる場合、残す

	LensWindowForm	*ShowLensWindow(bool ON ,const QString &WindowTitle=QString(/**/"Lens"));
	LensWindowForm	*ShowLensWindow(void);
	LensWindowForm	*ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY);
	bool		IsShowingLensWindow(void);

	void	SetZoneWindow(GUIFormBase *w);
	void	SetMoveZoneWindow(GUIFormBase *w);

	int		GetResultFromAlgorithm(void)	{	return ResultFromAlgorithm;	}
	void	SetResultFromAlgorithm(int b)	{	ResultFromAlgorithm=b;		}
	void	CopyTargetToTransposition(void);
	void	CopyTargetToCameraBuff(void);

	void	SetProcessDone(bool b=true);
	void	DeliverResultAnalizerData(void);

	bool	MakeImageNGCircle(QImage *tNGData ,QPainter *tPntFromNGData
					 ,int dtype //DisplayImage::DisplayType
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,bool RedCircleMode
					 ,bool ShowNGMarkInTarget
					 ,bool &RetNGData);

	bool    SaveControlPointsForPages(QIODevice *f);
	bool    LoadControlPointsForPages(QIODevice *f);
	bool    SaveControlPointsForPagesDefault(void);
	bool    LoadControlPointsForPagesDefault(void);	
	void	CopyControlPointsForPages(int SourcePhase ,int DestPhase);
	virtual	const	XYPointContainerWithName	&GetControlPointsForPages(int phase ,int page);

#define	LogoInQWidget(LayersBasePointer,QWidgetPointer ,dllroot ,dllname)	LayersBasePointer->ExecuteLogoInQWidget(QWidgetPointer ,typeid(QWidgetPointer).name(),dllroot ,dllname);

	QString LGetExistingDirectory	(QWidget* parent = 0, const QString& caption = QString(), const QString& dir = QString());
	QString LGetOpenFileName		(QWidget* parent = 0, const QString& caption = QString(), const QString& dir = QString(), const QString& filter = QString(), QString* selectedFilter = 0);
	QStringList LGetOpenFileNames	(QWidget* parent = 0, const QString& caption = QString(), const QString& dir = QString(), const QString& filter = QString(), QString* selectedFilter = 0);
	QString LGetSaveFileName		(QWidget* parent = 0, const QString& caption = QString(), const QString& dir = QString(), const QString& filter = QString(), QString* selectedFilter = 0);

	bool	CopyThresholdToClipboard(AlgorithmThreshold *Thr);
	bool	PasteThresholdFromClipboard(AlgorithmThreshold *Thr);

	void	ClearSystemResult(void);
	void	ReallocateSystemResult(int AllocCount);
	void	PushSystemResult(const QByteArray &data);
	SystemResult	*PopSystemResult(void);
	SystemResult	*GetLastSystemResult(void);
	int		GetStockedSystemResult(void);
private:
	bool	SQLUpdateMasterDataHeader(QBuffer &GeneralBuff ,QBuffer	&SettingBuff ,QBuffer &TopViewBuff 
									,QBuffer &LightBuff 
									,QBuffer &GeneralStockerBuff 
									,QBuffer &ResultAnalizerBuff
									,bool UpdateGeneralSetting
									,QString &ErrorMessageOfFalse);
	NPListPack<ReceiverList>			*GetRCmdBase(void)						{	return RCmdBase;						}
	NPListPack<DirectCommReceiverList>	*GetRCmdDirectCommBase(void)			{	return RCmdDirectCommBase;				}
	NPListPack<ReceiverList>			*GetRIntegrationCmdBase(void)			{	return RIntegrationCmdBase;				}

	void	SaveSlaveCommand(ResultInspection *Res);
	void	TF_BufferInfo(void);
	void	TF_ClearBufferInfo(void);
	void	TF_RemoveBufferInfo(int OriginCode);
signals:
	void	SignalMainFormCommand(int cmd);
	void	SignalChangedXY();
	void	SignalChangedPhasePageLayer();
	void	SignalChangeCurrentPhase();
	void	SignalChangeCurrentStrategicNumber();
	void	SignalChangeCurrentStrategicNumberSeq();
	void	SignalChangeThresholdLevel(int OldLevelID ,int NewLevelID);
	void	SignalChangedMasterImage(int Phase ,int Page ,int Layer);
private slots:
	void	SlotChangedMasterImage(int PhaseNo,int PageNo,int LayerNo);
public:
	void	SetChangedMasterImage(int PhaseNo,int PageNo,int LayerNo);
};

inline	void	LayersBase::SetGUIInitializer(GUIInitializer *guiInitializerData)	{	GuiInitializerData=guiInitializerData;	}

inline	AlgorithmDLLContainer	*LayersBase::GetAlgoDLLContPointer(void)		{	return AlgoDLLContPointer;		}
inline	AlgorithmDLLContainer	*LayersBase::GetAlgoDLLContPointer(void) const	{	return AlgoDLLContPointer;		}
inline	GUIFormBase				*LayersBase::GetMainWidget(void)				{	return MainWidget;				}
inline	LogicDLLBaseClass		*LayersBase::GetLogicDLLBase(void)		const	{	return LogicDLLBase;			}
inline	ResultDLLBaseClass		*LayersBase::GetResultDLLBase(void)		const	{	return ResultDLLBase;			}
inline	WriteResultThread		*LayersBase::GetResultThread(void)		const	{	return ResultThread;			}
inline	ClipboardList			*LayersBase::GetClipboardDatas(void)	const	{	return (ClipboardList *)&ClipboardDatas;			}
inline	void					LayersBase::SetSequenceInstance(ThreadSequence *seq){	SequenceInstance=seq;		}
inline	ThreadSequence			*LayersBase::GetSequenceInstance(void)	const	{	return SequenceInstance;		}
inline	LibTypeListContainer	*LayersBase::GetLibType(void)			const	{	return LibType;					}
inline	LibTypeListContainer	*LayersBase::GetInstalledLibType(void)	const	{	return InstalledLibType;		}
inline	MixTransferComm			*LayersBase::GetMTransfer(void)			const	{	return MTransfer;				}
inline	ResultHistryContainer	*LayersBase::GetResultHistryData(void)	const	{	return ResultHistryData;		}
inline	PieceStocker			*LayersBase::GetPieceStock(void)		const	{	return PieceStock;				}
inline	ArrangementDLLBase		*LayersBase::GetArrangementDLLStock(void)const	{	return ArrangementDLLStock;		}
inline	OnProcessingForm		*LayersBase::GetOnProcessing(void)		const	{	return OnProcessing;			}
inline	DirectComm				*LayersBase::GetDirectCommBase(void)	const	{	return DirectCommBase;			}
inline	LotBase					*LayersBase::GetLotBase(void)			const	{	return LotInfo;					}
inline	LightClassPack			*LayersBase::GetLightBase(void)			const	{	return LightBase;				}
inline	LogOutClass				*LayersBase::GetLogCreater(void)		const	{	return LogCreater;				}
inline	ParamDatabase			*LayersBase::GetLocalParamStocker(void)	const	{	return LocalParamStocker;		}
inline	std::shared_ptr<FilterBankBase>	LayersBase::GetFilterBank(void)	const	{	return FilterBank;				}
inline	FileRegistry			*LayersBase::GetFRegistry(void)			const	{	return FRegistry;				}
inline	OutlineOffsetInBlob		*LayersBase::GetOutlineOffsetWriter(void)const	{	return OutlineOffsetWriter;		}
inline	std::shared_ptr<LogoStocker>	LayersBase::GetLogoStockerInstance(void)	const	{	return LogoStockerInstance;		}
inline	AnyDataContainer		*LayersBase::GetAnyData(void)			const	{	return AnyData;					}
inline	GeneralStockerContainer	*LayersBase::GetGeneralStocker(void)	const	{	return GeneralStockerData;		}
inline	ErrorCodeListContainer	*LayersBase::GetErrorContainer(void)	const	{	return ErrorContainer;			}
inline	LearningRegListContainer	*LayersBase::GetLearningRegData(void)const			{	return LearningRegData;			}
inline	std::shared_ptr<PasswordManager>	LayersBase::GetPasswordHolder(void)	const	{	return PasswordHolder;			}
inline	std::shared_ptr<SyncGUIPack>		LayersBase::GetSyncGUIData(void)	const	{	return SyncGUIData;				}
inline	StatusController		*LayersBase::GetStatusController(void)			const	{	return StatusControllerData;	}
inline	LearningRegister		*LayersBase::GetLearningRegister(void)			const	{	return LearningRegisterData;	}
inline	ListOfQImageStocker		*LayersBase::GetListOfQImageStocker(void)		const	{	return ListOfQImageStockerData;	}
inline	ShareMasterContainer	*LayersBase::GetDataOfShareMasterContainer(void)const	{	return DataOfShareMasterContainer;	}
inline	bool					LayersBase::IsValidData(void)					const	{	return (PageData!=NULL)?PageData->IsValidData():false;	}


//========================================================================================
inline int	DataInLayer::GetLayer(void)	const	{	return Layer;						}
inline int	DataInLayer::GetPage(void)	const	{	return (ParentPage!=NULL)?ParentPage->Page:-1;			}
inline int	DataInLayer::GetPhase(void)	const	{	return (ParentPage!=NULL)?ParentPage->GetPhaseCode():-1;	}
inline LayersBase	*DataInLayer::GetLayersBase(void)	const	{	return (GetParent()!=NULL)?GetParent()->GetLayersBase():NULL;	}
inline XYData	*DataInLayer::GetOutlineOffset(void)	const	{	return (ParentPage!=NULL)?ParentPage->GetOutlineOffset():NULL;	}
inline ParamGlobal	*DataInLayer::GetParamGlobal(void)	const	{	return(GetLayersBase()->GetParamGlobal());	}
inline ParamComm	*DataInLayer::GetParamComm(void)	const	{	return(GetLayersBase()->GetParamComm());	}
inline int	DataInLayer::GetCountAllMasterBuff(void)		const	{	return(GetLayersBase()->GetCountAllMasterBuff());		}
inline int	DataInLayer::GetCountOnlyMasterBuff(void)		const	{	return(GetLayersBase()->GetCountOnlyMasterBuff());		}
inline int	DataInLayer::GetCountDispatchMasterBuff(void)	const	{	return(GetLayersBase()->GetCountDispatchMasterBuff());	}
inline int	DataInLayer::GetCountAllBackGroundBuff(void)	const	{	return(GetLayersBase()->GetCountAllBackGroundBuff());		}
inline int	DataInLayer::GetCountOnlyBackGroundBuff(void)	const	{	return(GetLayersBase()->GetCountOnlyBackGroundBuff());		}
inline int	DataInLayer::GetPageNumb(void)					const	{	return(GetLayersBase()->GetParamGlobal()->PageNumb);	}
inline int	DataInLayer::GetPhaseNumb(void)					const	{	return(GetLayersBase()->GetParamGlobal()->PhaseNumb);	}


inline PageDataInOnePhase	*DataInPage::GetParentPhase(void)	const{	return ParentPhase;		}
inline int	PageDataInOnePhase::GetCountAllMasterBuff(void)		const	{	return(GetLayersBase()->GetCountAllMasterBuff());		}
inline int	PageDataInOnePhase::GetCountOnlyMasterBuff(void)	const	{	return(GetLayersBase()->GetCountOnlyMasterBuff());		}
inline int	PageDataInOnePhase::GetCountDispatchMasterBuff(void)const	{	return(GetLayersBase()->GetCountDispatchMasterBuff());	}
inline int	PageDataInOnePhase::GetCountAllBackGroundBuff(void)	const	{	return(GetLayersBase()->GetCountAllBackGroundBuff());		}
inline int	PageDataInOnePhase::GetCountOnlyBackGroundBuff(void)const	{	return(GetLayersBase()->GetCountOnlyBackGroundBuff());		}

inline ParamGlobal	*DataInPage::GetParamGlobal(void)	const	{	return(GetLayersBase()->GetParamGlobal());	}
inline ParamComm	*DataInPage::GetParamComm(void)		const	{	return(GetLayersBase()->GetParamComm());	}
inline int	DataInPage::GetCountAllMasterBuff(void)		const	{	return(GetLayersBase()->GetCountAllMasterBuff());		}
inline int	DataInPage::GetCountOnlyMasterBuff(void)		const	{	return(GetLayersBase()->GetCountOnlyMasterBuff());		}
inline int	DataInPage::GetCountDispatchMasterBuff(void)	const	{	return(GetLayersBase()->GetCountDispatchMasterBuff());	}
inline int	DataInPage::GetCountAllBackGroundBuff(void)		const	{	return(GetLayersBase()->GetCountAllBackGroundBuff());		}
inline int	DataInPage::GetCountOnlyBackGroundBuff(void)	const	{	return(GetLayersBase()->GetCountOnlyBackGroundBuff());		}
inline int	DataInPage::GetPageNumb(void)					const	{	return(GetLayersBase()->GetParamGlobal()->PageNumb);	}
inline int	DataInPage::GetPhaseNumb(void)					const	{	return(GetLayersBase()->GetParamGlobal()->PhaseNumb);	}
inline int	DataInPage::GetPhaseCode(void)					const	{	return (ParentPhase!=NULL)?ParentPhase->GetPhaseCode():-1;		}

inline ParamGlobal	*LayersBase::GetParamGlobal(void)	const	{	return(ParamGlobalData	);	}
inline ParamComm	*LayersBase::GetParamComm(void)		const	{	return(ParamCommData	);	}
inline ParamGUI		*LayersBase::GetParamGUI(void)		const	{	return(ParamGUIData	);		}
inline int			LayersBase::GetPageNumb(void)		const	{	return(GetParamGlobal()->PageNumb);			}
inline int			LayersBase::GetPhaseNumb(void)		const	{	return(GetParamGlobal()->PhaseNumb);		}
inline int			LayersBase::GetCurrentPhase(void)	const	{	return CurrentPhase;						}

//========================================================================================

#include "XDataAlgorithm.h"

#endif
