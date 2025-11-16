#include "XAutoSaveImage.h"
#include "XGeneralFunc.h"
#include <QBuffer>

bool	BandImageFileList::Load(QIODevice *f)
{
	if(::Load(f,BaseFileName)==false)
		return false;
	if(::Load(f,EachFileNames)==false)
		return false;
	return true;
}
bool	BandImageFileList::Save(QIODevice *f)
{
	if(::Save(f,BaseFileName)==false)
		return false;
	if(::Save(f,EachFileNames)==false)
		return false;
	return true;
}

BandImageFileList	&BandImageFileList::operator=(BandImageFileList &src)
{
	BaseFileName	=src.BaseFileName;
	EachFileNames	=src.EachFileNames;
	return *this;
}

bool	BandImageFileContainer::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		BandImageFileList	*L=new BandImageFileList();
		if(L->Load(f)==false)
			return false;
		AppendList(L);
	}
	return true;
}
bool	BandImageFileContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(BandImageFileList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}

BandImageFileContainer	&BandImageFileContainer::operator=(BandImageFileContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}