#include "RecordMovie.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
//#include <Windows.h>
//#include <vfw.h>
#include <QMutex>
#include <QMessageBox>
#include "ShowMemoryForm.h"
#include "XMovieThread.h"
extern "C"
{
#include "libavcodec/codec_id.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
};

BmpClass::BmpClass(AddImageForMovie *p,RecordMovie *RP,LayersBase *base)
	:ServiceForLayers(base),Parent(p),RecordParent(RP)
{
	BmpData	=NULL;
	picture	=NULL;
	pkt		=NULL;
}
BmpClass::~BmpClass(void)
{
	if(BmpData!=NULL){
		delete	[]BmpData;
		BmpData=NULL;
	}
	if(picture!=NULL){
		av_frame_free(&picture);
		picture=NULL;
	}
	if(pkt!=NULL){
		av_packet_free(&pkt);
		pkt=NULL;
	}
}
void	BmpClass::AllocateBuff(void)
{
	int	Size=Parent->image_width*Parent->image_height;

	if(Parent->GetAVFormat()==FormatMPeg1){
		BmpByte=(Size*3)/2;

		BmpData=new BYTE[BmpByte];
		memset(BmpData,0,BmpByte);
		if(picture==NULL){
			picture= av_frame_alloc();

			picture->format = Parent->PixFormat;
			picture->width  = Parent->image_width;
			picture->height = Parent->image_height;

			int ret = av_frame_get_buffer(picture, 0);
			if (ret < 0) {
				Parent->Error=AVError_Codec;
				return;
			}
		}
		pkt = av_packet_alloc();
		if (!pkt){
			Parent->Error=AVError_Codec;
			return;
		}
		picture->data[0] = BmpData;
		picture->data[1] = picture->data[0] + Size;
		picture->data[2] = picture->data[1] + Size / 4;
		picture->linesize[0] = Parent->image_width;
		picture->linesize[1] = Parent->image_width / 2;
		picture->linesize[2] = Parent->image_width / 2;	
	}
	else
	if(Parent->GetAVFormat()==FormatMPeg2){
		BmpByte=(Size*3)/2;

		BmpData=new BYTE[BmpByte];
		memset(BmpData,0,BmpByte);
		if(picture==NULL){
			picture= av_frame_alloc();

			picture->format = Parent->PixFormat;
			picture->width  = Parent->image_width;
			picture->height = Parent->image_height;

			int ret = av_frame_get_buffer(picture, 0);
			if (ret < 0) {
				Parent->Error=AVError_Codec;
				return;
			}
		}
		pkt = av_packet_alloc();
		if (!pkt){
			Parent->Error=AVError_Codec;
			return;
		}
		picture->data[0] = BmpData;
		picture->data[1] = picture->data[0] + Size;
		picture->data[2] = picture->data[1] + Size / 4;
		picture->linesize[0] = Parent->image_width;
		picture->linesize[1] = Parent->image_width / 2;
		picture->linesize[2] = Parent->image_width / 2;	
	}
	else
	if(Parent->GetAVFormat()==FormatMPeg4){
		BmpByte=(Size*3)/2;

		BmpData=new BYTE[BmpByte];
		memset(BmpData,0,BmpByte);
		if(picture==NULL){
			picture= av_frame_alloc();

			picture->format = Parent->PixFormat;
			picture->width  = Parent->image_width;
			picture->height = Parent->image_height;

			int ret = av_frame_get_buffer(picture, 0);
			if (ret < 0) {
				Parent->Error=AVError_Codec;
				return;
			}
		}
		pkt = av_packet_alloc();
		if (!pkt){
			Parent->Error=AVError_Codec;
			return;
		}
		picture->data[0] = BmpData;
		picture->data[1] = picture->data[0] + Size;
		picture->data[2] = picture->data[1] + Size / 4;
		picture->linesize[0] = Parent->image_width;
		picture->linesize[1] = Parent->image_width / 2;
		picture->linesize[2] = Parent->image_width / 2;	
	}
	else
	if(Parent->GetAVFormat()==FormatMotionJPeg){
		BmpByte=Size*3;

		BmpData=new BYTE[BmpByte];
		memset(BmpData,0,BmpByte);
	}
}

bool	BmpClass::WriteFrame(QFile *AVFile,AVCodecContext *Context ,int &Error)
{
	int	ret = avcodec_send_frame(Context,picture);

	while (ret >= 0) {
	    ret = avcodec_receive_packet(Context, pkt);
	    if(ret == AVERROR(EAGAIN)){
			Error=AVError_Write;
	        return true;
	    }
		else
		if(ret == AVERROR_EOF){
			Error=AVError_Write;
	        return false;
	    }
		else
	    if (ret < 0) {
			Error=AVError_Write;
	        return false;
	    }
		if(AVFile->write((const char *)pkt->data
							, pkt->size)!=pkt->size){
			Error=AVError_Write;
			return false;
	    }
	    av_packet_unref(pkt);
	}
	Error=AVError_Success;
	return true;
}

bool	BmpClass::WriteFrameNull(QFile *AVFile,AVCodecContext *Context ,int &Error)
{
	int	ret = avcodec_send_frame(Context,NULL);

	while (ret >= 0) {
	    ret = avcodec_receive_packet(Context, pkt);
	    if(ret == AVERROR(EAGAIN)){
			Error=AVError_Write;
	        return true;
	    }
		else
		if(ret == AVERROR_EOF){
			Error=AVError_Write;
	        return false;
	    }
		else
	    if (ret < 0) {
			Error=AVError_Write;
	        return false;
	    }
		if(AVFile->write((const char *)pkt->data
							, pkt->size)!=pkt->size){
			Error=AVError_Write;
			return false;
	    }
	    av_packet_unref(pkt);
	}
	Error=AVError_Success;
	return true;
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
	codec		=NULL;
	Context		=NULL;
	AVFile		=NULL;
	BmpData		=NULL;
	BmpIndexR	=0;
	BmpIndexW	=0;
	BmpWidth	=0;
	BmpStockCount=0;
	FPS			= 0;
	ZoomRate	=1.0;
	MovieQuality=-1;
	PixFormat	=AV_PIX_FMT_YUV420P;
	SparseMilisec	=-1.0;
	StartMilisec	=0;
	RunningMilisec	=0;
	WrittenCount	=0;

	AVIHandle		=0;
	AVIFile			=NULL;
	AVIStreamHandle	=NULL;
}

AddImageForMovie::~AddImageForMovie(void)
{
	if (Context!=NULL) {
		avcodec_free_context(&Context);
		Context		= NULL;
	}
	if ( codec ) {
		//av_free(codec);
		codec = NULL;
	}
	if ( AVFile ) {
		delete	AVFile;
		AVFile = NULL;
	}

	ReleaseBuff();

	if(AVIStreamHandle!=NULL){
		AVIStreamRelease(AVIStreamHandle);
		AVIStreamHandle=NULL;
	}
	if(AVIFile!=0){
		AVIFileRelease(AVIFile);
		AVIFile=NULL;
	}
}

EnumAVFormat	AddImageForMovie::GetAVFormat(void)
{	
	return Parent->AVFormat;
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

void	AddImageForMovie::StopRecording(void)
{
	Running=false;
	GSleep(100);
}

void	AddImageForMovie::EndRecording(void)
{
	while(BmpStockCount>0){
		if(FPS>0 && StartMilisec>0){
			MutexSwitchFile.lock();
			DWORD	CurrentTime=::GetComputerMiliSec();
			double	Span=(CurrentTime-StartMilisec);
			int	n=((Span-1000.0/FPS*0.2)*FPS/1000.0);
			if(n>dwIndex){
				if(BmpStockCount>0) {
					if(Write()==false){
						MutexSwitchFile.unlock();
						break;
					}
				}
				else{
					if(WriteLast()==false){
						MutexSwitchFile.unlock();
						break;
					}
				}
			}
			else {
				msleep(2);
			}
			MutexSwitchFile.unlock();
		}
		else{
			msleep(2);
		}
	}

	if(Parent->AVFormat==FormatMPeg1){
		if(BmpData!=NULL && BmpData[0]!=NULL){
			BmpData[0]->WriteFrameNull(AVFile,Context ,Error);
		}
		if (Context!=NULL) {
			avcodec_free_context(&Context);
			Context		= NULL;
		}
		if ( codec ) {
			//av_free(codec);
			codec = NULL;
		}

		if ( AVFile ) {
			delete	AVFile;
			AVFile = NULL;
		}
	}
	else
	if(Parent->AVFormat==FormatMPeg2){
		if(BmpData!=NULL && BmpData[0]!=NULL){
			BmpData[0]->WriteFrameNull(AVFile,Context ,Error);
		}
		if (Context!=NULL) {
			avcodec_free_context(&Context);
			Context		= NULL;
		}
		if ( codec ) {
			//av_free(codec);
			codec = NULL;
		}

		if ( AVFile ) {
			delete	AVFile;
			AVFile = NULL;
		}
	}
	else
	if(Parent->AVFormat==FormatMPeg4){
		if(BmpData!=NULL && BmpData[0]!=NULL){
			BmpData[0]->WriteFrameNull(AVFile,Context ,Error);
		}
		if (Context!=NULL) {
			avcodec_free_context(&Context);
			Context		= NULL;
		}
		if ( codec ) {
			//av_free(codec);
			codec = NULL;
		}

		if ( AVFile ) {
			delete	AVFile;
			AVFile = NULL;
		}
	}
	else
	if(Parent->AVFormat==FormatMotionJPeg){
		AVIStreamRelease(AVIStreamHandle);
		AVIFileRelease(AVIFile);
		AVIFileExit();

		AVIStreamHandle=0;
		AVIFile=0;
	}

}

bool	AddImageForMovie::StartRecording(EnumAVFormat _AVFormat,const QString &AVIFileName
										,double _FPS ,int quality)
{
	//AVFormat=_AVFormat;
	char	ErrorBuff[10000];

	SparseMilisec	=1000.0/_FPS;
	MovieFileName	=AVIFileName;

	SavedAVFormat	=_AVFormat;
	SavedFPS		=_FPS;
	SavedQuality	=quality;

	if(image_width!=Parent->MovieXSize || image_height!=Parent->MovieYSize){
		Initialize();
	}

	if(GetAVFormat()==FormatMPeg1){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		Context->time_base	= av_make_q(1001,FPS*1000);
		Context->framerate	= av_make_q(FPS*1000, 1001);
		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->max_b_frames=1;
		Context->pix_fmt = PixFormat;

		/* open it */
		if (avcodec_open2(Context, codec,NULL) < 0) {
			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
		    return false;
		}

		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMPeg2){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		Context->time_base	= av_make_q(1001,FPS*1000);
		Context->framerate	= av_make_q(FPS*1000, 1001);
		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->max_b_frames=1;
		Context->pix_fmt = PixFormat;

		/* open it */
		if (avcodec_open2(Context, codec,NULL) < 0) {
			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
		    return false;
		}

		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMPeg4){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		//av_dict_set(&opts, "b", "2.5M", 0);
		codec = avcodec_find_encoder(AV_CODEC_ID_H264);	//AV_CODEC_ID_H265);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		//Context->time_base	= av_make_q(1001,FPS*1000);
		//Context->framerate	= av_make_q(FPS*1000, 1001);

		Context->time_base.num = 1;
		Context->time_base.den = FPS;
		Context->framerate.num = FPS;
		Context->framerate.den = 1;

		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->pix_fmt = PixFormat;

		Context->gop_size = 10;	//FPS*2;

		/// P-frames, generated by referencing data from prev and future frames.
		/// [Compression up, CPU usage up]
		/// [use 3/gop]
		Context->max_b_frames = 3;
		
		/// Can be used by a P-frame(predictive, partial frame) to help define a future frame in a compressed video.
		/// [use 3–5 ref per P]
		Context->refs = 3;
		
		/// Compression efficiency (slower -> better quality + higher cpu%)
		/// [ultrafast, superfast, veryfast, faster, fast, medium, slow, slower, veryslow]
		/// Set this option to "ultrafast" is critical for realtime encoding
		av_opt_set(Context->priv_data, "preset", "ultrafast", 0);
		
		/// Compression rate (lower -> higher compression) compress to lower size, makes decoded image more noisy
		/// Range: [0; 51], sane range: [18; 26]. I used 35 as good compression/quality compromise. This option also critical for realtime encoding
		av_opt_set(Context->priv_data, "crf", "35", 0);
		
		/// Change settings based upon the specifics of input
		/// [psnr, ssim, grain, zerolatency, fastdecode, animation]
		/// This option is most critical for realtime encoding, because it removes delay between 1th input frame and 1th output packet.
		//av_opt_set(Context->priv_data, "tune", "zerolatency", 0);
		int	Ret4=0;
		if((Ret4=avcodec_open2(Context, codec, nullptr)) < 0){
			av_strerror	(Ret4,ErrorBuff,sizeof(ErrorBuff));

			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
			return false;
		}
		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMotionJPeg){
		FPS =_FPS;
		//if(FPS<=2){
		//	FPS=2;
		//}
		//if(FPS>=30){
		//	FPS=30;
		//}

		wchar_t	FileNameW[1025];
		memset(FileNameW,0,sizeof(FileNameW));
		AVIFileName.toWCharArray(FileNameW);
		if (AVIFileOpen(&AVIFile, FileNameW, OF_CREATE | OF_WRITE, NULL) != 0){
			QMessageBox::critical(NULL,"Error"
								,"AVI ファイルを開けませんでした！");
		}
		int page = Parent->GetTargetPage();
		if (page < 0)
			page = 0;
		if (page >= GetPageNumb())
			page = GetPageNumb();
		DataInPage* P = GetLayersBase()->GetPageData(page);

		memset(&AVISInfo, 0,sizeof(AVISInfo));
		AVISInfo.fccType = streamtypeVIDEO;
		AVISInfo.fccHandler = comptypeDIB;
		AVISInfo.dwScale	= 100;
		AVISInfo.dwRate		= (DWORD)(FPS*100);
		AVISInfo.dwLength	= 10;
		AVISInfo.dwQuality = (DWORD)-1;
		SetRect(&AVISInfo.rcFrame, 0, 0, 32, 32);

		memset(&AVIBMi, 0,sizeof(AVIBMi));
		AVIBMi.biSize = sizeof(BITMAPINFOHEADER);
		AVIBMi.biWidth	= image_width;
		AVIBMi.biHeight = image_height;
		AVIBMi.biPlanes = 1;
		AVIBMi.biBitCount = 24;
		AVIBMi.biCompression = BI_RGB;

		if (AVIFileCreateStream(AVIFile, &AVIStreamHandle, &AVISInfo)!= 0){
			QMessageBox::critical(NULL,"Error"
								,"ストリームの作成に失敗しました！");
		}

		if (AVIStreamSetFormat(AVIStreamHandle, 0, &AVIBMi, sizeof(BITMAPINFOHEADER))!=0){
			QMessageBox::critical(NULL,"Error"
								,"ストリームのセットに失敗しました！");
		}
		int	LSize=image_width*image_height;
		MaxCountOfWrittenFrames=0x7FFFFFFFLU/(LSize*3+1000);
	}
	MakeBmpHeader();

	WrittenCount	=0;
	StartMilisec	=0;
	RunningMilisec	=0;
	AddedCount		=0;
	LastMilisec		=0;
	LastCount		=0;
	CountOfWrittenFrames	=0;

	FileNumber=0;
	dwIndex=0;

	Running=true;
	return true;
}

bool	AddImageForMovie::RestartRecording(const QString &AVIFileName ,double _FPS,int quality)
{
	//AVFormat=_AVFormat;
	char	ErrorBuff[10000];

	if(image_width!=Parent->MovieXSize || image_height!=Parent->MovieYSize){
		Initialize();
	}

	if(GetAVFormat()==FormatMPeg1){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		Context->time_base	= av_make_q(1001,FPS*1000);
		Context->framerate	= av_make_q(FPS*1000, 1001);
		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->max_b_frames=1;
		Context->pix_fmt = PixFormat;

		/* open it */
		if (avcodec_open2(Context, codec,NULL) < 0) {
			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
		    return false;
		}

		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMPeg2){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		Context->time_base	= av_make_q(1001,FPS*1000);
		Context->framerate	= av_make_q(FPS*1000, 1001);
		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->max_b_frames=1;
		Context->pix_fmt = PixFormat;

		/* open it */
		if (avcodec_open2(Context, codec,NULL) < 0) {
			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
		    return false;
		}

		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMPeg4){
		FPS =30;	// _FPS		30以外はavcodec_open2で拒否される
		if(FPS<=2){
			FPS=2;
		}
		//av_dict_set(&opts, "b", "2.5M", 0);
		codec = avcodec_find_encoder(AV_CODEC_ID_H264);	//AV_CODEC_ID_H265);
		if (!codec) {
			Error=AVError_Codec;
			return false;
		}

		Context= avcodec_alloc_context3(codec);

		/* put sample parameters */
		Context->bit_rate = 400000*quality/100;
		/* resolution must be a multiple of two */
		Context->width	= image_width;
		Context->height	= image_height;
		/* frames per second */
		//Context->time_base	= av_make_q(1001,FPS*1000);
		//Context->framerate	= av_make_q(FPS*1000, 1001);

		Context->time_base.num = 1;
		Context->time_base.den = FPS;
		Context->framerate.num = FPS;
		Context->framerate.den = 1;

		Context->gop_size = 10; /* emit one intra frame every ten frames */
		Context->pix_fmt = PixFormat;

		Context->gop_size = 10;	//FPS*2;

		/// P-frames, generated by referencing data from prev and future frames.
		/// [Compression up, CPU usage up]
		/// [use 3/gop]
		Context->max_b_frames = 3;
		
		/// Can be used by a P-frame(predictive, partial frame) to help define a future frame in a compressed video.
		/// [use 3–5 ref per P]
		Context->refs = 3;
		
		/// Compression efficiency (slower -> better quality + higher cpu%)
		/// [ultrafast, superfast, veryfast, faster, fast, medium, slow, slower, veryslow]
		/// Set this option to "ultrafast" is critical for realtime encoding
		av_opt_set(Context->priv_data, "preset", "ultrafast", 0);
		
		/// Compression rate (lower -> higher compression) compress to lower size, makes decoded image more noisy
		/// Range: [0; 51], sane range: [18; 26]. I used 35 as good compression/quality compromise. This option also critical for realtime encoding
		av_opt_set(Context->priv_data, "crf", "35", 0);
		
		/// Change settings based upon the specifics of input
		/// [psnr, ssim, grain, zerolatency, fastdecode, animation]
		/// This option is most critical for realtime encoding, because it removes delay between 1th input frame and 1th output packet.
		//av_opt_set(Context->priv_data, "tune", "zerolatency", 0);
		int	Ret4=0;
		if((Ret4=avcodec_open2(Context, codec, nullptr)) < 0){
			av_strerror	(Ret4,ErrorBuff,sizeof(ErrorBuff));

			Error=AVError_Codec;
		    fprintf(stderr, "could not open codec\n");
			return false;
		}
		AVFile = new QFile(AVIFileName);
		if(AVFile->open(QIODevice::WriteOnly)==false){
			Error=AVError_Open;
			return false;
		}
		MaxCountOfWrittenFrames=0x7FFFFFF;
	}
	else
	if(GetAVFormat()==FormatMotionJPeg){
		FPS =_FPS;
		//if(FPS<=2){
		//	FPS=2;
		//}
		//if(FPS>=30){
		//	FPS=30;
		//}

		wchar_t	FileNameW[1025];
		memset(FileNameW,0,sizeof(FileNameW));
		AVIFileName.toWCharArray(FileNameW);
		if (AVIFileOpen(&AVIFile, FileNameW, OF_CREATE | OF_WRITE, NULL) != 0){
			return false;
		}
		int page = Parent->GetTargetPage();
		if (page < 0)
			page = 0;
		if (page >= GetPageNumb())
			page = GetPageNumb();
		DataInPage* P = GetLayersBase()->GetPageData(page);

		memset(&AVISInfo, 0,sizeof(AVISInfo));
		AVISInfo.fccType = streamtypeVIDEO;
		AVISInfo.fccHandler = comptypeDIB;
		AVISInfo.dwScale	= 100;
		AVISInfo.dwRate		= (DWORD)(FPS*100);
		AVISInfo.dwLength	= 10;
		AVISInfo.dwQuality = (DWORD)-1;
		SetRect(&AVISInfo.rcFrame, 0, 0, 32, 32);

		memset(&AVIBMi, 0,sizeof(AVIBMi));
		AVIBMi.biSize = sizeof(BITMAPINFOHEADER);
		AVIBMi.biWidth	= image_width;
		AVIBMi.biHeight = image_height;
		AVIBMi.biPlanes = 1;
		AVIBMi.biBitCount = 24;
		AVIBMi.biCompression = BI_RGB;

		if (AVIFileCreateStream(AVIFile, &AVIStreamHandle, &AVISInfo)!= 0){
			return false;
		}

		if (AVIStreamSetFormat(AVIStreamHandle, 0, &AVIBMi, sizeof(BITMAPINFOHEADER))!=0){
			return false;
		}
		//int	LSize=image_width*image_height;
		//MaxCountOfWrittenFrames=0xFFFFFFFFLU/(LSize*3+100);

		//codec = avcodec_find_encoder(AV_CODEC_ID_MJPEG);
		//if (!codec) {
		//	Error=AVError_Codec;
		//	return false;
		//}
		//
		//Context= avcodec_alloc_context3(codec);
		//
		///* put sample parameters */
		//Context->bit_rate = 400000*quality/100;
		///* resolution must be a multiple of two */
		//Context->width	= 640;	//image_width;
		//Context->height	= 480;	//image_height;
		///* frames per second */
		//Context->time_base	= av_make_q(1,25);	//av_make_q(1001,FPS*1000);
		////Context->framerate	= av_make_q(FPS*1000, 1001);
		////Context->gop_size = 10; /* emit one intra frame every ten frames */
		////Context->max_b_frames=1;
		//Context->pix_fmt = AV_PIX_FMT_YUVJ420P;	//PixFormat;
		////if(formatContext->oformat->flags & AVFMT_GLOBALHEADER)
		////	Context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}
	//MakeBmpHeader();
	
	WrittenCount	=0;
	StartMilisec	=0;
	RunningMilisec	=0;
	AddedCount		=0;
	LastMilisec		=0;
	LastCount		=0;
	CountOfWrittenFrames	=0;

	//FileNumber=0;
	dwIndex=0;

	Running=true;
	return true;
}
static	int	DbgPPP=0;
bool	AddImageForMovie::Write(void)
{
	/* encode the image */
	bool	Ret;
	if(WrittenCount==1){
		DbgPPP++;
	}

	if(Parent->AVFormat==FormatMPeg1){
		Ret=BmpData[BmpIndexR]->WriteFrame(AVFile,Context ,Error);
	}
	else
	if(Parent->AVFormat==FormatMPeg2){
		Ret=BmpData[BmpIndexR]->WriteFrame(AVFile,Context ,Error);
	}
	else
	if(Parent->AVFormat==FormatMPeg4){
		Ret=BmpData[BmpIndexR]->WriteFrame(AVFile,Context ,Error);
	}
	else
	if(Parent->AVFormat==FormatMotionJPeg){
		if(AVIStreamWrite(AVIStreamHandle, dwIndex, 1, BmpData[BmpIndexR]->BmpData
		//if(AVIStreamWrite(AVIStreamHandle, 1, 1, BmpData[BmpIndexR]->BmpData
					, BmpData[BmpIndexR]->BmpByte, AVIIF_KEYFRAME, NULL, NULL)==0){
			Ret=true;
		}
		else{
			Ret=false;
		}
	}
	WrittenCount++;
	dwIndex++;
	MutexCounter.lock();
	BmpStockCount--;
	MutexCounter.unlock();

	BmpIndexR++;
	if (BmpIndexR >= MaxImageCount) {
		BmpIndexR=0;
	}
	return Ret;
}
bool	AddImageForMovie::WriteLast(void)
{
	bool	Ret;
	if(dwIndex>0){
		if(WrittenCount==1){
			DbgPPP++;
		}

		int	n=BmpIndexR-1;
		if(n<0){
			n=MaxImageCount-1;
		}

		if(Parent->AVFormat==FormatMPeg1){
			Ret=BmpData[n]->WriteFrame(AVFile,Context ,Error);
		}
		else
		if(Parent->AVFormat==FormatMPeg2){
			Ret=BmpData[n]->WriteFrame(AVFile,Context ,Error);
		}
		else
		if(Parent->AVFormat==FormatMPeg4){
			Ret=BmpData[n]->WriteFrame(AVFile,Context ,Error);
		}
		else
		if(Parent->AVFormat==FormatMotionJPeg){
			if(AVIStreamWrite(AVIStreamHandle, dwIndex, 1, BmpData[n]->BmpData
			//if(AVIStreamWrite(AVIStreamHandle, 1, 1, BmpData[n]->BmpData
						, BmpData[n]->BmpByte, AVIIF_KEYFRAME, NULL, NULL)==0){
				Ret=true;
			}
			else{
				Ret=false;
			}
		}
		WrittenCount++;
		dwIndex++;
		return Ret;
	}
	return true;
}

void	AddImageForMovie::run()
{
	while (Terminated==false && GetLayersBase()->GetOnTerminating()==false){
		if(FPS>0 && Running==true && StartMilisec>0){
			MutexSwitchFile.lock();
			DWORD	CurrentTime=::GetComputerMiliSec();
			double	Span=(CurrentTime-StartMilisec);
			int	n=((Span-1000.0/FPS*0.2)*FPS/1000.0);
			if(n>dwIndex){
				if(BmpStockCount>0) {
					if(Write()==false){
						Running=false;
						emit	SignalWriteError();
					}
				}
				else{
					if(WriteLast()==false){
						Running=false;
						emit	SignalWriteError();
					}
				}
			}
			else {
				msleep(2);
			}
			MutexSwitchFile.unlock();
		}
		else{
			msleep(2);
		}
	}
}

void	AddImageForMovie::MakeBmpHeader(void)
{
	image_width	 = Parent->MovieXSize;
	image_height = Parent->MovieYSize;
		
	int page = Parent->GetTargetPage();
	if (page < 0)
		page = 0;
	if (page >= GetPageNumb())
		page = GetPageNumb();
	DataInPage* P = GetLayersBase()->GetPageData(page);

	double	Zx=((double)image_width )/((double)P->GetDotPerLine());
	double	Zy=((double)image_height)/((double)P->GetMaxLines  ());
	ZoomRate=min(Zx,Zy);

	double	Z=1.0/ZoomRate;
	for (int x=0;x<image_width;x++) {
		XPosDim[x]=x*Z;
		if(P->GetDotPerLine()<=XPosDim[x]){
			XPosDim[x]=P->GetDotPerLine()-1;
		}
	}
}

void	AddImageForMovie::AddImage(void)
{
	if(Running==true){
		if(StartMilisec==0){
			StartMilisec=::GetComputerMiliSec();
			RunningMilisec	=0;
			AddedCount		=0;
			LastMilisec		=0;
			LastCount		=0;
			CountOfWrittenFrames	=0;
		}
		DWORD	t=::GetComputerMiliSec();
		if(t<LastMilisec){
			RunningMilisec+=0xFFFFFFFFLU-StartMilisec;
			AddedCount	+=LastCount;
			StartMilisec=1;
		}
		LastMilisec=t;
		int	N=(t-StartMilisec)/SparseMilisec+AddedCount;
		if(N>LastCount){
			LastCount=N;

			if(BmpData[BmpIndexW]->AddImage()==true){
				CountOfWrittenFrames++;
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

				if(CountOfWrittenFrames>=MaxCountOfWrittenFrames){
					//MutexSwitchFile.lock();
					FileNumber++;
					QFileInfo	FInfo(MovieFileName);
					QString	FileName=FInfo.path()
									+QDir::separator()
									+FInfo.baseName()
									+QString(/**/"-")
									+QString::number(FileNumber)
									+QString(/**/".")
									+FInfo.suffix();
					EndRecording();
					RestartRecording(FileName,SavedFPS,SavedQuality);
					//MutexSwitchFile.unlock();
				}
			}
		}
	}
}
