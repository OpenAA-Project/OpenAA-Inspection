/*
 * Copyright (C) 2023
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



#include "XLearning.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "omp.h"


bool	LearningFileList::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	return true;
}
	
bool	LearningFileList::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	return true;
}

LearningFileList	&LearningFileList::operator=(LearningFileList &src)
{
	FileName	=src.FileName;
	GlobalPage	=src.GlobalPage;
	LotAutoCount=src.LotAutoCount;
	ID			=src.ID;
	return *this;
}



bool	LearningFileListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();

	if(::Save(f,N)==false)
		return false;
	for(LearningFileList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	LearningFileListContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;

	RemoveAll();
	for(int i=0;i<N;i++){
		LearningFileList *a=new LearningFileList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}


LearningFileListContainer	&LearningFileListContainer::operator=(LearningFileListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
	
LearningFileListContainer	&LearningFileListContainer::operator+=(LearningFileListContainer &src)
{
	for(LearningFileList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LearningFileList *b=new LearningFileList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

static	int	SortByIDFunc(const void *a ,const void *b)
{
	LearningFileList **am=(LearningFileList **)a;
	LearningFileList **bm=(LearningFileList **)b;
	if((*am)->ID > (*bm)->ID)
		return 1;
	if((*am)->ID < (*bm)->ID)
		return -1;
	return 0;
}
static	int	SortByNameFunc(const void *a ,const void *b)
{
	LearningFileList **am=(LearningFileList **)a;
	LearningFileList **bm=(LearningFileList **)b;
	if((*am)->FileName > (*bm)->FileName)
		return 1;
	if((*am)->FileName < (*bm)->FileName)
		return -1;
	return 0;
}

void	LearningFileListContainer::SortByName(void)
{
	int	N=GetNumber();
	LearningFileList **Table=new LearningFileList *[N];
	int	k=0;
	LearningFileList *a;
	while((a=GetFirst())!=NULL){
		Table[k]=a;
		RemoveList(a);
		k++;
	}
	QSort(Table,N,sizeof(Table[0]),SortByNameFunc);
	for(int i=0;i<N;i++){
		AppendList(Table[i]);
	}
	delete	[]Table;
}
	
void	LearningFileListContainer::SortByID(void)
{
	int	N=GetNumber();
	LearningFileList **Table=new LearningFileList *[N];
	int	k=0;
	LearningFileList *a;
	while((a=GetFirst())!=NULL){
		Table[k]=a;
		RemoveList(a);
		k++;
	}
	QSort(Table,N,sizeof(Table[0]),SortByIDFunc);
	for(int i=0;i<N;i++){
		AppendList(Table[i]);
	}
	delete	[]Table;
}

bool	LearningAreaList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Ok)==false)
		return false;
	if(::Save(f,NGLevel)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}

bool	LearningAreaList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,NGLevel)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}
	
LearningAreaList	&LearningAreaList::operator=(LearningAreaList &src)
{
	GlobalPage	=src.GlobalPage;
	ItemID		=src.ItemID;
	Ok			=src.Ok;
	NGLevel		=src.NGLevel;
	X1			=src.X1;
	Y1			=src.Y1;
	X2			=src.X2;
	Y2			=src.Y2;
	return *this;
}


bool	LearningAreaListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();

	if(::Save(f,N)==false)
		return false;
	for(LearningAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	LearningAreaListContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;

	RemoveAll();
	for(int i=0;i<N;i++){
		LearningAreaList *a=new LearningAreaList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
LearningAreaListContainer &LearningAreaListContainer::operator=(LearningAreaListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
LearningAreaListContainer &LearningAreaListContainer::operator+=(LearningAreaListContainer &src)
{
	for(LearningAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		LearningAreaList *b=new LearningAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
