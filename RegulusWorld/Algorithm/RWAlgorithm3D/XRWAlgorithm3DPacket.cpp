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

#include "XRWAlgorithm3D.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

RWAlgorithm3DThresholdReq::RWAlgorithm3DThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	RWAlgorithm3DThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
bool	RWAlgorithm3DThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

RWAlgorithm3DThresholdSend::RWAlgorithm3DThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
}

void	RWAlgorithm3DThresholdSend::ConstructList(RWAlgorithm3DThresholdReq *reqPacket,RWAlgorithm3DBase *Base)
{
	//GlobalPage	=reqPacket->GlobalPage;
	//ItemID		=reqPacket->ItemID;
	//
	//int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	//AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	//if(Ap!=NULL){
	//	AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
	//	if(item!=NULL){
	//		RWAlgorithm3DItem	*BItem=(RWAlgorithm3DItem *)item;
	//
	//		const	RWAlgorithm3DThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
	//	}
	//}
}

bool	RWAlgorithm3DThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}
bool	RWAlgorithm3DThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}