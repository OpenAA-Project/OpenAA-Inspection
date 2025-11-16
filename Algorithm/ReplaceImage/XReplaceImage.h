#pragma once

#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"

#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithmList.h"
#include "XDataComponent.h"
#include "XVector.h"

#define	ReplaceImageVersion	1

class   ReplaceImageItem;
class	ReplaceImageInPage;
class	ReplaceImageBase;


//----------------------------------------------------------------------
class	ReplaceImageThreshold : public AlgorithmThreshold
{
public:
	enum OperateIsolation
	{
		 _RI_None			=0
		,_RI_ByColor		=1
		,_RI_ByMaskImage	=2
		,_RI_ByOutline		=3
		,_RI_ByDrawing		=4
	}OpeIso;

	enum OperateComposite
	{
		 _RC_None			=0
		,_RC_Mask			=1
		,_RC_Color			=2
		,_RC_Transparent	=3
		,_RC_Image			=4
		,_RC_Page			=5
	}OpeComp;
	bool	CompositeInside;


	ReplaceImageThreshold(ReplaceImageItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override{};
};


class   ReplaceImageItem : public AlgorithmItemPITemplate<ReplaceImageInPage,ReplaceImageBase>
{
	BYTE	**CMask;
	BYTE	**TmpMask;
	int		XLen,YLen;
public:
	ColorCubeBit	ColorMask;
	QImage			MaskImage;
	XYClassCluster	OriginalMaskOutline;
	XYClassCluster	CurrentMaskOutline;
	QMutex			MutexOutline;
	FlexArea		MaskArea;

	QColor	CompColor;
	QImage	CompImage;
	int		CompPage;

	ReplaceImageItem(void);
	virtual	~ReplaceImageItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ReplaceImageItem();	}
	const	ReplaceImageThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const ReplaceImageThreshold *)GetThresholdBaseReadable(base);	}
	ReplaceImageThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (ReplaceImageThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new ReplaceImageThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	ReplaceImageItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(ReplaceImageItem &src);
	void	CopyThresholdOnly(ReplaceImageItem &src);
	void	CopyArea(ReplaceImageItem &src);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;

	QColor	AddPickArea(FlexArea &Area);

	bool	CalcMask(void);
	void	GenerateEdge(int x, int y);

private:

};

class	ReplaceImageInPage : public AlgorithmInPagePITemplate<ReplaceImageItem,ReplaceImageBase>
{
public:

	ReplaceImageInPage(AlgorithmBase *parent);
	~ReplaceImageInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new ReplaceImageItem();	}
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

class	ReplaceImageBase : public AlgorithmBase
{
public:
	QColor		ColorNormal		;
	QColor		ColorSelected	;
	QColor		ColorActive		;
	QColor		Color0;
	QColor		Color1;
	QColor		Color2;
	QColor		Color3;
	QColor		Color4;
	QColor		Color5;
	QColor		Color6;
	QColor		Color7;


	ReplaceImageBase(LayersBase *Base);

	virtual	ReplaceImageInPage	*NewChild(AlgorithmBase *parent)override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("ReplaceImage");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigReplaceImage.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//==================================================================================
//==================================================================================
class	ReplaceImageDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ShowIsoMask;

	ReplaceImageDrawAttr(void):ServiceForLayers(NULL){	ShowIsoMask=false;	}
	ReplaceImageDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);

	void	Initial(void);

	ReplaceImageDrawAttr	&operator=(ReplaceImageDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	ReplaceImageDrawAttr::ReplaceImageDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
}

inline	ReplaceImageDrawAttr	&ReplaceImageDrawAttr::operator=(ReplaceImageDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	ShowIsoMask	=src.ShowIsoMask;

	return *this;
}
inline	bool	ReplaceImageDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,ShowIsoMask)==false)	return false;

	return true;
}
inline	bool	ReplaceImageDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,ShowIsoMask)==false)	return false;

	return true;
}

//==================================================================================
//==================================================================================

class	CmdReplaceImageAddMaskArea : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QColor		AverageColor;

	CmdReplaceImageAddMaskArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageAddMaskArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageAddMaskImage : public GUIDirectMessage
{
public:
	QImage	Image;

	CmdReplaceImageAddMaskImage(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageAddMaskImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageCalcMask : public GUIDirectMessage
{
public:
	CmdReplaceImageCalcMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageCalcMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageMouseLDown : public GUIDirectMessage
{
public:
	int	X,Y;
	CmdReplaceImageMouseLDown(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageMouseLDown(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageSetCompositeColor : public GUIDirectMessage
{
public:
	QColor	Color;

	CmdReplaceImageSetCompositeColor(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageSetCompositeColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageSetCompositeImage : public GUIDirectMessage
{
public:
	QImage	Image;

	CmdReplaceImageSetCompositeImage(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageSetCompositeImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageSetCompositePage : public GUIDirectMessage
{
public:
	int	CompPage;

	CmdReplaceImageSetCompositePage(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageSetCompositePage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageReqDraw : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	int		CanvasWidth;
	int		CanvasHeight;
	QImage	*Image;
	ReplaceImageDrawAttr	Attr;

	CmdReplaceImageReqDraw(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageReqDraw(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageProcessMode : public GUIDirectMessage
{
public:
	ReplaceImageThreshold::OperateComposite	CompMode;
	bool	CompositeInside;

	CmdReplaceImageProcessMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageProcessMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageMaskMode : public GUIDirectMessage
{
public:
	ReplaceImageThreshold::OperateIsolation	OpeMode;

	CmdReplaceImageMaskMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageMaskMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceImageMakeAreaMask : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdReplaceImageMakeAreaMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageMakeAreaMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};