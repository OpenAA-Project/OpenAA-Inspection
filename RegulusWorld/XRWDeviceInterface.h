#pragma once

#include <QtGui>
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
#include "XRWDevice.h"

class	GUIDirectMessage;

class	RWDeviceAccessClass : public NPList<RWDeviceAccessClass> ,public DLLManager ,public ServiceForLayers
{
	QLibrary 	DllLib;

	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	void	(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	RWDeviceBaseClass	*(*DLL_Initial)(LayersBase *base,const QString &LightParamStr);
	bool	(*DLL_Close)(RWDeviceBaseClass *handle);
	bool	(*DLL_Load)(RWDeviceBaseClass *handle ,QIODevice &str);
	bool	(*DLL_Save)(RWDeviceBaseClass *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(RWDeviceBaseClass *handle, QWidget *parent);

	QString		ParamStr;
	QString		DLLFileName;
	RWDeviceBaseClass		*Handle;
	QString		Copyright;
	QString		DLLName;
	bool		LoadedDone;
public:
	explicit	RWDeviceAccessClass(LayersBase *base);
	virtual	~RWDeviceAccessClass(void);

	bool	Initial(const QString &DLLFileName ,const QString Parameter 
					,int32 &ErrorCode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);
	bool	IsRWDeviceDLL(void);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	RWDeviceBaseClass	*GetHandle(void)	{	return Handle;	}

	QString	GetDLLName(void)	{	return DLLName;		}

	bool	LoadDLL(const QString &filename ,int32 &ErrorCode);
	bool	LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter);

	virtual	void	GetExportFunctions(QStringList &Str)	override;

	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);

	bool	IsLoadedDone(void)		{	return LoadedDone;	}
	void	SetLoadedDone(bool b)	{	LoadedDone=b;	}

	void	TransmitDirectly(GUIDirectMessage *packet);
};

//-----------------------------------------------------------------------------

class	RWDeviceAccessPack : public NPListPack<RWDeviceAccessClass> ,public ServiceForLayers
{
public:
	RWDeviceAccessPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode);

	RWDeviceBaseClass	*FindByDeviceID(int deviceID);

	virtual	bool	CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);
	virtual	bool	Initial(int32 &ErrorCode);

	virtual	void	LoopOnIdle(void);

	virtual	bool	Load(QIODevice *str);
	virtual	bool	Save(QIODevice *str);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);


};