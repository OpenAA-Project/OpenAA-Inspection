/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RecordMovie\RecordMovie.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RecordMovie.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include <Windows.h>
#include <vfw.h>
#include <QMutex>
#include <QMessageBox>
#include <QDir>
#include "XMovieThread.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "ShowCycleTime.h"
#include "SettingRecordDialog.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"RecordMovie";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to record movie");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new RecordMovie(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<8)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((RecordMovie *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((RecordMovie *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((RecordMovie *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((RecordMovie *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileNameFormat";
	Data[4].Pointer				 =&((RecordMovie *)Instance)->FileNameFormat;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"FPS";
	Data[5].Pointer				 =&((RecordMovie *)Instance)->FPS;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"MovieQuality";
	Data[6].Pointer				 = &((RecordMovie*)Instance)->MovieQuality;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"UsePage";
	Data[7].Pointer				 = &((RecordMovie*)Instance)->UsePage;
	Data[8].Type				 =/**/"MotionJPEG,MPEG1,MPEG2,MPEG4";
	Data[8].VariableNameWithRoute=/**/"AVFormatStr";
	Data[8].Pointer				 = &((RecordMovie*)Instance)->AVFormatStr;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"DefaultSettingFileName";
	Data[9].Pointer				 = &((RecordMovie*)Instance)->DefaultSettingFileName;
	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RecordMovie.png")));
}

//==================================================================================================

//==================================================================================================
RecordMovie::RecordMovie(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"RecordMovie");
	Msg=/**/"Record Movie";
	
	JpegQuality		=30;
	FPS				=30;
	MovieQuality	= 75;
	UsePage			=0;
	CycleTimePointer=NULL;
	DefaultSettingFileName	=/**/"DefaultRecordMovie.dat";
	MovieSizeMode	=4;

	CapturedCount	=0;
	CapturedWIndex	=0;
	LastTime		=0;

	SavedFolder		=/**/"\\Image";
	FileNameFormat	=/**/"yyyyMMdd_hhmmss";
	AVFormat		=FormatMPeg1;
	AVFormatStr		=/**/"MPEG1";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&SavedFolder, /**/"RecordMovie",/**/"SavedFolder"	
												,"Folder path to save mpg file");
	GetParamGUI()->SetParam(&JpegQuality, /**/"RecordMovie",/**/"JpegQuality"	
												,"Compression quality");

	ThreadImage = new AddImageForMovie		 (GetLayersBase(),this);

	connect(ThreadImage,SIGNAL(SignalMemoryOver()),this,SLOT(SlotMemoryOver()),Qt::QueuedConnection);
	connect(ThreadImage,SIGNAL(SignalWriteError()),this,SLOT(SlotWriteError()),Qt::QueuedConnection);
}

RecordMovie::~RecordMovie(void)
{
	Terminated();
	AVIFileExit();
}

void	RecordMovie::Terminated(void)
{
	if (ThreadImage != NULL) {
		ThreadImage->Terminated = true;
	}
	if (ThreadImage != NULL) {
		ThreadImage->deleteLater();
		ThreadImage =NULL;
	}
}

void	RecordMovie::Prepare(void)
{
	AVIFileInit();

	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setCheckable(true);
	Button.setChecked(false);

	MovieXSize	=GetDotPerLine(UsePage);
	if(MovieXSize<320)
		MovieXSize=320;
	MovieYSize	=GetMaxLines(UsePage);
	if(MovieYSize<240)
		MovieYSize=240;

	QString	UserPath=GetLayersBase()->GetUserPath();
	QFile	File(UserPath+QDir::separator()+DefaultSettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadContent(&File)==true){
			SetMovieSize(MovieSizeMode);
		}
	}

	ResizeAction();
	ThreadImage->Initialize();
	AVFormat=GetAVFormat();
	ReallocMovieXYPixels();
	ThreadImage->start();
}

void	RecordMovie::ReadyParam(void)
{
	ExecuteInspectBase	*e=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(e!=NULL){
		connect(e,SIGNAL(SignalTargetImageCaptured()), this ,SLOT(SlotTargetImageCaptured()));
	}

	CycleTimePointer=GetLayersBase()->FindByName(/**/"Action",/**/"ShowCycleTime",/**/"");
	if(CycleTimePointer==NULL){
		bool	Ret=false;
		ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(E!=NULL){
			Ret=(connect(E,SIGNAL(SignalCaptured(int))	,this,SLOT(SlotCaptured(int))	,Qt::QueuedConnection))?true:false;
		}
	}
}

void	RecordMovie::ResizeAction()
{
	Button.resize(width(),height());
}

void RecordMovie::SlotClicked (bool checked)
{
	if(Button.isChecked()==true){
		QDateTime	NowTime=QDateTime::currentDateTime();
		ForceDirectories( SavedFolder ); 
		CurrentFileName=SavedFolder+GetSeparator()+NowTime.toString(FileNameFormat)+QString(/**/".avi");
		CurrentFPS=GetFPS();
		ThreadImage->StartRecording(GetAVFormat(),CurrentFileName,CurrentFPS,MovieQuality);
	}
	else{
		ThreadImage->StopRecording();
		ThreadImage->EndRecording();
	}
}
EnumAVFormat	RecordMovie::GetAVFormat(void)
{
	EnumAVFormat	Ret=FormatMotionJPeg;
	if(AVFormatStr==/**/"MPEG1")
		Ret=FormatMPeg1;
	else
	if(AVFormatStr==/**/"MPEG2")
		Ret=FormatMPeg2;
	else
	if(AVFormatStr==/**/"MPEG4")
		Ret=FormatMPeg4;
	else
	if(AVFormatStr==/**/"MotionJPEG")
		Ret=FormatMotionJPeg;
	return Ret;
}
void	RecordMovie::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdStartRecordMovie	*CmdStartRecordMovieVar=dynamic_cast<CmdStartRecordMovie *>(packet);
	if(CmdStartRecordMovieVar!=NULL){
		if(Button.isChecked()==false){
			Button.setChecked(true);
			SlotClicked(true);
		}
		CmdStartRecordMovieVar->RetFileName=CurrentFileName;
		return;
	}
	CmdStartRecordMovieWithFileName	*CmdStartRecordMovieWithFileNameVar=dynamic_cast<CmdStartRecordMovieWithFileName *>(packet);
	if(CmdStartRecordMovieWithFileNameVar!=NULL){
		Button.setChecked(true);	
		CurrentFileName=CmdStartRecordMovieWithFileNameVar->FileName;
		QFileInfo	FInfo(CurrentFileName);
		ForceDirectories( FInfo.absolutePath() ); 
		SetTargetPage(CmdStartRecordMovieWithFileNameVar->RecordPageNo);
		//CurrentFPS=GetFPS();
		ThreadImage->StartRecording(GetAVFormat()
								,CurrentFileName
								,CmdStartRecordMovieWithFileNameVar->FPS
								,CmdStartRecordMovieWithFileNameVar->Quality);
		return;
	}
	CmdEndRecordMovie	*CmdEndRecordMovieVar=dynamic_cast<CmdEndRecordMovie *>(packet);
	if(CmdEndRecordMovieVar!=NULL){
		if(Button.isChecked()==true){
			Button.setChecked(false);
			SlotClicked(false);
		}
		return;
	}
	CmdSetRecordMovieSize	*CmdSetRecordMovieSizeVar=dynamic_cast<CmdSetRecordMovieSize *>(packet);
	if(CmdSetRecordMovieSizeVar!=NULL){
		MovieXSize	=CmdSetRecordMovieSizeVar->MovieXSize;
		MovieYSize	=CmdSetRecordMovieSizeVar->MovieYSize;
		MovieQuality=CmdSetRecordMovieSizeVar->MovieQuality;
		CurrentFPS=GetFPS();
		CmdSetRecordMovieSizeVar->ReturnFPS=CurrentFPS;
		ReallocMovieXYPixels();
		return;
	}
	CmdShowSettingRecordDialog	*CmdShowSettingRecordDialogVar=dynamic_cast<CmdShowSettingRecordDialog *>(packet);
	if(CmdShowSettingRecordDialogVar!=NULL){
		SettingRecordDialog	D(this);
		if(D.exec()==true){
			AVFormatStr		=D.AVFormatStr		;
			MovieSizeMode	=D.MovieSizeMode	;
			TargetFrameRate	=D.TargetFrameRate	;
			DivideMovieFile	=D.DivideMovieFile	;
			SetMovieSize(MovieSizeMode);

			QString	UserPath=GetLayersBase()->GetUserPath();
			QFile	File(UserPath+QDir::separator()+DefaultSettingFileName);
			if(File.open(QIODevice::WriteOnly)==true){
				SaveContent(&File);
			}
		}
		return;
	}
	CmdReqRecordMovieMaxTime	*CmdReqRecordMovieMaxTimeVar=dynamic_cast<CmdReqRecordMovieMaxTime *>(packet);
	if(CmdReqRecordMovieMaxTimeVar!=NULL){
		int	Size=CmdReqRecordMovieMaxTimeVar->MovieXSize*CmdReqRecordMovieMaxTimeVar->MovieYSize;
		CmdReqRecordMovieMaxTimeVar->RetMaxSecond=0x7FFFFFFFLU/(Size*3+1000)/CmdReqRecordMovieMaxTimeVar->FPS;
		return;
	}
}

void	RecordMovie::SetMovieSize(int Index)
{
	switch(Index){
	case 0:	MovieXSize	=2592;
			MovieYSize	=1944;
			break;
	case 1:	MovieXSize	=2048;
			MovieYSize	=1536;
			break;
	case 2:	MovieXSize	=1920;
			MovieYSize	=1080;
			break;
	case 3:	MovieXSize	=1024;
			MovieYSize	=768;
			break;
	case 4:	MovieXSize	=640;
			MovieYSize	=480;
			break;
	case 5:	MovieXSize	=320;
			MovieYSize	=240;
			break;
	}
}

void	RecordMovie::ReallocMovieXYPixels(void)
{
	ThreadImage->AllocateBuff();
}

void	RecordMovie::SlotTargetImageCaptured()
{
	if(GetLayersBase()->GetOnTerminating()==false){
		ThreadImage->AddImage();
	}
}

void	RecordMovie::SlotCaptured(int)
{
	DWORD	D=::GetComputerMiliSec();
	if(LastTime==0)
		LastTime=D;
	else{
		CapturedTime[CapturedWIndex]=D-LastTime;
		LastTime=D;
		CapturedWIndex++;
		if(CapturedWIndex>=sizeof(CapturedTime)/sizeof(CapturedTime[0]))
			CapturedWIndex=0;
		CapturedCount++;
		if(CapturedCount>sizeof(CapturedTime)/sizeof(CapturedTime[0]))
			CapturedCount=sizeof(CapturedTime)/sizeof(CapturedTime[0]);
	}
}

double	RecordMovie::GetFPS(void)
{
	if(CycleTimePointer!=NULL){
		CmdReqCycleTimeFPS	RCmd(GetLayersBase());
		CycleTimePointer->TransmitDirectly(&RCmd);
		CurrentFPS=RCmd.FPS;
	}
	else{
		DWORD	Sum=0;
		if(CapturedCount>0){
			for(int i=0;i<CapturedCount;i++){
				Sum+=CapturedTime[i];
			}
			double	V=((double)Sum)/((double)CapturedCount);
			if(V>0){
				CurrentFPS=1000.0/V;
			}
		}
	}
	return CurrentFPS;
}

void	RecordMovie::SlotMemoryOver()
{
	QMessageBox::critical(NULL
							,"Error"
							,"メモリーが不足したので録画を停止してください"
						);

}
void	RecordMovie::SlotWriteError()
{
	QMessageBox::critical(NULL
							,"Error"
							,"保存先に空き容量がなくなったので録画を停止してください"
						);
}

bool	RecordMovie::SaveContent(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver			)==false)	return false;
	if(::Save(f,AVFormatStr	)==false)	return false;
	if(::Save(f,MovieSizeMode	)==false)	return false;
	if(::Save(f,TargetFrameRate)==false)	return false;
	if(::Save(f,DivideMovieFile)==false)	return false;
	return true;
}

bool	RecordMovie::LoadContent(QIODevice *f)
{
	int32	Ver=1;

	if(::Load(f,Ver			)==false)	return false;
	if(::Load(f,AVFormatStr	)==false)	return false;
	if(::Load(f,MovieSizeMode	)==false)	return false;
	if(::Load(f,TargetFrameRate)==false)	return false;
	if(::Load(f,DivideMovieFile)==false)	return false;
	return true;
}

