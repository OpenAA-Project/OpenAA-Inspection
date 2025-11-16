#include"XModelPLICommander.h"
#include"XGeneralFunc.h"

SlaveCommReqRentalItems::SlaveCommReqRentalItems(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	Layer	=-1;
	FromGlobalPage=-1;
}

bool	SlaveCommReqRentalItems::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,FromGlobalPage)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;	
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Something)==false)
		return false;
	return true;
}
bool	SlaveCommReqRentalItems::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,FromGlobalPage)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;	
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Something)==false)
		return false;
	return true;
}

void	SlaveCommReqRentalItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckRentalItems	*S
	=(SlaveCommAckRentalItems *)((GetSendBackPacket()==NULL)?new SlaveCommAckRentalItems(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			AlgorithmInPagePLI	*aPg=(AlgorithmInPagePLI *)Pg;
			AlgorithmInLayerPLI *aLy=aPg->GetLayerDataPLI(Layer);
			if(aLy!=NULL){
				aLy->AckRentalItem(FromGlobalPage ,Something,S->RentalData);
				S->Layer	=Layer;
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}


SlaveCommAckRentalItems::SlaveCommAckRentalItems(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	Layer=-1;
}
bool	SlaveCommAckRentalItems::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;	
	if(::Load(f,AlgoName)==false)
		return false;

	int	N;
	if(::Load(f,N)==false)
		return false;

	RentalData.RemoveAll();

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(ABase!=NULL){
		for(int i=0;i<N;i++){
			int32	ItemClass;
			if(::Load(f,ItemClass)==false)
				return false;

			AlgorithmItemRoot	*a=ABase->GetPageData(0)->GetLayerData(0)->CreateItem(ItemClass);
			if(a->Load(f,GetLayersBase())==false)
				return false;
			AlgorithmItemPLI	*ap=dynamic_cast<AlgorithmItemPLI *>(a);
			if(ap!=NULL){
				RentalData.AppendList(ap);
			}
		}
	}
	return true;
}
bool	SlaveCommAckRentalItems::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;	
	if(::Save(f,AlgoName)==false)
		return false;

	int	N=RentalData.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext()){
		int32	ItemClass=a->GetItemClassType();
		if(::Save(f,ItemClass)==false)
			return false;
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}