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


#include "XPacketAlignment.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignment.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


bool	AlignmentShiftList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CalcDone)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,MasterX)==false)
		return false;
	if(::Save(f,MasterY)==false)
		return false;
	return true;
}

bool	AlignmentShiftList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CalcDone)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,MasterX)==false)
		return false;
	if(::Load(f,MasterY)==false)
		return false;
	return true;
}

ReqAlignmentAreaList	&ReqAlignmentAreaList::operator=(ReqAlignmentAreaList &src)
{
	AreaID		=src.AreaID;
	GlobalPage	=src.GlobalPage;
	Layer		=src.Layer;
	return *this;
}
bool	ReqAlignmentAreaList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}
bool	ReqAlignmentAreaList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

//==================================================================================
ReqAlignmentAreaListPack &ReqAlignmentAreaListPack::operator=(ReqAlignmentAreaListPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
ReqAlignmentAreaListPack &ReqAlignmentAreaListPack::operator+=(ReqAlignmentAreaListPack &src)
{
	for(ReqAlignmentAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReqAlignmentAreaList *b=new ReqAlignmentAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	ReqAlignmentAreaListPack::LayerExists(int page ,int layer)
{
	for(ReqAlignmentAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page && a->Layer==layer)
			return true;
	}
	return false;
}

bool	ReqAlignmentAreaListPack::ExistsAreaID(int areaID)
{
	for(ReqAlignmentAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID)
			return true;
	}
	return false;
}
bool	ReqAlignmentAreaListPack::Exists(int page ,int layer,int areaID)
{
	for(ReqAlignmentAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page && a->Layer==layer && a->AreaID==areaID)
			return true;
	}
	return false;
}
bool	ReqAlignmentAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ReqAlignmentAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	ReqAlignmentAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		ReqAlignmentAreaList *a=new ReqAlignmentAreaList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//==================================================================================
bool	AlignmentDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&DrawKind,sizeof(DrawKind))!=sizeof(DrawKind))
		return false;
	if(f->write((const char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;
	if(AList.Save(f)==false)
		return false;
	return true;
}
bool	AlignmentDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&DrawKind,sizeof(DrawKind))!=sizeof(DrawKind))
		return false;
	if(f->read((char *)&DrawMode,sizeof(DrawMode))!=sizeof(DrawMode))
		return false;
	if(AList.Load(f)==false)
		return false;
	return true;
}

//==================================================================================

SlaveCommReqAlignmentPoint::SlaveCommReqAlignmentPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}

bool	SlaveCommReqAlignmentPoint::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentPoint::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentPoint	*S
	=(SlaveCommAckAlignmentPoint *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentPoint(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmInPagePLI	*aPg=(AlgorithmInPagePLI *)Pg;
			AlgorithmInLayerPLI *aLy=aPg->GetLayerDataPLI(Layer);
			if(aLy!=NULL){
				CmdReqAlignmentPointPacket	Cmd(GetLayersBase());
				Cmd.AreaID		=AreaID;
				Cmd.AreaName	=AreaName;
				aLy->TransmitDirectly(&Cmd);
				S->AlignmentPointData=Cmd.AlignmentPointData;
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}



SlaveCommAckAlignmentPoint::SlaveCommAckAlignmentPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentPoint::Load(QIODevice *f)
{
	if(AlignmentPointData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentPoint::Save(QIODevice *f)
{
	if(AlignmentPointData.Save(f)==false)
		return false;
	return true;
}

//===================================================================================================
SlaveCommReqAlignmentShift::SlaveCommReqAlignmentShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommReqAlignmentShift::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(ItemID.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentShift::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(ItemID.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentShift::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentShift	*S
	=(SlaveCommAckAlignmentShift *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentShift(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmInPagePLI	*aPg=(AlgorithmInPagePLI *)Pg;
			AlgorithmInLayerPLI *aLy=aPg->GetLayerDataPLI(Layer);
			if(aLy!=NULL){
				CmdReqAlignmentShiftPacket	Cmd(GetLayersBase());
				Cmd.ItemIDPoint		=&ItemID;
				Cmd.ShiftDataPoint	=&S->ShiftData;
				aLy->TransmitDirectly(&Cmd);
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckAlignmentShift::SlaveCommAckAlignmentShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentShift::Load(QIODevice *f)
{
	if(ShiftData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentShift::Save(QIODevice *f)
{
	if(ShiftData.Save(f)==false)
		return false;
	return true;
}