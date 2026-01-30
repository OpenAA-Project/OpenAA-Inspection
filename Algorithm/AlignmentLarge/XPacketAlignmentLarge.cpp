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


#include "XPacketAlignmentLarge.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignmentLarge.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//==================================================================================

SlaveCommReqAlignmentLargePoint::SlaveCommReqAlignmentLargePoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	AreaID	=0;
	Layer	=0;
}

bool	SlaveCommReqAlignmentLargePoint::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentLargePoint::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentLargePoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentLargePoint	*S
	=(SlaveCommAckAlignmentLargePoint *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentLargePoint(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmInPagePLI	*aPg=(AlgorithmInPagePLI *)Pg;
			AlgorithmInLayerPLI *aLy=aPg->GetLayerDataPLI(Layer);
			if(aLy!=NULL){
				CmdReqAlignmentLargePointPacket	Cmd(GetLayersBase());
				Cmd.AreaID		=AreaID;
				Cmd.AreaName	=AreaName;
				aLy->TransmitDirectly(&Cmd);
				S->AlignmentLargePointData=Cmd.AlignmentLargePointData;
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}



SlaveCommAckAlignmentLargePoint::SlaveCommAckAlignmentLargePoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentLargePoint::Load(QIODevice *f)
{
	if(AlignmentLargePointData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentLargePoint::Save(QIODevice *f)
{
	if(AlignmentLargePointData.Save(f)==false)
		return false;
	return true;
}

//===================================================================================================
SlaveCommReqAlignmentLargeShift::SlaveCommReqAlignmentLargeShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	Layer=0;
}
bool	SlaveCommReqAlignmentLargeShift::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(ItemID.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentLargeShift::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(ItemID.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentLargeShift::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentLargeShift	*S
	=(SlaveCommAckAlignmentLargeShift *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentLargeShift(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmInPagePLI	*aPg=(AlgorithmInPagePLI *)Pg;
			AlgorithmInLayerPLI *aLy=aPg->GetLayerDataPLI(Layer);
			if(aLy!=NULL){
				CmdReqAlignmentLargeShiftPacket	Cmd(GetLayersBase());
				Cmd.ItemIDPoint		=&ItemID;
				Cmd.ShiftDataPoint	=&S->ShiftData;
				aLy->TransmitDirectly(&Cmd);
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckAlignmentLargeShift::SlaveCommAckAlignmentLargeShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentLargeShift::Load(QIODevice *f)
{
	if(ShiftData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentLargeShift::Save(QIODevice *f)
{
	if(ShiftData.Save(f)==false)
		return false;
	return true;
}