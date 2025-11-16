#include "XPQRunnerController.h"
#include <QDir>

PQRunnerController::PQRunnerController(LayersBase *base)
	:ServiceForLayers(base)
{
	Runner				=NULL;
	DLL_GetName			=NULL;
	DLL_GetDLLType		=NULL;
	DLL_GetVersion		=NULL;
	DLL_GetSystemVersion=NULL;
	DLL_GetExplain		=NULL;
	DLL_SetLanguage		=NULL;
	DLL_CheckCopyright	=NULL;
	
	DLL_CreateRunner	=NULL;
	DLL_CloseRunner		=NULL;
	DLL_InitialQt		=NULL;
}

PQRunnerController::~PQRunnerController()
{
	if(Runner!=NULL){
		if(DLL_CloseRunner!=NULL){
			DLL_CloseRunner(Runner);
		}
		else{
			delete	Runner;
		}
		Runner=NULL;
	}
}

bool	PQRunnerController::LoadDLL(const QString &dllFileName)
{
	DLLFileName=dllFileName;
	DllLib.setFileName(DLLFileName);
	if(DllLib.load()==false)
		return(false);

	DLL_GetDLLType		=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		return false;
	}
	WORD	d=DLL_GetDLLType();
	if(d!=DLLPQSystemRunner){
		return false;
	}
	DLL_GetName			=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_GetSystemVersion=(const char *(*)(VersionType vtype))DllLib.resolve("DLL_GetSystemVersion");
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_SetLanguage		=(void (*) (LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_CheckCopyright	=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	
	DLL_CreateRunner	=(PQSystemRunner *(*)(LayersBase *Base))DllLib.resolve("DLL_CreateRunner");
	DLL_CloseRunner		=(void (*)(PQSystemRunner *handle))DllLib.resolve("DLL_CloseRunner");
	DLL_InitialQt		=(void (*)(QApplication *AppBase))DllLib.resolve("DLL_InitialQt");

	if(DLL_GetName==NULL){
		return false;
	}
	if(DLL_GetSystemVersion==NULL){
		return false;
	}
	if(DLL_CreateRunner==NULL){
		return false;
	}
	return true;
}
bool	PQRunnerController::Create(void)
{
	Runner=DLL_CreateRunner(GetLayersBase());
	if(Runner==NULL){
		return false;
	}
	return true;
}

bool	PQRunnerController::InitialRunner(void)
{
	if(Runner!=NULL){
		return Runner->Initial();
	}
	return false;
}
bool	PQRunnerController::SetLanguage(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		return true;
	}
	return false;
}

//=======================================================================
PQRunnerControllerContainer::PQRunnerControllerContainer(LayersBase *base)
	:ServiceForLayers(base)
{
}
PQRunnerControllerContainer::~PQRunnerControllerContainer ()
{
}
bool	PQRunnerControllerContainer::SetLanguage(int LanguageCode)
{
	bool	Ret=true;
	for(PQRunnerController *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->SetLanguage(LanguageCode)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	PQRunnerControllerContainer::LoadDLL(const QString &DLLPath)
{
	QDir	cd(DLLPath);
	QStringList Files=cd.entryList(QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<Files.count();i++){
		QString	FileName=DLLPath+QDir::separator()+Files[i];
		PQRunnerController	*L=new PQRunnerController(GetLayersBase());
		if(L->LoadDLL(FileName)==false){
			delete	L;
		}
		else{
			AppendList(L);
		}
	}
	QStringList Folders=cd.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<Folders.count();i++){
		QString	FolderName=DLLPath+QDir::separator()+Folders[i];
		LoadDLL(FolderName);
	}
	return true;
}

