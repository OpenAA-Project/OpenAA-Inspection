#include <cmath>
#include "XIntegrationSimpleImagePanel.h"
#include "XIntegrationSimpleImagePanelPacket.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <QGestureEvent>
#include <QPinchGesture>
#include "SelectItemsDialog.h"
#include "XDataAlgorithmList.h"
#include "CopyAlgorithmDialog.h"
#include "SetLineWidthDialog.h"
#include "XGeneralFunc.h"

const int	IntegrationPanelMaxCommTime=1000;

MainImagePanel::MainImagePanel(LayersBase *Base,IntegrationSimpleImagePanel *parent)
	:mtGraphicUnit(parent),ServiceForLayers(Base),Parent(parent)
{
	CurrentPhase=-1;
	Img			=NULL;
	RCmdImage	=NULL;
	ACmdImage	=NULL;
	Dirty		=true;
	LastZoomRate=0;
	LastMoveX	=0;
	LastMoveY	=0;

	bool	ErrorOccurs;
	if(!connect(this,SIGNAL(SignalOnPaint(QPainter &)) ,this,SLOT(SlotOnPaint(QPainter &)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseMove(int ,int)) ,this,SLOT(SlotMouseMove(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseLDown(int ,int)),this,SLOT(SlotMouseLDown(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseRDown(int ,int)),this,SLOT(SlotMouseRDown(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseLDoubleClick(int ,int)),this,SLOT(SlotMouseLDoubleClick(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseRDoubleClick(int ,int)),this,SLOT(SlotMouseRDoubleClick(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalShiftAll(void))	,this,SLOT(SlotShiftAll(void)))){
		ErrorOccurs=true;
	}
}

MainImagePanel::~MainImagePanel(void)
{
	if(Img!=NULL){
		delete	Img;
		Img=NULL;
	}
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		if(RCmdImage!=NULL){
			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				delete	RCmdImage[SlaveNo];
			}
			delete	RCmdImage;
			RCmdImage=NULL;
		}
		if(ACmdImage!=NULL){
			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				delete	ACmdImage[SlaveNo];
			}
			delete	ACmdImage;
			ACmdImage=NULL;
		}
	}
}

void	MainImagePanel::Prepare(void)
{
	int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	RCmdImage	=new IntegrationReqPanelImage*[N];
	ACmdImage	=new IntegrationAckPanelImage*[N];
	for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
		RCmdImage[SlaveNo]	=new IntegrationReqPanelImage(GetLayersBase(),Parent->GetDLLRoot(),Parent->GetDLLName(),SlaveNo);
		ACmdImage[SlaveNo]	=new IntegrationAckPanelImage(GetLayersBase(),Parent->GetDLLRoot(),Parent->GetDLLName(),SlaveNo);
	}
}
void	MainImagePanel::SlotOnPaint(QPainter &pnt)
{
	if(Parent->GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(Parent->MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	if(CurrentPhase!=Phase){
		int	x1,y1,x2,y2;
		x1=y1=x2=y2=0;
		m->GetXY(x1,y1,x2,y2);
		SetAreaSize(x2,y2);
		CurrentPhase=Phase;
	}

	int	W=GetCanvasWidth();
	int	H=GetCanvasHeight();

	if(Parent->ModeThoughNet==false){
		if(Img==NULL || Img->width()!=W || Img->height()!=H){
			if(Img!=NULL)
				delete	Img;
			Img=new QImage(W,H,QImage::Format_ARGB32);
			Dirty=true;
		}
		if(Dirty==true
		|| LastZoomRate	!=GetZoomRate()
		|| LastMoveX	!=GetMovx()
		|| LastMoveY	!=GetMovy()){
			LastZoomRate=GetZoomRate();
			LastMoveX	=GetMovx();
			LastMoveY	=GetMovy();

			//Img->fill(Qt::black);
			::ClearImage(*Img, 255);
			double	Z=1.0/GetZoomRate();
			for(int page=0;page<m->GetPageNumb();page++){
				XYData	*XY=m->GetOutlineOffset(CurrentPhase,page);
				if(XY!=NULL){
					int	iDotPerLine	=m->GetDotPerLine(Phase,page);
					int	iMaxLines	=m->GetMaxLines(Phase,page);	

					int	gx1=(XY->x+GetMovx())*GetZoomRate();
					int	gy1=(XY->y+GetMovy())*GetZoomRate();
					int	gx2=(XY->x+GetMovx()+iDotPerLine)*GetZoomRate();
					int	gy2=(XY->y+GetMovy()+iMaxLines	)*GetZoomRate();

					gx1=max(gx1,0);
					gy1=max(gy1,0);
					gx2=min(gx2,W);
					gy2=min(gy2,H);
					int	X1=Clipping((int)(gx1*Z-XY->x-GetMovx()),0,iDotPerLine);
					int	X2=Clipping((int)(gx2*Z-XY->x-GetMovx()),0,iDotPerLine);

					int	YNumb=gy2-gy1;
					if(m->GetLayerNumb(Phase,page)==1){
						ImageBuffer	*SBuff0=m->GetMasterImage(CurrentPhase ,page ,0);
						if(SBuff0!=NULL){
							#pragma omp parallel                             
							{                                                
								#pragma omp for
								//for(int y=gy1;y<gy2;y++){
								for(int t=0;t<YNumb;t++){
									int	y=gy1+t;
									QRgb	*d=(QRgb *)Img->scanLine(y);
									d+=gx1;
									int	Y =Clipping((int)(y*Z-XY->y-GetMovy()),0,iMaxLines);
									BYTE	*s=SBuff0->GetY(Y);
									for(double DX=X1;DX<X2;DX+=Z,d++){
										BYTE	c=s[(int)DX];
										*d=qRgba(c,c,c,255);
									}
								}
							}
						}
					}
					else
					if(m->GetLayerNumb(Phase,page)==2){
						ImageBuffer	*SBuff0=m->GetMasterImage(CurrentPhase ,page ,0);
						ImageBuffer	*SBuff1=m->GetMasterImage(CurrentPhase ,page ,1);
						if(SBuff0!=NULL && SBuff1!=NULL){
							#pragma omp parallel                             
							{                                                
								#pragma omp for
								//for(int y=gy1;y<gy2;y++){
								for(int t=0;t<YNumb;t++){
									int	y=gy1+t;
									QRgb	*d=(QRgb *)Img->scanLine(y);
									d+=gx1;
									int	Y =Clipping((int)(y*Z-XY->y-GetMovy()),0,iMaxLines);
									BYTE	*s0=SBuff0->GetY(Y);
									BYTE	*s1=SBuff1->GetY(Y);
									for(double DX=X1;DX<X2;DX+=Z,d++){
										BYTE	c0=s0[(int)DX];
										BYTE	c1=s1[(int)DX];
										*d=qRgba(c0,c0,c1,255);
									}
								}
							}
						}
					}
					else
					if(m->GetLayerNumb(Phase,page)>=3){
						ImageBuffer	*SBuff0=m->GetMasterImage(CurrentPhase ,page ,0);
						ImageBuffer	*SBuff1=m->GetMasterImage(CurrentPhase ,page ,1);
						ImageBuffer	*SBuff2=m->GetMasterImage(CurrentPhase ,page ,2);
						if(SBuff0!=NULL && SBuff1!=NULL && SBuff2!=NULL){
							#pragma omp parallel                             
							{                                                
								#pragma omp for
								//for(int y=gy1;y<gy2;y++){
								for(int t=0;t<YNumb;t++){
									int	y=gy1+t;
									QRgb	*d=(QRgb *)Img->scanLine(y);
									d+=gx1;
									int	Y =Clipping((int)(y*Z-XY->y-GetMovy()),0,iMaxLines);
									BYTE	*s0=SBuff0->GetY(Y);
									BYTE	*s1=SBuff1->GetY(Y);
									BYTE	*s2=SBuff2->GetY(Y);
								
									for(double DX=X1;DX<X2;DX+=Z,d++){
										int	X=(int)DX;
										BYTE	c0=s0[X];
										BYTE	c1=s1[X];
										BYTE	c2=s2[X];
										*d=qRgba(c0,c1,c2,255);
									}
								}
							}
						}
					}
				}
			}
			Dirty=false;
		}
		pnt.drawImage(0,0,*Img);
	}
	else{
		int	SlaveNo=m->GetIntegrationSlaveNo();
		if(Img==NULL || Img->width()!=W || Img->height()!=H){
			if(Img!=NULL)
				delete	Img;
			Img=new QImage(W,H,QImage::Format_ARGB32);
			Dirty=true;
		}
		if(Dirty==true){
			RCmdImage[SlaveNo]->PanelImageInfo.Phase	=Phase;
			RCmdImage[SlaveNo]->PanelImageInfo.CanvasWidth	=W;
			RCmdImage[SlaveNo]->PanelImageInfo.CanvasHeight	=H;
			RCmdImage[SlaveNo]->PanelImageInfo.CountOfLayer	=GetLayerNumb(0);
			RCmdImage[SlaveNo]->PanelImageInfo.ZoomRate		=GetZoomRate();
			RCmdImage[SlaveNo]->PanelImageInfo.Movx			=GetMovx();
			RCmdImage[SlaveNo]->PanelImageInfo.Movy			=GetMovy();
			if(RCmdImage[SlaveNo]->Send(SlaveNo,0,*ACmdImage[SlaveNo])==true){
				ACmdImage[SlaveNo]->CopyToImage(*Img);
				//*Img=*ACmdImage[SlaveNo]->Image;
				Dirty=false;
			}
		}
		pnt.drawImage(0,0,*Img);
	}
	Parent->PaintFunc(pnt ,GetZoomRate() , GetMovx() , GetMovy());
}
void	MainImagePanel::SlotMouseMove(int globalX ,int globalY)
{
	if(Parent->CurrentMode!=IntegrationSimpleImagePanel::Mode_ZoomIn){
		emit	SignalCanvasMouseMove(globalX ,globalY);
	}
	else
	if(Parent->CurrentMode!=IntegrationSimpleImagePanel::Mode_ZoomOut){
		emit	SignalCanvasMouseMove(globalX ,globalY);
	}
}
void	MainImagePanel::SlotMouseLDown(int globalX ,int globalY)
{
	emit	SignalCanvasMouseLDown(globalX ,globalY);
}
void	MainImagePanel::SlotMouseRDown(int globalX ,int globalY)
{
	emit	SignalCanvasMouseRDown(globalX ,globalY);
}
void	MainImagePanel::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		if(GetZoomRate()<Parent->GetMaxZoomValue()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomIn(Gx ,Gy);
		}
	}
	else if(delta<0){
		if(GetZoomRate()>Parent->GetMinZoomValue()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomOut(Gx ,Gy);
		}
	}
}

void	MainImagePanel::SlotMouseLDoubleClick(int globalX ,int globalY)
{
	if(Parent->CurrentMode==IntegrationSimpleImagePanel::Mode_ZoomIn
	&& GetZoomRate()<Parent->GetMaxZoomValue()){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		ZoomIn(Gx ,Gy);
	}
	else
	if(Parent->CurrentMode==IntegrationSimpleImagePanel::Mode_ZoomOut
	&& GetZoomRate()<Parent->GetMaxZoomValue()){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		ZoomOut(Gx ,Gy);
	}
	else{
		emit	SignalCanvasMouseLDoubleClick(globalX ,globalY);
	}
}
void	MainImagePanel::SlotMouseRDoubleClick(int globalX ,int globalY)
{
	if(Parent->CurrentMode==IntegrationSimpleImagePanel::Mode_ZoomOut
	&& GetZoomRate()>Parent->GetMinZoomValue()){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		ZoomOut(Gx ,Gy);
	}
	else{
		emit	SignalCanvasMouseRDoubleClick(globalX ,globalY);
	}
}
void	MainImagePanel::SlotShiftAll(void)
{
}

//=================================================================================================

IntegrationSimpleImagePanel::IntegrationSimpleImagePanel(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
	,ModeButton		(this)
	,DeleteButton	(this)
	,DrawWhole		(this)
	,UndoButton		(this)
	,CopyButton		(this)
	,MainCanvas(Base,this)
{
	EnableButtons.Enabled_AddItem	=true;
	EnableButtons.Enabled_AddRect	=true;
	EnableButtons.Enabled_AddLine	=false;
	EnableButtons.Enabled_Select	=true;
	EnableButtons.Enabled_CutItem	=true;
	EnableButtons.Enabled_ZoomIn	=true;
	EnableButtons.Enabled_ZoomOut	=true;
	LineWidth	=0;

	resize(100,100);
	CurrentMode	=Mode_AddItem;
	MachineCode	=0;
	ModeThoughNet=false;
	UseSelectionDialog	=false;
	RedrawMode			=true;

	MinDrawArea		=10;
	MinDrawSize		=3;
	MaxDrawArea		=2000000000;
	MaxDrawSize		=100000;

	MainCanvas	.setGeometry(geometry());
	ModeButton	.setGeometry(0  ,0,63,63);
	DeleteButton.setGeometry(64 ,0,63,63);
	DrawWhole	.setGeometry(128,0,63,63);
	UndoButton	.setGeometry(192,0,63,63);
	CopyButton	.setGeometry(256,0,63,63);

	RModeButtonEnabler=new ButtonRightClickEnabler(&ModeButton);

	ModeButton	.raise();
	DeleteButton.raise();
	DrawWhole	.raise();
	UndoButton	.raise();
	CopyButton	.raise();

	ModeButton	.setCheckable(false);
	DeleteButton.setCheckable(false);
	DrawWhole	.setCheckable(false);
	UndoButton	.setCheckable(false);
	CopyButton	.setCheckable(false);
	ModeButton	.setFont(ButtonFont);
	DeleteButton.setFont(ButtonFont);
	DrawWhole	.setFont(ButtonFont);
	UndoButton	.setFont(ButtonFont);
	CopyButton	.setFont(ButtonFont);

	connect(&ModeButton	 ,SIGNAL(clicked()),this,SLOT(SlotClickedModeButton())	);
	connect(&DeleteButton,SIGNAL(clicked()),this,SLOT(SlotClickedDeleteButton()));
	connect(&DrawWhole	 ,SIGNAL(clicked()),this,SLOT(SlotClickedDrawWhole())	);
	connect(&UndoButton	 ,SIGNAL(clicked()),this,SLOT(SlotClickedUndoButton())	);
	connect(&CopyButton	 ,SIGNAL(clicked()),this,SLOT(SlotClickedCopyButton())	);
	connect(RModeButtonEnabler,SIGNAL(RightClicked(QAbstractButton *)),this,SLOT(SlotRightClickeddModeButton(QAbstractButton *))	);
	//CopyButton.hide();

	connect(&MainCanvas ,SIGNAL(SignalCanvasMouseMove(int,int)) ,this,SLOT(SlotCanvasMouseMove(int,int)));
	connect(&MainCanvas ,SIGNAL(SignalCanvasMouseLDown(int,int)),this,SLOT(SlotCanvasMouseLDown(int,int)));
	connect(&MainCanvas ,SIGNAL(SignalCanvasMouseRDown(int,int)),this,SLOT(SlotCanvasMouseRDown(int,int)));
	connect(&MainCanvas ,SIGNAL(SignalCanvasMouseLDoubleClick(int,int)),this,SLOT(SlotMouseLDoubleClick(int,int)));
	connect(&MainCanvas ,SIGNAL(SignalCanvasMouseRDoubleClick(int,int)),this,SLOT(SlotMouseRDoubleClick(int,int)));

	connect(&MainCanvas,SIGNAL(SignalDrawEnd(void))					,this,SLOT(SlotDrawEnd(void)));
	connect(&MainCanvas,SIGNAL(SignalJustMouseLPress	(int,int))	,this,SLOT(SlotJustMouseLPress	(int,int)));
	connect(&MainCanvas,SIGNAL(SignalJustMouseRPress	(int,int))	,this,SLOT(SlotJustMouseRPress	(int,int)));
	connect(&MainCanvas,SIGNAL(SignalJustMouseLRelease	(int,int))	,this,SLOT(SlotJustMouseLRelease(int,int)));
	connect(&MainCanvas,SIGNAL(SignalJustMouseRRelease	(int,int))	,this,SLOT(SlotJustMouseRRelease(int,int)));

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	grabGesture ( Qt::PinchGesture);
}
void	IntegrationSimpleImagePanel::Prepare(void)
{
	new IntegrationReqPanelImage	(GetLayersBase(),GetDLLRoot(),GetDLLName());
	new IntegrationAckPanelImage	(GetLayersBase(),GetDLLRoot(),GetDLLName());
	new IntegrationCmdUndo			(GetLayersBase(),GetDLLRoot(),GetDLLName());
	new IntegrationCmdRedo			(GetLayersBase(),GetDLLRoot(),GetDLLName());

	MainCanvas.SetMinZoomRate(GetParamGlobal()->ZoomMin);
	MainCanvas.SetMaxZoomRate(GetParamGlobal()->ZoomMax);

	ModeButton.setToolButtonStyle(Qt::ToolButtonIconOnly);
	ModeButton.setIconSize(ModeButton.size());

	//DeleteButton.setToolButtonStyle(Qt::ToolButtonIconOnly);
	//DeleteButton.setIconSize(DeleteButton.size());
	DeleteButton.setStyleSheet(
				/**/"QPushButton {"
				/**/"image: url(:/Resources/DeleteN.png);"
				/**/"}"
				/**/"QPushButton:pressed {"
				/**/"image: url(:/Resources/DeleteP.png);"
				/**/"}"
				);
	//QIcon	DeleteIcon;
	//DeleteIcon.addPixmap(QPixmap(/**/":Resources/DeleteN.png").scaled(DeleteButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::Off);
	//DeleteIcon.addPixmap(QPixmap(/**/":Resources/DeleteP.png").scaled(DeleteButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::On);
	//DeleteButton.setIcon(DeleteIcon);

	//DrawWhole.setToolButtonStyle(Qt::ToolButtonIconOnly);
	DrawWhole.setIconSize(DrawWhole.size());
	DrawWhole.setStyleSheet(
				/**/"QPushButton {"
				/**/"image: url(:/Resources/DrawWholeN.png);"
				/**/"}"
				/**/"QPushButton:pressed {"
				/**/"image: url(:/Resources/DrawWholeP.png);"
				/**/"}"
				);
	//QIcon	DrawWholeIcon;
	//DrawWholeIcon.addPixmap(QPixmap(/**/":Resources/DrawWholeN.png").scaled(DrawWhole.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::Off);
	//DrawWholeIcon.addPixmap(QPixmap(/**/":Resources/DrawWholeP.png").scaled(DrawWhole.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::On);
	//DrawWhole.setIcon(DrawWholeIcon);

	//UndoButton.setToolButtonStyle(Qt::ToolButtonIconOnly);
	UndoButton.setIconSize(UndoButton.size());
	UndoButton.setStyleSheet(
				/**/"QPushButton {"
				/**/"image: url(:/Resources/UndoN.png);"
				/**/"}"
				/**/"QPushButton:pressed {"
				/**/"image: url(:/Resources/UndoP.png);"
				/**/"}"
				);
	//QIcon	UndoButtonIcon;
	//UndoButtonIcon.addPixmap(QPixmap(/**/":Resources/UndoN.png").scaled(UndoButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::Off);
	//UndoButtonIcon.addPixmap(QPixmap(/**/":Resources/UndoP.png").scaled(UndoButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::On);
	//UndoButton.setIcon(UndoButtonIcon);

	//CopyButton.setToolButtonStyle(Qt::ToolButtonIconOnly);
	CopyButton.setIconSize(CopyButton.size());
	CopyButton.setStyleSheet(
				/**/"QPushButton {"
				/**/"image: url(:/Resources/CopyTransferN.png);"
				/**/"}"
				/**/"QPushButton:pressed {"
				/**/"image: url(:/Resources/CopyTransferP.png);"
				/**/"}"
				);
	//QIcon	CopyButtonIcon;
	//CopyButtonIcon.addPixmap(QPixmap(/**/":Resources/CopyTransferN.png").scaled(CopyButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::Off);
	//CopyButtonIcon.addPixmap(QPixmap(/**/":Resources/CopyTransferP.png").scaled(CopyButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),QIcon::Normal,QIcon::On);
	//CopyButton.setIcon(CopyButtonIcon);

	SetMode(Mode_AddItem);
	MainCanvas.SetLineWidth(0);

	MainCanvas.Prepare();
}

int		IntegrationSimpleImagePanel::SetPropertyInDLL(PropertyClass Data[] ,WORD maxDataDim)
{
	if(maxDataDim<2)
		return -1;
	Data[0].Type					=/**/"QFont";
	Data[0].VariableNameWithRoute	=/**/"ButtonFont";
	Data[0].Pointer					=&ButtonFont;
	Data[1].Type					=/**/"int32";
	Data[1].VariableNameWithRoute	=/**/"MachineCode";
	Data[1].Pointer					=&MachineCode;

	return 2;
}

void	IntegrationSimpleImagePanel::BuildForShow(void)
{
	SetDirty(true);
}

void	IntegrationSimpleImagePanel::ResizeAction()
{
	MainCanvas.setGeometry(geometry());
}
void	IntegrationSimpleImagePanel::SetCanvasSize(int XLen,int YLen)
{
	MainCanvas.SetAreaSize(XLen,YLen);
}

void	IntegrationSimpleImagePanel::SetLineWidth(int w)
{
	LineWidth	=w;
	MainCanvas.SetLineWidth(w);
}

void	IntegrationSimpleImagePanel::SetMode(mtFrameDraw::DrawingMode mode)
{
	MainCanvas.SetMode(mode);
}

void	IntegrationSimpleImagePanel::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdLoadedMasterData		*CmdLoadedMasterDataVar=dynamic_cast<CmdLoadedMasterData *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	if(CmdLoadedMasterDataVar!=NULL || CmdUpdatedMasterImageVar!=NULL){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
		if(m==NULL)
			return;
		if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
			return;

		int	x1,y1,x2,y2;
		x1=y1=x2=y2=0;
		m->GetXY(x1,y1,x2,y2);
		SetCanvasSize(x2,y2);
		MainCanvas.ZoomDrawWhole();
		return;
	}
}
void	IntegrationSimpleImagePanel::SlotClickedModeButton	()
{
	for(;;){
		if(CurrentMode==Mode_AddItem){
			if(EnableButtons.Enabled_AddRect==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_AddRect);
				break;
			}
			CurrentMode=Mode_AddRect;
		}
		else
		if(CurrentMode==Mode_AddRect){
			if(EnableButtons.Enabled_AddLine==true){
				MainCanvas.SetLineWidth(LineWidth);
				SetMode(Mode_AddLine);
				break;
			}
			CurrentMode=Mode_AddLine;
		}
		else
		if(CurrentMode==Mode_AddLine){
			if(EnableButtons.Enabled_Select==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_Select);
				break;
			}
			CurrentMode=Mode_Select;
		}
		else
		if(CurrentMode==Mode_Select){
			if(EnableButtons.Enabled_CutItem==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_CutItem);
				break;
			}
			CurrentMode=Mode_CutItem;
		}
		else
		if(CurrentMode==Mode_CutItem){
			if(EnableButtons.Enabled_ZoomIn==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_ZoomIn);
				break;
			}
			CurrentMode=Mode_ZoomIn;
		}
		else
		if(CurrentMode==Mode_ZoomIn){
			if(EnableButtons.Enabled_ZoomOut==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_ZoomOut);
				break;
			}
			CurrentMode=Mode_ZoomOut;
		}
		else
		if(CurrentMode==Mode_ZoomOut){
			if(EnableButtons.Enabled_AddItem==true){
				MainCanvas.SetLineWidth(0);
				SetMode(Mode_AddItem);
				break;
			}
			CurrentMode=Mode_AddItem;
		}
	}
	CancelSelectionMode();
	emit	SignalModeChanged();
}
void	IntegrationSimpleImagePanel::SlotRightClickeddModeButton(QAbstractButton *obj)
{
	if(CurrentMode==Mode_AddLine){
		SetLineWidthDialog	D(GetLayersBase(),GetSlaveNo()
							,MainCanvas.GetLineWidth());
		if(D.exec()==true){
			MainCanvas.SetLineWidth(D.LineWidth);
		}
	}
}

void	IntegrationSimpleImagePanel::SlotClickedDeleteButton()
{
}
void	IntegrationSimpleImagePanel::SlotClickedDrawWhole	()
{
	MainCanvas.ZoomDrawWhole();
}
void	IntegrationSimpleImagePanel::ResetDraw(void)
{
	MainCanvas.Clear();
}
void	IntegrationSimpleImagePanel::SetCancelDraw(void)
{
	MainCanvas.SetCancelDraw();
}
void	IntegrationSimpleImagePanel::SetMode(IntegrationSimpleImagePanel::Mode d)
{
	if(d==Mode_AddItem){
		QPixmap	P(/**/":Resources/AddModeN.png");
		QSize	SZ=ModeButton.size();
		QPixmap	Q=P.scaled(SZ,Qt::KeepAspectRatio,Qt::SmoothTransformation);
		QIcon	ModeIcon(Q);
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(false);
		CurrentMode=Mode_AddItem;
		SetMode(mtFrameDraw::fdPoly);
	}
	else
	if(d==Mode_AddRect){
		QPixmap	P(/**/":Resources/AddRectModeN.png");
		QSize	SZ=ModeButton.size();
		QPixmap	Q=P.scaled(SZ,Qt::KeepAspectRatio,Qt::SmoothTransformation);
		QIcon	ModeIcon(Q);
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(false);
		CurrentMode=Mode_AddRect;
		SetMode(mtFrameDraw::fdRectangle);
	}
	else
	if(d==Mode_AddLine){
		QPixmap	P(/**/":Resources/AddLineModeN.png");
		QSize	SZ=ModeButton.size();
		QPixmap	Q=P.scaled(SZ,Qt::KeepAspectRatio,Qt::SmoothTransformation);
		QIcon	ModeIcon(Q);
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(false);
		CurrentMode=Mode_AddLine;
		SetMode(mtFrameDraw::fdChoppedLine);
	}
	else
	if(d==Mode_Select){
		QIcon	ModeIcon(QPixmap(/**/":Resources/SelModeN.png").scaled(ModeButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(true);
		SetMode(mtFrameDraw::fdPoly);
		CurrentMode=Mode_Select;
	}
	else
	if(d==Mode_CutItem){
		QIcon	ModeIcon(QPixmap(/**/":Resources/CutItemN.png").scaled(ModeButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(true);
		SetMode(mtFrameDraw::fdPoly);
		CurrentMode=Mode_CutItem;
	}
	else
	if(d==Mode_ZoomIn){
		QIcon	ModeIcon(QPixmap(/**/":Resources/ZoomModeN.png").scaled(ModeButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(false);
		SetMode(mtFrameDraw::fdNone);
		CurrentMode=Mode_ZoomIn;
	}
	else
	if(d==Mode_ZoomOut){
		QIcon	ModeIcon(QPixmap(/**/":Resources/ZoomOutModeN.png").scaled(ModeButton.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		ModeButton.setIcon(ModeIcon);
		DeleteButton.setEnabled(false);
		SetMode(mtFrameDraw::fdNone);
		CurrentMode=Mode_ZoomOut;
	}
}

void	IntegrationSimpleImagePanel::SetEnableShiftImage(bool b)
{
	MainCanvas.SetEnableShiftImage(b);
}

bool	IntegrationSimpleImagePanel::GetEnableShiftImage(void)
{
	return MainCanvas.GetEnableShiftImage();
}

void	IntegrationSimpleImagePanel::SlotCanvasMouseMove (int globalX ,int globalY)
{
}
void	IntegrationSimpleImagePanel::SlotCanvasMouseLDown(int globalX ,int globalY)
{
	if(CurrentMode==Mode_ZoomIn){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		MainCanvas.ZoomIn(Gx ,Gy);
	}
	else
	if(CurrentMode==Mode_ZoomOut){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		MainCanvas.ZoomOut(Gx ,Gy);
	}
}
void	IntegrationSimpleImagePanel::SlotCanvasMouseRDown(int globalX ,int globalY)
{
	if(CurrentMode==Mode_ZoomIn || CurrentMode==Mode_ZoomOut){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		MainCanvas.ZoomOut(Gx ,Gy);
	}
}

void	IntegrationSimpleImagePanel::SlotMouseLDoubleClick(int globalX ,int globalY)
{
}
void	IntegrationSimpleImagePanel::SlotMouseRDoubleClick(int globalX ,int globalY)
{
}
void	IntegrationSimpleImagePanel::SlotDrawEnd(void)
{
	if(CurrentMode==Mode_AddItem || CurrentMode==Mode_AddRect || CurrentMode==Mode_AddLine  || CurrentMode==Mode_CutItem || CurrentMode==Mode_Select){
		FlexArea resultarea;
		ToFlexArea( MainCanvas.GetCanvas()->SData
                                ,resultarea);
		if(MinDrawArea<=resultarea.GetPatternByte()
		&& MinDrawSize<=resultarea.GetWidth()
		&& MinDrawSize<=resultarea.GetHeight()
		&& resultarea.GetPatternByte()<=MaxDrawArea
		&& resultarea.GetWidth()<=MaxDrawSize
		&& resultarea.GetHeight()<=MaxDrawSize){
			if(CurrentMode==Mode_AddItem){
				QByteArray	Data;
				CreateCallInfoInAddItem(Data);
				DrawEndAfterOperationAddItem(resultarea,Data);
			}
			if(CurrentMode==Mode_AddRect){
				QByteArray	Data;
				CreateCallInfoInAddItem(Data);
				DrawEndAfterOperationAddItem(resultarea,Data);
			}
			if(CurrentMode==Mode_AddLine){
				QByteArray	Data;
				CreateCallInfoInAddItem(Data);
				DrawEndAfterOperationAddItem(resultarea,Data);
			}
			if(CurrentMode==Mode_CutItem){
				QByteArray	Data;
				CreateCallInfoInCut(Data);
				DrawEndAfterOperationCutItem(resultarea,Data);
			}
			if(CurrentMode==Mode_Select){
				QByteArray	Data;
				CreateCallInfoInSelect(Data);
				DrawEndAfterOperationSelectArea(resultarea,Data);
			}
		}
		MainCanvas.Clear();
	}
}

void	IntegrationSimpleImagePanel::Repaint(void)
{
	MainCanvas.repaint();
}

void	IntegrationSimpleImagePanel::SetMode(void)
{
	SetMode(CurrentMode);
}

void	IntegrationSimpleImagePanel::ZoomDraw(int movx, int movy, double zoomrate)
{
	MainCanvas.ZoomDraw(movx,movy,zoomrate);
}
bool	IntegrationSimpleImagePanel::ZoomIn(int XonG, int YonG)
{
	return MainCanvas.ZoomIn(XonG,YonG);
}
bool	IntegrationSimpleImagePanel::ZoomOut(int XonG, int YonG)
{
	return MainCanvas.ZoomOut(XonG,YonG);
}
bool	IntegrationSimpleImagePanel::SetZoom(int XonG, int YonG , double ZoomRate)
{
	return MainCanvas.SetZoom(XonG,YonG,ZoomRate);
}
bool    IntegrationSimpleImagePanel::ZoomRectG(int Gx1 ,int Gy1 ,int Gx2 ,int Gy2)
{
	return MainCanvas.ZoomRectG(Gx1,Gy1,Gx2,Gy2);
}
bool    IntegrationSimpleImagePanel::ZoomRectU(int Ux1 ,int Uy1 ,int Ux2 ,int Uy2)
{
	return MainCanvas.ZoomRectU(Ux1,Uy1,Ux2,Uy2);
}
void	IntegrationSimpleImagePanel::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
	emit	SignalJustMouseLPress  (UniversalDx,UniversalDy);
}
void	IntegrationSimpleImagePanel::SlotJustMouseRPress  (int UniversalDx,int UniversalDy)
{
	emit	SignalJustMouseRPress  (UniversalDx,UniversalDy);
}
void	IntegrationSimpleImagePanel::SlotJustMouseLRelease(int UniversalDx,int UniversalDy)
{
	emit	SignalJustMouseLRelease(UniversalDx,UniversalDy);
}
void	IntegrationSimpleImagePanel::SlotJustMouseRRelease(int UniversalDx,int UniversalDy)
{
	emit	SignalJustMouseRRelease(UniversalDx,UniversalDy);
}
bool	IntegrationSimpleImagePanel::event(QEvent *event)
{
	if (event->type() == QEvent::Gesture){
		QGestureEvent *ge=static_cast<QGestureEvent*>(event);
		if (QGesture *pinch = ge->gesture(Qt::PinchGesture)){
			QPinchGesture	*gesture=(QPinchGesture *)pinch;
			 QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
			if(changeFlags & QPinchGesture::ScaleFactorChanged){
				QPointF	P=gesture->centerPoint();
				double	ZR=gesture->scaleFactor();
				QPoint	Pi=mapFromGlobal(P.toPoint());
				MainCanvas.SetZoom(Pi.x(), Pi.y(), GetZoomRate()*ZR);
			}
		}
	}
    return GUIFormBase::event(event);
}
int		IntegrationSimpleImagePanel::GetSlaveNo(void)	const
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		return GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	}
	return -1;
}
void	IntegrationSimpleImagePanel::SlotClickedUndoButton	()
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	SlaveNo=m->GetIntegrationSlaveNo();
	IntegrationCmdUndo	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
	if(RCmd.SendReqAck(NULL,SlaveNo,0)==true){
		repaint();
	}
	emit	SignalChangedItems();
}
//=============================================================================================
IntegrationAlgoSimpleImagePanel::IntegrationAlgoSimpleImagePanel(LayersBase *Base ,const QString &AlgoRoot , const QString &AlgoName ,QWidget *parent)
	:IntegrationSimpleImagePanel(Base,parent),AlgoDLLRoot(AlgoRoot),AlgoDLLName(AlgoName)
{
	CurrentPhase		=-1;
	RCmdImage			=NULL;
	ACmdImage			=NULL;
	DrawLineColor		=Qt::red;
	//OnSelection			=false;
	OnMoving			=false;
	MoveSelectionColor	=Qt::green;
	TransferedImage		=NULL;
	TRansferedBuffer	=NULL;
	CanvasWidthDim		=NULL;
	CanvasHeightDim		=NULL;
	CanvasCountOfLayer	=NULL;
	AllocatedCount		=0;
}
IntegrationAlgoSimpleImagePanel::~IntegrationAlgoSimpleImagePanel(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		if(RCmdImage!=NULL){
			for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
				delete	RCmdImage[SlaveNo];
			}
			delete	[]RCmdImage;
			RCmdImage=NULL;
		}
		if(ACmdImage!=NULL){
			for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
				delete	ACmdImage[SlaveNo];
			}
			delete	[]ACmdImage;
			ACmdImage=NULL;
		}
		if(TransferedImage!=NULL){
			for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
				delete	[]TransferedImage[SlaveNo];
			}
			delete	[]TransferedImage;
			TransferedImage=NULL;
		}
		if(TRansferedBuffer!=NULL){
			for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
				delete	TRansferedBuffer[SlaveNo];
			}
			delete	[]TRansferedBuffer;
			TRansferedBuffer=NULL;
		}
		if(CanvasWidthDim !=NULL){
			delete	[]CanvasWidthDim;
			CanvasWidthDim=NULL;
		}
		if(CanvasHeightDim!=NULL){
			delete	[]CanvasHeightDim;
			CanvasHeightDim=NULL;
		}
		if(CanvasCountOfLayer!=NULL){
			delete	[]CanvasCountOfLayer;
			CanvasCountOfLayer=NULL;
		}
	}
}
int		IntegrationAlgoSimpleImagePanel::SetPropertyInDLL(PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=IntegrationSimpleImagePanel::SetPropertyInDLL(Data ,maxDataDim);
	if(N<0 || maxDataDim<N+1)
		return -1;
	Data[N].Type					=/**/"QColor";
	Data[N].VariableNameWithRoute	=/**/"DrawLineColor";
	Data[N].Pointer					=&DrawLineColor;

	return N+1;
}

void	IntegrationAlgoSimpleImagePanel::Prepare(void)
{
	IntegrationSimpleImagePanel::Prepare();
	SetFrameColor(DrawLineColor);
	LayersBase	*Base=GetLayersBase();
	QString	RootStr=GetDLLRoot();
	QString	NameStr=GetDLLName();
	(*Base)=new IntegrationReqAlgorithmPanelImage				(Base,RootStr,NameStr);
	(*Base)=new IntegrationAckAlgorithmPanelImage				(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelAddItem				(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelReleaseSelection	(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelMoveSelection		(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelDeleteSelectItems	(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelCutItem				(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelSelectArea			(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAckAlgorithmPanelSelectArea		(Base,RootStr,NameStr);
	(*Base)=new IntegrationCmdAlgorithmPanelSelectItems			(Base,RootStr,NameStr);

	(*Base)=new IntegrationCmdReqHasSelectedItem	(GetLayersBase(),GetDLLRoot(),GetDLLName(),-1);
	(*Base)=new IntegrationCmdAckHasSelectedItem	(GetLayersBase(),GetDLLRoot(),GetDLLName(),-1);

	(*Base)=new IntegrationCmdReqAlgoDataWithControlPoints	(GetLayersBase(),GetDLLRoot(),GetDLLName(),-1);
	(*Base)=new IntegrationCmdAckAlgoDataWithControlPoints	(GetLayersBase(),GetDLLRoot(),GetDLLName(),-1);
	(*Base)=new IntegrationCmdSetAlgoDataWithControlPoints	(GetLayersBase(),GetDLLRoot(),GetDLLName(),-1);

	if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==true)
		AllocatedCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	else
		AllocatedCount=1;
	RCmdImage	=new IntegrationReqAlgorithmPanelImage*[AllocatedCount];
	ACmdImage	=new IntegrationAckAlgorithmPanelImage*[AllocatedCount];
	for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
		RCmdImage[SlaveNo]	=new IntegrationReqAlgorithmPanelImage(Base,RootStr,NameStr,SlaveNo);
		ACmdImage[SlaveNo]	=new IntegrationAckAlgorithmPanelImage(Base,RootStr,NameStr,SlaveNo);
	}
	TransferedImage		=new BYTE*[AllocatedCount];
	TRansferedBuffer	=new BYTE*[AllocatedCount];
	CanvasWidthDim		=new int[AllocatedCount];
	CanvasHeightDim		=new int[AllocatedCount];
	CanvasCountOfLayer	=new int[AllocatedCount];
	for(int SlaveNo=0;SlaveNo<AllocatedCount;SlaveNo++){
		TransferedImage[SlaveNo]=NULL;
		TRansferedBuffer[SlaveNo]=NULL;
		CanvasWidthDim [SlaveNo]=0;
		CanvasHeightDim[SlaveNo]=0;
		CanvasCountOfLayer[SlaveNo]=0;
	}
}
void	IntegrationAlgoSimpleImagePanel::PaintFunc(QPainter &Pnt ,double ZoomRate , int movx , int movy)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	if(CurrentPhase!=Phase || RedrawMode==true){
		int	x1,y1,x2,y2;
		x1=y1=x2=y2=0;
		m->GetXY(x1,y1,x2,y2);
		SetCanvasSize(x2,y2);
		CurrentPhase=Phase;
	}
	RedrawMode=false;

	int	W=GetCanvasWidth();
	int	H=GetCanvasHeight();
	int	SlaveNo=m->GetIntegrationSlaveNo();

	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.Phase	=Phase;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.CanvasWidth	=W;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.CanvasHeight	=H;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.CountOfLayer	=GetLayerNumb(0);
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.ZoomRate		=GetZoomRate();
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.Movx			=GetMovx();
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.Movy			=GetMovy();
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.OnSelection	=HasSelectedItem();	//OnSelection;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.OnMoving		=OnMoving;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.SelectionDx	=EndSelectionX-StartSelectionX;
	RCmdImage[SlaveNo]->ReqAlgorithmPanelInfo.SelectionDy	=EndSelectionY-StartSelectionY;
	GetActiveLayer(RCmdImage[SlaveNo]->LayerList);
	AlgorithmDrawAttr	*Attr=CreateDrawAttrPointer();
	if(Attr!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		Attr->SaveAttr(&Buff);
		RCmdImage[SlaveNo]->DrawAtterData=Buff.buffer();
		delete	Attr;
	}
	RCmdImage[SlaveNo]->AlgoDLLRoot	=AlgoDLLRoot;
	RCmdImage[SlaveNo]->AlgoDLLName	=AlgoDLLName;
	
	if(RCmdImage[SlaveNo]->Send(SlaveNo,0,*ACmdImage[SlaveNo],IntegrationPanelMaxCommTime)==true){
		if(CurrentImage.width()!=ACmdImage[SlaveNo]->AckAlgorithmPanelInfo.CanvasWidth
		|| CurrentImage.height()!=ACmdImage[SlaveNo]->AckAlgorithmPanelInfo.CanvasHeight){
			CurrentImage=QImage( ACmdImage[SlaveNo]->AckAlgorithmPanelInfo.CanvasWidth
								,ACmdImage[SlaveNo]->AckAlgorithmPanelInfo.CanvasHeight
								,QImage::Format_ARGB32);
		}
		ACmdImage[SlaveNo]->ConvertToImage(CurrentImage);
		Pnt.drawImage(0,0,CurrentImage);
	}
}
AlgorithmDrawAttr	*IntegrationAlgoSimpleImagePanel::CreateDrawAttrPointer(void)
{
	AlgorithmBase	*ABase=GetAlgorithmBase();
	if(ABase!=NULL){
		AlgorithmDrawAttr	*d=ABase->CreateDrawAttr();
		if(d!=NULL){
			return d;
		}
	}
	return NULL;
}
void	IntegrationAlgoSimpleImagePanel::GetActiveLayer(IntList &LayerList)	const
{
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	LayerList.RemoveAll();
	for(int Layer=0;Layer<m->GetMaxLayerNumb();Layer++){
		LayerList.Add(Layer);
	}
}
void	IntegrationAlgoSimpleImagePanel::DrawEndAfterOperationAddItem(FlexArea &ResultArea,QByteArray &SomethingData)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	int	SlaveNo=m->GetIntegrationSlaveNo();

	IntegrationCmdAlgorithmPanelAddItem	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
	RCmd.Phase		=Phase;
	GetActiveLayer(RCmd.LayerList);
	RCmd.Area		=ResultArea;
	RCmd.AlgoDLLRoot=AlgoDLLRoot;
	RCmd.AlgoDLLName=AlgoDLLName;
	RCmd.SomethingData	=SomethingData;
	MakeDataToAddItem(ResultArea ,RCmd.Data);
	
	if(RCmd.Send(NULL,SlaveNo,0)==true){
		repaint();
		emit	SignalDrawEndAfterOperation(ResultArea);
		emit	SignalChangedItems();
	}
}
void	IntegrationAlgoSimpleImagePanel::DrawEndAfterOperationCutItem(FlexArea &ResultArea,QByteArray &SomethingData)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	int	SlaveNo=m->GetIntegrationSlaveNo();

	IntegrationCmdAlgorithmPanelCutItem	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
	RCmd.Phase		=Phase;
	GetActiveLayer(RCmd.LayerList);
	RCmd.Area		=ResultArea;
	RCmd.AlgoDLLRoot=AlgoDLLRoot;
	RCmd.AlgoDLLName=AlgoDLLName;
	RCmd.SomethingData	=SomethingData;
	if(RCmd.Send(NULL,SlaveNo,0)==true){
		repaint();
	}
	emit	SignalChangedItems();
}
void	IntegrationAlgoSimpleImagePanel::CutItemInAlgorithm	(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &LocalArea ,QByteArray &SomethingData)
{
	APage->CutArea(LocalArea ,LayerList,false,SomethingData);
}
void	IntegrationAlgoSimpleImagePanel::DrawEndAfterOperationSelectArea(FlexArea &ResultArea,QByteArray &SomethingData)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	int	SlaveNo=m->GetIntegrationSlaveNo();

	IntegrationCmdAlgorithmPanelSelectArea		RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
	RCmd.Phase		=Phase;
	GetActiveLayer(RCmd.LayerList);
	RCmd.Area		=ResultArea;
	RCmd.AlgoDLLRoot=AlgoDLLRoot;
	RCmd.AlgoDLLName=AlgoDLLName;
	RCmd.UseSelectionDialog=UseSelectionDialog;
	RCmd.SomethingData	=SomethingData;
	
	if(UseSelectionDialog==true){
		IntegrationCmdAckAlgorithmPanelSelectArea	ACmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			int	N=ACmd.SelectedContainer.GetCount();
			if(N>=2){
				SelectItemsDialog	D(GetLayersBase(),ACmd.SelectedContainer,NULL);
				connect(&D,SIGNAL(SignalTempSelectItem(const SelectedItemsInfoContainer &))
						,this,SLOT(SlotTempSelectItem(const SelectedItemsInfoContainer &)));
				connect(&D,SIGNAL(SignalTempSelectCancel())
						,this,SLOT(SlotTempSelectCancel()));

				bool	Ret=(bool)D.exec();
				if(Ret==true){
					if(D.SelectedResult.GetCount()>0){
						IntegrationCmdAlgorithmPanelSelectItems		RItemCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
						RItemCmd.SelectedContainer	=D.SelectedResult;
						RItemCmd.Send(NULL,SlaveNo,0);
					}
					else{
						ReleaseSelection();
						//SetMode(mtFrameDraw::fdPoly);
						SetMode(Mode_Select);
						CancelSelectionMode();
						//OnSelection=false;
						repaint();
						return;
					}
				}
				else{
					ReleaseSelection();
					SetMode(Mode_Select);
					CancelSelectionMode();
					//OnSelection=false;
					repaint();
					return;
				}
			}
			repaint();
			SetMode(mtFrameDraw::fdNone);
		}
	}
	else{
		if(RCmd.Send(NULL,SlaveNo,0)==true){
			repaint();
			SetMode(mtFrameDraw::fdNone);
		}
	}
}

void	IntegrationAlgoSimpleImagePanel::SlotTempSelectItem(const SelectedItemsInfoContainer &src)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	int	SlaveNo=m->GetIntegrationSlaveNo();
	if(src.GetCount()>0){
		IntegrationCmdAlgorithmPanelSelectItems		RItemCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
		RItemCmd.SelectedContainer	=src;
		RItemCmd.Send(NULL,SlaveNo,0);
	}
	Repaint();
}

void	IntegrationAlgoSimpleImagePanel::SlotTempSelectCancel()
{
	ReleaseSelection();
	Repaint();
}

void	IntegrationAlgoSimpleImagePanel::SlotClickedDeleteButton()
{
	if(GetEditMode()==true)
		return;
	if(CurrentMode==Mode_Select){		
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
		if(m==NULL)
			return;
		if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
			return;
		int	Phase=m->GetCurrentPhase();
		if(Phase<0)
			return;

		int	SlaveNo=m->GetIntegrationSlaveNo();

		IntegrationCmdAlgorithmPanelDeleteSelectItems	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
		RCmd.Phase	=Phase;
		RCmd.AlgoDLLRoot=AlgoDLLRoot;
		RCmd.AlgoDLLName=AlgoDLLName;
		QByteArray	Data;
		CreateCallInfoInDelete(Data);
		RCmd.SomethingData=Data;
		
		if(RCmd.Send(NULL,SlaveNo,0)==true){
			repaint();
		}
		SetMode(Mode_Select);
		emit	SignalChangedItems();
	}
}
void	IntegrationAlgoSimpleImagePanel::DrawImage(QImage &Image
							,double iZoomRate ,int iMovX ,int iMovY 
							,int iPhase ,IntList &iLayerList
							,QByteArray	&iDrawAtterData
							,QString &iAlgoDLLRoot ,QString &iAlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(iAlgoDLLRoot ,iAlgoDLLName);
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(iPhase);
		if(Ah!=NULL){
			AlgorithmDrawAttr	*Attr=NULL;
			Attr=CreateDrawAttrPointer();
			if(Attr!=NULL){
				QBuffer	Buff(&iDrawAtterData);
				Buff.open(QIODevice::ReadOnly);
				Attr->LoadAttr(&Buff);
			}
			ClearImage(Image,0);
			//Image.fill(Qt::black);
			for(int page=0;page<GetPageNumb();page++){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
				if(Ap!=NULL){
					XYData	*XY=Ap->GetOutlineOffset();
					//Ap->Draw(CurrentImage, iLayerList ,iMovX+XY->x ,iMovY+XY->y ,iZoomRate ,Attr);
					Ap->Draw(Image, iLayerList ,iMovX+XY->x ,iMovY+XY->y ,iZoomRate ,Attr);
					if(tOnMoving==true){
						//Ap->DrawMove(tSelectionDx ,tSelectionDy,CurrentImage, iMovX ,iMovY ,iZoomRate ,MoveSelectionColor,Attr);
						Ap->DrawMove(tSelectionDx ,tSelectionDy,Image, iMovX ,iMovY ,iZoomRate ,MoveSelectionColor,Attr);
					}
				}
			}
			if(Attr!=NULL){
				delete	Attr;
			}
		}
	}
}

void	IntegrationAlgoSimpleImagePanel::MakeImageBuff(BYTE  *ImageBuff 
							,int CanvasWidth,int CanvasHeight,int CountOfLayer
							,double iZoomRate ,int iMovX ,int iMovY 
							,int iPhase ,IntList &iLayerList
							,QByteArray	&iDrawAtterData
							,QString &iAlgoDLLRoot ,QString &iAlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	if(CurrentImage.width()!=CanvasWidth
	|| CurrentImage.height()!=CanvasHeight){
		CurrentImage=QImage( CanvasWidth
							,CanvasHeight
							,QImage::Format_ARGB32);
	}
	ClearImage(CurrentImage,0x0);
	DrawImage(CurrentImage
			,iZoomRate ,iMovX ,iMovY 
			,iPhase ,iLayerList
			,iDrawAtterData
			,iAlgoDLLRoot ,iAlgoDLLName
			,tOnSelection
			,tOnMoving
			,tSelectionDx,tSelectionDy);
	int	W4=CanvasWidth*(CountOfLayer+1);
	if(CountOfLayer==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<CanvasHeight;y++){
				QRgb	*s=(QRgb *)CurrentImage.scanLine(y);
				BYTE	*d=&ImageBuff[y*W4];
				for(int x=0;x<CanvasWidth;x++){
					*d=qRed(*s);
					*(d+1)=qAlpha(*s);
					d+=2;
					s++;
				}
			}
		}
	}
	else
	if(CountOfLayer==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<CanvasHeight;y++){
				QRgb	*s=(QRgb *)CurrentImage.scanLine(y);
				BYTE	*d=&ImageBuff[y*W4];
				for(int x=0;x<CanvasWidth;x++){
					*d	  =qRed(*s);
					*(d+1)=qGreen(*s);
					*(d+2)=qAlpha(*s);
					d+=3;
					s++;
				}
			}
		}
	}
	else
	if(CountOfLayer>=3){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<CanvasHeight;y++){
				QRgb	*s=(QRgb *)CurrentImage.scanLine(y);
				BYTE	*d=&ImageBuff[y*W4];
				for(int x=0;x<CanvasWidth;x++){
					*d	  =qRed(*s);
					*(d+1)=qGreen(*s);
					*(d+2)=qBlue(*s);
					*(d+3)=qAlpha(*s);
					d+=4;
					s++;
				}
			}
		}
	}
}
AlgorithmBase	*IntegrationAlgoSimpleImagePanel::GetAlgorithmBase(void)	const
{
	return GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot,AlgoDLLName);
}

void	IntegrationAlgoSimpleImagePanel::SelectItem(int Phase,IntList &LayerList, FlexArea &Area,SelectedItemsInfoContainer &RetSelectedContainer,QByteArray &SomethingData)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				IntList	PageList;
				GetLayersBase()->GetLocalPageFromArea(Area,PageList);
				for(IntClass *v=PageList.GetFirst();v!=NULL;v=v->GetNext()){
					int	Page=v->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(Page);
					AlgorithmInPageRoot	*Ap=Ah->GetPageData(Page);
					if(Ap!=NULL && pdata!=NULL){
						FlexArea	A=Area;
						pdata->ClipMoveAreaFromGlobal(A);
						if(A.GetPatternByte()>0){
							Ap->SelectItems(A ,LayerList,false);
							AlgorithmItemPointerListContainer ItemPointers;
							Ap->GetSelectedItems(ItemPointers);
							for(AlgorithmItemPointerList *t=ItemPointers.GetFirst();t!=NULL;t=t->GetNext()){
								SelectedItemsInfo	*p=new SelectedItemsInfo();
								p->Phase=Phase;
								p->Page	=Page;
								p->Layer=t->GetItem()->GetLayer();
								p->ItemID	=t->GetItem()->GetID();
								p->ItemName	=t->GetItem()->GetItemName();
								p->Comment	=t->GetItem()->GetComment(_TypeItemComment_Normal);
								RetSelectedContainer.AppendList(p);
							}
						}
					}
				}
			}
		}
	}
}

void	IntegrationAlgoSimpleImagePanel::SelectItem(SelectedItemsInfoContainer &SelectedContainer)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			Ab->ReleaseAllSelectedItem();

			for(int Phase=0;Phase<GetPhaseNumb();Phase++){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
				for(int page=0;page<GetPageNumb();page++){
					ListLayerAndIDPack SelectedItem;
					for(SelectedItemsInfo *a=SelectedContainer.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Phase==Phase && a->Page==page){
							ListLayerAndID	*d=new ListLayerAndID();
							d->Layer=a->Layer;
							d->ID	=a->ItemID;
							SelectedItem.AppendList(d);
						}
					}
					if(SelectedItem.GetCount()>0){
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
						Ap->SelectItemByID(SelectedItem);
					}
				}
			}
		}
	}
}
void	IntegrationAlgoSimpleImagePanel::DelSelectedItemsInAlgorithm(int SlaveNo
																	,AlgorithmInPageRoot *APage 
																	,IntList &LayerList
																	,QByteArray &SomethingData)
{
	APage->DeleteSelectedItems(LayerList);
}

void	IntegrationAlgoSimpleImagePanel::ReleaseSelection(void)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;

	int	SlaveNo=m->GetIntegrationSlaveNo();

	IntegrationCmdAlgorithmPanelReleaseSelection	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);

	RCmd.AlgoDLLRoot=AlgoDLLRoot;
	RCmd.AlgoDLLName=AlgoDLLName;	
	if(RCmd.Send(NULL,SlaveNo,0)==true){
		repaint();
	}
}
void	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseLDown(int globalX ,int globalY)
{
	if(CurrentMode==Mode_Select){
		if(GetEditMode()==true)
			return;
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
		if(m==NULL)
			return;
		if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
			return;
		int	SlaveNo=m->GetIntegrationSlaveNo();

		if(HasSelectedItem()==false){
			//SetMode(mtFrameDraw::fdPoly);
			//OnSelection=true;
			OnMoving		=true;
			EndSelectionX	=StartSelectionX=globalX;
			EndSelectionY	=StartSelectionY=globalY;
		}
		else{
			if(OnMoving==false){
				OnMoving		=true;
				EndSelectionX	=StartSelectionX=globalX;
				EndSelectionY	=StartSelectionY=globalY;
			}
			else{
				IntegrationCmdAlgorithmPanelMoveSelection	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
				RCmd.Dx	=globalX-StartSelectionX;
				RCmd.Dy	=globalY-StartSelectionY;
				RCmd.AlgoDLLRoot=AlgoDLLRoot;
				RCmd.AlgoDLLName=AlgoDLLName;	
				if(RCmd.Send(NULL,SlaveNo,0)==true){
					repaint();
					//OnSelection=false;
					//SetMode(mtFrameDraw::fdPoly);
				}
				OnMoving=false;
				emit	SignalChangedItems();
			}
		}
	}
	else{
		IntegrationSimpleImagePanel::SlotCanvasMouseLDown(globalX ,globalY);
	}
}
void	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseRDown(int globalX ,int globalY)
{
	if(CurrentMode==Mode_Select){
		if(HasSelectedItem()==true || GetCanvas()->GetMode()==mtFrameDraw::fdNone){
			if(OnMoving==false){
				ReleaseSelection();
				SetMode(mtFrameDraw::fdPoly);
				CancelSelectionMode();
				//OnSelection=false;
			}
			else{
				OnMoving=false;
			}
		}
	}
	IntegrationSimpleImagePanel::SlotCanvasMouseRDown(globalX ,globalY);
}
void	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseMove (int globalX ,int globalY)
{
	if(CurrentMode==Mode_Select){
		if(HasSelectedItem()==true && OnMoving==true){
			EndSelectionX	=globalX;
			EndSelectionY	=globalY;
		}
	}
	else{
		IntegrationSimpleImagePanel::SlotCanvasMouseMove(globalX ,globalY);
	}
}
void	IntegrationAlgoSimpleImagePanel::ExecuteMoveItems(const QString &tAlgoDLLRoot ,const QString &tAlgoDLLName ,int GlobalDx ,int GlobalDy)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(tAlgoDLLRoot ,tAlgoDLLName);
		if(Ab!=NULL){
			for(int localPage=0;localPage<GetPageNumb();localPage++){
				Ab->ExecuteMove(localPage ,GlobalDx,GlobalDy);
			}
		}
	}
}
bool	IntegrationAlgoSimpleImagePanel::HasSelectedItem(void)
{
	if(GetEditMode()==true)
		return false;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return false;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return false;
	int	SlaveNo=m->GetIntegrationSlaveNo();
	for(int page=0;page<m->GetPageNumb();page++){
		IntegrationCmdReqHasSelectedItem	RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
		IntegrationCmdAckHasSelectedItem	ACmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
		RCmd.Phase		=m->GetCurrentPhase();
		RCmd.AlgoDLLRoot=AlgoDLLRoot;
		RCmd.AlgoDLLName=AlgoDLLName;
		int	LocalPage=m->GetLocalPageFromGlobal(page);
		if(RCmd.Send(SlaveNo,LocalPage,ACmd,IntegrationPanelMaxCommTime)==true){
			if(ACmd.SelectedItemCount!=0){
				return true;
			}
		}
	}
	return false;
}

void	IntegrationAlgoSimpleImagePanel::SlotClickedCopyButton()
{
	if(GetLayersBase()->GetShadowLevel()==0){
		int SlaveCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		if(SlaveCount>1){
			CopyAlgorithmDialog	D(GetLayersBase(),this);
			D.exec();
		}
	}
}

void	IntegrationAlgoSimpleImagePanel::CopyFromSlave(int SlaveNo)
{
	EachMaster	*TargetM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(TargetM==NULL)
		return;

	AlgoListInPageContainer	AlgoListInPageData;
	for(int page=0;page<TargetM->GetPageNumb();page++){
		for(int phase=0;phase<TargetM->GetPhaseNumb();phase++){
		    IntegrationCmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
			RCmd.Phase=phase;
			RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
			RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
			RootNameList RetRootName;
			GetAlgorithmBase()->GetAlgorithmRootName(RetRootName);
			RCmd.AlgorithmList.Merge(RetRootName);
		    IntegrationCmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),SlaveNo);
			int	LocalPage=TargetM->GetLocalPageFromGlobal(page);
		    if(RCmd.Send(SlaveNo,LocalPage,ACmd)==true){
				AlgoListInPage	*a=new AlgoListInPage();
				a->Phase=phase;
				a->Page=page;
				a->ControlPointsForPages=ACmd.ControlPointsForPages;
				a->AlgoList	=ACmd.AlgoList;
				AlgoListInPageData.AppendList(a);
		    }
		}
	}

	EachMaster	*OwnM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(OwnM==NULL)
		return;
	for(int page=0;page<OwnM->GetPageNumb();page++){
		for(int phase=0;phase<OwnM->GetPhaseNumb();phase++){
			AlgoListInPage *Point=NULL;
			for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Phase==phase && a->Page==page){
					Point=a;
					break;
				}
			}
			if(Point==NULL){
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase){
						Point=a;
						break;
					}
				}
			}
			if(Point!=NULL){
				IntegrationCmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),OwnM->GetIntegrationSlaveNo());
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
				RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
				RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
				RCmd.AlgoList		=Point->AlgoList;
				RCmd.GUIRoot		=GetDLLRoot();
				RCmd.GUIName		=GetDLLName();
				int	LocalPage=OwnM->GetLocalPageFromGlobal(page);
				RCmd.Send(NULL,OwnM->GetIntegrationSlaveNo(),LocalPage);
			}
		}
	}
}
void	IntegrationAlgoSimpleImagePanel::CopyToSlave(IntList &DestSlaveList,bool ClearBeforeCopy)
{
	EachMaster	*OwnM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(OwnM==NULL)
		return;

	QByteArray	CopyToSlaveInfo;
	MakeCopyToSlaveInfo(CopyToSlaveInfo);

	AlgoListInPageContainer	AlgoListInPageData;
	for(int page=0;page<OwnM->GetPageNumb();page++){
		int	LocalPage=OwnM->GetLocalPageFromGlobal(page);
		for(int phase=0;phase<OwnM->GetPhaseNumb();phase++){
			IntegrationCmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),OwnM->GetIntegrationSlaveNo());
			RCmd.Phase=phase;
			RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
			RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
			RootNameList RetRootName;
			GetAlgorithmBase()->GetAlgorithmRootName(RetRootName);
			RCmd.AlgorithmList.Merge(RetRootName);
			RCmd.CopyToSlaveInfo=CopyToSlaveInfo;
			RCmd.DLLRoot=GetDLLRoot();
			RCmd.DLLName=GetDLLName();
		    IntegrationCmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),OwnM->GetIntegrationSlaveNo());
		    if(RCmd.Send(OwnM->GetIntegrationSlaveNo(),LocalPage,ACmd)==true){
				AlgoListInPage	*a=new AlgoListInPage();
				a->Phase=phase;
				a->Page=page;
				a->ControlPointsForPages=ACmd.ControlPointsForPages;
				a->AlgoList	=ACmd.AlgoList;
				AlgoListInPageData.AppendList(a);
		    }
		}
	}
	for(IntClass *v=DestSlaveList.GetFirst();v!=NULL;v=v->GetNext()){
		int	DestSlaveNo=v->GetValue();
		EachMaster	*DstM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(DestSlaveNo);
		if(DstM==NULL)
			return;
		for(int page=0;page<DstM->GetPageNumb();page++){
			for(int phase=0;phase<DstM->GetPhaseNumb();phase++){
				AlgoListInPage *Point=NULL;
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase && a->Page==page){
						Point=a;
						break;
					}
				}
				if(Point==NULL){
					for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Phase==phase){
							Point=a;
							break;
						}
					}
				}
				if(Point!=NULL){
					int	LocalPage=OwnM->GetLocalPageFromGlobal(page);
					IntegrationCmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),GetDLLRoot(),GetDLLName(),DstM->GetIntegrationSlaveNo());
					RCmd.Phase=phase;
					RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
					RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
					RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
					RCmd.AlgoList		=Point->AlgoList;
					RCmd.GUIRoot		=GetDLLRoot();
					RCmd.GUIName		=GetDLLName();
					RCmd.ClearBeforeCopy=ClearBeforeCopy;
					RCmd.Send(NULL,DstM->GetIntegrationSlaveNo(),LocalPage);
				}
			}
		}
	}
}

bool	IntegrationAlgoSimpleImagePanel::SaveCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot *Ap,TransformBase	*Param,bool ClearBeforeCopy)
{
	QBuffer	Buff(&InfoData);
	Buff.open(QIODevice::ReadWrite);
	if(ClearBeforeCopy==true){
		Ap->RemoveAllDatas();
	}
	return Ap->LoadByTransform(&Buff,*Param);
}
