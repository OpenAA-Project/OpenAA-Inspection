#include "XPIOSignal.h"
#include "XGeneralFunc.h"

bool	SignalOne::Save(QIODevice *f)
{
	if(::Save(f,MicroSec)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}
bool	SignalOne::Load(QIODevice *f)
{
	if(::Load(f,MicroSec)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}

SignalData::SignalData(void)
{
	SignalDatas	=NULL;
	AllocCount	=0;
	CurrentPoint=0;
}
SignalData::~SignalData(void)
{
	if(SignalDatas!=NULL){
		delete	[]SignalDatas;
		SignalDatas=NULL;
	}
	AllocCount	=0;
	CurrentPoint=0;
}

void	SignalData::Alloc(int Count)
{
	if(SignalDatas!=NULL){
		delete	[]SignalDatas;
	}
	AllocCount	=Count;
	SignalDatas=new SignalOne[AllocCount];
	CurrentPoint=0;
}
void	SignalData::Reset(void)
{
	CurrentPoint=0;
}
void	SignalData::Set(DWORD _MicroSec ,bool data)
{
	if(CurrentPoint<AllocCount && SignalDatas!=NULL){
		SignalDatas[CurrentPoint].Set(_MicroSec ,data);
		CurrentPoint++;
	}
}
DWORD	SignalData::GetLastMilisec(void)
{
	if(CurrentPoint>0){
		return SignalDatas[CurrentPoint-1].MicroSec;
	}
	return 0;
}

SignalOne	*SignalData::GetSignalOnePointer(DWORD LaterMilisec ,int &Count)
{
	int	Index=-1;
	for(int i=0;i<CurrentPoint;i++){
		if(SignalDatas[i].MicroSec<LaterMilisec){
			Index=i;
		}
		else{
			if(Index>=0){
				Count=CurrentPoint-Index;
				return &SignalDatas[Index];
			}
			else{
				Count=CurrentPoint-i;
				return &SignalDatas[i];
			}
		}
	}
	if(Index>=0){
		Count=CurrentPoint-Index;
		return &SignalDatas[Index];
	}
	return NULL;
}

bool	SignalData::Save(QIODevice *f)
{
	if(::Save(f,AllocCount)==false)
		return false;
	if(::Save(f,CurrentPoint)==false)
		return false;

	for(int i=0;i<CurrentPoint;i++){
		if(SignalDatas[i].Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	SignalData::Load(QIODevice *f)
{
	if(::Load(f,AllocCount)==false)
		return false;
	if(::Load(f,CurrentPoint)==false)
		return false;
	if(SignalDatas!=NULL){
		delete	[]SignalDatas;
	}
	SignalDatas=new SignalOne[AllocCount];

	for(int i=0;i<CurrentPoint;i++){
		if(SignalDatas[i].Load(f)==false){
			return false;
		}
	}
	return true;
}