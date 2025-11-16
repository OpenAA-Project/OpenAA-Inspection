/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ReplaceImage\XReplaceImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XReplaceImage.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

ReplaceImageInPage::ReplaceImageInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<ReplaceImageItem,ReplaceImageBase>(parent)
{
}
ReplaceImageInPage::~ReplaceImageInPage(void)
{
}

ExeResult	ReplaceImageInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ReplaceImageItem	*t=tGetFirstData();
	if(t==NULL){
		ReplaceImageItem	*Item=new ReplaceImageItem();
		AppendItem(Item);
	}
	return _ER_true;
}

void	ReplaceImageInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReplaceImageReqDraw	*CmdReplaceImageReqDrawVar=dynamic_cast<CmdReplaceImageReqDraw *>(packet);
	if(CmdReplaceImageReqDrawVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->Draw(*CmdReplaceImageReqDrawVar->Image
					,CmdReplaceImageReqDrawVar->movx 
					,CmdReplaceImageReqDrawVar->movy
					,CmdReplaceImageReqDrawVar->ZoomRate
					,&CmdReplaceImageReqDrawVar->Attr);
		return;
	}
	CmdReplaceImageAddMaskArea	*CmdReplaceImageAddMaskAreaVar=dynamic_cast<CmdReplaceImageAddMaskArea *>(packet);
	if(CmdReplaceImageAddMaskAreaVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		CmdReplaceImageAddMaskAreaVar->AverageColor=Item->AddPickArea(CmdReplaceImageAddMaskAreaVar->Area);
		Item->OriginalMaskOutline.RemoveAll();
		Item->CurrentMaskOutline .RemoveAll();
		Item->CalcMask();
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageAddMaskImage	*CmdReplaceImageAddMaskImageVar=dynamic_cast<CmdReplaceImageAddMaskImage *>(packet);
	if(CmdReplaceImageAddMaskImageVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->MaskImage=CmdReplaceImageAddMaskImageVar->Image;
		Item->OriginalMaskOutline.RemoveAll();
		Item->CurrentMaskOutline .RemoveAll();
		Item->CalcMask();
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageCalcMask	*CmdReplaceImageCalcMaskVar=dynamic_cast<CmdReplaceImageCalcMask *>(packet);
	if(CmdReplaceImageCalcMaskVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->CalcMask();
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageMouseLDown	*CmdReplaceImageMouseLDownVar=dynamic_cast<CmdReplaceImageMouseLDown *>(packet);
	if(CmdReplaceImageMouseLDownVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->GenerateEdge(CmdReplaceImageMouseLDownVar->X,CmdReplaceImageMouseLDownVar->Y);
		Item->CalcMask();
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageSetCompositeColor	*CmdReplaceImageSetCompositeColorVar=dynamic_cast<CmdReplaceImageSetCompositeColor *>(packet);
	if(CmdReplaceImageSetCompositeColorVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->CompColor=CmdReplaceImageSetCompositeColorVar->Color;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageSetCompositeImage	*CmdReplaceImageSetCompositeImageVar=dynamic_cast<CmdReplaceImageSetCompositeImage *>(packet);
	if(CmdReplaceImageSetCompositeImageVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->CompImage=CmdReplaceImageSetCompositeImageVar->Image;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageSetCompositePage	*CmdReplaceImageSetCompositePageVar=dynamic_cast<CmdReplaceImageSetCompositePage *>(packet);
	if(CmdReplaceImageSetCompositePageVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		Item->CompPage=CmdReplaceImageSetCompositePageVar->CompPage;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageProcessMode	*CmdReplaceImageProcessModeVar=dynamic_cast<CmdReplaceImageProcessMode *>(packet);
	if(CmdReplaceImageProcessModeVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		ReplaceImageThreshold	*WThr=Item->GetThresholdW();
		WThr->OpeComp			=CmdReplaceImageProcessModeVar->CompMode;
		WThr->CompositeInside	=CmdReplaceImageProcessModeVar->CompositeInside;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageMaskMode	*CmdReplaceImageMaskModeVar=dynamic_cast<CmdReplaceImageMaskMode *>(packet);
	if(CmdReplaceImageMaskModeVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		ReplaceImageThreshold	*WThr=Item->GetThresholdW();
		WThr->OpeIso			=CmdReplaceImageMaskModeVar->OpeMode;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
	CmdReplaceImageMakeAreaMask	*CmdReplaceImageMakeAreaMaskVar=dynamic_cast<CmdReplaceImageMakeAreaMask *>(packet);
	if(CmdReplaceImageMakeAreaMaskVar!=NULL){
		ReplaceImageItem	*Item=tGetFirstData();
		if(Item==NULL){
			Item=new ReplaceImageItem();
			AppendItem(Item);
		}
		ReplaceImageThreshold	*WThr=Item->GetThresholdW();
		WThr->OpeIso			=ReplaceImageThreshold::_RI_ByDrawing;
		Item->MaskArea	=CmdReplaceImageMakeAreaMaskVar->Area;
		GetLayersBase()->SetEnableProcess(true);
		return;
	}
}

//===========================================================================================
ReplaceImageBase::ReplaceImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorNormal			=Qt::darkGreen;
	ColorSelected		=Qt::green;
	ColorActive			=Qt::red;
	Color0				=Qt::green;
	Color1				=Qt::yellow;
	Color2				=Qt::darkRed;
	Color3				=Qt::cyan;
	Color4				=Qt::magenta;
	Color5				=Qt::darkGreen;
	Color6				=Qt::darkYellow;
	Color7				=Qt::darkCyan;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&Color0			, /**/"Color"	,/**/"Color0"		,"Level Color 0");
	SetParam(&Color1			, /**/"Color"	,/**/"Color1"		,"Level Color 1");
	SetParam(&Color2			, /**/"Color"	,/**/"Color2"		,"Level Color 2");
	SetParam(&Color3			, /**/"Color"	,/**/"Color3"		,"Level Color 3");
	SetParam(&Color4			, /**/"Color"	,/**/"Color4"		,"Level Color 4");
	SetParam(&Color5			, /**/"Color"	,/**/"Color5"		,"Level Color 5");
	SetParam(&Color6			, /**/"Color"	,/**/"Color6"		,"Level Color 6");
	SetParam(&Color7			, /**/"Color"	,/**/"Color7"		,"Level Color 7");
}

AlgorithmDrawAttr	*ReplaceImageBase::CreateDrawAttr(void)
{
	return new ReplaceImageDrawAttr();
}

ReplaceImageInPage	*ReplaceImageBase::NewChild(AlgorithmBase *parent)
{	
	return(new ReplaceImageInPage(parent));
}
void	ReplaceImageBase::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdCreateTempReplaceImageItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempReplaceImageItemPacket *>(packet);
	//if(CreateBlockItem!=NULL){
	//	CreateBlockItem->Point=new ReplaceImageItem();
	//	return;
	//}
	//CmdCreateByteArrayFromReplaceImageItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromReplaceImageItemPacket *>(packet);
	//if(BAFromBlockItem!=NULL){
	//	QBuffer	Buff(&BAFromBlockItem->Buff);
	//	Buff.open(QIODevice::ReadWrite);
	//	BAFromBlockItem->Point->Save(&Buff);
	//}
	//CmdLoadReplaceImageItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadReplaceImageItemPacketFromByteArray *>(packet);
	//if(FromBA!=NULL){
	//	QBuffer	MBuff(&FromBA->Buff);
	//	MBuff.open(QIODevice::ReadWrite);
	//	FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	//}
	//CmdReplaceImageItemIDList	*CmdReplaceImageItemIDListVar=dynamic_cast<CmdReplaceImageItemIDList *>(packet);
	//if(CmdReplaceImageItemIDListVar!=NULL){
	//}
}

bool	ReplaceImageBase::GeneralDataRelease(int32 Command,void *data)
{
	//if(Command==ReplaceImageHistogramListSendCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageHistogramListReqCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageReqThresholdReqCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageReqThresholdSendCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageReqTryThresholdCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageSendTryThresholdCommand){
	//	delete	data;
	//	return true;
	//}
	//else if(Command==ReplaceImageReqChangeShiftCommand){
	//	delete	data;
	//	return true;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataRelease(Command,data);
	//}
	return true;
}
void	*ReplaceImageBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	//if(Command==ReplaceImageReqThresholdReqCommand){
	//	return new ReplaceImageThresholdReq();
	//}
	//else if(Command==ReplaceImageReqThresholdSendCommand){
	//	ReplaceImageThresholdSend	*pSend=new ReplaceImageThresholdSend();
	//	if(reqData!=NULL){
	//		ReplaceImageThresholdReq	*req=(ReplaceImageThresholdReq *)reqData;
	//		pSend->ConstructList(req,this);
	//	}
	//	return pSend;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataCreate(Command,reqData);
	//}

	return NULL;
}
bool	ReplaceImageBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	//if(Command==ReplaceImageReqThresholdReqCommand){
	//	ReplaceImageThresholdReq	*p=(ReplaceImageThresholdReq *)data;
	//	return p->Load(f);
	//}
	//else if(Command==ReplaceImageReqThresholdSendCommand){
	//	ReplaceImageThresholdSend	*p=(ReplaceImageThresholdSend *)data;
	//	return p->Load(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataLoad(f,Command,data);
	//}
	return false;
}
bool	ReplaceImageBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	//if(Command==ReplaceImageReqThresholdReqCommand){
	//	ReplaceImageThresholdReq	*p=(ReplaceImageThresholdReq *)data;
	//	return p->Save(f);
	//}
	//else if(Command==ReplaceImageReqThresholdSendCommand){
	//	ReplaceImageThresholdSend	*p=(ReplaceImageThresholdSend *)data;
	//	return p->Save(f);
	//}
	//else{
	//	return AlgorithmBase::GeneralDataSave(f,Command,data);
	//}

	return false;
}
bool	ReplaceImageBase::GeneralDataReply(int32 Command,void *data)
{
	//if(Command==ReplaceImageReqThresholdReqCommand){
	//	ReplaceImageThresholdReq	*p=(ReplaceImageThresholdReq *)data;
	//	return true;
	//}
	//else if(Command==ReplaceImageReqThresholdSendCommand){
	//	ReplaceImageThresholdSend	*p=(ReplaceImageThresholdSend *)data;
	//	return true;
	//}
	//else{
	//	return AlgorithmBase::GeneralDataReply(Command,data);
	//}

	return false;
}
