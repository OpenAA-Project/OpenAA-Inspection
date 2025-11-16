/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\XPropertyColorBlockPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyColorBlockPacket.h"
#include "XColorBlockInspection.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
		if(Ab!=NULL){
			CmdCreateTempColorBlockLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestColorBlockPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
}

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdTestClear::Load(QIODevice *f){		return true;	}
bool	GUICmdTestClear::Save(QIODevice *f){		return true;	}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestColorBlockPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
}
//====================================================================================

ColorBlockDrawAttr::ColorBlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
ColorBlockDrawAttr::ColorBlockDrawAttr(LayersBase *Base
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
void	ColorBlockDrawAttr::Initial(void)
{
	CmdColorBlockDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyColorBlockForm" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
	DType	=DrawMode.DType;
}


//=====================================================================================
GUICmdGenerateColorBlocks::GUICmdGenerateColorBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateColorBlocks::~GUICmdGenerateColorBlocks(void)
{
}

bool	GUICmdGenerateColorBlocks::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateColorBlocks::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateColorBlocks::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateColorBlockPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
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
GUICmdSendAddManualColorBlock::GUICmdSendAddManualColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualColorBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualColorBlock::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualColorBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ColorBlockBase *BBase=(ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(BBase!=NULL){
		CmdAddByteColorBlockItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdSendModifySelectedColorBlock::GUICmdSendModifySelectedColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedColorBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedColorBlock::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedColorBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorBlockBase *BBase=(ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(BBase!=NULL){
		CmdModifySelectedColorBlockFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedColorBlockItemAttr::GUICmdReqSelectedColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedColorBlockItemAttr::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectedColorBlockItemAttr::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqSelectedColorBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedColorBlockItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedColorBlockItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase(),LayerList);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedColorBlockItemAttr::GUICmdSendSelectedColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedColorBlockItemAttr::Make(int localPage ,LayersBase *Base ,IntList &LayerList)
{
	ColorBlockBase *BBase=(ColorBlockBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(BBase!=NULL){
		ColorBlockInPage	*PData=dynamic_cast<ColorBlockInPage	*>(BBase->GetPageData(localPage));
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
bool	GUICmdSendSelectedColorBlockItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedColorBlockItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedColorBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}
//=====================================================================================

GUICmdReqColorBlockInfoList::GUICmdReqColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqColorBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendColorBlockInfoList	*SendBack=GetSendBack(GUICmdSendColorBlockInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendColorBlockInfoList::GUICmdSendColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendColorBlockInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	ColorBlockInfos.RemoveAll();
	for(int i=0;i<N;i++){
		ColorBlockInfoList	*a=new ColorBlockInfoList();
		if(a->Load(f)==false)
			return false;
		ColorBlockInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendColorBlockInfoList::Save(QIODevice *f)
{
	int	N=ColorBlockInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ColorBlockInfoList	*a=ColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendColorBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendColorBlockInfoList::Make(int localPage)
{
	ColorBlockBase	*BBase=(ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	CmdColorBlockInfoListPacket	Cmd(this);
	Cmd.LocalPage=localPage;
	Cmd.ColorBlockInfos=&ColorBlockInfos;
	BBase->TransmitDirectly(&Cmd);
}

//=============================================================================================

GUICmdReqColorBlockFromList::GUICmdReqColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqColorBlockFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqColorBlockFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqColorBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorBlockFromList	*SendBack=GetSendBack(GUICmdAckColorBlockFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ColorBlockBase	*BBase=(ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(BBase!=NULL){
		int	N=0;
		for(IntClass *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetColorBlockFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->ColorBlockInfoOnMouse[N]=Cmd.ColorBlockInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorBlockFromList::GUICmdAckColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(ColorBlockInfoOnMouse)/sizeof(ColorBlockInfoOnMouse[0]);i++){
		ColorBlockInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckColorBlockFromList::~GUICmdAckColorBlockFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(ColorBlockInfoOnMouse)/sizeof(ColorBlockInfoOnMouse[0]);i++){
			if(ColorBlockInfoOnMouse[i]!=NULL){
				delete	ColorBlockInfoOnMouse[i];
				ColorBlockInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckColorBlockFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	ColorBlockBase	*BBase=(ColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	for(int i=0;i<N;i++){
		CmdCreateColorBlockItem	Cmd(this);
		BBase->TransmitDirectly(&Cmd);
		ColorBlockInfoOnMouse[i]=Cmd.ColorBlock;
		Created=true;
		if(ColorBlockInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckColorBlockFromList::Save(QIODevice *f)
{
	int32	N=sizeof(ColorBlockInfoOnMouse)/sizeof(ColorBlockInfoOnMouse[0]);
	for(int i=0;i<sizeof(ColorBlockInfoOnMouse)/sizeof(ColorBlockInfoOnMouse[0]);i++){
		if(ColorBlockInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(ColorBlockInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckColorBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
