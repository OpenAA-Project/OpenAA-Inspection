#include "ButtonSettingThresholdForm.h"
#include "XPanelShowResultImage.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XEachThresholdCommon.h"
#include <QGestureEvent>
#include <QGesture>
#include <QPinchGesture>

extern	const	char	*sRoot;
extern	const	char	*sName;

PanelShowResultImage::PanelShowResultImage(ButtonSettingThresholdForm *p,EachThresholdCommon *wnd)
	:ServiceForLayers(p->GetLayersBase())
	,Parent(p),ThCommon(wnd)
{
	DrawMode=false;

	OverlapNG	=true;
	SetMode(mtFrameDraw::fdNone);

	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(ThCommon->SlaveNo);
		if(m!=NULL){
			SetAreaSize(m->GetDotPerLine(ThCommon->RepresentativePhase,ThCommon->RepresentativePage),m->GetMaxLines(ThCommon->RepresentativePhase,ThCommon->RepresentativePage));
		}
	}
	SetScrollerWidth(32);
	ZoomDrawWhole();
	connect(this,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(this,SIGNAL(SignalMouseLDoubleClick(int,int)),this,SLOT(SlotMouseLDoubleClick(int,int)));
	connect(this,SIGNAL(SignalMouseLDown(int,int)),this,SLOT(SlotMouseLDown(int,int)));
	connect(this,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)));

	grabGesture ( Qt::PinchGesture);

	TM.setSingleShot(false);
	TM.setInterval(300);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}
void	PanelShowResultImage::SetGlobalPoint(int _GlobalX ,int _GlobalY)
{
	GlobalX=_GlobalX;
	GlobalY=_GlobalY;
}
void	PanelShowResultImage::SlotOnPaint(QPainter &pnt)
{
	if(ThCommon->DItem!=NULL){
	//	if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			ThCommon->DItem->GetThresholdW()->Save(&Buff);

			IntegrationReqTryInspection	RCmd(GetLayersBase(),sRoot,sName,ThCommon->SlaveNo);
			IntegrationAckTryInspection	ACmd(GetLayersBase(),sRoot,sName,ThCommon->SlaveNo);
			RCmd.Phase	=ThCommon->RepresentativePhase;
			RCmd.Page	=ThCommon->RepresentativePage;
			RCmd.ItemID	=ThCommon->RepresentativeItemID;
			RCmd.ItemThreshold	=Buff.buffer();
			RCmd.ZoomRate	=GetZoomRate();
			RCmd.movx		=GetMovx();
			RCmd.movy		=GetMovy();
			RCmd.ImageW		=GetCanvasWidth();
			RCmd.ImageH		=GetCanvasHeight();
			RCmd.OverlapNG	=OverlapNG;
			RCmd.DrawMode	=DrawMode	;
			RCmd.DrawGx		=DrawGx	;
			RCmd.DrawGy		=DrawGy	;
			RCmd.DrawColor	=DrawColor	;
			if(RCmd.Send(ThCommon->SlaveNo,0,ACmd)==true){
				pnt.drawImage(0,0,Parent->TargetImageWithNG);
			}
		}
	//}
}
void	PanelShowResultImage::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		if(GetZoomRate()<GetMaxZoomRate()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomIn(Gx ,Gy);
		}
	}
	else if(delta<0){
		if(GetZoomRate()>GetMinZoomRate()){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomOut(Gx ,Gy);
		}
	}
}

void	PanelShowResultImage::ShowMarkerPosition(void)
{
	double	TargetZoomRate=1.0;
	ZoomDraw(-GlobalX+width()/2/TargetZoomRate, -GlobalY+height()/2/TargetZoomRate, TargetZoomRate);
}

void	PanelShowResultImage::SlotMouseLDoubleClick(int gx,int gy)
{
	GlobalX	=gx;
	GlobalY	=gy;
	ThCommon->MouseLDoubleClick(gx,gy,ThCommon->GetThresholdLevelID());
	repaint();
}

void	PanelShowResultImage::SlotTimeOut()
{
	OverlapNG=!OverlapNG;
	repaint();
}
bool	PanelShowResultImage::event(QEvent *event)
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
				SetZoom(Pi.x(), Pi.y(), GetZoomRate()*ZR);
			}
		}
	}
    return mtGraphicUnit::event(event);
}
