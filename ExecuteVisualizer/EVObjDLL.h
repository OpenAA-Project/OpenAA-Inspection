#if	!defined(EVOBJDLL_H)
#define	EVOBJDLL_H

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	RunnerMap;
class	LanguagePackage;

extern "C"{

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD	DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void	DLL_GetUsageFiles(QStringList &RelativeFilePath);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base);
DEFFUNCEX	void	DLL_Close(void);
DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase);

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap);
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance);

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle);
};


#endif
