/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFilterManager.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XFilterManager.h"
#include <QtGui>
#include <QIODevice>
#include <QFile>
#include <QFileInfo>
#include <QApplication>
#include <QProgressBar>
#include <QSqlDatabase>
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XFilterInstance.h"

FilterDLLList::FilterDLLList(LayersBase *base ,const QString &dllfilename)
	:ServiceForLayers(base)
{
	DLL_GetDLLType			=NULL;
	DLL_GetName				=NULL;
	DLL_GetVersion			=NULL;
	DLL_GetExplain			=NULL;
	DLL_SetLanguage			=NULL;
	DLL_CheckCopyright		=NULL;
	DLL_AssociateComponent	=NULL;

	DLL_Initial				=NULL;
	DLL_Close				=NULL;
	DLL_Load				=NULL;
	DLL_Save				=NULL;
	DLL_ShowSetting			=NULL;
	DLL_ExecuteBeforeScan	=NULL;
	DLL_ExecuteImage		=NULL;

	DllFileName		=dllfilename;
}
FilterDLLList::~FilterDLLList(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;
	if(DllLib.isLoaded()==true){
		DllLib.unload();	//Error occurs in final DLL unload
	}
	ReEntrantDLL=false;
}

bool	FilterDLLList::InitialDLL(int32 &ErrorCode)
{
	QDir	Dir;
	QString	FileName;
	QFileInfo fi(DllFileName);
	if(fi.suffix().isEmpty()==true){
		FileName=DllFileName+QString(".")+GetDynamicFileExt();
	}
	else{
		FileName=DllFileName;
	}
	GetLayersBase()->TestLoadDLL(FileName);
	if(QLibrary::isLibrary(FileName)==true){
		if(LoadDLL(FileName,ErrorCode)==false){
			return(false);
		}
		if(IsFilterDLL()==true){
			ErrorCode=Error_Nothing;
			return(true);			
		}
	}
	ErrorCode=Error_FilterDLL;
	return(false);
}
	
bool	FilterDLLList::IsFilterDLL(void)
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLFilterMode){
			return(true);
		}
	}
	return(false);
}
	
bool	FilterDLLList::LoadDLL(QString &dllfilename,int32 &ErrorCode)
{
	DllLib.setFileName(dllfilename);
	if(DllLib.load()==false){
		return(false);
	}
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Filter_NoFunc_DLL_GetSystemVersion;
		return(false);
	}
	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_GetVersion;
		return(false);
	}

	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	if(DLL_GetExplain==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_GetExplain;
		return(false);
	}
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");

	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_Initial			=(FilterClassBase *(*)(LayersBase *))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_Initial;
		return(false);
	}
	DLL_Close			=(bool (*)(void *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(FilterClassBase *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(FilterClassBase *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(FilterClassBase *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_ShowSetting;
		return(false);
	}
	DLL_ExecuteBeforeScan	=(void (*)(FilterClassBase *handle))DllLib.resolve("DLL_ExecuteBeforeScan");
	if(DLL_ExecuteBeforeScan==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_ExecuteBeforeScan;
		return(false);
	}
	DLL_ExecuteImage		=(bool (*)(FilterClassBase *handle ,ImageBuffer *Buffer[] ,int BufferDimCounts))DllLib.resolve("DLL_ExecuteImage");
	if(DLL_ExecuteImage==NULL){
		ErrorCode=Error_Filter_NoFunc_DLL_ExecuteImage;
		return(false);
	}
	DLL_GetName(FilterName);

	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return false;
		}
	}
	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(dllfilename);
	}

	ErrorCode=Error_Nothing;
	return(true);
}


bool	FilterDLLList::SetLanguageCode(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
	}
	return true;
}

WORD	FilterDLLList::GetDLLType(void)	const
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}

WORD	FilterDLLList::GetVersion(void)	const
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

const QString	FilterDLLList::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

bool	FilterDLLList::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"Filter",/**/"",FilterName);
}

void	FilterDLLList::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}

FilterClassBase	*FilterDLLList::CreateInstance(LayersBase *Base)
{
	if(DLL_Initial!=NULL){
		return DLL_Initial(Base);
	}
	return NULL;
}

bool	FilterDLLList::Load(QIODevice *str,FilterClassBase	*Handle)
{
	if(DLL_Load!=NULL){
		return(DLL_Load(Handle,*str));
	}
	return(false);
}

bool	FilterDLLList::Save(QIODevice *str,FilterClassBase	*Handle)
{
	if(DLL_Save!=NULL){
		return(DLL_Save(Handle,*str));
	}
	return(false);
}

bool	FilterDLLList::ShowSetting(QWidget *parent,FilterClassBase	*Handle)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle, parent));
	}
	return(false);
}
void	FilterDLLList::ExecuteBeforeScan	(FilterClassBase	*Handle)
{
	if(DLL_ExecuteBeforeScan!=NULL){
		return(DLL_ExecuteBeforeScan(Handle));
	}
}
ExeResult	FilterDLLList::ExecuteInitialAfterEdit	(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecuteInitialAfterEdit();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecuteStartByInspection	(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecuteStartByInspection();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecutePreAlignment		(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecutePreAlignment();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecuteAlignment			(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecuteAlignment();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecutePreProcessing		(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecutePreProcessing();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecuteProcessing		(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecuteProcessing();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecuteProcessingRevived	(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecuteProcessingRevived();
	}
	return _ER_false;
}
ExeResult	FilterDLLList::ExecutePostProcessing	(FilterClassBase *Handle)
{
	if(Handle!=NULL){
		return Handle->ExecutePostProcessing();
	}
	return _ER_false;
}

bool	FilterDLLList::ExecuteImage(FilterClassBase	*Handle,ImageBuffer *Buff[],int BufferDimCounts)
{
	if(DLL_ExecuteImage!=NULL){
		return(DLL_ExecuteImage(Handle,Buff ,BufferDimCounts));
	}
	return(false);
}

bool	FilterDLLList::Release(FilterClassBase	*Handle)
{
	if(Handle!=NULL && DLL_Close!=NULL){
		Handle->Release();
		DLL_Close(Handle);
	}
	return true;
}


void	FilterDLLList::GetExportFunctions(QStringList &Str)
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
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
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
	if(DLL_ExecuteBeforeScan!=NULL){
		Str.append("DLL_ExecuteBeforeScan");
	}
	if(DLL_ExecuteImage!=NULL){
		Str.append("DLL_ExecuteImage");
	}
	DLLManager::GetExportFunctions(Str);
}
//==========================================================================================

FilterBankBase::FilterBankBase(LayersBase *base)
:ServiceForLayers(base)
{
}
FilterBankBase::~FilterBankBase(void)
{
}

int	FilterBankBase::SearchAddDLL(int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+GetParamGlobal()->FilterDLLPath;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				FilterDLLList	*a=new FilterDLLList(GetLayersBase(),FileName);
				if(a->InitialDLL(ErrorCode)==true){
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
bool	FilterBankBase::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(FilterDLLList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

FilterDLLList	*FilterBankBase::Search(const QString &_FilterName)
{
	for(FilterDLLList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetFilterName()==_FilterName){
			return a;
		}
	}
	return NULL;
}
int		FilterBankBase::GetDLLCounts(void)
{
	return GetNumber();
}


void	FilterBankBase::AssociateComponent	(ComponentListContainer &List)
{
	for(FilterDLLList *L=GetFirst();L!=NULL;L=L->GetNext()){
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

//=============================================================================================
FilterInstanceList::FilterInstanceList(FilterInstanceContainer *parent ,LayersBase *Base)
:ServiceForLayers(Base),Parent(parent)
{
	DLLPointer	=NULL;
	Handle		=NULL;
	Initialised	=false;
	Enabled		=true;
}
FilterInstanceList::~FilterInstanceList(void)
{
	Release();
}

bool	FilterInstanceList::CreateInstance(const QString &FilterNameStr,int32 &ErrorCode)
{
	DLLPointer=GetLayersBase()->GetFilterBank()->Search(FilterNameStr);
	if(DLLPointer==NULL){
		return false;
	}

	if(Initialised==false){
		Handle=DLLPointer->CreateInstance(GetLayersBase());
		Handle->SetPaernt(this);
	}
	return true;
}

bool	FilterInstanceList::Initial(const QString &FilterNameStr,int32 &ErrorCode)
{
	if(Initialised==false){
		if(Handle!=NULL){
			Handle->Initial();
		}
		Initialised=true;
	}
	return true;
}

bool	FilterInstanceList::Release(void)
{
	if(IsValid()==true){
		bool	ret=DLLPointer->Release(Handle);
		Handle=NULL;
		return ret;
	}
	return false;
}


FilterInstanceList	&FilterInstanceList::operator=(const FilterInstanceList &src)
{
	DLLPointer	=src.DLLPointer;
	if(IsValid()==true && Handle!=NULL){
		bool	ret=DLLPointer->Release(Handle);
	}
	if(DLLPointer!=NULL){
		Handle=DLLPointer->CreateInstance(GetLayersBase());
		Initialised=true;
		Enabled=src.Enabled;

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		src.Save(&Buff);
		Load(&Buff);
	}
	return *this;
}


bool	FilterInstanceList::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(Handle!=NULL){
		return Handle->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
	}
	return true;
}
bool	FilterInstanceList::Reallocate(int newLayerNumb)
{
	if(Handle!=NULL){
		return Handle->Reallocate(newLayerNumb);
	}
	return true;
}
	
int		FilterInstanceList::GetPage(void)	const
{
	if(Parent!=NULL){
		return Parent->GetPage();
	}
	return -1;
}

int		FilterInstanceList::GetPhaseCode(void)	const
{
	if(Parent!=NULL){
		return Parent->GetPhaseCode();
	}
	return -1;
}

int		FilterInstanceList::GetDLLVersion(void)	const
{
	return DLLPointer->GetVersion();
}

void	FilterInstanceList::SetLoadedDLLVersion(int d)	
{	
	if(Handle!=NULL){
		Handle->SetLoadedDLLVersion(d);
	}
}

int		FilterInstanceList::GetLoadedDLLVersion(void)	const
{	
	if(Handle!=NULL){
		return Handle->GetLoadedDLLVersion();	
	}
	return -1;
}
	
bool	FilterInstanceList::Load(QIODevice *str)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		return DLLPointer->Load(str,Handle);
	}
	return false;
}

bool	FilterInstanceList::Save(QIODevice *str)	const
{
	if(DLLPointer!=NULL && Handle!=NULL){
		return DLLPointer->Save(str,Handle);
	}
	return false;
}

	
bool	FilterInstanceList::ShowSetting(QWidget *parent)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		return DLLPointer->ShowSetting(parent,Handle);
	}
	return false;
}
void	FilterInstanceList::TransmitDirectly(GUIDirectMessage *packet)
{
	if(Handle!=NULL){
		Handle->TransmitDirectly(packet);
	}
}

void	FilterInstanceList::ExecuteBeforeScan(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			DLLPointer->ExecuteBeforeScan(Handle);
		}
	}
}

ExeResult	FilterInstanceList::ExecuteInitialAfterEdit	(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteInitialAfterEdit(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}

ExeResult	FilterInstanceList::ExecuteStartByInspection(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteStartByInspection(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecutePreAlignment		(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecutePreAlignment(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecuteAlignment		(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteAlignment(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecutePreProcessing	(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecutePreProcessing(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecuteProcessing		(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteProcessing(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecuteProcessingRevived(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteProcessingRevived(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
ExeResult	FilterInstanceList::ExecutePostProcessing	(void)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecutePostProcessing(Handle);
		}
		return _ER_true;
	}
	return _ER_false;
}
bool	FilterInstanceList::ExecuteImage(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(DLLPointer!=NULL && Handle!=NULL){
		if(Enabled==true){
			return DLLPointer->ExecuteImage(Handle,Buff ,BufferDimCounts);
		}
		return true;
	}
	return false;
}

bool	FilterInstanceList::IsValid(void)	const
{
	if(DLLPointer!=NULL && Handle!=NULL){
		return true;
	}
	return false;
}

QString	FilterInstanceList::GetFilterName(void)	const
{
	if(IsValid()==true){
		return DLLPointer->GetFilterName();
	}
	return /**/"";
}

FilterInstanceContainer::FilterInstanceContainer(int Phase,int page ,LayersBase *Base)
:ServiceForLayers(Base),Page(page),PhaseCode(Phase)
{
	ErrorCode=0;
}
FilterInstanceContainer::~FilterInstanceContainer(void)
{
}


bool	FilterInstanceContainer::Save(QIODevice *f)
{
	int32	Ver=10002;
	if(::Save(f,Ver)==false){
		return false;
	}

	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsValid()==true){
			if(::Save(f,a->GetFilterName())==false){
				return false;
			}
			int32	V=a->GetDLLVersion();
			if(::Save(f,V)==false){
				return false;
			}
			QBuffer	Buff;
			if(Buff.open(QIODevice::ReadWrite)==true){
				a->Save(&Buff);
				if(::Save(f,Buff.buffer())==false){
					return false;
				}
			}
		}
	}
	return true;
}
bool	FilterInstanceContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	if(N<10000){
		for(int i=0;i<N;i++){
			QString	Str;
			if(::Load(f,Str)==false){
				return false;
			}
			FilterInstanceList	*a=new FilterInstanceList(this,GetLayersBase());
			if(a->CreateInstance(Str,ErrorCode)==false){
				delete	a;
				continue;
			}
			if(a->Load(f)==false){
				return false;
			}
			if(a->Initial(Str,ErrorCode)==true){
				AppendList(a);
			}
			else{
				delete	a;
			}
		}
	}
	else if(N==10001){
		if(::Load(f,N)==false){
			return false;
		}
		for(int i=0;i<N;i++){
			QString	Str;
			if(::Load(f,Str)==false){
				return false;
			}
			FilterInstanceList	*a=new FilterInstanceList(this,GetLayersBase());
			if(a->CreateInstance(Str,ErrorCode)==false){
				delete	a;
				continue;
			}
			QByteArray	AData;
			if(::Load(f,AData)==false){
				return false;
			}
			QBuffer	Buff(&AData);
			Buff.open(QIODevice::ReadOnly);
			if(a->Load(&Buff)==true){
				if(a->Initial(Str,ErrorCode)==true){
					AppendList(a);
				}
				else{
					delete	a;
				}
			}
			else{
				delete	a;
			}
		}
	}
	else if(N==10002){
		if(::Load(f,N)==false){
			return false;
		}
		for(int i=0;i<N;i++){
			QString	Str;
			if(::Load(f,Str)==false){
				return false;
			}
			FilterInstanceList	*a=new FilterInstanceList(this,GetLayersBase());
			if(a->CreateInstance(Str,ErrorCode)==false){
				delete	a;
				continue;
			}
			int32	V=0;
			if(::Load(f,V)==false){
				return false;
			}
			a->SetLoadedDLLVersion(V);
			QByteArray	AData;
			if(::Load(f,AData)==false){
				return false;
			}
			QBuffer	Buff(&AData);
			Buff.open(QIODevice::ReadOnly);
			if(a->Load(&Buff)==true){
				if(a->Initial(Str,ErrorCode)==true){
					AppendList(a);
				}
				else{
					delete	a;
				}
			}
			else{
				delete	a;
			}
		}
	}
		
	return true;
}
FilterInstanceList	*FilterInstanceContainer::Search(const QString &_FilterName)	const
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetFilterName()==_FilterName){
			return a;
		}
	}
	return NULL;
}

void	FilterInstanceContainer::EnumInstance(NPListPack<FilterInstanceListPointerList> &PointerContainer ,const QString &_FilterName)
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetFilterName()==_FilterName){
			FilterInstanceListPointerList	*L=new FilterInstanceListPointerList(a);
			PointerContainer.AppendList(L);
		}
	}
}

ExeResult	FilterInstanceContainer::ExecuteInitialAfterEdit	(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecuteInitialAfterEdit();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecuteStartByInspection	(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecuteStartByInspection();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecutePreAlignment		(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecutePreAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecuteAlignment			(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecuteAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecutePreProcessing		(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecutePreProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecuteProcessing			(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecuteProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecuteProcessingRevived	(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecuteProcessingRevived();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	FilterInstanceContainer::ExecutePostProcessing		(void)
{
	ExeResult	Ret=_ER_true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		ExeResult	r=a->ExecutePostProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}

FilterInstanceContainer	&FilterInstanceContainer::operator=(const FilterInstanceContainer &src)
{
	ErrorCode	=src.ErrorCode;
	Page		=src.Page;
	PhaseCode	=src.PhaseCode;

	RemoveAll();
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		FilterInstanceList	*d=new FilterInstanceList(this,GetLayersBase());
		AppendList(d);
	}
	return *this;
}
	
int		FilterInstanceContainer::GetPage(void)	const
{
	return Page;
}
int		FilterInstanceContainer::GetPhaseCode(void)
{
	return PhaseCode;
}

void	FilterInstanceContainer::SetEnabled(bool b)
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetEnabled(b);
	}
}
bool	FilterInstanceContainer::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ReallocXYPixels(NewDotPerLine,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	FilterInstanceContainer::Reallocate(int newLayerNumb)
{
	bool	Ret=true;
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Reallocate(newLayerNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
void	FilterInstanceContainer::ExecuteBeforeScan	(void)
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->ExecuteBeforeScan();
	}
}
bool	FilterInstanceContainer::ExecuteImage(ImageBuffer *Buff[],int BufferDimCounts)
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteImage(Buff,BufferDimCounts)==false){
			return false;
		}
	}
	return true;
}

bool	FilterInstanceContainer::AppendFilter(const QString &FilterNameStr)
{
	FilterInstanceList	*a=new FilterInstanceList(this,GetLayersBase());
	if(a->CreateInstance(FilterNameStr,ErrorCode)==false){
		return false;
	}
	if(a->Initial(FilterNameStr,ErrorCode)==true){
		AppendList(a);
		return true;
	}
	return false;
}

bool	FilterInstanceContainer::ReleaseAll(void)
{
	for(FilterInstanceList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Release();
	}
	return true;
}
