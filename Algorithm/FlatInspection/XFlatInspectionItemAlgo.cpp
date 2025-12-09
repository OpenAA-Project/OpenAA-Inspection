#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "XBitImageProcessor.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"



void	FlatInspectionItem::MakeMaskArea(void)
{
	const	FlatInspectionThreshold	*RThr=GetThresholdR();

	int	Layer;
	int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	ImageBuffer		*Image=TargetImageList[Layer];

	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y	=GetArea().GetFLineAbsY(i);
		int	X1	=GetArea().GetFLineLeftX(i);
		int	Numb=GetArea().GetFLineNumb(i);

		int	Counter=0;
		BYTE	*s=Image->GetY(Y);
		for(int n=0;n<Numb;n++){
			if(*(s+X1+n)>=Mid){
				Counter++;
			}
		}
		if(Counter>100){
			ResultY1=Y;
			break;
		}
	}
	for(int i=N-1;i>=0;i--){
		int	Y	=GetArea().GetFLineAbsY(i);
		int	X1	=GetArea().GetFLineLeftX(i);
		int	Numb=GetArea().GetFLineNumb(i);

		int	Counter=0;
		BYTE	*s=Image->GetY(Y);
		for(int n=0;n<Numb;n++){
			if(*(s+X1+n)>=Mid){
				Counter++;
			}
		}
		if(Counter>100){
			ResultY2=Y;
			break;
		}
	}

	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	int	ImageH=Image->GetHeight();
	int	BandHeight=100;
	int	BandNumb=(ResultY2-ResultY1+1)/BandHeight;
	if(BandNumb>0){
		BandHeight=(ResultY2-ResultY1+1+BandNumb-1)/BandNumb;
		ResultMinX=99999999;
		ResultMaxX=-99999999;

		#pragma omp parallel
		{
			#pragma omp for
			for(int B=0;B<BandNumb;B++){
				int	X1,X2;
				for(int x=x1;x<x2;x++){
					int	Counter=0;
					for(int yn=0;yn<BandHeight;yn++){
						int	Y=yn+ResultY1+B*BandHeight;
						if(Y<ImageH){
							BYTE	*s=Image->GetY(Y);
							if(s[x]>=Mid){
								Counter++;
							}
						}
					}
					if(Counter>BandHeight/4){
						X1=x;
						break;
					}
				}
				for(int x=x2;x>=x1;x--){
					int	Counter=0;
					for(int yn=0;yn<BandHeight;yn++){
						int	Y=yn+ResultY1+B*BandHeight;
						if(Y<ImageH){
							BYTE	*s=Image->GetY(Y);
							if(s[x]>=Mid){
								Counter++;
							}
						}
					}
					if(Counter>BandHeight/4){
						X2=x;
						break;
					}
				}
				ResultMinX=min(ResultMinX,X1+RThr->SpaceToOutline);
				ResultMaxX=max(ResultMaxX,X2-RThr->SpaceToOutline);

				int	tY1=ResultY1+ B*BandHeight;
				int	tY2=ResultY1+(B+1)*BandHeight;
				if(tY1<ResultY1+RThr->SpaceToOutline)
					tY1=ResultY1+RThr->SpaceToOutline;
				if(tY2>ResultY2-RThr->SpaceToOutline)
					tY2=ResultY2-RThr->SpaceToOutline;


				if(B==0){
					int	W=X2-X1-2*RThr->SpaceToOutline;
					int	WNumb=9;
					int	WStep=(W+WNumb-1)/WNumb;
					for(int xn=0;xn<WNumb;xn++){
						int	wx1=X1+RThr->SpaceToOutline+xn*WStep;
						int	wx2=wx1+WStep;
						if(wx2>=(X2-RThr->SpaceToOutline))
							wx2= X2-RThr->SpaceToOutline;

						int	py=0;
						for(int i=0;i<N;i++){
							int	Y	=GetArea().GetFLineAbsY(i);
							int	X1	=GetArea().GetFLineLeftX(i);
							int	Numb=GetArea().GetFLineNumb(i);

							int	Counter=0;
							BYTE	*s=Image->GetY(Y);
							for(int n=0;n<Numb;n++){
								int	xi=X1+n;
								if(wx1<=xi && xi<wx2){
									if(*(s+xi)>=Mid){
										Counter++;
									}
								}
								if(Counter>WStep/3){
									py=Y+RThr->SpaceToOutline;							
									goto	TopE;;
								}
							}
						}
						TopE:;
						DrawBitRectangle(tGetParentInPage()->MaskMap
								,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen
								,wx1, py
								,wx2, tY2);
					}
				}
				else if(B==BandNumb-1){
					int	W=X2-X1-2*RThr->SpaceToOutline;
					int	WNumb=9;
					int	WStep=(W+WNumb-1)/WNumb;
					for(int xn=0;xn<WNumb;xn++){
						int	wx1=X1+RThr->SpaceToOutline+xn*WStep;
						int	wx2=wx1+WStep;
						if(wx2>=(X2-RThr->SpaceToOutline))
							wx2= X2-RThr->SpaceToOutline;

						int	py=0;
						for(int i=N-1;i>=0;i--){
							int	Y	=GetArea().GetFLineAbsY(i);
							int	X1	=GetArea().GetFLineLeftX(i);
							int	Numb=GetArea().GetFLineNumb(i);

							int	Counter=0;
							BYTE	*s=Image->GetY(Y);
							for(int n=0;n<Numb;n++){
								if(*(s+X1+n)>=Mid){
									Counter++;
								}
							}
							if(Counter>100){
								py=Y-RThr->SpaceToOutline;
								goto	EndE;
							}
						}
						EndE:;
						DrawBitRectangle(tGetParentInPage()->MaskMap
								,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen
								,wx1, tY1
								,wx2, py);
					}
				}
				else{
					DrawBitRectangle(tGetParentInPage()->MaskMap
								,tGetParentInPage()->MaskMapXByte ,tGetParentInPage()->MaskMapYLen
								,X1+RThr->SpaceToOutline, tY1
								,X2-RThr->SpaceToOutline, tY2);
				}
			}
		}
	}
}

void	FlatInspectionItem::SearchMax(int mx ,int my ,int &Dx ,int &Dy)
{
	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	int	Layer;
	int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	ImageBuffer		*Image=TargetImageList[Layer];

	int		wx=0;
	int		wy=0;
	int64	BrightSum=0;

	#pragma omp parallel                             
	{                                                
		#pragma omp for	
		for(int i=0;i<DimCount;i++){
			int64	D=CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,InsideArea)
					 -CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,OutsideArea);
			Dim[i].D=D;
		}
	}

	for(int i=0;i<DimCount;i++){
		if(Dim[i].D>BrightSum){
			BrightSum=Dim[i].D;
			wx=mx+Dim[i].Dx;
			wy=my+Dim[i].Dy;
		}
	}

	BrightSum=0;
	struct SearchParam	HDim[49];
	int	N=49;
	int	n=0;
	for(int dy=-3;dy<=3;dy++){
		for(int dx=-3;dx<=3;dx++){
			HDim[n].Dx=dx;
			HDim[n].Dy=dy;
			n++;
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for	
		for(int i=0;i<N;i++){
			int64	D=CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,InsideArea)
					 -CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,OutsideArea);
			HDim[i].D=D;
		}
	}

	for(int i=0;i<N;i++){
		if(HDim[i].D>BrightSum){
			BrightSum=HDim[i].D;
			Dx=wx+HDim[i].Dx;
			Dy=wy+HDim[i].Dy;
		}
	}
}

int64	FlatInspectionItem::CalcSum(ImageBuffer *Image,int dx,int dy,FlexArea &tArea)
{
	int	N=tArea.GetFLineLen();
	int	SumD[100000];
	int	SumN[100000];
	int	H=Image->GetHeight();
	int	W=Image->GetWidth();

	for(int i=0;i<N;i++){
		int	Y	=tArea.GetFLineAbsY(i)+dy;
		int	X1	=tArea.GetFLineLeftX(i)+dx;
		int	Numb=tArea.GetFLineNumb(i);
		if(X1<0){
			Numb+=X1;
			X1=0;
		}
		if(X1+Numb>W){
			Numb=W-X1;
		}

		if(0<=Y && Y<H){
			BYTE	*s=Image->GetY(Y);
			int	D=0;
			for(int n=0;n<Numb;n++){
				D+=*(s+X1+n);
			}
			SumD[i]=D;
			SumN[i]=Numb;
		}
		else{
			SumD[i]=0;
			SumN[i]=0;
		}
	}

	int64	Ret=0;
	int64	tNumb=0;
	for(int i=0;i<N;i++){
		Ret+=SumD[i];
		tNumb+=SumN[i];
	}
	return Ret/tNumb;
}
void	FlatInspectionItem::MakeWindow(int mx ,int my)
{
	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	int	Layer;
	int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	ImageBuffer		*Image=TargetImageList[Layer];


	struct SearchParam	HDim[49];
	int	HN=49;
	int	n=0;
	for(int dy=-3;dy<=3;dy++){
		for(int dx=-3;dx<=3;dx++){
			HDim[n].Dx=dx;
			HDim[n].Dy=dy;
			n++;
		}
	}
	{
		int		wx=0;
		int		wy=0;
		int64	BrightSum=0;

		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<DimCount;i++){
				int64	D=CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,OutsideAreaLeftTop)
						 -CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,InsideAreaLeftTop);
				Dim[i].D=D;
			}
		}

		for(int i=0;i<DimCount;i++){
			if(Dim[i].D>BrightSum){
				BrightSum=Dim[i].D;
				wx=mx+Dim[i].Dx;
				wy=my+Dim[i].Dy;
			}
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<HN;i++){
				int64	D=CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,OutsideAreaLeftTop)
						 -CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,InsideAreaLeftTop);
				HDim[i].D=D;
			}
		}
		BrightSum=0;
		for(int i=0;i<HN;i++){
			if(HDim[i].D>BrightSum){
				BrightSum=HDim[i].D;
				ResultDxLeftTop=wx+HDim[i].Dx;
				ResultDyLeftTop=wy+HDim[i].Dy;
			}
		}
	}
	{
		int		wx=0;
		int		wy=0;
		int64	BrightSum=0;
		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<DimCount;i++){
				int64	D=CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,OutsideAreaLeftBottom)
						 -CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,InsideAreaLeftBottom);
				Dim[i].D=D;
			}
		}

		for(int i=0;i<DimCount;i++){
			if(Dim[i].D>BrightSum){
				BrightSum=Dim[i].D;
				wx=mx+Dim[i].Dx;
				wy=my+Dim[i].Dy;
			}
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<HN;i++){
				int64	D=CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,OutsideAreaLeftBottom)
						 -CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,InsideAreaLeftBottom);
				HDim[i].D=D;
			}
		}
		BrightSum=0;
		for(int i=0;i<HN;i++){
			if(HDim[i].D>BrightSum){
				BrightSum=HDim[i].D;
				ResultDxLeftBottom=wx+HDim[i].Dx;
				ResultDyLeftBottom=wy+HDim[i].Dy;
			}
		}
	}
	{
		int		wx=0;
		int		wy=0;
		int64	BrightSum=0;
		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<DimCount;i++){
				int64	D=CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,OutsideAreaRightTop)
						 -CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,InsideAreaRightTop);
				Dim[i].D=D;
			}
		}

		for(int i=0;i<DimCount;i++){
			if(Dim[i].D>BrightSum){
				BrightSum=Dim[i].D;
				wx=mx+Dim[i].Dx;
				wy=my+Dim[i].Dy;
			}
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<HN;i++){
				int64	D=CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,OutsideAreaRightTop)
						 -CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,InsideAreaRightTop);
				HDim[i].D=D;
			}
		}
		BrightSum=0;
		for(int i=0;i<HN;i++){
			if(HDim[i].D>BrightSum){
				BrightSum=HDim[i].D;
				ResultDxRightTop=wx+HDim[i].Dx;
				ResultDyRightTop=wy+HDim[i].Dy;
			}
		}
	}
	{
		int		wx=0;
		int		wy=0;
		int64	BrightSum=0;
		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<DimCount;i++){
				int64	D=CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,OutsideAreaRightBottom)
						 -CalcSum(Image,mx+Dim[i].Dx,my+Dim[i].Dy,InsideAreaRightBottom);
				Dim[i].D=D;
			}
		}

		for(int i=0;i<DimCount;i++){
			if(Dim[i].D>BrightSum){
				BrightSum=Dim[i].D;
				wx=mx+Dim[i].Dx;
				wy=my+Dim[i].Dy;
			}
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for	
			for(int i=0;i<HN;i++){
				int64	D=CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,OutsideAreaRightBottom)
						 -CalcSum(Image,wx+HDim[i].Dx,wy+HDim[i].Dy,InsideAreaRightBottom);
				HDim[i].D=D;
			}
		}
		BrightSum=0;
		for(int i=0;i<HN;i++){
			if(HDim[i].D>BrightSum){
				BrightSum=HDim[i].D;
				ResultDxRightBottom=wx+HDim[i].Dx;
				ResultDyRightBottom=wy+HDim[i].Dy;
			}
		}
	}
}
	
void	FlatInspectionItem::AddDarkLightDot(FlexArea &ZoneArea)
{
	int	Layer;
	int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
	ImageBuffer		*MasterImageList[100];
	int	LayerNumb=GetMasterBuffList(MasterImageList);
	ImageBuffer		*Image=MasterImageList[Layer];

	int	BTable[256];
	memset(BTable,0,sizeof(BTable));
	ZoneArea.MakeBrightList(BTable ,GetDotPerLine(), GetMaxLines() ,*Image);

	int	MaxN=0;
	int	Peak=0;
	for(int i=2;i<255-2;i++){
		int	c=BTable[i-2]+BTable[i-1]+BTable[i]+BTable[i+1]+BTable[i+2];
		if(MaxN<c){
			MaxN=c;
			Peak=i;
		}
	}
	int	LevelH=Peak;
	int	LDown=8;
	double Avr ,Var;
	if(GetArea().CalcAvrVar(0,0,*Image,Avr ,Var
						,0.95,0.95)==true){
		double	s=sqrt(Var);
		LDown=s*tGetParentBase()->DeviationParam1;
	}

	int	LevelL=0;
	for(int L=8;L<LevelH-LDown;L++){
		int	Lt=BTable[L+2]+BTable[L+1]+BTable[L  ]+BTable[L-1]+BTable[L-2];
		int	L1=BTable[L+3]+BTable[L+4]+BTable[L+5]+BTable[L+6]+BTable[L+7];
		int	L2=BTable[L-4]+BTable[L-4]+BTable[L-5]+BTable[L-6]+BTable[L-7];
		if(L1<Lt && Lt>L2){
			LevelL=L;
			break;
		}
	}
	if(LevelL==0){
		LevelL=LevelH-LDown*tGetParentBase()->DeviationParam2;
	}
	int	CCol=(LevelH+LevelL)/2;

	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();

	int	N=ZoneArea.GetFLineLen();
	XYClassContainer	tDarkerDots;
	for(int i=0;i<N;i++){
		int	Y	=ZoneArea.GetFLineAbsY(i);
		int	X1	=ZoneArea.GetFLineLeftX(i);
		int	Numb=ZoneArea.GetFLineNumb(i);

		int	Counter=0;
		BYTE	*s=Image->GetY(Y);
		for(int n=0;n<Numb;n++){
			int	c=*(s+X1+n);
			if(c<CCol){
				int	kx=X1+n;
				int	CMin=c;
				int	MinKx=kx;
				for(int wx=-4;wx<=4;wx++){
					if(CMin>s[kx+wx]){
						CMin=s[kx+wx];
						MinKx=kx+wx;
					}
				}

				int	tx=MinKx	-OffsetX;
				int	ty=Y	-OffsetY;
				if(tDarkerDots.GetDistance(tx,ty)>=5){
					tDarkerDots.Add(tx,ty);
				}
			}
		}
	}
	XYClassContainer	tLighterDots;
	for(int Sep=5;Sep<20;Sep++){
		tLighterDots.RemoveAll();
		for(int i=0;i<N;i++){
			int	Y	=ZoneArea.GetFLineAbsY(i);
			int	X1	=ZoneArea.GetFLineLeftX(i);
			int	Numb=ZoneArea.GetFLineNumb(i);

			int	Counter=0;
			BYTE	*s=Image->GetY(Y);
			for(int n=0;n<Numb;n++){
				if(*(s+X1+n)>CCol){
					int	tx=X1+n	-OffsetX;
					int	ty=Y	-OffsetY;
					if(tDarkerDots.GetDistance(tx,ty)>=6
					&& tLighterDots.GetDistance(tx,ty)>=Sep){
						tLighterDots.Add(tx,ty);
					}
				}
			}
		}
		if(tLighterDots.GetCount()<tDarkerDots.GetCount()){
			break;
		}
	}
	DarkerDots.AddMove(tDarkerDots);
	LighterDots.AddMove(tLighterDots);
}

static	int	FuncDim(const void *ai, const void *bi)
{
	struct SearchParam	*a=(struct SearchParam *)ai;
	struct SearchParam	*b=(struct SearchParam *)bi;

	if(a->Coef<b->Coef)
		return 1;
	if(a->Coef>b->Coef)
		return -1;
	return 0;
}

void	FlatInspectionItem::SearchByDot(int mx ,int my ,int LimitUpperY ,int &Dx ,int &Dy,double &Expansion)
{
	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	int	Layer;
	int	Mid=BinarizedThresholdList.GetMaxValue(&Layer);
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	ImageBuffer		*Image=TargetImageList[Layer];
	FlatInspectionInPage	*Ap=tGetParentInPage();
	FlatInspectionBase		*ABase=tGetParentBase();

	int	tx1,ty1,tx2,ty2;
	GetXY(tx1,ty1,tx2,ty2);
	int	x1=max(tx1+mx-RThr->AreaSearchX,0);
	int	y1=max(ty1+my-RThr->AreaSearchY,0);
	int	x2=min(tx2+mx+RThr->AreaSearchX,GetDotPerLine());
	int	y2=min(ty2+my+RThr->AreaSearchY,GetMaxLines());
	x1=max(x1,tx1);
	y1=max(y1,ty1);
	x2=max(x2,tx2);
	y2=max(y2,ty2);

	y1=max(y1,LimitUpperY+1);

	int	BrTable[256];
	memset(BrTable,0,sizeof(BrTable));
	for(int y=y1;y<y2;y++){
		BYTE	*s=Image->GetY(y);
		BYTE	*m=Ap->MaskMap[y];
		for(int x=x1;x<x2;x++){
			if(GetBmpBitOnY(m,x)!=0){
				BrTable[s[x]]++;
			}
		}
	}

	int	D=0;
	int	CL=0;
	for(int i=0;i<256;i++){
		if(D+BrTable[i]>=ABase->SpecialMinDotL){
			CL=i;
			break;
		}
	}
	int	PeakH=255;
	int	Peak=0;
	for(int i=0;i<256;i++){
		if(Peak<BrTable[i]){
			Peak=BrTable[i];
			PeakH=i;
		}
	}
	int	LevelC=(PeakH+CL)/2;

//
//
//	int	N=0;
//	double	Avr=0;
//	double	AA=0;
//	for(int i=0;i<256;i++){
//		int	C=BrTable[i];
//		Avr+=C*i;
//		N+=C;
//		AA+=C*i*i;
//	}
//
//	Avr/=N;
//	double	Q=(AA-N*Avr*Avr)/((double)N);
//	double	sQ=sqrt(Q);
//
//	int	LevelL=Avr-sQ*ABase->LowSpecialDeviation ;
//	int	LevelH=Avr+sQ*ABase->HighSpecialDeviation;
//
//	int	Y1=0;
//	for(int y=y1;y<y2;y++){
//		BYTE	*s=Image->GetY(y);
//		BYTE	*m=Ap->MaskMap[y];
//		for(int x=x1;x<x2;x++){
//			if(GetBmpBitOnY(m,x)!=0){
//				int	C=s[x];
//				if(C<LevelL || LevelH<C){
//					Y1=y;
//					goto	FoundY1;
//				}
//			}
//		}
//	}
//FoundY1:;
//	int	Y2=0;
//	for(int y=y2;y>y1;y--){
//		BYTE	*s=Image->GetY(y);
//		BYTE	*m=Ap->MaskMap[y];
//		for(int x=x1;x<x2;x++){
//			if(GetBmpBitOnY(m,x)!=0){
//				int	C=s[x];
//				if(C<LevelL || LevelH<C){
//					Y2=y;
//					goto	FoundY2;
//				}
//			}
//		}
//	}
//FoundY2:;



	int	Y1=0;
	for(int y=y1;y<y2;y++){
		BYTE	*s=Image->GetY(y);
		BYTE	*m=Ap->MaskMap[y];
		for(int x=x1;x<x2;x++){
			if(GetBmpBitOnY(m,x)!=0){
				int	C=s[x];
				if(C<LevelC){
					Y1=y;
					goto	FoundY1;
				}
			}
		}
	}
FoundY1:;
	int	Y2=0;
	for(int y=y2;y>y1;y--){
		BYTE	*s=Image->GetY(y);
		BYTE	*m=Ap->MaskMap[y];
		for(int x=x1;x<x2;x++){
			if(GetBmpBitOnY(m,x)!=0){
				int	C=s[x];
				if(C<LevelC){
					Y2=y;
					goto	FoundY2;
				}
			}
		}
	}
FoundY2:;

	if(Y1!=0 && Y2!=0){
		my=(Y1+Y2)/2-(ty1+ty2)/2;
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<DimCount;i++){
			Dim[i].Coef=CalcCoefRough(Image,RThr->SelfSearch,mx+Dim[i].Dx,my+Dim[i].Dy,Dim[i].E,LimitUpperY);
		}
	}
	QSort(Dim,DimCount,sizeof(struct SearchParam),FuncDim);

	int		Kn=DimCount/1000;
	if(Kn<100){
		Kn=DimCount;
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<Kn;i++){
			Dim[i].Coef=CalcCoef(Image,RThr->SelfSearch,mx+Dim[i].Dx,my+Dim[i].Dy,Dim[i].E,LimitUpperY);
		}
	}
	double	MaxCoef=0.0;
	for(int i=0;i<Kn;i++){
		if(Dim[i].Coef>MaxCoef){
			MaxCoef=Dim[i].Coef;
			Dx			=mx+Dim[i].Dx;
			Dy			=my+Dim[i].Dy;
			Expansion	=Dim[i].E;
		}
	}

	AverageTarget.RemoveAll();
	for(int L=0;L<LayerNumb;L++){
		double	a=CalcAverage(TargetImageList[L] ,Dx ,Dy ,Expansion);
		AverageTarget.Add((int)a);
	}
}

double	FlatInspectionItem::CalcCoef(ImageBuffer *Image ,int SelfSearch,int mx ,int my ,double E ,int LimitUpperY)
{
	double	A=-((int)DarkerDots.GetCount())
			  +((int)LighterDots.GetCount());
	double	AA=DarkerDots.GetCount()+LighterDots.GetCount();
	int		N=DarkerDots.GetCount()+LighterDots.GetCount();
	//int		B=0;
	//int		BB=0;
	//int		AB=0;
	int		DarkB =0;
	int		LightB =0;
	int		DarkBB=0;

	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();
	for(XYClass *c=LighterDots.GetFirst();c!=NULL;c=c->GetNext()){
		int	x=c->x	+mx+OffsetX;
		int	y=c->y*E+my+OffsetY;
		if(y<LimitUpperY){
			return 0;
		}
		//BYTE	C=0;
		//for(int i=-SelfSearch;i<=SelfSearch;i++){
		//	BYTE	*s=Image->GetY(y+i);
		//	C=max(C,s[x]);
		//}
		//BYTE	*s=Image->GetY(y);
		//for(int i=-SelfSearch;i<=SelfSearch;i++){
		//	C=max(C,s[x+i]);
		//}
		BYTE	*s=Image->GetY(y);
		BYTE	C=s[x];

		//B+=C;
		LightB+=C;
		//BB+=C*C;
		//AB+=C;
	}
	int		Ln	=LighterDots.GetCount();
	double	Avr	=((double)LightB)/Ln;

	for(XYClass *c=DarkerDots.GetFirst();c!=NULL;c=c->GetNext()){
		int	x=c->x	+mx+OffsetX;
		int	y=c->y*E+my+OffsetY;
		BYTE	C=255;
		for(int i=-SelfSearch;i<=SelfSearch;i++){
			if((y+i)<LimitUpperY){
				return 0;
			}
			BYTE	*s=Image->GetY(y+i);
			for(int j=-SelfSearch;j<=SelfSearch;j++){
				BYTE	CC=s[x+j];
				if(CC<C){
					C=CC;
				}
			}
		}

		//B+=C;
		double	v=Avr-C;
		if(v>0){
			DarkB+=sqrt(v);
		}
		//int	C2=C*C;
		//DarkBB+=C2;
		//BB+=C2;
		//AB+=-C;
	}
	int	Dn	=DarkerDots.GetCount();
	double	DAvr=((double)DarkB)/Dn;

	return DAvr;


	//double	AAvr=A/N;
	//double	BAvr=B/N;
	//
	//double	PA=AA-N*AAvr*AAvr;
	//double	PB=BB-N*BAvr*BAvr;
	//double	M=sqrt(PA*PB);
	//if(M==0)
	//	return 0;
	//double	s=(AB-N*AAvr*BAvr)/M;
	//double	DL=(((double)DarkBB)-2*Avr*DarkB+Avr*Avr*Dn)/Dn;
	//return DL;
	//return s;
}

double	FlatInspectionItem::CalcCoefRough(ImageBuffer *Image ,int SelfSearch ,int mx ,int my ,double E ,int LimitUpperY)
{
	double	A=-((int)RoughDarkerDots.GetCount())
			  +((int)RoughLighterDots.GetCount());
	double	AA	=RoughDarkerDots.GetCount()+RoughLighterDots.GetCount();
	int		N	=RoughDarkerDots.GetCount()+RoughLighterDots.GetCount();
	//int		B	=0;
	//int		BB	=0;
	//int		AB	=0;
	int		DarkB =0;
	int		LightB =0;
	int		DarkBB=0;

	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();
	FlatInspectionInPage	*Ap=tGetParentInPage();
	if(SelfSearch<=0){
		SelfSearch=1;
	}

	for(XYClass *c=RoughLighterDots.GetFirst();c!=NULL;c=c->GetNext()){
		int	x=c->x	+mx+OffsetX;
		int	y=c->y*E+my+OffsetY;
		if(y<LimitUpperY){
			return 0;
		}
		//BYTE	C=0;
		//for(int i=-SelfSearch;i<=SelfSearch;i++){
		//	BYTE	*s=Image->GetY(y+i);
		//	C=max(C,s[x]);
		//}
		//BYTE	*s=Image->GetY(y);
		//for(int i=-SelfSearch;i<=SelfSearch;i++){
		//	C=max(C,s[x+i]);
		//}
		if(GetBmpBitOnY(Ap->MaskMap[y],x)==0){
			return 0;
		}
		BYTE	*s=Image->GetY(y);
		BYTE	C=s[x];

		//B+=C;
		LightB+=C;
		//BB+=C*C;
		//AB+=C;
	}
	int		Ln	=RoughLighterDots.GetCount();
	double	Avr	=((double)LightB)/Ln;
	for(XYClass *c=RoughDarkerDots.GetFirst();c!=NULL;c=c->GetNext()){
		int	x=c->x	+mx+OffsetX;
		int	y=c->y*E+my+OffsetY;

		BYTE	C=255;
		for(int i=-SelfSearch;i<=SelfSearch;i+=SelfSearch){
			if((y+i)<LimitUpperY){
				return 0;
			}
			BYTE	*s=Image->GetY(y+i);
			BYTE	*m=Ap->MaskMap[y+i];
			if(GetBmpBitOnY(m,x)!=0){
				for(int j=-SelfSearch;j<=SelfSearch;j++){
					//if(GetBmpBitOnY(m,x+j)==0){
					//	return 0;
					//}
					BYTE	CC=s[x+j];
					if(CC<C){
						C=CC;
					}
				}
			}
		}

		//B+=C;
		double	v=Avr-C;
		if(v>0){
			DarkB+=sqrt(v);
		}
		//int	C2=C*C;
		//DarkBB+=C2;
		//BB+=C2;
		//AB+=-C;
	}
	int	Dn	=RoughDarkerDots.GetCount();
	double	DAvr=((double)DarkB)/Dn;

	return DAvr;

	//double	AAvr=((double)A)/N;
	//double	BAvr=((double)B)/N;
	//
	//
	//double	PA=AA-N*AAvr*AAvr;
	//double	PB=BB-N*BAvr*BAvr;
	//double	M=sqrt(PA*PB);
	//if(M==0)
	//	return 0;
	//double	s=(AB-N*AAvr*BAvr)/M;
	//
	//double	DL=(((double)DarkBB)-2*Avr*DarkB+Avr*Avr*Dn)/Dn;
	///*
	//S(Di-AvrB)^2=S(Di^2-2AvrB*Di+AvrB^2)
	//			=S(Di^2)-2AvrB*S(Di)+AvrB^2*N
	//*/
	//return DL;
	//return s;
}

double	FlatInspectionItem::CalcAverage(ImageBuffer *Image ,int mx ,int my ,double E)
{
	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();

	qint64	LAddedA=0;
	int	LNumb=0;
	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	y	=GetArea().GetFLineAbsY(i);
		int	Y	=(y-OffsetY)*E+my+OffsetY;
		int	x1	=GetArea().GetFLineLeftX(i);
		int	X1	=x1+mx;
		int	Numb=GetArea().GetFLineNumb(i);

		int	AddedA=0;
		if(0<=Y && Y<Image->GetHeight()){
			BYTE	*s=Image->GetY(Y);
			for(int n=0;n<Numb;n++){
				AddedA+=*(s+X1+n);
			}
			LNumb+=Numb;
			LAddedA+=AddedA;
		}
	}
	double	b=((double)LAddedA)/((double)LNumb);
	return b;
}

void	FlatInspectionItem::MakeRoughDots(void)
{
	FlatInspectionBase	*ABase=tGetParentBase();
	int	Nd=DarkerDots.GetCount();
	int	Sep=Nd/ABase->RoughSparse;
	if(Sep>=2){
		RoughDarkerDots.RemoveAll();
		int	k=0;
		for(XYClass *a=DarkerDots.GetFirst();a!=NULL;a=a->GetNext(),k++){
			if((k%Sep)==0){
				XYClass	*d=new XYClass(*a);
				RoughDarkerDots.AppendList(d);
			}
		}
	}
	int	Nl=LighterDots.GetCount();
	Sep=Nl/ABase->RoughSparse;
	if(Sep>=2){
		RoughLighterDots.RemoveAll();
		int	k=0;
		for(XYClass *a=LighterDots.GetFirst();a!=NULL;a=a->GetNext(),k++){
			if((k%Sep)==0){
				XYClass	*d=new XYClass(*a);
				RoughLighterDots.AppendList(d);
			}
		}
	}
}

//=========================================================================================================

ExeResult	FlatInspectionItem::ExecuteProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear	(NGMapB ,0 ,NGMapXByte ,NGMapYLen);
	MatrixBuffClear	(NGMapN ,0 ,NGMapXByte ,NGMapYLen);
	ExeResult	Ret;
	if(FIT_Type==_FIType_MasterArea){
		Ret=ExecuteProcessingMasterArea(ExeID ,ThreadNo,Res);
	}
	else
	if(FIT_Type==_FIType_SpecialShape){
		Ret=ExecuteProcessingSpecialShape(ExeID ,ThreadNo,Res);
	}
	else
	if(FIT_Type==_FIType_InspectionArea){
		Ret=ExecuteProcessingInspectionArea(ExeID ,ThreadNo,Res);
	}
	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	if(RThr->LineMode==true){
		ExecuteProcessingPickLine(Res
								,NGMapB
								,ResultDx,ResultDy);
	}
	return Ret;
}

ExeResult	FlatInspectionItem::ExecuteProcessingMasterArea(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();

	const	FlatInspectionThreshold	*RThr=GetThresholdR();

	ImageBuffer		*MasterImageList[100];
	GetMasterBuffList(MasterImageList);
	
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	
	int	DiffB[3];
	for(int L=0;L<LayerNumb;L++){
		int	a=MasterArea.GetAverage(ResultDx,ResultDy,*TargetImageList[L],1.0,1.0);
		DiffB[L]=a-AverageMaster[L];
	}
	int	N=MasterArea.GetFLineLen();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++){
			int	y	=MasterArea.GetFLineAbsY(i);
			int	x1	=MasterArea.GetFLineLeftX(i);
			int	numb=MasterArea.GetFLineNumb(i);
			int	Y	=y +ResultDy;
			int	X1	=x1+ResultDx;
			if(y-NGMapOffsetY<0 || NGMapYLen<=y-NGMapOffsetY){
				continue;
			}
			BYTE	*mb=NGMapB[y-NGMapOffsetY];
			BYTE	*mn=NGMapN[y-NGMapOffsetY];

			if(LayerNumb>=3 && mb!=NULL && mn!=NULL){
				BYTE	*sr=MasterImageList[0]->GetY(y);
				BYTE	*sg=MasterImageList[1]->GetY(y);
				BYTE	*sb=MasterImageList[2]->GetY(y);
				BYTE	*dr=TargetImageList[0]->GetY(Y);
				BYTE	*dg=TargetImageList[1]->GetY(Y);
				BYTE	*db=TargetImageList[2]->GetY(Y);
				for(int n=0;n<numb;n++){
					int	x=x1+n;
					int	DifR=dr[X1+n]-(sr[x1+n]+DiffB[0]);
					if(DifR>=0){
						if(DifR>RThr->Broad.RThrOffsetH){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(DifR>RThr->Narrow.RThrOffsetH){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					else{
						if(-DifR>RThr->Broad.RThrOffsetL){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(-DifR>RThr->Narrow.RThrOffsetL){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					int	DifG=dg[X1+n]-(sg[x1+n]+DiffB[1]);
					if(DifG>=0){
						if(DifG>RThr->Broad.GThrOffsetH){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(DifG>RThr->Narrow.GThrOffsetH){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					else{
						if(-DifG>RThr->Broad.GThrOffsetL){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(-DifG>RThr->Narrow.GThrOffsetL){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					int	DifB=db[X1+n]-(sb[x1+n]+DiffB[2]);
					if(DifB>=0){
						if(DifB>RThr->Broad.BThrOffsetH){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(DifB>RThr->Narrow.BThrOffsetH){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					else{
						if(-DifB>RThr->Broad.BThrOffsetL){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(-DifB>RThr->Narrow.BThrOffsetL){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
				}
			}
			else
			if(LayerNumb==1 && mb!=NULL && mn!=NULL){
				BYTE	*sr=MasterImageList[0]->GetY(y);
				BYTE	*dr=TargetImageList[0]->GetY(Y);
				for(int n=0;n<numb;n++){
					int	x=x1+n;
					int	DifR=dr[X1+n]-(sr[x1+n]+DiffB[0]);
					if(DifR>=0){
						if(DifR>RThr->Broad.RThrOffsetH){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(DifR>RThr->Narrow.RThrOffsetH){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
					else{
						if(-DifR>RThr->Broad.RThrOffsetL){
							SetBmpBitOnY1(mb,x-NGMapOffsetX);
						}
						if(-DifR>RThr->Narrow.RThrOffsetL){
							SetBmpBitOnY1(mn,x-NGMapOffsetX);
						}
					}
				}
			}
		}
	}
	HandleNGMapToResult(Res ,OffsetX,OffsetY);
	if(Res->GetError()==1 && RThr->RedCheckMode==true){
		ExecuteProcessingRed(Res
							,TargetImageList
							,MasterArea
							,ResultDx,ResultDy);
	}

	FlatInspectionInPage	*Ap=tGetParentInPage();
	GetArea().MakeNotBitData(Ap->MaskMap ,Ap->MaskMapXByte*8 ,Ap->MaskMapYLen ,ResultDx,ResultDy);
	return _ER_true;
}

ExeResult	FlatInspectionItem::ExecuteProcessingSpecialShape(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	OffsetX=SpecialArea.GetMinX();
	int	OffsetY=SpecialArea.GetMinY();
	int	MaxLines=GetMaxLines();

	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	FlatInspectionInPage	*Ap=tGetParentInPage();
	int	N=SpecialArea.GetFLineLen();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++){
			int	y	=SpecialArea.GetFLineAbsY(i);
			int	x1	=SpecialArea.GetFLineLeftX(i);
			int	numb=SpecialArea.GetFLineNumb(i);
			int	Y	=(y-OffsetY)*ResultExpansion+OffsetY +ResultDy;
			int	X1	=x1+ResultDx;
			if(y-NGMapOffsetY<0 || NGMapYLen<=y-NGMapOffsetY || Y<0 || MaxLines<=Y){
				continue;
			}
			BYTE	*mb=NGMapB[y-NGMapOffsetY];
			BYTE	*mn=NGMapN[y-NGMapOffsetY];
			BYTE	*Mp=Ap->MaskMap[Y];

			if(LayerNumb>=3 && mb!=NULL && mn!=NULL){
				int	Ar=AverageTarget[0];
				int	Ag=AverageTarget[1];
				int	Ab=AverageTarget[2];
				BYTE	*dr=TargetImageList[0]->GetY(Y);
				BYTE	*dg=TargetImageList[1]->GetY(Y);
				BYTE	*db=TargetImageList[2]->GetY(Y);
				for(int n=0;n<numb;n++){
					int	x=x1+n;
					if(GetBmpBitOnY(Mp,x)!=0){
						int	DifR=dr[X1+n]-Ar;
						if(DifR>=0){
							if(DifR>RThr->Broad.RThrOffsetH){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(DifR>RThr->Narrow.RThrOffsetH){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						else{
							if(-DifR>RThr->Broad.RThrOffsetL){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(-DifR>RThr->Narrow.RThrOffsetL){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						int	DifG=dg[X1+n]-Ag;
						if(DifG>=0){
							if(DifG>RThr->Broad.GThrOffsetH){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(DifG>RThr->Narrow.GThrOffsetH){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						else{
							if(-DifG>RThr->Broad.GThrOffsetL){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(-DifG>RThr->Narrow.GThrOffsetL){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						int	DifB=db[X1+n]-Ab;
						if(DifB>=0){
							if(DifB>RThr->Broad.BThrOffsetH){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(DifB>RThr->Narrow.BThrOffsetH){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						else{
							if(-DifB>RThr->Broad.BThrOffsetL){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(-DifB>RThr->Narrow.BThrOffsetL){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
					}
					SetBmpBitOnY0(Mp,X1+n);
				}
			}
			else
			if(LayerNumb==1 && mb!=NULL && mn!=NULL){
				int	Ar=AverageTarget[0];
				BYTE	*dr=TargetImageList[0]->GetY(Y);
				for(int n=0;n<numb;n++){
					int	x=x1+n;
					if(GetBmpBitOnY(Mp,x)!=0){
						int	DifR=dr[X1+n]-Ar;
						if(DifR>=0){
							if(DifR>RThr->Broad.RThrOffsetH){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(DifR>RThr->Narrow.RThrOffsetH){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
						else{
							if(-DifR>RThr->Broad.RThrOffsetL){
								SetBmpBitOnY1(mb,x-NGMapOffsetX);
							}
							if(-DifR>RThr->Narrow.RThrOffsetL){
								SetBmpBitOnY1(mn,x-NGMapOffsetX);
							}
						}
					}
					SetBmpBitOnY0(Mp,X1+n);
				}
			}
		}
	}
	HandleNGMapToResult(Res ,OffsetX,OffsetY);
	if(Res->GetError()==1 && RThr->RedCheckMode==true){
		ExecuteProcessingRed(Res
							,TargetImageList
							,SpecialArea
							,ResultDx,ResultDy);
	}	
	return _ER_true;
}

ExeResult	FlatInspectionItem::ExecuteProcessingInspectionArea(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	NGMapOffsetX	=ResultMinX;
	NGMapOffsetY	=ResultY1;

	const	FlatInspectionThreshold	*RThr=GetThresholdR();
	int	OffsetX=GetArea().GetMinX();
	int	OffsetY=GetArea().GetMinY();
	int	W=GetArea().GetWidth();
	
	ImageBuffer		*TargetImageList[100];
	int	LayerNumb=GetTargetBuffList(TargetImageList);
	FlatInspectionInPage	*Ap=tGetParentInPage();

	int	XLen=ResultMaxX-ResultMinX;
	int	YLen=ResultY2-ResultY1;
	int	XDivCount=XLen/RThr->DivLenX;
	int	YDivCount=YLen/RThr->DivLenY;
	if(XDivCount==0){
		XDivCount=1;
	}
	if(YDivCount==0){
		YDivCount=1;
	}
	int	DivXLen = (XLen+XDivCount-1)/XDivCount;
	int	DivYLen = (YLen+YDivCount-1)/YDivCount;

	{
		struct XYDivCell
		{
			int	X,Y;
		};
		struct XYDivCell	XYDivCellDim[10000];
		struct XYDivCell	*XYDiv=XYDivCellDim;
		int	XYDivCount=XDivCount*YDivCount;
		if(XYDivCount>10000){
			XYDiv=new struct XYDivCell[XYDivCount];
		}
		int	Nd=0;
		for(int yn=0;yn<YDivCount;yn++){
			for(int xn=0;xn<XDivCount;xn++){
				XYDiv[Nd].X = ResultMinX+xn*DivXLen;
				XYDiv[Nd].Y = ResultY1+yn*DivYLen;
				Nd++;
			}
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<Nd;i++){
				int	X1=XYDiv[i].X;
				int	X2=X1+DivXLen;
				if(X2>ResultMaxX){
					X2=ResultMaxX;
				}
				int	Ar=0;
				int	Ag=0;
				int	Ab=0;
				int	N=0;
				int	LastY=XYDiv[i].Y+DivYLen;
				if(LayerNumb>=3){
					for(int	Y=XYDiv[i].Y;Y<LastY;Y+=20){
						BYTE	*dr=TargetImageList[0]->GetY(Y);
						BYTE	*dg=TargetImageList[1]->GetY(Y);
						BYTE	*db=TargetImageList[2]->GetY(Y);
						BYTE	*mn=Ap->MaskMap[Y];
						for(int X=X1;X<X2;X++){
							if(GetBmpBitOnY(mn,X)!=0){
								Ar+=dr[X];
								Ag+=dg[X];
								Ab+=db[X];
								N++;
							}
						}
					}
					if(N!=0){
						int	AvrR=Ar/N;
						int	AvrG=Ag/N;
						int	AvrB=Ab/N;

						for(int	Y=XYDiv[i].Y;Y<LastY;Y++){
							BYTE	*dr=TargetImageList[0]->GetY(Y);
							BYTE	*dg=TargetImageList[1]->GetY(Y);
							BYTE	*db=TargetImageList[2]->GetY(Y);
							BYTE	*mp=Ap->MaskMap[Y];
							if(Y-NGMapOffsetY<0 || NGMapYLen<=Y-NGMapOffsetY){
								continue;
							}

							BYTE	*mb=NGMapB[Y-NGMapOffsetY];
							BYTE	*mn=NGMapN[Y-NGMapOffsetY];
							if(mb!=NULL && mn!=NULL){
								for(int X=X1;X<X2;X++){
									if(GetBmpBitOnY(mp,X)!=0){

										int	DifR=dr[X]-AvrR;
										if(DifR>=0){
											if(DifR>RThr->Broad.RThrOffsetH){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(DifR>RThr->Narrow.RThrOffsetH){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										else{
											if(-DifR>RThr->Broad.RThrOffsetL){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(-DifR>RThr->Narrow.RThrOffsetL){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										int	DifG=dg[X]-AvrG;
										if(DifG>=0){
											if(DifG>RThr->Broad.GThrOffsetH){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(DifG>RThr->Narrow.GThrOffsetH){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										else{
											if(-DifG>RThr->Broad.GThrOffsetL){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(-DifG>RThr->Narrow.GThrOffsetL){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										int	DifB=db[X]-AvrB;
										if(DifB>=0){
											if(DifB>RThr->Broad.BThrOffsetH){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(DifB>RThr->Narrow.BThrOffsetH){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										else{
											if(-DifB>RThr->Broad.BThrOffsetL){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(-DifB>RThr->Narrow.BThrOffsetL){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
									}
								}
							}
						}
					}
				}
				else
				if(LayerNumb==1){
					for(int	Y=XYDiv[i].Y;Y<LastY;Y+=20){
						BYTE	*dr=TargetImageList[0]->GetY(Y);
						BYTE	*mn=Ap->MaskMap[Y];
						for(int X=X1;X<X2;X++){
							if(GetBmpBitOnY(mn,X)!=0){
								Ar+=dr[X];
								N++;
							}
						}
					}
					if(N!=0){
						int	AvrR=Ar/N;

						for(int	Y=XYDiv[i].Y;Y<LastY;Y++){
							BYTE	*dr=TargetImageList[0]->GetY(Y);
							BYTE	*mp=Ap->MaskMap[Y];
							if(Y-NGMapOffsetY<0 || NGMapYLen<=Y-NGMapOffsetY){
								continue;
							}
							BYTE	*mb=NGMapB[Y-NGMapOffsetY];
							BYTE	*mn=NGMapN[Y-NGMapOffsetY];
							if(mb!=NULL && mn!=NULL){
								for(int X=X1;X<X2;X++){
									if(GetBmpBitOnY(mp,X)!=0){

										int	DifR=dr[X]-AvrR;
										if(DifR>=0){
											if(DifR>RThr->Broad.RThrOffsetH){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(DifR>RThr->Narrow.RThrOffsetH){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
										else{
											if(-DifR>RThr->Broad.RThrOffsetL){
												SetBmpBitOnY1(mb,X-NGMapOffsetX);
											}
											if(-DifR>RThr->Narrow.RThrOffsetL){
												SetBmpBitOnY1(mn,X-NGMapOffsetX);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if(XYDiv!=XYDivCellDim){
			delete[] XYDiv;
			XYDiv=NULL;
		}
	}

	HandleNGMapToResult(Res ,ResultMinX,NGMapOffsetY);
	if(Res->GetError()==1 && RThr->RedCheckMode==true){
		ExecuteProcessingRed(Res
							,TargetImageList
							,ResultDx,ResultDy);
	}		
	return _ER_true;
}

void	FlatInspectionItem::HandleNGMapToResult(ResultInItemRoot *Res
												,int OffsetX ,int OffsetY)
{
	const	FlatInspectionThreshold	*RThr=GetThresholdR();

	bool	NG=false;
	ResultPosListContainer	NowList;
	PureFlexAreaListContainer FPackB;
	PickupFlexArea(NGMapB ,NGMapXByte ,NGMapXLen,NGMapYLen ,FPackB);
	for(PureFlexAreaList *p=FPackB.GetFirst();p!=NULL;p=p->GetNext()){
		int	Dots=p->GetPatternByte();
		int	NGW=p->GetWidth();
		int	NGH=p->GetHeight();
		double	NGLen=hypot(NGW, NGH);
		if(Dots>RThr->Broad.OKDot){
			int	Cx,Cy;
			p->MoveToNoClip(OffsetX ,OffsetY);
			p->GetCenter(Cx,Cy);
			FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
			r->result =0x10000;	//NG

			r->SetResult1(Dots);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			r->NGSize=Dots;
			NowList.AppendList(r);
		}
		else
		if(NGLen>RThr->Broad.OKLength){
			int	Cx,Cy;
			p->MoveToNoClip(OffsetX ,OffsetY);
			p->GetCenter(Cx,Cy);
			FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
			r->result =0x20001;	//NG

			r->SetResult1(Dots);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			r->NGSize=NGLen;
			NowList.AppendList(r);
		}
	}
	HandleMultiSpotNGMapToResult(RThr
								,NowList
								,FPackB
								,OffsetX ,OffsetY);

	if(NowList.GetCount()!=0){
		Res->AddMovePosList(NowList);
		Res->SetError(2);
		Res->SetAlignedXY(ResultDx,ResultDy);
		NG=true;
	}
	else{
		PureFlexAreaListContainer FPackN;
		PickupFlexArea(NGMapN ,NGMapXByte ,NGMapXLen,NGMapYLen ,FPackN);
		for(PureFlexAreaList *p=FPackN.GetFirst();p!=NULL;p=p->GetNext()){
			int	Dots=p->GetPatternByte();
			int	NGW=p->GetWidth();
			int	NGH=p->GetHeight();
			double	NGLen=hypot(NGW, NGH);
			if(Dots>RThr->Narrow.OKDot){
				int	Cx,Cy;
				p->MoveToNoClip(OffsetX ,OffsetY);
				p->GetCenter(Cx,Cy);
				FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
				r->result =0x30000;	//NG

				r->SetResult1(Dots);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				r->NGSize=Dots;
				NowList.AppendList(r);
			}
			else
			if(NGLen>RThr->Narrow.OKLength){
				int	Cx,Cy;
				p->MoveToNoClip(OffsetX ,OffsetY);
				p->GetCenter(Cx,Cy);
				FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
				r->result =0x40001;	//NG

				r->SetResult1(Dots);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				r->NGSize=NGLen;
				NowList.AppendList(r);
			}
		}
		HandleMultiSpotNGMapToResult(RThr
									,NowList
									,FPackN
									,OffsetX ,OffsetY);
		if(NowList.GetCount()!=0){
			Res->AddMovePosList(NowList);
			Res->SetError(2);
			Res->SetAlignedXY(ResultDx,ResultDy);
			NG=true;
		}
	}
	if(NG==false){
		Res->SetAlignedXY(ResultDx,ResultDy);
		Res->SetError(1);
	}
}

void	FlatInspectionItem::HandleMultiSpotNGMapToResult(const	FlatInspectionThreshold	*RThr
								,ResultPosListContainer	&NowList
								,PureFlexAreaListContainer &FPack
								,int OffsetX ,int OffsetY)
{
	int		MaxNGCountForMultiSpot	=tGetParentBase()->MaxNGCountForMultiSpot;

	if(RThr->MultiSpotCountGathered>0 && FPack.GetCount()<MaxNGCountForMultiSpot){
		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
			int	Dots=p->GetPatternByte();
			int	sx1,sy1,sx2,sy2;
			p->GetXY(sx1,sy1,sx2,sy2);
			int	MultiSpotGatheredMinSize=Dots;
			if(Dots>=RThr->MultiSpotDotGathered){
				FlexArea	M=*p;
				int			Count=1;
				NPListPack<NPListPointer<FlexArea> >	TmpContainer;
				TmpContainer.AppendList(new NPListPointer<FlexArea>(p));
				for(PureFlexAreaList *q=p->GetNext();q!=NULL;q=q->GetNext()){
					int	dx1,dy1,dx2,dy2;
					q->GetXY(dx1,dy1,dx2,dy2);
					dx1=min(dx1,sx1);
					dy1=min(dy1,sy1);
					dx2=max(dx2,sx2);
					dy2=max(dy2,sy2);
					double	L=hypot(dx1-dx2,dy1-dy2);
					Dots=q->GetPatternByte();
					if(Dots>=RThr->MultiSpotDotGathered 
					&& L<=RThr->MultiSpotLengthGathered){
						FlexArea	TmpA=M;
						M+=*q;
						if(hypot(M.GetWidth(),M.GetHeight())>=RThr->MultiSpotLengthGathered){
							M=TmpA;
						}
						else{
							TmpContainer.AppendList(new NPListPointer<FlexArea>(q));
							MultiSpotGatheredMinSize=min(MultiSpotGatheredMinSize,Dots);
							Count++;
						}
					}
				}
				if(Count>=RThr->MultiSpotCountGathered){
					int	Cx,Cy;
					M.MoveToNoClip(OffsetX ,OffsetY);
					M.GetCenter(Cx,Cy);
					FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
					r->result =0x50000;	//NG

					r->SetResult1(Count);
					r->SetResult2(MultiSpotGatheredMinSize);
					r->NGShape=M;
					r->NGSize =M.GetPatternByte();
					NowList.AppendList(r);

					for(NPListPointer<FlexArea> *r=TmpContainer.GetFirst();r!=NULL;r=r->GetNext()){
						r->GetPointer()->Clear();
					}
				}
			}
		}
	}
}
