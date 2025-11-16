#include "XLineEnhancerResource.h"
#include "XLineEnhancer.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>

LineEnhancerThreshold::LineEnhancerThreshold(LineEnhancerItem *parent)
:AlgorithmThreshold(parent)
{
	EmphasizeRate	=0;
	MaxLineWidth	=0;
	StepDot			=0;
	SelfSearch		=0;
}

void	LineEnhancerThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const LineEnhancerThreshold	*s=dynamic_cast<const LineEnhancerThreshold *>(&src);
	EmphasizeRate	=s->EmphasizeRate;
	MaxLineWidth	=s->MaxLineWidth;
	StepDot			=s->StepDot;
	SelfSearch		=s->SelfSearch;
}
bool	LineEnhancerThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const LineEnhancerThreshold	*s=dynamic_cast<const LineEnhancerThreshold *>(&src);
	if(EmphasizeRate	!=s->EmphasizeRate	)	return false;
	if(MaxLineWidth		!=s->MaxLineWidth	)	return false;
	if(StepDot			!=s->StepDot		)	return false;
	if(SelfSearch		!=s->SelfSearch		)	return false;
	return true;
}
bool	LineEnhancerThreshold::Save(QIODevice *f)
{
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,MaxLineWidth)==false)
		return false;
	if(::Save(f,StepDot)==false)
		return false;
	if(::Save(f,SelfSearch)==false)
		return false;

	return true;
}
bool	LineEnhancerThreshold::Load(QIODevice *f)
{
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,MaxLineWidth)==false)
		return false;
	if(::Load(f,StepDot)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;

	return true;
}

void	LineEnhancerThreshold::FromLibrary(AlgorithmLibrary *src)
{
	LineEnhancerLibrary	*s=dynamic_cast<LineEnhancerLibrary *>(src);
	EmphasizeRate	=s->EmphasizeRate;
	MaxLineWidth	=s->MaxLineWidth;
	StepDot			=s->StepDot;
	SelfSearch		=s->SelfSearch;
}

void	LineEnhancerThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	LineEnhancerLibrary	*d=dynamic_cast<LineEnhancerLibrary *>(Dest);
	d->EmphasizeRate=EmphasizeRate;
	d->MaxLineWidth	=MaxLineWidth;
	d->StepDot		=StepDot;
	d->SelfSearch	=SelfSearch;
}

//======================================================================
LineEnhancerItem::LineEnhancerItem(void)
{
	AngleList		=NULL;
	AngleDownList	=NULL;
	AVector			=NULL;
	AngleListCount	=0;
}
LineEnhancerItem::~LineEnhancerItem(void)
{
	if(AngleList!=NULL){
		delete	[]AngleList;
		AngleList=NULL;
	}
	if(AngleDownList!=NULL){
		delete	[]AngleDownList;
		AngleDownList=NULL;
	}
}

bool    LineEnhancerItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(CalcArea.Save(f)==false)
		return false;
	if(MatchingArea.Save(f)==false)
		return false;
	return true;
}

bool    LineEnhancerItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	if(CalcArea.Load(f)==false)
		return false;
	if(MatchingArea.Load(f)==false)
		return false;
	return true;
}

void	LineEnhancerItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	LineEnhancerDrawAttr	*BAttr=dynamic_cast<LineEnhancerDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==LineEnhancerDrawAttr::_Block){
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else if(BAttr->DrawingArea==LineEnhancerDrawAttr::_Calc){
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
		else if(BAttr->DrawingArea==LineEnhancerDrawAttr::_Matching){
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
void	LineEnhancerItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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

AlgorithmItemPI	&LineEnhancerItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	const LineEnhancerItem	*s=dynamic_cast<const LineEnhancerItem *>(&src);
	CalcArea		=s->CalcArea;
	MatchingArea	=s->MatchingArea;
	return *this;
}


void	LineEnhancerItem::CopyThreshold(LineEnhancerItem &src)
{
	GetThresholdW()->CopyFrom(*((LineEnhancerThreshold *)src.GetThresholdR()));
}

void	LineEnhancerItem::CopyThresholdOnly(LineEnhancerItem &src)
{
	GetThresholdW()->CopyFrom(*((LineEnhancerThreshold *)src.GetThresholdR()));
}
void	LineEnhancerItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((LineEnhancerItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==Data->GetLibID()){
			CopyThresholdOnly(*((LineEnhancerItem *)Data));
		}
	}
}

ExeResult	LineEnhancerItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	W=CalcArea.GetWidth();
	int	H=CalcArea.GetHeight();
	int	L=hypot(W,H)/2;
	double	MinAngle=atan(GetThresholdR()->StepDot/(double)L);
	AngleListCount	=M_PI/MinAngle;
	if(AngleList!=NULL){
		delete	[]AngleList;
	}
	if(AngleDownList!=NULL){
		delete	[]AngleDownList;
	}
	AngleList=new AngleDim[AngleListCount];
	for(int i=0;i<AngleListCount;i++){
		AngleList[i].Initial(i*MinAngle,CalcArea);
		AngleList[i].ExecuteInitialAfterEdit(CalcArea,EInfo);
	}
	AngleDownList=new AngleDimDown[AngleListCount];
	for(int i=0;i<AngleListCount;i+=2){
		AngleDownList[i].Initial(i*MinAngle,CalcArea);
		AngleDownList[i].ExecuteInitialAfterEdit(CalcArea,EInfo);
	}

	ImagePointerContainer MasterImageList;
	GetMasterBuffList(MasterImageList);
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		int	C=MatchingArea.GetAverage(*MasterImageList[Layer],0,0);
		MasterBrightness.Add(C);
	}
	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	return _ER_true;
}

ExeResult	LineEnhancerItem::ExecutePreProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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
	ImagePointerContainer TargetImages;
	GetDataInPage()->GetTargetImages(TargetImages);
	int	ResMx,ResMy;
	if(((LineEnhancerBase *)GetParentBase())->ModeOneLayer==-1 || GetLayerNumb()==1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			ImageBuffer	*TargetImage=TargetImages[Layer];
			ExecutePreProcessingByLayer(mx,my,*TargetImage
										,ResMx,ResMy
										,Layer);
		}
	}
	else{
		int	Layer=((LineEnhancerBase *)GetParentBase())->ModeOneLayer;
		ImageBuffer	*TargetImage=TargetImages[Layer];
		ExecutePreProcessingByLayer(mx,my,*TargetImage
									,ResMx,ResMy
									,Layer);
	}
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(ResMx-mx,ResMy-my);
	return _ER_true;
}
void	LineEnhancerItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
		CalcArea	.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
		MatchingArea.MoveToClip(GlobalDx,GlobalDy	,0,0,GetDotPerLine(),GetMaxLines());
	}
}

//----------------------------------------------------------------------------------------------------

LineEnhancerInPage::LineEnhancerInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}
LineEnhancerInPage::~LineEnhancerInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

void	LineEnhancerInPage::PickupTest(LineEnhancerLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		ImagePointerContainer MasterImages;
		GetDataInPage()->GetMasterImages(MasterImages);
		LibData.MakePickupTest(MasterImages
			,Map.GetBitMap()
			,PickupBmp,NULL
			,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
			,((LineEnhancerBase *)GetParentBase())->OmitZoneDot
			,((LineEnhancerBase *)GetParentBase())->ModeOneLayer);
	}
}

void	LineEnhancerInPage::CreateItems(AlgorithmLibraryListContainer &LibList)
{
	AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[LibList.GetNumber()];
	int	N=0;
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	int	LibType=Container->GetLibType();
	for(AlgorithmLibraryList *L=LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LibDim[N]=new AlgorithmLibraryLevelContainer(Container);
		Container->GetLibrary(L->GetLibID(),*LibDim[N]);
	}
	for(;;){
		bool	Changed=false;
		for(int i=0;i<N-1;i++){
			LineEnhancerLibrary	*L1=dynamic_cast<LineEnhancerLibrary *>(LibDim[i  ]->GetLibrary());
			LineEnhancerLibrary	*L2=dynamic_cast<LineEnhancerLibrary *>(LibDim[i+1]->GetLibrary());
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

	LineEnhancerLibrary	**DDim=new LineEnhancerLibrary*[N];
	for(int i=0;i<N;i++){
		DDim[i]=dynamic_cast<LineEnhancerLibrary *>(LibDim[i]->GetLibrary());
	}

	GenerateBlocks(DDim,N);		

	delete	[]DDim;
	for(int i=0;i<N;i++){
		delete	LibDim[i];
	}
	delete	[]LibDim;
}

void	LineEnhancerInPage::GenerateBlocks(LineEnhancerLibrary *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();

	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPI	*NextL=L->GetNext();
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
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->GetArea().MakeBitData(LastOcupyMap,GetDotPerLine() ,GetMaxLines());
	}

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	ImagePointerContainer MasterImages;
	GetDataInPage()->GetMasterImages(MasterImages);

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i])==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			const BYTE	**MaskBitmap=Map.GetBitMap();
			
			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

			LibDim[i]->MakePickupTest(MasterImages
				,MaskBitmap
				,CurrentMap,OcupyMap
				,XByte ,GetDotPerLine(),GetMaxLines()
				,((LineEnhancerBase *)GetParentBase())->OmitZoneDot
				,((LineEnhancerBase *)GetParentBase())->ModeOneLayer);
				
			NPListPack<AlgorithmItemPI>	TmpBlockData;
			LibDim[i]->MakeBlock(
					 CurrentMap,LastOcupyMap
					,XByte ,GetDotPerLine(),GetMaxLines()
					,TmpBlockData);
			AlgorithmItemPI	*q;
			while((q=TmpBlockData.GetFirst())!=NULL){
				TmpBlockData.RemoveList(q);
				AppendItem(q);
			}
			MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		}
	}

	DeleteMatrixBuff(CurrentMap		,GetMaxLines());
	DeleteMatrixBuff(OcupyMap		,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap	,GetMaxLines());
}
void	LineEnhancerInPage::CreatePickupBmpBuff(void)
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
void	LineEnhancerInPage::Draw(QImage &pnt,IntList &LayerList, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	LineEnhancerDrawAttr	*BAttr=dynamic_cast<LineEnhancerDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DrawingArea==LineEnhancerDrawAttr::_Pickup){
			if(PickupBmp!=NULL){
				LineEnhancerBase	*BBase=dynamic_cast<LineEnhancerBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
						,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
							,0,0
							,BBase->ColorPickup);
			}
		}
		else{
			AlgorithmInPagePI::Draw(pnt,LayerList, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInPagePI::Draw(pnt,LayerList, movx ,movy ,ZoomRate ,Attr);
	}
}

void	LineEnhancerInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestLineEnhancerPacket	*BPickLib=dynamic_cast<CmdPickupTestLineEnhancerPacket *>(packet);
	if(BPickLib!=NULL){
		PickupTest(*(LineEnhancerLibrary *)BPickLib->LibPoint->GetLibrary());		
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
	CmdCreateLineEnhancerPacket	*CmdCreateLineEnhancerPacketVar=dynamic_cast<CmdCreateLineEnhancerPacket *>(packet);
	if(CmdCreateLineEnhancerPacketVar!=NULL){
		CreateItems(CmdCreateLineEnhancerPacketVar->SelectedLibList);
		return;
	}
}

//----------------------------------------------------------------------------------------------------
LineEnhancerBase::LineEnhancerBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup				=Qt::yellow;
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;
	OmitZoneDot				=100;
	ModeOneLayer			=-1;

	SetParam(&ColorPickup			, /**/"Color"	,/**/"ColorPickup"			,LangSolver.GetString(XLineEnhancer_LS,LID_0)/*"Color for Image to Pickup-Test "*/);
	SetParam(&AreaColor				, /**/"Color"	,/**/"AreaColor"			,LangSolver.GetString(XLineEnhancer_LS,LID_1)/*"filtered Area Color"*/);
	SetParam(&NegAreaColorSelected	, /**/"Color"	,/**/"NegAreaColorSelected"	,LangSolver.GetString(XLineEnhancer_LS,LID_2)/*"Color for Selected filtered area"*/);
	SetParam(&NegAreaColor			, /**/"Color"	,/**/"NegAreaColor"			,LangSolver.GetString(XLineEnhancer_LS,LID_3)/*"Color for Active filtered area"*/);
	SetParam(&TransparentLevel		, /**/"Color"	,/**/"TransparentLevel"		,LangSolver.GetString(XLineEnhancer_LS,LID_4)/*"Color for Transparent display level"*/);
	SetParam(&OmitZoneDot			, /**/"Setting"	,/**/"OmitZoneDot"			,LangSolver.GetString(XLineEnhancer_LS,LID_5)/*"Omit zone dot in block generation"*/);
	SetParam(&ModeOneLayer			, /**/"Setting"	,/**/"ModeOneLayer"			,LangSolver.GetString(XLineEnhancer_LS,LID_10)/*"Use this layer in multi layer inspection , -1: use all layers"*/);
}

AlgorithmDrawAttr	*LineEnhancerBase::CreateDrawAttr(void)
{
	return new LineEnhancerDrawAttr();
}

void	LineEnhancerBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetLineEnhancerLibraryListPacket	*AListPacket=dynamic_cast<CmdGetLineEnhancerLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempLineEnhancerLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempLineEnhancerLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadLineEnhancerLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadLineEnhancerLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearLineEnhancerLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearLineEnhancerLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteLineEnhancerLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteLineEnhancerLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertLineEnhancerLibraryPacket	*BInsLib=dynamic_cast<CmdInsertLineEnhancerLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(LineEnhancerVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateLineEnhancerLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateLineEnhancerLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(LineEnhancerVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetLineEnhancerLibraryNamePacket	*CmdGetLineEnhancerLibraryNamePacketVar=dynamic_cast<CmdGetLineEnhancerLibraryNamePacket *>(packet);
	if(CmdGetLineEnhancerLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetLineEnhancerLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetLineEnhancerLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetLineEnhancerLibraryNamePacketVar->Success==true){
				CmdGetLineEnhancerLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
}

bool	LineEnhancerBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==LineEnhancerReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==LineEnhancerReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*LineEnhancerBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==LineEnhancerReqThresholdReqCommand){
		return new LineEnhancerThresholdReq();
	}
	else if(Command==LineEnhancerReqThresholdSendCommand){
		LineEnhancerThresholdSend	*pSend=new LineEnhancerThresholdSend();
		if(reqData!=NULL){
			LineEnhancerThresholdReq	*req=(LineEnhancerThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	LineEnhancerBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==LineEnhancerReqThresholdReqCommand){
		LineEnhancerThresholdReq	*p=(LineEnhancerThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==LineEnhancerReqThresholdSendCommand){
		LineEnhancerThresholdSend	*p=(LineEnhancerThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	LineEnhancerBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==LineEnhancerReqThresholdReqCommand){
		LineEnhancerThresholdReq	*p=(LineEnhancerThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==LineEnhancerReqThresholdSendCommand){
		LineEnhancerThresholdSend	*p=(LineEnhancerThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	LineEnhancerBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==LineEnhancerReqThresholdReqCommand){
		LineEnhancerThresholdReq	*p=(LineEnhancerThresholdReq *)data;
		return true;
	}
	else if(Command==LineEnhancerReqThresholdSendCommand){
		LineEnhancerThresholdSend	*p=(LineEnhancerThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}


//=======================================================================================
LineEnhancerThresholdReq::LineEnhancerThresholdReq(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;
}
bool	LineEnhancerThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	LineEnhancerThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

LineEnhancerThresholdSend::LineEnhancerThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Dx=0;
	Dy=0;

	EmphasizeRate	=0;
	MaxLineWidth	=0;
	StepDot			=0;
	SelfSearch		=0;
}

void	LineEnhancerThresholdSend::ConstructList(LineEnhancerThresholdReq *reqPacket,LineEnhancerBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			LineEnhancerItem	*BItem=(LineEnhancerItem *)item;
			const LineEnhancerThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			EmphasizeRate	=RThr->EmphasizeRate;
			MaxLineWidth	=RThr->MaxLineWidth;
			StepDot			=RThr->StepDot;
			SelfSearch		=RThr->SelfSearch;
		}
	}
}

bool	LineEnhancerThresholdSend::Save(QIODevice *f)
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

	return true;
}
bool	LineEnhancerThresholdSend::Load(QIODevice *f)
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
	return true;
}