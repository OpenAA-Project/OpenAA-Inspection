#include "XTypeDef.h"
#include "XShadowControlInterface.h"
//#include "XShadowControlDLL.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include <QFile>

ShadowControlInterface::ShadowControlInterface(int ShadowNumber ,LayersBase *base)
	:ServiceForLayers(base)
{
	InFunc				=false;
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_GetExplain		=NULL;
	DLL_SetLanguage		=NULL;
	DLL_CheckCopyright	=NULL;

	DLL_Initial			=NULL;
	DLL_Close			=NULL;
	DLL_ShowSetting		=NULL;
	Inst				=NULL;
}
ShadowControlInterface::ShadowControlInterface(const ShadowControlInterface &src)
:ServiceForLayers(src.GetLayersBase())
{
	InFunc				=false;
	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetVersion		=NULL;
	DLL_GetExplain		=NULL;
	DLL_SetLanguage		=NULL;
	DLL_CheckCopyright	=NULL;

	DLL_Initial			=NULL;
	DLL_Close			=NULL;
	DLL_ShowSetting		=NULL;
	Inst				=NULL;

	if(src.Inst!=NULL){
		int32	ErrorCode;
		LoadDLL(LibraryFileName,ErrorCode);

		Initial(src.Inst->GetShadowNumber(),src.Inst->GetParentLayersBase()
											,src.Inst->GetShadowGlobalFileName()
											,src.Inst->GetShadowGUIFileName());
	}
}
ShadowControlInterface::~ShadowControlInterface(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(Inst!=NULL){
		delete	Inst;
		Inst=NULL;
	}
	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}
ShadowControlInterface	&ShadowControlInterface::operator=(const ShadowControlInterface &src)
{
	if(src.Inst!=NULL){
		int32	ErrorCode;
		LoadDLL(LibraryFileName,ErrorCode);

		Initial(src.Inst->GetShadowNumber(),src.Inst->GetParentLayersBase()
											,src.Inst->GetShadowGlobalFileName()
											,src.Inst->GetShadowGUIFileName());
	}
	else{
		if(Inst!=NULL){
			delete	Inst;
			Inst=NULL;
		}
		if(DllLib.isLoaded()==true){
			DllLib.unload();	//Error occurs in final DLL unload
		}
		InFunc				=false;
		DLL_GetDLLType		=NULL;
		DLL_GetName			=NULL;
		DLL_GetVersion		=NULL;
		DLL_GetExplain		=NULL;
		DLL_SetLanguage		=NULL;
		DLL_CheckCopyright	=NULL;

		DLL_Initial			=NULL;
		DLL_Close			=NULL;
		DLL_ShowSetting		=NULL;
	}
	return *this;
}
bool	ShadowControlInterface::LoadDLL(const QString &dllfilename,int32 &ErrorCode)
{
	LibraryFileName	=dllfilename;
	DllLib.setFileName(dllfilename);
	if(DllLib.load()==false)
		return(false);
	DLL_GetDLLType		=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetName			=(bool (*)(QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_SetLanguage		=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_CheckCopyright	=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");

	DLL_Initial			=(ShadowTree *(*)(int ShadowNumber,LayersBase *ParentBase
										,const QString &,const QString &))DllLib.resolve("DLL_Initial");
	DLL_Close			=(bool (*)(ShadowTree *handle))DllLib.resolve("DLL_Close");
	DLL_ShowSetting		=(bool (*)(ShadowTree *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");

	return true;
}

bool	ShadowControlInterface::SetLanguageCode(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		InFunc=true;
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		InFunc=false;
		return true;
	}
	return false;
}

QString	ShadowControlInterface::GetLibraryFileName(void)
{	
	return LibraryFileName;
}
QString	ShadowControlInterface::GetCopyright(void)
{
	if(DLL_CheckCopyright!=NULL){
		InFunc=true;
		QString	CopyrightString;
		bool	ret=DLL_CheckCopyright(CopyrightString);
		InFunc=false;
		return CopyrightString;
	}
	return /**/"";
}
QString	ShadowControlInterface::GetName(void)
{
	if(DLL_GetName!=NULL){
		InFunc=true;
		QString	Name;
		bool	ret=DLL_GetName(Name);
		InFunc=false;
		return Name;
	}
	return /**/"";
}
WORD	ShadowControlInterface::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetVersion();
		InFunc=false;
		return ret;
	}
	return 0;
}
WORD	ShadowControlInterface::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		InFunc=true;
		WORD	ret=DLL_GetDLLType();
		InFunc=false;
		return ret;
	}
	return 0;
}
const QString	ShadowControlInterface::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		InFunc=true;
		const char	*c=DLL_GetExplain();
		InFunc=false;	
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
ShadowTree	*ShadowControlInterface::Initial(int ShadowNumber,LayersBase *ParentBase 
											,const QString &GlobalParamFileName
											,const QString &ShadowGUIFileName)
{
	if(DLL_Initial!=NULL){
		InFunc=true;
		Inst=DLL_Initial(ShadowNumber,ParentBase
						,GlobalParamFileName
						,ShadowGUIFileName);
		if(Inst!=NULL){
			if(GlobalParamFileName.isEmpty()==false){
				Inst->SetShadowGlobalFileName	(GlobalParamFileName);
			}
			else{
				Inst->SetShadowGlobalFileName	(Inst->GetParentLayersBase()->GetParamGlobal()->GetDefaultFileName());
			}
			if(ShadowGUIFileName.isEmpty()==false){
				Inst->SetShadowGUIFileName	(ShadowGUIFileName);
			}
			else{
				Inst->SetShadowGUIFileName	(Inst->GetParentLayersBase()->GetGUIFileName());
			}
		}
		InFunc=false;
		return Inst;
	}
	return NULL;
}
bool	ShadowControlInterface::Close(ShadowTree *handle)
{
	if(DLL_Close!=NULL){
		InFunc=true;
		bool	ret=DLL_Close(handle);
		InFunc=false;
		return ret;
	}
	return true;
}

bool	ShadowControlInterface::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		InFunc=true;
		bool	ret=DLL_ShowSetting(Inst,parent);
		InFunc=false;
		return ret;
	}
	return false;
}
//===================================================================
ShadowControlInterfaceContainer::ShadowControlInterfaceContainer(LayersBase *base)
:ServiceForLayers(base)
{
}
ShadowControlInterfaceContainer::ShadowControlInterfaceContainer(const ShadowControlInterfaceContainer &src)
:ServiceForLayers(src.GetLayersBase())
{
	for(ShadowControlInterface *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()!=NULL){
			ShadowControlInterface	*d=new ShadowControlInterface(*c);
			AppendList(d);
		}
	}
}

ShadowControlInterfaceContainer	&ShadowControlInterfaceContainer::operator=(const ShadowControlInterfaceContainer &src)
{
	RemoveAll();
	for(ShadowControlInterface *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()!=NULL){
			ShadowControlInterface	*d=new ShadowControlInterface(*c);
			AppendList(d);
		}
	}
	return *this;
}

bool	ShadowControlInterfaceContainer::InitialDLL(void)
{
	RemoveAll();

	int	N=0;
	for(ShadowParameter *s=GetParamGlobal()->ShadowParameterData.GetFirst();s!=NULL;s=s->GetNext(),N++){
		ShadowControlInterface	*c=new ShadowControlInterface(N,GetLayersBase());
		c->SetLanguageCode(GetLayersBase()->GetLanguageCode());
		int32	ErrorCode;
		if(c->LoadDLL(s->ShadowControlDLLFileName,ErrorCode)==true){
			ShadowTree	*t=c->Initial(N,GetLayersBase()
										,s->ShadowGlobalFileName
										,s->ShadowGUIFileName);
			if(t!=NULL){
				t->SetShadowDLLFileName(s->ShadowControlDLLFileName);
				t->SetInterface(c);
				t->SetParam	(*s);
				AppendList(c);
			}
		}
		else{
			delete	c;
		}
	}
	bool	Ret=true;
	for(ShadowControlInterface *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()!=NULL){
			if(c->GetInstance()->InitialInShadow()==false){
				Ret=false;
			}
			c->GetInstance()->GetTreeLayersBase()->CloseInformed();
		}
	}
	return Ret;
}
bool	ShadowControlInterfaceContainer::SaveShadowParam(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(ShadowControlInterface *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()!=NULL){
			QString	SName=c->GetName();
			if(::Save(f,SName)==false){
				return false;
			}
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			if(c->GetInstance()->SaveShadowParam(&Buff)==false){
				return false;
			}
			QByteArray	A=Buff.buffer();
			if(::Save(f,A)==false){
				return false;
			}
		}
	}
	return true;
}
bool	ShadowControlInterfaceContainer::LoadShadowParam(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	IntList	LoadedList;
	for(int i=0;i<N;i++){
		QString	SName;
		if(::Load(f,SName)==false){
			return false;
		}
		QByteArray	A;
		if(::Load(f,A)==false){
			return false;
		}

		int	n=0;
		for(ShadowControlInterface *c=GetFirst();c!=NULL;c=c->GetNext(),n++){
			if(LoadedList.IsInclude(n)==true)
				continue;
			if(c->GetName()==SName){
				QBuffer	Buff(&A);
				Buff.open(QIODevice::ReadOnly);
				if(c->GetInstance()->LoadShadowParam(&Buff)==false){
					return false;
				}
				LoadedList.Add(n);
				break;
			}
		}
	}
	return true;
}