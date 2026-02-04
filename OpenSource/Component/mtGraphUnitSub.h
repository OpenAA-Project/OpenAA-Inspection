#pragma once

#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "mtPushButtonWithBalloon.h"
//#include "mtFrameDraw.h"
#include "..\DisplayOpenGL\DisplayOpenGL.h""

class	mtGraphicUnit;

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
	virtual void	SlotDrawing(DrawingMode mode,int stage)	override;
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
