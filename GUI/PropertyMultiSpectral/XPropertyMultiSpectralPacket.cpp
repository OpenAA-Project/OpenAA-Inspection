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

#include "XPropertyMultiSpectralPacket.h"
#include "XGeneralFunc.h"

//=====================================================================================
GUICmdSendAddMultiSpectralUsageAreaItem::GUICmdSendAddMultiSpectralUsageAreaItem(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage)
	:GUICmdPacketBase(Base, emitterRoot, emitterName, typeid(this).name(), globalPage)
{
}
bool	GUICmdSendAddMultiSpectralUsageAreaItem::Load(QIODevice *f)
{
	if(LocalArea.Load(f) == false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddMultiSpectralUsageAreaItem::Save(QIODevice *f)
{
	if(LocalArea.Save(f) == false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddMultiSpectralUsageAreaItem::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	MultiSpectralBase *BBase=(MultiSpectralBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MultiSpectral");
	if(BBase != NULL) {
		MultiSpectralInPage *PData=dynamic_cast<MultiSpectralInPage *>(BBase->GetPageData(localPage));
		if(PData != NULL) {
			AddMultiSpectralAreaPacket	Cmd(this);
			Cmd.Area	=LocalArea;
			Cmd.LibID	=LibID;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}