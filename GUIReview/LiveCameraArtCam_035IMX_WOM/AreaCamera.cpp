#include "LiveCameraArtCam_035IMX_WOMResource.h"
#include "AreaCamera.h"

#include <QImage>
#include <QCoreApplication>

#include "ICColorStruct.h"

//==============================================================================================================
//ThreadView
//==============================================================================================================

void ThreadView::run()
{
	while(!m_flg_stop){
		if(m_flg_updateEnable){
			m_flg_updateEnable = false;
			emit update();
		}
		msleep(m_intervalTime);
	}
}

DShowLib::MemBufferCollection::tMemBufferPtr	getSingleFrame( DShowLib::Grabber& gr, DShowLib::tColorformatEnum type )
{
	smart_ptr<DShowLib::FrameHandlerSink> pHandlerSink = DShowLib::FrameHandlerSink::create( type, 1 );
	pHandlerSink->setSnapMode( true );

	gr.setSinkType( pHandlerSink );

	gr.startLive( false );
	Sleep( 250 ); // give the device time to adjust automatic settings i.e. auto exposure
	pHandlerSink->snapImages( 1, 2000 );
	gr.stopLive();

	// get pointer to the image data
	return pHandlerSink->getLastAcqMemBuffer();
}

AreaCamera::AreaCamera(QWidget *parent)
	:QLabel(parent),m_paintWidget(this),m_thread(NULL),m_isEditMode(true)
{
	// 画面更新用スレッド生成
	m_thread = new ThreadView(50);

	// 表示更新タイミングをスレッドのシグナルにあわせる
	connect(m_thread, SIGNAL(update()), this, SLOT(Update()), Qt::QueuedConnection);

	// 緊急停止対応
	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(uninit()));
}

AreaCamera::~AreaCamera()
{
	uninit();
}

bool AreaCamera::init()
{
	if(isInitialized()==true){
		return true;
	}

	if(m_thread->isRunning()==true){
		m_thread->stop();
		m_thread->wait();
	}
	if(m_paintWidget==NULL){
		return false;
	}
	if( !DShowLib::InitLibrary() ){
		return false;
	}

	if(m_cGrabber.isDevOpen()==true){
		m_cGrabber.stopLive();
		m_cGrabber.closeDev();
	}
	//m_pSink.destroy();
	
	// Get HWND value
	//m_hWnd = w->winId();

	// Resize the video window to 640*480 pixels.
	// m_cStaticVideoWindow.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);
	// Assign this window to the Grabber object for live video display.
	//m_cGrabber.setHWND(NULL/*m_paintWidget->winId()*//*this->winId()*//*m_hWnd*/);

	// Add the CListener object to the the Grabber object.
	//m_cGrabber.addListener(&m_cListener);

	// Set the sink
	m_pSink = DShowLib::FrameHandlerSink::create( DShowLib::eRGB24, 1 );
	//m_pSink->setSnapMode( true ); // Automatically copy every frame to the sink and call CListener::frameReady().
	m_cGrabber.setSinkType( m_pSink );

	// Try to load the previously used video capture device.
	if( m_cGrabber.loadDeviceStateFromFile(LangSolver.GetString(AreaCamera_LS,LID_0)/*"AreaCamera_DFK31AF03.xml"*//*confFileName.toStdString())*/))
	{
		// Display the device's name in the caption bar of the application.
		//SetWindowText( "ICTest " + CString(m_cGrabber.getDev().c_str()));
		m_cGrabber.startLive(false);
	}else{
		if(m_cGrabber.showDevicePage(m_paintWidget->winId()/*this->winId()*/)==true){
			if( m_cGrabber.isDevValid() ){
				m_cGrabber.saveDeviceStateToFile(LangSolver.GetString(AreaCamera_LS,LID_1)/*"AreaCamera_DFK31AF03.xml"*//*confFileName.toStdString())*/);
			}
		}
		m_cGrabber.startLive(false);
	}

	Resize();

	m_thread->setStopFlag(false);
	m_thread->setUpdateEnable(true);
	m_thread->start();

	//// Adjust the live video to the size of the window.
	//// 出力中のデフォルトビデオフォーマットのサイズ
	//int fmt_width = m_cGrabber.getAcqSizeMaxX();
	//int fmt_height = m_cGrabber.getAcqSizeMaxY();

	//// アスペクト保持後のビデオ出力ウインドウサイズ
	////int fix_width, fix_height;

	//// ビデオフォーマットのアスペクト比に合わせた出力画像サイズ計算
	//QSize canvasSize = size();
	//QSize formatSize = QSize(m_cGrabber.getAcqSizeMaxX(), m_cGrabber.getAcqSizeMaxY());

	//QSize fix_size = canvasSize;
	//fix_size.scale(formatSize, Qt::KeepAspectRatio);

	//// 保持
	////m_dWidth = fix_width;
	////m_dHeight = fix_height;
	//m_outputImageSize = fix_size;

	//// m_cStaticVideoWindow.GetClientRect( &rect);
	//m_cGrabber.setDefaultWindowPosition(false);
	//m_cGrabber.setWindowSize(fix_size.width(), fix_size.height());

	setInitialized(true);
	return true;
}

void AreaCamera::uninit(void)
{
	if(isEditMode()==false && isInitialized()==true){
		m_cGrabber.stopLive();
		if(m_thread->isRunning()==true){
			m_thread->stop();
			m_thread->wait();
		}
		if(m_thread!=NULL){
			disconnect(m_thread, SIGNAL(update()), this, SLOT(Update()));
			delete m_thread;
			m_thread = NULL;
		}
		m_cGrabber.closeDev();
		m_cGrabber.setSinkType(NULL);
		m_pSink.destroy();
		m_pSink = NULL;
		DShowLib::ExitLibrary();
		setInitialized(false);
	}
}

void AreaCamera::Update()
{
	if(m_thread!=NULL){
		GetCameraImage();
		m_thread->setUpdateEnable(true);
	}
}

void AreaCamera::Resize(void)
{
	// Adjust the live video to the size of the window.
	// 出力中のデフォルトビデオフォーマットのサイズ
	int fmt_width = m_cGrabber.getAcqSizeMaxX();
	int fmt_height = m_cGrabber.getAcqSizeMaxY();

	// アスペクト保持後のビデオ出力ウインドウサイズ
	//int fix_width, fix_height;

	// ビデオフォーマットのアスペクト比に合わせた出力画像サイズ計算
	QSize canvasSize = m_paintWidget->size();
	QSize formatSize = QSize(fmt_width, fmt_height);

	QSize fix_size = formatSize;
	fix_size.scale(canvasSize, Qt::KeepAspectRatio);

	// 保持
	//m_dWidth = fix_width;
	//m_dHeight = fix_height;
	m_outputImageSize = fix_size;

	// m_cStaticVideoWindow.GetClientRect( &rect);
	m_cGrabber.setDefaultWindowPosition(false);
	m_cGrabber.setWindowSize(fix_size.width(), fix_size.height());
}

void AreaCamera::mousePressEvent(QMouseEvent *event)
{
	QLabel::mousePressEvent(event);

	if(pixmap()==NULL || pixmap()->isNull()==true){
		return;
	}

	QPointF p = rect().center();
}

void AreaCamera::showEvent(QShowEvent *event)
{
	QLabel::showEvent(event);

	if(m_thread==NULL){
		m_thread = new ThreadView(50);
		connect(m_thread, SIGNAL(update()), this, SLOT(Update()), Qt::QueuedConnection);
	}
	if(isEditMode()==false && isInitialized()==false){
		init();
	}
}

void AreaCamera::hideEvent(QHideEvent *event)
{
	QLabel::hideEvent(event);

	uninit();
}

bool AreaCamera::StartLive(void)
{
	if( m_cGrabber.isDevValid()==true ){
		if( m_cGrabber.isDevOpen()==false && m_cGrabber.loadDeviceStateFromFile(LangSolver.GetString(AreaCamera_LS,LID_2)/*"AreaCamera_DFK31AF03.xml"*/)==false ){
			return false;
		}
		if( m_cGrabber.isLive()==false ){
			return m_cGrabber.startLive(false);
		}else{
			return true;
		}
	}else{
		return false;
	}
}

bool AreaCamera::StopLive(void)
{
	return true;
}

bool AreaCamera::SingleShot(void)
{
	return true;
}

bool AreaCamera::GetCameraImage(void)
{
	return true;
}

bool AreaCamera::GetCameraImage(QImage &image)
{
	StartLive();

	return true;
}

bool AreaCamera::Close(void)
{
	StopLive();
	return m_cGrabber.closeDev();
}

bool AreaCamera::Open(void)
{
	if(m_cGrabber.isLive()==true){
		m_cGrabber.stopLive();
	}
	
	// Try to load the previously used video capture device.
	if( m_cGrabber.loadDeviceStateFromFile(LangSolver.GetString(AreaCamera_LS,LID_3)/*"AreaCamera_DFK31AF03.xml"*/)==true )
	{
		// Display the device's name in the caption bar of the application.
		//SetWindowText( "ICTest " + CString(m_cGrabber.getDev().c_str()));
		return true;
	}else{
		//m_cGrabber.showDevicePage(m_paintWidget->winId()/*this->winId()*/);
		if(m_cGrabber.isDevValid()==true){
			return m_cGrabber.saveDeviceStateToFile(LangSolver.GetString(AreaCamera_LS,LID_4)/*"AreaCamera_DFK31AF03.xml"*/);
		}else{
			return false;
		}
	}
}

bool AreaCamera::ShowSettingDialog(void)
{
	if( m_paintWidget!=NULL &&
		m_cGrabber.isDevValid()==true &&
		m_cGrabber.showVCDPropertyPage(m_paintWidget->winId()/*this->winId()*/, LangSolver.GetString(AreaCamera_LS,LID_5)/*"Setting Camera Form"*/)==true &&
		m_cGrabber.saveDeviceStateToFile(LangSolver.GetString(AreaCamera_LS,LID_6)/*"AreaCamera_DFK31AF03.xml"*/)==true){
		return true;
	}else{
		return false;
	}
}

bool AreaCamera::changePaintLabel(QLabel *label)
{
	if(m_paintWidget==label)return true;

	m_thread->stop();
	m_thread->wait();
	
	if(label==NULL){
		//m_cGrabber.setHWND(label->winId());
		m_paintWidget = this;
	}else{
		//m_cGrabber.setHWND(winId());
		m_paintWidget = label;
	}

	m_thread->setStopFlag(false);
	m_thread->start();

	return true;
}

void AreaCamera::grapWindow(WId id)
{
	Close();
	Open();

	m_cGrabber.setHWND(id);

	WINDOWINFO wi;
	GetWindowInfo(id, &wi);
	
	// Adjust the live video to the size of the window.
	// 出力中のデフォルトビデオフォーマットのサイズ
	int fmt_width = m_cGrabber.getAcqSizeMaxX();
	int fmt_height = m_cGrabber.getAcqSizeMaxY();

	// アスペクト保持後のビデオ出力ウインドウサイズ
	//int fix_width, fix_height;

	// ビデオフォーマットのアスペクト比に合わせた出力画像サイズ計算
	QSize canvasSize = QSize(qAbs(wi.rcWindow.left - wi.rcWindow.right), qAbs(wi.rcWindow.top - wi.rcWindow.bottom));
	QSize formatSize = QSize(m_cGrabber.getAcqSizeMaxX(), m_cGrabber.getAcqSizeMaxY());

	QSize fix_size = canvasSize;
	fix_size.scale(formatSize, Qt::KeepAspectRatio);

	// 保持
	//m_dWidth = fix_width;
	//m_dHeight = fix_height;
	m_outputImageSize = fix_size;

	// m_cStaticVideoWindow.GetClientRect( &rect);
	m_cGrabber.setDefaultWindowPosition(false);
	m_cGrabber.setWindowSize(fix_size.width(), fix_size.height());

	StartLive();
}

void AreaCamera::resetWindow()
{
	//m_cGrabber.setHWND(m_paintWidget->winId()/*this->winId()*/);

	Resize();
}