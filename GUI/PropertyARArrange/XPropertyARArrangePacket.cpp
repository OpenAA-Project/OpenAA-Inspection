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

#include "PropertyARArrangeResource.h"
#include "XPropertyARArrangePacket.h"
#include "XGeneralFunc.h"
#include "XARArrange.h"


GUICmdReqARLearningList::GUICmdReqARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqARLearningList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendARLearningList	*SendBack=GetSendBack(GUICmdSendARLearningList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	GetLayersBase()->GetPageData(localPage)->MakeLearningImagePointerContainer(SendBack->LearningPointerContainer);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendARLearningList::GUICmdSendARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendARLearningList::Load(QIODevice *f)
{
	if(LearningPointerContainer.Load(f,GetLayersBase())==false){
		return false;
	}
	return true;
}

bool	GUICmdSendARLearningList::Save(QIODevice *f)
{
	if(LearningPointerContainer.Save(f)==false){
		return false;
	}
	return true;
}

//==============================================================================

GUICmdReqARArrangeList::GUICmdReqARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqARArrangeList::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false)
		return false;
	return true;
}
bool	GUICmdReqARArrangeList::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false)
		return false;
	return true;
}

void	GUICmdReqARArrangeList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendARArrangeList	*SendBack=GetSendBack(GUICmdSendARArrangeList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ARArrange");
	if(AlignBase!=NULL){
		AlgorithmInPageRoot	*PData=AlignBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdMakeARArrangeList	Cmd(GetLayersBase());
			Cmd.CreatedTime = CreatedTime;
			Cmd.ItemContainer=&SendBack->ItemContainer;
			PData->TransmitDirectly(&Cmd);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendARArrangeList::GUICmdSendARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendARArrangeList::Load(QIODevice *f)
{
	if(ItemContainer.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendARArrangeList::Save(QIODevice *f)
{
	if(ItemContainer.Save(f)==false)
		return false;
	return true;
}

//==============================================================================

GUICmdReqAddARArrange::GUICmdReqAddARArrange(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAddARArrange::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,CreatedTime)==false)
		return false;
	return true;
}
bool	GUICmdReqAddARArrange::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,CreatedTime)==false)
		return false;
	return true;
}

void	GUICmdReqAddARArrange::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ARArrange");
	if(AlignBase!=NULL){
		AlgorithmInPageRoot	*PData=AlignBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqAddARArrange	Cmd(this);
			Cmd.Area=Area;
			Cmd.CreatedTime=CreatedTime;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//==============================================================================

GUICmdReqLearningThumnail::GUICmdReqLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ImageWidth	=0;
	ImageHeight	=0;
}

bool	GUICmdReqLearningThumnail::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false)
		return false;
	if(::Load(f,ImageWidth)==false)
		return false;
	if(::Load(f,ImageHeight)==false)
		return false;
	return true;
}

bool	GUICmdReqLearningThumnail::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false)
		return false;
	if(::Save(f,ImageWidth)==false)
		return false;
	if(::Save(f,ImageHeight)==false)
		return false;
	return true;
}

void	GUICmdReqLearningThumnail::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendLearningThumnail	*SendBack=GetSendBack(GUICmdSendLearningThumnail,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Img=new QImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	LearningImage	*d=GetLayersBase()->GetPageData(localPage)->Find(CreatedTime);
	if(d!=NULL){
		d->DrawThumnailImage(*SendBack->Img,ImageWidth,ImageHeight);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendLearningThumnail::GUICmdSendLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Img=NULL;
}
GUICmdSendLearningThumnail::~GUICmdSendLearningThumnail(void)
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=NULL;
}

bool	GUICmdSendLearningThumnail::Load(QIODevice *f)
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=new QImage();
	if(::Load(f,*Img)==false)
		return false;
	return true;
}
	
bool	GUICmdSendLearningThumnail::Save(QIODevice *f)
{
	if(::Save(f,*Img)==false)
		return false;
	return true;
}