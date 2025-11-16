#if	!defined(LibWMFCamera_h)
#define	LibWMFCamera_h

#include "XCameraHandle.h"
#include "jpeglib.h"
#include "turbojpeg.h"
#include "XCamUSBCommon.h"


class	CaptureClass;
class	ImageBuffer;
class	QIODevice;
class	CameraReqInfo;

enum	EnumMediaType
{
	_EMT_None
	,_EMT_RGB32
	,_EMT_RGB24
	,_EMT_YUY2
	,_EMT_NV12
	,_EMT_MJPG
};

struct	StructMediaType
{
	int				Index;
	int				Width,Height;
	EnumMediaType	ConvertType;
	int				FPS;

	bool	IsEqual(struct StructMediaType &src){
		if(Index		==src.Index
		&& Width		==src.Width
		&& Height		==src.Height
		&& ConvertType	==src.ConvertType
		&& FPS			==src.FPS)
			return true;
		return false;
	}
};


class	PropertyItem
{
	friend	class	LibWMFCamera;
public:
	CAPTURE_PROPETIES	Prop;
	float	CurrentValue;
	long	MinValue;
	long	MaxValue;
	long	Step;
	long	DefaultValue;
	long	CapsFlags;
	bool	ModeAuto;

	PropertyItem(CAPTURE_PROPETIES e=CAPTURE_PROP_MAX);

	bool setProperty(LibWMFCamera *Cam);
	bool getProperty(LibWMFCamera *Cam);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	RestoreDefault(LibWMFCamera *Cam);

	PropertyItem	&operator=(PropertyItem &src);
};


class	PropertyItemPowerlineFrequency
{
	friend	class	LibWMFCamera;
public:
	CAPTURE_PROPETIES	Prop;
	long	CurrentValue;
	long	MinValue;
	long	MaxValue;
	long	Step;
	long	DefaultValue;
	long	CapsFlags;
	bool	ModeAuto;

	PropertyItemPowerlineFrequency(CAPTURE_PROPETIES e=CAPTURE_POWERLINEFREQUENCY);

	bool setProperty(LibWMFCamera *Cam);
	bool getProperty(LibWMFCamera *Cam);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	RestoreDefault(LibWMFCamera *Cam);

	PropertyItemPowerlineFrequency	&operator=(PropertyItemPowerlineFrequency &src);
};


class	LibWMFCamera : public CameraHandle
{
	friend	class	PropertyItem;
	friend	class	PropertyItemPowerlineFrequency;

	CaptureClass	*Cam;

	DWORD	LastCapturedTime;
	DWORD	SpanMiliSec[100];
	int		SpanMiliSecPoint;
	int		SpanMiliSecCount;

public:
	tjhandle DecHndle;
	bool	CapturedBeforeImaging;


	LibWMFCamera(int CamNo ,LayersBase *Base ,int DeviceNo ,struct DeviceInfo &_Dev);
	virtual	~LibWMFCamera(void);

	bool	Initial(void);

	int		EnumMediaType(struct StructMediaType Dim[] ,int MaxDim);
	bool	SetMediaType(struct	StructMediaType &Type);
	bool	GetMediaType(struct	StructMediaType &Type);
	bool	SetFastestSize(int XLen ,int YLen);

	bool	IsCaptured(void);
	bool	IsErrored(void);

	int		GetVendorID(void);
	int		GetProductID(void);
	const char	*GetDeviceName(void);
	int		GetDeviceNo(void);
	void	SignalCaptured(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool setProperty(void);
	bool getProperty(void);

	PropertyItem	*GetBrightness(void);
	PropertyItem	*GetContrast(void);
	PropertyItem	*GetColor(void);
	PropertyItem	*GetVivid(void);
	PropertyItem	*GetVividation(void);
	PropertyItem	*GetGamma(void);
	PropertyItem	*GetWhiteBalance(void);
	PropertyItem	*GetReflection(void);
	PropertyItem	*GetGain(void);
	PropertyItem	*GetZoom(void);
	PropertyItem	*GetFocus(void);
	PropertyItem	*GetExposure(void);
	PropertyItem	*GetIris(void);
	PropertyItem	*GetPan(void);
	PropertyItem	*GetTilt(void);
	PropertyItem	*GetRotation(void);
	PropertyItemPowerlineFrequency	*GetPowerlineFrequency(void);

	void	RestoreDefault(void);

	bool	GetMirrorX(void);
	bool	GetMirrorY(void);
	int		GetRotationAngle(void);
	bool	GetMonoChrome(void);

	void	SetMirrorX(bool b);
	void	SetMirrorY(bool b);
	void	SetRotationAngle(int angle);
	void	SetMonoChrome(bool b);

	bool	Convert(void);
	//ImageBuffer	*GetBuff(int n);
	bool	GetBuff(ImageBuffer *Buff[3]);
	bool	SwapBuff(ImageBuffer *Buff[3]);
	ImageBuffer	*GetBuffR(int n);
	void	LockBuff(void);
	void	UnlockBuff(void);
	void	ReallocXY(int XLen ,int YLen);

	BYTE	*GetMJPegTmpBuff(void);
	HRESULT	GetErrorCode(void);

	void	SetCapturedTime(void);
	double	GetAverageSpanTime(void);

	CaptureClass	*GetCameraClass(void)	{	return Cam;	}

	bool	IsEnableRingBuffer(void);
	bool	IsRingBuferCaptured(void);
	void	RingConvert(void);
};

struct DeviceInfo
{
	int	VendorID;
	int	ProductID;
	char	DeviceName[256];
};

extern	bool	InitialUVCSystem(void);
extern	int		GetDeviceCount(struct DeviceInfo DevDim[100],QStringList &CameraNameList);

#endif