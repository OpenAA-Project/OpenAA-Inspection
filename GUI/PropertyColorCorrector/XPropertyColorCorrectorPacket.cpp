#include "XPropertyColorCorrectorPacket.h"
#include "XColorCorrector.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdSendAddManualColorCorrector::GUICmdSendAddManualColorCorrector(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualColorCorrector::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;

	int32	d;
	if(::Load(f,d)==false)
		return false;
	VType=(ColorCorrectorType)d;

	return true;
}
bool	GUICmdSendAddManualColorCorrector::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;

	int32	d=(int32)VType;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	GUICmdSendAddManualColorCorrector::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	ColorCorrectorBase *BBase=(ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		ColorCorrectorInPage	*PData=dynamic_cast<ColorCorrectorInPage *>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddByteColorCorrectorItemPacket	Cmd(GetLayersBase());
			Cmd.Buff		=BItem;
			Cmd.Area		=Area;
			Cmd.VType		=VType;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//=============================================================================
bool	ColorCorrectorGridList::Save(QIODevice *f)
{
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
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
bool	ColorCorrectorGridList::Load(QIODevice *f)
{
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
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
	VType=(ColorCorrectorType)d;
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
	
	ColorCorrectorBase *BBase=(ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorCorrectorInPage	*PData=dynamic_cast<ColorCorrectorInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				for(AlgorithmItemPI *a=PData->GetFirstData();a!=NULL;a=a->GetNext()){
					if(a->GetItemClassType()==VType){
						ColorCorrectorGridList	*L=new ColorCorrectorGridList();
						L->Page=GetLayersBase()->GetGlobalPageFromLocal(localPage);
						L->ItemID=a->GetID();
						const	AlgorithmThreshold	*r=a->GetThresholdBaseReadable(GetLayersBase());
						const ColorCorrectorThresholdBase	*RThr=dynamic_cast<const ColorCorrectorThresholdBase *>(r);
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
GUICmdReqColorCorrectorItemData::GUICmdReqColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdReqColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	return true;
}
void	GUICmdReqColorCorrectorItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorCorrectorItemData	*SendBack=GetSendBack(GUICmdAckColorCorrectorItemData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	ColorCorrectorBase *BBase=(ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorCorrectorInPage	*PData=dynamic_cast<ColorCorrectorInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				ColorCorrectorThresholdBase	*RThr=dynamic_cast<ColorCorrectorThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				RThr->Save(&Buff);
				SendBack->Area		=a->GetArea();
				SendBack->BItem		=Buff.buffer();
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorCorrectorItemData::GUICmdAckColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,BItem	)==false)	return false;
	if(Area.Load(f)==false)			return false;
	return true;
}
bool	GUICmdAckColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,BItem	)==false)	return false;
	if(Area.Save(f)==false)			return false;
	return true;
}

	
GUICmdSetColorCorrectorItemData::GUICmdSetColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,BItem	)==false)	return false;
	return true;
}
bool	GUICmdSetColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,BItem	)==false)	return false;
	return true;
}
void	GUICmdSetColorCorrectorItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorCorrectorBase *BBase=(ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorCorrectorInPage	*PData=dynamic_cast<ColorCorrectorInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				ColorCorrectorThresholdBase	*WThr=dynamic_cast<ColorCorrectorThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff(&BItem);
				Buff.open(QIODevice::ReadWrite);
				WThr->Load(&Buff);
			}
		}
	}
}
GUICmdDeleteColorCorrectorItem::GUICmdDeleteColorCorrectorItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeleteColorCorrectorItem::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdDeleteColorCorrectorItem::Save(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}

void	GUICmdDeleteColorCorrectorItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ColorCorrectorBase *BBase=(ColorCorrectorBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			ColorCorrectorInPage	*PData=dynamic_cast<ColorCorrectorInPage *>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				PData->RemoveItem(a);
			}
		}
	}
}
