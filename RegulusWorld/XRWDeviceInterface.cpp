#include "XRWDeviceInterface.h"
#include "XRegulusWorld.h"

//=============================================================================

RWDeviceAccessClass::RWDeviceAccessClass(LayersBase *base):ServiceForLayers(base)
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
}
RWDeviceAccessClass::~RWDeviceAccessClass(void)
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

bool	RWDeviceAccessClass::Initial(const QString &_DLLFileName ,const QString Parameter 
							,int32 &ErrorCode)
{
	ParamStr=Parameter;
	QFileInfo fi(_DLLFileName);
	if(fi.suffix().isEmpty()==true){
		DLLFileName=_DLLFileName+QString(".")+GetDynamicFileExt();
	}
	else{
		DLLFileName=_DLLFileName;
	}
	GetLayersBase()->TestLoadDLL(DLLFileName);

	return LoadDLLLibrary(ErrorCode,DLLFileName,ParamStr);
}

bool	RWDeviceAccessClass::LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter)
{
	if(QLibrary::isLibrary(FileName)==true){
		if(LoadDLL(FileName,ErrorCode)==false){
			return(false);
		}
		if(IsRWDeviceDLL()==true){
			Handle=DLL_Initial(GetLayersBase(),Parameter);
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

bool	RWDeviceAccessClass::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		ErrorCode=Error_RWDevice_NotLoaded;
		return(false);
	}
	DLLFileName=filename;

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_GetVersion;
		return(false);
	}
	DLL_AssociateComponent	=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_RWDevice_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}

	DLL_Initial			=(RWDeviceBaseClass *(*)(LayersBase *base,const QString &ParamStr))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_Initial;
		return(false);
	}

	DLL_Close			=(bool (*)(RWDeviceBaseClass *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_Close;
		return(false);
	}
	DLL_Load			=(bool (*)(RWDeviceBaseClass *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(RWDeviceBaseClass *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(RWDeviceBaseClass *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_RWDevice_NoFunc_DLL_ShowSetting;
		return(false);
	}

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return true;
}


QString	RWDeviceAccessClass::GetName(void)
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	RWDeviceAccessClass::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	RWDeviceAccessClass::GetDLLType(void)
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	RWDeviceAccessClass::GetCopyright(void)
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}
void	RWDeviceAccessClass::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
const QString	RWDeviceAccessClass::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
bool	RWDeviceAccessClass::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"RWDeviceDLL",/**/"",DLLName);
}
bool	RWDeviceAccessClass::IsRWDeviceDLL(void)
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLRWDeviceMode){
			return(true);
		}
	}
	return(false);
}

bool	RWDeviceAccessClass::Load(QIODevice *str)
{
	if(DLL_Load!=NULL){
		QString	tName;
		if(::Load(str,tName)==false){
			return false;
		}
		QString	sName;
		if(DLL_GetName!=NULL){
			DLL_GetName(sName);
		}
		if(sName!=tName){
			return false;
		}
		bool	ret=DLL_Load(Handle,*str);
		return ret;
	}
	return(false);
}
bool	RWDeviceAccessClass::Save(QIODevice *str)
{
	if(DLL_Save!=NULL){
		QString	tName;
		if(DLL_GetName!=NULL){
			DLL_GetName(tName);
		}
		if(::Save(str,tName)==false){
			return false;
		}
		bool	ret=DLL_Save(Handle,*str);
		return ret;
	}
	return(false);
}


bool	RWDeviceAccessClass::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle,parent));
	}
	return(false);
}

void	RWDeviceAccessClass::TransmitDirectly(GUIDirectMessage *packet)
{
	RWDeviceBaseClass	*f=GetHandle();
	if(f!=NULL){
		f->TransmitDirectly(packet);
	}
}

void	RWDeviceAccessClass::GetExportFunctions(QStringList &Str)
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
bool	RWDeviceAccessPack::CheckSystemVersion(QStringList &Str)
{
	for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			return false;
		}
	}
	return true;
}
void	RWDeviceAccessPack::AssociateComponent	 (ComponentListContainer &List)
{
	for(RWDeviceAccessClass *L=GetFirst();L!=NULL;L=L->GetNext()){
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

int	RWDeviceAccessPack::SearchAddDLL(int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+DLLPathRWDevice;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				RWDeviceAccessClass	*a=new RWDeviceAccessClass(GetLayersBase());
				if(a->LoadDLL(FileName,ErrorCode)==true && a->IsRWDeviceDLL()==true){

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
bool	RWDeviceAccessPack::Initial(int32 &ErrorCode)
{
	RemoveAll();
	RegulusWorld	*R=GetRegulusWorld(GetLayersBase());
	if(R!=NULL){
		ParamRegulusWorld	*Param=R->GetParamRegulusWorld();
		for(RWDeviceParamList *L=Param->RWDeviceParams.GetFirst();L!=NULL;L=L->GetNext()){
			RWDeviceAccessClass	*a=new RWDeviceAccessClass(GetLayersBase());
			if(a->Initial(L->DLLFileName,L->Parameter,ErrorCode)==false){
				ErrorCode=Error_Device_DLL_Initial1;
				return false;
			}
			a->GetHandle()->SetDeviceID(L->DeviceID);
			AppendList(a);
		}
	}

	return true;
}

bool	RWDeviceAccessPack::Save(QIODevice *f)
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
		for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetHandle()!=NULL){
				N++;
			}
		}
		if(::Save(f,N)==false){
			return false;
		}
		for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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

bool	RWDeviceAccessPack::Load(QIODevice *f)
{
	for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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
			for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
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

void	RWDeviceAccessPack::LoopOnIdle(void)
{
	for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		RWDeviceBaseClass	*V=a->GetHandle();
		if(V!=NULL){
			V->LoopOnIdle();
		}
	}
}

void	RWDeviceAccessPack::TransmitDirectly(GUIDirectMessage *packet)
{
	for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}
RWDeviceBaseClass	*RWDeviceAccessPack::FindByDeviceID(int deviceID)
{
	for(RWDeviceAccessClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		RWDeviceBaseClass	*f=a->GetHandle();
		if(f!=NULL){
			if(f->GetDeviceID()==deviceID){
				return f;
			}
		}
	}
	return NULL;
}