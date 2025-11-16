/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1Item.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XEulerRingL1.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingL1Library.h"
#include "XImageProcess.h"
#include "swap.h"
#include <omp.h>
#include "XDisplayBitImage.h"
#include "XPropertyEulerRingL1Common.h"
#include "XAlgorithmDLL.h"

EulerRingL1Item::EulerRingL1Item(void)
{
	AVector=NULL;
	CenterBright		=0;
	CenterTargetBright	=0;
	MasterHoleDiameter	=0;

	BmpMap	=NULL;
	TmpMap	=NULL;
	MaskMap	=NULL;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	MapXPos=MapYPos=0;
	TestMode=false;
}

EulerRingL1Item::EulerRingL1Item(FlexArea &area)
:AlgorithmItemPLITemplate<EulerRingL1InLayer,EulerRingL1InPage,EulerRingL1Base>(area)
{
	AVector=NULL;
	CenterBright		=0;
	CenterTargetBright	=0;
	MasterHoleDiameter	=0;

	BmpMap	=NULL;
	TmpMap	=NULL;
	MaskMap	=NULL;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	MapXPos=MapYPos=0;
	TestMode=false;
}
EulerRingL1Item::~EulerRingL1Item(void)
{
	if(BmpMap!=NULL){
		DeleteMatrixBuff(BmpMap,YLen);
		BmpMap	=NULL;
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,YLen);
		TmpMap	=NULL;
	}
	if(MaskMap!=NULL){
		DeleteMatrixBuff(MaskMap,YLen);
		MaskMap	=NULL;
	}
	XLen	=0;
	XByte	=0;
	YLen	=0;
}

EulerRingL1Item &EulerRingL1Item::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(*((EulerRingL1Item *)&src));
	return *this;
}

void	EulerRingL1Item::CopyThreshold(EulerRingL1Item &src)
{
	GetThresholdW()->CopyFrom(*((EulerRingL1Threshold *)src.GetThresholdR()));
}

void	EulerRingL1Item::CopyThresholdOnly(EulerRingL1Item &src)
{
	GetThresholdW()->CopyFrom(*((EulerRingL1Threshold *)src.GetThresholdR()));
}

bool    EulerRingL1Item::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	if(::Save(file,MasterHoleDiameter)==false)
		return false;
	return true;
}
bool    EulerRingL1Item::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	if(GetLoadedVersion()<2){
		MasterHoleDiameter=GetArea().GetWidth();
	}
	else{
		if(::Load(file,MasterHoleDiameter)==false)
			return false;
	}
	return true;
}

void	EulerRingL1Item::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			bool	SavedModeEnableInRound	=GetThresholdR()->PointMove.ModeEnableInRound;
			CopyThresholdOnly(*((EulerRingL1Item *)Data));
			GetThresholdW()->PointMove.ModeEnableInRound	=SavedModeEnableInRound;
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((EulerRingL1Item *)Data)->GetLibID()){
			bool	SavedModeEnableInRound	=GetThresholdR()->PointMove.ModeEnableInRound;
			CopyThresholdOnly(*((EulerRingL1Item *)Data));
			GetThresholdW()->PointMove.ModeEnableInRound	=SavedModeEnableInRound;
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((EulerRingL1Item *)Data)->GetLibID()){
			EulerRingL1InLayer	*Ly=dynamic_cast<EulerRingL1InLayer *>(GetParentInLayer());
			UndoElement<EulerRingL1InLayer>	*UPointer=new UndoElement<EulerRingL1InLayer>(Ly,&EulerRingL1InLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			EulerRingL1Item *src=(EulerRingL1Item *)Data;
			SetItemName(src->GetItemName());
		}
	}
}
void	EulerRingL1Item::SetThresholdFromCommon(SetThresholdEulerRingL1Info *Info)
{
	//if(Info->BBrightL>=0)
	//	GetThresholdW()->DarkWidth		=Info->BBrightL;
	//if(Info->BBrightH>=0)
	//	GetThresholdW()->LightWidth		=Info->BBrightH;

	//if(Info->NGSize1>=0)
	//	GetThresholdW()->MinHoleDiameter=Info->NGSize1;
	//if(Info->NGSize2>=0)
	//	GetThresholdW()->MaxHoleDiameter=Info->NGSize2;

	if(Info->Shift>=0)
		GetThresholdW()->MaxShiftHole	=Info->Shift;
}

int		EulerRingL1Item::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}
void	EulerRingL1Item::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	EulerRingL1Item	*ASrc=dynamic_cast<EulerRingL1Item *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((EulerRingL1Base *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		CenterBright		=ASrc->CenterBright;
		CenterTargetBright	=ASrc->CenterTargetBright;
		MasterHoleDiameter	=ASrc->MasterHoleDiameter;
	}
}

static	int	Mergin=8;

ExeResult	EulerRingL1Item::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true
	|| (GetMasterBuff().IsNull()==false && GetMasterBuff().IsChanged()==true)){
		EulerRingL1InLayer	*P=(EulerRingL1InLayer *)GetParentInLayer();
		const EulerRingL1Threshold	*RThr=GetThresholdR();
		if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false){
			if(GetMasterBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
				CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
			}
			else if(GetTargetBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
				CenterBright=CalcCenterBright(GetTargetBuff(),0,0);
			}
			CenterTargetBright=CenterBright;
		}
		MapXPos = GetArea().GetMinX()  -Mergin  -RThr->ConnectLen;
		MapYPos = GetArea().GetMinY()  -Mergin  -RThr->ConnectLen;
		int	iXLen=GetArea().GetWidth() +Mergin*2+RThr->ConnectLen*2;
		int	iYLen=GetArea().GetHeight()+Mergin*2+RThr->ConnectLen*2;

		if(iXLen!=XLen || iYLen!=YLen || BmpMap==NULL || TmpMap==NULL || MaskMap==NULL){
			if(BmpMap!=NULL){
				DeleteMatrixBuff(BmpMap,YLen);
				BmpMap	=NULL;
			}
			if(TmpMap!=NULL){
				DeleteMatrixBuff(TmpMap,YLen);
				TmpMap	=NULL;
			}
			if(MaskMap!=NULL){
				DeleteMatrixBuff(MaskMap,YLen);
				MaskMap	=NULL;
			}
			XLen	=iXLen;
			YLen	=iYLen;
			XByte=(XLen+7)/8;
			BmpMap =MakeMatrixBuff(XByte,YLen);
			TmpMap =MakeMatrixBuff(XByte,YLen);
			MaskMap=MakeMatrixBuff(XByte,YLen);
		}

		GetArea().GetCenter(MasterCx,MasterCy);

		MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
		MatrixBuffClear	(MaskMap ,0 ,XByte,YLen);
		TestMode=false;
		if(Ret!=_ER_true){
			return Ret;
		}
	}
	return _ER_true;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	EulerRingL1Item::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
	MatrixBuffClear	(MaskMap ,0 ,XByte,YLen);
	return _ER_true;
}

ExeResult	EulerRingL1Item::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPLI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

	if(GetID()==DbgID)
		DbgNumer++;

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
	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;
	const EulerRingL1Threshold	*RThr=GetThresholdR();
	int	Dx,Dy;
	Search(mx,my,Dx,Dy);
	ExeResult	Ret=ExecutePreProcessingInside(ThreadNo,Res ,mx+Dx ,my+Dy,mx,my);
	if(Res->IsOk()==true || RThr->SearchDot==0)
		return Ret;

	/*
	for(int dy=-RThr->SearchDot;dy<=RThr->SearchDot;dy+=RThr->SearchDot){
		for(int dx=-RThr->SearchDot;dx<=RThr->SearchDot;dx+=RThr->SearchDot){
			Res->ClearPosList();
			Ret=ExecutePreProcessingInside(ThreadNo,Res ,mx+dx ,my+dy);
			if(Res->IsOk()==true)
				return Ret;
		}
	}
	for(int dy=-RThr->SearchDot;dy<=RThr->SearchDot;dy+=2){
		for(int dx=-RThr->SearchDot;dx<=RThr->SearchDot;dx+=2){
			Res->ClearPosList();
			Ret=ExecutePreProcessingInside(ThreadNo,Res ,mx+dx ,my+dy);
			if(Res->IsOk()==true)
				return Ret;
		}
	}
	*/
	return Ret;
}

ExeResult	EulerRingL1Item::ExecutePreProcessingInside(int ThreadNo,ResultInItemRoot *Res ,int mx ,int my ,int AlignedMx ,int AlignedMy)
{
	PureFlexAreaListContainer FPack;
	ExeResult	Ret;
	PureFlexAreaList *HoleF=NULL;
	const EulerRingL1Threshold	*RThr=GetThresholdR();
	if(RThr->SearchDot>0){
		HoleF=ExecutePreProcessingInsise	(Res ,mx ,my ,AlignedMx,AlignedMy ,false,FPack,Ret);
		if(Ret==_ER_ReqRetryLater)
			return Ret;

		int	wx=0;
		int	wy=0;
		if(HoleF!=NULL
		&& (ResultHoleDiameter<RThr->MinHoleDiameter || RThr->MaxHoleDiameter<ResultHoleDiameter
		  || HoleF->GetMinX()<3 || HoleF->GetMinY()<3 || HoleF->GetMaxX()>=(XLen-3) || HoleF->GetMaxY()>=(YLen-3))){
			int	W=GetArea().GetWidth()/4;
			int	H=GetArea().GetHeight()/4;
			double	vx=0;
			double	vy=0;
			if(HoleF->GetMinX()<3)
				vx-=W;
			if(HoleF->GetMinY()<3)
				vy-=H;
			if(HoleF->GetMaxX()>=(XLen-3))
				vx+=W;
			if(HoleF->GetMaxY()>=(YLen-3))
				vy+=H;

			double	v=hypot(vx,vy);
			MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
			if(v>RThr->SearchDot){
				vx/=v;
				vy/=v;
				wx=RThr->SearchDot*vx;
				wy=RThr->SearchDot*vy;
			}
			else{
				wx=vx;
				wy=vy;
			}
			HoleF=ExecutePreProcessingInsise	(Res ,mx+wx ,my+wy ,AlignedMx,AlignedMy ,false ,FPack,Ret);
			if(Ret==_ER_ReqRetryLater){
				return Ret;
			}
		}
		if(HoleF!=NULL){
			int	cx,cy;
			HoleF->GetCenter(cx,cy);
			//cx+=HoleShiftX;
			//cy+=HoleShiftY;
			FPack.RemoveAll();
			cx+=MapXPos+mx+wx;
			cy+=MapYPos+my+wy;
			int	gx,gy;
			GetCenter(gx,gy);
			int	ex=gx+mx;
			int	ey=gy+my;
			double	vx=cx-ex;
			double	vy=cy-ey;
			double	v=hypot(vx,vy);
			MatrixBuffClear	(BmpMap  ,0 ,XByte,YLen);
			if(v>RThr->SearchDot){
				vx/=v;
				vy/=v;
				int	wx=RThr->SearchDot*vx;
				int	wy=RThr->SearchDot*vy;
				mx+=wx;
				my+=wy;
				HoleF=ExecutePreProcessingInsise	(Res ,mx ,my ,AlignedMx,AlignedMy ,true,FPack,Ret);
				if(Ret==_ER_ReqRetryLater)
					return Ret;
			}
			else{
				mx+=vx;
				my+=vy;
				HoleF=ExecutePreProcessingInsise	(Res ,mx ,my ,AlignedMx,AlignedMy ,true,FPack,Ret);
				if(Ret==_ER_ReqRetryLater)
					return Ret;
			}
		}
	}
	else{
		HoleF=ExecutePreProcessingInsise	(Res ,mx ,my ,AlignedMx,AlignedMy ,true,FPack,Ret);
		if(Ret==_ER_ReqRetryLater)
			return Ret;
	}

	if(HoleF!=NULL){
		GetThresholdW()->AddHist(Hist_EulerRingL1_HoleDiameter	,ResultHoleDiameter	);
		GetThresholdW()->AddHist(Hist_EulerRingL1_HoleShift		,ResultHoleShift	);
		double	HoleBrightness=HoleF->GetAverage(GetTargetBuff(),MapXPos+mx,MapYPos+my);
		GetThresholdW()->AddHist(Hist_EulerRingL1_HoleCenterBrightness	,HoleBrightness	);

		if(RThr->PointMove.ModeEnableInRound==true
		&& RThr->PointMove.ModeEnableHoleCheck==true
		&& RThr->MaxShiftHole<ResultHoleShift){
			ResultPosList	*f=new ResultPosList(MasterCx,MasterCy);
			f->Rx=0;
			f->Ry=0;
			f->result=0x10001;
			f->SetResult1(ResultHoleShift);
			f->SetResult2(0);
			f->NGShape.SuckFrom(*HoleF);
			f->NGShape.MoveToNoClip(MapXPos,MapYPos);
			Res->AddPosList(f);
			Res->SetError(5);
			FinishCalc();
			return _ER_true;
		}
		int	iMinHoleDiameter=Clipping((int)MasterHoleDiameter-RThr->MinHoleDiameter,0,99999999);
		int	iMaxHoleDiameter=Clipping((int)MasterHoleDiameter+RThr->MaxHoleDiameter,0,99999999);
		if(RThr->PointMove.ModeEnableInRound==true
		&& RThr->PointMove.ModeEnableHoleCheck==true 
		&& (ResultHoleDiameter<iMinHoleDiameter || iMaxHoleDiameter<ResultHoleDiameter)){
			ResultPosList	*f=new ResultPosList(MasterCx,MasterCy);
			f->Rx=0;
			f->Ry=0;
			f->result=0x10002;
			f->SetResult1(ResultHoleDiameter);
			f->SetResult2(0);
			f->NGShape.SuckFrom(*HoleF);
			f->NGShape.MoveToNoClip(MapXPos,MapYPos);
			Res->AddPosList(f);
			Res->SetError(4);
			FinishCalc();
			return _ER_true;
		}
	}
	else{
		if(RThr->PointMove.ModeEnableInRound==true 
		&& RThr->PointMove.ModeEnableHoleCheck==true 
		&& 0<RThr->MinHoleDiameter){
			ResultPosList	*f=new ResultPosList(MasterCx,MasterCy);
			f->Rx=0;
			f->Ry=0;
			f->result=0x10005;
			f->SetResult1(ResultHoleDiameter);
			f->SetResult2(0);
			Res->AddPosList(f);
			Res->SetError(6);
			FinishCalc();
			return _ER_true;
		}
	}
	if(RThr->PointMove.ModeEnabled==true){
		if(RThr->PointMove.ModeEnableInRound==true 
		&& RThr->PointMove.ModeEnableOpenRingCheck==true
		&& (HoleF->GetMinX()<3 || HoleF->GetMinY()<3 || HoleF->GetMaxX()>=(XLen-3) || HoleF->GetMaxY()>=(YLen-3))){
			PureFlexAreaListContainer MPack;
			PickupFlexArea(BmpMap ,XByte ,XLen,YLen ,MPack);
			int	MaxDots=0;
			PureFlexAreaList *MaxT=NULL;
			for(PureFlexAreaList *t=MPack.GetFirst();t!=NULL;t=t->GetNext()){
				if(MaxDots<t->GetPatternByte()){
					MaxDots=t->GetPatternByte();
					MaxT=t;
				}
			}
			ResultPosList	*f=new ResultPosList(MasterCx,MasterCy);
			f->Rx=0;
			f->Ry=0;
			f->result=0x10003;
			f->SetResult1(0);
			f->SetResult2(0);
			if(MaxT!=NULL){
				f->NGShape.SuckFrom(*MaxT);
				f->NGShape.MoveToNoClip(MapXPos+mx,MapYPos+my);
			}
			Res->AddPosList(f);
			Res->SetError(3);
			FinishCalc();
			return _ER_true;
		}
	}

	Res->SetError(1);
	FinishCalc();
	return _ER_true;
}

PureFlexAreaList *EulerRingL1Item::ExecutePreProcessingInsise	(ResultInItemRoot *Res ,int mx ,int my,int AlignedMx ,int AlignedMy
														,bool ModeMakeHoleMask
														,PureFlexAreaListContainer &FPack
														,ExeResult &Ret)
{
	Res->ClearPosList();
	Res->SetAlignedXY(mx,my);

	const EulerRingL1Threshold	*RThr=GetThresholdR();
	int	BrightWidthL=RThr->DarkWidth;
	int	BrightWidthH=RThr->LightWidth;
	if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false){
		if(GetTargetBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
			if(RThr->HoleBrightnessAsReference<0){
				CenterTargetBright=CalcCenterBright(GetTargetBuff(),mx,my);
				if(RThr->PointMove.ModeAbsoluteBright==false){
					int	D=CenterTargetBright-CenterBright;
					if(D<0){
						if(-D> RThr->AdjustBlack){
							D=-RThr->AdjustBlack;
						}
					}
					else if(D>0){
						if(D> RThr->AdjustWhite){
							D=RThr->AdjustWhite;
						}
					}
					BrightWidthL=(CenterBright+D)-RThr->DarkWidth;
					BrightWidthH=(CenterBright+D)+RThr->LightWidth;
				}
			}
			else{
				CalcRingThreshold(GetTargetBuff(),mx,my ,RThr->HoleBrightnessAsReference,BrightWidthL,BrightWidthH);
			}
		}
	}

	if(CanBeProcessing()==false){
		Ret=_ER_ReqRetryLater;
		return NULL;
	}

	double	CenterRingAdd		=0;
	int		RingBrightnessLow	=9999;
	int		RingBrightnessHigh	=0;
	int		RingPixNumb			=0;

	for(int y=0;y<YLen;y++){
		int	Y=y+MapYPos+my;
		if(Y<0 || GetMaxLines()<=Y)
			continue;
		BYTE	*s=GetTargetBuff().GetY(Y);
		BYTE	*d=BmpMap[y];
		for(int x=0;x<XLen;x++){
			int	X=x+MapXPos+mx;
			if(X<0 || GetDotPerLine()<=X)
				continue;
			int	c=s[X];
			if(BrightWidthL<=c && c<=BrightWidthH){
				SetBmpBitOnY1(d,x);
				CenterRingAdd	+=c;
				if(c<RingBrightnessLow)
					RingBrightnessLow=c;
				if(RingBrightnessHigh<c)
					RingBrightnessHigh=c;
				RingPixNumb++;
			}
		}
	}
	double	AverageRingBrightness=0;
	if(RingPixNumb!=0){
		AverageRingBrightness=CenterRingAdd/RingPixNumb;
	}
	GetThresholdW()->AddHist(Hist_EulerRingL1_RingCenterBrightness	,(int)AverageRingBrightness	);
	GetThresholdW()->AddHist(Hist_EulerRingL1_RingLowBrightness		,(int)RingBrightnessLow		);
	GetThresholdW()->AddHist(Hist_EulerRingL1_RingHighBrightness	,(int)RingBrightnessHigh	);

	PureFlexAreaList *HoleF=NULL;
	if(BmpMap!=NULL){
		if(RThr->ConnectLen>0){	
			GetLayersBase()->ThinAreaN(BmpMap
						,TmpMap
						,XByte, YLen
						,RThr->ConnectLen);
			GetLayersBase()->FatAreaN(BmpMap
						,TmpMap
						,XByte, YLen
						,2*RThr->ConnectLen);
		}
		else if(RThr->ConnectLen<0){
			GetLayersBase()->FatAreaN(BmpMap
						,TmpMap
						,XByte, YLen
						,-RThr->ConnectLen);
			GetLayersBase()->ThinAreaN(BmpMap
						,TmpMap
						,XByte, YLen
						,-2*RThr->ConnectLen);
		}

		if(TestMode==true){
			PureFlexAreaListContainer RingAreaPack;
			PickupFlexArea(BmpMap ,XByte ,XLen,YLen ,RingAreaPack);
			ResultPosList	*RingArea=new ResultPosList(MasterCx,MasterCy);
			RingArea->Rx=0;
			RingArea->Ry=0;
			RingArea->result=0x1;
			RingArea->SetResult1(0);
			RingArea->SetResult2(0);
			for(PureFlexAreaList *f=RingAreaPack.GetFirst();f!=NULL;f=f->GetNext()){
				RingArea->NGShape+=*f;
			}
			RingArea->NGShape.MoveToNoClip(MapXPos,MapYPos);
			Res->AddPosList(RingArea);
		}

		MatrixBuffNotCopy	(TmpMap	,XByte, YLen
							,(const BYTE **)BmpMap,XByte, YLen);
		PickupFlexArea(TmpMap ,XByte ,XLen,YLen ,FPack);
		
		if(FPack.GetCount()>1){
			int	Ex=XLen>>1;
			int	Ey=YLen>>1;
			for(int L=0;L<Ex;L+=2){
				int	ky=Ey-L;
				int	kx;
				for(kx=Ex-L;kx<=Ex+L;kx+=2){
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->IsInclude(kx,ky)==true){
							HoleF=f;
							goto	PBreak;
						}
					}
				}
				kx=Ex+L;
				for(ky=Ey-L;ky<Ey+L;ky+=2){
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->IsInclude(kx,ky)==true){
							HoleF=f;
							goto	PBreak;
						}
					}
				}
				ky=Ey+L;
				for(kx=Ex+L;kx>Ex-L;kx-=2){
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->IsInclude(kx,ky)==true){
							HoleF=f;
							goto	PBreak;
						}
					}
				}
				kx=Ex-L;
				for(ky=Ey+L;ky>Ey-L;ky-=2){
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->IsInclude(kx,ky)==true){
							HoleF=f;
							goto	PBreak;
						}
					}
				}
			}
			PBreak:;
		}
		else{
			HoleF=FPack.GetFirst();
		}
		if(HoleF!=NULL && ModeMakeHoleMask==true){
			if(RThr->PointMove.ModeMakeDynamicMask==true){
				MakeHoleMask(HoleF,mx,my);
			}
			if(TestMode==true){
				ResultPosList	*HoleArea=new ResultPosList(MasterCx,MasterCy);
				HoleArea->Rx=0;
				HoleArea->Ry=0;
				HoleArea->result=0x2;
				HoleArea->SetResult1(0);
				HoleArea->SetResult2(0);
				HoleArea->NGShape=*HoleF;
				HoleArea->NGShape.MoveToNoClip(MapXPos,MapYPos);
				Res->AddPosList(HoleArea);

				PureFlexAreaListContainer HoleMaskAreaPack;
				PickupFlexArea(MaskMap ,XByte ,XLen,YLen ,HoleMaskAreaPack);
				PureFlexAreaList	*k=HoleMaskAreaPack.GetFirst();
				if(k!=NULL){
					ResultPosList	*HoleMaskArea=new ResultPosList(MasterCx,MasterCy);
					HoleMaskArea->Rx=0;
					HoleMaskArea->Ry=0;
					HoleMaskArea->result=0x3;
					HoleMaskArea->SetResult1(0);
					HoleMaskArea->SetResult2(0);
					HoleMaskArea->NGShape.SuckFrom(*k);
					HoleMaskArea->NGShape.MoveToNoClip(MapXPos-HoleShiftX,MapYPos-HoleShiftY);
					Res->AddPosList(HoleMaskArea);
				}
			}
		}
		if(HoleF!=NULL){
			int	Ex,Ey;
			GetCenter(Ex,Ey);
			Ex+=AlignedMx;
			Ey+=AlignedMy;
			int	Cx,Cy;
			HoleF->GetCenter(Cx,Cy);
			Cx+=MapXPos+mx;
			Cy+=MapYPos+my;
			ResultHoleShift=hypot(Ex-Cx,Ey-Cy);
			ResultHoleDiameter=(HoleF->GetWidth()+HoleF->GetHeight()+1)/2.0;
		}
	}
	Ret=_ER_true;
	return HoleF;
}


void	EulerRingL1Item::MakeHoleMask(FlexArea *HoleF,int mx,int my)
{
	const EulerRingL1Threshold	*RThr=GetThresholdR();
	EulerRingL1InPage	*EPage=dynamic_cast<EulerRingL1InPage *>(GetParentInPage());
	if(EPage!=NULL){
		int	HoleMinX=HoleF->GetMinX();
		int	HoleMinY=HoleF->GetMinY();
		HoleShiftX=-HoleMinX+abs(RThr->ExpandForDynamicMask)+Mergin;
		HoleShiftY=-HoleMinY+abs(RThr->ExpandForDynamicMask)+Mergin;
		HoleF->MakeBitData(MaskMap ,HoleShiftX,HoleShiftY,XLen ,YLen);
		if(RThr->ExpandForDynamicMask>0){
			GetLayersBase()->FatAreaN(MaskMap
					,TmpMap
					,XByte ,YLen
					,RThr->ExpandForDynamicMask
					,NULL,false);
		}
		else if(RThr->ExpandForDynamicMask<0){
			GetLayersBase()->ThinAreaN(MaskMap
					,TmpMap
					,XByte ,YLen
					,-RThr->ExpandForDynamicMask
					,NULL,false);
		}
		BYTE	**DynamicMaskingMapInPage=GetDataInPage()->GetDynamicMaskingMap();
		for(int y=0;y<YLen;y++){
			int	Y=y+MapYPos+my-HoleShiftY;
			if(0<=Y && Y<GetMaxLines()){
				BYTE	*s=MaskMap[y];
				BYTE	*d=DynamicMaskingMapInPage[Y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x+MapXPos+mx-HoleShiftX;
						if(0<=X && X<GetDotPerLine()){
							SetBmpBitOnY1(d,X);
						}
					}
				}
			}
		}
	}	
}

void	EulerRingL1Item::CopyArea(EulerRingL1Item &src)
{
	SetArea(src.GetArea());
}

void	EulerRingL1Item::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	EulerRingL1DrawAttr	*BAttr=dynamic_cast<EulerRingL1DrawAttr *>(Attr);
	if(BAttr!=NULL){
		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		BAttr->NormalColor=SavedColor;
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	EulerRingL1Item::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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
			}

			QColor HoleCol(130,130,0,180);
			DrawBitImageOr(IData, (const BYTE **)BmpMap ,XLen ,XByte ,YLen
						,MovX ,MovY ,ZoomRate
						,-(MapXPos+Res->GetAlignedX()),-(MapYPos+Res->GetAlignedY())
						,HoleCol);

			QColor MaskCol(0,100,0,180);
			DrawBitImageOr(IData, (const BYTE **)MaskMap ,XLen ,XByte ,YLen
						,MovX-HoleShiftX ,MovY-HoleShiftY ,ZoomRate
						,-(MapXPos+Res->GetAlignedX()),-(MapYPos+Res->GetAlignedY())
						,MaskCol);

			PData.setPen(Qt::yellow);

			int	Vx =(MasterCx + MovX +Res->GetTotalShiftedX())*ZoomRate;
			int	Vy1=(MasterCy-YLen/2-10+ MovY +Res->GetTotalShiftedY())*ZoomRate;
			int	Vy2=(MasterCy+YLen/2+10+ MovY +Res->GetTotalShiftedY())*ZoomRate;
			int	Hx1=(MasterCx-XLen/2-10+ MovX +Res->GetTotalShiftedX())*ZoomRate;
			int	Hx2=(MasterCx+XLen/2+10+ MovX +Res->GetTotalShiftedX())*ZoomRate;
			int	Hy =(MasterCy + MovY +Res->GetTotalShiftedY())*ZoomRate;
			PData.drawLine(Vx,Vy1,Vx,Vy2);
			PData.drawLine(Hx1,Hy,Hx2,Hy);
		}
	}
}

//===========================================================================================

const	int	BLKMergin	=2;

int	EulerRingL1Item::CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	int	YSep;
	int	XSep;
	FlexArea	&A=GetArea();
	if(A.GetFLineLen()<20)
		YSep=1;
	else if(A.GetFLineLen()<40)
		YSep=2;
	else if(A.GetFLineLen()<60)
		YSep=3;
	else if(A.GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;

	for(int i=0;i<A.GetFLineLen();i+=YSep){
		int	y =A.GetFLineAbsY  (i)+my;
		if(y<BLKMergin)
			continue;
		if(y>=MaxLines-BLKMergin)
			break;
		int	x1=A.GetFLineLeftX (i)+mx;
		int	x2=A.GetFLineRightX(i)+mx;
		if(x1<BLKMergin)
			x1=BLKMergin;
		if(x2>=DotPerLine-BLKMergin)
			x2=DotPerLine-BLKMergin;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		src=IBuff.GetY(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			BTable[*(src+x)]++;
		}
	}

	int	N=0;
	for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
		N+=BTable[i];
	}
	int	DiscardDotL=N/2;
	int	DiscardDotH=N/4;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDotL){
			break;
		}
	}
	D=0;
	for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
		D+=BTable[HLevel];
		if(D>DiscardDotH){
			break;
		}
	}
	N=0;
	double	DSum=0;
	for(int i=LLevel;i<=HLevel;i++){
		N+=BTable[i];
		DSum+=BTable[i]*i;
	}
	if(N!=0){
		return (WORD)(DSum/N);
	}
	return 0;
}
void	EulerRingL1Item::CalcRingThreshold(ImageBuffer &IBuff ,int mx,int my ,int HoleBrightnessAsReference ,int &BrightWidthL,int &BrightWidthH)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	int	YSep;
	int	XSep;
	FlexArea	&A=GetArea();
	if(A.GetFLineLen()<20)
		YSep=1;
	else if(A.GetFLineLen()<40)
		YSep=2;
	else if(A.GetFLineLen()<60)
		YSep=3;
	else if(A.GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;

	for(int i=0;i<A.GetFLineLen();i+=YSep){
		int	y =A.GetFLineAbsY  (i)+my;
		if(y<BLKMergin)
			continue;
		if(y>=MaxLines-BLKMergin)
			break;
		int	x1=A.GetFLineLeftX (i)+mx;
		int	x2=A.GetFLineRightX(i)+mx;
		if(x1<BLKMergin)
			x1=BLKMergin;
		if(x2>=DotPerLine-BLKMergin)
			x2=DotPerLine-BLKMergin;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		src=IBuff.GetY(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			BTable[*(src+x)]++;
		}
	}

	int		ATable[256];
	memset(ATable,0,sizeof(ATable));
	for(int i=2;i<sizeof(BTable)/sizeof(BTable[0])-2;i++){
		int	d=0;
		for(int j=i-2;j<=2;j++){
			d+=BTable[i+j];
		}
		ATable[i]=d;
	}

	int	N=0;
	for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
		N+=ATable[i];
	}

	int	MaxN=0;
	int	MaxI=0;
	for(int i=HoleBrightnessAsReference+5;i<256;i++){
		if(BTable[i]>MaxN){
			MaxN=ATable[i];
			MaxI=i;
		}
	}
	int	MidC=(MaxI+HoleBrightnessAsReference+5)/2;
	int	MinD=99999999;
	int	MinI=0;
	for(int i=HoleBrightnessAsReference+5;i<=MidC;i++){
		if(ATable[i]<MinD){
			MinD=ATable[i];
			MinI=i;
		}
	}
	BrightWidthL=MinI;
	BrightWidthH=256;
}

//===========================================================================================

struct	RearchResultStruct
{
	int	dx,dy;
	double	D;
};

static	int	SortDimFunc(const void *a ,const void *b)
{
	struct	RearchResultStruct	*pa=(struct	RearchResultStruct *)a;
	struct	RearchResultStruct	*pb=(struct	RearchResultStruct *)b;

	if(pa->D<pb->D)
		return 1;
	if(pa->D>pb->D)
		return -1;
	return 0;
}

double	EulerRingL1Item::CalcSearchUpper(ImageBuffer &TBuff ,int cx,int cy)
{
	BYTE	CBuff[8];
	CBuff[0]=TBuff.GetY(cy-4)[cx];
	CBuff[1]=TBuff.GetY(cy-3)[cx];
	CBuff[2]=TBuff.GetY(cy-2)[cx];
	CBuff[3]=TBuff.GetY(cy-1)[cx];
	CBuff[4]=TBuff.GetY(cy  )[cx];
	CBuff[5]=TBuff.GetY(cy+1)[cx];
	CBuff[6]=TBuff.GetY(cy+2)[cx];
	CBuff[7]=TBuff.GetY(cy+3)[cx];

	int	AA=8;
	int	A =0;
	BYTE	LowD=255;
	BYTE	HighD=0;
	short	B=0;
	int		BB=0;
	for(int i=0;i<8;i++){
		BYTE	c=CBuff[i];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		B+=c;
		BB+=c*c;
	}
	int	AB =+CBuff[0]
			+CBuff[1]
			+CBuff[2]
			+CBuff[3]
			-CBuff[4]
			-CBuff[5]
			-CBuff[6]
			-CBuff[7];

	double	DivL=1.0/8.0;
	double	AvrD=((double)B)*DivL;
	double	K=AB;
	double	M=AA*(BB-8.0*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return (HighD-LowD)*Cff;
}

double	EulerRingL1Item::CalcSearchLeft(ImageBuffer &TBuff ,int cx,int cy)
{
	BYTE	*CBuff=&TBuff.GetY(cy)[cx-4];

	int	AA=8;
	int	A =0;
	BYTE	LowD=255;
	BYTE	HighD=0;
	short	B=0;
	int		BB=0;
	for(int i=0;i<8;i++){
		BYTE	c=CBuff[i];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		B+=c;
		BB+=c*c;
	}
	int	AB =+CBuff[0]
			+CBuff[1]
			+CBuff[2]
			+CBuff[3]
			-CBuff[4]
			-CBuff[5]
			-CBuff[6]
			-CBuff[7];

	double	DivL=1.0/8.0;
	double	AvrD=((double)B)*DivL;
	double	K=AB;
	double	M=AA*(BB-8.0*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return (HighD-LowD)*Cff;
}

double	EulerRingL1Item::CalcSearchRight(ImageBuffer &TBuff ,int cx,int cy)
{
	BYTE	*CBuff=&TBuff.GetY(cy)[cx-4];

	int	AA=8;
	int	A =0;
	BYTE	LowD=255;
	BYTE	HighD=0;
	short	B=0;
	int		BB=0;
	for(int i=0;i<8;i++){
		BYTE	c=CBuff[i];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		B+=c;
		BB+=c*c;
	}
	int	AB =-CBuff[0]
			-CBuff[1]
			-CBuff[2]
			-CBuff[3]
			+CBuff[4]
			+CBuff[5]
			+CBuff[6]
			+CBuff[7];

	double	DivL=1.0/8.0;
	double	AvrD=((double)B)*DivL;
	double	K=AB;
	double	M=AA*(BB-8.0*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return (HighD-LowD)*Cff;
}

double	EulerRingL1Item::CalcSearchLower(ImageBuffer &TBuff ,int cx,int cy)
{
	BYTE	CBuff[8];
	CBuff[0]=TBuff.GetY(cy-4)[cx];
	CBuff[1]=TBuff.GetY(cy-3)[cx];
	CBuff[2]=TBuff.GetY(cy-2)[cx];
	CBuff[3]=TBuff.GetY(cy-1)[cx];
	CBuff[4]=TBuff.GetY(cy  )[cx];
	CBuff[5]=TBuff.GetY(cy+1)[cx];
	CBuff[6]=TBuff.GetY(cy+2)[cx];
	CBuff[7]=TBuff.GetY(cy+3)[cx];

	int	AA=8;
	int	A =0;
	BYTE	LowD=255;
	BYTE	HighD=0;
	short	B=0;
	int		BB=0;
	for(int i=0;i<8;i++){
		BYTE	c=CBuff[i];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		B+=c;
		BB+=c*c;
	}
	int	AB =-CBuff[0]
			-CBuff[1]
			-CBuff[2]
			-CBuff[3]
			+CBuff[4]
			+CBuff[5]
			+CBuff[6]
			+CBuff[7];

	double	DivL=1.0/8.0;
	double	AvrD=((double)B)*DivL;
	double	K=AB;
	double	M=AA*(BB-8.0*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return (HighD-LowD)*Cff;
}


struct	RearchResultLineStruct
{
	int	dx1,dy1;
	double	D1;
	int	dx2,dy2;
	double	D2;
};

static	int	SortHVDimFunc(const void *a ,const void *b)
{
	struct	RearchResultLineStruct	*pa=(struct	RearchResultLineStruct *)a;
	struct	RearchResultLineStruct	*pb=(struct	RearchResultLineStruct *)b;

	double	AD=pa->D1*pa->D2;
	double	BD=pb->D1*pb->D2;
	if(AD<BD)
		return 1;
	if(AD>BD)
		return -1;
	return 0;
}

void	CalcOnCircle(ImageBuffer &TBuff,int cx,int cy,int Rx ,int Ry ,double &Avr ,double &V)
{
	int	RxSin45=ceil(Rx*0.70710678118654752440084436210485);
	int	RySin45=ceil(Ry*0.70710678118654752440084436210485);

	int	SBuff[8];
	SBuff[0]=0;
	SBuff[1]=0;
	SBuff[2]=0;
	SBuff[3]=0;
	SBuff[4]=0;
	SBuff[5]=0;
	SBuff[6]=0;
	SBuff[7]=0;

	double	RRx=1.0/Rx;
	for(int x=0;x<=RxSin45;x++){
		int	y=Ry*sqrt((double)(1.0-x*x*RRx*RRx));
		BYTE	*D1=TBuff.GetY(y+cy);
		SBuff[0]+=D1[x+cx];
		SBuff[1]+=D1[-x+cx];
		BYTE	*D2=TBuff.GetY(-y+cy);
		SBuff[2]+=D2[x+cx];
		SBuff[3]+=D2[-x+cx];
	}
	double	RRy=1.0/Ry;
	for(int y=0;y<=RySin45;y++){
		int	x=Rx*sqrt((double)(1.0-y*y*RRy*RRy));
		BYTE	*D1=TBuff.GetY(y+cy);
		SBuff[4]+=D1[x+cx];
		SBuff[5]+=D1[-x+cx];
		BYTE	*D2=TBuff.GetY(-y+cy);
		SBuff[6]+=D2[x+cx];
		SBuff[7]+=D2[-x+cx];
	}
	Avr=0;
	double	RxSin45R=1.0/RxSin45;
	double	RySin45R=1.0/RySin45;
	SBuff[0]=SBuff[0]*RxSin45R;
	SBuff[1]=SBuff[1]*RxSin45R;
	SBuff[2]=SBuff[2]*RxSin45R;
	SBuff[3]=SBuff[3]*RxSin45R;
	SBuff[4]=SBuff[4]*RySin45R;
	SBuff[5]=SBuff[5]*RySin45R;
	SBuff[6]=SBuff[6]*RySin45R;
	SBuff[7]=SBuff[7]*RySin45R;
	for(int i=0;i<8;i++){
		Avr+=SBuff[i];
	}
	Avr/=8.0;
	V=0;
	for(int i=0;i<8;i++){
		V+=(SBuff[i]-Avr)*(SBuff[i]-Avr);
	}
}

bool	EulerRingL1Item::MatchDetail(ImageBuffer &TBuff,int cx,int cy,int Rx ,int Ry ,double &Rate)
{
	double HAvr ,HV;
	if(Rx-2<2 || Ry-2<2)
		return false;
	CalcOnCircle(TBuff, cx, cy, Rx-2,Ry-2 ,HAvr ,HV);
	double PAvr ,PV;
	CalcOnCircle(TBuff, cx, cy, Rx+2 ,Ry+2 ,PAvr ,PV);

	if(HV==0.0)
		return false;
	if(PV==0.0)
		return false;
	Rate=(PAvr-HAvr)*(PAvr-HAvr)*(PAvr-HAvr)/(HV*PV*PV);
	return true;
}


void	EulerRingL1Item::Search(int mx ,int my ,int &Dx ,int &Dy)
{
	int	cx,cy;
	GetCenter(cx,cy);
	const EulerRingL1Threshold	*RThr=GetThresholdR();

	int32		MinHoleD	=Clipping((int)(MasterHoleDiameter -RThr->MinHoleDiameter),0,99999999);
	int32		MaxHoleD	=Clipping((int)(MasterHoleDiameter+(RThr->MaxHoleDiameter+1)),0,99999999);

	ImageBuffer	&TBuff=GetTargetBuff();
	//int	SearchDot=RThr->SearchDot+MaxHoleD/2;
	int	SearchDot=RThr->SearchDot;
	int	SNumb=(2*SearchDot+1)*(2*SearchDot+1);

	struct	RearchResultStruct	*DimRoot=new struct	RearchResultStruct[4*SNumb];
	struct	RearchResultStruct	*DimU=DimRoot;
	struct	RearchResultStruct	*DimL=&DimRoot[  SNumb];
	struct	RearchResultStruct	*DimR=&DimRoot[2*SNumb];
	struct	RearchResultStruct	*DimB=&DimRoot[3*SNumb];
	int	nU=0;
	int	nL=0;
	int	nR=0;
	int	nB=0;
	for(int y=-SearchDot;y<=SearchDot;y++){
		for(int x=-SearchDot;x<=SearchDot;x++){
			DimU[nU].dx=x;
			DimU[nU].dy=y;
			if((DimU[nU].D=CalcSearchUpper(TBuff ,cx+mx+x,cy+my+y))>0.0){
				nU++;
			}
			DimL[nL].dx=x;
			DimL[nL].dy=y;
			if((DimL[nL].D=CalcSearchLeft (TBuff ,cx+mx+x,cy+my+y))>0.0){
				nL++;
			}
			DimR[nR].dx=x;
			DimR[nR].dy=y;
			if((DimR[nR].D=CalcSearchRight(TBuff ,cx+mx+x,cy+my+y))>0.0){
				nR++;
			}
			DimB[nB].dx=x;
			DimB[nB].dy=y;
			if((DimB[nB].D=CalcSearchLower(TBuff ,cx+mx+x,cy+my+y))>0.0){
				nB++;
			}
		}
	}
	QSort(DimU,nU,sizeof(DimU[0]),SortDimFunc);
	QSort(DimL,nL,sizeof(DimL[0]),SortDimFunc);
	QSort(DimR,nR,sizeof(DimR[0]),SortDimFunc);
	QSort(DimB,nB,sizeof(DimB[0]),SortDimFunc);

	const int	MaxDimNumb=100;
	struct	RearchResultLineStruct	VDim[MaxDimNumb];
	int	VNumb=0;
	for(int i=0;i<nU;i++){
		if(VNumb<MaxDimNumb && DimU[i].D>0){
			VDim[VNumb].dx1=DimU[i].dx;
			VDim[VNumb].dy1=DimU[i].dy;
			VDim[VNumb].D1 =DimU[i].D;
			int	MaxJ1=-1;
			int	MaxJ2=-1;
			double	MaxD1=0;
			double	MaxD2=0;
			for(int j=0;j<nB;j++){
				if(DimB[j].dx==DimU[i].dx && DimU[i].dy<DimB[j].dy && DimB[j].D>0){
					if(DimB[j].D>MaxD1){
						MaxD1=DimB[j].D;
						MaxJ1=j;
					}
					else if(DimB[j].D>MaxD2){
						MaxD2=DimB[j].D;
						MaxJ2=j;
					}
				}
			}
			if(VNumb<MaxDimNumb && MaxJ1>=0){
				VDim[VNumb].dx2=DimB[MaxJ1].dx;
				VDim[VNumb].dy2=DimB[MaxJ1].dy;
				VDim[VNumb].D2 =DimB[MaxJ1].D;
				VNumb++;
			}
			if(VNumb<MaxDimNumb && MaxJ2>=0){
				VDim[VNumb].dx1=DimU[i].dx;
				VDim[VNumb].dy1=DimU[i].dy;
				VDim[VNumb].D1 =DimU[i].D;
				VDim[VNumb].dx2=DimB[MaxJ2].dx;
				VDim[VNumb].dy2=DimB[MaxJ2].dy;
				VDim[VNumb].D2 =DimB[MaxJ2].D;
				VNumb++;
			}
		}
	}

	struct	RearchResultLineStruct	HDim[MaxDimNumb];
	int	HNumb=0;
	for(int i=0;i<nL;i++){
		if(HNumb<MaxDimNumb && DimL[i].D>0){
			HDim[HNumb].dx1=DimL[i].dx;
			HDim[HNumb].dy1=DimL[i].dy;
			HDim[HNumb].D1 =DimL[i].D;
			int	MaxJ1=-1;
			int	MaxJ2=-1;
			double	MaxD1=0;
			double	MaxD2=0;
			for(int j=0;j<nR;j++){
				if(DimR[j].dy==DimL[i].dy && DimL[i].dx<DimR[j].dx && DimR[j].D>0){
					if(DimR[j].D>MaxD1){
						MaxD1=DimR[j].D;
						MaxJ1=j;
					}
					else if(DimR[j].D>MaxD2){
						MaxD2=DimR[j].D;
						MaxJ2=j;
					}
				}
			}
			if(HNumb<MaxDimNumb && MaxJ1>=0){
				HDim[HNumb].dx2=DimR[MaxJ1].dx;
				HDim[HNumb].dy2=DimR[MaxJ1].dy;
				HDim[HNumb].D2 =DimR[MaxJ1].D;
				HNumb++;
			}
			if(HNumb<MaxDimNumb && MaxJ2>=0){
				HDim[HNumb].dx1=DimL[i].dx;
				HDim[HNumb].dy1=DimL[i].dy;
				HDim[HNumb].D1 =DimL[i].D;
				HDim[HNumb].dx2=DimR[MaxJ2].dx;
				HDim[HNumb].dy2=DimR[MaxJ2].dy;
				HDim[HNumb].D2 =DimR[MaxJ2].D;
				HNumb++;
			}
		}
	}
	QSort(HDim,HNumb,sizeof(HDim[0]),SortHVDimFunc);
	QSort(VDim,VNumb,sizeof(VDim[0]),SortHVDimFunc);

	double	MaxD=0;
	int		MaxCx=0;
	int		MaxCy=0;
	int		MaxR=0;
	int	HNumb2=HNumb/4;
	int	VNumb2=VNumb/4;
	for(int x=0;x<HNumb2;x++){
		for(int y=0;y<VNumb2;y++){
			int	Rx=(HDim[x].dx2-HDim[x].dx1)/2;
			int	Ry=(VDim[y].dy2-VDim[y].dy1)/2;
			if(abs(Rx-Ry)<6){
				int	Cx=(HDim[x].dx1+HDim[x].dx2)/2;
				int	Cy=(VDim[y].dy1+VDim[y].dy2)/2;
				int	R=(Rx+Ry)/2;
				double	D;
				//for(int i=-1;i<=1;i++){
				//	for(int j=-1;j<=1;j++){
				//		for(int m=-1;m<=1;m++){
						for(int m=0;m<=1;m++){
							//if(MatchDetail(TBuff,cx+mx+Cx+i,cy+my+Cy+j,Rx+m,Ry+m,D)==true){
							if(MatchDetail(TBuff,cx+mx+Cx,cy+my+Cy,Rx+m,Ry+m,D)==true){
								if(MaxD<D){
									MaxD=D;
									//MaxCx=Cx+i;
									//MaxCy=Cy+j;
									MaxCx=Cx;
									MaxCy=Cy;
									MaxR=R+m;
								}
							}
						}
					//}
				//}
			}
		}
	}
	delete	[]DimRoot;

	Dx=MaxCx;
	Dy=MaxCy;
}