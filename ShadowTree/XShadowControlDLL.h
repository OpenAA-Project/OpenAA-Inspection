#pragma once

#include <QString>
#include "XTypeDef.h"
#include "XDLLType.h"

class	LayersBase;
class	QWidget;
class	ShadowTree;
class	LanguagePackage;

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

extern	"C"
{
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &str);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	ShadowTree	*DLL_Initial(int ShadowNumber,LayersBase *ParentBase
									,const QString &GlobalParamFileName
									,const QString &GUIFileName);
DEFFUNCEX	bool		DLL_Close(ShadowTree *handle);
DEFFUNCEX	bool		DLL_ShowSetting(ShadowTree *handle, QWidget *parent);

};
