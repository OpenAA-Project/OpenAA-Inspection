/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFifoClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XTypeDef.h"
#include "XFifoClass.h"
//---------------------------------------------------------------------------

NFifoIntLeaf::NFifoIntLeaf(void)
:Data(0)
{
}
NFifoIntLeaf::NFifoIntLeaf(const NFifoIntLeaf &src)
{
	Data=src.Data;
}
NFifoIntLeaf::~NFifoIntLeaf(void)
{
}
NFifoIntLeaf	&NFifoIntLeaf::operator=(const NFifoIntLeaf &src)
{
	Data=src.Data;
	return *this;
}
void    NFifoIntLeaf::SetData(int data)
{
    Data=data;
}

int NFifoIntLeaf::PopData(void)
{
    return(Data);
}

FifoIntPacket::FifoIntPacket(void)
{
}
FifoIntPacket::FifoIntPacket(const FifoIntPacket &src)
{
	CSection.lock();
	LData.RemoveAll();
	for(NFifoIntLeaf *f=src.LData.GetFirst();f!=NULL;f=f->GetNext()){
		NFifoIntLeaf *a=new NFifoIntLeaf();
		*a=*f;
		LData.AppendList(a);
	}
	CSection.unlock();
}
FifoIntPacket::~FifoIntPacket(void)
{
}
FifoIntPacket	&FifoIntPacket::operator=(FifoIntPacket &src)
{
	CSection.lock();
	LData.RemoveAll();
	for(NFifoIntLeaf *f=src.LData.GetFirst();f!=NULL;f=f->GetNext()){
		NFifoIntLeaf *a=new NFifoIntLeaf();
		*a=*f;
		LData.AppendList(a);
	}
	CSection.unlock();
	return *this;
}
void    FifoIntPacket::Push(int data)
{
    NFifoIntLeaf   *a=new NFifoIntLeaf();
    a->SetData(data);
    CSection.lock();
    LData.AppendList(a);
    CSection.unlock();
}

int     FifoIntPacket::Pop(void)
{
    CSection.lock();
    NFifoIntLeaf   *a=LData.GetFirst();
    if(a!=NULL){
        LData.RemoveList(a);
        int   s=a->PopData();
        CSection.unlock();
        delete  a;
        return(s);
        }
    CSection.unlock();
    return(-1);
}
