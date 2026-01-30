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


#include "XRWAlgorithm3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

RWAlgorithm3DInPage::RWAlgorithm3DInPage(RW3DBaseRoot *parent)
	:RW3DInPageRoot(parent)
{
}
RWAlgorithm3DInPage::~RWAlgorithm3DInPage(void)
{
}

void	RWAlgorithm3DInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddRWAlgorithm3DItemPacket	*AddBItem=dynamic_cast<CmdAddRWAlgorithm3DItemPacket *>(packet);
	if(AddBItem!=NULL){
		RWAlgorithm3DItem	*item=new RWAlgorithm3DItem(this);
		item->SetManualCreated(true);
		AppendItem(item);
		return;		
	}
	CmdModifyRWAlgorithm3DItemPacket	*ModItem=dynamic_cast<CmdModifyRWAlgorithm3DItemPacket *>(packet);
	if(ModItem!=NULL){
		RWAlgorithm3DItem	*item=(RWAlgorithm3DItem *)SearchIDItem(ModItem->ItemID);
	}
	CmdCreateWholeRWAlgorithm3D	*CmdCreateWholeRWAlgorithm3DVar=dynamic_cast<CmdCreateWholeRWAlgorithm3D *>(packet);
	if(CmdCreateWholeRWAlgorithm3DVar!=NULL){
		return;		
	}
	CmdReqWholeRWAlgorithm3D	*CmdReqWholeRWAlgorithm3DVar=dynamic_cast<CmdReqWholeRWAlgorithm3D *>(packet);
	if(CmdReqWholeRWAlgorithm3DVar!=NULL){
		CmdReqWholeRWAlgorithm3DVar->RepeatCount=0;
		for(RWAlgorithm3DItem *a=(RWAlgorithm3DItem *)GetFirstData();a!=NULL;a=(RWAlgorithm3DItem *)a->GetNext()){
			if(a->IsManualCreated()==false){
				break;
			}
		}
		return;
	}
}

QColor	RWAlgorithm3DInPage::GetSurfaceColor(const PointVector3D &Line)
{
	CrossInfo	ClosedInfo;
	ClosedInfo.CrossT=FLT_MAX;
	SurfaceBase	*S=NULL;
	for(RWAlgorithm3DItem *a=(RWAlgorithm3DItem *)GetFirstData();a!=NULL;a=(RWAlgorithm3DItem *)a->GetNext()){
		CrossCluster CrossSides;
		if(a->Items.GetCrossPoint(Line ,CrossSides)==true){
			for(CrossVolume *t=CrossSides.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->NearSide.CrossT>0){
					if(ClosedInfo.CrossT>t->NearSide.CrossT){
						ClosedInfo=t->NearSide;
						S=CrossSides.GetSurface();
						break;
					}
				}
			}
		}
	}
	if(ClosedInfo.CrossT!=FLT_MAX){
		return S->GetColor();
	}
	return Qt::black;
}

//===========================================================================================
RWAlgorithm3DBase::RWAlgorithm3DBase(RegulusWorld *Base)
:RW3DBaseRoot(Base)
{
	ColorNormal			=Qt::darkGreen;
	ColorSelected		=Qt::green;
	ColorActive			=Qt::red;
	Color0				=Qt::green;
	Color1				=Qt::yellow;
	Color2				=Qt::darkRed;
	Color3				=Qt::cyan;
	Color4				=Qt::magenta;
	Color5				=Qt::darkGreen;
	Color6				=Qt::darkYellow;
	Color7				=Qt::darkCyan;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&Color0			, /**/"Color"	,/**/"Color0"		,"Level Color 0");
	SetParam(&Color1			, /**/"Color"	,/**/"Color1"		,"Level Color 1");
	SetParam(&Color2			, /**/"Color"	,/**/"Color2"		,"Level Color 2");
	SetParam(&Color3			, /**/"Color"	,/**/"Color3"		,"Level Color 3");
	SetParam(&Color4			, /**/"Color"	,/**/"Color4"		,"Level Color 4");
	SetParam(&Color5			, /**/"Color"	,/**/"Color5"		,"Level Color 5");
	SetParam(&Color6			, /**/"Color"	,/**/"Color6"		,"Level Color 6");
	SetParam(&Color7			, /**/"Color"	,/**/"Color7"		,"Level Color 7");
}

AlgorithmDrawAttr	*RWAlgorithm3DBase::CreateDrawAttr(void)
{
	return new RWAlgorithm3DDrawAttr();
}

RW3DInPageRoot	*RWAlgorithm3DBase::CreateChild(void)
{	
	return(new RWAlgorithm3DInPage(this));
}
void	RWAlgorithm3DBase::TransmitDirectly(GUIDirectMessage *packet)
{

}