#pragma once

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
#include "XRobotClass.h"

class	GUIDirectMessage;

class	RobotClass : public NPList<RobotClass> ,public DLLManager ,public ServiceForLayers
{
	QLibrary 	DllLib;

	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	void	(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	RobotDLLBaseClass	*(*DLL_Initial)(LayersBase *base,const QString &RobotParamStr);
	bool	(*DLL_Close)(RobotDLLBaseClass *handle);
	bool	(*DLL_Load)(RobotDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_Save)(RobotDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(RobotDLLBaseClass *handle, QWidget *parent);


	QString		RobotFileName;
	RobotDLLBaseClass		*Handle;
	QString		Copyright;
	QMutex		MutexRobot;

	QString		DLLName;
	QString		LoadingParameter;
	bool		LoadedDone;
	bool		Initialized;
public:
	explicit	RobotClass(LayersBase *base);
	virtual	~RobotClass(void);

	bool	Initial(int32 &ErrorCode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	RobotDLLBaseClass	*GetHandle(void)	{	return Handle;	}

	bool	IsRobotDLL(void);
	QString	GetDLLName(void)	{	return DLLName;		}

	bool	LoadDLL(int32 &ErrorCode,const QString &FileName,const QString &LoadingParameter);

	virtual	void	GetExportFunctions(QStringList &Str)	override;
	QString	GetFileName(void){	return RobotFileName;	}
	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);

	bool	IsLoadedDone(void)	const	{	return LoadedDone;	}
	void	SetLoadedDone(bool b)		{	LoadedDone=b;		}
	bool	IsInitialized(void)	const	{	return Initialized;	}
	void	SetInitialized(bool b)		{	Initialized=b;		}

	void	TransmitDirectly(GUIDirectMessage *packet);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
};

//=====================================================================================================

class	RobotAccessList : public NPList<RobotAccessList> ,public ServiceForLayers
{
	RobotClass	*Interface;
	bool		Copied;
	QString		UniqueCode;
	QString		DLLPathFileName;
	QString		LoadingParameter;
public:
	RobotAccessList(LayersBase *base ,const QString &DLLPathFileName,const QString &LoadingParameter,const QString &UniqueCode);
	RobotAccessList(const RobotAccessList &src);
	virtual	~RobotAccessList(void);

	RobotClass	*GetInterface(void)	const	{	return Interface;	}
	
	RobotAccessList	&operator=(const RobotAccessList &src);
	bool	Initial(int32 &ErrorCode);
	void	Set(const QString &DLLFileName,const QString &LoadingParameter,const QString &UniqueName);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	RobotDLLBaseClass	*GetHandle(void);

	bool	IsTurnOn(void)	;
	QString	GetDLLName(void)	const;
	QString	GetUniqueCode(void)	const			{	return UniqueCode;			}
	QString	GetDLLPathFileName(void)	const	{	return DLLPathFileName;		}
	QString	GetLoadingParameter(void)	const	{	return LoadingParameter;	}

	bool	IsRobotDLL(void)	const;
	bool	LoadDLL(int32 &ErrorCode);

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
};


class RobotInstanceParameter
{
public:
	QString	DLLFileName;
	QString	UniqueCode;
	QString	LoadingParameter;

	RobotInstanceParameter(void){}

};


class	RobotClassPack : public NPListPack<RobotAccessList> ,public ServiceForLayers
{
public:
	RobotClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(RobotInstanceParameter Param[] ,int ParamNumb,int32 &ErrorCode);

	virtual	bool		IsEmptyRobot(void)	;

	virtual	bool	CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);
	bool			Initial(int32 &ErrorCode);

	virtual	void	LoopOnIdle(void);

	virtual	bool	Load(QIODevice *str);
	virtual	bool	Save(QIODevice *str);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);

	virtual	RobotDLLBaseClass	*GetRobot(int n);
	virtual	RobotDLLBaseClass	*GetRobot(int n ,const QString &DLLname);
	virtual	RobotDLLBaseClass	*FindRobotByUniqueCode(const QString &UniqueCode);
	virtual	void				GetRobot(const QString &DLLname,IntList &RetN);
};
//-----------------------------------------------------------------------------