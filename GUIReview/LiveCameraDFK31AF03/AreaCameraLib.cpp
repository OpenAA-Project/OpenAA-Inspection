#include "LiveCameraDFK31AF03Resource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AreaCamera\AreaCameraLib\AreaCameraLib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "areacameralib.h"
#include <windows.h>

#include <QWidget>
#include <QMessageBox>

#if !defined(UNITS)
    #define UNITS	1
#endif
#define UNITSMAP    ((1<<UNITS)-1)  /* shorthand - bitmap of all units */

const QString confFileName = /**/"AreaCamera_DFK31AF03.xml";

void fixAspect(int cur_width, int cur_height, int fmt_width, int fmt_height, int &fix_width, int &fix_height);

inline	BYTE	Clip255(int d)
{
	if(d<0)
		return 0;
	if(d>255)
		return 255;
	return d;
}

AreaCameraLib::AreaCameraLib(QWidget *parent):m_parent(parent),m_dWidth(640),m_dHeight(480)
{
	if( !DShowLib::InitLibrary() ){
		QMessageBox::critical(NULL, LangSolver.GetString(AreaCameraLib_LS,LID_7)/*"Initial Error"*/, LangSolver.GetString(AreaCameraLib_LS,LID_8)/*"The IC Imaging Control Class Library could not be initialized.\n(invalid license key?)"*/);
		return;
	}

	//atexit(DShowLib::ExitLibrary);
}

AreaCameraLib::~AreaCameraLib()
{
	m_cGrabber.stopLive();
	m_cGrabber.closeDev();
	//pxd_PIXCIclose();
	DShowLib::ExitLibrary();
}

bool AreaCameraLib::StartLive()
{
	if( m_cGrabber.isDevValid() && !m_cGrabber.isLive() )
		m_cGrabber.startLive();
	else
		return false;
	//pxd_goLive(UNITSMAP, 1);
	return true;
}

bool AreaCameraLib::StopLive()
{
	if( m_cGrabber.isDevValid() )m_cGrabber.stopLive();
	//pxd_goUnLive(UNITSMAP);
	return true;
}

bool AreaCameraLib::SingleShot()
{
	StartLive();
	Error e = m_pSink->snapImages(1, 2000);
	if( e.isError() ){
		QMessageBox::critical(m_parent, LangSolver.GetString(AreaCameraLib_LS,LID_9)/*"SnapError"*/, LangSolver.GetString(AreaCameraLib_LS,LID_10)/*"SnapImage is Fault!"*/);
		return false;
	}

		
	//tFrameHandlerSinkPtr pSink = m_cGrabber.getSinkTypePtr();
	//m_cGrabber.stopLive();
	//pSink->setSnapMode(true);

	//m_cGrabber.startLive();
	//bool ch = m_cGrabber.snapImages();
	//m_cGrabber.stopLive();
	//
	//Sleep(100);

	////DShowLib::Error e = pSink->snapImages(1);

	//if(ch==false/*e.isError()*/){
	//	//QMessageBox::critical(m_parent, "Snap Error", e.c_str());
	//	QMessageBox::critical(m_parent, "Snap Error", "Snap is Flalse");
	//	pSink->setSnapMode(false);
	//	return false;
	//}
	return true;
}

bool AreaCameraLib::GetCameraImage()
{
	WINDOWINFO info;
	GetWindowInfo(m_hWnd, &info);


	//long width = abs(info.rcWindow.right - info.rcWindow.left);
	//long height = abs(info.rcWindow.bottom - info.rcWindow.top);

	//if(width/(double)height < m_dWidth/(double)m_dHeight){// 高さが大きい
	//	height = (long)(width * m_dHeight / (double)m_dWidth);
	//}
	//else{
	//	width = (long)(height * m_dWidth / (double)m_dHeight);
	//}

	int width, height;

	fixAspect(abs(info.rcWindow.right - info.rcWindow.left), abs(info.rcWindow.bottom - info.rcWindow.top), m_dWidth, m_dHeight, width, height);

	m_cGrabber.setDefaultWindowPosition(false);
	m_cGrabber.setWindowSize(width, height);
	return m_cGrabber.isLive();
}

void fixAspect(int cur_width, int cur_height, int fmt_width, int fmt_height, int &fix_width, int &fix_height)
{
	double wh_rate = fmt_width / (double)fmt_height;

	if(cur_width/(double)cur_height < fmt_width/(double)fmt_height){// ウインドウの高さが大きい(調整後の大きさは幅に依存)
		fix_width	=	cur_width;
		fix_height	=	(int)(fmt_height * cur_width / (double)fmt_width);
	}
	else{
		fix_height	=	cur_height;// そのまま
		fix_width	=	(int)(fmt_width * cur_height / (double)fmt_height);
	}
}

bool AreaCameraLib::GetCameraImage(QImage *image)
{
	if(image==NULL)return false;

	//int nSnaps = m_pSink->getFrameCount();

	if(m_cGrabber.isLive()==false)m_cGrabber.startLive();
	if(m_pSink->snapImages(1, 2000).isError()){
		QMessageBox::critical(m_parent, LangSolver.GetString(AreaCameraLib_LS,LID_11)/*"Snap Error"*/, LangSolver.GetString(AreaCameraLib_LS,LID_12)/*"Get Image is Error"*/);
		return false;
	}

	smart_ptr<DShowLib::MemBufferCollection> pMem = m_pSink->getMemBufferCollection();

	if(pMem==0)return false;

	DShowLib::MemBufferCollection::tMemBufferPtr mem = (*pMem)[0];

	if(mem==NULL)return false;

	mem->lock();

	int width = mem->getFrameType().dim.cx;
	int height = mem->getFrameType().dim.cy;

	double wDig = width / (double)image->width();
	double hDig = height / (double)image->height();

	pixel24 = (RGB24Pixel*)mem->getPtr();
	RGB24Pixel *line;
	//#pragma omp parallel
	{
		//#pragma omp for
		for(int y=0; y<image->height(); y++){
			int tag_y = (int)(y*hDig);
			QRgb *pYLine=(QRgb*)image->scanLine(image->height() - 1 - y);
			line = (pixel24 + tag_y*width);
			for(int x=0; x<image->width(); x++){
				int tag_x = (int)(x*wDig);
				pYLine[x] = qRgb(Clip255(line[tag_x].r), Clip255(line[tag_x].g), Clip255(line[tag_x].b));	
			}
			//pixel24 += width;
		}
	}

	mem->unlock();

	return true;

}

bool AreaCameraLib::Close()
{
	if(m_cGrabber.isLive())
		m_cGrabber.stopLive();
	m_cGrabber.closeDev();
	//pxd_PIXCIclose();
	return true;
}

bool AreaCameraLib::Open()
{
	if(m_cGrabber.isDevValid() && !m_cGrabber.isDevOpen() && m_cGrabber.isLive()){
		m_cGrabber.stopLive();
	}
	
	// Try to load the previously used video capture device.
	if( m_cGrabber.loadDeviceStateFromFile(confFileName.toStdString()))
	{
		// Display the device's name in the caption bar of the application.
		//SetWindowText( "ICTest " + CString(m_cGrabber.getDev().c_str()));
		m_cGrabber.startLive();
	}else{
		m_cGrabber.showDevicePage(m_hWnd);
		if(m_cGrabber.isDevValid())
			m_cGrabber.saveDeviceStateToFile(confFileName.toStdString());
		else
			return false;
	}
	//if (pxd_PIXCIopen(/**/"", /**/"", /**/"./SV5.fmt") < 0){
	//	pxd_mesgFault(1);
	//	return false;
	//}
	return true;
}

void AreaCameraLib::Init(QWidget *w,int W,int H)
{
	if(w==NULL)return;
	
	// Get HWND value
	m_hWnd = w->winId();
	// Resize the video window to 640*480 pixels.
	// m_cStaticVideoWindow.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);
	// Assign this window to the Grabber object for live video display.
	m_cGrabber.setHWND(m_hWnd);


	// Add the CListener object to the the Grabber object.
	//m_cGrabber.addListener(&m_cListener);

	// Set the sink
	m_pSink = DShowLib::FrameHandlerSink::create( DShowLib::eRGB24, 1 );
	m_pSink->setSnapMode( true ); // Automatically copy every frame to the sink and call CListener::frameReady().
	m_cGrabber.setSinkType( m_pSink );

	// Try to load the previously used video capture device.
	if( m_cGrabber.loadDeviceStateFromFile(LangSolver.GetString(AreaCameraLib_LS,LID_13)/*"AreaCamera_DFK31AF03.xml"*//*confFileName.toStdString())*/))
	{
		// Display the device's name in the caption bar of the application.
		//SetWindowText( "ICTest " + CString(m_cGrabber.getDev().c_str()));
		m_cGrabber.startLive();
	}else{
		if(m_cGrabber.showDevicePage(m_hWnd)==true){
			if( m_cGrabber.isDevValid() )
				m_cGrabber.saveDeviceStateToFile(LangSolver.GetString(AreaCameraLib_LS,LID_14)/*"AreaCamera_DFK31AF03.xml"*//*confFileName.toStdString())*/);
		}
	}

	// Adjust the live video to the size of the window.
	// 出力中のデフォルトビデオフォーマットのサイズ
	int fmt_width = m_cGrabber.getAcqSizeMaxX();
	int fmt_height = m_cGrabber.getAcqSizeMaxY();

	// アスペクト保持後のビデオ出力ウインドウサイズ
	int fix_width, fix_height;

	// ビデオフォーマットのアスペクト比に合わせた出力画像サイズ計算
	fixAspect(W, H, fmt_width, fmt_height, fix_width, fix_height);

	// 保持
	m_dWidth = fix_width;
	m_dHeight = fix_height;

	// m_cStaticVideoWindow.GetClientRect( &rect);
	m_cGrabber.setDefaultWindowPosition(false);
	m_cGrabber.setWindowSize(GetWidth(), GetHeight());

	//if((double)W/H < (double)GetWidth()/GetHeight()){
	//	m_dWidth=GetWidth()*H/GetHeight();
	//	m_dHeight=GetHeight()*H/GetHeight();
	//	m_dx=-(m_dWidth-W)>>1;
	//	m_dy=-(m_dHeight-H)>>1;
	//}
	//else{
	//	m_dWidth=GetWidth()*W/GetWidth();
	//	m_dHeight=GetHeight()*W/GetWidth();
	//	m_dx=-(m_dWidth-W)>>1;
	//	m_dy=-(m_dHeight-H)>>1;
	//}
}

void AreaCameraLib::SetBrightness(int BArray[])
{
	memcpy(m_pdBrightArray,BArray,sizeof(int[256]));
}

void AreaCameraLib::SetPlusRGB(int Red,int Green,int Blue)
{
	m_dPlusRed		= Red;
	m_dPlusGreen	= Green;
	m_dPlusBlue		= Blue;
	m_cListener.setPlusRGB(Red, Green, Blue);
}

bool AreaCameraLib::ShowSettingDialog()
{
	if(m_cGrabber.isDevValid())
	{
		m_cGrabber.showVCDPropertyPage(m_hWnd, LangSolver.GetString(AreaCameraLib_LS,LID_15)/*"カメラ設定"*/);
		m_cGrabber.saveDeviceStateToFile(LangSolver.GetString(AreaCameraLib_LS,LID_16)/*"AreaCamera_DFK31AF03.xml"*//*confFileName.toStdString())*/);
	}
	return true;
}