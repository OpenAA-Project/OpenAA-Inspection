#include "PieceListFormResource.h"
#include "PieceListForm.h"
#include "ui_PieceListForm.h"
#include "XGeneralFunc.h"
#include "XPieceForReview.h"
#include "XPieceListReviewSidePacket.h"


//==================================================================
ItemListReviewSide::ItemListReviewSide(const ItemListReviewSide &src)
{
	AreaNumber	=src.AreaNumber;
	AreaName	=src.AreaName;
}
bool	ItemListReviewSide::operator==(ItemListReviewSide &src)
{
	if(AreaNumber==src.AreaNumber
	&& AreaName==src.AreaName){
		return true;
	}
	return false;
}
bool	ItemListReviewSide::Save(QIODevice *f)
{
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	return true;
}

bool	ItemListReviewSide::Load(QIODevice *f)
{
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	return true;
}

bool	ItemListReviewSideContainer::IsInclude(ItemListReviewSide *c)
{
	for(ItemListReviewSide *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(*a==*c){
			return true;
		}
	}
	return false;
}

GUICmdReqItemListReviewSide::GUICmdReqItemListReviewSide(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqItemListReviewSide::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqItemListReviewSide::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqItemListReviewSide::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemListReviewSide	*SendBack=GetSendBack(GUICmdSendItemListReviewSide,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendItemListReviewSide::GUICmdSendItemListReviewSide(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendItemListReviewSide::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendItemListReviewSide::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendItemListReviewSide::Make(int localPage)
{
	PieceReviewSideBase *ABase=(PieceReviewSideBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceReviewSide");
	PieceReviewSideInPage	*APage=(PieceReviewSideInPage *)ABase->GetPageData(localPage);
	for(AlgorithmItemPI	*item=APage->GetFirstData();item!=NULL;item=item->GetNext()){
		PieceForReviewItem	*Am=(PieceForReviewItem *)item;
		ItemListReviewSide	*t=new ItemListReviewSide();
		t->AreaNumber	=Am->AreaNumber;
		t->AreaName		=Am->AreaName;
		ListData.AppendList(t);
	}
}
