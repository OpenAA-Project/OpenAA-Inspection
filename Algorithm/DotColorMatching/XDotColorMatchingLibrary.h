#if	!defined(XDotColorMatchingLIBRARY_H)
#define	XDotColorMatchingLIBRARY_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeDotColorMatchingInspect	54

class	DotColorMatchingLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//生成データ
#pragma	pack(push,1)
	int32		PickupRL;
	int32		PickupRH;
	int32		PickupGL;
	int32		PickupGH;
	int32		PickupBL;
	int32		PickupBH;
	int32		EvenWidth0;		//平均輝度値0での抽出均一範囲
	int32		EvenWidth255;	//平均輝度値255での抽出均一範囲
    int32		MinDotColorMatchingSize;
    int32		MaxDotColorMatchingSize;
    int32		MinDotColorMatchingDots;
    int32		MaxDotColorMatchingDots;
    int32		LimitDotColorMatchingSize;
	int32		OverlappedLength;
	int32		GenerateOnEdgeWidth;	//0 or 10000=normal generation
	int32		OutlineAroundPriorItems;		//先に生成された領域の周囲に生成する輪郭幅
	int32		SearchDotForBrightnessRange;	//生成時のOK輝度範囲を採集する範囲
	int32		BindGroupArea;					//文字などの場合のグループ化範囲
	int32		PriorityToShow;

	WORD		NoiseSize;			//孤立点削除
	WORD		NoiseSizePinHole;	//ピンホール削除
    short		SpaceToOutline;
    WORD		Priority;
	WORD		AreaType;	//0:単色	1:グラデーション	2:文字部分	3:無地	4:CAD線上
	bool		EnableOverlap;
	bool		GenerateOutlineMode;
	bool		GenerateHalfPitch;
	double		ThresholdPickupEdge;	//RotationPattern::DivAreaを生成するときの標準偏差しきい値
	double		ThresholdFlatPattern;
	bool		UseBackGround;
	bool		GenerateOnlyLimitedMask;
#pragma	pack(pop)

//検査データ
#pragma	pack(push,1)
	struct MLibThreshold
	{
		WORD	BrightWidthRL;	//暗側輝度幅
		WORD	BrightWidthRH;	//明側輝度幅
		WORD	BrightWidthGL;	//暗側輝度幅
		WORD	BrightWidthGH;	//明側輝度幅
		WORD	BrightWidthBL;	//暗側輝度幅
		WORD	BrightWidthBH;	//明側輝度幅

		DWORD	OKDot;			//ＯＫドット数
		DWORD	OKLength;		//ＯＫ距離

		char	RThrOffsetL;	//しきい値への直接加算値(-100～100)
		char	RThrOffsetH;
		char	GThrOffsetL;
		char	GThrOffsetH;
		char	BThrOffsetL;
		char	BThrOffsetH;

		MLibThreshold(void);

		bool	SaveBlob(QIODevice *f);
		bool	LoadBlob(QIODevice *f);
	}Broad,Narrow;

	float	VarietySigma;
	DWORD	MultiSpotDot;
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//密集多点
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;		

	WORD	AdjustBlack;		//輝度補正の下限幅
    WORD	AdjustWhite;		//輝度補正の上限幅
	WORD	AdjustContribute;	//補正の寄与度
	WORD	AreaSearchX;     //Ｘ方向領域探索ドット数
	WORD	AreaSearchY;     //Ｙ方向領域探索ドット数
    WORD	SelfSearch;     //自己探索ドット数
	bool	PreciseSearch;
	bool	Clusterize;		//塊判定
	bool	EnableT2M;
	bool	EnableM2T;
	bool	UseMaster2;
	WORD	ExpandToSubBlock;
	WORD	MaxAreaSearch;	//最大領域探索ドット数
    WORD	MaxSelfSearch;	//最大自己探索ドット数

	bool	ScratchEnable;
	float	ScratchStartDirection;
	float	ScratchRotationAngle ;	//Degree
	float	ScratchDiff;
	float	ScratchVariety;
	WORD	ScratchDetectLevelL;
	WORD	ScratchDetectLevelH;
	WORD	ScratchMaxWidth;
	bool	ScratchUseMaster;
	float	ScratchVOffset;

	bool	RedCheckMode;
	WORD	RedHighRate;	//G,Bに比べてRの輝度値の増値割合(%)
	BYTE	RedMinBrightness;
	BYTE	RedGBMerginRate;
	BYTE	RedGBMerginOffset;
	BYTE	RedShrink;
	DWORD	RedOKDot;

	bool	HsvCheckMode;
	bool	HsvFixedColorMode;
	WORD	HsvH;
	BYTE	HsvS,HsvV;
	WORD	HsvPHL,HsvPHH;	//パーセント値
	BYTE	HsvPSL,HsvPSH;
	BYTE	HsvPVL,HsvPVH;
	WORD	HsvDHL,HsvDHH;	//直接値
	BYTE	HsvDSL,HsvDSH;
	BYTE	HsvDVL,HsvDVH;
	DWORD	HsvOKDot;
	DWORD	HsvOKLength;	//ＯＫ距離

	BYTE	UseOneLayer;
	BYTE	MatchBrightnessByLayerH;
	BYTE	MatchBrightnessByLayerL;
	DWORD	MasterNoOriginCode;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OKバラツキ偏差値
	float	VariationGL,VariationGH;	//G-OKバラツキ偏差値
	float	VariationBL,VariationBH;	//B-OKバラツキ偏差値
	DWORD	VariationAdaptMinSize;		//最小適用領域サイズ
	float	VariationMultiplyMaster;	//マスター画像、バラツキ画像からの偏差しきい値計算時の係数
	bool	VariationDifMaster;			//マスター画像の差分をバラつき偏差で処理
	bool	VariationAndLogic;			//他の検査してNGになった部分だけをバラつき判定する
	float	VariationSubMasterVari;		//マスター画像のバラつき係数を引き算する係数

	bool	PitMode;
	WORD	PitBrightWidthRL;	//微小検出	暗側輝度幅
	WORD	PitBrightWidthRH;	//微小検出	明側輝度幅
	WORD	PitBrightWidthGL;	//微小検出	暗側輝度幅
	WORD	PitBrightWidthGH;	//微小検出	明側輝度幅
	WORD	PitBrightWidthBL;	//微小検出	暗側輝度幅
	WORD	PitBrightWidthBH;	//微小検出	明側輝度幅

	bool	LineMode;
	WORD	LineOKMinLength;
	WORD	LineMaxWidth;
	WORD	LineMinDensityPercent;
	WORD	LineMinCluster;		//線の最小塊面積

#pragma	pack(pop)
	IntList	SubtractLibID;

public:

	DotColorMatchingLibrary(int LibType,LayersBase *Base);
	virtual	~DotColorMatchingLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DotColorMatchingLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer *ImageList[]
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeDotColorMatching(
				ImageBuffer *IBuff[]
				,BYTE **CurrentMap,BYTE **OcupyMap ,BYTE **SubBlockMap
				,int Page
				,int XByte ,int XLen,int YLen
				,NPListPack<AlgorithmItemPI> &TmpDotColorMatchingData);

	void	MakeDotColorMatchingItems(BYTE **CurrentMap
									 ,int Page
									 ,int XByte ,int XLen,int YLen
									 ,PureFlexAreaListContainer &AreaList);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);

	void	MakeDotColorMatchingInner(
				ImageBuffer *IBuff[]
				,BYTE **CurrentMap,BYTE **OcupyMap
				,int Page
				,int XByte ,int XLen,int YLen
				,NPListPack<AlgorithmItemPI> &TmpDotColorMatchingData);

	void	BindBlockInner(
				 PureFlexAreaListContainer &TmpDotColorMatchingData);

	PureFlexAreaList *MakeEvenArea(
								 FlexArea &a,ImageBuffer *IBuff[] ,int LayerNumb
								,double AvrR,double AvrG,double AvrB);
};

class	DotColorMatchingLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DotColorMatchingLibraryContainer(LayersBase *base);
	virtual	~DotColorMatchingLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeDotColorMatchingInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DotColorMatching Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DotColorMatchingLibrary(GetLibType(),GetLayersBase());	}

};

#endif