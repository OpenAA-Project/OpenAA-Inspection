/*
 * Copyright (C) 2019
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

#include "NListComp.h"
#include "XGeneralFunc.h"
#include "XTypeDef.h"
#include <QBuffer>

template<class T>
NPListSaveLoad<T>	&NPListSaveLoad<T>::operator=(T &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Save(&Buff)==false){
		return *this;
	}
	Buff.seek(0);
	Load(&Buff);
	return *this;
}
template<class T>
NPListSaveLoad<T>	&NPListSaveLoad<T>::operator=(const T &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Save(&Buff)==false){
		return *this;
	}
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

template<class T>
inline	bool	NPListPackSaveLoad<T>::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(T *a=GetFirst();a!=NULL;a=a->GetNext()){
		NPListSaveLoad<T>	*k=(NPListSaveLoad<T> *)a;
		if(k->Save(f)==false){
			return false;
		}
	}
	return true;
}
	
template<class T>
inline	bool	NPListPackSaveLoad<T>::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		T	*a=Create();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		AppendListItem(a);
	}
return true;
}

template<class T>
inline	void	NPListPackSaveLoad<T>::AppendListItem(T *additem)
{
	AppendList(additem);
}
template<class T>
inline	bool	NPListPackSaveLoad<T>::Append(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		T	*a=Create();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		AppendListItem(a);
	}
	return true;
}

template<class T>	
inline	NPListPackSaveLoad<T>	&NPListPackSaveLoad<T>::operator=(NPListPackSaveLoad<T> &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
template<class T>	
inline	NPListPackSaveLoad<T>	&NPListPackSaveLoad<T>::operator=(const NPListPackSaveLoad<T> &src)
{
	RemoveAll();
	operator+=(*(NPListPackSaveLoad<T> *)&src);
	return *this;
}

template<class T>
inline	NPListPackSaveLoad<T>	&NPListPackSaveLoad<T>::operator+=(NPListPackSaveLoad<T> &src)
{
	for(T *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		T	*d=Create();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(s->Save(&Buff)==false){
			return *this;
		}
		Buff.seek(0);
		d->Load(&Buff);
		AppendListItem(d);
	}
	return *this;
}