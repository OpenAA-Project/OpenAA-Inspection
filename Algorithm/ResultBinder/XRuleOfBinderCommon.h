#if	!defined(XRuleOfBinderCommon_H)
#define	XRuleOfBinderCommon_H

//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include"NListComp.h"

class	ItemIDNameList : public NPListSaveLoad<ItemIDNameList>
{
public:
	int		ItemID;
	QString	ItemName;

	ItemIDNameList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	ItemIDNameContainer : public NPListPackSaveLoad<ItemIDNameList>
{
public:
	virtual	ItemIDNameList	*Create(void)	{	return new ItemIDNameList();	}
};


	
class	ConditionList : public NPListSaveLoad<ConditionList>
{
public:
	class	InputList : public NPListSaveLoad<InputList>
	{
	public:
		bool	OK;
		int		ErrorCode;
		BYTE	ErrorCondition;	//0:Ignore , 1:Equal 2:Larger 3:Smaller

		InputList(void){	OK=false;	ErrorCode=0;	ErrorCondition=0;	}

		virtual	bool	Save(QIODevice *f);
		virtual	bool	Load(QIODevice *f);
	};

	class	InputListContainer : public NPListPackSaveLoad<InputList>
	{
	public:
		virtual	InputList	*Create(void)	{	return new InputList();	}
	};

	InputListContainer	InputData;
	bool	OutputOK;
	int		OutputErrorCode;

	ConditionList(void){	OutputOK=false;		OutputErrorCode=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ConditionListContainer : public NPListPackSaveLoad<ConditionList>
{
public:
	virtual	ConditionList	*Create(void)	{	return new ConditionList();	}
};


#endif