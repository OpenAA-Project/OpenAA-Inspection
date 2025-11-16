#include "XLoadRelease.h"
#include "XGeneralFunc.h"
	
bool	LoadReleaseAlgoList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,Releaseable)==false)
		return false;
	return true;
}
	
bool	LoadReleaseAlgoList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,Releaseable)==false)
		return false;
	return true;
}


LoadReleaseAlgoContainer::LoadReleaseAlgoContainer(void)
{
	ReleaseableMasterBuff	=false;
	ReleaseableTargetBuff	=false;
}

LoadReleaseAlgoList	*LoadReleaseAlgoContainer::Create(void)
{
	return new LoadReleaseAlgoList();
}

bool	LoadReleaseAlgoContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ReleaseableMasterBuff)==false)
		return false;
	if(::Save(f,ReleaseableTargetBuff)==false)
		return false;
	if(NPListPackSaveLoad<LoadReleaseAlgoList>::Save(f)==false)
		return false;
	return true;
}
bool	LoadReleaseAlgoContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ReleaseableMasterBuff)==false)
		return false;
	if(::Load(f,ReleaseableTargetBuff)==false)
		return false;
	if(NPListPackSaveLoad<LoadReleaseAlgoList>::Load(f)==false)
		return false;
	return true;
}

