#include "XPropertySwitchPhasePacket.h"
#include "XGeneralFunc.h"
#include "PropertySwitchPhaseForm.h"

GUICmdSendAddManualBlock::GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SearchDot=0;
}

bool	GUICmdSendAddManualBlock::Load(QIODevice *f)
{
	if(::Load(f,SearchDot)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendAddManualBlock::Save(QIODevice *f)
{
	if(::Save(f,SearchDot)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AddSwitchPhaseAreaPacket	PPacket(this);
	PPacket.SearchDot	=SearchDot;
	PPacket.Area		=Area;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}

//=======================================================================================

GUICmdSendModifyItem::GUICmdSendModifyItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SearchDot=0;
}

bool	GUICmdSendModifyItem::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;

	return true;
}

bool	GUICmdSendModifyItem::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;

	return true;
}

void	GUICmdSendModifyItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ModifySwitchPhasePacket	PPacket(this);
	PPacket.SearchDot	=SearchDot;
	PPacket.ItemID		=ItemID;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}

//=======================================================================================
GUIReqTestMap::GUIReqTestMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqTestMap::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUIReqTestMap::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUIReqTestMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//CmdTestSwitchPhasePacket	PTestPacket(this);
	//AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	//if(Ab!=NULL){
	//	PTestPacket.LayerList=LayerList;
	//	Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	//}

	//SendAck(localPage);
}

//=======================================================================================
GUIClearMap::GUIClearMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUIClearMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//CmdClearSwitchPhasePacket	PTestPacket(this);
	//AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	//if(Ab!=NULL){
	//	Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	//}

	//SendAck(localPage);
}

//=======================================================================================

GUICmdReqPhaseItemList::GUICmdReqPhaseItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqPhaseItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPhaseItemList	*SendBack=GetSendBack(GUICmdAckPhaseItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(BBase!=NULL){
		CmdPhaseItemList	Cmd(this);
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
		SendBack->ItemsInfos	=Cmd.ItemsInfos;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPhaseItemList::GUICmdAckPhaseItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckPhaseItemList::Load(QIODevice *f)
{
	if(ItemsInfos.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckPhaseItemList::Save(QIODevice *f)
{
	if(ItemsInfos.Save(f)==false)
		return false;
	return true;
}

//-------------------------------------------------------------------------------------------------------
GUICmdReqItemInfoList::GUICmdReqItemInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemInfoList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	return true;
}
bool	GUICmdReqItemInfoList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	return true;
}

void	GUICmdReqItemInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemInfoList	*SendBack=GetSendBack(GUICmdAckItemInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(BBase!=NULL){
		CmdItemInfoList	Cmd(this);
		Cmd.Phase=Phase;
		BBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
		SendBack->ItemsInfos	=Cmd.ItemsInfos;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemInfoList::GUICmdAckItemInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemInfoList::Load(QIODevice *f)
{
	if(ItemsInfos.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckItemInfoList::Save(QIODevice *f)
{
	if(ItemsInfos.Save(f)==false)
		return false;
	return true;
}

//-------------------------------------------------------------------------------------------------------
GUICmdReqAddPhase::GUICmdReqAddPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAddPhase::Load(QIODevice *f)
{
	if(::Load(f,PhaseName)==false)	return false;
	return true;
}
bool	GUICmdReqAddPhase::Save(QIODevice *f)
{
	if(::Save(f,PhaseName)==false)	return false;
	return true;
}

void	GUICmdReqAddPhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAddPhase	*SendBack=GetSendBack(GUICmdAckAddPhase,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	int	PhaseNumb=GetPhaseNumb();
	if(GetLayersBase()->Reallocate(PhaseNumb+1)==true){
		GetParamGlobal()->SetPhaseString(PhaseNumb ,PhaseName);
		SendBack->AddedPhaseCode=PhaseNumb;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAddPhase::GUICmdAckAddPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAddPhase::Load(QIODevice *f)
{
	if(::Load(f,AddedPhaseCode)==false)	return false;
	return true;
}
bool	GUICmdAckAddPhase::Save(QIODevice *f)
{
	if(::Save(f,AddedPhaseCode)==false)	return false;
	return true;
}

GUICmdDeletePhase::GUICmdDeletePhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeletePhase::Load(QIODevice *f)
{
	if(::Load(f,PhaseCode)==false)	return false;
	return true;
}
bool	GUICmdDeletePhase::Save(QIODevice *f)
{
	if(::Load(f,PhaseCode)==false)	return false;
	return true;
}

void	GUICmdDeletePhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->RemovePhase(PhaseCode);
}

GUICmdDeleteAllPhases::GUICmdDeleteAllPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdDeleteAllPhases::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int PhaseCode=GetLayersBase()->GetPhaseNumb()-1;PhaseCode>=1;PhaseCode--){
		GetLayersBase()->RemovePhase(PhaseCode);
	}
}

//=======================================================================================
GUICmdCopyTargetToMaster::GUICmdCopyTargetToMaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCopyTargetToMaster::Load(QIODevice *f)
{
	if(::Load(f,SourcePhase)==false)	return false;
	if(::Load(f,DestPhase)==false)		return false;
	return true;
}
bool	GUICmdCopyTargetToMaster::Save(QIODevice *f)
{
	if(::Save(f,SourcePhase)==false)	return false;
	if(::Save(f,DestPhase)==false)		return false;
	return true;
}

void	GUICmdCopyTargetToMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Src=GetLayersBase()->GetPageDataPhase(SourcePhase);
	PageDataInOnePhase	*Dst=GetLayersBase()->GetPageDataPhase(DestPhase);
	if(Src!=NULL && Dst!=NULL){
		DataInPage	*Sp=Src->GetPageData(localPage);
		DataInPage	*Dp=Dst->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*SL=Sp->GetLayerData(Layer);
			DataInLayer	*DL=Dp->GetLayerData(Layer);
			DL->GetMasterBuff()=SL->GetTargetBuff();
			DL->GetMasterBuff().SetChanged(true);
		}
		CmdAdjustItemPosition	Cmd(GetLayersBase());
		Cmd.TargetPhase=DestPhase;
		SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Cmd);
		}
	}
}

//=======================================================================================
GUICmdReqMatchingResult::GUICmdReqMatchingResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMatchingResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMatchingResult	*SendBack=GetSendBack(GUICmdAckMatchingResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	CmdGatherItemResult	Cmd(GetLayersBase());
	SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	SendBack->Result	=Cmd.Result;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMatchingResult::GUICmdAckMatchingResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckMatchingResult::Load(QIODevice *f)
{
	if(Result.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckMatchingResult::Save(QIODevice *f)
{
	if(Result.Save(f)==false)	return false;
	return true;
}

//=======================================================================================
GUICmdReqEnableExecuteMatch::GUICmdReqEnableExecuteMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqEnableExecuteMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckEnableExecuteMatch	*SendBack=GetSendBack(GUICmdAckEnableExecuteMatch,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	if(localPage==0){
		SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
		if(BBase!=NULL){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(phase);
				SendBack->EnableExecuteMatch.Add(Ph->GetEnableExecute());
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckEnableExecuteMatch::GUICmdAckEnableExecuteMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckEnableExecuteMatch::Load(QIODevice *f)
{
	if(EnableExecuteMatch.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckEnableExecuteMatch::Save(QIODevice *f)
{
	if(EnableExecuteMatch.Save(f)==false)
		return false;
	return true;
}
//=======================================================================================
GUICmdSendEnableExecuteMatch::GUICmdSendEnableExecuteMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendEnableExecuteMatch::Load(QIODevice *f)
{
	if(EnableExecuteMatch.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendEnableExecuteMatch::Save(QIODevice *f)
{
	if(EnableExecuteMatch.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendEnableExecuteMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
		if(BBase!=NULL){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(phase);
				BoolClass	*B=EnableExecuteMatch.GetItem(phase);
				if(B!=NULL){
					Ph->SetEnableExecute(B->GetValue());
				}
			}
		}
	}
}
//=======================================================================================

GUICmdMakeAutoGeneration::GUICmdMakeAutoGeneration(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMakeAutoGeneration::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		CmdAutoGeneration	Cmd(GetLayersBase());
		SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
		if(BBase!=NULL){
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
		}
	}
}
//=======================================================================================

GUICmdDeleteAllItemInAllPhases::GUICmdDeleteAllItemInAllPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdDeleteAllItemInAllPhases::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		CmdDeleteAllItemInAllPhases	Cmd(GetLayersBase());
		SwitchPhaseBase *BBase=(SwitchPhaseBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
		if(BBase!=NULL){
			Cmd.LocalPage=localPage;
			BBase->TransmitDirectly(&Cmd);
		}
	}
}
//=======================================================================================

GUICmdReUseMark::GUICmdReUseMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReUseMark::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*LBase=GetLayersBase();
	SwitchPhaseBase *ABase=(SwitchPhaseBase *)LBase->GetAlgorithmBase(/**/"Basic",/**/"SwitchPhase");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(0);
		if(Ph!=NULL){
			SwitchPhaseInPage	*ApSource=dynamic_cast<SwitchPhaseInPage *>(Ph->GetPageData(localPage));
			for(AlgorithmItemPI	*a=ApSource->GetFirstData();a!=NULL;a=a->GetNext()){
				SwitchPhaseItem	*Item=dynamic_cast<SwitchPhaseItem *>(a);
				const	SwitchPhaseThreshold	*RThr=Item->GetThresholdR();
				int32	SearchDotForPhase	=RThr->SearchDot;
				FlexArea	Area=Item->GetArea();

				int	Page=localPage;
				int	SourcePhase=0;

				for(int phase=1;phase<GetPhaseNumb();phase++){
					AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(phase);
					AlgorithmInPageRoot	*Ap=APhase->GetPageData(Page);
					
					AddSwitchPhaseAreaPacket	Cmd(LBase);
					Cmd.Area=Area;
					Cmd.SearchDot=SearchDotForPhase		;

					PageDataInOnePhase	*Src=LBase->GetPageDataPhase(phase);
					PageDataInOnePhase	*Dst=LBase->GetPageDataPhase(SourcePhase);
					DataInPage	*Sp=Src->GetPageData(Page);
					DataInPage	*Dp=Dst->GetPageData(Page);
					for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
						DataInLayer	*SL=Sp->GetLayerData(Layer);
						DataInLayer	*DL=Dp->GetLayerData(Layer);
						DL->GetTargetBuff()=SL->GetMasterBuff();
					}
					LBase->SetCurrentPhase(SourcePhase);
					int	LastCurrentCalcPoint=LBase->GetCurrentCalcPoint();
					LBase->SetProcessDone(false);
					LBase->SetCurrentCalcPoint(LastCurrentCalcPoint);
					LBase->ExecuteStartByInspection	(false);

					int	Index=GetLayersBase()->GetIndexInCurrentStateExecuter(DataInExecuter::FinExecuteStartByInspection);
					LBase->SetProcessDone(false);
					LBase->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteStartByInspection);
					LBase->ExecutePreAlignment		(false);

					LBase->SetProcessDone(false);
					LBase->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreAlignment);
					LBase->ExecuteAlignment			(false);

					int	Cx,Cy;
					Area.GetCenter(Cx,Cy);

					AlignmentPacket2D	V;
					V.PosXOnTarget=Cx;
					V.PosYOnTarget=Cy;
					V.ShiftX=0;
					V.ShiftY=0;

					if(Ap!=NULL){
						Ap->GetAlignmentForProcessing(V);
						Cmd.Area.MoveToNoClip(V.ShiftX,V.ShiftY);
						Ap->TransmitDirectly(&Cmd);
					}
				}
			}
		}
	}
}
//=======================================================================================
