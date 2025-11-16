#include "EditDynamicClassifyLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicClassify\XDynamicClassifyPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDynamicClassifyPacket.h"
#include "XDynamicClassify.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
		if(Ab!=NULL){
			CmdCreateTempDynamicClassifyLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL)
		return false;
	int32	LibID;
	if(::Load(f,LibID)==false)
		return false;
	LibPoint->SetLibID(LibID);
	if(LibPoint->Load(f)==false)
		return false;
	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibPoint==NULL)
		return false;
	int32	LibID=LibPoint->GetLibID();
	if(::Save(f,LibID)==false)
		return false;
	if(LibPoint->Save(f)==false)
		return false;
	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestDynamicClassifyPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdTestClear::Load(QIODevice *f){		return true;	}
bool	GUICmdTestClear::Save(QIODevice *f){		return true;	}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestDynamicClassifyPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
}

//====================================================================================

GUICmdGenerateDynamicClassifys::GUICmdGenerateDynamicClassifys(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateDynamicClassifys::~GUICmdGenerateDynamicClassifys(void)
{
}

bool	GUICmdGenerateDynamicClassifys::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateDynamicClassifys::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateDynamicClassifys::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateDynamicClassifyPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdReqRGBStockFromArea::GUICmdReqRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqRGBStockFromArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqRGBStockFromArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqRGBStockFromArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ImagePointerContainer Images;
	GetLayersBase()->GetPageData(localPage)->GetMasterImages(Images);
	GUICmdSendRGBStockFromArea	*SendBack=GetSendBack(GUICmdSendRGBStockFromArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	Area.CreateRGBStock(Images, SendBack->RGBColors);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendRGBStockFromArea::GUICmdSendRGBStockFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendRGBStockFromArea::Load(QIODevice *f)
{
	if(RGBColors.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendRGBStockFromArea::Save(QIODevice *f)
{
	if(RGBColors.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendRGBStockFromArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
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
	return true;
}

bool	GUICmdReqAreaHistgramInMaster::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAreaHistgramInMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaHistgramInMaster	*SendBack=GetSendBack(GUICmdSendAreaHistgramInMaster,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeLists(Area,localPage,GetLayersBase());
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
void	GUICmdSendAreaHistgramInMaster::MakeLists(FlexArea &area ,int localPage,LayersBase *Base)
{
	DataInLayer	*BLayer=Base->GetPageData(localPage)->GetLayerData(0);
	BrightnessMapList	*BList=new BrightnessMapList();
	area.MakeBrightList(BList->BrightList,BLayer->GetDotPerLine(),BLayer->GetMaxLines(),BLayer->GetMasterBuff(),0 ,0);
	MapList.AppendList(BList);
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
/*
//=============================================================================================================
bool	CmdSetDynamicClassifyShowingState::Load(QIODevice *f)
{
	if(::Load(f,ModeCoreArea)==false)
		return false;
	if(::Load(f,ModeMaxZone)==false)
		return false;
	if(::Load(f,ModeBareArea)==false)
		return false;
	if(::Load(f,ModeInsideArea)==false)
		return false;
	if(::Load(f,ModeOutlineIArea)==false)
		return false;
	if(::Load(f,ModeOutlineTArea)==false)
		return false;
	if(::Load(f,ModeOutlineOArea)==false)
		return false;
	return true;
}

bool	CmdSetDynamicClassifyShowingState::Save(QIODevice *f)
{
	if(::Save(f,ModeCoreArea)==false)
		return false;
	if(::Save(f,ModeMaxZone)==false)
		return false;
	if(::Save(f,ModeBareArea)==false)
		return false;
	if(::Save(f,ModeInsideArea)==false)
		return false;
	if(::Save(f,ModeOutlineIArea)==false)
		return false;
	if(::Save(f,ModeOutlineTArea)==false)
		return false;
	if(::Save(f,ModeOutlineOArea)==false)
		return false;
	return true;
}

GUICmdSetDynamicClassifyShowingState::GUICmdSetDynamicClassifyShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetDynamicClassifyShowingState::Load(QIODevice *f)
{
	if(State.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetDynamicClassifyShowingState::Save(QIODevice *f)
{
	if(State.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetDynamicClassifyShowingState::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyDynamicClassify" ,"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&State);
	}
}
*/

//=============================================================================================================
GUICmdReqDynamicClassifyInfo::GUICmdReqDynamicClassifyInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDynamicClassifyInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDynamicClassifyInfo	*SendBack=GetSendBack(GUICmdSendDynamicClassifyInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDynamicClassifyInfo::GUICmdSendDynamicClassifyInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDynamicClassifyInfo::Load(QIODevice *f)
{
	if(DCInfoData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendDynamicClassifyInfo::Save(QIODevice *f)
{
	if(DCInfoData.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendDynamicClassifyInfo::MakeData(int localPage)
{
	AlgorithmBase		*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	CmdGetDynamicClassifyPacket	Cmd(this);
	Cmd.Point=&DCInfoData;
	PPage->TransmitDirectly(&Cmd);

	//DynamicClassifyBase *PBase=(DynamicClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	//if(PBase!=NULL){
	//	CmdGetDClassifyInfo	Cmd;
	//	PBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	//	DCInfoData=Cmd.DCInfoData;
	//}
}
