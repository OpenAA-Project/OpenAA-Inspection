/*
 * Copyright (C) 2025
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
// 必要なライブラリ: GLEW, GLFW


#include "HookPeakingForm.h"
#include "ui_HookPeakingForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XCrossObj.h"
#include "XDisplayBitImage.h"
#include "mtPushButtonColored.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "HookPeakingThread.h"
#include "XGpuSharpness.h"
#include "XMainSchemeMemory.h"

void	HookPeakingForm::Draw	(QPainter &pnt	,QImage &PntImage,double ZoomRate,int movx ,int movy ,int CanvasWidth , int CanvasHeight)
{
	if(ui->toolButtonMode->isChecked()==false)
		return;

	LastPaintTime	=::GetComputerMiliSec();

	QColor	Col=ButtonColor->color();
	int	Alpha=ui->horizontalSliderTransparentRate->value()*255/100;
	int	R=Col.red();
	int	G=Col.green();
	int	B=Col.blue();

	if(LastAlpha!=Alpha || LastColor!=Col){
		for(int d=0;d<256;d++){
			for(int c=0;c<256;c++){
				RTable[d][c]=ClipByte(d+Alpha*R*c/65536);
				GTable[d][c]=ClipByte(d+Alpha*G*c/65536);
				BTable[d][c]=ClipByte(d+Alpha*B*c/65536);
			}
		}
		LastAlpha=Alpha;
		LastColor=Col;
	}

	int	page=GetTargetPage();
	if(Thread->FlatBuff!=NULL){
		Thread->PeakMutex.lock();
		if(page<0){
			for(int p=0;p<GetPageNumb();p++){
				DrawInPage	(PntImage
						,p
						,ZoomRate,movx ,movy ,CanvasWidth , CanvasHeight
						,DrawTurn);
			}
		}
		else
		if(0<=page && page<GetPageNumb()){
			DrawInPage	(PntImage
						,page
						,ZoomRate,movx ,movy ,CanvasWidth , CanvasHeight
						,DrawTurn);
		}
		DrawTurn++;
		if(DrawTurn>=4)
			DrawTurn=0;
		Thread->PeakMutex.unlock();
	}
}

bool	HookPeakingForm::DrawInPage	(QImage &PntImage
						,int page
						,double ZoomRate,int movx ,int movy 
						,int CanvasWidth , int CanvasHeight
						,int tDrawTurn)
{
	FlatPeakingImageBuff	&ImageBuff=Thread->FlatBuff[page];

	int	Isolation=Thread->Isolation;
	QColor	Col=ButtonColor->color();
	BYTE	Alpha=ui->horizontalSliderTransparentRate->value()*255/100;
	int		Ra=Alpha*Col.red();
	int		Ga=Alpha*Col.green();
	int		Ba=Alpha*Col.blue();

	double	Z=1.0/ZoomRate;
	int		iZ=(int)(Z*65536.0);
	int	XLen=Thread->FlatBuff[page].Width;
	int	YLen=Thread->FlatBuff[page].Height;
	XYData	*XY=GetLayersBase()->GetPageData(page)->GetOutlineOffset();

	int	DivCanvasHeight	=CanvasHeight/Isolation;
	int	DivCanvasWidth	=CanvasWidth/Isolation;
	float	ZF = Z/Isolation;
	//#pragma omp parallel  num_threads(2)                           
	//{                                                
	//	#pragma omp for
		for(int y=0;y<CanvasHeight;y++){
			BYTE	*d=PntImage.scanLine(y);
			int	Y = (y*Z-movy-XY->y)/Isolation;
			if(0<=Y && Y<YLen){
				BYTE	*s=ImageBuff.OutData+(Y*ImageBuff.Width);
				float	X = (0*Z-movx-XY->x)/Isolation;
				for(int x=0;x<CanvasWidth;x++){
					int	Xi = (int)(X);
					X+=ZF;
					if(0<=Xi && Xi<XLen){
						BYTE	Index=s[Xi];
						int		Kr=(Ra*Index)>>16;
						int		Kg=(Ga*Index)>>16;
						int		Kb=(Ba*Index)>>16;
						*(d+3)=Alpha;
						*(d+2)=ClipByte(*(d+2)+Kr);
						*(d+1)=ClipByte(*(d+1)+Kg);
						*(d+0)=ClipByte(*(d  )+Kb);
						d+=4;
					}
					else{
						*(d+3)=0;
						*(d+2)=0;
						*(d+1)=0;
						*(d+0)=0;
						d+=4;
					}
				}
			}
			else{
				memset(d,0,CanvasWidth*4);
			}
		}
	//}
	return true;
}

FlatPeakingImageBuff::FlatPeakingImageBuff()
{
	InData	=NULL;
	OutData	=NULL;
	Width	=0;	
	Height	=0;
	Page	=0;
}
FlatPeakingImageBuff::~FlatPeakingImageBuff()
{
	if(InData!=NULL){
		delete	[]InData;
	}
	if(OutData!=NULL){
		delete	[]OutData;
	}
	InData	=NULL;
	OutData	=NULL;
	Width	=0;	
	Height	=0;
	Page = 0;
}
//================================================================


ThreadPeaking::ThreadPeaking(LayersBase *base ,int _Isolation ,HookPeakingForm *parent) 
	: QThread(parent),ServiceForLayers(base),Parent(parent)
{
	FlatBuff=NULL;
	AllocatedCount=0;
	Isolation	=_Isolation;
	AverageBuff	=NULL;
	APointR		=0;
	APointW		=0;
	StartMode	=false;
	SensitivityVal = 5;
	Radius		=3;
	PageCount = 0;
	Terminated=false;
	GpuContext = GetGpuSharpnessContextInstance();
}

ThreadPeaking::~ThreadPeaking(void)
{
	delete GpuContext;
    GpuContext=NULL;

	if(FlatBuff!=NULL){
		delete	[]FlatBuff;
	}
	if(AverageBuff!=NULL){
		delete	[]AverageBuff;
	}
	FlatBuff=NULL;
}

void	FlatPeakingImageBuff::Allocate(int width,int height,int page)
{
	if(InData!=NULL){
		delete	[]InData;
	}
	if(OutData!=NULL){
		delete	[]OutData;
	}
	Width	=width;
	Height	=height;
	Page	=page;
	InData = new BYTE[Width*Height];
	OutData = new BYTE[Width*Height];
}

void	ThreadPeaking::SetPeakingParam(float sensitivityVal,int radius)
{
	SensitivityVal	=sensitivityVal;
	Radius			=radius;
}


void	ThreadPeaking::run()
{
	Terminated=false;
	
	InitialGPUForShader(isGLES);

	while(Terminated==false){
		if(StartMode==true){
			GetLayersBase()->LockRChangingDataStructure();
			Realloc();
			int	Page=Parent->GetTargetPage();
			if(Page<0){
				for(int page=0;page<AllocatedCount;page++){
					MakePeakData(page);
				}
			}
			else if(0<=Page && Page<GetPageNumb()){
				MakePeakData(Page);
			}
			GetLayersBase()->UnlockChangingDataStructure();
			emit	SignalShowPeaking();
			msleep(30);
		}
		else{
			msleep(1000);
		}
	}
}
void	ThreadPeaking::Realloc(void)
{
	if(Parent==NULL){
		return;
	}
	int	Page=Parent->GetTargetPage();
	if(Page>=GetPageNumb()){
		return;
	}
	int	iAllocatedCount	=GetPageNumb();

	PeakMutex.lock();
	if(AllocatedCount!=iAllocatedCount){
		if(FlatBuff!=NULL){
			delete	[]FlatBuff;
		}
		FlatBuff=NULL;
	}

	if(Page<0 
	|| FlatBuff==NULL){
		AllocatedCount=iAllocatedCount;
		FlatBuff=new FlatPeakingImageBuff[AllocatedCount];
	}
	if(Page>=0){
		int	DotPerLine			=GetDotPerLine(Page)/Isolation;
		int	MaxLines			=GetMaxLines  (Page)/Isolation;

		if((DotPerLine!=FlatBuff[Page].Width
		|| MaxLines!=FlatBuff[Page].Height)){
			FlatBuff[Page].Allocate(DotPerLine,MaxLines,Page);
		}
	}
	PeakMutex.unlock();

	if(Page<0){
		if(PageCount!=GetPageNumb()){
			if(AverageBuff!=NULL){
				delete	[]AverageBuff;
			}
			PageCount=GetPageNumb();
			AverageBuff=new ImageBufferListContainer[PageCount];
			for(int p=0;p<GetPageNumb();p++){
				int	DotPerLine			=GetDotPerLine(p)/Isolation;
				int	MaxLines			=GetMaxLines  (p)/Isolation;
				for(int i=0;i<CountOfAverage;i++){
					ImageBufferList	*t=new ImageBufferList();
					t->Set(0,0,DotPerLine,MaxLines);
					AverageBuff[p].AppendList(t);
				}
			}
		}
		else{
			for(int p=0;p<GetPageNumb();p++){
				int	DotPerLine			=GetDotPerLine(p)/Isolation;
				int	MaxLines			=GetMaxLines  (p)/Isolation;
				if(AverageBuff[p].GetWidth()!=DotPerLine
				|| AverageBuff[p].GetHeight()!=MaxLines){
					for(int i=0;i<CountOfAverage;i++){
						ImageBufferList	*t=AverageBuff[p][i];
						t->Set(0,0,DotPerLine,MaxLines);
					}
				}
			}
		}
	}
	else
	if(0<=Page && Page<GetPageNumb()){
		if(PageCount!=1){
			if(AverageBuff!=NULL){
				delete	[]AverageBuff;
			}
			PageCount=1;
			AverageBuff=new ImageBufferListContainer[PageCount];
			int	DotPerLine			=GetDotPerLine(Page)/Isolation;
			int	MaxLines			=GetMaxLines  (Page)/Isolation;
			for(int i=0;i<CountOfAverage;i++){
				ImageBufferList	*t=new ImageBufferList();
				t->Set(0,0,DotPerLine,MaxLines);
				AverageBuff[0].AppendList(t);
			}
		}
		else{
			int	DotPerLine			=GetDotPerLine(Page)/Isolation;
			int	MaxLines			=GetMaxLines  (Page)/Isolation;
			if(AverageBuff[0].GetWidth()!=DotPerLine
			|| AverageBuff[0].GetHeight()!=MaxLines){
				for(int i=0;i<CountOfAverage;i++){
					ImageBufferList	*t=AverageBuff[0][i];
					t->Set(0,0,DotPerLine,MaxLines);
				}
			}
		}
	}
}

void	ThreadPeaking::SetTmage(int localPage)
{
	ImagePointerContainer	Src;

	int	Page=Parent->GetTargetPage();
	if(Parent->MemoryType==/**/"Target")
		GetLayersBase()->GetPageData(localPage)->GetTargetImages(Src);
	else
	if(Parent->MemoryType==/**/"Master")
		GetLayersBase()->GetPageData(localPage)->GetMasterImages(Src);
	else
	if(Parent->MemoryType==/**/"CamTarget")
		GetLayersBase()->GetPageData(localPage)->GetCamTargetImages(Src);

	if(Page<0){
		if(localPage<PageCount){
			SetAverage((AverageBuff[localPage])[APointW],Src);
			APointW++;
			if(APointW>=CountOfAverage){
				APointW=0;
			}
		}
	}
	else if(Page==localPage && PageCount==1){
		SetAverage((AverageBuff[0])[APointW],Src);
		APointW++;
		if(APointW>=CountOfAverage){
			APointW=0;
		}
	}
}

void	ThreadPeaking::SetAverage(ImageBuffer *Dst,ImagePointerContainer &Src)
{
	int	PCount = Src.GetCount();
	int	DstWidth	= Dst->GetWidth();
	int	DstHeight	= Dst->GetHeight();
	int	SrcWidth	= Src.GetWidth();
	int SrcHeight	= Src.GetHeight();

	if(PCount==3){
		ImageBuffer *R = Src[0];
		ImageBuffer *G = Src[1];
		ImageBuffer *B = Src[2];
		#pragma omp parallel  num_threads(2)                           
		{                                                
			#pragma omp for
			for(int y=0;y<DstHeight;y++){
				BYTE	*d=Dst->GetY(y);
				BYTE	*sr=R->GetY(y*Isolation);
				BYTE	*sg=G->GetY(y*Isolation);
				BYTE	*sb=B->GetY(y*Isolation);
				int	sx=0;
				for(int x=0;x<DstWidth;x++){
					int	r=sr[sx];
					int	g=sg[sx];
					int	b=sb[sx];
					int	gray=(r*76+g*150+b*28)>>8;
					d[x]=(BYTE)gray;
					sx+=Isolation;
				}
			}
		}
	}
	if(PCount==1){
		ImageBuffer *R = Src[0];
		#pragma omp parallel  num_threads(2)                           
		{                                                
			#pragma omp for
			for(int y=0;y<DstHeight;y++){
				BYTE	*d=Dst->GetY(y);
				BYTE	*sr=R->GetY(y*Isolation);
				int	sx=0;
				for(int x=0;x<DstWidth;x++){
					int	r=sr[sx];
					d[x]=sr[sx];
					sx+=Isolation;
				}
			}
		}
	}
}


void	ThreadPeaking::MakePeakData(int localPage)
{
	if(FlatBuff!=NULL){
		int	Page=Parent->GetTargetPage();
		int	p=0;
		if(Page<0){
			if(localPage<PageCount){
				p=localPage;
			}
		}
		else if(Page==localPage && PageCount==1){
			p=0;
		}

		int	DstWidth	= AverageBuff[p].GetWidth();
		int	DstHeight	= AverageBuff[p].GetHeight();
		if(CountOfAverage==2){
			#pragma omp parallel  num_threads(4)                           
			{                                                
				#pragma omp for
				for(int y=0;y<DstHeight;y++){
					BYTE *dst = FlatBuff[localPage].InData+(y*FlatBuff[localPage].Width);
					BYTE *src[100];
					for(int i=0;i<CountOfAverage;i++){
						src[i] = (AverageBuff[p])[i]->GetY(y);
					}
					for(int x = 0;x<DstWidth;x++){
						int	sum = 0;
						for(int i=0;i<CountOfAverage;i++){
							sum += src[i][x];
						}
						dst[x] = (BYTE)(sum>>1);
					}
				}
			}
		}
		else
		if(CountOfAverage==4){
			#pragma omp parallel  num_threads(4)                           
			{                                                
				#pragma omp for
				for(int y=0;y<DstHeight;y++){
					BYTE *dst = FlatBuff[localPage].InData+(y*FlatBuff[localPage].Width);
					BYTE *src[100];
					for(int i=0;i<CountOfAverage;i++){
						src[i] = (AverageBuff[p])[i]->GetY(y);
					}
					for(int x = 0;x<DstWidth;x++){
						int	sum = 0;
						for(int i=0;i<CountOfAverage;i++){
							sum += src[i][x];
						}
						dst[x] = (BYTE)(sum>>2);
					}
				}
			}
		}
		else
		if(CountOfAverage==8){
			#pragma omp parallel  num_threads(4)                           
			{                                                
				#pragma omp for
				for(int y=0;y<DstHeight;y++){
					BYTE *dst = FlatBuff[localPage].InData+(y*FlatBuff[localPage].Width);
					BYTE *src[100];
					for(int i=0;i<CountOfAverage;i++){
						src[i] = (AverageBuff[p])[i]->GetY(y);
					}
					for(int x = 0;x<DstWidth;x++){
						int	sum = 0;
						for(int i=0;i<CountOfAverage;i++){
							sum += src[i][x];
						}
						dst[x] = (BYTE)(sum>>3);
					}
				}
			}
		}
		else
		if(CountOfAverage==16){
			#pragma omp parallel  num_threads(4)                           
			{                                                
				#pragma omp for
				for(int y=0;y<DstHeight;y++){
					BYTE *dst = FlatBuff[localPage].InData+(y*FlatBuff[localPage].Width);
					BYTE *src[100];
					for(int i=0;i<CountOfAverage;i++){
						src[i] = (AverageBuff[p])[i]->GetY(y);
					}
					for(int x = 0;x<DstWidth;x++){
						int	sum = 0;
						for(int i=0;i<CountOfAverage;i++){
							sum += src[i][x];
						}
						dst[x] = (BYTE)(sum>>4);
					}
				}
			}
		}
		else{
			#pragma omp parallel  num_threads(4)                           
			{                                                
				#pragma omp for
				for(int y=0;y<DstHeight;y++){
					BYTE *dst = FlatBuff[localPage].InData+(y*FlatBuff[localPage].Width);
					BYTE *src[100];
					for(int i=0;i<CountOfAverage;i++){
						src[i] = (AverageBuff[p])[i]->GetY(y);
					}
					for(int x = 0;x<DstWidth;x++){
						int	sum = 0;
						for(int i=0;i<CountOfAverage;i++){
							sum += src[i][x];
						}
						dst[x] = (BYTE)(sum/CountOfAverage);
					}
				}
			}
		}

		GpuContext->init(FlatBuff[localPage].Width, FlatBuff[localPage].Height, Radius,isGLES);
		GpuContext->process(FlatBuff[localPage].InData, FlatBuff[localPage].OutData,SensitivityVal);

		//computeSharpness(FlatBuff[localPage].InData
		//				, FlatBuff[localPage].OutData
		//				, FlatBuff[localPage].Width
		//				, FlatBuff[localPage].Height
		//				, SensitivityVal
		//				,Radius	
		//				,isGLES);
	}
}

/*
int ThreadPeaking::calculateSharpness(ImageBuffer &Image, int X ,int Y,int width, int height, double sensitivity)
{
    if (width < 3 || height < 3) return 0; // 3x3未満はエッジ検出不可

    long long sum = 0;
    long long sq_sum = 0;
    int count = 0;

    // ラプラシアンフィルタ (4近傍)
    //    0   1   0
    //    1  -4   1
    //    0   1   0
    //
    // 画像の端(1px)は隣接画素がないため計算対象外とします
    // これにより条件分岐(if文)をループ内から排除し高速化します
    
    for (int y = 1; y < height - 1; ++y) {
		BYTE	*s =Image.GetY(Y+y);
		BYTE	*sp=Image.GetY(Y+y-1);
		BYTE	*sn=Image.GetY(Y+y+1);
        // 行の先頭インデックスを事前に計算

        for (int x = 1; x < width - 1; ++x) {
            // 各画素値の取得
			int	tX=X+x;
            int center = s[tX];
            int up     = sp[tX];
            int down   = sn[tX];
            int left   = s[tX-1];
            int right  = s[tX+1];

            // ラプラシアン値の計算
            int laplacian = up + down + left + right - (4 * center);

            // 平均と分散を計算するための累積
            sum += laplacian;
            sq_sum += (laplacian * laplacian);
            count++;
        }
    }

    if (count == 0) return 0;

    // 分散(Variance) = E[X^2] - (E[X])^2
    double mean = static_cast<double>(sum) / count;
    double variance = (static_cast<double>(sq_sum) / count) - (mean * mean);

    // スコア化 (0-255)
    double score = (variance / sensitivity) * 255.0;

    // クリッピング
    if (score > 255.0) return 255;
    if (score < 0.0) return 0;
    return static_cast<int>(score);
}
*/
