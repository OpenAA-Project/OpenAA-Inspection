/*
 * Copyright (C) 2024
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


#include "XTreeMasterPacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>
#include "XTreeMaster.h"

//==========================================================================================
GUICmdAddTreeMaster::GUICmdAddTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddTreeMaster::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	return true;
}
bool	GUICmdAddTreeMaster::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	return true;
}

void	GUICmdAddTreeMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAddTreeMasterItemPacket	Cmd(GetLayersBase());
	Cmd.TMItemID	=TMItemID;
	Cmd.CatName		=CatName;
	Cmd.MasterCode	=MasterCode;
	Cmd.MasterName = MasterName;

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================
GUICmdSetAlertTreeMaster::GUICmdSetAlertTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	TMItemID	=0;
	MasterCode	=0;
	AlertMark	=false;
}

bool	GUICmdSetAlertTreeMaster::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,AlertMark)==false)
		return false;
	return true;
}

bool	GUICmdSetAlertTreeMaster::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,AlertMark)==false)
		return false;
	return true;
}

void	GUICmdSetAlertTreeMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSetAlertTreeMaster	Cmd(GetLayersBase());
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	Cmd.TMItemID	=TMItemID;
	Cmd.MasterCode	=MasterCode;
	Cmd.AlertMark	=AlertMark;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================
GUICmdReqMaxTMItemID::GUICmdReqMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMaxTMItemID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMaxTMItemID	*SendBack=GetSendBack(GUICmdAckMaxTMItemID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	CmdReqMaxTMItemIDPacket	Cmd(GetLayersBase());
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
	SendBack->TMItemID	=	Cmd.MaxTMItemID;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMaxTMItemID::GUICmdAckMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	TMItemID=0;
}

bool	GUICmdAckMaxTMItemID::Load(QIODevice *f)
{
	if(::Load(f,TMItemID)==false)
		return false;
	return true;
}

bool	GUICmdAckMaxTMItemID::Save(QIODevice *f)
{
	if(::Save(f,TMItemID)==false)
		return false;
	return true;
}

GUICmdCopyTreeMasterItem::GUICmdCopyTreeMasterItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdCopyTreeMasterItem::Load(QIODevice *f)
{
	if(::Load(f,MasterSrc)==false)
		return false;
	if(::Load(f,MasterDst)==false)
		return false;
	return true;
}

bool GUICmdCopyTreeMasterItem::Save(QIODevice *f)
{
	if(::Save(f,MasterSrc)==false)
		return false;
	if(::Save(f,MasterDst)==false)
		return false;
	return true;
}

void	GUICmdCopyTreeMasterItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdCopyTreeMasterItemPacket	Cmd(GetLayersBase());
	Cmd.MasterSrc = MasterSrc;
	Cmd.MasterDst = MasterDst;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(Base==NULL)
		return;
	Base->TransmitDirectly(&Cmd);
}

GUICmdSetCategoryName::GUICmdSetCategoryName(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdSetCategoryName::Load(QIODevice *f)
{
	if(::Load(f,CatName)==false)
		return false;
	return true;
}

bool GUICmdSetCategoryName::Save(QIODevice *f)
{
	if(::Save(f,CatName)==false)
		return false;
	return true;
}

void	GUICmdSetCategoryName::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSetCategoryNamePacket	Cmd(GetLayersBase());
	Cmd.CatName = CatName;
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

GUICmdRemoveItem::GUICmdRemoveItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdRemoveItem::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool GUICmdRemoveItem::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void GUICmdRemoveItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdRemoveItemPacket	Cmd(GetLayersBase());
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================

GUICmdSelectItem::GUICmdSelectItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),globalPage)
{
}

bool GUICmdSelectItem::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool GUICmdSelectItem::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void GUICmdSelectItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSelectItemPacket	Cmd(GetLayersBase());
	Cmd.MasterCode = MasterCode;

	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	AlgorithmInPageRoot		*PData=Base->GetPageData(localPage);
	if(PData==NULL)
		return;
	PData->TransmitDirectly(&Cmd);
}


//===========================================================================

GUICmdAddTreeMasterArea::GUICmdAddTreeMasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddTreeMasterArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,TreeMasterColor)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;
	if(::Load(f,Selection)==false)
		return false;
	if(::Load(f,ThreShape)==false)
		return false;
	if(::Load(f,ThreColor)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;

	return true;
}
bool	GUICmdAddTreeMasterArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,TreeMasterColor)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;
	if(::Save(f,Selection)==false)
		return false;
	if(::Save(f,ThreShape)==false)
		return false;
	if(::Save(f,ThreColor)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;

	return true;
}

void	GUICmdAddTreeMasterArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CmdAddItemAreaPacket	Cmd(GetLayersBase());
	Cmd.TMItemID		=TMItemID;
	Cmd.Area			=Area;
	Cmd.MasterCode		=MasterCode;
	Cmd.TreeMasterColor	=TreeMasterColor;
	Cmd.CatName			=CatName;
	Cmd.MasterName		=MasterName;
	Cmd.Selection		=Selection;
	Cmd.ThreShape		=ThreShape;
	Cmd.ThreColor		=ThreColor;
	Cmd.SearchDot		=SearchDot;

	PData->TransmitDirectly(&Cmd);
}

//===========================================================================

GUICmdReqTreeMasterList::GUICmdReqTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqTreeMasterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTreeMasterList	*SendBack=GetSendBack(GUICmdSendTreeMasterList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeTreeMasterList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//===========================================================================
GUICmdSendTreeMasterList::GUICmdSendTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTreeMasterList::Load(QIODevice *f)
{
	if(TreeMasterInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendTreeMasterList::Save(QIODevice *f)
{
	if(TreeMasterInfo.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendTreeMasterList::MakeTreeMasterList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Classify" ,/**/"TreeMaster");
	if(ABase==NULL)
		return;
	TreeMasterInfo.RemoveAll();

	AlgorithmInPageRoot	*PData=ABase->GetPageData(localPage);
	if(PData!=NULL){
		CmdMakeTreeMasterList	Cmd(GetLayersBase());
		Cmd.TreeMasterInfo = &TreeMasterInfo;
		PData->TransmitDirectly(&Cmd);
	}
}
void	GUICmdSendTreeMasterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{}


//========================================================================================

GUICmdReqLoadMasterImage::GUICmdReqLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLoadMasterImage::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}

bool	GUICmdReqLoadMasterImage::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

void	GUICmdReqLoadMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	QString	ImageFileName=Pg->GetImageFile(MasterCode, GetLayersBase()->GetMachineID());

	QFile	ImageFile(ImageFileName);
	ImageFile.open(QIODevice::ReadOnly);
	for(int LNumb=0;LNumb<GetLayerNumb(localPage);LNumb++){

		GetLayersBase()->StepProcessing(localPage);
		DataInLayer	*L=Pg->GetLayerData(LNumb);
		if(GetParamGlobal()->NoLoadSaveMasterImage==false){
			if(L->GetMasterBuff().Load(&ImageFile,false)==false){
				goto	QEnd;
			}
			L->GetMasterBuff().SetChanged(false);
			ImageBuffer	Dummy;
			if(Dummy.Load(&ImageFile)==false){
				goto	QEnd;
			}
			if(Dummy.Load(&ImageFile)==false){
				goto	QEnd;
			}
			GetParamGlobal()->IsLoadedMasterImageSuccessful=true;
		}
		else{
			GetParamGlobal()->IsLoadedMasterImageSuccessful=false;
		}
	}
	QEnd:;
}