#include "XTypeDef.h"
#include "Regulus64System.h"
#include "XMasterData.h"
#include "XGeneralFunc.h"

//====================================================================================
LoadedInfoList::LoadedInfoList(void)
	:ItemCount(0),Error(_None)
{}
LoadedInfoList::LoadedInfoList(const LoadedInfoList &src)
{
	AlgoRoot	=src.AlgoRoot;
	AlgoName	=src.AlgoName;
	FileName	=src.FileName;
	ItemCount	=src.ItemCount;
	Error		=src.Error;
}
LoadedInfoList::~LoadedInfoList(void)
{
}
LoadedInfoList	&LoadedInfoList::operator=(const LoadedInfoList &src)
{
	AlgoRoot	=src.AlgoRoot;
	AlgoName	=src.AlgoName;
	FileName	=src.FileName;
	ItemCount	=src.ItemCount;
	Error		=src.Error;
	return *this;
}
bool	LoadedInfoList::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,FileName)==false){
		return false;
	}
	if(::Load(f,ItemCount)==false){
		return false;
	}
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	Error=(LoadedStatus)d;
	return true;
}

bool	LoadedInfoList::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,FileName)==false){
		return false;
	}
	if(::Save(f,ItemCount)==false){
		return false;
	}
	BYTE	d=(BYTE)Error;
	if(::Save(f,d)==false){
		return false;
	}
	return true;
}

LoadedInfoContainerInPhase::~LoadedInfoContainerInPhase(void)
{
}
LoadedInfoContainerInPhase::LoadedInfoContainerInPhase(const LoadedInfoContainerInPhase &src)
{
	for(LoadedInfoList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LoadedInfoList	*d=new LoadedInfoList(*s);
		AppendList(d);
	}
	Phase	=src.Phase;
	SuccessForImage	=src.SuccessForImage;
}
LoadedInfoContainerInPhase	&LoadedInfoContainerInPhase::operator=(const LoadedInfoContainerInPhase &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((LoadedInfoContainerInPhase *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	LoadedInfoContainerInPhase::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,SuccessForImage)==false){
		return false;
	}

	int32	N=GetCount();
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		LoadedInfoList *a=new LoadedInfoList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}
bool	LoadedInfoContainerInPhase::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,SuccessForImage)==false){
		return false;
	}

	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(LoadedInfoList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
LoadedInfoContainerInPhaseList::LoadedInfoContainerInPhaseList(const LoadedInfoContainerInPhaseList &src)
:LoadedInfoContainerInPhase(src)
{
}
LoadedInfoContainerInPhaseList::~LoadedInfoContainerInPhaseList(void)
{
}
LoadedInfoContainerInPhaseList	&LoadedInfoContainerInPhaseList::operator=(const LoadedInfoContainerInPhaseList &src)
{
	LoadedInfoContainerInPhase::operator=(*((LoadedInfoContainerInPhase *)&src));
	return *this;
}
LoadedInfoContainer::LoadedInfoContainer(const LoadedInfoContainer &src)
{
	for(LoadedInfoContainerInPhaseList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		LoadedInfoContainerInPhaseList	*d=new LoadedInfoContainerInPhaseList(*s);
		AppendList(d);
	}
}
LoadedInfoContainer::~LoadedInfoContainer(void)
{
}
LoadedInfoContainer	&LoadedInfoContainer::operator=(const LoadedInfoContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((LoadedInfoContainer *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}
bool	LoadedInfoContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		LoadedInfoContainerInPhaseList *a=new LoadedInfoContainerInPhaseList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	LoadedInfoContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(LoadedInfoContainerInPhaseList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
