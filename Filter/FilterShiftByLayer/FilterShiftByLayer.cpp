/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterShiftByLayer\FilterShiftByLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "FilterShiftByLayer.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ShiftByLayer";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shift image by Layer";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterShiftByLayer(base);
}

bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{

	SettingDialog	D(handle->GetLayersBase()
					, ((FilterShiftByLayer *)handle)->ShiftInfo);
	if(D.exec()==(int)true){
		((FilterShiftByLayer *)handle)->ShiftInfo	=D.ShiftInfo;
	}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
ShiftXYList::ShiftXYList(void)
{
	Layer	=-1;
	ShiftX	=0;
	ShiftY	=0;
}
ShiftXYList::ShiftXYList(const ShiftXYList &src)
{
	Layer	=src.Layer;
	ShiftX	=src.ShiftX;
	ShiftY	=src.ShiftY;
}

ShiftXYList	&ShiftXYList::operator=(const ShiftXYList &src)
{
	Layer	=src.Layer;
	ShiftX	=src.ShiftX;
	ShiftY	=src.ShiftY;
	return *this;
}
bool	ShiftXYList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)	return false;
	if(::Save(f,ShiftX)==false)	return false;
	if(::Save(f,ShiftY)==false)	return false;
	return true;
}
bool	ShiftXYList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)	return false;
	if(::Load(f,ShiftX)==false)	return false;
	if(::Load(f,ShiftY)==false)	return false;
	return true;
}

ShiftXYInPageContainer::ShiftXYInPageContainer(void)
{
	Page=-1;
}
ShiftXYInPageContainer::ShiftXYInPageContainer(const ShiftXYInPageContainer &src)
{
	Page=src.Page;
	for(ShiftXYList *s=src.NPListPackSaveLoad<ShiftXYList>::GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYList *d=new ShiftXYList(*s);
		AppendList(d);
	}
}

ShiftXYList	*ShiftXYInPageContainer::Create(void)
{
	return new ShiftXYList();
}
ShiftXYInPageContainer	&ShiftXYInPageContainer::operator=(const ShiftXYInPageContainer &src)
{
	Page=src.Page;
	for(ShiftXYList *s=src.NPListPackSaveLoad<ShiftXYList>::GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYList *d=new ShiftXYList(*s);
		AppendList(d);
	}
	return *this;
}

ShiftXYList	*ShiftXYInPageContainer::Find(int layer)
{
	for(ShiftXYList *s=NPListPackSaveLoad<ShiftXYList>::GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Layer==layer){
			return s;
		}
	}
	return NULL;
}

bool	ShiftXYInPageContainer::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)	return false;
	if(NPListPackSaveLoad<ShiftXYList>::Save(f)==false)
		return false;
	return true;
}
bool	ShiftXYInPageContainer::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)	return false;
	if(NPListPackSaveLoad<ShiftXYList>::Load(f)==false)
		return false;
	return true;
}

ShiftXYInPhaseContainer::ShiftXYInPhaseContainer(void)
{
	Phase=-1;
}
ShiftXYInPhaseContainer::ShiftXYInPhaseContainer(const ShiftXYInPhaseContainer &src)
{
	Phase=src.Phase;
	for(ShiftXYInPageContainer *s=src.NPListPackSaveLoad<ShiftXYInPageContainer>::GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYInPageContainer *d=new ShiftXYInPageContainer(*s);
		AppendList(d);
	}
}

ShiftXYInPageContainer	*ShiftXYInPhaseContainer::Create(void)
{
	return new ShiftXYInPageContainer();
}
ShiftXYInPhaseContainer	&ShiftXYInPhaseContainer::operator=(const ShiftXYInPhaseContainer &src)
{
	Phase=src.Phase;
	for(ShiftXYInPageContainer *s=src.NPListPackSaveLoad<ShiftXYInPageContainer>::GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYInPageContainer *d=new ShiftXYInPageContainer(*s);
		AppendList(d);
	}
	return *this;
}

ShiftXYInPageContainer	*ShiftXYInPhaseContainer::Find(int page)
{
	for(ShiftXYInPageContainer *s=NPListPackSaveLoad<ShiftXYInPageContainer>::GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Page==page){
			return s;
		}
	}
	return NULL;
}

bool	ShiftXYInPhaseContainer::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(NPListPackSaveLoad<ShiftXYInPageContainer>::Save(f)==false)
		return false;
	return true;
}
bool	ShiftXYInPhaseContainer::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(NPListPackSaveLoad<ShiftXYInPageContainer>::Load(f)==false)
		return false;
	return true;
}
ShiftXYInfo::ShiftXYInfo(void)
{
}
ShiftXYInfo::ShiftXYInfo(const ShiftXYInfo &src)
{
	for(ShiftXYInPhaseContainer *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYInPhaseContainer *d=new ShiftXYInPhaseContainer(*s);
		AppendList(d);
	}
}

ShiftXYInfo	&ShiftXYInfo::operator=(const ShiftXYInfo &src)
{
	for(ShiftXYInPhaseContainer *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ShiftXYInPhaseContainer *d=new ShiftXYInPhaseContainer(*s);
		AppendList(d);
	}
	return *this;
}
ShiftXYInPhaseContainer	*ShiftXYInfo::Find(int phase)
{
	for(ShiftXYInPhaseContainer *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Phase==phase){
			return s;
		}
	}
	return NULL;
}
ShiftXYInPhaseContainer	*ShiftXYInfo::Create(void)
{
	return new ShiftXYInPhaseContainer();
}

//================================================================================================
FilterShiftByLayer::FilterShiftByLayer(LayersBase *base)
:FilterClassBase(base)
{	
}

bool	FilterShiftByLayer::Save(QIODevice *f)
{
	if(ShiftInfo.Save(f)==false)
		return false;
	return true;
}
bool	FilterShiftByLayer::Load(QIODevice *f)
{
	if(ShiftInfo.Load(f)==false)
		return false;
	return true;
}

bool	FilterShiftByLayer::Initial(void)
{
	return true;
}

bool	FilterShiftByLayer::Release(void)
{
	return true;
}

bool	FilterShiftByLayer::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	ShiftXYInPhaseContainer	*XYPhase=ShiftInfo.Find(GetPhaseCode());
	if(XYPhase!=NULL){
		ShiftXYInPageContainer	*XYPage=XYPhase->Find(GetPage());
		if(XYPage!=NULL){
			for(int layer=0;layer<BufferDimCounts;layer++){
				ShiftXYList	*XY=XYPage->Find(layer);
				if(XY!=NULL){
					ExecuteShift(Buff[layer],XY->ShiftX,XY->ShiftY);
				}
			}
		}
	}
	return true;
}

void	FilterShiftByLayer::ExecuteShift(ImageBuffer *Buff,int ShiftX,int ShiftY)
{
	Buff->MoveImage(ShiftX,ShiftY);
}

void	FilterShiftByLayer::TransmitDirectly(GUIDirectMessage *packet)
{
}
