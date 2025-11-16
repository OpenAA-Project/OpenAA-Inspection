#include "XLineEnhancer.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>

LineEnhancerItem::AngleDimBase::AngleDimBase(void)
{
	AddedList			=NULL;
	PixelCount			=NULL;
	PixelCDivider		=NULL;
	PointerIndex		=NULL;
	ListNumb			=0;
	AllAvr				=-1;
	PointerIndexCount	=0;

	CosS=SinS	=0;
	Cx	=Cy		=0;
}
LineEnhancerItem::AngleDimBase::~AngleDimBase(void)
{
	if(AddedList!=NULL){
		delete	[]AddedList;
		AddedList=NULL;
	}
	if(PixelCount!=NULL){
		delete	[]PixelCount;
		PixelCount=NULL;
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

void	LineEnhancerItem::AngleDimBase::Initial(double Radian, FlexArea &area)
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
		if(PixelCDivider!=NULL){
			delete	[]PixelCDivider;
		}
		ListNumb=iListNumb;
		AddedList=new double[ListNumb];
		PixelCount=new int32[ListNumb];
		PixelCDivider=new double[ListNumb];
	}

	CosS=cos(Radian);
	SinS=sin(Radian);
	area.GetCenter(Cx,Cy);
}


void	LineEnhancerItem::AngleDim::Initial(double Radian, FlexArea &area)
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
void	LineEnhancerItem::AngleDimDown::Initial(double Radian, FlexArea &area)
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
void	LineEnhancerItem::AngleDim::ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo)
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
void	LineEnhancerItem::AngleDimDown::ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo)
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

void	LineEnhancerItem::AngleDimBase::ExecuteStartByInspection(void)
{
	for(int i=0;i<ListNumb;i++){
		AddedList[i]=0;
	}
}

double	LineEnhancerItem::AngleDimBase::MakeAverageAndPeaks(int MaxLineWidth)
{
	AllAvr=0;
	int		AllAvrCount=0;
	for(int i=0;i<ListNumb;i++){
		if(PixelCount[i]>0){
			AddedList[i]=AddedList[i]*PixelCDivider[i];
		}
		if(PixelCount[i]>4){
			AllAvr+=AddedList[i];
			AllAvrCount++;
		}
	}
	if(AllAvrCount==0){
		AllAvr=-1;
	}
	else{
		AllAvr/=AllAvrCount;
	}
	double	MaxPeak=0;
	for(int i=MaxLineWidth;i<ListNumb-MaxLineWidth;i++){
		if(PixelCount[i-MaxLineWidth]>4 && PixelCount[i]>4 && PixelCount[i+MaxLineWidth]>4){
			double	d1=AddedList[i-MaxLineWidth]-AllAvr;
			double	d2=AddedList[i             ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PixelCount[i-MaxLineWidth+1]>4 && PixelCount[i]>4 && PixelCount[i+MaxLineWidth]>4){
			double	d1=AddedList[i-MaxLineWidth+1]-AllAvr;
			double	d2=AddedList[i               ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth  ]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PixelCount[i-MaxLineWidth  ]>4 && PixelCount[i]>4 && PixelCount[i+MaxLineWidth-1]>4){
			double	d1=AddedList[i-MaxLineWidth  ]-AllAvr;
			double	d2=AddedList[i               ]-AllAvr;
			double	d3=AddedList[i+MaxLineWidth-1]-AllAvr;
			double	d=(d2-d1)*(d2-d3);
			if(d>MaxPeak){
				MaxPeak=d;
			}
		}
		else if(PixelCount[i-MaxLineWidth+1]>4 && PixelCount[i]>4 && PixelCount[i+MaxLineWidth-1]>4){
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

void	LineEnhancerItem::AngleDim::Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate)
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

double	LineEnhancerItem::CalcV(int mx,int my,ImageBuffer &IBuff)
//	ƒ°(v-a)^2	=ƒ°v^2 - 2*ƒ°v*a + ƒ°a*a
//				=ƒ°v^2 - 2*a*ƒ°v + a*a*N
//			a*N=ƒ°v
{
	int n=MatchingArea.GetFLineLen();
	int	DotC=0;
	double	AddC	=0.0;
	double	AddCC	=0.0;
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

int	DbgPx=3470;
int	DbgPy=466;
int	DbgPoint;

void	LineEnhancerItem::ExecutePreProcessingByLayer(int mx,int my,ImageBuffer &IBuff
													,int &ResMx ,int &ResMy 
													,int Layer)
{
	if(GetArea().IsInclude(DbgPx,DbgPy)==true){
		DbgPoint++;
	}
	double	MinDiv=65535.0*65535.0*65535.0;
	int	MinDx=0;
	int	MinDy=0;
	int	MasterColor=MasterBrightness[Layer];
	const LineEnhancerThreshold	*RThr=GetThresholdR();
	for(int dy=-RThr->SelfSearch;dy<=RThr->SelfSearch;dy+=2){
		for(int dx=-RThr->SelfSearch;dx<=RThr->SelfSearch;dx+=2){
			double	TempV=CalcV(mx+dx,my+dy,IBuff);
			double	C=MatchingArea.GetAverage(IBuff,mx+dx,my+dy);
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
			double	TempV=CalcV(mx+dx,my+dy,IBuff);
			double	C=MatchingArea.GetAverage(IBuff,mx+dx,my+dy);
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

	for(int k=0;k<AngleListCount;k++){
		AngleList[k].ExecuteStartByInspection();
	}
	for(int k=0;k<AngleListCount;k++){
		AngleDownList[k].ExecuteStartByInspection();
	}	
	
	int	index=0;
	int n=CalcArea.GetFLineLen();
	for(int i=0;i<n;i++){
		int x1=CalcArea.GetFLineLeftX (i);
		int x2=CalcArea.GetFLineRightX(i);
		int y =CalcArea.GetFLineAbsY  (i);
		BYTE	*s=IBuff.GetY(y+my);
		for(int x=((y&1)==0)?((x1+1)&0xFFFFE):(x1|1);x<x2;x+=2){
			BYTE	c=s[x+mx];
			for(int k=0;k<AngleListCount;k+=2){
				AngleDownList[k].ExecutePreProcessing(index,c);
			}
			index++;
		}
	}
	double	maxPeak=0;
	int		MaxIndex=0;
	for(int k=0;k<AngleListCount;k+=2){
		double	d=AngleDownList[k].MakeAverageAndPeaks(RThr->MaxLineWidth*2);
		if(d>maxPeak){
			maxPeak=d;
			MaxIndex=k;
		}
	}
	int	MinK=MaxIndex-1;
	if(MinK<0)
		MinK=0;
	int	MaxK=MaxIndex+1;
	if(MaxK>=AngleListCount){
		MaxK=AngleListCount-1;
	}
	
	index=0;
	n=CalcArea.GetFLineLen();
	for(int i=0;i<n;i++){
		int x1=CalcArea.GetFLineLeftX (i);
		int x2=CalcArea.GetFLineRightX(i);
		int y =CalcArea.GetFLineAbsY  (i);
		BYTE	*s=IBuff.GetY(y+my);
		for(int x=x1;x<x2;x++){
			BYTE	c=s[x+mx];
			for(int k=MinK;k<=MaxK;k++){
				AngleList[k].ExecutePreProcessing(index,c);
			}
			index++;
		}
	}
	maxPeak=0;
	MaxIndex=0;
	for(int k=MinK;k<=MaxK;k++){
		double	d=AngleList[k].MakeAverageAndPeaks(RThr->MaxLineWidth);
		if(d>maxPeak){
			maxPeak=d;
			MaxIndex=k;
		}
	}

	AngleList[MaxIndex].Reflect(mx,my,CalcArea,IBuff,RThr->EmphasizeRate);	
}