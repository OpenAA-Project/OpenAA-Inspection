/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MTFRAMEDRAW_H
#define MTFRAMEDRAW_H

//#include <QMetaType>
#include <QWidget>
#include <QMutex>
#include "NList.h"
#include <QIODevice>
#include "XTypeDef.h"
#include "mtFrameDataType.h"



//	Q_DECLARE_METATYPE(_ShapeData);

class	mtDrawCommand : public NPList<mtDrawCommand>
{
private:
	enum	DrawCommandAttr{
			 _DC_Dot
			,_DC_Line
			,_DC_ChopperLine
			,_DC_HalfLine
			,_DC_Arc
			,_DC_Ellipse
	};
	DrawCommandAttr	Attr;
	int		X1,Y1,X2,Y2;

public:
	explicit	mtDrawCommand(DrawCommandAttr attr){	Attr=attr;	}
	explicit	mtDrawCommand(DrawCommandAttr attr ,int x1,int y1 ,int x2 ,int y2);

	void	Draw(QPainter &Pnt);
};

class mtFrameDraw : public QWidget
{
    Q_OBJECT
	Q_ENUMS(DrawingMode)
	Q_PROPERTY(DrawingMode FrameMode READ GetMode WRITE SetMode)
	Q_PROPERTY(QColor FrameColor READ GetFrameColor WRITE SetFrameColor)

public:
    explicit	mtFrameDraw(QWidget *parent = 0);
    ~mtFrameDraw();

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

	void	(*DrawStartEvent)(QWidget *Sender, int &X ,int &Y);



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

//	Q_DECLARE_METATYPE(_ShapeData);

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
	void	Clear(QPainter &Pnt);
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

#endif