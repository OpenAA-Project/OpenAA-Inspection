#include "AddItemDialogResource.h"
#include "XPieceForReview.h"
#include "XPieceForReviewPacket.h"
#include "XGeneralFunc.h"
#include "XGUIPacketForDLL.h"
#include "XGUIPieceForReview.h"
#include "XGeneralFunc.h"
#include<QBuffer>


GUICmdAddItemPieceForReview::GUICmdAddItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaNumber	=0;
	SysRegNumber=0;
}

bool	GUICmdAddItemPieceForReview::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,SysRegNumber)==false)
		return false;
	return true;
}
bool	GUICmdAddItemPieceForReview::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,SysRegNumber)==false)
		return false;
	return true;
}

void	GUICmdAddItemPieceForReview::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceForReview");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	CmdAddItemPieceForReview	Cmd(GetLayersBase());
	Cmd.AreaName	=AreaName;
	Cmd.AreaNumber	=AreaNumber;
	Cmd.Area		=Area;
	Cmd.SysRegNumber=SysRegNumber;
	PData->TransmitDirectly(&Cmd);
}

//=================================================================================================

GUICmdReqItemListPieceForReview::GUICmdReqItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemListPieceForReview::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemListPieceForReview	*SendBack=GetSendBack(GUICmdAckItemListPieceForReview,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeList(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckItemListPieceForReview::GUICmdAckItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAckItemListPieceForReview::MakeList(int localPage)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceForReview");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CmdMakePieceForReviewList	Cmd(GetLayersBase());
	Cmd.ListData=&ListData;
	PData->TransmitDirectly(&Cmd);
}

bool	GUICmdAckItemListPieceForReview::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckItemListPieceForReview::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)
		return false;
	return true;
}

//=================================================================================================

GUICmdChangeItemPieceForReview::GUICmdChangeItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID		=0;
	AreaNumber	=0;
	SysRegNumber=0;
}
bool	GUICmdChangeItemPieceForReview::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaNumber)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,SysRegNumber)==false)
		return false;
	return true;
}
bool	GUICmdChangeItemPieceForReview::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaNumber)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,SysRegNumber)==false)
		return false;
	return true;
}
void	GUICmdChangeItemPieceForReview::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceForReview");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	CmdChangeItemPieceForReview	Cmd(GetLayersBase());
	Cmd.ItemID		=ItemID;
	Cmd.AreaNumber	=AreaNumber;
	Cmd.AreaName	=AreaName;
	Cmd.SysRegNumber=SysRegNumber;
	PData->TransmitDirectly(&Cmd);
}