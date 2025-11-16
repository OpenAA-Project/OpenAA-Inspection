#include"XPQSystemRunnerLoader.h"
#include "XPQSystemResult.h"
#include "XPQSystemRunner.h"
#include "XDLLType.h"
#include <QFile>
#include <QDir>
#include "XGeneralFunc.h"

PQSystemRunnerLoader::PQSystemRunnerLoader(PQSystemBase *Base)
	:PQSystemBaseService(Base)
{
	DLL_GetOrganization	=NULL;
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_SetLanguage		=NULL;
	DLL_GetExplain		=NULL;
	DLL_CheckCopyright	=NULL;
	DLL_AllocateRunner	=NULL;
	DLL_Release			=NULL;

	Pointer	=NULL;
}
PQSystemRunnerLoader::~PQSystemRunnerLoader(void)
{
}

bool		PQSystemRunnerLoader::LoadDLL(const QString &filename)
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
	DLL_AllocateRunner			=(PQSystemRunner	*(*)(PQSystemBase *Base))DllLib.resolve("DLL_AllocateRunner");
	DLL_Release					=(bool (*)(PQSystemRunner *pointer))DllLib.resolve("DLL_Release");
	return true;
}

bool		PQSystemRunnerLoader::Initial(void)
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

	if(DLL_AllocateRunner!=NULL){
		if(Pointer!=NULL){
			if(DLL_Release!=NULL){
				DLL_Release(Pointer);
			}
			Pointer=NULL;
		}
		Pointer	=DLL_AllocateRunner(GetPQSystemBase());
		if(Pointer==NULL){
			return false;
		}
	}

	if(Pointer!=NULL && ParamFileName.isEmpty()==false){
		QFile	PFile(ParamFileName);
		if(PFile.open(QIODevice::ReadOnly)==true){
			Pointer->LoadParam(&PFile);
		}
	}
	return(true);
}
void		PQSystemRunnerLoader::Release(void)
{
	if(DLL_Release!=NULL && Pointer!=NULL){
		DLL_Release(Pointer);
		Pointer=NULL;
	}
}

WORD			PQSystemRunnerLoader::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
const QString	PQSystemRunnerLoader::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

bool	PQSystemRunnerLoader::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"PQSystemRunner",DLLRoot,DLLName);
}
void	PQSystemRunnerLoader::GetExportFunctions(QStringList &Str)
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
	if(DLL_AllocateRunner!=NULL){
		Str.append("DLL_AllocateRunner");
	}

	DLLManager::GetExportFunctions(Str);
}

//==========================================================================================

PQSystemRunnerLoaderContainer::PQSystemRunnerLoaderContainer(PQSystemBase *Base)
	:PQSystemBaseService(Base)
{
}
PQSystemRunnerLoaderContainer::~PQSystemRunnerLoaderContainer(void)
{
	for(PQSystemRunnerLoader *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Release();
	}
}

int	PQSystemRunnerLoaderContainer::LoadAllDLL(const QString &RelativePath)
{
	QDir	Dir;

	Dir.cd(RelativePath);
	QString	SearchFile=QString("*.")+GetDynamicFileExt();
	QStringList nameFilters(SearchFile);
	QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );
	int	N=0;
	for(int i=0;i<List.size();i++){
		QString	FileName=RelativePath+QString(GetSeparator())+List.at(i);
		if(QLibrary::isLibrary(FileName)==true){
			PQSystemRunnerLoader	*DLL=new PQSystemRunnerLoader(GetPQSystemBase());
			DLL->SetFileName(FileName);
			printf("PQSystemRunnerDLL\n");
			if(DLL->LoadDLL(FileName)==true){
				printf("LoadDLL OK\n");
				if(DLL->GetDLLType()==DLLPQSystemRunner){
					printf("Initialc\n");
					DLL->Initial();

					printf("AppendList\n");
					AppendList(DLL);
					N++;
				}
				else{
					delete	DLL;
				}
			}
			else{
				delete	DLL;
			}
		}
	}

	Classified.RemoveAll();
	for(PQSystemRunnerLoader *a=GetFirst();a!=NULL;a=a->GetNext()){
		PQSystemRunnerLoaderClassified *c;
		for(c=Classified.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetDLLRoot()==a->GetDLLRoot()){
				break;
			}
		}
		if(c==NULL){
			c=new PQSystemRunnerLoaderClassified(a->GetDLLRoot());
			Classified.AppendList(c);
		}
		c->AppendList(new PQSystemRunnerLoaderPointer(a));
	}
	for(PQSystemRunnerLoaderClassified *c=Classified.GetFirst();c!=NULL;c=c->GetNext()){
		c->Sort();
	}
	Classified.Sort();


	return(N);
}

//===============================================================================
int	PQSystemRunnerLoaderPointer::Compare(PQSystemRunnerLoaderPointer &src)
{
	if(GetDLLName()<src.GetDLLName())
		return -1;
	else if(GetDLLName()>src.GetDLLName())
		return 1;
	return 0;
}

int	PQSystemRunnerLoaderClassified::Compare(PQSystemRunnerLoaderClassified &src)
{
	if(GetDLLRoot()<src.GetDLLRoot())
		return -1;
	else if(GetDLLRoot()>src.GetDLLRoot())
		return 1;
	return 0;
}