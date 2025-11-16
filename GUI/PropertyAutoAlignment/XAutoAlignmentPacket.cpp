/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoAlignment\XAutoAlignmentPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAutoAlignmentForm.h"
#include "EditLibraryAutoAlignment.h"
#include "XGeneralFunc.h"
#include "XAutoAlignmentPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=============================================================================================================

GUICmdCreateAutoAlignmentSheet::GUICmdCreateAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateAutoAlignmentSheet::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdCreateAutoAlignmentSheet::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdCreateAutoAlignmentSheet::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AutoAlignmentBase *PBase=(AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	CmdCreateAutoAlignmentSheetPacket	Cmd(this);
	Cmd.SelectedLibList=SelectedLibList;
	Cmd.LocalPage	=localPage;
	PBase->TransmitDirectly(&Cmd);
}


GUICmdReqAutoAlignmentInfo::GUICmdReqAutoAlignmentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAutoAlignmentInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAutoAlignmentInfo	*SendBack=GetSendBack(GUICmdSendAutoAlignmentInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAutoAlignmentInfo::GUICmdSendAutoAlignmentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAutoAlignmentInfo::Load(QIODevice *f)
{
	if(SheetLevels.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAutoAlignmentInfo::Save(QIODevice *f)
{
	if(SheetLevels.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendAutoAlignmentInfo::MakeData(int localPage)
{
	AutoAlignmentBase *PBase=(AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	CmdGetSheetLevel	Cmd(this);
	Cmd.LocalPage	=localPage;
	PBase->TransmitDirectly(&Cmd);
	SheetLevels=Cmd.SheetLevels;
}

//=============================================================================================================

GUICmdReqAutoAlignmentSheet::GUICmdReqAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAutoAlignmentSheet::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAutoAlignmentSheet	*SendBack=GetSendBack(GUICmdSendAutoAlignmentSheet,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAutoAlignmentSheet::GUICmdSendAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAutoAlignmentSheet::Load(QIODevice *f)
{
	if(AASheetInfoData.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAutoAlignmentSheet::Save(QIODevice *f)
{
	if(AASheetInfoData.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdSendAutoAlignmentSheet::MakeData(int localPage)
{
	AlgorithmBase		*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	CmdGetAutoAlignmentSheetPacket	Cmd(this);
	Cmd.Point=&AASheetInfoData;
	PPage->TransmitDirectly(&Cmd);
}

//=============================================================================================================

GUICmdSetAutoAlignmentLibColor::GUICmdSetAutoAlignmentLibColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdSetAutoAlignmentLibColor::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetAutoAlignmentLibColor::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	return true;
}

void	GUICmdSetAutoAlignmentLibColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase		*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	CmdSetAutoAlignmentLibColor	Cmd(this);
	Cmd.LocalArea	=LocalArea;
	Cmd.LibID		=LibID;
	PPage->TransmitDirectly(&Cmd);
}

//=============================================================================================================


GUICmdSetAutoAlignmentShowingState::GUICmdSetAutoAlignmentShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,State(Base)
{
}

bool	GUICmdSetAutoAlignmentShowingState::Load(QIODevice *f)
{
	if(State.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetAutoAlignmentShowingState::Save(QIODevice *f)
{
	if(State.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetAutoAlignmentShowingState::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&State);
	}
}

//=============================================================================================================

GUICmdAddAutoAlignmentSheet::GUICmdAddAutoAlignmentSheet(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddAutoAlignmentSheet::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	return true;
}
bool	GUICmdAddAutoAlignmentSheet::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	return true;
}

void	GUICmdAddAutoAlignmentSheet::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase		*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	CmdAddAutoAlignmentSheet	Cmd(this);
	Cmd.LocalArea	=LocalArea;
	Cmd.LibID		=LibID;
	PPage->TransmitDirectly(&Cmd);
}

//=============================================================================================================
GUICmdPickupTest::GUICmdPickupTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
///	LibPoint=NULL;
///	int LibID=-1;
///	CreatedInside=false;
}
GUICmdPickupTest::~GUICmdPickupTest(void)
{
/*
	if(CreatedInside==true)
		delete	LibPoint;
	LibPoint=NULL;
*/
}

bool	GUICmdPickupTest::Load(QIODevice *f)
{
	//if(LibPoint==NULL){
	//	CreatedInside=true;
	//	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	//	if(Ab!=NULL){
	//		CmdCreateTempAutoAlignmentLibraryPacket	Packet(GetLayersBase());
	//		Ab->TransmitDirectly(&Packet);
	//		LibPoint=Packet.Point;
	//	}
	//}
	//if(LibPoint==NULL)
	//	return false;

	//if(::Load(f,LibID)==false)
	//	return false;
	//LibPoint->SetLibID(LibID);
	//if(LibPoint->LoadBlob(f)==false)
	//	return false;
	return true;
}
bool	GUICmdPickupTest::Save(QIODevice *f)
{
	//if(LibPoint==NULL)
	//	return false;
	//int32	LibID=LibPoint->GetLibID();
	//if(::Save(f,LibID)==false)
	//	return false;
	//if(LibPoint->SaveBlob(f)==false)
	//	return false;
	return true;
}

void	GUICmdPickupTest::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestAutoAlignmentPacket	PTestPacket(this);
///	PTestPacket.LibID		=LibID;
///	PTestPacket.LibPoint	=LibPoint;
	PTestPacket.PhaseNumb	=PhaseNumb;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}
