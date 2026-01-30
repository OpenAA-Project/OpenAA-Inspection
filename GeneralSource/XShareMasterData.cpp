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

#include "XTypeDef.h"
#include "XShareMasterData.h"
#include "XGeneralFunc.h"

ShareMasterFromSource::ShareMasterFromSource(LayersBase *base)
	:ServiceForLayers(base)
{
	SourceMachineID	=-1;
	Dx=0;
	Dy=0;
	for(int i=0;i<256;i++){
		MultiplyLayer[i]=1.0;
	}
}

bool	ShareMasterFromSource::Save(QIODevice *f)
{
	if(::Save(f,SourceMachineID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)MultiplyLayer,sizeof(MultiplyLayer))!=sizeof(MultiplyLayer))
		return false;
	return true;
}

bool	ShareMasterFromSource::Load(QIODevice *f)
{
	if(::Load(f,SourceMachineID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)MultiplyLayer,sizeof(MultiplyLayer))!=sizeof(MultiplyLayer))
		return false;
	return true;
}


ShareMasterDestination::ShareMasterDestination(LayersBase *base)
	:ServiceForLayers(base)
{
	DestinationMachineID=-1;
}

ShareMasterFromSource	*ShareMasterDestination::Create(void)
{	
	return new ShareMasterFromSource(GetLayersBase());
}

int	ShareMasterSortFunc(const void *a,const void *b)
{
	ShareMasterFromSource **pa=(ShareMasterFromSource **)a;
	ShareMasterFromSource **pb=(ShareMasterFromSource **)b;

	return pa[0]->SourceMachineID - pb[0]->SourceMachineID;
}

void	ShareMasterDestination::SortItems(void)
{
	ShareMasterFromSource	**Point=new ShareMasterFromSource*[GetCount()];
	int	n=0;
	ShareMasterFromSource *s;
	while((s=NPListPackSaveLoad<ShareMasterFromSource>::GetFirst())!=NULL){
		RemoveList(s);
		Point[n]=s;
		n++;
	}
	QSort(Point,n,sizeof(ShareMasterFromSource *),ShareMasterSortFunc);
	for(int i=0;i<n;i++){
		AppendList(Point[i]);
	}
	delete	[]Point;
}

ShareMasterFromSource	*ShareMasterDestination::GetSource(int machineID)
{
	for(ShareMasterFromSource *s=NPListPackSaveLoad<ShareMasterFromSource>::GetFirst();s!=NULL;s=s->GetNext()){
		if(s->SourceMachineID==machineID){
			return s;
		}
	}
	return NULL;
}

bool	ShareMasterDestination::Save(QIODevice *f)
{
	if(::Save(f,DestinationMachineID)==false)
		return false;
	if(NPListPackSaveLoad<ShareMasterFromSource>::Save(f)==false)
		return false;
	return true;
}

bool	ShareMasterDestination::Load(QIODevice *f)
{
	if(::Load(f,DestinationMachineID)==false)
		return false;
	if(NPListPackSaveLoad<ShareMasterFromSource>::Load(f)==false)
		return false;
	return true;
}

//============================================================================
ShareMasterContainer::ShareMasterContainer(LayersBase *base)
	:ServiceForLayers(base)
{
}

ShareMasterDestination	*ShareMasterContainer::FindDestination(int DestMachineID)
{
	for(ShareMasterDestination *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->DestinationMachineID==DestMachineID)
			return d;
	}
	return NULL;
}

bool	ShareMasterContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false)
		return false;
	for(ShareMasterDestination *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	ShareMasterContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ShareMasterDestination	*d=new ShareMasterDestination(GetLayersBase());
		if(d->Load(f)==false){
			return false;
		}
		AppendList(d);
	}
	return true;
}