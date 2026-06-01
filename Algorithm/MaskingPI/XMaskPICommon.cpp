
#include "XGeneralFunc.h"
#include "XMaskingPI.h"

bool	MaskingPIListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
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
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}
bool	MaskingPIListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
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
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
MaskingPIListForPacket	&MaskingPIListForPacket::operator=(MaskingPIListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	Effective	=src.Effective;
	LimitedLib	=src.LimitedLib;
	return *this;
}


bool	MaskingPIListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(MaskingPIListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	MaskingPIListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		MaskingPIListForPacket	*c=new MaskingPIListForPacket();
		if(c->Load(f)==false)
			return false;
	}
	return true;
}

MaskingPIListForPacketPack	&MaskingPIListForPacketPack::operator=(MaskingPIListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
MaskingPIListForPacketPack	&MaskingPIListForPacketPack::operator+=(MaskingPIListForPacketPack &src)
{
	for(MaskingPIListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		MaskingPIListForPacket *d=new MaskingPIListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
}
