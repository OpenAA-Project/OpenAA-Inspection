/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "PropertyAlignmentPacket.h"
#include "XGeneralFunc.h"
#include "XAlignment.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"


//==============================================================================================

GUICmdReqAlignmentAreaList::GUICmdReqAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentAreaList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqAlignmentAreaList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqAlignmentAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentAreaList	*SendBack=GetSendBack(GUICmdSendAlignmentAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentAreaList::GUICmdSendAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentAreaList::MakeAreaList(int localPage,LayersBase *PBase)
{
	//int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlgorithmInPageRoot	*PData=AlignBase->GetPageData(localPage);
	if(PData!=NULL){
		for(int layer=0;layer<AlignBase->GetLayerNumb(localPage);layer++){
			AlgorithmInLayerRoot *PLayer=PData->GetLayerData(layer);

			CmdSetAlignmentAreaList	Cmd(GetLayersBase());
			Cmd.Area = &Area;
			PLayer->TransmitDirectly(&Cmd);
		}
	}
}
bool	GUICmdSendAlignmentAreaList::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentAreaList::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================
GUICmdReqAlignmentPointList::GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentPointList	*SendBack=GetSendBack(GUICmdSendAlignmentPointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakePointList(GetLayersBase(),Layer ,Number);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentPointList::GUICmdSendAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentPointList::MakePointList(LayersBase *PBase ,int Layer ,int Number)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	Points.RemoveAll();
	AlgorithmInPageRoot	*PData=AlignBase->GetPageData(LocalPage);
	if(PData!=NULL){
		AlgorithmInLayerRoot *PLayer=PData->GetLayerData(Layer);

		CmdSetAlignmentPointList	Cmd(GetLayersBase());
		Cmd.Number = Number;
		Cmd.Points = &Points;
		PLayer->TransmitDirectly(&Cmd);
	}
}
bool	GUICmdSendAlignmentPointList::Load(QIODevice *f)
{
	if(Points.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentPointList::Save(QIODevice *f)
{
	if(Points.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//==============================================================================
GUICmdReqAlignmentPutArea::GUICmdReqAlignmentPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(Area.Read(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqAlignmentPutArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(Area.Write(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPutArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot *AL=AP->GetLayerData(Layer);
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=static_cast<AlignmentInLayer *>(AL);

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(localPage));
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ImageControlTools" ,/**/"AlignmentTools");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
		}
	AddAlignmentAreaPacket	DPacket(this);
	DPacket.Number		=AInL->Areas.GetNumber();
	DPacket.Area		=Area;
	DPacket.AreaName	=AreaName;
	DPacket.Layer		=Layer;
	DPacket.LimitedLib	=LimitedLib;
	DPacket.Page		=localPage;
	DPacket.Priority	=Priority;
	AInL->TransmitDirectly(&DPacket);

	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(EmitterRoot,EmitterName,Ret,10);
	if(N!=NULL){
		CmdAddArea	Cmd(this);
		Ret[0]->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdReqAlignmentPutPoint::GUICmdReqAlignmentPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDot)==false)
		return false;
    if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	if(PointArea.Read(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPutPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDot)==false)
		return false;
    if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	if(PointArea.Write(f)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPutPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot *AL=AP->GetLayerData(Layer);
	if(AL==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentPointPacket	DPacket(this);
	DPacket.Area				=PointArea;
	DPacket.AreaID				=AreaID;
	DPacket.MoveDot				=MoveDot;		
    DPacket.Threshold			=Threshold;
	DPacket.AlignmentOnOutline	=AlignmentOnOutline;
	AL->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentModifyPoint::GUICmdReqAlignmentModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentModifyPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDot)==false)
		return false;
    if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentModifyPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDot)==false)
		return false;
    if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentModifyPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot *AL=AP->GetLayerData(Layer);
	if(AL==NULL)
		return;

	ModifyAlignmentPointPacket	DPacket(this);
	DPacket.AreaID				=AreaID;
	DPacket.ItemID				=ItemID;
	DPacket.MoveDot				=MoveDot;		
    DPacket.Threshold			=Threshold;
	DPacket.AlignmentOnOutline	=AlignmentOnOutline;	//�֊s�ňʒu���킹�����Ƃ�true
	AL->TransmitDirectly(&DPacket);
}
//==============================================================================

GUICmdReqAlignmentPutGroup::GUICmdReqAlignmentPutGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutGroup::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(GroupArea.Read(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPutGroup::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(GroupArea.Write(f)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPutGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot *AL=AP->GetLayerData(Layer);
	if(AL==NULL)
		return;

	AddAlignmentGroupPacket	DPacket(this);
	DPacket.Area				=GroupArea;
	DPacket.AreaID				=AreaID;
	DPacket.GroupNumber			=GroupNumber;
	AL->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentAreaInfo::GUICmdReqAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentAreaInfo	*SendBack=GetSendBack(GUICmdSendAlignmentAreaInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,Layer,AreaID,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentAreaInfo::GUICmdSendAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=-1;
	AreaID=-1;
}

void	GUICmdSendAlignmentAreaInfo::Make(int localPage,int layer,int areaID,LayersBase *Base)
{
	AlgorithmBase	*AlignBase=Base->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot *AL=AP->GetLayerData(layer);
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=static_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	for(XAlignmentArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID){
			Layer=layer;
			AreaID		=a->AreaID;
			Area		=a->Area;
			AreaName	=a->AreaName;
			LimitedLib	=a->LimitedLib;
			Priority	=a->Priority;
			return;
		}
	}
}
bool	GUICmdSendAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdSendAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================

GUICmdReqModifyAlignmentAreaInfo::GUICmdReqModifyAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqModifyAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	if(::Load(f,DeleteMode)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqModifyAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	if(::Save(f,DeleteMode)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}
void	GUICmdReqModifyAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;
	AlgorithmInLayerRoot	*AL=AP->GetLayerData(Layer);
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=static_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	if(DeleteMode==false){
		for(XAlignmentArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AreaID){
				a->Area			=Area	;
				a->AreaName		=AreaName;
				a->LimitedLib	=LimitedLib;
				a->Priority		=Priority;
				return;
			}
		}
	}
	else{
		RemoveAlignmentAreaPacket	Cmd(this);
		Cmd.AreaID=AreaID;
		AInL->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdSetActiveAreas::GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetActiveAreas::Load(QIODevice *f)
{
	if(ActiveAreas.Load(f)==false){
		return false;
	}
	if(::Load(f,InstForm)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetActiveAreas::Save(QIODevice *f)
{
	if(ActiveAreas.Save(f)==false){
		return false;
	}
	if(::Save(f,InstForm)==false){
		return false;
	}
	return true;
}

void	GUICmdSetActiveAreas::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstForm);
	if(L!=NULL){
		CmdSetActiveAreas	Cmd(this);
		Cmd.ActiveAreas=ActiveAreas;
		L->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//==============================================================================

GUICmdClickAreaButton::GUICmdClickAreaButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickAreaButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickAreaButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickAreaButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}

//==============================================================================

GUICmdClickPointButton::GUICmdClickPointButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickPointButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickPointButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickPointButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}

//==============================================================================

GUICmdClickGroupButton::GUICmdClickGroupButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickGroupButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickGroupButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickGroupButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}
