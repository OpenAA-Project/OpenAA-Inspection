#include "RealtimeGraphMeasure1Form.h"
#include <QImage>
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XGeneralFunc.h"
#include "XRealtimeGraphThread.h"
#include "XDataInLayer.h"

ThreadFocus::ThreadFocus(LayersBase *base ,RealtimeGraphMeasure1Form *parent)
	: ServiceForLayers(base),Parent(parent)
{
	inx			=NULL;
	iny			=NULL;
	outx		=NULL;
	outy		=NULL;
	CamNo		=-1;
	AllocXLen	=0;
	AllocYLen	=0;
	XLen		=0;
	YLen		=0;
	Brightness	=NULL;
	FocusValue	=NULL;
	AllocLayerNumb	=0;
	Page		=0;
}

ThreadFocus::~ThreadFocus(void)
{
	fftw_free(inx);
	fftw_free(iny);
	fftw_free(outx);
	fftw_free(outy);
	fftw_free(PlanX);
	fftw_free(PlanY);
	delete	[]Brightness;
	delete	[]FocusValue;
	CalcDone	=false;

	inx			=NULL;
	iny			=NULL;
	outx		=NULL;
	outy		=NULL;
	CamNo		=-1;
	AllocXLen	=0;
	AllocYLen	=0;
	XLen		=0;
	YLen		=0;
	Brightness	=NULL;
	FocusValue	=NULL;
	AllocLayerNumb	=0;
}

void	ThreadFocus::Realloc(void)
{
	Parent->MutexCalc.lock();
	if(AllocXLen!=XLen && inx!=NULL){
		fftw_free(inx);
		fftw_free(outx);
		fftw_free(PlanX);
		inx		=NULL;
		outx	=NULL;
	}
	if(AllocYLen!=YLen && iny!=NULL){
		fftw_free(iny);
		fftw_free(outy);
		fftw_free(PlanY);
		iny		=NULL;
		outy	=NULL;
	}
	if(inx==NULL){
		size_t mem_size = sizeof(fftw_complex) * XLen;
		AllocXLen=XLen;
		inx  = (fftw_complex*)fftw_malloc( mem_size );
		outx = (fftw_complex*)fftw_malloc( mem_size );
		PlanX=fftw_plan_dft_1d( AllocXLen, inx, outx, FFTW_FORWARD, FFTW_ESTIMATE );
	}
	if(iny==NULL){
		size_t mem_size = sizeof(fftw_complex) * YLen;
		AllocYLen=YLen;
		iny  = (fftw_complex*)fftw_malloc( mem_size );
		outy = (fftw_complex*)fftw_malloc( mem_size );
		PlanY=fftw_plan_dft_1d( AllocYLen, iny, outy, FFTW_FORWARD, FFTW_ESTIMATE );
	}
	if(AllocLayerNumb!=GetLayerNumb(Page) || Brightness==NULL){
		if(Brightness!=NULL){
			delete	[]Brightness;
		}
		Brightness=new double[GetLayerNumb(Page)];
	}
	if(AllocLayerNumb!=GetLayerNumb(Page) || FocusValue==NULL){
		if(FocusValue!=NULL){
			delete	[]FocusValue;
		}
		FocusValue=new double[GetLayerNumb(Page)];
	}
	AllocLayerNumb=GetLayerNumb(Page);
	Parent->MutexCalc.unlock();
}

void	ThreadFocus::Calculate(void)
{
	Realloc();

	IntList	PageList;
	GetParamGlobal()->GetPageListFromCameraNo(Parent->CamNo,PageList);
	int	Page=0;
	if(PageList.GetCount()>0){
		Page=PageList.GetFirst()->GetValue();
	}
	ImagePointerContainer Images;
	DataInPage *dp=GetLayersBase()->GetPageData(Page);
	if(dp!=NULL){
		dp->GetTargetImages(Images);
		for(int layer=0;layer<GetLayerNumb(Page);layer++){
			Brightness[layer]=0;
			FocusValue[layer]=0;
		}
		CalcWidth(Images);
		CalcHeight(Images);
	}
}

void	ThreadFocus::CalcWidth(ImagePointerContainer &Images)
{
	int	BandNumb=8;
	int	Band=AllocYLen/BandNumb;

	for(int layer=0;layer<GetLayerNumb(Page);layer++){
		ImageBuffer	*Buff=Images[layer];

		for(int i=0;i<BandNumb;i++){
			for(int x=0;x<AllocXLen;x++){
				inx[x][0]=0;
				inx[x][1]=0;
			}
			double	B=0;
			int		BNumb=0;
			for(int n=0;n<Band;n++){
				int	Y=YPos+i*Band+n;
				BYTE	*s=Buff->GetY(Y);
				for(int x=0;x<AllocXLen;x++){
					int	X=XPos+x;
					B+=s[X];
					BNumb++;
					inx[x][0]+=s[X];
				}
			}
			Parent->MutexCalc.lock();
			fftw_execute(PlanX);
			Parent->MutexCalc.unlock();

			double	Avr=B/BNumb;
			if(Brightness[layer]<Avr){
				Brightness[layer]=Avr;
			}
			double	MaxD=0;
			int	AllocXLen2=AllocXLen/2;
			for(int x=1;x<AllocXLen2;x++){
				double	d=sqrt(outx[x][0]*outx[x][0]+outx[x][1]*outx[x][1])/BNumb;
				if(d>MaxD){
					MaxD=d;
				}
			}
			if(FocusValue[layer]<MaxD){
				FocusValue[layer]=MaxD;
			}
		}
	}
}
void	ThreadFocus::CalcHeight(ImagePointerContainer &Images)
{
	int	BandNumb=8;
	int	Band=AllocXLen/BandNumb;
	for(int layer=0;layer<GetLayerNumb(Page);layer++){
		ImageBuffer	*Buff=Images[layer];

		for(int i=0;i<BandNumb;i++){
			for(int y=0;y<AllocYLen;y++){
				iny[y][0]=0;
				iny[y][1]=0;
			}
			double	B=0;
			int		BNumb=0;
			for(int n=0;n<Band;n++){
				int	X=XPos+i*Band+n;
				for(int y=0;y<AllocYLen;y++){
					int	Y=YPos+y;
					BYTE	*s=Buff->GetY(Y);
					B+=s[X];
					BNumb++;
					iny[y][0]+=s[X];
				}
			}
			Parent->MutexCalc.lock();
			fftw_execute(PlanY);
			Parent->MutexCalc.unlock();

			double	Avr=B/BNumb;
			if(Brightness[layer]<Avr){
				Brightness[layer]=Avr;
			}
			double	MaxD=0;
			int	AllocYLen2=AllocYLen/2;
			for(int y=1;y<AllocYLen2;y++){
				double	d=sqrt(outy[y][0]*outy[y][0]+outy[y][1]*outy[y][1]);
				if(d>MaxD){
					MaxD=d;
				}
			}
			if(FocusValue[layer]<MaxD){
				FocusValue[layer]=MaxD;
			}
		}
	}
}