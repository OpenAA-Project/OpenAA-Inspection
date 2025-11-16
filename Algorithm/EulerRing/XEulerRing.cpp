/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRing.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XEulerRingResource.h"
#include "XEulerRing.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"

//=====================================================================================
EulerRingThreshold::EulerRingThreshold(EulerRingItem *parent)
:AlgorithmThreshold(parent)
{
	ExpandedDot		=2;
	Mergin			=10;
    AdjustBlack		=20;    //‹P“x•â³‚Ì‰ºŒÀ•
    AdjustWhite		=20;    //‹P“x•â³‚ÌãŒÀ•
}

void	EulerRingThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const EulerRingThreshold *s=(const EulerRingThreshold *)&src;
    AdjustBlack		=s->AdjustBlack;
    AdjustWhite		=s->AdjustWhite;
	InspectionColor	=s->InspectionColor;
	ExpandedDot		=s->ExpandedDot;
	Mergin			=s->Mergin;

	if(InspectionColor.IsEnableTable()==true)
		InspectionColor.CreateTable(Mergin);
}
bool	EulerRingThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const EulerRingThreshold *s=(const EulerRingThreshold *)&src;

    if(AdjustBlack		!=s->AdjustBlack	)	return false;
    if(AdjustWhite		!=s->AdjustWhite	)	return false;
	if(InspectionColor	!=s->InspectionColor)	return false;
	if(ExpandedDot		!=s->ExpandedDot	)	return false;
	if(Mergin			!=s->Mergin			)	return false;
	return false;
}
bool	EulerRingThreshold::Save(QIODevice *file)
{
	if(InspectionColor.Save(file)==false)
		return false;
	if(::Save(file,Mergin)==false)
		return false;
	if(::Save(file,AdjustBlack)==false)
		return false;
	if(::Save(file,AdjustWhite)==false)
		return false;
	if(::Save(file,ExpandedDot)==false)
		return false;
	return true;
}

bool	EulerRingThreshold::Load(QIODevice *file)
{
	if(InspectionColor.Load(file)==false)
		return false;
	if(::Load(file,Mergin)==false)
		return false;
	if(::Load(file,AdjustBlack)==false)
		return false;
	if(::Load(file,AdjustWhite)==false)
		return false;
	if(::Load(file,ExpandedDot)==false)
		return false;
	return true;
}

void	EulerRingThreshold::FromLibrary(AlgorithmLibrary *src)
{
	EulerRingLibrary	*LSrc=dynamic_cast<EulerRingLibrary *>(src);
	if(LSrc==NULL)
		return;
	Mergin			=LSrc->Mergin;
	InspectionColor	=LSrc->InspectionColor;
	AdjustBlack	=LSrc->AdjustBlack;
	AdjustWhite	=LSrc->AdjustWhite;
	ExpandedDot	=LSrc->ExpandedDot;
}
void	EulerRingThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	EulerRingLibrary	*LDst=dynamic_cast<EulerRingLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->Mergin			=Mergin	;
	LDst->InspectionColor	=InspectionColor;
	LDst->AdjustBlack		=AdjustBlack	;
	LDst->AdjustWhite		=AdjustWhite	;
	LDst->ExpandedDot		=ExpandedDot	;
}

//=====================================================================================

bool	ResultClusterOnItem::Save(QIODevice *f)
{
	if(ResultArea.Save(f)==false)
		return false;
	return true;
}

bool	ResultClusterOnItem::Load(QIODevice *f)
{
	if(ResultArea.Load(f)==false)
		return false;
	return true;
}

//=====================================================================================


EulerRingItem::EulerRingItem(void)
{
	InitialConstructor();
}
EulerRingItem::EulerRingItem(FlexArea &area)
:AlgorithmItemPI(area)
{
	InitialConstructor();
}

void EulerRingItem::InitialConstructor(void)
{
	AVector=NULL;
}

AlgorithmItemPI	&EulerRingItem::operator=(const AlgorithmItemRoot &src)
{
	const EulerRingItem	*s=dynamic_cast<const EulerRingItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}
EulerRingItem &EulerRingItem::operator=(EulerRingItem &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(src);
	return *this;
}

void	EulerRingItem::CopyThreshold(EulerRingItem &src)
{
	GetThresholdW()->CopyFrom(*((EulerRingThreshold *)src.GetThresholdR()));
}

void	EulerRingItem::CopyThresholdOnly(EulerRingItem &src)
{
	GetThresholdW()->CopyFrom(*((EulerRingThreshold *)src.GetThresholdR()));
}

bool    EulerRingItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
	return true;
}
bool    EulerRingItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
	return true;
}

void	EulerRingItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((EulerRingItem *)Data));
			GetThresholdW()->InspectionColor.CreateTable(GetThresholdW()->Mergin);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((EulerRingItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((EulerRingItem *)Data));
			GetThresholdW()->InspectionColor.CreateTable(GetThresholdW()->Mergin);
		}
	}
}


int		EulerRingItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}
void	EulerRingItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	EulerRingItem	*ASrc=dynamic_cast<EulerRingItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((EulerRingBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
	}
}

ExeResult	EulerRingItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(IsOriginParts()==false){
		GetThresholdW()->InspectionColor.CreateTable(GetThresholdW()->Mergin);
	}
	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	EulerRingItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID)
		DbgNumer++;

	const EulerRingThreshold	*RThr=GetThresholdR();
	ColorLogic	InsColor;
	InsColor=*((ColorLogic *)&RThr->InspectionColor);

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

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
	short	Error=1;
	if(GetTargetBuff()[0]->IsNull()==false){
		if(ExecuteProcessingInner(Res
								  ,mx ,my
								  ,InsColor
								  ,RThr->Mergin)==false){
				Error = 0x02;	//Lˆæ‚Å‚m‚f”­¶
				Res->SetError(2);
				FinishCalc();
				return _ER_true;
		}
	}
	Res->SetError(Error);
	FinishCalc();
	return _ER_true;
}

void	EulerRingItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	EulerRingDrawAttr	*BAttr=dynamic_cast<EulerRingDrawAttr *>(Attr);
	if(BAttr!=NULL){
		EulerRingDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		switch(GetLibID()&7){
			case 0:	TmpAttr.NormalColor=BAttr->BlockColor0;	break;
			case 1:	TmpAttr.NormalColor=BAttr->BlockColor1;	break;
			case 2:	TmpAttr.NormalColor=BAttr->BlockColor2;	break;
			case 3:	TmpAttr.NormalColor=BAttr->BlockColor3;	break;
			case 4:	TmpAttr.NormalColor=BAttr->BlockColor4;	break;
			case 5:	TmpAttr.NormalColor=BAttr->BlockColor5;	break;
			case 6:	TmpAttr.NormalColor=BAttr->BlockColor6;	break;
			case 7:	TmpAttr.NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	EulerRingItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false){
				QColor	d=Qt::yellow;
				d.setAlpha(150);
				((ResultClusterOnItem *)Res->GetAddedData())->ResultArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,d.rgba()
							,ZoomRate ,MovX ,MovY);
			}
		}
	}
}

//===========================================================================================
EulerRingInPage::EulerRingInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte=0;
	PickupBmpYLen=0;
}
EulerRingInPage::~EulerRingInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

void	EulerRingInPage::CreatePickupBmpBuff(void)
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

void	EulerRingInPage::PickupTest(EulerRingLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		ImagePointerContainer	ImageList;
		GetDataInPage()->GetMasterImages(ImageList);
		LibData.MakePickupTest(ImageList
								,Map.GetBitMap()
								,PickupBmp,NULL
								,GetPage()
								,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
								,((EulerRingBase *)GetParentBase())->OmitZoneDot);
	}
}
void	EulerRingInPage::GenerateBlocks(EulerRingLibrary *LibDim[],int LibDimNumb)
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
	BYTE **GeneratedMap=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(GeneratedMap,0,XByte,GetMaxLines());

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(GetParentBase());
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
				LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
			}
			else{
				delete	Lib;
				Lib=NULL;
			}
		}
		if(Lib!=NULL){
			EulerRingLibrary	*BLib=dynamic_cast<EulerRingLibrary *>(Lib->GetLibrary());
			L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
		}
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	BYTE **tMaskMap	=MakeMatrixBuff(XByte,GetMaxLines());

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i])==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			const BYTE	**MaskBitmap=Map.GetBitMap();

			MatrixBuffCopy(tMaskMap,XByte,GetMaxLines()
			             , MaskBitmap,XByte,GetMaxLines());
			MatrixBuffNotAnd (tMaskMap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

			ImagePointerContainer	ImageList;
			GetDataInPage()->GetMasterImages(ImageList);
			LibDim[i]->MakePickupTest(ImageList
									,(const BYTE **)tMaskMap
									,CurrentMap,OcupyMap
									,GetPage()
									,XByte ,GetDotPerLine(),GetMaxLines()
									,((EulerRingBase *)GetParentBase())->OmitZoneDot);

			NPListPack<AlgorithmItemPI>	TmpBlockData;
			LibDim[i]->MakeBlock(
				 CurrentMap,LastOcupyMap
				 ,GetPage()
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
	DeleteMatrixBuff(CurrentMap	 ,GetMaxLines());
	DeleteMatrixBuff(OcupyMap	 ,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap,GetMaxLines());
	DeleteMatrixBuff(GeneratedMap,GetMaxLines());
	DeleteMatrixBuff(tMaskMap	 ,GetMaxLines());
}
void	EulerRingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedEulerRingFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedEulerRingFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		EulerRingItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			EulerRingItem	*B=(EulerRingItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				EulerRingItem	*B=(EulerRingItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
	}
	CmdClearTestEulerRingPacket	*CmdClearTestEulerRingPacketVar=dynamic_cast<CmdClearTestEulerRingPacket *>(packet);
	if(CmdClearTestEulerRingPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
	}
	CmdEulerRingInfoListPacket	*CmdEulerRingInfoListPacketVar=dynamic_cast<CmdEulerRingInfoListPacket *>(packet);
	if(CmdEulerRingInfoListPacketVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			EulerRingInfoList	*a;
			for(a=CmdEulerRingInfoListPacketVar->EulerRingInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->EulerRingCount.GetItem(0);
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new EulerRingInfoList();
				a->LibID=L->GetLibID();
				a->EulerRingCount.Add(1);
				CmdEulerRingInfoListPacketVar->EulerRingInfos->AppendList(a);
			}
		}
	}
	CmdGetEulerRingFromList	*CmdGetEulerRingFromListVar=dynamic_cast<CmdGetEulerRingFromList *>(packet);
	if(CmdGetEulerRingFromListVar!=NULL){
		EulerRingItem *Item=(EulerRingItem *)SearchIDItem(CmdGetEulerRingFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetEulerRingFromListVar->EulerRingInfoOnMouse=Item;
	}
	CmdCreateEulerRingItem	*CmdCreateEulerRingItemVar=dynamic_cast<CmdCreateEulerRingItem *>(packet);
	if(CmdCreateEulerRingItemVar!=NULL){
		CmdCreateEulerRingItemVar->EulerRing=(EulerRingItem *)CreateItem(0);
	}
}

bool	EulerRingInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	return true;
}
bool	EulerRingInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	return true;
}

void	EulerRingInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	EulerRingDrawAttr	*BAttr=dynamic_cast<EulerRingDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==EulerRingDrawAttr::_LibTest){
			if(PickupBmp!=NULL){
				EulerRingBase	*BBase=dynamic_cast<EulerRingBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==EulerRingDrawAttr::_CreatedBlock){
			AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	}
}

//===========================================================================================
EulerRingBase::EulerRingBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	EulerRingNormal		=Qt::darkGreen;
	EulerRingSelected	=Qt::green;
	EulerRingActive		=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;

	SetParam(&ColorPickup		, /**/"Color" ,/**/"ColorPickup"		,"Color for Image to Pickup-Test ");
	SetParam(&EulerRingNormal	, /**/"Color" ,/**/"EulerRingNormal"	,"Color for Area");
	SetParam(&EulerRingSelected	, /**/"Color" ,/**/"EulerRingSelected"	,"Color for Selected Area");
	SetParam(&EulerRingActive	, /**/"Color" ,/**/"EulerRingActive"	,"Color for Active Area");

	SetParam(&BlockColor0	, /**/"BlockColor" ,/**/"BlockColor0"	,"Area Color 0");
	SetParam(&BlockColor1	, /**/"BlockColor" ,/**/"BlockColor1"	,"Area Color 1");
	SetParam(&BlockColor2	, /**/"BlockColor" ,/**/"BlockColor2"	,"Area Color 2");
	SetParam(&BlockColor3	, /**/"BlockColor" ,/**/"BlockColor3"	,"Area Color 3");
	SetParam(&BlockColor4	, /**/"BlockColor" ,/**/"BlockColor4"	,"Area Color 4");
	SetParam(&BlockColor5	, /**/"BlockColor" ,/**/"BlockColor5"	,"Area Color 5");
	SetParam(&BlockColor6	, /**/"BlockColor" ,/**/"BlockColor6"	,"Area Color 6");
	SetParam(&BlockColor7	, /**/"BlockColor" ,/**/"BlockColor7"	,"Area Color 7");

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,"Omit zone dot in area generation");
}

AlgorithmDrawAttr	*EulerRingBase::CreateDrawAttr(void)
{
	return new EulerRingDrawAttr();
}

void	EulerRingBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetEulerRingLibraryListPacket	*AListPacket=dynamic_cast<CmdGetEulerRingLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetEulerRingLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetEulerRingLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertEulerRingLibraryPacket	*BInsLib=dynamic_cast<CmdInsertEulerRingLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(EulerRingVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateEulerRingLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateEulerRingLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(EulerRingVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadEulerRingLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadEulerRingLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempEulerRingLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempEulerRingLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearEulerRingLibraryPacket	*CmdClearEulerRingLibraryPacketVar=dynamic_cast<CmdClearEulerRingLibraryPacket *>(packet);
	if(CmdClearEulerRingLibraryPacketVar!=NULL){
		CmdClearEulerRingLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteEulerRingLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteEulerRingLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestEulerRingPacket	*BPickLib=dynamic_cast<CmdPickupTestEulerRingPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		EulerRingInPage	*Bp=dynamic_cast<EulerRingInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(*(EulerRingLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateEulerRingPacket	*BGenerated=dynamic_cast<CmdGenerateEulerRingPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}

		EulerRingLibrary	**DDim=new EulerRingLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<EulerRingLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			EulerRingInPage	*Bp=dynamic_cast<EulerRingInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(DDim,N);		
			}
		}
		delete	[]DDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		return;
	}
	CmdCreateTempEulerRingItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempEulerRingItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new EulerRingItem();
		return;
	}
	CmdCreateByteArrayFromEulerRingItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromEulerRingItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdAddByteEulerRingItemPacket	*AddBItem=dynamic_cast<CmdAddByteEulerRingItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			EulerRingItem	*Item=new EulerRingItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
	}
	CmdLoadEulerRingItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadEulerRingItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedEulerRingFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedEulerRingFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdClearTestEulerRingPacket	*CmdClearTestEulerRingPacketVar=dynamic_cast<CmdClearTestEulerRingPacket *>(packet);
	if(CmdClearTestEulerRingPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestEulerRingPacketVar);
		}
	}
	CmdEulerRingInfoListPacket	*CmdEulerRingInfoListPacketVar=dynamic_cast<CmdEulerRingInfoListPacket *>(packet);
	if(CmdEulerRingInfoListPacketVar!=NULL){
		GetPageData(CmdEulerRingInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetEulerRingFromList	*CmdGetEulerRingFromListVar=dynamic_cast<CmdGetEulerRingFromList *>(packet);
	if(CmdGetEulerRingFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetEulerRingFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateEulerRingItem	*CmdCreateEulerRingItemVar=dynamic_cast<CmdCreateEulerRingItem *>(packet);
	if(CmdCreateEulerRingItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

ExeResult	EulerRingBase::ExecuteInitialAfterEdit(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}


bool	EulerRingBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==EulerRingHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*EulerRingBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==EulerRingHistogramListSendCommand){
		EulerRingHistogramListSend	*pSend=new EulerRingHistogramListSend();
		if(reqData!=NULL){
			EulerRingHistogramListReq	*req=(EulerRingHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingHistogramListReqCommand){
		return new EulerRingHistogramListReq();
	}
	else if(Command==EulerRingReqThresholdReqCommand){
		return new EulerRingThresholdReq();
	}
	else if(Command==EulerRingReqThresholdSendCommand){
		EulerRingThresholdSend	*pSend=new EulerRingThresholdSend();
		if(reqData!=NULL){
			EulerRingThresholdReq	*req=(EulerRingThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingReqTryThresholdCommand){
		return new EulerRingReqTryThreshold();
	}
	else if(Command==EulerRingSendTryThresholdCommand){
		EulerRingSendTryThreshold	*pSend=new EulerRingSendTryThreshold();
		if(reqData!=NULL){
			EulerRingReqTryThreshold	*req=(EulerRingReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingReqChangeShiftCommand){
		return new EulerRingChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	EulerRingBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==EulerRingHistogramListSendCommand){
		EulerRingHistogramListSend	*p=(EulerRingHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingHistogramListReqCommand){
		EulerRingHistogramListReq	*p=(EulerRingHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingReqThresholdReqCommand){
		EulerRingThresholdReq	*p=(EulerRingThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingReqThresholdSendCommand){
		EulerRingThresholdSend	*p=(EulerRingThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingReqTryThresholdCommand){
		EulerRingReqTryThreshold	*p=(EulerRingReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==EulerRingSendTryThresholdCommand){
		EulerRingSendTryThreshold	*p=(EulerRingSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingReqChangeShiftCommand){
		EulerRingChangeShift	*p=(EulerRingChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	EulerRingBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==EulerRingHistogramListSendCommand){
		EulerRingHistogramListSend	*p=(EulerRingHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingHistogramListReqCommand){
		EulerRingHistogramListReq	*p=(EulerRingHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingReqThresholdReqCommand){
		EulerRingThresholdReq	*p=(EulerRingThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingReqThresholdSendCommand){
		EulerRingThresholdSend	*p=(EulerRingThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingReqTryThresholdCommand){
		EulerRingReqTryThreshold	*p=(EulerRingReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingSendTryThresholdCommand){
		EulerRingSendTryThreshold	*p=(EulerRingSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingReqChangeShiftCommand){
		EulerRingChangeShift	*p=(EulerRingChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	EulerRingBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==EulerRingHistogramListSendCommand){
		EulerRingHistogramListSend	*p=(EulerRingHistogramListSend *)data;
		return true;
	}
	else if(Command==EulerRingHistogramListReqCommand){
		EulerRingHistogramListReq	*p=(EulerRingHistogramListReq *)data;
		return true;
	}
	else if(Command==EulerRingReqThresholdReqCommand){
		EulerRingThresholdReq	*p=(EulerRingThresholdReq *)data;
		return true;
	}
	else if(Command==EulerRingReqThresholdSendCommand){
		EulerRingThresholdSend	*p=(EulerRingThresholdSend *)data;
		return true;
	}
	else if(Command==EulerRingReqTryThresholdCommand){
		EulerRingReqTryThreshold	*p=(EulerRingReqTryThreshold *)data;
		return true;
	}
	else if(Command==EulerRingSendTryThresholdCommand){
		EulerRingSendTryThreshold	*p=(EulerRingSendTryThreshold *)data;
		return true;
	}
	else if(Command==EulerRingReqChangeShiftCommand){
		EulerRingChangeShift	*p=(EulerRingChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}



