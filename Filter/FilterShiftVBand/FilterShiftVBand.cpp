/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterShiftVBand\FilterShiftVBand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterShiftVBand.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingShiftVBandDialog.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ShiftVBand";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shift VBand";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterShiftVBand(base);
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
	FilterShiftVBand	*H=(FilterShiftVBand *)handle;
	SettingShiftVBandDialog	D(handle->GetLayersBase(),H->VBands,parent);
	if(D.exec()==(int)true){
		H->VBands	=D.VBands;
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
VBandInfo::VBandInfo(const VBandInfo &src)
{
	XPos	=src.XPos;
	ShiftY	=src.ShiftY;
}
bool	VBandInfo::Save(QIODevice *f)
{
	if(::Save(f,XPos)==false)	return false;
	if(::Save(f,ShiftY)==false)	return false;
	return true;
}
bool	VBandInfo::Load(QIODevice *f)
{
	if(::Load(f,XPos)==false)	return false;
	if(::Load(f,ShiftY)==false)	return false;
	return true;
}

int	VBandInfo::Compare(VBandInfo &src)
{
	return XPos-src.XPos;
}
	
VBandInfoContainer::VBandInfoContainer(const VBandInfoContainer &src)
{
	for(VBandInfo *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		VBandInfo	*b=new VBandInfo(*a);
		AppendList(b);
	}
}

VBandInfo	*VBandInfoContainer::Create(void)
{
	return new VBandInfo();
}

//================================================================================================
FilterShiftVBand::FilterShiftVBand(LayersBase *base)
:FilterClassBase(base)
{	
}

bool	FilterShiftVBand::Save(QIODevice *f)
{
	if(VBands.Save(f)==false)
		return false;
	return true;
}
bool	FilterShiftVBand::Load(QIODevice *f)
{
	if(VBands.Load(f)==false)
		return false;

	Initial();
	return true;
}

bool	FilterShiftVBand::Initial(void)
{
	return true;
}

bool	FilterShiftVBand::Release(void)
{
	return true;
}

bool	FilterShiftVBand::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	VBands.Sort();

	for(int i=0;i<BufferDimCounts;i++){
		int	LeftX=0;
		int	RightX=0;
		int	AddedShiftY=0;
		for(VBandInfo *a=VBands.GetFirst();a!=NULL;a=a->GetNext()){
			RightX=a->XPos;
			ExeShiftY(Buff[i],LeftX,RightX,-AddedShiftY);
			LeftX=RightX;
			AddedShiftY+=a->ShiftY;
		}
		if(RightX<GetDotPerLine()){
			RightX=GetDotPerLine();
			ExeShiftY(Buff[i],LeftX,RightX,-AddedShiftY);
		}
	}
	return true;
}

void	FilterShiftVBand::ExeShiftY(ImageBuffer *Buff,int LeftX,int RightX,int AddedShiftY)
{
	if(LeftX<0)
		LeftX=0;
	if(RightX>GetDotPerLine())
		RightX=GetDotPerLine();
	int	XLen=RightX-LeftX;
	if(XLen>0){
		if(AddedShiftY<0){
			int	SrcY=-AddedShiftY;
			int	DstY=0;
			int	YLen=GetMaxLines()+AddedShiftY;
			for(int i=0;i<YLen;i++){
				BYTE	*s=Buff->GetY(SrcY);
				BYTE	*d=Buff->GetY(DstY);
				memcpy(&d[LeftX],&s[LeftX],XLen);
				SrcY++;
				DstY++;
			}
		}
		else if(AddedShiftY>0){
			int	SrcY=GetMaxLines()-1;
			int	DstY=GetMaxLines()-AddedShiftY-1;
			int	YLen=GetMaxLines()-AddedShiftY;
			for(int i=0;i<YLen;i++){
				BYTE	*s=Buff->GetY(SrcY);
				BYTE	*d=Buff->GetY(DstY);
				memcpy(&d[LeftX],&s[LeftX],XLen);
				SrcY--;
				DstY--;
			}
		}
	}
}
