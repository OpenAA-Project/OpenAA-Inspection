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


//---------------------------------------------------------------------------

#include "XDataInLayerForRepair.h"
#include "XMainSchemeMemoryForRepair.h"
#include "XFilterManager.h"

DataInLayerForRepair::DataInLayerForRepair(EntryPointBase	*pEntryPoint ,DataInPage *parent)
:DataInLayer(pEntryPoint ,parent)
{
}

DataInLayerForRepair::~DataInLayerForRepair(void)
{
}

void	DataInLayerForRepair::Initial(void)
{
	MasterBuff=new ImageBufferForRepair();
//	TargetBuff=new ImageBufferForRepair();

	((ImageBufferForRepair *)MasterBuff)->SetResolution(GetResolution());
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true)
			MasterBuff->Set(GetPage(),ImageBufferMaster ,GetDotPerLine()>>GetResolution() ,GetMaxLines()>>GetResolution());
	}
}

//---------------------------------------------------------------------------
DataInPageForRepair::DataInPageForRepair(int page,PageDataInOnePhase	*parent)
	:DataInPage(page,parent)
{
}

DataInPageForRepair::~DataInPageForRepair(void)
{
}

void    DataInPageForRepair::Initial(void)
{
	if(LayerData!=NULL)
		delete	[]LayerData;
	AllocatedLayerNumb	=GetLayerNumb();
	LayerData			=new DataInLayer*[GetLayerNumb()];
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]=new DataInLayerForRepair(EntryPoint,this);
		LayerData[Ly]->Layer		=Ly;
		((DataInLayerForRepair *)LayerData[Ly])->SetResolution(GetResolution());
		LayerData[Ly]->Initial();
	}
}

//---------------------------------------------------------------------------
PageDataInOnePhaseForRepair::PageDataInOnePhaseForRepair(void)
	:PageDataInOnePhase(-1, NULL)
{
}

PageDataInOnePhaseForRepair::~PageDataInOnePhaseForRepair(void)
{
}

void	PageDataInOnePhaseForRepair::InitialCreate(LayersBase *Base ,bool EnabledImageMemoryAllocation)
{
	if(GetFilterContainer()!=NULL){
		delete	GetFilterContainer();
	}
	SetFilterContainer(new FilterInstanceContainer(Base));

	if(GetPageData()!=NULL){
	    for(int i=0;i<GetAllocatedPageNumb();i++){
		    GetPageData(i)->Release();
			delete	GetPageData(i);
	        }
		delete	[]GetPageData();
		SetPageData(NULL);
	}
	SetAllocatedPageNumb(Base->GetPageNumb());
	SetPageData(new DataInPage*[GetAllocatedPageNumb()]);
	for(int i=0;i<GetAllocatedPageNumb();i++){
		SetPageData(i,new DataInPageForRepair(i,this));
		//PageData[i]->Parent=this;
		((DataInPageForRepair *)GetPageData(i))->SetResolution(GetResolution());
		GetPageData(i)->Initial(EnabledImageMemoryAllocation);
		GetPageData(i)->Page=i;
	}
}

//---------------------------------------------------------------------------
LayersBaseForRepair::LayersBaseForRepair(void)
{
}

LayersBaseForRepair::~LayersBaseForRepair(void)
{
}

void	LayersBaseForRepair::InitialCreatePages(EntryPointBase *pEntryPoint)
{
	SetEntryPoint(pEntryPoint);
	if(GetPhaseData()!=NULL){
		for(int i=0;i<GetAllocatedPhaseNumb();i++){
			delete	GetPageDataPhase(i);
		}
		delete	[]GetPhaseData();
	}
	SetAllocatedPhaseNumb(GetPhaseNumb());
	if(GetAllocatedPhaseNumb()==0){
		SetAllocatedPhaseNumb(1);
	}
	SetPhaseData(new PageDataInOnePhase*[GetAllocatedPhaseNumb()]);
	for(int i=0;i<GetAllocatedPhaseNumb();i++){
		SetPhaseData(i,new PageDataInOnePhaseForRepair());
		((PageDataInOnePhaseForRepair *)GetPageDataPhase(i))->SetResolution(GetResolution());
		GetPageDataPhase(i)->InitialCreate(this);
	}

	if(GetDrawPageIndex()!=NULL){
		delete	[]GetDrawPageIndex();
		SetDrawPageIndex(NULL);
	}
	SetPageData(GetPageDataPhase(0));
	SetDrawPageIndex(new DataInPage*[GetPageNumb()]);
	SetAllocatedPageNumb(GetPageNumb());
	for(int i=0;i<GetAllocatedPageNumb();i++){
		SetDrawPageIndex(i,GetCurrentPageDataPhase()->GetPageData()[i]);
	}
/*
	GetOutlineOffsetWriter()->Initial(AllocatedPageNumb);

	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;

	if((pEntryPoint!=NULL) && (pEntryPoint->IsMasterPC()==true)){
		GlobalPageNumb=GetPageNumb();
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
	}
*/
}