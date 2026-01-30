/*
 * Copyright (C) 2017
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

#include "LearningLibResource.h"
#include "XLearningLibHide.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"

GUICmdReqImageForPaint::GUICmdReqImageForPaint(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqImageForPaint::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false){
		return false;
	}
	if(::Load(f,LocalY1)==false){
		return false;
	}
	if(::Load(f,LocalX2)==false){
		return false;
	}
	if(::Load(f,LocalY2)==false){
		return false;
	}
	if(::Load(f,ZoomRate)==false){
		return false;
	}
	if(::Load(f,ScrWidth)==false){
		return false;
	}
	if(::Load(f,ScrHeight)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqImageForPaint::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false){
		return false;
	}
	if(::Save(f,LocalY1)==false){
		return false;
	}
	if(::Save(f,LocalX2)==false){
		return false;
	}
	if(::Save(f,LocalY2)==false){
		return false;
	}
	if(::Save(f,ZoomRate)==false){
		return false;
	}
	if(::Save(f,ScrWidth)==false){
		return false;
	}
	if(::Save(f,ScrHeight)==false){
		return false;
	}
	return true;
}

void	GUICmdReqImageForPaint::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckImageForPaint	*SendBack=GetSendBack(GUICmdAckImageForPaint,GetLayersBase(),EmitterRoot,EmitterName,localPage);
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	ImagePointerContainer Images;
	P->GetTargetImages(Images);
	SendBack->Image=Images.TransformImage(LocalX1,LocalY1
										,LocalX2,LocalY2
										,ZoomRate
										,ScrWidth
										,ScrHeight);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckImageForPaint::GUICmdAckImageForPaint(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckImageForPaint::Load(QIODevice *f)
{
	if(::Load(f,Image)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckImageForPaint::Save(QIODevice *f)
{
	if(::Save(f,Image)==false){
		return false;
	}
	return true;
}