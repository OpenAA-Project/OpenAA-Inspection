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



#include "XTypeDef.h"
#include "XFifoClass.h"
#include <string.h>
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


FifoBuffer::FifoBuffer(int MaxLen)
{
    AllocatedLen=MaxLen;
    Data=new BYTE[MaxLen];
    WPoint  =0;
    RPoint  =0;
    Len     =0;
}
FifoBuffer::~FifoBuffer(void)
{
    AllocatedLen=0;
    delete  []Data;
    Data=NULL;
    WPoint  =0;
    RPoint  =0;
    Len     =0;
}

bool    FifoBuffer::Push(BYTE *buff ,int len)
{
    if(Len+len>AllocatedLen){
        return false;
    }
    if(WPoint+len>AllocatedLen){
        int LenBefore=AllocatedLen-WPoint;
        memcpy(&Data[WPoint],buff,LenBefore);
        int LenAfter=len-LenBefore;
        memcpy(Data,&buff[LenBefore],LenAfter);
        WPoint+=len;
        WPoint-=AllocatedLen;
        Len+=len;
    }
    else{
        memcpy(&Data[WPoint],buff,len);
        WPoint+=len;
        Len+=len;
    }
    return true;
}
int    FifoBuffer::Pop(void)
{
    if(Len<=0){
        return -1;
    }
    BYTE    Ret=Data[RPoint];
    RPoint++;
    if(RPoint>=AllocatedLen){
        RPoint-=AllocatedLen;
    }
    Len--;
    return Ret;
}
int     FifoBuffer::Pop(char *buff ,int maxlen)
{
    if(Len<=0){
        return -1;
    }
    int N=Len;
    if(Len>maxlen){
        N=maxlen;
    }
    if(RPoint+N>AllocatedLen){
        int NBefore=AllocatedLen-RPoint;
        memcpy(buff,&Data[RPoint],NBefore);
        int NAfter=N-NBefore;
        memcpy(&buff[NBefore],Data,NAfter);
        Len-=N;
        RPoint+=N;
        if(RPoint>=AllocatedLen){
            RPoint-=AllocatedLen;
        }
        return N;
    }
    memcpy(buff,&Data[RPoint],N);
    Len-=N;
    RPoint+=N;
    if(RPoint>=AllocatedLen){
        RPoint-=AllocatedLen;
    }
    return N;
}

int     FifoBuffer::GetSize(void)
{
    return Len;
}
