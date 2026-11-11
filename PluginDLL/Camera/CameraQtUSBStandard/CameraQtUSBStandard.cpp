/*
 * Copyright (C) 2025
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

#include "CameraQtUSBStandard.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "SettingCameraDialog.h"
#include "XHidCommand.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XLogOut.h"
#include <QMediaDevices>

#define		CameraNameID	"USB Camera"

//---------------------------------------------------------------

DEFFUNCEX	WORD	DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}
DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="Standard USB camera for windows with Qt";
	return(true);
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}


DEFFUNCEX	int		_cdecl	DLL_GetCameraCount(LayersBase *base,const QString &CameraParameter)
{
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	return availableDevices.count();
}

DEFFUNCEX	CameraHandle*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//				CamInfo : Set unique several attributes in this function
{
	bool	ok;
	int	CamNo=CameraParameter.toInt(&ok);
	if(ok==false){
		CamNo=0;
	}
	USBQtCamera	*Handle=new USBQtCamera(base,CamNo);

	return Handle;
}

DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		delete	Handle;
	}
	return true;
}
DEFFUNCEX	bool	_cdecl	DLL_ResetToDefault(CameraHandle *handle)
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		//Handle->RestoreDefault();
		return true;
	}
	return false;
}
DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		if(Handle->ChangeInfo(caminfo)==true){
			return true;
		}
	}
	return false;
}
DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		if(Handle->Load(&str)==false){
			Handle->GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"CameraQtUSBStandard:DLL_ChangeInfo DLL_Load=false");
			return false;
		}
		Handle->ReflectToCamera();
		Handle->GetLayersBase()->ReallocXYPixels(Handle->CurrentResolution.width()
												,Handle->CurrentResolution.height());
		return true;
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		if(Handle->Save(&str)==false){
			Handle->GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"CameraUQtSBStandard:DLL_ChangeInfo DLL_Save=false");
			return false;
		}
		return true;
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		SettingCameraDialog	D(Handle->GetLayersBase(),Handle,parent);
		if(D.exec()==(int)true){

			Handle->CurrentResolution			=D.CurrentResolution			;
			Handle->CurrentExposureMode			=D.CurrentExposureMode			;
			Handle->CurrentFlashMode			=D.CurrentFlashMode				;
			Handle->CurrentExposureCompensation	=D.CurrentExposureCompensation	;
			Handle->CurrentISO					=D.CurrentISO					; 
			Handle->CurrentFocusMode			=D.CurrentFocusMode				;
			Handle->CurrentFocusDistance		=D.CurrentFocusDistance			;
			Handle->CurrentCustomFocusPoint		=D.CurrentCustomFocusPoint		;
			Handle->CurrentWhiteBalanceMode		=D.CurrentWhiteBalanceMode		;
			Handle->CurrentColorTemperature		=D.CurrentColorTemperature		;
			Handle->CurrentTorchMode			=D.CurrentTorchMode				;


			Handle->ReflectToCamera();
			Handle->GetLayersBase()->ReallocXYPixels(Handle->CurrentResolution.width()
													,Handle->CurrentResolution.height());
			return true;
		}
	}
	return false;
}
	

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	Start capruting till then end of Y lines. 
//	This function must return soon
//	if process fails, it returns false
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		Handle->StartCapture();
	}
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCaptureContinuously(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Start capruting till DLL_StopCaptureContinuously. 
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StopCaptureContinuously(CameraHandle *handle)
//	stop to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
//					Bit5		1:Start DMA transfer
//								Set bit soon after DMA starts in frame capturing
//								Set bit soon after one DMA frame starts in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit6		1:Finish DMA transfer
//								Set bit soon after DMA finishes in frame capturing
//								Set bit soon after 1 DMA frame finishes in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit7		0:Buffer empty( enable to capture)	1:Buffer full
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		if(Handle->IsCaptured()==true){
			return 0;
		}
	}
	return 1;
}

DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	bool	Ret=true;
	USBQtCamera	*Handle=(USBQtCamera *)handle;
	if(Handle!=NULL){
		Handle->GetImage(Buff,BufferDimCounts ,Info);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}
DEFFUNCEX	bool		_cdecl	DLL_ClearBit(CameraHandle *handle)
//	Clear status bit
//	This function must return soon
//	if process fails, it returns false
//	This function is used to reset Bit5 of GetStatus from application
{
	return true;
}

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
{
	USBQtCamera	*Handle=(USBQtCamera *)handle;

	if(Handle!=NULL){
	}
}

//========================================================================

USBQtCamera::USBQtCamera(LayersBase *base,int _CamNo)
	:CameraHandle(_CamNo ,base)
{
	CamNo=_CamNo;
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(CamNo);
	Camera = new QCamera(CamDevice);

	ImageCapture = new QImageCapture(this);
	session.setCamera(Camera);
	session.setImageCapture(ImageCapture);

	auto formats = CamDevice.videoFormats();
	if (!formats.isEmpty()) {
	    QCameraFormat bestFormat = formats.first();
	    QSize bestRes = bestFormat.resolution();
	    long long maxPixels = (long long)bestRes.width() * bestRes.height();
	
	    for (const auto &fmt : formats) {
	        QSize res = fmt.resolution();
	        long long currentPixels = (long long)res.width() * res.height();
	
	        if (currentPixels > maxPixels) {
	            maxPixels = currentPixels;
	            bestFormat = fmt;
	        }
	    }
	
	    Camera->setCameraFormat(bestFormat);
	    CurrentResolution = bestFormat.resolution();
	}
	connect(ImageCapture, &QImageCapture::imageCaptured,
			this, &USBQtCamera::onImageCaptured);
	connect(ImageCapture, &QImageCapture::errorOccurred,
            this, &USBQtCamera::handleErrorOccurred);

	DataBuff=NULL;
	Captured=false;

	connect(Camera, &QCamera::activeChanged, this, [this](bool active) {
	    if (active) {
	        // カメラが完全に起動したタイミングで取得する
	        QCameraFormat currentFormat = Camera->cameraFormat();
	        CurrentResolution = currentFormat.resolution();
	        qDebug() << "Actual Resolution:" << CurrentResolution;
	    }
	});

	Camera->start();

    QCameraFormat currentFormat = Camera->cameraFormat();
    CurrentResolution = currentFormat.resolution();


	CurrentExposureMode		=Camera->exposureMode();
	CurrentFlashMode		=Camera->flashMode();
	CurrentExposureCompensation = Camera->exposureCompensation();
	CurrentISO				=Camera->isoSensitivity();
	CurrentFocusMode		=Camera->focusMode();
	CurrentFocusDistance	=Camera->focusDistance();
	CurrentCustomFocusPoint =Camera->customFocusPoint();
	
	CurrentWhiteBalanceMode	=Camera->whiteBalanceMode();
	CurrentColorTemperature	=Camera->colorTemperature();
	CurrentTorchMode		=Camera->torchMode();
}

USBQtCamera::~USBQtCamera(void)
{
	delete	Camera;
	Camera=NULL;
	if(DataBuff!=NULL){
		delete	[]DataBuff;
		DataBuff=NULL;
	}
}

bool	USBQtCamera::ChangeInfo(CameraReqInfo &caminfo)
{
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(CamNo);
	bool	found=false;
	for (const QCameraFormat &format : CamDevice.videoFormats()) {
		if(format.resolution().width() == caminfo.XLen
		&& format.resolution().height() == caminfo.YLen) {
			Camera->setCameraFormat(format);
			found=true;
			break;
		}
	}

	if(DataBuff!=NULL){
		delete	[]DataBuff;
		DataBuff=NULL;
	}
	DataBuff = new BYTE[caminfo.XLen*caminfo.YLen * 3]; // RGB

	return found;
}

bool	USBQtCamera::GetImage(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
	if(Captured==false || DataBuff==NULL){
		return false;
	}
	int32	XLen=CurrentResolution.width();
	int32	YLen=CurrentResolution.height();
	if(BufferDimCounts<1){
		return false;
	}
	if(Buff[0]->GetWidth()<XLen || Buff[0]->GetHeight()<YLen){
		return false;
	}

	if(BufferDimCounts==3){
		for(int y = 0; y < YLen; y++) {
			BYTE	*dR = Buff[0]->GetY(y);
			BYTE	*dG = Buff[1]->GetY(y);
			BYTE	*dB = Buff[2]->GetY(y);
			BYTE	*s = DataBuff + y * XLen * 3;
			for(int x=0; x < XLen; x++) {
				dR[x] = s[0]; // R
				dG[x] = s[1]; // G
				dB[x] = s[2]; // B
				s+=3;
			}
		}
	}
	else if(BufferDimCounts==1){
		for(int y = 0; y < YLen; y++) {
			BYTE	*dR = Buff[0]->GetY(y);
			BYTE	*s = DataBuff + y * XLen;
			for(int x=0; x < XLen; x++) {
				dR[x] = s[0]; // R
				s++;
			}
		}
	}
	Captured=false;
	return true;
}

bool	USBQtCamera::StartCapture(void)
{
	Captured=false;
	ImageCapture->capture();
	return true;
}

void USBQtCamera::onImageCaptured(int id, const QImage &preview)
{
    Q_UNUSED(id);
    
    QImage rgbImage = preview.convertToFormat(QImage::Format_RGB888);

    int width		= rgbImage.width();
    int height		= rgbImage.height();
    int byteCount	= rgbImage.sizeInBytes();
    
    const uchar* data = rgbImage.constBits();
	if(DataBuff==NULL){
		DataBuff = new BYTE[width*height * 3]; // RGB
	}
	memcpy(DataBuff,data,byteCount);
    //// �y���z�ŏ��̃s�N�Z����R, G, B���\��
    //if (byteCount >= 3) {
    //    int r = data[0];
    //    int g = data[1];
    //    int b = data[2];
    //    qDebug() << "Pixel(0,0) RGB:" << r << g << b;
    //}
	//
    //// ������ data �|�C���^���g���ĉ摜�������C�u�����ɓn�������A���͂��s�������ł��܂��B
    //// ����: QImage���j���������ƃ|�C���^�������ɂȂ邽�߁A�K�v�Ȃ��f�[�^���R�s�[���Ă��������B

	Captured=true;
    emit finished(); // �A�v���P�[�V�������I��������
}

bool	USBQtCamera::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)	return false;
	if(::Save(f,CurrentResolution)==false)	return false;

    int	tCurrentExposureMode=(int)CurrentExposureMode;
	if(::Save(f,tCurrentExposureMode)==false)	return false;
	int	tCurrentFlashMode = (int)CurrentFlashMode;
	if(::Save(f,tCurrentFlashMode)==false)	return false;

	if(::Save(f,CurrentExposureCompensation)==false)	return false;
	if(::Save(f,CurrentISO)==false)	return false;

	int	tCurrentFocusMode = (int)CurrentFocusMode;
	if(::Save(f,tCurrentFocusMode)==false)	return false;
	if(::Save(f,CurrentFocusDistance)==false)	return false;
	if(::Save(f,CurrentCustomFocusPoint)==false)	return false;
	int tCurrentWhiteBalanceMode = (int)CurrentWhiteBalanceMode;
	if(::Save(f,tCurrentWhiteBalanceMode)==false)	return false;
	if(::Save(f,CurrentColorTemperature)==false)	return false;
	int	tCurrentTorchMode = (int)CurrentTorchMode;
	if(::Save(f,tCurrentTorchMode)==false)	return false;
	return true;
}

bool	USBQtCamera::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,CurrentResolution)==false)	return false;

	int	tCurrentExposureMode;
	if(::Load(f,tCurrentExposureMode)==false)	return false;
	CurrentExposureMode = (QCamera::ExposureMode)tCurrentExposureMode;
	int	tCurrentFlashMode;
	if(::Load(f,tCurrentFlashMode)==false)	return false;
	CurrentFlashMode = (QCamera::FlashMode)tCurrentFlashMode;

	if(::Load(f,CurrentExposureCompensation)==false)	return false;
	if(::Load(f,CurrentISO)==false)	return false;

	int	tCurrentFocusMode = (int)CurrentFocusMode;
	if(::Load(f,tCurrentFocusMode)==false)	return false;
	if(::Load(f,CurrentFocusDistance)==false)	return false;
	if(::Load(f,CurrentCustomFocusPoint)==false)	return false;
	int tCurrentWhiteBalanceMode;
	if(::Load(f,tCurrentWhiteBalanceMode)==false)	return false;
	CurrentWhiteBalanceMode = (QCamera::WhiteBalanceMode)tCurrentWhiteBalanceMode;
	if(::Load(f,CurrentColorTemperature)==false)	return false;

	int	tCurrentTorchMode;
	if(::Load(f,tCurrentTorchMode)==false)	return false;
	CurrentTorchMode = (QCamera::TorchMode)tCurrentTorchMode;
	return true;
}

bool	USBQtCamera::ReflectToCamera(void)
{
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(CamNo);
	bool	found=false;
	for (const QCameraFormat &format : CamDevice.videoFormats()) {
		if(format.resolution() == CurrentResolution) {
			Camera->setCameraFormat(format);
			found=true;
			break;
		}
	}

	Camera->setExposureMode(CurrentExposureMode);
	Camera->setFlashMode(CurrentFlashMode);
	Camera->setExposureCompensation(CurrentExposureCompensation);
	Camera->setManualIsoSensitivity(CurrentISO);
	//Camera->exposure()->setShutterSpeed(CurrentShutterSpeed);

	Camera->setFocusMode(CurrentFocusMode);
	Camera->setFocusDistance(CurrentFocusDistance);
	Camera->setCustomFocusPoint(CurrentCustomFocusPoint);
	Camera->setWhiteBalanceMode(CurrentWhiteBalanceMode);
	Camera->setColorTemperature(CurrentColorTemperature);
	Camera->setTorchMode(CurrentTorchMode);


	return true;
}

void USBQtCamera::handleErrorOccurred(int id, QImageCapture::Error error, const QString &errorString)
{
}

//========================================================================