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



#include "FilterBrightnessLogConvert.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "FilterSettingDialog.h"
#include "XPointer.h"

DEFFUNCEX	bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="BrightnessLogConvert";
	return(true);
}

DEFFUNCEX	WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Convert brightness logarithmically";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterBrightnessLogConvert(base);
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
	FilterBrightnessLogConvert	*v=(FilterBrightnessLogConvert *)handle;
	FilterSettingDialog	D(v->Position ,v->Strength ,handle->GetLayersBase(),parent);
	D.exec();
	v->Position	=D.Position;
	v->Strength	=D.Strength;
	return true;
}
DEFFUNCEX	bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterBrightnessLogConvert::FilterBrightnessLogConvert(LayersBase *base)
	:FilterClassBase(base)
{	
	Position	=128;
	Strength	=10.0;
}
FilterBrightnessLogConvert::~FilterBrightnessLogConvert(void)
{
}

bool	FilterBrightnessLogConvert::Save(QIODevice *f)
{
	if(::Save(f,Position)==false)
		return false;
	if(::Save(f,Strength)==false)
		return false;
	return true;
}
bool	FilterBrightnessLogConvert::Load(QIODevice *f)
{
	if(::Load(f,Position)==false)
		return false;
	if(::Load(f,Strength)==false)
		return false;
	return true;
}
bool	FilterBrightnessLogConvert::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return true;
}

bool	FilterBrightnessLogConvert::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterBrightnessLogConvert::Initial(void)
{
	//a(x-b)^2+c=y
	//Peak(Xp,Yp)
	//b=Xp, c=Yp
	//a1*Xp*Xp+Yp=0		a1=-Yp/(Xp*Xp)
	//a2(Xm-Xp)^2+Yp=0

	double	Xp=Position;
	double	Yp=Strength*(256-Position)/100.0;
	double	a1=-Yp/(Xp*Xp);
	double	a2=-Yp/((256-Xp)*(256-Xp));

	for(int x=0;x<Position;x++){
		double	d=a1*(x-Xp)*(x-Xp)+Yp;
		int	D=d+x;
		if(D<0)
			D=0;
		if(D>255)
			D=255;
		TransTable[x]=D;
	}
	for(int x=Position;x<256;x++){
		double	d=a2*(x-Xp)*(x-Xp)+Yp;
		int	D=d+x;
		if(D<0)
			D=0;
		if(D>255)
			D=255;
		TransTable[x]=D;
	}		

	return true;
}

bool	FilterBrightnessLogConvert::Execute(ImageBuffer *Buff[],int BufferDimCounts)
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
