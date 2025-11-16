
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XImageProcess.h"

/*
double	XAlignmentLarge::MatchItem(ImageBuffer &Master ,ImageBuffer &Target ,int dx,int dy)
{
	double AddedS =RootAddedS;
	double AddedSS=RootAddedSS;
	double AddedD =0;
	double AddedDD=0;
	double AddedSD=0;
	double SDCount=0;

	int	N=GetArea().GetFLineLen();
	for(int n=0;n<N;n++){
		int	Y	=GetArea().GetFLineAbsY(n);
		int	X1	=GetArea().GetFLineLeftX(n);
		int	Numb=GetArea().GetFLineNumb(n);
		BYTE	*s=Master.GetY(Y)+X1;
		BYTE	*d=Target.GetY(Y+dy)+X1+dx;

		int tAddedD =0;
		int tAddedDD=0;
		int tAddedSD=0;

		while(Numb>=8){
			BYTE	a0=*(s+0);
			BYTE	a1=*(s+1);
			BYTE	a2=*(s+2);
			BYTE	a3=*(s+3);
			BYTE	a4=*(s+4);
			BYTE	a5=*(s+5);
			BYTE	a6=*(s+6);
			BYTE	a7=*(s+7);
			BYTE	b0=*(d+0);
			BYTE	b1=*(d+1);
			BYTE	b2=*(d+2);
			BYTE	b3=*(d+3);
			BYTE	b4=*(d+4);
			BYTE	b5=*(d+5);
			BYTE	b6=*(d+6);
			BYTE	b7=*(d+7);
			tAddedD	+=b0+b1+b2+b3+b4+b5+b6+b7;
			tAddedDD+=b0*b0+b1*b1+b2*b2+b3*b3+b4*b4+b5*b5+b6*b6+b7*b7;
			tAddedSD+=a0*b0+a1*b1+a2*b2+a3*b3+a4*b4+a5*b5+a6*b6+a7*b7;
			s+=8;
			d+=8;
			Numb-=8;
		}
		for(int i=0;i<Numb;i++){
			BYTE	a=*s;
			BYTE	b=*d;
			tAddedD	+=b;
			tAddedDD+=b*b;
			tAddedSD+=a*b;
			s++;
			d++;
		}
		AddedD	+= tAddedD; 
		AddedDD	+= tAddedDD;
		AddedSD	+= tAddedSD;
		SDCount	+= Numb;
	}
	if(SDCount<1){
		return 0;
	}
	double	SDCountD=1.0/(double)SDCount;
	double	AvrS=((double)AddedS)*SDCountD;
	double	AvrD=((double)AddedD)*SDCountD;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}
*/