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



#include "FilterConvertResolution.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingResolutionDialog.h"
#include "XPointer.h"

bool		DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="ConvertResolution";
	return(true);
}

WORD		DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Convert Resolution";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterConvertResolution(base);
}

bool		DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool		DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool		DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterConvertResolution	*v=(FilterConvertResolution *)handle;
	SettingResolutionDialog	D(v->XZoom ,v->YZoom,v->Cx,v->Cy
								,handle->GetLayersBase()
								,parent);
	D.exec();
	v->XZoom	=D.XZoom;
	v->YZoom	=D.YZoom;
	v->Cx		=D.Cx;
	v->Cy		=D.Cy;
	return true;
}
bool		DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterConvertResolution::FilterConvertResolution(LayersBase *base)
	:FilterClassBase(base)
{	
	XZoom	=1.0;
	YZoom	=1.0;
	Cx		=0;
	Cy		=0;
}
FilterConvertResolution::~FilterConvertResolution(void)
{
}

bool	FilterConvertResolution::Save(QIODevice *f)
{
	if(::Save(f,XZoom)==false)
		return false;
	if(::Save(f,YZoom)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}
bool	FilterConvertResolution::Load(QIODevice *f)
{
	if(::Load(f,XZoom)==false)
		return false;
	if(::Load(f,YZoom)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}
bool	FilterConvertResolution::Initial(void)
{
	TmpImage.Set(0,0,GetDotPerLine(),GetMaxLines());
	return true;
}
bool	FilterConvertResolution::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	TmpImage.Set(0,0,NewDotPerLine,NewMaxLines);
	return true;
}

bool	FilterConvertResolution::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterConvertResolution::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	YLen=GetMaxLines();
	int	XLen=GetDotPerLine();
	double	Zx=1.0/XZoom;
	double	Zy=1.0/YZoom;
	for(int L=0;L<BufferDimCounts;L++){
		TmpImage=*Buff[L];
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<YLen;y++){
				BYTE	*d=Buff[L]->GetY(y);
				int	Y=(y-Cy)*Zy;
				if(0<=Y && Y<YLen){
					BYTE	*s=TmpImage[Y];
					for(int x=0;x<XLen;x++){
						int	X=(x-Cx)*Zx;
						if(0<=X && X<XLen){
							d[x]=s[X];
						}
						else{
							d[x]=0;
						}
					}
				}
				else{
					for(int x=0;x<XLen;x++){
						d[x]=0;
					}
				}
			}
		}
	}	

	return true;
}
