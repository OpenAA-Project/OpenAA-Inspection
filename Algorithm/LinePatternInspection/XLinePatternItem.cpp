#include "XLinePatternInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XPropertyLinePatternCommon.h"
#include "XAlgorithmDLL.h"

#if defined(linux)
#include <x86intrin.h>
#endif // defined(linux)

const int	LinePatternAreaMergin	=6;
const	int	BLKMergin	=4;

//==================================================================================================

LinePatternItem::LinePatternItem(void)
{
	AVector		=NULL;
	MasterColI	=0;
	MasterColO	=0;
	TargetColI	=0;
	TargetColO	=0;

	ResultGlobalShiftX	=ResultGlobalShiftY	=0;
	ResultShiftX		=ResultShiftY		=0;
	InsideAreaDim	=NULL;
	OutsideAreaDim	=NULL;
	AreaNumb		=0;
}
LinePatternItem::~LinePatternItem(void)
{
	if(InsideAreaDim!=NULL){
		delete	[]InsideAreaDim;
		InsideAreaDim=NULL;
	}
	if(OutsideAreaDim!=NULL){
		delete	[]OutsideAreaDim;
		OutsideAreaDim=NULL;
	}
	AreaNumb=0;
}
VectorLineBase	*LinePatternItem::CreateVectorBase(void)
{
	return new VectorLineDouble();
}
void	LinePatternItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	LinePatternItem	*ASrc=dynamic_cast<LinePatternItem *>(src);
	if(ASrc!=NULL){
		if(InsideAreaDim!=NULL){
			delete	[]InsideAreaDim;
			InsideAreaDim=NULL;
		}
		if(OutsideAreaDim!=NULL){
			delete	[]OutsideAreaDim;
			OutsideAreaDim=NULL;
		}
		if(ASrc->AreaNumb!=0){
			AreaNumb	=ASrc->AreaNumb;
			InsideAreaDim	=new FlexArea[AreaNumb];
			OutsideAreaDim	=new FlexArea[AreaNumb];
		}
		for(int i=0;i<AreaNumb;i++){
			InsideAreaDim[i]	=ASrc->InsideAreaDim[i];
			OutsideAreaDim[i]	=ASrc->OutsideAreaDim[i];
			InsideAreaDim[i]	.MoveToNoClip(OffsetX ,OffsetY);
			OutsideAreaDim[i]	.MoveToNoClip(OffsetX ,OffsetY);
		}

		MasterColI	=ASrc->MasterColI;
		MasterColO	=ASrc->MasterColO;
		TargetColI	=ASrc->TargetColI;
		TargetColO	=ASrc->TargetColO;
	}
}
void    LinePatternItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPLI::MoveTo(dx,dy);

	for(int i=0;i<AreaNumb;i++){
		InsideAreaDim[i]	.MoveToNoClip(dx,dy);
		OutsideAreaDim[i]	.MoveToNoClip(dx,dy);
	}
}

ExeResult	LinePatternItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetVector()->GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true
	|| (GetMasterBuff().IsNull()==false && GetMasterBuff().IsChanged()==true)){
		LinePatternBase	*ABase=(LinePatternBase *)GetParentBase();
		const LinePatternThreshold	*RThr=GetThresholdR();
		int	iAreaNumb=RThr->AngleNumb;
		if(iAreaNumb<=0)
			iAreaNumb=1;
		if((iAreaNumb&1)==0)
			iAreaNumb++;
		if(AreaNumb!=iAreaNumb){
			if(InsideAreaDim!=NULL){
				delete	[]InsideAreaDim;
				InsideAreaDim=NULL;
			}
			if(OutsideAreaDim!=NULL){
				delete	[]OutsideAreaDim;
				OutsideAreaDim=NULL;
			}
			AreaNumb=iAreaNumb;
			InsideAreaDim	=new FlexArea[AreaNumb];
			OutsideAreaDim	=new FlexArea[AreaNumb];
		}
		for(int i=0;i<AreaNumb;i++){
			InsideAreaDim[i]	.Clear();
			OutsideAreaDim[i]	.Clear();
		}

		LinePatternInLayer	*P=(LinePatternInLayer *)GetParentInLayer();
		P->ParallelMutex.lock();
		LinePatternLibrary	*Lib=(LinePatternLibrary *)ABase->FindOrLoadLibFromManagedCacheLib(GetLibID());
		P->ParallelMutex.unlock();

		if(Lib!=NULL){
			for(VectorItemBase	*p1=GetVector()->GetFirstItem();p1!=NULL;p1=p1->GetNext()){
				VectorItemBase	*p2=p1->GetNext();
				if(p2==NULL)
					break;

				double	X1=p1->GetX();
				double	Y1=p1->GetY();
				double	X2=p2->GetX();
				double	Y2=p2->GetY();

				MakeAreaIO(X1, Y1 ,X2 ,Y2 ,0 ,*Lib);
				double	Len=hypot(X2-X1,Y2-Y1);
				double	Angle=atan(RThr->ThreshBag.TransitDot/Len);
				double	Cx=(X2+X1)/2;
				double	Cy=(Y2+Y1)/2;
				int	n=1;
				for(int i=1;i<AreaNumb;i+=2,n++){
					double	SinS=sin(Angle*ABase->MultiplyInAngle*n);
					double	CosS=cos(Angle*ABase->MultiplyInAngle*n);
					MakeAreaIO((X1-Cx)*CosS+(Y1-Cy)*SinS+Cx, -(X1-Cx)*SinS+(Y1-Cy)*CosS+Cy ,(X2-Cx)*CosS+(Y2-Cy)*SinS+Cx, -(X2-Cx)*SinS+(Y2-Cy)*CosS+Cy ,i   ,*Lib);
					MakeAreaIO((X1-Cx)*CosS-(Y1-Cy)*SinS+Cx,  (X1-Cx)*SinS+(Y1-Cy)*CosS+Cy ,(X2-Cx)*CosS-(Y2-Cy)*SinS+Cx,  (X2-Cx)*SinS+(Y2-Cy)*CosS+Cy ,i+1 ,*Lib);
				}
			}
		}
		
		if(GetMasterBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
			if(RThr->ThreshBag.PointMove.ModeDynamicMask==true){
				MasterColI=CalcCenterBright(InsideAreaDim[0],GetMasterBuff(),0,0
											,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
				MasterColO=CalcCenterBright(OutsideAreaDim[0],GetMasterBuff(),0,0
											,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
			}
			else{
				MasterColI=CalcCenterBright(InsideAreaDim[0],GetMasterBuff(),0,0);
				MasterColO=CalcCenterBright(OutsideAreaDim[0],GetMasterBuff(),0,0);
			}
		}
		else{
			MasterColI=0;
			MasterColO=0;
		}
		TargetColI	=0;
		TargetColO	=0;
	}

	return _ER_true;
}

void	LinePatternItem::MakeAreaIO(double X1, double Y1 ,double X2 ,double Y2 ,int n ,LinePatternLibrary &Lib)
{
	double	hx=X2-X1;
	double	hy=Y2-Y1;
	double	L=hypot(hx,hy);
	double	vx=hy/L;
	double	vy=-hx/L;
	const LinePatternThreshold	*RThr=GetThresholdR();
	double	HalfTransitDot=RThr->ThreshBag.TransitDot/2.0;

	XYClassArea	A1;
	A1.AppendList(new XYClass(X1+vx*HalfTransitDot
							, Y1+vy*HalfTransitDot));
	A1.AppendList(new XYClass(X1+vx*(HalfTransitDot + Lib.LineWidthInPattern)
							, Y1+vy*(HalfTransitDot + Lib.LineWidthInPattern)));
	A1.AppendList(new XYClass(X2+vx*(HalfTransitDot + Lib.LineWidthInPattern)
							, Y2+vy*(HalfTransitDot + Lib.LineWidthInPattern)));
	A1.AppendList(new XYClass(X2+vx*HalfTransitDot
							, Y2+vy*HalfTransitDot));
	FlexArea	An1;
	A1.TransTo(An1);
	InsideAreaDim[n]+=An1;

	XYClassArea	A2;
	A2.AppendList(new XYClass(X1-vx*HalfTransitDot
							, Y1-vy*HalfTransitDot));
	A2.AppendList(new XYClass(X1-vx*(HalfTransitDot + Lib.LineWidthOutside)
							, Y1-vy*(HalfTransitDot + Lib.LineWidthOutside)));
	A2.AppendList(new XYClass(X2-vx*(HalfTransitDot + Lib.LineWidthOutside)
							, Y2-vy*(HalfTransitDot + Lib.LineWidthOutside)));
	A2.AppendList(new XYClass(X2-vx*HalfTransitDot
							, Y2-vy*HalfTransitDot));
	FlexArea	An2;
	A2.TransTo(An2);
	OutsideAreaDim[n]+=An2;

	if(n==0){
		FlexArea	Area;
		XYClassArea	A3;
		A3.AppendList(new XYClass(X1-vx*(HalfTransitDot + Lib.LineWidthOutside)
								, Y1-vy*(HalfTransitDot + Lib.LineWidthOutside)));
		A3.AppendList(new XYClass(X1+vx*(HalfTransitDot + Lib.LineWidthInPattern)
								, Y1+vy*(HalfTransitDot + Lib.LineWidthInPattern)));
		A3.AppendList(new XYClass(X2+vx*(HalfTransitDot + Lib.LineWidthInPattern)
								, Y2+vy*(HalfTransitDot + Lib.LineWidthInPattern)));
		A3.AppendList(new XYClass(X2-vx*(HalfTransitDot + Lib.LineWidthOutside)
								, Y2-vy*(HalfTransitDot + Lib.LineWidthOutside)));
		FlexArea	An3;
		A3.TransTo(An3);
		Area+=An3;
		SetArea(Area);
	}
}

ExeResult	LinePatternItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ResultGlobalShiftX	=ResultGlobalShiftY	=0;
	ResultShiftX		=ResultShiftY		=0;
	return _ER_true;
}

int		GetErrorPixelCount(ResultPosListContainer &NowList)
{
	int	SumE=0;
	for(ResultPosList  *r=NowList.GetFirst();r!=NULL;r=r->GetNext()){
		SumE+=r->GetResult1();
	}
	return SumE;
}


int	SortLinePatternShiftInfo(const void *a,const void *b)
{
	struct LinePatternShiftInfo	*pa=(struct LinePatternShiftInfo	*)a;
	struct LinePatternShiftInfo	*pb=(struct LinePatternShiftInfo	*)b;
	if(pa->MatchResult>pb->MatchResult)
		return -1;
	if(pa->MatchResult<pb->MatchResult)
		return 1;
	return 0;
}

ExeResult	LinePatternItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
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
	ImageBuffer	&Buff=GetTargetBuff();


	ResultPosListContainer	NowListI[1000];
	ResultPosListContainer	NowListO[1000];
	int	tResultShiftX[1000];
	int	tResultShiftY[1000];
	int	Error[1000];
	bool	ResultOK=false;

	for(int k=0;k<AreaNumb;k++){
		ResultOK=ExecuteProcessingFunc	(k,Res
										,mx ,my
										,Buff
										,NowListI[k] ,NowListO[k]
										,tResultShiftX[k] ,tResultShiftY[k]
										,Error[k]);
		if(ResultOK==true){
			//Result OK
			Res->SetError(1);
			Res->SetItemSearchedXY(tResultShiftX[k]+ResultGlobalShiftX,tResultShiftY[k]+ResultGlobalShiftY);
			ResultAngleNumber=k;
			ResultShiftX=tResultShiftX[ResultAngleNumber];
			ResultShiftY=tResultShiftY[ResultAngleNumber];
			Res->SetResult2(k);
			break;
		}
	}
	if(ResultOK==false){
		int	MinSum=99999999;
		ResultAngleNumber=0;
		for(int i=0;i<AreaNumb;i++){
			int	Sum=GetErrorPixelCount(NowListI[i]) + GetErrorPixelCount(NowListO[i]);
			if(Sum<MinSum){
				ResultAngleNumber=i;
				MinSum=Sum;
			}
		}
		Res->MovePosList(NowListI[ResultAngleNumber]);	
		Res->AddMovePosList(NowListO[ResultAngleNumber]);	

		ResultShiftX=tResultShiftX[ResultAngleNumber];
		ResultShiftY=tResultShiftY[ResultAngleNumber];
		Res->SetItemSearchedXY(ResultShiftX+ResultGlobalShiftX,ResultShiftY+ResultGlobalShiftY);
		Res->SetError(2+Error[ResultAngleNumber]);
		Res->SetResult2(ResultAngleNumber);
	}
	Res->SetAlignedXY(mx,my);

	return _ER_true;
}

ExeResult	LinePatternItem::ExecuteProcessingAngle	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,int ReqAngleNumber)
{
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
	ImageBuffer	&Buff=GetTargetBuff();


	ResultPosListContainer	NowListI;
	ResultPosListContainer	NowListO;
	int		Error;
	bool	ResultOK=false;

	if(ReqAngleNumber<0)
		ReqAngleNumber=0;
	if(ReqAngleNumber>=AreaNumb)
		ReqAngleNumber=AreaNumb-1;

	ResultOK=ExecuteProcessingFunc	(ReqAngleNumber,Res
										,mx ,my
										,Buff
										,NowListI ,NowListO
										,ResultShiftX ,ResultShiftY
										,Error);
	if(ResultOK==true){
		//Result OK
		Res->SetError(1);
		Res->SetItemSearchedXY(ResultShiftX+ResultGlobalShiftX,ResultShiftY+ResultGlobalShiftY);
		ResultAngleNumber=ReqAngleNumber;
		Res->SetResult2(ReqAngleNumber);
	}
	if(ResultOK==false){
		Res->MovePosList(NowListI);	
		Res->AddMovePosList(NowListO);	
		Res->SetItemSearchedXY(ResultShiftX+ResultGlobalShiftX,ResultShiftY+ResultGlobalShiftY);
		Res->SetError(2+Error);
		Res->SetResult2(ReqAngleNumber);
	}
	Res->SetAlignedXY(mx,my);

	return _ER_true;
}

bool	LinePatternItem::ExecuteProcessingFunc	(int AngleNumber,ResultInItemRoot *Res
													,int mx ,int my
													,ImageBuffer &Buff
													,ResultPosListContainer &NowListI ,ResultPosListContainer &NowListO
													,int &tResultShiftX ,int &tResultShiftY
													,int &Error)
{
	if(AngleNumber<0)
		AngleNumber=0;
	if(AngleNumber>=AreaNumb)
		AngleNumber=AreaNumb-1;
	const LinePatternThreshold	*RThr=GetThresholdR();
	int	SearchDot=RThr->ThreshBag.SearchDot;
	if(SearchDot>0){
		if(SearchDot<10){
			double	DMax=0;
			int		Rx=0;
			int		Ry=0;
			for(int dy=-SearchDot;dy<=SearchDot;dy++){
				for(int dx=-SearchDot;dx<=SearchDot;dx++){
					double	DSum=TryToMatch(ResultGlobalShiftX+dx ,ResultGlobalShiftY+dy,AngleNumber);
					if(DSum>DMax){
						DMax=DSum;
						Rx=dx;
						Ry=dy;
					}
				}
			}
			tResultShiftX=Rx;
			tResultShiftY=Ry;
		}
		else{
			LinePatternShiftInfo	ShiftDim[10000];
			int	N=0;
			for(int dy=-SearchDot;dy<=SearchDot;dy+=2){
				for(int dx=-SearchDot;dx<=SearchDot;dx+=2){
					if(N<sizeof(ShiftDim)/sizeof(ShiftDim[0])){
						ShiftDim[N].Dx=dx;
						ShiftDim[N].Dy=dy;
						N++;
					}
				}
			}
			for(int i=0;i<N;i++){
				double	DSum=TryToMatch(ResultGlobalShiftX+ShiftDim[i].Dx ,ResultGlobalShiftY+ShiftDim[i].Dy,AngleNumber);
				ShiftDim[i].MatchResult=DSum;
			}
			QSort(ShiftDim,N,sizeof(LinePatternShiftInfo),SortLinePatternShiftInfo);
			double	DMax=0;
			int		Rx=0;
			int		Ry=0;
			int		MaxIndex=0;
			for(int i=0;i<N && i<10;i++){
				for(int dy=-1;dy<=1;dy++){
					for(int dx=-1;dx<=1;dx++){
						double	DSum=TryToMatch(ResultGlobalShiftX+ShiftDim[i].Dx+dx ,ResultGlobalShiftY+ShiftDim[i].Dx+dy,AngleNumber);
						if(DMax<DSum){
							DMax=DSum;
							Rx=dx;
							Ry=dy;
							MaxIndex=i;
						}
					}
				}
			}
			tResultShiftX=ShiftDim[MaxIndex].Dx+Rx;
			tResultShiftY=ShiftDim[MaxIndex].Dy+Ry;
		}
	}
	else{
		tResultShiftX=0;
		tResultShiftY=0;
	}

	LinePatternInLayer	*P=(LinePatternInLayer *)GetParentInLayer();
	short	BrightIL;
	short	BrightIH;
	short	BrightOL;
	short	BrightOH;
	if(RThr->ThreshBag.PointMove.ModeAbsoluteBright==true){
		BrightIL=RThr->ThreshBag.BrightWidthIL;
		BrightIH=RThr->ThreshBag.BrightWidthIH;
		BrightOL=RThr->ThreshBag.BrightWidthOL;
		BrightOH=RThr->ThreshBag.BrightWidthOH;
		CalcTargetColI=(BrightIL+BrightIH)/2;
		CalcTargetColO=(BrightOL+BrightOH)/2;
	}
	else{
		if(RThr->ThreshBag.PointMove.ModeDynamicMask==true){
			TargetColI=CalcCenterBrightDetail(InsideAreaDim[AngleNumber] ,GetTargetBuff(),mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY
										,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
			TargetColO=CalcCenterBrightDetail(OutsideAreaDim[AngleNumber],GetTargetBuff(),mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY
										,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
		}
		else{
			TargetColI=CalcCenterBrightDetail(InsideAreaDim[AngleNumber] ,GetTargetBuff(),mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY);
			TargetColO=CalcCenterBrightDetail(OutsideAreaDim[AngleNumber],GetTargetBuff(),mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY);
		}
		if(RThr->ThreshBag.PointMove.ModeUseRegularBrightness==true){
			int	Dfi=TargetColI-RThr->ThreshBag.RegulatedColI;
			int	Dfo=TargetColO-RThr->ThreshBag.RegulatedColO;
			if(Dfi>=0 && Dfi>RThr->ThreshBag.AdjustBrightIH)
				Dfi=RThr->ThreshBag.AdjustBrightIH;
			if(Dfi<0 && Dfi<-RThr->ThreshBag.AdjustBrightIL)
				Dfi=-RThr->ThreshBag.AdjustBrightIL;
			if(Dfo>=0 && Dfo>RThr->ThreshBag.AdjustBrightOH)
				Dfo=RThr->ThreshBag.AdjustBrightOH;
			if(Dfo<0 && Dfo<-RThr->ThreshBag.AdjustBrightOL)
				Dfo=-RThr->ThreshBag.AdjustBrightOL;

			CalcTargetColI=RThr->ThreshBag.RegulatedColI+Dfi;
			CalcTargetColO=RThr->ThreshBag.RegulatedColO+Dfo;
			BrightIL=CalcTargetColI - RThr->ThreshBag.BrightWidthIL;
			BrightIH=CalcTargetColI + RThr->ThreshBag.BrightWidthIH;
			BrightOL=CalcTargetColO - RThr->ThreshBag.BrightWidthOL;
			BrightOH=CalcTargetColO + RThr->ThreshBag.BrightWidthOH;
		}
		else{
			int	Dfi=TargetColI-MasterColI;
			int	Dfo=TargetColO-MasterColO;
			if(Dfi>=0 && Dfi>RThr->ThreshBag.AdjustBrightIH)
				Dfi=RThr->ThreshBag.AdjustBrightIH;
			if(Dfi<0 && Dfi<-RThr->ThreshBag.AdjustBrightIL)
				Dfi=-RThr->ThreshBag.AdjustBrightIL;
			if(Dfo>=0 && Dfo>RThr->ThreshBag.AdjustBrightOH)
				Dfo=RThr->ThreshBag.AdjustBrightOH;
			if(Dfo<0 && Dfo<-RThr->ThreshBag.AdjustBrightOL)
				Dfo=-RThr->ThreshBag.AdjustBrightOL;
				
			CalcTargetColI=TargetColI+Dfi;
			CalcTargetColO=TargetColO+Dfo;
			BrightIL=CalcTargetColI - RThr->ThreshBag.BrightWidthIL;
			BrightIH=CalcTargetColI + RThr->ThreshBag.BrightWidthIH;
			BrightOL=CalcTargetColO - RThr->ThreshBag.BrightWidthOL;
			BrightOH=CalcTargetColO + RThr->ThreshBag.BrightWidthOH;
		}
	}
	Error=0;
	int	ErrorI=0;
	ExecuteInspectInArea(InsideAreaDim[AngleNumber],Buff
						,mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY ,mx,my
						,2*tResultShiftX+ResultGlobalShiftX,2*tResultShiftY+ResultGlobalShiftY
						,BrightIL,BrightIH
						,RThr->ThreshBag.NGSizeIL,RThr->ThreshBag.NGSizeIH
						,Res
						,NowListI
						,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen
						,ErrorI
						,0x100000);
	if(ErrorI!=0){			
		if((ErrorI&0x10)!=0)
			Error|=0x10;
		if((ErrorI&0x20)!=0)
			Error|=0x20;
	}

	int	ErrorO=0;
	ExecuteInspectInArea(OutsideAreaDim[AngleNumber],Buff
						,mx+tResultShiftX+ResultGlobalShiftX,my+tResultShiftY+ResultGlobalShiftY ,mx,my
						,2*tResultShiftX+ResultGlobalShiftX,2*tResultShiftY+ResultGlobalShiftY
						,BrightOL,BrightOH
						,RThr->ThreshBag.NGSizeOL,RThr->ThreshBag.NGSizeOH
						,Res
						,NowListO
						,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen
						,ErrorO
						,0x200000);
	if(ErrorO!=0){			
		if((ErrorO&0x10)!=0)
			Error|=0x40;
		if((ErrorO&0x20)!=0)
			Error|=0x80;
	}
	if(Error==0){
		//Result OK
		return true;
	}
	return false;
}
double	LinePatternItem::TryToMatch(int rx ,int ry ,int k)
{
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
	const LinePatternThreshold	*RThr=GetThresholdR();
	LinePatternInLayer	*P=(LinePatternInLayer *)GetParentInLayer();
	double	dTargetColI;
	double	dTargetColO;
	if(RThr->ThreshBag.PointMove.ModeDynamicMask==true){
		dTargetColI=CalcCenterBrightDetail(InsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry
									,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
		dTargetColO=CalcCenterBrightDetail(OutsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry
									,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
	}
	else{
		dTargetColI=CalcCenterBrightDetail(InsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry);
		dTargetColO=CalcCenterBrightDetail(OutsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry);
	}
	if(RThr->ThreshBag.PointMove.ModeUseRegularBrightness==true){
		if(RThr->ThreshBag.RegulatedColI<=RThr->ThreshBag.RegulatedColO){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
	else if(RThr->ThreshBag.PointMove.ModeAbsoluteBright==true){
		if((RThr->ThreshBag.BrightWidthIL+RThr->ThreshBag.BrightWidthIH)<=(RThr->ThreshBag.BrightWidthOL+RThr->ThreshBag.BrightWidthOH)){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
	else{
		if(MasterColI<MasterColO){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
}

double	LinePatternItem::TryToMatchRough(int rx ,int ry ,int k)
{
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
	LinePatternInLayer	*P=(LinePatternInLayer *)GetParentInLayer();
	const LinePatternThreshold	*RThr=GetThresholdR();
	double	dTargetColI;
	double	dTargetColO;
	if(RThr->ThreshBag.PointMove.ModeDynamicMask==true){
		dTargetColI=CalcCenterBright(InsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry
									,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
		dTargetColO=CalcCenterBright(OutsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry
									,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
	}
	else{
		dTargetColI=CalcCenterBright(InsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry);
		dTargetColO=CalcCenterBright(OutsideAreaDim[k],GetTargetBuff(),mx+rx,my+ry);
	}
	if(RThr->ThreshBag.PointMove.ModeUseRegularBrightness==true){
		if(RThr->ThreshBag.RegulatedColI<=RThr->ThreshBag.RegulatedColO){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
	else if(RThr->ThreshBag.PointMove.ModeAbsoluteBright==true){
		if((RThr->ThreshBag.BrightWidthIL+RThr->ThreshBag.BrightWidthIH)<=(RThr->ThreshBag.BrightWidthOL+RThr->ThreshBag.BrightWidthOH)){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
	else{
		if(MasterColI<MasterColO){
			return dTargetColO-dTargetColI;
		}
		else{
			return dTargetColI-dTargetColO;
		}
	}
}

void	LinePatternItem::ExecuteInspectInArea(FlexArea &Area,ImageBuffer &Buff
						,int mx ,int my	,int AlignedX,int AlignedY
						,int tResultShiftX, int tResultShiftY
						,int BrightL,int BrightH
						,int NGSizeL,int NGSizeH
						,ResultInItemRoot *Res
						,ResultPosListContainer	&NowList
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						,int &Error
						,DWORD InOut)
{
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	int	CountL=0;
	int	CountH=0;
	const LinePatternThreshold	*RThr=GetThresholdR();
	if(Buff.IsNull()==true){
		Error=0;
		return;
	}
	for(int i=0;i<Area.GetFLineLen();i++){
		int	y =Area.GetFLineAbsY  (i)+my;
		if(y<BLKMergin)
			continue;
		if(y>=MaxLines-BLKMergin)
			break;
		int	x1=Area.GetFLineLeftX (i)+mx;
		int	x2=Area.GetFLineRightX(i)+mx;
		if(x1<BLKMergin)
			x1=BLKMergin;
		if(x2>=DotPerLine-BLKMergin)
			x2=DotPerLine-BLKMergin;
		if(x1>x2)
			continue;

		int	XNumb=x2-x1;

		BYTE	*src=Buff.GetY(y)+x1;
		for(int x=0;x<XNumb;x++){
			BYTE	c=src[x];
			if(c<BrightL)
				CountL++;
			if(c>BrightH)
				CountH++;
		}
	}
	if(CountL<NGSizeL && CountH<NGSizeH){
		Error=0;
		return;
	}
    int Lx=(Area.GetWidth()+4+7)>>3;
    int Ly= Area.GetHeight()+4;
    int LByte=Lx*Ly;

    uchar   BackBuffH[20000];
    uchar   BackBuffL[20000];
    BYTE   *pMapH=NULL;
    BYTE   *pMapL=NULL;

	if(LByte>sizeof(BackBuffH))
	    pMapH=new BYTE[LByte];
	else
		pMapH=BackBuffH;

	if(LByte>sizeof(BackBuffL))
	    pMapL=new BYTE[LByte];
	else
	    pMapL=BackBuffL;

	int starty =Area.GetFLineAbsY(0);
	memset(pMapL,0,LByte);
	memset(pMapH,0,LByte);
	int	LSum=0;
	int	HSum=0;	
	for(int i=0;i<Area.GetFLineLen();i++){
		int Y =Area.GetFLineAbsY(i);
		if(Y+my<BLKMergin)
			continue;
		if(Y+my>=(MaxLines-BLKMergin))
			break;
		int X   =Area.GetFLineLeftX(i);
		int Numb=Area.GetFLineNumb(i);
		int x1=X;
		int x2=X+Numb;
		X=x1;
		if((X+Numb+mx)<BLKMergin || (X+mx)>=(DotPerLine-BLKMergin))
			continue;
		if((X+mx)<BLKMergin){
			X=BLKMergin-mx;
			x1=max(x1,X);
			x2=min(x2,X+Numb);
			Numb=min(Numb,x2-x1);
		}
		if((X+Numb+mx)>=(DotPerLine-BLKMergin)){
			Numb=(DotPerLine-BLKMergin)-(X+mx);
		}
		if(Numb<=0)
			continue;

		int px=X-Area.GetMinX();
		int mdy=Y-starty;
		if(mdy<0)
			continue;
		BYTE	*p=Buff.GetY(my+Y)+mx+X;
		int		MPoint=Lx*mdy+((X-Area.GetMinX())>>3);

		BYTE	*qL=&(pMapL[MPoint]);
		BYTE	*qH=&(pMapH[MPoint]);
		unsigned int	Mask=(0x8080808080808080u>>((X-Area.GetMinX())&7));

		if(DynamicMaskMap==NULL || RThr->ThreshBag.PointMove.ModeDynamicMask==false){
			for(int x=0;x<Numb;x+=8){
				int N=8;
				if(x+8>=Numb)
					N=Numb-x;
				for(int k=0;k<N;k++,p++){

						if(*p<BrightL){
							*qL|=(BYTE)Mask;
							LSum++;
						}
						if(BrightH<*p){
							*qH|=(BYTE)Mask;
							HSum++;
						}
					Mask=_rotr(Mask,1);
					if((Mask &0x80)!=0){
						qL++;
						qH++;
					}
				}
			}
		}
		else{
			BYTE	*DMapP=DynamicMaskMap[Y+my];
			int	MapX=X+mx;
			BYTE	DMapMask=(0x80>>(MapX &0x07));
			BYTE	*DMapPointer=&DMapP[MapX>>3];

			for(int k=0;k<Numb;){
				int	NN;
				BYTE	FullDMask;
				if(DMapMask==0x80){					
					NN=min(8,Numb-k);
					FullDMask=0xFF;
				}
				else if(DMapMask==0x40){
					NN=min(7,Numb-k);
					FullDMask=0x7F;
				}
				else if(DMapMask==0x20){
					NN=min(6,Numb-k);
					FullDMask=0x3F;
				}
				else if(DMapMask==0x10){
					NN=min(5,Numb-k);
					FullDMask=0x1F;
				}
				else if(DMapMask==0x08){
					NN=min(4,Numb-k);
					FullDMask=0x0F;
				}
				else if(DMapMask==0x04){
					NN=min(3,Numb-k);
					FullDMask=0x07;
				}
				else if(DMapMask==0x02){
					NN=min(2,Numb-k);
					FullDMask=0x03;
				}
				else if(DMapMask==0x01){
					NN=min(1,Numb-k);
					FullDMask=0x01;
				}
				else
					break;
				if(((*DMapPointer) & FullDMask)==0){
					for(int t=0;t<NN;t++,p++){
						if(*p<BrightL){
							*qL|=(BYTE)Mask;
							LSum++;
						}
						if(BrightH<*p){
							*qH|=(BYTE)Mask;
							HSum++;
						}
						Mask=_rotr(Mask,1);
						if((Mask &0x80)!=0){
							qL++;
							qH++;
						}
					}
				}
				else{
					for(int t=0;t<NN;t++,p++){
						if(((*DMapPointer) & DMapMask)==0){
							if(*p<BrightL){
								*qL|=(BYTE)Mask;
								LSum++;
							}
							if(BrightH<*p){
								*qH|=(BYTE)Mask;
								HSum++;
							}
						}
						DMapMask>>=1;
						Mask=_rotr(Mask,1);
						if((Mask &0x80)!=0){
							qL++;
							qH++;
						}
					}
				}

				DMapPointer++;
				DMapMask=0x80;
				k+=NN;
			}
		}
	}
		
	uchar   *BackPointer[5000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}
	
	if(LSum>NGSizeL){
	    BYTE   *pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		PureFlexAreaListContainer LFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,-1,false);

		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
			PureFlexAreaList *NextP=p->GetNext();
			int	SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumL>NGSizeL){
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				p->MoveToNoClip(Area.GetMinX(),Area.GetMinY());
				int	Cx,Cy;

				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,tResultShiftX,tResultShiftY);	//mx-AlignedX,my-AlignedY);
				r->result =0x10000+InOut;
				r->SetResult1(SumL);
				r->SetResult2(NGLen);

				r->NGShape.SuckFrom(*p);
				NowList.AppendList(r);

				Error |= 0x10;	//?????A?m?f
				
				delete	p;
				
			}
			p=NextP;
		}
	}
	if(HSum>NGSizeH){
	    BYTE   *pH=pMapH;
		for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}
		PureFlexAreaListContainer HFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,-1,false);

		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
			PureFlexAreaList *NextP=p->GetNext();
			int	SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumH>NGSizeH){
				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				p->MoveToNoClip(Area.GetMinX(),Area.GetMinY());
				int	Cx,Cy;

				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,tResultShiftX,tResultShiftY);	//mx-AlignedX,my-AlignedY);
				r->result =0x20000+InOut;
				r->SetResult1(SumH);
				r->SetResult2(NGLen);

				r->NGShape.SuckFrom(*p);
				NowList.AppendList(r);

				Error |= 0x20;	//?????A?m?f
				
				delete	p;
				
			}
			p=NextP;
		}
	}
	if(BackPointer!=BackDim){
		delete	[]BackDim;
	}
    if(pMapH!=BackBuffH)
        delete  []pMapH;
    if(pMapL!=BackBuffL)
        delete  []pMapL;
}

void	LinePatternItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	LinePatternDrawAttr	*BusAttr=dynamic_cast<LinePatternDrawAttr *>(Attr);
	if(BusAttr!=NULL){
		int	tIndex=BusAttr->ResultAngleNumber;
		if(tIndex>=AreaNumb)
			tIndex=AreaNumb-1;
		if(BusAttr->ModeDrawInside==true){
			if(InsideAreaDim!=NULL){
				if(GetSelected()==true){
					InsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()
						,ZoomRate ,movx ,movy);
				}
				else if(GetActive()==true){
					InsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()
						,ZoomRate ,movx ,movy);
				}
				else{
					InsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()
						,ZoomRate ,movx ,movy);
				}
			}
		}
		if(BusAttr->ModeDrawOutside==true){
			if(OutsideAreaDim!=NULL){
				if(GetSelected()==true){
					OutsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()
						,ZoomRate ,movx ,movy);
				}
				else if(GetActive()==true){
					OutsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()
						,ZoomRate ,movx ,movy);
				}
				else{
					OutsideAreaDim[tIndex].Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()
						,ZoomRate ,movx ,movy);
				}
			}
		}

		if(BusAttr->ModeDrawArea==true){
			AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		else{
			if(GetVector()!=NULL){
				QPainter	P(&pnt);
				if(Attr!=NULL){
					if(GetSelected()==true){
						P.setPen(Attr->SelectedColor);
					}
					else if(GetActive()==true){
						P.setPen(Attr->ActiveColor);
					}
					else{
						P.setPen(Attr->NormalColor);
					}
				}
				else{
					if(GetSelected()==true){
						P.setPen(Qt::green);
					}
					else if(GetActive()==true){
						P.setPen(Qt::red);
					}
					else{
						P.setPen(Qt::blue);
					}
				}
				GetVector()->Draw(P,movx,movy,ZoomRate);
			}
		}
	}
}
void	LinePatternItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AlgorithmItemPLI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}


void	LinePatternItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			LinePatternInLayer	*Ly=dynamic_cast<LinePatternInLayer *>(GetParentInLayer());
			UndoElement<LinePatternInLayer>	*UPointer=new UndoElement<LinePatternInLayer>(Ly,&LinePatternInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			LinePatternItem *src=(LinePatternItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((LinePatternItem *)Data)->GetLibID()){
			LinePatternInLayer	*Ly=dynamic_cast<LinePatternInLayer *>(GetParentInLayer());
			UndoElement<LinePatternInLayer>	*UPointer=new UndoElement<LinePatternInLayer>(Ly,&LinePatternInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			LinePatternItem *src=(LinePatternItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((LinePatternItem *)Data)->GetLibID()){
			LinePatternInLayer	*Ly=dynamic_cast<LinePatternInLayer *>(GetParentInLayer());
			UndoElement<LinePatternInLayer>	*UPointer=new UndoElement<LinePatternInLayer>(Ly,&LinePatternInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			LinePatternItem *src=(LinePatternItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}
void	LinePatternItem::CopyThresholdOnly(LinePatternItem &src)
{
	GetThresholdW()->CopyFrom(*((LinePatternThreshold *)src.GetThresholdR()));
}

WORD	LinePatternItem::CalcCenterBright(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	if(IBuff.IsNull()==true){
		return 0;
	}
	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	int	YSep;
	int	XSep;
	FlexArea	&A=Area;
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
	int	DiscardDot=N/4;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDot){
			break;
		}
	}
	D=0;
	for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
		D+=BTable[HLevel];
		if(D>DiscardDot){
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

WORD	LinePatternItem::CalcCenterBright(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	const LinePatternThreshold	*RThr=GetThresholdR();
	if(IBuff.IsNull()==true){
		return 0;
	}
	int		BTable[256];
	memset(BTable,0,sizeof(BTable));

	int	YSep;
	int	XSep;
	FlexArea	&A=Area;
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
		int	sy=A.GetFLineAbsY  (i);
		int	y =sy+my;
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
		if(DynamicMaskMap!=NULL && RThr->ThreshBag.PointMove.ModeDynamicMask==true){
			BYTE	*Mask=DynamicMaskMap[y];
			for(int x=0;x<XNumb;x+=XSep){
				if(GetBmpBitOnY(Mask,x1+x)==0){
					BTable[*(src+x)]++;
				}
			}
		}
		else{
			for(int x=0;x<XNumb;x+=XSep){
				BTable[*(src+x)]++;
			}
		}
	}
	int	N=0;
	for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
		N+=BTable[i];
	}
	int	DiscardDot=N/4;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDot){
			break;
		}
	}
	D=0;
	for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
		D+=BTable[HLevel];
		if(D>DiscardDot){
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


double	LinePatternItem::CalcCenterBrightDetail(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my)
{
	BYTE	*src;
	int		XNumb;
	if(IBuff.IsNull()==true){
		return 0;
	}
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	int	YSep;
	int	XSep;
	FlexArea	&A=Area;
	if(A.GetFLineLen()<40)
		YSep=1;
	else
		YSep=2;

	int64	DSum=0;
	int		N=0;
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

		if(XNumb<40)
			XSep=1;
		else
			XSep=2;

		src=IBuff.GetY(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			DSum+=*(src+x);
			N++;
		}
	}

	if(N!=0){
		return ((double)DSum)/N;
	}
	return 0;
}

double	LinePatternItem::CalcCenterBrightDetail(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	BYTE	*src;
	int		XNumb;
	if(IBuff.IsNull()==true){
		return 0;
	}
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	const LinePatternThreshold	*RThr=GetThresholdR();
	int	YSep;
	int	XSep;
	FlexArea	&A=Area;
	if(A.GetFLineLen()<40 || A.GetHeight()<20)
		YSep=1;
	else
		YSep=2;

	int64	DSum=0;
	int		N=0;
	for(int i=0;i<A.GetFLineLen();i+=YSep){
		int	sy=A.GetFLineAbsY  (i);
		int	y =sy+my;
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

		src=IBuff.GetY(y)+x1;
		if(DynamicMaskMap!=NULL && RThr->ThreshBag.PointMove.ModeDynamicMask==true){
			BYTE	*Mask=DynamicMaskMap[y];
			if(XNumb<40){
				int	Index1=x1>>3;
				int	Index2=(x2+7)>>3;
				bool	FoundMask=false;
				for(int x=Index1;x<=Index2;x++){
					if(Mask[x]!=0){
						FoundMask=true;
						break;
					}
				}
				if(FoundMask==false){
					for(int x=0;x<XNumb;x++){
						DSum+=*(src+x);
					}
					N+=XNumb;
				}
				else{
					for(int x=0;x<XNumb;x++){
						if(GetBmpBitOnY(Mask,x1+x)==0){
							DSum+=*(src+x);
							N++;
						}
					}
				}
			}
			else{
				int	Index1=x1>>3;
				int	Index2=(x2+7)>>3;
				bool	FoundMask=false;
				for(int x=Index1;x<=Index2;x++){
					if(Mask[x]!=0){
						FoundMask=true;
						break;
					}
				}
				if(FoundMask==false){
					for(int x=0;x<XNumb;x+=2){
						DSum+=*(src+x);
					}
					N+=(XNumb>>1);
				}
				else{
					for(int x=0;x<XNumb;x+=2){
						if(GetBmpBitOnY(Mask,x1+x)==0){
							DSum+=*(src+x);
							N++;
						}
					}
				}
			}
		}
		else{
			if(XNumb<40){
				for(int x=0;x<XNumb;x++){
					DSum+=*(src+x);
				}
				N+=XNumb;
			}
			else{
				for(int x=0;x<XNumb;x+=2){
					DSum+=*(src+x);
				}
				N+=(XNumb>>1);
			}
		}
	}
	if(N!=0){
		return ((double)DSum)/N;
	}
	return 0;
}

void	LinePatternItem::SetThresholdFromCommon(SetThresholdLinePatternInfo *Info)
{
	if(Info->BrightWidthIL>=0)
		GetThresholdW()->ThreshBag.BrightWidthIL	=Info->BrightWidthIL	;
	if(Info->BrightWidthIH>=0)
		GetThresholdW()->ThreshBag.BrightWidthIH	=Info->BrightWidthIH	;
	if(Info->BrightWidthOL>=0)
		GetThresholdW()->ThreshBag.BrightWidthOL	=Info->BrightWidthOL	;
	if(Info->BrightWidthOH>=0)
		GetThresholdW()->ThreshBag.BrightWidthOH	=Info->BrightWidthOH	;
	if(Info->NGSizeIL>=0)
		GetThresholdW()->ThreshBag.NGSizeIL			=Info->NGSizeIL			;
	if(Info->NGSizeIH>=0)
		GetThresholdW()->ThreshBag.NGSizeIH			=Info->NGSizeIH			;
	if(Info->NGSizeOL>=0)
		GetThresholdW()->ThreshBag.NGSizeOL			=Info->NGSizeOL			;
	if(Info->NGSizeOH>=0)
		GetThresholdW()->ThreshBag.NGSizeOH			=Info->NGSizeOH			;
	//GetThresholdW()->ThreshBag.TransitDot		=Info->TransitDot		;
	if(Info->SearchDot>=0)
		GetThresholdW()->ThreshBag.SearchDot		=Info->SearchDot		;
	if(Info->AdjustBrightIL>=0)
		GetThresholdW()->ThreshBag.AdjustBrightIL	=Info->AdjustBrightIL	;
	if(Info->AdjustBrightIH>=0)
		GetThresholdW()->ThreshBag.AdjustBrightIH	=Info->AdjustBrightIH	;
	if(Info->AdjustBrightOL>=0)
		GetThresholdW()->ThreshBag.AdjustBrightOL	=Info->AdjustBrightOL	;
	if(Info->AdjustBrightOH>=0)
		GetThresholdW()->ThreshBag.AdjustBrightOH	=Info->AdjustBrightOH	;
	//GetThresholdW()->ThreshBag.GlobalSearchDot	=Info->GlobalSearchDot	;

}

