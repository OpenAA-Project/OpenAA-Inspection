#include "CameraProvider.h"

#include "XDateTime.h"
#include <QThread>

//#include "XExecuteInspect.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <stdio.h>
#include "XParamGlobal.h"
#include "XFileRegistry.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"
#include "XDataInExe.h"
#include "XFilterManager.h"
#include "XIntClass.h"
#include "XForWindows.h"
#include <omp.h>
#include "SelectSettingDialog.h"

extern	int	WaitingMilisecForCapture;
extern	QString	CameraProviderSettingFile;

CameraProvider::CameraProvider(int _CountOfCamera,const QString &CameraDLLFileName ,LayersBase *base ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,ThreadCamProcessInst(this)
{
	ui.setupUi(this);
	CountOfCamera	=_CountOfCamera;
	int32 ErrorCode;

	for(int i=0;i<sizeof(CamNoTable)/sizeof(CamNoTable[0]);i++){
		CamNoTable[i]=i;
	}

	LoadSettingFile();

	if(CameraDLLFileName.isEmpty()==false){
		GetParamGlobal()->CameraDLL_FileName=CameraDLLFileName;
		GetParamGlobal()->CameraAllocation	=/**/"";
	}

	AllocatedCamNumb=CountOfCamera;		//	GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);

	for(int i=0;i<AllocatedCamNumb;i++){
		Cam[i]=new CameraClass(CamNoTable[i],GetLayersBase());
		Handle[i]=new CameraProviderHandle(base,CamNoTable[i]);
	}
	for(int i=0;i<AllocatedCamNumb;i++){
		if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
			return;
		}
		int	LanguageCode=GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
		Cam[i]->SetLanguageCode(LanguageCode);
		Handle[i]->OpenForServer(Handle[i]->GetDotPerLine(),Handle[i]->GetMaxLines(),GetLayerNumb());
		FirstAccessTime[i]=0;
	}
	ui.tableWidget->setRowCount(AllocatedCamNumb);
	for(int row=0;row<AllocatedCamNumb;row++){
		::SetDataToTable(ui.tableWidget ,0 ,row,QString::number(Cam[row]->GetCamNo()));
		::SetDataToTable(ui.tableWidget ,1 ,row,Cam[row]->GetLibraryFileName());
	}
	ui.tableWidget->setColumnWidth(0, 64);
	ui.tableWidget->setColumnWidth(1, 310);

	connect(this,SIGNAL(SignalShowSetting(int)),this,SLOT(SlotShowSetting(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalIncrease()),this,SLOT(SlotIncrease()),Qt::QueuedConnection);

	ThreadCamProcessInst.start();
}

CameraProvider::~CameraProvider()
{
	ThreadCamProcessInst.Terminated=true;
	ThreadCamProcessInst.wait(1000);
	for(int i=0;i<AllocatedCamNumb;i++){
		delete	Cam[i];
		delete	Handle[i];
	}
}

void	CameraProvider::ProcessInThread(void)
{
	for(int i=0;i<AllocatedCamNumb;i++){
		Handle[i]->Lock();
		struct	CameraProviderHandleHeader	*Header=Handle[i]->GetHeader();
		if(Header!=NULL){
			if(Header->Command==CameraProviderCommand_PrepareCapture){
				Cam[i]->PrepareCapture();
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_StartCapture){
				Cam[i]->StartCapture();
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_HaltCapture){
				Cam[i]->HaltCapture();
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_GetStatus){
				if(FirstAccessTime[i]==0){
					FirstAccessTime[i]=::GetComputerMiliSec();
					Header->Command=0;
					Header->RespondedValue	=1;
					Header->Response=true3;
				}
				else if(::GetComputerMiliSec()-FirstAccessTime[i]>WaitingMilisecForCapture){
					int status=Cam[i]->GetStatus();
					Header->Command=0;
					Header->RespondedValue	=status;
					Header->Response=true3;
				}
			}
			else if(Header->Command==CameraProviderCommand_GetLineCount){
				int Line=Cam[i]->GetCurrentLineCount();
				Header->Command=0;
				Header->RespondedValue	=Line;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_ClearError){
				Cam[i]->ClearError();
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_ClearBit){
				Cam[i]->ClearBuffer();
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_GetImage){
				FirstAccessTime[i]=0;
				ImageBuffer	*IBuff[10];
				for(int Layer=0;Layer<Header->LayerNumb;Layer++){
					IBuff[Layer]=new ImageBuffer();
					IBuff[Layer]->SetFromOriginalBuffer(Handle[i]->GetLayerBufferPointer(Layer),Header->XSize,Header->YSize);
				}
				bool	XReverse=false;
				bool	YReverse=false;
				Cam[i]->GetImage(IBuff,Header->LayerNumb,XReverse,YReverse);
				Header->Command=0;
				Header->Response=true3;
				for(int Layer=0;Layer<Header->LayerNumb;Layer++){
					delete	IBuff[Layer];
				}
			}
			else if(Header->Command==CameraProviderCommand_ReqCameraError){
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_ShowSetting){
				int	CamPointerNo=GetCamPointNumber(Header->CameraNo);
				CamFlag[CamPointerNo]=true;
				emit	SignalShowSetting(CamPointerNo);
				while(CamFlag[CamPointerNo]==true){
					GSleep(100);
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraProviderCommand_Save){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				bool	Ret=Cam[i]->Save(Buff);
				QByteArray	A=Buff.buffer();
				memcpy(Header->StreamData,A.data(),A.size());
				Header->StreamByte	=A.size();
				Header->Command=0;
				Header->Response=(Ret==true)?true3:false3;
			}
			else if(Header->Command==CameraProviderCommand_Load){
				QByteArray	A((const char *)Header->StreamData,Header->StreamByte);
				QBuffer	Buff(&A);
				Buff.open(QIODevice::ReadOnly);
				bool	Ret=Cam[i]->Load(Buff);
				Header->Command=0;
				Header->Response=(Ret==true)?true3:false3;
			}
		}
		Handle[i]->Unlock();
	}
	emit	SignalIncrease();
}
void	CameraProvider::SlotShowSetting(int Number)
{
	Cam[Number]->ShowSetting(NULL);
	CamFlag[Number]=false;
}
int		CameraProvider::GetCamPointNumber(int camNo)
{
	for(int i=0;i<AllocatedCamNumb;i++){
		if(Cam[i]->GetCamNo()==camNo){
			return i;
		}
	}
	return -1;
}
void	CameraProvider::SlotIncrease()
{
	int	n=ui.progressBar->value();
	n++;
	if(n>ui.progressBar->maximum())
		n=0;
	ui.progressBar->setValue(n);
}

ThreadCamProcess::ThreadCamProcess(CameraProvider *parent)
	:QThread(parent),Parent(parent)
{
	Terminated=false;
}

void ThreadCamProcess::run ()
{
	while(Terminated==false){
		Parent->ProcessInThread();
		usleep(100);
	}
}
void	CameraProvider::ShowSetting(int n)
{
	emit	SignalShowSetting(n);
}

void	CameraProvider::SetCamNo(int n ,int camNo)
{
	Cam[n]->SetCamNo(camNo);
	CamNoTable[n]=camNo;
}

bool	CameraProvider::LoadSettingFile(void)
{
	QFile	File(CameraProviderSettingFile);
	if(File.open(QIODevice::ReadOnly)==true){
		int	n;
		if(::Load(&File,n)==false)
			return false;
		int	i;
		for(i=0;i<n && i<sizeof(CamNoTable)/sizeof(CamNoTable[0]);i++){
			if(::Load(&File,CamNoTable[i])==false)
				return false;
		}
		for(;i<n;i++){
			int	Dymmy;
			if(::Load(&File,Dymmy)==false)
				return false;
		}
		return true;
	}
	return false;
}
bool	CameraProvider::SaveSettingFile(void)
{
	QFile	File(CameraProviderSettingFile);
	if(File.open(QIODevice::WriteOnly)==true){
		int	n=sizeof(CamNoTable)/sizeof(CamNoTable[0]);
		if(::Save(&File,n)==false)
			return false;
		for(int i=0;i<n;i++){
			if(::Save(&File,CamNoTable[i])==false)
				return false;
		}
		return true;
	}
	return false;
}

void CameraProvider::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	R=ui.tableWidget->currentRow();
	if(R<0)
		return;
	SelectSettingDialog	D(this,R);
	D.exec();
	SaveSettingFile();
}
