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


#include "XPropertyMaskingPacket.h"
#include "XGeneralFunc.h"
#include "XMasking.h"

GUICmdAddMaskingArea::GUICmdAddMaskingArea(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdAddMaskingArea::Load(QIODevice* f)
{
	if (MaskArea.Load(f) == false)
		return false;
	if (LayerList.Load(f) == false)
		return false;
	if (::Load(f, Effective) == false)
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	return true;
}
bool	GUICmdAddMaskingArea::Save(QIODevice* f)
{
	if (MaskArea.Save(f) == false)
		return false;
	if (LayerList.Save(f) == false)
		return false;
	if (::Save(f, Effective) == false)
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	return true;
}

void	GUICmdAddMaskingArea::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* L = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (L == NULL)
		return;
	AlgorithmInPageRoot* PData = L->GetPageData(localPage);
	if (PData == NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	AddMaskingAreaPacket	Cmd(this);
	Cmd.Area = MaskArea;
	Cmd.LayerList = LayerList;
	Cmd.Effective = Effective;
	Cmd.LimitedLib = LimitedLib;

	PData->TransmitDirectly(&Cmd);

	SendAck(localPage);
}
GUICmdAddMaskingLine::GUICmdAddMaskingLine(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	Vector = NULL;
}
bool	GUICmdAddMaskingLine::Load(QIODevice* f)
{
	int	VectorId;
	if (::Load(f, VectorId) == false) {
		return false;
	}
	if (Vector != NULL) {
		delete	Vector;
	}
	Vector = VectorLineBase::Create(VectorId);

	if (Vector->Load(f) == false) {
		return false;
	}
	if (LayerList.Load(f) == false) {
		return false;
	}
	return true;
}
bool	GUICmdAddMaskingLine::Save(QIODevice* f)
{
	int	VectorId = Vector->GetID();
	if (::Save(f, VectorId) == false) {
		return false;
	}

	if (Vector->Save(f) == false) {
		return false;
	}
	if (LayerList.Save(f) == false) {
		return false;
	}
	return true;
}

void	GUICmdAddMaskingLine::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* L = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (L == NULL)
		return;
	AlgorithmInPageRoot* PData = L->GetPageData(localPage);
	if (PData == NULL)
		return;
	AddMaskingLinePacket	Cmd(this);
	Cmd.Vector = Vector;
	Cmd.LayerList = LayerList;
	PData->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

GUICmdChangeMaskingAttr::GUICmdChangeMaskingAttr(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdChangeMaskingAttr::Load(QIODevice* f)
{
	if (::Load(f, ItemID) == false)
		return false;
	if (::Load(f, GlobalPage) == false)
		return false;
	if (::Load(f, Layer) == false)
		return false;
	if (::Load(f, Effective) == false)
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	return true;
}
bool	GUICmdChangeMaskingAttr::Save(QIODevice* f)
{
	if (::Save(f, ItemID) == false)
		return false;
	if (::Save(f, GlobalPage) == false)
		return false;
	if (::Save(f, Layer) == false)
		return false;
	if (::Save(f, Effective) == false)
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	return true;
}

void	GUICmdChangeMaskingAttr::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* L = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (L == NULL)
		return;
	AlgorithmInPageRoot* PData = L->GetPageData(localPage);
	if (PData == NULL)
		return;
	AlgorithmInLayerRoot* LData = PData->GetLayerData(Layer);
	if (LData == NULL)
		return;
	AlgorithmItemRoot* Item = LData->SearchIDItem(ItemID);
	if (Item == NULL)
		return;
	if(Item->GetItemClassType()!=0)
		return;

	MaskingItem* M = static_cast<MaskingItem*>(Item);
	M->GetThresholdW()->Effective = Effective;
	M->GetThresholdW()->SelAreaID = LimitedLib;

	SendAck(localPage);
}

//==============================================================================================

GUICmdReqMaskList::GUICmdReqMaskList(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	IneffectiveMode = false;
	EffectiveMode = false;
	IneffectiveLimitedMode = false;
	EffectiveLimitedMode = false;
}

bool	GUICmdReqMaskList::Load(QIODevice* f)
{
	if (::Load(f, IneffectiveMode) == false)
		return false;
	if (::Load(f, EffectiveMode) == false)
		return false;
	if (::Load(f, IneffectiveLimitedMode) == false)
		return false;
	if (::Load(f, EffectiveLimitedMode) == false)
		return false;
	return true;
}
bool	GUICmdReqMaskList::Save(QIODevice* f)
{
	if (::Save(f, IneffectiveMode) == false)
		return false;
	if (::Save(f, EffectiveMode) == false)
		return false;
	if (::Save(f, IneffectiveLimitedMode) == false)
		return false;
	if (::Save(f, EffectiveLimitedMode) == false)
		return false;
	return true;
}

void	GUICmdReqMaskList::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	GUICmdSendMaskList* SendBack = GetSendBack(GUICmdSendMaskList, GetLayersBase(), EmitterRoot, EmitterName, localPage);
	SendBack->MakeMaskList(EffectiveMode, IneffectiveMode, EffectiveLimitedMode, IneffectiveLimitedMode, localPage, GetLayersBase());
	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}

GUICmdSendMaskList::GUICmdSendMaskList(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

void	GUICmdSendMaskList::MakeMaskList(bool EffectiveMode, bool IneffectiveMode
	, bool EffectiveLimitedMode, bool IneffectiveLimitedMode
	, int localPage, LayersBase* PBase)
{
	AlgorithmBase* MaskingBase = PBase->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	MaskInfo.RemoveAll();

	AlgorithmInPageRoot* PData = MaskingBase->GetPageData(localPage);
	if (PData != NULL) {
		if (MaskingBase->GetLayerNumb(localPage) == 1) {
			MakeMaskListLayer1(MaskingBase
				,EffectiveMode, IneffectiveMode
				, EffectiveLimitedMode, IneffectiveLimitedMode
				, localPage, PBase);
		}
		else {
			MakeMaskListLayers(MaskingBase
				, EffectiveMode, IneffectiveMode
				, EffectiveLimitedMode, IneffectiveLimitedMode
				, localPage, PBase);
		}
	}
}

void	GUICmdSendMaskList::MakeMaskListLayer1(AlgorithmBase* MaskingBase
				,bool EffectiveMode, bool IneffectiveMode
				, bool EffectiveLimitedMode, bool IneffectiveLimitedMode
				, int localPage, LayersBase * PBase)
{
	AlgorithmInPageRoot* PData = MaskingBase->GetPageData(localPage);
	for (int layer = 0; layer < MaskingBase->GetLayerNumb(localPage); layer++) {
		AlgorithmInLayerRoot* PLayer = PData->GetLayerData(layer);

		CmdMakeMaskInfo	Cmd(GetLayersBase());
		Cmd.IneffectiveMode			=IneffectiveMode		;
		Cmd.EffectiveMode			=EffectiveMode			;
		Cmd.IneffectiveLimitedMode	=IneffectiveLimitedMode	;
		Cmd.EffectiveLimitedMode	=EffectiveLimitedMode	;
		Cmd.MaskInfo = &MaskInfo;
		PLayer->TransmitDirectly(&Cmd);
	}
}

void	GUICmdSendMaskList::MakeMaskListLayers(AlgorithmBase* MaskingBase
				,bool EffectiveMode, bool IneffectiveMode
				, bool EffectiveLimitedMode, bool IneffectiveLimitedMode
				, int localPage, LayersBase* PBase)
{
	AlgorithmInPageRoot* PData = MaskingBase->GetPageData(localPage);
	int	LayerCount = MaskingBase->GetLayerNumb(localPage);
	#pragma omp parallel for
	for (int layer = 0; layer < LayerCount; layer++) {
		MaskingListForPacketPack	iMaskInfo;
		AlgorithmInLayerRoot* PLayer = PData->GetLayerData(layer);

		CmdMakeMaskInfo	Cmd(GetLayersBase());
		Cmd.IneffectiveMode			=IneffectiveMode		;
		Cmd.EffectiveMode			=EffectiveMode			;
		Cmd.IneffectiveLimitedMode	=IneffectiveLimitedMode	;
		Cmd.EffectiveLimitedMode	=EffectiveLimitedMode	;
		Cmd.MaskInfo = &iMaskInfo;
		PLayer->TransmitDirectly(&Cmd);

		//
		//MaskingInLayer* MaskingLayer = dynamic_cast<MaskingInLayer*>(PLayer);
		//if (MaskingLayer != NULL) {
		//	int	ItemCount = MaskingLayer->GetItemCount();
		//	AlgorithmItemPLI** ItemDim = new AlgorithmItemPLI * [ItemCount];
		//	int	k = 0;
		//	for (AlgorithmItemPLI* item = MaskingLayer->GetFirstData(); item != NULL; item = item->GetNext()) {
		//		ItemDim[k] = item;
		//		k++;
		//	}
		//	for (int j = 0; j < ItemCount; j++) {
		//		MaskingItem* MItem = dynamic_cast<MaskingItem*>(ItemDim[j]);
		//		if (MItem != NULL
		//			&& ((EffectiveMode == true			&& MItem->GetThresholdR()->Effective == true  && ((MaskingThreshold*)MItem->GetThresholdR())->IsLimited() == false)
		//			 || (IneffectiveMode == true		&& MItem->GetThresholdR()->Effective == false && ((MaskingThreshold*)MItem->GetThresholdR())->IsLimited() == false)
		//			 || (EffectiveLimitedMode == true	&& MItem->GetThresholdR()->Effective == true  && ((MaskingThreshold*)MItem->GetThresholdR())->IsLimited() == true)
		//			 || (IneffectiveLimitedMode == true && MItem->GetThresholdR()->Effective == false && ((MaskingThreshold*)MItem->GetThresholdR())->IsLimited() == true))) {
		//			MaskingListForPacket* L = new MaskingListForPacket();
		//			L->Data.Page = PBase->GetGlobalPageFromLocal(localPage);
		//			L->Data.Layer = layer;
		//			L->Data.Effective = MItem->GetThresholdR()->Effective;
		//			int x1, y1, x2, y2;
		//			MItem->GetXY(x1, y1, x2, y2);
		//			L->Data.ItemID = MItem->GetID();
		//			L->Data.x1 = x1;
		//			L->Data.y1 = y1;
		//			L->Data.x2 = x2;
		//			L->Data.y2 = y2;
		//			L->LimitedLib = *((AlgorithmLibraryListContainer*)&MItem->GetThresholdR()->SelAreaID);
		//			iMaskInfo.AppendList(L);
		//		}
		//	}
		//	delete[]ItemDim;
		//}
		#pragma omp critical
		{
			MaskInfo += iMaskInfo;
		}
	}
}
bool	GUICmdSendMaskList::Load(QIODevice* f)
{
	if (MaskInfo.Load(f) == false)
		return false;
	return true;
}
bool	GUICmdSendMaskList::Save(QIODevice* f)
{
	if (MaskInfo.Save(f) == false)
		return false;
	return true;
}

void	GUICmdSendMaskList::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
}

//==============================================================================
GUICmdGenerateMaskInSameColor::GUICmdGenerateMaskInSameColor(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdGenerateMaskInSameColor::Load(QIODevice* f)
{
	if (::Load(f, PickupL) == false)
		return false;
	if (::Load(f, PickupH) == false)
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	if (::Load(f, Effective) == false)
		return false;
	if (LayerList.Load(f) == false)
		return false;
	if (PickupColor.Load(f) == false)
		return false;
	if (::Load(f, MinPickupSize) == false)
		return false;
	if (::Load(f, MaxPickupSize) == false)
		return false;
	if (::Load(f, MinPickupDots) == false)
		return false;
	if (::Load(f, MaxPickupDots) == false)
		return false;
	if (::Load(f, Erosion) == false)
		return false;
	if (::Load(f, TestMode) == false)
		return false;
	return true;
}
bool	GUICmdGenerateMaskInSameColor::Save(QIODevice* f)
{
	if (::Save(f, PickupL) == false)
		return false;
	if (::Save(f, PickupH) == false)
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	if (::Save(f, Effective) == false)
		return false;
	if (LayerList.Save(f) == false)
		return false;
	if (PickupColor.Save(f) == false)
		return false;
	if (::Save(f, MinPickupSize) == false)
		return false;
	if (::Save(f, MaxPickupSize) == false)
		return false;
	if (::Save(f, MinPickupDots) == false)
		return false;
	if (::Save(f, MaxPickupDots) == false)
		return false;
	if (::Save(f, Erosion) == false)
		return false;
	if (::Save(f, TestMode) == false)
		return false;
	return true;
}
void	GUICmdGenerateMaskInSameColor::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;

	CmdGenerateMaskInSameColor	Cmd(this);
	Cmd.PickupL = PickupL;
	Cmd.PickupH = PickupH;
	Cmd.LimitedLib = LimitedLib;
	Cmd.Effective = Effective;
	Cmd.PickupColor = PickupColor;
	Cmd.MinPickupSize = MinPickupSize;
	Cmd.MaxPickupSize = MaxPickupSize;
	Cmd.MinPickupDots = MinPickupDots;
	Cmd.MaxPickupDots = MaxPickupDots;
	Cmd.Erosion = Erosion;
	Cmd.LayerList = LayerList;
	Cmd.TestMode = TestMode;
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//==============================================================================
GUICmdReqSetButtonMode::GUICmdReqSetButtonMode(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	Mode = 0;
}

bool	GUICmdReqSetButtonMode::Load(QIODevice* f)
{
	if (::Load(f, Mode) == false) {
		return false;
	}
	if (::Load(f, InstForm) == false) {
		return false;
	}
	return true;
}
bool	GUICmdReqSetButtonMode::Save(QIODevice* f)
{
	if (::Save(f, Mode) == false) {
		return false;
	}
	if (::Save(f, InstForm) == false) {
		return false;
	}
	return true;
}

void	GUICmdReqSetButtonMode::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	GUIFormBase* L = GetLayersBase()->FindByName(EmitterRoot, EmitterName, InstForm);
	if (L != NULL) {
		CmdReqSetButtonMode	Cmd(this);
		Cmd.Mode = Mode;
		L->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdPourOnMouseLDown::GUICmdPourOnMouseLDown(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	MinSize=0;
	MinDots=0;
}

bool	GUICmdPourOnMouseLDown::Load(QIODevice* f)
{
	if (::Load(f, LocalX) == false)
		return false;
	if (::Load(f, LocalY) == false)
		return false;
	if (::Load(f, PickupRL) == false)
		return false;
	if (::Load(f, PickupRH) == false)
		return false;
	if (::Load(f, PickupGL) == false)
		return false;
	if (::Load(f, PickupGH) == false)
		return false;
	if (::Load(f, PickupBL) == false)
		return false;
	if (::Load(f, PickupBH) == false)
		return false;
	if (::Load(f, Effective) == false)
		return false;
	if (::Load(f, Exclusive) == false)
		return false;
	if (LayerList.Load(f) == false)
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	if (::Load(f, ExpandedDot) == false)
		return false;
	if (::Load(f, MinSize) == false)
		return false;
	if (::Load(f, MinDots) == false)
		return false;
	if (::Load(f, OmitX1) == false)
		return false;
	if (::Load(f, OmitY1) == false)
		return false;
	if (::Load(f, OmitX2) == false)
		return false;
	if (::Load(f, OmitY2) == false)
		return false;
	if (::Load(f, NoisePinhole) == false)
		return false;
	if (::Load(f, NoiseSmallDot) == false)
		return false;
	return true;
}
bool	GUICmdPourOnMouseLDown::Save(QIODevice* f)
{
	if (::Save(f, LocalX) == false)
		return false;
	if (::Save(f, LocalY) == false)
		return false;
	if (::Save(f, PickupRL) == false)
		return false;
	if (::Save(f, PickupRH) == false)
		return false;
	if (::Save(f, PickupGL) == false)
		return false;
	if (::Save(f, PickupGH) == false)
		return false;
	if (::Save(f, PickupBL) == false)
		return false;
	if (::Save(f, PickupBH) == false)
		return false;
	if (::Save(f, Effective) == false)
		return false;
	if (::Save(f, Exclusive) == false)
		return false;
	if (LayerList.Save(f) == false)
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	if (::Save(f, ExpandedDot) == false)
		return false;
	if (::Save(f, MinSize) == false)
		return false;
	if (::Save(f, MinDots) == false)
		return false;
	if (::Save(f, OmitX1) == false)
		return false;
	if (::Save(f, OmitY1) == false)
		return false;
	if (::Save(f, OmitX2) == false)
		return false;
	if (::Save(f, OmitY2) == false)
		return false;
	if (::Save(f, NoisePinhole) == false)
		return false;
	if (::Save(f, NoiseSmallDot) == false)
		return false;
	return true;
}

void	GUICmdPourOnMouseLDown::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;
	CmdPourAreaPacket	Cmd(this);
	Cmd.LayerList = LayerList;
	Cmd.PickupRL = PickupRL;
	Cmd.PickupRH = PickupRH;
	Cmd.PickupGL = PickupGL;
	Cmd.PickupGH = PickupGH;
	Cmd.PickupBL = PickupBL;
	Cmd.PickupBH = PickupBH;
	Cmd.LocalX			=LocalX;
	Cmd.LocalY			=LocalY;
	Cmd.Effective		=Effective;
	Cmd.Exclusive		=Exclusive;
	Cmd.MinDot			=MinDots;
	Cmd.MinSize			=MinSize;
	Cmd.LimitedLib		=LimitedLib;
	Cmd.ExpandedDot		=ExpandedDot;
	Cmd.OmitX1			=OmitX1;
	Cmd.OmitY1			=OmitY1;
	Cmd.OmitX2			=OmitX2;
	Cmd.OmitY2			=OmitY2;
	Cmd.NoisePinhole	=NoisePinhole;
	Cmd.NoiseSmallDot	=NoiseSmallDot;

	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}
//==============================================================================

GUICmdPickupArea::GUICmdPickupArea(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	AreaX1=0;
	AreaY1=0;
	AreaX2=99999999;
	AreaY2=99999999;
}

bool	GUICmdPickupArea::Load(QIODevice* f)
{
	if (::Load(f, PickupRL) == false)
		return false;
	if (::Load(f, PickupRH) == false)
		return false;
	if (::Load(f, PickupGL) == false)
		return false;
	if (::Load(f, PickupGH) == false)
		return false;
	if (::Load(f, PickupBL) == false)
		return false;
	if (::Load(f, PickupBH) == false)
		return false;
	if (::Load(f, Effective) == false)
		return false;
	if (LayerList.Load(f) == false)
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	if (::Load(f, ExpandedDot) == false)
		return false;
	if (::Load(f, MinSize) == false)
		return false;
	if (::Load(f, HoleMinArea) == false)
		return false;
	if (::Load(f, HoleErosionDot) == false)
		return false;
	if (::Load(f, AreaX1) == false)
		return false;
	if (::Load(f, AreaY1) == false)
		return false;
	if (::Load(f, AreaX2) == false)
		return false;
	if (::Load(f, AreaY2) == false)
		return false;
	return true;
}
bool	GUICmdPickupArea::Save(QIODevice* f)
{
	if (::Save(f, PickupRL) == false)
		return false;
	if (::Save(f, PickupRH) == false)
		return false;
	if (::Save(f, PickupGL) == false)
		return false;
	if (::Save(f, PickupGH) == false)
		return false;
	if (::Save(f, PickupBL) == false)
		return false;
	if (::Save(f, PickupBH) == false)
		return false;
	if (::Save(f, Effective) == false)
		return false;
	if (LayerList.Save(f) == false)
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	if (::Save(f, ExpandedDot) == false)
		return false;
	if (::Save(f, MinSize) == false)
		return false;
	if (::Save(f, HoleMinArea) == false)
		return false;
	if (::Save(f, HoleErosionDot) == false)
		return false;
	if (::Save(f, AreaX1) == false)
		return false;
	if (::Save(f, AreaY1) == false)
		return false;
	if (::Save(f, AreaX2) == false)
		return false;
	if (::Save(f, AreaY2) == false)
		return false;
	return true;
}

void	GUICmdPickupArea::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;
	CmdPickupAreaPacket	Cmd(this);
	Cmd.LayerList = LayerList;
	Cmd.PickupRL = PickupRL;
	Cmd.PickupRH = PickupRH;
	Cmd.PickupGL = PickupGL;
	Cmd.PickupGH = PickupGH;
	Cmd.PickupBL = PickupBL;
	Cmd.PickupBH = PickupBH;
	Cmd.Effective = Effective;
	Cmd.LimitedLib = LimitedLib;
	Cmd.ExpandedDot = ExpandedDot;
	Cmd.MinSize = MinSize;
	Cmd.HoleMinArea = HoleMinArea;
	Cmd.HoleErosionDot = HoleErosionDot;
	Cmd.AreaX1=AreaX1;
	Cmd.AreaY1=AreaY1;
	Cmd.AreaX2=AreaX2;
	Cmd.AreaY2=AreaY2;
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}
//==============================================================================
GUICmdExpandMask::GUICmdExpandMask(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdExpandMask::Load(QIODevice* f)
{
	if (::Load(f, PixelCount) == false)
		return false;
	return true;
}
bool	GUICmdExpandMask::Save(QIODevice* f)
{
	if (::Save(f, PixelCount) == false)
		return false;
	return true;
}
void	GUICmdExpandMask::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;

	CmdExpandMask	Cmd(this);
	Cmd.PixelCount = PixelCount;
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}
//==============================================================================
GUICmdReplaceInclusiveMask::GUICmdReplaceInclusiveMask(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

void	GUICmdReplaceInclusiveMask::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;

	CmdReplaceInclusiveMask	Cmd(this);
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//==============================================================================================

GUICmdReqLimitedLibMask::GUICmdReqLimitedLibMask(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

void	GUICmdReqLimitedLibMask::Receive(int32 localPage, int32 cmd, QString& EmitterRoot, QString& EmitterName)
{
	GUICmdAckLimitedLibMask* SendBack = GetSendBack(GUICmdAckLimitedLibMask, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase != NULL) {
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage != NULL) {
			CmdReqLimitedLibMask	Cmd(GetLayersBase());
			MaskPage->TransmitDirectly(&Cmd);
			SendBack->LimitedLib = Cmd.LimitedLib;
		}
	}

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}

GUICmdAckLimitedLibMask::GUICmdAckLimitedLibMask(LayersBase* Base, const QString& EmitterRoot, const QString& EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdAckLimitedLibMask::Load(QIODevice* f)
{
	if (LimitedLib.Load(f) == false)
		return false;
	return true;
}
bool	GUICmdAckLimitedLibMask::Save(QIODevice* f)
{
	if (LimitedLib.Save(f) == false)
		return false;
	return true;
}

//==============================================================================================
GUICmdMaskingMakeBackGround::GUICmdMaskingMakeBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	MasterMode=true;
}
bool	GUICmdMaskingMakeBackGround::Load(QIODevice *f)
{
	if (::Load(f, MasterMode) == false)
		return false;
	return true;
}
bool	GUICmdMaskingMakeBackGround::Save(QIODevice *f)
{
	if (::Save(f, MasterMode) == false)
		return false;
	return true;
}

void	GUICmdMaskingMakeBackGround::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;

	CmdMaskingMakeBackGround	Cmd(GetLayersBase());
	Cmd.MasterMode=MasterMode;
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//==============================================================================================

GUICmdClearMakeBackGround::GUICmdClearMakeBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

void	GUICmdClearMakeBackGround::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase == NULL)
		return;
	AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
	if (MaskPage == NULL)
		return;

	CmdMaskingClearBackGround	Cmd(GetLayersBase());
	MaskPage->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//==============================================================================================


GUICmdReqBindedLimitedLibMask::GUICmdReqBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
void	GUICmdReqBindedLimitedLibMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBindedLimitedLibMask* SendBack = GetSendBack(GUICmdAckBindedLimitedLibMask, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase != NULL) {
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage != NULL) {
			for(int layer=0;layer<GetLayerNumb(localPage);layer++){
				AlgorithmInLayerRoot *AL=MaskPage->GetLayerData(layer);
				if(AL!=NULL){
					CmdMaskingBindedList	Cmd(GetLayersBase());
					AL->TransmitDirectly(&Cmd);

					SendBack->InstList.AddMove(Cmd.InstList);
				}
			}
		}
	}

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}
	
GUICmdAckBindedLimitedLibMask::GUICmdAckBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdAckBindedLimitedLibMask::Load(QIODevice *f)
{
	if(InstList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckBindedLimitedLibMask::Save(QIODevice *f)
{
	if(InstList.Save(f)==false)
		return false;
	return true;
}


GUICmdSetBindedLimitedLibMask::GUICmdSetBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdSetBindedLimitedLibMask::Load(QIODevice *f)
{
	if(InstList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetBindedLimitedLibMask::Save(QIODevice *f)
{
	if(InstList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetBindedLimitedLibMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase != NULL) {
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage != NULL) {
			for(MaskingBindedList *b=InstList.GetFirst();b!=NULL;b=b->GetNext()){
				MaskingBindedList::BindedInPage	*Bp=b->BindedInPageContainerInst.GetFirst();
				for(MaskingBindedList::BindedInPage::BindedInLayer *BL=Bp->BindedInLayerContainerInst.GetFirst();BL!=NULL;BL=BL->GetNext()){
					AlgorithmInLayerRoot *AL=MaskPage->GetLayerData(BL->Layer);
					if(AL!=NULL){
						for(IntClass *c=BL->ItemIDs.GetFirst();c!=NULL;c=c->GetNext()){
							CmdSetLimitedLibMaskInItem	Cmd(GetLayersBase());
							Cmd.ItemID=c->GetValue();
							Cmd.SelAreaID=&b->LimitedLib;
							AL->TransmitDirectly(&Cmd);
						}
					}
				}
			}
		}
	}
}


GUICmdSelectBindedLimitedLibMask::GUICmdSelectBindedLimitedLibMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdSelectBindedLimitedLibMask::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(ItemIDs.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSelectBindedLimitedLibMask::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(ItemIDs.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSelectBindedLimitedLibMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase != NULL) {
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage != NULL) {
			AlgorithmInLayerRoot *AL=MaskPage->GetLayerData(Layer);
			for(IntClass *c=ItemIDs.GetFirst();c!=NULL;c=c->GetNext()){
				AlgorithmItemRoot	*Item=AL->SearchIDItem(c->GetValue());
				Item->SetSelected(true);
			}
		}
	}
}

GUICmdReqMaskCount::GUICmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
void	GUICmdReqMaskCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMaskCount* SendBack = GetSendBack(GUICmdAckMaskCount, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage!=NULL) {
			CmdReqUsedLimitedMaskCount	RCmd(GetLayersBase());
			MaskPage->TransmitDirectly(&RCmd);
			SendBack->MaskContainer=RCmd.MaskContainer;
		}
	}

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}

GUICmdAckMaskCount::GUICmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdAckMaskCount::Load(QIODevice *f)
{
	if(MaskContainer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckMaskCount::Save(QIODevice *f)
{
	if(MaskContainer.Save(f)==false)
		return false;
	return true;
}

//========================================================

GUICmdGenerateMaskOnSelectedItemsEdge::GUICmdGenerateMaskOnSelectedItemsEdge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdGenerateMaskOnSelectedItemsEdge::Load(QIODevice *f)
{
	if(::Load(f,Effective)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;
    if(::Load(f,InsideDot )==false)	return false;
    if(::Load(f,OutsideDot)==false)	return false;
	return true;
}
bool	GUICmdGenerateMaskOnSelectedItemsEdge::Save(QIODevice *f)
{
	if(::Save(f,Effective)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;
    if(::Save(f,InsideDot )==false)	return false;
    if(::Save(f,OutsideDot)==false)	return false;
	return true;
}

void	GUICmdGenerateMaskOnSelectedItemsEdge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage!=NULL) {
			CmdGenerateMaskOnSelectedItemsEdge	RCmd(GetLayersBase());
			RCmd.Effective	=Effective	;
			RCmd.LimitedLib	=LimitedLib	;
			RCmd.Expansion	=Expansion	;
			RCmd.InsideDot	=InsideDot	;
			RCmd.OutsideDot	=OutsideDot	;

			MaskPage->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}

//========================================================

GUICmdGeneratePatternEdgeOnSelected::GUICmdGeneratePatternEdgeOnSelected(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdGeneratePatternEdgeOnSelected::Load(QIODevice *f)
{
	if(::Load(f,Effective)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;
    if(::Load(f,BoundaryDiff )==false)	return false;
    if(::Load(f,WidthDot)==false)	return false;
	return true;
}
bool	GUICmdGeneratePatternEdgeOnSelected::Save(QIODevice *f)
{
	if(::Save(f,Effective)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;
    if(::Save(f,BoundaryDiff )==false)	return false;
    if(::Save(f,WidthDot)==false)	return false;
	return true;
}

void	GUICmdGeneratePatternEdgeOnSelected::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage!=NULL) {
			CmdGeneratePatternEdgeOnSelected	RCmd(GetLayersBase());
			RCmd.Effective	=Effective	;
			RCmd.LimitedLib	=LimitedLib	;
			RCmd.BoundaryDiff	=BoundaryDiff	;
			RCmd.WidthDot	=WidthDot	;

			MaskPage->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}

//========================================================

GUICmdReflectSelection::GUICmdReflectSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdReflectSelection::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)	return false;
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	GUICmdReflectSelection::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)	return false;
	if(Items.Save(f)==false)	return false;
	return true;
}

void	GUICmdReflectSelection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageRoot	*MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage!=NULL) {
			AlgorithmInLayerRoot *Lp=MaskPage->GetLayerData(Layer);
			if(Lp!=NULL){
				CmdReflectSelection	Cmd(GetLayersBase());
				Cmd.Items=Items;
				Lp->TransmitDirectly(&Cmd);
			}
		}
	}
	SendAck(localPage);
}
//========================================================

GUICmdReqRemoveMask::GUICmdReqRemoveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdReqRemoveMask::Load(QIODevice *f)
{
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,Phase	)==false)	return false;
	return true;
}
bool	GUICmdReqRemoveMask::Save(QIODevice *f)
{
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,Phase	)==false)	return false;
	return true;
}

void	GUICmdReqRemoveMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=MaskingBase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*MaskPage = Ah->GetPageData(localPage);
			if(MaskPage!=NULL) {
				AlgorithmInLayerRoot*Lp=MaskPage->GetLayerData(Layer);
				if(Lp!=NULL){
					CmdRemoveMaskItem	Cmd(GetLayersBase());
					Cmd.ItemID=ItemID;
					Lp->TransmitDirectly(&Cmd);
				}
			}
		}
	}
	SendAck(localPage);
}
	
//========================================================

GUICmdSetItemSelection::GUICmdSetItemSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdSetItemSelection::Load(QIODevice *f)
{
	if(::Load(f,Effective)==false)	return false;
	if(LimitedLib.Load(f)==false)	return false;
	return true;
}
bool	GUICmdSetItemSelection::Save(QIODevice *f)
{
	if(::Save(f,Effective)==false)	return false;
	if(LimitedLib.Save(f)==false)	return false;
	return true;
}

void	GUICmdSetItemSelection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase* MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageRoot* MaskPage = MaskingBase->GetPageData(localPage);
		if (MaskPage!=NULL) {
			CmdSetItemSelection	RCmd(GetLayersBase());
			RCmd.Effective	=Effective	;
			RCmd.LimitedLib	=LimitedLib	;

			MaskPage->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}