/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AreaCamera\AreaCameraLib\AreaCameraLib.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AREACAMERALIB_H
#define AREACAMERALIB_H

#include <QImage>
#include <QRgb>

#include <tisudshl.h>

#include "listener.h"

#include "ICColorStruct.h"


class AreaCameraLib
{
public:
	AreaCameraLib(QWidget *parent=NULL);
	~AreaCameraLib();
	bool	StartLive();
	bool	StopLive();
	bool	SingleShot();
	bool	GetCameraImage(QImage *image);
	bool	GetCameraImage();
	bool	Close();
	bool	Open();
	bool	ShowSettingDialog();

	void	Init(QWidget *w,int W,int H);
	void	SetBrightness(int BArray[]);
	void	SetPlusRGB(int Red,int Green,int Blue);

	int		GetWidth()	{	return(m_dWidth);	}
	int		GetHeight()	{	return(m_dHeight);	}

private:
	DShowLib::Grabber m_cGrabber;
	DShowLib::FrameHandlerSink::tFHSPtr m_pSink;
	DShowLib::CListener m_cListener;

	HWND m_hWnd;
	int m_dWidth;
	int m_dHeight;
	int m_dx,m_dy;
	int m_pdBrightArray[256];
	RGB24Pixel *pixel24;

	int m_dPlusRed,m_dPlusGreen,m_dPlusBlue;

	QWidget *m_parent;
};

#endif // AREACAMERALIB_H
