#include "XGeneralFunc.h"
#include "XVCutInspection.h"

bool	VCutInspectionList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(::Load(f,ThresholdLevel)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	return true;
}

bool	VCutInspectionList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	return true;
}

VCutInspectionListForPacketPack	&VCutInspectionListForPacketPack::operator+=(VCutInspectionListForPacketPack &src)
{
	for(VCutInspectionList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		VCutInspectionList *d=new VCutInspectionList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	VCutInspectionListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		VCutInspectionList *c=new VCutInspectionList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	VCutInspectionListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(VCutInspectionList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
