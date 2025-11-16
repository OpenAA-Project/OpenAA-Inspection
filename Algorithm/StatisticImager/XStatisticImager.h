/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XStatisticImager.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XSTATISTICIMAGER_H)
#define	XSTATISTICIMAGER_H

#define	StatisticImagerVersion	1


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XStatisticPacket.h"
#undef		DefinedModel
#include "XAutoAlignment.h"
///#include "XDynamicClassify.h"

class	StatisticImagerItem;
#define	LeastStatisticBuffCount	3

class	StatisticImagerDrawAttr : public AlgorithmDrawAttr
{
public:
	enum	_DrawMode{
		_None		=0
		,_Average	=1
		,_Dark		=2
		,_Light		=3
		,_Disorder	=4
	}DrawMode;
};

struct	LeastSquaresMethodStruct1
{
	double	a;
	double	b;
	double	c;
};
struct	LeastSquaresMethodStruct2
{
	double	a;
	double	b;
	double	c;

	double	*TMBrightCoef;
	bool	EnableShader;
};

class	StatisticImagerThreshold : public AlgorithmThreshold
{
public:

	StatisticImagerThreshold(StatisticImagerItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	StatisticImagerItem : public AlgorithmItemPLI
{
public:

	StatisticImagerItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new StatisticImagerItem();	}
	const	StatisticImagerThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const StatisticImagerThreshold *)GetThresholdBaseReadable(base);	}
	StatisticImagerThreshold			*GetThresholdW(LayersBase *base=NULL){	return (StatisticImagerThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold			*CreateThresholdInstance(void)	override{	return new StatisticImagerThreshold(this);	}

	//virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	//virtual	bool    Save(QIODevice *f)	override;
    //virtual	bool    Load(QIODevice *f)	override;
	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};

class   StatisticImagerInLayer : public AlgorithmInLayerPLI
{
public:
	PixelStatisticInLayer	**StatisticBuff;
	int	AllocXLen;
	int	AllocYLen;
	int	StatisticBuffCount;

	StatisticImagerInLayer(AlgorithmInPageRoot *parent);
	~StatisticImagerInLayer(void);

	void	SetShaderEnabled(bool Enabled)	{	ShaderEnabled=Enabled;	}
	bool	GetShaderEnabled()				{	return ShaderEnabled;	}
	PureFlexAreaListContainer &GetTargetMaskBitmapFPack()				{	return TargetMaskBitmapFPack;		}
	struct	LeastSquaresMethodStruct2	&GetTLeastSquaresMethodTable(int i)	{	return TLeastSquaresMethodTable[i];	}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			StatisticImagerItem	*a=new StatisticImagerItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecutePreScanning		(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteScanning			(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;	//A-20090910
///	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInLayerRoot *Res)	override;

	void	ExecutePreShader();

	bool	MakeAverageImage(ImageBuffer &Dest);
	bool	MakeLightImage(ImageBuffer &Dest);
	bool	MakeDarkImage(ImageBuffer &Dest);
	bool	MakeDisorderImage(ImageBuffer &Dest);

	virtual	bool    Save(QIODevice *f)	override;
    virtual	bool    Load(QIODevice *f)	override;

private:
	bool	ExecuteInitialAfterEditFlag;
	double	MasterBrightAvg;
	double	TargetBrightAvg;
	int		MaskBmpCnt;
	BYTE	**MaskBmp;	//マスク領域
	AutoAlignmentInPage	*pAlignPage;	//AutoAlignment
	AlgorithmBase	*ABase;

	int		EnLargeDot;
	bool	ShaderEnabled;

	void	InitialAlloc(void);
	BYTE	**GetMaskBitmap(void);
	BYTE	**GetAutoMaskBitmap(void);

	bool	GetAutoAlignmentLibrary(GUIDirectMessage *CmdPacket);

	PureFlexAreaListContainer MasterMaskBitmapFPack;
	PureFlexAreaListContainer TargetMaskBitmapFPack;
	struct	LeastSquaresMethodStruct1	*MLeastSquaresMethodTable;
	struct	LeastSquaresMethodStruct2	*TLeastSquaresMethodTable;
	void	GetLeastSquaresMethodM();	//最小二乗法を使用して、輝度の２次元平面を作成（マスター画像）
	void	GetLeastSquaresMethodT();
	void	CalcLeastSquaresMethodT();

	bool	CheckTargetPoint(int X,int Y,bool IsPad,bool IsSilk);
	int		SearchMasterArea(PureFlexAreaList *TArea,PureFlexAreaList *MArea,int ShiftX,int ShiftY,int TCnt,int MCnt);
};

class   StatisticImagerInPage : public AlgorithmInPagePLI
{
public:

	StatisticImagerInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new StatisticImagerInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecutePreScanning		(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteScanning			(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;				//A-20090910
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInPageRoot *Res)	override;

	void	ExecuteDoShader();

	void	DrawStatistic(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	void	DarkImageStatistic();

private:
///	bool	GetAverageBrightnessCorrectionM();	//平均輝度補正（マスター画像）
};

class	StatisticImagerBase : public AlgorithmBase
{
public:
	double	Gain;
	bool	AutoMakeAverageImage;
	int		AlignmentScanMergin;
	bool	DebugMode;
	bool	ShaderEnabled;
	double	BrightCoef;

	StatisticImagerBase(LayersBase *Base);

	virtual	ExeResult	ExecutePreScanning		(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new StatisticImagerInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("StatisticImager");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigStatisticImager.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================

class	CmdDrawStatistic : public GUIDirectMessage
{
public:
	StatisticImagerDrawAttr::_DrawMode	DrawMode;
	QImage	*Image;
	int		LocalPage;
	int		Movx ,Movy;
	double	ZoomRate;

	CmdDrawStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdDrawStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif