#include "CreateSpotReducerFormResource.h"
#include "XPropertySpotReducerPacket.h"
#include "XGeneralFunc.h"
#include "XSpotReducer.h"


GUICmdAddSpotReducerArea::GUICmdAddSpotReducerArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddSpotReducerArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,SpotBrightness)==false)
		return false;
	if(::Load(f,ReductionLevel)==false)
		return false;
	if(::Load(f,SpotArea)==false)
		return false;
	if(::Load(f,SpotCount)==false)
		return false;
	
	return true;
}
bool	GUICmdAddSpotReducerArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,SpotBrightness)==false)
		return false;
	if(::Save(f,ReductionLevel)==false)
		return false;
	if(::Save(f,SpotArea)==false)
		return false;
	if(::Save(f,SpotCount)==false)
		return false;
	return true;
}

void	GUICmdAddSpotReducerArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SpotReducer");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddSpotReducerAreaPacket	Cmd(this);
	Cmd.Area			=Area;
	Cmd.LayerList		=LayerList;
	Cmd.SpotBrightness	=SpotBrightness;
	Cmd.ReductionLevel	=ReductionLevel;
	Cmd.SpotArea		=SpotArea;
	Cmd.SpotCount		=SpotCount;
	SpotReducerInPage	*M=dynamic_cast<SpotReducerInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);
	
	SendAck(localPage);
}
