#include "ButtonSelectDatabaseResource.h"
#include "XDatabaseList.h"
#include "XGeneralFunc.h"


bool	DatabaseList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false){
		return false;
	}
	if(::Save(f,IP)==false){
		return false;
	}
	if(::Save(f,FileName)==false){
		return false;
	}
	if(::Save(f,PortNo)==false){
		return false;
	}
	return true;
}

bool	DatabaseList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false){
		return false;
	}
	if(::Load(f,IP)==false){
		return false;
	}
	if(::Load(f,FileName)==false){
		return false;
	}
	if(::Load(f,PortNo)==false){
		return false;
	}
	return true;
}

DatabaseListContainer	&DatabaseListContainer::operator=(DatabaseListContainer &src)
{
	RemoveAll();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


bool	DatabaseListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(DatabaseList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	DatabaseListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		DatabaseList *c=new DatabaseList();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}
