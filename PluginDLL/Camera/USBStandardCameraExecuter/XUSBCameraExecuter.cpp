#include "XUSBCameraExecuter.h"
#include <stdlib.h>
#include <stdio.h>
#include <QIODevice>
#include <QAbstractVideoBuffer>
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XDataInLayer.h"

bool	CheckCamera(const QCameraInfo &info
					,int PermissionVendorID[]
					,int PermissionVendorCount)
{
	QString d=info.deviceName();
	QString s=info.description();

	int	vid=0;
	int	pid=0;
	int	k=d.indexOf("vid_");
	if(k>0){
		QString	svid=d.mid(k+4).left(4);
		bool	ok;
		vid=svid.toInt(&ok,16);
	}
	k=d.indexOf("pid_");
	if(k>0){
		QString	spid=d.mid(k+4).left(4);
		bool	ok;
		pid=spid.toInt(&ok,16);
	}
	for(int i=0;i<PermissionVendorCount;i++){
		if(PermissionVendorID[i]==vid){
			return true;
		}
	}
	return false;
}

//===============================================================
	
WMFCamera::WMFCamera(int camid ,const QCameraInfo &info)
	:CamID(camid)
{
	MirrorX			=false;
	MirrorY			=false;
	RotationAngle	=0;
	WPoint			=0;
	RPoint			=0;
	aWidthInPixels	=0;
	aHeightInPixels	=0;
	MJPegTmpBuff	=NULL;

	DecHndle=tjInitDecompress();

	for(int i=0;i<CameraBufferSize;i++){
		CamBuff[i][0]=NULL;
		CamBuff[i][1]=NULL;
		CamBuff[i][2]=NULL;
	}

	CamInfo=info;
	DeviceName	=info.description();
	QString	d=info.deviceName();

	int	k=d.indexOf("vid_");
	if(k>0){
		DeviceID=d.mid(k+4).left(4);
	}
	k=d.indexOf("pid_");
	if(k>0){
		ProductID=d.mid(k+4).left(4);
	}

	Camera=new QCamera(info);
	CamImage=new QVideoProbe();
	CamImage->setSource(Camera);
	Captured		=0;
	SpanMilisec		=0;
	ComputerMiliSec	=::GetComputerMiliSec();
	bool	Ret=connect(CamImage,SIGNAL(videoFrameProbed(const QVideoFrame &)),this,SLOT(SlotVideoFrameProbed(const QVideoFrame &)));

	CamSettingList	=Camera->supportedViewfinderSettings();
	Camera->setCaptureMode(QCamera::CaptureVideo);
	Camera->start();
}

WMFCamera::~WMFCamera(void)
{
	delete	Camera;
	Camera=NULL;
	delete	CamImage;
	CamImage=NULL;
}

void WMFCamera::SlotVideoFrameProbed(const QVideoFrame &frame)
{
	((QVideoFrame *)&frame)->map(QAbstractVideoBuffer::ReadOnly);
	if(frame.isMapped()){
		Captured++;

		if(CamBuff[0][0]==NULL){
			CurrentSetting=Camera->viewfinderSettings();
			SetCurrentSetting(CurrentSetting);
		}

		if((Captured%30)==0){
			CurrentSetting=Camera->viewfinderSettings();
			emit	SignalUpdateSetting(CamID);
		}
		if((Captured%100)==0){
			DWORD	t=::GetComputerMiliSec();
			SpanMilisec=t-ComputerMiliSec;
			ComputerMiliSec=t;
		}
		if(aWidthInPixels>0){
			aSrcStride=frame.bytesPerLine()/aWidthInPixels;
			QVideoFrame::PixelFormat	F=frame.pixelFormat();
			ImageBuffer *Buff[3];
			Buff[0]=CamBuff[WPoint][0];
			Buff[1]=CamBuff[WPoint][1];
			Buff[2]=CamBuff[WPoint][2];
			int	Len=frame.mappedBytes();
			if(F==QVideoFrame::Format_Jpeg){
				TransformImage_MJPG(Buff
									,frame.bits()
									,Len);
			}
			else
			if(F==QVideoFrame::Format_YUYV){
				TransformImage_YUY2(Buff
									,frame.bits()
									,Len);
			}
			else
			if(F==QVideoFrame::Format_RGB32){
				TransformImage_RGB32(Buff
									,frame.bits()
									,Len);
			}
			else
			if(F==QVideoFrame::Format_RGB24){
				TransformImage_RGB24(Buff
									,frame.bits()
									,Len);
			}
			WPoint++;
			if(WPoint>=CameraBufferSize){
				WPoint=0;
			}
		}
	}
}

void	WMFCamera::SetCurrentSetting(QCameraViewfinderSettings &s)
{
	Camera->setViewfinderSettings(s);
	QSize	Size=s.resolution();

	for(int i=0;i<CameraBufferSize;i++){
		if(CamBuff[i][0]==NULL){
			CamBuff[i][0]=new ImageBuffer(0,Size.width(),Size.height());
			CamBuff[i][1]=new ImageBuffer(0,Size.width(),Size.height());
			CamBuff[i][2]=new ImageBuffer(0,Size.width(),Size.height());
		}
		else{
			CamBuff[i][0]->Set(0,0,Size.width(),Size.height());
			CamBuff[i][1]->Set(0,0,Size.width(),Size.height());
			CamBuff[i][2]->Set(0,0,Size.width(),Size.height());
		}
	}
	aWidthInPixels	=Size.width();
	aHeightInPixels	=Size.height();
	if(MJPegTmpBuff!=NULL){
		delete	[]MJPegTmpBuff;
	}
	MJPegTmpBuff = new BYTE[4*aWidthInPixels * aHeightInPixels];
}