/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHoleWall\XPropertyHoleWallPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyHoleWallPacket.h"
#include "XHoleWallInspection.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XPropertyHoleWallCommon.h"

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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
		if(Ab!=NULL){
			CmdCreateTempHoleWallLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestHoleWallPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
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
	CmdClearTestHoleWallPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

HoleWallDrawAttr::HoleWallDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
HoleWallDrawAttr::HoleWallDrawAttr(LayersBase *Base
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
void	HoleWallDrawAttr::Initial(void)
{
	CmdHoleWallDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyHoleWall" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
}


//=====================================================================================
GUICmdGenerateHoleWalls::GUICmdGenerateHoleWalls(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateHoleWalls::~GUICmdGenerateHoleWalls(void)
{
}

bool	GUICmdGenerateHoleWalls::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateHoleWalls::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateHoleWalls::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateHoleWallPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList.GetIDList();
	PTestPacket.Page		=localPage;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
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
GUICmdSendAddManualHoleWall::GUICmdSendAddManualHoleWall(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualHoleWall::Load(QIODevice *f)
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
bool	GUICmdSendAddManualHoleWall::Save(QIODevice *f)
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

void	GUICmdSendAddManualHoleWall::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	HoleWallBase *BBase=(HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		CmdAddByteHoleWallItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedHoleWall::GUICmdSendModifySelectedHoleWall(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedHoleWall::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedHoleWall::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedHoleWall::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	HoleWallBase *BBase=(HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		CmdModifySelectedHoleWallFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedHoleWallItemAttr::GUICmdReqSelectedHoleWallItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedHoleWallItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedHoleWallItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedHoleWallItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedHoleWallItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedHoleWallItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedHoleWallItemAttr::GUICmdSendSelectedHoleWallItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedHoleWallItemAttr::Make(int localPage ,LayersBase *Base)
{
	HoleWallBase *BBase=(HoleWallBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		HoleWallInPage	*PData=dynamic_cast<HoleWallInPage *>(BBase->GetPageData(localPage));
		CmdGetOneSelectedItem	Cmd(this);
		PData->TransmitDirectly(&Cmd);
		if(Cmd.ExistSelected==true){
			ExistSelected=true;
			BItem=Cmd.Buff;
		}
	}
}
bool	GUICmdSendSelectedHoleWallItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedHoleWallItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedHoleWallItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqHoleWallInfoList::GUICmdReqHoleWallInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqHoleWallInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendHoleWallInfoList	*SendBack=GetSendBack(GUICmdSendHoleWallInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendHoleWallInfoList::GUICmdSendHoleWallInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendHoleWallInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	HoleWallInfos.RemoveAll();
	for(int i=0;i<N;i++){
		HoleWallInfoList	*a=new HoleWallInfoList();
		if(a->Load(f)==false)
			return false;
		HoleWallInfos.AppendList(a);
	}
	return false;
}
bool	GUICmdSendHoleWallInfoList::Save(QIODevice *f)
{
	int	N=HoleWallInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(HoleWallInfoList	*a=HoleWallInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendHoleWallInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendHoleWallInfoList::Make(int localPage)
{
	HoleWallBase	*BBase=(HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	CmdHoleWallInfoListPacket	Cmd(this);
	Cmd.HoleWallInfos=&HoleWallInfos;
	BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
}

//=============================================================================================

GUICmdReqHoleWallFromList::GUICmdReqHoleWallFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqHoleWallFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqHoleWallFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqHoleWallFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHoleWallFromList	*SendBack=GetSendBack(GUICmdAckHoleWallFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	HoleWallBase	*BBase=(HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetHoleWallFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
			SendBack->HoleWallInfoOnMouse[N]=Cmd.HoleWallInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckHoleWallFromList::GUICmdAckHoleWallFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(HoleWallInfoOnMouse)/sizeof(HoleWallInfoOnMouse[0]);i++){
		HoleWallInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckHoleWallFromList::~GUICmdAckHoleWallFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(HoleWallInfoOnMouse)/sizeof(HoleWallInfoOnMouse[0]);i++){
			if(HoleWallInfoOnMouse[i]!=NULL){
				delete	HoleWallInfoOnMouse[i];
				HoleWallInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckHoleWallFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	HoleWallBase	*BBase=(HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	for(int i=0;i<N;i++){
		CmdCreateHoleWallItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		HoleWallInfoOnMouse[i]=Cmd.HoleWall;
		Created=true;
		if(HoleWallInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckHoleWallFromList::Save(QIODevice *f)
{
	int32	N=sizeof(HoleWallInfoOnMouse)/sizeof(HoleWallInfoOnMouse[0]);
	for(int i=0;i<sizeof(HoleWallInfoOnMouse)/sizeof(HoleWallInfoOnMouse[0]);i++){
		if(HoleWallInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(HoleWallInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckHoleWallFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		CmdRemoveAllOriginalHoleWallItems	Cmd(GetLayersBase());
		Cmd.GeneratedOrigin			=GeneratedOrigin;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdChangeHoleWallsThreshold::GUICmdChangeHoleWallsThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	BlockLibID=-1;
}

bool	GUICmdChangeHoleWallsThreshold::Load(QIODevice *f)
{
	if(::Load(f,BlockLibID)==false)
		return false;
	if(::Load(f,InfosData)==false)
		return false;
	return true;
}	
bool	GUICmdChangeHoleWallsThreshold::Save(QIODevice *f)
{
	if(::Save(f,BlockLibID)==false)
		return false;
	if(::Save(f,InfosData)==false)
		return false;
	return true;
}
	
void	GUICmdChangeHoleWallsThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		ChangeHoleWallsThresholdCommon	Cmd(GetLayersBase());
		Cmd.BlockLibID			=BlockLibID;
		Cmd.InfosData			=InfosData;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

GUICmdMakeBitBuff::GUICmdMakeBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdMakeBitBuff::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
	if(BBase!=NULL){
		HoleWallInPage	*PData=dynamic_cast<HoleWallInPage *>(BBase->GetPageData(localPage));
		CmdMakeBitBuff	Cmd(this);
		PData->TransmitDirectly(&Cmd);
	}
}

