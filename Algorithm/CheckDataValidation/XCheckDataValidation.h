#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include "XTypeDef.h"

#define	CheckDataValidationVersion	1

class	CheckDataValidationExistItemAreaItem;
class	CheckDataValidationExistItemVectorItem;
class	CheckDataValidationCheckMinMaxItem;
class	CheckDataValidationProhibiteItemItem;
class	CheckDataValidationRegulation;
class	CheckDataValidationInPage;
class	CheckDataValidationBase;
class	CheckDataValidationLibrary;

class	CheckDataValidationInPage;

/*
	ExistItemArea
		指定領域に他のアルゴリズムのアイテムが存在するかどうか
			マスク領域のA%以上にライブラリBのアイテムが存在するか
			指定する部分に指定するライブラリのアイテムが存在するか
	ExistItemVector
		計測ベクトルアイテムが指定範囲に存在するか
	CheckMinMax
		存在する他のアルゴリズムの指定するライブラリの、しきい値パラメータの上限、下限値のチャック
	ProhibiteItem
		指定領域に他のアルゴリズムの指定するるライブラリが存在してはいけない

*/

enum CheckDataValidationType
{
	 CheckDataValidation_ExistItemArea		=1
	,CheckDataValidation_ExistItemVector	=2
	,CheckDataValidation_MinMax				=3
	,CheckDataValidation_ProhibiteItem		=4
};

//==========================================================================================

class	CheckDataValidationDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CheckDataValidationType	VType;

	CheckDataValidationDrawAttr(LayersBase *Base):ServiceForLayers(Base){	VType=CheckDataValidation_ExistItemArea;	}
	CheckDataValidationDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	CheckDataValidationDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

inline	CheckDataValidationDrawAttr::CheckDataValidationDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol ,196
				 , scol ,196
				 , acol ,196),ServiceForLayers(Base)
{
	VType=CheckDataValidation_ExistItemArea;
}

inline	CheckDataValidationDrawAttr::CheckDataValidationDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	VType=CheckDataValidation_ExistItemArea;
}

inline	bool	CheckDataValidationDrawAttr::Save(QIODevice *f)
{
	int32	d=(int32)VType;
	if(::Save(f,d)==false)	return false;
	return true;
}
inline	bool	CheckDataValidationDrawAttr::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false)	return false;
	VType=(CheckDataValidationType)d;
	return true;
}
//========================================================================================
class	CheckDataValidationThresholdBase : public AlgorithmThreshold
{
public:
	int32	LibType;
	int32	LibID;

	CheckDataValidationThresholdBase(AlgorithmItemRoot *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)		override;
    virtual	bool	Load(QIODevice *f)		override;
};

class	CheckDataValidationItemBase : public AlgorithmItemPITemplate<CheckDataValidationInPage,CheckDataValidationBase>
{
public:
	bool	CheckNG;

	CheckDataValidationItemBase(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return NULL;	}
	virtual	int32		GetItemClassType(void)	override	{	return 0;		}

	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return NULL;	}
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	QString	CheckedMessage(void)	=0;
};

//========================================================================================
class	CheckDataValidationExistItemAreaThreshold : public CheckDataValidationThresholdBase
{
public:
	double	FilledPercentageInMask;
	bool	CheckExistence;

	CheckDataValidationExistItemAreaThreshold(void):CheckDataValidationThresholdBase(NULL){}
	CheckDataValidationExistItemAreaThreshold(CheckDataValidationExistItemAreaItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	CheckDataValidationExistItemAreaItem : public CheckDataValidationItemBase
{
	QString	NGMessage;
public:

	CheckDataValidationExistItemAreaItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckDataValidationExistItemAreaItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return (int32)CheckDataValidation_ExistItemArea;		}

	const	CheckDataValidationExistItemAreaThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CheckDataValidationExistItemAreaThreshold *)GetThresholdBaseReadable(base);	}
	CheckDataValidationExistItemAreaThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CheckDataValidationExistItemAreaThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CheckDataValidationExistItemAreaThreshold(this);	}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	QString	CheckedMessage(void)	override;
private:

};

//========================================================================================
class	CheckDataValidationExistItemVectorThreshold : public CheckDataValidationThresholdBase
{
public:
	CheckDataValidationExistItemVectorThreshold(void):CheckDataValidationThresholdBase(NULL){}
	CheckDataValidationExistItemVectorThreshold(CheckDataValidationExistItemVectorItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	CheckDataValidationExistItemVectorItem : public CheckDataValidationItemBase
{
public:

	CheckDataValidationExistItemVectorItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckDataValidationExistItemVectorItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return (int32)CheckDataValidation_ExistItemVector;		}

	const	CheckDataValidationExistItemVectorThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CheckDataValidationExistItemVectorThreshold *)GetThresholdBaseReadable(base);	}
	CheckDataValidationExistItemVectorThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CheckDataValidationExistItemVectorThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CheckDataValidationExistItemVectorThreshold(this);	}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	QString	CheckedMessage(void)	override;
private:

};

//========================================================================================

class ThresholdVariableMinMax
{
public:
	double	MinValueDouble;
	double	MaxValueDouble;
	int64	MinValueInt64;
	int64	MaxValueInt64;
	bool	FixedValueBool;
	DirectValueType	ValueType;

	ThresholdVariableMinMax(void);
	ThresholdVariableMinMax(const ThresholdVariableMinMax &src);

	ThresholdVariableMinMax	&operator=(const ThresholdVariableMinMax &src);
	bool	operator==(const ThresholdVariableMinMax &src)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CheckDataValidationCheckMinMaxThreshold : public CheckDataValidationThresholdBase
{
public:
	int32	ParamID;
	ThresholdVariableMinMax	Value;

	CheckDataValidationCheckMinMaxThreshold(void):CheckDataValidationThresholdBase(NULL){}
	CheckDataValidationCheckMinMaxThreshold(CheckDataValidationCheckMinMaxItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	CheckDataValidationCheckMinMaxItem : public CheckDataValidationItemBase
{
public:

	CheckDataValidationCheckMinMaxItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckDataValidationCheckMinMaxItem();	}
	virtual	int32		GetItemClassType(void)	override	{ return (int32)CheckDataValidation_MinMax; }

	const	CheckDataValidationCheckMinMaxThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CheckDataValidationCheckMinMaxThreshold *)GetThresholdBaseReadable(base);	}
	CheckDataValidationCheckMinMaxThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CheckDataValidationCheckMinMaxThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CheckDataValidationCheckMinMaxThreshold(this);	}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	QString	CheckedMessage(void)	override;
private:

};

//========================================================================================
class	CheckDataValidationProhibiteItemThreshold : public CheckDataValidationThresholdBase
{
public:

	CheckDataValidationProhibiteItemThreshold(void):CheckDataValidationThresholdBase(NULL){}
	CheckDataValidationProhibiteItemThreshold(CheckDataValidationProhibiteItemItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	CheckDataValidationProhibiteItemItem : public CheckDataValidationItemBase
{
public:

	CheckDataValidationProhibiteItemItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckDataValidationProhibiteItemItem();	}
	virtual	int32		GetItemClassType(void)	override	{	return (int32)CheckDataValidation_ProhibiteItem;		}

	const	CheckDataValidationProhibiteItemThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CheckDataValidationProhibiteItemThreshold *)GetThresholdBaseReadable(base);	}
	CheckDataValidationProhibiteItemThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CheckDataValidationProhibiteItemThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CheckDataValidationProhibiteItemThreshold(this);	}
	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	QString	CheckedMessage(void)	override;
private:

};

//========================================================================================

class   CheckDataValidationInPage : public QObject ,public AlgorithmInPagePITemplate<CheckDataValidationItemBase,CheckDataValidationBase>
{
	Q_OBJECT
public:
	QString	NGMessage;

	CheckDataValidationInPage(AlgorithmBase *parent);
	~CheckDataValidationInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

signals:
	void	SignalNGOccurs(int phase ,int page);
};

class	CheckDataValidationBase : public AlgorithmBase
{
public:
	QList<QByteArray>	Data[MaxCountOfPhase];
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	bool	LoadDefaultOnStart;
	QString	DefaultLoadFileName;

	CheckDataValidationBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new CheckDataValidationInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;	
	virtual	QString	GetDataText(void)	override{	return QString("CheckDataValidation");					}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigCheckDataValidation.dat");		}

	virtual	QString	GetNameByCurrentLanguage(void)	override;

	bool	SaveDefaultValidation(void);
	bool	LoadDefaultValidation(void);
};
//==================================================================================
class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetCheckDataValidation : public GUIDirectMessage
{
public:
	double		OKAngleL;
	double		OKAngleH;

	CmdSetCheckDataValidation(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdAddByteCheckDataValidationItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LibType;
	int			LibID;
	CheckDataValidationType	VType;
	
	CmdAddByteCheckDataValidationItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteCheckDataValidationItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdCreateThreshold : public GUIDirectMessage
{
public:
	CheckDataValidationType	VType;
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
