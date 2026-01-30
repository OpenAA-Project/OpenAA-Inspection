/*
 * Copyright (C) 2022
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

#pragma once


#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XCameraClass.h"
#include <QThread>
#include "XBoolList.h"
#include "NListComp.h"
#include <QSharedMemory>
#include <QString>
#include <QMutex>
#include "XMainSchemeMemory.h"

//#include "jpeglib.h"
#include "turbojpeg.h"

#include <QCameraInfo>
#include <QCamera>
#include <QObject>
#include <QVideoFrame>
#include <QVideoProbe>
#include <QCameraViewfinderSettings>

#define	CameraBufferSize	10

class	WMFCamera : public QObject
{
    Q_OBJECT

	ImageBuffer *CamBuff[CameraBufferSize][3];
	int	WPoint;
	int	RPoint;
	BYTE	*MJPegTmpBuff;

	QCameraInfo		CamInfo;
	QCamera			*Camera;
	QVideoProbe		*CamImage;

	QList<QCameraViewfinderSettings>	CamSettingList;
	QCameraViewfinderSettings			CurrentSetting;

	int		CamID;
	QString	DeviceName;
	QString	DeviceID;
	QString	ProductID;
	int	Captured;
	DWORD	ComputerMiliSec;
	DWORD	SpanMilisec;

	bool	MirrorX;
	bool	MirrorY;
	int		RotationAngle;

	int	    aSrcStride		;
	int		aWidthInPixels	;
	int		aHeightInPixels	;
public:
	tjhandle DecHndle;

	WMFCamera(int ID ,const QCameraInfo &info);
	virtual	~WMFCamera(void);

	int		GetCamID(void)			{	return CamID;		}
	QString	GetDeviceName(void)		{	return DeviceName;	}
	
	const QCameraViewfinderSettings	&GetCurrentSetting(void)	{	return CurrentSetting;	}
	void	SetCurrentSetting(QCameraViewfinderSettings &s);
	
	DWORD	GetSpanMilisec(void)	{	return SpanMilisec;	}



signals:
	void	SignalUpdateSetting(int ID);
private slots:
	void SlotVideoFrameProbed(const QVideoFrame &frame);

private:
	void	TransformImage_RGB24(ImageBuffer *Buff[3]
								,const BYTE* aSrc
								,DWORD		SrcTotalBuffByte);
	void	TransformImage_RGB32(ImageBuffer *Buff[]
								,const BYTE* aSrc
								,DWORD		SrcTotalBuffByte);
	void	TransformImage_YUY2(ImageBuffer *Buff[]
								,const BYTE* aSrc
								,DWORD		SrcTotalBuffByte);
	void	MakeMonochrome(ImageBuffer *Buff[]);

	void	TransformImage_MJPG(ImageBuffer *Buff[]
								,const BYTE* aSrc
								,DWORD		SrcTotalBuffByte);
};

bool	CheckCamera(const QCameraInfo &info
					,int PermissionVendorID[]
					,int PermissionVendorCount);