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