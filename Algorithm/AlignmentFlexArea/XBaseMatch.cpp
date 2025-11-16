//#include "XAlignmentFlexAreaResource.h"
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

BaseMatch::SImage::SImage(int n ,BaseMatch *p)
	:ParentBaseMatch(p),SImageNo(n)
{
	Angle=0;
}
BaseMatch::SImage::~SImage(void)
{
}

void	BaseMatch::SImage::Release(void)
{
}
bool	BaseMatch::SImage::ExecuteInitialAfterEdit1(double angle ,BYTE **RootBuff,ExecuteInitialAfterEditInfo &EInfo)
{
	Angle	=angle;
	int	XLen=ParentBaseMatch->SDotPerLine;
	int	XByte	=(XLen+7)/8;
	int	YLen	=ParentBaseMatch->SMaxLines;

	BYTE    **DBuff=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(DBuff ,0 ,XByte ,YLen);

	double	CosS=cos(angle);
	double	SinS=sin(angle);
	int	Cx=ParentBaseMatch->SDotPerLine/2;
	int	Cy=ParentBaseMatch->SMaxLines/2;

	#pragma omp parallel
	{
		#pragma omp for	
		for(int y=0;y<YLen;y++){
			BYTE	*d=DBuff[y];
			for(int x=0;x<XLen;x++){
				int	X=(x-Cx)*CosS-(y-Cy)*SinS+Cx;
				int	Y=(x-Cx)*SinS+(y-Cy)*CosS+Cy;

				if(X<0 || XLen<=X
				|| Y<0 || YLen<=Y)
					continue;
				if(GetBmpBit(RootBuff,X,Y)!=0){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
	ThinArea(DBuff
				,NULL
				,XByte ,YLen);

	PureFlexAreaListContainer	hArea;
	PickupFlexArea(DBuff ,XByte ,XLen,YLen ,hArea);

	DeleteMatrixBuff(DBuff,YLen);

	int	Count=hArea.GetCount();
	int	Sep=Count/ParentBaseMatch->ABase->BaseMatchSep;
	if(Sep==0)
		Sep=1;
	if((Count/Sep)>100)
		Sep=Count/100;
	int	R=0;

	int	MMinX=99999999;
	int	MMinY=99999999;
	int	MMaxX=-99999999;
	int	MMaxY=-99999999;
	for(PureFlexAreaList *f=hArea.GetFirst();f!=NULL;f=f->GetNext(),R++){
		int	x1,y1,x2,y2;
		f->GetXY(x1,y1,x2,y2);
		MMinX=min(x1,MMinX);
		MMinY=min(y1,MMinY);
		MMaxX=max(x2,MMaxX);
		MMaxY=max(y2,MMaxY);
	}
	int	CenterX=(MMinX+MMaxX)/2;
	int	CenterY=(MMinY+MMaxY)/2;

	MLeftTop.SPointNumb=0;
	for(PureFlexAreaList *f=hArea.GetFirst();f!=NULL;f=f->GetNext(),R++){
		if((R%Sep)==0){
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			if(Cx<CenterX && Cy<CenterY){
				if(f->IsInclude(Cx,Cy)==true){
					MLeftTop.SPoint[MLeftTop.SPointNumb][0]=Cx;
					MLeftTop.SPoint[MLeftTop.SPointNumb][1]=Cy;
					MLeftTop.SPointNumb++;
					if(MLeftTop.SPointNumb>=MaxSPointNumb){
						break;
					}
				}
			}
		}
	}
	MRightTop.SPointNumb=0;
	for(PureFlexAreaList *f=hArea.GetFirst();f!=NULL;f=f->GetNext(),R++){
		if((R%Sep)==0){
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			if(CenterX<=Cx && Cy<CenterY){
				if(f->IsInclude(Cx,Cy)==true){
					MRightTop.SPoint[MRightTop.SPointNumb][0]=Cx;
					MRightTop.SPoint[MRightTop.SPointNumb][1]=Cy;
					MRightTop.SPointNumb++;
					if(MRightTop.SPointNumb>=MaxSPointNumb){
						break;
					}
				}
			}
		}
	}
	MLeftBottom.SPointNumb=0;
	for(PureFlexAreaList *f=hArea.GetFirst();f!=NULL;f=f->GetNext(),R++){
		if((R%Sep)==0){
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			if(Cx<CenterX && CenterY<=Cy){
				if(f->IsInclude(Cx,Cy)==true){
					MLeftBottom.SPoint[MLeftBottom.SPointNumb][0]=Cx;
					MLeftBottom.SPoint[MLeftBottom.SPointNumb][1]=Cy;
					MLeftBottom.SPointNumb++;
					if(MLeftBottom.SPointNumb>=MaxSPointNumb){
						break;
					}
				}
			}
		}
	}
	MRightBottom.SPointNumb=0;
	for(PureFlexAreaList *f=hArea.GetFirst();f!=NULL;f=f->GetNext(),R++){
		if((R%Sep)==0){
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			if(CenterX<=Cx && CenterY<=Cy){
				if(f->IsInclude(Cx,Cy)==true){
					MRightBottom.SPoint[MRightBottom.SPointNumb][0]=Cx;
					MRightBottom.SPoint[MRightBottom.SPointNumb][1]=Cy;
					MRightBottom.SPointNumb++;
					if(MRightBottom.SPointNumb>=MaxSPointNumb){
						break;
					}
				}
			}
		}
	}
	return false;
}

bool	BaseMatch::SImage::ExecuteInitialAfterEdit2(double angle ,BYTE **RootBuff,ExecuteInitialAfterEditInfo &EInfo)
{
	Angle	=angle;
	int	XLen=ParentBaseMatch->SDotPerLine;
	int	XByte	=(XLen+7)/8;
	int	YLen	=ParentBaseMatch->SMaxLines;

	BYTE    **DBuff=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(DBuff ,0 ,XByte ,YLen);

	double	CosS=cos(angle);
	double	SinS=sin(angle);
	int	Cx=ParentBaseMatch->SDotPerLine/2;
	int	Cy=ParentBaseMatch->SMaxLines/2;

	#pragma omp parallel
	{
		#pragma omp for	
		for(int y=0;y<YLen;y++){
			BYTE	*d=DBuff[y];
			for(int x=0;x<XLen;x++){
				int	X=(x-Cx)*CosS-(y-Cy)*SinS+Cx;
				int	Y=(x-Cx)*SinS+(y-Cy)*CosS+Cy;

				if(X<0 || XLen<=X
				|| Y<0 || YLen<=Y)
					continue;
				if(GetBmpBit(RootBuff,X,Y)!=0){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
	SArea.RemoveAll();
	PickupFlexArea(DBuff ,XByte ,XLen,YLen ,SArea);

	DeleteMatrixBuff(DBuff,YLen);
	if(SArea.GetCount()>0)
		return true;
	return false;
}

double	BaseMatch::SImage::MatchingPointsStruct::CalcMatch1(SImage *Parent ,int dx ,int dy , int GlobalPage ,int skip)
{
	DataInPage	*Dp=Parent->ParentBaseMatch->GetLayersBase()->GetPageData(GlobalPage);
	if(Dp==NULL)
		return 0;
	DataInLayer	*Ly=Dp->GetLayerData(Parent->ParentBaseMatch->Layer);
	if(Ly==NULL)
		return 0;

	XYData	*XY=Parent->ParentBaseMatch->GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
	if(XY==NULL)
		return 0;
	int	OffX=XY->x*Parent->ParentBaseMatch->ZoomRate;
	int	OffY=XY->y*Parent->ParentBaseMatch->ZoomRate;

	int	DotPerLine1Page	=Parent->ParentBaseMatch->GetDotPerLine(-1)*Parent->ParentBaseMatch->ZoomRate;
	int	MaxLines1Page	=Parent->ParentBaseMatch->GetMaxLines(-1)*Parent->ParentBaseMatch->ZoomRate;
	int	DotPerLine		=Parent->ParentBaseMatch->GetDotPerLine(-1);
	int	MaxLines		=Parent->ParentBaseMatch->GetMaxLines(-1);
	double	Z=1.0/Parent->ParentBaseMatch->ZoomRate;
	ImageBuffer	&TBuff=Ly->GetTargetBuff();
	int	WCount=0;
	int	BCount=0;

	int	OutsidePointNumb=0;
	int	d=Parent->ParentBaseMatch->ABase->PermitDiffBaseMatch*Parent->ParentBaseMatch->ZoomRate;
	//int	d2=d/4;
	for(int i=0;i<SPointNumb;i+=skip){
		int	x=SPoint[i][0]+dx;
		int	y=SPoint[i][1]+dy;
		if(x<0 || Parent->ParentBaseMatch->SDotPerLine<=x || y<0 || Parent->ParentBaseMatch->SMaxLines<=y){
			OutsidePointNumb++;
		}
		x-=OffX;
		y-=OffY;
		if(0<=y && y<MaxLines1Page && 0<x && x<DotPerLine1Page){
			double	Yn=(y-d)*Z;
			for(int p=-d;p<=d;p++,Yn+=Z){
				int	Y=Yn;
				if(0<=Y && Y<MaxLines){
					BYTE	*s=TBuff.GetY(Y);
					double	Xn=(x-d)*Z;
					for(int q=-d;q<=d;q++,Xn+=Z){
						int	X=Xn;
						if(0<=X && X<DotPerLine){
							int	c=s[X];
							if(c>128){
								WCount++;
								goto	HNext;;
							}
						}
					}
				}
			}
			BCount++;
HNext:;
		}
	}
	if(OutsidePointNumb>10)
		return 0;
	if((WCount+BCount)==0)
		return 1.0;
	return ((double)WCount)/(double)(WCount+BCount);
}

double	BaseMatch::SImage::MatchingPointsStruct::CalcMatch(SImage *Parent ,int dx ,int dy , int GlobalPage)
{
	DataInPage	*Dp=Parent->ParentBaseMatch->GetLayersBase()->GetPageData(GlobalPage);
	if(Dp==NULL)
		return 0;
	DataInLayer	*Ly=Dp->GetLayerData(Parent->ParentBaseMatch->Layer);
	if(Ly==NULL)
		return 0;

	XYData	*XY=Parent->ParentBaseMatch->GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
	if(XY==NULL)
		return 0;
	dx-=XY->x*Parent->ParentBaseMatch->ZoomRate;
	dy-=XY->y*Parent->ParentBaseMatch->ZoomRate;

	int	DotPerLine1Page	=Parent->ParentBaseMatch->GetDotPerLine(-1)*Parent->ParentBaseMatch->ZoomRate;
	int	MaxLines1Page	=Parent->ParentBaseMatch->GetMaxLines(-1)*Parent->ParentBaseMatch->ZoomRate;
	double	Z=1.0/Parent->ParentBaseMatch->ZoomRate;
	ImageBuffer	&TBuff=Ly->GetTargetBuff();
	int	WCount=0;
	int	BCount=0;

	for(PureFlexAreaList *f=Parent->SArea.GetFirst();f!=NULL;f=f->GetNext()){
		for(int i=0;i<f->GetFLineLen();i++){
			int	x1=f->GetFLineLeftX (i)+dx;
			int	y =f->GetFLineAbsY  (i)+dy;
			int	x2=f->GetFLineRightX(i)+dx;
			if(0<=y && y<MaxLines1Page
			&& 0<x1 && x1<DotPerLine1Page){
				int	Y=y*Z;
				BYTE	*s=TBuff.GetY(Y);
				double	X1=x1*Z;
				for(int x=x1;x<x2 && x<DotPerLine1Page;x++){
					int	X=X1;
					int	c=s[X];
					if(c>128)
						WCount++;
					else
						BCount++;
					X1+=Z;
				}
			}
		}
	}
	if((WCount+BCount)==0)
		return 0;
	return ((double)WCount)/(double)(WCount+BCount);
}

double	BaseMatch::SImage::CalcMatch1(int dx ,int dy ,int GlobalPage ,int skip)
{
	double	d1=MLeftTop		.CalcMatch1(this,dx,dy,GlobalPage,skip);
	double	d2=MRightTop	.CalcMatch1(this,dx,dy,GlobalPage,skip);
	double	d3=MLeftBottom	.CalcMatch1(this,dx,dy,GlobalPage,skip);
	double	d4=MRightBottom	.CalcMatch1(this,dx,dy,GlobalPage,skip);
	return d1*d2*d3*d4;
}

void	BaseMatch::SImage::MatchingPointsStruct::Draw(SImage *Parent ,QPainter &P, int movx ,int movy ,double ZoomRate
							,const QColor &Col1 , const QColor &Col2)
{
	//QRgb c=qRgba(255,255,0,128);
	double	Z=1.0/Parent->ParentBaseMatch->ZoomRate;

	/*
	for(PureFlexAreaList *f=SArea.GetFirst();f!=NULL;f=f->GetNext()){
		f-> DrawAlpha(0,0 ,&pnt ,c
								,ZoomRate*ParentBaseMatch->ZoomRate ,movx ,movy);
	}
	*/
	P.setPen(Col1);
	for(int i=0;i<SPointNumb;i++){
		int	x=SPoint[i][0];
		int	y=SPoint[i][1];
		int	X=(x*Z+movx)*ZoomRate;
		int	Y=(y*Z+movy)*ZoomRate;
		P.drawLine(X-10,Y,X+10,Y);
		P.drawLine(X,Y-10,X,Y+10);
	}
	P.setPen(Col2);
	for(int i=0;i<SPointNumb;i++){
		int	x=SPoint[i][0];
		int	y=SPoint[i][1];
		int	X=(x*Z+Parent->ParentBaseMatch->ResultDx+movx)*ZoomRate;
		int	Y=(y*Z+Parent->ParentBaseMatch->ResultDy+movy)*ZoomRate;
		P.drawLine(X-10,Y,X+10,Y);
		P.drawLine(X,Y-10,X,Y+10);
	}

}
void	BaseMatch::SImage::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	QPainter	P(&pnt);
	MLeftTop	.MatchingPointsStruct::Draw(this ,P, movx ,movy ,ZoomRate ,Qt::yellow		, Qt::red);
	MRightTop	.MatchingPointsStruct::Draw(this ,P, movx ,movy ,ZoomRate ,Qt::darkYellow	, Qt::darkRed);
	MLeftBottom	.MatchingPointsStruct::Draw(this ,P, movx ,movy ,ZoomRate ,Qt::green		, Qt::red);
	MRightBottom.MatchingPointsStruct::Draw(this ,P, movx ,movy ,ZoomRate ,Qt::darkGreen	, Qt::darkRed);
}

//==================================================================
BaseMatch::BaseMatch(AlignmentFlexAreaBase *p,LayersBase *base)
	:ServiceForLayers(base),ABase(p)
{
	SImageInfo	=NULL;
	SImageNumb	=0;
	Layer		=0;

	ZoomRate	=0;
	SDotPerLine	=0;
	SMaxLines	=0;
	BaseBuff	=NULL;                        
	SearchDim	=NULL;
	SearchDimNumb	=0;
}
BaseMatch::~BaseMatch(void)
{
	for(int i=0;i<SImageNumb;i++){
		delete	SImageInfo[i];
	}
	delete	SImageInfo;
	SImageInfo=NULL;
	SImageNumb=0;
	if(BaseBuff!=NULL){
		DeleteMatrixBuff(BaseBuff,SMaxLines);
		BaseBuff=NULL;
	}
}

bool	BaseMatch::ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
{
	int x1 ,y1 ,x2 ,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);

	double	Zx=(double)GetDotPerLine(-1)/(double)x2;
	double	Zy=(double)GetMaxLines  (-1)/(double)y2;
	ZoomRate=((Zx<Zy)?Zx:Zy)*ABase->ZoomRateForBaseMatch;
	SDotPerLine	=ZoomRate*x2;
	SMaxLines	=ZoomRate*y2;

	if(BaseBuff!=NULL){
		DeleteMatrixBuff(BaseBuff,SMaxLines);
		BaseBuff=NULL;
	}
	BaseBuff	=MakeImageBuffer();

	int	L=max(SDotPerLine,SMaxLines);
	AngleDelta=atan(2.0/(double)L)*2;
	double	Range=ABase->RotationRangeBaseMatch*2*M_PI/360.0;
	if(AngleDelta==0.0)
		return false;
	int	N=Range/AngleDelta;
	SImageNumb=2*N+1;

	int	tMinXY=min(SDotPerLine,SMaxLines);
	RangeX=tMinXY*0.25;
	RangeY=tMinXY*0.25;
	SearchDimNumb=SImageNumb*(2*RangeX+1)*(2*RangeY+1);
	if(SearchDim!=NULL)
		delete	[]SearchDim;
	SearchDim=new struct SearchStruct[SearchDimNumb];

	return true;
}
bool	BaseMatch::MakeSImages(ExecuteInitialAfterEditInfo &EInfo)
{
	if(SImageInfo!=NULL){
		for(int i=0;i<SImageNumb;i++){
			delete	SImageInfo[i];
		}
		delete	SImageInfo;
	}
	SImageInfo=new SImage*[SImageNumb];
	int	N=SImageNumb/2;
	for(int i=-N;i<=N;i++){
		int	n=i+N;
		SImageInfo[n]=new SImage(n,this);
		SImageInfo[n]->ExecuteInitialAfterEdit1(i*AngleDelta,BaseBuff,EInfo);
	}
	/*
	int	XByte	=(SDotPerLine+7)/8;
	int	YLen	=SMaxLines;
	BYTE    **Tmp=MakeMatrixBuff(XByte ,YLen);
	if(ABase->ExpandBaseMatch>0){
		GetLayersBase()->FatAreaN(BaseBuff
					,Tmp
					,XByte, YLen
					,ABase->ExpandBaseMatch);
	}
	DeleteMatrixBuff(Tmp,YLen);

	for(int i=-N;i<=N;i++){
		int	n=i+N;
		SImageInfo[n]->ExecuteInitialAfterEdit2(i*AngleDelta,BaseBuff,ExecuteInitialAfterEdit_Changed);
	}
	*/

	return true;
}

BYTE	**BaseMatch::MakeImageBuffer(void)
{
	int	XByte	=(max(SDotPerLine,GetDotPerLine(-1))+7)/8;
	int	YLen	=max(SMaxLines,GetMaxLines(-1));
	BYTE    **s=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(s ,0 ,XByte ,YLen);
	return s;
}

void	BaseMatch::Draw(QImage &pnt, int movx ,int movy ,double tZoomRate ,int OffsetX ,int OffsetY ,AlgorithmDrawAttr *Attr)
{
	AlignmentFlexAreaDrawAttr	*LAttr=dynamic_cast<AlignmentFlexAreaDrawAttr *>(Attr);
	if(LAttr!=NULL){
		double	Z=1.0/ZoomRate;
		int	XByte	=(SDotPerLine+7)/8;
		DrawBitImageOr(pnt, (const BYTE **)BaseBuff,SDotPerLine ,XByte ,SMaxLines
						,movx*ZoomRate ,movy*ZoomRate ,tZoomRate*Z
						,OffsetX ,OffsetY
						,QColor(0,255,128,128));

		//for(int i=0;i<SImageNumb;i++){
		if(0<=LAttr->CurrentBaseMatchRow && LAttr->CurrentBaseMatchRow<SImageNumb){
			SImageInfo[LAttr->CurrentBaseMatchRow]->Draw(pnt,movx ,movy ,tZoomRate);
		}
	}
}

int	SearchStructFunc(const void *a , const void *b)
{
	struct BaseMatch::SearchStruct	*pa=(struct BaseMatch::SearchStruct *)a;
	struct BaseMatch::SearchStruct	*pb=(struct BaseMatch::SearchStruct *)b;
	if(pa->Total<pb->Total)
		return 1;
	if(pa->Total>pb->Total)
		return -1;
	return 0;
}

bool	BaseMatch::ExecuteMatching(void)
{
	int	n=0;
	for(int i=0;i<SImageNumb;i++){
		for(int dx=-RangeX;dx<RangeX;dx++){
			for(int dy=-RangeY;dy<RangeY;dy++){
				SearchDim[n].ImageNo=i;
				SearchDim[n].dx=dx;
				SearchDim[n].dy=dy;
				n++;
			}
		}
	}
	int	CalcDbgDx=-959*ZoomRate;
	int	CalcDbgDy=-432*ZoomRate;
	{
		double	TotalD=1.0;
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			double	D=SImageInfo[SImageNumb/2]->CalcMatch1(CalcDbgDx,CalcDbgDy,GlobalPage,1);
			TotalD*=D;
		}
			TotalD=0;
	}
	#pragma omp parallel
	{
		#pragma omp for	
		for(int i=0;i<n;i++){
			double	TotalD=1.0;
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				double	D=SImageInfo[SearchDim[i].ImageNo]->CalcMatch1(SearchDim[i].dx,SearchDim[i].dy,GlobalPage,ABase->BaseMatchLoopSep);
				TotalD*=D;
			}
			SearchDim[i].Total=TotalD;
		}
	}
	qsort(SearchDim,n,sizeof(struct	SearchStruct),SearchStructFunc);

	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	int		MaxN=0;
	int		nn=n/200;
	#pragma omp parallel
	{
		#pragma omp for	
		for(int i=0;i<nn;i++){
			double	TotalD=1.0;
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				double	D=SImageInfo[SearchDim[i].ImageNo]->CalcMatch1(SearchDim[i].dx,SearchDim[i].dy,GlobalPage,1);
				TotalD*=D;
			}
			#pragma omp critical
			{
				if(MaxD<TotalD){
					MaxD=TotalD;
					MaxDx=SearchDim[i].dx;
					MaxDy=SearchDim[i].dy;
					MaxN =SearchDim[i].ImageNo;
				}
			}
		}
	}
	ResultDx		=MaxDx;
	ResultDy		=MaxDy;
	ResultSImageNo	=MaxN;
	return true;
}



