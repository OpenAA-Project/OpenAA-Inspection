/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\XPropertyBlockPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyBlockPacket.h"
#include "XBlockInspection.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
		if(Ab!=NULL){
			CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestBlockPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
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
	CmdClearTestBlockPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

BlockDrawAttr::BlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
BlockDrawAttr::BlockDrawAttr(LayersBase *Base
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
void	BlockDrawAttr::Initial(void)
{
	CmdBlockDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBlockForm" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
	DType	=DrawMode.DType;

	DrawDirUp			=DrawMode.DrawDirUp		;
	DrawDirLeft			=DrawMode.DrawDirLeft	;	
	DrawDirRight		=DrawMode.DrawDirRight	;
	DrawDirBottom		=DrawMode.DrawDirBottom	;
	DrawDirSkip			=DrawMode.DrawDirSkip	;
	DrawOmitMatchLineArea=DrawMode.DrawOmitMatchLineArea	;
}


//=====================================================================================
GUICmdGenerateBlocks::GUICmdGenerateBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateBlocks::~GUICmdGenerateBlocks(void)
{
}

bool	GUICmdGenerateBlocks::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateBlocks::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateBlocks::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateBlockPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
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
GUICmdSendAddManualBlock::GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualBlock::Load(QIODevice *f)
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
bool	GUICmdSendAddManualBlock::Save(QIODevice *f)
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

void	GUICmdSendAddManualBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	BlockBase *BBase=(BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdAddByteBlockItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedBlock::GUICmdSendModifySelectedBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedBlock::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	BlockBase *BBase=(BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdModifySelectedBlockFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedBlockItemAttr::GUICmdReqSelectedBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedBlockItemAttr::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqSelectedBlockItemAttr::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqSelectedBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedBlockItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedBlockItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase(),LayerList);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedBlockItemAttr::GUICmdSendSelectedBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedBlockItemAttr::Make(int localPage ,LayersBase *Base ,IntList &LayerList)
{
	BlockBase *BBase=(BlockBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		BlockInPage	*PData=dynamic_cast<BlockInPage	*>(BBase->GetPageData(localPage));
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			BlockInLayer	*LData=dynamic_cast<BlockInLayer *>(PData->GetLayerData(L->GetValue()));
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
bool	GUICmdSendSelectedBlockItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedBlockItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqBlockInfoList::GUICmdReqBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBlockInfoList	*SendBack=GetSendBack(GUICmdSendBlockInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendBlockInfoList::GUICmdSendBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendBlockInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	BlockInfos.RemoveAll();
	for(int i=0;i<N;i++){
		BlockInfoList	*a=new BlockInfoList();
		if(a->Load(f)==false)
			return false;
		BlockInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendBlockInfoList::Save(QIODevice *f)
{
	int	N=BlockInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(BlockInfoList	*a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendBlockInfoList::Make(int localPage)
{
	BlockBase	*BBase=(BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdBlockInfoListPacket	Cmd(this);
		Cmd.LocalPage=localPage;
		Cmd.BlockInfos=&BlockInfos;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=============================================================================================

GUICmdReqBlockFromList::GUICmdReqBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqBlockFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqBlockFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBlockFromList	*SendBack=GetSendBack(GUICmdAckBlockFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	BlockBase	*BBase=(BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetBlockFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->BlockInfoOnMouse[N]=Cmd.BlockInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBlockFromList::GUICmdAckBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(BlockInfoOnMouse)/sizeof(BlockInfoOnMouse[0]);i++){
		BlockInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckBlockFromList::~GUICmdAckBlockFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(BlockInfoOnMouse)/sizeof(BlockInfoOnMouse[0]);i++){
			if(BlockInfoOnMouse[i]!=NULL){
				delete	BlockInfoOnMouse[i];
				BlockInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckBlockFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	BlockBase	*BBase=(BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	for(int i=0;i<N;i++){
		CmdCreateBlockItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		BlockInfoOnMouse[i]=Cmd.Block;
		Created=true;
		if(BlockInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckBlockFromList::Save(QIODevice *f)
{
	int32	N=sizeof(BlockInfoOnMouse)/sizeof(BlockInfoOnMouse[0]);
	for(int i=0;i<sizeof(BlockInfoOnMouse)/sizeof(BlockInfoOnMouse[0]);i++){
		if(BlockInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(BlockInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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

GUICmdReqShrinkArea::GUICmdReqShrinkArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ShrinkDot=0;
}


bool	GUICmdReqShrinkArea::Load(QIODevice *f)
{
	if(::Load(f,ShrinkDot)==false){
		return false;
	}
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqShrinkArea::Save(QIODevice *f)
{
	if(::Save(f,ShrinkDot)==false){
		return false;
	}
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqShrinkArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdReqShrinkArea	Cmd(GetLayersBase());
		Cmd.LayerList=LayerList;
		Cmd.ShrinkDot=ShrinkDot;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=============================================================================================

GUICmdReqShrinkHalf::GUICmdReqShrinkHalf(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqShrinkHalf::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqShrinkHalf::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqShrinkHalf::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdReqShrinkHalf	Cmd(GetLayersBase());
		Cmd.LayerList=LayerList;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdReqExpandHalf::GUICmdReqExpandHalf(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqExpandHalf::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqExpandHalf::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqExpandHalf::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdReqExpandHalf	Cmd(GetLayersBase());
		Cmd.LayerList=LayerList;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=============================================================================================

GUICmdSetNGSizeInBlock::GUICmdSetNGSizeInBlock(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetNGSizeInBlock::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,BlockType)==false){
		return false;
	}
	if(::Load(f,NGSize)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetNGSizeInBlock::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,BlockType)==false){
		return false;
	}
	if(::Save(f,NGSize)==false){
		return false;
	}
	return true;
}
void	GUICmdSetNGSizeInBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdSetNGSizeInBlock	Cmd(GetLayersBase());
		Cmd.LibID		=LibID;
		Cmd.BlockType	=BlockType;
		Cmd.NGSize		=NGSize;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//=============================================================================================

GUICmdSetSearchDotInBlock::GUICmdSetSearchDotInBlock(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetSearchDotInBlock::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,SearchDot)==false){
		return false;
	}

	return true;
}
bool	GUICmdSetSearchDotInBlock::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,SearchDot)==false){
		return false;
	}

	return true;
}
void	GUICmdSetSearchDotInBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdSetSearchDotInBlock	Cmd(GetLayersBase());
		Cmd.LibID		=LibID;
		Cmd.SearchDot	=SearchDot;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdUpdateBlockCommon::GUICmdUpdateBlockCommon(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdUpdateBlockCommon::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(ThresholdInfo.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdUpdateBlockCommon::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(ThresholdInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdUpdateBlockCommon::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdUpdateBlockCommon	Cmd(GetLayersBase());
		Cmd.LibID			=LibID;
		Cmd.ThresholdInfo	=ThresholdInfo;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdGenerateBlockCommon::GUICmdGenerateBlockCommon(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdGenerateBlockCommon::Load(QIODevice *f)
{
	if(Infos.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdGenerateBlockCommon::Save(QIODevice *f)
{
	if(Infos.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateBlockCommon::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdGenerateBlockCommon	Cmd(GetLayersBase());
		Cmd.Infos			=Infos;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
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
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		CmdRemoveAllOriginalBlockItems	Cmd(GetLayersBase());
		Cmd.GeneratedOrigin			=GeneratedOrigin;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdChangeBlocksThreshold::GUICmdChangeBlocksThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	BlockLibID=-1;
}

bool	GUICmdChangeBlocksThreshold::Load(QIODevice *f)
{
	if(::Load(f,BlockLibID)==false)
		return false;
	if(::Load(f,InfosData)==false)
		return false;
	return true;
}	
bool	GUICmdChangeBlocksThreshold::Save(QIODevice *f)
{
	if(::Save(f,BlockLibID)==false)
		return false;
	if(::Save(f,InfosData)==false)
		return false;
	return true;
}
	
void	GUICmdChangeBlocksThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(BBase!=NULL){
		ChangeBlocksThresholdCommon	Cmd(GetLayersBase());
		Cmd.BlockLibID			=BlockLibID;
		Cmd.InfosData			=InfosData;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
