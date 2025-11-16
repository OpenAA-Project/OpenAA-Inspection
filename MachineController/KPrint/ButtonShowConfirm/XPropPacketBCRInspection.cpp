#include "XPropPacketBCRInspection.h"
#include "XBCRInspectionLibrary.h"
#include "XBCRInspection.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"

bool	BCodeItemList::Save(QIODevice *f)
{
	if(ItemIndex.Save(f)==false)	return false;
	if(::Save(f,x1	)==false)		return false;
	if(::Save(f,y1	)==false)		return false;
	if(::Save(f,x2	)==false)		return false;
	if(::Save(f,y2	)==false)		return false;
	if(::Save(f,Result)==false)		return false;
	return true;
}
bool	BCodeItemList::Load(QIODevice *f)
{
	if(ItemIndex.Load(f)==false)	return false;
	if(::Load(f,x1	)==false)		return false;
	if(::Load(f,y1	)==false)		return false;
	if(::Load(f,x2	)==false)		return false;
	if(::Load(f,y2	)==false)		return false;
	if(::Load(f,Result)==false)		return false;
	return true;
}

BCodeItemList	&BCodeItemList::operator=(const BCodeItemList &src)
{
	ItemIndex=src.ItemIndex;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	Result	=src.Result;
	return *this;
}
BCodeItemListContainer	&BCodeItemListContainer::operator=(const BCodeItemListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
BCodeItemListContainer	&BCodeItemListContainer::operator+=(const BCodeItemListContainer &src)
{
	for(BCodeItemList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BCodeItemList *d=new BCodeItemList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

IntegrationReqBCodeItemListInfo::IntegrationReqBCodeItemListInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqBCodeItemListInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	return true;
}
bool	IntegrationReqBCodeItemListInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	return true;
}
void	IntegrationReqBCodeItemListInfo::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckBCodeItemListInfo	*SendBack=GetSendBackIntegration(IntegrationAckBCodeItemListInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeBCRInspection);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				for(AlgorithmItemPI	*a=Ap->GetFirstData();a!=NULL;a=a->GetNext()){
					BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(a);
					if(Item!=NULL){
						BCodeItemList	*m=new BCodeItemList();
						m->ItemIndex=Item->GetItemIndex();
						Item->GetXY(m->x1,m->x1,m->x2,m->y2);
						m->Result	=QString::number(Item->GetCurrentResult()->GetResultDouble(),'f',3);
						SendBack->Container.AppendList(m);
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckBCodeItemListInfo::IntegrationAckBCodeItemListInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckBCodeItemListInfo::Load(QIODevice *f)
{
	if(Container.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckBCodeItemListInfo::Save(QIODevice *f)
{
	if(Container.Save(f)==false)	return false;
	return true;
}

//===============================================================================

IntegrationReqBCRInspectionTryResult::IntegrationReqBCRInspectionTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqBCRInspectionTryResult::Load(QIODevice *f)
{
	if(ItemIndex.Load(f)==false)		return false;
	if(::Load(f,ThresholdData)==false)	return false;
	return true;
}
bool	IntegrationReqBCRInspectionTryResult::Save(QIODevice *f)
{
	if(ItemIndex.Save(f)==false)		return false;
	if(::Save(f,ThresholdData)==false)	return false;
	return true;
}

void	IntegrationReqBCRInspectionTryResult::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckBCRInspectionTryResult	*SendBack=GetSendBackIntegration(IntegrationAckBCRInspectionTryResult,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeBCRInspection);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				BCRInspectionItem	*Item=dynamic_cast<BCRInspectionItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(Item!=NULL){
					CmdBCRInspectionSendTryThreshold	Cmd(GetLayersBase());
					Cmd.Src=Item;
					Cmd.ThresholdDataForTarget=ThresholdData;
					ABase->TransmitDirectly(&Cmd);			;

					//ResultPosList	*r=Cmd.PTry->Result->GetPosListFirst();

					SendBack->Result=Cmd.Target->Result;
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckBCRInspectionTryResult::IntegrationAckBCRInspectionTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckBCRInspectionTryResult::Load(QIODevice *f)
{
	if(::Load(f,Result)==false)	return false;
	return true;
}
bool	IntegrationAckBCRInspectionTryResult::Save(QIODevice *f)
{
	if(::Save(f,Result)==false)	return false;
	return true;
}
