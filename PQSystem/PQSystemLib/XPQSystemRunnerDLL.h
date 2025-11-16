#pragma once

#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include "XDLLType.h"
#include <QApplication>

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	LanguagePackage;
class	PQSystemRunner;

#if	!defined(ForApplication)

extern "C"{

#ifdef _MSC_VER
DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD	DLL_GetDLLType(void);
DEFFUNCEX	WORD	DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	PQSystemRunner	*DLL_CreateRunner(LayersBase *Base);
DEFFUNCEX	void	DLL_CloseRunner(PQSystemRunner *handle);
DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase);

#else
bool	DLL_GetName(QString &Root ,QString &Name);
WORD	DLL_GetDLLType(void);
WORD	DLL_GetVersion(void);
const char	*DLL_GetSystemVersion(VersionType vtype);
const char	*DLL_GetExplain(void);
void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
bool	DLL_CheckCopyright(QString &CopyrightString);

PQSystemRunner	*DLL_InitialRunner(LayersBase *Base);
void	DLL_CloseRunner(PQSystemRunner *handle);
void	DLL_InitialQt(QApplication *AppBase);
#endif


};

#endif


