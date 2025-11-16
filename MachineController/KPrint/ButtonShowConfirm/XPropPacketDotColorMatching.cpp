#include "XPropPacketDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
#include "XDotColorMatching.h"


IntegrationReqDotColorMatchingTryResult::IntegrationReqDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqDotColorMatchingTryResult::Load(QIODevice *f)
{
	if(ItemIndex.Load(f)==false)		return false;
	if(::Load(f,ThresholdData)==false)	return false;
	return true;
}
bool	IntegrationReqDotColorMatchingTryResult::Save(QIODevice *f)
{
	if(ItemIndex.Save(f)==false)		return false;
	if(::Save(f,ThresholdData)==false)	return false;
	return true;
}

void	IntegrationReqDotColorMatchingTryResult::Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckDotColorMatchingTryResult	*SendBack=GetSendBackIntegration(IntegrationAckDotColorMatchingTryResult,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeDotColorMatchingInspect);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(ItemIndex.Data.Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(Ap->GetItemData(ItemIndex.Data.Layer,ItemIndex.Data.ItemID));
				if(Item!=NULL){
					CmdDotColorMatchingSendTryThreshold	Cmd(GetLayersBase());
					Cmd.Src=Item;
					Cmd.ThresholdDataForTarget=ThresholdData;
					ABase->TransmitDirectly(&Cmd);

					memset(&SendBack->ResultInfoData,0,sizeof(SendBack->ResultInfoData));					
					SendBack->ResultInfoData.CenterBrightR				=Cmd.Target->CenterBrightR;
					SendBack->ResultInfoData.CenterBrightG				=Cmd.Target->CenterBrightG;
					SendBack->ResultInfoData.CenterBrightB				=Cmd.Target->CenterBrightB;
					SendBack->ResultInfoData.CenterTargetBrightR		=Cmd.Target->CenterTargetBrightR	;
					SendBack->ResultInfoData.CenterTargetBrightG		=Cmd.Target->CenterTargetBrightG	;
					SendBack->ResultInfoData.CenterTargetBrightB		=Cmd.Target->CenterTargetBrightB	;
					SendBack->ResultInfoData.CurrentRotationPatternNo	=Cmd.Target->CurrentRotationPatternNo	;
					SendBack->ResultInfoData.ResultDx					=Cmd.Target->ResultDx					;
					SendBack->ResultInfoData.ResultDy					=Cmd.Target->ResultDy					;
					SendBack->ResultInfoData.ResultSelfSeachDx			=Cmd.Target->ResultSelfSeachDx			;
					SendBack->ResultInfoData.ResultSelfSeachDy			=Cmd.Target->ResultSelfSeachDy			;
					SendBack->ResultInfoData.ResultCode					=Cmd.Target->ResultCode					;

					ResultPosList	*r=Cmd.PTry->Result->GetPosListFirst();
					if(r!=NULL){
						if((r->result & 0xFFFFF)==0x10500){
							SendBack->ResultInfoData.ResultCode	=5;	//NG By Red
							SendBack->ResultInfoData.NGResultGroundSize		=r->GetResult1();
							SendBack->ResultInfoData.NGResultGroundLength	=r->GetResult2();
						}
						else
						if((r->result & 0xF00FF)==0x10000){
							SendBack->ResultInfoData.ResultCode	=2;		//NG By NGCount
							SendBack->ResultInfoData.NGResultSize	=r->GetResult1();
							SendBack->ResultInfoData.NGResultLength	=r->GetResult2();
						}
						else
						if((r->result & 0xF00FF)==0x10010){
							SendBack->ResultInfoData.ResultCode	=12;	//NG By Ground NGCount
							SendBack->ResultInfoData.NGResultGroundSize		=r->GetResult1();
							SendBack->ResultInfoData.NGResultGroundLength	=r->GetResult2();
						}
						else
						if((r->result & 0xF00FF)==0x10002){
							SendBack->ResultInfoData.ResultCode	=4;		//NG By NGLength
							SendBack->ResultInfoData.NGResultSize	=r->GetResult1();
							SendBack->ResultInfoData.NGResultLength	=r->GetResult2();
						}
						else
						if((r->result & 0xF00FF)==0x10012){
							SendBack->ResultInfoData.ResultCode	=14;	//NG By Ground NGLength
							SendBack->ResultInfoData.NGResultGroundSize		=r->GetResult1();
							SendBack->ResultInfoData.NGResultGroundLength	=r->GetResult2();
						}
					}
					if(Cmd.Target->ResultCode==3){
						SendBack->ResultInfoData.ResultCode	=3;		//NG MultiCount
						SendBack->ResultInfoData.NGResultSize		=Cmd.PTry->Result->GetResult2();	
						SendBack->ResultInfoData.NGResultMultiCount	=Cmd.PTry->Result->GetResult1();
					}
					for(ResultPosList *p=Cmd.PTry->Result->GetPosListFirst();p!=NULL;p=p->GetNext()){
						SendBack->NGShape+=p->NGShape;
					}
					SendBack->NGShape.MoveToNoClip(Cmd.PTry->Result->GetTotalShiftedX(),Cmd.PTry->Result->GetTotalShiftedY());
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckDotColorMatchingTryResult::IntegrationAckDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckDotColorMatchingTryResult::Load(QIODevice *f)
{
	if(f->read((char *)&ResultInfoData ,sizeof(ResultInfoData))!=sizeof(ResultInfoData))
		return false;
	if(NGShape.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationAckDotColorMatchingTryResult::Save(QIODevice *f)
{
	if(f->write((const char *)&ResultInfoData ,sizeof(ResultInfoData))!=sizeof(ResultInfoData))
		return false;
	if(NGShape.Save(f)==false)
		return false;
	return true;
}
