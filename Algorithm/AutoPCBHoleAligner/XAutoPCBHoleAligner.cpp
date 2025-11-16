/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoPCBHoleAligner.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoPCBHoleAlignerResource.h"
#include "XAutoPCBHoleAligner.h"
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
#include "XImageProcess.h"
#include "ChangeCreateAutoPCBHoleAlignerForm.h"

//#include "XGeneralFunc.h"
//#include "ImageControlTools.h"
//#include "XDLLOnly.h"
#include "XGUI.h"
//#include "XPointer.h"

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

AutoPCBHoleAlignerLibrary::AutoPCBHoleAlignerLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	StartupExecute	=false;
	ExpandForPickup	=3;
	MinDiameter		=10;
	MaxDiameter		=100;
	FringeDot		=20;
	CheckOutside	=false;
	MaxSearch		=10;
	ThresholdDiff	=100;

	FromOtherAlgorithmCount=0;
}

bool	AutoPCBHoleAlignerLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=AutoPCBHoleAlignerVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(PickupHoleColor.Save(f)==false)
		return false;
	if(::Save(f,StartupExecute)==false)
		return false;
	if(::Save(f,ExpandForPickup)==false)
		return false;
	if(::Save(f,MinDiameter)==false)
		return false;
	if(::Save(f,MaxDiameter)==false)
		return false;
	if(::Save(f,FringeDot)==false)
		return false;
	if(::Save(f,CheckOutside)==false)
		return false;
	if(::Save(f,MaxSearch)==false)
		return false;
	if(::Save(f,ThresholdDiff)==false)
		return false;

	return true;
}
bool	AutoPCBHoleAlignerLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(PickupHoleColor.Load(f)==false)
		return false;
	if(::Load(f,StartupExecute)==false)
		return false;
	if(::Load(f,ExpandForPickup)==false)
		return false;
	if(::Load(f,MinDiameter)==false)
		return false;
	if(::Load(f,MaxDiameter)==false)
		return false;
	if(::Load(f,FringeDot)==false)
		return false;
	if(::Load(f,CheckOutside)==false)
		return false;
	if(::Load(f,MaxSearch)==false)
		return false;
	if(::Load(f,ThresholdDiff)==false)
		return false;
	return true;
}

AutoPCBHoleAlignerLibrary	&AutoPCBHoleAlignerLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AutoPCBHoleAlignerLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AutoPCBHoleAlignerLibraryContainer::AutoPCBHoleAlignerLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
AutoPCBHoleAlignerLibraryContainer::~AutoPCBHoleAlignerLibraryContainer(void)
{
}


//====================================================================================================

AutoPCBHoleAlignerThreshold::AutoPCBHoleAlignerThreshold(AutoPCBHoleAlignerHole *parent)
:AlgorithmThreshold(parent)
{
	ExpandForPickup			=3;
	MinDiameter				=10;
	MaxDiameter				=100;
	FringeDot				=20;
	CheckOutside			=false;
	FromOtherAlgorithm		=false;
	FromOtherAlgorithmIndex	=0;
}

void	AutoPCBHoleAlignerThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AutoPCBHoleAlignerThreshold	*s=(const AutoPCBHoleAlignerThreshold *)&src;
	PickupHoleColor			=s->PickupHoleColor;
	ExpandForPickup			=s->ExpandForPickup;
	MinDiameter				=s->MinDiameter;
	MaxDiameter				=s->MaxDiameter;
	FringeDot				=s->FringeDot;
	CheckOutside			=s->CheckOutside;
	FromOtherAlgorithm		=s->FromOtherAlgorithm		;
	FromOtherAlgorithmIndex	=s->FromOtherAlgorithmIndex	;
}
bool	AutoPCBHoleAlignerThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AutoPCBHoleAlignerThreshold	*s=(const AutoPCBHoleAlignerThreshold *)&src;
	if(PickupHoleColor			!=s->PickupHoleColor		)	return false;
	if(ExpandForPickup			!=s->ExpandForPickup		)	return false;
	if(MinDiameter				!=s->MinDiameter			)	return false;
	if(MaxDiameter				!=s->MaxDiameter			)	return false;
	if(FringeDot				!=s->FringeDot				)	return false;
	if(CheckOutside				!=s->CheckOutside			)	return false;
	if(FromOtherAlgorithm		!=s->FromOtherAlgorithm		)	return false;
	if(FromOtherAlgorithmIndex	!=s->FromOtherAlgorithmIndex)	return false;
	return true;
}
bool	AutoPCBHoleAlignerThreshold::Save(QIODevice *f)
{
	if(PickupHoleColor.Save(f)==false)
		return false;
	if(::Save(f,ExpandForPickup)==false)
		return false;
	if(::Save(f,MinDiameter)==false)
		return false;
	if(::Save(f,MaxDiameter)==false)
		return false;
	if(::Save(f,FringeDot)==false)
		return false;
	if(::Save(f,CheckOutside)==false)
		return false;
	if(::Save(f,FromOtherAlgorithm)==false)
		return false;
	if(::Save(f,FromOtherAlgorithmIndex)==false)
		return false;
	return true;
}
bool	AutoPCBHoleAlignerThreshold::Load(QIODevice *f)
{
	if(PickupHoleColor.Load(f)==false)
		return false;
	if(::Load(f,ExpandForPickup)==false)
		return false;
	if(::Load(f,MinDiameter)==false)
		return false;
	if(::Load(f,MaxDiameter)==false)
		return false;
	if(::Load(f,FringeDot)==false)
		return false;
	if(::Load(f,CheckOutside)==false)
		return false;
	if(::Load(f,FromOtherAlgorithm)==false)
		return false;
	if(::Load(f,FromOtherAlgorithmIndex)==false)
		return false;
	return true;
}

void	AutoPCBHoleAlignerThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AutoPCBHoleAlignerLibrary	*s=(AutoPCBHoleAlignerLibrary *)src;
	PickupHoleColor		=s->PickupHoleColor;
	ExpandForPickup		=s->ExpandForPickup;
	MinDiameter			=s->MinDiameter;
	MaxDiameter			=s->MaxDiameter;
	FringeDot			=s->FringeDot;
	CheckOutside		=s->CheckOutside;
}

void	AutoPCBHoleAlignerThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AutoPCBHoleAlignerLibrary	*d=(AutoPCBHoleAlignerLibrary *)Dest;
	d->PickupHoleColor	=PickupHoleColor;
	d->ExpandForPickup	=ExpandForPickup;
	d->MinDiameter		=MinDiameter;
	d->MaxDiameter		=MaxDiameter;
	d->FringeDot		=FringeDot;
	d->CheckOutside		=CheckOutside;
}

//====================================================================================================
AutoPCBHoleAlignerHole::AutoPCBHoleAlignerHole(void)
{
}
AutoPCBHoleAlignerHole::~AutoPCBHoleAlignerHole(void)
{
}

ExeResult	AutoPCBHoleAlignerHole::ExecuteInitialAfterEdit	(int ExeID 
															,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	FringeArea=GetArea();
	int	mx=GetArea().GetMinX()-8-GetThresholdR()->FringeDot;
	int	my=GetArea().GetMinY()-8-GetThresholdR()->FringeDot;
	FringeArea.MoveToNoClip(-mx,-my);
	int	XLen=FringeArea.GetMaxX()+8+GetThresholdR()->FringeDot;
	int	YLen=FringeArea.GetMaxY()+8+GetThresholdR()->FringeDot;
	int	XByte=(XLen+7)/8;

	BYTE	BmpImageBuff[5000];
	BYTE	TmpImageBuff[5000];

	BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen,BmpImageBuff,sizeof(BmpImageBuff));
	//BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(BmpImage,0,XByte,YLen);
	BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen,TmpImageBuff,sizeof(TmpImageBuff));
	//BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(TmpImage,0,XByte,YLen);

	FringeArea.MakeBitData(BmpImage,XLen,YLen);

	GetLayersBase()->FatAreaN(BmpImage
				,TmpImage
				,XByte ,YLen
				,GetThresholdR()->FringeDot);

	FringeArea.BuildFromRaster(BmpImage,XByte ,YLen,0,0);

	//?????a?d?P?h?b?g?Å~?c?1?e
	FlexArea	ShrinkHole=GetArea();
	ShrinkHole.MoveToNoClip(-mx,-my);
	MatrixBuffClear(BmpImage,0,XByte,YLen);
	ShrinkHole.MakeBitData(BmpImage ,XByte ,YLen);
	ThinArea(BmpImage
			,TmpImage
			,XByte ,YLen);
	ShrinkHole.BuildFromRaster(BmpImage,XByte ,YLen,0,0);

	FringeArea	.MoveToNoClip(mx,my);
	ShrinkHole	.MoveToNoClip(mx,my);
	FringeArea	.Sub(FringeArea,ShrinkHole);

	if((BYTE	**)BmpImageBuff!=BmpImage){
		DeleteMatrixBuff(BmpImage,YLen);
	}
	if((BYTE	**)TmpImageBuff!=TmpImage){
		DeleteMatrixBuff(TmpImage,YLen);
	}
	return _ER_true;
}

bool    AutoPCBHoleAlignerHole::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
//	if(::Save(file,GetThresholdR()->FromOtherAlgorithm)==false)
//		return false;
	return true;
}

bool    AutoPCBHoleAlignerHole::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
//	if(::Load(file,GetThresholdW()->FromOtherAlgorithm)==false)
//		return false;
	return true;
}

void	AutoPCBHoleAlignerHole::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AutoPCBHoleAlignerDrawAttr	*a=dynamic_cast<AutoPCBHoleAlignerDrawAttr *>(Attr);
	if(a!=NULL && ((a->SelectedLDList.IsEmpty()==true) || a->SelectedLDList.IsInclude(GetLibID()))){
		if(a->DrawHole==true){
			GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
		}
		if(a->DrawFringe==true){
			FringeArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
		}
	}
}

//====================================================================================================

AutoPCBHoleAlignerInPage::AutoPCBHoleAlignerInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	BitmapFringe=NULL;
}

AutoPCBHoleAlignerInPage::~AutoPCBHoleAlignerInPage(void)
{
	Release();
}

class	AAAlgorithmLibraryList : public AlgorithmLibraryList
{
public:
	int	Priority;

	AAAlgorithmLibraryList(const AlgorithmLibraryList &src):AlgorithmLibraryList(src){}
};

void	AutoPCBHoleAlignerInPage::InitialAlloc(void)
{
	Release();
	XLen=GetDotPerLine();
	YLen=GetMaxLines();
	XByte=(XLen+7)/8;

	BitmapFringe=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(BitmapFringe ,0,XByte,YLen);
}
void	AutoPCBHoleAlignerInPage::Release(void)
{
	if(BitmapFringe!=NULL){
		DeleteMatrixBuff(BitmapFringe,YLen);
		BitmapFringe=NULL;
	}
}

ExeResult	AutoPCBHoleAlignerInPage::ExecuteInitialAfterEdit(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),4);
	GetLayersBase()->StepProcessing(GetPage());

	InitialAlloc();

//	RemoveAllDatas();

	QList<int>	&DeleteLibIDList=((AutoPCBHoleAlignerBase *)GetParentBase())->DeleteLibIDListFromOtherAlgorithm;
	QList<int>	&DeleteIndexList=((AutoPCBHoleAlignerBase *)GetParentBase())->DeleteIndexListFromOtherAlgorithm;
	int ListCnt=DeleteIndexList.count();
//	qSort(DeleteIndexList.begin(),DeleteIndexList.end(),qGreater<int>());

	for(AlgorithmItemPI *ItemPI=Data.GetFirst();ItemPI!=NULL;){
		AutoPCBHoleAlignerHole *AAlignHole=dynamic_cast<AutoPCBHoleAlignerHole *>(ItemPI);
		if(AAlignHole->GetThresholdR(GetLayersBase())->FromOtherAlgorithm==false){
			AlgorithmItemPI *ItemPINext=ItemPI->GetNext();
			Data.RemoveList(AAlignHole);
			delete	AAlignHole;
			ItemPI=ItemPINext;
		}
		else{
			for(int i=0;i<ListCnt;i++){
				if(AAlignHole->GetLibID()==DeleteLibIDList.at(i) && AAlignHole->GetThresholdR(GetLayersBase())->FromOtherAlgorithmIndex==DeleteIndexList.at(i)){
					AlgorithmItemPI *ItemPINext=ItemPI->GetNext();
					Data.RemoveList(AAlignHole);
					delete	AAlignHole;
					AAlignHole=NULL;
					ItemPI=ItemPINext;
					break;
				}
			}
			if(AAlignHole!=NULL){
				int DecrementCnt=0;
				for(int i=0;i<ListCnt;i++){
					if(AAlignHole->GetLibID()==DeleteLibIDList.at(i) && AAlignHole->GetThresholdR(GetLayersBase())->FromOtherAlgorithmIndex>DeleteIndexList.at(i)){
						DecrementCnt++;
					}
				}
				if(DecrementCnt>0){
					AAlignHole->GetThresholdW()->FromOtherAlgorithmIndex=AAlignHole->GetThresholdR(GetLayersBase())->FromOtherAlgorithmIndex-DecrementCnt;
				}
				ItemPI=ItemPI->GetNext();
			}
		}
	}
	for(int i=0;i<ListCnt;i++){
		int FromOtherACnt=((AutoPCBHoleAlignerBase *)GetParentBase())->GetFromOtherAlgorithmCount(DeleteLibIDList.at(i));
		((AutoPCBHoleAlignerBase *)GetParentBase())->SetFromOtherAlgorithmCount(DeleteLibIDList.at(i),FromOtherACnt-1);
	}
	DeleteLibIDList.clear();
	DeleteIndexList.clear();

	ConstMapBufferListContainer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap);
	ConstMapBuffer Map;
	MaskMap.BindOr(Map);
	const BYTE	**Mask=Map.GetBitMap();
	if(Map.IsEmpty()==true){
		return _ER_true;
	}

	BYTE	**HoleMap=MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);
	AutoPCBHoleAlignerBase	*PBase=(AutoPCBHoleAlignerBase *)GetParentBase();
	ImagePointerContainer Images;
	GetMasterImages(Images);
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	for(AlgorithmLibraryList *a=PBase->AdoptedLib.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryLevelContainer	Lib(Container);
		if(Container->GetLibrary(a->GetLibID() ,Lib)==true){
			AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(Lib.GetLibrary());
			MakeBitmap(Map.GetBitMap(),TmpMap,Images,*ALib,HoleMap);
		}
	}
	DeleteMatrixBuff(HoleMap,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
///	DeleteMatrixBuff(Mask,YLen);

	GetLayersBase()->StepProcessing(GetPage());

	AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	GetLayersBase()->StepProcessing(GetPage());

	MatrixBuffClear(BitmapFringe,0,XByte,YLen);
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		AutoPCBHoleAlignerHole	*b=(AutoPCBHoleAlignerHole *)a;
		b->GetArea().MakeBitData(BitmapFringe,GetDotPerLine(),GetMaxLines());
	}

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BitmapFringe , XByte , XLen, YLen ,FPack);
	MatrixBuffClear(BitmapFringe,0,XByte,YLen);
	PureFlexAreaList *f;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		int64	N=f->GetPatternByte();
		int64	L=max(f->GetWidth(),f->GetHeight());
		if(N>=L*L*PBase->AdoptedRate || L<5){
			f->MakeBitData(BitmapFringe,GetDotPerLine(),GetMaxLines());
		}
		delete	f;
	}
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
		int	Cx,Cy;
		a->GetCenter(Cx,Cy);
		if(GetBitmapFringe(Cx,Cy)==false){
			AlgorithmItemPI	*HNext=a->GetNext();
			RemoveItem(a);
			delete	a;
			a=HNext;
		}
		else{
			a=a->GetNext();
		}
	}

	MatrixBuffClear(BitmapFringe,0,XByte,YLen);
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		AutoPCBHoleAlignerHole	*b=(AutoPCBHoleAlignerHole *)a;
		b->FringeArea.MakeBitData(BitmapFringe,GetDotPerLine(),GetMaxLines());
	}

	GetLayersBase()->StepProcessing(GetPage());

	return _ER_true;
}

static	int		DebugX=1494;
static	int		DebugY=3155;
static	bool	DebugFound=false;

void	AutoPCBHoleAlignerInPage::MakeBitmap(const BYTE	**Mask
											 ,BYTE	**TmpMap
											 ,ImagePointerContainer &MasterImages
											 ,AutoPCBHoleAlignerLibrary &Lib
											 ,BYTE	**HoleMap)
{
	AutoPCBHoleAlignerBase	*PBase=(AutoPCBHoleAlignerBase *)GetParentBase();

	Lib.PickupHoleColor.MakeBitmap(MasterImages,HoleMap ,XLen ,YLen);
	MatrixBuffAnd(HoleMap ,Mask ,XByte ,YLen);

	if(Lib.MinDiameter>=3){
		ThinArea(HoleMap
					,TmpMap
					,XByte ,YLen);

		FatArea(HoleMap
					,TmpMap
					,XByte ,YLen);
	}

	PureFlexAreaListContainer FPack;
	PickupFlexArea(HoleMap , XByte , XLen, YLen ,FPack);
	MatrixBuffClear(HoleMap,0,XByte,YLen);
	PureFlexAreaList *f;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		if(f->IsInclude(DebugX,DebugY)==true){
			DebugFound=true;
		}

		if(Lib.MinDiameter<=f->GetWidth() && f->GetWidth()<=Lib.MaxDiameter
		&& Lib.MinDiameter<=f->GetHeight() && f->GetHeight()<=Lib.MaxDiameter){
			int64	N=f->GetPatternByte();
			int64	L=max(f->GetWidth(),f->GetHeight());
			int	CenterX ,CenterY;
			f->GetCenter(CenterX ,CenterY);
			if(N>=L*L*PBase->AdoptedRate*((double)(L*L)/(double)((L+2)*(L+2)))
			&& (Lib.CheckOutside==false || CheckOutside(CenterX ,CenterY
												,MasterImages
												,Lib.MaxSearch+((L+1)>>1) ,Lib.ThresholdDiff)==true)){
				f->MakeBitData(HoleMap,GetDotPerLine(),GetMaxLines());
			}
		}
		delete	f;
	}

	GetLayersBase()->FatAreaN(HoleMap
				,TmpMap
				,XByte ,YLen
				,Lib.ExpandForPickup);

	PickupFlexArea(HoleMap , XByte , XLen, YLen ,FPack);
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		if(f->IsInclude(DebugX,DebugY)==true){
			DebugFound=true;
		}

		if(Lib.MinDiameter<=f->GetWidth() && f->GetWidth()<=Lib.MaxDiameter
		&& Lib.MinDiameter<=f->GetHeight() && f->GetHeight()<=Lib.MaxDiameter){
			int64	N=f->GetPatternByte();
			int64	L=max(f->GetWidth(),f->GetHeight());
			int	CenterX ,CenterY;
			f->GetCenter(CenterX ,CenterY);
			if((N>=L*L*PBase->AdoptedRate || L<5)
			&& (Lib.CheckOutside==false || CheckOutside(CenterX ,CenterY
												,MasterImages
												,Lib.MaxSearch+((L+1)>>1) ,Lib.ThresholdDiff)==true)){
				AutoPCBHoleAlignerHole	*p=(AutoPCBHoleAlignerHole *)CreateItem(0);
				p->SetArea(*f);
				p->SetLibID(Lib.GetLibID());
				p->CopyThresholdFromLibrary(Lib.GetParentLevelContainer());
				AppendItem(p);
			}
		}
		delete	f;
	}
}

bool	AutoPCBHoleAlignerInPage::CheckOutside(int CenterX ,int CenterY
											 ,ImagePointerContainer &MasterImages
											 ,int MaxSearch ,int ThresholdDiff)
{
	//?a?o?Å˜?E?E???e?Åë???a?a?s?T?E?Å˜?Y?ÅE?e?c?2?Å~?e
	ImageBuffer	*RBuff=MasterImages[0];
	ImageBuffer	*GBuff=MasterImages[1];
	ImageBuffer	*BBuff=MasterImages[2];
	bool	Found;

	Found=false;
	for(int L=1;L<MaxSearch;L++){
		int	Dr=0;
		int	Dg=0;
		int	Db=0;
		int	N=0;
		for(int y=CenterY+L-1;y<=CenterY+L+1;y++){
			if(y<0 || y>=GetMaxLines()){
				continue;
			}
			BYTE	*R=RBuff->GetY(y);
			BYTE	*G=GBuff->GetY(y);
			BYTE	*B=BBuff->GetY(y);
			for(int x=CenterX-1;x<=CenterX+1;x++){
				if(x<0 || x>=GetDotPerLine()){
					continue;
				}
				Dr+=R[x];
				Dg+=G[x];
				Db+=B[x];
				N++;
			}
		}
		if(N>0){
			Dr/=N;
			Dg/=N;
			Db/=N;
			if(Dr>=ThresholdDiff || Db>=ThresholdDiff || Dg>=ThresholdDiff){
				Found=true;
				break;
			}
		}
	}
	if(Found==false){
		return false;
	}

	Found=false;
	for(int L=1;L<MaxSearch;L++){
		int	Dr=0;
		int	Dg=0;
		int	Db=0;
		int	N=0;
		for(int y=CenterY-L-1;y<=CenterY-L+1;y++){
			if(y<0 || y>=GetMaxLines()){
				continue;
			}
			BYTE	*R=RBuff->GetY(y);
			BYTE	*G=GBuff->GetY(y);
			BYTE	*B=BBuff->GetY(y);
			for(int x=CenterX-1;x<=CenterX+1;x++){
				if(x<0 || x>=GetDotPerLine()){
					continue;
				}
				Dr+=R[x];
				Dg+=G[x];
				Db+=B[x];
				N++;
			}
		}
		if(N>0){
			Dr/=N;
			Dg/=N;
			Db/=N;
			if(Dr>=ThresholdDiff || Db>=ThresholdDiff || Dg>=ThresholdDiff){
				Found=true;
				break;
			}
		}
	}
	if(Found==false){
		return false;
	}

	Found=false;
	for(int L=1;L<MaxSearch;L++){
		int	Dr=0;
		int	Dg=0;
		int	Db=0;
		int	N=0;
		for(int y=CenterY-1;y<=CenterY+1;y++){
			if(y<0 || y>=GetMaxLines()){
				continue;
			}
			BYTE	*R=RBuff->GetY(y);
			BYTE	*G=GBuff->GetY(y);
			BYTE	*B=BBuff->GetY(y);
			for(int x=CenterX+L-1;x<=CenterX+L+1;x++){
				if(x<0 || x>=GetDotPerLine()){
					continue;
				}
				Dr+=R[x];
				Dg+=G[x];
				Db+=B[x];
				N++;
			}
		}
		if(N>0){
			Dr/=N;
			Dg/=N;
			Db/=N;
			if(Dr>=ThresholdDiff || Db>=ThresholdDiff || Dg>=ThresholdDiff){
				Found=true;
				break;
			}
		}
	}
	if(Found==false){
		return false;
	}

	Found=false;
	for(int L=1;L<MaxSearch;L++){
		int	Dr=0;
		int	Dg=0;
		int	Db=0;
		int	N=0;
		for(int y=CenterY-1;y<=CenterY+1;y++){
			if(y<0 || y>=GetMaxLines()){
				continue;
			}
			BYTE	*R=RBuff->GetY(y);
			BYTE	*G=GBuff->GetY(y);
			BYTE	*B=BBuff->GetY(y);
			for(int x=CenterX-L-1;x<=CenterX-L+1;x++){
				if(x<0 || x>=GetDotPerLine()){
					continue;
				}
				Dr+=R[x];
				Dg+=G[x];
				Db+=B[x];
				N++;
			}
		}
		if(N>0){
			Dr/=N;
			Dg/=N;
			Db/=N;
			if(Dr>=ThresholdDiff || Db>=ThresholdDiff || Dg>=ThresholdDiff){
				Found=true;
				break;
			}
		}
	}
	if(Found==false){
		return false;
	}
	return true;
}

bool	AutoPCBHoleAlignerInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;

	return true;
}

bool	AutoPCBHoleAlignerInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;

	return true;
}

void	AutoPCBHoleAlignerInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetHoleInfo	*CmdGetHoleInfoVar=dynamic_cast<CmdGetHoleInfo *>(packet);
	if(CmdGetHoleInfoVar!=NULL){
		AlgorithmLibraryListContainer LibIDList;
		GetParentBase()->GetLibraryContainer()->EnumLibrary(LibIDList);
		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer LibDest(Container);
			if(Container->GetLibrary(L->GetLibID() ,LibDest)==true){
				AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(LibDest.GetLibrary());
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
				if(LibList[i]->GetLibID()>LibList[i+1]->GetLibID()){
					AlgorithmLibraryLevelContainer	TmpLib(*LibList[i]);
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			AutoPCBHoleAlignerLibrary	*L=dynamic_cast<AutoPCBHoleAlignerLibrary *>(LibList[i]->GetLibrary());
			AAHoleInfoList	*h=new AAHoleInfoList();
			h->ID			=L->GetLibID();
			h->MinDiameter	=L->MinDiameter;
			h->MaxDiameter	=L->MaxDiameter;
			h->FringeDot	=L->FringeDot;
			CmdGetHoleInfoVar->AAInfoData.AppendList(h);
		}
		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}

		return;
	}
	/*
	CmdGetHoleLevel	*CmdGetHoleLevelVar=dynamic_cast<CmdGetHoleLevel *>(packet);
	if(CmdGetHoleLevelVar!=NULL){
		CmdGetHoleLevelVar->HoleLevels.RemoveAll();
		for(AutoPCBHoleAlignerInPageMonoMiniSize *a=AutoPCBHoleAlignerInPageMonoMiniSizeContainer.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetHoleLevelVar->HoleLevels.Add(a->SparseDot);
		}
		return;
	}
	CmdGetAutoPCBHoleAlignerResult	*CmdGetAutoPCBHoleAlignerResultVar=dynamic_cast<CmdGetAutoPCBHoleAlignerResult *>(packet);
	if(CmdGetAutoPCBHoleAlignerResultVar!=NULL){
		CmdGetAutoPCBHoleAlignerResultVar->ShiftXFromMaster=GetShiftXFromMaster(CmdGetAutoPCBHoleAlignerResultVar->LocalX,CmdGetAutoPCBHoleAlignerResultVar->LocalY);
		CmdGetAutoPCBHoleAlignerResultVar->ShiftYFromMaster=GetShiftYFromMaster(CmdGetAutoPCBHoleAlignerResultVar->LocalX,CmdGetAutoPCBHoleAlignerResultVar->LocalY);
		CmdGetAutoPCBHoleAlignerResultVar->ShiftXFromTarget=GetShiftXFromTarget(CmdGetAutoPCBHoleAlignerResultVar->LocalX,CmdGetAutoPCBHoleAlignerResultVar->LocalY);
		CmdGetAutoPCBHoleAlignerResultVar->ShiftYFromTarget=GetShiftYFromTarget(CmdGetAutoPCBHoleAlignerResultVar->LocalX,CmdGetAutoPCBHoleAlignerResultVar->LocalY);
		return;
	}
	*/
}

//==================================================================================

AutoPCBHoleAlignerBase::AutoPCBHoleAlignerBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	AdoptedRate=0.5;
	StartupExecuteLibIDList.clear();
	DeleteLibIDListFromOtherAlgorithm.clear();
	DeleteIndexListFromOtherAlgorithm.clear();
	SetParam(&AdoptedRate, /**/"Setting",/**/"AdoptedRate",LangSolver.GetString(XAutoPCBHoleAligner_LS,LID_0)/*"Minimum rate of Dot count in hole / Diameter^2, Smaller is easier to pick up"*/);
}

AlgorithmDrawAttr	*AutoPCBHoleAlignerBase::CreateDrawAttr(void)
{
	return new AutoPCBHoleAlignerDrawAttr();
}

bool	AutoPCBHoleAlignerBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
	
bool	AutoPCBHoleAlignerBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

ExeResult	AutoPCBHoleAlignerBase::ExecuteInitialAfterEdit(int ExeID 
															,ResultBaseForAlgorithmRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	if(AdoptedLib.IsEmpty()==true){
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryListContainer	TmpLibContainer;
		Container->EnumLibrary(GetLibType(),TmpLibContainer);
		for(AlgorithmLibraryList *a=TmpLibContainer.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryLevelContainer	SrcLib(Container);
			if(Container->GetLibrary(a->GetLibID() ,SrcLib)==true){
				AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(SrcLib.GetLibrary());
				if(ALib->StartupExecute==true){
					AdoptedLib.Add(GetLibraryContainer()->GetLibType(),SrcLib);
					StartupExecuteLibIDList.append(ALib->GetLibID());
				}
			}
		}
		//FromOtherAlgorithmCount
		FromOtherAlgorithmCount=new int[StartupExecuteLibIDList.count()];
		for(int i=0;i<StartupExecuteLibIDList.count();i++){
			FromOtherAlgorithmCount[i]=0;
		}
	}
	return AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}


void	AutoPCBHoleAlignerBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit	*AExecInitAfterEdit=dynamic_cast<CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit *>(packet);
	if(AExecInitAfterEdit!=NULL){
		//ExecuteInitialAfterEdit?d?-?s
		ResultInspection	*RCalc=GetLayersBase()->GetCurrentResultForCalc();
		if(RCalc!=NULL){
			ResultBaseForAlgorithmRoot	*r=RCalc->GetResultBaseForAlgorithm(this);
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			GetLogicDLL()->ExecuteInitialAfterEdit	(0,r,EInfo);
		}
		return;
	}
	CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm	*ADelIndex=dynamic_cast<CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm *>(packet);
	if(ADelIndex!=NULL){
		//?i???I?UIndex?I?a??
		DeleteLibIDListFromOtherAlgorithm.append(ADelIndex->LibID);
		DeleteIndexListFromOtherAlgorithm.append(ADelIndex->DeleteIndex);
		//FromOtherAlgorithmCount?I?f?N???????g
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	SrcLib(this);
			if(GetLibraryContainer()->GetLibrary(ADelIndex->LibID,SrcLib)==true){
				AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(SrcLib.GetLibrary());
				ALib->FromOtherAlgorithmCount--;
				GetLibraryContainer()->Update(SrcLib);
			}
		}
		return;
	}
	CmdGetAutoPCBHoleAlignerLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAutoPCBHoleAlignerLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempAutoPCBHoleAlignerLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAutoPCBHoleAlignerLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		}
		return;
	}
	CmdLoadAutoPCBHoleAlignerLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAutoPCBHoleAlignerLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearAutoPCBHoleAlignerLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearAutoPCBHoleAlignerLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAutoPCBHoleAlignerLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteAutoPCBHoleAlignerLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertAutoPCBHoleAlignerLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAutoPCBHoleAlignerLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AutoPCBHoleAlignerVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAutoPCBHoleAlignerLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAutoPCBHoleAlignerLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AutoPCBHoleAlignerVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdCreateAutoPCBHoleAlignerHolePacket	*CmdCreateAutoPCBHoleAlignerHolePacketVar=dynamic_cast<CmdCreateAutoPCBHoleAlignerHolePacket *>(packet);
	if(CmdCreateAutoPCBHoleAlignerHolePacketVar!=NULL){
		AutoPCBHoleAlignerInPage	*Pg=(AutoPCBHoleAlignerInPage *)GetPageData(CmdCreateAutoPCBHoleAlignerHolePacketVar->LocalPage);
		AdoptedLib=CmdCreateAutoPCBHoleAlignerHolePacketVar->SelectedLibList;
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
		Pg->ExecuteInitialAfterEdit(0,NULL,EInfo);
		return;
	}
	CmdGetAutoPCBHoleAlignerLibraryNamePacket	*CmdGetAutoPCBHoleAlignerLibraryNamePacketVar=dynamic_cast<CmdGetAutoPCBHoleAlignerLibraryNamePacket *>(packet);
	if(CmdGetAutoPCBHoleAlignerLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetAutoPCBHoleAlignerLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetAutoPCBHoleAlignerLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetAutoPCBHoleAlignerLibraryNamePacketVar->Success==true){
				CmdGetAutoPCBHoleAlignerLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
	CmdReqAutoPCBHoleAlignerEnumLibs	*CmdReqAutoPCBHoleAlignerEnumLibsVar=dynamic_cast<CmdReqAutoPCBHoleAlignerEnumLibs *>(packet);
	if(CmdReqAutoPCBHoleAlignerEnumLibsVar!=NULL){
		AlgorithmLibraryListContainer LibIDList;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		Container->EnumLibrary(LibIDList);
		AlgorithmLibraryLevelContainer	*LibList[1000];
		int						CountLibList=0;
		for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){		
			AlgorithmLibraryLevelContainer	SrcLib(Container);
			if(Container->GetLibrary(L->GetLibID() ,SrcLib)==true){
				AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(SrcLib.GetLibrary());
				if(ALib->StartupExecute==true){
					LibList[CountLibList]=new AlgorithmLibraryLevelContainer(Container);
					*LibList[CountLibList]=SrcLib;
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
				if(LibList[i]->GetLibID()>LibList[i+1]->GetLibID()){
					AlgorithmLibraryLevelContainer	TmpLib(*LibList[i]);
					*LibList[i]=*LibList[i+1];
					*LibList[i+1]=TmpLib;
					RetryMode=true;
					break;
				}
			}
		}while(RetryMode==true);

		for(int i=0;i<CountLibList;i++){
			CmdReqAutoPCBHoleAlignerEnumLibsVar->LibIDList.Add(LibList[i]->GetLibID());
		}
		for(int i=0;i<CountLibList;i++){
			delete	LibList[i];
		}
		return;
	}
}

bool	AutoPCBHoleAlignerBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	ChangeCreateAutoPCBHoleAlignerForm	Q(this,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultAutoPCBHoleAligner.Save(&Buff)==false){
			return false;
		}
		GUIFormBase	*BaseStartCaptureButtonForDesktop=GetLayersBase()->FindByName(/**/"Action" ,/**/"StartCaptureButtonForDesktop" ,/**/"");
		if(BaseStartCaptureButtonForDesktop!=NULL){
			CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape	Packet(GetLayersBase());
			Packet.LibID					=Q.ResultAutoPCBHoleAligner.GetLibID();
			Packet.FromOtherAlgorithmIndex	=Q.ResultAutoPCBHoleAligner.GetThresholdR()->FromOtherAlgorithmIndex;
			BaseStartCaptureButtonForDesktop->TransmitDirectly(&Packet);
		}
	}
	return ret;
}
