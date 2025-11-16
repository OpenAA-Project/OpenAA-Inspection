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
	if(Thread->PeakBuff!=NULL){
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
	ImageBuffer	*IBuff=Thread->PeakBuff[page];
	if(IBuff==NULL)
		return true;
	int	Isolation=Thread->Isolation;
	QColor	Col=ButtonColor->color();
	BYTE	Alpha=ui->horizontalSliderTransparentRate->value()*255/100;
	int		Ra=Alpha*Col.red();
	int		Ga=Alpha*Col.green();
	int		Ba=Alpha*Col.blue();

	double	Z=1.0/ZoomRate;
	int		iZ=(int)(Z*65536.0);
	int	XLen=min(Thread->GetDotPerLine(page),Thread->PeakBuff[page]->GetWidth());
	int	YLen=min(Thread->GetMaxLines(page)	,Thread->PeakBuff[page]->GetHeight());
	XYData	*XY=GetLayersBase()->GetPageData(page)->GetOutlineOffset();
	int	DivCanvasHeight=CanvasHeight/4;
	//#pragma omp parallel  num_threads(2)                           
	//{                                                
	//	#pragma omp for
		//for(int y=0;y<CanvasHeight;y++){
		for(int ky=0;ky<DivCanvasHeight;ky++){
			int	y=tDrawTurn+ky*4;
			int	Y=y*Z-movy-XY->y;
			if(0<=Y && Y<YLen){
				BYTE	*d=PntImage.scanLine(y);
				BYTE	*s=IBuff->GetY((Y/Isolation)*Isolation);
				double	m=-movx-XY->x;
				int	StartX=0;
				if(m<0){
					StartX=ceil(-m/Z);
					memset(d,0,4*StartX);
					d+=4*StartX;
					m+=Z*StartX;
				}
				int	N=CanvasWidth;
				if((m+(CanvasWidth-StartX)*Z)>=XLen){
					N=floor((XLen-m)/Z+StartX);
				}
				N=(N/Isolation)*Isolation;
				int	x;
				int	im=(int)(m*65536.0);

				if(Isolation<=1){
					for(x=StartX;x<N;x++,im+=iZ , d+=4){
						int	X=im>>16;
						BYTE	Index=s[X];

						//*(d+2)=RTable[*(d+2)][Index];
						//*(d+1)=GTable[*(d+1)][Index];
						//*(d+0)=BTable[*(d+0)][Index];
						int	Kr=(Ra*Index)>>16;
						int	Kg=(Ga*Index)>>16;
						int	Kb=(Ba*Index)>>16;
						*(d+2)=ClipByte(*(d+2)+Kr);
						*(d+1)=ClipByte(*(d+1)+Kg);
						*(d+0)=ClipByte(*(d  )+Kb);
					}
				}
				else{
					int	iZN=iZ*Isolation;
					for(x=StartX;x<N;im+=iZN ,x+=Isolation){
						int	X=im>>16;
						BYTE	Index=s[(X/Isolation)*Isolation];

						int	NN=Isolation;
						if((NN+x)>N)
							NN=N-x;
						for(int h=0;h<NN;h++){
							//*(d+2)=RTable[*(d+2)][Index];
							//*(d+1)=GTable[*(d+1)][Index];
							//*(d+0)=BTable[*(d+0)][Index];
							int	Kr=(Ra*Index)>>16;
							int	Kg=(Ga*Index)>>16;
							int	Kb=(Ba*Index)>>16;
							*(d+2)=ClipByte(*(d+2)+Kr);
							*(d+1)=ClipByte(*(d+1)+Kg);
							*(d+0)=ClipByte(*(d  )+Kb);
							d+=4;
						}
					}
				}
				if(x<CanvasWidth){
					memset(d,0,(CanvasWidth-x)*4);
				}
			}
			else{
				BYTE	*d=PntImage.scanLine(y);
				memset(d,0,CanvasWidth*4);
			}
		}
	//}
	return true;
}

ThreadPeaking::ThreadPeaking(LayersBase *base ,HookPeakingForm *parent) 
	: QThread(parent),ServiceForLayers(base),Parent(parent)
{	
	DotPerLine	=0;
	MaxLines	=0;
	ynumb		=0;
	xnumb		=0;
	for(int i=0;i<sizeof(in)/sizeof(in[0]);i++){
		in[i]	=NULL;
		out[i]	=NULL;
		p[i]	=NULL;
	}
	PeakBuff=NULL;
	AllocatedCount=NULL;
	Isolation	=2;
	Turn		=0;

	Terminated=false;
}
ThreadPeaking::~ThreadPeaking(void)
{
	for(int yn=0;yn<ynumb;yn++){
		fftw_free(in[yn]);
		fftw_free(out[yn]);
		fftw_free(p[yn]);
	}
	if(PeakBuff!=NULL){
		for(int page=0;page<AllocatedCount;page++){
			delete	PeakBuff[page];
		}
		delete	[]PeakBuff;
	}
	PeakBuff=NULL;

}
void	ThreadPeaking::run()
{
	Terminated=false;
	while(Terminated==false){
		//if(Parent->Calclating==true){
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
		//}
		//else{
		//	msleep(2000);
		//}
	}
}
void	ThreadPeaking::Realloc(void)
{
	int	Page=Parent->GetTargetPage();
	if(Page>=GetPageNumb()){
		return;
	}
	DotPerLine			=GetDotPerLine(Page);
	MaxLines			=GetMaxLines  (Page);
	int	iAllocatedCount	=GetPageNumb();

	int	iynumb=(MaxLines	-(*CRadius+*CRadius-1)*2)/Isolation;
	int	ixnumb=(DotPerLine	-(*CRadius+*CRadius-1)*2)/Isolation;
	if(iynumb!=ynumb || ixnumb!=xnumb){
		for(int yn=0;yn<ynumb;yn++){
			fftw_free(in[yn]);
			fftw_free(out[yn]);
			fftw_free(p[yn]);
		}

		xnumb=ixnumb;
		ynumb=iynumb;

		for(int yn=0;yn<ynumb;yn++){
			int	y=yn*Isolation+*CRadius;
			int	x=*CRadius;
			int	x1=x-*CRadius;
			int	y1=y-*CRadius;
			int	x2=x+*CRadius-1;
			int	y2=y+*CRadius-1;
			int	SIZEX=x2-x1;
			int	SIZEY=y2-y1;
			int	SIZE=SIZEX*SIZEY;

			size_t mem_size = sizeof(fftw_complex) * SIZE;
			in[yn]  = (fftw_complex*)fftw_malloc( mem_size );
			out[yn] = (fftw_complex*)fftw_malloc( mem_size );

			p[yn]=fftw_plan_dft_2d( SIZEY, SIZEX, in[yn], out[yn], FFTW_FORWARD, FFTW_ESTIMATE );
		}
	}
	
	PeakMutex.lock();
	if(AllocatedCount!=iAllocatedCount
	|| Page<0 
	|| DotPerLine!=PeakBuff[Page]->GetWidth()
	|| MaxLines!=PeakBuff[Page]->GetHeight()){
		if(PeakBuff!=NULL){
			for(int page=0;page<AllocatedCount;page++){
				delete	PeakBuff[page];
			}
			delete	[]PeakBuff;
		}
		PeakBuff=NULL;
		AllocatedCount=iAllocatedCount;
		PeakBuff=new ImageBuffer*[AllocatedCount];
		for(int page=0;page<AllocatedCount;page++){
			PeakBuff[page]=new ImageBuffer(0,DotPerLine,MaxLines);
			PeakBuff[page]->Memset(0);
		}
	}
	PeakMutex.unlock();
}

void	ThreadPeaking::MakePeakData(int localPage)
{
	ImageBuffer	*Src=NULL;
	if(Parent->MemoryType==/**/"Target")
		Src=GetLayersBase()->GetPageData(localPage)->GetLayerData(0)->GetTargetBuffPointer();
	else
	if(Parent->MemoryType==/**/"Master")
		Src=GetLayersBase()->GetPageData(localPage)->GetLayerData(0)->GetMasterBuffPointer();
	else
	if(Parent->MemoryType==/**/"CamTarget")
		Src=GetLayersBase()->GetPageData(localPage)->GetLayerData(0)->GetCamTargetBuffPointer();

	if(Src==NULL)
		return;

	Turn++;
	if(Turn>=4)
		Turn=0;

	int	N=ynumb/4;
	//#pragma omp parallel                             
	//{                                                
	//	#pragma omp for
		//for(int yn=Turn;yn<ynumb;yn+=4){
		for(int k=0;k<N;k++){
			int	yn=Turn+k*4;
			int	y=yn*Isolation+*CRadius;
			int	x=*CRadius;
			BYTE	*d=PeakBuff[localPage]->GetY(y);

			int	x1=x-*CRadius;
			int	y1=y-*CRadius;
			int	x2=x+*CRadius-1;
			int	y2=y+*CRadius-1;
			int	SIZEX=x2-x1;
			int	SIZEY=y2-y1;

			for(int xn=0;xn<xnumb;xn++,x+=Isolation){
				int	c=MakePeakData(SIZEX,SIZEY,p[yn],in[yn],out[yn],*Src 
									,*PeakBuff[localPage]
									,x-*CRadius,y-*CRadius,x+*CRadius-1,y+*CRadius-1);
				d[x]=c;
			}
		}
	//}
}

static	int	MaxR=0;
int	ThreadPeaking::MakePeakData(int SIZEX,int SIZEY,fftw_plan p,fftw_complex *in,fftw_complex *out
								,ImageBuffer &Src, ImageBuffer &Image,int x1,int y1,int x2,int y2)
{
	int i,j,idx;
	// input data creation
	for( j=0; j<SIZEY; j++ ){
		int	y=y1+j;
		BYTE	*s=Src.GetY(y);
		for( i=0; i<SIZEX; i++ ){
			int	x=x1+i;
			idx = SIZEX*j+i; // column-major alignment
			in[idx][0] = s[x];
			in[idx][1] = 0;
		}
	}

	fftw_execute(p);

	int	SizeX2=SIZEX/2;
	int	SizeY2=SIZEY/2;
	/*
	double	Total=0;
	for( j=0; j<SizeY2; j++ ){
		for( i=0; i<SizeX2; i++ ){
			idx = SIZEX*j+i; // column-major alignment
			Total += out[idx][0]*out[idx][0]+out[idx][1]*out[idx][1];
		}
	}
	*/

	double	HighL=0;
	int		Numb=0;
	for( j=2; j<SizeY2-2; j++ ){
		for( i=2; i<SizeX2-2; i++ ){
			idx = SIZEX*j+i; // column-major alignment
			HighL += out[idx][0]*out[idx][0]+out[idx][1]*out[idx][1];
			Numb++;
		}
	}
	if(Numb==0){
		for( j=1; j<SizeY2-1; j++ ){
			for( i=1; i<SizeX2-1; i++ ){
				idx = SIZEX*j+i; // column-major alignment
				HighL += out[idx][0]*out[idx][0]+out[idx][1]*out[idx][1];
				Numb++;
			}
		}
	}
	if(Numb==0){
		for( j=0; j<SizeY2; j++ ){
			for( i=0; i<SizeX2; i++ ){
				idx = SIZEX*j+i; // column-major alignment
				HighL += out[idx][0]*out[idx][0]+out[idx][1]*out[idx][1];
				Numb++;
			}
		}
	}

	double	R=sqrt(HighL/Numb);
	if(R>MaxR){
		MaxR=R;
	}


	if(R<0)
		return 0;
	if(R>=256)
		return 255;
	return R;
}
void	ThreadPeaking::CopyToParent(int localPage)
{
}


