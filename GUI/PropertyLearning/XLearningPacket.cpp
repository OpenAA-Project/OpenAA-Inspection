#include "AddFileDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\XLearningPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XLearningPacket.h"
#include "XGeneralFunc.h"
#include "XLearning.h"

GUICmdLearningAddFile::GUICmdLearningAddFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLearningAddFile::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Index)==false)
		return false;
	return true;
}
bool	GUICmdLearningAddFile::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Index)==false)
		return false;
	return true;
}

void	GUICmdLearningAddFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningAddFilePacket	Cmd(this);
	Cmd.FileName=FileName;
	Cmd.Index=Index;
	PData->TransmitDirectly(&Cmd);
}

GUICmdLearningDelFile::GUICmdLearningDelFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdLearningDelFile::Load(QIODevice *f)
{
	if(::Load(f,IndexNumber)==false)
		return false;
	return true;
}

bool	GUICmdLearningDelFile::Save(QIODevice *f)
{
	if(::Save(f,IndexNumber)==false)
		return false;
	return true;
}

void	GUICmdLearningDelFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningDelFilePacket	Cmd(this);
	Cmd.IndexNumber=IndexNumber;
	PData->TransmitDirectly(&Cmd);
}

//==========================================================================================================
GUICmdReqStoredFileList::GUICmdReqStoredFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqStoredFileList::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	if(::Load(f,LotAutoCount)==false)
		return false;
	return true;
}
bool	GUICmdReqStoredFileList::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,LotAutoCount)==false)
		return false;
	return true;
}


void	GUICmdReqStoredFileList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckStoredFileList	*SendBack=GetSendBack(GUICmdAckStoredFileList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	LearningReqStoredFileList	Cmd(this);
	Cmd.List=&SendBack->List;
	Cmd.MasterCode	=MasterCode;
	Cmd.LotAutoCount=LotAutoCount;

	PData->TransmitDirectly(&Cmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckStoredFileList::GUICmdAckStoredFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckStoredFileList::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckStoredFileList::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckStoredFileList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//------------------------------------------------------------------------------------------------

GUICmdReqPickedFileList::GUICmdReqPickedFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqPickedFileList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPickedFileList	*SendBack=GetSendBack(GUICmdAckPickedFileList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	LearningReqPickedFileList	Cmd(this);
	Cmd.List=&SendBack->List;
	Cmd.LocalPage	=localPage;

	L->TransmitDirectly(&Cmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPickedFileList::GUICmdAckPickedFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckPickedFileList::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckPickedFileList::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckPickedFileList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//------------------------------------------------------------------------------------------------

GUICmdChangeLearningList::GUICmdChangeLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	SelectedListNumber=0;
}

bool	GUICmdChangeLearningList::Load(QIODevice *f)
{
	if(::Load(f,SelectedListNumber)==false)
		return false;
	return true;
}
bool	GUICmdChangeLearningList::Save(QIODevice *f)
{
	if(::Save(f,SelectedListNumber)==false)
		return false;
	return true;
}

void	GUICmdChangeLearningList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	LearningChangeSelectedNumber	Cmd(this);
	Cmd.SelectedNumber=SelectedListNumber;
	Cmd.Page=localPage;
	L->TransmitDirectly(&Cmd);
}

//------------------------------------------------------------------------------------------------

GUICmdAddLearningArea::GUICmdAddLearningArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ok=true;			//true:‹••ñ”rœ		false:‚m‚f”­•ñ
    NGLevel=0;	//0:Most important NG 1,2,3...lighter
}

bool	GUICmdAddLearningArea::Load(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,NGLevel)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddLearningArea::Save(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,NGLevel)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}

void	GUICmdAddLearningArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AddLearningAreaWithAttr	RCmd(this);
	RCmd.Area=Area;
	RCmd.NGLevel=NGLevel;
	RCmd.Ok=Ok;

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	PData->TransmitDirectly(&RCmd);
}


GUICmdReqLearningAreaListContainer::GUICmdReqLearningAreaListContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


void	GUICmdReqLearningAreaListContainer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLearningAreaListContainer	*SendBack=GetSendBack(GUICmdAckLearningAreaListContainer,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;

	AlgoLearningAreaListContainer	RCmd(this);
	RCmd.List=&SendBack->List;
	PData->TransmitDirectly(&RCmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckLearningAreaListContainer::GUICmdAckLearningAreaListContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckLearningAreaListContainer::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckLearningAreaListContainer::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckLearningAreaListContainer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
