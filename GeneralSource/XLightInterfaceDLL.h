/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\GeneralSource\XLightInterfaceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLIGHTINTERFACEDLL_H)
#define	XLIGHTINTERFACEDLL_H

#include <QtGui>
//#include <QSqlDatabase>
#include <QLibrary>
#include <QMutex>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XDLLManager.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"

class	GUIDirectMessage;

class	LightClass : public NPList<LightClass> ,public DLLManager ,public ServiceForLayers
{
	QLibrary 	DllLib;

	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	void	(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	LightDLLBaseClass	*(*DLL_Initial)(LayersBase *base,const QString &LightParamStr,bool OutputMode);
	bool	(*DLL_Close)(LightDLLBaseClass *handle);
	bool	(*DLL_Load)(LightDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_Save)(LightDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(LightDLLBaseClass *handle, QWidget *parent);
	int		(*DLL_GetLightPatternCount)(LightDLLBaseClass *handle);
	bool	(*DLL_LightOn)(LightDLLBaseClass *handle);
	bool	(*DLL_LightOff)(LightDLLBaseClass *handle);
	bool	(*DLL_SetPattern)(LightDLLBaseClass *handle ,int PatternNo);
	bool	(*DLL_ReqLightError)(LightDLLBaseClass *handle ,QStringList &Msg);

	QString		LightFileName;
	LightDLLBaseClass		*Handle;
	QString		Copyright;
	QMutex		MutexLight;
	int			PatternNo;
	bool		OnOff;
	QString		DLLName;
	bool		OutputMode;
	bool		LoadedDone;
public:
	explicit	LightClass(LayersBase *base);
	virtual	~LightClass(void);

	bool	Initial(const QString &DLLFileName ,const QString Parameter 
					,int32 &ErrorCode ,bool OutputMode);
	bool	InitialStraightPath(const QString &DLLFileName ,const QString Parameter 
								,int32 &ErrorCode,bool _OutputMode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	LightDLLBaseClass	*GetHandle(void)	{	return Handle;	}

	int		GetLightPatternCount(void);
	bool	LightOn(void);
	bool	LightOff(void);
	bool	SetPattern(int PatternNo);
	bool	ReqLightError(QStringList &Msg);

	int		GetPatternNo(void)	{	return PatternNo;	}
	bool	IsTurnOn(void)		{	return OnOff;		}
	QString	GetDLLName(void)	{	return DLLName;		}

	bool	IsLightDLL(void);
	bool	LoadDLL(const QString &filename ,int32 &ErrorCode);
	bool	LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter);

	virtual	void	GetExportFunctions(QStringList &Str)	override;
	QString	GetFileName(void){	return LightFileName;	}
	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);

	bool	IsLoadedDone(void)		{	return LoadedDone;	}
	void	SetLoadedDone(bool b)	{	LoadedDone=b;	}

	void	TransmitDirectly(GUIDirectMessage *packet);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
};

//-----------------------------------------------------------------------------


#endif