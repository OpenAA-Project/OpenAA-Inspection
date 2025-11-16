#include "XTypeDef.h"
#include <cmath>
#include"XUndo.h"
#include"XDataInLayer.h"
#include"XDataAlgorithm.h"
#include"XGUIFormBase.h"

UndoChainObject::UndoChainObject(LayersBase *base)
:ServiceForLayers(base)
{
	Buff.open(QIODevice::ReadWrite);
}

UndoTopic::UndoTopic(const QString &_UndoTopicMessage,int idForUndo)
{
	IDForUndo			=idForUndo;
	UndoTopicMessage	=_UndoTopicMessage;
}
UndoTopic::~UndoTopic(void)
{
	FuncUndo.RemoveAll();
}
void	UndoTopic::ExecuteUndo(void)
{
	for(UndoChainObject *a=FuncUndo.GetLast();a!=NULL;a=a->GetPrev()){
		a->Buff.seek(0);
		a->UndoExecute(&a->Buff);
	}
}

void	UndoTopic::ExecuteRedo(void)
{
	for(UndoChainObject *a=FuncUndo.GetFirst();a!=NULL;a=a->GetNext()){
		a->Buff.seek(0);
		a->RedoExecute(&a->Buff);
	}
}
//=============================================================================
UndoAlgorithmItemRoot::UndoAlgorithmItemRoot(AlgorithmItemRoot *Item,AlgorithmParentFromItem *parent ,FPFUNC fpfunc)
:UndoChainObject(Item->GetLayersBase())
{
	Parent=parent;
	m_Undofunc=fpfunc;
	ItemID			=Item->GetID();
	ItemClassType	=Item->GetItemClassType();
}

bool UndoAlgorithmItemRoot::UndoExecute(QIODevice *f)
{
	AlgorithmItemRoot	*Item=Parent->SearchIDItem(ItemID);
	if(Item!=NULL){
		(Item->*m_Undofunc)(f);
	}
	else{
		AlgorithmItemRoot	*LItem=Parent->CreateItem(ItemClassType);
		Parent->AppendItem(LItem);
		LItem->SetParentVirtual(Parent);
		(LItem->*m_Undofunc)(f);
	}
	return true;
}

//=============================================================================
UndoAlgorithmLayer::UndoAlgorithmLayer(AlgorithmInLayerRoot *_ThisInst ,FPFUNC fpfunc)
:UndoChainObject(_ThisInst->GetLayersBase())
{
	ThisInst=_ThisInst;
	m_Undofunc=fpfunc;
}

bool UndoAlgorithmLayer::UndoExecute(QIODevice *f)
{
	if(ThisInst!=NULL){
		(ThisInst->*m_Undofunc)(f);
	}
	return true;
}
//=============================================================================
UndoAlgorithmPage::UndoAlgorithmPage(AlgorithmInPageRoot *_ThisInst ,FPFUNC fpfunc)
:UndoChainObject(_ThisInst->GetLayersBase())
{
	ThisInst=_ThisInst;
	m_Undofunc=fpfunc;
}

bool UndoAlgorithmPage::UndoExecute(QIODevice *f)
{
	if(ThisInst!=NULL){
		(ThisInst->*m_Undofunc)(f);
	}
	return true;
}
//=============================================================================
UndoDataInLayer::UndoDataInLayer(DataInLayer *_ThisInst ,FPFUNC fpfunc)
:UndoChainObject(_ThisInst->GetLayersBase())
{
	ThisInst=_ThisInst;
	m_Undofunc=fpfunc;
}

bool UndoDataInLayer::UndoExecute(QIODevice *f)
{
	if(ThisInst!=NULL){
		(ThisInst->*m_Undofunc)(f);
	}
	return true;
}
//=============================================================================
UndoDataInPage::UndoDataInPage(DataInPage *_ThisInst ,FPFUNC fpfunc)
:UndoChainObject(_ThisInst->GetLayersBase())
{
	ThisInst=_ThisInst;
	m_Undofunc=fpfunc;
}

bool UndoDataInPage::UndoExecute(QIODevice *f)
{
	if(ThisInst!=NULL){
		(ThisInst->*m_Undofunc)(f);
	}
	return true;
}

//=============================================================================

UndoStocker::UndoStocker(LayersBase *base)
	:ServiceForLayers(base)
{
	IDBase=0;
	CurrentTopic=NULL;
}

UndoStocker::~UndoStocker(void)
{	
	MutexAboutUndoTopic.lock();
	RemoveAll();
	MutexAboutUndoTopic.unlock();
	CurrentTopic=NULL;
}
void	UndoStocker::SetElementToNewTopic(UndoChainObject *elem)
{
	UndoTopic	*L=GetCurrentTopic();
	if(L!=NULL){
		MutexAboutUndoTopic.lock();
		L->Add(elem);
		MutexAboutUndoTopic.unlock();
	}
}


int32	UndoStocker::SetNewTopic(const QString &UndoTopicMessage)
{
	MutexAboutUndoTopic.lock();
	int N=GetCount();
	while((N+1)>=GetParamGlobal()->MaxUndoCount){
		UndoTopic	*L=GetFirst();
		RemoveList(L);
		delete	L;
		N--;
	}
	if(CurrentTopic!=NULL){
		UndoTopic	*L;
		while((L=CurrentTopic->GetNext())!=NULL){
			RemoveList(L);
			delete	L;
		}
	}
	UndoTopic	*L=new UndoTopic(UndoTopicMessage,IDBase);
	IDBase++;
	AppendList(L);
	CurrentTopic=L;
	MutexAboutUndoTopic.unlock();

	return L->GetIDForUndo();
}
void		UndoStocker::SetLocalTopic(int idForUndo)
{
	UndoTopic	*L=SearchTopic(idForUndo);
	if(L==NULL){
		L=new UndoTopic(/**/"",idForUndo);

		MutexAboutUndoTopic.lock();
		AppendList(L);
		CurrentTopic=L;
		IDBase=0;
		for(UndoTopic	*a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetIDForUndo()>IDBase){
				IDBase=a->GetIDForUndo();
			}
		}
		IDBase++;
		MutexAboutUndoTopic.unlock();
	}
	else{
		CurrentTopic=L;
	}
}

UndoTopic	*UndoStocker::SearchTopic(int idForUndo)
{
	MutexAboutUndoTopic.lock();
	for(UndoTopic *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetIDForUndo()==idForUndo){
			MutexAboutUndoTopic.unlock();
			return a;
		}
	}
	MutexAboutUndoTopic.unlock();
	return NULL;
}

UndoTopic	*UndoStocker::ExecuteUndo(void)
{
	if(CurrentTopic!=NULL){
		UndoTopic	*L=SearchTopic(CurrentTopic->GetIDForUndo());
		if(L!=NULL){
			L->ExecuteUndo();
			CurrentTopic=CurrentTopic->GetPrev();
			return L;
		}
	}
	return NULL;
}

UndoTopic	*UndoStocker::ExecuteRedo(void)
{
	if(CurrentTopic!=NULL){
		UndoTopic	*L=SearchTopic(CurrentTopic->GetIDForUndo());
		if(L!=NULL){
			L->ExecuteRedo();
			CurrentTopic=CurrentTopic->GetPrev();
			return L;
		}
	}
	return NULL;
}

UndoTopic	*UndoStocker::UndoInMaster(void)
{
	if(CurrentTopic!=NULL){
		UndoTopic	*L=CurrentTopic;
		CurrentTopic=CurrentTopic->GetPrev();
		return L;
	}
	return NULL;
}

UndoTopic	*UndoStocker::RedoInMaster(void)
{
	if(CurrentTopic!=NULL && CurrentTopic->GetNext()!=NULL){
		CurrentTopic=CurrentTopic->GetNext();
		return CurrentTopic;
	}
	else if(CurrentTopic==NULL && GetCount()!=0){
		CurrentTopic=GetFirst();
		return CurrentTopic;
	}
	return NULL;
}
