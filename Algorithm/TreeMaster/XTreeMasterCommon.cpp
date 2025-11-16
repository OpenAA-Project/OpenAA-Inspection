#include "XTreeMasterCommon.h"
#include "XGeneralFunc.h"


bool	AreaWithColor::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Color.Save(f)==false)
		return false;
	return true;
}

bool	AreaWithColor::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Color.Load(f)==false)
		return false;
	return true;
}

void	AreaWithColor::MoveTo(int dx ,int dy)
{
	Area.MoveToNoClip(dx,dy);
}

//====================================================

void	AreaWithColorContainer::MoveTo(int dx ,int dy)
{
	for(AreaWithColor *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveTo(dx,dy);
	}
}
