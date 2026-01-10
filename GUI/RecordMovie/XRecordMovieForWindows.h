#pragma once

#include <QString>
#include <QImage>
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#include "XServiceForLayers.h"
#include "XMovieCommon.h"
#include <QMutex>
#include <QThread>

class	AddImageForMovie;
class	RecordMovie;
class	DataInPage;

class BmpClass : public ServiceForLayers
{
	friend	class	AddImageForMovie;
public:
    IMFMediaBuffer *pBuffer;
    DWORD           cbBufferSize;
	IMFSample		*pSample;

	AddImageForMovie	*Parent;
	RecordMovie			*RecordParent;
	DWORD				AddedMiliSec;
	HRESULT				Result;

	BmpClass(AddImageForMovie *p,RecordMovie	*RP,LayersBase *base);
	virtual	~BmpClass(void);

	bool	AddImage(void);
	void	AllocateBuff(void);

private:

	void	AddImageRGB(DataInPage* P);
};

// スマートポインタ簡略化のためのマクロ
template <class T> void SafeRelease(T **ppT) {
    if (*ppT) { (*ppT)->Release(); *ppT = NULL; }
}


class	AddImageForMovie : public QThread,public ServiceForLayers
{
	Q_OBJECT

	friend	class	WriteFileForMovieThread;
	friend	class BmpClass;

	RecordMovie		*Parent;

	IMFSinkWriter *pSinkWriter = nullptr;
    DWORD			streamIndex = 0;
    long long		frameDuration = 0; // 100ナノ秒単位
    long long		currentSampleTime = 0;
    int				videoWidth = 0;
    int				videoHeight = 0;
    bool			isOpened = false;

	int		SavedFPS	;
	int		SavedBitRate;

	int		image_width;
	int		image_height;
	double	ZoomRate;

public:
	volatile	bool	Terminated;
	volatile	bool	Running;
	int			Error;
	BmpClass	**BmpData;
	int			MaxImageCount;

	double		SparseMilisec;
	int64		RunningMilisec;
	DWORD		StartMilisec;
	int			AddedCount;
	int			WrittenCount;
	DWORD		LastMilisec;

	QString		MovieFileName;

	int		BmpIndexR;
	int		BmpIndexW;
	QMutex	MutexCounter;
	int		BmpStockCount;

public:
	AddImageForMovie(LayersBase *base ,RecordMovie *p);
	virtual	~AddImageForMovie(void);

	void	Initialize(void);

	void	AllocateBuff(void);
	void	ReleaseBuff(void);
	void	Close(void);
	void	AddImage(void);

	bool	StartRecording(const QString &filename
							, int width
							, int height
							, int fps
							, int bitrate);
	bool	RestartRecording(void);
	bool	HaltRecording(void);
	bool	EndRecording(void);

	virtual	void	run();
signals:
	void	SignalMemoryOver();
	void	SignalWriteError();

private:
	bool	InitializeSinkWriter(const QString &filename, int fps, int bitrate);
	bool	WriteFrame(void);
};

class MFSinkWriter
{
public:
    MFSinkWriter();
    ~MFSinkWriter();

    // 初期化 (ファイル名, 幅, 高さ, FPS, ビットレート)
    bool open(const QString &filename, int width, int height, int fps, int bitrate = 5000000);
    
    // フレーム書き込み
    bool writeFrame(const QImage &img);
    
    // 終了処理
    void close();

private:


    bool initializeSinkWriter(const QString &filename, int fps, int bitrate);
};

