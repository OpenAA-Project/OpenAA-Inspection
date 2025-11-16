/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentProjection\XAlignmentProjection.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XAlignmentProjectionH
#define XAlignmentProjectionH

#include <QIODevice>
#include <QPoint>
#include <QByteArray>
#include <QPainter>
#include <QPoint>
#include <QString>
#include <QMutex>
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPacketAlignmentProjection.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"

#define	AlignmentProjectionVersion	1

class	AlignmentProjectionItem;
class	AlignmentProjectionDrawAtt;


class	AlignmentProjectionThreshold : public AlgorithmThreshold
{
public:
	WORD		PeakCount;
	int			PeakIsolation;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	AlignmentProjectionThreshold(AlignmentProjectionItem *parent);
	~AlignmentProjectionThreshold(void);

	virtual	void	RegistHist(void)	override;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
};


#define	Hist_AlighmentProjectionShiftX			1
#define	Hist_AlighmentProjectionShiftY			2
#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12




class   AlignmentProjectionItem : public AlgorithmItemPI
{
	double	SCos,SSin;
	double	MasterCx,MasterCy;
public:
	int		LMinD;
	int		LMaxD;
	int		*MapPixelsCount;
	double	*MasterMapDim;
	double	*TargetMapDim;
	int		MapDimCount;
	double	*MasterPeak;
	double	*TargetPeak;

    double      ResultDx,ResultDy;	//Calculated position

	AlignmentProjectionItem(void);
	~AlignmentProjectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AlignmentProjectionItem();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	void	MoveTo(int dx ,int dy)	override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    AlignmentProjectionItem &operator=(AlignmentProjectionItem &src);

 	const	AlignmentProjectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AlignmentProjectionThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentProjectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AlignmentProjectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AlignmentProjectionThreshold(this);	}
	
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

    void    Clear(void);
    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	ImageBuffer	&GetMasterBuffForMakeArea(void);

	int		GetMx(void){	return(ResultDx);	}
	int		GetMy(void){	return(ResultDy);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	CopyThresholdOnly(AlignmentProjectionItem *src);

	void	GetAlignmentProjection(AlignmentPacket2D &AData);
	void	GetAlignmentByHandle(AlignmentPacket2D &AData ,void *Handle);

public:
	double    GetLinePointFoot(double Cx,double Cy ,double px ,double py ,double &X ,double &Y);
	void	MakeMapPeak(ImageBuffer &IBuff ,double *MapDim ,double *Peak);
};

class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
{
public:
	AlignmentProjectionItem	*AlignmentItem;

	AlignmentPacket2DList(void){}
};

class   AlignmentProjectionInPage : public AlgorithmInPagePI
{
public:
	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;

	AlignmentProjectionInPage(AlgorithmBase *parent);
	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override{	return new AlignmentProjectionItem();	}
	AlignmentPacket2D	*AppendAlignmentProjectionPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID,ResultInPageRoot *Res)	override;

	void	GetAlignmentProjection(AlignmentPacket2D &AData);
	void	GetAlignmentProjectionByHandle(AlignmentPacket2D &AData ,void *Handle);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
										,FlexArea &area ,AlgorithmBase *OriginBase
										,int ItemClass) override;

	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;

	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f);
private:

};

class	AlignmentProjectionBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points
	bool		UseBitBuff;
	bool		DrawOnlyTopPage;

	AlignmentProjectionBase(LayersBase *Base);
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return(new AlignmentProjectionInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)	override{	return QString("AlignmentProjection");			}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigAlignmentProjection.dat");	}
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

//=======================================================================================

class	ReqAlignmentProjectionPointPacket : public GUIDirectMessage
{
public:
	int			ItemID;
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	ReqAlignmentProjectionPointPacket(LayersBase *base):GUIDirectMessage(base){}
	ReqAlignmentProjectionPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentProjectionPointPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	AddAlignmentProjectionPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentProjectionPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyAlignmentProjectionPointPacket : public GUIDirectMessage
{
public:
	int			ItemID;
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	ModifyAlignmentProjectionPointPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyAlignmentProjectionPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SelectAlignmentPoints : public GUIDirectMessage
{
public:
	FlexArea	Area;

	SelectAlignmentPoints(LayersBase *base):GUIDirectMessage(base){}
	SelectAlignmentPoints(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

#endif
