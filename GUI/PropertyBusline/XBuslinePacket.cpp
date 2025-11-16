#include "XBuslinePacket.h"
#include "XGeneralFunc.h"


GUICmdSendAddManualBlock::GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	LibID=-1;
}

bool	GUICmdSendAddManualBlock::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendAddManualBlock::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAddBuslineItemPacket	PPacket(this);
	PPacket.LibID		=LibID;
	PPacket.LayerList	=LayerList;
	PPacket.Area		=Area;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}


GUIReqBuslineListForPacketPack::GUIReqBuslineListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUIReqBuslineListForPacketPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckBuslineListForPacketPack	*SendBack=GetSendBack(GUIAckBuslineListForPacketPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
	if(Ab!=NULL){
		MakeListPacket	RCmd(GetLayersBase());
		RCmd.ListInfo=&SendBack->Data;
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&RCmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckBuslineListForPacketPack::GUIAckBuslineListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIAckBuslineListForPacketPack::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUIAckBuslineListForPacketPack::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

//=======================================================================================
GUIReqGenerateBuslineItems::GUIReqGenerateBuslineItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqGenerateBuslineItems::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUIReqGenerateBuslineItems::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUIReqGenerateBuslineItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateBuslinePacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
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
	CmdTestBuslinePacket	PTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
	if(Ab!=NULL){
		PTestPacket.LayerList=LayerList;
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}

//=======================================================================================
GUIClearMap::GUIClearMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUIClearMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearBuslinePacket	PTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}
