/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDent\XPropertyDentPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyDentPacket.h"
#include "XDentInspection.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XPropertyDentCommon.h"

GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibID=-1;
}
GUICmdPickupTestList::~GUICmdPickupTestList(void)
{
}


bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;

	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;

	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestDentPacket	PTestPacket(this);
	PTestPacket.LibID	=LibID;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
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
	CmdClearTestDentPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}
//=====================================================================================
GUICmdGenerateDents::GUICmdGenerateDents(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateDents::~GUICmdGenerateDents(void)
{
}

bool	GUICmdGenerateDents::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdGenerateDents::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;

	return true;
}

void	GUICmdGenerateDents::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateDentPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}

//====================================================================================
void	DentDrawAttr::Initial(void)
{
	CmdDentDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDent" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
}

//=====================================================================================

GUICmdReqAreaHistgramInMaster::GUICmdReqAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAreaHistgramInMaster::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqAreaHistgramInMaster::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
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
	if(f->write((const char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
bool	BrightnessMapList::Load(QIODevice *f)
{
	if(f->read((char *)BrightList,sizeof(BrightList))!=sizeof(BrightList))
		return false;
	return true;
}
//=====================================================================================

GUICmdSendAreaHistgramInMaster::GUICmdSendAreaHistgramInMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaHistgramInMaster::MakeLists(FlexArea &area ,IntList &LayerList,int localPage,LayersBase *Base)
{
	DataInPage	*P=Base->GetPageData(localPage);
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		DataInLayer	*BLayer=P->GetLayerData(L->GetValue());
		BrightnessMapList	*BList=new BrightnessMapList();
		area.MakeBrightList(BList->BrightList,P->GetDotPerLine(),P->GetMaxLines(),BLayer->GetMasterBuff(),0 ,0);
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
GUICmdSendAddManualDent::GUICmdSendAddManualDent(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualDent::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;

	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;

	return true;
}
bool	GUICmdSendAddManualDent::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;

	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualDent::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DentBase *BBase=(DentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(BBase!=NULL){
		CmdAddDentItemPacket	Cmd(this);
		Cmd.Area		=Area;
		Cmd.Layer		=Layer;
		Cmd.ItemName	=ItemName;
		Cmd.LibID		=LibID;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdReqDentInfoList::GUICmdReqDentInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDentInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDentInfoList	*SendBack=GetSendBack(GUICmdSendDentInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DentBase *BBase=(DentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(BBase!=NULL){
		CmdDentInfoListPacket	Cmd(this);
		Cmd.DentInfos	=&SendBack->DentInfos;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDentInfoList::GUICmdSendDentInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDentInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	DentInfos.RemoveAll();
	for(int i=0;i<N;i++){
		DentInfoList	*a=new DentInfoList();
		if(a->Load(f)==false)
			return false;
		DentInfos.AppendList(a);
	}
	return false;
}
bool	GUICmdSendDentInfoList::Save(QIODevice *f)
{
	int	N=DentInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(DentInfoList	*a=DentInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendDentInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=============================================================================================
GUICmdDentGenerate::GUICmdDentGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDentGenerate::Load(QIODevice *f)
{
	if(ItemLibIDs.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdDentGenerate::Save(QIODevice *f)
{
	if(ItemLibIDs.Save(f)==false)
		return false;
	return true;
}

void	GUICmdDentGenerate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DentBase *BBase=(DentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DentInspection");
	if(BBase!=NULL){
		DentInPage	*PData=dynamic_cast<DentInPage *>(BBase->GetPageData(localPage));
		CmdDentGenerate	Cmd(GetLayersBase());
		Cmd.ItemLibIDs	=ItemLibIDs;
		PData->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
