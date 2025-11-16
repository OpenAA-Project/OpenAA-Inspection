#include "LiveCameraArtCam_035IMX_WOMResource.h"
#include "LiveCameraArtCam_035IMX_WOM.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "LiveCameraCommonPacket.h"

static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"LiveCameraArtCam_035IMX_WOM";

#include "CArtCamSdk.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Camera ArtCam ARTCAM-035IMX-WOM viewer.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	LiveCameraArtCam_035IMX_WOM *form = new LiveCameraArtCam_035IMX_WOM(Base,parent);
	return form;
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":LiveCameraArtCam_035IMX_WOM.PNG")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LiveCameraArtCam_035IMX_WOM
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LiveCameraArtCam_035IMX_WOM::LiveCameraArtCam_035IMX_WOM(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),previewLabel(NULL),threadView(new ThreadView(5)),cameraImageBuff(NULL),cameraImageBuffSize(0)
{
	ui.setupUi(this);

	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	if(GetEditMode()==false){
		camSdk.LoadLibrary(L"ArtCamSdk_IMX035_WOM.dll");
		camSdk.Initialize(NULL);

		int w = width();
		int h = height();

		QSize winSize = size();
		QSize camSize( camSdk.Width(), camSdk.Height() );

		camSize.scale( winSize, Qt::KeepAspectRatio );

		int wdiff = (w - camSize.width());
		int hdiff = (h - camSize.height());

		ui.lbCameraImage->installEventFilter( this );

		camSdk.SetPreviewWindow(winId(), wdiff/2, hdiff/2, width() - wdiff, height() - hdiff);
		//camSdk.SetPreviewWindow(NULL, 0, 0, camSdk.Width(), camSdk.Height());
		camSdk.Preview();
		//camSdk.Capture();

		connect(threadView, SIGNAL(update()), this, SLOT(Update()));
		threadView->start();
	}
	setLineWidth(1);
	setMidLineWidth(1);
	setFrameStyle(Shape::Box | Shadow::Sunken);

	//QLabel *testLabel = new QLabel();
	//testLabel->resize(500, 500);
	//testLabel->show();

	//previewLabel = testLabel;

	//camSdk.StopPreview();
}

LiveCameraArtCam_035IMX_WOM::~LiveCameraArtCam_035IMX_WOM()
{
	camSdk.Release();
	camSdk.FreeLibrary();
	
	if(cameraImageBuff){
		delete []cameraImageBuff;
		cameraImageBuff = NULL;
		cameraImageBuffSize = 0;
	}
}

bool LiveCameraArtCam_035IMX_WOM::eventFilter(QObject *obj, QEvent *event)
{
	if(obj==ui.lbCameraImage){
		QMouseEvent *mevent = dynamic_cast<QMouseEvent*>(event);
		if(mevent!=NULL){
			if(event->type()==QEvent::MouseButtonPress){
				mousePressEvent(mevent);
				return true;
			}else if(event->type()==QEvent::MouseButtonRelease){
				mouseReleaseEvent(mevent);
				return true;
			}else if(event->type()==QEvent::MouseMove){
				mouseMoveEvent(mevent);
				return true;
			}
		}
	}
	return GUIFormBase::eventFilter(obj, event);
}

void LiveCameraArtCam_035IMX_WOM::Update()
{
	threadView->setUpdateEnable(false);
	long currentCameraImageBuffSize = camSdk.Width() * camSdk.Height() * 3;
	if(currentCameraImageBuffSize!=cameraImageBuffSize){
		if(cameraImageBuff){
			delete []cameraImageBuff;
		}

		cameraImageBuff = new BYTE[currentCameraImageBuffSize];
		cameraImageBuffSize = currentCameraImageBuffSize;
	}


	if(previewLabel==NULL || previewLabel==ui.lbCameraImage){
		//camSdk.GetImage( cameraImageBuff, cameraImageBuffSize, TRUE);
		////camSdk.SnapShot( cameraImageBuff, cameraImageBuffSize, TRUE);

		//const int w = camSdk.Width();
		//const int h = camSdk.Height();
		//
		//QImage img(w, h, QImage::Format_RGB32);

		//if(img.isNull()==false){
		//	for(int y=0; y<h; y++){
		//		uchar *line = img.scanLine(y);
		//		QRgb *rgbLine = (QRgb*)line;
		//		for(int x=0; x<w; x++){
		//			BYTE *base = cameraImageBuff + (x + y*camSdk.Width())*3;
		//			rgbLine[x] = qRgb(base[2], base[1], base[0]);
		//		}
		//		if(y/400==0){
		//			//qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		//		}
		//	}
		//	if(previewLabel==NULL){
		//		ui.lbCameraImage->setPixmap( QPixmap::fromImage( img.scaled( ui.lbCameraImage->size(), Qt::KeepAspectRatio) ) );
		//	}else{
		//		previewLabel->setPixmap( QPixmap::fromImage( img.scaled( previewLabel->size(), Qt::KeepAspectRatio) ) );
		//	}
		//	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		//}
	}else if(previewLabel->isVisible()==true){
		camSdk.GetImage( cameraImageBuff, cameraImageBuffSize, TRUE);

		const int w = camSdk.Width();
		const int h = camSdk.Height();
		
		QImage img(w, h, QImage::Format_RGB32);

		if(img.isNull()==false){
			#pragma omp for
			for(int y=0; y<h; y++){
				uchar *line = img.scanLine(y);
				QRgb *rgbLine = (QRgb*)line;
				for(int x=0; x<w; x++){
					BYTE *base = cameraImageBuff + (x + y*camSdk.Width())*3;
					rgbLine[x] = qRgb(base[2], base[1], base[0]);
				}
				if(y/400==0){
					//qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
				}
			}

			previewLabel->setPixmap( QPixmap::fromImage( img ).scaled( previewLabel->size(), Qt::KeepAspectRatio) );
			//qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	threadView->setUpdateEnable(true);
}

void LiveCameraArtCam_035IMX_WOM::TransmitDirectly(GUIDirectMessage *packet){
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	GUICmdSetCameraWindow *GUICmdSetCameraWindowVar = dynamic_cast<GUICmdSetCameraWindow *>(packet);
	if(GUICmdSetCameraWindowVar!=NULL){
		threadView->setUpdateEnable(false);
		//camSdk.StopPreview();
		//camSdk.Close();

		previewLabel = GUICmdSetCameraWindowVar->label;

		//QSize s = GUICmdSetCameraWindowVar->label->size();
		//QSize c(camSdk.Width(), camSdk.Height());

		//c.scale( s, Qt::KeepAspectRatio );

		//camSdk.SetPreviewWindow(GUICmdSetCameraWindowVar->label->winId(), 0, 0, c.width(), c.height());

		//camSdk.StartPreview();

		//ui.AreaCameraView->changePaintLabel(GUICmdSetCameraWindowVar->label);
		GUICmdSetCameraWindowVar->ret = true;
		threadView->setUpdateEnable(true);
		return;
	}

	GUICmdResetCameraWindow *GUICmdResetCameraWindowVar = dynamic_cast<GUICmdResetCameraWindow *>(packet);
	if(GUICmdResetCameraWindowVar!=NULL){
		threadView->setUpdateEnable(false);
		//camSdk.StopPreview();
		//camSdk.Close();

		previewLabel = ui.lbCameraImage;
		
		//int w = width();
		//int h = height();

		//QSize winSize = size();
		//QSize camSize( camSdk.Width(), camSdk.Height() );

		//camSize.scale( winSize, Qt::KeepAspectRatio );

		//int wdiff = (w - camSize.width());
		//int hdiff = (h - camSize.height());

		//camSdk.SetPreviewWindow(winId(), wdiff/2, hdiff/2, width() - wdiff, height() - hdiff);
		//camSdk.StartPreview();

		////ui.AreaCameraView->changePaintLabel(NULL);
		GUICmdResetCameraWindowVar->ret = true;
		threadView->setUpdateEnable(true);
		return;
	}
	GUICmdReqCamSize	*GUICmdReqCamSizeVar=dynamic_cast<GUICmdReqCamSize *>(packet);
	if(GUICmdReqCamSizeVar!=NULL){
		GUICmdReqCamSizeVar->Width=camSdk.Width();
		GUICmdReqCamSizeVar->Height=camSdk.Height();
		return;
	}
}

void LiveCameraArtCam_035IMX_WOM::mousePressEvent(QMouseEvent *event)
{
	GUIFormBase::mousePressEvent(event);
	
	if(GetEditMode()==true){
		return;
	}

	if((event->buttons() & Qt::MouseButton::RightButton)!=0){
		if(GetEditMode()==false){
			threadView->setIntervalTime( 200 );
			camSdk.SetImageDlg(winId());
			threadView->setIntervalTime( 100 );

			camSdk.Close();
			camSdk.Release();

			camSdk.Initialize(NULL);
			//camSdk.Capture();
			
			int w = width();
			int h = height();

			QSize winSize = size();
			QSize camSize( camSdk.Width(), camSdk.Height() );

			camSize.scale( winSize, Qt::KeepAspectRatio );

			int wdiff = (w - camSize.width());
			int hdiff = (h - camSize.height());

			camSdk.SetPreviewWindow(winId(), wdiff/2, hdiff/2, width() - wdiff, height() - hdiff);
			camSdk.Preview();

			//camSdk.StopPreview();
			//camSdk.Close();
			//camSdk.Release();
			//camSdk.FreeLibrary();

			//camSdk.Initialize(winId());
			//camSdk.SetPreviewWindow(winId(), 0, 0, width(), height());
			//camSdk.StartPreview();

			//ui.AreaCameraView->setVisible(false);
			//ui.AreaCameraView->update();
			//ui.AreaCameraView->show();
		}
		return;
	}

	if((event->buttons() & Qt::MouseButton::LeftButton)==0){
		return;
	}
	
	AlgorithmBase *RBase = GetReviewAlgorithmBase();
	if(RBase==NULL){
		return;
	}

	qreal x,y;
	
	QSize s = size();
	QSize c(camSdk.Width(), camSdk.Height());

	c.scale( s, Qt::KeepAspectRatio );
	
	//QSize pixSize = ui.AreaCameraView->pixmap()->size();
	QSize pixSize = c;
	qreal x_rate = event->pos().x() / (qreal)pixSize.width();
	qreal y_rate = event->pos().y() / (qreal)pixSize.height();

	x = 2*x_rate - 1;
	y = 2*y_rate - 1;

	CmdMoveVRSOnCameraView moveVRS(GetLayersBase());

	moveVRS.x = x;
	moveVRS.y = y;

	RBase->TransmitDirectly( &moveVRS );
}

void LiveCameraArtCam_035IMX_WOM::updateGUI()
{
	GUIFormBase::update();
	//camSdk.StopPreview();
	//camSdk.StartPreview();
	//ui.AreaCameraView->StopLive();
	//ui.AreaCameraView->StartLive();
}

void LiveCameraArtCam_035IMX_WOM::ResizeAction()
{
	if(GetEditMode()==false){
		threadView->setUpdateEnable(false);
		//ui.AreaCameraView->Resize();
		//camSdk.StopPreview();
		camSdk.Close();
		
		int w = width();
		int h = height();

		QSize winSize = size();
		QSize camSize( camSdk.Width(), camSdk.Height() );

		camSize.scale( winSize, Qt::KeepAspectRatio );

		int wdiff = (w - camSize.width());
		int hdiff = (h - camSize.height());

		camSdk.SetPreviewWindow(winId(), wdiff/2, hdiff/2, width() - wdiff, height() - hdiff);

		camSdk.Preview();
		//camSdk.Capture();
		threadView->setUpdateEnable(true);
	}

	setLineWidth(1);
	setMidLineWidth(1);
	setFrameStyle(Shape::Box | Shadow::Sunken);
}
