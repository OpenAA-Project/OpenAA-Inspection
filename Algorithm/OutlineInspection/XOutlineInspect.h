/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\OutlineInspection\XOutlineInspect.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#if	!defined(XOUTLINEINSPECT_H)
#define	XOUTLINEINSPECT_H

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
#include "XOutlineLibrary.h"
#include "XStandardCommand.h"

class	ImageBuffer;
class	OutlineInPage;
class   OutlineInLayer;
class	OutlineBase;
class	OutlineItem;

#define	MAXGENTENOUTLINEDOTNUMB	10000
#define MaxPadSeparations   10


#define	OutlineInspectionVersion	6


//===============================================================================================
class	OutlineThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	OutlineThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	OutlineThreshold :public AlgorithmThreshold
{
public: 
	bool		MatchSlideOnMaster;

	//検査時のデータ
	RelativeThresholdColorBox	InsideNOKColor;		//内側安定域の狭域輝度範囲
	RelativeThresholdColorBox	InsideNTrOKColor;	//内側遷移域の狭域輝度範囲
	WORD						InsideNOKDot;
	WORD						InsideNMergin;
	RelativeThresholdColorBox	OutsideNOKColor;	//外側安定域の狭域輝度範囲
	RelativeThresholdColorBox	OutsideNTrOKColor;	//外側遷移域の狭域輝度範囲
	WORD						OutsideNOKDot;
	WORD						OutsideNMergin;

	RelativeThresholdColorBox	InsideBOKColor;		//内側安定域の広域輝度範囲
	RelativeThresholdColorBox	InsideBTrOKColor;	//内側遷移域の広域輝度範囲
	WORD						InsideBOKDot;
	WORD						InsideBMergin;
	RelativeThresholdColorBox	OutsideBOKColor;	//外側安定域の広域輝度範囲
	RelativeThresholdColorBox	OutsideBTrOKColor;	//外側遷移域の広域輝度範囲
	WORD						OutsideBOKDot;
	WORD						OutsideBMergin;

	bool		EffectiveNInside;		//検査結果出力　狭域　内側検査
	bool		EffectiveNOutside;		//検査結果出力　狭域　外側検査
	bool		EffectiveBInside;		//検査結果出力　広域　内側検査
	bool		EffectiveBOutside;		//検査結果出力　広域　外側検査

	WORD		SelfSearch;			//検査時　探索距離
	bool		AdjustMode;			//平均輝度補正するか
	WORD		AdjustLimitLInside;
	WORD		AdjustLimitHInside;
	WORD		AdjustLimitLOutside;
	WORD		AdjustLimitHOutside;
	bool		DiffMode;			//差分モード
	bool		AbsMode;


	OutlineThreshold(AlgorithmItemRoot *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)						override;
    virtual	bool	Load(QIODevice *f)						override;
    virtual	int		GetSize(void)				const		override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)		override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	OutlineItem : public AlgorithmItemPLI
{
public:
	int		MatchingDotCount;
	int		MatchingLayer;
	double	MasterAdd;
	double	MasterAdd2;
	int		MoveXForSelf;
	int		MoveYForSelf;

	QRgb	InsideCenterColorOnMaster;
	QRgb	OutsideCenterColorOnMaster;

	class	AlgoCalcStruct
	{
		OutlineItem	*Parent;
	public:
		int			CenterColorOnMaster;
		int			TrCenterColorOnMaster;
		FlexArea	Area;		//安定域
		FlexArea	TrArea;		//遷移域
		BYTE		**BMap;
		WORD		XByte;
		WORD		YLen;

		AlgoCalcStruct(OutlineItem	*parent);

		void	Initial(void);
		void	Release(void);
		void	ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);
		void	ExecuteStartByInspection(void);
		void	MoveTo(int dx, int dy);

		int		CalcDecision( ImageBuffer *MasterImageList
							, ImageBuffer *TargetImageList
							,int mx ,int my ,int hx ,int hy
							,const RelativeThresholdColorBox &OKColor 
							,const RelativeThresholdColorBox &TrOKColor 
							,int OKDotCount
							,int &Sum ,WORD Mode
							,ResultPosListContainer &PosList,bool EnabledResult
							,bool &Ok
							,int &MaxNGDot
							,int AdjustLimitL ,int AdjustLimitH);
		OutlineItem	*GetParent(void){	return Parent;	}
		AlgoCalcStruct	&operator=(AlgoCalcStruct &src);

		void	CutArea(FlexArea &localArea);
	};


public:
	AlgoCalcStruct	InsideAlgo;		//内側
	AlgoCalcStruct	OutsideAlgo;	//外側
	FlexArea		MatchingArea;
	int				ClusterID;

	int				ResultSearchX;	//個別の移動量
	int				ResultSearchY;
	int				ResultDotSumInside;
	int				ResultDotSumOutside;
	int				MaxNGDotInsideN;
	int				MaxNGDotOutsideN;
	int				MaxNGDotInsideB;
	int				MaxNGDotOutsideB;


	AlignmentPacket2D	*AVector;


	OutlineItem(void);
	~OutlineItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new OutlineItem();	}
	const OutlineThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const OutlineThreshold *)GetThresholdBaseReadable(base);	}
	OutlineThreshold		*GetThresholdW(LayersBase *base=NULL){	return (OutlineThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new OutlineThreshold(this);	} 
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID, int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID, int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID, int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(OutlineItem &src);

	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;

private:
	void	MatchingFit(int mx,int my);
	double	MatchingCalcFull(ImageBuffer *MasterBuff ,ImageBuffer *TargetBuff
							,int mx,int my);
	void	CalcDecision(ResultInItemRoot *Res
								 ,int mx ,int my);
	bool	CalcSelf(void);
	bool	IsUpdated(int iNNGInsideCount ,int iNNGOutsideCount
					 ,int iBNGInsideCount ,int iBNGOutsideCount);
	bool	IsTotalOk(bool iOkNInside ,bool iOkNOutside
					 ,bool iOkBInside ,bool iOkBOutside);
	bool	IsCompleteOk(bool iOkNInside ,bool iOkNOutside
						,bool iOkBInside ,bool iOkBOutside);

	bool	InFunc(int kx ,int ky,int mx ,int my
							,bool	&OkNInside
							,bool	&OkBInside
							,bool	&OkNOutside
							,bool	&OkBOutside
							,int	&MinD
							,int	&MinEx
							,int	&MinEy
							,int	&MinED
							,int	&MinNNGInsideCount
							,int	&MinBNGInsideCount
							,int	&MinNNGOutsideCount
							,int	&MinBNGOutsideCount
							,ImageBuffer *MasterImageList
							,ImageBuffer *TargetImageList
							,ResultPosListContainer	&NGList);

	void	OptimizeForMaster(double NExtendRate,double BExtendRate);
	void	GetTopBottom(int BrList[] ,int &ColL ,int &ColH);
	OutlineInspectLibNGTypeItem	*MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer);
};


//===============================================================================================
class	CalcInfoClass;

class   OutlineInLayer : public AlgorithmInLayerPLI
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
public:
	OutlineInLayer(AlgorithmInPageRoot *parent);
	~OutlineInLayer(void);

	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			OutlineItem	*a=new OutlineItem();
			a->SetParent(this);
			return a;
		}

	bool	CreateBlocks(int LibID);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	PickupTest(OutlineInspectLibrary &Lib);
	void	WashAreas(OutlineInspectLibrary *ALib
				   ,BYTE **BMap ,int XByte ,int YLen
				   ,PureFlexAreaListContainer &ResPack);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

private:
	void	CreateBlockItem(OutlineInspectLibrary *ALib ,FlexArea *Area 
							,const BYTE **MaskBitmap,BYTE **CutlineBitmap
							,int ClusterID);
	BYTE	**GetCutLineMaskBitmap(void);

	void	CalcOnePath(XYClassArea *Path,FlexArea *Area 
								   ,int Mx,int My
								   ,OutlineInspectLibrary *ALib
								   ,const BYTE **MaskBitmap
								   ,const BYTE **ShrinkedMaskBitmap
								   ,int tShrinkDot
								   ,int ClusterID);

	void	CalcOneChopped(XYClassArea *Path,FlexArea *Area 
									,int Mx,int My
									,OutlineInspectLibrary *ALib
									,const BYTE **MaskBitmap
									,int ClusterID
									,CalcInfoClass &CInfo);
	void	SetVectorForOnePath(XYClassArea *sa);
	void	Pickup(OutlineInspectLibrary *ALib
				   ,BYTE **BMap ,int XByte ,int YLen
				   ,const BYTE **MaskBitmap);

	void	CreatePickupBmpBuff(void);
	bool	ChoppedAreaIsEnabled(XYClassArea *Path ,int Mx,int My,const BYTE **MaskBitmap,int tShrinkDot);
};

class   OutlineInPage : public AlgorithmInPagePLI
{
public:
	OutlineInPage(AlgorithmBase *parent);
	~OutlineInPage(void){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new OutlineInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
};

class	OutlineBase : public AlgorithmBase
{
public:
	QColor		ColorPickup		;
	QColor		BlockNormal		;
	QColor		BlockSelected	;
	QColor		BlockActive		;
	int			OmitZoneDot		;

	OutlineBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return(new OutlineInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigOutline.dat");	}
	virtual	QString	GetDataText(void)			override{	return QString("OutlineInspect");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//===============================================================================================
class	OutlineThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	bool		MatchSlideOnMaster;
	bool		DiffMode;			//差分モード

	RelativeThresholdColorBox	InsideNOKColor;		//内側安定域の輝度範囲
	RelativeThresholdColorBox	InsideNTrOKColor;	//内側遷移域の輝度範囲
	WORD						InsideNOKDot;
	WORD						InsideNMergin;
	RelativeThresholdColorBox	OutsideNOKColor;	//外側安定域の輝度範囲
	RelativeThresholdColorBox	OutsideNTrOKColor;	//外側遷移域の輝度範囲
	WORD						OutsideNOKDot;
	WORD						OutsideNMergin;

	RelativeThresholdColorBox	InsideBOKColor;		//内側安定域の輝度範囲
	RelativeThresholdColorBox	InsideBTrOKColor;	//内側遷移域の輝度範囲
	WORD						InsideBOKDot;
	WORD						InsideBMergin;
	RelativeThresholdColorBox	OutsideBOKColor;	//外側安定域の輝度範囲
	RelativeThresholdColorBox	OutsideBTrOKColor;	//外側遷移域の輝度範囲
	WORD						OutsideBOKDot;
	WORD						OutsideBMergin;

	bool		EffectiveNInside;		//検査結果出力　狭域　内側検査
	bool		EffectiveNOutside;		//検査結果出力　狭域　外側検査
	bool		EffectiveBInside;		//検査結果出力　広域　内側検査
	bool		EffectiveBOutside;		//検査結果出力　広域　外側検査

	WORD		SelfSearch;		/*	検査時　探索距離	*/
	bool		AdjustMode;
	WORD		AdjustLimitLInside;
	WORD		AdjustLimitHInside;
	WORD		AdjustLimitLOutside;
	WORD		AdjustLimitHOutside;
	bool		AbsMode;

	OutlineThresholdSend(void);

	void	ConstructList(OutlineThresholdReq *reqPacket,OutlineBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	OutlineReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;	
	OutlineItem	Threshold;

	OutlineReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	OutlineSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInInsideN;
	int		NGDotInOutsideN;
	int		NGDotInInsideB;
	int		NGDotInOutsideB;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;

	OutlineSendTryThreshold(void);

	void	ConstructList(OutlineReqTryThreshold *reqPacket,OutlineBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	OutlineHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	OutlineHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	OutlineHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMasterInside[256];
	int		ListMasterTrInside[256];
	int		ListMasterOutside[256];
	int		ListMasterTrOutside[256];
	int		ListTargetInside[256];
	int		ListTargetTrInside[256];
	int		ListTargetTrOutside[256];
	int		ListTargetOutside[256];

	int		InsideCenterColorOnMaster;
	int		InsideTrCenterColorOnMaster;
	int		OutsideCenterColorOnMaster;
	int		OutsideTrCenterColorOnMaster;
	int		InsideCenterColorOnTarget;
	int		InsideTrCenterColorOnTarget;
	int		OutsideCenterColorOnTarget;
	int		OutsideTrCenterColorOnTarget;

	OutlineHistogramListSend(void);

	void	ConstructList(OutlineHistogramListReq *reqPacket,OutlineBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	SetIndependentItemDataCommand_Optimize		10
#define	SetIndependentItemDataCommand_OptimizeAll	11

#define	OutlineHistogramListReqCommand			3
#define	OutlineHistogramListSendCommand			4
#define	OutlineReqThresholdReqCommand			5
#define	OutlineReqThresholdSendCommand			6
#define	OutlineReqTryThresholdCommand			7
#define	OutlineSendTryThresholdCommand			8
#define	OutlineReqChangeShiftCommand			9

//===============================================================================================

class	CmdGetOutlineLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetOutlineLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOutlineLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOutlineLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetOutlineLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOutlineLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempOutlineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearOutlineLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertOutlineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateOutlineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadOutlineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteOutlineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteOutlineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteOutlineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestOutlinePacket : public GUIDirectMessage
{
public:
	//OutlineInspectLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList	LayerList;

	CmdPickupTestOutlinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestOutlinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateOutlinePacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	IntList		LibList;
	int			Page;
	CmdGenerateOutlinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateOutlinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempOutlineItemPacket : public GUIDirectMessage
{
public:
	OutlineItem	*Point;
	CmdCreateTempOutlineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempOutlineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromOutlineItemPacket : public GUIDirectMessage
{
public:
	OutlineItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromOutlineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromOutlineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteOutlineItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteOutlineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteOutlineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadOutlineItemPacketFromByteArray : public GUIDirectMessage
{
public:
	OutlineItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadOutlineItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadOutlineItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedOutlineFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedOutlineFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedOutlineFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestOutlinePacket: public GUIDirectMessage
{
public:
	CmdClearTestOutlinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestOutlinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdOutlineInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<OutlineInfoList>	*OutlineInfos;
	CmdOutlineInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdOutlineInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOutlineFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	OutlineItem	*OutlineInfoOnMouse;

	CmdGetOutlineFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOutlineFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateOutlineItem: public GUIDirectMessage
{
public:
	OutlineItem	*OutlineBlock;
	CmdCreateOutlineItem(LayersBase *base):GUIDirectMessage(base){	OutlineBlock=NULL;	}
	CmdCreateOutlineItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	OutlineBlock=NULL;	}
};


#endif
