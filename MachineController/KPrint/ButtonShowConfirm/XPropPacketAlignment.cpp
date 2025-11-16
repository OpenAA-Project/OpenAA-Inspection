#include "ButtonShowConfirmResource.h"
#include "XPropPacketAlignment.h"
#include "XAlignmentLargeLibrary.h"
#include "XPacketAlignmentLarge.h"


bool	AlignmentAreaList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)	return false;
	if(::Save(f,Layer)==false)	return false;
	int	d=(int)Priority;
	if(::Save(f,d)==false)	return false;
	return true;
}
bool	AlignmentAreaList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)	return false;
	if(::Load(f,Layer)==false)	return false;
	int	d;
	if(::Load(f,d)==false)	return false;
	Priority	=(XAlignmentLargeArea::_EnumPriority)d;
	return true;
}

QString	AlignmentAreaList::GetPriorityString(void)
{
	switch(Priority){
	case XAlignmentLargeArea::_PriorityNone	:	return LangSolver.GetString(XPropPacketAlignment_LS,LID_19)/*"None"*/;
	case XAlignmentLargeArea::_PriorityHigh	:	return LangSolver.GetString(XPropPacketAlignment_LS,LID_20)/*"蜆ｪ蜈�鬮�*/;
	case XAlignmentLargeArea::_PriorityMiddle:	return LangSolver.GetString(XPropPacketAlignment_LS,LID_21)/*"蜆ｪ蜈�荳ｭ"*/;
	case XAlignmentLargeArea::_PriorityLow	:	return LangSolver.GetString(XPropPacketAlignment_LS,LID_22)/*"蜆ｪ蜈�菴�*/;
	case XAlignmentLargeArea::_PriorityGlobal:	return LangSolver.GetString(XPropPacketAlignment_LS,LID_23)/*"繧ｰ繝ｭ繝ｼ繝舌Ν"*/;
	}
}

AlignmentAreaList	&AlignmentAreaList::operator=(const AlignmentAreaList &src)
{
	AreaID		=src.AreaID;
	Layer		=src.Layer;
	Priority	=src.Priority;
	return *this;
}

AlignmentAreaListContainer	&AlignmentAreaListContainer::operator=(const AlignmentAreaListContainer &src)
{
	RemoveAll();
	for(AlignmentAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlignmentAreaList	*b=new AlignmentAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

IntegrationReqAlignmentAreaInfo::IntegrationReqAlignmentAreaInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	return true;
}
bool	IntegrationReqAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	return true;
}

void	IntegrationReqAlignmentAreaInfo::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckAlignmentAreaInfo	*SendBack=GetSendBackIntegration(IntegrationAckAlignmentAreaInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				for(int Layer=0;Layer<GetLayerNumb(LocalPage);Layer++){
					CmdReqAlignmentLargeAreaListWithMark	Cmd(GetLayersBase());
					Ap->GetLayerData(Layer)->TransmitDirectly(&Cmd);
					for(ListAreaIDInfo *a=Cmd.AreaList.GetFirst();a!=NULL;a=a->GetNext()){
						AlignmentAreaList	*L=new AlignmentAreaList();
						L->AreaID	=a->AreaID;
						L->Layer	=a->Layer;
						L->Priority	=a->Priority;
						SendBack->Container.AppendList(L);
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlignmentAreaInfo::IntegrationAckAlignmentAreaInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckAlignmentAreaInfo::Load(QIODevice *f)
{
	if(Container.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckAlignmentAreaInfo::Save(QIODevice *f)
{
	if(Container.Save(f)==false)	return false;
	return true;
}

//============================================================================================================

bool	AlignmentMarkList::Save(QIODevice *f)
{
	if(f->write((const char *)&MarkThresholdData ,sizeof(MarkThresholdData))!=sizeof(MarkThresholdData))
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}
bool	AlignmentMarkList::Load(QIODevice *f)
{
	if(f->read((char *)&MarkThresholdData ,sizeof(MarkThresholdData))!=sizeof(MarkThresholdData))
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	return true;
}

AlignmentMarkList	&AlignmentMarkList::operator=(const AlignmentMarkList &src)
{
	MarkThresholdData	=src.MarkThresholdData;
	MatchingRate		=src.MatchingRate;
	return *this;
}
AlignmentMarkListContainer	&AlignmentMarkListContainer::operator=(const AlignmentMarkListContainer &src)
{
	RemoveAll();
	for(AlignmentMarkList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlignmentMarkList	*b=new AlignmentMarkList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

IntegrationReqAlignmentMarkInfo::IntegrationReqAlignmentMarkInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationReqAlignmentMarkInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Layer)==false)	return false;
	if(::Load(f,AreaID)==false)	return false;
	return true;
}
bool	IntegrationReqAlignmentMarkInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Layer)==false)	return false;
	if(::Save(f,AreaID)==false)	return false;
	return true;
}
void	IntegrationReqAlignmentMarkInfo::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckAlignmentMarkInfo	*SendBack=GetSendBackIntegration(IntegrationAckAlignmentMarkInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmInLayerPLI	*AL=(AlgorithmInLayerPLI *)Ap->GetLayerData(Layer);
				for(AlgorithmItemPLI *a=AL->GetFirstData();a!=NULL;a=a->GetNext()){
					XAlignmentLarge	*AItem=dynamic_cast<XAlignmentLarge *>(a);
					if(AItem!=NULL){
						if(AItem->AreaID==AreaID){
							const AlignmentLargeThreshold	*R=AItem->GetThresholdR();
							AlignmentMarkList	*d=new AlignmentMarkList();
							AItem->GetXY(d->MarkThresholdData.x1,d->MarkThresholdData.y1
										,d->MarkThresholdData.x2,d->MarkThresholdData.y2);
							d->MarkThresholdData.ItemID	=AItem->GetID();
							d->MarkThresholdData.MoveDotX	=R->MoveDotX;
							d->MarkThresholdData.MoveDotY	=R->MoveDotY;
							d->MarkThresholdData.MoveDotX2	=R->MoveDotX2;
							d->MarkThresholdData.MoveDotY2	=R->MoveDotY2;
							d->MarkThresholdData.MaxCountHLine	=R->MaxCountHLine;
							d->MarkThresholdData.MaxCountVLine	=R->MaxCountVLine;
							d->MarkThresholdData.JudgeWithBrDif	=R->JudgeWithBrDif;

							CmdReqAlignmentLargeFinalResult	Cmd(GetLayersBase());
							Cmd.Item=AItem;
							ABase->TransmitDirectly(&Cmd);
							if(Cmd.FinalResult!=NULL){
								d->MatchingRate=Cmd.FinalResult->Match;
							}
							else{
								d->MatchingRate=0;
							}

							SendBack->Container.AppendList(d);
						}
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlignmentMarkInfo::IntegrationAckAlignmentMarkInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckAlignmentMarkInfo::Load(QIODevice *f)
{
	if(Container.Load(f)==false)	return false;
	return true;
}
bool	IntegrationAckAlignmentMarkInfo::Save(QIODevice *f)
{
	if(Container.Save(f)==false)	return false;
	return true;
}

//============================================================================================================

IntegrationReqAlignmentPointResult::IntegrationReqAlignmentPointResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqAlignmentPointResult::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,localX	)==false)	return false;
	if(::Load(f,localY	)==false)	return false;
	return true;
}
bool	IntegrationReqAlignmentPointResult::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,localX	)==false)	return false;
	if(::Save(f,localY	)==false)	return false;
	return true;
}

void	IntegrationReqAlignmentPointResult::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckAlignmentPointResult	*SendBack=GetSendBackIntegration(IntegrationAckAlignmentPointResult,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlignmentPacket2D	P;
				P.PosXOnTarget=localX;
				P.PosYOnTarget=localY;
				Ap->GetAlignmentForProcessing(P);
				SendBack->ShiftX			=P.ShiftX;
				SendBack->ShiftY			=P.ShiftY;
				SendBack->RotationRadian	=P.Rotation;
			}
		}
	}
	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlignmentPointResult::IntegrationAckAlignmentPointResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
	ShiftX			=0;
	ShiftY			=0;
	RotationRadian	=0;
}
bool	IntegrationAckAlignmentPointResult::Load(QIODevice *f)
{
	if(::Load(f,ShiftX	)==false)	return false;
	if(::Load(f,ShiftY	)==false)	return false;
	if(::Load(f,RotationRadian)==false)	return false;
	return true;
}
bool	IntegrationAckAlignmentPointResult::Save(QIODevice *f)
{
	if(::Save(f,ShiftX	)==false)	return false;
	if(::Save(f,ShiftY	)==false)	return false;
	if(::Save(f,RotationRadian)==false)	return false;
	return true;
}

//===============================================================================

IntegrationReqAlignmentItem::IntegrationReqAlignmentItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqAlignmentItem::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Layer)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	IntegrationReqAlignmentItem::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Layer)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	return true;
}
void	IntegrationReqAlignmentItem::Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName)
{
	int	LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationAckAlignmentItem	*SendBack=GetSendBackIntegration(IntegrationAckAlignmentItem,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);
	SendBack->AreaID=-1;
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeAlignmentLarge);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmInLayerRoot	*AL=Ap->GetLayerData(Layer);
				if(AL!=NULL){
					XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(AL->SearchIDItem(ItemID));
					if(Item!=NULL){
						SendBack->AreaID=Item->AreaID;
					}
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlignmentItem::IntegrationAckAlignmentItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckAlignmentItem::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)	return false;
	return true;
}
bool	IntegrationAckAlignmentItem::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)	return false;
	return true;
}

