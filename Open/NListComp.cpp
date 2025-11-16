#include "NListComp.h"
#include "XGeneralFuncCore.h"
#include "XTypeDef.h"
#include <QBuffer>

template<class T>
inline	NPListSaveLoad<T>	&NPListSaveLoad<T>::operator=(T &src)
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
inline	void	NPListSaveLoad<T>::____Copy(T &src)
{
	operator=(src);
}

template<class T>
inline	NPListPackSaveLoad<T>::NPListPackSaveLoad(NPListPackSaveLoad<T> &src)
{
	____Add(src);
}

template<class T>
inline	bool	NPListPackSaveLoad<T>::Save(QIODevice *f)
{
    const int32	N=NPListPack<T>::GetCount();
	if(::Save(f,N)==false)
		return false;
    for(T *a=NPListPack<T>::GetFirst();a!=NULL;a=a->GetNext()){
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
    NPListPack<T>::RemoveAll();
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
        NPListPack<T>::AppendList(additem);
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
        NPListPack<T>::RemoveAll();
	____Add(src);
	return *this;
}
template<class T>	
inline	NPListPackSaveLoad<T>	&NPListPackSaveLoad<T>::operator=(const NPListPackSaveLoad<T> &src)
{
        NPListPack<T>::RemoveAll();
	____Add(*(NPListPackSaveLoad<T> *)&src);
	return *this;
}

template<class T>
inline	NPListPackSaveLoad<T>	&NPListPackSaveLoad<T>::operator+=(NPListPackSaveLoad<T> &src)
{
	____Add(src);
	return *this;
}

template<class T>
inline	void	NPListPackSaveLoad<T>::____Add(NPListPackSaveLoad<T> &src)
{
	for(T *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		T	*d=src.Create();
		d->____Copy(*s);
		AppendListItem(d);
	}
}
