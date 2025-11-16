/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPixelInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PixelInspectionResource.h"
#include <QSqlDatabase>
#include "XPixelInspection.h"
#include "XAutoMaskingPI.h"
#include "XMaskingFromGeneral.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XAnyData.h"
#include "XPropertyPixelInspectionPacket.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>
#include <QTextStream>
#include "XAutoAlignment.h"
#include "XAutoPCBHoleAligner.h"
#include "XVCutInspection.h"
#include "XCriticalFunc.h"
#include "XDisplayBitImage.h"
#include "ButtonThreshold2.h"
#include "XPixelInspectionPacket.h"
#include "XDisplayImage.h"
#include "XResultImportancePacket.h"
#include <QMessageBox>

//#define DebugConsole
//#define Debug
//#define Debug2
#ifdef Debug
int DebugPoint	=0;
int DebugPointX	=1413;
int DebugPointY	=3576;
#endif

int			ResultInPagePixel::GetNGCount(void)	const
{
	int	NGCount=0;
	for(ResultInItemPI *r=GetRawResult().GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsOk()==false){
			NGCount+=r->GetNGPointCount();
		}
	}
	return NGCount;
}

ResultInPageRoot	*ResultBaseForAlgorithmPixel::CreatePage(int phase ,int page)
{	
	return new ResultInPagePixel(GetPageDataPhase(phase),GetLayersBase()->GetPageData(page));	
}

PixelThresholdReq::PixelThresholdReq(void)
{
	GlobalPage	=-1;
	PixelItemID	=-1;
//	Mastered	=true;
//	Dx			=0;
//	Dy			=0;
}
bool	PixelThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,PixelItemID)==false)
		return false;
//	if(::Save(f,Mastered)==false)
//		return false;
//	if(::Save(f,Dx)==false)
//		return false;
//	if(::Save(f,Dy)==false)
//		return false;
	return true;
}
bool	PixelThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,PixelItemID)==false)
		return false;
//	if(::Load(f,Mastered)==false)
//		return false;
//	if(::Load(f,Dx)==false)
//		return false;
//	if(::Load(f,Dy)==false)
//		return false;
	return true;
}

PixelThresholdSend::PixelThresholdSend(void)
{
	GlobalPage		=-1;
	PixelItemID		=-1;
	PoleTable		=NULL;
	localX			=0;
	localY			=0;
	MasterX			=0;
	MasterY			=0;
	ThresholdRange	=0;

	MasterBrightness[0]		=MasterBrightness[1]	=MasterBrightness[2]	=0;
	MasterBrightness2[0]	=MasterBrightness2[1]	=MasterBrightness2[2]	=0;
	AverageBrightness[0]	=AverageBrightness[1]	=AverageBrightness[2]	=NULL;
	AverageBrightness2[0]	=AverageBrightness2[1]	=AverageBrightness2[2]	=NULL;
	LightBrightness[0]		=LightBrightness[1]		=LightBrightness[2]		=0;
	LightBrightness2[0]		=LightBrightness2[1]	=LightBrightness2[2]	=0;
	DarkBrightness[0]		=DarkBrightness[1]		=DarkBrightness[2]		=0;
	DarkBrightness2[0]		=DarkBrightness2[1]		=DarkBrightness2[2]		=0;
	TargetImageList[0]		=TargetImageList[1]		=TargetImageList[2]		=NULL;
	PL	=PH	=SL	=SH	=RL	=RH	=0;
	PLr	=PHr=SLr=SHr=RLr=RHr=0;
	InspectionLevel			=0;
	SearchAreaForMakeTable	=0;
	SearchDotBase			=0;
	PL1	=PH1=SL1=SH1=RL1=RH1=0;
	PLr1=PHr1=SLr1=SHr1=RLr1=RHr1=0;
	InsTargetBrightness[0]	=InsTargetBrightness[1]	=InsTargetBrightness[2]	=0;
	InsAverageCoordX		=0;
	InsAverageCoordY		=0;
	InsTargetCoordX			=0;
	InsTargetCoordY			=0;
	InsTargetBrightness2[0]	=InsTargetBrightness2[1]=InsTargetBrightness2[2]=0;
	InsAverageCoordX2		=0;
	InsAverageCoordY2		=0;
	InsTargetCoordX2		=0;
	InsTargetCoordY2		=0;
	InspectResult			=0;
//	ThresholdDifferencemap	=NULL;
	XLen=YLen				=0;
	pAlignPage				=NULL;
	pHoleAlignPage			=NULL;
	PixData					=NULL;
}

void	PixelThresholdSend::ConstructList(PixelThresholdReq *reqPacket,PixelInspectionBase *Base)
{
	GlobalPage		=reqPacket->GlobalPage;
	PixelItemID		=reqPacket->PixelItemID;
	InspectResult	=0;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(PixelItemID);
		if(item!=NULL){
//			int	dx=0;
//			int	dy=0;
//			if(item->GetCurrentResult()!=NULL){
//				dx=item->GetCurrentResult()->GetTotalShiftedX();
//				dy=item->GetCurrentResult()->GetTotalShiftedY();
//			}

			//?}?E?X?N???b?N?É ???A?W?d?a??
			PixelInspectionInPage *PInPage=dynamic_cast<PixelInspectionInPage *>(Ap);
			//int OutlineOffsetX=Ap->GetDataInPage()->GetOutlineOffset()->x;
			//int OutlineOffsetY=Ap->GetDataInPage()->GetOutlineOffset()->y;
			localX	=PInPage->GetLocalX();
			localY	=PInPage->GetLocalY();

			//PoleTable?d?a??
			PoleTable=PInPage->GetPoleTable();

			//?P?x?Ee??l?E?C?d?a??
			PixelInspectionItem	*PItem	=(PixelInspectionItem *)item;
			InspectionLevel				=((PixelInspectionBase *)PItem->GetParentBase())->getInspectionLevel();
			SearchDotBase				=((PixelInspectionBase *)PItem->GetParentBase())->getSearchDotBase();
			CheckPadIns					=((PixelInspectionBase *)PItem->GetParentBase())->getCheckPadIns();
			CheckSilkIns				=((PixelInspectionBase *)PItem->GetParentBase())->getCheckSilkIns();
			CheckResistIns				=((PixelInspectionBase *)PItem->GetParentBase())->getCheckResistIns();
			CheckHoleIns				=((PixelInspectionBase *)PItem->GetParentBase())->getCheckHoleIns();
			NGThresholdP				=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdP_B();
			NGThresholdS				=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdS_B();
			NGThresholdR				=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdR_B();
			NGThresholdH				=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdH_B();
			MinimumNGSizeP				=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeP();
			MinimumNGSizeS				=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeS();
			MinimumNGSizeR				=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeR();
			MinimumNGSizeH				=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeH();
			DonePadIns					=((PixelInspectionBase *)PItem->GetParentBase())->getDonePadIns();
			NGThresholdForPad			=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdForPad_B();
			MinimumNGSizeForPad			=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeForPad();
			DoneSilkIns					=((PixelInspectionBase *)PItem->GetParentBase())->getDoneSilkIns();
			NGThresholdForSilk			=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdForSilk_B();
			MinimumNGSizeForSilk		=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeForSilk();
			DoneResistIns				=((PixelInspectionBase *)PItem->GetParentBase())->getDoneResistIns();
			NGThresholdForResist		=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdForResist_B();
			MinimumNGSizeForResist		=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeForResist();
			DoneHoleIns					=((PixelInspectionBase *)PItem->GetParentBase())->getDoneHoleIns();
			NGThresholdForHole			=((PixelInspectionBase *)PItem->GetParentBase())->getNGThresholdForHole_B();
			MinimumNGSizeForHole		=((PixelInspectionBase *)PItem->GetParentBase())->getMinimumNGSizeForHole();
			BrightnessRange				=((PixelInspectionBase *)PItem->GetParentBase())->getBrightnessRange();
			RadianCoef					=M_PI/510.0;

			MasterX=MasterY=-1;
			SearchAreaForMakeTable=((PixelInspectionBase *)PItem->GetParentBase())->getSearchAreaForMakeTable();

			//???ÅC?a???I?a??
			PItem->GetTargetImageList(TargetImageList);

			if(DoneResistIns==true){
//////////////////////////////////////////////////////
//		???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC		//
//////////////////////////////////////////////////////

				//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
				if(PItem->GetMasterCoord		(localX,localY,MasterX,MasterY)==true){
					PItem->GetMasterBrightness	(MasterX,MasterY,MasterBrightness2,true);
					PItem->GetAverageBrightness	(MasterX,MasterY,SearchDotBase,AverageBrightness2,true);
					PItem->GetLightBrightness	(MasterX,MasterY,LightBrightness2,true);
					PItem->GetDarkBrightness	(MasterX,MasterY,DarkBrightness2,true);
					PItem->GetThreshold			(MasterX,MasterY,PL,PH,SL,SH,RL,RH,true);
					//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
					PItem->GetExecProcessingForResist1(MasterX,MasterY,SearchDotBase,NGThresholdForResist,BrightnessRange,255,PLr1,PHr1,SLr1,SHr1,RLr1,RHr1,InsAverageCoordX2,InsAverageCoordY2,InspectResult,ThresholdRange);
					if((InspectResult&0x0100000000)==0){
						//?u?I?I???ÅC?a???A?I???ÅC//
						PItem->GetExecProcessingForResist2(MasterX,MasterY,SearchDotBase,NGThresholdForResist,BrightnessRange,255,InsTargetBrightness2,InsTargetCoordX2,InsTargetCoordY2,InspectResult);
					}
				}
				if(InspectResult==0){
					//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
					PItem->GetMasterBrightness	(localX,localY,MasterBrightness);
					PItem->GetAverageBrightness	(localX,localY,SearchDotBase,AverageBrightness);
					PItem->GetLightBrightness	(localX,localY,LightBrightness);
					PItem->GetDarkBrightness	(localX,localY,DarkBrightness);
					PItem->GetThreshold			(localX,localY,PL,PH,SL,SH,RL,RH);
					//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
					PItem->GetExecProcessingForResist3(localX,localY,SearchDotBase,NGThresholdForResist,BrightnessRange,InspectionLevel,PLr1,PHr1,SLr1,SHr1,RLr1,RHr1,InsAverageCoordX,InsAverageCoordY,InspectResult,ThresholdRange);
					if((InspectResult&0x01000000000000)==0){
						//?u?I?I???ÅC?a???A?I???ÅC//
						PItem->GetExecProcessingForResist4(localX,localY,SearchDotBase,NGThresholdForResist,BrightnessRange,InspectionLevel,InsTargetBrightness2,InsTargetCoordX,InsTargetCoordY,InspectResult);
					}
				}
			}

//////////////////////////////////////////////////////
//					?E?i?I???ÅC						//
//////////////////////////////////////////////////////

			//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
			if(MasterX==-1){
				PItem->GetMasterCoord(localX,localY,MasterX,MasterY);
			}
			if(MasterX>=0){
				PItem->GetMasterBrightness	(MasterX,MasterY,MasterBrightness2,true);
				PItem->GetAverageBrightness	(MasterX,MasterY,SearchDotBase,AverageBrightness2,true);
				PItem->GetLightBrightness	(MasterX,MasterY,LightBrightness2,true);
				PItem->GetDarkBrightness	(MasterX,MasterY,DarkBrightness2,true);
				PItem->GetThreshold			(MasterX,MasterY,PL,PH,SL,SH,RL,RH,true);
				//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
				PItem->GetExecProcessing1(MasterX,MasterY,SearchDotBase,NGThresholdP,BrightnessRange,InspectionLevel,PL1,PH1,SL1,SH1,RL1,RH1,InsAverageCoordX,InsAverageCoordY,InspectResult,ThresholdRange);
				if((InspectResult&0x01)==0){
					//?u?I?I???ÅC?a???A?I???ÅC//
					PItem->GetExecProcessing2(MasterX,MasterY,SearchDotBase,NGThresholdP,BrightnessRange,InspectionLevel,InsTargetBrightness,InsTargetCoordX,InsTargetCoordY,InspectResult);
				}
			}
			if((InspectResult&0xFFFF)==0){
				//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
				PItem->GetMasterBrightness	(localX,localY,MasterBrightness);
				PItem->GetAverageBrightness	(localX,localY,SearchDotBase,AverageBrightness);
				PItem->GetLightBrightness	(localX,localY,LightBrightness);
				PItem->GetDarkBrightness	(localX,localY,DarkBrightness);
				PItem->GetThreshold			(localX,localY,PL,PH,SL,SH,RL,RH);
				//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
				PItem->GetExecProcessing3(localX,localY,SearchDotBase,NGThresholdP,BrightnessRange,InspectionLevel,PL1,PH1,SL1,SH1,RL1,RH1,InsAverageCoordX,InsAverageCoordY,InspectResult,ThresholdRange);
				if((InspectResult&0x010000)==0){
					//?u?I?I???ÅC?a???A?I???ÅC//
					PItem->GetExecProcessing4(localX,localY,SearchDotBase,NGThresholdP,BrightnessRange,InspectionLevel,InsTargetBrightness,InsTargetCoordX,InsTargetCoordY,InspectResult);
				}
			}

			//?f?[?^?d?R?s?[
			FPack						=PItem->wFPack;
//			ThresholdDifferencemap		=PItem->ThresholdDifferencemap;
			XLen						=PItem->XLen;
			YLen						=PItem->YLen;
			pAlignPage					=PItem->pAlignPage;
			pHoleAlignPage				=PItem->pHoleAlignPage;
			PixData						=PItem->PixData;
		}
	}
}

bool	PixelThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,PixelItemID)==false)
		return false;
//	if(::Save(f,Mastered)==false)
//		return false;
//	if(::Save(f,Dx)==false)
//		return false;
//	if(::Save(f,Dy)==false)
//		return false;
	return true;
}
bool	PixelThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,PixelItemID)==false)
		return false;
//	if(::Load(f,Mastered)==false)
//		return false;
//	if(::Load(f,Dx)==false)
//		return false;
//	if(::Load(f,Dy)==false)
//		return false;
	return true;
}

PixelTryThresholdReq::PixelTryThresholdReq(void)
{
	GlobalPage				=-1;
	PixelItemID				=-1;
	SearchAreaForMakeTable	=0;
	SearchDotBase			=0;
	PoleTable				=NULL;
	InspectionLevel			=0;
	localX					=0;
	localY					=0;
}
bool	PixelTryThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,PixelItemID)==false)
		return false;
	if(::Save(f,SearchAreaForMakeTable)==false)
		return false;
	if(::Save(f,SearchDotBase)==false)
		return false;
	return true;
}
bool	PixelTryThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,PixelItemID)==false)
		return false;
	if(::Load(f,SearchAreaForMakeTable)==false)
		return false;
	if(::Load(f,SearchDotBase)==false)
		return false;
	return true;
}

PixelTryThresholdSend::PixelTryThresholdSend(void)
{
	GlobalPage				=-1;
	PixelItemID				=-1;
	PoleTable				=NULL;
	localX					=0;
	localY					=0;

	AverageBrightness[0]	=AverageBrightness[1]	=AverageBrightness[2]	=NULL;
	TargetBrightness[0]		=TargetBrightness[1]	=TargetBrightness[2]	=NULL;
	PL	=PH	=SL	=SH	=RL	=RH	=NULL;
	InspectionLevel			=0;
	SearchAreaForMakeTable	=0;
	SearchDotBase			=0;
	PL1	=PH1=SL1=SH1=RL1=RH1=0;
	InsTargetBrightness[0]	=InsTargetBrightness[1]	=InsTargetBrightness[2]	=0;
	InsAverageCoordX		=0;
	InsAverageCoordY		=0;
	InsTargetCoordX			=0;
	InsTargetCoordY			=0;
	InspectResult			=0;
}

void	PixelTryThresholdSend::ConstructList(PixelTryThresholdReq *reqPacket,PixelInspectionBase *Base)
{
	GlobalPage				=reqPacket->GlobalPage;
	PixelItemID				=reqPacket->PixelItemID;
	SearchAreaForMakeTable	=reqPacket->SearchAreaForMakeTable;
	SearchDotBase			=reqPacket->SearchDotBase;
	PoleTable				=reqPacket->PoleTable;
	InspectionLevel			=reqPacket->InspectionLevel;
	localX					=reqPacket->localX;
	localY					=reqPacket->localY;
	InspectResult			=0;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(PixelItemID);
		if(item!=NULL){
			//?P?x?Ee??l?E?C?d?a??
			PixelInspectionItem	*PItem=(PixelInspectionItem *)item;
			PItem->GetAverageBrightness	(localX,localY,SearchDotBase,AverageBrightness);

			if(PL!=NULL){
				delete []PL;
			}
			if(PH!=NULL){
				delete []PH;
			}
			if(SL!=NULL){
				delete []SL;
			}
			if(SH!=NULL){
				delete []SH;
			}
			if(RL!=NULL){
				delete []RL;
			}
			if(RH!=NULL){
				delete []RH;
			}
			int Numb=((SearchDotBase<<1)+1)*((SearchDotBase<<1)+1);
			PL	=new BYTE[Numb];
			PH	=new BYTE[Numb];
			SL	=new BYTE[Numb];
			SH	=new BYTE[Numb];
			RL	=new BYTE[Numb];
			RH	=new BYTE[Numb];

			PItem->GetTryThreshold		(localX,localY,SearchDotBase,SearchAreaForMakeTable,PL,PH,SL,SH,RL,RH);
			PItem->GetTryExecProcessing1(localX,localY,SearchDotBase,InspectionLevel,PL,PH,SL,SH,RL,RH,PL1,PH1,SL1,SH1,RL1,RH1,InsAverageCoordX,InsAverageCoordY,InspectResult);
			PItem->GetTryExecProcessing2(localX,localY,SearchDotBase,InspectionLevel,PL,PH,SL,SH,RL,RH,InsTargetBrightness,InsTargetCoordX,InsTargetCoordY,InspectResult);
		}
	}
}

bool	PixelTryThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,PixelItemID)==false)
		return false;
	return true;
}
bool	PixelTryThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,PixelItemID)==false)
		return false;
	return true;
}

inline	double	Clip1(double d)
{
	if(d>1)
		return 1;
	if(d<-1)
		return -1;
	return d;
}

inline	BYTE	Clip255(int d)
{
	if(d<0)
		return 0;
	if(d>255)
		return 255;
	return d;
}

inline	BYTE	GetAvr(DWORD Added,int n)
{
	return Added/n;
}

inline	BYTE	GetDisorder(DWORD Added,DWORD Added2,int n)
{
	double	Avr=Added/(double)n;
	double	v=(Added2-(double)Avr*(double)Avr*n)/(double)n;
	return Clip255(sqrt(v));
}

///////////////?Å·???u?o?[?W?????I???c?Å·///////////////
bool	PixelSampleList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(PickupColor.Save(f)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,NGSize)==false)
		return false;
	return true;
}
	
bool	PixelSampleList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(PickupColor.Load(f)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,NGSize)==false)
		return false;
	return true;
}

PixelSampleList	&PixelSampleList::operator=(PixelSampleList &src)
{
	Name		=src.Name;
	PickupColor	=src.PickupColor;
	SearchDot	=src.SearchDot;
	NGSize		=src.NGSize;
	return *this;
}

PixelSampleContainer	&PixelSampleContainer::operator=(PixelSampleContainer &src)
{
	RemoveAll();
	for(PixelSampleList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		PixelSampleList	*d=new PixelSampleList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	PixelSampleContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(PixelSampleList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false)
			return false;
	}
	return true;
}

bool	PixelSampleContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		PixelSampleList *s=new PixelSampleList();
		if(s->Load(f)==false)
			return false;
		AppendList(s);
	}
	return true;
}
///////////////?a???u?o?[?W?????I???c?a///////////////

//=========================================================================================
	
PixelInspectionLibrary::PixelInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	DetailSettingNarrow			=true;
	SearchDotMasterNarrow		=0;
	SearchDotTargetNarrow		=1;
	RelativeNGThresholdNarrow	=0;
	AbsoluteNGThresholdNarrow	=10;
	NGSizeNarrow				=4;
	DetailSettingBroad			=false;
	SearchDotMasterBroad		=0;
	SearchDotTargetBroad		=1;
	RelativeNGThresholdBroad	=0;
	AbsoluteNGThresholdBroad	=10;
	NGSizeBroad					=100;

	ThrType						=_Other;
	IsCalcPixelInterPoration	=false;
}

PixelInspectionLibrary::~PixelInspectionLibrary(void)
{
}

bool	PixelInspectionLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false){
		return(false);
	}
	if(::Save(f,DetailSettingNarrow)==false){
		return false;
	}
	if(::Save(f,SearchDotMasterNarrow)==false){
		return false;
	}
	if(::Save(f,SearchDotTargetNarrow)==false){
		return false;
	}
	if(::Save(f,RelativeNGThresholdNarrow)==false){
		return false;
	}
	if(::Save(f,AbsoluteNGThresholdNarrow)==false){
		return false;
	}
	if(::Save(f,NGSizeNarrow)==false){
		return false;
	}
	if(::Save(f,DetailSettingBroad)==false){
		return false;
	}
	if(::Save(f,SearchDotMasterBroad)==false){
		return false;
	}
	if(::Save(f,SearchDotTargetBroad)==false){
		return false;
	}
	if(::Save(f,RelativeNGThresholdBroad)==false){
		return false;
	}
	if(::Save(f,AbsoluteNGThresholdBroad)==false){
		return false;
	}
	if(::Save(f,NGSizeBroad)==false){
		return false;
	}
	if(::Save(f,IsCalcPixelInterPoration)==false){
		return false;
	}
	return true;
}
bool	PixelInspectionLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false){
		return(false);
	}
	if(::Load(f,DetailSettingNarrow)==false){
		return false;
	}
	if(::Load(f,SearchDotMasterNarrow)==false){
		return false;
	}
	if(::Load(f,SearchDotTargetNarrow)==false){
		return false;
	}
	if(::Load(f,RelativeNGThresholdNarrow)==false){
		return false;
	}
	if(::Load(f,AbsoluteNGThresholdNarrow)==false){
		return false;
	}
	if(::Load(f,NGSizeNarrow)==false){
		return false;
	}
	if(::Load(f,DetailSettingBroad)==false){
		return false;
	}
	if(::Load(f,SearchDotMasterBroad)==false){
		return false;
	}
	if(::Load(f,SearchDotTargetBroad)==false){
		return false;
	}
	if(::Load(f,RelativeNGThresholdBroad)==false){
		return false;
	}
	if(::Load(f,AbsoluteNGThresholdBroad)==false){
		return false;
	}
	if(::Load(f,NGSizeBroad)==false){
		return false;
	}
	if(::Load(f,IsCalcPixelInterPoration)==false){
		return false;
	}
	return true;
}
PixelInspectionLibrary	&PixelInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	DetailSettingNarrow			=((const PixelInspectionLibrary *)&src)->DetailSettingNarrow;
	SearchDotMasterNarrow		=((const PixelInspectionLibrary *)&src)->SearchDotMasterNarrow;
	SearchDotTargetNarrow		=((const PixelInspectionLibrary *)&src)->SearchDotTargetNarrow;
	RelativeNGThresholdNarrow	=((const PixelInspectionLibrary *)&src)->RelativeNGThresholdNarrow;
	AbsoluteNGThresholdNarrow	=((const PixelInspectionLibrary *)&src)->AbsoluteNGThresholdNarrow;
	NGSizeNarrow				=((const PixelInspectionLibrary *)&src)->NGSizeNarrow;
	DetailSettingBroad			=((const PixelInspectionLibrary *)&src)->DetailSettingBroad;
	SearchDotMasterBroad		=((const PixelInspectionLibrary *)&src)->SearchDotMasterBroad;
	SearchDotTargetBroad		=((const PixelInspectionLibrary *)&src)->SearchDotTargetBroad;
	RelativeNGThresholdBroad	=((const PixelInspectionLibrary *)&src)->RelativeNGThresholdBroad;
	AbsoluteNGThresholdBroad	=((const PixelInspectionLibrary *)&src)->AbsoluteNGThresholdBroad;
	NGSizeBroad					=((const PixelInspectionLibrary *)&src)->NGSizeBroad;
	return *this;
}

PixelInspectionLibraryContainer::PixelInspectionLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

PixelInspectionLibraryContainer::~PixelInspectionLibraryContainer(void)
{
}

//-------------------------------------------------------------------------------------------------------

PixelInspectionThreshold::PixelInspectionThreshold(PixelInspectionItem *parent)
:AlgorithmThreshold(parent)
{
	Enable					=true;
	ThrType					=(DetailType)_None;
	ThrMode					=_None;
	SearchDotMaster			=0;
	SearchDotTarget			=0;
	RelativeNGThreshold		=0;
	AbsoluteNGThreshold		=10;
	NGSize					=10;
	IsCalcPixelInterPoration=false;
}

void	PixelInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	Enable					=((PixelInspectionThreshold *)&src)->Enable;
	ThrType					=((PixelInspectionThreshold *)&src)->ThrType;
	ThrMode					=((PixelInspectionThreshold *)&src)->ThrMode;
	SearchDotMaster			=((PixelInspectionThreshold *)&src)->SearchDotMaster;
	SearchDotTarget			=((PixelInspectionThreshold *)&src)->SearchDotTarget;
	RelativeNGThreshold		=((PixelInspectionThreshold *)&src)->RelativeNGThreshold;
	AbsoluteNGThreshold		=((PixelInspectionThreshold *)&src)->AbsoluteNGThreshold;
	NGSize					=((PixelInspectionThreshold *)&src)->NGSize;
	IsCalcPixelInterPoration=((PixelInspectionThreshold *)&src)->IsCalcPixelInterPoration;
}
bool	PixelInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	if(Enable					!=((PixelInspectionThreshold *)&src)->Enable					)	return false;
	if(ThrType					!=((PixelInspectionThreshold *)&src)->ThrType					)	return false;
	if(ThrMode					!=((PixelInspectionThreshold *)&src)->ThrMode					)	return false;
	if(SearchDotMaster			!=((PixelInspectionThreshold *)&src)->SearchDotMaster			)	return false;
	if(SearchDotTarget			!=((PixelInspectionThreshold *)&src)->SearchDotTarget			)	return false;
	if(RelativeNGThreshold		!=((PixelInspectionThreshold *)&src)->RelativeNGThreshold		)	return false;
	if(AbsoluteNGThreshold		!=((PixelInspectionThreshold *)&src)->AbsoluteNGThreshold		)	return false;
	if(NGSize					!=((PixelInspectionThreshold *)&src)->NGSize					)	return false;
	if(IsCalcPixelInterPoration	!=((PixelInspectionThreshold *)&src)->IsCalcPixelInterPoration	)	return false;
	return true;
}

bool	PixelInspectionThreshold::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,(int)ThrType)==false)
		return(false);
	if(::Save(f,(int)ThrMode)==false)
		return(false);
	if(::Save(f,SearchDotMaster)==false)
		return(false);
	if(::Save(f,SearchDotTarget)==false)
		return(false);
	if(::Save(f,RelativeNGThreshold)==false)
		return(false);
	if(::Save(f,AbsoluteNGThreshold)==false)
		return(false);
	if(::Save(f,NGSize)==false)
		return(false);
	if(::Save(f,IsCalcPixelInterPoration)==false)
		return(false);
	return(true);
}

bool	PixelInspectionThreshold::Load(QIODevice *f)
{
	//?}?X?^?[?f?[?^?I?o?[?W?????a?ÅëLoad?I??
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	if(MBase==NULL){
		return false;
	}
	PixelInspectionBase *PBase=dynamic_cast<PixelInspectionBase *>(MBase);
	if(PBase==NULL){
		return false;
	}
	int32 MasterLoadVer=PBase->MasterLoadVer;
	if(MasterLoadVer==0){
		//???u?o?[?W????
		if(SampleLists.Load(f)==false){
			return false;
		}
		return true;
	}

	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	int	iThrType;
	if(::Load(f,iThrType)==false)
		return(false);
	ThrType=(DetailType)iThrType;
	int	iThrMode;
	if(::Load(f,iThrMode)==false)
		return(false);
	ThrMode=(ThresholdMode)iThrMode;
	if(::Load(f,SearchDotMaster)==false)
		return(false);
	if(::Load(f,SearchDotTarget)==false)
		return(false);
	if(::Load(f,RelativeNGThreshold)==false)
		return(false);
	if(::Load(f,AbsoluteNGThreshold)==false)
		return(false);
	if(::Load(f,NGSize)==false)
		return(false);
	if(::Load(f,IsCalcPixelInterPoration)==false)
		return(false);
	return(true);
}

void	PixelInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	PixelInspectionLibrary	*LSrc=dynamic_cast<PixelInspectionLibrary *>(src);
	if(LSrc==NULL){
		return;
	}

	IsCalcPixelInterPoration=LSrc->IsCalcPixelInterPoration;

	if(ThrMode==_Narrow){
		Enable				=LSrc->DetailSettingNarrow;
		SearchDotMaster		=LSrc->SearchDotMasterNarrow;
		SearchDotTarget		=LSrc->SearchDotTargetNarrow;
		RelativeNGThreshold	=LSrc->RelativeNGThresholdNarrow;
		AbsoluteNGThreshold	=LSrc->AbsoluteNGThresholdNarrow;
		NGSize				=LSrc->NGSizeNarrow;
	}
	else if(ThrMode==_Broad){
		Enable				=LSrc->DetailSettingBroad;
		SearchDotMaster		=LSrc->SearchDotMasterBroad;
		SearchDotTarget		=LSrc->SearchDotTargetBroad;
		RelativeNGThreshold	=LSrc->RelativeNGThresholdBroad;
		AbsoluteNGThreshold	=LSrc->AbsoluteNGThresholdBroad;
		NGSize				=LSrc->NGSizeBroad;
	}
}
/*
void	PixelInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	PixelInspectionLibrary	*LDst=dynamic_cast<PixelInspectionLibrary *>(Dest);
	if(LDst==NULL){
		return;
	}

	if(ThrMode==_Narrow){
		LDst->DetailSettingNarrow		=true;
		LDst->SearchDotMasterNarrow		=SearchDotMaster;
		LDst->SearchDotTargetNarrow		=SearchDotTarget;
		LDst->RelativeNGThresholdNarrow	=RelativeNGThreshold;
		LDst->AbsoluteNGThresholdNarrow	=AbsoluteNGThreshold;
		LDst->NGSizeNarrow				=NGSize;
	}
	else if(ThrMode==_Broad){
		LDst->DetailSettingBroad		=true;
		LDst->SearchDotMasterBroad		=SearchDotMaster;
		LDst->SearchDotTargetBroad		=SearchDotTarget;
		LDst->RelativeNGThresholdBroad	=RelativeNGThreshold;
		LDst->AbsoluteNGThresholdBroad	=AbsoluteNGThreshold;
		LDst->NGSizeBroad				=NGSize;
	}
}
*/
//================================================================================

bool	ResultClusterOnItem::Save(QIODevice *f)
{
/*
	int32	N=List.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(PureFlexAreaList *L=List.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
*/
	return true;
}
	
bool	ResultClusterOnItem::Load(QIODevice *f)
{
/*
	List.RemoveAll();

	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		PureFlexAreaList	*a=new PureFlexAreaList();
		if(a->Load(f)==false)
			return false;
		List.AppendList(a);
	}
*/
	return true;
}

//=============================================================================================

PixelInspectionItem::PixelInspectionItem(void)
{
	PixData						=NULL;
	PixDataForResistSilk[0]		=PixDataForResistSilk[1]=NULL;
	AllocX=AllocY				=0;
	NGBitmap					=NULL;
	InsCheckedBitmap			=NULL;
	TempNGBitmap				=NULL;
//	ThresholdDifferencemap		=NULL;
	XByte	=XLen	=YLen		=0;
	pAlignPage					=NULL;
	pHoleAlignPage				=NULL;
	pVCutPage					=NULL;
	wFPack						=NULL;

	IsShowOnlyDetail			=false;
	IsShowOnlyCircle			=false;

	NowInspection				=false;

	MasterImageList[0]	=MasterImageList[1]		=MasterImageList[2]		=NULL;
	AverageImageList[0]	=AverageImageList[1]	=AverageImageList[2]	=NULL;
	LightImageList[0]	=LightImageList[1]		=LightImageList[2]		=NULL;
	DarkImageList[0]	=DarkImageList[1]		=DarkImageList[2]		=NULL;
	TargetImageList[0]	=TargetImageList[1]		=TargetImageList[2]		=NULL;
	DisorderImageList[0]=DisorderImageList[1]	=DisorderImageList[2]	=NULL;

	MLeastSquaresMethodTable[0]=MLeastSquaresMethodTable[1]=MLeastSquaresMethodTable[2]=NULL;
	TLeastSquaresMethodTable[0]=TLeastSquaresMethodTable[1]=TLeastSquaresMethodTable[2]=NULL;
	MaskBitmap	=NULL;

	CurrentMasterCounter=0;
	LoadedFlag			=false;
	ExecuteInitialAfterEditFlag = false;

	ThrRange	=0;		//256-InspectionLevel
	RadianCoef	=0;

	AreaArrayList				=NULL;	//?I?UAlgorithm?IItem?|?C???^?I???X?g?d?U??
	AreaArrayCnt				=0;
	UniqueID					=0;
	DCAlgorithmInPagePIPointer	=NULL;
	TargetAreaArrayList			=NULL;
	TargetAreaArrayCnt			=0;
	TargetDCBitmap				=NULL;
}

PixelInspectionItem::~PixelInspectionItem(void)
{
	Release();
	AllocX=AllocY=0;
	if(NGBitmap!=NULL){
		DeleteMatrixBuff(NGBitmap,YLen);
		NGBitmap=NULL;
	}
	if(InsCheckedBitmap!=NULL){
		DeleteMatrixBuff(InsCheckedBitmap,YLen);
		InsCheckedBitmap=NULL;
	}
	if(TempNGBitmap!=NULL){
		DeleteMatrixBuff(TempNGBitmap,YLen);
		TempNGBitmap=NULL;
	}
//	if(ThresholdDifferencemap!=NULL){
//		DeleteMatrixBuff(ThresholdDifferencemap,YLen);
//		ThresholdDifferencemap=NULL;
//	}
}

AlgorithmItemPI	&PixelInspectionItem::operator=(const AlgorithmItemRoot &src)
{
	const PixelInspectionItem	*s=dynamic_cast<const PixelInspectionItem *>(&src);
	if(s!=NULL){
		return AlgorithmItemPI::operator=(*s);
	}
	return *this;
/*
	AlgorithmItemPI::operator=(src);
	Release();
	PixelInspectionItem	*Src=dynamic_cast<PixelInspectionItem *>(&src);
	AllocX=Src->AllocX;
	AllocY=Src->AllocY;
	PixData=new PixelInsData*[AllocY];
	for(int y=0;y<AllocY;y++){
		PixData[y]=new PixelInsData[AllocX];
		memcpy(PixData[y],Src->PixData[y],AllocX*sizeof(PixData[0][0]));
	}
	return *this;
*/
}

//Target?I?A?W?E?I???ÅE?eMaster?A?W?d?T?ÅE
bool	PixelInspectionItem::GetMasterCoord(int TX,int TY,int &MX,int &MY)
{
	if(pAlignPage==NULL){
		MX=MY=-2;
		return false;
	}

	//?T?ÅE?I?I?d???s?e
	int SearchRange=((AutoAlignmentBase *)pAlignPage->GetParentBase())->SearchDot;

	//?ÅP?e?A?W?A?I?Å‚?f
	int mtX,mtY;
	mtX=TX;
	mtY=TY;
	mtX+=pAlignPage->GetShiftXFromMaster(TX,TY);
	mtY+=pAlignPage->GetShiftYFromMaster(TX,TY);
	if(mtX==TX && mtY==TY){
		MX=TX;
		MY=TY;
		return true;
	}

	//?u?I?A?I?Å‚?f
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	for(int Len=1;Len<=SearchRange;Len++){
		int	dx=0;
		int	dy=-Len;

		if(TY+dy>=0 && TY+dy<YNumb){
			for(dx=-Len;dx<Len;dx++){
				mtX=TX+dx;
				mtY=TY+dy;
				if(mtX<0 || mtX>=XNumb){
					continue;
				}
				mtX+=pAlignPage->GetShiftXFromMaster(TX+dx,TY+dy);
				mtY+=pAlignPage->GetShiftYFromMaster(TX+dx,TY+dy);
				if(mtX==TX && mtY==TY){
					MX=TX+dx;
					MY=TY+dy;
					return true;
				}
			}
		}
		if(TX+dx>=0 && TX+dx<XNumb){
			for(;dy<Len;dy++){
				mtX=TX+dx;
				mtY=TY+dy;
				if(mtY<0 || mtY>=YNumb){
					continue;
				}
				mtX+=pAlignPage->GetShiftXFromMaster(TX+dx,TY+dy);
				mtY+=pAlignPage->GetShiftYFromMaster(TX+dx,TY+dy);
				if(mtX==TX && mtY==TY){
					MX=TX+dx;
					MY=TY+dy;
					return true;
				}
			}
		}
		if(TY+dy>=0 && TY+dy<YNumb){
			for(;dx>-Len;dx--){
				mtX=TX+dx;
				mtY=TY+dy;
				if(mtX<0 || mtX>=XNumb){
					continue;
				}
				mtX+=pAlignPage->GetShiftXFromMaster(TX+dx,TY+dy);
				mtY+=pAlignPage->GetShiftYFromMaster(TX+dx,TY+dy);
				if(mtX==TX && mtY==TY){
					MX=TX+dx;
					MY=TY+dy;
					return true;
				}
			}
		}
		if(TX+dx>=0 && TX+dx<XNumb){
			for(;dy>-Len;dy--){
				mtX=TX+dx;
				mtY=TY+dy;
				if(mtY<0 || mtY>=YNumb){
					continue;
				}
				mtX+=pAlignPage->GetShiftXFromMaster(TX+dx,TY+dy);
				mtY+=pAlignPage->GetShiftYFromMaster(TX+dx,TY+dy);
				if(mtX==TX && mtY==TY){
					MX=TX+dx;
					MY=TY+dy;
					return true;
				}
			}
		}
	}
	MX=MY=-2;
	return false;
}

void	PixelInspectionItem::GetTargetImageList(ImageBuffer *Buffer[])
{
	Buffer[0]=TargetImageList[0];
	Buffer[1]=TargetImageList[1];
	Buffer[2]=TargetImageList[2];
}

bool	PixelInspectionItem::GetMasterBrightness(int X,int Y,BYTE Brightness[],bool Master)
{
	int	mx,my;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	if(Master==true){
		//X,Y?I?}?X?^?[?a??
		mx=X;
		my=Y;
	}
	else{
		//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
		int tmX,tmY;
		if(pAlignPage==NULL){
			tmX=tmY=0;
		}
		else{
			tmX=pAlignPage->GetShiftXFromTarget(X,Y);
			tmY=pAlignPage->GetShiftYFromTarget(X,Y);
		}
		mx=X+tmX;
		my=Y+tmY;
	}
	if(mx<0 || XNumb<=mx){
		return false;
	}
	if(my<0 || YNumb<=my){
		return false;
	}

	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	if(Colored==true){
		GetMasterBuffList(MasterImageList);
		Brightness[0]=*(MasterImageList[0]->GetY(my)+mx);
		Brightness[1]=*(MasterImageList[1]->GetY(my)+mx);
		Brightness[2]=*(MasterImageList[2]->GetY(my)+mx);
	}
	return true;
}

bool	PixelInspectionItem::GetAverageBrightness(int X,int Y,int SearchDot,BYTE *Brightness[],bool Master)
{
	int	mx,my;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	if(Master==true){
		//X,Y?I?}?X?^?[?a??
		mx=X;
		my=Y;
	}
	else{
		//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
		int tmX,tmY;
		if(pAlignPage==NULL){
			tmX=tmY=0;
		}
		else{
			tmX=pAlignPage->GetShiftXFromTarget(X,Y);
			tmY=pAlignPage->GetShiftYFromTarget(X,Y);
		}
		mx=X+tmX;
		my=Y+tmY;
	}
	if((mx-(SearchDot+1))<0 || XNumb<=(mx+(SearchDot+1))){
		return false;
	}
	if((my-(SearchDot+1))<0 || YNumb<=(my+(SearchDot+1))){
		return false;
	}

	//???u?Å‚
	if(Brightness[0]!=NULL){
		for(int i=0;i<3;i++){
			delete []Brightness[i];
		}
	}
	int Numb=(((SearchDot+1)<<1)+1)*(((SearchDot+1)<<1)+1);
	for(int i=0;i<3;i++){
		Brightness[i]=new BYTE[Numb];
	}

	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	if(Colored==true){
		Brightness[0][0]=*(AverageImageList[0]->GetY(my)+mx);
		Brightness[1][0]=*(AverageImageList[1]->GetY(my)+mx);
		Brightness[2][0]=*(AverageImageList[2]->GetY(my)+mx);

		int Index=1;
		for(int Len=1;Len<=(SearchDot+1);Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++,Index++){
				Brightness[0][Index]=*(AverageImageList[0]->GetY(my+dy)+mx+dx);
				Brightness[1][Index]=*(AverageImageList[1]->GetY(my+dy)+mx+dx);
				Brightness[2][Index]=*(AverageImageList[2]->GetY(my+dy)+mx+dx);
			}
			for(;dy<Len;dy++,Index++){
				Brightness[0][Index]=*(AverageImageList[0]->GetY(my+dy)+mx+dx);
				Brightness[1][Index]=*(AverageImageList[1]->GetY(my+dy)+mx+dx);
				Brightness[2][Index]=*(AverageImageList[2]->GetY(my+dy)+mx+dx);
			}
			for(;dx>-Len;dx--,Index++){
				Brightness[0][Index]=*(AverageImageList[0]->GetY(my+dy)+mx+dx);
				Brightness[1][Index]=*(AverageImageList[1]->GetY(my+dy)+mx+dx);
				Brightness[2][Index]=*(AverageImageList[2]->GetY(my+dy)+mx+dx);
			}
			for(;dy>-Len;dy--,Index++){
				Brightness[0][Index]=*(AverageImageList[0]->GetY(my+dy)+mx+dx);
				Brightness[1][Index]=*(AverageImageList[1]->GetY(my+dy)+mx+dx);
				Brightness[2][Index]=*(AverageImageList[2]->GetY(my+dy)+mx+dx);
			}
		}
	}

	return true;
}

bool	PixelInspectionItem::GetLightBrightness(int X,int Y,BYTE Brightness[],bool Master)
{
	int	mx,my;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	if(Master==true){
		//X,Y?I?}?X?^?[?a??
		mx=X;
		my=Y;
	}
	else{
		//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
		int tmX,tmY;
		if(pAlignPage==NULL){
			tmX=tmY=0;
		}
		else{
			tmX=pAlignPage->GetShiftXFromTarget(X,Y);
			tmY=pAlignPage->GetShiftYFromTarget(X,Y);
		}
		mx=X+tmX;
		my=Y+tmY;
	}
	if(mx<0 || XNumb<=mx){
		return false;
	}
	if(my<0 || YNumb<=my){
		return false;
	}

	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	if(Colored==true){
		if(GetLightBuffList(LightImageList)==false){
			return false;
		}
		Brightness[0]=*(LightImageList[0]->GetY(my)+mx);
		Brightness[1]=*(LightImageList[1]->GetY(my)+mx);
		Brightness[2]=*(LightImageList[2]->GetY(my)+mx);
	}
	//delete
	DeleteImageList(LightImageList);

	return true;
}

bool	PixelInspectionItem::GetDarkBrightness(int X,int Y,BYTE Brightness[],bool Master)
{
	int	mx,my;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	if(Master==true){
		//X,Y?I?}?X?^?[?a??
		mx=X;
		my=Y;
	}
	else{
		//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
		int tmX,tmY;
		if(pAlignPage==NULL){
			tmX=tmY=0;
		}
		else{
			tmX=pAlignPage->GetShiftXFromTarget(X,Y);
			tmY=pAlignPage->GetShiftYFromTarget(X,Y);
		}
		mx=X+tmX;
		my=Y+tmY;
	}
	if(mx<0 || XNumb<=mx){
		return false;
	}
	if(my<0 || YNumb<=my){
		return false;
	}

	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	if(Colored==true){
		if(GetDarkBuffList(DarkImageList)==false){
			return false;
		}
		Brightness[0]=*(DarkImageList[0]->GetY(my)+mx);
		Brightness[1]=*(DarkImageList[1]->GetY(my)+mx);
		Brightness[2]=*(DarkImageList[2]->GetY(my)+mx);
	}
	//delete
	DeleteImageList(DarkImageList);

	return true;
}

bool	PixelInspectionItem::GetThreshold(int X,int Y,BYTE &PL,BYTE &PH,BYTE &SL,BYTE &SH,BYTE &RL,BYTE &RH,bool Master)
{
	if(PixData==NULL){
		return false;
	}

	int	mx,my;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	if(Master==true){
		//X,Y?I?}?X?^?[?a??
		mx=X;
		my=Y;
	}
	else{
		//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
		int tmX,tmY;
		if(pAlignPage==NULL){
			tmX=tmY=0;
		}
		else{
			tmX=pAlignPage->GetShiftXFromTarget(X,Y);
			tmY=pAlignPage->GetShiftYFromTarget(X,Y);
		}
		mx=X+tmX;
		my=Y+tmY;
	}
	if(mx<0 || XNumb<=mx){
		return false;
	}
	if(my<0 || YNumb<=my){
		return false;
	}

	PixelInsData	*PixD=PixData[my];
	PL=PixD[mx].PL;
	PH=PixD[mx].PH;
	SL=PixD[mx].SL;
	SH=PixD[mx].SH;
	RL=PixD[mx].RL;
	RH=PixD[mx].RH;

	return true;
}

bool	PixelInspectionItem::GetTryThreshold(int X,int Y,int SearchDot,int SearchArea,BYTE *PL,BYTE *PH,BYTE *SL,BYTE *SH,BYTE *RL,BYTE *RH)
{
	if(PixData==NULL){
		return false;
	}

	//?^?[?Q?b?g?a???c?c?}?X?^?[?a???i???I?a???j?O?I?A?W?a?3
	int tmX,tmY;
	if(pAlignPage==NULL){
		tmX=tmY=0;
	}
	else{
		tmX=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY=pAlignPage->GetShiftYFromTarget(X,Y);
	}
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	int	mx=X+tmX;
	if(mx<0 || XNumb<=mx){
		return false;
	}
	int	my=Y+tmY;
	if(my<0 || YNumb<=my){
		return false;
	}

	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	if(Colored==true){
		//???I?a??
		int Index=0;
		PH[Index]=0;
		PL[Index]=255;
		SH[Index]=0;
		SL[Index]=255;
		RH[Index]=0;
		RL[Index]=255;
		CalcThresholdImageList(mx,my,SearchArea,AverageImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
		//?u?I?A?I?Å‚?f
		Index++;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++,Index++){
				PH[Index]=0;
				PL[Index]=255;
				SH[Index]=0;
				SL[Index]=255;
				RH[Index]=0;
				RL[Index]=255;
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,AverageImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy<Len;dy++,Index++){
				PH[Index]=0;
				PL[Index]=255;
				SH[Index]=0;
				SL[Index]=255;
				RH[Index]=0;
				RL[Index]=255;
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,AverageImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dx>-Len;dx--,Index++){
				PH[Index]=0;
				PL[Index]=255;
				SH[Index]=0;
				SL[Index]=255;
				RH[Index]=0;
				RL[Index]=255;
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,AverageImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy>-Len;dy--,Index++){
				PH[Index]=0;
				PL[Index]=255;
				SH[Index]=0;
				SL[Index]=255;
				RH[Index]=0;
				RL[Index]=255;
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,AverageImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
		}

		//???e?Åë?a??
		Index=0;
		if(GetLightBuffList(LightImageList)==false){
			return false;
		}
		CalcThresholdImageList(mx,my,SearchArea,LightImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
		//?u?I?A?I?Å‚?f
		Index++;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,LightImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy<Len;dy++,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,LightImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dx>-Len;dx--,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,LightImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy>-Len;dy--,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,LightImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
		}
		//delete
		DeleteImageList(LightImageList);

		//?A?Åë?a??
		Index=0;
		if(GetDarkBuffList(DarkImageList)==false){
			return false;
		}
		CalcThresholdImageList(mx,my,SearchArea,DarkImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
		//?u?I?A?I?Å‚?f
		Index++;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,DarkImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy<Len;dy++,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,DarkImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dx>-Len;dx--,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,DarkImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
			for(;dy>-Len;dy--,Index++){
				CalcThresholdImageList(mx+dx,my+dy,SearchArea,DarkImageList,PL[Index],PH[Index],SL[Index],SH[Index],RL[Index],RH[Index]);
			}
		}
		//delete
		DeleteImageList(DarkImageList);
	}

	return true;
}

//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessingForResist1(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
	PixelInsData &P	=PixData[Y][X];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return false;
	}

	int	tx,ty;
	int mtX,mtY;
	int tmX,tmY;
	int SearchDot;
	int wNGThreshold;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		mtX	=mtY=0;
		tmX	=tmY=0;
		tx	=X;
		ty	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
	}
	else{
		//?p?b?h?c?C???c
		if(pAlignPage->GetBitFirstPickupFromMaster(X,Y)==true){
			return false;
		}
		//?V???N?c?C???c
		if(pAlignPage->GetBitPickupFromMaster(X,Y)==true){
			return false;
		}
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;

		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		tmX	=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY	=pAlignPage->GetShiftYFromTarget(X,Y);
		tx	=X+mtX;
		ty	=Y+mtY;
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;

	if(tx<0 || XLen<=tx){
		return false;
	}
	if(ty<0 || YLen<=ty){
		return false;
	}
	if(X-(SearchDot+1)<0 || XLen<=X+SearchDot+1){
		return false;
	}
	if(Y-(SearchDot+1)<0 || YLen<=Y+SearchDot+1){
		return false;
	}

	wThresholdRange=ThresholdRange+wNGThreshold;
	int PL,PH,SL,SH,RL,RH;
	int	wPL=P.PL-wThresholdRange;
	int	wPH=P.PH+wThresholdRange;
	int	wSL=P.SL-wThresholdRange;
	int	wSH=P.SH+wThresholdRange;
	int	wRL=P.RL-wThresholdRange;
	int	wRH=P.RH+wThresholdRange;

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(P.PL,P.PH,P.SL,P.SH,P.RL,P.RH,X,Y,0x0200000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x0400000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x0400000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x0400000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x0400000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData	&P1=PixData[Y][X];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	PixelInsData	P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x0800000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x0800000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x0800000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x0800000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
	}

	//?V???N?c?C???c
	if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true){
		return true;
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	PixelInsData &Pw=PixData[Y][X];
	if(Pw.PL-Q->P > 0){
		DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-Pw.PH > 0){
		DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	if(Pw.SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-Pw.SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(Pw.RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-Pw.RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(Pw.PL,Pw.PH,Pw.SL,Pw.SH,Pw.RL,Pw.RH,X,Y,0x1000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	SetReturnExecProcessing(wPL,wPH,wSL,wSH,wRL,wRH,X,Y,0x0100000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
	return true;
}

//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessingForResist2(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
	PixelInsData &P	=PixData[Y][X];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return false;
	}

	int	tx,ty;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	int wThresholdRange;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		mtX	=mtY=0;
		tx	=X;
		ty	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
	}
	else{
		//?p?b?h?c?C???c
		if(pAlignPage->GetBitFirstPickupFromMaster(X,Y)==true){
			return false;
		}
		//?V???N?c?C???c
		if(pAlignPage->GetBitPickupFromMaster(X,Y)==true){
			return false;
		}
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;

		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		tx	=X+mtX;
		ty	=Y+mtY;
	}
	if(tx-(SearchDot+1)<0 || XLen<=tx+SearchDot+1){
		return false;
	}
	if(ty-(SearchDot+1)<0 || YLen<=ty+SearchDot+1){
		return false;
	}
	if(X-(SearchDot+1)<0 || XLen<=X+SearchDot+1){
		return false;
	}
	if(Y-(SearchDot+1)<0 || YLen<=Y+SearchDot+1){
		return false;
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;
	wThresholdRange=ThresholdRange+wNGThreshold;

	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange;
	int	wPH	=P.PH+wThresholdRange;
	int	wSL	=P.SL-wThresholdRange;
	int	wSH	=P.SH+wThresholdRange;
	int	wRL	=P.RL-wThresholdRange;
	int	wRH	=P.RH+wThresholdRange;

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(ts,tx,ty,0x020000000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x040000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x040000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x040000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x040000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x080000000000,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x080000000000,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x080000000000,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x080000000000,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
	}

	//?V???N?c?C???c
	if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true){
		return true;
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	if(PL-Q->P > 0){
		DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-PH > 0){
		DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	if(SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(ts,X,Y,0x100000000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	SetReturnExecProcessing(ts,tx,ty,0x010000000000,Brightness,CoordX,CoordY,InspectResult);
	return true;
}

//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessingForResist3(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	bool CheckedSilk=false;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		tmX	=tmY=0;
		mtX	=mtY=0;
		mx	=X;
		my	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
	}
	else{
		//?p?b?h?c?C???c
		if(pAlignPage->GetBitFirstPickupFromTarget(X,Y)==true){
			return false;
		}
		//?V???N?c?C???c
		if(pAlignPage->GetBitPickupFromTarget(X,Y)==true){
			return false;
		}
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;

		tmX	=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY	=pAlignPage->GetShiftYFromTarget(X,Y);
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		mx	=X+tmX;
		my	=Y+tmY;
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;
	if(mx<0 || XLen<=mx){
		return false;
	}
	if(my<0 || YLen<=my){
		return false;
	}

REINS3_1_R:;
	PixelInsData &P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}

	wThresholdRange=ThresholdRange+wNGThreshold;
	int PL,PH,SL,SH,RL,RH;
	int	wPL=P.PL-wThresholdRange;
	int	wPH=P.PH+wThresholdRange;
	int	wSL=P.SL-wThresholdRange;
	int	wSH=P.SH+wThresholdRange;
	int	wRL=P.RL-wThresholdRange;
	int	wRH=P.RH+wThresholdRange;

	if((mx-SearchDot)<0 || XLen<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YLen<=(my+SearchDot)){
		return false;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X],ts[1][X],ts[2][X])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(P.PL,P.PH,P.SL,P.SH,P.RL,P.RH,mx,my,0x02000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x04000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x04000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x04000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x04000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData	&P1=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	PixelInsData	P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
	}

	//?V???N?c?C???c
	if(CheckedSilk==false && pAlignPage->GetBitPickupFromMaster(mx,my)==true){
		int wX=pAlignPage->GetShiftXFromMaster(mx,my);
		int wY=pAlignPage->GetShiftYFromMaster(mx,my);
		mx	=X-wX;
		my	=Y-wY;
		if(mx-SearchDot>=0 && XLen>mx+SearchDot && my-SearchDot>=0 && YLen>my+SearchDot){
			CheckedSilk=true;
			goto	REINS3_1_R;
		}
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	PixelInsData &Pw=PixData[my][mx];
	if(Pw.PL-Q->P > 0){
		DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-Pw.PH > 0){
		DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	if(Pw.SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-Pw.SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(Pw.RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-Pw.RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(Pw.PL,Pw.PH,Pw.SL,Pw.SH,Pw.RL,Pw.RH,mx,my,0x10000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	SetReturnExecProcessing(wPL,wPH,wSL,wSH,wRL,wRH,mx,my,0x01000000000000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
	return true;
}

//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessingForResist4(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	int wThresholdRange;
	bool CheckedSilk=false;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		tmX	=tmY=0;
		mtX	=mtY=0;
		mx	=X;
		my	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
	}
	else{
		//?p?b?h?c?C???c
		if(pAlignPage->GetBitFirstPickupFromTarget(X,Y)==true){
			return false;
		}
		//?V???N?c?C???c
		if(pAlignPage->GetBitPickupFromTarget(X,Y)==true){
			return false;
		}
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;

		tmX	=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY	=pAlignPage->GetShiftYFromTarget(X,Y);
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		mx	=X+tmX;
		my	=Y+tmY;
	}
	if(mx<0 || XLen<=mx){
		return false;
	}
	if(my<0 || YLen<=my){
		return false;
	}

REINS4_1_R:;
	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;
	PixelInsData	&P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}
	wThresholdRange=ThresholdRange+wNGThreshold;
	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange;
	int	wPH	=P.PH+wThresholdRange;
	int	wSL	=P.SL-wThresholdRange;
	int	wSH	=P.SH+wThresholdRange;
	int	wRL	=P.RL-wThresholdRange;
	int	wRH	=P.RH+wThresholdRange;

	if((mx-SearchDot)<0 || XLen<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YLen<=(my+SearchDot)){
		return false;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X],ts[1][X],ts[2][X])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(ts,X,Y,0x0200000000000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0400000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0400000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0400000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0400000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0800000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0800000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0800000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x0800000000000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?V???N?c?C???c
	if(CheckedSilk==false && pAlignPage->GetBitPickupFromMaster(mx,my)==true){
		int wX=pAlignPage->GetShiftXFromMaster(mx,my);
		int wY=pAlignPage->GetShiftYFromMaster(mx,my);
		mx	=X-wX;
		my	=Y-wY;
		if(mx-SearchDot>=0 && XLen>mx+SearchDot && my-SearchDot>=0 && YLen>my+SearchDot){
			CheckedSilk=true;
			goto	REINS4_1_R;
		}
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	if(PL-Q->P > 0){
		DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-PH > 0){
		DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	if(SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(ts,X,Y,0x1000000000000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	SetReturnExecProcessing(ts,X,Y,0x0100000000000000,Brightness,CoordX,CoordY,InspectResult);
	return true;
}

//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessing1(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
	PixelInsData &P	=PixData[Y][X];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return false;
	}

	int	tx,ty;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	bool IsSilk;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		mtX	=mtY=0;
		tx	=X;
		ty	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
		IsSilk		=false;
	}
	else{
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		tx	=X+mtX;
		ty	=Y+mtY;

		//?V???N?u?I?I?T?o?h?b?g
		if(pAlignPage->GetBitPickupFromMaster(X,Y)==true){
			SearchDot	=SearchDotBase+1;
			wNGThreshold=(NGThreshold<<1);
			IsSilk		=true;
			InspectResult|=0x20;
		}
		else{
			SearchDot	=SearchDotBase;
			wNGThreshold=NGThreshold;
			IsSilk		=false;
		}
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;

	if(tx<0 || XLen<=tx){
		return false;
	}
	if(ty<0 || YLen<=ty){
		return false;
	}
	if(X-(SearchDot+1)<0 || XLen<=X+SearchDot+1){
		return false;
	}
	if(Y-(SearchDot+1)<0 || YLen<=Y+SearchDot+1){
		return false;
	}

	wThresholdRange=ThresholdRange+wNGThreshold;
	int	wPL	=P.PL;
	int	wPH	=P.PH;
	int	wSL	=P.SL;
	int	wSH	=P.SH;
	int	wRL	=P.RL;
	int	wRH	=P.RH;
	int	PL	=P.PL-wThresholdRange;
	int	PH	=P.PH+wThresholdRange;
	int	SL	=P.SL-wThresholdRange;
	int	SH	=P.SH+wThresholdRange;
	int	RL	=P.RL-wThresholdRange;
	int	RH	=P.RH+wThresholdRange;

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		SetReturnExecProcessing(P.PL,P.PH,P.SL,P.SH,P.RL,P.RH,X,Y,0x02,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[Y+dy][X+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,X+dx,Y+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData	&P1=PixData[Y][X];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	PixelInsData	P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,0x08,X+dx,Y+dy,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[Y+dy][X+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,X+dx,Y+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
	}

	//?V???N?c?C???c
	if(IsSilk!=pAlignPage->GetBitPickupFromTarget(tx,ty)){
		return true;
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	PixelInsData &Pw=PixData[Y][X];
	if(Pw.PL-Q->P > 0){
		DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-Pw.PH > 0){
		DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	if(Pw.SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-Pw.SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(Pw.RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-Pw.RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(Pw.PL,Pw.PH,Pw.SL,Pw.SH,Pw.RL,Pw.RH,X,Y,0x10,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	SetReturnExecProcessing(wPL,wPH,wSL,wSH,wRL,wRH,X,Y,0x01,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
	return true;
}

//Master?a???c?cTarget?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessing2(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
	PixelInsData &P	=PixData[Y][X];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return false;
	}

	int	tx,ty;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	int wThresholdRange;
	bool IsSilk;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		mtX	=mtY=0;
		tx	=X;
		ty	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
		IsSilk		=false;
	}
	else{
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		tx	=X+mtX;
		ty	=Y+mtY;

		//?V???N?u?I?I?T?o?h?b?g
		if(pAlignPage->GetBitPickupFromMaster(X,Y)==true){
			SearchDot	=SearchDotBase+1;
			wNGThreshold=(NGThreshold<<1);
			IsSilk		=true;
			InspectResult|=0x2000;
		}
		else{
			SearchDot	=SearchDotBase;
			wNGThreshold=NGThreshold;
			IsSilk		=false;
		}
	}
	if(tx-(SearchDot+1)<0 || XLen<=tx+SearchDot+1){
		return false;
	}
	if(ty-(SearchDot+1)<0 || YLen<=ty+SearchDot+1){
		return false;
	}
	if(X-(SearchDot+1)<0 || XLen<=X+SearchDot+1){
		return false;
	}
	if(Y-(SearchDot+1)<0 || YLen<=Y+SearchDot+1){
		return false;
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;

	wThresholdRange=ThresholdRange+wNGThreshold;
	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange;
	int	wPH	=P.PH+wThresholdRange;
	int	wSL	=P.SL-wThresholdRange;
	int	wSH	=P.SH+wThresholdRange;
	int	wRL	=P.RL-wThresholdRange;
	int	wRH	=P.RH+wThresholdRange;

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(ts,tx,ty,0x0200,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			SetReturnExecProcessing(ts,tx+dx,ty+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
			return true;
		}
	}

	//?V???N?c?C???c
	if(IsSilk!=pAlignPage->GetBitPickupFromTarget(tx,ty)){
		return true;
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	if(PL-Q->P > 0){
		DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-PH > 0){
		DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	if(SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(ts,X,Y,0x1000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	SetReturnExecProcessing(ts,tx,ty,0x0100,Brightness,CoordX,CoordY,InspectResult);
	return true;
}

//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessing3(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult,int &wThresholdRange)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	bool IsSilk,CheckedSilk=false;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		tmX	=tmY=0;
		mtX	=mtY=0;
		mx	=X;
		my	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
		IsSilk		=false;
	}
	else{
		tmX	=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY	=pAlignPage->GetShiftYFromTarget(X,Y);
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		mx	=X+tmX;
		my	=Y+tmY;

		//?V???N?u?I?I?T?o?h?b?g
		if(pAlignPage->GetBitPickupFromTarget(X,Y)==true){
			SearchDot	=SearchDotBase+1;
			wNGThreshold=(NGThreshold<<1);
			IsSilk		=true;
			InspectResult|=0x200000;
		}
		else{
			SearchDot	=SearchDotBase;
			wNGThreshold=NGThreshold;
			IsSilk		=false;
		}
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;
	if(mx<0 || XLen<=mx){
		return false;
	}
	if(my<0 || YLen<=my){
		return false;
	}

REINS3_1:;
	PixelInsData &P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}

	wThresholdRange=ThresholdRange+wNGThreshold;
	int	wPL	=P.PL;
	int	wPH	=P.PH;
	int	wSL	=P.SL;
	int	wSH	=P.SH;
	int	wRL	=P.RL;
	int	wRH	=P.RH;
	int	PL	=P.PL-wThresholdRange;
	int	PH	=P.PH+wThresholdRange;
	int	SL	=P.SL-wThresholdRange;
	int	SH	=P.SH+wThresholdRange;
	int	RL	=P.RL-wThresholdRange;
	int	RH	=P.RH+wThresholdRange;

	if((mx-SearchDot)<0 || XLen<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YLen<=(my+SearchDot)){
		return false;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X],ts[1][X],ts[2][X])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		SetReturnExecProcessing(P.PL,P.PH,P.SL,P.SH,P.RL,P.RH,mx,my,0x020000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x040000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x040000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x040000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL	=P1.PL-ThresholdRange;
			PH	=P1.PH+ThresholdRange;
			SL	=P1.SL-ThresholdRange;
			SH	=P1.SH+ThresholdRange;
			RL	=P1.RL-ThresholdRange;
			RH	=P1.RH+ThresholdRange;
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(P1.PL,P1.PH,P1.SL,P1.SH,P1.RL,P1.RH,mx+dx,my+dy,0x040000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData	&P1=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	PixelInsData	P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,0x080000,mx+dx,my+dy,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x080000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x080000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x080000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
	}

	//?V???N?c?C???c
	if(CheckedSilk==false && IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my)){
		int wX=pAlignPage->GetShiftXFromMaster(mx,my);
		int wY=pAlignPage->GetShiftYFromMaster(mx,my);
		mx	=X-wX;
		my	=Y-wY;
		if(mx-SearchDot>=0 && XLen>mx+SearchDot && my-SearchDot>=0 && YLen>my+SearchDot){
			CheckedSilk=true;
			goto	REINS3_1;
		}
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	PixelInsData &Pw=PixData[my][mx];
	if(Pw.PL-Q->P > 0){
		DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-Pw.PH > 0){
		DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
	}
	if(Pw.SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-Pw.SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(Pw.RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-Pw.RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(Pw.PL,Pw.PH,Pw.SL,Pw.SH,Pw.RL,Pw.RH,mx,my,0x100000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}

	SetReturnExecProcessing(wPL,wPH,wSL,wSH,wRL,wRH,mx,my,0x010000,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
	return true;
}

//Target?a???c?cMaster?a???O?I?I?ÅE?A?I???ÅC
bool	PixelInspectionItem::GetExecProcessing4(int X,int Y,int SearchDotBase,int NGThreshold,int BrightnessRange,int InspectionLevel,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	int SearchDot;
	int wNGThreshold;
	int wThresholdRange;
	bool IsSilk,CheckedSilk=false;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		tmX	=tmY=0;
		mtX	=mtY=0;
		mx	=X;
		my	=Y;
		SearchDot	=SearchDotBase;
		wNGThreshold=NGThreshold;
		IsSilk		=false;
	}
	else{
		tmX	=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY	=pAlignPage->GetShiftYFromTarget(X,Y);
		mtX	=pAlignPage->GetShiftXFromMaster(X,Y);
		mtY	=pAlignPage->GetShiftYFromMaster(X,Y);
		mx	=X+tmX;
		my	=Y+tmY;

		//?V???N?u?I?I?T?o?h?b?g
		if(pAlignPage->GetBitPickupFromTarget(X,Y)==true){
			SearchDot	=SearchDotBase+1;
			wNGThreshold=(NGThreshold<<1);
			IsSilk		=true;
			InspectResult|=0x20000000;
		}
		else{
			SearchDot	=SearchDotBase;
			wNGThreshold=NGThreshold;
			IsSilk		=false;
		}
	}
	if(mx<0 || XLen<=mx){
		return false;
	}
	if(my<0 || YLen<=my){
		return false;
	}

REINS4_1:;
	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

	int ThresholdRange=256-InspectionLevel;
	PixelInsData	&P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}
	wThresholdRange=ThresholdRange+wNGThreshold;
	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange;
	int	wPH	=P.PH+wThresholdRange;
	int	wSL	=P.SL-wThresholdRange;
	int	wSH	=P.SH+wThresholdRange;
	int	wRL	=P.RL-wThresholdRange;
	int	wRH	=P.RH+wThresholdRange;

	if((mx-SearchDot)<0 || XLen<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YLen<=(my+SearchDot)){
		return false;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X],ts[1][X],ts[2][X])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		SetReturnExecProcessing(ts,X,Y,0x02000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x04000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x04000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x04000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x04000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x08000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x08000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(Y+dy);
		ts[1]=TargetImageList[1]->GetY(Y+dy);
		ts[2]=TargetImageList[2]->GetY(Y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x08000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(Y+dy);
			ts[1]=TargetImageList[1]->GetY(Y+dy);
			ts[2]=TargetImageList[2]->GetY(Y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][X+dx],ts[1][X+dx],ts[2][X+dx])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,X+dx,Y+dy,0x08000000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?V???N?c?C???c
	if(CheckedSilk==false && IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my)){
		int wX=pAlignPage->GetShiftXFromMaster(mx,my);
		int wY=pAlignPage->GetShiftYFromMaster(mx,my);
		mx	=X-wX;
		my	=Y-wY;
		if(mx-SearchDot>=0 && XLen>mx+SearchDot && my-SearchDot>=0 && YLen>my+SearchDot){
			CheckedSilk=true;
			goto	REINS4_1;
		}
	}

	//???ÅCe??l?A?I?ÅE?d?Z?o
	BYTE DiffPSR=0;
	if(PL-Q->P > 0){
		DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	else if(Q->P-PH > 0){
		DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
	}
	if(SL-Q->S > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->S-SH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	if(RL-Q->R > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	else if(Q->R-RH > 0){
		BYTE wDiffPSR;
		if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
			DiffPSR=wDiffPSR;
		}
	}
	//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
	if(DiffPSR<BrightnessRange){
		SetReturnExecProcessing(ts,X,Y,0x10000000,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	ts[0]=TargetImageList[0]->GetY(Y);
	ts[1]=TargetImageList[1]->GetY(Y);
	ts[2]=TargetImageList[2]->GetY(Y);
	SetReturnExecProcessing(ts,X,Y,0x01000000,Brightness,CoordX,CoordY,InspectResult);
	return true;
}

bool	PixelInspectionItem::GetTryExecProcessing1(int X,int Y,int SearchDot,int InspectionLevel,BYTE *pPL,BYTE *pPH,BYTE *pSL,BYTE *pSH,BYTE *pRL,BYTE *pRH,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult)
{
/*
	int tmX,tmY;
	BYTE *ts[3];
	if(pAlignPage==NULL){
		tmX=tmY=0;
	}
	else{
		tmX=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY=pAlignPage->GetShiftYFromTarget(X,Y);
	}
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

//	PixelInsData	P,P2,P3;
	int ThresholdRange=256-InspectionLevel;
	int	mx=X+tmX;
	if(mx<0 || XNumb<=mx){
		return false;
	}
	int	my=Y+tmY;
	if(my<0 || YNumb<=my){
		return false;
	}
	int Index=0;
	PixelInsData P;
	P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}
	BYTE wPL=pPL[Index];
	BYTE wPH=pPH[Index];
	BYTE wSL=pSL[Index];
	BYTE wSH=pSH[Index];
	BYTE wRL=pRL[Index];
	BYTE wRH=pRH[Index];
	int	PL=pPL[Index]-ThresholdRange;
	int	PH=pPH[Index]+ThresholdRange;
	int	SL=pSL[Index]-ThresholdRange;
	int	SH=pSH[Index]+ThresholdRange;
	int	RL=pRL[Index]-ThresholdRange;
	int	RH=pRH[Index]+ThresholdRange;

	if((mx-SearchDot)<0 || XNumb<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YNumb<=(my+SearchDot)){
		return false;
	}

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
	bool	IsTargetBlack=false;
	if((IsTargetBlack=(ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)) && (ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)){
		SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx,my,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx,my,0x02,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
		return true;
	}
	//?u?I?A?I?Å‚?f
	Index++;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++,Index++){
			if(IsTargetBlack==true && (ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
			P=PixData[my+dy][mx+dx];
			if(P.StdDisorder==255){
				continue;
			}
			PL=pPL[Index]-ThresholdRange;
			PH=pPH[Index]+ThresholdRange;
			SL=pSL[Index]-ThresholdRange;
			SH=pSH[Index]+ThresholdRange;
			RL=pRL[Index]-ThresholdRange;
			RH=pRH[Index]+ThresholdRange;

			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x10,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy<Len;dy++,Index++){
			if(IsTargetBlack==true && (ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
			P=PixData[my+dy][mx+dx];
			if(P.StdDisorder==255){
				continue;
			}
			PL=pPL[Index]-ThresholdRange;
			PH=pPH[Index]+ThresholdRange;
			SL=pSL[Index]-ThresholdRange;
			SH=pSH[Index]+ThresholdRange;
			RL=pRL[Index]-ThresholdRange;
			RH=pRH[Index]+ThresholdRange;

			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x10,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dx>-Len;dx--,Index++){
			if(IsTargetBlack==true && (ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
			P=PixData[my+dy][mx+dx];
			if(P.StdDisorder==255){
				continue;
			}
			PL=pPL[Index]-ThresholdRange;
			PH=pPH[Index]+ThresholdRange;
			SL=pSL[Index]-ThresholdRange;
			SH=pSH[Index]+ThresholdRange;
			RL=pRL[Index]-ThresholdRange;
			RH=pRH[Index]+ThresholdRange;

			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x10,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy>-Len;dy--,Index++){
			if(IsTargetBlack==true && (ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x04,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
			P=PixData[my+dy][mx+dx];
			if(P.StdDisorder==255){
				continue;
			}
			PL=pPL[Index]-ThresholdRange;
			PH=pPH[Index]+ThresholdRange;
			SL=pSL[Index]-ThresholdRange;
			SH=pSH[Index]+ThresholdRange;
			RL=pRL[Index]-ThresholdRange;
			RH=pRH[Index]+ThresholdRange;

			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(pPL[Index],pPH[Index],pSL[Index],pSH[Index],pRL[Index],pRH[Index],mx+dx,my+dy,0x10,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	Index=1;
//	P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	PixelInsData	P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++,Index++){
//			PixelInsData	&P2=PixData[my+dy][mx+dx];
//			if(CalcPixelInsData(P,P2,P3)==true){
			if(CalcPixelInsData(Index,pPL,pPH,pSL,pSH,pRL,pRH,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		for(;dy<Len;dy++,Index++){
//			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(Index,pPL,pPH,pSL,pSH,pRL,pRH,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		for(;dx>-Len;dx--,Index++){
//			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(Index,pPL,pPH,pSL,pSH,pRL,pRH,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
		for(;dy>-Len;dy--,Index++){
//			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(Index,pPL,pPH,pSL,pSH,pRL,pRH,P3)==true){
				int	PL3=P3.PL-ThresholdRange;
				int	PH3=P3.PH+ThresholdRange;
				int	SL3=P3.SL-ThresholdRange;
				int	SH3=P3.SH+ThresholdRange;
				int	RL3=P3.RL-ThresholdRange;
				int	RH3=P3.RH+ThresholdRange;
				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					SetReturnExecProcessing(P3.PL,P3.PH,P3.SL,P3.SH,P3.RL,P3.RH,mx+dx,my+dy,0x08,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
					return true;
				}
			}
		}
	}
	SetReturnExecProcessing(wPL,wPH,wSL,wSH,wRL,wRH,mx,my,0x01,rPL1,rPH1,rSL1,rSH1,rRL1,rRH1,CoordX,CoordY,InspectResult);
*/
	return true;
}

bool	PixelInspectionItem::GetTryExecProcessing2(int X,int Y,int SearchDot,int InspectionLevel,BYTE *pPL,BYTE *pPH,BYTE *pSL,BYTE *pSH,BYTE *pRL,BYTE *pRH,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
/*
	int tmX,tmY;
	if(pAlignPage==NULL){
		tmX=tmY=0;
	}
	else{
		tmX=pAlignPage->GetShiftXFromTarget(X,Y);
		tmY=pAlignPage->GetShiftYFromTarget(X,Y);
	}
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;

//	PixelInsData	P,P2,P3;
	int ThresholdRange=256-InspectionLevel;
	int	mx=X+tmX;
	if(mx<0 || XNumb<=mx){
		return false;
	}
	int	my=Y+tmY;
	if(my<0 || YNumb<=my){
		return false;
	}
	int Index=0;
	PixelInsData	&P=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?^?[?Q?b?g?A?W?c?c?}?X?^?[?A?W?E?a?3
	if(P.StdDisorder==255){
		return false;
	}
	int	PL=pPL[Index]-ThresholdRange;
	int	PH=pPH[Index]+ThresholdRange;
	int	SL=pSL[Index]-ThresholdRange;
	int	SH=pSH[Index]+ThresholdRange;
	int	RL=pRL[Index]-ThresholdRange;
	int	RH=pRH[Index]+ThresholdRange;

	if((mx-SearchDot)<0 || XNumb<=(mx+SearchDot)){
		return false;
	}
	if((my-SearchDot)<0 || YNumb<=(my+SearchDot)){
		return false;
	}

	bool	IsMasterBlack=false;
	if((IsMasterBlack=(ms[0][Index]<30 && ms[1][Index]<30 && ms[2][Index]<30)) && (ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)){
		SetReturnExecProcessing(ts,Index,X,Y,0x0400,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		SetReturnExecProcessing(ts,Index,X,Y,0x0200,Brightness,CoordX,CoordY,InspectResult);
		return true;
	}

	//?u?I?A?I?Å‚?f
	Index++;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++,Index++){
			if(IsMasterBlack==true && (ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x1000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy<Len;dy++,Index++){
			if(IsMasterBlack==true && (ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x1000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dx>-Len;dx--,Index++){
			if(IsMasterBlack==true && (ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x1000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy>-Len;dy--,Index++){
			if(IsMasterBlack==true && (ts[0][Index]<30 && ts[1][Index]<30 && ts[2][Index]<30)){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0400,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x1000,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	Index=1;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++,Index++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy<Len;dy++,Index++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dx>-Len;dx--,Index++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
		for(;dy>-Len;dy--,Index++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][Index],ts[1][Index],ts[2][Index])];
			int SS=((Q->S+Q2->S)>>1);
			int PP=((Q->P+Q2->P)>>1);
			int RR=((Q->R+Q2->R)>>1);
			if(PL<=PP && PP<=PH && SL<=SS && SS<=SH && RL<=RR && RR<=RH){
				SetReturnExecProcessing(ts,Index,X+dx,Y+dy,0x0800,Brightness,CoordX,CoordY,InspectResult);
				return true;
			}
		}
	}
	SetReturnExecProcessing(ts,0,X,Y,0x0100,Brightness,CoordX,CoordY,InspectResult);
*/
	return true;
}

void	PixelInspectionItem::SetReturnExecProcessing(BYTE *ts[],int x,int y,uint64 ResultFlag,BYTE Brightness[],int &CoordX,int &CoordY,uint64 &InspectResult)
{
	Brightness[0]=ts[0][x];
	Brightness[1]=ts[1][x];
	Brightness[2]=ts[2][x];
	CoordX=x;
	CoordY=y;
	InspectResult+=ResultFlag;
}

void	PixelInspectionItem::SetReturnExecProcessing(BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH,int mx,int my,uint64 ResultFlag,BYTE &rPL1,BYTE &rPH1,BYTE &rSL1,BYTE &rSH1,BYTE &rRL1,BYTE &rRH1,int &CoordX,int &CoordY,uint64 &InspectResult)
{
	rPL1=PL;
	rPH1=PH;
	rSL1=SL;
	rSH1=SH;
	rRL1=RL;
	rRH1=RH;
	CoordX=mx;
	CoordY=my;
	InspectResult|=ResultFlag;
}

void	PixelInspectionItem::Alloc(void)
{
	AllocX=GetDotPerLine();
	AllocY=GetMaxLines();

	if(PixData!=NULL){
		Release();
	}

	PixData=new PixelInsData*[AllocY];
	for(int y=0;y<AllocY;y++){
		PixData[y]=new PixelInsData[AllocX];
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<AllocY;y++){
			for(int x=0;x<AllocX;x++){
				PixData[y][x].PH=0;
				PixData[y][x].PL=255;
				PixData[y][x].SH=0;
				PixData[y][x].SL=255;
				PixData[y][x].RH=0;
				PixData[y][x].RL=255;
				PixData[y][x].StdDisorder=255;
			}
		}
	}
}

void	PixelInspectionItem::Release(void)
{
	if(PixData!=NULL){
		for(int y=0;y<AllocY;y++){
			delete	[]PixData[y];
		}
		delete	[]PixData;
	}
	wFPack=NULL;
	PixData=NULL;
}

void	PixelInspectionItem::AllocPixDataForResistSilk(void)
{
#ifdef Debug
	int i,j;
	int x,y;
	int Cnt;
	int MBmpCnt;
	BYTE	*MBmp;
	BYTE	*ms[3];
	DWORD	AddedP,AddedS,AddedR;		//?A?Z?l
	DWORD	Added2P,Added2S,Added2R;	//?Q?a?a
	BYTE DisP,DisS,DisR;
#endif

	//?}?X?^?[?a??
	GetMasterBuffList(MasterImageList);

	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	BYTE	**MaskBmp=GetAutoMaskBitmap();

	//???W?X?g?Ie??l?I?i?[???[?N?i?Å 
	if(PixDataForResistSilk[0]==NULL){
#ifdef Debug
		for(Cnt=0;Cnt<2;Cnt++){
#else
		for(int Cnt=0;Cnt<2;Cnt++){
#endif
			PixDataForResistSilk[Cnt]=new PixelInsData*[(YNumb>>8)+1];
#ifdef Debug
			for(i=0;i<=(YNumb>>8);i++){
#else
			for(int i=0;i<=(YNumb>>8);i++){
#endif
				PixDataForResistSilk[Cnt][i]=new PixelInsData[(XNumb>>8)+1];
			}
		}
	}
	//???W?X?g?Ie??l?I?i?[???[?N???u?Å‚
#ifdef Debug
	for(Cnt=0;Cnt<2;Cnt++){
		for(i=0;i<=(YNumb>>8);i++){
			for(j=0;j<=(XNumb>>8);j++){
#else
	for(int Cnt=0;Cnt<2;Cnt++){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<=(YNumb>>8);i++){
				for(int j=0;j<=(XNumb>>8);j++){
#endif
					PixDataForResistSilk[Cnt][i][j].PL=0;
					PixDataForResistSilk[Cnt][i][j].PH=255;
					PixDataForResistSilk[Cnt][i][j].SL=0;
					PixDataForResistSilk[Cnt][i][j].SH=255;
					PixDataForResistSilk[Cnt][i][j].RL=0;
					PixDataForResistSilk[Cnt][i][j].RH=255;
					PixDataForResistSilk[Cnt][i][j].StdDisorder=0;
				}
			}
#ifndef Debug
		}
#endif
	}
	//???W?X?g?Ie??l?d?i?Å 
	if(pAlignPage!=NULL && MaskBmp!=NULL){
#ifdef Debug
		for(Cnt=0;Cnt<2;Cnt++){
			for(i=0;i<=(YNumb>>8);i++){
				for(j=0;j<=(XNumb>>8);j++){
#else
		for(int Cnt=0;Cnt<2;Cnt++){
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<=(YNumb>>8);i++){
					for(int j=0;j<=(XNumb>>8);j++){
						int MBmpCnt;
						DWORD	AddedP,AddedS,AddedR;		//?A?Z?l
						DWORD	Added2P,Added2S,Added2R;	//?Q?a?a
#endif
						MBmpCnt=0;
						AddedP	=AddedS	=AddedR	=0;
						Added2P	=Added2S=Added2R=0;
#ifdef Debug
						for(y=(i<<8);y<((i+1)<<8) && y<YNumb;y++){
							MBmp=MaskBmp[y];
#else
						for(int y=(i<<8);y<((i+1)<<8) && y<YNumb;y++){
							BYTE	*MBmp=MaskBmp[y];
#endif
							if(MBmp==NULL){
								continue;
							}
#ifdef Debug
							for(x=(j<<8);x<((j+1)<<8) && x<XNumb;x++){
#else
							for(int x=(j<<8);x<((j+1)<<8) && x<XNumb;x++){
#endif
								if((MBmp[x>>3]&(0x80>>(x&7)))!=0){
									if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
										continue;
									}
									if(Cnt==_Resist){
										if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
											continue;
										}
									}
									else if(Cnt==_Silk){
										if(pAlignPage->GetBitPickupFromMaster(x,y)==false){
											continue;
										}
									}
#ifndef Debug
									BYTE *ms[3];
#endif
									ms[0]=MasterImageList[0]->GetY(y);
									ms[1]=MasterImageList[1]->GetY(y);
									ms[2]=MasterImageList[2]->GetY(y);
									struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(ms[0][x],ms[1][x],ms[2][x])];
									AddedP	+=P->P;
									Added2P	+=P->P*P->P;
									AddedS	+=P->S;
									Added2S	+=P->S*P->S;
									AddedR	+=P->R;
									Added2R	+=P->R*P->R;
									MBmpCnt++;
								}
							}
						}
						if(MBmpCnt==0){
							continue;
						}
#ifndef Debug
						BYTE DisP,DisS,DisR;
#endif
						DisP=GetDisorder(AddedP,Added2P,MBmpCnt);
						DisS=GetDisorder(AddedS,Added2S,MBmpCnt);
						DisR=GetDisorder(AddedR,Added2R,MBmpCnt);
						PixDataForResistSilk[Cnt][i][j].PL=GetAvr(AddedP,MBmpCnt)-DisP;
						PixDataForResistSilk[Cnt][i][j].PH=GetAvr(AddedP,MBmpCnt)+DisP;
						PixDataForResistSilk[Cnt][i][j].SL=GetAvr(AddedS,MBmpCnt)-DisS;
						PixDataForResistSilk[Cnt][i][j].SH=GetAvr(AddedS,MBmpCnt)+DisS;
						PixDataForResistSilk[Cnt][i][j].RL=GetAvr(AddedR,MBmpCnt)-DisR;
						PixDataForResistSilk[Cnt][i][j].RH=GetAvr(AddedR,MBmpCnt)+DisR;
						PixDataForResistSilk[Cnt][i][j].StdDisorder=DisR;
					}
				}
#ifndef Debug
			}
#endif
		}
	}
}

void	PixelInspectionItem::DeleteImageList(ImageBuffer *ImageList[])
{
	for(int i=0;i<3;i++){
		if(ImageList[i]!=NULL){
			delete ImageList[i];
			ImageList[i]=NULL;
		}
	}
}

///////////////////////////////
//	?F?A?P?x?I?Å‚?I??
///////////////////////////////
ExeResult	PixelInspectionItem::ExecuteScanning(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	//?X?L?????n???I?a??
	int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

	//?P?X?L?????U?E?Q?X?L?????U?I?A?}?X?^?[?a???E?i?A?3?É ?a???E?I?A?o?I?ÅE
	if(CurrentMasterCnt<2){
		return _ER_true;
	}

	//?s?N?Z?????C?u?????d?a??
	int	DefaultLibID=((PixelInspectionBase *)GetParentBase())->getDefaultLibraryID();
	CmdGetPixelInspectionLibraryListPacket	packet(GetLayersBase());
	AlgorithmLibraryList *p=NULL;
	if(GetPixelInspectionLibrary(&packet)==true){
		for(p=packet.AList.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GetLibID()==DefaultLibID)
				break;
		}
	}
	if(p==NULL){
		return _ER_true;
	}
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	AlgorithmLibraryLevelContainer	LLib(Container);
	//PixelInspectionLibrary PLib(GetOrigin()->GetLibType(),GetLayersBase());
	if(GetLibraryContainer()->GetLibrary(p->GetLibID(),LLib)==false){
		return _ER_true;
	}

/*
	//?s?N?Z?????C?u?????I?A?e?}?X?N?d?a??
	ConstBitBuffer MaskMap;
	GetParentInPage()->GetMaskBitmap(MaskMap,&PLib);
	const BYTE	**MaskBitmap=MaskMap.GetBitMap();
*/
	//?R?X?L?????U?i?}?X?^?[?o?^?P???U?j
	if(CurrentMasterCnt==2){
		//AutoAlignment?I?A?N?o?É 
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
		if(ABase!=NULL){
			AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
			if(APage!=NULL){
				pAlignPage=dynamic_cast<AutoAlignmentInPage *>(APage);
			}
		}
		//?s?N?Z?????C?u?????I?A?e?}?X?N?d?a??
		MaskBitmap=GetMaskBitmap();
		if(MaskBitmap==NULL){
			return _ER_true;
		}
		PickupFlexArea((BYTE **)MaskBitmap,XByte,XLen,YLen,MaskBitmapFPack);
		//?}?X?^?[?a???d?v?Z
		GetMasterBuffList(MasterImageList);
		GetLeastSquaresMethodM(MasterImageList,MLeastSquaresMethodTable);
	}
	//?s?N?Z?????C?u?????I?A?e?}?X?N?I?L?3?d?m?F
	if(MaskBitmap==NULL){
		return _ER_true;
	}
	//?^?[?Q?b?g?a???d?v?Z?É ?A?P?x?a?3
	GetTargetBuffList(TargetImageList);
	GetLeastSquaresMethodT(TargetImageList,MLeastSquaresMethodTable,TLeastSquaresMethodTable);

	return _ER_true;
}

//?A?Å ?n?a?@?d?g?p?É ?A?A?P?x?I?Q???3???E?d?i?Å ?i?}?X?^?[?a???j
void	PixelInspectionItem::GetLeastSquaresMethodM(ImageBuffer *Buffer[],LeastSquaresMethodStruct *Least[])
{
	int MaskBitmapFPackNumb=MaskBitmapFPack.GetCount();
	int LayerNumb=GetLayerNumb();
	for(int i=0;i<LayerNumb;i++){
		if(Least[i]!=NULL){
			delete Least[i];
		}
		Least[i]=new struct LeastSquaresMethodStruct[MaskBitmapFPackNumb];
		int Cnt=0;
		for(PureFlexAreaList *c=MaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
			uint64	B;
			uint32	C,D,E;
			B=C=D=E=0;
			int	Len	=c->GetFLineLen();
			for(int j=0;j<Len;j++){
				int SumBrightness=0;
				int x1=c->GetFLineLeftX (j);
				int x2=c->GetFLineRightX(j);
				int y =c->GetFLineAbsY  (j);
				for(int x=x1;x<x2;x++){
					int	X,Y;
					X=x;
					Y=y;
					BYTE *Buff=Buffer[i]->GetY(Y);
					SumBrightness+=Buff[X];
				}
				int AvrBrightness=SumBrightness/(x2-x1);
///				A+=AvrBrightness*AvrBrightness;
				B+=y*y;
				C+=AvrBrightness;
				D+=y*AvrBrightness;
				E+=y;
			}
			int64 LenBEE;
			if((LenBEE=(Len*B-E*E))==0){
				Least[i][Cnt].a=0;
				Least[i][Cnt].b=C/Len;
			}
			else{
				Least[i][Cnt].a=(double)(Len*D-C*E)/LenBEE;
				Least[i][Cnt].b=(B*C-D*E)/LenBEE;
			}
		}
	}
}

//?A?Å ?n?a?@?d?g?p?É ?A?A?P?x?I?Q???3???E?d?i?Å ?i?^?[?Q?b?g?a???j
void	PixelInspectionItem::GetLeastSquaresMethodT(ImageBuffer *Buffer[],LeastSquaresMethodStruct *LeastM[],LeastSquaresMethodStruct *LeastT[])
{
	int MaskBitmapFPackNumb=MaskBitmapFPack.GetCount();
	int LayerNumb=GetLayerNumb();
	for(int i=0;i<LayerNumb;i++){
		if(LeastT[i]!=NULL){
			delete LeastT[i];
		}
		LeastT[i]=new struct LeastSquaresMethodStruct[MaskBitmapFPackNumb];
		int Cnt=0;
		for(PureFlexAreaList *c=MaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
			uint64	B;
			uint32	C,D,E;
			B=C=D=E=0;
			int	Len	=c->GetFLineLen();
			for(int j=0;j<Len;j++){
				int SumBrightness=0;
				int x1=c->GetFLineLeftX (j);
				int x2=c->GetFLineRightX(j);
				int y =c->GetFLineAbsY  (j);
				for(int x=x1;x<x2;x++){
					int	X,Y;
					X=x+pAlignPage->GetShiftXFromMaster(x,y);
					Y=y+pAlignPage->GetShiftYFromMaster(x,y);
					BYTE *Buff=Buffer[i]->GetY(Y);
					SumBrightness+=Buff[X];
				}
				int AvrBrightness=SumBrightness/(x2-x1);
///				A+=AvrBrightness*AvrBrightness;
				B+=y*y;
				C+=AvrBrightness;
				D+=y*AvrBrightness;
				E+=y;
			}
			int64 LenBEE;
			if((LenBEE=(Len*B-E*E))==0){
				LeastT[i][Cnt].a=0;
				LeastT[i][Cnt].b=C/Len;
			}
			else{
				LeastT[i][Cnt].a=(double)(Len*D-C*E)/LenBEE;
				LeastT[i][Cnt].b=(B*C-D*E)/LenBEE;
			}
		}

		Cnt=0;
		for(PureFlexAreaList *c=MaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
			//?P?x?a?3
			int	Len	=c->GetFLineLen();
			for(int j=0;j<Len;j++){
				int x1=c->GetFLineLeftX (j);
				int x2=c->GetFLineRightX(j);
				int y =c->GetFLineAbsY  (j);
				int MBrightness=LeastM[i][Cnt].a*y+LeastM[i][Cnt].b;
				int TBrightness=LeastT[i][Cnt].a*y+LeastT[i][Cnt].b;
				//Target?c?cMaster?O?I?P?x?I?ÅE?W???d?Z?o
				double TMBrightCoef=(double)MBrightness/TBrightness;
				for(int x=x1;x<x2;x++){
					int	X,Y;
					X=x+pAlignPage->GetShiftXFromMaster(x,y);
					Y=y+pAlignPage->GetShiftYFromMaster(x,y);
					BYTE	*ps=Buffer[i]->GetY(Y)+X;
					*ps=Clip255((*ps)*TMBrightCoef);
				}
			}
		}
	}
}

ExeResult	PixelInspectionItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),5);
	GetLayersBase()->StepProcessing(GetPage());

	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID,ThreadNo,Res,EInfo);

	CurrentMasterCounter=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);
	if(CurrentMasterCounter!=99999999){
		return Ret;
	}

	if(NGBitmap!=NULL){
		if(XByte!=((GetDotPerLine()+7)/8) || YLen!=GetMaxLines()){
			DeleteMatrixBuff(NGBitmap,YLen);
			NGBitmap=NULL;
		}
	}
	if(NGBitmap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		YLen	=GetMaxLines();
		NGBitmap=MakeMatrixBuff(XByte,YLen);
	}
	if(InsCheckedBitmap!=NULL){
		if(XByte!=((GetDotPerLine()+7)/8) || YLen!=GetMaxLines()){
			DeleteMatrixBuff(InsCheckedBitmap,YLen);
			InsCheckedBitmap=NULL;
		}
	}
	if(InsCheckedBitmap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		YLen	=GetMaxLines();
		InsCheckedBitmap=MakeMatrixBuff(XByte,YLen);
	}
	if(TempNGBitmap!=NULL){
		if(XByte!=((GetDotPerLine()+7)/8) || YLen!=GetMaxLines()){
			DeleteMatrixBuff(TempNGBitmap,YLen);
			TempNGBitmap=NULL;
		}
	}
	if(TempNGBitmap==NULL){
		XByte	=(GetDotPerLine()+7)/8;
		YLen	=GetMaxLines();
		TempNGBitmap=MakeMatrixBuff(XByte,YLen);
	}
	XLen=GetDotPerLine();
	YLen=GetMaxLines();

	//AutoAlignment?I?A?N?o?É 
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(GetPage());
		if(APage!=NULL){
			pAlignPage=dynamic_cast<AutoAlignmentInPage *>(APage);
		}
	}

	//AutoPCBHoleAligner?I?A?N?o?É 
	ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(GetPage());
		if(APage!=NULL){
			pHoleAlignPage=dynamic_cast<AutoPCBHoleAlignerInPage *>(APage);
		}
	}

	//VCutInspection?I?A?N?o?É 
	ABase=GetLayersBase()->GetAlgorithmBase(/**/"PCB",/**/"VCutInspection");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(GetPage());
		if(APage!=NULL){
			pVCutPage=dynamic_cast<VCutInspectionInPage *>(APage);
		}
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	PoleTable=PData->PoleTable;

	//?}?X?^?[?f?[?^?dLoad?É ?????a?I?e??
	if(LoadedFlag==true){
		LoadedFlag=false;
		return Ret;
	}
	if(ExecuteInitialAfterEditFlag == true) // phase function
		return Ret;
	//ExecuteAlignment?d?A?s
	GetLayersBase()->ExecuteStartByInspection	(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecutePreAlignment		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecuteAlignment			(GetLayersBase()->GetEntryPoint());

	Release();
	Alloc();

	//AverageImage Buffer
	//if(GetAverageBuffList(AverageImageList)==false){ // This function deletes MasterImage and is always false.
		GetMasterBuffList(AverageImageList);
	//}

	GetLayersBase()->StepProcessing(GetPage());
	MakeTable();
	GetLayersBase()->StepProcessing(GetPage());
	MakeTableForLight();
	GetLayersBase()->StepProcessing(GetPage());
	MakeTableForDark();
	GetLayersBase()->StepProcessing(GetPage());

	ExecuteInitialAfterEditFlag = true;

	return Ret;
}

bool	PixelInspectionItem::ManualExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
{
	//Enable
	if(GetThresholdR()->Enable==false){
		return true;
	}

	XByte	=(GetDotPerLine()+7)/8;
	XLen	=GetDotPerLine();
	YLen	=GetMaxLines();

	//AutoAlignment?I?A?N?o?É 
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
		if(APage!=NULL){
			pAlignPage=dynamic_cast<AutoAlignmentInPage *>(APage);
		}
	}

	//AutoPCBHoleAligner?I?A?N?o?É 
	ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
		if(APage!=NULL){
			pHoleAlignPage=dynamic_cast<AutoPCBHoleAlignerInPage *>(APage);
		}
	}

	//VCutInspection?I?A?N?o?É 
	ABase=GetLayersBase()->GetAlgorithmBase(/**/"PCB",/**/"VCutInspection");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
		if(APage!=NULL){
			pVCutPage=dynamic_cast<VCutInspectionInPage *>(APage);
		}
	}

	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	PoleTable=PData->PoleTable;

	//?}?X?^?[?f?[?^?dLoad?É ?????a?I?e??
	if(LoadedFlag==true){
		LoadedFlag=false;
		return true;
	}
/*
	//ExecuteAlignment?d?A?s
	GetLayersBase()->ExecuteStartByInspection	(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecutePreAlignment		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecuteAlignment			(GetLayersBase()->GetEntryPoint());
*/
	//FlexArea	area;
	//area.SetRectangle(0,0,AllocX,AllocY);
	//SetArea(area);

	//AverageImage Buffer
	if(GetAverageBuffList(AverageImageList)==false){
		GetMasterBuffList(AverageImageList);
	}

	//?!???A???S???Y?Ä?I??
	ManualMakeTableForLight();
	ManualMakeTableForDark();
	ManualMakeTable();

	return true;
}

BYTE	**PixelInspectionItem::GetAutoMaskBitmap(void)
{
//	AutoMaskingPIBase	*LBase=(AutoMaskingPIBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(LBase!=NULL){
		AlgorithmInPageRoot	*LPI=LBase->GetPageData(GetPage());
		CmdCreateAutoMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*LPI=ABase->GetPageData(GetPage());
		CmdCreateMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	return NULL;
}

bool	PixelInspectionItem::GetLightBuffList(ImageBuffer *ImageList[])
{
	//delete
	DeleteImageList(ImageList);

	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		CmdLightImageStatistic	Cmd(GetLayersBase());
		Cmd.XLen			=GetDotPerLine();
		Cmd.YLen			=GetMaxLines();
		Cmd.CurrentPageNumb	=GetPage();
		Cmd.LightImageList	=ImageList;
		MBase->TransmitDirectly(&Cmd);
		return Cmd.IsLightImage;
	}
	return false;
}

bool	PixelInspectionItem::GetDarkBuffList(ImageBuffer *ImageList[])
{
	//delete
	DeleteImageList(ImageList);

	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		CmdDarkImageStatistic	Cmd(GetLayersBase());
		Cmd.XLen			=GetDotPerLine();
		Cmd.YLen			=GetMaxLines();
		Cmd.CurrentPageNumb	=GetPage();
		Cmd.DarkImageList	=ImageList;
		MBase->TransmitDirectly(&Cmd);
		return Cmd.IsDarkImage;
	}
	return false;
}

bool	PixelInspectionItem::GetDisorderBuffList(ImageBuffer *ImageList[])
{
	//delete
	DeleteImageList(ImageList);

	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		CmdDisorderImageStatistic	Cmd(GetLayersBase());
		Cmd.XLen				=GetDotPerLine();
		Cmd.YLen				=GetMaxLines();
		Cmd.CurrentPageNumb		=GetPage();
		Cmd.DisorderImageList	=ImageList;
		MBase->TransmitDirectly(&Cmd);
		return Cmd.IsDisorderImage;
	}
	return false;
}

bool	PixelInspectionItem::GetAverageBuffList(ImageBuffer *ImageList[])
{
	//delete
	DeleteImageList(ImageList);

	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		CmdAverageImageStatistic	Cmd(GetLayersBase());
		Cmd.XLen				=GetDotPerLine();
		Cmd.YLen				=GetMaxLines();
		Cmd.CurrentPageNumb		=GetPage();
		Cmd.AverageImageList	=ImageList;
		MBase->TransmitDirectly(&Cmd);
		return Cmd.IsAverageImage;
	}
	return false;
}

bool	PixelInspectionItem::CalcThresholdImageList(int X,int Y,int SearchArea,ImageBuffer *ImageList[],BYTE &PL,BYTE &PH,BYTE &SL,BYTE &SH,BYTE &RL,BYTE &RH)
{
	PixelInspectionInPage *PData=(PixelInspectionInPage *)GetParentInPage();
	struct	PixelPoleMatrixStruct	*PoleTable=PData->PoleTable;
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	if((X-SearchArea)<0 || XNumb<=(X+SearchArea)){
		return false;
	}
	if((Y-SearchArea)<0 || YNumb<=(Y+SearchArea)){
		return false;
	}
	PixelInsData	*PixD=PixData[Y];
	for(int i=-SearchArea;i<=SearchArea;i++){
		BYTE	*ms[3];
		ms[0]=ImageList[0]->GetY(Y+i)+X;
		ms[1]=ImageList[1]->GetY(Y+i)+X;
		ms[2]=ImageList[2]->GetY(Y+i)+X;
//		BYTE	*ds[3];
//		ds[0]=DisorderImageList[0]->GetY(Y+i)+X;
//		ds[1]=DisorderImageList[1]->GetY(Y+i)+X;
//		ds[2]=DisorderImageList[2]->GetY(Y+i)+X;
		for(int j=-SearchArea;j<=SearchArea;j++){
			struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
			if(PL>P->P){
				PL=P->P;
			}
			if(PH<P->P){
				PH=P->P;
			}
			if(SL>P->S){
				SL=P->S;
			}
			if(SH<P->S){
				SH=P->S;
			}
			if(RL>P->R){
				RL=P->R;
			}
			if(RH<P->R){
				RH=P->R;
			}
//			//?Å‚?I?s?N?Z???E?u(x,y)?I?W?Ä?I?ÅE?d???s?e
//			BYTE StdDisorder=((double)((ds[0][j]))/((ms[0][j]))+(double)((ds[1][j]))/((ms[1][j]))+(double)((ds[2][j]))/((ms[2][j])))*sqrt((((ms[0][j]))*((ms[0][j]))+((ms[1][j]))*((ms[1][j]))+((ms[2][j]))*((ms[2][j])))/3.0)/3.0;
//			if(PixD[X].StdDisorder<StdDisorder){
//				PixD[X].StdDisorder=StdDisorder;
//			}
		}
	}
	return true;
}

PixelStatisticInLayer	**PixelInspectionItem::GetStatisticBuff(void)
{
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		CmdStatisticBuff	Cmd(GetLayersBase());
		MBase->TransmitDirectly(&Cmd);
		return Cmd.StatisticBuff;
	}
	return NULL;
}

bool	PixelInspectionItem::GetPixelInspectionLibrary(GUIDirectMessage *CmdPacket)
{
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	if(MBase!=NULL){
		CmdGetPixelInspectionLibraryListPacket	*Packet=dynamic_cast<CmdGetPixelInspectionLibraryListPacket *>(CmdPacket);
		if(Packet!=NULL){
			Packet->LibFolderID=-1;
			MBase->TransmitDirectly(Packet);
			return true;
		}
	}
	return false;
}

void	PixelInspectionItem::MakeTable(void)
{
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
//	int	SearchArea=1;
	int wSearchArea=((PixelInspectionBase *)GetParentBase())->getSearchAreaForMakeTable();

	if(Colored==true){
		if(GetDisorderBuffList(DisorderImageList)==true){
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YNumb;y++){
					BYTE	*MBmp=NULL;
					if(MaskBmp!=NULL){
						MBmp=MaskBmp[y];
						PixelInsData	*PixD=PixData[y];
						for(int x=0;x<XNumb;x++){
							//?V???N?u?I?I?T?o?h?b?g
							int SearchArea=wSearchArea;
							if(pAlignPage!=NULL){
								if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
									SearchArea=wSearchArea+1;
								}
							}
							//???u?I?I?T?o?h?b?g
							if(pHoleAlignPage!=NULL){
								if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
									SearchArea=wSearchArea+1;
								}
							}
							if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
								continue;
							}
							if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
								continue;
							}
							if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
								continue;
							}
							if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
								continue;
							}
							for(int i=-SearchArea;i<=SearchArea;i++){
								BYTE	*ms[3];
								ms[0]=AverageImageList[0]->GetY(y+i)+x;
								ms[1]=AverageImageList[1]->GetY(y+i)+x;
								ms[2]=AverageImageList[2]->GetY(y+i)+x;
								BYTE	*ds[3];
								ds[0]=DisorderImageList[0]->GetY(y+i)+x;
								ds[1]=DisorderImageList[1]->GetY(y+i)+x;
								ds[2]=DisorderImageList[2]->GetY(y+i)+x;
								for(int j=-SearchArea;j<=SearchArea;j++){
									struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
									if(PixD[x].PL>P->P){
										PixD[x].PL=P->P;
									}
									if(PixD[x].PH<P->P){
										PixD[x].PH=P->P;
									}
									if(PixD[x].SL>P->S){
										PixD[x].SL=P->S;
									}
									if(PixD[x].SH<P->S){
										PixD[x].SH=P->S;
									}
									if(PixD[x].RL>P->R){
										PixD[x].RL=P->R;
									}
									if(PixD[x].RH<P->R){
										PixD[x].RH=P->R;
									}
									//???S?s?N?Z???E?u(x,y)?I?W?Ä?I?ÅE?d???s?e
									if(i==0 && j==0){
//										PixD[x].StdDisorder=((double)((ds[0][j]))/((ms[0][j]))+(double)((ds[1][j]))/((ms[1][j]))+(double)((ds[2][j]))/((ms[2][j])))*sqrt((((ms[0][j]))*((ms[0][j]))+((ms[1][j]))*((ms[1][j]))+((ms[2][j]))*((ms[2][j])))/3.0)/3.0;
										PixD[x].StdDisorder=(double)(ds[0][j]+ds[1][j]+ds[2][j])/3.0+0.5;
										//?W?Ä?I?ÅE?I?I???I?e?O?Å˜?Ibit?E?p?b?h?c?C???c?I?Å‚?f?d?????1?e
										if(pAlignPage!=NULL){
											if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
												PixD[x].StdDisorder|=0x80;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//delete
			DeleteImageList(DisorderImageList);
		}
		else{
			//???I?a???a?3?Åë?e??
			GetMasterBuffList(MasterImageList);
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YNumb;y++){
					int SearchArea=wSearchArea;
					BYTE	*MBmp=NULL;
					if(MaskBmp!=NULL){
						MBmp=MaskBmp[y];
						PixelInsData	*PixD=PixData[y];
						for(int x=0;x<XNumb;x++){
							//?V???N?u?I?I?T?o?h?b?g
							SearchArea=wSearchArea;
							if(pAlignPage!=NULL){
								if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
									SearchArea=wSearchArea+1;
								}
							}
							//???u?I?I?T?o?h?b?g
							if(pHoleAlignPage!=NULL){
								if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
									SearchArea=wSearchArea+1;
								}
							}
							if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
								continue;
							}
							if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
								continue;
							}
							if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
								continue;
							}
							if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
								continue;
							}
							//?Å‚?I?s?N?Z???E?u(x,y)?I?W?Ä?I?ÅE?d?O?E?ÅE?e
							PixD[x].StdDisorder=0;
							for(int i=-SearchArea;i<=SearchArea;i++){
								BYTE	*ms[3];
								ms[0]=MasterImageList[0]->GetY(y+i)+x;
								ms[1]=MasterImageList[1]->GetY(y+i)+x;
								ms[2]=MasterImageList[2]->GetY(y+i)+x;
								for(int j=-SearchArea;j<=SearchArea;j++){
									struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
									if(PixD[x].PL>P->P){
										PixD[x].PL=P->P;
									}
									if(PixD[x].PH<P->P){
										PixD[x].PH=P->P;
									}
									if(PixD[x].SL>P->S){
										PixD[x].SL=P->S;
									}
									if(PixD[x].SH<P->S){
										PixD[x].SH=P->S;
									}
									if(PixD[x].RL>P->R){
										PixD[x].RL=P->R;
									}
									if(PixD[x].RH<P->R){
										PixD[x].RH=P->R;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//???W?X?g?Ie??l?I?i?[???[?N?i?Å 
	AllocPixDataForResistSilk();
}

void	PixelInspectionItem::MakeTableForLight(void)
{
	if(GetLightBuffList(LightImageList)==false){
		return;
	}
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
//	int	SearchArea=1;
	int wSearchArea=((PixelInspectionBase *)GetParentBase())->getSearchAreaForMakeTable();

#ifdef Debug
	int x,y;
	BYTE	*MBmp;
	PixelInsData	*PixD;
	BYTE	*ms[3];
	int i,j;
	int SearchArea;
	if(Colored==true){
//		#pragma omp parallel
//		{
//			#pragma omp for
			for(y=0;y<YNumb;y++){
				MBmp=NULL;
				if(MaskBmp!=NULL){
					MBmp=MaskBmp[y];
					PixD=PixData[y];
					for(x=0;x<XNumb;x++){
						if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
							continue;
						}
						//?V???N?u?I?I?T?o?h?b?g
						SearchArea=wSearchArea;
						if(pAlignPage!=NULL){
							if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						//???u?I?I?T?o?h?b?g
						if(pHoleAlignPage!=NULL){
							if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
							continue;
						}
						if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
							continue;
						}
						if(y==DebugPointY && x==DebugPointX){
							DebugPoint++;
						}
						for(i=-SearchArea;i<=SearchArea;i++){
							ms[0]=LightImageList[0]->GetY(y+i)+x;
							ms[1]=LightImageList[1]->GetY(y+i)+x;
							ms[2]=LightImageList[2]->GetY(y+i)+x;
							for(j=-SearchArea;j<=SearchArea;j++){
								struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
								if(PixD[x].PL>P->P){
									PixD[x].PL=P->P;
								}
								if(PixD[x].PH<P->P){
									PixD[x].PH=P->P;
								}
								if(PixD[x].SL>P->S){
									PixD[x].SL=P->S;
								}
								if(PixD[x].SH<P->S){
									PixD[x].SH=P->S;
								}
								if(PixD[x].RL>P->R){
									PixD[x].RL=P->R;
								}
								if(PixD[x].RH<P->R){
									PixD[x].RH=P->R;
								}
							}
						}
					}
				}
			}
//		}
	}
#else
	if(Colored==true){
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*MBmp=NULL;
				if(MaskBmp!=NULL){
					MBmp=MaskBmp[y];
					PixelInsData	*PixD=PixData[y];
					for(int x=0;x<XNumb;x++){
						if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
							continue;
						}
						//?V???N?u?I?I?T?o?h?b?g
						int SearchArea=wSearchArea;
						if(pAlignPage!=NULL){
							if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						//???u?I?I?T?o?h?b?g
						if(pHoleAlignPage!=NULL){
							if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
							continue;
						}
						if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
							continue;
						}
						for(int i=-SearchArea;i<=SearchArea;i++){
							BYTE	*ms[3];
							ms[0]=LightImageList[0]->GetY(y+i)+x;
							ms[1]=LightImageList[1]->GetY(y+i)+x;
							ms[2]=LightImageList[2]->GetY(y+i)+x;
							for(int j=-SearchArea;j<=SearchArea;j++){
								struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
								if(PixD[x].PL>P->P){
									PixD[x].PL=P->P;
								}
								if(PixD[x].PH<P->P){
									PixD[x].PH=P->P;
								}
								if(PixD[x].SL>P->S){
									PixD[x].SL=P->S;
								}
								if(PixD[x].SH<P->S){
									PixD[x].SH=P->S;
								}
								if(PixD[x].RL>P->R){
									PixD[x].RL=P->R;
								}
								if(PixD[x].RH<P->R){
									PixD[x].RH=P->R;
								}
							}
						}
					}
				}
			}
		}
	}
#endif
	//delete
	DeleteImageList(LightImageList);
}

void	PixelInspectionItem::MakeTableForDark(void)
///void	PixelInspectionItem::MakeTableForDark(VCutInspectionInPage	*pVCutPage)
{
	if(GetDarkBuffList(DarkImageList)==false){
		return;
	}
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
//	int	SearchArea=1;
	int wSearchArea=((PixelInspectionBase *)GetParentBase())->getSearchAreaForMakeTable();

#ifdef Debug
	int x,y;
	BYTE	*MBmp;
	PixelInsData	*PixD;
	BYTE	*ms[3];
	int i,j;
	int SearchArea;
	if(Colored==true){
//		#pragma omp parallel
//		{
//			#pragma omp for
			for(y=0;y<YNumb;y++){
				MBmp=NULL;
				if(MaskBmp!=NULL){
					MBmp=MaskBmp[y];
					PixD=PixData[y];
					for(x=0;x<XNumb;x++){
						if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
							continue;
						}
						//?V???N?u?I?I?T?o?h?b?g
						SearchArea=wSearchArea;
						if(pAlignPage!=NULL){
							if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						//???u?I?I?T?o?h?b?g
						if(pHoleAlignPage!=NULL){
							if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
							continue;
						}
						if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
							continue;
						}
						if(y==DebugPointY && x==DebugPointX){
							DebugPoint++;
						}
						for(i=-SearchArea;i<=SearchArea;i++){
							ms[0]=DarkImageList[0]->GetY(y+i)+x;
							ms[1]=DarkImageList[1]->GetY(y+i)+x;
							ms[2]=DarkImageList[2]->GetY(y+i)+x;
							for(j=-SearchArea;j<=SearchArea;j++){
								struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
								if(PixD[x].PL>P->P){
									PixD[x].PL=P->P;
								}
								if(PixD[x].PH<P->P){
									PixD[x].PH=P->P;
								}
								if(PixD[x].SL>P->S){
									PixD[x].SL=P->S;
								}
								if(PixD[x].SH<P->S){
									PixD[x].SH=P->S;
								}
								if(PixD[x].RL>P->R){
									PixD[x].RL=P->R;
								}
								if(PixD[x].RH<P->R){
									PixD[x].RH=P->R;
								}
							}
						}
					}
				}
			}
//		}
	}
#else
	if(Colored==true){
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*MBmp=NULL;
				if(MaskBmp!=NULL){
					MBmp=MaskBmp[y];
					PixelInsData	*PixD=PixData[y];
					for(int x=0;x<XNumb;x++){
						if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(x,y)!=NULL){
							continue;
						}
						//?V???N?u?I?I?T?o?h?b?g
						int SearchArea=wSearchArea;
						if(pAlignPage!=NULL){
							if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						//???u?I?I?T?o?h?b?g
						if(pHoleAlignPage!=NULL){
							if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
								SearchArea=wSearchArea+1;
							}
						}
						if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
							continue;
						}
						if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
							continue;
						}
						for(int i=-SearchArea;i<=SearchArea;i++){
							BYTE	*ms[3];
							ms[0]=DarkImageList[0]->GetY(y+i)+x;
							ms[1]=DarkImageList[1]->GetY(y+i)+x;
							ms[2]=DarkImageList[2]->GetY(y+i)+x;
							for(int j=-SearchArea;j<=SearchArea;j++){
								struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
								if(PixD[x].PL>P->P){
									PixD[x].PL=P->P;
								}
								if(PixD[x].PH<P->P){
									PixD[x].PH=P->P;
								}
								if(PixD[x].SL>P->S){
									PixD[x].SL=P->S;
								}
								if(PixD[x].SH<P->S){
									PixD[x].SH=P->S;
								}
								if(PixD[x].RL>P->R){
									PixD[x].RL=P->R;
								}
								if(PixD[x].RH<P->R){
									PixD[x].RH=P->R;
								}
							}
						}
					}
				}
			}
		}
	}
#endif
	//delete
	DeleteImageList(DarkImageList);
}

void	PixelInspectionItem::ManualMakeTableForLight()
{
	if(GetLightBuffList(LightImageList)==false){
		return;
	}
	int		XNumb=GetDotPerLine();
	int		YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
///	int		SearchArea=((PixelInspectionBase *)GetParentBase())->SearchAreaForMakeTable;
	int		SearchArea=GetThresholdR()->SearchDotMaster;
	ThresholdMode ThrMode=GetThresholdR()->ThrMode;

	PixelInsData	**pPixD=NULL;
	if(ThrMode==_Narrow){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataNarrow;
	}
	else if(ThrMode==_Broad){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataBroad;
	}
	else{
		return;
	}

#ifdef Debug
	int LineLen,Len;
	int x,x1,x2,y;
	BYTE	*MBmp;
	PixelInsData	*PixD;
	BYTE	*ms[3];
	int Cnt;
	int i,j;
	struct	PixelPoleMatrixStruct	*P;
#endif
	if(Colored==true){
		if(MaskBmp!=NULL){
#ifndef Debug
			#pragma omp parallel
			{
				#pragma omp for
				for(int Cnt=0;Cnt<AreaArrayCnt;Cnt++){
					int LineLen	=AreaArrayList[Cnt].GetFLineLen();
					for(int Len=0;Len<LineLen;Len++){
						int x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
						int x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
						int y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
						BYTE	*MBmp=MaskBmp[y];
						PixelInsData	*PixD=pPixD[y];
						for(int x=x1;x<x2;x++){
#else
				for(Cnt=0;Cnt<AreaArrayCnt;Cnt++){
					int LineLen	=AreaArrayList[Cnt].GetFLineLen();
					for(Len=0;Len<LineLen;Len++){
						x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
						x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
						y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
						MBmp=MaskBmp[y];
						PixD=pPixD[y];
						for(x=x1;x<x2;x++){
#endif
							if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
								continue;
							}
							if(PixD[x].StdDisorder!=255){
								continue;
							}
							if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
								continue;
							}
							if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
								continue;
							}
#ifdef Debug
							for(i=-SearchArea;i<=SearchArea;i++){
#else
							for(int i=-SearchArea;i<=SearchArea;i++){
								BYTE	*ms[3];
#endif
								ms[0]=LightImageList[0]->GetY(y+i)+x;
								ms[1]=LightImageList[1]->GetY(y+i)+x;
								ms[2]=LightImageList[2]->GetY(y+i)+x;
#ifdef Debug
								for(j=-SearchArea;j<=SearchArea;j++){
									P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#else
								for(int j=-SearchArea;j<=SearchArea;j++){
									struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#endif
									if(PixD[x].PL>P->P){
										PixD[x].PL=P->P;
									}
									if(PixD[x].PH<P->P){
										PixD[x].PH=P->P;
									}
									if(PixD[x].SL>P->S){
										PixD[x].SL=P->S;
									}
									if(PixD[x].SH<P->S){
										PixD[x].SH=P->S;
									}
									if(PixD[x].RL>P->R){
										PixD[x].RL=P->R;
									}
									if(PixD[x].RH<P->R){
										PixD[x].RH=P->R;
									}
								}
							}
						}
					}
				}
#ifndef Debug
			}
#endif
		}
	}
	//delete
	DeleteImageList(LightImageList);
}

void	PixelInspectionItem::ManualMakeTableForDark()
{
	if(GetDarkBuffList(DarkImageList)==false){
		return;
	}
	int		XNumb=GetDotPerLine();
	int		YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
//	int		SearchArea=((PixelInspectionBase *)GetParentBase())->SearchAreaForMakeTable;
	int		SearchArea=GetThresholdR()->SearchDotMaster;
	ThresholdMode ThrMode=GetThresholdR()->ThrMode;

	PixelInsData	**pPixD=NULL;
	if(ThrMode==_Narrow){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataNarrow;
	}
	else if(ThrMode==_Broad){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataBroad;
	}
	else{
		return;
	}

#ifdef Debug
	int LineLen,Len;
	int x,x1,x2,y;
	BYTE	*MBmp;
	PixelInsData	*PixD;
	BYTE	*ms[3];
	int Cnt;
	int i,j;
	struct	PixelPoleMatrixStruct	*P;
#endif

	if(Colored==true){
		if(MaskBmp!=NULL){
#ifndef Debug
			#pragma omp parallel
			{
				#pragma omp for
				for(int Cnt=0;Cnt<AreaArrayCnt;Cnt++){
					int LineLen	=AreaArrayList[Cnt].GetFLineLen();
					for(int Len=0;Len<LineLen;Len++){
						int x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
						int x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
						int y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
						BYTE	*MBmp=MaskBmp[y];
						PixelInsData	*PixD=pPixD[y];
						for(int x=x1;x<x2;x++){
#else
				for(Cnt=0;Cnt<AreaArrayCnt;Cnt++){
					LineLen	=AreaArrayList[Cnt].GetFLineLen();
					for(Len=0;Len<LineLen;Len++){
						x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
						x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
						y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
						MBmp=MaskBmp[y];
						PixD=pPixD[y];
						for(int x=x1;x<x2;x++){
#endif
							if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
								continue;
							}
							if(PixD[x].StdDisorder!=255){
								continue;
							}
							if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
								continue;
							}
							if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
								continue;
							}
#ifdef Debug
							for(i=-SearchArea;i<=SearchArea;i++){
#else
							for(int i=-SearchArea;i<=SearchArea;i++){
								BYTE	*ms[3];
#endif
								ms[0]=DarkImageList[0]->GetY(y+i)+x;
								ms[1]=DarkImageList[1]->GetY(y+i)+x;
								ms[2]=DarkImageList[2]->GetY(y+i)+x;
#ifdef Debug
								for(j=-SearchArea;j<=SearchArea;j++){
									P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#else
								for(int j=-SearchArea;j<=SearchArea;j++){
									struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#endif
									if(PixD[x].PL>P->P){
										PixD[x].PL=P->P;
									}
									if(PixD[x].PH<P->P){
										PixD[x].PH=P->P;
									}
									if(PixD[x].SL>P->S){
										PixD[x].SL=P->S;
									}
									if(PixD[x].SH<P->S){
										PixD[x].SH=P->S;
									}
									if(PixD[x].RL>P->R){
										PixD[x].RL=P->R;
									}
									if(PixD[x].RH<P->R){
										PixD[x].RH=P->R;
									}
								}
							}
						}
					}
				}
#ifndef Debug
			}
#endif
		}
	}
	//delete
	DeleteImageList(DarkImageList);
}

void	PixelInspectionItem::ManualMakeTable()
{
	int		XNumb=GetDotPerLine();
	int		YNumb=GetMaxLines();
	bool	Colored	=((PixelInspectionBase *)GetParentBase())->getColored();
	ThrRange=256-((PixelInspectionBase *)GetParentBase())->getInspectionLevel();
	BYTE	**MaskBmp=GetAutoMaskBitmap();
//	int		SearchArea=((PixelInspectionBase *)GetParentBase())->SearchAreaForMakeTable;
	int		SearchArea=GetThresholdR()->SearchDotMaster;
	DetailType		ThrType=GetThresholdR()->ThrType;
	ThresholdMode	ThrMode=GetThresholdR()->ThrMode;
	int		SearchDotTarget		=GetThresholdR()->SearchDotTarget;
    double	RelativeNGThreshold	=GetThresholdR()->RelativeNGThreshold;
    int		AbsoluteNGThreshold	=GetThresholdR()->AbsoluteNGThreshold;
    int		NGSize				=GetThresholdR()->NGSize;

	PixelInsData	**pPixD=NULL;
	if(ThrMode==_Narrow){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataNarrow;
		AbsoluteNGThreshold=ThrRange;
	}
	else if(ThrMode==_Broad){
		pPixD=((PixelInspectionInPage *)GetParentInPage())->PixDataBroad;
		ThrRange=AbsoluteNGThreshold;
	}
	else{
		return;
	}

#ifdef Debug
	int Cnt;
	int LineLen,Len;
	int x,x1,x2,y;
	BYTE	*MBmp;
	PixelInsData	*PixD;
	int i,j;
	BYTE	*ms[3];
	BYTE	*ds[3];
	struct	PixelPoleMatrixStruct	*P;
#endif

	if(Colored==true){
		if(GetDisorderBuffList(DisorderImageList)==true){
			if(MaskBmp!=NULL){
#ifndef Debug
				#pragma omp parallel
				{
					#pragma omp for
					for(int Cnt=0;Cnt<AreaArrayCnt;Cnt++){
						int LineLen	=AreaArrayList[Cnt].GetFLineLen();
						for(int Len=0;Len<LineLen;Len++){
							int x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
							int x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
							int y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
							BYTE	*MBmp=MaskBmp[y];
							PixelInsData	*PixD=pPixD[y];
							for(int x=x1;x<x2;x++){
#else
					for(Cnt=0;Cnt<AreaArrayCnt;Cnt++){
						LineLen	=AreaArrayList[Cnt].GetFLineLen();
						for(Len=0;Len<LineLen;Len++){
							x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
							x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
							y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
							MBmp=MaskBmp[y];
							PixD=pPixD[y];
							for(x=x1;x<x2;x++){
#endif
								if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
									continue;
								}
								if(PixD[x].StdDisorder!=255){
									continue;
								}
								if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
									continue;
								}
								if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
									continue;
								}
#ifdef Debug
								for(i=-SearchArea;i<=SearchArea;i++){
#else
								for(int i=-SearchArea;i<=SearchArea;i++){
									BYTE	*ms[3];
									BYTE	*ds[3];
#endif
									ms[0]=AverageImageList[0]->GetY(y+i)+x;
									ms[1]=AverageImageList[1]->GetY(y+i)+x;
									ms[2]=AverageImageList[2]->GetY(y+i)+x;
									ds[0]=DisorderImageList[0]->GetY(y+i)+x;
									ds[1]=DisorderImageList[1]->GetY(y+i)+x;
									ds[2]=DisorderImageList[2]->GetY(y+i)+x;
#ifdef Debug
									for(j=-SearchArea;j<=SearchArea;j++){
										P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#else
									for(int j=-SearchArea;j<=SearchArea;j++){
										struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#endif
										if(PixD[x].PL>P->P){
											PixD[x].PL=P->P;
										}
										if(PixD[x].PH<P->P){
											PixD[x].PH=P->P;
										}
										if(PixD[x].SL>P->S){
											PixD[x].SL=P->S;
										}
										if(PixD[x].SH<P->S){
											PixD[x].SH=P->S;
										}
										if(PixD[x].RL>P->R){
											PixD[x].RL=P->R;
										}
										if(PixD[x].RH<P->R){
											PixD[x].RH=P->R;
										}
										//???S?s?N?Z???E?u(x,y)?I?W?Ä?I?ÅE?d???s?e
										if(i==0 && j==0){
											PixD[x].StdDisorder=(double)(ds[0][j]+ds[1][j]+ds[2][j])/3.0+0.5;
											//?W?Ä?I?ÅE?I?I???I?e?O?Å˜?Ibit?E?p?b?h?c?C???c?I?Å‚?f?d?????1?e
											if(GetThresholdR()->ThrType==_Pad){
												PixD[x].StdDisorder|=0x80;
											}
										}
									}
								}
								int wThresholdRange2=(AbsoluteNGThreshold<<7)/((PixD[x].RL+PixD[x].RH)>>1);
								wThresholdRange2+=abs(AbsoluteNGThreshold-wThresholdRange2)*RelativeNGThreshold;
								PixD[x].PL=Clip255(PixD[x].PL-wThresholdRange2);
								PixD[x].PH=Clip255(PixD[x].PH+wThresholdRange2);
								PixD[x].SL=Clip255(PixD[x].SL-wThresholdRange2);
								PixD[x].SH=Clip255(PixD[x].SH+wThresholdRange2);
								PixD[x].RL=Clip255(PixD[x].RL-AbsoluteNGThreshold);
								PixD[x].RH=Clip255(PixD[x].RH+AbsoluteNGThreshold);
							}
						}
					}
				}
#ifndef Debug
			}
#endif
			//delete
			DeleteImageList(DisorderImageList);
		}
		else{
			//???I?a???a?3?Åë?e??
			GetMasterBuffList(MasterImageList);
			if(MaskBmp!=NULL){
#ifndef Debug
				#pragma omp parallel
				{
					#pragma omp for
					for(int Cnt=0;Cnt<AreaArrayCnt;Cnt++){
						int LineLen	=AreaArrayList[Cnt].GetFLineLen();
						for(int Len=0;Len<LineLen;Len++){
							int x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
							int x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
							int y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
							BYTE	*MBmp=MaskBmp[y];
							PixelInsData	*PixD=pPixD[y];
							for(int x=x1;x<x2;x++){
#else
					for(Cnt=0;Cnt<AreaArrayCnt;Cnt++){
						LineLen	=AreaArrayList[Cnt].GetFLineLen();
						for(Len=0;Len<LineLen;Len++){
							x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
							x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
							y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
							MBmp=MaskBmp[y];
							PixD=pPixD[y];
							for(x=x1;x<x2;x++){
#endif
								if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))==0){
									continue;
								}
								if(PixD[x].StdDisorder!=255){
									continue;
								}
								if((x-SearchArea)<0 || XNumb<=(x+SearchArea)){
									continue;
								}
								if((y-SearchArea)<0 || YNumb<=(y+SearchArea)){
									continue;
								}
								//?Å‚?I?s?N?Z???E?u(x,y)?I?W?Ä?I?ÅE?d?O?E?ÅE?e
								PixD[x].StdDisorder=0;
#ifdef Debug
								for(i=-SearchArea;i<=SearchArea;i++){
#else
								for(int i=-SearchArea;i<=SearchArea;i++){
								BYTE	*ms[3];
#endif
									ms[0]=MasterImageList[0]->GetY(y+i)+x;
									ms[1]=MasterImageList[1]->GetY(y+i)+x;
									ms[2]=MasterImageList[2]->GetY(y+i)+x;
#ifdef Debug
									for(j=-SearchArea;j<=SearchArea;j++){
										P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#else
									for(int j=-SearchArea;j<=SearchArea;j++){
										struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(*(ms[0]+j),*(ms[1]+j),*(ms[2]+j))];
#endif
										if(PixD[x].PL>P->P){
											PixD[x].PL=P->P;
										}
										if(PixD[x].PH<P->P){
											PixD[x].PH=P->P;
										}
										if(PixD[x].SL>P->S){
											PixD[x].SL=P->S;
										}
										if(PixD[x].SH<P->S){
											PixD[x].SH=P->S;
										}
										if(PixD[x].RL>P->R){
											PixD[x].RL=P->R;
										}
										if(PixD[x].RH<P->R){
											PixD[x].RH=P->R;
										}
									}
								}
								//?W?Ä?I?ÅE?I?I???I?e?O?Å˜?Ibit?E?p?b?h?c?C???c?I?Å‚?f?d?????1?e
								if(GetThresholdR()->ThrType==_Pad){
									PixD[x].StdDisorder|=0x80;
								}
								int wThresholdRange2=(AbsoluteNGThreshold<<7)/((PixD[x].RL+PixD[x].RH)>>1);
								wThresholdRange2+=abs(AbsoluteNGThreshold-wThresholdRange2)*RelativeNGThreshold;
								PixD[x].PL=Clip255(PixD[x].PL-wThresholdRange2);
								PixD[x].PH=Clip255(PixD[x].PH+wThresholdRange2);
								PixD[x].SL=Clip255(PixD[x].SL-wThresholdRange2);
								PixD[x].SH=Clip255(PixD[x].SH+wThresholdRange2);
								PixD[x].RL=Clip255(PixD[x].RL-AbsoluteNGThreshold);
								PixD[x].RH=Clip255(PixD[x].RH+AbsoluteNGThreshold);
							}
						}
					}
#ifndef Debug
				}
#endif
			}
		}
	}
}

struct	PixelLibrarySettingString
{
	QString	StringReadLine;
	uint	Priority;
};

int	PLibFunc(const void *a ,const void *b)
{
	if(((struct PixelLibrarySettingString *)a)->Priority<((struct PixelLibrarySettingString *)b)->Priority){
		return -1;
	}
	if(((struct PixelLibrarySettingString *)a)->Priority>((struct PixelLibrarySettingString *)b)->Priority){
		return 1;
	}
	return 0;
}

struct	AutoAlignmentLibraryStruct
{
	AutoAlignmentLibrary	*AutoAlignmentLibraryPointer;
	int						Priority;
};

int	AALibFunc(const void *a ,const void *b)
{
	if(((struct AutoAlignmentLibraryStruct *)a)->Priority<((struct AutoAlignmentLibraryStruct *)b)->Priority){
		return -1;
	}
	if(((struct AutoAlignmentLibraryStruct *)a)->Priority>((struct AutoAlignmentLibraryStruct *)b)->Priority){
		return 1;
	}
	return 0;
}

//?s?N?Z???a?R
bool	PixelInspectionItem::CalcPixelInterPoration(int tx,int ty,BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH)
{
	//?a?o?I?s?N?Z???d?c?A?a?R?F?d?i?Å ?É ?A???ÅC?ÅE?e
	if(ExecPixelInterPoration(tx,ty,tx,ty-1,tx,ty+1,PL,PH,SL,SH,RL,RH)==true){
		return true;
	}

	//?Å˜?E?I?s?N?Z???d?c?A?a?R?F?d?i?Å ?É ?A???ÅC?ÅE?e
	if(ExecPixelInterPoration(tx,ty,tx-1,ty,tx+1,ty,PL,PH,SL,SH,RL,RH)==true){
		return true;
	}

	return false;
}

//?Q?_?I?s?N?Z???d?c?A?a?R?F?d?i?Å ?É ?A???ÅC?ÅE?e
bool	PixelInspectionItem::ExecPixelInterPoration(int tx,int ty,int tx1,int ty1,int tx2,int ty2,BYTE PL,BYTE PH,BYTE SL,BYTE SH,BYTE RL,BYTE RH)
{
	//(x,y)?A(x1,y1)
	BYTE	tts[3];
	BYTE	*ts[3];		//(x,y)
	BYTE	*ts1[3];	//(x1,y1)
	struct	PixelPoleMatrixStruct	*Q;
	ts[0]	=TargetImageList[0]->GetY(ty);
	ts[1]	=TargetImageList[1]->GetY(ty);
	ts[2]	=TargetImageList[2]->GetY(ty);
	ts1[0]	=TargetImageList[0]->GetY(ty1);
	ts1[1]	=TargetImageList[1]->GetY(ty1);
	ts1[2]	=TargetImageList[2]->GetY(ty1);
	tts[0]	=(ts[0][tx]+ts1[0][tx1])>>1;
	tts[1]	=(ts[1][tx]+ts1[1][tx1])>>1;
	tts[2]	=(ts[2][tx]+ts1[2][tx1])>>1;
	Q=&PoleTable[MakePoleIndex(tts[0],tts[1],tts[2])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		return true;
	}
	ts1[0]	=TargetImageList[0]->GetY(ty2);
	ts1[1]	=TargetImageList[1]->GetY(ty2);
	ts1[2]	=TargetImageList[2]->GetY(ty2);
	tts[0]	=(ts[0][tx]+ts1[0][tx2])>>1;
	tts[1]	=(ts[1][tx]+ts1[1][tx2])>>1;
	tts[2]	=(ts[2][tx]+ts1[2][tx2])>>1;
	Q=&PoleTable[MakePoleIndex(tts[0],tts[1],tts[2])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		return true;
	}

	return false;
}

ExeResult	PixelInspectionItem::ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetThresholdR()->Enable==false){
		return _ER_true;
	}

	ExeResult	Ret=AlgorithmItemPI::ExecutePreProcessing(ExeID,ThreadNo,Res);

	XByte	=(GetDotPerLine()+7)/8;
	XLen	=GetDotPerLine();
	YLen	=GetMaxLines();

	//?!???A???S???Y?Ä?I??
	if(((PixelInspectionInPage *)GetParentInPage())->IsMultiAlgorithmSupport==true){
		//ThrRange?d?a??
		ThresholdMode	ThrMode=GetThresholdR()->ThrMode;
		int		AbsoluteNGThreshold	=GetThresholdR()->AbsoluteNGThreshold;
		if(ThrMode==_Narrow){
			ThrRange=256-((PixelInspectionBase *)GetParentBase())->getInspectionLevel();
		}
		else if(ThrMode==_Broad){
			ThrRange=AbsoluteNGThreshold;
		}
		//DynamicClassify?IAlgorithmInPagePI?|?C???^?d?T?d
		DCAlgorithmInPagePIPointer=((PixelInspectionInPage *)GetParentInPage())->GetAlgorithmInPagePIPointer();
		//???ÅC?a???IDynamicClassify?I?a?|?C???^?d?T?d
		if(GetThresholdR()->ThrType>=_DCBaseArea){
			int i=((PixelInspectionInPage *)GetParentInPage())->GetUniqueIDList().indexOf(UniqueID);
			TargetDCBitmap		=((PixelInspectionInPage *)GetParentInPage())->TargetDCBitmap[i];
			TargetAreaArrayList	=((PixelInspectionInPage *)GetParentInPage())->TargetAreaArrayList[i];
		}
	}

	//?^?[?Q?b?g?a???d?v?Z?É ?A?P?x?a?3
	GetTargetBuffList(TargetImageList);
	GetLeastSquaresMethodT(TargetImageList,MLeastSquaresMethodTable,TLeastSquaresMethodTable);

	if(NGBitmap==NULL){
		NGBitmap=MakeMatrixBuff(XByte,YLen);
	}
	MatrixBuffClear(NGBitmap,0,XByte,YLen);

	if(InsCheckedBitmap==NULL){
		InsCheckedBitmap=MakeMatrixBuff(XByte,YLen);
	}
	MatrixBuffClear(InsCheckedBitmap,0,XByte,YLen);

	if(TempNGBitmap==NULL){
		TempNGBitmap=MakeMatrixBuff(XByte,YLen);
	}
	MatrixBuffClear(TempNGBitmap,0,XByte,YLen);

//	if(ThresholdDifferencemap==NULL){
//		ThresholdDifferencemap=MakeMatrixBuff(XLen,YLen);
//	}
//	MatrixBuffClear(ThresholdDifferencemap,0,XLen,YLen);

	return Ret;
}

ExeResult	PixelInspectionItem::ExecuteProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	//Enable
	if(GetThresholdR()->Enable==false){
		return _ER_true;
	}

#ifdef DebugConsole
	//???O?I?v?a
	clock_t	StartTime,EndTime;
	StartTime=clock();
#endif

	//???????O?I?v?a?iHALT?I???j
	DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=GetParamGlobal()->MaxInspectMilisec;

	//???ÅC???t???O
	NowInspection=true;

	//TargetImage Buffer
	GetTargetBuffList(TargetImageList);

	RadianCoef=M_PI/510.0;

	//?!???A???S???Y?Ä?I??
	if(((PixelInspectionInPage *)GetParentInPage())->IsMultiAlgorithmSupport==true){
//////////////////////////////////////////////////////
//				?!???A???S???Y?Ä?I??				//
//////////////////////////////////////////////////////
		//Page?IPixDataNarrow?a?É ?-?IPixDataBroad?dItem?E?R?s?[
		ThresholdMode ThrMode=GetThresholdR()->ThrMode;
		if(ThrMode==_Narrow){
			PixData=((PixelInspectionInPage *)GetParentInPage())->PixDataNarrow;
		}
		else if(ThrMode==_Broad){
			PixData=((PixelInspectionInPage *)GetParentInPage())->PixDataBroad;
		}
		else{
			return _ER_true;
		}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
		//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
		ManualExecuteProcessing1();

		//?u?I?I???ÅC?a???A?I???ÅC//
		ManualExecuteProcessing2();

//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
		//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
		ManualExecuteProcessing3();

		//?u?I?I???ÅC?a???A?I???ÅC//
		ManualExecuteProcessing4();

		PureFlexAreaListContainer TempFPack;
#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(10)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		if(wFPack!=NULL){
			wFPack->RemoveAll();
		}
		int SumAreaSize=0;
		PickupFlexArea(TempNGBitmap,XByte ,XLen,YLen ,TempFPack);
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
			int AreaSize=c->GetPatternByte();
			if(AreaSize<GetThresholdR()->NGSize){
				//NG?r?b?g?d???A?ÅE
				int LineLen	=c->GetFLineLen();
				for(int i=0;i<LineLen;i++){
					int x1	=c->GetFLineLeftX(i);
					int x2	=c->GetFLineRightX(i);
					int y	=c->GetFLineAbsY(i);
					for(int x=x1;x<x2;x++){
						TempNGBitmap[y][x>>3] &= ~(0x80>>(x&7));
					}
				}
				PureFlexAreaList	*CNext=c->GetNext();
				TempFPack.RemoveList(c);
				delete	c;
				c=CNext;
			}
			else{
				c=c->GetNext();
				SumAreaSize+=1;
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(11)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		//?Å}?I???_?AHALT?`?F?b?N
		if(SumAreaSize>=Parent->GetParamGlobal()->MaxNGCountsPerCam){
			Res->GetResultInspection()->SetMaxErrorBreak(true);
			goto MANUAL_HALT_INS;
		}
		DWORD	NowTime=GetComputerMiliSec();
		if(NowTime-StartMilisec>=MaxInspectMilisec){
			Res->GetResultInspection()->SetTimeOutBreak(true);
			goto MANUAL_HALT_INS;
		}
/*
		//TempNGBitmap?d?N???A
		MatrixBuffClear(TempNGBitmap,0,XByte,YLen);

		//TempNGBitmap?d?A?\?z
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext()){
			c->MakeBitData(TempNGBitmap,XLen,YLen);
		}

		//NGBitmap?d?\?Å 
		MatrixBuffOr(NGBitmap,(const BYTE **)TempNGBitmap,XByte,YLen);
*/
		//TempFPack?d?N???A
		TempFPack.RemoveAll();

		PickupFlexArea(TempNGBitmap,XByte,XLen,YLen,TempFPack);

		int AreaListNumb=TempFPack.GetNumber();
		PureFlexAreaList **AreaList=new PureFlexAreaList*[AreaListNumb];
		int i=0;
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext(),i++){
			AreaList[i]=c;
		}

#ifndef Debug
		#pragma omp parallel
		{
			#pragma omp for
#endif
			for(i=0;i<AreaListNumb;i++){
				ManualExecuteProcessing(AreaList[i]);
			}
#ifndef Debug
		}
#endif

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(12)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		delete []AreaList;
		TempFPack.RemoveAll();
		PickupFlexArea(TempNGBitmap,XByte ,XLen,YLen ,TempFPack);
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
			int AreaSize=c->GetPatternByte();
			if(AreaSize<GetThresholdR()->NGSize){
				PureFlexAreaList	*CNext=c->GetNext();
				TempFPack.RemoveList(c);
				delete	c;
				c=CNext;
			}
			else{
				c=c->GetNext();
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(13)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

MANUAL_HALT_INS:;
		if(Res->GetAddedData()==NULL){
			Res->SetAddedData(new ResultClusterOnItem(),ResultPixelOnItemType);
		}
		else{
			Res->GetAddedData()->Clear();
		}
		int	NGNumb=0;
		PureFlexAreaList *f;
		while((f=TempFPack.GetFirst())!=NULL){
			TempFPack.RemoveList(f);
			f->Regulate();
			((ResultClusterOnItem *)Res->GetAddedData())->List.AppendList(f);
			NGNumb++;

			//PosList?d?i?Å ?É ?AAppend?ÅE?e
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);	//mx+hx ,my+hy);
			r->NGSize=f->GetPatternByte();
			Res->AddPosList(r);
		}
		Parent->AddNGCounter(NGNumb);

		wFPack=&(((ResultClusterOnItem *)Res->GetAddedData())->List);

		if(NGNumb==0){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
		}
		Res->SetResult1(NGNumb);
		Res->SetAlignedXY(0,0);
		Res->SetItemSearchedXY(0,0);

		//???ÅC???t???O?N???A
		NowInspection=false;

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(14)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
#endif
	}
	else{
//////////////////////////////////////////////////////
//				?Å}?e?U?A?I???ÅC???W?b?N				//
//////////////////////////////////////////////////////
		AlgorithmBase		*ABase=GetParentBase();
		PixelInspectionBase	*PBase=(PixelInspectionBase *)ABase;

		int		SumAreaSize				=0;
		int		ThresholdRange			=256-((PixelInspectionBase *)GetParentBase())->getInspectionLevel();
		int		SearchDotBase			=    ((PixelInspectionBase *)GetParentBase())->getSearchDotBase();
		bool	CheckPadIns				=    ((PixelInspectionBase *)GetParentBase())->getCheckPadIns();
		bool	CheckSilkIns			=    ((PixelInspectionBase *)GetParentBase())->getCheckSilkIns();
		bool	CheckResistIns			=    ((PixelInspectionBase *)GetParentBase())->getCheckResistIns();
		bool	CheckHoleIns			=    ((PixelInspectionBase *)GetParentBase())->getCheckHoleIns();
		double	NGThresholdP_B			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdP_B();
		double	NGThresholdP_D			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdP_D();
		double	NGThresholdS_B			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdS_B();
		double	NGThresholdS_D			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdS_D();
		double	NGThresholdR_B			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdR_B();
		double	NGThresholdR_D			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdR_D();
		double	NGThresholdH_B			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdH_B();
		double	NGThresholdH_D			=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdH_D();
		int		MinimumNGSizeP			=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeP();
		int		MinimumNGSizeS			=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeS();
		int		MinimumNGSizeR			=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeR();
		int		MinimumNGSizeH			=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeH();
		bool	DonePadIns				=    ((PixelInspectionBase *)GetParentBase())->getDonePadIns();
		int		NGThresholdForPad_B		=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForPad_B();
		int		NGThresholdForPad_D		=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForPad_D();
		int		MinimumNGSizeForPad		=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeForPad();
		bool	DoneSilkIns				=    ((PixelInspectionBase *)GetParentBase())->getDoneSilkIns();
		int		NGThresholdForSilk_B	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForSilk_B();
		int		NGThresholdForSilk_D	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForSilk_D();
		int		MinimumNGSizeForSilk	=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeForSilk();
		bool	DoneResistIns			=    ((PixelInspectionBase *)GetParentBase())->getDoneResistIns();
		int		NGThresholdForResist_B	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForResist_B();
		int		NGThresholdForResist_D	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForResist_D();
		int		MinimumNGSizeForResist	=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeForResist();
		bool	DoneHoleIns				=    ((PixelInspectionBase *)GetParentBase())->getDoneHoleIns();
		int		NGThresholdForHole_B	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForHole_B();
		int		NGThresholdForHole_D	=    ((PixelInspectionBase *)GetParentBase())->getNGThresholdForHole_D();
		int		MinimumNGSizeForHole	=    ((PixelInspectionBase *)GetParentBase())->getMinimumNGSizeForHole();
		int		BrightnessRange			=	 ((PixelInspectionBase *)GetParentBase())->getBrightnessRange();
		bool	IsCalcPixelInterPoration=	 ((PixelInspectionBase *)GetParentBase())->getIsCalcPixelInterPoration();

		DetailType	DMode=_Other;

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(0)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		PureFlexAreaListContainer TempFPack;

//////////////////////////////////////////////////////
//					?U?Å~???ÅC						//
//////////////////////////////////////////////////////
		if(DoneResistIns==true){
			//???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC
			DMode=_Resist;
			if(ExecuteProcessingForDetail(Res,SearchDotBase,NGThresholdForResist_B,NGThresholdForResist_D,BrightnessRange,DMode,MinimumNGSizeForResist,StartMilisec,MaxInspectMilisec,TempFPack,SumAreaSize)==false){
				goto HALT_INS_R;
			}
		}
		if(DonePadIns==true){
			//?p?b?h?I?U?Å~???ÅC
			DMode=_Pad;
			if(ExecuteProcessingForDetail(Res,SearchDotBase,NGThresholdForPad_B,NGThresholdForPad_D,BrightnessRange,DMode,MinimumNGSizeForPad,StartMilisec,MaxInspectMilisec,TempFPack,SumAreaSize)==false){
				goto HALT_INS_R;
			}
		}
		if(DoneSilkIns==true){
			//?V???N?I?U?Å~???ÅC
			DMode=_Silk;
			if(ExecuteProcessingForDetail(Res,SearchDotBase,NGThresholdForSilk_B,NGThresholdForSilk_D,BrightnessRange,DMode,MinimumNGSizeForSilk,StartMilisec,MaxInspectMilisec,TempFPack,SumAreaSize)==false){
				goto HALT_INS_R;
			}
		}
		if(DoneHoleIns==true){
			//???I?U?Å~???ÅC
			DMode=_Hole;
			if(ExecuteProcessingForDetail(Res,SearchDotBase,NGThresholdForHole_B,NGThresholdForHole_D,BrightnessRange,DMode,MinimumNGSizeForHole,StartMilisec,MaxInspectMilisec,TempFPack,SumAreaSize)==false){
				goto HALT_INS_R;
			}
		}

//////////////////////////////////////////////////////
//					?E?i???ÅC						//
//////////////////////////////////////////////////////
#ifndef Debug
		#pragma omp parallel
		{
			#pragma omp for
#endif
			for(int y=0;y<YLen;y++){
				//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
				//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
				ExecuteProcessing1(y,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange,CheckPadIns,CheckSilkIns,CheckResistIns,CheckHoleIns,IsCalcPixelInterPoration);
			}
#ifndef Debug
		}
#endif

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(7)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		//InsCheckedBitmap?d?N???A
		MatrixBuffClear(InsCheckedBitmap,0,XByte,YLen);

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
				//?u?I?I???ÅC?a???A?I???ÅC//
				ExecuteProcessing2(y,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange,CheckPadIns,CheckSilkIns,CheckResistIns,CheckHoleIns,IsCalcPixelInterPoration);
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(8)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		//InsCheckedBitmap?d?\?Å 
		MatrixBuffOr(InsCheckedBitmap,(const BYTE **)TempNGBitmap,XByte,YLen);

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
				//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
				ExecuteProcessing3(y,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange,CheckPadIns,CheckSilkIns,CheckResistIns,CheckHoleIns,IsCalcPixelInterPoration);
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(9)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
				//?u?I?I???ÅC?a???A?I???ÅC//
				ExecuteProcessing4(y,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange,CheckPadIns,CheckSilkIns,CheckResistIns,CheckHoleIns,IsCalcPixelInterPoration);
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(10)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		if(wFPack!=NULL){
			wFPack->RemoveAll();
		}
		SumAreaSize=0;
		PickupFlexArea(TempNGBitmap,XByte ,XLen,YLen ,TempFPack);
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
			int AreaSize=c->GetPatternByte();
			if(AreaSize<MinimumNGSizeP || AreaSize<MinimumNGSizeS || AreaSize<MinimumNGSizeR || AreaSize<MinimumNGSizeH){
				//?p?b?hor?V???Nor???W?X?g
				int PadCnt		=0;
				int SilkCnt		=0;
				int ResistCnt	=0;
				int HoleCnt		=0;
				int LineLen	=c->GetFLineLen();
				for(int i=0;i<LineLen;i++){
					int x1	=c->GetFLineLeftX(i);
					int x2	=c->GetFLineRightX(i);
					int y	=c->GetFLineAbsY(i);
					for(int x=x1;x<x2;x++){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
							PadCnt++;
						}
						else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
							SilkCnt++;
						}
						else{
							int mx=x+pAlignPage->GetShiftXFromTarget(x,y);
							int my=y+pAlignPage->GetShiftYFromTarget(x,y);
							if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
								HoleCnt++;
							}
							else{
								ResistCnt++;
							}
						}
					}
				}
				//?Å‚?e
				if(PadCnt>=MinimumNGSizeP || SilkCnt>=MinimumNGSizeS || ResistCnt>=MinimumNGSizeR || HoleCnt>=MinimumNGSizeH){
					c=c->GetNext();
					SumAreaSize+=1;
					continue;
				}
				//NG?r?b?g?d???A?ÅE
				for(int i=0;i<LineLen;i++){
					int x1	=c->GetFLineLeftX(i);
					int x2	=c->GetFLineRightX(i);
					int y	=c->GetFLineAbsY(i);
					for(int x=x1;x<x2;x++){
						TempNGBitmap[y][x>>3] &= ~(0x80>>(x&7));
					}
				}
				PureFlexAreaList	*CNext=c->GetNext();
				TempFPack.RemoveList(c);
				delete	c;
				c=CNext;
			}
			else{
				c=c->GetNext();
				SumAreaSize+=1;
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(11)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		//?Å}?I???_?AHALT?`?F?b?N
		if(SumAreaSize>=Parent->GetParamGlobal()->MaxNGCountsPerCam){
			Res->GetResultInspection()->SetMaxErrorBreak(true);
			goto HALT_INS;
		}
		DWORD	NowTime=GetComputerMiliSec();
		if(NowTime-StartMilisec>=MaxInspectMilisec){
			Res->GetResultInspection()->SetTimeOutBreak(true);
			goto HALT_INS;
		}

		//NG?O???d?n?i?K?T?o
///		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext()){
///			ExecuteProcessing1(c,ThresholdRange,SearchDotBase,NGThreshold,BrightnessRange);
///		}

		//TempNGBitmap?d?N???A
		MatrixBuffClear(TempNGBitmap,0,XByte,YLen);

		//TempNGBitmap?d?A?\?z
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext()){
			c->MakeBitData(TempNGBitmap,XLen,YLen);
		}

#ifdef Debug2
		//?i???n?d?ÅC?c?ÅE?Å~?I?j?A?I???ÅC???W?b?N?d?A?s
		CalcExecuteProcessing(TempNGBitmap,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,MinimumNGSizeP,MinimumNGSizeS,MinimumNGSizeR,MinimumNGSizeH,BrightnessRange);
#endif
		//NG???n?I?oNGThresholdForPad_B;NGThresholdP_B
		double	NGThrP_B,NGThrP_D;
		double	NGThrS_B,NGThrS_D;
		double	NGThrR_B,NGThrR_D;
		double	NGThrH_B,NGThrH_D;
		NGThrP_B=NGThrP_D=NGThrS_B=NGThrS_D=NGThrR_B=NGThrR_D=NGThrH_B=NGThrH_D=0;
		if(CheckPadIns==true){
			NGThrP_B=NGThresholdP_B;
			NGThrP_D=NGThresholdP_D;
		}
		if(CheckSilkIns==true){
			NGThrS_B=NGThresholdS_B;
			NGThrS_D=NGThresholdS_D;
		}
		if(CheckResistIns==true){
			NGThrR_B=NGThresholdR_B;
			NGThrR_D=NGThresholdR_D;
		}
		if(CheckHoleIns==true){
			NGThrH_B=NGThresholdH_B;
			NGThrH_D=NGThresholdH_D;
		}

		//NGBitmap?d?\?Å 
		MatrixBuffOr(NGBitmap,(const BYTE **)TempNGBitmap,XByte,YLen);

		//TempFPack?d?N???A
		TempFPack.RemoveAll();

		PickupFlexArea(NGBitmap,XByte,XLen,YLen,TempFPack);

		int AreaListNumb=TempFPack.GetNumber();
		PureFlexAreaList **AreaList=new PureFlexAreaList*[AreaListNumb];
		int i=0;
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext(),i++){
			AreaList[i]=c;
		}
		#pragma omp parallel
		{
			#pragma omp for
			for(i=0;i<AreaListNumb;i++){
				ExecuteProcessing(AreaList[i],ThresholdRange,SearchDotBase,NGThrP_B,NGThrP_D,NGThrS_B,NGThrS_D,NGThrR_B,NGThrR_D,NGThrH_B,NGThrH_D,BrightnessRange,NGBitmap);
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(12)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

		delete []AreaList;
		TempFPack.RemoveAll();
		PickupFlexArea(NGBitmap,XByte ,XLen,YLen ,TempFPack);
		for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
			int AreaSize=c->GetPatternByte();
			if(AreaSize<MinimumNGSizeP || AreaSize<MinimumNGSizeS || AreaSize<MinimumNGSizeR || AreaSize<MinimumNGSizeH){
				//?p?b?hor?V???Nor???W?X?g
				int PadCnt		=0;
				int SilkCnt		=0;
				int ResistCnt	=0;
				int HoleCnt		=0;
				int LineLen	=c->GetFLineLen();
				for(int i=0;i<LineLen;i++){
					int x1	=c->GetFLineLeftX(i);
					int x2	=c->GetFLineRightX(i);
					int y	=c->GetFLineAbsY(i);
					for(int x=x1;x<x2;x++){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
							PadCnt++;
						}
						else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
							SilkCnt++;
						}
						else{
							int mx=x+pAlignPage->GetShiftXFromTarget(x,y);
							int my=y+pAlignPage->GetShiftYFromTarget(x,y);
							if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
								HoleCnt++;
							}
							else{
								ResistCnt++;
							}
						}
					}
				}
				//?Å‚?e
				if(PadCnt>=MinimumNGSizeP || SilkCnt>=MinimumNGSizeS || ResistCnt>=MinimumNGSizeR || HoleCnt>=MinimumNGSizeH){
					c=c->GetNext();
					continue;
				}
				PureFlexAreaList	*CNext=c->GetNext();
				TempFPack.RemoveList(c);
				delete	c;
				c=CNext;
			}
			else{
				c=c->GetNext();
			}
		}

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(13)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
		StartTime=clock();
#endif

HALT_INS:;
		if(Res->GetAddedData()==NULL){
			Res->SetAddedData(new ResultClusterOnItem(),ResultPixelOnItemType);
		}
		else{
			Res->GetAddedData()->Clear();
		}
		int	NGNumb=0;
		PureFlexAreaList *f;
		while((f=TempFPack.GetFirst())!=NULL){
			TempFPack.RemoveList(f);
			f->Regulate();
			((ResultClusterOnItem *)Res->GetAddedData())->List.AppendList(f);
			NGNumb++;

			//PosList?d?i?Å ?É ?AAppend?ÅE?e
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);	//mx+hx ,my+hy);
			r->NGSize=f->GetPatternByte();
			Res->AddPosList(r);
		}
		Parent->AddNGCounter(NGNumb);

		wFPack=&(((ResultClusterOnItem *)Res->GetAddedData())->List);

		if(NGNumb==0){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
		}
		Res->SetResult1(NGNumb);
		Res->SetAlignedXY(0,0);
		Res->SetItemSearchedXY(0,0);

		//???ÅC???t???O?N???A
		NowInspection=false;

#ifdef DebugConsole
		EndTime=clock();
		printf(/**/"ExecuteProcessing(14)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
#endif

		return _ER_true;

HALT_INS_R:;
		PickupFlexArea(NGBitmap,XByte,XLen,YLen,TempFPack);
		if(Res->GetAddedData()==NULL){
			Res->SetAddedData(new ResultClusterOnItem(),ResultPixelOnItemType);
		}
		else{
			Res->GetAddedData()->Clear();
		}
		NGNumb=0;
		while((f=TempFPack.GetFirst())!=NULL){
			TempFPack.RemoveList(f);
			f->Regulate();
			((ResultClusterOnItem *)Res->GetAddedData())->List.AppendList(f);
			NGNumb++;

			//PosList?d?i?Å ?É ?AAppend?ÅE?e
			int	Cx,Cy;
			f->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);	//mx+hx ,my+hy);
			r->NGSize=f->GetPatternByte();
			Res->AddPosList(r);
		}
		wFPack=&(((ResultClusterOnItem *)Res->GetAddedData())->List);

		if(NGNumb==0){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
		}
		Res->SetResult1(NGNumb);
		Res->SetAlignedXY(0,0);
		Res->SetItemSearchedXY(0,0);

		//???ÅC???t???O?N???A
		NowInspection=false;
	}

	return _ER_true;
}

bool	PixelInspectionItem::ManualPixDataForResistSilk()
{
	//Enable
	if(GetThresholdR()->Enable==false){
		return true;
	}

	//Page?c?c?|?C???^?I???d?o?A?Åí?A?A?-?e
	PixelInsData	**pPixDataForResistSilk;
	pPixDataForResistSilk=((PixelInspectionInPage *)GetParentInPage())->PixDataForResistSilk[_Resist];
	PixDataForResistSilk[_Resist]	=pPixDataForResistSilk;
	pPixDataForResistSilk=((PixelInspectionInPage *)GetParentInPage())->PixDataForResistSilk[_Silk];
	PixDataForResistSilk[_Silk]		=pPixDataForResistSilk;

	if(GetThresholdR()->ThrType==_Resist || GetThresholdR()->ThrType==_Silk){
		//?}?X?^?[?a??
		GetMasterBuffList(MasterImageList);

		int	XNumb=GetDotPerLine();
		int	YNumb=GetMaxLines();
		BYTE	**MaskBmp=GetAutoMaskBitmap();

		//???W?X?g?Ie??l?I?i?[???[?N?I?m?F
		if(((PixelInspectionInPage *)GetParentInPage())->PixDataForResistSilk[0]==NULL || ((PixelInspectionInPage *)GetParentInPage())->PixDataForResistSilk[1]==NULL){
			return false;
		}

		//Page?c?c?|?C???^?I???d?o?A?Åí?A?A?-?e
		pPixDataForResistSilk=((PixelInspectionInPage *)GetParentInPage())->PixDataForResistSilk[GetThresholdR()->ThrType];

		//???W?X?g?Ie??l?d?i?Å 
		if(pAlignPage!=NULL && MaskBmp!=NULL){
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<=(YNumb>>8);i++){
					for(int j=0;j<=(XNumb>>8);j++){
						int MBmpCnt;
						DWORD	AddedP,AddedS,AddedR;		//?A?Z?l
						DWORD	Added2P,Added2S,Added2R;	//?Q?a?a
						MBmpCnt=0;
						AddedP	=AddedS	=AddedR	=0;
						Added2P	=Added2S=Added2R=0;
						for(int y=(i<<8);y<((i+1)<<8) && y<YNumb;y++){
							BYTE	*MBmp=MaskBmp[y];
							if(MBmp==NULL){
								continue;
							}
							for(int x=(j<<8);x<((j+1)<<8) && x<XNumb;x++){
								if(GetArea().IsInclude(x,y)==true){
									if((MBmp[x>>3]&(0x80>>(x&7)))!=0){
										BYTE *ms[3];
										ms[0]=MasterImageList[0]->GetY(y);
										ms[1]=MasterImageList[1]->GetY(y);
										ms[2]=MasterImageList[2]->GetY(y);
										struct	PixelPoleMatrixStruct	*P=&PoleTable[MakePoleIndex(ms[0][x],ms[1][x],ms[2][x])];
										AddedP	+=P->P;
										Added2P	+=P->P*P->P;
										AddedS	+=P->S;
										Added2S	+=P->S*P->S;
										AddedR	+=P->R;
										Added2R	+=P->R*P->R;
										MBmpCnt++;
									}
								}
							}
						}
						if(MBmpCnt==0){
							continue;
						}
						BYTE DisP,DisS,DisR;
						DisP=GetDisorder(AddedP,Added2P,MBmpCnt);
						DisS=GetDisorder(AddedS,Added2S,MBmpCnt);
						DisR=GetDisorder(AddedR,Added2R,MBmpCnt);
						pPixDataForResistSilk[i][j].PL=GetAvr(AddedP,MBmpCnt)-DisP;
						pPixDataForResistSilk[i][j].PH=GetAvr(AddedP,MBmpCnt)+DisP;
						pPixDataForResistSilk[i][j].SL=GetAvr(AddedS,MBmpCnt)-DisS;
						pPixDataForResistSilk[i][j].SH=GetAvr(AddedS,MBmpCnt)+DisS;
						pPixDataForResistSilk[i][j].RL=GetAvr(AddedR,MBmpCnt)-DisR;
						pPixDataForResistSilk[i][j].RH=GetAvr(AddedR,MBmpCnt)+DisR;
						pPixDataForResistSilk[i][j].StdDisorder=DisR;
					}
				}
			}
		}
	}
	return true;
}

bool	PixelInspectionItem::PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
/*
	if(::Save(f,sNoPCBImagePath)==false){
		return false;
	}
*/
	return true;
}

bool	PixelInspectionItem::PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
/*
	//e??l?I?i?Å 
	MakeTable();

	QString	PipeInNoPCBImagePath;
	if(::Load(f,PipeInNoPCBImagePath)==false){
		return false;
	}

	//?i?A?E?É ?a???I?C?Y???Y
	if(LoadTargetImage(PipeInNoPCBImagePath,localX1,localY1,localX2,localY2)==true){
	}
	else{
		//?i?A?E?É ?a???a?C?Y???s?E?c?A???e??
	}
*/
	return true;
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ExecuteProcessing1(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int	x;
	int	tx,ty;
	int mtX,mtY;
	int tmX,tmY;
	PixelInsData	P,P1,P2,P3;
	int	PL,PH,SL,SH,RL,RH;
	int	PL3,PH3,SL3,SH3,RL3,RH3;
	int SearchDot;
//	bool	IsTargetBlack;
	int wThresholdRange;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	bool IsPad,IsSilk;
	BYTE	*ts[3];

	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#else
	for(int x=0;x<XLen;x++){
		int	tx,ty;
		int mtX,mtY;
		int tmX,tmY;
		int SearchDot;
		int wThresholdRange;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		bool IsPad,IsSilk;
		BYTE	*ts[3];
		PixelInsData &P	=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
			continue;
		}
		if(pAlignPage==NULL){
			mtX	=mtY=0;
			tmX	=tmY=0;
			tx	=x;
			ty	=y;
		}
		else{
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			tx	=x+mtX;
			ty	=y+mtY;
		}

		if(tx<0 || XLen<=tx){
			continue;
		}
		if(ty<0 || YLen<=ty){
			continue;
		}

		wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
		if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
			//?p?b?h?I?e??
			if(CheckPadIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
			SearchDot	=SearchDotBase;
			IsPad		=true;
			IsSilk		=false;
			if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
				//?V???N?A?a???e?e??
				IsSilk	=true;
			}
		}
		else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
			//?V???N?I?e??
			if(CheckSilkIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
			SearchDot	=SearchDotBase+1;
			IsPad		=false;
			IsSilk		=true;
		}
		else{
			if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
				//???I?e??
				if(CheckHoleIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
			else{
				//???W?X?g?I?e??
				if(CheckResistIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
		}

		if(x-SearchDot<0 || XLen<=x+SearchDot){
			goto	Matched1;
		}
		if(y-SearchDot<0 || YLen<=y+SearchDot){
			goto	Matched1;
		}

		//?u?E???ÅC?I?Y
		if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
			//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
				continue;
			}
			//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
			else{
				TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
			}
		}
/*		else{
			//ExecuteProcessingForResist?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((NGBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
				continue;
			}
		}
*/
		wThresholdRange=ThresholdRange;

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		if(ty==DebugPointY && tx==DebugPointX){
			DebugPoint++;
		}

		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange;
		RH		=P.RH+wThresholdRange;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange;
		int	RH	=P.RH+wThresholdRange;
#endif
		wThresholdRange=ThresholdRange;

		ts[0]=TargetImageList[0]->GetY(ty);
		ts[1]=TargetImageList[1]->GetY(ty);
		ts[2]=TargetImageList[2]->GetY(ty);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
		if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
			goto	Matched1;
		}

		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange;
				RH	=P1.RH+wThresholdRange;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched1;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange;
				RH	=P1.RH+wThresholdRange;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched1;
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange;
				RH	=P1.RH+wThresholdRange;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched1;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange;
				RH	=P1.RH+wThresholdRange;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched1;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
		P1				=PixData[y][x];
#else
		PixelInsData &P1=PixData[y][x];
		PixelInsData P3;
#endif
		P3.SL=Q->S;
		P3.PL=Q->P;
		P3.RL=Q->R;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange;
					RH3		=P3.RH+wThresholdRange;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange;
					int	RH3	=P3.RH+wThresholdRange;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched1;
					}
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange;
					RH3		=P3.RH+wThresholdRange;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange;
					int	RH3	=P3.RH+wThresholdRange;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched1;
					}
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange;
					RH3		=P3.RH+wThresholdRange;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange;
					int	RH3	=P3.RH+wThresholdRange;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched1;
					}
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange;
					RH3		=P3.RH+wThresholdRange;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange;
					int	RH3	=P3.RH+wThresholdRange;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched1;
					}
				}
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(IsSilk!=pAlignPage->GetBitPickupFromTarget(tx,ty) || IsPad!=pAlignPage->GetBitFirstPickupFromTarget(tx,ty)){
			//Is Target Point Resist ?
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange,wThresholdRange,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	Matched1;
				}
			}
			//Is Target Point Silk ?
			else if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange,wThresholdRange,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	Matched1;
				}
			}
		}

		//M?ÅNT?AT?ÅNM?I?A???C?????g?U?R?E?a?a?A???c?AT?ÅNM?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromTarget1(x,y,wThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
				goto	Matched1;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		PixelInsData &Pw=PixData[y][x];
		if(Pw.PL-Q->P > 0){
			DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-Pw.PH > 0){
			DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		if(Pw.SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-Pw.SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(Pw.RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-Pw.RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	Matched1;
		}

		//?s?N?Z???a?R
		if(IsCalcPixelInterPoration==true){
			if(CalcPixelInterPoration(tx,ty,PL,PH,SL,SH,RL,RH)==true){
				goto	Matched1;
			}
		}

		TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));

Matched1:;
		InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
	}
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ExecuteProcessing2(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int	x;
	int	tx,ty;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P;
	int	PL,PH,SL,SH,RL,RH;
	int wPL,wPH,wSL,wSH,wRL,wRH;
	int SearchDot;
	int wThresholdRange;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	bool IsPad,IsSilk;
	BYTE	*ts[3];

	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#else
	for(int x=0;x<XLen;x++){
		int	tx,ty;
		int mtX,mtY;
		int tmX,tmY;
		int SearchDot;
		int wThresholdRange;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		bool IsPad,IsSilk;
		PixelInsData &P	=PixData[y][x];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){
			continue;
		}
		if(pAlignPage==NULL){
			mtX	=mtY=0;
			tmX	=tmY=0;
			tx	=x;
			ty	=y;
		}
		else{
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			tx	=x+mtX;
			ty	=y+mtY;
		}

		wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
		if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
			//?p?b?h?I?e??
			if(CheckPadIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
			SearchDot	=SearchDotBase;
			IsPad		=true;
			IsSilk		=false;
			if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
				//?V???N?A?a???e?e??
				IsSilk	=true;
			}
		}
		else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
			//?V???N?I?e??
			if(CheckSilkIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
			SearchDot	=SearchDotBase+1;
			IsPad		=false;
			IsSilk		=true;
		}
		else{
			if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
				//???I?e??
				if(CheckHoleIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
			else{
				//???W?X?g?I?e??
				if(CheckResistIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
		}
		if(tx-SearchDot<0 || XLen<=tx+SearchDot){
			continue;
		}
		if(ty-SearchDot<0 || YLen<=ty+SearchDot){
			continue;
		}

#ifdef Debug
		if(ty==DebugPointY && tx==DebugPointX){
			DebugPoint++;
		}
#endif
		//?u?E???ÅC?I?Y
		if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
			//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
				continue;
			}
			//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
			else{
				TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
			}
		}
		else{
			//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
				continue;
			}
		}

		wThresholdRange=ThresholdRange;

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		if(ty==DebugPointY && tx==DebugPointX){
			DebugPoint++;
		}

		PL		=P.PL-ThresholdRange;
		PH		=P.PH+ThresholdRange;
		SL		=P.SL-ThresholdRange;
		SH		=P.SH+ThresholdRange;
		RL		=P.RL-ThresholdRange;
		RH		=P.RH+ThresholdRange;
		wPL		=P.PL-wThresholdRange2_PD;
		wPH		=P.PH+wThresholdRange2_PB;
		wSL		=P.SL-wThresholdRange2_SD;
		wSH		=P.SH+wThresholdRange2_SB;
		wRL		=P.RL-wThresholdRange;
		wRH		=P.RH+wThresholdRange;
#else
		int	PL	=P.PL-ThresholdRange;
		int	PH	=P.PH+ThresholdRange;
		int	SL	=P.SL-ThresholdRange;
		int	SH	=P.SH+ThresholdRange;
		int	RL	=P.RL-ThresholdRange;
		int	RH	=P.RH+ThresholdRange;
		int	wPL	=P.PL-wThresholdRange2_PD;
		int	wPH	=P.PH+wThresholdRange2_PB;
		int	wSL	=P.SL-wThresholdRange2_SD;
		int	wSH	=P.SH+wThresholdRange2_SB;
		int	wRL	=P.RL-wThresholdRange;
		int	wRH	=P.RH+wThresholdRange;
#endif
		wThresholdRange=ThresholdRange;

#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(ty);
		ts[1]=TargetImageList[1]->GetY(ty);
		ts[2]=TargetImageList[2]->GetY(ty);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
		if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
			goto	Matched2;
		}

		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	Matched2;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	Matched2;
				}
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	Matched2;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	Matched2;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched2;
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched2;
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched2;
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched2;
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(IsSilk!=pAlignPage->GetBitPickupFromTarget(tx,ty) || IsPad!=pAlignPage->GetBitFirstPickupFromTarget(tx,ty)){
			//Is Target Point Resist ?
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange,wThresholdRange,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	Matched2;
				}
			}
			//Is Target Point Silk ?
			else if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange2_B,wThresholdRange2_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	Matched2;
				}
			}
		}

		//M?ÅNT?AT?ÅNM?I?A???C?????g?U?R?E?a?a?A???c?AT?ÅNM?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromTarget2(x,y,wThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
				goto	Matched2;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		if(PL-Q->P > 0){
			DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-PH > 0){
			DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		if(SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	Matched2;
		}

		//?s?N?Z???a?R
		if(IsCalcPixelInterPoration==true){
			if(CalcPixelInterPoration(tx,ty,PL,PH,SL,SH,RL,RH)==true){
				goto	Matched2;
			}
		}

		TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));

Matched2:;
		InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
	}
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
bool	PixelInspectionItem::ExecuteProcessingFromTarget1(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange)
{
	int	tx,ty;
	if(pAlignPage==NULL){
		tx	=x;
		ty	=y;
	}
	else{
		tx	=x-pAlignPage->GetShiftXFromTarget(x,y);
		ty	=y-pAlignPage->GetShiftYFromTarget(x,y);
	}
	PixelInsData &P	=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE

	int wThresholdRange_B=ThresholdRange;
	int wThresholdRange_D=ThresholdRange;

	if(tx<0 || XLen<=tx){
		return true;
	}
	if(ty<0 || YLen<=ty){
		return true;
	}

	int SearchDot;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;

	int wThresholdRange2_B,wThresholdRange2_D;
	wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
	if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
		//?p?b?h?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
		SearchDot	=SearchDotBase;
	}
	else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
		//?V???N?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
		SearchDot	=SearchDotBase+1;
	}
	else if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
		//???I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
		SearchDot	=SearchDotBase;
	}
	else{
		//???W?X?g?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
		SearchDot	=SearchDotBase;
	}

	if(x-SearchDot<0 || XLen<=x+SearchDot){
		return true;
	}
	if(y-SearchDot<0 || YLen<=y+SearchDot){
		return true;
	}

	//?É ?Å·?Åë?l?I?????A???I??
	if(((P.PL+P.PH)>>1)<=127){
		wThresholdRange2_PB=wThresholdRange2_B;
		wThresholdRange2_PD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_PB=wThresholdRange2_D;
		wThresholdRange2_PD=wThresholdRange2_B;
	}
	if(((P.SL+P.SH)>>1)<=127){
		wThresholdRange2_SB=wThresholdRange2_B;
		wThresholdRange2_SD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_SB=wThresholdRange2_D;
		wThresholdRange2_SD=wThresholdRange2_B;
	}

	int	PL	=P.PL-wThresholdRange2_PD;
	int	PH	=P.PH+wThresholdRange2_PB;
	int	SL	=P.SL-wThresholdRange2_SD;
	int	SH	=P.SH+wThresholdRange2_SB;
	int	RL	=P.RL-wThresholdRange_D;
	int	RH	=P.RH+wThresholdRange_B;

	BYTE	*ts[3];
	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		return true;
	}
	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[y+dy][x+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[y+dy][x+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[y+dy][x+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[y+dy][x+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData &P1=PixData[y][x];
	PixelInsData P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[y+dy][x+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[y+dy][x+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[y+dy][x+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[y+dy][x+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
	}
	return false;
}

bool	PixelInspectionItem::ExecuteProcessingFromTarget2(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange)
{
	int	tx,ty;
	if(pAlignPage==NULL){
		tx	=x;
		ty	=y;
	}
	else{
		tx	=x-pAlignPage->GetShiftXFromTarget(x,y);
		ty	=y-pAlignPage->GetShiftYFromTarget(x,y);
	}
	PixelInsData &P	=PixData[y][x];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return true;
	}

	int wThresholdRange_B=ThresholdRange;
	int wThresholdRange_D=ThresholdRange;

	int SearchDot;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;

	int wThresholdRange2_B,wThresholdRange2_D;
	wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
	if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
		//?p?b?h?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
		SearchDot	=SearchDotBase;
	}
	else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
		//?V???N?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
		SearchDot	=SearchDotBase+1;
	}
	else if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
		//???I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
		SearchDot	=SearchDotBase;
	}
	else{
		//???W?X?g?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
		SearchDot	=SearchDotBase;
	}

	if(tx-SearchDot<0 || XLen<=tx+SearchDot){
		return true;
	}
	if(ty-SearchDot<0 || YLen<=ty+SearchDot){
		return true;
	}

	//?É ?Å·?Åë?l?I?????A???I??
	if(((P.PL+P.PH)>>1)<=127){
		wThresholdRange2_PB=wThresholdRange2_B;
		wThresholdRange2_PD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_PB=wThresholdRange2_D;
		wThresholdRange2_PD=wThresholdRange2_B;
	}
	if(((P.SL+P.SH)>>1)<=127){
		wThresholdRange2_SB=wThresholdRange2_B;
		wThresholdRange2_SD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_SB=wThresholdRange2_D;
		wThresholdRange2_SD=wThresholdRange2_B;
	}

	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange2_PD;
	int	wPH	=P.PH+wThresholdRange2_PB;
	int	wSL	=P.SL-wThresholdRange2_SD;
	int	wSH	=P.SH+wThresholdRange2_SB;
	int	wRL	=P.RL-wThresholdRange_D;
	int	wRH	=P.RH+wThresholdRange_B;

	BYTE	*ts[3];
	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		return true;
	}
	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
	}
	return false;
}

//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ExecuteProcessing3(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P,P1,P2,P3;
	int PL,PH,SL,SH,RL,RH;
	int PL3,PH3,SL3,SH3,RL3,RH3;
	int SearchDot;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	bool IsPad,IsSilk;
	BYTE	*ts[3];
	int x;
	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
#else
	for(int x=0;x<XLen;x++){
		int	mx,my;
		int tmX,tmY;
		int mtX,mtY;
		int SearchDot;
		int wThresholdRange_B	,wThresholdRange_D;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		bool IsPad,IsSilk;
#endif
		//ExecuteProcessing1or2?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
		if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}

		if(pAlignPage==NULL){
			tmX	=tmY=0;
			mtX	=mtY=0;
			mx	=x;
			my	=y;
		}
		else{
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			mx	=x+tmX;
			my	=y+tmY;
		}

		if((mx-(SearchDotBase+1))<0 || XLen<=(mx+(SearchDotBase+1))){
			continue;
		}
		if((my-(SearchDotBase+1)<0 || YLen<=(my+(SearchDotBase+1)))){
			continue;
		}

#ifdef Debug
		if(my==DebugPointY && mx==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
		PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
			continue;
		}

		wThresholdRange_B=wThresholdRange_D=ThresholdRange;

		wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
		if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
			//?p?b?h?I?e??
			if(CheckPadIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
			SearchDot	=SearchDotBase;
			IsPad		=true;
			IsSilk		=false;
			if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
				//?V???N?A?a???e?e??
				IsSilk	=true;
			}
		}
		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			//?V???N?I?e??
			if(CheckSilkIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
			SearchDot	=SearchDotBase+1;
			IsPad		=false;
			IsSilk		=true;
		}
		else{
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
				//???I?e??
				if(CheckHoleIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
			else{
				//???W?X?g?I?e??
				if(CheckResistIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
			}
		}

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange_D;
		RH		=P.RH+wThresholdRange_B;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange_D;
		int	RH	=P.RH+wThresholdRange_B;
#endif
		if((x-SearchDot)<0 || XLen<=(x+SearchDot)){
			continue;
		}
		if((y-SearchDot)<0 || YLen<=(y+SearchDot)){
			continue;
		}

#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(y);
		ts[1]=TargetImageList[1]->GetY(y);
		ts[2]=TargetImageList[2]->GetY(y);
		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
		if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
			goto	Matched3;
		}

		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched3;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched3;
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched3;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched3;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
		P1				=PixData[my][mx];
#else
		PixelInsData &P1=PixData[my][mx];
		PixelInsData P3;
#endif
		P3.SL=Q->S;
		P3.PL=Q->P;
		P3.RL=Q->R;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched3;
					}
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched3;
					}
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched3;
					}
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	Matched3;
					}
				}
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my) || IsPad!=pAlignPage->GetBitFirstPickupFromMaster(mx,my)){
			//Is Target Point Resist ?
			if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	Matched3;
				}
			}
			//Is Target Point Silk ?
			else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	Matched3;
				}
			}
		}

		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromMaster1(x,y,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
				goto	Matched3;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		PixelInsData &Pw=PixData[my][mx];
		if(Pw.PL-Q->P > 0){
			DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-Pw.PH > 0){
			DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		if(Pw.SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-Pw.SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(Pw.RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-Pw.RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	Matched3;
		}

		//?s?N?Z???a?R
		if(IsCalcPixelInterPoration==true){
			if(CalcPixelInterPoration(x,y,PL,PH,SL,SH,RL,RH)==true){
				goto	Matched3;
			}
		}

		TempNGBitmap[y][x>>3] |= (0x80>>(x&7));

Matched3:;
	}
}

//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ExecuteProcessing4(int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,bool CheckPadIns,bool CheckSilkIns,bool CheckResistIns,bool CheckHoleIns,bool IsCalcPixelInterPoration)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P;
	int	PL,PH,SL,SH,RL,RH;
	int wPL,wPH,wSL,wSH,wRL,wRH;
	int SearchDot;
	int wThresholdRange;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	bool IsPad;
	bool IsSilk;
	DetailType	DPixelMode=_Resist;
	BYTE	*ts[3];
	int x;
	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
#else
	for(int x=0;x<XLen;x++){
		int	mx,my;
		int tmX,tmY;
		int mtX,mtY;
		int SearchDot;
		int wThresholdRange;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		bool IsPad;
		bool IsSilk;
		DetailType	DPixelMode=_Resist;
#endif
		//ExecuteProcessing1?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
		if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}
		//ExecuteProcessing3?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
		if((TempNGBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}

		if(pAlignPage==NULL){
			tmX	=tmY=0;
			mtX	=mtY=0;
			mx	=x;
			my	=y;
		}
		else{
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			mx	=x+tmX;
			my	=y+tmY;
		}
		if(mx<0 || XLen<=mx){
			continue;
		}
		if(my<0 || YLen<=my){
			continue;
		}

#ifdef Debug
		if(my==DebugPointY && mx==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
		PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){
			continue;
		}

		wThresholdRange=ThresholdRange;

		wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
		if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
			//?p?b?h?I?e??
			if(CheckPadIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
			SearchDot	=SearchDotBase;
			IsPad		=true;
			IsSilk		=false;
			DPixelMode	=_Pad;
			if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
				//?V???N?A?a???e?e??
				IsSilk	=true;
			}
		}
		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			//?V???N?I?e??
			if(CheckSilkIns==false){
				continue;
			}
			wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
			wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
			SearchDot	=SearchDotBase+1;
			IsPad		=false;
			IsSilk		=true;
			DPixelMode	=_Silk;
		}
		else{
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
				//???I?e??
				if(CheckHoleIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
				DPixelMode	=_Hole;
			}
			else{
				//???W?X?g?I?e??
				if(CheckResistIns==false){
					continue;
				}
				wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
				wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
				SearchDot	=SearchDotBase;
				IsPad		=false;
				IsSilk		=false;
				DPixelMode	=_Resist;
			}
		}

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		PL		=P.PL-ThresholdRange;
		PH		=P.PH+ThresholdRange;
		SL		=P.SL-ThresholdRange;
		SH		=P.SH+ThresholdRange;
		RL		=P.RL-ThresholdRange;
		RH		=P.RH+ThresholdRange;
		wPL		=P.PL-wThresholdRange2_PD;
		wPH		=P.PH+wThresholdRange2_PB;
		wSL		=P.SL-wThresholdRange2_SD;
		wSH		=P.SH+wThresholdRange2_SB;
		wRL		=P.RL-wThresholdRange;
		wRH		=P.RH+wThresholdRange;
#else
		int	PL	=P.PL-ThresholdRange;
		int	PH	=P.PH+ThresholdRange;
		int	SL	=P.SL-ThresholdRange;
		int	SH	=P.SH+ThresholdRange;
		int	RL	=P.RL-ThresholdRange;
		int	RH	=P.RH+ThresholdRange;
		int	wPL	=P.PL-wThresholdRange2_PD;
		int	wPH	=P.PH+wThresholdRange2_PB;
		int	wSL	=P.SL-wThresholdRange2_SD;
		int	wSH	=P.SH+wThresholdRange2_SB;
		int	wRL	=P.RL-wThresholdRange;
		int	wRH	=P.RH+wThresholdRange;
#endif
		if((x-SearchDot)<0 || XLen<=(x+SearchDot)){
			continue;
		}
		if((y-SearchDot)<0 || YLen<=(y+SearchDot)){
			continue;
		}

#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(y);
		ts[1]=TargetImageList[1]->GetY(y);
		ts[2]=TargetImageList[2]->GetY(y);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
		if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
			goto	Matched4;
		}

		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched4;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched4;
				}
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched4;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	Matched4;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched4;
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched4;
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched4;
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	Matched4;
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my) || IsPad!=pAlignPage->GetBitFirstPickupFromMaster(mx,my)){
			//Is Target Point Resist ?
			if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange,wThresholdRange,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	Matched4;
				}
			}
			//Is Target Point Silk ?
			else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange,wThresholdRange,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	Matched4;
				}
			}
		}
		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromMaster2(x,y,wThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
				goto	Matched4;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		if(PL-Q->P > 0){
			DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-PH > 0){
			DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		if(SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	Matched4;
		}

		//?s?N?Z???a?R
		if(IsCalcPixelInterPoration==true){
			if(CalcPixelInterPoration(x,y,PL,PH,SL,SH,RL,RH)==true){
				goto	Matched4;
			}
		}

		TempNGBitmap[y][x>>3] |= (0x80>>(x&7));

Matched4:;
	}
}

//???W?X?g?I?V???N?I??
bool	PixelInspectionItem::CalcReInspectionForResistSilk(int mx,int my,int tx,int ty,int wThresholdRange_B,int wThresholdRange_D,int wThresholdRange2_B,int wThresholdRange2_D,DetailType DPixelMode)
{
	int x=(mx>>8);
	int y=(my>>8);
	BYTE *ts[3];
	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	int	PL,PH,SL,SH,RL,RH;
	PL=PixDataForResistSilk[DPixelMode][y][x].PL-wThresholdRange2_D;
	PH=PixDataForResistSilk[DPixelMode][y][x].PH+wThresholdRange2_B;
	SL=PixDataForResistSilk[DPixelMode][y][x].SL-wThresholdRange2_D;
	SH=PixDataForResistSilk[DPixelMode][y][x].SH+wThresholdRange2_B;
	RL=PixDataForResistSilk[DPixelMode][y][x].RL-wThresholdRange_D;
	RH=PixDataForResistSilk[DPixelMode][y][x].RH+wThresholdRange_B;
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		return true;
	}

	return false;
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
bool	PixelInspectionItem::ExecuteProcessingFromMaster1(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange)
{
	bool	IsPad,IsSilk;

	BYTE	*ts[3];
	ts[0]=TargetImageList[0]->GetY(y);
	ts[1]=TargetImageList[1]->GetY(y);
	ts[2]=TargetImageList[2]->GetY(y);

	int	mx,my;
	if(pAlignPage==NULL){
		mx	=x;
		my	=y;
	}
	else{
		mx	=x-pAlignPage->GetShiftXFromMaster(x,y);
		my	=y-pAlignPage->GetShiftYFromMaster(x,y);
	}
	if(mx<0 || XLen<=mx){
		return true;
	}
	if(my<0 || YLen<=my){
		return true;
	}
	PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE

	if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
		return true;
	}

	int wThresholdRange_B=ThresholdRange;
	int wThresholdRange_D=ThresholdRange;

	int wThresholdRange2_PB,wThresholdRange2_PD;
	int wThresholdRange2_SB,wThresholdRange2_SD;

	int wThresholdRange2_B,wThresholdRange2_D;
	wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
	if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
		//?p?b?h?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
		IsPad	=true;
		IsSilk	=false;
		if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			IsSilk	=true;
		}
	}
	else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
		//?V???N?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
		IsPad	=false;
		IsSilk	=true;
	}
	else if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
		//???I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
		IsPad	=false;
		IsSilk	=false;
	}
	else{
		//???W?X?g?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
		IsPad	=false;
		IsSilk	=false;
	}

	//?É ?Å·?Åë?l?I?????A???I??
	if(((P.PL+P.PH)>>1)<=127){
		wThresholdRange2_PB=wThresholdRange2_B;
		wThresholdRange2_PD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_PB=wThresholdRange2_D;
		wThresholdRange2_PD=wThresholdRange2_B;
	}
	if(((P.SL+P.SH)>>1)<=127){
		wThresholdRange2_SB=wThresholdRange2_B;
		wThresholdRange2_SD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_SB=wThresholdRange2_D;
		wThresholdRange2_SD=wThresholdRange2_B;
	}

	int	PL	=P.PL-wThresholdRange2_PD;
	int	PH	=P.PH+wThresholdRange2_PB;
	int	SL	=P.SL-wThresholdRange2_SD;
	int	SH	=P.SH+wThresholdRange2_SB;
	int	RL	=P.RL-wThresholdRange_D;
	int	RH	=P.RH+wThresholdRange_B;
/*
	if(PL>PH || SL>SH || RL>RH){
		return true;
	}
*/
	//?V???N?u?I?I?T?o?h?b?g
	int SearchDot;
	if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
		SearchDot	=SearchDotBase+1;
	}
	else{
		SearchDot	=SearchDotBase;
	}

	if(mx-SearchDot<0 || XLen<=mx+SearchDot){
		return true;
	}
	if(my-SearchDot<0 || YLen<=my+SearchDot){
		return true;
	}

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
	if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
		return true;
	}
	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData &P1=PixData[my+dy][mx+dx];
			if(P1.StdDisorder==255){
				continue;
			}
			PL=P1.PL-ThresholdRange;
			PH=P1.PH+ThresholdRange;
			SL=P1.SL-ThresholdRange;
			SH=P1.SH+ThresholdRange;
			RL=P1.RL-ThresholdRange;
			RH=P1.RH+ThresholdRange;
/*			if(PL>PH || SL>SH || RL>RH){
				continue;
			}
*/
			if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
	PixelInsData &P1=PixData[my][mx];
	PixelInsData P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			PixelInsData	&P2=PixData[my+dy][mx+dx];
			if(CalcPixelInsData(P1,P2,P3)==true){
				int	PL3	=P3.PL-ThresholdRange;
				int	PH3	=P3.PH+ThresholdRange;
				int	SL3	=P3.SL-ThresholdRange;
				int	SH3	=P3.SH+ThresholdRange;
				int	RL3	=P3.RL-ThresholdRange;
				int	RH3	=P3.RH+ThresholdRange;
/*				if(PL3>PH3 || SL3>SH3 || RL3>RH3){
					continue;
				}
*/
				if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
					return true;
				}
			}
		}
	}
	//?V???N?c?C???c
	if(IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my) || IsPad!=pAlignPage->GetBitFirstPickupFromMaster(mx,my)){
		//Is Target Point Resist ?
///		if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
		if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
			//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
			if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
				return true;
			}
		}
		//Is Target Point Silk ?
///		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
			if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
				return true;
			}
		}
	}
	return false;
}

bool	PixelInspectionItem::ExecuteProcessingFromMaster2(int x,int y,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange)
{
	bool	IsPad,IsSilk;

	int	mx,my;
	if(pAlignPage==NULL){
		mx	=x;
		my	=y;
	}
	else{
		mx	=x-pAlignPage->GetShiftXFromMaster(x,y);
		my	=y-pAlignPage->GetShiftYFromMaster(x,y);
	}
	if(mx<0 || XLen<=mx){
		return true;
	}
	if(my<0 || YLen<=my){
		return true;
	}
	PixelInsData &P	=PixData[my][mx];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		return true;
	}

	int wThresholdRange_B=ThresholdRange;
	int wThresholdRange_D=ThresholdRange;

	int wThresholdRange2_PB,wThresholdRange2_PD;
	int wThresholdRange2_SB,wThresholdRange2_SD;

	int wThresholdRange2_B,wThresholdRange2_D;
	wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
	if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
		//?p?b?h?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
		IsPad	=true;
		IsSilk	=false;
		if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			IsSilk	=true;
		}
	}
	else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
		//?V???N?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
		IsPad	=false;
		IsSilk	=true;
	}
	else if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
		//???I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
		IsPad	=false;
		IsSilk	=false;
	}
	else{
		//???W?X?g?I?e??
		wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
		wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
		IsPad	=false;
		IsSilk	=false;
	}

	//?É ?Å·?Åë?l?I?????A???I??
	if(((P.PL+P.PH)>>1)<=127){
		wThresholdRange2_PB=wThresholdRange2_B;
		wThresholdRange2_PD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_PB=wThresholdRange2_D;
		wThresholdRange2_PD=wThresholdRange2_B;
	}
	if(((P.SL+P.SH)>>1)<=127){
		wThresholdRange2_SB=wThresholdRange2_B;
		wThresholdRange2_SD=wThresholdRange2_D;
	}
	else{
		wThresholdRange2_SB=wThresholdRange2_D;
		wThresholdRange2_SD=wThresholdRange2_B;
	}

	int	PL	=P.PL-ThresholdRange;
	int	PH	=P.PH+ThresholdRange;
	int	SL	=P.SL-ThresholdRange;
	int	SH	=P.SH+ThresholdRange;
	int	RL	=P.RL-ThresholdRange;
	int	RH	=P.RH+ThresholdRange;
	int	wPL	=P.PL-wThresholdRange2_PD;
	int	wPH	=P.PH+wThresholdRange2_PB;
	int	wSL	=P.SL-wThresholdRange2_SD;
	int	wSH	=P.SH+wThresholdRange2_SB;
	int	wRL	=P.RL-wThresholdRange_D;
	int	wRH	=P.RH+wThresholdRange_B;

	//?V???N?u?I?I?T?o?h?b?g
	int SearchDot;
	if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
		SearchDot	=SearchDotBase+1;
	}
	else{
		SearchDot	=SearchDotBase;
	}
	if(x-SearchDot<0 || XLen<=x+SearchDot){
		return true;
	}
	if(y-SearchDot<0 || YLen<=y+SearchDot){
		return true;
	}

	BYTE	*ts[3];
	ts[0]=TargetImageList[0]->GetY(y);
	ts[1]=TargetImageList[1]->GetY(y);
	ts[2]=TargetImageList[2]->GetY(y);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
	if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
		return true;
	}
	//?u?I?A?I?Å‚?f
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=SH){
				if(Q->S<SL && Q2->S<SL){
					continue;
				}
			}
			else{
				if(Q2->S>SH){
					continue;
				}
			}
			if(Q->P<=PH){
				if(Q->P<PL && Q2->P<PL){
					continue;
				}
			}
			else{
				if(Q2->P>PH){
					continue;
				}
			}
			if(Q->R<=RH){
				if(Q->R<RL && Q2->R<RL){
					continue;
				}
			}
			else{
				if(Q2->R>RH){
					continue;
				}
			}
			return true;
		}
	}
	//?V???N?c?C???c
	if(IsSilk!=pAlignPage->GetBitPickupFromMaster(mx,my) || IsPad!=pAlignPage->GetBitFirstPickupFromMaster(mx,my)){
		//Is Target Point Resist ?
///		if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
		if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
			//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
			if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
				return true;
			}
		}
		//Is Target Point Silk ?
///		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
		else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
			//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
			if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
				return true;
			}
		}
	}
	return false;
}

void	PixelInspectionItem::ExecuteProcessing(PureFlexAreaList *NGBitArea,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int BrightnessRange,BYTE **DestNGBitmap)
{
	//NG?a?a?Å·?Åë?a?I?I?A???ÅC?É ?E?Åë
	//?Å~?Åë?a?I?I???n?A???e?e???a???Åë?I?A?A???ÅC?ÅE?e
	int AreaSize=NGBitArea->GetPatternByte();
	if(AreaSize>40){
		int MaxL=max(NGBitArea->GetMaxX()-NGBitArea->GetMinX(),NGBitArea->GetMaxY()-NGBitArea->GetMinY());
		if(MaxL<((int)(AreaSize>>2))){
			return;
		}
//		int MinL=min(NGBitArea->GetMaxX()-NGBitArea->GetMinX(),NGBitArea->GetMaxY()-NGBitArea->GetMinY());
//		if(MinL>((int)(AreaSize>>4))){
//			return;
//		}
	}

	int LineLen	=NGBitArea->GetFLineLen();

	list<point> point_list;

#ifdef Debug
	BYTE	*ts[3];
	int	x,xx,yy;
	int XRange,YRange;
	int	mx[8][8],my[8][8];
	int mmx,mmy;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P,P1,P2,P3;
	int	PL,wPL,PL3;
	int	PH,wPH,PH3;
	int	SL,wSL,SL3;
	int	SH,wSH,SH3;
	int	RL,wRL,RL3;
	int	RH,wRH,RH3;
	int SearchDot;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	bool OutSearch;

	int		Index;
	int		xi,yi;
	int		xxi,yyi;
	//?T?o?Q?h?b?g?a?i25?G???A?j?I???ÅCNG?A???T?d???[?N
	BYTE	NGCheckedCnt[25];
	//?????S?~?S?ING?c?cOK?E?E?A???s?N?Z???d?U??
	BYTE	CanardBitmap[16];

	int i;
	int x1,x2,y;
	list<point>::iterator p;
	for(i=0;i<LineLen;i++){
		x1	=NGBitArea->GetFLineLeftX(i);
		x2	=NGBitArea->GetFLineRightX(i);
		y	=NGBitArea->GetFLineAbsY(i);
		for(x=x1;x<x2;x++){
#else
	for(int i=0;i<LineLen;i++){
		int x1	=NGBitArea->GetFLineLeftX(i);
		int x2	=NGBitArea->GetFLineRightX(i);
		int y	=NGBitArea->GetFLineAbsY(i);
		for(int x=x1;x<x2;x++){
			bool OutSearch;
			list<point>::iterator p;
#endif
			//?i?Ä?E?u?i?????I?S?~?S?}?X?I?Å˜?a?s?N?Z???j?c?c?A?`?F?b?N?I?Y?s?N?Z???d?o?I?ÅE
			for(p=point_list.begin();p!=point_list.end();p++){
				if(x>=p->x && x<p->x+4 && y>=p->y && y<p->y+4){
					break;
				}
			}
			if(p!=point_list.end()){
				continue;
			}
			//?i?Ä?E?u?i?????I?S?~?S?}?X?I?Å˜?a?s?N?Z???j?d?o?^
			point pp={x,y};
			point_list.push_back(pp);

			if(x-4<0 || XLen<=x+10){
				continue;
			}
			if(y-4<0 || YLen<=y+10){
				continue;
			}
			OutSearch=false;

//////////////?}?X?^?[?a???A?I???ÅC//////////////
#ifdef Debug
			if(y==DebugPointY && x==DebugPointX){
				DebugPoint++;
			}
			//???u?Å‚
			Index=0;
			memset(NGCheckedCnt,0,25);
			memset(CanardBitmap,0,16);

			//?W?~?W?}?X?I???ÅC
			XRange=x+6;
			YRange=y+6;
			yi=0;
			for(yy=y-2;yy<YRange;yy++,yi++){
#else
			int	mx[8][8],my[8][8];
			int tmX,tmY;
			int mtX,mtY;
			int SearchDot;
			int wThresholdRange_B	,wThresholdRange_D;
			int wThresholdRange2_B	,wThresholdRange2_D;
			int wThresholdRange2_PB	,wThresholdRange2_PD;
			int wThresholdRange2_SB	,wThresholdRange2_SD;
			//???u?Å‚
			int		Index=0;
			//?T?o?Q?h?b?g?a?i25?G???A?j?I???ÅCNG?A???T?d???[?N
			BYTE	NGCheckedCnt[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			//?????S?~?S?ING?c?cOK?E?E?A???s?N?Z???d?U??
			BYTE	CanardBitmap[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

			//?W?~?W?}?X?I???ÅC
			int xx,yy;
			int XRange=x+6;
			int YRange=y+6;
			int xi,yi=0;
			for(yy=y-2;yy<YRange;yy++,yi++){
				BYTE	*ts[3];
#endif
				xi=0;
				ts[0]=TargetImageList[0]->GetY(yy);
				ts[1]=TargetImageList[1]->GetY(yy);
				ts[2]=TargetImageList[2]->GetY(yy);
				for(xx=x-2;xx<XRange;xx++,xi++){
					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
						mx[yi][xi]	=xx;
						my[yi][xi]	=yy;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
						mx[yi][xi]	=xx+tmX;
						my[yi][xi]	=yy+tmY;
					}

					if(mx[yi][xi]-2<0 || XLen<=mx[yi][xi]+2){
						OutSearch=true;
						break;
					}
					if(my[yi][xi]-2<0 || YLen<=my[yi][xi]+2){
						OutSearch=true;
						break;
					}

//					//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
//					if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
//						continue;
//					}
#ifdef Debug
					if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){		//?}?X?N?O?I?e??
						//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
						if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
							NGCheckedCnt[Index]++;
						}
						continue;
					}

					wThresholdRange_B=wThresholdRange_D=wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
					if(pAlignPage->GetBitFirstPickupFromTarget(xx,yy)==true){
						//?p?b?h?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
					}
					else if(pAlignPage->GetBitPickupFromTarget(xx,yy)==true){
						//???W?X?g?E?V???N?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
					}
					else if(pHoleAlignPage->GetBitmapFringe(xx,yy)==true){
						//???I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
					}
					else{
						//???W?X?g?E?V???N?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
					}

					//?É ?Å·?Åë?l?I?????A???I??
					if(((P.PL+P.PH)>>1)<=127){
						wThresholdRange2_PB=wThresholdRange2_B;
						wThresholdRange2_PD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_PB=wThresholdRange2_D;
						wThresholdRange2_PD=wThresholdRange2_B;
					}
					if(((P.SL+P.SH)>>1)<=127){
						wThresholdRange2_SB=wThresholdRange2_B;
						wThresholdRange2_SD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_SB=wThresholdRange2_D;
						wThresholdRange2_SD=wThresholdRange2_B;
					}
#ifndef Debug
					int PL,PH,SL,SH,RL,RH;
#endif
					PL		=P.PL-wThresholdRange2_PD;
					PH		=P.PH+wThresholdRange2_PB;
					SL		=P.SL-wThresholdRange2_SD;
					SH		=P.SH+wThresholdRange2_SB;
					RL		=P.RL-wThresholdRange_D;
					RH		=P.RH+wThresholdRange_B;

					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
					if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
						continue;
					}
					NGCheckedCnt[Index]++;
				}
			}
			if(OutSearch==true){
				continue;
			}
			if(NGCheckedCnt[Index]==0){
				goto	ALLMATCHED1_1;
			}

			//?u?I?A?I?Å‚?f
			for(int Len=1;Len<=2;Len++){
				int	dx;
				int	dy=-Len;
				for(dx=-Len;dx<Len;dx++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P1.PL-wThresholdRange2_PD;
							PH		=P1.PH+wThresholdRange2_PB;
							SL		=P1.SL-wThresholdRange2_SD;
							SH		=P1.SH+wThresholdRange2_SB;
							RL		=P1.RL-wThresholdRange_D;
							RH		=P1.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED1_1;
					}
				}
				dx=Len;
				for(;dy<Len;dy++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P1.PL-wThresholdRange2_PD;
							PH		=P1.PH+wThresholdRange2_PB;
							SL		=P1.SL-wThresholdRange2_SD;
							SH		=P1.SH+wThresholdRange2_SB;
							RL		=P1.RL-wThresholdRange_D;
							RH		=P1.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED1_1;
					}
				}
				dy=Len;
				for(;dx>-Len;dx--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P1.PL-wThresholdRange2_PD;
							PH		=P1.PH+wThresholdRange2_PB;
							SL		=P1.SL-wThresholdRange2_SD;
							SH		=P1.SH+wThresholdRange2_SB;
							RL		=P1.RL-wThresholdRange_D;
							RH		=P1.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED1_1;
					}
				}
				dx=-Len;
				for(;dy>-Len;dy--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P1.PL-wThresholdRange2_PD;
							PH		=P1.PH+wThresholdRange2_PB;
							SL		=P1.SL-wThresholdRange2_SD;
							SH		=P1.SH+wThresholdRange2_SB;
							RL		=P1.RL-wThresholdRange_D;
							RH		=P1.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED1_1;
					}
				}
			}

#ifndef Debug
			int		xxi,yyi;
#endif
			//NGCheckedCnt[25]?a?A?Å ?I?_?d?I?O
			MinNGCheckedCnt(NGCheckedCnt,xxi,yyi,Index);

			yi=2;

			//?????I?S?~?S?}?X?I?Y???ÅC
			for(yy=y;yy<YRange-2;yy++,yi++){
#ifndef Debug
				BYTE	*ts[3];
#endif
				xi=2;
				ts[0]=TargetImageList[0]->GetY(yy);
				ts[1]=TargetImageList[1]->GetY(yy);
				ts[2]=TargetImageList[2]->GetY(yy);
				for(xx=x;xx<XRange-2;xx++,xi++){
					//ExecuteProcessing1?A?u?EOK?A?E?A?A?Åë?e?e???I?2?ÅP?e
					if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))==0){
						continue;
					}

					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
					}
#ifdef Debug
					mmx		=xx+tmX+xxi;
					mmy		=yy+tmY+yyi;
#else
					int mmx	=xx+tmX+xxi;
					int mmy	=yy+tmY+yyi;
#endif
					if(mmx-(SearchDotBase+1)<0 || XLen<=mmx+SearchDotBase+1){
						continue;
					}
					if(mmy-(SearchDotBase+1)<0 || YLen<=mmy+SearchDotBase+1){
						continue;
					}
#ifdef Debug
					if(mmy==DebugPointY && mmx==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[mmy][mmx];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[mmy][mmx];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
						continue;
					}

					wThresholdRange_B=wThresholdRange_D=wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
					if(pAlignPage->GetBitFirstPickupFromTarget(xx,yy)==true){
						//?p?b?h?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
						SearchDot	=SearchDotBase;
					}
					else if(pAlignPage->GetBitPickupFromTarget(xx,yy)==true){
						//???W?X?g?E?V???N?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
						SearchDot	=SearchDotBase+1;
					}
					else if(pHoleAlignPage->GetBitmapFringe(xx,yy)==true){
						//???I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
						SearchDot	=SearchDotBase;
					}
					else{
						//???W?X?g?E?V???N?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
						SearchDot	=SearchDotBase;
					}

					//?É ?Å·?Åë?l?I?????A???I??
					if(((P.PL+P.PH)>>1)<=127){
						wThresholdRange2_PB=wThresholdRange2_B;
						wThresholdRange2_PD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_PB=wThresholdRange2_D;
						wThresholdRange2_PD=wThresholdRange2_B;
					}
					if(((P.SL+P.SH)>>1)<=127){
						wThresholdRange2_SB=wThresholdRange2_B;
						wThresholdRange2_SD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_SB=wThresholdRange2_D;
						wThresholdRange2_SD=wThresholdRange2_B;
					}
#ifndef Debug
					int PL,PH,SL,SH,RL,RH;
#endif
					PL		=P.PL-wThresholdRange2_PD;
					PH		=P.PH+wThresholdRange2_PB;
					SL		=P.SL-wThresholdRange2_SD;
					SH		=P.SH+wThresholdRange2_SB;
					RL		=P.RL-wThresholdRange_D;
					RH		=P.RH+wThresholdRange_B;

					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
					if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
						goto	MATCHED1_1;
					}

					//?u?I?A?I?Å‚?f
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						for(dx=-Len;dx<Len;dx++){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							PL=P1.PL-wThresholdRange2_PD;
							PH=P1.PH+wThresholdRange2_PB;
							SL=P1.SL-wThresholdRange2_SD;
							SH=P1.SH+wThresholdRange2_SB;
							RL=P1.RL-wThresholdRange_D;
							RH=P1.RH+wThresholdRange_B;
/*							if(PL>PH || SL>SH || RL>RH){
								continue;
							}
*/
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								goto	MATCHED1_1;
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							PL=P1.PL-wThresholdRange2_PD;
							PH=P1.PH+wThresholdRange2_PB;
							SL=P1.SL-wThresholdRange2_SD;
							SH=P1.SH+wThresholdRange2_SB;
							RL=P1.RL-wThresholdRange_D;
							RH=P1.RH+wThresholdRange_B;
/*							if(PL>PH || SL>SH || RL>RH){
								continue;
							}
*/
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								goto	MATCHED1_1;
							}
						}
						dy=Len;
						for(;dx>-Len;dx--){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							PL=P1.PL-wThresholdRange2_PD;
							PH=P1.PH+wThresholdRange2_PB;
							SL=P1.SL-wThresholdRange2_SD;
							SH=P1.SH+wThresholdRange2_SB;
							RL=P1.RL-wThresholdRange_D;
							RH=P1.RH+wThresholdRange_B;
/*							if(PL>PH || SL>SH || RL>RH){
								continue;
							}
*/
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								goto	MATCHED1_1;
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							PL=P1.PL-wThresholdRange2_PD;
							PH=P1.PH+wThresholdRange2_PB;
							SL=P1.SL-wThresholdRange2_SD;
							SH=P1.SH+wThresholdRange2_SB;
							RL=P1.RL-wThresholdRange_D;
							RH=P1.RH+wThresholdRange_B;
/*							if(PL>PH || SL>SH || RL>RH){
								continue;
							}
*/
							if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
								goto	MATCHED1_1;
							}
						}
					}

					//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
					P1				=PixData[mmy][mmx];
#else
					PixelInsData &P1=PixData[mmy][mmx];
					PixelInsData P3;
#endif
					P3.SL=Q->S;
					P3.PL=Q->P;
					P3.RL=Q->R;
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						for(dx=-Len;dx<Len;dx++){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
#ifndef Debug
								int PL3,PH3,SL3,SH3,RL3,RH3;
#endif
								PL3		=P3.PL-wThresholdRange2_PD;
								PH3		=P3.PH+wThresholdRange2_PB;
								SL3		=P3.SL-wThresholdRange2_SD;
								SH3		=P3.SH+wThresholdRange2_SB;
								RL3		=P3.RL-wThresholdRange_D;
								RH3		=P3.RH+wThresholdRange_B;

								if(PL3>PH3 || SL3>SH3 || RL3>RH3){
									continue;
								}
								if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
									goto	MATCHED1_1;
								}
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
#ifndef Debug
								int PL3,PH3,SL3,SH3,RL3,RH3;
#endif
								PL3		=P3.PL-wThresholdRange2_PD;
								PH3		=P3.PH+wThresholdRange2_PB;
								SL3		=P3.SL-wThresholdRange2_SD;
								SH3		=P3.SH+wThresholdRange2_SB;
								RL3		=P3.RL-wThresholdRange_D;
								RH3		=P3.RH+wThresholdRange_B;

								if(PL3>PH3 || SL3>SH3 || RL3>RH3){
									continue;
								}
								if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
									goto	MATCHED1_1;
								}
							}
						}
						dy=Len;
						for(;dx>-Len;dx--){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
#ifndef Debug
								int PL3,PH3,SL3,SH3,RL3,RH3;
#endif
								PL3		=P3.PL-wThresholdRange2_PD;
								PH3		=P3.PH+wThresholdRange2_PB;
								SL3		=P3.SL-wThresholdRange2_SD;
								SH3		=P3.SH+wThresholdRange2_SB;
								RL3		=P3.RL-wThresholdRange_D;
								RH3		=P3.RH+wThresholdRange_B;

								if(PL3>PH3 || SL3>SH3 || RL3>RH3){
									continue;
								}
								if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
									goto	MATCHED1_1;
								}
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
#ifndef Debug
								int PL3,PH3,SL3,SH3,RL3,RH3;
#endif
								PL3		=P3.PL-wThresholdRange2_PD;
								PH3		=P3.PH+wThresholdRange2_PB;
								SL3		=P3.SL-wThresholdRange2_SD;
								SH3		=P3.SH+wThresholdRange2_SB;
								RL3		=P3.RL-wThresholdRange_D;
								RH3		=P3.RH+wThresholdRange_B;

							if(PL3>PH3 || SL3>SH3 || RL3>RH3){
								continue;
								}
								if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
									goto	MATCHED1_1;
								}
							}
						}
					}

					//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
					if(tmX!=-mtX || tmY!=-mtY){
						if(ExecuteProcessingFromMaster1(xx,yy,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
							goto	MATCHED1_1;
						}
					}

					//???ÅCe??l?A?I?ÅE?d?Z?o
					BYTE DiffPSR=0;
					PixelInsData &Pw=PixData[mmy][mmx];
					if(Pw.PL-Q->P > 0){
						DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
					}
					else if(Q->P-Pw.PH > 0){
						DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
					}
					if(Pw.SL-Q->S > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					else if(Q->S-Pw.SH > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					if(Pw.RL-Q->R > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					else if(Q->R-Pw.RH > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
					if(DiffPSR<BrightnessRange){
						goto	MATCHED1_1;
					}

					//?3?XNG?I?O???I?e???A?Å‚?I?U?Ucontinue
					continue;
MATCHED1_1:;
					//OK?A?Å‚?f?3?e???s?N?Z??
//					DestNGBitmap[yy][xx>>3] &= ~(0x80>>(xx&7));
					CanardBitmap[((yi-2)<<2)+xi-2]=1;
				}
			}
			goto NEXT1;

ALLMATCHED1_1:;
//			for(yy=y;yy<YRange-2;yy++){
//				for(xx=x;xx<XRange-2;xx++){
//					DestNGBitmap[yy][xx>>3] &= ~(0x80>>(xx&7));
//				}
//			}
			int i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
						CanardBitmap[i]=1;
					}
				}
			}

//////////////???ÅC?a???A?I???ÅC//////////////
NEXT1:;
#ifdef Debug
			if(y==DebugPointY && x==DebugPointX){
				DebugPoint++;
			}
#endif
			//???u?Å‚
			Index=0;

			if(NGCheckedCnt[Index]==0){
				goto	ALLMATCHED2_1;
			}
			memset(NGCheckedCnt+1,0,24);

			//?u?I?A?I?Å‚?f
			for(int Len=1;Len<=2;Len++){
				int	dx;
				int	dy=-Len;
				for(dx=-Len;dx<Len;dx++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}

							wThresholdRange_B=wThresholdRange_D=wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
							if(pAlignPage->GetBitFirstPickupFromTarget(xx,yy)==true){
								//?p?b?h?I?e??
								wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
								wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
							}
							else if(pAlignPage->GetBitPickupFromTarget(xx,yy)==true){
								//???W?X?g?E?V???N?I?e??
								wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
								wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
							}
							else if(pHoleAlignPage->GetBitmapFringe(xx,yy)==true){
								//???I?e??
								wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
								wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
							}
							else{
								//???W?X?g?E?V???N?I?e??
								wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
								wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
							}

							//?É ?Å·?Åë?l?I?????A???I??
							if(((P.PL+P.PH)>>1)<=127){
								wThresholdRange2_PB=wThresholdRange2_B;
								wThresholdRange2_PD=wThresholdRange2_D;
							}
							else{
								wThresholdRange2_PB=wThresholdRange2_D;
								wThresholdRange2_PD=wThresholdRange2_B;
							}
							if(((P.SL+P.SH)>>1)<=127){
								wThresholdRange2_SB=wThresholdRange2_B;
								wThresholdRange2_SD=wThresholdRange2_D;
							}
							else{
								wThresholdRange2_SB=wThresholdRange2_D;
								wThresholdRange2_SD=wThresholdRange2_B;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P.PL-wThresholdRange2_PD;
							PH		=P.PH+wThresholdRange2_PB;
							SL		=P.SL-wThresholdRange2_SD;
							SH		=P.SH+wThresholdRange2_SB;
							RL		=P.RL-wThresholdRange_D;
							RH		=P.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED2_1;
					}
				}
				dx=Len;
				for(;dy<Len;dy++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P.PL-wThresholdRange2_PD;
							PH		=P.PH+wThresholdRange2_PB;
							SL		=P.SL-wThresholdRange2_SD;
							SH		=P.SH+wThresholdRange2_SB;
							RL		=P.RL-wThresholdRange_D;
							RH		=P.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED2_1;
					}
				}
				dy=Len;
				for(;dx>-Len;dx--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P.PL-wThresholdRange2_PD;
							PH		=P.PH+wThresholdRange2_PB;
							SL		=P.SL-wThresholdRange2_SD;
							SH		=P.SH+wThresholdRange2_SB;
							RL		=P.RL-wThresholdRange_D;
							RH		=P.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED2_1;
					}
				}
				dx=-Len;
				for(;dy>-Len;dy--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
#ifndef Debug
							int PL,PH,SL,SH,RL,RH;
#endif
							PL		=P.PL-wThresholdRange2_PD;
							PH		=P.PH+wThresholdRange2_PB;
							SL		=P.SL-wThresholdRange2_SD;
							SH		=P.SH+wThresholdRange2_SB;
							RL		=P.RL-wThresholdRange_D;
							RH		=P.RH+wThresholdRange_B;

							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	ALLMATCHED2_1;
					}
				}
			}

			//NGCheckedCnt[25]?a?A?Å ?I?_?d?I?O
			MinNGCheckedCnt(NGCheckedCnt,xxi,yyi,Index);

			yi=2;

			//?????I?S?~?S?}?X?I?Y???ÅC
			for(yy=y;yy<YRange-2;yy++,yi++){
#ifndef Debug
				BYTE	*ts[3];
#endif
				if((yy+yyi-SearchDot)<0 || (yy+yyi+SearchDot)>=YLen){
					continue;
				}
				xi=2;
				ts[0]=TargetImageList[0]->GetY(yy+yyi);
				ts[1]=TargetImageList[1]->GetY(yy+yyi);
				ts[2]=TargetImageList[2]->GetY(yy+yyi);
				for(xx=x;xx<XRange-2;xx++,xi++){
					//ExecuteProcessing1?A?u?EOK?A?E?A?A?Åë?e?e???I?2?ÅP?e
					if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))==0){
						continue;
					}
					if((xx+xxi-SearchDot)<0 || (xx+xxi+SearchDot)>=XLen){
						continue;
					}

					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
					}
#ifdef Debug
					if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){
						continue;
					}

					wThresholdRange_B=wThresholdRange_D=wThresholdRange2_B=wThresholdRange2_D=(ThresholdRange<<7)/((P.RL+P.RH)>>1);
					if(pAlignPage->GetBitFirstPickupFromTarget(xx,yy)==true){
						//?p?b?h?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdP_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdP_D;
						SearchDot	=SearchDotBase;
					}
					else if(pAlignPage->GetBitPickupFromTarget(xx,yy)==true){
						//?V???N?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdS_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdS_D;
						SearchDot	=SearchDotBase+1;
					}
					else if(pHoleAlignPage->GetBitmapFringe(xx,yy)==true){
						//???I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdH_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdH_D;
						SearchDot	=SearchDotBase;
					}
					else{
						//???W?X?g?I?e??
						wThresholdRange2_B+=abs(ThresholdRange-wThresholdRange2_B)*NGThresholdR_B;
						wThresholdRange2_D+=abs(ThresholdRange-wThresholdRange2_D)*NGThresholdR_D;
						SearchDot	=SearchDotBase;
					}

					//?É ?Å·?Åë?l?I?????A???I??
					if(((P.PL+P.PH)>>1)<=127){
						wThresholdRange2_PB=wThresholdRange2_B;
						wThresholdRange2_PD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_PB=wThresholdRange2_D;
						wThresholdRange2_PD=wThresholdRange2_B;
					}
					if(((P.SL+P.SH)>>1)<=127){
						wThresholdRange2_SB=wThresholdRange2_B;
						wThresholdRange2_SD=wThresholdRange2_D;
					}
					else{
						wThresholdRange2_SB=wThresholdRange2_D;
						wThresholdRange2_SD=wThresholdRange2_B;
					}
#ifndef Debug
					int PL,PH,SL,SH,RL,RH;
					int wPL,wPH,wSL,wSH,wRL,wRH;
#endif
					PL	=wPL	=P.PL-wThresholdRange2_PD;
					PH	=wPH	=P.PH+wThresholdRange2_PB;
					SL	=wSL	=P.SL-wThresholdRange2_SD;
					SH	=wSH	=P.SH+wThresholdRange2_SB;
					RL	=wRL	=P.RL-wThresholdRange_D;
					RH	=wRH	=P.RH+wThresholdRange_B;

					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx+xxi],ts[1][xx+xxi],ts[2][xx+xxi])];
					if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
						goto	MATCHED2_1;
					}

					//?u?I?A?I?Å‚?f
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(dx=-Len;dx<Len;dx++){
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								goto	MATCHED2_1;
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								goto	MATCHED2_1;
							}
						}
						dy=Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(;dx>-Len;dx--){
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								goto	MATCHED2_1;
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
								goto	MATCHED2_1;
							}
						}
					}

					//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(dx=-Len;dx<Len;dx++){
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=SH){
								if(Q->S<SL && Q2->S<SL){
									continue;
								}
							}
							else{
								if(Q2->S>SH){
									continue;
								}
							}
							if(Q->P<=PH){
								if(Q->P<PL && Q2->P<PL){
									continue;
								}
							}
							else{
								if(Q2->P>PH){
									continue;
								}
							}
							if(Q->R<=RH){
								if(Q->R<RL && Q2->R<RL){
									continue;
								}
							}
							else{
								if(Q2->R>RH){
									continue;
								}
							}
							goto	MATCHED2_1;
						}
						dx=Len;
						for(;dy<Len;dy++){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=SH){
								if(Q->S<SL && Q2->S<SL){
									continue;
								}
							}
							else{
								if(Q2->S>SH){
									continue;
								}
							}
							if(Q->P<=PH){
								if(Q->P<PL && Q2->P<PL){
									continue;
								}
							}
							else{
								if(Q2->P>PH){
									continue;
								}
							}
							if(Q->R<=RH){
								if(Q->R<RL && Q2->R<RL){
									continue;
								}
							}
							else{
								if(Q2->R>RH){
									continue;
								}
							}
							goto	MATCHED2_1;
						}
						dy=Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(;dx>-Len;dx--){
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=SH){
								if(Q->S<SL && Q2->S<SL){
									continue;
								}
							}
							else{
								if(Q2->S>SH){
									continue;
								}
							}
							if(Q->P<=PH){
								if(Q->P<PL && Q2->P<PL){
									continue;
								}
							}
							else{
								if(Q2->P>PH){
									continue;
								}
							}
							if(Q->R<=RH){
								if(Q->R<RL && Q2->R<RL){
									continue;
								}
							}
							else{
								if(Q2->R>RH){
									continue;
								}
							}
							goto	MATCHED2_1;
						}
						dx=-Len;
						for(;dy>-Len;dy--){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=SH){
								if(Q->S<SL && Q2->S<SL){
									continue;
								}
							}
							else{
								if(Q2->S>SH){
									continue;
								}
							}
							if(Q->P<=PH){
								if(Q->P<PL && Q2->P<PL){
									continue;
								}
							}
							else{
								if(Q2->P>PH){
									continue;
								}
							}
							if(Q->R<=RH){
								if(Q->R<RL && Q2->R<RL){
									continue;
								}
							}
							else{
								if(Q2->R>RH){
									continue;
								}
							}
							goto	MATCHED2_1;
						}
					}

					//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
					if(tmX!=-mtX || tmY!=-mtY){
						if(ExecuteProcessingFromMaster2(xx+xxi,yy+yyi,ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange)==true){
							goto	MATCHED2_1;
						}
					}

					//???ÅCe??l?A?I?ÅE?d?Z?o
					BYTE DiffPSR=0;
					if(PL-Q->P > 0){
						DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
					}
					else if(Q->P-PH > 0){
						DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
					}
					if(SL-Q->S > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					else if(Q->S-SH > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					if(RL-Q->R > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					else if(Q->R-RH > 0){
						BYTE wDiffPSR;
						if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
							DiffPSR=wDiffPSR;
						}
					}
					//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
					if(DiffPSR<BrightnessRange){
						goto	MATCHED2_1;
					}

					//NG?I?O???I?e???ACanardBitmap?I?r?b?g?d?O?E?N???A
					CanardBitmap[((yi-2)<<2)+xi-2]=0;
					continue;
MATCHED2_1:;
					//OK?A?Å‚?f?3?e???s?N?Z???A?A?E???a?É ?E?Åë
//					if(CanardBitmap[((yi-2)<<2)+xi-2]==1){
//						CanardBitmap[((yi-2)<<2)+xi-2]=1;
//					}
				}
			}
			goto	NEXT2;

ALLMATCHED2_1:;
			i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if((DestNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
						CanardBitmap[i]=1;
					}
				}
			}
NEXT2:;
			i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if(CanardBitmap[i]==1){
						DestNGBitmap[yy][xx>>3] &= ~(0x80>>(xx&7));
					}
				}
			}
		}
	}
}

//?i???n?d?ÅC?c?ÅE?Å~?I?j?A?I???ÅC???W?b?N?d?A?s
void	PixelInspectionItem::CalcExecuteProcessing(BYTE **DestNGBitmap,int ThresholdRange,int SearchDotBase,double NGThresholdP_B,double NGThresholdP_D,double NGThresholdS_B,double NGThresholdS_D,double NGThresholdR_B,double NGThresholdR_D,double NGThresholdH_B,double NGThresholdH_D,int MinimumNGSizeP,int MinimumNGSizeS,int MinimumNGSizeR,int MinimumNGSizeH,int BrightnessRange)
{
	PureFlexAreaListContainer TempFPack;
	PickupFlexArea(DestNGBitmap,XByte,XLen,YLen,TempFPack);

	//DestNGBitmap?d?N???A
	MatrixBuffClear(DestNGBitmap,0,XByte,YLen);

	int AreaListNumb=TempFPack.GetNumber();
	PureFlexAreaList **AreaList=new PureFlexAreaList*[AreaListNumb];
	int i=0;
	for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext(),i++){
		AreaList[i]=c;
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(i=0;i<AreaListNumb;i++){
			ExecuteProcessing(AreaList[i],ThresholdRange,SearchDotBase,NGThresholdP_B,NGThresholdP_D,NGThresholdS_B,NGThresholdS_D,NGThresholdR_B,NGThresholdR_D,NGThresholdH_B,NGThresholdH_D,BrightnessRange,DestNGBitmap);
		}
	}

	delete []AreaList;
	TempFPack.RemoveAll();

	//NG?T?C?Y?A?U?e?Åë?E?c?ÅP?e
	CheckNGBitmap(DestNGBitmap,MinimumNGSizeP,MinimumNGSizeS,MinimumNGSizeR,MinimumNGSizeH);
}

//NG?T?C?Y?A?U?e?Åë?E?c?ÅP?e
void	PixelInspectionItem::CheckNGBitmap(BYTE **DestNGBitmap,int MinimumNGSizeP,int MinimumNGSizeS,int MinimumNGSizeR,int MinimumNGSizeH)
{
	int SumAreaSize=0;
	PureFlexAreaListContainer TempFPack;
	PickupFlexArea(DestNGBitmap,XByte ,XLen,YLen ,TempFPack);
	for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
		int AreaSize=c->GetPatternByte();
		if(AreaSize<MinimumNGSizeP || AreaSize<MinimumNGSizeS || AreaSize<MinimumNGSizeR || AreaSize<MinimumNGSizeH){
			//?p?b?hor?V???Nor???W?X?g
			int PadCnt		=0;
			int SilkCnt		=0;
			int ResistCnt	=0;
			int HoleCnt		=0;
			int LineLen	=c->GetFLineLen();
			for(int i=0;i<LineLen;i++){
				int x1	=c->GetFLineLeftX(i);
				int x2	=c->GetFLineRightX(i);
				int y	=c->GetFLineAbsY(i);
				for(int x=x1;x<x2;x++){
					if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
						PadCnt++;
					}
					else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
						SilkCnt++;
					}
					else{
						int mx=x+pAlignPage->GetShiftXFromTarget(x,y);
						int my=y+pAlignPage->GetShiftYFromTarget(x,y);
						if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
							HoleCnt++;
						}
						else{
							ResistCnt++;
						}
					}
				}
			}
			//?Å‚?e
			if(PadCnt>=MinimumNGSizeP || SilkCnt>=MinimumNGSizeS || ResistCnt>=MinimumNGSizeR || HoleCnt>=MinimumNGSizeH){
				c=c->GetNext();
				SumAreaSize+=1;
				continue;
			}
			PureFlexAreaList	*CNext=c->GetNext();
			TempFPack.RemoveList(c);
			delete	c;
			c=CNext;
		}
		else{
			c=c->GetNext();
			SumAreaSize+=1;
		}
	}

	//DestNGBitmap?d?N???A
	MatrixBuffClear(DestNGBitmap,0,XByte,YLen);

	//DestNGBitmap?d?A?\?z
	for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext()){
		c->MakeBitData(DestNGBitmap,XLen,YLen);
	}
}

//////////////////////////////////////////////////////
//		?U?Å~???ÅC									//
//////////////////////////////////////////////////////
bool	PixelInspectionItem::ExecuteProcessingForDetail(ResultInItemRoot *Res,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode,int MinimumNGSize,DWORD StartMilisec,int MaxInspectMilisec,PureFlexAreaListContainer &TempFPack,int &SumAreaSize)
{
#ifdef DebugConsole
	//???O?I?v?a
	clock_t	StartTime,EndTime;
	StartTime=clock();
#endif

	//InsCheckedBitmap?d?N???A
	MatrixBuffClear(InsCheckedBitmap,0,XByte,YLen);

#ifndef Debug
	#pragma omp parallel
	{
		#pragma omp for
#endif
		for(int y=0;y<YLen;y++){
			//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
			//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
			ExecuteProcessingForDetail1(y,SearchDotBase,NGThreshold_B,NGThreshold_D,BrightnessRange,DMode);
		}
#ifndef Debug
	}
#endif

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(1)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	//InsCheckedBitmap?d?N???A
	MatrixBuffClear(InsCheckedBitmap,0,XByte,YLen);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
			//?u?I?I???ÅC?a???A?I???ÅC//
			ExecuteProcessingForDetail2(y,SearchDotBase,NGThreshold_B,NGThreshold_D,BrightnessRange,DMode);
		}
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(2)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	//InsCheckedBitmap?d?\?Å 
	MatrixBuffOr(InsCheckedBitmap,(const BYTE **)TempNGBitmap,XByte,YLen);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
			//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
			ExecuteProcessingForDetail3(y,SearchDotBase,NGThreshold_B,NGThreshold_D,BrightnessRange,DMode);
		}
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(3)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YLen;y++){
			//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
			//?u?I?I???ÅC?a???A?I???ÅC//
			ExecuteProcessingForDetail4(y,SearchDotBase,NGThreshold_B,NGThreshold_D,BrightnessRange,DMode);
		}
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(4)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	//NG?I?a?Å·?3?A?O?e?Åë?E?c?ÅP?e
	PickupFlexArea(TempNGBitmap,XByte,XLen,YLen,TempFPack);

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(5.1)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;){
		int AreaSize=c->GetPatternByte();
		if(AreaSize<MinimumNGSize){
			PureFlexAreaList	*CNext=c->GetNext();
			TempFPack.RemoveList(c);
			delete	c;
			c=CNext;
		}
		else{
			c=c->GetNext();
			SumAreaSize+=1;
		}
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(5.2)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
	StartTime=clock();
#endif

	//TempNGBitmap?d?N???A
	MatrixBuffClear(TempNGBitmap,0,XByte,YLen);

	//TempNGBitmap?d?A?\?z
	for(PureFlexAreaList *c=TempFPack.GetFirst();c!=NULL;c=c->GetNext()){
		c->MakeBitData(TempNGBitmap,XLen,YLen);
	}

	//NGBitmap?d?\?Å 
	MatrixBuffOr(NGBitmap,(const BYTE **)TempNGBitmap,XByte,YLen);

	//TempNGBitmap?d?N???A
	MatrixBuffClear(TempNGBitmap,0,XByte,YLen);

	//InsCheckedBitmap?d?N???A
	MatrixBuffClear(InsCheckedBitmap,0,XByte,YLen);

	//TempFPack?d?N???A
	TempFPack.RemoveAll();

	//?Å}?I???_?AHALT?`?F?b?N
	if(SumAreaSize>=Parent->GetParamGlobal()->MaxNGCountsPerCam){
		Res->GetResultInspection()->SetMaxErrorBreak(true);
		return false;
	}
	DWORD	NowTime=GetComputerMiliSec();
	if(NowTime-StartMilisec>=MaxInspectMilisec){
		Res->GetResultInspection()->SetTimeOutBreak(true);
		return false;
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteProcessingForDetail(6)?F%.2f?b\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
#endif

	return true;
}

//==============================================//
//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
//?u?I?I?É ?Å·?Åë?l?A?I???ÅC						//
//???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC			//
//==============================================//
void	PixelInspectionItem::ExecuteProcessingForDetail1(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int	x;
	int	tx,ty;
	int mtX,mtY;
	int tmX,tmY;
	PixelInsData	P,P1,P2,P3;
	int	PL,wPL,PL3;
	int	PH,wPH,PH3;
	int	SL,wSL,SL3;
	int	SH,wSH,SH3;
	int	RL,wRL,RL3;
	int	RH,wRH,RH3;
	int SearchDot;
//	bool	IsTargetBlack;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	BYTE	*ts[3];

	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#else
	for(int x=0;x<XLen;x++){
		int	tx,ty;
		int mtX,mtY;
		int tmX,tmY;
		int SearchDot;
		int wThresholdRange_B	,wThresholdRange_D;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		BYTE	*ts[3];
		PixelInsData &P	=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
			continue;
		}

		if(pAlignPage==NULL){
			mtX	=mtY=0;
			tmX	=tmY=0;
			tx	=x;
			ty	=y;
			SearchDot	=SearchDotBase;
		}
		else{
			if(DMode==_Resist){
				if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
					//?p?b?h
					continue;
				}
				else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
					//?V???N
					continue;
				}
				else if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
					//??
					continue;
				}
				else{
					SearchDot		=SearchDotBase;
				}
			}
			else if(DMode==_Pad){
				if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==false){
					//?p?b?h?E?O
					continue;
				}
				else if((P.StdDisorder & 0x80)!=0){		//bit?I?e?O?Å˜?a'1'?I?e???IPad?a??
					SearchDot		=SearchDotBase;
				}
				else{
					continue;
				}
			}
			else if(DMode==_Silk){
				if(pAlignPage->GetBitPickupFromMaster(x,y)==false){
					//?V???N?E?O
					continue;
				}
				SearchDot		=SearchDotBase+1;
			}
			else if(DMode==_Hole){
				if(pHoleAlignPage->GetBitmapFringe(x,y)==false){
					//???E?O
					continue;
				}
				SearchDot		=SearchDotBase;
			}
			else{
				continue;
			}

			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			tx	=x+mtX;
			ty	=y+mtY;
		}
		if(tx<0 || XLen<=tx){
			continue;
		}
		if(ty<0 || YLen<=ty){
			continue;
		}
		if(x-SearchDot<0 || XLen<=x+SearchDot){
			goto	MatchedForDetail1;
		}
		if(y-SearchDot<0 || YLen<=y+SearchDot){
			goto	MatchedForDetail1;
		}

		//?u?E???ÅC?I?Y
		if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
			//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
				continue;
			}
			//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
			else{
				TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
			}
		}

		wThresholdRange_B=NGThreshold_B;
		wThresholdRange_D=NGThreshold_D;
///		wThresholdRange2=wThresholdRange-((((P.RL+P.RH)>>1)-128)>>3);
		wThresholdRange2_B=(wThresholdRange_B<<7)/((P.RL+P.RH)>>1);
		wThresholdRange2_D=(wThresholdRange_D<<7)/((P.RL+P.RH)>>1);

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		if(ty==DebugPointY && tx==DebugPointX){
			DebugPoint++;
		}
		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange_D;
		RH		=P.RH+wThresholdRange_B;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange_D;
		int	RH	=P.RH+wThresholdRange_B;
#endif
		ts[0]=TargetImageList[0]->GetY(ty);
		ts[1]=TargetImageList[1]->GetY(ty);
		ts[2]=TargetImageList[2]->GetY(ty);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
		if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
			goto	MatchedForDetail1;
		}
		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail1;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail1;
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail1;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P1				=PixData[y+dy][x+dx];
#else
				PixelInsData &P1=PixData[y+dy][x+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail1;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
		P1				=PixData[y][x];
#else
		PixelInsData &P1=PixData[y][x];
		PixelInsData P3;
#endif
		P3.SL=Q->S;
		P3.PL=Q->P;
		P3.RL=Q->R;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail1;
					}
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail1;
					}
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail1;
					}
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P2=PixData[y+dy][x+dx];
#else
				PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail1;
					}
				}
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(DMode==_Resist){
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	MatchedForDetail1;
				}
			}
		}
		else if(DMode==_Silk){
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	MatchedForDetail1;
				}
			}
		}

		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromTarget1(x,y,1,SearchDotBase,0,0,0,0,0,0,0,0,BrightnessRange)==true){
				goto	MatchedForDetail1;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		PixelInsData &Pw=PixData[y][x];
		if(Pw.PL-Q->P > 0){
			DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-Pw.PH > 0){
			DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		if(Pw.SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-Pw.SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(Pw.RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-Pw.RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	MatchedForDetail1;
		}

		TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));

MatchedForDetail1:;
		InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
	}
}

//==============================================//
//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
//?u?I?I???ÅC?a???A?I???ÅC						//
//???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC			//
//==============================================//
void	PixelInspectionItem::ExecuteProcessingForDetail2(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int	x;
	int	tx,ty;
	int mtX,mtY;
	int tmX,tmY;
	PixelInsData	P;
	int	PL,PH,SL,SH,RL,RH;
	int	wPL,wPH,wSL,wSH,wRL,wRH;
	int SearchDot;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	BYTE	*ts[3];

	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#else
	for(int x=0;x<XLen;x++){
		int	tx,ty;
		int mtX,mtY;
		int tmX,tmY;
		int SearchDot;
		int wThresholdRange_B	,wThresholdRange_D;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
		PixelInsData &P	=PixData[y][x];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){
			continue;
		}
		if(pAlignPage==NULL){
			mtX	=mtY=0;
			tmX	=tmY=0;
			tx	=x;
			ty	=y;
			SearchDot	=SearchDotBase;
		}
		else{
			if(DMode==_Resist){
				if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==true){
					//?p?b?h
					continue;
				}
				else if(pAlignPage->GetBitPickupFromMaster(x,y)==true){
					//?V???N
					continue;
				}
				else if(pHoleAlignPage->GetBitmapFringe(x,y)==true){
					//??
					continue;
				}
				else{
					SearchDot		=SearchDotBase;
				}
			}
			else if(DMode==_Pad){
				if(pAlignPage->GetBitFirstPickupFromMaster(x,y)==false){
					//?p?b?h?E?O
					continue;
				}
				else if((P.StdDisorder & 0x80)!=0){		//bit?I?e?O?Å˜?a'1'?I?e???IPad?a??
					SearchDot		=SearchDotBase;
				}
				else{
					continue;
				}
			}
			else if(DMode==_Silk){
				if(pAlignPage->GetBitPickupFromMaster(x,y)==false){
					//?V???N?E?O
					continue;
				}
				SearchDot		=SearchDotBase+1;
			}
			else if(DMode==_Hole){
				if(pHoleAlignPage->GetBitmapFringe(x,y)==false){
					//???E?O
					continue;
				}
				SearchDot		=SearchDotBase;
			}
			else{
				continue;
			}

			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			tx	=x+mtX;
			ty	=y+mtY;
		}
		if(tx-SearchDot<0 || XLen<=tx+SearchDot){
			continue;
		}
		if(ty-SearchDot<0 || YLen<=ty+SearchDot){
			continue;
		}

		//?u?E???ÅC?I?Y
		if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
			//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
				continue;
			}
			//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
			else{
				TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
			}
		}
		else{
			//ExecuteProcessingForDetail1?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
			if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
				continue;
			}
		}

		wThresholdRange_B=NGThreshold_B;
		wThresholdRange_D=NGThreshold_D;
///		wThresholdRange2=wThresholdRange-((((P.RL+P.RH)>>1)-128)>>3);
		wThresholdRange2_B=(wThresholdRange_B<<7)/((P.RL+P.RH)>>1);
		wThresholdRange2_D=(wThresholdRange_D<<7)/((P.RL+P.RH)>>1);

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange_D;
		RH		=P.RH+wThresholdRange_B;
		wPL		=P.PL-wThresholdRange2_PD;
		wPH		=P.PH+wThresholdRange2_PB;
		wSL		=P.SL-wThresholdRange2_SD;
		wSH		=P.SH+wThresholdRange2_SB;
		wRL		=P.RL-wThresholdRange_D;
		wRH		=P.RH+wThresholdRange_B;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange_D;
		int	RH	=P.RH+wThresholdRange_B;
		int	wPL	=P.PL-wThresholdRange2_PD;
		int	wPH	=P.PH+wThresholdRange2_PB;
		int	wSL	=P.SL-wThresholdRange2_SD;
		int	wSH	=P.SH+wThresholdRange2_SB;
		int	wRL	=P.RL-wThresholdRange_D;
		int	wRH	=P.RH+wThresholdRange_B;
#endif
#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(ty);
		ts[1]=TargetImageList[1]->GetY(ty);
		ts[2]=TargetImageList[2]->GetY(ty);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
		if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
			goto	MatchedForDetail2;
		}
		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	MatchedForDetail2;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	MatchedForDetail2;
				}
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	MatchedForDetail2;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(PL<=Q1->P && Q1->P<=PH && SL<=Q1->S && Q1->S<=SH && RL<=Q1->R && Q1->R<=RH){
					goto	MatchedForDetail2;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail2;
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail2;
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail2;
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(ty+dy);
				ts[1]=TargetImageList[1]->GetY(ty+dy);
				ts[2]=TargetImageList[2]->GetY(ty+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail2;
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(DMode==_Resist){
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	MatchedForDetail2;
				}
			}
		}
		else if(DMode==_Silk){
			if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(x,y,tx,ty,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	MatchedForDetail2;
				}
			}
		}

		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromTarget2(x,y,1,SearchDotBase,0,0,0,0,0,0,0,0,BrightnessRange)==true){
				goto	MatchedForDetail2;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		if(PL-Q->P > 0){
			DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-PH > 0){
			DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		if(SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	MatchedForDetail2;
		}

		TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));

MatchedForDetail2:;
		InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
	}
}

//==============================================//
//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
//?u?I?I?É ?Å·?Åë?l?A?I???ÅC						//
//???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC			//
//==============================================//
void	PixelInspectionItem::ExecuteProcessingForDetail3(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode)
{
	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P,P1,P2,P3;
	int	PL,wPL,PL3;
	int	PH,wPH,PH3;
	int	SL,wSL,SL3;
	int	SH,wSH,SH3;
	int	RL,wRL,RL3;
	int	RH,wRH,RH3;
	int SearchDot;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	BYTE	*ts[3];
	int x;
	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
#else
	for(int x=0;x<XLen;x++){
		int	mx,my;
		int tmX,tmY;
		int mtX,mtY;
		int SearchDot;
		int wThresholdRange_B	,wThresholdRange_D;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
#endif
		//ExecuteProcessingForDetail1or2?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
		if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}

		if(pAlignPage==NULL){
			tmX	=tmY=0;
			mtX	=mtY=0;
			mx	=x;
			my	=y;
			SearchDot	=SearchDotBase;
		}
		else{
			if(DMode==_Resist){
				if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
					//?p?b?h
					continue;
				}
				else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
					//?V???N
					continue;
				}
				else{
					SearchDot		=SearchDotBase;
				}
			}
			else if(DMode==_Silk){
				if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
					//?V???N?E?O
					continue;
				}
				SearchDot		=SearchDotBase+1;
			}
			else{
				SearchDot		=SearchDotBase+1;
			}

			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			mx	=x+tmX;
			my	=y+tmY;
		}

		if((mx-SearchDot)<0 || XLen<=(mx+SearchDot)){
			continue;
		}
		if((my-SearchDot)<0 || YLen<=(my+SearchDot)){
			continue;
		}

#ifdef Debug
		if(my==DebugPointY && mx==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
		PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
			continue;
		}

		if(DMode==_Resist){
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
				//??
				continue;
			}
		}
		else if(DMode==_Pad){
			if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?p?b?h?E?O
				continue;
			}
			else if((P.StdDisorder & 0x80)==0){		//bit?I?e?O?Å˜?a'1'?I?e???IPad?a??
				continue;
			}
		}
		else if(DMode==_Hole){
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==false){
				//???E?O
				continue;
			}
		}

		wThresholdRange_B=NGThreshold_B;
		wThresholdRange_D=NGThreshold_D;
///		wThresholdRange2=wThresholdRange-((((P.RL+P.RH)>>1)-128)>>3);
		wThresholdRange2_B=(wThresholdRange_B<<7)/((P.RL+P.RH)>>1);
		wThresholdRange2_D=(wThresholdRange_D<<7)/((P.RL+P.RH)>>1);

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange_D;
		RH		=P.RH+wThresholdRange_B;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange_D;
		int	RH	=P.RH+wThresholdRange_B;
#endif
		if((x-SearchDot)<0 || XLen<=(x+SearchDot)){
			continue;
		}
		if((y-SearchDot)<0 || YLen<=(y+SearchDot)){
			continue;
		}

#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(y);
		ts[1]=TargetImageList[1]->GetY(y);
		ts[2]=TargetImageList[2]->GetY(y);
		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
		if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
			goto	MatchedForDetail3;
		}
		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail3;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail3;
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail3;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P1				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
				if(P1.StdDisorder==255){
					continue;
				}
				PL	=P1.PL-wThresholdRange2_PD;
				PH	=P1.PH+wThresholdRange2_PB;
				SL	=P1.SL-wThresholdRange2_SD;
				SH	=P1.SH+wThresholdRange2_SB;
				RL	=P1.RL-wThresholdRange_D;
				RH	=P1.RH+wThresholdRange_B;
/*				if(PL>PH || SL>SH || RL>RH){
					continue;
				}
*/
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail3;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
		P1				=PixData[my][mx];
#else
		PixelInsData &P1=PixData[my][mx];
		PixelInsData P3;
#endif
		P3.SL=Q->S;
		P3.PL=Q->P;
		P3.RL=Q->R;
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail3;
					}
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail3;
					}
				}
			}
			dy=Len;
			for(;dx>-Len;dx--){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail3;
					}
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
#ifdef Debug
				P2				=PixData[my+dy][mx+dx];
#else
				PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
				if(CalcPixelInsData(P1,P2,P3)==true){
#ifdef Debug
					PL3		=P3.PL-wThresholdRange2_PD;
					PH3		=P3.PH+wThresholdRange2_PB;
					SL3		=P3.SL-wThresholdRange2_SD;
					SH3		=P3.SH+wThresholdRange2_SB;
					RL3		=P3.RL-wThresholdRange_D;
					RH3		=P3.RH+wThresholdRange_B;
#else
					int	PL3	=P3.PL-wThresholdRange2_PD;
					int	PH3	=P3.PH+wThresholdRange2_PB;
					int	SL3	=P3.SL-wThresholdRange2_SD;
					int	SH3	=P3.SH+wThresholdRange2_SB;
					int	RL3	=P3.RL-wThresholdRange_D;
					int	RH3	=P3.RH+wThresholdRange_B;
#endif
/*					if(PL3>PH3 || SL3>SH3 || RL3>RH3){
						continue;
					}
*/
					if(PL3<=Q->P && Q->P<=PH3 && SL3<=Q->S && Q->S<=SH3 && RL3<=Q->R && Q->R<=RH3){
						goto	MatchedForDetail3;
					}
				}
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(DMode==_Resist){
			if(pAlignPage->GetBitPickupFromMaster(mx,my)==true && pAlignPage->GetBitFirstPickupFromMaster(mx,my)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	MatchedForDetail3;
				}
			}
		}
		else if(DMode==_Silk){
			if(pAlignPage->GetBitPickupFromMaster(mx,my)==false && pAlignPage->GetBitFirstPickupFromMaster(mx,my)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	MatchedForDetail3;
				}
			}
		}

		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromMaster1(x,y,1,SearchDotBase,0,0,0,0,0,0,0,0,BrightnessRange)==true){
				goto	MatchedForDetail3;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		PixelInsData &Pw=PixData[my][mx];
		if(Pw.PL-Q->P > 0){
			DiffPSR=sin((Pw.PL-Q->P+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-Pw.PH > 0){
			DiffPSR=sin((Q->P-Pw.PH+((Pw.PH-Pw.PL)>>1))*RadianCoef)*Q->R;
		}
		if(Pw.SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Pw.SL-Q->S+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-Pw.SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-Pw.SH+((Pw.SH-Pw.SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(Pw.RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Pw.RL-Q->R+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-Pw.RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-Pw.RH+((Pw.RH-Pw.RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	MatchedForDetail3;
		}

		TempNGBitmap[y][x>>3] |= (0x80>>(x&7));

MatchedForDetail3:;
	}
}

//==============================================//
//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
//?u?I?I???ÅC?a???A?I???ÅC						//
//???W?X?g?i?p?b?h?A?V???N?E?O?j?I???ÅC			//
//==============================================//
void	PixelInspectionItem::ExecuteProcessingForDetail4(int y,int SearchDotBase,int NGThreshold_B,int NGThreshold_D,int BrightnessRange,DetailType DMode)
{
	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int	mx,my;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P;
	int	PL,PH,SL,SH,RL,RH;
	int	wPL,wPH,wSL,wSH,wRL,wRH;
	int SearchDot;
	int wThresholdRange_B	,wThresholdRange_D;
	int wThresholdRange2_B	,wThresholdRange2_D;
	int wThresholdRange2_PB	,wThresholdRange2_PD;
	int wThresholdRange2_SB	,wThresholdRange2_SD;
	BYTE	*ts[3];
	int x;
	for(x=0;x<XLen;x++){
		if(y==DebugPointY && x==DebugPointX){
			DebugPoint++;
		}
#else
	for(int x=0;x<XLen;x++){
		int	mx,my;
		int tmX,tmY;
		int mtX,mtY;
		int SearchDot;
		int wThresholdRange_B	,wThresholdRange_D;
		int wThresholdRange2_B	,wThresholdRange2_D;
		int wThresholdRange2_PB	,wThresholdRange2_PD;
		int wThresholdRange2_SB	,wThresholdRange2_SD;
#endif
		//ExecuteProcessingForDetail1or2?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
		if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}
		//ExecuteProcessingForDetail3?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
		if((TempNGBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
			continue;
		}

		if(pAlignPage==NULL){
			tmX	=tmY=0;
			mtX	=mtY=0;
			mx	=x;
			my	=y;
			SearchDot	=SearchDotBase;
		}
		else{
			if(DMode==_Resist){
				if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true){
					//?p?b?h
					continue;
				}
				else if(pAlignPage->GetBitPickupFromTarget(x,y)==true){
					//?V???N
					continue;
				}
				else{
					SearchDot		=SearchDotBase;
				}
			}
			else if(DMode==_Silk){
				if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
					//?V???N?E?O
					continue;
				}
				SearchDot		=SearchDotBase+1;
			}
			else{
				SearchDot		=SearchDotBase;
			}

			tmX	=pAlignPage->GetShiftXFromTarget(x,y);
			tmY	=pAlignPage->GetShiftYFromTarget(x,y);
			mtX	=pAlignPage->GetShiftXFromMaster(x,y);
			mtY	=pAlignPage->GetShiftYFromMaster(x,y);
			mx	=x+tmX;
			my	=y+tmY;
		}

		if(mx<0 || XLen<=mx){
			continue;
		}
		if(my<0 || YLen<=my){
			continue;
		}

#ifdef Debug
		if(my==DebugPointY && mx==DebugPointX){
			DebugPoint++;
		}
		P				=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
		PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
		if(P.StdDisorder==255){
			continue;
		}

		if(DMode==_Resist){
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==true){
				//??
				continue;
			}
		}
		else if(DMode==_Pad){
			if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
				//?p?b?h?E?O
				continue;
			}
			else if((P.StdDisorder & 0x80)==0){		//bit?I?e?O?Å˜?a'1'?I?e???IPad?a??
				continue;
			}
		}
		else if(DMode==_Hole){
			if(pHoleAlignPage->GetBitmapFringe(mx,my)==false){
				//???E?O
				continue;
			}
		}

		wThresholdRange_B=NGThreshold_B;
		wThresholdRange_D=NGThreshold_D;
///		wThresholdRange2=wThresholdRange-((((P.RL+P.RH)>>1)-128)>>3);
		wThresholdRange2_B=(wThresholdRange_B<<7)/((P.RL+P.RH)>>1);
		wThresholdRange2_D=(wThresholdRange_D<<7)/((P.RL+P.RH)>>1);

		//?É ?Å·?Åë?l?I?????A???I??
		if(((P.PL+P.PH)>>1)<=127){
			wThresholdRange2_PB=wThresholdRange2_B;
			wThresholdRange2_PD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_PB=wThresholdRange2_D;
			wThresholdRange2_PD=wThresholdRange2_B;
		}
		if(((P.SL+P.SH)>>1)<=127){
			wThresholdRange2_SB=wThresholdRange2_B;
			wThresholdRange2_SD=wThresholdRange2_D;
		}
		else{
			wThresholdRange2_SB=wThresholdRange2_D;
			wThresholdRange2_SD=wThresholdRange2_B;
		}

#ifdef Debug
		PL		=P.PL-wThresholdRange2_PD;
		PH		=P.PH+wThresholdRange2_PB;
		SL		=P.SL-wThresholdRange2_SD;
		SH		=P.SH+wThresholdRange2_SB;
		RL		=P.RL-wThresholdRange_D;
		RH		=P.RH+wThresholdRange_B;
		wPL		=P.PL-wThresholdRange2_PD;
		wPH		=P.PH+wThresholdRange2_PB;
		wSL		=P.SL-wThresholdRange2_SD;
		wSH		=P.SH+wThresholdRange2_SB;
		wRL		=P.RL-wThresholdRange_D;
		wRH		=P.RH+wThresholdRange_B;
#else
		int	PL	=P.PL-wThresholdRange2_PD;
		int	PH	=P.PH+wThresholdRange2_PB;
		int	SL	=P.SL-wThresholdRange2_SD;
		int	SH	=P.SH+wThresholdRange2_SB;
		int	RL	=P.RL-wThresholdRange_D;
		int	RH	=P.RH+wThresholdRange_B;
		int	wPL	=P.PL-wThresholdRange2_PD;
		int	wPH	=P.PH+wThresholdRange2_PB;
		int	wSL	=P.SL-wThresholdRange2_SD;
		int	wSH	=P.SH+wThresholdRange2_SB;
		int	wRL	=P.RL-wThresholdRange_D;
		int	wRH	=P.RH+wThresholdRange_B;
#endif
		if((x-SearchDot)<0 || XLen<=(x+SearchDot)){
			continue;
		}
		if((y-SearchDot)<0 || YLen<=(y+SearchDot)){
			continue;
		}

#ifndef Debug
		BYTE	*ts[3];
#endif
		ts[0]=TargetImageList[0]->GetY(y);
		ts[1]=TargetImageList[1]->GetY(y);
		ts[2]=TargetImageList[2]->GetY(y);

		struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
		if(wPL<=Q->P && Q->P<=wPH && wSL<=Q->S && Q->S<=wSH && wRL<=Q->R && Q->R<=wRH){
			goto	MatchedForDetail4;
		}
		//?u?I?A?I?Å‚?f
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail4;
				}
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail4;
				}
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail4;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(PL<=Q->P && Q->P<=PH && SL<=Q->S && Q->S<=SH && RL<=Q->R && Q->R<=RH){
					goto	MatchedForDetail4;
				}
			}
		}

		//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
		for(int Len=1;Len<=SearchDot;Len++){
			int	dx;
			int	dy=-Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(dx=-Len;dx<Len;dx++){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail4;
			}
			dx=Len;
			for(;dy<Len;dy++){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail4;
			}
			dy=Len;
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			for(;dx>-Len;dx--){
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail4;
			}
			dx=-Len;
			for(;dy>-Len;dy--){
				ts[0]=TargetImageList[0]->GetY(y+dy);
				ts[1]=TargetImageList[1]->GetY(y+dy);
				ts[2]=TargetImageList[2]->GetY(y+dy);
				struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
				if(Q->S<=SH){
					if(Q->S<SL && Q2->S<SL){
						continue;
					}
				}
				else{
					if(Q2->S>SH){
						continue;
					}
				}
				if(Q->P<=PH){
					if(Q->P<PL && Q2->P<PL){
						continue;
					}
				}
				else{
					if(Q2->P>PH){
						continue;
					}
				}
				if(Q->R<=RH){
					if(Q->R<RL && Q2->R<RL){
						continue;
					}
				}
				else{
					if(Q2->R>RH){
						continue;
					}
				}
				goto	MatchedForDetail4;
			}
		}

		//Silk -> Silk ? or PAD -> PAD ?
		if(DMode==_Resist){
			if(pAlignPage->GetBitPickupFromMaster(mx,my)==true && pAlignPage->GetBitFirstPickupFromMaster(mx,my)==false){
				//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Silk)==true){
					goto	MatchedForDetail4;
				}
			}
		}
		else if(DMode==_Silk){
			if(pAlignPage->GetBitPickupFromMaster(mx,my)==false && pAlignPage->GetBitFirstPickupFromMaster(mx,my)==false){
				//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
				if(CalcReInspectionForResistSilk(mx,my,x,y,wThresholdRange_B,wThresholdRange_D,wThresholdRange2_B,wThresholdRange2_D,_Resist)==true){
					goto	MatchedForDetail4;
				}
			}
		}

		//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
		if(tmX!=-mtX || tmY!=-mtY){
			if(ExecuteProcessingFromMaster2(x,y,1,SearchDotBase,0,0,0,0,0,0,0,0,BrightnessRange)==true){
				goto	MatchedForDetail4;
			}
		}

		//???ÅCe??l?A?I?ÅE?d?Z?o
		BYTE DiffPSR=0;
		if(PL-Q->P > 0){
			DiffPSR=sin((PL-Q->P+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		else if(Q->P-PH > 0){
			DiffPSR=sin((Q->P-PH+((PH-PL)>>1))*RadianCoef)*Q->R;
		}
		if(SL-Q->S > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((SL-Q->S+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->S-SH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=sin((Q->S-SH+((SH-SL)>>1))*RadianCoef)*Q->R) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		if(RL-Q->R > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=RL-Q->R+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		else if(Q->R-RH > 0){
			BYTE wDiffPSR;
			if((wDiffPSR=Q->R-RH+((RH-RL)>>1)) > DiffPSR){
				DiffPSR=wDiffPSR;
			}
		}
		//?ÅÄ?-?ENG?I?Å}?Å}?A?O?e?Åë?E?c?ÅP?e
		if(DiffPSR<BrightnessRange){
			goto	MatchedForDetail4;
		}

		TempNGBitmap[y][x>>3] |= (0x80>>(x&7));

MatchedForDetail4:;
	}
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ManualExecuteProcessing1()
{
	//Enable
	if(GetThresholdR()->Enable==false){
		return;
	}

	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int		x,y;
	int		x1,x2;
	int		tx,ty;
	int		mtX,mtY;
	int		tmX,tmY;
	int		wThresholdRange2;

	int		i;
	int		LineLen,iLen;
	BYTE	Ret;
#endif

#ifndef Debug
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<AreaArrayCnt;i++){
			int LineLen=AreaArrayList[i].GetFLineLen();
			#pragma omp parallel
			{
				#pragma omp for
				for(int iLen=0;iLen<LineLen;iLen++){
					int x1	=AreaArrayList[i].GetFLineLeftX(iLen);
					int x2	=AreaArrayList[i].GetFLineRightX(iLen);
					int y	=AreaArrayList[i].GetFLineAbsY(iLen);
					for(int x=x1;x<x2;x++){
						int		mtX,mtY;
						int		tmX,tmY;
						int		tx,ty;
						BYTE	Ret=0;
#else
		for(i=0;i<AreaArrayCnt;i++){
			LineLen=AreaArrayList[i].GetFLineLen();
				for(iLen=0;iLen<LineLen;iLen++){
					x1	=AreaArrayList[i].GetFLineLeftX(iLen);
					x2	=AreaArrayList[i].GetFLineRightX(iLen);
					y	=AreaArrayList[i].GetFLineAbsY(iLen);
					for(x=x1;x<x2;x++){
						Ret=0;
#endif
						if(pAlignPage==NULL){
							mtX	=mtY=0;
							tmX	=tmY=0;
							tx	=x;
							ty	=y;
						}
						else{
							mtX	=pAlignPage->GetShiftXFromMaster(x,y);
							mtY	=pAlignPage->GetShiftYFromMaster(x,y);
							tmX	=pAlignPage->GetShiftXFromTarget(x,y);
							tmY	=pAlignPage->GetShiftYFromTarget(x,y);
							tx	=x+mtX;
							ty	=y+mtY;
						}
#ifdef Debug
						if(y==DebugPointY && x==DebugPointX){
							DebugPoint++;
						}
						if(ty==DebugPointY && tx==DebugPointX){
							DebugPoint++;
						}
#endif
						if(tx<0 || XLen<=tx || ty<0 || YLen<=ty){
							continue;
						}
						if(ManualExecuteProcessingDetail1(x,y,tx,ty,Ret)==true){
							goto	ManualMatched1;
						}

						//Silk -> Silk ? or PAD -> PAD ?
						if(pAlignPage->GetBitFirstPickupFromMaster(x,y)!=pAlignPage->GetBitPickupFromTarget(tx,ty) || pAlignPage->GetBitFirstPickupFromMaster(x,y)!=pAlignPage->GetBitFirstPickupFromTarget(tx,ty)){
							//Is Target Point Resist ?
							//DetailType ThrType=GetThresholdR()->ThrType;
							//if(ThrType==_Resist){
							if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
								//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
//								wThresholdRange2	=(GetThresholdR()->AbsoluteNGThreshold<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
								wThresholdRange2	=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#else
//								int wThresholdRange2=(GetThresholdR()->AbsoluteNGThreshold<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
								int wThresholdRange2=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#endif
//								wThresholdRange2+=abs(GetThresholdR()->AbsoluteNGThreshold-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
								wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
//								if(CalcReInspectionForResistSilk(x,y,tx,ty,GetThresholdR()->AbsoluteNGThreshold,wThresholdRange2,_Resist)==true){
								if(CalcReInspectionForResistSilk(x,y,tx,ty,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Resist)==true){
									goto	ManualMatched1;
								}
							}
							//Is Target Point Silk ?
							//else if(ThrType==_Silk){
							else if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
								//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
								wThresholdRange2	=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#else
								int wThresholdRange2=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#endif
								wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
								if(CalcReInspectionForResistSilk(x,y,tx,ty,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Silk)==true){
									goto	ManualMatched1;
								}
							}
						}

						//M?ÅNT?AT?ÅNM?I?A???C?????g?U?R?E?a?a?A???c?AT?ÅNM?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
						if(tmX!=-mtX || tmY!=-mtY){
							if(pAlignPage==NULL){
								tx	=x;
								ty	=y;
							}
							else{
								tx	=x-pAlignPage->GetShiftXFromTarget(x,y);
								ty	=y-pAlignPage->GetShiftYFromTarget(x,y);
							}
							if(tx>=0 || XLen>tx || ty>=0 || YLen>ty){
								if(ManualExecuteProcessingDetail1(x,y,tx,ty,Ret)==true){
									goto	ManualMatched1;
								}
							}
						}
						//???ÅCe??l?A?I?ÅE?d?Z?o
						PixelInsData &P=PixData[y][x];

						////?s?N?Z???a?R
						//if(IsCalcPixelInterPoration==true){
						//	if(CalcPixelInterPoration(tx,ty,P.PL,P.PH,P.SL,P.SH,P.RL,P.RH)==true){
						//		Ret=0x01;
						//		goto	ManualMatched1;
						//	}
						//}

						TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));
ManualMatched1:;
						if((Ret&0x01)!=0){
							continue;
						}
						InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
					}
				}
#ifndef Debug
			}
#endif
		}
#ifndef Debug
	}
#endif

	return;
}

bool	PixelInspectionItem::ManualExecuteProcessingDetail1(int x,int y,int tx,int ty,BYTE &Ret)
{
	//DynamicClassify?d?c?A?Å‚?f
	if(GetThresholdR()->ThrType<_DCBaseArea){
		//Master?ADynamicClassify?I?a?A?I?E?-?ATarget?ADynamicClassify?I?a?E?E?A???e??
//		if(DCAlgorithmInPagePIPointer->GetItem(tx,ty)!=NULL){	//?Å}?e?a?x?Åë?H
		int UniqueIDListCnt=((PixelInspectionInPage *)GetParentInPage())->GetUniqueIDList().count();
		for(int i=0;i<UniqueIDListCnt;i++){
			if((((PixelInspectionInPage *)GetParentInPage())->TargetDCBitmap[i][ty][tx>>3] & (0x80>>(tx&7)))!=0){
				Ret=0x01;
				return true;
			}
		}
	}
	else{
		//Master?ADynamicClassify?I?a?A???e?ATarget?ADynamicClassify?I?a?A?I?E?-?E?A???e??
		if((TargetDCBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
			Ret=0x01;
			return true;
		}
	}

	Ret=0;
	int		SearchDot=GetThresholdR()->SearchDotTarget;

#ifdef Debug
	PixelInsData	P1,P2;

	int		Len;
	int		dx,dy;
#endif

	BYTE	*ts[3];

	PixelInsData	&P=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
		Ret=0x01;
		return true;
	}

	if(x-SearchDot<0 || XLen<=x+SearchDot || y-SearchDot<0 || YLen<=y+SearchDot){
		return true;
	}

#ifdef Debug
	if(ty==DebugPointY && tx==DebugPointX){
		DebugPoint++;
	}
#endif

	//?u?E???ÅC?I?Y
	if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
		//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
		if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
			Ret=0x01;
			return true;
		}
		//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
		else{
			TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
		}
	}

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
		return true;
	}

	//?u?I?A?I?Å‚?f
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		for(dx=-Len;dx<Len;dx++){
#ifdef Debug
			P1				=PixData[y+dy][x+dx];
#else
			PixelInsData &P1=PixData[y+dy][x+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
#ifdef Debug
			P1				=PixData[y+dy][x+dx];
#else
			PixelInsData &P1=PixData[y+dy][x+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
#ifdef Debug
			P1				=PixData[y+dy][x+dx];
#else
			PixelInsData &P1=PixData[y+dy][x+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
#ifdef Debug
			P1				=PixData[y+dy][x+dx];
#else
			PixelInsData &P1=PixData[y+dy][x+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
	P1				=PixData[y][x];
#else
	PixelInsData &P1=PixData[y][x];
#endif
	PixelInsData P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		for(dx=-Len;dx<Len;dx++){
#ifdef Debug
			P2=PixData[y+dy][x+dx];
#else
			PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
#ifdef Debug
			P2=PixData[y+dy][x+dx];
#else
			PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
#ifdef Debug
			P2=PixData[y+dy][x+dx];
#else
			PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
#ifdef Debug
			P2=PixData[y+dy][x+dx];
#else
			PixelInsData	&P2=PixData[y+dy][x+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
	}
	return false;
}

//?}?X?^?[?a???c?c?^?[?Q?b?g?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ManualExecuteProcessing2()
{
	//Enable
	if(GetThresholdR()->Enable==false){
		return;
	}

	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int		x,y;
	int		x1,x2;
	int		tx,ty;
	int		mtX,mtY;
	int		tmX,tmY;
	int		wThresholdRange2;

	int		i;
	int		LineLen,iLen;
	BYTE	Ret;
#endif

#ifndef Debug
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<AreaArrayCnt;i++){
			int LineLen=AreaArrayList[i].GetFLineLen();
			#pragma omp parallel
			{
				#pragma omp for
				for(int iLen=0;iLen<LineLen;iLen++){
					int x1	=AreaArrayList[i].GetFLineLeftX(iLen);
					int x2	=AreaArrayList[i].GetFLineRightX(iLen);
					int y	=AreaArrayList[i].GetFLineAbsY(iLen);
					for(int x=x1;x<x2;x++){
						int		mtX,mtY;
						int		tmX,tmY;
						int		tx,ty;
						BYTE	Ret=0;
#else
		for(i=0;i<AreaArrayCnt;i++){
			LineLen=AreaArrayList[i].GetFLineLen();
				for(iLen=0;iLen<LineLen;iLen++){
					x1	=AreaArrayList[i].GetFLineLeftX(iLen);
					x2	=AreaArrayList[i].GetFLineRightX(iLen);
					y	=AreaArrayList[i].GetFLineAbsY(iLen);
					for(x=x1;x<x2;x++){
						Ret=0;
#endif
						if(pAlignPage==NULL){
							mtX	=mtY=0;
							tmX	=tmY=0;
							tx	=x;
							ty	=y;
						}
						else{
							mtX	=pAlignPage->GetShiftXFromMaster(x,y);
							mtY	=pAlignPage->GetShiftYFromMaster(x,y);
							tmX	=pAlignPage->GetShiftXFromTarget(x,y);
							tmY	=pAlignPage->GetShiftYFromTarget(x,y);
							tx	=x+mtX;
							ty	=y+mtY;
						}
#ifdef Debug
						if(y==DebugPointY && x==DebugPointX){
							DebugPoint++;
						}
						if(ty==DebugPointY && tx==DebugPointX){
							DebugPoint++;
						}
#endif
						if(tx<0 || XLen<=tx || ty<0 || YLen<=ty){
							continue;
						}
						if(ManualExecuteProcessingDetail2(x,y,tx,ty,Ret)==true){
							goto	ManualMatched2;
						}

						//Silk -> Silk ? or PAD -> PAD ?
						if(pAlignPage->GetBitFirstPickupFromMaster(x,y)!=pAlignPage->GetBitPickupFromTarget(tx,ty) || pAlignPage->GetBitFirstPickupFromMaster(x,y)!=pAlignPage->GetBitFirstPickupFromTarget(tx,ty)){
							//Is Target Point Resist ?
							if(pAlignPage->GetBitPickupFromTarget(tx,ty)==false && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
								//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
								wThresholdRange2	=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#else
								int wThresholdRange2=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#endif
								wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
								if(CalcReInspectionForResistSilk(x,y,tx,ty,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Resist)==true){
									goto	ManualMatched2;
								}
							}
							else if(pAlignPage->GetBitPickupFromTarget(tx,ty)==true && pAlignPage->GetBitFirstPickupFromTarget(tx,ty)==false){
								//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
								wThresholdRange2	=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#else
								int wThresholdRange2=(ThrRange<<7)/((PixData[y][x].RL+PixData[y][x].RH)>>1);
#endif
								wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
								if(CalcReInspectionForResistSilk(x,y,tx,ty,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Silk)==true){
									goto	ManualMatched2;
								}
							}
						}

						//M?ÅNT?AT?ÅNM?I?A???C?????g?U?R?E?a?a?A???c?AT?ÅNM?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
						if(tmX!=-mtX || tmY!=-mtY){
							if(pAlignPage==NULL){
								tx	=x;
								ty	=y;
							}
							else{
								tx	=x-pAlignPage->GetShiftXFromTarget(x,y);
								ty	=y-pAlignPage->GetShiftYFromTarget(x,y);
							}
							if(tx>=0 || XLen>tx || ty>=0 || YLen>ty){
								if(ManualExecuteProcessingDetail2(x,y,tx,ty,Ret)==true){
									goto	ManualMatched2;
								}
							}
						}

						//???ÅCe??l?A?I?ÅE?d?Z?o
						PixelInsData &P=PixData[y][x];

						////?s?N?Z???a?R
						//if(IsCalcPixelInterPoration==true){
						//	if(CalcPixelInterPoration(tx,ty,P.PL,P.PH,P.SL,P.SH,P.RL,P.RH)==true){
						//		goto	ManualMatched2;
						//	}
						//}

						TempNGBitmap[ty][tx>>3] |= (0x80>>(tx&7));

ManualMatched2:;
						if((Ret&0x01)!=0){
							continue;
						}
						InsCheckedBitmap[ty][tx>>3] |= (0x80>>(tx&7));
					}
				}
#ifndef Debug
			}
#endif
		}
#ifndef Debug
	}
#endif
}

bool	PixelInspectionItem::ManualExecuteProcessingDetail2(int x,int y,int tx,int ty,BYTE &Ret)
{
	//DynamicClassify?d?c?A?Å‚?f
	if(GetThresholdR()->ThrType<_DCBaseArea){
		//Master?ADynamicClassify?I?a?A?I?E?-?ATarget?ADynamicClassify?I?a?E?E?A???e??
//		if(DCAlgorithmInPagePIPointer->GetItem(tx,ty)!=NULL){	//?Å}?e?a?x?Åë?H
		int UniqueIDListCnt=((PixelInspectionInPage *)GetParentInPage())->GetUniqueIDList().count();
		for(int i=0;i<UniqueIDListCnt;i++){
			if((((PixelInspectionInPage *)GetParentInPage())->TargetDCBitmap[i][ty][tx>>3] & (0x80>>(tx&7)))!=0){
				Ret=0x01;
				return true;
			}
		}
	}
	else{
		//Master?ADynamicClassify?I?a?A???e?ATarget?ADynamicClassify?I?a?A?I?E?-?E?A???e??
		if((TargetDCBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
			Ret=0x01;
			return true;
		}
	}

	Ret=0;
	int		SearchDot=GetThresholdR()->SearchDotTarget;

#ifdef Debug
	PixelInsData	P1,P2;

	int		Len;
	int		dx,dy;
#endif

	BYTE	*ts[3];

	PixelInsData	&P=PixData[y][x];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?O?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
		Ret=0x01;
		return true;
	}

#ifdef Debug
	if(ty==DebugPointY && tx==DebugPointX){
		DebugPoint++;
	}
#endif

	//?u?E???ÅC?I?Y
	if((InsCheckedBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
		//OK?A?E?A?A?Åë?e?e???I?2?ÅP?e
		if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))==0){
			Ret=0x01;
			return true;
		}
		//NG?A?E?A?A?Åë?e?e???ING?r?b?g?d???A?É ?A?A???ÅC
		else{
			TempNGBitmap[ty][tx>>3] &= ~(0x80>>(tx&7));
		}
	}
	else{
		//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
		if((TempNGBitmap[ty][tx>>3] & (0x80>>(tx&7)))!=0){
			Ret=0x01;
			return true;
		}
	}

	ts[0]=TargetImageList[0]->GetY(ty);
	ts[1]=TargetImageList[1]->GetY(ty);
	ts[2]=TargetImageList[2]->GetY(ty);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][tx],ts[1][tx],ts[2][tx])];
	if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
		return true;
	}

	//?u?I?A?I?Å‚?f
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(ty+dy);
		ts[1]=TargetImageList[1]->GetY(ty+dy);
		ts[2]=TargetImageList[2]->GetY(ty+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(ty+dy);
			ts[1]=TargetImageList[1]->GetY(ty+dy);
			ts[2]=TargetImageList[2]->GetY(ty+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][tx+dx],ts[1][tx+dx],ts[2][tx+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
	}
	return false;
}

//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ManualExecuteProcessing3()
{
	if(GetThresholdR()->ThrType<_DCBaseArea){
		return;
	}

	//?u?I?I?É ?Å·?Åë?l?A?I???ÅC//
#ifdef Debug
	int		i;
	int		LineLen,iLen;
	int		x,y;
	int		x1,x2;
	int		mx,my;
	int		mtX,mtY;
	int		tmX,tmY;
	int		wThresholdRange2;

	BYTE	Ret;
#endif

#ifndef Debug
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<TargetAreaArrayCnt;i++){
			int LineLen	=TargetAreaArrayList[i].GetFLineLen();
			for(int iLen=0;iLen<LineLen;iLen++){
				int x1	=TargetAreaArrayList[i].GetFLineLeftX(iLen);
				int x2	=TargetAreaArrayList[i].GetFLineRightX(iLen);
				int y	=TargetAreaArrayList[i].GetFLineAbsY(iLen);
				for(int x=x1;x<x2;x++){
					int		mtX,mtY;
					int		tmX,tmY;
					int		mx,my;
					BYTE	Ret=0;
#else
		for(i=0;i<TargetAreaArrayCnt;i++){
			LineLen	=TargetAreaArrayList[i].GetFLineLen();
			for(iLen=0;iLen<LineLen;iLen++){
				x1	=TargetAreaArrayList[i].GetFLineLeftX(iLen);
				x2	=TargetAreaArrayList[i].GetFLineRightX(iLen);
				y	=TargetAreaArrayList[i].GetFLineAbsY(iLen);
				for(x=x1;x<x2;x++){
					Ret=0;
#endif
					if(pAlignPage==NULL){
						tmX	=tmY=0;
						mtX	=mtY=0;
						mx	=x;
						my	=y;
					}
					else{
						tmX	=pAlignPage->GetShiftXFromTarget(x,y);
						tmY	=pAlignPage->GetShiftYFromTarget(x,y);
						mtX	=pAlignPage->GetShiftXFromMaster(x,y);
						mtY	=pAlignPage->GetShiftYFromMaster(x,y);
						mx	=x+tmX;
						my	=y+tmY;
					}
#ifdef Debug
					if(y==DebugPointY && x==DebugPointX){
						DebugPoint++;
					}
					if(my==DebugPointY && mx==DebugPointX){
						DebugPoint++;
					}
#endif
					if(mx<0 || XLen<=mx || my<0 || YLen<=my){
						continue;
					}
					if(GetThresholdR()->ThrType==_Pad){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Silk){
						if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Resist){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true || pAlignPage->GetBitPickupFromTarget(x,y)==true){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(mx,my)!=NULL){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Hole){
						if(pHoleAlignPage->GetBitmapFringe(mx,my)==false){
							continue;
						}
					}

					//ManualExecuteProcessing2?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
					if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
						continue;
					}

					//?^?[?Q?b?g?A?W?c?c?}?X?^?[?a???d?c?A?A?I?a?O???A???c?2?ÅP?e
					if(AreaArrayList[i].IsInclude(mx,my)==false){
						continue;
					}

					if(ManualExecuteProcessingDetail3(mx,my,x,y,Ret)==true){
						goto	ManualMatched3;
					}

					//Silk -> Silk ? or PAD -> PAD ?
					if(pAlignPage->GetBitFirstPickupFromMaster(mx,my)!=pAlignPage->GetBitPickupFromTarget(x,y) || pAlignPage->GetBitFirstPickupFromMaster(mx,my)!=pAlignPage->GetBitFirstPickupFromTarget(x,y)){
						//Is Target Point Resist ?
						if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
							wThresholdRange2	=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#else
							int wThresholdRange2=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#endif
							wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
							if(CalcReInspectionForResistSilk(mx,my,x,y,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Resist)==true){
								goto	ManualMatched3;
							}
						}
						//Is Target Point Silk ?
						else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
							wThresholdRange2	=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#else
							int wThresholdRange2=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#endif
							wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
							if(CalcReInspectionForResistSilk(mx,my,x,y,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Silk)==true){
								goto	ManualMatched3;
							}
						}
					}

					//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
					if(tmX!=-mtX || tmY!=-mtY){
						if(pAlignPage==NULL){
							mx	=x;
							my	=y;
						}
						else{
							mx	=x-pAlignPage->GetShiftXFromMaster(x,y);
							my	=y-pAlignPage->GetShiftYFromMaster(x,y);
						}
						if(ManualExecuteProcessingDetail3(mx,my,x,y,Ret)==true){
							goto	ManualMatched3;
						}
					}

					////?s?N?Z???a?R
					//if(IsCalcPixelInterPoration==true){
					//	if(CalcPixelInterPoration(x,y,PL,PH,SL,SH,RL,RH)==true){
					//		goto	Matched3;
					//	}
					//}

					TempNGBitmap[y][x>>3] |= (0x80>>(x&7));
ManualMatched3:;
				}
			}
		}
#ifndef Debug
	}
#endif
}

bool	PixelInspectionItem::ManualExecuteProcessingDetail3(int mx,int my,int x,int y,BYTE &Ret)
{
	Ret=0;
	int		SearchDot=GetThresholdR()->SearchDotTarget;

#ifdef Debug
	PixelInsData	P1,P2;

	int		Len;
	int		dx,dy;
#endif

	BYTE	*ts[3];

	if(mx-SearchDot<0 || XLen<=mx+SearchDot || my-SearchDot<0 || YLen<=my+SearchDot){
		Ret=0x01;
		return true;
	}

	PixelInsData	&P=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
		Ret=0x01;
		return true;
	}

	ts[0]=TargetImageList[0]->GetY(y);
	ts[1]=TargetImageList[1]->GetY(y);
	ts[2]=TargetImageList[2]->GetY(y);
	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
	if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
		return true;
	}

	//?u?I?A?I?Å‚?f
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		for(dx=-Len;dx<Len;dx++){
#ifdef Debug
			P1				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
#ifdef Debug
			P1				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
#ifdef Debug
			P1				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
#ifdef Debug
			P1				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P1=PixData[my+dy][mx+dx];
#endif
			if(P1.StdDisorder==255){
				continue;
			}
			if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
	P1				=PixData[my][mx];
#else
	PixelInsData &P1=PixData[my][mx];
#endif
	PixelInsData P3;
	P3.SL=Q->S;
	P3.PL=Q->P;
	P3.RL=Q->R;
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		for(dx=-Len;dx<Len;dx++){
#ifdef Debug
			P2				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
#ifdef Debug
			P2				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
#ifdef Debug
			P2				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
#ifdef Debug
			P2				=PixData[my+dy][mx+dx];
#else
			PixelInsData &P2=PixData[my+dy][mx+dx];
#endif
			if(CalcPixelInsData(P1,P2,P3)==true){
				if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
					return true;
				}
			}
		}
	}
	return false;
}

//?^?[?Q?b?g?a???c?c?}?X?^?[?a???O?I?I?ÅE?A?I???ÅC//
void	PixelInspectionItem::ManualExecuteProcessing4()
{
	if(GetThresholdR()->ThrType<_DCBaseArea){
		return;
	}

	//?u?I?I???ÅC?a???A?I???ÅC//
#ifdef Debug
	int		i;
	int		LineLen,iLen;
	int		x,y;
	int		x1,x2;
	int		mx,my;
	int		mtX,mtY;
	int		tmX,tmY;
	int		wThresholdRange2;

	BYTE	Ret;
#endif

#ifndef Debug
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<TargetAreaArrayCnt;i++){
			int LineLen	=TargetAreaArrayList[i].GetFLineLen();
			for(int iLen=0;iLen<LineLen;iLen++){
				int x1	=TargetAreaArrayList[i].GetFLineLeftX(iLen);
				int x2	=TargetAreaArrayList[i].GetFLineRightX(iLen);
				int y	=TargetAreaArrayList[i].GetFLineAbsY(iLen);
				for(int x=x1;x<x2;x++){
					int		mtX,mtY;
					int		tmX,tmY;
					int		mx,my;
					BYTE	Ret=0;
#else
		for(i=0;i<TargetAreaArrayCnt;i++){
			int LineLen	=TargetAreaArrayList[i].GetFLineLen();
			for(iLen=0;iLen<LineLen;iLen++){
				x1	=TargetAreaArrayList[i].GetFLineLeftX(iLen);
				x2	=TargetAreaArrayList[i].GetFLineRightX(iLen);
				y	=TargetAreaArrayList[i].GetFLineAbsY(iLen);
				for(x=x1;x<x2;x++){
					Ret=0;
#endif
					if(pAlignPage==NULL){
						tmX	=tmY=0;
						mtX	=mtY=0;
						mx	=x;
						my	=y;
					}
					else{
						tmX	=pAlignPage->GetShiftXFromTarget(x,y);
						tmY	=pAlignPage->GetShiftYFromTarget(x,y);
						mtX	=pAlignPage->GetShiftXFromMaster(x,y);
						mtY	=pAlignPage->GetShiftYFromMaster(x,y);
						mx	=x+tmX;
						my	=y+tmY;
					}
#ifdef Debug
					if(y==DebugPointY && x==DebugPointX){
						DebugPoint++;
					}
					if(my==DebugPointY && mx==DebugPointX){
						DebugPoint++;
					}
#endif
					if(mx<0 || XLen<=mx || my<0 || YLen<=my){
						continue;
					}

					if(GetThresholdR()->ThrType==_Pad){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Silk){
						if(pAlignPage->GetBitPickupFromTarget(x,y)==false){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Resist){
						if(pAlignPage->GetBitFirstPickupFromTarget(x,y)==true || pAlignPage->GetBitPickupFromTarget(x,y)==true){
							continue;
						}
						if(pVCutPage!=NULL && pVCutPage->GetItem(mx,my)!=NULL){
							continue;
						}
					}
					else if(GetThresholdR()->ThrType==_Hole){
						if(pHoleAlignPage->GetBitmapFringe(mx,my)==false){
							continue;
						}
					}

					//ExecuteProcessing1?A?u?E???ÅC?É ?A?Åë?e?e???I?2?ÅP?e
					if((InsCheckedBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
						continue;
					}
					//ExecuteProcessing3?A?u?ENG?A?E?A?A?Åë?e?e???I?2?ÅP?e
					if((TempNGBitmap[y][x>>3] & (0x80>>(x&7)))!=0){
						continue;
					}

					//?^?[?Q?b?g?A?W?c?c?}?X?^?[?a???d?c?A?A?I?a?O???A???c?2?ÅP?e
					if(AreaArrayList[i].IsInclude(mx,my)==false){
						continue;
					}

					if(ManualExecuteProcessingDetail4(mx,my,x,y,Ret)==true){
						goto	ManualMatched4;
					}

					//Silk -> Silk ? or PAD -> PAD ?
					if(pAlignPage->GetBitFirstPickupFromMaster(mx,my)!=pAlignPage->GetBitPickupFromTarget(x,y) || pAlignPage->GetBitFirstPickupFromMaster(mx,my)!=pAlignPage->GetBitFirstPickupFromTarget(x,y)){
						//Is Target Point Resist ?
						if(pAlignPage->GetBitPickupFromTarget(x,y)==false && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							//?o?^???E?i?Å ?É ?????W?X?g?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
							wThresholdRange2	=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#else
							int wThresholdRange2=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#endif
							wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
							if(CalcReInspectionForResistSilk(mx,my,x,y,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Resist)==true){
								goto	ManualMatched4;
							}
						}
						//Is Target Point Silk ?
						else if(pAlignPage->GetBitPickupFromTarget(x,y)==true && pAlignPage->GetBitFirstPickupFromTarget(x,y)==false){
							//?o?^???E?i?Å ?É ???V???N?Ie??l?d?g?A?A?A???ÅC
#ifdef Debug
							wThresholdRange2	=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#else
							int wThresholdRange2=(ThrRange<<7)/((PixData[my][mx].RL+PixData[my][mx].RH)>>1);
#endif
							wThresholdRange2+=abs(ThrRange-wThresholdRange2)*GetThresholdR()->RelativeNGThreshold;
							if(CalcReInspectionForResistSilk(mx,my,x,y,ThrRange,ThrRange,wThresholdRange2,wThresholdRange2,_Silk)==true){
								goto	ManualMatched4;
							}
						}
					}
					//T?ÅNM?AM?ÅNT?I?A???C?????g?U?R?E?a?a?A???c?AM?ÅNT?I?E?u???i?1?A?I???ÅC?a?É ?A?Y?e
					if(tmX!=-mtX || tmY!=-mtY){
						if(pAlignPage==NULL){
							mx	=x;
							my	=y;
						}
						else{
							mx	=x-pAlignPage->GetShiftXFromMaster(x,y);
							my	=y-pAlignPage->GetShiftYFromMaster(x,y);
						}
						if(ManualExecuteProcessingDetail4(mx,my,x,y,Ret)==true){
							goto	ManualMatched4;
						}
					}

					////?s?N?Z???a?R
					//if(IsCalcPixelInterPoration==true){
					//	if(CalcPixelInterPoration(x,y,PL,PH,SL,SH,RL,RH)==true){
					//		goto	Matched4;
					//	}
					//}

					TempNGBitmap[y][x>>3] |= (0x80>>(x&7));
ManualMatched4:;
				}
			}
		}
#ifndef Debug
	}
#endif
}

bool	PixelInspectionItem::ManualExecuteProcessingDetail4(int mx,int my,int x,int y,BYTE &Ret)
{
	Ret=0;
	int		SearchDot=GetThresholdR()->SearchDotTarget;

#ifdef Debug
	PixelInsData	P1,P2;

	int		Len;
	int		dx,dy;
#endif

	PixelInsData &P	=PixData[my][mx];		//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
	if(P.StdDisorder==255){
		Ret=0x01;
		return true;
	}
	if((x-SearchDot)<0 || XLen<=(x+SearchDot)){
		Ret=0x01;
		return true;
	}
	if((y-SearchDot)<0 || YLen<=(y+SearchDot)){
		Ret=0x01;
		return true;
	}

	BYTE	*ts[3];
	ts[0]=TargetImageList[0]->GetY(y);
	ts[1]=TargetImageList[1]->GetY(y);
	ts[2]=TargetImageList[2]->GetY(y);

	struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x],ts[1][x],ts[2][x])];
	if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
		return true;
	}

	//?u?I?A?I?Å‚?f
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
				return true;
			}
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
				return true;
			}
		}
	}

	//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
#ifdef Debug
	for(Len=1;Len<=SearchDot;Len++){
		dy=-Len;
#else
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
#endif
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(dx=-Len;dx<Len;dx++){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dx=Len;
		for(;dy<Len;dy++){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dy=Len;
		ts[0]=TargetImageList[0]->GetY(y+dy);
		ts[1]=TargetImageList[1]->GetY(y+dy);
		ts[2]=TargetImageList[2]->GetY(y+dy);
		for(;dx>-Len;dx--){
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			ts[0]=TargetImageList[0]->GetY(y+dy);
			ts[1]=TargetImageList[1]->GetY(y+dy);
			ts[2]=TargetImageList[2]->GetY(y+dy);
			struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][x+dx],ts[1][x+dx],ts[2][x+dx])];
			if(Q->S<=P.SH){
				if(Q->S<P.SL && Q2->S<P.SL){
					continue;
				}
			}
			else{
				if(Q2->S>P.SH){
					continue;
				}
			}
			if(Q->P<=P.PH){
				if(Q->P<P.PL && Q2->P<P.PL){
					continue;
				}
			}
			else{
				if(Q2->P>P.PH){
					continue;
				}
			}
			if(Q->R<=P.RH){
				if(Q->R<P.RL && Q2->R<P.RL){
					continue;
				}
			}
			else{
				if(Q2->R>P.RH){
					continue;
				}
			}
			return true;
		}
	}
	return false;
}

void	PixelInspectionItem::ManualExecuteProcessing(PureFlexAreaList *NGBitArea)
{
	//NG?a?a?Å·?Åë?a?I?I?A???ÅC?É ?E?Åë
	//?Å~?Åë?a?I?I???n?A???e?e???a???Åë?I?A?A???ÅC?ÅE?e
	int AreaSize=NGBitArea->GetPatternByte();
	if(AreaSize>40){
		int MaxL=max(NGBitArea->GetMaxX()-NGBitArea->GetMinX(),NGBitArea->GetMaxY()-NGBitArea->GetMinY());
		if(MaxL<((int)(AreaSize>>2))){
			return;
		}
	}

	int LineLen	=NGBitArea->GetFLineLen();

	list<point> point_list;

#ifdef Debug
	BYTE	*ts[3];
	int	x,xx,yy;
	int XRange,YRange;
	int	mx[8][8],my[8][8];
	int mmx,mmy;
	int tmX,tmY;
	int mtX,mtY;
	PixelInsData	P,P1,P2,P3;
	int	PL,wPL,PL3;
	int	PH,wPH,PH3;
	int	SL,wSL,SL3;
	int	SH,wSH,SH3;
	int	RL,wRL,RL3;
	int	RH,wRH,RH3;
	int SearchDot	=0;		//Temporary
	int wThresholdRange;
	int wThresholdRange2;
	bool OutSearch;

	int		Index;
	int		xi,yi;
	int		xxi,yyi;
	//?T?o?Q?h?b?g?a?i25?G???A?j?I???ÅCNG?A???T?d???[?N
	BYTE	NGCheckedCnt[25];
	//?????S?~?S?ING?c?cOK?E?E?A???s?N?Z???d?U??
	BYTE	CanardBitmap[16];

	int i;
	int x1,x2,y;
	list<point>::iterator p;
	for(i=0;i<LineLen;i++){
		x1	=NGBitArea->GetFLineLeftX(i);
		x2	=NGBitArea->GetFLineRightX(i);
		y	=NGBitArea->GetFLineAbsY(i);
		for(x=x1;x<x2;x++){
#else
	for(int i=0;i<LineLen;i++){
		int x1	=NGBitArea->GetFLineLeftX(i);
		int x2	=NGBitArea->GetFLineRightX(i);
		int y	=NGBitArea->GetFLineAbsY(i);
		for(int x=x1;x<x2;x++){
			bool OutSearch;
			list<point>::iterator p;
#endif
			//?i?Ä?E?u?i?????I?S?~?S?}?X?I?Å˜?a?s?N?Z???j?c?c?A?`?F?b?N?I?Y?s?N?Z???d?o?I?ÅE
			for(p=point_list.begin();p!=point_list.end();p++){
				if(x>=p->x && x<p->x+4 && y>=p->y && y<p->y+4){
					break;
				}
			}
			if(p!=point_list.end()){
				continue;
			}
			//?i?Ä?E?u?i?????I?S?~?S?}?X?I?Å˜?a?s?N?Z???j?d?o?^
			point pp={x,y};
			point_list.push_back(pp);

			if(x-4<0 || XLen<=x+10){
				continue;
			}
			if(y-4<0 || YLen<=y+10){
				continue;
			}
			OutSearch=false;

//////////////?}?X?^?[?a???A?I???ÅC//////////////
#ifdef Debug
			if(y==DebugPointY && x==DebugPointX){
				DebugPoint++;
			}
			//???u?Å‚
			Index=0;
			memset(NGCheckedCnt,0,25);
			memset(CanardBitmap,0,16);

			//?W?~?W?}?X?I???ÅC
			XRange=x+6;
			YRange=y+6;
			yi=0;
			for(yy=y-2;yy<YRange;yy++,yi++){
#else
			int	mx[8][8],my[8][8];
			int tmX,tmY;
			int mtX,mtY;
			int SearchDot=0;		//Temporary
			int wThresholdRange;
			int wThresholdRange2;
			//???u?Å‚
			int		Index=0;
			//?T?o?Q?h?b?g?a?i25?G???A?j?I???ÅCNG?A???T?d???[?N
			BYTE	NGCheckedCnt[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			//?????S?~?S?ING?c?cOK?E?E?A???s?N?Z???d?U??
			BYTE	CanardBitmap[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

			//?W?~?W?}?X?I???ÅC
			int xx,yy;
			int XRange=x+6;
			int YRange=y+6;
			int xi,yi=0;
			for(yy=y-2;yy<YRange;yy++,yi++){
				BYTE	*ts[3];
#endif
				xi=0;
				ts[0]=TargetImageList[0]->GetY(yy);
				ts[1]=TargetImageList[1]->GetY(yy);
				ts[2]=TargetImageList[2]->GetY(yy);
				for(xx=x-2;xx<XRange;xx++,xi++){
					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
						mx[yi][xi]	=xx;
						my[yi][xi]	=yy;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
						mx[yi][xi]	=xx+tmX;
						my[yi][xi]	=yy+tmY;
					}

					if(mx[yi][xi]-2<0 || XLen<=mx[yi][xi]+2){
						OutSearch=true;
						break;
					}
					if(my[yi][xi]-2<0 || YLen<=my[yi][xi]+2){
						OutSearch=true;
						break;
					}
#ifdef Debug
					if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){		//?}?X?N?O?I?e??
						//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
						if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
							NGCheckedCnt[Index]++;
						}
						continue;
					}
					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
					if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
						continue;
					}
					NGCheckedCnt[Index]++;
				}
			}
			if(OutSearch==true){
				continue;
			}
			if(NGCheckedCnt[Index]==0){
				goto	MANUAL_ALLMATCHED1_1;
			}

			//?u?I?A?I?Å‚?f
			for(int Len=1;Len<=2;Len++){
				int	dx;
				int	dy=-Len;
				for(dx=-Len;dx<Len;dx++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED1_1;
					}
				}
				dx=Len;
				for(;dy<Len;dy++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED1_1;
					}
				}
				dy=Len;
				for(;dx>-Len;dx--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED1_1;
					}
				}
				dx=-Len;
				for(;dy>-Len;dy--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy);
						ts[1]=TargetImageList[1]->GetY(yy);
						ts[2]=TargetImageList[2]->GetY(yy);
						for(xx=x-2;xx<XRange;xx++,xi++){
							if(mx[yi][xi]+dx<0 || XLen<=mx[yi][xi]+dx){
								continue;
							}
							if(my[yi][xi]+dy<0 || YLen<=my[yi][xi]+dy){
								continue;
							}
#ifdef Debug
							P1				=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#else
							PixelInsData &P1=PixData[my[yi][xi]+dy][mx[yi][xi]+dx];
#endif
							if(P1.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED1_1;
					}
				}
			}

#ifndef Debug
			int		xxi,yyi;
#endif
			//NGCheckedCnt[25]?a?A?Å ?I?_?d?I?O
			MinNGCheckedCnt(NGCheckedCnt,xxi,yyi,Index);

			yi=2;

			//?????I?S?~?S?}?X?I?Y???ÅC
			for(yy=y;yy<YRange-2;yy++,yi++){
#ifndef Debug
				BYTE	*ts[3];
#endif
				xi=2;
				ts[0]=TargetImageList[0]->GetY(yy);
				ts[1]=TargetImageList[1]->GetY(yy);
				ts[2]=TargetImageList[2]->GetY(yy);
				for(xx=x;xx<XRange-2;xx++,xi++){
					//ExecuteProcessing1?A?u?EOK?A?E?A?A?Åë?e?e???I?2?ÅP?e
					if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))==0){
						continue;
					}

					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
					}
#ifdef Debug
					mmx		=xx+tmX+xxi;
					mmy		=yy+tmY+yyi;
#else
					int mmx	=xx+tmX+xxi;
					int mmy	=yy+tmY+yyi;
#endif
					if(mmx-SearchDot<0 || XLen<=mmx+SearchDot){
						continue;
					}
					if(mmy-SearchDot<0 || YLen<=mmy+SearchDot){
						continue;
					}
#ifdef Debug
					if(mmy==DebugPointY && mmx==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[mmy][mmx];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[mmy][mmx];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){		//?}?X?N?O?I?e???I?2?ÅP?e
						continue;
					}

					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx],ts[1][xx],ts[2][xx])];
					if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
						goto	MANUAL_MATCHED1_1;
					}

					//?u?I?A?I?Å‚?f
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						for(dx=-Len;dx<Len;dx++){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								goto	MANUAL_MATCHED1_1;
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								goto	MANUAL_MATCHED1_1;
							}
						}
						dy=Len;
						for(;dx>-Len;dx--){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								goto	MANUAL_MATCHED1_1;
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
#ifdef Debug
							P1				=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData &P1=PixData[mmy+dy][mmx+dx];
#endif
							if(P1.StdDisorder==255){
								continue;
							}
							if(P1.PL<=Q->P && Q->P<=P1.PH && P1.SL<=Q->S && Q->S<=P1.SH && P1.RL<=Q->R && Q->R<=P1.RH){
								goto	MANUAL_MATCHED1_1;
							}
						}
					}

					//?i?Ä?_?A?u?e?I?_?I?É ?Å·?Åë?l?d???Å ?É ?A???o????
#ifdef Debug
					P1				=PixData[mmy][mmx];
#else
					PixelInsData &P1=PixData[mmy][mmx];
					PixelInsData P3;
#endif
					P3.SL=Q->S;
					P3.PL=Q->P;
					P3.RL=Q->R;
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						for(dx=-Len;dx<Len;dx++){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
								if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
									goto	MANUAL_MATCHED1_1;
								}
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
								if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
									goto	MANUAL_MATCHED1_1;
								}
							}
						}
						dy=Len;
						for(;dx>-Len;dx--){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
								if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
									goto	MANUAL_MATCHED1_1;
								}
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
#ifdef Debug
							P2					=PixData[mmy+dy][mmx+dx];
#else
							PixelInsData	&P2	=PixData[mmy+dy][mmx+dx];
#endif
							if(CalcPixelInsData(P1,P2,P3)==true){
								if(P3.PL<=Q->P && Q->P<=P3.PH && P3.SL<=Q->S && Q->S<=P3.SH && P3.RL<=Q->R && Q->R<=P3.RH){
									goto	MANUAL_MATCHED1_1;
								}
							}
						}
					}

					//?3?XNG?I?O???I?e???A?Å‚?I?U?Ucontinue
					continue;
MANUAL_MATCHED1_1:;
					//OK?A?Å‚?f?3?e???s?N?Z??
//					TempNGBitmap[yy][xx>>3] &= ~(0x80>>(xx&7));
					CanardBitmap[((yi-2)<<2)+xi-2]=1;
				}
			}
			goto MANUAL_NEXT1;

MANUAL_ALLMATCHED1_1:;
			int i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
						CanardBitmap[i]=1;
					}
				}
			}

//////////////???ÅC?a???A?I???ÅC//////////////
MANUAL_NEXT1:;
#ifdef Debug
			if(y==DebugPointY && x==DebugPointX){
				DebugPoint++;
			}
#endif
			//???u?Å‚
			Index=0;

			if(NGCheckedCnt[Index]==0){
				goto	MANUAL_ALLMATCHED2_1;
			}
			memset(NGCheckedCnt+1,0,24);

			//?u?I?A?I?Å‚?f
			for(int Len=1;Len<=2;Len++){
				int	dx;
				int	dy=-Len;
				for(dx=-Len;dx<Len;dx++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED2_1;
					}
				}
				dx=Len;
				for(;dy<Len;dy++){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED2_1;
					}
				}
				dy=Len;
				for(;dx>-Len;dx--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED2_1;
					}
				}
				dx=-Len;
				for(;dy>-Len;dy--){
					Index++;
					yi=0;

					//?W?~?W?}?X?I???ÅC
					for(yy=y-2;yy<YRange;yy++,yi++){
#ifndef Debug
						BYTE	*ts[3];
#endif
						xi=0;
						ts[0]=TargetImageList[0]->GetY(yy+dy);
						ts[1]=TargetImageList[1]->GetY(yy+dy);
						ts[2]=TargetImageList[2]->GetY(yy+dy);
						for(xx=x-2;xx<XRange;xx++,xi++){
#ifdef Debug
							if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
								DebugPoint++;
							}
							P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
							PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
							if(P.StdDisorder==255){
								//ExecuteProcessing1?A?u?ENG?A?E?A?A?Åë?e?e???ING?A?É ?A?2?ÅP?e
								if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
									NGCheckedCnt[Index]++;
								}
								continue;
							}
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+dx],ts[1][xx+dx],ts[2][xx+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								continue;
							}
							NGCheckedCnt[Index]++;
						}
					}
					if(NGCheckedCnt[Index]==0){
						goto	MANUAL_ALLMATCHED2_1;
					}
				}
			}

			//NGCheckedCnt[25]?a?A?Å ?I?_?d?I?O
			MinNGCheckedCnt(NGCheckedCnt,xxi,yyi,Index);

			yi=2;

			//?????I?S?~?S?}?X?I?Y???ÅC
			for(yy=y;yy<YRange-2;yy++,yi++){
#ifndef Debug
				BYTE	*ts[3];
#endif
				if((yy+yyi-SearchDot)<0 || (yy+yyi+SearchDot)>=YLen){
					continue;
				}
				xi=2;
				ts[0]=TargetImageList[0]->GetY(yy+yyi);
				ts[1]=TargetImageList[1]->GetY(yy+yyi);
				ts[2]=TargetImageList[2]->GetY(yy+yyi);
				for(xx=x;xx<XRange-2;xx++,xi++){
					//ExecuteProcessing1?A?u?EOK?A?E?A?A?Åë?e?e???I?2?ÅP?e
					if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))==0){
						continue;
					}
					if((xx+xxi-SearchDot)<0 || (xx+xxi+SearchDot)>=XLen){
						continue;
					}

					if(pAlignPage==NULL){
						tmX	=tmY	=0;
						mtX	=mtY	=0;
					}
					else{
						tmX			=pAlignPage->GetShiftXFromTarget(xx,yy);
						tmY			=pAlignPage->GetShiftYFromTarget(xx,yy);
						mtX			=pAlignPage->GetShiftXFromMaster(xx,yy);
						mtY			=pAlignPage->GetShiftYFromMaster(xx,yy);
					}
#ifdef Debug
					if(my[yi][xi]==DebugPointY && mx[yi][xi]==DebugPointX){
						DebugPoint++;
					}
					P				=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#else
					PixelInsData &P	=PixData[my[yi][xi]][mx[yi][xi]];	//?}?X?^?[?A?I?a?r?E?I?A?a?3?a?I?A?W?d?n?ÅE
#endif
					if(P.StdDisorder==255){
						continue;
					}

					struct	PixelPoleMatrixStruct	*Q=&PoleTable[MakePoleIndex(ts[0][xx+xxi],ts[1][xx+xxi],ts[2][xx+xxi])];
					if(P.PL<=Q->P && Q->P<=P.PH && P.SL<=Q->S && Q->S<=P.SH && P.RL<=Q->R && Q->R<=P.RH){
						goto	MANUAL_MATCHED2_1;
					}

					//?u?I?A?I?Å‚?f
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(dx=-Len;dx<Len;dx++){
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								goto	MANUAL_MATCHED2_1;
							}
						}
						dx=Len;
						for(;dy<Len;dy++){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								goto	MANUAL_MATCHED2_1;
							}
						}
						dy=Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(;dx>-Len;dx--){
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								goto	MANUAL_MATCHED2_1;
							}
						}
						dx=-Len;
						for(;dy>-Len;dy--){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q1=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(P.PL<=Q1->P && Q1->P<=P.PH && P.SL<=Q1->S && Q1->S<=P.SH && P.RL<=Q1->R && Q1->R<=P.RH){
								goto	MANUAL_MATCHED2_1;
							}
						}
					}

					//?i?Ä?_?A?u?e?I?_?I???ÅC?a???d???Å ?É ?A???o????
//					for(int Len=1;Len<=SearchDot;Len++){
					for(int Len=1;Len<=0;Len++){
						int	dx;
						int	dy=-Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(dx=-Len;dx<Len;dx++){
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=P.SH){
								if(Q->S<P.SL && Q2->S<P.SL){
									continue;
								}
							}
							else{
								if(Q2->S>P.SH){
									continue;
								}
							}
							if(Q->P<=P.PH){
								if(Q->P<P.PL && Q2->P<P.PL){
									continue;
								}
							}
							else{
								if(Q2->P>P.PH){
									continue;
								}
							}
							if(Q->R<=P.RH){
								if(Q->R<P.RL && Q2->R<P.RL){
									continue;
								}
							}
							else{
								if(Q2->R>P.RH){
									continue;
								}
							}
							goto	MANUAL_MATCHED2_1;
						}
						dx=Len;
						for(;dy<Len;dy++){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=P.SH){
								if(Q->S<P.SL && Q2->S<P.SL){
									continue;
								}
							}
							else{
								if(Q2->S>P.SH){
									continue;
								}
							}
							if(Q->P<=P.PH){
								if(Q->P<P.PL && Q2->P<P.PL){
									continue;
								}
							}
							else{
								if(Q2->P>P.PH){
									continue;
								}
							}
							if(Q->R<=P.RH){
								if(Q->R<P.RL && Q2->R<P.RL){
									continue;
								}
							}
							else{
								if(Q2->R>P.RH){
									continue;
								}
							}
							goto	MANUAL_MATCHED2_1;
						}
						dy=Len;
						ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
						ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
						ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
						for(;dx>-Len;dx--){
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=P.SH){
								if(Q->S<P.SL && Q2->S<P.SL){
									continue;
								}
							}
							else{
								if(Q2->S>P.SH){
									continue;
								}
							}
							if(Q->P<=P.PH){
								if(Q->P<P.PL && Q2->P<P.PL){
									continue;
								}
							}
							else{
								if(Q2->P>P.PH){
									continue;
								}
							}
							if(Q->R<=P.RH){
								if(Q->R<P.RL && Q2->R<P.RL){
									continue;
								}
							}
							else{
								if(Q2->R>P.RH){
									continue;
								}
							}
							goto	MANUAL_MATCHED2_1;
						}
						dx=-Len;
						for(;dy>-Len;dy--){
							ts[0]=TargetImageList[0]->GetY(yy+yyi+dy);
							ts[1]=TargetImageList[1]->GetY(yy+yyi+dy);
							ts[2]=TargetImageList[2]->GetY(yy+yyi+dy);
							struct	PixelPoleMatrixStruct	*Q2=&PoleTable[MakePoleIndex(ts[0][xx+xxi+dx],ts[1][xx+xxi+dx],ts[2][xx+xxi+dx])];
							if(Q->S<=P.SH){
								if(Q->S<P.SL && Q2->S<P.SL){
									continue;
								}
							}
							else{
								if(Q2->S>P.SH){
									continue;
								}
							}
							if(Q->P<=P.PH){
								if(Q->P<P.PL && Q2->P<P.PL){
									continue;
								}
							}
							else{
								if(Q2->P>P.PH){
									continue;
								}
							}
							if(Q->R<=P.RH){
								if(Q->R<P.RL && Q2->R<P.RL){
									continue;
								}
							}
							else{
								if(Q2->R>P.RH){
									continue;
								}
							}
							goto	MANUAL_MATCHED2_1;
						}
					}

					//NG?I?O???I?e???ACanardBitmap?I?r?b?g?d?O?E?N???A
					CanardBitmap[((yi-2)<<2)+xi-2]=0;
					continue;
MANUAL_MATCHED2_1:;
					//OK?A?Å‚?f?3?e???s?N?Z???A?A?E???a?É ?E?Åë
//					if(CanardBitmap[((yi-2)<<2)+xi-2]==1){
//						CanardBitmap[((yi-2)<<2)+xi-2]=1;
//					}
				}
			}
			goto	MANUAL_NEXT2;

MANUAL_ALLMATCHED2_1:;
			i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if((TempNGBitmap[yy][xx>>3] & (0x80>>(xx&7)))!=0){
						CanardBitmap[i]=1;
					}
				}
			}
MANUAL_NEXT2:;
			i=0;
			for(yy=y;yy<YRange-2;yy++){
				for(xx=x;xx<XRange-2;xx++,i++){
					if(CanardBitmap[i]==1){
						TempNGBitmap[yy][xx>>3] &= ~(0x80>>(xx&7));
					}
				}
			}
		}
	}
}

void	PixelInspectionItem::MinNGCheckedCnt(BYTE *NGCheckedCount,int &x,int &y,int &MinIndex)
{
	MinIndex=0;
	int MinValue=NGCheckedCount[0];
	for(int i=1;i<25;i++){
		if(MinValue>NGCheckedCount[i]){
			MinIndex=i;
			MinValue=NGCheckedCount[i];
		}
	}
	int Index=0;
	if(MinIndex!=Index){
		Index++;
		for(int Len=1;Len<=2;Len++){
			int	dx;
			int	dy=-Len;
			for(dx=-Len;dx<Len;dx++,Index++){
				if(MinIndex==Index){
					x=dx;
					y=dy;
					return;
				}
			}
			dx=Len;
			for(;dy<Len;dy++,Index++){
				if(MinIndex==Index){
					x=dx;
					y=dy;
					return;
				}
			}
			dy=Len;
			for(;dx>-Len;dx--,Index++){
				if(MinIndex==Index){
					x=dx;
					y=dy;
					return;
				}
			}
			dx=-Len;
			for(;dy>-Len;dy--,Index++){
				if(MinIndex==Index){
					x=dx;
					y=dy;
					return;
				}
			}
		}
	}
	x=y=0;
}

bool	PixelInspectionItem::CalcPixelInsData(PixelInsData P,PixelInsData P2,PixelInsData &P3)
{
	//NG?I?e???A?Å~?e?????F?I???O?F?A?a?Å‚?f?ÅE?e
	//  _ _   _
	// (C-D)?EA = 0  ?c  ?
	//  _ _   _
	// (C-D)?EB = 0  ?c  ?
	//
	// ??a?e
	//   _ 2              _  _       _  _
	// -|A| ( 1 - t ) s - A?EB t s + A?EC = 0
	//
	// ??a?e
	//   _  _                _ 2      _  _
	// - A?EB ( 1 - t ) s - |B| t s + B?EC = 0
	//
	// ?a?A?A  _  _    _ 2         _ 2     _  _
	//   .   ( A?EB - |A| ) t s + |A| s  = A?EC  ?c  ?
	//          _ 2  _  _         _  _     _  _
	// ?E ?E ( |B| - A?EB ) t s + A?EB s = B?EC
	//
	// ???R?E?Å‚?e???e???e?Its?I?W???d?c?ÅP?e
	//   _  _    _ 2     _ 2  _  _          _ 2   _ 2  _  _        _  _    _ 2  _  _
	// ( A?EB - |A| ) ( |B| - A?EB ) t s + |A| ( |B| - A?EB ) s  = A?EC ( |B| - A?EB )
	//   _  _    _ 2     _ 2  _  _         _  _   _  _    _ 2      _  _   _  _    _ 2
	// ( A?EB - |A| ) ( |B| - A?EB ) t s + A?EB ( A?EB - |A| ) s = B?EC ( A?EB - |A| )
	//
	// ???R?d?o?Åë?A?Ats?I?Ä?d?A?É ?As???ÅP?I?R?E?ÅE?e
	//    _ 2   _ 2  _  _     _  _   _  _    _ 2        _  _    _ 2  _  _     _  _   _  _    _ 2
	// [ |A| ( |B| - A?EB ) - A?EB ( A?EB - |A| ) ] s = A?EC ( |B| - A?EB ) - B?EC ( A?EB - |A| )
	//    _ 2 _ 2    _  _  2      _  _    _ 2  _  _     _  _   _  _    _ 2
	// ( |A| |B| - ( A?EB ) ) s = A?EC ( |B| - A?EB ) - B?EC ( A?EB - |A| )
	//
	// ?a?A?A      _  _    _ 2  _  _     _  _   _  _    _ 2
	//   .         A?EC ( |B| - A?EB ) - B?EC ( A?EB - |A| )
	//       s = ?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\
	// ?E ?E                  _ 2 _ 2    _  _  2
	//                       |A| |B| - ( A?EB )
	//
	// ??a?et?d???s?e
	//   _  _    _ 2         _  _     _ 2
	// ( A?EB - |A| ) t s =  A?EC  - |A| s
	//
	// ?a?A?A       _  _    _ 2
	//   .          A?EC - |A| s
	//       t = ?\?\?\?\?\?\?\?\?\
	// ?E ?E        _  _    _ 2
	//            ( A?EB - |A| ) s
	//        _
	// ?_D?c?cE?E???u?d?o?e?É ???_?dF?A?ÅE?e?A?A
	// _     _
	// F = u E
	//
	// ?A?Au ?d???s?e
	//   _   _   _      _   _
	// ( A + F - D )?E( B - A ) = 0
	// _    _   _     _    _   _     _    _   _
	// A?E( B - A ) + F?E( B - A ) - D?E( B - A ) = 0
	// _    _   _       _    _   _     _    _   _
	// A?E( B - A ) + u E?E( B - A ) - D?E( B - A ) = 0
	// _    _   _           _   _      _   _     _    _   _
	// A?E( B - A ) + t u ( B - A )?E( B - A ) - D?E( B - A ) = 0
	//       _   _      _   _     _    _   _     _    _   _
	// t u ( B - A )?E( B - A ) = D?E( B - A ) - A?E( B - A )
	//
	// ?a?A?A     _    _   _     _    _   _
	//   .        D?E( B - A ) - A?E( B - A )
	//       u = ?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\
	// ?E ?E             _   _      _   _
	//               t ( B - A )?E( B - A )
	//
	// u ?a???U?e?I?A?_F?I?A?W?a?a?c?e?I?A?A?Å‚?I?_?d???S?E?A?}??A?E?}??I?E?}??A?a?c?C???c?d?Å‚?f?ÅE?e
	//
	// ?_A (?A1 , ?I1 , ?A1) ?A?ÅE?e?A?A
	//
	//         SL(A) + SH(A)              SH(A) - SL(A)
	// ?A1 = ?\?\?\?\?\?\?\?\   ??A1 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	//         PL(A) + PH(A)              PH(A) - PL(A)
	// ?I1 = ?\?\?\?\?\?\?\?\   ??I1 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	//         RL(A) + RH(A)              RH(A) - RL(A)
	// ?A1 = ?\?\?\?\?\?\?\?\   ??A1 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	// ?_B (?A2 , ?I2 , ?A2) ?A?ÅE?e?A?A
	//
	//         SL(B) + SH(B)              SH(B) - SL(B)
	// ?A2 = ?\?\?\?\?\?\?\?\   ??A2 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	//         PL(B) + PH(B)              PH(B) - PL(B)
	// ?I2 = ?\?\?\?\?\?\?\?\   ??I2 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	//         RL(B) + RH(B)              RH(B) - RL(B)
	// ?A2 = ?\?\?\?\?\?\?\?\   ??A2 = ?\?\?\?\?\?\?\?\
	//               2        ,                 2
	//
	// ?E?I?A?A?_D?c?c?i?ÅP?l?E?_C?c?c?j?I???u?A???e?_F?A?I?Å‚?e???e?I?l (??A3 , ??I3 , ??A3) ?I?A
	//
	// ??A3 = ??A1 ( 1 - t u ) + ??A2 t u
	// ??I3 = ??I1 ( 1 - t u ) + ??I2 t u
	// ??A3 = ??A1 ( 1 - t u ) + ??A2 t u
	//
	// ?a?A?A?A?_C?A?_F?A?I???Åí?d???s?A?A?a?L?}??A3,?}??I3,?}??A3?a?E???e?c?C???c?d?2?Å~?e

	//        _  _    _ 2  _  _     _  _   _  _    _ 2
	//        A?EC ( |B| - A?EB ) - B?EC ( A?EB - |A| )
	//  s = ?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\
	//                   _ 2 _ 2    _  _  2
	//                  |A| |B| - ( A?EB )
	// ?a?e?A
	//  _ 2       _ 2      _  _       _  _       _  _
	// |A| = A2, |B| = B2, A?EB = AB, A?EC = AC, B?EC = BC ?A?ÅE?e?A?A

	int	AS=(P.SL+P.SH)>>1;
	int	AP=(P.PL+P.PH)>>1;
	int	AR=(P.RL+P.RH)>>1;
	int	BS=(P2.SL+P2.SH)>>1;
	int	BP=(P2.PL+P2.PH)>>1;
	int	BR=(P2.RL+P2.RH)>>1;

	// ?_A?iP?j?A?_B?iP1?j?d???n???u?a?E?A?_C?c?c???u?d?o?e?1?e?e???A?Å‚?I?_?A?Ie??l?iP3?j?d???s?e
	// ?u?aAB?O?_C?c?c?o?e?É ?????u?A?I?d?_?d?_D?A?ÅE?e?A?A
	// D = r * AB
	// ?Å}?I r ?d???s?e?E?I?A
	// ?u?aAB?x?N?g???d?3?K?Å‚?É ?i?P?E?x?N?g???j?A?Å‚?e?A?u?aAC?x?N?g???A?I?a?I?d?a?A?A?A?u?aAB?x?N?g???I?ÅE?3?A???e?A???U?e?U?ÅE
	//
	// ?u?aAB?x?N?g?? = AB*, |AB| = absAB ?A?ÅE?e?A?A

	int ABS=BS-AS;
	int ABP=BP-AP;
	int ABR=BR-AR;
	double absAB=sqrt((double)(ABS*ABS+ABP*ABP+ABR*ABR));
	if(absAB==0){
//		goto NEXT;
		return false;
	}

	// ?u?aAB?x?N?g???I?P?E?x?N?g?? = iAB* ?A?ÅE?e?A?A

	double iABS=ABS/absAB;
	double iABP=ABP/absAB;
	double iABR=ABR/absAB;

	// ?u?aAC?x?N?g?? = AC*, ?u?aAB?x?N?g???I?P?E?x?N?g???A?u?aAC?x?N?g???I?a?I = ABAC ?A?ÅE?e?A?A

	int ACS=P3.SL-AS;
	int ACP=P3.PL-AP;
	int ACR=P3.RL-AR;
	double iABAC=iABS*ACS+iABP*ACP+iABR*ACR;

	// iABAC ?d absAB ?A???e?A r ?a???U?e

	double r=iABAC/absAB;

	if(r>0 && r<1){
		P3.SL=P.SL*(1.0-r)+P2.SL*r;
		P3.SH=P.SH*(1.0-r)+P2.SH*r;
		P3.PL=P.PL*(1.0-r)+P2.PL*r;
		P3.PH=P.PH*(1.0-r)+P2.PH*r;
		P3.RL=P.RL*(1.0-r)+P2.RL*r;
		P3.RH=P.RH*(1.0-r)+P2.RH*r;
	}
	else{
		return false;
	}
	return true;

/*
NEXT:
	int	A2=AS*AS+AP*AP+AR*AR;
	int	B2=BS*BS+BP*BP+BR*BR;
	int	AB=AS*BS+AP*BP+AR*BR;
	int	AC=AS*P3.SL+AP*P3.PL+AR*P3.RL;
	int	BC=BS*P3.SL+BP*P3.PL+BR*P3.RL;

	double Denominator1=A2*B2-AB*AB;
	if(Denominator1==0){
		return false;
	}
	double	s=(AC*(B2-AB)-BC*(AB-A2))/Denominator1;

	//         _  _    _ 2
	//         A?EC - |A| s
	//  t = ?\?\?\?\?\?\?\?\?\
	//         _  _    _ 2
	//       ( A?EB - |A| ) s
	// ?a?e?A

	double Denominator2=(AB-A2)*s;
	if(Denominator2==0){
		return false;
	}
	double	t=(AC-A2*s)/Denominator2;

	//       _    _   _     _    _   _
	//       D?E( B - A ) - A?E( B - A )
	//  u = ?\?\?\?\?\?\?\?\?\?\?\?\?\?\?\
	//              _   _      _   _
	//          t ( B - A )?E( B - A )
	// _     _   _
	// D = ( A + E ) s
	//       _     _   _
	//   = ( A + ( B - A ) t ) s
	//
	// ?a?e?A

	int	SBminusA=BS-AS;
	int	PBminusA=BP-AP;
	int	RBminusA=BR-AR;
//	double	u=((((AS+SBminusA*t)*s)*SBminusA+((AP+PBminusA*t)*s)*PBminusA+((AR+RBminusA*t)*s)*RBminusA)-(AS*SBminusA+AP*PBminusA+AR*RBminusA))/(t*(SBminusA*SBminusA+PBminusA*PBminusA+RBminusA*RBminusA));

	//   _   _   _      _   _
	// ( A + F - D )?E( B - A ) = 0
	// ?a?e?A

	//(AS+SBminusA*t*u-(AS+SBminusA*t)*s)*SBminusA+(AP+PBminusA*t*u-(AP+PBminusA*t)*s)*PBminusA+(AR+RBminusA*t*u-(AR+RBminusA*t)*s)*RBminusA=0
	//SBminusA*SBminusA*t*u+(AS-(AS+SBminusA*t)*s)*SBminusA+PBminusA*PBminusA*t*u+(AP-(AP+PBminusA*t)*s)*PBminusA+RBminusA*RBminusA*t*u+(AR-(AR+RBminusA*t)*s)*RBminusA=0
	//(SBminusA*SBminusA+PBminusA*PBminusA+RBminusA*RBminusA)*t*u+(AS-(AS+SBminusA*t)*s)*SBminusA+(AP-(AP+PBminusA*t)*s)*PBminusA+(AR-(AR+RBminusA*t)*s)*RBminusA=0
	//(SBminusA*SBminusA+PBminusA*PBminusA+RBminusA*RBminusA)*t*u=((AS+SBminusA*t)*s-AS)*SBminusA+((AP+PBminusA*t)*s-AP)*PBminusA+((AR+RBminusA*t)*s-AR)*RBminusA
	double Denominator3=(SBminusA*SBminusA+PBminusA*PBminusA+RBminusA*RBminusA)*t;
	if(Denominator3==0){
		return false;
	}
	double	u=(((AS+SBminusA*t)*s-AS)*SBminusA+((AP+PBminusA*t)*s-AP)*PBminusA+((AR+RBminusA*t)*s-AR)*RBminusA)/Denominator3;

	// ??A3 = ??A1 ( 1 - t u ) + ??A2 t u
	// ??I3 = ??I1 ( 1 - t u ) + ??I2 t u
	// ??A3 = ??A1 ( 1 - t u ) + ??A2 t u
	// ?a?e?A

//	int	dAS=(P.SH-P.SL)>>1);
//	int	dAP=(P.PH-P.PL)>>1);
//	int	dAR=(P.RH-P.RL)>>1);
//	int	dBS=(P2.SH-P2.SL)>>1);
//	int	dBP=(P2.PH-P2.PL)>>1);
//	int	dBR=(P2.RH-P2.RL)>>1);
	double	tu=t*u;
//	int	dCS=dAS*(1.0-tu)+dBS*tu;
//	int	dCP=dAP*(1.0-tu)+dBP*tu;
//	int	dCR=dAR*(1.0-tu)+dBR*tu;

	if(tu>0 && tu<1){
		P3.SL=P.SL*(1.0-tu)+P2.SL*tu;
		P3.SH=P.SH*(1.0-tu)+P2.SH*tu;
		P3.PL=P.PL*(1.0-tu)+P2.PL*tu;
		P3.PH=P.PH*(1.0-tu)+P2.PH*tu;
		P3.RL=P.RL*(1.0-tu)+P2.RL*tu;
		P3.RH=P.RH*(1.0-tu)+P2.RH*tu;
	}
	else{
		return false;
	}
	return true;
*/
}

bool	PixelInspectionItem::CalcPixelInsData(int i,BYTE *PL,BYTE *PH,BYTE *SL,BYTE *SH,BYTE *RL,BYTE *RH,PixelInsData &P3)
{
	int	AS=(SL[0]+SH[0])>>1;
	int	AP=(PL[0]+PH[0])>>1;
	int	AR=(RL[0]+RH[0])>>1;
	int	BS=(SL[i]+SH[i])>>1;
	int	BP=(PL[i]+PH[i])>>1;
	int	BR=(RL[i]+RH[i])>>1;

	// ?_A?iP?j?A?_B?iP1?j?d???n???u?a?E?A?_C?c?c???u?d?o?e?1?e?e???A?Å‚?I?_?A?Ie??l?iP3?j?d???s?e
	// ?u?aAB?O?_C?c?c?o?e?É ?????u?A?I?d?_?d?_D?A?ÅE?e?A?A
	// D = r * AB
	// ?Å}?I r ?d???s?e?E?I?A
	// ?u?aAB?x?N?g???d?3?K?Å‚?É ?i?P?E?x?N?g???j?A?Å‚?e?A?u?aAC?x?N?g???A?I?a?I?d?a?A?A?A?u?aAB?x?N?g???I?ÅE?3?A???e?A???U?e?U?ÅE
	//
	// ?u?aAB?x?N?g?? = AB*, |AB| = absAB ?A?ÅE?e?A?A

	int ABS=BS-AS;
	int ABP=BP-AP;
	int ABR=BR-AR;
	double absAB=sqrt((double)(ABS*ABS+ABP*ABP+ABR*ABR));
	if(absAB==0){
		return false;
	}

	// ?u?aAB?x?N?g???I?P?E?x?N?g?? = iAB* ?A?ÅE?e?A?A

	double iABS=ABS/absAB;
	double iABP=ABP/absAB;
	double iABR=ABR/absAB;

	// ?u?aAC?x?N?g?? = AC*, ?u?aAB?x?N?g???I?P?E?x?N?g???A?u?aAC?x?N?g???I?a?I = ABAC ?A?ÅE?e?A?A

	int ACS=P3.SL-AS;
	int ACP=P3.PL-AP;
	int ACR=P3.RL-AR;
	double iABAC=iABS*ACS+iABP*ACP+iABR*ACR;

	// iABAC ?d absAB ?A???e?A r ?a???U?e

	double r=iABAC/absAB;

	if(r>0 && r<1){
		P3.SL=SL[0]*(1.0-r)+SL[i]*r;
		P3.SH=SH[0]*(1.0-r)+SH[i]*r;
		P3.PL=PL[0]*(1.0-r)+PL[i]*r;
		P3.PH=PH[0]*(1.0-r)+PH[i]*r;
		P3.RL=RL[0]*(1.0-r)+RL[i]*r;
		P3.RH=RH[0]*(1.0-r)+RH[i]*r;
	}
	else{
		return false;
	}
	return true;
}

bool    PixelInspectionItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(::Save(f,AllocX)==false)
		return false;
	if(::Save(f,AllocY)==false)
		return false;
	for(int y=0;y<AllocY;y++){
		for(int x=0;x<AllocX;x++){
			if(f->write((const char *)&PixData[y][x],sizeof(PixData[0][0]))!=sizeof(PixData[0][0]))
				return false;
		}
	}
	if(::Save(f,CurrentMasterCounter)==false)
		return false;
	return true;
}
bool    PixelInspectionItem::Load(QIODevice *f,LayersBase *LBase)
{
	Release();
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(::Load(f,AllocX)==false)
		return false;
	if(::Load(f,AllocY)==false)
		return false;
	Alloc();
	for(int y=0;y<AllocY;y++){
		for(int x=0;x<AllocX;x++){
			if(f->read((char *)&PixData[y][x],sizeof(PixData[0][0]))!=sizeof(PixData[0][0]))
				return false;
		}
	}
	if(::Load(f,CurrentMasterCounter)==false){
		return false;
	}
	//CurrentMasterCounter?I?Z?b?g
	GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
	//PixDataForResistSilk
	AllocPixDataForResistSilk();
	//LoadedFlag
	LoadedFlag=true;

	return true;
}
void	PixelInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
/*
	if(Attr!=NULL){
		AutoAlignmentDrawAttr	*A=(AutoAlignmentDrawAttr *)Attr;
		if(A!=NULL){
			QColor	c=Attr->NormalColor.rgba();
			c.setAlpha(100);
			DrawBitImage(pnt,(const BYTE **)MasterMap ,GetDotPerLine() ,XByte ,GetMaxLines()
				,movx ,movy ,ZoomRate
				,0 ,0
				,c);
		}
	}
*/
	//?s?N?Z?????C?u?????d?a??
	int	DefaultLibID=((PixelInspectionBase *)GetParentBase())->getDefaultLibraryID();
	CmdGetPixelInspectionLibraryListPacket	packet(GetLayersBase());
	AlgorithmLibraryList *p=NULL;
	if(GetPixelInspectionLibrary(&packet)==true){
		for(p=packet.AList.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GetLibID()==DefaultLibID)
				break;
		}
	}
	if(p==NULL){
		return;
	}
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	AlgorithmLibraryLevelContainer	LLib(Container);
	//PixelInspectionLibrary PLib(GetOrigin()->GetLibType(),GetLayersBase());
	if(GetLibraryContainer()->GetLibrary(p->GetLibID(),LLib)==false){
		return;
	}

	//?s?N?Z?????C?u?????I?A?e?}?X?N?d?a??
/*
	ConstBitBuffer MaskMap;
	GetParentInPage()->GetMaskBitmap(MaskMap,&PLib);
	const BYTE	**MaskBitmap=MaskMap.GetBitMap();
*/
	BYTE	**MaskBitmap=GetMaskBitmap();

	PixelInspectionBase	*LBase=dynamic_cast<PixelInspectionBase *>(GetParentBase());
	QColor	c=LBase->getColorSelected().rgba();
	c.setAlpha(100);
	DrawBitImage(pnt,(const BYTE **)MaskBitmap ,GetDotPerLine() ,XByte ,GetMaxLines()
		,movx ,movy ,ZoomRate
		,0 ,0
		,c);
}

BYTE	**PixelInspectionItem::GetMaskBitmap(void)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Masking");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*LPI=ABase->GetPageData(GetPage());
		CmdCreateMaskingBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=((PixelInspectionBase *)GetParentBase())->GetLibType();
		CmdPacket.LibID	=((PixelInspectionBase *)GetParentBase())->getDefaultLibraryID();
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	return NULL;
}

void	PixelInspectionItem::DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	int	CircleWidth=0;
	if(GetParamGlobal()!=NULL){
		CircleWidth=GetParamGlobal()->ResultNGCircleWidth;
	}
	try{
		//???ÅC???I???I?`?a?É ?E?Åë
		if(NowInspection==true){
			return;
		}
#ifdef Debug
		int x,y;
#endif
		if(Res->GetAddedDataType()==ResultPixelOnItemType && Res->GetAddedData()!=NULL){
			PixelInspectionBase	*LBase=dynamic_cast<PixelInspectionBase *>(GetParentBase());
			ResultClusterOnItem	*r=(ResultClusterOnItem	*)Res->GetAddedData();
			if(r==NULL){
				return;
			}

			//?U?Å~?\?|
			if(IsShowOnlyDetail==true){
				int		NGSize		=((PixelInspectionBase *)GetParentBase())->getNGSize();
				QColor	NGSizeColor	=((PixelInspectionBase *)GetParentBase())->getNGSizeColor();
				QRgb	NGColor;
				for(PureFlexAreaList *a=r->List.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->GetFLinePoint()==NULL){
						return;
					}
					if(a->GetPatternByte()<NGSize){
						NGColor=LBase->getColorNG().rgba();
					}
					else{
						NGColor=NGSizeColor.rgba();
					}
#ifdef Debug
					x=a->GetFLineLeftX(0);
					y=a->GetFLineAbsY(0);
					if(y==DebugPointY && x==DebugPointX){
						DebugPoint++;
					}
					if(y==DebugPointY && x==DebugPointX){
						DebugPoint++;
					}
					a->DrawOutline(0,0 ,&IData ,NGColor
						,ZoomRate ,MovX ,MovY ,false);
#else
					a->DrawOutline(0,0 ,&IData ,NGColor
						,ZoomRate ,MovX ,MovY);
#endif
				}
			}

			//?O?U?\?|
			if(IsShowOnlyCircle==true){
				int		NGSize		=((PixelInspectionBase *)GetParentBase())->getNGSize();
				QColor	NGSizeColor	=((PixelInspectionBase *)GetParentBase())->getNGSizeColor();
				double	NGMarkSize	=((PixelInspectionBase *)GetParentBase())->getNGMarkSize();
				ResultPosList *p=Res->GetPosListFirst();
				QRgb	NGColor;
				int32	NGMarkRadius;
				if(ZoomRate<1.0){
					for(;p!=NULL;p=p->GetNext()){
						if(p->NGSize<NGSize){
							NGColor=LBase->getColorNG().rgba();
						}
						else{
							NGColor=NGSizeColor.rgba();
						}
						if(p->ImportanceLevel<100){
							NGColor=((PixelInspectionBase *)GetParentBase())->ResultImportanceColor.rgba();
						}
						p->DrawResult(Res,IData ,PData ,MovX ,MovY ,ZoomRate,GetParamGlobal()->NGMarkRadius,NGColor,CircleWidth,true);
					}
				}
				else{
					for(;p!=NULL;p=p->GetNext()){
						if(p->NGSize<NGSize){
							NGColor=LBase->getColorNG().rgba();
							NGMarkRadius=GetParamGlobal()->NGMarkRadius;
						}
						else{
							NGColor=NGSizeColor.rgba();
							NGMarkRadius=GetParamGlobal()->NGMarkRadius*NGMarkSize;
						}
						if(p->ImportanceLevel<100){
							NGColor=((PixelInspectionBase *)GetParentBase())->ResultImportanceColor.rgba();
						}
						p->DrawResult(Res,IData ,PData ,MovX ,MovY ,ZoomRate,GetParamGlobal()->NGMarkRadius*ZoomRate,NGColor,CircleWidth,true);
					}
				}
			}
		}
	}
	catch(...){
		//???c?c?I?G???[?i?A?h???X?a?????j?a?-?Å˜
		//?X???[?ÅE?e
/*		qApp->beep();
		QMessageBox MsgBox;
		MsgBox.setText	(QString::fromLocal8Bit("???c?c?I?G???[?i?A?h???X?a?????j?a?-?Å˜?I"));
		MsgBox.addButton(QString::fromLocal8Bit("OK")	,QMessageBox::AcceptRole);
		MsgBox.exec();
*/
	}
}

//-------------------------------------------------------------------------------------------------------------

PixelInspectionInPage::PixelInspectionInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	PoleTable	= new struct PixelPoleMatrixStruct[256*256*256];
	localX		=0;
	localY		=0;
	XByte		=0;

	LoadedFlag					=false;
	IsMultiAlgorithmSupport		=false;
	InitialMultiAlgorithmSupport=false;
	PixDataNarrow=PixDataBroad	=NULL;
	PixDataForResistSilk[0]		=PixDataForResistSilk[1]=NULL;

	DCAlgorithmInPagePIPointer	=NULL;
	TargetAreaArrayList			=NULL;
	TargetDCBitmap				=NULL;


	#pragma omp parallel
	{
		#pragma omp for
		for(int r=0;r<256;r++){
			for(int g=0;g<256;g++){
				for(int b=0;b<256;b++){
					struct PixelPoleMatrixStruct	*K=&PoleTable[(r<<16)+(g<<8)+b];
					double	R=sqrt((double)r*(double)r+(double)g*(double)g+(double)b*(double)b);
					K->R=R/sqrt(3.0)+0.5;
					double	R1=sqrt((double)r*(double)r+(double)b*(double)b);
//					K->S=acos((double)b/R1)*255/(M_PI/2.0)+0.5;
//					K->S=atan((double)r/b)*255/(M_PI/2.0)+0.5;
//					K->P=atan((double)g/R1)*255/(M_PI/2.0)+0.5;
					K->S=atan((double)r/b)*510/M_PI+0.5;		//510 = 255 * 2.0
					K->P=atan((double)g/R1)*510/M_PI+0.5;		//510 = 255 * 2.0
					K->SearchDot=0;
					K->NGSize=0;
				}
			}
		}
	}
}

PixelInspectionInPage::~PixelInspectionInPage(void)
{
	if(PoleTable!=NULL){
		delete	[]PoleTable;
	}
	PoleTable=NULL;

	if(TargetDCBitmap!=NULL){
		for(int i=0;i<UniqueIDList.count();i++){
			DeleteMatrixBuff(TargetDCBitmap[i],GetMaxLines());
		}
		delete TargetDCBitmap;
		TargetDCBitmap=NULL;
	}
}

bool    PixelInspectionInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false){
		return false;
	}

	WORD	Ver=1;

	if(::Save(f,Ver)==false){
		return(false);
	}
/*
	if(::Save(f,AllocX)==false)
		return false;
	if(::Save(f,AllocY)==false)
		return false;
	for(int y=0;y<AllocY;y++){
		for(int x=0;x<AllocX;x++){
			if(f->write((const char *)&PixData[y][x],sizeof(PixData[0][0]))!=sizeof(PixData[0][0]))
				return false;
		}
	}
*/
	if(::Save(f,InitialMultiAlgorithmSupport)==false){
		return false;
	}
	if(::Save(f,IsMultiAlgorithmSupport)==false){
		return false;
	}
	return true;
}

bool    PixelInspectionInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false){
		return false;
	}

	//?}?X?^?[?f?[?^?I?o?[?W?????a?ÅëLoad?I??
	int32 MasterLoadVer=((PixelInspectionBase *)GetParentBase())->MasterLoadVer;
	if(MasterLoadVer==0){
		//???u?o?[?W????
		LoadedFlag=true;
		return true;
	}

	WORD	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
/*
	if(::Load(f,AllocX)==false)
		return false;
	if(::Load(f,AllocY)==false)
		return false;
	for(int y=0;y<AllocY;y++){
		for(int x=0;x<AllocX;x++){
			if(f->read((char *)&PixData[y][x],sizeof(PixData[0][0]))!=sizeof(PixData[0][0]))
				return false;
		}
	}
*/
	if(::Load(f,InitialMultiAlgorithmSupport)==false){
		return false;
	}
	if(::Load(f,IsMultiAlgorithmSupport)==false){
		return false;
	}
	//LoadedFlag
	LoadedFlag=true;

	return true;
}

void	PixelInspectionInPage::Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)
{
	AlgorithmInPagePI::Initial(phaseParent,Base);
///	AppendItem(CreateItem(-1,0));
	XByte	=(GetDotPerLine()+7)/8;
	localX	=GetDotPerLine();
	localY	=GetMaxLines();
}

ExeResult	PixelInspectionInPage::ExecuteInitialAfterEdit(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	int CurrentMasterCounter=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);
	if(CurrentMasterCounter==99999999){
		if(InitialMultiAlgorithmSupport==false){
			if(LoadedFlag==false){
				if(LoadPixelLibrarySetting()==true){
					if(CheckSettingData()==true){
						if(ExecMultiAlgorithmSupport()==true){
							IsMultiAlgorithmSupport=true;
						}
					}
				}
				else{
					AppendItem(CreateItem(0));
				}
			}
			InitialMultiAlgorithmSupport=true;
		}
		else{
			if(IsMultiAlgorithmSupport==true){
				//?A?Y?e
				ReExecMultiAlgorithmSupport();
			}
		}
	}

	if(IsMultiAlgorithmSupport==true){
		//Item?Ee??l?d?Y?e?ÅE?e
		CreateItemThreshold();
	}
	else{
		return AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	}

	return _ER_true;
}

ExeResult	PixelInspectionInPage::ExecutePreProcessing(int ExeID ,ResultInPageRoot *Res)
{
	//?!???A???S???Y?Ä?I??
	if(IsMultiAlgorithmSupport==true){
		//???ÅC?O?E???ÅC?a???IDynamicClassify?I?a?d?a???É ?AItem?E?Z?b?g?ÅE?e
		ManualCreateTargetDCBitmap();
	}
	//Item?IExecutePreProcessing?d?A?s
	ExeResult	Ret=AlgorithmInPagePI::ExecutePreProcessing(ExeID ,Res);

	return Ret;
}

bool	PixelInspectionInPage::LoadPixelLibrarySetting()
{
	//PixelLibrarySettingString
	struct PixelLibrarySettingString PLibInStack[10];
	struct PixelLibrarySettingString *PLib=PLibInStack;

	//PixelLibrarySetting.dat?I?C?Y???Y
	int	PLibNumb=0;
///	QString FileName=/**/"./PixelLibrarySetting.dat";	//??
	//ButtonThreshold2?I?a??
	GUIFormBase	*BaseButtonThreshold2=GetLayersBase()->FindByName(/**/"Button" ,/**/"ButtonThreshold2" ,/**/"");
	if(BaseButtonThreshold2==NULL){
		return false;
	}
	ButtonThreshold2	*pButtonThreshold2=dynamic_cast<ButtonThreshold2 *>(BaseButtonThreshold2);
	QString FileName=pButtonThreshold2->GetPixelLibSettingFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	QTextStream mystream(&File);
	QString myString;
	QStringList myStringList;
	while (!mystream.atEnd()){
		myString	=mystream.readLine();
		myStringList=myString.split(',');
		PLib[PLibNumb].StringReadLine	=myString;
		PLib[PLibNumb].Priority			=myStringList.last().toInt();
		PLibNumb++;
	}
	File.close();
	QSort(PLib,PLibNumb,sizeof(PLib[0]),PLibFunc);

	for(int i=0;i<PLibNumb;i++){
		PLibSettingStringList.append(PLib[i].StringReadLine);
	}

	return true;
}

bool	PixelInspectionInPage::CheckSettingData()
{
	LoadAlgorithmData();

	int PLibNumb=PLibSettingStringList.count();
	for(int i=0;i<PLibNumb;i++){
		QString Msg;
		QStringList myStringList=PLibSettingStringList.at(i).split(',');
		if(CheckPixelLibrarySettingData(myStringList,Msg)==false){
			QMessageBox::StandardButton Btn=QMessageBox::warning(NULL
									,LangSolver.GetString(XPixelInspection_LS,LID_26)/*"Warning"*/
									,Msg,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
			if(Btn==QMessageBox::Cancel){
				return false;
			}
			else{
				continue;
			}
		}
	}
	return true;
}

void	PixelInspectionInPage::LoadAlgorithmData()
{
	//AlgorithmListName?APixelLibrary?I?a??
	AlgorithmListName.clear();
	PixelLibraryIDList.clear();
	PixelLibraryNameList.clear();
	AlgorithmListName.append(/**/"");
	PixelLibraryIDList.append(/**/"");
	PixelLibraryNameList.append(/**/"");
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==/**/"PixelInspection"){
			AlgorithmLibraryContainer	*PixelAL=L->GetInstance()->GetLibraryContainer();
			if(PixelAL!=NULL){
				PixelAL->EnumLibrary(L->GetInstance()->GetLibType(),PixelAList);
				for(AlgorithmLibraryList *p=PixelAList.GetFirst();p!=NULL;p=p->GetNext()){
					PixelLibraryIDList.append(QString::number(p->GetLibID()));
					PixelLibraryNameList.append(p->GetLibName());
				}
			}
		}
		AlgorithmListName.append(L->GetDLLName());
	}
}

bool	PixelInspectionInPage::CheckPixelLibrarySettingData(const QStringList &myStringList,QString &Msg)
{
	int Cnt;
	if((Cnt=myStringList.count())<8){
		return false;
	}

	int iCnt=0;
	int i;
	for(i=0;i<PixelLibraryIDList.count();i++){
		if(myStringList.at(iCnt)==PixelLibraryIDList.at(i)){
			break;
		}
	}
	iCnt++;
	if(i==PixelLibraryIDList.count()){
		Msg+=LangSolver.GetString(XPixelInspection_LS,LID_27)/*"Not found PixelLibrary ID.\n"*/;
	}
	else{
		if(myStringList.at(iCnt)!=PixelLibraryNameList.at(i)){
			Msg+=LangSolver.GetString(XPixelInspection_LS,LID_28)/*"Not found PixelLibrary Name.\n"*/;
		}
	}
	iCnt++;
	for(i=0;i<AlgorithmListName.count();i++){
		if(myStringList.at(iCnt)==AlgorithmListName.at(i)){
			break;
		}
	}
	iCnt++;
	if(i==AlgorithmListName.count()){
		Msg+=LangSolver.GetString(XPixelInspection_LS,LID_29)/*"Not found Algorithm Name.\n"*/;
	}
	else{
		//Library?I?a??
		CreateLibraryNameList(AlgorithmListName.at(i));
		for(i=0;i<LibraryIDList.count();i++){
			if(myStringList.at(iCnt)==LibraryIDList.at(i)){
				break;
			}
		}
		iCnt++;
		if(i==LibraryIDList.count()){
			Msg+=LangSolver.GetString(XPixelInspection_LS,LID_30)/*"Not found Library ID.\n"*/;
		}
		else{
			if(myStringList.at(iCnt)!=LibraryNameList.at(i)){
				Msg+=LangSolver.GetString(XPixelInspection_LS,LID_31)/*"Not found Library Name.\n"*/;
			}
		}
		iCnt++;
		//UniqueID
		iCnt++;
		//Unique
		iCnt++;
	}
	bool IsOK;
	myStringList.at(iCnt).toInt(&IsOK);
	if(IsOK==false){
		Msg+=LangSolver.GetString(XPixelInspection_LS,LID_32)/*"Not correct Priority.\n"*/;
	}

	return Msg.isEmpty();
}

bool	PixelInspectionInPage::CreateLibraryNameList(const QString AlgorithmName)
{
	LibraryIDList.clear();
	LibraryNameList.clear();
	LibraryIDList.append(/**/"");
	LibraryNameList.append(/**/"");
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==AlgorithmName){
			AlgorithmLibraryContainer  *AL=L->GetInstance()->GetLibraryContainer();
			if(AL!=NULL){
				AlgorithmLibraryListContainer	AList;
				AL->EnumLibrary(L->GetInstance()->GetLibType(),AList);
				for(AlgorithmLibraryList *p=AList.GetFirst();p!=NULL;p=p->GetNext()){
					LibraryIDList.append(QString::number(p->GetLibID()));
					LibraryNameList.append(p->GetLibName());
				}
				if(L->GetDLLName()==/**/"AutoAlignment"){
					AAlignAList=AList;
				}
				return true;
			}
		}
	}
	return false;
}

//?Å‚?e???e?I?I?a?Ae??l?d?i?Å ?ÅE?e
bool	PixelInspectionInPage::ExecMultiAlgorithmSupport()
{
	int PLibNumb=PLibSettingStringList.count();
	for(int i=0;i<PLibNumb;i++){
		QString Msg;
		QStringList myStringList=PLibSettingStringList.at(i).split(',');
		if(CalcMultiAlgorithmSupport(myStringList.at(0).toInt(),myStringList.at(2),myStringList.at(3).toInt(),myStringList.at(5).toInt(),Msg)==false){
			QMessageBox::StandardButton Btn=QMessageBox::warning(NULL
												,LangSolver.GetString(XPixelInspection_LS,LID_33)/*"Warning"*/
												,Msg,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
			if(Btn==QMessageBox::Cancel){
				break;
			}
		}
	}
	return true;
}

//e??l?d?A?i?Å ?ÅE?e
bool	PixelInspectionInPage::ReExecMultiAlgorithmSupport()
{
	int ItemCount=GetItemCount();
	for(int i=0;i<ItemCount;i++){
		//?s?N?Z?????C?u?????d?a??
		//PixelInspectionLibrary PLib(GetParentBase()->GetLibType(),GetLayersBase());
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(GetLibraryContainer()->GetLibrary(GetItemData(0,i)->GetLibID(),LLib)==false){
			//?s?N?Z?????C?u?????a?E?c?A???c?H?H?H
			continue;
		}
		PixelInspectionLibrary	*ALib=dynamic_cast<PixelInspectionLibrary *>(LLib.GetLibrary());
		//Narrow//Broad
		((PixelInspectionItem *)GetItemData(0,i))->GetThresholdW()->FromLibrary(ALib);
	}
	return true;
}

//?Å‚?e???e?I?I?a?Ae??l?d?i?Å ?ÅE?e
bool	PixelInspectionInPage::CalcMultiAlgorithmSupport(int PixelLibID,const QString AlgorithmName,int LibID,int UniqueID,QString &Msg)
{
#ifdef Debug
	AlgorithmItemPI	*AlgorithmItemPIPointer;
	AlgorithmLibraryList *p;
#endif

	//?A???S???Y?Ä?i?I?a?j?I?w?e?a?E?Åë?e???A?U???I?I?e?A?Åë?E?Åë?I?a?d?Z?b?g
	if(AlgorithmName.isEmpty()==true){
		//?s?N?Z?????C?u?????d?a??
		//PixelInspectionLibrary PLib(GetParentBase()->GetLibType(),GetLayersBase());
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(GetLibraryContainer()->GetLibrary(PixelLibID,LLib)==false){
			Msg=LangSolver.GetString(XPixelInspection_LS,LID_34)/*"Not load pixel library. ( library ID = "*/ + QString::number(PixelLibID) + /**/" )";
			return false;
		}
		PixelInspectionLibrary	*ALib=dynamic_cast<PixelInspectionLibrary *>(LLib.GetLibrary());
		//Pixel?IItem?IAlgorithmItemPIPointerList?c?c?AResist?I?G???A?d???o
		BYTE **ResistArea=GetResistArea();
		PureFlexAreaListContainer ResistAreaFPack;
		PickupFlexArea((BYTE **)ResistArea,XByte,localX,localY,ResistAreaFPack);
		//?z?n?E?u?e?e
		int Cnt=0;
		FlexArea *AreaArrayList=new FlexArea[ResistAreaFPack.GetNumber()];
		for(PureFlexAreaList *p=ResistAreaFPack.GetFirst();p!=NULL;p=p->GetNext()){
			AreaArrayList[Cnt++]=*p;
		}

		ALib->ThrType=_Resist;
		PixelInspectionItem	*PItem;
		//Narrow
		PItem=dynamic_cast<PixelInspectionItem *>(CreateItem(0));
		PItem->GetThresholdW()->SetDetailType(ALib->ThrType);
		PItem->GetThresholdW()->SetThresholdMode(_Narrow);
		PItem->GetThresholdW()->FromLibrary(ALib);
		PItem->SetLibID			(ALib->GetLibID());
		PItem->SetAreaArrayList	(AreaArrayList);
		PItem->SetAreaArrayCnt	(Cnt);
		AppendItem				(PItem);
		//Broad
		PItem=dynamic_cast<PixelInspectionItem *>(CreateItem(0));
		PItem->GetThresholdW()->SetDetailType(ALib->ThrType);
		PItem->GetThresholdW()->SetThresholdMode(_Broad);
		PItem->GetThresholdW()->FromLibrary(ALib);
		PItem->SetLibID			(ALib->GetLibID());
		PItem->SetAreaArrayList	(AreaArrayList);
		PItem->SetAreaArrayCnt	(Cnt);
		AppendItem				(PItem);
		return true;
	}

	FlexArea DebugFlexArea;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==AlgorithmName){
			//???C?u?????i?n?d?a??
			AlgorithmBase	*AlgorithmBasePointer=GetLayersBase()->GetAlgorithmBase(L->GetDLLRoot(),L->GetDLLName());
			if(AlgorithmBasePointer==NULL){
				//AlgorithmBase?E?É 
				return false;
			}
			AlgorithmInPageRoot	*AlgorithmInPageRootPointer=AlgorithmBasePointer->GetPageData(GetPage());
			if(AlgorithmInPageRootPointer==NULL){
				//AlgorithmInPageRoot?E?É 
				return false;
			}
			AlgorithmInPagePI	*AlgorithmInPagePIPointer=dynamic_cast<AlgorithmInPagePI *>(AlgorithmInPageRootPointer);
			if(AlgorithmInPagePIPointer==NULL){
				//AlgorithmInPagePI?E?É 
				return false;
			}

			DetailType DType;
			struct AutoAlignmentLibraryStruct AALibInStack[10];
			struct AutoAlignmentLibraryStruct *AALib=AALibInStack;
			if(AlgorithmName==/**/"AutoAlignment"){
				int	AALibNumb=0;
				for(int i=0;i<AlgorithmInPagePIPointer->GetItemCount();i++){
					//?I?[?g?A???C?????g???C?u?????d?a??
					AlgorithmLibraryLevelContainer *AutoAlignmentLib=new AlgorithmLibraryLevelContainer(AlgorithmBasePointer->GetLibraryContainer());
					if(AutoAlignmentLib!=NULL){
#ifdef Debug
						AlgorithmItemPIPointer					=(AlgorithmItemPI *)AlgorithmInPagePIPointer->GetItemData(0,i);
#else
						AlgorithmItemPI	*AlgorithmItemPIPointer	=(AlgorithmItemPI *)AlgorithmInPagePIPointer->GetItemData(0,i);
#endif
						if(AlgorithmItemPIPointer!=NULL){
							AlgorithmLibraryContainer	*Container=GetLibraryContainer();
							if(AlgorithmBasePointer->GetLibraryContainer()->GetLibrary(AlgorithmItemPIPointer->GetLibID(),*AutoAlignmentLib)){
								AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(AutoAlignmentLib->GetLibrary());
								AALib[AALibNumb].AutoAlignmentLibraryPointer=ALib;
								AALib[AALibNumb].Priority					=ALib->Priority;
								AALibNumb++;
							}
						}
					}
				}
				QSort(AALib,AALibNumb,sizeof(AALib[0]),AALibFunc);
				if(AALib[0].AutoAlignmentLibraryPointer->GetLibID()==LibID){
					DType=_Pad;
				}
				else{
					DType=_Silk;
				}
			}

			int ItemCount=AlgorithmInPagePIPointer->GetItemCount();
			AlgorithmItemPI **AlgorithmItemPIList=new AlgorithmItemPI*[ItemCount];
			//???u?Å‚
			#pragma omp parallel
			{
				#pragma omp for
				for(int Cnt=0;Cnt<ItemCount;Cnt++){
					AlgorithmItemPIList[Cnt]=NULL;
				}
			}

			for(int i=0;i<ItemCount;i++){
#ifdef Debug
				AlgorithmItemPIPointer					=(AlgorithmItemPI *)AlgorithmInPagePIPointer->GetItemData(0,i);
#else
				AlgorithmItemPI	*AlgorithmItemPIPointer	=(AlgorithmItemPI *)AlgorithmInPagePIPointer->GetItemData(0,i);
#endif
				if(AlgorithmItemPIPointer!=NULL){
					if(AlgorithmName==/**/"VCutInspection" || AlgorithmItemPIPointer->GetLibID()==LibID){
///						FlexArea SumFlexArea(AlgorithmItemPIPointer->GetArea(UniqueID));
						AlgorithmItemPIList[i]=AlgorithmItemPIPointer;
						int SumCnt=1;
						if(i+1<ItemCount){
#ifndef Debug
							#pragma omp parallel
							{
								#pragma omp for reduction(+:SumCnt)
#endif
								for(int j=i+1;j<ItemCount;j++){
									AlgorithmItemPIPointer=(AlgorithmItemPI *)AlgorithmInPagePIPointer->GetItemData(0,j);
									if(AlgorithmItemPIPointer!=NULL){
										if(AlgorithmName==/**/"VCutInspection" || AlgorithmItemPIPointer->GetLibID()==LibID){
///											SumFlexArea+=AlgorithmItemPIPointer->GetArea(UniqueID);
											AlgorithmItemPIList[j]=AlgorithmItemPIPointer;
											SumCnt++;
										}
									}
								}
#ifndef Debug
							}
#endif
						}
						//?z?n?E?u?e?e
						FlexArea *AreaArrayList=new FlexArea[SumCnt];
						if(SumCnt==ItemCount){
							#pragma omp parallel
							{
								#pragma omp for
								for(int Cnt=0;Cnt<SumCnt;Cnt++){
									AreaArrayList[Cnt]=AlgorithmItemPIList[Cnt]->GetArea(UniqueID);
								}
							}
						}
						else{
							for(int Cnt=0,iCnt=0;iCnt<SumCnt;Cnt++){
								if(AlgorithmItemPIList[Cnt]!=NULL){
									DebugFlexArea=AlgorithmItemPIList[Cnt]->GetArea(UniqueID);
									AreaArrayList[iCnt++]=AlgorithmItemPIList[Cnt]->GetArea(UniqueID);
								}
							}
						}

						//?s?N?Z?????C?u?????d?a??
						AlgorithmLibraryContainer	*Container=GetLibraryContainer();
						AlgorithmLibraryLevelContainer	LLib(Container);
						//PixelInspectionLibrary PLib(GetParentBase()->GetLibType(),GetLayersBase());
						if(GetLibraryContainer()->GetLibrary(PixelLibID,LLib)==false){
							//?s?N?Z?????C?u?????a?E?c?A???c?H?H?H
///							(*ResistFlexArea)-=SumFlexArea;
							delete []AlgorithmItemPIList;
							delete []AreaArrayList;	
							return true;
						}
						PixelInspectionLibrary	*ALib=dynamic_cast<PixelInspectionLibrary *>(LLib.GetLibrary());

						if(AlgorithmName==/**/"AutoAlignment"){
							ALib->ThrType=DType;
						}
						else if(AlgorithmName==/**/"AutoPCBHoleAligner"){
							ALib->ThrType=_Hole;
						}
						else if(AlgorithmName==/**/"DynamicClassify"){
							ALib->ThrType=(DetailType)(UniqueID+3);
						}

						PixelInspectionItem	*PItem;
						//Narrow
						PItem=dynamic_cast<PixelInspectionItem *>(CreateItem(0));
						PItem->GetThresholdW()->SetDetailType(ALib->ThrType);
						PItem->GetThresholdW()->SetThresholdMode(_Narrow);
						PItem->GetThresholdW()->FromLibrary(ALib);
						PItem->SetLibID			(ALib->GetLibID());
						PItem->SetAreaArrayList	(AreaArrayList);
						PItem->SetAreaArrayCnt	(SumCnt);
						PItem->SetUniqueID		(UniqueID);
						AppendItem				(PItem);
						//Broad
						PItem=dynamic_cast<PixelInspectionItem *>(CreateItem(0));
						PItem->GetThresholdW()->SetDetailType(ALib->ThrType);
						PItem->GetThresholdW()->SetThresholdMode(_Broad);
						PItem->GetThresholdW()->FromLibrary(ALib);
						PItem->SetLibID			(ALib->GetLibID());
						PItem->SetAreaArrayList	(AreaArrayList);
						PItem->SetAreaArrayCnt	(SumCnt);
						PItem->SetUniqueID		(UniqueID);
						AppendItem				(PItem);
						if(AlgorithmName==/**/"DynamicClassify"){
							SetAlgorithmInPagePIPointer(AlgorithmInPagePIPointer);
							if(UniqueIDList.contains(UniqueID)==false){
								UniqueIDList.append(UniqueID);
							}
						}
						delete []AlgorithmItemPIList;
						return true;
					}
				}
			}
			delete []AlgorithmItemPIList;
			return true;
		}
	}

/*
	AlgorithmInLayerRoot *AlgorithmInLayerRootPointer=AlgorithmInPageRootPointer->GetLayerData(0);
	if(AlgorithmInLayerRootPointer==NULL){
		//?A???S???Y?Ä?E?É 
		return false;
	}
	AlgorithmInLayerRootPointer-

	AlgorithmItemRoot *AlgorithmItemRootPointer=Pg->GetItemData(0,LibID);
	if(AlgorithmItemRootPointer==NULL){
		//?A???S???Y?Ä?E?É 
		return false;
	}
	FlexArea AlgorithmItemArea=AlgorithmItemRootPointer->GetArea();
*/
	return false;
}

BYTE	**PixelInspectionInPage::GetResistArea()
{
	//ResistAreaBitmap
	BYTE **ResistAreaBitmap=GetAutoMaskBitmap();

	int ItemCount=GetItemCount();
	for(int i=0;i<ItemCount;i++){
		FlexArea *AreaArrayList=((PixelInspectionItem *)GetItemData(0,i))->GetAreaArrayList();
		int		 AreaArrayCnt=((PixelInspectionItem *)GetItemData(0,i))->GetAreaArrayCnt();
#ifndef Debug
		#pragma omp parallel
		{
			#pragma omp for
#endif
			for(int Cnt=0;Cnt<AreaArrayCnt;Cnt++){
				int LineLen	=AreaArrayList[Cnt].GetFLineLen();
				for(int Len=0;Len<LineLen;Len++){
					int x1	=AreaArrayList[Cnt].GetFLineLeftX(Len);
					int x2	=AreaArrayList[Cnt].GetFLineRightX(Len);
					int y	=AreaArrayList[Cnt].GetFLineAbsY(Len);
					for(int x=x1;x<x2;x++){
						ResistAreaBitmap[y][x>>3] &= ~(0x80>>(x&7));
					}
				}
			}
#ifndef Debug
		}
#endif
	}
	return ResistAreaBitmap;
}

void	PixelInspectionInPage::DeletePixelItem()
{
	int ItemCount=GetItemCount();
	for(int i=ItemCount-1;i>=0;i--){
		AlgorithmItemPI *AlgorithmItemPIPointer=(AlgorithmItemPI *)GetItemData(0,i);
		RemoveItem(AlgorithmItemPIPointer);
	}
}

void	PixelInspectionInPage::CreateItemThreshold()
{
	//?D?a?x???EItem?Ee??l?d?Y?e?ÅE?e
	int ItemCount=GetItemCount();

	GetLayersBase()->AddMaxProcessing(GetPage(),ItemCount<<1);

	Alloc();
	for(int i=0;i<ItemCount;i++){
		GetLayersBase()->StepProcessing(GetPage());
		((PixelInspectionItem *)GetItemData(0,i))->ManualExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
	}
	AllocPixDataForResistSilk();
	for(int i=0;i<ItemCount;i++){
		GetLayersBase()->StepProcessing(GetPage());
		((PixelInspectionItem *)GetItemData(0,i))->ManualPixDataForResistSilk();
	}
}

BYTE	**PixelInspectionInPage::GetAutoMaskBitmap(void)
{
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(LBase!=NULL){
		AlgorithmInPageRoot	*LPI=LBase->GetPageData(GetPage());
		CmdCreateAutoMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*LPI=ABase->GetPageData(GetPage());
		CmdCreateMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	return NULL;
}

void	PixelInspectionInPage::Alloc(void)
{
	AllocX=GetDotPerLine();
	AllocY=GetMaxLines();

	Release();

	PixDataNarrow	=new PixelInsData*[AllocY];
	PixDataBroad	=new PixelInsData*[AllocY];
	for(int y=0;y<AllocY;y++){
		PixDataNarrow[y]=new PixelInsData[AllocX];
		PixDataBroad [y]=new PixelInsData[AllocX];
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<AllocY;y++){
			for(int x=0;x<AllocX;x++){
				PixDataNarrow[y][x].PH=0;
				PixDataNarrow[y][x].PL=255;
				PixDataNarrow[y][x].SH=0;
				PixDataNarrow[y][x].SL=255;
				PixDataNarrow[y][x].RH=0;
				PixDataNarrow[y][x].RL=255;
				PixDataNarrow[y][x].StdDisorder=255;
				PixDataBroad [y][x].PH=0;
				PixDataBroad [y][x].PL=255;
				PixDataBroad [y][x].SH=0;
				PixDataBroad [y][x].SL=255;
				PixDataBroad [y][x].RH=0;
				PixDataBroad [y][x].RL=255;
				PixDataBroad [y][x].StdDisorder=255;
			}
		}
	}
}

void	PixelInspectionInPage::Release(void)
{
	if(PixDataNarrow!=NULL){
		for(int y=0;y<AllocY;y++){
			delete	[]PixDataNarrow[y];
		}
		delete	[]PixDataNarrow;
	}
	PixDataNarrow=NULL;

	if(PixDataBroad!=NULL){
		for(int y=0;y<AllocY;y++){
			delete	[]PixDataBroad[y];
		}
		delete	[]PixDataBroad;
	}
	PixDataBroad=NULL;
}

void	PixelInspectionInPage::AllocPixDataForResistSilk(void)
{
	int	XNumb=GetDotPerLine();
	int	YNumb=GetMaxLines();

	//???W?X?g?Ie??l?I?i?[???[?N?i?Å 
	if(PixDataForResistSilk[0]==NULL){
		for(int Cnt=0;Cnt<2;Cnt++){
			PixDataForResistSilk[Cnt]=new PixelInsData*[(YNumb>>8)+1];
			for(int i=0;i<=(YNumb>>8);i++){
				PixDataForResistSilk[Cnt][i]=new PixelInsData[(XNumb>>8)+1];
			}
		}
	}
	//???W?X?g?Ie??l?I?i?[???[?N???u?Å‚
	for(int Cnt=0;Cnt<2;Cnt++){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<=(YNumb>>8);i++){
				for(int j=0;j<=(XNumb>>8);j++){
					PixDataForResistSilk[Cnt][i][j].PL=0;
					PixDataForResistSilk[Cnt][i][j].PH=255;
					PixDataForResistSilk[Cnt][i][j].SL=0;
					PixDataForResistSilk[Cnt][i][j].SH=255;
					PixDataForResistSilk[Cnt][i][j].RL=0;
					PixDataForResistSilk[Cnt][i][j].RH=255;
					PixDataForResistSilk[Cnt][i][j].StdDisorder=0;
				}
			}
		}
	}
}

void	PixelInspectionInPage::ManualCreateTargetDCBitmap()
{
	if(TargetDCBitmap==NULL){
		TargetDCBitmap=new BYTE**[UniqueIDList.count()];
		for(int i=0;i<UniqueIDList.count();i++){
			TargetDCBitmap[i]=MakeMatrixBuff(XByte,AllocY);
		}
	}
	for(int i=0;i<UniqueIDList.count();i++){
		MatrixBuffClear(TargetDCBitmap[i],0,XByte,AllocY);
	}

	if(DCAlgorithmInPagePIPointer==NULL){
		return;
	}

	if(TargetAreaArrayList!=NULL){
		for(int i=0;i<UniqueIDList.count();i++){
			delete []TargetAreaArrayList[i];
		}
	}
	else{
		TargetAreaArrayList=new FlexArea*[UniqueIDList.count()];
	}
	for(int i=0;i<UniqueIDList.count();i++){
		TargetAreaArrayList[i]=new FlexArea[DCAlgorithmInPagePIPointer->GetItemCount()];
	}

	for(int i=0;i<UniqueIDList.count();i++){
#ifndef Debug
		#pragma omp parallel
		{
			#pragma omp for
			for(int j=0;j<DCAlgorithmInPagePIPointer->GetItemCount();j++){
				AlgorithmItemPI	*AlgorithmItemPIPointer=(AlgorithmItemPI	*)DCAlgorithmInPagePIPointer->GetItemData(0,j);
#else
			int j;
			AlgorithmItemPI	*AlgorithmItemPIPointer;
			for(j=0;j<DCAlgorithmInPagePIPointer->GetItemCount();j++){
				AlgorithmItemPIPointer=DCAlgorithmInPagePIPointer->GetItem(j);
#endif
				AlgorithmItemPIPointer->GetArea(UniqueIDList.at(i)).MakeBitData(TargetDCBitmap[i],GetDotPerLine(),GetMaxLines());
				TargetAreaArrayList[i][j]=AlgorithmItemPIPointer->GetArea(UniqueIDList.at(i));
			}
#ifndef Debug
		}
#endif
	}
}

void	PixelInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPixelNGDrawMode	*CmdPixelNGDrawModeVar=dynamic_cast<CmdPixelNGDrawMode *>(packet);
	if(CmdPixelNGDrawModeVar!=NULL){
		int ItemCount=GetItemCount();
		for(int i=0;i<ItemCount;i++){
			((PixelInspectionItem *)GetItemData(0,i))->IsShowOnlyDetail=CmdPixelNGDrawModeVar->ShowOnlyDetail;
			((PixelInspectionItem *)GetItemData(0,i))->IsShowOnlyCircle=CmdPixelNGDrawModeVar->ShowOnlyCircle;
		}
		return;
	}

	CmdGetPixelInsDataFromGlobalPoint	*CmdGetPixelInsDataFromGlobalPointVar=dynamic_cast<CmdGetPixelInsDataFromGlobalPoint *>(packet);
	if(CmdGetPixelInsDataFromGlobalPointVar!=NULL){
		int	localX=CmdGetPixelInsDataFromGlobalPointVar->GlobalX - GetDataInPage()->GetOutlineOffset()->x;
		int	localY=CmdGetPixelInsDataFromGlobalPointVar->GlobalY - GetDataInPage()->GetOutlineOffset()->y;
		if(GetDataInPage()->IsInclude(localX,localY)==true){
			AlgorithmItemPI	*p=Data.GetItem(CmdGetPixelInsDataFromGlobalPointVar->CurrentIndex);
			if(p!=NULL){
				PixelInspectionItem	*pi=dynamic_cast<PixelInspectionItem *>(p);
				if(pi!=NULL && pi->PixData!=NULL){
					CmdGetPixelInsDataFromGlobalPointVar->PData=pi->PixData[localY][localX];
					return;
				}
			}
		}
	}
	CmdGetPixelGenerateDataFromArea	*CmdGetPixelGenerateDataFromAreaVar=dynamic_cast<CmdGetPixelGenerateDataFromArea *>(packet);
	if(CmdGetPixelGenerateDataFromAreaVar!=NULL){
		ImagePointerContainer Images;
		GetDataInPage()->GetMasterImages(Images);
		RGBStock Stocker;
		CmdGetPixelGenerateDataFromAreaVar->LocalArea.CreateRGBStock(Images, Stocker);
		ColorSphere	*c=new ColorSphere();
		c->Create(Stocker);
		CmdGetPixelGenerateDataFromAreaVar->ColorData.AddBase(c);
		return;
	}
	CmdAddItem	*CmdAddItemVar=dynamic_cast<CmdAddItem *>(packet);
	if(CmdAddItemVar!=NULL){
		AppendItem(CreateItem(0));
		return;
	}
	CmdDelItem	*CmdDelItemVar=dynamic_cast<CmdDelItem *>(packet);
	if(CmdDelItemVar!=NULL){
		AlgorithmItemPI	*p=(AlgorithmItemPI	*)GetItemData(0,CmdDelItemVar->CurrentIndex);
		if(p!=NULL){
			RemoveItem(p);
		}
	}
}

bool	PixelInspectionInPage::PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
/*
	for(PixelInspectionItem *item=(PixelInspectionItem *)GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->PipeOutAutoGenerationForLearning(f 
											, localX1
											, localY1
											, localX2 
											, localY2)==false){
			return false;
		}
	}
*/
	return true;
}

bool	PixelInspectionInPage::PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2)
{
/*
	for(PixelInspectionItem *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->PipeInAutoGenerationForLearning(f 
											,localX1
											,localY1
											,localX2 
											,localY2)==false){
			return false;
		}
	}
*/
	return true;
}

PixelInspectionParam::PixelInspectionParam(void){
	ColorNormal				=Qt::darkGreen;
	ColorSelected			=Qt::green;
	ColorActive				=Qt::red;
	TransparentLevel		=100;
	NegColorNormal			=Qt::yellow;
	NegColorSelected		=Qt::cyan;
	ColorNG					=Qt::red;
	InspectionLevel			=200;	//0-256		256:Highest
	SearchAreaForMakeTable	=1;
	SearchDotBase			=1;
	Colored					=true;
	DefaultLibraryID		=-1;
	NGThresholdP_B			=0;
	NGThresholdP_D			=0;
	NGThresholdS_B			=0;
	NGThresholdS_D			=0;
	NGThresholdR_B			=0;
	NGThresholdR_D			=0;
	NGThresholdH_B			=0;
	NGThresholdH_D			=0;
	MinimumNGSizeP			=4;
	MinimumNGSizeS			=4;
	MinimumNGSizeR			=4;
	MinimumNGSizeH			=4;
	DonePadIns				=false;
	NGThresholdForPad_B		=10;
	NGThresholdForPad_D		=10;
	MinimumNGSizeForPad		=100;
	DoneSilkIns				=false;
	NGThresholdForSilk_B	=10;
	NGThresholdForSilk_D	=10;
	MinimumNGSizeForSilk	=100;
	DoneResistIns			=false;
	NGThresholdForResist_B	=10;
	NGThresholdForResist_D	=10;
	MinimumNGSizeForResist	=100;
	DoneHoleIns				=false;
	NGThresholdForHole_B	=10;
	NGThresholdForHole_D	=10;
	MinimumNGSizeForHole	=100;
	CheckPadIns				=true;
	CheckSilkIns			=true;
	CheckResistIns			=true;
	CheckHoleIns			=true;
	BrightnessRange			=0;
	IsCalcPixelInterPoration=false;
	IsShowOnlyDetail		=false;
	IsShowOnlyCircle		=false;
	IsShowBoth				=true;
	IsAllowNothing			=true;
	NGSize					=100;
	NGSizeColor				=Qt::red;
	NGMarkSize				=1.0;
}

void PixelInspectionParam::setParam(PixelInspectionBase* PBase,int phase){
	if(phase==0){
		PBase->SetParam(&ColorNormal				, /**/"Color" ,/**/"ColorNormal"			,LangSolver.GetString(XPixelInspection_LS,LID_1)/*"Normal PixelInspection area color"*/);
		PBase->SetParam(&ColorSelected				, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XPixelInspection_LS,LID_3)/*"Selected PixelInspection area color"*/);
		PBase->SetParam(&ColorActive				, /**/"Color" ,/**/"ColorActive"			,LangSolver.GetString(XPixelInspection_LS,LID_5)/*"Active PixelInspection area color"*/);
		PBase->SetParam(&TransparentLevel			, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XPixelInspection_LS,LID_7)/*"PixelInspection Transparent Level"*/);
		PBase->SetParam(&NegColorNormal				, /**/"Color" ,/**/"NegColorNormal"		,LangSolver.GetString(XPixelInspection_LS,LID_9)/*"Negative normal PixelInspection area color"*/);
		PBase->SetParam(&NegColorSelected			, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XPixelInspection_LS,LID_11)/*"Negative selected PixelInspection area color"*/);
		PBase->SetParam(&ColorNG					, /**/"Color" ,/**/"ColorNG"			,LangSolver.GetString(XPixelInspection_LS,LID_13)/*"NG circle color"*/);
	
		PBase->SetParam(&InspectionLevel			, /**/"Threshold"	,/**/"InspectionLevel"			,LangSolver.GetString(XPixelInspection_LS,LID_15)/*"Inspection quality"*/);
		PBase->SetParam(&SearchAreaForMakeTable		, /**/"Threshold"	,/**/"SearchAreaForMakeTable"	,LangSolver.GetString(XPixelInspection_LS,LID_35)/*"Search dot for master data"*/);
		PBase->SetParam(&SearchDotBase				, /**/"Threshold"	,/**/"SearchDotBase"			,LangSolver.GetString(XPixelInspection_LS,LID_17)/*"Standard search dot"*/);
		PBase->SetParam(&Colored					, /**/"Threshold"	,/**/"Colored"					,LangSolver.GetString(XPixelInspection_LS,LID_19)/*"Is Colored"*/);
		PBase->SetParam(&DefaultLibraryID			, /**/"Setting"	,/**/"DefaultLibraryID"			,LangSolver.GetString(XPixelInspection_LS,LID_21)/*"Default LibraryID"*/);
	//	PBase->SetParam(&DefaultNGSize				, /**/"Setting"	,/**/"DefaultNGSize"			,LangSolver.GetString(XPixelInspection_LS,LID_23)/*"Default NG Size"*/);
		PBase->SetParam(&NGThresholdP_B				, /**/"Setting"	,/**/"NGThreshold"				,LangSolver.GetString(XPixelInspection_LS,LID_36)/*"NG Threshold P"*/);
		PBase->SetParam(&NGThresholdR_B				, /**/"Setting"	,/**/"NGThreshold2"				,LangSolver.GetString(XPixelInspection_LS,LID_37)/*"NG Threshold R"*/);
		PBase->SetParam(&MinimumNGSizeP				, /**/"Setting"	,/**/"MinimumNGSize"			,LangSolver.GetString(XPixelInspection_LS,LID_38)/*"Minimum NG Size P (pixel)"*/);
		PBase->SetParam(&DoneResistIns				, /**/"Setting"	,/**/"DoneResistIns"			,LangSolver.GetString(XPixelInspection_LS,LID_39)/*"Enable Detail Resist inspection"*/);
		PBase->SetParam(&NGThresholdForResist_B		, /**/"Setting"	,/**/"NGThresholdForResist"		,LangSolver.GetString(XPixelInspection_LS,LID_40)/*"NG Threshold for Detail Resist"*/);
		PBase->SetParam(&MinimumNGSizeForResist		, /**/"Setting"	,/**/"MinimumNGSizeForResist"	,LangSolver.GetString(XPixelInspection_LS,LID_41)/*"Minimum NG Size for Detail Resist (pixel)"*/);
		PBase->SetParam(&BrightnessRange			, /**/"Setting"	,/**/"BrightnessRange"			,LangSolver.GetString(XPixelInspection_LS,LID_42)/*"Permissible ambient brightness range (0-255)"*/);
		PBase->SetParam(&IsCalcPixelInterPoration	, /**/"Setting"	,/**/"IsCalcPixelInterPoration"	,LangSolver.GetString(XPixelInspection_LS,LID_43)/*"Enable Calc Pixel InterPoration"*/);
		PBase->SetParam(&DonePadIns					, /**/"Setting"	,/**/"DonePadIns"				,LangSolver.GetString(XPixelInspection_LS,LID_44)/*"Enable Detail Pad inspection"*/);
		PBase->SetParam(&NGThresholdForPad_B		, /**/"Setting"	,/**/"NGThresholdForPad"		,LangSolver.GetString(XPixelInspection_LS,LID_45)/*"NG Threshold for Detail Pad"*/);
		PBase->SetParam(&MinimumNGSizeForPad		, /**/"Setting"	,/**/"MinimumNGSizeForPad"		,LangSolver.GetString(XPixelInspection_LS,LID_46)/*"Minimum NG Size for Detail Pad (pixel)"*/);
		PBase->SetParam(&NGThresholdS_B				, /**/"Setting"	,/**/"NGThresholdS"				,LangSolver.GetString(XPixelInspection_LS,LID_47)/*"NG Threshold S"*/);
		PBase->SetParam(&MinimumNGSizeS				, /**/"Setting"	,/**/"MinimumNGSizeS"			,LangSolver.GetString(XPixelInspection_LS,LID_48)/*"Minimum NG Size S (pixel)"*/);
		PBase->SetParam(&MinimumNGSizeR				, /**/"Setting"	,/**/"MinimumNGSizeR"			,LangSolver.GetString(XPixelInspection_LS,LID_49)/*"Minimum NG Size R (pixel)"*/);
		PBase->SetParam(&DoneSilkIns				, /**/"Setting"	,/**/"DoneSilkIns"				,LangSolver.GetString(XPixelInspection_LS,LID_50)/*"Enable Detail Silk inspection"*/);
		PBase->SetParam(&NGThresholdForSilk_B		, /**/"Setting"	,/**/"NGThresholdForSilk"		,LangSolver.GetString(XPixelInspection_LS,LID_51)/*"NG Threshold for Detail Silk"*/);
		PBase->SetParam(&MinimumNGSizeForSilk		, /**/"Setting"	,/**/"MinimumNGSizeForSilk"		,LangSolver.GetString(XPixelInspection_LS,LID_52)/*"Minimum NG Size for Detail Silk (pixel)"*/);
		PBase->SetParam(&NGThresholdH_B				, /**/"Setting"	,/**/"NGThresholdH"				,LangSolver.GetString(XPixelInspection_LS,LID_53)/*"NG Threshold H"*/);
		PBase->SetParam(&MinimumNGSizeH				, /**/"Setting"	,/**/"MinimumNGSizeH"			,LangSolver.GetString(XPixelInspection_LS,LID_54)/*"Minimum NG Size H (pixel)"*/);
		PBase->SetParam(&DoneHoleIns				, /**/"Setting"	,/**/"DoneHoleIns"				,LangSolver.GetString(XPixelInspection_LS,LID_55)/*"Enable Detail Hole inspection"*/);
		PBase->SetParam(&NGThresholdForHole_B		, /**/"Setting"	,/**/"NGThresholdForHole"		,LangSolver.GetString(XPixelInspection_LS,LID_56)/*"NG Threshold for Detail Hole"*/);
		PBase->SetParam(&MinimumNGSizeForHole		, /**/"Setting"	,/**/"MinimumNGSizeForHole"		,LangSolver.GetString(XPixelInspection_LS,LID_57)/*"Minimum NG Size for Detail Hole (pixel)"*/);
		PBase->SetParam(&CheckPadIns				, /**/"Setting"	,/**/"CheckPadIns"				,LangSolver.GetString(XPixelInspection_LS,LID_58)/*"Enable Pad inspection"*/);
		PBase->SetParam(&CheckSilkIns				, /**/"Setting"	,/**/"CheckSilkIns"				,LangSolver.GetString(XPixelInspection_LS,LID_59)/*"Enable Silk inspection"*/);
		PBase->SetParam(&CheckResistIns				, /**/"Setting"	,/**/"CheckResistIns"			,LangSolver.GetString(XPixelInspection_LS,LID_60)/*"Enable Resist inspection"*/);
		PBase->SetParam(&CheckHoleIns				, /**/"Setting"	,/**/"CheckHoleIns"				,LangSolver.GetString(XPixelInspection_LS,LID_61)/*"Enable Hole inspection"*/);
		PBase->SetParam(&IsShowOnlyDetail			, /**/"Setting"	,/**/"IsShowOnlyDetail"			,LangSolver.GetString(XPixelInspection_LS,LID_62)/*"Show Only NG Detail Mode"*/);
		PBase->SetParam(&IsShowOnlyCircle			, /**/"Setting"	,/**/"IsShowOnlyCircle"			,LangSolver.GetString(XPixelInspection_LS,LID_63)/*"Show Only NG Circle Mode"*/);
		PBase->SetParam(&IsShowBoth					, /**/"Setting"	,/**/"IsShowBoth"				,LangSolver.GetString(XPixelInspection_LS,LID_64)/*"Show NG Detail & Circle Mode"*/);
		PBase->SetParam(&IsAllowNothing				, /**/"Setting"	,/**/"IsAllowNothing"			,LangSolver.GetString(XPixelInspection_LS,LID_65)/*"Allow Nothing NG Show Mode"*/);

		PBase->SetParam(&NGThresholdP_D				, /**/"Setting"	,/**/"NGThresholdP_D"			,LangSolver.GetString(XPixelInspection_LS,LID_150)/*"NG Threshold P Dark"*/);
		PBase->SetParam(&NGThresholdForPad_D		, /**/"Setting"	,/**/"NGThresholdForPad_D"		,LangSolver.GetString(XPixelInspection_LS,LID_151)/*"NG Threshold for Detail Pad Dark"*/);
		PBase->SetParam(&NGThresholdS_D				, /**/"Setting"	,/**/"NGThresholdS_D"			,LangSolver.GetString(XPixelInspection_LS,LID_152)/*"NG Threshold S Dark"*/);
		PBase->SetParam(&NGThresholdForSilk_D		, /**/"Setting"	,/**/"NGThresholdForSilk_D"		,LangSolver.GetString(XPixelInspection_LS,LID_153)/*"NG Threshold for Detail Silk Dark"*/);
		PBase->SetParam(&NGThresholdR_D				, /**/"Setting"	,/**/"NGThresholdR_D"			,LangSolver.GetString(XPixelInspection_LS,LID_154)/*"NG Threshold R Dark"*/);
		PBase->SetParam(&NGThresholdForResist_D		, /**/"Setting"	,/**/"NGThresholdForResist_D"	,LangSolver.GetString(XPixelInspection_LS,LID_155)/*"NG Threshold for Detail Resist Dark"*/);
		PBase->SetParam(&NGThresholdH_D				, /**/"Setting"	,/**/"NGThresholdH_D"			,LangSolver.GetString(XPixelInspection_LS,LID_156)/*"NG Threshold H Dark"*/);
		PBase->SetParam(&NGThresholdForHole_D		, /**/"Setting"	,/**/"NGThresholdForHole_D"		,LangSolver.GetString(XPixelInspection_LS,LID_157)/*"NG Threshold for Detail Hole Dark"*/);

		PBase->SetParam(&NGSize						, /**/"Setting",/**/"NGSize"					,LangSolver.GetString(XPixelInspection_LS,LID_0)/*"Setting NG size(pixels)"*/);
		PBase->SetParam(&NGSizeColor				, /**/"Setting",/**/"NGSizeColor"				,LangSolver.GetString(XPixelInspection_LS,LID_2)/*"Setting NG size color"*/);
		PBase->SetParam(&NGMarkSize					, /**/"Setting",/**/"NGMarkSize"				,LangSolver.GetString(XPixelInspection_LS,LID_4)/*"Setting NG size mark scale"*/);
	}
	else{
		PBase->SetParam(&InspectionLevel			, /**/"Setting2"	,/**/"InspectionLevel_back"			,LangSolver.GetString(XPixelInspection_LS,LID_15)/*"Inspection quality"*/);
		PBase->SetParam(&DefaultLibraryID			, /**/"Setting2"	,/**/"DefaultLibraryID_back"		,LangSolver.GetString(XPixelInspection_LS,LID_21)/*"Default LibraryID"*/);
		PBase->SetParam(&NGThresholdP_B				, /**/"Setting2"	,/**/"NGThreshold_back"				,LangSolver.GetString(XPixelInspection_LS,LID_36)/*"NG Threshold P"*/);
		PBase->SetParam(&NGThresholdR_B				, /**/"Setting2"	,/**/"NGThreshold2_back"			,LangSolver.GetString(XPixelInspection_LS,LID_37)/*"NG Threshold R"*/);
		PBase->SetParam(&MinimumNGSizeP				, /**/"Setting2"	,/**/"MinimumNGSize_back"			,LangSolver.GetString(XPixelInspection_LS,LID_38)/*"Minimum NG Size P (pixel)"*/);
		PBase->SetParam(&DoneResistIns				, /**/"Setting2"	,/**/"DoneResistIns_back"			,LangSolver.GetString(XPixelInspection_LS,LID_39)/*"Enable Detail Resist inspection"*/);
		PBase->SetParam(&NGThresholdForResist_B		, /**/"Setting2"	,/**/"NGThresholdForResist_back"	,LangSolver.GetString(XPixelInspection_LS,LID_40)/*"NG Threshold for Detail Resist"*/);
		PBase->SetParam(&MinimumNGSizeForResist		, /**/"Setting2"	,/**/"MinimumNGSizeForResist_back"	,LangSolver.GetString(XPixelInspection_LS,LID_41)/*"Minimum NG Size for Detail Resist (pixel)"*/);
		PBase->SetParam(&BrightnessRange			, /**/"Setting2"	,/**/"BrightnessRange_back"			,LangSolver.GetString(XPixelInspection_LS,LID_42)/*"Permissible ambient brightness range (0-255)"*/);
		PBase->SetParam(&IsCalcPixelInterPoration	, /**/"Setting2"	,/**/"IsCalcPixelInterPoration_back",LangSolver.GetString(XPixelInspection_LS,LID_43)/*"Enable Calc Pixel InterPoration"*/);
		PBase->SetParam(&DonePadIns					, /**/"Setting2"	,/**/"DonePadIns_back"				,LangSolver.GetString(XPixelInspection_LS,LID_44)/*"Enable Detail Pad inspection"*/);
		PBase->SetParam(&NGThresholdForPad_B		, /**/"Setting2"	,/**/"NGThresholdForPad_back"		,LangSolver.GetString(XPixelInspection_LS,LID_45)/*"NG Threshold for Detail Pad"*/);
		PBase->SetParam(&MinimumNGSizeForPad		, /**/"Setting2"	,/**/"MinimumNGSizeForPad_back"		,LangSolver.GetString(XPixelInspection_LS,LID_46)/*"Minimum NG Size for Detail Pad (pixel)"*/);
		PBase->SetParam(&NGThresholdS_B				, /**/"Setting2"	,/**/"NGThresholdS_back"			,LangSolver.GetString(XPixelInspection_LS,LID_47)/*"NG Threshold S"*/);
		PBase->SetParam(&MinimumNGSizeS				, /**/"Setting2"	,/**/"MinimumNGSizeS_back"			,LangSolver.GetString(XPixelInspection_LS,LID_48)/*"Minimum NG Size S (pixel)"*/);
		PBase->SetParam(&MinimumNGSizeR				, /**/"Setting2"	,/**/"MinimumNGSizeR_back"			,LangSolver.GetString(XPixelInspection_LS,LID_49)/*"Minimum NG Size R (pixel)"*/);
		PBase->SetParam(&DoneSilkIns				, /**/"Setting2"	,/**/"DoneSilkIns_back"				,LangSolver.GetString(XPixelInspection_LS,LID_50)/*"Enable Detail Silk inspection"*/);
		PBase->SetParam(&NGThresholdForSilk_B		, /**/"Setting2"	,/**/"NGThresholdForSilk_back"		,LangSolver.GetString(XPixelInspection_LS,LID_51)/*"NG Threshold for Detail Silk"*/);
		PBase->SetParam(&MinimumNGSizeForSilk		, /**/"Setting2"	,/**/"MinimumNGSizeForSilk_back"	,LangSolver.GetString(XPixelInspection_LS,LID_52)/*"Minimum NG Size for Detail Silk (pixel)"*/);
		PBase->SetParam(&NGThresholdH_B				, /**/"Setting2"	,/**/"NGThresholdH_back"			,LangSolver.GetString(XPixelInspection_LS,LID_53)/*"NG Threshold H"*/);
		PBase->SetParam(&MinimumNGSizeH				, /**/"Setting2"	,/**/"MinimumNGSizeH_back"			,LangSolver.GetString(XPixelInspection_LS,LID_54)/*"Minimum NG Size H (pixel)"*/);
		PBase->SetParam(&DoneHoleIns				, /**/"Setting2"	,/**/"DoneHoleIns_back"				,LangSolver.GetString(XPixelInspection_LS,LID_55)/*"Enable Detail Hole inspection"*/);
		PBase->SetParam(&NGThresholdForHole_B		, /**/"Setting2"	,/**/"NGThresholdForHole_back"		,LangSolver.GetString(XPixelInspection_LS,LID_56)/*"NG Threshold for Detail Hole"*/);
		PBase->SetParam(&MinimumNGSizeForHole		, /**/"Setting2"	,/**/"MinimumNGSizeForHole_back"	,LangSolver.GetString(XPixelInspection_LS,LID_57)/*"Minimum NG Size for Detail Hole (pixel)"*/);
		PBase->SetParam(&CheckPadIns				, /**/"Setting2"	,/**/"CheckPadIns_back"				,LangSolver.GetString(XPixelInspection_LS,LID_58)/*"Enable Pad inspection"*/);
		PBase->SetParam(&CheckSilkIns				, /**/"Setting2"	,/**/"CheckSilkIns_back"			,LangSolver.GetString(XPixelInspection_LS,LID_59)/*"Enable Silk inspection"*/);
		PBase->SetParam(&CheckResistIns				, /**/"Setting2"	,/**/"CheckResistIns_back"			,LangSolver.GetString(XPixelInspection_LS,LID_60)/*"Enable Resist inspection"*/);
		PBase->SetParam(&CheckHoleIns				, /**/"Setting2"	,/**/"CheckHoleIns_back"			,LangSolver.GetString(XPixelInspection_LS,LID_61)/*"Enable Hole inspection"*/);
		PBase->SetParam(&IsShowOnlyDetail			, /**/"Setting2"	,/**/"IsShowOnlyDetail_back"		,LangSolver.GetString(XPixelInspection_LS,LID_62)/*"Show Only NG Detail Mode"*/);
		PBase->SetParam(&IsShowOnlyCircle			, /**/"Setting2"	,/**/"IsShowOnlyCircle_back"		,LangSolver.GetString(XPixelInspection_LS,LID_63)/*"Show Only NG Circle Mode"*/);
		PBase->SetParam(&IsShowBoth					, /**/"Setting2"	,/**/"IsShowBoth_back"				,LangSolver.GetString(XPixelInspection_LS,LID_64)/*"Show NG Detail & Circle Mode"*/);
		PBase->SetParam(&IsAllowNothing				, /**/"Setting2"	,/**/"IsAllowNothing_back"			,LangSolver.GetString(XPixelInspection_LS,LID_65)/*"Allow Nothing NG Show Mode"*/);

		PBase->SetParam(&NGThresholdP_D				, /**/"Setting2"	,/**/"NGThresholdP_D_back"			,LangSolver.GetString(XPixelInspection_LS,LID_150)/*"NG Threshold P Dark"*/);
		PBase->SetParam(&NGThresholdForPad_D		, /**/"Setting2"	,/**/"NGThresholdForPad_D_back"		,LangSolver.GetString(XPixelInspection_LS,LID_151)/*"NG Threshold for Detail Pad Dark"*/);
		PBase->SetParam(&NGThresholdS_D				, /**/"Setting2"	,/**/"NGThresholdS_D_back"			,LangSolver.GetString(XPixelInspection_LS,LID_152)/*"NG Threshold S Dark"*/);
		PBase->SetParam(&NGThresholdForSilk_D		, /**/"Setting2"	,/**/"NGThresholdForSilk_D_back"	,LangSolver.GetString(XPixelInspection_LS,LID_153)/*"NG Threshold for Detail Silk Dark"*/);
		PBase->SetParam(&NGThresholdR_D				, /**/"Setting2"	,/**/"NGThresholdR_D_back"			,LangSolver.GetString(XPixelInspection_LS,LID_154)/*"NG Threshold R Dark"*/);
		PBase->SetParam(&NGThresholdForResist_D		, /**/"Setting2"	,/**/"NGThresholdForResist_D_back"	,LangSolver.GetString(XPixelInspection_LS,LID_155)/*"NG Threshold for Detail Resist Dark"*/);
		PBase->SetParam(&NGThresholdH_D				, /**/"Setting2"	,/**/"NGThresholdH_D_back"			,LangSolver.GetString(XPixelInspection_LS,LID_156)/*"NG Threshold H Dark"*/);
		PBase->SetParam(&NGThresholdForHole_D		, /**/"Setting2"	,/**/"NGThresholdForHole_D_back"	,LangSolver.GetString(XPixelInspection_LS,LID_157)/*"NG Threshold for Detail Hole Dark"*/);

		PBase->SetParam(&NGSize						, /**/"Setting2"	,/**/"NGSize_back"					,LangSolver.GetString(XPixelInspection_LS,LID_6)/*"Setting NG size(pixels)"*/);
		PBase->SetParam(&NGSizeColor				, /**/"Setting2"	,/**/"NGSizeColor_back"				,LangSolver.GetString(XPixelInspection_LS,LID_8)/*"Setting NG size color"*/);
		PBase->SetParam(&NGMarkSize					, /**/"Setting2"	,/**/"NGMarkSize_back"				,LangSolver.GetString(XPixelInspection_LS,LID_10)/*"Setting NG size mark scale"*/);
	}
}

//===============================================================================

PixelInspectionBase::PixelInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	for(int phase=0;phase<2;phase++){
		Param[phase].setParam(this,phase);
	}
	MasterLoadVer			=-1;
	ResultImportanceColor	=Qt::red;
}

bool	PixelInspectionBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false){
		return false;
	}
	return true;
}
bool	PixelInspectionBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false){
		return false;
	}

	//?}?X?^?[?f?[?^?I?o?[?W?????a?ÅëLoad?I??
	qint64 Pos=f->pos();
	if(::Load(f,MasterLoadVer)==true){
		if(MasterLoadVer==0){
			//???u?o?[?W????
			//int32	N=Conditions.GetNumber();?ILoad?I???c
			//?Å‚?I?U?U???a?É ?E?Åë
		}
		else if(MasterLoadVer==2){
			//?Å‚?i?K?I?o?[?W?????i2012.02.28?j
			//Ver:2?I?AAlgorithmInPagePI::Save?A?t?ÅP?c?e?eVer
			f->seek(Pos);	//?|?C???^?d?s?ÅE
		}
	}

	return true;
}

ExeResult	PixelInspectionBase::ExecuteInitialAfterEdit(int ExeID 
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		ResultBasePhase		*Ph=Res->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			GetPageDataPhase(phase)->GetPageData(page)->ExecuteInitialAfterEdit(ExeID 
																				,Ph->GetPageData(page)
																				,EInfo);
		}
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
	// phase function : ?S?A?I?t?F?C?Y?I?A?C?e?Ä?AExecuteInitialAfterEdit?I?i?A???e???I?S?A?I?A?C?e?Ä?Iflag?dfalse?E?ÅE?e
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			PixelInspectionInPage* Page = (PixelInspectionInPage*)GetPageDataPhase(phase)->GetPageData(page);
			for(int i=0;i<Page->GetItemCount();i++){
				PixelInspectionItem *item = (PixelInspectionItem *)Page->GetItemData(0,i);
				if(item->getExecuteInitialAfterEditFlag()==false)
					return _ER_true;
			}
		}
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			PixelInspectionInPage* Page = (PixelInspectionInPage*)GetPageDataPhase(phase)->GetPageData(page);
			for(int i=0;i<Page->GetItemCount();i++){
				PixelInspectionItem *item = (PixelInspectionItem *)Page->GetItemData(0,i);
				item->setExecuteInitialAfterEditFlag(false);
			}
		}
	}
	return _ER_true;
}

AlgorithmDrawAttr	*PixelInspectionBase::CreateDrawAttr(void)
{
	return NULL;
}

void	PixelInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPixelNGDrawMode	*CmdPixelNGDrawModeVar=dynamic_cast<CmdPixelNGDrawMode *>(packet);
	if(CmdPixelNGDrawModeVar!=NULL){
		//???u?\?|
		if(CmdPixelNGDrawModeVar->ShowOnlyDetail==true && CmdPixelNGDrawModeVar->ShowOnlyCircle==true){
			if(getIsShowBoth()==true){
				//???u?\?|
				CmdPixelNGDrawModeVar->Ret=0;
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==3){
				//?3??
				if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
				else if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
				else if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==1){
				//?t??
				if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
				else if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
				else if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
			}
		}
		//?U?Å~?\?|?I?Y
		else if(CmdPixelNGDrawModeVar->ShowOnlyDetail==true){
			if(getIsShowOnlyDetail()==true){
				//?U?Å~?\?|?I?Y
				CmdPixelNGDrawModeVar->Ret=3;
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==2){
				//?3??
				if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
				else if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
				else if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==0){
				//?t??
				if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
				else if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
				else if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
			}
		}
		else if(CmdPixelNGDrawModeVar->ShowOnlyCircle==true){
			if(getIsShowOnlyCircle()==true){
				//?O?U?\?|?I?Y
				CmdPixelNGDrawModeVar->Ret=2;
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==1){
				//?3??
				if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
				else if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
				else if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==3){
				//?t??
				if(getIsAllowNothing()==true){
					//?O?\?|?d?A?ÅE
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=1;
				}
				else if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
				else if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
			}
		}
		else{
			if(getIsAllowNothing()==true){
				//?O?\?|?d?A?ÅE
				CmdPixelNGDrawModeVar->Ret=1;
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==0){
				//?3??
				if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
				else if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
				else if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
			}
			else if(CmdPixelNGDrawModeVar->GeneralInfo2==2){
				//?t??
				if(getIsShowBoth()==true){
					//???u?\?|
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=0;
				}
				else if(getIsShowOnlyDetail()==true){
					//?U?Å~?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=true;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=false;
					CmdPixelNGDrawModeVar->Ret=3;
				}
				else if(getIsShowOnlyCircle()==true){
					//?O?U?\?|?I?Y
					CmdPixelNGDrawModeVar->ShowOnlyDetail=false;
					CmdPixelNGDrawModeVar->ShowOnlyCircle=true;
					CmdPixelNGDrawModeVar->Ret=2;
				}
			}
		}
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				GetPageDataPhase(phase)->GetPageData(page)->TransmitDirectly(packet);
			}
		}
		//?A?`?a
		GUIFormBase	*TargetImage;
		for(int phase=0;phase<GetLayersBase()->GetPhaseNumb();phase++){
			QString TargetImagePanelName(/**/"");
			if(phase==1)
				TargetImagePanelName = /**/"TargetImage2";
			TargetImage=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,TargetImagePanelName);
			if(TargetImage==NULL){
				return;
			}
			DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
			TargetImagePanel->repaint();
		}
		//?A?`?a
		TargetImage=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayThumbnailImage" ,/**/"");
		if(TargetImage==NULL){
			return;
		}
		TargetImage->repaint();
		// TODO: PopupGeneralDisplayWholeImage repaints.

		return;
	}
	CmdResultImportanceColor	*CmdResultImportanceColorVar=dynamic_cast<CmdResultImportanceColor *>(packet);
	if(CmdResultImportanceColorVar!=NULL){
		ResultImportanceColor=CmdResultImportanceColorVar->ResultImportanceColor;
		return;
	}
	CmdPixelNGSize	*CmdPixelNGSizeVar=dynamic_cast<CmdPixelNGSize *>(packet);
	if(CmdPixelNGSizeVar!=NULL){
		CmdPixelNGSizeVar->NGSize		=getNGSize();
		CmdPixelNGSizeVar->NGSizeColor	=getNGSizeColor();
		return;
	}

	if(dynamic_cast<CmdAddItem *>(packet)!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
	}
	int AAA;
	CmdCreateNGListPacket	*CmdCreateNGListPacketVar=dynamic_cast<CmdCreateNGListPacket *>(packet);
	if(CmdCreateNGListPacketVar!=NULL){
		if(CmdCreateNGListPacketVar->Res!=NULL){
			ResultBaseForAlgorithmRoot	*AR=CmdCreateNGListPacketVar->Res->GetResultBaseForAlgorithm(this);
			if(AR!=NULL){
				int	phase=GetLayersBase()->GetCurrentPhase();
				ResultBasePhase		*Ph=AR->GetPageDataPhase(phase);
				for(int page=0;page<GetPageNumb();page++){
					ResultInPageRoot	*RP=Ph->GetPageData(page);
					ResultInPagePI	*RPI=dynamic_cast<ResultInPagePI *>(RP);
					for(int i=0;i<RP->GetNGCount();i++){
						ResultInItemPI		*RI=RPI->GetItem(i);
						if(RI->GetAddedDataType()==ResultPixelOnItemType && RI->GetAddedData()!=NULL){
							ResultClusterOnItem	*Ro=(ResultClusterOnItem *)RI->GetAddedData();
							AAA=Ro->List.GetNumber();
							for(PureFlexAreaList *p=Ro->List.GetFirst();p!=NULL;p=p->GetNext()){
								PixelInspectionNGDataList	*a=new PixelInspectionNGDataList();
								a->Page=page;
								p->GetCenter(a->CenterX,a->CenterY);
								a->LibID=RI->GetAlgorithmItemRoot()->GetLibID();
								a->Area=p->GetPatternByte();
								CmdCreateNGListPacketVar->Point->AppendList(a);
							}
						}
					}
				}
			}
		}
		return;
	}
	CmdReqCalcThresholdPacket	*ReqCalcThresholdPacket=dynamic_cast<CmdReqCalcThresholdPacket *>(packet);
	if(ReqCalcThresholdPacket!=NULL){
		GetLayersBase()->ClearAllAckFlag();
		GetLayersBase()->ShowProcessingForm(/**/"CalcThreshold");
		for(int page=0;page<GetPageNumb();page++){
			if(((PixelInspectionInPage *)GetPageData(page))->GetIsMultiAlgorithmSupport()==true){
				//?A?Y?e
				((PixelInspectionInPage *)GetPageData(page))->ReExecMultiAlgorithmSupport();
				//Item?Ee??l?d?Y?e?ÅE?e
				((PixelInspectionInPage *)GetPageData(page))->CreateItemThreshold();
/*
				//?S?A?IItem?dDelete
				((PixelInspectionInPage *)GetPageData(page))->DeletePixelItem();
				//?A?Y?e
				((PixelInspectionInPage *)GetPageData(page))->ExecMultiAlgorithmSupport();
				//Item?Ee??l?d?Y?e?ÅE?e
				((PixelInspectionInPage *)GetPageData(page))->CreateItemThreshold();
*/
			}
		}
		GetLayersBase()->CloseProcessingForm();
		return;
	}
	CmdCreateTempPixelInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempPixelInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdGetPixelInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetPixelInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(AListPacket->LibFolderID==-1)
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->AList);
		else
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID,AListPacket->AList);
		return;
	}
	CmdGetPixelInspectionLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetPixelInspectionLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		return;
	}
	CmdInsertPixelInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertPixelInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(PixelInspectionVersion);
		GetLibraryContainer()->SaveNew(*BInsLib->Point);
		return;
	}
	CmdUpdatePixelInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdatePixelInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(PixelInspectionVersion);
		GetLibraryContainer()->Update(*BUpdLib->Point);
		return;
	}
	CmdLoadPixelInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadPixelInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		GetLibraryContainer()->Load(*BLoadLib->Point);
		return;
	}
	CmdDeletePixelInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeletePixelInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		return;
	}
}

void	PixelInspectionBase::MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmBase::MakeIndependentItems(TargetPhase,localPage,SubResultMoving,localX,localY,Data);

	PixelInspectionInPage *PInPage=dynamic_cast<PixelInspectionInPage *>(GetPageData(localPage));
	PInPage->SetLocalX(localX);
	PInPage->SetLocalY(localY);
}

bool	PixelInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
/*
	if(Command==PixelHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==PixelHistogramListReqCommand){
		delete	data;
		return true;
	}
*/
	if(Command==PixelReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==PixelReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==PixelReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==PixelSendTryThresholdCommand){
		delete	data;
		return true;
	}
/*
	else if(Command==PixelReqChangeShiftCommand){
		delete	data;
		return true;
	}
*/
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*PixelInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
/*
	if(Command==PixelHistogramListSendCommand){
		PixelHistogramListSend	*pSend=new PixelHistogramListSend();
		if(reqData!=NULL){
			PixelHistogramListReq	*req=(PixelHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==PixelHistogramListReqCommand){
		return new PixelHistogramListReq();
	}
*/
	if(Command==PixelReqThresholdReqCommand){
		return new PixelThresholdReq();
	}
	else if(Command==PixelReqThresholdSendCommand){
		PixelThresholdSend	*pSend=new PixelThresholdSend();
		if(reqData!=NULL){
			PixelThresholdReq	*req=(PixelThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==PixelReqTryThresholdCommand){
		return new PixelTryThresholdReq();
	}
	else if(Command==PixelSendTryThresholdCommand){
		PixelTryThresholdSend	*pSend=new PixelTryThresholdSend();
		if(reqData!=NULL){
			PixelTryThresholdReq	*req=(PixelTryThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
/*
	else if(Command==PixelReqChangeShiftCommand){
		return new PixelChangeShift();
	}
*/
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	PixelInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
/*
	if(Command==PixelHistogramListSendCommand){
		PixelHistogramListSend	*p=(PixelHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==PixelHistogramListReqCommand){
		PixelHistogramListReq	*p=(PixelHistogramListReq *)data;
		return p->Load(f);
	}
*/
	if(Command==PixelReqThresholdReqCommand){
		PixelThresholdReq	*p=(PixelThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==PixelReqThresholdSendCommand){
		PixelThresholdSend	*p=(PixelThresholdSend *)data;
		return p->Load(f);
	}
/*
	else if(Command==PixelReqTryThresholdCommand){
		PixelReqTryThreshold	*p=(PixelReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==PixelSendTryThresholdCommand){
		PixelSendTryThreshold	*p=(PixelSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==PixelReqChangeShiftCommand){
		PixelChangeShift	*p=(PixelChangeShift *)data;
		return p->Load(f);
	}
*/
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	PixelInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
/*
	if(Command==PixelHistogramListSendCommand){
		PixelHistogramListSend	*p=(PixelHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==PixelHistogramListReqCommand){
		PixelHistogramListReq	*p=(PixelHistogramListReq *)data;
		return p->Save(f);
	}
*/
	if(Command==PixelReqThresholdReqCommand){
		PixelThresholdReq	*p=(PixelThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==PixelReqThresholdSendCommand){
		PixelThresholdSend	*p=(PixelThresholdSend *)data;
		return p->Save(f);
	}
/*
	else if(Command==PixelReqTryThresholdCommand){
		PixelReqTryThreshold	*p=(PixelReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==PixelSendTryThresholdCommand){
		PixelSendTryThreshold	*p=(PixelSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==PixelReqChangeShiftCommand){
		PixelChangeShift	*p=(PixelChangeShift *)data;
		return p->Save(f);
	}
*/
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	PixelInspectionBase::GeneralDataReply(int32 Command,void *data)
{
/*
	if(Command==PixelHistogramListSendCommand){
		PixelHistogramListSend	*p=(PixelHistogramListSend *)data;
		return true;
	}
	else if(Command==PixelHistogramListReqCommand){
		PixelHistogramListReq	*p=(PixelHistogramListReq *)data;
		return true;
	}
*/
	if(Command==PixelReqThresholdReqCommand){
		PixelThresholdReq	*p=(PixelThresholdReq *)data;
		return true;
	}
	else if(Command==PixelReqThresholdSendCommand){
		PixelThresholdSend	*p=(PixelThresholdSend *)data;
		return true;
	}
/*
	else if(Command==PixelReqTryThresholdCommand){
		PixelReqTryThreshold	*p=(PixelReqTryThreshold *)data;
		return true;
	}
	else if(Command==PixelSendTryThresholdCommand){
		PixelSendTryThreshold	*p=(PixelSendTryThreshold *)data;
		return true;
	}
	else if(Command==PixelReqChangeShiftCommand){
		PixelChangeShift	*p=(PixelChangeShift *)data;
		p->Reflect(this);
		return true;
	}
*/
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	PixelInspectionBase::PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	PixelInspectionInPage	*P=(PixelInspectionInPage *)GetPageData(LocalPage);
	if(P->PipeOutAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}
bool	PixelInspectionBase::PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)
{
	PixelInspectionInPage	*P=(PixelInspectionInPage *)GetPageData(LocalPage);
	if(P->PipeInAutoGenerationForLearning(f ,localX1, localY1, localX2 ,localY2)==false){
		return false;
	}
	return true;
}
