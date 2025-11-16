#include "XPropertyCheckDataValidationPacket.h"
#include "XCheckDataValidation.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdSendAddManualCheckDataValidation::GUICmdSendAddManualCheckDataValidation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualCheckDataValidation::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,LibType)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;

	int32	d;
	if(::Load(f,d)==false)
		return false;
	VType=(CheckDataValidationType)d;

	return true;
}
bool	GUICmdSendAddManualCheckDataValidation::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,LibType)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;

	int32	d=(int32)VType;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	GUICmdSendAddManualCheckDataValidation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
	if(BBase!=NULL){
		CheckDataValidationInPage	*PData=dynamic_cast<CheckDataValidationInPage *>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddByteCheckDataValidationItemPacket	Cmd(GetLayersBase());
			Cmd.Buff		=BItem;
			Cmd.Area		=Area;
			Cmd.LayerList	=LayerList;
			Cmd.LibType		=LibType;
			Cmd.LibID		=LibID;
			Cmd.VType		=VType;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=============================================================================
bool	CheckDataValidationGridList::Save(QIODevice *f)
{
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	return true;
}
bool	CheckDataValidationGridList::Load(QIODevice *f)
{
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;

	return true;
}



GUICmdReqGridList::GUICmdReqGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGridList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	int32	d;
	if(::Load(f,d)==false)	return false;
	VType=(CheckDataValidationType)d;
	return true;
}
bool	GUICmdReqGridList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	int32	d=(int32)VType;
	if(::Save(f,d)==false)	return false;
	return true;
}
void	GUICmdReqGridList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGridList	*SendBack=GetSendBack(GUICmdAckGridList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			CheckDataValidationInPage	*PData=dynamic_cast<CheckDataValidationInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				for(AlgorithmItemPI *a=PData->GetFirstData();a!=NULL;a=a->GetNext()){
					if(a->GetItemClassType()==VType){
						CheckDataValidationGridList	*L=new CheckDataValidationGridList();
						L->Page=GetLayersBase()->GetGlobalPageFromLocal(localPage);
						L->ItemID=a->GetID();
						const	AlgorithmThreshold	*r=a->GetThresholdBaseReadable(GetLayersBase());
						const CheckDataValidationThresholdBase	*RThr=dynamic_cast<const CheckDataValidationThresholdBase *>(r);
						L->LibType	=RThr->LibType;
						L->LibID	=RThr->LibID;
						a->GetXY(L->x1,L->y1,L->x2,L->y2);
						SendBack->ListData.AppendList(L);
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckGridList::GUICmdAckGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckGridList::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckGridList::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)	return false;
	return true;
}

//==============================================================================================
GUICmdReqCheckDataValidationItemData::GUICmdReqCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqCheckDataValidationItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdReqCheckDataValidationItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	return true;
}
void	GUICmdReqCheckDataValidationItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckCheckDataValidationItemData	*SendBack=GetSendBack(GUICmdAckCheckDataValidationItemData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			CheckDataValidationInPage	*PData=dynamic_cast<CheckDataValidationInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				CheckDataValidationThresholdBase	*RThr=dynamic_cast<CheckDataValidationThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				RThr->Save(&Buff);
				SendBack->Area		=a->GetArea();
				SendBack->BItem		=Buff.buffer();
				SendBack->LibType	=RThr->LibType;
				SendBack->LibID		=RThr->LibID;
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckCheckDataValidationItemData::GUICmdAckCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckCheckDataValidationItemData::Load(QIODevice *f)
{
	if(::Load(f,BItem	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	if(Area.Load(f)==false)			return false;
	return true;
}
bool	GUICmdAckCheckDataValidationItemData::Save(QIODevice *f)
{
	if(::Save(f,BItem	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	if(Area.Save(f)==false)			return false;
	return true;
}

	
GUICmdSetCheckDataValidationItemData::GUICmdSetCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetCheckDataValidationItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,BItem	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	return true;
}
bool	GUICmdSetCheckDataValidationItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,BItem	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	return true;
}
void	GUICmdSetCheckDataValidationItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			CheckDataValidationInPage	*PData=dynamic_cast<CheckDataValidationInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				CheckDataValidationThresholdBase	*WThr=dynamic_cast<CheckDataValidationThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff(&BItem);
				Buff.open(QIODevice::ReadWrite);
				WThr->Load(&Buff);
			}
		}
	}
}
GUICmdDeleteCheckDataValidationItem::GUICmdDeleteCheckDataValidationItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeleteCheckDataValidationItem::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdDeleteCheckDataValidationItem::Save(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}

void	GUICmdDeleteCheckDataValidationItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			CheckDataValidationInPage	*PData=dynamic_cast<CheckDataValidationInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				PData->RemoveItem(a);
			}
		}
	}
}

//=========================================================================================

bool	ThresholdMemberList::Save(QIODevice *f)
{
	if(::Save(f,MemberName	)==false)	return false;
	int32	d=(int32)VType;
	if(::Save(f,d	)==false)	return false;

	return true;
}
bool	ThresholdMemberList::Load(QIODevice *f)
{
	if(::Load(f,MemberName	)==false)	return false;
	int32	d;
	if(::Load(f,d	)==false)	return false;
	VType=(DirectValueType)d;
	return true;
}

GUICmdReqThresholdMemberString::GUICmdReqThresholdMemberString(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqThresholdMemberString::Load(QIODevice *f)
{
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	return true;
}
bool	GUICmdReqThresholdMemberString::Save(QIODevice *f)
{
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	return true;
}

static	bool SearchMemberItemFunc(void *caller,AlgorithmItemRoot *item)
{
	int32	*LibID=(int32 *)caller;
	if(item->GetLibID()==*LibID){
		return true;
	}
	return false;
}

void	GUICmdReqThresholdMemberString::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckThresholdMemberString	*SendBack=GetSendBack(GUICmdAckThresholdMemberString,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	CheckDataValidationBase *BBase=(CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(LibType);
	if(BBase!=NULL){
		int	Phase=GetLayersBase()->GetCurrentPhase();
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);
			if(Ap!=NULL){
				AlgorithmItemPointerListContainer Items;
				Ap->EnumItems(&LibID,Items , SearchMemberItemFunc);				
				for(AlgorithmItemPointerList *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
					AlgorithmItemRoot	*a=p->GetItem();
						
					const AlgorithmThreshold	*RThr=a->GetThresholdBaseReadable(GetLayersBase());;
					ReportedTopicContainer RetContainer;
					RThr->MakeReportedTopics(RetContainer);
					for(ReportedTopic *r=RetContainer.GetFirst();r!=NULL;r=r->GetNext()){
						ThresholdMemberList	*t=new ThresholdMemberList();
						t->MemberName=r->Title;
						t->VType=r->GetType();
						SendBack->LContainer.AppendList(t);
					}
					break;
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckThresholdMemberString::GUICmdAckThresholdMemberString(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckThresholdMemberString::Load(QIODevice *f)
{
	if(LContainer.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckThresholdMemberString::Save(QIODevice *f)
{
	if(LContainer.Save(f)==false)	return false;
	return true;
}
