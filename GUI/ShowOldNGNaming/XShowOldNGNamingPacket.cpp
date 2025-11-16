#include "ShowOldNGNamingResource.h"
#include "ShowOldNGNamingForm.h"
#include "XNaming.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XShowOldNGNamingPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==========================================================================

GUICmdReqNamingAreaList::GUICmdReqNamingAreaList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqNamingAreaList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqNamingAreaList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdReqNamingAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingAreaList	*SendBack=GetSendBack(GUICmdSendNamingAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	NamingBase	*Ab=(NamingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ph=Ab->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);
			if(Ap!=NULL){
				ReqBuildItemPointerNamingPage	Cmd(GetLayersBase());
				Cmd.Stocker=&SendBack->NamingArea;
				Ap->TransmitDirectly(&Cmd);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}

GUICmdSendNamingAreaList::GUICmdSendNamingAreaList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNamingAreaList::Load(QIODevice *f)
{
	if(NamingArea.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendNamingAreaList::Save(QIODevice *f)
{
	if(NamingArea.Save(f)==false){
		return false;
	}
	return true;
}

//==========================================================================

GUICmdReqOlderNGList::GUICmdReqOlderNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentInspectionID	=-1;
	GenerationLevel		=1;
	Phase				=0;
}

bool	GUICmdReqOlderNGList::Load(QIODevice *f)
{
	if(::Load(f,CurrentInspectionID)==false){
		return false;
	}
	if(::Load(f,GenerationLevel)==false){
		return false;
	}	
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqOlderNGList::Save(QIODevice *f)
{
	if(::Save(f,CurrentInspectionID)==false){
		return false;
	}
	if(::Save(f,GenerationLevel)==false){
		return false;
	}	
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdReqOlderNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendOlderNGList	*SendBack=GetSendBack(GUICmdSendOlderNGList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	NamingBase	*Ab=(NamingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ph=Ab->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*Ap=Ph->GetPageData(localPage);
			if(Ap!=NULL){
				ResultInspection	*Res=GetLayersBase()->GetBufferedOlderResult(CurrentInspectionID, GenerationLevel);
				if(Res!=NULL){
					NGAreaListContainer List;
					Res->BindNGAreaListContainer(localPage,List);
					for(NGAreaList *c=List.GetFirst();c!=NULL;c=c->GetNext()){
						ReqItemFromAreaName	Cmd(GetLayersBase());
						Cmd.AreaName	=c->GetAreaName();
						Ap->TransmitDirectly(&Cmd);
						if(Cmd.Item!=NULL){
							NamingNG	*NG=new NamingNG();
							NG->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(localPage);
							NG->NGCount		=c->GetNGCount();
							NG->ItemID		=Cmd.Item->GetID();
							SendBack->NGNaming.AppendList(NG);
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendOlderNGList::GUICmdSendOlderNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendOlderNGList::Load(QIODevice *f)
{
	if(NGNaming.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendOlderNGList::Save(QIODevice *f)
{
	if(NGNaming.Save(f)==false){
		return false;
	}
	return true;
}
