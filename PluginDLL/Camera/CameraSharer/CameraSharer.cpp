#include "CameraSharer.h"
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
#include "SelectChangeableDialog.h"

extern	int		WaitingMilisecForCapture;
QString		CameraSharer::FileNameForKeepPosition=/**/"CameraSharer.dat";
QString		CameraSharer::FileNameForParam=/**/"CameraSharerParam.dat";

CameraSharer::CameraSharer(int _CountOfCamera ,int _CountOfShare 
							,const QString &CameraDLLFileName 
							,const QString &_CameraSettingFileName 
							,LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,ThreadCamProcessInst(this)
	,ContactToCameraSharer(/**/"ContactToCameraSharer")
{
	ui.setupUi(this);

	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);

	CountOfCamera	=_CountOfCamera;
	CountOfShare	=_CountOfShare;
	CameraSettingFileName	=_CameraSettingFileName;
	if(CountOfShare==0)
		CountOfShare=1;

	int32 ErrorCode;
	ButtonNames.append("Top");
	ButtonNames.append("Bottom");
	for(int i=0;i<CountOfShare;i++){
		VisibleButton.Add(true);
	}

	QFile	File(FileNameForParam);
	if(File.open(QIODevice::ReadOnly)==true){
		LoadParam(&File);
	}


	for(int i=0;i<sizeof(CamNoTable)/sizeof(CamNoTable[0]);i++){
		CamNoTable[i]=i;
	}

	if(CameraDLLFileName.isEmpty()==false){
		GetParamGlobal()->CameraDLL_FileName=CameraDLLFileName;
		GetParamGlobal()->CameraAllocation	=/**/"";
	}

	for(int i=0;i<CountOfCamera;i++){
		Cam[i]=new CameraClass(CamNoTable[i],GetLayersBase());
		if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
			return;
		}
		int	LanguageCode=GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
		Cam[i]->SetLanguageCode(LanguageCode);
	}
	LoadSettingFile();

	for(int i=0;i<CountOfShare;i++){
		Handle[i]=new CameraSharerHandle(i,base,i);
		Handle[i]->OpenForServer();
		FirstAccessTime[i]=0;

		AssignedButton[i]=new QToolButton(this);
		AssignedButton[i]->move((ui.frame->width()/CountOfShare)*i,0);
		AssignedButton[i]->resize(ui.frame->width()/CountOfShare,ui.frame->height());
		AssignedButton[i]->setCheckable(true);
		AssignedButton[i]->setAutoExclusive(true);
		connect(AssignedButton[i],SIGNAL(clicked()),this,SLOT(SlotActiveShare()));

		if(i<ButtonNames.count())
			AssignedButton[i]->setText(ButtonNames[i]);
		else
			AssignedButton[i]->setText(QString("Cam")+QString::number(i+1));

		AssignedButton[i]->setEnabled(VisibleButton[i]);
	}
	AssignedButton[0]->setChecked(true);
	ActiveShareNo=0;

	ui.spinBoxCameraNo->setMaximum(CountOfCamera-1);

	connect(this,SIGNAL(SignalShowSetting(int)),this,SLOT(SlotShowSetting(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalIncrease()),this,SLOT(SlotIncrease()),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalReflectActiveNo(int)),this,SLOT(SlotReflectActiveNo(int)),Qt::QueuedConnection);

	if(ContactToCameraSharer.attach()==false){
		ContactToCameraSharer.create(sizeof(struct	CameraShareSwitcher));
	}
	ThreadCamProcessInst.start();
}

CameraSharer::~CameraSharer()
{
	ThreadCamProcessInst.Terminated=true;
	ThreadCamProcessInst.wait(1000);
	for(int i=0;i<CountOfCamera;i++){
		delete	Cam[i];
	}
	for(int i=0;i<CountOfShare;i++){
		delete	Handle[i];
	}
}


void	CameraSharer::closeEvent ( QCloseEvent * event )
{
	QFile	File(FileNameForKeepPosition);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	x=geometry().x();
		int32	y=geometry().y();
		int32	w=geometry().width();
		int32	h=geometry().height();

		if(::Save(&File,x)==false)
			return;
		if(::Save(&File,y)==false)
			return;
		if(::Save(&File,w)==false)
			return;
		if(::Save(&File,h)==false)
			return;
	}
}

void	CameraSharer::moveEvent ( QMoveEvent * event )
{
	if(isVisible()==true){
		QFile	File(FileNameForKeepPosition);
		if(File.open(QIODevice::WriteOnly)==true){
			int32	x=geometry().x();
			int32	y=geometry().y();
			int32	w=geometry().width();
			int32	h=geometry().height();

			if(::Save(&File,x)==false)
				return;
			if(::Save(&File,y)==false)
				return;
			if(::Save(&File,w)==false)
				return;
			if(::Save(&File,h)==false)
				return;
		}
	}
}

void	CameraSharer::showEvent ( QShowEvent * event )
{
	QFile	File(FileNameForKeepPosition);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	x,y,w,h;
		if(::Load(&File,x)==false)
			return;
		if(::Load(&File,y)==false)
			return;
		if(::Load(&File,w)==false)
			return;
		if(::Load(&File,h)==false)
			return;
		move(x,y);
	}
}

void	CameraSharer::ProcessInThread(void)
{
	for(int i=0;i<CountOfShare;i++){
		if(ActiveShareNo!=i){
			continue;
		}
		Handle[i]->Lock();
		struct	CameraSharerHandleHeader	*Header=Handle[i]->GetHeader();
		if(Header!=NULL){
			if(Header->Command==CameraSharerCommand_PrepareCapture){
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Cam[Header->CamNo]->PrepareCapture();
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_StartCapture){
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Cam[Header->CamNo]->StartCapture();
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_GetStatus){
				if(FirstAccessTime[i]==0){
					FirstAccessTime[i]=::GetComputerMiliSec();
					Header->Command=0;
					Header->RespondedValue	=1;
					Header->Response=true3;
				}
				else if(::GetComputerMiliSec()-FirstAccessTime[i]>WaitingMilisecForCapture){
					int status=0;
					if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
						status=Cam[Header->CamNo]->GetStatus();
					}
					Header->Command=0;
					Header->RespondedValue	=status;
					Header->Response=true3;
				}
			}
			else if(Header->Command==CameraSharerCommand_GetLineCount){
				int	Line=0;
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Line=Cam[Header->CamNo]->GetCurrentLineCount();
				}
				Header->Command=0;
				Header->RespondedValue	=Line;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_ClearError){
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Cam[Header->CamNo]->ClearError();
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_ClearBit){
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Cam[Header->CamNo]->ClearBuffer();
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_GetImage){
				FirstAccessTime[i]=0;
				ImageBuffer	*IBuff[10];
				for(int Layer=0;Layer<Header->LayerNumb;Layer++){
					IBuff[Layer]=new ImageBuffer();
					IBuff[Layer]->SetFromOriginalBuffer(Handle[i]->GetLayerBufferPointer(Layer),Header->XSize,Header->YSize);
				}
				bool	XReverse=false;
				bool	YReverse=false;
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					Cam[Header->CamNo]->GetImage(IBuff,Header->LayerNumb,XReverse,YReverse);
				}
				Header->Command=0;
				Header->Response=true3;
				for(int Layer=0;Layer<Header->LayerNumb;Layer++){
					delete	IBuff[Layer];
				}
			}
			else if(Header->Command==CameraSharerCommand_ReqCameraError){
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_ShowSetting){
				int	CamPointerNo=GetCamPointNumber(Header->ShareNo);
				CamFlag[CamPointerNo]=true;
				emit	SignalShowSetting(CamPointerNo);
				while(CamFlag[CamPointerNo]==true){
					GSleep(100);
				}
				Header->Command=0;
				Header->Response=true3;
			}
			else if(Header->Command==CameraSharerCommand_Save){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				bool	Ret=Cam[i]->Save(Buff);
				QByteArray	A=Buff.buffer();
				memcpy(Header->StreamData,A.data(),A.size());
				Header->StreamByte	=A.size();
				Header->Command=0;
				Header->Response=(Ret==true)?true3:false3;
			}
			else if(Header->Command==CameraSharerCommand_Load){
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

	for(int i=0;i<CountOfShare;i++){
		Handle[i]->Lock();
		struct	CameraSharerHandleHeader	*Header=Handle[i]->GetHeader();
		if(Header!=NULL){
			if(Header->Command==CameraSharerCommand_HaltCapture){
				if(0<=Header->CamNo && Header->CamNo<CountOfCamera){
					if(ActiveShareNo==i){
						Cam[Header->CamNo]->HaltCapture();
					}
				}
				Header->Command=0;
				Header->Response=true3;
			}
			if(Header->Command==CameraSharerCommand_Allocate){
				Handle[i]->Allocate();
				if(Header->XSize!=Handle[i]->GetDotPerLine()
				|| Header->YSize!=Handle[i]->GetMaxLines()){
				//|| Header->LayerNumb!=GetLayerNumb()){
					GetParamGlobal()->DotPerLine=Header->XSize;
					GetParamGlobal()->MaxLines	=Header->YSize;
					GetParamGlobal()->LayerNumb	=Header->LayerNumb;
					for(int i=0;i<CountOfCamera;i++){
						if(Cam[i]->ChangeInfo(Header->XSize ,Header->YSize,Header->LayerNumb,Header->PageNumb)==false){
							int32	ErrorCode;
							Cam[i]->Realloc(GetParamGlobal(),ErrorCode);
						}
					}
				}

				Header->Command=0;
				Header->Response=true3;
			}
		}
		Handle[i]->Unlock();
	}
	ContactToCameraSharer.lock();
	struct	CameraShareSwitcher	*Point=(struct	CameraShareSwitcher *)ContactToCameraSharer.data();
	if(Point!=NULL){
		if(Point->Command==1){
			for(int i=0;i<CountOfShare;i++){
				ActiveShareNo++;
				ActiveShareNo = ActiveShareNo % CountOfShare;
				if(VisibleButton[ActiveShareNo]==true){
					break;
				}
			}
			emit	SignalReflectActiveNo(ActiveShareNo);
		}
		else if(Point->Command==-5){
			int	m=Point->ReqSetActiveNo;
			if(VisibleButton[m]==true){
				ActiveShareNo=m;
				emit	SignalReflectActiveNo(ActiveShareNo);
			}
		}
		else if(Point->Command>=2){
			int	m=Point->Command-2;
			m = m % CountOfShare;
			if(VisibleButton[m]==true){
				ActiveShareNo=m;
				emit	SignalReflectActiveNo(ActiveShareNo);
			}
		}
		else if(Point->Command==-10){
			for(int i=0;i<CountOfShare;i++){
				if(AssignedButton[i]!=NULL){
					AssignedButton[i]->setEnabled(false);
				}
			}
		}
		else if(Point->Command==-11){
			for(int i=0;i<CountOfShare;i++){
				if(AssignedButton[i]!=NULL){
					AssignedButton[i]->setEnabled(true);
				}
			}
		}

		Point->CurrentActiveNo=ActiveShareNo;
		Point->Command=0;
	}
	ContactToCameraSharer.unlock();

	emit	SignalIncrease();
}


void	CameraSharer::SlotShowSetting(int Number)
{
	Cam[Number]->ShowSetting(NULL);
	CamFlag[Number]=false;
}
int		CameraSharer::GetCamPointNumber(int camNo)
{
	for(int i=0;i<CountOfCamera;i++){
		if(Cam[i]->GetCamNo()==camNo){
			return i;
		}
	}
	return -1;
}
void	CameraSharer::SlotIncrease()
{

}
void	CameraSharer::SlotReflectActiveNo(int ActiveNo)
{
	if(AssignedButton[ActiveNo]!=NULL){
		AssignedButton[ActiveNo]->setChecked(true);
	}
	ActiveShareNo=ActiveNo;
}
void	CameraSharer::SlotActiveShare()
{
	for(int i=0;i<CountOfShare;i++){
		if(AssignedButton[i]->isChecked()==true){
			ActiveShareNo=i;
		}
	}
}

ThreadCamProcess::ThreadCamProcess(CameraSharer *parent)
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
void	CameraSharer::ShowSetting(int n)
{
	emit	SignalShowSetting(n);
}

void	CameraSharer::SetCamNo(int n ,int camNo)
{
	Cam[n]->SetCamNo(camNo);
	CamNoTable[n]=camNo;
}

bool	CameraSharer::LoadSettingFile(void)
{
	QFile	File(CameraSettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		bool	Ret=true;
		int	n;
		if(::Load(&File,n)==false)
			return false;
		int	i;
		for(i=0;i<n && i<CountOfCamera;i++){
			QByteArray	Array;
			if(::Load(&File,Array)==false)
				return false;
			QBuffer	Buff(&Array);
			Buff.open(QIODevice::ReadOnly);
			if(Cam[i]->Load(Buff)==false){
				Ret=false;
			}
		}
		return Ret;
	}
	return false;
}
bool	CameraSharer::SaveSettingFile(void)
{
	QFile	File(CameraSettingFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(::Save(&File,CountOfCamera)==false)
			return false;

		for(int i=0;i<CountOfCamera;i++){
			QBuffer	Buff;
			Buff.open(QIODevice::WriteOnly);
			if(Cam[i]->Save(Buff)==false)
				return false;
			QByteArray	Array=Buff.buffer();
			if(::Save(&File,Array)==false)
				return false;
		}

		return true;
	}
	return false;
}

void CameraSharer::on_pushButtonSetting_clicked()
{
	int	N=ui.spinBoxCameraNo->value();
	if(0<=N && N<CountOfCamera && Cam[N]!=NULL){
		Cam[N]->ShowSetting(NULL);
	}
	SaveSettingFile();
}

void CameraSharer::on_pushButtonSelect_clicked()
{
	SelectChangeableDialog	D(this);
	if(D.exec()==true){
		QFile	File(FileNameForParam);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveParam(&File);

			for(int i=0;i<CountOfShare;i++){
				if(i<ButtonNames.count())
					AssignedButton[i]->setText(ButtonNames[i]);
				else
					AssignedButton[i]->setText(QString("Cam")+QString::number(i+1));

				AssignedButton[i]->setEnabled(VisibleButton[i]);
			}
		}
	}
}
	
bool	CameraSharer::LoadParam(QIODevice *f)
{
	if(::Load(f,ButtonNames)==false)
		return false;
	if(VisibleButton.Load(f)==false)
		return false;
	return true;
}

bool	CameraSharer::SaveParam(QIODevice *f)
{
	if(::Save(f,ButtonNames)==false)
		return false;
	if(VisibleButton.Save(f)==false)
		return false;
	return true;
}

