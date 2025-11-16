#include "EditStatisticBlockLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\XPropertyStatisticBlockPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyStatisticBlockPacket.h"
#include "XStatisticBlock.h"
#include "XGeneralFunc.h"
#include "XGUI.h"


GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibPoint=NULL;
	CreatedInside=false;
}
GUICmdPickupTestList::~GUICmdPickupTestList(void)
{
	if(CreatedInside==true)
		delete	LibPoint;
	LibPoint=NULL;
}


bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(LibPoint==NULL){
		CreatedInside=true;
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
		if(Ab!=NULL){
			CmdCreateTempStatisticBlockLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL)
		return false;
	if(LibPoint->LoadBlob(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibPoint==NULL)
		return false;
	if(LibPoint->SaveBlob(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestStatisticBlockPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}
GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdTestClear::Load(QIODevice *f){		return true;	}
bool	GUICmdTestClear::Save(QIODevice *f){		return true;	}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestStatisticBlockPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
}

//====================================================================================



//=====================================================================================
GUICmdGenerateStatisticBlocks::GUICmdGenerateStatisticBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateStatisticBlocks::~GUICmdGenerateStatisticBlocks(void)
{
}

bool	GUICmdGenerateStatisticBlocks::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateStatisticBlocks::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateStatisticBlocks::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateStatisticBlockPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdReqAreaHistgramInMaster::GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAreaHistgramInMaster::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqAreaHistgramInMaster::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAreaHistgramInMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaHistgramInMaster	*SendBack=GetSendBack(GUICmdSendAreaHistgramInMaster,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeLists(Area,LayerList,localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=====================================================================================
BrightnessMapList::BrightnessMapList(void)
{
	memset(BrightList,0,sizeof(BrightList));
}

bool	BrightnessMapList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(f->write((const char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
bool	BrightnessMapList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(f->read((char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
//=====================================================================================

GUICmdSendAreaHistgramInMaster::GUICmdSendAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaHistgramInMaster::MakeLists(FlexArea &area ,IntList &LayerList ,int localPage,LayersBase *Base)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		DataInLayer	*BLayer=Base->GetPageData(localPage)->GetLayerData(L->GetValue());
		BrightnessMapList	*BList=new BrightnessMapList();
		area.MakeBrightList(BList->BrightList,BLayer->GetDotPerLine(),BLayer->GetMaxLines(),BLayer->GetMasterBuff(),0 ,0);
		MapList.AppendList(BList);
	}
}
bool	GUICmdSendAreaHistgramInMaster::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	MapList.RemoveAll();
	for(int i=0;i<N;i++){
		BrightnessMapList *L=new BrightnessMapList();
		if(L->Load(f)==false)
			return false;
		MapList.AppendList(L);
	}
	return true;
}
bool	GUICmdSendAreaHistgramInMaster::Save(QIODevice *f)
{
	int32	N=MapList.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(BrightnessMapList *L=MapList.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendAreaHistgramInMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//=====================================================================================
GUICmdSendAddManualStatisticBlock::GUICmdSendAddManualStatisticBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualStatisticBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualStatisticBlock::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualStatisticBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	StatisticBlockBase *BBase=(StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		CmdAddByteStatisticBlockItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedStatisticBlock::GUICmdSendModifySelectedStatisticBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedStatisticBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedStatisticBlock::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedStatisticBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	StatisticBlockBase *BBase=(StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		CmdModifySelectedStatisticBlockFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedStatisticBlockItemAttr::GUICmdReqSelectedStatisticBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedStatisticBlockItemAttr::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectedStatisticBlockItemAttr::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqSelectedStatisticBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedStatisticBlockItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedStatisticBlockItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase(),LayerList);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedStatisticBlockItemAttr::GUICmdSendSelectedStatisticBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedStatisticBlockItemAttr::Make(int localPage ,LayersBase *Base ,IntList &LayerList)
{
	StatisticBlockBase *BBase=(StatisticBlockBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		StatisticBlockInPage	*PData=dynamic_cast<StatisticBlockInPage	*>(BBase->GetPageData(localPage));
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			StatisticBlockInLayer	*LData=dynamic_cast<StatisticBlockInLayer *>(PData->GetLayerData(L->GetValue()));
			if(LData!=NULL){
				CmdGetOneSelectedItem	Cmd(this);
				LData->TransmitDirectly(&Cmd);
				if(Cmd.ExistSelected==true){
					ExistSelected=true;
					BItem=Cmd.Buff;
					return;
				}
			}
		}
	}
}
bool	GUICmdSendSelectedStatisticBlockItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedStatisticBlockItemAttr::Save(QIODevice *f)
{
	if(::Save(f,ExistSelected)==false)
		return false;
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendSelectedStatisticBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqStatisticBlockInfoList::GUICmdReqStatisticBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqStatisticBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendStatisticBlockInfoList	*SendBack=GetSendBack(GUICmdSendStatisticBlockInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendStatisticBlockInfoList::GUICmdSendStatisticBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendStatisticBlockInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	StatisticBlockInfos.RemoveAll();
	for(int i=0;i<N;i++){
		StatisticBlockInfoList	*a=new StatisticBlockInfoList();
		if(a->Load(f)==false)
			return false;
		StatisticBlockInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendStatisticBlockInfoList::Save(QIODevice *f)
{
	int	N=StatisticBlockInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(StatisticBlockInfoList *a=StatisticBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendStatisticBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendStatisticBlockInfoList::Make(int localPage)
{
	StatisticBlockBase	*BBase=(StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		CmdStatisticBlockInfoListPacket	Cmd(this);
		Cmd.LocalPage=localPage;
		Cmd.StatisticBlockInfos=&StatisticBlockInfos;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=============================================================================================

GUICmdReqStatisticBlockFromList::GUICmdReqStatisticBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqStatisticBlockFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqStatisticBlockFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqStatisticBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckStatisticBlockFromList	*SendBack=GetSendBack(GUICmdAckStatisticBlockFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	StatisticBlockBase	*BBase=(StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetStatisticBlockFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->StatisticBlockInfoOnMouse[N]=Cmd.StatisticBlockInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckStatisticBlockFromList::GUICmdAckStatisticBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(StatisticBlockInfoOnMouse)/sizeof(StatisticBlockInfoOnMouse[0]);i++){
		StatisticBlockInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckStatisticBlockFromList::~GUICmdAckStatisticBlockFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(StatisticBlockInfoOnMouse)/sizeof(StatisticBlockInfoOnMouse[0]);i++){
			if(StatisticBlockInfoOnMouse[i]!=NULL){
				delete	StatisticBlockInfoOnMouse[i];
				StatisticBlockInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckStatisticBlockFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	StatisticBlockBase	*BBase=(StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	for(int i=0;i<N;i++){
		CmdCreateStatisticBlockItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		StatisticBlockInfoOnMouse[i]=Cmd.StatisticBlock;
		Created=true;
		if(StatisticBlockInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckStatisticBlockFromList::Save(QIODevice *f)
{
	int32	N=sizeof(StatisticBlockInfoOnMouse)/sizeof(StatisticBlockInfoOnMouse[0]);
	for(int i=0;i<sizeof(StatisticBlockInfoOnMouse)/sizeof(StatisticBlockInfoOnMouse[0]);i++){
		if(StatisticBlockInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(StatisticBlockInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckStatisticBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
