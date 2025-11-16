#include "XPropertyCounterPacket.h"
#include "XCounter.h"
#include "XGeneralFunc.h"
#include "XMasking.h"
	
GUICmdReqItemImage::GUICmdReqItemImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemImage::Load(QIODevice *f)
{
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	return true;
}
bool	GUICmdReqItemImage::Save(QIODevice *f)
{
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	return true;
}

void	GUICmdReqItemImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemImage	*SendBack=GetSendBack(GUICmdAckItemImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL && PData->GetItemCount()){
			CmdReqItemImage	Cmd(GetLayersBase());
			Cmd.Width				=Width;
			Cmd.Height				=Height;
			PData->TransmitDirectly(&Cmd);
			SendBack->ItemImage			=Cmd.ItemImage;
			SendBack->ItemBackGround	=Cmd.ItemBackGround;
			SendBack->ItemImageWithMask	=Cmd.ItemImageWithMask;

			SendBack->Angles			=Cmd.Angles;
			SendBack->RotatedImages		=Cmd.RotatedImages;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemImage::GUICmdAckItemImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemImage::Load(QIODevice *f)
{
	if(::Load(f,ItemImage)==false)
		return false;
	if(::Load(f,ItemBackGround)==false)
		return false;
	if(::Load(f,ItemImageWithMask)==false)
		return false;
	if(Angles.Load(f)==false)
		return false;
	int32	N=RotatedImages.count();
	if(::Load(f,N)==false)
		return false;
	RotatedImages.clear();
	for(int i=0;i<N;i++){
		QImage	tImg;
		if(::Load(f,tImg)==false)
			return false;
		RotatedImages.append(tImg);
	}
	return true;
}
bool	GUICmdAckItemImage::Save(QIODevice *f)
{
	if(::Save(f,ItemImage)==false)
		return false;
	if(::Save(f,ItemBackGround)==false)
		return false;
	if(::Save(f,ItemImageWithMask)==false)
		return false;
	if(Angles.Save(f)==false)
		return false;
	int32	N=RotatedImages.count();
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(::Save(f,RotatedImages[i])==false)
			return false;
	}
	return true;
}


GUICmdAddAreaManual::GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddAreaManual	Cmd(GetLayersBase());
			Cmd.Area	=LocalArea;
			GetLayersBase()->LockForLoadSave();
			PData->TransmitDirectly(&Cmd);
			GetLayersBase()->UnlockForLoadSave();
		}
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdAddMaskForCounter::GUICmdAddMaskForCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAddMaskForCounter::Load(QIODevice *f)
{
	if(LocalArea.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddMaskForCounter::Save(QIODevice *f)
{
	if(LocalArea.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddMaskForCounter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MaskingBase *MBase=(MaskingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(MBase!=NULL){
		MaskingInPage	*PData=dynamic_cast<MaskingInPage	*>(MBase->GetPageData(localPage));
		if(PData!=NULL){
			AddMaskingAreaPacket	Cmd(GetLayersBase());
			Cmd.Area	=LocalArea;
			for(int Layer=0;Layer<PData->GetLayerNumb();Layer++){
				Cmd.LayerList.Add(Layer);
			}
			Cmd.Effective	=false;
			PData->TransmitDirectly(&Cmd);
		}
	}
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			PData->ChangedMask=true;
		}
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdRemoveMask::GUICmdRemoveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdRemoveMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MaskingBase *MBase=(MaskingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(MBase!=NULL){
		MaskingInPage	*PData=dynamic_cast<MaskingInPage	*>(MBase->GetPageData(localPage));
		if(PData!=NULL){
			DelMaskingPacket	Cmd(GetLayersBase());
			for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
				Cmd.LayerList.Add(Layer);
			}
			Cmd.Effective	=false;
			PData->TransmitDirectly(&Cmd);
		}
	}
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage *>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			PData->ChangedMask=true;
		}
	}
	SendAck(localPage);
}

//=====================================================================================

GUICmdRegisterBackGround::GUICmdRegisterBackGround(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdRegisterBackGround::Load(QIODevice *f)
{
	if(::Load(f,SetBackGround)==false)
		return false;
	return true;
}
bool	GUICmdRegisterBackGround::Save(QIODevice *f)
{
	if(::Save(f,SetBackGround)==false)
		return false;
	return true;
}
void	GUICmdRegisterBackGround::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	{
		MaskingBase *BBase=(MaskingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
		if(BBase!=NULL){
			MaskingInPage	*PData=dynamic_cast<MaskingInPage *>(BBase->GetPageData(localPage));
			if(PData!=NULL){
				CmdMaskingMakeBackGround	RCmd(GetLayersBase());
				RCmd.MasterMode=false;
				PData->TransmitDirectly(&RCmd);
			}
		}
	}
	{
		CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
		if(BBase!=NULL){
			CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
			if(PData!=NULL){
				CmdSetBackGround	Cmd(GetLayersBase());
				Cmd.SetBackGround=SetBackGround;
				PData->TransmitDirectly(&Cmd);
			}
		}
	}
}

//=====================================================================================

GUICmdReqResultCounter::GUICmdReqResultCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqResultCounter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultCounter	*SendBack=GetSendBack(GUICmdAckResultCounter,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqResultCount	RCmd(GetLayersBase());
			PData->TransmitDirectly(&RCmd);
			SendBack->Count	 =RCmd.Count;
			SendBack->TimeOut=RCmd.TimeOut;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckResultCounter::GUICmdAckResultCounter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckResultCounter::Load(QIODevice *f)
{
	if(::Load(f,Count)==false)
		return false;
	if(::Load(f,TimeOut)==false)
		return false;
	return true;
}
bool	GUICmdAckResultCounter::Save(QIODevice *f)
{
	if(::Save(f,Count)==false)
		return false;
	if(::Save(f,TimeOut)==false)
		return false;
	return true;
}

//=====================================================================================

GUICmdReqAdoptedRate::GUICmdReqAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAdoptedRate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAdoptedRate	*SendBack=GetSendBack(GUICmdAckAdoptedRate,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqAdoptedRate	RCmd(GetLayersBase());
			PData->TransmitDirectly(&RCmd);
			SendBack->AdoptedRate=RCmd.AdoptedRate;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAdoptedRate::GUICmdAckAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAdoptedRate::Load(QIODevice *f)
{
	if(::Load(f,AdoptedRate)==false)
		return false;
	return true;
}
bool	GUICmdAckAdoptedRate::Save(QIODevice *f)
{
	if(::Save(f,AdoptedRate)==false)
		return false;
	return true;
}


GUICmdSendAdoptedRate::GUICmdSendAdoptedRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAdoptedRate::Load(QIODevice *f)
{
	if(::Load(f,AdoptedRate)==false)
		return false;
	return true;
}
bool	GUICmdSendAdoptedRate::Save(QIODevice *f)
{
	if(::Save(f,AdoptedRate)==false)
		return false;
	return true;
}
void	GUICmdSendAdoptedRate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdSetAdoptedRate	RCmd(GetLayersBase());
			RCmd.AdoptedRate	=AdoptedRate;
			PData->TransmitDirectly(&RCmd);
		}
	}
}


//=====================================================================================

GUICmdReqAdoptPixelsRate::GUICmdReqAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAdoptPixelsRate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAdoptPixelsRate	*SendBack=GetSendBack(GUICmdAckAdoptPixelsRate,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		SendBack->AdoptPixelsRate=BBase->AdoptPixelsRate;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAdoptPixelsRate::GUICmdAckAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAdoptPixelsRate::Load(QIODevice *f)
{
	if(::Load(f,AdoptPixelsRate)==false)
		return false;
	return true;
}
bool	GUICmdAckAdoptPixelsRate::Save(QIODevice *f)
{
	if(::Save(f,AdoptPixelsRate)==false)
		return false;
	return true;
}


GUICmdSendAdoptPixelsRate::GUICmdSendAdoptPixelsRate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAdoptPixelsRate::Load(QIODevice *f)
{
	if(::Load(f,AdoptPixelsRate)==false)
		return false;
	return true;
}
bool	GUICmdSendAdoptPixelsRate::Save(QIODevice *f)
{
	if(::Save(f,AdoptPixelsRate)==false)
		return false;
	return true;
}
void	GUICmdSendAdoptPixelsRate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		BBase->AdoptPixelsRate=AdoptPixelsRate;
	}
}


//=====================================================================================

GUICmdReqFocusLevel::GUICmdReqFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqFocusLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFocusLevel	*SendBack=GetSendBack(GUICmdAckFocusLevel,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		SendBack->FocusLevel=BBase->FocusLevel;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckFocusLevel::GUICmdAckFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckFocusLevel::Load(QIODevice *f)
{
	if(::Load(f,FocusLevel)==false)
		return false;
	return true;
}
bool	GUICmdAckFocusLevel::Save(QIODevice *f)
{
	if(::Save(f,FocusLevel)==false)
		return false;
	return true;
}


GUICmdSendFocusLevel::GUICmdSendFocusLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendFocusLevel::Load(QIODevice *f)
{
	if(::Load(f,FocusLevel)==false)
		return false;
	return true;
}
bool	GUICmdSendFocusLevel::Save(QIODevice *f)
{
	if(::Save(f,FocusLevel)==false)
		return false;
	return true;
}
void	GUICmdSendFocusLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		BBase->FocusLevel=FocusLevel;
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdSetFocusLevel	RCmd(GetLayersBase());
			PData->TransmitDirectly(&RCmd);
		}
	}
}
//=====================================================================================

GUICmdSendOutsideCalc::GUICmdSendOutsideCalc(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendOutsideCalc::Load(QIODevice *f)
{
	if(::Load(f,OutsideCalc)==false)
		return false;
	return true;
}
bool	GUICmdSendOutsideCalc::Save(QIODevice *f)
{
	if(::Save(f,OutsideCalc)==false)
		return false;
	return true;
}
void	GUICmdSendOutsideCalc::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		BBase->OutsideCalc=OutsideCalc;
	}
}
//=====================================================================================
GUICmdReqItemArea::GUICmdReqItemArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemArea	*SendBack=GetSendBack(GUICmdAckItemArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqItemArea	RCmd(GetLayersBase());
			RCmd.Areas	=&SendBack->Areas;
			PData->TransmitDirectly(&RCmd);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemArea::GUICmdAckItemArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemArea::Load(QIODevice *f)
{
	if(Areas.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckItemArea::Save(QIODevice *f)
{
	if(Areas.Save(f)==false)
		return false;
	return true;
}

//=====================================================================================

GUICmdSetFilterMode::GUICmdSetFilterMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetFilterMode::Load(QIODevice *f)
{
	if(::Load(f,FilterON)==false)
		return false;
	return true;
}
bool	GUICmdSetFilterMode::Save(QIODevice *f)
{
	if(::Save(f,FilterON)==false)
		return false;
	return true;
}

void	GUICmdSetFilterMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CounterBase *BBase=(CounterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Counter");
	if(BBase!=NULL){
		CounterInPage	*PData=dynamic_cast<CounterInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdSetFilterMode	Cmd(GetLayersBase());
			Cmd.FilterON	=FilterON;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
//=====================================================================================

GUICmdReqMaskCount::GUICmdReqMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqMaskCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMaskCount	*SendBack=GetSendBack(GUICmdAckMaskCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	MaskingBase *BBase=(MaskingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(BBase!=NULL){
		MaskingInPage	*PData=dynamic_cast<MaskingInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqMaskCount	RCmd(GetLayersBase());
			PData->TransmitDirectly(&RCmd);
			SendBack->MaskCount	=RCmd.CountNoEffective;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdAckMaskCount::GUICmdAckMaskCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMaskCount::Load(QIODevice *f)
{
	if(::Load(f,MaskCount)==false)
		return false;
	return true;
}
bool	GUICmdAckMaskCount::Save(QIODevice *f)
{
	if(::Save(f,MaskCount)==false)
		return false;
	return true;
}