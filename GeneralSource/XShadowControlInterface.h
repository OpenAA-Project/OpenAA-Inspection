#pragma once

#include <QtGui>
#include <QLibrary>
#include "XTypeDef.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"
#include "NList.h"

class	ImageBuffer;
class	LanguagePackage;
class	CameraClass;
class	GUIDirectMessage;
class	SpecifiedBroadcaster;
class	CameraInterface;
class	ShadowTree;
class	ShadowParameter;

class	ShadowControlInterface : public DLLManager 
								,public ServiceForLayers
								,public NPList<ShadowControlInterface>
{

	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &str);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);

	ShadowTree	*(*DLL_Initial)(int ShadowNumber,LayersBase *ParentBase
								,const QString &GlobalParamFileName
								,const QString &GUIFileName);
	bool		(*DLL_Close)(ShadowTree *handle);
	bool		(*DLL_ShowSetting)(ShadowTree *handle, QWidget *parent);

	QLibrary 	DllLib;
	QString		LibraryFileName;
	QString		Copyright;
	bool		InFunc;
	ShadowTree	*Inst;
public:
	ShadowControlInterface(int ShadowNumber ,LayersBase *base);
	ShadowControlInterface(const ShadowControlInterface &src);
	~ShadowControlInterface(void);

	ShadowControlInterface	&operator=(const ShadowControlInterface &src);
	bool	LoadDLL(const QString &dllfilename,int32 &ErrorCode);
	bool	SetLanguageCode(int LanguageCode);

	QString	GetLibraryFileName(void);
	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);

	ShadowTree	*Initial(int ShadowNumber,LayersBase *ParentBase 
						,const QString &GlobalParamFileName
						,const QString &ShadowGUIFileName);
	ShadowTree	*GetInstance(void)	{	return Inst;	}
	bool		ShowSetting(QWidget *parent);
	bool	Close(ShadowTree *handle);
};


class	ShadowControlInterfaceContainer :public ServiceForLayers
										,public NPListPack<ShadowControlInterface>
{
public:
	ShadowControlInterfaceContainer(LayersBase *base);
	ShadowControlInterfaceContainer(const ShadowControlInterfaceContainer &src);

	ShadowControlInterfaceContainer	&operator=(const ShadowControlInterfaceContainer &src);
	bool	InitialDLL(void);

	bool	SaveShadowParam(QIODevice *f);
	bool	LoadShadowParam(QIODevice *f);
};
