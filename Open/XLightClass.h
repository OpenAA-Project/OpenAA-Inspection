/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XLightClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLIGHTCLASS_H)
#define	XLIGHTCLASS_H

#include <QtGui>
//#include <QSqlDatabase>
#include <QLibrary>
#include <QMutex>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	LightClass;
class	GUIDirectMessage;
class	LightClassPack;

class	CmdReqReflectFromLightSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CmdReqReflectFromLightSpecifiedBroadcaster(void){}
};

class	LightDLLBaseClass : public QWidget 
							,public IdentifiedClass
							,public ServiceForLayers
{
	Q_OBJECT
public:
	LightDLLBaseClass(QWidget *parent ,LayersBase *base):QWidget(parent),ServiceForLayers(base){}
	virtual	~LightDLLBaseClass(void){}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	LoopOnIdle(void){}

	virtual	bool	Save(QIODevice *f)						=0;
	virtual	bool	Load(QIODevice *f)						=0;

	virtual	bool	ShowSettingDialog(void)					=0;
	virtual	bool	ReflectDataInDialog(void);
	virtual	bool	ReflectOnOffInDialog(bool LightOn);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)				{	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb){	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb)									{	return true;	}
	virtual	bool	InsertPage(int IndexPage)										{	return true;	}
	virtual	bool	RemovePage(int IndexPage)										{	return true;	}

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	=0;
	virtual	bool	ReflectPhysical(void)					=0;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		=0;

	virtual	bool	IsAbleToSetBrightness(void)					{	return false;	}
	virtual	bool	SetBrightness(int Layer ,int Percent[100])	{	return false;	}
	//	This is for Automatic adjustment of brightness
	//	Percent dimension : Percent[Position]
	//						Percent[0] = left side	Percent[99]=right side

signals:
	void	SignalReflectDataInDialog();
	void	SignalReflectOnOffInDialog(bool LightOn);
};

//=====================================================================================================

class	LightAccessList : public NPList<LightAccessList> ,public ServiceForLayers
{
	LightClass	*Interface;
	bool		Copied;
public:
	LightAccessList(LayersBase *base);
	LightAccessList(const LightAccessList &src);
	virtual	~LightAccessList(void);

	LightClass	*GetInterface(void)	const	{	return Interface;	}
	
	LightAccessList	&operator=(const LightAccessList &src);
	bool	Initial(const QString &DLLFileName ,const QString &Parameter 
					,int32 &ErrorCode ,bool OutputMode);
	bool	InitialStraightPath(const QString &DLLFileName ,const QString &Parameter 
								,int32 &ErrorCode,bool _OutputMode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	LightDLLBaseClass	*GetHandle(void);

	int		GetLightPatternCount(void);
	bool	LightOn(void);
	bool	LightOff(void);
	bool	SetPattern(int PatternNo);
	bool	ReqLightError(QStringList &Msg);

	int		GetPatternNo(void);
	bool	IsTurnOn(void)	;
	QString	GetDLLName(void)	const;

	bool	IsLightDLL(void)	const;
	bool	LoadDLL(const QString &filename ,int32 &ErrorCode);
	bool	LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString &Parameter);

	void	GetExportFunctions(QStringList &Str);
	QString	GetFileName(void)	const;
	QString	GetCopyright(void)	const;
	QString	GetName(void)		const;
	WORD	GetVersion(void)	const;
	WORD	GetDLLType(void)	const;
	QString	GetExplain(void)	const;

	bool	IsLoadedDone(void)	const;
	void	SetLoadedDone(bool b);

	void	TransmitDirectly(GUIDirectMessage *packet);	
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
};


class	LightClassPack : public NPListPack<LightAccessList> ,public ServiceForLayers
{
public:
	LightClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode);

	virtual	bool		IsEmptyLight(void)	;

	virtual	bool	CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);
	virtual	bool	Initial(int32 &ErrorCode ,bool OutputMode);
	virtual	bool	LightOn(void);
	virtual	bool	LightOff(void);
	virtual	bool	SetPattern(int PatternNo);
	virtual	int		GetPatternNo(void);
	virtual	bool	IsTurnOn(void);
	virtual	void	LoopOnIdle(void);

	virtual	bool	Load(QIODevice *str);
	virtual	bool	Save(QIODevice *str);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	virtual	LightDLLBaseClass	*GetLight(int n);
	virtual	LightDLLBaseClass	*GetLight(int n ,const QString &DLLname);
	virtual	void				GetLight(const QString &DLLname,IntList &RetN);
};
//-----------------------------------------------------------------------------
class	CmdSendRequestLight : public GUIDirectMessage
{
public:
	BYTE	*AnyData;
	int		BytesOfAnyData;

	CmdSendRequestLight(LayersBase *base)		:GUIDirectMessage(base)	{	AnyData=NULL;	BytesOfAnyData=0;	}
	CmdSendRequestLight(GUICmdPacketBase *base)	:GUIDirectMessage(base)	{	AnyData=NULL;	BytesOfAnyData=0;	}
	CmdSendRequestLight(LayersBase *base ,BYTE *data ,int dataLen)		:GUIDirectMessage(base)	{	AnyData=data;	BytesOfAnyData=dataLen;	}
	CmdSendRequestLight(GUICmdPacketBase *base,BYTE *data ,int dataLen)	:GUIDirectMessage(base)	{	AnyData=data;	BytesOfAnyData=dataLen;	}
	~CmdSendRequestLight(void){}
};

#endif