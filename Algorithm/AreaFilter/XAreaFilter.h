/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilter.h
** Author : YYYYYYYYYY
*******************************************************************************/


#ifndef XAREAFILTER_H
#define XAREAFILTER_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"

#define	DefLibTypeAreaFilter	8
#define	AreaFilterVersion	1

class	AreaFilterItem;
class	RotatedXYBuffer;

class	AreaFilterLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	enum	_FilterType{
		_PatternInverted		=0
		,_VerticalEmphasize		=1
		,_LineEmphasize			=2
		,_LargeEnflat			=3
		,_HorizontalEmphasize	=4
		,_Differential			=5
	}FilterType;

	int32	BlockSize;
	int32	EmphasizeRate;
	double	UpperBlocksPercentageByVariance;
	double	SliceUpperBlocksByValue;
	bool	BoolSliceUpperBlocksByValue;
	int32	SkipTheta;
	int32	SkipKy;
	int32	UnifiedLineNumb;
	bool	MoveByAlignment;
	int32	SkipDot;
	int32	GeneratedBrightness;
	double	AdoptedRate;
	int32	BlockHeight;
	int32	ShrinkRate;

	AreaFilterLibrary(int LibType,LayersBase *Base);
	virtual	~AreaFilterLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AreaFilterLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	AreaFilterLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AreaFilterLibraryContainer(LayersBase *base);
	virtual	~AreaFilterLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAreaFilter;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AreaFilter Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AreaFilterLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------

class	AreaFilterItemPatternInverted;
class	AreaFilterThresholdPatternInverted : public AlgorithmThreshold
{
public:
	AreaFilterThresholdPatternInverted(AreaFilterItemPatternInverted *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	AreaFilterItem : public AlgorithmItemPLI
{
public:

	AreaFilterItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItem();	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return NULL;	}
	void	CopyThreshold(AreaFilterItem &src);
	void	CopyThresholdOnly(AreaFilterItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	bool    Save(QIODevice *f)						override{	return true;	}
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override{	return true;	}
};

class	AreaFilterItemPatternInverted : public AreaFilterItem
{
public:
	FlexAreaImage	ImagePattern;

	AreaFilterItemPatternInverted(void);
	~AreaFilterItemPatternInverted(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemPatternInverted();	}
	const	AreaFilterThresholdPatternInverted	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdPatternInverted *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdPatternInverted			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdPatternInverted *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaFilterThresholdPatternInverted(this);	}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	int32	GetItemClassType(void)	override	{		return 0;		}
};

class	AreaFilterItemVerticalEmphasize;
class	AreaFilterThresholdVerticalEmphasize : public AlgorithmThreshold
{
public:
	AreaFilterThresholdVerticalEmphasize(AreaFilterItemVerticalEmphasize *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	AreaFilterItemVerticalEmphasize : public AreaFilterItem
{
public:

	AreaFilterItemVerticalEmphasize(void);
	~AreaFilterItemVerticalEmphasize(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemVerticalEmphasize();	}
	const	AreaFilterThresholdVerticalEmphasize	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdVerticalEmphasize *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdVerticalEmphasize			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdVerticalEmphasize *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaFilterThresholdVerticalEmphasize(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 1;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
};

//-------------------------------------------------------

class AreaFilterItemLineEmphasize;
class	AreaFilterThresholdLineEmphasize : public AlgorithmThreshold
{
public:
	AreaFilterThresholdLineEmphasize(AreaFilterItemLineEmphasize *parent);

	int32	BlockSize;
	int32	EmphasizeRate;
	double	UpperBlocksPercentageByVariance;
	double	SliceUpperBlocksByValue;
	bool	BoolSliceUpperBlocksByValue;
	int32	SkipTheta;
	int32	SkipKy;
	int32	UnifiedLineNumb;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void ToLibrary(AlgorithmLibrary *dest)		override;
};


class BlockInfo
{
public:
	double	brightnessvariance;	//‹P“x‚Ì•ªŽU
	double	brightnessvariance2;	//‹P“x‚Ì•ªŽU
	double	DifVar;					//‚S•ªŠ„—Ìˆæ‚Ì•ªŽU‚Ì·
	int		lightsidengdotcount;	//‹–—e”ÍˆÍŠO‚Ì–¾‚é‚¢‘¤‚Ìƒhƒbƒg”
	unsigned int xn;				//”Ô†
	unsigned int yn;
	unsigned int X1;				//BlockSize‚Ì¶ãÀ•W
	unsigned int Y1;
	unsigned int X2;				//BlockSize‚Ì¶ãÀ•W
	unsigned int Y2;
	bool	Effective;
	bool	isinsidemasking;
	int		EffectivePixels;	//—LŒø‚ÈƒsƒNƒZƒ‹”
	double	AverageBlockBrightness;
	double *Avrbuf;
	double *TmpAvrbuf;

	BlockInfo(void);
	~BlockInfo(void);

	void	CheckOnMask( const BYTE **MaskingMap,int XByte ,int YLen
						,BYTE **DynamicMaskingMap
						,int BlockSize);

	void	CalcBrightnessDistribution( const BYTE **MaskingMap,int XByte ,int YLen
										,BYTE **DynamicMaskingMap
										,ImageBuffer &RefTargetBuff);
	double	calcSumSquares(int Theta, double *Avrbuf, int SumbufNum
							 ,int OffsetX, int OffsetY, int ***dx, int ***dy
							 , ImageBuffer *wTargetBuff
							 ,int SkipKy);
	double calcSumSquares(int Theta, double *Avrbuf, int SumbufNum
							 ,int OffsetX, int OffsetY, int ***dx, int ***dy
							 , ImageBuffer *wTargetBuff
							 ,const BYTE **MaskingMap,BYTE **DynamicMaskingMap
							 ,int SkipKy);
	void	CalcAngle(const BYTE **MaskingMap,int XByte ,int YLen
							,BYTE **DynamicMaskingMap
							,ImageBuffer &DstBuff
							,ImageBuffer &SrcBuff
							,int SkipTheta
							,int SumbufNum
							,double EmphasizeRate
							,int SkipKy
							,RotatedXYBuffer &RotatedXY);
	void	MakeBrightTable( const BYTE **MaskingMap,int XByte ,int YLen
							,BYTE **DynamicMaskingMap
							,ImageBuffer &RefTargetBuff
							,int PixTable[256]
							,int Lx1,int Ly1,int Lx2,int Ly2);
	void	MakeAvrVar(int PixTable[],double &Avr,double &Var);
};

int CompareBlockBrightnessVariances(const void *a, const void *b);
int CompareLightSideNGDotCount(const void *a, const void *b);

class	RotatedXYBuffer
{
public:
	RotatedXYBuffer(void);
	~RotatedXYBuffer(void);
	void	Prepare(int rotatedblocksize);
	void	Release(void);
	void	Allocate(void);
	void	Calc(void);

	int***	GetDestXPointer(void){return DestX;};
	int***	GetDestYPointer(void){return DestY;};
	double	GetSin(int theta){if((theta>=180) || (theta<0)) return 0.0; return SinTable[theta];};
	double	GetCos(int theta){if((theta>=180) || (theta<0)) return 0.0; return CosTable[theta];};

	int	RotatedBlockSize;
	int	GetRotatedBlockSize(void){return RotatedBlockSize;};
	void SetRotatedBlockSize(int size){this->RotatedBlockSize=size;};

private:
	int***	DestX;
	int***	DestY;

	double	SinTable[180];
	double	CosTable[180];
	void	CalcSinAndCos(void);
};

class	AreaFilterItemLineEmphasize : public AreaFilterItem
{
public:
	AreaFilterItemLineEmphasize(void);
	~AreaFilterItemLineEmphasize(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemLineEmphasize();	}
	const	AreaFilterThresholdLineEmphasize	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdLineEmphasize *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdLineEmphasize			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdLineEmphasize *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AreaFilterThresholdLineEmphasize(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 2;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecutePreProcessing       (int ExeID ,int ThreadNo, ResultInItemRoot *Res)	override;
	virtual ExeResult	ExecuteInitialAfterEdit    (int ExeID ,int ThresdNo, ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;


protected:
	
	ImageBuffer *wTargetBuff;

private:
	BlockInfo *BlockInfos;
	int LBlockNumb;
	BlockInfo **BlockInfoIndexes;

	int LBlockHNumb;
	int LBlockVNumb;

	int	GetRotatedBlockSize(int blocksize);
	RotatedXYBuffer	RotatedXY;

	BYTE	**GetDynamicMaskingMap(void);

	void	AllocateBuffers(void);
	void	ReleaseBuffers(void);
};

//--------------------------------------------------------------------------------------------------------
class	AreaFilterItemLineLargeEnflat;

class	AreaFilterThresholdLargeEnflat : public AlgorithmThreshold
{
public:
	AreaFilterThresholdLargeEnflat(AreaFilterItemLineLargeEnflat *parent);

	int32	BlockSize		;
	bool	MoveByAlignment	;
	int32	SkipDot	;
	int32	GeneratedBrightness;
	double	AdoptedRate;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void ToLibrary(AlgorithmLibrary *dest)		override;
};

class	AreaFilterItemLineLargeEnflat : public AreaFilterItem
{
	AlignmentPacket2D	*AVector;
	int		MasterBrightness;
	FlexArea	ClippedArea;

	int		XLen;
	int		YLen;
	BYTE	**TmpBuff;	
	int		BuffX,BuffY;

public:
	AreaFilterItemLineLargeEnflat(void);
	~AreaFilterItemLineLargeEnflat(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemLineLargeEnflat();	}
	const	AreaFilterThresholdLargeEnflat	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdLargeEnflat *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdLargeEnflat			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdLargeEnflat *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaFilterThresholdLargeEnflat(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 3;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecutePreProcessing       (int ExeID ,int ThreadNo, ResultInItemRoot *Res)	override;
	virtual ExeResult	ExecuteInitialAfterEdit    (int ExeID ,int ThresdNo, ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

protected:

private:
	int	MakeAverage(int	MinC,int MaxC ,int BTable[256] ,int TotalCount);
	int	MakeAverage(int	MinC,int MaxC ,BYTE BTable[256] ,int TotalCount);
	int	MakeAverage(int	MinC,int MaxC ,WORD BTable[256] ,int TotalCount);
};

//--------------------------------------------------------------------------------------------------------
class	AreaFilterItemHorizontalEmphasize;

class	AreaFilterThresholdHorizontalEmphasize : public AlgorithmThreshold
{
public:
	AreaFilterThresholdHorizontalEmphasize(AreaFilterItemHorizontalEmphasize *parent);

	int32	BlockSize		;
	int32	SkipDot			;
	int32	EmphasizeRate	;
	bool	MoveByAlignment	;
	int32	BlockHeight		;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void ToLibrary(AlgorithmLibrary *dest)		override;
};

class	AreaFilterItemHorizontalEmphasize : public AreaFilterItem
{
	AlignmentPacket2D	*AVector;
	int		MasterBrightness;
	FlexArea	ClippedArea;

	int		XLen;
	int		YLen;
	BYTE	**TmpBuff;	
	int		BuffX,BuffY;

public:
	AreaFilterItemHorizontalEmphasize(void);
	~AreaFilterItemHorizontalEmphasize(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemHorizontalEmphasize();	}
	const	AreaFilterThresholdHorizontalEmphasize	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdHorizontalEmphasize *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdHorizontalEmphasize			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdHorizontalEmphasize *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaFilterThresholdHorizontalEmphasize(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 4;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecutePreProcessing       (int ExeID,int ThreadNo, ResultInItemRoot *Res)	override;
	virtual ExeResult	ExecuteInitialAfterEdit    (int ExeID,int ThresdNo, ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

protected:

private:

};
//--------------------------------------------------------------------------------------------------------
class	AreaFilterItemDifferential;

class	AreaFilterThresholdDifferential : public AlgorithmThreshold
{
public:
	AreaFilterThresholdDifferential(AreaFilterItemDifferential *parent);

	int32	BlockSize		;
	int32	SkipDot			;
	int32	EmphasizeRate	;
	bool	MoveByAlignment	;
	int32	ShrinkRate		;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void ToLibrary(AlgorithmLibrary *dest)		override;
};

class	AreaFilterItemDifferential : public AreaFilterItem
{
	AlignmentPacket2D	*AVector;
	int		MasterBrightness;
	FlexArea	ClippedArea;

	int		XLen;
	int		YLen;
	BYTE	**TmpBuff;	
	int		BuffX,BuffY;

	int		FilterSize;
	int		**FilterDim;

public:
	AreaFilterItemDifferential(void);
	~AreaFilterItemDifferential(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaFilterItemDifferential();	}
	const	AreaFilterThresholdDifferential	*GetThresholdR(LayersBase *base=NULL){	return (const AreaFilterThresholdDifferential *)GetThresholdBaseReadable(base);	}
	AreaFilterThresholdDifferential			*GetThresholdW(LayersBase *base=NULL){	return (AreaFilterThresholdDifferential *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AreaFilterThresholdDifferential(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 4;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteStartByInspection	(int ExeID ,int ThreadNo, ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID ,int ThreadNo, ResultInItemRoot *Res)	override;
	virtual ExeResult	ExecuteInitialAfterEdit		(int ExeID ,int ThresdNo, ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

protected:

private:

};

//--------------------------------------------------------------------------------------------------------
class   AreaFilterInLayer : public AlgorithmInLayerPLI
{
public:
	AreaFilterInLayer(AlgorithmInPageRoot *parent):AlgorithmInLayerPLI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override;
	virtual	AlgorithmItemRoot		*CreateItem(AreaFilterLibrary &Lib);
	//void	AddMask(MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
};


class   AreaFilterInPage : public AlgorithmInPagePLI
{
public:
	AreaFilterInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new AreaFilterInLayer(parent);	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	AreaFilterBase : public AlgorithmBase
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;
	int32	TransparentLevel;
	bool	CopyImageInLayer1;	//Copy Layer0 -> Layer1	before ExecuteAlignment
	bool	CopyImageInLayer2;	//Copy Layer0 -> Layer2 before ExecuteAlignment

	AreaFilterBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override	{	return new AreaFilterInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	QString	GetDataText(void)			override{	return QString("AreaFilter");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAreaFilter.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	AvailableShrinkItem(void)		const	override	{	return true;	}
	virtual	bool	AvailableChangeLibrary(void)	const	override	{	return false;	}

};
//==================================================================================
//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	AreaFilterReqChangeShiftCommand					9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
//===================================================================================

class	AreaFilterDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;

	AreaFilterDrawAttr(void){}
	AreaFilterDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	AreaFilterDrawAttr(  QColor ncol ,int ntranparentLevel
						,QColor scol ,int stranparentLevel
						,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		AreaColor			=ncol;	
		NegAreaColor		=acol;	
		NegAreaColorSelected=scol;	
		AreaColor			.setAlpha(ntranparentLevel);
		NegAreaColor		.setAlpha(atranparentLevel);
		NegAreaColorSelected.setAlpha(stranparentLevel);
	}
};

//===================================================================================

class	CmdGetAreaFilterLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaFilterLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaFilterLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAreaFilterLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaFilterLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaFilterLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAreaFilterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAreaFilterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAreaFilterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAreaFilterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAreaFilterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAreaFilterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAreaFilterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAreaFilterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAreaFilterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAreaFilterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdLoadAreaFilterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAreaFilterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAreaFilterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAreaFilterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAreaFilterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAreaFilterDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	}Mode;
	enum	DrawType{
		_Area
		,_Edge
		,_Inside
	}DType;

	CmdAreaFilterDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaFilterDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AreaFilterImagePanel;
class	CmdAreaFilterDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AreaFilterImagePanel	*ImagePanelPoint;

	CmdAreaFilterDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaFilterDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAreaFilterItemPacket: public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			SelectedLibID;
	int			LocalPage;
	IntList		LayerList;

	CmdAddAreaFilterItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAreaFilterItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif