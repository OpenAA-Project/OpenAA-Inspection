#include "XTypeDef.h"
#include "XResultAnalizer.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include <QFile>
#include "XDataAlgorithm.h"
#include "XIntClass.h"

bool	ResultAnalizerItemBase::ShowResultDialogFunc(AlgorithmBase *ABase,int Phase ,int GlobalPage,int Layer,int ItemID)
{
	GUICmdReqResultAnalizerShowData	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
	GUICmdAckResultAnalizerShowData	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
	ABase->GetAlgorithmRootName(RCmd.AlgoRoot,RCmd.AlgoName);
	RCmd.ResultAnalizerItemBaseID	=ID;
	RCmd.Phase	=Phase;
	RCmd.Layer	=Layer;
	RCmd.ItemID	=ItemID;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		if(ACmd.Effective==true){
			return ShowResultDialogFunc(ACmd.DataForShow);
		}
	}
	return false;
}
ExeResult	ResultAnalizerItemBase::ExecuteInitialAfterEditPost	(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteInitialAfterEditPost!=NULL){
			return DLLHandle->DLL_ExecuteInitialAfterEditPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecuteStartByInspectionPost(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteStartByInspectionPost!=NULL){
			return DLLHandle->DLL_ExecuteStartByInspectionPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecuteCapturedPost		(int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteCapturedPost!=NULL){
			return DLLHandle->DLL_ExecuteCapturedPost	(this,ExeID,Res,CapturedList);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecutePreAlignmentPost		(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecutePreAlignmentPost!=NULL){
			return DLLHandle->DLL_ExecutePreAlignmentPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecuteAlignmentPost		(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteAlignmentPost!=NULL){
			return DLLHandle->DLL_ExecuteAlignmentPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecutePreProcessingPost	(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecutePreProcessingPost!=NULL){
			return DLLHandle->DLL_ExecutePreProcessingPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecuteProcessingPost		(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteProcessingPost!=NULL){
			return DLLHandle->DLL_ExecuteProcessingPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecuteProcessingRevivedPost(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecuteProcessingRevivedPost!=NULL){
			return DLLHandle->DLL_ExecuteProcessingRevivedPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

ExeResult	ResultAnalizerItemBase::ExecutePostProcessingPost	(int ExeID ,ResultInItemRoot *Res)
{
	if(DLLHandle!=NULL){
		if(DLLHandle->DLL_ExecutePostProcessingPost!=NULL){
			return DLLHandle->DLL_ExecutePostProcessingPost	(this,ExeID,Res);
		}
	}
	return _ER_NoFunc;
}

void		ResultAnalizerItemBaseContainer::TransmitDirectly(GUIDirectMessage *packet)
{
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

bool		ResultAnalizerItemBaseContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		QString	DLLRoot;
		QString	DLLName;
		a->DLLHandle->GetRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		if(::Save(f,a->Name)==false){
			return false;
		}
		if(::Save(f,a->ID)==false){
			return false;
		}
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(a->Save(&Buff)==false){
			return false;
		}
		QByteArray	Array=Buff.buffer();
		if(::Save(f,Array)==false){
			return false;
		}

	}
	return true;
}
bool		ResultAnalizerItemBaseContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}

	for(int i=0;i<N;i++){
		QString	DLLRoot;
		QString	DLLName;
		QString	Name;
		int32	ID;
		if(::Load(f,DLLRoot)==false){
			return false;
		}
		if(::Load(f,DLLName)==false){
			return false;
		}
		if(::Load(f,Name)==false){
			return false;
		}
		if(::Load(f,ID)==false){
			return false;
		}
		QByteArray	Array;
		if(::Load(f,Array)==false){
			return false;
		}
		for(ResultAnalizerDLL *DLL=GetLayersBase()->GetResultAnalizerDLLContainer()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			QString		LRoot ,LName;
			DLL->GetRootName(LRoot ,LName);
			if(LRoot==DLLRoot && LName==DLLName){
				ResultAnalizerItemBase	*a=DLL->InitialCreate();
				if(a!=NULL){
					a->SetLayersBase(GetLayersBase());
					a->DLLHandle=DLL;
					a->SetName(LName);
					a->SetID(ID);
					QBuffer	Buff(&Array);
					Buff.open(QIODevice::ReadOnly);
					if(a->Load(&Buff)==true){
						AppendList(a);
					}
					else{
						delete	a;
					}
				}
				break;
			}
		}
	}
	return true;
}
	
bool	ResultAnalizerItemBaseContainer::LoadDefault(void)
{
	QString	DefaultFileName= GetLayersBase()->GetUserPath()
							+QDir::separator()
							+GetParamGlobal()->ResultAnalizerFileName;
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		return Load(&File);
	}
	return false;
}

bool	ResultAnalizerItemBaseContainer::SaveDefault(void)
{
	QString	DefaultFileName= GetLayersBase()->GetUserPath()
							+QDir::separator()
							+GetParamGlobal()->ResultAnalizerFileName;
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		return Save(&File);
	}
	return false;
}

int		ResultAnalizerItemBaseContainer::GetMaxID(void)	const
{
	int	MaxID=0;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(MaxID<a->GetID()){
			MaxID=a->GetID();
		}
	}
	return MaxID;
}

ResultAnalizerItemBase	*ResultAnalizerItemBaseContainer::FindByID(int ResultAnalizerItemBaseID)
{
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID==ResultAnalizerItemBaseID){
			return a;
		}
	}
	return NULL;
}
	
bool	ResultAnalizerItemBaseContainer::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	Ret=true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->MakeExecuteInitialAfterEditInfo	(ExeID ,Res,EInfo)==false){
			Ret=false;
		}
	}
	return Ret;
}

ExeResult	ResultAnalizerItemBaseContainer::ExecuteInitialAfterEditPost	(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteInitialAfterEditPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecuteStartByInspectionPost	(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteStartByInspectionPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecuteCapturedPost(int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteCapturedPost	(ExeID,Res,CapturedList)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecutePreAlignmentPost		(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecutePreAlignmentPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecuteAlignmentPost			(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteAlignmentPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecutePreProcessingPost		(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecutePreProcessingPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecuteProcessingPost			(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteProcessingPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecuteProcessingRevivedPost	(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecuteProcessingRevivedPost	(ExeID,Res)==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}
ExeResult	ResultAnalizerItemBaseContainer::ExecutePostProcessingPost		(int ExeID ,ResultInItemRoot *Res)
{
	ExeResult	Ret=_ER_true;
	for(ResultAnalizerItemBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExecutePostProcessingPost	(ExeID,Res )==_ER_false){
			Ret=_ER_false;
		}
	}
	return Ret;
}

//=======================================================================================================================================
ResultAnalizerDLL::ResultAnalizerDLL(LayersBase *base)
	:ServiceForLayers(base)
{
	ReEntrantDLL				=false;
	DLL_GetName					=NULL;
	DLL_GetOrganization			=NULL;
	DLL_GetDLLType				=NULL;
	DLL_GetVersion				=NULL;
	DLL_GetSystemVersion		=NULL;
	DLL_AssociateComponent		=NULL;
	DLL_SetLanguage				=NULL;
	DLL_Initial					=NULL;
	DLL_Release					=NULL;
	DLL_CheckParallelExecution	=NULL;

	DLL_ExecuteInitialAfterEditPost	=NULL;
	DLL_ExecuteStartByInspectionPost=NULL;
	DLL_ExecuteCapturedPost			=NULL;
	DLL_ExecutePreAlignmentPost		=NULL;
	DLL_ExecuteAlignmentPost		=NULL;
	DLL_ExecutePreProcessingPost	=NULL;
	DLL_ExecuteProcessingPost		=NULL;
	DLL_ExecuteProcessingRevivedPost=NULL;
	DLL_ExecutePostProcessingPost	=NULL;
}
ResultAnalizerDLL::~ResultAnalizerDLL(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;
	CloseDLL();
	ReEntrantDLL=false;
}

bool	ResultAnalizerDLL::OpenDLL(const QString &DLLFileName)
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
	if(DLL_GetDLLType()!=DLLResultAnalizerMode){
		return false;
	}

	DLL_GetName					=(void (*)(QString &,QString &))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		return false;
	}
	DLL_GetName(Root,Name);

	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_GetSystemVersion		=(const char *(*)(VersionType vtype))DllLib.resolve("DLL_GetSystemVersion");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_Initial					=(ResultAnalizerItemBase *(*)(LayersBase *Base))DllLib.resolve(/**/"DLL_Initial");
	DLL_Release					=(void (*)(ResultAnalizerItemBase *handle))DllLib.resolve(/**/"DLL_Release");
	DLL_CheckParallelExecution	=(bool (*)(ModeParallelExecution mode))DllLib.resolve(/**/"DLL_CheckParallelExecution");

	DLL_ExecuteInitialAfterEditPost		=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecuteInitialAfterEditPost");
	DLL_ExecuteStartByInspectionPost	=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecuteStartByInspectionPost");
	DLL_ExecuteCapturedPost				=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList))DllLib.resolve(/**/"DLL_ExecuteCapturedPost");
	DLL_ExecutePreAlignmentPost			=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecutePreAlignmentPost");
	DLL_ExecuteAlignmentPost			=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecuteAlignmentPost");
	DLL_ExecutePreProcessingPost		=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecutePreProcessingPost");
	DLL_ExecuteProcessingPost			=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingPost");
	DLL_ExecuteProcessingRevivedPost	=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecuteProcessingRevivedPost");
	DLL_ExecutePostProcessingPost		=(ExeResult	(*)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res))DllLib.resolve(/**/"DLL_ExecutePostProcessingPost");

	if(DLL_GetOrganization!=NULL){
		DLL_GetOrganization(Organization);
	}
	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(DLLFileName);
	}

	return true;
}
void	ResultAnalizerDLL::CloseDLL(void)
{
	if(DllLib.isLoaded ()==true){
		DllLib.unload();
	}
}
bool	ResultAnalizerDLL::CheckSystemVersion(QStringList &Str)
{
	return true;
}
void	ResultAnalizerDLL::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}

ResultAnalizerItemBase	*ResultAnalizerDLL::InitialCreate(void)
{
	if(DLL_Initial!=NULL){
		ResultAnalizerItemBase	*a=DLL_Initial(GetLayersBase());
		if(a!=NULL){
			a->DLLHandle=this;
			a->SetLayersBase(GetLayersBase());
			return a;
		}
	}
	return NULL;
}

void	ResultAnalizerDLL::SetLanguage(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
	}
}


bool	ResultAnalizerDLLContainer::OpenDLL(void)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	Path=Path+GetParamGlobal()->ResultAnalizerDLLPath;

	QDir	Dir;
	if(Dir.cd(Path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=Path+GetSeparator()+List[i];
			if(FileName.isEmpty()==false){
				ResultAnalizerDLL	*a=new ResultAnalizerDLL(GetLayersBase());
				if(a->OpenDLL(FileName)==true){
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

void	ResultAnalizerDLLContainer::SetLanguage(int LanguageCode)
{
	for(ResultAnalizerDLL *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetLanguage(LanguageCode);
	}
}


bool	ResultAnalizerDLLContainer::CheckSystemVersion(QStringList &Str)
{
	for(ResultAnalizerDLL *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			return false;
		}
	}
	return true;
}
void	ResultAnalizerDLLContainer::AssociateComponent	 (ComponentListContainer &List)
{
	for(ResultAnalizerDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
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
ResultAnalizerDLL	*ResultAnalizerDLLContainer::Search(const QString &DLLRoot,const QString &DLLName)
{
	for(ResultAnalizerDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		QString _Root ,_Name;
		L->GetRootName(_Root ,_Name);
		if(_Root==DLLRoot && _Name==DLLName){
			return L;
		}
	}
	return NULL;
}
//============================================================================
GUICmdReqResultAnalizerShowData::GUICmdReqResultAnalizerShowData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqResultAnalizerShowData::Load(QIODevice *f)
{
	if(::Load(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Load(f,AlgoRoot				)==false)	return false;
	if(::Load(f,AlgoName				)==false)	return false;
	if(::Load(f,Phase					)==false)	return false;
	if(::Load(f,Layer					)==false)	return false;
	if(::Load(f,ItemID					)==false)	return false;
	return true;
}

bool	GUICmdReqResultAnalizerShowData::Save(QIODevice *f)
{
	if(::Save(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Save(f,AlgoRoot				)==false)	return false;
	if(::Save(f,AlgoName				)==false)	return false;
	if(::Save(f,Phase					)==false)	return false;
	if(::Save(f,Layer					)==false)	return false;
	if(::Save(f,ItemID					)==false)	return false;
	return true;
}

void	GUICmdReqResultAnalizerShowData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultAnalizerShowData	*SendBack=GetSendBack(GUICmdAckResultAnalizerShowData,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);


	ResultAnalizerItemBase	*R=GetLayersBase()->GetResultAnalizerItemBaseContainer()->FindByID(ResultAnalizerItemBaseID);
	if(R!=NULL){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
		if(Ab!=NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					AlgorithmItemRoot	*Item=Ap->GetItemData(Layer,ItemID);
					if(Item!=NULL){
						ResultInItemRoot	*Res=Item->GetCurrentResult();
						if(Res!=NULL){
							SendBack->Effective	=R->MakeDataForShow(Res,SendBack->DataForShow);
						}
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckResultAnalizerShowData::GUICmdAckResultAnalizerShowData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Effective=false;
}

bool	GUICmdAckResultAnalizerShowData::Load(QIODevice *f)
{
	if(::Load(f,Effective)==false)		return false;
	if(::Load(f,DataForShow)==false)	return false;
	return true;
}
bool	GUICmdAckResultAnalizerShowData::Save(QIODevice *f)
{
	if(::Save(f,Effective)==false)		return false;
	if(::Save(f,DataForShow)==false)	return false;
	return true;
}