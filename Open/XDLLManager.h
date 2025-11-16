#if	!defined(XDLLMANAGER_H)
#define	XDLLMANAGER_H

#include "Regulus64Version.h"
#include "XTypeDef.h"
#include <QtGlobal>
#include <stdlib.h>
#include <QStringList>
#include <QLibrary>

class	DLLManager
{
protected:
	bool	ReEntrantDLL;

	const char	*(*DLL_GetSystemVersion)(VersionType vtype);
	bool	(*DLL_GetRelatedDLL)(QStringList &DLLFileNames);		
	char	*(*DLL_GetRelatedDLLSystemVersion)(const QString &DLLFileName ,VersionType vtype);

public:
	DLLManager(void);
	virtual	~DLLManager(void);

	bool	LoadDLL(QLibrary &DllLib);

	bool	GetRelatedDLL(QStringList &DLLFileNames);
	char	*GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype);
	const char	*GetSystemVersion(VersionType vtype);

	virtual	void	GetExportFunctions(QStringList &Str);
	bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName);
};

#endif
