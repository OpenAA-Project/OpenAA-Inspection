/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyThinMetal\XPropertyThinMetalPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyThinMetalPacket.h"
#include "XThinMetal.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
		if(Ab!=NULL){
			CmdCreateTempThinMetalLibraryPacket	Packet(GetLayersBase());
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
	int32	LibID=LibPoint->GetLibID();
	if(::Save(f,LibID)==false)
		return false;
	if(LibPoint->SaveBlob(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestThinMetalPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
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
	CmdClearTestThinMetalPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

ThinMetalDrawAttr::ThinMetalDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
ThinMetalDrawAttr::ThinMetalDrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	Initial();
}
void	ThinMetalDrawAttr::Initial(void)
{
	CmdThinMetalDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyThinMetal" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
}


//=====================================================================================
GUICmdGenerateThinMetals::GUICmdGenerateThinMetals(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateThinMetals::~GUICmdGenerateThinMetals(void)
{
}

bool	GUICmdGenerateThinMetals::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateThinMetals::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateThinMetals::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateThinMetalPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
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
GUICmdSendAddManualThinMetal::GUICmdSendAddManualThinMetal(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualThinMetal::Load(QIODevice *f)
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
bool	GUICmdSendAddManualThinMetal::Save(QIODevice *f)
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

void	GUICmdSendAddManualThinMetal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ThinMetalBase *BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		CmdAddByteThinMetalItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedThinMetal::GUICmdSendModifySelectedThinMetal(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedThinMetal::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedThinMetal::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedThinMetal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ThinMetalBase *BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		CmdModifySelectedThinMetalFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedThinMetalItemAttr::GUICmdReqSelectedThinMetalItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedThinMetalItemAttr::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectedThinMetalItemAttr::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqSelectedThinMetalItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedThinMetalItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedThinMetalItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase(),LayerList);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedThinMetalItemAttr::GUICmdSendSelectedThinMetalItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedThinMetalItemAttr::Make(int localPage ,LayersBase *Base ,IntList &LayerList)
{
	ThinMetalBase *BBase=(ThinMetalBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		ThinMetalInPage	*PData=dynamic_cast<ThinMetalInPage	*>(BBase->GetPageData(localPage));
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			ThinMetalInLayer	*LData=dynamic_cast<ThinMetalInLayer *>(PData->GetLayerData(L->GetValue()));
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
bool	GUICmdSendSelectedThinMetalItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedThinMetalItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedThinMetalItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqThinMetalInfoList::GUICmdReqThinMetalInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqThinMetalInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendThinMetalInfoList	*SendBack=GetSendBack(GUICmdSendThinMetalInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendThinMetalInfoList::GUICmdSendThinMetalInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendThinMetalInfoList::Load(QIODevice *f)
{
	if(ThinMetalInfos.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendThinMetalInfoList::Save(QIODevice *f)
{
	if(ThinMetalInfos.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendThinMetalInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendThinMetalInfoList::Make(int localPage)
{
	ThinMetalBase	*BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		CmdThinMetalInfoListPacket	Cmd(this);
		Cmd.LocalPage=localPage;
		Cmd.ThinMetalInfos=&ThinMetalInfos;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=============================================================================================

GUICmdReqThinMetalFromList::GUICmdReqThinMetalFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqThinMetalFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqThinMetalFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqThinMetalFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThinMetalFromList	*SendBack=GetSendBack(GUICmdAckThinMetalFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ThinMetalBase	*BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetThinMetalFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->ThinMetalInfoOnMouse[N]=Cmd.ThinMetalInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckThinMetalFromList::GUICmdAckThinMetalFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(ThinMetalInfoOnMouse)/sizeof(ThinMetalInfoOnMouse[0]);i++){
		ThinMetalInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckThinMetalFromList::~GUICmdAckThinMetalFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(ThinMetalInfoOnMouse)/sizeof(ThinMetalInfoOnMouse[0]);i++){
			if(ThinMetalInfoOnMouse[i]!=NULL){
				delete	ThinMetalInfoOnMouse[i];
				ThinMetalInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckThinMetalFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	ThinMetalBase	*BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	for(int i=0;i<N;i++){
		CmdCreateThinMetalItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		ThinMetalInfoOnMouse[i]=Cmd.ThinMetal;
		Created=true;
		if(ThinMetalInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckThinMetalFromList::Save(QIODevice *f)
{
	int32	N=sizeof(ThinMetalInfoOnMouse)/sizeof(ThinMetalInfoOnMouse[0]);
	for(int i=0;i<sizeof(ThinMetalInfoOnMouse)/sizeof(ThinMetalInfoOnMouse[0]);i++){
		if(ThinMetalInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(ThinMetalInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckThinMetalFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=============================================================================================

GUICmdReqSetButtonMode::GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
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

//=============================================================================================

GUICmdReqThinMetalSampleList::GUICmdReqThinMetalSampleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqThinMetalSampleList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

bool	GUICmdReqThinMetalSampleList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
void	GUICmdReqThinMetalSampleList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendThinMetalSampleList	*SendBack=GetSendBack(GUICmdSendThinMetalSampleList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ThinMetalBase *BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		ThinMetalInPage	*PData=dynamic_cast<ThinMetalInPage	*>(BBase->GetPageData(localPage));
		ThinMetalInLayer	*LData=dynamic_cast<ThinMetalInLayer *>(PData->GetLayerData(Layer));
		if(LData!=NULL){
			CmdReqSampleList	Cmd(this);
			Cmd.ItemID	=ItemID;
			Cmd.Judgement	=&SendBack->Judgements;
			LData->TransmitDirectly(&Cmd);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendThinMetalSampleList::GUICmdSendThinMetalSampleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendThinMetalSampleList::Load(QIODevice *f)
{
	if(Judgements.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendThinMetalSampleList::Save(QIODevice *f)
{
	if(Judgements.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================

GUICmdReqThinMetalSampleDetail::GUICmdReqThinMetalSampleDetail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqThinMetalSampleDetail::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqThinMetalSampleDetail::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqThinMetalSampleDetail::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendThinMetalSampleDetail	*SendBack=GetSendBack(GUICmdSendThinMetalSampleDetail,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ThinMetalBase *BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		ThinMetalInPage	*PData=dynamic_cast<ThinMetalInPage	*>(BBase->GetPageData(localPage));
		ThinMetalInLayer	*LData=dynamic_cast<ThinMetalInLayer *>(PData->GetLayerData(Layer));
		if(LData!=NULL){
			CmdReqSampleDetail	Cmd(this);
			Cmd.ItemID	=ItemID;
			Cmd.Number	=Number;
			LData->TransmitDirectly(&Cmd);
			SendBack->DetailSample=*Cmd.Point;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendThinMetalSampleDetail::GUICmdSendThinMetalSampleDetail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendThinMetalSampleDetail::Load(QIODevice *f)
{
	if(DetailSample.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendThinMetalSampleDetail::Save(QIODevice *f)
{
	if(DetailSample.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================

GUICmdReqThinMetalDeleteSamples::GUICmdReqThinMetalDeleteSamples(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqThinMetalDeleteSamples::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(Numbers.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqThinMetalDeleteSamples::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(Numbers.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqThinMetalDeleteSamples::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ThinMetalBase *BBase=(ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(BBase!=NULL){
		ThinMetalInPage	*PData=dynamic_cast<ThinMetalInPage	*>(BBase->GetPageData(localPage));
		ThinMetalInLayer	*LData=dynamic_cast<ThinMetalInLayer *>(PData->GetLayerData(Layer));
		if(LData!=NULL){
			CmdReqDeleteSample	Cmd(this);
			Cmd.ItemID	=ItemID;
			Cmd.Numbers	=Numbers;
			LData->TransmitDirectly(&Cmd);
		}
	}
}

