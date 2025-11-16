#include "XShiftMark.h"
#include "XShiftMarkAlgoPacket.h"



ShiftMarkListForPacket::ShiftMarkListForPacket(void)
{
	ItemID	=-1;
	Page	=-1;
	LibID	=-1;
	x1		=0;
	y1		=0;
	x2		=0;
	y2		=0;
	SearchDotEdge=0;
}

bool	ShiftMarkListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
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
	if(::Save(f,SearchDotEdge)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

bool	ShiftMarkListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
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
	if(::Load(f,SearchDotEdge)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

ShiftMarkListForPacket	&ShiftMarkListForPacket::operator=(ShiftMarkListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	LibID	=src.LibID;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	SearchDotEdge=src.SearchDotEdge;
	ItemName=src.ItemName;
	return *this;
}

bool	ShiftMarkListForPacketPackForPhase::Save(QIODevice *f)
{
	if(NPListPackSaveLoad<ShiftMarkListForPacket>::Save(f)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	return true;
}
bool	ShiftMarkListForPacketPackForPhase::Load(QIODevice *f)
{
	if(NPListPackSaveLoad<ShiftMarkListForPacket>::Load(f)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	return true;
}

ShiftMarkListForPacket	*ShiftMarkListForPacketPackForPhase::Create(void)
{
	return new ShiftMarkListForPacket();
}
ShiftMarkListForPacketPackForPhase	&ShiftMarkListForPacketPackForPhase::operator=(ShiftMarkListForPacketPackForPhase &src)
{
	RemoveAll();
	for(ShiftMarkListForPacket *s=src.NPListPackSaveLoad<ShiftMarkListForPacket>::GetFirst();s!=NULL;s=s->GetNext()){
		ShiftMarkListForPacket	*d=new ShiftMarkListForPacket();
		*d=*s;
		AppendList(d);
	}
	Phase=src.Phase;
	return *this;
}

ShiftMarkListForPacketPackForPhase	*ShiftMarkListForPacketPack::Create(void)
{
	return new ShiftMarkListForPacketPackForPhase();
}