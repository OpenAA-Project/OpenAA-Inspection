#include "XTypeDef.h"
#include "XManualExecuter.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayerCmdLocal.h"
#include "XDataInLayer.h"

bool	ManualExecuterItem::SaveData(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Command)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

bool	ManualExecuterItem::LoadData(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Command)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}

ManualExecuterItem	*ManualExecuterContainer::FindByCommand(int cmd)
{
	for(ManualExecuterItem *a=NPListPack<ManualExecuterItem>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Command==cmd)
			return a;
	}
	return NULL;
}
int					ManualExecuterContainer::GetLibID(void)
{
	ManualExecuterItem *a=NPListPack<ManualExecuterItem>::GetFirst();
	if(a==NULL)
		return -1;
	return a->LibID;
}
bool	ManualExecuterContainer::Execute(AlgorithmItemRoot *item)
{
	for(ManualExecuterItem *a=NPListPack<ManualExecuterItem>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Execute(item)==false)
			return false;
	}
	return true;
}
bool	ManualExecuterContainer::IsExist(int cmd ,int LibID)
{
	for(ManualExecuterItem *a=NPListPack<ManualExecuterItem>::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID && a->Command==cmd){
			return true;
		}
	}
	return false;
}

bool	ManualExecuterContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ManualExecuterItem *a=NPListPack<ManualExecuterItem>::GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->Command)==false)
			return false;
		if(::Save(f,a->LibID)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	ManualExecuterContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(RegisteredContainer==NULL)
		return false;
	if(::Load(f,Ver)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		int32	Command;
		int32	LibID;
		if(::Load(f,Command)==false)
			return false;
		if(::Load(f,LibID)==false)
			return false;
		ManualExecuterItem	*g=RegisteredContainer->FindByCommand(Command);
		if(g==NULL)
			return false;
		ManualExecuterItem	*a=g->Create();
		a->Command	=Command;
		a->LibID	=LibID;
		if(a->Load(f)==false)
			return false;
		NPListPack<ManualExecuterItem>::AppendList(a);
	}
	return true;
}

//----------------------------------------------------------------------------
ManualExecuter::ManualExecuter(void)
	:Registered(NULL)
{
}
	
void	ManualExecuter::RegisteringClass(ManualExecuterItem *f)
{
	Registered.AppendList(f);
}
	
void	ManualExecuter::AppendCommand(ManualExecuterItem *f)
{
	for(ManualExecuterContainer *a=CommandList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==f->LibID){
			a->AppendList(f);
			return;
		}
	}
	ManualExecuterContainer *k=new ManualExecuterContainer(&Registered);
	k->AppendList(f);
	CommandList.AppendList(k);
}
bool	ManualExecuter::DeliverToSlave(AlgorithmBase *ABase)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	SaveCommand(&Buff);

	LayersBase	*Base=ABase->GetLayersBase();
	QString DLLRoot;
	QString DLLName;
	ABase->GetAlgorithmRootName(DLLRoot ,DLLName);

	for(int page=0;page<Base->GetPageNumb();page++){
		int	globalPage=Base->GetGlobalPageFromLocal(page);
		GUICmdDeliverManualExecuter	Cmd(Base,"ANY","ANY",globalPage);
		Cmd.DLLRoot=DLLRoot;
		Cmd.DLLName=DLLName;
		Cmd.ManualArray	=Buff.buffer();
		Cmd.Send(NULL,globalPage ,0);
	}
	return true;
}
bool	ManualExecuter::Execute(AlgorithmItemRoot *item)
{
	for(ManualExecuterContainer *a=CommandList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==item->GetLibID()){
			if(a->Execute(item)==false)
				return false;
			return true;
		}
	}
	return false;
}
	
bool	ManualExecuter::IsExist(int cmd ,int LibID)
{
	for(ManualExecuterContainer *a=CommandList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsExist(cmd ,LibID)==true){
			return true;
		}
	}
	return false;
}

bool	ManualExecuter::ClearCommandAll(void)
{
	CommandList.RemoveAll();
	return true;
}
	
bool	ManualExecuter::SaveCommand(QIODevice *f)
{
	int32	N=CommandList.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ManualExecuterContainer *a=CommandList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	ManualExecuter::LoadCommand(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	CommandList.RemoveAll();
	for(int i=0;i<N;i++){
		ManualExecuterContainer	*a=new ManualExecuterContainer(&Registered);
		if(a->Load(f)==false)
			return false;
		CommandList.AppendList(a);
	}
	return true;
}

//=====================================================================
