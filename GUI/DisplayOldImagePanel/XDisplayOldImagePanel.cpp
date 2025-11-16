#include "DisplayOldImagePanelResource.h"
#include "XDisplayOldImagePanel.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XNaming.h"

NamingInfo::NamingInfo(void)
{
	GlobalPage=0;
}

bool	NamingInfo::Save(QIODevice *f)
{
	if(NamingArea.Save(f)==false)
		return false;
//	if(NamingOutline.Write(f)==false)
//		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

bool	NamingInfo::Load(QIODevice *f)
{
	if(NamingArea.Load(f)==false)
		return false;
//	if(NamingOutline.Read(f)==false)
//		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

//===============================================================================
GUICmdReqNamingInfo::GUICmdReqNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Phase=0;
}

bool	GUICmdReqNamingInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	return true;
}
bool	GUICmdReqNamingInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	return true;
}

void	GUICmdReqNamingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingInfo	*SendBack=GetSendBack(GUICmdSendNamingInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	NamingBase	*Ab=(NamingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ph=Ab->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			NamingInPage	*Ap=(NamingInPage *)Ph->GetPageData(localPage);
			if(Ap!=NULL){
				for(AlgorithmItemPI	*p=Ap->GetFirstData();p!=NULL;p=p->GetNext()){
					NamingItem	*Item=(NamingItem *)p;
					NamingInfo	*d=new NamingInfo();
					d->AreaName	=Item->GetItemName();
					d->NamingArea	=Item->GetArea();
					d->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(localPage);
					d->ItemID		=p->GetID();
					//d->NamingArea.MakeOutlineDot(d->NamingOutline);
					SendBack->NamingData.AppendList(d);
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNamingInfo::GUICmdSendNamingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNamingInfo::Load(QIODevice *f)
{
	if(NamingData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNamingInfo::Save(QIODevice *f)
{
	if(NamingData.Save(f)==false)
		return false;
	return true;
}
