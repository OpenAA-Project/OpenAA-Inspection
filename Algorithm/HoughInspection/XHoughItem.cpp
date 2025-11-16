#include "XHoughInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include <stdio.h>

#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>


const int	HoughAreaMergin	=6;

//==================================================================================================

HoughItem::HoughItem(void)
{
	BMap	=NULL;
	BMapXLen=0;
	BMapYLen=0;
	BMapPointDim		=NULL;
	BMapPointCount		=0;
	BMapPointMaxCount	=0;
	AVector	=NULL;

	SmallAreaDim=NULL;
	SmallAreaXNumb	=0;
	SmallAreaYNumb	=0;

	CosTable	=NULL;
	SinTable	=NULL;
	DivS		=0;

	BitMap	=NULL;
	XLen	=0;
	YLen	=0;
	XByte	=0;
	TmpMap	=NULL;
	Mx=My=0;
	CompressXRate	=0;
}
HoughItem::~HoughItem(void)
{
	ReleaseBuffer();
}

void	HoughItem::ReleaseBuffer(void)
{
	if(BMap!=NULL){
		for(int y=0;y<BMapYLen;y++){
			delete	[]BMap[y];
		}
		delete	[]BMap;
		BMap=NULL;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,BMapYLen);
		TmpMap=NULL;
	}
	BMapXLen=0;
	BMapYLen=0;

	if(SmallAreaDim!=NULL){
		for(int y=0;y<SmallAreaYNumb;y++){
			delete	[]SmallAreaDim[y];
		}
		delete	[]SmallAreaDim;
		SmallAreaDim=NULL;
	}
	delete	[]CosTable;
	delete	[]SinTable;

	if(BitMap!=NULL){
		DeleteMatrixBuff(BitMap,YLen);
		BitMap=NULL;
	}
	if(BMapPointDim!=NULL){
		delete	[]BMapPointDim;
		BMapPointDim=NULL;
	}
	BMapPointCount=0;
	BMapPointMaxCount=0;
}

static	int	MError=0;

ExeResult	HoughItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	if(BMap!=NULL){
		for(int y=0;y<BMapYLen;y++){
			delete	[]BMap[y];
		}
		delete	[]BMap;
		BMap=NULL;
		BMapYLen=0;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,BMapYLen);
		TmpMap=NULL;
	}

	BMapXLen	=GetArea().GetWidth();
	if(BMapXLen>1800){
		BMapXLen=1800;
	}
	CompressXRate	=(double)GetArea().GetWidth()/(double)BMapXLen;

	BMapYLen	=ceil(2.0*hypot(GetArea().GetHeight(),GetArea().GetWidth()));
	//BMapYLen	=GetArea().GetWidth();

	BMap=new uint32 *[BMapYLen];
	for(int y=0;y<BMapYLen;y++){
		BMap[y]=new uint32 [BMapXLen];
	}
	TmpMap	=MakeMatrixBuff((BMapXLen+7)/8,BMapYLen);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}

	if(SmallAreaDim!=NULL){
		for(int y=0;y<SmallAreaYNumb;y++){
			delete	[]SmallAreaDim[y];
		}
		delete	[]SmallAreaDim;
		SmallAreaDim=NULL;
	}
	const HoughThreshold	*RThr=GetThresholdR();
	if(RThr->BinarizedLength==0)
		GetThresholdW()->BinarizedLength=10;
	SmallAreaXNumb = (GetArea().GetWidth()  + RThr->BinarizedLength-1)/RThr->BinarizedLength;
	SmallAreaYNumb = (GetArea().GetHeight() + RThr->BinarizedLength-1)/RThr->BinarizedLength;

	if(SmallAreaXNumb==0)
		SmallAreaXNumb=1;
	if(SmallAreaYNumb==0)
		SmallAreaYNumb=1;

	int	Mergin=(RThr->BinarizedLength-1)/10;
	if(Mergin<=1)
		Mergin=2;
	SmallAreaDim=new FlexArea *[SmallAreaYNumb];
	for(int y=0;y<SmallAreaYNumb;y++){
		SmallAreaDim[y]=new FlexArea[SmallAreaXNumb];
		for(int x=0;x<SmallAreaXNumb;x++){
			(SmallAreaDim[y])[x]=GetArea();
			int	x1=GetArea().GetMinX()+x*RThr->BinarizedLength-1;
			int	y1=GetArea().GetMinY()+y*RThr->BinarizedLength-1;
			int	x2=x1+RThr->BinarizedLength-1;
			int	y2=y1+RThr->BinarizedLength-1;

			(SmallAreaDim[y])[x].ClipArea(x1-Mergin ,y1-Mergin ,x2+Mergin ,y2+Mergin);
		}
	}

	int64	MaxArea=RThr->BinarizedLength*RThr->BinarizedLength;
	int64	MinArea=MaxArea/20;
	for(int y=0;y<SmallAreaYNumb;y++){
		for(int x=0;x<SmallAreaXNumb;x++){
			int64	Dots=(SmallAreaDim[y])[x].GetPatternByte();
			if(Dots<MinArea){
				if(x<(SmallAreaXNumb-1) && (SmallAreaDim[y])[x+1].GetPatternByte()>=MinArea){
					(SmallAreaDim[y])[x+1] += (SmallAreaDim[y])[x];
					(SmallAreaDim[y])[x].Clear();
				}
				else if(0<x && (SmallAreaDim[y])[x-1].GetPatternByte()>=MinArea){
					(SmallAreaDim[y])[x-1] += (SmallAreaDim[y])[x];
					(SmallAreaDim[y])[x].Clear();
				}
				else if(0<y && (SmallAreaDim[y-1])[x].GetPatternByte()>=MinArea){
					(SmallAreaDim[y-1])[x] += (SmallAreaDim[y])[x];
					(SmallAreaDim[y])[x].Clear();
				}
				else if(y<(SmallAreaYNumb-1) && (SmallAreaDim[y+1])[x].GetPatternByte()>=MinArea){
					(SmallAreaDim[y+1])[x] += (SmallAreaDim[y])[x];
					(SmallAreaDim[y])[x].Clear();
				}
				else{
					(SmallAreaDim[y])[x].Clear();
				}
			}
		}
	}

	CosTable=new double[BMapXLen];
	SinTable=new double[BMapXLen];

	for(int x=0;x<BMapXLen;x++){
		double	s=M_PI*(double)x/(double)BMapXLen;
		CosTable[x]=cos(s);
		SinTable[x]=sin(s);
	}
	DivS=M_PI/(double)BMapXLen;

	if(BitMap!=NULL){
		DeleteMatrixBuff(BitMap,YLen);
		BitMap=NULL;
	}
	XLen	=GetArea().GetWidth()+1;
	YLen	=GetArea().GetHeight()+1;
	XByte	=(XLen+7)/8;
	BitMap	=MakeMatrixBuff(XByte,YLen);

	if(BMapPointDim!=NULL){
		delete	[]BMapPointDim;
	}
	BMapPointMaxCount	=RThr->MaxLineCount*10;
	BMapPointDim=new struct BMapPointIndex[BMapPointMaxCount];

	ClearBMap();
	Mx=My=0;
	return _ER_true;
}

void	HoughItem::ClearBMap(void)
{
	for(int y=0;y<BMapYLen;y++){
		for(int x=0;x<BMapXLen;x++){
			BMap[y][x]=0;
		}
	}
	MatrixBuffClear(BitMap,0,XByte,YLen);
	BMapPointCount	=0;
}

ExeResult	HoughItem::ExecuteStartByInspection	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ClearBMap();
	return _ER_true;
}


ExeResult	HoughItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
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
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ImageBuffer	&IBuff=GetTargetBuff();
	short	Error=0;
	Mx=mx;
	My=my;
	ClearBMap();
	const HoughThreshold	*RThr=GetThresholdR();

	if(RThr->DynamicBinarize==false){
		for(int y=0;y<SmallAreaYNumb;y++){
			for(int x=0;x<SmallAreaXNumb;x++){
				MakeBitMap(IBuff  ,mx  ,my
							,(SmallAreaDim[y])[x] ,RThr->PickupL ,RThr->PickupH);
			}
		}
	}
	else{
		int	BTable[256];
		for(int y=0;y<SmallAreaYNumb;y++){
			for(int x=0;x<SmallAreaXNumb;x++){
				memset(BTable,0,sizeof(BTable));
				int	TotalCount=(SmallAreaDim[y])[x].MakeBrightList(BTable,GetDotPerLine(),GetMaxLines(),IBuff,mx,my);
				int	PickupLCount=TotalCount*((double)RThr->PickupL)/10000.0;
				int	PickupHCount=TotalCount*((double)RThr->PickupH)/10000.0;
				int	DL=0;
				int	Lp;
				for(Lp=0;Lp<256;Lp++){
					if((DL+BTable[Lp])>PickupLCount){
						break;
					}
					DL+=BTable[Lp];
				}
				int	DH=0;
				int	Hp;
				for(Hp=255;Hp>=0;Hp--){
					if((DH+BTable[Hp])>PickupHCount){
						break;
					}
					DH+=BTable[Hp];
				}
				MakeBitMapDirect(IBuff  ,mx  ,my
								,(SmallAreaDim[y])[x] ,Lp ,Hp);
			}
		}
	}

	if(RThr->ReducedSize!=0){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BitMap ,XByte ,XLen,YLen ,FPack);
		MatrixBuffClear(BitMap,0,XByte,YLen);

		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetPatternByte()>RThr->ReducedSize){
				f->MakeBitData(BitMap,GetDotPerLine(),GetMaxLines());
			}
		}
	}

	MakeBitCountFromBitMap();
	if(((HoughBase *)GetParentBase())->OutputDebugFile==true){
		SaveBMapImage(GetID());
	}

	PeakPoints.RemoveAll();
	PickupPeaks();

	Res->SetError(1);	//OK

	PeakPointList *p;
	//#pragma omp parallel
	//#pragma omp single private(p)
	for(p=PeakPoints.GetFirst();p!=NULL;p=p->GetNext()){
	//	#pragma omp task
	//	{
			LineWithWidth	ResultLines[100];
			double	AveCont=0;
			int	KNumb=CheckLine(p->x1,p->y1,p->x2,p->y2,ResultLines,AveCont);
			p->PartialCount=0;
			double	MinWidth= 99999999;
			double	MaxWidth=-99999999;
			double	Length=0;
			int		PixelCount=0;
			for(int i=0;i<KNumb;i++){
				MinWidth=min(MinWidth,ResultLines[i].Width);
				MaxWidth=max(MaxWidth,ResultLines[i].Width);
				Length += hypot(ResultLines[i].x2-ResultLines[i].x1 ,ResultLines[i].y2-ResultLines[i].y1);
				PixelCount +=ResultLines[i].PixelCount;
				if(ResultLines[i].Width>=RThr->MinNGWidth && ResultLines[i].Width<=RThr->MaxNGWidth){
					p->PartialCount++;
					ResultLines[i].Effective=true;
				}
				else{
					ResultLines[i].Effective=false;
				}
			}
			p->MinWidthPartially=MinWidth;
			p->MaxWidthPartially=MaxWidth;
			p->Length			=Length;
			p->FoldedCount		=PixelCount;
			p->AveCont			=AveCont;
	
			//if(p->PartialCount>=KNumb*((HoughBase *)GetParentBase())->RangeToFillWidth
			//&& ((double)PixelCount/Length)>=((HoughBase *)GetParentBase())->FillRate
			//&& AveCont>=RThr->MinAverageContinuous){
				ResultPosList	*L=new ResultPosList((p->x2+p->x1)/2,(p->y2+p->y1)/2,Mx,My);
				for(int i=0;i<KNumb;i++){
					TreePointList	*h1=new TreePointList(ResultLines[i].x1,ResultLines[i].y1);
					TreePointList	*h2=new TreePointList(ResultLines[i].x2,ResultLines[i].y2);
					if(ResultLines[i].Effective==true)
						h1->SetLevel(255);
					else
						h1->SetLevel(60);
					L->Vector.AppendList(h1);
					h2->SetLevel(0);
					L->Vector.AppendList(h2);
				}
				L->result=0x10001;
				L->NGSize=PixelCount;
				L->SetResult1(Length);
				L->SetResult2(p->Width);
				#pragma omp critical
				{
					Res->AddPosList(L);
					Res->SetError(2);
				}
			//}
		}
	//}

	return _ER_true;
}

void	HoughItem::MakeBitMap(ImageBuffer &Buff ,int mx ,int my,FlexArea &RectArea ,int PickupL ,int PickupH)
{
	const HoughThreshold	*RThr=GetThresholdR();
	int	N=RectArea.GetFLineLen();
	HoughInLayer	*P=(HoughInLayer *)GetParentInLayer();
	int	DotCount=0;
	double	AddedC=0;
	#pragma omp parallel                          
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			int	X1=RectArea.GetFLineLeftX(i)+mx;
			int	Y=RectArea.GetFLineAbsY(i)	+my;
			int	Numb=RectArea.GetFLineNumb(i);
			if(Y<0 || Y>=GetMaxLines()){
				continue;
			}
			if(X1>=GetDotPerLine())
				continue;
			if(X1<0){
				Numb+=X1;
				X1=0;
			}
			if(X1+Numb>=GetDotPerLine()){
				Numb=GetDotPerLine()-X1;
			}
			if(Numb<0)
				continue;
			BYTE	*s=Buff.GetY(Y);
			int	AddedCX=0;

			if(P->DynamicMaskMap!=NULL && RThr->RemoveDynamicMask==true){
				for(int j=0;j<Numb;j++){
					int	x=X1+j;
					if(GetBmpBitOnY(P->DynamicMaskMap[Y],x)==0){
						AddedCX+=s[x];
						#pragma omp atomic
						DotCount++;
					}
				}
			}
			else{
				for(int j=0;j<Numb;j++){
					int	x=X1+j;
					AddedCX+=s[x];
				}
				#pragma omp atomic
				DotCount+=Numb;
			}
			#pragma omp atomic
			AddedC+=AddedCX;
		}
	}
	if(DotCount==0)
		return;

	double	Avr=AddedC/(double)DotCount;
	int	MinC=Avr-PickupL;
	int	MaxC=Avr+PickupH;
	MakeBitMapDirect(Buff ,mx ,my,RectArea ,MinC ,MaxC);
}

void	HoughItem::MakeBitMapDirect(ImageBuffer &Buff ,int mx ,int my,FlexArea &RectArea ,int MinC ,int MaxC)
{
	const HoughThreshold	*RThr=GetThresholdR();
	int	N=RectArea.GetFLineLen();
	HoughInLayer	*P=(HoughInLayer *)GetParentInLayer();

	#pragma omp parallel                          
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			int	mX1=RectArea.GetFLineLeftX(i);
			int	mY1=RectArea.GetFLineAbsY(i);
			int	mNumb=RectArea.GetFLineNumb(i);

			int	X1=mX1+mx;
			int	Y =mY1+my;
			int	Numb=mNumb;
			if(Y<0 || Y>=GetMaxLines()){
				continue;
			}
			if(X1>=GetDotPerLine())
				continue;
			if(X1<0){
				Numb+=X1;
				mX1-=X1;
				mNumb+=X1;
				X1=0;
			}
			if(X1+Numb>=GetDotPerLine()){
				Numb=GetDotPerLine()-X1;
			}
			if(Numb<0)
				continue;
			BYTE	*s=Buff.GetY(Y);
			int	AddedCX=0;

			mX1	-=GetArea().GetMinX();
			mY1	-=GetArea().GetMinY();
			if(P->DynamicMaskMap!=NULL && RThr->RemoveDynamicMask==true){
				for(int j=0;j<Numb;j++){
					int	x=X1+j;
					int	c=s[x];
					if((c<MinC || MaxC<c) && GetBmpBitOnY(P->DynamicMaskMap[Y],x)==0){
						int	h=mX1+j;
						BYTE	*U=BitMap[mY1] + (h>>3);
						BYTE	Mask=0x80>>(h&7);
						#pragma omp atomic
						*U |= Mask;
					}
				}
			}
			else{
				for(int j=0;j<Numb;j++){
					int	c=s[X1+j];
					if(c<MinC || MaxC<c){
						int	h=mX1+j;
						BYTE	*U=BitMap[mY1] + (h>>3);
						BYTE	Mask=0x80>>(h&7);
						#pragma omp atomic
						*U |= Mask;
						/*
						#pragma omp critical
						{
							SetBmpBitOnY1(BitMap[mY1],mX1+j);
						}
						*/
					}
				}
			}
		}
	}
}
void	HoughItem::MakeBitCountFromBitMap(void)
{
	double	BMapYLen2=BMapYLen/2.0;

	#pragma omp parallel                          
	{                                                
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*s=BitMap[y];
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(s,x)!=0){
					for(int s=0;s<BMapXLen;s++){
						double	k=x*SinTable[s]+y*CosTable[s];
						k+=BMapYLen2;
						int	ki=k;
						if(0<=ki && ki<BMapYLen){
							#pragma omp atomic
							(BMap[ki])[s]++;
						}
					}
				}
			}
		}
	}		
}

void	HoughItem::SaveBMapImage(int ID)
{
	QImage	TmpImage(BMapXLen,BMapYLen,QImage::Format_RGB32);
	for(int y=0;y<BMapYLen;y++){
		for(int x=0;x<BMapXLen;x++){
			int	c=BMap[y][x];
			if(c>255)
				c=255;
			QRgb	col=qRgb(c,c,c);
			TmpImage.setPixel(x,y,col);
		}
	}
	QString	FileName=QString("LineBMap")+QString::number(ID)+QString(".png");
	TmpImage.save(FileName,"PNG");
}

static	int	Sep=4;

static	int	BMapPointIndexFunc(const void *a ,const void *b)
{
	struct BMapPointIndex	*pa=(struct BMapPointIndex *)a;
	struct BMapPointIndex	*pb=(struct BMapPointIndex *)b;
	return pb->Count - pa->Count;
}

void	HoughItem::PickupPeaks(void)
{
	const HoughThreshold	*RThr=GetThresholdR();
	int	ZoneWidth2=(RThr->ZoneWidth+1)/2;
	//int	ZoneWidth2=RThr->ZoneWidth;

	int	YNumb=BMapYLen-ZoneWidth2-ZoneWidth2;
	#pragma omp parallel                          
	{                                                
		#pragma omp for
		for(int i=0;i<YNumb;i++){
			int	y=i+ZoneWidth2;
		//for(int y=ZoneWidth2;y<BMapYLen-ZoneWidth2;y++){
			for(int x=0;x<BMapXLen;x++){
				uint	Count=GatherCount(x ,y);
				if(Count>=RThr->MinPixels){
					#pragma omp critical
					{
						if(BMapPointCount<BMapPointMaxCount){
							BMapPointDim[BMapPointCount].XPos=x;
							BMapPointDim[BMapPointCount].YPos=y;
							BMapPointDim[BMapPointCount].Count=Count;
							BMapPointCount++;
						}
					}
				}
			}
		}
	}
	QSort(BMapPointDim,BMapPointCount,sizeof(struct BMapPointIndex),BMapPointIndexFunc);

	if(((HoughBase *)GetParentBase())->ModeThread==true && BMapPointCount>=2){
		#pragma omp parallel                          
		{                                                
			#pragma omp for
			for(int i=0;i<BMapPointCount;i++){
				PickupLine(BMapPointDim[i].XPos,BMapPointDim[i].YPos-BMapYLen/2);
			}
		}
	}
	else{
		for(int i=0;i<BMapPointCount;i++){
			PickupLine(BMapPointDim[i].XPos,BMapPointDim[i].YPos-BMapYLen/2);
		}
	}
	return;



	MatrixBuffClear(TmpMap,0,(BMapXLen+7)/8,BMapYLen);

	XYClassContainer	MaxPoints;
	for(int n=0;n<RThr->MaxLineCount;n++){
		int	MaxD=0;
		int	MaxX=0;
		int	MaxY=0;
		for(int y=ZoneWidth2;y<BMapYLen-ZoneWidth2;y++){
			for(int x=ZoneWidth2;x<BMapXLen-ZoneWidth2;x++){
				uint32	c=BMap[y][x];
				if(MaxD<c){
					MaxD=c;
					MaxX=x;
					MaxY=y;
				}
			}
		}
		uint	Count=GatherCount(MaxX ,MaxY);

		if(Count<RThr->MinPixels){
			break;
		}

		//Continuous points are combined to this max point
		XYClassContainer	ClosedPoints;
		ClosedPoints.Add(MaxX,MaxY);
		int ReEntrantCount=0;
		SearchAddPoints(ClosedPoints,MaxX,MaxY,ReEntrantCount,Count*((HoughBase *)GetParentBase())->SearchNeighborRate);

		uint	AtreaCount=0;
		for(XYClass *r=ClosedPoints.GetFirst();r!=NULL;r=r->GetNext()){
			for(int y=-(Sep-1);y<=(Sep-1);y++){
				for(int x=-(Sep-1);x<=(Sep-1);x++){
					int	X=r->x+x;
					int	Y=r->y+y;
					if(0<=X && X<BMapXLen && 0<=Y && Y<BMapYLen){
						AtreaCount+=BMap[Y][X];
						BMap[Y][X]=0;
						SetBmpBit0(TmpMap,X,Y);
					}
					else{
						MError++;
					}
				}
			}
		}
		MaxPoints.Add(MaxX,MaxY);
	}

	int	LineCount=0;
	int	PNumb=0;
	XYClass		*XYDim=new XYClass[MaxPoints.GetCount()];
	for(XYClass *r=MaxPoints.GetFirst();r!=NULL;r=r->GetNext()){
		XYDim[PNumb].x=r->x;
		XYDim[PNumb].y=r->y;
		PNumb++;
	}
	if(((HoughBase *)GetParentBase())->ModeThread==true && PNumb>=2){
		#pragma omp parallel                          
		{                                                
			#pragma omp for
			for(int i=0;i<PNumb;i++){
				PickupLine(XYDim[i].x,XYDim[i].y-BMapYLen/2);
			}
		}
	}
	else{
		for(int i=0;i<PNumb;i++){
			PickupLine(XYDim[i].x,XYDim[i].y-BMapYLen/2);
		}
	}
	delete	[]XYDim;
}

uint	HoughItem::GatherCount(int x ,int y)
{
	const HoughThreshold	*RThr=GetThresholdR();
	uint	Count=0;
	int	ZoneWidthX=ceil((RThr->ZoneWidth+1)/2.0/CompressXRate);
	int	ZoneWidthY=(RThr->ZoneWidth+1)/2;


	int	StartX=x-ZoneWidthX;
	if(StartX<0)
		StartX=0;
	int	EndX=x+ZoneWidthX;
	if(EndX>BMapXLen)
		EndX=BMapXLen;

	int	StartY=y-ZoneWidthY;
	if(StartY<0)
		StartY=0;
	int	EndY=y+ZoneWidthY;
	if(EndY>BMapYLen)
		EndY=BMapYLen;

	for(int ty=StartY;ty<EndY;ty++){
		uint32	*d=BMap[ty];
		for(int tx=StartX;tx<EndX;tx++){
			Count+=d[tx];
			//d[tx]=0;
		}
	}
	return Count;
}

#define	MaxReEntrant	2000

void	HoughItem::SearchAddPoints(XYClassContainer &ClosedPoints ,int x,int y ,int &ReEntrantCount ,int ThresholdCount)
{
	if(ReEntrantCount>=MaxReEntrant)
		return;
	bool	P[8];
	P[0]=false;
	P[1]=false;
	P[2]=false;
	P[3]=false;
	P[4]=false;
	P[5]=false;
	P[6]=false;
	P[7]=false;

	#pragma omp parallel
	#pragma omp sections
	{                                                
		#pragma omp section
		{
			if(0<=(x-Sep) && 0<=(y-Sep) && GetBmpBit(TmpMap,x-Sep,y-Sep)==0){
				if(GatherCount(x-Sep,y-Sep)>=ThresholdCount){
					P[0]=true;
				}
			}
		}
		#pragma omp section
		{
			if(0<=x && x<BMapXLen && 0<=(y-Sep) && GetBmpBit(TmpMap,x,y-Sep)==0){
				if(GatherCount(x,y-Sep)>=ThresholdCount){
					P[1]=true;
				}
			}
		}
		#pragma omp section
		{
			if((x+Sep)<BMapXLen && 0<=(y-Sep) && GetBmpBit(TmpMap,x+Sep,y-Sep)==0){
				if(GatherCount(x+Sep,y-Sep)>=ThresholdCount){
					P[2]=true;
				}
			}
		}
		#pragma omp section
		{
			if(0<=(x-Sep) && 0<=y && y<BMapYLen && GetBmpBit(TmpMap,x-Sep,y)==0){
				if(GatherCount(x-Sep,y)>=ThresholdCount){
					P[3]=true;
				}
			}
		}
		#pragma omp section
		{
			if((x+Sep)<BMapXLen && 0<=y && y<BMapYLen && GetBmpBit(TmpMap,x+Sep,y)==0){
				if(GatherCount(x+Sep,y)>=ThresholdCount){
					P[4]=true;
				}
			}
		}
		#pragma omp section
		{
			if(0<=(x-Sep) && (y+Sep)<BMapYLen && GetBmpBit(TmpMap,x-Sep,y+Sep)==0){
				if(GatherCount(x-Sep,y+Sep)>=ThresholdCount){
					P[5]=true;
				}
			}
		}
		#pragma omp section
		{
			if(0<=x && x<BMapXLen && (y+Sep)<BMapYLen && GetBmpBit(TmpMap,x,y+Sep)==0){
				if(GatherCount(x,y+Sep)>=ThresholdCount){
					P[6]=true;
				}
			}
		}
		#pragma omp section
		{
			if((x+Sep)<BMapXLen && (y+Sep)<BMapYLen && GetBmpBit(TmpMap,x+Sep,y+Sep)==0){
				if(GatherCount(x+Sep,y+Sep)>=ThresholdCount){
					P[7]=true;
				}
			}
		}
	}

	if(P[0]==true){
		ClosedPoints.Add(x-Sep,y-Sep);
		SetBmpBit1(TmpMap,x-Sep,y-Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x-Sep,y-Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[1]==true){
		ClosedPoints.Add(x,y-Sep);
		SetBmpBit1(TmpMap,x,y-Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x,y-Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[2]==true){
		ClosedPoints.Add(x+Sep,y-Sep);
		SetBmpBit1(TmpMap,x+Sep,y-Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x+Sep,y-Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[3]==true){
		ClosedPoints.Add(x-Sep,y);
		SetBmpBit1(TmpMap,x-Sep,y);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x-Sep,y,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[4]==true){
		ClosedPoints.Add(x+Sep,y);
		SetBmpBit1(TmpMap,x+Sep,y);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x+Sep,y,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[5]==true){
		ClosedPoints.Add(x-Sep,y+Sep);
		SetBmpBit1(TmpMap,x-Sep,y+Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x-Sep,y+Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[6]==true){
		ClosedPoints.Add(x,y+Sep);
		SetBmpBit1(TmpMap,x,y+Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x,y+Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
	if(P[7]==true){
		ClosedPoints.Add(x+Sep,y+Sep);
		SetBmpBit1(TmpMap,x+Sep,y+Sep);
		ReEntrantCount++;
		SearchAddPoints(ClosedPoints ,x+Sep,y+Sep,ReEntrantCount,ThresholdCount);
		ReEntrantCount--;
	}
}

bool    GetLPointFoot(double a ,double b ,double p	//a*x+b*y=p
			,int px ,int py ,double &X ,double &Y)
{
	double  T = a*a + b*b;
	if(T==0){
		return false;
	}
	double	k=b*px-a*py;
	X=(a*p+b*k)/T;
	Y=(b*p-a*k)/T;
	return true ;
}

struct	LengthWidth
{
	double	LPoint;
	double	W;
};

static	int	SortDoubleFunc(const void *a ,const void *b)
{
	struct	LengthWidth	*ad=(struct	LengthWidth *)a;
	struct	LengthWidth	*bd=(struct	LengthWidth *)b;
	if(ad->LPoint<bd->LPoint)
		return -1;
	if(ad->LPoint>bd->LPoint)
		return 1;
	return 0;
}

bool	HoughItem::PickupLine(int s ,int p)
{
	const HoughThreshold	*RThr=GetThresholdR();
	if(PeakPoints.GetCount()>=RThr->MaxLineCount){
		return false;
	}
	double	a=SinTable[s];
	double	b=CosTable[s];
	double	ZoneWidth2=RThr->ZoneWidth/2.0;

	int	Y0,Y1;
	int	X0,X1;
	if(fabs(b)>=0.00001){
		Y0=p/b;
		Y1=(p-a*XLen)/b;
	}
	else{
		Y0=0;
		Y1=YLen;
	}
	if(fabs(a)>=0.00001){
		X0=p/a;
		X1=(p-b*YLen)/a;
	}
	else{
		X0=0;
		X1=XLen;
	}
	if(X0>X1)
		swap(X0,X1);
	if(Y0>Y1)
		swap(Y0,Y1);

	if(X0<0)
		X0=0;
	if(X1>=XLen)
		X1=XLen-1;
	if(Y0<0)
		Y0=0;
	if(Y1>=YLen)
		Y1=YLen-1;

	double	Cx,Cy;

	if(fabs(a)>0.0001){
		Cx=p/a;
		Cy=0;
	}
	else{
		Cx=0;
		Cy=p/b;
	}

	int	N=0;
	int	MaxCount=(XLen+YLen)*RThr->ZoneWidth;
	struct	LengthWidth	*DTable=new struct	LengthWidth[MaxCount];
	for(int y=Y0;y<=Y1;y++){
		BYTE	*s=BitMap[y];
		for(int x=X0;x<=X1;x++){
			if(GetBmpBitOnY(s,x)!=0){
				double	L=fabs(a*x+b*y-p);
				if(L<=ZoneWidth2){
					double	X,Y;
					GetLPointFoot(a,b,p,x,y,X,Y);
					double	t=hypot(X-Cx,Y-Cy);
					if(N<MaxCount){
						DTable[N].LPoint=t;
						DTable[N].W		=L;
						N++;
					}
				}
			}
		}
	}
	QSort(DTable,N,sizeof(struct LengthWidth),SortDoubleFunc);
	
	for(int i=0;i<N;){
		double	TopD=DTable[i].LPoint;
		double	LastD=TopD;
		int	LCount=1;
		double	MaxWidth=0;
		for(;i<N;i++){
			if(DTable[i].LPoint-LastD>RThr->MaxIsolation)
				break;
			LastD=DTable[i].LPoint;
			MaxWidth=max(MaxWidth,DTable[i].W);
			LCount++;
		}
		MaxWidth*=2;
		if(LCount>=RThr->MinPixels && (LastD-TopD)>=RThr->NGLength 
		&& RThr->MinNGWidth<=MaxWidth && MaxWidth<=RThr->MaxNGWidth){
			PeakPointList	*m=new PeakPointList();
			m->Count=LCount;
			m->x1=-b*TopD+Cx+ GetArea().GetMinX();
			m->y1=a*TopD+Cy	+ GetArea().GetMinY();
			m->x2=-b*LastD+Cx+ GetArea().GetMinX();
			m->y2=a*LastD+Cy+ GetArea().GetMinY();
			m->Width=MaxWidth;
			ProcessMutex.lock();
			PeakPoints.AppendList(m);
			int	Numb=PeakPoints.GetCount();
			ProcessMutex.unlock();
			if(Numb>=RThr->MaxLineCount){
				delete	[]DTable;
				return false;
			}
		}
	}
	delete	[]DTable;
	return true;
}

int	HoughItem::CheckLine(int x1, int y1, int x2 ,int y2 ,LineWithWidth ResultLines[100] ,double &AveCont)
{
	int		ResultLineCount=0;
	int		DivCount=((HoughBase *)GetParentBase())->DefaultDivCount;
	double	L=hypot(x2-x1,y2-y1);
	double	Ld=L/DivCount;
	const HoughThreshold	*RThr=GetThresholdR();
	if(Ld<RThr->ZoneWidth*2){
		DivCount=ceil(L/(RThr->ZoneWidth*2));
		Ld=L/DivCount;
	}
	int		MaxDimCount=100000;
	XYData	*XYDim=new XYData[MaxDimCount];
	
	double	Dx=(x2-x1)/L;
	double	Dy=(y2-y1)/L;
	double	s1=GetSita(Dx,Dy);
	double	ZoneWidth2=RThr->ZoneWidth/2.0;
	double	Vx=-ZoneWidth2*Dy;
	double	Vy= ZoneWidth2*Dx;

	bool	LastExist=false;
	int		NCount=0;
	int		LineClusterCount[100000];

	LineClusterCount[0]=0;
	for(int i=0;i<DivCount;i++){
		double	X1=x1+Ld*Dx*i;
		double	Y1=y1+Ld*Dy*i;
		double	X2=x1+Ld*Dx*(i+1);
		double	Y2=y1+Ld*Dy*(i+1);
		int		XYDimCount=0;

		int	mx1=X1+Vx;
		int	my1=Y1+Vy;
		int	mx2=X2+Vx;
		int	my2=Y2+Vy;
		int	mx3=X2-Vx;
		int	my3=Y2-Vy;
		int	mx4=X1-Vx;
		int	my4=Y1-Vy;

		int	TopY	=min(min(my1,my2),min(my3,my4));
		int	BottomY	=max(max(my1,my2),max(my3,my4));

		double	RXX=0;
		double	RX=0;
		double	RYY=0;
		double	RY=0;
		double	RXY=0;
		int		Numb=0;

		for(int y=TopY;y<=BottomY;y++){
			if(y<0 || GetMaxLines()<=y)
				continue;
			int	qy=y   -GetArea().GetMinY();
			if(qy<0 || YLen<=qy)
				continue;
			double	X[4];
			int		N=0;
			if(::GetCrossHalfInnerPoint((double)mx1,(double)my1,(double)mx2,(double)my2,(double)y ,X[N])==true)
				N++;
			if(::GetCrossHalfInnerPoint((double)mx2,(double)my2,(double)mx3,(double)my3,(double)y ,X[N])==true)
				N++;
			if(::GetCrossHalfInnerPoint((double)mx3,(double)my3,(double)mx4,(double)my4,(double)y ,X[N])==true)
				N++;
			if(::GetCrossHalfInnerPoint((double)mx4,(double)my4,(double)mx1,(double)my1,(double)y ,X[N])==true)
				N++;

			int	qx1=0,qx2=0;
			if(N==1){
				qx1=X[0]-GetArea().GetMinX();
				qx2=qx1;
			}
			else if(N==2){
				qx1=min(X[0],X[1])-GetArea().GetMinX();
				qx2=max(X[0],X[1])-GetArea().GetMinX();
			}
			else if(N==3){
				qx1=min(min(X[0],X[1]),X[2])-GetArea().GetMinX();
				qx2=max(max(X[0],X[1]),X[2])-GetArea().GetMinX();
			}
			else if(N==4){
				qx1=min(min(X[0],X[1]),min(X[2],X[3]))-GetArea().GetMinX();
				qx2=max(max(X[0],X[1]),max(X[2],X[3]))-GetArea().GetMinX();
			}
			BYTE	*s=BitMap[qy];
			qx1=max(qx1,0);
			qx2=min(qx2,XLen-1);
			int	numb=0;
			for(int x=qx1;x<=qx2;x++){
				if(GetBmpBitOnY(s,x)!=0){
					numb++;
					RXX+=x*x;
					RX +=x;
					RXY+=x*qy;
					if(XYDimCount<MaxDimCount){
						XYDim[XYDimCount].x=x;
						XYDim[XYDimCount].y=qy;
						XYDimCount++;
					}
				}
			}
			RYY+=numb*qy*qy;
			RY +=numb*qy;
			Numb+=numb;
		}
		if(Numb!=0){
			double	A=RXX-RX*RX/Numb;
			double	B=RXY-RX*RY/Numb;
			double	C=B;
			double	D=RYY-RY*RY/Numb;

			double	Ta=A*A+B*B;
			double	Tb=C*C+D*D;
			double	a1,b1,c1;
			double	a2,b2,c2;
			if(Ta>=Tb){
				Ta=sqrt(Ta);
				b1=A/Ta;
				a1=-B/A*b1;
				c1=-(a1*RX+b1*RY)/Numb;
				b2=-b1;
				a2=-a1;
				c2=-(a2*RX+b2*RY)/Numb;
			}
			else{
				Tb=sqrt(Tb);
				b1=C/Tb;
				a1=-D/C*b1;
				c1=-(a1*RX+b1*RY)/Numb;
				b2=-b1;
				a2=-a1;
				c2=-(a2*RX+b2*RY)/Numb;
			}

			double	s2=GetSita(-b1,a1);
			double	s3=GetSita(-b2,a2);
			double	ds1=DiffSita(s1,s2);
			double	ds2=DiffSita(s1,s3);
			double	a,b,c;
			if(ds1<ds2){
				a=a1;
				b=b1;
				c=c1;
			}
			else{
				a=a2;
				b=b2;
				c=c2;
			}
			double	Kx,Ky;
			if(b!=0.0){
				Kx=100000000.0;
				Ky=(-a*Kx-c)/b;
			}
			else{
				Ky=100000000.0;
				Kx=(-b*Ky-c)/a;
			}
			double	MinM= 999999999999.0;
			double	MaxM=-999999999999.0;
			double	MaxWidth=0;
			for(int j=0;j<XYDimCount;j++){
				double	M=hypot(Kx-XYDim[j].x,Ky-XYDim[j].y);
				MinM=min(M,MinM);
				MaxM=max(M,MaxM);
				double	W=fabs(a*XYDim[j].x+b*XYDim[j].y+c);
				MaxWidth=max(MaxWidth,W);
			}
			int	tx1,ty1,tx2,ty2;

			if(Kx>100000 && b<0){ 
				tx1=Kx+MinM*b;
				ty1=Ky-MinM*a;
				tx2=Kx+MaxM*b;
				ty2=Ky-MaxM*a;
			}
			else{
				tx1=Kx-MinM*b;
				ty1=Ky+MinM*a;
				tx2=Kx-MaxM*b;
				ty2=Ky+MaxM*a;
			}
			GetClusterCount(tx1,ty1,tx2,ty2 ,XYDim ,XYDimCount
										,LastExist ,NCount
										,LineClusterCount);


			ResultLines[ResultLineCount].x1=tx1+GetArea().GetMinX();
			ResultLines[ResultLineCount].y1=ty1+GetArea().GetMinY();
			ResultLines[ResultLineCount].x2=tx2+GetArea().GetMinX();
			ResultLines[ResultLineCount].y2=ty2+GetArea().GetMinY();

			ResultLines[ResultLineCount].PixelCount	=Numb;
			ResultLines[ResultLineCount].Width		=MaxWidth*2;
			ResultLineCount++;
		}
	}

	int	AddCont=0;
	for(int k=0;k<NCount;k++){
		AddCont += LineClusterCount[k];
	}
	AveCont=(double)AddCont/(double)NCount;
		
	delete	[]XYDim;
	return ResultLineCount;
}
int		HoughItem::GetClusterCount(int x1,int y1,int x2,int y2 ,XYData *XYDim ,int XYDimCount
										,bool &LastExist ,int &NCount
										,int LineClusterCount[])
{
	int	dx=x2-x1;
	int	dy=y2-y1;

	if(dx>=0 && dx>=dy){
		for(int n=0;n<dx;n++){
			int	X=x1+n;
			int	Y=y1+dy*n/dx;
			if(Exist(XYDim,XYDimCount,X,Y)==true){
				LineClusterCount[NCount]++;
				LastExist=true;
			}
			else{
				if(LastExist==true){
					NCount++;
					LineClusterCount[NCount]=0;
				}
				LastExist=false;
			}
		}
	}
	else if(dx<0 && (-dx)>dy){
		for(int n=0;n<(-dx);n++){
			int	X=x1-n;
			int	Y=y1-dy*n/dx;
			if(Exist(XYDim,XYDimCount,X,Y)==true){
				LineClusterCount[NCount]++;
				LastExist=true;
			}
			else{
				if(LastExist==true){
					NCount++;
					LineClusterCount[NCount]=0;
				}
				LastExist=false;
			}
		}
	}
	else if(dy>=0 && dy>=dx){
		for(int n=0;n<dy;n++){
			int	Y=y1+n;
			int	X=x1+dx*n/dy;
			if(Exist(XYDim,XYDimCount,X,Y)==true){
				LineClusterCount[NCount]++;
				LastExist=true;
			}
			else{
				if(LastExist==true){
					NCount++;
					LineClusterCount[NCount]=0;
				}
				LastExist=false;
			}
		}
	}
	else{
		for(int n=0;n<(-dy);n++){
			int	Y=y1-n;
			int	X=x1-dx*n/dy;
			if(Exist(XYDim,XYDimCount,X,Y)==true){
				LineClusterCount[NCount]++;
				LastExist=true;
			}
			else{
				if(LastExist==true){
					NCount++;
					LineClusterCount[NCount]=0;
				}
				LastExist=false;
			}
		}
	}

	return NCount;	
}

bool	HoughItem::Exist(XYData *XYDim ,int XYDimCount,int X,int Y)
{
	for(int i=0;i<XYDimCount;i++){
		if(XYDim[i].x==X && XYDim[i].y==Y)
			return true;
	}
	return false;
}

void	HoughItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	HoughDrawAttr	*HAttr=dynamic_cast<HoughDrawAttr *>(Attr);
	if(HAttr!=NULL){
		if(HAttr->DMode==HoughDrawAttr::__Mode_PickupArea){
			QColor	Col(0,255,0,120);
			DrawBitImage(pnt, (const BYTE **)BitMap ,XLen,XByte ,YLen
					,movx ,movy ,ZoomRate
					,-GetArea().GetMinX()-Mx,-GetArea().GetMinY()-My
					,Col);
		}
		else if(HAttr->DMode==HoughDrawAttr::__Mode_ItemArea){
			AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
}
void	HoughItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	Col(0,0,255,255);
	
	AlgorithmItemPLI::DrawResultItem(Res,IData ,PData ,MovX+Mx ,MovY+My ,ZoomRate,OnlyNG);

	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){	
		PData.setPen(Col);
		for(PeakPointList *p=PeakPoints.GetFirst();p!=NULL;p=p->GetNext()){
			PData.drawLine((p->x1+MovX+Mx)*ZoomRate,(p->y1+MovY+My)*ZoomRate
						 , (p->x2+MovX+Mx)*ZoomRate,(p->y2+MovY+My)*ZoomRate);
			QRect	rect(0,0,IData.width(),IData.height());
			int	kx=(p->x1+MovX+Mx)*ZoomRate;
			int	ky=(p->y1+MovY+My)*ZoomRate;
			PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);

			//double	Len=hypot(p->x2-p->x1,p->y2-p->y1);
			double	Len=p->Length;

			PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Pixel(")+QString::number((int)p->Count) + QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnitSquare(GetPage(),p->Count),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm2")
						,&rect);
			PData.drawText(kx,ky+16*2,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Folded Pixel(")+QString::number((int)p->FoldedCount) + QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnitSquare(GetPage(),p->FoldedCount),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm2")
						,&rect);
			PData.drawText(kx,ky+16*3,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Len(")+QString::number(Len,'f',2) +QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnit(GetPage(),Len),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm")
						,&rect);
			PData.drawText(kx,ky+16*4,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Minimum Width(")+QString::number(p->MinWidthPartially,'f',2) +QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnit(GetPage(),p->MinWidthPartially),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm")
						,&rect);
			PData.drawText(kx,ky+16*5,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Maximum Width(")+QString::number(p->MaxWidthPartially,'f',2) +QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnit(GetPage(),p->MaxWidthPartially),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm")
						,&rect);
			PData.drawText(kx,ky+16*6,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"AveCont(")+QString::number(p->AveCont,'f',2) +QString(/**/") ")
						+QString::number(GetParamGlobal()->TransformPixelToUnit(GetPage(),Len),'f',GetParamGlobal()->SmallNumberFigure)
						+QString(/**/"mm")
						,&rect);
		}
	}
}


void	HoughItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOneHough){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			HoughInLayer	*Ly=dynamic_cast<HoughInLayer *>(GetParentInLayer());
			UndoElement<HoughInLayer>	*UPointer=new UndoElement<HoughInLayer>(Ly,&HoughInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			HoughItem *src=(HoughItem *)Data;
			SetItemName(src->GetItemName());
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_AllHough){
		if(GetLibID()==((HoughItem *)Data)->GetLibID()){
			HoughInLayer	*Ly=dynamic_cast<HoughInLayer *>(GetParentInLayer());
			UndoElement<HoughInLayer>	*UPointer=new UndoElement<HoughInLayer>(Ly,&HoughInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			HoughItem *src=(HoughItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}

}
void	HoughItem::CopyThresholdOnly(HoughItem &src)
{
	GetThresholdW()->CopyFrom(*((HoughThreshold *)src.GetThresholdR()));
}

