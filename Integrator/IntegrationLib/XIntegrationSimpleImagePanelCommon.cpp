#include "XIntegrationSimpleImagePanelCommon.h"

//=============================================================================================
bool	SelectedItemsInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,ItemName)==false)	return false;
	if(::Save(f,Comment)==false)	return false;
	if(::Save(f,SomethingData)==false)	return false;
	return true;
}
bool	SelectedItemsInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,ItemName)==false)	return false;
	if(::Load(f,Comment)==false)	return false;
	if(::Load(f,SomethingData)==false)	return false;
	return true;
}
SelectedItemsInfo	&SelectedItemsInfo::operator=(const SelectedItemsInfo &src)
{
	Phase		=src.Phase		;
	Page		=src.Page		;
	Layer		=src.Layer		;
	ItemID		=src.ItemID		;
	ItemName	=src.ItemName	;
	Comment		=src.Comment	;
	SomethingData	=src.SomethingData	;
	return *this;
}
SelectedItemsInfoContainer	&SelectedItemsInfoContainer::operator=(const SelectedItemsInfoContainer &src)
{
	RemoveAll();

	for(SelectedItemsInfo *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		SelectedItemsInfo	*d=new SelectedItemsInfo();
		*d=*s;
		AppendList(d);
	}
	return *this;
}