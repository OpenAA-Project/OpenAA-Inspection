//#include "CreateManualDotColorMatchingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDotColorMatching\XPropertyDotColorMatchingPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
//#include "XGUI.h"


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
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(LibPoint==NULL){
		CreatedInside=true;
		if(Ab!=NULL){
			CmdCreateTempDotColorMatchingLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL || Ab==NULL)
		return false;
	//AlgorithmLibraryLevelContainer	LLib(Ab->GetLibType(),Ab->GetLibraryContainer());
	int32	LibID;
	if(::Load(f,LibID)==false)
		return false;

	//LibPoint->SetLibID(LibID);
	if(LibPoint->LoadBlob(f)==false)
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

	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestDotColorMatchingPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
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
	CmdClearTestDotColorMatchingPacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

DotColorMatchingDrawAttr::DotColorMatchingDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
DotColorMatchingDrawAttr::DotColorMatchingDrawAttr(LayersBase *Base
							,const QColor &ncol ,int ntranparentLevel
							,const QColor &scol ,int stranparentLevel
							,const QColor &acol ,int atranparentLevel
							,const QColor &pickupcol	,int ptranparentLevel
							, const QColor &_DotColorMatchingColor0
							, const QColor &_DotColorMatchingColor1
							, const QColor &_DotColorMatchingColor2
							, const QColor &_DotColorMatchingColor3
							, const QColor &_DotColorMatchingColor4
							, const QColor &_DotColorMatchingColor5
							, const QColor &_DotColorMatchingColor6
							, const QColor &_DotColorMatchingColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel),ServiceForLayers(Base)
{
	Initial();
	ColorPickup				=pickupcol;
	ColorPickup				.setAlpha(ptranparentLevel);

	DotColorMatchingColor0	=_DotColorMatchingColor0;
	DotColorMatchingColor1	=_DotColorMatchingColor1;
	DotColorMatchingColor2	=_DotColorMatchingColor2;
	DotColorMatchingColor3	=_DotColorMatchingColor3;
	DotColorMatchingColor4	=_DotColorMatchingColor4;
	DotColorMatchingColor5	=_DotColorMatchingColor5;
	DotColorMatchingColor6	=_DotColorMatchingColor6;
	DotColorMatchingColor7	=_DotColorMatchingColor7;

	DotColorMatchingColor0.setAlpha(ptranparentLevel);
	DotColorMatchingColor1.setAlpha(ptranparentLevel);
	DotColorMatchingColor2.setAlpha(ptranparentLevel);
	DotColorMatchingColor3.setAlpha(ptranparentLevel);
	DotColorMatchingColor4.setAlpha(ptranparentLevel);
	DotColorMatchingColor5.setAlpha(ptranparentLevel);
	DotColorMatchingColor6.setAlpha(ptranparentLevel);
	DotColorMatchingColor7.setAlpha(ptranparentLevel);
}
void	DotColorMatchingDrawAttr::Initial(void)
{
	ModeShowArea		=true;
	ModeShowRotation	=false;
	ModeShowDiv			=false;
	ModeShowFlat		=false;
	ModeShowBackGround	=false;
	CmdDotColorMatchingDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotColorMatching" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
		ModeShowArea		=DrawMode.ModeShowArea		;
		ModeShowRotation	=DrawMode.ModeShowRotation	;
		ModeShowDiv			=DrawMode.ModeShowDiv		;
		ModeShowFlat		=DrawMode.ModeShowFlat		;
		ModeShowBackGround	=DrawMode.ModeShowBackGround;
	}
}


//=====================================================================================
GUICmdGenerateDotColorMatchings::GUICmdGenerateDotColorMatchings(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateDotColorMatchings::~GUICmdGenerateDotColorMatchings(void)
{
}

bool	GUICmdGenerateDotColorMatchings::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdGenerateDotColorMatchings::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;

	return true;
}

void	GUICmdGenerateDotColorMatchings::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateDotColorMatchingPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
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
GUICmdSendAddManualDotColorMatching::GUICmdSendAddManualDotColorMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualDotColorMatching::Load(QIODevice *f)
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
bool	GUICmdSendAddManualDotColorMatching::Save(QIODevice *f)
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

void	GUICmdSendAddManualDotColorMatching::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DotColorMatchingBase *BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		CmdAddByteDotColorMatchingItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedDotColorMatching::GUICmdSendModifySelectedDotColorMatching(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedDotColorMatching::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendModifySelectedDotColorMatching::Save(QIODevice *f)
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

void	GUICmdSendModifySelectedDotColorMatching::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase *BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		CmdModifySelectedDotColorMatchingFromByteArray	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.LayerList	=LayerList;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedDotColorMatchingItemAttr::GUICmdReqSelectedDotColorMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedDotColorMatchingItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedDotColorMatchingItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedDotColorMatchingItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedDotColorMatchingItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedDotColorMatchingItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedDotColorMatchingItemAttr::GUICmdSendSelectedDotColorMatchingItemAttr(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedDotColorMatchingItemAttr::Make(int localPage ,LayersBase *Base)
{
	DotColorMatchingBase *BBase=(DotColorMatchingBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*PData=dynamic_cast<DotColorMatchingInPage	*>(BBase->GetPageData(localPage));
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
bool	GUICmdSendSelectedDotColorMatchingItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedDotColorMatchingItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedDotColorMatchingItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqDotColorMatchingInfoList::GUICmdReqDotColorMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDotColorMatchingInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDotColorMatchingInfoList	*SendBack=GetSendBack(GUICmdSendDotColorMatchingInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDotColorMatchingInfoList::GUICmdSendDotColorMatchingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDotColorMatchingInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	DotColorMatchingInfos.RemoveAll();
	for(int i=0;i<N;i++){
		DotColorMatchingInfoList	*a=new DotColorMatchingInfoList();
		if(a->Load(f)==false)
			return false;
		DotColorMatchingInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendDotColorMatchingInfoList::Save(QIODevice *f)
{
	int	N=DotColorMatchingInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(DotColorMatchingInfoList	*a=DotColorMatchingInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendDotColorMatchingInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendDotColorMatchingInfoList::Make(int localPage)
{
}

//=============================================================================================

GUICmdReqDotColorMatchingFromList::GUICmdReqDotColorMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqDotColorMatchingFromList::Load(QIODevice *f)
{
	if(CurrentItem.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqDotColorMatchingFromList::Save(QIODevice *f)
{
	if(CurrentItem.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqDotColorMatchingFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDotColorMatchingFromList	*SendBack=GetSendBack(GUICmdAckDotColorMatchingFromList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		int	N=0;
		for(ListLayerAndID *a=CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
			CmdGetDotColorMatchingFromList	Cmd(this);
			Cmd.CurrentItem=*a;
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
			SendBack->DotColorMatchingInfoOnMouse[N]=Cmd.DotColorMatchingInfoOnMouse;
			N++;
			if(N>=100)
				break;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckDotColorMatchingFromList::GUICmdAckDotColorMatchingFromList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	for(int i=0;i<sizeof(DotColorMatchingInfoOnMouse)/sizeof(DotColorMatchingInfoOnMouse[0]);i++){
		DotColorMatchingInfoOnMouse[i]=NULL;
	}
	Created=false;
}

GUICmdAckDotColorMatchingFromList::~GUICmdAckDotColorMatchingFromList(void)
{
	if(Created==true){
		for(int i=0;i<sizeof(DotColorMatchingInfoOnMouse)/sizeof(DotColorMatchingInfoOnMouse[0]);i++){
			if(DotColorMatchingInfoOnMouse[i]!=NULL){
				delete	DotColorMatchingInfoOnMouse[i];
				DotColorMatchingInfoOnMouse[i]=NULL;
			}
		}
	}
}

bool	GUICmdAckDotColorMatchingFromList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	for(int i=0;i<N;i++){
		CmdCreateDotColorMatchingItem	Cmd(GetLayersBase());
		BBase->TransmitDirectly(&Cmd);
		DotColorMatchingInfoOnMouse[i]=Cmd.DotColorMatching;
		Created=true;
		if(DotColorMatchingInfoOnMouse[i]->Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdAckDotColorMatchingFromList::Save(QIODevice *f)
{
	int32	N=sizeof(DotColorMatchingInfoOnMouse)/sizeof(DotColorMatchingInfoOnMouse[0]);
	for(int i=0;i<sizeof(DotColorMatchingInfoOnMouse)/sizeof(DotColorMatchingInfoOnMouse[0]);i++){
		if(DotColorMatchingInfoOnMouse[i]==NULL){
			N=i;
			break;
		}
	}
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(DotColorMatchingInfoOnMouse[i]->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdAckDotColorMatchingFromList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
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
BlockListInfo	&BlockListInfo::operator=(const BlockListInfo &src)
{
	BlockListData=src.BlockListData;
	return *this;
}

bool	BlockListInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&BlockListData,sizeof(BlockListData))!=sizeof(BlockListData))
		return false;
	return true;
}
bool	BlockListInfo::Load(QIODevice *f)
{
	if(f->read((char *)&BlockListData,sizeof(BlockListData))!=sizeof(BlockListData))
		return false;
	return true;
}
BlockListInfoContainer	&BlockListInfoContainer::operator= (const BlockListInfoContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
BlockListInfoContainer	&BlockListInfoContainer::operator+=(const BlockListInfoContainer &src)
{
	for(BlockListInfo *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BlockListInfo *d=new BlockListInfo();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
GUICmdReqBlockListInfo::GUICmdReqBlockListInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqBlockListInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBlockListInfo	*SendBack=GetSendBack(GUICmdAckBlockListInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			for(AlgorithmItemPI *a=BPage->GetFirstData();a!=NULL;a=a->GetNext()){
				BlockListInfo	*t=new BlockListInfo();
				t->BlockListData.Page=GetLayersBase()->GetGlobalPageFromLocal(localPage);
				t->BlockListData.ItemID	=a->GetID();
				t->BlockListData.LibID	=a->GetLibID();
				a->GetXY(t->BlockListData.x1,t->BlockListData.y1
						,t->BlockListData.x2,t->BlockListData.y2);
				const DotColorMatchingThreshold	*RThr=(const DotColorMatchingThreshold	*)a->GetThresholdBaseReadable();
				t->BlockListData.AreaSearchX=RThr->AreaSearchX;
				t->BlockListData.AreaSearchY=RThr->AreaSearchY;
				t->BlockListData.SelfSearch	=RThr->SelfSearch;
				t->BlockListData.OKDotB		=RThr->Broad.OKDot;
				t->BlockListData.OKDotN		=RThr->Narrow.OKDot;
				SendBack->BlockListInfoContainerData.AppendList(t);
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

	
GUICmdAckBlockListInfo::GUICmdAckBlockListInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckBlockListInfo::Load(QIODevice *f)
{
	if(BlockListInfoContainerData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckBlockListInfo::Save(QIODevice *f)
{
	if(BlockListInfoContainerData.Save(f)==false)
		return false;
	return true;
}

//=============================================================================================
GUICmdSelectByLibOutline::GUICmdSelectByLibOutline(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSelectByLibOutline::Load(QIODevice *f)
{
	if(SelectedList.Load(f)==false)		return false;
	if(::Load(f,OutlineMode)==false)	return false;
	return true;
}
bool	GUICmdSelectByLibOutline::Save(QIODevice *f)
{
	if(SelectedList.Save(f)==false)		return false;
	if(::Save(f,OutlineMode)==false)	return false;
	return true;
}

void	GUICmdSelectByLibOutline::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			for(AlgorithmItemPI *a=BPage->GetFirstData();a!=NULL;a=a->GetNext()){
				DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
				if(Item!=NULL){
					SelectLibList	*f=SelectedList.Find(DefLibTypeDotColorMatchingInspect ,Item->GetLibID());
					if(f!=NULL && Item->OutlineBlock==OutlineMode){
						Item->SetSelected(true);
					}
					else{
						Item->SetSelected(false);
					}
				}
			}
		}
	}
	SendAck(localPage);
}

//=============================================================================================
GUICmdSetItemsByLibID::GUICmdSetItemsByLibID(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID=-1;
}
bool	GUICmdSetItemsByLibID::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)	return false;
	if(::Load(f,LibID)==false)	return false;
    if(::Load(f,AvailableMasterNo)==false)	return false;
    if(::Load(f,MasterNoOriginCode)==false)	return false;

    if(::Load(f,AvailableSubBlock)==false)	return false;
    if(SubBlockList.Load(f)==false)	return false;
	if(::Load(f,ExpandToSubBlock)==false)	return false;
	return true;
}
bool	GUICmdSetItemsByLibID::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)	return false;
	if(::Save(f,LibID)==false)	return false;
    if(::Save(f,AvailableMasterNo)==false)	return false;
    if(::Save(f,MasterNoOriginCode)==false)	return false;

    if(::Save(f,AvailableSubBlock)==false)	return false;
    if(SubBlockList.Save(f)==false)	return false;
	if(::Save(f,ExpandToSubBlock)==false)	return false;
	return true;
}

void	GUICmdSetItemsByLibID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			if(ItemID<0){
				for(AlgorithmItemPI *a=BPage->GetFirstData();a!=NULL;a=a->GetNext()){
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
					if(Item!=NULL && Item->GetLibID()==LibID){
						if(AvailableMasterNo==true){
							int	MasterNo=GetLayersBase()->FindBufferInfo(MasterNoOriginCode);
							Item->GetThresholdW()->MasterNo=MasterNo;
							Item->SetMasterNo(MasterNo);
						}
						if(AvailableSubBlock==true){
							IntList	SubtractLibID;
							for(AlgorithmLibraryList *a=SubBlockList.GetFirst();a!=NULL;a=a->GetNext()){
								SubtractLibID.Add(a->GetLibID());
							}
							Item->GetThresholdW()->SubtractLibID	=SubtractLibID;
						}
						Item->GetThresholdW()->ExpandToSubBlock	=ExpandToSubBlock;
					}
				}
			}
			else{
				DotColorMatchingItem	*Item=(DotColorMatchingItem *)BPage->SearchIDItem(ItemID);
				if(Item!=NULL){
					if(AvailableMasterNo==true){
						int	MasterNo=GetLayersBase()->FindBufferInfo(MasterNoOriginCode);
						Item->GetThresholdW()->MasterNo=MasterNo;
						Item->SetMasterNo(MasterNo);
					}
					if(AvailableSubBlock==true){
						IntList	SubtractLibID;
						for(AlgorithmLibraryList *a=SubBlockList.GetFirst();a!=NULL;a=a->GetNext()){
							SubtractLibID.Add(a->GetLibID());
						}
						Item->GetThresholdW()->SubtractLibID	=SubtractLibID;
					}
					Item->GetThresholdW()->ExpandToSubBlock	=ExpandToSubBlock;
				}
			}
		}
	}
}

//=============================================================================================
GUICmdReqItemsByLibID::GUICmdReqItemsByLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemsByLibID::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	if(::Load(f,LibID)==false)	return false;
	return true;
}
bool	GUICmdReqItemsByLibID::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	if(::Save(f,LibID)==false)	return false;
	return true;
}

void	GUICmdReqItemsByLibID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemsByLibID	*SendBack=GetSendBack(GUICmdAckItemsByLibID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			if(ItemID<0){
				for(AlgorithmItemPI *a=BPage->GetFirstData();a!=NULL;a=a->GetNext()){
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
					if(Item!=NULL && Item->GetLibID()==LibID){
						SendBack->SetData(Item);
					}
				}
			}
			else{
				DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(BPage->SearchIDItem(ItemID));
				if(Item!=NULL){
					SendBack->SetData(Item);
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemsByLibID::GUICmdAckItemsByLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemsByLibID::Load(QIODevice *f)
{
	if(::Load(f,MasterNoOriginCode)==false)	return false;
	if(SubLibIDs.Load(f)==false)				return false;
	if(::Load(f,ExpandToSubBlock)==false)	return false;
	return true;
}
bool	GUICmdAckItemsByLibID::Save(QIODevice *f)
{
	if(::Save(f,MasterNoOriginCode)==false)	return false;
	if(SubLibIDs.Save(f)==false)				return false;
	if(::Save(f,ExpandToSubBlock)==false)	return false;
	return true;
}
void	GUICmdAckItemsByLibID::SetData(DotColorMatchingItem *Item)
{
	BufferInfoList	*B=GetLayersBase()->GetBufferInfo(Item->GetMasterNo());
	if(B!=NULL){
		MasterNoOriginCode=B->OriginCode;
	}
	for(SubtractItem *d=Item->GetSubBlock().GetFirst();d!=NULL;d=d->GetNext()){
		SubLibIDs.Merge(GetLayersBase()
					,DefLibTypeDotColorMatchingInspect
					,d->LibID);
	}
	ExpandToSubBlock=Item->GetThresholdR()->ExpandToSubBlock;
}

//=============================================================================================

GUICmdSetSpecialData::GUICmdSetSpecialData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetSpecialData::Load(QIODevice *f)
{
	if(::Load(f,SpecialData)==false)	return false;
	return true;
}
bool	GUICmdSetSpecialData::Save(QIODevice *f)
{
	if(::Save(f,SpecialData)==false)	return false;
	return true;
}
void	GUICmdSetSpecialData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdSetSpecialData	DPacket(this);
			DPacket.SpecialData	=SpecialData;
			BPage->TransmitDirectly(&DPacket);
		}
	}
	SendAck(localPage);
}
//=============================================================================================

GUICmdAddDotColorMatching::GUICmdAddDotColorMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddDotColorMatching::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)	return false;
	if(Area.Load(f)==false)		return false;
	if(::Load(f,ItemName)==false)	return false;
	return true;
}
bool	GUICmdAddDotColorMatching::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)	return false;
	if(Area.Save(f)==false)		return false;
	if(::Save(f,ItemName)==false)	return false;
	return true;
}

void	GUICmdAddDotColorMatching::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdAddDotColorMatching	DPacket(this);
			DPacket.LibID	=LibID;
			DPacket.Area	=Area;
			DPacket.ItemName=ItemName;
			BPage->TransmitDirectly(&DPacket);
		}
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdDeleteDotColorMatchingByName::GUICmdDeleteDotColorMatchingByName(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdDeleteDotColorMatchingByName::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)	return false;
	return true;
}
bool	GUICmdDeleteDotColorMatchingByName::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)	return false;
	return true;
}

void	GUICmdDeleteDotColorMatchingByName::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			CmdDeleteDotColorMatchingByName	DPacket(this);
			DPacket.ItemName=ItemName;
			BPage->TransmitDirectly(&DPacket);
		}
	}
	SendAck(localPage);
}

//=============================================================================================

GUICmdReqSelectedItemLib::GUICmdReqSelectedItemLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqSelectedItemLib::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectedItemLib	*SendBack=GetSendBack(GUICmdAckSelectedItemLib,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		DotColorMatchingInPage	*BPage=(DotColorMatchingInPage *)BBase->GetPageData(localPage);
		if(BPage!=NULL){
			for(AlgorithmItemPI *a=BPage->GetFirstData();a!=NULL;a=a->GetNext()){
				DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
				if(Item!=NULL && Item->GetSelected()==true){
					SendBack->SelectedItemLibID.Merge(Item->GetLibID());
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckSelectedItemLib::GUICmdAckSelectedItemLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckSelectedItemLib::Load(QIODevice *f)
{
	if(SelectedItemLibID.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckSelectedItemLib::Save(QIODevice *f)
{
	if(SelectedItemLibID.Save(f)==false)	return false;
	return true;
}