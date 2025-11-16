#include "LiveCameraMightexUSB3Resource.h"
#include "ChildPanelForm.h"
#include "ui_ChildPanelForm.h"
#include "XMightexControl.h"
#include "XGeneralFunc.h"
#include <memory.h>
#include <QDesktopWidget>
#include "CameraSettingForm.h"
#include "XCriticalFunc.h"
#include "XAutofocusControl.h"
#include "XVRSControlCommand.h"
#include <QMessageBox>

extern	MightexCameraContainer	*CameraList;

ChildCamPanel::ChildCamPanel(QWidget *parent)
	:mtFrameDraw(parent)
{
	LiveParent=(ChildPanelForm *)parent;
}
void	ChildCamPanel::SlotOnPaint(QPainter &pnt)
{
	LiveParent->SlotOnPaint(pnt);
}

void ChildCamPanel::mousePressEvent ( QMouseEvent * e )
{
	int	XPos	=e->x();
	int	YPos	=e->y();
	QDesktopWidget *D=QApplication::desktop();
	QRect r=D->screenGeometry(0);
	int	Dx=XPos-r.width()/2;
	int	Dy=YPos-r.height()/2;

	CmdReqLensRange	RCmd(LiveParent->GetLayersBase());
	GUIFormBase	*GProp=LiveParent->GetLayersBase()->FindByName(/**/"Review" ,/**/"OLSCControllPanel" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&RCmd);
	}
	int	ZoomRate=RCmd.ZoomRate;
	if(ZoomRate<=0)
		ZoomRate=5;
	int	Mx=Dx*LiveParent->ParentForm->PulsePer100Pixels/ZoomRate/100;
	int	My=Dy*LiveParent->ParentForm->PulsePer100Pixels/ZoomRate/100;

	GUIFormBase	*MGProp=LiveParent->GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(MGProp!=NULL){
		CmdVRSMoveXY	CmdMove(LiveParent->GetLayersBase());
		CmdMove.Dx	=-Mx;
		CmdMove.Dy	= My;
		MGProp->TransmitDirectly(&CmdMove);
	}
}


ChildPanelForm::ChildPanelForm(LayersBase *base ,LiveMightexForm *p,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::ChildPanelForm),ViewerPanel(this)
{
    ui->setupUi(this);
	ParentForm	=(LiveMightexForm *)p;

	ViewerPanel.setParent(ui->frame);
	ViewerPanel.move(0,0);
	ViewerPanel.resize(ui->frame->width(),ui->frame->height());
	ViewerPanel.SetMode(mtFrameDraw::fdNone);
	ViewerPanel.SetFrameColor(Qt::red);

	QDesktopWidget *D=QApplication::desktop();
	QRect r=D->screenGeometry(0);
	setGeometry(r);
}

ChildPanelForm::~ChildPanelForm()
{
    delete ui;
}

void ChildPanelForm::on_pushButtonSetting_clicked()
{
	int	deviceID=2;
	CameraItem &item = CameraList->fromDeviceID(deviceID);
	CameraSettingForm form(deviceID);

	form.setExposureTime(item.exposureTime());
	form.setGainR(item.gainR());
	form.setGainG(item.gainG());
	form.setGainB(item.gainB());
	form.setDeviceInfomation(item.moduleNo(), item.serialNo());
	form.setTriggerMode(item.isTriggerMode());

	if(form.exec()==QDialog::Accepted){
		item.setExposureTime( form.exposureTime() );
		quint8 gainR = form.gainR();
		quint8 gainG = form.gainG();
		quint8 gainB = form.gainB();
		item.setGainR( gainR );
		item.setGainG( gainG );
		item.setGainB( gainB );
		item.setTriggerMode( form.triggerMode() );

		int ret;
		ret = SSClassicUSB_SetExposureTime(deviceID, item.exposureTime());
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(ChildPanelForm_LS,LID_1)/*"Error"*/
								, LangSolver.GetString(ChildPanelForm_LS,LID_2)/*"SSClassicUSB_SetExposureTime()"*/);
		}

		const int r = gainR;
		const int g = gainG;
		const int b = gainB;
		ret = SSClassicUSB_SetGains(deviceID, r, g, b);
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(ChildPanelForm_LS,LID_3)/*"Error"*/
								, LangSolver.GetString(ChildPanelForm_LS,LID_4)/*"SSClassicUSB_SetGains()"*/);
		}

		ParentForm->SaveCameraSetting();
	}
}

void ChildPanelForm::on_toolButtonLive_clicked()
{
}
void ChildPanelForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->resize(width(),height()-ui->frame->geometry().top());
	ViewerPanel.resize(ui->frame->width(),ui->frame->height());
}
void	ChildPanelForm::SlotOnPaint(QPainter &pnt)
{
	CameraItem	*a=CameraList->GetItem(1);
	if(a!=NULL){
		if(ui->toolButtonLive->isChecked()==true){
			pnt.setCompositionMode(QPainter::CompositionMode_Source);
			Pict=a->Img->scaled(ViewerPanel.width(),ViewerPanel.height());
		}
		pnt.drawImage(0,0,Pict);
	}
}
void ChildPanelForm::SlotDraw()
{
	ViewerPanel.repaint();
}
	
