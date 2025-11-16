#include "XBuslineInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XAlgorithmDLL.h"

void	MatrixBuffCopyWindow(BYTE **MapSrc,int SrcXLen,int SrcYLen
						,int Px,int Py
						,BYTE **DstMap,int DstXLen,int DstYLen
						,int DstMerginX,int DstMerginY);

static	int	DbgPx=4350;
static	int	DbgPy=1000;
static	int	DbgD=0;

//==================================================================================================

BuslineItem::BuslineItem(void)
{
	BMap		=NULL;
	BMapOpen	=NULL;
	BMapShort	=NULL;
	TmpMap1		=NULL;
	TmpMap2		=NULL;
	BMapXByte	=0;
	BMapXLen	=0;
	BMapYLen	=0;
	AVector		=NULL;
	MerginX		=0;
	MerginY		=0;
}
BuslineItem::~BuslineItem(void)
{
	if(BMap!=NULL){
		DeleteMatrixBuff(BMap,BMapYLen);
		BMap=NULL;
	}
	if(BMapOpen !=NULL){
		DeleteMatrixBuff(BMapOpen,BMapYLen);
		BMapOpen =NULL;
	}
	if(BMapShort !=NULL){
		DeleteMatrixBuff(BMapShort,BMapYLen);
		BMapShort =NULL;
	}
	if(TmpMap1!=NULL){
		DeleteMatrixBuff(TmpMap1,BMapYLen);
		TmpMap1=NULL;
	}
	if(TmpMap2!=NULL){
		DeleteMatrixBuff(TmpMap2,BMapYLen);
		TmpMap2=NULL;
	}

	BMapXByte=0;
	BMapXLen=0;
	BMapYLen=0;
}

void	BuslineItem::CreateBinarizedArea(BuslineLibrary &Lib)
{
	BinarizedAreas.RemoveAll();
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	L=Lib.BinarizedLength;
	int	WNumb=(W-L/4)*4/L/3+1;
	int	HNumb=(H-L/4)*4/L/3+1;

	MerginX=(WNumb*L*3/4+L/4-W)/2;
	MerginY=(HNumb*L*3/4+L/4-H)/2;
	int	MinX=GetArea().GetMinX();
	int	MinY=GetArea().GetMinY();
	for(int xn=0;xn<WNumb;xn++){
		for(int yn=0;yn<HNumb;yn++){
			int	x1=MinX-MerginX+L*xn*3/4;
			int	y1=MinY-MerginY+L*yn*3/4;
			int	x2=x1+L;
			int	y2=y1+L;
			if(GetArea().CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==false)
				continue;
			FlexArea	ALeftTop	=GetArea();
			FlexArea	ARightTop	=GetArea();
			FlexArea	ALeftBottom	=GetArea();
			FlexArea	ARightBottom=GetArea();
			ALeftTop	.ClipArea(x1,y1,x1+L/2,y1+L/2);
			ARightTop	.ClipArea(x2-L/2,y1,x2,y1+L/2);
			ALeftBottom	.ClipArea(x1,y2-L/2,x1+L/2,y2);
			ARightBottom.ClipArea(x2-L/2,y2-L/2,x2,y2);
			int64	DLeftTop	=ALeftTop.GetPatternByte();
			int64	DRightTop	=ARightTop.GetPatternByte();
			int64	DLeftBottom	=ALeftBottom.GetPatternByte();
			int64	DRightBottom=ARightBottom.GetPatternByte();
			if(DLeftTop+DRightTop==0){
				y1+=L/4;
				y2+=L/4;
			}
			if(DLeftBottom+DRightBottom==0){
				y1-=L/4;
				y2-=L/4;
			}
			if(DLeftTop+DLeftBottom==0){
				x1+=L/4;
				x2+=L/4;
			}
			if(DRightTop+DRightBottom==0){
				x1-=L/4;
				x2-=L/4;
			}
			if(x2<=0 || GetDotPerLine()<=x1 || y2<=0 || GetMaxLines()<=y1)
				continue;
			if(x1<0){
				x2+=-x1;
				x1=0;
			}
			if(y1<0){
				y2+=-y1;
				y1=0;
			}
			if(GetDotPerLine()<x2){
				x1-=x2-GetDotPerLine();
				x2=GetDotPerLine();
			}
			if(GetMaxLines()<y2){
				y1-=y2-GetMaxLines();
				y2=GetMaxLines();
			}

			AreaWithBrightness	*a=new AreaWithBrightness();
			a->SetRectangle(x1,y1,x2,y2);
			a->ClipArea(GetArea());
			BinarizedAreas.AppendList(a);
		}
	}
	int	MinArea=L*L/10;
	for(AreaWithBrightness  *a=BinarizedAreas.GetFirst();a!=NULL;){
		AreaWithBrightness  *NextA=a->GetNext();
		if(a->GetPatternByte()<MinArea){
			BinarizedAreas.RemoveList(a);
			for(AreaWithBrightness  *b=BinarizedAreas.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->CheckOverlap(a)==true){
					*b+=*a;
					break;
				}
			}
			delete	a;
		}
		a=NextA;
	}
}
void	BuslineItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	BuslineItem	*ASrc=dynamic_cast<BuslineItem *>(src);
	if(ASrc!=NULL){
		MerginX	=ASrc->MerginX;
		MerginY	=ASrc->MerginY;
	}
}

ExeResult	BuslineItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true
	|| (GetMasterBuff().IsNull()==false && GetMasterBuff().IsChanged()==true)){
		if(BMap!=NULL){
			DeleteMatrixBuff(BMap,BMapYLen);
			BMap=NULL;
			BMapYLen=0;
		}
		if(BMapOpen !=NULL){
			DeleteMatrixBuff(BMapOpen,BMapYLen);
			BMapOpen =NULL;
		}
		if(BMapShort !=NULL){
			DeleteMatrixBuff(BMapShort,BMapYLen);
			BMapShort =NULL;
		}
		if(TmpMap1!=NULL){
			DeleteMatrixBuff(TmpMap1,BMapYLen);
			TmpMap1=NULL;
		}
		if(TmpMap2!=NULL){
			DeleteMatrixBuff(TmpMap2,BMapYLen);
			TmpMap2=NULL;
		}

		BMapXLen	=GetArea().GetWidth()+BuslineAreaMergin*2;
		BMapXByte	=(BMapXLen+7)/8;
		BMapYLen	=GetArea().GetHeight()+BuslineAreaMergin*2;

		BMap		=MakeMatrixBuff(BMapXByte,BMapYLen);
		BMapOpen	=MakeMatrixBuff(BMapXByte,BMapYLen);
		BMapShort	=MakeMatrixBuff(BMapXByte,BMapYLen);
		TmpMap1		=MakeMatrixBuff(BMapXByte,BMapYLen);
		TmpMap2		=MakeMatrixBuff(BMapXByte,BMapYLen);

		int	cx,cy;
		GetCenter(cx,cy);
		AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
		if(AVector!=NULL){
			AVector->Set(this);
		}
		BinarizedAreas.RemoveAll();
		MasterAreas.RemoveAll();

		AlgorithmLibraryLevelContainer	* Lib=GetLibFromManagedCacheLib();
		if(Lib==NULL){
			AlgorithmLibraryContainer	*Container=GetLibraryContainer();
			Lib=new AlgorithmLibraryLevelContainer(Container);
			GetLibrary(*Lib);
		}
		BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(Lib->GetLibrary());
		CreateBinarizedArea(*ALib);
		const	BuslineThreshold	*RThr=GetThresholdR();
		if(RThr->CompareToMaster==true){
			ImageBuffer	&Buff=GetMasterBuff();
			MakeBMap(Buff,0,0,RThr->Darkside);

			PureFlexAreaListContainer Blocks;
			PickupFlexArea(BMap ,BMapXByte,BMapXLen,BMapYLen ,Blocks);
			RegulatePureFlexAreaList(Blocks);
			for(PureFlexAreaList *a=Blocks.GetFirst();a!=NULL;a=a->GetNext()){
				PureFlexAreaList	*d=new PureFlexAreaList();
				*d=*a;
				MasterAreas.AppendList(d);
			}
		}
		
		delete	Lib;
		MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
	}
	return _ER_true;
}

ExeResult	BuslineItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
	NGDotOpen	=0;
	NGDotShort	=0;
	return _ER_true;
}

ExeResult	BuslineItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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
	ImageBuffer	&Buff=GetTargetBuff();
	MakeBMap(Buff,mx,my,GetThresholdR()->Darkside);

	short	Error=0;

	ExecuteProcessingCompareToMaster(Buff,Res,mx,my,Error);
	ExecuteProcessingCheckShort(Buff,Res,mx,my,Error);
	ExecuteProcessingCheckOpen (Buff,Res,mx,my,Error);
	if(Error!=0){
		Res->SetError(2);
		}
	else
		Res->SetError(1);
	return _ER_true;
}

void	BuslineItem::MakeBMap(void)
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
	ImageBuffer	&Buff=GetTargetBuff();
	MakeBMap(Buff,mx,my,GetThresholdR()->Darkside);
}

void	BuslineItem::ClearBMap(void)
{
	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
}

void	BuslineItem::ExecuteProcessingCompareToMaster(ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error)
{
	const	BuslineThreshold	*RThr=GetThresholdR();
	if(RThr->CompareToMaster==false)
		return;
	int	SearchDot=RThr->SearchDotToMaster;
	int	Px=GetArea().GetMinX();
	int	Py=GetArea().GetMinY();
	int	MinDx=0;
	int	MinDy=0;
	int	LMinDx=0;
	int	LMinDy=0;
	int	DMin=30000*30000;
	if(SearchDot!=0){
		for(int dy=-SearchDot;dy<=SearchDot;dy+=2){
			for(int dx=-SearchDot;dx<=SearchDot;dx+=2){
				MatrixBuffCopy	(BMapOpen,BMapXByte,BMapYLen
								,(const BYTE **)BMap	,BMapXByte,BMapYLen);
				for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeNotBitData(BMapOpen,BMapXLen,BMapYLen,mx+dx ,my+dy);
				}
				int	D=GetBitCount((const BYTE **)BMapOpen,BMapXByte,BMapYLen);
				if(DMin>D){
					DMin=D;
					MinDx=dx;
					MinDy=dy;
				}
			}
		}
		for(int dy=-1+MinDy;dy<=+1+MinDy;dy++){
			for(int dx=-1+MinDx;dx<=+1+MinDx;dx++){
				if(dx==MinDx && dy==MinDy)
					continue;
				MatrixBuffCopy	(BMapOpen,BMapXByte,BMapYLen
								,(const BYTE **)BMap	,BMapXByte,BMapYLen);
				for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeNotBitData(BMapOpen,BMapXLen,BMapYLen,mx+MinDx+dx ,my+MinDy+dy);
				}
				int	D=GetBitCount((const BYTE **)BMapOpen,BMapXByte,BMapYLen);
				if(DMin>D){
					DMin=D;
					LMinDx=dx;
					LMinDy=dy;
				}
			}
		}
	}

	if(DMin>0){
		MatrixBuffCopy	(BMapOpen			,BMapXByte,BMapYLen
						,(const BYTE **)BMap,BMapXByte,BMapYLen);
		for(int dy=-1;dy<=1;dy++){
			for(int dx=-1;dx<=1;dx++){
				for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeNotBitData(BMapOpen,BMapXLen,BMapYLen,mx+MinDx+LMinDx ,my+MinDy+LMinDy);
				}
			}
		}
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BMapOpen,BMapXByte,BMapXLen,BMapYLen,FPack);
		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
			int64	NGDot=p->GetPatternByte();
			if(NGDot<=1)
				continue;
			int	Cx,Cy;
			p->GetCenter(Cx,Cy);
			if(OverlapEffective(Cx,Cy)==true){
				ResultPosList	*r=new ResultPosList(Cx+GetArea().GetMinX()-BuslineAreaMergin
													,Cy+GetArea().GetMinY()-BuslineAreaMergin ,MinDx+LMinDx,MinDy+LMinDy);
				r->result =0x10000+0x1;	
				r->SetResult1(NGDot);
				r->SetResult2(0);
				r->NGShape.SuckFrom(*p);
				r->NGShape.MoveToNoClip(GetArea().GetMinX()-BuslineAreaMergin ,GetArea().GetMinY()-BuslineAreaMergin);
				Res->AddPosList(r);
				Error |= 0x01;	//
			}
		}
	}


	MinDx=0;
	MinDy=0;
	LMinDx=0;
	LMinDy=0;
	DMin=0;
	if(SearchDot!=0){
		for(int dy=-SearchDot;dy<=SearchDot;dy+=2){
			for(int dx=-SearchDot;dx<=SearchDot;dx+=2){
				MatrixBuffClear	(BMapOpen,0 ,BMapXByte,BMapYLen);
				for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeBitData(BMapOpen,mx+dx ,my+dy);
				}
				MatrixBuffAnd(BMapOpen,(const BYTE **)BMap,BMapXByte,BMapYLen);
				int	D=GetBitCount((const BYTE **)BMapOpen,BMapXByte,BMapYLen);
				if(DMin<D){
					DMin=D;
					MinDx=dx;
					MinDy=dy;
				}
			}
		}
		for(int dy=-1+MinDy;dy<=+1+MinDy;dy++){
			for(int dx=-1+MinDx;dx<=+1+MinDx;dx++){
				if(dx==MinDx && dy==MinDy)
					continue;
				MatrixBuffClear	(BMapOpen,0 ,BMapXByte,BMapYLen);
				for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
					a->MakeBitData(BMapOpen,mx+MinDx+dx ,my+MinDy+dy);
				}
				MatrixBuffAnd(BMapOpen,(const BYTE **)BMap,BMapXByte,BMapYLen);
				int	D=GetBitCount((const BYTE **)BMapOpen,BMapXByte,BMapYLen);
				if(DMin<D){
					DMin=D;
					LMinDx=dx;
					LMinDy=dy;
				}
			}
		}
	}

	MatrixBuffClear	(BMapOpen,0 ,BMapXByte,BMapYLen);
	for(PureFlexAreaList *a=MasterAreas.GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(BMapOpen,mx+MinDx+LMinDx ,my+MinDy+LMinDy);
	}
	for(int dy=-1;dy<=1;dy++){
		for(int dx=-1;dx<=1;dx++){
			MatrixBuffShiftBitCopy	(TmpMap1			,BMapXLen ,BMapYLen
									,(const BYTE **)BMap,BMapXLen ,BMapYLen
									,dx ,dy);		
			MatrixBuffNotAnd(BMapOpen,(const BYTE **)TmpMap1,BMapXByte,BMapYLen);
		}
	}

	int	D=GetBitCount((const BYTE **)BMapOpen,BMapXByte,BMapYLen);
	if(D>0){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BMapOpen,BMapXByte,BMapXLen,BMapYLen,FPack);
		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
			int64	NGDot=p->GetPatternByte();
			if(NGDot<=1)
				continue;
			int	Cx,Cy;
			p->GetCenter(Cx,Cy);
			int	PeakL,PeakH;
			if(p->GetPeak(Buff,GetArea().GetMinX()-BuslineAreaMergin,GetArea().GetMinY()-BuslineAreaMergin,	PeakL,PeakH)==true){
				AreaWithBrightness	*B=BinarizedAreas.SearchArea(Cx+GetArea().GetMinX()-BuslineAreaMergin ,Cy+GetArea().GetMinY()-BuslineAreaMergin);
				if(B!=NULL){
					int	DarkL,DarkH;
					int	LightL,LightH;
					if(RThr->Darkside==true){
						DarkL	=B->PeakL-RThr->BrightnessWidthInsideL;
						DarkH	=B->PeakL+RThr->BrightnessWidthInsideH;
						LightL	=B->PeakH-RThr->BrightnessWidthOutsideL;
						LightH	=B->PeakH+RThr->BrightnessWidthOutsideH;
					}
					else{
						DarkL	=B->PeakL-RThr->BrightnessWidthOutsideL;
						DarkH	=B->PeakL+RThr->BrightnessWidthOutsideH;
						LightL	=B->PeakH-RThr->BrightnessWidthInsideL;
						LightH	=B->PeakH+RThr->BrightnessWidthInsideH;
					}
					if((PeakL<DarkL || DarkH<PeakH) && (PeakL<LightL || LightH<PeakH)){

						int64	NGDot=p->GetPatternByte();
						if(NGDot<RThr->MinGap-4)
							continue;
						if(OverlapEffective(Cx,Cy)==true){
							ResultPosList	*r=new ResultPosList(Cx+GetArea().GetMinX()-BuslineAreaMergin
																,Cy+GetArea().GetMinY()-BuslineAreaMergin ,MinDx+LMinDx,MinDy+LMinDy);
							r->result =0x10000+0x1;	
							r->SetResult1(NGDot);
							r->SetResult2(0);
							r->NGShape.SuckFrom(*p);
							r->NGShape.MoveToNoClip(GetArea().GetMinX()-BuslineAreaMergin ,GetArea().GetMinY()-BuslineAreaMergin);
							Res->AddPosList(r);
							Error |= 0x01;	//
						}
					}
				}
			}
		}
	}
}

void	BuslineItem::ExecuteProcessingCheckShort(ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error)
{
	MatrixBuffCopy	(TmpMap2					,BMapXByte,BMapYLen
					,(const BYTE **)BMap	,BMapXByte,BMapYLen);
	const	BuslineThreshold	*RThr=GetThresholdR();

	GetLayersBase()->ThinAreaN(TmpMap2
				,TmpMap1
				,BMapXByte,BMapYLen
				,RThr->MinGap/2);
	GetLayersBase()->FatAreaN(TmpMap2
				,TmpMap1
				,BMapXByte,BMapYLen
				,RThr->MinGap/2);
	
	int	OKShortDot=RThr->MinGap*RThr->OKShortRate/100;
	if(OKShortDot<RThr->WidthToIgnoreEdge)
		OKShortDot=RThr->WidthToIgnoreEdge;
	GetLayersBase()->FatAreaN(TmpMap2
				,TmpMap1
				,BMapXByte,BMapYLen
				,OKShortDot);

	MatrixBuffCopy	(BMapShort	,BMapXByte,BMapYLen
					,(const BYTE **)BMap	,BMapXByte,BMapYLen);
	MatrixBuffNotAnd(BMapShort,(const BYTE **)TmpMap2,BMapXByte,BMapYLen);
	MaskEdge(BMapShort, BMapXLen, BMapYLen
			, BuslineAreaMergin*2+RThr->MinGap
			, BuslineAreaMergin*2+RThr->MinGap
			, BuslineAreaMergin*2+RThr->MinGap
			, BuslineAreaMergin*2+RThr->MinGap);

	PureFlexAreaListContainer FPack;

	PickupFlexArea(BMapShort,BMapXByte,BMapXLen,BMapYLen,FPack);
	int	MinNGSize=min(RThr->MinGap/2, RThr->MinSize);
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetWidth()<MinNGSize && p->GetHeight()<MinNGSize)
			continue;
		int64	NGDot = p->GetPatternByte();
		if (NGDot<RThr->MinArea || RThr->MaxArea<NGDot)
			continue;
		int	Cx,Cy;
		p->GetCenter(Cx,Cy);
		if(hypot(Cx+GetArea().GetMinX()-DbgPx,Cy+GetArea().GetMinY()-DbgPy)<30)
			DbgD++;
		int	PeakL,PeakH;
		if(p->GetPeak(Buff,GetArea().GetMinX()-BuslineAreaMergin,GetArea().GetMinY()-BuslineAreaMergin,	PeakL,PeakH)==true){
			AreaWithBrightness	*B=BinarizedAreas.SearchArea(Cx+GetArea().GetMinX()-BuslineAreaMergin ,Cy+GetArea().GetMinY()-BuslineAreaMergin);
			if(B!=NULL){
				int	DarkL=0,DarkH=255;
				int	LightL=0,LightH=255;
				bool	Judge=false;
				if(RThr->Darkside==true){
					LightL	=B->PeakH-RThr->BrightnessWidthOutsideL;
					LightH	=B->PeakH+RThr->BrightnessWidthOutsideH;
					if(PeakL<LightL || LightH<PeakH)
						Judge=true;
				}
				else{
					DarkL=B->PeakL-RThr->BrightnessWidthOutsideL;
					DarkH=B->PeakL+RThr->BrightnessWidthOutsideH;
					if(PeakL<DarkL || DarkH<PeakH)
						Judge=true;
				}
				if(Judge==true){
					if(NGDot<RThr->MinGap-4)
						continue;
					if(OverlapEffective(Cx+GetArea().GetMinX()-BuslineAreaMergin,Cy+GetArea().GetMinY()-BuslineAreaMergin)==true && IsOnTheEdge(p,GetArea().GetMinX()-BuslineAreaMergin,GetArea().GetMinY()-BuslineAreaMergin)==false){
						ResultPosList	*r=new ResultPosList(Cx+GetArea().GetMinX()-BuslineAreaMergin
															,Cy+GetArea().GetMinY()-BuslineAreaMergin,mx,my);
						r->result =0x10000+0x2;	
						r->SetResult1(NGDot);
						r->SetResult2(0);
						r->NGShape.SuckFrom(*p);
						r->NGShape.MoveToNoClip(GetArea().GetMinX()-BuslineAreaMergin ,GetArea().GetMinY()-BuslineAreaMergin);
						Res->AddPosList(r);
						Error |= 0x02;	//
						NGDotShort+=NGDot;
					}
				}
			}
		}
	}
}

bool	BuslineItem::IsOnTheEdge(FlexArea *f,int dx ,int dy)
{
	FlexArea	A;
	A=*f;
	A.MoveToNoClip(dx-1,dy);
	A-=GetArea();
	if(A.GetPatternByte()>0)
		return true;
	A=*f;
	A.MoveToNoClip(dx+1,dy);
	A-=GetArea();
	if(A.GetPatternByte()>0)
		return true;
	A=*f;
	A.MoveToNoClip(dx,dy+1);
	A-=GetArea();
	if(A.GetPatternByte()>0)
		return true;
	A=*f;
	A.MoveToNoClip(dx,dy-1);
	A-=GetArea();
	if(A.GetPatternByte()>0)
		return true;
	return false;
}

void	BuslineItem::ExecuteProcessingCheckOpen (ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error)
{
	MatrixBuffCopy	(BMapOpen,BMapXByte,BMapYLen
					,(const BYTE **)BMap	,BMapXByte,BMapYLen);
	const	BuslineThreshold	*RThr=GetThresholdR();

	GetLayersBase()->FatAreaN(BMapOpen
				,TmpMap1
				,BMapXByte,BMapYLen
				,RThr->MinWidth/2);
	GetLayersBase()->ThinAreaN(BMapOpen
				,TmpMap1
				,BMapXByte,BMapYLen
				,RThr->MinWidth/2);
	
	MatrixBuffCopy	(TmpMap2				,BMapXByte,BMapYLen
					,(const BYTE **)BMapOpen,BMapXByte,BMapYLen);

	MatrixBuffNotAnd(BMapOpen,(const BYTE **)BMap,BMapXByte,BMapYLen);
	MatrixBuffNot	(TmpMap2 ,BMapXByte,BMapYLen);
	GetLayersBase()->FatAreaN(TmpMap2
				,TmpMap1
				,BMapXByte,BMapYLen
				,RThr->WidthToIgnoreEdge);

	MatrixBuffNotAnd(BMapOpen,(const BYTE **)TmpMap2,BMapXByte,BMapYLen);
	MaskEdge(BMapOpen, BMapXLen, BMapYLen
			, BuslineAreaMergin*2+RThr->MinWidth
			, BuslineAreaMergin*2+RThr->MinWidth
			, BuslineAreaMergin*2+RThr->MinWidth
			, BuslineAreaMergin*2+RThr->MinWidth);

	int	MinNGSize= min(RThr->MinWidth/2, RThr->MinSize);
	PureFlexAreaListContainer FPack;
	//PickupFlexArea(TmpMap3 ,BMapXByte,BMapXLen,BMapYLen,FPack);
	PickupFlexArea(BMapOpen,BMapXByte,BMapXLen,BMapYLen,FPack);
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		int	Cx,Cy;
		p->GetCenter(Cx,Cy);
		if(hypot(Cx+GetArea().GetMinX()-DbgPx,Cy+GetArea().GetMinY()-DbgPy)<30)
			DbgD++;
		if(p->GetWidth()<MinNGSize && p->GetHeight()<MinNGSize)
			continue;

		int64	NGDot = p->GetPatternByte();
		if (NGDot < RThr->MinArea || RThr->MaxArea < NGDot)
			continue;

		int	PeakL,PeakH;
		if(p->GetPeak(Buff,GetArea().GetMinX()-BuslineAreaMergin,GetArea().GetMinY()-BuslineAreaMergin,	PeakL,PeakH)==true){
			AreaWithBrightness	*B=BinarizedAreas.SearchArea(Cx+GetArea().GetMinX()-BuslineAreaMergin ,Cy+GetArea().GetMinY()-BuslineAreaMergin);
			if(B!=NULL){
				int	DarkL=0,DarkH=255;
				int	LightL=0,LightH=255;
				bool	Judge=false;
				if(RThr->Darkside==true){
					DarkL	=B->PeakL-RThr->BrightnessWidthInsideL;
					DarkH	=B->PeakL+RThr->BrightnessWidthInsideH;
					if(PeakL<DarkL || DarkH<PeakH)
						Judge=true;
				}
				else{
					LightL	=B->PeakH-RThr->BrightnessWidthInsideL;
					LightH	=B->PeakH+RThr->BrightnessWidthInsideH;
					if(PeakL<LightL || LightH<PeakH)
						Judge=true;
				}
				if(Judge==true){
					if(NGDot<RThr->MinWidth-RThr->WidthToIgnoreEdge*2)
						continue;
					if(OverlapEffective(Cx+GetArea().GetMinX()-BuslineAreaMergin,Cy+GetArea().GetMinY()-BuslineAreaMergin)==true && CheckOpenInPoint(Cx,Cy)==true){
						ResultPosList	*r=new ResultPosList(Cx+GetArea().GetMinX()-BuslineAreaMergin
															,Cy+GetArea().GetMinY()-BuslineAreaMergin ,mx,my);
						r->result =0x10000+0x3;	
						r->SetResult1(NGDot);
						r->SetResult2(0);
						r->NGShape.SuckFrom(*p);
						r->NGShape.MoveToNoClip(GetArea().GetMinX()-BuslineAreaMergin ,GetArea().GetMinY()-BuslineAreaMergin);
						Res->AddPosList(r);
						Error |= 0x04;	//
						NGDotOpen=NGDot;
					}
				}
			}
		}
	}
}

void	BuslineItem::MaskEdge(BYTE **Map, int XLen, int YLen
							, int LMerginLeft, int LMerginTop, int LMerginRight, int LMerginBottom)
{
	int	XByte=(XLen+7)/8;
	for(int y=0;y< LMerginTop && y<YLen;y++){
		BYTE	*p=Map[y];
		memset(p,0,XByte);
	}
	for (int y = YLen-1- LMerginBottom; y<YLen; y++) {
		if(y>=0){
			BYTE* p = Map[y];
			memset(p, 0, XByte);
		}
	}
	for(int y=0;y<YLen;y++){
		BYTE* p = Map[y];
		for(int x=0;x< LMerginLeft && x< XLen;x++){
			SetBmpBitOnY0(p, x);
		}
		for (int x = XLen-1- LMerginRight; x < XLen; x++) {
			if(x>=0){
				SetBmpBitOnY0(p, x);
			}
		}
	}
}

bool	BuslineItem::CheckOpenInPoint(int Px, int Py)
{
	bool	Ret=false;
	const	BuslineThreshold	*RThr=GetThresholdR();

	int	W=RThr->MinWidth*3+8+8;
	int	H=RThr->MinWidth*3+8+8;
	int	WXByte=(W+7)/8;
	BYTE	TmpLBuff2[10000];
	BYTE	**LMap2=MakeMatrixBuff(WXByte,H,TmpLBuff2,sizeof(TmpLBuff2));
	MatrixBuffClear	(LMap2 ,0 ,WXByte,H);
	MatrixBuffCopyWindow(TmpMap2,BMapXLen,BMapYLen
						,Px-W/2,Py-H/2
						,LMap2,W,H
						,8,8);

	BYTE	TmpLBuff[10000];
	BYTE	**LMap=MakeMatrixBuff(WXByte,H,TmpLBuff,sizeof(TmpLBuff));
	MatrixBuffClear	(LMap ,0 ,WXByte,H);
	MatrixBuffCopyWindow(BMap,BMapXLen,BMapYLen
						,Px-W/2,Py-H/2
						,LMap,W,H
						,8,8);
	/*
	PureFlexAreaListContainer FPack;
	PickupFlexArea(LMap ,WXByte,W,H,FPack);
	PureFlexAreaList *MaxF=NULL;
	int64		MaxArea=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(MaxArea<f->GetPatternByte()){
			MaxArea	=f->GetPatternByte();
			MaxF	=f;
		}
	}
	if(MaxF==NULL){
		DeleteMatrixBuff(LMap ,TmpLBuff ,H);
		DeleteMatrixBuff(LMap2,TmpLBuff2,H);
		return Ret;
	}
	MatrixBuffClear	(LMap ,0 ,WXByte,H);
	MaxF->MakeBitData(LMap,W,H);
	*/
	MatrixBuffNotAnd(LMap ,(const BYTE **)LMap2,WXByte,H);

	int	OKNickWidth1Side=RThr->MinWidth*RThr->OKNickRate/200;
	for(int i=0;i<OKNickWidth1Side;i++){
		::ThinArea(LMap
				,TmpMap1
				,WXByte,H);
	}
	PureFlexAreaListContainer GPack;
	PickupFlexArea(LMap ,WXByte,W,H,GPack);
	if(GPack.GetCount()!=1){
		Ret=true;
	}
	DeleteMatrixBuff(LMap ,TmpLBuff ,H);
	DeleteMatrixBuff(LMap2,TmpLBuff2,H);
	return Ret;
}

void	MatrixBuffCopyWindow(BYTE **MapSrc,int SrcXLen,int SrcYLen
						,int Px,int Py
						,BYTE **DstMap,int DstXLen,int DstYLen
						,int DstMerginX,int DstMerginY)
{
	for(int y=DstMerginY;y<DstYLen-DstMerginY;y++){
		int	Y=y+Py;
		if(Y<0)
			continue;
		if(Y>=SrcYLen)
			break;
		int	LeftX=Px;
		int	StartPoint=0;
		int	RightX=Px+DstXLen;
		if(LeftX<0){
			StartPoint=-LeftX;
			LeftX=0;
		}
		else if(LeftX>=SrcXLen)
			continue;
		if(RightX<0)
			continue;
		else if(RightX>=SrcXLen){
			RightX=SrcXLen;
		}
		BYTE	*s=MapSrc[Y];
		BYTE	*d=DstMap[y];
		int	x=StartPoint;
		for(int X=LeftX;X<RightX;X++,x++){
			if(x<DstMerginX)
				continue;
			if(DstXLen-DstMerginX<=x)
				break;
			if(GetBmpBitOnY(s,X)!=0){
				SetBmpBitOnY1(d,x);
			}
		}
	}
}

void	BuslineItem::RegulatePureFlexAreaList(PureFlexAreaListContainer &FPack)
{
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
		PureFlexAreaList *N=a->GetNext();
		if(a->GetPatternByte()<5){
			FPack.RemoveList(a);
			delete	a;
		}
		a=N;
	}
}
bool	BuslineItem::OverlapEffective(int cx,int cy)
{
	if(GetArea().IsInclude(cx,cy)==true){
		return true;
	}
	return false;
}

int		BuslineItem::GetBinarizedBrightness(ImageBuffer &Buff,int mx ,int my
											,AreaWithBrightness &BArea)
{
	const	BuslineThreshold	*RThr=GetThresholdR();

	if(RThr->AutoBinarize==true)
		return RThr->ReferredBrightness;
	int		CenterBright;
	int	BrList[256];
	memset(BrList,0,sizeof(BrList));
	BArea.MakeBrightList(BrList ,GetDotPerLine(),GetMaxLines(),Buff,mx,my);
	int	C=RThr->ReferredBrightness;

	int	AvBrList[256];
	for(int i=0;i<256;i++){
		AvBrList[i]=0;
		for(int k=-2;k<=2;k++){
			int	j=i+k;
			if(j<0)
				j=0;
			if(j>255)
				j=255;
			AvBrList[i]+=BrList[j];
		}
	}

	int	LMax=0;
	int	LPeak=0;
	for(int k=C;k>=0;k--){
		if(1<k && k<254){
			if(((AvBrList[k-1]<=AvBrList[k] && AvBrList[k]>=AvBrList[k+1])
			 || (AvBrList[k-2]<=AvBrList[k-1] && AvBrList[k+1]>=AvBrList[k+2]))
			&& AvBrList[k]>LMax){
				LMax=AvBrList[k];
				LPeak=k;
			}
		}
	}
	int	HMax=0;
	int	HPeak=255;
	for(int k=C;k<256;k++){
		if(1<k && k<254){
			if((AvBrList[k-1]<=AvBrList[k  ] && AvBrList[k  ]>=AvBrList[k+1])
			|| (AvBrList[k-2]<=AvBrList[k-1] && AvBrList[k+1]>=AvBrList[k+2])){
				if(AvBrList[k]>HMax){
					HMax=AvBrList[k];
					HPeak=k;
				}
			}
		}
	}
	//谷が複数ある時、より基準値に近いほうを採用する
	int	DiffC=0x7FFFFFFF;
	CenterBright=(LPeak+HPeak+1)/2;
	for(int k=LPeak+2;k<HPeak-2;k++){
		if(1<k && k<254){
			if(((AvBrList[k-1]>=AvBrList[k  ]) && (AvBrList[k  ]<=AvBrList[k+1]))
			|| ((AvBrList[k-2]>=AvBrList[k-1]) && (AvBrList[k+1]<=AvBrList[k+2]))){
				int	H=abs(k - RThr->ReferredBrightness);
				if(H<DiffC){
					DiffC=H;
					CenterBright=k;
				}
			}
		}
	}
	BArea.ThresholdBrightness	=CenterBright;
	BArea.PeakH	=HPeak;
	BArea.PeakL	=LPeak;

	return CenterBright;
}

void		BuslineItem::MakeBMap(ImageBuffer &Buff,int mx ,int my ,bool DarkSide)
{
	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
	const	BuslineThreshold	*RThr=GetThresholdR();
	int	Px=GetArea().GetMinX();
	int	Py=GetArea().GetMinY();
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	for(AreaWithBrightness *s=BinarizedAreas.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->IsInclude(DbgPx,DbgPy)==true)
			DbgD++;
		int	CenterBright=GetBinarizedBrightness(Buff,mx ,my ,*s);
		if(CenterBright<0){
			continue;
		}

	    for(int i=0;i<s->GetFLineLen();i++){
		    int x1  =s->GetFLineLeftX(i)+mx;
	        int Numb=s->GetFLineNumb(i);
			int	y	=s->GetFLineAbsY(i)+my;
			if(0<=y && y<GetMaxLines()){
				if(x1<0){
					Numb=Numb+x1;
					x1=0;
				}
				if(x1+Numb>=GetDotPerLine()){
					Numb=GetDotPerLine()-x1;
				}
				if(Numb>0){
					BYTE	*s=Buff.GetY(y);
					int	MapY=y-my-Py+BuslineAreaMergin;
					if(MapY<0  || H<=MapY)
						continue;
					BYTE	*d=BMap[MapY];
					if(DarkSide==true){
						for(int j=0;j<Numb;j++){
							int	x=x1+j;
							int	c=s[x];
							if(0<=c && c<=CenterBright){
								int	MapX=x-Px-mx+BuslineAreaMergin;
								if(MapX<0  || W<=MapX)
									continue;
								SetBmpBitOnY1(d,x-Px-mx+BuslineAreaMergin);
							}
						}
					}
					else{
						for(int j=0;j<Numb;j++){
							int	x=x1+j;
							int	c=s[x];
							if(CenterBright<=c && c<=256){
								int	MapX=x-Px-mx+BuslineAreaMergin;
								if(MapX<0  || W<=MapX)
									continue;
								SetBmpBitOnY1(d,x-Px-mx+BuslineAreaMergin);
							}
						}
					}
				}
			}
		}
	}
	if(RThr->ReduceNoise==true){
		::FatArea(BMap
				, BMapOpen
				, BMapXByte,BMapYLen);	
		::ThinArea(BMap
				, BMapOpen
				, BMapXByte,BMapYLen);	
		::ThinArea(BMap
				, BMapOpen
				, BMapXByte,BMapYLen);	
		::FatArea(BMap
				, BMapOpen
				, BMapXByte,BMapYLen);	
	}
	else{
		//微小ノイズの削除
		MatrixBuffCopy	(BMapOpen			,BMapXByte,BMapYLen
						,(const BYTE **)BMap,BMapXByte,BMapYLen);
		::FatArea(BMapOpen
				, TmpMap1
				, BMapXByte,BMapYLen);	
		::ThinArea(BMapOpen
				, TmpMap1
				, BMapXByte,BMapYLen);	
		MatrixBuffNotAnd(BMapOpen,(const BYTE **)BMap,BMapXByte,BMapYLen);
		PureFlexAreaListContainer GPack;
		PickupFlexArea(BMapOpen,BMapXByte,BMapXLen,BMapYLen,GPack);
		for(PureFlexAreaList *f=GPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetPatternByte()<5){
				f->MakeBitData(BMap,BMapXLen,BMapYLen);
			}
		}
	}

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BMap ,BMapXByte,BMapXLen,BMapYLen,FPack);
	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);

	PureFlexAreaListContainer BigPack;
	PureFlexAreaListContainer SmallPack;

	PureFlexAreaList *f;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		int64	Dots=f->GetPatternByte();
		if(RThr->MinArea<=Dots && Dots<=RThr->MaxArea){
			BigPack.AppendList(f);
		}
		else{
			SmallPack.AppendList(f);
		}
	}
	for(f=SmallPack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MakeBitData(BMap,BMapXLen,BMapYLen);
	}

	GetLayersBase()->FatAreaN(BMap
				, TmpMap1
				, BMapXByte,BMapYLen
				,RThr->MinGap/2);	

	PureFlexAreaListContainer SmallFatPack;
	PickupFlexArea(BMap ,BMapXByte,BMapXLen,BMapYLen,SmallFatPack);

	MatrixBuffClear(BMap,0,BMapXByte,BMapYLen);
	for(f=BigPack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MakeBitData(BMap,BMapXLen,BMapYLen);
	}

	MatrixBuffClear(BMapOpen,0,BMapXByte,BMapYLen);
	for(f=SmallFatPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->CheckOverlapBit(BMap,BMapXLen,BMapYLen)==true){
			f->MakeBitData(BMapOpen,BMapXLen,BMapYLen);
		}
	}
	for(int i=0;i<RThr->MinGap/2;i++){
		::ThinArea(BMapOpen
				, TmpMap1
				, BMapXByte,BMapYLen);	
	}
	MatrixBuffOr	(BMap ,(const BYTE **)BMapOpen, BMapXByte,BMapYLen);

	MatrixBuffClear(BMapOpen,0,BMapXByte,BMapYLen);
}

void	BuslineItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	BuslineDrawAttr	*BusAttr=dynamic_cast<BuslineDrawAttr *>(Attr);
	if(BusAttr!=NULL){
		if(BusAttr->DMode==BuslineDrawAttr::__Mode_PickupArea){
			QColor	Col(0,255,0,120);
			DrawBitImage(pnt, (const BYTE **)BMap ,BMapXLen,BMapXByte ,BMapYLen
					,movx ,movy ,ZoomRate
					,-GetArea().GetMinX()+BuslineAreaMergin,-GetArea().GetMinY()+BuslineAreaMergin
					,Col);
		}
		else if(BusAttr->DMode==BuslineDrawAttr::__Mode_TestOpen){
			QColor	Col(0,255,0,120);
			DrawBitImage(pnt, (const BYTE **)BMapOpen,BMapXLen,BMapXByte ,BMapYLen
					,movx ,movy ,ZoomRate
					,-GetArea().GetMinX()+BuslineAreaMergin,-GetArea().GetMinY()+BuslineAreaMergin
					,Col);
		}
		else if(BusAttr->DMode==BuslineDrawAttr::__Mode_TestShort){
			QColor	Col(0,255,0,120);
			DrawBitImage(pnt, (const BYTE **)BMapShort,BMapXLen,BMapXByte ,BMapYLen
					,movx ,movy ,ZoomRate
					,-GetArea().GetMinX()+BuslineAreaMergin,-GetArea().GetMinY()+BuslineAreaMergin
					,Col);
		}
		else if(BusAttr->DMode==BuslineDrawAttr::__Mode_ItemArea){
			AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
}
void	BuslineItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	Col(0,0,192,128);
	DrawBitImageOr(IData, (const BYTE **)BMap ,BMapXLen ,BMapXByte ,BMapYLen
					,MovX ,MovY ,ZoomRate
					,-GetArea().GetMinX()+BuslineAreaMergin ,-GetArea().GetMinY()+BuslineAreaMergin
					,Col);
	AlgorithmItemPLI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}


void	BuslineItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			BuslineInLayer	*Ly=dynamic_cast<BuslineInLayer *>(GetParentInLayer());
			UndoElement<BuslineInLayer>	*UPointer=new UndoElement<BuslineInLayer>(Ly,&BuslineInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			BuslineItem *src=(BuslineItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((BuslineItem *)Data)->GetLibID()){
			BuslineInLayer	*Ly=dynamic_cast<BuslineInLayer *>(GetParentInLayer());
			UndoElement<BuslineInLayer>	*UPointer=new UndoElement<BuslineInLayer>(Ly,&BuslineInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			BuslineItem *src=(BuslineItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}

}
void	BuslineItem::CopyThresholdOnly(BuslineItem &src)
{
	GetThresholdW()->CopyFrom(*((BuslineThreshold *)src.GetThresholdR()));
}

void	BuslineItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AreaWithBrightness	*B=BinarizedAreas.SearchArea(LocalX ,LocalY);
	if(B!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,B->ThresholdBrightness);
		::Save(&Buff,B->PeakL);
		::Save(&Buff,B->PeakH);
		AInd->Something=Buff.buffer();
	}
}