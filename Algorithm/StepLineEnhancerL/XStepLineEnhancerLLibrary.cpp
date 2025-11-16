#include "XStepLineEnhancerL.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XImageProcess.h"


StepLineEnhancerLLibrary::StepLineEnhancerLLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base),AlgorithmLibrary(LibType)
{
	PickupColorL=0;
	PickupColorH=255;
	GenerateOverlap	=true;

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
	StartAngle	=0;
	EndAngle	=360;
	ExcludeDynamicMask	=false;
}
StepLineEnhancerLLibrary::~StepLineEnhancerLLibrary(void)
{
}
bool	StepLineEnhancerLLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=StepLineEnhancerLVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxDot)==false)
		return false;
	if(::Save(f,MinDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,PickupColorL)==false)
		return false;
	if(::Save(f,PickupColorH)==false)
		return false;
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,GenerateOverlap)==false)
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
	if(::Save(f,StartAngle)==false)
		return false;
	if(::Save(f,EndAngle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
	return true;


}
bool	StepLineEnhancerLLibrary::LoadBlob(QIODevice *f)
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
	if(::Load(f,PickupColorL)==false)
		return false;
	if(::Load(f,PickupColorH)==false)
		return false;
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,GenerateOverlap)==false)
			return false;
	}

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

	if(::Load(f,LimitDot)==false)
		return false;
	if(::Load(f,StartAngle)==false)
		return false;
	if(::Load(f,EndAngle)==false)
		return false;
	if(Ver>=4){
		if(::Load(f,ExcludeDynamicMask)==false)
			return false;	
	}
	return true;
}

StepLineEnhancerLLibrary	&StepLineEnhancerLLibrary::operator=(const AlgorithmLibrary &src)
{
	const StepLineEnhancerLLibrary	*s=dynamic_cast<const StepLineEnhancerLLibrary *>(&src);
	MaxDot				=s->MaxDot;
	MinDot				=s->MinDot;
	LimitDot			=s->LimitDot;
	ShrinkDot			=s->ShrinkDot;
	PickupColorL		=s->PickupColorL;
	PickupColorH		=s->PickupColorH;
	EmphasizeRate		=s->EmphasizeRate;
	GenerateOverlap		=s->GenerateOverlap;

	Priority			=s->Priority;
	StepDot				=s->StepDot;
	MaxSize				=s->MaxSize;
	MinSize				=s->MinSize;
	SearchBlockWidth	=s->SearchBlockWidth;
	SelfSearch			=s->SelfSearch;
	StartAngle			=s->StartAngle;
	EndAngle			=s->EndAngle;
	ExcludeDynamicMask	=s->ExcludeDynamicMask;
	return *this;
}


void	StepLineEnhancerLLibrary::MakePickupTest(ImageBuffer *MasterImage
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	int	YNumb=min(YLen,MasterImage->GetHeight());
	int	XNumb=min(XLen,MasterImage->GetWidth());

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*src=MasterImage->GetY(y);
			BYTE	*dest=BmpPoint[y];
			int		c;
			for(int x=0;x<XNumb;x++,src++){
				c=*src;
				if(PickupColorL<=c && c<=PickupColorH){
					dest[x>>3] |= 0x80>>(x&7);
				}
			}
		}
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
	for(int i=0;i<ShrinkDot;i++){
		ThinArea(BmpPoint,TmpData ,XByte, YLen);
	}

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
	for(int i=0;i<ShrinkDot;i++){
		FatArea(BmpPoint,TmpData ,XByte, YLen);
	}

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}

	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}

void	StepLineEnhancerLLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList)
{
	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	for(int i=0;i<ShrinkDot;i++){
		ThinArea(CurrentMap,TmpData ,XByte, YLen);
	}

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
		A.MakeBitData(TmpBuff);
		int	W=A.GetWidth()	+2*AddDot+32;
		int	H=A.GetHeight()	+2*AddDot+32;

		int	WByte=W>>3;
		int	MatchingWidth=min(ShrinkDot-1,SearchBlockWidth);
		for(int i=0;i<MatchingWidth;i++){
			FatArea(TmpBuff,TmpBuff2 ,WByte, H);
		}
		FlexArea	MatchingArea;
		MatchingArea.BuildFromRaster(TmpBuff,WByte,H,mx ,my);
		MatchingArea -= *a;

		for(int i=0;i<ShrinkDot-MatchingWidth;i++){
			FatArea(TmpBuff,TmpBuff2 ,WByte, H);
		}
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

					StepLineEnhancerLItem	*v=new StepLineEnhancerLItem();
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

}
StepLineEnhancerLItem	*StepLineEnhancerLLibrary::CreateOneItem(FlexArea &Area)
{
	int	AddDot=(ShrinkDot>0)?ShrinkDot:0;

	int	XLen=Area.GetWidth() +AddDot*2+32;
	int	YLen=Area.GetHeight()+AddDot*2+32;
	int	XByte=(XLen+7)/8;

	BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear(TmpBuff ,0,XByte ,YLen);
	
	int	mx=Area.GetMinX()-AddDot-16;
	int	my=Area.GetMinY()-AddDot-16;

	FlexArea	A;
	A=Area;
	A.MoveToNoClip(-mx,-my);
	A.MakeBitData(TmpBuff);
	int	W=A.GetWidth()	+2*AddDot+32;
	int	H=A.GetHeight()	+2*AddDot+32;

	int	WByte=W>>3;
	int	MatchingWidth=min(ShrinkDot-1,SearchBlockWidth);
	for(int i=0;i<MatchingWidth;i++){
		FatArea(TmpBuff,TmpBuff2 ,WByte, H);
	}
		
	FlexArea	MatchingArea;
	MatchingArea.BuildFromRaster(TmpBuff,WByte,H,mx ,my);
	MatchingArea -= Area;

	for(int i=0;i<ShrinkDot-MatchingWidth;i++){
		FatArea(TmpBuff,TmpBuff2 ,WByte, H);
	}
	A.BuildFromRaster(TmpBuff,WByte,H,mx ,my);


	FlexArea	LArea=A;
	LArea.ClipArea(LimitDot		,LimitDot 
				,  GetDotPerLine()-LimitDot ,GetMaxLines()-LimitDot );

	FlexArea	CArea=Area;
	CArea.ClipArea(LimitDot		,LimitDot 
				,  GetDotPerLine()-LimitDot ,GetMaxLines()-LimitDot );

	FlexArea	MArea=MatchingArea;
	MArea.ClipArea(LimitDot		,LimitDot 
				,  GetDotPerLine()-LimitDot ,GetMaxLines()-LimitDot );

	StepLineEnhancerLItem	*v=new StepLineEnhancerLItem();
	v->SetArea(LArea);
	v->CalcArea=CArea;
	v->MatchingArea=MArea;
	v->CopyThresholdFromLibrary(GetParentLevelContainer());
				
	if(MArea.GetPatternByte()<10){
		v->GetThresholdW()->SelfSearch=0;
	}

	v->SetLibID(GetLibID());
	DeleteMatrixBuff(TmpBuff,YLen);
	DeleteMatrixBuff(TmpBuff2,YLen);

	return v;
}