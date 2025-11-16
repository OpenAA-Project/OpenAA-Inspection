#include "XShowHistgramTotalPacket.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"

bool	HistgramTypeList::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,HistID)==false)
		return false;
	if(::Save(f,HistName)==false)
		return false;
	return true;
}

bool	HistgramTypeList::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,HistID)==false)
		return false;
	if(::Load(f,HistName)==false)
		return false;
	return true;
}

HistgramTypeList	&HistgramTypeList::operator=(HistgramTypeList &src)
{
	AlgoRoot	=src.AlgoRoot;
	AlgoName	=src.AlgoName;
	HistID		=src.HistID;
	HistName	=src.HistName;
	return *this;
}

bool				HistgramTypeList::operator==(HistgramTypeList &src)
{
	if(AlgoRoot	!=src.AlgoRoot)
		return false;
	if(AlgoName	!=src.AlgoName)
		return false;
	if(HistID	!=src.HistID)
		return false;
	if(HistName	!=src.HistName)
		return false;
	return true;
}

HistgramTypeListContainer	&HistgramTypeListContainer::operator=(HistgramTypeListContainer &src)
{
	RemoveAll();
	for(HistgramTypeList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		HistgramTypeList *b=new HistgramTypeList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
bool	HistgramTypeListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(HistgramTypeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	HistgramTypeListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		HistgramTypeList	*a=new HistgramTypeList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

//========================================================================

GUICmdReqHistgramTypeList::GUICmdReqHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqHistgramTypeList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendHistgramTypeList	*SendBack=GetSendBack(GUICmdSendHistgramTypeList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeHistgramList(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendHistgramTypeList::GUICmdSendHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendHistgramTypeList::Load(QIODevice *f)
{
	if(HContainer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendHistgramTypeList::Save(QIODevice *f)
{
	if(HContainer.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendHistgramTypeList::MakeHistgramList(int localPage)
{
	HContainer.RemoveAll();
	for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmBase	*A=a->GetInstance();
		AlgorithmBase::RegisteredHistgramListContainer List;
		A->EnumHistgram(List);

		for(AlgorithmBase::RegisteredHistgramList *h=List.GetFirst();h!=NULL;h=h->GetNext()){
			HistgramTypeList	*L=new HistgramTypeList();
			L->AlgoRoot	=a->GetDLLRoot();
			L->AlgoName	=a->GetDLLName();
			L->HistID	=h->GetID();
			L->HistName	=h->GetName();
			HContainer.AppendList(L);
		}
	}
}

//========================================================================

bool	LibraryItemList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ItemCount)==false)
		return false;
	return true;
}

bool	LibraryItemList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ItemCount)==false)
		return false;
	return true;
}


LibraryItemList	&LibraryItemList::operator=(LibraryItemList &src)
{
	LibID	=src.LibID;
	ItemCount	=src.ItemCount;
	return *this;
}

bool	LibraryItemListContainer::Save(QIODevice *f)
{
	int	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LibraryItemList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	LibraryItemListContainer::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LibraryItemList	*a=new LibraryItemList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
LibraryItemList	*LibraryItemListContainer::GetLibraryItemList(int LibID)
{
	for(LibraryItemList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID){
			return a;
		}
	}
	return NULL;
}

GUICmdReqHistgramLibrary::GUICmdReqHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqHistgramLibrary::Load(QIODevice *f)
{
	if(PointData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqHistgramLibrary::Save(QIODevice *f)
{
	if(PointData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqHistgramLibrary::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendHistgramLibrary	*SendBack=GetSendBack(GUICmdSendHistgramLibrary,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeHistgramData(PointData,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendHistgramLibrary::GUICmdSendHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendHistgramLibrary::MakeHistgramData(HistgramTypeList &Point,int localPage)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Point.AlgoRoot,Point.AlgoName);
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
		AlgorithmItemPointerListContainer RetContainer;
		APage->EnumItemHistgram(Point.HistID,RetContainer);
		for(AlgorithmItemPointerList *a=RetContainer.GetFirst();a!=NULL;a=a->GetNext()){
			LibraryItemList	*k=LibData.GetLibraryItemList(a->Pointer->GetLibID());
			if(k==NULL){
				LibraryItemList	*t=new LibraryItemList();
				t->LibID=a->Pointer->GetLibID();
				t->ItemCount=1;
				LibData.AppendList(t);
			}
			else{
				k->ItemCount++;
			}
		}
	}
}

bool	GUICmdSendHistgramLibrary::Load(QIODevice *f)
{
	if(LibData.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendHistgramLibrary::Save(QIODevice *f)
{
	if(LibData.Load(f)==false)
		return false;
	return true;
}

//========================================================================

GUICmdReqHistgramTotalData::GUICmdReqHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqHistgramTotalData::Load(QIODevice *f)
{
	if(PointData.Load(f)==false)
		return false;
	if(LibData.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqHistgramTotalData::Save(QIODevice *f)
{
	if(PointData.Save(f)==false)
		return false;
	if(LibData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqHistgramTotalData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendHistgramTotalData	*SendBack=GetSendBack(GUICmdSendHistgramTotalData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeHistgramData(PointData,LibData,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendHistgramTotalData::GUICmdSendHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


void	GUICmdSendHistgramTotalData::MakeHistgramData(HistgramTypeList &PointH,LibraryItemList &PointL,int localPage)
{
	HistgramByParamBasePointerContainer	HContainer;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(PointH.AlgoRoot,PointH.AlgoName);
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
		AlgorithmInPageRoot	*APage=Ph->GetPageData(localPage);
		AlgorithmItemPointerListContainer RetContainer;
		APage->EnumItemHistgram(PointH.HistID,PointL.LibID,RetContainer);
		for(AlgorithmItemPointerList *a=RetContainer.GetFirst();a!=NULL;a=a->GetNext()){
			HistgramByParamBase	*H=a->Pointer->GetHistgramBase(PointH.HistID);
			if(H!=NULL){
				HContainer.Add(H);
			}
		}
	}
	double	MinData=99999999;
	double	MaxData=-99999999;
	for(HistgramByParamBasePointerList *k=HContainer.GetFirst();k!=NULL;k=k->GetNext()){
		double tMinData ,tMaxData;
		k->Pointer->GetMinMaxData(tMinData ,tMaxData);
		if(tMinData<MinData){
			MinData=tMinData;
		}
		if(tMaxData>MaxData){
			MaxData=tMaxData;
		}
	}
	Data.Create(MinData,MaxData,1.0);
	for(HistgramByParamBasePointerList *k=HContainer.GetFirst();k!=NULL;k=k->GetNext()){
		k->Pointer->AddTo(&Data);
	}
}

bool	GUICmdSendHistgramTotalData::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendHistgramTotalData::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}
