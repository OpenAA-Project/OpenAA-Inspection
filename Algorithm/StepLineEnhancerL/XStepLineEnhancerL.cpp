//#include "XStepLineEnhancerLResource.h"
#include "XStepLineEnhancerL.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XDynamicMaskingPICommon.h"

StepLineEnhancerLThreshold::StepLineEnhancerLThreshold(StepLineEnhancerLItem *parent)
:AlgorithmThreshold(parent)
{
	EmphasizeRate	=1.0;
	MaxLineWidth	=100;
	StepDot			=1;
	SelfSearch		=0;
	StartAngle		=0;
	EndAngle		=360;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	ExcludeDynamicMask	=false;
}

void	StepLineEnhancerLThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const StepLineEnhancerLThreshold	*s=dynamic_cast<const StepLineEnhancerLThreshold *>(&src);
	EmphasizeRate		=s->EmphasizeRate;
	MaxLineWidth		=s->MaxLineWidth;
	StepDot				=s->StepDot;
	SelfSearch			=s->SelfSearch;
	StartAngle			=s->StartAngle;
	EndAngle			=s->EndAngle;
	ExcludeDynamicMask	=s->ExcludeDynamicMask;
}
bool	StepLineEnhancerLThreshold::IsEqual(const AlgorithmThreshold &src)
{
	const StepLineEnhancerLThreshold	*s=dynamic_cast<const StepLineEnhancerLThreshold *>(&src);
	if(EmphasizeRate		!=s->EmphasizeRate		)	return false;
	if(MaxLineWidth			!=s->MaxLineWidth		)	return false;
	if(StepDot				!=s->StepDot			)	return false;
	if(SelfSearch			!=s->SelfSearch			)	return false;
	if(StartAngle			!=s->StartAngle			)	return false;
	if(EndAngle				!=s->EndAngle			)	return false;
	if(ExcludeDynamicMask	!=s->ExcludeDynamicMask	)	return false;
	return true;
}
bool	StepLineEnhancerLThreshold::Save(QIODevice *f)
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
	return true;
}
bool	StepLineEnhancerLThreshold::Load(QIODevice *f)
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

	return true;
}

void	StepLineEnhancerLThreshold::FromLibrary(AlgorithmLibrary *src)
{
	StepLineEnhancerLLibrary	*s=dynamic_cast<StepLineEnhancerLLibrary *>(src);
	EmphasizeRate	=s->EmphasizeRate;
	MaxLineWidth	=s->MaxLineWidth;
	StepDot			=s->StepDot;
	SelfSearch		=s->SelfSearch;
	StartAngle		=s->StartAngle;
	EndAngle		=s->EndAngle;
	ExcludeDynamicMask	=s->ExcludeDynamicMask;
}

void	StepLineEnhancerLThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	StepLineEnhancerLLibrary	*d=dynamic_cast<StepLineEnhancerLLibrary *>(Dest);
	d->EmphasizeRate=EmphasizeRate;
	d->MaxLineWidth	=MaxLineWidth;
	d->StepDot		=StepDot;
	d->SelfSearch	=SelfSearch;
	d->StartAngle	=StartAngle;
	d->EndAngle		=EndAngle;
	d->ExcludeDynamicMask	=ExcludeDynamicMask;
}

//======================================================================
StepLineEnhancerLItem::StepLineEnhancerLItem(void)
{
	AngleList		=NULL;
	AngleDownList	=NULL;
	AVector			=NULL;
	AnglePointList	=NULL;
	AngleListCount	=0;
	MinAngle		=0.1;
}
StepLineEnhancerLItem::~StepLineEnhancerLItem(void)
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

bool    StepLineEnhancerLItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false)
		return false;

	if(CalcArea.Save(f)==false)
		return false;
	if(MatchingArea.Save(f)==false)
		return false;
	return true;
}

bool    StepLineEnhancerLItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	if(CalcArea.Load(f)==false)
		return false;
	if(MatchingArea.Load(f)==false)
		return false;
	return true;
}

void	StepLineEnhancerLItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	StepLineEnhancerLDrawAttr	*BAttr=dynamic_cast<StepLineEnhancerLDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==StepLineEnhancerLDrawAttr::_Block){
			AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else if(BAttr->DrawingArea==StepLineEnhancerLDrawAttr::_Calc){
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
		else if(BAttr->DrawingArea==StepLineEnhancerLDrawAttr::_Matching){
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
void	StepLineEnhancerLItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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

AlgorithmItemPLI	&StepLineEnhancerLItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	StepLineEnhancerLItem	*s=dynamic_cast<StepLineEnhancerLItem *>(&src);
	CalcArea		=s->CalcArea;
	MatchingArea	=s->MatchingArea;
	return *this;
}


void	StepLineEnhancerLItem::CopyThreshold(StepLineEnhancerLItem &src)
{
	GetThresholdW()->CopyFrom(*((StepLineEnhancerLThreshold *)src.GetThresholdR()));
}

void	StepLineEnhancerLItem::CopyThresholdOnly(StepLineEnhancerLItem &src)
{
	GetThresholdW()->CopyFrom(*((StepLineEnhancerLThreshold *)src.GetThresholdR()));
}
void	StepLineEnhancerLItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((StepLineEnhancerLItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==Data->GetLibID()){
			CopyThresholdOnly(*((StepLineEnhancerLItem *)Data));
		}
	}
}

ExeResult	StepLineEnhancerLItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	int	W=CalcArea.GetWidth();
	int	H=CalcArea.GetHeight();
	int	L=hypot(W,H)/2;
	const StepLineEnhancerLThreshold	*RThr=GetThresholdR();
	MinAngle=atan(RThr->StepDot/(double)L);
	int	iAngleListCount	=M_PI/MinAngle;
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
	for(int i=0;i<=AngleListCount;i++){
		AngleList[i].Initial(i*MinAngle,CalcArea);
		AngleList[i].ExecuteInitialAfterEdit(CalcArea,ExecuteInitialAfterEdit_Changed);
	}
	for(int i=0;i<=AngleListCount;i++){
		AngleDownList[i].Initial(i*MinAngle,CalcArea);
		AngleDownList[i].ExecuteInitialAfterEdit(CalcArea,ExecuteInitialAfterEdit_Changed);
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

ExeResult	StepLineEnhancerLItem::ExecutePreProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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
	StepLineEnhancerLInLayer	*P=(StepLineEnhancerLInLayer *)GetParentInLayer();
	ImageBuffer &TargetImage=GetTargetBuff();
	int	ResMx,ResMy;
	ExecutePreProcessingByLayer(mx,my,TargetImage
								,ResMx,ResMy
								,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(ResMx-mx,ResMy-my);
	return _ER_true;
}

void	StepLineEnhancerLItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPLI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
		CalcArea	.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
		MatchingArea.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
	}
}

//----------------------------------------------------------------------------------------------------

StepLineEnhancerLInLayer::StepLineEnhancerLInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
	DynamicMaskMap	=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}
StepLineEnhancerLInLayer::~StepLineEnhancerLInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
	DynamicMaskMap	=NULL;		//This is only pointer. So memory doesn't leak
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}

void	StepLineEnhancerLInLayer::PickupTest(StepLineEnhancerLLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);
	ImageBuffer	&MasterImage=GetMasterBuff();
	LibData.MakePickupTest(&MasterImage
		,MaskMap.GetBitMap()
		,PickupBmp,NULL
		,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
		,((StepLineEnhancerLBase *)GetParentBase())->OmitZoneDot);
}

void	StepLineEnhancerLInLayer::CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList)
{
	StepLineEnhancerLLibrary	**LibDim=new StepLineEnhancerLLibrary*[LibList.GetNumber()];
	int	N=0;
	int	LibType=GetParentBase()->GetLibraryContainer()->GetLibType();
	for(AlgorithmLibraryList *L=LibList.GetFirst();L!=NULL;L=L->GetNext()){
		LibDim[N]=new StepLineEnhancerLLibrary(LibType,GetLayersBase());
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
			if(LibDim[i]->Priority>LibDim[i+1]->Priority){
				StepLineEnhancerLLibrary	Tmp(LibType,GetLayersBase());
				Tmp=*LibDim[i];
				*LibDim[i]=*LibDim[i+1];
				*LibDim[i+1]=Tmp;
				Changed=true;
			}
		}
		if(Changed==false)
			break;
	}

	GenerateBlocks(LibDim,N);		

	for(int i=0;i<N;i++){
		delete	LibDim[i];
	}
	delete	[]LibDim;
}

void	StepLineEnhancerLInLayer::GenerateBlocks(StepLineEnhancerLLibrary *LibDim[],int LibDimNumb)
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
			,((StepLineEnhancerLBase *)GetParentBase())->OmitZoneDot);
			
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
void	StepLineEnhancerLInLayer::CreatePickupBmpBuff(void)
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
void	StepLineEnhancerLInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	
{
	StepLineEnhancerLDrawAttr	*BAttr=dynamic_cast<StepLineEnhancerLDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==StepLineEnhancerLDrawAttr::_Pickup){
			if(PickupBmp!=NULL){
				StepLineEnhancerLBase	*BBase=dynamic_cast<StepLineEnhancerLBase *>(GetParentBase());
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

void	StepLineEnhancerLInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestStepLineEnhancerLPacket	*BPickLib=dynamic_cast<CmdPickupTestStepLineEnhancerLPacket *>(packet);
	if(BPickLib!=NULL){
		PickupTest(*BPickLib->LibPoint);		
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
	CmdCreateStepLineEnhancerLPacket	*CmdCreateStepLineEnhancerLPacketVar=dynamic_cast<CmdCreateStepLineEnhancerLPacket *>(packet);
	if(CmdCreateStepLineEnhancerLPacketVar!=NULL){
		CreateItems(CmdCreateStepLineEnhancerLPacketVar->LayerList
					,CmdCreateStepLineEnhancerLPacketVar->SelectedLibList);
		return;
	}
	CmdAddByteStepLineEnhancerLItemPacket	*CmdAddByteStepLineEnhancerLItemPacketVar=dynamic_cast<CmdAddByteStepLineEnhancerLItemPacket *>(packet);
	if(CmdAddByteStepLineEnhancerLItemPacketVar!=NULL){
		CreateOneItem(CmdAddByteStepLineEnhancerLItemPacketVar->Area,CmdAddByteStepLineEnhancerLItemPacketVar->LibID);
		return;
	}
}

bool	StepLineEnhancerLInLayer::CreateOneItem(FlexArea &Area,int LibID)
{	
	StepLineEnhancerLBase	*BBase=dynamic_cast<StepLineEnhancerLBase *>(GetParentBase());
	StepLineEnhancerLLibrary	TmpLib(BBase->GetLibType(),GetLayersBase());
	if(GetLibraryContainer()->GetLibrary(LibID,TmpLib)==false)
		return false;

	StepLineEnhancerLItem	*Item=TmpLib.CreateOneItem(Area);
	if(Item==NULL)
		return false;
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

ExeResult	StepLineEnhancerLInLayer::ExecuteInitialAfterEdit	(int ExeID 
																,ResultInLayerRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmInLayerPLI::ExecuteInitialAfterEdit(ExeID ,Res,ExecuteInitialAfterEdit_Changed);

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
		AlgorithmLibrary		*a=LibContainer->CreateNew();
		StepLineEnhancerLLibrary	*AL=(StepLineEnhancerLLibrary *)a;
		LibContainer->GetLibrary(D[i].LibID,*AL);
		D[i].Priority=AL->Priority;
		delete	a;
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

void	StepLineEnhancerLInLayer::ItemPointerListContainer::Add(int index ,AlgorithmItemRoot *item)
{
	AppendList(new ItemPointerList(index,item));
}

ExeResult	StepLineEnhancerLInLayer::ExecutePreProcessing(int ExeID ,ResultInLayerRoot *R)
{
	DynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	DynamicMaskMapXByte	=GetDataInPage()->GetDynamicMaskMapXByte();
	DynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	ExeResult	Ret=_ER_true;
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

	return Ret;
}


//----------------------------------------------------------------------------------------------------

void	StepLineEnhancerLInPage::PickupTest(IntList &LayerList ,StepLineEnhancerLLibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			StepLineEnhancerLInLayer	*BI=dynamic_cast<StepLineEnhancerLInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}

void	StepLineEnhancerLInPage::GenerateBlocks(IntList &LayerList, StepLineEnhancerLLibrary *LibDim[],int LibDimNumb)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			StepLineEnhancerLInLayer	*BI=dynamic_cast<StepLineEnhancerLInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(LibDim,LibDimNumb);
			}
		}
	}
}

void	StepLineEnhancerLInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestStepLineEnhancerLPacket	*BPickLib=dynamic_cast<CmdPickupTestStepLineEnhancerLPacket *>(packet);
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
	CmdCreateStepLineEnhancerLPacket	*CmdCreateStepLineEnhancerLPacketVar=dynamic_cast<CmdCreateStepLineEnhancerLPacket *>(packet);
	if(CmdCreateStepLineEnhancerLPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		/*
		for(IntClass *L=CmdCreateStepLineEnhancerLPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		*/
		return;
	}
	CmdAddByteStepLineEnhancerLItemPacket	*CmdAddByteStepLineEnhancerLItemPacketVar=dynamic_cast<CmdAddByteStepLineEnhancerLItemPacket *>(packet);
	if(CmdAddByteStepLineEnhancerLItemPacketVar!=NULL){
		for(IntClass *L=CmdAddByteStepLineEnhancerLItemPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		return;
	}
}

//----------------------------------------------------------------------------------------------------
StepLineEnhancerLBase::StepLineEnhancerLBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup				=Qt::yellow;
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;
	OmitZoneDot				=100;

	SetParam(&ColorPickup			, /**/"Color"	,/**/"ColorPickup"			,"Color for Image to Pickup-Test ");
	SetParam(&AreaColor				, /**/"Color"	,/**/"AreaColor"			,"filtered Area Color");
	SetParam(&NegAreaColorSelected	, /**/"Color"	,/**/"NegAreaColorSelected"	,"Color for Selected filtered area");
	SetParam(&NegAreaColor			, /**/"Color"	,/**/"NegAreaColor"			,"Color for Active filtered area");
	SetParam(&TransparentLevel		, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&OmitZoneDot			, /**/"Setting"	,/**/"OmitZoneDot"			,"Omit zone dot in block generation");
}

AlgorithmDrawAttr	*StepLineEnhancerLBase::CreateDrawAttr(void)
{
	return new StepLineEnhancerLDrawAttr();
}

void	StepLineEnhancerLBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetStepLineEnhancerLLibraryListPacket	*AListPacket=dynamic_cast<CmdGetStepLineEnhancerLLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
											,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempStepLineEnhancerLLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempStepLineEnhancerLLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new StepLineEnhancerLLibrary(GetLibType(),GetLayersBase());
		return;
	}
	CmdLoadStepLineEnhancerLLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadStepLineEnhancerLLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearStepLineEnhancerLLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearStepLineEnhancerLLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteStepLineEnhancerLLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteStepLineEnhancerLLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertStepLineEnhancerLLibraryPacket	*BInsLib=dynamic_cast<CmdInsertStepLineEnhancerLLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(StepLineEnhancerLVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateStepLineEnhancerLLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateStepLineEnhancerLLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(StepLineEnhancerLVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetStepLineEnhancerLLibraryNamePacket	*CmdGetStepLineEnhancerLLibraryNamePacketVar=dynamic_cast<CmdGetStepLineEnhancerLLibraryNamePacket *>(packet);
	if(CmdGetStepLineEnhancerLLibraryNamePacketVar!=NULL){
		StepLineEnhancerLLibrary	TmpLib(GetLibType(),GetLayersBase());
		CmdGetStepLineEnhancerLLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetStepLineEnhancerLLibraryNamePacketVar->LibID,TmpLib);
		CmdGetStepLineEnhancerLLibraryNamePacketVar->LibName=TmpLib.GetLibName();
		return;
	}
	CmdCreateTempStepLineEnhancerLItemPacket	*CmdCreateTempStepLineEnhancerLItem=dynamic_cast<CmdCreateTempStepLineEnhancerLItemPacket *>(packet);
	if(CmdCreateTempStepLineEnhancerLItem!=NULL){
		CmdCreateTempStepLineEnhancerLItem->Point=new StepLineEnhancerLItem();
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		StepLineEnhancerLLibrary	LibData(GetLibType(),GetLayersBase());
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
}

bool	StepLineEnhancerLBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==StepLineEnhancerLReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==StepLineEnhancerLReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*StepLineEnhancerLBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==StepLineEnhancerLReqThresholdReqCommand){
		return new StepLineEnhancerLThresholdReq();
	}
	else if(Command==StepLineEnhancerLReqThresholdSendCommand){
		StepLineEnhancerLThresholdSend	*pSend=new StepLineEnhancerLThresholdSend();
		if(reqData!=NULL){
			StepLineEnhancerLThresholdReq	*req=(StepLineEnhancerLThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	StepLineEnhancerLBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==StepLineEnhancerLReqThresholdReqCommand){
		StepLineEnhancerLThresholdReq	*p=(StepLineEnhancerLThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==StepLineEnhancerLReqThresholdSendCommand){
		StepLineEnhancerLThresholdSend	*p=(StepLineEnhancerLThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	StepLineEnhancerLBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==StepLineEnhancerLReqThresholdReqCommand){
		StepLineEnhancerLThresholdReq	*p=(StepLineEnhancerLThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==StepLineEnhancerLReqThresholdSendCommand){
		StepLineEnhancerLThresholdSend	*p=(StepLineEnhancerLThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	StepLineEnhancerLBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==StepLineEnhancerLReqThresholdReqCommand){
		StepLineEnhancerLThresholdReq	*p=(StepLineEnhancerLThresholdReq *)data;
		return true;
	}
	else if(Command==StepLineEnhancerLReqThresholdSendCommand){
		StepLineEnhancerLThresholdSend	*p=(StepLineEnhancerLThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}


//=======================================================================================
StepLineEnhancerLThresholdReq::StepLineEnhancerLThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Layer	=-1;
	Dx=0;
	Dy=0;
}
bool	StepLineEnhancerLThresholdReq::Save(QIODevice *f)
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
bool	StepLineEnhancerLThresholdReq::Load(QIODevice *f)
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

StepLineEnhancerLThresholdSend::StepLineEnhancerLThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Dx=0;
	Dy=0;
}

void	StepLineEnhancerLThresholdSend::ConstructList(StepLineEnhancerLThresholdReq *reqPacket,StepLineEnhancerLBase *Base)
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
				StepLineEnhancerLItem	*BItem=(StepLineEnhancerLItem *)item;
				const StepLineEnhancerLThreshold	*RThr=BItem->GetThresholdR(GetLayersBase());
				EmphasizeRate		=RThr->EmphasizeRate;
				MaxLineWidth		=RThr->MaxLineWidth;
				StepDot				=RThr->StepDot;
				SelfSearch			=RThr->SelfSearch;
				StartAngle			=RThr->StartAngle;
				EndAngle			=RThr->EndAngle;
				ExcludeDynamicMask	=RThr->ExcludeDynamicMask;
			}
		}
	}
}

bool	StepLineEnhancerLThresholdSend::Save(QIODevice *f)
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

	return true;
}
bool	StepLineEnhancerLThresholdSend::Load(QIODevice *f)
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
	return true;
}