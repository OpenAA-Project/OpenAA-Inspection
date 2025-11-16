#pragma once

#include <Windows.h>
#include <vfw.h>
#include <QMutex>
#include <QThread>
#include <QString>
#include <QFile>
#include "XServiceForLayers.h"
//#ifdef HAVE_AV_CONFIG_H
//#undef HAVE_AV_CONFIG_H
//#endif
#include "XMovieCommon.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/mathematics.h"
};

const	int	MaxTimeCount=30*3600*2;

class	WriteFileForMovieThread;
class	RecordMovie;
class	AddImageForMovie;
class	DataInPage;

#define	AVError_Success		0
#define	AVError_Codec		1
#define	AVError_Open		2
#define	AVError_Write		3

class BmpClass : public ServiceForLayers
{
public:
	AddImageForMovie	*Parent;
	RecordMovie				*RecordParent;
	DWORD		AddedMiliSec;
	BYTE		*BmpData;
	AVFrame		*picture;
	int			BmpByte;
	AVPacket	*pkt;

	BmpClass(AddImageForMovie *p,RecordMovie	*RP,LayersBase *base);
	virtual	~BmpClass(void);

	bool	AddImage(void);
	void	AllocateBuff(void);

	bool	WriteFrame(QFile *AVFile,AVCodecContext	*Context ,int &Error);
	bool	WriteFrameNull(QFile *AVFile,AVCodecContext	*Context ,int &Error);

private:
	void	AddImageYUV(DataInPage* P);
	void	AddImageRGB(DataInPage* P);
};


class	AddImageForMovie : public QThread,public ServiceForLayers
{
	Q_OBJECT

	friend	class	WriteFileForMovieThread;

	RecordMovie	*Parent;
	int		MaxImageCount;
	EnumAVFormat SavedAVFormat;
	double		SavedFPS;
	int			SavedQuality;
public:
	//EnumAVFormat	AVFormat;

	bool	Terminated;
	int		image_width;
	int		image_height;
	double	FPS;
	double	ZoomRate;
	int		MovieQuality;	//-1 , or 0-100

	const	AVCodec	*codec;
	AVCodecContext	*Context;
	BITMAPINFOHEADER BmpInfoHeader;
	AVPixelFormat	PixFormat;
	QFile			*AVFile;

	HRESULT			AVIHandle		;
	PAVIFILE		AVIFile;
	PAVISTREAM		AVIStreamHandle	;
	AVISTREAMINFO	AVISInfo;
	BITMAPINFOHEADER AVIBMi;

	volatile	bool	Running;
	int			Error;
	BmpClass	**BmpData;
	LONG		dwIndex;
	int			BmpWidth;
	int			XPosDim[16000];
	double		SparseMilisec;
	int64		RunningMilisec;
	DWORD		StartMilisec;
	int			AddedCount;
	int			WrittenCount;
	DWORD		LastMilisec;
	int			LastCount;
	int			CountOfWrittenFrames;
	int			MaxCountOfWrittenFrames;
	QString		MovieFileName;
	QMutex		MutexSwitchFile;

	int		BmpIndexR;
	int		BmpIndexW;
	QMutex	MutexCounter;
	int		BmpStockCount;

	int		FileNumber;

public:
	AddImageForMovie(LayersBase *base ,RecordMovie *p);
	virtual	~AddImageForMovie(void);

	void	Initialize(void);

	void	AllocateBuff(void);
	void	ReleaseBuff(void);

	void	AddImage(void);
	void	MakeBmpHeader(void);

	bool	StartRecording(EnumAVFormat	_AVFormat,const QString &AVIFileName
							,double FPS ,int quality);
	bool	RestartRecording(const QString &AVIFileName ,double FPS,int quality);
	void	StopRecording(void);
	void	EndRecording(void);

	bool	Write(void);
	bool	WriteLast(void);

	EnumAVFormat	GetAVFormat(void);

	virtual	void	run();
signals:
	void	SignalMemoryOver();
	void	SignalWriteError();
};

