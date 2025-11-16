/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVIA\XPropertyVIAPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyVIAPacket.h"
#include "XViaInspection.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
		if(Ab!=NULL){
			CmdCreateTempVIALibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestVIAPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
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
	CmdClearTestVIAPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

VIADrawAttr::VIADrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
VIADrawAttr::VIADrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,QColor pickupcol		,int ptranparentLevel
							, QColor &_VIAColor0
							, QColor &_VIAColor1
							, QColor &_VIAColor2
							, QColor &_VIAColor3
							, QColor &_VIAColor4
							, QColor &_VIAColor5
							, QColor &_VIAColor6
							, QColor &_VIAColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel),ServiceForLayers(Base)
{
	Initial();
	ColorPickup				=pickupcol;
	ColorPickup				.setAlpha(ptranparentLevel);

	VIAColor0	=_VIAColor0;
	VIAColor1	=_VIAColor1;
	VIAColor2	=_VIAColor2;
	VIAColor3	=_VIAColor3;
	VIAColor4	=_VIAColor4;
	VIAColor5	=_VIAColor5;
	VIAColor6	=_VIAColor6;
	VIAColor7	=_VIAColor7;

	VIAColor0.setAlpha(ptranparentLevel);
	VIAColor1.setAlpha(ptranparentLevel);
	VIAColor2.setAlpha(ptranparentLevel);
	VIAColor3.setAlpha(ptranparentLevel);
	VIAColor4.setAlpha(ptranparentLevel);
	VIAColor5.setAlpha(ptranparentLevel);
	VIAColor6.setAlpha(ptranparentLevel);
	VIAColor7.setAlpha(ptranparentLevel);
}
void	VIADrawAttr::Initial(void)
{
	CmdVIADrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyVIAInspection" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
}


//=====================================================================================
GUICmdGenerateVIAs::GUICmdGenerateVIAs(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateVIAs::~GUICmdGenerateVIAs(void)
{
}

bool	GUICmdGenerateVIAs::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateVIAs::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateVIAs::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateVIAPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
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
GUICmdSendAddManualVIA::GUICmdSendAddManualVIA(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualVIA::Load(QIODevice *f)
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
bool	GUICmdSendAddManualVIA::Save(QIODevice *f)
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

void	GUICmdSendAddManualVIA::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	VIABase *BBase=(VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		CmdAddByteVIAItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedVIA::GUICmdSendModifySelectedVIA(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedVIA::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedVIA::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedVIA::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	VIABase *BBase=(VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		CmdModifySelectedVIAFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedVIAItemAttr::GUICmdReqSelectedVIAItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedVIAItemAttr::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectedVIAItemAttr::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqSelectedVIAItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedVIAItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedVIAItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase(),LayerList);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedVIAItemAttr::GUICmdSendSelectedVIAItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedVIAItemAttr::Make(int localPage ,LayersBase *Base ,IntList &LayerList)
{
	VIABase *BBase=(VIABase *)Base->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		VIAInPage	*PData=dynamic_cast<VIAInPage	*>(BBase->GetPageData(localPage));
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			VIAInLayer	*LData=dynamic_cast<VIAInLayer *>(PData->GetLayerData(L->GetValue()));
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
bool	GUICmdSendSelectedVIAItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedVIAItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedVIAItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqVIAInfoList::GUICmdReqVIAInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqVIAInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendVIAInfoList	*SendBack=GetSendBack(GUICmdSendVIAInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendVIAInfoList::GUICmdSendVIAInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendVIAInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	VIAInfos.RemoveAll();
	for(int i=0;i<N;i++){
		VIAInfoList	*a=new VIAInfoList();
		if(a->Load(f)==false)
			return false;
		VIAInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendVIAInfoList::Save(QIODevice *f)
{
	int	N=VIAInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(VIAInfoList	*a=VIAInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendVIAInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendVIAInfoList::Make(int localPage)
{
	VIABase	*BBase=(VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		CmdVIAInfoListPacket	Cmd(this);
		Cmd.LocalPage=localPage;
		Cmd.VIAInfos=&VIAInfos;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=============================================================================================

GUICmdReqVIAFromList::GUICmdReqVIAFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqVIAFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqVIAFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqVIAFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckVIAFromList	*SendBack=GetSendBack(GUICmdAckVIAFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	VIABase	*BBase=(VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetVIAFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->VIAInfoOnMouse[N]=Cmd.VIAInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckVIAFromList::GUICmdAckVIAFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(VIAInfoOnMouse)/sizeof(VIAInfoOnMouse[0]);i++){
		VIAInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckVIAFromList::~GUICmdAckVIAFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(VIAInfoOnMouse)/sizeof(VIAInfoOnMouse[0]);i++){
			if(VIAInfoOnMouse[i]!=NULL){
				delete	VIAInfoOnMouse[i];
				VIAInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckVIAFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	VIABase	*BBase=(VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	for(int i=0;i<N;i++){
		CmdCreateVIAItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		VIAInfoOnMouse[i]=Cmd.VIA;
		Created=true;
		if(VIAInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckVIAFromList::Save(QIODevice *f)
{
	int32	N=sizeof(VIAInfoOnMouse)/sizeof(VIAInfoOnMouse[0]);
	for(int i=0;i<sizeof(VIAInfoOnMouse)/sizeof(VIAInfoOnMouse[0]);i++){
		if(VIAInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(VIAInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckVIAFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
