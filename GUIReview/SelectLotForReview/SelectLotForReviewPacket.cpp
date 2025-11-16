//#include "SelectLotForReviewResource.h"
#include "SelectLotForReviewPacket.h"
#include "XGeneralFunc.h"
#include "ReviewStructureItems.h"

bool GUICmdReviewLotList::Save(QIODevice *f)
{
	if(::Save(f, lotList.count())==false)
		return false;
	for(int i=0; i<lotList.count(); i++){
		if(::Save(f, lotList[i].TableName)==false)
			return false;
		if(::Save(f, lotList[i].LotName)==false)
			return false;
		if(::Save(f, lotList[i].Remark)==false)
			return false;
	}

	return true;
}

bool GUICmdReviewLotList::Load(QIODevice *f)
{
	int count;
	if(::Load(f, count)==false)
		return false;

	lotList.clear();
	for(int i=0; i<count; i++){
		LotInfoItem info;
		if(::Save(f, info.TableName)==false)
			return false;
		if(::Save(f, info.LotName)==false)
			return false;
		if(::Save(f, info.Remark)==false)
			return false;
		lotList << info;
	}

	return true;
}
