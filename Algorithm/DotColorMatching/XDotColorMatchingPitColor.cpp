/*
 * Copyright (C) 2024
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
#include "swap.h"


int	DotColorMatchingItem::ExecuteProcessingPitColor(ResultInItemRoot *Res
														,ImageBuffer *ImageTargetList[100]
														,int Mx,int My)
{
	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)GetParentBase());

	int	mx=Mx;
	int	my=My;
	const	DotColorMatchingThreshold	*Th=GetThresholdR();
	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	int	LayerNumb=GetLayerNumb();
	RotationPattern	*R=CurrentMasterPattern;
	DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();
	if(LayerNumb>=3 && Th->UseOneLayer==0xFF){
		int	N=R->GetFLineLen();
		int	RL=CenterTargetBrightR-Th->PitBrightWidthRL;
		int	RH=CenterTargetBrightR+Th->PitBrightWidthRH;
		int	GL=CenterTargetBrightG-Th->PitBrightWidthGL;
		int	GH=CenterTargetBrightG+Th->PitBrightWidthGH;
		int	BL=CenterTargetBrightB-Th->PitBrightWidthBL;
		int	BH=CenterTargetBrightB+Th->PitBrightWidthBH;

		for(int i=0;i<N;i++){
			int	Ys	=R->GetFLineAbsY(i);
			int	Xs1	=R->GetFLineLeftX(i);
			int	Y	=Ys+My;
			int	X1	=Xs1+Mx;
			int	Numb=R->GetFLineNumb(i);
			if(Y<0 || MaxLines<=Y){
				continue;
			}
			if(X1<0){
				Numb +=X1;
				X1=0;
			}
			if(DotPerLine<=(X1+Numb)){
				Numb=DotPerLine-X1;
			}
			BYTE	*Rp=ImageTargetList[0]->GetY(Y)+X1;
			BYTE	*Gp=ImageTargetList[1]->GetY(Y)+X1;
			BYTE	*Bp=ImageTargetList[2]->GetY(Y)+X1;
			for(int n=0;n<Numb;n++){
				BYTE	R=Rp[n];
				BYTE	G=Gp[n];
				BYTE	B=Bp[n];
				if(R<RL || RH<R
				|| G<GL || GH<G
				|| B<BL || BH<B){
					ResultPosList	*r=new DotColorMatchingResultPosList(Xs1+n,Ys ,0,0);
					r->result =0x10003+GetResultType();	//NG
					int	MaxDR=max(RL-R,R-RH);
					int	MaxDG=max(GL-G,G-GH);
					int	MaxDB=max(BL-B,B-BH);
					int	MaxCol=max(MaxDR,MaxDG,MaxDB);
					r->SetResult1(MaxCol);
					r->NGSize	=1;
					ResultPosListContainer	NowList;
					NowList.AppendList(r);
					Res->MovePosList(NowList);
					Res->SetItemSearchedXY(0,0);
					
					Res->SetAlignedXY(mx,my);
					ResultDx=mx;
					ResultDy=my;
					ResultCode=3;
					Res->SetResult1(MaxCol);
					Res->SetResult2(MaxCol);
					Res->SetError(21);
					return 21;			//NG
				}
			}
		}
	}
	else
	if(LayerNumb==1 && Th->UseOneLayer==0xFF){
		int	N=R->GetFLineLen();
		int	RL=CenterTargetBrightR-Th->PitBrightWidthRL;
		int	RH=CenterTargetBrightR+Th->PitBrightWidthRH;

		for(int i=0;i<N;i++){
			int	Ys	=R->GetFLineAbsY(i);
			int	Xs1	=R->GetFLineLeftX(i);
			int	Y	=Ys+My;
			int	X1	=Xs1+Mx;
			int	Numb=R->GetFLineNumb(i);
			if(Y<0 || MaxLines<=Y){
				continue;
			}
			if(X1<0){
				Numb +=X1;
				X1=0;
			}
			if(DotPerLine<=(X1+Numb)){
				Numb=DotPerLine-X1;
			}
			BYTE	*Rp=ImageTargetList[0]->GetY(Y)+X1;

			for(int n=0;n<Numb;n++){
				BYTE	R=Rp[n];
				if(R<RL || RH<R){
					ResultPosList	*r=new DotColorMatchingResultPosList(Xs1+n,Ys ,0,0);
					r->result =0x10003+GetResultType();	//NG
					int	MaxDR=max(RL-R,R-RH);
					r->SetResult1(MaxDR);
					r->NGSize	=1;
					ResultPosListContainer	NowList;
					NowList.AppendList(r);
					Res->MovePosList(NowList);
					Res->SetItemSearchedXY(0,0);
					
					Res->SetAlignedXY(mx,my);
					ResultDx=mx;
					ResultDy=my;
					ResultCode=3;
					Res->SetResult1(MaxDR);
					Res->SetResult2(MaxDR);
					Res->SetError(21);
					return 21;			//NG
				}
			}
		}
	}

	return 1;
}