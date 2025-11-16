//#include "CreateManualColorDifferenceFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorDifference\XPropertyColorDifferencePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyColorDifferencePacket.h"
#include "XColorDifference.h"
#include "XGeneralFunc.h"
//#include "XGUI.h"
#include "XColorDifferenceLibrary.h"

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
GUICmdSendAddManualColorDifference::GUICmdSendAddManualColorDifference(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualColorDifference::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualColorDifference::Save(QIODevice *f)
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
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualColorDifference::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ColorDifferenceBase *BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*PData=dynamic_cast<ColorDifferenceInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddByteColorDifferenceItemPacket	Cmd(this);
			Cmd.Buff		=BItem;
			Cmd.Area		=Area;
			Cmd.LayerList	=LayerList;
			Cmd.LibID		=LibID;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedColorDifference::GUICmdSendModifySelectedColorDifference(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedColorDifference::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedColorDifference::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedColorDifference::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorDifferenceBase *BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		CmdModifySelectedColorDifferenceFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedColorDifferenceItemAttr::GUICmdReqSelectedColorDifferenceItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedColorDifferenceItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedColorDifferenceItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedColorDifferenceItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedColorDifferenceItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedColorDifferenceItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedColorDifferenceItemAttr::GUICmdSendSelectedColorDifferenceItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedColorDifferenceItemAttr::Make(int localPage ,LayersBase *Base)
{
	ColorDifferenceBase *BBase=(ColorDifferenceBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*PData=dynamic_cast<ColorDifferenceInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdGetOneSelectedItem	Cmd(this);
			PData->TransmitDirectly(&Cmd);
			if(Cmd.ExistSelected==true){
				ExistSelected=true;
				BItem=Cmd.Buff;
				return;
			}
		}
	}
}
bool	GUICmdSendSelectedColorDifferenceItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedColorDifferenceItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedColorDifferenceItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqColorDifferenceInfoList::GUICmdReqColorDifferenceInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqColorDifferenceInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendColorDifferenceInfoList	*SendBack=GetSendBack(GUICmdSendColorDifferenceInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendColorDifferenceInfoList::GUICmdSendColorDifferenceInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendColorDifferenceInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	ColorDifferenceInfos.RemoveAll();
	for(int i=0;i<N;i++){
		ColorDifferenceInfoList	*a=new ColorDifferenceInfoList();
		if(a->Load(f)==false)
			return false;
		ColorDifferenceInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendColorDifferenceInfoList::Save(QIODevice *f)
{
	int	N=ColorDifferenceInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ColorDifferenceInfoList	*a=ColorDifferenceInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendColorDifferenceInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendColorDifferenceInfoList::Make(int localPage)
{
}

//=============================================================================================

GUICmdReqColorDifferenceFromList::GUICmdReqColorDifferenceFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqColorDifferenceFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqColorDifferenceFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqColorDifferenceFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorDifferenceFromList	*SendBack=GetSendBack(GUICmdAckColorDifferenceFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetColorDifferenceFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->ColorDifferenceInfoOnMouse[N]=Cmd.ColorDifferenceInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorDifferenceFromList::GUICmdAckColorDifferenceFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(ColorDifferenceInfoOnMouse)/sizeof(ColorDifferenceInfoOnMouse[0]);i++){
		ColorDifferenceInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckColorDifferenceFromList::~GUICmdAckColorDifferenceFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(ColorDifferenceInfoOnMouse)/sizeof(ColorDifferenceInfoOnMouse[0]);i++){
			if(ColorDifferenceInfoOnMouse[i]!=NULL){
				delete	ColorDifferenceInfoOnMouse[i];
				ColorDifferenceInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckColorDifferenceFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	for(int i=0;i<N;i++){
		CmdCreateColorDifferenceItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		ColorDifferenceInfoOnMouse[i]=Cmd.ColorDifference;
		Created=true;
		if(ColorDifferenceInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckColorDifferenceFromList::Save(QIODevice *f)
{
	int32	N=sizeof(ColorDifferenceInfoOnMouse)/sizeof(ColorDifferenceInfoOnMouse[0]);
	for(int i=0;i<sizeof(ColorDifferenceInfoOnMouse)/sizeof(ColorDifferenceInfoOnMouse[0]);i++){
		if(ColorDifferenceInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(ColorDifferenceInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckColorDifferenceFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=============================================================================================
/*
GUICmdReqSetButtonMode::GUICmdReqSetButtonMode(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSetButtonMode::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Mode=(ButtonMode)d;
	if(::Load(f,InstForm)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSetButtonMode::Save(QIODevice *f)
{
	BYTE	d=(BYTE)Mode;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,InstForm)==false){
		return false;
	}
	return true;
}
void	GUICmdReqSetButtonMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstForm);
	if(L!=NULL){
		CmdReqSetButtonMode	Cmd(this);
		Cmd.Mode=Mode;
		L->TransmitDirectly(&Cmd);
	}
}
*/
//=============================================================================================
GUICmdReqItemListForPageContainer::GUICmdReqItemListForPageContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemListForPageContainer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemListForPageContainer	*SendBack=GetSendBack(GUICmdAckItemListForPageContainer,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdItemListForPageContainer	Cmd(GetLayersBase());
			Cmd.Container=&SendBack->ItemListForPageData;
			BPage->TransmitDirectly(&Cmd);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckItemListForPageContainer::GUICmdAckItemListForPageContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemListForPageContainer::Load(QIODevice *f)
{
	if(ItemListForPageData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckItemListForPageContainer::Save(QIODevice *f)
{
	if(ItemListForPageData.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================
GUICmdAddColorDifferenceOK::GUICmdAddColorDifferenceOK(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAddColorDifferenceOK::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdAddColorDifferenceOK	Cmd(GetLayersBase());
			BPage->TransmitDirectly(&Cmd);
		}
	}
}
//=============================================================================================
GUICmdAddColorDifferenceNG::GUICmdAddColorDifferenceNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdAddColorDifferenceNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdAddColorDifferenceNG	Cmd(GetLayersBase());
			BPage->TransmitDirectly(&Cmd);
		}
	}
}


//===================================================================================================
GUICmdRegistInFlowON::GUICmdRegistInFlowON(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdRegistInFlowON::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)ABase->GetPageData(localPage);
		if(BPage!=NULL){
			BPage->RegistInFlowMode=true;
		}
	}
}
//===================================================================================================
GUICmdRegistInFlowOFF::GUICmdRegistInFlowOFF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdRegistInFlowOFF::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)ABase->GetPageData(localPage);
		if(BPage!=NULL){
			BPage->RegistInFlowMode=false;
		}
	}
}
//===================================================================================================
GUICmdSetStatisticThreshold::GUICmdSetStatisticThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetStatisticThreshold::Load(QIODevice *f)
{
	if(::Load(f,SigmaH)==false)
		return false;
	if(::Load(f,SigmaS)==false)
		return false;
	if(::Load(f,SigmaV)==false)
		return false;
	return true;
}
bool	GUICmdSetStatisticThreshold::Save(QIODevice *f)
{
	if(::Save(f,SigmaH)==false)
		return false;
	if(::Save(f,SigmaS)==false)
		return false;
	if(::Save(f,SigmaV)==false)
		return false;
	return true;
}

void	GUICmdSetStatisticThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)ABase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdSetStatisticThreshold	Cmd(GetLayersBase());
			Cmd.SigmaH	=SigmaH;
			Cmd.SigmaS	=SigmaS;
			Cmd.SigmaV	=SigmaV;
			BPage->TransmitDirectly(&Cmd);
		}
	}
}
//===================================================================================================
GUICmdClearFlowStack::GUICmdClearFlowStack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdClearFlowStack::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(ABase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)ABase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdClearFlowStack	Cmd(GetLayersBase());
			BPage->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================

GUICmdReqFlowData::GUICmdReqFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqFlowData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFlowData	*SendBack=GetSendBack(GUICmdAckFlowData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdReqFlowData	Cmd(GetLayersBase());
			BPage->TransmitDirectly(&Cmd);
			SendBack->Data=Cmd.Data;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckFlowData::GUICmdAckFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckFlowData::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdAckFlowData::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}

GUICmdSendFlowData::GUICmdSendFlowData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendFlowData::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSendFlowData::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}
void	GUICmdSendFlowData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdSendFlowData	Cmd(GetLayersBase());
			Cmd.Data=Data;
			BPage->TransmitDirectly(&Cmd);
		}
	}
}

//=============================================================================================

GUICmdAutoGenerate::GUICmdAutoGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAutoGenerate::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAutoGenerate::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)	return false;
	return true;
}

void	GUICmdAutoGenerate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorDifferenceBase	*BBase=(ColorDifferenceBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		ColorDifferenceInPage	*BPage=(ColorDifferenceInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdAutoGenerate	Cmd(GetLayersBase());
			Cmd.SelectedLibList=SelectedLibList;
			BPage->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
