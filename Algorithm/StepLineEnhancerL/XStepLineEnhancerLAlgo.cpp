#include "XStepLineEnhancerL.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>

StepLineEnhancerLItem::AngleDimBase::AngleDimBase(void)
{
	AddedList					=NULL;
	PixelCount					=NULL;
	PixelCountForDynamicMasking	=NULL;
	PixelCDivider				=NULL;
	PointerIndex				=NULL;
	ListNumb					=0;
	AllAvr						=-1;
	PointerIndexCount			=0;
}
StepLineEnhancerLItem::AngleDimBase::~AngleDimBase(void)
{
	if(AddedList!=NULL){
		delete	[]AddedList;
		AddedList=NULL;
	}
	if(PixelCount!=NULL){
		delete	[]PixelCount;
		PixelCount=NULL;
	}
	if(PixelCountForDynamicMasking!=NULL){
		delete	[]PixelCountForDynamicMasking;
		PixelCountForDynamicMasking=NULL;
	}
	if(PixelCDivider!=NULL){
		delete	[]PixelCDivider;
		PixelCDivider=NULL;
	}
	if(PointerIndex!=NULL){
		delete	[]PointerIndex;
		PointerIndex=NULL;
	}
	ListNumb	=0;
}

void	StepLineEnhancerLItem::AngleDimBase::Initial(double Radian, FlexArea &area)
{
	int	W=area.GetWidth();
	int	H=area.GetHeight();

	int	iListNumb=ceil(hypot(W,H))+1;
	if(ListNumb!=iListNumb){
		if(AddedList!=NULL){
			delete	[]AddedList;
		}
		if(PixelCount!=NULL){
			delete	[]PixelCount;
		}
		if(PixelCountForDynamicMasking!=NULL){
			delete	[]PixelCountForDynamicMasking;
		}
		if(PixelCDivider!=NULL){
			delete	[]PixelCDivider;
		}
		ListNumb=iListNumb;
		AddedList=new double[ListNumb];
		PixelCount=new int32[ListNumb];
		PixelCountForDynamicMasking	=new int32[ListNumb];
		PixelCDivider=new double[ListNumb];
	}
	CosS=cos(Radian);
	SinS=sin(Radian);
	area.GetCenter(Cx,Cy);
}


void	StepLineEnhancerLItem::AngleDim::Initial(double Radian, FlexArea &area)
{
	AngleDimBase::Initial(Radian, area);
	int64	N=area.GetPatternByte();
	if(PointerIndexCount!=N){
		PointerIndexCount=N;
		if(PointerIndex!=NULL){
			delete	[]PointerIndex;
		}
		PointerIndex=new WORD[PointerIndexCount];
	}
}
void	StepLineEnhancerLItem::AngleDimDown::Initial(double Radian, FlexArea &area)
{
	AngleDimBase::Initial(Radian, area);
	int	index=0;
	int n=area.GetFLineLen();
	for(int i=0;i<n;i++){
		int x1=area.GetFLineLeftX (i);
		int x2=area.GetFLineRightX(i);
		int y =area.GetFLineAbsY  (i);
		for(int x=((y&1)==0)?((x1+1)&0xFFFFE):(x1|1);x<x2;x+=2){
			index++;
		}
	}
	PointerIndex=new WORD[index];
}
void	StepLineEnhancerLItem::AngleDim::ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int i=0;i<ListNumb;i++){
		PixelCount[i]=0;
	}
	int	index=0;
	int n=area.GetFLineLen();
	for(int i=0;i<n;i++){
		int x1=area.GetFLineLeftX (i);
		int x2=area.GetFLineRightX(i);
		int y =area.GetFLineAbsY  (i);
		for(int x=x1;x<x2;x++){
			int	dx=x-Cx;
			int	dy=y-Cy;
			int	Y=dx*SinS+dy*CosS+(ListNumb/2);
			PointerIndex[index]=Y;
			index++;
			PixelCount[Y]++;
		}
	}
	for(int i=0;i<ListNumb;i++){
		if(PixelCount[i]!=0){
			PixelCDivider[i]=1.0/(double)PixelCount[i];
		}
		else{
			PixelCDivider[i]=0;
		}
	}
}
void	StepLineEnhancerLItem::AngleDimDown::ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int i=0;i<ListNumb;i++){
		PixelCount[i]=0;
	}
	int	index=0;
	int n=area.GetFLineLen();
	for(int i=0;i<n;i++){
		int x1=area.GetFLineLeftX (i);
		int x2=area.GetFLineRightX(i);
		int y =area.GetFLineAbsY  (i);
		for(int x=((y&1)==0)?((x1+1)&0xFFFFE):(x1|1);x<x2;x+=2){
			int	dx=x-Cx;
			int	dy=y-Cy;
			int	Y=dx*SinS+dy*CosS+(ListNumb/2);
			PointerIndex[index]=Y;
			index++;
			PixelCount[Y]++;
		}
	}
	for(int i=0;i<ListNumb;i++){
		if(PixelCount[i]!=0){
			PixelCDivider[i]=1.0/(double)PixelCount[i];
		}
		else{
			PixelCDivider[i]=0;
		}
	}
}

void	StepLineEnhancerLItem::AngleDimBase::ExecuteStartByInspection(void)
{
	for(int i=0;i<ListNumb;i++){
		AddedList[i]=0;
		PixelCountForDynamicMasking[i]=PixelCount[i];
	}
}
void	StepLineEnhancerLItem::AngleDimBase::ExecutePreProcessingReduceDynamicMasking(int index)
{	
	PixelCountForDynamicMasking[PointerIndex[index]]--;
}
double	StepLineEnhancerLItem::AngleDimBase::MakeAverageAndPeaks(int MaxLineWidth ,bool ModeDynamicMask)
{
	AllAvr=0;
	int		AllAvrCount=0;
	if(ModeDynamicMask==true){
		for(int i=0;i<ListNumb;i++){
			if(PixelCountForDynamicMasking[i]>0){
				AddedList[i]=AddedList[i]/PixelCountForDynamicMasking[i];
			}
			if(PixelCountForDynamicMasking[i]>4){
				AllAvr+=AddedList[i];
				AllAvrCount++;
			}
		}
	}
	else{
		for(int i=0;i<ListNumb;i++){
			if(PixelCount[i]>0){
				AddedList[i]=AddedList[i]*PixelCDivider[i];
			}
			if(PixelCount[i]>4){
				AllAvr+=AddedList[i];
				AllAvrCount++;
			}
		}
	}
	if(AllAvrCount==0){
		AllAvr=-1;
	}
	else{
		AllAvr/=AllAvrCount;
	}

	int32	*PCount=(ModeDynamicMask==true)?PixelCountForDynamicMasking:PixelCount;
	double	MaxPeak=0;
	for(int i=MaxLineWidth;i<ListNumb-MaxLineWidth;i++){
		if(PCount[i-MaxLineWidth]>4 && PCount[i]>4 && PCount[i+MaxLineWidth]>4){
			double	d1=AddedList[i-MaxLineWidth]-AllAvr;
			double	d2=AddedList[i             ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PCount[i-MaxLineWidth+1]>4 && PCount[i]>4 && PCount[i+MaxLineWidth]>4){
			double	d1=AddedList[i-MaxLineWidth+1]-AllAvr;
			double	d2=AddedList[i               ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth  ]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PCount[i-MaxLineWidth  ]>4 && PCount[i]>4 && PCount[i+MaxLineWidth-1]>4){
			double	d1=AddedList[i-MaxLineWidth  ]-AllAvr;
			double	d2=AddedList[i               ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth-1]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PCount[i-MaxLineWidth+1]>4 && PCount[i]>4 && PCount[i+MaxLineWidth-1]>4){
			double	d1=AddedList[i-MaxLineWidth+1]-AllAvr;
			double	d2=AddedList[i               ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth-1]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
	}
	return MaxPeak;
}

void	StepLineEnhancerLItem::AngleDim::Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate
											 ,bool ExcludeDynamicMask
											 ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<ListNumb;i++){
		if(PixelCount[i]>0 && PixelCount[i]<=4){
			double	AddedData=0;
			int		AddC=0;
			for(int k=i-2;k<=i+2;k++){
				if(0<=k && k<ListNumb && PixelCount[k]>2){
					AddedData+=AddedList[k];
					AddC++;
				}
			}
			if(AddC>0){
				AddedList[i]=AddedData/AddC;
			}
			else{
				AddedData=0;
				AddC=0;
				for(int k=i-6;k<=i+6;k++){
					if(0<=k && k<ListNumb && PixelCount[k]>2){
						AddedData+=AddedList[k];
						AddC++;
					}
				}
				if(AddC>0){
					AddedList[i]=AddedData/AddC;
				}
			}
		}
	}
	if(AllAvr>=0){
		int	index=0;
		int n=area.GetFLineLen();
		if(ExcludeDynamicMask==true && DynamicMaskMap!=NULL){
			for(int i=0;i<n;i++){
				int x1=area.GetFLineLeftX (i);
				int x2=area.GetFLineRightX(i);
				int y =area.GetFLineAbsY  (i);
				BYTE	*d=IBuff.GetY(y+my);
				BYTE	*m=DynamicMaskMap[y+my];
				for(int x=x1;x<x2;x++){
					if(GetBmpBitOnY(m,x+mx)==0){
						int	c=d[x+mx]+(AddedList[PointerIndex[index]]-AllAvr)*EmphasizeRate;
						if(c<0)
							c=0;
						if(c>255)
							c=255;
						d[x+mx]=c;
					}
					index++;
				}
			}
		}
		else{
			for(int i=0;i<n;i++){
				int x1=area.GetFLineLeftX (i);
				int x2=area.GetFLineRightX(i);
				int y =area.GetFLineAbsY  (i);
				BYTE	*d=IBuff.GetY(y+my);
				for(int x=x1;x<x2;x++){
					int	c=d[x+mx]+(AddedList[PointerIndex[index]]-AllAvr)*EmphasizeRate;
					if(c<0)
						c=0;
					if(c>255)
						c=255;
					d[x+mx]=c;
					index++;
				}
			}
		}
	}

}

double	StepLineEnhancerLItem::CalcV(int mx,int my,ImageBuffer &IBuff
								,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
//	ƒ°(v-a)^2	=ƒ°v^2 - 2*ƒ°v*a + ƒ°a*a
//				=ƒ°v^2 - 2*a*ƒ°v + a*a*N
//			a*N=ƒ°v
{
	int n=MatchingArea.GetFLineLen();
	int	DotC=0;
	double	AddC	=0.0;
	double	AddCC	=0.0;
	const StepLineEnhancerLThreshold	*RThr=GetThresholdR();
	if(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL){
		for(int i=0;i<n;i++){
			int x1=MatchingArea.GetFLineLeftX (i);
			int x2=MatchingArea.GetFLineRightX(i);
			int y =MatchingArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			BYTE	*m=DynamicMaskMap[y+my];
			int	iAddC=0;
			int	iAddCC=0;
			for(int x=x1;x<x2;x++){
				if(GetBmpBitOnY(m,x+mx)==0){
					int	c=s[x+mx];
					iAddC +=c;
					iAddCC+=c*c;
					DotC++;
				}
			}
			AddC+=iAddC;
			AddCC+=iAddCC;
		}
		double	A=AddC/DotC;
		return AddCC - 2*A*AddC + A*A*DotC;
	}
	else{
		for(int i=0;i<n;i++){
			int x1=MatchingArea.GetFLineLeftX (i);
			int x2=MatchingArea.GetFLineRightX(i);
			int y =MatchingArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			int	iAddC=0;
			int	iAddCC=0;
			for(int x=x1;x<x2;x++){
				int	c=s[x+mx];
				iAddC +=c;
				iAddCC+=c*c;
			}
			DotC+=x2-x1;
			AddC+=iAddC;
			AddCC+=iAddCC;
		}
		double	A=AddC/DotC;
		return AddCC - 2*A*AddC + A*A*DotC;
	}
}

double	 StepLineEnhancerLItem::GetAverage(FlexArea &area ,ImageBuffer &Data,int dx ,int dy
										,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int 	N=0;
	double	D=0.0;
	const StepLineEnhancerLThreshold	*RThr=GetThresholdR();
	if(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL){
		for(int i=0;i<area.GetFLineLen();i++){
			int x1=area.GetFLineLeftX (i)+dx;
			int x2=area.GetFLineRightX(i)+dx;
			int y =area.GetFLineAbsY  (i)+dy;

			if(y<0 || y>=Data.GetHeight()){
				continue;
			}

			if(x1<0){
				x1=0;
			}
			if(x1>=Data.GetWidth()){
				x1=Data.GetWidth()-1;
			}
			if(x2<0){
				x2=0;
			}
			if(x2>=Data.GetWidth()){
				x2=Data.GetWidth()-1;
			}

			if(x1>x2){
				continue;
			}
			if(x2<=0 || x1>=(Data.GetWidth()-1)){
				continue;
			}

			int Len=x2-x1;
			if(Len<=0){
				continue;
			}
			register	BYTE	*p=Data.GetY(y);
			BYTE	*m=DynamicMaskMap[y];
			int Di=0;
			for(int x=x1;x<=x2;x++){
				if(GetBmpBitOnY(m,x)==0){
					Di+= *(p+x);
					N++;
				}
			}
			D+=Di;
		}
		if(N==0){
			return(0);
		}
		return(D/N);
	}
	else{
		return area.GetAverage(Data,dx,dy);
	}
}


int	DbgPx=3470;
int	DbgPy=466;
int	DbgPoint;
void	StepLineEnhancerLItem::ExecutePreProcessingByLayer(int mx,int my,ImageBuffer &IBuff
													,int &ResMx ,int &ResMy 
													,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	if(GetArea().IsInclude(DbgPx,DbgPy)==true){
		DbgPoint++;
	}
	const StepLineEnhancerLThreshold	*RThr=GetThresholdR();
	double	MinDiv=65535.0*65535.0*65535.0;
	int	MinDx=0;
	int	MinDy=0;
	int	MasterColor=MasterBrightness;
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	x1+=mx;
	y1+=my;
	x2+=mx;
	y2+=my;
	if(x1<=RThr->SelfSearch+2 || GetDotPerLine()+RThr->SelfSearch+2<=x2
	|| y1<=RThr->SelfSearch+2 || GetMaxLines() + RThr->SelfSearch+2<=y2){
		return;
	}
	for(int dy=-RThr->SelfSearch;dy<=RThr->SelfSearch;dy+=2){
		for(int dx=-RThr->SelfSearch;dx<=RThr->SelfSearch;dx+=2){
			double	TempV=CalcV(mx+dx,my+dy,IBuff
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			double	C=GetAverage(MatchingArea,IBuff,mx+dx,my+dy
											,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			TempV=TempV*(C-MasterColor)*(C-MasterColor);
			if(TempV<MinDiv){
				MinDiv=TempV;
				MinDx=dx;
				MinDy=dy;
			}
		}
	}
	MinDiv=65535.0*65535.0*65535.0;
	mx+=MinDx;
	my+=MinDy;
	for(int dy=-1;dy<=1;dy++){
		for(int dx=-1;dx<=1;dx++){
			double	TempV=CalcV(mx+dx,my+dy,IBuff
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			double	C=GetAverage(MatchingArea,IBuff,mx+dx,my+dy
											,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			TempV=TempV*(C-MasterColor)*(C-MasterColor);
			if(TempV<MinDiv){
				MinDiv=TempV;
				MinDx=dx;
				MinDy=dy;
			}
		}
	}
	mx+=MinDx;
	my+=MinDy;
	ResMx=mx;
	ResMy=my;

	int	IndexStart	=RThr->StartAngle*2*M_PI/360.0 / MinAngle;
	int	IndexEnd	=RThr->EndAngle  *2*M_PI/360.0 / MinAngle;
	if(IndexStart>AngleListCount){
		IndexStart=AngleListCount-1;
	}
	if(IndexEnd>AngleListCount){
		IndexEnd=AngleListCount-1;
	}

	if(IndexStart<=IndexEnd){
		for(int k=IndexStart;k<=IndexEnd;k++){
			AngleList[k].ExecuteStartByInspection();
		}
		for(int k=IndexStart;k<=IndexEnd;k++){
			AngleDownList[k].ExecuteStartByInspection();
		}	
	}
	else{
		for(int k=0;k<=IndexEnd;k++){
			AngleList[k].ExecuteStartByInspection();
		}
		for(int k=IndexStart;k<AngleListCount;k++){
			AngleList[k].ExecuteStartByInspection();
		}
		for(int k=0;k<=IndexEnd;k++){
			AngleDownList[k].ExecuteStartByInspection();
		}	
		for(int k=IndexStart;k<AngleListCount;k++){
			AngleDownList[k].ExecuteStartByInspection();
		}	
	}
	
	int	index=0;
	int n=CalcArea.GetFLineLen();
	if(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL){
		for(int i=0;i<n;i++){
			int x1=CalcArea.GetFLineLeftX (i);
			int x2=CalcArea.GetFLineRightX(i);
			int y =CalcArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			BYTE	*m=DynamicMaskMap[y+my];
			for(int x=((y&1)==0)?((x1+1)&0xFFFFE):(x1|1);x<x2;x+=2){
				if(GetBmpBitOnY(m,x+mx)==0){
					BYTE c=s[x+mx];
					if(IndexStart<=IndexEnd){
						for(int k=IndexStart;k<=IndexEnd;k+=2){
							AngleDownList[k].ExecutePreProcessing(index,c);
						}
						index++;
					}
					else{
						for(int k=0;k<=IndexEnd;k+=2){
							AngleDownList[k].ExecutePreProcessing(index,c);
						}
						for(int k=IndexStart;k<AngleListCount;k+=2){
							AngleDownList[k].ExecutePreProcessing(index,c);
						}
						index++;
					}
				}
				else{
					if(IndexStart<=IndexEnd){
						for(int k=IndexStart;k<=IndexEnd;k+=2){
							AngleDownList[k].ExecutePreProcessingReduceDynamicMasking(index);
						}
						index++;
					}
					else{
						for(int k=0;k<=IndexEnd;k+=2){
							AngleDownList[k].ExecutePreProcessingReduceDynamicMasking(index);
						}
						for(int k=IndexStart;k<AngleListCount;k+=2){
							AngleDownList[k].ExecutePreProcessingReduceDynamicMasking(index);
						}
						index++;
					}
				}
			}
		}
	}
	else{
		for(int i=0;i<n;i++){
			int x1=CalcArea.GetFLineLeftX (i);
			int x2=CalcArea.GetFLineRightX(i);
			int y =CalcArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			for(int x=((y&1)==0)?((x1+1)&0xFFFFE):(x1|1);x<x2;x+=2){
				BYTE	c=s[x+mx];
				if(IndexStart<=IndexEnd){
					for(int k=IndexStart;k<=IndexEnd;k+=2){
						AngleDownList[k].ExecutePreProcessing(index,c);
					}
					index++;
				}
				else{
					for(int k=0;k<=IndexEnd;k+=2){
						AngleDownList[k].ExecutePreProcessing(index,c);
					}
					for(int k=IndexStart;k<AngleListCount;k+=2){
						AngleDownList[k].ExecutePreProcessing(index,c);
					}
					index++;
				}
			}
		}
	}
	double	maxPeak=0;
	int		MaxIndex=IndexStart;
	if(IndexStart!=IndexEnd){
		if(IndexStart<IndexEnd){
			for(int k=IndexStart;k<=IndexEnd;k+=2){
				double	d=AngleDownList[k].MakeAverageAndPeaks(RThr->MaxLineWidth*2 
															   ,(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL)?true:false);
				if(d>maxPeak){
					maxPeak=d;
					MaxIndex=k;
				}
			}
		}
		else{
			for(int k=0;k<=IndexEnd;k+=2){
				double	d=AngleDownList[k].MakeAverageAndPeaks(RThr->MaxLineWidth*2
															   ,(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL)?true:false);
				if(d>maxPeak){
					maxPeak=d;
					MaxIndex=k;
				}
			}
			for(int k=IndexStart;k<AngleListCount;k+=2){
				double	d=AngleDownList[k].MakeAverageAndPeaks(RThr->MaxLineWidth*2
															   ,(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL)?true:false);
				if(d>maxPeak){
					maxPeak=d;
					MaxIndex=k;
				}
			}
		}
	}
	index=0;
	n=CalcArea.GetFLineLen();
	if(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL){
		for(int i=0;i<n;i++){
			int x1=CalcArea.GetFLineLeftX (i);
			int x2=CalcArea.GetFLineRightX(i);
			int y =CalcArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			BYTE	*m=DynamicMaskMap[y+my];
			for(int x=x1;x<x2;x++){
				if(GetBmpBitOnY(m,x+mx)==0){
					BYTE	c=s[x+mx];
					AngleList[MaxIndex].ExecutePreProcessing(index,c);
					index++;
				}
				else{
					AngleList[MaxIndex].ExecutePreProcessingReduceDynamicMasking(index);
					index++;
				}
			}
		}
	}
	else{
		for(int i=0;i<n;i++){
			int x1=CalcArea.GetFLineLeftX (i);
			int x2=CalcArea.GetFLineRightX(i);
			int y =CalcArea.GetFLineAbsY  (i);
			BYTE	*s=IBuff.GetY(y+my);
			for(int x=x1;x<x2;x++){
				BYTE	c=s[x+mx];
				AngleList[MaxIndex].ExecutePreProcessing(index,c);
				index++;
			}
		}
	}
	AngleList[MaxIndex].MakeAverageAndPeaks(RThr->MaxLineWidth,(RThr->ExcludeDynamicMask==true && DynamicMaskMap!=NULL)?true:false);
	AngleList[MaxIndex].Reflect(mx,my,CalcArea,IBuff,RThr->EmphasizeRate
								,RThr->ExcludeDynamicMask
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);	
}