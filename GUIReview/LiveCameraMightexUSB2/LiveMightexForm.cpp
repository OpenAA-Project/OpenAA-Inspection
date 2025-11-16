#include "LiveCameraMightexUSB2Resource.h"
#include "LiveMightexForm.h"
#include "ui_LiveMightexForm.h"
#include "XGeneralFunc.h"
#include <memory.h>
#include "CameraSettingForm.h"
#include "../XGUIReviewCommonPacket.h"
#include "../LiveCameraCommonPacket.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "XVRSControlCommand.h"
#include "XMightexControl.h"
#include <QFileDialog>
#include "XReviewCameraCommon.h"
#include "XCriticalFunc.h"
#include "XSequenceRepairLocal.h"

extern	MightexCameraContainer	*CameraList;

VRSSetting::VRSSetting(void){}
VRSSetting::InspectionSideSetting::InspectionSideSetting(void)
{}
VRSSetting::VRSSideSetting::VRSSideSetting(void)
{}

CamPanel::CamPanel(QWidget *parent)
	:mtFrameDraw(parent)
{
	LiveParent=(LiveMightexForm *)parent;
}
void	CamPanel::SlotOnPaint(QPainter &pnt)
{
	LiveParent->SlotOnPaint(pnt);
	QColor	Col(180,0,0,120);
	pnt.setPen(Col);
	pnt.drawLine(0,height()/2,width(),height()/2);
	pnt.drawLine(width()/2,0,width()/2,height());
}

void	CamPanel::mousePressEvent ( QMouseEvent *Ev )
{
	mtFrameDraw::mousePressEvent(Ev);

	ReviewPIBase *RBase=dynamic_cast<ReviewPIBase*>(LiveParent->GetLayersBase()->GetAlgorithmBase(/**/"Review",/**/"ReviewStructure"));
	CmdReqVRSSetting reqVRSSetting(LiveParent->GetLayersBase());
	RBase->TransmitDirectly( &reqVRSSetting );


	int	W=width();
	int	H=height();
	double	Xr=W/2-(double)Ev->x();
	double	Yr=H/2-(double)Ev->y();

	int	XPulse= Xr*LiveParent->PulsePer100Pixels*LiveParent->MainCameraZoomRate/100;
	int	YPulse=-Yr*LiveParent->PulsePer100Pixels*LiveParent->MainCameraZoomRate/100;

	GUIFormBase	*MGProp=LiveParent->GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(MGProp!=NULL){
		CmdVRSMoveXY	CmdMove(LiveParent->GetLayersBase());
		CmdMove.Dx	=XPulse;
		CmdMove.Dy	=YPulse;
		MGProp->TransmitDirectly(&CmdMove);
	}

	/*
	CmdReqVRSMotorState reqMotor(LiveParent->GetLayersBase());
	RBase->TransmitDirectly( &reqMotor );
	if(reqMotor.ret==false || reqMotor.x_enable==false)
		return;

	CmdSetVRSMotorState setMotor(LiveParent->GetLayersBase());
	setMotor.setX(reqMotor.x+XPulse);
	setMotor.setY(reqMotor.y+YPulse);
	RBase->TransmitDirectly( &setMotor );
	*/
}

void cameraFaultCallBack(int ImageType)
{
	BUFUSB_StopCameraEngine();
	BUFUSB_UnInitDevice();
}

DWORD	LastCapturedTime;
DWORD	CurentCapturedTime;
void cameraFrameDataCallBack( TProcessedDataProperty* Attributes, unsigned char *BytePtr )
{
	//static int count = 0;
	CameraItem &item = CameraList->fromDeviceID(Attributes->CameraID);

	// ・ｽB・ｽ・ｽ・ｽv・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽﾈゑｿｽ・ｽ・ｽ・ｽﾎ会ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾉ終・ｽ・?
	if(item.grabberState()!=stL_Grabber){
		return;
	}
	DWORD	t=::GetComputerMiliSec();
	CurentCapturedTime=t-LastCapturedTime;
	LastCapturedTime=t;

	// ・ｽ・ｽ・ｽﾝプ・ｽ・ｽ・ｽp・ｽe・ｽB・ｽ・ｽ・ｽi・?
	item.setProcessedDataProperty(*Attributes);

	// ・ｽ鞫懶ｿｽo・ｽb・ｽt・?・ｽ・ｽ・ｽR・ｽs・?
	memcpy(item.frameMem(), BytePtr, qMin(item.frameSize(), Attributes->Column*Attributes->Row*3));
	item.MakeImage();
	//item.Img->save("c:/data/test.bmp","BMP");
	item.CommandDraw();
}

bool	Ret;

LiveMightexForm::LiveMightexForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::LiveMightexForm),ViewerPanel(this),previewLabel(NULL)
{
    ui->setupUi(this);

	CameraList=new MightexCameraContainer(this);
	ReverseX=true;
	ReverseY=true;
	ShowSettingButton	=true;
	ShowLiveButton		=true;
	PulsePer100Pixels	=160;
	MainCameraZoomRate	=1.0;
	iLiveMode			=NULL;
	SysRegLiveMode		=-1;

	GetParamGUI()->SetParam(&PulsePer100Pixels, /**/"LiveMightex",/**/"PulsePer100Pixels"
							,LangSolver.GetString(LiveMightexForm_LS,LID_0)/*"Motor pulse per 100 pixels in standard zoom rete"*/		);

	GetParamGUI()->SetParam(&MainCameraZoomRate, /**/"LiveMightex",/**/"MainCameraZoomRate"
							,LangSolver.GetString(LiveMightexForm_LS,LID_1)/*"ZoomRate From Pixel to real length(mm)"*/		);

	ViewerPanel.setParent(ui->frame);
	ViewerPanel.move(0,0);
	ViewerPanel.resize(ui->frame->width(),ui->frame->height());
	ViewerPanel.SetMode(mtFrameDraw::fdNone);
	ViewerPanel.SetFrameColor(Qt::red);

	connect(this, SIGNAL(SignalResize()), SLOT(ResizeAction()));
}

LiveMightexForm::~LiveMightexForm()
{
	BUFUSB_StopCameraEngine();
	BUFUSB_UnInitDevice();

    delete ui;
}

void	LiveMightexForm::Prepare(void)
{
	int	ret;

	if(GetEditMode()==true)
		return;

	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(SysRegLiveMode>0){
					iLiveMode		=new SignalOperandBit(this,SysRegLiveMode,/**/"LiveMightex:iLiveMode");
					Param->SetSpecialOperand(iLiveMode);
					iLiveMode->Set(true);
				}
			}
		}
	}

	int	TotalDevices = BUFUSB_InitDevice();

	if(TotalDevices>0){
		if(ShowSettingButton==false)
			ui->pushButtonSetting->setVisible(false);
		if(ShowLiveButton==false)
			ui->toolButtonLive	->setVisible(false);

		if(ShowSettingButton==false && ShowLiveButton==false){
			ui->frame->move(0,0);
		}
	}

	CameraItem	*a;
	// ・ｽg・ｽp・ｽ・ｽ・ｽ・ｽ・ｽf・ｽo・ｽC・ｽX・ｽ・ｽ・ｽﾇ会ｿｽ
	if(TotalDevices>0){
		ret=BUFUSB_AddDeviceToWorkingSet(1);
		if(ret<0){
			return;
		}
		a=new CameraItem(this);
		CameraList->AppendList(a);
		connect(a,SIGNAL(SignalDraw()),this,SLOT(SlotDraw()),Qt::QueuedConnection);
	}

	// ・ｽe・ｽf・ｽo・ｽC・ｽX・ｽﾌ・ｿｽ・ｽW・ｽ・ｽ・?・ｽ・ｽ・ｽ・ｽ・ｽﾆシ・ｽ・ｽ・ｽA・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ謫ｾ
	for(int i=0; i<TotalDevices; i++){
		char moduleNo[32];	// least 16byte
		char serialNo[32];	// least 16byte
		int	ret = BUFUSB_GetModuleNoSerialNo(i+1, moduleNo, serialNo);
		if(ret<0){
			return;
		}
		CameraList->fromDeviceID(i+1).setModuleNoSerialNo(moduleNo, serialNo);
	}

	// ・ｽG・ｽ・ｽ・?・ｽR・?・ｽ・ｽ・ｽo・ｽb・ｽN・ｽﾆフ・ｽ・ｽ・?・ｽ・ｽ・ｽ謫ｾ・ｽR・?・ｽ・ｽ・ｽo・ｽb・ｽN・ｽﾝ抵ｿｽ
	if(TotalDevices>0){
		ret = BUFUSB_InstallUSBDeviceHooker(cameraFaultCallBack);
		if(ret<0){
			return;
		}
		ret = BUFUSB_InstallFrameHooker(1, cameraFrameDataCallBack);
		if(ret<0){
			return;
		}
	}


	ret=BUFUSB_StartCameraEngine(0, 8);	// ・ｽG・ｽ・ｽ・?・ｽﾊ知・ｽe・ｽE・ｽB・ｽ・ｽ・ｽh・ｽE・ｽﾈゑｿｽ・ｽA8・ｽr・ｽb・ｽg・ｽf・?・?・ｽd・ｽl
	if(ret<0){
		return;
	}

	// ・ｽ?恣x・ｽ・ｽ・ｽﾏ更
	for(int i=0; i<TotalDevices; i++){
		CameraList->fromDeviceID(i+1).setResolution(8);
		ret = BUFUSB_SetCustomizedResolution(i+1, 1280, 960, 0, 1);//	2592,1944,0,1);	//1280, 960, 0, 1);	// 11:2592 x1944
		if(ret<0){
			return;
		}
		BUFUSB_SetXYStart( i+1, 656, 492); 
		ret = BUFUSB_SetCameraWorkMode(i+1, 0);		// trigger mode
		if(ret<0){
			return;
		}
		ret = BUFUSB_SetBWMode(0, (ReverseX==true)?1:0, (ReverseY==true)?1:0);

	}
	for(int i=0; i<TotalDevices; i++){
		CameraList->fromDeviceID(i+1).setEnable(true);
	}
	
	// ・ｽt・ｽ・ｽ・?・ｽ・ｽ・ｽx・ｽ・ｽ・ｽ・ｽ・ｽﾅ擾ｿｽ・ｽﾉゑｿｽ・ｽ・ｽ・ｽ謔､・ｽﾝ抵ｿｽ
	ret = BUFUSB_SetMinimumFrameDelay(1);
	if(ret<0){
		QMessageBox::warning(NULL
							, LangSolver.GetString(LiveMightexForm_LS,LID_2)/*"Initial Error"*/
							, /**/"BUFUSB_SetMinimumFrameDelay()");
		return;
	}

	// ・ｽB・ｽ・ｽ・ｽJ・ｽn
	for(int i=0; i<TotalDevices; i++){
		ret = BUFUSB_StartFrameGrab(GRAB_FRAME_FOREVER);	//grab frame forever
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(LiveMightexForm_LS,LID_3)/*"Initial Error"*/
								, /**/"BUFUSB_StartFrameGrab()");
			return;
		}
	}

	GSleep(2000);
	if(LoadCameraSetting()==true){
		int	deviceID=1;
		CameraItem &item = CameraList->fromDeviceID(deviceID);
		int ret;
		ret = BUFUSB_SetExposureTime(deviceID, item.exposureTime());
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(LiveMightexForm_LS,LID_4)/*"Error"*/
								, /**/"SSClassicUSB_SetExposureTime()");
		}
		BUFUSB_SetFrameTime(deviceID, 100);

		const int r = item.gainR();
		const int g = item.gainG();
		const int b = item.gainB();
		ret = BUFUSB_SetGains(deviceID, r, g, b);
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(LiveMightexForm_LS,LID_5)/*"Error"*/
								, /**/"SSClassicUSB_SetGains()");
		}
	}
	CameraList->startGrabber();
}

bool	LiveMightexForm::SaveCameraSetting(void)
{
	QString	FileName=/**/"/SettingMightexCamera.dat";
	QString	PathFileName=GetLayersBase()->GetUserPath()+FileName;
	QFile	File(PathFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(CameraList->Save(&File)==true){
			return true;
		}
	}
	return false;
}
bool	LiveMightexForm::LoadCameraSetting(void)
{
	QString	FileName=/**/"/SettingMightexCamera.dat";
	QString	PathFileName=GetLayersBase()->GetUserPath()+FileName;
	QFile	File(PathFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(CameraList->Load(&File)==true){
			return true;
		}
	}
	return false;
}


bool	LiveMightexForm::SaveContent(QIODevice *f)
{
	if(CameraList->Save(f)==false)
		return false;
	return true;
}

bool	LiveMightexForm::LoadContent(QIODevice *f)
{
	if(CameraList->Load(f)==false)
		return false;
	return true;
}

void LiveMightexForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		ViewerPanel.repaint();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	GUICmdSetCameraWindow *GUICmdSetCameraWindowVar = dynamic_cast<GUICmdSetCameraWindow *>(packet);
	if(GUICmdSetCameraWindowVar!=NULL){
		previewLabel = GUICmdSetCameraWindowVar->label;
		GUICmdSetCameraWindowVar->ret = true;
		return;
	}

	GUICmdResetCameraWindow *GUICmdResetCameraWindowVar = dynamic_cast<GUICmdResetCameraWindow *>(packet);
	if(GUICmdResetCameraWindowVar!=NULL){
		previewLabel = NULL;
		GUICmdResetCameraWindowVar->ret = true;
		return;
	}
	/*
	GUICmdReqCamSize	*GUICmdReqCamSizeVar=dynamic_cast<GUICmdReqCamSize *>(packet);
	if(GUICmdReqCamSizeVar!=NULL){
		GUICmdReqCamSizeVar->Width=camSdk.Width();
		GUICmdReqCamSizeVar->Height=camSdk.Height();
		return;
	}
	*/
	CmdReqImageFromReviewCamera	*CmdReqImageFromReviewCameraVar=dynamic_cast<CmdReqImageFromReviewCamera *>(packet);
	if(CmdReqImageFromReviewCameraVar!=NULL){
		CameraItem	*a=CameraList->GetItem(0);
		if(a!=NULL){
			CmdReqImageFromReviewCameraVar->Image=*a->Img;
			CmdReqImageFromReviewCameraVar->ImageWidth	=CmdReqImageFromReviewCameraVar->Image.width();
			CmdReqImageFromReviewCameraVar->ImageHeight	=CmdReqImageFromReviewCameraVar->Image.height();
			CmdReqImageFromReviewCameraVar->Result		=true;
			return;
		}
		CmdReqImageFromReviewCameraVar->Result		=false;
		return;
	}
}
void LiveMightexForm::ResizeAction()
{
	ui->frame->resize(width(),height()-ui->frame->geometry().top());
	ViewerPanel.resize(ui->frame->width(),ui->frame->height());
}
void	LiveMightexForm::Terminated(void)
{
}
void LiveMightexForm::on_pushButtonSetting_clicked()
{
	int	deviceID=1;
	CameraItem &item = CameraList->fromDeviceID(deviceID);
	CameraSettingForm form(deviceID);

	form.setExposureTime(item.exposureTime());
	form.setGainR(item.gainR());
	form.setGainG(item.gainG());
	form.setGainB(item.gainB());
	form.setDeviceInfomation(item.moduleNo(), item.serialNo());
	form.setTriggerMode(item.isTriggerMode());
	form.setResolution(item.resolution());
	form.setGamma(item.gamma());

	if(form.exec()==QDialog::Accepted){
		item.setExposureTime( form.exposureTime() );
		quint8 gainR = form.gainR();
		quint8 gainG = form.gainG();
		quint8 gainB = form.gainB();
		item.setGainR( gainR );
		item.setGainG( gainG );
		item.setGainB( gainB );
		item.setTriggerMode( form.triggerMode() );
		item.setGamma(form.gamma());
		item.setResolution(form.resolution());

		int ret;
		ret = BUFUSB_SetExposureTime(deviceID, item.exposureTime());
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(LiveMightexForm_LS,LID_6)/*"Error"*/
								, /**/"BUFUSB_SetExposureTime()");
		}

		const int r = gainR;
		const int g = gainG;
		const int b = gainB;
		ret = BUFUSB_SetGains(deviceID, r, g, b);
		if(ret<0){
			QMessageBox::warning(NULL
								, LangSolver.GetString(LiveMightexForm_LS,LID_7)/*"Error"*/
								, /**/"BUFUSB_SetGains()");
		}

		SaveCameraSetting();
	}
}

void LiveMightexForm::on_toolButtonLive_clicked()
{

}

void	LiveMightexForm::SlotOnPaint(QPainter &pnt)
{
	CameraItem	*a=CameraList->GetItem(0);
	if(a!=NULL){
		if(ui->toolButtonLive->isChecked()==true){
			//a->MakeImage();
			if(iLiveMode==NULL || iLiveMode->Get()==true){
				pnt.setCompositionMode(QPainter::CompositionMode_Source);
				Pict=a->Img->scaled(ViewerPanel.width(),ViewerPanel.height(),Qt::KeepAspectRatio);
			}
		}
		pnt.drawImage(0,0,Pict);

		if(previewLabel!=NULL){
			if(iLiveMode==NULL || iLiveMode->Get()==true){
				QPixmap	map=QPixmap::fromImage(a->Img->scaled(previewLabel->width(),previewLabel->height(),Qt::KeepAspectRatio));
				previewLabel->setPixmap(map);
			}
		}
	}
}

void	LiveMightexForm::SlotDraw()
{
	ViewerPanel.repaint();
}
void LiveMightexForm::on_pushButtonCapture_clicked()
{
	QString	s=QFileDialog::getSaveFileName ( 0
										, LangSolver.GetString(LiveMightexForm_LS,LID_8)/*"Save file"*/
										, QString(/**/"")
										, QString(/**/"PNG(*.png)"));
	if(s.isEmpty()==false){
		Pict.save(s,/**/"PNG");
	}
}
