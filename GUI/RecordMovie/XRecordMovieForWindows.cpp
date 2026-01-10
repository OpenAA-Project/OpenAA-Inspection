#include "XRecordMovieForWindows.h"
#include <QDebug>
#include <mfapi.h>
#include <mferror.h>
#include "RecordMovie.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

// リンク用ライブラリ (MSVCならコード内指定も可)
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

bool	GetMemoryInfo(
	 unsigned long		&dwMemoryLoad
	,unsigned long long	&ullTotalPhys
	,unsigned long long	&ullAvailPhys
	,unsigned long long	&ullTotalPageFile
	,unsigned long long	&ullAvailPageFile
	,unsigned long long	&ullTotalVirtual
	,unsigned long long	&ullAvailVirtual
	,unsigned long long	&ullAvailExtendedVirtual
	);


BmpClass::BmpClass(AddImageForMovie *p,RecordMovie *RP,LayersBase *base)
	:ServiceForLayers(base),Parent(p),RecordParent(RP)
{
	pBuffer		=NULL;
	cbBufferSize=0;
	pSample		=NULL;
	AddedMiliSec		=0;
}
BmpClass::~BmpClass(void)
{
	if(pSample!=NULL){
		SafeRelease(&pSample);
	}
	if(pBuffer!=NULL){
		SafeRelease(&pBuffer);
	}
}

void	BmpClass::AllocateBuff(void)
{
    // メディアバッファの作成
    const DWORD cbWidth = 4 * Parent->image_width;
    cbBufferSize = cbWidth * Parent->image_height;
    
    Result = MFCreateMemoryBuffer(cbBufferSize, &pBuffer);
	Result = MFCreateSample(&pSample);
}

bool	BmpClass::AddImage(void)
{
	if(pBuffer==NULL){
		return false;
	}
	AddedMiliSec	=::GetComputerMiliSec();
	if (Parent->SavedFPS > 0) {
		int page = RecordParent->GetTargetPage();
		if (page < 0)
			page = 0;
		if (page >= GetPageNumb())
			page = GetPageNumb();
		DataInPage* P = GetLayersBase()->GetPageData(page);

		AddImageRGB(P);

		return true;
	}
}

void	BmpClass::AddImageRGB(DataInPage* P)
{
	double	Z=1.0/Parent->ZoomRate;
	int	image_height	=Parent->image_height;
	int	image_width		=Parent->image_width;
	int	image_width2	=image_width/2;

    BYTE *pData = nullptr;
    Result = pBuffer->Lock(&pData, NULL, NULL);	
	if (SUCCEEDED(Result)) {
		GetLayersBase()->LockRChangingDataStructure();
		if (P->GetLayerNumb() >= 3) {
			ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
			ImageBuffer& G = P->GetLayerData(1)->GetTargetBuff();
			ImageBuffer& B = P->GetLayerData(2)->GetTargetBuff();
			int	DotPerLine	=R.GetWidth();
			int	MaxLines	=R.GetHeight();
			int32	AddedInt=(int)(Z*65536);
			int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
			#pragma omp parallel                             
			{                  
				/* Y */
				#pragma omp for
				for(int y=0;y<image_height;y++) {
					int	Y = y*Z;	//(image_height - y - 1)*Z;
					if(Y<MaxLines){
						BYTE* sR = R.GetYWithoutDepended(MaxLines-Y-1);
						BYTE* sG = G.GetYWithoutDepended(MaxLines-Y-1);
						BYTE* sB = B.GetYWithoutDepended(MaxLines-Y-1);
						BYTE	*d=&pData[y*image_width*4];
						int32	XAddedInt=0;
						for(int x=0;x<image_width;x++) {
							int	X=(XAddedInt)>>16;
							*(d+0)=sB[X];
							*(d+1)=sG[X];
							*(d+2)=sR[X];
							*(d+3)=0;
							d+=4;
							XAddedInt+=AddedInt;
						}
					}
				}
			}
		}
		else
		if (P->GetLayerNumb()==1) {
			ImageBuffer& R = P->GetLayerData(0)->GetTargetBuff();
			int	DotPerLine	=R.GetWidth();
			int	MaxLines	=R.GetHeight();
			int32	AddedInt=(int)(Z*65536);
			int	MaxX=min(R.GetWidth(),(int)(image_width*Z));
			#pragma omp parallel                             
			{                  
				/* Y */
				#pragma omp for
				for(int y=0;y<image_height;y++) {
					int	Y = y*Z;	//(image_height - y - 1)*Z;
					if(Y<MaxLines){
						BYTE* sR = R.GetYWithoutDepended(MaxLines-Y-1);
						BYTE	*d=&pData[y*image_width*3];
						int32	XAddedInt=0;
						for(int x=0;x<image_width;x++) {
							int	X=(XAddedInt)>>16;
							*(d+0)=sR[X];
							*(d+1)=sR[X];
							*(d+2)=sR[X];
							*(d+3)=0;
							d+=4;
							XAddedInt+=AddedInt;
						}
					}
				}
			}
		}
		GetLayersBase()->UnlockChangingDataStructure();
		pBuffer->Unlock();
		pBuffer->SetCurrentLength(cbBufferSize);
	}
}

//=====================================================================================


AddImageForMovie::AddImageForMovie(LayersBase *base ,RecordMovie *p)
	:QThread(p),ServiceForLayers(base),Parent(p)
{
	Terminated=false;
	Running		=false;
	Error		=0;
	Running		=false;
	//gwavi		=NULL;
	image_width	=0;
	image_height=0;
	BmpData		=NULL;
	BmpIndexR	=0;
	BmpIndexW	=0;
	BmpStockCount=0;
	ZoomRate	=1.0;

	SparseMilisec	=-1.0;
	StartMilisec	=0;
	RunningMilisec	=0;
	WrittenCount	=0;

    SavedFPS	=0;
    SavedBitRate=0;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    MFStartup(MF_VERSION);
}

AddImageForMovie::~AddImageForMovie(void)
{
 	ReleaseBuff();
	Close();

    MFShutdown();
    CoUninitialize();
}

void	AddImageForMovie::Initialize(void)
{
	double	Zx=((double)Parent->MovieXSize)/((double)Parent->GetDotPerLine(Parent->UsePage));
	double	Zy=((double)Parent->MovieYSize)/((double)Parent->GetMaxLines  (Parent->UsePage));
	ZoomRate=min(Zx,Zy);
}
void	AddImageForMovie::AllocateBuff(void)
{
	if(image_width ==Parent->MovieXSize
	&& image_height==Parent->MovieYSize){
		return;
	}
	ReleaseBuff();

	image_width	=Parent->MovieXSize;
	image_height=Parent->MovieYSize;
	unsigned long		dwMemoryLoad		   ;
	unsigned long long	ullTotalPhys		   ;
	unsigned long long	ullAvailPhys		   ;
	unsigned long long	ullTotalPageFile	   ;
	unsigned long long	ullAvailPageFile	   ;
	unsigned long long	ullTotalVirtual		   ;
	unsigned long long	ullAvailVirtual		   ;
	unsigned long long	ullAvailExtendedVirtual;
	GetMemoryInfo(
				 dwMemoryLoad
				,ullTotalPhys
				,ullAvailPhys
				,ullTotalPageFile
				,ullAvailPageFile
				,ullTotalVirtual
				,ullAvailVirtual
				,ullAvailExtendedVirtual
				);

	int	Size=image_width*image_height;
	unsigned long long 	BmpByte=Size*3;
	if(ullAvailPhys>4000000000UL){
		ullAvailPhys-=3000000000UL;
	}
	MaxImageCount=ullAvailPhys/BmpByte;
	MaxImageCount/=2;
	if(MaxImageCount<20){
		MaxImageCount=20;
	}
	if(MaxImageCount>100){
		MaxImageCount=100;
	}
	BmpData = new BmpClass * [MaxImageCount];
	//#pragma omp parallel                             
	//{                  
	//	#pragma omp for
		for (int i = 0; i < MaxImageCount; i++) {
			BmpData[i] = new BmpClass(this,Parent,GetLayersBase());
			BmpData[i]->AllocateBuff();
		}
	//}

	BmpIndexR = 0;
	BmpIndexW = 0;
	BmpStockCount = 0;
}
void	AddImageForMovie::ReleaseBuff(void)
{
	if (BmpData != NULL) {
		for (int i = 0; i < MaxImageCount; i++) {
			delete	BmpData[i];
		}
		delete	[]BmpData;
		BmpData = NULL;
	}
	BmpIndexR = 0;
	BmpIndexW = 0;
	BmpStockCount = 0;
}

void	AddImageForMovie::AddImage(void)
{
	if(Running==true){
		if(StartMilisec==0){
			StartMilisec=::GetComputerMiliSec();
			RunningMilisec	=0;
			AddedCount		=0;
			LastMilisec		=0;
		}
		DWORD	t=::GetComputerMiliSec();

		if(BmpData[BmpIndexW]->AddImage()==true){
			BmpIndexW++;
			if(BmpIndexW>=MaxImageCount) {
				BmpIndexW=0;
			}
			MutexCounter.lock();
			BmpStockCount++;
			MutexCounter.unlock();
			if(BmpStockCount>=MaxImageCount) {
				Running=false;
				emit	SignalMemoryOver();
			}
		}
	}
}
void AddImageForMovie::Close(void)
{
    if (pSinkWriter) {
        pSinkWriter->Finalize(); // 重要: ファイルを閉じる処理
        SafeRelease(&pSinkWriter);
        pSinkWriter=NULL;
    }
    isOpened = false;
}

bool	AddImageForMovie::StartRecording(const QString &filename
							, int width
							, int height
							, int fps
							, int bitrate)
{
    Close();

    videoWidth = width;
    videoHeight = height;
    
    // 1フレームあたりの時間 (単位: 100ナノ秒)
    frameDuration = 10 * 1000 * 1000 / fps;
    currentSampleTime = 0;

    if (!InitializeSinkWriter(filename, fps, bitrate)) {
        return false;
    }

    isOpened = true;
    return true;
}

bool AddImageForMovie::InitializeSinkWriter(const QString &filename, int fps, int bitrate)
{
    HRESULT hr = S_OK;

	SavedFPS=fps;
	SavedBitRate = bitrate;

    // Sink Writerの作成
    IMFAttributes *pAttr = nullptr;
    MFCreateAttributes(&pAttr, 1);
    pAttr->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, TRUE); // ハードウェア加速を有効化

    hr = MFCreateSinkWriterFromURL(reinterpret_cast<LPCWSTR>(filename.utf16()), NULL, pAttr, &pSinkWriter);
    SafeRelease(&pAttr);
    if (FAILED(hr)) return false;

    // 1. 出力メディアタイプの設定 (H.264)
    IMFMediaType *pMediaTypeOut = nullptr;
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

    // 2. 入力メディアタイプの設定 (RGB32)
    // ここでRGBを指定すると、MFが自動的にH.264(NV12)へ変換してくれる
    IMFMediaType *pMediaTypeIn = nullptr;
    MFCreateMediaType(&pMediaTypeIn);
    pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32); // QImage::Format_RGB32に対応
    pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
    MFSetAttributeSize(pMediaTypeIn, MF_MT_FRAME_SIZE, videoWidth, videoHeight);
    MFSetAttributeRatio(pMediaTypeIn, MF_MT_FRAME_RATE, fps, 1);
    MFSetAttributeRatio(pMediaTypeIn, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);

    hr = pSinkWriter->SetInputMediaType(streamIndex, pMediaTypeIn, NULL);
    SafeRelease(&pMediaTypeIn);
    if (FAILED(hr)) return false;

    // 書き込み開始
    hr = pSinkWriter->BeginWriting();
	Running=true;

    return SUCCEEDED(hr);
}
	
bool	AddImageForMovie::RestartRecording(void)
{
	if (!isOpened || !pSinkWriter) return false;
	Running=true;
	return true;
}

bool	AddImageForMovie::HaltRecording(void)
{
	Running=false;
}
bool	AddImageForMovie::EndRecording(void)
{
	Close();
	return true;
}

bool AddImageForMovie::WriteFrame(void)
{
    if (!isOpened || !pSinkWriter) return false;
	if(BmpStockCount>0) {
		MutexCounter.lock();
		BmpStockCount--;
		MutexCounter.unlock();
		BmpClass *R = BmpData[BmpIndexR];
		BmpIndexR++;
		if(BmpIndexR >= MaxImageCount) {
			BmpIndexR = 0;
		}

		HRESULT hr = S_OK;

		if (SUCCEEDED(hr)) {
		    hr = R->pSample->AddBuffer(R->pBuffer);
		}
		long long SampleTime = R->AddedMiliSec*1000;
		if (SUCCEEDED(hr)) {
		    hr = R->pSample->SetSampleTime(R->AddedMiliSec);
		}
		// 1フレームあたりの時間 (単位: 100ナノ秒)

		if (SUCCEEDED(hr)) {
		    hr = R->pSample->SetSampleDuration(frameDuration);
		}

		// 書き込み実行
		if (SUCCEEDED(hr)) {
		    hr = pSinkWriter->WriteSample(streamIndex, R->pSample);
		}

		if (SUCCEEDED(hr)) {
		    currentSampleTime = frameDuration;
		    return true;
		} else {
		    qWarning() << "WriteSample failed. HRESULT:" << hr;
		    return false;
		}
		return true;
	}
	return false;
}

void	AddImageForMovie::run()
{
	while (Terminated==false && GetLayersBase()->GetOnTerminating()==false){
		if(Running==true && StartMilisec>0){
			if(BmpStockCount>0) {
				if(WriteFrame()==false){
					Running=false;
					emit	SignalWriteError();
				}
			}
			else {
				msleep(2);
			}
		}
		else{
			msleep(2);
		}
	}
}
