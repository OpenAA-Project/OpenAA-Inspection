#include "mtGraphUnitSub.h"
#include "mtGraphicUnit.h"

mtQFrameDrawInGUnit::mtQFrameDrawInGUnit(mtGraphicUnit *mparent ,QWidget *parent)
:PARENTCLASS(parent)
{
	Parent	=mparent;
	SetZoomRate(1.0);
	SetMovXY(0,0);
	AreaSizeX=100;
	AreaSizeY=100;
}

void	mtQFrameDrawInGUnit::mousePressEvent ( QMouseEvent *Ev )
{	
	PARENTCLASS::mousePressEvent(Ev); 
	Parent->LaunchSignalMousePressEvent(Ev);
}

void	mtQFrameDrawInGUnit::SlotDrawEnd(void)
{
	Parent->LaunchSignalDrawEnd();
}
void	mtQFrameDrawInGUnit::SlotDrawing(DrawingMode mode,int stage)
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
void	mtGraphicUnit::LaunchSignalDrawing(DrawingMode mode,int stage)
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
	PARENTCLASS::mtMousePoint(Ev ,x ,y ,valid);
	Parent->LaunchSignalMousePoint(Ev ,x ,y ,valid);
}
void	mtQFrameDrawInGUnit::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	PARENTCLASS::mtMouseLDown(Ev ,x ,y);
	Parent->LaunchSignalMouseLDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	PARENTCLASS::mtMouseRDown(Ev ,x ,y);
	Parent->LaunchSignalMouseRDown(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseMove(QMouseEvent *Ev ,int x ,int y)
{
	PARENTCLASS::mtMouseMove(Ev ,x ,y);
	Parent->LaunchSignalMouseMove(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseLUp(QMouseEvent *Ev ,int x ,int y)
{
	PARENTCLASS::mtMouseLDown(Ev ,x ,y);
	emit	SignalMouseLUp(x/GetZoomRate()-GetMovX(),y/GetZoomRate()-GetMovY());
	Parent->LaunchSignalMouseLUp(Ev ,x ,y);
}
void	mtQFrameDrawInGUnit::mtMouseRUp(QMouseEvent *Ev ,int x ,int y)
{
	PARENTCLASS::mtMouseRDown(Ev ,x ,y);
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