#include "PropertyResultBinderForm.h"
#include"XPropertyResultBinderPacket.h"
#include "XDisplayImagePacket.h"
#include "XResultBinder.h"

GUICmdAddAreaManual::GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultBinderItemID	=-1;
	RuleType			=0;

	Phase	=0;
	Page	=0;
	Layer	=0;
	Conclusion=false;
	NGOthers=false;
	Conclusion=false;
}

bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(::Load(f,ResultBinderItemID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;

	if(::Load(f,RuleType)==false)
		return false;

	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(ConditionData.Load(f)==false)
		return false;
	if(::Load(f,RuleName)==false)
		return false;
	if(::Load(f,RuleRemark)==false)
		return false;
	if(::Load(f,NGOthers)==false)
		return false;
	if(::Load(f,Conclusion)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(::Save(f,ResultBinderItemID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,RuleType)==false)
		return false;

	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(ConditionData.Save(f)==false)
		return false;
	if(::Save(f,RuleName)==false)
		return false;
	if(::Save(f,RuleRemark)==false)
		return false;
	if(::Save(f,NGOthers)==false)
		return false;
	if(::Save(f,Conclusion)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		AddRulePacket	Da(GetLayersBase());
		Da.ResultBinderItemID	=ResultBinderItemID;
		Da.Area			=Area;
		Da.RuleType		=RuleType;

		Da.AlgoRoot		=AlgoRoot;
		Da.AlgoName		=AlgoName;
		Da.Phase		=Phase;
		Da.Page			=Page;
		Da.Layer		=Layer;
		Da.ItemID		=ItemID;
		Da.ItemName		=ItemName;
		Da.ConditionData=ConditionData;
		Da.RuleName		=RuleName;
		Da.RuleRemark	=RuleRemark;
		Da.NGOthers		=NGOthers;
		Da.Conclusion	=Conclusion;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//=========================================================================================================

GUICmdChangeAreaManual::GUICmdChangeAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultBinderItemID	=-1;
	RuleType			=0;

	Phase	=0;
	Page	=0;
	Layer	=0;
	Conclusion	=false;
	RuleID		=-1;
	NGOthers	=false;
	DeleteMode	=false;
}

bool	GUICmdChangeAreaManual::Load(QIODevice *f)
{
	if(::Load(f,ResultBinderItemID)==false)
		return false;
	if(::Load(f,RuleType)==false)
		return false;

	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(ConditionData.Load(f)==false)
		return false;
	if(::Load(f,RuleName)==false)
		return false;
	if(::Load(f,RuleRemark)==false)
		return false;
	if(::Load(f,RuleID)==false)
		return false;
	if(::Load(f,NGOthers)==false)
		return false;
	if(::Load(f,Conclusion)==false)
		return false;
	if(::Load(f,DeleteMode)==false)
		return false;
	return true;
}
bool	GUICmdChangeAreaManual::Save(QIODevice *f)
{
	if(::Save(f,ResultBinderItemID)==false)
		return false;
	if(::Save(f,RuleType)==false)
		return false;

	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(ConditionData.Save(f)==false)
		return false;
	if(::Save(f,RuleName)==false)
		return false;
	if(::Save(f,RuleRemark)==false)
		return false;
	if(::Save(f,RuleID)==false)
		return false;
	if(::Save(f,NGOthers)==false)
		return false;
	if(::Save(f,Conclusion)==false)
		return false;
	if(::Save(f,DeleteMode)==false)
		return false;
	return true;
}

void	GUICmdChangeAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdChangeRulePacket	Da(GetLayersBase());
		Da.ResultBinderItemID	=ResultBinderItemID;
		Da.RuleType		=RuleType;

		Da.AlgoRoot		=AlgoRoot;
		Da.AlgoName		=AlgoName;
		Da.Phase		=Phase;
		Da.Page			=Page;
		Da.Layer		=Layer;
		Da.ItemID		=ItemID;
		Da.ItemName		=ItemName;
		Da.ConditionData=ConditionData;
		Da.RuleName		=RuleName;
		Da.RuleRemark	=RuleRemark;
		Da.RuleID		=RuleID;
		Da.NGOthers		=NGOthers;
		Da.Conclusion	=Conclusion;
		Da.DeleteMode	=DeleteMode;
		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//=========================================================================================================
GUICmdReqItemList::GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=0;
}

bool	GUICmdReqItemList::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqItemList::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

struct	SomethingOfReqItemList
{
	int					Layer;
	ItemIDNameContainer	*Data;
};

static	void ItemFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	SomethingOfReqItemList	*p=(struct	SomethingOfReqItemList *)_Something;
	if(Item->GetLayer()==p->Layer){
		ItemIDNameList	*a=new ItemIDNameList();
		a->ItemID	=Item->GetID();
		a->ItemName	=Item->GetItemName();
		p->Data->AppendList(a);
	}
}

void	GUICmdReqItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemList	*SendBack=GetSendBack(GUICmdAckItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(LibType);
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			struct	SomethingOfReqItemList	SData;
			SData.Layer=Layer;
			SData.Data	=&SendBack->Data;
			Ap->LoopforAllItems(ItemFunc,&SData);
		}
	}
	SendBack->Layer=Layer;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckItemList::GUICmdAckItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=0;
}

	
bool	GUICmdAckItemList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckItemList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(Data.Save(f)==false)
		return false;
	return true;
}

//=========================================================================================================
GUICmdReqResultBinderItemAdd::GUICmdReqResultBinderItemAdd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqResultBinderItemAdd::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	return true;
}
bool	GUICmdReqResultBinderItemAdd::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	return true;
}

void	GUICmdReqResultBinderItemAdd::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultBinderItemAdd	*SendBack=GetSendBack(GUICmdAckResultBinderItemAdd,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqResultBinderItemAdd	Cmd(GetLayersBase());
		Cmd.ResultBinderItemName	=ItemName;
		PPage->TransmitDirectly(&Cmd);
		SendBack->ItemID=Cmd.ResultBinderItemID;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckResultBinderItemAdd::GUICmdAckResultBinderItemAdd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}
bool	GUICmdAckResultBinderItemAdd::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdAckResultBinderItemAdd::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

//=========================================================================================================

GUICmdReqResultBinderItemInfo::GUICmdReqResultBinderItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}
bool	GUICmdReqResultBinderItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqResultBinderItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqResultBinderItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendResultBinderItemInfo	*SendBack=GetSendBack(GUICmdSendResultBinderItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqResultBinderItemInfo	Cmd(GetLayersBase());
		Cmd.ItemID	=ItemID;
		PPage->TransmitDirectly(&Cmd);
		SendBack->ItemName=Cmd.ItemName;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendResultBinderItemInfo::GUICmdSendResultBinderItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendResultBinderItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdSendResultBinderItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

//=========================================================================================================
GUICmdReqResultBinderItemMod::GUICmdReqResultBinderItemMod(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqResultBinderItemMod::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdReqResultBinderItemMod::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdReqResultBinderItemMod::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqResultBinderItemMod	Cmd(GetLayersBase());
		Cmd.ItemID		=ItemID;
		Cmd.ItemName	=ItemName;
		PPage->TransmitDirectly(&Cmd);
	}
}
//=========================================================================================================
GUICmdReqResultBinderItemEnum::GUICmdReqResultBinderItemEnum(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
void	GUICmdReqResultBinderItemEnum::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultBinderItemEnum	*SendBack=GetSendBack(GUICmdAckResultBinderItemEnum,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqResultBinderItemEnum	Cmd(GetLayersBase());
		Cmd.Items	=&SendBack->Items;
		PPage->TransmitDirectly(&Cmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckResultBinderItemEnum::GUICmdAckResultBinderItemEnum(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckResultBinderItemEnum::Load(QIODevice *f)
{
	if(Items.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckResultBinderItemEnum::Save(QIODevice *f)
{
	if(Items.Save(f)==false)
		return false;
	return true;
}

//=========================================================================================================
GUICmdReqResultBinderItemDel::GUICmdReqResultBinderItemDel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}
	
bool	GUICmdReqResultBinderItemDel::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdReqResultBinderItemDel::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

void	GUICmdReqResultBinderItemDel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqResultBinderItemDel	Cmd(GetLayersBase());
		Cmd.ResultBinderItemID	=ItemID;
		PPage->TransmitDirectly(&Cmd);
	}

}


//=========================================================================================================

GUICmdReqRuleOnXY::GUICmdReqRuleOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ZoomRate	=1;
	PosX=PosY=0;
	ResultBinderItemID=-1;
}

bool	GUICmdReqRuleOnXY::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,PosX)==false)
		return false;
	if(::Load(f,PosY)==false)
		return false;
	if(::Load(f,ResultBinderItemID)==false)
		return false;

	return true;
}
bool	GUICmdReqRuleOnXY::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,PosX)==false)
		return false;
	if(::Save(f,PosY)==false)
		return false;
	if(::Save(f,ResultBinderItemID)==false)
		return false;

	return true;
}

void	GUICmdReqRuleOnXY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRuleOnXY	*SendBack=GetSendBack(GUICmdAckRuleOnXY,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqRuleOnXY	Cmd(GetLayersBase());
		Cmd.ZoomRate=ZoomRate;
		Cmd.PosX=PosX;
		Cmd.PosY=PosY;
		Cmd.ResultBinderItemID=ResultBinderItemID;
		PPage->TransmitDirectly(&Cmd);

		SendBack->RuleType	=Cmd.RuleType;
		SendBack->AlgoRoot	=Cmd.AlgoRoot;
		SendBack->AlgoName	=Cmd.AlgoName;
		SendBack->Phase		=Cmd.Phase;
		SendBack->Page		=Cmd.Page;
		SendBack->Layer		=Cmd.Layer;
		SendBack->ItemID	=Cmd.ItemID;
		SendBack->ConditionData	=Cmd.ConditionData;
		SendBack->ItemName	=Cmd.ItemName;
		SendBack->RuleName	=Cmd.RuleName;
		SendBack->RuleRemark=Cmd.RuleRemark;
		SendBack->Conclusion=Cmd.Conclusion;
		SendBack->RuleID	=Cmd.RuleID;
		SendBack->NGOthers	=Cmd.NGOthers;
		SendBack->InputNumb	=Cmd.InputNumb;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRuleOnXY::GUICmdAckRuleOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultBinderItemID	=-1;
	RuleType			=0;

	Phase	=0;
	Page	=0;
	Layer	=0;
	ItemID	=-1;
	Conclusion=false;
	RuleID	=-1;
	NGOthers=false;
}
	
bool	GUICmdAckRuleOnXY::Load(QIODevice *f)
{
	if(::Load(f,ResultBinderItemID)==false)
		return false;
	if(::Load(f,RuleType)==false)
		return false;

	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(ConditionData.Load(f)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,RuleName)==false)
		return false;
	if(::Load(f,RuleRemark)==false)
		return false;
	if(::Load(f,Conclusion)==false)
		return false;
	if(::Load(f,RuleID)==false)
		return false;
	if(::Load(f,NGOthers)==false)
		return false;
	return true;
}

bool	GUICmdAckRuleOnXY::Save(QIODevice *f)
{
	if(::Save(f,ResultBinderItemID)==false)
		return false;
	if(::Save(f,RuleType)==false)
		return false;

	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(ConditionData.Save(f)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,RuleName)==false)
		return false;
	if(::Save(f,RuleRemark)==false)
		return false;
	if(::Save(f,Conclusion)==false)
		return false;
	if(::Save(f,RuleID)==false)
		return false;
	if(::Save(f,NGOthers)==false)
		return false;
	return true;
}


//=========================================================================================================

GUICmdReqAddConnection::GUICmdReqAddConnection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ParentRuleID	=-1;
	ChildRuleID		=-1;
	ResultBinderItemID=-1;
}

bool	GUICmdReqAddConnection::Load(QIODevice *f)
{
	if(::Load(f,ParentRuleID)==false)
		return false;
	if(::Load(f,ChildRuleID)==false)
		return false;
	if(::Load(f,ResultBinderItemID)==false)
		return false;
	return true;
}

bool	GUICmdReqAddConnection::Save(QIODevice *f)
{
	if(::Save(f,ParentRuleID)==false)
		return false;
	if(::Save(f,ChildRuleID)==false)
		return false;
	if(::Save(f,ResultBinderItemID)==false)
		return false;
	return true;
}

void	GUICmdReqAddConnection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqAddConnection	Cmd(GetLayersBase());
		Cmd.ParentRuleID=ParentRuleID;
		Cmd.ChildRuleID	=ChildRuleID;
		Cmd.ResultBinderItemID=ResultBinderItemID;
		PPage->TransmitDirectly(&Cmd);
	}
}

//=========================================================================================================

GUICmdReqClosedConnectionOnXY::GUICmdReqClosedConnectionOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ZoomRate=1;
	PosX=PosY=0;
	ResultBinderItemID=-1;
}

bool	GUICmdReqClosedConnectionOnXY::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,PosX)==false)
		return false;
	if(::Load(f,PosY)==false)
		return false;
	if(::Load(f,ResultBinderItemID)==false)
		return false;

	return true;
}
bool	GUICmdReqClosedConnectionOnXY::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,PosX)==false)
		return false;
	if(::Save(f,PosY)==false)
		return false;
	if(::Save(f,ResultBinderItemID)==false)
		return false;

	return true;
}

void	GUICmdReqClosedConnectionOnXY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckClosedConnectionOnXY	*SendBack=GetSendBack(GUICmdAckClosedConnectionOnXY,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAckClosedConnectionOnXY	Cmd(GetLayersBase());
		Cmd.ZoomRate=ZoomRate;
		Cmd.PosX=PosX;
		Cmd.PosY=PosY;
		Cmd.ResultBinderItemID=ResultBinderItemID;
		PPage->TransmitDirectly(&Cmd);

		SendBack->ParentRuleID	=Cmd.ParentRuleID;
		SendBack->ChildRuleID	=Cmd.ChildRuleID;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckClosedConnectionOnXY::GUICmdAckClosedConnectionOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ParentRuleID	=-1;
	ChildRuleID		=-1;
}

bool	GUICmdAckClosedConnectionOnXY::Load(QIODevice *f)
{
	if(::Load(f,ParentRuleID)==false)
		return false;
	if(::Load(f,ChildRuleID)==false)
		return false;

	return true;
}
bool	GUICmdAckClosedConnectionOnXY::Save(QIODevice *f)
{
	if(::Save(f,ParentRuleID)==false)
		return false;
	if(::Save(f,ChildRuleID)==false)
		return false;

	return true;
}


//=========================================================================================================

GUICmdDelConnection::GUICmdDelConnection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ParentRuleID		=-1;
	ChildRuleID			=-1;
	ResultBinderItemID	=-1;
}

bool	GUICmdDelConnection::Load(QIODevice *f)
{
	if(::Load(f,ParentRuleID)==false)
		return false;
	if(::Load(f,ChildRuleID)==false)
		return false;
	if(::Load(f,ResultBinderItemID)==false)
		return false;

	return true;
}

bool	GUICmdDelConnection::Save(QIODevice *f)
{
	if(::Save(f,ParentRuleID)==false)
		return false;
	if(::Save(f,ChildRuleID)==false)
		return false;
	if(::Save(f,ResultBinderItemID)==false)
		return false;

	return true;
}
	
void	GUICmdDelConnection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultBinder");
	if(PBase==NULL)
		return;
	ResultBinderInPage	*PPage=dynamic_cast<ResultBinderInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDelConnection	Cmd(GetLayersBase());
		Cmd.ParentRuleID=ParentRuleID;
		Cmd.ChildRuleID=ChildRuleID;
		Cmd.ResultBinderItemID=ResultBinderItemID;
		PPage->TransmitDirectly(&Cmd);
	}
}
