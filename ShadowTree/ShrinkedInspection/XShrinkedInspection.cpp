#include "ShrinkedInspection.h"
#include "XGUI.h"
#include "XPassword.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationBase.h"
#include "XLogOut.h"
#include "XStatusController.h"
#include "Regulus64System.h"
#include "XTransform.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return /**/"InspectionGeneral.lng";
}

ShrinkedInspection::ShrinkedInspection(int ShadowNumber ,LayersBase *ParentBase)
	:LayersBase(ParentBase,ShadowNumber)
{
	SkipDot=4;
	AddSystemMenu=true;
	MainForm=NULL;
	HorizontalTile	=true;
	VerticalTile	=false;
	SetTreeLayersBase(this);
}

bool	ShrinkedInspection::InitialInShadow(void)
{
	if(LayersBase::InitialInShadow()==false){
		return false;
	}
	LayersBase	*LBase=GetTreeLayersBase();
	if(GetShadowLevel()>0){
		if(LBase->GetParamGlobal()->ShadowParameterData==GetParentLayersBase()->GetParamGlobal()->ShadowParameterData){
			LBase->GetParamGlobal()->ShadowParameterData.RemoveAll();
		}
	}

	GUIInitializer	*G=new GUIInitializer(LBase);
	LBase->SetGUIInitializer(G);
	DWORD	ErrorCode=0;
	QString	ErrorMsg;
	if(G->Initial(LBase,ErrorCode ,ErrorMsg,false)==false || ErrorCode!=0){
		return false;
	}
	LBase->SetCurrentPath(GetParentLayersBase()->GetUserPath());

	RootNameListContainer	AlgorithmRootNameList;
	QFile	gfile(GetShadowGUIFileName());
	if(gfile.open(QIODevice::ReadOnly)==true){
		if(G->GetGUIInstanceRoot()->LoadOnlyAlgorithm(&gfile)==true){
			AlgorithmRootNameList=G->GetGUIInstanceRoot()->AlgorithmList;
		}
		gfile.close();
	}
	{
		CopyParamGlobalFromParent();
		//LBase->GetParamGlobal()->DotPerLine	=LBase->GetDotPerLine(0)/SkipDot;
		//LBase->GetParamGlobal()->MaxLines	=LBase->GetMaxLines(0)  /SkipDot;
		QString Msg;
		if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
			return false;
		}
	}
	SetSkipDot(SkipDot);

	int	BootingLevel=GetParentLayersBase()->GetBootingLevel();
	LBase->SetBootingLevel(BootingLevel);
	LBase->SetMasterType(BootingLevel);
	LBase->LoadAttrDefault();

	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	LBase->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
	LBase->ReadLogicSettingFiles(true);

	ParamIntegrationMaster	ParamIntegrationMasterData(LBase);
	ParamIntegrationMasterData.LoadDefault(LBase->GetUserPath());
	IntegrationBase	*IBase=new IntegrationBase(LBase,&ParamIntegrationMasterData);
	IBase->Initialize();
	LBase->SetIntegrationBase(IBase);

	LBase->InitialAlgorithmBlob();
	LBase->InitialAlgorithmLibrary();
	{
		if(LBase->IsValidDatabase()==true){
			QString	ErrorMsg;
			if(G->InitialAdditionalFieldFromGUI(LBase->GetDatabase(),ErrorMsg)==false){
				QString  msg=QString(/**/"Database Error");
				return false;
			}
		}
	}
	if(BootingLevel==0 && LBase->GetEntryPoint()->IsMasterPC()==true){
		LBase->LoadOutlineOffsetForDatabase();
	}

	MainForm=NULL;
	{
		QFile	file(GetShadowGUIFileName());
		if(file.open(QIODevice::ReadOnly)==true){
			LBase->SetGUIFileName(GetShadowGUIFileName());
			G->GetGUIInstanceRoot()->CloseAll();
			QString ErrorMsg;
			if(G->GetGUIInstanceRoot()->LoadInstances(&file,ErrorMsg)==false){
				return false;
			}
			file.close();
			G->RemoveUselessGUI();

			RootNameListContainer LackOfAlgorithm;
			if(LBase->CheckInstalledAlgorithm(AlgorithmRootNameList,LackOfAlgorithm)==false){
				return false;
			}
			LBase->SetLanguageCode(false,true,true);
			LBase->InitialAllocExecuterDim();
			LBase->InitialResult();
			MainForm=G->GetGUIInstanceRoot()->CreateMainForm(LBase,GUIInstancePack::_Center,AddSystemMenu);
		}
		else{
			if(GetTopLayersBase()->GetEntryPoint()->GUIIsEditMode()==false){
				return false;
			}
		}
	}
	for(GUIInstancePack *L=G->GUIInstanceRoot.GetFirst();L!=NULL;L=L->GetNext()){
		for(GUIItemInstance *s=L->NPListPack<GUIItemInstance>::GetFirst();s!=NULL;s=s->GetNext()){
			IntegratorRelation	*d=dynamic_cast<IntegratorRelation *>(s->GetForm());
			if(d!=NULL){
				d->SetParamPointer(&ParamIntegrationMasterData);
			}
		}
	}
	if(MainForm!=NULL){
		LBase->SetGUIInstancePack(G->GetGUIInstanceRoot());
		LBase->SetMainForm(G->GetGUIInstanceRoot()->GetFirstForm());
		G->GetGUIInstanceRoot()->ShowAll(MainForm	,LBase
										,LBase->GetParamGUI());
		MainForm->hide();
	}
	//Layers->InitialArrangementDLL();
	AlgorithmRootNameList.RemoveAll();

	if(G->GetGUIInstanceRoot()->GetFirstForm()!=NULL){
		G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"InspectionEditor");
	}
	QCoreApplication::processEvents();
	
	LBase->GetParamGUI()->LoadDefault(LBase->GetUserPath());
	//G->GetGUIInstanceRoot()->GetFirstForm()->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);


	LBase->SetWorkerID	(GetParentLayersBase()->GetWorkerID());
	LBase->SetWorkerName	(GetParentLayersBase()->GetWorkerName());
	LBase->SQLSetWorker	(GetParentLayersBase()->GetWorkerID());

	LBase->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());

	LBase->InitialFilterBank();
	LBase->InitialResultAnalizer();

	LBase->ReadAllSettingFiles(true,-1);
	LBase->InitialAfterParamLoaded();

	ExecuteInitialAfterEditInfo EInfo;
	LBase->ExecuteInitialAfterEdit(EInfo);
	//ExecuteInitialAfterEdit();

	GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
	if(B!=NULL){
		B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);
		LBase->ExecuteLogoInGUIForm(B ,/**/"",/**/"");
	}

	LBase->GetPasswordHolder()->SetDefaultFile(GUIFileName);
	LBase->GetPasswordHolder()->LoadDefaultFile();

	if(MainForm!=NULL){
		MainForm->ReflectAlignment();
	}
	if(G!=NULL && G->GetGUIInstanceRoot()!=NULL && MainForm!=NULL){
		G->GetGUIInstanceRoot()->ReadyParam(MainForm);
	}

	LBase->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	LBase->DeliverOutlineOffset();
	if(LBase->GetEntryPoint()->IsMasterPC()==true){
		LBase->DeliverAllCommsForDirectComm(50000);
	}
	else{
		LBase->OpenCommsForDirectComm();
	}
	LBase->LoadFilterDef();
	if(LBase->GetStatusController()!=NULL){
		LBase->GetStatusController()->InstallFilter();
	}

	G->GetGUIInstanceRoot()->AfterPrepare();

	std::shared_ptr<OperationLogger>	pLogger=LBase->GetOperationLoggerData();
	if(pLogger){
		pLogger->PutLogStart(pLogger->GetProgramName());
	}
	LBase->CloseInformed();
	G->InitialIntegration();
	//LBase->LoadShadowChildrenDLL();
	if(MainForm!=NULL){
		MainForm->hide();
	}
	return true;
}
void	ShrinkedInspection::ChildCopyParamGlobalFromParent(ParamGlobal *ParentParam)
{
	GetParamGlobal()->DotPerLine=ParentParam->GetDotPerLine(0)/SkipDot;
	GetParamGlobal()->MaxLines	=ParentParam->GetMaxLines(0)  /SkipDot;
}

bool	ShrinkedInspection::SaveShadowParam(QIODevice *f)
{
	if(ShadowTree::SaveShadowParam(f)==false){
		return false;
	}
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,SkipDot)==false){
		return false;
	}
	if(::Save(f,HorizontalTile)==false){
		return false;
	}
	if(::Save(f,VerticalTile)==false){
		return false;
	}
	return true;
}

bool	ShrinkedInspection::LoadShadowParam(QIODevice *f)
{
	if(ShadowTree::LoadShadowParam(f)==false){
		return false;
	}
	int32	Ver=1;

	if(::Load(f,Ver)==false){
		return false;
	}
	int32	iSkipDot;
	if(::Load(f,iSkipDot)==false){
		return false;
	}
	if(::Load(f,HorizontalTile)==false){
		return false;
	}
	if(::Load(f,VerticalTile)==false){
		return false;
	}
	SetSkipDot(iSkipDot);
	return true;
}

void	ShrinkedInspection::SetSkipDot(int skipdot)
{
	SkipDot=skipdot;
	LayersBase	*PL=GetParentLayersBase();
	ReallocXYPixelsShadowInChild(PL->GetDotPerLine(0) ,PL->GetMaxLines(0));

	if(HorizontalTile==true){
		int	*X=new int [GetTreeLayersBase()->GetPhaseNumb()];
		for(int phase=0;phase<GetTreeLayersBase()->GetPhaseNumb();phase++){
			X[phase]=0;
		}
		for(int page=0;page<GetTreeLayersBase()->GetPageNumb();page++){
			for(int phase=0;phase<GetTreeLayersBase()->GetPhaseNumb();phase++){
				PageDataInOnePhase	*Ph=GetTreeLayersBase()->GetPageDataPhase(phase);
				if(Ph!=NULL){
					DataInPage *Dp=Ph->GetPageData(page);
					if(Dp!=NULL){
						Dp->GetOutlineOffset()->x=X[phase];
						X[phase]+=Dp->GetDotPerLine();
					}
				}
			}
		}
		delete	[]X;
	}
	else if(VerticalTile==true){
		int	*Y=new int [GetTreeLayersBase()->GetPhaseNumb()];
		for(int phase=0;phase<GetTreeLayersBase()->GetPhaseNumb();phase++){
			Y[phase]=0;
		}
		for(int page=0;page<GetTreeLayersBase()->GetPageNumb();page++){
			for(int phase=0;phase<GetTreeLayersBase()->GetPhaseNumb();phase++){
				PageDataInOnePhase	*Ph=GetTreeLayersBase()->GetPageDataPhase(phase);
				if(Ph!=NULL){
					DataInPage *Dp=Ph->GetPageData(page);
					if(Dp!=NULL){
						Dp->GetOutlineOffset()->y=Y[phase];
						Y[phase]+=Dp->GetMaxLines();
					}
				}
			}
		}
		delete	[]Y;
	}
}
void	ShrinkedInspection::ShowShadow(void)
{
	if(MainForm!=NULL){
		MainForm->show();
	}
}

void	ShrinkedInspection::ConvertToTop(int32 &x ,int32 &y)
{
	x=x*SkipDot;
	y=y*SkipDot;
}
void	ShrinkedInspection::ConvertToLocal(int32 &TopX ,int32 &TopY)
{
	TopX=TopX/SkipDot;
	TopY=TopY/SkipDot;
}

ExeResult	ShrinkedInspection::ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep)
{
	int	DotPerLine	=GetParentLayersBase()->GetDotPerLine(0)/SkipDot;
	int	MaxLines	=GetParentLayersBase()->GetMaxLines(0)  /SkipDot;

	if(GetTreeLayersBase()->GetDotPerLine(0)!=DotPerLine
	|| GetTreeLayersBase()->GetMaxLines(0)!=MaxLines){
		GetTreeLayersBase()->ReallocXYPixels(DotPerLine ,MaxLines);
	}
	ExeResult	Ret=LayersBase::ExecuteInitialAfterEdit(EInfo,ProgressStep);
	return Ret;
}

ExeResult	ShrinkedInspection::ExecuteCaptured(ListPhasePageLayerPack &CapturedList ,bool ProgressStep)
{
	ExeResult	Ret=LayersBase::ExecuteCaptured(CapturedList ,ProgressStep);

	GetTreeLayersBase()->LockWChangingDataStructure();
	LayersBase	*ParentLBase=GetParentLayersBase();
	bool	AllocCamTargetBuffer=ParentLBase->GetParamGlobal()->AllocCamTargetBuffer;
	IntList	PhaseList;
	CapturedList.GetPhaseList(PhaseList);
	for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
		int	Phase=c->GetValue();
		PageDataInOnePhase	*sPh=ParentLBase		->GetPageDataPhase(Phase);
		PageDataInOnePhase	*dPh=GetTreeLayersBase()->GetPageDataPhase(Phase);
		if(sPh!=NULL && dPh!=NULL){
			ListPageLayerPack PageLayer;
			CapturedList.GetPageLayer(Phase,PageLayer);
			IntList	PageList;
			PageLayer.GetPageList(PageList);
			for(IntClass *e=PageList.GetFirst();e!=NULL;e=e->GetNext()){
				int	Page=e->GetValue();
				DataInPage	*sPd=sPh->GetPageData(Page);
				DataInPage	*dPd=dPh->GetPageData(Page);
				if(sPd!=NULL && dPd!=NULL){
					IntList	LayerList;
					PageLayer.GetLayer(Page,LayerList);
					for(IntClass *f=LayerList.GetFirst();f!=NULL;f=f->GetNext()){
						int	Layer=f->GetValue();
						DataInLayer	*sLy=sPd->GetLayerData(Layer);
						DataInLayer	*dLy=dPd->GetLayerData(Layer);
						if(sPd!=NULL && dPd!=NULL){
							if(AllocCamTargetBuffer==false){
								CopyFilterdCopy( dLy->GetTargetBuff()
												,sLy->GetTargetBuff()
												,SkipDot);
							}
							else{
								CopyFilterdCopy( dLy->GetTargetBuff()
												,sLy->GetCamTargetBuff()
												,SkipDot);
								GetTreeLayersBase()->ExecuteFilteringTarget();
							}
						}
					}
				}
			}
		}
	}
	GetTreeLayersBase()->UnlockChangingDataStructure();
	return Ret;
}


void	ShrinkedInspection::ShadeMakeImageNGCircleInChild(QImage *tNGData ,QPainter *tPntFromNGData
									,int dtype		//DisplayImage::DisplayType
									,int Gx1,int Gy1 ,int Gx2,int Gy2
									,int MovX,int MovY, double ZoomRate
									,int localPage
									,bool RedCircleMode
									,bool ShowNGMarkInTarget
									,bool &RetNGData
									,int ShadowNumber)
{
	//LayersBase	*L=GetTopLayersBase();
	if(localPage<GetTreeLayersBase()->GetPageNumb()){
		GetTreeLayersBase()->MakeImageNGCircle(tNGData ,tPntFromNGData
							,dtype //DisplayImage::DisplayType
							,Gx1,Gy1 ,Gx2,Gy2
							,MovX/SkipDot,MovY/SkipDot, ZoomRate*SkipDot
							,localPage
							,RedCircleMode
							,ShowNGMarkInTarget
							,RetNGData);
	}
}
bool	ShrinkedInspection::ReallocXYPixelsShadowInChild(int NewDotPerLine ,int NewMaxLines)
{
	int	DotPerLine	=GetParentLayersBase()->GetDotPerLine(0)/SkipDot;
	int	MaxLines	=GetParentLayersBase()->GetMaxLines(0)  /SkipDot;
	return GetTreeLayersBase()->ReallocXYPixels(DotPerLine ,MaxLines);
}

void	ShrinkedInspection::CopyShadowImageFromParentInChild(bool Mastered ,int MasterNo
															,DataInPage *SrcPg
															,int Phase ,int Page)
{
	PageDataInOnePhase	*dPh=GetTreeLayersBase()->GetPageDataPhase(Phase);
	if(dPh!=NULL){
		DataInPage	*dPd=dPh->GetPageData(Page);
		if(dPd!=NULL && SrcPg!=NULL){
			for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
				DataInLayer	*sLy=SrcPg->GetLayerData(Layer);
				DataInLayer	*dLy=dPd->GetLayerData(Layer);
				if(sLy!=NULL && dLy!=NULL){
					if(Mastered==true){
						CopyFilterdCopy( dLy->GetMasterBuff(MasterNo)
										,sLy->GetMasterBuff(MasterNo)
										,SkipDot);
					}
					else{
						CopyFilterdCopy( dLy->GetTargetBuff()
										,sLy->GetTargetBuff()
										,SkipDot);
					}
				}
			}
		}
	}
}

TransformBase	&ShrinkedInspection::MakeTransformFromMain(void)
{
	double	m=1.0/SkipDot;
	TransformAffin	A(m,0,0,0,m,0);
	TransformData=A;
	return TransformData;
}

bool	ShrinkedInspection::CopyShadowAlgorithmPage(const AlgorithmInPageRoot &ParentAPage	, AlgorithmInPageRoot *ChildPage)
{
	double	m[6];
	m[0]=1.0/(double)SkipDot;
	m[1]=0;
	m[2]=0;
	m[3]=0;
	m[4]=1.0/(double)SkipDot;
	m[5]=0;
	TransformAffin	Param(m);
	ChildPage->TransformCopyFrom(Param,ParentAPage);
	return ShadowTree::CopyShadowAlgorithmPage(ParentAPage, ChildPage);
}
bool	ShrinkedInspection::CopyShadowAlgorithmLayer(const AlgorithmInLayerRoot &ParentALayer	, AlgorithmInLayerRoot *ChildLayer)
{
	double	m[6];
	m[0]=1.0/(double)SkipDot;
	m[1]=0;
	m[2]=0;
	m[3]=0;
	m[4]=1.0/(double)SkipDot;
	m[5]=0;
	TransformAffin	Param(m);
	ChildLayer->TransformCopyFrom(Param,ParentALayer);
	return ShadowTree::CopyShadowAlgorithmLayer(ParentALayer, ChildLayer);
}
bool	ShrinkedInspection::CopyShadowAlgorithmItem(AlgorithmParentFromItem *ParentG	, const AlgorithmItemRoot &ParentItem)
{
	AlgorithmItemRoot	*item=ParentG->CreateItem(((AlgorithmItemRoot *)&ParentItem)->GetItemClassType());
	double	m[6];
	m[0]=1.0/(double)SkipDot;
	m[1]=0;
	m[2]=0;
	m[3]=0;
	m[4]=1.0/(double)SkipDot;
	m[5]=0;
	TransformAffin	Param(m);
	item->TransformCopyFrom(Param,ParentItem);
	ParentG->AppendItem(item);
	return true;
}
