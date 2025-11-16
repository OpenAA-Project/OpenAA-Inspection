#include "XPropertySavePartialImagePacket.h"
#include "XDisplayImagePacket.h"
#include "AddItemDialog.h"
#include "XSavePartialImage.h"

//================================================================================
GUICmdReqGridList::GUICmdReqGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqGridList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendGridList	*SendBack=GetSendBack(GUICmdSendGridList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SavePartialImage");
	if(PBase==NULL)
		return;
	SavePartialImageInPage	*PPage=dynamic_cast<SavePartialImageInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqSavePartialImageInfo	Da(GetLayersBase());
		Da.Info			=&SendBack->GridList;
		PPage->TransmitDirectly(&Da);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendGridList::GUICmdSendGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendGridList::Load(QIODevice *f)
{
	if(GridList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendGridList::Save(QIODevice *f)
{
	if(GridList.Save(f)==false)
		return false;
	return true;
}

GUICmdAddAreaManual::GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SavePartialImage");
	if(PBase==NULL)
		return;
	SavePartialImageInPage	*PPage=dynamic_cast<SavePartialImageInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAddAreaManual	Da(GetLayersBase());
		Da.Area			=Area;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=0;
}
bool	GUICmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
	
bool	GUICmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemInfo	*SendBack=GetSendBack(GUICmdSendItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SavePartialImage");
	if(PBase==NULL)
		return;
	SavePartialImageInPage	*PPage=dynamic_cast<SavePartialImageInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqItemInfo	Da(GetLayersBase());
		Da.ItemID	=ItemID;
		PPage->TransmitDirectly(&Da);
		SendBack->ItemID			=Da.ItemID;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdSendItemInfo::GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdSendItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

