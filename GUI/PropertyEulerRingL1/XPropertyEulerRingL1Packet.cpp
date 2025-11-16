/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRingL1\XPropertyEulerRingL1Packet.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyEulerRingL1Packet.h"
#include "XEulerRingL1.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XPropertyEulerRingL1Common.h"

//=============================================================================================================

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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
		if(Ab!=NULL){
			CmdCreateTempEulerRingL1LibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestEulerRingL1Packet	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
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
	CmdClearTestEulerRingL1Packet	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

EulerRingL1DrawAttr::EulerRingL1DrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
EulerRingL1DrawAttr::EulerRingL1DrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,QColor pickupcol		,int ptranparentLevel
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
	ColorPickup				=pickupcol;
	ColorPickup				.setAlpha(ptranparentLevel);

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
void	EulerRingL1DrawAttr::Initial(void)
{
	CmdEulerRingL1DrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyEulerRingL1" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
}


//=====================================================================================
GUICmdGenerateEulerRingL1s::GUICmdGenerateEulerRingL1s(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateEulerRingL1s::~GUICmdGenerateEulerRingL1s(void)
{
}

bool	GUICmdGenerateEulerRingL1s::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateEulerRingL1s::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateEulerRingL1s::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateEulerRingL1Packet	PTestPacket(this);
	PTestPacket.LibList		=LibList.GetIDList();
	PTestPacket.Page		=localPage;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
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
GUICmdSendAddManualEulerRingL1::GUICmdSendAddManualEulerRingL1(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualEulerRingL1::Load(QIODevice *f)
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
bool	GUICmdSendAddManualEulerRingL1::Save(QIODevice *f)
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

void	GUICmdSendAddManualEulerRingL1::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	EulerRingL1Base *BBase=(EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		CmdAddByteEulerRingL1ItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedEulerRingL1::GUICmdSendModifySelectedEulerRingL1(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedEulerRingL1::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedEulerRingL1::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedEulerRingL1::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	EulerRingL1Base *BBase=(EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		CmdModifySelectedEulerRingL1FromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedEulerRingL1ItemAttr::GUICmdReqSelectedEulerRingL1ItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedEulerRingL1ItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedEulerRingL1ItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedEulerRingL1ItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedEulerRingL1ItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedEulerRingL1ItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedEulerRingL1ItemAttr::GUICmdSendSelectedEulerRingL1ItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedEulerRingL1ItemAttr::Make(int localPage ,LayersBase *Base)
{
	EulerRingL1Base *BBase=(EulerRingL1Base *)Base->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		EulerRingL1InPage	*PData=dynamic_cast<EulerRingL1InPage *>(BBase->GetPageData(localPage));
		CmdGetOneSelectedItem	Cmd(this);
		PData->TransmitDirectly(&Cmd);
		if(Cmd.ExistSelected==true){
			ExistSelected=true;
			BItem=Cmd.Buff;
		}
	}
}
bool	GUICmdSendSelectedEulerRingL1ItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedEulerRingL1ItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedEulerRingL1ItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqEulerRingL1InfoList::GUICmdReqEulerRingL1InfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqEulerRingL1InfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendEulerRingL1InfoList	*SendBack=GetSendBack(GUICmdSendEulerRingL1InfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendEulerRingL1InfoList::GUICmdSendEulerRingL1InfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendEulerRingL1InfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	EulerRingL1Infos.RemoveAll();
	for(int i=0;i<N;i++){
		EulerRingL1InfoList	*a=new EulerRingL1InfoList();
		if(a->Load(f)==false)
			return false;
		EulerRingL1Infos.AppendList(a);
	}
	return false;
}
bool	GUICmdSendEulerRingL1InfoList::Save(QIODevice *f)
{
	int	N=EulerRingL1Infos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(EulerRingL1InfoList	*a=EulerRingL1Infos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendEulerRingL1InfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendEulerRingL1InfoList::Make(int localPage)
{
	EulerRingL1Base	*BBase=(EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	CmdEulerRingL1InfoListPacket	Cmd(this);
	Cmd.EulerRingL1Infos=&EulerRingL1Infos;
	BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
}

//=============================================================================================

GUICmdReqEulerRingL1FromList::GUICmdReqEulerRingL1FromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEulerRingL1FromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqEulerRingL1FromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqEulerRingL1FromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckEulerRingL1FromList	*SendBack=GetSendBack(GUICmdAckEulerRingL1FromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	EulerRingL1Base	*BBase=(EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetEulerRingL1FromList	Cmd(this);
			Cmd.CurrentItem=*a;
			BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
			SendBack->EulerRingL1InfoOnMouse[N]=Cmd.EulerRingL1InfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckEulerRingL1FromList::GUICmdAckEulerRingL1FromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(EulerRingL1InfoOnMouse)/sizeof(EulerRingL1InfoOnMouse[0]);i++){
		EulerRingL1InfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckEulerRingL1FromList::~GUICmdAckEulerRingL1FromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(EulerRingL1InfoOnMouse)/sizeof(EulerRingL1InfoOnMouse[0]);i++){
			if(EulerRingL1InfoOnMouse[i]!=NULL){
				delete	EulerRingL1InfoOnMouse[i];
				EulerRingL1InfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckEulerRingL1FromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	EulerRingL1Base	*BBase=(EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	for(int i=0;i<N;i++){
		CmdCreateEulerRingL1Item	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		EulerRingL1InfoOnMouse[i]=Cmd.EulerRingL1;
		Created=true;
		if(EulerRingL1InfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckEulerRingL1FromList::Save(QIODevice *f)
{
	int32	N=sizeof(EulerRingL1InfoOnMouse)/sizeof(EulerRingL1InfoOnMouse[0]);
	for(int i=0;i<sizeof(EulerRingL1InfoOnMouse)/sizeof(EulerRingL1InfoOnMouse[0]);i++){
		if(EulerRingL1InfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(EulerRingL1InfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckEulerRingL1FromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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

GUICmdReqRemoveAllOriginal::GUICmdReqRemoveAllOriginal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdReqRemoveAllOriginal::Load(QIODevice *f)
{
	if(::Load(f,GeneratedOrigin)==false)
		return false;
	return true;
}
	
bool	GUICmdReqRemoveAllOriginal::Save(QIODevice *f)
{
	if(::Save(f,GeneratedOrigin)==false)
		return false;
	return true;
}

	
void	GUICmdReqRemoveAllOriginal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		CmdRemoveAllOriginalEulerRingL1Items	Cmd(GetLayersBase());
		Cmd.GeneratedOrigin			=GeneratedOrigin;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdChangeEulerRingL1sThreshold::GUICmdChangeEulerRingL1sThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	BlockLibID=-1;
}

bool	GUICmdChangeEulerRingL1sThreshold::Load(QIODevice *f)
{
	if(::Load(f,BlockLibID)==false)
		return false;
	if(::Load(f,InfosData)==false)
		return false;
	return true;
}	
bool	GUICmdChangeEulerRingL1sThreshold::Save(QIODevice *f)
{
	if(::Save(f,BlockLibID)==false)
		return false;
	if(::Save(f,InfosData)==false)
		return false;
	return true;
}
	
void	GUICmdChangeEulerRingL1sThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
	if(BBase!=NULL){
		ChangeEulerRingL1sThresholdCommon	Cmd(GetLayersBase());
		Cmd.BlockLibID			=BlockLibID;
		Cmd.InfosData			=InfosData;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}