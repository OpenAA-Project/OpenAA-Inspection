#include "XDotColorMatching.h"
#include "XGeneralFunc.h"

BlockListInfo	&BlockListInfo::operator=(const BlockListInfo &src)
{
	BlockListData=src.BlockListData;
	return *this;
}

bool	BlockListInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&BlockListData,sizeof(BlockListData))!=sizeof(BlockListData))
		return false;
	return true;
}
bool	BlockListInfo::Load(QIODevice *f)
{
	if(f->read((char *)&BlockListData,sizeof(BlockListData))!=sizeof(BlockListData))
		return false;
	return true;
}
BlockListInfoContainer	&BlockListInfoContainer::operator= (const BlockListInfoContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
BlockListInfoContainer	&BlockListInfoContainer::operator+=(const BlockListInfoContainer &src)
{
	for(BlockListInfo *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BlockListInfo *d=new BlockListInfo();
		*d=*s;
		AppendList(d);
	}
	return *this;
}