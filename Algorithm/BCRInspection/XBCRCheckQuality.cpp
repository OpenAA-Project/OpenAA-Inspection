#include "swap.h"
#include "BCRInspectionResource.h"
#include "XBCRInspection.h"
#include "fftw3.h"
#include "malloc.h"

double	BCRInspectionItem::CalcFFT(int n ,BYTE Data[])
{
	int DataLen=FFTLen[n];
	if(DataLen==0){
		return 0;
	}
	int32	A=0;
	int32	AA=0;
	for(int i=0;i<DataLen;i++){
		BYTE	D=Data[i];
		A	+=D;
		AA	+=D*D;
		(*(FFT_in[n]+i))[0]=D;
		(*(FFT_in[n]+i))[1]=0;
	}
	double	Avr=A/((double)DataLen);
	double	V=(AA-DataLen*Avr*Avr)/DataLen;
	if(Avr<=0)
		return 0;
	V=sqrt(V);
	for(int i=0;i<DataLen;i++){
		(*(FFT_in[n]+i))[0]/=V;
	}
	fftw_execute(FPlan[n]);

	int	DLen=DataLen/2-1;
	double	HighL=0;
	int		N=0;
	int		StartK=DataLen/6;
	StartK=max(2,StartK);
	for(int k=StartK;k<DLen;k++){
		double	L=FFT_out[n][k][0]*FFT_out[n][k][0]
				 +FFT_out[n][k][1]*FFT_out[n][k][1];
		HighL += L;
		N++;
	}
	if(N==0)
		return 0;
	HighL/=N;
	
	return HighL;
}

BCRGradeList	*BCRInspectionItem::CheckQuality(ImagePointerContainer &ImageList,double &MaxV)
{
	ResultMx=0;
	ResultMy=0;
	if(AVector!=NULL){
		ResultMx=AVector->ShiftX;
		ResultMy=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		ResultMx=V.ShiftX;
		ResultMy=V.ShiftY;
	}
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);

	x1+=ResultMx;
	y1+=ResultMy;
	x2+=ResultMx;
	y2+=ResultMy;

	MaxV=0;
	for(ImagePointerList *p=ImageList.GetFirst();p!=NULL;p=p->GetNext()){

		//double DAvr;
		//double	V=GetArea().GetVar(mx ,my	,*p->GetImage()
        //                        ,DAvr);
		//V=V/DAvr*100.0;
		//MaxV=max(MaxV,V);

		BYTE	Data[10000];
		double	HighL[4];
		ImageBuffer	*B=p->GetImage();
		{
			int	n=0;
			int	X=(x1+x2)/2;
			for(int y=y1;y<y2 && n<FFTLen[0];y++,n++){
				Data[n]=B->GetY(y)[X];
			}
			HighL[0]=CalcFFT(0 ,Data);
		}
		{
			int	Y=(y1+y2)/2;
			BYTE	*s=B->GetY(Y);
			HighL[1]=CalcFFT(1 ,&s[x1]);
		}

		{
			double	Hx=(x2-x1)/(double)FFTLen[2];
			double	Hy=(y2-y1)/(double)FFTLen[2];
			for(int k=0;k<FFTLen[2];k++){
				int	x=x1+Hx*k;
				int	y=y1+Hy*k;
				Data[k]=B->GetY(y)[x];
			}
			HighL[2]=CalcFFT(2 ,Data);
		}

		{
			double	Hx=(x1-x2)/(double)FFTLen[3];
			double	Hy=(y2-y1)/(double)FFTLen[3];
			for(int k=0;k<FFTLen[3];k++){
				int	x=x2+Hx*k;
				int	y=y1+Hy*k;
				Data[k]=B->GetY(y)[x];
			}
			HighL[3]=CalcFFT(3 ,Data);
		}

		for(int i=0;i<4;i++){
			MaxV=max(MaxV,HighL[i]);
		}
	}
	const	BCRInspectionThreshold	*RThr=GetThresholdR();

	BCRGradeList *MinL=NULL;
	for(BCRGradeList *a=RThr->GradeList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Quality<MaxV){
			if(MinL!=NULL){
				if(MinL->Quality<a->Quality){
					MinL=a;
				}
			}
			else{
				MinL=a;
			}
		}
	}
	return MinL;
}
bool	BCRInspectionItem::CheckQuality(ImagePointerContainer &ImageList,ResultInItemRoot *Res)
{
	const	BCRInspectionThreshold	*RThr=GetThresholdR();

	double MaxV;
	BCRGradeList	*MinL=CheckQuality(ImageList,MaxV);
	Res->SetAlignedXY(ResultMx,ResultMy);
	Res->SetResultDouble(MaxV);
	if(MaxV<RThr->QuilityGrade){
		Res->SetError(12);	//NG
	}
	else{
		Res->SetError(1);	//OK
	}
	int	cx,cy;
	GetCenter(cx,cy);
	ResultPosList	*P=new ResultPosList(cx,cy);

	if(MinL!=NULL){	
		P->Message		=MinL->Grade;
	}
	bool	Ret;
	P->SetResult(MaxV);
	if(Res->GetError()==1){
		P->result=1;
		Ret=true;
	}
	else{
		P->result=0x11000;
		Ret=false;
	}
	Res->AddPosList(P);
	Result=QString::number(MaxV,'f',1);
	return Ret;
}

