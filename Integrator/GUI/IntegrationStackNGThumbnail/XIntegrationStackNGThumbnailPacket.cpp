#include "IntegrationStackNGThumbnailForm.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "swap.h"
#include "XDLLType.h"
#include "XCriticalFunc.h"
#include "XDataAlgorithmList.h"
#include "XIntegrationStackNGThumbnailPacket.h"
#include "XIntegrationPacketComm.h"


IntegrationCmdUpdateThreshold::IntegrationCmdUpdateThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdUpdateThreshold::Load(QIODevice *f)
{
	if(::Load(f,LibType			)==false)	return false;
	if(::Load(f,LibID			)==false)	return false;
	if(::Load(f,LearningMenuID	)==false)	return false;
	if(::Load(f,InspectionID	)==false)	return false;
	if(::Load(f,Phase			)==false)	return false;
	if(::Load(f,Page			)==false)	return false;
	if(::Load(f,ItemID			)==false)	return false;
	if(::Load(f,ShadowLevel		)==false)	return false;
	if(::Load(f,ShadowNumber	)==false)	return false;
	if(LRes.Load(f)==false)	return false;
	return true;
}
bool	IntegrationCmdUpdateThreshold::Save(QIODevice *f)
{
	if(::Save(f,LibType			)==false)	return false;
	if(::Save(f,LibID			)==false)	return false;
	if(::Save(f,LearningMenuID	)==false)	return false;
	if(::Save(f,InspectionID	)==false)	return false;
	if(::Save(f,Phase			)==false)	return false;
	if(::Save(f,Page			)==false)	return false;
	if(::Save(f,ItemID			)==false)	return false;
	if(::Save(f,ShadowLevel		)==false)	return false;
	if(::Save(f,ShadowNumber	)==false)	return false;
	if(LRes.Save(f)==false)	return false;
	return true;
}

void	IntegrationCmdUpdateThreshold::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetShadowTree(ShadowLevel,ShadowNumber)->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmItemPointerListContainer Items;
		AlgorithmInPageInOnePhase	*Ph=ABase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*Ap=Ph->GetPageData(Page);
			if(Ap!=NULL){
				if(ItemID>=0){
					ListLayerAndIDPack ItemList;
					for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
						ListLayerAndID	*a=new ListLayerAndID(Layer,ItemID);
						ItemList.AppendList(a);
					}
					Ap->GetItems(ItemList ,Items);					
				}
				else{
					Ap->GetAllItems(Items);
				}
			}
		}
		if(ItemID>=0){
			IntList LayerList;
			for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
				LayerList.Add(Layer);
			}
			for(int dphase=0;dphase<GetPhaseNumb();dphase++){
				AlgorithmInPageInOnePhase	*dPh=ABase->GetPageDataPhase(dphase);
				if(dPh!=NULL){
					AlgorithmInPageRoot	*Ap=dPh->GetPageData(Page);
					if(Ap!=NULL){
						for(AlgorithmItemPointerList *item=Items.GetFirst();item!=NULL;item=item->GetNext()){
							int	cx,cy;
							item->GetItem()->GetCenter(cx,cy);
							ListLayerIDLibNamePack ItemList;
							Ap->GetLayerAndItemID(cx,cy ,ItemList,LayerList);
							for(ListLayerIDLibName *d=ItemList.GetFirst();d!=NULL;d=d->GetNext()){
								if(d->LibID==LibID){
									Ap->UpdateThreshold(LearningMenuID,LibID,d->ID,LRes);
								}
							}
						}
					}
				}
			}
		}
		else{
			for(AlgorithmItemPointerList *item=Items.GetFirst();item!=NULL;item=item->GetNext()){
				AlgorithmItemRoot	*a=item->GetItem();
				if(a->GetLibID()==LibID){
					a->UpdateThreshold(LearningMenuID,LRes);
				}
			}
		}
	}
}


IntegrationCmdReqLearningMenu::IntegrationCmdReqLearningMenu(LayersBase *Base,const QString &EmitterRoot ,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdReqLearningMenu::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	return true;
}
bool	IntegrationCmdReqLearningMenu::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	return true;
}

void	IntegrationCmdReqLearningMenu::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckLearningMenu	*SendBack=GetSendBackIntegration(IntegrationCmdAckLearningMenu,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);
	
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		SendBack->MenuDimNumb=ABase->GetLearningMenu(SendBack->LearningMenuDim,100);
	}
	else{
		SendBack->MenuDimNumb=0;
	}
	LearningRegister	*L=GetLayersBase()->GetLearningRegister();
	if(L!=NULL){
		SendBack->MenuDimNumb=L->GetLearningMenu(LibType,SendBack->LearningMenuDim,sizeof(SendBack->LearningMenuDim)/sizeof(SendBack->LearningMenuDim[0]));
	}
	else{
		SendBack->MenuDimNumb=0;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckLearningMenu::IntegrationCmdAckLearningMenu(LayersBase *Base,const QString &EmitterRoot ,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdAckLearningMenu::Load(QIODevice *f)
{

	if(::Load(f,MenuDimNumb)==false)	return false;
	for(int i=0;i<MenuDimNumb && i<100;i++){
		if(LearningMenuDim[i].Load(f)==false){
			return false;
		}
	}
	return true;
}
bool	IntegrationCmdAckLearningMenu::Save(QIODevice *f)
{
	if(::Save(f,MenuDimNumb)==false)	return false;
	for(int i=0;i<MenuDimNumb;i++){
		if(LearningMenuDim[i].Save(f)==false){
			return false;
		}
	}

	return true;
}

//===================================================================================
IntegrationCmdReqItemInfo::IntegrationCmdReqItemInfo(LayersBase *base
													,const QString &EmitterRoot ,const QString &EmitterName 
													,int SlaveNo)
:IntegrationCmdPacketBase(base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	IntegrationCmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	return true;
}
void	IntegrationCmdReqItemInfo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int32 LocalPage=cmd;
	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
	IntegrationCmdAckItemInfo	*SendBack=GetSendBackIntegration(IntegrationCmdAckItemInfo,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
			if(Ap!=NULL){
				AlgorithmItemRoot	*Item=Ap->GetItemData(Layer,ItemID);
				if(Item!=NULL){
					const AlgorithmThreshold	*RThr=Item->GetThresholdBaseReadable();
					RThr->MakeReportedTopics(SendBack->ReportedContainer);
				}
			}
		}
	}

	SendBack->Send(this,0,globalPage);
	CloseSendBackIntegration(SendBack);
}
	
IntegrationCmdAckItemInfo::IntegrationCmdAckItemInfo(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName
							,int SlaveNo)
:IntegrationCmdPacketBase(base,EmitterRoot,EmitterName,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckItemInfo::Load(QIODevice *f)
{
	return ReportedContainer.Load(f);
}
bool	IntegrationCmdAckItemInfo::Save(QIODevice *f)
{
	return ReportedContainer.Save(f);
}