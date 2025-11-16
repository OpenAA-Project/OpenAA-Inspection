#include "LiveCameraDFK31AF03Resource.h"
//////////////////////////////////////////////////////////////////////
// Listener.cpp: implementation of the CListener class.
//
//////////////////////////////////////////////////////////////////////

#include "Listener.h"

BYTE	Clip255(int d);

namespace DShowLib{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListener::CListener()
{
	m_dPlusRed = m_dPlusGreen = m_dPlusBlue = 0;
}

//////////////////////////////////////////////////////////////////////////

CListener::~CListener() 
{
}

//////////////////////////////////////////////////////////////////////////

void CListener::SetParent( HDC *pParent)
{
}

//////////////////////////////////////////////////////////////////////////
// Notify parent, device is lost.
//////////////////////////////////////////////////////////////////////////

void CListener::deviceLost( Grabber& param) 
{
}

//////////////////////////////////////////////////////////////////////////
// Callback handler.
//////////////////////////////////////////////////////////////////////////

void CListener::frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
{
	pBuffer->lock();
	DoImageProcessing( pBuffer );
	pBuffer->unlock();
}

//////////////////////////////////////////////////////////////////////////
// The image processing is done here. For the sake of simplicity, the
// image data is inverted by this sample code.
//////////////////////////////////////////////////////////////////////////

void CListener::DoImageProcessing(smart_ptr<MemBuffer> pBuffer)
{
	//// Get the bitmap info header from the membuffer. It contains the bits per pixel,
	//// width and height.
	//smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

	//// Now retrieve a pointer to the image. For organization of the image data, please
	//// refer to:
	//// http://www.imagingcontrol.com/ic/docs/html/class/Pixelformat.htm

	////BYTE* pImageData = pBuffer->getPtr();
	//RGB24Pixel* pImageData = (RGB24Pixel*)pBuffer->getPtr();

	//// Calculate the size of the image.
	//int bufSize = sizeof(RGB24Pixel);
	//int iImageSize = pInf->biWidth * pInf->biHeight * pInf->biBitCount / 8 / bufSize;

	//// Now loop through the data and change every byte. This small sample inverts every pixel.
	//#pragma omp parallel
	//{
	//#pragma omp for
	//for(int i=0; i < iImageSize; i++){
	//	Clip255( pImageData[i].r + m_dPlusRed + 200 );
	//	Clip255( pImageData[i].g + m_dPlusGreen + 200 );
	//	Clip255( pImageData[i].b + m_dPlusBlue + 200 );
	//}
	//}
}

void CListener::setPlusRGB(int r, int g, int b)
{
	m_dPlusRed = r;
	m_dPlusGreen = g;
	m_dPlusBlue = b;
}

}