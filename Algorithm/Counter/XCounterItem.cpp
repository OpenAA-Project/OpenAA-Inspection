/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCounterItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XCounterResource.h"
#include "XCounter.h"
#include "XMasking.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XInterpolation.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include "XCriticalFunc.h"

//=====================================================================================

CounterThreshold::CounterThreshold(CounterItem *parent)
:AlgorithmThreshold(parent)
{
	NoiseLevel		=40;
	AdoptedRate		=0.3;
	LineLength		=8;
	FilterRate		=0.6;
	OutMergin		=6;
	OutlineSearchDot=3;
}

bool	CounterThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CounterThreshold	*s=(const CounterThreshold *)&src;

	if(NoiseLevel		==s->NoiseLevel)
		return true;
	if(AdoptedRate		==s->AdoptedRate)
		return true;
	if(LineLength		==s->LineLength)
		return true;
	if(OutMergin		==s->OutMergin)
		return true;
	if(OutlineSearchDot	==s->OutlineSearchDot)
		return true;
	return false;
}
void	CounterThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const CounterThreshold	*s=(const CounterThreshold *)&src;
	NoiseLevel		=s->NoiseLevel;
	AdoptedRate		=s->AdoptedRate;
	LineLength		=s->LineLength;
	OutMergin		=s->OutMergin;
	OutlineSearchDot=s->OutlineSearchDot;
}
bool	CounterThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,NoiseLevel)==false)
		return(false);
	if(::Save(file,AdoptedRate)==false)
		return(false);
	if(::Save(file,LineLength)==false)
		return(false);
	if(::Save(file,OutMergin)==false)
		return(false);
	if(::Save(file,OutlineSearchDot)==false)
		return(false);

	return(true);
}
bool	CounterThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,NoiseLevel)==false)
		return(false);
	if(::Load(file,AdoptedRate)==false)
		return(false);
	if(::Load(file,LineLength)==false)
		return(false);
	if(::Load(file,OutMergin)==false)
		return(false);
	if(::Load(file,OutlineSearchDot)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
CounterItem::CounterItem(void)
{
	MatchingResultDim=NULL;
	MaxMatchingResultCount	=0;
	ResultCount				=0;
	RoughRotatedContainerTable	=NULL;
	RoughResult				=NULL;
	TimeOut					=false;
}

CounterItem::~CounterItem(void)
{
	if(MatchingResultDim!=NULL){
		delete	[]MatchingResultDim;
		MatchingResultDim=NULL;
	}
	if(RoughRotatedContainerTable!=NULL){
		delete	[]RoughRotatedContainerTable;
		RoughRotatedContainerTable=NULL;
	}
	if(RoughResult!=NULL){
		delete	[]RoughResult;
		RoughResult=NULL;
	}
}
bool	CounterItem::Save(QIODevice *f)
{
	if(AlgorithmItemPITemplate<CounterInPage,CounterBase>::Save(f)==false)
		return false;
	if(SourcePattern.Save(f)==false)
		return false;
	if(PickedAreaInPattern.Save(f)==false)
		return false;
	return true;
}
bool	CounterItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPITemplate<CounterInPage,CounterBase>::Load(f,LBase)==false)
		return false;
	if(SourcePattern.Load(f)==false)
		return false;
	if(PickedAreaInPattern.Load(f)==false)
		return false;
	return true;
}
double	CounterItem::GetRotatedZoomRate(int width ,int height)
{
	double	MinZoomRate=999999999;
	for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->GetNext()){
		int	W=r->SourcePattern[0]->GetWidth();
		int	H=r->SourcePattern[0]->GetHeight();
		double	Zx=width /(double)W;
		double	Zy=height/(double)H;
		double	ZoomRate=min(Zx,Zy);
		MinZoomRate=min(MinZoomRate,ZoomRate);
	}
	return MinZoomRate;
}
double	CounterItem::MakeImage(int width ,int height 
							   ,QImage &ItemImage
							   ,QImage &ItemImageWithMask
							   ,QImage &ItemBackGround)
{
	ItemImage=QImage(width,height,QImage::Format_RGB32);
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	double	Zx=width /(double)W;
	double	Zy=height/(double)H;
	double	ZoomRate=min(Zx,Zy);
	SourcePattern	 .MakeImage(ItemImage ,0,0 ,ZoomRate);

	ItemBackGround=QImage(width,height,QImage::Format_RGB32);
	BackGroundPattern.MakeImage(ItemBackGround ,0,0 ,ZoomRate);

	ItemImageWithMask=QImage(width,height,QImage::Format_RGB32);
	ItemImageWithMask=ItemImage;
	PickedAreaInPattern.DrawAlpha(0,0
								,&ItemImageWithMask,qRgba(255,0,0,128)
								,ZoomRate,0,0);
	return ZoomRate;
}

void	CounterItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	CounterDrawAttr	*MAttr=dynamic_cast<CounterDrawAttr *>(Attr);
	if(MAttr!=NULL && MAttr->ShowItems==true){
		SetVisible(true);
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

		CounterBase	*ABase=(CounterBase *)GetParentBase();
		int	n=0;
		for(int i=ResultCount-1;i>=0;i--,n++){
			MatchingResultList	*r=&MatchingResultDim[i];
			QColor	Col=ABase->GetItemColor(n);
			r->Pointer->Draw(pnt,movx ,movy ,ZoomRate
							,r->ResultPosX,r->ResultPosY
							,Col);

		}
		int	W=GetArea().GetWidth()/2;
		int	H=GetArea().GetHeight()/2;

		if(ABase->ShowMatchingRate==true){
			QPainter	Pnt(&pnt);
			Pnt.setBrush(Qt::white);
			Pnt.setPen(Qt::white);
			for(int i=ResultCount-1;i>=0;i--,n++){
				MatchingResultList	*r=&MatchingResultDim[i];
				Pnt.drawText((r->ResultPosX+W+movx)*ZoomRate,(r->ResultPosY+H+movy)*ZoomRate
							 ,QString("一致率:")+QString::number(r->MatchingResult));
				if(ABase->ShowDebugMode==true){
					Pnt.drawText((r->ResultPosX+W+movx)*ZoomRate,(r->ResultPosY+H+movy)*ZoomRate+16
								 ,QString("Rotation:")+QString::number(r->RotatedIndex));
				}
			}
		}
	}
}

void	CounterItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	CounterBase	*ABase=(CounterBase *)GetParentBase();
	int	n=0;
	for(int i=ResultCount-1;i>=0;i--,n++){
		MatchingResultList	*r=&MatchingResultDim[i];
		r->Pointer->Draw(IData,MovX ,MovY ,ZoomRate
						,r->ResultPosX,r->ResultPosY
						,ABase->GetItemColor(n));
	}
}

void	CounterItem::MakeInitial(void)
{
	SourcePattern.RemoveAll();
	ImagePointerContainer ImageList;
	GetTargetBuffList	(ImageList);

	AlgorithmBase	*MaskBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	AlgorithmInPageRoot	*MaskPage=NULL;
	if(MaskBase!=NULL){
		MaskPage=MaskBase->GetPageData(GetPage());
	}
	int	w=GetArea().GetWidth();
	int	h=GetArea().GetHeight();
	for(int layer=0;layer<GetLayerNumb();layer++){
		ImageBufferList	*L=new ImageBufferList(0,w,h);
		L->PartialCopy(*ImageList[layer],GetArea().GetMinX(),GetArea().GetMinY());
		SourcePattern.AppendList(L);
	}

	int	CountBackGround=0;
	ImageBuffer	*BackGroundImage[100];
	ImageBuffer	*MotherImage[100];
	int	LayerNumb=min(GetLayerNumb(),3);
	for(int layer=0;layer<LayerNumb;layer++){
		BackGroundImage[layer]=NULL;
		if(MaskPage!=NULL){
			MaskingInLayer	*MaskLayer=(MaskingInLayer *)MaskPage->GetLayerData(layer);
			if(MaskLayer->BackGroundImage.IsNull()==false){
				BackGroundImage[layer]=&MaskLayer->BackGroundImage;
				CountBackGround++;
			}
		}
		MotherImage[layer]=ImageList[layer];
	}

	int	Mergin=32;
	int	MapW=w+Mergin+Mergin;
	int	MapH=h+Mergin+Mergin;
	int	MapXByte=(MapW+7)/8;
	const	CounterThreshold	*RThr=GetThresholdR();
	int	NoisePass=RThr->NoiseLevel;

	BYTE	**Map=MakeMatrixBuff(MapXByte,MapH);
	MatrixBuffClear	(Map ,0 ,MapXByte,MapH);
	int	N=GetArea().GetFLineLen();
	BackGroundPattern.RemoveAll();
	if(CountBackGround==GetLayerNumb()){
		for(int layer=0;layer<GetLayerNumb();layer++){
			ImageBufferList	*L=new ImageBufferList(0,w,h);
			L->PartialCopy(*BackGroundImage[layer],GetArea().GetMinX(),GetArea().GetMinY());
			BackGroundPattern.AppendList(L);
		}

		FlexArea	Surround=GetArea();
		Surround.FatAreaN(3);
		Surround-=GetArea();

		double	AvrTarget[100];
		double	AvrBackGround[100];
		double	AvrDiff[100];
		for(int layer=0;layer<LayerNumb;layer++){
			AvrTarget	 [layer]=Surround.GetAverage(0,0,*MotherImage	 [layer]);
			AvrBackGround[layer]=Surround.GetAverage(0,0,*BackGroundImage[layer]);
			AvrDiff[layer]=AvrTarget[layer]-AvrBackGround[layer];
		}

		for(int i=0;i<N;i++){
			int	Y	=GetArea().GetFLineAbsY(i);
			int	X1	=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*s[100];
			BYTE	*b[100];
			for(int layer=0;layer<LayerNumb;layer++){
				s[layer]=MotherImage[layer]		->GetYWithoutDepended(Y);
				b[layer]=BackGroundImage[layer]	->GetYWithoutDepended(Y);
			}
			BYTE	*d=Map[Y-GetArea().GetMinY()+Mergin];
			for(int n=0;n<Numb;n++){
				int	X=X1+n;
				int layer;
				for(layer=0;layer<LayerNumb;layer++){
					int	t=abs((s[layer])[X]-((b[layer])[X]+AvrDiff[layer]));
					if(t>NoisePass){
						break;
					}
				}
				if(layer<LayerNumb){
					int	xn=X-GetArea().GetMinX()+Mergin;
					SetBmpBitOnY1(d,xn);
				}
			}
		}
	}
	else{
		FlexArea	Surround=GetArea();
		Surround.FatAreaN(3);
		Surround-=GetArea();

		double	Avr[100];
		for(int layer=0;layer<LayerNumb;layer++){
			Avr[layer]=Surround.GetAverage(0,0,*MotherImage[layer]);
		}
		for(int i=0;i<N;i++){
			int	Y	=GetArea().GetFLineAbsY(i);
			int	X1	=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*s[100];
			for(int layer=0;layer<LayerNumb;layer++){
				s[layer]=MotherImage[layer]->GetYWithoutDepended(Y);
			}
			BYTE	*d=Map[Y-GetArea().GetMinY()+Mergin];
			for(int n=0;n<Numb;n++){
				int	X=X1+n;
				int layer;
				for(layer=0;layer<LayerNumb;layer++){
					double	t=fabs((s[layer])[X]-Avr[layer]);
					if(t>NoisePass){
						break;
					}
				}
				if(layer<LayerNumb){
					int	xn=X-GetArea().GetMinX()+Mergin;
					SetBmpBitOnY1(d,xn);
				}
			}
		}
	}
	BYTE	**TmpMap=MakeMatrixBuff(MapXByte,MapH);
	::FatArea(Map
				,TmpMap
				,MapXByte,MapH);
	::ThinArea(Map
				,TmpMap
				,MapXByte,MapH);
	::ThinArea(Map
				,TmpMap
				,MapXByte,MapH);
	::FatArea(Map
				,TmpMap
				,MapXByte,MapH);
	DeleteMatrixBuff(TmpMap,MapH);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(Map ,MapXByte,MapW ,MapH ,FPack);
	CounterBase		*ABase=tGetParentBase();
	PickedAreaInPattern.Clear();
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetPatternByte()>ABase->MinAreaPiece){
			PickedAreaInPattern+=*a;
		}
	}
	PickedAreaInPattern.MoveToNoClip(-Mergin,-Mergin);

	DeleteMatrixBuff(Map,MapH);
}

void	CounterItem::CalcFocusLevel(void)
{
	int	RotatedCount=RotatedContainer.GetCount();
	HaltProcess.lock();
	for(int i=0;i<RotatedCount;i++){
		RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
		r->CalcFocusLevel();
	}
	HaltProcess.unlock();
}

ExeResult	CounterItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	CounterBase		*ABase=tGetParentBase();
	double	RoundIsolation=ABase->AngleStep;	//2.5;
	RotatedContainer.RemoveAll();
	double	RadiusL=hypot(GetArea().GetWidth(),GetArea().GetHeight())/2.0;
	int	RoundCount=(2*M_PI*RadiusL)/RoundIsolation;
	if(RoundCount>0){
		double	dS=2*M_PI/RoundCount;

		for(int s=0;s<RoundCount;s++){
			RotatedMatchingPattern	*r=new RotatedMatchingPattern(this);
			r->Angle=s*dS;
			r->MakeInitial(this
						   ,GetArea()
						   ,PickedAreaInPattern
						   ,SourcePattern);

			//bool	Found=false;
			//for(RotatedMatchingPattern *q=RotatedContainer.GetFirst();q!=NULL;q=q->GetNext()){
			//	double	d=q->Match(r);
			//	if(d>ABase->RotationalSame){
			//		Found=true;
			//		break;
			//	}
			//}
			//if(Found==true){
			//	delete	r;
			//}
			//else{
				RotatedContainer.AppendList(r);
			//}
		}
	}
	if(MatchingResultDim!=NULL){
		delete	[]MatchingResultDim;
	}
	MaxMatchingResultCount=tGetParentBase()->MaxMatchingResultCount;
	MatchingResultDim=new MatchingResultList[MaxMatchingResultCount];
	ResultCount	=0;

	if(RoughRotatedContainerTable!=NULL){
		delete	[]RoughRotatedContainerTable;
	}
	int	N=RotatedContainer.GetCount();
	//const	CounterThreshold	*RThr=GetThresholdR();
	RoughRotatedContainerTable=new RotatedMatchingPattern*[N];
	int	n=0;
	for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->GetNext(),n++){
		RoughRotatedContainerTable[n]=r;
	}
	if(RoughResult!=NULL){
		delete	[]RoughResult;
	}
	RoughCount=N*100000;
	RoughResult=new MatchingResultList[RoughCount];

	return Ret;
}

int	RoughResultFunc(const void *a ,const void *b)
{
	MatchingResultList	*pa=(MatchingResultList *)a;
	MatchingResultList	*pb=(MatchingResultList *)b;
	if(pa->MatchingResult<pb->MatchingResult)
		return 1;
	if(pa->MatchingResult>pb->MatchingResult)
		return -1;
	return 0;
}
int	MatchingResultListFuncByXY(const void *a ,const void *b)
{
	MatchingResultList	*pa=(MatchingResultList *)a;
	MatchingResultList	*pb=(MatchingResultList *)b;
	if(pa->ResultPosY<pb->ResultPosY)
		return 1;
	if(pa->ResultPosY>pb->ResultPosY)
		return -1;
	if(pa->ResultPosX<pb->ResultPosX)
		return 1;
	if(pa->ResultPosX>pb->ResultPosX)
		return -1;
	return 0;
}


struct ShiftXYR
{
	int		RIndex;
	short	Dx,Dy;
	float	D;
};
int	ShiftXYRFunc(const void *a ,const void *b)
{
	struct ShiftXYR	*pa=(struct ShiftXYR *)a;
	struct ShiftXYR	*pb=(struct ShiftXYR *)b;
	if(pa->D<pb->D)
		return 1;
	if(pa->D>pb->D)
		return -1;
	return 0;
}

static	bool	EnanbleOpenMP=true;
int	DbgX=1900;
int	DbgY=400;
int	DbgC=0;

ExeResult	CounterItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	CounterBase		*ABase=tGetParentBase();
	CounterInPage	*APage=tGetParentInPage();

	ResultCount=0;
	CounterThreshold	*WThr=GetThresholdW();
	MatchingMethod Method=_AveragePower;

	if(ABase->FocusLevel>8)
		WThr->OutlineSearchDot=4;
	else
	if(ABase->FocusLevel>5)
		WThr->OutlineSearchDot=3;
	else
	if(ABase->FocusLevel>3){
		WThr->OutlineSearchDot=2;
		Method=_MinRate;
	}
	else{
		WThr->OutlineSearchDot=1;
		Method=_MinRate;
	}
	const	CounterThreshold	*RThr=GetThresholdR();
	DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();
	DWORD	tm;

	int XLen	=GetDotPerLine();
	int YLen	=GetMaxLines();

	int	RotatedCount=RotatedContainer.GetCount();
	int	RCount=RotatedCount;
	int	Sep=ABase->SearchSep;
	int	AngleSep=2;
	BYTE **ExecuteMap=((CounterInPage *)GetParentInPage())->ExecuteMap;
	ImageBuffer *TargetImageList[3];
	GetTargetBuffList(TargetImageList);
	int	PMergin=hypot(GetArea().GetWidth(),GetArea().GetHeight())*0.2;
	if(PMergin>20)
		PMergin=20;

	TimeOut=false;
	HaltProcess.lock();

	if(ABase->ShowDebugMode==false){
		PureFlexAreaList *f;
		#pragma omp parallel
		#pragma omp single private(f)
		for(f=APage->ExecutedPickedFPack.GetFirst();f!=NULL;f=f->GetNext()){
			#pragma omp task
			{
				int	tx1,ty1,tx2,ty2;
				f->GetXY(tx1,ty1,tx2,ty2);
				//int	W=f->GetWidth();
				//int	H=f->GetHeight();

				for(int dy=ty1;dy<=ty2;dy+=Sep){
					for(int dx=tx1;dx<=tx2;dx+=Sep){
						for(int i=0;i<RCount;i+=AngleSep){
							tm=GetComputerMiliSec()-StartMilisec;
							if(tm>=GetParamGlobal()->MaxInspectMilisec){
								TimeOut=true;
								goto	TestEnd;
							}
							RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
							if(dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
							|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
								continue;
							}
							int	Kx=dx-r->PickedAreaInPattern.GetMinX();
							int	Ky=dy-r->PickedAreaInPattern.GetMinY();
							if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
									double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
									if(d>=RThr->AdoptedRate){
										double	d2=0,LastD=-1;
										for(int i=0;i<10;i++){
											d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
											if(d2<=LastD)
												break;
											LastD=d2;
										}
										if(d2>=RThr->AdoptedRate){
											#pragma omp critical
											{
												r->PickedAreaInPatternFat.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
												//SavePNGFileBit ("LLL1.png" ,ExecuteMap ,XLen/8 ,YLen);
												if(ResultCount<MaxMatchingResultCount){
													MatchingResultDim[ResultCount].RotatedIndex	=i;
													MatchingResultDim[ResultCount].Pointer		=r;
													MatchingResultDim[ResultCount].ResultPosX	=Kx;
													MatchingResultDim[ResultCount].ResultPosY	=Ky;
													MatchingResultDim[ResultCount].MatchingResult=d2;
													ResultCount++;
												}
											}
											break;
										}
									}
								}
							}
						}
					}
				}
				TestEnd:;
			}
		}
	}
	else{
		int	L=40;
		for(PureFlexAreaList *f=APage->ExecutedPickedFPack.GetFirst();f!=NULL;f=f->GetNext()){
			int	tx1,ty1,tx2,ty2;
			f->GetXY(tx1,ty1,tx2,ty2);
			//int	W=f->GetWidth();
			//int	H=f->GetHeight();

			int	Len=f->GetFLineLen();
			for(int t=0;t<Len;t++){
				int	Y	=f->GetFLineAbsY(t);
				int	X1	=f->GetFLineLeftX(t);
				int	Numb=f->GetFLineNumb(t);
				if(Numb<=4)
					continue;
				//int	X2=f->GetFLineRightX(t);
				int	dy=Y;
				for(int dx=X1-L;dx<X1;dx+=Sep){
					for(int i=0;i<RCount;i+=AngleSep){
						tm=GetComputerMiliSec()-StartMilisec;
						if(tm>=GetParamGlobal()->MaxInspectMilisec){
							TimeOut=true;
							goto	TestEnd2;
						}
						RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
						if(dx<=0 || dy<=0
						|| dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
						|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
							continue;
						}
						int	Kx=dx-r->PickedAreaInPattern.GetMinX();
						int	Ky=dy-r->PickedAreaInPattern.GetMinY();
						if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
							if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
								if(d>=RThr->AdoptedRate){
									double	d2=0,LastD=-1;
									for(int k=0;k<10;k++){
										d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
										if(d2<=LastD)
											break;
										LastD=d2;
									}
									if(d2>=RThr->AdoptedRate){
										//#pragma omp critical
										//{
											r->PickedAreaInPatternFat.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
											//SavePNGFileBit ("LLL1.png" ,ExecuteMap ,XLen/8 ,YLen);
											if(ResultCount<MaxMatchingResultCount){
												MatchingResultDim[ResultCount].RotatedIndex	=i;
												MatchingResultDim[ResultCount].Pointer		=r;
												MatchingResultDim[ResultCount].ResultPosX	=Kx;
												MatchingResultDim[ResultCount].ResultPosY	=Ky;
												MatchingResultDim[ResultCount].MatchingResult=d2;
												ResultCount++;
											}
										//}
										break;
									}
								}
							}
						}
					}
				}
			}

			/*
			int	MaxL=max(W,H);

			EAgain:;
			for(int L=-Sep;L<MaxL;L+=Sep){
				int	dx,dy;
				dy=ty1+L;
				for(dx=tx1+L;dx<=(tx2-L);dx+=Sep){
					for(int i=0;i<RCount;i+=AngleSep){
						tm=GetComputerMiliSec()-StartMilisec;
						if(tm>=GetParamGlobal()->MaxInspectMilisec){
							TimeOut=true;
							goto	TestEnd;
						}
						RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
						if(dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
						|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
							continue;
						}
						int	Kx=dx-r->PickedAreaInPattern.GetMinX();
						int	Ky=dy-r->PickedAreaInPattern.GetMinY();
						if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
							if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
								if(d>=RThr->AdoptedRate){
									double	d2;
									d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									if(d2>=RThr->AdoptedRate){
										r->PickedAreaInPatternFat.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
										//SavePNGFileBit ("LLL1.png" ,ExecuteMap ,XLen/8 ,YLen);
										if(ResultCount<MaxMatchingResultCount){
											MatchingResultDim[ResultCount].RotatedIndex	=i;
											MatchingResultDim[ResultCount].Pointer		=r;
											MatchingResultDim[ResultCount].ResultPosX	=Kx;
											MatchingResultDim[ResultCount].ResultPosY	=Ky;
											MatchingResultDim[ResultCount].MatchingResult=d2;
											ResultCount++;
											//goto	TestEnd;
											goto	EAgain;
										}
									}
								}
							}
						}
					}
				}
				dx=ty2-L;
				for(dy=ty1+L;dy<=(ty2-L);dy+=Sep){
					for(int i=0;i<RCount;i+=AngleSep){
						tm=GetComputerMiliSec()-StartMilisec;
						if(tm>=GetParamGlobal()->MaxInspectMilisec){
							TimeOut=true;
							goto	TestEnd;
						}
						RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
						if(dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
						|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
							continue;
						}
						int	Kx=dx-r->PickedAreaInPattern.GetMinX();
						int	Ky=dy-r->PickedAreaInPattern.GetMinY();
						if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
							if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
								if(d>=RThr->AdoptedRate){
									double	d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									if(d2>=RThr->AdoptedRate){
										r->PickedAreaInPattern.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
										if(ResultCount<MaxMatchingResultCount){
											MatchingResultDim[ResultCount].RotatedIndex	=i;
											MatchingResultDim[ResultCount].Pointer		=r;
											MatchingResultDim[ResultCount].ResultPosX	=Kx;
											MatchingResultDim[ResultCount].ResultPosY	=Ky;
											MatchingResultDim[ResultCount].MatchingResult=d2;
											ResultCount++;
											//goto	TestEnd;
										}
									}
								}
							}
						}
					}
				}
				dy=ty2-L;
				for(dx=tx2-L;dx>=(tx1+L);dx-=Sep){
					for(int i=0;i<RCount;i+=AngleSep){
						tm=GetComputerMiliSec()-StartMilisec;
						if(tm>=GetParamGlobal()->MaxInspectMilisec){
							TimeOut=true;
							goto	TestEnd;
						}

						RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
						if(dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
						|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
							continue;
						}
						int	Kx=dx-r->PickedAreaInPattern.GetMinX();
						int	Ky=dy-r->PickedAreaInPattern.GetMinY();
						if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
							if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
								if(d>=RThr->AdoptedRate){
									double	d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									if(d2>=RThr->AdoptedRate){
										r->PickedAreaInPattern.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
										if(ResultCount<MaxMatchingResultCount){
											MatchingResultDim[ResultCount].RotatedIndex	=i;
											MatchingResultDim[ResultCount].Pointer		=r;
											MatchingResultDim[ResultCount].ResultPosX	=Kx;
											MatchingResultDim[ResultCount].ResultPosY	=Ky;
											MatchingResultDim[ResultCount].MatchingResult=d2;
											ResultCount++;
											//goto	TestEnd;
										}
									}
								}
							}
						}
					}
				}
				dx=ty1+L;
				for(dy=ty2-L;dy>=(ty1+L);dy-=Sep){
					for(int i=0;i<RCount;i+=AngleSep){
						tm=GetComputerMiliSec()-StartMilisec;
						if(tm>=GetParamGlobal()->MaxInspectMilisec){
							TimeOut=true;
							goto	TestEnd;
						}

						RotatedMatchingPattern *r=RoughRotatedContainerTable[i];
						if(dx+(r->PickedAreaInPatternXLen-PMergin)>tx2
						|| dy+(r->PickedAreaInPatternYLen-PMergin)>ty2){
							continue;
						}
						int	Kx=dx-r->PickedAreaInPattern.GetMinX();
						int	Ky=dy-r->PickedAreaInPattern.GetMinY();
						if(r->GetCrossRoughPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
							if(r->GetCrossDetailPoints(Kx,Ky ,ExecuteMap ,XLen ,YLen)==true){
								double	d=r->Match(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot,Method);
								if(d>=RThr->AdoptedRate){
									double	d2=r->MatchByEdge(TargetImageList ,Kx,Ky,RThr->OutlineSearchDot);
									if(d2>=RThr->AdoptedRate){
										r->PickedAreaInPattern.MakeNotBitData(ExecuteMap ,XLen ,YLen,Kx,Ky);
										if(ResultCount<MaxMatchingResultCount){
											MatchingResultDim[ResultCount].RotatedIndex	=i;
											MatchingResultDim[ResultCount].Pointer		=r;
											MatchingResultDim[ResultCount].ResultPosX	=Kx;
											MatchingResultDim[ResultCount].ResultPosY	=Ky;
											MatchingResultDim[ResultCount].MatchingResult=d2;
											ResultCount++;
											//goto	TestEnd;
										}
									}
								}
							}
						}
					}
				}
			}
			*/
			TestEnd2:;
		}
	}

	QSort(MatchingResultDim,ResultCount,sizeof(MatchingResultDim[0]),MatchingResultListFuncByXY);
	HaltProcess.unlock();

	FinishCalc();
	return _ER_true;
}
