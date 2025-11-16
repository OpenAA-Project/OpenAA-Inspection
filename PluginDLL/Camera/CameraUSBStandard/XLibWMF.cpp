#include "XLibWMF.h"
#include "LibWMFCamera.h"
#include <stdlib.h>
#include <Vidcap.h>
#include <QIODevice>
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XCameraCommon.h"
#include "CameraUSBStandard.h"
#include <dshow.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfobjects.h>
#include <mfreadwrite.h>
#include <ks.h>
#include <ksmedia.h>
#include <ksproxy.h>
#include <dshow.h>

static	int	StrHexToInt(char c)
{
	switch(c){
	case '0':	return 0;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':	return 0x0a;
	case 'a':	return 0x0a;
	case 'B':	return 0x0b;
	case 'b':	return 0x0b;
	case 'C':	return 0x0c;
	case 'c':	return 0x0c;
	case 'D':	return 0x0d;
	case 'd':	return 0x0d;
	case 'E':	return 0x0e;
	case 'e':	return 0x0e;
	case 'F':	return 0x0f;
	case 'f':	return 0x0f;
	default:	return -1;
	}
}
bool	InitialUVCSystem(void)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) return false;

	hr = MFStartup(MF_VERSION);
	if (FAILED(hr)) return false;

	return true;
}
int	GetDeviceCount(struct DeviceInfo hDevDim[100],QStringList &CameraNameList)
{
	HRESULT hr;
	// choose device
	IMFAttributes *attributes = NULL;
	hr = MFCreateAttributes(&attributes, 1);
	ScopedRelease<IMFAttributes> attributes_s(attributes);

	if (FAILED(hr)) return 0;

	hr = attributes->SetGUID(
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
		);
	if (FAILED(hr)) return 0;

	ChooseDeviceParam param = { 0 };
	hr = MFEnumDeviceSources(attributes, &param.mDevices, &param.mCount);

	if (FAILED(hr)) return 0;

	for(int r=0;r<param.mCount && r<100;r++){

		WCHAR* buffer = nullptr;
		UINT32 length = 0;
		hr = param.mDevices[r]->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &buffer, &length);
		if(FAILED(hr)){
			hr = S_OK;
			CameraNameList.append(/**/"");
			continue;
		}
		char DeviceName[100000];
		memset(DeviceName,0,sizeof(DeviceName));
		wcstombs(DeviceName, buffer, sizeof(DeviceName));
		strcpy(hDevDim[r].DeviceName,DeviceName);

		CameraNameList.append(DeviceName);

		WCHAR* symLinkWCStr = nullptr;
		UINT32 symLinkLength = 0;
		hr = param.mDevices[r]->GetAllocatedString(
                    MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, &symLinkWCStr, &symLinkLength);
		if(FAILED(hr)){
			hr = S_OK;
			continue;
		}
		char DevicePathName[100000];
		memset(DevicePathName,0,sizeof(DevicePathName));
		int	VendorID=0;
		int	ProductID=0;
		wcstombs(DevicePathName, symLinkWCStr, sizeof(DevicePathName));
		char	*vid=strstr(DevicePathName,"vid_");
		if(vid!=NULL){
			vid+=4;
			for(int i=0;i<4;i++){
				int	dn=StrHexToInt(*vid);
				vid++;
				if(dn<0)
					break;
				VendorID*=16;
				VendorID+=dn;
			}
		}
		hDevDim[r].VendorID=VendorID;
		char	*pid=strstr(DevicePathName,"pid_");
		if(pid!=NULL){
			pid+=4;
			for(int i=0;i<4;i++){
				int	dn=StrHexToInt(*pid);
				pid++;
				if(dn<0)
					break;
				ProductID*=16;
				ProductID+=dn;
			}
		}
		hDevDim[r].ProductID=ProductID;
	}
	//CoUninitialize();

	return param.mCount;
}



CaptureClass::CaptureClass(int DeviceNo ,LibWMFCamera *parent ,struct DeviceInfo &_Dev)
	:Brightness(CAPTURE_BRIGHTNESS)
	,Contrast(CAPTURE_CONTRAST)
	,Color(CAPTURE_HUE)
	,Vivid(CAPTURE_SATURATION)
	,Vividation(CAPTURE_SHARPNESS)
	,Gamma(CAPTURE_GAMMA)
	,WhiteBalance(CAPTURE_WHITEBALANCE)
	,Reflection(CAPTURE_BACKLIGHTCOMPENSATION)
	,Gain(CAPTURE_GAIN)
	,Zoom(CAPTURE_ZOOM)
	,Focus(CAPTURE_FOCUS)
	,Exposure(CAPTURE_EXPOSURE)
	,Iris(CAPTURE_IRIS)
	,Pan(CAPTURE_PAN)
	,Tilt(CAPTURE_TILT)
	,Rotation(CAPTURE_ROLL)
	,PowerlineFrequency(CAPTURE_POWERLINEFREQUENCY)
{
	Parent			=parent;
	Dev				=_Dev;
	mRefCount		=1;
	mReader			= NULL;
	mSource			= NULL;
	InitializeCriticalSection(&mCritsec);
	mDefaultStride	=0;
	mConvertFn		=NULL;
	mWhoAmI			=DeviceNo;
	mUsedIndex		=0;
	mRedoFromStart	=0;
	mCaptureBuffer	=NULL;
	MJPegTmpBuff	=NULL;
	mCaptureBufferWidth = 0;
	mCaptureBufferHeight = 0;
	mErrorLine		=0;
	mErrorCode		=0;
	mBadIndices		=0;
	mMaxBadIndices =16;
	mBadIndex = new unsigned int[mMaxBadIndices];
	mRedoFromStart	=0;
	Grabbed			=0;
	OnReading		=false;
	Changed			=0;
	StartCount		=0;
	SpanTimePointer	=0;
	LCCounter		=0;
	LastTime		=::GetComputerMiliSec();
	SampleError		=0;
	ContinueSampling=true;
	AckContinueSampling=false;
	FirstThread		=true;

	EnableRingBuffer=true;
	RbRPoint=0;
	RbWPoint=0;
	RbCaptured		=0;

	CamProp.CurrentType.Index=-1;

	CamProp.MirrorX				=false;
	CamProp.MirrorY				=false;
	CamProp.RotationAngle		=0;
	CamProp.MonoChrome			=false;

	for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
		//ImageBuff[i]=NULL;
		ImageBuff2[i]=NULL;
		ImageBuff3[i]=NULL;
	}
	MediaDimNumb=0;
}

CaptureClass::~CaptureClass()
{
	DeleteCriticalSection(&mCritsec);
	delete[] mBadIndex;
	mBadIndex=NULL;

	if(mCaptureBuffer!=NULL){
		delete	[]mCaptureBuffer;
		mCaptureBuffer=NULL;
	}
	if(MJPegTmpBuff!=NULL){
		delete	[]MJPegTmpBuff;
		MJPegTmpBuff=NULL;
	}
	for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
		//if(ImageBuff[i]!=NULL){
		//	delete	ImageBuff[i];
		//	ImageBuff[i]=NULL;
		//}
		if(ImageBuff2[i]!=NULL){
			delete	ImageBuff2[i];
			ImageBuff2[i]=NULL;
		}
		if(ImageBuff3[i]!=NULL){
			delete	ImageBuff3[i];
			ImageBuff3[i]=NULL;
		}
	}
}

// IUnknown methods
STDMETHODIMP CaptureClass::QueryInterface(REFIID aRiid, void** aPpv)
{
	static const QITAB qit[] =
	{
		QITABENT(CaptureClass, IMFSourceReaderCallback),
		{ 0 },
	};
	return QISearch(this, qit, aRiid, aPpv);
}

STDMETHODIMP_(ULONG) CaptureClass::AddRef()
{
	return InterlockedIncrement(&mRefCount);
}

STDMETHODIMP_(ULONG) CaptureClass::Release()
{
	ULONG count = InterlockedDecrement(&mRefCount);
	if (count == 0)
	{
		//delete this;
	}
	// For thread safety, return a temporary variable.
	return count;
}

CameraRingBuffer::CameraRingBuffer(void)
{
	RawData=new BYTE[4096*4096*4];
	RawDataLen=0;

	ImageBuff[0]=new ImageBuffer();
	ImageBuff[1]=new ImageBuffer();
	ImageBuff[2]=new ImageBuffer();
	ImageBuff[3]=new ImageBuffer();
	DoneConverted=false;
	Swapped		=false;
}
CameraRingBuffer::~CameraRingBuffer(void)
{
	if(RawData!=NULL){
		delete	[]RawData;
		RawData=NULL;
	}
	RawDataLen=0;

	delete	ImageBuff[0];
	delete	ImageBuff[1];
	delete	ImageBuff[2];
	delete	ImageBuff[3];
}
void	CameraRingBuffer::ReallocXY(int XLen ,int YLen)
{
	ImageBuff[0]->Set(0,0,XLen,YLen);
	ImageBuff[1]->Set(0,0,XLen,YLen);
	ImageBuff[2]->Set(0,0,XLen,YLen);
	ImageBuff[3]->Set(0,0,XLen,YLen);
	DoneConverted=false;
}

int CaptureClass::escapiPropToMFProp(int aProperty)
{
	int prop = 0;
	switch (aProperty)
	{
		//case CAPTURE_BRIGHTNESS:
	default:
		prop = VideoProcAmp_Brightness;
		break;
	case CAPTURE_CONTRAST:
		prop = VideoProcAmp_Contrast;
		break;
	case CAPTURE_HUE:
		prop = VideoProcAmp_Hue;
		break;
	case CAPTURE_SATURATION:
		prop = VideoProcAmp_Saturation;
		break;
	case CAPTURE_SHARPNESS:
		prop = VideoProcAmp_Sharpness;
		break;
	case CAPTURE_GAMMA:
		prop = VideoProcAmp_Gamma;
		break;
	case CAPTURE_COLORENABLE:
		prop = VideoProcAmp_ColorEnable;
		break;
	case CAPTURE_WHITEBALANCE:
		prop = VideoProcAmp_WhiteBalance;
		break;
	case CAPTURE_BACKLIGHTCOMPENSATION:
		prop = VideoProcAmp_BacklightCompensation;
		break;
	case CAPTURE_GAIN:
		prop = VideoProcAmp_Gain;
		break;
	case CAPTURE_PAN:
		prop = CameraControl_Pan;
		break;
	case CAPTURE_TILT:
		prop = CameraControl_Tilt;
		break;
	case CAPTURE_ROLL:
		prop = CameraControl_Roll;
		break;
	case CAPTURE_ZOOM:
		prop = CameraControl_Zoom;
		break;
	case CAPTURE_EXPOSURE:
		prop = CameraControl_Exposure;
		break;
	case CAPTURE_IRIS:
		prop = CameraControl_Iris;
		break;
	case CAPTURE_FOCUS:
		prop = CameraControl_Focus;
		break;
	case CAPTURE_POWERLINEFREQUENCY:
		prop = CameraControl_PowerLineFrequency;
		break;
	}
	return prop;
}

// IMFSourceReaderCallback methods
STDMETHODIMP CaptureClass::OnReadSample(
	HRESULT aStatus,
	DWORD aStreamIndex,
	DWORD aStreamFlags,
	LONGLONG aTimestamp,
	IMFSample *aSample
	)
{
//	QThread *q=QThread::currentThread();
//	QThread::Priority	Pr=q->priority();
//	q->setPriority(QThread::HighestPriority);

	static	int	wError=0;
	OnReading=true;
	StartCount--;
	HRESULT hr = S_OK;
	IMFMediaBuffer *mediabuffer = NULL;

	if(FirstThread==true){
		QThread *c=QThread::currentThread();
		if(c!=NULL){
			c->setPriority(QThread::TimeCriticalPriority);
		}
		FirstThread=false;
	}

	if (FAILED(aStatus))
	{
		// Bug workaround: some resolutions may just return error.
		// http://stackoverflow.com/questions/22788043/imfsourcereader-giving-error-0x80070491-for-some-resolutions
		// we fix by marking the resolution bad and retrying, which should use the next best match.
		mRedoFromStart = 1;
		if (mBadIndices == mMaxBadIndices)
		{
			unsigned int *t = new unsigned int[mMaxBadIndices * 2];
			memcpy(t, mBadIndex, mMaxBadIndices * sizeof(unsigned int));
			delete[] mBadIndex;
			mBadIndex = t;
			mMaxBadIndices *= 2;
		}
		mBadIndex[mBadIndices] = mUsedIndex;
		mBadIndices++;
		OnReading=false;
		if(aStatus!=0xC00D3EA2){
			SampleError=-1;
		}
		mErrorCode=aStatus;
//		q->setPriority(Pr);
		return aStatus;
	}

	DWORD	t1=::GetComputerMiliSec();
	SpanTime[SpanTimePointer]=t1-LastTime;
	LastTime=t1;


	if(mCaptureBuffer!=NULL){
//		if(Parent->GetLayersBase()->TryLockRChangingDataStructure()==false){
//			if(ContinueSampling==true){
//				if(StartCount<=0){
//					hr = mReader->ReadSample(
//						(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
//						0,
//						NULL,   // actual
//						NULL,   // flags
//						NULL,   // timestamp
//						NULL    // sample
//						);
//					if(hr!=0){
//						Parent->GetLayersBase()->UnlockChangingDataStructure();
//						LeaveCriticalSection(&mCritsec);
//						OnReading=false;
//						SampleError=-5;
//						return hr;
//					}
//					StartCount++;
//				}
//			}
//			OnReading=false;
//			SampleError=10;
//			q->setPriority(Pr);
//			return aStatus;
//		}

//		EnterCriticalSection(&mCritsec);
		if(Changed==0){
			if (SUCCEEDED(aStatus))
			{
				if (aSample)
				{
					// Get the video frame buffer from the sample.

					hr = aSample->GetBufferByIndex(0, &mediabuffer);
					ScopedRelease<IMFMediaBuffer> mediabuffer_s(mediabuffer);
					if(hr!=0){
//						Parent->GetLayersBase()->UnlockChangingDataStructure();
//						LeaveCriticalSection(&mCritsec);
						OnReading=false;
						SampleError=-2;
//						q->setPriority(Pr);
						return hr;
					}

					hr = aSample->GetTotalLength(&mTotalBuffByte);
					if(hr!=0){
//						Parent->GetLayersBase()->UnlockChangingDataStructure();
//						LeaveCriticalSection(&mCritsec);
						OnReading=false;
						SampleError=-3;
//						q->setPriority(Pr);
					}

					// Draw the frame.

					if (mConvertFn)
					{
						VideoBufferLock buffer(mediabuffer);    // Helper object to lock the video buffer.

						BYTE *scanline0 = NULL;
						LONG stride = 0;
						hr = buffer.LockBuffer(mDefaultStride, mCaptureBufferHeight, &scanline0, &stride);
						if(hr!=0){
//							Parent->GetLayersBase()->UnlockChangingDataStructure();
//							LeaveCriticalSection(&mCritsec);
							OnReading=false;
							SampleError=-4;
//							q->setPriority(Pr);
							return hr;
						}
						if(EnableRingBuffer==true){
							RingBuffer[RbWPoint].Mutex.lock();
							memcpy(RingBuffer[RbWPoint].RawData,scanline0,mTotalBuffByte);
							RingBuffer[RbWPoint].RawDataLen=mTotalBuffByte;
							RingBuffer[RbWPoint].XLen=Parent->GetDotPerLine();
							RingBuffer[RbWPoint].YLen=Parent->GetMaxLines();
							RingBuffer[RbWPoint].DoneConverted=false;
							RingBuffer[RbWPoint].Mutex.unlock();
							RbWPoint++;
							if(RbWPoint>=sizeof(RingBuffer)/sizeof(RingBuffer[0])){
								RbWPoint=0;
							}
							MutexRb.lock();
							RbCaptured++;
							MutexRb.unlock();
						}
						else{
							CopyMemory(mCaptureBuffer, scanline0, mTotalBuffByte);
						}
						/*
						mConvertFn(
							(BYTE *)mCaptureBuffer,
							mCaptureBufferWidth * 4,
							scanline0,
							stride,
							mCaptureBufferWidth,
							mCaptureBufferHeight
							);
						*/
					}
					else
					{
						// No convert function?
						VideoBufferLock buffer(mediabuffer);    // Helper object to lock the video buffer.
						BYTE *scanline0 = NULL;
						LONG stride = 0;
						hr = buffer.LockBuffer(mDefaultStride, mCaptureBufferHeight, &scanline0, &stride);
						if (stride < 0)
						{
							scanline0 += stride * mCaptureBufferHeight;
							stride = -stride;
						}
						//LONG bytes = stride * mCaptureBufferHeight;
						if(EnableRingBuffer==true){
							RingBuffer[RbWPoint].Mutex.lock();
							memcpy(RingBuffer[RbWPoint].RawData,scanline0,mTotalBuffByte);
							RingBuffer[RbWPoint].RawDataLen=mTotalBuffByte;
							RingBuffer[RbWPoint].XLen=Parent->GetDotPerLine();
							RingBuffer[RbWPoint].YLen=Parent->GetMaxLines();
							RingBuffer[RbWPoint].DoneConverted=false;
							RingBuffer[RbWPoint].Mutex.unlock();
							RbWPoint++;
							if(RbWPoint>=sizeof(RingBuffer)/sizeof(RingBuffer[0])){
								RbWPoint=0;
							}
							MutexRb.lock();
							RbCaptured++;
							MutexRb.unlock();
						}
						else{
							CopyMemory(mCaptureBuffer, scanline0, mTotalBuffByte);
						}
					}
					Grabbed++;
				}
			}
		}
		if(Changed>0)
			Changed--;
		// Request the next frame.
		if(ContinueSampling==true){
			if(StartCount<=0){
				hr = mReader->ReadSample(
					(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
					0,
					NULL,   // actual
					NULL,   // flags
					NULL,   // timestamp
					NULL    // sample
					);
				if(hr!=0){
//					Parent->GetLayersBase()->UnlockChangingDataStructure();
//					LeaveCriticalSection(&mCritsec);
					OnReading=false;
					SampleError=-5;
					return hr;
				}
				StartCount++;
			}
			if(Grabbed!=0){
				DWORD	tt1=::GetComputerMiliSec();
				if(EnableRingBuffer==false){
					Convert(ImageBuff2,(const BYTE *)mCaptureBuffer,mTotalBuffByte);
					LCTime[LCCounter]=::GetComputerMiliSec()-tt1;
					LCCounter++;
					if(LCCounter>=sizeof(LCTime)/sizeof(LCTime[0]))
						LCCounter=0;

					//LockBuff();
					//for(int i=0;i<sizeof(ImageBuff)/sizeof(ImageBuff[0]);i++){
					//	ImageBuff[i]->Swap(*ImageBuff2[i]);
					//}
				}
				//UnlockBuff();
			}
			else{
				wError++;
			}
		}
		else{
			AckContinueSampling=true;
		}

//		LeaveCriticalSection(&mCritsec);
//		Parent->GetLayersBase()->UnlockChangingDataStructure();
	}
	else{
		wError++;
	}
	ConvTime[SpanTimePointer]=::GetComputerMiliSec()-t1;
	SpanTimePointer++;
	if(SpanTimePointer>=sizeof(ConvTime)/sizeof(ConvTime[0]))
		SpanTimePointer=0;

	OnReading=false;
	Parent->CapturedBeforeImaging=true;
	SampleError=1;
	Parent->SignalCaptured();
//	q->setPriority(Pr);
	return hr;
}

bool	CaptureClass::Convert(ImageBuffer *IBuff[4],const BYTE *SrcBuff, int SrcByte)
{
	if(mConvertFn!=NULL){
		mConvertFn(Parent
					,IBuff
					,SrcBuff
					,mDefaultStride
					,mCaptureBufferWidth
					,mCaptureBufferHeight
					,SrcByte
					,CamProp.MirrorX
					,CamProp.MirrorY
					,CamProp.RotationAngle
					);
		return true;
	}
	return false;
}

static	int		RbRPointList[1000];
static	int		RbRPointPoint=0;
void	CaptureClass::RingConvert(void)
{
	RbRPoint=RbWPoint-1;
	if(RbRPoint<0){
		RbRPoint=sizeof(RingBuffer)/sizeof(RingBuffer[0])-1;
	}
	if(RbRPoint>=sizeof(RingBuffer)/sizeof(RingBuffer[0])){
		RbRPoint=sizeof(RingBuffer)/sizeof(RingBuffer[0])-1;
	}
	RingBuffer[RbRPoint].Mutex.lock();
	if(RingBuffer[RbRPoint].DoneConverted==false
	&& RingBuffer[RbRPoint].XLen!=0 && RingBuffer[RbRPoint].YLen!=0
	&& RingBuffer[RbRPoint].ImageBuff[0]!=NULL && RingBuffer[RbRPoint].ImageBuff[0]->IsNull()==false
	&& RingBuffer[RbRPoint].ImageBuff[1]!=NULL && RingBuffer[RbRPoint].ImageBuff[1]->IsNull()==false
	&& RingBuffer[RbRPoint].ImageBuff[2]!=NULL && RingBuffer[RbRPoint].ImageBuff[2]->IsNull()==false){		
		Convert(RingBuffer[RbRPoint].ImageBuff,RingBuffer[RbRPoint].RawData, RingBuffer[RbRPoint].RawDataLen);
		RingBuffer[RbRPoint].DoneConverted	=true;
		RingBuffer[RbRPoint].Swapped		=false;
		
	}
	RingBuffer[RbRPoint].Mutex.unlock();

	RbRPointList[RbRPointPoint]=RbRPoint;
	RbRPointPoint++;
	if(RbRPointPoint>=1000)
		RbRPointPoint=0;
	//RbRPoint++;
	//if(RbRPoint>=sizeof(RingBuffer)/sizeof(RingBuffer[0])){
	//	RbRPoint=0;
	//}
}

void CaptureClass::run()
{
	while(Parent->GetLayersBase()->GetOnTerminating()==false){
		RingConvert();
		//msleep(10);
	}
}
	
bool	CaptureClass::GetBuff(ImageBuffer *Buff[3])
{
	for(int i=0;i<sizeof(RingBuffer)/sizeof(RingBuffer[0]);i++){
		int	k=RbRPoint-i;
		if(k<0){
			k+=sizeof(RingBuffer)/sizeof(RingBuffer[0]);
		}
		if(RingBuffer[k].DoneConverted==true){
			RingBuffer[k].Mutex.lock();
			Buff[0]=RingBuffer[k].ImageBuff[0];
			Buff[1]=RingBuffer[k].ImageBuff[1];
			Buff[2]=RingBuffer[k].ImageBuff[2];
			RingBuffer[k].Mutex.unlock();
			return true;
		}
	}
	return false;
}

bool	CaptureClass::SwapBuff(ImageBuffer *Buff[3])
{
	for(int i=0;i<sizeof(RingBuffer)/sizeof(RingBuffer[0]);i++){
		int	k=RbRPoint-i;
		if(k<0){
			k+=sizeof(RingBuffer)/sizeof(RingBuffer[0]);
		}
		if(RingBuffer[k].DoneConverted==true){
			if(RingBuffer[k].Swapped==false){
				RingBuffer[k].Mutex.lock();
				if(RingBuffer[k].XLen!=Buff[0]->GetWidth()
				|| RingBuffer[k].YLen!=Buff[0]->GetHeight()){
					Buff[0]->Set(0,0,RingBuffer[k].XLen,RingBuffer[k].YLen);
				}
				if(RingBuffer[k].XLen!=Buff[1]->GetWidth()
				|| RingBuffer[k].YLen!=Buff[1]->GetHeight()){
					Buff[1]->Set(0,0,RingBuffer[k].XLen,RingBuffer[k].YLen);
				}
				if(RingBuffer[k].XLen!=Buff[2]->GetWidth()
				|| RingBuffer[k].YLen!=Buff[2]->GetHeight()){
					Buff[2]->Set(0,0,RingBuffer[k].XLen,RingBuffer[k].YLen);
				}

				RingBuffer[k].ImageBuff[0]->Swap(*Buff[0]);
				RingBuffer[k].ImageBuff[1]->Swap(*Buff[1]);
				RingBuffer[k].ImageBuff[2]->Swap(*Buff[2]);
				RingBuffer[k].Swapped=true;
				RingBuffer[k].Mutex.unlock();
				return true;
			}
			return false;
		}
	}
	return false;
}

STDMETHODIMP CaptureClass::OnEvent(DWORD, IMFMediaEvent *)
{
	return S_OK;
}

STDMETHODIMP CaptureClass::OnFlush(DWORD)
{
	return S_OK;
}

bool CaptureClass::isFormatSupported(REFGUID aSubtype) const
{
	int i;
	for (i = 0; gFormatConversions[i].mXForm!=NULL; i++){
		if (aSubtype == gFormatConversions[i].mSubtype){
			return true;
		}
	}
	return false;
}

bool CaptureClass::initCapture(void)
{
	HRESULT hr;

	SampleError=0;
	// choose device
	IMFAttributes *attributes = NULL;
	hr = MFCreateAttributes(&attributes, 1);
	if(hr!=0)	return false;
	ScopedRelease<IMFAttributes> attributes_s(attributes);
	hr = attributes->SetGUID(
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
		);
	if(hr!=0)	return false;

	ChooseDeviceParam param = { 0 };
	hr = MFEnumDeviceSources(attributes, &param.mDevices, &param.mCount);
	if(hr!=0)	return false;

	// use param.ppDevices[0]
	EnterCriticalSection(&mCritsec);

	hr = param.mDevices[mWhoAmI]->ActivateObject(
		__uuidof(IMFMediaSource),
		(void**)&mSource
		);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	IMFAttributes   *attributesN = NULL;
	hr = MFCreateAttributes(&attributesN, 3);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}
	ScopedRelease<IMFAttributes> attributes_sN(attributesN);

	hr = attributesN->SetUINT32(MF_READWRITE_DISABLE_CONVERTERS, TRUE);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	hr = attributesN->SetUnknown(
		MF_SOURCE_READER_ASYNC_CALLBACK,
		this
		);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	hr = MFCreateSourceReaderFromMediaSource(
		mSource,
		attributesN,
		&mReader
		);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	LeaveCriticalSection(&mCritsec);

	if(MediaDimNumb==0){
		MediaDimNumb	=EnumMediaType();
	}
	return true;
}

void CaptureClass::deinitCapture()
{
	AckContinueSampling=false;
	ContinueSampling=false;
	SampleError=0;
	for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<1500;){
		//if(SampleError!=0){
		if(AckContinueSampling==true){
			break;
		}
		//QCoreApplication::processEvents();
		GSleep(30);
	}

	EnterCriticalSection(&mCritsec);

	if(mReader!=NULL){
		mReader->Release();
		mReader=NULL;
	}

	if(mSource!=NULL){
		mSource->Shutdown();
		mSource->Release();
		mSource=NULL;
	}

	if(mCaptureBuffer!=NULL){
		delete[] mCaptureBuffer;
		mCaptureBuffer=NULL;
	}
	if(MJPegTmpBuff!=NULL){
		delete[] MJPegTmpBuff;
		MJPegTmpBuff=NULL;
	}
	for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
		//if(ImageBuff[i]!=NULL){
		//	delete	ImageBuff[i];
		//	ImageBuff[i]=NULL;
		//}
		if(ImageBuff2[i]!=NULL){
			delete	ImageBuff2[i];
			ImageBuff2[i]=NULL;
		}
		if(ImageBuff3[i]!=NULL){
			delete	ImageBuff3[i];
			ImageBuff3[i]=NULL;
		}
	}
	LeaveCriticalSection(&mCritsec);
}

int		CaptureClass::EnumMediaType(void)
{
	int MaxDim=sizeof(RealMediaDim)/sizeof(RealMediaDim[0]);

	HRESULT hr;
	int	MediaCount=0;

	for(DWORD count=0;count<MaxDim;count++){
		IMFMediaType * nativeType = NULL;
		HRESULT nativeTypeErrorCode = mReader->GetNativeMediaType(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			count,
			&nativeType);
		ScopedRelease<IMFMediaType> nativeType_s(nativeType);

		if (nativeTypeErrorCode != S_OK){
			continue;
		}

		// get the media type 
		GUID nativeGuid = { 0 };
		hr = nativeType->GetGUID(MF_MT_SUBTYPE, &nativeGuid);

		if (FAILED(hr))	break;

		UINT32 width, height;
		hr = MFGetAttributeSize(nativeType, MF_MT_FRAME_SIZE, &width, &height);

		if (FAILED(hr)) break;

		RealMediaDim[MediaCount].Index	=count;
		RealMediaDim[MediaCount].Width	=width;
		RealMediaDim[MediaCount].Height	=height;
		RealMediaDim[MediaCount].ConvertType=_EMT_YUY2;

		UINT32 Numerator;
		UINT32 Denominator;
		hr = MFGetAttributeRatio(nativeType,
					        MF_MT_FRAME_RATE, 
							&Numerator, 
							&Denominator);
		RealMediaDim[MediaCount].FPS=Numerator;

		bool	FoundMType=false;
		for (DWORD i = 0; gFormatConversions[i].mXForm!=NULL; i++){
			if(nativeGuid==gFormatConversions[i].mSubtype){
				RealMediaDim[MediaCount].ConvertType=gFormatConversions[i].MType;
				FoundMType=true;
				break;
			}
		}
		if(FoundMType==true){
			MediaCount++;
			if(MediaCount>=MaxDim)
				break;
		}
	}
	int	N=0;
	for(int i=0;i<MediaCount;i++){
		if(RealMediaDim[i].ConvertType==_EMT_YUY2 || RealMediaDim[i].ConvertType==_EMT_MJPG){
			MediaDim[N]=RealMediaDim[i];
			N++;
		}
	}

	return N;
}
bool	CaptureClass::SetMediaType(struct StructMediaType &Type)
{
	HRESULT hr;
	bool	AlreadyLocked=false;

	ContinueSampling=false;
	if(Parent->GetLayersBase()->TryLockRChangingDataStructure()==false){
		AlreadyLocked=true;
	}
	Parent->GetLayersBase()->UnlockChangingDataStructure();

	for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<500;){
		if(Parent->GetLayersBase()->GetOnTerminating()==true){
			break;
		}
		if(SampleError!=0){
			break;
		}
		QCoreApplication::processEvents();
	}

	if(AlreadyLocked==true){
		Parent->GetLayersBase()->LockWChangingDataStructure();
	}

	EnterCriticalSection(&mCritsec);

	CamProp.CurrentType=Type;
	if(Type.Index<0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}
	GSleep(200);
	hr = mReader->SetStreamSelection(MF_SOURCE_READER_FIRST_VIDEO_STREAM,false);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}
	GSleep(100);
	hr = mReader->Flush(MF_SOURCE_READER_FIRST_VIDEO_STREAM);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}
	GSleep(100);
	mUsedIndex = Type.Index;
	IMFMediaType * nativeType = NULL;
	hr = mReader->GetNativeMediaType(
		(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
		mUsedIndex,
		&nativeType
		);
	ScopedRelease<IMFMediaType> type_s(nativeType);

	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	GSleep(100);
	hr = setVideoType(nativeType);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	GSleep(100);
	hr = mReader->SetCurrentMediaType(
		(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
		NULL,
		nativeType
		);
	if(hr!=0){
		LeaveCriticalSection(&mCritsec);
		return false;
	}

	LeaveCriticalSection(&mCritsec);

	//hr = mReader->SetStreamSelection(MF_SOURCE_READER_FIRST_VIDEO_STREAM,TRUE);
	//if(hr!=0){
	//	return false;
	//}
	GSleep(100);
	hr = mReader->SetStreamSelection(MF_SOURCE_READER_FIRST_VIDEO_STREAM,TRUE);
	if(hr!=0){
		return false;
	}
	ContinueSampling=true;
	if(Parent->GetLayersBase()->TryLockRChangingDataStructure()==false){
		AlreadyLocked=true;
	}
	Parent->GetLayersBase()->UnlockChangingDataStructure();
	GSleep(100);
	//do{
		hr = mReader->ReadSample(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			0,
			NULL,
			NULL,
			NULL,
			NULL
			);
		if(hr!=0){
			return false;
		}
		for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<5000;){
			if(Parent->GetLayersBase()->GetOnTerminating()==true){
				break;
			}
			if(SampleError!=0){
				break;
			}
			Parent->GetLayersBase()->LockWeakDraw();
			QCoreApplication::processEvents();
			Parent->GetLayersBase()->UnlockWeakDraw();
		}
	//}while(SampleError==-1);

	if(AlreadyLocked==true){
		Parent->GetLayersBase()->LockWChangingDataStructure();
	}

	if(SampleError<=0){
		return false;
	}

	StartCount++;
	Changed=3;

	return true;
}

HRESULT CaptureClass::setConversionFunction(REFGUID aSubtype)
{
	mConvertFn = NULL;

	// If raw data is desired, skip conversion
	for (DWORD i = 0; gFormatConversions[i].mXForm!=NULL; i++){
		if (gFormatConversions[i].mSubtype == aSubtype){
			mConvertFn = gFormatConversions[i].mXForm;
			return S_OK;
		}
	}

	return MF_E_INVALIDMEDIATYPE;
}
HRESULT CaptureClass::setVideoType(IMFMediaType *aType)
{
	HRESULT hr = S_OK;
	GUID subtype = { 0 };

	// Find the video subtype.
	hr = aType->GetGUID(MF_MT_SUBTYPE, &subtype);
	if(hr!=0)	return hr;

	// Choose a conversion function.
	// (This also validates the format type.)

	hr = setConversionFunction(subtype);
	if(hr!=0)	return hr;

	//
	// Get some video attributes.
	//

	subtype = GUID_NULL;

	UINT32 width = 0;
	UINT32 height = 0;

	// Get the subtype and the image size.
	hr = aType->GetGUID(MF_MT_SUBTYPE, &subtype);
	if(hr!=0)	return hr;

	hr = MFGetAttributeSize(aType, MF_MT_FRAME_SIZE, &width, &height);
	if(hr!=0)	return hr;

	hr = MFGetStrideForBitmapInfoHeader(subtype.Data1, width, &mDefaultStride);
	if(hr!=0)	return hr;

	if(mCaptureBuffer!=NULL){
		delete	[]mCaptureBuffer;
	}
	mCaptureBuffer = new unsigned int[width * height];

	if(MJPegTmpBuff!=NULL){
		delete	[]MJPegTmpBuff;
	}
	MJPegTmpBuff = new BYTE[4*width * height];

	mCaptureBufferWidth = width;
	mCaptureBufferHeight = height;

	LockBuff();
	if(CamProp.RotationAngle==0 || CamProp.RotationAngle==180){
		for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
			//if(ImageBuff[i]==NULL)
			//	ImageBuff[i]=new ImageBuffer(0,width,height);
			//else if(ImageBuff[i]->GetWidth()!=width || ImageBuff[i]->GetHeight()!=height){
			//	ImageBuff[i]->Set(0,0,width,height);
			//}
			if(ImageBuff2[i]==NULL)
				ImageBuff2[i]=new ImageBuffer(0,width,height);
			else if(ImageBuff2[i]->GetWidth()!=width || ImageBuff2[i]->GetHeight()!=height){
				ImageBuff2[i]->Set(0,0,width,height);
			}
			if(ImageBuff3[i]==NULL)
				ImageBuff3[i]=new ImageBuffer(0,width,height);
			else if(ImageBuff3[i]->GetWidth()!=width || ImageBuff3[i]->GetHeight()!=height){
				ImageBuff3[i]->Set(0,0,width,height);
			}
		}
	}
	else{
		for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
			//if(ImageBuff[i]==NULL)
			//	ImageBuff[i]=new ImageBuffer(0,height,width);
			//else if(ImageBuff[i]->GetWidth()!=height || ImageBuff[i]->GetHeight()!=width){
			//	ImageBuff[i]->Set(0,0,height,width);
			//}
			if(ImageBuff2[i]==NULL)
				ImageBuff2[i]=new ImageBuffer(0,height,width);
			else if(ImageBuff2[i]->GetWidth()!=height || ImageBuff2[i]->GetHeight()!=width){
				ImageBuff2[i]->Set(0,0,height,width);
			}
			if(ImageBuff3[i]==NULL)
				ImageBuff3[i]=new ImageBuffer(0,height,width);
			else if(ImageBuff3[i]->GetWidth()!=height || ImageBuff3[i]->GetHeight()!=width){
				ImageBuff3[i]->Set(0,0,height,width);
			}
		}
	}
	UnlockBuff();

	return hr;
}
bool	CaptureClass::Save(QIODevice *f)
{
	DWORD	Ver=0x2a080002;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return false;
	if(f->write((const char *)&CamProp,sizeof(CamProp))!=sizeof(CamProp))
		return false;

	if(Brightness	.Save(f)==false)	return false;
	if(Contrast		.Save(f)==false)	return false;
	if(Color		.Save(f)==false)	return false;
	if(Vivid		.Save(f)==false)	return false;
	if(Vividation	.Save(f)==false)	return false;
	if(Gamma		.Save(f)==false)	return false;
	if(WhiteBalance	.Save(f)==false)	return false;
	if(Reflection	.Save(f)==false)	return false;
	if(Gain			.Save(f)==false)	return false;
	if(Zoom			.Save(f)==false)	return false;
	if(Focus		.Save(f)==false)	return false;
	if(Exposure		.Save(f)==false)	return false;
	if(Iris			.Save(f)==false)	return false;
	if(Pan			.Save(f)==false)	return false;
	if(Tilt			.Save(f)==false)	return false;
	if(Rotation		.Save(f)==false)	return false;
	if(PowerlineFrequency.Save(f)==false)	return false;
	return true;
}

bool	CaptureClass::Load(QIODevice *f)
{
	DWORD	Ver;

	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return false;
	DWORD	LVer=Ver&0xFFFF0000;
	if(LVer!=0x2a080000)
		return false;
	Ver &=0xFF;

	if(f->read((char *)&CamProp,sizeof(CamProp))!=sizeof(CamProp))
		return false;
	if(Brightness	.Load(f)==false)	return false;
	if(Contrast		.Load(f)==false)	return false;
	if(Color		.Load(f)==false)	return false;
	if(Vivid		.Load(f)==false)	return false;
	if(Vividation	.Load(f)==false)	return false;
	if(Gamma		.Load(f)==false)	return false;
	if(WhiteBalance	.Load(f)==false)	return false;
	if(Reflection	.Load(f)==false)	return false;
	if(Gain			.Load(f)==false)	return false;
	if(Zoom			.Load(f)==false)	return false;
	if(Focus		.Load(f)==false)	return false;
	if(Exposure		.Load(f)==false)	return false;
	if(Iris			.Load(f)==false)	return false;
	if(Pan			.Load(f)==false)	return false;
	if(Tilt			.Load(f)==false)	return false;
	if(Rotation		.Load(f)==false)	return false;
	if(Ver>=2){
		if(PowerlineFrequency.Load(f)==false)	return false;
	}
	return true;
}
	
void	CaptureClass::LockBuff(void)
{
	MutexBuff.lock();
}

void	CaptureClass::UnlockBuff(void)
{
	MutexBuff.unlock();
}

void	CaptureClass::ReallocXY(int XLen ,int YLen)
{
	//_heapchk();
	for(int i=0;i<sizeof(ImageBuff2)/sizeof(ImageBuff2[0]);i++){
		//if(ImageBuff[i]!=NULL && (ImageBuff[i]->GetWidth()!=XLen || ImageBuff[i]->GetHeight()!=YLen)){
		//	ImageBuff[i]->Set(0,0,XLen,YLen);
		//}
		if(ImageBuff2[i]!=NULL && (ImageBuff2[i]->GetWidth()!=XLen || ImageBuff2[i]->GetHeight()!=YLen)){
			ImageBuff2[i]->Set(0,0,XLen,YLen);
		}
		if(ImageBuff3[i]!=NULL && (ImageBuff3[i]->GetWidth()!=XLen || ImageBuff3[i]->GetHeight()!=YLen)){
			ImageBuff3[i]->Set(0,0,XLen,YLen);
		}
	}
	for(int i=0;i<sizeof(RingBuffer)/sizeof(RingBuffer[0]);i++){
		RingBuffer[i].Mutex.lock();
	}
	for(int i=0;i<sizeof(RingBuffer)/sizeof(RingBuffer[0]);i++){
		RingBuffer[i].ReallocXY(XLen,YLen);
	}
	for(int i=0;i<sizeof(RingBuffer)/sizeof(RingBuffer[0]);i++){
		RingBuffer[i].Mutex.unlock();
	}
}

//========================================================================
PropertyItem::PropertyItem(CAPTURE_PROPETIES e)
{
	Prop			=e;
	CurrentValue	=0;
	MinValue		=0;
	MaxValue		=100;
	Step			=1;
	DefaultValue	=0;
	CapsFlags		=0;
	ModeAuto		=true;
}
bool PropertyItem::setProperty(LibWMFCamera *Cam)
{
	CaptureClass	*pCam=Cam->Cam;
	if(pCam==NULL)
		return false;

	HRESULT hr;
	IAMVideoProcAmp *procAmp = NULL;
	IAMCameraControl *control = NULL;

	int prop = pCam->escapiPropToMFProp(Prop);

	if (Prop < CAPTURE_PAN){
		hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&procAmp));
		if (SUCCEEDED(hr)){
			hr = procAmp->GetRange(prop, &MinValue, &MaxValue, &Step, &DefaultValue, &CapsFlags);

			if (SUCCEEDED(hr)){
				LONG val = (long)floor(MinValue + (MaxValue - MinValue) * CurrentValue);
				if (ModeAuto==true)
					val = DefaultValue;
				hr = procAmp->Set(prop, val, (ModeAuto==true) ? VideoProcAmp_Flags_Auto : VideoProcAmp_Flags_Manual);
			}
			procAmp->Release();
			if(hr!=0)	return false;
			return true;
		}
	}
	else{
		hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&control));
		if (SUCCEEDED(hr)){
			hr = control->GetRange(prop, &MinValue, &MaxValue, &Step, &DefaultValue, &CapsFlags);

			if (SUCCEEDED(hr)){
				LONG val = (long)floor(MinValue + (MaxValue - MinValue) * CurrentValue);
				if (ModeAuto==true)
					val = DefaultValue;
				hr = control->Set(prop, val, (ModeAuto==true) ? VideoProcAmp_Flags_Auto : VideoProcAmp_Flags_Manual);
			}
			control->Release();
			if(hr!=0)	return false;
			return true;
		}
	}
	return false;
}
bool PropertyItem::getProperty(LibWMFCamera *Cam)
{
	CaptureClass	*pCam=Cam->Cam;
	if(pCam==NULL)
		return false;
	HRESULT hr;
	IAMVideoProcAmp *procAmp = NULL;
	IAMCameraControl *control = NULL;

	ModeAuto = false;
	CurrentValue = -1;

	int prop = pCam->escapiPropToMFProp(Prop);

	if (Prop < CAPTURE_PAN){
		hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&procAmp));
		if (SUCCEEDED(hr)){
			hr = procAmp->GetRange(prop, &MinValue, &MaxValue, &Step, &DefaultValue, &CapsFlags);

			if (SUCCEEDED(hr)){
				long v = 0, f = 0;
				hr = procAmp->Get(prop, &v, &f);
				if (SUCCEEDED(hr)){
					CurrentValue = (v - MinValue) / (float)(MaxValue - MinValue);
					ModeAuto = ((f & VideoProcAmp_Flags_Auto)!=0)?true:false;
				}
			}
			procAmp->Release();
			return true;
		}
	}
	else
	{
		hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&control));
		if (SUCCEEDED(hr)){
			hr = control->GetRange(prop, &MinValue, &MaxValue, &Step, &DefaultValue, &CapsFlags);

			if (SUCCEEDED(hr)){
				long v = 0, f = 0;
				hr = control->Get(prop, &v, &f);
				if (SUCCEEDED(hr)){
					CurrentValue = (v - MinValue) / (float)(MaxValue - MinValue);
					ModeAuto = ((f & VideoProcAmp_Flags_Auto)!=0)?true:false;
				}
			}
			control->Release();
			return true;
		}
	}
	return false;
}
void	PropertyItem::RestoreDefault(LibWMFCamera *Cam)
{
	CurrentValue = (DefaultValue - MinValue) / (float)(MaxValue - MinValue);
	setProperty(Cam);
}

bool	PropertyItem::Save(QIODevice *f)
{
	if(f->write((const char *)&Prop,sizeof(Prop))!=sizeof(Prop))
		return false;
	if(f->write((const char *)&CurrentValue,sizeof(CurrentValue))!=sizeof(CurrentValue))
		return false;
	if(f->write((const char *)&ModeAuto,sizeof(ModeAuto))!=sizeof(ModeAuto))
		return false;

	return true;
}

bool	PropertyItem::Load(QIODevice *f)
{
	if(f->read((char *)&Prop,sizeof(Prop))!=sizeof(Prop))
		return false;
	if(f->read((char *)&CurrentValue,sizeof(CurrentValue))!=sizeof(CurrentValue))
		return false;
	if(f->read((char *)&ModeAuto,sizeof(ModeAuto))!=sizeof(ModeAuto))
		return false;

	return true;
}
PropertyItem	&PropertyItem::operator=(PropertyItem &src)
{
	Prop			=src.Prop			;
	CurrentValue	=src.CurrentValue	;
	MinValue		=src.MinValue		;
	MaxValue		=src.MaxValue		;
	Step			=src.Step			;
	DefaultValue	=src.DefaultValue	;
	ModeAuto		=src.ModeAuto		;
	return *this;
}


//========================================================================
PropertyItemPowerlineFrequency::PropertyItemPowerlineFrequency(CAPTURE_PROPETIES e)
{
	Prop			=e;
	CurrentValue	=0;
	MinValue		=0;
	MaxValue		=100;
	Step			=1;
	DefaultValue	=0;
	CapsFlags		=0;
	ModeAuto		=true;
}

bool PropertyItemPowerlineFrequency::setProperty(LibWMFCamera *Cam)
{
	CaptureClass	*pCam=Cam->Cam;
	if(pCam==NULL)
		return false;

	IAMVideoProcAmp *procAmp = NULL;
	HRESULT hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&procAmp));
	if (SUCCEEDED(hr)){
		long f = (ModeAuto==true)?VideoProcAmp_Flags_Auto:VideoProcAmp_Flags_Manual;
		hr = procAmp->Set(VideoProcAmpProperty(13), CurrentValue, f);
		procAmp->Release();
		return true;
	}

	return false;
}
bool PropertyItemPowerlineFrequency::getProperty(LibWMFCamera *Cam)
{
	CaptureClass	*pCam=Cam->Cam;
	if(pCam==NULL)
		return false;

	IAMVideoProcAmp *procAmp = NULL;
	HRESULT hr = pCam->mSource->QueryInterface(IID_PPV_ARGS(&procAmp));
	if (SUCCEEDED(hr)){
		long v = 0, f = 0;
		hr = procAmp->Get(VideoProcAmpProperty(13), &v, &f);
		if (SUCCEEDED(hr)){
			CurrentValue = v;
			ModeAuto = ((f & VideoProcAmp_Flags_Auto)!=0)?true:false;
		}
		procAmp->Release();
		return true;
	}

	return false;
}
void	PropertyItemPowerlineFrequency::RestoreDefault(LibWMFCamera *Cam)
{
	CurrentValue = (DefaultValue - MinValue) / (float)(MaxValue - MinValue);
	setProperty(Cam);
}

bool	PropertyItemPowerlineFrequency::Save(QIODevice *f)
{
	if(f->write((const char *)&Prop,sizeof(Prop))!=sizeof(Prop))
		return false;
	if(f->write((const char *)&CurrentValue,sizeof(CurrentValue))!=sizeof(CurrentValue))
		return false;
	if(f->write((const char *)&ModeAuto,sizeof(ModeAuto))!=sizeof(ModeAuto))
		return false;

	return true;
}

bool	PropertyItemPowerlineFrequency::Load(QIODevice *f)
{
	if(f->read((char *)&Prop,sizeof(Prop))!=sizeof(Prop))
		return false;
	if(f->read((char *)&CurrentValue,sizeof(CurrentValue))!=sizeof(CurrentValue))
		return false;
	if(f->read((char *)&ModeAuto,sizeof(ModeAuto))!=sizeof(ModeAuto))
		return false;

	return true;
}
PropertyItemPowerlineFrequency	&PropertyItemPowerlineFrequency::operator=(PropertyItemPowerlineFrequency &src)
{
	Prop			=src.Prop			;
	CurrentValue	=src.CurrentValue	;
	MinValue		=src.MinValue		;
	MaxValue		=src.MaxValue		;
	Step			=src.Step			;
	DefaultValue	=src.DefaultValue	;
	ModeAuto		=src.ModeAuto		;
	return *this;
}
//========================================================================
LibWMFCamera::LibWMFCamera(int CamNo ,LayersBase *Base ,int DeviceNo ,struct DeviceInfo &_Dev)
	:CameraHandle(CamNo,Base)
{
	LastCapturedTime=0;
	SpanMiliSecPoint=0;
	SpanMiliSecCount=0;
	CapturedBeforeImaging	=false;

	Cam=new CaptureClass(DeviceNo ,this,_Dev);
	DecHndle=tjInitDecompress();
	Cam->start();
}

LibWMFCamera::~LibWMFCamera(void)
{
	if(Cam!=NULL){
		Cam->deinitCapture();
		//for(DWORD t=::GetComputerMiliSec();::GetComputerMiliSec()-t<500;){
		GSleep(100);
		delete	Cam;
		Cam=NULL;
	}
	tjDestroy(DecHndle);
}

bool	LibWMFCamera::Initial(void)
{
	if(Cam==NULL)
		return false;
	return Cam->initCapture();
}

int		LibWMFCamera::EnumMediaType(struct StructMediaType Dim[] ,int MaxDim)
{
	if(Cam==NULL)
		return -1;
	int	Count=0;
	for(int i=0;i<Cam->MediaDimNumb && i<MaxDim;i++){
		Dim[i]=Cam->MediaDim[i];
		Count++;
	}
	return Count;
}
bool	LibWMFCamera::SetMediaType(struct	StructMediaType &Type)
{
	if(Cam==NULL)
		return false;
	if(Cam->CamProp.CurrentType.IsEqual(Type)==true){
		return true;
	}
	Cam->deinitCapture();
	if(Cam->initCapture()==false){
		return false;
	}
	bool	b=GetLayersBase()->IsPossibleToUpdateDisplay();
	GetLayersBase()->SetPossibleToUpdateDisplay(false);

	bool	Ret=Cam->SetMediaType(Type);
	if(Ret==false){
		Cam->deinitCapture();
		if(Cam->initCapture()==false){
			return false;
		}
		Ret=Cam->SetMediaType(Type);
	}
	GetLayersBase()->SetPossibleToUpdateDisplay(b);
	return Ret;
}

bool	LibWMFCamera::SetFastestSize(int XLen ,int YLen)
{
	if(Cam==NULL)
		return false;
	int	Index=-1;
	if(Cam->CamProp.RotationAngle==0 || Cam->CamProp.RotationAngle==180){
		int	MaxFPS=0;
		for(int i=0;i<Cam->MediaDimNumb;i++){
			if(Cam->MediaDim[i].Width==XLen && Cam->MediaDim[i].Height==YLen
			&& Cam->MediaDim[i].FPS>MaxFPS
			&& Cam->MediaDim[i].ConvertType!=_EMT_NV12){
				MaxFPS=Cam->MediaDim[i].FPS;
				Index=i;
			}
		}
	}
	else{
		int	MaxFPS=0;
		for(int i=0;i<Cam->MediaDimNumb;i++){
			if(Cam->MediaDim[i].Width==YLen && Cam->MediaDim[i].Height==XLen
			&& Cam->MediaDim[i].FPS>MaxFPS
			&& Cam->MediaDim[i].ConvertType!=_EMT_NV12){
				MaxFPS=Cam->MediaDim[i].FPS;
				Index=i;
			}
		}
	}
	if(Index>=0){
		return SetMediaType(Cam->MediaDim[Index]);
	}
	return false;
}
bool	LibWMFCamera::GetMediaType(struct	StructMediaType &Type)
{
	if(Cam==NULL)
		return false;
	Type=Cam->CamProp.CurrentType;
	return true;
}
bool	LibWMFCamera::IsCaptured(void)
{
	if(Cam==NULL)
		return false;
	if(Cam->Grabbed>0){
		Cam->Grabbed=0;
		return true;
	}
	return false;
}
bool	LibWMFCamera::IsErrored(void)
{
	if(Cam==NULL)
		return false;
	if(Cam->SampleError<0){
		return true;
	}
	return false;
}
int		LibWMFCamera::GetVendorID(void)
{
	if(Cam==NULL)
		return -1;
	return Cam->Dev.VendorID;
}
int		LibWMFCamera::GetProductID(void)
{
	if(Cam==NULL)
		return -1;
	return Cam->Dev.ProductID;
}
const char	*LibWMFCamera::GetDeviceName(void)
{
	if(Cam==NULL)
		return NULL;
	return Cam->Dev.DeviceName;
}
int		LibWMFCamera::GetDeviceNo(void)
{
	if(Cam==NULL)
		return -1;
	return Cam->mWhoAmI;
}

bool	LibWMFCamera::Save(QIODevice *f)
{
	if(Cam==NULL)
		return false;
	struct	StructMediaType Type;
	GetMediaType(Type);
	if(f->write((const char *)&Type,sizeof(Type))!=sizeof(Type)){
		return false;
	}
	return Cam->Save(f);
}

bool	LibWMFCamera::Load(QIODevice *f)
{
	if(Cam==NULL)
		return false;
	struct	StructMediaType Type;
	if(f->read((char *)&Type,sizeof(Type))!=sizeof(Type)){
		return false;
	}
	SetMediaType(Type);
	return Cam->Load(f);
}

bool LibWMFCamera::setProperty(void)
{
	bool	Ret=true;
	if(Cam->Brightness			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Contrast			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Color				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Vivid				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Vividation			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Gamma				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->WhiteBalance		.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Reflection			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Gain				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Zoom				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Focus				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Exposure			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Iris				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Pan					.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Tilt				.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->Rotation			.setProperty(this)==false)	{	Ret=false;	}
	if(Cam->PowerlineFrequency	.setProperty(this)==false)	{	Ret=false;	}

	return Ret;
}
bool LibWMFCamera::getProperty(void)
{
	bool	Ret=true;

	if(Cam->Brightness			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Contrast			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Color				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Vivid				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Vividation			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Gamma				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->WhiteBalance		.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Reflection			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Gain				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Zoom				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Focus				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Exposure			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Iris				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Pan					.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Tilt				.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->Rotation			.getProperty(this)==false)	{	Ret=false;	}
	if(Cam->PowerlineFrequency	.getProperty(this)==false)	{	Ret=false;	}
	return Ret;
}

void	LibWMFCamera::RestoreDefault(void)
{
	Cam->Brightness			.RestoreDefault(this);
	Cam->Contrast			.RestoreDefault(this);
	Cam->Color				.RestoreDefault(this);
	Cam->Vivid				.RestoreDefault(this);
	Cam->Vividation			.RestoreDefault(this);
	Cam->Gamma				.RestoreDefault(this);
	Cam->WhiteBalance		.RestoreDefault(this);
	Cam->Reflection			.RestoreDefault(this);
	Cam->Gain				.RestoreDefault(this);
	Cam->Zoom				.RestoreDefault(this);
	Cam->Focus				.RestoreDefault(this);
	Cam->Exposure			.RestoreDefault(this);
	Cam->Iris				.RestoreDefault(this);
	Cam->Pan				.RestoreDefault(this);
	Cam->Tilt				.RestoreDefault(this);
	Cam->Rotation			.RestoreDefault(this);
	Cam->PowerlineFrequency	.RestoreDefault(this);
}

PropertyItem	*LibWMFCamera::GetBrightness(void)	{	return (Cam!=NULL)?(&Cam->Brightness	):NULL;		}
PropertyItem	*LibWMFCamera::GetContrast(void)	{	return (Cam!=NULL)?(&Cam->Contrast		):NULL;		}
PropertyItem	*LibWMFCamera::GetColor(void)		{	return (Cam!=NULL)?(&Cam->Color			):NULL;		}
PropertyItem	*LibWMFCamera::GetVivid(void)		{	return (Cam!=NULL)?(&Cam->Vivid			):NULL;		}
PropertyItem	*LibWMFCamera::GetVividation(void)	{	return (Cam!=NULL)?(&Cam->Vividation	):NULL;		}
PropertyItem	*LibWMFCamera::GetGamma(void)		{	return (Cam!=NULL)?(&Cam->Gamma			):NULL;		}
PropertyItem	*LibWMFCamera::GetWhiteBalance(void){	return (Cam!=NULL)?(&Cam->WhiteBalance	):NULL;		}
PropertyItem	*LibWMFCamera::GetReflection(void)	{	return (Cam!=NULL)?(&Cam->Reflection	):NULL;		}
PropertyItem	*LibWMFCamera::GetGain(void)		{	return (Cam!=NULL)?(&Cam->Gain			):NULL;		}
PropertyItem	*LibWMFCamera::GetZoom(void)		{	return (Cam!=NULL)?(&Cam->Zoom			):NULL;		}
PropertyItem	*LibWMFCamera::GetFocus(void)		{	return (Cam!=NULL)?(&Cam->Focus			):NULL;		}
PropertyItem	*LibWMFCamera::GetExposure(void)	{	return (Cam!=NULL)?(&Cam->Exposure		):NULL;		}
PropertyItem	*LibWMFCamera::GetIris(void)		{	return (Cam!=NULL)?(&Cam->Iris			):NULL;		}
PropertyItem	*LibWMFCamera::GetPan(void)			{	return (Cam!=NULL)?(&Cam->Pan			):NULL;		}
PropertyItem	*LibWMFCamera::GetTilt(void)		{	return (Cam!=NULL)?(&Cam->Tilt			):NULL;		}
PropertyItem	*LibWMFCamera::GetRotation(void)	{	return (Cam!=NULL)?(&Cam->Rotation		):NULL;		}
PropertyItemPowerlineFrequency	*LibWMFCamera::GetPowerlineFrequency(void){	return (Cam!=NULL)?(&Cam->PowerlineFrequency):NULL;		}

bool	LibWMFCamera::GetMirrorX(void)		{	return	(Cam!=NULL)?Cam->CamProp.MirrorX:false;		}
bool	LibWMFCamera::GetMirrorY(void)		{	return	(Cam!=NULL)?Cam->CamProp.MirrorY:false;		}
int		LibWMFCamera::GetRotationAngle(void){	return	(Cam!=NULL)?Cam->CamProp.RotationAngle:0;	}
bool	LibWMFCamera::GetMonoChrome(void)	{	return	(Cam!=NULL)?Cam->CamProp.MonoChrome:false;	}

void	LibWMFCamera::SetMirrorX(bool b)			{	if(Cam!=NULL)Cam->CamProp.MirrorX=b;			}
void	LibWMFCamera::SetMirrorY(bool b)			{	if(Cam!=NULL)Cam->CamProp.MirrorY=b;			}
void	LibWMFCamera::SetRotationAngle(int angle)	{	if(Cam!=NULL)Cam->CamProp.RotationAngle=angle;	}
void	LibWMFCamera::SetMonoChrome(bool b)			{	if(Cam!=NULL)Cam->CamProp.MonoChrome=b;			}

bool	LibWMFCamera::Convert(void)
{
	return Cam->Convert(Cam->ImageBuff2,(const BYTE *)Cam->mCaptureBuffer,Cam->mTotalBuffByte);
}
//ImageBuffer	*LibWMFCamera::GetBuff(int n)
//{
//	return Cam->ImageBuff[n];
//}
	
bool	LibWMFCamera::GetBuff(ImageBuffer *Buff[3])
{
	return Cam->GetBuff(Buff);
}

bool	LibWMFCamera::SwapBuff(ImageBuffer *Buff[3])
{
	return Cam->SwapBuff(Buff);
}

ImageBuffer	*LibWMFCamera::GetBuffR(int n)
{
	return Cam->ImageBuff3[n];
}
void	LibWMFCamera::LockBuff(void)
{
	if(Cam!=NULL)	Cam->LockBuff();
}

void	LibWMFCamera::UnlockBuff(void)
{
	if(Cam!=NULL)	Cam->UnlockBuff();
}

BYTE	*LibWMFCamera::GetMJPegTmpBuff(void)
{
	return Cam->MJPegTmpBuff;
}
void	LibWMFCamera::ReallocXY(int XLen ,int YLen)
{
	GetLayersBase()->LockWChangingDataStructure();
	Cam->ReallocXY(XLen ,YLen);
	GetLayersBase()->UnlockChangingDataStructure();
}
void	LibWMFCamera::SetCapturedTime(void)
{
	DWORD	t=::GetComputerMiliSec();
	DWORD	d=t-LastCapturedTime;
	if(d<300){
		SpanMiliSec[SpanMiliSecPoint]=d;
		SpanMiliSecPoint++;
		if(SpanMiliSecPoint>=sizeof(SpanMiliSec)/sizeof(SpanMiliSec[0])){
			SpanMiliSecPoint=0;
		}
		SpanMiliSecCount++;
		if(SpanMiliSecCount>=sizeof(SpanMiliSec)/sizeof(SpanMiliSec[0])){
			SpanMiliSecCount=sizeof(SpanMiliSec)/sizeof(SpanMiliSec[0]);
		}
	}
	LastCapturedTime=t;
}
double	LibWMFCamera::GetAverageSpanTime(void)
{
	DWORD	D=0;
	for(int i=0;i<SpanMiliSecCount;i++){
		D+=SpanMiliSec[i];
	}
	if(SpanMiliSecCount<2)
		return 33;
	return D/((double)SpanMiliSecCount);
}
HRESULT	LibWMFCamera::GetErrorCode(void)
{
	if(Cam==NULL)
		return 0;
	return Cam->mErrorCode;
}

bool	LibWMFCamera::IsEnableRingBuffer(void)
{
	if(Cam!=NULL){
		return Cam->EnableRingBuffer;
	}
	return false;
}
bool	LibWMFCamera::IsRingBuferCaptured(void)
{
	if(Cam!=NULL){
		if(Cam->EnableRingBuffer==true){
			//Cam->MutexRb.lock();
			if (Cam->RbCaptured>0) {
				Cam->MutexRb.lock();
				Cam->RbCaptured--;
				Cam->MutexRb.unlock();
				return true;
			}
			//Cam->MutexRb.unlock();
		}
	}
	return false;
}
void	LibWMFCamera::RingConvert(void)
{
	if(Cam!=NULL){
		Cam->RingConvert();
	}
}

void	LibWMFCamera::SignalCaptured(void)
{
	EmitSignalCaptured();
}
/*
internal void SetPowerLineFrequency()
{

object source = null;
Guid iid = typeof(IBaseFilter).GUID;
Device.capDevice.Mon.BindToObject(null, null, ref iid, out source);
theDevice = (IBaseFilter)source;

Guid KSNODETYPE_VIDEO_PROCESSING = new Guid("DFF229E5-F70F-
11D0-B917-00A0C9223196");

IKsTopologyInfo iKsTopologyInfo = theDevice as IKsTopologyInfo;
int pdwNumNodes;
iKsTopologyInfo.get_NumNodes(out pdwNumNodes);
for (int i = 0; i < pdwNumNodes; i++)
{
Guid pNodeType;
int hr = iKsTopologyInfo.get_NodeType(i, out pNodeType);
if (pNodeType == KSNODETYPE_VIDEO_PROCESSING)
{
object ppvObject;
hr = iKsTopologyInfo.CreateNodeInstance(i, typeof(IVideoProcAmp).GUID, out
ppvObject);
IVideoProcAmp amp = (IVideoProcAmp)ppvObject;

int pMin, pMax, pSteppingDelta, pDefault;
VideoProcAmpFlags pFlags;

amp.getRange_PowerlineFrequency(out pMin,
out pMax,
out pSteppingDelta,
out pDefault,
out pFlags);

amp.put_PowerlineFrequency(1, VideoProcAmpFlags.Manual);
Marshal.ReleaseComObject(ppvObject);
}
}
Marshal.ReleaseComObject(theDevice);
theDevice = null;
}

*/