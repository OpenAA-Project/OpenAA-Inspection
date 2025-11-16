#include "RasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Raster\XRaster.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include <QBuffer>
#include <QString>

#include "XRaster.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XRasterPacket.h"
#include "swap.h"
#include <omp.h>

#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGUIRasterPacket.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <float.h>
#include "XBitImageProcessor.h"

//======================================================================
RasterFileLayer::RasterFileLayer(RasterFileLayerContainer *parent)
{
	Parent=parent;

	FileLayerID		=-1;
	LibID			=-1;
	Visible			=true;
}

bool	RasterFileLayer::Save(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;

	return true;
}

bool	RasterFileLayer::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;

	return true;
}
RasterFileLayerContainer::RasterFileLayerContainer(RasterInPage *parent)
	:Parent(parent)
{
}

int		RasterFileLayerContainer::GetMaxFileLayerID(void)
{
	int	MaxID=0;
	for(RasterFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FileLayerID>MaxID){
			MaxID=a->FileLayerID;
		}
	}
	return MaxID;
}
RasterFileLayer	*RasterFileLayerContainer::Find(int ID)
{
	for(RasterFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->FileLayerID==ID)
			return a;
	}
	return NULL;
}

RasterFileLayer	*RasterFileLayerContainer::FindByLibID(int LibID)
{
	for(RasterFileLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID)
			return a;
	}
	return NULL;
}
RasterFileLayerContainer	&RasterFileLayerContainer::operator=(RasterFileLayerContainer &src)
{
	NPListPackSaveLoad<RasterFileLayer>::operator=(src);
	return *this;
}
//======================================================================
RasterThreshold::RasterThreshold(RasterItemAbstract *parent)
		:AlgorithmThreshold(parent)
{}

void	RasterThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	RasterThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	return true;
}
bool	RasterThreshold::Save(QIODevice *f)
{
	return true;
}
bool	RasterThreshold::Load(QIODevice *f)
{
	return true;
}
int		RasterThreshold::GetSize(void)	const 
{
	return 0;
}
//======================================================================

RasterInPage::RasterInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent),FileLayerList(this)
{
	ImagingBmp		=NULL;
	ImagingBmpXByte	=0;
	ImagingBmpYLen	=0;
	MasterNo		=-1;

	Mode	=DisplayImage::_Normal;
	LastPosX=LastPosY							=0;
	MoveStartPosX		=MoveStartPosY			=0;
	LastElementPosX		=LastElementPosY		=0;
	MoveStartElementPosX=MoveStartElementPosY	=0;
	RotateCenterXOnData	=RotateCenterYOnData	=0;
	RotateFirstX		=RotateFirstY			=0;
	RotateAngle									=0;
	ExtendCenterXOnData	=ExtendCenterYOnData	=0;
	ExtendFirstX		=ExtendFirstY			=0;
	SlopeXCenterXOnData	=SlopeXCenterYOnData	=0;
	SlopeXFirstX		=SlopeXFirstY			=0;
	SlopeXAngle									=0;
	SlopeYCenterXOnData	=SlopeYCenterYOnData	=0;
	SlopeYFirstX		=SlopeYFirstY			=0;
	SlopeYAngle									=0;
}
RasterInPage::~RasterInPage(void)
{
	if(ImagingBmp!=NULL)
		DeleteMatrixBuff(ImagingBmp,ImagingBmpYLen);
	ImagingBmp=NULL;
	ImagingBmpXByte=0;
	ImagingBmpYLen=0;
}

void	RasterInPage::CreateImagingBmpBuff(void)
{
	if(ImagingBmp!=NULL && (ImagingBmpYLen!=GetMaxLines()) && (ImagingBmpXByte!=(GetDotPerLine()+7)/8)){
		DeleteMatrixBuff(ImagingBmp,ImagingBmpYLen);
		ImagingBmp=NULL;
		ImagingBmpYLen=0;
	}
	if(ImagingBmp==NULL){
		ImagingBmpYLen=GetMaxLines();
		ImagingBmpXByte=(GetDotPerLine()+7)/8;
		ImagingBmp=MakeMatrixBuff(ImagingBmpXByte ,ImagingBmpYLen);
	}
	MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);

}

AlgorithmItemRoot		*RasterInPage::CreateItem(int ItemClassType)
{
	RasterItemAbstract	*a=NULL;
	switch(ItemClassType){
		case 1:
			a=new RasterPDFItem();
			break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}
void	RasterInPage::RemoveItem(AlgorithmItemRoot *a)	
{
	int	FileLayerID=-1;
	RasterItemAbstract	*Item=static_cast<RasterItemAbstract *>(a);
	if(Item!=NULL){
		FileLayerID=Item->GetFileLayerID();
	}
	AlgorithmInPagePI::RemoveItem(a);

	bool	FoundFileLayerID=false;
	for(AlgorithmItemPI	*b=GetFirstData();b!=NULL;b=b->GetNext()){
		RasterItemAbstract	*tItem=static_cast<RasterItemAbstract *>(b);
		if(FileLayerID==tItem->GetFileLayerID()){
			FoundFileLayerID=true;
			break;
		}
	}
	if(FoundFileLayerID==false){
		RasterFileLayer	*FL=FileLayerList.Find(FileLayerID);
		if(FL!=NULL){
			FileLayerList.RemoveList(FL);
			delete	FL;
		}
	}
}
void	RasterInPage::MakeXY(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			RasterItemAbstract	*Item=static_cast<RasterItemAbstract *>(a);
			if(Item!=NULL && Item->GetItemClassType()!=5){	//No composite
				Item->MakeXY();
			}
		}
	}
	for(AlgorithmItemPI	*b=GetFirstData();b!=NULL;b=b->GetNext()){
		RasterItemAbstract	*Item=static_cast<RasterItemAbstract *>(b);
		if(Item->GetItemClassType()==5){	//Only composite
			Item->MakeXY();
		}
	}
}

ExeResult	RasterInPage::ExecuteInitialAfterEdit	(int ExeID 
													,ResultInPageRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	return Ret;
}

void	RasterInPage::UndoDrawAllSelected	(QIODevice *f)
{
	int32	Count;
	if(::Load(f,Count)==false)
		return;

	FastSearchIDItemStart();


	for(int i=0;i<Count;i++){
		int32	ID;
		if(::Load(f,ID)==false)
			return;
		AlgorithmItemRoot	*a=FastSearchIDItem(ID);
		if(a!=NULL){
			RemoveItem(a);
			delete	a;
		}
	}
	FastSearchIDItemStart();
	SetCurrentSize();
}
	
void	RasterInPage::UndoRemoveLine		(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;
	int32	Count;
	if(::Load(f,Count)==false)
		return;
	for(int i=0;i<Count;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false)
			return;
		AlgorithmItemRoot		*b=CreateItem(ItemClassType);
		if(b->Save(f)==false){
			delete	b;
			return;
		}
		AppendItem(b);
	}
	RasterFileLayer	*DestFL=new RasterFileLayer(&FileLayerList);
	if(DestFL->Load(f)==false){
		delete	DestFL;
		return;
	}
	RasterFileLayer	*FL=FileLayerList[LineNo];
	if(FL!=NULL){
		FileLayerList.InsertForward(FL,DestFL);
	}
	else{
		FileLayerList.AppendList(DestFL);
	}
}

void	RasterInPage::UndoSwapNext		(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;

	RasterFileLayer	*FL1=FileLayerList.GetItem(LineNo);
	RasterFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);

	FileLayerList.RemoveList(FL1);
	FileLayerList.InsertLater(FL2,FL1);
}

void	RasterInPage::UndoDuplicateLine	(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;
	int32	Count;
	if(::Load(f,Count)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Count;i++){
		int32	ID;
		if(::Load(f,ID)==false)
			return;
		AlgorithmItemRoot	*a=FastSearchIDItem(ID);
		if(a!=NULL){
			RemoveItem(a);
			delete	a;
		}
	}
	RasterFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);
	FileLayerList.RemoveList(FL2);

	SetCurrentSize();
}
void	RasterInPage::UndoAddEmptyLayer	(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;

	RasterFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);
	FileLayerList.RemoveList(FL2);

	SetCurrentSize();
}

bool	RasterInPage::Save(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){

		if(FileLayerList.Save(f)==false)
			return false;

		if(TriangleAreaData.Save(f)==false)
			return false;

		BYTE	d=(BYTE)Mode;
		if(::Save(f,d)==false)
			return false;

		if(::Save(f,LastPosX)==false)
			return false;
		if(::Save(f,LastPosY)==false)
			return false;
		if(::Save(f,MoveStartPosX)==false)
			return false;
		if(::Save(f,MoveStartPosY)==false)
			return false;
		if(::Save(f,LastElementPosX)==false)
			return false;
		if(::Save(f,LastElementPosY)==false)
			return false;
		if(::Save(f,MoveStartElementPosX)==false)
			return false;
		if(::Save(f,MoveStartElementPosY)==false)
			return false;
		if(::Save(f,RotateCenterXOnData)==false)
			return false;
		if(::Save(f,RotateCenterYOnData)==false)
			return false;
		if(::Save(f,RotateFirstX)==false)
			return false;
		if(::Save(f,RotateFirstY)==false)
			return false;
		if(::Save(f,RotateAngle)==false)
			return false;
		if(::Save(f,ExtendCenterXOnData)==false)
			return false;
		if(::Save(f,ExtendCenterYOnData)==false)
			return false;
		if(::Save(f,ExtendFirstX)==false)
			return false;
		if(::Save(f,ExtendFirstY)==false)
			return false;
		if(::Save(f,SlopeXCenterXOnData)==false)
			return false;
		if(::Save(f,SlopeXCenterYOnData)==false)
			return false;
		if(::Save(f,SlopeXFirstX)==false)
			return false;
		if(::Save(f,SlopeXFirstY)==false)
			return false;
		if(::Save(f,SlopeXAngle)==false)
			return false;
		if(::Save(f,SlopeYCenterXOnData)==false)
			return false;
		if(::Save(f,SlopeYCenterYOnData)==false)
			return false;
		if(::Save(f,SlopeYFirstX)==false)
			return false;
		if(::Save(f,SlopeYFirstY)==false)
			return false;
		if(::Save(f,SlopeYAngle)==false)
			return false;

		for(int i=0;i<MaxRasterPointNumb;i++){
			if(ImagePoint[i].Save(f)==false)
				return false;
			if(CadPoint[i].Save(f)==false)
				return false;
		}

		if(AlgorithmInPagePI::Save(f)==false)
			return false;
	}
	return true;
}

bool	RasterInPage::Load(QIODevice *f)
{
	if(FileLayerList.Load(f)==false)
		return false;

	if(TriangleAreaData.Load(f)==false)
		return false;

	BYTE	d=(BYTE)Mode;
	if(::Load(f,d)==false)
		return false;

	if(::Load(f,LastPosX)==false)
		return false;
	if(::Load(f,LastPosY)==false)
		return false;
	if(::Load(f,MoveStartPosX)==false)
		return false;
	if(::Load(f,MoveStartPosY)==false)
		return false;
	if(GetLoadedVersion()>=3){
		if(::Load(f,LastElementPosX)==false)
			return false;
		if(::Load(f,LastElementPosY)==false)
			return false;
		if(::Load(f,MoveStartElementPosX)==false)
			return false;
		if(::Load(f,MoveStartElementPosY)==false)
			return false;
	}
	if(::Load(f,RotateCenterXOnData)==false)
		return false;
	if(::Load(f,RotateCenterYOnData)==false)
		return false;
	if(::Load(f,RotateFirstX)==false)
		return false;
	if(::Load(f,RotateFirstY)==false)
		return false;
	if(::Load(f,RotateAngle)==false)
		return false;
	if(::Load(f,ExtendCenterXOnData)==false)
		return false;
	if(::Load(f,ExtendCenterYOnData)==false)
		return false;
	if(::Load(f,ExtendFirstX)==false)
		return false;
	if(::Load(f,ExtendFirstY)==false)
		return false;
	if(::Load(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeXFirstX)==false)
		return false;
	if(::Load(f,SlopeXFirstY)==false)
		return false;
	if(::Load(f,SlopeXAngle)==false)
		return false;
	if(::Load(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeYFirstX)==false)
		return false;
	if(::Load(f,SlopeYFirstY)==false)
		return false;
	if(::Load(f,SlopeYAngle)==false)
		return false;

	for(int i=0;i<MaxRasterPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}

	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){

		FastSearchIDItemStart();
	}
	bool	Error=true;
	if(BuildPointer(Error)==false)
		return false;
	if(Error==false)
		return false;
	return true;
}

void	RasterInPage::UndoMove		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoRotate	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoZoom		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoShear		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoMirror	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoCenterize	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoCenterizeOnly	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((RasterItemAbstract *)Item)->LoadOnlyShape(f);
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}


void	RasterInPage::UndoMovePoints(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			Item->Load(f,GetLayersBase());
			((RasterItemAbstract *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	RasterInPage::UndoRasterDraw(QIODevice *f)
{
	FastSearchIDItemStart();
	for(;;){
		int32	id;
		if(::Load(f,id)==false)
			break;
		AlgorithmItemRoot	*Item=FastSearchIDItem(id);
		if(Item!=NULL){
			RemoveItem(Item);
			delete	Item;
		}
	}
	FastSearchIDItemStart();
	SetCurrentSize();
}

bool	RasterInPage::BuildPointer(bool &Error)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
		RasterItemAbstract	*item=static_cast<RasterItemAbstract *>(a);
		if(item->GetID()<0){
			AlgorithmItemPI	*NextItem=a->GetNext();
			RemoveItem(item);
			delete	item;
			a=NextItem;
		}
		else{
			if(item->BuildPointer(FileLayerList)==false){
				AlgorithmItemPI	*NextItem=a->GetNext();
				RemoveItem(item);
				delete	item;
				a=NextItem;
				Error=true;
			}
			else{
				a=a->GetNext();
			}
		}
	}
	return true;
}
void	RasterInPage::SetCurrentSize(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			item->SetCurrentSize();
		}
	}
}
void	RasterInPage::SetFileLayerVisible(IntListFast &ShownFileID)
{
	for(RasterFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		f->Visible=false;
	}

	for(IntClass *b=ShownFileID.GetFirst();b!=NULL;b=b->GetNext()){
		int	N=b->GetValue();
		if(FileLayerList[N]!=NULL){
			FileLayerList[N]->Visible=true;
		}
	}
}
int		RasterInPage::GetOwnOrder(int FileLayerID)
{
	int	N=0;
	for(RasterFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->FileLayerID==FileLayerID){
			return N;
		}
		N++;
	}
	return -1;
}

void	RasterInPage::BuildShapeToArea(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			item->BuildPointer(FileLayerList);
			item->BuildShapeToArea();
		}
	}
}

bool	RasterInPage::SaveTransformParam(QIODevice *f)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		//if(a->GetID()==CmdMoveElementVar->ItemID){
		RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
		if(Item!=NULL){
			return Item->SaveTransformParam(f);
		}
	}
	return true;
}

bool	RasterInPage::LoadTransformParam(QIODevice *f)
{
	int64	pos=f->pos();
	bool	Ret=true;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
		if(Item!=NULL){
			f->seek(pos);
			if(Item->LoadTransformParam(f)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	RasterInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);

	RasterDrawAttr	*GAttr=(RasterDrawAttr *)Attr;
	RasterBase	*Base=(RasterBase *)GetParentBase();
	QPainter	Pnt(&pnt);
	if(ImagingBmp!=NULL){
		DrawBitImage(pnt, (const BYTE **)ImagingBmp,ImagingBmpXByte*8,ImagingBmpXByte,ImagingBmpYLen
			,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,Base->ColorImaging);
	}

	int	CanvasWidth=pnt.width();
	int	CanvasHeight=pnt.height();

	int	hx1=(movx					)*ZoomRate;
	int	hy1=(movy					)*ZoomRate;
	int	hx2=(movx+GetDotPerLine()	)*ZoomRate;
	int	hy2=(movy+GetMaxLines()		)*ZoomRate;
	
	if(hx2<0 || CanvasWidth<=hx1
	|| hy2<0 || CanvasHeight<=hy1){
		return;
	}
	hx1=max(hx1,0);
	hy1=max(hy1,0);
	hx2=min(hx2,CanvasWidth);
	hy2=min(hy2,CanvasHeight);

	XYData	*xy=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(GetPage()));
	DataInPage	*Dp=GetDataInPage();

	if(GAttr!=NULL && GAttr->DrawMode.RotateMode==true){
		if(Mode==DisplayImage::_RotateMoveAngleStart || Mode==DisplayImage::_RotateMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(RotateCenterXOnData+movx)*ZoomRate;
			int	y=(RotateCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_RotateMoveAngling){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*c=dynamic_cast<RasterItemAbstract *>(a);
					if(c!=NULL){
						if(GAttr->ShownFileID.IsInclude(c->GetFileLayerID())==true){
							int	x1 ,y1 ,x2 ,y2;
							if(c->IsExistRotate(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
												,RotateAngle,RotateCenterXOnData	,RotateCenterYOnData)==true){
								if((x2-x1)*(y2-y1)>=20){
									if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,Attr->NormalColor.rgba())==false){
										c->DrawRotate(Pnt,pnt, movx ,movy ,ZoomRate ,Attr
														,RotateCenterXOnData	,RotateCenterYOnData
														,RotateAngle);
									}
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(RotateCenterXOnData+movx)*ZoomRate;
				int	cy=(RotateCenterYOnData+movy)*ZoomRate;
				int	x1=(RotateFirstX+movx)*ZoomRate;
				int	y1=(RotateFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(GAttr!=NULL && GAttr->DrawMode.ExtendMode==true){
		if(Mode==DisplayImage::_ExtendMoveStart || Mode==DisplayImage::_ExtendMoving){
			Pnt.setPen(Qt::red);
			int	x=(ExtendCenterXOnData+movx)*ZoomRate;
			int	y=(ExtendCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
	
			if(Mode==DisplayImage::_ExtendMoving){

				Pnt.setPen(Qt::yellow);
				int	rx1=abs(ExtendFirstX-ExtendCenterXOnData);
				int	ry1=abs(ExtendFirstY-ExtendCenterYOnData);
				int	rx2=abs(LastPosX-ExtendCenterXOnData);
				int	ry2=abs(LastPosY-ExtendCenterYOnData);
				int	x11=(ExtendCenterXOnData-rx1+movx)*ZoomRate;
				int	y11=(ExtendCenterYOnData-ry1+movy)*ZoomRate;
				int	x12=(ExtendCenterXOnData+rx1+movx)*ZoomRate;
				int	y12=(ExtendCenterYOnData+ry1+movy)*ZoomRate;
				int	x21=(ExtendCenterXOnData-rx2+movx)*ZoomRate;
				int	y21=(ExtendCenterYOnData-ry2+movy)*ZoomRate;
				int	x22=(ExtendCenterXOnData+rx2+movx)*ZoomRate;
				int	y22=(ExtendCenterYOnData+ry2+movy)*ZoomRate;
				double	Zx=1.0;
				double	Zy=1.0;
				if(rx1!=0)
					Zx=(double)rx2/(double)rx1;
				if(ry1!=0)
					Zy=(double)ry2/(double)ry1;
			
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*c=dynamic_cast<RasterItemAbstract *>(a);
					if(c!=NULL){
						if(GAttr->ShownFileID.IsInclude(c->GetFileLayerID())==true){
							int	x1 ,y1 ,x2 ,y2;
							if(c->IsExistZoom(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
												,Zx,Zy,ExtendCenterXOnData	,ExtendCenterYOnData)==true){
								if((x2-x1)*(y2-y1)>=20){
									if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,Attr->NormalColor.rgba())==false){
										c->DrawZoom(Pnt,pnt, movx ,movy ,ZoomRate ,Attr
													,ExtendCenterXOnData	,ExtendCenterYOnData,Zx,Zy);
									}
								}
							}
						}
					}
				}
				Pnt.drawLine(x11,y11,x12,y11);
				Pnt.drawLine(x12,y11,x12,y12);
				Pnt.drawLine(x12,y12,x11,y12);
				Pnt.drawLine(x11,y12,x11,y11);
				Pnt.setPen(Qt::red);
				Pnt.drawLine(x21,y21,x22,y21);
				Pnt.drawLine(x22,y21,x22,y22);
				Pnt.drawLine(x22,y22,x21,y22);
				Pnt.drawLine(x21,y22,x21,y21);
			}
		}
	}
	else if(GAttr!=NULL && GAttr->DrawMode.SlopeXMode==true){
		if(Mode==DisplayImage::_SlopeXMoveAngleStart || Mode==DisplayImage::_SlopeXMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(SlopeXCenterXOnData+movx)*ZoomRate;
			int	y=(SlopeXCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_SlopeXMoveAngling){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*c=dynamic_cast<RasterItemAbstract *>(a);
					if(c!=NULL){
						if(GAttr->ShownFileID.IsInclude(c->GetFileLayerID())==true){
							int	x1 ,y1 ,x2 ,y2;
							if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
												,true,SlopeXAngle,SlopeXCenterXOnData	,SlopeXCenterYOnData )==true){
								if((x2-x1)*(y2-y1)>=20){
									if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,Attr->NormalColor.rgba())==false){
										c->DrawShearX(Pnt,pnt, movx ,movy ,ZoomRate ,Attr
													 ,SlopeXCenterXOnData	,SlopeXCenterYOnData ,SlopeXAngle);
									}
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(SlopeXCenterXOnData+movx)*ZoomRate;
				int	cy=(SlopeXCenterYOnData+movy)*ZoomRate;
				int	x1=(SlopeXFirstX+movx)*ZoomRate;
				int	y1=(SlopeXFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(GAttr!=NULL && GAttr->DrawMode.SlopeYMode==true){
		if(Mode==DisplayImage::_SlopeYMoveAngleStart || Mode==DisplayImage::_SlopeYMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(SlopeYCenterXOnData+movx)*ZoomRate;
			int	y=(SlopeYCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_SlopeYMoveAngling){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*c=dynamic_cast<RasterItemAbstract *>(a);
					if(c!=NULL){
						if(GAttr->ShownFileID.IsInclude(c->GetFileLayerID())==true){
							int	x1 ,y1 ,x2 ,y2;
							if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
											,false ,SlopeYAngle,SlopeYCenterXOnData	,SlopeYCenterYOnData)==true){
								if((x2-x1)*(y2-y1)>=20){
									if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,Attr->NormalColor.rgba())==false){
										c->DrawShearY(Pnt,pnt, movx ,movy ,ZoomRate ,Attr
													 ,SlopeYCenterXOnData	,SlopeYCenterYOnData ,SlopeYAngle);
									}
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(SlopeYCenterXOnData+movx)*ZoomRate;
				int	cy=(SlopeYCenterYOnData+movy)*ZoomRate;
				int	x1=(SlopeYFirstX+movx)*ZoomRate;
				int	y1=(SlopeYFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(GAttr!=NULL && GAttr->DrawMode.AlignmentMode==true){
		QPen	BackPen(Qt::black);
		BackPen.setWidth(3);
		Pnt.setPen(BackPen);
		for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
			if(ImagePoint[i].x!=0 || ImagePoint[i].y!=0){
				int	x=(ImagePoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(ImagePoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
			}
		}
		for(int i=0;i<sizeof(CadPoint)/sizeof(CadPoint[0]);i++){
			if(CadPoint[i].x!=0 || CadPoint[i].y!=0){
				int	x=(CadPoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(CadPoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
			}
		}
		QPen	ImagePen(Qt::red);
		ImagePen.setWidth(1);
		Pnt.setPen(ImagePen);
		for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
			if(ImagePoint[i].x!=0 || ImagePoint[i].y!=0){
				int	x=(ImagePoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(ImagePoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y+10,QString(/**/"Image:")+QString::number(i+1));
			}
		}
		QPen	CadPen(Qt::yellow);
		CadPen.setWidth(1);
		Pnt.setPen(CadPen);
		for(int i=0;i<sizeof(CadPoint)/sizeof(CadPoint[0]);i++){
			if(CadPoint[i].x!=0 || CadPoint[i].y!=0){
				int	x=(CadPoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(CadPoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y-10,QString(/**/"CAD:")+QString::number(i+1));
			}
		}
	}
	else if(GAttr!=NULL && GAttr->DrawMode.DrawPickUpArea==true){
		QImage	TmpImage(pnt.width(),pnt.height(),QImage::Format_ARGB32);
		TmpImage.fill(0);
		LocalPickupArea.Draw(0,0,&TmpImage,qRgba(255,100,100,100)
									,ZoomRate ,movx ,movy);
		Pnt.drawImage(0,0,TmpImage);
	}
	else if(GAttr!=NULL && GAttr->DrawMode.MoveElementMode==true){
		QImage	TmpImage(pnt.width(),pnt.height(),QImage::Format_ARGB32);
		TmpImage.fill(0);
		for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
			RasterItemAbstract	*AItem=dynamic_cast<RasterItemAbstract *>(item);
			if(AItem!=NULL){
				AItem->Elements.DrawColor(TmpImage
											,movx-(MoveStartElementPosX-LastElementPosX)
											,movy-(MoveStartElementPosY-LastElementPosY)
											,ZoomRate
											,GAttr->DrawMode.CurrentElementID
											,qRgba(0,0,255,128));
			}
		}
		Pnt.drawImage(0,0,TmpImage);
	}
}

RasterFileLayer			*RasterInPage::FindFileLayer(int FileLayerID)
{
	for(RasterFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->FileLayerID==FileLayerID){
			return f;
		}
	}
	return NULL;
}

void	RasterInPage::PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(globalX,globalY)==true){
			Found.AppendList(new AlgorithmItemPointerList(a));
		}
	}
}
bool	RasterInPage::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste)
{
	bool	Ret=false;
	if(item->ItemClassType!=5){
		AlgorithmItemRoot	*a=CreateItem(item->ItemClassType);
		QBuffer	Buff(&item->ItemData);
		Buff.open(QIODevice::ReadOnly);
		a->Load(&Buff,GetLayersBase());
		RasterItemAbstract	*AItem=(RasterItemAbstract *)a;
		RasterFileLayer		*FL=FileLayerList.Find(AItem->GetLoadedFileLayerID());
		AItem->SetFileLayer(FL);

		if(SelectModeAfterPaste==true){
			a->SetSelected(true);
		}
		a->MoveTo(globalDx,globalDy);
		((RasterItemAbstract *)a)->BuildPointer(FileLayerList);
		AppendItem(a);
		UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
		if(GetParamGlobal()->MaxUndoCount>0){
			::Save(UPointer->GetWritePointer(),a->GetID());
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

		Changed=true;
		CalcDone =false;
		Ret=true;
	}
	return Ret;
}

void	RasterInPage::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoMove);
	if(GetParamGlobal()->MaxUndoCount>0){
		int32	Numb=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if((a->GetSelected()==true || AllItems==true) && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=static_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					Numb++;
				}
			}
		}
		::Save(UPointer->GetWritePointer(),Numb);
	}
	bool	FlagUndoBuff=true;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if((a->GetSelected()==true || AllItems==true) && a->GetEditLocked()==false  && a->GetVisible()==true){
			RasterItemAbstract	*item=static_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				if(GetParamGlobal()->MaxUndoCount>0){
					if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
						FlagUndoBuff=false;
					if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
						FlagUndoBuff=false;
				}
				item->MoveToFloat(GlobalDx,GlobalDy);
			}
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	SetCurrentSize();
}

void	RasterInPage::CopyFrom(AlgorithmBase *DestParent
									,AlgorithmInPageRoot *src 
									,int OffsetX,int OffsetY
									,int PartsMaster ,int PartsID
									,bool ReferedThresholdMode)
{
	RemoveAllDatas();
	return;
}
void	RasterInPage::RefreshFileLayerList(void)
{
	for(RasterFileLayer *L=FileLayerList.GetFirst();L!=NULL;){
		bool	Found=false;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=static_cast<RasterItemAbstract *>(a);
			if(item->GetFileLayerID()==L->GetFileLayerID()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			RasterFileLayer *NextL=L->GetNext();
			FileLayerList.RemoveList(L);
			delete	L;
			L=NextL;
		}
		else{
			L=L->GetNext();
		}
	}
}

static	int	RasterDbgX=4706;
static	int	RasterDbgY=3290;
static	int	RasterDbg=0;
static	int	DbgR=22;
static	int	DbgG=89;
static	int	DbgB=72;

bool	RasterInPage::ConvertImageW(QImage &RasterImages ,ImagePointerContainer &DstImages,RasterMaskContainer &RMaskList)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	DataInPage *Pg=GetDataInPage();
	ConstMapBufferListContainer MaskMap;
	if(Pg->GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		DoubleList	SrcAvr;
		DoubleList	SrcV;
		DoubleList	DstAvr;
		DoubleList	DstV;
		const BYTE	**MaskBitmap=Map.GetBitMap();
		BYTE	**RMaskBitmap=MakeMatrixBuff(Map.GetXByte(),Map.GetYLen());
		MatrixBuffCopy	(RMaskBitmap,Map.GetXByte(),Map.GetYLen()
						,MaskBitmap	,Map.GetXByte(),Map.GetYLen());

		for(RasterMask *m=RMaskList.GetFirst();m!=NULL;m=m->GetNext()){
			m->MaskArea.MakeBitData(RMaskBitmap ,Map.GetXLen() ,Map.GetYLen());
		}

		//FlexArea	MaskArea;
		//MaskArea.BuildFromRaster((uchar **)MaskBitmap ,Map.GetXByte() ,Map.GetYLen(),0,0);
		ColorCountListContainer	CCContainer;

		int	XLen=GetDotPerLine();
		int	YLen=GetMaxLines();
		int	Mergin=2;
		for(int y=Mergin;y<YLen-Mergin-1;y++){
			const BYTE	*m=MaskBitmap[y];
			QRgb	*s=(QRgb *)RasterImages.scanLine(y);
			for(int x=Mergin;x<XLen-Mergin-1;x++){
				if(GetBmpBitOnY(m,x)!=0){
					if(x==RasterDbgX && y==RasterDbgY){
						RasterDbg++;
					}
					ColorCountList	*c=CCContainer.FindIndexColor(s[x]);
					if(c==NULL){
						c=new ColorCountList(s[x]);
						CCContainer.Append(c);
					}
					for(int i=-Mergin;i<=Mergin;i++){
						for(int j=-Mergin;j<=Mergin;j++){
							QRgb	d=DstImages.GetColorRgb(x+i,y+j);
							c->IncreaseCount(d);
						}
					}
				}
			}
		}
		for(ColorCountList *c=CCContainer.GetFirst();c!=NULL;c=c->GetNext()){
			if(qRed  (c->IndexColor)==DbgR
			&& qGreen(c->IndexColor)==DbgG
			&& qBlue (c->IndexColor)==DbgB){
				RasterDbg++;
			}
			c->MakeDestColor();
		}
		for(int y=0;y<YLen;y++){
			const BYTE	*m=MaskBitmap[y];
			QRgb	*s=(QRgb *)RasterImages.scanLine(y);
			for(int x=0;x<XLen;x++){
				if(GetBmpBitOnY(m,x)!=0){
					QRgb	SCol=s[x];
					ColorCountList	*c=CCContainer.FindIndexColor(SCol);					
					if(c!=NULL){
						QRgb	d=DstImages.GetColorRgb(x,y);
						double	CLen=GetColorDistancce(c->DestColor,d);
						if(CLen>=ABase->ThresholdColorConvDistance){
							int	R=qRed  (SCol);
							int	G=qGreen(SCol);
							int	B=qBlue (SCol);
							for(int L=1;L<10;L++){
								for(int r=R-L;r<=R+L;r++){
									if(0<=r && r<256){
										for(int g=G-L;g<=G+L;g++){
											if(0<=g && g<256){
												for(int b=B-L;b<=B+L;b++){
													if(0<=b && b<256){
														QRgb	tSCol=qRgb(r,g,b);
														ColorCountList	*cc=CCContainer.FindIndexColor(tSCol);
														if(cc!=NULL){
															CLen=GetColorDistancce(cc->DestColor,d);
															if (CLen<ABase->ThresholdColorConvDistance) {
																SCol=tSCol;
																c=cc;
																goto	FoundClosed;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						FoundClosed:;
						int	R=qRed  (SCol);
						int	G=qGreen(SCol);
						int	B=qBlue (SCol);
						for(int L=1;L<2;L++){
							for(int r=R-L;r<=R+L;r++){
								if(0<=r && r<256){
									for(int g=G-L;g<=G+L;g++){
										if(0<=g && g<256){
											for(int b=B-L;b<=B+L;b++){
												if(0<=b && b<256){
													QRgb	tSCol=qRgb(r,g,b);
													ColorCountList	*cc=CCContainer.FindIndexColor(tSCol);
													if(cc!=NULL){
														double	tCLen=GetColorDistancce(cc->DestColor,d);
														if (tCLen<CLen) {
															CLen=tCLen;
															c=cc;
														}
													}
												}
											}
										}
									}
								}
							}
						}

						DstImages.SetColor(x,y,c->DestColor);
					}
				}
			}
		}
		DstImages.SetChanged(true);
		DeleteMatrixBuff(RMaskBitmap,Map.GetYLen());
	}
	return true;
}

bool	RasterInPage::CopyRasterToImageByProfile(QImage &RasterImages 
												,ImagePointerContainer &DstImages 
												,const ColorProfileContainerWithTable &ColorProfiles)
{
	RasterBase	*ABase=(RasterBase *)GetParentBase();
	DataInPage *Pg=GetDataInPage();
	ConstMapBufferListContainer MaskMap;
	if(Pg->GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		int	XLen=GetDotPerLine();
		int	YLen=GetMaxLines();
		const BYTE	**MaskBitmap=Map.GetBitMap();

		#pragma omp parallel
		{
			#pragma omp for	
			for(int y=0;y<YLen;y++){
				const BYTE	*m=MaskBitmap[y];
				QRgb	*s=(QRgb *)RasterImages.scanLine(y);
				BYTE	*dR=DstImages[0]->GetY(y);
				BYTE	*dG=DstImages[1]->GetY(y);
				BYTE	*dB=DstImages[2]->GetY(y);
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(m,x)!=0){
						const	QRgb	col=ColorProfiles.GetColor(*s);
						*dR=qRed(col);
						*dG=qGreen(col);
						*dB=qBlue(col);
					}
					dR++;
					dG++;
					dB++;
					s++;
				}
			}
		}
	}
	return true;
}
void	RasterInPage::MakeProfileByImage(bool Mastered)
{
	ColorSamplingAverager	*AveragerDim=new ColorSamplingAverager[256*256*256];
	memset(AveragerDim,0,sizeof(ColorSamplingAverager)*256*256*256);

	DataInPage *Pg=GetDataInPage();
	ConstMapBufferListContainer MaskMap;
	RasterBase	*ABase=(RasterBase	*)GetParentBase();

	if(Pg->GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		const BYTE	**MaskBitmap=Map.GetBitMap();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				Item->MakeProfileByImage(MaskBitmap,Mastered,AveragerDim);
			}
		}
	}
	for(int r=0;r<256;r++){
		for(int g=0;g<256;g++){
			for(int b=0;b<256;b++){
				ColorSamplingAverager	*a=&AveragerDim[(r<<16)+(g<<8)+b];
				if(a->Numb>20){
					int	gR=a->AddedImageR/a->Numb;
					int	gG=a->AddedImageG/a->Numb;
					int	gB=a->AddedImageB/a->Numb;
					QColor	RasterColor(r,g,b);
					QColor	ImageColor(gR,gG,gB);
					ColorProfile	*L2=ABase->ColorProfiles.GetClosedDstColor(RasterColor);
					if(L2==NULL){
						ColorProfile	*C=new ColorProfile(ImageColor,RasterColor);
						ABase->ColorProfiles.AppendList(C);
						continue;;
					}
					if(GetColorDistancce(L2->DstColor,RasterColor)<3){
						continue;;
					}
					ColorProfile	*C=new ColorProfile(ImageColor,RasterColor);
					ABase->ColorProfiles.AppendList(C);
				}
			}
		}
	}
	delete	[]AveragerDim;
}

//==========================================================================================

RasterBase::RasterBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNormal			=Qt::yellow;
	ColorSelected		=Qt::white;
	ColorActive			=Qt::red;
	ColorImaging		=Qt::magenta;
	TransparentLevel	=120;

	CenterizeByArea				=true;
	SwingDotInLastMatch			=3;
	MaxBindedAreaLength			=1000;
	OverlapPixelToCutBigArea	=50;

	LoadedCenterization			=true;
	LoadedOffsetX				=0;
	LoadedOffsetY				=0;
	IsolationToSelect			=5.0;
	UseMasterImage				=false;
	PDFDefaultSize				=/**/"A4-L";
	MasterNoForImaging			=0;
	ThresholdColorConvDistance	=60;
	DefaultTransformFileName	=/**/"DefaultRasterTransform.dat";
	DefaultColorProfileFileName	=/**/"RasterDefaultColorProfile.dat";

	ModeDeliverAllPhasesInLoadRaster	=true;
	SetModeLoadSaveInPlayer(true);

	SetParam(&ColorNormal					, /**/"Color"	,/**/"ColorNormal"						,LangSolver.GetString(XRaster_LS,LID_0)/*"Color for normal Raster item"*/);
	SetParam(&ColorSelected					, /**/"Color"	,/**/"ColorSelected"					,LangSolver.GetString(XRaster_LS,LID_1)/*"Color for Selected Raster item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"						,LangSolver.GetString(XRaster_LS,LID_2)/*"Color for Active Raster Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"						,LangSolver.GetString(XRaster_LS,LID_3)/*"Color for Active Raster Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorImaging"						,LangSolver.GetString(XRaster_LS,LID_4)/*"Color for Imaging area"*/);
	SetParam(&TransparentLevel				, /**/"Color"	,/**/"TransparentLevel"					,LangSolver.GetString(XRaster_LS,LID_5)/*"Transparent level 0-255"*/);

	SetParam(&CenterizeByArea				, /**/"Setting"	,/**/"CenterizeByArea"					,LangSolver.GetString(XRaster_LS,LID_6)/*"Pick up CAD-center by area"*/);
	SetParam(&SwingDotInLastMatch			, /**/"Setting"	,/**/"SwingDotInLastMatch"				,LangSolver.GetString(XRaster_LS,LID_7)/*"Search-dot near location in last matching sequence."*/);
	SetParam(&IsolationToSelect				, /**/"Setting"	,/**/"IsolationToSelect"				,LangSolver.GetString(XRaster_LS,LID_8)/*"Isolation to select"*/);
	SetParam(&MasterNoForImaging			, /**/"Setting"	,/**/"MasterNoForImaging"				,LangSolver.GetString(XRaster_LS,LID_9)/*"MasterNo for Imaging"*/);
	SetParam(&MaxBindedAreaLength			, /**/"AutoMatch"	,/**/"MaxBindedAreaLength"			,LangSolver.GetString(XRaster_LS,LID_10)/*"Max length of Binded Area"*/);
	SetParam(&OverlapPixelToCutBigArea		, /**/"AutoMatch"	,/**/"OverlapPixelToCutBigArea"		,LangSolver.GetString(XRaster_LS,LID_11)/*"Overlapped Pixel length to cut too big Raster pattern"*/);
	SetParam(&UseMasterImage				, /**/"AutoMatch"	,/**/"UseMasterImage"				,LangSolver.GetString(XRaster_LS,LID_12)/*"Use master image in matching"*/);

	SetParam(&LoadedCenterization			, /**/"Initial"	,/**/"LoadedCenterization"			,LangSolver.GetString(XRaster_LS,LID_13)/*"Centerization after loading"*/);
	SetParam(&LoadedOffsetX					, /**/"Initial"	,/**/"LoadedOffsetX"				,LangSolver.GetString(XRaster_LS,LID_14)/*"Offset X after loading"*/);
	SetParam(&LoadedOffsetY					, /**/"Initial"	,/**/"LoadedOffsetY"				,LangSolver.GetString(XRaster_LS,LID_15)/*"Offset Y after loading"*/);
	SetParam(&DefaultColorProfileFileName	, /**/"Initial"	,/**/"DefaultColorProfileFileName"		,"Default color profile file name");

	SetParam(&ModeDeliverAllPhasesInLoadRaster	, /**/"Setting"	,/**/"ModeDeliverAllPhasesInLoadRaster"	,LangSolver.GetString(XRaster_LS,LID_16)/*"Mode to deliver RasterData for all phases when it\'s loaded"*/);
	SetParam(&ThresholdColorConvDistance	, /**/"Setting"	,/**/"ThresholdColorConvDistance"		,"Threshold color-converter distance");
}

void	RasterBase::InitialAfterParamLoaded(void)
{
	AlgorithmBase::InitialAfterParamLoaded();

	QDir::setCurrent(GetLayersBase()->GetUserPath());
	QFile	File(DefaultColorProfileFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(ColorProfiles.Load(&File)==true){
			ColorProfiles.MakeTable();
		}
	}
}

AlgorithmDrawAttr	*RasterBase::CreateDrawAttr(void)
{
	return new RasterDrawAttr();
}

void	RasterBase::SetPdfXYmm(double &PgSizeX,double &PgSizeY)
{
	if(PDFDefaultSize==/**/"A0-L"){
		PgSizeX=841;
		PgSizeY=1189;
	}
	else
	if(PDFDefaultSize==/**/"A1-L"){
		PgSizeX=594;
		PgSizeY=841;
	}
	else
	if(PDFDefaultSize==/**/"A2-L"){
		PgSizeX=420;
		PgSizeY=594;
	}
	else
	if(PDFDefaultSize==/**/"A3-L"){
		PgSizeX=297;
		PgSizeY=420;
	}
	else
	if(PDFDefaultSize==/**/"A4-L"){
		PgSizeX=210;
		PgSizeY=297;
	}
	else
	if(PDFDefaultSize==/**/"A5-L"){
		PgSizeX=148;
		PgSizeY=210;
	}
	else
	if(PDFDefaultSize==/**/"A6-L"){
		PgSizeX=105;
		PgSizeY=148;
	}
	else
	if(PDFDefaultSize==/**/"A7-L"){
		PgSizeX=74;
		PgSizeY=105;
	}
	else
	if(PDFDefaultSize==/**/"A8-L"){
		PgSizeX=52;
		PgSizeY=74;
	}
	else
	if(PDFDefaultSize==/**/"A9-L"){
		PgSizeX=37;
		PgSizeY=52;
	}
	else
	if(PDFDefaultSize==/**/"A10-L"){
		PgSizeX=26;
		PgSizeY=37;
	}

	else
	if(PDFDefaultSize==/**/"B0-L"){
		PgSizeX=1030;
		PgSizeY=1456;
	}
	else
	if(PDFDefaultSize==/**/"B1-L"){
		PgSizeX=728;
		PgSizeY=1030;
	}
	else
	if(PDFDefaultSize==/**/"B2-L"){
		PgSizeX=515;
		PgSizeY=728;
	}
	else
	if(PDFDefaultSize==/**/"B3-L"){
		PgSizeX=364;
		PgSizeY=515;
	}
	else
	if(PDFDefaultSize==/**/"B4-L"){
		PgSizeX=257;
		PgSizeY=364;
	}
	else
	if(PDFDefaultSize==/**/"B5-L"){
		PgSizeX=182;
		PgSizeY=257;
	}
	else
	if(PDFDefaultSize==/**/"B6-L"){
		PgSizeX=128;
		PgSizeY=182;
	}
	else
	if(PDFDefaultSize==/**/"B7-L"){
		PgSizeX=91;
		PgSizeY=128;
	}
	else
	if(PDFDefaultSize==/**/"B8-L"){
		PgSizeX=64;
		PgSizeY=91;
	}
	else
	if(PDFDefaultSize==/**/"B9-L"){
		PgSizeX=45;
		PgSizeY=64;
	}
	else
	if(PDFDefaultSize==/**/"B10-L"){
		PgSizeX=32;
		PgSizeY=45;
	}
}

bool	RasterBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false){
		return false;
	}
	if(ColorProfiles.ColorProfileContainer::Save(f)==false)
		return false;
	return true;
}

bool	RasterBase::LoadOnlyBase(QIODevice *f,QString &ErrorMsg)
{
	if(AlgorithmBase::LoadOnlyBase(f,ErrorMsg)==false){
		return false;
	}
	if(GetLoadedVersion()>=4){
		if(ColorProfiles.ColorProfileContainer::Load(f)==false){
			return false;
		}
		ColorProfiles.MakeTable();
	}
	return true;
}

void	RasterBase::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdRasterSendShowingLayerInfo	*GInfo=dynamic_cast<GUICmdRasterSendShowingLayerInfo *>(packet);
	if(GInfo!=NULL){
		if(GetLibraryContainer()!=NULL){
			IntList PhaseList;
			if(GetParamGlobal()->CommonOperationInAllPhases==false){
				PhaseList.Add(GetLayersBase()->GetCurrentPhase());
			}
			else{
				for(int phase=0;phase<GetPhaseNumb();phase++){
					PhaseList.Add(phase);
				}
			}
		}
		return;			
	}
	CmdGetRasterLibraryListPacket	*AListPacket=dynamic_cast<CmdGetRasterLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetRasterLibraryNamesPacket	*ANamesPacket=dynamic_cast<CmdGetRasterLibraryNamesPacket *>(packet);
	if(ANamesPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamesPacket->AList);
		}
		return;
	}
	CmdGetRasterLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetRasterLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			ANamePacket->LibName=GetLibraryContainer()->GetLibraryName(ANamePacket->LibID);
		}
		return;
	}
	CmdGetRasterTemporaryLibraryPacket	*CmdGetRasterTemporaryLibraryPacketVar=dynamic_cast<CmdGetRasterTemporaryLibraryPacket *>(packet);
	if(CmdGetRasterTemporaryLibraryPacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			CmdGetRasterTemporaryLibraryPacketVar->TempLib=(RasterLibrary *)GetLibraryContainer()->CreateNew();
		}
		return;
	}
	CmdInsertRasterLibraryPacket	*BInsLib=dynamic_cast<CmdInsertRasterLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(RasterVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateRasterLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateRasterLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(RasterVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadRasterLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadRasterLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempRasterLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempRasterLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearRasterLibraryPacket	*CmdClearRasterLibraryPacketVar=dynamic_cast<CmdClearRasterLibraryPacket *>(packet);
	if(CmdClearRasterLibraryPacketVar!=NULL){
		CmdClearRasterLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteRasterLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteRasterLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	MsgSaveConstruct	*MsgSaveConstructVar=dynamic_cast<MsgSaveConstruct *>(packet);
	if(MsgSaveConstructVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		int32	PhaseNumb=GetPhaseNumb();
		if(::Save(&Buff,PhaseNumb)==false)
			return;

		for(int phase=0;phase<PhaseNumb;phase++){
			AlgorithmInPageInOnePhase	*APhase=GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				MsgSaveConstruct	RCmd(GetLayersBase());
				APhase->GetPageData(page)->TransmitDirectly(&RCmd);
				if(::Save(&Buff,RCmd.Data)==false)
					return;
			}
		}
		MsgSaveConstructVar->Data=Buff.buffer();
		return;
	}
	MsgLoadConstruct	*MsgLoadConstructVar=dynamic_cast<MsgLoadConstruct *>(packet);
	if(MsgLoadConstructVar!=NULL){
		if(GetLoadedVersion()>=10){
			QBuffer	Buff(&MsgLoadConstructVar->Data);
			Buff.open(QIODevice::ReadOnly);
			int32	PhaseNumb;
			if(::Load(&Buff,PhaseNumb)==false)
				return;
			for(int phase=0;phase<PhaseNumb && phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*APhase=GetPageDataPhase(phase);
				for(int page=0;page<GetPageNumb();page++){
					MsgLoadConstruct	RCmd(GetLayersBase());
					if(::Load(&Buff,RCmd.Data)==false)
						return;
					APhase->GetPageData(page)->TransmitDirectly(&RCmd);
				}
			}
		}
		else{
			QBuffer	Buff(&MsgLoadConstructVar->Data);
			Buff.open(QIODevice::ReadOnly);
			for(int page=0;page<GetPageNumb();page++){
				MsgLoadConstruct	RCmd(GetLayersBase());
				if(::Load(&Buff,RCmd.Data)==false)
					return;
				GetPageData(page)->TransmitDirectly(&RCmd);
			}
		}
		return;
	}
	CmdSaveDefaultColorProfile	*CmdSaveDefaultColorProfileVar=dynamic_cast<CmdSaveDefaultColorProfile *>(packet);
	if(CmdSaveDefaultColorProfileVar!=NULL){
		ColorProfiles=CmdSaveDefaultColorProfileVar->ColorProfiler;

		QDir::setCurrent(GetLayersBase()->GetUserPath());
		QFile	File(DefaultColorProfileFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			ColorProfiles.Save(&File);
		}
		return;
	}
}
QString	RasterBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XRaster_LS,LID_17)/*"PDF蜃ｦ逅*/;
}
