#include "XDataAlgorithm.h"
#include "XDataAlgorithmList.h"


AlgorithmItemPointerList::AlgorithmItemPointerList(AlgorithmItemRoot *item)
	:Pointer(item)
{
	if(Pointer!=NULL){
		ID=Pointer->GetID();
	}
	else{
		ID=-1;
	}
}
	
bool	AlgorithmItemPointerList::Save(QIODevice *f)
{
	const bool	b=(Pointer!=NULL)?true:false;
	if(::Save(f,b)==false)
		return false;
	if(b==true){
		ID=Pointer->GetID();
		if(::Save(f,ID)==false)
			return false;
	}
	return true;
}

bool	AlgorithmItemPointerList::Load(QIODevice *f)
{
	bool	b;
	if(::Load(f,b)==false)
		return false;
	if(b==true){
		if(::Load(f,ID)==false)
			return false;
	}
	else{
		Pointer=NULL;
	}
	return true;
}
//========================================================================================
void	AlgorithmItemPointerListContainer::Add(AlgorithmItemRoot *item)
{
	AppendList(new AlgorithmItemPointerList(item));
}

bool	AlgorithmItemPointerListContainer::IsExist(AlgorithmItemRoot *item)	const
{
	for(AlgorithmItemPointerList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()==item)
			return true;
	}
	return false;
}
bool	AlgorithmItemPointerListContainer::RemoveItemPoionter(AlgorithmItemRoot *item)
{
	bool	Ret=false;
	for(AlgorithmItemPointerList *a=GetFirst();a!=NULL;){
		AlgorithmItemPointerList *NextA=a->GetNext();
		if(a->GetItem()==item){
			RemoveList(a);
			delete	a;
			Ret=true;
		}
		a=NextA;
	}
	return Ret;
}

AlgorithmItemPointerListContainer	&AlgorithmItemPointerListContainer::operator=(const AlgorithmItemPointerListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
AlgorithmItemPointerListContainer	&AlgorithmItemPointerListContainer::operator+=(const AlgorithmItemPointerListContainer &src)
{
	for(AlgorithmItemPointerList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemPointerList	*b=new AlgorithmItemPointerList(a->GetItem());
		AppendList(b);
	}
	return *this;
}
//========================================================================================

//==========================================================================
AlgorithmItemPointerListContainerByLib::AlgorithmItemPointerListContainerByLib(void) 
: Layer(0),LibID(-1)
{
}
AlgorithmItemPointerListContainerByLib::AlgorithmItemPointerListContainerByLib(int layer ,int libID)
	:Layer(layer),LibID(libID)
{
}
AlgorithmItemPointerListContainerByLib::~AlgorithmItemPointerListContainerByLib(void)
{}
AlgorithmItemPointerListContainerByLib	&AlgorithmItemPointerListContainerByLib::operator=(const AlgorithmItemPointerListContainerByLib &src)
{
	Layer		=src.Layer	;
	LibID		=src.LibID	;
	Container	=src.Container;
	return *this;
}
bool	AlgorithmItemPointerListContainerByLib::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(Container.Save(f)==false)
		return false;
	return true;
}
bool	AlgorithmItemPointerListContainerByLib::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(Container.Load(f)==false)
		return false;
	return true;
}
AlgorithmItemPointerListContainerByLib	*AlgorithmItemPointerListContainerByLibContainer::FindByLibID(int layer ,int libID)	const
{
	for(AlgorithmItemPointerListContainerByLib *f=GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Layer==layer && f->LibID==libID){
			return f;
		}
	}
	return NULL;
}

//==========================================================================

ItemsByAlgorithm::ItemsByAlgorithm(void)
{
	LibType	=0;
	LibID	=0;
	Layer	=0;
}
ItemsByAlgorithm::~ItemsByAlgorithm(void)
{
}

bool	ItemsByAlgorithm::Save(QIODevice *f)
{
	if(ItemID.Save(f)==false)
		return false;
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}
bool	ItemsByAlgorithm::Load(QIODevice *f)
{
	if(ItemID.Load(f)==false)
		return false;
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

ItemsByAlgorithm	&ItemsByAlgorithm::operator=(const ItemsByAlgorithm &src)
{
	LibType	=src.LibType;
	LibID	=src.LibID;
	Layer	=src.Layer;
	ItemID	=src.ItemID;
	return *this;
}

ItemsByAlgorithmContainer::ItemsByAlgorithmContainer(void)
{
}
ItemsByAlgorithmContainer::~ItemsByAlgorithmContainer(void)
{
}

ItemsByAlgorithm	*ItemsByAlgorithmContainer::Create(void)
{
	return new ItemsByAlgorithm();
}

ItemsByAlgorithmContainer	&ItemsByAlgorithmContainer::operator=(const ItemsByAlgorithmContainer &src)
{
	NPListPackSaveLoad<ItemsByAlgorithm>::operator=(src);
	return *this;
}

//==========================================================================

AlgorithmItemPointerListContainer1D	&AlgorithmItemPointerListContainer1D::operator=(const AlgorithmItemPointerListContainer1D &src)
{
	RemoveAll();
	return operator+=(src);
}
AlgorithmItemPointerListContainer1D	&AlgorithmItemPointerListContainer1D::operator+=(const AlgorithmItemPointerListContainer1D &src)
{
	for(AlgorithmItemPointerList *a=src.NPListPackSaveLoad<AlgorithmItemPointerList>::GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemPointerList	*b=new AlgorithmItemPointerList(a->GetItem());
		AppendList(b);
	}
	return *this;
}
AlgorithmItemPointerListContainer2D	&AlgorithmItemPointerListContainer2D::operator=(const AlgorithmItemPointerListContainer2D &src)
{
	RemoveAll();
	return operator+=(src);
}
AlgorithmItemPointerListContainer2D	&AlgorithmItemPointerListContainer2D::operator+=(const AlgorithmItemPointerListContainer2D &src)
{
	for(AlgorithmItemPointerListContainer1D *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemPointerListContainer1D	*b=new AlgorithmItemPointerListContainer1D();
		AppendList(b);
	}
	return *this;
}
