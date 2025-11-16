/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMakeAverageImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XMakeAverageImage_H)
#define	XMakeAverageImage_H

#define	MakeAverageImageVersion	1

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XMakeAverageImagePacket.h"
#include "XServiceForLayers.h"

class	MakeAverageImageItem;
class MakeAverageImageUsageAreaItem;

class	MakeAverageImageDrawAttr : public AlgorithmDrawAttr, public ServiceForLayers
{
public:
	enum	_DrawMode{
		_None		=0
		,_Average	=1
		,_Dark		=2
		,_Light		=3
		,_Variable	=4
		,_AverageWithManualItem	=10
	}DrawMode;
	bool	ModeShowItems;
	int		VariableStrength;

	MakeAverageImageDrawAttr(void):ServiceForLayers(NULL){	DrawMode=_None;	ModeShowItems=false;	}
	MakeAverageImageDrawAttr(LayersBase *Base
							,const QColor &ncol ,int ntranparentLevel
							,const QColor &scol ,int stranparentLevel
							,const QColor &acol ,int atranparentLevel);

	MakeAverageImageDrawAttr	&operator=(MakeAverageImageDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	MakeAverageImageDrawAttr::MakeAverageImageDrawAttr(LayersBase *Base
							,const QColor &ncol ,int ntranparentLevel
							,const QColor &scol ,int stranparentLevel
							,const QColor &acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
{
	DrawMode=_None;	ModeShowItems=false;
	VariableStrength=1;
}
inline	MakeAverageImageDrawAttr	&MakeAverageImageDrawAttr::operator=(MakeAverageImageDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	DrawMode		=src.DrawMode;
	ModeShowItems	=src.ModeShowItems;
	VariableStrength=src.VariableStrength;
	return *this;
}

inline	bool	MakeAverageImageDrawAttr::Save(QIODevice *f)
{
	BYTE	d=(BYTE)DrawMode;
	if(::Save(f,d)==false)	return false;
	if(::Save(f,ModeShowItems)==false)	return false;
	if(::Save(f,VariableStrength)==false)	return false;
	return true;
}

inline	bool	MakeAverageImageDrawAttr::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	DrawMode=(_DrawMode)d;
	if(::Load(f,ModeShowItems)==false)	return false;
	if(::Load(f,VariableStrength)==false)	return false;
	return true;
}
//-------------------------------------------------------------

#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12

class	MakeAverageImageThreshold : public AlgorithmThreshold
{
public:
	int		SearchDot;
	double	RotationDegree;

	MakeAverageImageThreshold(MakeAverageImageItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MakeAverageImageUsageAreaThreshold : public AlgorithmThreshold
{
public:
	MakeAverageImageUsageAreaThreshold(MakeAverageImageUsageAreaItem *parent);

	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override	{	return true;	}
	virtual	bool	Save(QIODevice *f)				override	{	return true;	}
	virtual	bool	Load(QIODevice *f)				override	{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

//-----------------------------------------------------------------

class	MakeAverageImageItem : public AlgorithmItemPI
{
	AlignmentPacket2D	*AVector;
	int					AdoptedLayer;
public:

	MakeAverageImageItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MakeAverageImageItem();	}
	virtual	int32		GetItemClassType(void)	override	{ return 0; }

	const	MakeAverageImageThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MakeAverageImageThreshold *)GetThresholdBaseReadable(base);	}
	MakeAverageImageThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MakeAverageImageThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold			*CreateThresholdInstance(void)	override	{	return new MakeAverageImageThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteScanning			(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	DrawArea  (FlexArea &area	,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	CopyThresholdOnly(MakeAverageImageItem *src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
};

class	MakeAverageImageUsageAreaItem : public AlgorithmItemPI
{
public:
	MakeAverageImageUsageAreaItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MakeAverageImageUsageAreaItem();	}
	virtual	int32		GetItemClassType(void)	override	{ return 1; }
	const	MakeAverageImageUsageAreaThreshold 	*GetThresholdR(LayersBase *base=NULL)	{ return (const MakeAverageImageUsageAreaThreshold *)GetThresholdBaseReadable(base); }
	MakeAverageImageUsageAreaThreshold 			*GetThresholdW(LayersBase *base=NULL)	{ return (MakeAverageImageUsageAreaThreshold *)GetThresholdBaseWritable(base); }
	virtual	AlgorithmThreshold *CreateThresholdInstance(void)	override{ return new MakeAverageImageUsageAreaThreshold(this); }

	virtual	void	DrawArea(FlexArea &area, QImage &pnt, int movx, int movy, double ZoomRate, AlgorithmDrawAttr *Attr)	override;
	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};

class   MakeAverageImageInPage : public AlgorithmInPagePI
{
public:
	class	AverageLayerImage : public ServiceForLayers
	{
		MakeAverageImageInPage	*Parent;
		int	Layer;
	public:
		ImageBuffer	LightImage;
		ImageBuffer	DarkImage;
		ImageBuffer	AddedImage;		//	2Byte/pixel
		ImageBuffer	Added2Image;	//	4Byte/pixel
		int			AddedCount;

		AverageLayerImage(LayersBase *base,MakeAverageImageInPage *p ,int layer);
		bool	AllocateMemory(void);
		void	ResetAverage(void);
		void	CopyImage(ImageBuffer &buff);
		void	SetAverageImageIntoMaster(AlgorithmItemPointerListContainer	&UsageAreaContainer);
		bool	MakeVarietyMap(AlgorithmItemPointerListContainer &UsageAreaContainer,ConstMapBuffer &Map);
		void	MakeVariable(BYTE **RMap ,AlgorithmItemPointerListContainer	&UsageAreaContainer,int XLen,int YLen);
		bool    Save(QIODevice *f);
		bool    Load(QIODevice *f);
	};

	AverageLayerImage	*ALayerImages[100];
	int					AllocatedLayers;

public:

	MakeAverageImageInPage(AlgorithmBase *parent);
	~MakeAverageImageInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			if(ItemClassType==0){
				MakeAverageImageItem	*a=new MakeAverageImageItem();	
				a->SetParent(this);
				return a;
			}
			else
			if(ItemClassType==1) {
				MakeAverageImageUsageAreaItem *a=new MakeAverageImageUsageAreaItem();
				a->SetParent(this);
				return a;
			}
			return NULL;
		}
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteScanning			(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool    Save(QIODevice *f)	override;
    virtual	bool    Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	ResetAverage(void);
	void	SetAverageImageIntoMaster(void);

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything=NULL)	override;
	virtual	bool	IncludeLibInReflectionForGenerator(ReflectionMode Mode,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;

	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f);
private:
	void	MakeImageAverage(QImage &pnt, ImageBuffer *Buff[],int AddedCount ,int LayersCount
								,double ZoomRate ,int movx ,int movy
								,int Alpha);
	void	MakeImageVariable(QImage &pnt, ImageBuffer *Buff[],ImageBuffer *Buff2[],int AddedCount ,int LayersCount
								,double ZoomRate ,int movx ,int movy
								,int Alpha ,int VariableStrength);

};

class	MakeAverageImageBase : public AlgorithmBase
{
public:
	QColor	ColorSelected	;
	QColor	ColorActive		;
	QColor	UsageAreaColor	;
	int		DefaultSearchDot;
	double	DefaultRotationDegree;
	int		PartialSize;
	int		ExpandingFromMask;

	MakeAverageImageBase(LayersBase *Base);
	~MakeAverageImageBase(void);

	virtual	bool	HasReflection(ReflectionMode mode)	override{	return (mode==_Reflection_Variety)?true:false;	}

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MakeAverageImageInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MakeAverageImage");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMakeAverageImage.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================

class	CmdDrawStatistic : public GUIDirectMessage
{
public:
	MakeAverageImageDrawAttr::_DrawMode	DrawMode;
	QImage	*Image;
	int		LocalPage;
	int		Movx ,Movy;
	double	ZoomRate;

	CmdDrawStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdDrawStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAddedCountByPhases : public GUIDirectMessage
{
public:
	int	*AddedCountByPhases;

	CmdGetAddedCountByPhases(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAddedCountByPhases(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearAverage: public GUIDirectMessage
{
public:
	int	Phase;
	CmdClearAverage(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAverage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteAverage: public GUIDirectMessage
{
public:
	CmdExecuteAverage(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteAverage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddAverageArea : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAverageArea(LayersBase *base) :GUIDirectMessage(base) {}
	CmdAddAverageArea(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class	CmdResetAverage: public GUIDirectMessage
{
public:
	CmdResetAverage(LayersBase *base):GUIDirectMessage(base){}
	CmdResetAverage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif