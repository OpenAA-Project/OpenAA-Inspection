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

#include "XCacheTargetImage.h"

CacheTargetImageInLayer::CacheTargetImageInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
}
CacheTargetImageInLayer::~CacheTargetImageInLayer(void)
{
}

void	CacheTargetImageInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	PacketSetToTarget	*PacketSetToTargetVar=dynamic_cast<PacketSetToTarget *>(packet);
	if(PacketSetToTargetVar!=NULL){
		DataInLayer		*L=GetDataInLayer();
		ImageBuffer	*Img=IBuffer.GetItem(PacketSetToTargetVar->Number);
		if(Img==NULL)
			return;
		L->SetToTargetBuff(*Img);
		return;
	}
	PacketGetImageBuffer	*PacketGetImageBufferVar=dynamic_cast<PacketGetImageBuffer *>(packet);
	if(PacketGetImageBufferVar!=NULL){
		PacketGetImageBufferVar->Img=IBuffer.GetItem(PacketGetImageBufferVar->Number);
		return;
	}
}

ExeResult	CacheTargetImageInLayer::ExecuteInitialAfterEdit(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	CacheTargetImageBase	*ABase=dynamic_cast<CacheTargetImageBase *>(GetParentBase());
	for(ImageBufferList *p=IBuffer.GetFirst();p!=NULL;){
		ImageBufferList *NextP=p->GetNext();
		if(p->GetWidth()!=GetDotPerLine() || p->GetHeight()!=GetMaxLines()){
			IBuffer.RemoveList(p);
			delete	p;
		}
		p=NextP;
	}
	while(IBuffer.GetCount()<ABase->BufferCount){
		ImageBufferList	*p=new ImageBufferList(ImageBufferTarget,GetDotPerLine(),GetMaxLines());
		IBuffer.AppendList(p);
	}
	while(IBuffer.GetCount()>ABase->BufferCount){
		ImageBufferList	*p=IBuffer.GetLast();
		IBuffer.RemoveList(p);
		delete	p;
	}
	return _ER_true;
}
ExeResult	CacheTargetImageInLayer::ExecuteProcessing	(int ExeID ,ResultInLayerRoot *Res)
{
	ImageBufferList	*p=IBuffer.GetFirst();
	if(p!=NULL){
		*((ImageBuffer *)p)=GetTargetBuff();
		IBuffer.RemoveList(p);
		IBuffer.AppendList(p);
	}
	return _ER_true;
}

ImageBuffer	*CacheTargetImageInLayer::GetPoint(int n)
{
	ImageBufferList	*p=IBuffer.GetItem(n);
	if(p!=NULL){
		return p;
	}
	return NULL;
}

//=================================================================================================================

void	CacheTargetImageInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	PacketSetToTarget	*PacketSetToTargetVar=dynamic_cast<PacketSetToTarget *>(packet);
	if(PacketSetToTargetVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
}

//=================================================================================================================
CacheTargetImageBase::CacheTargetImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	BufferCount	=5;

	SetParam(&BufferCount		, /**/"Setting" ,/**/"BufferCount"		,"Count of stored target images");
}


AlgorithmDrawAttr	*CacheTargetImageBase::CreateDrawAttr(void)
{
	return NULL;
}