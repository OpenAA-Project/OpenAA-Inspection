#include "XMeasureLineMoveResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\XMeasureLineMove.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XMasking.h"
#include "XMaskingLibrary.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureLineMove.h"
#include "XDisplayBitImage.h"
#include "omp.h"
#include "XCriticalFunc.h"
#include "XFileThread.h"
#include "XLearningRegist.h"
#include "XTransform.h"
//==============================================================================
bool	ResultLineMoveInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)
{
	WrittenNGCount=0;
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;

		int32	N=0;
		for(ResultInItemPI *a=GetResultFirst();a!=NULL;a=a->GetNext()){
			if(a->GetError()==0){
				continue;
			}
			if(a->IsOk()==true){
				N++;
			}
			else{
				for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
					N++;
				}
			}
		}
		if(::Save(f,N)==false){
			return false;
		}

		for(ResultInItemPI *a=GetResultFirst();a!=NULL;a=a->GetNext()){
			if(a->GetError()==0){
				continue;
			}
			AlgorithmItemRoot	*Item=a->GetAlgorithmItem();
			if(Item!=NULL){
				if(a->IsOk()==true){
					ResultPositionInfomation	RData;

					Item->GetCenter(RData.X,RData.Y);
					RData.Error=a->GetError();
					RData.MX=a->GetAlignedX();
					RData.MY=a->GetAlignedY();
					RData.HX=0;
					RData.HY=0;
					LBase->ConvertToTop(RData.X,RData.Y);
					LBase->ConvertToTop(RData.MX,RData.MY);
					LBase->ConvertToTop(RData.HX,RData.HY);

					RData.ResultValue.ResultDouble	=a->GetResultDouble();
					RData.ResultType	=_ResultDouble;
					RData.LibID			=Item->GetLibID();
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					RData.Layer		=0;
					RData.UniqueID1	=Item->GetID();
					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					WrittenNGCount++;
				}
				else{
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						QStringList	AreaNames;
						if(p->AreaNames.count()==0){
							QString	AreaName;
							if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
								AreaName=/**/"";
								AreaNames.append(AreaName);
							}
							else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																								,p->Py	//+a->GetAlignedY()+p->Ry 
																								,AreaName)==true){
								AreaNames.append(AreaName);
							}
						}
						else{
							AreaNames=p->AreaNames;
						}
						QByteArray	EData;
						ResultPositionInfomation	RData;
						RData.Error=a->GetError();
						RData.X=p->Px+a->GetAlignedX()+p->Rx;
						RData.Y=p->Py+a->GetAlignedY()+p->Ry;
						RData.MX=a->GetAlignedX();
						RData.MY=a->GetAlignedY();
						RData.HX=p->Rx;
						RData.HY=p->Ry;

						LBase->ConvertToTop(RData.X,RData.Y);
						LBase->ConvertToTop(RData.MX,RData.MY);
						LBase->ConvertToTop(RData.HX,RData.HY);

						p->GetExtraData(EData);
						RData.ExtraDataByte	=EData.size();

						if(AreaNames.count()!=0){
							QString	AName;
							int	AreaNameCount=0;
							for(int k=0;k<AreaNames.count();k++){
								if(AreaNames[k].length()!=0){
									AreaNameCount++;
								}
							}
							if(AreaNameCount!=0){
								for(int k=0;k<AreaNames.count();k++){
									AName=AName+AreaNames[k];
									if(k<AreaNames.count()-1){
										AName=AName+QString(/**/",");
									}
								}
							}					
							::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
						}
						else{
							memset(&RData.AreaName,0,sizeof(RData.AreaName));
						}

						if(Item!=NULL){
							RData.LibID	=a->GetAlgorithmItem()->GetLibID();
							RData.UniqueID1	=Item->GetID();
						}
						else{
							RData.LibID	=-1;
							RData.UniqueID1	=-1;
						}

						RData.NGTypeUniqueCode	=-1;	
						if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
							LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
							if(t!=NULL){
								RData.NGTypeUniqueCode	=t->TypeCode;
							}
						}
						RData.ResultValue.ResultDouble	=a->GetResultDouble();
						RData.ResultType	=_ResultDouble;
						DWORD	*dwp=(DWORD	*)RData.Something;
						*dwp	=p->GetResult1();
						*(dwp+1)=p->GetResult2();
						AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
						if(pLibContainer!=NULL){
							RData.LibType=pLibContainer->GetLibType();
						}
						RData.Layer		=0;
						
						if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
							return false;
						}
						if(RData.ExtraDataByte>0){
							if(f->write(EData)!=RData.ExtraDataByte){
								return false;
							}
						}
						WrittenNGCount++;
					}
				}
			}
		}
	}
	return true;
}
bool	ResultLineMoveInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f
											,int &WrittenNGCount)
{
	WrittenNGCount=0;
	LayersBase	*LBase=GetLayersBase();
	bool	OutputNGCause=(LBase!=NULL)?LBase->GetParamGlobal()->OutputNGCause:false;

	int32	N=0;
	for(ResultInItemPI *a=GetResultFirst();a!=NULL;a=a->GetNext()){
		if(a->GetError()==0){
			continue;
		}
		if(a->IsOk()==true){
			N++;
		}
		else{
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				N++;
			}
		}
	}
	if(f->Save(N)==false){
		return false;
	}

	for(ResultInItemPI *a=GetResultFirst();a!=NULL;a=a->GetNext()){
		if(a->GetError()==0){
			continue;
		}
		AlgorithmItemRoot	*Item=a->GetAlgorithmItem();
		if(Item!=NULL){
			if(a->IsOk()==true){
				ResultPositionInfomation	RData;

				Item->GetCenter(RData.X,RData.Y);
				RData.Error=a->GetError();
				RData.MX=a->GetAlignedX();
				RData.MY=a->GetAlignedY();
				RData.HX=0;
				RData.HY=0;

				RData.ResultValue.ResultDouble	=a->GetResultDouble();
				RData.ResultType	=_ResultDouble;
				RData.LibID			=Item->GetLibID();
				AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
				if(pLibContainer!=NULL){
					RData.LibType=pLibContainer->GetLibType();
				}
				RData.Layer		=0;
				RData.UniqueID1	=Item->GetID();
				if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
					return false;
				}
				WrittenNGCount++;
			}
			else{
				for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
					QStringList	AreaNames;
					if(p->AreaNames.count()==0){
						QString	AreaName;
						if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
							AreaName=/**/"";
							AreaNames.append(AreaName);
						}
						else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																							,p->Py	//+a->GetAlignedY()+p->Ry 
																							,AreaName)==true){
							AreaNames.append(AreaName);
						}
					}
					else{
						AreaNames=p->AreaNames;
					}
					QByteArray	EData;
					ResultPositionInfomation	RData;
					RData.Error=a->GetError();
					RData.X=p->Px+a->GetAlignedX()+p->Rx;
					RData.Y=p->Py+a->GetAlignedY()+p->Ry;
					RData.MX=a->GetAlignedX();
					RData.MY=a->GetAlignedY();
					RData.HX=p->Rx;
					RData.HY=p->Ry;
					p->GetExtraData(EData);
					RData.ExtraDataByte	=EData.size();

					if(AreaNames.count()!=0){
						QString	AName;
						int	AreaNameCount=0;
						for(int k=0;k<AreaNames.count();k++){
							if(AreaNames[k].length()!=0){
								AreaNameCount++;
							}
						}
						if(AreaNameCount!=0){
							for(int k=0;k<AreaNames.count();k++){
								AName=AName+AreaNames[k];
								if(k<AreaNames.count()-1){
									AName=AName+QString(/**/",");
								}
							}
						}					
						::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
					}
					else{
						memset(&RData.AreaName,0,sizeof(RData.AreaName));
					}

					if(Item!=NULL){
						RData.LibID	=a->GetAlgorithmItem()->GetLibID();
						RData.UniqueID1	=Item->GetID();
					}
					else{
						RData.LibID	=-1;
						RData.UniqueID1	=-1;
					}

					RData.NGTypeUniqueCode	=-1;	
					if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
						LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
						if(t!=NULL){
							RData.NGTypeUniqueCode	=t->TypeCode;
						}
					}
					RData.ResultValue.ResultDouble	=a->GetResultDouble();
					RData.ResultType	=_ResultDouble;
					DWORD	*dwp=(DWORD	*)RData.Something;
					*dwp	=p->GetResult1();
					*(dwp+1)=p->GetResult2();
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					RData.Layer		=0;
					
					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					if(RData.ExtraDataByte>0){
						if(f->write(EData)!=RData.ExtraDataByte){
							return false;
						}
					}
					WrittenNGCount++;
				}
			}
		}
	}
	return true;
}
//==============================================================================

LineMoveThresholdReq::LineMoveThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	LineMoveThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	LineMoveThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

LineMoveThresholdSend::LineMoveThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;

	SearchDot	=0;
	ThresholdM	=0;
	ThresholdP	=0;
	EdgeWidth	=0;
}

void	LineMoveThresholdSend::ConstructList(LineMoveThresholdReq *reqPacket,MeasureLineMoveBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			MeasureLineMoveItemBase	*BItem=(MeasureLineMoveItemBase *)item;
			const MeasureLineMoveThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			SearchDot	=RThr->SearchDot;
			ThresholdM	=RThr->ThresholdM;
			ThresholdP	=RThr->ThresholdP;
			EdgeWidth	=RThr->EdgeWidth;
		}
	}
}

bool	LineMoveThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdM)==false)
		return false;
	if(::Save(f,ThresholdP)==false)
		return false;
	if(::Save(f,EdgeWidth)==false)
		return false;

	return true;
}
bool	LineMoveThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ThresholdM)==false)
		return false;
	if(::Load(f,ThresholdP)==false)
		return false;
	if(::Load(f,EdgeWidth)==false)
		return false;

	return true;
}

LineMoveReqTryThreshold::LineMoveReqTryThreshold(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	LineMoveReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(ItemLine.Save(f)==false)
		return false;
	if(ItemRxLine.Save(f)==false)
		return false;
	if(ItemArc.Save(f)==false)
		return false;
	if(ItemDistance.Save(f)==false)
		return false;
	return true;
}
bool	LineMoveReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(ItemLine.Load(f,LBase)==false)
		return false;
	if(ItemRxLine.Load(f,LBase)==false)
		return false;
	if(ItemArc.Load(f,LBase)==false)
		return false;
	if(ItemDistance.Load(f,LBase)==false)
		return false;
	return true;
}

LineMoveSendTryThreshold::LineMoveSendTryThreshold(void)
{
	PosDiffX	=0;
	PosDiffY	=0;
	Error		=0;

	DiffR		=0;
	Radius		=0;

	Distance	=0;
	DiffDistance=0;
	RealDistance=0;
	Result	=new ResultInItemPI();
}

LineMoveSendTryThreshold::~LineMoveSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}

bool	LineMoveSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,PosDiffX	)==false)
		return false;
	if(::Save(f,PosDiffY	)==false)
		return false;
	if(::Save(f,Error		)==false)
		return false;
	if(::Save(f,DiffR		)==false)
		return false;
	if(::Save(f,Radius		)==false)
		return false;
	if(::Save(f,Distance	)==false)
		return false;
	if(::Save(f,DiffDistance)==false)
		return false;
	if(::Save(f,RealDistance)==false)
		return false;
	if(Result->Save(f)==false)
		return false;

	return true;
}
bool	LineMoveSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,PosDiffX	)==false)
		return false;
	if(::Load(f,PosDiffY	)==false)
		return false;
	if(::Load(f,Error		)==false)
		return false;
	if(::Load(f,DiffR		)==false)
		return false;
	if(::Load(f,Radius		)==false)
		return false;
	if(::Load(f,Distance	)==false)
		return false;
	if(::Load(f,DiffDistance)==false)
		return false;
	if(::Load(f,RealDistance)==false)
		return false;
	if(Result->Load(f)==false)
		return false;

	return true;
}

void	LineMoveSendTryThreshold::ConstructList(LineMoveReqTryThreshold *reqPacket,MeasureLineMoveBase *Base)
{
	MeasureLineMoveInPage		*BP=(MeasureLineMoveInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		MeasureLineMoveItemBase		*BI=(MeasureLineMoveItemBase *)BP->SearchIDItem(reqPacket->ItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			BI->SetConstructList(reqPacket,this);
		}
	}
}

void	LineMoveSendTryThreshold::Calc(
				 MeasureLineMoveDistanceItem *TargetDistance ,MeasureLineMoveItemBase *TargetLine1,MeasureLineMoveItemBase *TargetLine2
				,MeasureLineMoveDistanceItem *SrcDistance ,MeasureLineMoveItemBase *SrcLine1,MeasureLineMoveItemBase *SrcLine2
				,MeasureLineMoveBase *Base)
{
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
	
	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;

	TargetLine1->SetParent(SrcLine1->GetParent());
	TargetLine1->SetArea(SrcLine1->GetArea());
	TargetLine1->SetVector(*SrcLine1->GetVector());
	TargetLine1->ExecuteInitialAfterEdit	(0,0,Result,DummyEInfo);

	TargetLine1->AVector=SrcLine1->AVector;
	TargetLine1->ExecuteStartByInspection	(0,0,Result);
	TargetLine1->ExecuteProcessing			(0,0,Result);

	Result->GetPosList().RemoveAll();
	TargetLine2->SetParent(SrcLine2->GetParent());
	TargetLine2->SetArea(SrcLine2->GetArea());
	TargetLine2->SetVector(*SrcLine2->GetVector());
	TargetLine2->ExecuteInitialAfterEdit	(0,0,Result,DummyEInfo);

	TargetLine1->AVector=SrcLine2->AVector;
	TargetLine2->ExecuteStartByInspection	(0,0,Result);
	TargetLine2->ExecuteProcessing			(0,0,Result);

	Result->GetPosList().RemoveAll();
	TargetDistance->SetParent(SrcDistance->GetParent());
	TargetDistance->SetArea(SrcDistance->GetArea());
	TargetDistance->SetVector(*SrcDistance->GetVector());
	TargetDistance->ExecuteInitialAfterEdit	(0,0,Result,DummyEInfo);

	TargetDistance->AVector=SrcDistance->AVector;
	TargetDistance->ExecuteStartByInspection	(0,0,Result);
	TargetDistance->ExecuteProcessingLocal		(TargetLine1->GetMeasureCommon(),TargetLine2->GetMeasureCommon(),Result);
}

//==============================================================================

MeasureLineMoveLibraryContainer::MeasureLineMoveLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

MeasureLineMoveLibraryContainer::~MeasureLineMoveLibraryContainer(void)
{
}

//==============================================================================
MeasureLineMoveThreshold::MeasureLineMoveThreshold(AlgorithmItemPI *parent)
:AlgorithmThreshold(parent)
{
	SearchDot	=10;
	ThresholdM	=0;
	ThresholdP	=0;
	EdgeWidth	=10;
	PrevailRight	=false;
	PrevailLeft		=false;
	UsageLayer		=0;
	ModeToSetInInitial	=true;
	OKRangeInInitial	=0;
	OutputType			=0;
	SearchType			=0;
	ThresholdRate		=0.1;

	BrightnessMasterRight	=NULL;
	BrightnessMasterLeft	=NULL;
	BrightnessIdealRight	=0;
	BrightnessIdealLeft		=0;
	BrightnessIdealRightRange	=0;
	BrightnessIdealLeftRange	=0;
}
MeasureLineMoveThreshold::~MeasureLineMoveThreshold(void)
{
	if(BrightnessMasterRight!=NULL){
		delete	[]BrightnessMasterRight;
		BrightnessMasterRight=NULL;
	}
	if(BrightnessMasterLeft!=NULL){
		delete	[]BrightnessMasterLeft;
		BrightnessMasterLeft=NULL;
	}
}
void	MeasureLineMoveThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MeasureLineMoveThreshold *s=(const MeasureLineMoveThreshold *)&src;
	SearchDot			=s->SearchDot;
	ThresholdM			=s->ThresholdM;
	ThresholdP			=s->ThresholdP;
	EdgeWidth			=s->EdgeWidth;
	PrevailRight		=s->PrevailRight;
	PrevailLeft			=s->PrevailLeft;
	UsageLayer			=s->UsageLayer;
	ModeToSetInInitial	=s->ModeToSetInInitial;
	OKRangeInInitial	=s->OKRangeInInitial;
	OutputType			=s->OutputType;
	SearchType			=s->SearchType;
	ThresholdRate		=s->ThresholdRate;
	BrightnessIdealRight=s->BrightnessIdealRight	;
	BrightnessIdealLeft	=s->BrightnessIdealLeft	;
	BrightnessIdealRightRange	=s->BrightnessIdealRightRange	;
	BrightnessIdealLeftRange	=s->BrightnessIdealLeftRange	;
}
bool	MeasureLineMoveThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MeasureLineMoveThreshold *s=(const MeasureLineMoveThreshold *)&src;
	if(SearchDot			!=s->SearchDot				)	return false;
	if(ThresholdM			!=s->ThresholdM				)	return false;
	if(ThresholdP			!=s->ThresholdP				)	return false;
	if(EdgeWidth			!=s->EdgeWidth				)	return false;
	if(PrevailRight			!=s->PrevailRight			)	return false;
	if(PrevailLeft			!=s->PrevailLeft			)	return false;
	if(UsageLayer			!=s->UsageLayer				)	return false;
	if(ModeToSetInInitial	!=s->ModeToSetInInitial		)	return false;
	if(OKRangeInInitial		!=s->OKRangeInInitial		)	return false;
	if(OutputType			!=s->OutputType				)	return false;
	if(SearchType			!=s->SearchType				)	return false;
	if(ThresholdRate		!=s->ThresholdRate			)	return false;
	if(BrightnessIdealRight	!=s->BrightnessIdealRight	)	return false;
	if(BrightnessIdealLeft	!=s->BrightnessIdealLeft	)	return false;
	if(BrightnessIdealRightRange	!=s->BrightnessIdealRightRange	)	return false;
	if(BrightnessIdealLeftRange		!=s->BrightnessIdealLeftRange	)	return false;
	return true;
}
bool	MeasureLineMoveThreshold::Save(QIODevice *f)
{
	WORD	Ver=9;

	if(::Save(f,Ver)==false)
		return(false);

	if(::Save(f,SearchDot)==false)
		return(false);
	if(::Save(f,ThresholdM)==false)
		return(false);
	if(::Save(f,ThresholdP)==false)
		return(false);
	if(::Save(f,EdgeWidth)==false)
		return(false);
	if(::Save(f,PrevailRight)==false)
		return(false);
	if(::Save(f,PrevailLeft)==false)
		return(false);
	if(::Save(f,UsageLayer)==false)
		return(false);
	if(::Save(f,ModeToSetInInitial)==false)
		return(false);
	if(::Save(f,OKRangeInInitial)==false)
		return(false);
	if(::Save(f,OutputType)==false)
		return(false);
	if(::Save(f,SearchType)==false)
		return(false);
	if(::Save(f,BrightnessIdealRight)==false)
		return(false);
	if(::Save(f,BrightnessIdealLeft)==false)
		return(false);
	if(::Save(f,ThresholdRate)==false)
		return(false);
	if(::Save(f,BrightnessIdealRightRange)==false)
		return(false);
	if(::Save(f,BrightnessIdealLeftRange)==false)
		return(false);
	return(true);
}
bool	MeasureLineMoveThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);

	if(::Load(f,SearchDot)==false)
		return(false);
	if(::Load(f,ThresholdM)==false)
		return(false);
	if(::Load(f,ThresholdP)==false)
		return(false);
	if(::Load(f,EdgeWidth)==false)
		return(false);
	if(Ver>=2){
		if(::Load(f,PrevailRight)==false)
			return(false);
		if(::Load(f,PrevailLeft)==false)
			return(false);
	}
	if(Ver>=3){
		if(::Load(f,UsageLayer)==false)
			return(false);
	}
	if(Ver>=4){
		if(::Load(f,ModeToSetInInitial)==false)
			return(false);
		if(::Load(f,OKRangeInInitial)==false)
			return(false);
	}
	if(Ver>=5){
		if(::Load(f,OutputType)==false)
			return(false);
	}
	if(Ver>=6){
		if(::Load(f,SearchType)==false)
			return(false);
	}
	if(Ver>=7){
		if(::Load(f,BrightnessIdealRight)==false)
			return(false);
		if(::Load(f,BrightnessIdealLeft)==false)
			return(false);
	}
	if(Ver>=8){
		if(::Load(f,ThresholdRate)==false)
			return(false);
	}
	if(Ver>=9){
		if(::Load(f,BrightnessIdealRightRange)==false)
			return(false);
		if(::Load(f,BrightnessIdealLeftRange)==false)
			return(false);
	}
	return(true);
}
	
void	MeasureLineMoveThreshold::FromLibrary(AlgorithmLibrary *src)
{
	MeasureLineMoveLibrary	*s=(MeasureLineMoveLibrary *)src;

	SearchDot	=s->SearchDot;
	ThresholdM	=s->ThresholdM;
	ThresholdP	=s->ThresholdP;
	EdgeWidth	=s->EdgeWidth;
	PrevailRight=s->PrevailRight;
	PrevailLeft	=s->PrevailLeft;
	UsageLayer	=s->UsageLayer;
	ModeToSetInInitial	=s->ModeToSetInInitial;
	OKRangeInInitial	=s->OKRangeInInitial;
	OutputType			=s->OutputType;
	SearchType			=s->SearchType;
	ThresholdRate		=s->ThresholdRate;
}
	
void	MeasureLineMoveThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	MeasureLineMoveLibrary	*d=(MeasureLineMoveLibrary *)Dest;

	d->SearchDot	=SearchDot;
	d->ThresholdM	=ThresholdM;
	d->ThresholdP	=ThresholdP;
	d->EdgeWidth	=EdgeWidth;
	d->PrevailRight	=PrevailRight;
	d->PrevailLeft	=PrevailLeft;
	d->UsageLayer	=UsageLayer;
	d->ModeToSetInInitial	=ModeToSetInInitial;
	d->OKRangeInInitial		=OKRangeInInitial;
	d->OutputType			=OutputType;
	d->SearchType			=SearchType;
	d->ThresholdRate		=ThresholdRate;
}

//===========================================
SocketApp::SocketApp(QTcpSocket *p,MeasureLineMoveInPage *parent)
	:sv(p),Parent(parent)
{
	connect(sv,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	SocketApp::SlotReadyRead()
{
	QByteArray	RData=sv->readAll();
	Parent->ReceiveFromTransfer(RData);
}
//===========================================
MeasureLineMoveInPage::MeasureLineMoveInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	PickupBmp		=NULL;
	PickupBmpYLen	=0;
	PickupBmpXByte	=0;
}
MeasureLineMoveInPage::~MeasureLineMoveInPage(void)
{
	ReleasePickupBmpBuff();
}

void	MeasureLineMoveInPage::InitialAfterParamLoaded(void)
{
	MeasureLineMoveBase	*ABase=(MeasureLineMoveBase *)GetParentBase();
	if(ABase!=NULL){
		if(ABase->Receiver==true && ABase->TransferPortNo>0){
			QWidget	*W=GetLayersBase()->GetMainWidget();
			Server.setParent(W);
			connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
			Server.listen(QHostAddress::Any,ABase->TransferPortNo);
		}
		if(ABase->Receiver==false && ABase->TransferPortNo>0){
			connect(&SockSender,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
			connect(&TimerForConnection,SIGNAL(timeout()),this,SLOT(SlotTimer()));
			TimerForConnection.setInterval(2000);
			TimerForConnection.setSingleShot(true);
			TimerForConnection.start();
		}
	}
}

void	MeasureLineMoveInPage::SlotNewConnection()
{
	QTcpSocket *s=Server.nextPendingConnection();
	ServerSock=new SocketApp(s,this);
}
void	MeasureLineMoveInPage::SlotTimer()
{
	if(SockSender.state()!=QAbstractSocket::ConnectedState){
		MeasureLineMoveBase	*ABase=(MeasureLineMoveBase *)GetParentBase();
		if(ABase!=NULL){
			SockSender.connectToHost(ABase->TransferIP,ABase->TransferPortNo);
		}
		TimerForConnection.start();
	}
}
void	MeasureLineMoveInPage::SlotDisconnected()
{
	TimerForConnection.start();
}
void	MeasureLineMoveInPage::TransferTx(QByteArray &TData)
{
	if(SockSender.state()==QAbstractSocket::ConnectedState){
		SockSender.write(TData);
		SockSender.flush();
	}
}

TransferItem	*MeasureLineMoveInPage::FindTransferItem(int64 InspectionID,int ID)
{
	for(TransferPacket *f=TransferPacks.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->InspectionID==InspectionID){
			for(TransferItem *t=f->TransferItems.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->ID==ID){
					return t;
				}
			}
		}
	}
	return NULL;
}

void	MeasureLineMoveInPage::ReceiveFromTransfer(QByteArray &RData)
{
	TransferPacket	*P=new TransferPacket();
	QBuffer	Buff(&RData);
	Buff.open(QIODevice::ReadWrite);
	int64	InspectionID;
	::Load(&Buff,InspectionID);
	P->InspectionID=InspectionID;
	int32	Count;
	::Load(&Buff,Count);

	for(int i=0;i<Count;i++){
		TransferItem	*p=new TransferItem;
		::Load(&Buff,p->ID);
		::Load(&Buff,p->Data);
		P->TransferItems.AppendList(p);
	}

	while(TransferPacks.GetCount()>10){
		TransferPacket	*F=TransferPacks.GetFirst();
		TransferPacks.RemoveList(F);
		delete	F;
	}
	for(TransferPacket *F=TransferPacks.GetFirst();F!=NULL;){
		TransferPacket *NextF=F->GetNext();
		if(F->InspectionID==InspectionID){
			TransferPacks.RemoveList(F);
			delete	F;
		}
		F=NextF;
	}

	TransferPacks.AppendList(P);
}

AlgorithmItemRoot		*MeasureLineMoveInPage::CreateItem(int ItemClassType)
{	
	MeasureLineMoveItemBase	*a=NULL;
	switch(ItemClassType){
		case MeasureLineMove_ItemClass_Line:
			a=new MeasureLineMoveLineItem();	
			break;
		case MeasureLineMove_ItemClass_RxLine:
			a=new MeasureLineMoveRxLineItem();	
			break;
		case MeasureLineMove_ItemClass_CornerR:
			a=new MeasureLineMoveCornerRItem();	
			break;
		case MeasureLineMove_ItemClass_Mark:
			a=new MeasureLineMoveMarkItem();	
			break;
		case MeasureLineMove_ItemClass_Distance:
			a=new MeasureLineMoveDistanceItem();	
			break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}

void	MeasureLineMoveInPage::CreatePickupBmpBuff(void)
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

void	MeasureLineMoveInPage::ReleasePickupBmpBuff(void)
{
	if(PickupBmp!=NULL){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
}

void	MeasureLineMoveInPage::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
}
void	MeasureLineMoveInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen)
{
}

void	MeasureLineMoveInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMeasureLineMoveAreaPacket	*AddMArea=dynamic_cast<AddMeasureLineMoveAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MeasureLineMoveItemBase	*MData=NULL;
		if(AddMArea->ModeLine==true){
			MData=(MeasureLineMoveItemBase *)CreateItem(MeasureLineMove_ItemClass_Line);
		}
		else if(AddMArea->ModeCornerR==true){
			MData=(MeasureLineMoveItemBase *)CreateItem(MeasureLineMove_ItemClass_CornerR);
		}
		else if(AddMArea->ModeDistance==true){
			MData=(MeasureLineMoveItemBase *)CreateItem(MeasureLineMove_ItemClass_Distance);
		}
		MData->SetManualCreated(true);
		AppendItem(MData);
	}
	CmdReqMeasureDataPacket	*CmdReqMeasureDataVar=dynamic_cast<CmdReqMeasureDataPacket *>(packet);
	if(CmdReqMeasureDataVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveCornerRItem	*ar=dynamic_cast<MeasureLineMoveCornerRItem *>(a);
			if(ar!=NULL){
				MeasureDataList	*D=new MeasureDataList();
				D->Page	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				D->Name	=ar->GetItemName();
				D->AlgoType	=/**/"Arc Radius";
				D->Value=ar->RxOnMaster+ar->ResultDifR;
				CmdReqMeasureDataVar->Data.AppendList(D);
			}
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				MeasureDataList	*D=new MeasureDataList();
				D->Page	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				D->Name	=ad->GetItemName();
				D->AlgoType	=/**/"Distance";
				D->Value=ad->GetResultDistance();
				CmdReqMeasureDataVar->Data.AppendList(D);
			}
		}
		return;
	}
	/*
	CmdCreateMaskingPIBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingPIBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLibPacket->XByte ,BmpWithLibPacket->YLen);
		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
					 ,Dst,BmpWithLibPacket->XByte<<3 ,BmpWithLibPacket->YLen);
		BmpWithLibPacket->BmpMap=Dst;
		return;
	}
	*/
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveItemBase	*ai=dynamic_cast<MeasureLineMoveItemBase *>(a);
			if(ai!=NULL){
				LineMoveListForPacket	*d=new LineMoveListForPacket();
				d->ItemID	=ai->GetID();
				d->ItemName	=ai->GetItemName();
				d->LibID	=ai->GetLibID();
				d->Page		=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				if(ai->GetXY(d->x1 ,d->y1 ,d->x2 ,d->y2)==true){
					d->SearchDot=ai->GetThresholdR(GetLayersBase())->SearchDot;
					MakeListPacketVar->ListInfo->AppendList(d);
				}

			}
		}
		return;
	}
	CmdReqMeasureLineMoveIDPacket	*CmdReqMeasureLineMoveIDPacketVar=dynamic_cast<CmdReqMeasureLineMoveIDPacket *>(packet);
	if(CmdReqMeasureLineMoveIDPacketVar!=NULL){
		int	NearBy=20;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureCommon	*ai=dynamic_cast<MeasureCommon *>(a);
			if(ai!=NULL){
				double	Len=ai->GetIsolation(CmdReqMeasureLineMoveIDPacketVar->LocalX ,CmdReqMeasureLineMoveIDPacketVar->LocalY);
				if(Len<NearBy){
					CmdReqMeasureLineMoveIDPacketVar->ItemID=a->GetID();
					break;
				}
			}
		}
		return;
	}
	{
		CmdGenerateMeasure	*CmdGenerateMeasureVar=dynamic_cast<CmdGenerateMeasure *>(packet);
		if(CmdGenerateMeasureVar!=NULL){
			PickupArea.Clear();
			MaskArea.Clear();

			AlgorithmInPageRoot	*MaskPage=GetLayersBase()->GetAlgorithmBase(DefLibTypeMasking)->GetPageData(GetPage());
			if(MaskPage!=NULL){
				CmdGetMaskingAreaInLibraryPacket	MCmd(GetLayersBase());
				MCmd.LibID=CmdGenerateMeasureVar->MaskLib;
				MaskPage->TransmitDirectly(&MCmd);
				if(MCmd.Areas.GetCount()==0){
					PickupBlade( CmdGenerateMeasureVar->BladePickupRL,CmdGenerateMeasureVar->BladePickupRH
								,CmdGenerateMeasureVar->BladePickupGL,CmdGenerateMeasureVar->BladePickupGH
								,CmdGenerateMeasureVar->BladePickupBL,CmdGenerateMeasureVar->BladePickupBH
								,CmdGenerateMeasureVar->BladeLeft	,CmdGenerateMeasureVar->BladeRight
								,PickupArea,MaskArea);
				}
				else{
					ConstMapBufferListContainer MaskMap;
					if(GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
						ConstMapBuffer Map;
						MaskMap.BindOr(Map);
						PureFlexAreaListContainer MaskPack;
						PickupFlexArea(Map.GetBitMap()
									  ,Map.GetXByte()
									  ,GetDotPerLine(),Map.GetYLen() ,MaskPack);
						PureFlexAreaList *MaskMaxF=NULL;
						int	MaskMaxAreaD=0;
						for(PureFlexAreaList *a=MaskPack.GetFirst();a!=NULL;a=a->GetNext()){
							int	d=a->GetPatternByte();
							if(d>MaskMaxAreaD){
								MaskMaxAreaD=d;
								MaskMaxF=a;
							}
						}
						if(MaskMaxF!=NULL){
							MaskArea=*MaskMaxF;
						}
						for(PureFlexAreaList *a=MCmd.Areas.GetFirst();a!=NULL;a=a->GetNext()){
							PickupArea+=*a;
						}
					}
				}
			}
			if(CmdGenerateMeasureVar->OnlyGenerateFilmLen==false){
				if(PickupArea.IsNull()==false){
					MaskHole(PickupArea,CmdGenerateMeasureVar->BladeHoleMinArea,CmdGenerateMeasureVar->BladeHoleErosionDot);
					//RemoveAllDatas();
					for(int i=0;i<CmdGenerateMeasureVar->BladeMeasureData.CountGenDatas;i++){
						AddMeasureItems(PickupArea,MaskArea
										,CmdGenerateMeasureVar->BladeMeasureData.GenDatas[i]
										,CmdGenerateMeasureVar->LineLib,CmdGenerateMeasureVar->DistanceLib
											,i,i);
					}
					for(int i=0;i<CmdGenerateMeasureVar->FilmMeasureData.CountGenDatas;i++){
						AddFilmMeasureItems(PickupArea,MaskArea
										,CmdGenerateMeasureVar->FilmMeasureData.GenDatas[i]
										,CmdGenerateMeasureVar->LineLib,CmdGenerateMeasureVar->RxLineLib,CmdGenerateMeasureVar->DistanceLib
											,1000+i,100+i);
					}
					if(CmdGenerateMeasureVar->FilmMeasureData.CountGenDatas==0){
						for(int i=0;i<10;i++){
							RemoveFilmMeasure(100+i);
						}
					}
				}
			}
			else{
				if(PickupArea.IsNull()==false){
					for(int i=0;i<CmdGenerateMeasureVar->FilmMeasureData.CountGenDatas;i++){
						AddFilmMeasureItems(PickupArea,MaskArea
										,CmdGenerateMeasureVar->FilmMeasureData.GenDatas[i]
										,CmdGenerateMeasureVar->LineLib,CmdGenerateMeasureVar->RxLineLib,CmdGenerateMeasureVar->DistanceLib
											,1000+i,100+i);
					}
					if(CmdGenerateMeasureVar->FilmMeasureData.CountGenDatas==0){
						for(int i=0;i<10;i++){
							RemoveFilmMeasure(100+i);
						}
					}
				}
			}
			return;
		}
	}
	{
		CmdReqCorrentValues	*CmdReqCorrentValuesVar=dynamic_cast<CmdReqCorrentValues *>(packet);
		if(CmdReqCorrentValuesVar!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
				if(ad!=NULL){
					int	n=ad->GetID();
					if(n<CmdReqCorrentValuesVar->BladeMeasureData.CountGenDatas){
						double	X1,Y1,X2,Y2;
						double	Len;
						if(CmdReqCorrentValuesVar->Mastered==true)
							Len=ad->GetDistanceInMaster(X1,Y1,X2,Y2);
						else
							Len=ad->ResultLen;
						if(CmdReqCorrentValuesVar->BladeMeasureData.GenDatas[n].bHorizontal==true)
							CmdReqCorrentValuesVar->BladeMeasureData.GenDatas[n].CorrectLength=Len*GetParamGlobal()->ResolutionXNano/1000000.0;
						else
							CmdReqCorrentValuesVar->BladeMeasureData.GenDatas[n].CorrectLength=Len*GetParamGlobal()->ResolutionYNano/1000000.0;
					}
				}
			}
			return;
		}
	}
	{
		CmdSetCorrectValues	*CmdSetCorrectValuesVar=dynamic_cast<CmdSetCorrectValues *>(packet);
		if(CmdSetCorrectValuesVar!=NULL){
			if(PickupArea.IsNull()==true){
				CmdGetMaskingAreaInLibraryPacket	MCmd(GetLayersBase());
				MCmd.LibID=CmdSetCorrectValuesVar->MaskLib;
				AlgorithmInPageRoot	*MaskPage=GetLayersBase()->GetAlgorithmBase(DefLibTypeMasking)->GetPageData(GetPage());
				MaskPage->TransmitDirectly(&MCmd);
				if(MCmd.Areas.GetCount()==0){
					PickupBlade( CmdSetCorrectValuesVar->BladePickupRL,CmdSetCorrectValuesVar->BladePickupRH
								,CmdSetCorrectValuesVar->BladePickupGL,CmdSetCorrectValuesVar->BladePickupGH
								,CmdSetCorrectValuesVar->BladePickupBL,CmdSetCorrectValuesVar->BladePickupBH
								,0,GetDotPerLine()
								,PickupArea,MaskArea);
				}
			}
			if(PickupArea.IsNull()==false){
				//RemoveAllDatas();
				for(int i=0;i<CmdSetCorrectValuesVar->BladeMeasureData.CountGenDatas;i++){
					AddMeasureItems(PickupArea,MaskArea
									,CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[i]
									,CmdSetCorrectValuesVar->LineLib
									,CmdSetCorrectValuesVar->DistanceLib
									,i,i);
				}
			}
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
				if(ad!=NULL){
					int	n=ad->GetID();
					if(n<CmdSetCorrectValuesVar->BladeMeasureData.CountGenDatas){
						if(CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].bHorizontal==true){
							double	MasterLen=CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].CorrectLength/GetParamGlobal()->ResolutionXNano*1000000.0;
							ad->GetThresholdW()->ThresholdM=MasterLen-CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0/2;
							ad->GetThresholdW()->ThresholdP=MasterLen+CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0/2;
							ad->GetThresholdW()->ModeToSetInInitial=false;
						}
						else{
							double	MasterLen=CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].CorrectLength/GetParamGlobal()->ResolutionYNano*1000000.0;
							ad->GetThresholdW()->ThresholdM=MasterLen-CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
							ad->GetThresholdW()->ThresholdP=MasterLen+CmdSetCorrectValuesVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
							ad->GetThresholdW()->ModeToSetInInitial=false;
						}
					}
				}
			}

			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			if(Res!=NULL){
				ResultBaseForAlgorithmRoot *r=Res->GetResultBaseForAlgorithm(GetParentBase());
				if(r!=NULL){
					ExecuteInitialAfterEditInfo DummyEInfo;
					DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;

					GetParentBase()->ExecuteInitialAfterEdit	(0 ,r,DummyEInfo);
					GetParentBase()->ExecutePreProcessing		(0 ,r);
					GetParentBase()->ExecuteProcessing			(0 ,r);
				}
			}
			return;
		}
	}
	{
		CmdSetOnlyBladeThreshold	*CmdSetOnlyBladeThresholdVar=dynamic_cast<CmdSetOnlyBladeThreshold *>(packet);
		if(CmdSetOnlyBladeThresholdVar!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
				if(ad!=NULL){
					if(ad->MeasurePointNo<100){
						int	n=ad->GetID();
						if(n<CmdSetOnlyBladeThresholdVar->BladeMeasureData.CountGenDatas){
							if(CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].bHorizontal==true){
								double	MasterLen=CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].CorrectLength/GetParamGlobal()->ResolutionXNano*1000000.0;
								ad->GetThresholdW()->ThresholdM=MasterLen-CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0/2;
								ad->GetThresholdW()->ThresholdP=MasterLen+CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0/2;
								ad->GetThresholdW()->ModeToSetInInitial=false;
							}
							else{
								double	MasterLen=CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].CorrectLength/GetParamGlobal()->ResolutionYNano*1000000.0;
								ad->GetThresholdW()->ThresholdM=MasterLen-CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
								ad->GetThresholdW()->ThresholdP=MasterLen+CmdSetOnlyBladeThresholdVar->BladeMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
								ad->GetThresholdW()->ModeToSetInInitial=false;
							}
						}
					}
					else
					if(ad->MeasurePointNo<200){
						int	n=ad->MeasurePointNo-100;
						if(0<=n && n<CmdSetOnlyBladeThresholdVar->FilmMeasureData.CountGenDatas){
							double	MasterLen=CmdSetOnlyBladeThresholdVar->FilmMeasureData.GenDatas[n].CorrectLength/GetParamGlobal()->ResolutionYNano*1000000.0;
							ad->GetThresholdW()->ThresholdM=MasterLen-CmdSetOnlyBladeThresholdVar->FilmMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
							ad->GetThresholdW()->ThresholdP=MasterLen+CmdSetOnlyBladeThresholdVar->FilmMeasureData.GenDatas[n].OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0/2;
							ad->GetThresholdW()->ModeToSetInInitial=false;
						}
					}
				}
			}
			SaveMasterData();
			return;
		}
	}
	{
		CmdSetMeasureEndPoint	*CmdSetMeasureEndPointVar=dynamic_cast<CmdSetMeasureEndPoint *>(packet);
		if(CmdSetMeasureEndPointVar!=NULL){
			MeasureLineMoveDistanceItem	*D=NULL;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
				if(ad!=NULL){
					if(ad->MeasurePointNo==CmdSetMeasureEndPointVar->MeasureNo){
						D=ad;
						break;
					}
				}
			}
			if(D==NULL){
				int	n=0;
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
					if(ad!=NULL){
						if(n==CmdSetMeasureEndPointVar->MeasureNo){
							D=ad;
							break;
						}
					}
					n++;
				}
			}
			if(D!=NULL){
				D->SetEndPoint(CmdSetMeasureEndPointVar->EndNo,CmdSetMeasureEndPointVar->X,CmdSetMeasureEndPointVar->Y);
			}
			return;
		}
	}
	CmdReqDistancePacket	*CmdReqDistancePacketVar=dynamic_cast<CmdReqDistancePacket *>(packet);
	if(CmdReqDistancePacketVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				const MeasureLineMoveThreshold	*RThr=ad->GetThresholdR();
				MeasureDistanceItemInfo	*Info=new MeasureDistanceItemInfo();
				Info->Data.Phase		=GetPhaseCode();
				Info->Data.Page			=GetPage();
				Info->Data.ItemID		=ad->GetID();
				Info->Data.MeasureNo	=ad->MeasurePointNo;
				Info->Data.OKLengthL	=RThr->ThresholdM;
				Info->Data.OKLengthH	=RThr->ThresholdP;
				Info->Data.CurrentValue	=ad->GetResultDistance();
				if(Info->Data.CurrentValue==0.0){
					double	X1,Y1,X2,Y2;
					Info->Data.CurrentValue	=ad->GetDistanceInMaster(X1,Y1,X2,Y2);
				}
				Info->Data.OKLengthLUnit	=ad->TrasnformUnitFromPixel(Info->Data.OKLengthL);
				Info->Data.OKLengthHUnit	=ad->TrasnformUnitFromPixel(Info->Data.OKLengthH);
				Info->Data.CurrentValueUnit	=ad->TrasnformUnitFromPixel(Info->Data.CurrentValue);

				CmdReqDistancePacketVar->DataList.AppendList(Info);
			}
		}
		return;
	}
	CmdSetDistanceCorrectValue	*CmdSetDistanceCorrectValueVar=dynamic_cast<CmdSetDistanceCorrectValue *>(packet);
	if(CmdSetDistanceCorrectValueVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdSetDistanceCorrectValueVar->ItemID);
		MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
		if(ad!=NULL){
			MeasureLineMoveThreshold	*WThr=ad->GetThresholdW();
			WThr->ThresholdM	=ad->TransformPixelFromUnit(CmdSetDistanceCorrectValueVar->OKLengthLUnit);
			WThr->ThresholdP	=ad->TransformPixelFromUnit(CmdSetDistanceCorrectValueVar->OKLengthHUnit);
		}
		return;
	}
	CmdAddDistance	*CmdAddDistanceVar=dynamic_cast<CmdAddDistance *>(packet);
	if(CmdAddDistanceVar!=NULL){
		MeasureLineMoveLineItem	*MLine1=NULL;
		MeasureLineMoveLineItem	*MLine2=NULL;
		MeasureLineMoveDistanceItem	*MDistance=NULL;

		MLine1		=(MeasureLineMoveLineItem *)CreateItem(MeasureLineMove_ItemClass_Line);
		MLine2		=(MeasureLineMoveLineItem *)CreateItem(MeasureLineMove_ItemClass_Line);
		MDistance	=(MeasureLineMoveDistanceItem *)CreateItem(MeasureLineMove_ItemClass_Distance);

		MLine1	 ->SetManualCreated(true);
		MLine2	 ->SetManualCreated(true);
		MDistance->SetManualCreated(true);

		AppendItem(MLine1);
		AppendItem(MLine2);
		AppendItem(MDistance);

		MDistance->LineType1=1;
		MDistance->LineID1	=MLine1->GetID();
		MDistance->LineType2=1;
		MDistance->LineID2	=MLine2->GetID();

		double	Dx=CmdAddDistanceVar->X2-CmdAddDistanceVar->X1;
		double	Dy=CmdAddDistanceVar->Y2-CmdAddDistanceVar->Y1;
		double	Len=hypot(Dx,Dy);
		if(Len>0){
			double	Vx= Dy/Len;
			double	Vy=-Dx/Len;

			VectorLineDouble	*L1Line=new VectorLineDouble();
			L1Line->AppendItemBase(new VectorItemDouble( CmdAddDistanceVar->X1-Vx*CmdAddDistanceVar->LineLength/2
														,CmdAddDistanceVar->Y1-Vy*CmdAddDistanceVar->LineLength/2));
			L1Line->AppendItemBase(new VectorItemDouble( CmdAddDistanceVar->X1+Vx*CmdAddDistanceVar->LineLength/2
														,CmdAddDistanceVar->Y1+Vy*CmdAddDistanceVar->LineLength/2));
			MLine1->SetVector(L1Line);
			MLine1->SetLibID(CmdAddDistanceVar->LineLibID1);
			MLine1->SetLocalData(this);
			{
				AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
				if(GetLibraryContainer()->GetLibrary(CmdAddDistanceVar->LineLibID1,Lib)==true){
					Lib.GetLibrary(GetLayersBase()->GetThresholdLevelID());
					MLine1->CopyThresholdFromLibrary(&Lib);
				}
			}

			VectorLineDouble	*L2Line=new VectorLineDouble();
			L2Line->AppendItemBase(new VectorItemDouble( CmdAddDistanceVar->X2-Vx*CmdAddDistanceVar->LineLength/2
														,CmdAddDistanceVar->Y2-Vy*CmdAddDistanceVar->LineLength/2));
			L2Line->AppendItemBase(new VectorItemDouble( CmdAddDistanceVar->X2+Vx*CmdAddDistanceVar->LineLength/2
														,CmdAddDistanceVar->Y2+Vy*CmdAddDistanceVar->LineLength/2));
			MLine2->SetVector(L2Line);
			MLine2->SetLibID(CmdAddDistanceVar->LineLibID2);
			MLine2->SetLocalData(this);
			{
				AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
				if(GetLibraryContainer()->GetLibrary(CmdAddDistanceVar->LineLibID2,Lib)==true){
					Lib.GetLibrary(GetLayersBase()->GetThresholdLevelID());
					MLine2->CopyThresholdFromLibrary(&Lib);
				}
			}

			MDistance->MeasurePointNo	=GetMaxItemID()+1;
			MDistance->NoCalc=true;
			MDistance->Line1InGlobalPage=GetPage();
			MDistance->Line2InGlobalPage=GetPage();
			MDistance->DrawPoint1=0.5;
			MDistance->DrawPoint2=0.5;
			MDistance->DifLen	=0;
			MDistance->ResultLen=0;
			VectorLineDouble	*LDLine=new VectorLineDouble();
			LDLine->AppendItemBase(new VectorItemDouble(CmdAddDistanceVar->X1,CmdAddDistanceVar->Y1));
			LDLine->AppendItemBase(new VectorItemDouble(CmdAddDistanceVar->X2,CmdAddDistanceVar->Y2));
			MDistance->SetVector(LDLine);
			MDistance->SetLibID(CmdAddDistanceVar->DistanceLibID);
			MDistance->SetLocalData(this);
			{
				AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
				if(GetLibraryContainer()->GetLibrary(CmdAddDistanceVar->DistanceLibID,Lib)==true){
					Lib.GetLibrary(GetLayersBase()->GetThresholdLevelID());
					MDistance->CopyThresholdFromLibrary(&Lib);
				}
			}

			MDistance->GetThresholdW()->OKRangeInInitial	=20;
			//MDistance->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			//MDistance->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			MDistance->GetThresholdW()->ModeToSetInInitial=false;
		}
		return;
	}
	CmdDeleteMeasureDistance	*CmdDeleteMeasureDistanceVar=dynamic_cast<CmdDeleteMeasureDistance *>(packet);
	if(CmdDeleteMeasureDistanceVar!=NULL){
		MeasureLineMoveDistanceItem	*D=NULL;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				if(ad->MeasurePointNo==CmdDeleteMeasureDistanceVar->MeasureNo){
					D=ad;
					break;
				}
			}
		}
		AlgorithmItemPointerListContainer items;
		if(D!=NULL){
			AlgorithmItemRoot	*p1=SearchIDItem(D->LineID1);
			if(p1!=NULL){
				items.Add(p1);
			}
			AlgorithmItemRoot	*p2=SearchIDItem(D->LineID2);
			if(p2!=NULL){
				items.Add(p2);
			}
			items.Add(D);
			RemoveItems(items);
		}
		return;
	}
	CmdReqMeasureLineInfo	*CmdReqMeasureLineInfoVar=dynamic_cast<CmdReqMeasureLineInfo *>(packet);
	if(CmdReqMeasureLineInfoVar!=NULL){
		MeasureLineMoveDistanceItem	*D=NULL;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				if(ad->MeasurePointNo==CmdReqMeasureLineInfoVar->MeasureNo){
					D=ad;
					break;
				}
			}
		}
		if(D!=NULL){
			AlgorithmItemRoot	*p=NULL;
			if(CmdReqMeasureLineInfoVar->EndNo==0){
				p=SearchIDItem(D->LineID1);
			}
			else{
				p=SearchIDItem(D->LineID2);
			}
			if(p!=NULL){
				const MeasureLineMoveThreshold	*Thr=((MeasureLineMoveItemBase *)p)->GetThresholdR();
				CmdReqMeasureLineInfoVar->SearchDot=Thr->SearchDot;
			}
		}
		return;
	}
	CmdSetMeasureLineInfo	*CmdSetMeasureLineInfoVar=dynamic_cast<CmdSetMeasureLineInfo *>(packet);
	if(CmdSetMeasureLineInfoVar!=NULL){
		MeasureLineMoveDistanceItem	*D=NULL;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				if(ad->MeasurePointNo==CmdSetMeasureLineInfoVar->MeasureNo){
					D=ad;
					break;
				}
			}
		}
		if(D!=NULL){
			AlgorithmItemRoot	*p=NULL;
			if(CmdSetMeasureLineInfoVar->EndNo==0){
				p=SearchIDItem(D->LineID1);
			}
			else{
				p=SearchIDItem(D->LineID2);
			}
			if(p!=NULL){
				MeasureLineMoveThreshold	*Thr=((MeasureLineMoveItemBase *)p)->GetThresholdW();
				Thr->SearchDot=CmdSetMeasureLineInfoVar->SearchDot;
			}
		}
		return;
	}
	CmdSetMeasureLineInfoAll	*CmdSetMeasureLineInfoAllVar=dynamic_cast<CmdSetMeasureLineInfoAll *>(packet);
	if(CmdSetMeasureLineInfoAllVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveLineItem	*ad=dynamic_cast<MeasureLineMoveLineItem *>(a);
			if(ad!=NULL){
				MeasureLineMoveThreshold	*Thr=((MeasureLineMoveItemBase *)a)->GetThresholdW();
				Thr->SearchDot=CmdSetMeasureLineInfoAllVar->SearchDot;
			}
			MeasureLineMoveCornerRItem	*ae=dynamic_cast<MeasureLineMoveCornerRItem *>(a);
			if(ae!=NULL){
				MeasureLineMoveThreshold	*Thr=((MeasureLineMoveItemBase *)a)->GetThresholdW();
				Thr->SearchDot=CmdSetMeasureLineInfoAllVar->SearchDot;
			}
		}
		return;
	}
	CmdReqMeasureLinePosition	*CmdReqMeasureLinePositionVar=dynamic_cast<CmdReqMeasureLinePosition *>(packet);
	if(CmdReqMeasureLinePositionVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL && ad->GetID()==CmdReqMeasureLinePositionVar->DistanceItemID){
				MeasureCommon	*p1=ad->GetFirstPointOnMaster();
				if(p1!=NULL){
					double x ,y;
					p1->GetDrawPoint(ad->DrawPoint1 ,x ,y);
					CmdReqMeasureLinePositionVar->RetPos1X=x;
					CmdReqMeasureLinePositionVar->RetPos1Y=y;
				}
				MeasureCommon	*p2=ad->GetSecondPointOnMaster();
				if(p2!=NULL){
					double x ,y;
					p2->GetDrawPoint(ad->DrawPoint2 ,x ,y);
					CmdReqMeasureLinePositionVar->RetPos2X=x;
					CmdReqMeasureLinePositionVar->RetPos2Y=y;
				}
				break;
			}
		}
		return;
	}
	CmdReqChangeMeasureLineMoveEndPoint	*CmdReqChangeMeasureLineMoveEndPointVar=dynamic_cast<CmdReqChangeMeasureLineMoveEndPoint *>(packet);
	if(CmdReqChangeMeasureLineMoveEndPointVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL && ad->GetID()==CmdReqChangeMeasureLineMoveEndPointVar->ItemID){
				if(CmdReqChangeMeasureLineMoveEndPointVar->Point1==true){
					ad->SetEndPoint(0,CmdReqChangeMeasureLineMoveEndPointVar->LocalX ,CmdReqChangeMeasureLineMoveEndPointVar->LocalY);
				}
				if(CmdReqChangeMeasureLineMoveEndPointVar->Point2==true){
					ad->SetEndPoint(1,CmdReqChangeMeasureLineMoveEndPointVar->LocalX ,CmdReqChangeMeasureLineMoveEndPointVar->LocalY);
				}
			}
		}
		return;
	}
}

void	MeasureLineMoveInPage::PickupBlade(  int BladePickupRL,int BladePickupRH
											,int BladePickupGL,int BladePickupGH
											,int BladePickupBL,int BladePickupBH
											,int X1, int X2
											,FlexArea &BladeArea
											,FlexArea &MaskArea)
{
	CreatePickupBmpBuff();
	MakeBMap(PickupBmp ,PickupBmpXByte,GetDotPerLine(),PickupBmpYLen
			,BladePickupRL
			,BladePickupRH
			,BladePickupGL
			,BladePickupGH
			,BladePickupBL
			,BladePickupBH
			,X1,X2);
			
	PureFlexAreaListContainer FPack;
	PickupFlexArea(PickupBmp,PickupBmpXByte,GetDotPerLine(),PickupBmpYLen ,FPack);

	PureFlexAreaList *MaxF=NULL;
	int	MaxAreaD=0;
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		int	d=a->GetPatternByte();
		if(d>MaxAreaD){
			MaxAreaD=d;
			MaxF=a;
		}
	}
	if(MaxF!=NULL){
		BladeArea=*MaxF;
	}
	//DeleteMatrixBuff(PickupBmp,PickupBmpYLen);

	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		PureFlexAreaListContainer MaskPack;
		::PickupFlexArea(Map.GetBitMap(),PickupBmpXByte,GetDotPerLine(),PickupBmpYLen ,MaskPack);
		PureFlexAreaList *MaskMaxF=NULL;
		int	MaskMaxAreaD=0;
		for(PureFlexAreaList *a=MaskPack.GetFirst();a!=NULL;a=a->GetNext()){
			int	d=a->GetPatternByte();
			if(d>MaskMaxAreaD){
				MaskMaxAreaD=d;
				MaskMaxF=a;
			}
		}
		if(MaskMaxF!=NULL){
			MaskArea=*MaskMaxF;
		}
	}
}
	
void	MeasureLineMoveInPage::MaskHole(FlexArea &PickupArea
										,int BladeHoleMinArea
										,int BladeHoleErosionDot)
{
	int	x1,y1,x2,y2;
	PickupArea.GetXY(x1,y1,x2,y2);
	int	Lx1=max(0,x1-32);
	int	Ly1=max(0,y1-32);
	int	Lx2=min(x2+32,GetDotPerLine());
	int	Ly2=min(y2+32,GetMaxLines());

	int	LYLen=Ly2-Ly1;
	int	LXLen=Lx2-Lx1;
	int	LXByte	=(LXLen+7)/8;
	BYTE	**TmpMap=MakeMatrixBuff(LXByte,LYLen);
	BYTE	**TmpMap2=MakeMatrixBuff(LXByte,LYLen);
	MatrixBuffClear	(TmpMap ,0,LXByte,LYLen);
	PickupArea.MakeBitData(TmpMap
                       ,-Lx1 ,-Ly1
                       ,LXLen, LYLen);
	MatrixBuffNot	(TmpMap ,LXByte,LYLen);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpMap ,LXByte ,LXLen,LYLen ,FPack);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
		PureFlexAreaList *NextF=f->GetNext();
		if(f->GetPatternByte()<BladeHoleMinArea){
			FPack.RemoveList(f);
		}
		f=NextF;
	}
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->IsInclude(16,16)==true){
			FPack.RemoveList(f);
			break;
		}
	}
	MatrixBuffClear	(TmpMap ,0,LXByte,LYLen);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MakeBitData(TmpMap,LXLen, LYLen);
	}
	GetLayersBase()->FatAreaN(TmpMap,TmpMap2,LXByte,LYLen,BladeHoleErosionDot);
	PureFlexAreaListContainer GPack;
	PickupFlexArea(TmpMap ,LXByte ,LXLen,LYLen ,GPack);
	for(PureFlexAreaList *f=GPack.GetFirst();f!=NULL;f=f->GetNext()){
		f->MoveToNoClip(Lx1,Ly1);
		PickupArea.Sub(*f,0,0);
	}
	DeleteMatrixBuff(TmpMap ,LYLen);
	DeleteMatrixBuff(TmpMap2,LYLen);
}

ExeResult	MeasureLineMoveInPage::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	AddMonoFilmMeasureItems();

	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);


	Items1.RemoveAll();
	Items2.RemoveAll();
	Items3.RemoveAll();
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		MeasureLineMoveItemBase	*Item=dynamic_cast<MeasureLineMoveItemBase *>(a);
		if(Item->GetItemClassType()!=MeasureLineMove_ItemClass_Distance){
			if(Item->GetItemClassType()!=MeasureLineMove_ItemClass_RxLine)
				Items1.Add(Item);
			else{
				Items2.Add(Item);
			}
		}
		else{
			Items3.Add(Item);
		}
	}
	return Ret;
}

ExeResult	MeasureLineMoveInPage::ExecuteProcessing	(int ExeID ,ResultInPageRoot *R)
{
	//DotColorMatchingBase	*ABase=dynamic_cast<DotColorMatchingBase *>(GetParentBase());

	if(GetParamGlobal()->CalcSingleThread==false){
		AlgorithmItemPointerList *a;
		#pragma omp parallel
		{
			if(Items1.GetCount()!=0){
				#pragma omp single private(a)
				for(a=Items1.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
					}
				}
			}
			if(Items2.GetCount()!=0){
				#pragma omp single private(a)
				for(a=Items2.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						if(GetNGCounter()<=Parent->GetParamGlobal()->MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
						}
					}
				}
			}
			if(Items3.GetCount()!=0){
				#pragma omp single private(a)
				for(a=Items3.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						if(GetNGCounter()<=Parent->GetParamGlobal()->MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
						}
					}
				}
			}
		}
	}
	else{
		AlgorithmItemPointerList *a;
		for(a=Items1.GetFirst();a!=NULL;a=a->GetNext()){
			a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
		}
		for(a=Items2.GetFirst();a!=NULL;a=a->GetNext()){
			a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
		}
		for(a=Items3.GetFirst();a!=NULL;a=a->GetNext()){
			if(GetNGCounter()<=Parent->GetParamGlobal()->MaxNGCountsPerCam){
				a->GetItem()->ExecuteProcessing	(ExeID ,0,a->GetItem()->GetCurrentResult());
			}
		}
	}
	int32	TxCount=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		MeasureLineMoveDistanceItem	*p=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
		if(p!=NULL && p->TransferInfo>=0){
			TxCount++;
		}
	}
	if(TxCount!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int64	InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		::Save(&Buff,InspectionID);
		::Save(&Buff,TxCount);
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*p=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(p!=NULL && p->TransferInfo>=0){
				::Save(&Buff,p->TransferInfo);
				QBuffer	TmpBuff;
				TmpBuff.open(QIODevice::ReadWrite);
				p->MakeDataToTransfer(&TmpBuff);
				::Save(&Buff,TmpBuff.buffer());
			}
		}
		TransferTx(Buff.buffer());
	}

	return _ER_true;
}

MeasureLineMoveDistanceItem	*MeasureLineMoveInPage::SearchDistanceItem(int MeasurePointNo)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		MeasureLineMoveDistanceItem	*p=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
		if(p!=NULL){
			if(p->MeasurePointNo==MeasurePointNo){
				return p;
			}
		}
	}
	return NULL;
}

bool	MeasureLineMoveInPage::AddMeasureItems(FlexArea &BladeArea,FlexArea &MaskArea
												,struct MeasureHVInfo	&GenData
												,int LineLib,int DistanceLib
												,int BaseItemID
												,int MeasurePointNo)
{
	//ImageBuffer *MasterImageList[100];
	//GetMasterBuffList(MasterImageList);	
	MeasureLineMoveLineItem	*L1=NULL;
	MeasureLineMoveLineItem	*L2=NULL;
	MeasureLineMoveDistanceItem	*LD=NULL;

	MeasureLineMoveDistanceItem	*CurrentLD=SearchDistanceItem(MeasurePointNo);
	int	CurrentDistanceID=-1;
	if(CurrentLD!=NULL){
		CurrentDistanceID=CurrentLD->GetID();
		if(CurrentLD->GenData.bOnlyInside	==GenData.bOnlyInside	
		&& CurrentLD->GenData.bHorizontal	==GenData.bHorizontal
		&& CurrentLD->GenData.bFrom0		==GenData.bFrom0
		&& CurrentLD->GenData.bPartnerFrom0	==GenData.bPartnerFrom0
		&& CurrentLD->GenData.PartnerPos	==GenData.PartnerPos	
		&& CurrentLD->GenData.RegLineLength	==GenData.RegLineLength){
			if(GenData.CorrectLength!=0.0){
				CurrentLD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				CurrentLD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				CurrentLD->GetThresholdW()->ModeToSetInInitial=false;
			}
			return true;
		}
		AlgorithmItemRoot	*L1=SearchIDItem(CurrentLD->LineID1);
		AlgorithmItemRoot	*L2=SearchIDItem(CurrentLD->LineID2);
		AlgorithmItemPointerListContainer Items;
		Items.Add(CurrentLD);
		if(L1!=NULL)
			Items.Add(L1);
		if(L2!=NULL)
			Items.Add(L2);
		RemoveItems(Items);
	}

	if(GenData.bOnlyInside==false && GenData.bHorizontal==true && GenData.bFrom0==true && GenData.bPartnerFrom0==true){
		int	YPos=BladeArea.GetMinY()+GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x2=BladeArea.GetFLineLeftX(BIndexStart);

		int MIndexStart ,MIndexEnd;
		int	nM=MaskArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x1=MaskArea.GetFLineLeftX(MIndexStart);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==true && GenData.bFrom0==true && GenData.bPartnerFrom0==false){
		int	YPos=BladeArea.GetMaxY()-GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x2=BladeArea.GetFLineLeftX(BIndexStart);

		int MIndexStart ,MIndexEnd;
		int	nM=MaskArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x1=MaskArea.GetFLineLeftX(MIndexStart);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==true && GenData.bFrom0==false && GenData.bPartnerFrom0==true){
		int	YPos=BladeArea.GetMinY()+GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x1=BladeArea.GetFLineRightX(BIndexEnd);

		int MIndexStart ,MIndexEnd;
		int	nM=MaskArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x2=MaskArea.GetFLineRightX(MIndexEnd);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}

		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==true && GenData.bFrom0==false && GenData.bPartnerFrom0==false){
		int	YPos=BladeArea.GetMaxY()-GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x1=BladeArea.GetFLineRightX(BIndexEnd);

		int MIndexStart ,MIndexEnd;
		int	nM=MaskArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x2=MaskArea.GetFLineRightX(MIndexEnd);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}

		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==false && GenData.bFrom0==true && GenData.bPartnerFrom0==true){
		int	XPos=BladeArea.GetMinX()+GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y2=BMinY;

		int	MMinY,MMaxY;
		bool	nM=FindY(MaskArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y1=MMinY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==false && GenData.bFrom0==true && GenData.bPartnerFrom0==false){
		int	XPos=BladeArea.GetMaxX()-GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y2=BMinY;

		int	MMinY,MMaxY;
		bool	nM=FindY(MaskArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y1=MMinY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==false && GenData.bFrom0==false && GenData.bPartnerFrom0==true){
		int	XPos=BladeArea.GetMinX()+GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y1=BMaxY;

		int	MMinY,MMaxY;
		bool	nM=FindY(MaskArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y2=MMaxY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==false && GenData.bHorizontal==false && GenData.bFrom0==false && GenData.bPartnerFrom0==false){
		int	XPos=BladeArea.GetMaxX()-GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y1=BMaxY;

		int	MMinY,MMaxY;
		bool	nM=FindY(MaskArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y2=MMaxY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==true && GenData.bHorizontal==true && GenData.bPartnerFrom0==true){
		int	YPos=BladeArea.GetMinY()+GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x1=BladeArea.GetFLineLeftX(BIndexStart);

		int MIndexStart ,MIndexEnd;
		int	nM=BladeArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x2=BladeArea.GetFLineRightX(MIndexStart);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==true && GenData.bHorizontal==true && GenData.bPartnerFrom0==false){
		int	YPos=BladeArea.GetMaxY()-GenData.PartnerPos/GetParamGlobal()->ResolutionYNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	nB=BladeArea.FindIndex(YPos,BIndexStart ,BIndexEnd);
		if(nB<=0)
			return false;
		int	x1=BladeArea.GetFLineLeftX(BIndexEnd);

		int MIndexStart ,MIndexEnd;
		int	nM=BladeArea.FindIndex(YPos,MIndexStart ,MIndexEnd);
		if(nM<=0)
			return false;
		int	x2=BladeArea.GetFLineRightX(MIndexEnd);

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1Line->AppendItemBase(new VectorItemDouble(x1,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2Line->AppendItemBase(new VectorItemDouble(x2,YPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(x1,YPos));
		LDLine->AppendItemBase(new VectorItemDouble(x2,YPos));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}

		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==true && GenData.bHorizontal==false && GenData.bPartnerFrom0==true){
		int	XPos=BladeArea.GetMinX()+GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y2=BMaxY;

		int	MMinY,MMaxY;
		bool	nM=FindY(BladeArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y1=MMinY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}
	else
	if(GenData.bOnlyInside==true && GenData.bHorizontal==false && GenData.bPartnerFrom0==false){
		int	XPos=BladeArea.GetMaxX()-GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
		int BIndexStart ,BIndexEnd;
		int	BMinY,BMaxY;
		bool	nB=FindY(BladeArea,XPos,BMinY,BMaxY);
		if(nB==false)
			return false;
		int	y2=BMaxY;

		int	MMinY,MMaxY;
		bool	nM=FindY(BladeArea,XPos,MMinY,MMaxY);
		if(nM==false)
			return false;
		int	y1=MMinY;

		L1=new MeasureLineMoveLineItem();
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y1));
		L1->SetVector(L1Line);
		L1->SetLibID(LineLib);
		L1->SetLocalData(this);
		AppendItem(L1);

		L2=new MeasureLineMoveLineItem();
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(XPos-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2Line->AppendItemBase(new VectorItemDouble(XPos+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,y2));
		L2->SetVector(L2Line);
		L2->SetLibID(LineLib);
		L2->SetLocalData(this);
		AppendItem(L2);
		if(L1!=NULL){
			L1->SetID(BaseItemID+100);
		}
		if(L2!=NULL){
			L2->SetID(BaseItemID+200);
		}

		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=MeasurePointNo	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=L1->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=L2->GetID();
		LD->DrawPoint1=0.5;
		LD->DrawPoint2=0.5;
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y1));
		LDLine->AppendItemBase(new VectorItemDouble(XPos,y2));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		LD->GenData=GenData;
		//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Vertical;
		LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionYNano*1000000.0;
		if(GenData.CorrectLength!=0.0){
			LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionYNano*1000000.0;
			LD->GetThresholdW()->ModeToSetInInitial=false;
		}
		AppendItem(LD);
	}

	AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
	if(GetLibraryContainer()->GetLibrary(LineLib,Lib)==true){
		if(L1!=NULL){
			L1->CopyThresholdFromLibrary(&Lib);
		}
		if(L2!=NULL){
			L2->CopyThresholdFromLibrary(&Lib);
		}
	}
	if(LD!=NULL){
		if(CurrentDistanceID>=0){
			LD->SetID(CurrentDistanceID);
		}
		else{
			LD->SetID(BaseItemID);
		}
	}
	return true;
}

bool	MeasureLineMoveInPage::RemoveFilmMeasure(int MeasurePointNo)
{
	MeasureLineMoveDistanceItem	*CurrentLD=SearchDistanceItem(MeasurePointNo);
	int	CurrentDistanceID=-1;
	if(CurrentLD!=NULL){
		CurrentDistanceID=CurrentLD->GetID();

		AlgorithmItemRoot	*L1=SearchIDItem(CurrentLD->LineID1);
		AlgorithmItemRoot	*L2=SearchIDItem(CurrentLD->LineID2);
		AlgorithmItemPointerListContainer Items;
		Items.Add(CurrentLD);
		if(L1!=NULL)
			Items.Add(L1);
		if(L2!=NULL)
			Items.Add(L2);
		RemoveItems(Items);
	}
	return true;
}

bool	MeasureLineMoveInPage::AddFilmMeasureItems(FlexArea &BladeArea,FlexArea &MaskArea
												,struct MeasureHVInfo	&GenData
												,int LineLib,int RxLineLib,int DistanceLib
												,int BaseItemID
												,int MeasurePointNo)
{
	//ImageBuffer *MasterImageList[100];
	//GetMasterBuffList(MasterImageList);	
	MeasureLineMoveLineItem	*LPaperEdge=NULL;
	MeasureLineMoveLineItem	*LBladeEdge=NULL;
	MeasureLineMoveRxLineItem	*RxL=NULL;
	//MeasureLineMoveLineItem		*Lp=NULL;
	MeasureLineMoveDistanceItem	*LD=NULL;

	MeasureLineMoveDistanceItem	*CurrentLD=SearchDistanceItem(MeasurePointNo);
	int	CurrentDistanceID=-1;
	if(CurrentLD!=NULL){
		CurrentDistanceID=CurrentLD->GetID();
		if(CurrentLD->GenData.bOnlyInside	==GenData.bOnlyInside	
		&& CurrentLD->GenData.bHorizontal	==GenData.bHorizontal
		&& CurrentLD->GenData.bFrom0		==GenData.bFrom0
		&& CurrentLD->GenData.bPartnerFrom0	==GenData.bPartnerFrom0
		&& CurrentLD->GenData.PartnerPos	==GenData.PartnerPos	
		&& CurrentLD->GenData.RegLineLength	==GenData.RegLineLength){
			if(GenData.CorrectLength!=0.0){
				CurrentLD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				CurrentLD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				CurrentLD->GetThresholdW()->ModeToSetInInitial=false;
			}
			return true;
		}
		AlgorithmItemRoot	*L1=SearchIDItem(CurrentLD->LineID1);
		AlgorithmItemRoot	*L2=SearchIDItem(CurrentLD->LineID2);
		AlgorithmItemPointerListContainer Items;
		Items.Add(CurrentLD);
		if(L1!=NULL)
			Items.Add(L1);
		if(L2!=NULL)
			Items.Add(L2);
		RemoveItems(Items);
	}

	if(GenData.bOnlyInside==true && GenData.bHorizontal==false && GenData.bFrom0==false && GenData.bPartnerFrom0==true){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				if(ad->GenData.bOnlyInside	==false
				&& ad->GenData.bHorizontal	==false
				&& ad->GenData.bFrom0		==true
				&& ad->GenData.bPartnerFrom0==true){	//上側寄り刃
					MeasureLineMoveLineItem	*L1=dynamic_cast<MeasureLineMoveLineItem *>(SearchIDItem(ad->LineID1));
					MeasureLineMoveLineItem	*L2=dynamic_cast<MeasureLineMoveLineItem *>(SearchIDItem(ad->LineID2));
					if(L1->Y1OnMaster<L2->Y1OnMaster){
						LPaperEdge=L1;
						LBladeEdge=L2;
					}
					else{
						LPaperEdge=L2;
						LBladeEdge=L1;
					}
					break;
				}
			}
		}
		if(LPaperEdge!=NULL && LBladeEdge!=NULL){
			int BIndexStart ,BIndexEnd;
			int	yb1=BladeArea.GetMinY();
			int	nB=BladeArea.FindIndex(yb1+20,BIndexStart ,BIndexEnd);
			if(nB<=0)
				return false;
			int	x1=BladeArea.GetFLineLeftX(BIndexStart);
			int	x2=BladeArea.GetFLineRightX(BIndexStart);
			int	Cx=(x1+x2*2)/3;
			//double	BladeY=0;

			int	FirstLen=GenData.CorrectLength/GetParamGlobal()->ResolutionYNano*1000000.0;
			int	YPos=LBladeEdge->Y1OnMaster-FirstLen;
			//{
			//	int	LpCx=MaskArea.GetMaxX()-GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
			VectorItemDouble	*Pe1=(VectorItemDouble *)LBladeEdge->GetVector()->GetFirstItem();
			double	BladeY=Pe1->GetY();
			//
			//	VectorLineDouble	*L1Line=new VectorLineDouble();
			//	*L1Line=*((VectorLineDouble	*)LBladeEdge->GetVector());
			//	//L1Line->AppendItemBase(new VectorItemDouble(LpCx-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,Pe1->GetY()));
			//	//L1Line->AppendItemBase(new VectorItemDouble(LpCx+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,Pe1->GetY()));
			//
			//	Lp=new MeasureLineMoveLineItem();
			//	Lp->SetVector(L1Line);
			//	Lp->SetLibID(LineLib);
			//	Lp->SetLocalData(this);
			//	AppendItem(Lp);
			//}
			{
				RxL=new MeasureLineMoveRxLineItem();
				VectorLineDouble	*L1Line=new VectorLineDouble();
				L1Line->AppendItemBase(new VectorItemDouble(Cx-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2,YPos));
				L1Line->AppendItemBase(new VectorItemDouble(Cx+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2,YPos));
				RxL->SetVector(L1Line);
				RxL->SetLibID(RxLineLib);
				RxL->SetLocalData(this);
				RxL->HookedItemID	=LPaperEdge->GetID();
				RxL->RxID			=1;
				AppendItem(RxL);
			}
			LD=new MeasureLineMoveDistanceItem();
			LD->MeasurePointNo	=MeasurePointNo	;
			LD->LineType1=1;
			LD->LineType2=1;
			LD->NoCalc=true;
			LD->Line1InGlobalPage=GetPage();
			LD->LineID1	=LBladeEdge->GetID();
			LD->Line2InGlobalPage=GetPage();
			LD->LineID2	=RxL->GetID();
			LD->DrawPoint1=LBladeEdge ->GetDrawParam(Cx,BladeY);
			LD->DrawPoint2=RxL->GetDrawParam(Cx,YPos);
			LD->DifLen	=0;
			LD->ResultLen=0;
			VectorLineDouble	*LDLine=new VectorLineDouble();
			LDLine->AppendItemBase(new VectorItemDouble(Cx,BladeY));
			LDLine->AppendItemBase(new VectorItemDouble(Cx,YPos));
			LD->SetVector(LDLine);
			LD->SetLibID(DistanceLib);
			LD->SetLocalData(this);
			LD->GenData=GenData;
			//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
			LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
			if(GenData.CorrectLength!=0.0){
				LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				LD->GetThresholdW()->ModeToSetInInitial=false;
			}
			AppendItem(LD);
		}
	}
	else
	if(GenData.bOnlyInside==true && GenData.bHorizontal==false && GenData.bFrom0==false && GenData.bPartnerFrom0==false){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			MeasureLineMoveDistanceItem	*ad=dynamic_cast<MeasureLineMoveDistanceItem *>(a);
			if(ad!=NULL){
				if(ad->GenData.bOnlyInside	==false
				&& ad->GenData.bHorizontal	==false
				&& ad->GenData.bFrom0		==false
				&& ad->GenData.bPartnerFrom0==true){	//下側寄り刃
					MeasureLineMoveLineItem	*L1=dynamic_cast<MeasureLineMoveLineItem *>(SearchIDItem(ad->LineID1));
					MeasureLineMoveLineItem	*L2=dynamic_cast<MeasureLineMoveLineItem *>(SearchIDItem(ad->LineID2));
					if(L1->Y1OnMaster>L2->Y1OnMaster){
						LPaperEdge=L1;
						LBladeEdge=L2;
					}
					else{
						LPaperEdge=L2;
						LBladeEdge=L1;
					}
					break;
				}
			}
		}
		if(LPaperEdge!=NULL && LBladeEdge!=NULL){
			int BIndexStart ,BIndexEnd;
			int	yb1=BladeArea.GetMaxY();
			int	nB=BladeArea.FindIndex(yb1-20,BIndexStart ,BIndexEnd);
			if(nB<=0)
				return false;
			int	x1=BladeArea.GetFLineLeftX(BIndexStart);
			int	x2=BladeArea.GetFLineRightX(BIndexStart);
			int	Cx=(x1+x2*2)/3;
			//double	BladeY=0;

			int	FirstLen=GenData.CorrectLength/GetParamGlobal()->ResolutionYNano*1000000.0;
			int	YPos=LBladeEdge->Y1OnMaster+FirstLen;
			//{
			//	int	LpCx=MaskArea.GetMaxX()-GenData.PartnerPos/GetParamGlobal()->ResolutionXNano*1000000.0;
			VectorItemDouble	*Pe1=(VectorItemDouble *)LBladeEdge->GetVector()->GetFirstItem();
			double	BladeY=Pe1->GetY();
			//
			//	VectorLineDouble	*L1Line=new VectorLineDouble();
			//	*L1Line=*((VectorLineDouble	*)LBladeEdge->GetVector());
			//	//L1Line->AppendItemBase(new VectorItemDouble(LpCx-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,Pe1->GetY()));
			//	//L1Line->AppendItemBase(new VectorItemDouble(LpCx+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionXNano*1000000.0/2,Pe1->GetY()));
			//
			//	Lp=new MeasureLineMoveLineItem();
			//	Lp->SetVector(L1Line);
			//	Lp->SetLibID(LineLib);
			//	Lp->SetLocalData(this);
			//	AppendItem(Lp);
			//}
			{
				RxL=new MeasureLineMoveRxLineItem();
				VectorLineDouble	*L1Line=new VectorLineDouble();
				L1Line->AppendItemBase(new VectorItemDouble(Cx-((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2,YPos));
				L1Line->AppendItemBase(new VectorItemDouble(Cx+((double)GenData.RegLineLength)/GetParamGlobal()->ResolutionYNano*1000000.0/2,YPos));
				RxL->SetVector(L1Line);
				RxL->SetLibID(RxLineLib);
				RxL->SetLocalData(this);
				RxL->HookedItemID	=LPaperEdge->GetID();
				RxL->RxID			=2;
				AppendItem(RxL);
			}
			LD=new MeasureLineMoveDistanceItem();
			LD->MeasurePointNo	=MeasurePointNo	;
			LD->LineType1=1;
			LD->LineType2=1;
			LD->NoCalc=true;
			LD->Line1InGlobalPage=GetPage();
			LD->LineID1	=LBladeEdge->GetID();
			LD->Line2InGlobalPage=GetPage();
			LD->LineID2	=RxL->GetID();
			LD->DrawPoint1=LBladeEdge ->GetDrawParam(Cx,BladeY);
			LD->DrawPoint2=RxL->GetDrawParam(Cx,YPos);
			LD->DifLen	=0;
			LD->ResultLen=0;
			VectorLineDouble	*LDLine=new VectorLineDouble();
			LDLine->AppendItemBase(new VectorItemDouble(Cx,BladeY));
			LDLine->AppendItemBase(new VectorItemDouble(Cx,YPos));
			LD->SetVector(LDLine);
			LD->SetLibID(DistanceLib);
			LD->SetLocalData(this);
			LD->GenData=GenData;
			//LD->DirectionMode	=MeasureLineMoveDistanceItem::_Horizontal;
			LD->GetThresholdW()->OKRangeInInitial	=GenData.OKWidth/GetParamGlobal()->ResolutionXNano*1000000.0;
			if(GenData.CorrectLength!=0.0){
				LD->GetThresholdW()->ThresholdM	=(GenData.CorrectLength-GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				LD->GetThresholdW()->ThresholdP	=(GenData.CorrectLength+GenData.OKWidth/2.0)/GetParamGlobal()->ResolutionXNano*1000000.0;
				LD->GetThresholdW()->ModeToSetInInitial=false;
			}
			AppendItem(LD);
		}
	}


	AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
	if(GetLibraryContainer()->GetLibrary(RxLineLib,Lib)==true){
		if(RxL!=NULL){
			RxL->CopyThresholdFromLibrary(&Lib);
		}
	}

	if(LD!=NULL){
		if(CurrentDistanceID>=0){
			LD->SetID(CurrentDistanceID);
		}
		else{
			LD->SetID(BaseItemID);
		}
	}
	return true;
}


int		MeasureLineMoveInPage::SearchLeftEdge(ImageBuffer &Buff,int X,int Y,int SearchDot)
{
	int	Mergin=10;
	FlexArea	D1;
	FlexArea	D2;
	FlexArea	DV;
	D1.SetRectangle(X-Mergin,Y-Mergin,X-1,Y+Mergin);
	D2.SetRectangle(X+1,Y-Mergin,X+Mergin,Y+Mergin);
	DV.SetRectangle(X-Mergin,Y-Mergin,X+Mergin,Y+Mergin);
	double	MaxV=0;
	int		Lx=0;
	for(int dx=-SearchDot;dx<=SearchDot;dx++){
		double	V1=D1.GetAverage(dx ,0,Buff,1.0,1.0);
		double	V2=D2.GetAverage(dx ,0,Buff,1.0,1.0);
		double DAvr;
		double	V=DV.GetVar(dx ,0 ,Buff ,DAvr);
		if(MaxV<V && V1<V2){
			MaxV=V;
			Lx=dx;
		}
	}
	return X+Lx;
}


bool	MeasureLineMoveInPage::AddMonoFilmMeasureItems(void)
{
	MeasureLineMoveBase	*MBase=(MeasureLineMoveBase *)GetParentBase();

	int	BaseItemID	=500;
	int	SearchXDot=30;

	AlgorithmItemPointerListContainer	RemovedItems;
	AlgorithmItemRoot	*LD1=SearchIDItem(BaseItemID);
	if(LD1!=NULL){
		RemovedItems.Add(LD1);
		AlgorithmItemRoot	*LL1=SearchIDItem(BaseItemID+110);
		AlgorithmItemRoot	*LL2=SearchIDItem(BaseItemID+120);
		if(LL1!=NULL)
			RemovedItems.Add(LL1);
		if(LL2!=NULL)
			RemovedItems.Add(LL2);
	}
	AlgorithmItemRoot	*LD2=SearchIDItem(BaseItemID+1);
	if(LD2!=NULL){
		RemovedItems.Add(LD2);
		AlgorithmItemRoot	*LL1=SearchIDItem(BaseItemID+1+110);
		AlgorithmItemRoot	*LL2=SearchIDItem(BaseItemID+1+120);
		if(LL1!=NULL)
			RemovedItems.Add(LL1);
		if(LL2!=NULL)
			RemovedItems.Add(LL2);
	}
	RemoveItems(RemovedItems);

	if(MBase->EnableFilm==false)
		return false;

	ConstMapBufferListContainer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap);
	ConstMapBuffer Map;
	MaskMap.BindOr(Map);
	const BYTE	**MaskBitmap=Map.GetBitMap();
	FlexArea	MaskArea;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(MaskBitmap ,Map.GetXByte(),Map.GetXLen(),Map.GetYLen(),FPack);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetPatternByte()>1000){
			MaskArea+=*f;
		}
	}
	ImageBuffer *MasterImageList[10];
	GetMasterBuffList(0,MasterImageList);
	
	int LineLib		=MBase->FilmLineLibID;
	int DistanceLib	=MBase->FilmLineDistanceLibID;

	AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
	if(GetLibraryContainer()->GetLibrary(LineLib,Lib)==true){
		int	LMinX=99999999;
		int	LMinY=MaskArea.GetMinY();
		for(int k=0;k<MaskArea.GetFLineLen();k++){
			int	Y=MaskArea.GetFLineAbsY(k);
			int	x=MaskArea.GetFLineLeftX(k);
			if(Y-MaskArea.GetMinY()>MBase->FilmTopRangeYLen){
				break;
			}
			if(x<LMinX){
				LMinX=x;
			}
		}
		LMinX=SearchLeftEdge(*MasterImageList[0],LMinX,LMinY+MBase->FilmTopRangeYLen,SearchXDot);

		int	FilmPaperX=LMinX+MBase->FilmTopFilmPaperX;
		int	FilmX=FilmPaperX;
		int	FilmY=0;
		for(int k=0;k<MaskArea.GetFLineLen();k++){
			int	Y=MaskArea.GetFLineAbsY(k);
			if(MaskArea.GetFLineLeftX(k)<=FilmX && FilmX<MaskArea.GetFLineRightX(k)){
				FilmX=LMinX+MBase->FilmTopFilmEdgeOffsetX;
				FilmY=Y-MBase->FilmTopFilmEdgeOffsetY;
				break;
			}
		}

		int	LpCx=LMinX+MBase->FilmTopPaperLineOffsetX;
		for(int k=0;k<MaskArea.GetFLineLen();k++){
			int	Y=MaskArea.GetFLineAbsY(k);
			if(MaskArea.GetFLineLeftX(k)<=LpCx && LpCx<MaskArea.GetFLineRightX(k)){
				LMinY=Y;
				break;
			}
		}
	
		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(LpCx-MBase->FilmLineLen/2,LMinY));
		L1Line->AppendItemBase(new VectorItemDouble(LpCx+MBase->FilmLineLen/2,LMinY));
	
		MeasureLineMoveLineItem	*Lp=new MeasureLineMoveLineItem();
		Lp->SetVector(L1Line);
		Lp->SetLibID(LineLib);
		Lp->SetLocalData(this);
		Lp->CopyThresholdFromLibrary(&Lib);
		MeasureLineMoveThreshold	*WpThr=Lp->GetThresholdW(GetLayersBase());
		WpThr->SearchDot =MBase->FilmLineSearchDot;
		WpThr->OKRangeInInitial	=false;
		AppendItem(Lp);
		Lp->SetID(BaseItemID+110);
	
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(FilmX-MBase->FilmLineLen/2,FilmY));
		L2Line->AppendItemBase(new VectorItemDouble(FilmX+MBase->FilmLineLen/2,FilmY));
	
		MeasureLineMoveLineItem	*Lq=new MeasureLineMoveLineItem();
		Lq->SetVector(L2Line);
		Lq->SetLibID(LineLib);
		Lq->SetLocalData(this);
		Lq->CopyThresholdFromLibrary(&Lib);
		MeasureLineMoveThreshold	*WqThr=Lq->GetThresholdW(GetLayersBase());
		WqThr->SearchDot =MBase->FilmLineSearchDot;
		WqThr->OKRangeInInitial	=false;
		WqThr->BrightnessIdealRight		=MBase->FilmTopBrightness1		;
		WqThr->BrightnessIdealLeft		=MBase->FilmTopBrightness2		;
		WqThr->BrightnessIdealRightRange=MBase->FilmTopBrightness1Range	;
		WqThr->BrightnessIdealLeftRange	=MBase->FilmTopBrightness2Range	;
		AppendItem(Lq);
		Lq->SetID(BaseItemID+120);
	
		MeasureLineMoveDistanceItem	*LD;
		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=0	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=Lp->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=Lq->GetID();
		LD->DrawPoint1=-Lp->GetDrawParam(FilmX,LMinY);
		LD->DrawPoint2=Lq->GetDrawParam(FilmX,FilmY);
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(FilmX,LMinY));
		LDLine->AppendItemBase(new VectorItemDouble(FilmX,FilmY));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		MeasureLineMoveThreshold	*WDThr=LD->GetThresholdW(GetLayersBase());
		WDThr->OKRangeInInitial	=false;
		WDThr->ModeToSetInInitial=false;
		WDThr->ThresholdM	=0;
		WDThr->ThresholdP	=99999999;

		LD->TransferInfo	=1;
		AppendItem(LD);
		LD->SetID(BaseItemID);
	}

	if(GetLibraryContainer()->GetLibrary(LineLib,Lib)==true){
		int	LMinX=99999999;
		int	LMaxY=MaskArea.GetMaxY();
		for(int k=MaskArea.GetFLineLen()-1;k>=0;k--){
			int	Y=MaskArea.GetFLineAbsY(k);
			int	x=MaskArea.GetFLineLeftX(k);
			if(MaskArea.GetMaxY()-Y>MBase->FilmBotRangeYLen){
				break;
			}
			if(x<LMinX){
				LMinX=x;
			}
		}
		LMinX=SearchLeftEdge(*MasterImageList[0],LMinX,LMaxY-MBase->FilmBotRangeYLen,SearchXDot);

		int	FilmPaperX=LMinX+MBase->FilmBotFilmPaperX;
		int	FilmX=FilmPaperX;
		int	FilmY=0;
		for(int k=MaskArea.GetFLineLen()-1;k>=0;k--){
			int	Y=MaskArea.GetFLineAbsY(k);
			if(MaskArea.GetFLineLeftX(k)<=FilmX && FilmX<MaskArea.GetFLineRightX(k)){
				FilmX=LMinX+MBase->FilmBotFilmEdgeOffsetX;
				FilmY=Y+MBase->FilmBotFilmEdgeOffsetY;
				break;
			}
		}

		int	LpCx=LMinX+MBase->FilmBotPaperLineOffsetX;
		for(int k=MaskArea.GetFLineLen()-1;k>=0;k--){
			int	Y=MaskArea.GetFLineAbsY(k);
			if(MaskArea.GetFLineLeftX(k)<=LpCx && LpCx<MaskArea.GetFLineRightX(k)){
				LMaxY=Y;
				break;
			}
		}

		VectorLineDouble	*L1Line=new VectorLineDouble();
		L1Line->AppendItemBase(new VectorItemDouble(LpCx-MBase->FilmLineLen/2,LMaxY));
		L1Line->AppendItemBase(new VectorItemDouble(LpCx+MBase->FilmLineLen/2,LMaxY));
	
		MeasureLineMoveLineItem	*Lp=new MeasureLineMoveLineItem();
		Lp->SetVector(L1Line);
		Lp->SetLibID(LineLib);
		Lp->SetLocalData(this);
		Lp->CopyThresholdFromLibrary(&Lib);
		MeasureLineMoveThreshold	*WpThr=Lp->GetThresholdW(GetLayersBase());
		WpThr->SearchDot =MBase->FilmLineSearchDot;
		WpThr->OKRangeInInitial	=false;
		AppendItem(Lp);
		Lp->SetID(BaseItemID+1+110);
	
		VectorLineDouble	*L2Line=new VectorLineDouble();
		L2Line->AppendItemBase(new VectorItemDouble(FilmX-MBase->FilmLineLen/2,FilmY));
		L2Line->AppendItemBase(new VectorItemDouble(FilmX+MBase->FilmLineLen/2,FilmY));
	
		MeasureLineMoveLineItem	*Lq=new MeasureLineMoveLineItem();
		Lq->SetVector(L2Line);
		Lq->SetLibID(LineLib);
		Lq->SetLocalData(this);
		Lq->CopyThresholdFromLibrary(&Lib);
		MeasureLineMoveThreshold	*WqThr=Lq->GetThresholdW(GetLayersBase());
		WqThr->SearchDot =MBase->FilmLineSearchDot;
		WqThr->OKRangeInInitial	=false;
		WqThr->BrightnessIdealRight		=MBase->FilmBotBrightness1		;
		WqThr->BrightnessIdealLeft		=MBase->FilmBotBrightness2		;
		WqThr->BrightnessIdealRightRange=MBase->FilmBotBrightness1Range	;
		WqThr->BrightnessIdealLeftRange	=MBase->FilmBotBrightness2Range	;
		AppendItem(Lq);
		Lq->SetID(BaseItemID+1+120);
	
		MeasureLineMoveDistanceItem	*LD;
		LD=new MeasureLineMoveDistanceItem();
		LD->MeasurePointNo	=0	;
		LD->LineType1=1;
		LD->LineType2=1;
		LD->NoCalc=true;
		LD->Line1InGlobalPage=GetPage();
		LD->LineID1	=Lp->GetID();
		LD->Line2InGlobalPage=GetPage();
		LD->LineID2	=Lq->GetID();
		LD->DrawPoint1=-Lp->GetDrawParam(FilmX,LMaxY);
		LD->DrawPoint2=Lq->GetDrawParam(FilmX,FilmY);
		LD->DifLen	=0;
		LD->ResultLen=0;
		VectorLineDouble	*LDLine=new VectorLineDouble();
		LDLine->AppendItemBase(new VectorItemDouble(FilmX,LMaxY));
		LDLine->AppendItemBase(new VectorItemDouble(FilmX,FilmY));
		LD->SetVector(LDLine);
		LD->SetLibID(DistanceLib);
		LD->SetLocalData(this);
		MeasureLineMoveThreshold	*WDThr=LD->GetThresholdW(GetLayersBase());
		WDThr->OKRangeInInitial	=false;
		WDThr->ModeToSetInInitial=false;
		WDThr->ThresholdM	=0;
		WDThr->ThresholdP	=99999999;

		LD->TransferInfo	=2;
		AppendItem(LD);
		LD->SetID(BaseItemID+1);
	}
	return true;
}

bool	MeasureLineMoveInPage::FindY(FlexArea &Area,int XPos,int &BMinY,int &BMaxY)
{
	
	BMaxY=Area.GetMaxY();
	for(BMinY=Area.GetMinY();BMinY<Area.GetMaxY();BMinY++){
		if(Area.IsInclude(XPos,BMinY)==true){
			break;
		}
	}
	if(BMinY>=Area.GetMaxY()){
		return false;
	}
	for(BMaxY=Area.GetMaxY();BMaxY>=Area.GetMinY();BMaxY--){
		if(Area.IsInclude(XPos,BMaxY)==true){
			break;
		}
	}
	if(BMaxY<Area.GetMinY()){
		return false;
	}
	return true;
}

void	MeasureLineMoveInPage::MakeBMap(BYTE **CurrentMap ,int XByte,int XLen ,int YLen
							,int BladePickupRL
							,int BladePickupRH
							,int BladePickupGL
							,int BladePickupGH
							,int BladePickupBL
							,int BladePickupBH
							,int X1, int X2)
{
	ImageBuffer *ImageList[100];
	GetMasterBuffList(ImageList);
	MatrixBuffClear(CurrentMap,0,XByte,YLen);
	if(GetLayerNumb()>=3){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=ImageList[0]->GetY(y);
				BYTE	*s1=ImageList[1]->GetY(y);
				BYTE	*s2=ImageList[2]->GetY(y);
				BYTE	*d=CurrentMap[y];
				for(int x=0;x<XLen;x++){
					if(X1<=x && x<=X2){
						if(BladePickupRL<=*s0 && *s0<=BladePickupRH
						&& BladePickupGL<=*s1 && *s1<=BladePickupGH
						&& BladePickupBL<=*s2 && *s2<=BladePickupBH){
							SetBmpBitOnY1(d,x);
						}
					}
					s0++;
					s1++;
					s2++;
				}
			}
		}
	}
	else
	if(GetLayerNumb()==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=ImageList[0]->GetY(y);
				BYTE	*s1=ImageList[1]->GetY(y);
				BYTE	*d=CurrentMap[y];
				for(int x=0;x<XLen;x++){
					if(X1<=x && x<=X2){
						if(BladePickupRL<=*s0 && *s0<=BladePickupRH
						&& BladePickupGL<=*s1 && *s1<=BladePickupGH){
							SetBmpBitOnY1(d,x);
						}
					}
					s0++;
					s1++;
				}
			}
		}
	}
	else
	if(GetLayerNumb()==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*s0=ImageList[0]->GetY(y);
				BYTE	*d=CurrentMap[y];
				for(int x=0;x<XLen;x++){
					if(X1<=x && x<=X2){
						if(BladePickupRL<=*s0 && *s0<=BladePickupRH){
							SetBmpBitOnY1(d,x);
						}
					}
					s0++;
				}
			}
		}
	}

	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);
	::FatArea (CurrentMap,TmpMap ,XByte,YLen);
	::FatArea (CurrentMap,TmpMap ,XByte,YLen);
	::ThinArea(CurrentMap,TmpMap ,XByte,YLen);
	::ThinArea(CurrentMap,TmpMap ,XByte,YLen);
	::ThinArea(CurrentMap,TmpMap ,XByte,YLen);
	::ThinArea(CurrentMap,TmpMap ,XByte,YLen);
	::FatArea (CurrentMap,TmpMap ,XByte,YLen);
	::FatArea (CurrentMap,TmpMap ,XByte,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
}
void	MeasureLineMoveInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(PickupBmp!=NULL){
		QColor	Col(128,192,0,80);
		DrawBitImageOr(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
				,movx ,movy,ZoomRate
				,0,0
				,Col);
	}
	PickupArea.DrawAlpha(0,0,&pnt,qRgba(0,255,0,128),ZoomRate,movx,movy);

	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	
	AlgorithmBase	*AHole=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(AHole!=NULL){
		AlgorithmInPagePI	*HPage=(AlgorithmInPagePI *)AHole->GetPageData(GetPage());
		HPage->Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	}
}

void	MeasureLineMoveInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		MeasureLineMoveItemBase	*BI=(MeasureLineMoveItemBase *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
//===========================================
MeasureLineMoveBase::MeasureLineMoveBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	ResultColor		=Qt::yellow;
	ResultArrowEnableMakeImage	=true;
	ResultArrowEnableDrawLine	=true;
	ResultDistanceEnableMakeImage	=true;
	ResultDistanceEnableDrawLine	=true;
	SaveItemImage					=true;
	Receiver		=true;	
	TransferPortNo	=-1;
	TransferIP		=/**/"";

	EnableFilm				=false;
	FilmLineLen				=50;
	FilmLineLibID			=1;
	FilmLineDistanceLibID	=2;
	FilmLineSearchDot		=60;
	FilmTopPaperLineOffsetX	=200;
	FilmTopFilmPaperX		=100;
	FilmTopFilmEdgeOffsetX	=100;
	FilmTopFilmEdgeOffsetY	=100;
	FilmTopRangeYLen		=1000;
	FilmTopBrightness1		=0;
	FilmTopBrightness2		=0;
	FilmTopBrightness1Range	=0;
	FilmTopBrightness2Range	=0;
	
	FilmBotPaperLineOffsetX	=200;
	FilmBotFilmPaperX		=100;
	FilmBotFilmEdgeOffsetX	=100;
	FilmBotFilmEdgeOffsetY	=100;
	FilmBotRangeYLen		=1000;
	FilmBotBrightness1		=0;
	FilmBotBrightness2		=0;
	FilmBotBrightness1Range	=0;
	FilmBotBrightness2Range	=0;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,LangSolver.GetString(XMeasureLineMove_LS,LID_0)/*"Color for Mask"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XMeasureLineMove_LS,LID_1)/*"Color for Selected Mask"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XMeasureLineMove_LS,LID_2)/*"Color for Active Mask"*/);
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,LangSolver.GetString(XMeasureLineMove_LS,LID_3)/*"Color for Negative Mask"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XMeasureLineMove_LS,LID_4)/*"Color for Selected Negative Mask"*/);
	SetParam(&ResultColor		, /**/"Color" ,/**/"ResultColor"		,LangSolver.GetString(XMeasureLineMove_LS,LID_6)/*"Result color"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XMeasureLineMove_LS,LID_5)/*"Color for Transparent display level"*/);

	SetParam(&ResultArrowEnableMakeImage	, /**/"Result" ,/**/"ResultArrowEnableMakeImage"	,LangSolver.GetString(XMeasureLineMove_LS,LID_11)/*"Arrow Enable MakeImage in Result data"*/);
	SetParam(&ResultArrowEnableDrawLine		, /**/"Result" ,/**/"ResultArrowEnableDrawLine"		,LangSolver.GetString(XMeasureLineMove_LS,LID_16)/*"Arrow Enable DrawLine in Result data"*/);
	SetParam(&ResultDistanceEnableMakeImage	, /**/"Result" ,/**/"ResultDistanceEnableMakeImage"	,LangSolver.GetString(XMeasureLineMove_LS,LID_22)/*"Distance Enable MakeImage in Result data"*/);
	SetParam(&ResultDistanceEnableDrawLine	, /**/"Result" ,/**/"ResultDistanceEnableDrawLine"	,LangSolver.GetString(XMeasureLineMove_LS,LID_23)/*"Distance Enable DrawLine in Result data"*/);
	SetParam(&SaveItemImage					, /**/"Result" ,/**/"SaveItemImage"					,LangSolver.GetString(XMeasureLineMove_LS,LID_24)/*"Save Item image in Result data"*/);

	SetParam(&Receiver			, /**/"Transfer" ,/**/"Receiver"		,LangSolver.GetString(XMeasureLineMove_LS,LID_25)/*"Is it Receiver for transfer?"*/);
	SetParam(&TransferPortNo	, /**/"Transfer" ,/**/"TransferPortNo"	,LangSolver.GetString(XMeasureLineMove_LS,LID_26)/*"Port number for transfer"*/);
	SetParam(&TransferIP		, /**/"Transfer" ,/**/"TransferIP"		,LangSolver.GetString(XMeasureLineMove_LS,LID_27)/*"IP address for transfer"*/);

	SetParam(&EnableFilm				, /**/"FilmMono" ,/**/"EnableFilm"				,LangSolver.GetString(XMeasureLineMove_LS,LID_28)/*"EnableFilm"*/);
	SetParam(&FilmLineLen				, /**/"FilmMono" ,/**/"FilmLineLen"				,LangSolver.GetString(XMeasureLineMove_LS,LID_29)/*"Film Line Length"*/);
	SetParam(&FilmLineLibID				, /**/"FilmMono" ,/**/"FilmLineLibID"			,LangSolver.GetString(XMeasureLineMove_LS,LID_30)/*"Film Line LibID"*/);
	SetParam(&FilmLineDistanceLibID		, /**/"FilmMono" ,/**/"FilmLineDistanceLibID"	,LangSolver.GetString(XMeasureLineMove_LS,LID_31)/*"Film Distance LibID"*/);
	SetParam(&FilmLineSearchDot			, /**/"FilmMono" ,/**/"FilmLineSearchDot"		,LangSolver.GetString(XMeasureLineMove_LS,LID_32)/*"Film line - search dot"*/);
	SetParam(&FilmTopPaperLineOffsetX	, /**/"FilmMono" ,/**/"FilmTopPaperLineOffsetX"	,LangSolver.GetString(XMeasureLineMove_LS,LID_33)/*"Film Top PaperLine OffsetX"*/);
	SetParam(&FilmTopFilmPaperX			, /**/"FilmMono" ,/**/"FilmTopFilmPaperX"		,LangSolver.GetString(XMeasureLineMove_LS,LID_34)/*"Film Top Film side OffsetX"*/);
	SetParam(&FilmTopFilmEdgeOffsetX	, /**/"FilmMono" ,/**/"FilmTopFilmEdgeOffsetX"	,LangSolver.GetString(XMeasureLineMove_LS,LID_35)/*"Film Top FilmEdge OffsetX"*/);
	SetParam(&FilmTopFilmEdgeOffsetY	, /**/"FilmMono" ,/**/"FilmTopFilmEdgeOffsetY"	,LangSolver.GetString(XMeasureLineMove_LS,LID_36)/*"Film Top FilmEdge OffsetY"*/);
	SetParam(&FilmTopRangeYLen			, /**/"FilmMono" ,/**/"FilmTopRangeYLen"		,LangSolver.GetString(XMeasureLineMove_LS,LID_37)/*"Film Top Range YLen"*/);

	SetParam(&FilmTopBrightness1		, /**/"FilmMono" ,/**/"FilmTopBrightness1"		,LangSolver.GetString(XMeasureLineMove_LS,LID_38)/*"Film Top Brightness1"*/);
	SetParam(&FilmTopBrightness2		, /**/"FilmMono" ,/**/"FilmTopBrightness2"		,LangSolver.GetString(XMeasureLineMove_LS,LID_39)/*"Film Top Brightness2"*/);
	SetParam(&FilmTopBrightness1Range	, /**/"FilmMono" ,/**/"FilmTopBrightness1Range"	,LangSolver.GetString(XMeasureLineMove_LS,LID_40)/*"Film Top Brightness1 Range"*/);
	SetParam(&FilmTopBrightness2Range	, /**/"FilmMono" ,/**/"FilmTopBrightness2Range"	,LangSolver.GetString(XMeasureLineMove_LS,LID_41)/*"Film Top Brightness2 Range"*/);
	//SetParam(&FilmTopRangeMaxY			, /**/"FilmMono" ,/**/"FilmTopRangeMaxY"		,"Film Top Range MaxY");

	SetParam(&FilmBotPaperLineOffsetX	, /**/"FilmMono" ,/**/"FilmBotPaperLineOffsetX"	,LangSolver.GetString(XMeasureLineMove_LS,LID_42)/*"Film Bottom PaperLine OffsetX"*/);
	SetParam(&FilmBotFilmPaperX			, /**/"FilmMono" ,/**/"FilmBotFilmPaperX"		,LangSolver.GetString(XMeasureLineMove_LS,LID_43)/*"Film Bottom Film side OffsetX"*/);
	SetParam(&FilmBotFilmEdgeOffsetX	, /**/"FilmMono" ,/**/"FilmBotFilmEdgeOffsetX"	,LangSolver.GetString(XMeasureLineMove_LS,LID_44)/*"Film Bottom FilmEdge OffsetX"*/);
	SetParam(&FilmBotFilmEdgeOffsetY	, /**/"FilmMono" ,/**/"FilmBotFilmEdgeOffsetY"	,LangSolver.GetString(XMeasureLineMove_LS,LID_45)/*"Film Bottom FilmEdge OffsetY"*/);
	SetParam(&FilmBotRangeYLen			, /**/"FilmMono" ,/**/"FilmBotRangeYLen"		,LangSolver.GetString(XMeasureLineMove_LS,LID_46)/*"Film Bottom Range YLen"*/);
	//SetParam(&FilmBotRangeMaxY			, /**/"FilmMono" ,/**/"FilmBotRangeMaxY"		,"Film Bottom Range MaxY");
	SetParam(&FilmBotBrightness1		, /**/"FilmMono" ,/**/"FilmBotBrightness1"		,LangSolver.GetString(XMeasureLineMove_LS,LID_47)/*"Film Bottom Brightness1"*/);
	SetParam(&FilmBotBrightness2		, /**/"FilmMono" ,/**/"FilmBotBrightness2"		,LangSolver.GetString(XMeasureLineMove_LS,LID_48)/*"Film Bottom Brightness2"*/);
	SetParam(&FilmBotBrightness1Range	, /**/"FilmMono" ,/**/"FilmBotBrightness1Range"	,LangSolver.GetString(XMeasureLineMove_LS,LID_49)/*"Film Bottom Brightness1 Range"*/);
	SetParam(&FilmBotBrightness2Range	, /**/"FilmMono" ,/**/"FilmBotBrightness2Range"	,LangSolver.GetString(XMeasureLineMove_LS,LID_50)/*"Film Bottom Brightness2 Range"*/);



}

AlgorithmDrawAttr	*MeasureLineMoveBase::CreateDrawAttr(void)
{
	return new MeasureLineMoveDrawAttr();
}

void	MeasureLineMoveBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempMeasureLineMoveLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempMeasureLineMoveLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdGetMeasureLineMoveLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMeasureLineMoveLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdLoadMeasureLineMoveLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMeasureLineMoveLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearMeasureLineMoveLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearMeasureLineMoveLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteMeasureLineMoveLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteMeasureLineMoveLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdAddByteMeasureLineMoveItemPacket	*AddBItem=dynamic_cast<CmdAddByteMeasureLineMoveItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			MBuff.open(QIODevice::ReadWrite);

			MeasureLineMoveItemBase	*Item	=(MeasureLineMoveItemBase *)PData->CreateItem(AddBItem->ItemClass);
			Item->Load(&MBuff,GetLayersBase());
			if(AddBItem->Vector!=NULL){
				Item->SetVector(*AddBItem->Vector);
			}
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			Item->SetLibID(AddBItem->SelectedLibID);
			Item->SetItemName(AddBItem->ItemName);
			Item->InitialInCreation();
			if(Item->SetLocalData((MeasureLineMoveInPage *)PData)==true){
				PData->AppendItem(Item);
			}
			else{
				MeasureLineMoveDistanceItem	*DItem=dynamic_cast<MeasureLineMoveDistanceItem *>(Item);
				if(DItem!=NULL){
					DItem->NoCalc				=AddBItem->NoCalc;
					DItem->Line1InGlobalPage	=AddBItem->GlobalPage1;
					if(DItem->Line1InGlobalPage>=0)
						DItem->LineID1				=AddBItem->ClosedItemID1;
					DItem->Line2InGlobalPage	=AddBItem->GlobalPage2;
					if(DItem->Line2InGlobalPage>=0)
						DItem->LineID2				=AddBItem->ClosedItemID2;
				}
				if(DItem->Line1InGlobalPage>=0 && DItem->LineID1>=0
				&& DItem->Line2InGlobalPage>=0 && DItem->LineID2>=0){
					PData->AppendItem(DItem);
				}
				else{
					delete	Item;
				}
			}
		}
		return;
	}
	CmdInsertMeasureLineMoveLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMeasureLineMoveLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MeasureLineMoveVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMeasureLineMoveLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMeasureLineMoveLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MeasureLineMoveVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdExecuteAlignMeasureLineMove	*CmdExecuteAlignMeasureLineMoveVar=dynamic_cast<CmdExecuteAlignMeasureLineMove *>(packet);
	if(CmdExecuteAlignMeasureLineMoveVar!=NULL){
		AlgorithmInPageRoot	*p=GetPageData(0);
		double	Dest[6];
		p->GetAffinParam(CmdExecuteAlignMeasureLineMoveVar->ItemPoint[0].GetX(),CmdExecuteAlignMeasureLineMoveVar->ItemPoint[0].GetY()
						,CmdExecuteAlignMeasureLineMoveVar->ItemPoint[1].GetX(),CmdExecuteAlignMeasureLineMoveVar->ItemPoint[1].GetY()
						,CmdExecuteAlignMeasureLineMoveVar->ItemPoint[2].GetX(),CmdExecuteAlignMeasureLineMoveVar->ItemPoint[2].GetY()
						,CmdExecuteAlignMeasureLineMoveVar->ImagePoint[0].GetX(),CmdExecuteAlignMeasureLineMoveVar->ImagePoint[0].GetY()
						,CmdExecuteAlignMeasureLineMoveVar->ImagePoint[1].GetX(),CmdExecuteAlignMeasureLineMoveVar->ImagePoint[1].GetY()
						,CmdExecuteAlignMeasureLineMoveVar->ImagePoint[2].GetX(),CmdExecuteAlignMeasureLineMoveVar->ImagePoint[2].GetY()
						,Dest);
		TransformAffin	Param(Dest);
		ExecuteTransformSelectedItems(Param);
	}
	CmdCreateThresholdPacket	*CmdCreateThresholdPacketVar=dynamic_cast<CmdCreateThresholdPacket *>(packet);
	if(CmdCreateThresholdPacketVar!=NULL){
		CmdCreateThresholdPacketVar->Thre=new MeasureLineMoveThreshold(NULL);
		return;
	}
	CmdCreateThresholdMeasureLineMove	*CmdCreateThresholdVar=dynamic_cast<CmdCreateThresholdMeasureLineMove *>(packet);
	if(CmdCreateThresholdVar!=NULL){
		CmdCreateThresholdVar->Item=new MeasureLineMoveDistanceItem();
		CmdCreateThresholdVar->ThresholdD	=(MeasureLineMoveThreshold *)CmdCreateThresholdVar->Item->CreateThresholdInstance();
		CmdCreateThresholdVar->ThresholdL1	=(MeasureLineMoveThreshold *)CmdCreateThresholdVar->Item->CreateThresholdInstance();
		CmdCreateThresholdVar->ThresholdL2	=(MeasureLineMoveThreshold *)CmdCreateThresholdVar->Item->CreateThresholdInstance();
		return;
	}
	CmdMeasureLineMoveSendTryThreshold	*CmdMeasureLineMoveSendTryThresholdVar=dynamic_cast<CmdMeasureLineMoveSendTryThreshold *>(packet);
	if(CmdMeasureLineMoveSendTryThresholdVar!=NULL){
		CmdMeasureLineMoveSendTryThresholdVar->PTry=new LineMoveSendTryThreshold();

		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(CmdMeasureLineMoveSendTryThresholdVar->SrcD->GetPhaseCode());
		if(Ah!=NULL){
			AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(CmdMeasureLineMoveSendTryThresholdVar->SrcD->GetPage());
			if(Ap!=NULL){
				CmdMeasureLineMoveSendTryThresholdVar->TargetD	=dynamic_cast<MeasureLineMoveDistanceItem *>(Ap->CreateItem(CmdMeasureLineMoveSendTryThresholdVar->SrcD->GetItemClassType()));
				CmdMeasureLineMoveSendTryThresholdVar->TargetL1	=dynamic_cast<MeasureLineMoveItemBase *>(Ap->CreateItem(CmdMeasureLineMoveSendTryThresholdVar->SrcL1->GetItemClassType()));
				CmdMeasureLineMoveSendTryThresholdVar->TargetL2	=dynamic_cast<MeasureLineMoveItemBase *>(Ap->CreateItem(CmdMeasureLineMoveSendTryThresholdVar->SrcL2->GetItemClassType()));

				CmdMeasureLineMoveSendTryThresholdVar->TargetD	->SetParent(Ap);
				CmdMeasureLineMoveSendTryThresholdVar->TargetL1	->SetParent(Ap);
				CmdMeasureLineMoveSendTryThresholdVar->TargetL2	->SetParent(Ap);
		
				QBuffer	BuffD(&CmdMeasureLineMoveSendTryThresholdVar->ThresholdDataForTargetD);
				BuffD.open(QIODevice::ReadWrite);
				CmdMeasureLineMoveSendTryThresholdVar->TargetD->GetThresholdW()->Load(&BuffD);

				QBuffer	BuffL1(&CmdMeasureLineMoveSendTryThresholdVar->ThresholdDataForTargetL1);
				BuffL1.open(QIODevice::ReadWrite);
				CmdMeasureLineMoveSendTryThresholdVar->TargetL1->GetThresholdW()->Load(&BuffL1);

				QBuffer	BuffL2(&CmdMeasureLineMoveSendTryThresholdVar->ThresholdDataForTargetL2);
				BuffL2.open(QIODevice::ReadWrite);
				CmdMeasureLineMoveSendTryThresholdVar->TargetL2->GetThresholdW()->Load(&BuffL2);

				CmdMeasureLineMoveSendTryThresholdVar->PTry->Calc( 
															 CmdMeasureLineMoveSendTryThresholdVar->TargetD
															,CmdMeasureLineMoveSendTryThresholdVar->TargetL1
															,CmdMeasureLineMoveSendTryThresholdVar->TargetL2
															,CmdMeasureLineMoveSendTryThresholdVar->SrcD
															,CmdMeasureLineMoveSendTryThresholdVar->SrcL1
															,CmdMeasureLineMoveSendTryThresholdVar->SrcL2
														   ,this);
			}
		}
		return;
	}
	CmdReqThresholdHLMeasureLineMove	*CmdReqThresholdHLMeasureLineMoveVar=dynamic_cast<CmdReqThresholdHLMeasureLineMove *>(packet);
	if(CmdReqThresholdHLMeasureLineMoveVar!=NULL){
		CmdReqThresholdHLMeasureLineMoveVar->ThresholdMUnit=CmdReqThresholdHLMeasureLineMoveVar->Item->TransformPixelToUnit(CmdReqThresholdHLMeasureLineMoveVar->ThresholdM);
		CmdReqThresholdHLMeasureLineMoveVar->ThresholdPUnit=CmdReqThresholdHLMeasureLineMoveVar->Item->TransformPixelToUnit(CmdReqThresholdHLMeasureLineMoveVar->ThresholdP);
		return;
	}
}

//bool	MeasureLineMoveBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
//{
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
//	return true;
//}

bool	MeasureLineMoveBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==ReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==SendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*MeasureLineMoveBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==ReqThresholdReqCommand){
		return new LineMoveThresholdReq();
	}
	else if(Command==ReqThresholdSendCommand){
		LineMoveThresholdSend	*pSend=new LineMoveThresholdSend();
		if(reqData!=NULL){
			LineMoveThresholdReq	*req=(LineMoveThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ReqTryThresholdCommand){
		return new LineMoveReqTryThreshold();
	}
	else if(Command==SendTryThresholdCommand){
		LineMoveSendTryThreshold	*pSend=new LineMoveSendTryThreshold();
		if(reqData!=NULL){
			LineMoveReqTryThreshold	*req=(LineMoveReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}

	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	MeasureLineMoveBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==ReqThresholdReqCommand){
		LineMoveThresholdReq	*p=(LineMoveThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==ReqThresholdSendCommand){
		LineMoveThresholdSend	*p=(LineMoveThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==ReqTryThresholdCommand){
		LineMoveReqTryThreshold	*p=(LineMoveReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==SendTryThresholdCommand){
		LineMoveSendTryThreshold	*p=(LineMoveSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	MeasureLineMoveBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==ReqThresholdReqCommand){
		LineMoveThresholdReq	*p=(LineMoveThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==ReqThresholdSendCommand){
		LineMoveThresholdSend	*p=(LineMoveThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==ReqTryThresholdCommand){
		LineMoveReqTryThreshold	*p=(LineMoveReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==SendTryThresholdCommand){
		LineMoveSendTryThreshold	*p=(LineMoveSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	MeasureLineMoveBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==ReqThresholdReqCommand){
		LineMoveThresholdReq	*p=(LineMoveThresholdReq *)data;
		return true;
	}
	else if(Command==ReqThresholdSendCommand){
		LineMoveThresholdSend	*p=(LineMoveThresholdSend *)data;
		return true;
	}
	else if(Command==ReqTryThresholdCommand){
		LineMoveReqTryThreshold	*p=(LineMoveReqTryThreshold *)data;
		return true;
	}
	else if(Command==SendTryThresholdCommand){
		LineMoveSendTryThreshold	*p=(LineMoveSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}
int	MeasureLineMoveBase::GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)
{
	if(MaxDimCount>=4){
		MenuPointer[0].MenuMessage	=LangSolver.GetString(XMeasureLineMove_LS,LID_7)/*"長さでOK"*/;
		MenuPointer[0].MenuID		=LearningMenu_MeasureLineMove_OK_ByDistance;
		MenuPointer[0].OkMode		=true;
		MenuPointer[1].MenuMessage	=LangSolver.GetString(XMeasureLineMove_LS,LID_8)/*"1側拡大"*/;
		MenuPointer[1].MenuID		=LearningMenu_MeasureLineMove_OK_BySide1;
		MenuPointer[1].OkMode		=true;
		MenuPointer[2].MenuMessage	=LangSolver.GetString(XMeasureLineMove_LS,LID_9)/*"2側拡大"*/;
		MenuPointer[2].MenuID		=LearningMenu_MeasureLineMove_OK_BySide2;
		MenuPointer[2].OkMode		=true;
		return 3;
	}
	return 0;
}
QString	MeasureLineMoveBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XMeasureLineMove_LS,LID_10)/*"測長検査"*/;
}
