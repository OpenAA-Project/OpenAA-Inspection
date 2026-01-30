/*
 * Copyright (C) 2017
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

#include "ShowPieceResultListResource.h"
#include "XShowPieceResultListPacket.h"
#include "XGeneralFunc.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XPieceForReview.h"

ResultPieceList::ResultPieceList(void)
{
	AreaNumber=-1;
	Result	=_Ok;
}

bool	ResultPieceList::Save(QIODevice *f)
{
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	BYTE	d=(BYTE)Result;
	if(::Save(f,d)==false)
		return false;
	return true;
}

bool	ResultPieceList::Load(QIODevice *f)
{
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Result=(ResultAttr)d;
	return true;
}

//====================================================

GUICmdReqPieceList::GUICmdReqPieceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqPieceList::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}

bool	GUICmdReqPieceList::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqPieceList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPieceList	*SendBack=GetSendBack(GUICmdSendPieceList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		PieceForReviewBase *ABase=(PieceForReviewBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceForReview");
		PieceForReviewInPage	*APage=(PieceForReviewInPage *)ABase->GetPageData(localPage);
		for(AlgorithmItemPI	*item=APage->GetFirstData();item!=NULL;item=item->GetNext()){
			PieceForReviewItem	*Am=(PieceForReviewItem *)item;
			ResultPieceList		*Rt=new ResultPieceList();
			if(R->IsResultTimeOut()==true){
				Rt->Result=ResultPieceList::_TimeOver;
			}
			else if(R->IsResultMaxError()==true){
				Rt->Result=ResultPieceList::_MaxError;
			}
			else{
				ResultPosList *RetDim[10000];
				int	N=R->GetPointerListOfResultPosList(Am->GetArea()
												,RetDim ,10000);
				if(N==0){
					Rt->Result=ResultPieceList::_Ok;
				}
				else{
					Rt->Result=ResultPieceList::_Ng;
				}
			}
			Rt->AreaNumber	=Am->AreaNumber;
			Rt->AreaName	=Am->AreaName;
			SendBack->ResData.AppendList(Rt);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendPieceList::GUICmdSendPieceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendPieceList::Load(QIODevice *f)
{
	if(ResData.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendPieceList::Save(QIODevice *f)
{
	if(ResData.Save(f)==false)
		return false;
	return true;
}
