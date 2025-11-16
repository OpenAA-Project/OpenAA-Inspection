#include "XTypeDef.h"
#include <QFile>

#include "XGeneralStocker.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XIntClass.h"
#include "XDatabase.h"
#include "XGUIFormBase.h"

GeneralStocker::GeneralStocker(LayersBase *base)
:ServiceForLayers(base)
{
	DLL_GetName						=NULL;
	DLL_GetOrganization				=NULL;
	DLL_GetDLLType					=NULL;
	DLL_GetVersion					=NULL;
	DLL_GetSystemVersion			=NULL;
	DLL_AssociateComponent			=NULL;
	DLL_SetLanguage					=NULL;
	DLL_Release						=NULL;
	DLL_Initial						=NULL;
	DLL_ReturnProperty				=NULL;

	DLL_EnumKeyword					=NULL;
	DLL_GetType						=NULL;
	DLL_GetData						=NULL;
	DLL_ShowDialog					=NULL;
	DLL_TransmitDirectly			=NULL;

	DLL_Save						=NULL;
	DLL_Load						=NULL;
	DLL_GetGuiAdditionalDatabase	=NULL;

	DLL_ExecuteInitialAfterEditPrev	=NULL;
	DLL_ExecuteInitialAfterEditPost	=NULL;
	DLL_ExecuteStartByInspectionPrev=NULL;
	DLL_ExecuteStartByInspectionPost=NULL;
	DLL_ExecuteCapturedPrev			=NULL;
	DLL_ExecuteCapturedPost			=NULL;
	DLL_ExecutePreAlignmentPrev		=NULL;
	DLL_ExecutePreAlignmentPost		=NULL;
	DLL_ExecuteAlignmentPrev		=NULL;
	DLL_ExecuteAlignmentPost		=NULL;
	DLL_ExecutePreProcessingPrev	=NULL;
	DLL_ExecutePreProcessingPost	=NULL;
	DLL_ExecuteProcessingPrev		=NULL;
	DLL_ExecuteProcessingPost		=NULL;
	DLL_ExecuteProcessingRevivedPrev=NULL;
	DLL_ExecuteProcessingRevivedPost=NULL;
	DLL_ExecutePostProcessingPrev	=NULL;
	DLL_ExecutePostProcessingPost	=NULL;

	SaveInMasterData	=false;
	SynchronizeToSlave	=false;
	Handle				=NULL;
	ReEntrantDLL		=false;
}

GeneralStocker::~GeneralStocker(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	CloseDLL();
	ReEntrantDLL=false;
}

bool			GeneralStocker::OpenDLL(const QString &DLLFileName)
{
	FileName=DLLFileName;
	GetLayersBase()->TestLoadDLL(DLLFileName);

	DllLib.setFileName(DLLFileName);
	if(DllLib.load()==false){
		return(false);
	}

	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		return false;
	}
	if(DLL_GetDLLType()!=DLLGeneralStockerMode){
		return false;
	}

	DLL_GetName					=(bool (*)(QString &))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		return false;
	}
	DLL_GetName(Name);

	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_GetSystemVersion		=(const char *(*)(VersionType vtype))DllLib.resolve("DLL_GetSystemVersion");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_Initial					=(GeneralStockerItemBase *(*)(LayersBase *Base))DllLib.resolve(/**/"DLL_Initial");
	DLL_Release					=(void (*)(GeneralStockerItemBase *handle))DllLib.resolve(/**/"DLL_Release");
	DLL_ReturnProperty			=(void (*)(struct PropertyGeneralStocker &Prop))DllLib.resolve(/**/"DLL_ReturnProperty");

	DLL_EnumKeyword				=(void(*)(GeneralStockerItemBase *handle ,QStringList &List))DllLib.resolve(/**/"DLL_EnumKeyword");
	DLL_GetType					=(QVariant::Type (*)(GeneralStockerItemBase *handle ,QString Keyword))DllLib.resolve(/**/"DLL_GetType");
	DLL_GetData					=(bool (*)(GeneralStockerItemBase *handle ,QString Keyword 
										,QVariantList &ReturnValue,QVariantList &ArgValue))DllLib.resolve(/**/"DLL_GetData");

	DLL_ShowDialog				=(bool (*)(GeneralStockerItemBase *handle ,QString Keyword, QWidget *parent))DllLib.resolve(/**/"DLL_ShowDialog");
	DLL_TransmitDirectly		=(void (*)(GeneralStockerItemBase *handle ,GUIDirectMessage *packet))DllLib.resolve(/**/"DLL_TransmitDirectly");
	DLL_Save					=(bool (*)(QIODevice *f,GeneralStockerItemBase *handle))DllLib.resolve(/**/"DLL_Save");
	DLL_Load					=(bool (*)(QIODevice *f,GeneralStockerItemBase *handle))DllLib.resolve(/**/"DLL_Load");

	DLL_GetGuiAdditionalDatabase=(void (*)(NPListPack<GuiAdditionalDatabase> &Data))DllLib.resolve(/**/"DLL_GetGuiAdditionalDatabase");

	DLL_ExecuteInitialAfterEditPrev	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteInitialAfterEditPrev");
	DLL_ExecuteInitialAfterEditPost	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteInitialAfterEditPost");
	DLL_ExecuteStartByInspectionPrev=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteStartByInspectionPrev");
	DLL_ExecuteStartByInspectionPost=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteStartByInspectionPost");
	DLL_ExecuteCapturedPrev			=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList))DllLib.resolve(/**/"DLL_ExecuteCapturedPrev");
	DLL_ExecuteCapturedPost			=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList))DllLib.resolve(/**/"DLL_ExecuteCapturedPost");
	DLL_ExecutePreAlignmentPrev		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePreAlignmentPrev");
	DLL_ExecutePreAlignmentPost		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePreAlignmentPost");
	DLL_ExecuteAlignmentPrev		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteAlignmentPrev");
	DLL_ExecuteAlignmentPost		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteAlignmentPost");
	DLL_ExecutePreProcessingPrev	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePreProcessingPrev");
	DLL_ExecutePreProcessingPost	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePreProcessingPost");
	DLL_ExecuteProcessingPrev		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingPrev");
	DLL_ExecuteProcessingPost		=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingPost");
	DLL_ExecuteProcessingRevivedPrev=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingRevivedPrev");
	DLL_ExecuteProcessingRevivedPost=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingRevivedPost");
	DLL_ExecutePostProcessingPrev	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePostProcessingPrev");
	DLL_ExecutePostProcessingPost	=(ExeResult	(*)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res))DllLib.resolve(/**/"DLL_ExecutePostProcessingPost");

	if(DLL_GetOrganization!=NULL){
		DLL_GetOrganization(Organization);
	}
	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(DLLFileName);
	}
	if(DLL_ReturnProperty!=NULL){
		struct	PropertyGeneralStocker	Prop;
		Prop.SaveInMasterData	=false;
		Prop.SynchronizeToSlave	=false;
		DLL_ReturnProperty(Prop);

		Prop.SaveInMasterData	=SaveInMasterData;
		Prop.SynchronizeToSlave	=SynchronizeToSlave;
	}
	return true;
}


void	GeneralStocker::CloseDLL(void)
{
	if(DLL_Release!=NULL){
		DLL_Release(Handle);
	}
	if(DllLib.isLoaded ()==true){
		DllLib.unload();
	}
}

void	GeneralStocker::Initial(LayersBase *base)
{
	if(DLL_Initial!=NULL){
		Handle=DLL_Initial(base);
	}
}
void	GeneralStocker::InitialAfterParamLoaded(void)
{
	if(Handle!=NULL){
		Handle->InitialAfterParamLoaded();
	}
}

bool	GeneralStocker::CheckSystemVersion(QStringList &Str)
{
	return true;
}
void	GeneralStocker::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}

void	GeneralStocker::SetLanguage(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
	}
	EnumKeyword(KeywordList);
}

void	GeneralStocker::EnumKeyword(QStringList &List)
{
	if(DLL_EnumKeyword!=NULL){
		DLL_EnumKeyword(Handle,List);
	}
}
QVariant::Type	GeneralStocker::GetType(QString Keyword)
{
	if(DLL_GetType!=NULL){
		return DLL_GetType(Handle,Keyword);
	}
	return QVariant::Invalid;
}
bool	GeneralStocker::GetData(LayersBase *Base ,const QString &Keyword 
								,QVariantList &ReturnValue,QVariantList &ArgValue)
{
	if(DLL_GetData!=NULL){
		return DLL_GetData(Handle,Keyword,ReturnValue,ArgValue);
	}
	return false;
}

bool	GeneralStocker::ShowDialog(const QString &Keyword, QWidget *parent)
{
	if(DLL_ShowDialog!=NULL){
		return DLL_ShowDialog(Handle,Keyword,parent);
	}
	return false;
}
void	GeneralStocker::TransmitDirectly(GUIDirectMessage *packet)
{
	if(DLL_TransmitDirectly!=NULL){
		DLL_TransmitDirectly(Handle,packet);
	}
}
void	GeneralStocker::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	Handle->SpecifiedDirectly(v);
}

bool	GeneralStocker::Save(QIODevice *f)
{
	if(DLL_Save!=NULL){
		return DLL_Save(f,Handle);
	}
	return true;
}
bool	GeneralStocker::Load(QIODevice *f)
{
	if(DLL_Load!=NULL){
		return DLL_Load(f,Handle);
	}
	return true;
}


bool	GeneralStocker::CreateExcludedList(ExcludedListPack &EList)
{
	if(DLL_GetGuiAdditionalDatabase!=NULL){
		NPListPack<GuiAdditionalDatabase> FieldList;
		DLL_GetGuiAdditionalDatabase(FieldList);
		for(GuiAdditionalDatabase *d=FieldList.GetFirst();d!=NULL;d=d->GetNext()){
			ExcludedListForCheck	*e=new ExcludedListForCheck(d->TableName,d->FieldName);
			EList.AppendList(e);
		}
	}
	return true;		
}

bool	GeneralStocker::ExistsKeyword(const QString &Keyword)
{
	for(int i=0;i<KeywordList.count();i++){
		if(KeywordList[i]==Keyword){
			return true;
		}
	}
	return false;
}

bool	GeneralStocker::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{	
	if(Handle!=NULL){
		return Handle->MakeExecuteInitialAfterEditInfo(ExeID ,Res,EInfo);
	}
	return true;
}

ExeResult	GeneralStocker::ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteInitialAfterEditPrev!=NULL){
		return DLL_ExecuteInitialAfterEditPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteInitialAfterEditPost!=NULL){
		return DLL_ExecuteInitialAfterEditPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteStartByInspectionPrev(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteStartByInspectionPrev!=NULL){
		return DLL_ExecuteStartByInspectionPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteStartByInspectionPost(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteStartByInspectionPost!=NULL){
		return DLL_ExecuteStartByInspectionPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}

ExeResult	GeneralStocker::ExecuteCapturedPrev	(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)
{
	if(DLL_ExecuteCapturedPrev!=NULL){
		return DLL_ExecuteCapturedPrev(ExeID ,Handle,Res,CapturedList);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteCapturedPost	(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)
{
	if(DLL_ExecuteCapturedPost!=NULL){
		return DLL_ExecuteCapturedPost(ExeID ,Handle,Res,CapturedList);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePreAlignmentPrev		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreAlignmentPrev!=NULL){
		return DLL_ExecutePreAlignmentPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePreAlignmentPost		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreAlignmentPost!=NULL){
		return DLL_ExecutePreAlignmentPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteAlignmentPrev		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteAlignmentPrev!=NULL){
		return DLL_ExecuteAlignmentPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteAlignmentPost		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteAlignmentPost!=NULL){
		return DLL_ExecuteAlignmentPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePreProcessingPrev	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreProcessingPrev!=NULL){
		return DLL_ExecutePreProcessingPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePreProcessingPost	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreProcessingPost!=NULL){
		return DLL_ExecutePreProcessingPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteProcessingPrev		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessingPrev!=NULL){
		return DLL_ExecuteProcessingPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteProcessingPost		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessingPost!=NULL){
		return DLL_ExecuteProcessingPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteProcessingRevivedPrev(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessingRevivedPrev!=NULL){
		return DLL_ExecuteProcessingRevivedPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecuteProcessingRevivedPost(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessingRevivedPost!=NULL){
		return DLL_ExecuteProcessingRevivedPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePostProcessingPrev	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePostProcessingPrev!=NULL){
		return DLL_ExecutePostProcessingPrev(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}
ExeResult	GeneralStocker::ExecutePostProcessingPost	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePostProcessingPost!=NULL){
		return DLL_ExecutePostProcessingPost(ExeID ,Handle,Res);
	}
	return _ER_NoFunc;
}

void	GeneralStocker::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetOrganization!=NULL){
		Str.append("DLL_GetOrganization");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_GetSystemVersion!=NULL){
		Str.append("DLL_GetSystemVersion");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_Load!=NULL){
		Str.append("DLL_Load");
	}
	if(DLL_Save!=NULL){
		Str.append("DLL_Save");
	}
	if(DLL_Release!=NULL){
		Str.append("DLL_Release");
	}
	if(DLL_ReturnProperty!=NULL){
		Str.append("DLL_ReturnProperty");
	}
	if(DLL_EnumKeyword!=NULL){
		Str.append("DLL_EnumKeyword");
	}					
	if(DLL_GetType!=NULL){
		Str.append("DLL_GetType");
	}
	if(DLL_GetData!=NULL){
		Str.append("DLL_GetData");
	}
	if(DLL_ShowDialog!=NULL){
		Str.append("DLL_ShowDialog");
	}
	if(DLL_TransmitDirectly!=NULL){
		Str.append("DLL_TransmitDirectly");
	}
	if(DLL_ExecuteInitialAfterEditPrev!=NULL){
		Str.append("DLL_ExecuteInitialAfterEditPrev");
	}
	if(DLL_ExecuteInitialAfterEditPost!=NULL){
		Str.append("DLL_ExecuteInitialAfterEditPost");
	}
	if(DLL_ExecuteStartByInspectionPrev!=NULL){
		Str.append("DLL_ExecuteStartByInspectionPrev");
	}
	if(DLL_ExecuteStartByInspectionPost!=NULL){
		Str.append("DLL_ExecuteStartByInspectionPost");
	}
	if(DLL_ExecuteCapturedPrev!=NULL){
		Str.append("DLL_ExecuteCapturedPrev");
	}
	if(DLL_ExecuteCapturedPost!=NULL){
		Str.append("DLL_ExecuteCapturedPost");
	}
	if(DLL_ExecutePreAlignmentPrev!=NULL){
		Str.append("DLL_ExecutePreAlignmentPrev");
	}
	if(DLL_ExecutePreAlignmentPost!=NULL){
		Str.append("DLL_ExecutePreAlignmentPost");
	}
	if(DLL_ExecuteAlignmentPrev!=NULL){
		Str.append("DLL_ExecuteAlignmentPrev");
	}
	if(DLL_ExecuteAlignmentPost!=NULL){
		Str.append("DLL_ExecuteAlignmentPost");
	}
	if(DLL_ExecutePreProcessingPrev!=NULL){
		Str.append("DLL_ExecutePreProcessingPrev");
	}
	if(DLL_ExecutePreProcessingPost!=NULL){
		Str.append("DLL_ExecutePreProcessingPost");
	}
	if(DLL_ExecuteProcessingPrev!=NULL){
		Str.append("DLL_ExecuteProcessingPrev");
	}
	if(DLL_ExecuteProcessingPost!=NULL){
		Str.append("DLL_ExecuteProcessingPost");
	}
	if(DLL_ExecuteProcessingRevivedPrev!=NULL){
		Str.append("DLL_ExecuteProcessingRevivedPrev");
	}
	if(DLL_ExecuteProcessingRevivedPost!=NULL){
		Str.append("DLL_ExecuteProcessingRevivedPost");
	}
	if(DLL_ExecutePostProcessingPrev!=NULL){
		Str.append("DLL_ExecutePostProcessingPrev");
	}
	if(DLL_ExecutePostProcessingPost!=NULL){
		Str.append("DLL_ExecutePostProcessingPost");
	}
}

//==========================================================================================

bool			GeneralStockerContainer::OpenDLL(void)
{
	GeneralStocker	*v;
	RemoveAll();

	QString	FileName1=GetParamGlobal()->GeneralStockerFileName1;
	if(QFile::exists(FileName1)==true){
		v=new GeneralStocker(GetLayersBase());
		if(v->OpenDLL(FileName1)==true){
			AppendList(v);
		}
		else{
			delete	v;
		}
	}

	QString	FileName2=GetParamGlobal()->GeneralStockerFileName2;
	if(QFile::exists(FileName2)==true){
		v=new GeneralStocker(GetLayersBase());
		if(v->OpenDLL(FileName2)==true){
			AppendList(v);
		}
		else{
			delete	v;
		}
	}

	QString	FileName3=GetParamGlobal()->GeneralStockerFileName3;
	if(QFile::exists(FileName3)==true){
		v=new GeneralStocker(GetLayersBase());
		if(v->OpenDLL(FileName3)==true){
			AppendList(v);
		}
		else{
			delete	v;
		}
	}

	QString	FileName4=GetParamGlobal()->GeneralStockerFileName4;
	if(QFile::exists(FileName4)==true){
		v=new GeneralStocker(GetLayersBase());
		if(v->OpenDLL(FileName4)==true){
			AppendList(v);
		}
		else{
			delete	v;
		}
	}
	return true;
}
void	GeneralStockerContainer::Initial(void)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->Initial(GetLayersBase());
	}

	QFile	FL(GetFileName());
	if(FL.open(QIODevice::ReadOnly)==true){
		struct	PropertyGeneralStocker	Prop;
		Load(&FL,Prop);
	}
}
void	GeneralStockerContainer::InitialAfterParamLoaded(void)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->InitialAfterParamLoaded();
	}
}
void	GeneralStockerContainer::AssociateComponent	 (ComponentListContainer &List)
{
	for(GeneralStocker *L=GetFirst();L!=NULL;L=L->GetNext()){
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

void	GeneralStockerContainer::SetLanguage(int LanguageCode)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->SetLanguage(LanguageCode);
	}
}
GeneralStocker	*GeneralStockerContainer::Search(const QString &DLLName)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetName()==DLLName){
			return s;
		}
	}
	return NULL;
}

QVariant::Type	GeneralStockerContainer::GetType(const QString &Keyword)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ExistsKeyword(Keyword)==true){
			return s->GetType(Keyword);
		}
	}
	return QVariant::Invalid;
}

bool	GeneralStockerContainer::GetData(const QString &Keyword 
										,QVariantList &ReturnValue,QVariantList &ArgValue)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ExistsKeyword(Keyword)==true){
			return s->GetData(GetLayersBase(),Keyword 
							,ReturnValue,ArgValue);
		}
	}
	return false;
}

bool	GeneralStockerContainer::ShowDialog(const QString &Keyword, QWidget *parent)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ExistsKeyword(Keyword)==true){
			bool	ret=s->ShowDialog(Keyword, parent);
			if(ret==true){
				QFile	FL(GetFileName());	
				if(FL.open(QIODevice::WriteOnly)==true){
					struct	PropertyGeneralStocker	Prop;
					Save(&FL,Prop);
				}
			}
			return ret;
		}
	}
	return false;
}

int	GeneralStockerContainer::GetCountOfEffectiveShowDialog(const QString &Keyword)
{
	int	Counter=0;
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->DLL_ShowDialog!=NULL){
			Counter++;
		}
	}
	return Counter;
}

GeneralStocker	*GeneralStockerContainer::GetShowDialogPointer(int n)
{
	int	Counter=0;
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->DLL_ShowDialog==NULL){
			continue;
		}
		if(Counter==n){
			return s;
		}
		Counter++;
	}
	return NULL;
}

void	GeneralStockerContainer::TransmitDirectly(const QString &Keyword ,GUIDirectMessage *packet)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ExistsKeyword(Keyword)==true){
			s->TransmitDirectly(packet);
		}
	}
}

void	GeneralStockerContainer::TransmitDirectly(GUIDirectMessage *packet)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->TransmitDirectly(packet);
	}
}
void	GeneralStockerContainer::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->SpecifiedDirectly(v);
	}
}
void	GeneralStockerContainer::TransmitDirectlyByName(const QString &GeneralStockerDLLName ,GUIDirectMessage *packet)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Name==GeneralStockerDLLName){
			s->TransmitDirectly(packet);
		}
	}
}

bool			GeneralStockerContainer::Save(QIODevice *f,struct	PropertyGeneralStocker &Prop)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}

	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if((Prop.SaveInMasterData==true && s->GetSynchronizeToSlave()==false)
		|| (Prop.SynchronizeToSlave==true && s->GetSynchronizeToSlave()==false))
			continue;
		QString	NameStr=s->GetName();
		if(::Save(f,NameStr)==false){
			return false;
		}
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool			GeneralStockerContainer::Load(QIODevice *f,struct	PropertyGeneralStocker &Prop)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		QString	NameStr;
		if(::Load(f,NameStr)==false){
			return false;
		}
		GeneralStocker *s;
		for(s=GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetName()==NameStr){
				if((Prop.SaveInMasterData==true && s->GetSynchronizeToSlave()==false)
				|| (Prop.SynchronizeToSlave==true && s->GetSynchronizeToSlave()==false))
					break;
				if(s->Load(f)==false){
					return false;
				}
				break;
			}
		}
		if(s==NULL){
			return false;
		}
	}
	return true;
}
bool	GeneralStockerContainer::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(GeneralStocker *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

QString	GeneralStockerContainer::GetFileName(void)
{
	return GetLayersBase()->GetUserPath()+GetSeparator()+GetParamGlobal()->GeneralStockerFileName;
}

ExeResult	GeneralStockerContainer::ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteInitialAfterEditPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteInitialAfterEditPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteStartByInspectionPrev(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteStartByInspectionPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteStartByInspectionPost(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteStartByInspectionPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}

ExeResult	GeneralStockerContainer::ExecuteCapturedPrev	(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteCapturedPrev	(ExeID,Res,CapturedList);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteCapturedPost	(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteCapturedPost	(ExeID,Res,CapturedList);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePreAlignmentPrev	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePreAlignmentPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePreAlignmentPost	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePreAlignmentPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteAlignmentPrev		(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteAlignmentPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteAlignmentPost		(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteAlignmentPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePreProcessingPrev	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePreProcessingPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePreProcessingPost	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePreProcessingPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteProcessingPrev		(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteProcessingPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteProcessingPost		(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteProcessingPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteProcessingRevivedPrev(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteProcessingRevivedPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecuteProcessingRevivedPost(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecuteProcessingRevivedPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePostProcessingPrev	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePostProcessingPrev	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}
ExeResult	GeneralStockerContainer::ExecutePostProcessingPost	(int ExeID ,ResultInspection *Res)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		ExeResult	Ret=s->ExecutePostProcessingPost	(ExeID,Res);
		if(Ret!=_ER_true && Ret!=_ER_NoFunc){
			return Ret;
		}
	}
	return _ER_true;
}


bool	GeneralStockerContainer::CreateExcludedList(ExcludedListPack &EList)
{
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->CreateExcludedList(EList)==false){
			return false;
		}
	}
	return true;
}
