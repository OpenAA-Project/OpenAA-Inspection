/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaColorConverter\XAreaColorConverterItem.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

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

