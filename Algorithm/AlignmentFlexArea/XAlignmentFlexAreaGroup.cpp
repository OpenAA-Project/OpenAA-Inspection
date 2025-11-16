#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XMultiEquSolve.h"
#include "XCrossObj.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include "XPacketAlignmentFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	DbgID=10923;
static	int	DbgData=0;
//---------------------------------------------------------------------------------------
AlignmentGroup::AlignmentGroup(XAlignmentFlexAreaArea *p)
	:GroupID(-1)
	,ResultDx(0),ResultDy(0)
{
	ParentInPage=p->ParentInPage;
	ParentArea	=p;

	ShiftList			=NULL;
	ShiftListNumb		=0;
	SortedList			=NULL;
	AllocSortedListNumb	=0;
	SortedListNumb		=0;
	MatchList			=NULL;
	DList				=NULL;
	IList				=NULL;

	CountOfBestMatch	=0;
	AdoptedIndex		=0;
	GlobalShiftX		=0;
	GlobalShiftY		=0;

	MinX=MinY	=0;
	MaxX=MaxY	=0;
}
AlignmentGroup::~AlignmentGroup(void)
{
	if(ShiftList!=NULL){
		delete	[]ShiftList;
		ShiftList=NULL;
	}
	if(SortedList!=NULL){
		delete	[]SortedList;
		SortedList=NULL;
	}
	if(MatchList!=NULL){
		delete	[]MatchList;
		MatchList=NULL;
	}
	if(DList!=NULL){
		delete	[]DList;
		DList=NULL;
	}
	if(IList!=NULL){
		delete	[]IList;
		IList=NULL;
	}
}
AlignmentGroup	&AlignmentGroup::operator=(const AlignmentGroup &src)
{
	if(ShiftList!=NULL){
		delete	[]ShiftList;
	}
	ShiftListNumb	=src.ShiftListNumb;
	ShiftList=new struct AlignmentFlexAreaShiftListIndexStruct[ShiftListNumb];
	memcpy(ShiftList,src.ShiftList,sizeof(ShiftList[0])*ShiftListNumb);

	if(SortedList!=NULL)
		delete	[]SortedList;
	AllocSortedListNumb	=src.AllocSortedListNumb;
	SortedList=new struct AlignmentFlexAreaShiftListIndexStruct[AllocSortedListNumb];
	memcpy(SortedList,src.SortedList,sizeof(SortedList[0])*AllocSortedListNumb);
	return *this;
}

void	AlignmentGroup::ExecuteStartByInspection(void)
{
	for(int i=0;i<sizeof(BestMatch)/sizeof(BestMatch[0]);i++){
		BestMatch[i].Adopted=false;
	}
	GlobalShiftX=GlobalShiftY=0;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetItem()->ExecuteStartByInspection(0,NULL ,NULL);
	}
}

bool	AlignmentGroup::HasItem(void)
{
	if(ItemPack.GetFirst()!=NULL){
		return true;
	}
	return false;
}

void	AlignmentGroup::MakeShiftList(void)
{
	if(ShiftList!=NULL){
		delete	[]ShiftList;
	}
	if(SortedList!=NULL){
		delete	[]SortedList;
		SortedList=NULL;
		AllocSortedListNumb	=0;
	}
	if(MatchList!=NULL){
		delete	[]MatchList;
	}
	AlignmentFlexAreaBase	*ABase=(AlignmentFlexAreaBase *)ParentInPage->GetParentBase();
	int	Sep=ABase->SkipDotForRoughSearch;
	int	GlobalSearchDot	=99999999;
	int	SearchDot		=99999999;
	
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		const	AlignmentFlexAreaThreshold	*RThr=((AlignmentFlexAreaItem *)p->GetItem())->GetThresholdR(NULL);
		if(GlobalSearchDot>RThr->GlobalSearchDot){
			GlobalSearchDot=RThr->GlobalSearchDot;
		}
		if(SearchDot>RThr->SearchDot){
			SearchDot=RThr->SearchDot;
		}
	}
	if(ParentArea->Priority==XAlignmentFlexAreaArea::_PriorityGlobal)
		SearchDot=GlobalSearchDot;

	int	Lm=(2*SearchDot+1+Sep-1)/Sep;
	int	LNumb=Lm*Lm;
	ShiftListNumb=0;
	ShiftList=new struct AlignmentFlexAreaShiftListIndexStruct[LNumb];
	if(SortedList!=NULL)
		delete	[]SortedList;
	SortedList=new struct AlignmentFlexAreaShiftListIndexStruct[LNumb];

	for(int y=-SearchDot;y<=SearchDot;y+=Sep){
		for(int x=-SearchDot;x<=SearchDot;x+=Sep){
			bool	Inside=true;
			for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
				int	x1=p->GetItem()->GetArea().GetMinX()+x;
				int	y1=p->GetItem()->GetArea().GetMinY()+y;
				int	x2=p->GetItem()->GetArea().GetMaxX()+x;
				int	y2=p->GetItem()->GetArea().GetMaxY()+y;
				if(x1<0 || ParentInPage->GetDotPerLine()<=x2 || y1<0 || ParentInPage->GetMaxLines()<=y2){
					Inside=false;
					break;
				}
			}
			if(Inside==true){
				ShiftList[ShiftListNumb].Index=0;
				ShiftList[ShiftListNumb].Dx=x;
				ShiftList[ShiftListNumb].Dy=y;
				ShiftList[ShiftListNumb].Match=0;
				ShiftListNumb++;
			}
		}
	}
	int	n=ItemPack.GetCount();
	MatchList=new struct	AlignmentMatchList[max(n,ShiftListNumb)];

	if(DList!=NULL){
		delete	[]DList;
	}
	DList=new double[n];


	if(IList!=NULL){
		delete	[]IList;
	}
	IList=new int[n];

	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		if(a->MatchList!=NULL){
			delete	[]a->MatchList;
		}
		a->MatchList=new struct	AlignmentMatchList[ShiftListNumb];
		a->MatchListNumb=ShiftListNumb;
	}
}

bool	AlignmentGroup::AddItem(AlgorithmItemRoot *Item ,int GroupAreaSize)
{
	/*
	int	X1=99999999;
	int	Y1=99999999;
	int	X2=-99999999;
	int	Y2=-99999999;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		int	x1,y1,x2,y2;
		p->GetItem()->GetXY(x1,y1,x2,y2);
		X1=min(X1,x1);
		Y1=min(Y1,y1);
		X2=max(X2,x2);
		Y2=max(Y2,y2);
	}
	*/
	int		iMinX=MinX;
	int		iMinY=MinY;
	int		iMaxX=MaxX;
	int		iMaxY=MaxY;
	if(ItemPack.GetCount()==0){
		Item->GetXY(iMinX,iMinY,iMaxX,iMaxY);
	}
	else{
		int	x1,y1,x2,y2;
		Item->GetXY(x1,y1,x2,y2);
		iMinX=min(iMinX,x1);
		iMinY=min(iMinY,y1);
		iMaxX=max(iMaxX,x2);
		iMaxY=max(iMaxY,y2);
	}
	int	W=iMaxX-iMinX;
	int	H=iMaxY-iMinY;
	if(W<GroupAreaSize && H<GroupAreaSize){
		MinX=iMinX;
		MinY=iMinY;
		MaxX=iMaxX;
		MaxY=iMaxY;
		ItemPack.Add(Item);
		return true;
	}
	return false;
}

bool	AlignmentGroup::AppendItem(AlgorithmItemRoot *Item)
{
	Item->GetXY(MinX,MinY,MaxX,MaxY);
	ItemPack.Add(Item);
	return true;
}

void	AlignmentGroup::CalcCenter(void)
{
	int	X1=99999999;
	int	Y1=99999999;
	int	X2=-99999999;
	int	Y2=-99999999;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		int	x1,y1,x2,y2;
		p->GetItem()->GetXY(x1,y1,x2,y2);
		X1=min(X1,x1);
		Y1=min(Y1,y1);
		X2=max(X2,x2);
		Y2=max(Y2,y2);
	}
	CenterX=(X1+X2)/2;
	CenterY=(Y1+Y2)/2;
}
	
void	AlignmentGroup::GetCenter(int &Cx ,int &Cy)
{
	Cx=CenterX;
	Cy=CenterY;
}

void	AlignmentGroup::SetShiftByGlobal(void)
{
	AlignmentPacket2D	AData;
	AData.PosXOnTarget=CenterX;
	AData.PosYOnTarget=CenterY;
	IndexForGroup	*G=ParentInPage->GetAlignmentFlexAreaGlobalIndex(AData);
	if(G!=NULL){
		G->CalcShift(CenterX,CenterY,GlobalShiftX,GlobalShiftY);
	}
	else{
		GlobalShiftX=0;
		GlobalShiftY=0;
	}
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		if(a->GetID()==DbgID){
			DbgData++;
		}
		int	cx,cy;
		a->GetCenter(cx,cy);
		/*
		AlignmentPacket2D	AData;
		AData.PosXOnTarget=cx;
		AData.PosYOnTarget=cy;
		ParentInPage->GetAlignmentFlexAreaGlobal(AData);
		a->ShiftByGlobalX=AData.ShiftX;
		a->ShiftByGlobalY=AData.ShiftY;
		*/
		if(G!=NULL){
			G->CalcShift(cx,cy,a->ShiftByGlobalX,a->ShiftByGlobalY);
		}
		else{
			a->ShiftByGlobalX=0;
			a->ShiftByGlobalY=0;
		}
	}

}
void	AlignmentGroup::SetShiftByGlobal(int dx ,int dy)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		a->ShiftByGlobalX=dx;
		a->ShiftByGlobalY=dy;
	}
}

static	int	SortMatchListFunc(const void *a ,const void *b)
{
	struct AlignmentMatchList	*pa=(struct AlignmentMatchList *)a;
	struct AlignmentMatchList	*pb=(struct AlignmentMatchList *)b;
	if(pa->MatchRate>pb->MatchRate)
		return -1;
	if(pa->MatchRate<pb->MatchRate)
		return 1;
	return 0;
}

static	int	SortMatchListFuncLow(const void *a ,const void *b)
{
	struct AlignmentMatchList	*pa=(struct AlignmentMatchList *)a;
	struct AlignmentMatchList	*pb=(struct AlignmentMatchList *)b;
	if(pa->MatchRate>pb->MatchRate)
		return 1;
	if(pa->MatchRate<pb->MatchRate)
		return -1;
	return 0;
}

static	int	SortMatchListIndexFunc(const void *a ,const void *b)
{
	struct AlignmentMatchList	*pa=(struct AlignmentMatchList *)a;
	struct AlignmentMatchList	*pb=(struct AlignmentMatchList *)b;
	if(pa->Index>pb->Index)
		return 1;
	if(pa->Index<pb->Index)
		return -1;
	return 0;
}

static	int	SortIntFunc(const void *a ,const void *b)
{
	int	*pa=(int *)a;
	int	*pb=(int *)b;
	if(*pa>*pb)
		return 1;
	if(*pa<*pb)
		return -1;
	return 0;
}
static	int	SortDoubleFunc(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(fabs(*pa)>fabs(*pb))
		return -1;
	if(fabs(*pa)<fabs(*pb))
		return 1;
	return 0;
}

static	int	FuncShiftList(const void *a ,const void *b)
{
	struct	AlignmentFlexAreaShiftListIndexStruct	*pa=(struct	AlignmentFlexAreaShiftListIndexStruct	*)a;
	struct	AlignmentFlexAreaShiftListIndexStruct	*pb=(struct	AlignmentFlexAreaShiftListIndexStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}
static	int	FuncShiftListIndex(const void *a ,const void *b)
{
	struct	AlignmentFlexAreaShiftListIndexStruct	*pa=(struct	AlignmentFlexAreaShiftListIndexStruct	*)a;
	struct	AlignmentFlexAreaShiftListIndexStruct	*pb=(struct	AlignmentFlexAreaShiftListIndexStruct	*)b;
	if(pa->Index>pb->Index)
		return -1;
	else if(pa->Index<pb->Index)
		return 1;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}
static	int	SortBestMatchFunc(const void *a , const void *b)
{
	struct	AlignmentFlexAreaShiftItemListStruct	*pa=(struct	AlignmentFlexAreaShiftItemListStruct	*)a;
	struct	AlignmentFlexAreaShiftItemListStruct	*pb=(struct	AlignmentFlexAreaShiftItemListStruct	*)b;
	if(pa->Match>pb->Match)
		return -1;
	else if(pa->Match<pb->Match)
		return 1;
	return 0;
}

void	AlignmentGroup::CalcAlignment(ImagePointerContainer &Images,ImagePointerContainer &TRImages,int offsetX,int offsetY)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		FlexArea	&a=p->GetItem()->GetArea();
		if(a.GetPatternByte()==0
		|| (a.GetMinX()+offsetX)<0 
		|| (a.GetMaxX()+offsetX)>=ParentInPage->GetDotPerLine() 
		|| (a.GetMinY()+offsetY)<0 
		|| (a.GetMaxY()+offsetY)>=ParentInPage->GetMaxLines()){
			ResultDx=offsetX;
			ResultDy=offsetY;
			return ;
		}
	}

	int	GlobalSearchDot	=99999999;
	int	SearchDot		=99999999;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		const	AlignmentFlexAreaThreshold	*RThr=((AlignmentFlexAreaItem *)p->GetItem())->GetThresholdR(NULL);
		if(GlobalSearchDot>RThr->GlobalSearchDot){
			GlobalSearchDot=RThr->GlobalSearchDot;
		}
		if(SearchDot>RThr->SearchDot){
			SearchDot=RThr->SearchDot;
		}
	}
	//ForDebug
	int	DotPerLine	=ParentInPage->GetDotPerLine();
	int	MaxLines	=ParentInPage->GetMaxLines();
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetItem()->GetID()==DbgID){
			DbgData++;
			for(int i=0;i<ShiftListNumb;i++){
				SortedList[i]=ShiftList[i];
				SortedList[i].Match=0;
				SortedList[i].Index=0;
				AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
				const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(NULL);
				int	Layer=RThr->TargetLayer;
				if(Layer>ParentInPage->GetLayerNumb()){
					Layer=0;
				}
				ImageBuffer	*IBuff	=Images[Layer];
				ImageBuffer	*TRIBuff=TRImages[Layer];
				if(i<a->MatchListNumb){
					double	MaxD=0;
					for(int u=0;u<3;u++){
						double	d=a->MatchCross(*IBuff,*TRIBuff
												,ShiftList[i].Dx+offsetX+a->ShiftByGlobalX,ShiftList[i].Dy+offsetY+a->ShiftByGlobalY,u
												,DotPerLine,MaxLines);
						d=a->AdjustByLength(d,ShiftList[i].Dx,ShiftList[i].Dy);
						if(d>MaxD){
							MaxD=d;
						}
					}
					if(RThr->KeepBW==true){
						if(MaxD!=0.0){
							SortedList[i].Index++;
							SortedList[i].Match+=MaxD;
						}
					}
					else{
						if(MaxD!=0.0){
							SortedList[i].Index++;
							SortedList[i].Match+=fabs(MaxD);
						}
					}
				}
			}
			QSort(SortedList,ShiftListNumb,sizeof(SortedList[0]),FuncShiftListIndex);
		}
	}
	int	SepCount=ItemPack.GetCount()/10;
	if(SepCount==0)
		SepCount=1;
	int	LayerNumb=ParentInPage->GetLayerNumb();
	for(int i=0;i<ShiftListNumb;i++){
		SortedList[i]=ShiftList[i];
		SortedList[i].Match=0;
		SortedList[i].Index=0;
		int	N=0;
		for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext(),N++){
			if((N%SepCount)!=0){
				continue;
			}
			AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
			const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
			int	Layer=RThr->TargetLayer;
			if(Layer>=LayerNumb){
				Layer=0;
			}
			ImageBuffer	*IBuff=Images[Layer];
			ImageBuffer	*TRIBuff=TRImages[Layer];
			if(i<a->MatchListNumb){
				double	d=a->MatchCross(*IBuff,*TRIBuff
										,ShiftList[i].Dx+offsetX+a->ShiftByGlobalX,ShiftList[i].Dy+offsetY+a->ShiftByGlobalY,AlignmentFlexAreaNormalLine
										,DotPerLine,MaxLines);
				d=a->AdjustByLength(d,ShiftList[i].Dx,ShiftList[i].Dy);
				if(RThr->KeepBW==true){
					if(d!=0.0){
						SortedList[i].Index++;
						SortedList[i].Match+=d;
					}
				}
				else{
					if(d!=0.0){
						SortedList[i].Index++;
						SortedList[i].Match+=fabs(d);
					}
				}
			}
		}
	}
	QSort(SortedList,ShiftListNumb,sizeof(SortedList[0]),FuncShiftListIndex);

	struct	AlignmentFlexAreaShiftListStruct	DetailList[1000];
	int	N=min(4,ShiftListNumb);
	int	DetailListNumb=0;
	for(int i=0;i<N;i++){
		int	Kx=SortedList[i].Dx;
		int	Ky=SortedList[i].Dy;
		for(int x=-4;x<=4;x+=2){
			for(int y=-4;y<=4;y+=2){
				DetailList[DetailListNumb].Match=0;
				int	N=0;
				for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext(),N++){
					if((N%SepCount)!=0){
						continue;
					}
					AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
					const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
					int	Layer=RThr->TargetLayer;
					if(Layer>ParentInPage->GetLayerNumb()){
						Layer=0;
					}
					ImageBuffer	*IBuff=Images[Layer];
					ImageBuffer	*TRIBuff=TRImages[Layer];
					double	d=a->MatchCross(*IBuff,*TRIBuff
											,Kx+offsetX+x+a->ShiftByGlobalX,Ky+offsetY+y+a->ShiftByGlobalY,AlignmentFlexAreaNormalLine
											,DotPerLine,MaxLines);
					d=a->AdjustByLength(d,Kx+x,Ky+y);
					if(RThr->KeepBW==true)
						DetailList[DetailListNumb].Match+=d;
					else
						DetailList[DetailListNumb].Match+=fabs(d);
				}
				DetailList[DetailListNumb].Dx=Kx+offsetX+x+GlobalShiftX;
				DetailList[DetailListNumb].Dy=Ky+offsetY+y+GlobalShiftY;
				int	h;
				for(h=0;h<DetailListNumb;h++){
					if(DetailList[h].Dx==DetailList[DetailListNumb].Dx
					&& DetailList[h].Dy==DetailList[DetailListNumb].Dy){
						break;
					}
				}
				if(h>=DetailListNumb){
					DetailListNumb++;
				}
			}
		}
	}
	QSort(DetailList,DetailListNumb,sizeof(DetailList[0]),FuncShiftList);

	if(DetailListNumb==0 || DetailList[0].Match==0){
		ResultDx=offsetX;
		ResultDy=offsetY;
		return;
	}
	CountOfBestMatch=min(3,DetailListNumb);
	int	OutlineWidth=1;

	for(int K=0;K<CountOfBestMatch;K++){
		int		MaxDX=DetailList[K].Dx;
		int		MaxDY=DetailList[K].Dy;

		double	hMaxD=0;
		int		hMaxDX=0;
		int		hMaxDY=0;
		for(int y=-OutlineWidth;y<=OutlineWidth;y+=2){
			for(int x=-OutlineWidth;x<=OutlineWidth;x+=2){
				double	d=TransAreaCalcCoeff(MaxDX+x,MaxDY+y,Images);
				if(d>=hMaxD){
					hMaxD=d;
					hMaxDX=x;
					hMaxDY=y;
				}
			}
		}

		double	qMaxD=0;
		int		qMaxDX=0;
		int		qMaxDY=0;
		for(int y=-1;y<=1;y++){
			for(int x=-1;x<=1;x++){
				double	d=TransAreaCalcCoeff(MaxDX+hMaxDX+x,MaxDY+hMaxDY+y	,Images);
				if(d>=qMaxD){
					qMaxD=d;
					qMaxDX=x;
					qMaxDY=y;
				}
			}
		}
		int	vx=MaxDX+hMaxDX+qMaxDX;
		int	vy=MaxDY+hMaxDY+qMaxDY;
		BestMatch[K].Dx		=vx;
		BestMatch[K].Dy		=vy;
		BestMatch[K].Match	=qMaxD;
		BestMatch[K].Item	=this;
		BestMatch[K].Adopted=false;
	}

	QSort(BestMatch,CountOfBestMatch,sizeof(BestMatch[0]),SortBestMatchFunc);
	BindNext:;
	for(int i=CountOfBestMatch-1;i>=1;i--){
		for(int j=0;j<i;j++){
			if(BestMatch[i].Dx==BestMatch[j].Dx && BestMatch[i].Dy==BestMatch[j].Dy){
				for(int k=i;k<CountOfBestMatch-1;k++){
					BestMatch[k]=BestMatch[k+1];
				}
				CountOfBestMatch--;
				goto	BindNext;
			}
		}
	}

	ResultDx=BestMatch[0].Dx;
	ResultDy=BestMatch[0].Dy;

}

double	AlignmentGroup::GetMinMatchByMaster(ImagePointerContainer &Images ,ImagePointerContainer &TRImages ,int dx,int dy)
{
	double	MinD=99999999;
	int	ShiftSmall=2;
	int	DotPerLine	=ParentInPage->GetDotPerLine();
	int	MaxLines	=ParentInPage->GetMaxLines();
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
		int	Layer=RThr->TargetLayer;
		if(Layer>ParentInPage->GetLayerNumb()){
			Layer=0;
		}
		ImageBuffer	*IBuff	=Images[Layer];
		ImageBuffer	*TRIBuff=TRImages[Layer];
		double	MaxD=0;

		for(int x=-ShiftSmall;x<=ShiftSmall;x++){
			for(int y=-ShiftSmall;y<=ShiftSmall;y++){
				double	d=a->MatchCross(*IBuff,*TRIBuff
										,dx+x,dy+y,AlignmentFlexAreaNormalLine
										,DotPerLine,MaxLines);
				if(RThr->KeepBW==false)
					d=fabs(d);
				if(MaxD<d){
					MaxD=d;
				}
			}
		}
		if(MinD>MaxD){
			MinD=MaxD;
		}
	}
	return MinD;
}

double	AlignmentGroup::GetMaxMatchByMaster(ImagePointerContainer &Images ,ImagePointerContainer &TRImages ,int dx,int dy)
{
	double	AddedD=0;
	int	ShiftSmall=0;	//2;
	int	DotPerLine	=ParentInPage->GetDotPerLine();
	int	MaxLines	=ParentInPage->GetMaxLines();
	if(ItemPack.GetCount()<20){
		for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
			AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
			const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
			int	Layer=RThr->TargetLayer;
			if(Layer>ParentInPage->GetLayerNumb()){
				Layer=0;
			}
			ImageBuffer	*IBuff	=Images[Layer];
			ImageBuffer	*TRIBuff=TRImages[Layer];
				
			double	MaxD=0;

			for(int x=-ShiftSmall;x<=ShiftSmall;x++){
				for(int y=-ShiftSmall;y<=ShiftSmall;y++){
					double	d=a->MatchCross(*IBuff,*TRIBuff
											,dx+x,dy+y,AlignmentFlexAreaNormalLine
											,DotPerLine,MaxLines);
					if(RThr->KeepBW==false)
						d=fabs(d);
					if(MaxD<d){
						MaxD=d;
					}
				}
			}
			AddedD+=MaxD;
		}
	}
	else{
		int	Skip=ItemPack.GetCount()/10;
		for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;){
			AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
			const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
			int	Layer=RThr->TargetLayer;
			if(Layer>ParentInPage->GetLayerNumb()){
				Layer=0;
			}
			ImageBuffer	*IBuff	=Images[Layer];
			ImageBuffer	*TRIBuff=TRImages[Layer];	
			double	MaxD=0;

			for(int x=-ShiftSmall;x<=ShiftSmall;x++){
				for(int y=-ShiftSmall;y<=ShiftSmall;y++){
					double	d=a->MatchCross(*IBuff,*TRIBuff
											,dx+x,dy+y,AlignmentFlexAreaNormalLine
											,DotPerLine,MaxLines);
					if(RThr->KeepBW==false)
						d=fabs(d);
					if(MaxD<d){
						MaxD=d;
					}
				}
			}
			AddedD+=MaxD;
			for(int i=0;i<Skip && p!=NULL;i++){
				p=p->GetNext();
			}
		}
	}
	return AddedD;
}

bool	AlignmentGroup::IsInclude(int x ,int y)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		if(a->GetArea().IsInclude(x,y)==true)
			return true;
	}
	return false;
}
double	AlignmentGroup::TransAreaCalcCoeff(int dx,int dy,ImagePointerContainer &Images )
{
	int	Row=0;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext(),Row++){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		const	AlignmentFlexAreaThreshold	*RThr=a->GetThresholdR(ParentInPage->GetLayersBase());
		int	Layer=RThr->TargetLayer;
		if(Layer>ParentInPage->GetLayerNumb()){
			Layer=0;
		}
		ImageBuffer	*IBuff=Images[Layer];
		double	d=a->TransAreaCalcCoeff(dx,dy,*IBuff);
		if(RThr->KeepBW==false)
			d=fabs(d);
		DList[Row]=d;
	}
	QSort(DList,Row,sizeof(double),SortDoubleFunc);
	int	Row2=(Row+1)/2;
	int	Plus=0;
	int	Minus=0;
	double	SumD=0;
	for(int j=0;j<Row2;j++){
		if(DList[j]>0)
			Plus++;
		if(DList[j]<0)
			Minus++;
		SumD+=DList[j];
	}
	if(Plus==0 || Minus==0){
		return SumD;
	}
	return 0;
}
	
void	AlignmentGroup::DeleteSelectedItems(void)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;){
		AlgorithmItemPointerList *NextP=p->GetNext();
		AlgorithmItemRoot	*Item=p->GetItem();
		if(Item->GetSelected()==true && Item->GetEditLocked()==false){
			ItemPack.RemoveList(p);
			ParentInPage->RemoveItem(Item);
			delete	p;
			delete	Item;
		}
		p=NextP;
	}
}

void	AlignmentGroup::ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems)
{
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetItem()->ExecuteMove(GlobalDx,GlobalDy, AllItems);
	}
}
void	AlignmentGroup::Draw(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	Cx,Cy;
	GetCenter(Cx ,Cy);
	int	X=(Cx+movx)*ZoomRate;
	int	Y=(Cy+movy)*ZoomRate;

	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::white);
	Pnt.drawText(X,Y
				,QString(/**/"Shift=")	+QString::number(ResultDx )+QString(/**/",")+QString::number(ResultDy));
}

//---------------------------------------------------------------------------------------

IndexForGroup::IndexForGroup(int id,int _AreaID)
{
	ID		=id;
	AreaID	=_AreaID;
	Index[0]=NULL;
	Index[1]=NULL;
	Index[2]=NULL;
}

double	IndexForGroup::GetDistance(int x,int y)
{
	double	LenD=0;
	int		Numb=0;
	for(int i=0;i<sizeof(Index)/sizeof(Index[0]);i++){
		if(Index[i]!=NULL){
			int	cx,cy;
			Index[i]->GetCenter(cx,cy);
			LenD+=hypot(x-cx,y-cy);
			Numb++;
		}
	}
	if(Numb!=0)
		return LenD/Numb;
	return 99999999;
}

bool	IndexForGroup::CheckEqual(AlignmentGroup *g1,AlignmentGroup *g2,AlignmentGroup *g3)
{
	if(Index[0]==g1 && Index[1]==g2 && Index[2]==g3)
		return true;
	if(Index[0]==g1 && Index[1]==g3 && Index[2]==g2)
		return true;
	if(Index[0]==g2 && Index[1]==g1 && Index[2]==g3)
		return true;
	if(Index[0]==g2 && Index[1]==g3 && Index[2]==g1)
		return true;
	if(Index[0]==g3 && Index[1]==g1 && Index[2]==g2)
		return true;
	if(Index[0]==g3 && Index[1]==g2 && Index[2]==g1)
		return true;
	return false;
}
static	int		DebugIndexDbg=0;
static	int		DebugIndexID=2;
static	int		DebugIndexGroupID=3;

void	IndexForGroup::MinimizeTransformation(double CutRate)
{
	if(ID==DebugIndexID)
		DebugIndexDbg++;
	/*
		a*x+b*y+c=X
		d*x+e*y+f=Y
		*/
	double	DMax=0;
	int		MaxI=0;
	int		MaxJ=0;
	int		MaxK=0;
	if(Index[0]!=NULL && Index[1]!=NULL && Index[2]!=NULL){
		for(int i=0;i<Index[0]->CountOfBestMatch;i++){
			if(Index[0]->BestMatch[i].Match/Index[0]->BestMatch[0].Match<CutRate)
				continue;
			int	cx1,cy1;
			Index[0]->BestMatch[i].Item->GetCenter(cx1,cy1);
			for(int j=0;j<Index[1]->CountOfBestMatch;j++){
				if(Index[1]->BestMatch[j].Match/Index[1]->BestMatch[0].Match<CutRate)
					continue;
				int	cx2,cy2;
				Index[1]->BestMatch[j].Item->GetCenter(cx2,cy2);
				for(int k=0;k<Index[2]->CountOfBestMatch;k++){
					if(Index[2]->BestMatch[k].Match/Index[2]->BestMatch[0].Match<CutRate)
						continue;
					int	cx3,cy3;
					Index[2]->BestMatch[k].Item->GetCenter(cx3,cy3);
					XMultiEquSolve	SolX;
					SolX.AllocateMatrix(3);
					SolX.SetMatrixValue(1,1,cx1);
					SolX.SetMatrixValue(2,1,cy1);
					SolX.SetMatrixValue(3,1,1);
					SolX.SetMatrixValue(1,2,cx2);
					SolX.SetMatrixValue(2,2,cy2);
					SolX.SetMatrixValue(3,2,1);
					SolX.SetMatrixValue(1,3,cx3);
					SolX.SetMatrixValue(2,3,cy3);
					SolX.SetMatrixValue(3,3,1);
					SolX.SetMatrixValueBn(1,cx1+Index[0]->BestMatch[i].Dx);
					SolX.SetMatrixValueBn(2,cx2+Index[1]->BestMatch[j].Dx);
					SolX.SetMatrixValueBn(3,cx3+Index[2]->BestMatch[k].Dx);
					SolX.ExecuteGaussianElimination();

					XMultiEquSolve	SolY;
					SolY.AllocateMatrix(3);
					SolY.SetMatrixValue(1,1,cx1);
					SolY.SetMatrixValue(2,1,cy1);
					SolY.SetMatrixValue(3,1,1);
					SolY.SetMatrixValue(1,2,cx2);
					SolY.SetMatrixValue(2,2,cy2);
					SolY.SetMatrixValue(3,2,1);
					SolY.SetMatrixValue(1,3,cx3);
					SolY.SetMatrixValue(2,3,cy3);
					SolY.SetMatrixValue(3,3,1);
					SolY.SetMatrixValueBn(1,cy1+Index[0]->BestMatch[i].Dy);
					SolY.SetMatrixValueBn(2,cy2+Index[1]->BestMatch[j].Dy);
					SolY.SetMatrixValueBn(3,cy3+Index[2]->BestMatch[k].Dy);
					SolY.ExecuteGaussianElimination();

					double	a=SolX.GetAnswer(1);
					double	b=SolX.GetAnswer(2);
					double	c=SolX.GetAnswer(3);
					double	d=SolY.GetAnswer(1);
					double	e=SolY.GetAnswer(2);
					double	f=SolY.GetAnswer(3);

					/*
						|cos  sin||p 0||1 tan|
						|-sin cos||0 q||0 1  |

						|p*cos  q*sin||1 tan|
						|-p*sin q*cos||0 1  |

						p*cos =a;
						p*cos*tan+q*sin=b;
						-p*sin=d
						-p*sin*tan+q*cos=e;

						a*tan+q*sin=b;		q*sin=(b-a*tan)
						d*tan+q*cos=e;		q*cos=(e-d*tan)

						a*cos*tan-d*sin*tan=b*cos-e*sin
						p^2=a^2+d^2		->  p = sqrt(a^2+d^2)
						cos=a/p
						sin=-d/p
						tan=(b*cos-e*sin)/(a*cos-d*sin)
						q=sqrt((b-a*tan)^2+(e-d*tan)^2)
						*/
					double	p=hypot(a,d);
					double	r=hypot(d,e);
					double	coss=a/p;
					double	sins=-d/p;
					double	tans=(b*coss-e*sins)/(a*coss-d*sins);
					double	q=hypot(b-a*tans,e-d*tans);
					
					if(p>1)
						p=1.0/p;
					if(q>1)
						q=1.0/q;
					if(r>1)
						r=1.0/r;
					double	s=atan(tans);
					double	D=cos(s)*hypot(p,q)*r;
					if(DMax<D){
						DMax=D;
						MaxI=i;
						MaxJ=j;
						MaxK=k;
						m[0]=a;
						m[1]=b;
						m[2]=c;
						m[3]=d;
						m[4]=e;
						m[5]=f;
					}
				}
			}
		}
		Index[0]->SetAdoptedIndex(MaxI);
		Index[1]->SetAdoptedIndex(MaxJ);
		Index[2]->SetAdoptedIndex(MaxK);
	}
	else if(Index[0]!=NULL && Index[1]!=NULL){
		for(int i=0;i<Index[0]->CountOfBestMatch;i++){
			if(Index[0]->BestMatch[i].Match/Index[0]->BestMatch[0].Match<CutRate)
				continue;
			int	cx1,cy1;
			Index[0]->BestMatch[i].Item->GetCenter(cx1,cy1);
			for(int j=0;j<Index[1]->CountOfBestMatch;j++){
				if(Index[1]->BestMatch[j].Match/Index[1]->BestMatch[0].Match<CutRate)
					continue;
				int	cx2,cy2;
				Index[1]->BestMatch[j].Item->GetCenter(cx2,cy2);

				/*
					a*x1+b*y1+c=x1+dx1
					a*x2+b*y2+c=x2+dx2

					-b*x1+a*y1+d=y1+dy1
					-b*x2+a*y2+d=y2+dy2

					a*(x1-x2)+b*(y1-y2)=x1-x2+dx1-dx2
					a*(y1-y2)-b*(x1-x2)=y1-y2+dy1-dy2
					*/


				XMultiEquSolve	SolX;
				SolX.AllocateMatrix(2);
				SolX.SetMatrixValue(1,1,cx1-cx2);
				SolX.SetMatrixValue(2,1,cy1-cy2);
				SolX.SetMatrixValue(1,2,cy1-cy2);
				SolX.SetMatrixValue(2,2,cx1-cx2);
				SolX.SetMatrixValueBn(1,cx1-cx2+Index[0]->BestMatch[i].Dx-Index[1]->BestMatch[j].Dx);
				SolX.SetMatrixValueBn(2,cy1-cy2+Index[0]->BestMatch[i].Dy-Index[1]->BestMatch[j].Dy);
				SolX.ExecuteGaussianElimination();

				double	a=SolX.GetAnswer(1);
				double	b=SolX.GetAnswer(2);
				double	p=hypot(a,b);
				if(p>1)
					p=1.0/p;

				if(DMax<p){
					DMax=p;
					MaxI=i;
					MaxJ=j;
					m[0]=a;
					m[1]=b;
				}
			}
		}
		Index[0]->SetAdoptedIndex(MaxI);
		Index[1]->SetAdoptedIndex(MaxJ);
	}
	else if(Index[0]!=NULL){
		m[0]=1;
		m[1]=0;
		m[2]=Index[0]->BestMatch[0].Dx;
		m[3]=0;
		m[4]=1;
		m[5]=Index[0]->BestMatch[0].Dy;
		Index[0]->SetAdoptedIndex(0);
	}
}

void	AlignmentGroup::SetAdoptedIndex(int index)
{
	if(GroupID==DebugIndexGroupID)
		DebugIndexDbg++;
	AdoptedIndex=index;
	for(AlgorithmItemPointerList *p=ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentFlexAreaItem	*a=((AlignmentFlexAreaItem *)p->GetItem());
		a->ResultDx=BestMatch[AdoptedIndex].Dx;
		a->ResultDy=BestMatch[AdoptedIndex].Dy;
		BestMatch[AdoptedIndex].Adopted=true;
	}
}

void	IndexForGroup::CalcParameter(void)
{
	if(ID==DebugIndexID)
		DebugIndexDbg++;
	if(Index[0]!=NULL && Index[1]!=NULL && Index[2]!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Item!=NULL
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Item!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Item!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Adopted==true
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Adopted==true
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Adopted==true){
		int	cx1,cy1;
		Index[0]->BestMatch[Index[0]->AdoptedIndex].Item->GetCenter(cx1,cy1);
		int	cx2,cy2;
		Index[1]->BestMatch[Index[1]->AdoptedIndex].Item->GetCenter(cx2,cy2);
		int	cx3,cy3;
		Index[2]->BestMatch[Index[2]->AdoptedIndex].Item->GetCenter(cx3,cy3);

		XMultiEquSolve	SolX;
		SolX.AllocateMatrix(3);
		SolX.SetMatrixValue(1,1,cx1);
		SolX.SetMatrixValue(2,1,cy1);
		SolX.SetMatrixValue(3,1,1);
		SolX.SetMatrixValue(1,2,cx2);
		SolX.SetMatrixValue(2,2,cy2);
		SolX.SetMatrixValue(3,2,1);
		SolX.SetMatrixValue(1,3,cx3);
		SolX.SetMatrixValue(2,3,cy3);
		SolX.SetMatrixValue(3,3,1);
		SolX.SetMatrixValueBn(1,cx1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx);
		SolX.SetMatrixValueBn(2,cx2+Index[1]->BestMatch[Index[1]->AdoptedIndex].Dx);
		SolX.SetMatrixValueBn(3,cx3+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dx);
		SolX.ExecuteGaussianElimination();

		XMultiEquSolve	SolY;
		SolY.AllocateMatrix(3);
		SolY.SetMatrixValue(1,1,cx1);
		SolY.SetMatrixValue(2,1,cy1);
		SolY.SetMatrixValue(3,1,1);
		SolY.SetMatrixValue(1,2,cx2);
		SolY.SetMatrixValue(2,2,cy2);
		SolY.SetMatrixValue(3,2,1);
		SolY.SetMatrixValue(1,3,cx3);
		SolY.SetMatrixValue(2,3,cy3);
		SolY.SetMatrixValue(3,3,1);
		SolY.SetMatrixValueBn(1,cy1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy);
		SolY.SetMatrixValueBn(2,cy2+Index[1]->BestMatch[Index[1]->AdoptedIndex].Dy);
		SolY.SetMatrixValueBn(3,cy3+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dy);
		SolY.ExecuteGaussianElimination();

		m[0]=SolX.GetAnswer(1);
		m[1]=SolX.GetAnswer(2);
		m[2]=SolX.GetAnswer(3);
		m[3]=SolY.GetAnswer(1);
		m[4]=SolY.GetAnswer(2);
		m[5]=SolY.GetAnswer(3);
	}
	else if(Index[0]!=NULL && Index[1]!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Item!=NULL
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Item!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Adopted==true
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Adopted==true){
		int	cx1,cy1;
		Index[0]->BestMatch[Index[0]->AdoptedIndex].Item->GetCenter(cx1,cy1);
		int	cx2,cy2;
		Index[1]->BestMatch[Index[1]->AdoptedIndex].Item->GetCenter(cx2,cy2);

		/*
			a*x1+b*y1+c=x1+dx1
			a*x2+b*y2+c=x2+dx2

			-b*x1+a*y1+d=y1+dy1
			-b*x2+a*y2+d=y2+dy2

			a*(x1-x2)+b*(y1-y2)=x1-x2+dx1-dx2
			a*(y1-y2)-b*(x1-x2)=y1-y2+dy1-dy2
			*/


		XMultiEquSolve	SolX;
		SolX.AllocateMatrix(2);
		SolX.SetMatrixValue(1,1,cx1-cx2);
		SolX.SetMatrixValue(2,1,cy1-cy2);
		SolX.SetMatrixValue(1,2,cy1-cy2);
		SolX.SetMatrixValue(2,2,-cx1+cx2);
		SolX.SetMatrixValueBn(1,cx1-cx2+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx-Index[1]->BestMatch[Index[1]->AdoptedIndex].Dx);
		SolX.SetMatrixValueBn(2,cy1-cy2+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy-Index[1]->BestMatch[Index[1]->AdoptedIndex].Dy);
		SolX.ExecuteGaussianElimination();

		double	a=SolX.GetAnswer(1);
		double	b=SolX.GetAnswer(2);
		double	c=cx1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx - a*cx1 - b*cy1;
		double	d=cy1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy + b*cx1 - a*cy1;

		m[0]=a;
		m[1]=b;
		m[2]=c;
		m[3]=-b;
		m[4]=a;
		m[5]=d;
	}
	else if(Index[2]!=NULL && Index[1]!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Item!=NULL
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Item!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Adopted==true
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Adopted==true){
		int	cx1,cy1;
		Index[2]->BestMatch[Index[2]->AdoptedIndex].Item->GetCenter(cx1,cy1);
		int	cx2,cy2;
		Index[1]->BestMatch[Index[1]->AdoptedIndex].Item->GetCenter(cx2,cy2);

		/*
			a*x1+b*y1+c=x1+dx1
			a*x2+b*y2+c=x2+dx2

			-b*x1+a*y1+d=y1+dy1
			-b*x2+a*y2+d=y2+dy2

			a*(x1-x2)+b*(y1-y2)=x1-x2+dx1-dx2
			a*(y1-y2)-b*(x1-x2)=y1-y2+dy1-dy2
			*/


		XMultiEquSolve	SolX;
		SolX.AllocateMatrix(2);
		SolX.SetMatrixValue(1,1,cx1-cx2);
		SolX.SetMatrixValue(2,1,cy1-cy2);
		SolX.SetMatrixValue(1,2,cy1-cy2);
		SolX.SetMatrixValue(2,2,-cx1+cx2);
		SolX.SetMatrixValueBn(1,cx1-cx2+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dx-Index[1]->BestMatch[Index[1]->AdoptedIndex].Dx);
		SolX.SetMatrixValueBn(2,cy1-cy2+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dy-Index[1]->BestMatch[Index[1]->AdoptedIndex].Dy);
		SolX.ExecuteGaussianElimination();

		double	a=SolX.GetAnswer(1);
		double	b=SolX.GetAnswer(2);
		double	c=cx1+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dx - a*cx1 - b*cy1;
		double	d=cy1+Index[2]->BestMatch[Index[2]->AdoptedIndex].Dy + b*cx1 - a*cy1;

		m[0]=a;
		m[1]=b;
		m[2]=c;
		m[3]=-b;
		m[4]=a;
		m[5]=d;
	}
	else if(Index[0]!=NULL && Index[2]!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Item!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Item!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Adopted==true
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Adopted==true){
		int	cx1,cy1;
		Index[0]->BestMatch[Index[0]->AdoptedIndex].Item->GetCenter(cx1,cy1);
		int	cx2,cy2;
		Index[2]->BestMatch[Index[2]->AdoptedIndex].Item->GetCenter(cx2,cy2);

		/*
			a*x1+b*y1+c=x1+dx1
			a*x2+b*y2+c=x2+dx2

			-b*x1+a*y1+d=y1+dy1
			-b*x2+a*y2+d=y2+dy2

			a*(x1-x2)+b*(y1-y2)=x1-x2+dx1-dx2
			a*(y1-y2)-b*(x1-x2)=y1-y2+dy1-dy2
			*/


		XMultiEquSolve	SolX;
		SolX.AllocateMatrix(2);
		SolX.SetMatrixValue(1,1,cx1-cx2);
		SolX.SetMatrixValue(2,1,cy1-cy2);
		SolX.SetMatrixValue(1,2,cy1-cy2);
		SolX.SetMatrixValue(2,2,-cx1+cx2);
		SolX.SetMatrixValueBn(1,cx1-cx2+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx-Index[2]->BestMatch[Index[2]->AdoptedIndex].Dx);
		SolX.SetMatrixValueBn(2,cy1-cy2+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy-Index[2]->BestMatch[Index[2]->AdoptedIndex].Dy);
		SolX.ExecuteGaussianElimination();

		double	a=SolX.GetAnswer(1);
		double	b=SolX.GetAnswer(2);
		double	c=cx1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx - a*cx1 - b*cy1;
		double	d=cy1+Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy + b*cx1 - a*cy1;

		m[0]=a;
		m[1]=b;
		m[2]=c;
		m[3]=-b;
		m[4]=a;
		m[5]=d;
	}
	else if(Index[0]!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Item!=NULL
	&& Index[0]->BestMatch[Index[0]->AdoptedIndex].Adopted==true){
		m[0]=1;
		m[1]=0;
		m[2]=Index[0]->BestMatch[Index[0]->AdoptedIndex].Dx;
		m[3]=0;
		m[4]=1;
		m[5]=Index[0]->BestMatch[Index[0]->AdoptedIndex].Dy;
	}
	else if(Index[1]!=NULL
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Item!=NULL
	&& Index[1]->BestMatch[Index[1]->AdoptedIndex].Adopted==true){
		m[0]=1;
		m[1]=0;
		m[2]=Index[1]->BestMatch[Index[1]->AdoptedIndex].Dx;
		m[3]=0;
		m[4]=1;
		m[5]=Index[1]->BestMatch[Index[1]->AdoptedIndex].Dy;
	}
	else if(Index[2]!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Item!=NULL
	&& Index[2]->BestMatch[Index[2]->AdoptedIndex].Adopted==true){
		m[0]=1;
		m[1]=0;
		m[2]=Index[2]->BestMatch[Index[2]->AdoptedIndex].Dx;
		m[3]=0;
		m[4]=1;
		m[5]=Index[2]->BestMatch[Index[2]->AdoptedIndex].Dy;
	}
	else{
		m[0]=1;
		m[1]=0;
		m[2]=0;
		m[3]=0;
		m[4]=1;
		m[5]=0;
	}
}

void	IndexForGroup::CalcPosition(int x, int y, int &ResX ,int &ResY)
{
	ResX=x*m[0]+y*m[1]+m[2];
	ResY=x*m[3]+y*m[4]+m[5];
}

void	IndexForGroup::CalcShift(int x, int y, int &ShiftX ,int &ShiftY)
{
	ShiftX=x*m[0]+y*m[1]+m[2] -x;
	ShiftY=x*m[3]+y*m[4]+m[5] -y;
}

double	IndexForGroup::GetRotation(void)
{
	double	A ,B, Tx ,Ty ,S ,R;
	if(GetAffinDecompose(m 
					,A ,B, Tx ,Ty ,S ,R)==true){
		return R;
	}
	return 0.0;
}

