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

#include "startcapturebuttonResource.h"

#include "XPushCmdPacket.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XEntryPoint.h"

GUICmdPushedStartCapture::GUICmdPushedStartCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPushedStartCapture::Load(QIODevice *f)
{
	if(::Load(f,ImageType)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	GUICmdPushedStartCapture::Save(QIODevice *f)
{
	if(::Save(f,ImageType)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}

void	GUICmdPushedStartCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//if(GetParamGlobal()->GetMaxScanStrategy()<=1 || StrategicNumber==0){
		if(GetParamComm()->Mastered==false){
			GetLayersBase()->SetCurrentStrategicNumber		(StrategicNumber);
			GetLayersBase()->SetCurrentStrategicNumberForSeq(StrategicNumber);
		}
	//}
	
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(ImageType==/**/"Master")	
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoMasterCaptureOnly();
		else if(ImageType==/**/"Target")	
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoTargetCaptureOnly();
	}
	
	GUICmdRepliedPushStartCapture	*SendBack=GetSendBack(GUICmdRepliedPushStartCapture,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdRepliedPushStartCapture::GUICmdRepliedPushStartCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRepliedPushStartCapture::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdRepliedPushStartCapture::Save(QIODevice *f)
{
	return true;
}
void	GUICmdRepliedPushStartCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}