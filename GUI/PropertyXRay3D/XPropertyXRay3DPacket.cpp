/*
 * Copyright (C) 2026
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

#include "XPropertyXRay3DPacket.h"
#include "XXRay3D.h"
#include "XGeneralFunc.h"
	
GUICmdLoadImages::GUICmdLoadImages(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}


bool	GUICmdLoadImages::Load(QIODevice *f)
{
	if(::Load(f,ImageFileNames)==false)	return false;
	return true;
}
bool	GUICmdLoadImages::Save(QIODevice *f)
{
	if(::Save(f,ImageFileNames)==false)	return false;
	return true;
}

void	GUICmdLoadImages::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
			if(AP!=NULL){
				CmdLoadImages	Cmd(GetLayersBase());
				Cmd.ImageFileNames		=ImageFileNames	;	;
				AP->TransmitDirectly(&Cmd);
			}
		}
	}
}

GUICmdSetPointY::GUICmdSetPointY(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetPointY::Load(QIODevice *f)
{
	if(::Load(f,PointToDraw)==false)	return false;
	return true;
}
bool	GUICmdSetPointY::Save(QIODevice *f)
{
	if(::Save(f,PointToDraw)==false)	return false;
	return true;
}

void	GUICmdSetPointY::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
			if(AP!=NULL){
				CmdSetPointY	Cmd(GetLayersBase());
				Cmd.PointToDraw		=PointToDraw	;	;
				AP->TransmitDirectly(&Cmd);
			}
		}
	}
}

GUICmdReqSmooth::GUICmdReqSmooth(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSmooth::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqSmooth::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqSmooth::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
			if(AP!=NULL){
				CmdReqSmooth	Cmd(GetLayersBase());
				AP->TransmitDirectly(&Cmd);
			}
		}
	}
}

GUICmdReqEmphasize::GUICmdReqEmphasize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEmphasize::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqEmphasize::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqEmphasize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
			if(AP!=NULL){
				CmdReqEmphasize	Cmd(GetLayersBase());
				AP->TransmitDirectly(&Cmd);
			}
		}
	}
}

GUICmdReqMatchFile::GUICmdReqMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMatchFile::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)	return false;
	return true;
}
bool	GUICmdReqMatchFile::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)	return false;
	return true;
}

void	GUICmdReqMatchFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMatchFile	*SendBack=GetSendBack(GUICmdAckMatchFile,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	XRay3DBase *RBBase=(XRay3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"XRay3D");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(0);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
			if(AP!=NULL){
				CmdMatchFile	Cmd(GetLayersBase());
				Cmd.FileName		=FileName	;	;
				AP->TransmitDirectly(&Cmd);
				SendBack->RetFileNo = Cmd.RetFileNo;
				SendBack->RetX = Cmd.RetX;
				SendBack->RetY = Cmd.RetY;
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMatchFile::GUICmdAckMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMatchFile::Load(QIODevice *f)
{
	if(::Load(f,RetFileNo)==false)	return false;
	if(::Load(f,RetX)==false)	return false;
	if(::Load(f,RetY)==false)	return false;
	return true;
}

bool	GUICmdAckMatchFile::Save(QIODevice *f)
{
	if(::Save(f,RetFileNo)==false)	return false;
	if(::Save(f,RetX)==false)	return false;
	if(::Save(f,RetY)==false)	return false;
	return true;
}