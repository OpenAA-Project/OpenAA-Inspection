#include "XRuleOfBinderCommon.h"
#include "XGeneralFunc.h"

bool	ItemIDNameList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	ItemIDNameList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

		
bool	ConditionList::InputList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,OK)==false)
		return false;
	if(::Save(f,ErrorCode)==false)
		return false;
	if(::Save(f,ErrorCondition)==false)
		return false;
	return true;
}

bool	ConditionList::InputList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,OK)==false)
		return false;
	if(::Load(f,ErrorCode)==false)
		return false;
	if(::Load(f,ErrorCondition)==false)
		return false;
	return true;
}

			
bool	ConditionList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(InputData.Save(f)==false)
		return false;
	if(::Save(f,OutputOK)==false)
		return false;
	if(::Save(f,OutputErrorCode)==false)
		return false;
	return true;
}

bool	ConditionList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(InputData.Load(f)==false)
		return false;
	if(::Load(f,OutputOK)==false)
		return false;
	if(::Load(f,OutputErrorCode)==false)
		return false;
	return true;
}


