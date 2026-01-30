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