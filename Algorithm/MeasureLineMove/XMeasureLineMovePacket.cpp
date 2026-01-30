/*
 * Copyright (C) 2022
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

#include "XMeasureLineMovePacket.h"
#include "XGeneralFunc.h"
#include "XMeasureLineMove.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//================================================================================
SlaveCommReqPosition::SlaveCommReqPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqPosition::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,DrawPoint)==false)
		return false;
	return true;
}
bool	SlaveCommReqPosition::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,DrawPoint)==false)
		return false;
	return true;
}

void	SlaveCommReqPosition::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckPosition	*S
	=(SlaveCommAckPosition *)((GetSendBackPacket()==NULL)?new SlaveCommAckPosition(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmItemRoot	*Item=Pg->SearchIDItem(ItemID);
			if(Item!=NULL){
				MeasureCommon	*m=dynamic_cast<MeasureCommon *>(Item);
				if(m!=NULL){
					m->GetDrawPoint(DrawPoint,S->MasterLocalX,S->MasterLocalY);
					S->Found=true;
				}
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckPosition::SlaveCommAckPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	Found=false;
}

bool	SlaveCommAckPosition::Load(QIODevice *f)
{
	if(::Load(f,MasterLocalX)==false)
		return false;
	if(::Load(f,MasterLocalY)==false)
		return false;
	if(::Load(f,Found)==false)
		return false;
	return true;
}
bool	SlaveCommAckPosition::Save(QIODevice *f)
{
	if(::Save(f,MasterLocalX)==false)
		return false;
	if(::Save(f,MasterLocalY)==false)
		return false;
	if(::Save(f,Found)==false)
		return false;
	return true;
}
//================================================================================
SlaveCommReqResultPosition::SlaveCommReqResultPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqResultPosition::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,DrawPoint)==false)
		return false;
	return true;
}
bool	SlaveCommReqResultPosition::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,DrawPoint)==false)
		return false;
	return true;
}

void	SlaveCommReqResultPosition::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckResultPosition	*S
	=(SlaveCommAckResultPosition *)((GetSendBackPacket()==NULL)?new SlaveCommAckResultPosition(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmItemRoot	*Item=Pg->SearchIDItem(ItemID);
			if(Item!=NULL){
				MeasureCommon	*m=dynamic_cast<MeasureCommon *>(Item);
				if(m!=NULL){
					m->GetDrawPoint(DrawPoint,S->MasterLocalX,S->MasterLocalY);
					m->GetShiftVector(S->ShiftX, S->ShiftY);
					S->CalcDone	=Item->IsCalcDone();
					S->Found=true;
				}
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckResultPosition::SlaveCommAckResultPosition(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	Found=false;
	CalcDone=false;
}

bool	SlaveCommAckResultPosition::Load(QIODevice *f)
{
	if(::Load(f,MasterLocalX)==false)
		return false;
	if(::Load(f,MasterLocalY)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,Found)==false)
		return false;
	if(::Load(f,CalcDone)==false)
		return false;
	return true;
}
bool	SlaveCommAckResultPosition::Save(QIODevice *f)
{
	if(::Save(f,MasterLocalX)==false)
		return false;
	if(::Save(f,MasterLocalY)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,Found)==false)
		return false;
	if(::Save(f,CalcDone)==false)
		return false;
	return true;
}

//================================================================================

GUICmdReqConvertUnitPixel::GUICmdReqConvertUnitPixel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqConvertUnitPixel::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,PixelToUnit)==false)
		return false;
	if(::Load(f,Value)==false)
		return false;

	return true;
}
bool	GUICmdReqConvertUnitPixel::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,PixelToUnit)==false)
		return false;
	if(::Save(f,Value)==false)
		return false;

	return true;
}

void	GUICmdReqConvertUnitPixel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckConvertUnitPixel	*SendBack=GetSendBack(GUICmdAckConvertUnitPixel,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureLineMoveBase *BBase=(MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			MeasureLineMoveDistanceItem	*Item=dynamic_cast<MeasureLineMoveDistanceItem *>(PData->SearchIDItem(ItemID));
			if(Item!=NULL){
				if(PixelToUnit==true){
					SendBack->Value=Item->TrasnformUnitFromPixel(Value);
				}
				else{
					SendBack->Value=Item->TransformPixelFromUnit(Value);
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckConvertUnitPixel::GUICmdAckConvertUnitPixel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckConvertUnitPixel::Load(QIODevice *f)
{
	if(::Load(f,Value)==false)
		return false;
	return true;
}
bool	GUICmdAckConvertUnitPixel::Save(QIODevice *f)
{
	if(::Save(f,Value)==false)
		return false;
	return true;
}