/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XDot.h"
#include "XGeneralFunc.h"

DotList::DotList(const DotList &src)
{
	X=src.X;
	Y=src.Y;
}

DotList	&DotList::operator=(const DotList &src)
{
	X=src.X;
	Y=src.Y;
	return *this;
}

bool	DotList::Save(QIODevice *f)
{
	if(::Save(f,X)==false){
		return false;
	}
	if(::Save(f,Y)==false){
		return false;
	}
	return true;
}
	
bool	DotList::Load(QIODevice *f)
{
	if(::Load(f,X)==false){
		return false;
	}
	if(::Load(f,Y)==false){
		return false;
	}
	return true;
}


DotListContainer	&DotListContainer::operator=(DotListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
DotListContainer	&DotListContainer::operator+=(DotListContainer &src)
{
	for(DotList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		DotList *d=new DotList();
		*d= *c;
		AppendList(d);
	}
	return *this;
}

void	DotListContainer::MakeFilledDotsFrom(FlexArea &src)
{
	RemoveAll();
    for(int i=0;i<src.GetFLineLen();i++){
        int nx  =src.GetFLineLeftX(i);
        int numb=src.GetFLineNumb(i);
		int	y	=src.GetFLineAbsY(i);
        for(int x=0;x<numb;x++){
			AppendList(new DotList(nx+x,y));
            }
        }
}

void	DotListContainer::GetCenter(double &cx, double &cy)
{
	cx=0;
	cy=0;
	int	N=0;
	for(DotList *L=GetFirst();L!=NULL;L=L->GetNext()){
		cx+=L->GetX();
		cy+=L->GetY();
		N++;
	}
	if(N!=0){
		cx/=N;
		cy/=N;
	}
}


bool	DotListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(DotList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
	
bool	DotListContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		DotList	*a=new DotList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

