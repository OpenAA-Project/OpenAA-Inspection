#include "XFrameDefPacket.h"
#include "XGeneralFunc.h"
#include "XFrameDef.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SlaveCommReqMasterImage::SlaveCommReqMasterImage(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	GroupNumber	=-1;
	ZoomRate	=0;
	Gx1=Gy1=Gx2=Gy2;
}

	
bool	SlaveCommReqMasterImage::Load(QIODevice *f)
{
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,Gx1)==false)
		return false;
	if(::Load(f,Gy1)==false)
		return false;
	if(::Load(f,Gx2)==false)
		return false;
	if(::Load(f,Gy2)==false)
		return false;
	if(::Load(f,DestGCx)==false)
		return false;
	if(::Load(f,DestGCy)==false)
		return false;
	return true;
}
bool	SlaveCommReqMasterImage::Save(QIODevice *f)
{
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,Gx1)==false)
		return false;
	if(::Save(f,Gy1)==false)
		return false;
	if(::Save(f,Gx2)==false)
		return false;
	if(::Save(f,Gy2)==false)
		return false;
	if(::Save(f,DestGCx)==false)
		return false;
	if(::Save(f,DestGCy)==false)
		return false;
	return true;
}

void	SlaveCommReqMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckMasterImage	*S
	=(SlaveCommAckMasterImage *)((GetSendBackPacket()==NULL)?new SlaveCommAckMasterImage(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		FrameDefInPage	*Pg=(FrameDefInPage *)BBase->GetPageData(localPage);
		for(AlgorithmItemPI	*p=Pg->GetFirstData();p!=NULL;p=p->GetNext()){
			FrameDefItem	*a=dynamic_cast<FrameDefItem *>(p);
			if(a->GroupNumber==GroupNumber && a->Original==true){
				a->MakeMasterImage(S->MasterImage,ZoomRate
									,Gx1,Gy1,Gx2,Gy2
									,DestGCx,DestGCy);
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}


SlaveCommAckMasterImage::SlaveCommAckMasterImage(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

	
bool	SlaveCommAckMasterImage::Load(QIODevice *f)
{
	if(::Load(f,MasterImage)==false)
		return false;
	return true;
}
	
bool	SlaveCommAckMasterImage::Save(QIODevice *f)
{
	if(::Save(f,MasterImage)==false)
		return false;
	return true;
}
