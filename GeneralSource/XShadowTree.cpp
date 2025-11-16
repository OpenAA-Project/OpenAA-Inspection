#include "XTypeDef.h"
#include "XShadowTree.h"
#include "XShadowControlInterface.h"
#include "XGeneralFunc.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XIntClass.h"
#include "XWriteResultThread.h"
#include "XGUI.h"
#include "XDateTime.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include "XResult.h"
#include "XFileThread.h"
#include "XDataInLayerCmdLocal.h"
#include "XLearningRegist.h"
#include "XDataAlgorithmList.h"
#include "XDataAlgorithm.h"

ShadowTree::ShadowTree(int _ShadowNumber ,LayersBase *ParentBase)
	:PipeShadowTree(this),ShadowNumber(_ShadowNumber)
{
	ShadowInterface	=NULL;

	if(_ShadowNumber==-1){
		LayersBasePointer=ParentBase;
	}
	else{
		LayersBasePointer=NULL;
	}
	ParentPointer	=ParentBase;
	Children=new ShadowControlInterfaceContainer(ParentPointer);
}

ShadowTree::ShadowTree(const ShadowTree &src)
:PipeShadowTree(this),ShadowNumber(src.ShadowNumber)
{
	ShadowInterface=src.ShadowInterface;

	LayersBasePointer=src.LayersBasePointer;

	ParentPointer	=src.ParentPointer;
	Children=new ShadowControlInterfaceContainer(ParentPointer);

	ShadowDLLFileName	=src.ShadowDLLFileName		;
	ShadowGlobalFileName=src.ShadowGlobalFileName	;
	ShadowGUIFileName	=src.ShadowGUIFileName		;
	Param				=src.Param					;
}

ShadowTree::~ShadowTree(void)
{
	if(LayersBasePointer!=NULL && ShadowInterface!=NULL){
		ShadowInterface->Close(this);
		LayersBasePointer=NULL;
	}
	ShadowInterface=NULL;

	delete	Children;
	Children=NULL;
}

ShadowTree	&ShadowTree::operator=(const ShadowTree &src)
{
	if(ShadowInterface!=NULL){
		if(src.ShadowInterface!=NULL){
			if(ShadowInterface->GetLibraryFileName()!=src.ShadowInterface->GetLibraryFileName()){
				ShadowInterface->Close(this);
			}
		}
	}
	ShadowInterface=src.ShadowInterface;
	LayersBasePointer=src.LayersBasePointer;
	ParentPointer	=src.ParentPointer;
	if(Children!=NULL){
		delete	Children;
	}
	Children=new ShadowControlInterfaceContainer(ParentPointer);
	*Children=*src.Children;

	ShadowDLLFileName	=src.ShadowDLLFileName		;
	ShadowGlobalFileName=src.ShadowGlobalFileName	;
	ShadowGUIFileName	=src.ShadowGUIFileName		;
	Param				=src.Param					;
	return *this;
}
	
ShadowControlInterface	*ShadowTree::GetShadowInterface(void)
{
	return ShadowInterface;
}

void	ShadowTree::SetInterface(ShadowControlInterface *iface)
{
	ShadowInterface=iface;
}

bool	ShadowTree::LoadShadowChildrenDLL(void)
{
	if(GetShadowLevel()>0){
		if(GetTreeLayersBase()->GetParamGlobal()->ShadowParameterData==GetParentLayersBase()->GetParamGlobal()->ShadowParameterData){
			GetTreeLayersBase()->GetParamGlobal()->ShadowParameterData.RemoveAll();
		}
	}

	if(Children->InitialDLL()==false){
		return false;
	}
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ShadowTree	*t=c->GetInstance();
		QString	ParamFileName=t->GetShadowParamFileName();
		if(ParamFileName.isEmpty()==false){
			QDir::setCurrent(GetTopLayersBase()->GetUserPath());
			QFile	File(ParamFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				t->LoadShadowParam(&File);
			}
		}
	}
	return true;
}

int		ShadowTree::GetIDInClass(void)	const
{
	return 0;
}
int		ShadowTree::GetLevel(void)	const
{
	return 0;
}
int		ShadowTree::GetUniqueID(void)	const
{
	return 0;
}

QString	ShadowTree::GetShadowDLLFileName(void)	const
{	
	return ShadowDLLFileName;
}
QString	ShadowTree::GetShadowGlobalFileName(void)	const
{
	return ShadowGlobalFileName;
}
QString	ShadowTree::GetShadowGUIFileName(void)	const
{
	return ShadowGUIFileName;
}
QString	ShadowTree::GetShadowParamFileName(void)	const
{
	return Param.ShadowParamFileName;
}
void	ShadowTree::SetShadowDLLFileName	(const QString &filename)
{
	ShadowDLLFileName=filename;
}
void	ShadowTree::SetShadowGlobalFileName	(const QString &filename)
{
	ShadowGlobalFileName=filename;
}
void	ShadowTree::SetShadowGUIFileName	(const QString &filename)
{
	ShadowGUIFileName=filename;
}
void	ShadowTree::SetParam(const ShadowParameter &s)
{
	Param=s;
}

int		ShadowTree::GetShadowChildrenCount(void)	const
{
	return Children->GetCount();
}
int		ShadowTree::GetShadowTotalChildrenCount(void)	const
{
	int	N=Children->GetCount();
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		N+=ShadowTreeChild->GetShadowTotalChildrenCount();
	}
	return N;
}
ShadowTree	*ShadowTree::GetShadowChildren(int n)	const
{
	ShadowControlInterface	*s=Children->GetItem(n);
	if(s!=NULL){
		return s->GetInstance();
	}
	return NULL;
}

bool	ShadowTree::SaveShadowParam(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(Children->SaveShadowParam(f)==false){
		return false;
	}
	return true;
}
bool	ShadowTree::LoadShadowParam(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(Children->LoadShadowParam(f)==false){
		return false;
	}
	return true;
}

void	ShadowTree::SetTreeLayersBase(LayersBase *s)
{	
	LayersBasePointer=s;
	if(Children!=NULL){
		delete	Children;
	}
	Children=new ShadowControlInterfaceContainer(LayersBasePointer);
}
bool	ShadowTree::InitialInShadow(void)
{
	if(GetShadowGlobalFileName().isEmpty()==false){
		GetTreeLayersBase()->GetParamGlobal()->SetDefaultFileName(GetShadowGlobalFileName());
	}
	else{
		GetTreeLayersBase()->GetParamGlobal()->SetDefaultFileName(GetParentLayersBase()->GetParamGlobal()->GetDefaultFileName());
	}
	GetTreeLayersBase()->GetParamComm()->SetDefaultFileName(GetParentLayersBase()->GetParamComm()->GetDefaultFileName());

	if(GetTreeLayersBase()->GetParamGlobal()->LoadDefault(GetTopLayersBase()->GetUserPath())==false){
		return false;
	}
	return true;
}

int		ShadowTree::GetShadowLevel(void)	const
{
	if(GetParentLayersBase()==GetTreeLayersBase())
		return 0;
	return GetParentLayersBase()->GetShadowLevel()+1;
}

LayersBase	*ShadowTree::GetTopLayersBase(void)	const
{
	if(GetParentLayersBase()==GetTreeLayersBase())
		return GetTreeLayersBase();
	return GetParentLayersBase()->GetTopLayersBase();
}

LayersBase	*ShadowTree::GetShadowTree(int ShadowLevel ,int ShadowNumber)	const
{
	LayersBase	*L=GetTopLayersBase();
	if(ShadowLevel==0 && ShadowNumber==0){
		return L;
	}
	ShadowTree	*R=L->GetShadowTreeInner(ShadowLevel ,ShadowNumber);
	if(R!=NULL){
		return R->GetTreeLayersBase();
	}
	return NULL;
}

ShadowTree	*ShadowTree::GetShadowTreeInner(int _ShadowLevel ,int _ShadowNumber)	const
{
	if(GetShadowLevel()==_ShadowLevel && GetShadowNumber()==_ShadowNumber){
		return (ShadowTree *)this;
	}
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		ShadowTree	*R=ShadowTreeChild->GetShadowTreeInner(_ShadowLevel ,_ShadowNumber);
		if(R!=NULL){
			return R;
		}
	}
	return NULL;
}

void	ShadowTree::GatherUsedLibInfoList(LibInfoListContainer &Ret)
{
	for(LogicDLL *L=GetTreeLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
	    LibInfoList *t=new LibInfoList();
	    AlgorithmBase	*ABase=L->GetInstance();
	    ABase->EnumLibID(t->LibIDs);
	    if(t->LibIDs.GetCount()!=0){
	        t->LibType=ABase->GetLibType();
	        if(Ret.AppendMerge(t)==false){
	            delete  t;
	        }
	    }
	    else{
	        delete  t;
	    }
	}
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		ShadowTreeChild->GatherUsedLibInfoList(Ret);
	}
}

static  bool FuncLibDataList(void *caller,AlgorithmItemRoot *item)
{
    int LibID=*((int *)caller);
    if(item->GetLibID()==LibID){
        return true;
    }
    return false;
}
void	ShadowTree::SetLibDataList(LibDataList &src)
{
	AlgorithmBase	*ABase=GetTreeLayersBase()->GetAlgorithmBase(src.LibType);
	if(ABase!=NULL){
		AlgorithmItemPointerListContainer Items;
		ABase->EnumItems(&src.LibID,Items , FuncLibDataList);
		for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
		    AlgorithmItemRoot   *Item=p->GetItem();
            QBuffer ABuff(&src.LibData);
            if(ABuff.open(QIODevice::ReadWrite)==true){
				Item->GetThresholdBaseWritable()->Load(&ABuff);
			}
		}
	}
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		ShadowTreeChild->SetLibDataList(src);
	}
}

ShadowTree	*ShadowTree::FindShadowTree(int UniqueID)	const
{
	LayersBase	*Top=GetTopLayersBase();
	return Top->FindShadowTreeInner(UniqueID);
}

ShadowTree	*ShadowTree::FindShadowTreeInner(int UniqueID)	const
{
	if(GetUniqueID()==UniqueID)
		return (ShadowTree	*)this;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild->GetUniqueID()==UniqueID){
			return ShadowTreeChild;
		}
		ShadowTree	*w=ShadowTreeChild->FindShadowTreeInner(UniqueID);
		if(w!=NULL){
			return w;
		}
	}
	return NULL;
}
void	ShadowTree::SetMasterCodeInTree(int MasterCode)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		ShadowTreeChild->SetMasterCode(MasterCode);
		ShadowTreeChild->SetMasterCodeInTree(MasterCode);
	}
}

ExeResult	ShadowTree::ChildrenExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteInitialAfterEdit(EInfo,ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteStartByScanOnly	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteStartByScanOnly(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteStartByInspection(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteStartByInspection(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteCaptured	(ListPhasePageLayerPack &CapturedList ,bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteCaptured(CapturedList,ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecutePreAlignment	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecutePreAlignment(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteAlignment(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteAlignment(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecutePreProcessing(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecutePreProcessing(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteProcessing(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	ResultInspection	*ParentResult=GetParentLayersBase()->GetCurrentResultForCalc();
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ParentResult->SetShadowResult(ShadowTreeChild->GetCurrentResultForCalc(),ShadowTreeChild->GetShadowNumber());
			ExeResult	R=ShadowTreeChild->ExecuteProcessing(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteProcessingRevived(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteProcessingRevived(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecutePostProcessing	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecutePostProcessing(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecutePreScanning	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecutePreScanning(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecuteScanning	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecuteScanning(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenExecutePostScanning	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->ExecutePostScanning(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
ExeResult	ShadowTree::ChildrenPretendFinishProcessing	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			ExeResult	R=ShadowTreeChild->PretendFinishProcessing(ProgressStep);
			if(R!=_ER_true){
				Ret=R;
			}
		}
	}
	return Ret;
}
bool	ShadowTree::ReallocateMasterCountShadow(int CountMaster)
{
	bool	Ret=true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		if(ShadowTreeChild!=NULL){
			if(ShadowTreeChild->ReallocateMasterCount(CountMaster)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	ShadowTree::SetThresholdLevelShadowTree(int LevelParentID ,int LevelID)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*ShadowTreeChild=dynamic_cast<LayersBase *>(c->GetInstance());
		ShadowTreeChild->SetThresholdLevel(LevelParentID ,LevelID);
	}
}
//--------------------------------------------------------------------------
bool	ShadowTree::GetShadowResult(ResultInspection *ParentResultInspection
							,bool3 &Ok ,bool &TimeOver, bool &MaxError
							,bool DependOnPhaseMode,bool DependOnPageMode)
{
	Ok=true3;
	TimeOver=false;
	MaxError=false;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r==NULL){
			return false;
		}
		bool3	tOk=true3;
		bool	tTimeOver=false;
		bool	tMaxError=false;
		if(c->GetInstance()->GetShadowResultInChildren(r 
							,tOk ,tTimeOver, tMaxError
							,DependOnPhaseMode,DependOnPageMode)==false){
			return false;
		}
		if(tOk==false3)
			Ok=false3;
		if(tTimeOver==true)
			TimeOver=true;
		if(tMaxError==true)
			MaxError=true;
	}
	return true;
}
bool	ShadowTree::GetShadowResultInChildren(ResultInspection *Res
									,bool3 &Ok ,bool &TimeOver, bool &MaxError
									,bool DependOnPhaseMode,bool DependOnPageMode)
{
	if(Res!=NULL){
		Res->GatherResult(Ok ,MaxError , TimeOver,DependOnPhaseMode,DependOnPageMode);
		return true;
	}
	return  false;
}

void	ShadowTree::ShowShadowHistory(int ResultCode
										,bool DependOnPhaseMode,bool DependOnPageMode
										, DWORD InspectionTimeMilisec)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->ShowShadowHistoryInChildren(ResultCode, DependOnPhaseMode,DependOnPageMode,InspectionTimeMilisec);
	}
}
void	ShadowTree::ShowShadowHistoryInChildren(int ResultCode
												,bool DependOnPhaseMode,bool DependOnPageMode
												,DWORD InspectionTimeMilisec)
{
	LayersBase	*L=GetTreeLayersBase();
	ResultInspection	*eRes=GetTreeLayersBase()->GetCurrentResultForCalc();
	if(eRes!=NULL){
		bool3	Ok;
		bool	TimeOver;
		bool	MaxError;
		eRes->GatherResult(Ok ,MaxError , TimeOver,DependOnPhaseMode,DependOnPageMode);

		L->SetInspectionTimeMilisec(InspectionTimeMilisec);
		L->SetEndInspectionTime(XDateTime::currentDateTime());
		L->GetResultHistryData()->AddHistry(ResultCode
											,eRes->GetStartTimeForInspection()
											,L->GetCurrentInspectIDForExecute()
											,eRes->GetIDStr()
											,TimeOver
											,MaxError
											,eRes->ExecTime.TM_TotalProcessMilisec);
	
		eRes->SetInspectionID(L->GetCurrentInspectIDForExecute());
	}

	L->IncrementInspectID();
}

void	ShadowTree::MakeShadowLayersBasePointer(NPListPack<LayersBasePointerList> &ShadowLayersBasePointer)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ShadowLayersBasePointer.AppendList(new LayersBasePointerList(c->GetInstance()->GetTreeLayersBase()));
		c->GetInstance()->MakeShadowLayersBasePointer(ShadowLayersBasePointer);
	}
}

//--------------------------------------------------------------------------

bool	ShadowTree::ReallocateShadow(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	bool	Ret=true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()->ReallocateShadowInChild(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	ShadowTree::ReallocateShadow(int newPhaseNumb)
{
	bool	Ret=true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()->ReallocateShadowInChild(newPhaseNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ShadowTree::InsertPageShadow(int IndexPage)	//Create page before Indexed page
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->InsertPageShadowInChild(IndexPage);
	}
}
bool	ShadowTree::RemovePageShadow(int IndexPage)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->RemovePageShadowInChild(IndexPage);
	}
}

bool	ShadowTree::ReallocateShadowInChild(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	return GetTreeLayersBase()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
}

bool	ShadowTree::ReallocateShadowInChild(int newPhaseNumb)
{
	return GetTreeLayersBase()->Reallocate(newPhaseNumb);
}

bool	ShadowTree::ReallocXYPixelsShadow(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()->ReallocXYPixelsShadowInChild(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ShadowTree::ReallocXYPixelsShadowInChild(int NewDotPerLine ,int NewMaxLines)
{
	return GetTreeLayersBase()->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}

void	ShadowTree::InsertPageShadowInChild(int IndexPage)
{
	GetTreeLayersBase()->InsertPage(IndexPage);
}
void	ShadowTree::RemovePageShadowInChild(int IndexPage)
{
	GetTreeLayersBase()->RemovePage(IndexPage); 
}

void	ShadowTree::ShadowCopyPageData(int DstPage ,int SrcPage ,bool ModeCopyAllAlgorithm ,bool ModeCopyAllFilter)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*LBase=c->GetInstance()->GetTreeLayersBase();
		LBase->CopyPageData(DstPage ,SrcPage ,ModeCopyAllAlgorithm ,ModeCopyAllFilter);
	}
}


void	ShadowTree::CopyShadowMasterToChildren(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->CopyMasterFromParant();
		c->GetInstance()->CopyShadowMasterToChildren();
	}
}

void	ShadowTree::CopyMasterFromParant(void)
{
	if(GetShadowLevel()>0){
		LayersBase	*Pr=GetTopLayersBase ();
		LayersBase	*Cr=GetTreeLayersBase();
		Cr->SetMasterCode		(Pr->GetMasterCode());
		Cr->SetMasterName		(Pr->GetMasterName());
		Cr->SetMachineID		(Pr->GetMachineID());
		Cr->SetRemark			(Pr->GetRemark());
		Cr->SetMachineIDFromMaster(Pr->GetMachineIDFromMaster());
		Cr->SetRegTime			(Pr->GetRegTime());
		Cr->SetWorkerID			(Pr->GetWorkerID());
		Cr->SetWorkerName		(Pr->GetWorkerName());
		Cr->SetVersion			(Pr->GetVersion());
		Cr->SetLoadedVersion	(Pr->GetLoadedVersion());
		Cr->SetLastEditTime		(Pr->GetLastEditTime());
		Cr->SetCategoryID		(Pr->GetCategoryID());
		Cr->SetInspectionRemark	(Pr->GetInspectionRemark());
		Cr->SetMasterType		(Pr->GetMasterType());

		Cr->SetStartInspectionTimeMilisec	(Pr->GetStartInspectionTimeMilisec	());
		Cr->SetInspectionTimeMilisec		(Pr->GetInspectionTimeMilisec		());
		Cr->SetResultWrittenID				(Pr->GetResultWrittenID());
		Cr->SetInspectionNumber				(Pr->GetInspectionNumber());
		Cr->SetLatchedInspectionNumber		(Pr->GetLatchedInspectionNumber());
		Cr->SetSelectedImagePath			(Pr->GetSelectedImagePath());
		Cr->SetThresholdLevel				(Pr->GetThresholdLevelID());
	}
}
bool	ShadowTree::CopyShadowAlgorithmToChildren(void)
{
	bool	Ret=true;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*Pr=c->GetInstance()->GetParentLayersBase ();
		LayersBase	*Cr=c->GetInstance()->GetTreeLayersBase();
		for(LogicDLL *Lp=Pr->GetLogicDLLBase()->GetFirst();Lp!=NULL;Lp=Lp->GetNext()){
			for(LogicDLL *Lc=Cr->GetLogicDLLBase()->GetFirst();Lc!=NULL;Lc=Lc->GetNext()){
				if(Lp->GetDLLRoot()==Lc->GetDLLRoot()
				&& Lp->GetDLLName()==Lc->GetDLLName()){
					if(CopyShadowAlgorithmBase(c->GetInstance(),*Lp->GetInstance(),Lc->GetInstance())==false){
						Ret=false;
					}
				}
			}
		}
	}
	return Ret;
}
bool	ShadowTree::CopyShadowAlgorithmBase(ShadowTree *Child,const AlgorithmBase &ParentABase, AlgorithmBase *ChildBase)
{
	bool	Ret=true;
	LayersBase	*PL=ParentABase.GetLayersBase();
	if(PL!=NULL && PL->GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<PL->GetPageNumb();page++){
			for(int phase=0;phase<PL->GetPhaseNumb();phase++){
				GUICmdCopyShadowAlgorithm	RCmd(PL ,/**/"ANY",/**/"ANY",page);
				ParentABase.GetDLLName(RCmd.DLLRoot,RCmd.DLLName);
				RCmd.Phase			=phase;
				RCmd.ParentShadowLevel	=GetShadowLevel();
				RCmd.ParentShadowNumber	=GetShadowNumber();
				RCmd.ChildShadowLevel	=Child->GetShadowLevel();
				RCmd.ChildShadowNumber	=Child->GetShadowNumber();
				if(RCmd.Send(NULL,page,0)==false){
					Ret=false;
				}
			}
		}
	}
	return Ret;
}
bool	ShadowTree::CopyShadowAlgorithmPage(const AlgorithmInPageRoot &ParentAPage, AlgorithmInPageRoot *ChildPage)
{
	return ChildPage->CopyShadowAlgorithmPage(this, ParentAPage);
}
bool	ShadowTree::CopyShadowAlgorithmLayer(const AlgorithmInLayerRoot &ParentALayer, AlgorithmInLayerRoot *ChildLayer)
{
	return ChildLayer->CopyShadowAlgorithmLayer(this, ParentALayer);
}

bool	ShadowTree::CopyShadowAlgorithmItem(AlgorithmParentFromItem *ParentG, const AlgorithmItemRoot &ParentItem)
{
	return ParentG->CopyShadowAlgorithmItem(this, ParentItem);
}

bool	ShadowTree::SaveShadowChildrenGUIContent(int _MachineID,const QString &ImagePath)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->SaveShadowChildrenGUIContent(_MachineID,ImagePath,N)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::LoadShadowChildrenGUIContent(int _MachineID)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->LoadShadowChildrenGUIContent(_MachineID,N)==false){
			return false;
		}
	}
	return true;

}
bool	ShadowTree::SaveShadowChildrenGUIContent(int _MachineID,const QString &ImagePath ,int _ShadowNumber)
{
	LayersBase	*Ly=GetTreeLayersBase();
	QString	GUIContentFileName=Ly->CreateGUIContentFileName(Ly->GetMasterCode(),_MachineID ,ImagePath
										,GetShadowLevel(),_ShadowNumber);
	if(Ly->SaveGUIContent(GUIContentFileName)==false){
		GSleep(Ly->GetParamGlobal()->WaitingMilisecForRetryLoading);
		if(Ly->SaveGUIContent(GUIContentFileName)==false){
			GSleep(Ly->GetParamGlobal()->WaitingMilisecForRetryLoading*1.5);
			if(Ly->SaveGUIContent(GUIContentFileName)==false){
				GSleep(Ly->GetParamGlobal()->WaitingMilisecForRetryLoading*2);
				return false;
			}
		}
	}
	SaveShadowChildrenGUIContent(_MachineID,ImagePath);
	return true;
}
bool	ShadowTree::LoadShadowChildrenGUIContent(int _MachineID,int _ShadowNumber)
{
	LayersBase	*Ly=GetTreeLayersBase();

	QStringList	ImagePathes=Ly->GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	QString		GUIContentFileName;
	bool		FoundGUIContentFileName=false;
	for(int h=0;h<ImagePathes.count();h++){
		ImagePath=ImagePathes[h];
		GUIContentFileName=Ly->CreateGUIContentFileName(Ly->GetMasterCode(),Ly->GetMachineID(),ImagePath
														,GetShadowLevel(),_ShadowNumber);
		if(QFile::exists(GUIContentFileName)==true){
			FoundGUIContentFileName=true;
			break;
		}
	}
	if(FoundGUIContentFileName==false){
		if(ImagePathes.count()==0)
			ImagePath=/**/"";
		else
			ImagePath=ImagePathes[0];
		GUIContentFileName=Ly->CreateGUIContentFileName(Ly->GetMasterCode(),_MachineID,ImagePath);
	}

	if(Ly->GetParamGlobal()->RetryLoadIfFails==true){
		for(int h=0;h<Ly->GetParamGlobal()->CountToRetryLoading;h++){
			if(Ly->LoadGUIContent(GUIContentFileName)==true){
				break;
			}
			GSleep(Ly->GetParamGlobal()->WaitingMilisecForRetryLoading);
		}
	}
	else{
		Ly->LoadGUIContent(GUIContentFileName);
	}
	return true;
}

bool	ShadowTree::SaveShadowParamInChildren(QIODevice *f)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()->GetTreeLayersBase()->GetParamComm()->SaveParam(f)==false){
			return false;
		}
		if(c->GetInstance()->SaveShadowParamInChildren(f)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::LoadShadowParamInChildren(QIODevice *f)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetInstance()->GetTreeLayersBase()->GetParamComm()->LoadParam(f)==false){
			return false;
		}
		if(c->GetInstance()->LoadShadowParamInChildren(f)==false){
			return false;
		}
	}
	return true;
}

void	ShadowTree::CopyShadowImageFromParent(bool Mastered ,int MasterNo
											,int Phase ,int Page)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		PageDataInOnePhase	*SrcPh=GetParentLayersBase()->GetPageDataPhase(Phase);
		//PageDataInOnePhase	*DstPh=c->GetInstance()->GetTreeLayersBase()->GetPageDataPhase(Phase);
		if(SrcPh!=NULL){
			DataInPage	*SrcPg=SrcPh->GetPageData(Page);
			if(SrcPg!=NULL){
				if(Mastered==false || MasterNo<GetTreeLayersBase()->GetParamGlobal()->AllocatedCountMasterBuff){
					c->GetInstance()->CopyShadowImageFromParentInChild(Mastered ,MasterNo,SrcPg,Phase ,Page);
				}
			}
		}
	}
}

bool	ShadowTree::SaveShadowMasterImageFileInChildren(int32 masterCode, int32 machineID,const QString &ImagePath,bool ForceSave
												,int LocalPhase,int LocalPage)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->SaveShadowMasterImageFileInChildren(masterCode, machineID,ImagePath,ForceSave
												,LocalPhase,LocalPage,N)==false)
			return false;
	}
	return true;
}

bool	ShadowTree::LoadShadowMasterImageFileInChildren(int32 masterCode, int32 machineID,const QString &ImagePath
												,int LocalPhase,int LocalPage)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->LoadShadowMasterImageFileInChildren(masterCode, machineID,ImagePath
												,LocalPhase,LocalPage,N)==false)
			return false;
	}
	return true;
}

bool	ShadowTree::SaveShadowMasterImageFileInChildren(int32 masterCode, int32 machineID,const QString &ImagePath,bool ForceSave
												,int LocalPhase,int LocalPage,int _ShadowNumber)
{
	LayersBase			*L =GetTreeLayersBase();
	PageDataInOnePhase	*Ph=L->GetPageDataPhase(LocalPhase);
	if(Ph==NULL){
		return true;
	}
	DataInPage			*Dp=Ph->GetPageData(LocalPage);
	if(Dp==NULL){
		return true;
	}

	QString	ImageFileName=Dp->CreateMasterImageFileName(masterCode,machineID,ImagePath
														,GetShadowLevel(),_ShadowNumber);
	if(Dp->SaveMasterImageFile(ImageFileName,ForceSave)==false){
		if(L->GetParamGlobal()->RetryLoadIfFails==true){
			GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading+LocalPage*500);
			if(Dp->SaveMasterImageFile(ImageFileName,ForceSave)==false){
				GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*1.5+LocalPage*10000);
				if(Dp->SaveMasterImageFile(ImageFileName,ForceSave)==false){
					GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*2+LocalPage*20000);
					if(Dp->SaveMasterImageFile(ImageFileName,ForceSave)==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool	ShadowTree::LoadShadowMasterImageFileInChildren(int32 masterCode, int32 machineID,const QString &ImagePath
												,int LocalPhase,int LocalPage,int _ShadowNumber)
{
	LayersBase			*L =GetTreeLayersBase();
	PageDataInOnePhase	*Ph=L->GetPageDataPhase(LocalPhase);
	if(Ph==NULL){
		return true;
	}
	DataInPage			*Dp=Ph->GetPageData(LocalPage);
	if(Dp==NULL){
		return true;
	}

	QString	ImageFileName=Dp->CreateMasterImageFileName(masterCode,machineID,ImagePath
														,GetShadowLevel(),_ShadowNumber);
	if(Dp->LoadMasterImageFile(ImageFileName)==false){
		if(L->GetParamGlobal()->RetryLoadIfFails==true){
			GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading+LocalPage*500);
			if(Dp->LoadMasterImageFile(ImageFileName)==false){
				GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*1.5+LocalPage*10000);
				if(Dp->LoadMasterImageFile(ImageFileName)==false){
					GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*2+LocalPage*20000);
					if(Dp->LoadMasterImageFile(ImageFileName)==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool	ShadowTree::SaveShadowLogicFileInChildren(int32 masterCode, int32 machineID
												,const QString &ImagePath
												,int LocalPhase,int LocalPage)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->SaveShadowLogicFileInChildren(masterCode, machineID,ImagePath
												,LocalPhase,LocalPage
												,N)==false)
			return false;
	}
	return true;
}
bool	ShadowTree::LoadShadowLogicFileInChildren(int32 masterCode, int32 machineID, int DataVersion
												,const QString &ImagePath
												,int LocalPhase,int LocalPage)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		if(c->GetInstance()->LoadShadowLogicFileInChildren(masterCode, machineID,DataVersion
												,ImagePath
												,LocalPhase,LocalPage
												,N)==false)
			return false;
	}
	return true;
}
bool	ShadowTree::SaveShadowLogicFileInChildren(int32 masterCode, int32 machineID
											,const QString &ImagePath
											,int LocalPhase,int LocalPage
											,int _ShadowNumber)
{
	LayersBase			*L =GetTreeLayersBase();
	PageDataInOnePhase	*Ph=L->GetPageDataPhase(LocalPhase);
	if(Ph==NULL){
		return true;
	}
	DataInPage			*Dp=Ph->GetPageData(LocalPage);
	if(Dp==NULL){
		return true;
	}

	for(LogicDLL *p=GetTreeLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName().isEmpty()==true){
			continue;
		}
		AlgorithmBase	*base=GetTreeLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
		if(base==NULL){
			continue;
		}
		AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(LocalPhase);
		if(pbase==NULL){
			continue;
		}
		AlgorithmInPageRoot	*ap=pbase->GetPageData(LocalPage);
		if(ap==NULL){
			continue;
		}
		if(base->GetModeLoadSaveInPlayer()==true || (base->GetModeLoadSaveInPlayer()==false 
		&& GetTopLayersBase()->GetModeInspectionPlayer()==false)){
			QString	LogicFileName=Dp->CreateLogicFileName(masterCode,p,machineID,ImagePath
														,GetShadowLevel(),_ShadowNumber);
			if(Dp->SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
				if(L->GetParamGlobal()->RetryLoadIfFails==true){
					GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading);
					if(Dp->SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
						GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*1.5);
						if(Dp->SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
							GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading*2);
							if(Dp->SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
								continue;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool	ShadowTree::LoadShadowLogicFileInChildren(int32 masterCode, int32 machineID, int DataVersion
											,const QString &ImagePath
											,int LocalPhase,int LocalPage
											,int _ShadowNumber)
{
	LayersBase			*L =GetTreeLayersBase();
	PageDataInOnePhase	*Ph=L->GetPageDataPhase(LocalPhase);
	if(Ph==NULL){
		return true;
	}
	DataInPage			*Dp=Ph->GetPageData(LocalPage);
	if(Dp==NULL){
		return true;
	}

	for(LogicDLL *p=GetTreeLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetBlobName().isEmpty()==true){
			continue;
		}
		AlgorithmBase	*base=GetTreeLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
		if(base==NULL){
			continue;
		}
		AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(LocalPhase);
		if(pbase==NULL){
			continue;
		}
		AlgorithmInPageRoot	*ap=pbase->GetPageData(LocalPage);
		if(ap==NULL){
			continue;
		}

		QString	LogicFileName=Dp->CreateLogicFileName(masterCode,p,machineID,ImagePath
													,GetShadowLevel(),_ShadowNumber);
		for(int h=0;h<L->GetParamGlobal()->CountToRetryLoading;h++){
			if(Dp->LoadLogicFile(LogicFileName ,base ,pbase,ap,DataVersion)==true){
				break;
			}
			GSleep(L->GetParamGlobal()->WaitingMilisecForRetryLoading);
		}
	}
	return true;
}

void	ShadowTree::ShadowSetMasterImageChanged(bool b,int LocalPhase,int LocalPage)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->ShadowSetMasterImageChangedInChildren(b,LocalPhase,LocalPage);
	}
}
void	ShadowTree::ShadowSetMasterImageChangedInChildren(bool b,int LocalPhase,int LocalPage)
{
	LayersBase			*Lb =GetTreeLayersBase();
	PageDataInOnePhase	*Ph=Lb->GetPageDataPhase(LocalPhase);
	if(Ph==NULL){
		return;
	}
	DataInPage			*Dp=Ph->GetPageData(LocalPage);
	if(Dp==NULL){
		return;
	}
	for(int LNumb=0;LNumb<Lb->GetLayerNumb(LocalPage);LNumb++){
		DataInLayer	*L=Dp->GetLayerData(LNumb);
		L->GetMasterBuff().EmitDataChanged();
		L->GetMasterBuff().SetChanged(b);
	}
}
void	ShadowTree::ShadowSetStartInspectionTimeMilisec(DWORD	s)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*Ly=c->GetInstance()->GetTreeLayersBase();
		Ly->SetStartInspectionTimeMilisec(s);
	}
}
	
void	ShadowTree::ShadeMakeImageNGCircle(QImage *tNGData ,QPainter *tPntFromNGData
									,int dtype		//DisplayImage::DisplayType
									,int Gx1,int Gy1 ,int Gx2,int Gy2
									,int MovX,int MovY, double ZoomRate
									,int localPage
									,bool RedCircleMode
									,bool ShowNGMarkInTarget
									,bool &RetNGData)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext(),N++){
		bool tRetNGData=false;
		c->GetInstance()->ShadeMakeImageNGCircleInChild(tNGData ,tPntFromNGData
									,dtype		//DisplayImage::DisplayType
									,Gx1,Gy1 ,Gx2,Gy2
									,MovX,MovY, ZoomRate
									,localPage
									,RedCircleMode
									,ShowNGMarkInTarget
									,tRetNGData
									,N);
		c->GetInstance()->ShadeMakeImageNGCircle(tNGData ,tPntFromNGData
									,dtype		//DisplayImage::DisplayType
									,Gx1,Gy1 ,Gx2,Gy2
									,MovX,MovY, ZoomRate
									,localPage
									,RedCircleMode
									,ShowNGMarkInTarget
									,tRetNGData);
		if(tRetNGData==true){
			RetNGData=true;
		}
	}
}
	
void	ShadowTree::WriteResultShadowForceWriteCommon(ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->WriteResultShadowForceWriteCommonInChildren(ShadowResStocks);
	}
}

void	ShadowTree::WriteResultShadowForceWriteCommonInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	ResultInspectionForStock	*W=GetTreeLayersBase()->GetResultThread()->GetResultCache()->GetOldestAndClear();
	if(W!=NULL && GetTopLayersBase()->GetResultDLLBase()->UnSavedResult()==false && W->GetShouldWriteResult()==true){
		if(GetTreeLayersBase()->IsLocalCamera()==true){
			if(GetTreeLayersBase()->GetParamGlobal()->ModeCompressNGImage==true){
				while(W->IsDoneCompressed()==false && GetTreeLayersBase()->GetParamGlobal()->ModeCompressNGImage==true){
					if(GetTopLayersBase()->GetOnTerminating()==true){
						return;
					}
					GSleep(10);
				}
			}
		}
		ShadowResStocks.AppendList(new ResultInspectionForStockPointer(this,W));
	}
}

void	ShadowTree::WriteResultShadowStockedWriteCommon(ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->WriteResultShadowStockedWriteCommonInChildren(ShadowResStocks);
	}
}
void	ShadowTree::WriteResultShadowStockedWriteCommonInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks)
{
	ResultInspectionForStock	*W=GetTreeLayersBase()->GetResultThread()->GetResultCache()->SearchOnWrite();	//Find oldest Result(Enable==true && OnWrite==true)	, and set false 
	if(W!=NULL && GetTopLayersBase()->GetResultDLLBase()->UnSavedResult()==false && W->GetShouldWriteResult()==true){
		if(GetTreeLayersBase()->IsLocalCamera()==true){
			if(GetTreeLayersBase()->GetParamGlobal()->ModeCompressNGImage==true){
				while(W->IsDoneCompressed()==false && GetTreeLayersBase()->GetParamGlobal()->ModeCompressNGImage==true){
					if(GetTopLayersBase()->GetOnTerminating()==true){
						return;
					}
					GSleep(10);
				}
			}
		}
		ShadowResStocks.AppendList(new ResultInspectionForStockPointer(this,W));
	}
}
	
void	ShadowTree::WriteResultShadowPickupForWriteInSlave(ResultInspectionForStockPointerContainer &ShadowResStocks
															,const XDateTime &InspectedTime)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->WriteResultShadowPickupForWriteInSlaveInChildren(ShadowResStocks,InspectedTime);
	}
}

void	ShadowTree::WriteResultShadowPickupForWriteInSlaveInChildren(ResultInspectionForStockPointerContainer &ShadowResStocks
																	,const XDateTime &InspectedTime)
{
	ResultInspectionForStock	*W=GetTreeLayersBase()->GetResultThread()->GetResultCache()->PickupForWriteInSlave(InspectedTime);
	if(W!=NULL){
		ShadowResStocks.AppendList(new ResultInspectionForStockPointer(this,W));
	}
}

void	ShadowTree::WriteResultShadowCastAll(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->WriteResultShadowCastAllInChildren();
	}
}

void	ShadowTree::WriteResultShadowCastAllInChildren(void)
{
	GetTreeLayersBase()->GetResultThread()->GetResultCache()->CastAll();
}

int		ShadowTree::GetWriteResultShadowStockedCount(void)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		N+=c->GetInstance()->GetWriteResultShadowStockedCountInChildren();
	}
	return N;
}
int		ShadowTree::GetWriteResultShadowStockedCountInChildren(void)
{
	int	N=GetTreeLayersBase()->GetResultThread()->GetStockedCount();
	return N+GetWriteResultShadowStockedCount();
}

void	ShadowTree::WriteResultSlaveWriteThreadLoop(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		c->GetInstance()->WriteResultSlaveWriteThreadLoopInChildren();
	}
}

void	ShadowTree::WriteResultSlaveWriteThreadLoopInChildren(void)
{
	GetTreeLayersBase()->GetResultThread()->GetSlaveWriteThreadInst()->WriteLoop();
}

//===================================================================
bool	ShadowTree::ShadowOutputResult(ResultInspection *ParentResultInspection
							,const QString &LotID,int LocalPhase,int LocalPage
							,QIODevice &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowOutputResultInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::ShadowOutputResult(ResultInspection *ParentResultInspection
							,const QString &LotID,int LocalPhase,int LocalPage
							,FileThread &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowOutputResultInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}
int		ShadowTree::ShadowGetNGImageCount(ResultInspection *ParentResultInspection
							,const QString &LotID,int LocalPhase,int LocalPage)
{
	int	N=0;
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL){
			N+=c->GetInstance()->ShadowGetNGImageCountInChildren(r
								,LotID,LocalPhase,LocalPage);
		}
	}
	return N;
}
bool	ShadowTree::ShadowWriteNGImage(ResultInspection *ParentResultInspection
							,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowWriteNGImageInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::ShadowSaveNGImage(ResultInspection *ParentResultInspection
									,const QString &LotID,int LocalPhase,int LocalPage
									,QFile &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowSaveNGImageInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}

bool	ShadowTree::ShadowWriteNGImage(ResultInspection *ParentResultInspection
							,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowWriteNGImageInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::ShadowSaveNGImage(ResultInspection *ParentResultInspection
									,const QString &LotID,int LocalPhase,int LocalPage
									,FileThread &File)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		ResultInspection	*r=ParentResultInspection->GetShadowResult(c->GetInstance()->GetShadowNumber());
		if(r!=NULL && c->GetInstance()->ShadowSaveNGImageInChildren(r
							,LotID,LocalPhase,LocalPage
							,File)==false){
			return false;
		}
	}
	return true;
}
bool	ShadowTree::ShadowOutputResultInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File)
{
	if(::Save(&File,GetShadowLevel())==false){
		return false;
	}
	if(::Save(&File,GetShadowNumber())==false){
		return false;
	}
	int	WrittenNGCount;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(LocalPhase);
		ResultInPageRoot	*R=RPh->GetPageData(LocalPage);
		if(R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(LocalPage) 
							,B->GetLogicDLL(), &File,WrittenNGCount)==false){
			return false;
		}
	}
	return true;
}

bool	ShadowTree::ShadowOutputResultInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File)
{
	if(File.Save(GetShadowLevel())==false){
		return false;
	}
	if(File.Save(GetShadowNumber())==false){
		return false;
	}
	int	eWrittenNGCount=0;
	for(ResultBaseForAlgorithmRoot *B=Res->GetResultBaseDimFirst();B!=NULL;B=B->GetNext()){
		ResultBasePhase		*RPh=B->GetPageDataPhase(LocalPhase);
		ResultInPageRoot	*R=RPh->GetPageData(LocalPage);
		int	tmpeWrittenNGCount=0;
		if(R->OutputResult(Res->GetLayersBase()->GetGlobalPageFromLocal(LocalPage) 
							,B->GetLogicDLL(), &File,tmpeWrittenNGCount)==false){
			return false;
		}
		eWrittenNGCount+=tmpeWrittenNGCount;
	}
	return true;
}
int		ShadowTree::ShadowGetNGImageCountInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage)
{
	int32	N=0;
	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(LocalPhase);
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(LocalPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(LocalPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				N++;
			}
		}
	}
	return N;
}
bool	ShadowTree::ShadowWriteNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,QIODevice &File)
{
	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(LocalPhase);
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(LocalPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(LocalPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);

				struct	NGIInfo	NGIData;
				NGIData.X	=mx1;
				NGIData.Y	=my1;
				NGIData.W	=m->GetWidth();
				NGIData.H	=m->GetHeight();
				NGIData.MX	=m->GetMx();
				NGIData.MY	=m->GetMy();
				NGIData.IDX	=Res->GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
				NGIData.Index=m->GetNumber();
				if(File.write((const char *)&NGIData,sizeof(NGIData))!=sizeof(NGIData)){
					return false;
				}
			}
		}
	}
	return true;
}
	
bool	ShadowTree::ShadowSaveNGImageInChildren(ResultInspection *Res
												,const QString &LotID,int LocalPhase,int LocalPage
												,QFile &File)
{
	if(::Save(&File,GetShadowLevel())==false){
		return false;
	}
	if(::Save(&File,GetShadowNumber())==false){
		return false;
	}

	if(Res->SaveNGImage(&File,LocalPage)==false){
		return false;
	}
	return true;
}

bool	ShadowTree::ShadowWriteNGImageInChildren(ResultInspection *Res
								,const QString &LotID,int LocalPhase,int LocalPage
								,FileThread &File)
{
	NGImageContainerInPhase	*NGPhase=Res->GetNGImageInPhase(LocalPhase);
	if(NGPhase!=NULL){
		if(NGPhase->GetNGImageInPage(LocalPage)!=NULL){
			for(NGImage *m=NGPhase->GetNGImageInPage(LocalPage)->GetNGImageDataFirst();m!=NULL;m=m->GetNext()){
				int mx1,my1,mx2,my2;
				m->GetXY(mx1,my1,mx2,my2);

				struct	NGIInfo	NGIData;
				NGIData.X	=mx1;
				NGIData.Y	=my1;
				NGIData.W	=m->GetWidth();
				NGIData.H	=m->GetHeight();
				NGIData.MX	=m->GetMx();
				NGIData.MY	=m->GetMy();
				NGIData.IDX	=Res->GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
				NGIData.Index=m->GetNumber();
				if(File.write((const char *)&NGIData,sizeof(NGIData))!=sizeof(NGIData)){
					return false;
				}
			}
		}
	}
	return true;
}
	
bool	ShadowTree::ShadowSaveNGImageInChildren(ResultInspection *Res
												,const QString &LotID,int LocalPhase,int LocalPage
												,FileThread &File)
{
	if(File.Save(GetShadowLevel())==false){
		return false;
	}
	if(File.Save(GetShadowNumber())==false){
		return false;
	}

	if(Res->SaveNGImage(&File,LocalPage)==false){
		return false;
	}
	return true;
}

void	ShadowTree::ShadowSetResultReceivedFlag(int Page)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*CBase=c->GetInstance()->GetTreeLayersBase();
		ResultInspection	*CurrentResult=CBase->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			CurrentResult->SetResultReceivedFlag(Page
												,CurrentResult->GetNGCount()
												,CurrentResult->GetTimeOutBreak()
												,CurrentResult->GetMaxErrorBreak());
		}
	}
}

void	ShadowTree::ShadowBroadcastRefreshCache(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastRefreshCache();
		}
	}
}
void	ShadowTree::ShadowBroadcastRepaintAll(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastRepaintAll();
		}
	}
}
void	ShadowTree::ShadowBroadcastShowInPlayer(int64 shownInspectionID)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastShowInPlayer(shownInspectionID);
		}
	}
}
void	ShadowTree::ShadowBroadcastOnTheWayInPlayer(int64 shownInspectionID)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastOnTheWayInPlayer(shownInspectionID);
		}
	}
}
void	ShadowTree::ShadowBroadcastRunByEveryInspection(int64 shownInspectionID)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastRunByEveryInspection(shownInspectionID);
		}
	}
}
void	ShadowTree::ShadowBroadcastShowInEdit(void)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		GUIFormBase	*Form=c->GetInstance()->GetTreeLayersBase()->GetMainWidget();
		if(Form!=NULL){
			Form->BroadcastShowInEdit();
		}
	}
}

void	ShadowTree::CopyParamGlobalFromParent(void)
{
	LayersBase	*ParentLayer=GetParentLayersBase();
	if(ParentLayer!=NULL){
		ChildCopyParamGlobalFromParent(ParentLayer->GetParamGlobal());
	}
}
void	ShadowTree::CopyShadowTreeParamResultDLL(ResultDLL *SrcParent)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*L=c->GetInstance()->GetTreeLayersBase();
		L->ChildCopyShadowTreeParamResultDLL(SrcParent);

		if(L->GetResultDLLBase()!=NULL){
			for(ResultDLL *R=L->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
				if(R->GetDLLRoot()==SrcParent->GetDLLRoot() && R->GetDLLName()==SrcParent->GetDLLName()){
					L->CopyShadowTreeParamResultDLL(R);
				}
			}
		}
	}
}
void	ShadowTree::ChildCopyShadowTreeParamResultDLL(ResultDLL *SrcParent)
{
	ResultDLLBaseRoot	*PRoot=SrcParent->GetDLLPoint();
	LayersBase	*L=GetTreeLayersBase();
	if(L->GetResultDLLBase()!=NULL){
		for(ResultDLL *R=L->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
			if(R->GetDLLRoot()==SrcParent->GetDLLRoot() && R->GetDLLName()==SrcParent->GetDLLName()){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				PRoot->SaveParam(&Buff);
				ResultDLLBaseRoot	*DestRoot=R->GetDLLPoint();
				Buff.seek(0);
				DestRoot->LoadParam(&Buff);
				break;
			}
		}
	}
}
void	ShadowTree::CopyShadowTreeParamLogicDLL(LogicDLL *SrcParent)
{
	for(ShadowControlInterface *c=Children->GetFirst();c!=NULL;c=c->GetNext()){
		LayersBase	*Ly=c->GetInstance()->GetTreeLayersBase();
		AlgorithmBase	*ABase=Ly->GetAlgorithmBase(SrcParent->GetDLLRoot(),SrcParent->GetDLLName());
		if(ABase!=NULL){
			ABase->ChildCopyShadowTreeParamLogicDLL(SrcParent->GetInstance());

			if(Ly->GetLogicDLLBase()!=NULL){
				for(LogicDLL *L=Ly->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					if(L->GetDLLRoot()==SrcParent->GetDLLRoot() && L->GetDLLName()==SrcParent->GetDLLName()){
						Ly->CopyShadowTreeParamLogicDLL(SrcParent);
					}
				}
			}
		}
	}
}