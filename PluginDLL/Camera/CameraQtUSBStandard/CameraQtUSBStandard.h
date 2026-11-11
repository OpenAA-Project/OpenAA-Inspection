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

#pragma once

#include "cameraqtusbstandard_global.h"
#include "XCameraHandle.h"
#include "XGUIPacketForDLL.h"
#include "XCameraCommon.h"
#include <QStringList>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>

class	WMFCamera;
class	PropertyItem;
class	ImageBuffer;

class  USBQtCamera :public CameraHandle
{
	Q_OBJECT

	QCamera	*Camera;
	QImageCapture	*ImageCapture;
	QMediaCaptureSession session;

public:
	int		CamNo;

	QSize						CurrentResolution;
    QCamera::ExposureMode		CurrentExposureMode;
    QCamera::FlashMode			CurrentFlashMode;
    qreal						CurrentExposureCompensation;
	int							CurrentISO; 
    QCamera::FocusMode			CurrentFocusMode;
    qreal						CurrentFocusDistance;
	QPointF						CurrentCustomFocusPoint;
    QCamera::WhiteBalanceMode	CurrentWhiteBalanceMode;
	int							CurrentColorTemperature;
	QCamera::TorchMode			CurrentTorchMode;


	BYTE	*DataBuff;
	bool	Captured	=false;
public:
	USBQtCamera(LayersBase *base,int CamNo);
	virtual	~USBQtCamera(void);

	QCamera *GetCamera(void)	{	return Camera;	}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	bool	ChangeInfo(CameraReqInfo &caminfo);

	bool	ReflectToCamera(void);
	bool	StartCapture(void);
	bool	IsCaptured(void)	{ return Captured; }
	bool	GetImage(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
signals:
	void	finished();
private slots:
	void onImageCaptured(int id, const QImage &preview);
	void handleErrorOccurred(int id, QImageCapture::Error error, const QString &errorString);
};