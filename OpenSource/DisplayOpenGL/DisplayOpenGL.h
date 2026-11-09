#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QPainter> // 追加
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QFont>
#include <QResizeEvent>
#include <QMutex>
#include <QScrollBar>
#include "XServiceForLayers.h"
#include "mtFrameDataType.h"
#include "mtWidgetPosition.h"
#include <QWheelEvent>
#include <QElapsedTimer>

#pragma pack(push,1)
struct GPUPixel
{
	BYTE	R,G,B,A;

	GPUPixel(BYTE r=0 ,BYTE g=0 ,BYTE b=0 ,BYTE a=255)
		:R(r),G(g),B(b),A(a)
	{
	}
};
#pragma pack(pop)


// OpenGL背景描画 + QPainterオーバーレイ描画のハイブリッドクラス
class mtFrameDrawOGL : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
	Q_ENUMS(DrawingMode)
	Q_PROPERTY(DrawingMode FrameMode READ GetMode WRITE SetMode)
	Q_PROPERTY(QColor FrameColor READ GetFrameColor WRITE SetFrameColor)

private:
    QTimer m_timer;
    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer m_vbo;
    GLuint m_texture;
    GLuint m_pbo;
    
    qreal m_devicePixelRatio;

    int m_width;
    int m_height;
    
    //QImage m_spriteImage; // 描画テスト用画像
public:

	void	SetMode(DrawingMode mode);
	DrawingMode GetMode(void)	const	{	return(FDrawMode);	}
	void	SetEnableShiftImage(bool b);
	bool	GetEnableShiftImage(void)	const;
	void	SetFrameColor(const QColor &col){	FColor=col;	}
	QColor	GetFrameColor(void)	const	{	return(FColor);	}
	void	GetCanvasToUniverse(int gx, int gy ,int &ux, int &uy)	const;

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

	void	SetImage(QImage *img);
	void	DelImage(void);
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

	void	(*DrawStartEvent)(mtFrameDrawOGL *Sender, int &X ,int &Y);

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
    ColPoint	*PolyLastPoint;
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
	QImage		*Image;
	bool		NoShiftCanvasMode;
	int			ImageShiftDelay;
	int			TmpPoint[4][2];
	bool		FModeCrossLine;
	QColor		FCrossLineColor;
	QMutex		PaintMutex;
	bool		FModeRepaintOnMouseMove;
	bool		CancelClicked;
	double		LineWidth;
	double		ZoomRate;
	double		movx,movy;		//Visual Matrix(Gx,Gy)
								//Data Matrix(x,y)
								//(Gx,Gy) = ( (x,y) + (movx,movy) )*ZoomRate
public:
	struct  _ShapeData  SData;

public:
    mtFrameDrawOGL(QWidget *parent);
    ~mtFrameDrawOGL();

	void	DrawFromOutside(QStringList &data);
	void	SetCursor(DrawingMode mode);
	double	GetZoomRate(void)	const	{	return ZoomRate;	}
	int		GetMovX(void)		const	{	return movx;		}
	int		GetMovY(void)		const	{	return movy;		}

	void	SetZoomRate(double z)	{	ZoomRate=z;				}
	void	SetMovXY(int mx,int my)	{	movx=mx;	movy=my;	}
	void	SetMovX(int mx)			{	movx=mx;				}
	void	SetMovY(int my)			{	movy=my;				}

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
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
	virtual	void	paintEvent(QPaintEvent *event)				override;
   
    virtual	void resizeEvent ( QResizeEvent * event )			override;

	virtual void	mousePressEvent ( QMouseEvent *Ev )			override;
	virtual void	mouseDoubleClickEvent ( QMouseEvent * e )	override;
	virtual void	mouseMoveEvent	( QMouseEvent * e )			override;
	virtual void	mouseReleaseEvent( QMouseEvent * e )		override;
	virtual void	wheelEvent		( QWheelEvent * event )		override;
	virtual	void	keyPressEvent	( QKeyEvent * event )		override;
	virtual	void	closeEvent(QCloseEvent *event)				override;
	void	InPaint(QPainter &pnt);

signals:
	void	SignalDrawBackground(GPUPixel* buffer ,int XLen ,int YLen);

	void	SignalDrawEnd(void);
	void	SignalDrawing(DrawingMode mode ,int stage);
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
	virtual	void	SlotDrawing(DrawingMode mode,int stage);
	virtual	void	SlotCancelDraw(void);
	virtual	void	SlotOnPaint(QPainter &pnt);
private:
	void	SetClosedArea(bool Value);
	bool	IsPixelEffective(int x ,int y);
	bool    Drawing(void);
	void	PutPixelOnly(int x ,int y ,QColor &col);
	void	PutCrossLine(QPainter &Pnt ,int x,int y);
	void	GetEffectiveArea(int &minx,int &miny,int &maxx ,int &maxy);

	void	ChangeMode(DrawingMode newmode);
	void	ChangeCursor(DrawingMode newmode ,int CurrentDrawStage);

	void	SetStartCursor(void);
	void	Loaded(void);

	void	DrawRotEllipse(QPainter &Pnt);
	void	DrawRing(QPainter &Pnt);
	void	DrawLineZoom(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRate);
	void	DrawLineZoomInner(QPainter &Pnt ,int x1, int y1 ,int x2, int y2 ,double ZoomRate);
	void	DrawLongCircle(QPainter &Pnt);
	void	DrawRingArc(QPainter &Pnt);

};

//======================================================================================
class mtGraphicUnitOG;
class mtPushButtonWithBalloon;
class mtMeter;


class	mtQFrameDrawInGUnitOG :public mtFrameDrawOGL
{
    Q_OBJECT
	friend	class	mtGraphicUnitOG;

	mtGraphicUnitOG	*Parent;
public:
	int				AreaSizeX;
	int				AreaSizeY;

public:
    explicit	mtQFrameDrawInGUnitOG(mtGraphicUnitOG *mparent ,QWidget *parent = 0);

protected:
	virtual	void	mousePressEvent ( QMouseEvent *Ev )			override;
	virtual	void	mtMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid)	override;
	virtual	void	mtMouseLDown(QMouseEvent *Ev ,int x ,int y)	override;
	virtual	void	mtMouseRDown(QMouseEvent *Ev ,int x ,int y)	override;
	virtual	void	mtMouseMove(QMouseEvent *Ev ,int x ,int y)	override;
	virtual	void	mtMouseLUp(QMouseEvent *Ev ,int x ,int y)	;
	virtual	void	mtMouseRUp(QMouseEvent *Ev ,int x ,int y)	;
	virtual	void	ShiftPressed(int gx ,int gy)				;
	virtual void	wheelEvent ( QWheelEvent * event )			override;

signals:
	void	SignalMouseMove(int ,int);
	void	SignalMouseLDown(int ,int);
	void	SignalMouseLUp(int ,int);
	void	SignalMouseRDown(int ,int);
	void	SignalMouseRUp(int ,int);
	void	SignalWheel(QWheelEvent * e);

private slots:
	virtual void	SlotDrawEnd(void)		;
	virtual void	SlotDrawing(DrawingMode mode,int stage);
	virtual void	SlotCancelDraw(void)	;
	virtual void	SlotOnPaint(QPainter &pnt);
};

class	mtScrollBarOG	:public QScrollBar
{
    Q_OBJECT
	friend	class	mtGraphicUnitOG;

	mtGraphicUnitOG	*Parent;
public:
	explicit	mtScrollBarOG(mtGraphicUnitOG *mparent , Qt::Orientation orientation,QWidget *parent = 0);
protected:
	virtual void sliderChange ( SliderChange change )	override;
	virtual void enterEvent ( QEnterEvent * event )			override;
	virtual void leaveEvent ( QEvent * event )			override;
signals:
	void	SignalEnter();
	void	SignalLeave();

};


class mtGraphicUnitOG : public mtWidgetPosition
{
    Q_OBJECT
	//Q_PROPERTY(mtDirection  DrawMode READ GetDrawMode WRITE SetDrawMode)
	Q_ENUMS(DrawingMode)
	Q_PROPERTY(DrawingMode FrameMode READ GetMode WRITE SetMode)
	Q_PROPERTY(QColor FrameColor READ GetFrameColor WRITE SetFrameColor)

	friend	mtQFrameDrawInGUnitOG;
	friend	class	mtScrollBarOG;

	Qt::MouseButtons	StateMouseButtons;
	bool				FirstTime;
	int					ScrollerWidth;
	QElapsedTimer		PushedTimeer;
	int					LongPushMilisec;
	bool				UseLongPush;
private:
	mtMeter				*MeterTop;
	mtMeter				*MeterLeft;
	mtScrollBarOG		*VScroll;
	mtScrollBarOG		*HScroll;
	mtQFrameDrawInGUnitOG	*FrDraw;
	double				FZoomRateMin;
	double				FZoomRateMax;
	double				FVerticalMerginRate		;
	double				FHorizontalMerginRate	;
	//QAbstractButton		*ButtonZoomIn;
	//QAbstractButton		*ButtonRect;
	//QAbstractButton		*ButtonWhole;
	int					InsideFunc;
	mtPushButtonWithBalloon	*FitZoomBtn;
	mtPushButtonWithBalloon	*UpPageBtn;
	mtPushButtonWithBalloon	*DownPageBtn;
	mtPushButtonWithBalloon	*LeftPageBtn;
	mtPushButtonWithBalloon	*RightPageBtn;
	struct{
		bool	EnableMeasure	:1;
		bool	EnableToolArea	:1;
		bool	EnableVScroller	:1;
		bool	EnableHScroller	:1;
		bool	EnableZoom		:1;
		bool	EnableMove		:1;
		bool	EnableFitZoom	:1;
	};
public:
    explicit	mtGraphicUnitOG(QWidget *parent = 0
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);
    ~mtGraphicUnitOG(void);
	
	mtQFrameDrawInGUnitOG	*GetCanvas(void)	const;

	void	SetZoomMinMax(double MinZ ,double MaxZ)	{	FZoomRateMin=MinZ;	FZoomRateMax=MaxZ;	}
	double	GetMaxZoomRate(void)	const	{	return FZoomRateMax;	}
	double	GetMinZoomRate(void)	const	{	return FZoomRateMin;	}
	void	SetMaxZoomRate(double d)		{	FZoomRateMax=d;			}
	void	SetMinZoomRate(double d)		{	FZoomRateMin=d;			}
	void	ZoomDraw(int movx, int movy, double zoomrate);
	bool	ZoomIn(int XonG, int YonG);
	bool	ZoomOut(int XonG, int YonG);
	bool	SetZoom(int XonG, int YonG , double ZoomRate);
	bool    ZoomRectG(int Gx1 ,int Gy1 ,int Gx2 ,int Gy2);
	bool    ZoomRectU(int Ux1 ,int Uy1 ,int Ux2 ,int Uy2);
	void	DrawAdd(int UOffx, int UOffy);
	void	SetDrawOffset(int UMovx ,int UMovy);
	void	SetMeterOffset(int OffsetX ,int OffsetY);
	void	GetMeterOffset(int &OffsetX ,int &OffsetY);
	void	ZoomDrawWhole(void);
	void	ZoomDrawFit(void);
	void	SetEnableShiftImage(bool b);
	bool	GetEnableShiftImage(void)	const;
	void	SetScrollerWidth(int w);
	void	Clear(void);
	void	SetCancelDraw(void);
	void	Repaint(void);
	void	SetMerginRate(double Hr,double Vr);
	bool	GetUseLongPush(void)		const	{	return UseLongPush;		}
	void	SetUseLongPush(bool b)				{	UseLongPush	=b;			}
	int		GetLongPushMilisec(void)	const	{	return LongPushMilisec;	}
	void	SetLongPushMilisec(int n)			{	LongPushMilisec=n;		}

	double	GetZoomRate(void)	const	{ return(FrDraw->GetZoomRate());	}
	void	SetZoomRate(double ZoomRate){	FrDraw->SetZoomRate(ZoomRate);	}
	int		GetMovx(void)		const	{ return(FrDraw->GetMovX());	}
	int		GetMovy(void)		const	{ return(FrDraw->GetMovY());	}
	void	SetMovXY(int mx ,int my)	{	FrDraw->SetMovXY(mx,my);	}
	int		GetCanvasWidth(void) const	{ return(FrDraw->width()); }
	int		GetCanvasHeight(void) const { return(FrDraw->height()); }
	QSize	GetCanvasSize()		const	{ return FrDraw->size(); };
	void	SetAreaSize(int xlen ,int ylen);
	double	GetZoomRateForWhole(void)	const;
	double	GetZoomRateForFit(void)		const;
	void	SetLineWidth(double width)	{	FrDraw->SetLineWidth(width);	}
	double	GetLineWidth(void)	const	{	return FrDraw->GetLineWidth();	}

	//QAbstractButton		*GetButtonZoomIn(void){	return(ButtonZoomIn);	}
	//QAbstractButton		*GetButtonRect(void){	return(ButtonRect);		}
	//QAbstractButton		*GetButtonWhole(void){	return(ButtonWhole);	}
	mtScrollBarOG			*GetVScroll(void)	const	{	return(VScroll);	}
	mtScrollBarOG			*GetHScroll(void)	const	{	return(HScroll);	}
	void	SetSlider(void);
	void	SetMeter(void);

	void	SetMode(DrawingMode mode)	{	GetCanvas()->SetMode(mode);		}
	DrawingMode GetMode(void)	const	{	return(GetCanvas()->GetMode());	}
	void	SetCursor(DrawingMode mode);
	void	SetFrameColor(const QColor &col){	GetCanvas()->SetFrameColor(col);	}
	QColor	GetFrameColor(void)	const		{	return(GetCanvas()->GetFrameColor());	}
	QPoint	GetCursorPos(void)				{	return 	GetCanvas()->GetCursorPos();	}
	bool	IsIncludeInCanvas(QPoint &P)const;
	void	SetMouseCursorPos(int XonG, int YonG);
	void	ExecuteMouseMove(int XonG, int YonG);
	Qt::MouseButtons	&GetStateMouseButtons()		{	return StateMouseButtons;		}
	QString	ToString(DrawingMode mode)	{	return FrDraw->ToString(mode);	}

	void	SetCrossLineMode(bool mode ,const QColor &Col=Qt::yellow);

	void	SetFModeRepaintOnMouseMove(bool b)	;
	bool	GetFModeRepaintOnMouseMove(void)	;

	void	LockPaintMutex(void)	{	FrDraw->LockPaintMutex();		}
	void	UnlockPaintMutex(void)	{	FrDraw->UnlockPaintMutex();		}
	void	SetCancelClicked(bool b){	FrDraw->SetCancelClicked(b);	}
	bool	GetCancelClicked(void)	const	{	return FrDraw->GetCancelClicked();	}
private:
	bool	IsInnerFuncMode(void){	return((InsideFunc!=0)?true:false);	}

	void	LaunchSignalDrawEnd(void);
	void	LaunchSignalDrawing(DrawingMode mode,int stage);
	void	LaunchSignalCancelDraw(void);
	void	LaunchSignalOnPaint(QPainter &pnt);
	void	LaunchSignalScrollDraw(void);

	void	LaunchSignalMousePoint(QMouseEvent *Ev ,int x ,int y ,bool &valid);
	void	LaunchSignalMouseLDown(QMouseEvent *Ev ,int x ,int y);
	void	LaunchSignalMouseRDown(QMouseEvent *Ev ,int x ,int y);
	void	LaunchSignalMouseMove(QMouseEvent *Ev ,int x ,int y);
	void	LaunchSignalMouseLUp(QMouseEvent *Ev ,int x ,int y);
	void	LaunchSignalMouseRUp(QMouseEvent *Ev ,int x ,int y);
	void	LaunchSignalShiftPressed(int gx ,int gy);
	void	LaunchSignalMousePressEvent(QMouseEvent *Ev);
	void	ZoomDrawFree(int movx, int movy, double zoomrate);

protected:
	virtual void enterEvent ( QEnterEvent * event )			override;
	virtual void leaveEvent ( QEvent * event )			override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;

signals:
	void	SignalDrawEnd(void);
	void	SignalDrawing(DrawingMode mode,int stage);
	void	SignalScrollDraw();
	void	SignalCancelDraw();
	void	SignalOnPaint(QPainter &pnt);
	void	SignalMouseMove(int ,int);
	void	SignalMouseLDown(int ,int);
	void	SignalMouseLDoubleClick(int ,int);
	void	SignalMouseRDoubleClick(int ,int);
	void	SignalMouseLDownWithShift(int ,int);
	void	SignalMouseLUp(int ,int);
	void	SignalMouseRDown(int ,int);
	void	SignalMouseRDownWithShift(int ,int);
	void	SignalMouseRUp(int ,int);
	void	SignalShiftPressed(int,int);
	void	SignalMousePressEvent(QMouseEvent *Ev);
	void	SignalEnter();
	void	SignalLeave();
	void	SignalKeyPress(int key ,int XonG, int YonG ,bool &Accept);
	void	SignalMouseWheel(int delta ,int x,int y);
	void	SignalShiftAll(void);
	void	SignalDrawMessage(const QStringList &title ,const QStringList &msg);
	void	SignalJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SignalJustMouseRRelease(int UniversalDx,int UniversalDy);
	void	SignalFitZoom();
	void	SignalJustMouseLLongPress  (int UniversalDx,int UniversalDy);
	void	SignalJustMouseRLongPress  (int UniversalDx,int UniversalDy);
protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:
	void	SlotDrawEnd(void);
	void	SlotDrawing(DrawingMode mode,int stage);
	void	SlotCancelDraw(void);
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseMove(int ,int);
	void	SlotMouseLDown(int ,int);
	void	SlotMouseLUp(int ,int);
	void	SlotMouseRDown(int ,int);
	void	SlotMouseRUp(int ,int);
	void	SlotEnter();
	void	SlotLeave();
	void	SlotKeyPress(int key ,QPoint RawPos ,bool &Accept);
	void	SlotDoubleClick(QMouseEvent *Ev);
	void	SlotWheel(QWheelEvent * e);
	void	SlotShiftCanvas(int UniversalDx,int UniversalDy);
	void	SlotDrawMessage(const QStringList &title ,const QStringList &msg);
private slots:
	void	SlotJustMouseLPress  (int UniversalDx,int UniversalDy);
	void	SlotJustMouseRPress  (int UniversalDx,int UniversalDy);
	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy);
	void	SlotJustMouseRRelease(int UniversalDx,int UniversalDy);

public slots:
	void	SlotUpPageButtonDown();
	void	SlotDownPageButtonDown();
	void	SlotLeftPageButtonDown();
	void	SlotRightPageButtonDown();
	void	SlotFitZoomBtnDown();
};
