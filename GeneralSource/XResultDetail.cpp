/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\GeneralSource\XResultDetail.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XResultDetail.h"
#include "XGeneralFunc.h"

ResultDetailItem::ResultDetailItem(ResultDetailStocker *parent)
{
	Parent=parent;
	Color	=Qt::red;
	WaitMilisec	=0;
}

bool	ResultDetailItem::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmName)==false)
		return false;
	if(::Save(f,MatchingCode)==false)
		return false;
	if(::Save(f,DetailMessage)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	if(::Save(f,WaitMilisec)==false)
		return false;
	return true;
}

bool	ResultDetailItem::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmName)==false)
		return false;
	if(::Load(f,MatchingCode)==false)
		return false;
	if(::Load(f,DetailMessage)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	if(::Load(f,WaitMilisec)==false)
		return false;
	return true;
}

QString		ResultDetailItem::GetDetailMessage(void)
{
	int	LanguageCode=0;
	if(Parent!=NULL){
		LanguageCode=Parent->GetLanguageCode();
	}
	if(DetailMessage.count()<LanguageCode){
		return DetailMessage[LanguageCode];
	}
	else
		return /**/"";
}

//------------------------------------------------------------------

bool	ResultDetailStocker::Save(QIODevice *f)
{
	if(::Save(f,DataVersion)==false)
		return false;
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ResultDetailItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		if(item->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ResultDetailStocker::Load(QIODevice *f)
{
	int32	N=0;

	if(::Load(f,DataVersion)==false)
		return false;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ResultDetailItem	*item=new ResultDetailItem(this);
		if(item->Load(f)==false)
			return false;
		AppendList(item);
	}
	DataVersion=ResultDetailVersion;
	return true;
}

ResultDetailItem	*ResultDetailStocker::Search(const QString &AlgorithmName ,int matchingcode)
{
	for(ResultDetailItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		if(item->GetAlgorithmName()==AlgorithmName
		&& item->GetMatchingCode()==matchingcode){
			return item;
		}
	}
	return NULL;
}

void	ResultDetailStocker::EnumAlgorithm	(QStringList &AlgorithmNames)
{
	AlgorithmNames.clear();
	for(ResultDetailItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		bool	Found=false;
		for(int i=0;i<AlgorithmNames.count();i++){
			if(AlgorithmNames[i]==item->GetAlgorithmName())
				Found=true;
				break;
		}
		if(Found==false){
			AlgorithmNames.append(item->GetAlgorithmName());
		}
	}
}

void	ResultDetailStocker::EnumCodes		(const QString &AlgorithmName ,IntList &Codes)
{
	for(ResultDetailItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		if(item->GetAlgorithmName()==AlgorithmName){
			Codes.Add(item->GetMatchingCode());
		}
	}
}



