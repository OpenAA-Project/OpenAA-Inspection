/*
 * Copyright (C) 2023
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

#include "AlignmentLargeImagePanelResource.h"

#include "AlignmentLargeImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "AlignmentLargeImagePropertyPacket.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentLarge.h"
#include "ImagePanelTools.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
AlignmentLargeImagePanel::AlignmentLargeImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AlignmentLarge",QString(sRoot),QString(sName),__Master,parent)
{
	HasBitbuffData=false;
}

AlignmentLargeImagePanel::~AlignmentLargeImagePanel(void)
{
}


void	AlignmentLargeImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	if(GetParamGlobal()->AllocBitBuffer==false)
		ChangeDisplayType(__BitBuff);
}

void	AlignmentLargeImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*AlignmentLargeImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqAlignmentLargeDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}

	AlignmentLargeDrawAttr	*A=new AlignmentLargeDrawAttr();
	A->AList		=DrawMode.AList;
	A->DrawKind		=DrawMode.Mode;
	A->AngleRadian	=DrawMode.AngleRadian;
	return A;
}

void	AlignmentLargeImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentLargeDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.MultiSelect=GetMultiSelect();
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentLargeImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentLargeReflectChangeItems	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentLargeImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();

	HasBitbuffData=false;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeCheckBitBuff	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckAlignmentLargeCheckBitBuff	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true){
			if(ACmd.HasData==true){
				HasBitbuffData=true;
			}
		}
	}
	GUIFormBase	*f=GetLayersBase()->FindByName(ImageControlToolsName);
	if(f!=NULL){
		CmdSetBitBuffMode	RCmd(GetLayersBase());
		RCmd.BitBuffMode=HasBitbuffData;
		f->TransmitDirectly(&RCmd);
		CmdReqImageLayer	DModeCmd(GetLayersBase(),GetLayerNumb());
		f->TransmitDirectly(&DModeCmd);
		ChangeDisplayType(DModeCmd.DType);
		Repaint();
	}

}

void	AlignmentLargeImagePanel::CanvasSlotOnPaint(QPainter &pnt)
{
	if(GetDisplayType()==DisplayImage::__BitBuff){
		AlgorithmBase	*A=GetAlgorithmBase();
		AlignmentLargeBase	*Ab=dynamic_cast<AlignmentLargeBase *>(A);
		if(Ab!=NULL){
			//SetTransparentLevelInBitBuff(Ab->TransparentLevelInBitBuff);
		}
	}
	DisplayImageWithAlgorithm::CanvasSlotOnPaint(pnt);
}

void	AlignmentLargeImagePanel::MultiSelectBtnDown()
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		CmdSetMultiSelectAlignmentLarge	Da(GetLayersBase());
		Da.MultiSelect	=GetMultiSelect();
		GProp->TransmitDirectly(&Da);
	}
	DisplayImageWithAlgorithm::MultiSelectBtnDown();
}

void	AlignmentLargeImagePanel::SelectArea(IntList &LayerList, FlexArea &Area)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectItemsAlignmentLarge	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
		if(GProp!=NULL){
			CmdReqAlignmentLargeSelectedAreaID	RCmd(GetLayersBase());
			RCmd.Page=page;
			GProp->TransmitDirectly(&RCmd);
			hCmd.AreaIDList=RCmd.AreaIDList;
		}
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :SelectArea",ErrorCodeList::_Alart);
			}
		}
	}
}
void	AlignmentLargeImagePanel::ExeCutItems(FlexArea &Area)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Cut items");
                             
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCutItemsAlignmentLarge	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
		if(GProp!=NULL){
			CmdReqAlignmentLargeSelectedAreaID	RCmd(GetLayersBase());
			RCmd.Page=page;
			GProp->TransmitDirectly(&RCmd);
			hCmd.AreaIDList=RCmd.AreaIDList;
		}
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ExeCutItems",ErrorCodeList::_Alart);
			}
		}
	}
}

//=========================================================

GUICmdReqAlignmentLargeCheckBitBuff::GUICmdReqAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentLargeCheckBitBuff::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentLargeCheckBitBuff	*SendBack=GetSendBack(GUICmdAckAlignmentLargeCheckBitBuff,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		if(GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer)->HasDataInBitBuff()==true){
			SendBack->HasData=true;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentLargeCheckBitBuff::GUICmdAckAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	HasData=false;
}

bool	GUICmdAckAlignmentLargeCheckBitBuff::Load(QIODevice *f)
{
	if(::Load(f,HasData)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentLargeCheckBitBuff::Save(QIODevice *f)
{
	if(::Save(f,HasData)==false)
		return false;
	return true;
}

//=======================================================================
GUICmdSelectItemsAlignmentLarge::GUICmdSelectItemsAlignmentLarge(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MultiSelect=false;
}
bool	GUICmdSelectItemsAlignmentLarge::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItemsAlignmentLarge::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItemsAlignmentLarge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		CmdSelectItemsAlignmentLarge	RCmd(GetLayersBase());
		RCmd.Area		=Area;
		RCmd.AreaIDList	=AreaIDList;
		Ap->TransmitDirectly(&RCmd);
	}
	SendAck(localPage);
}


//=======================================================================
GUICmdCutItemsAlignmentLarge::GUICmdCutItemsAlignmentLarge(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCutItemsAlignmentLarge::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdCutItemsAlignmentLarge::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdCutItemsAlignmentLarge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		CmdCutItemsAlignmentLarge	RCmd(GetLayersBase());
		RCmd.Area		=Area;
		RCmd.AreaIDList	=AreaIDList;
		Ap->TransmitDirectly(&RCmd);
	}

	SendAck(localPage);
}