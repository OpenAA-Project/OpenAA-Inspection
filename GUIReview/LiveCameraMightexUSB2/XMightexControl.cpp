#include "LiveCameraMightexUSB2Resource.h"
#include "XMightexControl.h"
#include "XGeneralFunc.h"
#include <QImage>
#include "swap.h"

MightexCameraContainer	*CameraList;

CameraItem::CameraItem(QObject *parent)
{
	m_gainR=20;
	m_gainG=20;
	m_gainB=20;
	m_exposureTime	=100;
	m_grabberState	=stL_Idle;
	m_resolution	=8;
	m_frameMem		=NULL;
	m_frameSize		=0;
	m_isTriggerMode	=false;
	m_isEnable		=true;
	m_Gamma			=0.0;
	Img				=NULL;
}
void CameraItem::setProcessedDataProperty(const TProcessedDataProperty &prop)
{ 
	m_processedDataProperty = prop;
}

const TProcessedDataProperty &CameraItem::processedDataProperty() const
{ 
	return m_processedDataProperty;
}

TProcessedDataProperty &CameraItem::processedDataProperty()
{ 
	return m_processedDataProperty;
}

void CameraItem::resetGrabberState()	{	setGrabberState(stL_Idle);		};

void CameraItem::startGrabber()			{	setGrabberState(stL_Grabber);	};

void CameraItem::endGrabber()			{	setGrabberState(stL_GrabEnd);	};

bool CameraItem::setResolution(int index)
{
	if(index<1 || 11<index){
		return false;
	}
	m_resolution = index;
	if(isEnable()==false){
		if(frameMem()){
			delete frameMem();
			_setFrameMem(0);
		}
		_setFrameSize(0);
		return true;
	}

	int headerSize = 14*sizeof(int);
	int frameSize_;
	/* Index Resolution Decimision Max Buffer Count(8bit Camera)
	* 1 64x64 None 23
	* 2 160x120 None 23
	*			1:2 23
	* 3 320x240 None 23
	*			1:2 23
	* 4 640x480 None 23
	*			1:2 23
	* 5 752x480 None 23
	*			1:2 23
	* 6 800x600 None 23
	*			1:2 23
	* 7 1024x768 None 23
	*			1:2 23
	* 8 1280x1024 None 23
	*			1:2 23
	* 9 1600x1200 None 6
	*			1:2 12
	* 10 2048x1536 None 4
	*			1:2 8
	* 11 2592 x1944 None 3
	*			1:2 8
	*/
	if(Img!=NULL)
		delete	Img;
	switch(index){
	case 1:
		frameSize_ = 64*64;
		Img=new QImage(64,64,QImage::Format_RGB32);
		break;
	case 2:
		frameSize_ = 160*120;
		Img=new QImage(160,120,QImage::Format_RGB32);
		break;
	case 3:
		frameSize_ = 320*240;
		Img=new QImage(320,240,QImage::Format_RGB32);
		break;
	case 4:
		frameSize_ = 640*480;
		Img=new QImage(640,480,QImage::Format_RGB32);
		break;
	case 5:
		frameSize_ = 752*480;
		Img=new QImage(752,480,QImage::Format_RGB32);
		break;
	case 6:
		frameSize_ = 800*600;
		Img=new QImage(800,600,QImage::Format_RGB32);
		break;
	case 7:
		frameSize_ = 1024*768;
		Img=new QImage(1024,768,QImage::Format_RGB32);
		break;
	case 8:
		frameSize_ = 1280*960;
		Img=new QImage(1280,960,QImage::Format_RGB32);
		break;
	case 9:
		frameSize_ = 1600*1200;
		Img=new QImage(1600,1200,QImage::Format_RGB32);
		break;
	case 10:
		frameSize_ = 2048*1536;
		Img=new QImage(2048,1536,QImage::Format_RGB32);
		break;
	case 11:
		frameSize_ = 2592*1944;
		Img=new QImage(2592,1944,QImage::Format_RGB32);
		break;
	default:
		return false;
		break;
	}
	frameSize_=frameSize_*3;
	unsigned char *ptr = new unsigned char[frameSize_];
	if(ptr==0){
		return false;
	}
	memset(ptr, 0, frameSize_);

	if(frameMem()){
		delete frameMem();
		_setFrameMem(0);
	}

	_setFrameMem(ptr);
	_setFrameSize(frameSize_);

	return true;
};
void	CameraItem::setGamma(double val)
{
	m_Gamma=val;

	if(m_Gamma<=0.0){
		for(int i=0;i<256;i++){
			GammaTable[i]=i;
		}
	}
	else{
		double	MaxLog=log(256*m_Gamma);
		for(int i=0;i<256;i++){
			if(i==0)
				GammaTable[i]=0;
			else{
				double	v=log(i*m_Gamma)/MaxLog*256.0;
				if(v<0)
					v=0;
				if(v>=255)
					v=255;
				
				GammaTable[i]=v;
			}
		}
	}
}

bool	CameraItem::Save(QIODevice *f)
{
	if(::Save(f,m_gainR)==false)
		return false;
	if(::Save(f,m_gainG)==false)
		return false;
	if(::Save(f,m_gainB)==false)
		return false;
	if(::Save(f,m_exposureTime)==false)
		return false;
	if(::Save(f,m_moduleNo)==false)
		return false;
	if(::Save(f,m_serialNo)==false)
		return false;
	if(::Save(f,m_resolution)==false)
		return false;
	if(::Save(f,m_isTriggerMode)==false)
		return false;
	if(::Save(f,m_isEnable)==false)
		return false;
	if(::Save(f,m_Gamma)==false)
		return false;
	return true;
}

bool	CameraItem::Load(QIODevice *f)
{
	if(::Load(f,m_gainR)==false)
		return false;
	if(::Load(f,m_gainG)==false)
		return false;
	if(::Load(f,m_gainB)==false)
		return false;
	if(::Load(f,m_exposureTime)==false)
		return false;
	if(::Load(f,m_moduleNo)==false)
		return false;
	if(::Load(f,m_serialNo)==false)
		return false;
	if(::Load(f,m_resolution)==false)
		return false;
	if(::Load(f,m_isTriggerMode)==false)
		return false;
	if(::Load(f,m_isEnable)==false)
		return false;
	if(::Load(f,m_Gamma)==false)
		return false;

	setGainR(m_gainR);
	setGainG(m_gainG);
	setGainB(m_gainB);
	setExposureTime(m_exposureTime);
	setResolution(m_resolution);
	setTriggerMode(m_isTriggerMode);
	setEnable(m_isEnable);
	setGamma(m_Gamma);

	return true;
}

// must bmp buffer size is over bayer length*3
bool CameraItem::bayerToBMP(const unsigned char *bayer, unsigned char *bmp, int width, int height)
{
	if(bayer==NULL || bmp==NULL || width<=0 || height<=0){
		return false;
	}

	//QImage image(width, height, QImage::Format_RGB32);
	//image.fill(0);
	
	// 輪郭部

	// 角部
	// y==0
	{
		// x==0
		// G R G R G R <-左上
		// B G B G B G
		// G R G R G R
		// B G B G B G
		const unsigned int center		= *(bayer);
		const unsigned int right		= *(bayer + 1);
		const unsigned int bottom		= *(bayer + width);
		const unsigned int bottomRight	= *(bayer + width + 1);

		const int r = right;
		const int g = ((int)center + bottomRight)/2;
		const int b = bottom;

		QRgb pic = qRgb(r, g, b);

		*bmp = qRed(pic);
		*(bmp+1) = qGreen(pic);
		*(bmp+2) = qBlue(pic);

		//image.setPixel(0, 0, pic);
	}
	{
		// x==width-1
		// G R G R G R <-右上
		// B G B G B G
		// G R G R G R
		// B G B G B G
		const int startIndex = width - 1;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int left			= *(bayer + startIndex - 1);
		const unsigned int bottom		= *(bayer + startIndex + width);
		const unsigned int bottomLeft	= *(bayer + startIndex + width - 1);

		const int r = center;
		const int g = ((int)left + bottom)/2;
		const int b = bottomLeft;

		QRgb pic = qRgb(r, g, b);

		*(bmp + startIndex*3) = qRed(pic);
		*(bmp + startIndex*3 + 1) = qGreen(pic);
		*(bmp + startIndex*3 + 2) = qBlue(pic);

		//image.setPixel(width-1, 0, pic);
	}
	// y==height-1
	{
		// x==0
		// G R G R G R
		// B G B G B G
		// G R G R G R
		// B G B G B G <-左下
		const int startIndex = (height-1)*width;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int right		= *(bayer + startIndex + 1);
		const unsigned int top			= *(bayer + startIndex - width);
		const unsigned int topRight		= *(bayer + startIndex - width + 1);

		const int r = topRight;
		const int g = ((int)top + right)/2;
		const int b = center;

		QRgb pic = qRgb(r, g, b);

		*(bmp + startIndex*3) = qRed(pic);
		*(bmp + startIndex*3 + 1) = qGreen(pic);
		*(bmp + startIndex*3 + 2) = qBlue(pic);

		//image.setPixel(0, height-1, pic);
	}
	// y==height-1
	{
		// x==width-1
		// G R G R G R
		// B G B G B G
		// G R G R G R
		// B G B G B G <-右下
		const int startIndex = height*width - 1;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int left			= *(bayer + startIndex - 1);
		const unsigned int top			= *(bayer + startIndex - width);
		const unsigned int topLeft		= *(bayer + startIndex - width - 1);

		const int r = top;
		const int g = ((int)center + topLeft)/2;
		const int b = left;

		QRgb pic = qRgb(r, g, b);

		*(bmp + startIndex*3) = qRed(pic);
		*(bmp + startIndex*3 + 1) = qGreen(pic);
		*(bmp + startIndex*3 + 2) = qBlue(pic);

		//image.setPixel(width-1, height-1, pic);
	}

	// 上部
	// y==0, x=1~width-1
	for(int x=1; x<width-1; x++){
		// G R G R G R <-
		// B G B G B G
		// G R G R G R
		// B G B G B G
		const unsigned int center		= *(bayer + x);
		const unsigned int left			= *(bayer + x - 1);
		const unsigned int right		= *(bayer + x + 1);
		const unsigned int bottom		= *(bayer + x + width);
		const unsigned int bottomLeft	= *(bayer + x + width - 1);
		const unsigned int bottomRight	= *(bayer + x + width + 1);
		
		QRgb pic;
		if((x%2)==0){
			const int r = ((int)left + right)/2;
			const int g = center;
			const int b = bottom;

			pic = qRgb(r, g, b);
		}else{
			const int r = center;
			const int g = ((int)left + right + bottom)/3;
			const int b = ((int)bottomLeft + bottomRight)/2;

			pic = qRgb(r, g, b);
		}

		*(bmp + x*3)		= qRed(pic);
		*(bmp + x*3 + 1)	= qGreen(pic);
		*(bmp + x*3 + 2)	= qBlue(pic);
		
		//image.setPixel(x, 0, pic);
	}
	
	// 下部
	for(int x=1; x<width-1; x++){
		int startIndex = (height - 1)*width;
		// G R G R G R
		// B G B G B G
		// G R G R G R
		// B G B G B G <-
		const unsigned int center		= *(bayer + startIndex + x);
		const unsigned int top			= *(bayer + startIndex + x - width);
		const unsigned int topLeft		= *(bayer + startIndex + x - width - 1);
		const unsigned int topRight		= *(bayer + startIndex + x - width + 1);
		const unsigned int left			= *(bayer + startIndex + x - 1);
		const unsigned int right		= *(bayer + startIndex + x + 1);
		
		QRgb pic;
		if((x%2)==0){
			const int r = ((int)topLeft + topRight)/2;
			const int g = ((int)left + top + right)/3;
			const int b = center;

			pic = qRgb(r, g, b);
		}else{
			const int r = top;
			const int g = ((int)topLeft + topRight)/2;
			const int b = ((int)left + right)/2;

			pic = qRgb(r, g, b);
		}

		*(bmp + (startIndex + x)*3)		= qRed(pic);
		*(bmp + (startIndex + x)*3 + 1)	= qGreen(pic);
		*(bmp + (startIndex + x)*3 + 2)	= qBlue(pic);
		
		//image.setPixel(x, height-1, pic);
	}
	
	// 左部
	for(int y=1; y<height-1; y++){
		// G R G R G R
		// B G B G B G <-左?
		// G R G R G R <-左?
		// B G B G B G

		int startIndex = y*width;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int top			= *(bayer + startIndex - width);
		const unsigned int topRight		= *(bayer + startIndex - width + 1);
		const unsigned int right		= *(bayer + startIndex + 1);
		const unsigned int bottom		= *(bayer + startIndex + width);
		const unsigned int bottomRight	= *(bayer + startIndex + width + 1);
		
		QRgb pic;
		if((y%2)==0){
			const int r = right;
			const int g = ((int)center + topRight + bottomRight)/3;
			const int b = ((int)top + bottom)/2;

			pic = qRgb(r, g, b);
		}else{
			const int r = ((int)topRight + bottomRight)/2;
			const int g = ((int)top + right + bottom)/3;
			const int b = center;

			pic = qRgb(r, g, b);
		}

		*(bmp + startIndex*3)		= qRed(pic);
		*(bmp + startIndex*3 + 1)	= qGreen(pic);
		*(bmp + startIndex*3 + 2)	= qBlue(pic);

		//qDebug() << qRed(pic) << "," << qGreen(pic) << "," << qBlue(pic);
	}

	// 右部
	for(int y=1; y<height-1; y++){
		// G R G R G R
		// B G B G B G <-右?
		// G R G R G R <-右?
		// B G B G B G

		int startIndex = y*width - 1;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int top			= *(bayer + startIndex - width);
		const unsigned int topLeft		= *(bayer + startIndex - width - 1);
		const unsigned int left			= *(bayer + startIndex - 1);
		const unsigned int bottom		= *(bayer + startIndex + width);
		const unsigned int bottomLeft	= *(bayer + startIndex + width - 1);
		
		QRgb pic;
		if((y%2)==0){
			const int r = center;
			const int g = ((int)top + left + bottom)/3;
			const int b = ((int)topLeft + bottomLeft)/2;

			pic = qRgb(r, g, b);
		}else{
			const int r = ((int)top + bottom)/2;
			const int g = ((int)center + topLeft + bottomLeft)/3;
			const int b = left;

			pic = qRgb(r, g, b);
		}

		*(bmp + startIndex*3)		= qRed(pic);
		*(bmp + startIndex*3 + 1)	= qGreen(pic);
		*(bmp + startIndex*3 + 2)	= qBlue(pic);
		
		//image.setPixel(width-1, y, pic);
	}

	// y=1~height-1, x==0
	for(int y=1; y<height-1; y++){
		const int startIndex = y*width;
		const unsigned int center		= *(bayer + startIndex);
		const unsigned int top			= *(bayer + startIndex - width);
		const unsigned int topRight		= *(bayer + startIndex - width + 1);
		const unsigned int right		= *(bayer + startIndex + 1);
		const unsigned int bottom		= *(bayer + startIndex + width);
		const unsigned int bottomRight	= *(bayer + startIndex + width + 1);
		
		QRgb pic;
		if((y%2)==0){
			const int r = ((int)top + bottom)/2;
			const int g = center;
			const int b = right;

			pic = qRgb(r, g, b);
		}else{
			const int r = center;
			const int g = ((int)top + bottom + right)/3;
			const int b = ((int)topRight + bottomRight)/2;

			pic = qRgb(r, g, b);
		}

		*(bmp + startIndex*3)		= qRed(pic);
		*(bmp + startIndex*3 + 1)	= qGreen(pic);
		*(bmp + startIndex*3 + 2)	= qBlue(pic);

		//image.setPixel(0, y, pic);
	}

	for(int y=1; y<height-1; y++){
		const int startIndex = y*width;
		if((y%2)==0){
			// G R G R G R <-
			// B G B G B G
			// G R G R G R <-
			// B G B G B G
			for(int x=1; x<width-1; x++){
				const unsigned int center		= *(bayer + startIndex + x);
				const unsigned int top			= *(bayer + startIndex + x - width);
				const unsigned int topLeft		= *(bayer + startIndex + x - width - 1);
				const unsigned int topRight		= *(bayer + startIndex + x - width + 1);
				const unsigned int left			= *(bayer + startIndex + x - 1);
				const unsigned int right		= *(bayer + startIndex + x + 1);
				const unsigned int bottom		= *(bayer + startIndex + x + width);
				const unsigned int bottomLeft	= *(bayer + startIndex + x + width - 1);
				const unsigned int bottomRight	= *(bayer + startIndex + x + width + 1);
				QRgb pic;
				if((x%2)==0){
					const int r = ((int)right + left)/2;
					const int g = center;
					const int b = ((int)top + bottom)/2;

					pic = qRgb(r, g, b);
				}else{
					const int r = center;
					const int g = ((int)right + bottom + top + bottom)/4;
					const int b = ((int)topLeft + topRight + bottomLeft + bottomRight)/4;

					pic = qRgb(r, g, b);
				}
				*(bmp + (startIndex + x)*3)		= qRed(pic);
				*(bmp + (startIndex + x)*3 + 1)	= qGreen(pic);
				*(bmp + (startIndex + x)*3 + 2)	= qBlue(pic);
				//image.setPixel(x, y, pic);
			}
		}else{
			// G R G R G R
			// B G B G B G <-
			// G R G R G R
			// B G B G B G <-
			for(int x=1; x<width-1; x++){
				const unsigned int center		= *(bayer + startIndex + x);
				const unsigned int top			= *(bayer + startIndex + x - width);
				const unsigned int topLeft		= *(bayer + startIndex + x - width - 1);
				const unsigned int topRight		= *(bayer + startIndex + x - width + 1);
				const unsigned int left			= *(bayer + startIndex + x - 1);
				const unsigned int right		= *(bayer + startIndex + x + 1);
				const unsigned int bottom		= *(bayer + startIndex + x + width);
				const unsigned int bottomLeft	= *(bayer + startIndex + x + width - 1);
				const unsigned int bottomRight	= *(bayer + startIndex + x + width + 1);
				
				QRgb pic;
				if((x%2)==0){
					
					const int r = ((int)topLeft + topRight + bottomLeft + bottomRight)/4;
					const int g = ((int)top + bottom + left + right)/4;
					const int b = center;

					pic = qRgb(r, g, b);
				}else{
					const int r = ((int)top + bottom)/2;
					const int g = center;
					const int b = ((int)left + right)/2;

					pic = qRgb(r, g, b);
				}
				
				*(bmp + (startIndex + x)*3)		= qRed(pic);
				*(bmp + (startIndex + x)*3 + 1)	= qGreen(pic);
				*(bmp + (startIndex + x)*3 + 2)	= qBlue(pic);

				//image.setPixel(x, y, pic);
			}
		}
	}

	//image.save("Test.bmp");

	return true;
}

void	CameraItem::MakeImage(void)
{
	const int row = min(processedDataProperty().Row,Img->height());
	const int column = min(processedDataProperty().Column,Img->width());

	#pragma omp parallel for
	for(int y=0; y<row; y++){
		int startIndex = y*column*3;
		int32	*dest=(int32 *)Img->scanLine(y);
		int currentIndex=startIndex;
		for(int x=0; x<column; x++){
			dest[x] = 0xFF000000 + (*(m_frameMem + currentIndex+2)<<16)
								 + (*(m_frameMem + currentIndex+1)<<8)
								 + (*(m_frameMem + currentIndex+0));
			currentIndex+=3;
		}
	}
}

CameraItem	&CameraItem::operator=(CameraItem &src)
{
	m_gainR					=src.m_gainR;
	m_gainG					=src.m_gainG;
	m_gainB					=src.m_gainB;
	m_exposureTime			=src.m_exposureTime;
	m_grabberState			=src.m_grabberState;
	m_processedDataProperty	=src.m_processedDataProperty;
	m_resolution			=src.m_resolution;
	m_frameSize				=src.m_frameSize;
	m_isTriggerMode			=src.m_isTriggerMode;
	m_isEnable				=src.m_isEnable;
	m_Gamma					=src.m_Gamma;

	setResolution(m_resolution);
	return *this;
}

CameraItem	&CameraItem::operator=(const CameraItem &src)
{
	m_gainR					=src.m_gainR;
	m_gainG					=src.m_gainG;
	m_gainB					=src.m_gainB;
	m_exposureTime			=src.m_exposureTime;
	m_grabberState			=src.m_grabberState;
	m_processedDataProperty	=src.m_processedDataProperty;
	m_resolution			=src.m_resolution;
	m_frameSize				=src.m_frameSize;
	m_isTriggerMode			=src.m_isTriggerMode;
	m_isEnable				=src.m_isEnable;
	m_Gamma					=src.m_Gamma;

	setResolution(m_resolution);
	return *this;
}

void	CameraItem::CommandDraw(void)
{
	emit	SignalDraw();
}
//=========================================================================

MightexCameraContainer::MightexCameraContainer(QWidget *parent)	
{	
	Parent=parent;
	m_grabberState=stG_Idle;
}
MightexCameraContainer::~MightexCameraContainer()
{}

int MightexCameraContainer::deviceNumb()	
{ 
	return GetCount();
};

bool MightexCameraContainer::hasDeviceID(int id)
{
	if(id<=0){
		return false;
	}
	int	N=GetCount();
	return (id<=(int)N);
}
bool MightexCameraContainer::hasDeviceHandle(Qt::HANDLE handle)
{
	return hasDeviceID((int)handle);
}
	
CameraItem &MightexCameraContainer::fromDeviceID(int id)
{ 
	return *GetItem(id-1);
}

void MightexCameraContainer::setData(int deviceID, const CameraItem &data)
{
	if(hasDeviceID(deviceID)==true){
		*GetItem(deviceID-1) = data;
	}
}

void MightexCameraContainer::setSavedData(int deviceID, const CameraItem &data)
{
	if(hasDeviceID(deviceID)==true){
		GetItem(deviceID-1)->setExposureTime( data.exposureTime() );
		GetItem(deviceID-1)->setGainR( data.gainR() );
		GetItem(deviceID-1)->setGainG( data.gainG() );
		GetItem(deviceID-1)->setGainB( data.gainB() );
		GetItem(deviceID-1)->setTriggerMode( data.isTriggerMode() );
	}
}

void MightexCameraContainer::setGrabberState(int deviceID, LocalGrabberState state)
{
	if(hasDeviceID(deviceID)==false){
		return;
	}

	fromDeviceID(deviceID).setGrabberState(state);
}

void MightexCameraContainer::resetGrabber(int deviceID)
{
	setGrabberState(deviceID, stL_Idle);
}
void MightexCameraContainer::startGrabber(int deviceID)
{
	setGrabberState(deviceID, stL_Grabber);
}
void MightexCameraContainer::endGrabber(int deviceID)
{
	setGrabberState(deviceID, stL_GrabEnd);
}

bool MightexCameraContainer::isCameraGrabber() const
{
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->grabberState()>=stL_Grabber){
			return true;
		}
	}
	return false;
}

int MightexCameraContainer::enableCameraCount() const
{
	int cnt=0;
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->isEnable()==true){
			cnt++;
		}
	}
	return cnt;
}

int MightexCameraContainer::grabberCameraCount() const
{
	int cnt=0;
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->grabberState()==stL_Grabber){
			cnt++;
		}
	}
	return cnt;
}

void MightexCameraContainer::setGrabberState(GlobalGrabberState state)
{ 
	m_grabberState = state;
}
GlobalGrabberState MightexCameraContainer::grabberState() const 
{ 
	return m_grabberState;
}
void MightexCameraContainer::startGrabber()
{ 
	setGrabberState(stG_Grabber); 
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->setGrabberState(stL_Grabber);
	}
}
void MightexCameraContainer::stopGrabber()
{ 
	setGrabberState(stG_Idle);
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->setGrabberState(stL_Idle);
	}
}
bool MightexCameraContainer::isGrabber() const
{ 
	return (grabberState()==stG_Grabber);
}

bool	MightexCameraContainer::Save(QIODevice *f)
{
	int32	N=CameraList->GetCount();
	if(::Save(f,N)==false)
		return false;
	for(CameraItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	MightexCameraContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		CameraItem	*a=GetItem(i);
		if(a==NULL){
			a=new CameraItem(Parent);
			AppendList(a);
		}
		if(a->Load(f)==false){
			return false;
		}
	}
	return true;
}

