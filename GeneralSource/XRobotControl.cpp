/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XRobotClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XRobotClass.h"
#include "XRobotControl.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "Regulus64System.h"



//=============================================================================

RobotClass::RobotClass(LayersBase *base):ServiceForLayers(base)
{
	DLL_GetDLLType			=NULL;
	DLL_GetName				=NULL;
	DLL_GetVersion			=NULL;
	DLL_GetExplain			=NULL;
	DLL_CheckCopyright		=NULL;
	DLL_AssociateComponent	=NULL;
	DLL_Initial				=NULL;

	DLL_Close				=NULL;
	DLL_Load				=NULL;
	DLL_Save				=NULL;
	DLL_ShowSetting			=NULL;

	Handle					=NULL;
	LoadedDone				=false;
	Initialized				=false;
}
RobotClass::~RobotClass(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(Handle!=NULL){
		if(DLL_Close!=NULL){
			DLL_Close(Handle);
		}
	}		
	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}

bool	RobotClass::Initial(int32 &ErrorCode)
{
	if(IsRobotDLL()==true){
		Handle=DLL_Initial(GetLayersBase(),LoadingParameter);
		if(DLL_GetName!=NULL){
			DLL_GetName(DLLName);
		}
		if(Handle==NULL){
			return false;
		}
		return(true);		
	}

	return false;
}

bool	RobotClass::LoadDLL(int32 &ErrorCode,const QString &FileName,const QString &_LoadingParameter)
{
	DllLib.setFileName(FileName);
	if(DllLib.load()==false){
		ErrorCode=Error_Robot_NotLoaded;
		return(false);
	}
	RobotFileName=FileName;
	LoadingParameter=_LoadingParameter;

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_GetVersion;
		return(false);
	}
	DLL_AssociateComponent	=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Robot_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}

	DLL_Initial			=(RobotDLLBaseClass *(*)(LayersBase *base,const QString &RobotParamStr))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_Initial;
		return(false);
	}

	DLL_Close			=(bool (*)(RobotDLLBaseClass *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(RobotDLLBaseClass *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(RobotDLLBaseClass *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(RobotDLLBaseClass *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_Robot_NoFunc_DLL_ShowSetting;
		return(false);
	}

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(FileName);
	}
	LoadedDone=true;

	return true;
}


QString	RobotClass::GetName(void)
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	RobotClass::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	RobotClass::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	RobotClass::GetCopyright(void)
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}
void	RobotClass::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
const QString	RobotClass::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
bool	RobotClass::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"RobotDLL",/**/"",DLLName);
}

bool	RobotClass::IsRobotDLL(void)
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLRobotMode){
			return(true);
		}
	}
	return(false);
}

bool	RobotClass::Load(QIODevice *str)
{
	if(DLL_Load!=NULL){
		QString	tName;
		if(::Load(str,tName)==false){
			return false;
		}
		QString	sName;
		if(DLL_GetName!=NULL){
			MutexRobot.lock();
			DLL_GetName(sName);
			MutexRobot.unlock();
		}
		if(sName!=tName){
			return false;
		}
		MutexRobot.lock();
		bool	ret=DLL_Load(Handle,*str);
		MutexRobot.unlock();
		return ret;
	}
	return(false);
}
bool	RobotClass::Save(QIODevice *str)
{
	if(DLL_Save!=NULL){
		QString	tName;
		if(DLL_GetName!=NULL){
			MutexRobot.lock();
			DLL_GetName(tName);
			MutexRobot.unlock();
		}
		if(::Save(str,tName)==false){
			return false;
		}
		MutexRobot.lock();
		bool	ret=DLL_Save(Handle,*str);
		MutexRobot.unlock();
		return ret;
	}
	return(false);
}


bool	RobotClass::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle,parent));
	}
	return(false);
}

void	RobotClass::TransmitDirectly(GUIDirectMessage *packet)
{
	RobotDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		f->TransmitDirectly(packet);
	}
}
bool	RobotClass::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	RobotDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
	}
	return false;
}
bool	RobotClass::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	RobotDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	return false;
}
bool	RobotClass::Reallocate(int newPhaseNumb)
{
	RobotDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->Reallocate(newPhaseNumb);
	}
	return false;
}
void	RobotClass::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_Load!=NULL){
		Str.append("DLL_Load");
	}
	if(DLL_Save!=NULL){
		Str.append("DLL_Save");
	}
	if(DLL_ShowSetting!=NULL){
		Str.append("DLL_ShowSetting");
	}

	DLLManager::GetExportFunctions(Str);
}
//===========================================================================
RobotAccessList::RobotAccessList(LayersBase *base
									,const QString &_DLLPathFileName
									,const QString &_LoadingParameter
									,const QString &_UniqueCode)
	:ServiceForLayers(base)
	,Interface(new RobotClass(base))
{
	UniqueCode		=_UniqueCode;
	DLLPathFileName	=_DLLPathFileName;
	LoadingParameter=_LoadingParameter;
	Copied=false;
}
RobotAccessList::RobotAccessList(const RobotAccessList &src)
	:ServiceForLayers(src.GetLayersBase())
	,Interface(src.Interface)
{
	UniqueCode=src.UniqueCode;
	Copied=true;
}
RobotAccessList::~RobotAccessList(void)
{
	if(Copied==false){
		delete	Interface;
	}
	Interface=NULL;
}
void	RobotAccessList::AssociateComponent	(ComponentListContainer &List)
{
	if(Interface!=NULL){
		Interface->AssociateComponent(List);
	}
}

void	RobotAccessList::Set(const QString &_DLLFileName,const QString &_LoadingParameter,const QString &_UniqueName)
{
	UniqueCode		=_UniqueName;
	DLLPathFileName	=_DLLFileName;
	LoadingParameter=_LoadingParameter;
}

RobotAccessList	&RobotAccessList::operator=(const RobotAccessList &src)
{
	if(Copied==true){
		Interface=src.Interface;
	}
	UniqueCode=src.UniqueCode;
	return *this;
}
bool	RobotAccessList::Initial(int32 &ErrorCode)
{
	return Interface->Initial(ErrorCode);
}

bool	RobotAccessList::CheckSystemVersion(QStringList &Str)
{
	return Interface->CheckSystemVersion(Str);
}

bool	RobotAccessList::Load(QIODevice *str)
{
	if(::Load(str,UniqueCode		)==false)	return false;
	if(::Load(str,LoadingParameter	)==false)	return false;
	return Interface->Load(str);
}
bool	RobotAccessList::Save(QIODevice *str)
{
	if(::Save(str,UniqueCode		)==false)	return false;
	if(::Save(str,LoadingParameter	)==false)	return false;
	return Interface->Save(str);
}

bool	RobotAccessList::ShowSetting(QWidget *parent)
{
	return Interface->ShowSetting(parent);
}
RobotDLLBaseClass	*RobotAccessList::GetHandle(void)
{
	return Interface->GetHandle();
}

QString	RobotAccessList::GetDLLName(void)	const
{
	return Interface->GetDLLName();
}

bool	RobotAccessList::IsRobotDLL(void)	const
{
	return Interface->IsRobotDLL();
}
bool	RobotAccessList::LoadDLL(int32 &ErrorCode)
{
	QFileInfo	FInfo(DLLPathFileName);
	QString	Path;
	QString	DLLFileName;
	if(FInfo.isRelative()==true){
		Path=GetLayersBase()->GetSystemPath();
		if(Path.right(1)!="\\" && Path.right(1)!="/"){
			Path=Path+GetSeparator();
		}
		DLLFileName=Path+DefPluginDLLPath+GetSeparator()+DLLPathFileName;
	}
	else{
		DLLFileName=DLLPathFileName;
	}

	return Interface->LoadDLL(ErrorCode,DLLFileName,LoadingParameter);
}

void	RobotAccessList::GetExportFunctions(QStringList &Str)
{
	Interface->GetExportFunctions(Str);
}
QString	RobotAccessList::GetFileName(void)		const	{	return Interface->GetFileName();	}
QString	RobotAccessList::GetCopyright(void)		const	{	return Interface->GetCopyright();	}
QString	RobotAccessList::GetName(void)			const	{	return Interface->GetName();		}
WORD	RobotAccessList::GetVersion(void)		const	{	return Interface->GetVersion();		}
WORD	RobotAccessList::GetDLLType(void)		const	{	return Interface->GetDLLType();		}
QString	RobotAccessList::GetExplain(void)		const	{	return Interface->GetExplain();		}

bool	RobotAccessList::IsLoadedDone(void)		const	{	return Interface->IsLoadedDone();	}
void	RobotAccessList::SetLoadedDone(bool b)			{	return Interface->SetLoadedDone(b);	}

void	RobotAccessList::TransmitDirectly(GUIDirectMessage *packet)
{
	Interface->TransmitDirectly(packet);
}	
bool	RobotAccessList::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return Interface->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}
bool	RobotAccessList::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	return Interface->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
}
bool	RobotAccessList::Reallocate(int newPhaseNumb)
{
	return Interface->Reallocate(newPhaseNumb);
}

//===========================================================================
bool	RobotClassPack::CheckSystemVersion(QStringList &Str)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			return false;
		}
	}
	return true;
}
void	RobotClassPack::AssociateComponent	 (ComponentListContainer &List)
{
	for(RobotAccessList *L=GetFirst();L!=NULL;L=L->GetNext()){
		ComponentListContainer TmpList;
		L->AssociateComponent(TmpList);
		for(ComponentList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
			ComponentList	*Boss;
			for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
				if(*Boss==*L){
					break;
				}
			}
			if(Boss==NULL){
				ComponentList	*d=new ComponentList(*L);
				List.AppendList(d);
			}
		}
	}
}
bool		RobotClassPack::IsEmptyRobot(void)
{
	return IsEmpty();
}

int	RobotClassPack::SearchAddDLL(RobotInstanceParameter Param[] ,int ParamNumb,int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	int	LoadedCount=0;
	for(int i=0;i<ParamNumb;i++){
		QString	DLLPathFileName=Param[i].DLLFileName;
		QFileInfo	FInfo(DLLPathFileName);
		QString	Path;
		if(FInfo.isRelative()==true){
			QString	Path=GetLayersBase()->GetSystemPath();
			if(Path.right(1)!="\\" && Path.right(1)!="/"){
				Path=Path+GetSeparator();
			}
			Path=Path+DefPluginDLLPath;
		}
		else{
			Path=FInfo.path();
		}
		QDir	Dir;
		if(Dir.cd(Path)==true){
			QString	DLLFileName=FInfo.fileName();
			if(DLLFileName.isEmpty()==false){
				RobotAccessList	*a=new RobotAccessList(GetLayersBase()
														,Path+GetSeparator()+DLLFileName
														,Param[i].LoadingParameter
														,Param[i].UniqueCode);
				if(a->LoadDLL(ErrorCode)==true && a->IsRobotDLL()==true){
					AppendList(a);
					LoadedCount++;
				}
			}
		}
	}

	return LoadedCount;
}
/*
bool	RobotClassPack::Initial(int32 &ErrorCode ,int CoutOfRobot 
							,const QStringList &RobotDLLFileNameList 
							,const QStringList &RobotParamStrList)
{
	RemoveAll();

	for(int i=0;i<CoutOfRobot && i<RobotDLLFileNameList.count();i++){
		RobotAccessList	*a=new RobotAccessList(GetLayersBase());
		QString	RobotParamStr;
		if(i<RobotParamStrList.count()){
			RobotParamStr=RobotParamStrList[i];
		}
		QString	DLLFileName=RobotDLLFileNameList[i];
		if(a->Initial(DLLFileName,RobotParamStr,ErrorCode)==false){
			ErrorCode=Error_Robot_DLL_Initial;
			return false;
		}
		AppendList(a);
	}

	return true;
}
*/
bool	RobotClassPack::Initial(int32 &ErrorCode)
{
	bool	Ret=true;
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		RobotClass	*r=a->GetInterface();
		if(r->IsLoadedDone()==false){
			int32	ErrorCode;
			if(a->LoadDLL(ErrorCode)==false){
				Ret=false;
			}
		}
		if(r->IsLoadedDone()==true && r->IsInitialized()==false){
			int32	ErrorCode;
			if(a->Initial(ErrorCode)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	RobotClassPack::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}

	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->GetUniqueCode())==false){
			return false;
		}
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,a->GetDLLPathFileName())==false){
			return false;
		}
		if(::Save(&Buff,a->GetLoadingParameter())==false){
			return false;
		}
		a->Save(&Buff);
		QByteArray	BData=Buff.buffer();
		if(::Save(f,BData)==false){
			return false;
		}
	}

	return true;
}

bool	RobotClassPack::Load(QIODevice *f)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetLoadedDone(false);
	}

	int32	Ver=1;
	if(::Load(f,Ver)==false){
		return false;
	}

	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		QString	UniqueCode;
		if(::Load(f,UniqueCode)==false){
			return false;
		}
		QByteArray	BData;
		if(::Load(f,BData)==false){
			return false;
		}
		QBuffer	Buff(&BData);
		if(Buff.open(QIODevice::ReadOnly)==true){
			QString	DLLPathFileName;
			if(::Load(&Buff,DLLPathFileName)==false){
				return false;
			}
			QString	LoadingParameter;
			if(::Load(&Buff,LoadingParameter)==false){
				return false;
			}
			bool	Found=false;
			for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
				if(a->GetUniqueCode()==UniqueCode){
					a->Load(&Buff);
					a->SetLoadedDone(true);
					Found=true;
				}
			}
			if(Found==false){
				RobotAccessList	*a=new RobotAccessList(GetLayersBase(),DLLPathFileName,LoadingParameter,UniqueCode);
				int32	ErrorCode;
				if(a->LoadDLL(ErrorCode)==true && a->IsRobotDLL()==true){
					AppendList(a);
					if(a->Initial(ErrorCode)==true){
						a->SetLoadedDone(true);
					}
				}
			}
		}
	}

	return true;
}

void	RobotClassPack::LoopOnIdle(void)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		RobotDLLBaseClass	*V=a->GetHandle();
		if(V!=NULL){
			V->LoopOnIdle();
		}
	}
}

void	RobotClassPack::TransmitDirectly(GUIDirectMessage *packet)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

RobotDLLBaseClass	*RobotClassPack::GetRobot(int n)
{
	RobotAccessList *a=GetItem(n);
	return a->GetHandle();
}

RobotDLLBaseClass	*RobotClassPack::GetRobot(int n ,const QString &DLLName)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetName()==DLLName){
			if(n==0){
				return a->GetHandle();
			}
			n--;
		}
	}
	return NULL;
}
void	RobotClassPack::GetRobot(const QString &DLLName,IntList &RetN)
{
	int	n=0;
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext(),n++){
		if(a->GetName()==DLLName){
			RetN.Add(n);
		}
	}
}

RobotDLLBaseClass	*RobotClassPack::FindRobotByUniqueCode(const QString &UniqueCode)
{
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetUniqueCode()==UniqueCode){
			return a->GetHandle();
		}
	}
	return NULL;
}
	
bool	RobotClassPack::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	RobotClassPack::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	bool	Ret=true;
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	RobotClassPack::Reallocate(int newPhaseNumb)
{
	bool	Ret=true;
	for(RobotAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Reallocate(newPhaseNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
