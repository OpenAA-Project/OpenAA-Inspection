/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoMaskingPI\XAutoMaskingPI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAutoMaskingPIResource.h"
#include "XAutoMaskingPI.h"
#include "AutoMaskingPI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XMaskingFromGeneral.h"
#include "XBitImageProcessor.h"
#include "XDisplayBitImage.h"
#include "omp.h"
#include <QColor>
#include "XAutoMaskingPIPacket.h"
#include "XAnyData.h"
#include "XMaskingFromGeneral.h"

AutoMaskingPILibrary::AutoMaskingPILibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	ColDiffRate	=20;
	EnLargeDot	=5;
	EnSmallDot	=8;
	MinSlitDot	=200;
	MinSlitSize	=200;
	DefaultMask	=false;
	MinSlitWidth	=30;
	MaxLakeSize		=100;
	MinClusterSize	=500;
	MinClusterArea	=10000;
	NoiseSize		=2;
	PickupDarker	=false;
	StageShadeColor	=10;
	chkEnLargeDot	=false;
}

bool	AutoMaskingPILibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=5;

	if(::Save(f,Ver)==false){
		return(false);
	}
	if(::Save(f,ColDiffRate)==false){
		return false;
	}
	if(::Save(f,EnLargeDot)==false){
		return false;
	}
	if(::Save(f,EnSmallDot)==false){
		return false;
	}
	if(::Save(f,MinSlitDot)==false){
		return false;
	}
	if(::Save(f,MinSlitSize)==false){
		return false;
	}
	if(::Save(f,DefaultMask)==false){
		return false;
	}
	if(::Save(f,MinSlitWidth)==false){
		return false;
	}
	if(::Save(f,MaxLakeSize)==false){
		return false;
	}
	if(::Save(f,MinClusterSize)==false){
		return false;
	}
	if(::Save(f,MinClusterArea)==false){
		return false;
	}
	if(::Save(f,PickupDarker)==false){
		return false;
	}
	if(::Save(f,NoiseSize)==false){
		return false;
	}
	if(::Save(f,StageShadeColor)==false){
		return false;
	}
	if(::Save(f,chkEnLargeDot)==false){
		return false;
	}
	return true;
}

bool	AutoMaskingPILibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false){
		return(false);
	}
	if(::Load(f,ColDiffRate)==false){
		return false;
	}
	if(::Load(f,EnLargeDot)==false){
		return false;
	}
	if(::Load(f,EnSmallDot)==false){
		return false;
	}
	if(::Load(f,MinSlitDot)==false){
		return false;
	}
	if(::Load(f,MinSlitSize)==false){
		return false;
	}
	if(::Load(f,DefaultMask)==false){
		return false;
	}
	if(Ver>=3){
		if(::Load(f,MinSlitWidth)==false){
			return false;
		}
		if(::Load(f,MaxLakeSize)==false){
			return false;
		}
		if(::Load(f,MinClusterSize)==false){
			return false;
		}
	}
	if(Ver>=4){
		if(::Load(f,MinClusterArea)==false){
			return false;
		}
		if(::Load(f,PickupDarker)==false){
			return false;
		}
		if(::Load(f,NoiseSize)==false){
			return false;
		}
		if(::Load(f,StageShadeColor)==false){
			return false;
		}
	}
	if(Ver>=5){
		if(::Load(f,chkEnLargeDot)==false){
			return false;
		}
	}
	return true;
}


AutoMaskingPILibrary	&AutoMaskingPILibrary::operator=(const AlgorithmLibrary &src)
{
	ColDiffRate		=((AutoMaskingPILibrary *)&src)->ColDiffRate;
	EnLargeDot		=((AutoMaskingPILibrary *)&src)->EnLargeDot;
	EnSmallDot		=((AutoMaskingPILibrary *)&src)->EnSmallDot;
	MinSlitDot		=((AutoMaskingPILibrary *)&src)->MinSlitDot;
	MinSlitSize		=((AutoMaskingPILibrary *)&src)->MinSlitSize;
	DefaultMask		=((AutoMaskingPILibrary *)&src)->DefaultMask;
	MinSlitWidth	=((AutoMaskingPILibrary *)&src)->MinSlitWidth;
	MaxLakeSize		=((AutoMaskingPILibrary *)&src)->MaxLakeSize;
	MinClusterSize	=((AutoMaskingPILibrary *)&src)->MinClusterSize;
	MinClusterArea	=((AutoMaskingPILibrary *)&src)->MinClusterArea;
	PickupDarker	=((AutoMaskingPILibrary *)&src)->PickupDarker;
	NoiseSize		=((AutoMaskingPILibrary *)&src)->NoiseSize;
	StageShadeColor	=((AutoMaskingPILibrary *)&src)->StageShadeColor;
	chkEnLargeDot	=((AutoMaskingPILibrary *)&src)->chkEnLargeDot;
	return *this;
}

int	PnDbgX;
int	PnDbgY;
int	PnDbg;


void	AutoMaskingPILibrary::MakeMask(ImageBuffer *MasterBuff[]
									  ,ImageBuffer *TargetBuff[]
									  ,int LayerCount
									  ,BYTE **MaskBitmap
									  ,int XByte ,int	XLen ,int YLen)
{
/*
	if(GetLayersBase()->GetInsideLearningEditor()==true){
		if(MasterBuff[0]==NULL){
			return;
		}
		if(MasterBuff[0]->IsNull()==true){
			return;
		}
		if(TargetBuff[0]==NULL){
			return;
		}
		if(TargetBuff[0]->IsNull()==true){
			return;
		}
		return;
	}
*/
//////////
	if(MasterBuff[0]->IsNull() || TargetBuff[0]->IsNull())
		return;
/////////
	BYTE **TmpMap=MakeMatrixBuff(XByte,YLen);
	BYTE **TmpMap2=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(MaskBitmap,0,XByte,YLen);

	//?i?A?3?μ?I?a???I???I?P?x?d?v?Z?・?e
	double	AddedCTargetR=0;
	double	AddedCTargetG=0;
	double	AddedCTargetB=0;

	#pragma omp parallel
	{
		#pragma omp for reduction(+:AddedCTargetR,AddedCTargetG,AddedCTargetB)
		for(int y=0;y<YLen;y++){
			BYTE	*TLine[100];
			for(int L=0;L<LayerCount;L++){
				TLine[L]=TargetBuff[L]->GetY(y);
			}
			int	iAddedCTarget[3];
			for(int L=0;L<LayerCount && L<3;L++){
				iAddedCTarget[L]=0;
			}
			for(int x=0;x<XLen;x++){
				for(int L=0;L<LayerCount && L<3;L++){
					iAddedCTarget[L]+=TLine[L][x];
				}
			}
			switch(LayerCount){
				case 0:	break;
				case 1:	AddedCTargetR+=iAddedCTarget[0];
						break;
				case 2:	AddedCTargetR+=iAddedCTarget[0];
						AddedCTargetG+=iAddedCTarget[1];
						break;
				default:AddedCTargetR+=iAddedCTarget[0];
						AddedCTargetG+=iAddedCTarget[1];
						AddedCTargetB+=iAddedCTarget[2];
						break;
			}
		}
	}
	double	AvrCTarget[3];
	AvrCTarget[0]=AddedCTargetR/(XLen*YLen);
	AvrCTarget[1]=AddedCTargetG/(XLen*YLen);
	AvrCTarget[2]=AddedCTargetB/(XLen*YLen);

	//?・?a?E?a?e?s?N?Z???2?A?I?}?X?N?r?b?g?d?¶?￢
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			BYTE	*MLine[100];
			BYTE	*TLine[100];
			BYTE	*M=MaskBitmap[y];
			for(int L=0;L<LayerCount;L++){
				MLine[L]=MasterBuff[L]->GetY(y);
				TLine[L]=TargetBuff[L]->GetY(y);
			}
			for(int x=0;x<XLen;x++){
				int	MLen=0;
				int	TLen=0;
				int	DLen=0;
				if(PnDbgX==x && PnDbgY==y){
					PnDbg++;
				}
				for(int L=0;L<LayerCount && L<3;L++){
					MLen += MLine[L][x]*MLine[L][x];
					if(TLine[L][x]<=StageShadeColor){
						//?i?A?3?μ?a???A?X?e?[?W?a?E?C?A?A?・?￢?e???a?I???I?P?x?d?I?p?・?e
						TLen += AvrCTarget[L]*AvrCTarget[L];
						DLen +=(MLine[L][x]-AvrCTarget[L])*(MLine[L][x]-AvrCTarget[L]);
					}
					else{
						TLen += TLine[L][x]*TLine[L][x];
						DLen +=(MLine[L][x]-TLine[L][x])*(MLine[L][x]-TLine[L][x]);
					}
				}
				int	KLen=min(MLen,TLen);
				//if((DLen>KLen*ColDiffRate*ColDiffRate/10000 && TLen<=MLen) || (DLen>KLen*0.5)){
				if(DLen>KLen*ColDiffRate*ColDiffRate/10000 && TLen<=MLen){
					SetBmpBitOnY1(M,x);
				}
				if(PickupDarker==true){
					if(DLen>TLen*ColDiffRate*ColDiffRate/10000 && TLen>MLen){
						SetBmpBitOnY1(M,x);
					}
				}
			}
		}
	}
	//?S?O?s?T?d?3?o?G???A?E?・?e
	int	Len=max(EnLargeDot,EnSmallDot);
	Len=max(Len,30);
	for(int y=0;y<Len;y++){
		memset(MaskBitmap[y],0,XByte);
	}
	for(int y=0;y<Len;y++){
		memset(MaskBitmap[YLen-y-1],0,XByte);
	}
	for(int y=0;y<YLen;y++){
		for(int x=0;x<Len;x++){
			BYTE	*M=MaskBitmap[y];
			SetBmpBitOnY0(M,x);
			SetBmpBitOnY0(M,(XLen-x-1));
		}
	}

	GetLayersBase()->FatAreaN(MaskBitmap
				,TmpMap
				,XByte, YLen
				,NoiseSize);
	GetLayersBase()->ThinAreaN(MaskBitmap
				,TmpMap
				,XByte, YLen
				,NoiseSize);
	GetLayersBase()->ThinAreaN(MaskBitmap
				,TmpMap
				,XByte, YLen
				,NoiseSize);
	GetLayersBase()->FatAreaN(MaskBitmap
				,TmpMap
				,XByte, YLen
				,NoiseSize);

	MatrixBuffCopy(TmpMap2,XByte, YLen
                 , (const BYTE **)MaskBitmap,XByte, YLen);

	GetLayersBase()->FatAreaN(MaskBitmap
				,TmpMap
				,XByte, YLen
				,EnLargeDot);

	//MinSlitDot?E?a?I?A?O?μ?・?￢???X???b?g?d?n???3?1?e
	MatrixBuffCopy(TmpMap	 ,XByte, YLen
                 , (const BYTE **)MaskBitmap,XByte, YLen);

		//?±?INotAnd?A?X???b?g?A???E?C?A?A?O?μ?・?￢??Bitmap?d?¶?￢
	MatrixBuffNotAnd(TmpMap,(const BYTE **)TmpMap2,XByte, YLen);
	
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpMap,XByte ,XLen,YLen ,FPack);

	MatrixBuffClear(TmpMap2 ,0,XByte ,YLen);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetPatternByte()>MinSlitDot && (f->GetWidth()>MinSlitSize || f->GetHeight()>MinSlitSize)){
			f->MakeBitData(TmpMap2 ,XLen ,YLen);
		}
	}
	GetLayersBase()->ThinAreaN(TmpMap2
				,TmpMap
				,XByte, YLen
				,MinSlitWidth/2);
	GetLayersBase()->FatAreaN(TmpMap2
				,TmpMap
				,XByte, YLen
				,MinSlitWidth/2);

	MatrixBuffNotAnd(MaskBitmap,(const BYTE **)TmpMap2,XByte, YLen);
	
	//?C???I???e?I?d?c?A?￣?A?≫?e?d?L?o?G???A?E?・?e
	PureFlexAreaListContainer PickedPack;
	PickupFlexArea(MaskBitmap,XByte ,XLen,YLen ,PickedPack);

	MatrixBuffClear(TmpMap2 ,0xFF,XByte, YLen);
	MatrixBuffNotAnd(TmpMap2,(const BYTE **)MaskBitmap,XByte, YLen);
	PureFlexAreaListContainer LakePack;
	PickupFlexArea(TmpMap2,XByte ,XLen,YLen ,LakePack);
	for(PureFlexAreaList *f=LakePack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()<MaxLakeSize && f->GetHeight()<MaxLakeSize){
			int	X1,Y1,X2,Y2;
			f->GetXY(X1,Y1,X2,Y2);
			for(PureFlexAreaList *g=PickedPack.GetFirst();g!=NULL;g=g->GetNext()){
				if(g->GetWidth()<MaxLakeSize && g->GetHeight()<MaxLakeSize){
					int	Cx,Cy;
					g->GetCenter(Cx,Cy);
					if(f->IsInclude(Cx,Cy)==false && X1<Cx && Cx<X2 && Y1<Cy && Cy<Y2){
						f->MakeBitData(MaskBitmap,XLen ,YLen);
						break;
					}
				}
			}
		}
	}
	//?￢?3?E?L?o?}?X?N?d?i??
	PickedPack.RemoveAll();
	PickupFlexArea(MaskBitmap,XByte ,XLen,YLen ,PickedPack);
	MatrixBuffClear(MaskBitmap ,0,XByte ,YLen);
	for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()>MinClusterSize && f->GetHeight()>MinClusterSize && f->GetPatternByte()>=MinClusterArea){
			f->MakeBitData(MaskBitmap,XLen ,YLen);
		}
	}
/*
	//?u?k?3?1?e
	for(int i=0;i<(EnLargeDot+EnSmallDot);i++){
		ThinArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}

	DeleteMatrixBuff(TmpMap ,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
*/

	if(chkEnLargeDot==true){
		GetLayersBase()->ThinAreaN(MaskBitmap
					,TmpMap
					,XByte, YLen
					,EnLargeDot+EnSmallDot);
	}
	else{
		GetLayersBase()->ThinAreaN(MaskBitmap
					,TmpMap
					,XByte, YLen
					,EnLargeDot);

		//EnLargeDot?a???￣?u?k?3?1??Map?d???e
		MatrixBuffCopy(TmpMap2,XByte,YLen
					 , (const BYTE **)MaskBitmap,XByte, YLen);

		GetLayersBase()->ThinAreaN(MaskBitmap
					,TmpMap
					,XByte, YLen
					,EnSmallDot);

		//?u?k?3?1?e?O?IMap?AAnd?d?a?e
		MatrixBuffXor(TmpMap2 ,(const BYTE **)MaskBitmap,XByte, YLen);
//		MatrixBuffXor(MaskBitmap,TmpMap2 ,XByte, YLen);

		//?p?b?h?a?d?w?i?i?X???b?g?j?A?e?F?￣?μ?E?￠?a???E?A?p?b?h???o?F?A?a?r?・?e
///		AutoPCBHoleAlignerLibrary *PCBHoleAlignLib=GetFirstAutoPCBHoleAlignerLibrary();
		AlgorithmLibraryLevelContainer *LLib=GetFirstAutoAlignmentLibrary();
		AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(LLib->GetLibrary());

		PickedPack.RemoveAll();
		PickupFlexArea(TmpMap2,XByte ,XLen,YLen ,PickedPack);
		MatrixBuffClear(TmpMap2 ,0,XByte ,YLen);
		for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(ComparePickupPadColor(f,ALib,MasterBuff)==true){
				f->MakeBitData(TmpMap2,XLen ,YLen);
			}
		}

		//?u?k?3?1?e?O?IMap?AAnd?d?a?e
		MatrixBuffXor(MaskBitmap,(const BYTE **)TmpMap2 ,XByte, YLen);
	}

	//?￢?3?E?L?o?}?X?N?d?i??
	PickedPack.RemoveAll();
	PickupFlexArea(MaskBitmap,XByte ,XLen,YLen ,PickedPack);
	MatrixBuffClear(MaskBitmap ,0,XByte ,YLen);
	for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()>MinClusterSize && f->GetHeight()>MinClusterSize && f->GetPatternByte()>=MinClusterArea){
			f->MakeBitData(MaskBitmap,XLen ,YLen);
		}
	}

	DeleteMatrixBuff(TmpMap ,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
}

AlgorithmLibraryLevelContainer *AutoMaskingPILibrary::GetFirstAutoAlignmentLibrary()
{
	//???C?u?????i?n?d?a??
	AlgorithmBase	*AutoAlignmentBasePointer=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(AutoAlignmentBasePointer==NULL){
		return NULL;
	}
	//?A???a??
	CmdReqAutoAlignmentEnumLibs	CmdAlignEnum(GetLayersBase());
	AutoAlignmentBasePointer->TransmitDirectly(&CmdAlignEnum);

	IntClass *LibIDPoint=CmdAlignEnum.LibIDList.GetFirst();
	AlgorithmLibraryLevelContainer	*SrcLib=new AlgorithmLibraryLevelContainer(AutoAlignmentBasePointer);
	if(LibIDPoint!=NULL){
		int	LibID=LibIDPoint->GetValue();
		AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,*SrcLib);
	}
	return SrcLib;
}


bool AutoMaskingPILibrary::ComparePickupPadColor(PureFlexAreaList *AreaList,AutoAlignmentLibrary *Lib,ImageBuffer *MImageList[])
{
	int DotCounter=0;
	BYTE *Brightness[3];
	int	Len=AreaList->GetFLineLen();
	int	Page=0;
	for(int i=0;i<Len;i++){
		int x1=AreaList->GetFLineLeftX (i);
		int x2=AreaList->GetFLineRightX(i);
		int y =AreaList->GetFLineAbsY  (i);

		if(GetLayerNumb(Page)>=3){
			Brightness[0]=MImageList[0]->GetY(y);
			Brightness[1]=MImageList[1]->GetY(y);
			Brightness[2]=MImageList[2]->GetY(y);
		}
		else if(GetLayerNumb(Page)==2){
			Brightness[0]=MImageList[0]->GetY(y);
			Brightness[1]=MImageList[1]->GetY(y);
			Brightness[2]=MImageList[1]->GetY(y);
		}
		else if(GetLayerNumb(Page)==1){
			Brightness[0]=MImageList[0]->GetY(y);
			Brightness[1]=MImageList[0]->GetY(y);
			Brightness[2]=MImageList[0]->GetY(y);
		}

		for(int x=x1;x<x2;x++){
			if(Lib->PickupColor.Calc(Brightness[0][x],Brightness[1][x],Brightness[2][x],0)==true){
				DotCounter++;
			}
		}
	}

	int64 AreaDot=AreaList->GetPatternByte();
	if((double)DotCounter/(double)AreaDot>0.2){
		return true;
	}
	return false;
}

AutoMaskingPIThreshold::AutoMaskingPIThreshold(AutoMaskingPIItem *parent)
:AlgorithmThreshold(parent)
{
	Effective=false;
}

void	AutoMaskingPIThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AutoMaskingPIThreshold *s=(const AutoMaskingPIThreshold *)&src;

	SelAreaID=s->SelAreaID;
	Effective=s->Effective;
}
bool	AutoMaskingPIThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AutoMaskingPIThreshold *s=(const AutoMaskingPIThreshold *)&src;

	if(SelAreaID!=s->SelAreaID)	return false;
	if(Effective!=s->Effective)	return false;
	return true;
}

bool	AutoMaskingPIThreshold::Save(QIODevice *file)
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

bool	AutoMaskingPIThreshold::Load(QIODevice *file)
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

AlgorithmItemPI &AutoMaskingPIItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}



bool		AutoMaskingPIItem::IsEffective(void)	const
{
	return (((AutoMaskingPIItem *)this)->GetThresholdR())->Effective;
}

void		AutoMaskingPIItem::SetEffective(bool effective)
{
	GetThresholdW()->Effective=effective;
}

void	AutoMaskingPIItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AutoMaskingPIDrawAttr	*a=dynamic_cast<AutoMaskingPIDrawAttr	*>(Attr);
	if(a!=NULL){
		AutoMaskingPIDrawAttr	A=*((AutoMaskingPIDrawAttr *)Attr);
		if(IsEffective()==false){
			if(A.IneffectiveMode==true){
				A.NormalColor	=A.NegColorMask;
				A.SelectedColor =A.NegColorSelected;
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


AutoMaskingPIInPage::AutoMaskingPIInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	AutoMaskMap	=NULL;
	MaskMap		=NULL;
	XByte	= 0;
	XLen	= 0;
	YLen	= 0;

	sNoPCBImagePath=/**/"";
}

AutoMaskingPIInPage::~AutoMaskingPIInPage(void)
{
	if(AutoMaskMap!=NULL){
		DeleteMatrixBuff(AutoMaskMap,YLen);
	}
	if(MaskMap!=NULL){
		DeleteMatrixBuff(MaskMap,YLen);
	}
	AutoMaskMap	=NULL;
	MaskMap		=NULL;
	XByte	= 0;
	XLen	= 0;
	YLen	= 0;
}

void	AutoMaskingPIInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateAutoMaskingPIBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateAutoMaskingPIBitmapWithLibPacket*>(packet);
	if(BmpWithLibPacket!=NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();	

//		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
//					 ,Dst,XByte,YLen);
//		BmpWithLibPacket->BmpMap=Dst;

		/*
		if(MaskMap==NULL){
			BYTE	**Dst=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(Dst ,0,XByte,YLen);
			BmpWithLibPacket->BmpMap=Dst;
		}
		else{
			BmpWithLibPacket->BmpMap=GetItemBitmap();
		}
		*/
		BmpWithLibPacket->BmpMap=GetItemBitmap();
		return;
	}
	CmdCreateAutoMaskingPIAutoBitmapWithLibPacket	*AutoBmpWithLibPacket=dynamic_cast<CmdCreateAutoMaskingPIAutoBitmapWithLibPacket*>(packet);
	if(AutoBmpWithLibPacket!=NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();
		AutoBmpWithLibPacket->AutoBmpMap=GetItemAutoBitmap();
		return;
	}
	CmdGenerateAutoMaskingPILibraryPacket	*CmdGenerateAutoMaskingPILibraryPacketVar=dynamic_cast<CmdGenerateAutoMaskingPILibraryPacket *>(packet);
	if(CmdGenerateAutoMaskingPILibraryPacketVar!=NULL){
		ImageBuffer *MasterImageList[100];
		ImageBuffer *TargetImageList[100];
		GetMasterBuffList(MasterImageList);
		GetTargetBuffList(TargetImageList);
		if(AutoMaskMap==NULL){
			XByte	=(GetDotPerLine()+7)/8;
			XLen	=GetDotPerLine();
			YLen	=GetMaxLines();	
			AutoMaskMap=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(AutoMaskMap ,0,XByte,YLen);
		}

		AutoMaskingPIBase	*PBase=(AutoMaskingPIBase *)GetParentBase();
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		if(CmdGenerateAutoMaskingPILibraryPacketVar->LibID>=0){
			AlgorithmLibraryLevelContainer	Lib(PBase);
			if(Container->GetLibrary(CmdGenerateAutoMaskingPILibraryPacketVar->LibID ,Lib)==true){
				AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(Lib.GetLibrary());
				ALib->MakeMask(MasterImageList
							,TargetImageList
							,GetLayerNumb()
							,AutoMaskMap
							,XByte ,XLen ,YLen);
			}
		}
		else{
			for(AlgorithmLibraryList *a=PBase->AdoptedLib.GetFirst();a!=NULL;a=a->GetNext()){
				AlgorithmLibraryLevelContainer	Lib(PBase);
				if(Container->GetLibrary(a->GetLibID() ,Lib)==true){
					AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(Lib.GetLibrary());
					ALib->MakeMask(MasterImageList
								,TargetImageList
								,GetLayerNumb()
								,AutoMaskMap
								,XByte ,XLen ,YLen);
				}
				break;
			}
		}
		//?^?[?Q?b?g?a???d?U?¶
		if(PBase->NoPCBImagePath.isEmpty()==true){
			return;
		}
		sNoPCBImagePath=PBase->NoPCBImagePath + QDir::separator() + QDate::currentDate().toString(/**/"yyyyMMdd") + /**/"-" + QTime::currentTime().toString(/**/"hhmmss") + /**/".pix";
		if(SaveTargetImage(sNoPCBImagePath)==false){
		}
		return;
	}
	AddAutoMaskingPIAreaPacket	*AddAutoMaskingPIAreaVar=dynamic_cast<AddAutoMaskingPIAreaPacket*>(packet);
	if(AddAutoMaskingPIAreaVar!=NULL){
		AutoMaskingPIItem	*Item=(AutoMaskingPIItem *)CreateItem();
		Item->GetThresholdW()->Effective=AddAutoMaskingPIAreaVar->Effective;
		Item->SetArea(AddAutoMaskingPIAreaVar->Area);
		AppendItem(Item);
		return;
	}
	CmdCreateMaskingBitmapWithLibPacket	*BmpWithLib=dynamic_cast<CmdCreateMaskingBitmapWithLibPacket *>(packet);
	if(BmpWithLib!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLib->XByte ,BmpWithLib->YLen);
		GetItemBitmap(Dst,BmpWithLib->XByte,BmpWithLib->XByte<<3 ,BmpWithLib->YLen);
		BmpWithLib->BmpMap=Dst;
		return;
	}
}


void	AutoMaskingPIInPage::GetItemBitmap(BYTE **Dst ,int _XByte, int _XLen ,int _YLen)
{
	if(MaskMap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();	
		MaskMap=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(MaskMap ,0,XByte,YLen);
	}
	if(AutoMaskMap!=NULL){
		MatrixBuffCopy(    Dst,XByte,YLen
                     , (const BYTE **)AutoMaskMap,XByte,YLen);
	}
	else{
		MatrixBuffClear(Dst ,0,XByte,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(Dst,XLen,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(Dst,XLen,YLen);
	}
}

BYTE **AutoMaskingPIInPage::GetItemBitmap(void)
{
	if(MaskMap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();	
		MaskMap=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(MaskMap ,0,XByte,YLen);
	}
	if(AutoMaskMap!=NULL){
		MatrixBuffCopy(MaskMap	  ,XByte,YLen
                     , (const BYTE **)AutoMaskMap,XByte,YLen);
	}
	else{
		MatrixBuffClear(MaskMap,0,XByte,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(MaskMap,XLen,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(MaskMap,XLen,YLen);
	}
	return MaskMap;
}

BYTE **AutoMaskingPIInPage::GetItemAutoBitmap(void)
{
	if(AutoMaskMap!=NULL){
		return AutoMaskMap;
	}
	return MaskMap;
}

void	AutoMaskingPIInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen
											,bool GenerateOnlyLimitMask)
{
	bool	FoundLimited=false;
	if(GetFirstData()!=NULL){
		if(AutoMaskMap!=NULL){
			MatrixBuffCopy(Dst	  ,XByte,YLen
				         , (const BYTE **)AutoMaskMap,XByte,YLen);
		}
		else{
			MatrixBuffClear(Dst ,0,XByte,YLen);
		}
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL && a->IsEffective()==true){
				a->GetArea().MakeBitData(Dst,XLen,YLen);
				FoundLimited=true;
			}
		}
		if(FoundLimited==false && GenerateOnlyLimitMask==false){
			for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
					a->GetArea().MakeBitData(Dst,XLen,YLen);
			}
		}
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
				a->GetArea().MakeNotBitData(Dst,XLen,YLen);
		}
	}
	else{
		MatrixBuffClear(MaskMap ,0xFF,XByte,YLen);
		if(AutoMaskMap!=NULL){
			MatrixBuffCopy(Dst	  ,XByte,YLen
				         , (const BYTE **)AutoMaskMap,XByte,YLen);
		}
	}
}

void	AutoMaskingPIInPage::SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen)
{
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeBitData(MaskMap,XByte<<3,YLen);
		}
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeNotBitData(MaskMap,XByte<<3,YLen);
		}
	}
}


ExeResult	AutoMaskingPIInPage::ExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),4);
	GetLayersBase()->StepProcessing(GetPage());

	int CurrentMasterCounter=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);
	if(CurrentMasterCounter==1 || CurrentMasterCounter==2 || CurrentMasterCounter==99999999){
		return _ER_true;
	}

	if(AutoMaskMap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();	
		AutoMaskMap=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(AutoMaskMap ,0,XByte,YLen);
	}
	if(MaskMap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();	
		MaskMap=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(MaskMap ,0,XByte,YLen);
	}

	ImageBuffer *MasterImageList[100];
	ImageBuffer *TargetImageList[100];
	GetMasterBuffList(MasterImageList);
	GetTargetBuffList(TargetImageList);

	for(int L=0;L<GetLayerNumb();L++){
		if(MasterImageList[L]->IsNull()==true){
			return _ER_true;
		}
	}
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	AutoMaskingPIBase	*PBase=(AutoMaskingPIBase *)GetParentBase();
	for(AlgorithmLibraryList *a=PBase->AdoptedLib.GetFirst();a!=NULL;a=a->GetNext()){	
		AlgorithmLibraryLevelContainer	Lib(Container);
		if(GetParentBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,Lib)==true){
			AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(Lib.GetLibrary());
			ALib->MakeMask(MasterImageList
							,TargetImageList
							,GetLayerNumb()
							,AutoMaskMap
							,XByte ,XLen ,YLen);
		}
		break;
	}

	GetLayersBase()->StepProcessing(GetPage());

	MatrixBuffCopy(MaskMap		,XByte,YLen
                 , (const BYTE **)AutoMaskMap	,XByte,YLen);
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(MaskMap,XLen,YLen);
	}

	GetLayersBase()->StepProcessing(GetPage());

	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR(GetLayersBase())->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(MaskMap,XLen,YLen);
	}

	GetLayersBase()->StepProcessing(GetPage());

	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

bool	AutoMaskingPIInPage::Save(QIODevice *f)
{
	WORD	Ver=4;

	if(::Save(f,Ver)==false){
		return(false);
	}
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	if(::Save(f,XByte)==false)
		return false;
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(AutoMaskMap!=NULL){
		for(int y=0;y<YLen;y++){
			BYTE	*p=AutoMaskMap[y];
			if(f->write((char *)p,XByte*sizeof(p[0]))!=XByte*sizeof(p[0]))
				return false;
		}
	}
	if(MaskMap!=NULL){
		for(int y=0;y<YLen;y++){
			BYTE	*p=MaskMap[y];
			if(f->write((char *)p,XByte*sizeof(p[0]))!=XByte*sizeof(p[0]))
				return false;
		}
	}
	if(::Save(f,sNoPCBImagePath)==false)
		return false;
	return true;
}

bool	AutoMaskingPIInPage::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false){
		return(false);
	}
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	int	iXByte;
	int	iXLen;
	int	iYLen;
	if(::Load(f,iXByte)==false)
		return false;
	if(::Load(f,iXLen)==false)
		return false;
	if(::Load(f,iYLen)==false)
		return false;

	if(iXByte!=0){
		if(iXByte!=XByte || iYLen!=YLen){
			DeleteMatrixBuff(AutoMaskMap,YLen);
			DeleteMatrixBuff(MaskMap,YLen);
			AutoMaskMap	=NULL;
			MaskMap		=NULL;
		}
		if(AutoMaskMap==NULL){
			XByte	=(GetDotPerLine()+7)/8;
			XLen	=GetDotPerLine();
			YLen	=GetMaxLines();	
			AutoMaskMap=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(AutoMaskMap ,0,XByte,YLen);
		}
		if(MaskMap==NULL){
			XByte	=(GetDotPerLine()+7)/8;
			XLen	=GetDotPerLine();
			YLen	=GetMaxLines();	
			MaskMap=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(MaskMap ,0,XByte,YLen);
		}
		for(int y=0;y<iYLen;y++){
			BYTE	*p=AutoMaskMap[y];
			if(f->read((char *)p,iXByte*sizeof(p[0]))!=iXByte*sizeof(p[0]))
				return false;
		}
		for(int y=0;y<iYLen;y++){
			BYTE	*p=MaskMap[y];
			if(f->read((char *)p,iXByte*sizeof(p[0]))!=iXByte*sizeof(p[0]))
				return false;
		}
	}
	else{
		if(XByte!=0 || YLen!=0){
			DeleteMatrixBuff(AutoMaskMap,YLen);
			DeleteMatrixBuff(MaskMap,YLen);
			AutoMaskMap	=NULL;
			MaskMap		=NULL;
		}
		XByte=0;
		XLen=0;
		YLen=0;
	}
	if(Ver>=4){
		if(::Load(f,sNoPCBImagePath)==false)
			return false;
	}

	return true;
}

void	AutoMaskingPIInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AutoMaskingPIDrawAttr	*A=(AutoMaskingPIDrawAttr *)Attr;
	if((A!=NULL) && (A->AutoGenMode==true) && (AutoMaskMap!=NULL)){
		QColor	Col=Qt::cyan;
		Col.setAlpha(180);
		DrawBitImage(pnt, (const BYTE **)AutoMaskMap ,XLen ,XByte ,YLen
					,movx ,movy ,ZoomRate
					,0,0
					,Col);
	}
	if((A!=NULL) && (A->CompositeMask==true) && (MaskMap!=NULL)){
		QColor	Col=Qt::yellow;
		Col.setAlpha(180);
		DrawBitImage(pnt, (const BYTE **)MaskMap ,XLen ,XByte ,YLen
					,movx ,movy ,ZoomRate
					,0,0
					,Col);
	}
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
}

ConstMapBuffer	*AutoMaskingPIInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
						 ,(BYTE **)Dst->GetBitMap(),GetDotPerLine() ,GetMaxLines()
						,false);
		return Dst;
	}
	else
	if(Mode==_Reflection_MaskOnlyInLimitMask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
						 ,(BYTE **)Dst->GetBitMap(),GetDotPerLine() ,GetMaxLines()
						,true);
		return Dst;
	}
	return NULL;
}
ConstMapBuffer	*AutoMaskingPIInPage::CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		ConstMapBuffer	*Dst=new ConstMapBuffer(GetDotPerLine() ,GetMaxLines(),MapBufferBase::_BitMap);
		int	iXByte	=(GetDotPerLine()+7)/8 ;
		int	iYLen	=GetMaxLines();
		GetItemBitmap((BYTE **)Dst->GetBitMap() ,iXByte,iXByte*8,iYLen);
		return Dst;
	}
	return NULL;
}
bool	AutoMaskingPIInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		return true;
	}
	return false;
}
bool	AutoMaskingPIInPage::CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything)
{
	if(Mode==_Reflection_Mask || Mode==_Reflection_MaskOnlyInLimitMask){
		return true;
	}
	return false;
}

bool	AutoMaskingPIInPage::PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	if(::Save(f,sNoPCBImagePath)==false){
		return false;
	}
/*
	int32	N=0;
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		if(k->GetArea().CheckOverlapRectangle(localX1 ,localY1 ,localX2 ,localY2)==true){
			N++;
		}
	}
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		if(k->GetArea().CheckOverlapRectangle(localX1 ,localY1 ,localX2 ,localY2)==true){
			FlexArea	A=k->GetArea();
			A.ClipArea(localX1 ,localY1 ,localX2 ,localY2);
			A.MoveToNoClip(-localX1 ,-localY1);
			AlgorithmItemPLI	*a=NewChild(k->GetItemClassType());
			*a=*k;
			a->SetArea(A);
			if(::Save(f,k->GetItemClassType())==false){
				return false;
			}
			if(a->Save(f)==false){
				return false;
			}
			delete	a;
		}
	}
*/
	return true;
}

bool	AutoMaskingPIInPage::PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
	QString	PipeInNoPCBImagePath;
	if(::Load(f,PipeInNoPCBImagePath)==false){
		return false;
	}

	//?i?A?E?μ?a???I?C?Y???Y
	if(LoadTargetImage(PipeInNoPCBImagePath,localX1,localY1,localX2,localY2)==true){
	}
	else{
		//?i?A?E?μ?a???a?C?Y???s?E?c?A???e??
	}
/*
	int32	N=0;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return false;
		}
		AlgorithmItemPLI	*a=NewChild(ItemClassType);
		if(a->Load(f,GetLayersBase())==false){
			return false;
		}
		AppendItem(a);
	}
*/
	return true;
}

bool	AutoMaskingPIInPage::SaveTargetImage(QString FileName)
{
	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=1;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetLayerNumb())==false)
		return false;
	if(::Save(&WFile,(int)GetDotPerLine())==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines())==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	GetLayersBase()->ShowProcessingForm ("Saving target image");
	GetLayersBase()->AddMaxProcessing(GetPage(),1);
	for(int page=0;page<GetPageNumb();page++){
		int	YCount=100;
		for(int TopY=0;TopY<GetMaxLines();TopY+=YCount){
			if(TopY+YCount>GetMaxLines())
				YCount=GetMaxLines()-TopY;
			for(int Layer=0;Layer<GetLayerNumb();Layer++){
				GUICmdReqSaveTargetImageForAutoMaskingPI	RCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
				RCmd.Layer	=Layer;
				RCmd.TopY	=TopY;
				RCmd.YCount	=YCount;
				GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
				if(RCmd.Send(page ,0,SCmd)==true){
					if(WFile.write(SCmd.Data)!=SCmd.Data.size()){
						return false;
					}
				}
			}
		}
		GetLayersBase()->StepProcessing(GetPage());
	}
	GetLayersBase()->CloseProcessingForm ();
	return true;
}

bool AutoMaskingPIInPage::LoadTargetImage(QString FileName,int localX1,int localY1,int localX2,int localY2)
{
	QFile	RFile(FileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;

	GetLayersBase()->ShowProcessingForm ("Loading target image");
	GetLayersBase()->AddMaxProcessing(GetPage(),min(GetPageNumb(),iPageNumb));
/*
	for(int page=0;page<SkipPage && page<iPageNumb;page++){
		int	YCount=iYCountBase;
		int	TopY;
		for(TopY=0;TopY<iMaxLines;TopY+=YCount){
			if(TopY+YCount>iMaxLines)
				YCount=iMaxLines-TopY;
			int	Layer;
			for(Layer=0;Layer<GetLayerNumb() && Layer<iLayerNumb;Layer++){
				RFile.read(YCount*iDotPerLine);
			}
		}
		GetLayersBase()->StepProcessing();
	}
*/
	for(int page=0;page<iPageNumb;page++){
		int	YCount=iYCountBase;
		int	TopY;
		for(TopY=0;TopY<iMaxLines;TopY+=YCount){
			if(TopY+YCount>iMaxLines)
				YCount=iMaxLines-TopY;
			int	Layer;
			for(Layer=0;Layer<iLayerNumb;Layer++){
				GUICmdSendLoadTargetImageForAutoMaskingPI	RCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
				RCmd.Layer		=Layer;
				RCmd.TopY		=TopY;
				RCmd.YCount		=YCount;
				RCmd.iDotPerLine=iDotPerLine;
				RCmd.Data=RFile.read(YCount*iDotPerLine);
				RCmd.localX1	=localX1;
				RCmd.localY1	=localY1;
				RCmd.localX2	=localX2;
				RCmd.localY2	=localY2;
				RCmd.SendOnly(page ,0);
			}
			if(Layer<iLayerNumb){
				for(;Layer<iLayerNumb;Layer++){
					GUICmdSendLoadTargetImageForAutoMaskingPI	RCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
					RCmd.Data=RFile.read(YCount*iDotPerLine);
				}
			}
		}
		if(TopY<iMaxLines){
			for(;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<iLayerNumb;Layer++){
					GUICmdSendLoadTargetImageForAutoMaskingPI	RCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
					RCmd.Data=RFile.read(YCount*iDotPerLine);
				}
			}			
		}
		for(int Layer=0;Layer<iLayerNumb;Layer++){
			GUICmdFinalizeLoadTargetImageForAutoMaskingPI	RCmd(GetLayersBase() ,/**/"Basic",/**/"AutoMaskingPI",page);
			RCmd.Layer		=Layer;
			RCmd.SendOnly(page ,0);
		}
		GetLayersBase()->StepProcessing(GetPage());
	}
	GetLayersBase()->CloseProcessingForm ();
///	BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	return true;
}

//===========================================
AutoMaskingPIBase::AutoMaskingPIBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive 	=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	PickupSideBarColorMergin	=10;
	BaseColorMergin 			=3;
	NoiseSize					=0;
	LeftRightMerginDot			=9; // 1 <-> 24
	TopBottomMerginDot			=0;
	MaxHoleSize					=200;
	ExpansionSlitDot			=6;
	NoPCBImagePath				=/**/"";

	SetParam(&ColorMask					, /**/"Color" ,/**/"ColorMask" 		,LangSolver.GetString(XAutoMaskingPI_LS,LID_1)/*"Color for Mask"*/);
	SetParam(&ColorSelected				, /**/"Color" ,/**/"ColorSelected" 	,LangSolver.GetString(XAutoMaskingPI_LS,LID_3)/*"Color for Selected Mask"*/);
	SetParam(&ColorActive				, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XAutoMaskingPI_LS,LID_5)/*"Color for Active Mask"*/);
	SetParam(&NegColorMask				, /**/"Color" ,/**/"NegColorMask"		,LangSolver.GetString(XAutoMaskingPI_LS,LID_7)/*"Color for Negative Mask"*/);
	SetParam(&NegColorSelected			, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XAutoMaskingPI_LS,LID_9)/*"Color for Selected Negative Mask"*/);
	SetParam(&TransparentLevel			, /**/"Color" ,/**/"TransparentLevel" ,LangSolver.GetString(XAutoMaskingPI_LS,LID_11)/*"Color for Transparent display level"*/);
	SetParam(&PickupSideBarColor		, /**/"Setting" ,/**/"PickupSideBarColor" 	,LangSolver.GetString(XAutoMaskingPI_LS,LID_13)/*"Color for Pickup"*/);
	SetParam(&BaseColor 				, /**/"Setting" ,/**/"BaseColor"				,LangSolver.GetString(XAutoMaskingPI_LS,LID_15)/*"Color for nothing"*/);
	SetParam(&PickupSideBarColorMergin	, /**/"Setting" ,/**/"PickupSideBarColorMergin"	,LangSolver.GetString(XAutoMaskingPI_LS,LID_17)/*"Pickup color mergin"*/);
	SetParam(&BaseColorMergin			, /**/"Setting" ,/**/"BaseColorMergin"			,LangSolver.GetString(XAutoMaskingPI_LS,LID_19)/*"nothing color mergin"*/);
	SetParam(&NoiseSize 				, /**/"Setting" ,/**/"NoiseSize"				,LangSolver.GetString(XAutoMaskingPI_LS,LID_21)/*"Noize size for Automatic pickup"*/);
	SetParam(&LeftRightMerginDot		, /**/"Setting" ,/**/"LeftRightMerginDot" 	,LangSolver.GetString(XAutoMaskingPI_LS,LID_23)/*"Mergin dot for left side and right side"*/);
	SetParam(&TopBottomMerginDot		, /**/"Setting" ,/**/"TopBottomMerginDot" 	,LangSolver.GetString(XAutoMaskingPI_LS,LID_25)/*"Mergin dot for top side and bottom side"*/);

	SetParam(&MaxHoleSize				, /**/"Setting" ,/**/"MaxHoleSize"		,LangSolver.GetString(XAutoMaskingPI_LS,LID_26)/*"Maximum hole size to include mask area"*/);
	SetParam(&ExpansionSlitDot			, /**/"Setting" ,/**/"ExpansionSlitDot" ,LangSolver.GetString(XAutoMaskingPI_LS,LID_27)/*"Enlarge mergin for slit"*/);

	SetParamPath(&NoPCBImagePath		, /**/"Setting" ,/**/"NoPCBImagePath"	,LangSolver.GetString(XAutoMaskingPI_LS,LID_28)/*"No PCB Image Path (Only stage image)"*/);
}

AlgorithmDrawAttr	*AutoMaskingPIBase::CreateDrawAttr(void)
{
	return new AutoMaskingPIDrawAttr();
}

bool	AutoMaskingPIBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	SelectLibraryInMaskForm *DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	//DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	MaskingPIItem	Item(NULL);
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	*/
	return true;
}

void	AutoMaskingPIBase::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdExecuteAutoPickup *GUICmdExecuteAutoPickupVar=dynamic_cast<GUICmdExecuteAutoPickup *>(packet);
	if(GUICmdExecuteAutoPickupVar!=NULL){
		CmdGenerateAutoMaskForDesktop	Cmd(GetLayersBase());
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
///				GetPageData(page)->TransmitDirectly(&Cmd);
				GetPageDataPhase(phase)->GetPageData(page)->TransmitDirectly(&Cmd);
			}
		}
		return;
	}
	CmdGenerateAutoMaskForDesktop	*CmdGenerateAutoMaskForDesktopVar=dynamic_cast<CmdGenerateAutoMaskForDesktop *>(packet);
	if(CmdGenerateAutoMaskForDesktopVar!=NULL){
		GetPageData(CmdGenerateAutoMaskForDesktopVar->LocalPage)->TransmitDirectly(packet);
		return;
	}

	CmdGenerateAutoMaskingPILibraryPacket	*CmdGenerateAutoMaskingPILibraryPacketVar=dynamic_cast<CmdGenerateAutoMaskingPILibraryPacket *>(packet);
	if(CmdGenerateAutoMaskingPILibraryPacketVar!=NULL){
		SetAdopted();
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
///				GetPageData(page)->TransmitDirectly(packet);
				GetPageDataPhase(phase)->GetPageData(page)->TransmitDirectly(packet);
			}
		}
		return;
	}

	CmdGetAutoMaskingPILibraryListPacket	*AListPacket=dynamic_cast<CmdGetAutoMaskingPILibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetAutoMaskingPILibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAutoMaskingPILibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAutoMaskingPILibraryPacket	*BInsLib=dynamic_cast<CmdInsertAutoMaskingPILibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AutoMaskingPIVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAutoMaskingPILibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAutoMaskingPILibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AutoMaskingPIVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAutoMaskingPILibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAutoMaskingPILibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAutoMaskingPILibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAutoMaskingPILibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearAutoMaskingPILibraryPacket	*CmdClearAutoMaskingPILibraryPacketVar=dynamic_cast<CmdClearAutoMaskingPILibraryPacket *>(packet);
	if(CmdClearAutoMaskingPILibraryPacketVar!=NULL){
		CmdClearAutoMaskingPILibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAutoMaskingPILibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAutoMaskingPILibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
}

bool	AutoMaskingPIBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}

bool	AutoMaskingPIBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}
ExeResult	AutoMaskingPIBase::ExecuteInitialAfterEdit(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	SetAdopted();

	return AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}

void	AutoMaskingPIBase::SetAdopted(void)
{
	AdoptedLib.RemoveAll();
	AlgorithmLibraryListContainer	TmpLibContainer;
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	Container->EnumLibrary(GetLibType(),TmpLibContainer);
	for(AlgorithmLibraryList *a=TmpLibContainer.GetFirst();a!=NULL;a=a->GetNext()){			
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(a->GetLibID() ,SrcLib)==true){
			AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(SrcLib.GetLibrary());
			if(ALib->DefaultMask==true){
				AdoptedLib.Add(Container->GetLibType(),SrcLib);
			}
		}
	}
}

bool	AutoMaskingPIBase::PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	AutoMaskingPIInPage	*P=(AutoMaskingPIInPage *)GetPageData(LocalPage);
	if(P->PipeOutAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}
bool	AutoMaskingPIBase::PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	AutoMaskingPIInPage	*P=(AutoMaskingPIInPage *)GetPageData(LocalPage);
	if(P->PipeInAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}

//===========================================================================================

GUICmdReqSaveTargetImageForAutoMaskingPI::GUICmdReqSaveTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSaveTargetImageForAutoMaskingPI::Load(QIODevice *f)
{
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	GUICmdReqSaveTargetImageForAutoMaskingPI::Save(QIODevice *f)
{
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqSaveTargetImageForAutoMaskingPI::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSaveTargetImage	*SendBack=GetSendBack(GUICmdSendSaveTargetImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		SendBack->Data.resize(YCount*GetDotPerLine(localPage));
		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,L->GetTargetBuff().GetY(y),GetDotPerLine(localPage));
			Dest+=GetDotPerLine(localPage);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSaveTargetImage::GUICmdSendSaveTargetImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSaveTargetImage::Load(QIODevice *f)
{
	Data=f->readAll();
	return true;
}
bool	GUICmdSendSaveTargetImage::Save(QIODevice *f)
{
	f->write(Data);
	return true;
}

void	GUICmdSendSaveTargetImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//======================================================================================

GUICmdSendLoadTargetImageForAutoMaskingPI::GUICmdSendLoadTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendLoadTargetImageForAutoMaskingPI::Load(QIODevice *f)
{
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,iDotPerLine)==false)
		return false;
	Data=f->readAll();
	return true;
}
bool	GUICmdSendLoadTargetImageForAutoMaskingPI::Save(QIODevice *f)
{
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,iDotPerLine)==false)
		return false;
	f->write(Data);
	return true;
}

void	GUICmdSendLoadTargetImageForAutoMaskingPI::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		BYTE	*Src=(BYTE *)Data.data();
		int	XLen=min(iDotPerLine,GetDotPerLine(localPage));
		if((TopY+YCount>=localY1 && TopY<=localY2)){
			for(int y=TopY;y<TopY+YCount;y++){
				if(y<GetMaxLines(localPage)){
					if(y>=localY1 && y<=localY2){
						memcpy(L->GetTargetBuff().GetY(y)+localX1,Src,localX2-localX1);
					}
					Src+=iDotPerLine;
				}
			}
		}
	}
	SendAck(localPage);
}
//======================================================================================

GUICmdFinalizeLoadTargetImageForAutoMaskingPI::GUICmdFinalizeLoadTargetImageForAutoMaskingPI(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdFinalizeLoadTargetImageForAutoMaskingPI::Load(QIODevice *f)
{

	if(::Load(f,Layer)==false)
		return false;

	return true;
}
bool	GUICmdFinalizeLoadTargetImageForAutoMaskingPI::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdFinalizeLoadTargetImageForAutoMaskingPI::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
	if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
		L->CopyTargetImageToRaw();
	}
	SendAck(localPage);
}
