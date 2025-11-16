#include "XDateTime.h"
#include <QThread>
//#include "XCameraInterfaceDLL.h"
#include "XCameraClass.h"
#include "XRWExecuteCamera.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <stdio.h>
#include "XParamGlobal.h"
#include "XFileRegistry.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"
#include "XResultDLLManager.h"
//#include "XFilterManager.h"
#include "XIntClass.h"
#include "XForWindows.h"
//#include "XSequence.h"
#include "XPIOButton.h"
#include "XLogOut.h"
#include "XResult.h"
#include "swap.h"
#include <omp.h>

const	int		MAXBUFFERCOUNTS=10000;
const	int		ExeSleepTimeMilisec=1;

RWExecuteCamera	*RWExecuteCamera::StaticInstance=NULL;
void	KickAutoStart(LayersBase *base);


//================================================================================================

RWExecuteCamera::RWExecuteCamera(QObject *parent ,EntryPointBase *_EntryPoint ,SeqLocalParam *_SeqParam) 
: ExecuteInspectBase(parent,_EntryPoint,_SeqParam)
,GoSlotAutomodeStart(false)
{
	Cam						=NULL;
	AllocatedCamNumb		=0;
	StaticInstance			=this;
	StackedCountInAutoMode	=0;

	StatusCameraHalt		=false;
	NowOnWorking			=false;
	SignalCounter			=0;

	TriggeredCapture	=false;
	setPriority(QThread::HighestPriority);
}

RWExecuteCamera::~RWExecuteCamera(void)
{
	Release();
}

bool	RWExecuteCamera::InitialCamera(int32 &ErrorCode)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]==NULL){
				CameraErrorCode=Error_CameraDLL;
				return(false);
			}
			if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
				CameraErrorCode=ErrorCode;
				return(false);
			}
			int	LanguageCode=GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
			Cam[i]->SetLanguageCode(LanguageCode);
			CameraErrorCode=ErrorCode;
		}
	}
	return(true);
}
bool	RWExecuteCamera::ChangeCameraInfo(CameraReqInfoAnyData *anydata)
{
	if(IsLocalCamera()==true){
		ChangingCameraInfo.lock();
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->ChangeInfo(GetParamGlobal()->GetDotPerLineInCamera(i) 
								 ,GetParamGlobal()->GetMaxLinesInCamera(i)
								 , GetLayerNumb(),GetPageNumb()
								 ,anydata)==false){
				ChangingCameraInfo.unlock();
				return(false);
			}
		}
		ChangingCameraInfo.unlock();
	}
	return true;
}

bool	RWExecuteCamera::CheckCameraDLL(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->CheckCameraDLL()==false){
				return false;
			}
		}
	}
	return true;
}

QString	RWExecuteCamera::MakeCamDefaultName(void)
{
	QString	Str1=GetLayersBase()->GetUserPath()+QDir::separator()+GetParamGlobal()->CameraSetting_FileName;
	QFileInfo	Info(Str1);
	if(Info.isRelative()==true){
		Info.makeAbsolute();
	}
	QString	ComputerName;
	while(::MtGetComputerName(ComputerName)==false){
		GSleep(100);
	}
	QString	FName=Info.path()+GetSeparator()+Info.completeBaseName()
				+ QString("_")+ComputerName
				+ QString(".")+Info.suffix();
	return FName;
}

bool	RWExecuteCamera::LoadDefault(void)
{
	QString	Str1=MakeCamDefaultName();
	QFile	file1(Str1);
	if(file1.open(QIODevice::ReadOnly)==true){
		if(Load(&file1)==true){
			ChangeCameraInfo();
			return true;
		}
	}
	QString	Str2=GetLayersBase()->GetUserPath()+QDir::separator()+GetParamGlobal()->CameraSetting_FileName;
	QFile	file2(Str2);
	if(file2.open(QIODevice::ReadOnly)==true){
		if(Load(&file2)==true){
			ChangeCameraInfo();
			return true;
		}
	}
	return false;
}

bool	RWExecuteCamera::Load(QIODevice *file)
{
	for(int i=0;i<GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID) && i<AllocatedCamNumb;i++){
		int32	Len;
		if(::Load(file,Len)==false){
			return(false);
		}
		QByteArray	AR;
		if(::Load(file,AR)==false){
			return(false);
		}
		QBuffer	TmpBuff(&AR);
		TmpBuff.open(QIODevice::ReadOnly);
		if(Cam[i]->Load(TmpBuff)==false){
			return(false);
		}
	}
	return(true);
}

bool	RWExecuteCamera::SaveDefault(void)
{
	QString	Str=MakeCamDefaultName();
	QFile	file(Str);
	if(file.open(QIODevice::WriteOnly)==true){
		if(Save(&file)==false)
			return false;
		return true;
	}
	return false;
}
bool	RWExecuteCamera::Save(QIODevice *file)
{
	for(int i=0;i<AllocatedCamNumb;i++){
		QBuffer	TmpBuff;
		TmpBuff.open(QIODevice::WriteOnly);
		if(Cam[i]->Save(TmpBuff)==false){
			return(false);
		}
		int32	Len=TmpBuff.size();
		if(::Save(file,Len)==false){
			return(false);
		}
		QByteArray	AR=TmpBuff.buffer();
		if(::Save(file,AR)==false){
			return(false);
		}
	}
	return true;
}


void	RWExecuteCamera::Initial(void)
{
	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
	Cam=new CameraClass*[AllocatedCamNumb];
	for(int i=0;i<AllocatedCamNumb;i++){
		Cam[i]=new CameraClass(i,GetLayersBase());
	}
	connect( this,SIGNAL(SignalCaptureHalt())							
			,this,SLOT(SlotCaptureHalt())							,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalInspectionRefresh(LayersBase *,int64))	
			,this,SLOT(SlotInspectionRefresh(LayersBase *,int64))	,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalInspectionOnTheWay(int64))				
			,this,SLOT(SlotInspectionOnTheWay(int64))				,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalRunByEveryInspection(LayersBase *,int64))	
			,this,SLOT(SlotRunByEveryInspection(LayersBase *,int64)),Qt::QueuedConnection);
	connect( this,SIGNAL(SignalOccurError(int))
			,this,SLOT(SlotOccurError(int))							,Qt::QueuedConnection);
}

IntList	DbgFinList;
IntList	DbgStrFinList;

CameraClass		*RWExecuteCamera::GetCamera(int n)
{	
	if(0<=n && n<GetParamGlobal()->TotalCameraNumb)
		return Cam[n];
	return NULL;
}

int		RWExecuteCamera::GetCameraDim(CameraClass *CamDim[])
{
	int	n=0;
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb;i++){
		CamDim[i]=Cam[i];
		n++;
	}
	return n;
}

void	RWExecuteCamera::SetCameraDim(CameraClass *CamDim[])
{
	GetLayersBase()->LockWChangingDataStructure();
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb;i++){
		Cam[i]=CamDim[i];
	}
	GetLayersBase()->UnlockChangingDataStructure();
}

void	RWExecuteCamera::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SpecifiedDirectly(v);
			}
		}
	}
	CmdReqInspectionRefresh	*CmdReqInspectionRefreshVar=dynamic_cast<CmdReqInspectionRefresh *>(v);
	if(CmdReqInspectionRefreshVar!=NULL){
		emit	SignalInspectionRefresh(GetLayersBase(),CmdReqInspectionRefreshVar->InspectionID);
		for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
			emit	SignalInspectionRefresh(L->Base,CmdReqInspectionRefreshVar->InspectionID);
		}
		return;
	}
}

void	RWExecuteCamera::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SetScanInfo(ScanNumber ,ScanMastered);
			}
		}
	}
}

void	RWExecuteCamera::Release(void)
{
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
}

void	RWExecuteCamera::CamRelease(void)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			delete	Cam[i];
		}
		delete	[]Cam;
	}
	Cam=NULL;
}

bool	RWExecuteCamera::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}

int		RWExecuteCamera::GetCameraCount(void)
{
	int	n=0;
	for(int i=0;i<AllocatedCamNumb;i++){
		switch(i){
		case 0:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter);
			if(n>0){
				return n;
			}
			break;
		case 1:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter2);
			if(n>0){
				return n;
			}
			break;
		case 2:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter3);
			if(n>0){
				return n;
			}
			break;
		case 3:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter4);
			if(n>0){
				return n;
			}
			break;
		default:
			return -1;
		}
	}
	return -1;
}

bool	RWExecuteCamera::CheckCamera(int32 &ErrorCode)
{
	if(IsLocalCamera()==true){
		bool	Reallocation=false;
		ChangingCameraInfo.lock();
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->ShouldRealloc(GetParamGlobal())==true){
				delete	Cam[i];
				Cam[i]=NULL;
				Reallocation=true;
			}
		}
		if(Reallocation==true){
			LoopToWait:;
			GSleep(2000);
			PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(0);
			if(Ph==NULL)
				goto	LoopToWait;
			for(int page=0;page<GetPageNumb();page++){
				DataInPage *Pg=Ph->GetPageData(page);
				if(Pg==NULL)
					goto	LoopToWait;
				for(int Layer=0;Layer<GetLayerNumb();Layer++){
					DataInLayer	*Ly=Pg->GetLayerData(Layer);
					if(Ly==NULL)
						goto	LoopToWait;
					if(GetParamGlobal()->AllocateMasterBuff==true && Ly->IsMasterBuffEnabled()==false)
						goto	LoopToWait;
					if(GetParamGlobal()->AllocateTargetBuff==true && Ly->IsTargetBuffEnabled()==false)
						goto	LoopToWait;
				}
			}
			for(int i=0;i<AllocatedCamNumb;i++){
				Cam[i]=new CameraClass(i,GetLayersBase());
				if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
					return false;
				}
			}
		}
		ChangingCameraInfo.unlock();
		return true;
	}
	return false;
}

bool	RWExecuteCamera::CapturePrepare(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->PrepareCapture();
		}
		return(true);
	}
	return(false);
}
bool	RWExecuteCamera::CaptureStart(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->StartCapture();
		}
		//qWarning(/**/"CaptureStart\n");

		StatusCameraHalt=false;
		TriggeredCapture=true;
		return(true);
	}
	return(false);
}


bool	RWExecuteCamera::CaptureHalt(void)
{
	if(IsLocalCamera()==true){
		StatusCameraHalt=true;
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->HaltCapture();
		}
		GetLayersBase()->ClearTopInCapturedPageLayer();
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
		GetLayersBase()->PopCurrentStrategicNumberForCalc();

		ClearHaltMode();
		TriggeredCapture=false;
		return(true);
	}
	GetLayersBase()->CloseProcessingForm();
	return(false);
}
void	RWExecuteCamera::SlotCaptureHalt()
{
	if(GetEntryPoint()->IsMasterPC()==true){

		int	LPage=-1;
		do{
			LPage=GetLayersBase()->GetTopPageInCapturedPageLayer(true);
			if(LPage>=0){
				GetLayersBase()->PopCurrentStrategicNumberForCalc();
			}
		}while(LPage>=0);
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	}
}

int		RWExecuteCamera::CaptureGetState(void)
{
	if(IsLocalCamera()==true){
		if(StatusCameraHalt==true){
			GoHalt();
		}
		int	ret=0;
		for(int i=0;i<AllocatedCamNumb;i++){
			int	W=Cam[i]->GetStatus();
			ret|=W;
		}
		return(ret);
	}
	return(0);
}

IntList	PDbgSlotList;

bool	RWExecuteCamera::CaptureGetMasterImage(int CStrategic,ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
				ImageBuffer	*Buff[P->GetLayerNumb()];
				int			BuffNumb=0;
				for(int layer=0;layer<P->GetLayerNumb();layer++){
					DataInLayer	*L=P->GetLayerData(layer);
					Buff[BuffNumb]=L->GetMasterBuffPointer();
					CapturedList.Merge(CPhase,page,layer);
					BuffNumb++;
				}
				if(page<AllocatedCamNumb){
					bool XDirReverse ,YDirReverse;
					GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
					bool tXDirReverse	=XDirReverse;
					bool tYDirReverse	=YDirReverse;
					Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
					if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
						ImageReverse(page,Buff ,BuffNumb);
					}
					ImageYDelay(page,Buff ,BuffNumb);
				}
			}
			if(PhaseCodes.GetCount()>1){
				for(int i=1;i<PhaseCodes.GetCount();i++){
					int	phase=PhaseCodes[i];
					for(int page=0;page<GetPageNumb();page++){
						DataInPage	*Ps=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
						DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
						for(int layer=0;layer<Ps->GetLayerNumb();layer++){
							DataInLayer	*Ls=Ps->GetLayerData(layer);
							DataInLayer	*Ld=Pd->GetLayerData(layer);
							Ld->GetMasterBuff()=Ls->GetMasterBuff();
							CapturedList.Merge(phase,page,layer);
						}
					}
				}
			}
		}
	}
	else{
		if(IsLocalCamera()==true){
			if((GetParamGlobal()->DebugLevel & 0x04)!=0){
				PDbgSlotList.AppendList(new IntClass(CStrategic));
			}
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(CStrategic,SList);
			int	N=0;
			int	PageType[10];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}

			//Žæ‚èž‚Ý‚ð‘‚­‚·‚é‚½‚ß‚Éæ‚ÉGetImage‚¾‚¯‚ðs‚¤
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
			bool XDirReverse ,YDirReverse;
			GetLayersBase()->GetParamGlobal()->GetPageDir(GetLayersBase()->GetCurrentStrategicNumber() ,XDirReverse ,YDirReverse);
			bool tXDirReverse	=XDirReverse;
			bool tYDirReverse	=YDirReverse;
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					int	BuffNumb=0;
					ImageBuffer	*Buff[SList.GetCount()];
					int	CamNo=GetParamGlobal()->GetCameraNo(PageType[camcode]);
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetMasterBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					if(CamNo<AllocatedCamNumb){
						tXDirReverse	=XDirReverse;
						tYDirReverse	=YDirReverse;
						Cam[CamNo]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
					}
				}
			//}
			if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					int	BuffNumb=0;
					ImageBuffer	*Buff[SList.GetCount()];
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetMasterBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					ImageReverse(GetLayersBase()->GetCurrentStrategicNumber(),Buff ,BuffNumb);
				}
			}
				
			for(int camcode=0;camcode<PageTypeNumb;camcode++){
				int	BuffNumb=0;
				ImageBuffer	*Buff[SList.GetCount()];
				for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
					if(PageType[camcode]!=s->Page)
						continue;
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
					DataInLayer	*L=P->GetLayerData(s->Layer);
					Buff[BuffNumb]=L->GetMasterBuffPointer();
					CapturedList.Merge(CPhase,s->Page,s->Layer);
					BuffNumb++;
					//if(BuffNumb>=MAXBUFFERCOUNTS)
					//	break;
				}
				ImageYDelay(PageType[camcode],Buff ,BuffNumb);
			}
		}
	}
	GetLayersBase()->ExecuteFilteringMaster();
	GetLayersBase()->SetEdited(true);

	return(true);
}
static	int	CaptureGetTargetImageCounter=0;
static	int	CaptureGetTargetImageDbg=0;
static	IntList	CaptureGetTargetImageList;
DWORD	FilteringMilisec;

bool	RWExecuteCamera::CaptureGetTargetImage(ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];

	CurrentCapturedPageLayer.RemoveAll();
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			int	N=GetPageNumb();
			if(N==1){
				for(int page=0;page<N;page++){
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
					ImageBuffer	*Buff[P->GetLayerNumb()];//MAXBUFFERCOUNTS];
					ImageBuffer	*TRBuff[P->GetLayerNumb()];//MAXBUFFERCOUNTS];
					int			BuffNumb=0;
					for(int layer=0;layer<P->GetLayerNumb();layer++){
						DataInLayer	*L=P->GetLayerData(layer);
						L->StoringStartTargetBuff();
						Buff  [BuffNumb]=L->GetTargetBuffPointer();
						TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
						CapturedList.Merge(CPhase,page,layer);
						BuffNumb++;
					}
					if(page<AllocatedCamNumb){
						bool XDirReverse ,YDirReverse;
						GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
						bool tXDirReverse	=XDirReverse;
						bool tYDirReverse	=YDirReverse;
						if(Cam[page]->IsTREffective()==false){
							Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
						}
						else{
							Cam[page]->GetImage(Buff ,TRBuff ,BuffNumb,tXDirReverse ,tYDirReverse);
						}
						if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
							ImageReverse(page,Buff ,BuffNumb);
						}
						ImageYDelay(page,Buff ,BuffNumb);
					}
					if(GetParamGlobal()->AllocCamTargetBuffer==true){
						for(int layer=0;layer<P->GetLayerNumb();layer++){
							DataInLayer	*L=P->GetLayerData(layer);
							L->GetCamTargetBuff()=L->GetTargetBuff();
						}
					}
				}
			}
			else{
				if(GetParamGlobal()->GetMaxScanStrategy()==1 && GetPageNumb()>AllocatedCamNumb){						
					for(int CamNo=0;CamNo<AllocatedCamNumb;CamNo++){
						int			BuffNumb=0;
						ImageBuffer	*Buff[1000];
						ImageBuffer	*TRBuff[1000];
						IntList PageList;
						GetParamGlobal()->GetPageListFromCameraNo(CamNo ,PageList);
						for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
							int	page=p->GetValue();
							DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								L->StoringStartTargetBuff();
								Buff  [BuffNumb]=L->GetTargetBuffPointer();
								TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
								CapturedList.Merge(CPhase,page,layer);
								BuffNumb++;
								if(BuffNumb>1000)
									break;
							}
						}
						bool XDirReverse=false ,YDirReverse=false;
						if(Cam[CamNo]->IsTREffective()==false)
							Cam[CamNo]->GetImage(Buff ,BuffNumb,XDirReverse ,YDirReverse);
						else
							Cam[CamNo]->GetImage(Buff ,TRBuff,BuffNumb,XDirReverse ,YDirReverse);
						if(XDirReverse==true || YDirReverse==true){
							for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
								int	page=p->GetValue();
								ImageReverse(page,Buff ,BuffNumb);
							}
						}
					}
				}
				else{
					#pragma omp parallel for
					for(int page=0;page<N;page++){
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
						ImageBuffer	*Buff[P->GetLayerNumb()];
						ImageBuffer	*TRBuff[P->GetLayerNumb()];
						int			BuffNumb=0;
						for(int layer=0;layer<P->GetLayerNumb();layer++){
							DataInLayer	*L=P->GetLayerData(layer);
							L->StoringStartTargetBuff();
							Buff[BuffNumb]=L->GetTargetBuffPointer();
							TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
							#pragma omp critical
							{
								CapturedList.Merge(CPhase,page,layer);
							}
							BuffNumb++;
						}
						if(page<AllocatedCamNumb){
							bool XDirReverse ,YDirReverse;
							GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
							bool tXDirReverse	=XDirReverse;
							bool tYDirReverse	=YDirReverse;
							if(Cam[page]->IsTREffective()==false)
								Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
							else
								Cam[page]->GetImage(Buff ,TRBuff,BuffNumb,tXDirReverse ,tYDirReverse);
							if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
								ImageReverse(page,Buff ,BuffNumb);
							}
							ImageYDelay(page,Buff ,BuffNumb);
						}
						if(GetParamGlobal()->AllocCamTargetBuffer==true){
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								L->GetCamTargetBuff()=L->GetTargetBuff();
							}
						}
					}
				}
			}
			if(PhaseCodes.GetCount()>1){
				for(int i=1;i<PhaseCodes.GetCount();i++){
					int	phase=PhaseCodes[i];
					for(int page=0;page<GetPageNumb();page++){
						if(GetLayersBase()->GetPageDataPhase(phase)->GetFromSourcePhase()==CPhase){
							DataInPage	*Ps=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
							DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
							for(int layer=0;layer<Ps->GetLayerNumb();layer++){
								DataInLayer	*Ls=Ps->GetLayerData(layer);
								DataInLayer	*Ld=Pd->GetLayerData(layer);
								
								if(GetParamGlobal()->CommonTargetBetweenPhases==false){
									Ld->StoringStartTargetBuff();
									Ld->GetTargetBuff()		=Ls->GetTargetBuff();
									CapturedList.Merge(phase,page,layer);
								}
								if(GetParamGlobal()->AllocCamTargetBuffer==true){
									Ld->GetCamTargetBuff()	=Ls->GetTargetBuff();
								}
							}
						}
					}
				}
			}
		}
	}	
	else{
		if(CaptureGetTargetImageCounter==2)
			CaptureGetTargetImageDbg++;

		if(IsLocalCamera()==true){
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),SList);
			int	N=0;
			int	PageType[10];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}
	
			//Žæ‚èž‚Ý‚ð‘‚­‚·‚é‚½‚ß‚Éæ‚ÉGetImage‚¾‚¯‚ðs‚¤
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
			bool XDirReverse ,YDirReverse;
			GetLayersBase()->GetParamGlobal()->GetPageDir(GetLayersBase()->GetCurrentStrategicNumber() ,XDirReverse ,YDirReverse);
			bool tXDirReverse	=XDirReverse;
			bool tYDirReverse	=YDirReverse;
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					ImageBuffer	*Buff[SList.GetCount()];
					ImageBuffer	*TRBuff[SList.GetCount()];
					int	BuffNumb=0;
					int	CamNo=GetParamGlobal()->GetCameraNo(PageType[camcode]);
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						L->StoringStartTargetBuff();
						Buff  [BuffNumb]=L->GetTargetBuffPointer();
						TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					if(CamNo<AllocatedCamNumb){
						tXDirReverse	=XDirReverse;
						tYDirReverse	=YDirReverse;
						if(Cam[CamNo]->IsTREffective()==false)
							Cam[CamNo]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
						else
							Cam[CamNo]->GetImage(Buff ,TRBuff ,BuffNumb,tXDirReverse ,tYDirReverse);
						CaptureGetTargetImageList.Add(CamNo);
					}
				}
			//}
			if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					ImageBuffer	*Buff[SList.GetCount()];
					ImageBuffer	*TRBuff[SList.GetCount()];
					int	BuffNumb=0;
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						L->StoringStartTargetBuff();
						Buff  [BuffNumb]=L->GetTargetBuffPointer();
						TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					ImageReverse(GetLayersBase()->GetCurrentStrategicNumber(),Buff ,BuffNumb);
				}
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					if(GetParamGlobal()->AllocCamTargetBuffer==true){
						for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
							if(PageType[camcode]!=s->Page)
								continue;
							DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
							DataInLayer	*L=P->GetLayerData(s->Layer);
							L->GetCamTargetBuff()=L->GetTargetBuff();
						}
					}
				}
			}
			for(int camcode=0;camcode<PageTypeNumb;camcode++){
				int	BuffNumb=0;
				ImageBuffer	*Buff[SList.GetCount()];
				for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
					if(PageType[camcode]!=s->Page)
						continue;
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
					DataInLayer	*L=P->GetLayerData(s->Layer);
					L->StoringStartTargetBuff();
					Buff[BuffNumb]=L->GetTargetBuffPointer();
					CapturedList.Merge(CPhase,s->Page,s->Layer);
					BuffNumb++;
					//if(BuffNumb>=MAXBUFFERCOUNTS)
					//	break;
				}
				ImageYDelay(PageType[camcode],Buff ,BuffNumb);
			}
		}
	}
	FilteringMilisec=GetComputerMiliSec();
	GetLayersBase()->ExecuteFilteringTarget();
	for(ListPhasePageLayer *a=CapturedList.GetFirst();a!=NULL;a=a->GetNext()){
		DataInPage	*P=GetLayersBase()->GetPageDataPhase(a->Phase)->GetPageData(a->Page);
		DataInLayer	*L=P->GetLayerData(a->Layer);
		L->StoringFinishTargetBuff();
	}
	FilteringMilisec=GetComputerMiliSec()-FilteringMilisec;

	CaptureGetTargetImageCounter++;
	return(true);
}


void	RWExecuteCamera::GoInspect(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspect);
}
void	RWExecuteCamera::GoInspectWithoutCapture(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspectWithoutCapture);
}
void	RWExecuteCamera::GoMasterCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyMaster);
}
void	RWExecuteCamera::GoTargetCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyTarget);
}
void	RWExecuteCamera::GoGray(void)
{
	ClearHaltMode();
	SetMode(_CaptureGray);
}

void	RWExecuteCamera::ExecuteHalt(void)
{
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	GetLayersBase()->SetCurrentStrategicNumber(0);
	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);

	GetLayersBase()->ClearTopInCapturedPageLayer();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	GetLayersBase()->PopCurrentStrategicNumberForCalc();
	GoHalt();
}


void	RWExecuteCamera::CamShowSetting(int CamNo)
{
	if(Cam[CamNo]->ShowSetting(GetLayersBase()->GetMainWidget())==true){
		SaveDefault();
	}
}

void	RWExecuteCamera::Exit(GUIFormBase *)
{
	if(GetLayersBase()->GetResultDLLBase()!=NULL)
		GetLayersBase()->GetResultDLLBase()->Release();
}

int		RWExecuteCamera::GetAllocatedCameraCount(void)
{
	return min(GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID),AllocatedCamNumb);
}
bool	RWExecuteCamera::LoadCameraSetting(QIODevice *f)
{
	if(ExecuteInspectBase::LoadCameraSetting(f)==false){
		return false;
	}
	MotionMode	tMode=GetMode();
	if(tMode==_CaptureInspect || tMode==_CaptureInspectWithoutCapture || tMode==_CaptureOnlyMaster || tMode==_CaptureOnlyTarget){
		if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
			TriggeredCapture=true;
			CapturePrepare();
			CaptureStart();
		}
	}
	return(true);
}

void	RWExecuteCamera::ClearCameraBuffer(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->ClearBuffer();
		}
	}
}
bool	RWExecuteCamera::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	int	iAllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
	if(AllocatedCamNumb!=iAllocatedCamNumb){
		for(int i=0;i<AllocatedCamNumb;i++){
			delete	Cam[i];
		}
		delete	[]Cam;
		AllocatedCamNumb=iAllocatedCamNumb;
		Cam=new CameraClass*[AllocatedCamNumb];
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]=new CameraClass(i,GetLayersBase());
		}
	}
	if(AllocatedCamNumb==1){
		for(int page=0;page<newPageNumb;page++){
			GetParamGlobal()->SetCameraNo(page,0);
		}
	}
	return true;
}
//==================================================================

static	int	TrunCaptured=0;
static	int	TrunStarted=0;
static	int	TrunStartStarted1=0;
static	int	TrunStartStarted2=0;
static	int	TrunStartStarted3=0;
IntList	StrategicStartList;

void RWExecuteCamera::OccurCamError(int CamStatus)
{
	QString	Msg;
	if((CamStatus & BitCamErrorOverRun)!=0){
		Msg = "OverRun error in Camera";
	}
	else if((CamStatus & BitCamErrorElse)!=0){
		Msg = "Something error in Camera";
	}
	else if((CamStatus & BitLineInvalid)!=0) {
		Msg = "Line invalid in Camera";
	}
	GetLayersBase()->SendErrorToMaster(1 , Msg ,ErrorCodeList::_Critical);
	//emit	SignalOccurError(CamStatus);
}

void	RWExecuteCamera::SlotOccurError(int CamStatus)
{
	if((CamStatus & BitLineInvalid)!=0) {
		GUIFormBase* F=GetLayersBase()->GetMainWidget();
		if(F!=NULL) {
			QPalette	P=F->palette();
			P.setColor(QPalette::Window, Qt::red);
			F->setPalette(P);
		}
	}
}

static	DWORD		C,Cn;
static	volatile	DWORD	ExecTimeDim[100];
static	volatile	int		ExecTimeDimCount = 0;

void RWExecuteCamera::run()
{
	DWORD	TimeInThisPoint;

IdleTurn:;
	for(;;){
		LayersBase	*Layer=GetLayersBase();
		PushOnIdle();
		if(GetPermitToRun()==true){
			C=GetComputerMiliSec();

			if(GetAutoRepeat()==_AutoCaptureInspect){
 				Layer->SetStartInspectTime(XDateTime::currentDateTime());
				Layer->SetInspectionTimeMilisec(GetComputerMiliSec());

				CurrentState=_EI_Prepare;

				if(GetParamComm()->Mastered==true){
					Layer->SetCurrentStrategicNumber(Layer->GetCurrentStrategicNumberForSeq());
					ResultInspection	*Res=Layer->GetNextResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());
						GoSlotAutomodeStart=true;
					}
				}
				if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				SetMode (ExecuteInspectBase::_CaptureInspect);
			}
			else
			if(GetAutoRepeat()==_AutoCaptureOnlyTarget){
 				Layer->SetStartInspectTime(XDateTime::currentDateTime());
				Layer->SetInspectionTimeMilisec(GetComputerMiliSec());

				CurrentState=_EI_Prepare;

				if(GetParamComm()->Mastered==true){
					Layer->SetCurrentStrategicNumber(Layer->GetCurrentStrategicNumberForSeq());
					ResultInspection	*Res=Layer->GetNextResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());
						GoSlotAutomodeStart=true;
					}
				}
				if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				SetMode (ExecuteInspectBase::_CaptureOnlyTarget);
			}
			Cn=GetComputerMiliSec();

			MotionMode	CurrentModeN=GetMode();
			if(CurrentModeN==_CaptureInspect){
				Layer->GetLogCreater()->PutLog(__LINE__,"XRWExecuteCamera:Enter");

				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(Layer->GetCurrentStrategicNumber() ,false);
				
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					CurrentState=_EI_Prepare;
					if(TriggeredCapture==false || Layer->GetParamGlobal()->CaptureInBackground==false){
						CapturePrepare();
					}
				}
				
				TrunStarted++;

				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || Layer->GetParamGlobal()->CaptureInBackground==false){
					TrunStartStarted1++;
					CaptureStart();
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}

				CurrentState=_EI_OnCapturing;
				DWORD	StartWaitingPoint=::GetComputerMiliSec();
				int	CamStatus;
				if(CurrentModeN==_CaptureInspect){
					while((CamStatus=CaptureGetState())!=0){
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							TriggeredCapture=false;
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if((CamStatus & BitCamError)!=0){
							OccurCamError(CamStatus);
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							TriggeredCapture=false;
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if((CamStatus & BitLineInvalid)!=0) {
							OccurCamError(CamStatus);
						}
						msleep(ExeSleepTimeMilisec);
 						if(Layer->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				Layer->SetStartInspectTime(XDateTime::currentDateTime());

				ExecTimeDim[ExecTimeDimCount]=::GetComputerMiliSec()-StartWaitingPoint;
				ExecTimeDimCount++;
				if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
					ExecTimeDimCount=0;
				}

				TimeInThisPoint=::GetComputerMiliSec();
				Layer->LockForLoadSave();
				DWORD	WaitingMilisec=TimeInThisPoint-StartWaitingPoint;

				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					TriggeredCapture=false;
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					Layer->UnlockForLoadSave();
					goto	IdleTurn;
				}
			
				if(GetEntryPoint()->IsMasterPC()==true){
					//SetCaptured(Layer->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					//EmitSignalCaptured(Layer->GetCurrentStrategicNumber());
				}

				TrunCaptured++;
				CurrentState=_EI_OnCalc;
				TriggeredCapture=false;
				if(Layer->GetParamGlobal()->CaptureInBackground==true && Layer->GetOnTerminating()==false){
					if(GetParamGlobal()->WaitMilisecAfterScan==0){
						if(GetAutoRepeat()==_AutoCaptureInspect
						|| GetParamGlobal()->GetMaxScanStrategy()>(Layer->GetCurrentStrategicNumberForCalc()+2)
						|| (IsLocalCamera()==true && GetParamGlobal()->UnconditionalCaptureBackground==true)
						|| (GetParamGlobal()->GetMaxScanStrategy()<=1 && GetEntryPoint()->IsMasterPC()==false)){
							TriggeredCapture=true;
							TrunStartStarted2++;
							CapturePrepare();
							CaptureStart();
						}
					}
				}
			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«

					IntList PhaseCodes;
					Layer->GetCurrentPhaseFromScanPhase(PhaseCodes);
					int	CPhase=PhaseCodes[0];
					Layer->GetLogCreater()->PutLogA1(__LINE__,"XRWExecuteCamera:Captured",CPhase);

					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						Layer->UnlockForLoadSave();
						return;
					}

					ListPhasePageLayerPack CapturedList;
					if(GetCurrentCaptureSource()==_Target)
						CaptureGetTargetImage(CapturedList);
					else if(GetCurrentCaptureSource()==_Master){
						int	CStrategic=Layer->GetCurrentStrategicNumber();
						CaptureGetMasterImage(CStrategic,CapturedList);
					}

					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					int	NextCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					if(GetParamGlobal()->AutoIncrementScanPhaseNumber==true){
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							NextCurrentScanPhaseNumber++;
							if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
								NextCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((Layer->GetCurrentStrategicNumber()+1)>=GetParamGlobal()->GetMaxScanStrategy()){
								NextCurrentScanPhaseNumber++;
								if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
									NextCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					Layer->SetStartInspectionTimeMilisec(GetComputerMiliSec());
									
					int	CStrNumber=Layer->GetCurrentStrategicNumber();
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(GetParamGlobal()->GetMaxScanStrategy()<=1 
					|| GetParamGlobal()->GetMaxScanStrategy()<=(Layer->GetCurrentStrategicNumberForCalc()+1)){
						Layer->SetLatchedInspectionNumber(Layer->GetInspectionNumber());
					}
					if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
						Layer->ExecuteStartByInspection();
					}
					ResultInspection	*Res=Layer->GetCurrentResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());
						Layer->GetLogCreater()->PutLogA1(__LINE__,"XRWExecuteCamera:StartCalc",Res->GetInspectionID());
						Layer->PopCurrentStrategicNumberForCalc();

						C=TimeInThisPoint;
						DWORD	ProcessStartTime=C;
						if(GetParamGlobal()->UseExecuteCaptured==true){
							Layer->ExecuteCaptured(CapturedList);
						}
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteCaptured=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteCaptured");

						Layer->ExecutePreAlignment	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePreAlignment");

						Layer->ExecuteAlignment		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteAlignment=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteAlignment");


						Layer->ExecutePreProcessing	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreProcessing=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePreProcessing");


						Layer->ExecuteProcessing		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteProcessing=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteProcessing");


						Layer->ExecuteProcessingRevived();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteProcessingRevived");


						//ŒŸ¸Š®—¹Žž
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

						Layer->ExecutePostProcessing();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePostProcessing=Cn-C;
						Res->ExecTime.TM_TotalProcessMilisec=Cn-ProcessStartTime;
						C=Cn;
						Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePostProcessing");

						DWORD	CalcTotalMilisec=::GetComputerMiliSec()-TimeInThisPoint;
						EmitCalcDone(*Res,tCurrentScanPhaseNumber,CStrNumber);
						Layer->GetLogCreater()->PutLog(__LINE__,"EmitCalcDone");

						Layer->SetCurrentScanPhaseNumber(NextCurrentScanPhaseNumber);
						DWORD	CalcTotalMilisec2=::GetComputerMiliSec()-TimeInThisPoint;
						//
						//ExecTimeDim[ExecTimeDimCount]=CalcTotalMilisec2;	//::GetComputerMiliSec()-StartCalcTime;
						//ExecTimeDimCount++;
						//if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
						//	ExecTimeDimCount=0;
						//}
						CurrentState=_EI_IDLE;
				
						if(Layer->GetParamGlobal()->CaptureInBackground==true){
							if(GetParamGlobal()->WaitMilisecAfterScan!=0){
								TrunStartStarted3++;
								CapturePrepare();
								CaptureStart();
							}
						}

						if(GetParamGlobal()->GetMaxScanStrategy()>1){
							if(GetParamGlobal()->GetMaxScanStrategy()>(CStrNumber+1)){
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(CStrNumber+1);
							}
							else{
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(0);
							}
						}
						Layer->GetLogCreater()->PutLog(__LINE__,"EndLoop");
					}
				}
				Layer->UnlockForLoadSave();
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
			else
			if(CurrentModeN==_CaptureInspectWithoutCapture){
				Layer->GetLogCreater()->PutLog(__LINE__,"XRWExecuteCamera:Enter");

				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(Layer->GetCurrentStrategicNumber() ,false);
				
				CurrentState=_EI_StartCamera;
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				CurrentState=_EI_OnCapturing;

				DWORD	StartWaitingPoint=::GetComputerMiliSec();
				DWORD	TimeInThisPoint	 =::GetComputerMiliSec();
				DWORD	WaitingMilisec=TimeInThisPoint-StartWaitingPoint;
			
				if(GetEntryPoint()->IsMasterPC()==true){
					//SetCaptured(Layer->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					//EmitSignalCaptured(Layer->GetCurrentStrategicNumber());
				}
				Layer->SetStartInspectTime(XDateTime::currentDateTime());

				CurrentState=_EI_OnCalc;
			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					IntList PhaseCodes;
					Layer->GetCurrentPhaseFromScanPhase(PhaseCodes);
					int	CPhase=PhaseCodes[0];
					Layer->GetLogCreater()->PutLogA1(__LINE__,"XRWExecuteCamera:Captured",CPhase);

					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
					
					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					int	NextCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					if(GetParamGlobal()->AutoIncrementScanPhaseNumber==true){
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							NextCurrentScanPhaseNumber++;
							if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
								NextCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((Layer->GetCurrentStrategicNumber()+1)>=GetParamGlobal()->GetMaxScanStrategy()){
								NextCurrentScanPhaseNumber++;
								if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
									NextCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					Layer->LockForLoadSave();

					Layer->SetStartInspectionTimeMilisec(GetComputerMiliSec());
									
					int	CStrNumber=Layer->GetCurrentStrategicNumber();
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(GetParamGlobal()->GetMaxScanStrategy()<=1 
					|| GetParamGlobal()->GetMaxScanStrategy()<=(Layer->GetCurrentStrategicNumberForCalc()+1)){
						Layer->SetLatchedInspectionNumber(Layer->GetInspectionNumber());
					}
					if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
						Layer->ExecuteStartByInspection();
					}
					ResultInspection	*Res=Layer->GetCurrentResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

						Layer->GetLogCreater()->PutLogA1(__LINE__,"XRWExecuteCamera:StartCalc",Res->GetInspectionID());

						Layer->PopCurrentStrategicNumberForCalc();

						C=GetComputerMiliSec();
						DWORD	ProcessStartTime=C;
						Layer->ExecutePreAlignment	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
						C=Cn;

						Layer->ExecuteAlignment		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteAlignment=Cn-C;
						C=Cn;

						Layer->ExecutePreProcessing	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreProcessing=Cn-C;
						C=Cn;

						Layer->ExecuteProcessing		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteProcessing=Cn-C;
						C=Cn;

						Layer->ExecuteProcessingRevived();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
						C=Cn;

						//ŒŸ¸Š®—¹Žž
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

						Layer->ExecutePostProcessing	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePostProcessing=Cn-C;
						Res->ExecTime.TM_TotalProcessMilisec=Cn-ProcessStartTime;
						C=Cn;

						DWORD	CalcTotalMilisec=::GetComputerMiliSec()-TimeInThisPoint;
						EmitCalcDone(*Res,tCurrentScanPhaseNumber,CStrNumber);

						Layer->SetCurrentScanPhaseNumber(NextCurrentScanPhaseNumber);
						DWORD	CalcTotalMilisec2=::GetComputerMiliSec()-TimeInThisPoint;

						ExecTimeDim[ExecTimeDimCount]=::GetComputerMiliSec()-StartCalcTime;
						ExecTimeDimCount++;
						if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
							ExecTimeDimCount=0;
						}
						CurrentState=_EI_IDLE;
				
						if(Layer->GetParamGlobal()->CaptureInBackground==true){
							if(GetParamGlobal()->WaitMilisecAfterScan!=0){
								TrunStartStarted3++;
								CapturePrepare();
								CaptureStart();
							}
						}

						if(GetParamGlobal()->GetMaxScanStrategy()>1){
							if(GetParamGlobal()->GetMaxScanStrategy()>(CStrNumber+1)){
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(CStrNumber+1);
							}
							else{
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(0);
							}
						}
					}
					Layer->UnlockForLoadSave();
				}
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
		}
		//msleep(ExeSleepTimeMilisec);
		if(Layer->GetOnTerminating()==true){
			//CamRelease();
			return;
		}
		if(GetHaltMode()==true){
			ExecuteHalt();
			emit	SignalCaptureHalt();
			ClearHaltMode();
			msleep(100);
		}
		msleep(3);
	}
}

void	RWExecuteCamera::EmitCalcDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber)
{
	IntList	PhaseCodes;
	GetLayersBase()->GetPhaseFromScanPhase(tCurrentScanPhaseNumber,PhaseCodes);
	for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
		Res.SetCalcDone(c->GetValue());
	}

	if(GetParamGlobal()->ModePhaseOutputResult==-4 ){
		DataInExecuter	*Re=GetLayersBase()->GetExecuter(&Res);
		ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
		
		if(GetLayersBase()->GetCurrentStrategicNumber()>=(GetParamGlobal()->GetMaxScanStrategy()-1)
		&& GetLayersBase()->GetCurrentPhase()>=(GetLayersBase()->GetPhaseNumb()-1)){
			IntList PageList;
			GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();
				EPBase->FinishCapture(page);
				Re->SetResultReceivedFlag(page);
			}
			FinishInspection(&Res,nStrategicNumber);
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				EPBase->FinishCapture(page);
				Re->SetResultReceivedFlag(page);
			}
			PreFinishInspection(&Res,nStrategicNumber);
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-3 || GetPhaseNumb()<=1){
		if(tCurrentScanPhaseNumber>=GetParamGlobal()->GetScanPhaseCount()-1){
			DataInExecuter	*Re=GetLayersBase()->GetExecuter(&Res);
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
			
			if(GetParamGlobal()->GetMaxScanStrategy()>1){
				IntList PageList;
				GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(GetParamGlobal()->GetMaxScanStrategy()>1){
					IntList PageList;
					GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-2){
		if(Res.IsAllCalcDone()==true){
			if(tCurrentScanPhaseNumber>=GetParamGlobal()->GetScanPhaseCount()-1){
				DataInExecuter	*Re=GetLayersBase()->GetExecuter(&Res);
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(GetParamGlobal()->GetMaxScanStrategy()>1){
					IntList PageList;
					GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(GetParamGlobal()->GetMaxScanStrategy()>1){
						IntList PageList;
						GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
				}
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-1){
		if(tCurrentScanPhaseNumber>=GetParamGlobal()->GetScanPhaseCount()-1){
			DataInExecuter	*Re=GetLayersBase()->GetExecuter(&Res);
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

			if(GetParamGlobal()->GetMaxScanStrategy()>1){
				IntList PageList;
				GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(GetParamGlobal()->GetMaxScanStrategy()>1){
					IntList PageList;
					GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult>=0){
		int	phase=GetParamGlobal()->ModePhaseOutputResult;
		if(Res.IsCalcDone(phase)==true){
			if(tCurrentScanPhaseNumber>=GetParamGlobal()->GetScanPhaseCount()-1){
				DataInExecuter	*Re=GetLayersBase()->GetExecuter(&Res);
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(GetParamGlobal()->GetMaxScanStrategy()>1){
					IntList PageList;
					GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(GetParamGlobal()->GetMaxScanStrategy()>1){
						IntList PageList;
						GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
				}
			}
		}
	}
}

void	RWExecuteCamera::ChangeLot(void)
{
	if(GetMode()==_CaptureInspect || GetMode()==_CaptureInspectWithoutCapture){
		if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
			//GetLayersBase()->ExecuteStartByInspection();
		}
	}
}

static	XDateTime	LastStartTimeForInspection;
static	int			eRepliedCounter=0;
static	int			eOutputCounter=0;

void	RWExecuteCamera::FinishInspection(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L=GetLayersBase();
	//PacketReplied->Result	=CmdInspectionRepliedBase::_OK;
	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;

	DWORD	MiliSecTable[10];
	DWORD	C=::GetComputerMiliSec();
	DWORD	Cn;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	//EPBase->FinishCapture(localPage);
	//Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	RWExecuteCamera	*EP=(RWExecuteCamera *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(GetParamGlobal()->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(GetLayersBase()->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		//ŒŸ¸Š®—¹Žž

		if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
		|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){

			Cn=::GetComputerMiliSec();
			MiliSecTable[0]=Cn-C;
			C=Cn;

			bool3	ShadowOk;
			bool	ShadowTimeOver;
			bool	ShadowMaxError;
			L->GetShadowResult(Res
							,ShadowOk ,ShadowTimeOver, ShadowMaxError);

			Cn=::GetComputerMiliSec();
			MiliSecTable[1]=Cn-C;
			C=Cn;

			ResultPkNgPacket	ResultPacket(GetLayersBase());
			if(Re->IsResultTimeOut()==true || ShadowTimeOver==true){
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				if(Re->IsResultMaxError()==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
				}
				else{
					Res->SetMaxErrorBreak(false);
				}
			}
			else{
				Res->SetTimeOutBreak(false);
				if(Re->IsResultMaxError()==true || ShadowMaxError==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
				}
				else{
					Res->SetMaxErrorBreak(false);
				}
			}

			int	ResultCode=0;
			if(Re->IsResultOK()==true && ShadowOk==true3){
				ResultCode=1;
				ResultPacket.Ok=true3;

				Res->SetOutputCode(1);
			}
			else{
				ResultCode=2;
				ResultPacket.Ok=false3;
				Res->SetOutputCode(2);
			}
			
			Cn=::GetComputerMiliSec();
			MiliSecTable[2]=Cn-C;
			C=Cn;

			ResultInspection	*eRes=GetLayersBase()->GetCurrentResultForCalc();
			if(eRes!=NULL){
				DataInExecuter	*eRe=GetLayersBase()->GetExecuter(eRes);
				if(eRe!=Re){
					eRe->CopyResultCountFrom(*Re);
				}
				DWORD InspectionTimeMilisec=GetComputerMiliSec() - L->GetStartInspectionTimeMilisec();
				L->SetInspectionTimeMilisec(InspectionTimeMilisec);
				L->SetEndInspectionTime(XDateTime::currentDateTime());
				L->GetResultHistryData()->AddHistry(ResultCode
													,Res->GetStartTimeForInspection()
													,L->GetCurrentInspectIDForExecute()
													,Res->GetIDStr()
													,((Re->IsResultTimeOut()==true) || (Res->GetTimeOutBreak()==true))?true:false
													,((Re->IsResultMaxError()==true) || (Res->GetMaxErrorBreak()==true))?true:false
													,Res->ExecTime.TM_TotalProcessMilisec);
			
				Res->SetInspectionID(L->GetCurrentInspectIDForExecute());

				Cn=::GetComputerMiliSec();
				MiliSecTable[3]=Cn-C;
				C=Cn;

				L->ShowShadowHistory(ResultCode, InspectionTimeMilisec);

				Cn=::GetComputerMiliSec();
				MiliSecTable[4]=Cn-C;
				C=Cn;
			}

			Re->PutCurrentResult();

			Cn=::GetComputerMiliSec();
			MiliSecTable[5]=Cn-C;
			C=Cn;

			L->IncrementInspectID();
			
			L->CloseProcessingForm();

			if(GetParamGlobal()->ReDrawByInspection==true){
				int64	tInspectID=L->GetCurrentInspectIDForDisplay();
				emit	SignalRunByEveryInspection(GetLayersBase(),tInspectID);

				Cn=::GetComputerMiliSec();
				MiliSecTable[6]=Cn-C;
				C=Cn;

				for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
					emit	SignalRunByEveryInspection(L->Base,tInspectID);
				}
				Cn=::GetComputerMiliSec();
				MiliSecTable[7]=Cn-C;
				C=Cn;

				if(NowOnWorking==false && SignalCounter==0){
					int64	tInspectID=L->GetCurrentInspectIDForDisplay();
					SignalCounter+=1+ShadowLayersBasePointer.GetCount();
					emit	SignalInspectionRefresh(GetLayersBase(),tInspectID);

					Cn=::GetComputerMiliSec();
					MiliSecTable[8]=Cn-C;
					C=Cn;

					for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
						emit	SignalInspectionRefresh(L->Base,tInspectID);
					}

					Cn=::GetComputerMiliSec();
					MiliSecTable[9]=Cn-C;
					C=Cn;
				}
			}
		}
		else{
			if(Re->IsResultOK()==true){
				Res->SetOutputCode(1);
			}
			else{
				Res->SetOutputCode(2);
			}
		}
}

void	RWExecuteCamera::PreFinishInspection(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	RWExecuteCamera	*EP=(RWExecuteCamera *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(GetParamGlobal()->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(GetLayersBase()->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		//ŒŸ¸Š®—¹Žž

		if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
		|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){

			ResultPkNgPacket	ResultPacket(GetLayersBase());

			if(Re->IsResultTimeOut()==true){
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				if(Re->IsResultMaxError()==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
				}
				else{
					Res->SetMaxErrorBreak(false);
				}
			}
			else{
				Res->SetTimeOutBreak(false);
				if(Re->IsResultMaxError()==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
				}
				else{
					Res->SetMaxErrorBreak(false);
				}
			}

			if(Re->IsResultOK()==true){
				ResultPacket.Ok=true3;
				Res->SetOutputCode(1);
			}
			else{
				ResultPacket.Ok=true3;
				Res->SetOutputCode(2);
			}
			ResultInspection	*eRes=GetLayersBase()->GetCurrentResultForCalc();
			if(eRes!=NULL){
				DataInExecuter	*eRe=GetLayersBase()->GetExecuter(eRes);
				if(eRe!=Re){
					eRe->CopyResultCountFrom(*Re);
				}
			}
			L->CloseProcessingForm();
		}
		else{
			if(Re->IsResultOK()==true){
				Res->SetOutputCode(1);
			}
			else{
				Res->SetOutputCode(2);
			}
		}
		if(GetParamGlobal()->ReDrawByInspection==true){
			emit	SignalInspectionOnTheWay(L->GetCurrentInspectIDForDisplay());
		}

}

void	RWExecuteCamera::SlotInspectionRefresh(LayersBase *base,int64 InspectionID)
{
	NowOnWorking=true;
	GUIInitializer	*G=base->GetGuiInitializer();
	if(base->GetParamGlobal()->WaitmilisecForDelayedView!=0){
		G->DelayedViewRefreshInPlayer(InspectionID,base->GetParamGlobal()->WaitmilisecForDelayedView);
	}
	else{
		G->ViewRefreshInPlayer(InspectionID);
	}
	NowOnWorking=false;
	SignalCounter--;
}
void	RWExecuteCamera::SlotInspectionOnTheWay(int64 InspectionID)
{
	NowOnWorking=true;
	GetLayersBase()->GetGuiInitializer()->ViewOnTheWayInPlayer(InspectionID);
	NowOnWorking=false;
}
void	RWExecuteCamera::SlotRunByEveryInspection(LayersBase *base,int64 InspectionID)
{
	base->GetGuiInitializer()->RefreshByEveryInspection(InspectionID);
}

//=================================================================================================

