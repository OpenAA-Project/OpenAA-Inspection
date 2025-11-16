#include "AddSourceItemDialogResource.h"

#include"XPropertySkipMarkPacket.h"
#include "XDisplayImagePacket.h"
#include "XSkipMark.h"

//================================================================================
GUICmdReqGridList::GUICmdReqGridList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqGridList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendGridList	*SendBack=GetSendBack(GUICmdSendGridList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqSkipMarkInfo	Da(GetLayersBase());
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
	NamingID	=-1;
	Layer		=-1;
}

bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,NamingID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,NamingID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAddAreaManual	Da(GetLayersBase());
		Da.ItemName				=ItemName;
		Da.NamingDLLRoot		=NamingDLLRoot;
		Da.NamingDLLName		=NamingDLLName;
		Da.NamingID				=NamingID;
		Da.Layer				=Layer;
		Da.Area			=Area;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//--------------------------------------------------------------------------------------

GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=0;
	Layer	=0;
}
bool	GUICmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
	
bool	GUICmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemInfo	*SendBack=GetSendBack(GUICmdSendItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqItemInfo	Da(GetLayersBase());
		Da.ItemID	=ItemID;
		Da.Layer	=Layer;
		PPage->TransmitDirectly(&Da);
		SendBack->ItemID			=Da.ItemID;
		SendBack->Layer				=Da.Layer;
		SendBack->ItemName			=Da.ItemName;

		SendBack->NamingDLLRoot		=Da.NamingDLLRoot;
		SendBack->NamingDLLName		=Da.NamingDLLName;
		SendBack->NamingID			=Da.NamingID;

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
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,NamingID)==false)
		return false;

	return true;
}
bool	GUICmdSendItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,NamingID)==false)
		return false;

	return true;
}

GUICmdSetItemInfo::GUICmdSetItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID		=-1;
	Layer		=-1;
	NamingID	=-1;
}
bool	GUICmdSetItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,NamingID)==false)
		return false;
	return true;
}
bool	GUICmdSetItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,NamingID)==false)
		return false;
	return true;
}

void	GUICmdSetItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdUpdateManual	Da(GetLayersBase());
		Da.ItemID		=ItemID;
		Da.Layer		=Layer;
		Da.ItemName		=ItemName;
		Da.NamingDLLRoot=NamingDLLRoot;
		Da.NamingDLLName=NamingDLLName;
		Da.NamingID		=NamingID;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}
//--------------------------------------------------------------------------------------

	
bool	NamingInfoList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	return true;
}
	
bool	NamingInfoList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	return true;
}

GUICmdReqNamingList::GUICmdReqNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdReqNamingList::Load(QIODevice *f)
{
	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
	
bool	GUICmdReqNamingList::Save(QIODevice *f)
{
	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

static	void ItemFuncNaming(AlgorithmItemRoot *Item ,void *_Something)
{
	NamingInfoListContainer		*NamingContainer=(NamingInfoListContainer *)_Something;
	NamingInfoList	*r=new NamingInfoList();
	r->ItemID	=Item->GetID();
	r->ItemName	=Item->GetItemName();
	Item->GetArea().GetXY(r->x1,r->y1,r->x2,r->y2);
	NamingContainer->AppendList(r);
}

void	GUICmdReqNamingList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingList	*SendBack=GetSendBack(GUICmdSendNamingList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(NamingDLLRoot ,NamingDLLName);
	if(NamingBase!=NULL){
		NamingBase->GetPageData(localPage)->LoopforAllItems(ItemFuncNaming,&SendBack->NamingContainer);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNamingList::GUICmdSendNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

	
bool	GUICmdSendNamingList::Load(QIODevice *f)
{
	if(NamingContainer.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendNamingList::Save(QIODevice *f)
{
	if(NamingContainer.Save(f)==false)
		return false;
	return true;
}

//--------------------------------------------------------------------------------------

GUICmdReqSource::GUICmdReqSource(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer	=-1;
	ItemID	=-1;
}

bool	GUICmdReqSource::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
	
bool	GUICmdReqSource::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqSource::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSource	*SendBack=GetSendBack(GUICmdSendSource,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqSource	Cmd(GetLayersBase());
		Cmd.Layer	=Layer;
		Cmd.ItemID	=ItemID;
		Cmd.Sources	=&SendBack->Sources;
		PPage->TransmitDirectly(&Cmd);		
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSource::GUICmdSendSource(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage),Sources(Base)
{
}


bool	GUICmdSendSource::Load(QIODevice *f)
{
	if(Sources.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdSendSource::Save(QIODevice *f)
{
	if(Sources.Save(f)==false)
		return false;
	return true;
}

//--------------------------------------------------------------------------------------

GUICmdReqSourceItemInfo::GUICmdReqSourceItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=-1;
}

bool	GUICmdReqSourceItemInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(IDList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqSourceItemInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(IDList.Save(f)==false)
		return false;
	return true;
}

struct	ReqItemInfoStruct
{
	int		Page;
	int		Layer;
	IntList					*IDList;
	ItemInfoContainer		*ItemInfos;
};

static	void ReqItemInfoItemFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	ReqItemInfoStruct	*s=(struct	ReqItemInfoStruct *)_Something;
	if(Item->GetPage()==s->Page && Item->GetLayer()==s->Layer && s->IDList->IsInclude(Item->GetID())==true){
		ItemInfoList	*t=new ItemInfoList();
		t->ItemID	=Item->GetID();
		t->ItemName	=Item->GetItemName();
		Item->GetCenter(t->Cx,t->Cy);
		t->x1	=Item->GetArea().GetMinX();
		t->y1	=Item->GetArea().GetMinY();
		t->x2	=Item->GetArea().GetMaxX();
		t->y2	=Item->GetArea().GetMaxY();
		s->ItemInfos->AppendList(t);
	}
}

void	GUICmdReqSourceItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSourceItemInfo	*SendBack=GetSendBack(GUICmdSendSourceItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	struct	ReqItemInfoStruct	s;
	s.Page	=localPage;
	s.Layer=Layer;
	s.IDList	=&IDList;
	s.ItemInfos=&SendBack->ItemInfos;
	PPage->LoopforAllItems(ReqItemInfoItemFunc,&s);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSourceItemInfo::GUICmdSendSourceItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSourceItemInfo::Load(QIODevice *f)
{
	if(ItemInfos.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendSourceItemInfo::Save(QIODevice *f)
{
	if(ItemInfos.Save(f)==false)
		return false;
	return true;
}

//--------------------------------------------------------------------------------------

GUICmdModifySourceItems::GUICmdModifySourceItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,Sources(Base)
{
	Layer=-1;
}

bool	GUICmdModifySourceItems::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(Sources.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdModifySourceItems::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(Sources.Save(f)==false)
		return false;
	return true;
}
void	GUICmdModifySourceItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SkipMark");
	if(PBase==NULL)
		return;
	SkipMarkInPage	*PPage=dynamic_cast<SkipMarkInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdModifySource	Cmd(GetLayersBase());
		Cmd.Layer	=Layer;
		Cmd.ItemID	=ItemID;
		Cmd.Sources	=&Sources;
		PPage->TransmitDirectly(&Cmd);		
	}
	SendAck(localPage);
}


//--------------------------------------------------------------------------------------

GUICmdReqSourceAllItemsInfo::GUICmdReqSourceAllItemsInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=-1;
}

bool	GUICmdReqSourceAllItemsInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	return true;
}

bool	GUICmdReqSourceAllItemsInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;

	return true;
}

struct	ReqAllItemsInfoStruct
{
	int		Page;
	int		Layer;
	ItemInfoContainer		*ItemInfos;
};

static	void ReqAllItemsInfoItemFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	ReqAllItemsInfoStruct	*s=(struct	ReqAllItemsInfoStruct *)_Something;
	if(Item->GetPage()==s->Page && Item->GetLayer()==s->Layer){
		ItemInfoList	*t=new ItemInfoList();
		t->ItemID	=Item->GetID();
		t->LibID	=Item->GetLibID();
		t->ItemName	=Item->GetItemName();
		Item->GetCenter(t->Cx,t->Cy);
		t->x1	=Item->GetArea().GetMinX();
		t->y1	=Item->GetArea().GetMinY();
		t->x2	=Item->GetArea().GetMaxX();
		t->y2	=Item->GetArea().GetMaxY();
		s->ItemInfos->AppendList(t);
	}
}

void	GUICmdReqSourceAllItemsInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSourceAllItemsInfo	*SendBack=GetSendBack(GUICmdSendSourceAllItemsInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	struct	ReqAllItemsInfoStruct	s;
	s.Page	=localPage;
	s.Layer	=Layer;
	s.ItemInfos=&SendBack->ItemInfos;
	PPage->LoopforAllItems(ReqAllItemsInfoItemFunc,&s);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSourceAllItemsInfo::GUICmdSendSourceAllItemsInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSourceAllItemsInfo::Load(QIODevice *f)
{
	if(ItemInfos.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendSourceAllItemsInfo::Save(QIODevice *f)
{
	if(ItemInfos.Save(f)==false)
		return false;
	return true;
}
