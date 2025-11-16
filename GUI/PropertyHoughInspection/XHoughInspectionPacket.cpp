#include "XHoughInspectionPacket.h"
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
	CmdAddHoughItemPacket	PPacket(this);
	PPacket.LibID		=LibID;
	PPacket.LayerList	=LayerList;
	PPacket.Area		=Area;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
	if(Ab!=NULL){
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&PPacket);
	}
	SendAck(localPage);
}


GUIReqHoughListForPacketPack::GUIReqHoughListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUIReqHoughListForPacketPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckHoughListForPacketPack	*SendBack=GetSendBack(GUIAckHoughListForPacketPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
	if(Ab!=NULL){
		HoughMakeListPacket	RCmd(GetLayersBase());
		RCmd.ListInfo=&SendBack->Data;
		AlgorithmInPageRoot		*Pg=Ab->GetPageData(localPage);
		Pg->TransmitDirectly(&RCmd);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckHoughListForPacketPack::GUIAckHoughListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIAckHoughListForPacketPack::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUIAckHoughListForPacketPack::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

//=======================================================================================
GUIReqGenerateHoughItems::GUIReqGenerateHoughItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUIReqGenerateHoughItems::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUIReqGenerateHoughItems::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUIReqGenerateHoughItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdGenerateHoughPacket	PTestPacket(this);
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}

	SendAck(localPage);
}

