/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Palletize\XPalletize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPalletize.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XPalletizeLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=====================================================================================

PalletizeThreshold::PalletizeThreshold(PalletizeItem *parent)
:AlgorithmThreshold(parent)
{
	AngleRange		=20;
	MinZoomSize		=0.8;
	MaxZoomSize		=1.3;
	PieceSize		=50;
	SearchDotPiece	=4;
	ThresholdV		=30;
	MaxCountOfPiece	=1;
	ThreshCoeff		=0.6;
	SearchNearBy	=50;
	MaxShift		=200;
}

void	PalletizeThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const PalletizeThreshold *s=(const PalletizeThreshold *)&src;
	AngleRange		=s->AngleRange;
	MinZoomSize		=s->MinZoomSize;
	MaxZoomSize		=s->MaxZoomSize;
	PieceSize		=s->PieceSize;
	SearchDotPiece	=s->SearchDotPiece;
	ThresholdV		=s->ThresholdV;
	MaxCountOfPiece	=s->MaxCountOfPiece;
	ThreshCoeff		=s->ThreshCoeff;
	SearchNearBy	=s->SearchNearBy;
	MaxShift		=s->MaxShift;
}
bool	PalletizeThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const PalletizeThreshold *s=(const PalletizeThreshold *)&src;
	if(AngleRange		==s->AngleRange
	&& MinZoomSize		==s->MinZoomSize
	&& MaxZoomSize		==s->MaxZoomSize
	&& PieceSize		==s->PieceSize
	&& SearchDotPiece	==s->SearchDotPiece
	&& ThresholdV		==s->ThresholdV
	&& MaxCountOfPiece	==s->MaxCountOfPiece
	&& ThreshCoeff		==s->ThreshCoeff
	&& SearchNearBy		==s->SearchNearBy
	&& MaxShift			==s->MaxShift)
		return true;
	return false;
}
bool	PalletizeThreshold::Save(QIODevice *f)
{
	WORD	Ver=PalletizeVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,AngleRange)==false)
		return false;
	if(::Save(f,MinZoomSize)==false)
		return false;
	if(::Save(f,MaxZoomSize)==false)
		return false;
	if(::Save(f,PieceSize)==false)
		return false;
	if(::Save(f,SearchDotPiece)==false)
		return false;
	if(::Save(f,ThresholdV)==false)
		return false;
	if(::Save(f,MaxCountOfPiece)==false)
		return false;
	if(::Save(f,ThreshCoeff)==false)
		return false;
	if(::Save(f,SearchNearBy)==false)
		return false;
	if(::Save(f,MaxShift)==false)
		return false;

	return true;
}

bool	PalletizeThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,AngleRange)==false)
		return false;
	if(::Load(f,MinZoomSize)==false)
		return false;
	if(::Load(f,MaxZoomSize)==false)
		return false;
	if(::Load(f,PieceSize)==false)
		return false;
	if(::Load(f,SearchDotPiece)==false)
		return false;
	if(::Load(f,ThresholdV)==false)
		return false;
	if(::Load(f,MaxCountOfPiece)==false)
		return false;
	if(::Load(f,ThreshCoeff)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,SearchNearBy)==false)
			return false;
		if(::Load(f,MaxShift)==false)
			return false;
	}
	else{
		SearchNearBy=50;
		MaxShift	=200;
	}

	return true;
}

void	PalletizeThreshold::FromLibrary(AlgorithmLibrary *src)
{
	PalletizeLibrary	*LSrc=dynamic_cast<PalletizeLibrary *>(src);
	if(LSrc==NULL)
		return;

	AngleRange		=LSrc->AngleRange;
	MinZoomSize		=LSrc->MinZoomSize;
	MaxZoomSize		=LSrc->MaxZoomSize;
	PieceSize		=LSrc->PieceSize;
	SearchDotPiece	=LSrc->SearchDotPiece;
	ThresholdV		=LSrc->ThresholdV;
	MaxCountOfPiece	=LSrc->MaxCountOfPiece;
	ThreshCoeff		=LSrc->ThreshCoeff;
	SearchNearBy	=LSrc->SearchNearBy;
	MaxShift		=LSrc->MaxShift;
}
void	PalletizeThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	PalletizeLibrary	*LDst=dynamic_cast<PalletizeLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->AngleRange		=AngleRange;
	LDst->MinZoomSize		=MinZoomSize;
	LDst->MaxZoomSize		=MaxZoomSize;
	LDst->PieceSize			=PieceSize;
	LDst->SearchDotPiece	=SearchDotPiece;
	LDst->ThresholdV		=ThresholdV;
	LDst->MaxCountOfPiece	=MaxCountOfPiece;
	LDst->ThreshCoeff		=ThreshCoeff;
	LDst->SearchNearBy		=SearchNearBy;
	LDst->MaxShift			=MaxShift;
}
//===========================================================================================

bool	MasterPositionList::Save(QIODevice *f)
{
	int	Ver=1;
	if(::Save(f,Ver)==false)	return false;
	if(::Save(f,XPos)==false)	return false;
	if(::Save(f,YPos)==false)	return false;
	if(::Save(f,ZPos)==false)	return false;
	return true;
}
bool	MasterPositionList::Load(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,XPos)==false)	return false;
	if(::Load(f,YPos)==false)	return false;
	if(::Load(f,ZPos)==false)	return false;
	return true;
}
MasterPositionList	*MasterPositionListContainer::Create(void)
{
	return new MasterPositionList();
}
//===========================================================================================

PalletizeItem::PalletizeItem(void)
{
	RotatedContainer=NULL;
	CountZoomSize	=0;
	MList		=NULL;
	SList		=NULL;
	MListCount	=0;
	SkipSearchXY=3;

	NearMList		=NULL;
	NearSList		=NULL;
	NearMListCount	=0;
	NearSkipSearchXY=2;

	LastResultCount	=0;
}

PalletizeItem::~PalletizeItem(void)
{
	if(RotatedContainer!=NULL){
		delete	[]RotatedContainer;
		RotatedContainer=NULL;
	}
	CountZoomSize	=0;
	if(MList!=NULL){
		delete	[]MList;
		MList=NULL;
	}
	if(SList!=NULL){
		delete	[]SList;
		SList=NULL;
	}
	MListCount=0;

	if(NearMList!=NULL){
		delete	[]NearMList;
		NearMList=NULL;
	}
	if(NearSList!=NULL){
		delete	[]NearSList;
		NearSList=NULL;
	}
	NearMListCount=0;
}

PalletizeItem &PalletizeItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((PalletizeItem *)&src));
	return *this;
}

void	PalletizeItem::CopyThreshold(PalletizeItem &src)
{
	GetThresholdW()->CopyFrom(*((PalletizeThreshold *)src.GetThresholdR()));
}

void	PalletizeItem::CopyThresholdOnly(PalletizeItem &src)
{
	GetThresholdW()->CopyFrom(*((PalletizeThreshold *)src.GetThresholdR()));
}

bool    PalletizeItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
	if(ItemArea.Save(file)==false)
		return false;
	if(MasterPositions.Save(file)==false)
		return false;
	return true;
}
bool    PalletizeItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
	if(ItemArea.Load(file)==false)
		return false;
	if(MasterPositions.Load(file)==false)
		return false;
	return true;
}

void	PalletizeItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((PalletizeItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((PalletizeItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((PalletizeItem *)Data));
		}
	}
}

void	PalletizeItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
}
void	PalletizeItem::CopyArea(PalletizeItem &src)
{
	SetArea(src.GetArea());
}

void	PalletizeItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	PalletizeDrawAttr	*BAttr=dynamic_cast<PalletizeDrawAttr *>(Attr);
	if(BAttr!=NULL){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		if(BAttr->ShowResult==true){
			QRgb	Col=qRgba(255,255,0,128);
			for(int i=0;i<Results.ResultCount;i++){
				MatchingResult	*f=&Results.ResultList[i];
				RotatedMatchingPattern	*P=GetRotPattern(f->RotatedIndex,f->ZoomSizeIndex);
				if(P!=NULL){
					P->PickedAreaInPattern.DrawAlpha(f->ResultPosX,f->ResultPosY
													 ,&pnt,Col
													 ,ZoomRate,movx,movy);
				}
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}


}

void	PalletizeItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::red;
		c.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);

		int	GWidth	=IData.width();
		int	GHeight=IData.height();

		PData.setBrush(Qt::yellow);
		PData.setPen(Qt::yellow);
	}
}
RotatedMatchingPattern	*PalletizeItem::GetRotPattern(int RotIndex ,int ZoomIndex)
{
	if(0<=ZoomIndex && ZoomIndex<CountZoomSize){
		RotatedMatchingPattern	*R=RotatedContainer[ZoomIndex].GetItem(RotIndex);
		return R;
	}
	return NULL;
}

int		PalletizeItem::GetCountRotation(void)
{
	if(CountZoomSize!=0){
		return RotatedContainer[0].GetCount();
	}
	return 0;
}

void	PalletizeItem::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPalletizeResultInItem	*CmdPalletizeResultInItemVar=dynamic_cast<CmdPalletizeResultInItem *>(packet);
	if(CmdPalletizeResultInItemVar!=NULL){
		if(0<=CmdPalletizeResultInItemVar->ResultIndex
		&& CmdPalletizeResultInItemVar->ResultIndex<Results.ResultCount){
			RotatedMatchingPattern	*R=GetRotPattern(Results.ResultList[CmdPalletizeResultInItemVar->ResultIndex].RotatedIndex
													,Results.ResultList[CmdPalletizeResultInItemVar->ResultIndex].ZoomSizeIndex);
			if(R!=NULL){
				CmdPalletizeResultInItemVar->Radian=R->Radian;
			}
		}
		return;
	}
}

void	PalletizeItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AlgorithmItemPITemplate<PalletizeInPage,PalletizeBase>::MakeIndependentItems(AInd,LocalX ,LocalY);

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	MasterPositions.Save(&Buff);
	AInd->Something=Buff.buffer();
}

ExeResult	PalletizeItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	if(RotatedContainer!=NULL){
		delete	[]RotatedContainer;
	}
	CountZoomSize	=GetThresholdR()->PieceSize*(GetThresholdR()->MaxZoomSize-GetThresholdR()->MinZoomSize);
	double	DivZ=(GetThresholdR()->MaxZoomSize-GetThresholdR()->MinZoomSize)/CountZoomSize;
	CountZoomSize++;
	RotatedContainer=new NPListPack<RotatedMatchingPattern>[CountZoomSize];
	double	DivR=3.0/((double)GetThresholdR()->PieceSize);
	double	DivS=atan(DivR);
	int	tRotationCount=(GetThresholdR()->AngleRange*M_PI/180.0)/DivS;
	int	DivA=GetThresholdR()->AngleRange/tRotationCount;
	int	RotationCount=tRotationCount*2+1;
	for(int i=0;i<CountZoomSize;i++){		
		for(int a=-tRotationCount;a<=tRotationCount;a++){
			double	Radian=DivA*a*M_PI/180.0;
			RotatedMatchingPattern	*v=new RotatedMatchingPattern(this ,Radian,GetThresholdR()->MinZoomSize+DivZ*i);
			RotatedContainer[i].AppendList(v);
		}
	}
	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int i=0;i<CountZoomSize;i++){
			for(RotatedMatchingPattern	*v=RotatedContainer[i].GetFirst();v!=NULL;v=v->GetNext()){
				v->BuildInitial(ItemArea);
			}
		}
	}
	int	XLen=GetDotPerLine()-GetArea().GetWidth();
	int	YLen=GetMaxLines()	-GetArea().GetHeight();

	if(MList!=NULL){
		delete	[]MList;
		MList=NULL;
	}
	if(SList!=NULL){
		delete	[]SList;
		SList=NULL;
	}
	MListCount=0;
	for(int dx=0;dx<XLen;dx+=SkipSearchXY){
		for(int dy=0;dy<YLen;dy+=SkipSearchXY){
			for(int i=0;i<CountZoomSize;i++){
				for(int k=0;k<RotationCount;k++){
					MListCount++;
				}
			}
		}
	}
	MList=new struct MatchingShiftList[MListCount];
	SList=new struct MatchingShiftList[MListCount];

	int	n=0;
	for(int dx=0;dx<XLen;dx+=SkipSearchXY){
		for(int dy=0;dy<YLen;dy+=SkipSearchXY){
			for(int i=0;i<CountZoomSize;i++){
				for(int k=0;k<RotationCount;k++){
					MList[n].Dx=dx;
					MList[n].Dy=dy;
					MList[n].RIndex=k;
					MList[n].ZIndex=i;
					MList[n].Pointer=RotatedContainer[i].GetItem(k);
					n++;
				}
			}
		}
	}

	if(NearMList!=NULL){
		delete	[]NearMList;
		NearMList=NULL;
	}
	if(NearSList!=NULL){
		delete	[]NearSList;
		NearSList=NULL;
	}
	NearMListCount=0;
	int	SearchNearBy	=GetThresholdR()->SearchNearBy;
	for(int dx=-SearchNearBy;dx<SearchNearBy;dx+=NearSkipSearchXY){
		for(int dy=-SearchNearBy;dy<SearchNearBy;dy+=NearSkipSearchXY){
			for(int i=0;i<CountZoomSize;i++){
				for(int k=0;k<RotationCount;k++){
					NearMListCount++;
				}
			}
		}
	}
	NearMList=new struct MatchingShiftList[NearMListCount];
	NearSList=new struct MatchingShiftList[NearMListCount];

	n=0;
	for(int dx=-SearchNearBy;dx<SearchNearBy;dx+=NearSkipSearchXY){
		for(int dy=-SearchNearBy;dy<SearchNearBy;dy+=NearSkipSearchXY){
			for(int i=0;i<CountZoomSize;i++){
				for(int k=0;k<RotationCount;k++){
					NearMList[n].Dx=dx;
					NearMList[n].Dy=dy;
					NearMList[n].RIndex=k;
					NearMList[n].ZIndex=i;
					NearMList[n].Pointer=RotatedContainer[i].GetItem(k);
					n++;
				}
			}
		}
	}
	return Ret;
}

int FuncMList(const void *a, const void *b)
{
	struct MatchingShiftList	*pa=(struct MatchingShiftList *)a;
	struct MatchingShiftList	*pb=(struct MatchingShiftList *)b;
	if(pa->MatchingValue<pb->MatchingValue)
		return 1;
	if(pa->MatchingValue>pb->MatchingValue)
		return -1;
	return 0;
}

static	int	DbgX=1500;
static	int	DbgCount=0;

ExeResult	PalletizeItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	Results.Allocate(GetThresholdR()->MaxCountOfPiece);
	for(int i=0;i<StockCountResult;i++){
		LastResults[i].Allocate(GetThresholdR()->MaxCountOfPiece);
	}

	ImageBuffer *TargetImageList[100];
	GetTargetBuffList(TargetImageList);

	if(MasterPositions.GetCount()==0){
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int i=0;i<MListCount;i++){
				RotatedMatchingPattern	*v=MList[i].Pointer;
				SList[i]		=MList[i];
				SList[i].MatchingValue=v->MatchByOneLine(MList[i].Dx,MList[i].Dy,*TargetImageList[0]);
			}
		}
		::QSort(SList,MListCount,sizeof(struct MatchingShiftList),FuncMList);

		int	MListCount1=MListCount/50;
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int i=0;i<MListCount1;i++){
				RotatedMatchingPattern	*v=SList[i].Pointer;
				SList[i].MatchingValue=v->MatchRoughByLine(SList[i].Dx,SList[i].Dy,*TargetImageList[0]);
			}
		}
		::QSort(SList,MListCount1,sizeof(struct MatchingShiftList),FuncMList);

		for(int i=0;i<MListCount;i++){
			if(SList[i].Dx>DbgX){
				DbgCount++;
			}
		}

		int	MListCount2=MListCount1/50;
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int i=0;i<MListCount2;i++){
				RotatedMatchingPattern	*v=SList[i].Pointer;
				SList[i].MatchingValue=v->MatchByLine(SList[i].Dx,SList[i].Dy,*TargetImageList[0]);
			}
		}
		//::QSort(SList,MListCount2,sizeof(struct MatchingShiftList),FuncMList);
		//for(int i=0;i<MListCount2;i++){
		//	if(SList[i].Dx>DbgX){
		//		DbgCount++;
		//	}
		//}

		//int	MFinalListCount=(MListCount2<200)?MListCount2:200;
		//#pragma omp parallel
		//{                                                
		//	#pragma omp for
		//	for(int i=0;i<MFinalListCount;i++){
		//		RotatedMatchingPattern	*v=SList[i].Pointer;
		//		SList[i].MatchingValue=v->Match(SList[i].Dx,SList[i].Dy,*TargetImageList[0]);
		//	}
		//}
		//::QSort(SList,MFinalListCount,sizeof(struct MatchingShiftList),FuncMList);
		//for(int i=0;i<MFinalListCount;i++){
		//	if(SList[i].Dx>DbgX){
		//		DbgCount++;
		//	}
		//}

		Results.ResultCount=0;
		for(int N=0;N<GetThresholdR()->MaxCountOfPiece;N++){

			::QSort(SList,MListCount2,sizeof(struct MatchingShiftList),FuncMList);
			int	MFinalListCount=(MListCount2<50)?MListCount2:50;
			#pragma omp parallel
			{                                                
				#pragma omp for
				for(int i=0;i<MFinalListCount;i++){
					RotatedMatchingPattern	*v=SList[i].Pointer;
					SList[i].MatchingValue=v->Match(SList[i].Dx,SList[i].Dy,*TargetImageList[0]);
				}
			}
			::QSort(SList,MFinalListCount,sizeof(struct MatchingShiftList),FuncMList);
			for(int i=0;i<MFinalListCount;i++){
				if(SList[i].Dx>DbgX){
					DbgCount++;
				}
			}
			for(int i=0;i<MFinalListCount;i++){
				if(SList[i].MatchingValue>GetThresholdR()->ThreshCoeff){
					int	sx=SList[i].Dx;
					int	sy=SList[i].Dy;
					FlexArea	A=ItemArea;
					A.MoveToNoClip(sx,sy);
					bool	Overlapped=false;
					for(int j=0;j<Results.ResultCount;j++){
						int	rx=Results.ResultList[j].ResultPosX;
						int	ry=Results.ResultList[j].ResultPosY;
						FlexArea	S=ItemArea;
						S.MoveToNoClip(rx,ry);
						if(A.CheckOverlap(&S)==true){
							Overlapped=true;
							break;
						}
					}
					if(Overlapped==true){
						SList[i].MatchingValue=0;
					}
					else{
						#pragma omp parallel
						{                                                
							#pragma omp for
							for(int i=0;i<NearMListCount;i++){
								RotatedMatchingPattern	*v=NearMList[i].Pointer;
								NearSList[i]=NearMList[i];
								NearSList[i].MatchingValue=v->MatchRoughByLine(NearMList[i].Dx+sx,NearMList[i].Dy+sy,*TargetImageList[0]);
							}
						}
						::QSort(NearSList,NearMListCount,sizeof(struct MatchingShiftList),FuncMList);

						int	NearMListCount1=NearMListCount/20;
						#pragma omp parallel
						{                                                
							#pragma omp for
							for(int i=0;i<NearMListCount1;i++){
								RotatedMatchingPattern	*v=NearMList[i].Pointer;
								NearSList[i].MatchingValue=v->MatchRough(NearMList[i].Dx+sx,NearMList[i].Dy+sy,*TargetImageList[0]);
							}
						}
						::QSort(NearSList,NearMListCount1,sizeof(struct MatchingShiftList),FuncMList);

						int	NearMListCount2=NearMListCount1/20;
						#pragma omp parallel
						{                                                
							#pragma omp for
							for(int i=0;i<NearMListCount2;i++){
								RotatedMatchingPattern	*v=NearMList[i].Pointer;
								NearSList[i].MatchingValue=v->Match(NearMList[i].Dx+sx,NearMList[i].Dy+sy,*TargetImageList[0]);
							}
						}
						::QSort(NearSList,NearMListCount2,sizeof(struct MatchingShiftList),FuncMList);

						Results.ResultList[Results.ResultCount].ResultPosX=NearSList[0].Dx+sx;
						Results.ResultList[Results.ResultCount].ResultPosY=NearSList[0].Dy+sy;
						Results.ResultList[Results.ResultCount].RotatedIndex	=NearSList[0].RIndex;
						Results.ResultList[Results.ResultCount].ZoomSizeIndex	=NearSList[0].ZIndex;
						RotatedMatchingPattern	*v=NearMList[0].Pointer;
						Results.ResultList[Results.ResultCount].MatchingValue	=v->Match(NearMList[0].Dx+sx,NearMList[0].Dy+sy,*TargetImageList[0]);
						Results.ResultList[Results.ResultCount].DiffX	=0;
						Results.ResultList[Results.ResultCount].DiffY	=0;	
						Results.ResultCount++;

						int	W=GetArea().GetWidth();
						int	H=GetArea().GetHeight();
						for(int i=0;i<MListCount2;i++){
							if(CheckOverlapRectRect(sx,sy,sx+W,sy+H
										,SList[i].Dx,SList[i].Dy,SList[i].Dx+W,SList[i].Dy+H)==true){
								SList[i].MatchingValue=0;
							}
						}
					}
				}
			}
		}
		for(int i=0;i<Results.ResultCount;i++){
			int	IndexMasterPos=0;
			for(MasterPositionList *L=MasterPositions.GetFirst();L!=NULL;L=L->GetNext(),IndexMasterPos++){
				int	dx=Results.ResultList[i].ResultPosX - L->XPos;
				int	dy=Results.ResultList[i].ResultPosY - L->YPos;
				if(hypot(dx,dy)<GetThresholdR()->MaxShift){
					Results.ResultList[i].DiffX=dx;
					Results.ResultList[i].DiffY=dy;
					Results.ResultList[i].IndexMasterPos=IndexMasterPos;
					break;
				}
			}
		}
	}
	else{
		Results.ResultCount=0;
		int	IndexMasterPos=0;
		for(MasterPositionList *a=MasterPositions.GetFirst();a!=NULL;a=a->GetNext(),IndexMasterPos++){
			#pragma omp parallel
			{                                                
				#pragma omp for
				for(int i=0;i<NearMListCount;i++){
					RotatedMatchingPattern	*v=NearMList[i].Pointer;
					NearSList[i]=NearMList[i];
					NearSList[i].MatchingValue=v->MatchRoughByLine(NearMList[i].Dx+a->XPos,NearMList[i].Dy+a->YPos,*TargetImageList[0]);
				}
			}
			::QSort(NearSList,NearMListCount,sizeof(struct MatchingShiftList),FuncMList);

			int	NearMListCount1=NearMListCount/20;
			#pragma omp parallel
			{                                                
				#pragma omp for
				for(int i=0;i<NearMListCount1;i++){
					RotatedMatchingPattern	*v=NearMList[i].Pointer;
					NearSList[i].MatchingValue=v->MatchRough(NearMList[i].Dx+a->XPos,NearMList[i].Dy+a->YPos,*TargetImageList[0]);
				}
			}
			::QSort(NearSList,NearMListCount1,sizeof(struct MatchingShiftList),FuncMList);

			int	NearMListCount2=NearMListCount1/20;
			#pragma omp parallel
			{                                                
				#pragma omp for
				for(int i=0;i<NearMListCount2;i++){
					RotatedMatchingPattern	*v=NearMList[i].Pointer;
					NearSList[i].MatchingValue=v->Match(NearMList[i].Dx+a->XPos,NearMList[i].Dy+a->YPos,*TargetImageList[0]);
				}
			}
			::QSort(NearSList,NearMListCount2,sizeof(struct MatchingShiftList),FuncMList);

			RotatedMatchingPattern	*v=NearMList[0].Pointer;
			double	Avr=v->PickedAreaInPattern.GetAverage(NearSList[0].Dx+a->XPos ,NearSList[0].Dy+a->YPos
														,*TargetImageList[0]
														,0.9,0.6);
			if(Avr>tGetParentBase()->MinAvrage){
				Results.ResultList[Results.ResultCount].ResultPosX=NearSList[0].Dx+a->XPos;
				Results.ResultList[Results.ResultCount].ResultPosY=NearSList[0].Dy+a->YPos;
				Results.ResultList[Results.ResultCount].RotatedIndex	=NearSList[0].RIndex;
				Results.ResultList[Results.ResultCount].ZoomSizeIndex	=NearSList[0].ZIndex;
				Results.ResultList[Results.ResultCount].MatchingValue	=v->Match(NearMList[0].Dx+a->XPos,NearMList[0].Dy+a->YPos,*TargetImageList[0]);
				Results.ResultList[Results.ResultCount].DiffX	=NearSList[0].Dx;
				Results.ResultList[Results.ResultCount].DiffY	=NearSList[0].Dy;
				Results.ResultList[Results.ResultCount].IndexMasterPos=IndexMasterPos;
				Results.ResultCount++;
			}
		}
	}
	for(int i=StockCountResult-1;i>=1;i--){
		LastResults[i]=LastResults[i-1];
	}
	if(LastResultCount<StockCountResult)
		LastResultCount++;
	LastResults[0]=Results;

	IntList	IndexMasterPosList;
	for(int i=0;i<Results.ResultCount;i++){
		bool	NoIndex=false;
		for(int k=0;k<IgnoreStockCount && k<LastResultCount;k++){
			bool	Found=false;
			for(int n=0;n<LastResults[k].ResultCount;n++){
				if(LastResults[k].ResultList[n].IndexMasterPos==Results.ResultList[i].IndexMasterPos){
					Found=true;
					break;
				}
			}
			if(Found==false){
				NoIndex=true;
				break;
			}
		}
		if(NoIndex==false){
			IndexMasterPosList.Add(Results.ResultList[i].IndexMasterPos);
		}
	}
	for(int i=0;i<Results.ResultCount;i++){
		Results.ResultList[i].DiffX			=0;
		Results.ResultList[i].DiffY			=0;
		Results.ResultList[i].ResultPosX	=0;
		Results.ResultList[i].ResultPosY	=0;
		Results.ResultList[i].RotatedIndex	=0;
		Results.ResultList[i].ZoomSizeIndex	=0;
	}
	Results.ResultCount=0;

	for(IntClass *v=IndexMasterPosList.GetFirst();v!=NULL;v=v->GetNext()){
		int	i=Results.ResultCount;
		Results.ResultList[i].IndexMasterPos=v->GetValue();
		int	HCount=0;
		for(int k=IgnoreStockCount;k<LastResultCount && k<StockCountResult;k++){
			for(int n=0;n<LastResults[k].ResultCount;n++){
				if(LastResults[k].ResultList[n].IndexMasterPos==Results.ResultList[i].IndexMasterPos){
					Results.ResultList[i].DiffX			+=LastResults[k].ResultList[n].DiffX;
					Results.ResultList[i].DiffY			+=LastResults[k].ResultList[n].DiffY;
					Results.ResultList[i].ResultPosX	+=LastResults[k].ResultList[n].ResultPosX;
					Results.ResultList[i].ResultPosY	+=LastResults[k].ResultList[n].ResultPosY;
					Results.ResultList[i].RotatedIndex	+=LastResults[k].ResultList[n].RotatedIndex;
					Results.ResultList[i].ZoomSizeIndex	+=LastResults[k].ResultList[n].ZoomSizeIndex;
					HCount++;
				}
			}
		}
		if(HCount!=0){
			Results.ResultList[i].DiffX			/=HCount;
			Results.ResultList[i].DiffY			/=HCount;
			Results.ResultList[i].ResultPosX	/=HCount;
			Results.ResultList[i].ResultPosY	/=HCount;
			Results.ResultList[i].RotatedIndex	/=HCount;
			Results.ResultList[i].ZoomSizeIndex	/=HCount;
			Results.ResultCount++;
		}
	}
		
	//for(int i=0;i<Results.ResultCount;i++){
	//	int	HCount=1;
	//	for(int k=0;k<LastResultCount;k++){
	//		for(int n=0;n<LastResults[k].ResultCount;n++){
	//			if(LastResults[k].ResultList[n].IndexMasterPos==Results.ResultList[i].IndexMasterPos){
	//				Results.ResultList[i].DiffX			+=LastResults[k].ResultList[n].DiffX;
	//				Results.ResultList[i].DiffY			+=LastResults[k].ResultList[n].DiffY;
	//				Results.ResultList[i].ResultPosX	+=LastResults[k].ResultList[n].ResultPosX;
	//				Results.ResultList[i].ResultPosY	+=LastResults[k].ResultList[n].ResultPosY;
	//				Results.ResultList[i].RotatedIndex	+=LastResults[k].ResultList[n].RotatedIndex;
	//				Results.ResultList[i].ZoomSizeIndex	+=LastResults[k].ResultList[n].ZoomSizeIndex;
	//				HCount++;
	//			}
	//		}
	//	}
	//	Results.ResultList[i].DiffX			/=HCount;
	//	Results.ResultList[i].DiffY			/=HCount;
	//	Results.ResultList[i].ResultPosX	/=HCount;
	//	Results.ResultList[i].ResultPosY	/=HCount;
	//	Results.ResultList[i].RotatedIndex	/=HCount;
	//	Results.ResultList[i].ZoomSizeIndex	/=HCount;
	//}

	return _ER_true;
}
