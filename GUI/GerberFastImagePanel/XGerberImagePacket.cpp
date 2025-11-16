#include "GerberFastImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GerberImagePanel\GerberImagePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "GerberFastImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "XGUIGerberPacket.h"
#include <QBitmap>
#include "XForWindows.h"
#include "XCrossObj.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XDisplayImagePacket.h"
#include "swap.h"
#include "XGerberImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//====================================================================================

GUICmdGerberDrawMode::GUICmdGerberDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberDrawMode::Save(QIODevice *f)
{
	BYTE	m=(BYTE)Mode;
	if(::Save(f,m)==false)
		return false;

	if(::Save(f,MoveMode)==false)
		return false;
	if(::Save(f,RotateMode)==false)
		return false;
	if(::Save(f,SlopeXMode)==false)
		return false;
	if(::Save(f,SlopeYMode)==false)
		return false;
	if(::Save(f,ExtendMode)==false)
		return false;
	if(::Save(f,AlignmentMode)==false)
		return false;
	if(::Save(f,AutoMatchingMode)==false)
		return false;
	if(::Save(f,LastPosX)==false)
		return false;
	if(::Save(f,LastPosY)==false)
		return false;
	if(::Save(f,MoveStartPosX)==false)
		return false;
	if(::Save(f,MoveStartPosY)==false)
		return false;
	if(::Save(f,RotateCenterXOnData)==false)
		return false;
	if(::Save(f,RotateCenterYOnData)==false)
		return false;
	if(::Save(f,RotateFirstX)==false)
		return false;
	if(::Save(f,RotateFirstY)==false)
		return false;
	if(::Save(f,RotateAngle)==false)
		return false;
	if(::Save(f,ExtendCenterXOnData)==false)
		return false;
	if(::Save(f,ExtendCenterYOnData)==false)
		return false;
	if(::Save(f,ExtendFirstX)==false)
		return false;
	if(::Save(f,ExtendFirstY)==false)
		return false;

	if(::Save(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Save(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Save(f,SlopeXFirstX)==false)
		return false;
	if(::Save(f,SlopeXFirstY)==false)
		return false;
	if(::Save(f,SlopeXAngle)==false)
		return false;

	if(::Save(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Save(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Save(f,SlopeYFirstX)==false)
		return false;
	if(::Save(f,SlopeYFirstY)==false)
		return false;
	if(::Save(f,SlopeYAngle)==false)
		return false;

	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Save(f)==false)
			return false;
		if(CadPoint[i].Save(f)==false)
			return false;
	}
	for(int i=0;i<100;i++){
		if(AMImagePoint[i].Save(f)==false)
			return false;
		if(AMCadPoint[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	GUICmdGerberDrawMode::Load(QIODevice *f)
{
	BYTE	m;
	if(::Load(f,m)==false)
		return false;
	Mode=(DisplayImage::__DrawingMode)m;

	if(::Load(f,MoveMode)==false)
		return false;
	if(::Load(f,RotateMode)==false)
		return false;
	if(::Load(f,SlopeXMode)==false)
		return false;
	if(::Load(f,SlopeYMode)==false)
		return false;
	if(::Load(f,ExtendMode)==false)
		return false;
	if(::Load(f,AlignmentMode)==false)
		return false;
	if(::Load(f,AutoMatchingMode)==false)
		return false;
	if(::Load(f,LastPosX)==false)
		return false;
	if(::Load(f,LastPosY)==false)
		return false;
	if(::Load(f,MoveStartPosX)==false)
		return false;
	if(::Load(f,MoveStartPosY)==false)
		return false;
	if(::Load(f,RotateCenterXOnData)==false)
		return false;
	if(::Load(f,RotateCenterYOnData)==false)
		return false;
	if(::Load(f,RotateFirstX)==false)
		return false;
	if(::Load(f,RotateFirstY)==false)
		return false;
	if(::Load(f,RotateAngle)==false)
		return false;
	if(::Load(f,ExtendCenterXOnData)==false)
		return false;
	if(::Load(f,ExtendCenterYOnData)==false)
		return false;
	if(::Load(f,ExtendFirstX)==false)
		return false;
	if(::Load(f,ExtendFirstY)==false)
		return false;

	if(::Load(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeXFirstX)==false)
		return false;
	if(::Load(f,SlopeXFirstY)==false)
		return false;
	if(::Load(f,SlopeXAngle)==false)
		return false;

	if(::Load(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeYFirstX)==false)
		return false;
	if(::Load(f,SlopeYFirstY)==false)
		return false;
	if(::Load(f,SlopeYAngle)==false)
		return false;

	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}
	for(int i=0;i<100;i++){
		if(AMImagePoint[i].Load(f)==false)
			return false;
		if(AMCadPoint[i].Load(f)==false)
			return false;
	}
	return true;}

void	GUICmdGerberDrawMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	GerberFastInPage	*GPage	=(GerberFastInPage *)Base->GetPageData(localPage);

	GPage->MoveMode				=MoveMode;
	GPage->RotateMode			=RotateMode;
	GPage->SlopeXMode			=SlopeXMode;
	GPage->SlopeYMode			=SlopeYMode;
	GPage->ExtendMode			=ExtendMode;
	GPage->AlignmentMode		=AlignmentMode;
	GPage->AutoMatchingMode		=AutoMatchingMode;
	GPage->Mode					=Mode;
	GPage->LastPosX				=LastPosX;
	GPage->LastPosY				=LastPosY;
	GPage->MoveStartPosX		=MoveStartPosX;
	GPage->MoveStartPosY		=MoveStartPosY;
	GPage->RotateCenterXOnData	=RotateCenterXOnData;
	GPage->RotateCenterYOnData	=RotateCenterYOnData;
	GPage->RotateFirstX			=RotateFirstX;
	GPage->RotateFirstY			=RotateFirstY;
	GPage->RotateAngle			=RotateAngle;
	GPage->ExtendCenterXOnData	=ExtendCenterXOnData;
	GPage->ExtendCenterYOnData	=ExtendCenterYOnData;
	GPage->ExtendFirstX			=ExtendFirstX;
	GPage->ExtendFirstY			=ExtendFirstY;

	GPage->SlopeXCenterXOnData	=SlopeXCenterXOnData;
	GPage->SlopeXCenterYOnData	=SlopeXCenterYOnData;
	GPage->SlopeXFirstX			=SlopeXFirstX;
	GPage->SlopeXFirstY			=SlopeXFirstY;
	GPage->SlopeXAngle			=SlopeXAngle;

	GPage->SlopeYCenterXOnData	=SlopeYCenterXOnData;
	GPage->SlopeYCenterYOnData	=SlopeYCenterYOnData;
	GPage->SlopeYFirstX			=SlopeYFirstX;
	GPage->SlopeYFirstY			=SlopeYFirstY;
	GPage->SlopeYAngle			=SlopeYAngle;

	for(int i=0;i<MaxGerberPointNumb;i++){
		GPage->ImagePoint[i]=ImagePoint[i];
		GPage->CadPoint[i]	=CadPoint[i];
	}
	for(int i=0;i<100;i++){
		GPage->AMImagePoint[i]	=AMImagePoint[i];
		GPage->AMCadPoint[i]	=AMCadPoint[i];
	}
}

//====================================================================================

GUICmdMsgGerberSelectAll::GUICmdMsgGerberSelectAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMsgGerberSelectAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	AlgorithmInPageRoot	*GPage=Base->GetPageData(localPage);
	MsgGerberSelectAll	MCmd(this);
	GPage->TransmitDirectly(&MCmd);
}

//====================================================================================

GUICmdGerberDraw::GUICmdGerberDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberDraw::Save(QIODevice *f)
{
	if(::Save(f,GlobalX)==false)
		return false;
	if(::Save(f,GlobalY)==false)
		return false;
	if(ButtonsToShowLayer.Save(f)==false)
		return false;
	if(ButtonsToOperateLayer.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdGerberDraw::Load(QIODevice *f)
{
	if(::Load(f,GlobalX)==false)
		return false;
	if(::Load(f,GlobalY)==false)
		return false;
	if(ButtonsToShowLayer.Load(f)==false)
		return false;
	if(ButtonsToOperateLayer.Load(f)==false)
		return false;
	return true;
}

void	GUICmdGerberDraw::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*GPage=Ah->GetPageData(localPage);
		CmdGerberDraw	LCmd(this);
		LCmd.GlobalX=GlobalX;
		LCmd.GlobalY=GlobalY;
		LCmd.ButtonsToShowLayer		=ButtonsToShowLayer;
		LCmd.ButtonsToOperateLayer	=ButtonsToOperateLayer;
		GPage->TransmitDirectly(&LCmd);
	}
}

//==========================================================================================
GUICmdMsgGerberExtendWithCenter::GUICmdMsgGerberExtendWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	RateX=RateY=0;
}

bool	GUICmdMsgGerberExtendWithCenter::Save(QIODevice *f)
{
	if(::Save(f,RateX)==false)
		return false;
	if(::Save(f,RateY)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgGerberExtendWithCenter::Load(QIODevice *f)
{
	if(::Load(f,RateX)==false)
		return false;
	if(::Load(f,RateY)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgGerberExtendWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");

		MsgGerberExtend	MCmd(this);
		MCmd.RateX=RateX;
		MCmd.RateY=RateY;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}

//==========================================================================================
GUICmdMsgGerberRotateWithCenter::GUICmdMsgGerberRotateWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgGerberRotateWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgGerberRotateWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgGerberRotateWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		MsgGerberRotate	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}
//==========================================================================================
GUICmdMsgGerberSlopeXWithCenter::GUICmdMsgGerberSlopeXWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgGerberSlopeXWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgGerberSlopeXWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgGerberSlopeXWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		MsgGerberSlopeX	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}
//==========================================================================================
GUICmdMsgGerberSlopeYWithCenter::GUICmdMsgGerberSlopeYWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Radian=0;
}

bool	GUICmdMsgGerberSlopeYWithCenter::Save(QIODevice *f)
{
	if(::Save(f,Radian)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	GUICmdMsgGerberSlopeYWithCenter::Load(QIODevice *f)
{
	if(::Load(f,Radian)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}

void	GUICmdMsgGerberSlopeYWithCenter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		MsgGerberSlopeY	MCmd(this);
		MCmd.Radian	=Radian;
		MCmd.Cx=Cx;
		MCmd.Cy=Cy;
		Base->TransmitDirectly(&MCmd);		
	}
}

//==========================================================================================
GUICmdMsgGerberPaste::GUICmdMsgGerberPaste(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMsgGerberPaste::Save(QIODevice *f)
{
	if(::Save(f,index)==false)
		return false;
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;
	return true;
}
bool	GUICmdMsgGerberPaste::Load(QIODevice *f)
{
	if(::Load(f,index)==false)
		return false;
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	return true;
}

void	GUICmdMsgGerberPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		if(Base==NULL)
			return;
		MsgGerberPaste	Cmd(this);
		Cmd.index=index;
		Cmd.x=x;
		Cmd.y=y;
		Base->TransmitDirectly(&Cmd);
	}
}

//==========================================================================================
GUICmdGerberDrawWithPoints::GUICmdGerberDrawWithPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGerberDrawWithPoints::Save(QIODevice *f)
{
	if(Dots.Save(f)==false)
		return false;
	return true;
}
bool	GUICmdGerberDrawWithPoints::Load(QIODevice *f)
{
	if(Dots.Load(f)==false)
		return false;
	return true;
}

void	GUICmdGerberDrawWithPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		CmdGerberDrawWithPoints	CmdDots(this);
		CmdDots.Dots=Dots;
		if(CmdDots.Dots.GetNumber()==0)
			return;
		AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");
		if(Base!=NULL){
			Base->TransmitDirectly(&CmdDots);
		}
	}
}

//==========================================================================================

GUICmdSelectItemsGerberFast::GUICmdSelectItemsGerberFast(LayersBase *Base ,const QString &EmitterRoot ,const QString &EmitterName,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MultiSelect=false;
}
bool	GUICmdSelectItemsGerberFast::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(ButtonsToOperateLayer.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItemsGerberFast::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(ButtonsToOperateLayer.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItemsGerberFast::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"GerberFast");

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
		if(Ap!=NULL){
			CmdSelectItemsGerberFast	Cmd(GetLayersBase());
			Cmd.Area					=Area;
			Cmd.ButtonsToOperateLayer	=ButtonsToOperateLayer;
			Ap->TransmitDirectly(&Cmd);
		}
	}
	
	SendAck(localPage);
}
