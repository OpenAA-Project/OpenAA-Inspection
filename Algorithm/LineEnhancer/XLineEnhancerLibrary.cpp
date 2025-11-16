#include "XLineEnhancer.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XImageProcess.h"


LineEnhancerLibrary::LineEnhancerLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	MaxDot=90000;
	MinDot=20;
	ShrinkDot=3;
	EmphasizeRate=1.0;
	Priority=100;
	MaxLineWidth=3;
	StepDot	=3;
	MaxSize	=500;
	MinSize	=50;
	SearchBlockWidth=2;
	SelfSearch	=4;
	LimitDot	=200;
}
LineEnhancerLibrary::~LineEnhancerLibrary(void)
{
}
bool	LineEnhancerLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=LineEnhancerVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxDot)==false)
		return false;
	if(::Save(f,MinDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(PickupColor.Save(f)==false)
		return false;
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,MaxLineWidth)==false)
		return false;
	if(::Save(f,StepDot)==false)
		return false;
	if(::Save(f,MaxSize)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,SearchBlockWidth)==false)
		return false;
	if(::Save(f,SelfSearch)==false)
		return false;
	if(::Save(f,LimitDot)==false)
		return false;
	return true;


}
bool	LineEnhancerLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MaxDot)==false)
		return false;
	if(::Load(f,MinDot)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(PickupColor.Load(f)==false)
		return false;
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,MaxLineWidth)==false)
		return false;
	if(::Load(f,StepDot)==false)
		return false;
	if(::Load(f,MaxSize)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,SearchBlockWidth)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,LimitDot)==false)
			return false;
	}
	return true;
}

LineEnhancerLibrary	&LineEnhancerLibrary::operator=(const AlgorithmLibrary &src)
{
	const LineEnhancerLibrary	*s=dynamic_cast<const LineEnhancerLibrary *>(&src);
	MaxDot			=s->MaxDot;
	MinDot			=s->MinDot;
	LimitDot		=s->LimitDot;
	ShrinkDot		=s->ShrinkDot;
	PickupColor		=s->PickupColor;
	EmphasizeRate	=s->EmphasizeRate;
	Priority		=s->Priority;
	StepDot			=s->StepDot;
	MaxSize			=s->MaxSize;
	MinSize			=s->MinSize;
	SearchBlockWidth=s->SearchBlockWidth;
	SelfSearch		=s->SelfSearch;
	return *this;
}


void	LineEnhancerLibrary::MakePickupTest(ImagePointerContainer &MasterImages
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot
									 ,int ModeOneLayer)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	ImageBuffer	*MasterImage=MasterImages[0];
	int	YNumb=min(YLen,MasterImage->GetHeight());
	int	XNumb=min(XLen,MasterImage->GetWidth());
	int	PickupL,PickupH;
	int	Page=0;
	if(GetLayerNumb(Page)==1){
		PickupColor.GetMonoColorRange(PickupL,PickupH);

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*src=MasterImage->GetY(y);
				BYTE	*dest=BmpPoint[y];
				int		c;
				for(int x=0;x<XNumb;x++,src++){
					c=*src;
					if(PickupL<=c && c<=PickupH){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(ModeOneLayer!=-1){
		ImageBuffer	*MasterImage=MasterImages[ModeOneLayer];
		PickupColor.GetMonoColorRange(PickupL,PickupH);

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*src=MasterImage->GetY(y);
				BYTE	*dest=BmpPoint[y];
				int		c;
				for(int x=0;x<XNumb;x++,src++){
					c=*src;
					if(PickupL<=c && c<=PickupH){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)>=3){
		PickupColor.MakeBitmap(MasterImages,BmpPoint,XLen ,YLen);
	}
	GetLayersBase()->StepProcessing(-1);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	for(int i=0;i<1;i++)
		ThinArea(BmpPoint,TmpData ,XByte, YLen);
	for(int i=0;i<1;i++)
		FatArea(BmpPoint,TmpData ,XByte, YLen);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);
	DeleteMatrixBuff(TmpData2,YLen);

	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[y],0,XByte);
	}
	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[YLen-y-1],0,XByte);
	}
	for(int y=OmitZoneDot;y<YLen-OmitZoneDot;y++){
		for(int x=0;x<OmitZoneDot;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
		for(int x=XLen-OmitZoneDot;x<XLen;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
	}

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	
	GetLayersBase()->StepProcessing(-1);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
	//					   ,XLen, YLen);

	GetLayersBase()->StepProcessing(-1);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen ,ShrinkDot);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
	MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		int64	DotN=a->GetPatternByte();
		int	W=a->GetWidth();
		int	H=a->GetHeight();
		int	MinLen=min(W,H);
		int	MaxLen=max(W,H);
		if(MinDot<=DotN && DotN<=MaxDot && MinSize<=MinLen && MaxLen<MaxSize){
			a->MakeBitData(BmpPoint,XLen ,YLen);
		}
	}
	GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen ,ShrinkDot);

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}

	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}

void	LineEnhancerLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &BlockList)
{
	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	GetLayersBase()->ThinAreaN(CurrentMap,TmpData ,XByte, YLen ,ShrinkDot);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
		PureFlexAreaList *NextA=a->GetNext();
		int64	DotN=a->GetPatternByte();
		if(DotN<MinDot || MaxDot<DotN){
			FPack.RemoveList(a);
			delete	a;
		}
		a=NextA;
	}

	BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear(TmpBuff ,0,XByte ,YLen);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		int	AddDot=(ShrinkDot>0)?ShrinkDot:0;
		int	mx=a->GetMinX()-AddDot-16;
		int	my=a->GetMinY()-AddDot-16;

		FlexArea	A;
		A=*a;
		A.MoveToNoClip(-mx,-my);
		A.MakeBitData(TmpBuff,XLen,YLen);
		int	W=A.GetWidth()	+2*AddDot+32;
		int	H=A.GetHeight()	+2*AddDot+32;

		int	WByte=W>>3;
		int	MatchingWidth=min(ShrinkDot-1,SearchBlockWidth);
		GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2 ,WByte, H ,MatchingWidth);

		FlexArea	MatchingArea;
		MatchingArea.BuildFromRaster(TmpBuff,WByte,H,mx ,my);
		MatchingArea -= *a;

		GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2 ,WByte, H ,ShrinkDot-MatchingWidth);

		A.BuildFromRaster(TmpBuff,WByte,H,mx ,my);

//		if(A.GetWidth()>LimitDot || A.GetHeight()>LimitDot){
			int	WNumb=(A.GetWidth()+LimitDot-1)/LimitDot;
			int	HNumb=(A.GetHeight()+LimitDot-1)/LimitDot;

			int	WMergin=(WNumb*LimitDot-A.GetWidth())/2;
			int	HMergin=(HNumb*LimitDot-A.GetHeight())/2;
			int	Left=A.GetMinX()-WMergin;
			int	Top =A.GetMinY()-HMergin;
		
			for(int yn=0;yn<HNumb;yn++){
				for(int xn=0;xn<WNumb;xn++){
					FlexArea	LArea=A;
					LArea.ClipArea(Left+xn*LimitDot		,Top+yn*LimitDot 
								,  Left+(xn+1)*LimitDot ,Top+(yn+1)*LimitDot );

					FlexArea	CArea=*a;
					CArea.ClipArea(Left+xn*LimitDot		,Top+yn*LimitDot 
								,  Left+(xn+1)*LimitDot ,Top+(yn+1)*LimitDot );

					FlexArea	MArea=MatchingArea;
					MArea.ClipArea(Left+xn*LimitDot		,Top+yn*LimitDot 
								,  Left+(xn+1)*LimitDot ,Top+(yn+1)*LimitDot );

					LineEnhancerItem	*v=new LineEnhancerItem();
					v->SetArea(LArea);
					v->CalcArea=CArea;
					v->MatchingArea=MArea;
					v->CopyThresholdFromLibrary(GetParentLevelContainer());
				
					if(MArea.GetPatternByte()<10){
						v->GetThresholdW()->SelfSearch=0;
					}

					v->SetLibID(GetLibID());
					BlockList.AppendList(v);
				}
			}
//		}


		MatrixBuffClear(TmpBuff ,0,WByte,H);
	}
	DeleteMatrixBuff(TmpBuff,YLen);
	DeleteMatrixBuff(TmpBuff2,YLen);
	DeleteMatrixBuff(TmpData,YLen);
}
