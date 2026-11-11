#include "XCheckDataValidation.h"
#include "XGeneralFunc.h"

//=============================================================================
bool	CheckDataValidationGridList::Save(QIODevice *f)
{
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	return true;
}
bool	CheckDataValidationGridList::Load(QIODevice *f)
{
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;

	return true;
}
