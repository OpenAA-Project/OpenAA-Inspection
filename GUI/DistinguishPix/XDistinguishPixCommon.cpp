#include "XDistinguishPixCommon.h"
#include "XGeneralFunc.h"

FileListLeaf::FileListLeaf(void)
{
	Judgement=0;
}

bool	FileListLeaf::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,UFolderName)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Judgement)==false)
		return false;
	return true;
}
bool	FileListLeaf::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,UFolderName)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Judgement)==false)
		return false;
	return true;
}

FileListLeaf	*FileListContainer::Find(const QString &UFolderName,const QString &FileName)
{
	for(FileListLeaf *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->UFolderName==UFolderName && a->FileName==FileName){
			return a;
		}
	}
	return NULL;
}

bool	FileListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;

	for(FileListLeaf *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	FileListContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N=GetCount();
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		FileListLeaf	*a=new FileListLeaf();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}