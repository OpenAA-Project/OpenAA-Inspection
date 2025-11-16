#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTemplateRule.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XTemplateRule_H)
#define	XTemplateRule_H

#define	TemplateRuleVersion	1

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XTemplateRulePacket.h"
#include "XServiceForLayers.h"

class	TemplateRuleItem;
class	TemplateRuleInPage;
class	TemplateRuleBase;
class TemplateRuleUsageAreaItem;

class	TemplateRuleDrawAttr : public AlgorithmDrawAttr, public ServiceForLayers
{
public:

	TemplateRuleDrawAttr(void):ServiceForLayers(NULL){	}
	TemplateRuleDrawAttr(LayersBase *Base
							,const QColor &ncol ,int ntranparentLevel
							,const QColor &scol ,int stranparentLevel
							,const QColor &acol ,int atranparentLevel);

	TemplateRuleDrawAttr	&operator=(TemplateRuleDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	TemplateRuleDrawAttr::TemplateRuleDrawAttr(LayersBase *Base
							,const QColor &ncol ,int ntranparentLevel
							,const QColor &scol ,int stranparentLevel
							,const QColor &acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
{
}
inline	TemplateRuleDrawAttr	&TemplateRuleDrawAttr::operator=(TemplateRuleDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	return *this;
}

inline	bool	TemplateRuleDrawAttr::Save(QIODevice *f)
{
	//BYTE	d=(BYTE)DrawMode;
	//if(::Save(f,d)==false)	return false;
	//if(::Save(f,ModeShowItems)==false)	return false;
	//if(::Save(f,VariableStrength)==false)	return false;
	return true;
}

inline	bool	TemplateRuleDrawAttr::Load(QIODevice *f)
{
	//BYTE	d;
	//if(::Load(f,d)==false)	return false;
	//DrawMode=(_DrawMode)d;
	//if(::Load(f,ModeShowItems)==false)	return false;
	//if(::Load(f,VariableStrength)==false)	return false;
	return true;
}
//-------------------------------------------------------------

#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12

class PLRuleValue : public NPListSaveLoad<PLRuleValue>
{
public:
	enum _RuleType
	{
		RType_Int		=1
		,RType_WORD		=2
		,RType_BYTE		=3
		,RType_Double	=4
		,RType_Float	=5
		,RType_String	=6
		,RType_Bool		=7
	}RuleType;
	int32	ThresholdID;
	int32	ChangeMode;	//0:Add/True	1:Replace/False		2:Toggle

	int		ValueInt	;
	WORD	ValueWord	;
	BYTE	ValueByte	;
	double	ValueDouble	;
	float	ValueFloat	;
	QString	ValueString	;
	bool	ValueBool	;

	PLRuleValue(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;	
};

class PLRuleValueContainer : public NPListPackSaveLoad<PLRuleValue>
{
public:
	PLRuleValueContainer(void){}

	virtual	PLRuleValue	*Create(void)	{	return new PLRuleValue();	}
};


class	TemplateRuleThreshold : public AlgorithmThreshold
{
public:

	TemplateRuleThreshold(TemplateRuleItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

//-----------------------------------------------------------------

class	TemplateRuleItem : public AlgorithmItemPITemplate<TemplateRuleInPage,TemplateRuleBase>
{
public:
	int32	TargetAlgorithmType	;
	int32	TargetLibID			;
	IntList	TargetItemID		;
	QString	TargetItemName		;
	PLRuleValueContainer	PLRules;

	TemplateRuleItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new TemplateRuleItem();	}
	virtual	int32		GetItemClassType(void)	override	{ return 0; }

	const	TemplateRuleThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const TemplateRuleThreshold *)GetThresholdBaseReadable(base);	}
	TemplateRuleThreshold			*GetThresholdW(LayersBase *base=NULL){	return (TemplateRuleThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold			*CreateThresholdInstance(void)	override	{	return new TemplateRuleThreshold(this);	}

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f,LayersBase *LBase)override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

class   TemplateRuleInPage : public AlgorithmInPagePITemplate<TemplateRuleItem,TemplateRuleBase>
{
public:
	TemplateRuleInPage(AlgorithmBase *parent);
	~TemplateRuleInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
};

class	TemplateRuleBase : public AlgorithmBase
{
public:
	QColor	ColorArea		;
	QColor	ColorSelected	;
	QColor	ColorActive		;
	QColor	NegColorArea	;
	QColor	NegColorSelected;
	int32	TransparentLevel;

	TemplateRuleBase(LayersBase *Base);
	~TemplateRuleBase(void);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new TemplateRuleInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("TemplateRule");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigTemplateRule.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================

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