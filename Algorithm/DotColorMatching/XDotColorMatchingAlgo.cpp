#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XCriticalFunc.h"
#include "swap.h"

static	int	DbgID=24967;
static	int	DbgLayer=1;
static	int	DbgNumer=0;


ExeResult	DotColorMatchingItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	//MatrixBuffClear(DummyMap,0,MapXByte,MapYLen);
	ResultMultiSpot.RemoveAll();
	ResultMultiSpotGathered.RemoveAll();
	return _ER_true;
}

int	DbgR1;
int	DbgR2;

ExeResult	DotColorMatchingItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID){
		DbgR1++;
	}
	if(MasterPattern==NULL){
		return _ER_true;
	}
	DWORD	StartMilisec=Parent->GetLayersBase()->GetStartInspectionTimeMilisec();

	const DotColorMatchingThreshold	*Th=GetThresholdR();
	DotColorMatchingThreshold		*WTh=GetThresholdW();
	if(Th->EnableT2M==false && Th->EnableM2T==false){
		return _ER_true;
	}
	//if(ProcessMutex.tryLock()==false){
	//	Locked++;
	//}

	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)GetParentBase());
	ExeResult	Ret=_ER_true;
	//if(Th->ScratchEnable==false || ScratchLayer<0){

		int	MaxInspectMilisec=Parent->GetParamGlobal()->MaxInspectMilisec;
		int	MaxNGCountsPerCam=Parent->GetParamGlobal()->MaxNGCountsPerCam;

		int	CurrentAreaSearchX=Clipping(Th->AreaSearchX,Th->MaxAreaSearch);
		if(CurrentAreaSearchX>ABase->MaxAreaSearch){
			CurrentAreaSearchX=ABase->MaxAreaSearch;
		}
		if(FoldingArea==false){
			CurrentAreaSearchX=CurrentAreaSearchX*ABase->MultiplyParamInFoldingArea;
		}
		else
		if(OutlineArea==true){
			double	MultiplyParamInOutlineArea=ABase->MultiplyParamInOutlineArea;
			CurrentAreaSearchX=CurrentAreaSearchX*MultiplyParamInOutlineArea;
		}
		if(OutlineBlock==true){
			CurrentAreaSearchX=CurrentAreaSearchX*2;
		}

		int	CurrentAreaSearchY=Clipping(Th->AreaSearchY,Th->MaxAreaSearch);
		if(CurrentAreaSearchY>ABase->MaxAreaSearch){
			CurrentAreaSearchY=ABase->MaxAreaSearch;
		}
		if(FoldingArea==false){
			CurrentAreaSearchY=CurrentAreaSearchY*ABase->MultiplyParamInFoldingArea;
		}
		else
		if(OutlineArea==true){
			double	MultiplyParamInOutlineArea=ABase->MultiplyParamInOutlineArea;
			CurrentAreaSearchY=CurrentAreaSearchY*MultiplyParamInOutlineArea;
		}
		if(OutlineBlock==true){
			CurrentAreaSearchY=CurrentAreaSearchY*2;
		}
		Ret=ExecuteProcessing(Res 
							,Th,&Th->Broad
							,CurrentAreaSearchX,CurrentAreaSearchY,0);

		if(Res->GetError()==2 || Res->GetError()==3){
			//if(ABase->ModeMatchHighPrecise==true){
			if(Th->PreciseSearch==true){
				if(ExecuteProcessingDetail(Res,Th,&Th->Broad)==true){
					goto	JudgeOK;
				}
			}		
		}
JudgeOK:
		if(Res->GetError()>=2){
			if(GetLayersBase()->GetResultFromAlgorithm()==0){
				GetLayersBase()->SetResultFromAlgorithm(1);
			}
			for(ResultPosList *Pos=Res->GetPosListFirst();Pos!=NULL;Pos=Pos->GetNext()){
				int	d=Pos->result&0xFF;
				if(d==0){
					WTh->AddHist(Hist_DotColorMatching_NGSize,(int)Pos->GetResult1());
				}
				else if(d==2){
					WTh->AddHist(Hist_DotColorMatching_NGLength,(int)Pos->GetResult2());
				}
			}
		}
		if(Res->GetError()==1 && Th->Narrow.OKDot!=0){
			ResetProcessDone();
			ExecuteProcessingNoAlignmentFixed(Res
											,Th,&Th->Narrow
											,Res->GetItemSearchedX(),Res->GetItemSearchedY()
											,Res->GetAlignedX() ,Res->GetAlignedY());
		}
	if(Th->ScratchEnable==true && ScratchLayer>=0 && Res->IsOk()==true){
		int	Mx,My;
		GetAlignmentShift(Mx,My);
		if(CheckInAreaAfterShift(Mx ,My ,10,10)==true){
			ImageBuffer *ImageTargetList[100];
			GetTargetBuffList(ImageTargetList);
			int	kx=0;
			int	ky=0;
			RotationPattern	*R=CurrentMasterPattern;
			int	LoopCountX=Clipping(Th->AreaSearchX,Th->MaxAreaSearch);
			int	LoopCountY=Clipping(Th->AreaSearchY,Th->MaxAreaSearch);
			if(HasHOrVLine()==false || SearchType==1){
				ExecuteSearchByPattern(ImageTargetList,LoopCountX,LoopCountY,Mx,My
															,kx ,ky);
			}
			else if(R->DivArea.IsNull()==false){
				ExecuteSearchByPattern(ImageTargetList,LoopCountX,LoopCountY,Mx,My
																,kx ,ky);
			}
			Mx+=kx;
			My+=ky;

			Res->SetAlignedXY(Mx,My);

			int		tScratchResultWidth=0;
			float	tScratchResultPeakH=0;
			float	tScratchResultPeakL=0;
			int	Cx,Cy;
			GetArea().GetCenter(Cx,Cy);
			double	sd=2.5;	//2.0;
			double	MaxNGDifference=0;
			double	MaxS=0;
			double	MaxOKDifference=0;
			double	MaxOKS=0;
			int ResultX ,ResultY;
			bool	ResultNG=false;
			double	TotalMaxCoef=0;
			double	TotalMinCoef=0;
			double	MinAngle=0;
			int		Isolation=4;
			if(Th->ScratchRotationAngle>0){
				for(double s=0;s<=Th->ScratchRotationAngle;s+=sd){
					if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
						break;
					}
					if(Parent->GetNGCounter()>=MaxNGCountsPerCam){
						break;
					}
					double	RAngleDegree=s+Th->ScratchStartDirection;
					double	NGDifference;
					float	tScratchResultVariety;
					double	MaxCoef;
					double	MinCoef;
					int		NGPos;
					if(ExecuteProcessingScratch(Res 
											,CurrentMasterPattern->Angle
											,Cx,Cy ,Mx,My
											,RAngleDegree
											,NGDifference,ScratchResultWidth
											,tScratchResultPeakH ,tScratchResultPeakL
											,tScratchResultVariety
											,ResultX ,ResultY
											,MaxCoef,MinCoef
											,NGPos
											,false,ScratchTableDim,Isolation)==false){
						if(MaxNGDifference<fabs(NGDifference)){
							MaxNGDifference=fabs(NGDifference);
							MaxS=RAngleDegree-Th->ScratchStartDirection;
							ResultNG=true;
						}
					}
					else{
						if(TotalMinCoef>MinCoef){
							TotalMinCoef=MinCoef;
							MinAngle=RAngleDegree;
							MaxOKS=RAngleDegree-Th->ScratchStartDirection;
						}
						if(TotalMaxCoef<MaxCoef){
							TotalMaxCoef=MaxCoef;
							MaxOKS=RAngleDegree-Th->ScratchStartDirection;
						}
						if(MaxOKDifference<fabs(NGDifference)){
							MaxOKDifference=fabs(NGDifference);
							MaxOKS=RAngleDegree-Th->ScratchStartDirection;
						}
					}
				}
				if(ResultNG==false && TotalMinCoef<0 && Th->ScratchDetectLevelL>0){
					double	Q=-TotalMinCoef/Th->ScratchDetectLevelL;
					Isolation=2;
					if(Th->ScratchRotationAngle>0 && Q>0.8){
						for(int div=0;div<4;div++){
							if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
								break;
							}
							if(Parent->GetNGCounter()>=MaxNGCountsPerCam){
								break;
							}
							TotalMinCoef=0;
							sd *=0.5;
							for(int r=-1;r<=1;r++){
								double	RAngleDegree=MinAngle+r*sd;
								double	NGDifference;
								float	tScratchResultVariety;
								double	MaxCoef;
								double	MinCoef;
								int		NGPos;
								if(ExecuteProcessingScratch(Res 
														,CurrentMasterPattern->Angle
														,Cx,Cy ,Mx,My
														,RAngleDegree
														,NGDifference,ScratchResultWidth
														,tScratchResultPeakH ,tScratchResultPeakL
														,tScratchResultVariety
														,ResultX ,ResultY
														,MaxCoef,MinCoef
														,NGPos
														,false,ScratchTableDim,Isolation)==false){
									if(MaxNGDifference<fabs(NGDifference)){
										MaxNGDifference=fabs(NGDifference);
										MaxS=RAngleDegree-Th->ScratchStartDirection;
										ResultNG=true;
										goto	FoundNG;
										
									}
								}
								else{
									if(TotalMinCoef>MinCoef){
										TotalMinCoef=MinCoef;
										MinAngle=RAngleDegree;
										MaxS=RAngleDegree-Th->ScratchStartDirection;
									}
									if(MaxOKDifference<fabs(NGDifference)){
										MaxOKDifference=fabs(NGDifference);
										MaxOKS=RAngleDegree-Th->ScratchStartDirection;
									}
								}
							}
							if(TotalMinCoef>=0.0){
								break;
							}
						}
					}
				}
				FoundNG:;
				double	NGDifference;
				if(ResultNG==true){
					double	RAngle=MaxS+Th->ScratchStartDirection;
					double	MaxCoef;
					double	MinCoef;
					int		MNGPos;
					bool	MRes=ExecuteProcessingScratch(Res 
											,CurrentMasterPattern->Angle
											,Cx,Cy ,0,0
											,RAngle
											,NGDifference,tScratchResultWidth
											,tScratchResultPeakH ,tScratchResultPeakL
											,ScratchResultVariety
											,ResultX ,ResultY
											,MaxCoef,MinCoef
											,MNGPos
											,true,ScratchTableMasterDim,Isolation);
					int		TNGPos;
					bool	TRes=ExecuteProcessingScratch(Res 
											,CurrentMasterPattern->Angle
											,Cx,Cy ,Mx,My
											,RAngle
											,NGDifference,tScratchResultWidth
											,tScratchResultPeakH ,tScratchResultPeakL
											,ScratchResultVariety
											,ResultX ,ResultY
											,MaxCoef,MinCoef
											,TNGPos
											,false,ScratchTableDim,Isolation);

					if(MRes==true && TRes==false && CheckScratchInMaster(ScratchTableMasterDim,TNGPos)==false){
						ResultPosList	*t=new DotColorMatchingResultPosList(ResultX ,ResultY);
						t->SetResult1(ceil(fabs(NGDifference)));
						t->SetResult2(ScratchResultWidth);
						t->result	=0x20000;
						Res->AddPosList(t);
						Res->SetError(5);
					}
					else{
						Res->SetError(1);
					}
				}
				else{
					if(ExeID>=10000){
						double	RAngle=MaxOKS+Th->ScratchStartDirection;
						double	MaxCoef;
						double	MinCoef;
						int		MNGPos;
						ExecuteProcessingScratch(Res 
												,CurrentMasterPattern->Angle
												,Cx,Cy ,0,0
												,RAngle
												,NGDifference,tScratchResultWidth
												,tScratchResultPeakH ,tScratchResultPeakL
												,ScratchResultVariety
												,ResultX ,ResultY
												,MaxCoef,MinCoef
												,MNGPos
												,true,ScratchTableMasterDim,Isolation);
						int		TNGPos;
						ExecuteProcessingScratch(Res 
												,CurrentMasterPattern->Angle
												,Cx,Cy ,Mx,My
												,RAngle
												,NGDifference,tScratchResultWidth
												,tScratchResultPeakH ,tScratchResultPeakL
												,ScratchResultVariety
												,ResultX ,ResultY
												,MaxCoef,MinCoef
												,TNGPos
												,false,ScratchTableDim,Isolation);
					}
					Res->SetError(1);
				}
			}
			else{
				double	RAngleDegree=Th->ScratchStartDirection;
				double	NGDifference;
				float	ScratchResultVariety;
				double	MaxCoef;
				double	MinCoef;
				int		NGPos;
				int		Isolation=1;
				if(ExecuteProcessingScratch(Res 
										,CurrentMasterPattern->Angle
										,Cx,Cy ,Mx,My
										,RAngleDegree
										,NGDifference,tScratchResultWidth
										,tScratchResultPeakH ,tScratchResultPeakL
										,ScratchResultVariety
										,ResultX ,ResultY
										,MaxCoef,MinCoef
										,NGPos
										,false,ScratchTableDim,Isolation)==false){
					ResultPosList	*t=new DotColorMatchingResultPosList(ResultX ,ResultY);
					t->SetResult1(ceil(fabs(NGDifference)));
					t->SetResult2(ScratchResultWidth);
					t->result	=0x20000;
					Res->AddPosList(t);
					Res->SetError(5);
				}
				else{
					Res->SetError(1);
				}
			}
			if(tScratchResultPeakH>ScratchResultPeakH){
				ScratchResultPeakH=tScratchResultPeakH;
				ScratchCounter=0;
			}
			if(tScratchResultPeakL>ScratchResultPeakL){
				ScratchResultPeakL=tScratchResultPeakL;
				ScratchCounter=0;
			}
			ScratchCounter++;
			if(ScratchCounter>=100){
				ScratchResultPeakH=0;
				ScratchResultPeakL=0;
				ScratchCounter=0;
			}
		}
		else{
			Res->SetError(1);
		}
	}
	if(Res->GetError()==1 && Th->RedCheckMode==true){
		ImageBuffer *ImageTargetList[100];
		GetTargetBuffList(ImageTargetList);
		int NGSize;
		int	ResultX, ResultY;
		ExecuteProcessingRed(Res
							, ImageTargetList
							, NGSize
							, ResultX, ResultY
							, 0 ,0);
		if(Th->PreciseSearch==true && Res->GetError()>=2){
			for(int zy=-Th->AreaSearchY;zy<=Th->AreaSearchY;zy+=3){
				for(int zx=-Th->AreaSearchX;zx<=Th->AreaSearchX;zx+=3){
					Res->ClearPosList();
					ResetProcessDone();
					ExecuteProcessingRed(Res
										, ImageTargetList
										, NGSize
										, ResultX, ResultY
										, zx ,zy);
					if(Res->GetError()==1){
						goto	EndRed;
					}
				}
			}
		EndRed:;
		}
	}
	if(Res->GetError()==1 && Th->HsvCheckMode==true){
		ImageBuffer *ImageTargetList[100];
		GetTargetBuffList(ImageTargetList);
		int NGSize;
		int	ResultX, ResultY;
		int	MinX=0,MinY=0;
		int	MinNGSize=99999999;
		int	tAreaSearchX=Clipping(Th->AreaSearchX,Th->MaxAreaSearch);
		int	tAreaSearchY=Clipping(Th->AreaSearchY,Th->MaxAreaSearch);
		for(int dy=-tAreaSearchY;dy<=tAreaSearchY;dy+=2){
			for(int dx=-tAreaSearchX;dx<=tAreaSearchX;dx+=2){
				if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
					goto	EndOfHSVProcess;
				}
				
				int	iRet=ExecuteProcessingHSV(Res
								, ImageTargetList
								, NGSize
								, dx,dy
								, ResultX, ResultY
								,false);
				if(iRet==1){
					MinX=dx;
					MinY=dy;
					goto	HSVOK;
				}
				if(MinNGSize>Res->GetResult2()){
					MinNGSize=Res->GetResult2();
					MinX=dx;
					MinY=dy;
				}
			}
		}
		int	MinX2=0,MinY2=0;
		for(int dy=-1;dy<=1;dy++){
			for(int dx=-1;dx<=1;dx++){
				if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
					goto	EndOfHSVProcess;
				}
				int	iRet=ExecuteProcessingHSV(Res
								, ImageTargetList
								, NGSize
								, MinX+dx ,MinY+dy
								, ResultX, ResultY
								,false);
				if(iRet==1){
					MinX2=dx;
					MinY2=dy;
					MinX+=MinX2;
					MinY+=MinY2;
					goto	HSVOK;
				}
				if(MinNGSize>Res->GetResult2()){
					MinNGSize=Res->GetResult2();
					MinX2=dx;
					MinY2=dy;
				}
			}
		}
		MinX+=MinX2;
		MinY+=MinY2;

		HSVOK:;
		ExecuteProcessingHSV(Res
						, ImageTargetList
						, NGSize
						, MinX,MinY
						, ResultX, ResultY
						,true);
		EndOfHSVProcess:;
	}
	if((Res->GetError()==1 && Th->VariationMode==true && Th->VariationAndLogic==false)
	|| (Res->GetError()>=2 && Th->VariationMode==true && Th->VariationAndLogic==true)){
		ImageBuffer *ImageTargetList[100];
		GetTargetBuffList(ImageTargetList);
		ImageBuffer *ImageMasterList[100];
		GetMasterBuffList(ImageMasterList);
		int	Mx,My;
		Res->SetError(0);
		GetAlignmentShift(Mx,My);
		ExecuteProcessingVariation(Res
								, ImageTargetList
								, ImageMasterList
								, Mx,My);
	}
	if(Res->GetError()==1 && Th->PitMode==true){
		ImageBuffer *ImageTargetList[100];
		GetTargetBuffList(ImageTargetList);
		int	Mx,My;
		GetAlignmentShift(Mx,My);
		ExecuteProcessingPitColor(Res
								,ImageTargetList
								,Mx,My);
	}

	WTh->AddHist(Hist_DotColorMatching_CenterBrightR	,CenterTargetBrightR-CenterBrightR);
	WTh->AddHist(Hist_DotColorMatching_CenterBrightG	,CenterTargetBrightG-CenterBrightG);
	WTh->AddHist(Hist_DotColorMatching_CenterBrightB	,CenterTargetBrightB-CenterBrightB);
	WTh->AddHist(Hist_DotColorMatching_SearchArea	,max(ResultDx,ResultDy));
				
	SetProcessDone();
	//ProcessMutex.unlock();

	GetParent()->IncrementNGCounterWithMutex(Res->GetError());
	//if(GetID()==DbgID){
	//	DbgR1++;
	//}
	return Ret;
}


//int	PlusOr0(int n)
//{
//	if(n<0)	return 0;
//	return n;
//

ExeResult	DotColorMatchingItem::ExecuteProcessingNoAlignment(ResultInItemRoot *Res
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,int AreaDx ,int AreaDy
													,int Mx ,int My
													,int AreaSearchX,int AreaSearchY)

{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *ImageTRTargetList[100];
	GetTargetTRBuffList(ImageTRTargetList);

	MakeShiftBrightness(Th,ImageTargetList,Mx+AreaDx,My+AreaDy);

	int	SelfSearch	=Clipping(Th->SelfSearch,Th->MaxSelfSearch);
	if(MatchingType!=0){
		if(SearchType!=1){
			SelfSearch=SelfSearch/4;
			if(SelfSearch<=1)
				SelfSearch=2;
		}
		else{
			SelfSearch=0;
		}
	}

	int	Skip;
	if(SelfSearch<4)
		Skip=1;
	else if(SelfSearch<15)
		Skip=2;
	else if(SelfSearch<35)
		Skip=3;
	else
		Skip=4;

	FlexArea	*R=CurrentMasterPattern;
	int	MapXPoint=R->GetMinX()-8;
	int	MapYPoint=R->GetMinY()-8;

	int	Error=2;
	int r=ExecuteProcessingLoop	(Res 
								,Th,MTh
								,AreaSearchX,AreaSearchY
								,ImageTargetList,ImageTRTargetList
								//,CDiffR ,CDiffG ,CDiffB
								,Mx+AreaDx,My+AreaDy
								,MapXPoint,MapYPoint
								,SelfSearch ,Skip);
	if(r==1){
		Error=1;
	}

	Res->SetError(Error);	//OK
	ResultSelfSeachDx=ResultDx-Mx;
	ResultSelfSeachDy=ResultDy-My;

	SetProcessDone();
	
	return _ER_true;
}


ExeResult	DotColorMatchingItem::ExecuteProcessingNoAlignmentFixed(ResultInItemRoot *Res
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,int AreaDx ,int AreaDy
													,int Mx ,int My)

{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *ImageTRTargetList[100];
	GetTargetTRBuffList(ImageTRTargetList);

	MakeShiftBrightness(Th,ImageTargetList,Mx+AreaDx,My+AreaDy);

	int	SelfSearch	=Clipping(Th->SelfSearch,Th->MaxSelfSearch);
	if(MatchingType!=0){
		if(SearchType!=1){
			SelfSearch=SelfSearch/4;
			if(SelfSearch<=1)
				SelfSearch=2;
		}
		else{
			SelfSearch=0;
		}
	}

	int	Skip;
	if(SelfSearch<4)
		Skip=1;
	else if(SelfSearch<15)
		Skip=2;
	else if(SelfSearch<35)
		Skip=3;
	else
		Skip=4;

	FlexArea	*R=CurrentMasterPattern;
	int	MapXPoint=R->GetMinX()-8;
	int	MapYPoint=R->GetMinY()-8;

	int	Error=2;
	int r=ExecuteProcessingLoopFixed	(Res
								,Th,MTh
								,ImageTargetList,ImageTRTargetList
								//,CDiffR ,CDiffG ,CDiffB
								,Mx+AreaDx,My+AreaDy
								,MapXPoint,MapYPoint
								,SelfSearch ,Skip);
	if(r==1){
		Error=1;
	}

	Res->SetError(Error);	//OK
	ResultSelfSeachDx=ResultDx-Mx;
	ResultSelfSeachDy=ResultDy-My;

	SetProcessDone();
	
	return _ER_true;
}

ExeResult	DotColorMatchingItem::ExecuteProcessingNoAlignmentFixedNGCount(ResultInItemRoot *Res
											,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
											,int AreaDx ,int AreaDy
											,int Mx ,int My
											,int &NGLCount,int &NGHCount)

{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *ImageTRTargetList[100];
	GetTargetTRBuffList(ImageTRTargetList);

	MakeShiftBrightness(Th,ImageTargetList,Mx+AreaDx,My+AreaDy);

	int	SelfSearch	=Clipping(Th->SelfSearch,Th->MaxSelfSearch);
	if(MatchingType!=0){
		if(SearchType!=1){
			SelfSearch=SelfSearch/4;
			if(SelfSearch<=1)
				SelfSearch=2;
		}
		else{
			SelfSearch=0;
		}
	}

	int	Skip;
	if(SelfSearch<4)
		Skip=1;
	else if(SelfSearch<15)
		Skip=2;
	else if(SelfSearch<35)
		Skip=3;
	else
		Skip=4;

	FlexArea	*R=CurrentMasterPattern;
	int	MapXPoint=R->GetMinX()-8;
	int	MapYPoint=R->GetMinY()-8;

	int	Error=2;
	int r=ExecuteProcessingLoopFixedNGCount	(Res
								,Th,MTh
								,ImageTargetList,ImageTRTargetList
								//,CDiffR ,CDiffG ,CDiffB
								,Mx+AreaDx,My+AreaDy
								,MapXPoint,MapYPoint
								,SelfSearch ,Skip
								,NGLCount,NGHCount);
	if(r==1){
		Error=1;
	}

	Res->SetError(Error);	//OK
	ResultSelfSeachDx=ResultDx-Mx;
	ResultSelfSeachDy=ResultDy-My;

	SetProcessDone();
	
	return _ER_true;
}
int	DotColorMatchingItem::ExecuteProcessingLoop	(ResultInItemRoot *Res 
												,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
												,int LoopCountX,int LoopCountY
												,ImageBuffer *ImageTargetList[100],ImageBuffer *ImageTRTargetList[100]
												//,int	CDiffR ,int	CDiffG ,int	CDiffB
												,int Mx,int My
												,int MapXPoint,int MapYPoint
												,int SelfSearch ,int Skip)
{
	int	kx=0;
	int	ky=0;
	RotationPattern	*R=CurrentMasterPattern;
	if(HasHOrVLine()==false || SearchType==1){
		ExecuteSearchByPattern(ImageTargetList,LoopCountX,LoopCountY,Mx,My
													,kx ,ky);
		MakeShiftBrightness(Th,ImageTargetList,Mx+kx,My+ky);
	}
	else if(R->DivArea.IsNull()==false){
		if(SearchType!=8){
			LoopCountX=2;
			LoopCountY=2;
			ExecuteSearchByPattern(ImageTargetList,LoopCountX,LoopCountY,Mx,My
														,kx ,ky);
			MakeShiftBrightness(Th,ImageTargetList,Mx+kx,My+ky);
		}
		else{
			LoopCountX/=2;
			if(LoopCountX<2)
				LoopCountX=2;
			LoopCountY/=2;
			if(LoopCountY<2)
				LoopCountY=2;
			ExecuteSearchByPattern(ImageTargetList,LoopCountX,LoopCountY,Mx,My
														,kx ,ky);
			MakeShiftBrightness(Th,ImageTargetList,Mx+kx,My+ky);
		}
	}
	Res->ClearPosList();
	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int	Ret=ExecuteProcessingLoopN(Res
							,Th,MTh
							,ImageTargetList,ImageTRTargetList
							//,CDiffR ,CDiffG ,CDiffB
							, Mx+kx, My+ky
							, MapXPoint, MapYPoint
							, SelfSearch , Skip);
	return Ret;
}

int	DotColorMatchingItem::ExecuteProcessingLoopFixed	(ResultInItemRoot *Res
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,ImageBuffer *ImageTargetList[100],ImageBuffer *ImageTRTargetList[100]
													//,int	CDiffR ,int	CDiffG ,int	CDiffB
													,int Mx,int My
													,int MapXPoint,int MapYPoint
													,int SelfSearch ,int Skip)
{
	int	kx=0;
	int	ky=0;
	RotationPattern	*R=CurrentMasterPattern;
	if(HasHOrVLine()==false || SearchType==1){
		MakeShiftBrightness(Th,ImageTargetList,Mx,My);
	}
	else if(R->DivArea.IsNull()==false){
		MakeShiftBrightness(Th,ImageTargetList,Mx,My);
	}
	Res->ClearPosList();
	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int	Ret=ExecuteProcessingLoopN(Res
							,Th,MTh
							,ImageTargetList,ImageTRTargetList
							//,CDiffR ,CDiffG ,CDiffB
							, Mx, My
							, MapXPoint, MapYPoint
							, SelfSearch , Skip);
	return Ret;
}

int	DotColorMatchingItem::ExecuteProcessingLoopFixedNGCount	(ResultInItemRoot *Res
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,ImageBuffer *ImageTargetList[100],ImageBuffer *ImageTRTargetList[100]
													//,int	CDiffR ,int	CDiffG ,int	CDiffB
													,int Mx,int My
													,int MapXPoint,int MapYPoint
													,int SelfSearch ,int Skip
													,int &NGLCount,int &NGHCount)
{
	int	kx=0;
	int	ky=0;
	RotationPattern	*R=CurrentMasterPattern;
	if(HasHOrVLine()==false || SearchType==1){
		MakeShiftBrightness(Th,ImageTargetList,Mx,My);
	}
	else if(R->DivArea.IsNull()==false){
		MakeShiftBrightness(Th,ImageTargetList,Mx,My);
	}
	Res->ClearPosList();
	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int	Ret=ExecuteProcessingLoopNNGCount(Res
							,Th,MTh
							,ImageTargetList,ImageTRTargetList
							//,CDiffR ,CDiffG ,CDiffB
							, Mx, My
							, MapXPoint, MapYPoint
							, SelfSearch , Skip
							,NGLCount,NGHCount);
	return Ret;
}

int	SDimFunc(const void *a ,const void *b)
{
	if(((struct	XYRateStruct *)a)->Rate<((struct XYRateStruct *)b)->Rate)
		return 1;
	else
	if(((struct	XYRateStruct *)a)->Rate>((struct XYRateStruct *)b)->Rate)
		return -1;
	return 0;
}

bool	DotColorMatchingItem::ExecuteSearchByPattern(ImageBuffer *ImageTargetList[100]
													,int LoopCountX,int LoopCountY,int Mx,int My
													,int &kx ,int &ky)
{
	double	MaxD=0;
	kx=0;
	ky=0;
	struct	XYRateStruct	SDim[10000];
	int	SDimNumb=0;
	int	PatternEdgeWidth=((DotColorMatchingBase *)GetParentBase())->PatternEdgeWidth*2;
	RotationPattern	*R=CurrentMasterPattern;
	if(R->DivArea.IsNull()==false){
		if(LoopCountX<=3 && LoopCountY<=3){
			if(R->DivArea.IsNull()==true){
				MaxD=R->SearchMatchByArea(ImageTargetList[R->AdoptLayer] ,LoopCountX,LoopCountY,Mx,My ,kx,ky);
			}
			else{
				if(LoopCountX>=2 & LoopCountY>=2){
					if(R->FlatAreaWidth>=PatternEdgeWidth){
						int	LKx=0;
						int	LKy=0;
						int	SSSep=3;
						for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSSep){
							for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSSep){
								double	D=CalcMatchByAreaEdgeRough(ImageTargetList ,Mx+dx ,My+dy);
								if(MaxD<D){
									MaxD=D;
									kx=LKx=dx;
									ky=LKy=dy;
								}
							}
						}
						MaxD=R->SearchMatchByArea(ImageTargetList[R->AdoptLayer] ,1,1,Mx+LKx,My+LKy ,kx,ky);
					}
					else{
						MaxD=R->SearchMatchByArea(ImageTargetList[R->AdoptLayer] ,LoopCountX,LoopCountY,Mx,My ,kx,ky);
					}
				}
				else{
					if(R->FlatAreaWidth>=PatternEdgeWidth){
						for(int dy=-LoopCountY;dy<=LoopCountY;dy++){
							for(int dx=-LoopCountX;dx<=LoopCountX;dx++){
								double	D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
								if(MaxD<D){
									MaxD=D;
									kx=dx;
									ky=dy;
								}
							}
						}
					}
					else{
						MaxD=R->SearchMatchByArea(ImageTargetList[R->AdoptLayer] ,LoopCountX,LoopCountY,Mx,My ,kx,ky);
					}
				}
			}
		}
		else{
			int	SSkip=2;
			int	tKx=0;
			int	tKy=0;
			if(R->EffectiveSkip==true && R->FlatAreaWidth>=PatternEdgeWidth){
				if(LoopCountX<=5 && LoopCountY<=5){
					SSkip=2;
					for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
						for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
							double	D;
							if(R->DivArea.IsNull()==true){
								D=CalcMatchByAreaSkip(ImageTargetList ,Mx+dx ,My+dy);
							}
							else{
								D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
							}
							if(SDimNumb<sizeof(SDim)/sizeof(SDim[0])){
								SDim[SDimNumb].Dx=dx;
								SDim[SDimNumb].Dy=dy;
								SDim[SDimNumb].Rate=D;
								SDimNumb++;
							}
						}
					}
					for(int dy=-LoopCountY+1;dy<=LoopCountY;dy+=SSkip){
						for(int dx=-LoopCountX+1;dx<=LoopCountX;dx+=SSkip){
							double	D;
							if(CurrentMasterPattern->DivArea.IsNull()==true){
								D=CalcMatchByAreaSkip(ImageTargetList ,Mx+dx ,My+dy);
							}
							else{
								D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
							}
							if(SDimNumb<sizeof(SDim)/sizeof(SDim[0])){
								SDim[SDimNumb].Dx=dx;
								SDim[SDimNumb].Dy=dy;
								SDim[SDimNumb].Rate=D;
								SDimNumb++;
							}
						}
					}
				}
				else{
					SSkip=4;
					for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
						for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
							double	D;
							if(R->DivArea.IsNull()==true){
								D=CalcMatchByAreaSkip(ImageTargetList ,Mx+dx ,My+dy);
							}
							else{
								D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
							}
							if(D>0 && SDimNumb<sizeof(SDim)/sizeof(SDim[0])){
								SDim[SDimNumb].Dx=dx;
								SDim[SDimNumb].Dy=dy;
								SDim[SDimNumb].Rate=D;
								SDimNumb++;
							}
						}
					}
					for(int dy=-LoopCountY+2;dy<=LoopCountY;dy+=SSkip){
						for(int dx=-LoopCountX+2;dx<=LoopCountX;dx+=SSkip){
							double	D;
							if(CurrentMasterPattern->DivArea.IsNull()==true){
								D=CalcMatchByAreaSkip(ImageTargetList ,Mx+dx ,My+dy);
							}
							else{
								D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
							}
							if(D>0 && SDimNumb<sizeof(SDim)/sizeof(SDim[0])){
								SDim[SDimNumb].Dx=dx;
								SDim[SDimNumb].Dy=dy;
								SDim[SDimNumb].Rate=D;
								SDimNumb++;
							}
						}
					}
				}
				QSort(SDim,SDimNumb,sizeof(SDim[0]),SDimFunc,false3);
				int	DNumb=SDimNumb/10;
				if(DNumb<5){
					DNumb=SDimNumb/2;
					if(DNumb<5){
						DNumb=SDimNumb;
					}
				}
				if(DNumb>6)
					DNumb=6;
				MaxD=0;
				for(int i=0;i<DNumb;i++){
					double	D=CalcMatchByArea(ImageTargetList ,Mx+SDim[i].Dx ,My+SDim[i].Dy);
					if(D>MaxD){
						MaxD=D;
						kx=tKx=SDim[i].Dx;
						ky=tKy=SDim[i].Dy;
					}
				}
			}
			else if(R->FlatAreaWidth>=PatternEdgeWidth){
				for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
					for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
						double	D=CalcMatchByArea(ImageTargetList ,Mx+dx ,My+dy);
						if(MaxD<D){
							MaxD=D;
							kx=tKx=dx;
							ky=tKy=dy;
						}
					}
				}
				for(int dy=-LoopCountY+1;dy<=LoopCountY;dy+=SSkip){
					for(int dx=-LoopCountX+1;dx<=LoopCountX;dx+=SSkip){
						double	D=CalcMatchByArea(ImageTargetList ,Mx+dx ,My+dy);
						if(MaxD<D){
							MaxD=D;
							kx=tKx=dx;
							ky=tKy=dy;
						}
					}
				}
			}
			else if(R->DivIsClosedToOutline==true && R->FlatPattern==true && R->DivArea.IsNull()==false){
				SSkip=1;
				for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
					for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
						double	D;
						D=CalcMatchByAreaEdge(ImageTargetList ,Mx+dx ,My+dy);
						if(MaxD<D){
							MaxD=D;
							kx=tKx=dx;
							ky=tKy=dy;
						}
					}
				}
				return true;
			}
			else{
				MaxD=R->SearchMatchByArea(ImageTargetList[R->AdoptLayer] ,LoopCountX,LoopCountY,Mx,My ,kx,ky);
				return true;
			}
			MaxD=0;
			int	HSkip=SSkip-1;

			if(HSkip>=2){
				int	iKx=0;
				int	iKy=0;
				for(int dy=-HSkip;dy<=HSkip;dy+=2){
					for(int dx=-HSkip;dx<=HSkip;dx+=2){
						double	D=CalcMatchByArea(ImageTargetList ,Mx+tKx+dx ,My+tKy+dy);
						if(MaxD<D){
							MaxD=D;
							iKx=tKx+dx;
							iKy=tKy+dy;
						}
					}
				}
				kx=iKx;
				ky=iKy;
				for(int dy=-1;dy<=1;dy++){
					for(int dx=-1;dx<=1;dx++){
						if(dx==0 && dy==0)
							continue;
						double	D=CalcMatchByArea(ImageTargetList ,Mx+iKx+dx ,My+iKy+dy);
						if(MaxD<D){
							MaxD=D;
							kx=iKx+dx;
							ky=iKy+dy;
						}
					}
				}
			}
			else{
				for(int dy=-HSkip;dy<=HSkip;dy++){
					for(int dx=-HSkip;dx<=HSkip;dx++){
						double	D=CalcMatchByArea(ImageTargetList ,Mx+tKx+dx ,My+tKy+dy);
						if(MaxD<D){
							MaxD=D;
							kx=tKx+dx;
							ky=tKy+dy;
						}
					}
				}
			}
		}
	}
	else{
		if(LoopCountX==0 && LoopCountY==0){
			kx=0;
			ky=0;
		}
		else
		if(LoopCountX==1 && LoopCountY==1){
			MaxD=0.0;
			for(int dy=-1;dy<=1;dy++){
				for(int dx=-1;dx<=1;dx++){
					double	D=CalcMatchByArea(ImageTargetList ,Mx+dx ,My+dy);
					if(MaxD<D){
						MaxD=D;
						kx=dx;
						ky=dy;
					}
				}
			}
		}
		else
		if(LoopCountX<=3 && LoopCountY<=3){
			MaxD=0.0;
			int	MaxDx=0;
			int	MaxDy=0;
			int	StepX=(LoopCountX!=0)?LoopCountX:1;
			int	StepY=(LoopCountY!=0)?LoopCountY:1;
			for(int dy=-LoopCountY;dy<=LoopCountY;dy+=StepY){
				for(int dx=-LoopCountX;dx<=LoopCountX;dx+=StepX){
					double	D=CalcMatchByArea(ImageTargetList ,Mx+dx ,My+dy);
					if(MaxD<D){
						MaxD=D;
						MaxDx=dx;
						MaxDy=dy;
					}
				}
			}
			MaxD=0.0;
			for(int dy=-1;dy<=1;dy++){
				for(int dx=-1;dx<=1;dx++){
					double	D=CalcMatchByArea(ImageTargetList ,Mx+MaxDx+dx ,My+MaxDy+dy);
					if(MaxD<D){
						MaxD=D;
						kx=MaxDx+dx;
						ky=MaxDy+dy;
					}
				}
			}
		}
		else if(R->FlatPattern==true){
			int	SSkip=4;	//3;
			int	tKx=0;
			int	tKy=0;
			for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
				for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
					//double	D=CalcMatchByAreaFlat(ImageTargetList ,Mx+dx ,My+dy);
					double	D=CalcMatchByAreaFlatRough(ImageTargetList ,Mx+dx ,My+dy);
					if(MaxD<D){
						MaxD=D;
						kx=tKx=dx;
						ky=tKy=dy;
					}
				}
			}
			MaxD=0;
			int	rKx=0;
			int	rKy=0;
			for(int dy=-SSkip;dy<=SSkip;dy+=2){
				for(int dx=-SSkip;dx<=SSkip;dx+=2){
					double	D=CalcMatchByAreaFlatRough(ImageTargetList ,Mx+tKx+dx ,My+tKy+dy);	//?
					if(MaxD<D){
						MaxD=D;
						rKx=dx;
						rKy=dy;
					}
				}
			}
			//MaxD=0;
			for(int dy=-1;dy<=1;dy++){
				for(int dx=-1;dx<=1;dx++){
					if(dx==0 && dy==0)
						continue;
					double	D=CalcMatchByAreaFlat(ImageTargetList ,Mx+tKx+rKx+dx ,My+tKy+rKy+dy);
					if(MaxD<D){
						MaxD=D;
						kx=tKx+rKx+dx;
						ky=tKy+rKy+dy;
					}
				}
			}
		}
		else{
			int	SSkip=3;
			for(int dy=-LoopCountY;dy<=LoopCountY;dy+=SSkip){
				for(int dx=-LoopCountX;dx<=LoopCountX;dx+=SSkip){
					//double	D=CalcMatchByAreaFlat(ImageTargetList ,Mx+dx ,My+dy);
					double	D=CalcMatchByAreaSkip(ImageTargetList ,Mx+dx ,My+dy);

					if(D>0 && SDimNumb<sizeof(SDim)/sizeof(SDim[0])){
						SDim[SDimNumb].Dx=dx;
						SDim[SDimNumb].Dy=dy;
						SDim[SDimNumb].Rate=D;
						SDimNumb++;
					}
					/*
					if(MaxD<D){
						MaxD=D;
						kx=tKx=dx;
						ky=tKy=dy;
					}
					*/
				}
			}

			QSort(SDim,SDimNumb,sizeof(SDim[0]),SDimFunc,false3);
			int	DNumb=0;
			/*
			int	DNumb=SDimNumb/10;
			if(DNumb<4){
				DNumb=SDimNumb/3;
				if(DNumb<4){
					DNumb=SDimNumb;
				}
			}
			*/
			struct	XYRateStruct	SpDim[10];
			SpDim[0]=SDim[0];
			int	NSSkip=2;	//3;
			for(int i=1;i<SDimNumb && DNumb<3;i++){
				int	j;
				for(j=0;j<i;j++){
					if(abs(SDim[j].Dx-SDim[i].Dx)<=NSSkip && abs(SDim[j].Dy-SDim[i].Dy)<=NSSkip)
						continue;
				}
				if(j>=i){
					SpDim[DNumb]=SDim[i];
					DNumb++;
				}
			}

			int	ikx=SpDim[0].Dx;
			int	iky=SpDim[0].Dy;
			MaxD=0;
			for(int i=0;i<DNumb;i++){
				for(int dy=-NSSkip;dy<=NSSkip;dy+=2){
					for(int dx=-NSSkip;dx<=NSSkip;dx+=2){
						if(-LoopCountX<=(SpDim[i].Dx+dx) && (SpDim[i].Dx+dx)<=LoopCountX
						&& -LoopCountY<=(SpDim[i].Dy+dy) && (SpDim[i].Dy+dy)<=LoopCountY){
							double	D=CalcMatchByAreaSkip(ImageTargetList ,Mx+SpDim[i].Dx+dx ,My+SpDim[i].Dy+dy);	//?
							if(MaxD<D){
								MaxD=D;
								ikx=SpDim[i].Dx+dx;
								iky=SpDim[i].Dy+dy;
							}
						}
					}
				}
				MaxD=0;
				kx=ikx;
				ky=iky;
				for(int dy=-1;dy<=1;dy++){
					for(int dx=-1;dx<=1;dx++){
						//if(dx==0 && dy==0)
						//	continue;
						if(-LoopCountX<=(ikx+dx) && (ikx+dx)<=LoopCountX
						&& -LoopCountY<=(iky+dy) && (iky+dy)<=LoopCountY){
							double	D=CalcMatchByArea(ImageTargetList ,Mx+dx+ikx ,My+dy+iky);
							if(MaxD<D){
								MaxD=D;
								kx=dx+ikx;
								ky=dy+iky;
							}
						}
					}
				}
			}
		}
	}

	return true;
}


bool	DotColorMatchingItem::ExecuteProcessingFixed(ResultInItemRoot *Res 
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,int Mx ,int My)
{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	ImageBuffer *ImageTargetList[100];
	GetTargetBuffList(ImageTargetList);
	ImageBuffer *ImageTRTargetList[100];
	GetTargetTRBuffList(ImageTRTargetList);

	MakeShiftBrightness(Th,ImageTargetList,Mx,My);

	int	SelfSearch	=Clipping(Th->SelfSearch,Th->MaxSelfSearch);
	if(MatchingType!=0)
		SelfSearch=0;

	int	Skip;
	if(SelfSearch<4)
		Skip=1;
	else if(SelfSearch<15)
		Skip=2;
	else if(SelfSearch<35)
		Skip=3;
	else
		Skip=4;

	FlexArea	*R=CurrentMasterPattern;
	int	MapXPoint=R->GetMinX()-8;
	int	MapYPoint=R->GetMinY()-8;

	Res->ClearPosList();
	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int	r=ExecuteProcessingLoopN(Res
							,Th,MTh
							,ImageTargetList,ImageTRTargetList
							//,CDiffR ,CDiffG ,CDiffB
							, Mx, My
							, MapXPoint, MapYPoint
							, SelfSearch , Skip);
	SetProcessDone();
	if(r==1){
		Res->SetError(1);	//OK
		return true;
	}
	else{
		Res->SetError(r);	//NG
		return false;
	}
}

int	DotColorMatchingItem::ExecuteProcessingLoopN(ResultInItemRoot *Res
												,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,ImageBuffer *ImageTargetList[100]
														,ImageBuffer *ImageTRTargetList[100]
														//,int	CDiffR ,int	CDiffG ,int	CDiffB
														,int Mx,int My
														,int MapXPoint,int MapYPoint
														,int SelfSearch ,int Skip)
{
	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)GetParentBase());

	int	NoiseBrightness		=ABase->NoiseBrightness;
	int	AcceptionRateGray	=ABase->AcceptionRateGray;
	int	mx=Mx;
	int	my=My;

	int NGCount1;
	int NGCount2;
	int GrayDotsM=0;
	int GrayDotsT=0;
	int	LayerNumb=GetLayerNumb();
	DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();
	if(LayerNumb>=3 && Th->UseOneLayer==0xFF){
		bool	VarietyMode=false;
		if(AP->VarietyMap[0].IsValid()==true
		&& AP->VarietyMap[1].IsValid()==true
		&& AP->VarietyMap[2].IsValid()==true){
			VarietyMode=true;
		}
		ImageBufferFast	*TBuff[3];
		TBuff[0]=new ImageBufferFast(ImageTargetList[0]);
		TBuff[1]=new ImageBufferFast(ImageTargetList[1]);
		TBuff[2]=new ImageBufferFast(ImageTargetList[2]);
		if(Th->UseMaster2==true
		&& GetCountOnlyMasterBuff()>1){
			if(VarietyMode==false){
				CalcInside2(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,GrayDotsM
						,GrayDotsT
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		
			}
			else{
				CalcInside2WithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,GrayDotsM
						,GrayDotsT
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		else if(SubBlock.GetFirst()!=NULL){
			if(VarietyMode==false){
				CalcInsideSubtract(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
			else{
				CalcInsideSubtractWithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		else{
			if(VarietyMode==false){
				CalcInside1(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
			else{
				CalcInside1WithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGCount1
						,NGCount2
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		delete	TBuff[0];
		delete	TBuff[1];
		delete	TBuff[2];
	}
	else{
		bool	VarietyMode=false;
		if(AP->VarietyMap[0].IsValid()==true){
			VarietyMode=true;
		}
		int	Layer=Clipping((int)Th->UseOneLayer,0,LayerNumb-1);
		//int	CDiff;
		if(Layer==0){
			CDiffL=CDiffRL;
			CDiffH=CDiffRH;
		}
		else if(Layer==1){
			CDiffL=CDiffGL;
			CDiffH=CDiffGH;
		}
		else if(Layer==2){
			CDiffL=CDiffBL;
			CDiffH=CDiffBH;
		}
		else{
			CDiffL=0;
			CDiffH=0;
		}
		ImageBufferFast	*TBuff[3];
		TBuff[0]=new ImageBufferFast(ImageTargetList[0]);
		if(LayerNumb>=2){
			TBuff[1]=new ImageBufferFast(ImageTargetList[1]);
		}
		else{
			TBuff[1]=NULL;
		}
		if(LayerNumb>=3){
			TBuff[2]=new ImageBufferFast(ImageTargetList[2]);
		}
		else{
			TBuff[2]=NULL;
		}
		if(VarietyMode==false){
			CalcInsideMono(Th,MTh
					,*TBuff[Layer],*ImageTRTargetList[Layer]
					,Layer
					,mx ,my
					,Skip ,SelfSearch 
					//,CDiff 
					,NoiseBrightness
					,MapXPoint ,MapYPoint
					,NGCount1
					,NGCount2
					,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		}
		else{
			CalcInsideMonoWithVariety(Th,MTh
					,*TBuff[Layer],*ImageTRTargetList[Layer]
					,Layer
					,mx ,my
					,Skip ,SelfSearch 
					//,CDiff 
					,NoiseBrightness
					,MapXPoint ,MapYPoint
					,NGCount1
					,NGCount2
					,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		}
			
		delete	TBuff[0];
		delete	TBuff[1];
		delete	TBuff[2];
	}
	int	OKGrayArea=GetArea().GetPatternByte()*AcceptionRateGray/100;
	if(GrayDotsM>OKGrayArea
	|| GrayDotsT>OKGrayArea){
		int	Cx,Cy;
		GetCenter(Cx,Cy);
		ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
		r->result =0x10003+GetResultType();	//NG
		r->SetResult1(max(GrayDotsM,GrayDotsT));
		r->NGSize	=max(GrayDotsM,GrayDotsT);
		ResultPosListContainer	NowList;
		NowList.AppendList(r);
		Res->MovePosList(NowList);
		Res->SetItemSearchedXY(0,0);
		
		Res->SetAlignedXY(mx,my);
		ResultDx=mx;
		ResultDy=my;
		ResultCode=3;
		Res->SetResult1(GrayDotsM);
		Res->SetResult2(GrayDotsT);
		return 3;			//NG
	}

	if(Th->Clusterize==false 
	&& NGCount1<MTh->OKDot 
	&& NGCount2<MTh->OKDot
	&& GrayDotsM<OKGrayArea
	&& GrayDotsT<OKGrayArea){
		Res->SetAlignedXY(mx,my);
		ResultDx=mx;
		ResultDy=my;
		ResultCode=1;
		Res->SetResult1(NGCount1);
		Res->SetResult2(NGCount2);
					//OK
		DbgR1++;
		return 1;
	}
	else{
		if(Th->LineMode==true){
			if(ExecuteProcessingPickLine(Res
									,Map,MapXByte,MapXByte*8,MapYLen
									,MapXPoint,MapYPoint
									,mx,my)!=0){
				return 5;
			}
		}
		DbgR2++;
		if(Th->SmoothCluster==true){
			for(int h=0;h<2;h++){
				 FatArea(Map
						,DummyMap
						,MapXByte,MapYLen);
			}
			for(int h=0;h<2;h++){
				 ThinArea(Map
						,DummyMap
						,MapXByte,MapYLen);
			}
		}
		int	MaxNGCountsPerCam=Parent->GetParamGlobal()->MaxNGCountsPerCam;
		if(GetParentInPage()->GetNGCounter()>MaxNGCountsPerCam){
			Res->SetAlignedXY(mx,my);
			ResultDx=mx;
			ResultDy=my;
			ResultCode=1;
			Res->SetResult1(0);
			Res->SetResult2(0);
			Res->SetResultDouble(0);
			return 1;	
		}
		if(Th->Clusterize==true || Th->MultiSpotCount!=0 || Th->MultiSpotCountGathered!=0){
			PureFlexAreaListContainer FPack;
			PickupFlexArea(Map,MapXByte,MapXByte*8,MapYLen,FPack);

			int64	NGCount=0;
			int64	NGDots=0;
			double	NGLength=0;
			ResultPosListContainer	NowList;
			ResultPosListContainer	MultiSpotList;
			int						MultiSpotListCount=0;
			int						MultiSpotMinSize=99999999;
			ResultPosListContainer	MultiSpotGatheredList;
			int						MultiSpotGatheredListCount=0;
			int						MultiSpotGatheredMinSize=99999999;
			int	MaxNGCountInBlock=ABase->MaxNGCountInBlock;
			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				if(NGCount>=MaxNGCountInBlock){
					break;
				}
				if(p->GetWidth()<=2 || p->GetHeight()<=2){
					RotationPattern	*R=CurrentMasterPattern;
					int	x=p->GetFLineLeftX(0)+MapXPoint;
					int	y=p->GetFLineAbsY(0) +MapYPoint;
					for(int dy=-2;dy<=2;dy++){
						for(int dx=-2;dx<=2;dx++){
							if(dx==0 && dy==0)
								continue;
							if(R->IsInclude(x+dx,y+dy)==false){
								goto	EdgeThinOK;
							}
						}
					}
				}
				{
					p->MoveToNoClip(MapXPoint,MapYPoint);
					int	COKDot		=MTh->OKDot;
					int	COKLength	=MTh->OKLength;
					bool	CalcByBackGround=false;
					if(Th->UseBackGround==true && CurrentMasterPattern->BackGround.CheckOverlap(p)==true){
						COKDot		=Th->BackGroundOKDot;
						COKLength	=Th->BackGroundOKLength;
						CalcByBackGround=true;
					}

					int64	Dots=p->GetPatternByte();
					int	NGW=p->GetWidth();
					int	NGH=p->GetHeight();
					double	NGLen=hypot(NGW, NGH);
					if(Dots>COKDot){
						int	Cx,Cy;
						p->GetCenter(Cx,Cy);
						ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
						if(CalcByBackGround==false){
							r->result =0x10000+GetResultType();	//NG
						}
						else{
							r->result =0x10010+GetResultType();	//NG
						}
						r->SetResult1(Dots);
						r->SetResult2(NGLen);
						r->NGShape.SuckFrom(*p);
						r->NGSize=Dots;
						NowList.AppendList(r);
						NGCount++;
						NGDots+=Dots;
					}
					else if(NGLen>=COKLength) {
						int	Cx, Cy;
						p->GetCenter(Cx, Cy);
						ResultPosList *r=new DotColorMatchingResultPosList(Cx, Cy, 0, 0);
						if(CalcByBackGround==false){
							r->result=0x10002+GetResultType();	//NG
						}
						else{
							r->result=0x10012+GetResultType();	//NG
						}
						r->SetResult1(Dots);
						r->SetResult2(NGLen);
						r->NGShape.SuckFrom(*p);
						r->NGSize=NGLen;
						NGLength=max(NGLength, NGLen);
						NowList.AppendList(r);
						NGCount++;
					}
					else
					if((Dots>=Th->MultiSpotDot && Th->MultiSpotDot!=0)
					|| (Dots>=Th->MultiSpotDotGathered && Th->MultiSpotDotGathered!=0)){
						int	Cx,Cy;
						p->GetCenter(Cx,Cy);
						if(Dots>=Th->MultiSpotDot && Th->MultiSpotDot!=0){
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10001+GetResultType();	//NG
							r->SetResult1(Dots);
							r->SetResult2(NGLen);
							MultiSpotMinSize=min(MultiSpotMinSize,(int)p->GetPatternByte());
							r->NGShape=*p;
							r->NGSize=Dots;
							MultiSpotList.AppendList(r);
							MultiSpotListCount++;
						}
						if(Dots>=Th->MultiSpotDotGathered && Th->MultiSpotDotGathered!=0){
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10021+GetResultType();	//NG
							r->SetResult1(Dots);
							r->SetResult2(NGLen);
							MultiSpotMinSize=min(MultiSpotMinSize,(int)p->GetPatternByte());
							r->NGShape.SuckFrom(*p);
							r->NGSize=Dots;
							MultiSpotGatheredList.AppendList(r);
							MultiSpotGatheredListCount++;
						}
					}
				}
				EdgeThinOK:;
			}
			Res->MovePosList(NowList);
			Res->SetItemSearchedXY(0,0);
			if(NGCount>0){
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=2;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetResultDouble(NGLength);
				return 2;				//NG
			}
			else if(Th->MultiSpotCount!=0 && Th->MultiSpotCount<=MultiSpotListCount){
				Res->MovePosList(MultiSpotList);
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=3;
				Res->SetResult1(MultiSpotListCount);
				Res->SetResult2(MultiSpotMinSize);
				Res->SetResultDouble(NGLength);
				return 3;				//NG by MultiSpot
			}
			else if(Th->MultiSpotCountGathered!=0
			&& IsGathered(MultiSpotGatheredList,Th->MultiSpotCountGathered,Th->MultiSpotLengthGathered)==true){
				Res->MovePosList(MultiSpotGatheredList);
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=5;
				Res->SetResult1(MultiSpotGatheredListCount);
				Res->SetResult2(MultiSpotGatheredMinSize);
				Res->SetResultDouble(NGLength);
				return 3;				//NG by MultiSpot
			}
			else{
				if(Th->MultiSpotCount!=0 && Th->MultiSpotCount>MultiSpotListCount){
					ResultMultiSpot.Move(MultiSpotList);
				}
				else
				if(Th->MultiSpotCountGathered!=0 && Th->MultiSpotCountGathered>MultiSpotGatheredListCount){
					ResultMultiSpotGathered.Move(MultiSpotGatheredList);
				}
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetResultDouble(NGLength);
				return 1;				//OK
			}
		}
		else{
			int64	NGCount=::GetBitCount((const BYTE **)Map,MapXByte,MapYLen);
			if(NGCount>MTh->OKDot){
				int	Cx,Cy;
				GetCenter(Cx,Cy);
				ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
				r->result =0x10000+GetResultType();	//NG
				r->SetResult1(NGCount);
				r->NGSize=NGCount;
				ResultPosListContainer	NowList;
				NowList.AppendList(r);
				Res->MovePosList(NowList);
				Res->SetItemSearchedXY(0,0);
				
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=2;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				return 2;			//NG
			}
			else{
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				return 1;			//OK
			}
		}
	}

	return 1;
}

int	DotColorMatchingItem::ExecuteProcessingLoopNNGCount(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,ImageBuffer *ImageTargetList[100]
														,ImageBuffer *ImageTRTargetList[100]
														//,int	CDiffR ,int	CDiffG ,int	CDiffB
														,int Mx,int My
														,int MapXPoint,int MapYPoint
														,int SelfSearch ,int Skip
														,int &NGLCount,int &NGHCount)
{
	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)GetParentBase());

	NGLCount=0;
	NGHCount=0;

	int	NoiseBrightness		=ABase->NoiseBrightness;
	int	AcceptionRateGray	=ABase->AcceptionRateGray;
	int	mx=Mx;
	int	my=My;

	int GrayDotsM=0;
	int GrayDotsT=0;
	int	LayerNumb=GetLayerNumb();
	DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();
	if(LayerNumb>=3 && Th->UseOneLayer==0xFF){
		bool	VarietyMode=false;
		if(AP->VarietyMap[0].IsValid()==true
		&& AP->VarietyMap[1].IsValid()==true
		&& AP->VarietyMap[2].IsValid()==true){
			VarietyMode=true;
		}
		ImageBufferFast	*TBuff[3];
		TBuff[0]=new ImageBufferFast(ImageTargetList[0]);
		TBuff[1]=new ImageBufferFast(ImageTargetList[1]);
		TBuff[2]=new ImageBufferFast(ImageTargetList[2]);
		if(Th->UseMaster2==true
		&& GetCountOnlyMasterBuff()>1){
			if(VarietyMode==false){
				CalcInside2(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,GrayDotsM
						,GrayDotsT
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		
			}
			else{
				CalcInside2WithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,GrayDotsM
						,GrayDotsT
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		else if(SubBlock.GetFirst()!=NULL){
			if(VarietyMode==false){
				CalcInsideSubtract(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
			else{
				CalcInsideSubtractWithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		else{
			if(VarietyMode==false){
				CalcInside1(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
			else{
				CalcInside1WithVariety(Th,MTh
						,TBuff,ImageTRTargetList
						,mx ,my
						,Skip ,SelfSearch 
						//,CDiffR,CDiffG,CDiffB 
						,NoiseBrightness
						,MapXPoint ,MapYPoint
						,NGLCount
						,NGHCount
						,Parent->GetLayersBase()->GetStartInspectionTimeMilisec()
						,Parent->GetParamGlobal()->MaxInspectMilisec);
			}
		}
		delete	TBuff[0];
		delete	TBuff[1];
		delete	TBuff[2];
	}
	else{
		bool	VarietyMode=false;
		if(AP->VarietyMap[0].IsValid()==true){
			VarietyMode=true;
		}
		int	Layer=Clipping((int)Th->UseOneLayer,0,LayerNumb-1);
		//int	CDiff;
		if(Layer==0){
			CDiffL=CDiffRL;
			CDiffH=CDiffRH;
		}
		else if(Layer==1){
			CDiffL=CDiffGL;
			CDiffH=CDiffGH;
		}
		else if(Layer==2){
			CDiffL=CDiffBL;
			CDiffH=CDiffBH;
		}
		else{
			CDiffL=0;
			CDiffH=0;
		}
		ImageBufferFast	*TBuff[3];
		TBuff[0]=new ImageBufferFast(ImageTargetList[0]);
		if(LayerNumb>=2){
			TBuff[1]=new ImageBufferFast(ImageTargetList[1]);
		}
		else{
			TBuff[1]=NULL;
		}
		if(LayerNumb>=3){
			TBuff[2]=new ImageBufferFast(ImageTargetList[2]);
		}
		else{
			TBuff[2]=NULL;
		}
		if(VarietyMode==false){
			CalcInsideMono(Th,MTh
					,*TBuff[Layer],*ImageTRTargetList[Layer]
					,Layer
					,mx ,my
					,Skip ,SelfSearch 
					//,CDiff 
					,NoiseBrightness
					,MapXPoint ,MapYPoint
					,NGLCount
					,NGHCount
					,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		}
		else{
			CalcInsideMonoWithVariety(Th,MTh
					,*TBuff[Layer],*ImageTRTargetList[Layer]
					,Layer
					,mx ,my
					,Skip ,SelfSearch 
					//,CDiff 
					,NoiseBrightness
					,MapXPoint ,MapYPoint
					,NGLCount
					,NGHCount
					,Parent->GetLayersBase()->GetStartInspectionTimeMilisec(),Parent->GetParamGlobal()->MaxInspectMilisec);
		}
			
		delete	TBuff[0];
		delete	TBuff[1];
		delete	TBuff[2];
	}
	int	OKGrayArea=GetArea().GetPatternByte()*AcceptionRateGray/100;
	Res->SetAlignedXY(mx,my);
	ResultDx=mx;
	ResultDy=my;
	ResultCode=1;
	Res->SetResult1(NGLCount);
	Res->SetResult2(NGHCount);

	if(Th->Clusterize==false 
	&& NGLCount<MTh->OKDot 
	&& NGHCount<MTh->OKDot
	&& GrayDotsM<OKGrayArea
	&& GrayDotsT<OKGrayArea){
		Res->SetAlignedXY(mx,my);
		ResultDx=mx;
		ResultDy=my;
		ResultCode=1;
		Res->SetResult1(NGLCount);
		Res->SetResult2(NGHCount);
					//OK
		DbgR1++;
		return 1;
	}

	return 2;	//BG
}

bool	MakeFootPoint3D( int x1,int y1,int z1
						,int x2,int y2,int z2
						,int X ,int Y, int Z
						,double &mx ,double &my ,double &mz)
{
	int	dx=x2-x1;
	int	dy=y2-y1;
	int	dz=z2-z1;
	
	double	Len=sqrt(dx*dx+dy*dy+dz*dz);
	if(Len<1.0)
		return false;
	double	Dx=dx/Len;
	double	Dy=dy/Len;
	double	Dz=dz/Len;

	/*
	* D=(Dx*t+x1,Dy*t+y1,Dz*t+z1)
	* (x-X)*(x-X)+(y-Y)*(y-Y)+(z-Z)*(z-Z)=R*R
	* (Dx*t+x1-X)^2 + (Dy*t+y1-Y)^2 + (Dz*t+z1-Z)^2 =R^2
	* (Dx*Dx+Dy*Dy+Dz*Dz)*t+Dx*(x1-X)+Dy*(y1-Y)+Dz*(z1-Z)=0
	* t=-(Dx*(x1-X)+Dy*(y1-Y)+Dz*(z1-Z))/(Dx*Dx+Dy*Dy+Dz*Dz)
	*/
	double	t=-(Dx*(x1-X)+Dy*(y1-Y)+Dz*(z1-Z));
	mx=Dx*t+x1;
	my=Dy*t+y1;
	mz=Dz*t+z1;
	return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------

struct ProcessingDetailStruct
{
	int	zx,zy;
	int	NGLCount,NGHCount;
};


int	SortGListFunc(const void *a,const void *b)
{
	struct ProcessingDetailStruct	*pa=(struct ProcessingDetailStruct *)a;
	struct ProcessingDetailStruct	*pb=(struct ProcessingDetailStruct *)b;
	int	Na=pa->NGLCount+pa->NGHCount;
	int	Nb=pb->NGLCount+pb->NGHCount;
	return Na-Nb;
}

bool		DotColorMatchingItem::ExecuteProcessingDetail(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh)
{
	int	Mx,My;

	ResultPosListContainer	CurrentPosList;
	CurrentPosList.Move(Res->GetPosList());
	Mx=Res->GetAlignedX()+Res->GetItemSearchedX();
	My=Res->GetAlignedY()+Res->GetItemSearchedY();
	short		ItemSearchedX=Res->GetItemSearchedX();	
	short		ItemSearchedY=Res->GetItemSearchedY();	
	short		AlignedX=Res->GetAlignedX();		
	short		AlignedY=Res->GetAlignedY();		

	int	LoopCounter=0;

	for(int zy=-Th->AreaSearchY;zy<=Th->AreaSearchY;zy+=3){
		for(int zx=-Th->AreaSearchX;zx<=Th->AreaSearchX;zx+=3){
			LoopCounter++;
		}
	}
	struct ProcessingDetailStruct	GListDim[1000];
	struct ProcessingDetailStruct	*GList;
	if(LoopCounter>1000){
		GList=new struct ProcessingDetailStruct[LoopCounter];
	}
	else{
		GList=GListDim;
	}
	int	MaxMilisecInPage=GetParentBase()->GetMaxMilisecInPage();
	int	Kn=0;
	for(int zy=-Th->AreaSearchY;zy<=Th->AreaSearchY;zy+=3){
		for(int zx=-Th->AreaSearchX;zx<=Th->AreaSearchX;zx+=3){

			Res->ClearPosList();
			ResetProcessDone();
			int	NGLCount,NGHCount;
			int	Ret=ExecuteProcessingNoAlignmentFixedNGCount(Res
										,Th,MTh
										,0 ,0
										,Mx+zx ,My+zy
										,NGLCount,NGHCount);
			if(Ret==1){
				return true;
			}
			GList[Kn].zx=zx;
			GList[Kn].zy=zy;
			GList[Kn].NGLCount=NGLCount;
			GList[Kn].NGHCount=NGHCount;
			Kn++;
			if(Ret==1){
				if(GList!=GListDim){
					delete	[]GList;
				}
				return true;
			}
			DWORD	NowMilisec=::GetComputerMiliSec();
			if((NowMilisec-GetParentInPage()->GetStartTimeMilisec())>MaxMilisecInPage){
				goto	GoOutFromDetail;
			}
		}
	}
GoOutFromDetail:;

	QSort(GList,Kn,sizeof(GList[0]),SortGListFunc);

	Res->ClearPosList();
	ResetProcessDone();
	ExecuteProcessingNoAlignmentFixed(Res
									,Th,MTh
									,0 ,0
									,Mx+GList[0].zx ,My+GList[0].zy);
	if(Res->IsOk()==true){
		if(GList!=GListDim){
			delete	[]GList;
		}
		return true;
	}		
	Res->ClearPosList();
	Res->GetPosList().Move(CurrentPosList);
	Res->SetAlignedXY(AlignedX,AlignedY);
	Res->SetItemSearchedXY(ItemSearchedX,ItemSearchedY);
	return false;
}

ExeResult	DotColorMatchingItem::ExecuteProcessing(ResultInItemRoot *Res 
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,int _AreaSearchX,int _AreaSearchY
													,int ShiftDot)
{
	int	CurrentAreaSearchX=_AreaSearchX;
	int	CurrentAreaSearchY=_AreaSearchY;

	if(Th->MatchBrightnessByLayerH<GetLayerNumb()){
		return ExecuteProcessingMatchBrightnessByLayerH(Res
									,Th,MTh
									,Th->MatchBrightnessByLayerH
									,CurrentAreaSearchX,CurrentAreaSearchY
									,ShiftDot);
	}
	if(Th->MatchBrightnessByLayerL<GetLayerNumb()){
		return ExecuteProcessingMatchBrightnessByLayerL(Res
									,Th,MTh
									,Th->MatchBrightnessByLayerL
									,CurrentAreaSearchX,CurrentAreaSearchY
									,ShiftDot);
	}

	if(SearchType==1){
		return ExecuteProcessing0(Res
									,Th,MTh
									,0,0
									,CurrentAreaSearchX,CurrentAreaSearchY);
	}
	else
	if(SearchType==2){
		int	kx,ky;
		int	AreaDx,AreaDy;
		int	Mx,My;
		if(MaxCoefItem!=NULL){
			AreaDx=MaxCoefItem->ResultSelfSeachDx;
			AreaDy=MaxCoefItem->ResultSelfSeachDy;
			if(MaxCoefItem->AVector!=NULL){
				Mx=MaxCoefItem->AVector->ShiftX;
				My=MaxCoefItem->AVector->ShiftY;
				CurrentRotationPatternNo=Clipping((int)(MaxCoefItem->AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
				CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
				//GetAlignmentShiftByHandle(Mx,My,MaxCoefItem->AVector->Handle);
			}
			else{
				GetAlignmentShift(Mx,My);
			}
		}
		else{
			AreaDx=ReferedDx;
			AreaDy=ReferedDy;
			GetAlignmentShift(Mx,My);
		}
		if(CheckInAreaAfterShift(Mx ,My ,CurrentAreaSearchX,CurrentAreaSearchY)==true){
			ExecuteSearchByLine(AreaDx+Mx,AreaDy+My,kx,ky,CurrentAreaSearchX/4,CurrentAreaSearchY/4);
			ExecuteProcessingNoAlignment(Res
										,Th,MTh
										,AreaDx+kx,AreaDy+ky
										,Mx,My
										,CurrentAreaSearchX/8,CurrentAreaSearchY/8);
		}
	}
	else
	if(SearchType==3){
		int	kx,ky;
		int	AreaDx,AreaDy;
		int	Mx,My;
		if(MaxCoefItem!=NULL){
			AreaDx=MaxCoefItem->ResultSelfSeachDx;
			AreaDy=MaxCoefItem->ResultSelfSeachDy;
			if(MaxCoefItem->AVector!=NULL){
				Mx=MaxCoefItem->AVector->ShiftX;
				My=MaxCoefItem->AVector->ShiftY;
				CurrentRotationPatternNo=Clipping((int)(MaxCoefItem->AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
				CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
				//GetAlignmentShiftByHandle(Mx,My,MaxCoefItem->AVector->Handle);
			}
			else{
				GetAlignmentShift(Mx,My);
			}
		}
		else{
			AreaDx=ReferedDx;
			AreaDy=ReferedDy;
			GetAlignmentShift(Mx,My);
		}
		if(CheckInAreaAfterShift(Mx ,My ,CurrentAreaSearchX,CurrentAreaSearchY)==true){
			ExecuteSearchByLine(AreaDx+Mx,AreaDy+My,kx,ky,CurrentAreaSearchX,CurrentAreaSearchY);
			ExecuteProcessingNoAlignment(Res
										,Th,MTh
										,AreaDx+kx,AreaDy+ky
										,Mx,My
										,CurrentAreaSearchX/4,CurrentAreaSearchY/4);
		}
	}
	else
	if(SearchType==5){
		int	AreaDx,AreaDy;
		int	Mx,My;
		int	AreaSearhX=CurrentAreaSearchX/4;
		int	AreaSearhY=CurrentAreaSearchY/4;
		if(AreaSearhX==0)
			AreaSearhX=1;
		if(AreaSearhY==0)
			AreaSearhY=1;
		if(MaxCoefItem!=NULL){
			AreaDx=MaxCoefItem->ResultSelfSeachDx;
			AreaDy=MaxCoefItem->ResultSelfSeachDy;
			if(MaxCoefItem->AVector!=NULL){
				//GetAlignmentShiftByHandle(Mx,My,MaxCoefItem->AVector->Handle);
				Mx=MaxCoefItem->AVector->ShiftX;
				My=MaxCoefItem->AVector->ShiftY;
				CurrentRotationPatternNo=Clipping((int)(MaxCoefItem->AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
				CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];

				double	Lx=fabs(MasterCx-MaxCoefItem->MasterCx);
				double	Ly=fabs(MasterCy-MaxCoefItem->MasterCy);
				DotColorMatchingInPage	*Ap=(DotColorMatchingInPage	*)GetParentInPage();
				int	AddedSearchDot1X=ceil(Lx/fabs(Ap->DimItemsListInAreaXLen)*CurrentAreaSearchX/6);	//4);
				int	AddedSearchDot2X=ceil(Ly*tan(RotationDiv)/5);	//3.5);
				int	AddedSearchDot1Y=ceil(Ly/fabs(Ap->DimItemsListInAreaYLen)*CurrentAreaSearchY/6);	//4);
				int	AddedSearchDot2Y=ceil(Lx*tan(RotationDiv)/5);	//3.5);
				AreaSearhX+=max(AddedSearchDot1X,AddedSearchDot2X);
				AreaSearhY+=max(AddedSearchDot1Y,AddedSearchDot2Y);
			}
			else
				GetAlignmentShift(Mx,My);
		}
		else{
			AreaDx=ReferedDx;
			AreaDy=ReferedDy;
			GetAlignmentShift(Mx,My);
		}
		if(CheckInAreaAfterShift(Mx ,My ,CurrentAreaSearchX,CurrentAreaSearchY)==true){
			ExecuteProcessingNoAlignment(Res
								,Th,MTh
								,AreaDx,AreaDy
								,Mx,My
								,AreaSearhX,AreaSearhY);
			if(Res->GetError()>=2){
				ResetProcessDone();

				AreaSearhX=CurrentAreaSearchX;
				AreaSearhY=CurrentAreaSearchY;
				if(AreaSearhX==0)
					AreaSearhX=1;
				if(AreaSearhY==0)
					AreaSearhY=1;
				if(MaxCoefItem!=NULL){
					AreaDx=MaxCoefItem->ResultSelfSeachDx;
					AreaDy=MaxCoefItem->ResultSelfSeachDy;
					if(MaxCoefItem->AVector!=NULL){
						//GetAlignmentShiftByHandle(Mx,My,MaxCoefItem->AVector->Handle);
						Mx=MaxCoefItem->AVector->ShiftX;
						My=MaxCoefItem->AVector->ShiftY;
						CurrentRotationPatternNo=Clipping((int)(MaxCoefItem->AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
						CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];

						double	Lx=fabs(MasterCx-MaxCoefItem->MasterCx);
						double	Ly=fabs(MasterCy-MaxCoefItem->MasterCy);
						DotColorMatchingInPage	*Ap=(DotColorMatchingInPage	*)GetParentInPage();
						int	AddedSearchDot1X=ceil(Lx/fabs(Ap->DimItemsListInAreaXLen)*CurrentAreaSearchX/6);	//4);
						int	AddedSearchDot2X=ceil(Ly*tan(RotationDiv)/5);	//3.5);
						int	AddedSearchDot1Y=ceil(Ly/fabs(Ap->DimItemsListInAreaYLen)*CurrentAreaSearchY/6);	//4);
						int	AddedSearchDot2Y=ceil(Lx*tan(RotationDiv)/5);	//3.5);
						AreaSearhX+=max(AddedSearchDot1X,AddedSearchDot2X);
						AreaSearhY+=max(AddedSearchDot1Y,AddedSearchDot2Y);
					}
					else
						GetAlignmentShift(Mx,My);
				}
				else{
					AreaDx=ReferedDx;
					AreaDy=ReferedDy;
					GetAlignmentShift(Mx,My);
				}
				ExecuteProcessingNoAlignment(Res
									,Th,MTh
									,AreaDx,AreaDy
									,Mx,My
									,AreaSearhX,AreaSearhY);
			}
		}
	}
	else
	if(SearchType==6){
		ExecuteProcessing0(Res
							,Th,MTh
							,0,0,CurrentAreaSearchX,CurrentAreaSearchY);
	}
	else
	if(SearchType==7){
		int	kx,ky;
		int	Mx,My;
		GetAlignmentShift(Mx,My);
		if(CheckInAreaAfterShift(Mx ,My ,CurrentAreaSearchX ,CurrentAreaSearchY)==true){
			ExecuteSearchByLine(Mx,My,kx,ky,CurrentAreaSearchX,CurrentAreaSearchY);
			ExecuteProcessing0(Res
								,Th,MTh
								,kx,ky,CurrentAreaSearchX,CurrentAreaSearchY);
		}
	}
	else
	if(SearchType==8){
		int	Mx,My;
		GetAlignmentShift(Mx,My);
		RotationPattern	*R=CurrentMasterPattern;
		if(HasHOrVLine()==true && R->DivArea.IsNull()==true){
			int	kx,ky;
			if(CheckInAreaAfterShift(Mx ,My ,CurrentAreaSearchX,CurrentAreaSearchY)==true){
				ExecuteSearchByLine(Mx,My,kx,ky,CurrentAreaSearchX,CurrentAreaSearchY);
				ExecuteProcessing0(Res
									,Th,MTh
									,kx,ky,CurrentAreaSearchX,CurrentAreaSearchY);
			}
		}
		else{
			return ExecuteProcessing0(Res
									,Th,MTh
									,0,0
									,CurrentAreaSearchX,CurrentAreaSearchY);
		}
	}
	return _ER_true;
}


ExeResult	DotColorMatchingItem::ExecuteProcessingDetail(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,int AreaSearchX,int AreaSearchY)
{
	int	Mx,My;
	GetAlignmentShift(Mx,My);
	if(CheckInAreaAfterShift(Mx ,My ,AreaSearchX,AreaSearchY)==true){
		ImageBuffer *ImageTargetList[100];
		GetTargetBuffList(ImageTargetList);

		RotationPattern	*R=CurrentMasterPattern;
		double	MaxD=0;
		int	MaxDx=0;
		int	MaxDy=0;
		if(AreaSearchX>2 && AreaSearchY>2){
			for(int dy=-AreaSearchY;dy<=AreaSearchY;dy+=2){
				for(int dx=-AreaSearchX;dx<=AreaSearchX;dx+=2){
					double	D=R->CalcMatchByDetail(ImageTargetList[R->AdoptLayer],Mx+dx,My+dy);
					if(MaxD<D){
						MaxD=D;
						MaxDx=dx;
						MaxDy=dy;
					}
				}
			}
		}
		MaxD=0;
		int	tMaxDx=0;
		int	tMaxDy=0;
		for(int dy=-2;dy<=2;dy++){
			for(int dx=-2;dx<=2;dx++){
				double	D=R->CalcMatchByDetail(ImageTargetList[R->AdoptLayer],Mx+MaxDx+dx,My+MaxDy+dy);
				if(MaxD<D){
					MaxD=D;
					tMaxDx=dx;
					tMaxDy=dy;
				}
			}
		}
		ExecuteProcessingFixed(Res
								,Th,MTh
								,Mx+MaxDx+tMaxDx,My+MaxDy+tMaxDy);
	}
	return _ER_true;
}

ExeResult	DotColorMatchingItem::ExecuteProcessing0(ResultInItemRoot *Res
													,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
													,int AreaDx ,int AreaDy
													,int AreaSearchX,int AreaSearchY)

{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	int	Mx,My;
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
		CurrentRotationPatternNo=Clipping((int)(AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
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
		Mx=V.ShiftX;
		My=V.ShiftY;
		CurrentRotationPatternNo=Clipping((int)(V.Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
	}
	if(CheckInAreaAfterShift(Mx ,My ,AreaSearchX ,AreaSearchY)==true){
		ExecuteProcessingNoAlignment(Res
									,Th,MTh
									,AreaDx ,AreaDy
									,Mx ,My
									,AreaSearchX,AreaSearchY);
	}
	
	return _ER_true;
}


ExeResult	DotColorMatchingItem::ExecuteProcessingMatchBrightnessByLayerH(ResultInItemRoot *Res
																		,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
																		,int MatchBrightnessByLayer
																		,int AreaSearchX,int AreaSearchY
																		,int ShiftDot)
{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	int	Mx,My;
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
		CurrentRotationPatternNo=Clipping((int)(AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
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
		Mx=V.ShiftX;
		My=V.ShiftY;
		CurrentRotationPatternNo=Clipping((int)(V.Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
	}
	if(CheckInAreaAfterShift(Mx ,My ,AreaSearchX,AreaSearchY)==true){
		int	Lx,Ly;
		SearchBrightnessH(Mx ,My ,Lx,Ly,AreaSearchX,AreaSearchY,MatchBrightnessByLayer);
		ExecuteProcessingFixed(Res 
								,Th,MTh
								,Mx+Lx ,My+Ly);

		if(Res->IsOk()==false){

			int	MinNGSize=Res->GetTotalNGSize();
			int	MinDx	=Res->GetAlignedX();
			int	MinDy	=Res->GetAlignedY();
			ResultPosListContainer	MinPosContainer;
			MinPosContainer.Move(Res->GetPosList());

			ResetProcessDone();
			for(int dy=-ShiftDot;dy<=ShiftDot;dy++){
				for(int dx=-ShiftDot;dx<=ShiftDot;dx++){
					Res->ClearPosList();
					ResetProcessDone();
					ExecuteProcessingFixed(Res
											,Th,MTh
											,Mx+Lx+dx ,My+Ly+dy);
					if(Res->IsOk()==true){
						break;
					}
					else{
						int	NGSize=Res->GetTotalNGSize();
						if(NGSize<MinNGSize){
							MinPosContainer.RemoveAll();
							MinPosContainer.Move(Res->GetPosList());
							MinNGSize=NGSize;
							MinDx=Res->GetAlignedX();
							MinDy=Res->GetAlignedY();
						}
					}
				}
			}
			Res->GetPosList().RemoveAll();
			if(Res->IsOk()==false){
				Res->GetPosList().Move(MinPosContainer);
				Res->SetAlignedXY(MinDx,MinDy);
			}
			else{
				MinPosContainer.RemoveAll();
			}
		}
	}
	
	return _ER_true;
}

ExeResult	DotColorMatchingItem::ExecuteProcessingMatchBrightnessByLayerL(ResultInItemRoot *Res
														,const	DotColorMatchingThreshold	*Th,const DotColorMatchingThreshold::MThreshold *MTh
														,int MatchBrightnessByLayer
														,int AreaSearchX,int AreaSearchY
														,int ShiftDot)
{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(IsProcessDone()==true)
		return _ER_true; 

	int	Mx,My;
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
		CurrentRotationPatternNo=Clipping((int)(AVector->Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
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
		Mx=V.ShiftX;
		My=V.ShiftY;
		CurrentRotationPatternNo=Clipping((int)(V.Rotation/RotationDiv+PatternCount*0.5),0,PatternCount-1);
		CurrentMasterPattern=&MasterPattern[CurrentRotationPatternNo];
	}
	if(CheckInAreaAfterShift(Mx ,My ,AreaSearchX,AreaSearchY)==true){
		int	Lx,Ly;
		SearchBrightnessL(Mx ,My ,Lx,Ly,AreaSearchX,AreaSearchY,MatchBrightnessByLayer);
		ExecuteProcessingFixed(Res 
								,Th,MTh
								,Mx+Lx ,My+Ly);
		if(Res->IsOk()==false){

			int	MinNGSize=Res->GetTotalNGSize();
			int	MinDx	=Res->GetAlignedX();
			int	MinDy	=Res->GetAlignedY();
			ResultPosListContainer	MinPosContainer;
			MinPosContainer.Move(Res->GetPosList());

			ResetProcessDone();
			for(int dy=-ShiftDot;dy<=ShiftDot;dy++){
				for(int dx=-ShiftDot;dx<=ShiftDot;dx++){
					Res->ClearPosList();
					ResetProcessDone();
					ExecuteProcessingFixed(Res 
											,Th,MTh
											,Mx+Lx+dx ,My+Ly+dy);
					if(Res->IsOk()==true){
						break;
					}
					else{
						int	NGSize=Res->GetTotalNGSize();
						if(NGSize<MinNGSize){
							MinPosContainer.RemoveAll();
							MinPosContainer.Move(Res->GetPosList());
							MinNGSize=NGSize;
							MinDx=Res->GetAlignedX();
							MinDy=Res->GetAlignedY();
						}
					}
				}
			}
			Res->GetPosList().RemoveAll();
			if(Res->IsOk()==false){
				Res->GetPosList().Move(MinPosContainer);
				Res->SetAlignedXY(MinDx,MinDy);
			}
			else{
				MinPosContainer.RemoveAll();
			}
		}
	}
	
	return _ER_true;
}


//======================================================================================================================

int	DotColorMatchingItem::GetResultType(void)
{
	if(MasterPattern[0].FlatPattern==true){
		//単色
		return 0x100;
	}
	else
	if(MasterPattern[0].FlatPattern==false && MasterPattern[0].DivArea.IsEmpty()==true){
		//グラデーション
		return 0x200;
	}
	else
	if(MasterPattern[0].FlatPattern==false && MasterPattern[0].DivArea.IsEmpty()==false){
		//文字
		return 0x300;
	}
	return 0x400;
}


void	DotColorMatchingItem::CalcSide(int Layer
										,double &VLeft ,double &VTop , double &VRight , double &VBottom)
{
	VLeft	=0;
	VTop	=0;
	VRight	=0;
	VBottom	=0;
	RotationPattern	*R=CurrentMasterPattern;
	int	W=R->GetWidth();
	int	H=R->GetHeight();

	int	W6=W/6;
	if(W6==0)
		W6=2;
	int	H6=H/6;
	if(H6==0)
		H6=2;
	int	x1=R->GetMinX()+W6;
	int	x2=R->GetMaxX()-W6;
	int	y1=R->GetMinY()+H6;
	int	y2=R->GetMaxY()-H6;

	int	N=R->GetFLineLen();
	double	AreaALeft	=0;
	double	AreaATop	=0;
	double	AreaARight	=0;
	double	AreaABottom	=0;
	double	AreaAALeft	=0;
	double	AreaAATop	=0;
	double	AreaAARight	=0;
	double	AreaAABottom=0;
	int		NumbLeft	=0;
	int		NumbTop		=0;
	int		NumbRight	=0;
	int		NumbBottom	=0;

	int		MCx=R->XLen/2;
	int		MCy=R->YLen/2;

	for(int i=0;i<N;i++){
		int	Y	=R->GetFLineAbsY(i);
		int	X1	=R->GetFLineLeftX(i);
		int	numb=R->GetFLineNumb(i);
		BMatrix &MasterMap=R->BuffByMaster[0].Map[Layer];
		int		Yn=Y-MasterCy+MCy;
		BYTE	*MP=MasterMap[Yn];
		if(MP!=NULL){
			for(int xn=0;xn<numb;xn++){
				int	x=X1+xn;
				BYTE	m=MP[x-MasterCx+MCx];
				if(x<=x1){
					AreaALeft	+=m;
					AreaAALeft	+=m*m;
					NumbLeft++;
				}
				if(x2<=x){
					AreaARight	+=m;
					AreaAARight	+=m*m;
					NumbRight++;
				}
				if(Y<=y1){
					AreaATop	+=m;
					AreaAATop	+=m*m;
					NumbTop++;
				}
				if(y2<=Y){
					AreaABottom	+=m;
					AreaAABottom+=m*m;
					NumbBottom++;
				}
			}
		}
		else{
			BYTE	m=MasterMap.GetConstantBrightness(Yn);
			int	iNumbLeft=0;
			int	iNumbRight=0;
			int	iNumbTop=0;
			int	iNumbBottom=0;
			for(int xn=0;xn<numb;xn++){
				int	x=X1+xn;
				if(x<=x1){
					iNumbLeft++;
				}
				if(x2<=x){
					iNumbRight++;
				}
				if(Y<=y1){
					iNumbTop++;
				}
				if(y2<=Y){
					iNumbBottom++;
				}
			}
			AreaALeft	+=m*iNumbLeft;
			AreaAALeft	+=m*m*iNumbLeft;
			NumbLeft	+=iNumbLeft;

			AreaARight	+=m*iNumbRight;
			AreaAARight	+=m*m*iNumbRight;
			NumbRight	+=iNumbRight;

			AreaATop	+=m*iNumbTop;
			AreaAATop	+=m*m*iNumbTop;
			NumbTop		+=iNumbTop;

			AreaABottom	+=m*iNumbBottom;
			AreaAABottom+=m*m*iNumbBottom;
			NumbBottom	+=iNumbBottom;
		}
	}
	if(NumbLeft!=0){
		double	Avr=AreaALeft/NumbLeft;
		double	D=AreaAALeft - Avr*Avr*NumbLeft;
		double	V=sqrt(D/NumbLeft);
		VLeft	=V/Avr*256;
	}
	if(NumbRight!=0){
		double	Avr=AreaARight/NumbRight;
		double	D=AreaAARight - Avr*Avr*NumbRight;
		double	V=sqrt(D/NumbRight);
		VRight	=V/Avr*256;
	}
	if(NumbTop!=0){
		double	Avr=AreaATop/NumbTop;
		double	D=AreaAATop - Avr*Avr*NumbTop;
		double	V=sqrt(D/NumbTop);
		VTop	=V/Avr*256;
	}
	if(NumbBottom!=0){
		double	Avr=AreaABottom/NumbBottom;
		double	D=AreaAABottom - Avr*Avr*NumbBottom;
		double	V=sqrt(D/NumbBottom);
		VBottom	=V/Avr*256;
	}
}




const	int	NoiseLevelForCalcMatch=5;

void	DotColorMatchingItem::CalcAAA(void)
{
	RotationPattern	*R=CurrentMasterPattern;
	int	N=R->GetFLineLen();
	AreaAR=0;
	AreaAG=0;
	AreaAB=0;
	AreaAAR=0;
	AreaAAG=0;
	AreaAAB=0;
	BMatrix	&MBuff0=R->BuffByMaster[0].Map[0];
	BMatrix	&MBuff1=R->BuffByMaster[0].Map[1];
	BMatrix	&MBuff2=R->BuffByMaster[0].Map[2];
	int		MCx=R->XLen/2;
	int		MCy=R->YLen/2;

	int	Numb=0;
	for(int i=0;i<N;i++){
		int	Y	=R->GetFLineAbsY(i);
		int	X1	=R->GetFLineLeftX(i);
		int	numb=R->GetFLineNumb(i);
		int		Yn=Y-MasterCy+MCy;
		BYTE	*MPR=MBuff0[Yn];
		BYTE	*MPG=MBuff1[Yn];
		BYTE	*MPB=MBuff2[Yn];
		int	iAR=0;
		int	iAG=0;
		int	iAB=0;
		int64	iAAR=0;
		int64	iAAG=0;
		int64	iAAB=0;
		if(MPR!=NULL){
			for(int xn=0;xn<numb;xn++){
				int	Xk=X1+xn-MasterCx+MCx;
				BYTE	mR=MPR[Xk];
				iAR+=mR;
				iAAR+=mR*mR;
			}
		}
		else{
			BYTE	mR=MBuff0.GetConstantBrightness(Yn);
			iAR+=mR*numb;
			iAAR+=mR*mR*numb;
		}
		if(MPG!=NULL){
			for(int xn=0;xn<numb;xn++){
				int	Xk=X1+xn-MasterCx+MCx;
				BYTE	mG=MPG[Xk];
				iAG+=mG;
				iAAG+=mG*mG;
			}
		}
		else{
			BYTE	mG=MBuff1.GetConstantBrightness(Yn);
			iAG+=mG*numb;
			iAAG+=mG*mG*numb;
		}
		if(MPB!=NULL){
			for(int xn=0;xn<numb;xn++){
				int	Xk=X1+xn-MasterCx+MCx;
				BYTE	mB=MPB[Xk];
				iAB+=mB;
				iAAB+=mB*mB;
			}
		}
		else{
			BYTE	mB=MBuff2.GetConstantBrightness(Yn);
			iAB+=mB*numb;
			iAAB+=mB*mB*numb;
		}
		AreaAR	+=iAR;
		AreaAG	+=iAG;
		AreaAB	+=iAB;
		AreaAAR	+=iAAR;
		AreaAAG	+=iAAG;
		AreaAAB	+=iAAB;
		Numb	+=numb;
	}
	if(Numb==0)
		return;
	double	AvrR=AreaAR/Numb;
	double	AvrG=AreaAG/Numb;
	double	AvrB=AreaAB/Numb;
	if(AvrR<5.0)
		AvrR=5.0;
	if(AvrG<5.0)
		AvrG=5.0;
	if(AvrB<5.0)
		AvrB=5.0;
	double	DR=AreaAAR-AvrR*AvrR*Numb;
	double	DG=AreaAAG-AvrG*AvrG*Numb;
	double	DB=AreaAAB-AvrB*AvrB*Numb;
	double	nVR=sqrt(DR/Numb);
	double	nVG=sqrt(DG/Numb);
	double	nVB=sqrt(DB/Numb);
	double	ColPower=sqrt(AvrR*AvrR+AvrG*AvrG+AvrB*AvrB);
	double	VR=(nVR<NoiseLevelForCalcMatch)?0:nVR/ColPower*256;
	double	VG=(nVG<NoiseLevelForCalcMatch)?0:nVG/ColPower*256;
	double	VB=(nVB<NoiseLevelForCalcMatch)?0:nVB/ColPower*256;

	int	ClassifiedMethod	=((DotColorMatchingBase *)GetParentBase())->ClassifiedMethod;

	double	VLeft ,VTop , VRight , VBottom;
	int	AdoptLayer=0;
	if(VR>=VG && VR>=VB){
		AdoptLayer=0;
		CalcSide(AdoptLayer
				,VLeft ,VTop , VRight , VBottom);
		if(VR		>ClassifiedMethod
		|| VLeft	>ClassifiedMethod
		|| VTop		>ClassifiedMethod
		|| VRight	>ClassifiedMethod
		|| VBottom	>ClassifiedMethod){
			MatchingType=0;
		}
		else{
			MatchingType=1;
		}
	}
	else if(VG>=VR && VG>=VB){
		AdoptLayer=1;
		CalcSide(AdoptLayer
				,VLeft ,VTop , VRight , VBottom);
		if(VG		>ClassifiedMethod
		|| VLeft	>ClassifiedMethod
		|| VTop		>ClassifiedMethod
		|| VRight	>ClassifiedMethod
		|| VBottom	>ClassifiedMethod){
			MatchingType=0;
		}
		else{
			MatchingType=1;
		}
	}
	else if(VB>=VR && VB>=VG){
		AdoptLayer=2;
		CalcSide(AdoptLayer
				,VLeft ,VTop , VRight , VBottom);
		if(VB		>ClassifiedMethod
		|| VLeft	>ClassifiedMethod
		|| VTop		>ClassifiedMethod
		|| VRight	>ClassifiedMethod
		|| VBottom	>ClassifiedMethod){
			MatchingType=0;
		}
		else{
			MatchingType=1;
		}
	}
}


//==============================================================================================
