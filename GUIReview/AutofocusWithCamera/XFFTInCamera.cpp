#include "AutofocusWithCameraResource.h"
#include "XReviewCameraCommon.h"
#include "AutofocusWithCameraForm.h"
#include "XGeneralFunc.h"
#include "XVRSControlCommand.h"

#include "XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include <QElapsedTimer>
#include "SettingFocusAreaDialog.h"
#include "XDataInLayer.h"
#include "XLightClass.h"

#include"fftw3.h"


double	AutofocusWithCameraForm::CalcRect(QImage &Image,int x1,int y1,int x2,int y2)
{
	int	SIZEX=Image.width()/3;
	int	SIZEY=Image.height()/3;
	int	SIZE=SIZEX*SIZEY;

	fftw_complex *in  = NULL;
	fftw_complex *out = NULL;
	fftw_plan p       = NULL;
	int i,j,idx;

	size_t mem_size = sizeof(fftw_complex) * SIZE;
	in  = (fftw_complex*)fftw_malloc( mem_size );
	out = (fftw_complex*)fftw_malloc( mem_size );

	p=fftw_plan_dft_2d( SIZEY, SIZEX, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

	// input data creation
	for( j=0; j<SIZEY; j++ ){
		int	y=SIZEY+j;
		BYTE	*s=Image.scanLine(y);
		for( i=0; i<SIZEX; i++ ){
			int	x=SIZEX+i;
			idx = SIZEX*j+i; // column-major alignment
			in[idx][0] = s[4*x];
			in[idx][1] = 0;
		}
	}

	fftw_execute(p);

	double	Total=0;
	for( j=0; j<SIZEY/2; j++ ){
		for( i=0; i<SIZEX/2; i++ ){
			idx = SIZEX*j+i; // column-major alignment
			Total += hypot(out[idx][0],	out[idx][1]);
		}
	}
	double	HighL=0;
	for( j=1; j<SIZEY/2-2; j++ ){
		for( i=1; i<SIZEX/2-2; i++ ){
			idx = SIZEX*j+i; // column-major alignment
			//HighL += hypot(out[idx][0],	out[idx][1]);
			//HighL += (out[idx][0],	out[idx][1])*(out[idx][0],	out[idx][1]);
			HighL += out[idx][0]*out[idx][0]+out[idx][1]*out[idx][1];
		}
	}
	return HighL;

	/*
	double	DDr=0;
	double	Dr=0;
	double	DDg=0;
	double	Dg=0;
	double	DDb=0;
	double	Db=0;
	int		N=0;
	for(int y=y1;y<y2;y++){
		QRgb	*s=(QRgb *)Image.scanLine(y);
		for(int x=x1;x<x2;x++){
			int	r=qRed	(s[x]);
			int	g=qGreen(s[x]);
			int	b=qBlue	(s[x]);
			DDr	+=r*r;
			Dr	+=r;
			DDg	+=g*g;
			Dg	+=g;
			DDb	+=b*b;
			Db	+=b;
			N++;
		}
	}
	if(N!=0){
		double	Pa=DDr-(Dr*Dr/N);
		double	Pb=DDg-(Dg*Dg/N);
		double	Pc=DDb-(Db*Db/N);
		if(Pa==0.0 && Pb==0.0 && Pc==0.0)
			return 0.0;
		if(Pa==0.0 && Pb==0.0 && Pc!=0.0)
			return Pc*Pc*Pc;
		if(Pa==0.0 && Pb!=0.0 && Pc==0.0)
			return Pb*Pb*Pb;
		if(Pa!=0.0 && Pb==0.0 && Pc==0.0)
			return Pa*Pa*Pa;
		if(Pa==0.0 && Pb!=0.0 && Pc!=0.0)
			return Pb*sqrt(Pb*Pc)*Pc;
		if(Pa!=0.0 && Pb==0.0 && Pc!=0.0)
			return Pa*sqrt(Pa*Pc)*Pc;
		if(Pa!=0.0 && Pb!=0.0 && Pc==0.0)
			return Pa*sqrt(Pa*Pb)*Pb;
		return Pa*Pb*Pc;
	}
	return 0;
	*/
}

