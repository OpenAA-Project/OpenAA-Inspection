#include "CaptureThreadForRealtimeGraphResource.h"
#include "CaptureThreadForRealtimeGraph.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XCameraClass.h"

CaptureThreadForRealtimeGraph::TmpBufferPerCam::TmpBufferPerCam(int32 camNo ,LayersBase *base)
:ServiceForLayers(base),CamNo(camNo)
{
	if(base->GetEntryPoint()!=NULL){
		Executer=base->GetEntryPoint()->GetExecuteInspect();
	}
	else{
		Executer=NULL;
	}
	IBuffPointer=new ImageBuffer*[GetLayerNumb()];
	for(int layer=0;layer<GetLayerNumb();layer++){
		IBuffPointer[layer]=NULL;
	}
	CamPointer=NULL;
	ModeCamChangedInfo=false;
}

CaptureThreadForRealtimeGraph::TmpBufferPerCam::~TmpBufferPerCam(void)
{
	IBuffer.RemoveAll();
	delete	[]IBuffPointer;
	IBuffPointer=NULL;
}

void	CaptureThreadForRealtimeGraph::TmpBufferPerCam::Allocate(void)
{
	if(Executer!=NULL){
		CamPointer=Executer->GetCamera(CamNo);
		if(CamPointer!=NULL){
			bool	Ret=CamPointer->ChangeInfo(GetParamGlobal()->GetDotPerLineInCamera(CamNo),TempMaxLines, GetLayerNumb(),GetPageNumb());
			if(Ret==true){
				ModeCamChangedInfo=true;
				IBuffer.RemoveAll();
				for(int layer=0;layer<GetLayerNumb();layer++){
					ImageBufferList	*mem=new ImageBufferList(ImageBufferOther,GetParamGlobal()->GetDotPerLineInCamera(CamNo),TempMaxLines);
					IBuffer.AppendList(mem);
					IBuffPointer[layer]=mem;
				}
			}
			else{
				ModeCamChangedInfo=false;
				DataInPage	*dp=GetLayersBase()->GetPageData(CamNo);
				if(dp!=NULL){
					for(int layer=0;layer<GetLayerNumb();layer++){
						IBuffPointer[layer]=&(dp->GetLayerData(layer)->GetTargetBuff());
					}
				}
			}
		}
	}
}


void	CaptureThreadForRealtimeGraph::TmpBufferPerCam::RestoreCamInfo(void)
{
	if(ModeCamChangedInfo==true && CamPointer!=NULL){
		CamPointer->RestoreCamInfo();
	}
}

void	CaptureThreadForRealtimeGraph::TmpBufferPerCam::StartCapture(void)
{
	if(CamPointer!=NULL){
		CamPointer->PrepareCapture();
		CamPointer->StartCapture();
	}
}

int	CaptureThreadForRealtimeGraph::TmpBufferPerCam::GetStatus(void)
{
	if(CamPointer!=NULL){
		return CamPointer->GetStatus();
	}
	return -1;
}

void	CaptureThreadForRealtimeGraph::TmpBufferPerCam::GetImage(void)
{
	if(CamPointer!=NULL){
		bool	XReverse=false;
		bool	YReverse=false;
		CamPointer->GetImage(IBuffPointer ,GetLayerNumb(),XReverse,YReverse);
	}
}

//===================================================================================
CaptureThreadForRealtimeGraph::CaptureThreadForRealtimeGraph(LayersBase *base)
	:ServiceForLayers(base),QThread(base->GetMainWidget())
{
	CamBuffer=NULL;
	TotalCameraNumb=0;
	Terminated=false;
}

CaptureThreadForRealtimeGraph::~CaptureThreadForRealtimeGraph(void)
{
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			delete	CamBuffer[cam];
		}
		delete	[]CamBuffer;
	}
	CamBuffer=NULL;
}


void	CaptureThreadForRealtimeGraph::Initialize(void)
{
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			delete	CamBuffer[cam];
		}
		delete	[]CamBuffer;
	}
	TotalCameraNumb=GetParamGlobal()->TotalCameraNumb;
	CamBuffer=new TmpBufferPerCam*[TotalCameraNumb];
	for(int cam=0;cam<TotalCameraNumb;cam++){
		CamBuffer[cam]=new TmpBufferPerCam(cam,GetLayersBase());
	}
}

void	CaptureThreadForRealtimeGraph::StartRepeatableCapture(void)
{
	if(isRunning ()==false){
		AllocMemory();
		start();
	}
}

void	CaptureThreadForRealtimeGraph::StopRepeatableCapture(void)
{
	if(isRunning ()==true){
		Terminated=false;
		wait();
		for(int cam=0;cam<TotalCameraNumb;cam++){
			CamBuffer[cam]->RestoreCamInfo();
		}
	}
}

void CaptureThreadForRealtimeGraph::run ()
{
	while(Terminated==false){
		StartCapture();
		while(Terminated==false){
			int	CamStatus =GetStatus();
			if((CamStatus & BitCamError)!=0){
				emit	CamErrorOccurs(CamStatus);
				return;
			}
			if(CamStatus!=0){
				break;
			}
		}
		GetImage();
	}
}

void	CaptureThreadForRealtimeGraph::AllocMemory(void)
{
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			CamBuffer[cam]->Allocate();
		}
	}			
}
void	CaptureThreadForRealtimeGraph::StartCapture(void)
{
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			CamBuffer[cam]->StartCapture();
		}
	}
}
int		CaptureThreadForRealtimeGraph::GetStatus(void)
{
	int	Status=0;
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			Status |=CamBuffer[cam]->GetStatus();
		}
		return Status;
	}
	return -1;
}
void	CaptureThreadForRealtimeGraph::GetImage(void)
{
	if(CamBuffer!=NULL){
		for(int cam=0;cam<TotalCameraNumb;cam++){
			CamBuffer[cam]->GetImage();
		}
	}
}
