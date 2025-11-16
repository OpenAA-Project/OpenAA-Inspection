/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\XDisplayDirectPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XImageProcess.h"
#include "XDisplayImagePacket.h"
#include "XDisplayBitImage.h"
#include "swap.h"



SlaveCommReqPasteShape::SlaveCommReqPasteShape(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}
bool	SlaveCommReqPasteShape::Load(QIODevice *f)
{
	if(::Load(f,DrawnGlobalPage)==false){
		return false;
	}
	if(::Load(f,MoveGlobalDx)==false){
		return false;
	}
	if(::Load(f,MoveGlobalDy)==false){
		return false;
	}
	if(::Load(f,InstName)==false){
		return false;
	}
	if(::Load(f,Movx)==false){
		return false;
	}
	if(::Load(f,Movy)==false){
		return false;
	}
	if(::Load(f,ZoomRate)==false){
		return false;
	}
	if(::Load(f,Col)==false){
		return false;
	}
	if(::Load(f,Gx1)==false){
		return false;
	}
	if(::Load(f,Gy1)==false){
		return false;
	}
	if(::Load(f,Gx2)==false){
		return false;
	}
	if(::Load(f,Gy2)==false){
		return false;
	}

	return true;
}
bool	SlaveCommReqPasteShape::Save(QIODevice *f)
{
	if(::Save(f,DrawnGlobalPage)==false){
		return false;
	}
	if(::Save(f,MoveGlobalDx)==false){
		return false;
	}
	if(::Save(f,MoveGlobalDy)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	if(::Save(f,Movx)==false){
		return false;
	}
	if(::Save(f,Movy)==false){
		return false;
	}
	if(::Save(f,ZoomRate)==false){
		return false;
	}
	if(::Save(f,Col)==false){
		return false;
	}
	if(::Save(f,Gx1)==false){
		return false;
	}
	if(::Save(f,Gy1)==false){
		return false;
	}
	if(::Save(f,Gx2)==false){
		return false;
	}
	if(::Save(f,Gy2)==false){
		return false;
	}
	return true;
}

void	SlaveCommReqPasteShape::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	SlaveCommAckPasteShape	*SendBack=(SlaveCommAckPasteShape *)((GetSendBackPacket()==NULL)?new SlaveCommAckPasteShape(GetLayersBase() ,EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;
	QImage	TmpImage(LGx,LGy,QImage::Format_ARGB32);
	//TmpImage.fill(0);
	::ClearImage(TmpImage, 0);

	XYData	*DrawnXY=GetLayersBase()->GetGlobalOutlineOffset(DrawnGlobalPage);
	XYData	*ThisXY =GetLayersBase()->GetGlobalOutlineOffset(CurrentGlobalPage);

	if(A->PastedItemsDraw(localPage 
						,MoveGlobalDx + ThisXY->x - DrawnXY->x
						,MoveGlobalDy + ThisXY->y - DrawnXY->y
						,TmpImage
						,Movx-Gx1/ZoomRate ,Movy-Gy1/ZoomRate
						,ZoomRate ,Col)==true){
		SendBack->Drawn=true;
		SendBack->Pnt=TmpImage;
		SendBack->DrawnPosX=0;
		SendBack->DrawnPosY=0;
	}

	SendBack->Send(this ,GetGlobalPageFrom(),0);
	CloseSendBack(SendBack);
}

SlaveCommAckPasteShape::SlaveCommAckPasteShape(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	DrawnPosX=0;
	DrawnPosY=0;
	Drawn	=false;
}

bool	SlaveCommAckPasteShape::Load(QIODevice *f)
{
	if(::Load(f,Drawn)==false){
		return false;
	}
	if(Drawn==true){
		if(::Load(f,DrawnPosX)==false){
			return false;
		}
		if(::Load(f,DrawnPosY)==false){
			return false;
		}
		if(::Load(f,Pnt)==false){
			return false;
		}
	}
	return true;
}
bool	SlaveCommAckPasteShape::Save(QIODevice *f)
{
	if(::Save(f,Drawn)==false){
		return false;
	}
	if(Drawn==true){
		if(::Save(f,DrawnPosX)==false){
			return false;
		}
		if(::Save(f,DrawnPosY)==false){
			return false;
		}
		if(::Save(f,Pnt)==false){
			return false;
		}
	}
	return true;
}

//===============================================================================================================

SlaveCommSendTemporaryItems::SlaveCommSendTemporaryItems(AlgorithmBase *base 
									  ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase((base!=NULL)?base->GetLayersBase():NULL,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	Data=NULL;
}

bool	SlaveCommSendTemporaryItems::Load(QIODevice *f)
{
	Data.clear();
	if(::Load(f,Data)==false){
		return false;
	}
	return true;
}
bool	SlaveCommSendTemporaryItems::Save(QIODevice *f)
{
	if(::Save(f,Data)==false){
		return false;
	}
	return true;
}

void	SlaveCommSendTemporaryItems::SetData(ItemPointerListInPage *PageData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadWrite);
	PageData->Save(&Buff);
}


void	SlaveCommSendTemporaryItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(L!=NULL){
		AlgorithmInPageRoot	*Pg=L->GetPageData(localPage);
		if(Pg!=NULL){
			ItemPointerListInPage	ItemLists;
			QBuffer	Buff(&Data);
			Buff.open(QIODevice::ReadWrite);
			ItemLists.Load(&Buff,Pg,GetLayersBase());
			Pg->SetTemporaryItems(&ItemLists);
		}
	}
}

SlaveCommSendFixTemporaryItems::SlaveCommSendFixTemporaryItems(AlgorithmBase *base 
									  ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase((base!=NULL)?base->GetLayersBase():NULL,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	Data=NULL;
}

bool	SlaveCommSendFixTemporaryItems::Load(QIODevice *f)
{
	Data.clear();
	if(::Load(f,Data)==false){
		return false;
	}
	return true;
}
bool	SlaveCommSendFixTemporaryItems::Save(QIODevice *f)
{
	if(::Save(f,Data)==false){
		return false;
	}
	return true;
}

void	SlaveCommSendFixTemporaryItems::SetData(ItemPointerListInPage *PageData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadWrite);
	PageData->Save(&Buff);
}


void	SlaveCommSendFixTemporaryItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(L!=NULL){
		AlgorithmInPageRoot	*Pg=L->GetPageData(localPage);
		if(Pg!=NULL){
			GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

			ItemPointerListInPage	ItemLists;
			QBuffer	Buff(&Data);
			Buff.open(QIODevice::ReadWrite);
			ItemLists.Load(&Buff,Pg,GetLayersBase());
			Pg->AddItemsForMove(&ItemLists);
		}
	}
}

//===================================================================================================
SlaveCommReqPasteFromClipboard::SlaveCommReqPasteFromClipboard(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqPasteFromClipboard::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	if(::Load(f,MoveGlobalDx)==false){
		return false;
	}
	if(::Load(f,MoveGlobalDy)==false){
		return false;
	}
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	SlaveCommReqPasteFromClipboard::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	if(::Save(f,MoveGlobalDx)==false){
		return false;
	}
	if(::Save(f,MoveGlobalDy)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	SlaveCommReqPasteFromClipboard::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckPasteFromClipboard	*SendBack=(SlaveCommAckPasteFromClipboard *)((GetSendBackPacket()==NULL)?new SlaveCommAckPasteFromClipboard(GetLayersBase() ,EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	ClipboardAlgorithm	*m=GetLayersBase()->SearchClipboard(*((const XDateTime *)&CreatedTime));
	if(m!=NULL){
		IntList	LocalPages;
		LocalPages.Add(localPage);
		SendBack->ClipboardDatas.CopyInPages(*m,LocalPages);
	}
	SendBack->Send(this ,GetGlobalPageFrom(),0);
	CloseSendBack(SendBack);
}

SlaveCommAckPasteFromClipboard::SlaveCommAckPasteFromClipboard(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
,ClipboardDatas(base)
{
}

bool	SlaveCommAckPasteFromClipboard::Load(QIODevice *f)
{
	if(ClipboardDatas.Load(f)==false){
		return false;
	}
	return true;
}
bool	SlaveCommAckPasteFromClipboard::Save(QIODevice *f)
{
	if(ClipboardDatas.Save(f)==false){
		return false;
	}
	return true;
}

void	SlaveCommAckPasteFromClipboard::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
