#if	!defined(XPQSystemPlugin_h)
#define	XPQSystemPlugin_h


#include <QtGui>
#include <QColor>
#include "XTypeDef.h"


#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


class	LanguagePackage;
class	PQSystemRunner;
class	PQSystemParam;
class	PQSystemBase;

extern	"C"{



#ifdef _MSC_VER
DEFFUNCEX	bool		DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void		DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);

DEFFUNCEX	PQSystemRunner	*DLL_AllocateRunner(PQSystemBase *Base);
DEFFUNCEX	bool		DLL_Release(PQSystemRunner *pointer);

#endif

};



#endif