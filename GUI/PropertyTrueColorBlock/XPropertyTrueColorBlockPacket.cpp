/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\XPropertyTrueColorBlockPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyTrueColorBlockPacket.h"
#include "XTrueColorBlock.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
		if(Ab!=NULL){
			CmdCreateTempTrueColorBlockLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestTrueColorBlockPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
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
	CmdClearTestTrueColorBlockPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
}

//====================================================================================

TrueColorBlockDrawAttr::TrueColorBlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
TrueColorBlockDrawAttr::TrueColorBlockDrawAttr(LayersBase *Base
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
void	TrueColorBlockDrawAttr::Initial(void)
{
	CmdTrueColorBlockDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTrueColorBlockForm" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
	DType	=DrawMode.DType;
}


//=====================================================================================
GUICmdGenerateTrueColorBlocks::GUICmdGenerateTrueColorBlocks(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateTrueColorBlocks::~GUICmdGenerateTrueColorBlocks(void)
{
}

bool	GUICmdGenerateTrueColorBlocks::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateTrueColorBlocks::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateTrueColorBlocks::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateTrueColorBlockPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
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
//	DataInLayer	*BLayer=Base->GetPageData(localPage)->GetLayerData(L->d);
//		BrightnessMapList	*BList=new BrightnessMapList();
//		area.MakeBrightList(BList->BrightList,BLayer->GetMasterBuff(),0 ,0);
//		MapList.AppendList(BList);
//	}
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
GUICmdSendAddManualTrueColorBlock::GUICmdSendAddManualTrueColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualTrueColorBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualTrueColorBlock::Save(QIODevice *f)
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

void	GUICmdSendAddManualTrueColorBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	TrueColorBlockBase *BBase=(TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(BBase!=NULL){
		CmdAddByteTrueColorBlockItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdSendModifySelectedTrueColorBlock::GUICmdSendModifySelectedTrueColorBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedTrueColorBlock::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedTrueColorBlock::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedTrueColorBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TrueColorBlockBase *BBase=(TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(BBase!=NULL){
		CmdModifySelectedTrueColorBlockFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedTrueColorBlockItemAttr::GUICmdReqSelectedTrueColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedTrueColorBlockItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedTrueColorBlockItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedTrueColorBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedTrueColorBlockItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedTrueColorBlockItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedTrueColorBlockItemAttr::GUICmdSendSelectedTrueColorBlockItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedTrueColorBlockItemAttr::Make(int localPage ,LayersBase *Base)
{
	TrueColorBlockBase *BBase=(TrueColorBlockBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(BBase!=NULL){
		TrueColorBlockInPage	*PData=dynamic_cast<TrueColorBlockInPage *>(BBase->GetPageData(localPage));
		CmdGetOneSelectedItem	Cmd(this);
		PData->TransmitDirectly(&Cmd);
		if(Cmd.ExistSelected==true){
			ExistSelected=true;
			BItem=Cmd.Buff;
		}
	}
}
bool	GUICmdSendSelectedTrueColorBlockItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedTrueColorBlockItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedTrueColorBlockItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqTrueColorBlockInfoList::GUICmdReqTrueColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqTrueColorBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTrueColorBlockInfoList	*SendBack=GetSendBack(GUICmdSendTrueColorBlockInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendTrueColorBlockInfoList::GUICmdSendTrueColorBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTrueColorBlockInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	TrueColorBlockInfos.RemoveAll();
	for(int i=0;i<N;i++){
		TrueColorBlockInfoList	*a=new TrueColorBlockInfoList();
		if(a->Load(f)==false)
			return false;
		TrueColorBlockInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendTrueColorBlockInfoList::Save(QIODevice *f)
{
	int	N=TrueColorBlockInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(TrueColorBlockInfoList	*a=TrueColorBlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendTrueColorBlockInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendTrueColorBlockInfoList::Make(int localPage)
{
	TrueColorBlockBase	*BBase=(TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	CmdTrueColorBlockInfoListPacket	Cmd(this);
	Cmd.LocalPage=localPage;
	Cmd.TrueColorBlockInfos=&TrueColorBlockInfos;
	BBase->TransmitDirectly(&Cmd);
}

//=============================================================================================

GUICmdReqTrueColorBlockFromList::GUICmdReqTrueColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqTrueColorBlockFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqTrueColorBlockFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqTrueColorBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckTrueColorBlockFromList	*SendBack=GetSendBack(GUICmdAckTrueColorBlockFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	TrueColorBlockBase	*BBase=(TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetTrueColorBlockFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->TrueColorBlockInfoOnMouse[N]=Cmd.TrueColorBlockInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckTrueColorBlockFromList::GUICmdAckTrueColorBlockFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(TrueColorBlockInfoOnMouse)/sizeof(TrueColorBlockInfoOnMouse[0]);i++){
		TrueColorBlockInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckTrueColorBlockFromList::~GUICmdAckTrueColorBlockFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(TrueColorBlockInfoOnMouse)/sizeof(TrueColorBlockInfoOnMouse[0]);i++){
			if(TrueColorBlockInfoOnMouse[i]!=NULL){
				delete	TrueColorBlockInfoOnMouse[i];
				TrueColorBlockInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckTrueColorBlockFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	TrueColorBlockBase	*BBase=(TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	for(int i=0;i<N;i++){
		CmdCreateTrueColorBlockItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		TrueColorBlockInfoOnMouse[i]=Cmd.TrueColorBlock;
		Created=true;
		if(TrueColorBlockInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckTrueColorBlockFromList::Save(QIODevice *f)
{
	int32	N=sizeof(TrueColorBlockInfoOnMouse)/sizeof(TrueColorBlockInfoOnMouse[0]);
	for(int i=0;i<sizeof(TrueColorBlockInfoOnMouse)/sizeof(TrueColorBlockInfoOnMouse[0]);i++){
		if(TrueColorBlockInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(TrueColorBlockInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckTrueColorBlockFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
