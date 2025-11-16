/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtFrameDraw3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>
#include <QString>
#include <QStringList>

#include "mtFrameDraw3D.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include "XCrossObj.h"
#include <QtGlobal>


mtFrameDraw3D::mtFrameDraw3D(QWidget *parent)
	: QWidget(parent)
{
	static	bool	Initialized=false;
	resize(400, 400);
	DrawStartEvent			=NULL;

	//Cursor				=crDefault;
	FDrawMode				=fdNone;
	DrawStage				=0;
	FCancelDraw				=false;
	FOnDrawMode				=false;
	FEnableShiftImage		=true;
	//FCrossOnMoving		=false;
	FArrowLength			=30;
	setMouseTracking(true);
	NowGx=NowGy				=0;
	LastMouseDownPointX		=0;
	LastMouseDownPointY		=0;
	LastShitX				=0;
	LastShitY				=0;
	ShiftingMode			=false;
	LeftClicked				=false;
	RightClicked			=false;
	DblClickMode			=false;
	NoShiftCanvasMode		=false;
	ImageShiftDelay			= 0;
	FModeCrossLine			=false;
	FCrossLineColor			=Qt::yellow;
	FModeRepaintOnMouseMove	=true;
	CancelClicked			=false;
	LineWidth				=0.0;

	connect(this,SIGNAL(SignalDrawEnd(void))	,this,SLOT(SlotDrawEnd(void)));
	connect(this,SIGNAL(SignalDrawing(mtFrameDraw3D::DrawingMode,int))	,this,SLOT(SlotDrawing(mtFrameDraw3D::DrawingMode,int)));
	connect(this,SIGNAL(SignalCancelDraw(void))	,this,SLOT(SlotCancelDraw(void)));
	connect(this,SIGNAL(SignalOnPaint(QPainter &))	,this,SLOT(SlotOnPaint(QPainter &)));
	qRegisterMetaType<mtFrameDraw3D::DrawingMode>("mtFrameDraw3D::DrawingMode");
	//grabKeyboard ();

	if(Initialized==false){
		Q_INIT_RESOURCE(mtFrameDraw3D);
		Initialized=true;
	}
}

mtFrameDraw3D::~mtFrameDraw3D()
{
	disconnect(this,SLOT(SlotDrawEnd(void)));
	disconnect(this,SLOT(SlotDrawing(mtFrameDraw3D::DrawingMode,int)));
	disconnect(this,SLOT(SlotCancelDraw(void)));
	disconnect(this,SLOT(SlotOnPaint(QPainter &)));
}

void	mtFrameDraw3D::SlotDrawEnd(void)
{
//	setCursor(QCursor(Qt::ArrowCursor));
}
void	mtFrameDraw3D::SlotDrawing(mtFrameDraw3D::DrawingMode,int)
{
}
void	mtFrameDraw3D::SlotCancelDraw(void)
{
}
void	mtFrameDraw3D::SlotOnPaint(QPainter &pnt)
{
}
	
void	mtFrameDraw3D::GetZoomRate(double &ZoomRateX ,double &ZoomRateY)	const
{
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);
}

bool	mtFrameDraw3D::GetMovxy(double &movx ,double &movy)	const
{
	return CInfo.GetMovXY(movx,movy);
}

void	mtFrameDraw3D::SetCrossLineMode(bool mode ,const QColor &Col)
{
	FModeCrossLine	=mode;
	FCrossLineColor	=Col;
}
void	mtFrameDraw3D::SetMode(DrawingMode Value)
{
	if(FDrawMode==fdLine){
		SData.UData.LineData.x=0;
		SData.UData.LineData.y=0;
		SData.UData.LineData.s=0;
	}
	else if(FDrawMode==fdHalfLine){
		SData.UData.HalfLineData.x=0;
		SData.UData.HalfLineData.y=0;
		SData.UData.HalfLineData.s=0;
	}
	else if(FDrawMode==fdChoppedLine){
		SData.UData.ChoppedLineData.x1=0;
		SData.UData.ChoppedLineData.y1=0;
		SData.UData.ChoppedLineData.x2=0;
		SData.UData.ChoppedLineData.y2=0;
	}
	else if(FDrawMode==fdRectangle){
		SData.UData.RectangleData.x1=0;
		SData.UData.RectangleData.y1=0;
		SData.UData.RectangleData.x2=0;
		SData.UData.RectangleData.y2=0;
	}
	else if(FDrawMode==fdRotRectangle){
		SData.UData.RotRectangleData.cx=0;
		SData.UData.RotRectangleData.cy=0;
		SData.UData.RotRectangleData.rx=0;
		SData.UData.RotRectangleData.ry=0;
		SData.UData.RotRectangleData.s =0;
	}
	else if(FDrawMode==fdCircle){
		SData.UData.CircleData.cx=0;
		SData.UData.CircleData.cy=0;
		SData.UData.CircleData.r=0;
	}
	else if(FDrawMode==fdEllipse || FDrawMode==fdEllipse4){
		SData.UData.EllipseData.cx=0;
		SData.UData.EllipseData.cy=0;
		SData.UData.EllipseData.rx=0;
		SData.UData.EllipseData.ry=0;
	}
	else if(FDrawMode==fdRotEllipse){
		SData.UData.RotEllipseData.cx=0;
		SData.UData.RotEllipseData.cy=0;
		SData.UData.RotEllipseData.rx=0;
		SData.UData.RotEllipseData.ry=0;
		SData.UData.RotEllipseData.s =0;
	}
	else if(FDrawMode==fdArc){
		SData.UData.ArcData.cx=0;
		SData.UData.ArcData.cy=0;
		SData.UData.ArcData.r=0;
		SData.UData.ArcData.s1=0;
		SData.UData.ArcData.s2=0;
	}
	else if(FDrawMode==fdRing){
		SData.UData.ERingData.cx =0;
		SData.UData.ERingData.cy =0;
		SData.UData.ERingData.rx1=0;
		SData.UData.ERingData.ry1=0;
		SData.UData.ERingData.rx2=0;
		SData.UData.ERingData.ry2=0;
	}
	else if(FDrawMode==fdSingleArrow){
		SData.UData.SingleArrowLineData.x1=0;
		SData.UData.SingleArrowLineData.y1=0;
		SData.UData.SingleArrowLineData.x2=0;
		SData.UData.SingleArrowLineData.y2=0;
	}
	else if(FDrawMode==fdDualArrow){
		SData.UData.DualArrowLineData.x1=0;
		SData.UData.DualArrowLineData.y1=0;
		SData.UData.DualArrowLineData.x2=0;
		SData.UData.DualArrowLineData.y2=0;
	}
	else if(FDrawMode==fdFree){
		if(SData.UData.FreeData.points!=NULL){
			SData.UData.FreeData.points->RemoveAll();
			delete SData.UData.FreeData.points;
			}
		SData.UData.FreeData.points=NULL;
		}
	else if(FDrawMode==fdPoly){
		if(SData.UData.PolyData.points!=NULL){
			SData.UData.PolyData.points->RemoveAll();
			delete SData.UData.PolyData.points;
			}
		SData.UData.PolyData.points=NULL;
		}
	else if(FDrawMode==fdMove){
		if(SData.UData.MoveData.points!=NULL){
			SData.UData.MoveData.points->RemoveAll();
			delete SData.UData.MoveData.points;
			}
		SData.UData.MoveData.points=NULL;
		}
	else if(FDrawMode==fdRingArc1 || FDrawMode==fdRingArc4){
		SData.UData.RingArcData.cx=0;
		SData.UData.RingArcData.cy=0;
		SData.UData.RingArcData.rx1=0;
		SData.UData.RingArcData.ry1=0;
		SData.UData.RingArcData.rx2=0;
		SData.UData.RingArcData.ry2=0;
		SData.UData.RingArcData.s1=0;
		SData.UData.RingArcData.s2=0;
	}
	SData.LineWidth	=LineWidth;
	DrawStage=0;
	ChangeMode(Value);

//	  FDrawMode=Value;
	if(FDrawMode==fdLine
	|| FDrawMode==fdChoppedLine
	|| FDrawMode==fdHChoppedLine
	|| FDrawMode==fdVChoppedLine
	|| FDrawMode==fdSingleArrow
	|| FDrawMode==fdDualArrow
	|| FDrawMode==fdArc
	|| FDrawMode==fdArc3
	|| FDrawMode==fdRingArc1
	|| FDrawMode==fdRingArc4)
		FClosedArea=false;
	else if(   FDrawMode==fdRectangle
			|| FDrawMode==fdRotRectangle
			|| FDrawMode==fdCircle
			|| FDrawMode==fdCircle3
			|| FDrawMode==fdEllipse
			|| FDrawMode==fdEllipse4
			|| FDrawMode==fdRotEllipse
			|| FDrawMode==fdRing){
		FClosedArea=true;
	}

	if(FDrawMode==fdFree){
		SData.UData.FreeData.points = new NPListPack<ShapePoint3D>();
		}
	else if(FDrawMode==fdPoly){
		SData.UData.PolyData.points = new NPListPack<ShapePoint3D>();
		}
	else if(FDrawMode==fdMove){
		SData.UData.MoveData.points=new NPListPack<ShapePoint3D>();
		}
	SetStartCursor();
	SData.dtype=Value;
	FOnDrawMode=false;
}

void	mtFrameDraw3D::paintEvent(QPaintEvent *event)
{
	setUpdatesEnabled(false);

	PaintMutex.lock();
	QPainter	Pnt(this);
	PaintMutex.unlock();

	emit SignalOnPaint(Pnt);

	if(DrawStage>0){
		PaintMutex.lock();

		Pnt.setPen(FColor);
		Pnt.setBrush(FColor);

		int		x1,y1,x2,y2,x3,y3,x4,y4;
		int		mx1,my1,mx2,my2;
		int		nx1,ny1,nx2,ny2;
		double	s,s1,s2;
		double	s11,s12;
		double	s21,s22;

		double	movx;
		double	movy;
		CInfo.GetMovXY(movx,movy);
		double	ZoomRateX,ZoomRateY;
		CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

		int		MinDataGx=-movx;
		int		MinDataGy=-movy;
		int		MaxDataGx=width()/ZoomRateX-movx;
		int		MaxDataGy=height()/ZoomRateY-movy;


		switch(FDrawMode){
			case fdPoint	:
				DrawLineZoom(Pnt
							,SData.UData.PointData.x+movx,SData.UData.PointData.y+movy
							,SData.UData.PointData.x+movx,SData.UData.PointData.y+movy
							,ZoomRateX,ZoomRateY);
				break;
			case fdLine:
				if(1.75*M_PI<=SData.UData.LineData.s || SData.UData.LineData.s<=0.25*M_PI){
					DrawLineZoom(Pnt
								,MinDataGx+movx	,-tan(SData.UData.LineData.s)*SData.UData.LineData.x			+SData.UData.LineData.y+movy
								,MaxDataGx+movx ,tan(SData.UData.LineData.s)*(MaxDataGx-SData.UData.LineData.x)+SData.UData.LineData.y+movy
								,ZoomRateX,ZoomRateY);
				}
				else if(0.75*M_PI>=SData.UData.LineData.s){
					DrawLineZoom(Pnt
								,(-cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*SData.UData.LineData.y				+SData.UData.LineData.x+movx)	,(MinDataGy+movy)
								,(cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*(MaxDataGy-SData.UData.LineData.y)	+SData.UData.LineData.x+movx)	,(MaxDataGy+movy)
								,ZoomRateX,ZoomRateY);
				}
				else if(1.25*M_PI>=SData.UData.LineData.s){
					DrawLineZoom(Pnt
								,MinDataGx+movx	,(-tan(SData.UData.LineData.s)*SData.UData.LineData.x			+SData.UData.LineData.y+movy)
								,MaxDataGx+movx	,(tan(SData.UData.LineData.s)*(MaxDataGx-SData.UData.LineData.x)+SData.UData.LineData.y+movy)
								,ZoomRateX,ZoomRateY);
				}
				else{
					DrawLineZoom(Pnt
								,(-cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*SData.UData.LineData.y				+SData.UData.LineData.x+movx),(MinDataGy+movy)
								,( cos(SData.UData.LineData.s)/sin(SData.UData.LineData.s)*(MaxDataGy-SData.UData.LineData.y)	+SData.UData.LineData.x+movx),(MaxDataGy+movy)
								,ZoomRateX,ZoomRateY);
				}
				break;

			case fdHalfLine	:
				if(1.75*M_PI<=SData.UData.HalfLineData.s || SData.UData.HalfLineData.s<=0.25*M_PI){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx,SData.UData.HalfLineData.y+movy
								,MaxDataGx+movx					,tan(SData.UData.HalfLineData.s)*(MaxDataGx-SData.UData.HalfLineData.x)	+SData.UData.HalfLineData.y+movy
								,ZoomRateX,ZoomRateY);
				}
				else if(0.75*M_PI>=SData.UData.HalfLineData.s){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx																										,SData.UData.HalfLineData.y+movy
								,cos(SData.UData.HalfLineData.s)/sin(SData.UData.HalfLineData.s)*(MaxDataGy-SData.UData.HalfLineData.y)	+SData.UData.HalfLineData.x+movx,MaxDataGy+movy
								,ZoomRateX,ZoomRateY);
				}
				else if(1.25*M_PI>=SData.UData.HalfLineData.s){
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx,SData.UData.HalfLineData.y+movy
								,MinDataGx+movx					,-tan(SData.UData.HalfLineData.s)*SData.UData.HalfLineData.x	+SData.UData.HalfLineData.y+movy
								,ZoomRateX,ZoomRateY);
				}
				else{
					DrawLineZoom(Pnt
								,SData.UData.HalfLineData.x+movx																								,SData.UData.HalfLineData.y+movy
								,-cos(SData.UData.HalfLineData.s)/sin(SData.UData.HalfLineData.s)*SData.UData.HalfLineData.y +SData.UData.HalfLineData.x+movx	,MinDataGy+movy
								,ZoomRateX,ZoomRateY);
				}
				break;

			case fdChoppedLine:
			case fdHChoppedLine:
			case fdVChoppedLine:
				DrawLineZoom(Pnt
							,SData.UData.ChoppedLineData.x1+movx	,SData.UData.ChoppedLineData.y1+movy
							,SData.UData.ChoppedLineData.x2+movx	,SData.UData.ChoppedLineData.y2+movy
							,ZoomRateX,ZoomRateY);
				break;

			case fdRectangle:
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y1+movy
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y1+movy
							,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y1+movy
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y2+movy
							,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x2+movx,SData.UData.RectangleData.y2+movy
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y2+movy
							,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y2+movy
							,SData.UData.RectangleData.x1+movx,SData.UData.RectangleData.y1+movy
							,ZoomRateX,ZoomRateY);
				break;
			case fdRotRectangle:
				x1=(SData.UData.RotRectangleData.cx-SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y1=(SData.UData.RotRectangleData.cy+SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x2=(SData.UData.RotRectangleData.cx+SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y2=(SData.UData.RotRectangleData.cy-SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)-SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x3=(SData.UData.RotRectangleData.cx+SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y3=(SData.UData.RotRectangleData.cy-SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				x4=(SData.UData.RotRectangleData.cx-SData.UData.RotRectangleData.rx*cos(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*sin(-SData.UData.RotRectangleData.s)+movx);
				y4=(SData.UData.RotRectangleData.cy+SData.UData.RotRectangleData.rx*sin(-SData.UData.RotRectangleData.s)+SData.UData.RotRectangleData.ry*cos(-SData.UData.RotRectangleData.s)+movy);
				DrawLineZoom(Pnt,x1,y1 ,x2,y2	,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt,x2,y2 ,x3,y3	,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt,x3,y3 ,x4,y4	,ZoomRateX,ZoomRateY);
				DrawLineZoom(Pnt,x4,y4 ,x1,y1	,ZoomRateX,ZoomRateY);
				break;
			case fdCircle:
				Pnt.drawArc( (SData.UData.CircleData.cx-SData.UData.CircleData.r+movx)*ZoomRateX	,(SData.UData.CircleData.cy-SData.UData.CircleData.r+movy)*ZoomRateY
							,2*SData.UData.CircleData.r*ZoomRateX,2*SData.UData.CircleData.r*ZoomRateY
							,0,5760);
				break;
			case fdCircle3:
				Pnt.drawArc( (SData.UData.CircleData.cx-SData.UData.CircleData.r+movx)*ZoomRateX	,(SData.UData.CircleData.cy-SData.UData.CircleData.r+movy)*ZoomRateY
							,2*SData.UData.CircleData.r*ZoomRateX,2*SData.UData.CircleData.r*ZoomRateY
							,0,5760);
				if(DrawStage==1){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRateX-2	,(TmpPoint[0][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==2){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRateX-2	,(TmpPoint[0][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRateX-2	,(TmpPoint[1][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==3){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRateX-2	,(TmpPoint[0][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRateX-2	,(TmpPoint[1][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[2][0]+movx)*ZoomRateX-2	,(TmpPoint[2][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
				}
				break;
			case fdEllipse:
			case fdEllipse4:
				Pnt.drawArc( (SData.UData.EllipseData.cx-SData.UData.EllipseData.rx+movx)*ZoomRateX,(SData.UData.EllipseData.cy-SData.UData.EllipseData.ry+movy)*ZoomRateY
							,2*SData.UData.EllipseData.rx*ZoomRateX,2*SData.UData.EllipseData.ry*ZoomRateY
							,0,5760);
				break;
			case fdRotEllipse:
				DrawRotEllipse(Pnt);
				break;
			case fdArc:
				s=SData.UData.ArcData.s2-SData.UData.ArcData.s1;
				while(s<0){
					s+=2.0*M_PI;
				}

				Pnt.drawArc( (SData.UData.ArcData.cx-SData.UData.ArcData.r+movx)*ZoomRateX	,(SData.UData.ArcData.cy-SData.UData.ArcData.r+movy)*ZoomRateY
							,2*SData.UData.ArcData.r*ZoomRateX,2*SData.UData.ArcData.r*ZoomRateY
							//,5760*SData.UData.ArcData.s1/(2*M_PI),5760*SData.UData.ArcData.s2/(2*M_PI));
							,5760*(1.0-SData.UData.ArcData.s2/(2*M_PI))
							,5760*s/(2*M_PI));
				break;
			case fdArc3:
				if(DrawStage==1){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRateX-2	,(TmpPoint[0][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
				}
				else if(DrawStage==2){
					Pnt.drawArc( (TmpPoint[0][0]+movx)*ZoomRateX-2	,(TmpPoint[0][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
					Pnt.drawArc( (TmpPoint[1][0]+movx)*ZoomRateX-2	,(TmpPoint[1][1]+movy)*ZoomRateY-2
								,5,5
								,0,5760);
					
					s=SData.UData.ArcData.s2-SData.UData.ArcData.s1;
					while(s<0){
						s+=2.0*M_PI;
					}

					Pnt.drawArc( (SData.UData.ArcData.cx-SData.UData.ArcData.r+movx)*ZoomRateX	,(SData.UData.ArcData.cy-SData.UData.ArcData.r+movy)*ZoomRateY
								,2*SData.UData.ArcData.r*ZoomRateX,2*SData.UData.ArcData.r*ZoomRateY
								//,5760*SData.UData.ArcData.s1/(2*M_PI),5760*SData.UData.ArcData.s2/(2*M_PI));
								,5760*(1.0-SData.UData.ArcData.s2/(2*M_PI))
								,5760*s/(2*M_PI));
				}
				break;
			case fdFree:
				for(ShapePoint3D	*p=SData.UData.FreeData.points->GetFirst();p!=NULL;p=p->GetNext()){
					ShapePoint3D	*q=p->GetNext();
					if(q==NULL){
						break;
					}
					DrawLineZoom(Pnt
								,p->x+movx	,p->y+movy
								,q->x+movx	,q->y+movy
								,ZoomRateX,ZoomRateY);
				}
				break;
			case fdPoly:
				for(ShapePoint3D	*p=SData.UData.PolyData.points->GetFirst();p!=NULL;p=p->GetNext()){
					ShapePoint3D	*q=p->GetNext();
					if(q==NULL){
						DrawLineZoom(Pnt
							,p->x+movx	,p->y+movy
							,rotx+movx	,roty+movy
							,ZoomRateX,ZoomRateY);
						break;
					}
					DrawLineZoom(Pnt
								,p->x+movx	,p->y+movy
								,q->x+movx	,q->y+movy
								,ZoomRateX,ZoomRateY);
				}
				break;
			case fdSingleArrow:
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRateY
							,(SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY);
				s=GetSita(SData.UData.SingleArrowLineData.x1-SData.UData.SingleArrowLineData.x2
						, SData.UData.SingleArrowLineData.y1-SData.UData.SingleArrowLineData.y2);
				s1=s+M_PI/6;
				s2=s-M_PI/6;
				mx1=SData.UData.SingleArrowLineData.x2+16*cos(s1);
				my1=SData.UData.SingleArrowLineData.y2+16*sin(s1);
				mx2=SData.UData.SingleArrowLineData.x2+16*cos(s2);
				my2=SData.UData.SingleArrowLineData.y2+16*sin(s2);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY
						 	 ,(mx1+movx)*ZoomRateX	,(my1+movy)*ZoomRateY);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY
							,(mx2+movx)*ZoomRateX	,(my2+movy)*ZoomRateY);
				break;
			case fdDualArrow:
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRateY
							,(SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY);
				s1=GetSita(SData.UData.SingleArrowLineData.x1-SData.UData.SingleArrowLineData.x2
						 , SData.UData.SingleArrowLineData.y1-SData.UData.SingleArrowLineData.y2);
				s11=s1+M_PI/6;
				s12=s1-M_PI/6;
				mx1=SData.UData.SingleArrowLineData.x2+16*cos(s11);
				my1=SData.UData.SingleArrowLineData.y2+16*sin(s11);
				mx2=SData.UData.SingleArrowLineData.x2+16*cos(s12);
				my2=SData.UData.SingleArrowLineData.y2+16*sin(s12);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY
							,(mx1+movx)*ZoomRateX	,(my1+movy)*ZoomRateY);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x2+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y2+movy)*ZoomRateY
							,(mx2+movx)*ZoomRateX	,(my2+movy)*ZoomRateY);
				s2=GetSita(SData.UData.SingleArrowLineData.x2-SData.UData.SingleArrowLineData.x1
						 , SData.UData.SingleArrowLineData.y2-SData.UData.SingleArrowLineData.y1);
				s21=s2+M_PI/6;
				s22=s2-M_PI/6;
				nx1=SData.UData.SingleArrowLineData.x1+16*cos(s21);
				ny1=SData.UData.SingleArrowLineData.y1+16*sin(s21);
				nx2=SData.UData.SingleArrowLineData.x1+16*cos(s22);
				ny2=SData.UData.SingleArrowLineData.y1+16*sin(s22);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRateY
							 ,(nx1+movx)*ZoomRateX	,(ny1+movy)*ZoomRateY);
				Pnt.drawLine((SData.UData.SingleArrowLineData.x1+movx)*ZoomRateX	,(SData.UData.SingleArrowLineData.y1+movy)*ZoomRateY
							 ,(nx2+movx)*ZoomRateX	,(ny2+movy)*ZoomRateY);
				break;
			case fdRing:
				DrawRing(Pnt);
				break;
			case fdLongCircle:
				DrawLongCircle(Pnt);
				break;

			case fdRingArc1:
				DrawRingArc(Pnt);
				break;
			case fdRingArc4:
				DrawRingArc(Pnt);
				break;
		}
		PaintMutex.unlock();
	}
	if(FModeCrossLine==true){
		//QPainter	Pnt(this);
		PaintMutex.lock();
		Pnt.setPen(FCrossLineColor);
		Pnt.drawLine(0,NowGy,width(),NowGy);
		Pnt.drawLine(NowGx,0,NowGx,height());
		PaintMutex.unlock();
	}
	setUpdatesEnabled(true);
}

static	void	DrawPixelZoom(QPainter &Pnt ,int x1, int y1 ,double ZoomRateX,double ZoomRateY)
{
	int	ix1=x1*ZoomRateX;
	int	iy1=y1*ZoomRateY;
	int	ix2=(x1+1)*ZoomRateX-1;
	int	iy2=(y1+1)*ZoomRateY;

	for(int i=iy1;i<iy2;i++){
		Pnt.drawLine(ix1,i,ix2,i);
	}
}

void	mtFrameDraw3D::DrawLineZoom(QPainter &Pnt ,int x1, int y1 ,int x2, int y2
									,double ZoomRateX,double ZoomRateY)
{
	double	R=GetLineWidth()/2.0;
	if(ZoomRateX<2.0 && ZoomRateY<2.0){
		if(R*ZoomRateX<=0.00001 && R*ZoomRateY<=0.00001){
			Pnt.drawLine(x1*ZoomRateX ,y1*ZoomRateY, x2*ZoomRateX,y2*ZoomRateY);
		}
		else{
			double	dx=x2-x1;
			double	dy=y2-y1;
			double	Len=hypot(dx,dy);
			if(Len>0){
				dx /=Len;
				dy /=Len;
				double	Vx=-dy;
				double	Vy= dx;

				Pnt.drawLine((x1+Vx*R)*ZoomRateX ,(y1+Vy*R)*ZoomRateY, (x2+Vx*R)*ZoomRateX,(y2+Vy*R)*ZoomRateY);
				Pnt.drawLine((x1-Vx*R)*ZoomRateX ,(y1-Vy*R)*ZoomRateY, (x2-Vx*R)*ZoomRateX,(y2-Vy*R)*ZoomRateY);
				double	s1=-GetSita(Vx,Vy);
				double	s2=RegulateAngle(s1-M_PI);
				Pnt.drawArc((x1-R)*ZoomRateX, (y1-R)*ZoomRateY, R*2*ZoomRateX, R*2*ZoomRateY, 5760*s2/(2*M_PI), 180*16);
				Pnt.drawArc((x2-R)*ZoomRateX, (y2-R)*ZoomRateY, R*2*ZoomRateX, R*2*ZoomRateY, 5760*s1/(2*M_PI), 180*16);
			}
		}
	}
	else{
		if(R*ZoomRateX<=0.00001 && R*ZoomRateY<=0.00001){
			DrawLineZoomInner(Pnt ,x1, y1 ,x2, y2 ,ZoomRateX,ZoomRateY);
		}
		else{
			double	dx=x2-x1;
			double	dy=y2-y1;
			double	Len=hypot(dx,dy);
			if(Len>0){
				dx /=Len;
				dy /=Len;
				double	Vx=-dy;
				double	Vy= dx;
				DrawLineZoomInner(Pnt ,x1+Vx*R, y1+Vy*R ,x2+Vx*R, y2+Vy*R ,ZoomRateX,ZoomRateY);
				DrawLineZoomInner(Pnt ,x1-Vx*R, y1-Vy*R ,x2-Vx*R, y2-Vy*R ,ZoomRateX,ZoomRateY);

				double	s1=-GetSita(Vx,Vy);
				double	s2=RegulateAngle(s1-M_PI);
				Pnt.drawArc((x1-R)*ZoomRateX, (y1-R)*ZoomRateY, R*2*ZoomRateX, R*2*ZoomRateY, 5760*s2/(2*M_PI), 180*16);
				Pnt.drawArc((x2-R)*ZoomRateX, (y2-R)*ZoomRateY, R*2*ZoomRateX, R*2*ZoomRateY, 5760*s1/(2*M_PI), 180*16);
			}
		}
	}

}

void	mtFrameDraw3D::DrawLineZoomInner(QPainter &Pnt ,int x1, int y1 ,int x2, int y2
										,double ZoomRateX,double ZoomRateY)
{
	int lastx=99999999 ,lasty=99999999;
	int x,y;		
	int dx=x2-x1;
	int dy=y2-y1;
	if(abs(dx)>abs(dy)){
	    if(dx>0){
	        for(x=0;x<dx;x++){
	            y=x*dy/dx+y1;
	            if(lastx!=x1+x || lasty!=y){
	                lastx=x1+x;
	                lasty=y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRateX,ZoomRateY);
				}
			}
		}
	    else{
	        for(x=0;x>dx;x--){
	            y=x*dy/dx+y1;
	            if(lastx!=x1+x || lasty!=y){
	                lastx=x1+x;
	                lasty=y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRateX,ZoomRateY);
				}
			}
		}
	}
	else{
	    if(dy>0){
	        for(y=0;y<dy;y++){
	            x=y*dx/dy+x1;
	            if(lastx!=x || lasty!=y1+y){
	                lastx=x;
	                lasty=y1+y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRateX,ZoomRateY);
				}
			}
		}
	    else if(dy!=0){
	        for(y=0;y>dy;y--){
	            x=y*dx/dy+x1;
	            if(lastx!=x || lasty!=y1+y){
	                lastx=x;
	                lasty=y1+y;
					DrawPixelZoom(Pnt ,lastx,lasty ,ZoomRateX,ZoomRateY);
				}
			}
		}
	    else if(lastx!=x1 || lasty!=y1){
			DrawPixelZoom(Pnt ,x1,y1 ,ZoomRateX,ZoomRateY);
	        lastx=x1;
	        lasty=y1;
		}
	}
}


static	bool	GetRotEllipseXY(double Cx,double Cy,double rx,double ry
									,double c,double s
									,double a,double b
									,double &X1,double &Y1,double &X2,double &Y2)
{
	double	Rx2=rx*rx;
	double	Ry2=ry*ry;
	double	D=(b*c+a*s)*(b*c+a*s)*Rx2 + (a*c-b*s)*(a*c-b*s)*Ry2;
	if(D<=0){
		return false;
	}
	D=sqrt(D);
	X1=-a*rx*ry/D +Cx;
	Y1=-b*rx*ry/D +Cy;
	X2= a*rx*ry/D +Cx;
	Y2= b*rx*ry/D +Cy;

	return true;
}

void	mtFrameDraw3D::DrawRotEllipse(QPainter &Pnt)
{
	double	movx;
	double	movy;
	CInfo.GetMovXY(movx,movy);
	double	ZoomRateX,ZoomRateY;
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

	int	N=1000;
	double	LastX1,LastY1;
	double	LastX2,LastY2;
	double	Cx=(SData.UData.RotEllipseData.cx+movx)*ZoomRateX;
	double	Cy=(SData.UData.RotEllipseData.cy+movy)*ZoomRateY;
	double	Rx=SData.UData.RotEllipseData.rx*ZoomRateX;
	double	Ry=SData.UData.RotEllipseData.ry*ZoomRateY;
	if(N>2*Rx){
		N=2*Rx+1;
	}
	if(N>2*Ry){
		N=2*Ry+1;
	}
	if(N<10){
		N=10;
	}
	double	s=sin(-SData.UData.RotEllipseData.s);
	double	c=cos(-SData.UData.RotEllipseData.s);

	GetRotEllipseXY(Cx,Cy,Rx+1,Ry+1,c,s,1,0,LastX1,LastY1,LastX2,LastY2);
//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=1;i<N;i++){
			double	l=i*M_PI/N;
			double	X1,Y1;
			double	X2,Y2;
			if(GetRotEllipseXY(Cx,Cy,Rx,Ry,c,s,cos(l),sin(l),X1,Y1,X2,Y2)==true){
				double	L1=hypot(LastX1-X1,LastY1-Y1);
				double	L2=hypot(LastX1-X2,LastY1-Y2);
				if(L2<L1){
					swap(X1,X2);
					swap(Y1,Y2);
				}
				Pnt.drawLine(LastX1,LastY1,X1,Y1);
				Pnt.drawLine(LastX2,LastY2,X2,Y2);
				LastX1=X1;
				LastY1=Y1;
				LastX2=X2;
				LastY2=Y2;
			}
		}
//	}
}

void	mtFrameDraw3D::DrawRing(QPainter &Pnt)
{
	double	movx;
	double	movy;
	CInfo.GetMovXY(movx,movy);
	double	ZoomRateX,ZoomRateY;
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

	double	Cx=(SData.UData.ERingData.cx+movx)*ZoomRateX;
	double	Cy=(SData.UData.ERingData.cy+movy)*ZoomRateY;
	double	Rx1=SData.UData.ERingData.rx1*ZoomRateX;
	double	Ry1=SData.UData.ERingData.ry1*ZoomRateY;
	double	Rx2=SData.UData.ERingData.rx2*ZoomRateX;
	double	Ry2=SData.UData.ERingData.ry2*ZoomRateY;

	if(Ry2<Ry1){
		swap(Rx1,Rx2);
		swap(Ry1,Ry2);
	}
	double	Ry22=Ry2*Ry2;
	double	Ry11=Ry1*Ry1;
	double	Rx22=Rx2*Rx2;
	double	Rx11=Rx1*Rx1;

	int	ILen=Ry2*2+1;
//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=0;i<ILen;i++){
			int	y=i-Ry2;
		//for(int y=-Ry2;y<=Ry2;y++){
			if(y<=-Ry1 || Ry1<=y){

#if 1 // 20100210
				double D;

				if (0.0 == Ry22)
					D = Rx22;
				else
					D = Rx22 - Rx22 * y * y / Ry22;
#else
				double	D=Rx22-Rx22*y*y/Ry22;
#endif

				if(D>=0){
					D=sqrt(D);
					double	X1=Cx-D;
					double	X2=Cx+D;
					Pnt.drawLine(X1,Cy+y,X2,Cy+y);
				}
			}
			else{

#if 1 // 20100210
				double D2;

				if (0.0 == Ry22)
					D2 = Rx22;
				else
					D2 = Rx22 - Rx22 * y * y / Ry22;
#else
				double	D2=Rx22-Rx22*y*y/Ry22;
#endif

				if(D2>=0){
					D2=sqrt(D2);
					double	X21=Cx-D2;
					double	X22=Cx+D2;

#if 1 // 20100210
					double D1;

					if (0.0 == Ry11)
						D1 = Rx11;
					else
						D1 = Rx11 - Rx11 * y * y / Ry11;
#else
					double	D1=Rx11-Rx11*y*y/Ry11;
#endif

					if(D1>=0){
						D1=sqrt(D1);
						double	X11=Cx-D1;
						double	X12=Cx+D1;
						Pnt.drawLine(X11,Cy+y,X21,Cy+y);
						Pnt.drawLine(X12,Cy+y,X22,Cy+y);
					}
				}
			}
		}
//	}
}

void	mtFrameDraw3D::DrawLongCircle(QPainter &Pnt)
{
	double	movx;
	double	movy;
	CInfo.GetMovXY(movx,movy);
	double	ZoomRateX,ZoomRateY;
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

	double	Cx1=(SData.UData.LongCircleData.cx1+movx)*ZoomRateX;
	double	Cy1=(SData.UData.LongCircleData.cy1+movy)*ZoomRateY;
	double	Cx2=(SData.UData.LongCircleData.cx2+movx)*ZoomRateX;
	double	Cy2=(SData.UData.LongCircleData.cy2+movy)*ZoomRateY;
	double	dx=SData.UData.LongCircleData.cx2-SData.UData.LongCircleData.cx1;
	double	dy=SData.UData.LongCircleData.cy2-SData.UData.LongCircleData.cy1;
	double	R=SData.UData.LongCircleData.r;
	double	r=SData.UData.LongCircleData.r*ZoomRateX;
	double	L=hypot(dx,dy);
	if(L>0.00001){
		double	hx=-dy*R/L;
		double	hy= dx*R/L;
		double	Rx11=(SData.UData.LongCircleData.cx1+hx+movx)*ZoomRateX;
		double	Ry11=(SData.UData.LongCircleData.cy1+hy+movy)*ZoomRateY;
		double	Rx12=(SData.UData.LongCircleData.cx2+hx+movx)*ZoomRateX;
		double	Ry12=(SData.UData.LongCircleData.cy2+hy+movy)*ZoomRateY;
		double	Rx21=(SData.UData.LongCircleData.cx1-hx+movx)*ZoomRateX;
		double	Ry21=(SData.UData.LongCircleData.cy1-hy+movy)*ZoomRateY;
		double	Rx22=(SData.UData.LongCircleData.cx2-hx+movx)*ZoomRateX;
		double	Ry22=(SData.UData.LongCircleData.cy2-hy+movy)*ZoomRateY;

		double	Ky11=(SData.UData.LongCircleData.cy1-SData.UData.LongCircleData.r+movy)*ZoomRateX;
		double	Ky12=(SData.UData.LongCircleData.cy1+SData.UData.LongCircleData.r+movy)*ZoomRateY;
		double	Ky21=(SData.UData.LongCircleData.cy2-SData.UData.LongCircleData.r+movy)*ZoomRateX;
		double	Ky22=(SData.UData.LongCircleData.cy2+SData.UData.LongCircleData.r+movy)*ZoomRateY;

		int	YMin=min(Ky11,Ky21);
		int	YMax=max(Ky12,Ky22);

		for(int y=YMin;y<=YMax;y++){
			int	gminx=99999999,gmaxx=-99999999;
			if(-r<=(y-Cy1) && (y-Cy1)<=r){
				double	x=sqrt(r*r-(y-Cy1)*(y-Cy1));
				gminx=Cx1-x;
				gmaxx=Cx1+x;
			}
			long	X;
			if(GetCrossHalfInnerPoint(Rx11,Ry11,Rx12,Ry12,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(GetCrossHalfInnerPoint(Rx21,Ry21,Rx22,Ry22,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(-r<=(y-Cy2) && (y-Cy2)<=r){
				double	x=sqrt(r*r-(y-Cy2)*(y-Cy2));
				if(Cx2-x<gminx){
					gminx=Cx2-x;
				}
				if(Cx2+x>gmaxx){
					gmaxx=Cx2+x;
				}
			}
			if(gminx<=gmaxx){
				Pnt.drawLine(gminx,y,gmaxx,y);
			}
		}
	}
	else{
		Pnt.drawArc( (SData.UData.LongCircleData.cx1-SData.UData.LongCircleData.r+movx)*ZoomRateX	
					,(SData.UData.LongCircleData.cy1-SData.UData.LongCircleData.r+movy)*ZoomRateY
					,2*SData.UData.LongCircleData.r*ZoomRateX,2*SData.UData.LongCircleData.r*ZoomRateY
					,0,5760);
	}
}

int	CutLineByAngle(int X1,int X2,int Y
					,int Cx,int Cy ,double s1,double s2 ,double CosS1 ,double SinS1,double CosS2 ,double SinS2
					,int P[2][4])
{
	/*
		constraint s1	:	SinS1*(x-cx)-CosS1(y-cy)=0;
		constraint s2	:	SinS2*(x-cx)-CosS2(y-cy)=0;
	*/
	if(X1>X2)	swap(X1,X2);

	double	ts1=GetSita(X1-Cx,Y-Cy);
	double	ts2=GetSita(X2-Cx,Y-Cy);
	bool	b1=IsInsideAngle(ts1,s1,s2);
	bool	b2=IsInsideAngle(ts2,s1,s2);
	if(b1==true && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				P[1][0]=hX2;
				P[1][1]=Y;
				P[1][2]=X2;
				P[1][3]=Y;
				return 2;
			}
		}
		P[0][0]=X1;
		P[0][1]=Y;
		P[0][2]=X2;
		P[0][3]=Y;
		return 1;
	}
	if(b1==true && b2==false){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX1;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	if(b1==false && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=hX2;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	else{
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
			}
		}
	}
	return 0;
}


void	mtFrameDraw3D::DrawRingArc(QPainter &Pnt)
{
	double	movx;
	double	movy;
	CInfo.GetMovXY(movx,movy);
	double	ZoomRateX,ZoomRateY;
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

	double	Cx=(SData.UData.RingArcData.cx+movx)*ZoomRateX;
	double	Cy=(SData.UData.RingArcData.cy+movy)*ZoomRateY;
	double	Rx1=SData.UData.RingArcData.rx1*ZoomRateX;
	double	Ry1=SData.UData.RingArcData.ry1*ZoomRateY;
	double	Rx2=SData.UData.RingArcData.rx2*ZoomRateX;
	double	Ry2=SData.UData.RingArcData.ry2*ZoomRateY;
	double	S1 =SData.UData.RingArcData.s1;
	double	S2 =SData.UData.RingArcData.s2;

	double	CosS1=cos(S1);
	double	SinS1=sin(S1);
	double	CosS2=cos(S2);
	double	SinS2=sin(S2);

	if(Ry2<Ry1){
		swap(Rx1,Rx2);
		swap(Ry1,Ry2);
	}
	double	Ry22=Ry2*Ry2;
	double	Ry11=Ry1*Ry1;
	double	Rx22=Rx2*Rx2;
	double	Rx11=Rx1*Rx1;

	int	ILen=Ry2*2+1;
	for(int i=0;i<ILen;i++){
		int	y=i-Ry2;
		if(y<=-Ry1 || Ry1<=y){
			double D;

			if (0.0 == Ry22)
				D = Rx22;
			else
				D = Rx22 - Rx22 * y * y / Ry22;

			if(D>=0){
				D=sqrt(D);
				double	X1=Cx-D;
				double	X2=Cx+D;

				int	P[2][4];
				int	N=CutLineByAngle(X1,X2,Cy+y
									,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
									,P);
				for(int k=0;k<N;k++){
					Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
				}
			}
		}
		else{
			double D2;

			if (0.0 == Ry22)
				D2 = Rx22;
			else
				D2 = Rx22 - Rx22 * y * y / Ry22;

			if(D2>=0){
				D2=sqrt(D2);
				double	X21=Cx-D2;
				double	X22=Cx+D2;

				double D1;

				if (0.0 == Ry11)
					D1 = Rx11;
				else
					D1 = Rx11 - Rx11 * y * y / Ry11;

				if(D1>=0){
					D1=sqrt(D1);
					double	X11=Cx-D1;
					double	X12=Cx+D1;
					int	P[2][4];
					int	N;
					N=CutLineByAngle(X11,X21,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
					}
					N=CutLineByAngle(X12,X22,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						Pnt.drawLine(P[k][0],P[k][1],P[k][2],P[k][3]);
					}
				}
			}
		}
	}
}

void mtFrameDraw3D::SetClosedArea(bool Value)
{
	if(FDrawMode==fdFree
	|| FDrawMode==fdPoly){
		FClosedArea=Value;
	}

	else
	if(FDrawMode==fdRectangle
	|| FDrawMode==fdRotRectangle
	|| FDrawMode==fdCircle
	|| FDrawMode==fdCircle3
	|| FDrawMode==fdEllipse
	|| FDrawMode==fdEllipse4
	|| FDrawMode==fdRotEllipse){
		FClosedArea=true;
	}
	else{
		FClosedArea=false;
	}
}


//---------------------------------------------------------------------------
bool	mtFrameDraw3D::_ShapeData::Save(QIODevice *file)
{
	int N;
	switch(dtype){
		case fdPoint:
			if(file->write((const char *)&UData.PointData.x,sizeof(UData.PointData.x))!=sizeof(UData.PointData.x)){
				return(false);
			}
			if(file->write((const char *)&UData.PointData.y,sizeof(UData.PointData.y))!=sizeof(UData.PointData.y)){
				return(false);
			}
			break;
		case fdLine:
			if(file->write((const char *)&UData.LineData.x,sizeof(UData.LineData.x))!=sizeof(UData.LineData.x)){
				return(false);
			}
			if(file->write((const char *)&UData.LineData.y,sizeof(UData.LineData.y))!=sizeof(UData.LineData.y)){
				return(false);
			}
			if(file->write((const char *)&UData.LineData.s,sizeof(UData.LineData.s))!=sizeof(UData.LineData.s)){
				return(false);
			}
			break;
		case fdHalfLine:
			if(file->write((const char *)&UData.HalfLineData.x,sizeof(UData.HalfLineData.x))!=sizeof(UData.HalfLineData.x)){
				return(false);
			}
			if(file->write((const char *)&UData.HalfLineData.y,sizeof(UData.HalfLineData.y))!=sizeof(UData.HalfLineData.y)){
				return(false);
			}
			if(file->write((const char *)&UData.HalfLineData.s,sizeof(UData.HalfLineData.s))!=sizeof(UData.HalfLineData.s)){
				return(false);
			}
			break;
		case fdChoppedLine:
		case fdHChoppedLine:
		case fdVChoppedLine:
			if(file->write((const char *)&UData.ChoppedLineData.x1,sizeof(UData.ChoppedLineData.x1))!=sizeof(UData.ChoppedLineData.x1)){
				return(false);
			}
			if(file->write((const char *)&UData.ChoppedLineData.y1,sizeof(UData.ChoppedLineData.y1))!=sizeof(UData.ChoppedLineData.y1)){
				return(false);
			}
			if(file->write((const char *)&UData.ChoppedLineData.x2,sizeof(UData.ChoppedLineData.x2))!=sizeof(UData.ChoppedLineData.x2)){
				return(false);
			}
			if(file->write((const char *)&UData.ChoppedLineData.y2,sizeof(UData.ChoppedLineData.y2))!=sizeof(UData.ChoppedLineData.y2)){
				return(false);
			}
			break;
		case fdRectangle:
			if(file->write((const char *)&UData.RectangleData.x1,sizeof(UData.RectangleData.x1))!=sizeof(UData.RectangleData.x1)){
				return(false);
			}
			if(file->write((const char *)&UData.RectangleData.y1,sizeof(UData.RectangleData.y1))!=sizeof(UData.RectangleData.y1)){
				return(false);
			}
			if(file->write((const char *)&UData.RectangleData.x2,sizeof(UData.RectangleData.x2))!=sizeof(UData.RectangleData.x2)){
				return(false);
			}
			if(file->write((const char *)&UData.RectangleData.y2,sizeof(UData.RectangleData.y2))!=sizeof(UData.RectangleData.y2)){
				return(false);
			}
			break;
		case fdRotRectangle:
			if(file->write((const char *)&UData.RotRectangleData.cx,sizeof(UData.RotRectangleData.cx))!=sizeof(UData.RotRectangleData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.RotRectangleData.cy,sizeof(UData.RotRectangleData.cy))!=sizeof(UData.RotRectangleData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.RotRectangleData.rx,sizeof(UData.RotRectangleData.rx))!=sizeof(UData.RotRectangleData.rx)){
				return(false);
			}
			if(file->write((const char *)&UData.RotRectangleData.ry,sizeof(UData.RotRectangleData.ry))!=sizeof(UData.RotRectangleData.ry)){
				return(false);
			}
			if(file->write((const char *)&UData.RotRectangleData.s ,sizeof(UData.RotRectangleData.s ))!=sizeof(UData.RotRectangleData.s )){
				return(false);
			}
			break;
		case fdCircle:
		case fdCircle3:
			if(file->write((const char *)&UData.CircleData.cx,sizeof(UData.CircleData.cx))!=sizeof(UData.CircleData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.CircleData.cy,sizeof(UData.CircleData.cy))!=sizeof(UData.CircleData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.CircleData.r ,sizeof(UData.CircleData.r ))!=sizeof(UData.CircleData.r )){
				return(false);
			}
			break;
		case fdEllipse:
		case fdEllipse4:
			if(file->write((const char *)&UData.EllipseData.cx,sizeof(UData.EllipseData.cx))!=sizeof(UData.EllipseData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.EllipseData.cy,sizeof(UData.EllipseData.cy))!=sizeof(UData.EllipseData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.EllipseData.rx,sizeof(UData.EllipseData.rx))!=sizeof(UData.EllipseData.rx)){
				return(false);
			}
			if(file->write((const char *)&UData.EllipseData.ry,sizeof(UData.EllipseData.ry))!=sizeof(UData.EllipseData.ry)){
				return(false);
			}
			break;
		case fdRotEllipse:
			if(file->write((const char *)&UData.RotEllipseData.cx,sizeof(UData.RotEllipseData.cx))!=sizeof(UData.RotEllipseData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.RotEllipseData.cy,sizeof(UData.RotEllipseData.cy))!=sizeof(UData.RotEllipseData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.RotEllipseData.rx,sizeof(UData.RotEllipseData.rx))!=sizeof(UData.RotEllipseData.rx)){
				return(false);
			}
			if(file->write((const char *)&UData.RotEllipseData.ry,sizeof(UData.RotEllipseData.ry))!=sizeof(UData.RotEllipseData.ry)){
				return(false);
			}
			if(file->write((const char *)&UData.RotEllipseData.s ,sizeof(UData.RotEllipseData.s ))!=sizeof(UData.RotEllipseData.s )){
				return(false);
			}
			break;
		case fdArc:
		case fdArc3:
			if(file->write((const char *)&UData.ArcData.cx,sizeof(UData.ArcData.cx))!=sizeof(UData.ArcData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.ArcData.cy,sizeof(UData.ArcData.cy))!=sizeof(UData.ArcData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.ArcData.r ,sizeof(UData.ArcData.r ))!=sizeof(UData.ArcData.r )){
				return(false);
			}
			if(file->write((const char *)&UData.ArcData.s1,sizeof(UData.ArcData.s1))!=sizeof(UData.ArcData.s1)){
				return(false);
			}
			if(file->write((const char *)&UData.ArcData.s2,sizeof(UData.ArcData.s2))!=sizeof(UData.ArcData.s2)){
				return(false);
			}
			break;
		case fdFree:
			if(UData.FreeData.points==NULL){
				N=0;
			}
			else{
				N=UData.FreeData.points->GetNumber();
			}

			if(file->write((const char *)&N ,sizeof(N)) !=sizeof(N)){
				return(false);
			}
			if(N==0){
				break;
			}
			for(ShapePoint3D *s=UData.FreeData.points->GetFirst();s!=NULL;s=s->GetNext()){
				int px=s->x;
				int py=s->y;
				if(file->write((const char *)&px ,sizeof(px)) !=sizeof(px)){
					return(false);
				}
				if(file->write((const char *)&py ,sizeof(py)) !=sizeof(py)){
					return(false);
				}
				}
			break;
		case fdPoly:
			if(UData.PolyData.points==NULL){
				N=0;
			}
			else{
				N=UData.PolyData.points->GetNumber();
			}

			if(file->write((const char *)&N ,sizeof(N)) !=sizeof(N)){
				return(false);
			}
			if(N==0){
				break;
			}
			for(ShapePoint3D *s=UData.PolyData.points->GetFirst();s!=NULL;s=s->GetNext()){
				int px=s->x;
				int py=s->y;
				if(file->write((const char *)&px ,sizeof(px)) !=sizeof(px)){
					return(false);
				}
				if(file->write((const char *)&py ,sizeof(py)) !=sizeof(py)){
					return(false);
				}
				}
			break;
		case fdMove:
			break;
		case fdRing:
			if(file->write((const char *)&UData.ERingData.cx ,sizeof(UData.ERingData.cx)) !=sizeof(UData.ERingData.cx)){
				return(false);
			}
			if(file->write((const char *)&UData.ERingData.cy ,sizeof(UData.ERingData.cy)) !=sizeof(UData.ERingData.cy)){
				return(false);
			}
			if(file->write((const char *)&UData.ERingData.rx1,sizeof(UData.ERingData.rx1))!=sizeof(UData.ERingData.rx1)){
				return(false);
			}
			if(file->write((const char *)&UData.ERingData.ry1,sizeof(UData.ERingData.ry1))!=sizeof(UData.ERingData.ry1)){
				return(false);
			}
			if(file->write((const char *)&UData.ERingData.rx2,sizeof(UData.ERingData.rx2))!=sizeof(UData.ERingData.rx2)){
				return(false);
			}
			if(file->write((const char *)&UData.ERingData.ry2,sizeof(UData.ERingData.ry2))!=sizeof(UData.ERingData.ry2)){
				return(false);
			}
			break;
		case fdSingleArrow:
			if(file->write((const char *)&UData.SingleArrowLineData.x1,sizeof(UData.SingleArrowLineData.x1))!=sizeof(UData.SingleArrowLineData.x1)){
				return(false);
			}
			if(file->write((const char *)&UData.SingleArrowLineData.y1,sizeof(UData.SingleArrowLineData.y1))!=sizeof(UData.SingleArrowLineData.y1)){
				return(false);
			}
			if(file->write((const char *)&UData.SingleArrowLineData.x2,sizeof(UData.SingleArrowLineData.x2))!=sizeof(UData.SingleArrowLineData.x2)){
				return(false);
			}
			if(file->write((const char *)&UData.SingleArrowLineData.y2,sizeof(UData.SingleArrowLineData.y2))!=sizeof(UData.SingleArrowLineData.y2)){
				return(false);
			}
			break;
		case fdDualArrow:
			if(file->write((const char *)&UData.DualArrowLineData.x1,sizeof(UData.DualArrowLineData.x1))!=sizeof(UData.DualArrowLineData.x1))
				return(false);
			if(file->write((const char *)&UData.DualArrowLineData.y1,sizeof(UData.DualArrowLineData.y1))!=sizeof(UData.DualArrowLineData.y1))
				return(false);
			if(file->write((const char *)&UData.DualArrowLineData.x2,sizeof(UData.DualArrowLineData.x2))!=sizeof(UData.DualArrowLineData.x2))
				return(false);
			if(file->write((const char *)&UData.DualArrowLineData.y2,sizeof(UData.DualArrowLineData.y2))!=sizeof(UData.DualArrowLineData.y2))
				return(false);
			break;
		case fdLongCircle:
			if(file->write((const char *)&UData.LongCircleData.cx1 ,sizeof(UData.LongCircleData.cx1)) !=sizeof(UData.LongCircleData.cx1))
				return(false);
			if(file->write((const char *)&UData.LongCircleData.cy1 ,sizeof(UData.LongCircleData.cy1)) !=sizeof(UData.LongCircleData.cy1))
				return(false);
			if(file->write((const char *)&UData.LongCircleData.cx2 ,sizeof(UData.LongCircleData.cx2)) !=sizeof(UData.LongCircleData.cx2))
				return(false);
			if(file->write((const char *)&UData.LongCircleData.cy2 ,sizeof(UData.LongCircleData.cy2)) !=sizeof(UData.LongCircleData.cy2))
				return(false);
			if(file->write((const char *)&UData.LongCircleData.r   ,sizeof(UData.LongCircleData.r  )) !=sizeof(UData.LongCircleData.r  ))
				return(false);
			break;
		case fdNone:
			break;
		}
	return(true);
}
bool	mtFrameDraw3D::_ShapeData::Load(QIODevice *file)
{
	int N;
	switch(dtype){
		case fdPoint:
			if(file->read((char *)&UData.PointData.x,sizeof(UData.PointData.x))!=sizeof(UData.PointData.x))
				return(false);
			if(file->read((char *)&UData.PointData.y,sizeof(UData.PointData.y))!=sizeof(UData.PointData.y))
				return(false);
			break;
		case fdLine:
			if(file->read((char *)&UData.LineData.x,sizeof(UData.LineData.x))!=sizeof(UData.LineData.x))
				return(false);
			if(file->read((char *)&UData.LineData.y,sizeof(UData.LineData.y))!=sizeof(UData.LineData.y))
				return(false);
			if(file->read((char *)&UData.LineData.s,sizeof(UData.LineData.s))!=sizeof(UData.LineData.s))
				return(false);
			break;
		case fdHalfLine:
			if(file->read((char *)&UData.HalfLineData.x,sizeof(UData.HalfLineData.x))!=sizeof(UData.HalfLineData.x))
				return(false);
			if(file->read((char *)&UData.HalfLineData.y,sizeof(UData.HalfLineData.y))!=sizeof(UData.HalfLineData.y))
				return(false);
			if(file->read((char *)&UData.HalfLineData.s,sizeof(UData.HalfLineData.s))!=sizeof(UData.HalfLineData.s))
				return(false);
			break;
		case fdChoppedLine:
		case fdHChoppedLine:
		case fdVChoppedLine:
			if(file->read((char *)&UData.ChoppedLineData.x1,sizeof(UData.ChoppedLineData.x1))!=sizeof(UData.ChoppedLineData.x1))
				return(false);
			if(file->read((char *)&UData.ChoppedLineData.y1,sizeof(UData.ChoppedLineData.y1))!=sizeof(UData.ChoppedLineData.y1))
				return(false);
			if(file->read((char *)&UData.ChoppedLineData.x2,sizeof(UData.ChoppedLineData.x2))!=sizeof(UData.ChoppedLineData.x2))
				return(false);
			if(file->read((char *)&UData.ChoppedLineData.y2,sizeof(UData.ChoppedLineData.y2))!=sizeof(UData.ChoppedLineData.y2))
				return(false);
			break;
		case fdRectangle:
			if(file->read((char *)&UData.RectangleData.x1,sizeof(UData.RectangleData.x1))!=sizeof(UData.RectangleData.x1))
				return(false);
			if(file->read((char *)&UData.RectangleData.y1,sizeof(UData.RectangleData.y1))!=sizeof(UData.RectangleData.y1))
				return(false);
			if(file->read((char *)&UData.RectangleData.x2,sizeof(UData.RectangleData.x2))!=sizeof(UData.RectangleData.x2))
				return(false);
			if(file->read((char *)&UData.RectangleData.y2,sizeof(UData.RectangleData.y2))!=sizeof(UData.RectangleData.y2))
				return(false);
			break;
		case fdRotRectangle:
			if(file->read((char *)&UData.RotRectangleData.cx,sizeof(UData.RotRectangleData.cx))!=sizeof(UData.RotRectangleData.cx))
				return(false);
			if(file->read((char *)&UData.RotRectangleData.cy,sizeof(UData.RotRectangleData.cy))!=sizeof(UData.RotRectangleData.cy))
				return(false);
			if(file->read((char *)&UData.RotRectangleData.rx,sizeof(UData.RotRectangleData.rx))!=sizeof(UData.RotRectangleData.rx))
				return(false);
			if(file->read((char *)&UData.RotRectangleData.ry,sizeof(UData.RotRectangleData.ry))!=sizeof(UData.RotRectangleData.ry))
				return(false);
			if(file->read((char *)&UData.RotRectangleData.s ,sizeof(UData.RotRectangleData.s ))!=sizeof(UData.RotRectangleData.s ))
				return(false);
			break;
		case fdCircle:
		case fdCircle3:
			if(file->read((char *)&UData.CircleData.cx,sizeof(UData.CircleData.cx))!=sizeof(UData.CircleData.cx))
				return(false);
			if(file->read((char *)&UData.CircleData.cy,sizeof(UData.CircleData.cy))!=sizeof(UData.CircleData.cy))
				return(false);
			if(file->read((char *)&UData.CircleData.r ,sizeof(UData.CircleData.r ))!=sizeof(UData.CircleData.r ))
				return(false);
			break;
		case fdEllipse:
		case fdEllipse4:
			if(file->read((char *)&UData.EllipseData.cx,sizeof(UData.EllipseData.cx))!=sizeof(UData.EllipseData.cx))
				return(false);
			if(file->read((char *)&UData.EllipseData.cy,sizeof(UData.EllipseData.cy))!=sizeof(UData.EllipseData.cy))
				return(false);
			if(file->read((char *)&UData.EllipseData.rx,sizeof(UData.EllipseData.rx))!=sizeof(UData.EllipseData.rx))
				return(false);
			if(file->read((char *)&UData.EllipseData.ry,sizeof(UData.EllipseData.ry))!=sizeof(UData.EllipseData.ry))
				return(false);
			break;
		case fdRotEllipse:
			if(file->read((char *)&UData.RotEllipseData.cx,sizeof(UData.RotEllipseData.cx))!=sizeof(UData.RotEllipseData.cx))
				return(false);
			if(file->read((char *)&UData.RotEllipseData.cy,sizeof(UData.RotEllipseData.cy))!=sizeof(UData.RotEllipseData.cy))
				return(false);
			if(file->read((char *)&UData.RotEllipseData.rx,sizeof(UData.RotEllipseData.rx))!=sizeof(UData.RotEllipseData.rx))
				return(false);
			if(file->read((char *)&UData.RotEllipseData.ry,sizeof(UData.RotEllipseData.ry))!=sizeof(UData.RotEllipseData.ry))
				return(false);
			if(file->read((char *)&UData.RotEllipseData.s ,sizeof(UData.RotEllipseData.s ))!=sizeof(UData.RotEllipseData.s ))
				return(false);
			break;
		case fdArc:
		case fdArc3:
			if(file->read((char *)&UData.ArcData.cx,sizeof(UData.ArcData.cx))!=sizeof(UData.ArcData.cx))
				return(false);
			if(file->read((char *)&UData.ArcData.cy,sizeof(UData.ArcData.cy))!=sizeof(UData.ArcData.cy))
				return(false);
			if(file->read((char *)&UData.ArcData.r ,sizeof(UData.ArcData.r ))!=sizeof(UData.ArcData.r ))
				return(false);
			if(file->read((char *)&UData.ArcData.s1,sizeof(UData.ArcData.s1))!=sizeof(UData.ArcData.s1))
				return(false);
			if(file->read((char *)&UData.ArcData.s2,sizeof(UData.ArcData.s2))!=sizeof(UData.ArcData.s2))
				return(false);
			break;
		case fdFree:
			if(file->read((char *)&N ,sizeof(N)) !=sizeof(N))
				return(false);
			UData.FreeData.points=new NPListPack<ShapePoint3D>();
			for(int i=0;i<N;i++){
				ShapePoint3D	*s=new ShapePoint3D();
				int px;
				int py;
				if(file->read((char *)&px ,sizeof(px)) !=sizeof(px))
					return(false);
				if(file->read((char *)&py ,sizeof(py)) !=sizeof(py))
					return(false);
				s->x=px;
				s->y=py;
				UData.FreeData.points->AppendList(s);
				}
			break;
		case fdPoly:
			if(file->read((char *)&N ,sizeof(N)) !=sizeof(N))
				return(false);
			UData.PolyData.points=new NPListPack<ShapePoint3D>();
			for(int i=0;i<N;i++){
				ShapePoint3D	*s=new ShapePoint3D();
				int px;
				int py;
				if(file->read((char *)&px ,sizeof(px)) !=sizeof(px))
					return(false);
				if(file->read((char *)&py ,sizeof(py)) !=sizeof(py))
					return(false);
				s->x=px;
				s->y=py;
				UData.PolyData.points->AppendList(s);
				}
			break;
		case fdMove:
			break;
		case fdRing:
			if(file->read((char *)&UData.ERingData.cx ,sizeof(UData.ERingData.cx)) !=sizeof(UData.ERingData.cx))
				return(false);
			if(file->read((char *)&UData.ERingData.cy ,sizeof(UData.ERingData.cy)) !=sizeof(UData.ERingData.cy))
				return(false);
			if(file->read((char *)&UData.ERingData.rx1,sizeof(UData.ERingData.rx1))!=sizeof(UData.ERingData.rx1))
				return(false);
			if(file->read((char *)&UData.ERingData.ry1,sizeof(UData.ERingData.ry1))!=sizeof(UData.ERingData.ry1))
				return(false);
			if(file->read((char *)&UData.ERingData.rx2,sizeof(UData.ERingData.rx2))!=sizeof(UData.ERingData.rx2))
				return(false);
			if(file->read((char *)&UData.ERingData.ry2,sizeof(UData.ERingData.ry2))!=sizeof(UData.ERingData.ry2))
				return(false);
			break;
		case fdSingleArrow:
			if(file->read((char *)&UData.SingleArrowLineData.x1,sizeof(UData.SingleArrowLineData.x1))!=sizeof(UData.SingleArrowLineData.x1))
				return(false);
			if(file->read((char *)&UData.SingleArrowLineData.y1,sizeof(UData.SingleArrowLineData.y1))!=sizeof(UData.SingleArrowLineData.y1))
				return(false);
			if(file->read((char *)&UData.SingleArrowLineData.x2,sizeof(UData.SingleArrowLineData.x2))!=sizeof(UData.SingleArrowLineData.x2))
				return(false);
			if(file->read((char *)&UData.SingleArrowLineData.y2,sizeof(UData.SingleArrowLineData.y2))!=sizeof(UData.SingleArrowLineData.y2))
				return(false);
			break;
		case fdDualArrow:
			if(file->read((char *)&UData.DualArrowLineData.x1,sizeof(UData.DualArrowLineData.x1))!=sizeof(UData.DualArrowLineData.x1))
				return(false);
			if(file->read((char *)&UData.DualArrowLineData.y1,sizeof(UData.DualArrowLineData.y1))!=sizeof(UData.DualArrowLineData.y1))
				return(false);
			if(file->read((char *)&UData.DualArrowLineData.x2,sizeof(UData.DualArrowLineData.x2))!=sizeof(UData.DualArrowLineData.x2))
				return(false);
			if(file->read((char *)&UData.DualArrowLineData.y2,sizeof(UData.DualArrowLineData.y2))!=sizeof(UData.DualArrowLineData.y2))
				return(false);
			break;
		case fdLongCircle:
			if(file->read((char *)&UData.LongCircleData.cx1 ,sizeof(UData.LongCircleData.cx1)) !=sizeof(UData.LongCircleData.cx1))
				return(false);
			if(file->read((char *)&UData.LongCircleData.cy1 ,sizeof(UData.LongCircleData.cy1)) !=sizeof(UData.LongCircleData.cy1))
				return(false);
			if(file->read((char *)&UData.LongCircleData.cx2 ,sizeof(UData.LongCircleData.cx2)) !=sizeof(UData.LongCircleData.cx2))
				return(false);
			if(file->read((char *)&UData.LongCircleData.cy2 ,sizeof(UData.LongCircleData.cy2)) !=sizeof(UData.LongCircleData.cy2))
				return(false);
			if(file->read((char *)&UData.LongCircleData.r   ,sizeof(UData.LongCircleData.r  )) !=sizeof(UData.LongCircleData.r  ))
				return(false);
			break;
		case fdNone:
			break;
		}
	return(true);
}

bool	mtFrameDraw3D::Save(QIODevice *file)
{
	if(SData.Save(file)==false)
		return(false);
	if(file->write((const char *)&DrawStage,sizeof(DrawStage))!=sizeof(DrawStage))
		return(false);
	int32	r=FColor.red();
	if(file->write((const char *)&r,sizeof(r))!=sizeof(r))
		return(false);
	int32	g=FColor.green();
	if(file->write((const char *)&g,sizeof(g))!=sizeof(g))
		return(false);
	int32	b=FColor.blue();
	if(file->write((const char *)&b,sizeof(b))!=sizeof(b))
		return(false);
	int32	a=FColor.alpha();
	if(file->write((const char *)&a,sizeof(a))!=sizeof(a))
		return(false);
	if(file->write((const char *)&FDrawMode,sizeof(FDrawMode))!=sizeof(FDrawMode))
		return(false);
	if(file->write((const char *)&FClosedArea,sizeof(FClosedArea))!=sizeof(FClosedArea))
		return(false);
	if(file->write((const char *)&FCancelDraw,sizeof(FCancelDraw))!=sizeof(FCancelDraw))
		return(false);
	if(file->write((const char *)&FOnDrawMode,sizeof(FOnDrawMode))!=sizeof(FOnDrawMode))
		return(false);
	if(file->write((const char *)&rotx,sizeof(rotx))!=sizeof(rotx))
		return(false);
	if(file->write((const char *)&roty,sizeof(roty))!=sizeof(roty))
		return(false);

	return(true);
}
bool	mtFrameDraw3D::Load(QIODevice *file)
{
	if(SData.Load(file)==false)
		return(false);
	if(file->read((char *)&DrawStage,sizeof(DrawStage))!=sizeof(DrawStage))
		return(false);
	int32	r,g,b,a;
	if(file->read((char *)&r,sizeof(r))!=sizeof(r))
		return(false);
	if(file->read((char *)&g,sizeof(g))!=sizeof(g))
		return(false);
	if(file->read((char *)&b,sizeof(b))!=sizeof(b))
		return(false);
	if(file->read((char *)&a,sizeof(a))!=sizeof(a))
		return(false);
	FColor.setRgb(r,g,b,a);
	if(file->read((char *)&FDrawMode,sizeof(FDrawMode))!=sizeof(FDrawMode))
		return(false);
	if(file->read((char *)&FClosedArea,sizeof(FClosedArea))!=sizeof(FClosedArea))
		return(false);
	if(file->read((char *)&FCancelDraw,sizeof(FCancelDraw))!=sizeof(FCancelDraw))
		return(false);
	if(file->read((char *)&FOnDrawMode,sizeof(FOnDrawMode))!=sizeof(FOnDrawMode))
		return(false);
	if(file->read((char *)&rotx,sizeof(rotx))!=sizeof(rotx))
		return(false);
	if(file->read((char *)&roty,sizeof(roty))!=sizeof(roty))
		return(false);

	return(true);
}

bool	ColPoint3D::Save(QIODevice *file)
{
	if(file->write((const char *)&x,sizeof(x))!=sizeof(x))
		return(false);
	if(file->write((const char *)&y,sizeof(y))!=sizeof(y))
		return(false);
	if(file->write((const char *)&col,sizeof(col))!=sizeof(col))
		return(false);
	return(true);
}
bool	ColPoint3D::Load(QIODevice *file)
{
	if(file->read((char *)&x,sizeof(x))!=sizeof(x))
		return(false);
	if(file->read((char *)&y,sizeof(y))!=sizeof(y))
		return(false);
	if(file->read((char *)&col,sizeof(col))!=sizeof(col))
		return(false);
	return(true);
}

mtFrameDraw3D::_ShapeData::~_ShapeData(void)
{
	if(dtype==fdFree){
		if(UData.FreeData.points!=NULL){
			UData.FreeData.points->RemoveAll();
			delete UData.FreeData.points;
			UData.FreeData.points=NULL;
			}
		}
	else if(dtype==fdPoly){
		if(UData.PolyData.points!=NULL){
			UData.PolyData.points->RemoveAll();
			delete UData.PolyData.points;
			UData.PolyData.points=NULL;
			}
		}
	else if(dtype==fdMove){
		if(UData.MoveData.points!=NULL){
			UData.MoveData.points->RemoveAll();
			delete UData.MoveData.points;
			UData.MoveData.points=NULL;
			}
		}
}


bool mtFrameDraw3D::IsPixelEffective(int x ,int y)
{
	return(true);
}

bool	mtFrameDraw3D::Drawing(void)
{
	if(DrawStage==0)
		return(false);
	return(true);
}

void	mtFrameDraw3D::PutPixelOnly(int x ,int y ,QColor &col)
{
	QPainter	Pnt(this);

	QPen	mPen(FColor);
	Pnt.setPen(mPen);
	Pnt.drawPoint(x,y);
}

void	mtFrameDraw3D::GetCanvasToUniverse(int gx, int gy ,int &ux, int &uy)	const
{
	double	movx;
	double	movy;
	CInfo.GetMovXY(movx,movy);
	double	ZoomRateX,ZoomRateY;
	CInfo.GetZoomRate(ZoomRateX,ZoomRateY);

	ux=gx/ZoomRateX-movx;
	uy=gy/ZoomRateY-movy;
}

void mtFrameDraw3D::mousePressEvent ( QMouseEvent *Ev )
{
	DblClickMode=false;
	CancelClicked=false;
	bool ShiftKey;

	int	X=Ev->x();
	int	Y=Ev->y();
	NowGx=X;
	NowGx=Y;
	MousePressX=X;
	MousePressY=Y;
	ClickedTime=GetComputerMiliSec();

	// フラグを取得(左右クリック、シフトキー)
	LeftClicked		= ((Ev->buttons() & Qt::LeftButton)!=0) ? true : false;
	RightClicked	= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
	ShiftKey		= ((Ev->modifiers() & Qt::ShiftModifier)!=0) ? true : false;

	if(LeftClicked){
		bool	mvalid=true;
		mtMousePoint(Ev,X,Y,mvalid);
		if(mvalid==false){
			return;
		}
	}

	if((ShiftKey==true) && (LeftClicked==true)){
		if(GetMode()!=fdNone && GetMode()!=fdPoint){
			mtMouseLDown(Ev,X,Y);
		}
		return;
	}

	int uX, uY;
	GetCanvasToUniverse(X, Y ,uX, uY);
	if(LeftClicked){
		LastMouseDownPointX=uX;
		LastMouseDownPointY=uY;
		LastShitX=X;
		LastShitY=Y;
		ShiftingMode=false;
		emit	SignalJustMouseLPress(uX,uY);
	}
	else
	if((ShiftKey==true) && (RightClicked==true)){
		//mtMouseRDown(Ev, X,Y);
		return;
	}
	else
	if(RightClicked==true){
		emit	SignalJustMouseRPress(uX,uY);
		return;
	}
}

void	mtFrameDraw3D::SetEnableShiftImage(bool b)
{
	FEnableShiftImage=b;
}
bool	mtFrameDraw3D::GetEnableShiftImage(void)	const
{
	return FEnableShiftImage;
}

void	mtFrameDraw3D::mouseDoubleClickEvent ( QMouseEvent * Ev )
{
	DblClickMode=true;
	int	X=Ev->x();
	int	Y=Ev->y();
	MousePressX=X;
	MousePressY=Y;

	LeftClicked = ((Ev->buttons() & Qt::LeftButton)!=0) ? true : false;
	RightClicked= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
}
void	mtFrameDraw3D::mouseMoveEvent ( QMouseEvent * Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
	NowGx=X;
	NowGy=Y;
	double	A,B,C;
	DrawingMode	CurrentMode=FDrawMode;

	if(CancelClicked==true){
		return;
	}

	bool	mvalid=true;
	mtMousePoint(Ev,X,Y,mvalid);
	if(mvalid==false){
		return;
		}
	mtMouseMove(Ev, X, Y);

	int uX, uY;
	GetCanvasToUniverse(X, Y ,uX, uY);

	if((Ev->buttons()&Qt::LeftButton)!=0){
		double	movx;
		double	movy;
		CInfo.GetMovXY(movx,movy);
		double	ZoomRateX,ZoomRateY;
		CInfo.GetZoomRate(ZoomRateX,ZoomRateY);
		if(abs(uX-LastMouseDownPointX)*ZoomRateX>10
		|| abs(uY-LastMouseDownPointY)*ZoomRateY>10 || ShiftingMode==true){
			if(GetComputerMiliSec()-ClickedTime>ImageShiftDelay){
				if(FEnableShiftImage==true){
					int	Dx=X-LastShitX;
					int	Dy=Y-LastShitY;
					ShiftingMode=true;
					emit	SignalShiftCanvas(Dx,Dy);
					LastShitX=X;
					LastShitY=Y;
					return;
				}
			}
		}
		RepaintAll();
	}

	if(DrawStage==1){
		switch(CurrentMode){
			case fdLine:
				SData.UData.LineData.s=GetSita(uX-SData.UData.LineData.x,uY-SData.UData.LineData.y);
				emit	SignalDrawMessage(QStringList("Angle")
										 ,QStringList(QString::number(SData.UData.LineData.s*180.0/M_PI,'f',3)));
				break;
			case fdHalfLine:
				SData.UData.HalfLineData.s=GetSita(uX-SData.UData.HalfLineData.x,uY-SData.UData.HalfLineData.y);
				emit	SignalDrawMessage(QStringList("Length")<<QString("Angle")
					,QStringList( QString::number(hypot(uX-SData.UData.HalfLineData.x,uY-SData.UData.HalfLineData.y),'f',2))
								<<QString::number(SData.UData.HalfLineData.s*180.0/M_PI,'f',3));
				break;
			case fdChoppedLine:
				SData.UData.ChoppedLineData.x2=uX;
				SData.UData.ChoppedLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdHChoppedLine:
				SData.UData.ChoppedLineData.x2=uX;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdVChoppedLine:
				SData.UData.ChoppedLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.ChoppedLineData.x2-SData.UData.ChoppedLineData.x1))
							   <<QString::number(SData.UData.ChoppedLineData.y2-SData.UData.ChoppedLineData.y1));
				break;
			case fdSingleArrow:
				SData.UData.SingleArrowLineData.x2=uX;
				SData.UData.SingleArrowLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.SingleArrowLineData.x2-SData.UData.SingleArrowLineData.x1))
							   <<QString::number(SData.UData.SingleArrowLineData.y2-SData.UData.SingleArrowLineData.y1));
				break;
			case fdDualArrow:
				SData.UData.DualArrowLineData.x2=uX;
				SData.UData.DualArrowLineData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList(QString::number(SData.UData.DualArrowLineData.x2-SData.UData.DualArrowLineData.x1,'f',1))
							   <<QString::number(SData.UData.DualArrowLineData.y2-SData.UData.DualArrowLineData.y1,'f',1));
				break;
			case fdRectangle:
				SData.UData.RectangleData.x2=uX;
				SData.UData.RectangleData.y2=uY;
				emit	SignalDrawMessage(QStringList("dx")<<QString("dy")
					,QStringList( QString::number(SData.UData.RectangleData.x2-SData.UData.RectangleData.x1))
								<<QString::number(SData.UData.RectangleData.y2-SData.UData.RectangleData.y1));
				break;
			case fdRotRectangle:
				SData.UData.RotRectangleData.rx=fabs(uX-SData.UData.RotRectangleData.cx);
				SData.UData.RotRectangleData.ry=fabs(uY-SData.UData.RotRectangleData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotRectangleData.rx,'f',2))
							   <<QString::number(SData.UData.RotRectangleData.ry,'f',2)
							   <<QString("0"));
				break;
			case fdCircle:
				SData.UData.CircleData.r=hypot(uX-SData.UData.CircleData.cx
											 , uY-SData.UData.CircleData.cy);
				emit	SignalDrawMessage(QStringList("Radius")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdCircle3:
				SData.UData.CircleData.cx=(uX+TmpPoint[0][0])/2;
				SData.UData.CircleData.cy=(uY+TmpPoint[0][1])/2;
				SData.UData.CircleData.r=hypot(uX-SData.UData.CircleData.cx
											 , uY-SData.UData.CircleData.cy);
				emit	SignalDrawMessage(QStringList("Second Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdEllipse:
				SData.UData.EllipseData.rx=fabs(uX-SData.UData.EllipseData.cx);
				SData.UData.EllipseData.ry=fabs(uY-SData.UData.EllipseData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")
					,QStringList(QString::number(SData.UData.EllipseData.rx,'f',2))
							   <<QString::number(SData.UData.EllipseData.ry,'f',2));
				break;
			case fdEllipse4:
				SData.UData.EllipseData.cx=TmpPoint[0][0];
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+uY)/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-uY)/2.0;
				emit	SignalDrawMessage(QStringList("Top-Y")<<QString("Bottom-Y")
							,QStringList(QString::number(uY,'f',2))
							   <<QString::number(uY,'f',2));
				break;
			case fdRotEllipse:
				SData.UData.RotEllipseData.rx=fabs(uX-SData.UData.RotEllipseData.cx);
				SData.UData.RotEllipseData.ry=fabs(uY-SData.UData.RotEllipseData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotEllipseData.rx,'f',2))
							   <<QString::number(SData.UData.RotEllipseData.ry,'f',2)
							   <<QString("0"));
				break;
			case fdArc:
				SData.UData.ArcData.r=hypot(uX-SData.UData.ArcData.cx
										  , uY-SData.UData.ArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList(QString::number(SData.UData.ArcData.r,'f',2))
								<<QString("0")
								<<QString("360"));
				break;
			case fdArc3:
				emit	SignalDrawMessage(QStringList("Second Point-X")<<QString("Second Point-Y")
					,QStringList(QString::number(uX,'f',2))
								<<QString::number(uY,'f',2));
				break;
			case fdFree:
				if(SData.UData.FreeData.points!=NULL){
					ShapePoint3D	*q=SData.UData.FreeData.points->GetLast();
					if(q!=NULL && (q->x!=uX || q->y!=uY)){
						SData.UData.FreeData.points->AppendList(new ShapePoint3D(uX,uY));
						emit	SignalDrawMessage(QStringList("Dx")<<QString("Dy")
								,QStringList( QString::number(uX-SData.UData.FreeData.points->GetFirst()->x))
											<<QString::number(uY-SData.UData.FreeData.points->GetFirst()->y));
					}
				}
				rotx=uX;
				roty=uY;
				break;
			case fdPoly:
				if(SData.UData.PolyData.points!=NULL){
					ShapePoint3D	*q=SData.UData.PolyData.points->GetLast();
					if(q!=NULL){
						emit	SignalDrawMessage(QStringList("Dx")<<QString("Dy")
								,QStringList( QString::number(uX-q->x))
											<<QString::number(uY-q->y));
					}
				}
				rotx=uX;
				roty=uY;
				break;
			/*
			case fdMove:
				MovePoints(X-rotx ,Y-roty);
				rotx=X;
				roty=Y;
				break;
			*/
			case fdRing:
				SData.UData.ERingData.rx1=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry1=fabs(uY-SData.UData.ERingData.cy);
				SData.UData.ERingData.rx2=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry2=fabs(uY-SData.UData.ERingData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")
					,QStringList( QString::number(SData.UData.ERingData.rx1,'f',2))
								<<QString::number(SData.UData.ERingData.ry1,'f',2)
								<<QString::number(SData.UData.ERingData.rx2,'f',2)
								<<QString::number(SData.UData.ERingData.ry2,'f',2));
				break;
			case fdLongCircle:
				SData.UData.LongCircleData.cx1=(uX+TmpPoint[0][0])/2;
				SData.UData.LongCircleData.cy1=(uY+TmpPoint[0][1])/2;
				SData.UData.LongCircleData.cx2=SData.UData.LongCircleData.cx1;
				SData.UData.LongCircleData.cy2=SData.UData.LongCircleData.cy1;
				SData.UData.LongCircleData.r  =hypot(uX-SData.UData.LongCircleData.cx1
													,uY-SData.UData.LongCircleData.cy1);
				emit	SignalDrawMessage(QStringList("Second Point")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.rx1=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry1=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")
					,QStringList(QString::number(SData.UData.RingArcData.rx1,'f',2))
							   <<QString::number(SData.UData.RingArcData.ry1,'f',2));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=TmpPoint[0][0];
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+uY)/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-uY)/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;
				emit	SignalDrawMessage(QStringList("Top-Y")<<QString("Bottom-Y")
										,QStringList(QString::number(uY,'f',2))
										<<QString::number(uY,'f',2));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==2){
		switch(CurrentMode){
			case fdCircle3:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.CircleData.cx,SData.UData.CircleData.cy,SData.UData.CircleData.r);
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdEllipse4:
				SData.UData.EllipseData.cx=(uX+TmpPoint[0][0])/2.0;
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.rx=abs(uX-TmpPoint[0][0])/2.0;

				emit	SignalDrawMessage(QStringList("Left-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
			case fdRotRectangle:
				SData.UData.RotRectangleData.s=GetSita(uX -SData.UData.RotRectangleData.cx	,uY -SData.UData.RotRectangleData.cy)
													-GetSita(rotx-SData.UData.RotRectangleData.cx,roty-SData.UData.RotRectangleData.cy);
				SData.UData.RotRectangleData.s=RegulateAngle(SData.UData.RotRectangleData.s);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotRectangleData.rx,'f',2))
							   <<QString::number(SData.UData.RotRectangleData.ry,'f',2)
							   <<QString::number(SData.UData.RotRectangleData.s*180.0/M_PI,'f',3));
				break;
			case fdRotEllipse:
				SData.UData.RotEllipseData.s=GetSita(uX -SData.UData.RotEllipseData.cx	,uY -SData.UData.RotEllipseData.cy)
													-GetSita(rotx-SData.UData.RotEllipseData.cx,roty-SData.UData.RotEllipseData.cy);
				SData.UData.RotEllipseData.s=RegulateAngle(SData.UData.RotEllipseData.s);
				emit	SignalDrawMessage(QStringList("Radius-X")<<QString("Radius-Y")<<QString("Angle")
					,QStringList(QString::number(SData.UData.RotEllipseData.rx,'f',2))
							   <<QString::number(SData.UData.RotEllipseData.ry,'f',2)
							   <<QString::number(SData.UData.RotEllipseData.s*180.0/M_PI,'f',3));
				break;
			case fdArc:
				SData.UData.ArcData.s1=GetSita(uX -SData.UData.ArcData.cx	,uY -SData.UData.ArcData.cy)
											-GetSita(rotx-SData.UData.ArcData.cx,roty-SData.UData.ArcData.cy);
				SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.ArcData.r,'f',2))
								<<QString::number(SData.UData.ArcData.s1*180.0/M_PI,'f',3)
								<<QString("360"));
				break;
			case fdArc3:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.ArcData.cx,SData.UData.ArcData.cy,SData.UData.ArcData.r);
				A=TmpPoint[1][1]-TmpPoint[0][1];
				B=-(TmpPoint[1][0]-TmpPoint[0][0]);
				C=-TmpPoint[0][0]*TmpPoint[1][1]+TmpPoint[1][0]*TmpPoint[0][1];
				if(A*uX+B*uY+C>=0){
					SData.UData.ArcData.s1=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
					SData.UData.ArcData.s2=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
				}
				else{
					SData.UData.ArcData.s2=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
					SData.UData.ArcData.s1=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
				}
				SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
				SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.CircleData.r,'f',2)));
				break;
			case fdRing:
				SData.UData.ERingData.rx2=fabs(uX-SData.UData.ERingData.cx);
				SData.UData.ERingData.ry2=fabs(uY-SData.UData.ERingData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")
					,QStringList( QString::number(SData.UData.ERingData.rx1,'f',2))
								<<QString::number(SData.UData.ERingData.ry1,'f',2)
								<<QString::number(SData.UData.ERingData.rx2,'f',2)
								<<QString::number(SData.UData.ERingData.ry2,'f',2));
				break;
			case fdLongCircle:
				CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
									, TmpPoint[1][0],TmpPoint[1][1]
									, uX,uY
									, SData.UData.LongCircleData.cx1,SData.UData.LongCircleData.cy1,SData.UData.LongCircleData.r);
				SData.UData.LongCircleData.cx2=SData.UData.LongCircleData.cx1;
				SData.UData.LongCircleData.cy2=SData.UData.LongCircleData.cy1;
				emit	SignalDrawMessage(QStringList("Third Point")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.s1=GetSita(uX  -SData.UData.RingArcData.cx	,uY -SData.UData.RingArcData.cy)
										  -GetSita(rotx-SData.UData.RingArcData.cx ,roty-SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s1=RegulateAngle(SData.UData.RingArcData.s1);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString("360"));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=(uX+TmpPoint[0][0])/2.0;
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.rx1=abs(uX-TmpPoint[0][0])/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;

				emit	SignalDrawMessage(QStringList("Left-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==3){
		switch(CurrentMode){
			case fdEllipse4:
				SData.UData.EllipseData.cx=(TmpPoint[2][0]+uX)/2.0;
				SData.UData.EllipseData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.ry=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.EllipseData.rx=abs(TmpPoint[2][0]-uX)/2.0;
				emit	SignalDrawMessage(QStringList("Right-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
			case fdArc:
				SData.UData.ArcData.s2=GetSita(uX	-SData.UData.ArcData.cx,uY	 -SData.UData.ArcData.cy)
								-GetSita(rotx-SData.UData.ArcData.cx,roty-SData.UData.ArcData.cy);
				SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
				emit	SignalDrawMessage(QStringList("Radius")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.ArcData.r,'f',2))
								<<QString::number(SData.UData.ArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.ArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdLongCircle:
				SData.UData.LongCircleData.cx2=uX;
				SData.UData.LongCircleData.cy2=uY;
				emit	SignalDrawMessage(QStringList("Other circle")
										 ,QStringList(QString::number(SData.UData.LongCircleData.r,'f',2)));
				break;
			case fdRingArc1:
				SData.UData.RingArcData.s2=GetSita(uX	-SData.UData.RingArcData.cx,uY	 -SData.UData.RingArcData.cy)
										  -GetSita(rotx -SData.UData.RingArcData.cx,roty -SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s2=RegulateAngle(SData.UData.RingArcData.s2);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.cx=(TmpPoint[2][0]+uX)/2.0;
				SData.UData.RingArcData.cy=(TmpPoint[0][1]+TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.ry1=abs(TmpPoint[0][1]-TmpPoint[1][1])/2.0;
				SData.UData.RingArcData.rx1=abs(TmpPoint[2][0]-uX)/2.0;
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				SData.UData.RingArcData.s1=0;
				SData.UData.RingArcData.s2=0;
				emit	SignalDrawMessage(QStringList("Right-X")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==4){
		switch(CurrentMode){
			case fdRingArc1:
				SData.UData.RingArcData.rx2=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry2=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.rx2,'f',2)
								<<QString::number(SData.UData.RingArcData.ry2,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.s1=GetSita(uX  -SData.UData.RingArcData.cx	,uY -SData.UData.RingArcData.cy)
										  -GetSita(rotx-SData.UData.RingArcData.cx ,roty-SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s1=RegulateAngle(SData.UData.RingArcData.s1);
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
										,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
											<<QString::number(SData.UData.RingArcData.ry1,'f',2)
											<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
											<<QString("360"));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==5){
		switch(CurrentMode){
			case fdRingArc1:
				SData.UData.RingArcData.rx2=fabs(uX-SData.UData.RingArcData.cx);
				SData.UData.RingArcData.ry2=fabs(uY-SData.UData.RingArcData.cy);
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Radius-X2")<<QString("Radius-Y2")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.rx2,'f',2)
								<<QString::number(SData.UData.RingArcData.ry2,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
			case fdRingArc4:
				SData.UData.RingArcData.s2=GetSita(uX	-SData.UData.RingArcData.cx,uY	 -SData.UData.RingArcData.cy)
										  -GetSita(rotx -SData.UData.RingArcData.cx,roty -SData.UData.RingArcData.cy);
				SData.UData.RingArcData.s2=RegulateAngle(SData.UData.RingArcData.s2);
				SData.UData.RingArcData.rx2=0;
				SData.UData.RingArcData.ry2=0;
				emit	SignalDrawMessage(QStringList("Radius-X1")<<QString("Radius-Y1")<<QString("Start-R")<<QString("End-R")
					,QStringList( QString::number(SData.UData.RingArcData.rx1,'f',2))
								<<QString::number(SData.UData.RingArcData.ry1,'f',2)
								<<QString::number(SData.UData.RingArcData.s1*180.0/M_PI,'f',3)
								<<QString::number(SData.UData.RingArcData.s2*180.0/M_PI,'f',3));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==6){
		switch(CurrentMode){
			case fdRingArc4:
				SData.UData.RingArcData.ry2=abs(SData.UData.RingArcData.cy-uY);
				SData.UData.RingArcData.rx2=SData.UData.RingArcData.ry2;
				emit	SignalDrawMessage(QStringList("Top-Y2")<<QString("Bottom-Y2")
										,QStringList(QString::number(uY,'f',2))
										<<QString::number(uY,'f',2));
				break;
		}
		RepaintAll();
	}
	else if(DrawStage==7){
		switch(CurrentMode){
			case fdRingArc4:
				SData.UData.RingArcData.rx2=abs(SData.UData.RingArcData.cx-uX);
				emit	SignalDrawMessage(QStringList("Right-X2")
							,QStringList(QString::number(uX,'f',2)));
				break;
		}
		RepaintAll();
	}
	else{
		if(FModeRepaintOnMouseMove==true){
			repaint();
		}
	}
}

void	mtFrameDraw3D::wheelEvent ( QWheelEvent * event )
{
	emit	SignalWheel(event);
}


void mtFrameDraw3D::PutCrossLine(QPainter &Pnt ,int x,int y )
{
	Pnt.drawLine(0,y,width(),y);
	Pnt.drawLine(x,0,x,height());
}

void mtFrameDraw3D::mouseReleaseEvent ( QMouseEvent * Ev )
{
	//int	X=Ev->x();
	//int	Y=Ev->y();
	//bool	mvalid=true;
	//mtMousePoint(Ev,X,Y,mvalid);
	if(CancelClicked==true){
		return;
	}

	if(DblClickMode==false){
		if(ShiftingMode==true){
			ShiftingMode=false;
			return;
		}

		ShapePoint3D	*c;
		ShapePoint3D	*d;
		ShapePoint3D	*q;
		int	X=Ev->x();
		int	Y=Ev->y();
		double	A,B,C;

		DrawingMode	CurrentMode=FDrawMode;
		ShiftingMode=false;

		bool	mvalid=true;
		mtMousePoint(Ev,X,Y,mvalid);
		if(mvalid==false){
			return;
		}

		FCancelDraw=false;

		int uX, uY;
		GetCanvasToUniverse(MousePressX, MousePressY ,uX, uY);
		if(LeftClicked==true){
			LastMouseDownPointX=uX;
			LastMouseDownPointY=uY;
			emit	SignalJustMouseLRelease(uX,uY);

			if(CancelClicked==true){
				return;
			}
			if(GetMode()==fdNone || GetMode()==fdPoint){
				mtMouseLDown(Ev,X,Y);
			}
			if(CurrentMode==fdNone){
				RepaintAll();
				return;
			}
			if(FCancelDraw==true){
				RepaintAll();
				return;
			}
			if((Ev->modifiers() & Qt::ShiftModifier)!=0){
				RepaintAll();
				return;
			}

			if(DrawStage==0){
				SData.dtype=CurrentMode;
				if(DrawStartEvent!=NULL)
					DrawStartEvent(this,X,Y);
				switch(CurrentMode){
					case fdPoint:
						SData.UData.PointData.x=uX;
						SData.UData.PointData.y=uY;
						DrawStage++;
						SData.LineWidth=LineWidth;
						DrawingOn();
						emit SignalDrawing(fdPoint,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor(Qt::ArrowCursor);
						break;
					case fdLine:
						FOnDrawMode=true;
						SData.UData.LineData.x=uX;
						SData.UData.LineData.y=uY;
						SData.UData.LineData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLine,DrawStage);
						//setCursor=(TCursor)crLine2;
						break;
					case fdHalfLine:
						FOnDrawMode=true;
						SData.UData.HalfLineData.x=uX;
						SData.UData.HalfLineData.y=uY;
						SData.UData.HalfLineData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHalfLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdHChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdVChoppedLine:
						FOnDrawMode=true;
						SData.UData.ChoppedLineData.x1=uX;
						SData.UData.ChoppedLineData.y1=uY;
						SData.UData.ChoppedLineData.x2=uX;
						SData.UData.ChoppedLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdVChoppedLine,DrawStage);
						//setCursor=(TCursor)crHalfLine2;
						break;
					case fdSingleArrow:
						FOnDrawMode=true;
						SData.UData.SingleArrowLineData.x1=uX;
						SData.UData.SingleArrowLineData.y1=uY;
						SData.UData.SingleArrowLineData.x2=uX;
						SData.UData.SingleArrowLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdSingleArrow,DrawStage);
						//setCursor=(TCursor)crArrowLine2;
						break;
					case fdDualArrow:
						FOnDrawMode=true;
						SData.UData.DualArrowLineData.x1=uX;
						SData.UData.DualArrowLineData.y1=uY;
						SData.UData.DualArrowLineData.x2=uX;
						SData.UData.DualArrowLineData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdDualArrow,DrawStage);
						//setCursor=(TCursor)crArrowLine2;
						break;
					case fdRectangle:
						FOnDrawMode=true;
						SData.UData.RectangleData.x1=uX;
						SData.UData.RectangleData.y1=uY;
						SData.UData.RectangleData.x2=uX;
						SData.UData.RectangleData.y2=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRectangle,DrawStage);
						//setCursor=(TCursor)crRect2;
						break;
					case fdRotRectangle:
						FOnDrawMode=true;
						SData.UData.RotRectangleData.cx=uX;
						SData.UData.RotRectangleData.cy=uY;
						SData.UData.RotRectangleData.rx=0;
						SData.UData.RotRectangleData.ry=0;
						SData.UData.RotRectangleData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						//setCursor=(TCursor)crRotRect2;
						break;
					case fdCircle:
						FOnDrawMode=true;
						SData.UData.CircleData.cx=uX;
						SData.UData.CircleData.cy=uY;
						SData.UData.CircleData.r=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdCircle3:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdEllipse:
						FOnDrawMode=true;
						SData.UData.EllipseData.cx=uX;
						SData.UData.EllipseData.cy=uY;
						SData.UData.EllipseData.rx=0;
						SData.UData.EllipseData.ry=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						TmpPoint[3][0]=TmpPoint[2][0]=TmpPoint[1][0]=TmpPoint[0][0]=uX;
						TmpPoint[3][1]=TmpPoint[2][1]=TmpPoint[1][1]=TmpPoint[0][1]=uY;
						SData.UData.EllipseData.rx=10;
						SData.UData.EllipseData.ry=10;
						SData.UData.EllipseData.cx=uX;
						SData.UData.EllipseData.cy=uY+SData.UData.EllipseData.rx;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotEllipse:
						FOnDrawMode=true;
						SData.UData.RotEllipseData.cx=uX;
						SData.UData.RotEllipseData.cy=uY;
						SData.UData.RotEllipseData.rx=0;
						SData.UData.RotEllipseData.ry=0;
						SData.UData.RotEllipseData.s=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdArc:
						FOnDrawMode=true;
						SData.UData.ArcData.cx=uX;
						SData.UData.ArcData.cy=uY;
						SData.UData.ArcData.r=0;
						SData.UData.ArcData.s1=0;
						SData.UData.ArcData.s2=2*M_PI;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc2;
						break;
					case fdArc3:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdFree:
						FOnDrawMode=true;
						if(SData.UData.FreeData.points==NULL){
							SData.UData.FreeData.points = new NPListPack<ShapePoint3D>();
							}
						SData.UData.FreeData.points->AppendList(new ShapePoint3D(uX,uY));
						rotx=uX;
						roty=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdFree,DrawStage);
						//setCursor=(TCursor)crFree2;
						break;
					case fdPoly:
						FOnDrawMode=true;
						if(SData.UData.PolyData.points==NULL){
							SData.UData.PolyData.points = new NPListPack<ShapePoint3D>();
							}
						SData.UData.PolyData.points->AppendList(new ShapePoint3D(uX,uY));
						rotx=uX;
						roty=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdPoly,DrawStage);
						//setCursor=(TCursor)crPoly2;
						break;
					/*
					case fdMove:
						FOnDrawMode=true;
						DrawStage++;
						if(SData.UData.MoveData.points==NULL){
							SData.UData.MoveData.points = new NPListPack<ShapePoint3D>();
							}
						DrawingOn();
						emit SignalDrawing(fdMove,DrawStage);
						//setCursor=(TCursor)crMove2;
						break;
					*/
					case fdRing:
						FOnDrawMode=true;
						PutPixelOnly(X,Y,FColor);
						SData.UData.ERingData.cx=uX;
						SData.UData.ERingData.cy=uY;
						SData.UData.ERingData.rx1=0;
						SData.UData.ERingData.ry1=0;
						SData.UData.ERingData.rx2=0;
						SData.UData.ERingData.ry2=0;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						//setCursor=(TCursor)crRing2;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						TmpPoint[0][0]=uX;
						TmpPoint[0][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdRingArc1:
						FOnDrawMode=true;
						SData.UData.RingArcData.cx=uX;
						SData.UData.RingArcData.cy=uY;
						SData.UData.RingArcData.rx1=0;
						SData.UData.RingArcData.ry1=0;
						SData.UData.RingArcData.rx2=0;
						SData.UData.RingArcData.ry2=0;
						SData.UData.RingArcData.s1=0;
						SData.UData.RingArcData.s2=2*M_PI;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc2;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						TmpPoint[3][0]=TmpPoint[2][0]=TmpPoint[1][0]=TmpPoint[0][0]=uX;
						TmpPoint[3][1]=TmpPoint[2][1]=TmpPoint[1][1]=TmpPoint[0][1]=uY;
						SData.UData.RingArcData.rx1=10;
						SData.UData.RingArcData.ry1=10;
						SData.UData.RingArcData.cx=uX;
						SData.UData.RingArcData.cy=uY+SData.UData.EllipseData.rx;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					}
				}
			else if(DrawStage==1){
				switch(CurrentMode){
					case fdLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crLine1;
						break;
					case fdHalfLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHalfLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdChoppedLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdHChoppedLine:
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdHChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdVChoppedLine:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdVChoppedLine,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crHalfLine1;
						break;
					case fdSingleArrow:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdSingleArrow,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArrowLine1;
						break;
					case fdDualArrow:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdDualArrow,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArrowLine1;
						break;
					case fdRectangle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						if(SData.UData.RectangleData.x1>SData.UData.RectangleData.x2)
							swap(SData.UData.RectangleData.x1,SData.UData.RectangleData.x2);
						if(SData.UData.RectangleData.y1>SData.UData.RectangleData.y2)
							swap(SData.UData.RectangleData.y1,SData.UData.RectangleData.y2);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRectangle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRect1;
						break;
					case fdRotRectangle:
						FOnDrawMode=true;
						rotx=uX;
						roty=uY;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						//setCursor=(TCursor)crRotRect3;
						break;
					case fdCircle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crCircle1;
						break;
					case fdCircle3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdEllipse:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotEllipse:
						FOnDrawMode=true;
						rotx=uX;
						roty=uY;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						//setCursor=(TCursor)crRotEllipse3;
						break;
					case fdArc:
						FOnDrawMode=true;
						rotx=SData.UData.ArcData.cx+(int)((double)SData.UData.ArcData.r*cos(SData.UData.ArcData.s1));
						roty=SData.UData.ArcData.cy+(int)((double)SData.UData.ArcData.r*sin(SData.UData.ArcData.s1));
						mtMouseMove(Ev, X, Y);
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc3;
						break;
					case fdArc3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;
					case fdFree:
						mtMouseMove(Ev, X, Y);
						c=SData.UData.FreeData.points->GetFirst();
						d=SData.UData.FreeData.points->GetLast();
						SData.LineWidth=LineWidth;
						if(FClosedArea==true){
							if(c->x!=d->x || c->y!=d->y){
								SData.UData.FreeData.points->AppendList(new ShapePoint3D(c->x,c->y));
							}
						}
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdFree,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crFree1;
						break;
					case fdPoly:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						if(SData.UData.PolyData.points==NULL){
							SData.UData.PolyData.points = new NPListPack<ShapePoint3D>();
						}
						q=SData.UData.PolyData.points->GetLast();
						if((q!=NULL && (q->x!=uX || q->y!=uY)) || (q==NULL)){
							SData.UData.PolyData.points->AppendList(new ShapePoint3D(uX,uY));
						}

						rotx=uX;
						roty=uY;
						DrawingOn();
						emit SignalDrawing(fdPoly,DrawStage);
						//setCursor=(TCursor)crPoly2;
						break;
					/*
					case fdMove:
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdMove,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crMove1;
						break;
					*/
					case fdRing:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						//setCursor=(TCursor)crRing2;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						//setCursor=(TCursor)crCircle2;
						break;	
					case fdRingArc1:
						FOnDrawMode=true;
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s1));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s1));
						mtMouseMove(Ev, X, Y);
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc3;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
						}
				}
			else if(DrawStage==2){
				switch(CurrentMode){
					case fdCircle3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.CircleData.cx,SData.UData.CircleData.cy,SData.UData.CircleData.r);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdCircle3,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdEllipse4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					case fdRotRectangle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotRectangle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRotEllipse:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRotEllipse,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdArc:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.ArcData.cx+(int)((double)SData.UData.ArcData.r*cos(SData.UData.ArcData.s2));
						roty=SData.UData.ArcData.cy+(int)((double)SData.UData.ArcData.r*sin(SData.UData.ArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					case fdArc3:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.ArcData.cx,SData.UData.ArcData.cy,SData.UData.ArcData.r);
						A=TmpPoint[1][1]-TmpPoint[0][1];
						B=-(TmpPoint[1][0]-TmpPoint[0][0]);
						C=-TmpPoint[0][0]*TmpPoint[1][1]+TmpPoint[1][0]*TmpPoint[0][1];
						if(A*uX+B*uY+C>=0){
							SData.UData.ArcData.s1=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
							SData.UData.ArcData.s2=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
						}
						else{
							SData.UData.ArcData.s2=GetSita(TmpPoint[0][0] -SData.UData.ArcData.cx	,TmpPoint[0][1] -SData.UData.ArcData.cy);
							SData.UData.ArcData.s1=GetSita(TmpPoint[1][0] -SData.UData.ArcData.cx	,TmpPoint[1][1] -SData.UData.ArcData.cy);
						}
						SData.UData.ArcData.s1=RegulateAngle(SData.UData.ArcData.s1);
						SData.UData.ArcData.s2=RegulateAngle(SData.UData.ArcData.s2);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc3,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRing:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRing,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRing1;
						break;
					case fdLongCircle:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						CalcCircleFrom3Points(TmpPoint[0][0],TmpPoint[0][1]
											, TmpPoint[1][0],TmpPoint[1][1]
											, TmpPoint[2][0],TmpPoint[2][1]
											, SData.UData.LongCircleData.cx1,SData.UData.LongCircleData.cy1,SData.UData.LongCircleData.r);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						FOnDrawMode=false;
						//setCursor=(TCursor)crRotRect1;
						break;
					case fdRingArc1:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s2));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;
					}
				}
			else if(DrawStage==3){
				switch(CurrentMode){
					case fdEllipse4:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[3][0]=uX;
						TmpPoint[3][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdEllipse4,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						break;
					case fdArc:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdArc,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crArc1;
						break;
					case fdLongCircle:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdLongCircle,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crRotRect1;
						break;
					//case fdFree:
					case fdRingArc1:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s1));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s1));
						TmpPoint[3][0]=uX;
						TmpPoint[3][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						break;
					}
				}
			else if(DrawStage==4){
				switch(CurrentMode){
					case fdRingArc1:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc1,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						//setCursor=(TCursor)crEllipse1;
						break;
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						rotx=SData.UData.RingArcData.cx+(int)((double)SData.UData.RingArcData.rx1*cos(SData.UData.RingArcData.s2));
						roty=SData.UData.RingArcData.cy+(int)((double)SData.UData.RingArcData.ry1*sin(SData.UData.RingArcData.s2));
						//P=GetClientOrigin();
						//::SetCursorPos(P.x+rotx,P.y+roty);
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crArc4;
						break;
					}
				}
			else if(DrawStage==5){
				switch(CurrentMode){
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[1][0]=uX;
						TmpPoint[1][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						//setCursor=(TCursor)crEllipse2;
						break;				}
			}
			else if(DrawStage==6){
				switch(CurrentMode){
					case fdRingArc4:
						FOnDrawMode=true;
						mtMouseMove(Ev, X, Y);
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						break;
				}
			}
			else if(DrawStage==7){
				switch(CurrentMode){
					case fdRingArc4:
						mtMouseMove(Ev, X, Y);
						SData.LineWidth=LineWidth;
						TmpPoint[2][0]=uX;
						TmpPoint[2][1]=uY;
						DrawStage++;
						DrawingOn();
						emit SignalDrawing(fdRingArc4,DrawStage);
						FOnDrawMode=false;
						DrawEnd();
						emit SignalDrawEnd();
						break;
				}
			}

			ChangeCursor(CurrentMode ,DrawStage);
		}
		else
		if((Ev->buttons()&Qt::SHIFT)!=0
		&& RightClicked==true){
			RepaintAll();
			return;
			}
		else
		if(RightClicked==true){
			LastMouseDownPointX=uX;
			LastMouseDownPointY=uY;
			emit	SignalJustMouseRRelease(uX,uY);

			mtMouseRDown(Ev, X,Y);
			if((Ev->modifiers() & Qt::ShiftModifier)!=0){
				RepaintAll();
				return;
			}
			if(CurrentMode==fdPoly){
				if(SData.UData.PolyData.points!=NULL){
					ShapePoint3D	*p=SData.UData.PolyData.points->GetLast();
					if(p!=NULL){
						SData.UData.PolyData.points->RemoveList(p);
						delete	p;
						if(SData.UData.PolyData.points->GetFirst()==NULL){
							DrawStage=0;
							FOnDrawMode=false;
							CancelDraw();
							emit SignalCancelDraw();
						}
					}
				}
			}
			else{
				if(CurrentMode==fdFree
				&& SData.UData.FreeData.points!=NULL){
					delete	SData.UData.FreeData.points;
					SData.UData.FreeData.points=NULL;
					}
	
				if(DrawStage>0)
					DrawStage--;
				if(CurrentMode==fdRotRectangle){
					SData.UData.RotRectangleData.s=0;
				}
				FOnDrawMode=false;
				CancelDraw();
				emit SignalCancelDraw();
			}
			ChangeCursor(CurrentMode ,DrawStage);
		}
	}
	else{	//When double click occurs
		int	X=Ev->x();
		int	Y=Ev->y();
		DrawingMode	CurrentMode=FDrawMode;

		if(LeftClicked==true){
			if(CurrentMode==fdPoly){
				SData.LineWidth=LineWidth;
				if(SData.UData.PolyData.points==NULL){
					SData.UData.PolyData.points = new NPListPack<ShapePoint3D>();
				}
				ShapePoint3D	*c=SData.UData.PolyData.points->GetFirst();
				ShapePoint3D	*d=SData.UData.PolyData.points->GetLast();
				if(FClosedArea==true && c!=NULL && d!=NULL){
					if(c->x!=d->x || c->y!=d->y){
						SData.UData.PolyData.points->AppendList(new ShapePoint3D(c->x,c->y));
						}
					}
				DrawStage++;
				DrawingOn();
				emit SignalDrawing(fdPoly,DrawStage);

				FOnDrawMode=false;
				DrawEnd();
				emit SignalDrawEnd();
				//setCursor=(TCursor)crPoly1;
				RepaintAll();
				return;
			}
			else{
				QMouseEvent	PushedEvent(Ev->type(),Ev->pos(),Qt::LeftButton,Ev->buttons() | Qt::LeftButton,Ev->modifiers());
				emit	SignalDoubleClick(&PushedEvent);
			}
		}
		else
		if(RightClicked==true && CurrentMode==fdPoly){
			mtMouseRDown(Ev, X,Y);
			FOnDrawMode=false;
			CancelDraw();
			emit SignalCancelDraw();
		}
		else{
			if(RightClicked==true){
				QMouseEvent	PushedEvent(Ev->type(),Ev->pos(),Qt::RightButton,Ev->buttons(),Ev->modifiers());
				emit	SignalDoubleClick(Ev);
			}
		}
		ChangeCursor(CurrentMode ,DrawStage);
	}
	RepaintAll();
}

struct	TmpPoint
{
	short x,y;
};

void mtFrameDraw3D::Clear(void)
{
	if(FDrawMode==fdFree){
		if(SData.UData.FreeData.points!=NULL){
			SData.UData.FreeData.points->RemoveAll();
			}
		}
	else if(FDrawMode==fdPoly){
		if(SData.UData.PolyData.points!=NULL){
			SData.UData.PolyData.points->RemoveAll();
			}
		}
	else if(FDrawMode==fdMove){
		if(SData.UData.MoveData.points!=NULL){
			SData.UData.MoveData.points->RemoveAll();
			}
		}

	DrawStage=0;
	FOnDrawMode=false;
	SetStartCursor();
}

void mtFrameDraw3D::GetEffectiveArea(int &minx,int &miny,int &maxx ,int &maxy)
{
	minx=0;
	miny=0;
	maxx=width();
	maxy=height();
}

void	mtFrameDraw3D::keyPressEvent ( QKeyEvent * event )
{
	if(event->isAccepted ()==true){
		QWidget::keyPressEvent ( event );
		return;
	}
	QPoint	P=GetCursorPos();
	if(0<=P.x() && P.x()<width() && 0<=P.y() && P.y()<height()){
		bool Accept=false;
		emit SignalKeyPress(event->key() ,P,Accept);
		if(Accept==true){
			event->accept();
		}
		if(Accept==false){
			/*
			if(event->key()==Qt::Key_Up){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x(), P.y()-1);
				}
				else{
					SetMouseCursorPos(P.x(), P.y()-10);
				}
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Down){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x(), P.y()+1);
				}
				else{
					SetMouseCursorPos(P.x(), P.y()+10);
				}
				event->accept();
			}
			else 
			*/
			if(event->key()==Qt::Key_Left){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x()-1, P.y());
				}
				else{
					SetMouseCursorPos(P.x()-10, P.y());
				}
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Right){
				if((event->modifiers() & Qt::ShiftModifier)==0){
					SetMouseCursorPos(P.x()+1, P.y());
				}
				else{
					SetMouseCursorPos(P.x()+10, P.y());
				}
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter){
				QMouseEvent	LMouse(QEvent::MouseButtonPress
								,P
								,Qt::LeftButton
								,Qt::LeftButton
								,Qt::NoModifier);
				mousePressEvent(&LMouse);
				mouseReleaseEvent(&LMouse);
				event->accept();
			}
			else
			if(event->key()==Qt::Key_Escape){
				QMouseEvent	LMouse(QEvent::MouseButtonPress
								,P
								,Qt::RightButton
								,Qt::RightButton
								,Qt::NoModifier);
				mousePressEvent(&LMouse);
				mouseReleaseEvent(&LMouse);
				event->accept();
			}
		}
	}
	else{
		QWidget::keyPressEvent ( event );
	}
}

QPoint	mtFrameDraw3D::GetCursorPos( void)
{
	const	QCursor	C=cursor ();
	return QWidget::mapFromGlobal (C.pos());
}

void	mtFrameDraw3D::SetMouseCursorPos(int XonG, int YonG)
{
	const	QCursor	C=cursor ();
	const QPoint pos(XonG,YonG);
	QPoint P=QWidget::mapToGlobal (pos);
	C.setPos(P);
}

void	mtFrameDraw3D::ExecuteMouseMove(int XonG, int YonG)
{
	QPoint position(XonG, YonG);
	QMouseEvent Ev( QEvent::MouseMove
					, position
					, Qt::NoButton
					, Qt::NoButton
					, Qt::NoModifier);
	mouseMoveEvent(&Ev); 
}

QString	mtFrameDraw3D::ToString(DrawingMode mode)
{
	QString	Ret;
	switch(FDrawMode){
		case fdArc:
			Ret=/**/"fdArc";
			break;
		case fdArc3:
			Ret=/**/"fdArc3";
			break;
		case fdChoppedLine:
			Ret=/**/"fdChoppedLine";
			break;
		case fdHChoppedLine:
			Ret=/**/"fdHChoppedLine";
			break;
		case fdVChoppedLine:
			Ret=/**/"fdVChoppedLine";
			break;
		case fdCircle:
			Ret=/**/"fdCircle";
			break;
		case fdCircle3:
			Ret=/**/"fdCircle3";
			break;
		case fdDualArrow:
			Ret=/**/"fdDualArrow";
			break;
		case fdEllipse:
			Ret=/**/"fdEllipse";
			break;
		case fdEllipse4:
			Ret=/**/"fdEllipse4";
			break;
		case fdFree:
			Ret=/**/"fdFree";
			break;
		case fdHalfLine:
			Ret=/**/"fdHalfLine";
			break;
		case fdLine:
			Ret=/**/"fdLine";
			break;
		case fdMove:
			Ret=/**/"fdMove";
			break;
		case fdNone:
			Ret=/**/"fdNone";
			break;
		case fdPoint:
			Ret=/**/"fdPoint";
			break;
		case fdPoly:
			Ret=/**/"fdPoly";
			break;
		case fdRectangle:
			Ret=/**/"fdRectangle";
			break;
		case fdRing:
			Ret=/**/"fdRing";
			break;
		case fdRotEllipse:
			Ret=/**/"fdRotEllipse";
			break;
		case fdRotRectangle:
			Ret=/**/"fdRotRectangle";
			break;
		case fdSingleArrow:
			Ret=/**/"fdSingleArrow";
			break;
		case fdSpoint:
			Ret=/**/"fdSpoint";
			break;
		case fdRingArc1:
			Ret=/**/"fdRingArc1";
			break;
		case fdRingArc4:
			Ret=/**/"fdRingArc4";
			break;
	}
	return Ret;
}

void mtFrameDraw3D::ChangeMode(DrawingMode newmode)
{
	FDrawMode=newmode;
	ChangeCursor(newmode ,DrawStage);
}

void	mtFrameDraw3D::SetCursor(mtFrameDraw3D::DrawingMode mode)
{
	ChangeCursor(mode ,0);
}

void mtFrameDraw3D::ChangeCursor(DrawingMode newmode ,int CurrentDrawStage)
{
	switch(newmode){
			case fdArc:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdArc3:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdHChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdVChoppedLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdCircle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				break;
			case fdCircle3:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/EllipseTop.PNG"),8,1));
				break;
			case fdDualArrow:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdEllipse:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				break;
			case fdEllipse4:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/EllipseTop.PNG"),8,1));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				break;
			case fdFree:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(QPixmap(":/Icon/Free1.PNG"),11,0));
				break;
			case fdHalfLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdLine:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdMove:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(QPixmap(":/Icon/MoveItem1.PNG"),7,7));
				break;
			case fdNone:
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdPoint:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdPoly:
				setCursor(QCursor(QPixmap(":/Icon/Polygon1.PNG"),9,9));
				break;
			case fdRectangle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle1.PNG"),4,4));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle2.PNG"),12,12));
				//setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRing:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRotEllipse:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse1.PNG"),7,7));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse2.PNG"),12,8));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/Ellipse3.PNG"),8,14));
				else if(CurrentDrawStage==3)
					setCursor(QCursor(QPixmap(":/Icon/RotEllipse1.PNG"),12,14));
				//setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRotRectangle:
				if(CurrentDrawStage==0)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle1.PNG"),4,4));
				else if(CurrentDrawStage==1)
					setCursor(QCursor(QPixmap(":/Icon/Rectangle2.PNG"),12,12));
				else if(CurrentDrawStage==2)
					setCursor(QCursor(QPixmap(":/Icon/RotRectangle1.PNG"),12,14));
				break;
			case fdSingleArrow:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdSpoint:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRingArc1:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			case fdRingArc4:
				//setCursor(QCursor(QPixmap(":/Icon/***.png")));
				setCursor(QCursor(Qt::ArrowCursor));
				break;
			default:
				setCursor(QCursor(Qt::ArrowCursor));
	}
}

void mtFrameDraw3D::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtFrameDraw3D::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}

void mtFrameDraw3D::Loaded(void)
{
	/*
	TCustomControl::Loaded();

	if(LoadedMode==false){
		LoadedMode=true;
		Screen->Cursors[crLine1 	 ] = LoadCursor(HInstance, "LINE1");
		Screen->Cursors[crLine2 	 ] = LoadCursor(HInstance, "LINE2");
		Screen->Cursors[crMove1 	 ] = LoadCursor(HInstance, "MOVE1");
		Screen->Cursors[crMove2 	 ] = LoadCursor(HInstance, "MOVE2");
		Screen->Cursors[crRing1 	 ] = LoadCursor(HInstance, "RING1");
		Screen->Cursors[crRing2 	 ] = LoadCursor(HInstance, "RING2");
		Screen->Cursors[crPoly1 	 ] = LoadCursor(HInstance, "POLY1");
		Screen->Cursors[crPoly2 	 ] = LoadCursor(HInstance, "POLY2");
		Screen->Cursors[crFree1 	 ] = LoadCursor(HInstance, "FREE1");
		Screen->Cursors[crFree2 	 ] = LoadCursor(HInstance, "FREE2");
		Screen->Cursors[crRotRect1	 ] = LoadCursor(HInstance, "ROTRECT1");
		Screen->Cursors[crRotRect2	 ] = LoadCursor(HInstance, "ROTRECT2");
		Screen->Cursors[crRotRect3	 ] = LoadCursor(HInstance, "ROTRECT3");
		Screen->Cursors[crEllipse1	 ] = LoadCursor(HInstance, "ELLIPSE1");
		Screen->Cursors[crEllipse2	 ] = LoadCursor(HInstance, "ELLIPSE2");
		Screen->Cursors[crRotEllipse3] = LoadCursor(HInstance, "ROTELLIPSE3");
		Screen->Cursors[crRect1 	 ] = LoadCursor(HInstance, "RECT1");
		Screen->Cursors[crRect2 	 ] = LoadCursor(HInstance, "RECT2");
		Screen->Cursors[crHalfLine1  ] = LoadCursor(HInstance, "HALFLINE1");
		Screen->Cursors[crHalfLine2  ] = LoadCursor(HInstance, "HALFLINE2");
		Screen->Cursors[crCircle1	 ] = LoadCursor(HInstance, "CIRCLE1");
		Screen->Cursors[crCircle2	 ] = LoadCursor(HInstance, "CIRCLE2");
		Screen->Cursors[crArc1		 ] = LoadCursor(HInstance, "ARC1");
		Screen->Cursors[crArc2		 ] = LoadCursor(HInstance, "ARC2");
		Screen->Cursors[crArc3		 ] = LoadCursor(HInstance, "ARC3");
		Screen->Cursors[crArc4		 ] = LoadCursor(HInstance, "ARC4");
		Screen->Cursors[crArrowLine1 ] = LoadCursor(HInstance, "ARROWLINE1");
		Screen->Cursors[crArrowLine2 ] = LoadCursor(HInstance, "ARROWLINE2");
		Screen->Cursors[crSpoint	 ] = LoadCursor(HInstance, "SPOINT");
		Screen->Cursors[crSmallCross ] = LoadCursor(HInstance, "SMALLCROSS");
		}
	*/
}

void mtFrameDraw3D::SetStartCursor(void)
{
	/*
	switch(FDrawMode){
		case fdPoint:
			Cursor=(TCursor)crSmallCross;
			break;
		case fdLine:
			Cursor=(TCursor)crLine1;
			break;
		case fdHalfLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdHChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdVChoppedLine:
			Cursor=(TCursor)crHalfLine1;
			break;
		case fdRectangle:
			Cursor=(TCursor)crRect1;
			break;
		case fdRotRectangle:
			Cursor=(TCursor)crRotRect1;
			break;
		case fdCircle:
			Cursor=(TCursor)crCircle1;
			break;
		case fdCircle3:
			Cursor=(TCursor)crCircle1;
			break;
		case fdEllipse:
			Cursor=(TCursor)crEllipse1;
			break;
		case fdEllipse4:
			Cursor=(TCursor)crEllipse4;
			break;
		case fdRotEllipse:
			Cursor=(TCursor)crEllipse1;
			break;
		case fdArc:
			Cursor=(TCursor)crArc1;
			break;
		case fdArc3:
			Cursor=(TCursor)crArc1;
			break;
		case fdFree:
			Cursor=(TCursor)crFree1;
			break;
		case fdPoly:
			Cursor=(TCursor)crPoly1;
			break;
		case fdMove:
			Cursor=(TCursor)crMove1;
			break;
		case fdRing:
			Cursor=(TCursor)crRing1;
			break;
		case fdSingleArrow:
			Cursor=(TCursor)crArrowLine1;
			break;
		case fdDualArrow:
			Cursor=(TCursor)crArrowLine1;
			break;
		case fdSpoint:
			Cursor=(TCursor)crSpoint;
			break;
		case fdRingArc1:
			Cursor=(TCursor)crRingArc1;
			break;
		case fdRingArc4:
			Cursor=(TCursor)crRingArc4;
			break;
		case fdNone:
			Cursor=(TCursor)crDefault;
			break;
		}
	*/
}

void	mtFrameDraw3D::RepaintAll(void)
{
	update();
}

