/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLightClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XLightClass.h"
#include "XLightInterfaceDLL.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "Regulus64System.h"

bool	LightDLLBaseClass::ReflectDataInDialog(void)
{
	emit	SignalReflectDataInDialog();
	return true;
}

bool	LightDLLBaseClass::ReflectOnOffInDialog(bool LightOn)
{
	emit	SignalReflectOnOffInDialog(LightOn);
	return true;
}

//=============================================================================

LightClass::LightClass(LayersBase *base):ServiceForLayers(base)
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
	DLL_GetLightPatternCount=NULL;
	DLL_LightOn				=NULL;
	DLL_LightOff			=NULL;
	DLL_SetPattern			=NULL;
	DLL_ReqLightError		=NULL;
	Handle					=NULL;
	PatternNo				=0;
	OnOff					=true;
	OutputMode				=true;
	LoadedDone				=false;
}
LightClass::~LightClass(void)
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

bool	LightClass::Initial(const QString &DLLFileName ,const QString Parameter 
							,int32 &ErrorCode,bool _OutputMode)
{
	OutputMode	=_OutputMode;
	QString	FileName;
	QFileInfo fi(DLLFileName);
	if(fi.suffix().isEmpty()==true){
		FileName=GetLayersBase()->GetSystemPath()+GetSeparator()
				+DLLFileName+QString(".")+GetDynamicFileExt();
	}
	else{
		FileName=GetLayersBase()->GetSystemPath()+GetSeparator()
				+DLLFileName;
	}
	GetLayersBase()->TestLoadDLL(FileName);

	return LoadDLLLibrary(ErrorCode,FileName,Parameter);
}

bool	LightClass::InitialStraightPath(const QString &DLLFileName ,const QString Parameter 
							,int32 &ErrorCode,bool _OutputMode)
{
	OutputMode	=_OutputMode;
	GetLayersBase()->TestLoadDLL(DLLFileName);

	return LoadDLLLibrary(ErrorCode,DLLFileName,Parameter);
}


bool	LightClass::LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter)
{
	if(QLibrary::isLibrary(FileName)==true){
		if(LoadDLL(FileName,ErrorCode)==false){
			return(false);
		}
		if(IsLightDLL()==true){
			Handle=DLL_Initial(GetLayersBase(),Parameter,OutputMode);
			if(DLL_GetName!=NULL){
				DLL_GetName(DLLName);
			}
			if(Handle==NULL){
				return false;
			}
			return(true);		
		}
	}
	return(false);
}

bool	LightClass::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		ErrorCode=Error_Light_NotLoaded;
		return(false);
	}
	LightFileName=filename;

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_GetVersion;
		return(false);
	}
	DLL_AssociateComponent	=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Light_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}

	DLL_Initial			=(LightDLLBaseClass *(*)(LayersBase *base,const QString &LightParamStr,bool OutputMode))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_Initial;
		return(false);
	}

	DLL_Close			=(bool (*)(LightDLLBaseClass *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(LightDLLBaseClass *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(LightDLLBaseClass *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(LightDLLBaseClass *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_ShowSetting;
		return(false);
	}
	DLL_GetLightPatternCount=(int (*)(LightDLLBaseClass *handle))DllLib.resolve("DLL_GetLightPatternCount");
	if(DLL_GetLightPatternCount==NULL){
		ErrorCode=Error_Light_NoFunc_DLL_GetLightPatternCount;
		return(false);
	}
	DLL_LightOn			=(bool (*)(LightDLLBaseClass *handle))DllLib.resolve("DLL_LightOn");
	DLL_LightOff		=(bool (*)(LightDLLBaseClass *handle))DllLib.resolve("DLL_LightOff");
	DLL_SetPattern		=(bool (*)(LightDLLBaseClass *handle,int PatternNo))DllLib.resolve("DLL_SetPattern");
	DLL_ReqLightError	=(bool (*)(LightDLLBaseClass *handle,QStringList &Msg))DllLib.resolve("DLL_ReqLightError");

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return true;
}


QString	LightClass::GetName(void)
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	LightClass::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	LightClass::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	LightClass::GetCopyright(void)
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}
void	LightClass::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
const QString	LightClass::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
bool	LightClass::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"LightDLL",/**/"",DLLName);
}

bool	LightClass::IsLightDLL(void)
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLLightMode){
			return(true);
		}
	}
	return(false);
}

bool	LightClass::Load(QIODevice *str)
{
	if(DLL_Load!=NULL){
		QString	tName;
		if(::Load(str,tName)==false){
			return false;
		}
		QString	sName;
		if(DLL_GetName!=NULL){
			MutexLight.lock();
			DLL_GetName(sName);
			MutexLight.unlock();
		}
		if(sName!=tName){
			return false;
		}
		MutexLight.lock();
		bool	ret=DLL_Load(Handle,*str);
		MutexLight.unlock();
		return ret;
	}
	return(false);
}
bool	LightClass::Save(QIODevice *str)
{
	if(DLL_Save!=NULL){
		QString	tName;
		if(DLL_GetName!=NULL){
			MutexLight.lock();
			DLL_GetName(tName);
			MutexLight.unlock();
		}
		if(::Save(str,tName)==false){
			return false;
		}
		MutexLight.lock();
		bool	ret=DLL_Save(Handle,*str);
		MutexLight.unlock();
		return ret;
	}
	return(false);
}


bool	LightClass::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle,parent));
	}
	return(false);
}

int		LightClass::GetLightPatternCount(void)
{
	if(DLL_GetLightPatternCount!=NULL){
		MutexLight.lock();
		int	ret=DLL_GetLightPatternCount(Handle);
		MutexLight.unlock();
		return ret;
	}
	return 0;
}
bool	LightClass::LightOn(void)
{
	if(DLL_LightOn!=NULL){
		MutexLight.lock();
		OnOff=true;
		bool	ret=DLL_LightOn(Handle);
		MutexLight.unlock();
		return ret;
	}
	return false;
}
bool	LightClass::LightOff(void)
{
	if(DLL_LightOff!=NULL){
		MutexLight.lock();
		OnOff=false;
		bool	ret=DLL_LightOff(Handle);
		MutexLight.unlock();
		return ret;
	}
	return false;
}
bool	LightClass::SetPattern(int _PatternNo)
{
	if(DLL_SetPattern!=NULL){
		int	MaxPattern=GetLightPatternCount();
		if(_PatternNo<0 || MaxPattern<=_PatternNo){
			return false;
		}
		MutexLight.lock();
		PatternNo=_PatternNo;
		bool	ret=DLL_SetPattern(Handle ,_PatternNo);
		MutexLight.unlock();
		return ret;
	}
	return false;
}
bool	LightClass::ReqLightError(QStringList &Msg)
{
	if(DLL_ReqLightError!=NULL){
		MutexLight.lock();
		bool	ret=DLL_ReqLightError(Handle ,Msg);
		MutexLight.unlock();
		return ret;
	}
	return false;
}

void	LightClass::TransmitDirectly(GUIDirectMessage *packet)
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		f->TransmitDirectly(packet);
	}
}
bool	LightClass::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
	}
	return false;
}
bool	LightClass::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	return false;
}
bool	LightClass::Reallocate(int newPhaseNumb)
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->Reallocate(newPhaseNumb);
	}
	return false;
}

bool	LightClass::InsertPage(int IndexPage)	//Create page before Indexed page
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->InsertPage(IndexPage);
	}
	return false;
}
bool	LightClass::RemovePage(int IndexPage)
{
	LightDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		return f->RemovePage(IndexPage);
	}
	return false;
}

void	LightClass::GetExportFunctions(QStringList &Str)
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
	if(DLL_GetLightPatternCount!=NULL){
		Str.append("DLL_GetLightPatternCount");
	}
	if(DLL_LightOn!=NULL){
		Str.append("DLL_LightOn");
	}
	if(DLL_LightOff!=NULL){
		Str.append("DLL_LightOff");
	}
	if(DLL_SetPattern!=NULL){
		Str.append("DLL_SetPattern");
	}
	if(DLL_ReqLightError!=NULL){
		Str.append("DLL_ReqLightError");
	}
	DLLManager::GetExportFunctions(Str);
}
//===========================================================================
LightAccessList::LightAccessList(LayersBase *base)
	:ServiceForLayers(base)
	,Interface(new LightClass(base))
{
	Copied=false;
}
LightAccessList::LightAccessList(const LightAccessList &src)
	:ServiceForLayers(src.GetLayersBase())
	,Interface(src.Interface)
{
	Copied=true;
}
LightAccessList::~LightAccessList(void)
{
	if(Copied==false){
		delete	Interface;
	}
	Interface=NULL;
}
void	LightAccessList::AssociateComponent	(ComponentListContainer &List)
{
	if(Interface!=NULL){
		Interface->AssociateComponent(List);
	}
}
LightAccessList	&LightAccessList::operator=(const LightAccessList &src)
{
	if(Copied==true){
		Interface=src.Interface;
	}
	return *this;
}
bool	LightAccessList::Initial(const QString &DLLFileName ,const QString &Parameter 
								,int32 &ErrorCode ,bool OutputMode)
{
	return Interface->Initial(DLLFileName ,Parameter ,ErrorCode ,OutputMode);
}
bool	LightAccessList::InitialStraightPath(const QString &DLLFileName ,const QString &Parameter 
											,int32 &ErrorCode,bool _OutputMode)
{
	return Interface->InitialStraightPath(DLLFileName ,Parameter ,ErrorCode ,_OutputMode);
}

bool	LightAccessList::CheckSystemVersion(QStringList &Str)
{
	return Interface->CheckSystemVersion(Str);
}

bool	LightAccessList::Load(QIODevice *str)
{
	return Interface->Load(str);
}
bool	LightAccessList::Save(QIODevice *str)
{
	return Interface->Save(str);
}

bool	LightAccessList::ShowSetting(QWidget *parent)
{
	return Interface->ShowSetting(parent);
}
LightDLLBaseClass	*LightAccessList::GetHandle(void)
{
	return Interface->GetHandle();
}
int		LightAccessList::GetLightPatternCount(void)
{
	return Interface->GetLightPatternCount();
}
bool	LightAccessList::LightOn(void)
{
	return Interface->LightOn();
}
bool	LightAccessList::LightOff(void)
{
	return Interface->LightOff();
}
bool	LightAccessList::SetPattern(int PatternNo)
{
	return Interface->SetPattern(PatternNo);
}
bool	LightAccessList::ReqLightError(QStringList &Msg)
{
	return Interface->ReqLightError(Msg);
}

int		LightAccessList::GetPatternNo(void)
{
	return Interface->GetPatternNo();
}
bool	LightAccessList::IsTurnOn(void)
{
	return Interface->IsTurnOn();
}
QString	LightAccessList::GetDLLName(void)	const
{
	return Interface->GetDLLName();
}

bool	LightAccessList::IsLightDLL(void)	const
{
	return Interface->IsLightDLL();
}
bool	LightAccessList::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	return Interface->LoadDLL(filename ,ErrorCode);
}
bool	LightAccessList::LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString &Parameter)
{
	return Interface->LoadDLLLibrary(ErrorCode,FileName,Parameter);
}

void	LightAccessList::GetExportFunctions(QStringList &Str)
{
	Interface->GetExportFunctions(Str);
}
QString	LightAccessList::GetFileName(void)		const	{	return Interface->GetFileName();	}
QString	LightAccessList::GetCopyright(void)		const	{	return Interface->GetCopyright();	}
QString	LightAccessList::GetName(void)			const	{	return Interface->GetName();		}
WORD	LightAccessList::GetVersion(void)		const	{	return Interface->GetVersion();		}
WORD	LightAccessList::GetDLLType(void)		const	{	return Interface->GetDLLType();		}
QString	LightAccessList::GetExplain(void)		const	{	return Interface->GetExplain();		}

bool	LightAccessList::IsLoadedDone(void)		const	{	return Interface->IsLoadedDone();	}
void	LightAccessList::SetLoadedDone(bool b)			{	return Interface->SetLoadedDone(b);	}

void	LightAccessList::TransmitDirectly(GUIDirectMessage *packet)
{
	Interface->TransmitDirectly(packet);
}	
bool	LightAccessList::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return Interface->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}
bool	LightAccessList::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	return Interface->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
}
bool	LightAccessList::Reallocate(int newPhaseNumb)
{
	return Interface->Reallocate(newPhaseNumb);
}
bool	LightAccessList::InsertPage(int IndexPage)	//Create page before Indexed page
{
	return Interface->InsertPage(IndexPage);
}
bool	LightAccessList::RemovePage(int IndexPage)
{
	return Interface->InsertPage(IndexPage);
}
//===========================================================================
bool	LightClassPack::CheckSystemVersion(QStringList &Str)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			return false;
		}
	}
	return true;
}
void	LightClassPack::AssociateComponent	 (ComponentListContainer &List)
{
	for(LightAccessList *L=GetFirst();L!=NULL;L=L->GetNext()){
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
bool		LightClassPack::IsEmptyLight(void)
{
	return IsEmpty();
}

int	LightClassPack::SearchAddDLL(int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+DefPluginDLLPath;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				LightAccessList	*a=new LightAccessList(GetLayersBase());
				if(a->LoadDLL(FileName,ErrorCode)==true && a->IsLightDLL()==true){
					AppendList(a);
					Ret++;
				}
				else{
					delete	a;
				}
			}
		}
	}
	return Ret;
}
bool	LightClassPack::Initial(int32 &ErrorCode ,bool OutputMode)
{
	RemoveAll();

	if(GetParamGlobal()->LightDLLFileName.isEmpty()==false){
		LightAccessList	*a=new LightAccessList(GetLayersBase());
		if(a->Initial(GetParamGlobal()->LightDLLFileName,GetParamGlobal()->LightParamStr,ErrorCode,OutputMode)==false){
			ErrorCode=Error_Light_DLL_Initial1;
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->LightDLLFileName2.isEmpty()==false){
		LightAccessList	*a=new LightAccessList(GetLayersBase());
		if(a->Initial(GetParamGlobal()->LightDLLFileName2,GetParamGlobal()->LightParamStr2,ErrorCode,OutputMode)==false){
			ErrorCode=Error_Light_DLL_Initial2;
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->LightDLLFileName3.isEmpty()==false){
		LightAccessList	*a=new LightAccessList(GetLayersBase());
		if(a->Initial(GetParamGlobal()->LightDLLFileName3,GetParamGlobal()->LightParamStr3,ErrorCode,OutputMode)==false){
			ErrorCode=Error_Light_DLL_Initial3;
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->LightDLLFileName4.isEmpty()==false){
		LightAccessList	*a=new LightAccessList(GetLayersBase());
		if(a->Initial(GetParamGlobal()->LightDLLFileName4,GetParamGlobal()->LightParamStr4,ErrorCode,OutputMode)==false){
			ErrorCode=Error_Light_DLL_Initial4;
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	LightClassPack::LightOn(void)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LightOn()==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LightClassPack::LightOff(void)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LightOff()==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	LightClassPack::SetPattern(int PatternNo)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->SetPattern(PatternNo)==false){
			return false;
		}
	}
	return true;
}

int		LightClassPack::GetPatternNo(void)
{
	if(GetFirst()!=NULL){
		return GetFirst()->GetPatternNo();
	}
	return -1;
}

bool	LightClassPack::IsTurnOn(void)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsTurnOn()==true){
			return true;
		}
	}
	return false;
}

bool	LightClassPack::Save(QIODevice *f)
{
	if(GetCount()==1){
		if(GetFirst()->Save(f)==false){
			return false;
		}
		return true;
	}
	else if(GetCount()>1){
		int32	Ver=1;
		if(::Save(f,Ver)==false){
			return false;
		}

		int32	N=0;
		for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetHandle()!=NULL){
				N++;
			}
		}
		if(::Save(f,N)==false){
			return false;
		}
		for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetHandle()!=NULL){
				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				if(::Save(&Buff,a->GetDLLName())==false){
					return false;
				}
				a->Save(&Buff);
				QByteArray	BData=Buff.buffer();
				if(::Save(f,BData)==false){
					return false;
				}
			}
		}
	}
	return true;
}

bool	LightClassPack::Load(QIODevice *f)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetLoadedDone(false);
	}

	if(GetCount()==1){
		if(GetFirst()->Load(f)==false){
			int32	Ver;
			if(::Load(f,Ver)==false){
				return false;
			}
			if(Ver>1 || Ver<=0){
				return false;
			}
			int32	N;
			if(::Load(f,N)==false){
				return false;
			}
			for(int i=0;i<N;i++){
				QByteArray	BData;
				if(::Load(f,BData)==false){
					return false;
				}
				QBuffer	Buff(&BData);
				Buff.open(QIODevice::ReadOnly);
				QString	DLLName;
				if(::Load(&Buff,DLLName)==false){
					return false;
				}
				if(GetFirst()->GetDLLName()==DLLName){
					if(GetFirst()->Load(&Buff)==false){
						return false;
					}
					GetFirst()->SetLoadedDone(true);
				}
			}
			return true;
		}
		return true;
	}
	else if(GetCount()>1){
		int32	Ver;
		if(::Load(f,Ver)==false){
			return false;
		}
		if(Ver>1 || Ver<=0){
			return false;
		}
		int32	N;
		if(::Load(f,N)==false){
			return false;
		}
		for(int i=0;i<N;i++){
			QByteArray	BData;
			if(::Load(f,BData)==false){
				return false;
			}
			QBuffer	Buff(&BData);
			Buff.open(QIODevice::ReadOnly);
			QString	DLLName;
			if(::Load(&Buff,DLLName)==false){
				return false;
			}
			for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
				if(a->GetDLLName()==DLLName && a->IsLoadedDone()==false){
					if(a->Load(&Buff)==false){
						return false;
					}
					a->SetLoadedDone(true);
					break;
				}
			}
		}
		return true;
	}			
	return true;
}

void	LightClassPack::LoopOnIdle(void)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		LightDLLBaseClass	*V=a->GetHandle();
		if(V!=NULL){
			V->LoopOnIdle();
		}
	}
}

void	LightClassPack::TransmitDirectly(GUIDirectMessage *packet)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

LightDLLBaseClass	*LightClassPack::GetLight(int n)
{
	LightAccessList *a=GetItem(n);
	return a->GetHandle();
}

LightDLLBaseClass	*LightClassPack::GetLight(int n ,const QString &DLLName)
{
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetName()==DLLName){
			if(n==0){
				return a->GetHandle();
			}
			n--;
		}
	}
	return NULL;
}
void	LightClassPack::GetLight(const QString &DLLName,IntList &RetN)
{
	int	n=0;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext(),n++){
		if(a->GetName()==DLLName){
			RetN.Add(n);
		}
	}
}
	
bool	LightClassPack::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	LightClassPack::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	LightClassPack::Reallocate(int newPhaseNumb)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Reallocate(newPhaseNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
	
bool	LightClassPack::InsertPage(int IndexPage)	//Create page before Indexed page
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->InsertPage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LightClassPack::RemovePage(int IndexPage)
{
	bool	Ret=true;
	for(LightAccessList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->RemovePage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}