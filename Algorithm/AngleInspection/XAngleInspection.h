#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>

#define	AngleInspectionVersion	1

class	AngleInspectionItem;
class	AngleInspectionRegulation;
class	AngleInspectionInPage;
class	AngleInspectionBase;
class	AngleInspectionLibrary;

class	AngleInspectionItem;
class	AngleInspectionInPage;


//==========================================================================================

class	AngleInspectionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	AngleInspectionDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	AngleInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	AngleInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);
};

inline	AngleInspectionDrawAttr::AngleInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol ,196
				 , scol ,196
				 , acol ,196),ServiceForLayers(Base)
{
}

inline	AngleInspectionDrawAttr::AngleInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

//========================================================================================
class	AngleInspectionThreshold : public AlgorithmThreshold
{
public:
	double		OKAngleL;
	double		OKAngleH;

	AngleInspectionThreshold(AngleInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	AngleInspectionItem : public AlgorithmItemPITemplate<AngleInspectionInPage,AngleInspectionBase>
{
	AlignmentPacket2D	*AVector;
	int		MasterCx,MasterCy;
public:

	AngleInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AngleInspectionItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return 0;		}

	const	AngleInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AngleInspectionThreshold *)GetThresholdBaseReadable(base);	}
	AngleInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AngleInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AngleInspectionThreshold(this);	}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:

};

class   AngleInspectionInPage : public AlgorithmInPagePITemplate<AngleInspectionItem,AngleInspectionBase>
{
public:
	AngleInspectionInPage(AlgorithmBase *parent);
	~AngleInspectionInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};

#define	LearningMenu_AngleInspection_OK_ByDeltaE	1

class	AngleInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;

	AngleInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new AngleInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;	
	virtual	QString	GetDataText(void)	override{	return QString("AngleInspection");					}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigAngleInspection.dat");		}

	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================
class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetAngleInspection : public GUIDirectMessage
{
public:
	double		OKAngleL;
	double		OKAngleH;

	CmdSetAngleInspection(LayersBase *Base):GUIDirectMessage(Base){}
};