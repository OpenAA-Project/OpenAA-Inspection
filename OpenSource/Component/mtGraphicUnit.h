/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtGraphicUnit.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MTGRAPHICUNIT_H
#define MTGRAPHICUNIT_H

#include <QWidget>
#include <QScrollBar>
#include <QAbstractButton>
#include "NList.h"
#include "mtMeter.h"
#include "mtFrameDraw.h"
#include "mtWidgetPosition.h"
#include <QWheelEvent>
#include <QElapsedTimer>

class	mtPushButtonWithBalloon;
class	mtGraphicUnit;
class	mtScrollBar;


class	mtQFrameDrawInGUnit :public mtFrameDraw
{
    Q_OBJECT
	mtGraphicUnit	*Parent;
public:
	int				AreaSizeX;
	int				AreaSizeY;

public:
    explicit	mtQFrameDrawInGUnit(mtGraphicUnit *mparent ,QWidget *parent = 0);

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
	virtual void	SlotDrawEnd(void)			override;
	virtual void	SlotDrawing(mtFrameDraw::DrawingMode mode,int stage)	override;
	virtual void	SlotCancelDraw(void)		override;
	virtual void	SlotOnPaint(QPainter &pnt)	override;
};

class	mtScrollBar	:public QScrollBar
{
    Q_OBJECT
	mtGraphicUnit	*Parent;
public:
	explicit	mtScrollBar(mtGraphicUnit *mparent , Qt::Orientation orientation,QWidget *parent = 0);
protected:
	virtual void sliderChange ( SliderChange change )	override;
	virtual void enterEvent ( QEnterEvent * event )			override;
	virtual void leaveEvent ( QEvent * event )			override;
signals:
	void	SignalEnter();
	void	SignalLeave();

};


class mtGraphicUnit : public mtWidgetPosition
{
    Q_OBJECT
	//Q_PROPERTY(mtFrameDraw::mtDirection  DrawMode READ GetDrawMode WRITE SetDrawMode)
	Q_ENUMS(mtFrameDraw::DrawingMode)
	Q_PROPERTY(mtFrameDraw::DrawingMode FrameMode READ GetMode WRITE SetMode)
	Q_PROPERTY(QColor FrameColor READ GetFrameColor WRITE SetFrameColor)

	friend	mtQFrameDrawInGUnit;
	friend	class	mtScrollBar;

	Qt::MouseButtons	StateMouseButtons;
	bool				FirstTime;
	int					ScrollerWidth;
	QElapsedTimer		PushedTimeer;
	int					LongPushMilisec;
	bool				UseLongPush;
private:
	mtMeter				*MeterTop;
	mtMeter				*MeterLeft;
	mtScrollBar			*VScroll;
	mtScrollBar			*HScroll;
	mtQFrameDrawInGUnit	*FrDraw;
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
    explicit	mtGraphicUnit(QWidget *parent = 0
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);
    ~mtGraphicUnit(void);
	
	mtQFrameDrawInGUnit	*GetCanvas(void)	const;
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
	mtScrollBar			*GetVScroll(void)	const	{	return(VScroll);	}
	mtScrollBar			*GetHScroll(void)	const	{	return(HScroll);	}
	void	SetSlider(void);
	void	SetMeter(void);

	void	SetMode(mtFrameDraw::DrawingMode mode)	{	GetCanvas()->SetMode(mode);		}
	mtFrameDraw::DrawingMode GetMode(void)	const	{	return(GetCanvas()->GetMode());	}
	void	SetCursor(mtFrameDraw::DrawingMode mode);
	void	SetFrameColor(const QColor &col){	GetCanvas()->SetFrameColor(col);	}
	QColor	GetFrameColor(void)	const		{	return(GetCanvas()->GetFrameColor());	}
	QPoint	GetCursorPos(void)				{	return 	GetCanvas()->GetCursorPos();	}
	bool	IsIncludeInCanvas(QPoint &P)const;
	void	SetMouseCursorPos(int XonG, int YonG);
	void	ExecuteMouseMove(int XonG, int YonG);
	Qt::MouseButtons	&GetStateMouseButtons()		{	return StateMouseButtons;		}
	QString	ToString(mtFrameDraw::DrawingMode mode)	{	return FrDraw->ToString(mode);	}

	void	DrawFromOutside(QStringList &data);
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
	void	LaunchSignalDrawing(mtFrameDraw::DrawingMode mode,int stage);
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
	void	SignalDrawing(mtFrameDraw::DrawingMode mode,int stage);
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
	void	SlotDrawing(mtFrameDraw::DrawingMode mode,int stage);
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

#endif
