/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RealtimeImagePanel\RealtimeImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RealtimeImagePanel.h"
#include "XCrossObj.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "XCameraClass.h"

static	const	char	*sRoot=/**/"RealtimeGraph";
static	const	char	*sName=/**/"ImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show image realtimely in ImagePanel ");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new RealtimeImagePanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((RealtimeImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QStringList";
	Data[N].VariableNameWithRoute=/**/"RelatedItems";
	Data[N].Pointer				 =&((RealtimeImagePanel *)Instance)->RelatedItems;
	Data[N+1].Type				  =/**/"QString";
	Data[N+1].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N+1].Pointer			  =&((RealtimeImagePanel *)Instance)->ImageControlToolsName;
	Data[N+2].Type				  =/**/"int32";
	Data[N+2].VariableNameWithRoute=/**/"ShowFixedPhase";
	Data[N+2].Pointer			  =&((RealtimeImagePanel *)Instance)->ShowFixedPhase;
	Data[N+3].Type				  =/**/"Master,Target,DelayedView,CamTarget,RawTarget,SpecialBuffer";
	Data[N+3].VariableNameWithRoute=/**/"ImageType";
	Data[N+3].Pointer			  =&((RealtimeImagePanel *)Instance)->ImageType;
	Data[N+4].Type				  =/**/"int32";
	Data[N+4].VariableNameWithRoute=/**/"IntervalMilisec";
	Data[N+4].Pointer			  =&((RealtimeImagePanel *)Instance)->IntervalMilisec;
	
	return(N+5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RealtimeImagePanel.png")));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImage::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================

ImageBufferDimClass::ImageBufferDimClass(void)
{
	IBuff[0]=NULL;
	IBuff[1]=NULL;
	IBuff[2]=NULL;
}
ImageBufferDimClass::~ImageBufferDimClass(void)
{
	for(int i=0;i<3;i++){
		if(IBuff[i]!=NULL){
			delete	IBuff[i];
			IBuff[i]=NULL;
		}
	}
}

void	ImageBufferDimClass::Alloc(int XLen ,int YLen)
{
	for(int i=0;i<3;i++){
		if(IBuff[i]!=NULL){
			delete	IBuff[i];
		}
		IBuff[i]=new ImageBuffer();
		IBuff[i]->Set(0,0,XLen,YLen);
	}
}


//=====================================================================


RealtimeImagePanel::RealtimeImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImage(Base,QString(sRoot),QString(sName),__Target,parent)
{
	ImageType=/**/"Target";
	IntervalMilisec	=50;
	CountCamera	=0;
	IBuff=NULL;
	Cam=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

RealtimeImagePanel::~RealtimeImagePanel(void)
{
	if(IBuff!=NULL){
		delete	[]IBuff;
		IBuff=NULL;
	}
	if(Cam!=NULL){
		delete	[]Cam;
		Cam=NULL;
	}
}

void	RealtimeImagePanel::Prepare(void)
{
	DisplayImage::Prepare();
	if(ImageType==/**/"Master"){
		ChangeDisplayType(DisplayImage::__Master);
	}
	else if(ImageType==/**/"Target"){
		ChangeDisplayType(DisplayImage::__Target);
	}
	else if(ImageType==/**/"DelayedView"){
		ChangeDisplayType(DisplayImage::__DelayedView);
	}
	else if(ImageType==/**/"CamTarget"){
		ChangeDisplayType(DisplayImage::__CamTarget);
	}
	else if(ImageType==/**/"RawTarget"){
		ChangeDisplayType(DisplayImage::__RawTarget);
	}
	else if(ImageType==/**/"SpecialBuffer"){
		CountCamera=GetParamComm()->GetLocalCameraNumb(0);
		if(IBuff!=NULL){
			delete	[]IBuff;
		}
		IBuff=new ImageBufferDimClass[CountCamera];

		if(Cam!=NULL){
			delete	[]Cam;
		}
		Cam=new CameraClass*[CountCamera];

		for(int i=0;i<CountCamera;i++){
			Cam[i]=NULL;
		}

		Timer.setInterval(IntervalMilisec);
		Timer.setSingleShot(false);
		connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
		Timer.start();
	}
}

void	RealtimeImagePanel::ReadyParam(void)
{
	if(Cam!=NULL){
		ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(E!=NULL){
			for(int i=0;i<CountCamera;i++){
				Cam[i]=E->GetCamera(i);
			}
		}
	}
	if(IBuff!=NULL){
		for(int i=0;i<CountCamera;i++){
			IBuff[i].Alloc(GetDotPerLine(i) ,GetMaxLines(i));
		}
	}
}
void	RealtimeImagePanel::ResizeAction()
{
	Image=QImage(width(),height(),QImage::Format_RGB32);
}
void	RealtimeImagePanel::SlotTimeout()
{
	if(Cam!=NULL){
		for(int i=0;i<CountCamera;i++){
			if(IBuff[i].IBuff[0]!=NULL && Cam[i]!=NULL){
				Cam[i]->StartCaptureContinuously(IBuff[i].IBuff,GetLayerNumb(i),NULL);
			}
		}
		Repaint();
	}
}
void	RealtimeImagePanel::ShowInPlayer(int64 shownInspectionID)
{
	Repaint();
}
void	RealtimeImagePanel::ShowInScanning(int64 shownInspectionID)
{
	ShowInPlayer(shownInspectionID);
}

bool	RealtimeImagePanel::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(IBuff!=NULL){
		for(int i=0;i<CountCamera;i++){
			IBuff[i].Alloc(NewDotPerLine ,NewMaxLines);
		}
	}
	return true;
}

void	RealtimeImagePanel::CanvasSlotOnPaint(QPainter &pnt)
{
	if(ImageType!=/**/"SpecialBuffer"){
		DisplayImage::CanvasSlotOnPaint(pnt);
	}
	else if(IBuff!=NULL && IBuff[0].IBuff[0]!=NULL){
		int	movx=GetMovx();
		int	movy=GetMovy();
		double	ZoomRate=GetZoomRate();
		double	Z=1.0/ZoomRate;

		int	W=Image.width();
		int	H=Image.height();

		for(int cam=0;cam<CountCamera;cam++){
			int	OffsetX=cam*GetDotPerLine(0);
			int	OffsetY=0;
			int	ImageHeight=IBuff[cam].IBuff[0]->GetHeight();
			int	ImageWidth =IBuff[cam].IBuff[0]->GetWidth();

			for(int y=0;y<H;y++){
				QRgb	*d=(QRgb *)Image.scanLine(y);
				int	Y=(y+OffsetY-movy)*Z;
				if(0<=Y && Y<ImageHeight){
					if(GetLayerNumb(0)==3){
						BYTE	*sR=IBuff[cam].IBuff[0]->GetY(Y);
						BYTE	*sG=IBuff[cam].IBuff[1]->GetY(Y);
						BYTE	*sB=IBuff[cam].IBuff[2]->GetY(Y);
						for(int x=0;x<W;x++,d++){
							int	X=(x-movx)*Z;
							if(0<=X && X<ImageWidth){
								*d=qRgb(sR[X],sG[X],sB[X]);
							}
							else{
								*d=qRgb(0,0,0);
							}
						}
					}
					else
					if(GetLayerNumb(0)==1){
						BYTE	*sR=IBuff[cam].IBuff[0]->GetY(Y);
						for(int x=0;x<W;x++,d++){
							int	X=(x-movx)*Z;
							if(0<=X && X<ImageWidth){
								*d=qRgb(sR[X],sR[X],sR[X]);
							}
							else{
								*d=qRgb(0,0,0);
							}
						}
					}
				}
				else{
					for(int x=0;x<W;x++,d++){
						*d=qRgb(0,0,0);
					}
				}
			}
		}
		pnt.drawImage(0,0,Image);
	}
}
