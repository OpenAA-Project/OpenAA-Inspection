/*
 * Copyright (C) 2023
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