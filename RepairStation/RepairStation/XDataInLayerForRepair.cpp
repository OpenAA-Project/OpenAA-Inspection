/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XDataInLayerForRepair.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
