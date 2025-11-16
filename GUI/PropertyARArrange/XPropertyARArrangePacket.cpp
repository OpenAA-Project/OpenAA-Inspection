#include "PropertyARArrangeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyARArrange\XPropertyARArrangePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyARArrangePacket.h"
#include "XGeneralFunc.h"
#include "XARArrange.h"


GUICmdReqARLearningList::GUICmdReqARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqARLearningList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendARLearningList	*SendBack=GetSendBack(GUICmdSendARLearningList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	GetLayersBase()->GetPageData(localPage)->MakeLearningImagePointerContainer(SendBack->LearningPointerContainer);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendARLearningList::GUICmdSendARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendARLearningList::Load(QIODevice *f)
{
	if(LearningPointerContainer.Load(f,GetLayersBase())==false){
		return false;
	}
	return true;
}

bool	GUICmdSendARLearningList::Save(QIODevice *f)
{
	if(LearningPointerContainer.Save(f)==false){
		return false;
	}
	return true;
}

//==============================================================================

ARItemList::ARItemList(ARArrangeItem *p)
{
	ItemID		=p->GetID();
	CreatedTime	=p->GetIndex()->GetCreatedTime();
	Result		=p->GetARResult();
	p->GetArea().GetCenter(Position);
}

bool	ARItemList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CreatedTime)==false)
		return false;
	BYTE	d=(BYTE)Result;
	if(::Save(f,d)==false)
		return false;
	if(Position.Save(f)==false)
		return false;
	return true;
}
bool	ARItemList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CreatedTime)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Result=(ARArrangeItem::ARResult)d;
	if(Position.Load(f)==false)
		return false;
	return true;
}
ARItemList	&ARItemList::operator=(ARItemList &src)
{
	ItemID		=src.ItemID;
	CreatedTime	=src.CreatedTime;
	Result		=src.Result;
	Position	=src.Position;
	return *this;
}


bool	ARItemListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ARItemList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	ARItemListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ARItemList *a=new ARItemList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

ARItemListContainer	&ARItemListContainer::operator+=(ARItemListContainer &src)
{
	for(ARItemList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ARItemList *b=new ARItemList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}



GUICmdReqARArrangeList::GUICmdReqARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqARArrangeList::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false)
		return false;
	return true;
}
bool	GUICmdReqARArrangeList::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false)
		return false;
	return true;
}

void	GUICmdReqARArrangeList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendARArrangeList	*SendBack=GetSendBack(GUICmdSendARArrangeList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ARArrange");
	if(AlignBase!=NULL){
		ARArrangeInPage	*PData=dynamic_cast<ARArrangeInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			for(AlgorithmItemPI	*a=PData->GetFirstData();a!=NULL;a=a->GetNext()){
				ARArrangeItem	*p=dynamic_cast<ARArrangeItem *>(a);
				if(p!=NULL){
					if(p->GetIndex()!=NULL){
						if(p->GetIndex()->GetCreatedTime()==CreatedTime){
							SendBack->ItemContainer.AppendList(new ARItemList(p));
						}
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendARArrangeList::GUICmdSendARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendARArrangeList::Load(QIODevice *f)
{
	if(ItemContainer.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdSendARArrangeList::Save(QIODevice *f)
{
	if(ItemContainer.Save(f)==false)
		return false;
	return true;
}

//==============================================================================

GUICmdReqAddARArrange::GUICmdReqAddARArrange(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAddARArrange::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,CreatedTime)==false)
		return false;
	return true;
}
bool	GUICmdReqAddARArrange::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,CreatedTime)==false)
		return false;
	return true;
}

void	GUICmdReqAddARArrange::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ARArrange");
	if(AlignBase!=NULL){
		ARArrangeInPage	*PData=dynamic_cast<ARArrangeInPage	*>(AlignBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdReqAddARArrange	Cmd(this);
			Cmd.Area=Area;
			Cmd.CreatedTime=CreatedTime;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

//==============================================================================

GUICmdReqLearningThumnail::GUICmdReqLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ImageWidth	=0;
	ImageHeight	=0;
}

bool	GUICmdReqLearningThumnail::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false)
		return false;
	if(::Load(f,ImageWidth)==false)
		return false;
	if(::Load(f,ImageHeight)==false)
		return false;
	return true;
}

bool	GUICmdReqLearningThumnail::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false)
		return false;
	if(::Save(f,ImageWidth)==false)
		return false;
	if(::Save(f,ImageHeight)==false)
		return false;
	return true;
}

void	GUICmdReqLearningThumnail::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendLearningThumnail	*SendBack=GetSendBack(GUICmdSendLearningThumnail,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Img=new QImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	LearningImage	*d=GetLayersBase()->GetPageData(localPage)->Find(CreatedTime);
	if(d!=NULL){
		d->DrawThumnailImage(*SendBack->Img,ImageWidth,ImageHeight);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendLearningThumnail::GUICmdSendLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Img=NULL;
}
GUICmdSendLearningThumnail::~GUICmdSendLearningThumnail(void)
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=NULL;
}

bool	GUICmdSendLearningThumnail::Load(QIODevice *f)
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=new QImage();
	if(::Load(f,*Img)==false)
		return false;
	return true;
}
	
bool	GUICmdSendLearningThumnail::Save(QIODevice *f)
{
	if(::Save(f,*Img)==false)
		return false;
	return true;
}
