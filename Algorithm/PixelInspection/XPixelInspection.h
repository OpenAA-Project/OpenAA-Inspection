/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPixelInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XPIXELINSPECTION_H
#define XPIXELINSPECTION_H

#define	PixelInspectionVersion	1

#include <list>
using namespace std;

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include "XStatisticPacket.h"
#include "XAutoAlignment.h"
#include "XAutoPCBHoleAligner.h"
#include "XVCutInspection.h"

class	PixelInspectionItem;
#define	PixelInspectionLibType		11

#define	ResultPixelOnItemType		6
#define	DefLibTypePixelInspection	5

//#define	SetIndependentItemDataCommand_OnlyOne	1
//#define	SetIndependentItemDataCommand_All		2
//#define	PixelHistogramListReqCommand			3
//#define	PixelHistogramListSendCommand			4
#define	PixelReqThresholdReqCommand				5
#define	PixelReqThresholdSendCommand			6
#define	PixelReqTryThresholdCommand				7
#define	PixelSendTryThresholdCommand			8
//#define	PixelReqChangeShiftCommand				9

#pragma	pack(push,1)

typedef	struct	_PixelInsData
{
	BYTE	SL,SH;
	BYTE	PL,PH;
	BYTE	RL,RH;
	BYTE	StdDisorder;												//A-20090910
//	BYTE	SearchDot;													//D-20090910
//	char	MinSearchDotX,MaxSearchDotX,MinSearchDotY,MaxSearchDotY;	//D-20090910
//	WORD	NGSize;														//D-20090910
}PixelInsData;

struct	PixelPoleMatrixStruct
{
	BYTE	S,P,R;
//	BYTE	MinS,MinP,MinR;
//	BYTE	MaxS,MaxP,MaxR;
	BYTE	SearchDot;
	WORD	NGSize;
};

#pragma	pack(pop)

struct	LeastSquaresMethodStruct
{
	double	a;
	int		b;
};

typedef	enum	_DetailType{
	_Other			=-1
	,_Resist		=0
	,_Silk			=1
	,_Pad			=2
	,_Hole			=3
	,_DCCoreArea	=4
	,_DCMaxZone		=5
	,_DCBaseArea	=6
	,_DCInsideArea	=7
	,_DCOutlineOArea=8
	,_DCOutlineTArea=9
	,_DCOutlineIArea=10
}DetailType;

typedef	enum	_ThresholdMode{
	_None		=-1
	,_Narrow	=0
	,_Broad		=1
}ThresholdMode;

#define	MakePoleIndex(r,g,b)	(((r)<<16)+((g)<<8)+(b))

///////////////↓初期バージョンの名残↓///////////////
class	PixelSampleList : public NPList<PixelSampleList>
{
public:
	QString			Name;
	ColorLogic		PickupColor;
	int				SearchDot;
	int				NGSize;

	PixelSampleList(void){	SearchDot=2;	NGSize=100;	}

	PixelSampleList	&operator=(PixelSampleList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PixelSampleContainer : public NPListPack<PixelSampleList>
{
public:
	PixelSampleContainer(void){}

	PixelSampleContainer	&operator=(PixelSampleContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
///////////////↑初期バージョンの名残↑///////////////

class	PixelInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	//狭域
    bool	DetailSettingNarrow;		//検査有効チェック
    int		SearchDotMasterNarrow;		//マスターデータ作成時の周囲包括ドット
    int		SearchDotTargetNarrow;		//検査時の探索ドット
    double	RelativeNGThresholdNarrow;	//-1<=RelativeNGThresholdNarrow<=1
    int		AbsoluteNGThresholdNarrow;	// 0<=AbsoluteNGThresholdNarrow<=255
    int		NGSizeNarrow;				//NGサイズ

	//広域
    bool	DetailSettingBroad;			//検査有効チェック
    int		SearchDotMasterBroad;		//マスターデータ作成時の周囲包括ドット
    int		SearchDotTargetBroad;		//検査時の探索ドット
    double	RelativeNGThresholdBroad;	//-1<=RelativeNGThresholdBroad<=1
    int		AbsoluteNGThresholdBroad;	// 0<=AbsoluteNGThresholdBroad<=255
    int		NGSizeBroad;				//NGサイズ

	DetailType ThrType;
	bool	IsCalcPixelInterPoration;	//ピクセル補間機能を有効にする

	PixelInspectionLibrary(int LibType,LayersBase *Base);
	virtual	~PixelInspectionLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	PixelInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	PixelInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	PixelInspectionLibraryContainer(LayersBase *base);
	virtual	~PixelInspectionLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypePixelInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Pixel Inspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new PixelInspectionLibrary(GetLibType(),GetLayersBase());	}
};

//=======================================================================================================

class	ResultInPagePixel : public ResultInPagePI
{
public:
	ResultInPagePixel(ResultBasePhase *pPhaseParent,DataInPage *pPage) :ResultInPagePI(pPhaseParent,pPage){}

	virtual	int			GetNGCount(void)	const	override;
};

class	ResultBaseForAlgorithmPixel : public ResultBaseForAlgorithmPI
{
public:
	ResultBaseForAlgorithmPixel(LogicDLL *parent) : ResultBaseForAlgorithmPI(parent){}

	virtual	ResultInPageRoot	*CreatePage(int phase ,int page);
};

//=======================================================================================================
class	PixelInspectionThreshold : public AlgorithmThreshold
{
public:
	PixelSampleContainer	SampleLists;	//初期バージョンの名残

	bool	Enable;
	DetailType		ThrType;
	ThresholdMode	ThrMode;
	int		SearchDotMaster;
	int		SearchDotTarget;
    double	RelativeNGThreshold;
    int		AbsoluteNGThreshold;
    int		NGSize;
	bool	IsCalcPixelInterPoration;

	PixelInspectionThreshold(PixelInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
///	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	void	SetDetailType	(DetailType Type)		{	ThrType=Type;	}
	void	SetThresholdMode(ThresholdMode Mode)	{	ThrMode=Mode;	}
};

//=======================================================================================================
class	ResultClusterOnItem : public AddedDataClass
{
public:
	PureFlexAreaListContainer	List;
	ResultClusterOnItem(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Clear(void){	List.RemoveAll();	}
};

class	PixelInspectionItem : public AlgorithmItemPI
{
public:
	PixelInsData	**PixData;
	int		AllocX;
	int		AllocY;

	BYTE	**NGBitmap;
	BYTE	**InsCheckedBitmap;
	BYTE	**TempNGBitmap;
//	BYTE	**ThresholdDifferencemap;
	int		XByte;
	int		XLen;
	int		YLen;
	AutoAlignmentInPage			*pAlignPage;		//アライメントポインタ（AutoAlignmentInPage *）
	AutoPCBHoleAlignerInPage	*pHoleAlignPage;	//穴アライメントポインタ（AutoPCBHoleAlignerInPage *）
	VCutInspectionInPage		*pVCutPage;			//Vカットポインタ（VCutInspectionInPage *）
	PureFlexAreaListContainer *wFPack;

	bool	IsShowOnlyDetail,IsShowOnlyCircle;

	PixelInspectionItem(void);
	~PixelInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PixelInspectionItem();	}
	//Targetの座標に対応するMaster座標を探す
	bool	GetMasterCoord				(int TX,int TY,int &MX,int &MY);

	void	GetTargetImageList			(ImageBuffer *Buffer[]);
	bool	GetMasterBrightness			(int X,int Y,BYTE Brightness[],bool Master=false);
	bool	GetAverageBrightness		(int X,int Y,int SearchDotBase,BYTE *Brightness[],bool Master=false);
	bool	GetLightBrightness			(int X,int Y,BYTE Brightness[],bool Master=false);
	bool	GetDarkBrightness			(int X,int Y,BYTE Brightness[],bool Master=false);
	bool	GetThreshold				(int X,int Y,BYTE &PL,BYTE &PH,BYTE &SL,BYTE &SH,BYTE &RL,BYTE &RH,bool Master=false);
//	bool	GetThreshold				(int X,int Y,int SearchArea,BYTE &PL,BYTE &PH,BYTE &SL,BYTE &SH,BYTE &RL,BYTE &RH);
	bool	GetTryThreshold				(int X,int Y,int SearchDotBase,int SearchArea,BYTE *PL,BYTE *PH,BYTE *SL,BYTE *SH,BYTE *RL,BYTE *RH);
	bool	GetExecProcessingForResist1	(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange);
	bool	GetExecProcessingForResist2	(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	bool	GetExecProcessingForResist3	(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange);
	bool	GetExecProcessingForResist4	(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	bool	GetExecProcessing1			(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange);
	bool	GetExecProcessing2			(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	bool	GetExecProcessing3			(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange);
	bool	GetExecProcessing4			(int X,int Y,int SearchDot,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	bool	GetTryExecProcessing1		(int X,int Y,int SearchDot,int InspectionLevel,BYTE *pPL,BYTE *pPH,BYTE *pSL,BYTE *pSH,BYTE *pRL,BYTE *pRH,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult);
	bool	GetTryExecProcessing2		(int X,int Y,int SearchDot,int InspectionLevel,BYTE *pPL,BYTE *pPH,BYTE *pSL,BYTE *pSH,BYTE *pRL,BYTE *pRH,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	void	SetReturnExecProcessing		(BYTE *ts[],int x,int y,uint64 ResultFlag,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult);
	void	SetReturnExecProcessing		(BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH,int mx,int my,uint64 ResultFlag,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult);

	const	PixelInspectionThreshold	*GetThresholdR(LayersBase *base=NULL)		{	return (const PixelInspectionThreshold *)GetThresholdBaseReadable(base);	}
	PixelInspectionThreshold			*GetThresholdW(LayersBase *base=NULL)		{	return (PixelInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold			*CreateThresholdInstance(void)	override	{	return new PixelInspectionThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

	virtual	ExeResult	ExecuteScanning			(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	bool	ManualExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	bool	ManualPixDataForResistSilk();

	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);

	void	SetAreaArrayList(FlexArea *ArrayList)			{	AreaArrayList=ArrayList;			}
	FlexArea	*GetAreaArrayList()							{	return AreaArrayList;				}
	void	SetAreaArrayCnt(int Value)						{	AreaArrayCnt=Value;					}
	int		GetAreaArrayCnt()								{	return AreaArrayCnt;				}
	void	SetUniqueID(int ID)								{	UniqueID=ID;						}

	bool	getExecuteInitialAfterEditFlag(){ return ExecuteInitialAfterEditFlag;}
	void	setExecuteInitialAfterEditFlag(bool flag){ ExecuteInitialAfterEditFlag = flag;}
private:
	bool	NowInspection;	//検査中フラグ

	bool	ExecuteInitialAfterEditFlag; // Flag for phase function

	ImageBuffer *MasterImageList[3];
	ImageBuffer *AverageImageList[3];
	ImageBuffer *LightImageList[3];
	ImageBuffer *DarkImageList[3];
	ImageBuffer *TargetImageList[3];
	ImageBuffer *DisorderImageList[3];

	struct	PixelPoleMatrixStruct	*PoleTable;

	struct point {
		int x, y;
	};
//	list<point> point_list;

	int		CurrentMasterCounter;
	bool	LoadedFlag;

	int		ThrRange;	//256-InspectionLevel
	double	RadianCoef;

	FlexArea	*AreaArrayList;			//対象AlgorithmItemのAreaリストを保持
	int			AreaArrayCnt;
	int			UniqueID;
	AlgorithmInPagePI	*DCAlgorithmInPagePIPointer;
	FlexArea	*TargetAreaArrayList;	//TargetのAlgorithmItemのAreaリストを保持
	int			TargetAreaArrayCnt;
	BYTE		**TargetDCBitmap;

	void	Alloc(void);
	void	Release(void);
	void	AllocPixDataForResistSilk(void);
	void	DeleteImageList(ImageBuffer *ImageList[]);
	void	ExecuteProcessing1(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration);
	void	ExecuteProcessing2(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration);
	bool	ExecuteProcessingFromTarget1(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange);
	bool	ExecuteProcessingFromTarget2(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange);
	void	ExecuteProcessing3(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration);
	void	ExecuteProcessing4(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration);
	int		LeftX,TopY;
	PixelInsData	**PixDataForResistSilk[2];
	bool	CalcReInspectionForResistSilk(int mx,int my,int tx,int ty,int wThresholdRange_B,int wThresholdRange_D,int wThresholdRange2_B,int wThresholdRange2_D,DetailType DPixelMode);
	bool	ExecuteProcessingFromMaster1(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange);
	bool	ExecuteProcessingFromMaster2(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange);
	void	ExecuteProcessing(PureFlexAreaList *NGBitArea,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,BYTE **DestNGBitmap);
	void	CalcExecuteProcessing(BYTE **DestNGBitmap,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int MinimumNGSizeP,int MinimumNGSizeS,int MinimumNGSizeR,int MinimumNGSizeH,int BrightnessRange);
	void	CheckNGBitmap(BYTE **DestNGBitmap,int MinimumNGSizeP,int MinimumNGSizeS,int MinimumNGSizeR,int MinimumNGSizeH);
	bool	ExecuteProcessingForDetail(ResultInItemRoot *Res,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode,int MinimumNGSize,DWORD StartMilisec,int MaxInspectMilisec,PureFlexAreaListContainer &TempFPack,int &SumAreaSize);
	void	ExecuteProcessingForDetail1(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode);
	void	ExecuteProcessingForDetail2(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode);
	void	ExecuteProcessingForDetail3(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode);
	void	ExecuteProcessingForDetail4(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode);

	void	ManualExecuteProcessing1();
	bool	ManualExecuteProcessingDetail1(int x,int y,int tx,int ty,BYTE &Ret);
	void	ManualExecuteProcessing2();
	bool	ManualExecuteProcessingDetail2(int x,int y,int tx,int ty,BYTE &Ret);
	void	ManualExecuteProcessing3();
	bool	ManualExecuteProcessingDetail3(int mx,int my,int x,int y,BYTE &Ret);
	void	ManualExecuteProcessing4();
	bool	ManualExecuteProcessingDetail4(int mx,int my,int x,int y,BYTE &Ret);
	void	ManualExecuteProcessing(PureFlexAreaList *NGBitArea);

	void	MinNGCheckedCnt(BYTE *NGCheckedCount,int &x,int &y,int &MinIndex);

	bool	CalcPixelInsData(PixelInsData P,PixelInsData P2,PixelInsData &P3);
	bool	CalcPixelInsData(int i,BYTE *PL,BYTE *PH,BYTE *SL,BYTE *SH,BYTE *RL,BYTE *RH,PixelInsData &P3);

	BYTE	**GetAutoMaskBitmap(void);
	bool	GetLightBuffList	(ImageBuffer *ImageList[]);
	bool	GetDarkBuffList		(ImageBuffer *ImageList[]);
	bool	GetDisorderBuffList	(ImageBuffer *ImageList[]);
	bool	GetAverageBuffList	(ImageBuffer *ImageList[]);

	bool	CalcThresholdImageList(int X,int Y,int SearchArea,ImageBuffer *ImageList[],BYTE &PL,BYTE &PH,BYTE &SL,BYTE &SH,BYTE &RL,BYTE &RH);

	bool	GetPixelInspectionLibrary(GUIDirectMessage *CmdPacket);
	PixelStatisticInLayer	**GetStatisticBuff(void);

	void	MakeTable(void);
	void	MakeTableForLight(void);
	void	MakeTableForDark(void);

	void	ManualMakeTableForLight();
	void	ManualMakeTableForDark();
	void	ManualMakeTable();

	bool	CalcPixelInterPoration(int tx,int ty,BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH);
	bool	ExecPixelInterPoration(int tx,int ty,int tx1,int ty1,int tx2,int ty2,BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH);

	struct	LeastSquaresMethodStruct	*MLeastSquaresMethodTable[3];
	struct	LeastSquaresMethodStruct	*TLeastSquaresMethodTable[3];
	PureFlexAreaListContainer MaskBitmapFPack;
	BYTE	**MaskBitmap;
	BYTE	**GetMaskBitmap(void);
	void	GetLeastSquaresMethodM(ImageBuffer *Buffer[],LeastSquaresMethodStruct *Least[]);
	void	GetLeastSquaresMethodT(ImageBuffer *Buffer[],LeastSquaresMethodStruct *LeastM[],LeastSquaresMethodStruct *LeastT[]);
};

class   PixelInspectionInPage : public AlgorithmInPagePI
{
	friend	class	PixelInspectionItem;
	struct	PixelPoleMatrixStruct	*PoleTable;
	int		localX;
	int		localY;

	bool	IsMultiAlgorithmSupport;
	QStringList	PLibSettingStringList;	//PixelLibrarySetting.datの文字列

	QStringList	PixelLibraryIDList;
	QStringList	PixelLibraryNameList;
	QStringList	AlgorithmListName;
	QStringList	LibraryIDList;
	QStringList	LibraryNameList;

	AlgorithmLibraryListContainer	PixelAList;
	AlgorithmLibraryListContainer	AAlignAList;

	bool	LoadedFlag;						//マスターデータがLoadされたのかどうか
	bool	InitialMultiAlgorithmSupport;	//MultiAlgorithmSupportのinitial処理

	AlgorithmInPagePI	*DCAlgorithmInPagePIPointer;
	QList<int>	UniqueIDList;
	FlexArea	**TargetAreaArrayList;	//TargetのAlgorithmItemのAreaリストを保持

	bool	LoadPixelLibrarySetting();
	bool	CheckSettingData();
	void	LoadAlgorithmData();
	bool	CheckPixelLibrarySettingData(const QStringList &myStringList,QString &Msg);
	bool	CreateLibraryNameList(const QString AlgorithmName);
	bool	CalcMultiAlgorithmSupport(int PixelLibID,const QString AlgorithmName,int LibID,int UniqueID,QString &Msg);
	BYTE	**GetResistArea();

	BYTE	**GetAutoMaskBitmap(void);

	void	Alloc(void);
	virtual	void	Release(void)	override;
	void	AllocPixDataForResistSilk(void);

	void	SetAlgorithmInPagePIPointer(AlgorithmInPagePI	*Pointer)	{	DCAlgorithmInPagePIPointer=Pointer;	}
	AlgorithmInPagePI	*GetAlgorithmInPagePIPointer()					{	return DCAlgorithmInPagePIPointer;	}
	void	ManualCreateTargetDCBitmap();

public:
	PixelInspectionInPage(AlgorithmBase *parent);
	~PixelInspectionInPage(void);

	PixelInsData	**PixDataNarrow;
	PixelInsData	**PixDataBroad;
	int		AllocX;
	int		AllocY;
	int		XByte;
	PixelInsData	**PixDataForResistSilk[2];

	BYTE	***TargetDCBitmap;

	virtual	bool    Save(QIODevice *f)	override;
    virtual	bool    Load(QIODevice *f)	override;

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			PixelInspectionItem	*a=new PixelInspectionItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInPageRoot *Res)	override;

	struct	PixelPoleMatrixStruct	*GetPoleTable()	{	return PoleTable;	};
	void	SetLocalX(int X)	{	localX=X;		}
	int		GetLocalX()			{	return localX;	}
	void	SetLocalY(int Y)	{	localY=Y;		}
	int		GetLocalY()			{	return localY;	}

	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);

	bool		GetIsMultiAlgorithmSupport()	{	return IsMultiAlgorithmSupport;	}
	QStringList	GetPLibSettingStringList()		{	return PLibSettingStringList;	}

	bool	ExecMultiAlgorithmSupport();
	bool	ReExecMultiAlgorithmSupport();
	void	DeletePixelItem();
	void	CreateItemThreshold();

	QList<int>	&GetUniqueIDList()	{	return UniqueIDList;	}
};
class	PixelInspectionBase;
class	PixelInspectionParam{
	QColor	ColorNormal;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorNormal;
	QColor	NegColorSelected;
	QColor	ColorNG;
	int		InspectionLevel;	//0-256		256:Highest
	int		SearchAreaForMakeTable;
	int		SearchDotBase;
	bool	Colored;
	int		DefaultLibraryID;
	double	NGThresholdP_B		,NGThresholdS_B	,NGThresholdR_B	,NGThresholdH_B;
	double	NGThresholdP_D		,NGThresholdS_D	,NGThresholdR_D	,NGThresholdH_D;
	int		MinimumNGSizeP		,MinimumNGSizeS	,MinimumNGSizeR	,MinimumNGSizeH;
	bool	CheckPadIns			,CheckSilkIns	,CheckResistIns	,CheckHoleIns;
	bool	DonePadIns			,DoneSilkIns	,DoneResistIns	,DoneHoleIns;
	int		NGThresholdForPad_B		,NGThresholdForPad_D	,MinimumNGSizeForPad;
	int		NGThresholdForSilk_B	,NGThresholdForSilk_D	,MinimumNGSizeForSilk;
	int		NGThresholdForResist_B	,NGThresholdForResist_D	,MinimumNGSizeForResist;
	int		NGThresholdForHole_B	,NGThresholdForHole_D	,MinimumNGSizeForHole;
	int		BrightnessRange;
	bool	IsCalcPixelInterPoration;
	bool	IsShowOnlyDetail	,IsShowOnlyCircle,IsShowBoth	,IsAllowNothing;
	int		NGSize;
	QColor	NGSizeColor;
	double	NGMarkSize;
public:
	PixelInspectionParam(void);
	void	setParam(PixelInspectionBase* PBase, int phase);

	QColor	getColorNormal()				{ return ColorNormal;}
	QColor	getColorSelected()				{ return ColorSelected;}
	QColor	getColorActive()				{ return ColorActive;}
	int32	getTransparentLevel()			{ return TransparentLevel;}
	QColor	getNegColorNormal()				{ return NegColorNormal;}
	QColor	getNegColorSelected()			{ return NegColorSelected;}
	QColor	getColorNG()					{ return ColorNG;}
	int		getInspectionLevel()			{ return InspectionLevel;}
	int		getSearchAreaForMakeTable()		{ return SearchAreaForMakeTable;}
	int		getSearchDotBase()				{ return SearchDotBase;}
	bool	getColored()					{ return Colored;}
	int		getDefaultLibraryID()			{ return DefaultLibraryID;}
	double	getNGThresholdP_B()				{ return NGThresholdP_B;}
	double	getNGThresholdS_B()				{ return NGThresholdS_B;}
	double	getNGThresholdR_B()				{ return NGThresholdR_B;}
	double	getNGThresholdH_B()				{ return NGThresholdH_B;}
	double	getNGThresholdP_D()				{ return NGThresholdP_D;}
	double	getNGThresholdS_D()				{ return NGThresholdS_D;}
	double	getNGThresholdR_D()				{ return NGThresholdR_D;}
	double	getNGThresholdH_D()				{ return NGThresholdH_D;}
	int		getMinimumNGSizeP()				{ return MinimumNGSizeP;}
	int		getMinimumNGSizeS()				{ return MinimumNGSizeS;}
	int		getMinimumNGSizeR()				{ return MinimumNGSizeR;}
	int		getMinimumNGSizeH()				{ return MinimumNGSizeH;}
	bool	getCheckPadIns()				{ return CheckPadIns;}
	bool	getCheckSilkIns()				{ return CheckSilkIns;}
	bool	getCheckResistIns()				{ return CheckResistIns;}
	bool	getCheckHoleIns()				{ return CheckHoleIns;}
	bool	getDonePadIns()					{ return DonePadIns;}
	bool	getDoneSilkIns()				{ return DoneSilkIns;}
	bool	getDoneResistIns()				{ return DoneResistIns;}
	bool	getDoneHoleIns()				{ return DoneHoleIns;}
	int		getNGThresholdForPad_B()		{ return NGThresholdForPad_B;}
	int		getNGThresholdForPad_D()		{ return NGThresholdForPad_D;}
	int		getMinimumNGSizeForPad()		{ return MinimumNGSizeForPad;}
	int		getNGThresholdForSilk_B()		{ return NGThresholdForSilk_B;}
	int		getNGThresholdForSilk_D()		{ return NGThresholdForSilk_D;}
	int		getMinimumNGSizeForSilk()		{ return MinimumNGSizeForSilk;}
	int		getNGThresholdForResist_B()		{ return NGThresholdForResist_B;}
	int		getNGThresholdForResist_D()		{ return NGThresholdForResist_D;}
	int		getMinimumNGSizeForResist()		{ return MinimumNGSizeForResist;}
	int		getNGThresholdForHole_B()		{ return NGThresholdForHole_B;}
	int		getNGThresholdForHole_D()		{ return NGThresholdForHole_D;}
	int		getMinimumNGSizeForHole()		{ return MinimumNGSizeForHole;}
	int		getBrightnessRange()			{ return BrightnessRange;}
	bool	getIsCalcPixelInterPoration()	{ return IsCalcPixelInterPoration;}
	bool	getIsShowOnlyDetail()			{ return IsShowOnlyDetail;}
	bool	getIsShowOnlyCircle()			{ return IsShowOnlyCircle;}
	bool	getIsShowBoth()					{ return IsShowBoth;}
	bool	getIsAllowNothing()				{ return IsAllowNothing;}
	int		getNGSize()						{ return NGSize;}
	QColor	getNGSizeColor()				{ return NGSizeColor;}
	double	getNGMarkSize()					{ return NGMarkSize;}

	void	setInspectionLevel			(int _InspectionLevel)			{ InspectionLevel = _InspectionLevel;}
	void	setNGThresholdP_B			(double _NGThresholdP_B)		{ NGThresholdP_B = _NGThresholdP_B;}
	void	setNGThresholdS_B			(double _NGThresholdS_B)		{ NGThresholdS_B = _NGThresholdS_B;}
	void	setNGThresholdR_B			(double _NGThresholdR_B)		{ NGThresholdR_B = _NGThresholdR_B;}
	void	setNGThresholdH_B			(double _NGThresholdH_B)		{ NGThresholdH_B = _NGThresholdH_B;}
	void	setNGThresholdP_D			(double _NGThresholdP_D)		{ NGThresholdP_D = _NGThresholdP_D;}
	void	setNGThresholdS_D			(double _NGThresholdS_D)		{ NGThresholdS_D = _NGThresholdS_D;}
	void	setNGThresholdR_D			(double _NGThresholdR_D)		{ NGThresholdR_D = _NGThresholdR_D;}
	void	setNGThresholdH_D			(double _NGThresholdH_D)		{ NGThresholdH_D = _NGThresholdH_D;}
	void	setMinimumNGSizeP			(int _MinimumNGSizeP)			{ MinimumNGSizeP = _MinimumNGSizeP;}
	void	setMinimumNGSizeS			(int _MinimumNGSizeS)			{ MinimumNGSizeS = _MinimumNGSizeS;}
	void	setMinimumNGSizeR			(int _MinimumNGSizeR)			{ MinimumNGSizeR = _MinimumNGSizeR;}
	void	setMinimumNGSizeH			(int _MinimumNGSizeH)			{ MinimumNGSizeH = _MinimumNGSizeH;}
	void	setCheckPadIns				(bool _CheckPadIns)				{ CheckPadIns = _CheckPadIns;}
	void	setCheckSilkIns				(bool _CheckSilkIns)			{ CheckSilkIns = _CheckSilkIns;}
	void	setCheckResistIns			(bool _CheckResistIns)			{ CheckResistIns = _CheckResistIns;}
	void	setCheckHoleIns				(bool _CheckHoleIns)			{ CheckHoleIns = _CheckHoleIns;}
	void	setDonePadIns				(bool _DonePadIns)				{ DonePadIns = _DonePadIns;}
	void	setDoneSilkIns				(bool _DoneSilkIns)				{ DoneSilkIns = _DoneSilkIns;}
	void	setDoneResistIns			(bool _DoneResistIns)			{ DoneResistIns = _DoneResistIns;}
	void	setDoneHoleIns				(bool _DoneHoleIns)				{ DoneHoleIns = _DoneHoleIns;}
	void	setNGThresholdForPad_B		(int _NGThresholdForPad_B)		{ NGThresholdForPad_B = _NGThresholdForPad_B;}
	void	setNGThresholdForPad_D		(int _NGThresholdForPad_D)		{ NGThresholdForPad_D = _NGThresholdForPad_D;}
	void	setMinimumNGSizeForPad		(int _MinimumNGSizeForPad)		{ MinimumNGSizeForPad = _MinimumNGSizeForPad;}
	void	setNGThresholdForSilk_B		(int _NGThresholdForSilk_B)		{ NGThresholdForSilk_B = _NGThresholdForSilk_B;}
	void	setNGThresholdForSilk_D		(int _NGThresholdForSilk_D)		{ NGThresholdForSilk_D = _NGThresholdForSilk_D;}
	void	setMinimumNGSizeForSilk		(int _MinimumNGSizeForSilk)		{ MinimumNGSizeForSilk = _MinimumNGSizeForSilk;}
	void	setNGThresholdForResist_B	(int _NGThresholdForResist_B)	{ NGThresholdForResist_B = _NGThresholdForResist_B;}
	void	setNGThresholdForResist_D	(int _NGThresholdForResist_D)	{ NGThresholdForResist_D = _NGThresholdForResist_D;}
	void	setMinimumNGSizeForResist	(int _MinimumNGSizeForResist)	{ MinimumNGSizeForResist = _MinimumNGSizeForResist;}
	void	setNGThresholdForHole_B		(int _NGThresholdForHole_B)		{ NGThresholdForHole_B = _NGThresholdForHole_B;}
	void	setNGThresholdForHole_D		(int _NGThresholdForHole_D)		{ NGThresholdForHole_D = _NGThresholdForHole_D;}
	void	setMinimumNGSizeForHole		(int _MinimumNGSizeForHole)		{ MinimumNGSizeForHole = _MinimumNGSizeForHole;}
	void	setIsCalcPixelInterPoration	(bool _IsCalcPixelInterPoration){ IsCalcPixelInterPoration = _IsCalcPixelInterPoration;}
};

class	PixelInspectionBase : public AlgorithmBase
{

	PixelInspectionParam Param[2];
	//PixelInspectionParam* currentParam; // currentParam = Param[GetLayersBase()->GetCurrentPhase()]
public:
	QColor	getColorNormal()				{ return Param[GetLayersBase()->GetCurrentPhase()].getColorNormal();}
	QColor	getColorSelected()				{ return Param[GetLayersBase()->GetCurrentPhase()].getColorSelected();}
	QColor	getColorActive()				{ return Param[GetLayersBase()->GetCurrentPhase()].getColorActive();}
	int32	getTransparentLevel()			{ return Param[GetLayersBase()->GetCurrentPhase()].getTransparentLevel();}
	QColor	getNegColorNormal()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNegColorNormal();}
	QColor	getNegColorSelected()			{ return Param[GetLayersBase()->GetCurrentPhase()].getNegColorSelected();}
	QColor	getColorNG()					{ return Param[GetLayersBase()->GetCurrentPhase()].getColorNG();}
	int		getInspectionLevel()			{ return Param[GetLayersBase()->GetCurrentPhase()].getInspectionLevel();}
	int		getSearchAreaForMakeTable()		{ return Param[GetLayersBase()->GetCurrentPhase()].getSearchAreaForMakeTable();}
	int		getSearchDotBase()				{ return Param[GetLayersBase()->GetCurrentPhase()].getSearchDotBase();}
	bool	getColored()					{ return Param[GetLayersBase()->GetCurrentPhase()].getColored();}
	int		getDefaultLibraryID()			{ return Param[GetLayersBase()->GetCurrentPhase()].getDefaultLibraryID();}
	double	getNGThresholdP_B()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdP_B();}
	double	getNGThresholdS_B()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdS_B();}
	double	getNGThresholdR_B()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdR_B();}
	double	getNGThresholdH_B()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdH_B();}
	double	getNGThresholdP_D()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdP_D();}
	double	getNGThresholdS_D()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdS_D();}
	double	getNGThresholdR_D()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdR_D();}
	double	getNGThresholdH_D()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdH_D();}
	int		getMinimumNGSizeP()				{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeP();}
	int		getMinimumNGSizeS()				{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeS();}
	int		getMinimumNGSizeR()				{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeR();}
	int		getMinimumNGSizeH()				{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeH();}
	bool	getCheckPadIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getCheckPadIns();}
	bool	getCheckSilkIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getCheckSilkIns();}
	bool	getCheckResistIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getCheckResistIns();}
	bool	getCheckHoleIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getCheckHoleIns();}
	bool	getDonePadIns()					{ return Param[GetLayersBase()->GetCurrentPhase()].getDonePadIns();}
	bool	getDoneSilkIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getDoneSilkIns();}
	bool	getDoneResistIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getDoneResistIns();}
	bool	getDoneHoleIns()				{ return Param[GetLayersBase()->GetCurrentPhase()].getDoneHoleIns();}
	int		getNGThresholdForPad_B()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForPad_B();}
	int		getNGThresholdForPad_D()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForPad_D();}
	int		getMinimumNGSizeForPad()		{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeForPad();}
	int		getNGThresholdForSilk_B()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForSilk_B();}
	int		getNGThresholdForSilk_D()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForSilk_D();}
	int		getMinimumNGSizeForSilk()		{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeForSilk();}
	int		getNGThresholdForResist_B()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForResist_B();}
	int		getNGThresholdForResist_D()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForResist_D();}
	int		getMinimumNGSizeForResist()		{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeForResist();}
	int		getNGThresholdForHole_B()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForHole_B();}
	int		getNGThresholdForHole_D()		{ return Param[GetLayersBase()->GetCurrentPhase()].getNGThresholdForHole_D();}
	int		getMinimumNGSizeForHole()		{ return Param[GetLayersBase()->GetCurrentPhase()].getMinimumNGSizeForHole();}
	int		getBrightnessRange()			{ return Param[GetLayersBase()->GetCurrentPhase()].getBrightnessRange();}
	bool	getIsCalcPixelInterPoration()	{ return Param[GetLayersBase()->GetCurrentPhase()].getIsCalcPixelInterPoration();}
	bool	getIsShowOnlyDetail()			{ return Param[GetLayersBase()->GetCurrentPhase()].getIsShowOnlyDetail();}
	bool	getIsShowOnlyCircle()			{ return Param[GetLayersBase()->GetCurrentPhase()].getIsShowOnlyCircle();}
	bool	getIsShowBoth()					{ return Param[GetLayersBase()->GetCurrentPhase()].getIsShowBoth();}
	bool	getIsAllowNothing()				{ return Param[GetLayersBase()->GetCurrentPhase()].getIsAllowNothing();}
	int		getNGSize()						{ return Param[GetLayersBase()->GetCurrentPhase()].getNGSize();}
	QColor	getNGSizeColor()				{ return Param[GetLayersBase()->GetCurrentPhase()].getNGSizeColor();}
	double	getNGMarkSize()					{ return Param[GetLayersBase()->GetCurrentPhase()].getNGMarkSize();}

	void	setInspectionLevel			(int _InspectionLevel)			{ Param[GetLayersBase()->GetCurrentPhase()].setInspectionLevel(_InspectionLevel);}
	void	setNGThresholdP_B			(double _NGThresholdP_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdP_B(_NGThresholdP_B);}
	void	setNGThresholdS_B			(double _NGThresholdS_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdS_B(_NGThresholdS_B);}
	void	setNGThresholdR_B			(double _NGThresholdR_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdR_B(_NGThresholdR_B);}
	void	setNGThresholdH_B			(double _NGThresholdH_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdH_B(_NGThresholdH_B);}
	void	setNGThresholdP_D			(double _NGThresholdP_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdP_D(_NGThresholdP_D);}
	void	setNGThresholdS_D			(double _NGThresholdS_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdS_D(_NGThresholdS_D);}
	void	setNGThresholdR_D			(double _NGThresholdR_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdR_D(_NGThresholdR_D);}
	void	setNGThresholdH_D			(double _NGThresholdH_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdH_D(_NGThresholdH_D);}
	void	setMinimumNGSizeP			(int _MinimumNGSizeP)			{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeP(_MinimumNGSizeP);}
	void	setMinimumNGSizeS			(int _MinimumNGSizeS)			{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeS(_MinimumNGSizeS);}
	void	setMinimumNGSizeR			(int _MinimumNGSizeR)			{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeR(_MinimumNGSizeR);}
	void	setMinimumNGSizeH			(int _MinimumNGSizeH)			{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeH(_MinimumNGSizeH);}
	void	setCheckPadIns				(bool _CheckPadIns)				{ Param[GetLayersBase()->GetCurrentPhase()].setCheckPadIns(_CheckPadIns);}
	void	setCheckSilkIns				(bool _CheckSilkIns)			{ Param[GetLayersBase()->GetCurrentPhase()].setCheckSilkIns(_CheckSilkIns);}
	void	setCheckResistIns			(bool _CheckResistIns)			{ Param[GetLayersBase()->GetCurrentPhase()].setCheckResistIns(_CheckResistIns);}
	void	setCheckHoleIns				(bool _CheckHoleIns)			{ Param[GetLayersBase()->GetCurrentPhase()].setCheckHoleIns(_CheckHoleIns);}
	void	setDonePadIns				(bool _DonePadIns)				{ Param[GetLayersBase()->GetCurrentPhase()].setDonePadIns(_DonePadIns);}
	void	setDoneSilkIns				(bool _DoneSilkIns)				{ Param[GetLayersBase()->GetCurrentPhase()].setDoneSilkIns(_DoneSilkIns);}
	void	setDoneResistIns			(bool _DoneResistIns)			{ Param[GetLayersBase()->GetCurrentPhase()].setDoneResistIns(_DoneResistIns);}
	void	setDoneHoleIns				(bool _DoneHoleIns)				{ Param[GetLayersBase()->GetCurrentPhase()].setDoneHoleIns(_DoneHoleIns);}
	void	setNGThresholdForPad_B		(int _NGThresholdForPad_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForPad_B(_NGThresholdForPad_B);}
	void	setNGThresholdForPad_D		(int _NGThresholdForPad_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForPad_D(_NGThresholdForPad_D);}
	void	setMinimumNGSizeForPad		(int _MinimumNGSizeForPad)		{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeForPad(_MinimumNGSizeForPad);}
	void	setNGThresholdForSilk_B		(int _NGThresholdForSilk_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForSilk_B(_NGThresholdForSilk_B);}
	void	setNGThresholdForSilk_D		(int _NGThresholdForSilk_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForSilk_D(_NGThresholdForSilk_D);}
	void	setMinimumNGSizeForSilk		(int _MinimumNGSizeForSilk)		{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeForSilk(_MinimumNGSizeForSilk);}
	void	setNGThresholdForResist_B	(int _NGThresholdForResist_B)	{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForResist_B(_NGThresholdForResist_B);}
	void	setNGThresholdForResist_D	(int _NGThresholdForResist_D)	{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForResist_D(_NGThresholdForResist_D);}
	void	setMinimumNGSizeForResist	(int _MinimumNGSizeForResist)	{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeForResist(_MinimumNGSizeForResist);}
	void	setNGThresholdForHole_B		(int _NGThresholdForHole_B)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForHole_B(_NGThresholdForHole_B);}
	void	setNGThresholdForHole_D		(int _NGThresholdForHole_D)		{ Param[GetLayersBase()->GetCurrentPhase()].setNGThresholdForHole_D(_NGThresholdForHole_D);}
	void	setMinimumNGSizeForHole		(int _MinimumNGSizeForHole)		{ Param[GetLayersBase()->GetCurrentPhase()].setMinimumNGSizeForHole(_MinimumNGSizeForHole);}
	void	setIsCalcPixelInterPoration	(bool _IsCalcPixelInterPoration){ Param[GetLayersBase()->GetCurrentPhase()].setIsCalcPixelInterPoration(_IsCalcPixelInterPoration);}
////////
	int32	MasterLoadVer;	//マスターデータのバージョン違いLoad対応
	QColor	ResultImportanceColor;

	PixelInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new PixelInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("PixelInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigPixelInspection.dat");	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	void	MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY ,AlgorithmItemIndependentPack &Data)	override;
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;
	virtual	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;
};

//============================================================================================================================

class	PixelInspectionNGDataList : public NPList<PixelInspectionNGDataList>
{
public:
	int32	Page;
	int32	LibID;
	int32	CenterX,CenterY;
	int32	Area;	//面積

	PixelInspectionNGDataList(void){}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PixelInspectionNGDataListContainer : public NPListPack<PixelInspectionNGDataList>
{
public:
	PixelInspectionNGDataListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateNGListPacket : public GUIDirectMessage
{
public:
	PixelInspectionNGDataListContainer	*Point;
	ResultInspection			*Res;
	CmdCreateNGListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetPixelInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetPixelInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetPixelInspectionLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetPixelInspectionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateTempPixelInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempPixelInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdInsertPixelInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertPixelInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdUpdatePixelInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdatePixelInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadPixelInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdLoadPixelInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDeletePixelInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeletePixelInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

//しきい値設定画面で確定
class	CmdReqCalcThresholdPacket : public GUIDirectMessage
{
public:
	CmdReqCalcThresholdPacket(LayersBase *base):GUIDirectMessage(base){}
};

//==================================================================================
class	PixelThresholdReq
{
public:
	int32	GlobalPage;
	int		PixelItemID;
//	bool	Mastered;
//	int32	Dx,Dy;

	PixelThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PixelThresholdSend
{
public:
	int32	GlobalPage;
	int		PixelItemID;

	struct	PixelPoleMatrixStruct	*PoleTable;
	int		localX;							//マウスクリック座標X
	int		localY;							//マウスクリック座標Y
	int		MasterX;						//マウスクリック座標Xに対応するマスター座標
	int		MasterY;						//マウスクリック座標Yに対応するマスター座標
	BYTE	MasterBrightness[3];			//マスター画像の輝度（検査画像から補正用）
	BYTE	MasterBrightness2[3];			//マスター画像の輝度（マスター画像から補正用）
//	BYTE	AverageBrightness[3];			//平均画像の輝度
	BYTE	*AverageBrightness[3];			//平均画像の輝度（検査画像から補正用）
	BYTE	*AverageBrightness2[3];			//平均画像の輝度（マスター画像から補正用）
	BYTE	LightBrightness[3];				//明るい画像の輝度（検査画像から補正用）
	BYTE	LightBrightness2[3];			//明るい画像の輝度（マスター画像から補正用）
	BYTE	DarkBrightness[3];				//暗い画像の輝度（検査画像から補正用）
	BYTE	DarkBrightness2[3];				//暗い画像の輝度（マスター画像から補正用）
//	BYTE	*TargetBrightness[3];			//検査画像の輝度
	ImageBuffer *TargetImageList[3];		//検査画像の輝度
	BYTE	PL,PH,SL,SH,RL,RH;				//３次元極座標での閾値
	BYTE	PLr,PHr,SLr,SHr,RLr,RHr;		//３次元極座標での閾値（レジスト検査用）
	int		InspectionLevel;				//検査レベル（0～255）
	int		SearchAreaForMakeTable;			//マスター作成時の周囲ドット数
	int		SearchDotBase;					//検査時の探索ドット数
	bool	CheckPadIns		,CheckSilkIns	,CheckResistIns	,CheckHoleIns;		//検査を行うかどうかのフラグ
	double	NGThresholdP	,NGThresholdS	,NGThresholdR	,NGThresholdH;		//NGThreshold
	int		MinimumNGSizeP	,MinimumNGSizeS	,MinimumNGSizeR	,MinimumNGSizeH;	//MinimumNGSize
	bool	DonePadIns;						//パッドの詳細検査を行うかどうかのフラグ
	int		NGThresholdForPad;				//
	int		MinimumNGSizeForPad;			//
	bool	DoneSilkIns;					//シルクの詳細検査を行うかどうかのフラグ
	int		NGThresholdForSilk;				//
	int		MinimumNGSizeForSilk;			//
	bool	DoneResistIns;					//レジストの詳細検査を行うかどうかのフラグ
	int		NGThresholdForResist;			//
	int		MinimumNGSizeForResist;			//
	bool	DoneHoleIns;					//穴の詳細検査を行うかどうかのフラグ
	int		NGThresholdForHole;				//
	int		MinimumNGSizeForHole;			//
	int		BrightnessRange;				//
	int		ThresholdRange;					//
	BYTE	PL1,PH1,SL1,SH1,RL1,RH1;		//検査での周囲平均画像のしきい値
	BYTE	PLr1,PHr1,SLr1,SHr1,RLr1,RHr1;	//検査での周囲平均画像のしきい値（レジスト検査用）
	BYTE	InsTargetBrightness[3];			//検査での周囲検査画像の輝度
	int		InsAverageCoordX;				//検査での周囲平均画像の座標X
	int		InsAverageCoordY;				//検査での周囲平均画像の座標Y
	int		InsTargetCoordX;				//検査での周囲検査画像の座標X
	int		InsTargetCoordY;				//検査での周囲検査画像の座標Y
	BYTE	InsTargetBrightness2[3];		//検査での周囲検査画像の輝度（レジスト検査用）
	int		InsAverageCoordX2;				//検査での周囲平均画像の座標X（レジスト検査用）
	int		InsAverageCoordY2;				//検査での周囲平均画像の座標Y（レジスト検査用）
	int		InsTargetCoordX2;				//検査での周囲検査画像の座標X（レジスト検査用）
	int		InsTargetCoordY2;				//検査での周囲検査画像の座標Y（レジスト検査用）
	uint64	InspectResult;					//検査結果のフラグ用
	PureFlexAreaListContainer *FPack;	//
//	BYTE	**ThresholdDifferencemap;		//NG箇所(ピクセル)の平均画像との輝度差のマップ
	int		XLen,YLen;						//画像サイズ
	AutoAlignmentInPage			*pAlignPage;		//アライメントポインタ（AutoAlignmentInPage *）
	AutoPCBHoleAlignerInPage	*pHoleAlignPage;	//穴アライメントポインタ（AutoPCBHoleAlignerInPage *）
	PixelInsData	**PixData;				//ピクセルデータ（閾値）

	PixelThresholdSend(void);

	void	ConstructList(PixelThresholdReq *reqPacket,PixelInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

private:
	double	RadianCoef;
};

class	PixelTryThresholdReq
{
public:
	int32	GlobalPage;
	int		PixelItemID;
	int		SearchAreaForMakeTable;	//マスター作成時の周囲ドット数
	int		SearchDotBase;			//検査時の探索ドット数
	struct	PixelPoleMatrixStruct	*PoleTable;
	int		InspectionLevel;		//検査レベル（0～255）
	int		localX;					//マウスクリック座標X
	int		localY;					//マウスクリック座標Y

	PixelTryThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PixelTryThresholdSend
{
public:
	int32	GlobalPage;
	int		PixelItemID;
	struct	PixelPoleMatrixStruct	*PoleTable;
	int		localX;						//マウスクリック座標X
	int		localY;						//マウスクリック座標Y

	BYTE	*AverageBrightness[3];		//平均画像の輝度
	BYTE	*TargetBrightness[3];		//検査画像の輝度
	BYTE	*PL,*PH,*SL,*SH,*RL,*RH;	//３次元極座標での閾値
	int		InspectionLevel;			//検査レベル（0～255）
	int		SearchAreaForMakeTable;		//マスター作成時の周囲ドット数
	int		SearchDotBase;				//検査時の探索ドット数
	BYTE	PL1,PH1,SL1,SH1,RL1,RH1;	//検査での周囲平均画像のしきい値
	BYTE	InsTargetBrightness[3];		//検査での周囲検査画像の輝度
	int		InsAverageCoordX;			//検査での周囲平均画像の座標X
	int		InsAverageCoordY;			//検査での周囲平均画像の座標Y
	int		InsTargetCoordX;			//検査での周囲検査画像の座標X
	int		InsTargetCoordY;			//検査での周囲検査画像の座標Y
	uint64	InspectResult;				//検査結果フラグ

	PixelTryThresholdSend(void);

	void	ConstructList(PixelTryThresholdReq *reqPacket,PixelInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif
