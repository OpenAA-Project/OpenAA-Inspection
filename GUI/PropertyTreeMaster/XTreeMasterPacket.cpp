/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTreeMaster\XTreeMasterPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTreeMasterPacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>
#include "XTreeMaster.h"

//==========================================================================================
GUICmdAddTreeMaster::GUICmdAddTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddTreeMaster::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	return true;
}
bool	GUICmdAddTreeMaster::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	return true;
}

void	GUICmdAddTreeMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAddTreeMasterItemPacket	Cmd(GetLayersBase());
	Cmd.TMItemID	=TMItemID;
	Cmd.CatName		=CatName;
	Cmd.MasterCode	=MasterCode;
	Cmd.MasterName = MasterName;

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================
GUICmdSetAlertTreeMaster::GUICmdSetAlertTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	TMItemID	=0;
	MasterCode	=0;
	AlertMark	=false;
}

bool	GUICmdSetAlertTreeMaster::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,AlertMark)==false)
		return false;
	return true;
}

bool	GUICmdSetAlertTreeMaster::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,AlertMark)==false)
		return false;
	return true;
}

void	GUICmdSetAlertTreeMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSetAlertTreeMaster	Cmd(GetLayersBase());
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	Cmd.TMItemID	=TMItemID;
	Cmd.MasterCode	=MasterCode;
	Cmd.AlertMark	=AlertMark;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================
GUICmdReqMaxTMItemID::GUICmdReqMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMaxTMItemID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMaxTMItemID	*SendBack=GetSendBack(GUICmdAckMaxTMItemID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	CmdReqMaxTMItemIDPacket	Cmd(GetLayersBase());
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
	SendBack->TMItemID	=	Cmd.MaxTMItemID;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMaxTMItemID::GUICmdAckMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	TMItemID=0;
}

bool	GUICmdAckMaxTMItemID::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	return true;
}

bool	GUICmdAckMaxTMItemID::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	return true;
}

GUICmdCopyTreeMasterItem::GUICmdCopyTreeMasterItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdCopyTreeMasterItem::Load(QIODevice *f)
{
	if(::Load(f,MasterSrc)==false)
		return false;
	if(::Load(f,MasterDst)==false)
		return false;
	return true;
}

bool GUICmdCopyTreeMasterItem::Save(QIODevice *f)
{
	if(::Save(f,MasterSrc)==false)
		return false;
	if(::Save(f,MasterDst)==false)
		return false;
	return true;
}

void	GUICmdCopyTreeMasterItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdCopyTreeMasterItemPacket	Cmd(GetLayersBase());
	Cmd.MasterSrc = MasterSrc;
	Cmd.MasterDst = MasterDst;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(Base==NULL)
		return;
	Base->TransmitDirectly(&Cmd);
}

GUICmdSetCategoryName::GUICmdSetCategoryName(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdSetCategoryName::Load(QIODevice *f)
{
	if(::Load(f,CatName)==false)
		return false;
	return true;
}

bool GUICmdSetCategoryName::Save(QIODevice *f)
{
	if(::Save(f,CatName)==false)
		return false;
	return true;
}

void	GUICmdSetCategoryName::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSetCategoryNamePacket	Cmd(GetLayersBase());
	Cmd.CatName = CatName;
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

GUICmdRemoveItem::GUICmdRemoveItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdRemoveItem::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool GUICmdRemoveItem::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void GUICmdRemoveItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdRemoveItemPacket	Cmd(GetLayersBase());
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================

GUICmdSelectItem::GUICmdSelectItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdSelectItem::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool GUICmdSelectItem::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void GUICmdSelectItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSelectItemPacket	Cmd(GetLayersBase());
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================

bool	TreeMasterList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	if(::Load(f,AlertMask)==false)
		return false;
	return true;
}

bool	TreeMasterList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	if(::Save(f,AlertMask)==false)
		return false;
	return true;
}

TreeMasterList	&TreeMasterList::operator=(TreeMasterList &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

TreeMasterList	*TreeMasterListForPacketPack::FindByItemID(int TMItemID)
{
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID==TMItemID){
			return (c);
		}
	}
	return NULL;
}

TreeMasterList	*TreeMasterListForPacketPack::FindByMasterCode(int MasterCode)
{
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->MasterCode==MasterCode){
			return (c);
		}
	}
	return NULL;
}

void TreeMasterListForPacketPack::decreaseID(int BaseID){
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID>BaseID){
			c->ItemID--;
		}
	}
}

TreeMasterListForPacketPack	&TreeMasterListForPacketPack::operator+=(TreeMasterListForPacketPack &src)
{
	for(TreeMasterList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		TreeMasterList *d=new TreeMasterList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	TreeMasterListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		TreeMasterList *c=new TreeMasterList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	TreeMasterListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(TreeMasterList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

//===========================================================================

GUICmdAddTreeMasterArea::GUICmdAddTreeMasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddTreeMasterArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,TreeMasterColor)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	if(::Load(f,Selection)==false)
		return false;
	if(::Load(f,ThreShape)==false)
		return false;
	if(::Load(f,ThreColor)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;

	return true;
}
bool	GUICmdAddTreeMasterArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,TreeMasterColor)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	if(::Save(f,Selection)==false)
		return false;
	if(::Save(f,ThreShape)==false)
		return false;
	if(::Save(f,ThreColor)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;

	return true;
}

void	GUICmdAddTreeMasterArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CmdAddItemAreaPacket	Cmd(GetLayersBase());
	Cmd.TMItemID		=TMItemID;
	Cmd.Area			=Area;
	Cmd.MasterCode		=MasterCode;
	Cmd.TreeMasterColor	=TreeMasterColor;
	Cmd.CatName			=CatName;
	Cmd.MasterName		=MasterName;
	Cmd.Selection		=Selection;
	Cmd.ThreShape		=ThreShape;
	Cmd.ThreColor		=ThreColor;
	Cmd.SearchDot		=SearchDot;

	PData->TransmitDirectly(&Cmd);
}

//===========================================================================

GUICmdReqTreeMasterList::GUICmdReqTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqTreeMasterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTreeMasterList	*SendBack=GetSendBack(GUICmdSendTreeMasterList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeTreeMasterList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//===========================================================================
GUICmdSendTreeMasterList::GUICmdSendTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTreeMasterList::Load(QIODevice *f)
{
	if(TreeMasterInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendTreeMasterList::Save(QIODevice *f)
{
	if(TreeMasterInfo.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendTreeMasterList::MakeTreeMasterList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(ABase==NULL)
		return;
	TreeMasterInfo.RemoveAll();

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			TreeMasterItem	*MItem=dynamic_cast<TreeMasterItem *>(item);
			if(MItem!=NULL){
				TreeMasterList	*L=new TreeMasterList();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				int x1 ,y1 ,x2 ,y2;
				MItem->GetXY(x1 ,y1 ,x2 ,y2);
				L->x1=x1;
				L->y1=y1;
				L->x2=x2;
				L->y2=y2;
				L->CatName		= MItem->CatName;
				L->MasterCode	= MItem->MasterCode;
				L->ItemID			= MItem->TMItemID;
				L->MasterName	= MItem->MasterName;
				L->AlertMask	= MItem->AlertMark;

				TreeMasterInfo.AppendList(L);				
			}
		}
	}
}
void	GUICmdSendTreeMasterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{}

//========================================================================================

TreeMasterResultList	&TreeMasterResultList::operator=(TreeMasterResultList &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Save(&Buff)==false){
		return *this;
	}
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	TreeMasterResultList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,ResultE)==false)
		return false;
	return true;
}

bool	TreeMasterResultList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,ResultE)==false)
		return false;
	return true;
}

TreeMasterResultList	*TreeMasterResultListForPacketPack::FindByItemID(int TMItemID)
{
	for(TreeMasterResultList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ItemID==TMItemID){
			return (c);
		}
	}
	return NULL;
}

//========================================================================================

GUICmdReqLoadMasterImage::GUICmdReqLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLoadMasterImage::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool	GUICmdReqLoadMasterImage::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void	GUICmdReqLoadMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	QString	ImageFileName=Pg->GetImageFile(MasterCode, GetLayersBase()->GetMachineID());

	QFile	ImageFile(ImageFileName);
	ImageFile.open(QIODevice::ReadOnly);
	for(int LNumb=0;LNumb<GetLayerNumb(localPage);LNumb++){

		GetLayersBase()->StepProcessing(localPage);
		DataInLayer	*L=Pg->GetLayerData(LNumb);
		if(GetParamGlobal()->NoLoadSaveMasterImage==false){
			if(L->GetMasterBuff().Load(&ImageFile,false)==false){
				goto	QEnd;
			}
			L->GetMasterBuff().SetChanged(false);
			ImageBuffer	Dummy;
			if(Dummy.Load(&ImageFile)==false){
				goto	QEnd;
			}
			if(Dummy.Load(&ImageFile)==false){
				goto	QEnd;
			}
			GetParamGlobal()->IsLoadedMasterImageSuccessful=true;
		}
		else{
			GetParamGlobal()->IsLoadedMasterImageSuccessful=false;
		}
	}
	QEnd:;
}
