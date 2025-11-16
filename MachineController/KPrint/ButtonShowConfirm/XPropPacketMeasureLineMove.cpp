#include "XPropPacketMeasureLineMove.h"
#include "XMeasureLineMoveLibrary.h"
#include "XMeasureLineMove.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "ConfirmForm.h"

//=================================================================================================

IntegrationReqMeasureLineMoveSelectItems::IntegrationReqMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	Mode=-1;
}

bool	IntegrationReqMeasureLineMoveSelectItems::Load(QIODevice *f)
{
	if(SelectedLib.Load(f)	==false)	return false;
	if(GlobalArea.Load(f)	==false)	return false;
	if(::Load(f,Phase)		==false)	return false;
	if(::Load(f,GlobalX)	==false)	return false;
	if(::Load(f,GlobalY)	==false)	return false;
	if(::Load(f,Mode)		==false)	return false;
	return true;
}
bool	IntegrationReqMeasureLineMoveSelectItems::Save(QIODevice *f)
{
	if(SelectedLib.Save(f)	==false)	return false;
	if(GlobalArea.Save(f)	==false)	return false;
	if(::Save(f,Phase)		==false)	return false;
	if(::Save(f,GlobalX)	==false)	return false;
	if(::Save(f,GlobalY)	==false)	return false;
	if(::Save(f,Mode)		==false)	return false;
	return true;
}

void	IntegrationReqMeasureLineMoveSelectItems::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckMeasureLineMoveSelectItems	*SendBack=GetSendBackIntegration(IntegrationAckMeasureLineMoveSelectItems,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	PageDataInOnePhase	*ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(ph!=NULL){
		if(Mode==0){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(GlobalArea,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	page=c->GetValue();
				DataInPage	*dp=ph->GetPageData(page);
				if(dp!=NULL){
					GUICmdReqMeasureLineMoveSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					RCmd.SelectedLib=SelectedLib;
					RCmd.LocalArea=GlobalArea;
					dp->ClipMoveAreaFromGlobal(RCmd.LocalArea);
					RCmd.Phase		=Phase;
					RCmd.Mode=Mode;
					GUICmdAckMeasureLineMoveSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					if(RCmd.Send(page,0,ACmd)==true){
						SendBack->Items.Merge(ACmd.Items);
					}
				}
			}
		}
		else if(Mode==1){
			IntList PageList;
			GetLayersBase()->GetGlobalPage(GlobalX ,GlobalY,PageList);
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	page=c->GetValue();
				DataInPage	*dp=ph->GetPageData(page);
				if(dp!=NULL){
					GUICmdReqMeasureLineMoveSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					RCmd.SelectedLib=SelectedLib;
					dp->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,RCmd.LocalX ,RCmd.LocalY);
					RCmd.Phase		=Phase;
					RCmd.Mode=Mode;
					GUICmdAckMeasureLineMoveSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
					if(RCmd.Send(page,0,ACmd)==true){
						SendBack->Items.Merge(ACmd.Items);
					}
				}
			}
		}
		else if(Mode==2){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqMeasureLineMoveSelectItems	RCmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				RCmd.SelectedLib=SelectedLib;
				RCmd.Phase		=Phase;
				RCmd.Mode=Mode;
				GUICmdAckMeasureLineMoveSelectItems	ACmd(GetLayersBase(),EmitterRoot,EmitterName,page);
				if(RCmd.Send(page,0,ACmd)==true){
					SendBack->Items.Merge(ACmd.Items);
				}
			}
		}
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMeasureLineMoveSelectItems::IntegrationAckMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckMeasureLineMoveSelectItems::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckMeasureLineMoveSelectItems::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}

GUICmdReqMeasureLineMoveSelectItems::GUICmdReqMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
	Mode=-1;
}
bool	GUICmdReqMeasureLineMoveSelectItems::Load(QIODevice *f)
{
	if(SelectedLib.Load(f)	==false)	return false;
	if(LocalArea.Load(f)	==false)	return false;
	if(::Load(f,Phase)		==false)	return false;
	if(::Load(f,LocalX)		==false)	return false;
	if(::Load(f,LocalY)		==false)	return false;
	if(::Load(f,Mode)		==false)	return false;
	return true;
}
bool	GUICmdReqMeasureLineMoveSelectItems::Save(QIODevice *f)
{
	if(SelectedLib.Save(f)	==false)	return false;
	if(LocalArea.Save(f)	==false)	return false;
	if(::Save(f,Phase)		==false)	return false;
	if(::Save(f,LocalX)		==false)	return false;
	if(::Save(f,LocalY)		==false)	return false;
	if(::Save(f,Mode)		==false)	return false;
	return true;
}

void	GUICmdReqMeasureLineMoveSelectItems::Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMeasureLineMoveSelectItems	*SendBack=GetSendBack(GUICmdAckMeasureLineMoveSelectItems,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(SelectedLib.GetLibType());
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				AlgorithmItemPointerListContainer ItemPointers;
				if(SelectedLib.GetLibID()>=0){
					IntList LibIDs;
					LibIDs.Add(SelectedLib.GetLibID());
					Ap->EnumItemsByLib(LibIDs ,ItemPointers);
				}
				else{
					Ap->EnumAllItems(ItemPointers);
				}
				int		GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
				if(Mode==0){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						MeasureLineMoveDistanceItem	*Item=dynamic_cast<MeasureLineMoveDistanceItem *>(a->GetItem());
						if(Item!=NULL){
							if(Item->IsCrossed(&LocalArea)==true){
								SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
							}
						}
					}
				}
				else if(Mode==1){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						MeasureLineMoveDistanceItem	*Item=dynamic_cast<MeasureLineMoveDistanceItem *>(a->GetItem());
						if(Item!=NULL){
							if(Item->IsInclude(LocalX,LocalY)==true
							|| (Item->GetVector()!=NULL && Item->GetVector()->GetDistance(LocalX,LocalY)<10)){
								SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
							}
						}
					}
				}
				else if(Mode==3){
					for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
						MeasureLineMoveDistanceItem	*Item=dynamic_cast<MeasureLineMoveDistanceItem *>(a->GetItem());
						if(Item!=NULL){
							SendBack->Items.Add(Phase,GlobalPage,Item->GetLayer(),Item->GetID());
						}
					}
				}
			}
		}
	}

	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMeasureLineMoveSelectItems::GUICmdAckMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),GlobanPage)
{
}

bool	GUICmdAckMeasureLineMoveSelectItems::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckMeasureLineMoveSelectItems::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}

//=================================================================================================

IntegrationReqMeasureLineMoveItemThresholdData::IntegrationReqMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqMeasureLineMoveItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	return true;
}
bool	IntegrationReqMeasureLineMoveItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	return true;
}
void	IntegrationReqMeasureLineMoveItemThresholdData::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckMeasureLineMoveItemThresholdData	*SendBack=GetSendBackIntegration(IntegrationAckMeasureLineMoveItemThresholdData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				MeasureLineMoveDistanceItem	*ItemD=dynamic_cast<MeasureLineMoveDistanceItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(ItemD!=NULL){
					MeasureLineMoveItemBase	*ItemL1=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID1));
					MeasureLineMoveItemBase	*ItemL2=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID2));
					if(ItemL1!=NULL && ItemL2!=NULL){
						QBuffer	Buff;
						Buff.open(QIODevice::ReadWrite);
						const AlgorithmThreshold	*RD=ItemD->GetThresholdBaseReadable();
						if(((AlgorithmThreshold *)RD)->Save(&Buff)==true){
							SendBack->ThresholdDataDistance=Buff.buffer();
							CmdReqThresholdHLMeasureLineMove	HLCmd(GetLayersBase());
							HLCmd.ThresholdM=((MeasureLineMoveThreshold *)RD)->ThresholdM;
							HLCmd.ThresholdP=((MeasureLineMoveThreshold *)RD)->ThresholdP;
							HLCmd.Item=ItemD;
							ABase->TransmitDirectly(&HLCmd);
							SendBack->OKLengthLUnit	=HLCmd.ThresholdM;
							SendBack->OKLengthHUnit	=HLCmd.ThresholdP;	
						}
						QBuffer	BuffL1;
						BuffL1.open(QIODevice::ReadWrite);
						const AlgorithmThreshold	*RL1=ItemL1->GetThresholdBaseReadable();
						if(((AlgorithmThreshold *)RL1)->Save(&BuffL1)==true){
							SendBack->Line1ItemID		=ItemL1->GetID();	
							SendBack->ThresholdDataLine1=BuffL1.buffer();
						}
						QBuffer	BuffL2;
						BuffL2.open(QIODevice::ReadWrite);
						const AlgorithmThreshold	*RL2=ItemL2->GetThresholdBaseReadable();
						if(((AlgorithmThreshold *)RL2)->Save(&BuffL2)==true){
							SendBack->Line2ItemID		=ItemL2->GetID();	
							SendBack->ThresholdDataLine2=BuffL2.buffer();
						}
					}
				}
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMeasureLineMoveItemThresholdData::IntegrationAckMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	Line1ItemID=-1;
	Line2ItemID=-1;
}
bool	IntegrationAckMeasureLineMoveItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,Line1ItemID				)==false)	return false;
	if(::Load(f,Line2ItemID				)==false)	return false;
	if(::Load(f,ThresholdDataDistance	)==false)	return false;
	if(::Load(f,ThresholdDataLine1		)==false)	return false;
	if(::Load(f,ThresholdDataLine2		)==false)	return false;
	if(::Load(f,OKLengthLUnit			)==false)	return false;
	if(::Load(f,OKLengthHUnit			)==false)	return false;
	return true;
}
bool	IntegrationAckMeasureLineMoveItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,Line1ItemID				)==false)	return false;
	if(::Save(f,Line2ItemID				)==false)	return false;
	if(::Save(f,ThresholdDataDistance	)==false)	return false;
	if(::Save(f,ThresholdDataLine1		)==false)	return false;
	if(::Save(f,ThresholdDataLine2		)==false)	return false;
	if(::Save(f,OKLengthLUnit			)==false)	return false;
	if(::Save(f,OKLengthHUnit			)==false)	return false;
	return true;
}

IntegrationSetMeasureLineMoveItemThresholdData::IntegrationSetMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationSetMeasureLineMoveItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	if(::Load(f,ThresholdDataDistance	)==false)	return false;
	if(::Load(f,ThresholdDataLine1		)==false)	return false;
	if(::Load(f,ThresholdDataLine2		)==false)	return false;
	return true;
}
bool	IntegrationSetMeasureLineMoveItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	if(::Save(f,ThresholdDataDistance	)==false)	return false;
	if(::Save(f,ThresholdDataLine1		)==false)	return false;
	if(::Save(f,ThresholdDataLine2		)==false)	return false;
	return true;
}
void	IntegrationSetMeasureLineMoveItemThresholdData::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckMeasureLineMoveItemThresholdData	*SendBack=GetSendBackIntegration(IntegrationAckMeasureLineMoveItemThresholdData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				MeasureLineMoveDistanceItem	*ItemD=dynamic_cast<MeasureLineMoveDistanceItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(ItemD!=NULL){
					MeasureLineMoveItemBase	*ItemL1=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID1));
					MeasureLineMoveItemBase	*ItemL2=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID2));
					if(ItemL1!=NULL && ItemL2!=NULL){
						QBuffer	Buff(&ThresholdDataDistance);
						Buff.open(QIODevice::ReadWrite);
						AlgorithmThreshold	*WD=ItemD->GetThresholdBaseWritable();
						if(WD->Load(&Buff)==true){
						}
						QBuffer	BuffL1(&ThresholdDataLine1);
						BuffL1.open(QIODevice::ReadWrite);
						AlgorithmThreshold	*WL1=ItemL1->GetThresholdBaseWritable();
						if(WL1->Load(&BuffL1)==true){
						}
						QBuffer	BuffL2(&ThresholdDataLine2);
						BuffL2.open(QIODevice::ReadWrite);
						AlgorithmThreshold	*WL2=ItemL2->GetThresholdBaseWritable();
						if(WL2->Load(&BuffL2)==true){
						}
					}
				}
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}
//=================================================================================================

IntegrationReqMeasureLineMoveTryResult::IntegrationReqMeasureLineMoveTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqMeasureLineMoveTryResult::Load(QIODevice *f)
{
	if(ItemIndex.Load(f)==false)				return false;
	if(::Load(f,ThresholdDataDistance)==false)	return false;
	if(::Load(f,ThresholdDataLine1)==false)		return false;
	if(::Load(f,ThresholdDataLine2)==false)		return false;
	return true;
}
bool	IntegrationReqMeasureLineMoveTryResult::Save(QIODevice *f)
{
	if(ItemIndex.Save(f)==false)		return false;
	if(::Save(f,ThresholdDataDistance)==false)	return false;
	if(::Save(f,ThresholdDataLine1)==false)		return false;
	if(::Save(f,ThresholdDataLine2)==false)		return false;
	return true;
}

void	IntegrationReqMeasureLineMoveTryResult::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckMeasureLineMoveTryResult	*SendBack=GetSendBackIntegration(IntegrationAckMeasureLineMoveTryResult,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeMeasureLineMove);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				MeasureLineMoveDistanceItem	*ItemD=dynamic_cast<MeasureLineMoveDistanceItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(ItemD!=NULL){
					MeasureLineMoveItemBase	*ItemL1=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID1));
					MeasureLineMoveItemBase	*ItemL2=dynamic_cast<MeasureLineMoveItemBase *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemD->LineID2));
					if(ItemL1!=NULL && ItemL2!=NULL){

						CmdMeasureLineMoveSendTryThreshold	Cmd(GetLayersBase());
						Cmd.SrcD	=ItemD;
						Cmd.SrcL1	=ItemL1;
						Cmd.SrcL2	=ItemL2;
						Cmd.ThresholdDataForTargetD	=ThresholdDataDistance;
						Cmd.ThresholdDataForTargetL1=ThresholdDataLine1;
						Cmd.ThresholdDataForTargetL2=ThresholdDataLine2;
						ABase->TransmitDirectly(&Cmd);

						SendBack->OK		=Cmd.PTry->Result->IsOk();
						SendBack->Distance	=Cmd.PTry->Result->GetResultDouble();
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckMeasureLineMoveTryResult::IntegrationAckMeasureLineMoveTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckMeasureLineMoveTryResult::Load(QIODevice *f)
{
	if(::Load(f,OK		)==false)	return false;
	if(::Load(f,Distance)==false)	return false;
	return true;
}
bool	IntegrationAckMeasureLineMoveTryResult::Save(QIODevice *f)
{
	if(::Save(f,OK		)==false)	return false;
	if(::Save(f,Distance)==false)	return false;
	return true;
}