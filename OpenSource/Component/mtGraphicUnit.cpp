/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtGraphicUnit.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>

#include "mtMeter.h"
#include "mtGraphicUnit.h"
#include "swap.h"
#include "mtPushButtonWithBalloon.h"


mtQFrameDrawInGUnit::mtQFrameDrawInGUnit(mtGraphicUnit *mparent ,QWidget *parent)
:mtFrameDraw(parent)
{
	Parent	=mparent;
	SetZoomRate(1.0);
	SetMovXY(0,0);
	AreaSizeX=100;
	AreaSizeY=100;
}

void	mtQFrameDrawInGUnit::mousePressEvent ( QMouseEvent *Ev )
{	
	mtFrameDraw::mousePressEvent(Ev); 
	Parent->LaunchSignalMousePressEvent(Ev);
}

void	mtQFrameDrawInGUnit::SlotDrawEnd(void)
{
	Parent->LaunchSignalDrawEnd();
}
void	mtQFrameDrawInGUnit::SlotDrawing(mtFrameDraw::DrawingMode mode,int stage)
{
	Parent->LaunchSignalDrawing(mode,stage);
}
void	mtQFrameDrawInGUnit::SlotCancelDraw(void)
{
	Parent->LaunchSignalCancelDraw();
}
void	mtQFrameDrawInGUnit::SlotOnPaint(QPainter &pnt)
{
	Parent->LaunchSignalOnPaint(pnt);
}

void	mtGraphicUnit::LaunchSignalDrawEnd(void)
{
	emit	SignalDrawEnd();
}
void	mtGraphicUnit::LaunchSignalDrawing(mtFrameDraw::DrawingMode mode,int stage)
{
	emit	SignalDrawing(mode,stage);
}
void	mtGraphicUnit::LaunchSignalCancelDraw(void)
{
	emit	SignalCancelDraw();
}
void	mtGraphicUnit::LaunchSignalOnPaint(QPainter &pnt)
{
	emit	SignalOnPaint(pnt);
}

void	mtQFrameDrawInGUnit::wheelEvent ( QWheelEvent * event )
{
	emit	SignalWheel(event);
}
void	mtQFrameDrawInGUnit::mtMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid)
{
	mtFrameDraw::mtMousePoint(Ev ,x ,y ,valid);
	Parent->LaunchSignalMousePoint(Ev ,x ,y ,valid);
}
void	mtQFrameDrawInGUnit::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDraw::mtMouseLDown(Ev ,x ,y);
	Parent->LaunchSignalMouseLDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDraw::mtMouseRDown(Ev ,x ,y);
	Parent->LaunchSignalMouseRDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseMove(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDraw::mtMouseMove(Ev ,x ,y);
	Parent->LaunchSignalMouseMove(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseLUp(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDraw::mtMouseLDown(Ev ,x ,y);
	emit	SignalMouseLUp(x/GetZoomRate()-GetMovX(),y/GetZoomRate()-GetMovY());
	Parent->LaunchSignalMouseLUp(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseRUp(QMouseEvent *Ev ,int x ,int y)
{
	mtFrameDraw::mtMouseRDown(Ev ,x ,y);
	Parent->LaunchSignalMouseRUp(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::ShiftPressed(int gx ,int gy)
{
	Parent->LaunchSignalShiftPressed(gx ,gy);
}


mtScrollBar::mtScrollBar( mtGraphicUnit *mparent ,Qt::Orientation orientation,QWidget *parent)
:QScrollBar(orientation,parent)
{
	Parent	=mparent;
}

void mtScrollBar::sliderChange ( SliderChange change )
{
	if(Parent->IsInnerFuncMode()==true){
		return;
	}
	if(orientation ()==Qt::Horizontal){
		Parent->GetCanvas()->SetMovX(-Parent->GetHScroll()->value());
		Parent->GetHScroll()->repaint(0,0,Parent->GetHScroll()->width(),Parent->GetHScroll()->height());
	}
	else{
		Parent->GetCanvas()->SetMovY(-Parent->GetVScroll()->value());
		Parent->GetVScroll()->repaint(0,0,Parent->GetVScroll()->width()
										 ,Parent->GetVScroll()->height());
	}
	Parent->SetMeter();
	Parent->GetCanvas()->RepaintAll();
	Parent->LaunchSignalScrollDraw();
}

void mtScrollBar::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtScrollBar::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}

mtGraphicUnit::mtGraphicUnit(QWidget *parent				
							,bool	_EnableMeasure
							,bool	_EnableToolArea
							,bool	_EnableVScroller
							,bool	_EnableHScroller
							,bool	_EnableZoom
							,bool	_EnableMove
							,bool	_EnableFitZoom)
    : mtWidgetPosition(parent)
{
	FirstTime	=true;

	EnableMeasure	=_EnableMeasure		;
	EnableToolArea	=_EnableToolArea	;
	EnableVScroller	=_EnableVScroller	;
	EnableHScroller	=_EnableHScroller	;
	EnableZoom		=_EnableZoom		;
	EnableMove		=_EnableMove		;
	EnableFitZoom	=_EnableFitZoom		;
	FVerticalMerginRate		=0.1;
	FHorizontalMerginRate	=0.1;
	UseLongPush		=false;
	LongPushMilisec	=1000;

	InsideFunc	=0;
	if(EnableMeasure==true){
		MeterTop	=new mtMeter(this);
		MeterTop->SetDrawMode(mtMeter::mtHorizLower);
		MeterLeft	=new mtMeter(this);
		MeterLeft->SetDrawMode(mtMeter::mtVertRight);
	}
	else{
		MeterTop=NULL;
		MeterLeft=NULL;
	}

	ScrollerWidth=16;
	if(EnableHScroller==true){
		HScroll	=new mtScrollBar(this,Qt::Horizontal,this);
		LeftPageBtn	=new mtPushButtonWithBalloon(this);
		RightPageBtn=new mtPushButtonWithBalloon(this);
	}
	else{
		HScroll		=NULL;
		LeftPageBtn	=NULL;
		RightPageBtn=NULL;
	}
	if(EnableVScroller==true){
		VScroll	=new mtScrollBar(this,Qt::Vertical,this);
		UpPageBtn	=new mtPushButtonWithBalloon(this);
		DownPageBtn	=new mtPushButtonWithBalloon(this);
	}
	else{
		VScroll		=NULL;
		UpPageBtn	=NULL;
		DownPageBtn	=NULL;
	}
	if(EnableFitZoom==true){
		FitZoomBtn	=new mtPushButtonWithBalloon(this);
	}
	else{
		FitZoomBtn=NULL;
	}

	FrDraw =new mtQFrameDrawInGUnit(this,this);
	FZoomRateMin=0.001;
	FZoomRateMax=100;
	resize(400, 400);


	connect(FrDraw,SIGNAL(SignalDrawEnd(void))		,this,SLOT(SlotDrawEnd(void)));
	connect(FrDraw,SIGNAL(SignalDrawing(mtFrameDraw::DrawingMode,int))		,this,SLOT(SlotDrawing(mtFrameDraw::DrawingMode,int)));
	connect(FrDraw,SIGNAL(SignalCancelDraw(void))	,this,SLOT(SlotCancelDraw(void)));
	connect(FrDraw,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(FrDraw,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
	connect(FrDraw,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
	connect(FrDraw,SIGNAL(SignalKeyPress(int,QPoint,bool &)),this,SLOT(SlotKeyPress(int,QPoint,bool &)));
	connect(FrDraw,SIGNAL(SignalDoubleClick(QMouseEvent *)),this,SLOT(SlotDoubleClick(QMouseEvent *)));
	connect(FrDraw,SIGNAL(SignalWheel(QWheelEvent*)),this,SLOT(SlotWheel(QWheelEvent*)));
	connect(FrDraw,SIGNAL(SignalShiftCanvas(int,int)),this,SLOT(SlotShiftCanvas(int,int)));
	connect(FrDraw,SIGNAL(SignalDrawMessage(const QStringList &,const QStringList &))	,this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
	connect(FrDraw,SIGNAL(SignalJustMouseLPress	(int,int))	,this,SLOT(SlotJustMouseLPress	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseRPress	(int,int))	,this,SLOT(SlotJustMouseRPress	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseLRelease(int,int))	,this,SLOT(SlotJustMouseLRelease	(int,int)));
	connect(FrDraw,SIGNAL(SignalJustMouseRRelease(int,int))	,this,SLOT(SlotJustMouseRRelease	(int,int)));

	bool	ModeEnterLeave=false;
	if(VScroll!=NULL){
		connect(VScroll,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(VScroll,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(HScroll!=NULL && ModeEnterLeave==false){
		connect(HScroll,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(HScroll,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(MeterTop!=NULL && ModeEnterLeave==false){
		connect(MeterTop,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(MeterTop,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(MeterLeft!=NULL && ModeEnterLeave==false){
		connect(MeterLeft,SIGNAL(SignalEnter())			,this,SLOT(SlotEnter()));
		connect(MeterLeft,SIGNAL(SignalLeave())			,this,SLOT(SlotLeave()));
		ModeEnterLeave=true;
	}
	if(UpPageBtn!=NULL){
		connect(UpPageBtn,SIGNAL(clicked())		,this,SLOT(SlotUpPageButtonDown		()));
	}
	if(DownPageBtn!=NULL){
		connect(DownPageBtn,SIGNAL(clicked())	,this,SLOT(SlotDownPageButtonDown	()));
	}
	if(LeftPageBtn!=NULL){
		connect(LeftPageBtn,SIGNAL(clicked())	,this,SLOT(SlotLeftPageButtonDown	()));
	}
	if(RightPageBtn!=NULL){
		connect(RightPageBtn,SIGNAL(clicked())	,this,SLOT(SlotRightPageButtonDown	()));
	}
	if(FitZoomBtn!=NULL){
		connect(FitZoomBtn,SIGNAL(clicked())	,this,SLOT(SlotFitZoomBtnDown	()));
	}
}


mtGraphicUnit::~mtGraphicUnit(void)
{
	disconnect(this,SLOT(SlotDrawEnd(void)));
	disconnect(this,SLOT(SlotDrawing(mtFrameDraw::DrawingMode,int)));
	disconnect(this,SLOT(SlotCancelDraw(void)));
	disconnect(this,SLOT(SlotOnPaint(QPainter &)));
	disconnect(this,SLOT(SlotEnter()));
	disconnect(this,SLOT(SlotLeave()));
	disconnect(this,SLOT(SlotKeyPress(int,QPoint,bool &)));
	disconnect(this,SLOT(SlotDoubleClick(QMouseEvent *)));
	disconnect(this,SLOT(SlotWheel(QWheelEvent*)));
	disconnect(this,SLOT(SlotShiftCanvas(int,int)));
	disconnect(this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
	disconnect(this,SLOT(SlotJustMouseLPress	(int,int)));
	disconnect(this,SLOT(SlotJustMouseRPress	(int,int)));
	disconnect(this,SLOT(SlotJustMouseLRelease	(int,int)));
	disconnect(this,SLOT(SlotJustMouseRRelease	(int,int)));
	disconnect(this,SLOT(SlotUpPageButtonDown		()));
	disconnect(this,SLOT(SlotDownPageButtonDown	()));
	disconnect(this,SLOT(SlotLeftPageButtonDown	()));
	disconnect(this,SLOT(SlotRightPageButtonDown	()));
	disconnect(this,SLOT(SlotFitZoomBtnDown	()));

	delete	MeterTop;
	delete	MeterLeft;
	delete	VScroll;
	delete	HScroll;
	delete	FrDraw;
	delete	FitZoomBtn;
	delete	UpPageBtn;
	delete	DownPageBtn;
	delete	LeftPageBtn;
	delete	RightPageBtn;

	MeterTop	=NULL;
	MeterLeft	=NULL;
	VScroll		=NULL;
	HScroll		=NULL;
	FrDraw		=NULL;
	FitZoomBtn	=NULL;
	UpPageBtn	=NULL;
	DownPageBtn	=NULL;
	LeftPageBtn	=NULL;
	RightPageBtn=NULL;
}


void mtGraphicUnit::resizeEvent ( QResizeEvent *event)
{
	int	x1=0;
	int	y1=0;
	int	W=width();
	int	H=height();
	int	CWidth=W;
	int	CHeight=H;

	if(MeterTop!=NULL){
		if(MeterLeft!=NULL){
			MeterTop ->setGeometry ( 16, 0, CWidth -32, 16 );
		}
		else{
			MeterTop ->setGeometry ( 0, 0, CWidth -16, 16 );
		}
		y1=16;
		H-=16;
	}
	if(MeterLeft!=NULL){
		if(MeterTop!=NULL){
			MeterLeft->setGeometry ( 0 , 16,16, CHeight -32 );
		}
		else{
			MeterLeft->setGeometry ( 0 , 0,16, CHeight-16 );
		}
		x1=16;
		W-=16;
	}
	int	VScrollWidth=ScrollerWidth;
	if(VScroll!=NULL){
		if(MeterTop!=NULL){
			VScroll	->setGeometry (CWidth -1-VScrollWidth, 16, VScrollWidth, CHeight -32 -16);
		}
		else{
			VScroll	->setGeometry (CWidth -1-VScrollWidth, 0, VScrollWidth, CHeight -32);
		}
		W-=VScrollWidth;
	}
	int	HScrollHeight=ScrollerWidth;
	if(HScroll!=NULL){
		if(MeterLeft!=NULL){
			HScroll	->setGeometry ( 16 , CHeight -1-HScrollHeight, CWidth -32-16, HScrollHeight);
		}
		else{
			HScroll	->setGeometry ( 0 , CHeight -1-HScrollHeight, CWidth -32, HScrollHeight);
		}
		H-=HScrollHeight;
	}
	FrDraw->setGeometry (x1,y1,W,H);

	if(UpPageBtn!=NULL){
		UpPageBtn	->setGeometry (CWidth -1-VScrollWidth,0,16,16);
	}
	if(DownPageBtn!=NULL){
		DownPageBtn	->setGeometry (CWidth -1-VScrollWidth, CHeight -32,16,16);
	}
	if(LeftPageBtn!=NULL){
		LeftPageBtn	->setGeometry (0, CHeight -1-HScrollHeight,16,16);
	}
	if(RightPageBtn!=NULL){
		RightPageBtn->setGeometry (CWidth -32, CHeight -1-HScrollHeight,16,16);
	}
	if(FitZoomBtn!=NULL){
		FitZoomBtn->setGeometry (0,0,16,16);
	}
	//QWidget::resizeEvent ( event );
	SetWindowPos();

	if(FirstTime==true && GetCanvasWidth()>0){
		ZoomDrawWhole();
		FirstTime=false;
	}
	update();
	if(event!=NULL){
		QWidget::resizeEvent(event);
		event->accept();
	}
}

mtQFrameDrawInGUnit	*mtGraphicUnit::GetCanvas(void)	const
{
	return(FrDraw);
}
void	mtGraphicUnit::ZoomDraw( int movx, int movy, double ZoomRate)
{
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	ZoomDrawFree(movx, movy, ZoomRate);
}
void	mtGraphicUnit::ZoomDrawFree(int movx, int movy, double zoomrate)
{
	FrDraw->SetMovXY(movx,movy);
	FrDraw->SetZoomRate(zoomrate);
	
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}

bool	mtGraphicUnit::ZoomIn(int XonG, int YonG)
{
	double	ZoomRate=GetZoomRate()*2;
	if(ZoomRate<FZoomRateMin){
		return false;
	}
	if(FZoomRateMax<ZoomRate){
		return false;
	}

    int LX=(int)((double)XonG/ZoomRate);
    int LY=(int)((double)YonG/ZoomRate);
	ZoomDrawFree(GetMovx()-LX, GetMovy()-LY,ZoomRate);
	return true;
}

bool	mtGraphicUnit::ZoomOut(int XonG, int YonG)
{
	double	OldZoomRate=GetZoomRate();
	double	tZoomRate=GetZoomRate()/2.0;
	if(tZoomRate<FZoomRateMin){
		return false;
	}
	double	Z=OldZoomRate/tZoomRate;
	int LX=(int)((double)XonG/(tZoomRate*Z));
	int LY=(int)((double)YonG/(tZoomRate*Z));
	ZoomDrawFree(GetMovx()+LX, GetMovy()+LY, tZoomRate);
	return true;
}

bool	mtGraphicUnit::SetZoom(int XonG, int YonG , double _ZoomRate)
{
	if(FZoomRateMin<=_ZoomRate && _ZoomRate<=FZoomRateMax){
	    int LX=(int)((double)XonG/GetZoomRate());
		int LY=(int)((double)YonG/GetZoomRate());
	    int LXNew=(int)((double)XonG/_ZoomRate);
		int LYNew=(int)((double)YonG/_ZoomRate);
		ZoomDraw(GetMovx()-LX+LXNew, GetMovy()-LY+LYNew, _ZoomRate);
		return true;
	}
	return false;
}

bool    mtGraphicUnit::ZoomRectG(int Gx1 ,int Gy1 ,int Gx2 ,int Gy2)
{
    int cx=(Gx2+Gx1)/2;
    int cy=(Gy2+Gy1)/2;
    int Ux=abs(Gx2-Gx1);
    int Uy=abs(Gy2-Gy1);

    cx=cx/GetZoomRate()-GetMovx();
    cy=cy/GetZoomRate()-GetMovy();
    Ux=Ux/GetZoomRate();
    Uy=Uy/GetZoomRate();

    double  ZX,ZY;
	if(Ux>0){
        ZX=(double)(double)GetCanvas()->width()/Ux;
	}
	else{
        ZX=FZoomRateMax;
	}
	if(Uy>0){
        ZY=(double)(double)GetCanvas()->height()/Uy;
	}
	else{
        ZY=FZoomRateMax;
	}
    double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(FZoomRateMin<=ZoomRate && ZoomRate<=FZoomRateMax){
	    int	movx=GetCanvas()->width()/2/ZoomRate - cx;
		int	movy=GetCanvas()->height()/2/ZoomRate- cy;
		ZoomDraw(movx, movy, ZoomRate);
		return true;
	}
	return false;
}

bool    mtGraphicUnit::ZoomRectU(int Ux1 ,int Uy1 ,int Ux2 ,int Uy2)
{
    int cx=(Ux2+Ux1)/2;
    int cy=(Uy2+Uy1)/2;
    int Ux=abs(Ux2-Ux1);
    int Uy=abs(Uy2-Uy1);

    double  ZX,ZY;
	if(Ux>0){
        ZX=(double)(double)GetCanvas()->width()/Ux;
	}
	else{
        ZX=FZoomRateMax;
	}
	if(Uy>0){
        ZY=(double)(double)GetCanvas()->height()/Uy;
	}
	else{
        ZY=FZoomRateMax;
	}
	double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(FZoomRateMin<=ZoomRate && ZoomRate<=FZoomRateMax){
		int	movx=GetCanvas()->width()/2/ZoomRate - cx;
		int	movy=GetCanvas()->height()/2/ZoomRate- cy;
		ZoomDraw(movx, movy, ZoomRate);
		return true;
	}
	return false;
}

double	mtGraphicUnit::GetZoomRateForWhole(void)	const
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZX=((double)vW)/((double)GetCanvas()->AreaSizeX);
    double	ZY=((double)vH)/((double)GetCanvas()->AreaSizeY);
    double	ZoomRate=(ZX>ZY)?ZY:ZX;
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	return ZoomRate;
}

void	mtGraphicUnit::ZoomDrawWhole(void)
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZoomRate=GetZoomRateForWhole();
	int	GW=GetCanvas()->AreaSizeX*ZoomRate;
	int	GH=GetCanvas()->AreaSizeY*ZoomRate;
	int	XSpare=(vW-GW)/2;
	int	YSpare=(vH-GH)/2;

	ZoomDraw(XSpare/ZoomRate, YSpare/ZoomRate, ZoomRate);
}

double	mtGraphicUnit::GetZoomRateForFit(void)	const
{
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	double	ZX=((double)vW)/((double)GetCanvas()->AreaSizeX);
    double	ZY=((double)vH)/((double)GetCanvas()->AreaSizeY);
    double	ZoomRate=(ZX<ZY)?ZY:ZX;
	if(ZoomRate<FZoomRateMin){
		ZoomRate=FZoomRateMin;
	}
	if(FZoomRateMax<ZoomRate){
		ZoomRate=FZoomRateMax;
	}
	return ZoomRate;
}
void	mtGraphicUnit::ZoomDrawFit(void)
{
	double	ZoomRate=GetZoomRateForFit();
	int	vW=GetCanvas()->width();
	int	vH=GetCanvas()->height();
	int	GW=GetCanvas()->AreaSizeX*ZoomRate;
	int	GH=GetCanvas()->AreaSizeY*ZoomRate;
	int	XSpare=(vW-GW)/2;
	int	YSpare=(vH-GH)/2;

	ZoomDraw(XSpare/ZoomRate, YSpare/ZoomRate, ZoomRate);
}
void	mtGraphicUnit::SetScrollerWidth(int w)
{	
	ScrollerWidth=w;
}
void	mtGraphicUnit::SetFModeRepaintOnMouseMove(bool b)
{
	GetCanvas()->SetFModeRepaintOnMouseMove(b);
}
bool	mtGraphicUnit::GetFModeRepaintOnMouseMove(void)
{
	return GetCanvas()->GetFModeRepaintOnMouseMove();
}
void	mtGraphicUnit::Repaint(void)
{
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnit::SetAreaSize(int xlen ,int ylen)
{
	if(xlen>0)
		FrDraw->AreaSizeX=xlen;
	if(ylen>0)
		FrDraw->AreaSizeY=ylen;
}

class	MMQWidget : public QWidget
{
public:
	void KeyPressEvent ( QKeyEvent * event )	{	keyPressEvent(event);	}
	void KeyReleaseEvent ( QKeyEvent * event )	{	keyReleaseEvent(event);	}
};


void	mtGraphicUnit::keyPressEvent(QKeyEvent * event )
{
	((MMQWidget *)FrDraw)->KeyPressEvent(event);
}
void	mtGraphicUnit::SetMerginRate(double Hr,double Vr)
{
	FVerticalMerginRate		=Hr;
	FHorizontalMerginRate	=Vr;
}
void	mtGraphicUnit::SetSlider(void)
{
	InsideFunc++;

	if(HScroll!=NULL){
		int	MinV=FrDraw->AreaSizeX*(-FHorizontalMerginRate)/GetZoomRate();
		int	MaxV=FrDraw->AreaSizeX*(1.0+FHorizontalMerginRate)/GetZoomRate();
		int	Range=FrDraw->width()/GetZoomRate();
		HScroll->setMinimum (MinV);
		HScroll->setMaximum (MaxV-Range);
		HScroll->setPageStep(Range);
		int	XPos=-GetMovx();
		HScroll->setValue(XPos);
		HScroll->repaint();

	}

	if(VScroll!=NULL){
		int	MinV=FrDraw->AreaSizeY*(-FVerticalMerginRate)/GetZoomRate();
		int	MaxV=FrDraw->AreaSizeY*(1.0+FVerticalMerginRate)/GetZoomRate();
		int	Range=FrDraw->height()/GetZoomRate();
		VScroll->setMinimum (MinV);
		VScroll->setMaximum (MaxV-Range);
		VScroll->setPageStep(Range);
		int	YPos=-GetMovy();
		VScroll->setValue(YPos);
		VScroll->repaint();
	}

	InsideFunc--;

}
void	mtGraphicUnit::DrawAdd(int UOffx, int UOffy)
{
	InsideFunc++;

	FrDraw->SetMovXY(FrDraw->GetMovX()+UOffx,FrDraw->GetMovY()+UOffy);

	if(HScroll!=NULL){
		int	NowH=HScroll->sliderPosition();
		NowH-=UOffx;
		HScroll->setSliderPosition(NowH);
		HScroll->repaint();
		HScroll->setValue(-GetMovx());
	}

	if(VScroll!=NULL){
		int	NowV=VScroll->sliderPosition();
		NowV-=UOffy;
		VScroll->setSliderPosition(NowV);
		VScroll->repaint();
		VScroll->setValue(-GetMovy());
	}

	SetMeter();
	GetCanvas()->RepaintAll();

	InsideFunc--;
}

void	mtGraphicUnit::SetDrawOffset(int UMovx ,int UMovy)
{
	InsideFunc++;

	FrDraw->SetMovXY(UMovx,UMovy);

	if(HScroll!=NULL){
		int	NowH=-UMovx;
		HScroll->setSliderPosition(NowH);
		HScroll->repaint();
		HScroll->setValue(-GetMovx());
	}
	if(VScroll!=NULL){
		int	NowV=-UMovx;
		VScroll->setSliderPosition(NowV);
		VScroll->repaint();
		VScroll->setValue(-GetMovy());
	}
	SetMeter();
	GetCanvas()->RepaintAll();

	InsideFunc--;
}


void	mtGraphicUnit::SetMeter(void)
{
	if(MeterTop!=NULL){
		MeterTop	->SetZoomRate	 (GetZoomRate());
		MeterTop	->SetLeftPosition(-GetMovx());
	}
	if(MeterLeft!=NULL){
		MeterLeft	->SetZoomRate(GetZoomRate());
		MeterLeft	->SetLeftPosition(-GetMovy());
	}
}

void	mtGraphicUnit::Clear(void)
{
	if(FrDraw!=NULL){
		FrDraw->Clear();
	}
}

void	mtGraphicUnit::SetCancelDraw(void)
{
	if(FrDraw!=NULL){
		FrDraw->SetCancelDraw();
	}
}
void	mtGraphicUnit::SetCursor(mtFrameDraw::DrawingMode mode)
{
	FrDraw->SetCursor(mode);
}
void	mtGraphicUnit::LaunchSignalMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid)
{
}
void	mtGraphicUnit::LaunchSignalMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	if((Ev->modifiers() & Qt::ShiftModifier)==0){
		emit	SignalMouseLDown(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->modifiers() & Qt::ShiftModifier)!=0){
		emit	SignalMouseLDownWithShift(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}
void	mtGraphicUnit::LaunchSignalMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	if((Ev->modifiers() & Qt::ShiftModifier)==0){
		emit	SignalMouseRDown(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->modifiers() & Qt::ShiftModifier)!=0){
		emit	SignalMouseRDownWithShift(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}
void	mtGraphicUnit::LaunchSignalMouseMove(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseMove(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}
void	mtGraphicUnit::LaunchSignalMouseLUp(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseLUp(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}
void	mtGraphicUnit::LaunchSignalMouseRUp(QMouseEvent *Ev ,int x ,int y)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMouseRUp(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
}

void	mtGraphicUnit::SlotWheel(QWheelEvent * e)
{
	QPoint numDegrees = e->angleDelta();
	//int	D=e->delta();
	int	D=numDegrees.y();
	int	X=e->position().x()/FrDraw->GetZoomRate()-FrDraw->GetMovX();
	int	Y=e->position().y()/FrDraw->GetZoomRate()-FrDraw->GetMovY();
	emit	SignalMouseWheel(D,X,Y);
}

void	mtGraphicUnit::LaunchSignalShiftPressed(int gx ,int gy)
{
	emit	SignalShiftPressed(gx ,gy);
}

void	mtGraphicUnit::LaunchSignalMousePressEvent(QMouseEvent *Ev)
{
	StateMouseButtons=Ev->buttons();
	emit	SignalMousePressEvent(Ev);
}

void	mtGraphicUnit::SlotDrawEnd(void)
{
}
void	mtGraphicUnit::SlotDrawing(mtFrameDraw::DrawingMode mode,int stage)
{
}
void	mtGraphicUnit::SlotCancelDraw(void)
{
}
void	mtGraphicUnit::SlotOnPaint(QPainter &pnt)
{
}
void	mtGraphicUnit::SlotMouseMove(int globalX,int globalY)
{
}
void	mtGraphicUnit::SlotMouseLDown(int globalX,int globalY)
{
}
void	mtGraphicUnit::SlotMouseLUp(int globalX,int globalY)
{
}
void	mtGraphicUnit::SlotMouseRDown(int globalX,int globalY)
{
}
void	mtGraphicUnit::SlotMouseRUp(int globalX,int globalY)
{
}
void mtGraphicUnit::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtGraphicUnit::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}

void	mtGraphicUnit::SlotEnter()
{
	emit	SignalEnter();
}
void	mtGraphicUnit::SlotLeave()
{
	emit	SignalLeave();
}

void	mtGraphicUnit::SlotKeyPress(int key ,QPoint RawPos,bool &Accept)
{
	emit	SignalKeyPress(key,RawPos.x(),RawPos.y() ,Accept);
}

bool	mtGraphicUnit::IsIncludeInCanvas(QPoint &P)	const
{
	if(0<=P.x() && P.x()<GetCanvas()->width() && 0<=P.y() && P.y()<GetCanvas()->height()){
		return true;
	}
	return false;
}

void	mtGraphicUnit::SetMouseCursorPos(int XonG, int YonG)
{
	GetCanvas()->SetMouseCursorPos(XonG, YonG);
}

void	mtGraphicUnit::ExecuteMouseMove(int XonG, int YonG)
{
	GetCanvas()->ExecuteMouseMove(XonG, YonG);
}

void	mtGraphicUnit::LaunchSignalScrollDraw(void)
{
	emit	SignalScrollDraw();
}
void	mtGraphicUnit::SlotDoubleClick(QMouseEvent *Ev)
{
	int	x=Ev->x();
	int	y=Ev->y();
	StateMouseButtons=Ev->buttons();

	if((Ev->buttons()&Qt::LeftButton)!=0){
		emit	SignalMouseLDoubleClick(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
	else if((Ev->buttons()&Qt::RightButton)!=0){
		emit	SignalMouseRDoubleClick(x/FrDraw->GetZoomRate()-FrDraw->GetMovX() ,y/FrDraw->GetZoomRate()-FrDraw->GetMovY());
	}
}

void	mtGraphicUnit::SlotUpPageButtonDown()
{
    int	movy=GetCanvas()->height()/2/GetZoomRate();
	FrDraw->SetMovY(FrDraw->GetMovY()+movy);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnit::SlotDownPageButtonDown()
{
    int	movy=GetCanvas()->height()/2/GetZoomRate();
	FrDraw->SetMovY(FrDraw->GetMovY()-movy);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnit::SlotLeftPageButtonDown()
{
    int	movx=GetCanvas()->width()/2/GetZoomRate();
	FrDraw->SetMovX(FrDraw->GetMovX()+movx);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnit::SlotRightPageButtonDown()
{
    int	movx=GetCanvas()->width()/2/GetZoomRate();
	FrDraw->SetMovX(FrDraw->GetMovX()-movx);
	SetSlider();
	SetMeter();
	GetCanvas()->RepaintAll();
}
void	mtGraphicUnit::SlotFitZoomBtnDown()
{
    ZoomDrawWhole();
	GetCanvas()->RepaintAll();
	emit	SignalFitZoom();
}
void	mtGraphicUnit::SlotShiftCanvas(int UniversalDx,int UniversalDy)
{
	if(EnableMove==true){
		FrDraw->SetMovX(FrDraw->GetMovX()+UniversalDx/GetZoomRate());
		FrDraw->SetMovY(FrDraw->GetMovY()+UniversalDy/GetZoomRate());
		SetSlider();
		SetMeter();
		GetCanvas()->RepaintAll();
		emit	SignalShiftAll();
	}
}
void	mtGraphicUnit::SlotDrawMessage(const QStringList &title ,const QStringList &msg)
{
	emit	SignalDrawMessage(title ,msg);

}
void	mtGraphicUnit::DrawFromOutside(QStringList &data)
{
	FrDraw->DrawFromOutside(data);
}
	
void	mtGraphicUnit::SetEnableShiftImage(bool b)
{
	FrDraw->SetEnableShiftImage(b);
}
bool	mtGraphicUnit::GetEnableShiftImage(void)	const
{
	return FrDraw->GetEnableShiftImage();
}

void	mtGraphicUnit::SetCrossLineMode(bool mode ,const QColor &Col)
{
	FrDraw->SetCrossLineMode(mode ,Col);
}

void	mtGraphicUnit::SetMeterOffset(int OffsetX ,int OffsetY)
{
	if(MeterTop!=NULL){
		MeterTop->SetOffsetValue(OffsetX);
	}
	if(MeterLeft!=NULL){
		MeterLeft->SetOffsetValue(OffsetY);
	}
}

void	mtGraphicUnit::GetMeterOffset(int &OffsetX ,int &OffsetY)
{
	if(MeterTop!=NULL){
		OffsetX	=MeterTop->GetOffsetValue();
	}
	else{
		OffsetX=0;
	}
	if(MeterLeft!=NULL){
		OffsetY	=MeterLeft->GetOffsetValue();
	}
	else{
		OffsetY	=0;
	}
}
void	mtGraphicUnit::SlotJustMouseLPress  (int UniversalDx,int UniversalDy)
{
	PushedTimeer.start();
	emit	SignalJustMouseLPress  (UniversalDx,UniversalDy);
}
void	mtGraphicUnit::SlotJustMouseLRelease(int UniversalDx,int UniversalDy)
{
	if(UseLongPush==false || PushedTimeer.hasExpired(LongPushMilisec)==false){
		emit	SignalJustMouseLRelease(UniversalDx,UniversalDy);
	}
	else{
		emit	SignalJustMouseLLongPress(UniversalDx,UniversalDy);
	}
}
void	mtGraphicUnit::SlotJustMouseRPress  (int UniversalDx,int UniversalDy)
{
	PushedTimeer.start();
	emit	SignalJustMouseRPress  (UniversalDx,UniversalDy);
}
void	mtGraphicUnit::SlotJustMouseRRelease(int UniversalDx,int UniversalDy)
{
	if(UseLongPush==false || PushedTimeer.hasExpired(LongPushMilisec)==false){
		emit	SignalJustMouseRRelease(UniversalDx,UniversalDy);
	}
	else{
		emit	SignalJustMouseRLongPress(UniversalDx,UniversalDy);
	}
}
