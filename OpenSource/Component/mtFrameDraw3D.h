#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtFrameDraw3D.h
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include <QMetaType>
#include <QWidget>
#include <QMutex>
#include "NList.h"
#include <QIODevice>
#include "XTypeDef.h"
#include "X3DCommon.h"

class   ShapePoint3D : public NPList<ShapePoint3D>
{
public:
    double  x,y;
    ShapePoint3D(void){}
    explicit	ShapePoint3D(int _x ,int _y) : x(_x),y(_y){}
    explicit	ShapePoint3D(double _x ,double _y) : x(_x),y(_y){}
};

class   ColPoint3D : public NPList<ColPoint3D>
{
  public:
    double  x,y;
    QColor  col;
	bool	ColEffectiveMask;

    ColPoint3D(void){}
    explicit	ColPoint3D(int _x ,int _y ,QColor &c)		: x(_x),y(_y),col(c){	ColEffectiveMask=false;}
    explicit	ColPoint3D(double _x ,double _y ,QColor &c) : x(_x),y(_y),col(c){	ColEffectiveMask=false;}
    explicit	ColPoint3D(double _x ,double _y ,bool mask) : x(_x),y(_y)		{	ColEffectiveMask=mask;}
    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

    short   X,Y;
    short   EffectiveMode;

};

class mtFrameDraw3D : public QWidget
{
    Q_OBJECT
	Q_ENUMS(DrawingMode)
	Q_PROPERTY(DrawingMode FrameMode READ GetMode WRITE SetMode)
	Q_PROPERTY(QColor FrameColor READ GetFrameColor WRITE SetFrameColor)

public:
    explicit	mtFrameDraw3D(QWidget *parent = 0);
    ~mtFrameDraw3D();

	enum    DrawingMode{
                 fdNone					=0
				,fdPoint				=1
                ,fdLine					=2
                ,fdHalfLine				=3
                ,fdChoppedLine			=4
                ,fdRectangle			=5
                ,fdRotRectangle			=6
                ,fdCircle				=7
				,fdCircle3				=20
                ,fdEllipse				=8
				,fdEllipse4				=19
                ,fdRotEllipse			=9
                ,fdArc					=10
				,fdArc3					=18
                ,fdFree					=11
                ,fdPoly					=12
                ,fdMove					=13
                ,fdRing					=14
                ,fdSingleArrow			=15
                ,fdDualArrow			=16
                ,fdSpoint				=17
				,fdVChoppedLine			=21
				,fdHChoppedLine			=22
				,fdLongCircle			=23
				,fdRingArc1				=24		//from Center
				,fdRingArc4				=25
	};


	void	SetMode(DrawingMode mode);
	DrawingMode GetMode(void)	const	{	return(FDrawMode);	}
	void	SetEnableShiftImage(bool b);
	bool	GetEnableShiftImage(void)	const;
	void	SetFrameColor(const QColor &col){	FColor=col;	}
	QColor	GetFrameColor(void)	const	{	return(FColor);	}
	void	GetCanvasToUniverse(int gx, int gy ,int &ux, int &uy)	const;

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

	void	Clear(void);

	//virtual	void	ShiftPressed(int gx ,int gy){}
	virtual	void	mtMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid){	valid=true;	};
	virtual	void	mtMouseLDown(QMouseEvent *Ev ,int x ,int y){}
	virtual	void	mtMouseRDown(QMouseEvent *Ev ,int x ,int y){}
	virtual	void	mtMouseMove(QMouseEvent *Ev ,int x ,int y){}
	//virtual	void	mtMouseLUp(QMouseEvent *Ev ,int x ,int y){}
	//virtual	void	mtMouseRUp(QMouseEvent *Ev ,int x ,int y){}
	virtual	void	DrawingOn(void){}
	virtual	void	DrawEnd(void){}
	virtual	void	CancelDraw(void){}
	QPoint	GetCursorPos( void);
	void	SetMouseCursorPos(int XonG, int YonG);
	void	ExecuteMouseMove(int XonG, int YonG);
	QString	ToString(DrawingMode mode);
	void	setShiftMode(bool enable){ NoShiftCanvasMode = !enable; };
	void	setImageShiftDelay(int msec){ ImageShiftDelay = msec; };

	void	(*DrawStartEvent)(QWidget *Sender, int &X ,int &Y);

	struct  _ShapeData{		//ç¿ïWånÇÕìôî{Ç…Ç®ÇØÇÈíl
	    DrawingMode dtype;
		union _UUU{
			struct  _PointData{
				double x;
	            double y;
		        }PointData;
			struct  _LineData{
				double	x;
	            double	y;
		        double  s;
			    }LineData;
	        struct  _HalfLineData{
		        double	x;
			    double	y;
				double  s;
	            }HalfLineData;
		    struct  _ChoppedLineData{
			    double x1,y1;
				double x2,y2;
	            }ChoppedLineData;
		    struct  _RectangleData{
			    double x1,y1;
				double x2,y2;
	            }RectangleData;
		    struct  _RotRectangleData{
			    double cx,cy;
				double rx,ry;
	            double  s;
		        }RotRectangleData;
			struct  _CircleData{
				double cx,cy;
	            double r;
		        }CircleData;
			struct  _EllipseData{
				double cx,cy;
	            double rx,ry;
		        }EllipseData;
			struct  _RotEllipseData{
				double cx,cy;
	            double rx,ry;
		        double  s;
			    }RotEllipseData;
	        struct  _ArcData{
		        double cx,cy;
			    double r;
				double  s1,s2;
	            }ArcData;
		    struct  _FreeData{
			    NPListPack<ShapePoint3D>  *points;
				}FreeData;
	        struct  _PolyData{
		        NPListPack<ShapePoint3D>  *points;
			    }PolyData;
	        struct  _MoveData{
		        NPListPack<ShapePoint3D>  *points;
			    }MoveData;
	        struct  _ERingData{
		        double cx,cy;
			    double rx1,ry1;
				double rx2,ry2;
	            }ERingData;
		    struct  _SingleArrowLineData{
			    double x1,y1;
				double x2,y2;
	            }SingleArrowLineData;
		    struct  _DualArrowLineData{
			    double x1,y1;
				double x2,y2;
	            }DualArrowLineData;
		    struct  _LongCircleData{
			    double cx1,cy1;
			    double cx2,cy2;
	            double  r;
		        }LongCircleData;
	        struct  _RingArcData{
		        double cx,cy;
			    double rx1,ry1;
				double rx2,ry2;
				double  s1,s2;
	            }RingArcData;
		}UData;
		double	LineWidth;
		_ShapeData(void){   UData.FreeData.points=NULL;   UData.PolyData.points=NULL;   UData.MoveData.points=NULL;   LineWidth=0.0;	}
		~_ShapeData(void);

		bool    Save(QIODevice *file);
		bool    Load(QIODevice *file);
	};

private:
	DrawingMode FDrawMode;
	QColor		FColor;
	int			DrawStage;
    bool		FClosedArea;
    bool		FCancelDraw;
    bool		FOnDrawMode;
	bool		FEnableShiftImage;
    int			FArrowLength;
    int			rotx,roty;
    ColPoint3D	*PolyLastPoint;
	int			NowGx,NowGy;	//Current mouse point
	bool		ShiftingMode;
	bool		LeftClicked;
	bool		RightClicked;
	bool		DblClickMode;
	DWORD		ClickedTime;
	int			MousePressX,MousePressY;
	int			LastMouseDownPointX;
	int			LastMouseDownPointY;
	int			LastShitX,LastShitY;
	bool		NoShiftCanvasMode;
	int			ImageShiftDelay;
	int			TmpPoint[4][2];
	bool		FModeCrossLine;
	QColor		FCrossLineColor;
	QMutex		PaintMutex;
	bool		FModeRepaintOnMouseMove;
	bool		CancelClicked;
	double		LineWidth;
	Canvas3D	CInfo;

public:
	struct  _ShapeData  SData;

//	Q_DECLARE_METATYPE(_ShapeData);

	void	SetCursor(mtFrameDraw3D::DrawingMode mode);
	const	Canvas3D	&GetCanvas3DInfo(void)	const	{	return CInfo;	}
	void	GetZoomRate(double &ZoomRateX ,double &ZoomRateY)	const;
	bool	GetMovxy(double &movx ,double &movy)				const;
	int32	GetCanvasWidth (void)	const	{	return CInfo.Data.CanvasWidth;	}
	int32	GetCanvasHeight(void)	const	{	return CInfo.Data.CanvasHeight;	}

	//double	GetZoomRate(void)	const	{	return ZoomRate;	}
	//int		GetMovX(void)		const	{	return movx;		}
	//int		GetMovY(void)		const	{	return movy;		}
	//
	//void	SetZoomRate(double z)	{	ZoomRate=z;				}
	//void	SetMovXY(int mx,int my)	{	movx=mx;	movy=my;	}
	//void	SetMovX(int mx)			{	movx=mx;				}
	//void	SetMovY(int my)			{	movy=my;				}

	void	SetCrossLineMode(bool mode ,const QColor &Col=Qt::yellow);

	void	LockPaintMutex(void)		{	PaintMutex.lock();		}
	void	UnlockPaintMutex(void)		{	PaintMutex.unlock();	}
	void	RepaintAll(void);
	void	SetCancelDraw(void)			{	FCancelDraw=true;		}
	void	SetCancelClicked(bool b)	{	CancelClicked=b;		}
	bool	GetCancelClicked(void)	const	{	return CancelClicked;	}

	void	SetFModeRepaintOnMouseMove(bool b)			{	FModeRepaintOnMouseMove=b;		}
	bool	GetFModeRepaintOnMouseMove(void)	const	{	return FModeRepaintOnMouseMove;	}

	void	SetLineWidth(double width)	{	LineWidth=width;	}
	double	GetLineWidth(void)	const	{	return LineWidth;	}

protected:
    virtual	void	paintEvent(QPaintEvent *event)				override;

	virtual void	mousePressEvent ( QMouseEvent *Ev )			override;
	virtual void	mouseDoubleClickEvent ( QMouseEvent * e )	override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )			override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )		override;
	virtual void	wheelEvent ( QWheelEvent * event )			override;
	virtual void	enterEvent ( QEnterEvent * event )				override;
	virtual void	leaveEvent ( QEvent * event )				override;
	virtual	void	keyPressEvent ( QKeyEvent * event )			override;

signals:
	void	SignalDrawEnd(void);
	void	SignalDrawing(mtFrameDraw3D::DrawingMode mode ,int stage);
	void	SignalCancelDraw(void);
	void	SignalDoubleClick(QMouseEvent * e);
	void	SignalOnPaint(QPainter &pnt);
	void	SignalEnter();
	void	SignalLeave();
	void	SignalKeyPress(int key ,QPoint RawPos ,bool &Accept);
	void	SignalWheel(QWheelEvent * e);
	void	SignalShiftCanvas(int UniversalDx,int UniversalDy);
	void	SignalDrawMessage(const QStringList &title ,const QStringList &msg);
	void	SignalJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SignalJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseRRelease(int UniversalDx,int UniversalDy);
private slots:
	virtual	void	SlotDrawEnd(void);
	virtual	void	SlotDrawing(mtFrameDraw3D::DrawingMode mode,int stage);
	virtual	void	SlotCancelDraw(void);
	virtual	void	SlotOnPaint(QPainter &pnt);

private:
	void	SetClosedArea(bool Value);
	bool	IsPixelEffective(int x ,int y);
	bool    Drawing(void);
	void	PutPixelOnly(int x ,int y ,QColor &col);
	void	PutCrossLine(QPainter &Pnt ,int x,int y);
	void	Clear(QPainter &Pnt);
	void	GetEffectiveArea(int &minx,int &miny,int &maxx ,int &maxy);

	void	ChangeMode(DrawingMode newmode);
	void	ChangeCursor(DrawingMode newmode ,int CurrentDrawStage);

	void	SetStartCursor(void);
	void	Loaded(void);

	void	DrawRotEllipse(QPainter &Pnt);
	void	DrawRing(QPainter &Pnt);
	void	DrawLineZoom(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRateX,double ZoomRateY);
	void	DrawLineZoomInner(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRateX,double ZoomRateY);
	void	DrawLongCircle(QPainter &Pnt);
	void	DrawRingArc(QPainter &Pnt);

};

