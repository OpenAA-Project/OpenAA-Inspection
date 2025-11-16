/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceForReview.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PieceForReviewResource.h"
#include "XPieceForReview.h"
#include "XPieceReviewSide.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XPieceForReviewPacket.h"
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//====================================================================
ReviewSideItems::ReviewSideItems(const ReviewSideItems &src)
{
	GlobalPage	=src.GlobalPage;
	AreaNumber	=src.AreaNumber;
	AreaName	=src.AreaName;
}


bool	ReviewSideItems::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	return true;
}

bool	ReviewSideItems::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	return true;
}

//===========================================================================================================

PieceReviewSideBase::PieceReviewSideBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPieceReviewSide			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorPieceReviewSide		=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;

	SetParam(&ColorPieceReviewSide	, /**/"Color" ,/**/"ColorPieceReviewSide"	,"Color for PieceForReview area");
	SetParam(&ColorSelected			, /**/"Color" ,/**/"ColorSelected"			,"Color for Selected Piece");
	SetParam(&ColorActive			, /**/"Color" ,/**/"ColorActive"			,"Color for Active Piece");
	SetParam(&TransparentLevel		, /**/"Color" ,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&NegColorPieceReviewSide, /**/"Color" ,/**/"NegColorPieceReviewSide"	,"Color for Negative PieceForReview area");
	SetParam(&NegColorSelected		, /**/"Color" ,/**/"NegColorSelected"		,"Color for Negative selected PieceForReview");

	Restructured=false;
}
void	PieceReviewSideBase::TransmitDirectly(GUIDirectMessage *packet)
{

}

ExeResult	PieceReviewSideBase::ExecuteInitialAfterEdit	(int ExeID 
															,ResultBaseForAlgorithmRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	if(Restructured==false){
		ReviewSideItemsContainer	ItemsDim[100];
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage);
			GUICmdReqAlgorithmGeneralData	PacketReq(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			PacketReq.BuildData(sRoot,sName,PieceReviewSideReqItems ,PieceReviewSideSendItems);

			GUICmdSendAlgorithmGeneralData	PacketSend(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			ClassPieceReviewSideReqItem	*RPoint=(ClassPieceReviewSideReqItem *)PacketReq.GetData();
			RPoint->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);

			PacketReq.Send(globalPage,0,PacketSend);

			ClassPieceReviewSideSendItem	*ThrePoint=(ClassPieceReviewSideSendItem *)PacketSend.GetData();
			ItemsDim[localPage]=ThrePoint->Items;
		}
		ReviewSideItems *OnePageItem=NULL;
		int	LocalPage=-1;
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			for(ReviewSideItems *a=ItemsDim[localPage].GetFirst();a!=NULL;a=a->GetNext()){
				bool	ModeOtherPage=false;
				for(int localPage2=localPage+1;localPage2<GetPageNumb();localPage2++){
					for(ReviewSideItems *b=ItemsDim[localPage2].GetFirst();a!=NULL;a=a->GetNext()){
						if(a->AreaNumber==b->AreaNumber){
							ModeOtherPage=true;
							break;
						}
					}
				}
				if(ModeOtherPage==false){
					OnePageItem=a;
					LocalPage=localPage;
					goto	FoundOnePage;
				}
			}
		}
FoundOnePage:;
		if(OnePageItem!=NULL){
			DataInPage *Pg=GetLayersBase()->GetPageData(LocalPage);
			int	globalPage=OnePageItem->GlobalPage;
			GUICmdReqAlgorithmGeneralData	PacketReq(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			PacketReq.BuildData(sRoot,sName,PieceReviewSideReqImage ,PieceReviewSideSendImage);

			GUICmdSendAlgorithmGeneralData	PacketSend(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
			ClassPieceReviewSideReqImage	*RPoint=(ClassPieceReviewSideReqImage *)PacketReq.GetData();
			RPoint->GlobalPage=globalPage;
			RPoint->AreaNumber=OnePageItem->AreaNumber;

			PacketReq.Send(globalPage,0,PacketSend);
			ClassPieceReviewSideSendImage	*SPoint=(ClassPieceReviewSideSendImage *)PacketSend.GetData();

			int	W=SPoint->ImageR.GetWidth();
			int	H=SPoint->ImageR.GetHeight();

			Pg->SetDotPerLine(W);
			Pg->SetMaxLines	 (H);
			GetParamGlobal()->PageNumb	=1;

			GetLayersBase()->InitialCreatePages(true);
			DataInPage	*Dp=GetLayersBase()->GetPageData(0);
			ImagePointerContainer MasterImages;
			Dp->GetMasterImages(MasterImages);
			if(GetLayerNumb(LocalPage)>=3){
				SPoint->ImageR.CopyToBuffer(*MasterImages[0]);
				SPoint->ImageG.CopyToBuffer(*MasterImages[1]);
				SPoint->ImageB.CopyToBuffer(*MasterImages[2]);
			}
			else if(GetLayerNumb(LocalPage)==2){
				SPoint->ImageR.CopyToBuffer(*MasterImages[0]);
				SPoint->ImageG.CopyToBuffer(*MasterImages[1]);
			}
			else if(GetLayerNumb(LocalPage)==1){
				SPoint->ImageR.CopyToBuffer(*MasterImages[0]);
			}
			Restructured=true;
		}
	}
	return _ER_true;
}

AlgorithmDrawAttr	*PieceReviewSideBase::CreateDrawAttr(void)
{
	return NULL;
}

bool	PieceReviewSideBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	PieceReviewSideBase::LoadOnlyBase(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver<0 || Ver>1){
		return false;
	}
	QString	dllRoot,dllName;
	if(::Load(f,dllRoot)==false){
		return false;
	}
	if(::Load(f,dllName)==false){
		return false;
	}
	int32	iAllocatedPageNumb;
	if(::Load(f,iAllocatedPageNumb)==false){
		return(false);
	}
	Restructured=false;
	return true;
}


bool	PieceReviewSideBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==PieceReviewSideReqItems){
		delete	data;
		return true;
	}
	else if(Command==PieceReviewSideSendItems){
		delete	data;
		return true;
	}
	else if(Command==PieceReviewSideReqImage){
		delete	data;
		return true;
	}
	else if(Command==PieceReviewSideSendImage){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*PieceReviewSideBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==PieceReviewSideReqItems){
		return new ClassPieceReviewSideReqItem();
	}
	else if(Command==PieceReviewSideSendItems){
		ClassPieceReviewSideSendItem	*pSend=new ClassPieceReviewSideSendItem();
		if(reqData!=NULL){
			ClassPieceReviewSideReqItem	*req=(ClassPieceReviewSideReqItem *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==PieceReviewSideReqImage){
		return new ClassPieceReviewSideReqImage();
	}
	else if(Command==PieceReviewSideSendImage){
		ClassPieceReviewSideSendImage	*pSend=new ClassPieceReviewSideSendImage();
		if(reqData!=NULL){
			ClassPieceReviewSideReqImage	*req=(ClassPieceReviewSideReqImage *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	PieceReviewSideBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==PieceReviewSideReqItems){
		ClassPieceReviewSideReqItem	*p=(ClassPieceReviewSideReqItem *)data;
		return p->Load(f);
	}
	else if(Command==PieceReviewSideSendItems){
		ClassPieceReviewSideSendItem	*p=(ClassPieceReviewSideSendItem *)data;
		return p->Load(f);
	}
	else if(Command==PieceReviewSideReqImage){
		ClassPieceReviewSideReqImage	*p=(ClassPieceReviewSideReqImage *)data;
		return p->Load(f);
	}
	else if(Command==PieceReviewSideSendImage){
		ClassPieceReviewSideSendImage	*p=(ClassPieceReviewSideSendImage *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	PieceReviewSideBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==PieceReviewSideReqItems){
		ClassPieceReviewSideReqItem	*p=(ClassPieceReviewSideReqItem *)data;
		return p->Save(f);
	}
	else if(Command==PieceReviewSideSendItems){
		ClassPieceReviewSideSendItem	*p=(ClassPieceReviewSideSendItem *)data;
		return p->Save(f);
	}
	else if(Command==PieceReviewSideReqImage){
		ClassPieceReviewSideReqImage	*p=(ClassPieceReviewSideReqImage *)data;
		return p->Save(f);
	}
	else if(Command==PieceReviewSideSendImage){
		ClassPieceReviewSideSendImage	*p=(ClassPieceReviewSideSendImage *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	PieceReviewSideBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==PieceReviewSideReqItems){
		ClassPieceReviewSideReqItem	*p=(ClassPieceReviewSideReqItem *)data;
		return true;
	}
	else if(Command==PieceReviewSideSendItems){
		ClassPieceReviewSideSendItem	*p=(ClassPieceReviewSideSendItem *)data;
		return true;
	}
	else if(Command==PieceReviewSideReqImage){
		ClassPieceReviewSideReqImage	*p=(ClassPieceReviewSideReqImage *)data;
		return true;
	}
	else if(Command==PieceReviewSideSendImage){
		ClassPieceReviewSideSendImage	*p=(ClassPieceReviewSideSendImage *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}

