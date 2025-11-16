#include "XPQSystemXMLLoader.h"
#include "XPQSystemResult.h"
#include "XDLLType.h"
#include <QFile>

PQSystemXMLLoader::PQSystemXMLLoader(PQSystemBase *Base)
	:PQSystemBaseService(Base)
{
	DLL_GetOrganization	=NULL;
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_SetLanguage		=NULL;
	DLL_GetExplain		=NULL;
	DLL_CheckCopyright	=NULL;
	DLL_GetParamName	=NULL;
	DLL_Initial			=NULL;
	DLL_Release			=NULL;

	DLLPoint	=NULL;
}
PQSystemXMLLoader::~PQSystemXMLLoader(void)
{
}

bool		PQSystemXMLLoader::LoadDLL(const QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		return(false);
	}
	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetName					=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve(/**/"DLL_SetLanguage");

	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	DLL_GetParamName			=(const char *(*)(void))DllLib.resolve("DLL_GetParamName");
	
	DLL_Initial					=(PQSystemXMLDLLBaseRoot *(*)(PQSystemBase *Base))DllLib.resolve("DLL_Initial");
	DLL_Release					=(bool (*)(PQSystemXMLDLLBaseRoot *))DllLib.resolve("DLL_Release");


	return true;
}
bool		PQSystemXMLLoader::IsResultDLL(void)
{
	if(DLL_GetDLLType!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLResultMode){
			return(true);
		}
	}
	return(false);
}
bool		PQSystemXMLLoader::Initial(void)
{
	PQSystemBase	*Base=GetPQSystemBase();

	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return false;
		}
	}
	if(DLL_GetVersion!=NULL){
		Ver=DLL_GetVersion();
	}
	if(DLL_GetName!=NULL){
		DLL_GetName(DLLRoot,DLLName);
	}
	if(DLL_GetOrganization!=NULL){
		DLL_GetOrganization(Organization);
	}

	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
	}

	if(DLL_Initial!=NULL){
		if(DLLPoint!=NULL){
			delete	DLLPoint;
		}
		DLLPoint	=DLL_Initial(GetPQSystemBase());
		if(DLLPoint==NULL){
			return false;
		}
	}
	if(DLL_GetParamName!=NULL){
		ParamFileName=QString(DLL_GetParamName());
	}
	if(DLLPoint!=NULL && ParamFileName.isEmpty()==false){
		QFile	PFile(ParamFileName);
		if(PFile.open(QIODevice::ReadOnly)==true){
			DLLPoint->LoadParam(&PFile);
		}
	}
	return(true);
}
void		PQSystemXMLLoader::Release(void)
{
	if(DLL_Release!=NULL && DLLPoint!=NULL){
		DLL_Release(DLLPoint);
		DLLPoint=NULL;
	}
}

WORD			PQSystemXMLLoader::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
const QString	PQSystemXMLLoader::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

bool	PQSystemXMLLoader::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"PQSystemXMLAccessor",DLLRoot,DLLName);
}
void	PQSystemXMLLoader::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetOrganization!=NULL){
		Str.append("DLL_GetOrganization");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_GetParamName!=NULL){
		Str.append("DLL_GetParamName");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Release!=NULL){
		Str.append("DLL_Release");
	}

	DLLManager::GetExportFunctions(Str);
}
