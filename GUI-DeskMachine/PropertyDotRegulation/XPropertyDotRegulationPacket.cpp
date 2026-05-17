#include "XPropertyDotRegulationPacket.h"
#include "XDotRegulation.h"

GUICmdReqAddDotRegulationArea::GUICmdReqAddDotRegulationArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAddDotRegulationArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Layers.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAddDotRegulationArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Layers.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAddDotRegulationArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DotRegulation");
	if(AlignBase!=NULL){
		DotRegulationInPage	*PData=dynamic_cast<DotRegulationInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			for(IntClass *c=Layers.GetFirst();c!=NULL;c=c->GetNext()){
				AlgorithmInLayerRoot	*DL=PData->GetLayerData(c->GetValue());
				CmdAddDotArea	DCmd(GetLayersBase());
				DCmd.Area=Area;
				DL->TransmitDirectly(&DCmd);
			}
		}
		return;
	}

}

//=======================================================================================

GUICmdReqPickup::GUICmdReqPickup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Threshold	=0;
	Layer		=0;
}


bool	GUICmdReqPickup::Load(QIODevice *f)
{
	if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqPickup::Save(QIODevice *f)
{
	if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqPickup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DotRegulation");
	if(AlignBase!=NULL){
		DotRegulationInPage	*PData=dynamic_cast<DotRegulationInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			AlgorithmInLayerRoot	*DL=PData->GetLayerData(Layer);
			DL->TransmitDirectly(this);
		}
	}
}

//=======================================================================================

GUICmdReqXPosList::GUICmdReqXPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=0;
}
bool	GUICmdReqXPosList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqXPosList::Save(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqXPosList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckXPosList	*SendBack=GetSendBack(GUICmdAckXPosList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DotRegulation");
	if(AlignBase!=NULL){
		DotRegulationInPage	*PData=dynamic_cast<DotRegulationInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			AlgorithmInLayerRoot	*DL=PData->GetLayerData(Layer);
			DL->TransmitDirectly(SendBack);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckXPosList::GUICmdAckXPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckXPosList::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckXPosList::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckXPosList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//=======================================================================================

GUICmdReqYPosList::GUICmdReqYPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=0;
}
bool	GUICmdReqYPosList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqYPosList::Save(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqYPosList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckXPosList	*SendBack=GetSendBack(GUICmdAckXPosList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DotRegulation");
	if(AlignBase!=NULL){
		DotRegulationInPage	*PData=dynamic_cast<DotRegulationInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			AlgorithmInLayerRoot	*DL=PData->GetLayerData(Layer);
			DL->TransmitDirectly(SendBack);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckYPosList::GUICmdAckYPosList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckYPosList::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckYPosList::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckYPosList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//=======================================================================================

GUICmdReqBrightnessList::GUICmdReqBrightnessList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=0;
}
bool	GUICmdReqBrightnessList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqBrightnessList::Save(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqBrightnessList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckXPosList	*SendBack=GetSendBack(GUICmdAckXPosList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DotRegulation");
	if(AlignBase!=NULL){
		DotRegulationInPage	*PData=dynamic_cast<DotRegulationInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			AlgorithmInLayerRoot	*DL=PData->GetLayerData(Layer);
			DL->TransmitDirectly(SendBack);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBrightnessList::GUICmdAckBrightnessList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckBrightnessList::Load(QIODevice *f)
{
	//if(::Load(f,List)==false)
	//	return false;
	return true;
}
bool	GUICmdAckBrightnessList::Save(QIODevice *f)
{
	//if(::Save(f,List)==false)
	//	return false;
	return true;
}

void	GUICmdAckBrightnessList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}