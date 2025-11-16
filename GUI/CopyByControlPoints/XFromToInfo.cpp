#include "XFromToInfo.h"
#include "XGeneralFunc.h"

FromToClass::FromToClass(void)
{
	SrcType	=Info_AllPages;
	SrcShadowLevel	=0;
	SrcShadowNumber	=0;
	DstType	=Info_AllPages;
	DstShadowLevel	=0;
	DstShadowNumber	=0;
}

bool	FromToClass::Save(QIODevice *f)
{
	BYTE	d=(BYTE)SrcType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,SrcFileName	)==false)	return false;
	if(SrcPage.Save(f)==false)			return false;
	if(::Save(f,SrcShadowLevel)==false)	return false;
	if(::Save(f,SrcShadowNumber)==false)	return false;

	d=(BYTE)DstType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,DstFileName	)==false)	return false;
	if(DstPage.Save(f)==false)			return false;
	if(::Save(f,DstShadowLevel)==false)	return false;
	if(::Save(f,DstShadowNumber)==false)	return false;
	return true;
}
	
bool	FromToClass::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d			)==false)	return false;
	SrcType	=(FromToClassType)d;
	if(::Load(f,SrcFileName	)==false)	return false;
	if(SrcPage.Load(f)==false)			return false;
	if(::Load(f,SrcShadowLevel)==false)	return false;
	if(::Load(f,SrcShadowNumber)==false)	return false;

	if(::Load(f,d			)==false)	return false;
	DstType	=(FromToClassType)d;
	if(::Load(f,DstFileName	)==false)	return false;
	if(DstPage.Load(f)==false)			return false;
	if(::Load(f,DstShadowLevel)==false)	return false;
	if(::Load(f,DstShadowNumber)==false)	return false;

	return true;
}