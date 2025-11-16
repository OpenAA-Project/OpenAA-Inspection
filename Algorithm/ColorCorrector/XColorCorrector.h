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

#define	ColorCorrectorVersion	1

class   ColorShiftVItem;
class   ColorChangeVItem;
class	ColorCorrectorInPage;
class	ColorCorrectorBase;

enum ColorCorrectorType
{

	 ItemClassColorShiftV	=0
	,ItemClassColorShiftH	=1
	,ItemClassColorChangeV	=2
	,ItemClassColorChangeH	=3
};

//----------------------------------------------------------------------
class	ColorCorrectorThresholdBase : public AlgorithmThreshold
{
public:
	ColorCorrectorThresholdBase(AlgorithmItemRoot *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)		override;
    virtual	bool	Load(QIODevice *f)		override;
};

class   ColorCorrectorItemBase : public AlgorithmItemPITemplate<ColorCorrectorInPage,ColorCorrectorBase>
{
public:

	ColorCorrectorItemBase(void);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};
//----------------------------------------------------------------------
class	ColorShiftVThreshold : public ColorCorrectorThresholdBase
{
public:
	int		BandHeight;
	int		SearchXDot;
	int		SearchYDot;
	int		RegularLayer;	//Normally green

	ColorShiftVThreshold(void):ColorCorrectorThresholdBase(NULL){}
	ColorShiftVThreshold(ColorShiftVItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override{};
};


class   ColorShiftVItem : public ColorCorrectorItemBase
{
public:

	ColorShiftVItem(void);

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ColorShiftVItem();	}
	virtual	int32		GetItemClassType(void)	override	{	return ItemClassColorShiftV;		}

	const	ColorShiftVThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const ColorShiftVThreshold *)GetThresholdBaseReadable(base);	}
	ColorShiftVThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (ColorShiftVThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new ColorShiftVThreshold(this);	}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;


private:

};

//----------------------------------------------------------------------
class	ColorChangeVThreshold : public ColorCorrectorThresholdBase
{
public:
	ColorChangeVThreshold(void):ColorCorrectorThresholdBase(NULL){}
	ColorChangeVThreshold(ColorChangeVItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override{};
};


class   ColorChangeVItem : public ColorCorrectorItemBase
{
public:

	ColorChangeVItem(void);

	virtual	int32		GetItemClassType(void)	override	{	return ItemClassColorChangeV;		}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ColorChangeVItem();	}
	
	const	ColorChangeVThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const ColorChangeVThreshold *)GetThresholdBaseReadable(base);	}
	ColorChangeVThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (ColorChangeVThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override		{	return new ColorChangeVThreshold(this);	}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;


private:

};
//==============================================================================
class	ColorCorrectorInPage : public AlgorithmInPagePITemplate<ColorCorrectorItemBase,ColorCorrectorBase>
{
public:

	ColorCorrectorInPage(AlgorithmBase *parent);
	~ColorCorrectorInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	ColorCorrectorBase : public AlgorithmBase
{
public:
	QColor		ColorNormal		;
	QColor		ColorSelected	;
	QColor		ColorActive		;
	QColor		NegColorArea	;
	QColor		NegColorSelected;
	int32		TransparentLevel;

	ColorCorrectorBase(LayersBase *Base);

	virtual	ColorCorrectorInPage	*NewChild(AlgorithmBase *parent)override{	return new ColorCorrectorInPage(parent);		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)								override{	return QString("ColorCorrector");			}
	QString	GetDefaultFileName(void)								override{	return QString("ConfigColorCorrector.dat");	}
	QString	GetNameByCurrentLanguage(void);

	//virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	//virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	//virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	//virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	//virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//==================================================================================
//==================================================================================
class	ColorCorrectorDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	ColorCorrectorType	VType;

	ColorCorrectorDrawAttr(LayersBase *Base):ServiceForLayers(Base){	VType=ItemClassColorShiftV;	}
	ColorCorrectorDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	ColorCorrectorDrawAttr(LayersBase *Base
						, QColor ncol ,int ntranparentLevel
						, QColor scol ,int stranparentLevel
						, QColor acol ,int atranparentLevel);
	void	Initial(void);

	ColorCorrectorDrawAttr	&operator=(ColorCorrectorDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	ColorCorrectorDrawAttr::ColorCorrectorDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol ,196
				 , scol ,196
				 , acol ,196),ServiceForLayers(Base)
{
}
inline	ColorCorrectorDrawAttr::ColorCorrectorDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	VType=ItemClassColorShiftV;
}

inline	ColorCorrectorDrawAttr	&ColorCorrectorDrawAttr::operator=(ColorCorrectorDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	VType	=src.VType;

	return *this;
}
inline	bool	ColorCorrectorDrawAttr::Save(QIODevice *f)
{
	int32	d=(int32)VType;
	if(::Save(f,d)==false)	return false;

	return true;
}
inline	bool	ColorCorrectorDrawAttr::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false)	return false;
	VType=(ColorCorrectorType)d;

	return true;
}

//==================================================================================
//==================================================================================
class	CmdAddByteColorCorrectorItemPacket : public GUIDirectMessage
{
public:
	QByteArray			Buff;
	FlexArea			Area;
	ColorCorrectorType	VType;
	
	CmdAddByteColorCorrectorItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteColorCorrectorItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateThreshold : public GUIDirectMessage
{
public:
	ColorCorrectorType	VType;
	AlgorithmThreshold	*Thr;

	CmdCreateThreshold(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdLoadThreshold : public GUIDirectMessage
{
public:
	AlgorithmThreshold	*Thr;
	QByteArray			Data;

	CmdLoadThreshold(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSaveThreshold : public GUIDirectMessage
{
public:
	AlgorithmThreshold	*Thr;
	QByteArray			Data;

	CmdSaveThreshold(LayersBase *Base):GUIDirectMessage(Base){}
};
