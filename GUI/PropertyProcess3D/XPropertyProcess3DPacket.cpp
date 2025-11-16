/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyProcess3D\XPropertyProcess3DPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyProcess3DPacket.h"
#include "XProcess3D.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XPropertyProcess3DCommon.h"


//====================================================================================

Process3DDrawAttr::Process3DDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
Process3DDrawAttr::Process3DDrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,int ptranparentLevel
							, QColor &blockColor0
							, QColor &blockColor1
							, QColor &blockColor2
							, QColor &blockColor3
							, QColor &blockColor4
							, QColor &blockColor5
							, QColor &blockColor6
							, QColor &blockColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel),ServiceForLayers(Base)
{
	Initial();

	BlockColor0	=blockColor0;
	BlockColor1	=blockColor1;
	BlockColor2	=blockColor2;
	BlockColor3	=blockColor3;
	BlockColor4	=blockColor4;
	BlockColor5	=blockColor5;
	BlockColor6	=blockColor6;
	BlockColor7	=blockColor7;

	BlockColor0.setAlpha(ptranparentLevel);
	BlockColor1.setAlpha(ptranparentLevel);
	BlockColor2.setAlpha(ptranparentLevel);
	BlockColor3.setAlpha(ptranparentLevel);
	BlockColor4.setAlpha(ptranparentLevel);
	BlockColor5.setAlpha(ptranparentLevel);
	BlockColor6.setAlpha(ptranparentLevel);
	BlockColor7.setAlpha(ptranparentLevel);
}
void	Process3DDrawAttr::Initial(void)
{
	CmdProcess3DDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProcess3D" ,/**/"");
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

GUICmdSendAreaHistgramInMaster::GUICmdSendAreaHistgramInMaster(LayersBase *Base  ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaHistgramInMaster::MakeLists(FlexArea &area ,IntList &LayerList,int localPage,LayersBase *Base)
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
GUICmdSendAddManualProcess3D::GUICmdSendAddManualProcess3D(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualProcess3D::Load(QIODevice *f)
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
bool	GUICmdSendAddManualProcess3D::Save(QIODevice *f)
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

void	GUICmdSendAddManualProcess3D::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	Process3DBase *BBase=(Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	if(BBase!=NULL){
		CmdAddProcess3DItemPacket	Cmd(this);
		Cmd.Area		=Area;
		Cmd.Layer		=Layer;
		Cmd.ItemName	=ItemName;
		Cmd.LibID		=LibID;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedProcess3D::GUICmdSendModifySelectedProcess3D(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedProcess3D::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedProcess3D::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedProcess3D::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	Process3DBase *BBase=(Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	if(BBase!=NULL){
		CmdModifySelectedProcess3DFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedProcess3DItemAttr::GUICmdReqSelectedProcess3DItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedProcess3DItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedProcess3DItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedProcess3DItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedProcess3DItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedProcess3DItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedProcess3DItemAttr::GUICmdSendSelectedProcess3DItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedProcess3DItemAttr::Make(int localPage ,LayersBase *Base)
{
	Process3DBase *BBase=(Process3DBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	if(BBase!=NULL){
		Process3DInPage	*PData=dynamic_cast<Process3DInPage *>(BBase->GetPageData(localPage));
		CmdGetOneSelectedItem	Cmd(this);
		PData->TransmitDirectly(&Cmd);
		if(Cmd.ExistSelected==true){
			ExistSelected=true;
			BItem=Cmd.Buff;
		}
	}
}
bool	GUICmdSendSelectedProcess3DItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedProcess3DItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedProcess3DItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqProcess3DInfoList::GUICmdReqProcess3DInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqProcess3DInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendProcess3DInfoList	*SendBack=GetSendBack(GUICmdSendProcess3DInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	Process3DBase *BBase=(Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	if(BBase!=NULL){
		CmdProcess3DInfoListPacket	Cmd(this);
		Cmd.Process3DInfos	=&SendBack->Process3DInfos;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendProcess3DInfoList::GUICmdSendProcess3DInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendProcess3DInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	Process3DInfos.RemoveAll();
	for(int i=0;i<N;i++){
		Process3DInfoList	*a=new Process3DInfoList();
		if(a->Load(f)==false)
			return false;
		Process3DInfos.AppendList(a);
	}
	return false;
}
bool	GUICmdSendProcess3DInfoList::Save(QIODevice *f)
{
	int	N=Process3DInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(Process3DInfoList	*a=Process3DInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendProcess3DInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=============================================================================================

GUICmdReqProcess3DFromList::GUICmdReqProcess3DFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqProcess3DFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqProcess3DFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqProcess3DFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckProcess3DFromList	*SendBack=GetSendBack(GUICmdAckProcess3DFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	Process3DBase	*BBase=(Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetProcess3DFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
			SendBack->Process3DInfoOnMouse[N]=Cmd.Process3DInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckProcess3DFromList::GUICmdAckProcess3DFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(Process3DInfoOnMouse)/sizeof(Process3DInfoOnMouse[0]);i++){
		Process3DInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckProcess3DFromList::~GUICmdAckProcess3DFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(Process3DInfoOnMouse)/sizeof(Process3DInfoOnMouse[0]);i++){
			if(Process3DInfoOnMouse[i]!=NULL){
				delete	Process3DInfoOnMouse[i];
				Process3DInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckProcess3DFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	Process3DBase	*BBase=(Process3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Process3D");
	for(int i=0;i<N;i++){
		CmdCreateProcess3DItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		Process3DInfoOnMouse[i]=Cmd.Process3D;
		Created=true;
		if(Process3DInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckProcess3DFromList::Save(QIODevice *f)
{
	int32	N=sizeof(Process3DInfoOnMouse)/sizeof(Process3DInfoOnMouse[0]);
	for(int i=0;i<sizeof(Process3DInfoOnMouse)/sizeof(Process3DInfoOnMouse[0]);i++){
		if(Process3DInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(Process3DInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckProcess3DFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//=============================================================================================
