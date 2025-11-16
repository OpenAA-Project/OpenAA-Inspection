#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"


double	RotationPattern::CalcMatchByArea(ImageBuffer *tTBuff ,int dx ,int dy)
{
	/*
	(An-Bn)^4=(An^2-2AnBn+Bn^2)^2
			 =(An^4-4An^3Bn-4AnBn^3+6An^2Bn^2+Bn^4
	*/
	int	LMinX=GetMinX()+dx;
	int	LMinY=GetMinY()+dy;
	int	LMaxX=GetMaxX()+dx;
	int	LMaxY=GetMaxY()+dy;
	int	MasterCx=Parent->MasterCx;
	int	MasterCy=Parent->MasterCy;

	ImageBufferFast	TBuff(tTBuff);

	int	Numb=0;
	int	N=GetFLineLen();
	int	FACx=XLen/2;
	int	FACy=YLen/2;
	if(FlatPattern==false){
		int		tA=0;
		double	tAA=0;
		int		tB=0;
		double	tBB=0;
		double	tAB=0;
		BMatrix	&MasterMap=BuffByMaster[0].Map[AdoptLayer];
		if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
			for(int i=0;i<N;i++){
				int	Y	=GetFLineAbsY(i);
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				int	Yn=Y-MasterCy+FACy;
				BYTE	*MP=MasterMap[Yn];
				BYTE	*TP=TBuff.GetYWithoutDepended(Y+dy);
				int		iB=0;
				int		iBB=0;
				int		iAB=0;
				BYTE	*pTP=&TP[X1+dx];
				if(MP!=NULL){
					BYTE	*pMP=&MP[X1-MasterCx+FACx];
					for(int xn=0;xn<numb;xn++){
						BYTE	t=*(pTP++);
						BYTE	m=*(pMP++);
						iB+=t;
						iBB+=t*t;
						iAB+=m*t;
					}
				}
				else{
					BYTE	m=MasterMap.GetConstantBrightness(Yn);
					int	itSum=0;
					for(int xn=0;xn<numb;xn++){
						BYTE	t=*(pTP++);						
						itSum+=t;
						iBB+=t*t;
					}

					iB+=itSum;
					iAB+=m*itSum;
				}
				tB+=iB;
				tBB+=iBB;
				tAB+=iAB;
				Numb+=numb;
			}
			GetParamA(tA ,tAA);
		}
		else{
			for(int i=0;i<N;i++){
				int	Y	=GetFLineAbsY(i);
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					int	Yn=Y-MasterCy+FACy;
					BYTE	*MP=MasterMap[Yn];
					BYTE	*TP=TBuff.GetYWithoutDepended(Y+dy);
					int		iA=0;
					int		iAA=0;
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					if(MP!=NULL){
						for(int xn=0;xn<numb;xn++){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	m=MP[X1+xn-MasterCx+FACx];
								BYTE	t=TP[X1+xn+dx];
								iA+=m;
								iAA+=m*m;
								iB+=t;
								iBB+=t*t;
								iAB+=m*t;
								Numb++;
							}
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(Yn);
						int	iNumb=0;
						int	itSum=0;
						for(int xn=0;xn<numb;xn++){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	t=TP[X1+xn+dx];
								itSum+=t;
								iBB+=t*t;
								iNumb++;
							}
						}
						iA	+=m*iNumb;
						iAA	+=m*m*iNumb;
						iB	+=itSum;
						iAB	+=m*itSum;
						Numb+=iNumb;
					}					
					tA	+=iA;
					tAA	+=iAA;
					tB	+=iB;
					tBB	+=iBB;
					tAB	+=iAB;
				}
			}
		}
		if(Numb<10){
			return 0.0;
		}
		double	AvrS=((double)tA)/((double)Numb);
		double	AvrD=((double)tB)/((double)Numb);

		double	D=(tAA-Numb*AvrS*AvrS)*(tBB-Numb*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=tAB-Numb*AvrS*AvrD;
		if(ComplexPattern==true){
			return K/D;
		}
		else{
			DotColorMatchingBase	*ABase=(DotColorMatchingBase *)Parent->GetParentBase();
			//double	Hs=sqrt(tBB/Numb-AvrD*AvrD);
			//double	Hr=exp(-Hs/ABase->ThresholdWeightForBrDiff);
			double	Dif=sqrt((tAA-2*tAB+tBB)/Numb)*0.3;
			//double	R=exp(-Dif/ABase->ThresholdWeightForBrDiff);
			//double	HrR=exp(-(Hs+Dif)/ABase->ThresholdWeightForBrDiff);
			double	HrR=exp(-(Dif)/ABase->ThresholdWeightForBrDiff);
			double	Cf=K/D;
			return HrR*Cf*Cf*Cf;
		}
	}
	else{
		//double	A=0;
		int		tB=0;
		double	tBB=0;
		if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
			for(int i=0;i<N;i++){
				int	Y	=GetFLineAbsY(i);
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				BYTE	*TP=TBuff.GetYWithoutDepended(Y+dy);
				int		iB=0;
				int		iBB=0;
				BYTE	*cTP=&TP[X1+dx];
				for(int xn=0;xn<numb;xn++){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
					cTP++;
				}

				Numb+=numb;
				tB	+=iB;
				tBB	+=iBB;
			}
		}
		else{
			for(int i=0;i<N;i++){
				int	Y	=GetFLineAbsY(i);
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					BYTE	*TP=TBuff.GetYWithoutDepended(Y+dy);
					//int		iA=0;
					int		iB=0;
					int		iBB=0;
					//int		iAB=0;
					for(int xn=0;xn<numb;xn++){
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							BYTE	t=TP[X1+dx+xn];
							iB+=t;
							iBB+=t*t;
							Numb++;
						}
					}
					tB	+=iB;
					tBB	+=iBB;
				}
			}
		}
		if(Numb<10){
			return 0.0;
		}
		//double	AvrS=A/Numb;
		double	AvrD=((double)tB)/((double)Numb);

		double	D=tBB/Numb-AvrD*AvrD;
		if(D==0)
			return 1.0;
		//double	Diff=AB/Numb - (AvrD-AvrS);
		return 1.0/D;
	}
}


double	RotationPattern::CalcMatchByAreaSkip(ImageBuffer *tTBuffer ,int dx ,int dy)
{
	int	LMinX=GetMinX()+dx;
	int	LMinY=GetMinY()+dy;
	int	LMaxX=GetMaxX()+dx;
	int	LMaxY=GetMaxY()+dy;

	int	Numb=0;
	int	N=GetFLineLen();
	int	FACx=XLen/2;
	int	FACy=YLen/2;
	int	MasterCx=Parent->MasterCx;
	int	MasterCy=Parent->MasterCy;

	int		tA=0;
	double	tAA=0;
	int		tB=0;
	double	tBB=0;
	double	tAB=0;
	BMatrix	&MasterMap=BuffByMaster[0].Map[AdoptLayer];
	ImageBufferFast TBuffer(tTBuffer);

	if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
		for(int i=0;i<N;i++){
			int	Y	=GetFLineAbsY(i);
			int	MapY=Y-MasterCy+FACy;
			if((MapY&0x01)==0){
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				BYTE	*TP=TBuffer.GetYWithoutDepended(Y+dy);
				int		iB=0;
				int		iBB=0;
				int		iAB=0;
				BYTE	*pTP=&TP[X1+dx];
				BYTE	*MP=MasterMap[MapY];	//MBuff[R->AdoptLayer]->GetYWithoutDepended(Y+dy);
				if(MP!=NULL){
					BYTE	*pMP=&MP[X1-MasterCx+FACx];

					if(numb<=32){
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							BYTE	m=*(pMP++);
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
						}
						Numb+=numb;
					}
					else
					if(numb<=64){
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							BYTE	m=*pMP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=2;
							pMP+=2;
						}
						Numb+=(numb+1)>>1;
					}
					else{
						for(int xn=0;xn<numb;xn+=4){
							BYTE	t=*pTP;
							BYTE	m=*pMP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=4;
							pMP+=4;
						}
						Numb+=(numb+3)>>2;
					}
				}
				else{
					BYTE	m=MasterMap.GetConstantBrightness(MapY);
					if(numb<=32){
						int	itSum=0;
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							itSum+=t;
							iBB+=t*t;
						}
						iB+=itSum;
						iAB+=m*itSum;
						Numb+=numb;
					}
					else
					if(numb<=64){
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=2;
						}
						Numb+=(numb+1)>>1;
					}
					else{
						for(int xn=0;xn<numb;xn+=4){
							BYTE	t=*pTP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=4;
						}
						Numb+=(numb+3)>>2;
					}
				}
				tB+=iB;
				tBB+=iBB;
				tAB+=iAB;
			}
		}
		tA =SkipA[AdoptLayer];
		tAA=SkipAA[AdoptLayer];
	}
	else{
		for(int i=0;i<N;i++){
			int	Y	=GetFLineAbsY(i);
			if((Y&0x01)==0){
				int	X1	=GetFLineLeftX(i);
				int	numb=GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					int	Yn=Y-MasterCy+FACy;
					BYTE	*TP=TBuffer.GetYWithoutDepended(Y+dy);
					int		iA=0;
					int		iAA=0;
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					BYTE	*MP=MasterMap[Yn];
					if(MP!=NULL){
						for(int xn=0;xn<numb;xn+=2){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	m=MP[X1+xn-MasterCx+FACx];
								BYTE	t=TP[X1+xn+dx];
								iA+=m;
								iAA+=m*m;
								iB+=t;
								iBB+=t*t;
								iAB+=m*t;
								Numb++;
								}
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(Yn);
						int	itSum=0;
						int	iNumb=0;
						for(int xn=0;xn<numb;xn+=2){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	t=TP[X1+xn+dx];
								itSum+=t;
								iBB+=t*t;
								iNumb++;
							}
						}
						iA	+=m*iNumb;
						iAA	+=m*m*iNumb;
						iB	+=itSum;
						iAB	+=m*itSum;
						Numb+=iNumb;					
					}
					tA	+=iA;
					tAA	+=iAA;
					tB	+=iB;
					tBB	+=iBB;
					tAB	+=iAB;
				}
			}
		}
	}
	if(Numb<10){
		return 0.0;
	}
	double	AvrS=((double)tA)/Numb;
	double	AvrD=((double)tB)/Numb;

	double	D=(tAA-Numb*AvrS*AvrS)*(tBB-Numb*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=tAB-Numb*AvrS*AvrD;
	//return AvrD*K/D;
	double	W=fabs(AvrS-AvrD);

	double	Z=AvrS+5;
	double	M=exp(-W/Z);
	return M*K/D;
}

double	RotationPattern::CalcMatchByAreaFlat(ImageBuffer *tCurrentBuff ,int dx ,int dy)
{
	FlexArea	&FA=OutlineArea;
	int	LMinX=FA.GetMinX()+dx;
	int	LMinY=FA.GetMinY()+dy;
	int	LMaxX=FA.GetMaxX()+dx;
	int	LMaxY=FA.GetMaxY()+dy;

	int	Numb=0;
	int	N=FA.GetFLineLen();

	//double	A=0;
	int		tB=0;
	double	tBB=0;
	double	CenterAvr=0;

	ImageBufferFast CurrentBuff(tCurrentBuff);

	if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
		for(int i=0;i<N;i++){
			int	Y	=FA.GetFLineAbsY(i);
			int	X1	=FA.GetFLineLeftX(i);
			int	numb=FA.GetFLineNumb(i);
			BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
			//int		iA=0;
			int		iB=0;
			int		iBB=0;
			//int		iAB=0;
			BYTE	*cTP=&TP[X1+dx];
			if((Y&1)==0){
				numb=(numb+1)>>1;
				for(int xn=0;xn<numb;xn++,cTP+=2){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
				}
				Numb+=numb;
			}
			else{
				cTP++;
				numb=numb>>1;
				//for(int xn=1;xn<numb;xn+=2,cTP+=2){
				for(int xn=0;xn<numb;xn++,cTP+=2){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
				}
				Numb+=numb;
			}
			
			//A	+=iA;
			tB	+=iB;
			tBB	+=iBB;
			//AB	+=iAB;
		}
		int	CenterN=GetFLineLen()/2;
		int	Cd=0;
		int	CdNumb=0;
		for(int i=-1;i<=1;i++){
			int	NN=CenterN+i;
			if(0<=NN && NN<GetFLineLen()){
				int	Y	=GetFLineAbsY(NN);
				int	X1	=GetFLineLeftX(NN);
				int	numb=GetFLineNumb(NN);
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				BYTE	*cTP=&TP[X1+dx];
				int	CenterXn=numb/2;
				if(1<=CenterXn && (CenterXn+1)<numb){
					for(int j=-1;j<=1;j++){
						Cd+=cTP[CenterXn+j];
						CdNumb++;
					}
				}
				else{
					for(int j=-1;j<=1;j++){
						if(0<=CenterXn+j && (CenterXn+j)<numb){
							Cd+=cTP[CenterXn+j];
							CdNumb++;
						}
					}
				}
			}
		}
		if(CdNumb==0)
			return 0.0;
		CenterAvr=((double)Cd)/CdNumb;
	}
	else{
		for(int i=0;i<N;i++){
			int	Y	=FA.GetFLineAbsY(i);
			int	X1	=FA.GetFLineLeftX(i);
			int	numb=FA.GetFLineNumb(i);
			if(0<=Y+dy && Y+dy<MaxLines){
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				//int		iA=0;
				int		iB=0;
				int		iBB=0;
				//int		iAB=0;
				if((Y&1)==0){
					for(int xn=0;xn<numb;xn+=2){
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							BYTE	t=TP[X1+dx+xn];
							iB+=t;
							iBB+=t*t;
							Numb++;
						}
					}
				}
				else{
					for(int xn=1;xn<numb;xn+=2){
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							BYTE	t=TP[X1+dx+xn];
							iB+=t;
							iBB+=t*t;
							Numb++;
						}
					}
				}
				tB	+=iB;
				tBB	+=iBB;
			}
		}
		int	CenterN=GetFLineLen()/2;
		int	Cd=0;
		int	CdNumb=0;
		for(int i=-1;i<=1;i++){
			int	NN=CenterN+i;
			if(0<=NN && NN<GetFLineLen()){
				int	Y	=GetFLineAbsY(NN);
				if(0<=Y+dy && Y+dy<MaxLines){
					int	X1	=GetFLineLeftX(NN);
					int	numb=GetFLineNumb(NN);
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					BYTE	*cTP=&TP[X1+dx];
					int	CenterXn=numb/2;
					for(int j=-1;j<=1;j++){
						int	xn=CenterXn+j;
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							Cd+=cTP[xn];
							CdNumb++;
						}
					}
				}
			}
		}
		if(CdNumb==0)
			return 0.0;
		CenterAvr=((double)Cd)/CdNumb;
	}
	if(Numb<10){
		return 0.0;
	}
	double	AvrD=((double)tB)/Numb;
	double	D=tBB/Numb-AvrD*AvrD;
	if(D==0)
		return 1.0;
	int		A;
	double	AA;
	int	ACalcNumb=GetParamA(A ,AA);
	double	AvrS=((double)A)/ACalcNumb;
	double	F=fabs(AvrS-CenterAvr)+1;
	//double	Diff=AB/Numb - (AvrD-AvrS);
	return 1.0/(D*F);
}

double	RotationPattern::CalcMatchByAreaFlatRough(ImageBuffer *tCurrentBuff ,int dx ,int dy)
{
	FlexArea	&FA=OutlineArea;
	int	LMinX=FA.GetMinX()+dx;
	int	LMinY=FA.GetMinY()+dy;
	int	LMaxX=FA.GetMaxX()+dx;
	int	LMaxY=FA.GetMaxY()+dy;

	ImageBufferFast CurrentBuff(tCurrentBuff);
	int	Numb=0;
	int	N=FA.GetFLineLen();
	//double	A=0;
	int		tB=0;
	double	tBB=0;
	double	CenterAvr=0;
	if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
		int		iB=0;
		int		iBB=0;
		for(int i=0;i<N;i++){
			int	Y	=FA.GetFLineAbsY(i);
			int	X1	=FA.GetFLineLeftX(i);
			int	numb=FA.GetFLineNumb(i);
			BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
			BYTE	*cTP=&TP[X1+dx];
			//if((Y&0x03)==0 || i==0 || (i+1)==N){
				int	knumb=(numb+3)>>2;
				for(int xn=0;xn<knumb;xn++,cTP+=4){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
				}
				Numb+=knumb;
			//}
			BYTE	t=TP[X1+dx+numb-1];
			iB+=t;
			iBB+=t*t;
			Numb++;
		}

		//A	+=iA;
		tB	+=iB;
		tBB	+=iBB;
		//AB	+=iAB;

		int	CenterN=GetFLineLen()/2;
		int	Cd=0;
		int	CdNumb=0;
		for(int i=-1;i<=1;i++){
			int	NN=CenterN+i;
			if(0<=NN && NN<GetFLineLen()){
				int	Y	=GetFLineAbsY(NN);
				int	X1	=GetFLineLeftX(NN);
				int	numb=GetFLineNumb(NN);
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				BYTE	*cTP=&TP[X1+dx];
				int	CenterXn=numb/2;
				if(1<=CenterXn && (CenterXn+1)<numb){
					for(int j=-1;j<=1;j++){
						Cd+=cTP[CenterXn+j];
						CdNumb++;
					}
				}
				else{
					for(int j=-1;j<=1;j++){
						if(0<=(CenterXn+j) && (CenterXn+j)<numb){
							Cd+=cTP[CenterXn+j];
							CdNumb++;
						}
					}
				}
			}
		}
		if(CdNumb==0)
			return 0.0;
		CenterAvr=((double)Cd)/CdNumb;
	}
	else{
		for(int i=0;i<N;i++){
			int	Y	=FA.GetFLineAbsY(i);
			int	X1	=FA.GetFLineLeftX(i);
			int	numb=FA.GetFLineNumb(i);
			if(0<=Y+dy && Y+dy<MaxLines){
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				//int		iA=0;
				int		iB=0;
				int		iBB=0;
				//int		iAB=0;
				//if((Y&0x01)==0){
					for(int xn=0;xn<numb;xn+=4){
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							BYTE	t=TP[X1+dx+xn];
							iB+=t;
							iBB+=t*t;
							Numb++;
						}
					}
				//}
				tB	+=iB;
				tBB	+=iBB;
			}
		}
		int	CenterN=GetFLineLen()/2;
		int	Cd=0;
		int	CdNumb=0;
		for(int i=-1;i<=1;i++){
			int	NN=CenterN+i;
			if(0<=NN && NN<GetFLineLen()){
				int	Y	=GetFLineAbsY(NN);
				if(0<=Y+dy && Y+dy<MaxLines){
					int	X1	=GetFLineLeftX(NN);
					int	numb=GetFLineNumb(NN);
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					BYTE	*cTP=&TP[X1+dx];
					int	CenterXn=numb/2;
					if(1<=CenterXn && (CenterXn+1)<numb){
						for(int j=-1;j<=1;j++){
							int	xn=CenterXn+j;
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								Cd+=cTP[xn];
								CdNumb++;
							}
						}
					}
				}
			}
		}
		if(CdNumb==0)
			return 0.0;
		CenterAvr=((double)Cd)/CdNumb;
	}
	if(Numb<10){
		return 0.0;
	}
	double	AvrD=((double)tB)/Numb;
	double	D=tBB/Numb-AvrD*AvrD;
	if(D==0)
		return 1.0;
	int		A;
	double	AA;
	int	ACalcNumb=GetParamA(A ,AA);
	double	AvrS=((double)A)/ACalcNumb;
	DotColorMatchingBase	*ABase=(DotColorMatchingBase *)Parent->GetParentBase();
	double	F=fabs(AvrS-CenterAvr)/ABase->DifBrightnessForFlatArea;	//128.0;
	double	R=exp(-F);
	//double	Diff=AB/Numb - (AvrD-AvrS);
	return R/D;
}


double	RotationPattern::CalcMatchByAreaEdge(ImageBuffer *tCurrentBuff ,FlexAreaCoef	&FA ,int dx ,int dy)
{
	int	LMinX=FA.GetMinX()+dx;
	int	LMinY=FA.GetMinY()+dy;
	int	LMaxX=FA.GetMaxX()+dx;
	int	LMaxY=FA.GetMaxY()+dy;
	int	MasterCx=Parent->MasterCx;
	int	MasterCy=Parent->MasterCy;

	ImageBufferFast CurrentBuff(tCurrentBuff);
	int	Numb=0;
	int	N=FA.GetFLineLen();
	int	FACx=XLen/2;
	int	FACy=YLen/2;

	if(DivArea.IsNull()==false){
		int		tA=0;
		double	tAA=0;
		int		tB=0;
		double	tBB=0;
		double	tAB=0;
		BMatrix &MasterMap=BuffByMaster[0].Map[AdoptLayer];
		if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
			if(FA.GetPatternByte()<65536
			&& (FA.GetWidth()<20 || FA.GetHeight()<20)){
				int		iB=0;
				int		iBB=0;
				int		iAB=0;
				for(int i=0;i<N;i++){
					int	Y	=FA.GetFLineAbsY(i);
					int	MapY=Y-MasterCy+FACy;
					//if(N>32 && ((MapY&0x01)!=0))
					//	continue;
					int	X1	=FA.GetFLineLeftX(i);
					int	numb=FA.GetFLineNumb(i);
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					BYTE	*pTP=&TP[X1+dx];
					BYTE	*MP=MasterMap[MapY];	//MBuff[R->AdoptLayer]->GetYWithoutDepended(Y+dy);
					if(MP!=NULL){
						BYTE	*pMP=&MP[X1-MasterCx+FACx];
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							BYTE	m=*(pMP++);
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(MapY);
						int	itSum=0;
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							itSum+=t;
							iBB+=t*t;
						}
						iB	+=itSum;
						iAB	+=m*itSum;
					}
					Numb+=numb;
				}
				tB=iB;
				tBB=iBB;
				tAB=iAB;
			}
			else{
				for(int i=0;i<N;i++){
					int	Y	=FA.GetFLineAbsY(i);
					int	MapY=Y-MasterCy+FACy;
					if(N>32 && ((MapY&0x01)!=0))
						continue;
					int	X1	=FA.GetFLineLeftX(i);
					int	numb=FA.GetFLineNumb(i);
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					BYTE	*pTP=&TP[X1+dx];
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					BYTE	*MP=MasterMap[MapY];	//MBuff[R->AdoptLayer]->GetYWithoutDepended(Y+dy);
					if(MP!=NULL){
						BYTE	*pMP=&MP[X1-MasterCx+FACx];
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							BYTE	m=*(pMP++);
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(MapY);
						int	itSum=0;
						for(int xn=0;xn<numb;xn++){
							BYTE	t=*(pTP++);
							itSum+=t;
							iBB+=t*t;
						}
						iB	+=itSum;
						iAB	+=m*itSum;
					}
					tB+=iB;
					tBB+=iBB;
					tAB+=iAB;
					Numb+=numb;
				}
			}
			tA =FA.DivA[AdoptLayer];
			tAA=FA.DivAA[AdoptLayer];
		}
		else{
			for(int i=0;i<N;i++){
				int	Y	=FA.GetFLineAbsY(i);
				int	X1	=FA.GetFLineLeftX(i);
				int	numb=FA.GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					int		Yn=Y-MasterCy+FACy;
					BYTE	*MP=MasterMap[Yn];
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					int		iA=0;
					int		iAA=0;
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					if(MP!=NULL){
						for(int xn=0;xn<numb;xn++){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	m=MP[X1+xn-MasterCx+FACx];
								BYTE	t=TP[X1+xn+dx];
								iA+=m;
								iAA+=m*m;
								iB+=t;
								iBB+=t*t;
								iAB+=m*t;
								Numb++;
								}
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(Yn);
						int	itSum=0;
						int	iNumb=0;
						for(int xn=0;xn<numb;xn++){
							if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
								BYTE	t=TP[X1+xn+dx];
								itSum+=t;
								iBB	 +=t*t;
								iNumb++;
							}
						}
						iA	+=m*iNumb;
						iAA	+=m*m*iNumb;
						iB	+=itSum;
						iAB	+=m*itSum;
						Numb+=iNumb;
					}
					tA	+=iA;
					tAA	+=iAA;
					tB	+=iB;
					tBB	+=iBB;
					tAB	+=iAB;
				}
			}
		}
		if(Numb<10){
			return 0.0;
		}
		double	AvrS=((double)tA)/Numb;
		double	AvrD=((double)tB)/Numb;

		double	D=(tAA-Numb*AvrS*AvrS)*(tBB-Numb*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=tAB-Numb*AvrS*AvrD;
		return K/D;
		/*
		double	W=fabs(AvrS-AvrD);

		double	Z=AvrS+5;
		double	R=exp(-W/Z);
		return R*K/D;
		*/
	}
	else{
		//double	A=0;
		int		tB=0;
		double	tBB=0;
		if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
			for(int i=0;i<N;i++){
				int	Y	=FA.GetFLineAbsY(i);
				int	X1	=FA.GetFLineLeftX(i);
				int	numb=FA.GetFLineNumb(i);
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				//int		iA=0;
				int		iB=0;
				int		iBB=0;
				//int		iAB=0;
				BYTE	*cTP=&TP[X1+dx];
				for(int xn=0;xn<numb;xn++){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
					cTP++;
					//iAB+=m*t;
				}
				Numb+=numb;
				//A	+=iA;
				tB	+=iB;
				tBB	+=iBB;
				//AB	+=iAB;
			}
		}	
		else{
			for(int i=0;i<N;i++){
				int	Y	=FA.GetFLineAbsY(i);
				int	X1	=FA.GetFLineLeftX(i);
				int	numb=FA.GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					//int		iA=0;
					int		iB=0;
					int		iBB=0;
					//int		iAB=0;
					for(int xn=0;xn<numb;xn++){
						if(0<=(X1+xn+dx) && (X1+xn+dx)<DotPerLine){
							BYTE	t=TP[X1+dx+xn];
							iB+=t;
							iBB+=t*t;
							Numb++;
						}
					}
					tB	+=iB;
					tBB	+=iBB;
				}
			}
		}
		if(Numb<10){
			return 0.0;
		}
		//double	AvrS=A/Numb;
		double	AvrD=((double)tB)/Numb;

		double	D=tBB/Numb-AvrD*AvrD;
		if(D==0)
			return 1.0;
		//double	Diff=AB/Numb - (AvrD-AvrS);
		return 1.0/D;
	}
}