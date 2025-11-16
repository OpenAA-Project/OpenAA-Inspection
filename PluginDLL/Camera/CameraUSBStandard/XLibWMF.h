#if	!defined(XLibWMF_H)
#define	XLibWMF_H

//#include <sal.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>

#include <shlwapi.h> // QITAB and friends
#include <objbase.h> // IID_PPV_ARGS and friends
#include <dshow.h> // IAMVideoProcAmp and friends
#define	_USE_MATH_DEFINES
#include <math.h>
#include "LibWMFCamera.h"
#include <QMutex>
#include <QThread>

class	QIODevice;
class	ImageBuffer;

#define	CountOfRingBuffer	8

typedef void(*IMAGE_TRANSFORM_FN)(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);
enum	EnumMediaType;

struct ConversionFunction
{
	GUID               mSubtype;
	IMAGE_TRANSFORM_FN mXForm;
	EnumMediaType		MType;
};

void TransformImage_RGB24(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);

void TransformImage_RGB32(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);

void TransformImage_YUY2(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);

void TransformImage_NV12(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);

void TransformImage_MJPG(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	);


class CameraRingBuffer
{
public:
	QMutex	Mutex;
	BYTE	*RawData;
	int32	RawDataLen;
	int		XLen;
	int		YLen;
	ImageBuffer	*ImageBuff[4];
	volatile	bool	DoneConverted;
	volatile	bool	Swapped;
public:
	CameraRingBuffer(void);
	~CameraRingBuffer(void);

	void	ReallocXY(int XLen ,int YLen);
};



extern ConversionFunction gFormatConversions[];
extern const DWORD gConversionFormats;

struct StructMediaType;

class CaptureClass : public IMFSourceReaderCallback ,public QThread
{
public:
	struct DeviceInfo	Dev;
	LibWMFCamera		*Parent;
	struct StructMediaType RealMediaDim[256];
	int					RealMediaDimNumb;
	struct StructMediaType MediaDim[256];
	int					MediaDimNumb;
	int					SampleError;
	bool				ContinueSampling;
	bool				AckContinueSampling;
	bool				FirstThread;


	volatile	bool	EnableRingBuffer;
	CameraRingBuffer	RingBuffer[CountOfRingBuffer];
	volatile	int		RbRPoint;
	volatile	int		RbWPoint;
	volatile	int		RbCaptured;
	QMutex				MutexRb;
	
	CaptureClass(int DeviceNo ,LibWMFCamera *parent ,struct DeviceInfo &_Dev);
	virtual	~CaptureClass();

	STDMETHODIMP QueryInterface(REFIID aRiid, void** aPpv);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP OnReadSample(
		HRESULT aStatus,
		DWORD aStreamIndex,
		DWORD aStreamFlags,
		LONGLONG aTimestamp,
		IMFSample *aSample
		);
	STDMETHODIMP OnEvent(DWORD, IMFMediaEvent *);
	STDMETHODIMP OnFlush(DWORD);
	int escapiPropToMFProp(int aProperty);
	bool isFormatSupported(REFGUID aSubtype) const;
	HRESULT setConversionFunction(REFGUID aSubtype);
	HRESULT setVideoType(IMFMediaType *aType);
	bool	initCapture(void);
	void	deinitCapture();

	bool	SetMediaType(struct	StructMediaType &Type);
	//bool	Convert(void);
	bool	Convert(ImageBuffer *DstIBuff[4] ,const BYTE *SrcBuff, int SrcByte);
	void	RingConvert(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	long                    mRefCount;        // Reference count.
	CRITICAL_SECTION        mCritsec;

	IMFSourceReader         *mReader;
	IMFMediaSource			*mSource;

	LONG                    mDefaultStride;
	IMAGE_TRANSFORM_FN      mConvertFn;    // Function to convert the video to RGB32

	unsigned int			*mCaptureBuffer;
	BYTE					*MJPegTmpBuff;
	unsigned int			mCaptureBufferWidth, mCaptureBufferHeight;
	DWORD					mTotalBuffByte;
	int						mErrorLine;
	HRESULT					mErrorCode;
	int						mWhoAmI;
	unsigned int			*mBadIndex;
	unsigned int			mBadIndices;
	unsigned int			mMaxBadIndices;
	unsigned int			mUsedIndex;
	int						mRedoFromStart;
	volatile	int			Grabbed;
	volatile	bool		OnReading;
	volatile	int			Changed;
	int						StartCount;

	PropertyItem	Brightness;
	PropertyItem	Contrast;
	PropertyItem	Color;
	PropertyItem	Vivid;
	PropertyItem	Vividation;
	PropertyItem	Gamma;
	PropertyItem	WhiteBalance;
	PropertyItem	Reflection;
	PropertyItem	Gain;
	PropertyItem	Zoom;
	PropertyItem	Focus;
	PropertyItem	Exposure;
	PropertyItem	Iris;
	PropertyItem	Pan;
	PropertyItem	Tilt;
	PropertyItem	Rotation;
	PropertyItemPowerlineFrequency	PowerlineFrequency;

	struct	{
		struct	StructMediaType	CurrentType;

		bool	MirrorX;
		bool	MirrorY;
		int		RotationAngle;
		bool	MonoChrome;
	}CamProp;

	//ImageBuffer	*ImageBuff[4];
	ImageBuffer	*ImageBuff2[4];
	ImageBuffer	*ImageBuff3[4];
	QMutex		MutexBuff;

	void	LockBuff(void);
	void	UnlockBuff(void);
	void	ReallocXY(int XLen ,int YLen);

	bool	GetBuff(ImageBuffer *Buff[3]);
	bool	SwapBuff(ImageBuffer *Buff[3]);

	DWORD	SpanTime[200];
	DWORD	ConvTime[200];
	DWORD	LCTime[200];
	int		SpanTimePointer;
	int		LCCounter;
	DWORD	LastTime;

private:
	int		EnumMediaType(void);

private:
	virtual	void run()	override;
};


template <class T> class ScopedRelease
{
public:
	T *mVar;
	ScopedRelease(T * aVar)
	{
		mVar = aVar;
	}
	~ScopedRelease()
	{
		if (mVar != 0)
			mVar->Release();
	}
};

struct ChooseDeviceParam
{
	IMFActivate **mDevices;    // Array of IMFActivate pointers.
	UINT32      mCount;          // Number of elements in the array.
	UINT32      mSelection;      // Selected device, by array index.

	~ChooseDeviceParam()
	{
		unsigned int i;
		for (i = 0; i < mCount; i++)
		{
			if (mDevices[i])
				mDevices[i]->Release();
		}
		CoTaskMemFree(mDevices);
	}
};
class VideoBufferLock
{
public:
	VideoBufferLock(IMFMediaBuffer *aBuffer);
	~VideoBufferLock();
	HRESULT LockBuffer(
		LONG  aDefaultStride,    // Minimum stride (with no padding).
		DWORD aHeightInPixels,  // Height of the image, in pixels.
		BYTE  **aScanLine0,    // Receives a pointer to the start of scan line 0.
		LONG  *aStride          // Receives the actual stride.
		);
	void UnlockBuffer();

private:
	IMFMediaBuffer  *mBuffer;
	IMF2DBuffer     *m2DBuffer;

	BOOL            mLocked;
};
#endif
