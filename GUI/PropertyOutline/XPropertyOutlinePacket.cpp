/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOutline\XPropertyOutlinePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyOutlinePacket.h"
#include "XOutlineInspect.h"
#include "XGeneralFunc.h"


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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
		if(Ab!=NULL){
			CmdCreateTempOutlineLibraryPacket	Packet(GetLayersBase());
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
	if(LibPoint->Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestOutlinePacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}
}

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdTestClear::Load(QIODevice *f){		return true;	}
bool	GUICmdTestClear::Save(QIODevice *f){		return true;	}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestOutlinePacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
}

//====================================================================================

OutlineDrawAttr::OutlineDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
OutlineDrawAttr::OutlineDrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,QColor pickupcol		,int ptranparentLevel)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel),ServiceForLayers(Base)
{
	Initial();
	ColorPickup				=pickupcol;
	ColorPickup				.setAlpha(ptranparentLevel);
}
void	OutlineDrawAttr::Initial(void)
{
	CmdOutlineDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyOutlineForm" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
	DType	=DrawMode.DType;
}


//=====================================================================================
GUICmdGenerateOutlines::GUICmdGenerateOutlines(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateOutlines::~GUICmdGenerateOutlines(void)
{
}

bool	GUICmdGenerateOutlines::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateOutlines::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateOutlines::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateOutlinePacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
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
	MapList.RemoveAll();
	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		DataInLayer	*BLayer=Base->GetPageData(localPage)->GetLayerData(Layer);
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
GUICmdSendAddManualOutline::GUICmdSendAddManualOutline(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualOutline::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualOutline::Save(QIODevice *f)
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

void	GUICmdSendAddManualOutline::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	OutlineBase *BBase=(OutlineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(BBase!=NULL){
		CmdAddByteOutlineItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdSendModifySelectedOutline::GUICmdSendModifySelectedOutline(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedOutline::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedOutline::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedOutline::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	OutlineBase *BBase=(OutlineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(BBase!=NULL){
		CmdModifySelectedOutlineFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=====================================================================================
GUICmdReqSelectedOutlineItemAttr::GUICmdReqSelectedOutlineItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedOutlineItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedOutlineItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedOutlineItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedOutlineItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedOutlineItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedOutlineItemAttr::GUICmdSendSelectedOutlineItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedOutlineItemAttr::Make(int localPage ,LayersBase *Base)
{
	OutlineBase *BBase=(OutlineBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(BBase!=NULL){
		OutlineInPage	*PData=dynamic_cast<OutlineInPage *>(BBase->GetPageData(localPage));
		CmdGetOneSelectedItem	Cmd(this);
		PData->TransmitDirectly(&Cmd);
		if(Cmd.ExistSelected==true){
			ExistSelected=true;
			BItem=Cmd.Buff;
		}
	}
}
bool	GUICmdSendSelectedOutlineItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedOutlineItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedOutlineItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqOutlineInfoList::GUICmdReqOutlineInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqOutlineInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendOutlineInfoList	*SendBack=GetSendBack(GUICmdSendOutlineInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendOutlineInfoList::GUICmdSendOutlineInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendOutlineInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	OutlineInfos.RemoveAll();
	for(int i=0;i<N;i++){
		OutlineInfoList	*a=new OutlineInfoList();
		if(a->Load(f)==false)
			return false;
		OutlineInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendOutlineInfoList::Save(QIODevice *f)
{
	int	N=OutlineInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(OutlineInfoList	*a=OutlineInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendOutlineInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendOutlineInfoList::Make(int localPage)
{
	OutlineBase	*BBase=(OutlineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	CmdOutlineInfoListPacket	Cmd(GetLayersBase());
	Cmd.LocalPage=localPage;
	Cmd.OutlineInfos=&OutlineInfos;
	BBase->TransmitDirectly(&Cmd);
}

//=============================================================================================

GUICmdReqOutlineFromList::GUICmdReqOutlineFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqOutlineFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqOutlineFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqOutlineFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOutlineFromList	*SendBack=GetSendBack(GUICmdAckOutlineFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	OutlineBase	*BBase=(OutlineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetOutlineFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->OutlineInfoOnMouse[N]=Cmd.OutlineInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOutlineFromList::GUICmdAckOutlineFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(OutlineInfoOnMouse)/sizeof(OutlineInfoOnMouse[0]);i++){
		OutlineInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckOutlineFromList::~GUICmdAckOutlineFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(OutlineInfoOnMouse)/sizeof(OutlineInfoOnMouse[0]);i++){
			if(OutlineInfoOnMouse[i]!=NULL){
				delete	OutlineInfoOnMouse[i];
				OutlineInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckOutlineFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	OutlineBase	*BBase=(OutlineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	for(int i=0;i<N;i++){
		CmdCreateOutlineItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		OutlineInfoOnMouse[i]=Cmd.OutlineBlock;
		Created=true;
		if(OutlineInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckOutlineFromList::Save(QIODevice *f)
{
	int32	N=sizeof(OutlineInfoOnMouse)/sizeof(OutlineInfoOnMouse[0]);
	for(int i=0;i<sizeof(OutlineInfoOnMouse)/sizeof(OutlineInfoOnMouse[0]);i++){
		if(OutlineInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(OutlineInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckOutlineFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
	BYTE	e;
	if(::Load(f,e)==false){
		return false;
	}
	DType=(DrawType)e;
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
	BYTE	e=(BYTE)DType;
	if(::Save(f,e)==false){
		return false;
	}

	return true;
}
void	GUICmdReqSetButtonMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstForm);
	if(L!=NULL){
		CmdReqSetButtonMode	Cmd(this);
		Cmd.Mode	=Mode;
		Cmd.DType	=DType;
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
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqRGBStockFromArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
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
