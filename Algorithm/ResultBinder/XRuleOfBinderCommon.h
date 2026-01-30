/*
 * Copyright (C) 2016
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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