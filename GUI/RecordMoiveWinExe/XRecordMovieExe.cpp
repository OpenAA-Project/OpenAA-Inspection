/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XRecordMovieExe.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "RecordMovie.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

#ifdef Q_OS_WIN
// Libraries for linking (Can be specified in code for MSVC)
#pragma comment(lib, "Vfw32.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#endif

//=====================================================================================

AddImageForMovie::AddImageForMovie(int page ,QObject *obj)
	:QThread(obj),UsePage(page)
{
	Terminated	=false;
	Running		=false;
	Error		=0;
	image_width	=0;
	image_height=0;
	ZoomRate	=1.0;
	FrameCount	=0;
	LoopCount	=0;

	InitialOpened	=false;

#ifdef Q_OS_WIN
	m_pDXGIManager=NULL;
	m_pD3D11Device=NULL;
	pBuffer		=NULL;
	pSample		=NULL;
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    HRESULT hr = MFStartup(MF_VERSION);
#else
    m_ffmpegProcess = NULL;
#endif

	MovieFileName =/**/"TestMovie.mp4";

	TM.setInterval(2000);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

AddImageForMovie::~AddImageForMovie(void)
{
	if(Socket){
		Socket->close();
		Socket->deleteLater();
		Socket=NULL;
	}

	if(SharedMemForMovie!=NULL){
		SharedMemForMovie->detach();
		delete	SharedMemForMovie;
		SharedMemForMovie=NULL;
	}

	Close();

#ifdef Q_OS_WIN
    MFShutdown();
    CoUninitialize();
#endif
}

void    AddImageForMovie::SlotTimeout()
{
	Socket = new MovieSocket(this);
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer(QString(/**/"RecordMovieServer")+QString::number(UsePage));

	SharedMemForMovie = NULL;
	Semaphore = new QSystemSemaphore(QString(/**/"RecordMovieSem")+QString::number(UsePage),0, QSystemSemaphore::Create);

	QThread::msleep(1000);

	start();
}

void AddImageForMovie::Close(void)
{
#ifdef Q_OS_WIN
    if (pSinkWriter) {
        pSinkWriter->Finalize(); // Important: Close the file
        SafeRelease(&pSinkWriter);
        pSinkWriter=NULL;
    }
	SafeRelease(&pBuffer);
	SafeRelease(&pSample);
#else
    if (m_ffmpegProcess) {
        m_ffmpegProcess->closeWriteChannel(); // Close standard input to terminate ffmpeg normally
        m_ffmpegProcess->waitForFinished(3000);
        delete m_ffmpegProcess;
        m_ffmpegProcess = nullptr;
    }
#endif

    isOpened = false;
}

bool AddImageForMovie::StartRecording(wchar_t *filename, int width, int height, int fps, int bitrate)
{
	Close();

	FPS	=fps;
	image_width		= width;
	image_height	= height;
	BitRate			= bitrate;
	MovieFileName	= QString::fromWCharArray(filename);

	videoWidth = image_width;
	videoHeight = image_height;
	// Time per frame (Unit: 100 nanoseconds)
	frameDuration = 10 * 1000 * 1000 / FPS;
	currentSampleTime = 0;
	FrameCount		=0;

#ifdef Q_OS_WIN
	if(InitializeSinkWriter(filename, FPS, BitRate)==false) {
		InitialOpened=false;
		QMessageBox::warning(NULL,"Error","Failed to create video.");
	}
	else{
		isOpened = true;
		InitialOpened=true;

		SharedMemForMovie->lock();
		void	*BuffTop=SharedMemForMovie->data();
		struct RecordHeaderStruct	*HeaderPtr=(struct RecordHeaderStruct *)BuffTop;
		HeaderPtr->Opened=true;
		SharedMemForMovie->unlock();
	}
#else
    // Linux: Start ffmpeg process and pipe raw data (RGB32 = bgra)
    m_ffmpegProcess = new QProcess(this);
    QStringList args;
    args << "-y" 
         << "-f" << "rawvideo" 
         << "-pix_fmt" << "bgra" // Corresponds to QImage::Format_RGB32 (Little Endian environment)
         << "-s" << QString("%1x%2").arg(videoWidth).arg(videoHeight)
         << "-r" << QString::number(FPS)
         << "-i" << "-" // Receive from standard input
         << "-c:v" << "libx264" 
         << "-pix_fmt" << "yuv420p" // Standard compatible format for H.264
         << "-b:v" << QString::number(BitRate)
         << MovieFileName;

    m_ffmpegProcess->start("ffmpeg", args);
    if (!m_ffmpegProcess->waitForStarted(3000)) {
        InitialOpened=false;
        QMessageBox::warning(NULL, "Error", "Failed to start ffmpeg.");
    } else {
        isOpened = true;
        InitialOpened = true;

        SharedMemForMovie->lock();
		void	*BuffTop=SharedMemForMovie->data();
		struct RecordHeaderStruct	*HeaderPtr=(struct RecordHeaderStruct *)BuffTop;
		HeaderPtr->Opened=true;
		SharedMemForMovie->unlock();
    }
#endif
	return true;
}

#ifdef Q_OS_WIN
// Helper for creating D3D11 device and DXGI manager
HRESULT AddImageForMovie::createD3DManager()
{
    HRESULT hr = S_OK;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11DeviceContext *pContext = nullptr;

    hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 
                           D3D11_CREATE_DEVICE_VIDEO_SUPPORT, NULL, 0, 
                           D3D11_SDK_VERSION, &m_pD3D11Device, &featureLevel, &pContext);
    if (FAILED(hr)) return hr;

    // Enable multithread protection
    ID3D11Multithread *pMultithread = nullptr;
    if (SUCCEEDED(m_pD3D11Device->QueryInterface(__uuidof(ID3D11Multithread), (void**)&pMultithread))) {
        pMultithread->SetMultithreadProtected(TRUE);
        pMultithread->Release();
    }

    UINT token;
    hr = MFCreateDXGIDeviceManager(&token, &m_pDXGIManager);
    if (SUCCEEDED(hr)) {
        hr = m_pDXGIManager->ResetDevice(m_pD3D11Device, token);
    }

    if (pContext) pContext->Release();
    return hr;
}

bool AddImageForMovie::InitializeSinkWriter(wchar_t *filename, int fps, int bitrate)
{
    HRESULT hr = S_OK;

	hr = createD3DManager();

    // Create Sink Writer
    IMFAttributes *pAttr = nullptr;
    MFCreateAttributes(&pAttr, 1);
    pAttr->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE); // Enable hardware acceleration
	pAttr->SetUnknown(MF_SINK_WRITER_D3D_MANAGER, m_pDXGIManager);
	pAttr->SetUINT32(MF_LOW_LATENCY, TRUE);

    hr = MFCreateSinkWriterFromURL(filename, NULL, pAttr, &pSinkWriter);
    SafeRelease(&pAttr);
    if (FAILED(hr)) return false;
	
    // 1. Set output media type (H.264)
    IMFMediaType *pMediaTypeOut = nullptr;
 	UINT32 stride = videoWidth * 4; 
	MFCreateMediaType(&pMediaTypeOut);
    pMediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    pMediaTypeOut->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
    pMediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, bitrate);
    pMediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
    MFSetAttributeSize(pMediaTypeOut, MF_MT_FRAME_SIZE, videoWidth, videoHeight);
    MFSetAttributeRatio(pMediaTypeOut, MF_MT_FRAME_RATE, fps, 1);
    MFSetAttributeRatio(pMediaTypeOut, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);

    hr = pSinkWriter->AddStream(pMediaTypeOut, &streamIndex);
    SafeRelease(&pMediaTypeOut);
    if (FAILED(hr)) return false;

    // 2. Set input media type (RGB32)
    // By specifying RGB here, MF automatically converts it to H.264 (NV12)
    IMFMediaType *pMediaTypeIn = nullptr;
    MFCreateMediaType(&pMediaTypeIn);
    pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32); // Corresponds to QImage::Format_RGB32

    pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
    MFSetAttributeSize(pMediaTypeIn, MF_MT_FRAME_SIZE, videoWidth, videoHeight);
    MFSetAttributeRatio(pMediaTypeIn, MF_MT_FRAME_RATE, fps, 1);
    MFSetAttributeRatio(pMediaTypeIn, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
	pMediaTypeIn->SetUINT32(MF_MT_DEFAULT_STRIDE, videoWidth * 4);

    // [Fix B] Add sample size and fixed size flags (Prone to errors if omitted)
    pMediaTypeIn->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, TRUE);
    pMediaTypeIn->SetUINT32(MF_MT_FIXED_SIZE_SAMPLES, TRUE);
    pMediaTypeIn->SetUINT32(MF_MT_SAMPLE_SIZE, videoWidth * videoHeight * 4); // Number of bytes per frame

    hr = pSinkWriter->SetInputMediaType(streamIndex, pMediaTypeIn, NULL);
    SafeRelease(&pMediaTypeIn);
    if (FAILED(hr)) return false;

    // Start writing
    hr = pSinkWriter->BeginWriting();
	Running=true;

    return SUCCEEDED(hr);
}
#endif

bool AddImageForMovie::RestartRecording(void)
{
#ifdef Q_OS_WIN
	if (!isOpened || !pSinkWriter) return false;
#else
    if (!isOpened || !m_ffmpegProcess) return false;
#endif
	Running=true;
	return true;
}

bool AddImageForMovie::HaltRecording(void)
{
	Running=false;
    return true;
}

bool AddImageForMovie::EndRecording(void)
{
	Close();
	return true;
}

bool AddImageForMovie::WriteFrame(void)
{
#ifdef Q_OS_WIN
    if (!isOpened || !pSinkWriter) return false;
	HRESULT hr = S_OK;

	SharedMemForMovie->lock();
	void	*BuffTop=SharedMemForMovie->data();
	struct RecordHeaderStruct	*H=(struct RecordHeaderStruct *)BuffTop;
	BYTE	*ImgData=((BYTE *)BuffTop)+sizeof(struct RecordHeaderStruct);

	const DWORD cbWidth = 4 * videoWidth; 
    const DWORD cbBuffer = cbWidth * videoHeight;

    // 1. Create memory buffer
	pBuffer = new UnownedMediaBuffer(const_cast<BYTE*>(ImgData), cbBuffer);
	SafeRelease(&pSample);
	hr = MFCreateSample(&pSample);

    if (SUCCEEDED(hr)) {
        hr = pSample->AddBuffer(pBuffer);
    }

	// 5. Set timestamp
	hr = pSample->SetSampleTime(H->CurrentTime*10000);
	hr = pSample->SetSampleDuration(H->Duration*10000);

    // 6. Send to writer (Encode)
    if(SUCCEEDED(hr)) {
        hr = pSinkWriter->WriteSample(streamIndex, pSample);
		if(SUCCEEDED(hr)) {
			FrameCount++;
		}
    }

	SharedMemForMovie->unlock();

	SafeRelease(&pSample);
    SafeRelease(&pBuffer);
#else
    if (!isOpened || !m_ffmpegProcess) return false;
    
    SharedMemForMovie->lock();
	void	*BuffTop=SharedMemForMovie->data();
	BYTE	*ImgData=((BYTE *)BuffTop)+sizeof(struct RecordHeaderStruct);

    const int cbWidth = 4 * videoWidth; 
    const int cbBuffer = cbWidth * videoHeight;

    qint64 written = m_ffmpegProcess->write((const char*)ImgData, cbBuffer);
    if (written == cbBuffer) {
        FrameCount++;
    }
    
    SharedMemForMovie->unlock();
#endif
	return true;
}

void AddImageForMovie::SlotReadyRead()
{
	void	*BuffTop;
	struct RecordHeaderStruct	*H;
	while (Socket->bytesAvailable() >= sizeof(struct RecordStruct)) {
		struct RecordStruct Cmd;
		Socket->read((char *)&Cmd,sizeof(Cmd));
		struct RecordStruct ACmd;
		switch(Cmd.Cmd) {
		case RecordStruct::_ReqDetach:
			if(SharedMemForMovie!=NULL){
				SharedMemForMovie->detach();
				delete	SharedMemForMovie;
				SharedMemForMovie = NULL;
			}
			ACmd.Cmd = RecordStruct::_Ack;
			Socket->write((char *)&ACmd,sizeof(ACmd));
			Socket->flush();
			break;
		case RecordStruct::_ReqAttach:
			if(SharedMemForMovie==NULL){
				SharedMemForMovie = new QSharedMemory(QString(/**/"RecordMovieMem")+QString::number(UsePage));
			}
			if(SharedMemForMovie->attach(QSharedMemory::ReadWrite)==false){
				qDebug() << "Shared Memory Attach Error:" << SharedMemForMovie->errorString();
			}
			ACmd.Cmd = RecordStruct::_Ack;
			Socket->write((char *)&ACmd,sizeof(ACmd));
			Socket->flush();
			break;
		case RecordStruct::_StartRecording:
			BuffTop=SharedMemForMovie->data();
			H=(struct RecordHeaderStruct *)BuffTop;
			StartRecording(H->FileName
							,Cmd.MovieXSize
							,Cmd.MovieYSize
							,static_cast<int>(Cmd.FPS)
							,Cmd.Quality);
			ACmd.Cmd = RecordStruct::_Ack;
			Socket->write((char *)&ACmd,sizeof(ACmd));
			Socket->flush();
			break;
		case RecordStruct::_EndRecording:
			EndRecording();
			break;
		case RecordStruct::_RestartRecording:
			RestartRecording();
			break;
		case RecordStruct::_HaltRecording:
			HaltRecording();
			break;
		}
	}
}

void AddImageForMovie::run()
{
	while (Terminated==false){
		if(Semaphore->acquire()==false){
			break;
		}
		LoopCount++;
		if(WriteFrame()==false){
			break;
		}
	}
}