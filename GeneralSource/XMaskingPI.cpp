/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMaskingPI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XMaskingPIResource.h"
#include "XMaskingPI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XGUIFormBase.h"
#include "omp.h"

MaskingPIThreshold::MaskingPIThreshold(MaskingPIItem *parent)
:AlgorithmThreshold(parent)
{
	Effective=false;
}

void	MaskingPIThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MaskingPIThreshold *s=(const MaskingPIThreshold *)&src;
    SelAreaID=s->SelAreaID;
	Effective=s->Effective;
}
bool	MaskingPIThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MaskingPIThreshold *s=(const MaskingPIThreshold *)&src;
    if(SelAreaID!=s->SelAreaID)	return false;
	if(Effective!=s->Effective)	return false;
	return true;
}
bool	MaskingPIThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,Effective)==false)
		return(false);
	if(SelAreaID.Save(file)==false)
		return(false);
	return(true);
}
bool	MaskingPIThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,Effective)==false)
		return(false);
	if(SelAreaID.Load(file)==false)
		return(false);
	return(true);
}

AlgorithmItemPI	&MaskingPIItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    MaskingPIItem::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    MaskingPIItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(Ver<=2){
		if(f->read((char *)&GetThresholdW()->Effective,sizeof(GetThresholdW()->Effective))!=sizeof(GetThresholdW()->Effective))
			return(false);
	    //if(Area.Read(file)==false)
		//	return(false);
		FlexArea	FArea;
	    if(FArea.Read(f)==false)
			return(false);
		SetArea(FArea);
		if(GetThresholdW()->SelAreaID.Load(f)==false)
			return(false);
		int32	PartsID;
		if(f->read((char *)&PartsID,sizeof(PartsID))!=sizeof(PartsID))
			return(false);
		return(true);
	}
	else{
		if(AlgorithmItemPI::Load(f,LBase)==false)
			return false;
	}

	return true;
}

bool		MaskingPIItem::IsEffective(void)	const
{
	return (((MaskingPIItem *)this)->GetThresholdR())->Effective;
}
void		MaskingPIItem::SetEffective(bool effective)
{
	GetThresholdW()->Effective=effective;
}

void	MaskingPIItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MaskingPIDrawAttr	*a=dynamic_cast<MaskingPIDrawAttr	*>(Attr);
	if(a!=NULL){
		MaskingPIDrawAttr	A=*((MaskingPIDrawAttr *)Attr);
		if(IsEffective()==false){
			if(A.IneffectiveMode==true){
				A.NormalColor	=A.NegColorMask;
				A.SelectedColor	=A.NegColorSelected;
				AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
			}
		}
		else{
			if(A.EffectiveMode==true){
				AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
	else{
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

//===========================================

void	MaskingPIInPage::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
	MatrixBuffClear(Dst ,0,XByte,YLen);
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(Dst,XLen,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(Dst,XLen,YLen);
	}
}
void	MaskingPIInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen)
{
	bool	FoundLimited=false;
	if(GetFirstData()!=NULL){
		MatrixBuffClear(Dst ,0,(XLen+7)>>3,YLen);
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL && a->IsEffective()==true){
				a->GetArea().MakeBitData(Dst,XLen,YLen);
				FoundLimited=true;
			}
		}
		if(FoundLimited==false){
			for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
					a->GetArea().MakeBitData(Dst,XLen,YLen);
			}
		}
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
				a->GetArea().MakeNotBitData(Dst,XLen,YLen);
		}
	}
	else{
		MatrixBuffClear(Dst ,0xFF,(XLen+7)>>3,YLen);
	}
}
void	MaskingPIInPage::SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen)
{
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		const MaskingPIThreshold	*RThr=((MaskingPIItem *)a)->GetThresholdR(GetLayersBase());
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&RThr->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&RThr->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeBitData(MaskBitmap,XByte<<3,YLen);
		}
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		const MaskingPIThreshold	*RThr=((MaskingPIItem *)a)->GetThresholdR(GetLayersBase());
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&RThr->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&RThr->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeNotBitData(MaskBitmap,XByte<<3,YLen);
		}
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((MaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(MaskBitmap,XByte<<3,YLen);
	}
}

/*
void	MaskingInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGenerateMaskInSameColor	*MSameColor=dynamic_cast<CmdGenerateMaskInSameColor *>(packet);
	if(MSameColor!=NULL){
		GenerateMaskInSameColor(MSameColor->PickupL,MSameColor->PickupH,MSameColor->Effective);
		return;
	}
	CmdCreateMaskingBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLibPacket->XByte ,BmpWithLibPacket->YLen);
		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
					 ,Dst,BmpWithLibPacket->XByte<<3 ,BmpWithLibPacket->YLen);
		BmpWithLibPacket->BmpMap=Dst;
		return;
	}
	CmdCoverLimitedMaskWithLibPacket	*LimitedWithLib=dynamic_cast<CmdCoverLimitedMaskWithLibPacket *>(packet);
	if(LimitedWithLib!=NULL){
		SetLimitedMask(LimitedWithLib->LibType,LimitedWithLib->LibID
			,LimitedWithLib->BmpMap,LimitedWithLib->XByte,LimitedWithLib->YLen);	
		return;
	}
}
*/

static	void MaskFoundOneCluster(BYTE **MapData,int xbyte,int ylen,int minX,int minY,int maxX,int maxY,void *anydata)
{
	PureFlexAreaListContainer	*TmpMasks=(PureFlexAreaListContainer	*)anydata;
	PureFlexAreaList	*a=new PureFlexAreaList();
	a->BuildFromRaster(MapData,xbyte,ylen
                                        ,0,0
                                        ,minX,minY,maxX,maxY
										,xbyte*8,ylen);
	//a->FArea.MakeOutlineDot(a->Area);
	TmpMasks->AppendList(a);
}

/*
void	MaskingPIInPage::GenerateMaskInSameColor(int PickupL ,int PickupH ,bool Effective)
{
	int	XByte=(GetDotPerLine()+7)/8;
	BYTE	**BMap=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(BMap ,0,XByte,GetMaxLines());
	for(int y=0;y<GetMaxLines();y++){
		BYTE	*s=GetMasterBuff().GetY(y);
		BYTE	*d=BMap[y];
		for(int x=0;x<GetDotPerLine();x++,s++){
			if(PickupL<=*s && *s<=PickupH){
				*(d+(x>>3)) |= 0x80>>(x&7);
			}
		}
	}
	PureFlexAreaListContainer	TmpMasks;
	BitmapClusterSized(BMap,XByte ,GetMaxLines()
					,max(GetDotPerLine(),GetMaxLines()),0,GetDotPerLine()*GetMaxLines(),0
					,GetDotPerLine(),GetMaxLines()
					,99999999
					,MaskFoundOneCluster
					,&TmpMasks);
	PureFlexAreaList	*a;
	while((a=TmpMasks.GetFirst())!=NULL){
		TmpMasks.RemoveList(a);
		AlgorithmItemPLI	*m=NewChild();
		m->SetArea(*a);
		((MaskingPIItem *)m)->GetThresholdW()->Effective=Effective;
		AppendItem(m);
		delete	a;
	}
}
*/


void	MaskingPIInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMaskingPIAreaPacket	*AddMArea=dynamic_cast<AddMaskingPIAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MaskingPIItem	*MData=(MaskingPIItem	*)CreateItem();
		MData->GetThresholdW()->Effective	=AddMArea->Effective;
		MData->SetArea(AddMArea->Area);
		MData->GetThresholdW()->SelAreaID	=AddMArea->LimitedLib;
		MData->SetManualCreated(true);
		AppendItem(MData);
	}
	CmdCreateMaskingPIBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingPIBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLibPacket->XByte ,BmpWithLibPacket->YLen);
		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
					 ,Dst,BmpWithLibPacket->XByte<<3 ,BmpWithLibPacket->YLen);
		BmpWithLibPacket->BmpMap=Dst;
		return;
	}
	CmdCoverLimitedMaskWithLibPacket	*LimitedWithLib=dynamic_cast<CmdCoverLimitedMaskWithLibPacket *>(packet);
	if(LimitedWithLib!=NULL){
		SetLimitedMask(LimitedWithLib->LibType,LimitedWithLib->LibID
			,LimitedWithLib->BmpMap,LimitedWithLib->XByte,LimitedWithLib->YLen);	
		return;
	}
	CmdRemoveMaskPIItem	*CmdRemoveMaskItemVar=dynamic_cast<CmdRemoveMaskPIItem *>(packet);
	if(CmdRemoveMaskItemVar!=NULL){
		AlgorithmItemRoot	*Item=SearchIDItem(CmdRemoveMaskItemVar->ItemID);
		if(Item!=NULL){
			UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoDeleteSelectedItems);
			int32	ItemCount=1;
			::Save(UndoPointer->GetWritePointer(),ItemCount);

			int32	ItemClassType=Item->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			Item->Save(UndoPointer->GetWritePointer());
			SetChanged();
			RemoveItem(Item);
			delete	Item;
			Changed=true;
			CalcDone =false;

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
		return;
	}
}
ConstMapBuffer	*MaskingPIInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
						 ,(BYTE **)Dst->GetBitMap(),GetDotPerLine() ,GetMaxLines());
		return Dst;
	}
	return NULL;
}
ConstMapBuffer	*MaskingPIInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		int	iXByte	=(GetDotPerLine()+7)/8 ;
		int	iYLen	=GetMaxLines();
		GetItemBitmap((BYTE **)Dst->GetBitMap() ,iXByte,iXByte*8,iYLen);
		return Dst;
	}
	return NULL;
}
bool	MaskingPIInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		return true;
	}
	return false;
}
bool	MaskingPIInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		return true;
	}
	return false;
}
//===========================================
MaskingPIBase::MaskingPIBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
}

AlgorithmDrawAttr	*MaskingPIBase::CreateDrawAttr(void)
{
	return new MaskingPIDrawAttr();
}

bool	MaskingPIBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,GetLayersBase()->GetMainWidget());
	//DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	MaskingPIItem	Item;
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->GetSelectedList();
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	return true;
}

