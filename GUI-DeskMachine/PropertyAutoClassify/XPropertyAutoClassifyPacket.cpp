/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\PropertyAutoClassify\XPropertyAutoClassifyPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyAutoClassifyPacket.h"
#include "XAutoClassify.h"
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
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
		if(Ab!=NULL){
			CmdCreateTempAutoClassifyLibraryPacket	Packet(GetLayersBase());
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
	CmdPickupTestAutoClassifyPacket	PTestPacket(GetLayersBase());
	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
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
	CmdClearTestAutoClassifyPacket	ClearTestPacket(GetLayersBase());
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//====================================================================================

AutoClassifyDrawAttr::AutoClassifyDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
	Initial();
}
AutoClassifyDrawAttr::AutoClassifyDrawAttr(LayersBase *Base
							,QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,QColor pickupcol		,int ptranparentLevel
							, QColor &areaColor0
							, QColor &areaColor1
							, QColor &areaColor2
							, QColor &areaColor3
							, QColor &areaColor4
							, QColor &areaColor5
							, QColor &areaColor6
							, QColor &areaColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel ,scol ,stranparentLevel,acol,atranparentLevel),ServiceForLayers(Base)
{
	Initial();
	ColorPickup				=pickupcol;
	ColorPickup				.setAlpha(ptranparentLevel);

	AreaColor0	=areaColor0;
	AreaColor1	=areaColor1;
	AreaColor2	=areaColor2;
	AreaColor3	=areaColor3;
	AreaColor4	=areaColor4;
	AreaColor5	=areaColor5;
	AreaColor6	=areaColor6;
	AreaColor7	=areaColor7;

	AreaColor0.setAlpha(ptranparentLevel);
	AreaColor1.setAlpha(ptranparentLevel);
	AreaColor2.setAlpha(ptranparentLevel);
	AreaColor3.setAlpha(ptranparentLevel);
	AreaColor4.setAlpha(ptranparentLevel);
	AreaColor5.setAlpha(ptranparentLevel);
	AreaColor6.setAlpha(ptranparentLevel);
	AreaColor7.setAlpha(ptranparentLevel);
}
void	AutoClassifyDrawAttr::Initial(void)
{
	CmdAutoClassifyDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoClassifyForm" ,/**/"");
	if(DProp!=NULL){
		DProp->TransmitDirectly(&DrawMode);
	}
	Mode	=DrawMode.Mode;
}


//=====================================================================================
GUICmdGenerateAreas::GUICmdGenerateAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateAreas::~GUICmdGenerateAreas(void)
{
}

bool	GUICmdGenerateAreas::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdGenerateAreas::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdGenerateAreas::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdGenerateAutoClassifyPacket	PTestPacket(GetLayersBase());
	PTestPacket.LibList		=LibList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}

//=====================================================================================
GUICmdSendAddManualArea::GUICmdSendAddManualArea(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualArea::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualArea::Save(QIODevice *f)
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

void	GUICmdSendAddManualArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(Ab!=NULL){
		CmdAddByteAutoClassifyItemPacket	Cmd(GetLayersBase());
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LocalPage	=localPage;
		Ab->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdSendModifySelectedArea::GUICmdSendModifySelectedArea(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifySelectedArea::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendModifySelectedArea::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	return true;
}

void	GUICmdSendModifySelectedArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(Ab!=NULL){
		CmdModifySelectedAutoClassifyFromByteArray	Cmd(GetLayersBase());
		Cmd.Buff		=BItem;
		Cmd.LocalPage	=localPage;
		Ab->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdReqSelectedAutoClassifyItemAttr::GUICmdReqSelectedAutoClassifyItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedAutoClassifyItemAttr::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqSelectedAutoClassifyItemAttr::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSelectedAutoClassifyItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedAutoClassifyItemAttr	*SendBack=GetSendBack(GUICmdSendSelectedAutoClassifyItemAttr,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdSendSelectedAutoClassifyItemAttr::GUICmdSendSelectedAutoClassifyItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ExistSelected=false;
}
void	GUICmdSendSelectedAutoClassifyItemAttr::Make(int localPage ,LayersBase *Base)
{
	AutoClassifyBase *BBase=(AutoClassifyBase *)Base->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(BBase!=NULL){
		AutoClassifyInPage	*PData=dynamic_cast<AutoClassifyInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdGetOneSelectedItem	Cmd(GetLayersBase());
			PData->TransmitDirectly(&Cmd);
			if(Cmd.ExistSelected==true){
				ExistSelected=true;
				BItem=Cmd.Buff;
				return;
			}
		}
	}
}
bool	GUICmdSendSelectedAutoClassifyItemAttr::Load(QIODevice *f)
{
	if(::Load(f,ExistSelected)==false)
		return false;
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	return true;
}
bool	GUICmdSendSelectedAutoClassifyItemAttr::Save(QIODevice *f)
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

void	GUICmdSendSelectedAutoClassifyItemAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
}

//=====================================================================================

GUICmdReqAreaInfoList::GUICmdReqAreaInfoList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAreaInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaInfoList	*SendBack=GetSendBack(GUICmdSendAreaInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAreaInfoList::GUICmdSendAreaInfoList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAreaInfoList::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	AreaInfos.RemoveAll();
	for(int i=0;i<N;i++){
		AreaInfoList	*a=new AreaInfoList();
		if(a->Load(f)==false)
			return false;
		AreaInfos.AppendList(a);
	}
	return true;
}
bool	GUICmdSendAreaInfoList::Save(QIODevice *f)
{
	int	N=AreaInfos.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AreaInfoList	*a=AreaInfos.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendAreaInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendAreaInfoList::Make(int localPage)
{
	AutoClassifyBase	*BBase=(AutoClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(BBase!=NULL){
		CmdAreaInfoListPacket	Cmd(GetLayersBase());
		Cmd.LocalPage=localPage;
		Cmd.AreaInfos=&AreaInfos;
		BBase->TransmitDirectly(&Cmd);
	}
}

//=============================================================================================

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
		CmdReqSetButtonMode	Cmd(GetLayersBase());
		Cmd.Mode=Mode;
		L->TransmitDirectly(&Cmd);
	}
}
