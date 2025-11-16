#include "ButtonSelectLearningTargetImageResource.h"
#include "XSelectLearningPacketResource.h"
#include "XSelectLearningPacket.h"
#include "XGeneralFunc.h"
#include "XLearningRegist.h"

bool	LearningImageList::Save(QIODevice *f)
{
	if(::Save(f,CreateTime)==false)
		return false;
	return true;
}
bool	LearningImageList::Load(QIODevice *f)
{
	if(::Load(f,CreateTime)==false)
		return false;
	return true;
}
LearningImageList	&LearningImageList::operator=(LearningImageList &src)
{
	CreateTime=src.CreateTime;
	return *this;
}
	
bool	LearningImageListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(LearningImageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	LearningImageListContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		LearningImageList *a=new LearningImageList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//======================================================================
GUICmdReqLearningStockerList::GUICmdReqLearningStockerList(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqLearningStockerList::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendLearningStockerList	*SendBack=GetSendBack(GUICmdSendLearningStockerList,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);

	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendLearningStockerList::GUICmdSendLearningStockerList(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendLearningStockerList::Load(QIODevice *f)
{
	if(Stocker.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendLearningStockerList::Save(QIODevice *f)
{
	if(Stocker.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendLearningStockerList::MakeData(int localPage)
{
	Stocker.RemoveAll();
	for(LearningImage *L=GetLayersBase()->GetPageData(localPage)->LearningImageStocker.GetFirst();L!=NULL;L=L->GetNext()){
		LearningImageList	*a=new LearningImageList();
		a->CreateTime=L->GetCreatedTime();
		Stocker.AppendList(a);
	}
}
void	GUICmdSendLearningStockerList::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//======================================================================
GUICmdReqSetLearningImage::GUICmdReqSetLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSetLearningImage::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	if(::Load(f,Mastered)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSetLearningImage::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	if(::Save(f,Mastered)==false){
		return false;
	}
	return true;
}
void	GUICmdReqSetLearningImage::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSetLearningImage	*SendBack=GetSendBack(GUICmdSendSetLearningImage,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);

	LearningImage	*f=GetLayersBase()->GetPageData(localPage)->Find(CreatedTime);
	if(Mastered==true){
		GetLayersBase()->GetPageData(localPage)->RestoreAllLearningImageMaster();
		if(f!=NULL){
			GetLayersBase()->GetPageData(localPage)->AddShowingLearningImageMaster(f);
			f->GetOrgLocalArea(  SendBack->LocalX1
								,SendBack->LocalY1
								,SendBack->LocalX2
								,SendBack->LocalY2);
		}
		else{
			SendBack->LocalX1=-1;
			SendBack->LocalY1=-1;
			SendBack->LocalX2=-1;
			SendBack->LocalY2=-1;
		}
	}
	else{
		GetLayersBase()->GetPageData(localPage)->RestoreAllLearningImageTarget();
		if(f!=NULL){
			GetLayersBase()->GetPageData(localPage)->AddShowingLearningImageTarget(f);
			f->GetOrgLocalArea(  SendBack->LocalX1
								,SendBack->LocalY1
								,SendBack->LocalX2
								,SendBack->LocalY2);
		}
		else{
			SendBack->LocalX1=-1;
			SendBack->LocalY1=-1;
			SendBack->LocalX2=-1;
			SendBack->LocalY2=-1;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

	
GUICmdSendSetLearningImage::GUICmdSendSetLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LocalX1	=-1;
	LocalY1	=-1;
	LocalX2	=-1;
	LocalY2	=-1;
}
bool	GUICmdSendSetLearningImage::Load(QIODevice *f)
{
	if(::Load(f,LocalX1)==false)
		return false;
	if(::Load(f,LocalY1)==false)
		return false;
	if(::Load(f,LocalX2)==false)
		return false;
	if(::Load(f,LocalY2)==false)
		return false;
	return true;
}
bool	GUICmdSendSetLearningImage::Save(QIODevice *f)
{
	if(::Save(f,LocalX1)==false)
		return false;
	if(::Save(f,LocalY1)==false)
		return false;
	if(::Save(f,LocalX2)==false)
		return false;
	if(::Save(f,LocalY2)==false)
		return false;
	return true;
}

void	GUICmdSendSetLearningImage::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//======================================================================
GUICmdReqDeleteLearningImage::GUICmdReqDeleteLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqDeleteLearningImage::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqDeleteLearningImage::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	return true;
}
void	GUICmdReqDeleteLearningImage::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSetLearningImage	*SendBack=GetSendBack(GUICmdSendSetLearningImage,GetLayersBase(),/**/"ANY",/**/"ANY",localPage);

	LearningImage	*f=GetLayersBase()->GetPageData(localPage)->Find(CreatedTime);
	if(f!=NULL){
		GetLayersBase()->GetPageData(localPage)->DeleteLearning(f);
	}
}
