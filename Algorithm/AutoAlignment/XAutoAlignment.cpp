/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoAlignmentResource.h"
#include "XAutoAlignment.h"
#include "XDoubleClass.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XAutoMaskingPI.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XStatisticPacket.h"
#include "XPointer.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "XMaskingFromGeneral.h"
#include "XAutoAlignmentCommon.h"


static	bool	IsBit(BYTE **MBmp,int x1 ,int y1 ,int x2 ,int y2)
{
	for(int y=y1;y<y2;y++){
		BYTE	*s=MBmp[y];
		for(int x=x1;x<x2;x++){
			if((s[x>>3]&(0x80>>(x&7)))!=0)
				return true;
		}
	}
	return false;
}

AutoAlignmentLibrary::AutoAlignmentLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PicoShift=5;
	StartupExecute	=false;
	Priority		=100;
	PickupExpansion	=5;
	NoiseShrink		=2;
	ExpandForPickup	=2;
	MinDot			=100;
	FringeWidth		=5;
	AdptedMatchingRate		=0.5;
	CompletelyMatchingRate	=0.82;
}

bool	AutoAlignmentLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=AutoAlignmentVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(PickupColor.Save(f)==false)
		return false;
	if(::Save(f,PicoShift)==false)
		return false;
	if(::Save(f,StartupExecute)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,PickupExpansion)==false)
		return false;
	if(::Save(f,NoiseShrink)==false)
		return false;
	if(::Save(f,ExpandForPickup)==false)
		return false;
	if(::Save(f,MinDot)==false)
		return false;
	if(::Save(f,FringeWidth)==false)
		return false;
	if(::Save(f,AdptedMatchingRate)==false)
		return false;
	if(::Save(f,CompletelyMatchingRate)==false)
		return false;
	return true;
}
bool	AutoAlignmentLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(PickupColor.Load(f)==false)
		return false;
	if(::Load(f,PicoShift)==false)
		return false;
	if(::Load(f,StartupExecute)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,PickupExpansion)==false)
		return false;
	if(::Load(f,NoiseShrink)==false)
		return false;
	if(::Load(f,ExpandForPickup)==false)
		return false;
	if(::Load(f,MinDot)==false)
		return false;
	if(::Load(f,FringeWidth)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,AdptedMatchingRate)==false)
			return false;
		if(::Load(f,CompletelyMatchingRate)==false)
			return false;
	}
	return true;
}

AutoAlignmentLibrary	&AutoAlignmentLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AutoAlignmentLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//====================================================================================================
AutoAlignmentLibraryContainer::AutoAlignmentLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
AutoAlignmentLibraryContainer::~AutoAlignmentLibraryContainer(void)
{
}

//====================================================================================================

AutoAlignmentThreshold::AutoAlignmentThreshold(AutoAlignmentSheet *parent)
:AlgorithmThreshold(parent)
{
	PicoShift=5;
}

void	AutoAlignmentThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AutoAlignmentThreshold	*s=(const AutoAlignmentThreshold *)&src;
	PickupColor				=s->PickupColor;
	PicoShift				=s->PicoShift;
	NoiseShrink				=s->NoiseShrink;
	PickupExpansion			=s->PickupExpansion;
	Priority				=s->Priority;
	ExpandForPickup			=s->ExpandForPickup;
	MinDot					=s->MinDot;
	FringeWidth				=s->FringeWidth;
	AdptedMatchingRate		=s->AdptedMatchingRate;
	CompletelyMatchingRate	=s->CompletelyMatchingRate;
}

bool	AutoAlignmentThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AutoAlignmentThreshold	*s=(const AutoAlignmentThreshold *)&src;
	if(PickupColor				!=s->PickupColor			)	return false;
	if(PicoShift				!=s->PicoShift				)	return false;
	if(NoiseShrink				!=s->NoiseShrink			)	return false;
	if(PickupExpansion			!=s->PickupExpansion		)	return false;
	if(Priority					!=s->Priority				)	return false;
	if(ExpandForPickup			!=s->ExpandForPickup		)	return false;
	if(MinDot					!=s->MinDot					)	return false;
	if(FringeWidth				!=s->FringeWidth			)	return false;
	if(AdptedMatchingRate		!=s->AdptedMatchingRate		)	return false;
	if(CompletelyMatchingRate	!=s->CompletelyMatchingRate	)	return false;
	return true;
}

bool	AutoAlignmentThreshold::Save(QIODevice *f)
{
	if(PickupColor.Save(f)==false)
		return false;
	if(::Save(f,PicoShift)==false)
		return false;
	if(::Save(f,NoiseShrink)==false)
		return false;
	if(::Save(f,PickupExpansion)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,ExpandForPickup)==false)
		return false;
	if(::Save(f,MinDot)==false)
		return false;
	if(::Save(f,FringeWidth)==false)
		return false;
	if(::Save(f,AdptedMatchingRate)==false)
		return false;
	if(::Save(f,CompletelyMatchingRate)==false)
		return false;
	return true;
}
bool	AutoAlignmentThreshold::Load(QIODevice *f)
{
	if(PickupColor.Load(f)==false)
		return false;
	if(::Load(f,PicoShift)==false)
		return false;
	if(::Load(f,NoiseShrink)==false)
		return false;
	if(::Load(f,PickupExpansion)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,ExpandForPickup)==false)
		return false;
	if(::Load(f,MinDot)==false)
		return false;
	if(::Load(f,FringeWidth)==false)
		return false;
	if(::Load(f,AdptedMatchingRate)==false)
		return false;
	if(::Load(f,CompletelyMatchingRate)==false)
		return false;
	return true;
}

void	AutoAlignmentThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AutoAlignmentLibrary	*s=(AutoAlignmentLibrary *)src;
	PickupColor				=s->PickupColor;
	PicoShift				=s->PicoShift;
	PickupExpansion			=s->PickupExpansion;
	NoiseShrink				=s->NoiseShrink;
	Priority				=s->Priority;
	ExpandForPickup			=s->ExpandForPickup;
	MinDot					=s->MinDot;
	FringeWidth				=s->FringeWidth;
	AdptedMatchingRate		=s->AdptedMatchingRate;
	CompletelyMatchingRate	=s->CompletelyMatchingRate;
}

void	AutoAlignmentThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AutoAlignmentLibrary	*d=(AutoAlignmentLibrary *)Dest;
	d->PickupColor				=PickupColor;
	d->PicoShift				=PicoShift;
	d->PickupExpansion			=PickupExpansion;
	d->NoiseShrink				=NoiseShrink;
	d->Priority					=Priority;
	d->ExpandForPickup			=ExpandForPickup;
	d->MinDot					=MinDot;
	d->FringeWidth				=FringeWidth;
	d->AdptedMatchingRate		=AdptedMatchingRate;
	d->CompletelyMatchingRate	=CompletelyMatchingRate;
}

//====================================================================================================

AutoAlignmentInPage::AutoAlignmentInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	NoAdjustMode=false;

	ResultPerPixXFromTarget=NULL;
	ResultPerPixYFromTarget=NULL;
	ResultPerPixXFromMaster=NULL;
	ResultPerPixYFromMaster=NULL;
	ResultRelativeXFromTarget=NULL;
	ResultRelativeYFromTarget=NULL;
	ResultRelativeXFromMaster=NULL;
	ResultRelativeYFromMaster=NULL;

#if	defined(NeedFringeBit)
	ResultBitTransFromMaster=NULL;
	ResultBitTransFromTarget=NULL;
	ResultBitFirstTransFromMaster=NULL;
	ResultBitFirstTransFromTarget=NULL;
#endif
	ResultBitPickupFromMaster=NULL;
	ResultBitPickupFromTarget=NULL;
	ResultBitFirstPickupFromMaster=NULL;
	ResultBitFirstPickupFromTarget=NULL;

}

AutoAlignmentInPage::~AutoAlignmentInPage(void)
{
	Release();
}

class	AAAlgorithmLibraryList : public AlgorithmLibraryList
{
public:
	int	Priority;

	AAAlgorithmLibraryList(const AlgorithmLibraryList &src):AlgorithmLibraryList(src){}
};

void	AutoAlignmentInPage::InitialAlloc(void)
{
	Release();
	XLen=GetDotPerLine();
	YLen=GetMaxLines();
	XByte=(XLen+7)/8;

	ResultPerPixXFromTarget=(char**)MakeMatrixBuff(XLen,YLen);
	ResultPerPixYFromTarget=(char**)MakeMatrixBuff(XLen,YLen);
	ResultPerPixXFromMaster=(char**)MakeMatrixBuff(XLen,YLen);
	ResultPerPixYFromMaster=(char**)MakeMatrixBuff(XLen,YLen);
	ResultRelativeXFromTarget=(char**)MakeMatrixBuff(XLen,YLen);
	ResultRelativeYFromTarget=(char**)MakeMatrixBuff(XLen,YLen);
	ResultRelativeXFromMaster=(char**)MakeMatrixBuff(XLen,YLen);
	ResultRelativeYFromMaster=(char**)MakeMatrixBuff(XLen,YLen);

#if	defined(NeedFringeBit)
	ResultBitTransFromMaster=MakeMatrixBuff(XByte,YLen);
	ResultBitTransFromTarget=MakeMatrixBuff(XByte,YLen);
	ResultBitFirstTransFromMaster=MakeMatrixBuff(XByte,YLen);
	ResultBitFirstTransFromTarget=MakeMatrixBuff(XByte,YLen);
#endif
	ResultBitPickupFromMaster=MakeMatrixBuff(XByte,YLen);
	ResultBitPickupFromTarget=MakeMatrixBuff(XByte,YLen);
	ResultBitFirstPickupFromMaster=MakeMatrixBuff(XByte,YLen);
	ResultBitFirstPickupFromTarget=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear((BYTE **)ResultPerPixXFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultPerPixYFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultPerPixXFromMaster ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultPerPixYFromMaster ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeXFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeYFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeXFromMaster ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeYFromMaster ,0,XLen,YLen);

#if	defined(NeedFringeBit)
	MatrixBuffClear(ResultBitTransFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitTransFromTarget ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstTransFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstTransFromTarget ,0,XByte,YLen);
#endif
	MatrixBuffClear(ResultBitPickupFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitPickupFromTarget ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstPickupFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstPickupFromTarget ,0,XByte,YLen);
}
void	AutoAlignmentInPage::Release(void)
{
	if(ResultPerPixXFromTarget!=NULL){
		DeleteMatrixBuff((BYTE **)ResultPerPixXFromTarget,YLen);
		ResultPerPixXFromTarget=NULL;
	}
	if(ResultPerPixYFromTarget!=NULL){
		DeleteMatrixBuff((BYTE **)ResultPerPixYFromTarget,YLen);
		ResultPerPixYFromTarget=NULL;
	}
	if(ResultPerPixXFromMaster!=NULL){
		DeleteMatrixBuff((BYTE **)ResultPerPixXFromMaster,YLen);
		ResultPerPixXFromMaster=NULL;
	}
	if(ResultPerPixYFromMaster!=NULL){
		DeleteMatrixBuff((BYTE **)ResultPerPixYFromMaster,YLen);
		ResultPerPixYFromMaster=NULL;
	}
	if(ResultRelativeXFromTarget!=NULL){
		DeleteMatrixBuff((BYTE **)ResultRelativeXFromTarget,YLen);
		ResultRelativeXFromTarget=NULL;
	}
	if(ResultRelativeYFromTarget!=NULL){
		DeleteMatrixBuff((BYTE **)ResultRelativeYFromTarget,YLen);
		ResultRelativeYFromTarget=NULL;
	}
	if(ResultRelativeXFromMaster!=NULL){
		DeleteMatrixBuff((BYTE **)ResultRelativeXFromMaster,YLen);
		ResultRelativeXFromMaster=NULL;
	}
	if(ResultRelativeYFromMaster!=NULL){
		DeleteMatrixBuff((BYTE **)ResultRelativeYFromMaster,YLen);
		ResultRelativeYFromMaster=NULL;
	}

#if	defined(NeedFringeBit)
	if(ResultBitTransFromMaster!=NULL){
		DeleteMatrixBuff(ResultBitTransFromMaster,YLen);
		ResultBitTransFromMaster=NULL;
	}
	if(ResultBitTransFromTarget!=NULL){
		DeleteMatrixBuff(ResultBitTransFromTarget,YLen);
		ResultBitTransFromTarget=NULL;
	}
	if(ResultBitFirstTransFromMaster!=NULL){
		DeleteMatrixBuff(ResultBitFirstTransFromMaster,YLen);
		ResultBitFirstTransFromMaster=NULL;
	}
	if(ResultBitFirstTransFromTarget!=NULL){
		DeleteMatrixBuff(ResultBitFirstTransFromTarget,YLen);
		ResultBitFirstTransFromTarget=NULL;
	}
#endif
	if(ResultBitPickupFromMaster!=NULL){
		DeleteMatrixBuff(ResultBitPickupFromMaster,YLen);
		ResultBitPickupFromMaster=NULL;
	}
	if(ResultBitPickupFromTarget!=NULL){
		DeleteMatrixBuff(ResultBitPickupFromTarget,YLen);
		ResultBitPickupFromTarget=NULL;
	}
	if(ResultBitFirstPickupFromMaster!=NULL){
		DeleteMatrixBuff(ResultBitFirstPickupFromMaster,YLen);
		ResultBitFirstPickupFromMaster=NULL;
	}
	if(ResultBitFirstPickupFromTarget!=NULL){
		DeleteMatrixBuff(ResultBitFirstPickupFromTarget,YLen);
		ResultBitFirstPickupFromTarget=NULL;
	}
}

static	int	SheetDataFunc(const void *a,const void *b)
{
	if((*((AutoAlignmentSheet **)a))->CreatedManual==true && (*((AutoAlignmentSheet **)b))->CreatedManual==false){
		return 1;
	}
	else if((*((AutoAlignmentSheet **)a))->CreatedManual==false && (*((AutoAlignmentSheet **)b))->CreatedManual==true){
		return -1;
	}
	int	d=(*((AutoAlignmentSheet **)a))->GetThresholdR()->Priority - (*((AutoAlignmentSheet **)b))->GetThresholdR()->Priority;
	return d;
}

bool	AutoAlignmentInPage::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}

ExeResult	AutoAlignmentInPage::ExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	AlignmentPacket2DContainer.RemoveAll();
	if(IsLocalCamera()==false){
//////////////
		////phase?I??
		//PhaseProcess();
//////////////
		return _ER_true;
	}
	InitialAlloc();

	ConstMapBufferListContainer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap);
	ConstMapBuffer Map;
	MaskMap.BindOr(Map);
	const BYTE	**Mask=Map.GetBitMap();

	if(Mask==NULL || MaskMap.IsEmpty()==true){
///////////////
		////phase?I??
		//PhaseProcess();
//////////////
		return _ER_true;
	}

	AutoAlignmentInPageMonoMiniSizeContainer.RemoveAll();
	for(int	L=400;L<min(GetDotPerLine(),GetMaxLines())/3;L*=2){
		AutoAlignmentInPageMonoMiniSize	*a=new AutoAlignmentInPageMonoMiniSize(this);
		a->InitialAlloc(max(GetDotPerLine(),GetMaxLines())/L);
		a->CreateMasterMap(Mask);
		AutoAlignmentInPageMonoMiniSizeContainer.AppendList(a);
	}
	if(GetFirstData()==NULL){
		AlgorithmLibraryListContainer	StartupLibList;
		AlgorithmLibraryListContainer	TmpStartupLibList;
		AlgorithmLibraryListContainer	AllLibIDList;
		GetParentBase()->GetLibraryContainer()->EnumLibrary(AllLibIDList);
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(AlgorithmLibraryList *a=AllLibIDList.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryLevelContainer	TmpLib(Container);
			if(Container->GetLibrary(a->GetLibID(),TmpLib)==true){
				AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TmpLib.GetLibrary());
				if(ALib->StartupExecute==true){
					AAAlgorithmLibraryList	*b=new AAAlgorithmLibraryList(*a);
					b->Priority=ALib->Priority;
					TmpStartupLibList.AppendList(b);
				}
			}
		}
		while(TmpStartupLibList.GetFirst()!=NULL){
			AAAlgorithmLibraryList	*Point=(AAAlgorithmLibraryList *)TmpStartupLibList.GetFirst();
			for(AAAlgorithmLibraryList *a=(AAAlgorithmLibraryList *)Point->GetNext();a!=NULL;a=(AAAlgorithmLibraryList *)a->GetNext()){
				if(Point->Priority>a->Priority){
					Point=a;
				}
			}
			TmpStartupLibList.RemoveList(Point);
			StartupLibList.AppendList(Point);
		}
		for(AAAlgorithmLibraryList *a=(AAAlgorithmLibraryList*)StartupLibList.GetFirst();a!=NULL;a=(AAAlgorithmLibraryList*)a->GetNext()){
			AutoAlignmentSheet	*p=(AutoAlignmentSheet *)CreateItem(0);
			AlgorithmLibraryContainer	*Container=GetParentBase()->GetLibraryContainer();
			AlgorithmLibraryLevelContainer	SrcLib(Container);
			if(Container->GetLibrary(a->GetLibID(),SrcLib)==true){
				p->CopyThresholdFromLibrary(&SrcLib);
				p->SetLibID(a->GetLibID());
				AppendItem(p);
			}
		}
	}
	else{
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			p->ReloadFromLibrary();
		}
	}
	if(Mask!=NULL){
		FlexArea	Area;
		Area.BuildFromRaster((BYTE **)Mask,(GetDotPerLine()+7)/8 ,GetMaxLines(),0,0);
		for(AutoAlignmentSheet	*p=(AutoAlignmentSheet *)GetFirstData();p!=NULL;p=(AutoAlignmentSheet *)p->GetNext()){
			if(p->CreatedManual==false){
				p->SetArea(Area);
			}
		}
///		DeleteMatrixBuff(Mask,GetMaxLines());	//091209AutoMasking?I??
	}

	AutoAlignmentSheet	*SheetData[1000];
	int	SheetDataCount=0;
	AlgorithmItemPI	*p;
	while((p=GetFirstData())!=NULL){
		AutoAlignmentSheet	*a=dynamic_cast<AutoAlignmentSheet *>(p);
		if(a!=NULL){
			SheetData[SheetDataCount]=a;
			SheetDataCount++;
			if(SheetDataCount>=sizeof(SheetData)/sizeof(SheetData[0])){
				break;
			}
		}
		RemoveItem(p);
	}
	QSort(SheetData,SheetDataCount,sizeof(AutoAlignmentSheet	*),SheetDataFunc);
	for(int i=0;i<SheetDataCount;i++){
		AppendItem(SheetData[i]);
	}

	bool	BackupCalcSingleThread=GetParamGlobal()->CalcSingleThread;
	GetParamGlobal()->CalcSingleThread=true;
	AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	GetParamGlobal()->CalcSingleThread=BackupCalcSingleThread;

	MatrixBuffClear((BYTE **)ResultPerPixXFromTarget,0 ,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultPerPixYFromTarget,0 ,XLen,YLen);

	AlgorithmItemPI	*FirstP=GetFirstData();
	if(FirstP!=NULL){
		AutoAlignmentSheet	*FirstSheet=dynamic_cast<AutoAlignmentSheet *>(FirstP);
		for(p=FirstP->GetNext();p!=NULL;p=p->GetNext()){
			AutoAlignmentSheet	*aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=NULL){
				aSeet->SetBasePointer(FirstSheet);
			}
		}
	}
////////////
	////phase?I??
	//PhaseProcess();
////////////
	return _ER_true;
}
void	AutoAlignmentInPage::CreateSheet(AlgorithmLibraryListContainer &SelectedLibList)
{
	IntList LayerList;
	SelectAll(LayerList);
	DeleteSelectedItems(LayerList);

	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryLevelContainer	SrcLib(GetLibraryContainer());
		if(GetLibraryContainer()->GetLibrary(a->GetLibID(),SrcLib)==true){
			AutoAlignmentSheet	*p=(AutoAlignmentSheet *)CreateItem(0);
			p->CopyThresholdFromLibrary(&SrcLib);
			AppendItem(p);
		}
	}
	ConstMapBufferListContainer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap);
	ConstMapBuffer Map;
	MaskMap.BindOr(Map);
	if(Map.IsEmpty()==false){
		FlexArea	Area;
		Area.BuildFromRaster((BYTE **)Map.GetBitMap(),(GetDotPerLine()+7)/8 ,GetMaxLines(),0,0);
		for(AutoAlignmentSheet	*p=(AutoAlignmentSheet *)GetFirstData();p!=NULL;p=(AutoAlignmentSheet *)p->GetNext()){
			p->SetArea(Area);
		}
		//DeleteMatrixBuff(Mask,GetMaxLines());
	}
	ResultInspection	*RCalc=GetLayersBase()->GetCurrentResultForCalc();
	if(RCalc!=NULL){
		ResultBaseForAlgorithmRoot	*r=RCalc->GetResultBaseForAlgorithm(GetParentBase());
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
		GetParentBase()->GetLogicDLL()->ExecuteInitialAfterEdit	(0,r,EInfo);
	}
}

int	AutoAlignmentInPage::GetMaxSearchDot(void)
{
	int	MaxSearchDot=0;

	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		AutoAlignmentSheet	*a=dynamic_cast<AutoAlignmentSheet *>(p);
		if(a!=NULL){
			if(a->GetThresholdR(GetLayersBase())->PicoShift>MaxSearchDot){
				MaxSearchDot=a->GetThresholdR(GetLayersBase())->PicoShift;
			}
		}
	}
	return MaxSearchDot;
}



bool	AutoAlignmentInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;

	return true;
}

bool	AutoAlignmentInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;

	return true;
}

ExeResult	AutoAlignmentInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteStartByInspection(ExeID ,Res);
	AlignedDx=0;
	AlignedDy=0;
	AlignedTheta=0;

#if	defined(NeedFringeBit)
	MatrixBuffClear(ResultBitTransFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitTransFromTarget ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstTransFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstTransFromTarget ,0,XByte,YLen);
#endif
	MatrixBuffClear(ResultBitPickupFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitPickupFromTarget ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstPickupFromMaster ,0,XByte,YLen);
	MatrixBuffClear(ResultBitFirstPickupFromTarget ,0,XByte,YLen);

	MatrixBuffClear((BYTE **)ResultRelativeXFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeYFromTarget ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeXFromMaster ,0,XLen,YLen);
	MatrixBuffClear((BYTE **)ResultRelativeYFromMaster ,0,XLen,YLen);

	NoAdjustMode=false;

	return Ret;
}

static	int	Error;

ExeResult	AutoAlignmentInPage::ExecuteAlignment(int ExeID ,ResultInPageRoot *Res)
{
	AutoAlignmentBase	*PBase=(AutoAlignmentBase *)GetParentBase();

	double	dx=0.0;
	double	dy=0.0;
	double	Theta=0.0;

	AutoAlignmentInPageMonoMiniSize	*a=AutoAlignmentInPageMonoMiniSizeContainer.GetFirst();
	if(a==NULL){
		return _ER_true;
	}
	a->CreateTargetMap();
	/*
	a->FirstMatch(dx ,dy ,Theta
		, PBase->SearchDot/a->SparseDot ,PBase->MaxThetaDegree*M_PI/180.0);

	for(a=a->GetNext();a!=NULL;a=a->GetNext()){
		a->CreateTargetMap();
		a->SlightMatch(dx ,dy ,Theta
			, dx*2,dy*2,Theta);
	}
	*/
	a->FirstMatch(dx ,dy, PBase->SearchDot/a->SparseDot);

	for(a=a->GetNext();a!=NULL;a=a->GetNext()){
		a->CreateTargetMap();
		a->SlightMatch(dx ,dy , dx*2,dy*2);
	}
	a=AutoAlignmentInPageMonoMiniSizeContainer.GetLast();
	dx*=a->SparseDot;
	dy*=a->SparseDot;

	AlignedDx=dx;
	AlignedDy=dy;
	AlignedTheta=Theta;

	ExeResult	Ret=AlgorithmInPagePI::ExecuteAlignment(ExeID,Res);

	AlgorithmItemPI	*p=GetFirstData();
	AutoAlignmentSheet	*aSeet;
	if(p!=NULL){
		aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL){
			aSeet->PutShiftMapAll();
		}
		for(p=p->GetNext();p!=NULL;p=p->GetNext()){
			aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=NULL){
				aSeet->PutShiftMap();
			}
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			char	*s=ResultPerPixXFromTarget[y];
			char	*Xt=ResultPerPixXFromTarget[y];
			char	*Yt=ResultPerPixYFromTarget[y];
			for(int x=0;x<XLen;x++){
				if(s[x]==0x7F){
					int	kx,ky;
					bool	Found=false;
					for(int L=1;L<100;L++){
						Found=InnerSearchEffectiveDot(L,x ,y,kx ,ky);
						if(Found==true){
							break;
						}
					}
					if(Found==true){
						if(kx>=XLen || kx<0 || ky<0 || ky>=YLen || x>=XLen || x<0 || y<0 || y>=YLen){
							Error++;
						}
						else{
							Xt[x]=(*(ResultPerPixXFromTarget+ky))[kx];
							Yt[x]=(*(ResultPerPixYFromTarget+ky))[kx];
						}
					}
					else{
						Error++;
					}
				}
			}
		}
	}
	if(NoAdjustMode==false){
		p=GetFirstData();
		if(p!=NULL){
			for(p=p->GetNext();p!=NULL;p=p->GetNext()){
				aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
				if(aSeet!=NULL){
					aSeet->AvoidOverlap();
				}
			}
		}
	}

#if	defined(NeedFringeBit)
	p=GetFirstData();
	if(p!=NULL){
		for(p=p->GetNext();p!=NULL;p=p->GetNext()){
			aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=NULL){
				aSeet->SetTransBit();
			}
		}
	}
	p=GetFirstData();
	if(p!=NULL){
		aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL){
			aSeet->SetFirstTransBit();
		}
	}
#endif
	p=GetFirstData();
	if(p!=NULL){
		for(p=p->GetNext();p!=NULL;p=p->GetNext()){
			aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=NULL){
				aSeet->SetPickupBit();
			}
		}
	}
	p=GetFirstData();
	if(p!=NULL){
		aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL){
			aSeet->SetFirstPickupBit();
		}
	}

	for(AlignmentPacket2DList *p=AlignmentPacket2DContainer.GetFirst();p!=NULL;p=p->GetNext()){
		p->ShiftX=*(ResultPerPixXFromMaster[p->PosYOnTarget]+p->PosXOnTarget);
		p->ShiftY=*(ResultPerPixYFromMaster[p->PosYOnTarget]+p->PosXOnTarget);
		p->Calculated=true;
	}
	return Ret;
}
bool	AutoAlignmentInPage::InnerSearchEffectiveDot(int L,int x ,int y,int &kx ,int &ky)
{
	char	*tx;
	ky=y-L;
	if(ky>=0){
		tx=ResultPerPixXFromTarget[ky];
		for(kx=x-L;kx<x+L;kx++){
			if(0<=kx && kx<XLen){
				if(tx[kx]!=0x7F){
					return true;
				}
			}
		}
	}
	kx=x+L;
	if(kx<XLen){
		for(ky=y-L;ky<y+L;ky++){
			if(0<=ky && ky<YLen){
				tx=ResultPerPixXFromTarget[ky];
				if(tx[kx]!=0x7F){
					return true;
				}
			}
		}
	}
	ky=y+L;
	if(ky<YLen){
		tx=ResultPerPixXFromTarget[ky];
		for(kx=x+L;kx>x-L;kx--){
			if(0<=kx && kx<XLen){
				if(tx[kx]!=0x7F){
					return true;
				}
			}
		}
	}
	kx=x-L;
	if(kx>=0){
		for(ky=y+L;ky>y-L;ky--){
			if(0<=ky && ky<YLen){
				tx=ResultPerPixXFromTarget[ky];
				if(tx[kx]!=0x7F){
					return true;
				}
			}
		}
	}
	return false;
}


void	AutoAlignmentInPage::GetAlignment(AlignmentPacketWithColor *c)
{
	for(int	Mergin=0;Mergin<128;Mergin+=16){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			AutoAlignmentSheet	*p=dynamic_cast<AutoAlignmentSheet *>(a);
			if(p!=NULL){
				if(p->ColorIsIncluded(c,Mergin)==true && p->GetAlignment(c)==true){
					return;
				}
			}
		}
	}
}

void	AutoAlignmentInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAutoAlignmentNoAdjustPacket	*CmdAutoAlignmentNoAdjustPacketVar=dynamic_cast<CmdAutoAlignmentNoAdjustPacket *>(packet);
	if(CmdAutoAlignmentNoAdjustPacketVar!=NULL){
		NoAdjustMode=true;
		return;
	}
	CmdGetSheetLevel	*CmdGetSheetLevelVar=dynamic_cast<CmdGetSheetLevel *>(packet);
	if(CmdGetSheetLevelVar!=NULL){
		CmdGetSheetLevelVar->SheetLevels.RemoveAll();
		for(AutoAlignmentInPageMonoMiniSize *a=AutoAlignmentInPageMonoMiniSizeContainer.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetSheetLevelVar->SheetLevels.Add(a->SparseDot);
		}
		return;
	}
	CmdGetAutoAlignmentSheetPacket	*CmdGetAutoAlignmentSheetPacketVar=dynamic_cast<CmdGetAutoAlignmentSheetPacket *>(packet);
	if(CmdGetAutoAlignmentSheetPacketVar!=NULL){
		AlgorithmLibraryListContainer LibIDList;
		GetParentBase()->GetLibraryContainer()->EnumLibrary(LibIDList);
		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){

			LibList[CountLibList]=new AlgorithmLibraryLevelContainer(Container);
			if(Container->GetLibrary(L->GetLibID() ,*LibList[CountLibList])==true){
				AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(LibList[CountLibList]->GetLibrary());
				if(ALib->StartupExecute==true){
					CountLibList++;
					if(CountLibList>=sizeof(LibList)/sizeof(LibList[0])){
						break;
					}
				}
			}
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int i=0;i<CountLibList-1;i++){
				AutoAlignmentLibrary	*L1=dynamic_cast<AutoAlignmentLibrary *>(LibList[i  ]->GetLibrary());
				AutoAlignmentLibrary	*L2=dynamic_cast<AutoAlignmentLibrary *>(LibList[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	TmpLib(Container);
					TmpLib=*LibList[i];
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			AutoAlignmentLibrary	*L=dynamic_cast<AutoAlignmentLibrary *>(LibList[i]->GetLibrary());
			AASheetInfoList	*h=new AASheetInfoList(LibList[i]->GetLibID(),L->PicoShift,false);
			CmdGetAutoAlignmentSheetPacketVar->Point->AppendList(h);
		}
		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}

		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			AutoAlignmentSheet	*aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=NULL){
				if(aSeet->CreatedManual==true){
					AASheetInfoList	*h;
					for(h=CmdGetAutoAlignmentSheetPacketVar->Point->GetFirst();h!=NULL;h=h->GetNext()){
						if(h->ID==aSeet->GetLibID() && h->CreatedManual==true){
							break;
						}
					}
					if(h==NULL){
						AASheetInfoList	*h=new AASheetInfoList(aSeet->GetLibID(),aSeet->GetThresholdR(GetLayersBase())->PicoShift,aSeet->CreatedManual);
						CmdGetAutoAlignmentSheetPacketVar->Point->AppendList(h);
					}
				}
			}
		}
		return;
	}
	CmdGetAutoAlignmentResult	*CmdGetAutoAlignmentResultVar=dynamic_cast<CmdGetAutoAlignmentResult *>(packet);
	if(CmdGetAutoAlignmentResultVar!=NULL){
		if(ResultPerPixXFromMaster!=NULL){
			CmdGetAutoAlignmentResultVar->ShiftXFromMaster=GetShiftXFromMaster(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftYFromMaster=GetShiftYFromMaster(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftXFromTarget=GetShiftXFromTarget(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftYFromTarget=GetShiftYFromTarget(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftRelativeXFromMaster=GetRelativeShiftXFromMaster(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftRelativeYFromMaster=GetRelativeShiftYFromMaster(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftRelativeXFromTarget=GetRelativeShiftXFromTarget(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
			CmdGetAutoAlignmentResultVar->ShiftRelativeYFromTarget=GetRelativeShiftYFromTarget(CmdGetAutoAlignmentResultVar->LocalX,CmdGetAutoAlignmentResultVar->LocalY);
		}
		else{
			CmdGetAutoAlignmentResultVar->ShiftXFromMaster=0;
			CmdGetAutoAlignmentResultVar->ShiftYFromMaster=0;
			CmdGetAutoAlignmentResultVar->ShiftXFromTarget=0;
			CmdGetAutoAlignmentResultVar->ShiftYFromTarget=0;
			CmdGetAutoAlignmentResultVar->ShiftRelativeXFromMaster=0;
			CmdGetAutoAlignmentResultVar->ShiftRelativeYFromMaster=0;
			CmdGetAutoAlignmentResultVar->ShiftRelativeXFromTarget=0;
			CmdGetAutoAlignmentResultVar->ShiftRelativeYFromTarget=0;
		}
		return;
	}
	CmdSetAutoAlignmentLibColor	*CmdSetAutoAlignmentLibColorVar=dynamic_cast<CmdSetAutoAlignmentLibColor *>(packet);
	if(CmdSetAutoAlignmentLibColorVar!=NULL){

	}
	CmdAddAutoAlignmentSheet	*CmdAddAutoAlignmentSheetVar=dynamic_cast<CmdAddAutoAlignmentSheet *>(packet);
	if(CmdAddAutoAlignmentSheetVar!=NULL){
		AlgorithmItemRoot	*ManualItem=CreateItem(0);
		ManualItem->SetArea(CmdAddAutoAlignmentSheetVar->LocalArea);
		ManualItem->SetLibID(CmdAddAutoAlignmentSheetVar->LibID);
		AutoAlignmentSheet	*Item=(AutoAlignmentSheet *)ManualItem;
		Item->CreatedManual=true;
		AppendItem(ManualItem);
		return;
	}
}

void	AutoAlignmentInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	AutoAlignmentDrawAttr	*A=(AutoAlignmentDrawAttr *)Attr;
	if(A!=NULL){
		AutoAlignmentInPageMonoMiniSize *a=AutoAlignmentInPageMonoMiniSizeContainer.GetItem(A->MonoLevel);
		if(a!=NULL){
			a->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
}
bool	AutoAlignmentInPage::DrawResult(ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	AlgorithmInPagePI::DrawResult(Res,IData ,PData ,MovX ,MovY ,ZoomRate);
	for(AutoAlignmentInPageMonoMiniSize *a=AutoAlignmentInPageMonoMiniSizeContainer.GetFirst();a!=NULL;a=a->GetNext()){
		ResultInItemPI	DummyItem;
		a->DrawResult(DummyItem,IData ,PData ,MovX ,MovY ,ZoomRate,false);
	}
	return true;
}

bool	AutoAlignmentInPage::ExistArea(int localX ,int localY)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		AutoAlignmentSheet	*aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL){
			if(aSeet->ExistArea(localX ,localY)==true)
				return true;
		}
	}
	return false;
}

void	AutoAlignmentInPage::PhaseProcess(void)
{
	//phase?I??
	if(GetGlobalPage()==GetPageNumb()-1){
		if(GetPhaseNumb()>=2){
			int CurrentPhase=GetLayersBase()->GetCurrentPhase();
			if((CurrentPhase+1)==GetPhaseNumb()){
				GetLayersBase()->SetCurrentPhase(0);
			}
			else{
				GetLayersBase()->SetCurrentPhase(CurrentPhase+1);
			}
		}
	}
}

AlignmentPacket2D	*AutoAlignmentInPage::AppendAlignmentPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal)
{
	if(ExistArea(localX,localY)==true){	
		AlignmentPacket2DList	*L=new AlignmentPacket2DList();
		L->LibType		=Item->GetParentBase()->GetLibType();
		L->LibID		=Item->GetLibID();
		L->PosXOnTarget	=localX;
		L->PosYOnTarget	=localY;
		AlignmentPacket2DCreaterMutex.lock();
		AlignmentPacket2DContainer.AppendList(L);
		AlignmentPacket2DCreaterMutex.unlock();
		return L;
	}
	return NULL;
}

///void	AutoAlignmentInPage::PickupTest(AutoAlignmentLibrary &LibData)
///void	AutoAlignmentInPage::PickupTest(int LibID)
void	AutoAlignmentInPage::PickupTest(void)
{
	if(GetFirstData()==NULL){
		AlgorithmLibraryListContainer	StartupLibList;
		AlgorithmLibraryListContainer	TmpStartupLibList;
		AlgorithmLibraryListContainer	AllLibIDList;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		GetParentBase()->GetLibraryContainer()->EnumLibrary(AllLibIDList);
		for(AlgorithmLibraryList *a=AllLibIDList.GetFirst();a!=NULL;a=a->GetNext()){					
			AlgorithmLibraryLevelContainer	TmpLib(Container);
			if(Container->GetLibrary(a->GetLibID(),TmpLib)==true){
				AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(TmpLib.GetLibrary());
				if(ALib->StartupExecute==true){
					AAAlgorithmLibraryList	*b=new AAAlgorithmLibraryList(*a);
					b->Priority=ALib->Priority;
					TmpStartupLibList.AppendList(b);
				}
			}
		}
		while(TmpStartupLibList.GetFirst()!=NULL){
			AAAlgorithmLibraryList	*Point=(AAAlgorithmLibraryList *)TmpStartupLibList.GetFirst();
			for(AAAlgorithmLibraryList *a=(AAAlgorithmLibraryList *)Point->GetNext();a!=NULL;a=(AAAlgorithmLibraryList *)a->GetNext()){
				if(Point->Priority>a->Priority){
					Point=a;
				}
			}
			TmpStartupLibList.RemoveList(Point);
			StartupLibList.AppendList(Point);
		}
		for(AAAlgorithmLibraryList *a=(AAAlgorithmLibraryList*)StartupLibList.GetFirst();a!=NULL;a=(AAAlgorithmLibraryList*)a->GetNext()){
			AutoAlignmentSheet	*p=(AutoAlignmentSheet *)CreateItem(0);
			AlgorithmLibraryLevelContainer	TmpLib(Container);
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(a->GetLibID(),TmpLib)==true){
				p->CopyThresholdFromLibrary(&TmpLib);
				p->SetLibID(a->GetLibID());
				AppendItem(p);
			}
		}
	}
	else{
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			p->ReloadFromLibrary();
		}
	}

		int Index=0;
		AutoAlignmentSheet	*wp=(AutoAlignmentSheet *)GetFirstData();
		for(AutoAlignmentSheet	*p=(AutoAlignmentSheet *)GetFirstData();p!=NULL;p=(AutoAlignmentSheet *)p->GetNext(),Index++){
			//PickupTest?I???W?b?N?d?O???E?U?A?s?e
			int		TransW;
			int		NoiseShrink;
			BYTE	**TmpMap,**TmpMap2;
			p->MakePickupTest(&TmpMap,&TmpMap2,TransW,NoiseShrink);

			//delete
			DeleteMatrixBuff(TmpMap		,GetMaxLines());
			DeleteMatrixBuff(TmpMap2	,GetMaxLines());

			if(Index==1){
				//?Q?A?U?IPickupBmp?c?c?P?A?U?IPickupBmp?d?o?-
				MatrixBuffNotAnd(p->GetPickupBmp(),(const BYTE **)wp->GetPickupBmp(),XByte,GetMaxLines());
			}
		}
//	}
}

//==================================================================================

AutoAlignmentBase::AutoAlignmentBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	SearchDot=20;
	MaxThetaDegree			=5;
	PicoSize				=200;
	SelectedLayer			=1;
	DetailThreshold			=0.6;
	Enabled					=true;
	MinTransDot				=1000;
	MaxHoleSize				=200;
	TransDot				=4;
	VectorMergin			=2;

	SetParam(&SearchDot				,/**/"Setting" ,/**/"SearchDot"		,LangSolver.GetString(XAutoAlignment_LS,LID_0)/*"Search area dot. Search area is defined for plus-minus this value"*/);
	SetParam(&MaxThetaDegree		,/**/"Setting" ,/**/"MaxThetaDegree",LangSolver.GetString(XAutoAlignment_LS,LID_9)/*"Search angle in degree. Search area is defined for plus-minus this value"*/);
	SetParam(&PicoSize				,/**/"Setting" ,/**/"PicoSize"		,LangSolver.GetString(XAutoAlignment_LS,LID_10)/*"Pico area size"*/);
	SetParam(&SelectedLayer			,/**/"Setting" ,/**/"SelectedLayer"	,LangSolver.GetString(XAutoAlignment_LS,LID_11)/*"Select one uniquest layer for calculation"*/);
	SetParam(&DetailThreshold		,/**/"Setting" ,/**/"DetailThreshold",LangSolver.GetString(XAutoAlignment_LS,LID_12)/*"0 - 1: If mathing level is under this, it calculates in detail mode"*/);
	SetParam(&Enabled				,/**/"Setting" ,/**/"Enabled"		,LangSolver.GetString(XAutoAlignment_LS,LID_13)/*"By unchecked state , alignment function is disabled (Shift=0 and Rotation=0)"*/);
	SetParam(&MinTransDot			,/**/"Setting" ,/**/"MinTransDot"	,LangSolver.GetString(XAutoAlignment_LS,LID_14)/*"Minimum TransferDot"*/);
	SetParam(&MaxHoleSize			,/**/"Setting" ,/**/"MaxHoleSize"	,LangSolver.GetString(XAutoAlignment_LS,LID_15)/*"Maximum hole size to remove inside matching outline"*/);
	SetParam(&TransDot				,/**/"Setting" ,/**/"TransDot"		,"Transfer dot length");
	SetParam(&VectorMergin			,/**/"Setting" ,/**/"VectorMergin"	,"Vector Mergin for adjust shift");
	//SetParam(&AdptedMatchingRate	,/**/"Setting" ,/**/"AdptedMatchingRate"		,"Minimum matching rate to adopt as vector (Max:1.0)");
	//SetParam(&CompletelyMatchingRate,/**/"Setting" ,/**/"CompletelyMatchingRate"	,"Minimum completely matching rate");
}

AlgorithmDrawAttr	*AutoAlignmentBase::CreateDrawAttr(void)
{
	return new AutoAlignmentDrawAttr();
}

bool	AutoAlignmentBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
	
bool	AutoAlignmentBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

ExeResult	AutoAlignmentBase::ExecuteInitialAfterEdit(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase		*Ph=Res->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			GetPageDataPhase(phase)->GetPageData(page)->ExecuteInitialAfterEdit(ExeID ,Ph->GetPageData(page),EInfo);
		}
	}
	return _ER_true;
}

void	AutoAlignmentBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestAutoAlignmentPacket	*AAPickLib=dynamic_cast<CmdPickupTestAutoAlignmentPacket *>(packet);
	if(AAPickLib!=NULL){
		GetLayersBase()->SetCurrentPhase(AAPickLib->PhaseNumb);
		AlgorithmInPageRoot		*p=GetPageDataPhase(AAPickLib->PhaseNumb)->GetPageData(AAPickLib->Page);
		if(p==NULL)
			return;
		AutoAlignmentInPage	*AAp=dynamic_cast<AutoAlignmentInPage *>(p);
		if(AAp==NULL)
			return;
///		AAp->PickupTest(*AAPickLib->LibPoint);		
///		AAp->PickupTest(AAPickLib->LibID);		
		AAp->PickupTest();		
		return;
	}
	CmdAutoAlignmentNoAdjustPacket	*CmdAutoAlignmentNoAdjustPacketVar=dynamic_cast<CmdAutoAlignmentNoAdjustPacket *>(packet);
	if(CmdAutoAlignmentNoAdjustPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetAutoAlignmentLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAutoAlignmentLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempAutoAlignmentLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAutoAlignmentLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadAutoAlignmentLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAutoAlignmentLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearAutoAlignmentLibraryPacket	*CmdClearAutoAlignmentLibraryPacketVar=dynamic_cast<CmdClearAutoAlignmentLibraryPacket *>(packet);
	if(CmdClearAutoAlignmentLibraryPacketVar!=NULL){
		CmdClearAutoAlignmentLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAutoAlignmentLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteAutoAlignmentLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertAutoAlignmentLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAutoAlignmentLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AutoAlignmentVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAutoAlignmentLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAutoAlignmentLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AutoAlignmentVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdCreateAutoAlignmentSheetPacket	*CmdCreateAutoAlignmentSheetPacketVar=dynamic_cast<CmdCreateAutoAlignmentSheetPacket *>(packet);
	if(CmdCreateAutoAlignmentSheetPacketVar!=NULL){
		AutoAlignmentInPage	*Pg=(AutoAlignmentInPage *)GetPageData(CmdCreateAutoAlignmentSheetPacketVar->LocalPage);
		Pg->CreateSheet(CmdCreateAutoAlignmentSheetPacketVar->SelectedLibList);
		return;
	}
	CmdGetSheetLevel	*CmdGetSheetLevelVar=dynamic_cast<CmdGetSheetLevel *>(packet);
	if(CmdGetSheetLevelVar!=NULL){
		AutoAlignmentInPage	*Pg=(AutoAlignmentInPage *)GetPageData(CmdGetSheetLevelVar->LocalPage);
		Pg->TransmitDirectly(packet);
		return;
	}
	CmdGetAutoAlignmentLibraryNamePacket	*CmdGetAutoAlignmentLibraryNamePacketVar=dynamic_cast<CmdGetAutoAlignmentLibraryNamePacket *>(packet);
	if(CmdGetAutoAlignmentLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetAutoAlignmentLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetAutoAlignmentLibraryNamePacketVar->LibID,TmpLib);
			CmdGetAutoAlignmentLibraryNamePacketVar->LibName=TmpLib.GetLibName();
		}
		return;
	}
	CmdReqAutoAlignmentEnumLibs	*CmdReqAutoAlignmentEnumLibsVar=dynamic_cast<CmdReqAutoAlignmentEnumLibs *>(packet);
	if(CmdReqAutoAlignmentEnumLibsVar!=NULL){
		AlgorithmLibraryListContainer LibIDList;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		Container->EnumLibrary(LibIDList);
		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer	LibDest(Container);
			if(Container->GetLibrary(L->GetLibID() ,LibDest)==true){
				AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(LibDest.GetLibrary());
				if(ALib->StartupExecute==true){
					LibList[CountLibList]=new AlgorithmLibraryLevelContainer(Container);
					*LibList[CountLibList]=LibDest;
					CountLibList++;
					if(CountLibList>=sizeof(LibList)/sizeof(LibList[0])){
						break;
					}
				}
			}
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int i=0;i<CountLibList-1;i++){
				AutoAlignmentLibrary	*L1=dynamic_cast<AutoAlignmentLibrary *>(LibList[i  ]->GetLibrary());
				AutoAlignmentLibrary	*L2=dynamic_cast<AutoAlignmentLibrary *>(LibList[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	TmpLib(Container);
					TmpLib=*LibList[i];
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			CmdReqAutoAlignmentEnumLibsVar->LibIDList.Add(LibList[i]->GetLibID());
		}
		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}
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
