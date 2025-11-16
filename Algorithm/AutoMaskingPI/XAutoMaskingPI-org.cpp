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
:ServiceForLayers(Base),AlgorithmLibrary(LibType)
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


AutoMaskingPILibrary	&AutoMaskingPILibrary::operator=(AlgorithmLibrary &src)
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
	BYTE **TmpMap=MakeMatrixBuff(XByte,YLen);
	BYTE **TmpMap2=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(MaskBitmap,0,XByte,YLen);

	//基板無しの画像の平均輝度を計算する
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

	//差分によるピクセルごとのマスクビットを生成
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
						//基板無し画像でステージ溝などで暗すぎる部分は平均輝度を採用する
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
	//４辺近傍を無効エリアにする
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
	//ノイズ除去
	for(int i=0;i<NoiseSize;i++){
		FatArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}
	for(int i=0;i<NoiseSize;i++){
		ThinArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}
	for(int i=0;i<NoiseSize;i++){
		ThinArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}
	for(int i=0;i<NoiseSize;i++){
		FatArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}

	MatrixBuffCopy(TmpMap2,XByte, YLen
                 , (const BYTE **)MaskBitmap,XByte, YLen);

	//小さな穴、スリットを塗りつぶす
	for(int i=0;i<EnLargeDot;i++){
		FatArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}

	//MinSlitDot以上のつぶしすぎたスリットを回復させる
	MatrixBuffCopy(TmpMap	 ,XByte, YLen
                 , (const BYTE **)MaskBitmap,XByte, YLen);

		//このNotAndでスリット、穴など、つぶしすぎたBitmapを生成
	MatrixBuffNotAnd(TmpMap,(const BYTE **)TmpMap2,XByte, YLen);
	
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpMap,XByte ,XLen,YLen ,FPack);

	MatrixBuffClear(TmpMap2 ,0,XByte ,YLen);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetPatternByte()>MinSlitDot && (f->GetWidth()>MinSlitSize || f->GetHeight()>MinSlitSize)){
			f->MakeBitData(TmpMap2);
		}
	}
	for(int i=0;i<MinSlitWidth/2;i++){
		ThinArea(TmpMap2
				,TmpMap
				,XByte, YLen);
	}
	for(int i=0;i<MinSlitWidth/2;i++){
		FatArea(TmpMap2
				,TmpMap
				,XByte, YLen);
	}
	MatrixBuffNotAnd(MaskBitmap,(const BYTE **)TmpMap2,XByte, YLen);
	
	//孤島のある湖を見つけ、それを有効エリアにする
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
						f->MakeBitData(MaskBitmap);
						break;
					}
				}
			}
		}
	}
	//小さな有効マスクを削除
	PickedPack.RemoveAll();
	PickupFlexArea(MaskBitmap,XByte ,XLen,YLen ,PickedPack);
	MatrixBuffClear(MaskBitmap ,0,XByte ,YLen);
	for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()>MinClusterSize && f->GetHeight()>MinClusterSize && f->GetPatternByte()>=MinClusterArea){
			f->MakeBitData(MaskBitmap);
		}
	}
/*
	//収縮させる
	for(int i=0;i<(EnLargeDot+EnSmallDot);i++){
		ThinArea(MaskBitmap
				,TmpMap
				,XByte, YLen);
	}

	DeleteMatrixBuff(TmpMap ,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
*/

	if(chkEnLargeDot==true){
		//収縮させる
		for(int i=0;i<EnLargeDot+EnSmallDot;i++){
			ThinArea(MaskBitmap
					,TmpMap
					,XByte, YLen);
		}
	}
	else{
		//収縮させる
		for(int i=0;i<EnLargeDot;i++){
			ThinArea(MaskBitmap
					,TmpMap
					,XByte, YLen);
		}

		//EnLargeDot分だけ収縮させたMapを得る
		MatrixBuffCopy(TmpMap2,XByte,YLen
					 , (const BYTE **)MaskBitmap,XByte, YLen);

		//収縮させる
		for(int i=0;i<EnSmallDot;i++){
			ThinArea(MaskBitmap
					,TmpMap
					,XByte, YLen);
		}

		//収縮させる前のMapとAndを取る
		MatrixBuffXor(TmpMap2 ,(const BYTE **)MaskBitmap,XByte, YLen);
//		MatrixBuffXor(MaskBitmap,TmpMap2 ,XByte, YLen);

		//パッド上を背景（スリット）と誤認識しないように、パッド抽出色と比較する
///		AutoPCBHoleAlignerLibrary *PCBHoleAlignLib=GetFirstAutoPCBHoleAlignerLibrary();
		AutoAlignmentLibrary *AlignLib=GetFirstAutoAlignmentLibrary();

		PickedPack.RemoveAll();
		PickupFlexArea(TmpMap2,XByte ,XLen,YLen ,PickedPack);
		MatrixBuffClear(TmpMap2 ,0,XByte ,YLen);
		for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
			if(ComparePickupPadColor(f,AlignLib,MasterBuff)==true){
				f->MakeBitData(TmpMap2);
			}
		}

		//収縮させる前のMapとAndを取る
		MatrixBuffXor(MaskBitmap,(const BYTE **)TmpMap2 ,XByte, YLen);
	}

	//小さな有効マスクを削除
	PickedPack.RemoveAll();
	PickupFlexArea(MaskBitmap,XByte ,XLen,YLen ,PickedPack);
	MatrixBuffClear(MaskBitmap ,0,XByte ,YLen);
	for(PureFlexAreaList *f=PickedPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetWidth()>MinClusterSize && f->GetHeight()>MinClusterSize && f->GetPatternByte()>=MinClusterArea){
			f->MakeBitData(MaskBitmap);
		}
	}

	DeleteMatrixBuff(TmpMap ,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
}

AutoAlignmentLibrary *AutoMaskingPILibrary::GetFirstAutoAlignmentLibrary()
{
	//ライブラリ情報を取得
	AlgorithmBase	*AutoAlignmentBasePointer=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(AutoAlignmentBasePointer==NULL){
		return NULL;
	}
	//個数取得
	CmdReqAutoAlignmentEnumLibs	CmdAlignEnum(GetLayersBase());
	AutoAlignmentBasePointer->TransmitDirectly(&CmdAlignEnum);

	AutoAlignmentLibrary	*Lib=dynamic_cast<AutoAlignmentLibrary *>(AutoAlignmentBasePointer->GetLibraryContainer()->CreateNew());
	if(Lib==NULL){
		return NULL;
	}
	IntClass *LibIDPoint=CmdAlignEnum.LibIDList.GetFirst();
	if(LibIDPoint!=NULL){
		int	LibID=LibIDPoint->GetValue();
		//ライブラリの中身をＩＤ番号から取得
		//ライブラリの読込コードが無くても仮想関数で読込できる
		AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,*Lib);
	}
	return Lib;
}

//パッド上を背景（スリット）と誤認識しないように、パッド抽出色と比較する
bool AutoMaskingPILibrary::ComparePickupPadColor(PureFlexAreaList *AreaList,AutoAlignmentLibrary *Lib,ImageBuffer *MImageList[])
{
	int DotCounter=0;
	BYTE *Brightness[3];
	int	Len=AreaList->GetFLineLen();
	for(int i=0;i<Len;i++){
		int x1=AreaList->GetFLineLeftX (i);
		int x2=AreaList->GetFLineRightX(i);
		int y =AreaList->GetFLineAbsY  (i);

		if(GetLayerNumb()>=3){
			Brightness[0]=MImageList[0]->GetY(y);
			Brightness[1]=MImageList[1]->GetY(y);
			Brightness[2]=MImageList[2]->GetY(y);
		}
		else if(GetLayerNumb()==2){
			Brightness[0]=MImageList[0]->GetY(y);
			Brightness[1]=MImageList[1]->GetY(y);
			Brightness[2]=MImageList[1]->GetY(y);
		}
		else if(GetLayerNumb()==1){
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

	int AreaDot=AreaList->GetPatternByte();
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
	SelAreaID=((AutoMaskingPIThreshold *)&src)->SelAreaID;
	Effective=((AutoMaskingPIThreshold *)&src)->Effective;
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



bool		AutoMaskingPIItem::IsEffective(void)
{
	return GetThresholdR()->Effective;
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
		if(CmdGenerateAutoMaskingPILibraryPacketVar->LibID>=0){
			AutoMaskingPILibrary	Lib(GetLibraryContainer()->GetLibType(),GetLayersBase());
			GetParentBase()->GetLibraryContainer()->GetLibrary(CmdGenerateAutoMaskingPILibraryPacketVar->LibID ,Lib);
			Lib.MakeMask(MasterImageList
					,TargetImageList
					,GetLayerNumb()
					,AutoMaskMap
					,XByte ,XLen ,YLen);
		}
		else{
			for(AlgorithmLibraryList *a=PBase->AdoptedLib.GetFirst();a!=NULL;a=a->GetNext()){
				AutoMaskingPILibrary	Lib(GetLibraryContainer()->GetLibType(),GetLayersBase());
				GetParentBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,Lib);
				Lib.MakeMask(MasterImageList
							,TargetImageList
							,GetLayerNumb()
							,AutoMaskMap
							,XByte ,XLen ,YLen);
				break;
			}
		}
		//ターゲット画像を保存
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
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(Dst,XLen,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
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
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(MaskMap,XLen,YLen);
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
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

void	AutoMaskingPIInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen)
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
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL && a->IsEffective()==true){
				a->GetArea().MakeBitData(Dst,XLen,YLen);
				FoundLimited=true;
			}
		}
		if(FoundLimited==false){
			for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
					a->GetArea().MakeBitData(Dst,XLen,YLen);
			}
		}
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
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
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeBitData(MaskMap,XByte<<3,YLen);
		}
	}
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()!=NULL){
			AlgorithmLibraryList	*s=((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->SearchLibrary(LibType,LibID);
			if(s!=NULL)
				a->GetArea().MakeNotBitData(MaskMap,XByte<<3,YLen);
		}
	}
}

/*
AutoPCBHoleAlignerLibrary *AutoMaskingPIInPage::GetFirstAutoPCBHoleAlignerLibrary()
{
	//ライブラリ情報を取得
	AlgorithmBase	*AutoPCBHoleAlignerBasePointer=GetLayersBase()->GetAlgorithmBase("Basic","AutoPCBHoleAligner");
	if(AutoPCBHoleAlignerBasePointer==NULL){
		return NULL;
	}
	//個数取得
	CmdReqAutoPCBHoleAlignerEnumLibs	CmdPCBHoleAlignEnum;
	AutoPCBHoleAlignerBasePointer->TransmitDirectly(&CmdPCBHoleAlignEnum);

	AutoPCBHoleAlignerLibrary	*Lib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(AutoPCBHoleAlignerBasePointer->GetLibraryContainer()->CreateNew());
	if(Lib==NULL){
		return NULL;
	}
	IntClass *LibIDPoint=CmdPCBHoleAlignEnum.LibIDList.GetFirst();
	if(LibIDPoint!=NULL){
		int	LibID=LibIDPoint->GetValue();
		//ライブラリの中身をＩＤ番号から取得
		//ライブラリの読込コードが無くても仮想関数で読込できる
		AutoPCBHoleAlignerBasePointer->GetLibraryContainer()->GetLibrary(LibID,*Lib);
	}
	return Lib;
}

//基板上を背景（スリット）と誤認識しないように、穴抽出色と比較する
bool AutoMaskingPIInPage::ComparePickupHoleColor(PureFlexAreaList *AreaList,AutoPCBHoleAlignerLibrary *Lib,ImageBuffer *MImageList[])
{
	int DotCounter=0;
	BYTE *Brightness[3];
	int	Len=AreaList->GetFLineLen();
	for(int i=0;i<Len;i++){
		int x1=AreaList->GetFLineLeftX (i);
		int x2=AreaList->GetFLineRightX(i);
		int y =AreaList->GetFLineAbsY  (i);

		Brightness[0]=MImageList[0]->GetY(y);
		Brightness[1]=MImageList[1]->GetY(y);
		Brightness[2]=MImageList[2]->GetY(y);

		for(int x=x1;x<x2;x++){
			if(Lib->PickupHoleColor.Calc(Brightness[0][x],Brightness[1][x],Brightness[2][x],0)==true){
				DotCounter++;
			}
		}
	}

	int AreaDot=AreaList->GetPatternByte();
	if((double)DotCounter/(double)AreaDot>0.3){
		return true;
	}
	return false;
}

AutoAlignmentLibrary *AutoMaskingPIInPage::GetFirstAutoAlignmentLibrary()
{
	//ライブラリ情報を取得
	AlgorithmBase	*AutoAlignmentBasePointer=GetLayersBase()->GetAlgorithmBase("Basic","AutoAlignment");
	if(AutoAlignmentBasePointer==NULL){
		return NULL;
	}
	//個数取得
	CmdReqAutoAlignmentEnumLibs	CmdAlignEnum;
	AutoAlignmentBasePointer->TransmitDirectly(&CmdAlignEnum);

	AutoAlignmentLibrary	*Lib=dynamic_cast<AutoAlignmentLibrary *>(AutoAlignmentBasePointer->GetLibraryContainer()->CreateNew());
	if(Lib==NULL){
		return NULL;
	}
	IntClass *LibIDPoint=CmdAlignEnum.LibIDList.GetFirst();
	if(LibIDPoint!=NULL){
		int	LibID=LibIDPoint->GetValue();
		//ライブラリの中身をＩＤ番号から取得
		//ライブラリの読込コードが無くても仮想関数で読込できる
		AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,*Lib);
	}
	return Lib;
}

//パッド上を背景（スリット）と誤認識しないように、パッド抽出色と比較する
bool AutoMaskingPIInPage::ComparePickupPadColor(PureFlexAreaList *AreaList,AutoAlignmentLibrary *Lib,ImageBuffer *MImageList[])
{
	int DotCounter=0;
	BYTE *Brightness[3];
	int	Len=AreaList->GetFLineLen();
	for(int i=0;i<Len;i++){
		int x1=AreaList->GetFLineLeftX (i);
		int x2=AreaList->GetFLineRightX(i);
		int y =AreaList->GetFLineAbsY  (i);

		Brightness[0]=MImageList[0]->GetY(y);
		Brightness[1]=MImageList[1]->GetY(y);
		Brightness[2]=MImageList[2]->GetY(y);

		for(int x=x1;x<x2;x++){
			if(Lib->PickupColor.Calc(Brightness[0][x],Brightness[1][x],Brightness[2][x],0)==true){
				DotCounter++;
			}
		}
	}

	int AreaDot=AreaList->GetPatternByte();
	if((double)DotCounter/(double)AreaDot>0.2){
		return true;
	}
	return false;
}
*/

bool	AutoMaskingPIInPage::ExecuteInitialAfterEdit(ResultInPageRoot *Res ,EntryPointBase *pInspectionData)
{
	GetLayersBase()->AddMaxProcessing(4);
	GetLayersBase()->StepProcessing();

	int CurrentMasterCounter=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);
	if(CurrentMasterCounter==1 || CurrentMasterCounter==2 || CurrentMasterCounter==99999999){
		return true;
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

	AutoMaskingPIBase	*PBase=(AutoMaskingPIBase *)GetParentBase();
	for(AlgorithmLibraryList *a=PBase->AdoptedLib.GetFirst();a!=NULL;a=a->GetNext()){
		AutoMaskingPILibrary	Lib(GetLibraryContainer()->GetLibType(),GetLayersBase());
		GetParentBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,Lib);
		Lib.MakeMask(MasterImageList
					,TargetImageList
					,GetLayerNumb()
					,AutoMaskMap
					,XByte ,XLen ,YLen);
		break;
	}

	GetLayersBase()->StepProcessing();

	MatrixBuffCopy(MaskMap		,XByte,YLen
                 , (const BYTE **)AutoMaskMap	,XByte,YLen);
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeBitData(MaskMap,XLen,YLen);
	}

	GetLayersBase()->StepProcessing();

	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==false && ((AlgorithmLibraryListContainer *)(&((AutoMaskingPIItem *)a)->GetThresholdR()->SelAreaID))->GetFirst()==NULL)
			a->GetArea().MakeNotBitData(MaskMap,XLen,YLen);
	}

	GetLayersBase()->StepProcessing();

	AlgorithmInPagePI::ExecuteInitialAfterEdit(Res ,pInspectionData);

	return true;
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

BYTE	**AutoMaskingPIInPage::CreateMaskBitmapForMaskSide(int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	BYTE **Dst=MakeMatrixBuff((GetDotPerLine()+7)/8 ,GetMaxLines());
	GetItemBitmap(LibData->GetLibType(),LibData->GetLibID()
					 ,Dst,GetDotPerLine() ,GetMaxLines());
	return Dst;
}
BYTE	**AutoMaskingPIInPage::CreateMaskBitmapForMaskSide(int layer ,void *Anything)
{
	int	iXByte	=(GetDotPerLine()+7)/8 ;
	int	iYLen	=GetMaxLines();
	BYTE	**Map=MakeMatrixBuff(iXByte,iYLen);
	GetItemBitmap(Map ,iXByte,iXByte*8,iYLen);
	return Map;
}
bool	AutoMaskingPIInPage::CreateMaskVectorForMaskSide(VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything)
{
	return true;
}
bool	AutoMaskingPIInPage::CreateMaskVectorForMaskSide(VectorLineBase &MaskVector ,int layer ,void *Anything)
{
	return true;
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

	//基板なし画像の読み込み
	if(LoadTargetImage(PipeInNoPCBImagePath,localX1,localY1,localX2,localY2)==true){
	}
	else{
		//基板なし画像が読み込めなかった場合
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

	GetLayersBase()->ShowProcessingForm ();
	GetLayersBase()->AddMaxProcessing(GetPageNumb());
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
		GetLayersBase()->StepProcessing();
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

	GetLayersBase()->ShowProcessingForm ();
	GetLayersBase()->AddMaxProcessing(min(GetPageNumb(),iPageNumb));
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
		GetLayersBase()->StepProcessing();
	}
	GetLayersBase()->CloseProcessingForm ();
///	BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	return true;
}

//===========================================
AutoMaskingPIBase::AutoMaskingPIBase(void)
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

bool	AutoMaskingPIBase::ShowPasteCreateWithShape(QByteArray &templateData)
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
		GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
			,AListPacket->AList);
		return;
	}
	CmdGetAutoMaskingPILibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAutoMaskingPILibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		return;
	}
	CmdInsertAutoMaskingPILibraryPacket	*BInsLib=dynamic_cast<CmdInsertAutoMaskingPILibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(AutoMaskingPIVersion);
		GetLibraryContainer()->SaveNew(*BInsLib->Point);
		return;
	}
	CmdUpdateAutoMaskingPILibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAutoMaskingPILibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(AutoMaskingPIVersion);
		GetLibraryContainer()->Update(*BUpdLib->Point);
		return;
	}
	CmdLoadAutoMaskingPILibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAutoMaskingPILibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		return;
	}
	CmdCreateTempAutoMaskingPILibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAutoMaskingPILibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AutoMaskingPILibrary(GetLibType(),GetLayersBase());
		return;
	}
	CmdClearAutoMaskingPILibraryPacket	*CmdClearAutoMaskingPILibraryPacketVar=dynamic_cast<CmdClearAutoMaskingPILibraryPacket *>(packet);
	if(CmdClearAutoMaskingPILibraryPacketVar!=NULL){
		AutoMaskingPILibrary	*c=new AutoMaskingPILibrary(GetLibType(),GetLayersBase());
		*((AutoMaskingPILibrary *)CmdClearAutoMaskingPILibraryPacketVar->Point)=*c;
		delete	c;
		return;
	}
	CmdDeleteAutoMaskingPILibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAutoMaskingPILibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
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
bool	AutoMaskingPIBase::ExecuteInitialAfterEdit(ResultBaseForAlgorithmRoot *Res ,EntryPointBase *pInspectionData)
{
	SetAdopted();

	return AlgorithmBase::ExecuteInitialAfterEdit(Res ,pInspectionData);
}

void	AutoMaskingPIBase::SetAdopted(void)
{
	AdoptedLib.RemoveAll();
	AlgorithmLibraryListContainer	TmpLibContainer;
	GetLibraryContainer()->EnumLibrary(GetLibType(),TmpLibContainer);
	AutoMaskingPILibrary	*TmpLib=(AutoMaskingPILibrary *)GetLibraryContainer()->CreateNew();
	for(AlgorithmLibraryList *a=TmpLibContainer.GetFirst();a!=NULL;a=a->GetNext()){
		GetLibraryContainer()->GetLibrary(a->GetLibID() ,*TmpLib);
		if(TmpLib->DefaultMask==true){
			AdoptedLib.Add(GetLibraryContainer()->GetLibType(),*TmpLib);
		}
	}
	delete	TmpLib;
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
		SendBack->Data.resize(YCount*GetDotPerLine());
		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,L->GetTargetBuff().GetY(y),GetDotPerLine());
			Dest+=GetDotPerLine();
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
		int	XLen=min(iDotPerLine,GetDotPerLine());
		if((TopY+YCount>=localY1 && TopY<=localY2)){
			for(int y=TopY;y<TopY+YCount;y++){
				if(y<GetMaxLines()){
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
