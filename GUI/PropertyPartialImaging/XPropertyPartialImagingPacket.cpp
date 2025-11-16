#include "XPropertyPartialImagingPacket.h"
#include "XDisplayImagePacket.h"
#include "XPartialImaging.h"
#include "XMainSchemeMemory.h"



GUICmdAddAreaManual::GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Priority		=0;
	SaveTargetImage	=true;
	SaveOnlyInNG	=false;
	BufferType		=ImageBufferTarget;
}

bool	GUICmdAddAreaManual::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,SaveTargetImage)==false)
		return false;
	if(::Load(f,SaveOnlyInNG)==false)
		return false;
	if(::Load(f,BufferType)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdAddAreaManual::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,SaveTargetImage)==false)
		return false;
	if(::Save(f,SaveOnlyInNG)==false)
		return false;
	if(::Save(f,BufferType)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdAddAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	if(PBase==NULL)
		return;
	PartialImagingInPage	*PPage=dynamic_cast<PartialImagingInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdAddAreaPartialImaging	Da(GetLayersBase());
		Da.Area			=Area;
		Da.Priority		=Priority;
		Da.SaveTargetImage	=SaveTargetImage;
		Da.SaveOnlyInNG		=SaveOnlyInNG;
		Da.BufferType		=BufferType;
		Da.ItemName			=ItemName;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//================================================================================================================================

GUICmdEditAreaManual::GUICmdEditAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID			=-1;
	Priority		=0;
	SaveTargetImage	=true;
	SaveOnlyInNG	=false;
	BufferType		=ImageBufferTarget;
}

bool	GUICmdEditAreaManual::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,SaveTargetImage)==false)
		return false;
	if(::Load(f,SaveOnlyInNG)==false)
		return false;
	if(::Load(f,BufferType)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdEditAreaManual::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,SaveTargetImage)==false)
		return false;
	if(::Save(f,SaveOnlyInNG)==false)
		return false;
	if(::Save(f,BufferType)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdEditAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	if(PBase==NULL)
		return;
	PartialImagingInPage	*PPage=dynamic_cast<PartialImagingInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdEditAreaPartialImaging	Da(GetLayersBase());
		Da.ItemID			=ItemID;
		Da.Priority			=Priority;
		Da.SaveTargetImage	=SaveTargetImage;
		Da.SaveOnlyInNG		=SaveOnlyInNG;
		Da.BufferType		=BufferType;
		Da.ItemName			=ItemName;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//================================================================================================================================

GUICmdDeleteAreaManual::GUICmdDeleteAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID			=-1;
}

bool	GUICmdDeleteAreaManual::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdDeleteAreaManual::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdDeleteAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	if(PBase==NULL)
		return;
	PartialImagingInPage	*PPage=dynamic_cast<PartialImagingInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdDeletePartialImaging	Da(GetLayersBase());
		Da.ItemID			=ItemID;

		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//================================================================================================================================

GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID	=0;
}
bool	GUICmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
	
bool	GUICmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemInfo	*SendBack=GetSendBack(GUICmdSendItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	if(PBase==NULL)
		return;
	PartialImagingInPage	*PPage=dynamic_cast<PartialImagingInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqItemInfo	Da(GetLayersBase());
		Da.ItemID	=ItemID;
		PPage->TransmitDirectly(&Da);
		SendBack->ItemID			=Da.ItemID;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdSendItemInfo::GUICmdSendItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendItemInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdSendItemInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

//================================================================================================================================

GUICmdReqPartialImagingInfoList::GUICmdReqPartialImagingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqPartialImagingInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPartialImagingInfoList	*SendBack=GetSendBack(GUICmdSendPartialImagingInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PartialImaging");
	if(PBase==NULL)
		return;
	PartialImagingInPage	*PPage=dynamic_cast<PartialImagingInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqEnumInfo	Da(GetLayersBase());
		PPage->TransmitDirectly(&Da);
		SendBack->PInfoContainer	=Da.PInfoContainer;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendPartialImagingInfoList::GUICmdSendPartialImagingInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendPartialImagingInfoList::Load(QIODevice *f)
{
	if(PInfoContainer.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendPartialImagingInfoList::Save(QIODevice *f)
{
	if(PInfoContainer.Save(f)==false)
		return false;
	return true;
}

