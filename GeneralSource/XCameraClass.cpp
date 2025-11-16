/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCameraClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <QtGui>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QProgressBar>
#include <QSqlDatabase>
#include "XIntClass.h"
#include "XCameraClass.h"
#include "XCameraHandle.h"
#include "XCameraInterfaceDLL.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XErrorMessage.h"
#include "swap.h"
#include "XLogOut.h"
#include "Regulus64System.h"


const	int		ExeSleepTimeMilisec=20;

ThreadSoftBuffer::ThreadSoftBuffer(LayersBase *base ,CameraInterface *Handle ,QObject *parent)
	:QThread(parent),ServiceForLayers(base),CameraHandle(Handle)
{
	CamStatus=0;
	FinishMode=false;
}

void ThreadSoftBuffer::run ()
{
	while(GetLayersBase()->GetOnTerminating()==false && FinishMode==false){
		msleep(ExeSleepTimeMilisec);
		if(GetParamGlobal()->CameraSoftBuffer!=0){
			if((CamStatus=CameraHandle->GetStatusWithoutBuffer())==0){
				CameraHandle->CaptureToBuffer();
				GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"ThreadSoftBuffer:Captured",CameraHandle->GetStockedCountInBuffer());
				if(GetParamGlobal()->CaptureInBackground==true){
					CameraHandle->PrepareCapture();
					CameraHandle->StartCapture();
				}
			}
		}
	}
}

void	ThreadSoftBuffer::ClearBuffer(void)
{
	int				RPointBuffer;
	int				WPointBuffer;
}

//======================================================================

bool	CameraInterface::InitialDLL(const QString &dllfilename,bool ModeShowInfo,int32 &ErrorCode)
{
	QDir::setCurrent(GetLayersBase()->GetSystemPath());
	QFileInfo fi(dllfilename);
	if(fi.suffix().isEmpty()==true){
		LibraryFileName=dllfilename+QString(".")+GetDynamicFileExt();
	}
	else{
		LibraryFileName=dllfilename;
	}
	if(ModeShowInfo==true){
		GetLayersBase()->TestLoadDLL(LibraryFileName);
	}
	if(QLibrary::isLibrary(LibraryFileName)==true){
		if(LoadDLL(LibraryFileName,ErrorCode)==false){
			return(false);
		}
		if(IsCameraDLL()==true){
			ErrorCode=Error_Nothing;
			return(true);			
		}
	}
	ErrorCode=Error_CameraDLL;
	return(false);
}

bool	CameraInterface::LoadDLL(const QString &filename ,int32 &ErrorCode)
{
	CamFileName=filename;
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		::SendErrorMessage(QString(/**/"Can not load Camera library : ")+filename);
		return(false);
	}

	DLL_GetDLLType		=(WORD	(*)(void))DllLib.resolve("DLL_GetDLLType");
	if(DLL_GetDLLType==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_GetDLLType;
		return(false);
	}
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_GetName;
		return(false);
	}
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");

	DLL_GetVersion		=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLL_GetVersion==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_GetVersion;
		return(false);
	}
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_Camera_NoFunc_DLL_GetSystemVersion;
		return false;
	}
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	DLL_GetCameraCount	=(int (*)(LayersBase *base, const QString &CameraParameter))DllLib.resolve("DLL_GetCameraCount");
	DLL_Initial			=(CameraHandle *(*)(int N,LayersBase *base,CameraReqInfo &caminfo,const QString &CameraParameter))DllLib.resolve("DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_Initial;
		return(false);
	}
	DLL_GetCameraDLLInfo=(bool (*)(CameraHandle *handle ,CameraDLLInfo &CamInfo))DllLib.resolve("DLL_GetCameraDLLInfo");
	DLL_ChangeInfo		=(bool (*)(CameraHandle *handle ,CameraReqInfo &caminfo))DllLib.resolve("DLL_ChangeInfo");

	DLL_Close			=(bool (*)(CameraHandle *handle))DllLib.resolve("DLL_Close");
	if(DLL_Close==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_Close;
		return(false);
	}
	DLL_ResetToDefault	=(bool (*)(CameraHandle *handle))DllLib.resolve("DLL_ResetToDefault");
	DLL_Load			=(bool (*)(CameraHandle *handle ,QIODevice &str))DllLib.resolve("DLL_Load");
	if(DLL_Load==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_Load;
		return(false);
	}
	DLL_Save			=(bool (*)(CameraHandle *handle,QIODevice &str))DllLib.resolve("DLL_Save");
	if(DLL_Save==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_Save;
		return(false);
	}
	DLL_ShowSetting		=(bool (*)(CameraHandle *handle, QWidget *parent))DllLib.resolve("DLL_ShowSetting");
	if(DLL_ShowSetting==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_ShowSetting;
		return(false);
	}
	DLL_PrepareCapture	=(bool (*)(CameraHandle *handle,CameraScanInfo *Info))DllLib.resolve("DLL_PrepareCapture");
	if(DLL_PrepareCapture==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_PrepareCapture;
		return(false);
	}
	DLL_StartCapture	=(bool (*)(CameraHandle *handle,CameraScanInfo *Info))DllLib.resolve("DLL_StartCapture");
	if(DLL_StartCapture==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_StartCapture;
		return(false);
	}
	DLL_HaltCapture		=(bool (*)(CameraHandle *handle))DllLib.resolve("DLL_HaltCapture");
	if(DLL_HaltCapture==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_HaltCapture;
		return(false);
	}
	DLL_SetAutoRepeat	=(bool (*)(CameraHandle *handle,bool RepeatON))DllLib.resolve("DLL_SetAutoRepeat");

	DLL_GetStatus		=(int  (*)(CameraHandle *handle,CameraScanInfo *Info))DllLib.resolve("DLL_GetStatus");
	if(DLL_GetStatus==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_GetStatus;
		return(false);
	}
	DLL_GetCurrentLineCount	=(int  (*)(CameraHandle *handle))DllLib.resolve("DLL_GetCurrentLineCount");

	DLL_ClearError		=(bool (*)(CameraHandle *handle))DllLib.resolve("DLL_ClearError");
	if(DLL_ClearError==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_ClearError;
		return(false);
	}
	DLL_GetImage		=(bool (*)(CameraHandle *handle ,ImageBuffer *Buffer[] ,int BufferDimCounts,CameraScanInfo *Info))DllLib.resolve("DLL_GetImage");
	DLL_GetImageTR		=(bool (*)(CameraHandle *handle ,ImageBuffer *Buffer[] ,ImageBuffer *TRBuffer[] ,int BufferDimCounts,CameraScanInfo *Info))DllLib.resolve("DLL_GetImageTR");
	if(DLL_GetImage==NULL && DLL_GetImageTR==NULL){
		ErrorCode=Error_Camera_NoFunc_DLL_GetImage;
		return(false);
	}
	DLL_TransmitDirectly	=(void (*)(CameraHandle *handle ,GUIDirectMessage *packet))DllLib.resolve("DLL_TransmitDirectly");
	DLL_SpecifiedDirectly	=(void (*)(CameraHandle *handle ,SpecifiedBroadcaster *v))DllLib.resolve("DLL_SpecifiedDirectly");

	DLL_StartCaptureContinuously	=(bool (*)(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info))DllLib.resolve("DLL_StartCaptureContinuously");
	DLL_StopCaptureContinuously		=(bool (*)(CameraHandle *handle))DllLib.resolve("DLL_StopCaptureContinuously");
	DLL_SetQuickProperty			=(bool (*)(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue))DllLib.resolve("DLL_SetQuickProperty");
	DLL_LoopOnIdle					=(void (*)(CameraHandle *handle))DllLib.resolve("DLL_LoopOnIdle");

	DLL_ExecuteInitialAfterEdit	=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteInitialAfterEdit");
	DLL_ExecuteStartByInspection=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteStartByInspection");
	DLL_ExecuteCaptured			=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base,ListPhasePageLayerPack &CapturedList))DllLib.resolve("DLL_ExecuteCaptured");
	DLL_ExecutePreAlignment		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecutePreAlignment");
	DLL_ExecuteAlignment		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteAlignment");
	DLL_ExecutePreProcessing	=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecutePreProcessing");
	DLL_ExecuteProcessing		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteProcessing");
	DLL_ExecuteProcessingRevived=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteProcessingRevived");
	DLL_ExecutePostProcessing	=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecutePostProcessing");
	DLL_ExecutePreScanning		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecutePreScanning");
	DLL_ExecuteScanning			=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteScanning");
	DLL_ExecutePostScanning		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecutePostScanning");
	DLL_ExecuteManageResult		=(ExeResult	(*)(CameraHandle *handle ,int ExeID ,LayersBase *base))DllLib.resolve("DLL_ExecuteManageResult");



	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	return(true);
}

bool	CameraInterface::IsCameraDLL(void)
{
	if(DLL_GetVersion!=NULL){
		const int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLCameraMode){
			return(true);
		}
	}
	return(false);
}

bool	CameraInterface::CheckCameraDLL(void)
{
	if(DLL_GetImage!=NULL || DLL_GetImageTR!=NULL)
		return true;
	return false;
}
void	CameraInterface::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
void	CameraInterface::InitialPrepare(void)
{
	if(Handle!=NULL){
		Handle->InitialPrepare();
	}
}
void	CameraInterface::Prepare(void)
{
	if(Handle!=NULL){
		Handle->Prepare();
	}
}
void	CameraInterface::AfterPrepare(void)
{
	if(Handle!=NULL){
		Handle->AfterPrepare();
	}
}
void	CameraInterface::ReadyParam(void)
{
	if(Handle!=NULL){
		Handle->ReadyParam();
	}
}
void	CameraInterface::AfterStartSequence(void)
{
	if(Handle!=NULL){
		Handle->AfterStartSequence();
	}
}

//============================================================================================================


CameraInterface::CameraInterface(int _CamNo ,LayersBase *base)
:ServiceForLayers(base)
{
	CamNo=_CamNo;
	DLL_GetDLLType					=NULL;
	DLL_ChangeInfo					=NULL;
	DLL_GetExplain					=NULL;
	DLL_GetName						=NULL;
	DLL_GetVersion					=NULL;
	DLL_SetLanguage					=NULL;
	DLL_CheckCopyright				=NULL;
	DLL_AssociateComponent			=NULL;

	DLL_GetCameraCount				=NULL;
	DLL_Initial						=NULL;
	DLL_GetCameraDLLInfo			=NULL;
	DLL_Close						=NULL;
	DLL_ResetToDefault				=NULL;
	DLL_Load						=NULL;
	DLL_Save						=NULL;
	DLL_ShowSetting					=NULL;
	DLL_PrepareCapture				=NULL;
	DLL_StartCapture				=NULL;
	DLL_HaltCapture					=NULL;
	DLL_SetAutoRepeat				=NULL;
	DLL_GetStatus					=NULL;
	DLL_ClearError					=NULL;
	DLL_GetImage					=NULL;
	DLL_GetImageTR					=NULL;
	DLL_GetCurrentLineCount			=NULL;
	DLL_TransmitDirectly			=NULL;
	DLL_SpecifiedDirectly			=NULL;
	DLL_StartCaptureContinuously	=NULL;
	DLL_StopCaptureContinuously		=NULL;
	DLL_SetQuickProperty			=NULL;
	DLL_LoopOnIdle					=NULL;
	
	DLL_ExecuteInitialAfterEdit		=NULL;
	DLL_ExecuteStartByInspection	=NULL;
	DLL_ExecuteCaptured				=NULL;
	DLL_ExecutePreAlignment			=NULL;
	DLL_ExecuteAlignment			=NULL;
	DLL_ExecutePreProcessing		=NULL;
	DLL_ExecuteProcessing			=NULL;
	DLL_ExecuteProcessingRevived	=NULL;
	DLL_ExecutePostProcessing		=NULL;
	DLL_ExecutePreScanning			=NULL;
	DLL_ExecuteScanning				=NULL;
	DLL_ExecutePostScanning			=NULL;
	DLL_ExecuteManageResult			=NULL;

	Initialised	=false;
	Captured	=false;
	Handle=NULL;

	ScanInfo.ReverseRightLeft	=false;	
	ScanInfo.ReverseTopDown		=false;
	ScanInfo.FreeRun			=false;

	SoftBuffer					=NULL;
	AllocatedCountOfSoftBuffer	=0;
	AllocatedCountOfLayer		=0;
	RPointBuffer				=0;
	WPointBuffer				=0;
	StockedCountInBuffer		=0;
	CapThread					=NULL;
	CapturedCount				=0;

	MutexInDLL					=false;
}

CameraInterface::~CameraInterface(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;
	if(CapThread!=NULL){
		CapThread->FinishMode=true;
		CapThread->wait(1000);
		CapThread->deleteLater();
		CapThread=NULL;
	}

	if(Handle!=NULL && DLL_Close!=NULL){
		DLL_Close(Handle);
	}
	Handle=NULL;

	DLL_GetDLLType					=NULL;
	DLL_ChangeInfo					=NULL;
	DLL_GetExplain					=NULL;
	DLL_GetName						=NULL;
	DLL_GetVersion					=NULL;
	DLL_SetLanguage					=NULL;
	DLL_CheckCopyright				=NULL;
	DLL_AssociateComponent			=NULL;
	DLL_GetCameraCount				=NULL;
	DLL_Initial						=NULL;
	DLL_GetCameraDLLInfo			=NULL;
	DLL_Close						=NULL;
	DLL_Load						=NULL;
	DLL_Save						=NULL;
	DLL_ShowSetting					=NULL;
	DLL_PrepareCapture				=NULL;
	DLL_StartCapture				=NULL;
	DLL_HaltCapture					=NULL;
	DLL_SetAutoRepeat				=NULL;
	DLL_GetStatus					=NULL;
	DLL_ClearError					=NULL;
	DLL_GetImage					=NULL;
	DLL_GetImageTR					=NULL;
	DLL_GetCurrentLineCount			=NULL;
	DLL_TransmitDirectly			=NULL;
	DLL_SpecifiedDirectly			=NULL;
	DLL_StartCaptureContinuously	=NULL;
	DLL_StopCaptureContinuously		=NULL;
	DLL_SetQuickProperty			=NULL;
	DLL_LoopOnIdle					=NULL;
	
	DLL_ExecuteInitialAfterEdit		=NULL;
	DLL_ExecuteStartByInspection	=NULL;
	DLL_ExecuteCaptured				=NULL;
	DLL_ExecutePreAlignment			=NULL;
	DLL_ExecuteAlignment			=NULL;
	DLL_ExecutePreProcessing		=NULL;
	DLL_ExecuteProcessing			=NULL;
	DLL_ExecuteProcessingRevived	=NULL;
	DLL_ExecutePostProcessing		=NULL;
	DLL_ExecutePreScanning			=NULL;
	DLL_ExecuteScanning				=NULL;
	DLL_ExecutePostScanning			=NULL;
	DLL_ExecuteManageResult			=NULL;

	if(SoftBuffer!=NULL){
		for(int i=0;i<AllocatedCountOfSoftBuffer;i++){
			if(CameraSoftBufferType==0){
				for(int L=0;L<AllocatedCountOfLayer;L++){
					delete	SoftBuffer[i][L];
				}
			}
			delete	[]SoftBuffer[i];
		}
		delete	[]SoftBuffer;
	}
	ReEntrantDLL=false;
}

static	bool	IsIncludeCam(const QString &AllocationStr ,int CamNo)
{
	if(AllocationStr.isEmpty()==true)
		return true;
	QStringList	List=AllocationStr.split(',');
	for(int i=0;i<List.count();i++){
		bool	ok;
		int	d=List[i].toInt(&ok);
		if(ok==true && CamNo==d){
			return true;
		}
	}
	return false;
}

bool	CameraInterface::Initial(ParamGlobal *param ,bool ModeShowInfo,int32 &ErrorCode)
{
	bool	Ret=false;
	QString	CameraParameter;
	if(Initialised==false){
		if(IsIncludeCam(param->CameraAllocation,CamNo)==true){
			CameraParameter=param->CameraParameter;
			if(param->CameraDLL_FileName.isEmpty()==false){
				Ret=InitialDLL(param->CameraDLL_FileName ,ModeShowInfo,ErrorCode);
			}
		}
		else if(param->CameraDLL_FileName2.isEmpty()==false && IsIncludeCam(param->CameraAllocation2,CamNo)==true){
			CameraParameter=param->CameraParameter2;
			if(param->CameraDLL_FileName2.isEmpty()==false){
				Ret=InitialDLL(param->CameraDLL_FileName2 ,ModeShowInfo,ErrorCode);
			}
		}
		else if(param->CameraDLL_FileName3.isEmpty()==false && IsIncludeCam(param->CameraAllocation3,CamNo)==true){
			CameraParameter=param->CameraParameter3;
			if(param->CameraDLL_FileName3.isEmpty()==false){
				Ret=InitialDLL(param->CameraDLL_FileName3 ,ModeShowInfo,ErrorCode);
			}
		}
		else if(param->CameraDLL_FileName4.isEmpty()==false && IsIncludeCam(param->CameraAllocation4,CamNo)==true){
			CameraParameter=param->CameraParameter4;
			if(param->CameraDLL_FileName4.isEmpty()==false){
				Ret=InitialDLL(param->CameraDLL_FileName4 ,ModeShowInfo,ErrorCode);
			}
		}
		Initialised=true;
	}
	if(Ret==true){
		if(InitialLater(param ,CameraParameter,ErrorCode)==false){
			return false;
		}
		if(DLL_GetCameraDLLInfo!=NULL){
			CameraDLLInfo	CInfo;
			if(DLL_GetCameraDLLInfo(Handle,CInfo)==true){
				MutexInDLL=CInfo.MutexInDLL;
			}
		}
	}
	return Ret;
}

bool	CameraInterface::InitialLater(ParamGlobal *param ,const QString &CameraParameter ,int32 &ErrorCode)
{
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return false;
		}
	}

	CamInfo.XLen		=param->DotPerLine;
	CamInfo.YLen		=param->MaxLines;
	CamInfo.PageNumb	=param->PageNumb;
	CamInfo.LayerNumber	=param->LayerNumb;
	CamInfo.CamSimultaneousLayerCount	=param->LayerNumb;
	CamInfo.CamMinimumDotPerLine		=param->DotPerLine;
	CamInfo.CamMaximumDotPerLine		=param->DotPerLine;
	CamInfo.CamMinimumLines				=param->MaxLines;
	CamInfo.CamMaximumLines				=param->MaxLines;
	CamInfo.ErrorCode					=0;
	memset(CamInfo.ErrorMessage,0,sizeof(CamInfo.ErrorMessage));

	ScanInfo.CurrentScanNumber=0;
	ScanInfo.ScanMastered=true;
	GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),ScanInfo.StrategicList);

	bool	Ret=false;
	if(DLL_Initial!=NULL){
		Handle=DLL_Initial(CamNo,GetLayersBase(),CamInfo,CameraParameter);
		if(Handle!=NULL){
			connect(Handle,SIGNAL(CameraHandleSignalCaptured()),this,SLOT(SlotCaptured()));
			Ret=true;
		}
		else{
			ErrorCode=CamInfo.ErrorCode;
			//::SendErrorMessage(/**/"Camera DLL_Initial return NULL");
			return false;
		}
	}
	else{
		ErrorCode=-1;
		//::SendErrorMessage(/**/"Camera , No DLL_Initial is loaded");
		return false;
	}
	if(param->CameraSoftBuffer!=0){
		CameraSoftBufferType		=param->CameraSoftBufferType;
		if(CameraSoftBufferType==0){
			AllocatedCountOfSoftBuffer	=param->CameraSoftBuffer;
			AllocatedCountOfLayer		=param->GetLayerNumb(0);
			SoftBuffer	=new ImageBuffer**[AllocatedCountOfSoftBuffer];
			for(int i=0;i<AllocatedCountOfSoftBuffer;i++){
				SoftBuffer[i]=new ImageBuffer*[AllocatedCountOfLayer];
				for(int L=0;L<AllocatedCountOfLayer;L++){
					SoftBuffer[i][L]=new ImageBuffer(ImageBufferOther,param->DotPerLine,param->MaxLines);
				}
			}
		}
		else if(CameraSoftBufferType==1){
			AllocatedCountOfSoftBuffer	=param->GetPageNumb();
			AllocatedCountOfLayer		=param->GetLayerNumb(0);
			SoftBuffer	=new ImageBuffer**[AllocatedCountOfSoftBuffer];
			for(int i=0;i<AllocatedCountOfSoftBuffer;i++){
				SoftBuffer[i]=new ImageBuffer*[AllocatedCountOfLayer];
				for(int L=0;L<AllocatedCountOfLayer;L++){
					SoftBuffer[i][L]=&GetLayersBase()->GetPageDataPhase(0)->GetPageData(i)->GetLayerData(L)->GetTargetBuff();
				}
			}
		}
		else if(CameraSoftBufferType==2){
			AllocatedCountOfSoftBuffer	=param->GetPageNumb();
			AllocatedCountOfLayer		=param->GetLayerNumb(0);
			SoftBuffer	=new ImageBuffer**[AllocatedCountOfSoftBuffer];
			for(int i=0;i<AllocatedCountOfSoftBuffer;i++){
				SoftBuffer[i]=new ImageBuffer*[AllocatedCountOfLayer];
				for(int L=0;L<AllocatedCountOfLayer;L++){
					SoftBuffer[i][L]=&GetLayersBase()->GetPageDataPhase(0)->GetPageData(i)->GetLayerData(L)->GetMasterBuff();
				}
			}
		}
		CapThread	=new ThreadSoftBuffer(GetLayersBase(),this,GetLayersBase()->GetMainWidget());
		CapThread->start();
	}
	if(Handle==NULL){
		ErrorCode=Error_Camera_DLL_InitialError;
		Ret=false;
	}
	return Ret;
}
bool	CameraInterface::ChangeInfo(int XLen ,int YLen, int LayerCount ,int PageNumb,CameraReqInfoAnyData *anydata)
{
	if(DLL_ChangeInfo!=NULL){
		if(MutexExeCam.tryLock()==true){
			LastScanInfo=ScanInfo;
			CamInfo.XLen=XLen;
			CamInfo.YLen=YLen;
			CamInfo.LayerNumber=LayerCount;
			CamInfo.PageNumb=PageNumb;
			CamInfo.CamSimultaneousLayerCount	=LayerCount;
			CamInfo.CamMinimumDotPerLine		=0;
			CamInfo.CamMaximumDotPerLine		=GetDotPerLine(PageNumb);
			CamInfo.CamMinimumLines				=0;
			CamInfo.CamMaximumLines				=GetMaxLines(PageNumb);
			CamInfo.AnyData						=anydata;
			const bool	ret=DLL_ChangeInfo(Handle,CamInfo);
			MutexExeCam.unlock();
			return ret;
		}
	}
	return false;
}

bool	CameraInterface::RestoreCamInfo(void)
{
	ScanInfo=LastScanInfo;
	if(DLL_ChangeInfo!=NULL){
		if(MutexExeCam.tryLock()==true){
			const bool	ret=DLL_ChangeInfo(Handle ,CamInfo);
			MutexExeCam.unlock();
			return ret;
		}
	}
	return false;
}
bool	CameraInterface::ResetToDefault(void)
{
	if(DLL_ResetToDefault!=NULL){
		if(MutexExeCam.tryLock()==true){
			const bool	ret=DLL_ResetToDefault(Handle);
			MutexExeCam.unlock();
			return ret;
		}
	}
	return false;
}

bool	CameraInterface::SetLanguageCode(int LanguageCode)
{
	if(DLL_SetLanguage!=NULL){
		if(MutexExeCam.tryLock()==true){
			DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
			MutexExeCam.unlock();
		}
	}
	return true;
}
bool	CameraInterface::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return Handle->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}
bool	CameraInterface::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	return Handle->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
}
bool	CameraInterface::ReallocateMasterCount(int CountMaster)
{
	return Handle->ReallocateMasterCount(CountMaster);
}
bool	CameraInterface::Realloc(ParamGlobal *param ,int32 &ErrorCode)
{
	if(Initialised==true){
		IntList PageList;
		GetParamGlobal()->GetPageListFromCameraNo(CamNo,PageList);
		int	TmpDotPerLine=0;
		int	TmpMaxLines=0;
		int	TmpMaxLayerNumb=0;
		for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
			const int	Page=p->GetValue();
			TmpDotPerLine	=max(TmpDotPerLine	,GetLayersBase()->GetDotPerLine(Page));
			TmpMaxLines		=max(TmpMaxLines	,GetLayersBase()->GetMaxLines(Page));
			TmpMaxLayerNumb	=max(TmpMaxLayerNumb,GetLayersBase()->GetLayerNumb(Page));
		}
		if(ChangeInfo(TmpDotPerLine ,TmpMaxLines, TmpMaxLayerNumb, param->GetPageNumb())==true){
			return true;
		}
		else{
			return false;
		}
	}
	if(DLL_ChangeInfo!=NULL){
		CameraReqInfo RCmd;
		RCmd.XLen		=param->DotPerLine;			//Dot counts of X direction
		RCmd.YLen		=param->MaxLines;			//Dot counts of Y direction
		RCmd.LayerNumber=param->LayerNumb;	//Layer counts of simultanious caption
		RCmd.PageNumb	=param->TotalCameraNumb;		//Local page count

		if(MutexExeCam.tryLock()==true){
			const bool	Ret=DLL_ChangeInfo(Handle ,RCmd);
			MutexExeCam.unlock();
			return Ret;
		}
		return false;
	}
	else{
		if(Handle!=NULL && DLL_Close!=NULL){
			if(MutexExeCam.tryLock()==true){
				DLL_Close(Handle);
				MutexExeCam.unlock();
			}
		}
		return Initial(param ,false,ErrorCode);
	}
}

bool	CameraInterface::InsertPage(int IndexPage)	//Create page before Indexed page
{
	if(Initialised==true){
		if(ChangeInfo(GetDotPerLine(IndexPage)
					 ,GetMaxLines(IndexPage)
					 ,GetLayerNumb(IndexPage)
					 , GetPageNumb()+1)==true){
			return true;
		}
		else{
			return false;
		}
	}
	if(DLL_ChangeInfo!=NULL){
		CameraReqInfo RCmd;
		RCmd.XLen		=GetDotPerLine(IndexPage);	//Dot counts of X direction
		RCmd.YLen		=GetMaxLines(IndexPage);	//Dot counts of Y direction
		RCmd.LayerNumber=GetLayerNumb(IndexPage);	//Layer counts of simultanious caption
		RCmd.PageNumb	= GetPageNumb()+1;			//Local page count

		if(MutexExeCam.tryLock()==true){
			const bool	Ret=DLL_ChangeInfo(Handle ,RCmd);
			MutexExeCam.unlock();
			return Ret;
		}
		return false;
	}
	else{
		if(Handle!=NULL && DLL_Close!=NULL){
			if(MutexExeCam.tryLock()==true){
				DLL_Close(Handle);
				MutexExeCam.unlock();
			}
		}
	}
	return true;
}
bool	CameraInterface::RemovePage(int IndexPage)
{
	if(Initialised==true){
		if(ChangeInfo(GetDotPerLine(IndexPage)
					 ,GetMaxLines(IndexPage)
					 ,GetLayerNumb(IndexPage)
					 , GetPageNumb()-1)==true){
			return true;
		}
		else{
			return false;
		}
	}
	if(DLL_ChangeInfo!=NULL){
		CameraReqInfo RCmd;
		RCmd.XLen		=GetDotPerLine(IndexPage);	//Dot counts of X direction
		RCmd.YLen		=GetMaxLines(IndexPage);	//Dot counts of Y direction
		RCmd.LayerNumber=GetLayerNumb(IndexPage);	//Layer counts of simultanious caption
		RCmd.PageNumb	= GetPageNumb()-1;			//Local page count

		if(MutexExeCam.tryLock()==true){
			const bool	Ret=DLL_ChangeInfo(Handle ,RCmd);
			MutexExeCam.unlock();
			return Ret;
		}
		return false;
	}
	else{
		if(Handle!=NULL && DLL_Close!=NULL){
			if(MutexExeCam.tryLock()==true){
				DLL_Close(Handle);
				MutexExeCam.unlock();
			}
		}
	}
	return true;
}

bool	CameraInterface::ShouldRealloc(const ParamGlobal *param )
{
	if(CamInfo.XLen!=param->DotPerLine
	|| CamInfo.YLen!=param->MaxLines
	|| CamInfo.LayerNumber!=param->LayerNumb
	|| CamInfo.PageNumb!=param->PageNumb){
		bool	Ret=ChangeInfo(param->DotPerLine ,param->MaxLines, param->LayerNumb, param->PageNumb);
		if(Ret==false){
			return true;
		}
	}
	return false;
}
bool	CameraInterface::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"CameraDLL",/**/"",CamFileName);
}

void	CameraInterface::TransmitDirectly(GUIDirectMessage *packet)
{
	if(DLL_TransmitDirectly!=NULL){
		//MutexExeCam.lock();
		DLL_TransmitDirectly(Handle,packet);
		//MutexExeCam.unlock();
	}
}

void	CameraInterface::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(DLL_SpecifiedDirectly!=NULL){
		if(MutexExeCam.tryLock()==true){
			DLL_SpecifiedDirectly(Handle,v);
			MutexExeCam.unlock();
		}
	}
}
bool	CameraInterface::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	bool	Ret=false;
	if(DLL_SetQuickProperty!=NULL){
		if(MutexExeCam.tryLock()==true){
			Ret=DLL_SetQuickProperty(Handle,Attr,RelativeValue);
			MutexExeCam.unlock();
		}
	}
	return Ret;
}

bool	CameraInterface::Load(QIODevice &str)
{
	if(DLL_Load!=NULL){
		return(DLL_Load(Handle,str));
	}
	return(false);
}
bool	CameraInterface::Save(QIODevice &str)
{
	if(DLL_Save!=NULL){
		return(DLL_Save(Handle,str));
	}
	return(false);
}

bool	CameraInterface::ShowSetting(QWidget *parent)
{
	if(DLL_ShowSetting!=NULL){
		return(DLL_ShowSetting(Handle, parent));
	}
	return(false);
}

bool	CameraInterface::PrepareCapture(void)
{
	if(DLL_PrepareCapture!=NULL){
		MutexExeCam.lock();
		const bool	Ret=DLL_PrepareCapture(Handle,&ScanInfo);
		MutexExeCam.unlock();
		return Ret;
	}
	return(false);
}
bool	CameraInterface::StartCapture(void)
{
	if(DLL_StartCapture!=NULL){
		MutexExeCam.lock();
		const bool	Ret=DLL_StartCapture(Handle,&ScanInfo);
		MutexExeCam.unlock();
		if(Ret==true){
			Captured=false;
		}
		return Ret;
	}
	return(false);
}

bool	CameraInterface::HaltCapture(void)
{
	if(DLL_HaltCapture!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_HaltCapture(Handle);
		MutexExeCam.unlock();

		if(SoftBuffer!=NULL){
			MutexStockedCounter.lock();
			StockedCountInBuffer=0;
			MutexStockedCounter.unlock();
			WPointBuffer=RPointBuffer=0;
		}
		return Ret;
	}
	return(false);
}
bool	CameraInterface::SetAutoRepeat(bool RepeatON)
{
	if(DLL_SetAutoRepeat!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_SetAutoRepeat(Handle,RepeatON);
		MutexExeCam.unlock();
		return Ret;
	}
	return(false);
}

int		CameraInterface::GetStatus(CameraInfoDetailBase **Info)
{
	if(Captured==true)
		return 0;

	int	MRet=-1;
	if(SoftBuffer==NULL){
		if(DLL_GetStatus!=NULL){
			MutexExeCam.lock();
			int	Ret=DLL_GetStatus(Handle,&ScanInfo);
			MutexExeCam.unlock();
			MRet=Ret & 0xFFFF7F;
			if(MRet==0){
				Captured=true;
			}
			if(Info!=NULL){
				*Info=ScanInfo.DetailResult;
			}
			return MRet;
		}
	}
	else{
		if(StockedCountInBuffer>0){
			Captured=true;
			return 0;
		}
		if((CapThread->CamStatus & BitCamError)!=0)
			return BitCamError;
		return 2;
	}
	
	return -1;
}

bool	CameraInterface::IsBufferFull(void)
{
	if(SoftBuffer==NULL){
		if(DLL_GetStatus!=NULL){
			MutexExeCam.lock();
			const int	Ret=DLL_GetStatus(Handle,&ScanInfo);
			MutexExeCam.unlock();
			if((Ret & 0x80)!=0){
				return true;
			}
		}
	}
	return false;
}

void	CameraInterface::LoopOnIdle(void)
{
	if(DLL_LoopOnIdle!=NULL){
		DLL_LoopOnIdle(Handle);
	}
}

int		CameraInterface::GetCurrentLineCount(void)
{
	if(DLL_GetCurrentLineCount!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_GetCurrentLineCount(Handle);
		MutexExeCam.unlock();
		return Ret;
	}
	return 0;
}


bool	CameraInterface::ClearError(void)
{
	if(DLL_ClearError!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_ClearError(Handle);
		MutexExeCam.unlock();
		return Ret;
	}
	return(false);
}

bool	CameraInterface::ClearBit(void)
{
	/*
	if(DLL_ClearBit!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_ClearBit(Handle);
		MutexExeCam.unlock();
		return Ret;
	}
	*/
	return(false);
}
bool	CameraInterface::IsTREffective(void)
{
	if(DLL_GetImageTR!=NULL && GetParamGlobal()->AllocateTargetTRBuff==true)
		return true;
	return false;
}

bool	CameraInterface::StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
	if(DLL_StartCaptureContinuously!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_StartCaptureContinuously(Handle,Buff,BufferDimCounts ,Info);
		MutexExeCam.unlock();
		return Ret;
	}
	return(false);
}

bool	CameraInterface::StopCaptureContinuously(void)
{
	if(DLL_StopCaptureContinuously!=NULL){
		MutexExeCam.lock();
		bool	Ret=DLL_StopCaptureContinuously(Handle);
		MutexExeCam.unlock();
		return Ret;
	}
	return(false);
}


bool	CameraInterface::GetImage(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)
{
	if(SoftBuffer==NULL){
		if(DLL_GetImage!=NULL || DLL_GetImageTR!=NULL){
			if(MutexInDLL==false){
				GetLayersBase()->LockRChangingDataStructure();
			}
			ScanInfo.ReverseRightLeft	=XReverse;
			ScanInfo.ReverseTopDown		=YReverse;
			GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),ScanInfo.StrategicList);
			bool	Ret;
			if(DLL_GetImage!=NULL){
				Ret=DLL_GetImage(Handle,Buffer ,BufferDimCounts,&ScanInfo);
			}
			else{
				ImageBuffer *TRBuffer[1000];
				for(int i=0;i<BufferDimCounts;i++){
					TRBuffer[i]=NULL;
				}
				Ret=DLL_GetImageTR(Handle,Buffer ,TRBuffer,BufferDimCounts,&ScanInfo);
			}
			XReverse	=ScanInfo.ReverseRightLeft;
			YReverse	=ScanInfo.ReverseTopDown;

			if(Ret==true){
				CapturedCount++;
			}
			if(MutexInDLL==false){
				GetLayersBase()->UnlockChangingDataStructure();
			}
			//CallFunc(Buffer ,BufferDimCounts,XReverse ,YReverse);
			return Ret;
			
		}
	}
	else{
		//if(GetLayersBase()->TryLockRChangingDataStructure()==true){

		if(MutexInDLL==false){
			GetLayersBase()->LockRChangingDataStructure();
		}

		MutexStockedCounter.lock();
		int	iStockedCountInBuffer=StockedCountInBuffer;
		MutexStockedCounter.unlock();

		if(CameraSoftBufferType==0){
			if(iStockedCountInBuffer>0){
				for(int L=0;L<AllocatedCountOfLayer;L++){
					*Buffer[L]=*SoftBuffer[RPointBuffer][L];
				}
				RPointBuffer++;
				if(RPointBuffer>=AllocatedCountOfSoftBuffer){
					RPointBuffer=0;
				}
				MutexStockedCounter.lock();
				StockedCountInBuffer--;
				MutexStockedCounter.unlock();
			}
		}
		else if(CameraSoftBufferType==1 || CameraSoftBufferType==2){
			if(iStockedCountInBuffer>=0){
				RPointBuffer++;
				if(RPointBuffer>=AllocatedCountOfSoftBuffer){
					RPointBuffer=0;
				}
				MutexStockedCounter.lock();
				StockedCountInBuffer--;
				MutexStockedCounter.unlock();
			}
		}
		CapturedCount++;
		if(MutexInDLL==false){
			GetLayersBase()->UnlockChangingDataStructure();
		}
		//CallFunc(Buffer ,BufferDimCounts,XReverse ,YReverse);
		return true;
	}
	
	return(false);
}


bool	CameraInterface::GetImage(ImageBuffer *Buffer[] ,ImageBuffer *TRBuffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)
{
	if(DLL_GetImageTR!=NULL){
		if(MutexInDLL==false){
			GetLayersBase()->LockRChangingDataStructure();
		}
		ScanInfo.ReverseRightLeft	=XReverse;
		ScanInfo.ReverseTopDown		=YReverse;
		GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),ScanInfo.StrategicList);
		const bool	Ret=DLL_GetImageTR(Handle,Buffer ,TRBuffer ,BufferDimCounts,&ScanInfo);
		XReverse	=ScanInfo.ReverseRightLeft;
		YReverse	=ScanInfo.ReverseTopDown;
		if(Ret==true){
			CapturedCount++;
			for(int i=0;i<BufferDimCounts;i++){
				TRBuffer[i]->SetFlagCaptured(true);
			}
		}
		if(MutexInDLL==false){
			GetLayersBase()->UnlockChangingDataStructure();
		}
		//CallFunc(Buffer ,BufferDimCounts,XReverse ,YReverse);

		return Ret;
	}
	else{
		if(MutexInDLL==false){
			GetLayersBase()->LockRChangingDataStructure();
		}
		ScanInfo.ReverseRightLeft	=XReverse;
		ScanInfo.ReverseTopDown		=YReverse;
		GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),ScanInfo.StrategicList);
		const bool	Ret=DLL_GetImage(Handle,Buffer ,BufferDimCounts,&ScanInfo);
		XReverse	=ScanInfo.ReverseRightLeft;
		YReverse	=ScanInfo.ReverseTopDown;
		if(Ret==true){
			CapturedCount++;
		}
		if(MutexInDLL==false){
			GetLayersBase()->UnlockChangingDataStructure();
		}
		//CallFunc(Buffer ,BufferDimCounts,XReverse ,YReverse);
		return Ret;
	}
	
	return(false);
}
void	CameraInterface::AddFuncCaptured(ListFuncAbstruct *f)
{
	ListFuncConatiner.AppendList(f);
}
void	CameraInterface::CallFunc(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)
{
	for(ListFuncAbstruct *a=ListFuncConatiner.GetFirst();a!=NULL;a=a->GetNext()){
		a->Execute(Buffer ,BufferDimCounts,XReverse ,YReverse);
	}
}

QString	CameraInterface::GetName(void)	const
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	CameraInterface::GetVersion(void)	const
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	CameraInterface::GetDLLType(void)	const
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	CameraInterface::GetCopyright(void)	const
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}

const QString	CameraInterface::GetExplain(void)	const
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

void	CameraInterface::SetScanMode_FreeRun(bool b)
{
	ScanInfo.FreeRun=b;
}


void	CameraInterface::GetExportFunctions(QStringList &Str)
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
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}

	if(DLL_GetCameraCount!=NULL){
		Str.append("DLL_GetCameraCount");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_GetCameraDLLInfo!=NULL){
		Str.append("DLL_GetCameraDLLInfo");
	}
	if(DLL_ResetToDefault!=NULL){
		Str.append("DLL_ResetToDefault");
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
	if(DLL_PrepareCapture!=NULL){
		Str.append("DLL_PrepareCapture");
	}
	if(DLL_StartCapture!=NULL){
		Str.append("DLL_StartCapture");
	}
	if(DLL_SetAutoRepeat!=NULL){
		Str.append("DLL_SetAutoRepeat");
	}
	if(DLL_HaltCapture!=NULL){
		Str.append("DLL_HaltCapture");
	}
	if(DLL_GetStatus!=NULL){
		Str.append("DLL_GetStatus");
	}
	if(DLL_GetCurrentLineCount!=NULL){
		Str.append("DLL_GetCurrentLineCount");
	}
	if(DLL_ClearError!=NULL){
		Str.append("DLL_ClearError");
	}
	if(DLL_GetImage!=NULL){
		Str.append("DLL_GetImage");
	}
	if(DLL_TransmitDirectly!=NULL){
		Str.append("DLL_TransmitDirectly");
	}
	if(DLL_SpecifiedDirectly!=NULL){
		Str.append("DLL_SpecifiedDirectly");
	}
	if(DLL_StartCaptureContinuously!=NULL){
		Str.append("DLL_StartCaptureContinuously");
	}
	if(DLL_StopCaptureContinuously!=NULL){
		Str.append("DLL_StopCaptureContinuously");
	}
	if(DLL_SetQuickProperty!=NULL){
		Str.append("DLL_SetQuickProperty");
	}
	if(DLL_LoopOnIdle!=NULL){
		Str.append("DLL_LoopOnIdle");
	}

	if(DLL_ExecuteInitialAfterEdit!=NULL){
		Str.append("DLL_ExecuteInitialAfterEdit");
	}
	if(DLL_ExecuteStartByInspection!=NULL){
		Str.append("DLL_ExecuteStartByInspection");
	}
	if(DLL_ExecuteCaptured!=NULL){
		Str.append("DLL_ExecuteCaptured");
	}
	if(DLL_ExecutePreAlignment!=NULL){
		Str.append("DLL_ExecutePreAlignment");
	}
	if(DLL_ExecuteAlignment!=NULL){
		Str.append("DLL_ExecuteAlignment");
	}
	if(DLL_ExecutePreProcessing!=NULL){
		Str.append("DLL_ExecutePreProcessing");
	}
	if(DLL_ExecuteProcessing!=NULL){
		Str.append("DLL_ExecuteProcessing");
	}
	if(DLL_ExecuteProcessingRevived!=NULL){
		Str.append("DLL_ExecuteProcessingRevived");
	}
	if(DLL_ExecutePostProcessing!=NULL){
		Str.append("DLL_ExecutePostProcessing");
	}
	if(DLL_ExecutePreScanning!=NULL){
		Str.append("DLL_ExecutePreScanning");
	}
	if(DLL_ExecuteScanning!=NULL){
		Str.append("DLL_ExecuteScanning");
	}
	if(DLL_ExecutePostScanning!=NULL){
		Str.append("DLL_ExecutePostScanning");
	}
	if(DLL_ExecuteManageResult!=NULL){
		Str.append("DLL_ExecuteManageResult");
	}
	DLLManager::GetExportFunctions(Str);
}

int		CameraInterface::GetStatusWithoutBuffer(void)
{
	if(DLL_GetStatus!=NULL){
		MutexExeCam.lock();
		int	Ret=DLL_GetStatus(Handle,&ScanInfo);
		MutexExeCam.unlock();
		return Ret & 0x7F;
	}
	return -1;
}
void	CameraInterface::CaptureToBuffer(void)
{
	if(DLL_GetImage!=NULL){
		GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),ScanInfo.StrategicList);
		bool	Ret=DLL_GetImage(Handle,SoftBuffer[WPointBuffer],AllocatedCountOfLayer,&ScanInfo);
		WPointBuffer++;
		if(WPointBuffer>=AllocatedCountOfSoftBuffer)
			WPointBuffer=0;
		MutexStockedCounter.lock();
		StockedCountInBuffer++;
		MutexStockedCounter.unlock();
	}
}
void	CameraInterface::ClearBuffer(void)
{
	MutexStockedCounter.lock();
	StockedCountInBuffer=0;
	MutexStockedCounter.unlock();

	WPointBuffer=0;
	RPointBuffer=0;
}

int		CameraInterface::GetCameraCount(QString &dllfilename,const QString &CameraParameter)
{
	QLibrary	MDllLib(dllfilename);

	if(MDllLib.load()==false){
		return(-1);
	}

	DLL_GetCameraCount	=(int (*)(LayersBase *base, const QString &CameraParameter))MDllLib.resolve("DLL_GetCameraCount");

	if(DLL_GetCameraCount!=NULL){
		return DLL_GetCameraCount(GetLayersBase(),CameraParameter);
	}
	return -1;
}

void	CameraInterface::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
	ScanInfo.CurrentScanNumber	=ScanNumber;
	ScanInfo.ScanMastered		=ScanMastered;
}
bool	CameraInterface::MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo)
{
	if(Handle!=NULL){
		return Handle->MakeExecuteInitialAfterEditInfo	(ExeID ,EInfo);
	}
	return false;
}
ExeResult	CameraInterface::ExecuteInitialAfterEdit	(int ExeID)
{
	if(DLL_ExecuteInitialAfterEdit!=NULL){
		return DLL_ExecuteInitialAfterEdit(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteStartByInspection	(int ExeID)
{
	if(DLL_ExecuteStartByInspection!=NULL){
		return DLL_ExecuteStartByInspection(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteCaptured(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	if(DLL_ExecuteCaptured!=NULL){
		return DLL_ExecuteCaptured(Handle,ExeID,GetLayersBase(),CapturedList);
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecutePreAlignment		(int ExeID)
{
	if(DLL_ExecutePreAlignment!=NULL){
		return DLL_ExecutePreAlignment(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteAlignment			(int ExeID)
{
	if(DLL_ExecuteAlignment!=NULL){
		return DLL_ExecuteAlignment(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecutePreProcessing		(int ExeID)
{
	if(DLL_ExecutePreProcessing!=NULL){
		return DLL_ExecutePreProcessing(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteProcessing			(int ExeID)
{
	if(DLL_ExecuteProcessing!=NULL){
		return DLL_ExecuteProcessing(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteProcessingRevived	(int ExeID)
{
	if(DLL_ExecuteProcessingRevived!=NULL){
		return DLL_ExecuteProcessingRevived(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecutePostProcessing		(int ExeID)
{
	if(DLL_ExecutePostProcessing!=NULL){
		return DLL_ExecutePostProcessing(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecutePreScanning			(int ExeID)
{
	if(DLL_ExecutePreScanning!=NULL){
		return DLL_ExecutePreScanning(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteScanning			(int ExeID)
{
	if(DLL_ExecuteScanning!=NULL){
		return DLL_ExecuteScanning(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecutePostScanning		(int ExeID)
{
	if(DLL_ExecutePostScanning!=NULL){
		return DLL_ExecutePostScanning(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
ExeResult	CameraInterface::ExecuteManageResult		(int ExeID)
{
	if(DLL_ExecuteManageResult!=NULL){
		return DLL_ExecuteManageResult(Handle,ExeID,GetLayersBase());
	}
	return _ER_NoFunc;
}
void	CameraInterface::SlotCaptured()
{
	emit	SignalCaptured();
}

//============================================================================
int	CameraClassPack::SearchAddDLL(int32 &ErrorCode)
{
	int	Ret=0;
	RemoveAll();

	QString	Path=GetLayersBase()->GetSystemPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+::GetSeparator();
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
				CameraClass	*a=new CameraClass(0,GetLayersBase());
				if(a->LoadDLL(FileName,ErrorCode)==true && a->IsCameraDLL()==true){
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

void	CameraClassPack::TransmitDirectly(GUIDirectMessage *packet)
{
	for(CameraClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

//=============================================================================================

CameraClass::CameraClass(int CamNo ,LayersBase *base)
:ServiceForLayers(base),Camera(new CameraInterface(CamNo,base))
{
	Copied=false;
}
CameraClass::CameraClass(const CameraClass &src)
:ServiceForLayers(src.GetLayersBase()),Camera(src.Camera)
{
	Copied=true;
}
CameraClass::~CameraClass(void)
{
	if(Copied==false){
		delete	Camera;
	}
	Camera=NULL;
}
CameraClass	&CameraClass::operator=(const CameraClass &src)
{
	return *this;
}
void	CameraClass::AssociateComponent	(ComponentListContainer &List)
{
	if(Camera==NULL)
		return;
	Camera->AssociateComponent(List);
}
bool	CameraClass::Initial(ParamGlobal *param ,int32 &ErrorCode)
{
	if(Camera==NULL)
		return false;
	bool	Ret=Camera->Initial(param ,param->ModeToShowLoadingDLLWindow,ErrorCode);
	if(Ret==true){
		connect(Camera,SIGNAL(SignalCaptured()),this,SLOT(SlotCaptured));
	}
	return Ret;
}
bool	CameraClass::InitialLater(ParamGlobal *param ,const QString &CameraParameter ,int32 &ErrorCode)
{
	if(Camera==NULL)
		return false;
	return Camera->InitialLater(param ,CameraParameter ,ErrorCode);
}
void	CameraClass::InitialPrepare(void)
{
	if(Camera!=NULL){
		Camera->InitialPrepare();
	}
}
void	CameraClass::Prepare(void)
{
	if(Camera!=NULL){
		Camera->Prepare();
	}
}
void	CameraClass::AfterPrepare(void)
{
	if(Camera!=NULL){
		Camera->AfterPrepare();
	}
}
void	CameraClass::ReadyParam(void)
{
	if(Camera!=NULL){
		Camera->ReadyParam();
	}
}
void	CameraClass::AfterStartSequence(void)
{
	if(Camera!=NULL){
		Camera->AfterStartSequence();
	}
}

bool	CameraClass::ChangeInfo(int XLen ,int YLen, int LayerCount ,int PageNumb,CameraReqInfoAnyData *anydata)
{
	if(Camera==NULL)
		return false;
	return Camera->ChangeInfo(XLen ,YLen, LayerCount ,PageNumb,anydata);
}

bool	CameraClass::IsCameraDLL(void)
{
	if(Camera==NULL)
		return false;
	return Camera->IsCameraDLL();
}
bool	CameraClass::LoadDLL(const QString &dllfilename,int32 &ErrorCode)
{
	if(Camera==NULL)
		return false;
	return Camera->LoadDLL(dllfilename ,ErrorCode);
}
bool	CameraClass::RestoreCamInfo(void)
{
	if(Camera==NULL)
		return false;
	return Camera->RestoreCamInfo();
}

bool	CameraClass::ResetToDefault(void)
{
	if(Camera==NULL)
		return false;
	return Camera->ResetToDefault();
}
bool	CameraClass::SetLanguageCode(int LanguageCode)
{
	if(Camera==NULL)
		return false;
	return Camera->SetLanguageCode(LanguageCode);
}
bool	CameraClass::CheckCameraDLL(void)
{
	if(Camera==NULL)
		return false;
	return Camera->CheckCameraDLL();
}
int		CameraClass::GetCameraCount(QString &dllfilename,const QString &CameraParameter)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetCameraCount(dllfilename,CameraParameter);
}

bool	CameraClass::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(Camera==NULL)
		return false;
	return Camera->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}
bool	CameraClass::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(Camera==NULL)
		return false;
	return Camera->Reallocate(newPhaseNumb ,newPageNumb ,newLayerNumb);
}
bool	CameraClass::ReallocateMasterCount(int CountMaster)
{
	if(Camera==NULL)
		return false;
	return Camera->ReallocateMasterCount(CountMaster);
}
bool	CameraClass::Realloc(ParamGlobal *param ,int32 &ErrorCode)
{
	if(Camera==NULL)
		return false;
	return Camera->Realloc(param ,ErrorCode);
}

bool	CameraClass::InsertPage(int IndexPage)	//Create page before Indexed page
{
	if(Camera==NULL)
		return false;
	return Camera->InsertPage(IndexPage);
}
bool	CameraClass::RemovePage(int IndexPage)
{
	if(Camera==NULL)
		return false;
	return Camera->RemovePage(IndexPage);
}
bool	CameraClass::ShouldRealloc(ParamGlobal *param )
{
	if(Camera==NULL)
		return false;
	return Camera->ShouldRealloc(param);
}

bool	CameraClass::Load(QIODevice &str)
{
	if(Camera==NULL)
		return false;
	return Camera->Load(str);
}
bool	CameraClass::Save(QIODevice &str)
{
	if(Camera==NULL)
		return false;
	return Camera->Save(str);
}

bool	CameraClass::ShowSetting(QWidget *parent)
{
	if(Camera==NULL)
		return false;
	return Camera->ShowSetting(parent);
}
bool	CameraClass::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	if(Camera==NULL)
		return false;
	return Camera->SetQuickProperty(Attr,RelativeValue);
}

bool	CameraClass::PrepareCapture(void)
{
	if(Camera==NULL)
		return false;
	return Camera->PrepareCapture();
}
bool	CameraClass::StartCapture(void)
{
	if(Camera==NULL)
		return false;
	return Camera->StartCapture();
}
bool	CameraClass::HaltCapture(void)
{
	if(Camera==NULL)
		return false;
	return Camera->HaltCapture();
}
bool	CameraClass::SetAutoRepeat(bool RepeatON)
{
	if(Camera==NULL)
		return false;
	return Camera->SetAutoRepeat(RepeatON);
}
int		CameraClass::GetStatus(CameraInfoDetailBase **Info)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetStatus(Info);
}
bool	CameraClass::IsBufferFull(void)
{
	if(Camera==NULL)
		return false;
	return Camera->IsBufferFull();
}
int		CameraClass::GetCurrentLineCount(void)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetCurrentLineCount();
}
bool	CameraClass::ClearError(void)
{
	if(Camera==NULL)
		return false;
	return Camera->ClearError();
}
bool	CameraClass::ClearBit(void)
{
	if(Camera==NULL)
		return false;
	return Camera->ClearBit();
}
bool	CameraClass::IsTREffective(void)
{
	if(Camera==NULL)
		return false;
	return Camera->IsTREffective();
}

bool	CameraClass::StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
	if(Camera==NULL)
		return false;
	return Camera->StartCaptureContinuously(Buff,BufferDimCounts ,Info);
}

bool	CameraClass::StopCaptureContinuously(void)
{
	if(Camera==NULL)
		return false;
	return Camera->StopCaptureContinuously();
}


bool	CameraClass::GetImage(ImageBuffer *Buffer[] ,int DimCounts,bool &XReverse ,bool &YReverse)
{
	if(Camera==NULL)
		return false;
	return Camera->GetImage(Buffer ,DimCounts,XReverse ,YReverse);
}
bool	CameraClass::GetImage(ImageBuffer *Buffer[] ,ImageBuffer *TRBuffer[] ,int DimCounts,bool &XReverse ,bool &YReverse)
{
	if(Camera==NULL)
		return false;
	return Camera->GetImage(Buffer ,TRBuffer,DimCounts,XReverse ,YReverse);
}

QString	CameraClass::GetLibraryFileName(void)	const
{
	if(Camera==NULL)
		return /**/"";
	return Camera->GetLibraryFileName();
}
QString	CameraClass::GetFileName(void)	const
{
	if(Camera==NULL)
		return /**/"";
	return Camera->GetFileName();
}
QString	CameraClass::GetCopyright(void)	const
{
	if(Camera==NULL)
		return /**/"";
	return Camera->GetCopyright();
}
QString	CameraClass::GetName(void)	const
{
	if(Camera==NULL)
		return /**/"";
	return Camera->GetName();
}
WORD	CameraClass::GetVersion(void)	const
{
	if(Camera==NULL)
		return 0;
	return Camera->GetVersion();
}
WORD	CameraClass::GetDLLType(void)	const
{
	if(Camera==NULL)
		return 0;
	return Camera->GetDLLType();
}
QString	CameraClass::GetExplain(void)	const
{
	if(Camera==NULL)
		return /**/"";
	return Camera->GetExplain();
}

void	CameraClass::SetScanMode_FreeRun(bool b)
{
	if(Camera==NULL)
		return;
	Camera->SetScanMode_FreeRun(b);
}
int		CameraClass::GetStatusWithoutBuffer(void)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetStatusWithoutBuffer();
}

void	CameraClass::CaptureToBuffer(void)
{
	if(Camera==NULL)
		return;
	Camera->CaptureToBuffer();
}
int		CameraClass::GetStockedCountInBuffer(void)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetStockedCountInBuffer();
}
void	CameraClass::ClearBuffer(void)
{
	if(Camera==NULL)
		return;
	Camera->ClearBuffer();
}
void	CameraClass::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
	if(Camera==NULL)
		return;
	Camera->SetScanInfo(ScanNumber ,ScanMastered);
}
void	CameraClass::GetExportFunctions(QStringList &Str)
{
	if(Camera==NULL)
		return;
	Camera->GetExportFunctions(Str);
}
void	CameraClass::TransmitDirectly(GUIDirectMessage *packet)
{
	if(Camera==NULL)
		return;
	Camera->TransmitDirectly(packet);
}
void	CameraClass::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(Camera==NULL)
		return;
	Camera->SpecifiedDirectly(v);
}
int		CameraClass::GetCamNo(void)	const
{
	if(Camera==NULL)
		return -1;
	return Camera->GetCamNo();
}
void	CameraClass::SetCamNo(int n)
{
	if(Camera==NULL)
		return;
	Camera->SetCamNo(n);
}
void	*CameraClass::GetHandle(void)
{
	if(Camera==NULL)
		return NULL;
	return Camera->GetHandle();
}
void	CameraClass::SetCapturedCount(int n)
{
	if(Camera==NULL)
		return;
	Camera->SetCapturedCount(n);
}
int		CameraClass::GetCapturedCount(void)
{
	if(Camera==NULL)
		return 0;
	return Camera->GetCapturedCount();
}
bool	CameraClass::GetCaptured(void)
{
	if(Camera==NULL)
		return false;
	return Camera->GetCaptured();
}
void	CameraClass::LoopOnIdle(void)
{
	if(Camera==NULL)
		return;
	Camera->LoopOnIdle();
}

bool	CameraClass::MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->MakeExecuteInitialAfterEditInfo(ExeID,EInfo);
}

ExeResult	CameraClass::ExecuteInitialAfterEdit	(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteInitialAfterEdit(ExeID);
}
ExeResult	CameraClass::ExecuteStartByInspection(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteStartByInspection(ExeID);
}
ExeResult	CameraClass::ExecuteCaptured(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteCaptured(ExeID,CapturedList);
}
ExeResult	CameraClass::ExecutePreAlignment		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecutePreAlignment(ExeID);
}
ExeResult	CameraClass::ExecuteAlignment		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteAlignment(ExeID);
}
ExeResult	CameraClass::ExecutePreProcessing	(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecutePreProcessing(ExeID);
}
ExeResult	CameraClass::ExecuteProcessing		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteProcessing(ExeID);
}
ExeResult	CameraClass::ExecuteProcessingRevived(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteProcessingRevived(ExeID);
}
ExeResult	CameraClass::ExecutePostProcessing	(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecutePostProcessing(ExeID);
}
ExeResult	CameraClass::ExecutePreScanning		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecutePreScanning(ExeID);
}
ExeResult	CameraClass::ExecuteScanning			(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteScanning(ExeID);
}
ExeResult	CameraClass::ExecutePostScanning		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecutePostScanning(ExeID);
}
ExeResult	CameraClass::ExecuteManageResult		(int ExeID)
{
	if(Camera==NULL)
		return _ER_false;
	return Camera->ExecuteManageResult(ExeID);
}


void	CameraClass::AddFuncCaptured(ListFuncAbstruct *f)
{
	if(Camera==NULL)
		return;
	Camera->AddFuncCaptured(f);
}
void	CameraClass::CallFunc(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)
{
	if(Camera==NULL)
		return;
	Camera->CallFunc(Buffer ,BufferDimCounts,XReverse ,YReverse);
}

void	CameraClass::SlotCaptured()
{
	emit	SignalCaptured();
}

CameraHandle	*CameraClass::GetCameraHandle(void)	const
{	
	if(Camera==NULL)
		return NULL;
	return Camera->GetCameraHandle();
}