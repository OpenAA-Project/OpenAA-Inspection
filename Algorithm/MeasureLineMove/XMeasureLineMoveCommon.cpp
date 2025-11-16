#include "XMeasureLineMove.h"


LineMoveListForPacket::LineMoveListForPacket(void)
{
	ItemID	=-1;
	Page	=-1;
	LibID	=-1;
	x1		=0;
	y1		=0;
	x2		=0;
	y2		=0;
	SearchDot=0;
}

bool	LineMoveListForPacket::Save(QIODevice *f)
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
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

bool	LineMoveListForPacket::Load(QIODevice *f)
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
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

LineMoveListForPacket	&LineMoveListForPacket::operator=(LineMoveListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	LibID	=src.LibID;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	SearchDot=src.SearchDot;
	ItemName=src.ItemName;
	return *this;
}

LineMoveListForPacket	*LineMoveListForPacketPack::Create(void)
{
	return new LineMoveListForPacket();
}
