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
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XLearningRegist.h"

int	DotColorMatchingItem::ExecuteProcessingVariation(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, ImageBuffer *ImageMasterList[]
								, int dx,int dy)
{
	const	DotColorMatchingThreshold	*Thr=GetThresholdR();

	if(GetArea().GetPatternByte()>=Thr->VariationAdaptMinSize){
		double DAvrR,DAvrG,DAvrB;
		if(Thr->VariationDifMaster==false){
			DeviationResultR=CurrentMasterPattern->GetVar(dx ,dy
														,*ImageTargetList[0]
														,DAvrR);
		}
		else{
			DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();

			if(AP->VarietyMap[0].IsValid()==false){
				DeviationResultR=CurrentMasterPattern->GetVarByDiffMaster(dx ,dy
															,*ImageTargetList[0]
															,*ImageMasterList[0]
															,DAvrR);
			}
			else{
				DeviationResultR=CurrentMasterPattern->GetVarByDiffMasterVariety(dx ,dy
															,*ImageTargetList[0]
															,*ImageMasterList[0]
															,AP->VarietyMap[0]
															,Thr->VarietySigma
															,DAvrR);
			}
		}
		double	dR=DeviationResultR-MasterVariationR*Thr->VariationSubMasterVari;
		if(dR<0){
			dR=0;
		}
		DeviationResultR=sqrt(dR);
		if(GetLayerNumb()>=3){
			DeviationResultG=CurrentMasterPattern->GetVar(dx ,dy
			                                ,*ImageTargetList[1]
				                            ,DAvrG);
			DeviationResultG=sqrt(DeviationResultG);
			DeviationResultB=CurrentMasterPattern->GetVar(dx ,dy
			                                ,*ImageTargetList[2]
				                            ,DAvrB);
			DeviationResultB=sqrt(DeviationResultB);
		}
		if(DeviationResultR<Thr->VariationRL || Thr->VariationRH<DeviationResultR){
			SetErrorInVariation(Res,0x30,DeviationResultR,dx,dy);
			return 2;				//NG
		}
		if(GetLayerNumb()>=3){
			if(DeviationResultG<Thr->VariationGL || Thr->VariationGH<DeviationResultG){
				SetErrorInVariation(Res,0x31,DeviationResultG,dx,dy);
				return 2;				//NG
			}
			if(DeviationResultB<Thr->VariationBL || Thr->VariationBH<DeviationResultB){
				SetErrorInVariation(Res,0x32,DeviationResultB,dx,dy);
				return 2;				//NG
			}
		}
	}
	Res->ClearPosList();
	return 1;	//OK
}

void	DotColorMatchingItem::SetErrorInVariation(ResultInItemRoot* Res
								,int ErrorCode
								,double DeviationValue
								, int dx,int dy)
{
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
	r->SetResultCode (0x10000+0x800+ErrorCode);
	r->SetResult(DeviationValue);
	r->NGShape=*CurrentMasterPattern;
	ResultPosListContainer	NowList;
	NowList.AppendList(r);
	Res->MovePosList(NowList);
	Res->SetItemSearchedXY(0,0);

	Res->SetAlignedXY(dx,dy);
	ResultCode=ErrorCode;
	Res->SetResult1(DeviationValue);
	Res->SetError(ErrorCode);
}


double  RotationPattern::GetVarByDiffMasterVariety(int dx ,int dy
									,ImageBuffer &TargetBuff
									,ImageBuffer &MasterBuff
									,ConstMapBuffer &VarietyBuff
									,float SigmaV
									,double &DAvr)          const
{
	uint	D=0;
	uint	Avr=0;
	uchar	*p1;
	uchar	*p2;
	uchar	*v;
	int 	N=0;
	int		tMaxX=TargetBuff.GetWidth();
	int		tMaxY=TargetBuff.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int my =GetFLineAbsY(i);
		int ty =my+dy;
		if(ty<0)
			continue;
		if(tMaxY<=ty)
			break;
		int	mx1=GetFLineLeftX(i);
		int	mx2=GetFLineRightX(i);
		int	tx1=mx1+dx;
		int	tx2=mx2+dx;
		if(tx1<0)
			tx1=0;
		if(tMaxX<=tx2)
			tx2=tMaxX;
		if(mx1<0)
			mx1=0;
		if(tMaxX<=mx2)
			mx2=tMaxX;
		int	tNumb=tx2-tx1;
		int	mNumb=mx2-mx1;
		int	Numb=min(tNumb,mNumb);
		p1=TargetBuff.GetY(ty)+tx1;
		p2=MasterBuff.GetY(my)+mx1;
		v =VarietyBuff.GetY(my)+mx1;
		if(Numb>0){
			for(int x=0;x<Numb;x++ ,p1++,p2++,v++){
				int	c=*p1 - *p2;
				if(c>=0){
					c-=*v*SigmaV;
					if(c<0){
						c=0;
					}
				}
				else{
					c+=*v*SigmaV;
					if(c>0){
						c=0;
					}
				}
				Avr+= c;
				D+=c*c;
			}
			N +=Numb;
		}
	}
	if(N<=0)
		return 0;
	DAvr=(double)Avr/(double)N;

	double	DD=(double)D/(double)N;
	DD=DD-DAvr*DAvr;
	if(DD<0){
		return(0);
	}

	DD=sqrt(DD);

	return(DD);
}