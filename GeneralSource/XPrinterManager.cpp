/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPrinterManager.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XPrinterManager.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "XPrinterDLLBaseClass.h"
#include "Regulus64System.h"

//=============================================================================

PrinterClass::PrinterClass(LayersBase *base):QObject(NULL),ServiceForLayers(base)
{
	DLL_GetDLLType			=NULL;
	DLL_GetName				=NULL;
	DLL_GetVersion			=NULL;
	DLL_GetExplain			=NULL;
	DLL_CheckCopyright		=NULL;
	DLL_AssociateComponent	=NULL;
	DLL_Initial				=NULL;
	DLL_SetLayersBasePointer=NULL;

	DLL_Close				=NULL;
	DLL_Load				=NULL;
	DLL_Save				=NULL;
	DLL_ShowSetting			=NULL;

	LoadedDone				=false;
}
PrinterClass::~PrinterClass(void)
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

bool	PrinterClass::Initial(const QString &DLLFileName ,const QString Parameter 
							,int32 &ErrorCode)
{
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

bool	PrinterClass::InitialStraightPath(const QString &DLLFileName ,const QString Parameter 
							,int32 &ErrorCode)
{
	GetLayersBase()->TestLoadDLL(DLLFileName);

	return LoadDLLLibrary(ErrorCode,DLLFileName,Parameter);
}


bool	PrinterClass::LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter)
{
	if(QLibrary::isLibrary(FileName)==true){
		if(LoadDLL(FileName,ErrorCode)==false){
			return(false);
		}
		if(IsPrinterDLL()==true){
			Handle=DLL_Initial(GetLayersBase(),Parameter);
			if(DLL_GetName!=NULL){
				DLL_GetName(DLLName);
			}
			if(DLL_SetLayersBasePointer!=NULL){
				DLL_SetLayersBasePointer(Handle,GetLayersBase());
			}
			return(true);		
		}
	}
	return(false);
}

bool	PrinterClass::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		ErrorCode=Error_Printer_NotLoaded;
		return(false);
	}
	PrinterFileName=filename;

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_GetVersion;
		return(false);
	}
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Printer_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_Initial			=(PrinterDLLBaseClass *(*)(LayersBase *base,const QString &PrinterParamStr))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_Initial;
		return(false);
	}
	DLL_SetLayersBasePointer	=(void (*)(PrinterDLLBaseClass *handle ,LayersBase *base))DllLib.resolve("DLL_SetLayersBasePointer");

	DLL_Close			=(bool (*)(PrinterDLLBaseClass *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(PrinterDLLBaseClass *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(PrinterDLLBaseClass *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(PrinterDLLBaseClass *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_Printer_NoFunc_DLL_ShowSetting;
		return(false);
	}

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return true;
}

QString	PrinterClass::GetName(void)
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

void	PrinterClass::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}

WORD	PrinterClass::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	PrinterClass::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	PrinterClass::GetCopyright(void)
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}

const QString	PrinterClass::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
bool	PrinterClass::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"PrinterDLL",/**/"",DLLName);
}

bool	PrinterClass::IsPrinterDLL(void)
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLPrinterMode){
			return(true);
		}
	}
	return(false);
}

bool	PrinterClass::Load(QIODevice *str)
{
	if(DLL_Load!=NULL){
		QString	tName;
		if(::Load(str,tName)==false){
			return false;
		}
		QString	sName;
		if(DLL_GetName!=NULL){
			MutexPrinter.lock();
			DLL_GetName(sName);
			MutexPrinter.unlock();
		}
		if(sName!=tName){
			return false;
		}
		MutexPrinter.lock();
		bool	ret=DLL_Load(Handle,*str);
		MutexPrinter.unlock();
		return ret;
	}
	return(false);
}
bool	PrinterClass::Save(QIODevice *str)
{
	if(DLL_Save!=NULL){
		QString	tName;
		if(DLL_GetName!=NULL){
			MutexPrinter.lock();
			DLL_GetName(tName);
			MutexPrinter.unlock();
		}
		if(::Save(str,tName)==false){
			return false;
		}
		MutexPrinter.lock();
		bool	ret=DLL_Save(Handle,*str);
		MutexPrinter.unlock();
		return ret;
	}
	return(false);
}


bool	PrinterClass::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle,parent));
	}
	return(false);
}

void	PrinterClass::TransmitDirectly(GUIDirectMessage *packet)
{
	PrinterDLLBaseClass	*f=GetHandle();
	if(f!=NULL){
		f->TransmitDirectly(packet);
	}
}

void	PrinterClass::GetExportFunctions(QStringList &Str)
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
	if(DLL_SetLayersBasePointer!=NULL){
		Str.append("DLL_SetLayersBasePointer");
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
bool	PrinterClassPack::CheckSystemVersion(QStringList &Str)
{
	for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			return false;
		}
	}
	return true;
}
int	PrinterClassPack::SearchAddDLL(int32 &ErrorCode)
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
				PrinterClass	*a=new PrinterClass(GetLayersBase());
				if(a->LoadDLL(FileName,ErrorCode)==true && a->IsPrinterDLL()==true){
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
bool	PrinterClassPack::Initial(int32 &ErrorCode)
{
	RemoveAll();

	if(GetParamGlobal()->PrinterDLLFileName.isEmpty()==false){
		PrinterClass	*a=new PrinterClass(GetLayersBase());
		if(a->Initial(GetParamGlobal()->PrinterDLLFileName,GetParamGlobal()->PrinterParamStr,ErrorCode)==false){
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->PrinterDLLFileName2.isEmpty()==false){
		PrinterClass	*a=new PrinterClass(GetLayersBase());
		if(a->Initial(GetParamGlobal()->PrinterDLLFileName2,GetParamGlobal()->PrinterParamStr2,ErrorCode)==false){
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->PrinterDLLFileName3.isEmpty()==false){
		PrinterClass	*a=new PrinterClass(GetLayersBase());
		if(a->Initial(GetParamGlobal()->PrinterDLLFileName3,GetParamGlobal()->PrinterParamStr3,ErrorCode)==false){
			return false;
		}
		AppendList(a);
	}
	if(GetParamGlobal()->PrinterDLLFileName4.isEmpty()==false){
		PrinterClass	*a=new PrinterClass(GetLayersBase());
		if(a->Initial(GetParamGlobal()->PrinterDLLFileName4,GetParamGlobal()->PrinterParamStr4,ErrorCode)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	PrinterClassPack::Save(QIODevice *f)
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
		for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetHandle()!=NULL){
				N++;
			}
		}
		if(::Save(f,N)==false){
			return false;
		}
		for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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

bool	PrinterClassPack::Load(QIODevice *f)
{
	for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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
			for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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

void	PrinterClassPack::LoopOnIdle(void)
{
	for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		PrinterDLLBaseClass	*V=a->GetHandle();
		if(V!=NULL){
			V->LoopOnIdle();
		}
	}
}
PrinterClass	*PrinterClassPack::Search(const QString &DLLName)
{
	for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetName()==DLLName){
			return a;
		}
	}
	return NULL;
}

void	PrinterClassPack::TransmitDirectly(GUIDirectMessage *packet)
{
	for(PrinterClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}
void	PrinterClassPack::AssociateComponent	 (ComponentListContainer &List)
{
	for(PrinterClass *L=GetFirst();L!=NULL;L=L->GetNext()){
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