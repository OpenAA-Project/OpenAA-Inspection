#include "XLineEnhancer1LResource.h"
#include "XLineEnhancer1L.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XDynamicMaskingPICommon.h"
#include "XLineEnhancerL1AlgoPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

LineEnhancer1LThreshold::LineEnhancer1LThreshold(LineEnhancer1LItem *parent)
:AlgorithmThreshold(parent)
{
	EmphasizeRate	=1.0;
	MaxLineWidth	=100;
	StepDot			=1;
	SelfSearch		=0;
	StartAngle		=0;
	EndAngle		=360;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	ExcludeDynamicMask	=false;
	FixedAngle		=false;
	SourceLayer		= -1;
}

void	LineEnhancer1LThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const LineEnhancer1LThreshold	*s=dynamic_cast<const LineEnhancer1LThreshold *>(&src);
	EmphasizeRate		=s->EmphasizeRate;
	MaxLineWidth		=s->MaxLineWidth;
	StepDot				=s->StepDot;
	SelfSearch			=s->SelfSearch;
	StartAngle			=s->StartAngle;
	EndAngle			=s->EndAngle;
	ExcludeDynamicMask	=s->ExcludeDynamicMask;
	FixedAngle			=s->FixedAngle;
	SourceLayer			=s->SourceLayer;
}
bool	LineEnhancer1LThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const LineEnhancer1LThreshold	*s=dynamic_cast<const LineEnhancer1LThreshold *>(&src);
	if(EmphasizeRate		!=s->EmphasizeRate		)	return false;
	if(MaxLineWidth			!=s->MaxLineWidth		)	return false;
	if(StepDot				!=s->StepDot			)	return false;
	if(SelfSearch			!=s->SelfSearch			)	return false;
	if(StartAngle			!=s->StartAngle			)	return false;
	if(EndAngle				!=s->EndAngle			)	return false;
	if(ExcludeDynamicMask	!=s->ExcludeDynamicMask	)	return false;
	if(FixedAngle			!=s->FixedAngle			)	return false;
	if(SourceLayer			!=s->SourceLayer		)	return false;
	return true;
}
bool	LineEnhancer1LThreshold::Save(QIODevice *f)
{
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,MaxLineWidth)==false)
		return false;
	if(::Save(f,StepDot)==false)
		return false;
	if(::Save(f,SelfSearch)==false)
		return false;
	if(::Save(f,StartAngle)==false)
		return false;
	if(::Save(f,EndAngle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
	if(::Save(f,FixedAngle)==false)
		return false;
	if(::Save(f,SourceLayer) == false)
		return false;
	return true;
}
bool	LineEnhancer1LThreshold::Load(QIODevice *f)
{
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,MaxLineWidth)==false)
		return false;
	if(::Load(f,StepDot)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;
	if(::Load(f,StartAngle)==false)
		return false;
	if(::Load(f,EndAngle)==false)
		return false;

	if(GetLoadedVersion()>=4){
		if(::Load(f,ExcludeDynamicMask)==false)
			return false;
	}
	if(GetLoadedVersion()>=5){
		if(::Load(f,FixedAngle)==false)
			return false;
		//FixedAngle=true;
	}
	if(GetLoadedVersion()>=5){
		if(::Load(f,SourceLayer)==false)
			return false;
		//FixedAngle=true;
	}
	return true;
}

void	LineEnhancer1LThreshold::FromLibrary(AlgorithmLibrary *src)
{
	LineEnhancer1LLibrary	*s=dynamic_cast<LineEnhancer1LLibrary *>(src);
	EmphasizeRate	=s->EmphasizeRate;
	MaxLineWidth	=s->MaxLineWidth;
	StepDot			=s->StepDot;
	SelfSearch		=s->SelfSearch;
	StartAngle		=s->StartAngle;
	EndAngle		=s->EndAngle;
	ExcludeDynamicMask	=s->ExcludeDynamicMask;
	FixedAngle		=s->FixedAngle;
	SourceLayer		=s->SourceLayer;
}

void	LineEnhancer1LThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	LineEnhancer1LLibrary	*d=dynamic_cast<LineEnhancer1LLibrary *>(Dest);
	d->EmphasizeRate=EmphasizeRate;
	d->MaxLineWidth	=MaxLineWidth;
	d->StepDot		=StepDot;
	d->SelfSearch	=SelfSearch;
	d->StartAngle	=StartAngle;
	d->EndAngle		=EndAngle;
	d->ExcludeDynamicMask	=ExcludeDynamicMask;
	d->FixedAngle	=FixedAngle;
	d->SourceLayer	=SourceLayer;
}

//======================================================================
LineEnhancer1LItem::LineEnhancer1LItem(void)
{
	AngleList		=NULL;
	AngleDownList	=NULL;
	AVector			=NULL;
	AnglePointList	=NULL;
	AngleListCount	=0;
	MinAngle		=0.1;
	MasterBrightness=0;
}
LineEnhancer1LItem::~LineEnhancer1LItem(void)
{
	if(AnglePointList!=NULL){
		delete	[]AnglePointList;
		AnglePointList=NULL;
	}
	if(AngleList!=NULL){
		delete	[]AngleList;
		AngleList=NULL;
	}
	if(AngleDownList!=NULL){
		delete	[]AngleDownList;
		AngleDownList=NULL;
	}
	AngleListCount=0;
}

bool    LineEnhancer1LItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;

	if(CalcArea.Save(f)==false)
		return false;
	if(MatchingArea.Save(f)==false)
		return false;
	return true;
}

bool    LineEnhancer1LItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	if(CalcArea.Load(f)==false)
		return false;
	if(MatchingArea.Load(f)==false)
		return false;
	return true;
}

void	LineEnhancer1LItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	LineEnhancer1LDrawAttr	*BAttr=dynamic_cast<LineEnhancer1LDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==LineEnhancer1LDrawAttr::_Block){
			AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else if(BAttr->DrawingArea==LineEnhancer1LDrawAttr::_Calc){
			if(GetSelected()==true){
				CalcArea.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()
					,ZoomRate ,movx ,movy);
			}
			else if(GetActive()==true){
				CalcArea.Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()
					,ZoomRate ,movx ,movy);
			}
			else{
				CalcArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()
					,ZoomRate ,movx ,movy);
			}
		}
		else if(BAttr->DrawingArea==LineEnhancer1LDrawAttr::_Matching){
			if(GetSelected()==true){
				MatchingArea.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()
					,ZoomRate ,movx ,movy);
			}
			else if(GetActive()==true){
				MatchingArea.Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()
					,ZoomRate ,movx ,movy);
			}
			else{
				MatchingArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()
					,ZoomRate ,movx ,movy);
			}
		}
	}
	else{
		QColor	c=Qt::black;
		CalcArea.Draw(0,0 ,&pnt ,c.rgba()
			,ZoomRate ,movx ,movy);
	}
}
void	LineEnhancer1LItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){	
		QColor	c=Qt::red;
		c.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
						,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);
	}
}

AlgorithmItemPLI	&LineEnhancer1LItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	const LineEnhancer1LItem	*s=dynamic_cast<const LineEnhancer1LItem *>(&src);
	if(s!=NULL){
		CalcArea		=s->CalcArea;
		MatchingArea	=s->MatchingArea;
	}
	return *this;
}


void	LineEnhancer1LItem::CopyThreshold(LineEnhancer1LItem &src)
{
	GetThresholdW()->CopyFrom(*((LineEnhancer1LThreshold *)src.GetThresholdR()));
}

void	LineEnhancer1LItem::CopyThresholdOnly(LineEnhancer1LItem &src)
{
	GetThresholdW()->CopyFrom(*((LineEnhancer1LThreshold *)src.GetThresholdR()));
}
void	LineEnhancer1LItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((LineEnhancer1LItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==Data->GetLibID()){
			CopyThresholdOnly(*((LineEnhancer1LItem *)Data));
		}
	}
}

ExeResult	LineEnhancer1LItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	W=CalcArea.GetWidth();
	int	H=CalcArea.GetHeight();
	int	L=hypot(W,H)/2;
	const LineEnhancer1LThreshold	*RThr=GetThresholdR();
	MinAngle=atan(RThr->StepDot/(double)L);
	int	iAngleListCount	=M_PI/MinAngle;
	if(RThr->FixedAngle==true)
		iAngleListCount=1;

	if(iAngleListCount!=AngleListCount){
		AngleListCount=iAngleListCount;
		if(AnglePointList!=NULL){
			delete	[]AnglePointList;
		}
		AnglePointList=new int[AngleListCount+1];
		if(AngleList!=NULL){
			delete	[]AngleList;
		}
		AngleList=new AngleDim[AngleListCount+1];
		if(AngleDownList!=NULL){
			delete	[]AngleDownList;
		}
		AngleDownList=new AngleDimDown[AngleListCount+1];
	}
	if(RThr->FixedAngle==true){
		AngleList[0].Initial(RThr->StartAngle,CalcArea);
		AngleList[0].ExecuteInitialAfterEdit(CalcArea,EInfo);
		AngleDownList[0].Initial(RThr->StartAngle,CalcArea);
		AngleDownList[0].ExecuteInitialAfterEdit(CalcArea,EInfo);
	}
	else{
		for(int i=0;i<=AngleListCount;i++){
			AngleList[i].Initial(i*MinAngle,CalcArea);
			AngleList[i].ExecuteInitialAfterEdit(CalcArea,EInfo);
		}
		for(int i=0;i<=AngleListCount;i++){
			AngleDownList[i].Initial(i*MinAngle,CalcArea);
			AngleDownList[i].ExecuteInitialAfterEdit(CalcArea,EInfo);
		}
	}

	ImageBuffer	&IBuff=GetMasterBuff();
	MasterBrightness=MatchingArea.GetAverage(IBuff,0,0);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	return _ER_true;
}

ExeResult	LineEnhancer1LItem::ExecutePreProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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
	LineEnhancer1LInLayer	*P=(LineEnhancer1LInLayer *)GetParentInLayer();
	ImageBuffer &TargetImage=GetTargetBuff();
	int	ResMx,ResMy;
	ExecutePreProcessingByLayer(mx,my,TargetImage
								,ResMx,ResMy
								,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(ResMx-mx,ResMy-my);
	return _ER_true;
}

void	LineEnhancer1LItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPLI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
		CalcArea	.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
		MatchingArea.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
	}
}

//----------------------------------------------------------------------------------------------------

LineEnhancer1LInLayer::LineEnhancer1LInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
	DynamicMaskMap	=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}
LineEnhancer1LInLayer::~LineEnhancer1LInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
	DynamicMaskMap	=NULL;		//This is only pointer. So memory doesn't leak
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}
bool		LineEnhancer1LInLayer::AppendItem(AlgorithmItemRoot *item)
{
	if(item->GetLibID()>=0){
		AlgorithmLibraryLevelContainer	*LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		if(LibP==NULL){
			GetParentBase()->LoadAllManagedCacheLib();
			LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		}
		if(LibP!=NULL){
			if(LibP->HasGenLayer(GetLayer())==true){
				return AlgorithmInLayerPLI::AppendItem(item);
			}
			return false;
		}
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}

bool		LineEnhancer1LInLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		LineEnhancer1LInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		LineEnhancer1LInLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

void	LineEnhancer1LInLayer::PickupTest(LineEnhancer1LLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);
	ImageBuffer	&MasterImage=GetMasterBuff();
	LibData.MakePickupTest(&MasterImage
		,MaskMap.GetBitMap()
		,PickupBmp,NULL
		,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
		,((LineEnhancer1LBase *)GetParentBase())->OmitZoneDot);
}

void	LineEnhancer1LInLayer::CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList)
{
	AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[LibList.GetNumber()];
	int	N=0;
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	int	LibType=GetParentBase()->GetLibraryContainer()->GetLibType();
	for(AlgorithmLibraryList *L=LibList.GetFirst();L!=NULL;L=L->GetNext()){
		LibDim[N]=new AlgorithmLibraryLevelContainer(Container);
		GetLibraryContainer()->GetLibrary(L->GetLibID(),*LibDim[N]);
		if(LibDim[N]->HasGenLayer(GetLayer())==true
		|| ((LibDim[N]->GetAdaptedGenLayers().IsEmpty()==true) && LayerList.IsInclude(GetLayer())==true)){
			N++;
		}
		else{
			delete	LibDim[N];
		}
	}
	for(;;){
		bool	Changed=false;
		for(int i=0;i<N-1;i++){
			LineEnhancer1LLibrary	*L1=dynamic_cast<LineEnhancer1LLibrary *>(LibDim[i  ]->GetLibrary());
			LineEnhancer1LLibrary	*L2=dynamic_cast<LineEnhancer1LLibrary *>(LibDim[i+1]->GetLibrary());
			if(L1->Priority>L2->Priority){
				AlgorithmLibraryLevelContainer	Tmp(Container);
				Tmp=*LibDim[i];
				*LibDim[i]=*LibDim[i+1];
				*LibDim[i+1]=Tmp;
				Changed=true;
			}
		}
		if(Changed==false)
			break;
	}
	LineEnhancer1LLibrary	**DDim=new LineEnhancer1LLibrary*[N];
	for(int i=0;i<N;i++){
		DDim[i]=dynamic_cast<LineEnhancer1LLibrary *>(LibDim[i]->GetLibrary());
	}

	GenerateBlocks(DDim,N);		

	delete	[]DDim;
	for(int i=0;i<N;i++){
		delete	LibDim[i];
	}
	delete	[]LibDim;
}

void	LineEnhancer1LInLayer::GenerateBlocks(LineEnhancer1LLibrary *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();

	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->GetArea().MakeBitData(LastOcupyMap,GetDotPerLine() ,GetMaxLines());
	}

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	GetParentBase()->LoadAllManagedCacheLib();

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBuffer MaskMap;
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			AlgorithmInPagePLI	*LPg=(AlgorithmInPagePLI*)GetParentInPage();
			AlgorithmInLayerPLI	*LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(LibDim[i]->GetAdaptedPickLayers().GetFirst()->GetValue());
			LL->GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		else{
			GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		
		if(LibDim[i]->GenerateOverlap==false){
			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());
		}
		ImageBuffer	*MasterImage=&GetMasterBuff();
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			for(int LLayer=0;LLayer<GetLayerNumb();LLayer++){
				if(LibDim[i]->HasPickLayer(LLayer)==true){
					ImagePointerContainer ImagesPointers;
					GetParentInPage()->GetMasterImages(ImagesPointers);
					MasterImage=ImagesPointers[LLayer];
					break;
				}
			}
		}

		LibDim[i]->MakePickupTest(MasterImage
			,MaskBitmap
			,CurrentMap,OcupyMap
			,XByte ,GetDotPerLine(),GetMaxLines()
			,((LineEnhancer1LBase *)GetParentBase())->OmitZoneDot);
			
		NPListPack<AlgorithmItemPLI>	TmpBlockData;
		LibDim[i]->MakeBlock(
				 CurrentMap,LastOcupyMap
				,XByte ,GetDotPerLine(),GetMaxLines()
				,TmpBlockData);
		AlgorithmItemPLI	*q;
		while((q=TmpBlockData.GetFirst())!=NULL){
			TmpBlockData.RemoveList(q);
			AppendItem(q);
		}
		MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
	}

	DeleteMatrixBuff(CurrentMap		,GetMaxLines());
	DeleteMatrixBuff(OcupyMap		,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap	,GetMaxLines());
}
void	LineEnhancer1LInLayer::CreatePickupBmpBuff(void)
{
	if(PickupBmp!=NULL && PickupBmpYLen!=GetMaxLines()){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
	if(PickupBmp==NULL){
		PickupBmpYLen=GetMaxLines();
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmp=MakeMatrixBuff(PickupBmpXByte ,PickupBmpYLen);
	}
	MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
}
void	LineEnhancer1LInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	
{
	LineEnhancer1LDrawAttr	*BAttr=dynamic_cast<LineEnhancer1LDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==LineEnhancer1LDrawAttr::_Pickup){
			if(PickupBmp!=NULL){
				LineEnhancer1LBase	*BBase=dynamic_cast<LineEnhancer1LBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
						,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
							,0,0
							,BBase->ColorPickup);
			}
		}
		else{
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	LineEnhancer1LInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestLineEnhancer1LPacket	*BPickLib=dynamic_cast<CmdPickupTestLineEnhancer1LPacket *>(packet);
	if(BPickLib!=NULL){
		PickupTest(*(LineEnhancer1LLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdClearTestLineEnhancePacket	*CmdClearTestLineEnhancePacketVar=dynamic_cast<CmdClearTestLineEnhancePacket *>(packet);
	if(CmdClearTestLineEnhancePacketVar!=NULL){
		if(PickupBmp!=NULL)
			DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
		return;
	}
	CmdCreateLineEnhancer1LPacket	*CmdCreateLineEnhancer1LPacketVar=dynamic_cast<CmdCreateLineEnhancer1LPacket *>(packet);
	if(CmdCreateLineEnhancer1LPacketVar!=NULL){
		CreateItems(CmdCreateLineEnhancer1LPacketVar->LayerList
					,CmdCreateLineEnhancer1LPacketVar->SelectedLibList);
		return;
	}
	CmdAddByteLineEnhancer1LItemPacket	*CmdAddByteLineEnhancer1LItemPacketVar=dynamic_cast<CmdAddByteLineEnhancer1LItemPacket *>(packet);
	if(CmdAddByteLineEnhancer1LItemPacketVar!=NULL){
		CreateOneItem(CmdAddByteLineEnhancer1LItemPacketVar->Area,CmdAddByteLineEnhancer1LItemPacketVar->LibID);
		return;
	}
}

bool	LineEnhancer1LInLayer::CreateOneItem(FlexArea &Area,int LibID)
{	
	LineEnhancer1LBase	*BBase=dynamic_cast<LineEnhancer1LBase *>(GetParentBase());

	AlgorithmLibraryLevelContainer	LLib(BBase);
	if(GetLibraryContainer()->GetLibrary(LibID,LLib)==false)
		return false;
	LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(LLib.GetLibrary());
	LineEnhancer1LItem	*Item=ALib->CreateOneItem(GetPage(),Area);
	if(Item==NULL)
		return false;

	GetParentBase()->ClearManagedCacheLib();
	AppendItem(Item);
	return true;
}


struct	ExecuteItemDim
{
	int	LibID;
	int	Priority;
};

static	int	ExecuteItemDimSortFunc(const void *a, const void *b)
{
	struct	ExecuteItemDim	*aa=(struct	ExecuteItemDim *)a;
	struct	ExecuteItemDim	*bb=(struct	ExecuteItemDim *)b;
	if(aa->Priority>bb->Priority)
		return 1;
	if(aa->Priority<bb->Priority)
		return -1;
	return 0;
}

ExeResult	LineEnhancer1LInLayer::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmInLayerPLI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	struct	ExecuteItemDim	*D=new struct	ExecuteItemDim[GetItemCount()];
	int	LibN=0;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		bool	Found=false;
		for(int i=0;i<LibN;i++){
			if(D[i].LibID==L->GetLibID()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			D[LibN].LibID	=L->GetLibID();
			LibN++;
		}
	}
	AlgorithmLibraryContainer	*LibContainer=GetLibraryContainer();
	for(int i=0;i<LibN;i++){
		AlgorithmLibraryLevelContainer	LLib(LibContainer);
		if(LibContainer->GetLibrary(D[i].LibID,LLib)==true){
			LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(LLib.GetLibrary());
			D[i].Priority=ALib->Priority;
		}
	}
	QSort(D,LibN,sizeof(struct	ExecuteItemDim),ExecuteItemDimSortFunc);
	ExecutingList.RemoveAll();
	for(int i=0;i<LibN;i++){
		ItemByLibContainerList	*p=new ItemByLibContainerList(D[i].LibID,this);
		int	Index=0;
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext(),Index++){
			if(D[i].LibID==L->GetLibID()){
				p->Add(Index,L);
			}
		}
		ExecutingList.AppendList(p);
	}
	delete	[]D;
		
	return _ER_true;
}

void	LineEnhancer1LInLayer::ItemPointerListContainer::Add(int index ,AlgorithmItemRoot *item)
{
	AppendList(new ItemPointerList(index,item));
}

ExeResult	LineEnhancer1LInLayer::ExecutePreProcessing(int ExeID ,ResultInLayerRoot *R)
{
	DynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	DynamicMaskMapXByte	=GetDataInPage()->GetDynamicMaskMapXByte();
	DynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->CalcSingleThread==false){
		for(ItemByLibContainerList *a=ExecutingList.GetFirst();a!=NULL;a=a->GetNext()){
			ItemPointerList *k;
			#pragma omp parallel
			#pragma omp single private(k)
			for(k=a->ItemPointerListContainer::GetFirst();k!=NULL;k=k->GetNext()){
				#pragma omp task
				{
					ExeResult	RR=k->Pointer->ExecutePreProcessing(ExeID ,0,Res->GetResultItem(k->Index));
					if(RR!=_ER_true){
						Ret=RR;
					}
				}
			}
		}
	}
	else{
		for(ItemByLibContainerList *a=ExecutingList.GetFirst();a!=NULL;a=a->GetNext()){
			ItemPointerList *k;
			for(k=a->ItemPointerListContainer::GetFirst();k!=NULL;k=k->GetNext()){
				ExeResult	RR=k->Pointer->ExecutePreProcessing(ExeID ,0,Res->GetResultItem(k->Index));
				if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}
	}
	return Ret;
}

bool	LineEnhancer1LInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfLECerL1	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfLECerL1	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	LineEnhancer1LInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		LineEnhancer1LItem	*a=dynamic_cast<LineEnhancer1LItem *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------

void	LineEnhancer1LInPage::PickupTest(IntList &LayerList ,LineEnhancer1LLibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			LineEnhancer1LInLayer	*BI=dynamic_cast<LineEnhancer1LInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}

void	LineEnhancer1LInPage::GenerateBlocks(IntList &LayerList, LineEnhancer1LLibrary *LibDim[],int LibDimNumb)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			LineEnhancer1LInLayer	*BI=dynamic_cast<LineEnhancer1LInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(LibDim,LibDimNumb);
			}
		}
	}
}

void	LineEnhancer1LInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestLineEnhancer1LPacket	*BPickLib=dynamic_cast<CmdPickupTestLineEnhancer1LPacket *>(packet);
	if(BPickLib!=NULL){
		for(IntClass *L=BPickLib->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdClearTestLineEnhancePacket	*CmdClearTestLineEnhancePacketVar=dynamic_cast<CmdClearTestLineEnhancePacket *>(packet);
	if(CmdClearTestLineEnhancePacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(layer);
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateLineEnhancer1LPacket	*CmdCreateLineEnhancer1LPacketVar=dynamic_cast<CmdCreateLineEnhancer1LPacket *>(packet);
	if(CmdCreateLineEnhancer1LPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		/*
		for(IntClass *L=CmdCreateLineEnhancer1LPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		*/
		return;
	}
	CmdAddByteLineEnhancer1LItemPacket	*CmdAddByteLineEnhancer1LItemPacketVar=dynamic_cast<CmdAddByteLineEnhancer1LItemPacket *>(packet);
	if(CmdAddByteLineEnhancer1LItemPacketVar!=NULL){
		for(IntClass *L=CmdAddByteLineEnhancer1LItemPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		return;
	}
}
bool	LineEnhancer1LInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_InitialBmpMap){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmItemPointerListContainer Items;
			GetLayerData(layer)->EnumOriginTypeItems(Info.OperationOrigin,Items);
			for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
				AlgorithmItemPointerList *NextP=a->GetNext();
				if(a->GetItem()->GetEditLocked()==true){
					Items.RemoveList(a);
					delete	a;
				}
				a=NextP;
			}
			GetLayerData(layer)->RemoveItems(Items);
		}
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		GetParentBase()->LoadAllManagedCacheLib();
		LineEnhancer1LLibrary	*TmpLib=(LineEnhancer1LLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(int layer=0;layer<GetLayerNumb();layer++){
				NPListPack<AlgorithmItemPLI>	TmpBlockData;
				if(TmpLib->HasGenLayer(layer)==true){
					LineEnhancer1LInLayer	*BL=(LineEnhancer1LInLayer*)GetLayerData(layer);
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					BL->GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);
					bool	LimitedMaskInOtherPage=BL->UseLibraryForMaskingInOtherPage(Info.LibID);
					bool	LimitedMaskInThisPage =BL->IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						MatrixBuffAnd	(TmpData ,MaskMap.GetBitMap() ,Info.XByte ,Info.YLen);
						TmpLib->MakeBlockOnly(
							 TmpData,MaskMap.GetBitMap() 
							,Info.XByte ,Info.XByte*8,Info.YLen
							,TmpBlockData);
						AlgorithmItemPLI	*q;
						while((q=TmpBlockData.GetFirst())!=NULL){
							TmpBlockData.RemoveList(q);
							q->SetOriginType(Info.OperationOrigin);
							q->SetOrigin(Info.Origin);
							BL->AppendItem(q);
						}
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			LineEnhancer1LInLayer	*L=(LineEnhancer1LInLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------------------------------
LineEnhancer1LBase::LineEnhancer1LBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup				=Qt::yellow;
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;
	OmitZoneDot				=100;

	SetParam(&ColorPickup			, /**/"Color"	,/**/"ColorPickup"			,LangSolver.GetString(XLineEnhancer1L_LS,LID_0)/*"Color for Image to Pickup-Test "*/);
	SetParam(&AreaColor				, /**/"Color"	,/**/"AreaColor"			,LangSolver.GetString(XLineEnhancer1L_LS,LID_1)/*"filtered Area Color"*/);
	SetParam(&NegAreaColorSelected	, /**/"Color"	,/**/"NegAreaColorSelected"	,LangSolver.GetString(XLineEnhancer1L_LS,LID_2)/*"Color for Selected filtered area"*/);
	SetParam(&NegAreaColor			, /**/"Color"	,/**/"NegAreaColor"			,LangSolver.GetString(XLineEnhancer1L_LS,LID_3)/*"Color for Active filtered area"*/);
	SetParam(&TransparentLevel		, /**/"Color"	,/**/"TransparentLevel"		,LangSolver.GetString(XLineEnhancer1L_LS,LID_4)/*"Color for Transparent display level"*/);
	SetParam(&OmitZoneDot			, /**/"Setting"	,/**/"OmitZoneDot"			,LangSolver.GetString(XLineEnhancer1L_LS,LID_5)/*"Omit zone dot in block generation"*/);
}

AlgorithmDrawAttr	*LineEnhancer1LBase::CreateDrawAttr(void)
{
	return new LineEnhancer1LDrawAttr();
}

void	LineEnhancer1LBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetLineEnhancer1LLibraryListPacket	*AListPacket=dynamic_cast<CmdGetLineEnhancer1LLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempLineEnhancer1LLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempLineEnhancer1LLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadLineEnhancer1LLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadLineEnhancer1LLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearLineEnhancer1LLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearLineEnhancer1LLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteLineEnhancer1LLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteLineEnhancer1LLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertLineEnhancer1LLibraryPacket	*BInsLib=dynamic_cast<CmdInsertLineEnhancer1LLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(LineEnhancer1LVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateLineEnhancer1LLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateLineEnhancer1LLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(LineEnhancer1LVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetLineEnhancer1LLibraryNamePacket	*CmdGetLineEnhancer1LLibraryNamePacketVar=dynamic_cast<CmdGetLineEnhancer1LLibraryNamePacket *>(packet);
	if(CmdGetLineEnhancer1LLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetLineEnhancer1LLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetLineEnhancer1LLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetLineEnhancer1LLibraryNamePacketVar->Success==true){
				CmdGetLineEnhancer1LLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
	CmdCreateTempLineEnhancer1LItemPacket	*CmdCreateTempLineEnhancer1LItem=dynamic_cast<CmdCreateTempLineEnhancer1LItemPacket *>(packet);
	if(CmdCreateTempLineEnhancer1LItem!=NULL){
		CmdCreateTempLineEnhancer1LItem->Point=new LineEnhancer1LItem();
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
}

bool	LineEnhancer1LBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==LineEnhancer1LReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==LineEnhancer1LReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*LineEnhancer1LBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==LineEnhancer1LReqThresholdReqCommand){
		return new LineEnhancer1LThresholdReq();
	}
	else if(Command==LineEnhancer1LReqThresholdSendCommand){
		LineEnhancer1LThresholdSend	*pSend=new LineEnhancer1LThresholdSend();
		if(reqData!=NULL){
			LineEnhancer1LThresholdReq	*req=(LineEnhancer1LThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	LineEnhancer1LBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==LineEnhancer1LReqThresholdReqCommand){
		LineEnhancer1LThresholdReq	*p=(LineEnhancer1LThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==LineEnhancer1LReqThresholdSendCommand){
		LineEnhancer1LThresholdSend	*p=(LineEnhancer1LThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	LineEnhancer1LBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==LineEnhancer1LReqThresholdReqCommand){
		LineEnhancer1LThresholdReq	*p=(LineEnhancer1LThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==LineEnhancer1LReqThresholdSendCommand){
		LineEnhancer1LThresholdSend	*p=(LineEnhancer1LThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	LineEnhancer1LBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==LineEnhancer1LReqThresholdReqCommand){
		LineEnhancer1LThresholdReq	*p=(LineEnhancer1LThresholdReq *)data;
		return true;
	}
	else if(Command==LineEnhancer1LReqThresholdSendCommand){
		LineEnhancer1LThresholdSend	*p=(LineEnhancer1LThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}


//=======================================================================================
LineEnhancer1LThresholdReq::LineEnhancer1LThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Layer	=-1;
	Dx=0;
	Dy=0;
	Mastered	=true;
}
bool	LineEnhancer1LThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	LineEnhancer1LThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

LineEnhancer1LThresholdSend::LineEnhancer1LThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Dx=0;
	Dy=0;


	EmphasizeRate		=0;
	MaxLineWidth		=0;
	StepDot				=0;
	SelfSearch			=0;
	StartAngle=EndAngle	=0;
	ExcludeDynamicMask	=true;
	FixedAngle			=false;
}

void	LineEnhancer1LThresholdSend::ConstructList(LineEnhancer1LThresholdReq *reqPacket,LineEnhancer1LBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerRoot	*Al=Ap->GetLayerData(reqPacket->Layer);
		if(Al!=NULL){
			AlgorithmItemRoot	*item	=Al->SearchIDItem(ItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				LineEnhancer1LItem	*BItem=(LineEnhancer1LItem *)item;
				const LineEnhancer1LThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				EmphasizeRate		=RThr->EmphasizeRate;
				MaxLineWidth		=RThr->MaxLineWidth;
				StepDot				=RThr->StepDot;
				SelfSearch			=RThr->SelfSearch;
				StartAngle			=RThr->StartAngle;
				EndAngle			=RThr->EndAngle;
				ExcludeDynamicMask	=RThr->ExcludeDynamicMask;
				FixedAngle			=RThr->FixedAngle;
			}
		}
	}
}

bool	LineEnhancer1LThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,MaxLineWidth)==false)
		return false;
	if(::Save(f,StepDot)==false)
		return false;
	if(::Save(f,SelfSearch)==false)
		return false;
	if(::Save(f,StartAngle)==false)
		return false;
	if(::Save(f,EndAngle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
	if(::Save(f,FixedAngle)==false)
		return false;

	return true;
}
bool	LineEnhancer1LThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,MaxLineWidth)==false)
		return false;
	if(::Load(f,StepDot)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;
	if(::Load(f,StartAngle)==false)
		return false;
	if(::Load(f,EndAngle)==false)
		return false;
	if(::Load(f,ExcludeDynamicMask)==false)
		return false;
	if(::Load(f,FixedAngle)==false)
		return false;

	return true;
}