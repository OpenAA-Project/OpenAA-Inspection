/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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