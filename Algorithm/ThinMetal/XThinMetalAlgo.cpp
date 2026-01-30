/*
 * Copyright (C) 2023
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


//#include "ThinMetalFormResource.h"
#include "XThinMetal.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XThinMetalLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"
#include "XAlignmentCommon.h"
#include "XAlgorithmDLL.h"
#include "XDisplaySimPanel.h"
#include "XThinMetalAlgoPacket.h"


ExeResult	ThinMetalItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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

	int	swing=30;
	int	Dx,Dy;
	double	Result;
	int SampleNo;
	int	Judgement=MatchSamples(mx,my,swing,Dx,Dy,Result,SampleNo);
	if(Judgement>=0){
		Res->SetError(Judgement);
		Res->SetAlignedXY(mx,my);
		if(Judgement>=2){
			int	cx,cy;
			GetCenter(cx,cy);
			ResultPosList	*r=new ResultPosList(cx,cy);
			r->result	=0x10000;
			r->SetResult1((DWORD)(Result*10000.0));
			Res->SetResult1(Result*10000.0);
			Res->SetResult2(SampleNo);
			r->SetResult2(SampleNo);
			r->Message	=QString(/**/"M:")+QString::number(Result*100,'f',1)
						+QString(/**/"  File:")
						+SampleImages[SampleNo]->TargetFileName;
			Res->GetPosList().AppendList(r);
		}
	}

	return _ER_true;
}