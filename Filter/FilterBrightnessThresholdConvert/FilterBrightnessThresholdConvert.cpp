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



#include "FilterBrightnessThresholdConvert.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "XPointer.h"

DEFFUNCEX	bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="BrightnessThresholdConvert";
	return(true);
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Convert brightness with threshold";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterBrightnessThresholdConvert(base);
}

DEFFUNCEX	bool		DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

DEFFUNCEX	bool		DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
DEFFUNCEX	bool		DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterBrightnessThresholdConvert	*v=(FilterBrightnessThresholdConvert *)handle;
	SettingDialog	D(v->ThresholdBrightness ,v->ThresholdWidth ,handle->GetLayersBase(),parent);
	D.exec();
	v->ThresholdBrightness	=D.ThresholdBrightness;
	v->ThresholdWidth		=D.ThresholdWidth;
	return true;
}
DEFFUNCEX	bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterBrightnessThresholdConvert::FilterBrightnessThresholdConvert(LayersBase *base)
	:FilterClassBase(base)
{	
	ThresholdBrightness	=128;
	ThresholdWidth		=10.0;
}
FilterBrightnessThresholdConvert::~FilterBrightnessThresholdConvert(void)
{
}

bool	FilterBrightnessThresholdConvert::Save(QIODevice *f)
{
	if(::Save(f,ThresholdBrightness)==false)
		return false;
	if(::Save(f,ThresholdWidth)==false)
		return false;
	return true;
}
bool	FilterBrightnessThresholdConvert::Load(QIODevice *f)
{
	if(::Load(f,ThresholdBrightness)==false)
		return false;
	if(::Load(f,ThresholdWidth)==false)
		return false;
	return true;
}
bool	FilterBrightnessThresholdConvert::Initial(void)
{
	if(ThresholdWidth<=0.0)
		ThresholdWidth=0.1;
	for(int r=0;r<256;r++){
		int	y=256/(1+exp((double)(ThresholdBrightness-r)/ThresholdWidth));
		TransTable[r]=y;
	}

	return true;
}
bool	FilterBrightnessThresholdConvert::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return true;
}

bool	FilterBrightnessThresholdConvert::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterBrightnessThresholdConvert::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	YLen=GetMaxLines();
	int	XLen=GetDotPerLine();

	for(int L=0;L<BufferDimCounts;L++){
		ImageBuffer *B=Buff[L];
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<YLen;y++){
				BYTE	*d=B->GetY(y);
				for(int x=0;x<XLen;x++){
					d[x]=TransTable[d[x]];
				}
			}
		}
	}	

	return true;
}
