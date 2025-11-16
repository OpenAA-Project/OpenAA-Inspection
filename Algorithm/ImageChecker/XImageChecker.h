/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageChecker\XImageChecker.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XImageChecker_h
#define XImageChecker_h

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XDirectComm.h"

#define	ImageCheckerVersion	1

class	ImageCheckerItem;
class	ImageCheckerInLayer;

struct	ImageCheckerRegData
{
	struct	ImageCheckerRegCalcCamX
	{
		double	StandardValue;
		double	LLimit;
		double	HLimit;
		double	Value;
		bool	Ok;
	}RegCalcCamX;
	struct	ImageCheckerRegCalcCamY
	{
		double	StandardValue;
		double	LLimit;
		double	HLimit;
		double	Value;
		bool	Ok;
	}RegCalcCamY;
	struct	ImageCheckerRegCalcCamZ
	{
		double	StandardValue;
		double	LLimit;
		double	HLimit;
		double	Value;
		double	Value2;
		bool	Ok;
	}RegCalcCamZ;
	struct	ImageCheckerRegCalcCamXTilt
	{
	}RegCalcCamXTilt;
	struct	ImageCheckerRegCalcCamYTilt
	{
	}RegCalcCamYTilt;
	struct	ImageCheckerRegCalcCamRot
	{
	}RegCalcCamRot;
	struct	ImageCheckerRegCalcStageFlat
	{
	}RegCalcStageFlat;
	struct	ImageCheckerRegCalcStageVerocity
	{
	}RegCalcStageVerocity;
	struct	ImageCheckerRegCalcStageVConst
	{
	}RegCalcStageVConst;
	struct	ImageCheckerRegCalcLightWhole
	{
		double	StandardValue;
		double	LLimit;
		double	HLimit;
		double	Value;
		bool	Ok;
	}RegCalcLightWhole[3];
	struct	ImageCheckerRegCalcLightLeftRight
	{
	}RegCalcLightLeftRight;

	struct	ImageCheckerRegCalcResolution
	{
		double	Resolution;
		double	PosY;
		double	DifResLow;
		double	DifResHigh;
		double	Value;
		bool	Ok;
	}RegCalcResolution;
	struct	ImageCheckerRegCalcSlide
	{
		double	XPos;
		double	YPos;
		double	DifPosLow;
		double	DifPosHigh;
		double	Value;
		double	Value2;
		bool	Ok;
	}RegCalcSlide;

	struct	ImageCheckerRegCalcIncline
	{
		double	VarTop;
		double	VarLeft;
		double	VarRight;
		double	VarBottom;
		double	DifLow;
		double	DifHigh;
		double	Value;
		double	Value2;
		double	Value3;
		double	Value4;
		double	Value5;
		double	Value6;
		bool	Ok;
	}RegCalcIncline;

	struct	ImageCheckerRegParamEntry
	{
		double	CamA;
		double	CamB;
		double	LightA;
		double	LightB;
		double	ValueCam;
		double	Value[3];
		bool	Ok;
	}RegParamEntry;
};

class	ImageCheckerThreshold : public AlgorithmThreshold
{
public:
	enum	_PointType{
		_ShiftXYMatching	=1
		,_ShiftXMatching	=2
		,_ShiftYMatching	=3
		,_CalcAvrVar		=4
		,_SweepY			=5
	}PointType;

	enum	__ImageCheckerRegMode{
		_ImageCheckerRegCalcCamX			=0
		,_ImageCheckerRegCalcCamY			=1
		,_ImageCheckerRegCalcCamZ			=2
		,_ImageCheckerRegCalcCamXTilt		=3
		,_ImageCheckerRegCalcCamYTilt		=4
		,_ImageCheckerRegCalcCamRot			=5
		,_ImageCheckerRegCalcStageFlat		=6
		,_ImageCheckerRegCalcStageVerocity	=7
		,_ImageCheckerRegCalcStageVConst	=8
		,_ImageCheckerRegCalcLightWhole		=9
		,_ImageCheckerRegCalcLightLeftRight	=10
		,_ImageCheckerRegCalcResolution		=11
		,_ImageCheckerRegCalcSlide			=12
		,_ImageCheckerRegCalcIncline		=13
		,_ImageCheckerRegCalcMatching		=20
	}ImageCheckerRegMode;

	ImageCheckerThreshold(ImageCheckerItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	FlexArea2DList : public NPList<FlexArea2DList>
{
public:
	PureFlexAreaListContainer	FlexAreas;

	FlexArea2DList(void);
};


class	ImageCheckerItem : public AlgorithmItemPLI
{
public:
	FlexArea	***DotMatrix;
	int			MaxXCount;		//校正計算のたびに再計算される
	int			MaxYCount;		//校正計算のたびに再計算される
	double		CenterPointForSlideX;	//最初に設定される
	double		CenterPointForSlideY;	//最初に設定される
	double		FFTList[10000];
	int			FFTListCount;
	int			MainPosX,MainPosY;

	ImageCheckerItem(void);
	~ImageCheckerItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ImageCheckerItem();	}
	const	ImageCheckerThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ImageCheckerThreshold *)GetThresholdBaseReadable(base);	}
	ImageCheckerThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ImageCheckerThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ImageCheckerThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	//virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	MakeDotMatrix(void);
	void	MakeFFTList(void);
	void	SetCenterPointForSlide(void);
	void	MatchingPosInLine(int &X ,int &Y);
private:
	int		GetPeak(int *BrList);
	int		GetSecondPeak(int *BrList,int Peak);
};

class	ImageCheckerRegCalcBase
{
protected:
	ImageCheckerInLayer	*LayerPoint;
	double	Result;
	double	Result2;
	double	Result3;
	double	Result4;
	double	Result5;
	double	Result6;
	bool	Ok;
public:
	ImageCheckerRegCalcBase(ImageCheckerInLayer *Ly){	LayerPoint=Ly;	}

	//virtual	bool	Execute(void){	return true;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	double	GetResult(void){	return Result;	}
	double	GetResult2(void){	return Result2;	}
	double	GetResult3(void){	return Result3;	}
	double	GetResult4(void){	return Result4;	}
	double	GetResult5(void){	return Result5;	}
	double	GetResult6(void){	return Result6;	}
	bool	GetOk(void)		{	return Ok;	}
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item)	=0;
	bool	IsMasterMode(void);
};

//　　Ｘ方向（横）ズレ
//		リファレンス基板上の基準位置の画像上の横方向ずれで判別
class	ImageCheckerRegCalcCamX : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*LeftPoint;
	double	StandardValue;
	double	LLimit;
	double	HLimit;

	ImageCheckerRegCalcCamX(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	Ｙ方向（前後）ズレ
//		リファレンス基板上の基準位置の画像上の縦方向ずれで判別
class	ImageCheckerRegCalcCamY : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*TopPoint;
	double	StandardValue;
	double	LLimit;
	double	HLimit;

	ImageCheckerRegCalcCamY(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	Ｚ方向（上下）ズレ
//		リファレンス基板上の中央部分の標準偏差で判別
class	ImageCheckerRegCalcCamZ : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*CenterPoint;
	double	StandardValue;
	double	LLimit;
	double	HLimit;

	ImageCheckerRegCalcCamZ(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(int ShiftX ,int ShiftY);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	横チルト
//		リファレンス基板上の左右の標準偏差の差異で判別
class	ImageCheckerRegCalcCamXTilt : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*LeftPoint;
	ImageCheckerItem	*RightPoint;
	double				LimitDot;

	ImageCheckerRegCalcCamXTilt(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	前後チルト
//		リファレンスの中央と左右の基準位置での標準偏差の差異で判別
class	ImageCheckerRegCalcCamYTilt : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*LeftPoint;
	ImageCheckerItem	*RightPoint;
	ImageCheckerItem	*CenterPoint;
	double				LimitDot;

	ImageCheckerRegCalcCamYTilt(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	カメラ回転
//		リファレンス基板上の左右の基準位置の上下ズレで判別
class	ImageCheckerRegCalcCamRot : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*LeftPoint;
	ImageCheckerItem	*RightPoint;
	double				LimitDot;

	ImageCheckerRegCalcCamRot(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	平行度
//		画像上の上下左右の４か所の標準偏差の差異で判別
class	ImageCheckerRegCalcStageFlat : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*TopPoint;
	ImageCheckerItem	*LeftPoint;
	ImageCheckerItem	*RightPoint;
	ImageCheckerItem	*BottomPoint;
	double				LimitDot;

	ImageCheckerRegCalcStageFlat(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	速度
//		リファレンス基板上の上下の基準位置の画像上の距離で判別
class	ImageCheckerRegCalcStageVerocity : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*TopPoint;
	ImageCheckerItem	*BottomPoint;
	double				LimitDot;

	ImageCheckerRegCalcStageVerocity(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	等速性
//		中央部分の、横方向標準偏差を上から下まで、計算枠をスイープした最大、最小
class	ImageCheckerRegCalcStageVConst : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*TopToBottomPoint;
	double				LimitDot;

	ImageCheckerRegCalcStageVConst(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	全体の照度
//		リファレンス全体の標準輝度
class	ImageCheckerRegCalcLightWhole : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*WholePoint;
	double	StandardValue;
	double	LLimit;
	double	HLimit;

	ImageCheckerRegCalcLightWhole(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

//	左右の照度
//		リファレンスの左右の基準位置での標準偏差の差異で判別
class	ImageCheckerRegCalcLightLeftRight : public ImageCheckerRegCalcBase
{
public:
	ImageCheckerItem	*LeftPoint;
	ImageCheckerItem	*RightPoint;
	double				LimitDot;

	ImageCheckerRegCalcLightLeftRight(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

class	ImageCheckerRegCalcResolution : public ImageCheckerRegCalcBase
{
public:
	double	Resolution;
	double	PosY;
	double	DifResHigh;
	double	DifResLow;

	ImageCheckerRegCalcResolution(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(int ShiftX ,int ShiftY);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

class	ImageCheckerRegCalcSlide : public ImageCheckerRegCalcBase
{
public:
	double	XPos;
	double	YPos;
	double	DifPosLow;
	double	DifPosHigh;

	ImageCheckerRegCalcSlide(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

class	ImageCheckerRegCalcIncline : public ImageCheckerRegCalcBase
{
public:
	double	VarTop;
	double	VarLeft;
	double	VarRight;
	double	VarBottom;
	double	DifLow;
	double	DifHigh;

	ImageCheckerRegCalcIncline(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item);
};

class	ImageCheckerRegCalcParamEntry : public ImageCheckerRegCalcBase
{
public:
	double	CamA;
	double	CamB;
	double	LightA;
	double	LightB;

	ImageCheckerRegCalcParamEntry(ImageCheckerInLayer *Ly);
	virtual	bool	Execute(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	DeletedItem(AlgorithmItemPLI *Item){	return true;	}
};



class   ImageCheckerInLayer : public AlgorithmInLayerPLI
{
public:
	ImageCheckerRegCalcCamX				RegCalcCamX;
	ImageCheckerRegCalcCamY				RegCalcCamY;
	ImageCheckerRegCalcCamZ				RegCalcCamZ;
	ImageCheckerRegCalcCamXTilt			RegCalcCamXTilt;
	ImageCheckerRegCalcCamYTilt			RegCalcCamYTilt;
	ImageCheckerRegCalcCamRot			RegCalcCamRot;
	ImageCheckerRegCalcStageFlat		RegCalcStageFlat;
	ImageCheckerRegCalcStageVerocity	RegCalcStageVerocity;
	ImageCheckerRegCalcStageVConst		RegCalcStageVConst;
	ImageCheckerRegCalcLightWhole		RegCalcLightWhole;
	ImageCheckerRegCalcLightLeftRight	RegCalcLightLeftRight;
	ImageCheckerRegCalcResolution		RegCalcResolution;
	ImageCheckerRegCalcSlide			RegCalcSlide;
	ImageCheckerRegCalcIncline			RegCalcIncline;
	ImageCheckerRegCalcParamEntry		RegCalcParamEntry;

	ImageCheckerInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			ImageCheckerItem	*a=new ImageCheckerItem();	
			a->SetParent(this);
			return a;
		}
	//void	AddMask(MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	MakeAvrVar(FlexArea &Area,ImageBuffer &Buff
						,double &Avr ,double &Var ,int CellSize=100);
	void	MakeAvrVar(FlexArea &Area ,ImageBuffer &Buff
						,BYTE **MaskMap
						,double &Avr ,double &Var ,int CellSize=100);
	virtual	void	DeleteSelectedItems(void)	override;

private:
	void	SetRegData(struct ImageCheckerRegData &RegData);
};

class   ImageCheckerInPage : public AlgorithmInPagePLI
{
public:
	ImageCheckerInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new ImageCheckerInLayer(parent);	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
};

class	ImageCheckerBase : public AlgorithmBase
{
public:
	QColor	ColorNormal;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorNormal;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	ModeDotPattern;
	int		BlocksizeOfAutoPickPadUp;
	int		NoiseDot;
	int		LineAngle;
	double	LineFreqMicron;
	double	DotResolutionMicron;
	double	SlopAngle;
	bool	InspectMaster;

	ImageCheckerBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new ImageCheckerInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ImageChecker");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigImageChecker.dat");	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==========================================================================================

class	ImageCheckerDrawAttr : public AlgorithmDrawAttr
{
public:
	ImageCheckerThreshold::__ImageCheckerRegMode		Mode;

	ImageCheckerDrawAttr(void){}
	ImageCheckerDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	ImageCheckerDrawAttr(			 int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol
					,ImageCheckerThreshold::__ImageCheckerRegMode mode)
		:AlgorithmDrawAttr(scol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		Mode=mode;
	}
};

class	AddAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	ImageCheckerThreshold::__ImageCheckerRegMode		Mode;

	AddAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SetRegDataPacket : public GUIDirectMessage
{
public:
	struct	ImageCheckerRegData	RegData;

	SetRegDataPacket(LayersBase *base):GUIDirectMessage(base){}
	SetRegDataPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ReqRegDataPacket : public GUIDirectMessage
{
public:
	struct	ImageCheckerRegData	RegData;

	ReqRegDataPacket(LayersBase *base):GUIDirectMessage(base){}
	ReqRegDataPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqValuePacket: public GUIDirectMessage
{
public:
	struct	ImageCheckerRegData	RegData;
	bool	Effective;

	ReqValuePacket(LayersBase *base):GUIDirectMessage(base){}
	ReqValuePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetResultPacket: public GUIDirectMessage
{
public:
	bool	Effective[100];
	struct	ImageCheckerRegData	RegData[100];

	CmdGetResultPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetResultPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdImageCheckerDrawMode : public GUIDirectMessage
{
public:
	ImageCheckerThreshold::__ImageCheckerRegMode	Mode;

	CmdImageCheckerDrawMode(LayersBase *base):GUIDirectMessage(base){}
	CmdImageCheckerDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetImageCheckerDrawMode : public GUIDirectMessage
{
public:
	ImageCheckerThreshold::__ImageCheckerRegMode	Mode;

	CmdSetImageCheckerDrawMode(LayersBase *base):GUIDirectMessage(base){}
	CmdSetImageCheckerDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif