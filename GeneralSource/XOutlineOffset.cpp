/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineOffset.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XOutlineOffset.h"
#include "XGeneralFunc.h"


OutlineOffsetInBlobPage::OutlineOffsetInBlobPage(void)
{
	OutlineOffsetInPageDimNumb	=0;
	OutlineOffsetInPageDim		=NULL;
}
OutlineOffsetInBlobPage::~OutlineOffsetInBlobPage(void)
{
	if(OutlineOffsetInPageDim!=NULL)
		delete	[]OutlineOffsetInPageDim;
	OutlineOffsetInPageDim		=NULL;
	OutlineOffsetInPageDimNumb	=0;
}

void	OutlineOffsetInBlobPage::Initial(int PageCount)
{
	OutlineOffsetInPageDimNumb=PageCount;
	if(OutlineOffsetInPageDim!=NULL)
		delete	[]OutlineOffsetInPageDim;
	OutlineOffsetInPageDim=new OutlineOffsetInPage[OutlineOffsetInPageDimNumb];
	for(int i=0;i<OutlineOffsetInPageDimNumb;i++){
		OutlineOffsetInPageDim[i].Dx=0;
		OutlineOffsetInPageDim[i].Dy=0;
	}
}

void	OutlineOffsetInBlobPage::SetData(int page ,OutlineOffsetInPage &Data)
{
	if(OutlineOffsetInPageDimNumb>page){
		OutlineOffsetInPageDim[page]=Data;
	}
}
OutlineOffsetInPage	OutlineOffsetInBlobPage::GetData(int page)	const
{
	if(OutlineOffsetInPageDimNumb>page){
		return OutlineOffsetInPageDim[page];
	}
	OutlineOffsetInPage	data;
	data.Dx=0;
	data.Dy=0;
	return data;
}
void	OutlineOffsetInBlobPage::Copy(const OutlineOffsetInBlobPage &src)
{
	for(int i=0;i<OutlineOffsetInPageDimNumb && i<src.OutlineOffsetInPageDimNumb;i++){
		OutlineOffsetInPageDim[i]=src.OutlineOffsetInPageDim[i];
	}
}
OutlineOffsetInBlobPage	&OutlineOffsetInBlobPage::operator=(const OutlineOffsetInBlobPage &src)
{
	if(this!=&src){
		if(OutlineOffsetInPageDim!=NULL)
			delete	[]OutlineOffsetInPageDim;
		OutlineOffsetInPageDimNumb=src.OutlineOffsetInPageDimNumb;
		OutlineOffsetInPageDim=new OutlineOffsetInPage[OutlineOffsetInPageDimNumb];
		Copy(src);
	}
	return *this;
}

bool	OutlineOffsetInBlobPage::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,OutlineOffsetInPageDimNumb)==false)
		return false;
	for(int i=0;i<OutlineOffsetInPageDimNumb;i++){
		if(::Save(f,OutlineOffsetInPageDim[i].Dx)==false)
			return false;
		if(::Save(f,OutlineOffsetInPageDim[i].Dy)==false)
			return false;
	}
	return true;
}
bool	OutlineOffsetInBlobPage::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	int32	iOutlineOffsetInPageDimNumb;
	if(::Load(f,iOutlineOffsetInPageDimNumb)==false)
		return false;
	if(OutlineOffsetInPageDim!=NULL){
		delete	[]OutlineOffsetInPageDim;
	}
	OutlineOffsetInPageDimNumb=iOutlineOffsetInPageDimNumb;
	OutlineOffsetInPageDim=new OutlineOffsetInPage[OutlineOffsetInPageDimNumb];

	for(int i=0;i<OutlineOffsetInPageDimNumb;i++){
		if(::Load(f,OutlineOffsetInPageDim[i].Dx)==false)
			return false;
		if(::Load(f,OutlineOffsetInPageDim[i].Dy)==false)
			return false;
	}

	return true;
}
//=================================================================================

OutlineOffsetInBlob::OutlineOffsetInBlob(LayersBase *base)
:ServiceForLayers(base)
{
	OutlineOffsetInPhaseDimNumb	=0;
	OutlineOffsetInPhaseDim		=NULL;
}
OutlineOffsetInBlob::~OutlineOffsetInBlob(void)
{
	if(OutlineOffsetInPhaseDim!=NULL)
		delete	[]OutlineOffsetInPhaseDim;
	OutlineOffsetInPhaseDim		=NULL;
	OutlineOffsetInPhaseDimNumb	=0;
}

void	OutlineOffsetInBlob::Initial(void)
{
	OutlineOffsetInPhaseDimNumb=GetPhaseNumb();
	if(OutlineOffsetInPhaseDim!=NULL)
		delete	[]OutlineOffsetInPhaseDim;
	OutlineOffsetInPhaseDim=new OutlineOffsetInBlobPage[OutlineOffsetInPhaseDimNumb];
	for(int i=0;i<OutlineOffsetInPhaseDimNumb;i++){
		OutlineOffsetInPhaseDim[i].Initial(GetPageNumb());
	}
}

void	OutlineOffsetInBlob::Reallocate(void)
{
	int	iOutlineOffsetInPhaseDimNumb=GetPhaseNumb();
	OutlineOffsetInBlobPage		*iOutlineOffsetInPhaseDim=new OutlineOffsetInBlobPage[iOutlineOffsetInPhaseDimNumb];
	for(int i=0;i<iOutlineOffsetInPhaseDimNumb;i++){
		iOutlineOffsetInPhaseDim[i].Initial(GetPageNumb());
	}
	for(int i=0;i<iOutlineOffsetInPhaseDimNumb && i<OutlineOffsetInPhaseDimNumb;i++){
		iOutlineOffsetInPhaseDim[i].Copy(OutlineOffsetInPhaseDim[i]);
	}
	delete	[]OutlineOffsetInPhaseDim;
	OutlineOffsetInPhaseDim=iOutlineOffsetInPhaseDim;
	OutlineOffsetInPhaseDimNumb=iOutlineOffsetInPhaseDimNumb;
}

void	OutlineOffsetInBlob::SetData(int phase ,int page ,OutlineOffsetInPage &Data)
{
	if(OutlineOffsetInPhaseDimNumb>phase){
		OutlineOffsetInPhaseDim[phase].SetData(page ,Data);
	}
}
OutlineOffsetInPage	OutlineOffsetInBlob::GetData(int phase,int page)	const
{
	if(OutlineOffsetInPhaseDimNumb>phase){
		return OutlineOffsetInPhaseDim[phase].GetData(page);
	}
	OutlineOffsetInPage	data;
	data.Dx=0;
	data.Dy=0;
	return data;
}
int		OutlineOffsetInBlob::GetPageCount(int phase)	const
{
	if(OutlineOffsetInPhaseDimNumb<=phase)
		return 0;
	return OutlineOffsetInPhaseDim[phase].GetPageCount();
}
bool	OutlineOffsetInBlob::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,OutlineOffsetInPhaseDimNumb)==false)
		return false;
	for(int i=0;i<OutlineOffsetInPhaseDimNumb;i++){
		if(OutlineOffsetInPhaseDim[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	OutlineOffsetInBlob::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(Ver==1){
		f->seek(0);
		if(OutlineOffsetInPhaseDim!=NULL)
			if(OutlineOffsetInPhaseDim[0].Load(f)==false){
				return false;
			}
	}

	int32	iOutlineOffsetInPhaseDimNumb;
	if(::Load(f,iOutlineOffsetInPhaseDimNumb)==false)
		return false;
	if(OutlineOffsetInPhaseDim!=NULL){
		delete	[]OutlineOffsetInPhaseDim;
	}
	OutlineOffsetInPhaseDimNumb=iOutlineOffsetInPhaseDimNumb;
	OutlineOffsetInPhaseDim=new OutlineOffsetInBlobPage[OutlineOffsetInPhaseDimNumb];
	for(int i=0;i<OutlineOffsetInPhaseDimNumb;i++){
		if(OutlineOffsetInPhaseDim[i].Load(f)==false){
			return false;
		}
	}

	return true;
}