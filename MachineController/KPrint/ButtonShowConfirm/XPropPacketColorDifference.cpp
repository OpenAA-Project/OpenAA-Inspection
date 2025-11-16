#include "XPropPacketColorDifference.h"
#include "XColorDifferenceLibrary.h"
#include "XColorDifference.h"

//=================================================================================================

IntegrationReqColorDifferenceItemThresholdData::IntegrationReqColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqColorDifferenceItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	return true;
}
bool	IntegrationReqColorDifferenceItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	return true;
}
void	IntegrationReqColorDifferenceItemThresholdData::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckColorDifferenceItemThresholdData	*SendBack=GetSendBackIntegration(IntegrationAckColorDifferenceItemThresholdData,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				ColorDifferenceItem	*Item=(ColorDifferenceItem *)Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID);
				if(Item!=NULL){
					const AlgorithmThreshold	*R=Item->GetThresholdBaseReadable();
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					if(((AlgorithmThreshold	*)R)->Save(&Buff)==true){
						SendBack->ItemClass					=Item->GetItemClassType();
						SendBack->ThresholdData				=Buff.buffer();
						SendBack->OutputConstantlyInItem	=Item->OutputConstantly;
						SendBack->LibID						=Item->GetLibID();
					}
				}
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckColorDifferenceItemThresholdData::IntegrationAckColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckColorDifferenceItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,ItemClass		)==false)	return false;
	if(::Load(f,ThresholdData	)==false)	return false;
	if(::Load(f,LibID			)==false)	return false;
	if(::Load(f,OutputConstantlyInItem	)==false)	return false;
	return true;
}
bool	IntegrationAckColorDifferenceItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,ItemClass		)==false)	return false;
	if(::Save(f,ThresholdData	)==false)	return false;
	if(::Save(f,LibID			)==false)	return false;
	if(::Save(f,OutputConstantlyInItem	)==false)	return false;
	return true;
}

IntegrationSetColorDifferenceItemThresholdData::IntegrationSetColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationSetColorDifferenceItemThresholdData::Load(QIODevice *f)
{
	if(::Load(f,LibType			)==false)	return false;
	if(::Load(f,ThresholdData	)==false)	return false;
	if(ItemIndex.Load(f)==false)	return false;
	if(::Load(f,OutputConstantlyInItem	)==false)	return false;
	return true;
}
bool	IntegrationSetColorDifferenceItemThresholdData::Save(QIODevice *f)
{
	if(::Save(f,LibType			)==false)	return false;
	if(::Save(f,ThresholdData	)==false)	return false;
	if(ItemIndex.Save(f)==false)	return false;
	if(::Save(f,OutputConstantlyInItem	)==false)	return false;
	return true;
}

void	IntegrationSetColorDifferenceItemThresholdData::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				ColorDifferenceItem	*Item=(ColorDifferenceItem *)Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID);
				if(Item!=NULL){
					AlgorithmThreshold	*W=Item->GetThresholdBaseWritable();
					QBuffer	Buff(&ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					W->Load(&Buff);
					Item->OutputConstantly=OutputConstantlyInItem;
				}
			}
		}
	}
}
//===============================================================================

IntegrationReqColorDifferenceTryResult::IntegrationReqColorDifferenceTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqColorDifferenceTryResult::Load(QIODevice *f)
{
	if(ItemIndex.Load(f)==false)		return false;
	if(::Load(f,ThresholdData)==false)	return false;
	return true;
}
bool	IntegrationReqColorDifferenceTryResult::Save(QIODevice *f)
{
	if(ItemIndex.Save(f)==false)		return false;
	if(::Save(f,ThresholdData)==false)	return false;
	return true;
}

void	IntegrationReqColorDifferenceTryResult::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckColorDifferenceTryResult	*SendBack=GetSendBackIntegration(IntegrationAckColorDifferenceTryResult,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeColorDifference);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				ColorDifferenceItem	*Item=dynamic_cast<ColorDifferenceItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(Item!=NULL){
					CmdColorDifferenceSendTryThreshold	Cmd(GetLayersBase());
					Cmd.Src=Item;
					Cmd.ThresholdDataForTarget=ThresholdData;
					ABase->TransmitDirectly(&Cmd);

					SendBack->ResultMoveDx	=Cmd.PTry->ResultMoveDx	;
					SendBack->ResultMoveDy	=Cmd.PTry->ResultMoveDy	;
					SendBack->Error			=Cmd.PTry->Error		;
					SendBack->LenOK			=Cmd.PTry->LenOK		;
					SendBack->LenNG			=Cmd.PTry->LenNG		;
					SendBack->DeltaE		=Cmd.PTry->DeltaE		;
					SendBack->ReferenceColor1=Cmd.PTry->ReferenceColor1;
					SendBack->ReferenceColor2=Cmd.PTry->ReferenceColor2;
					SendBack->MasterColor	=Cmd.PTry->MasterColor	;
					SendBack->TargetColor	=Cmd.PTry->TargetColor	;
					SendBack->StatisticData.MasterH	=Cmd.PTry->StatisticData.MasterH;
					SendBack->StatisticData.MasterS	=Cmd.PTry->StatisticData.MasterS;
					SendBack->StatisticData.MasterV	=Cmd.PTry->StatisticData.MasterV;
					SendBack->StatisticData.TargetH	=Cmd.PTry->StatisticData.TargetH;
					SendBack->StatisticData.TargetS	=Cmd.PTry->StatisticData.TargetS;
					SendBack->StatisticData.TargetV	=Cmd.PTry->StatisticData.TargetV;
					SendBack->StatisticData.SigmaH	=Cmd.PTry->StatisticData.SigmaH;
					SendBack->StatisticData.SigmaS	=Cmd.PTry->StatisticData.SigmaS;
					SendBack->StatisticData.SigmaV	=Cmd.PTry->StatisticData.SigmaV;
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckColorDifferenceTryResult::IntegrationAckColorDifferenceTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckColorDifferenceTryResult::Load(QIODevice *f)
{
	if(::Load(f,ResultMoveDx)==false)	return false;
	if(::Load(f,ResultMoveDy)==false)	return false;
	if(::Load(f,Error		)==false)	return false;
	if(::Load(f,LenOK		)==false)	return false;
	if(::Load(f,LenNG		)==false)	return false;
	if(::Load(f,DeltaE		)==false)	return false;
	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;
	if(ReferenceColor1.Load(f)==false)
		return false;
	if(ReferenceColor2.Load(f)==false)
		return false;
	if(f->read((char *)&StatisticData ,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}
bool	IntegrationAckColorDifferenceTryResult::Save(QIODevice *f)
{
	if(::Save(f,ResultMoveDx)==false)	return false;
	if(::Save(f,ResultMoveDy)==false)	return false;
	if(::Save(f,Error		)==false)	return false;
	if(::Save(f,LenOK		)==false)	return false;
	if(::Save(f,LenNG		)==false)	return false;
	if(::Save(f,DeltaE		)==false)	return false;
	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;
	if(ReferenceColor1.Save(f)==false)
		return false;
	if(ReferenceColor2.Save(f)==false)
		return false;
	if(f->write((const char *)&StatisticData ,sizeof(StatisticData))!=sizeof(StatisticData))
		return false;
	return true;
}