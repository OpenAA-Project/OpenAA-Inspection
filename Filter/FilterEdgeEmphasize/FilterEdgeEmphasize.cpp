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



#include "FilterEdgeEmphasize.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "XPointer.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="EdgeEmphasize";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Make Edge emphasis";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterEdgeEmphasize(base);
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
	FilterEdgeEmphasize	*v=(FilterEdgeEmphasize *)handle;
	SettingDialog	D(handle->GetLayersBase(),v,parent);
	D.exec();
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterEdgeEmphasize::FilterEdgeEmphasize(LayersBase *base)
	:FilterClassBase(base)
{	
	Radius=2;
	Strength=10.0;
	SourceYLen=0;
	SourceBuffer=NULL;
}
FilterEdgeEmphasize::~FilterEdgeEmphasize(void)
{
	if(SourceBuffer!=NULL){
		DeleteMatrixBuff(SourceBuffer,SourceYLen);
		SourceYLen=0;
		SourceBuffer=NULL;
	}
}

bool	FilterEdgeEmphasize::Save(QIODevice *f)
{
	if(::Save(f,Radius)==false)
		return false;
	if(::Save(f,Strength)==false)
		return false;
	return true;
}
bool	FilterEdgeEmphasize::Load(QIODevice *f)
{
	if(::Load(f,Radius)==false)
		return false;
	if(::Load(f,Strength)==false)
		return false;
	return true;
}
bool	FilterEdgeEmphasize::Initial(void)
{
	double	Sum=0;
	for(int y=-Radius;y<=Radius;y++){
		for(int x=-Radius;x<=Radius;x++){
			if(x==0 && y==0)
				continue;
			int	X=x+Radius;
			int	Y=y+Radius;
			double	L=x*x+y*y;
			int	P=-256.0*Strength/L;
			Sum+=P;
			FilterTable[Y][X]=P;
		}
	}
	FilterTable[Radius][Radius]=-Sum;

	if(SourceBuffer!=NULL){
		DeleteMatrixBuff(SourceBuffer,SourceYLen);
	}
	SourceYLen=2*Radius+1+Radius+1;
	SourceBuffer=MakeMatrixBuff(GetDotPerLine() ,SourceYLen);

	return true;
}
bool	FilterEdgeEmphasize::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(SourceBuffer!=NULL){
		DeleteMatrixBuff(SourceBuffer,SourceYLen);
	}
	SourceBuffer=MakeMatrixBuff(NewDotPerLine ,SourceYLen);

	return true;
}

bool	FilterEdgeEmphasize::Reallocate(int newLayerNumb)
{
	return true;
}
bool	FilterEdgeEmphasize::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	for(int L=0;L<BufferDimCounts;L++){
		for(int y=0;y<SourceYLen;y++){
			memcpy(SourceBuffer[y],Buff[L]->GetY(y),GetDotPerLine());
			SourcePointer[y]=SourceBuffer[y];
		}
		int YLen=GetMaxLines()-SourceYLen;
		#pragma omp parallel
		{
			#pragma omp for
			for(int Y=0;Y<YLen;Y++){
				int	y=Y+Radius;
				BYTE	*d=Buff[L]->GetY(y);
				for(int x=Radius;x<GetDotPerLine()-Radius;x++){
					int	D=0;
					//int	ix,iy;
					for(int dy=-Radius,iy=0;dy<=Radius;dy++,iy++){
						BYTE	*s=SourcePointer[Radius+dy];
						for(int dx=-Radius,ix=0;dx<=Radius;dx++,ix++){
							D+=FilterTable[iy][ix]*s[x+dx];
						}
					}
					D>>=16;
					d[x]=D;
				}
				BYTE	*FirstP=SourcePointer[0];
				memmove(SourcePointer,&SourcePointer[1],(SourceYLen-1)*sizeof(BYTE *));
				if(Y+SourceYLen<GetMaxLines()){
					memcpy(FirstP,Buff[L]->GetY(Y+SourceYLen),GetDotPerLine());
					SourcePointer[SourceYLen-1]=FirstP;
				}
			}
		}
	}	

	return true;
}
