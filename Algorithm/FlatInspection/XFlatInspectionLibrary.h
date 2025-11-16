#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>

//========================================================================================

#define	DefLibTypeFlatInspection	65

class	FlatInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
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
    int32		MinFlatInspectionSize;
    int32		MaxFlatInspectionSize;
    int32		MinFlatInspectionDots;
    int32		MaxFlatInspectionDots;
    int32		LimitFlatInspectionSize;
	int32		OverlappedLength;

	WORD		NoiseSize;			//孤立点削除
	WORD		NoiseSizePinHole;	//ピンホール削除
#pragma	pack(pop)

	struct MLibThreshold
	{
		DWORD	OKDot;			//ＯＫドット数
		DWORD	OKLength;		//ＯＫ距離

		short	RThrOffsetL;	//しきい値への直接加算値	(-100～100)
		short	RThrOffsetH;
		short	GThrOffsetL;
		short	GThrOffsetH;
		short	BThrOffsetL;
		short	BThrOffsetH;

		MLibThreshold(void);

		bool	SaveBlob(QIODevice *f);
		bool	LoadBlob(QIODevice *f);

	}Broad,Narrow;

    short	SpaceToOutline;

	DWORD	MultiSpotDot;	//単多点
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//密集多点
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;
	bool	UseBackGround;

	WORD	AdjustBlack;		//輝度補正の下限幅
    WORD	AdjustWhite;		//輝度補正の上限幅
	WORD	AreaSearchX;		//Ｘ方向領域探索ドット数
	WORD	AreaSearchY;		//Ｙ方向領域探索ドット数
	WORD	SelfSearch;			//自己探索ドット数
	bool	EnableInspection;
	WORD	MaxAreaSearch;	//最大領域探索ドット数
    WORD	MaxSelfSearch;	//最大自己探索ドット数


	bool	RedCheckMode;
	WORD	RedHighRate;	//G,Bに比べてRの輝度値の増値割合(%)
	BYTE	RedMinBrightness;
	BYTE	RedGBMerginRate;
	BYTE	RedGBMerginOffset;
	BYTE	RedShrink;
	DWORD	RedOKDot;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OKバラツキ偏差値
	float	VariationGL,VariationGH;	//G-OKバラツキ偏差値
	float	VariationBL,VariationBH;	//B-OKバラツキ偏差値
	DWORD	VariationAdaptMinSize;		//最小適用領域サイズ
	float	VariationMultiplyMaster;	//マスター画像、バラツキ画像からの偏差しきい値計算時の係数
	bool	VariationDifMaster;			//マスター画像の差分をバラつき偏差で処理
	bool	VariationAndLogic;			//他の検査してNGになった部分だけをバラつき判定する
	float	VariationSubMasterVari;		//マスター画像のバラつき係数を引き算する係数

	bool	LineMode;
	WORD	LineOKMinLength;
	WORD	LineMaxWidth;
	WORD	LineMinDensityPercent;
	WORD	LineMinCluster;		//線の最小塊面積
public:

	FlatInspectionLibrary(int LibType,LayersBase *Base);
	virtual	~FlatInspectionLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	FlatInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

private:
	bool	LoadBlobNew(QIODevice *f);
	bool	LoadBlobOld(QIODevice *f);
};

class	FlatInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	FlatInspectionLibraryContainer(LayersBase *base);
	virtual	~FlatInspectionLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeFlatInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "FlatInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new FlatInspectionLibrary(GetLibType(),GetLayersBase());	}

};
