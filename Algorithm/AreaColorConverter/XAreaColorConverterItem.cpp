/*
 * Copyright (C) 2023
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


#include "XAreaColorConverter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaColorConverterPacket.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


AreaColorConverterThreshold::AreaColorConverterThreshold(AreaColorConverterItem *parent)
	:AlgorithmThreshold(parent)
{
}

void	AreaColorConverterThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	AreaColorConverterThreshold::IsEqual(const AlgorithmThreshold &src)	const
{	
	return true;
}
bool	AreaColorConverterThreshold::Save(QIODevice *f)
{
	return true;
}
bool	AreaColorConverterThreshold::Load(QIODevice *f)
{
	return true;
}

int		AreaColorConverterThreshold::GetSize(void)	const
{	
	return sizeof(this);
}

//===========================================================================

void	AreaColorConverterItem::CopyThreshold(AreaColorConverterItem &src)
{
	GetThresholdBaseWritable()->CopyFrom(*src.GetThresholdBaseWritable());
}

void	AreaColorConverterItem::CopyThresholdOnly(AreaColorConverterItem &src)
{
	GetThresholdBaseWritable()->CopyFrom(*src.GetThresholdBaseWritable());
}

void	AreaColorConverterItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((AreaColorConverterItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AreaColorConverterItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((AreaColorConverterItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((AreaColorConverterItem *)Data)->GetLibID()){
			AreaColorConverterInPage	*Pg=dynamic_cast<AreaColorConverterInPage *>(GetParentInPage());
			UndoElement<AreaColorConverterInPage>	*UPointer=new UndoElement<AreaColorConverterInPage>(Pg,&AreaColorConverterInPage::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AreaColorConverterItem *src=(AreaColorConverterItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

ExeResult	AreaColorConverterItem::ExecuteCaptured	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	return _ER_true;
}
