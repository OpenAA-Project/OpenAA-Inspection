/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceArrange.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "PieceArrangeResource.h"
#include "XPieceArrange.h"
#include "XPieceArchitect.h"
#include "XGeneralFunc.h"
#include "XPacketAlignment.h"
#include "XPiecePacket.h"
#include "SelectExpandableAlgorithmForm.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmDLL.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XFileRegistry.h"
#include "XAlignmentCommon.h"
#include "XImageExpand.h"
#include "XResize.h"
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XSyncGUI.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"
#include <QMessageBox>
#include <omp.h>


LayersBase::LayersBase(EntryPointBase *pEntryPoint,bool _StartThreadWriteMode)
:AuthenticationInComponent(this)
,ShadowTree(-1,this)
,OnTerminating(false)
,EntryPoint(pEntryPoint)
,TopView(256,256,QImage::Format_RGB32)
,UndoDataStocker(this),RedoDataStocker(this)
,Parent(NULL)
,ChangingDataStructure(QReadWriteLock::Recursive)
, SystemResultContainer(this)
{
	ReadyOK					=false;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
	InstShowLoadingDLLForm	=NULL;
	CurrentShadowNumber		=-1;
	ShadowNumber			=-1;
	ReturnCode				=0;
    FastBoot				=false;
    StartThreadWriteMode	=_StartThreadWriteMode;
	
	#pragma omp parallel                             
	{             
		NumThreads=omp_get_num_threads();
	}
	LibType					=new LibTypeListContainer();
	InstalledLibType		=new LibTypeListContainer();
	ResultHistryData		=new ResultHistryContainer(this);
	ArrangementDLLStock		=new ArrangementDLLBase(this);
	LogCreater				=new LogOutClass("C:/LogFile.txt");
	ResultInspectionPointerStocker	=new ResultInspectionPointerStock();
	
	OnChanging				=false;
	MilisecExecuteFilter	=0;
	InsideLearningEditor	=false;
	QString	CurPath			=QDir::currentPath();
	FRegistry				=new FileRegistry(CurPath+/**/"/MachineInfo.dat");
	int	LanguageCode=GetFRegistry()->LoadRegInt(/**/"Language",0);

	LanguagePackageData		=new LanguagePackage();
	LoadLanguageSolution(GetLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	UseDynamicMasking		=false;

	ParamGlobalData			=new ParamGlobal(this);
	ParamCommData			=new ParamComm	(this);
	ParamGUIData			=new ParamGUI	();
	AllocatedBufferInfoCount=0;
	BufferInfoListDim		=NULL;
	//RCmdBase				=new NPListPack<ReceiverList>;
	RCmdBase				= NULL;
	GlobalOffset			=NULL;
	SendingData				=NULL;
	GlobalPageNumb			=0;

	//RIntegrationCmdBase		=new NPListPack<ReceiverList>;
	RIntegrationCmdBase		= NULL;
	IntegrationSendingData	=NULL;

	DefaultArrangeMode		=false;
	RootDBase				=NULL;
	OriginalRootDBase		=true;
	CurrentStrategicNumber	=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicNumberInExe		=0;
	StopCommSender			=false;
	MasterCode				= -1;
	PageData				=NULL;
	PageDataPhase			=NULL;
	DrawPageIndex			=NULL;
	CurrentPhase			=0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb		=0;
	//MachineID				=0;
	RegTime					=XDateTime::currentDateTime();
	WorkerID				= -1;
	Version					=RegulusVersion;
	LoadedVersion			=RegulusVersion;
	LastEditTime			=RegTime;
	StartInspectionTime		=RegTime;
	CategoryID				= -1;
	_CurrentInspectID		=0;
	_LastInspectID			=0;
	InspectionRemark		=0;
	LotInfo					=NULL;	/////////////////////////////////
	ExecuterDim				=NULL;
	AllocExecuterDim		=0;
	CurrentCalcPoint		=0;
	CurrentDrawPoint		=0;
	LastCurrentCalcPoint	=0;
	AlgoDLLContPointer		=new AlgorithmDLLContainer(this);
	LogicDLLBase			=new LogicDLLBaseClass(this);
	ResultDLLBase			=NULL;	/////////////////////////////////
	SequenceInstance		=NULL;
	InspectionTimeMilisec	=0;
	DBLoader				=NULL;
	MasterType				=0;		//0:MasterData 1:PieceData
	PieceStock				=new PieceStocker(this);
	BootingLevel			=0;
	OnProcessing			=NULL;
	ErrorOccurs				=0;
	AckFlag					=NULL;
	AllocatedAckFlag		=0;
	DirectCommBase			=NULL;
	ProcessingReEntrant		=0;
	LightBase				=NULL;
	ForceChangedInspectID	=false;
	LanguageCode			=0;
	MTransfer				=NULL;
	MainWidget				=NULL;
	CurrentLevel			=NULL;
	EnableFilter			=true;
	EnableProcess			=true;
 
	LocalParamStocker		=new ParamDatabase(/**/"LocalData.dat");
	AppPointer	=(QApplication *)QCoreApplication::instance();
	ShouldWriteResult		=true;
	FilterBank				=NULL;	//new FilterBankBase(this);
	OutlineOffsetWriter		=NULL;	//new OutlineOffsetInBlob(this);
	LogoStockerInstance		=NULL;	//new LogoStocker();
	AnyData					=NULL;	//new AnyDataContainer();
	GeneralStockerData		=NULL;	//new GeneralStockerContainer(this);
	ErrorContainer			=new ErrorCodeListContainer();
	LatchedInspectionNumber	=0;
	InsideReEntrant			=0;
	ResultWrittenID			=0;
	PasswordHolder			=NULL;	//new PasswordManager(this);
	SyncGUIData				=std::make_shared<SyncGUIPack>(this);
	StatusControllerData	=NULL;	//new StatusController(this);
	LearningRegisterData	=NULL;	//new LearningRegister(this);
	EventPriority			=0;

	RCmdDirectCommBase		=new NPListPack<DirectCommReceiverList>; 
	LearningRegData			=new LearningRegListContainer();
	TmpHidingProcessingForm	=false;
	ListOfQImageStockerData	=new ListOfQImageStocker();

	MachineID				=FRegistry->LoadRegInt(/**/"MachineID",0);
	MachineIDFromMaster		=MachineID;
	CurrentScanPhaseNumber	=0;
	ViewRefreshCounter		=0;
	ThresholdLevelParentID	=0;
	ThresholdLevelID		=0;
	CurrentLibFolderID		=-1;

	DataOfShareMasterContainer		=NULL;
	MainThread						=QThread::currentThreadId();
	PasteListMatrixContainerBase	=NULL;
	OperationLoggerData				=NULL;
	PrinterClassPackData			=NULL;
	ShrinkingPackContainerInstance	=NULL;
	ModeInspectionPlayer		=false;
	LensWindow					=NULL;
	ZoneWindow					=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm			=0;
	IntegrationBaseData			=NULL;
	ResizeData					=new WidgetGeometry();
	ResultAnalizerDLLPack		=NULL;
	ResultAnalizerItemBasePack	=NULL;	
	ResultThread				=new WriteResultThread(this,StartThreadWriteMode);
	AuthenticationInst			=NULL;
	FileThreadListContainerInst	=new FileThreadListContainer(this);
	EditPasswordMode			=false;
	LevelFolderContainerInst	=new LevelFolderContainer(this);
	
	EnableLoopOnIdle	=true;
	PossibleToUpdateDisplay		=true;
}

PieceThreshold::PieceThreshold(PieceArrangeItem *parent)
:AlgorithmThreshold(parent)
{
}


bool	ReflectionAttr::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,EnabledReflection)==false)
		return false;
	return true;
}
	
bool	ReflectionAttr::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,EnabledReflection)==false)
		return false;
	return true;
}



bool	ReflectionAttrPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ReflectionAttr *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
	
bool	ReflectionAttrPack::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		ReflectionAttr	*a=new ReflectionAttr();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

bool	ReflectionAttrPack::Check(QString DLLRoot,QString DLLName)
{
	for(ReflectionAttr *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DLLRoot==DLLRoot && a->DLLName==DLLName)
			return a->EnabledReflection;
	}
	return true;
}

//---------------------------------------------------------------------------------

bool    PieceArrangeItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(ReflectionData.Save(f)==false)
		return false;
	return true;
}
bool    PieceArrangeItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(LoadedVersion>=4){
		if(ReflectionData.Load(f)==false)
			return false;
	}
	return true;
}
void	PieceArrangeItem::ListupMasterID(IntList &List)
{
	for(IntClass *d=List.GetFirst();d!=NULL;d=d->GetNext()){
		if(MasterCode==d->GetValue())
			return;
	}
	List.Add(MasterCode);
}

void	PieceArrangeItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		FlexArea	area=GetArea();
		//area.MoveToClip(GlobalDx,GlobalDy, 0,0,GetDotPerLine(),GetMaxLines());
		area.MoveToNoClip(GlobalDx,GlobalDy);
		SetArea(area);
		SetEdited(true);
		SetCalcDone(false);
	}
}
void	PieceArrangeItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	PieceDrawAttr	*LAttr=dynamic_cast<PieceDrawAttr *>(Attr);
	if(LAttr!=NULL){
		int	mx=GetArea().GetMinX();
		int	my=GetArea().GetMinY();
		QString ErrorMessageOfFalse;
		PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(MasterCode,ErrorMessageOfFalse);
		if(Piece!=NULL){
			LayersBase	*PBase=Piece->GetLayersBase();
			if(PBase!=NULL){
				AlgorithmBase	*A=PBase->GetAlgorithmBase(LAttr->DLLRoot,LAttr->DLLName);
				if(A!=NULL){
					if(LAttr->SelectedLines.IsInclude(GetGlobalPage(),GetID())==true){
						A->Draw(pnt, LAttr->LayerList ,mx+movx ,my+movy ,ZoomRate ,Attr);
					}
					else{
						QColor	ActiveColor		=Attr->ActiveColor;
						QColor	NormalColor		=Attr->NormalColor;
						QColor	SelectedColor	=Attr->SelectedColor;
						QColor	UncoveredColor	=Attr->UncoveredColor;

						Attr->ActiveColor	.setAlpha( ((PieceArrangeBase *)GetParentBase())->TransparentLevelNonSelection);
						Attr->NormalColor	.setAlpha( ((PieceArrangeBase *)GetParentBase())->TransparentLevelNonSelection);
						Attr->SelectedColor	.setAlpha( ((PieceArrangeBase *)GetParentBase())->TransparentLevelNonSelection);
						Attr->UncoveredColor.setAlpha( ((PieceArrangeBase *)GetParentBase())->TransparentLevelNonSelection);

						A->Draw(pnt, LAttr->LayerList ,mx+movx ,my+movy ,ZoomRate ,Attr);

						Attr->ActiveColor	=ActiveColor	;
						Attr->NormalColor	=NormalColor	;
						Attr->SelectedColor	=SelectedColor	;
						Attr->UncoveredColor=UncoveredColor	;	
					}
					return;
				}
				else{
					int	Lx1,Ly1,Lx2,Ly2;
					PBase->GetArea(Lx1,Ly1,Lx2,Ly2);
					int	gLx1=(Lx1+movx+GetArea().GetMinX())*ZoomRate;
					int	gLy1=(Ly1+movy+GetArea().GetMinY())*ZoomRate;
					int	gLx2=(Lx2+movx+GetArea().GetMinX())*ZoomRate;
					int	gLy2=(Ly2+movy+GetArea().GetMinY())*ZoomRate;
					if(gLx2<0 || gLx1>pnt.width() || gLy2<0 || gLy1>pnt.height())
						return;
					int	W=gLx2-gLx1;
					int	H=gLy2-gLy1;
					QImage	WImage(W,H,QImage::Format_ARGB32);
					PBase->Draw(WImage,0,0,ZoomRate);
					if(LAttr->SelectedLines.IsInclude(GetGlobalPage(),GetID())==true){
						AddAlphaChannel(WImage, ((PieceArrangeBase *)GetParentBase())->TransparentLevel);
					}
					else{
						AddAlphaChannel(WImage, ((PieceArrangeBase *)GetParentBase())->TransparentLevelNonSelection);
					}
					QPainter	Pnt(&pnt);

					if(GetSelected()==true){
						QImage	FImage(W,H,QImage::Format_ARGB32);
						QColor	CCol(0,180,0,128);
						FImage.fill(CCol);
						Pnt.drawImage((movx+GetArea().GetMinX())*ZoomRate
									 ,(movy+GetArea().GetMinY())*ZoomRate
									 ,FImage);
					}
					else if(GetActive()==true){
						QImage	FImage(W,H,QImage::Format_ARGB32);
						QColor	CCol(180,0,0,128);
						FImage.fill(CCol);
						Pnt.drawImage((movx+GetArea().GetMinX())*ZoomRate
									 ,(movy+GetArea().GetMinY())*ZoomRate
									 ,FImage);
					}		
					Pnt.drawImage((movx+GetArea().GetMinX())*ZoomRate
								 ,(movy+GetArea().GetMinY())*ZoomRate
								 ,WImage);
					
					return;
				}
			}
		}
		else{
			if(ErrorMessageOfFalse.isEmpty()==false){
				QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
			}
		}
	}
	AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}

ExeResult	PieceArrangeItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	//AlgorithmItemPI::ExecuteInitialAfterEdit(ThreadNo,Res ,pInspectionData);
	QString ErrorMessageOfFalse;
	PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(MasterCode,ErrorMessageOfFalse);
	if(Piece!=NULL){
		LayersBase	*LBase=Piece->GetLayersBase();

		for(LogicDLL *L=LBase->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*PBase=L->GetInstance();
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(L->GetDLLRoot(),L->GetDLLName());

			AlgorithmInPageRoot		*d=ABase->GetPageData(GetPage());
			AlgorithmInPageRoot		*s=PBase->GetPageData(0);
			if(d==NULL || s==NULL)
				continue;
			if(ReflectionData.Check(L->GetDLLRoot(),L->GetDLLName())==false)
				continue;
			((PieceArrangeInPage *)GetParent())->MutexExecuteInitialAfterEditInLayer.lock();
			d->CopyFrom(ABase,s	
							,GetArea().GetMinX(),GetArea().GetMinY()
							,MasterCode							
							,GetID()
							,true);
			((PieceArrangeInPage *)GetParent())->MutexExecuteInitialAfterEditInLayer.unlock();
		}
	}
	else{
		if(ErrorMessageOfFalse.isEmpty()==false){
			QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
		}
	}
	return _ER_true;
}

void	PieceArrangeItem::CalcFittableInfo(double AffinParam[6] ,int SearchDot)
{
	QString ErrorMessageOfFalse;
	PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(MasterCode,ErrorMessageOfFalse);
	if(Piece!=NULL){
		LayersBase		*PBase=Piece->GetLayersBase();
		if(PBase==NULL)
			return;
		AlgorithmBasePointerContainer AlignmentBases;
		PBase->GetAlgorithmByType(AlignmentBases,AlgorithmBit_TypeAlignment);

		if(AlignmentBases[0]==NULL)
			return;
		AlgorithmBase	*PAlignBase=AlignmentBases[0]->GetAlgorithmBase();

		int	X1,Y1,X2,Y2;
		GetXY(X1,Y1,X2,Y2);

		int		OriginalWidth	=PBase->GetDotPerLine(0);
		int		OriginalHeight	=PBase->GetMaxLines(0);
		PBase->ReallocXYPixels(OriginalWidth+SearchDot*2, OriginalHeight+SearchDot*2);
		PBase->GetLogicDLLBase()->ExecuteMove(0,SearchDot,SearchDot,true);

		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			ImageBuffer	&MasterImage=PBase->GetPageData(0)->GetLayerData(Layer)->GetMasterBuff();
			MasterImage.MoveImage(SearchDot,SearchDot);
		}
		ImagePointerContainer CurentImageList;
		GetMasterBuffList(CurentImageList);
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			ImageBuffer	&TargetImage=PBase->GetPageData(0)->GetLayerData(Layer)->GetTargetBuff();
			TargetImage.Memset(0);
			TargetImage.PartialCopy(*CurentImageList[Layer],X1-SearchDot,Y1-SearchDot);
		}
		
		ListPhasePageLayerPack	CapturedList;
		PBase->MakeCapturedAllList(CapturedList);
		
		ResultBaseForAlgorithmRoot	*Res=PAlignBase->GetLogicDLL()->CreateResultBaseForAlgorithm(NULL);
		Res->Initial();

		{
			QBuffer	TmpBuff;
			TmpBuff.open(QIODevice::ReadWrite);
			PAlignBase->SaveOnlyThreshold(&TmpBuff);
			TmpBuff.seek(0);

			CmdAlignmentSetSearchDot	RCmd(GetLayersBase());
			RCmd.SearchDotX	=SearchDot;
			RCmd.SearchDotY	=SearchDot;
			PAlignBase->TransmitDirectly(&RCmd);

			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			PAlignBase->ExecuteInitialAfterEdit	(0,Res,EInfo);
			PAlignBase->ExecuteStartByInspection(0,Res);
			PAlignBase->ExecuteCaptured			(0,Res,CapturedList);
			PAlignBase->ExecutePreAlignment		(0,Res);
			PAlignBase->ExecuteAlignment		(0,Res);
			PAlignBase->LoadOnlyThreshold(&TmpBuff);

			AlignmentPacket2D	APackat;
			APackat.PosXOnTarget	=PBase->GetParamGlobal()->DotPerLine/2;
			APackat.PosYOnTarget	=PBase->GetParamGlobal()->MaxLines/2;
			PAlignBase->GetPageData(0)->GetAlignmentForProcessing(APackat);
			for(int k=1;k<10 && APackat.ShiftX<=-1000 && APackat.ShiftY<=-1000;k++){
				APackat.PosXOnTarget	=PBase->GetParamGlobal()->DotPerLine/10*k;
				APackat.PosYOnTarget	=PBase->GetParamGlobal()->MaxLines/10*k;
				PAlignBase->GetPageData(0)->GetAlignmentForProcessing(APackat);
			}
			delete	Res;
			AffinParam[0]=1.0;
			AffinParam[1]=0.0;
			AffinParam[2]=APackat.ShiftX;
			AffinParam[3]=0.0;
			AffinParam[4]=1.0;
			AffinParam[5]=APackat.ShiftY;
		}
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			ImageBuffer	&MasterImage=PBase->GetPageData(0)->GetLayerData(Layer)->GetMasterBuff();
			MasterImage.MoveImage(-SearchDot,-SearchDot);
		}
		PBase->GetLogicDLLBase()->ExecuteMove(0,-SearchDot,-SearchDot,true);
		PBase->ReallocXYPixels(OriginalWidth, OriginalHeight);
	}
	else{
		if(ErrorMessageOfFalse.isEmpty()==false){
			QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
		}
	}
	return;
}

void	PieceArrangeItem::ExecuteAlignmentByAffin(double AffinParam[6])
{
	int x1 ,y1 ,x2 ,y2;
	QString ErrorMessageOfFalse;
	PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(MasterCode,ErrorMessageOfFalse);
	if(Piece!=NULL){
		LayersBase		*PBase=Piece->GetLayersBase();
		PBase->GetArea(x1 ,y1 ,x2 ,y2);
		x1+=GetArea().GetMinX();
		y1+=GetArea().GetMinY();
		x2+=GetArea().GetMinX();
		y2+=GetArea().GetMinY();
		double	cx=(x1+x2)/2;
		double	cy=(y1+y2)/2;
		double	wx=AffinParam[0]*cx+AffinParam[1]*cy+AffinParam[2];
		double	wy=AffinParam[3]*cx+AffinParam[4]*cy+AffinParam[5];
		//if(AffinParam[0]<0.95 || AffinParam[0]>1.05 || AffinParam[4]<0.95 || AffinParam[4]>1.05){
		//	MoveTo(AffinParam[2],AffinParam[5]);
		//}
		//else{
			MoveTo(wx-cx,wy-cy);
		//}
	}
	else{
		if(ErrorMessageOfFalse.isEmpty()==false){
			QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
		}
	}
}


PieceSearchItem::PieceSearchItem(PieceArrangeInPage *parentpage,LayersBase *Base,int _MasterCode)
:ServiceForLayers(Base)
,MasterCode(_MasterCode)
,ParentPage(parentpage)
{
	Piece							=NULL;
	ItemWidth						=0;
	ItemHeight						=0;
	ExecutionDLLInPiece				=NULL;
	ExecutionAlgorithmBaseInPiece	=NULL;
	ExecutionAlgorithmPageInPiece	=NULL;
}

void	PieceSearchItem::Initial(void)
{
	QString ErrorMessageOfFalse;
	PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(MasterCode,ErrorMessageOfFalse);
	if(Piece!=NULL){
		LayersBase	*LBase=Piece->GetLayersBase();
		ItemWidth	=LBase->GetDotPerLine(0);
		ItemHeight	=LBase->GetMaxLines(0);

		for(LogicDLL *L=LBase->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckAlgorithmType(AlgorithmBit_TypeMatchAlignment)==true){
				ExecutionDLLInPiece=L;
				ExecutionAlgorithmBaseInPiece=ExecutionDLLInPiece	->GetInstance();
				ExecutionAlgorithmPageInPiece=ExecutionAlgorithmBaseInPiece->GetPageData(0);
				break;
			}
		}
	}
	else{
		if(ErrorMessageOfFalse.isEmpty()==false){
			QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
		}
	}
}

bool	PieceSearchItem::Match(int ExeID ,bool MasterImage ,int cx, int cy ,double &Result)
{
	if(ExecutionDLLInPiece!=NULL){
		ImagePointerContainer TargetImages;
		if(MasterImage==true){
			ParentPage->GetMasterImages(TargetImages);
		}
		else{
			ParentPage->GetTargetImages(TargetImages);
		}
		bool	ret=ExecutionDLLInPiece->ExecuteMatch(ExeID ,TargetImages,cx, cy,Result);
		return ret;
	}
	return false;
}



//-----------------------------------------------------------------------------------------
void	PieceArrangeInPage::ListupMasterID(IntList &List)
{
	for(PieceArrangeItem *Item=(PieceArrangeItem *)GetFirstData();Item!=NULL;Item=(PieceArrangeItem *)Item->GetNext()){
		Item->ListupMasterID(List);
	}
}

void	PieceArrangeInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateOnePiece	*CmdCreateOnePieceVar=dynamic_cast<CmdCreateOnePiece *>(packet);
	if(CmdCreateOnePieceVar!=NULL){
		PieceArrangeItem	*item=(PieceArrangeItem	*)CreateItem(0);
		item->SetMasterCode(CmdCreateOnePieceVar->MasterCode);
		QString ErrorMessageOfFalse;
		PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(CmdCreateOnePieceVar->MasterCode,ErrorMessageOfFalse);
		if(Piece!=NULL){
			LayersBase		*PBase=Piece->GetLayersBase();
			FlexArea	A;
			A.SetRectangle(CmdCreateOnePieceVar->Area.GetMinX(),CmdCreateOnePieceVar->Area.GetMinY()
						,CmdCreateOnePieceVar->Area.GetMinX()+PBase->GetDotPerLine(0)
						,CmdCreateOnePieceVar->Area.GetMinY()+PBase->GetMaxLines(0));
			item->SetArea(A);
		}
		else{
			item->SetArea(CmdCreateOnePieceVar->Area);
			if(ErrorMessageOfFalse.isEmpty()==false){
				QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
			}
		}
		item->SetManualCreated(true);
		item->ReflectionData=CmdCreateOnePieceVar->ReflectionData;
		AppendItem(item);
		return;
	}
	GetPieceItemInfoPacket	*GetPieceItemInfoPacketVar=dynamic_cast<GetPieceItemInfoPacket *>(packet);
	if(GetPieceItemInfoPacketVar!=NULL){
		AlgorithmItemRoot	*Item=SearchIDItem(GetPieceItemInfoPacketVar->ItemID);
		if(Item!=NULL){
			PieceArrangeItem	*A=dynamic_cast<PieceArrangeItem *>(Item);
			if(A!=NULL){
				GetPieceItemInfoPacketVar->MasterCode=A->GetMasterCode();
			}
		}
		return;
	}
	CmdReqPieceGrid	*CmdReqPieceGridVar=dynamic_cast<CmdReqPieceGrid *>(packet);
	if(CmdReqPieceGridVar!=NULL){
		for(PieceArrangeItem *Item=(PieceArrangeItem *)GetFirstData();Item!=NULL;Item=(PieceArrangeItem *)Item->GetNext()){
			PieceGridList	*p=new PieceGridList();
			p->Page			=GetGlobalPage();
			p->PieceID		=Item->GetID();
			p->MasterCode	=Item->GetMasterCode();
			CmdReqPieceGridVar->PieceGridInfo->AppendList(p);
		}
		return;
	}
	CmdReqSelectPiece	*CmdReqSelectPieceVar=dynamic_cast<CmdReqSelectPiece *>(packet);
	if(CmdReqSelectPieceVar!=NULL){
		ListLayerAndIDPack	SelectedItem;
		ListLayerAndID	*a=new ListLayerAndID(0,CmdReqSelectPieceVar->PieceID);
		SelectedItem.AppendList(a);
		SelectItemByID(SelectedItem);
		return;
	}
}

void	PieceArrangeInPage::ExecuteAlignmentForPiece(int SearchDot)
{
	int	N=0;
	for(PieceArrangeItem *Item=(PieceArrangeItem *)GetFirstData();Item!=NULL;Item=(PieceArrangeItem *)Item->GetNext()){
		if(Item->GetSelected()==true){
			N++;
		}
	}
	GetLayersBase()->AddMaxProcessing(GetPage(),N);
	for(PieceArrangeItem *Item=(PieceArrangeItem *)GetFirstData();Item!=NULL;Item=(PieceArrangeItem *)Item->GetNext()){
		if(Item->GetSelected()==true){
			double	m[6];
			Item->CalcFittableInfo(m,SearchDot);
			Item->ExecuteAlignmentByAffin(m);
			GetLayersBase()->StepProcessing(GetPage());
		}
	}
	GetLayersBase()->SendAckToMaster(GetPage());
}

bool	PieceArrangeInPage::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
														,FlexArea &area,AlgorithmBase *OriginBase
														,int ItemClass)
{
	AlgorithmItemRoot	*a=CreateItem(ItemClass);
	QBuffer	HBuff(&item->ItemData);
	HBuff.open(QIODevice::ReadOnly);
	if(a->Load(&HBuff,GetLayersBase())==false){
		delete	a;
		return false;
	}
	a->SetArea(area);
	if(AppendItem(a)==true){
		a->SetOrigin(OriginBase);
		return true;
	}
	return false;
}
bool	PieceArrangeInPage::ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)
{
	bool	Ret=false;
	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		if(Item->GetSelected()==true){
			/*
			int	mx,my;
			PieceArrangeItem	*PItem=dynamic_cast<PieceArrangeItem *>(Item);
			PieceClass	*Pc=GetLayersBase()->GetPieceStock()->SearchAndLoad(PItem->GetMasterCode());
			mx=Item->GetArea().GetMinX()+Pc->GetLayersBase()->GetDotPerLine()/2;
			my=Item->GetArea().GetMinY()+Pc->GetLayersBase()->GetMaxLines()/2;
			*/
			AlgorithmItemRoot	*d=CreateItem(Item->GetItemClassType());
			d->SetRefereneFrom(Item,Dx,Dy);
			if(d->GetArea().CheckOverlapRectangle(0,0,GetDotPerLine(),GetMaxLines())==true){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				Item->Save(&Buff);
				Buff.seek(0);
				d->Load(&Buff,GetLayersBase());
				d->MoveTo(Dx,Dy);
				AppendItem(d);
				Ret=true;
			}
			else{
				delete	d;
			}
			Changed=true;
			CalcDone=false;
		}
	}
	return Ret;
}
ExeResult	PieceArrangeInPage::ExecuteInitialAfterEdit(int ExeID
														,ResultInPageRoot *R
														,ExecuteInitialAfterEditInfo &EInfo)
{
	//bool	b=GetParamGlobal()->CalcSingleThread;
	//GetParamGlobal()->CalcSingleThread=true;
	ExeResult	ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,R,EInfo);
	//GetParamGlobal()->CalcSingleThread=b;
	return ret;
}

void	PieceArrangeInPage::ExecuteAutoAlignmentForPiece(IntList &AutoSelectedMasterList)
{
	for(IntClass *c=AutoSelectedMasterList.GetFirst();c!=NULL;c=c->GetNext()){
		PieceSearchItem		Src(this,GetLayersBase(),c->GetValue());
		Src.Initial();

		NPListPack<AlgorithmItemPointerList>	AlgorithmItemPointerLists;
		int	SkipDot=2;
		for(int y=1;y<GetMaxLines()-Src.ItemHeight-1;y+=SkipDot){
			for(int x=1;x<GetDotPerLine()-Src.ItemWidth-1;x+=SkipDot){
				AlgorithmItemPointerList *p;
				int	DstX1=x;
				int	DstY1=y;
				int	DstX2=x+Src.ItemWidth;
				int	DstY2=y+Src.ItemHeight;
				for(p=AlgorithmItemPointerLists.GetFirst();p!=NULL;p=p->GetNext()){
					int	SrcX1=p->GetItem()->GetArea().GetMinX();
					int	SrcY1=p->GetItem()->GetArea().GetMinY();
					int	SrcX2=p->GetItem()->GetArea().GetMaxX();
					int	SrcY2=p->GetItem()->GetArea().GetMaxY();

					if(CheckOverlapRectRect( SrcX1 ,SrcY1 ,SrcX2 ,SrcY2
											,DstX1 ,DstY1 ,DstX2 ,DstY2)==true){
						break;
					}
				}
				if(p==NULL){
					double	Result=0;
					if(Src.Match(0,true,x,y,Result)==true){
						int	Dx=0;
						int	Dy=0;
						for(int dy=-3;dy<=3;dy++){
							for(int dx=-3;dx<=3;dx++){
								double	iResult=0;
								if(Src.Match(0,true,x+dx,y+dy,iResult)==true){
									if(Result<iResult){
										Result=iResult;
										Dx=dx;
										Dy=dy;
									}
								}
							}
						}

						PieceArrangeItem	*k=(PieceArrangeItem *)CreateItem();
						FlexArea	Area;
						Area.SetRectangle(x+Dx,y+Dy
										,x+Dx+Src.ItemWidth,y+Dy+Src.ItemHeight);
						k->SetArea(Area);
						k->SetMasterCode(c->GetValue());
						k->AlignmentProbability=Result;
						AppendItem(k);
						p=new AlgorithmItemPointerList(k);
						AlgorithmItemPointerLists.AppendList(p);
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------
PieceArrangeBase::PieceArrangeBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPiece					=Qt::green;
	ColorSelected				=Qt::yellow;
	ColorActive					=Qt::red;
	TransparentLevel			=120;
	TransparentLevelNonSelection=20;
	TempPath					=/**/"c:/";
	PieceGUIFile				=/**/"";
	EditorPathFile				=/**/"InspectionEditor.exe";

	SetParam(&ColorPiece		, /**/"Color" ,/**/"ColorPiece"			,LangSolver.GetString(XPieceArrange_LS,LID_1)/*"Color for Piece"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XPieceArrange_LS,LID_3)/*"Color for Selected Piece"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XPieceArrange_LS,LID_5)/*"Color for Active Piece"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XPieceArrange_LS,LID_7)/*"Color for Transparent display level"*/);
	SetParam(&TransparentLevelNonSelection	, /**/"Color" ,/**/"TransparentLevelNonSelection"	,"Color for Transparent display level of non selection");

	SetParamPath	(&TempPath		, /**/"File" ,/**/"TempPath"		,LangSolver.GetString(XPieceArrange_LS,LID_9)/*"Path name for Temporary file"*/);
	SetParamPath	(&PieceGUIFile	, /**/"File" ,/**/"PieceGUIFile"	,"GUI file name with Path for piece edition");
	SetParamFileName(&EditorPathFile, /**/"File" ,/**/"EditorPathFile"	,"Editor program(exe) file name with Path");
}
PieceArrangeBase::~PieceArrangeBase(void)
{
}

AlgorithmDrawAttr	*PieceArrangeBase::CreateDrawAttr(void)
{
	return new PieceDrawAttr(GetLayersBase());
}

void	PieceArrangeBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPieceCreateTempFiles	*CmdPieceCreateTempFilesVar=dynamic_cast<CmdPieceCreateTempFiles *>(packet);
	if(CmdPieceCreateTempFilesVar!=NULL){
		CreateTempFiles(CmdPieceCreateTempFilesVar->ParamFileName ,CmdPieceCreateTempFilesVar->PixFileName);
		return;
	}
	CmdPieceAdd	*CmdPieceAddVar=dynamic_cast<CmdPieceAdd *>(packet);
	if(CmdPieceAddVar!=NULL){
		SelectExpandableAlgorithmForm	*Q=new SelectExpandableAlgorithmForm(NULL,GetLayersBase());
		Q->exec();

		PieceArrangeInPage	*P=(PieceArrangeInPage *)GetPageData(CmdPieceAddVar->GlobalPage);
		PieceArrangeItem	*Item=(PieceArrangeItem *)P->CreateItem(0);
		Item->ReflectionData	=Q->ReflectionAttrData;
		FlexArea	Area;
		int	x1=min(min(CmdPieceAddVar->X1,CmdPieceAddVar->X2),min(CmdPieceAddVar->X3,CmdPieceAddVar->X4));
		int	x2=max(max(CmdPieceAddVar->X1,CmdPieceAddVar->X2),max(CmdPieceAddVar->X3,CmdPieceAddVar->X4));
		int	y1=min(min(CmdPieceAddVar->Y1,CmdPieceAddVar->Y2),min(CmdPieceAddVar->Y3,CmdPieceAddVar->Y4));
		int	y2=max(max(CmdPieceAddVar->Y1,CmdPieceAddVar->Y2),max(CmdPieceAddVar->Y3,CmdPieceAddVar->Y4));
		Area.SetRectangle(x1 ,y1 ,x2 ,y2);
		Item->SetArea(Area);
		Item->SetMasterCode(CmdPieceAddVar->MasterCode);
		P->AppendItem(Item);
		delete	Q;
		return;
	}
	CmdExecuteAlignmentPiece	*CmdExecuteAlignmentPieceVar=dynamic_cast<CmdExecuteAlignmentPiece *>(packet);
	if(CmdExecuteAlignmentPieceVar!=NULL){
		PieceArrangeInPage	*P=(PieceArrangeInPage *)GetPageData(CmdExecuteAlignmentPieceVar->LocalPage);
		if(P!=NULL){
			P->ExecuteAlignmentForPiece(CmdExecuteAlignmentPieceVar->SearchDot);		
		}
		return;
	}
	CmdReflectionAttrPack	*CmdReflectionAttrPackVar=dynamic_cast<CmdReflectionAttrPack *>(packet);
	if(CmdReflectionAttrPackVar!=NULL){
		SelectExpandableAlgorithmForm	*Q=new SelectExpandableAlgorithmForm(&CmdReflectionAttrPackVar->ReflectionData,GetLayersBase());
		Q->exec();
		CmdReflectionAttrPackVar->ReflectionData=Q->ReflectionAttrData;
		delete	Q;
		return;
	}
	CmdExecuteAutoAlignmentPiece	*CmdExecuteAutoAlignmentPieceVar=dynamic_cast<CmdExecuteAutoAlignmentPiece *>(packet);
	if(CmdExecuteAutoAlignmentPieceVar!=NULL){
		PieceArrangeInPage	*P=(PieceArrangeInPage *)GetPageData(CmdExecuteAutoAlignmentPieceVar->LocalPage);
		if(P!=NULL){
			P->ExecuteAutoAlignmentForPiece(CmdExecuteAutoAlignmentPieceVar->AutoSelectedMasterList);		
		}
		return;
	}
	CmdUpdateParts	*CmdUpdatePartsVar=dynamic_cast<CmdUpdateParts *>(packet);
	if(CmdUpdatePartsVar!=NULL){
		QString ErrorMessageOfFalse;
		if(GetLayersBase()->GetPieceStock()->ReLoadMasterDataForPiece(ErrorMessageOfFalse)==false){
			if(ErrorMessageOfFalse.isEmpty()==false){
				QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
			}
		}
		return;
	}
	GetReqMasterNamePacket	*GetReqMasterNamePacketVar=dynamic_cast<GetReqMasterNamePacket *>(packet);
	if(GetReqMasterNamePacketVar!=NULL){
		QString ErrorMessageOfFalse;
		PieceClass	*Piece=GetLayersBase()->GetPieceStock()->SearchAndLoad(GetReqMasterNamePacketVar->MasterCode
																		   ,ErrorMessageOfFalse);
		if(Piece!=NULL){
			LayersBase	*LBase=Piece->GetLayersBase();
			GetReqMasterNamePacketVar->MasterName	=LBase->GetMasterName();
		}
		else{
			if(ErrorMessageOfFalse.isEmpty()==false){
				QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
			}
		}
		return;
	}
}

bool	PieceArrangeBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	PieceArrangeBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

void	PieceArrangeBase::ClearTempFiles(void)
{
	if(GetLayersBase()->GetBootingLevel()==0){
		QString	ParamFileName;
		ParamFileName	=	TempPath;
		if(TempPath.right(1)!=QDir::separator () && TempPath.right(1)!=::GetSeparator())
			ParamFileName	= ParamFileName+::GetSeparator();
		ParamFileName	= ParamFileName+QString(/**/"GParam")+QString(/**/"*.tmp");
		RemoveFiles(ParamFileName);
	
		QString	PixFileName;
		PixFileName	=	TempPath;
		if(TempPath.right(1)!=QDir::separator () && TempPath.right(1)!=::GetSeparator())
			PixFileName	= PixFileName+::GetSeparator();
		PixFileName	= PixFileName+QString(/**/"Pix")+QString(/**/"*.tmp");
		RemoveFiles(PixFileName);
	}
}
bool	PieceArrangeBase::CreateTempFiles(QString &ParamFileName ,QString &PixFileName)
{
	int	i;
	for(i=0;i<1000;i++){
		ParamFileName	=	TempPath;
		if(TempPath.right(1)!=QDir::separator () && TempPath.right(1)!=::GetSeparator())
			ParamFileName	= ParamFileName+::GetSeparator();
		ParamFileName	= ParamFileName+QString(/**/"GParam")+QString::number(GetLayersBase()->GetBootingLevel())
			+QString(/**/"_")+QString::number(i)+QString(/**/".tmp");
		if(QFile::exists(ParamFileName)==false)
			break;
	}
	if(i>=1000)
		return false;

	for(i=0;i<1000;i++){
		PixFileName	=	TempPath;
		if(TempPath.right(1)!=QDir::separator () && TempPath.right(1)!=::GetSeparator())
			PixFileName	= PixFileName+::GetSeparator();
		PixFileName	=	PixFileName	+QString(/**/"Pix")+QString::number(GetLayersBase()->GetBootingLevel())
			+QString(/**/"_")+QString::number(i)+QString(/**/".tmp");
		if(QFile::exists(PixFileName)==false)
			break;
	}
	if(i>=1000)
		return false;
	return true;
}

void	PieceArrangeBase::ListupMasterID(IntList &List)
{
	for(int page=0;page<GetPageNumb();page++){
		PieceArrangeInPage	*P=(PieceArrangeInPage *)GetPageData(page);
		if(P==NULL)
			continue;
		P->ListupMasterID(List);
	}
	
}

bool	PieceArrangeBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->y);
	area.MoveToNoClip(globalDx,globalDy);
	if(GetLayersBase()->GetPageData(item->Page)->IsOverlapped(area)==true){
		//GetLayersBase()->GetPageData(item->Page)->ClipMoveAreaFromGlobal(area);
		area.MoveToNoClip(-GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->x
						, -GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->y);
		AlgorithmInPageRoot	*Ap=GetPageData(item->Page);
		if(Ap!=NULL){
			if(Ap->ExecutePaste(PastedLayer,item ,globalDx, globalDy,area)==false){
				return false;
			}
		}
	}
	return true;
}

ExeResult	PieceArrangeBase::ExecuteInitialAfterEdit	(int ExeID 
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	QString ErrorMessageOfFalse;
	if(GetLayersBase()->GetPieceStock()->ExecuteInitialAfterEdit	(ExeID,EInfo,ErrorMessageOfFalse)==false){
		QMessageBox::critical(NULL,"Load Error",ErrorMessageOfFalse);
	}
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		//AlgorithmBase	*PBase=L->GetInstance();
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(L->GetDLLRoot(),L->GetDLLName());
		PieceArrangeBase	*PABase=dynamic_cast<PieceArrangeBase *>(ABase);
		if(PABase==NULL){
			ABase->InitializeFromParts();
		}
	}
	return AlgorithmBase::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
}