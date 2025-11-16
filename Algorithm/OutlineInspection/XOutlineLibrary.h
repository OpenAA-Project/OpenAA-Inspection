/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\OutlineInspection\XOutlineLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#if	!defined(XOUTLINELIBRARY_H)
#define	XOUTLINELIBRARY_H

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XDataInLayer.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XColorSpace.h"
#include "XPropertyOutlinePacket.h"

#define	DefLibTypeOutlineInspect	3

class	OutlineInspectLibNGTypeItem : public LibNGTypeItem
{
	AlgorithmLibraryContainer	*Lib;
public:
	ColorLogic	ColorZone;
	int			MinSize		,MaxSize;
	int			MinRoundRate,MaxRoundRate;

	OutlineInspectLibNGTypeItem(LayersBase *base,AlgorithmLibraryContainer *lib);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSetting(void);
};

class	OutlineInspectLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	//抽出時のデータ
	ColorLogic	PickupColor;
	WORD		TransDot;			//輪郭ばらつきドット
	WORD		InsideWidth;		//内側安定域の幅
	WORD		OutsideWidth;		//外側安定域の幅
	WORD		NoiseDot;
	WORD		ChoppedLength;
	WORD		Priority;
	int32		MinAreaDot;
	int32		MaxAreaDot;
	int32		MinAreaSize;
	int32		MaxAreaSize;
	bool		MatchSlideOnMaster;

	WORD		InsideTrWidth;		//内側遷移域の幅
	WORD		OutsideTrWidth;		//外側遷移域の幅

	//検査時のデータ
	RelativeThresholdColorBox	InsideNOKColor;		//狭域　内側安定域の狭域輝度範囲
	RelativeThresholdColorBox	InsideNTrOKColor;	//狭域　内側遷移域の狭域輝度範囲
	WORD						InsideNOKDot;
	WORD						InsideNMergin;
	RelativeThresholdColorBox	OutsideNOKColor;	//狭域　外側安定域の狭域輝度範囲
	RelativeThresholdColorBox	OutsideNTrOKColor;	//狭域　外側遷移域の狭域輝度範囲
	WORD						OutsideNOKDot;
	WORD						OutsideNMergin;

	RelativeThresholdColorBox	InsideBOKColor;		//広域　内側安定域の広域輝度範囲
	RelativeThresholdColorBox	InsideBTrOKColor;	//広域　内側遷移域の広域輝度範囲
	WORD						InsideBOKDot;
	WORD						InsideBMergin;
	RelativeThresholdColorBox	OutsideBOKColor;	//広域　外側安定域の広域輝度範囲
	RelativeThresholdColorBox	OutsideBTrOKColor;	//広域　外側遷移域の広域輝度範囲
	WORD						OutsideBOKDot;
	WORD						OutsideBMergin;

	bool		EffectiveNInside;		//検査結果出力　狭域　内側検査
	bool		EffectiveNOutside;		//検査結果出力　狭域　外側検査
	bool		EffectiveBInside;		//検査結果出力　広域　内側検査
	bool		EffectiveBOutside;		//検査結果出力　広域　外側検査


	WORD		SelfSearch;			//検査時　探索距離
	bool		AdjustMode;			//平均輝度補正するか
	WORD		AdjustLimitLInside;
	WORD		AdjustLimitHInside;		//差分モードのとき、平均輝度同士がこの範囲内にあるかどうかを検査する
	WORD		AdjustLimitLOutside;
	WORD		AdjustLimitHOutside;	//差分モードのとき、平均輝度同士がこの範囲内にあるかどうかを検査する
	bool		DiffMode;			//差分モード
	bool		AbsMode;			//絶対値モード

	OutlineInspectLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	OutlineInspectLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	OutlineInspectLibraryContainer : public AlgorithmLibraryContainer
{
public:
	OutlineInspectLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~OutlineInspectLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeOutlineInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Outline Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new OutlineInspectLibrary(GetLibType(),GetLayersBase());	}
	virtual	LibNGTypeItem	*CreateLibNGTypeItem(LayersBase *base)	override{	return new OutlineInspectLibNGTypeItem(base ,this);	}
};



#endif