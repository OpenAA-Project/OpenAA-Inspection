#pragma once

#include "PQSystemService.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include <QIcon>
#include <QBuffer>
#include "XDLLType.h"
#include <QWidget>
#include <QApplication>
#include <QLibrary>

class	LayersBase;
class	QWidget;
class	LanguagePackage;
class	PQSystemRunner;

class PQRunnerController : public NPList<PQRunnerController>,public ServiceForLayers
{
	QLibrary 		DllLib;
	QString			DLLFileName;

	PQSystemRunner	*Runner;

	bool		(*DLL_GetName)(QString &Root ,QString &Name);
	WORD		(*DLL_GetDLLType)(void);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetSystemVersion)(VersionType vtype);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguage) (LanguagePackage &Pkg ,int LanguageCode);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);
	
	PQSystemRunner	*(*DLL_CreateRunner)(LayersBase *Base);
	void		(*DLL_CloseRunner)(PQSystemRunner *handle);
	void		(*DLL_InitialQt)(QApplication *AppBase);

public:
	PQRunnerController(LayersBase *base);
	~PQRunnerController();

	bool	LoadDLL(const QString &DLLFileName);
	bool	SetLanguage(int LanguageCode);
	bool	Create(void);
	bool	InitialRunner(void);
	PQSystemRunner	*GetRunner(void)	{	return Runner;		}
};

class PQRunnerControllerContainer : public NPListPack<PQRunnerController>,public ServiceForLayers
{
public:
	PQRunnerControllerContainer(LayersBase *base);
	~PQRunnerControllerContainer ();

	bool	LoadDLL(const QString &DLLPath);
	bool	SetLanguage(int LanguageCode);
private:

};
