#include "XPieceForReview.h"
#include "XPieceReviewSide.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XPieceForReviewPacket.h"
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"

bool	ClassPieceReviewSideReqItem::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	return true;
}

bool	ClassPieceReviewSideReqItem::Load(QIODevice *f)	
{	
	if(::Load(f,GlobalPage)==false)
		return false;
	return true;
}


void	ClassPieceReviewSideSendItem::ConstructList(ClassPieceReviewSideReqItem *Req ,PieceReviewSideBase *ABase)
{
	int	LocalPage=ABase->GetLayersBase()->GetLocalPageFromGlobal(Req->GlobalPage);
	AlgorithmInPageRoot	*APage=ABase->GetPageData(LocalPage);
	PieceReviewSideInPage	*pAPage=(PieceReviewSideInPage *)APage;
	for(AlgorithmItemPI	*Item=pAPage->GetFirstData();Item!=NULL;Item=Item->GetNext()){
		PieceForReviewItem	*Am=(PieceForReviewItem *)Item;
		ReviewSideItems	*c=new ReviewSideItems();
		c->GlobalPage	=Req->GlobalPage;
		c->AreaNumber	=Am->AreaNumber;
		c->AreaName		=Am->AreaName;
		Items.AppendList(c);
	}
}

bool	ClassPieceReviewSideSendItem::Save(QIODevice *f)
{
	if(Items.Save(f)==false)
		return false;
	return true;
}

bool	ClassPieceReviewSideSendItem::Load(QIODevice *f)
{
	if(Items.Load(f)==false)
		return false;
	return true;
}

//===============================================================

bool	ClassPieceReviewSideReqImage::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	return true;
}

bool	ClassPieceReviewSideReqImage::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	return true;
}


void	ClassPieceReviewSideSendImage::ConstructList(ClassPieceReviewSideReqImage *Req ,PieceReviewSideBase *ABase)
{
	int	LocalPage=ABase->GetLayersBase()->GetLocalPageFromGlobal(Req->GlobalPage);
	DataInPage	*Dp=ABase->GetLayersBase()->GetPageData(LocalPage);
	ImagePointerContainer MasterImages;
	Dp->GetMasterImages(MasterImages);

	AlgorithmInPageRoot	*APage=ABase->GetPageData(LocalPage);
	PieceReviewSideInPage	*pAPage=(PieceReviewSideInPage *)APage;
	for(AlgorithmItemPI	*Item=pAPage->GetFirstData();Item!=NULL;Item=Item->GetNext()){
		PieceForReviewItem	*Am=(PieceForReviewItem *)Item;
		if(Am->AreaNumber==Req->AreaNumber){
			if(ABase->GetLayerNumb(LocalPage)>=3){
				ImageBuffer *BufferR=MasterImages[0];
				ImageBuffer *BufferG=MasterImages[1];
				ImageBuffer *BufferB=MasterImages[2];
				ImageR.Set(Am->GetArea(),*BufferR);
				ImageG.Set(Am->GetArea(),*BufferG);
				ImageB.Set(Am->GetArea(),*BufferB);
			}
			else if(ABase->GetLayerNumb(LocalPage)==2){
				ImageBuffer *BufferR=MasterImages[0];
				ImageBuffer *BufferG=MasterImages[1];
				ImageR.Set(Am->GetArea(),*BufferR);
				ImageG.Set(Am->GetArea(),*BufferG);
			}
			else if(ABase->GetLayerNumb(LocalPage)==1){
				ImageBuffer *BufferR=MasterImages[0];
				ImageR.Set(Am->GetArea(),*BufferR);
			}
			ImageR.MoveToNoClip(-Am->GetArea().GetMinX(),-Am->GetArea().GetMinY());
			ImageG.MoveToNoClip(-Am->GetArea().GetMinX(),-Am->GetArea().GetMinY());
			ImageB.MoveToNoClip(-Am->GetArea().GetMinX(),-Am->GetArea().GetMinY());
			break;
		}
	}
}

bool	ClassPieceReviewSideSendImage::Save(QIODevice *f)
{
	if(ImageR.Save(f)==false)
		return false;
	if(ImageG.Save(f)==false)
		return false;
	if(ImageB.Save(f)==false)
		return false;
	return true;
}

bool	ClassPieceReviewSideSendImage::Load(QIODevice *f)
{
	if(ImageR.Load(f)==false)
		return false;
	if(ImageG.Load(f)==false)
		return false;
	if(ImageB.Load(f)==false)
		return false;
	return true;
}
