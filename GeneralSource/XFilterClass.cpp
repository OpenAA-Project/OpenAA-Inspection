/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFilterClass.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XFilterClass.h"
#include "XFilterManager.h"
#include "XDataInLayer.h"
#include "XFilterInstance.h"

void	FilterClassBase::SetPaernt(FilterInstanceList *p)
{
	Holder=p;
}
int		FilterClassBase::GetDLLVersion(void)	const
{
	if(Holder!=NULL){
		return Holder->GetDLLVersion();
	}
	return 0;
}

int		FilterClassBase::GetPage(void)	const
{
	if(Holder!=NULL){
		return Holder->GetPage();
	}
	return -1;
}

int		FilterClassBase::GetPhaseCode(void)	const
{
	if(Holder!=NULL){
		return Holder->GetPhaseCode();
	}
	return -1;
}

bool	FilterClassBase::Save(QIODevice *f)
{
	return true;
}
bool	FilterClassBase::Load(QIODevice *f)
{
	return true;
}

int		FilterClassBase::GetDotPerLine(void)	const
{
	if(Holder==NULL || Holder->Parent==NULL){
		return 0;
	}
	return GetLayersBase()->GetDotPerLine(Holder->Parent->Page);
}

DataInPage *FilterClassBase::GetPageData(void)	const
{
	int	PhaseCode=GetPhaseCode();
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(PhaseCode);
	if(Ph!=NULL){
		return Ph->GetPageData(GetPage());
	}
	return NULL;
}

int		FilterClassBase::GetMaxLines(void)	const
{
	if(Holder==NULL || Holder->Parent==NULL){
		return 0;
	}
	return GetLayersBase()->GetMaxLines(Holder->Parent->Page);
}

bool	FilterClassBase::Initial(void)
{
	return true;
}
bool	FilterClassBase::Release(void)
{
	return true;
}
bool	FilterClassBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	
{
	Release();
	Initial();
	return true;
}
bool	FilterClassBase::Reallocate(int newLayerNumb)						
{
	Release();
	Initial();
	return true;
}
bool	FilterClassBase::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	return true;
}
