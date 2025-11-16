/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLearningRule.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XLearningRule.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"

void	LearningRegList::AddDiv(void)
{
	switch(DataType){
		case _LearnReg_BYTE:
			*((BYTE *)Data) +=(BYTE)CurrentDiv;
			break;
		case _LearnReg_WORD:
			*((WORD *)Data) +=(WORD)CurrentDiv;
			break;
		case _LearnReg_DWORD:
			*((DWORD *)Data) +=(DWORD)CurrentDiv;
			break;
		case _LearnReg_int16:
			*((int16 *)Data) +=(int16)CurrentDiv;
			break;
		case _LearnReg_int32:
			*((int32 *)Data) +=(int32)CurrentDiv;
			break;
		case _LearnReg_int64:
			*((int64 *)Data) +=(int64)CurrentDiv;
			break;
		case _LearnReg_bool:
			if(fabs(CurrentDiv)>0.5){
				*((bool *)Data) =(*((bool *)Data)==true)?false:true;
			}
			break;
		case _LearnReg_double:
			*((double *)Data) +=(double)CurrentDiv;
			break;
		case _LearnReg_float:
			*((float *)Data) +=(float)CurrentDiv;
			break;
		default:
			break;
	}
}
void	LearningRegList::SubDiv(void)
{
	switch(DataType){
		case _LearnReg_BYTE:
			*((BYTE *)Data) -=(BYTE)CurrentDiv;
			break;
		case _LearnReg_WORD:
			*((WORD *)Data) -=(WORD)CurrentDiv;
			break;
		case _LearnReg_DWORD:
			*((DWORD *)Data) -=(DWORD)CurrentDiv;
			break;
		case _LearnReg_int16:
			*((int16 *)Data) -=(int16)CurrentDiv;
			break;
		case _LearnReg_int32:
			*((int32 *)Data) -=(int32)CurrentDiv;
			break;
		case _LearnReg_int64:
			*((int64 *)Data) -=(int64)CurrentDiv;
			break;
		case _LearnReg_bool:
			if(fabs(CurrentDiv)>0.5){
				*((bool *)Data) =(*((bool *)Data)==true)?false:true;
			}
			break;
		case _LearnReg_double:
			*((double *)Data) -=(double)CurrentDiv;
			break;
		case _LearnReg_float:
			*((float *)Data) -=(float)CurrentDiv;
			break;
		default:
			break;
	}
}
void	LearningRegList::Change(double DifResult)
{
	switch(DataType){
		case _LearnReg_BYTE:
			*((BYTE *)Data) +=(BYTE)(CurrentDiv*DifResult);
			break;
		case _LearnReg_WORD:
			*((WORD *)Data) +=(WORD)(CurrentDiv*DifResult);
			break;
		case _LearnReg_DWORD:
			*((DWORD *)Data) +=(DWORD)(CurrentDiv*DifResult);
			break;
		case _LearnReg_int16:
			*((int16 *)Data) +=(int16)(CurrentDiv*DifResult);
			break;
		case _LearnReg_int32:
			*((int32 *)Data) +=(int32)(CurrentDiv*DifResult);
			break;
		case _LearnReg_int64:
			*((int64 *)Data) +=(int64)(CurrentDiv*DifResult);
			break;
		case _LearnReg_bool:
			if(fabs(CurrentDiv*DifResult)>0.5){
				*((bool *)Data) =(*((bool *)Data)==true)?false:true;
			}
			break;
		case _LearnReg_double:
			*((double *)Data) +=(double)(CurrentDiv*DifResult);
			break;
		case _LearnReg_float:
			*((float *)Data) +=(float)(CurrentDiv*DifResult);
			break;
		default:
			break;
	}
	Changed=true;
}
void	LearningRegList::ChangeDiv(void)
{
	CurrentDiv=CurrentDiv/2.0;
}
void	LearningRegList::Set(BYTE *data	,BYTE _MinData	,BYTE _MaxData	,BYTE _DivData)
{
	Data=data;
	DataType=_LearnReg_BYTE;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(WORD *data	,WORD _MinData	,WORD _MaxData	,WORD _DivData)
{
	Data=data;
	DataType=_LearnReg_WORD;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(DWORD *data,DWORD _MinData	,DWORD _MaxData	,DWORD _DivData)
{
	Data=data;
	DataType=_LearnReg_DWORD;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(int16 *data,int16 _MinData	,int16 _MaxData	,int16 _DivData)
{
	Data=data;
	DataType=_LearnReg_int16;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(int32 *data,int32 _MinData	,int32 _MaxData	,int32 _DivData)
{
	Data=data;
	DataType=_LearnReg_int32;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(int64 *data,int64 _MinData	,int64 _MaxData	,int64 _DivData)
{
	Data=data;
	DataType=_LearnReg_int64;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(bool *data)
{
	Data=data;
	DataType=_LearnReg_bool;
}
void	LearningRegList::Set(double *data,double _MinData ,double _MaxData ,double _DivData)
{
	Data=data;
	DataType=_LearnReg_double;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}
void	LearningRegList::Set(float *data,float _MinData	,float _MaxData	,float _DivData)
{
	Data=data;
	DataType=_LearnReg_float;
	MinData	=_MinData;
	MaxData	=_MaxData;
	DivData	=_DivData;
}

int		LearningRegList::GetDataByte(void)
{
	switch(DataType){
		case _LearnReg_BYTE:
			return sizeof(BYTE);
		case _LearnReg_WORD:
			return sizeof(WORD);
		case _LearnReg_DWORD:
			return sizeof(DWORD);
		case _LearnReg_int16:
			return sizeof(int16);
		case _LearnReg_int32:
			return sizeof(int32);
		case _LearnReg_int64:
			return sizeof(int64);
		case _LearnReg_bool:
			return sizeof(bool);
		case _LearnReg_double:
			return sizeof(double);
		case _LearnReg_float:
			return sizeof(float);
		default:
			break;
	}
	return 0;
}


bool	LearningRegList::Save(LearningLeafForSave *f)
{
	f->DataType	=DataType;
	f->Name		=Name;
	switch(DataType){
		case _LearnReg_BYTE:
			*((BYTE *)f->Data)	=*((BYTE *)(Data));
			break;
		case _LearnReg_WORD:
			*((WORD *)f->Data)	=*((WORD *)(Data));
			break;
		case _LearnReg_DWORD:
			*((DWORD *)f->Data) =*((DWORD *)(Data));
			break;
		case _LearnReg_int16:
			*((int16 *)f->Data) =*((int16 *)(Data));
			break;
		case _LearnReg_int32:
			*((int32 *)f->Data) =*((int32 *)(Data));
			break;
		case _LearnReg_int64:
			*((int64 *)f->Data) =*((int64 *)(Data));
			break;
		case _LearnReg_bool:
			*((bool *)f->Data)	=*((bool *)(Data));
			break;
		case _LearnReg_double:
			*((double *)f->Data)=*((double *)(Data));
			break;
		case _LearnReg_float:
			*((float *)f->Data) =*((float *)(Data));
			break;
		default:
			break;
	}
	return true;
}
bool	LearningRegList::Load(LearningLeafForSave *f)
{
	DataType	=f->DataType;
	Name		=f->Name;
	switch(DataType){
		case _LearnReg_BYTE:
			*((BYTE *)Data)	=*((BYTE *)(f->Data));
			break;
		case _LearnReg_WORD:
			*((WORD *)Data)	=*((WORD *)(f->Data));
			break;
		case _LearnReg_DWORD:
			*((DWORD *)Data) =*((DWORD *)(f->Data));
			break;
		case _LearnReg_int16:
			*((int16 *)Data) =*((int16 *)(f->Data));
			break;
		case _LearnReg_int32:
			*((int32 *)Data) =*((int32 *)(f->Data));
			break;
		case _LearnReg_int64:
			*((int64 *)Data) =*((int64 *)(f->Data));
			break;
		case _LearnReg_bool:
			*((bool *)Data)	=*((bool *)(f->Data));
			break;
		case _LearnReg_double:
			*((double *)Data)=*((double *)(f->Data));
			break;
		case _LearnReg_float:
			*((float *)Data) =*((float *)(f->Data));
			break;
		default:
			break;
	}
	return true;
}

bool	LearningRegList::IsMatchingLeaf(LearningRegList *s)
{
	if(Name==s->Name && DataType==s->DataType){
		return true;
	}
	return false;
}

//---------------------------------------------------------------------
LearningRegListByLib::LearningRegListByLib(void)
{
	LibType=-1;
	LibID	=-1;
}

bool	LearningRegListByLib::Delete(LearningValueBase *data)
{
	for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetBase()==data){
			LearningRegDats.RemoveList(L);
			delete	L;
			return true;
		}
	}
	return false;
}
void	LearningRegListByLib::InitialChanged(void)
{
	for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialChanged();
	}
}
void	LearningRegListByLib::InitialTotal(void)
{
	for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialTotal();
	}
}
void	LearningRegListByLib::AddDiv(LearningRegList *v)
{
	if(LibType!=-1 || LibID!=-1){
		for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
			if((L==v || L->Name==v->Name) && L->Changed==false){
				L->AddDiv();
			}
		}
	}
	else{
		v->AddDiv();
	}
}
void	LearningRegListByLib::SubDiv(LearningRegList *v)
{
	if(LibType!=-1 || LibID!=-1){
		for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
			if((L==v || L->Name==v->Name) && L->Changed==false){
				L->SubDiv();
			}
		}
	}
	else{
		v->SubDiv();
	}
}
void	LearningRegListByLib::Change(LearningRegList *v,double DifResult)
{
	if(LibType!=-1 || LibID!=-1){
		for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
			if((L==v || L->Name==v->Name) && L->Changed==false){
				L->Change(DifResult);
			}
		}
	}
	else{
		v->Change(DifResult);
	}
}
void	LearningRegListByLib::ChangeDiv(void)
{
	for(LearningRegList *L=LearningRegDats.GetFirst();L!=NULL;L=L->GetNext()){
		L->ChangeDiv();
	}
}
LearningRegList	*LearningRegListByLib::GetNextValue(LearningRegList *C)
{
	while(C!=NULL){
		if(C->Changed==false){
			return C;
		}
		C=C->GetNext();
	}
	return NULL;
}

void	LearningRegListByLib::Set(LearningValueBase  *Base,const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,bool *data)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,double *data	,double MinData ,double MaxData ,double DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}
void	LearningRegListByLib::Set(LearningValueBase *Base,const QString &Name,float *data	,float MinData	,float MaxData	,float DivData)
{
	LearningRegList	*L=new LearningRegList(Name,Base);
	L->Set(data,MinData,MaxData,DivData);
	LearningRegDats.AppendList(L);
}

bool	LearningRegListByLib::Save(LearningLeafForSaveContainer &LearnedDatabase)
{
	for(LearningRegList *c=LearningRegDats.GetFirst();c!=NULL;c=c->GetNext()){
		bool	Found=false;
		for(LearningLeafForSave *s=LearnedDatabase.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->LibType==LibType && s->LibID==LibID && s->Name==c->Name){
				c->Save(s);
				Found=true;
				break;
			}
		}
		if(Found==true){
			LearningLeafForSave	*d=new LearningLeafForSave();
			d->LibType	=LibType;
			d->LibID	=LibID;
			c->Save(d);
			LearnedDatabase.AppendList(d);
		}
	}
	return true;
}

bool	LearningRegListByLib::Load(LearningLeafForSaveContainer &LearnedDatabase)
{
	bool	Ret = true;
	for(LearningRegList *c=LearningRegDats.GetFirst();c!=NULL;c=c->GetNext()){
		for(LearningLeafForSave *s=LearnedDatabase.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->LibType==LibType && s->LibID==LibID && s->Name==c->Name){
				if (c->Load(s) == false){
					Ret = false;
				}
				break;
			}
		}
	}
	return Ret;
}

bool	LearningRegListByLib::IsMatching(LearningRegListByLib *src)
{
	if(LibType==-1 && LibID==-1){
		return true;
	}
	if(LibType==src->LibType && LibID==src->LibID){
		return true;
	}
	return false;
}

//---------------------------------------------------------------------

void	LearningRegListContainer::Delete(LearningValueBase *data)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Delete(data)==true){
			if(L->LearningRegDats.GetFirst()==NULL){
				RemoveList(L);
				delete	L;
			}
			return;
		}
	}	
}

void	LearningRegListContainer::InitialChanged(void)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialChanged();
	}
}
void	LearningRegListContainer::InitialTotal(void)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialTotal();
	}
}
void	LearningRegListContainer::ChangeDiv(void)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->ChangeDiv();
	}
}

void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, bool *data)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, double *data	,double MinData ,double MaxData ,double DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}
void	LearningRegListContainer::Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, float *data	,float MinData	,float MaxData	,float DivData)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LibType==LibType && L->LibID==LibID){
			L->Set(Base,Name,data	,MinData,MaxData,DivData);
			return;
		}
	}
	LearningRegListByLib	*LL=new LearningRegListByLib();
	LL->LibType	=LibType;
	LL->LibID	=LibID;
	LL->Set(Base,Name,data	,MinData,MaxData,DivData);
	AppendList(LL);
}

void	LearningRegListContainer::BuildPlan(LearningPlanBase &Plan)
{
	Plan.InitialTop();
	InitialChanged();
	Plan.CurrentLib=GetFirst();
	if(Plan.CurrentLib!=NULL){
		Plan.CurrentValue=Plan.CurrentLib->LearningRegDats.GetFirst();
	}
}

bool	LearningRegListContainer::Save(LearningLeafForSaveContainer &LearnedDatabase)
{
	for(LearningRegListByLib *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(LearnedDatabase)==false){
			return false;
		}
	}
	return true;
}
bool	LearningRegListContainer::Load(LearningLeafForSaveContainer &LearnedDatabase)
{
	for(LearningRegListByLib *dst=GetFirst();dst!=NULL;dst=dst->GetNext()){
		if(dst->Load(LearnedDatabase)==true){
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------
LearningPlanBase::LearningPlanBase(LayersBase *base)
:ServiceForLayers(base)
{
	MaxLoopCount=10;
	InitialTop();
}

void	LearningPlanBase::InitialTop(void)
{
	CurrentLib	=NULL;
	CurrentValue=NULL;
	ResultList.RemoveAll();
}

void	LearningPlanBase::ExecuteTotalLoop(void)
{
	ExeLowLevelTotalFirst();

	for(int i=0;i<MaxLoopCount;i++){
		ExeLowLevelLoopFirst();
		ExeLowLevelLoopContent();
	}
}

void	LearningPlanBase::ExecuteOneLoop(void)
{
	ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
	if(CurrentResult!=NULL){
		double	FirstResult=GetResult(*CurrentResult);
		ResultList.Add(FirstResult);

		while(CurrentLib!=NULL && CurrentValue!=NULL){
			CurrentLib->AddDiv(CurrentValue);
			ExecuteOneValue();
			double	d=GetResult(*CurrentResult);
			CurrentLib->SubDiv(CurrentValue);
			CurrentLib->Change(CurrentValue,-(d-FirstResult));

			CurrentValue=CurrentLib->GetNextValue(CurrentValue);
			if(CurrentValue==NULL){
				CurrentLib=CurrentLib->GetNext();
				if(CurrentLib!=NULL){
					CurrentValue=CurrentLib->LearningRegDats.GetFirst();
				}
			}
		}
	}
}
void	LearningPlanBase::ExecuteOneValue(void)
{
	GetLayersBase()->SetCurrentInspectID(0);
	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());
	int	TempStrategy=GetParamGlobal()->GetMaxScanStrategy();
	GetLayersBase()->GetParamGlobal()->SetMaxScanStrategy(1);

	XDateTime	NowD=GetLayersBase()->GetStartInspectTime();
	//GetLayersBase()->SetStartTimeForInspection(NowD);

	GetLayersBase()->ExecuteStartByInspection	(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecutePreAlignment		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecuteAlignment			(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecutePreProcessing		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->ExecuteProcessing			(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->SetShouldWriteResult(false);
	GetLayersBase()->ExecutePostProcessing		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->SetShouldWriteResult(true);

	GetLayersBase()->GetParamGlobal()->SetMaxScanStrategy(TempStrategy);
}

void	LearningPlanBase::ExeLowLevelTotalFirst(void)
{
	GetLayersBase()->GetLearningRegData()->InitialTotal();
	InitialTop();
}
void	LearningPlanBase::ExeLowLevelLoopFirst(void)
{
	GetLayersBase()->GetLearningRegData()->InitialChanged();
	CurrentLib=GetLayersBase()->GetLearningRegData()->GetFirst();
	if(CurrentLib!=NULL){
		CurrentValue=CurrentLib->LearningRegDats.GetFirst();
	}
	ExecuteOneValue();
}
void	LearningPlanBase::ExeLowLevelLoopContent(void)
{
	ExecuteOneLoop();
	GetLayersBase()->GetLearningRegData()->ChangeDiv();
}

//---------------------------------------------------------------------
LearningLeafForSave::~LearningLeafForSave(void)
{
	ReleaseData();
}

void	LearningLeafForSave::ReleaseData(void)
{
	if(Data!=NULL){
		if(DataType==LearningRegList::_LearnReg_Nothing	){
			Data=NULL;
		}
		else if(DataType==LearningRegList::_LearnReg_BYTE	){
			BYTE	*p=(BYTE *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_WORD	){
			WORD	*p=(WORD *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_DWORD	){
			DWORD	*p=(DWORD *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_int16	){
			int16	*p=(int16 *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_int32	){
			int32	*p=(int32 *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_int64	){
			int64	*p=(int64 *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_bool	){
			bool	*p=(bool *)Data;
			delete	p;
		}
		else if(DataType==LearningRegList::_LearnReg_double	){
			double	*p=(double *)Data;
			delete	p;		}
		else if(DataType==LearningRegList::_LearnReg_float	){
			float	*p=(float *)Data;
			delete	p;
		}
		Data=NULL;
	}
}
bool	LearningLeafForSave::Save(QIODevice *f)
{
	BYTE	H=(BYTE)DataType;
	if(::Save(f,H)==false){
		return false;
	}
	if(::Save(f,Name)==false){
		return false;
	}
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(f->write((const char *)Data,GetDataByte())!=GetDataByte()){
		return false;
	}
	return true;
}

bool	LearningLeafForSave::Load(QIODevice *f)
{
	ReleaseData();

	BYTE	H;
	if(::Load(f,H)==false){
		return false;
	}
	DataType=(LearningRegList::_DataType)H;

	if(::Load(f,Name)==false){
		return false;
	}

	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}

	BYTE	*p=new BYTE[GetDataByte()];
	Data=p;
	if(f->read((char *)Data,GetDataByte())!=GetDataByte()){
		return false;
	}
	return true;
}

LearningLeafForSave	&LearningLeafForSave::operator=(LearningLeafForSave &src)
{
	ReleaseData();

	DataType	=src.DataType;
	Name		=src.Name;
	LibType		=src.LibType;
	LibID		=src.LibID;

	BYTE	*p=new BYTE[GetDataByte()];
	memcpy(p,src.Data,GetDataByte());
	Data=p;
	return *this;
}

int		LearningLeafForSave::GetDataByte(void)
{
	switch(DataType){
		case LearningRegList::_LearnReg_BYTE:
			return sizeof(BYTE);
		case LearningRegList::_LearnReg_WORD:
			return sizeof(WORD);
		case LearningRegList::_LearnReg_DWORD:
			return sizeof(DWORD);
		case LearningRegList::_LearnReg_int16:
			return sizeof(int16);
		case LearningRegList::_LearnReg_int32:
			return sizeof(int32);
		case LearningRegList::_LearnReg_int64:
			return sizeof(int64);
		case LearningRegList::_LearnReg_bool:
			return sizeof(bool);
		case LearningRegList::_LearnReg_double:
			return sizeof(double);
		case LearningRegList::_LearnReg_float:
			return sizeof(float);
		default:
			break;
	}
	return 0;
}

bool	LearningLeafForSaveContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(LearningLeafForSave *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	LearningLeafForSaveContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		LearningLeafForSave *c=new LearningLeafForSave();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}

LearningLeafForSaveContainer	&LearningLeafForSaveContainer::operator=(LearningLeafForSaveContainer &src)
{
	RemoveAll();
	for(LearningLeafForSave *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		LearningLeafForSave *d=new LearningLeafForSave();
		*d=*c;
		AppendList(d);
	}
	return *this;
}

//---------------------------------------------------------------------

LearningValueBase::LearningValueBase(void)
{
	Base=NULL;
}
LearningValueBase::~LearningValueBase(void)
{
	if(GetLayers()!=NULL && GetLayers()->GetLearningRegData()!=NULL){
		GetLayers()->GetLearningRegData()->Delete(this);
	}
}

void	LearningValueInThreshold::Set(const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_BYTE;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_WORD;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_DWORD;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_int16;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_int32;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_int64;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,bool *data)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_bool;
	c->Name=Name;
	c->Data=data;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,double *data	,double MinData ,double MaxData ,double DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_double;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}
void	LearningValueInThreshold::Set(const QString &Name,float *data	,float MinData	,float MaxData	,float DivData)
{
	TmpLearningValueInThreshold	*c=new TmpLearningValueInThreshold();
	c->DataType=LearningRegList::_LearnReg_float;
	c->Name=Name;
	c->Data=data;
	c->MinData=MinData;
	c->MaxData=MaxData;
	c->DivData=DivData;
	TmpPack.AppendList(c);
}

void	LearningValueInThreshold::SetLearn(LayersBase *base)
{
	LearningValueBase::SetLearn(base);
	for(TmpLearningValueInThreshold *c=TmpPack.GetFirst();c!=NULL;c=c->GetNext()){
		switch(c->DataType){
			case LearningRegList::_LearnReg_BYTE:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (BYTE *)c->Data	,(BYTE)c->MinData,(BYTE)c->MaxData,(BYTE)c->DivData);
				break;
			case LearningRegList::_LearnReg_WORD:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (WORD *)c->Data	,(WORD)c->MinData,(WORD)c->MaxData,(WORD)c->DivData);
				break;
			case LearningRegList::_LearnReg_DWORD:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (DWORD *)c->Data,(DWORD)c->MinData,(DWORD)c->MaxData,(DWORD)c->DivData);
				break;
			case LearningRegList::_LearnReg_int16:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (int16 *)c->Data	,(int16)c->MinData,(int16)c->MaxData,(int16)c->DivData);
				break;
			case LearningRegList::_LearnReg_int32:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (int32 *)c->Data	,(int32)c->MinData,(int32)c->MaxData,(int32)c->DivData);
				break;
			case LearningRegList::_LearnReg_int64:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (int64 *)c->Data	,(int64)c->MinData,(int64)c->MaxData,(int64)c->DivData);
				break;
			case LearningRegList::_LearnReg_bool:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (bool *)c->Data);
				break;
			case LearningRegList::_LearnReg_double:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (double *)c->Data	,(double)c->MinData,(double)c->MaxData,(double)c->DivData);
				break;
			case LearningRegList::_LearnReg_float:
				GetLayers()->GetLearningRegData()->Set(this,c->Name,Item->GetParentBase()->GetLibType(),Item->GetLibID(), (float *)c->Data	,(float)c->MinData,(float)c->MaxData,(float)c->DivData);
				break;
			default:
				break;
		}
	}
	TmpPack.RemoveAll();
}


void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, bool *data)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, double *data	,double MinData ,double MaxData ,double DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}
void	LearningValueByLib::Set(const QString &Name,int LibType,int LibID, float *data	,float MinData	,float MaxData	,float DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,LibType,LibID, data	,MinData,MaxData,DivData);
}


void	LearningValueByEach::Set(const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,DWORD *data,DWORD MinData	,DWORD MaxData	,DWORD DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,int16 *data,int16 MinData	,int16 MaxData	,int16 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,int32 *data,int32 MinData	,int32 MaxData	,int32 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,int64 *data,int64 MinData	,int64 MaxData	,int64 DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,bool *data)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data);
}
void	LearningValueByEach::Set(const QString &Name,double *data,double MinData ,double MaxData ,double DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
void	LearningValueByEach::Set(const QString &Name,float *data,float MinData	,float MaxData	,float DivData)
{
	GetLayers()->GetLearningRegData()->Set(this,Name,-1,-1, data	,MinData,MaxData,DivData);
}
