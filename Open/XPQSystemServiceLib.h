#if	!defined(XPQSystemService_h)
#define	XPQSystemService_h

#include <QString>
#include <QSqlDatabase>
#include "XTypeDef.h"
#include "NList.h"

class	PQSystemDBLoader;
class	PQSystemParam;
class	PQSystemResult;
class	PQSystemXMLLoader;
class	PQSystemXMLAccessor;
class	LanguagePackage;
class	PQSystemXMLDLLBaseRoot;
class	PQSystemRunnerLoaderContainer;
class	MachineInfoContainer;
class	LocalDatabaseBasicClass;
class	FileRegistry;
class	PQSystemRunner;

class	PQSystemBase
{
	QString					CurrentPath;
	FileRegistry			*FRegistry;
	PQSystemDBLoader		*DBLoader;
	PQSystemParam			*PQSystemParamData;
	PQSystemXMLLoader		*XMLLoader;
	PQSystemRunnerLoaderContainer	*Runners;

	PQSystemXMLAccessor		*PQSystemResult;
	int						LanguageCode;
	LanguagePackage			*LanguagePackageData;
	QSqlDatabase			*RootDBase;
	LocalDatabaseBasicClass	*KDatabase;
public:
	PQSystemBase(const QString &currentpath);
	virtual ~PQSystemBase(void);

	bool	LoadInitialParam(void);

	bool	InitialDBLoader(void);
	bool	InitialXMLLoader(void);
	bool	InitialRunner(void);

	QString	GetCurrentPath(void)	{	return CurrentPath;		}
	int		GetLanguageCode(void)	{	return LanguageCode;	}
	LanguagePackage		&GetLanguagePackageData(void)	{	return *LanguagePackageData;	}

	PQSystemParam			*GetPQSystemParam(void)	{	return PQSystemParamData;	}

	//--------SQL database---------//
	PQSystemDBLoader	*GetDB(void)	{	return DBLoader;	}
	bool	IsSQLDatabaseExist(void);
	bool	SQLEnumMachines(MachineInfoContainer &AllMachines);

	PQSystemXMLDLLBaseRoot	*GetXML(void);
	PQSystemRunnerLoaderContainer	*GetRunners(void)	{	return Runners;		}
};

//=====================================================================================

class	MachineInfoList : public NPList<MachineInfoList>
{
public:
	int		MachineCode;
	QString	MachineName;

	MachineInfoList(void){	MachineCode=0;	}
};

class	MachineInfoContainer : public NPListPack<MachineInfoList>
{
public:
	MachineInfoContainer(void){}
};


#endif