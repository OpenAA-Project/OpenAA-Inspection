#include "XDataAlgorithmConfirm.h"
#include "XGeneralFunc.h"
#include "XDataInLayerCmdLocal.h"

ConfirmItemList::ConfirmItemList(void)
{
	Phase	=0;
	Page	=0;
	Layer	=0;
	ItemID	=-1;
	CType=CF_ReqConfirm;
}
ConfirmItemList::ConfirmItemList(const ConfirmItemList &src)
{
	Phase	=src.Phase	;
	Page	=src.Page	;
	Layer	=src.Layer	;
	ItemID	=src.ItemID	;
	Cause	=src.Cause	;
	CType	=src.CType	;
}

bool	ConfirmItemList::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,Cause	)==false)	return false;
	BYTE	d=(BYTE)CType;
	if(::Save(f,d		)==false)	return false;
	return true;
}
bool	ConfirmItemList::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,Cause	)==false)	return false;
	BYTE	d;
	if(::Load(f,d		)==false)	return false;
	CType=(ConfirmType)d;
	return true;
}

ConfirmItemList	&ConfirmItemList::operator=(const ConfirmItemList &src)
{
	Phase	=src.Phase	;
	Page	=src.Page	;
	Layer	=src.Layer	;
	ItemID	=src.ItemID	;
	Cause	=src.Cause	;
	CType	=src.CType	;
	return *this;
}
ConfirmItemListContainer::ConfirmItemListContainer(void)
{
}
ConfirmItemListContainer::ConfirmItemListContainer(const ConfirmItemListContainer &src)
{
	for(ConfirmItemList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ConfirmItemList	*d=new ConfirmItemList();
		*d=*s;
		AppendList(d);
	}
}
ConfirmItemList	*ConfirmItemListContainer::Create(void)
{
	return new ConfirmItemList();
}

ConfirmItemListContainer	&ConfirmItemListContainer::operator=(const ConfirmItemListContainer &src)
{
	RemoveAll();
	for(ConfirmItemList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ConfirmItemList	*d=new ConfirmItemList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

//======================================================================

GUICmdReqConfirmItemList::GUICmdReqConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqConfirmItemList::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)	return false;
	if(::Load(f,AlgorithmName)==false)	return false;
	return true;
}
bool	GUICmdReqConfirmItemList::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)	return false;
	if(::Save(f,AlgorithmName)==false)	return false;
	return true;
}

void	GUICmdReqConfirmItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckConfirmItemList	*SendBack=GetSendBack(GUICmdAckConfirmItemList,GetLayersBase(),"ANY","ANY",localPage);

	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot,AlgorithmName);
	if(ABase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot *PData=Ph->GetPageData(localPage);
				if(PData!=NULL){
					ConfirmItemListContainer	tItemList;
					PData->MakeConfirmItem(tItemList);
					for(ConfirmItemList *a=tItemList.GetFirst();a!=NULL;a=a->GetNext()){
						a->Page=GlobalPage;
						a->Phase=phase;
					}
					SendBack->ItemList.AddMove(tItemList);
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckConfirmItemList::GUICmdAckConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckConfirmItemList::Load(QIODevice *f)
{
	if(ItemList.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckConfirmItemList::Save(QIODevice *f)
{
	if(ItemList.Save(f)==false)	return false;
	return true;
}
