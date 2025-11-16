/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XResultImportance\XResultImportance.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XResultImportance_H)
#define	XResultImportance_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
//#include "XResultImportanceCommon.h"

class	ResultImportanceItem;
class	ResultImportanceInPage;
class	ResultImportanceBase;

#define	ResultImportanceVersion		1
#define	DefLibTypeResultImportance			28

class	ResultImportanceLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	ResultImportanceLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override{	return true;	}
	virtual	bool	LoadBlob(QIODevice *f)	override{	return true;	}
};

class	ResultImportanceLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ResultImportanceLibraryContainer(LayersBase *base)
		:AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeResultImportance;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ResultImportance Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ResultImportanceLibrary(GetLibType(),GetLayersBase());	}
};

//-------------------------------------------------------------------------

class	ResultImportanceThreshold : public AlgorithmThreshold
{
public:

	ResultImportanceThreshold(ResultImportanceItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	ResultImportanceItem : public AlgorithmItemPITemplate<ResultImportanceInPage,ResultImportanceBase>
{
	ResultPosList **RetDim;
	int MaxCount;
public:
	int		ImportanceLevel;	//0 is the most important

	ResultImportanceItem(void);
	~ResultImportanceItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ResultImportanceItem();	}
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	const	ResultImportanceThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ResultImportanceThreshold *)GetThresholdBaseReadable(base);	}
	ResultImportanceThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ResultImportanceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ResultImportanceThreshold(this);	}
};


class   ResultImportanceInPage : public AlgorithmInPagePITemplate<ResultImportanceItem,AlgorithmBase>
{
public:
	ResultImportanceInPage(AlgorithmBase *parent);
	~ResultImportanceInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			ResultImportanceItem	*a=new ResultImportanceItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	ResultImportanceBase : public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorSelected;
	QColor		ColorActive;
	int32		TransparentLevel;
	QColor		NegColorArea;
	QColor		NegColorSelected;

	QColor		AreaColor0;
	QColor		AreaColor1;
	QColor		AreaColor2;
	QColor		AreaColor3;
	QColor		AreaColor4;
	QColor		AreaColor5;
	QColor		AreaColor6;
	QColor		AreaColor7;

	ResultImportanceBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new ResultImportanceInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ResultImportance");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigResultImportance.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================


class	CmdAddResultImportanceItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		ImportanceLevel;

	CmdAddResultImportanceItemPacket(LayersBase *base):GUIDirectMessage(base){}
};


#endif
