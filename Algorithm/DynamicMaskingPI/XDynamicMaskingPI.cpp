/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicMaskingPI\XDynamicMaskingPI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDynamicMaskingPI.h"
#include "XBitImageProcessor.h"
#include "omp.h"
#include "XDynamicMaskingPICommon.h"
#include "XDisplayBitImage.h"

DynamicMaskingPILibrary::DynamicMaskingPILibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	EnlargeDot	=0;
}
DynamicMaskingPILibrary::~DynamicMaskingPILibrary(void)
{
}

bool	DynamicMaskingPILibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	return true;
}
bool	DynamicMaskingPILibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;
	return true;
}

DynamicMaskingPILibrary	&DynamicMaskingPILibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((DynamicMaskingPILibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================

DynamicMaskingPILibraryContainer::DynamicMaskingPILibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
DynamicMaskingPILibraryContainer::~DynamicMaskingPILibraryContainer(void)
{
}

//==============================================================================
DynamicMaskingPIThreshold::DynamicMaskingPIThreshold(DynamicMaskingPIItem *parent)
:AlgorithmThreshold(parent)
{
	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;

	EnlargeDot	=0;
	EnsmallDot	=0;
	MinSize		=0;

	BlockWidth=BlockHeight=100;
	OpeType	=_PickupMask;
	DrawColR=0;
	DrawColG=0;
	DrawColB=0;

	AbsLR2=AbsHR2=0;
	AbsLG2=AbsHG2=0;
	AbsLB2=AbsHB2=0;

	EnlargeDot2	=0;
	EnsmallDot2	=0;

	DrawColR2=0;
	DrawColG2=0;
	DrawColB2=0;
	Mergin	=0;
	Layer	=0;
}

void	DynamicMaskingPIThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const DynamicMaskingPIThreshold *s=(const DynamicMaskingPIThreshold *)&src;

	AbsLR		=s->AbsLR;
	AbsHR		=s->AbsHR;
	AbsLG		=s->AbsLG;
	AbsHG		=s->AbsHG;
	AbsLB		=s->AbsLB;
	AbsHB		=s->AbsHB;
	EnlargeDot	=s->EnlargeDot;
	EnsmallDot	=s->EnsmallDot;
	BlockWidth	=s->BlockWidth;
	BlockHeight	=s->BlockHeight;
	OpeType		=s->OpeType;
	DrawColR	=s->DrawColR;
	DrawColG	=s->DrawColG;
	DrawColB	=s->DrawColB;
	MinSize		=s->MinSize;

	AbsLR2		=s->AbsLR2;
	AbsHR2		=s->AbsHR2;
	AbsLG2		=s->AbsLG2;
	AbsHG2		=s->AbsHG2;
	AbsLB2		=s->AbsLB2;
	AbsHB2		=s->AbsHB2;
	EnlargeDot2	=s->EnlargeDot2;
	EnsmallDot2	=s->EnsmallDot2;
	DrawColR2	=s->DrawColR2;
	DrawColG2	=s->DrawColG2;
	DrawColB2	=s->DrawColB2;

	Mergin		=s->Mergin;
	MaskingColor=s->MaskingColor;
	Layer		=s->Layer;
}

bool	DynamicMaskingPIThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const DynamicMaskingPIThreshold *s=(const DynamicMaskingPIThreshold *)&src;
	if(AbsLR		!=s->AbsLR			)	return false;
	if(AbsHR		!=s->AbsHR			)	return false;
	if(AbsLG		!=s->AbsLG			)	return false;
	if(AbsHG		!=s->AbsHG			)	return false;
	if(AbsLB		!=s->AbsLB			)	return false;
	if(AbsHB		!=s->AbsHB			)	return false;
	if(EnlargeDot	!=s->EnlargeDot		)	return false;
	if(EnsmallDot	!=s->EnsmallDot		)	return false;
	if(BlockWidth	!=s->BlockWidth		)	return false;
	if(BlockHeight	!=s->BlockHeight	)	return false;
	if(OpeType		!=s->OpeType		)	return false;
	if(DrawColR		!=s->DrawColR		)	return false;
	if(DrawColG		!=s->DrawColG		)	return false;
	if(DrawColB		!=s->DrawColB		)	return false;
	if(MinSize		!=s->MinSize		)	return false;

	if(AbsLR2		!=s->AbsLR2			)	return false;
	if(AbsHR2		!=s->AbsHR2			)	return false;
	if(AbsLG2		!=s->AbsLG2			)	return false;
	if(AbsHG2		!=s->AbsHG2			)	return false;
	if(AbsLB2		!=s->AbsLB2			)	return false;
	if(AbsHB2		!=s->AbsHB2			)	return false;
	if(EnlargeDot2	!=s->EnlargeDot2	)	return false;
	if(EnsmallDot2	!=s->EnsmallDot2	)	return false;
	if(DrawColR2	!=s->DrawColR2		)	return false;
	if(DrawColG2	!=s->DrawColG2		)	return false;
	if(DrawColB2	!=s->DrawColB2		)	return false;

	if(Mergin		!=s->Mergin			)	return false;
	if(MaskingColor	!=s->MaskingColor	)	return false;
	if(Layer		!=s->Layer			)	return false;
	return true;
}
bool	DynamicMaskingPIThreshold::Save(QIODevice *f)
{
	WORD	Ver=6;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;

	BYTE	D=(BYTE)OpeType;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,DrawColR)==false)
		return false;
	if(::Save(f,DrawColG)==false)
		return false;
	if(::Save(f,DrawColB)==false)
		return false;

	if(::Save(f,AbsLR2)==false)
		return false;
	if(::Save(f,AbsHR2)==false)
		return false;
	if(::Save(f,AbsLG2)==false)
		return false;
	if(::Save(f,AbsHG2)==false)
		return false;
	if(::Save(f,AbsLB2)==false)
		return false;
	if(::Save(f,AbsHB2)==false)
		return false;
	if(::Save(f,EnlargeDot2)==false)
		return false;
	if(::Save(f,EnsmallDot2)==false)
		return false;
	if(::Save(f,DrawColR2)==false)
		return false;
	if(::Save(f,DrawColG2)==false)
		return false;
	if(::Save(f,DrawColB2)==false)
		return false;
	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(AdaptedPickupLayers.Save(f)==false)
		return false;

	return(true);
}
bool	DynamicMaskingPIThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;	
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;	
	if(Ver>=2){
		BYTE	D;
		if(::Load(f,D)==false)
			return false;
		OpeType=(OperationType)D;

		if(::Load(f,DrawColR)==false)
			return false;
		if(::Load(f,DrawColG)==false)
			return false;
		if(::Load(f,DrawColB)==false)
			return false;
	}
	if(Ver>=2){
		if(::Load(f,AbsLR2)==false)
			return false;
		if(::Load(f,AbsHR2)==false)
			return false;
		if(::Load(f,AbsLG2)==false)
			return false;
		if(::Load(f,AbsHG2)==false)
			return false;
		if(::Load(f,AbsLB2)==false)
			return false;
		if(::Load(f,AbsHB2)==false)
			return false;
		if(::Load(f,EnlargeDot2)==false)
			return false;
		if(::Load(f,EnsmallDot2)==false)
			return false;
		if(::Load(f,DrawColR2)==false)
			return false;
		if(::Load(f,DrawColG2)==false)
			return false;
		if(::Load(f,DrawColB2)==false)
			return false;

		if(Ver>=6){
			if(::Load(f,Mergin)==false)
				return false;
		}
		else{
			Mergin=0;
		}
		if(MaskingColor.Load(f)==false)
			return false;
		if(::Load(f,Layer)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,MinSize)==false)
			return false;
	}
	if(Ver>=5){
		if(AdaptedPickupLayers.Load(f)==false)
			return false;
	}
	else{
		AdaptedPickupLayers.Add(Layer);
	}

	return(true);
}

void	DynamicMaskingPIThreshold::FromLibrary(AlgorithmLibrary *src)
{
}
void	DynamicMaskingPIThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
}

DynamicMaskingPIItem::DynamicMaskingPIItem(void)
{
	MaskingMap	=NULL;
	TmpBuff		=NULL;
	XByte	=0;
	YLen	=0;
	AVector=NULL;

	Cx=Cy	=0;
}
DynamicMaskingPIItem::~DynamicMaskingPIItem(void)
{
	if(MaskingMap!=NULL){
		DeleteMatrixBuff(MaskingMap,YLen);
		DeleteMatrixBuff(TmpBuff,YLen);
		MaskingMap	=NULL;
		TmpBuff		=NULL;
	}
}

AlgorithmItemPI	&DynamicMaskingPIItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);

	const DynamicMaskingPIItem	*s=dynamic_cast<const DynamicMaskingPIItem *>(&src);
	if(s!=NULL){
		MaskingArea=s->MaskingArea;
	}

	return *this;
}

bool    DynamicMaskingPIItem::Save(QIODevice *f)
{
	WORD	Ver=2;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(MaskingArea.Save(f)==false)
		return false;
	return true;
}
bool    DynamicMaskingPIItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(Ver>=2){
		if(MaskingArea.Load(f)==false)
			return false;
	}
	return true;
}

void	DynamicMaskingPIItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DynamicMaskingPIDrawAttr	*A=dynamic_cast<DynamicMaskingPIDrawAttr *>(Attr);
	if(A!=NULL){
		if(A->MaskMode==DynamicMaskingPIDrawAttr::_PickupMode){
			AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else{
			if(A->SelectedMask.Page==GetLayersBase()->GetGlobalPageFromLocal(GetPage())
			&& A->SelectedMask.ID==GetID()){
				AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
				QRgb	Col=qRgba(255,0,255,80);
				for(PureFlexAreaList *a=MaskingArea.GetFirst();a!=NULL;a=a->GetNext()){
					a->DrawAlpha(0,0,&pnt,Col ,ZoomRate,movx ,movy);
				}
			}
		}
	}
}

const	int	XMergin=256;
const	int	YMergin=256;

ExeResult	DynamicMaskingPIItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	if(MaskingMap!=NULL){
		DeleteMatrixBuff(MaskingMap,YLen);
		DeleteMatrixBuff(TmpBuff,YLen);
	}
	YLen		=GetArea().GetHeight()+YMergin*2;
	XByte		=(GetArea().GetWidth()+XMergin*2+7)/8;
	MaskingMap	=MakeMatrixBuff(XByte ,YLen);
	TmpBuff		=MakeMatrixBuff(XByte ,YLen);
	
	BYTE	**DynamicMaskingMapInPage=GetDataInPage()->GetDynamicMaskingMap();

	if(MaskingArea.IsEmpty()==true){
		MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
		MakePickupMask(0,0,MaskingMap , XByte ,YLen,true);
		GetGravityCenter(MaskingMap , XByte*8 ,YLen
							,Cx ,Cy);
		MatrixBuffBitOr	(DynamicMaskingMapInPage ,GetDataInPage()->GetDynamicMaskMapXByte()*8,GetDataInPage()->GetDynamicMaskMapYLen()
						,MaskingMap ,XByte*8 ,YLen
						,GetArea().GetMinX()-XMergin ,GetArea().GetMinY()-YMergin);
		//MatrixBuffOr	(P->MaskingMap ,(const BYTE **)MaskingMap ,XByte ,YLen);
	}
	else{
		MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
		MakePickupMask	(0,0,MaskingMap , XByte ,YLen,true);

		GetGravityCenter(MaskingMap , XByte*8 ,YLen
							,Cx ,Cy);
		Cx+=GetArea().GetMinX()-XMergin;
		Cy+=GetArea().GetMinY()-YMergin;

		for(PureFlexAreaList *a=MaskingArea.GetFirst();a!=NULL;a=a->GetNext()){
			a->MakeBitData(DynamicMaskingMapInPage , 0,0,GetDataInPage()->GetDynamicMaskMapXByte()*8 ,GetDataInPage()->GetDynamicMaskMapYLen());
		}
	}
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	return _ER_true;
}

ExeResult	DynamicMaskingPIItem::ExecutePreAlignment	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	DynamicMaskingPIBase	*PB=(DynamicMaskingPIBase *)GetParentBase();
	if(PB->ModePreAlignment==true){
		BYTE	**DynamicMaskingMapInPage=GetDataInPage()->GetDynamicMaskingMap();

		if(MaskingArea.IsEmpty()==true){
			MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
			MakePickupMask(0,0,MaskingMap , XByte ,YLen,false);
			MatrixBuffBitOr	(DynamicMaskingMapInPage ,GetDataInPage()->GetDynamicMaskMapXByte()*8,GetDataInPage()->GetDynamicMaskMapYLen()
							,MaskingMap ,XByte*8 ,YLen
							,GetArea().GetMinX()-XMergin ,GetArea().GetMinY()-YMergin);
			//MatrixBuffOr	(P->MaskingMap ,(const BYTE **)MaskingMap ,XByte ,YLen);
		}
		else{
			MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
			MakePickupMask	(0,0,MaskingMap , XByte ,YLen,false);

			double	Wx,Wy;
			GetGravityCenter(MaskingMap , XByte*8 ,YLen
								,Wx ,Wy);
			Wx+=GetArea().GetMinX()-XMergin;
			Wy+=GetArea().GetMinY()-YMergin;
			int	Mx=Wx-Cx;
			int	My=Wy-Cy;
			for(PureFlexAreaList *a=MaskingArea.GetFirst();a!=NULL;a=a->GetNext()){
				a->MakeBitData(DynamicMaskingMapInPage , Mx,My
							,GetDataInPage()->GetDynamicMaskMapXByte()*8 ,GetDataInPage()->GetDynamicMaskMapYLen());
			}
		}
	}
	return _ER_true;
}

void	DynamicMaskingPIItem::MakePickupMask(int mx,int my,BYTE	**LMaskingMap,int LXByte ,int LYLen ,bool Master)
{
	//_heapchk();

	const	DynamicMaskingPIThreshold	*RThr=GetThresholdR();
	if(GetLayerNumb()==1){
		ImageBuffer *ImageList[100];
		if(Master==true)
			GetMasterBuffList(ImageList);
		else
			GetTargetBuffList(ImageList);
		PickupBitmapWithTmp(GetArea(),mx-(GetArea().GetMinX()-XMergin),my-(GetArea().GetMinY()-YMergin)
					,LMaskingMap , LXByte ,LYLen
					,*ImageList[0]
					//,RThr->BlockWidth ,RThr->BlockHeight
					,RThr->AbsLR		,RThr->AbsHR
					,RThr->EnsmallDot	,RThr->EnlargeDot
					,TmpBuff);
		}
	else if(GetLayerNumb()>=3){
		ImageBuffer *ImageList[1000];
		if(Master==true)
			GetMasterBuffList(ImageList);
		else
			GetTargetBuffList(ImageList);
		int	Layer=RThr->Layer;

		if(RThr->AdaptedPickupLayers.GetCount()==1){
			if(RThr->AdaptedPickupLayers.GetFirst()!=NULL){
				Layer=RThr->AdaptedPickupLayers.GetFirst()->GetValue();
			}

			//_heapchk();
			PickupBitmapWithTmp(GetArea(),mx-(GetArea().GetMinX()-XMergin),my-(GetArea().GetMinY()-YMergin)
						,LMaskingMap , LXByte ,LYLen
						,*ImageList[Layer]
						//,RThr->BlockWidth			,RThr->BlockHeight
						,RThr->AbsLR		,RThr->AbsHR
						,RThr->EnsmallDot,RThr->EnlargeDot
						,TmpBuff);
			//_heapchk();
		}
		else{
			DynamicMaskingPIThreshold	*Thre=GetThresholdW();
			if(Thre->MaskingColor.IsEmpty()==true){
				int	LNumb=0;
				ImageBuffer *HImageList[100];
				int		AbsL[100],AbsH[100];
				for(IntClass *c=Thre->AdaptedPickupLayers.GetFirst();c!=NULL;c=c->GetNext()){
					HImageList[LNumb]=ImageList[c->GetValue()];
					if(c->GetValue()==0){
						AbsL[LNumb]=RThr->AbsLR;
						AbsH[LNumb]=RThr->AbsHR;
					}
					else if(c->GetValue()==1){
						AbsL[LNumb]=RThr->AbsLG;
						AbsH[LNumb]=RThr->AbsHG;
					}
					else if(c->GetValue()==2){
						AbsL[LNumb]=RThr->AbsLB;
						AbsH[LNumb]=RThr->AbsHB;
					}
					else{
						AbsL[LNumb]=0;
						AbsH[LNumb]=255;
					}
					LNumb++;
				}
				PickupBitmapWithTmpMulti(GetArea(),mx-(GetArea().GetMinX()-XMergin),my-(GetArea().GetMinY()-YMergin)
							,LMaskingMap , LXByte ,LYLen
							,HImageList,LNumb
							,AbsL,AbsH
							,RThr->EnsmallDot ,RThr->EnlargeDot
							,TmpBuff);
			}
			else{
				ImagePointerContainer Images;
				if(Master==true)
					GetMasterBuffList(Images);
				else
					GetTargetBuffList(Images);
				FlexArea	A;
				A=GetArea();
				A.MoveToClip(mx,my ,0,0,GetDotPerLine(),GetMaxLines());
				A.MakeBitmap(Thre->MaskingColor ,Thre->Mergin ,Images 
							,-(GetArea().GetMinX()-XMergin),-(GetArea().GetMinY()-YMergin)
							,LMaskingMap ,LXByte*8 ,LYLen);
				A.MoveToClip(-(GetArea().GetMinX()-XMergin),-(GetArea().GetMinY()-YMergin),0,0,LXByte*8 ,LYLen);
				for(int i=0;i<RThr->EnsmallDot;i++){
					A.ThinAreaPartial(LMaskingMap
								,TmpBuff
								, LXByte ,LYLen);
				}
				for(int i=0;i<(RThr->EnsmallDot+RThr->EnlargeDot);i++){
					A.FatAreaPartial(i, LMaskingMap
								,TmpBuff
								, LXByte ,LYLen);
				}
			}
		}
	}
	if(RThr->MinSize>0){
		//_heapchk();

		PureFlexAreaListContainer FPack;
		PickupFlexArea(LMaskingMap , LXByte ,GetDotPerLine(),LYLen,FPack);
		MatrixBuffClear	(LMaskingMap ,0, LXByte ,LYLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetPatternByte()>RThr->MinSize){
				a->MakeBitData(LMaskingMap , LXByte*8 ,LYLen);
			}
		}
	}
}

ExeResult	DynamicMaskingPIItem::ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	DynamicMaskingPIBase	*PB=(DynamicMaskingPIBase *)GetParentBase();
	const	DynamicMaskingPIThreshold	*RThr=GetThresholdR();
	if(RThr->OpeType==DynamicMaskingPIThreshold::_DrawMask){
		ImageBuffer *ImageList[100];
		GetTargetBuffList(ImageList);
		if(GetLayerNumb()==1){
			GetArea().PaintWithColor(*ImageList[0],(int)(RThr->DrawColR),0,0);
		}
		else if(GetLayerNumb()==2){
			GetArea().PaintWithColor(*ImageList[0],(int)(RThr->DrawColR),0,0);
			GetArea().PaintWithColor(*ImageList[1],(int)(RThr->DrawColG),0,0);
		}
		if(GetLayerNumb()>=3){
			GetArea().PaintWithColor(*ImageList[0],(int)(RThr->DrawColR),0,0);
			GetArea().PaintWithColor(*ImageList[1],(int)(RThr->DrawColG),0,0);
			GetArea().PaintWithColor(*ImageList[2],(int)(RThr->DrawColB),0,0);
		}
	}
	else if(PB->ModePreAlignment==false && RThr->OpeType==DynamicMaskingPIThreshold::_PickupMask){
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
		BYTE	**DynamicMaskingMapInPage=GetDataInPage()->GetDynamicMaskingMap();
		if(MaskingArea.IsEmpty()==true){
			MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
			MakePickupMask(mx,my,MaskingMap , XByte ,YLen,false);
			MatrixBuffBitOr	(DynamicMaskingMapInPage ,GetDataInPage()->GetDynamicMaskMapXByte()*8,GetDataInPage()->GetDynamicMaskMapYLen()
						,MaskingMap ,XByte*8 ,YLen
						,GetArea().GetMinX()-XMergin ,GetArea().GetMinY()-YMergin);
			//MatrixBuffOr	(P->MaskingMap ,(const BYTE **)MaskingMap ,XByte ,YLen);	
		}
		else{
			MatrixBuffClear	(MaskingMap ,0, XByte ,YLen);
			MakePickupMask	(mx,my,MaskingMap , XByte ,YLen,false);

			double	Wx,Wy;
			GetGravityCenter(MaskingMap , XByte*8 ,YLen
								,Wx ,Wy);
			Wx+=GetArea().GetMinX()-XMergin;
			Wy+=GetArea().GetMinY()-YMergin;
			int	Mx=Wx-Cx;
			int	My=Wy-Cy;
			for(PureFlexAreaList *a=MaskingArea.GetFirst();a!=NULL;a=a->GetNext()){
				a->MakeBitData(DynamicMaskingMapInPage , Mx,My
								,GetDataInPage()->GetDynamicMaskMapXByte()*8 ,GetDataInPage()->GetDynamicMaskMapYLen());
			}
		}
	}
	else if(RThr->OpeType==DynamicMaskingPIThreshold::_DynamicDrawMask){
		ImageBuffer *ImageList[100];
		GetTargetBuffList(ImageList);
		int	XLen=GetArea().GetWidth() +RThr->EnlargeDot2*2+4;
		int	YLen=GetArea().GetHeight()+RThr->EnlargeDot2*2+4;
		int	XByte	=(XLen+7)/8;
		BYTE	**TmpBuff	=MakeMatrixBuff(XByte,YLen);
		BYTE	**TmpBuff2	=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(TmpBuff ,0 ,XByte,YLen);

		int	TopY	=GetArea().GetMinY()-RThr->EnlargeDot2-2;
		int	LeftX	=GetArea().GetMinX()-RThr->EnlargeDot2-2;
		if(LeftX<0)
			LeftX=0;
		if(TopY<0)
			TopY=0;
		int	Layer=RThr->Layer;

	    for(int i=0;i<GetArea().GetFLineLen();i++){
		    int y  =GetArea().GetFLineAbsY (i);
			int tx1=GetArea().GetFLineLeftX(i);
	        int tx2=GetArea().GetFLineRightX(i);
            int L=tx2-tx1;
			if(y-TopY<0 || y-TopY>=GetMaxLines())
				continue;
			BYTE	*s=ImageList[Layer]->GetY(y)+(int)tx1;
			BYTE	*d=TmpBuff[y-TopY];

			int	LC=RThr->AbsLR;
			int	HC=RThr->AbsHR;
            for(int x=tx1;x<tx2;x++ ,s++){
				if(LC<=*s && *s<=HC){
					int	X=x-LeftX;
					if(X<0 || X>=GetDotPerLine())
						continue;
					d[X>>3] |= 0x80>>(X & 7);
				}
			}
        }
		GetLayersBase()->ThinAreaN(TmpBuff
					,TmpBuff2
					,XByte ,YLen
					,RThr->EnsmallDot2);
		GetLayersBase()->FatAreaN (TmpBuff
					,TmpBuff2
					,XByte ,YLen
					,RThr->EnlargeDot2);
		for(int y=0;y<YLen;y++){
			BYTE	*d=ImageList[Layer]->GetY(y+TopY)+LeftX;
			BYTE	*s=TmpBuff[y];
			for(int x=0;x<XLen;x++,d++){
				if((s[x>>3] & (0x80>>(x & 7)))!=0){
					*d=RThr->DrawColR2;
				}
			}
		}
		DeleteMatrixBuff(TmpBuff ,YLen);
		DeleteMatrixBuff(TmpBuff2,YLen);
	}
	return _ER_true;
}

void	DynamicMaskingPIItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
		MaskingArea.MoveNoClip(GlobalDx,GlobalDy);
	}
}
//===========================================
DynamicMaskingPIInPage::DynamicMaskingPIInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
}

DynamicMaskingPIInPage::~DynamicMaskingPIInPage(void)
{
}

void	DynamicMaskingPIInPage::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
}
void	DynamicMaskingPIInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen)
{
}


void	DynamicMaskingPIInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddDynamicMaskingPIAreaPacket	*AddMArea=dynamic_cast<AddDynamicMaskingPIAreaPacket *>(packet);
	if(AddMArea!=NULL){
		if(AddMArea->OpeType==DynamicMaskingPIThreshold::_PickupMask){
			DynamicMaskingPIItem	*MData=(DynamicMaskingPIItem *)CreateItem();
			MData->SetArea(AddMArea->MaskArea);

			MData->GetThresholdW()->AbsLR		=AddMArea->AbsLR;
			MData->GetThresholdW()->AbsHR		=AddMArea->AbsHR;
			MData->GetThresholdW()->AbsLG		=AddMArea->AbsLG;
			MData->GetThresholdW()->AbsHG		=AddMArea->AbsHG;
			MData->GetThresholdW()->AbsLB		=AddMArea->AbsLB;
			MData->GetThresholdW()->AbsHB		=AddMArea->AbsHB;
			MData->GetThresholdW()->EnlargeDot	=AddMArea->EnlargeDot;
			MData->GetThresholdW()->EnsmallDot	=AddMArea->EnsmallDot;
			MData->GetThresholdW()->BlockWidth	=AddMArea->BlockWidth;
			MData->GetThresholdW()->BlockHeight	=AddMArea->BlockHeight;
			MData->GetThresholdW()->OpeType		=AddMArea->OpeType;
			MData->GetThresholdW()->DrawColR	=AddMArea->DrawColR;
			MData->GetThresholdW()->DrawColG	=AddMArea->DrawColG;
			MData->GetThresholdW()->DrawColB	=AddMArea->DrawColB;
			MData->GetThresholdW()->MinSize		=AddMArea->MinSize;

			MData->GetThresholdW()->AbsLR2		=AddMArea->AbsLR2;
			MData->GetThresholdW()->AbsHR2		=AddMArea->AbsHR2;
			MData->GetThresholdW()->AbsLG2		=AddMArea->AbsLG2;
			MData->GetThresholdW()->AbsHG2		=AddMArea->AbsHG2;
			MData->GetThresholdW()->AbsLB2		=AddMArea->AbsLB2;
			MData->GetThresholdW()->AbsHB2		=AddMArea->AbsHB2;
			MData->GetThresholdW()->EnlargeDot2	=AddMArea->EnlargeDot2;
			MData->GetThresholdW()->EnsmallDot2	=AddMArea->EnsmallDot2;
			MData->GetThresholdW()->DrawColR2	=AddMArea->DrawColR2;
			MData->GetThresholdW()->DrawColG2	=AddMArea->DrawColG2;
			MData->GetThresholdW()->DrawColB2	=AddMArea->DrawColB2;
			MData->GetThresholdW()->Mergin		=AddMArea->Mergin;
			MData->GetThresholdW()->MaskingColor=AddMArea->MaskingColor;
			MData->GetThresholdW()->Layer		=AddMArea->Layer;
			MData->GetThresholdW()->AdaptedPickupLayers		=AddMArea->AdaptedPickupLayers;

			MData->SetManualCreated(true);
			AppendItem(MData);
			return;
		}
		else if(AddMArea->OpeType==DynamicMaskingPIThreshold::_MakeDynamicMask){
			AlgorithmItemRoot	*PItem=SearchIDItem(AddMArea->ParentItemID);
			if(PItem!=NULL){
				DynamicMaskingPIItem	*DPItem=dynamic_cast<DynamicMaskingPIItem *>(PItem);
				if(DPItem!=NULL){
					PureFlexAreaList	*a=new PureFlexAreaList(AddMArea->MaskArea);
					DPItem->MaskingArea.AppendList(a);
				}
			}
		}
	}
	ModDynamicMaskingPIAreaPacket	*ModMArea=dynamic_cast<ModDynamicMaskingPIAreaPacket *>(packet);
	if(ModMArea!=NULL){
		DynamicMaskingPIItem	*MData=(DynamicMaskingPIItem *)SearchIDItem(ModMArea->ID);
		if(MData!=NULL){
			MData->GetThresholdW()->AbsLR		=ModMArea->AbsLR;
			MData->GetThresholdW()->AbsHR		=ModMArea->AbsHR;
			MData->GetThresholdW()->AbsLG		=ModMArea->AbsLG;
			MData->GetThresholdW()->AbsHG		=ModMArea->AbsHG;
			MData->GetThresholdW()->AbsLB		=ModMArea->AbsLB;
			MData->GetThresholdW()->AbsHB		=ModMArea->AbsHB;
			MData->GetThresholdW()->EnlargeDot	=ModMArea->EnlargeDot;
			MData->GetThresholdW()->EnsmallDot	=ModMArea->EnsmallDot;
			MData->GetThresholdW()->BlockWidth	=ModMArea->BlockWidth;
			MData->GetThresholdW()->BlockHeight	=ModMArea->BlockHeight;
			MData->GetThresholdW()->OpeType		=ModMArea->OpeType;
			MData->GetThresholdW()->DrawColR	=ModMArea->DrawColR;
			MData->GetThresholdW()->DrawColG	=ModMArea->DrawColG;
			MData->GetThresholdW()->DrawColB	=ModMArea->DrawColB;
			MData->GetThresholdW()->MinSize		=ModMArea->MinSize;

			MData->GetThresholdW()->AbsLR2		=ModMArea->AbsLR2;
			MData->GetThresholdW()->AbsHR2		=ModMArea->AbsHR2;
			MData->GetThresholdW()->AbsLG2		=ModMArea->AbsLG2;
			MData->GetThresholdW()->AbsHG2		=ModMArea->AbsHG2;
			MData->GetThresholdW()->AbsLB2		=ModMArea->AbsLB2;
			MData->GetThresholdW()->AbsHB2		=ModMArea->AbsHB2;
			MData->GetThresholdW()->EnlargeDot2	=ModMArea->EnlargeDot2;
			MData->GetThresholdW()->EnsmallDot2	=ModMArea->EnsmallDot2;
			MData->GetThresholdW()->DrawColR2	=ModMArea->DrawColR2;
			MData->GetThresholdW()->DrawColG2	=ModMArea->DrawColG2;
			MData->GetThresholdW()->DrawColB2	=ModMArea->DrawColB2;
			MData->GetThresholdW()->Mergin		=ModMArea->Mergin;
			MData->GetThresholdW()->MaskingColor=ModMArea->MaskingColor;
			MData->GetThresholdW()->Layer		=ModMArea->Layer;
			MData->GetThresholdW()->AdaptedPickupLayers		=ModMArea->AdaptedPickupLayers;
			MData->SetManualCreated(true);
		}
		return;
	}
	CmdReqDMaskingPIAreaInfoList	*CmdReqDMaskingPIAreaInfoListVar=dynamic_cast<CmdReqDMaskingPIAreaInfoList *>(packet);
	if(CmdReqDMaskingPIAreaInfoListVar!=NULL){
		for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
			DynamicMaskingPIItem	*s=dynamic_cast<DynamicMaskingPIItem *>(c);
			if(s!=NULL){
				DynamicMaskingPIInfoList	*d=new DynamicMaskingPIInfoList();
				const	DynamicMaskingPIThreshold	*RThr=s->GetThresholdR(GetLayersBase());
				d->ID			=s->GetID();
				d->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(s->GetPage());
				d->AbsLR		=RThr->AbsLR;
				d->AbsHR		=RThr->AbsHR;
				d->AbsLG		=RThr->AbsLG;
				d->AbsHG		=RThr->AbsHG;
				d->AbsLB		=RThr->AbsLB;
				d->AbsHB		=RThr->AbsHB;
				d->EnlargeDot	=RThr->EnlargeDot;
				d->EnsmallDot	=RThr->EnsmallDot;
				d->BlockWidth	=RThr->BlockWidth;
				d->BlockHeight	=RThr->BlockHeight;
				d->MinSize		=RThr->MinSize;
				s->GetCenter(d->Cx,d->Cy);
				d->Page			=GetPage();
				d->OpeType		=RThr->OpeType;
				d->DrawColR		=RThr->DrawColR;
				d->DrawColG		=RThr->DrawColG;
				d->DrawColB		=RThr->DrawColB;

				d->AbsLR2		=RThr->AbsLR2;
				d->AbsHR2		=RThr->AbsHR2;
				d->AbsLG2		=RThr->AbsLG2;
				d->AbsHG2		=RThr->AbsHG2;
				d->AbsLB2		=RThr->AbsLB2;
				d->AbsHB2		=RThr->AbsHB2;
				d->EnlargeDot2	=RThr->EnlargeDot2;
				d->EnsmallDot2	=RThr->EnsmallDot2;
				d->DrawColR2	=RThr->DrawColR2;
				d->DrawColG2	=RThr->DrawColG2;
				d->DrawColB2	=RThr->DrawColB2;
				d->Mergin		=RThr->Mergin;
				d->MaskingColor	=RThr->MaskingColor;
				d->Layer		=RThr->Layer;
				d->AdaptedPickupLayers	=RThr->AdaptedPickupLayers;
				s->GetXY(d->x1,d->y1,d->x2,d->y2);

				CmdReqDMaskingPIAreaInfoListVar->List->AppendList(d);
			}
		}
		return;
	}
}

ExeResult	DynamicMaskingPIInPage::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}
ExeResult	DynamicMaskingPIInPage::ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePI::ExecutePreAlignment(ExeID ,Res);
}

bool	DynamicMaskingPIInPage::DrawResultItem(ResultInPageRoot *Res,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(GetItemCount()>0){
		DynamicMaskingPIBase	*LBase=dynamic_cast<DynamicMaskingPIBase *>(GetParentBase());
		DataInPage	*Dp=GetDataInPage();
		DrawBitImage(IData, (const BYTE **)Dp->GetDynamicMaskingMap(),Dp->GetDynamicMaskMapXByte()*8,Dp->GetDynamicMaskMapXByte(),Dp->GetDynamicMaskMapYLen()
			,(MovX<0)?MovX:0 ,(MovY<0)?MovY:0,ZoomRate
			,0,0
			,LBase->ColorMask);
	}
	return true;
}

//===========================================
DynamicMaskingPIBase::DynamicMaskingPIBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	OnlyMakeMask	=false;
	ModePreAlignment=true;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
	SetParam(&OnlyMakeMask		, /**/"Setting" ,/**/"OnlyMakeMask"		,"Check only to make DynamicMask");
	SetParam(&ModePreAlignment	, /**/"Setting" ,/**/"ModePreAlignment"	,"Processing in PreAlignment, otherwise PreProcessing ");
}

AlgorithmDrawAttr	*DynamicMaskingPIBase::CreateDrawAttr(void)
{
	return new DynamicMaskingPIDrawAttr();
}

bool	DynamicMaskingPIBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	DynamicMaskingPIItem	Item(NULL);
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	*/
	return true;
}





