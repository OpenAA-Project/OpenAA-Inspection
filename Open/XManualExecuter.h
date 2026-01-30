/*
 * Copyright (C) 2022
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

#if	!defined(XManualExecuter_h)
#define	XManualExecuter_h

#include "NListComp.h"
#include <QIODevice>
#include "XTypeDef.h"

class	AlgorithmItemRoot;
class	AlgorithmBase;

class	ManualExecuterItem : public NPList<ManualExecuterItem>
{
public:
	int32	Command;
	int32	LibID;

	ManualExecuterItem(void)	{	Command=0;	LibID=-1;	}
	explicit	ManualExecuterItem(int cmd)					{	Command=cmd;	}
	ManualExecuterItem(const ManualExecuterItem &src)	{	Command=src.Command;	LibID=src.LibID;	}

	bool	SaveData(QIODevice *f);
	bool	LoadData(QIODevice *f);

	//ManualExecuterItem	&operator=(ManualExecuterItem &src){	Command=src.Command;	LibID=src.LibID;	return *this;	}
	virtual	ManualExecuterItem	*Create(void)			=0;
	virtual	bool	Save(QIODevice *f)					=0;
	virtual	bool	Load(QIODevice *f)					=0;
	virtual	bool	Execute(AlgorithmItemRoot *item)	=0;
};

class	ManualExecuterContainer : public NPListPack<ManualExecuterItem> ,public NPList<ManualExecuterContainer>
{
	ManualExecuterContainer	*RegisteredContainer;
public:
	ManualExecuterContainer(void)	{	RegisteredContainer=NULL;	}
	explicit	ManualExecuterContainer(ManualExecuterContainer *registeredContainer){	RegisteredContainer=registeredContainer;	}

	ManualExecuterItem	*FindByCommand(int cmd);
	int					GetLibID(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Execute(AlgorithmItemRoot *item);
	bool	IsExist(int cmd ,int LibID);

	//ManualExecuterContainer &operator=(ManualExecuterContainer &src)
	//{
	//	NPListPack<ManualExecuterItem>::operator=(*((NPListPack<ManualExecuterItem> *)&src));
	//	return *this;
	//}
};

class	ManualExecuter
{
	ManualExecuterContainer	Registered;
	NPListPack<ManualExecuterContainer>	CommandList;
public:
	ManualExecuter(void);

	void	RegisteringClass(ManualExecuterItem *f);
	void	AppendCommand(ManualExecuterItem *f);
	bool	DeliverToSlave(AlgorithmBase *ABase);
	bool	Execute(AlgorithmItemRoot *item);

	bool	SaveCommand(QIODevice *f);
	bool	LoadCommand(QIODevice *f);
	bool	IsExist(int cmd ,int LibID);
	bool	ClearCommandAll(void);
};
	
//=====================================================================



#endif