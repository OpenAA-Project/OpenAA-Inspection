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
#include "XCriticalFunc.h"
#include "swap.h"



void	DotColorMatchingItem::GetAlignmentShift(int	&Mx,int &My)
{
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
		CurrentRotationPatternNo=Clipping((int)(AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
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
		Mx=V.ShiftX;
		My=V.ShiftY;
		CurrentRotationPatternNo=Clipping((int)(V.Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
	}
}
void	DotColorMatchingItem::MakeShiftBrightness(const	DotColorMatchingThreshold	*Th
												,ImageBuffer *ImageTargetList[],int dx, int dy)
{
	CDiffRL=0;
	CDiffRH=0;
	CDiffGL=0;
	CDiffGH=0;
	CDiffBL=0;
	CDiffBH=0;

	int	LayerNumb=GetLayerNumb();
	CenterTargetBrightR=CalcCenterBright(*ImageTargetList[0],dx,dy,TargetSDRL,TargetSDRH);
	if(LayerNumb>=2){
		CenterTargetBrightG=CalcCenterBright(*ImageTargetList[1],dx,dy,TargetSDGL,TargetSDGH);
	}
	if(LayerNumb>=3){
		CenterTargetBrightB=CalcCenterBright(*ImageTargetList[2],dx,dy,TargetSDBL,TargetSDBH);
	}
	

	CDiffRL=CenterTargetBrightR-CenterBrightR - Th->AdjustContribute*abs(TargetSDRL-MasterSDRL)/100;
	CDiffRH=CenterTargetBrightR-CenterBrightR + Th->AdjustContribute*abs(TargetSDRH-MasterSDRH)/100;
	if(CDiffRL>0){
		if(CDiffRL>Th->AdjustWhite){
			CDiffRL=Th->AdjustWhite;
		}
	}
	else if(CDiffRL<0){
		if(-CDiffRL>Th->AdjustBlack){
			CDiffRL=-Th->AdjustBlack;
		}
	}
	if(CDiffRH>0){
		if(CDiffRH>Th->AdjustWhite){
			CDiffRH=Th->AdjustWhite;
		}
	}
	else if(CDiffRH<0){
		if(-CDiffRH>Th->AdjustBlack){
			CDiffRH=-Th->AdjustBlack;
		}
	}

	CDiffGL=CenterTargetBrightG-CenterBrightG - Th->AdjustContribute*abs(TargetSDGL-MasterSDGL)/100;
	CDiffGH=CenterTargetBrightG-CenterBrightG + Th->AdjustContribute*abs(TargetSDGH-MasterSDGH)/100;
	if(CDiffGL>0){
		if(CDiffGL>Th->AdjustWhite){
			CDiffGL=Th->AdjustWhite;
		}
	}
	else if(CDiffGL<0){
		if(-CDiffGL>Th->AdjustBlack){
			CDiffGL=-Th->AdjustBlack;
		}
	}
	if(CDiffGH>0){
		if(CDiffGH>Th->AdjustWhite){
			CDiffGH=Th->AdjustWhite;
		}
	}
	else if(CDiffGH<0){
		if(-CDiffGH>Th->AdjustBlack){
			CDiffGH=-Th->AdjustBlack;
		}
	}
	CDiffBL=CenterTargetBrightB-CenterBrightB - Th->AdjustContribute*abs(TargetSDBL-MasterSDBL)/100;
	CDiffBH=CenterTargetBrightB-CenterBrightB + Th->AdjustContribute*abs(TargetSDBH-MasterSDBH)/100;
	if(CDiffBL>0){
		if(CDiffBL>Th->AdjustWhite){
			CDiffBL=Th->AdjustWhite;
		}
	}
	else if(CDiffBL<0){
		if(-CDiffBL>Th->AdjustBlack){
			CDiffBL=-Th->AdjustBlack;
		}
	}
	if(CDiffBH>0){
		if(CDiffBH>Th->AdjustWhite){
			CDiffBH=Th->AdjustWhite;
		}
	}
	else if(CDiffBH<0){
		if(-CDiffBH>Th->AdjustBlack){
			CDiffBH=-Th->AdjustBlack;
		}
	}
}



bool	DotColorMatchingItem::IsGathered(ResultPosListContainer &MultiSpotGatheredList
										,int MultiSpotCountGathered
										,int MultiSpotLengthGathered)
{
	int	N=MultiSpotGatheredList.GetCount();
	if(N<MultiSpotCountGathered)
		return false;
	ResultPosList	*Dim[1000];
	ResultPosList	**DimPointer;
	ResultPosList	*RDim[1000];
	ResultPosList	**RDimPointer;
	if(N>1000){
		DimPointer	=new ResultPosList*[N];
		RDimPointer	=new ResultPosList*[N];
	}
	else{
		DimPointer	=Dim;
		RDimPointer	=RDim;
	}
	int	index=0;
	for(ResultPosList *r=MultiSpotGatheredList.GetFirst();r!=NULL;r=r->GetNext(),index++){
		DimPointer[index]=r;
	}
	bool	Ret=false;
	for(int i=0;i<N;i++){
		int cx1,cy1,cx2,cy2;
		DimPointer[i]->GetXY(cx1,cy1,cx2,cy2);
		int	cx=(cx1+cx2)/2;
		int	cy=(cy1+cy2)/2;
		RDimPointer[0]=DimPointer[i];
		int	k=1;
		for(int j=i+1;j<N;j++){
			int dx1,dy1,dx2,dy2;
			DimPointer[j]->GetXY(dx1,dy1,dx2,dy2);
			int	dx=(dx1+dx2)/2;
			int	dy=(dy1+dy2)/2;
			if(hypot(cx-dx,cy-dy)<MultiSpotLengthGathered){
				RDimPointer[k]=DimPointer[j];
				k++;
			}
		}
		if(k>=MultiSpotCountGathered){
			for(ResultPosList *r=MultiSpotGatheredList.GetFirst();r!=NULL;){
				ResultPosList	*RNext=r->GetNext();
				int	t;
				for(t=0;t<k;t++){
					if(RDimPointer[t]==r)
						break;
				}
				if(t>=k){
					MultiSpotGatheredList.RemoveList(r);
					delete	r;
				}
				r=RNext;
			}
			Ret=true;
			break;
		}
	}
	if(DimPointer!=Dim){
		delete	[]DimPointer;
		delete	[]RDimPointer;
	}
	return Ret;
}


//========================================================================================================================

double	RotationPattern::CalcMatchByDetail(ImageBuffer *tCurrentBuff ,int dx ,int dy)
{
	FlexArea	&FA=DetailSearchArea;
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

	if(DetailSearchArea.IsNull()==false){
		int		tA=0;
		double	tAA=0;
		int		tB=0;
		double	tBB=0;
		double	tAB=0;
		BMatrix &MasterMap=BuffByMaster[0].Map[AdoptLayer];
		if(0<=LMinX && LMaxX<DotPerLine && 0<=LMinY && LMaxY<MaxLines){
			int		iB=0;
			int		iBB=0;
			int		iAB=0;
			for(int i=0;i<N;i++){
				int	Y	=FA.GetFLineAbsY(i);
				int	MapY=Y-MasterCy+FACy;
				int	X1	=FA.GetFLineLeftX(i);
				int	numb=FA.GetFLineNumb(i);
				BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
				BYTE	*pTP=&TP[X1+dx];
				BYTE	*MP=MasterMap[MapY];	
				if(MP!=NULL){
					BYTE	*pMP=&MP[X1-MasterCx+FACx];
					for(int xn=0;xn<numb;xn++){
						BYTE	t=*(pTP++);
						BYTE	m=*(pMP++);
						tA+=m;
						tAA+=m*m;
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
					tA	+=m*numb;
					tAA	+=m*m*numb;
					iB	+=itSum;
					iAB	+=m*itSum;
				}
				Numb+=numb;
			}
			tB=iB;
			tBB=iBB;
			tAB=iAB;

			tA =DetailA;
			tAA=DetailAA;
		}
		else{
			for(int i=0;i<N;i++){
				int	Y	=FA.GetFLineAbsY(i);
				int	X1	=FA.GetFLineLeftX(i);
				int	numb=FA.GetFLineNumb(i);
				if(0<=Y+dy && Y+dy<MaxLines){
					int	Yn=Y-MasterCy+FACy;
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					int		iA=0;
					int		iAA=0;
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					BYTE	*MP=MasterMap[Yn];
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
		double	AvrS=((double)tA)/Numb;
		double	AvrD=((double)tB)/Numb;

		double	D=(tAA-Numb*AvrS*AvrS)*(tBB-Numb*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=tAB-Numb*AvrS*AvrD;
		return K/D;

	}
	return 0;
}


WORD	DotColorMatchingItem::CalcCenterBright(ImageBuffer &tIBuff ,int mx ,int my ,float &LVar ,float &HVar)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	ImageBufferFast	IBuff(&tIBuff);	

	int	YSep;
	int	XSep;
	FlexArea	&A=GetArea();	//MasterPattern[CurrentRotationPatternNo];
	if(A.GetFLineLen()<20)
		YSep=1;
	else if(A.GetFLineLen()<40)
		YSep=2;
	else if(A.GetFLineLen()<60)
		YSep=3;
	else if(A.GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;
	
	for(int i=0;i<A.GetFLineLen();i+=YSep){
		int	y =A.GetFLineAbsY  (i)+my;
		if(y<0)
			continue;
		if(y>=MaxLines)
			break;
		int	x1=A.GetFLineLeftX (i)+mx;
		int	x2=A.GetFLineRightX(i)+mx;
		if(x1<0)
			x1=0;
		if(x2>=DotPerLine)
			x2=DotPerLine;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		src=IBuff.GetYWithoutDepended(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			BTable[*(src+x)]++;
		}
	}
	int	N=0;
	for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
		N+=BTable[i];
	}
	int	AdoptedRateForCenterBrightness=((DotColorMatchingBase *)GetParentBase())->AdoptedRateForCenterBrightness;
	int	DiscardDot=((N*(100-AdoptedRateForCenterBrightness))/100)/2;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDot){
			break;
		}
	}
	D=0;
	for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
		D+=BTable[HLevel];
		if(D>DiscardDot){
			break;
		}
	}
	N=0;
	double	DSum=0;
	for(int i=LLevel;i<=HLevel;i++){
		N+=BTable[i];
		DSum+=BTable[i]*i;
	}
	double	Avr=(N!=0)?(((double)DSum)/N):0;

	double	BBL=0;
	int		NL=0;
	for(int L=Avr;L>=0;L--){
		double	d=L-Avr;
		BBL+=d*d*BTable[L];
		NL++;
	}
	double	BBH=0;
	int		NH=0;
	for(int H=Avr;H<256;H++){
		double	d=H-Avr;
		BBH+=d*d*BTable[H];
		NH++;
	}
	if(NL!=0){
		LVar=sqrt(((double)BBL)/NL);
	}
	if(NH!=0){
		HVar=sqrt(((double)BBH)/NH);
	}
	return (WORD)Avr;
}
	
void	DotColorMatchingItem::SearchBrightnessH(int Mx ,int My ,int &Lx,int &Ly
												,int AreaSearchX,int AreaSearchY,int MatchBrightnessByLayer)
{
	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *Buff=ImageTargetList[MatchBrightnessByLayer];
	double	MaxAvr=0;
	if(AreaSearchX>=5 || AreaSearchY>=5){
		int	MaxLx=0;
		int	MaxLy=0;
		for(int	dy=-AreaSearchY;dy<=AreaSearchY;dy+=2){
			for(int	dx=-AreaSearchX;dx<=AreaSearchX;dx+=2){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+dx ,My+dy);
				if(MaxAvr<D){
					MaxAvr=D;
					MaxLx=dx;
					MaxLy=dy;
				}
			}
		}
		MaxAvr=0;
		Lx=0;
		Ly=0;
		for(int	dy=-1;dy<=1;dy++){
			for(int	dx=-1;dx<=1;dx++){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+MaxLx+dx ,My+MaxLy+dy);
				if(MaxAvr<D){
					MaxAvr=D;
					Lx=MaxLx+dx;
					Ly=MaxLy+dy;
				}
			}
		}
	}
	else{
		Lx=0;
		Ly=0;
		for(int	dy=-AreaSearchY;dy<=AreaSearchY;dy++){
			for(int	dx=-AreaSearchX;dx<=AreaSearchX;dx++){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+dx ,My+dy);
				if(MaxAvr<D){
					MaxAvr=D;
					Lx=dx;
					Ly=dy;
				}
			}
		}
	}
}

void	DotColorMatchingItem::SearchBrightnessL(int Mx ,int My ,int &Lx,int &Ly
												,int AreaSearchX,int AreaSearchY
												,int MatchBrightnessByLayer)
{
	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *Buff=ImageTargetList[MatchBrightnessByLayer];
	double	MaxAvr=999;
	if(AreaSearchX>=5 || AreaSearchY>=5){
		int	MaxLx=0;
		int	MaxLy=0;
		for(int	dy=-AreaSearchY;dy<=AreaSearchY;dy+=2){
			for(int	dx=-AreaSearchX;dx<=AreaSearchX;dx+=2){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+dx ,My+dy);
				if(MaxAvr>D){
					MaxAvr=D;
					MaxLx=dx;
					MaxLy=dy;
				}
			}
		}
		MaxAvr=999;
		Lx=0;
		Ly=0;
		for(int	dy=-AreaSearchY;dy<=AreaSearchY;dy++){
			for(int	dx=-AreaSearchX;dx<=AreaSearchX;dx++){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+MaxLx+dx ,My+MaxLy+dy);
				if(MaxAvr>D){
					MaxAvr=D;
					Lx=MaxLx+dx;
					Ly=MaxLy+dy;
				}
			}
		}
	}
	else{
		Lx=0;
		Ly=0;
		for(int	dy=-AreaSearchY;dy<=AreaSearchY;dy++){
			for(int	dx=-AreaSearchX;dx<=AreaSearchX;dx++){
				double	D=CurrentMasterPattern->GetAverageOptimized(*Buff,Mx+dx ,My+dy);
				if(MaxAvr>D){
					MaxAvr=D;
					Lx=dx;
					Ly=dy;
				}
			}
		}
	}
}


//==================================================================
FlexAreaCoefXY::FlexAreaCoefXY(void)
{
	LineSumB =NULL;
	LineSumBB=NULL;
	OffsetXToMap=0;
	OffsetYToMap=0;
}
FlexAreaCoefXY::~FlexAreaCoefXY(void)
{
	delete	[]LineSumB;
	LineSumB=NULL;
	delete	[]LineSumBB;
	LineSumBB=NULL;
}

void	FlexAreaCoefXY::SetInitial(int _OffsetXToMap,int _OffsetYToMap ,BMatrix &BMap)
{
	delete	[]LineSumB;
	delete	[]LineSumBB;

	int	M=GetMaxY()-GetMinY()+1;
	LineSumB =new int[M];
	LineSumBB=new double[M];
	OffsetXToMap=_OffsetXToMap;
	OffsetYToMap=_OffsetYToMap;

	int	N=GetFLineLen();
	cA=0;
	cAA=0;
	for(int i=0;i<N;i++){
		int	Y =GetFLineAbsY(i)+OffsetYToMap;
		int	X1=GetFLineLeftX(i)+OffsetXToMap;
		int	numb=GetFLineNumb(i);
		int	iA=0;
		int	iAA=0;
		BYTE	*L=BMap[Y];
		if(L!=NULL){
			BYTE	*s=&L[X1];
			for(int j=0;j<numb;j++){
				BYTE	a=*s++;
				iA+=a;
				iAA+=a*a;
			}
		}
		else{
			BYTE	a=BMap.GetConstantBrightness(Y);
			iA +=a*numb;
			iAA+=a*a*numb;
		}
		cA+=iA;
		cAA+=iAA;
	}
}
void	FlexAreaCoefXY::MakeCalcFirst(int dx ,int dy ,BMatrix &Map ,ImageBuffer *tTargetBuff)
{
	ImageBufferFast TargetBuff(tTargetBuff);

	int	M=GetMaxY()-GetMinY()+1;
	for(int i=0;i<M;i++){
		LineSumB [i]=0;
		LineSumBB[i]=0;
	}
	cAB=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		int	mY =Y+OffsetYToMap;
		int	Yp =Y-GetMinY();
		Y+=dy;
		int	X1=GetFLineLeftX(i);
		int	mX1=X1+OffsetXToMap;
		X1+=dx;
		int	numb=GetFLineNumb(i);
		BYTE	*sL=Map[mY];
		BYTE	*d=&TargetBuff.GetYWithoutDepended(Y)[X1];
		int	iB=0;
		int	iBB=0;
		int	iAB=0;
		if(sL!=NULL){
			BYTE	*s=&sL[mX1];
			for(int j=0;j<numb;j++){
				BYTE	a=*s++;
				BYTE	b=*d++;
				iB+=b;
				iBB+=b*b;
				iAB+=a*b;
			}
		}
		else{
			BYTE	m=Map.GetConstantBrightness(mY);
			int	itSum=0;
			for(int j=0;j<numb;j++){
				BYTE	b=*d++;
				itSum+=b;
				iBB+=b*b;
			}
			iB +=itSum;
			iAB+=m*itSum;
		}
		LineSumB [Yp]+=iB;
		LineSumBB[Yp]+=iBB;
		cAB+=iAB;
	}
}
void	FlexAreaCoefXY::CalcStepX1(int dx ,int dy ,BMatrix &Map ,ImageBuffer *tTargetBuff)
{
	ImageBufferFast TargetBuff(tTargetBuff);
	cAB=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		int	mY =Y+OffsetYToMap;
		int	Yp =Y-GetMinY();
		Y+=dy;
		int	X1=GetFLineLeftX(i);
		int	mX1=X1+OffsetXToMap;
		X1+=dx;
		int	numb=GetFLineNumb(i);
		BYTE	*sL=Map[mY];
		BYTE	*d=&TargetBuff.GetYWithoutDepended(Y)[X1-1];

		BYTE	d1=*d;
		d++;
		BYTE	d2=d[numb-1];
		int	iAB=0;
		if(sL!=NULL){
			BYTE	*s=&sL[mX1-1];
			s++;
			for(int j=0;j<numb;j++){
				BYTE	a=*s++;
				BYTE	b=*d++;
				iAB+=a*b;
			}
		}
		else{
			BYTE	m=Map.GetConstantBrightness(mY);
			int	itSum=0;
			for(int j=0;j<numb;j++){
				BYTE	b=*d++;
				itSum+=b;
			}
			iAB+=m*itSum;
		}
		LineSumB [Yp]+=d2-d1;
		LineSumBB[Yp]+=d2*d2-d1*d1;
		cAB+=iAB;
	}
}
double	FlexAreaCoefXY::CalcCoefWithCheck(int dx ,int dy ,BMatrix &Map ,ImageBuffer *tTargetBuff
										,bool ComplexPattern,double ThresholdWeightForBrDiff)
{
	ImageBufferFast TargetBuff(tTargetBuff);
	double	A=0;
	double	B=0;
	double	AA=0;
	double	BB=0;
	double	AB=0;
	int		Count=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		int	mY =Y+OffsetYToMap;
		Y+=dy;
		if(Y<0 || TargetBuff.GetHeight()<=Y)
			continue;
		int	X1=GetFLineLeftX(i);
		int	numb=GetFLineNumb(i);

		int	mX1=X1+OffsetXToMap;
		int	mX2=mX1+numb;

		X1+=dx;
		int	X2=X1+numb;
		if(X1<0){
			mX1+=-X1;
			X1=0;
		}
		if(TargetBuff.GetWidth()<=X2)
			X2=TargetBuff.GetWidth()-1;

		numb=X2-X1;
		if(numb<=0)
			continue;
		if(mX1+numb>mX2)
			continue;

		BYTE	*d=&TargetBuff.GetYWithoutDepended(Y)[X1];
		int	iA=0;
		int	iB=0;
		int	iAA=0;
		int	iBB=0;
		int	iAB=0;
		BYTE	*sL=Map[mY];
		if(sL!=NULL){
			BYTE	*s=&sL[mX1];
			for(int j=0;j<numb;j++){
				BYTE	a=*s++;
				BYTE	b=*d++;
				iA+=a;
				iB+=b;
				iAA+=a*a;
				iBB+=b*b;
				iAB+=a*b;
			}
		}
		else{
			BYTE	a=Map.GetConstantBrightness(mY);
			int	itSum=0;
			for(int j=0;j<numb;j++){
				BYTE	b=*d++;
				itSum+=b;
				iBB+=b*b;
			}
			iA	+=a*numb;
			iB	+=itSum;
			iAA	+=a*a*numb;
			iAB	+=a*itSum;
		}
		Count+=numb;
		A+=iA;
		B+=iB;
		AA+=iAA;
		BB+=iBB;
		AB+=iAB;
	}

	if(Count<10){
		return 0.0;
	}
	double	AvrS=((double)A)/Count;
	double	AvrD=((double)B)/Count;

	double	D=(AA-Count*AvrS*AvrS)*(BB-Count*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AB-Count*AvrS*AvrD;
	if(ComplexPattern==true){
		return K/D;
	}
	else{
		double	Dif=sqrt((AA-2*AB+BB)/Count)*0.3;
		double	HrR=exp(-(Dif)/ThresholdWeightForBrDiff);
		double	Cf=K/D;
		return HrR*Cf*Cf*Cf;
	}
}
int	FlexAreaCoefXY::GetCalcParam(int &A ,double &AA ,int &B ,double &BB ,double &AB)
{
	int	M=GetMaxY()-GetMinY()+1;
	B=0;
	BB=0;
	AB=0;
	for(int i=0;i<M;i++){
		B+=LineSumB [i];
		BB+=LineSumBB[i];
	}
	A=cA;
	AA=cAA;
	AB=cAB;
	return GetPatternByte();
}
int	FlexAreaCoefXY::GetCalcParam(int &B ,double &BB)
{
	int	M=GetMaxY()-GetMaxY()+1;
	B=0;
	BB=0;
	for(int i=0;i<M;i++){
		B+=LineSumB [i];
		BB+=LineSumBB[i];
	}
	return GetPatternByte();
}
int	FlexAreaCoefXY::GetParamA(int &A ,double &AA)
{
	A=cA;
	AA=cAA;
	return GetPatternByte();
}

void	FlexAreaCoefXY::MakeFlatFirst(int dx ,int dy ,ImageBuffer *tTargetBuff)
{
	ImageBufferFast TargetBuff(tTargetBuff);
	int	M=GetMaxY()-GetMaxY()+1;
	for(int i=0;i<M;i++){
		LineSumB [i]=0;
		LineSumBB[i]=0;
	}
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		int	Yp =Y-GetMinY();
		Y+=dy;
		int	X1=GetFLineLeftX(i);
		X1+=dx;
		int	numb=GetFLineNumb(i);
		BYTE	*d=&TargetBuff.GetYWithoutDepended(Y)[X1];

		int	iB=0;
		int	iBB=0;
		for(int j=0;j<numb;j++){
			BYTE	b=*d++;
			iB+=b;
			iBB+=b*b;
		}
		LineSumB [Yp]+=iB;
		LineSumBB[Yp]+=iBB;
	}
}

void	FlexAreaCoefXY::FlatStepX1(int dx ,int dy ,ImageBuffer *tTargetBuff)
{
	ImageBufferFast TargetBuff(tTargetBuff);
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		int	Yp =Y-GetMinY();
		Y+=dy;
		int	X1=GetFLineLeftX(i);
		X1+=dx;
		int	numb=GetFLineNumb(i);
		BYTE	*d=TargetBuff.GetYWithoutDepended(Y);
		BYTE	d1=d[X1-1];
		BYTE	d2=d[X1+numb-1];
		LineSumB [Yp]+=d2-d1;
		LineSumBB[Yp]+=d2*d2-d1*d1;
	}
}

double	FlexAreaCoefXY::CalcFlatWithCheck(int dx ,int dy ,BMatrix &Map ,ImageBuffer *tTargetBuff)
{
	ImageBufferFast TargetBuff(tTargetBuff);
	double	B=0;
	double	BB=0;
	int		Count=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y  =GetFLineAbsY(i);
		Y+=dy;
		if(Y<0 || TargetBuff.GetHeight()<=Y)
			continue;
		int	X1=GetFLineLeftX(i);
		int	numb=GetFLineNumb(i);

		X1+=dx;
		int	X2=X1+numb;
		if(X1<0){
			X1=0;
		}
		if(TargetBuff.GetWidth()<=X2)
			X2=TargetBuff.GetWidth()-1;

		numb=X2-X1;
		if(numb<=0)
			continue;

		BYTE	*d=&TargetBuff.GetYWithoutDepended(Y)[X1];
		int	iB=0;
		int	iBB=0;
		for(int j=0;j<numb;j++){
			BYTE	b=*d++;
			iB+=b;
			iBB+=b*b;
		}
		Count+=numb;
		B+=iB;
		BB+=iBB;
	}

	if(Count<10){
		return 0.0;
	}

	//double	AvrS=A/Numb;
	double	AvrD=((double)B)/Count;
	double	D=BB/Count-AvrD*AvrD;
	if(D==0)
		return 1.0;
	//double	Diff=AB/Numb - (AvrD-AvrS);
	return 1.0/D;
}

//----

double	DotColorMatchingItem::CalcMatchByAreaSkip(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByAreaSkip(TBuff[R->AdoptLayer] ,dx ,dy);
}

double	DotColorMatchingItem::CalcMatchByAreaFlat(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByAreaFlat(TBuff[R->AdoptLayer] ,dx ,dy);
}


double	DotColorMatchingItem::CalcMatchByAreaFlatRough(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByAreaFlatRough(TBuff[R->AdoptLayer] ,dx ,dy);
}

double	DotColorMatchingItem::CalcMatchByAreaEdge(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByAreaEdge(TBuff[R->AdoptLayer] ,dx ,dy);
}
double	RotationPattern::CalcMatchByAreaEdge(ImageBuffer *CurrentBuff ,int dx ,int dy)
{
	double	D=1.0;
	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
		D*=CalcMatchByAreaEdge(CurrentBuff ,*a ,dx ,dy);
	}
	return D;
}

double	DotColorMatchingItem::CalcMatchByAreaEdgeRough(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByAreaEdgeRough(TBuff[R->AdoptLayer] ,dx ,dy);
}

double	RotationPattern::CalcMatchByAreaEdgeRough(ImageBuffer *CurrentBuff ,int dx ,int dy)
{
	double	D=1.0;
	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
		D*=CalcMatchByAreaEdgeRough(CurrentBuff ,*a ,dx ,dy);
	}
	return D;
}
double	RotationPattern::CalcMatchByAreaEdgeRough(ImageBuffer *tCurrentBuff ,FlexAreaCoef &FA ,int dx ,int dy)
{
	int	LMinX=FA.GetMinX()+dx;
	int	LMinY=FA.GetMinY()+dy;
	int	LMaxX=FA.GetMaxX()+dx;
	int	LMaxY=FA.GetMaxY()+dy;
	int	MasterCx	=Parent->MasterCx;
	int	MasterCy	=Parent->MasterCy;

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
			if(FA.GetPatternByte()<65536){
				int		iB=0;
				int		iBB=0;
				int		iAB=0;
				for(int i=0;i<N;i++){
					int	Y	=FA.GetFLineAbsY(i);
					int	MapY=Y-MasterCy+FACy;
					if(N>32 && ((MapY&0x01)!=0))
						continue;
					int	X1	=FA.GetFLineLeftX(i);
					int	numb=FA.GetFLineNumb(i);
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
					BYTE	*pTP=&TP[X1+dx];
					BYTE	*MP=MasterMap[MapY];	//MBuff[R->AdoptLayer]->GetYWithoutDepended(Y+dy);
					if(MP!=NULL){
						BYTE	*pMP=&MP[X1-MasterCx+FACx];
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							BYTE	m=*pMP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=2;
							pMP+=2;
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(MapY);
						int	itSum=0;
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							itSum+=t;
							iBB+=t*t;
							pTP+=2;
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
					int		iB=0;
					int		iBB=0;
					int		iAB=0;
					BYTE	*pTP=&TP[X1+dx];
					BYTE	*MP=MasterMap[MapY];	//MBuff[R->AdoptLayer]->GetYWithoutDepended(Y+dy);
					if(MP!=NULL){
						BYTE	*pMP=&MP[X1-MasterCx+FACx];
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							BYTE	m=*pMP;
							iB+=t;
							iBB+=t*t;
							iAB+=m*t;
							pTP+=2;
							pMP+=2;
						}
					}
					else{
						BYTE	m=MasterMap.GetConstantBrightness(MapY);
						int	itSum=0;
						for(int xn=0;xn<numb;xn+=2){
							BYTE	t=*pTP;
							itSum+=t;
							iBB+=t*t;
							pTP+=2;
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
					int	Yn=Y-MasterCy+FACy;
					BYTE	*TP=CurrentBuff.GetYWithoutDepended(Y+dy);
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
				for(int xn=0;xn<numb;xn+=2,cTP+=2){
					BYTE	t=*cTP;
					iB+=t;
					iBB+=t*t;
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
					for(int xn=0;xn<numb;xn+=2){
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


//----------------

double	DotColorMatchingItem::CalcMatchByArea(ImageBuffer *TBuff[] ,int dx ,int dy)
{
	RotationPattern	*R=CurrentMasterPattern;
	return R->CalcMatchByArea(TBuff[R->AdoptLayer] ,dx ,dy);
}

double	RotationPattern::SearchMatchByArea	(ImageBuffer *TBuff ,int SearchAreaX ,int SearchAreaY ,int Mx, int My ,int &ResultX ,int &ResultY)
{
	double	MaxD=0;
	if(0<=GetMinX()+Mx-SearchAreaX && GetMaxX()+Mx+SearchAreaX<TBuff->GetWidth()
	&& 0<=GetMinY()+My-SearchAreaY && GetMaxY()+My+SearchAreaY<TBuff->GetHeight()){
		if(FlatPattern==false){
			for(int dy=-SearchAreaY;dy<=SearchAreaY;dy++){
				int	n=0;
				for(int dx=-SearchAreaX;dx<=SearchAreaX;dx++,n++){
					if(n==0)
						MakeCalcFirst(Mx+dx,My+dy ,BuffByMaster[0].Map[AdoptLayer] ,TBuff);
					else
						CalcStepX1(Mx+dx ,My+dy ,BuffByMaster[0].Map[AdoptLayer] ,TBuff);

					double	D=GetMatchByAreaResult();
					if(D>MaxD){
						MaxD=D;
						ResultX=dx;
						ResultY=dy;
					}
				}
			}
		}
		else{
			for(int dy=-SearchAreaY;dy<=SearchAreaY;dy++){
				int	n=0;
				for(int dx=-SearchAreaX;dx<=SearchAreaX;dx++,n++){
					if(n==0)
						MakeFlatFirst(Mx+dx,My+dy ,TBuff);
					else
						FlatStepX1(Mx+dx ,My+dy ,TBuff);

					double	D=GetMatchByAreaResultFlat();
					if(D>MaxD){
						MaxD=D;
						ResultX=dx;
						ResultY=dy;
					}
				}
			}
		}
	}
	else{
		if(FlatPattern==false){
			DotColorMatchingBase	*ABase=(DotColorMatchingBase *)Parent->GetParentBase();
			double ThresholdWeightForBrDiff=ABase->ThresholdWeightForBrDiff;
			for(int dy=-SearchAreaY;dy<=SearchAreaY;dy++){
				int	n=0;
				for(int dx=-SearchAreaX;dx<=SearchAreaX;dx++,n++){
					double	D=CalcCoefWithCheck(Mx+dx,My+dy ,BuffByMaster[0].Map[AdoptLayer] ,TBuff
												,ComplexPattern,ThresholdWeightForBrDiff);
					if(D>MaxD){
						MaxD=D;
						ResultX=dx;
						ResultY=dy;
					}
				}
			}
		}
		else{
			for(int dy=-SearchAreaY;dy<=SearchAreaY;dy++){
				int	n=0;
				for(int dx=-SearchAreaX;dx<=SearchAreaX;dx++,n++){
					double	D=CalcFlatWithCheck(Mx+dx,My+dy ,BuffByMaster[0].Map[AdoptLayer] ,TBuff);
					if(D>MaxD){
						MaxD=D;
						ResultX=dx;
						ResultY=dy;
					}
				}
			}
		}
	}
	return MaxD;
}
double	RotationPattern::GetMatchByAreaResult(void)
{
	int	A,B;
	double AA ,BB ,AB;
	int	Numb=GetCalcParam(A ,AA ,B ,BB ,AB);
	if(Numb<10){
		return 0.0;
	}
	double	AvrS=((double)A)/Numb;
	double	AvrD=((double)B)/Numb;

	double	D=(AA-Numb*AvrS*AvrS)*(BB-Numb*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AB-Numb*AvrS*AvrD;
	if(ComplexPattern==true){
		return K/D;
	}
	else{
		DotColorMatchingBase	*ABase=(DotColorMatchingBase *)Parent->GetParentBase();
		//double	Hs=sqrt(tBB/Numb-AvrD*AvrD);
		//double	Hr=exp(-Hs/ABase->ThresholdWeightForBrDiff);
		double	Dif=sqrt((AA-2*AB+BB)/Numb)*0.3;
		//double	R=exp(-Dif/ABase->ThresholdWeightForBrDiff);
		//double	HrR=exp(-(Hs+Dif)/ABase->ThresholdWeightForBrDiff);
		double	HrR=exp(-(Dif)/ABase->ThresholdWeightForBrDiff);
		double	Cf=K/D;
		return HrR*Cf*Cf*Cf;
	}
}
double	RotationPattern::GetMatchByAreaResultFlat(void)
{
	int	B;
	double BB;
	int	Numb=GetCalcParam(B ,BB);
	if(Numb<10){
		return 0.0;
	}
	//double	AvrS=A/Numb;
	double	AvrD=((double)B)/Numb;

	double	D=BB/Numb-AvrD*AvrD;
	if(D==0)
		return 1.0;
	//double	Diff=AB/Numb - (AvrD-AvrS);
	return 1.0/D;
}
//======================================================================================================================

